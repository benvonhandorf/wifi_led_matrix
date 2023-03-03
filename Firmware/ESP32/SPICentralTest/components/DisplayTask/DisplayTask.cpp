/*
 * DisplayTask.cpp
 *
 *  Created on: Mar 7, 2021
 *      Author: benvh
 */

#include "DisplayTask.h"

#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/atomic.h"

#include <stdio.h>
#include <string.h>

#include "TaskParameters.h"
#include "Configuration.h"
#include "DisplayBuffer.h"

#include "Protocol.h"

#include "PerformanceCounters.h"

QueueHandle_t AVAILABLE_DISPLAY_BUFFER;
QueueHandle_t COMMITTED_DISPLAY_BUFFER;

DisplayTask internalDisplayTask;

constexpr uint16_t COMMAND_BUFFER_SIZE = 2048;

QueueHandle_t AVAILABLE_COMMAND_BUFFER;

constexpr uint8_t DISPLAY_BUFFERS = 3;
DisplayBuffer displayBuffers[DISPLAY_BUFFERS];

#define MESSAGE_HEADER 4
#define BYTES_PER_PIXEL 8
constexpr uint16_t DATA_POSITION = PROTOCOL_HEADER + MESSAGE_HEADER;
constexpr uint16_t PIXELS_PER_MESSAGE = (MESSAGE_BODY_BYTES - MESSAGE_HEADER)
		/ BYTES_PER_PIXEL;

void displayTask(void *pvParameters) {
	TaskParameters *taskParameters = (TaskParameters*) pvParameters;
	Configuration *configuration = taskParameters->configuration;

	ESP_LOGI("DisplayTask", "Begin initialize");

	internalDisplayTask.Initialize(configuration, taskParameters->spiDevice);
}

DisplayTask::DisplayTask() {

}

DisplayTask::~DisplayTask() {

}

void DisplayTask::Initialize(Configuration *configuration,
		spi_device_handle_t spi) {
	this->configuration = configuration;
	this->spiDevice = spi;

	AVAILABLE_DISPLAY_BUFFER = xQueueCreate(3, sizeof(DisplayBuffer*));
	COMMITTED_DISPLAY_BUFFER = xQueueCreate(3, sizeof(DisplayBuffer*));

	uint16_t bufferSize = configuration->width * configuration->height * 4;

	for (int i = 0; i < DISPLAY_BUFFERS; i++) {
		DisplayBuffer *displayBuffer = &(displayBuffers[i]);
		displayBuffer->width = configuration->width;
		displayBuffer->height = configuration->height;

		displayBuffer->buffer = (uint8_t*) malloc(bufferSize);

		ESP_LOGI("DisplayTask", "Adding buffer: %lx", (uint32_t) displayBuffer);

		xQueueSend(AVAILABLE_DISPLAY_BUFFER, &displayBuffer, portMAX_DELAY);
	}

	AVAILABLE_COMMAND_BUFFER = xQueueCreate(2, sizeof(uint8_t*));

	uint8_t *txBuffer = (uint8_t*) malloc(COMMAND_BUFFER_SIZE);

	xQueueSend(AVAILABLE_COMMAND_BUFFER, &txBuffer, portMAX_DELAY);

	txBuffer = (uint8_t*) malloc(COMMAND_BUFFER_SIZE);

	xQueueSend(AVAILABLE_COMMAND_BUFFER, &txBuffer, portMAX_DELAY);

	ESP_LOGI("DisplayTask", "Preparing for configure");

	Configure();

	while (true) {
		DisplayBuffer *displayBuffer;

		if (xQueueReceive(COMMITTED_DISPLAY_BUFFER, &displayBuffer,
		portMAX_DELAY) == pdPASS) {

			ProcessBuffer(displayBuffer);

			xQueueSend(AVAILABLE_DISPLAY_BUFFER, &displayBuffer, portMAX_DELAY);
		} else {
			ESP_LOGI("DisplayTask", "No command available");
		}
	}
}

