/*
 * MatrixTask.cpp
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

#include "MatrixTask.h"

#include "../data/image.h"

#include "string.h"

#include "Protocol.h"

extern uint8_t txBufferA[2048];
extern uint8_t txBufferB[2048];

#define MESSAGE_HEADER 4
#define BYTES_PER_PIXEL 4

constexpr uint16_t DATA_POSITION = PROTOCOL_HEADER + MESSAGE_HEADER;
constexpr uint16_t PIXELS_PER_MESSAGE = (MESSAGE_BODY_BYTES - MESSAGE_HEADER)
		/ BYTES_PER_PIXEL;

#define TASK_NAME "MatrixTask"

void matrixTask(void *pvParameters) {
	ESP_LOGI(TASK_NAME, "Task start");

	static spi_transaction_t txTransA;
	static spi_transaction_t txTransB;
	static bool useA = true;

	spi_transaction_t *txTrans = useA ? &txTransA : &txTransB;

	uint8_t *txBuffer = useA ? txBufferA : txBufferB;

	TaskParameters *taskParameters = (TaskParameters*) pvParameters;

	uint8_t frame = 0;

	txTransA.rx_buffer = NULL;
	txTransA.tx_buffer = txBufferA;
	txTransA.length = (MESSAGE_BODY_BYTES + PROTOCOL_HEADER) * 8;
	txTransA.rxlength = 0;

	txTransB.rx_buffer = NULL;
	txTransB.tx_buffer = txBufferB;
	txTransB.length = (MESSAGE_BODY_BYTES + PROTOCOL_HEADER) * 8;
	txTransB.rxlength = 0;

	gpio_config_t gpio_conf = {
		.pin_bit_mask = 1 << 4,
		.mode = GPIO_MODE_OUTPUT };

	ESP_ERROR_CHECK(gpio_config(&gpio_conf));
	ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_4, 0));

	//Configure the target to use matrix mode
	uint16_t width = 64;
	uint16_t height = 32;

	struct ConfigurationDefinition configurationDefinition = {
		.version = CONFIGURATION_VERSION,
		.displayType = ConfigurationDisplayType::Matrix,
		.widthH = UINT16_TO_HBYTE(width),
		.widthL = UINT16_TO_LBYTE(width),
		.heightH = UINT16_TO_HBYTE(height),
		.heightL = UINT16_TO_LBYTE(height),
		.elements = 2,
		.pixelMappingType = 2 };

	txBuffer[0] = RequestType::Configure;

	uint16_t messageSize = sizeof(struct ConfigurationDefinition);
	txBuffer[1] = messageSize >> 8;
	txBuffer[2] = messageSize & 0xFF;

	memcpy(&txBuffer[3], &configurationDefinition, messageSize);

	ESP_ERROR_CHECK(
			spi_device_polling_transmit(taskParameters->spiDevice,
					txTrans));

	vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);
	vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);
	vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);

	ESP_LOGI(TASK_NAME, "Configuration sent");

	while (1) {
		uint16_t pixelCount = 0;

		txBuffer[0] = RequestType::SetPixelData;

		for (uint16_t y = 0; y < IMAGE_HEIGHT; y++) {
			for (uint16_t x = 0; x < IMAGE_WIDTH; x++) {
//				uint8_t r =0;
//				uint8_t g =0;
//				uint8_t b =0;
//
//				if(y == frame) {
//					r = 255;
//				}
				if (pixelCount == 0) {
					//X Starting coordinate
					txBuffer[3] = x >> 8;
					txBuffer[4] = x & 0xFF;
					//Y Starting coordinate
					txBuffer[5] = y >> 8;
					txBuffer[6] = y & 0xFF;
				}

				uint8_t r =
						IMAGE_DATA[frame][x % IMAGE_WIDTH][y % IMAGE_HEIGHT][0];
				uint8_t g =
						IMAGE_DATA[frame][x % IMAGE_WIDTH][y % IMAGE_HEIGHT][1];
				uint8_t b =
						IMAGE_DATA[frame][x % IMAGE_WIDTH][y % IMAGE_HEIGHT][2];

				txBuffer[DATA_POSITION + (pixelCount * BYTES_PER_PIXEL) + 0] =
						r;
				txBuffer[DATA_POSITION + (pixelCount * BYTES_PER_PIXEL) + 1] =
						g;
				txBuffer[DATA_POSITION + (pixelCount * BYTES_PER_PIXEL) + 2] =
						b;
				txBuffer[DATA_POSITION + (pixelCount * BYTES_PER_PIXEL) + 3] =
						0;

				pixelCount++;

				if (pixelCount == PIXELS_PER_MESSAGE) {
					uint16_t messageBytes = 4 + (BYTES_PER_PIXEL * pixelCount);
					txBuffer[1] = messageBytes >> 8;
					txBuffer[2] = messageBytes & 0xFF;

					ESP_ERROR_CHECK(
							spi_device_polling_transmit(
									taskParameters->spiDevice, txTrans));

					useA = !useA;
					txTrans = useA ? &txTransA : &txTransB;
					txBuffer = useA ? txBufferA : txBufferB;

					txBuffer[0] = RequestType::SetPixelData;

					vTaskDelay(MESSAGE_DELAY_MS / portTICK_PERIOD_MS);

					pixelCount = 0;
				}
			}
		}

		if (pixelCount > 0) {
			uint16_t messageBytes = 4 + (BYTES_PER_PIXEL * pixelCount);
			txBufferA[1] = messageBytes >> 8;
			txBufferA[2] = messageBytes & 0xFF;
			ESP_ERROR_CHECK(
					spi_device_polling_transmit(taskParameters->spiDevice,
							txTrans));

			useA = !useA;
			txTrans = useA ? &txTransA : &txTransB;
			txBuffer = useA ? txBufferA : txBufferB;

			vTaskDelay(MESSAGE_DELAY_MS / portTICK_PERIOD_MS);

//			ESP_LOGI(TASK_NAME, "Frame Completion");

			pixelCount = 0;
		}

		txBuffer[0] = RequestType::Commit;
		txBuffer[1] = 0;
		txBuffer[2] = 0;

		ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_4, 1));

		ESP_ERROR_CHECK(
				spi_device_polling_transmit(taskParameters->spiDevice,
						txTrans));

		useA = !useA;
		txTrans = useA ? &txTransA : &txTransB;
		txBuffer = useA ? txBufferA : txBufferB;

//		ESP_LOGI(TASK_NAME, "Frame Commit");

		ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_4, 0));

		vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);

		frame++;

		if (frame >= IMAGE_FRAMES) {
			ESP_LOGI(TASK_NAME, "Frame Reset");
			frame = 0;
		}
	}
}

MatrixTask::MatrixTask() {

}

MatrixTask::~MatrixTask() {

}

