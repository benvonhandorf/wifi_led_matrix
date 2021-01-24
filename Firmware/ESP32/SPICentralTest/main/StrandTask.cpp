/*
 * StrandTask.cpp
 *
 *  Created on: Jan 17, 2021
 *      Author: benvh
 */

#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"

#include "TaskParameters.h"

#include "StrandTask.h"

#include "Protocol.h"

#include "string.h"

extern uint8_t txBufferA[2048];
extern uint8_t txBufferB[2048];

#define MESSAGE_HEADER 4
#define BYTES_PER_PIXEL 8
constexpr uint16_t DATA_POSITION = PROTOCOL_HEADER + MESSAGE_HEADER;
constexpr uint16_t PIXELS_PER_MESSAGE = (MESSAGE_BODY_BYTES - MESSAGE_HEADER)
		/ BYTES_PER_PIXEL;

void write_strand(spi_device_handle_t *spi, uint16_t x, uint16_t pixels,
		uint8_t *values) {
	spi_transaction_t txTrans = {

	};

	uint16_t offset = 0;

	txBufferA[offset++] = RequestType::SetPixelData;
	txBufferA[offset++] = 0x00;
	txBufferA[offset++] = 0x00;

	txBufferA[offset++] = x / 256;
	txBufferA[offset++] = x % 256;
	txBufferA[offset++] = 0x00;
	txBufferA[offset++] = 0x00;

	uint16_t valueOffset = 0;

	for (uint16_t i = 0; i < pixels; i++) {
		txBufferA[offset++] = values[valueOffset++];
		txBufferA[offset++] = values[valueOffset++];
		txBufferA[offset++] = values[valueOffset++];
		txBufferA[offset++] = values[valueOffset++];
	}

	uint16_t bodyBytes = offset - 3;
	txBufferA[1] = ((uint8_t) (bodyBytes / 256));
	txBufferA[2] = ((uint8_t) (bodyBytes % 256));

	txTrans.rx_buffer = NULL;
	txTrans.tx_buffer = txBufferA;
	txTrans.length = (MESSAGE_BODY_BYTES + 3) * 8;
	txTrans.rxlength = 0;

	esp_err_t ret;

	ESP_LOGI("StrandTask", "Data: %d - %d - %d  %d", x, txBufferA[1],
			txBufferA[2], bodyBytes);

	ret = spi_device_polling_transmit(*spi, &txTrans);
	ESP_ERROR_CHECK(ret);
}

void commit_strand(spi_device_handle_t *spi) {
	uint16_t offset = 0;
	txBufferA[offset++] = RequestType::Commit;
	txBufferA[offset++] = 0x00;
	txBufferA[offset++] = 0x00;

	spi_transaction_t txTrans = {

	};

	txTrans.tx_buffer = txBufferA;
	txTrans.rx_buffer = NULL;
	txTrans.length = NETWORK_PACKET_SIZE * 8;
	txTrans.rxlength = 0;

	esp_err_t ret;

	ESP_LOGI("StrandTask", "Commit");

	ret = spi_device_polling_transmit(*spi, &txTrans);
	ESP_ERROR_CHECK(ret);
}

typedef struct {
	int16_t position;
	int8_t velocity;
	uint8_t color[4];
} Particle;

#define PARTICLES 4

Particle particles[PARTICLES];

void assign_strand(spi_device_handle_t *spi) {
	spi_transaction_t txTrans = {

	};

	uint16_t offset = 0;

	txBufferA[offset++] = RequestType::ClearAssignPixelData;
	txBufferA[offset++] = 0x00;
	txBufferA[offset++] = 0x00;

	for (uint16_t particleIndex = 0; particleIndex < PARTICLES;
			particleIndex++) {
		Particle *particle = particles + particleIndex;

		for (uint8_t tail = 0; tail < 8; tail++) {
			int16_t direction = particle->velocity > 0 ? -1 : 1;
			int16_t position = particle->position + (tail * direction);

			if (position > 0 && position < 300) {
				txBufferA[offset++] = position / 256;
				txBufferA[offset++] = position % 256;
				txBufferA[offset++] = 0x00;
				txBufferA[offset++] = 0x00;
				txBufferA[offset++] = particle->color[0] / (tail + 1);
				txBufferA[offset++] = particle->color[1] / (tail + 1);
				txBufferA[offset++] = particle->color[2] / (tail + 1);
				txBufferA[offset++] = particle->color[3] / (tail + 1);
			}
		}
	}

	uint16_t bodyBytes = offset - 3;
	txBufferA[1] = ((uint8_t) (bodyBytes / 256));
	txBufferA[2] = ((uint8_t) (bodyBytes % 256));

	txTrans.tx_buffer = txBufferA;
	txTrans.rx_buffer = NULL;
	txTrans.length = NETWORK_PACKET_SIZE * 8;
	txTrans.rxlength = 0;

	esp_err_t ret;

	ret = spi_device_polling_transmit(*spi, &txTrans);
	ESP_ERROR_CHECK(ret);
}