void DisplayTask::Configure() {
	uint8_t *txBuffer = NULL;

	if (xQueueReceive(AVAILABLE_COMMAND_BUFFER, &txBuffer,
	portMAX_DELAY) == pdPASS) {

		struct ConfigurationDefinition configurationDefinition = {
			.version = CONFIGURATION_VERSION,
			.displayType = ConfigurationDisplayType::WS2812Strand,
			.widthH = UINT16_TO_HBYTE(configuration->width),
			.widthL = UINT16_TO_LBYTE(configuration->width),
			.heightH = UINT16_TO_HBYTE(configuration->height),
			.heightL = UINT16_TO_LBYTE(configuration->height),
			.elements = 1,
			.pixelMappingType = 0 };

		txBuffer[0] = RequestType::Configure;

		uint16_t messageSize = sizeof(struct ConfigurationDefinition);
		txBuffer[1] = messageSize >> 8;
		txBuffer[2] = messageSize & 0xFF;

		memcpy(&txBuffer[3], &configurationDefinition, messageSize);

		SendMessage(txBuffer);

		xQueueSend(AVAILABLE_COMMAND_BUFFER, &txBuffer, portMAX_DELAY);
	} else {
		ESP_LOGE("DisplayTask", "No command available for configuration!");
	}
}

void DisplayTask::ProcessBuffer(DisplayBuffer *displayBuffer) {

	uint8_t *txBuffer = NULL;

	if (xQueueReceive(AVAILABLE_COMMAND_BUFFER, &txBuffer,
	portMAX_DELAY) == pdPASS) {

		uint16_t offset = 0;

		txBuffer[offset++] = RequestType::ClearAssignPixelData;
		//Skip the message size bytes
		offset++;
		offset++;

		for (uint16_t x = 0; x < configuration->width; x++) {
			for (uint16_t y = 0; y < configuration->height; y++) {
				uint16_t pixelOffset = (y * configuration->width * 4) + (x * 4);

				if (displayBuffer->buffer[pixelOffset + 0]
						|| displayBuffer->buffer[pixelOffset + 1]
						|| displayBuffer->buffer[pixelOffset + 2]
						|| displayBuffer->buffer[pixelOffset + 3]) {
					//Something for this pixel is non-zero, so we send it.
					txBuffer[offset++] = UINT16_TO_HBYTE(x);
					txBuffer[offset++] = UINT16_TO_LBYTE(x);
					txBuffer[offset++] = UINT16_TO_HBYTE(y);
					txBuffer[offset++] = UINT16_TO_LBYTE(y);
					txBuffer[offset++] = displayBuffer->buffer[pixelOffset + 0];
					txBuffer[offset++] = displayBuffer->buffer[pixelOffset + 1];
					txBuffer[offset++] = displayBuffer->buffer[pixelOffset + 2];
					txBuffer[offset++] = displayBuffer->buffer[pixelOffset + 3];
				}

				if ((offset + BYTES_PER_PIXEL) > NETWORK_PACKET_SIZE) {
					uint16_t bodyBytes = offset - 3;
					txBuffer[1] = ((uint8_t) (bodyBytes / 256));
					txBuffer[2] = ((uint8_t) (bodyBytes % 256));

					SendMessage(txBuffer);

					txBuffer[0] = RequestType::AssignPixelData;
					offset = 3;
				}
			}
		}

		if (offset > 3) {
			uint16_t bodyBytes = offset - 3;
			txBuffer[1] = ((uint8_t) (bodyBytes / 256));
			txBuffer[2] = ((uint8_t) (bodyBytes % 256));

			SendMessage(txBuffer);
		}

		txBuffer[0] = RequestType::Commit;
		txBuffer[1] = 0;
		txBuffer[2] = 0;

		SendMessage(txBuffer);

		xQueueSend(AVAILABLE_COMMAND_BUFFER, &txBuffer, portMAX_DELAY);

		Atomic_Increment_u32(&(performanceCounters.framesDrawn));
	} else {
		ESP_LOGI("DisplayTask",
				"No command available display buffer, frame dropped!");
	}
}

void DisplayTask::SendMessage(uint8_t *transmissionBuffer) {
	esp_err_t ret;

	spi_transaction_t transaction;

	transaction.flags = 0;
	transaction.rx_buffer = NULL;
	transaction.tx_buffer = transmissionBuffer;
	transaction.length = (MESSAGE_BODY_BYTES + 3) * 8;
	transaction.rxlength = 0;

	ret = spi_device_polling_transmit(spiDevice, &transaction);
	ESP_ERROR_CHECK(ret);

	Atomic_Increment_u32(&(performanceCounters.packetsSent));

	vTaskDelay(7 / portTICK_PERIOD_MS);
}