void strandTask(void *pvParameters) {
	ESP_LOGI("StrandTask", "Task start");

	struct TaskParameters *taskParameters = (TaskParameters*) pvParameters;

	uint8_t particleIndex = 0;
	uint32_t velocityRandom;

	particles[particleIndex].position = 0;
	velocityRandom = esp_random();
	particles[particleIndex].velocity = ((int8_t) velocityRandom & 0x7)
			* (velocityRandom & 0x80 ? -1 : 1);
	particles[particleIndex].velocity =
			particles[particleIndex].velocity ?
					particles[particleIndex].velocity : 1;
	esp_fill_random(particles[particleIndex].color, 4);
	particles[particleIndex].color[3] /= 8;

	particleIndex++;

	particles[particleIndex].position = 0;
	velocityRandom = esp_random();
	particles[particleIndex].velocity = ((int8_t) velocityRandom & 0x7)
			* (velocityRandom & 0x80 ? -1 : 1);
	particles[particleIndex].velocity =
			particles[particleIndex].velocity ?
					particles[particleIndex].velocity : 1;
	esp_fill_random(particles[particleIndex].color, 4);
	particles[particleIndex].color[3] /= 8;

	particleIndex++;

	particles[particleIndex].position = 0;
	velocityRandom = esp_random();
	particles[particleIndex].velocity = ((int8_t) velocityRandom & 0x7)
			* (velocityRandom & 0x80 ? -1 : 1);
	particles[particleIndex].velocity =
			particles[particleIndex].velocity ?
					particles[particleIndex].velocity : 1;
	esp_fill_random(particles[particleIndex].color, 4);
	particles[particleIndex].color[3] /= 8;

	particleIndex++;

	particles[particleIndex].position = 0;
	velocityRandom = esp_random();
	particles[particleIndex].velocity = ((int8_t) velocityRandom & 0x7)
			* (velocityRandom & 0x80 ? -1 : 1);
	particles[particleIndex].velocity =
			particles[particleIndex].velocity ?
					particles[particleIndex].velocity : 1;
	esp_fill_random(particles[particleIndex].color, 4);
	particles[particleIndex].color[3] /= 8;

	esp_err_t ret;

	gpio_config_t gpio_conf = {
		.pin_bit_mask = 1 << 4,
		.mode = GPIO_MODE_OUTPUT };

	ESP_ERROR_CHECK(gpio_config(&gpio_conf));
	ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_4, 0));

	//Configure the target to use matrix mode
	uint16_t width = 300;
	uint16_t height = 1;

	struct ConfigurationDefinition configurationDefinition = {
		.version = CONFIGURATION_VERSION,
		.displayType = ConfigurationDisplayType::WS2812Strand,
		.widthH = UINT16_TO_HBYTE(width),
		.widthL = UINT16_TO_LBYTE(width),
		.heightH = UINT16_TO_HBYTE(height),
		.heightL = UINT16_TO_LBYTE(height),
		.elements = 1,
		.pixelMappingType = 0 };

	txBufferA[0] = RequestType::Configure;

	uint16_t messageSize = sizeof(struct ConfigurationDefinition);
	txBufferA[1] = messageSize >> 8;
	txBufferA[2] = messageSize & 0xFF;

	memcpy(&txBufferA[3], &configurationDefinition, messageSize);

	vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);
	vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);
	vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);

	spi_transaction_t txTrans = {

	};

	txTrans.tx_buffer = txBufferA;
	txTrans.rx_buffer = NULL;
	txTrans.length = NETWORK_PACKET_SIZE * 8;
	txTrans.rxlength = 0;

//	while (1) {
	ESP_ERROR_CHECK(
			spi_device_polling_transmit(taskParameters->spiDevice, &txTrans));

	ESP_LOGI("StrandTask", "Configuration sent - %d", messageSize);
//		for (int i = 0; i < 50; i++) {
//			vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);
//			vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);
//			vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);
//			vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);
//			vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);
//			vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);
//			vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);
//			vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);
//			vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);
//			vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);
//			vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);
//			vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);
//		}
//	}

	vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);
	vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);
	vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);

	uint16_t shift = 0;
	uint16_t pixels = 64;

	while (1) {
		ESP_LOGI("StrandTask", "Loop, shift %d", shift);

		for (particleIndex = 0; particleIndex < PARTICLES; particleIndex++) {
			particles[particleIndex].position +=
					particles[particleIndex].velocity;
			if (particles[particleIndex].position < -10) {
				velocityRandom = esp_random();
				if ((velocityRandom & 0x3) == 0x3
						&& particles[particleIndex].velocity > -10) {
					particles[particleIndex].velocity -= 1;
					particles[particleIndex].velocity =
							particles[particleIndex].velocity ?
									particles[particleIndex].velocity : -1;
				} else if ((velocityRandom & 0x1) == 0x1
						&& particles[particleIndex].velocity < -0) {
					particles[particleIndex].velocity += 1;
					particles[particleIndex].velocity =
							particles[particleIndex].velocity ?
									particles[particleIndex].velocity : 1;
				}

				particles[particleIndex].position = 300;

			} else if (particles[particleIndex].position > 310) {
				velocityRandom = esp_random();
				if ((velocityRandom & 0x3) == 0x3
						&& particles[particleIndex].velocity > -10) {
					particles[particleIndex].velocity -= 1;
					particles[particleIndex].velocity =
							particles[particleIndex].velocity ?
									particles[particleIndex].velocity : -1;
				} else if ((velocityRandom & 0x1) == 0x1
						&& particles[particleIndex].velocity < -0) {
					particles[particleIndex].velocity += 1;
					particles[particleIndex].velocity =
							particles[particleIndex].velocity ?
									particles[particleIndex].velocity : 1;
				}

				particles[particleIndex].position = 0;
			}
		}

		ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_4, 1));
		assign_strand(&taskParameters->spiDevice);
		ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_4, 0));

		vTaskDelay(MESSAGE_DELAY_MS / portTICK_PERIOD_MS);

		ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_4, 1));
		commit_strand(&taskParameters->spiDevice);
		ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_4, 0));

		vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);

		shift++;
	}
}

StrandTask::StrandTask() {
	// TODO Auto-generated constructor stub

}

StrandTask::~StrandTask() {
	// TODO Auto-generated destructor stub
}

