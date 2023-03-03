/*
 * ChaserTask.cpp
 *
 *  Created on: Jan 17, 2021
 *      Author: benvh
 */

#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_random.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"

#include "TaskParameters.h"

#include "Protocol.h"

#include "string.h"

#include "DisplayBuffer.h"

#include "ChaserTask.h"
#include "Colors.h"

typedef struct {
	int16_t position;
	int8_t velocity;
	uint8_t color[4];
} Particle;

#define PARTICLES 4

Particle particles[PARTICLES];

void chaserTask(void *pvParameters) {
	ESP_LOGI("ChaserTask", "Task start");

	struct TaskParameters *taskParameters = (TaskParameters*) pvParameters;
	Configuration *configuration = taskParameters->configuration;

	uint8_t particleIndex = 0;
	uint32_t velocityRandom;

	particles[particleIndex].position = 0;
	velocityRandom = esp_random();
	particles[particleIndex].velocity = ((int8_t) velocityRandom & 0x7)
			* (velocityRandom & 0x80 ? -1 : 1);
	particles[particleIndex].velocity =
			particles[particleIndex].velocity ?
					particles[particleIndex].velocity : 1;
	random_rgbw_uint8_t(particles[particleIndex].color);
	particles[particleIndex].color[3] /= 8;

	particleIndex++;

	particles[particleIndex].position = 0;
	velocityRandom = esp_random();
	particles[particleIndex].velocity = ((int8_t) velocityRandom & 0x7)
			* (velocityRandom & 0x80 ? -1 : 1);
	particles[particleIndex].velocity =
			particles[particleIndex].velocity ?
					particles[particleIndex].velocity : 1;
	random_rgbw_uint8_t(particles[particleIndex].color);
	particles[particleIndex].color[3] /= 8;

	particleIndex++;

	particles[particleIndex].position = 0;
	velocityRandom = esp_random();
	particles[particleIndex].velocity = ((int8_t) velocityRandom & 0x7)
			* (velocityRandom & 0x80 ? -1 : 1);
	particles[particleIndex].velocity =
			particles[particleIndex].velocity ?
					particles[particleIndex].velocity : 1;
	random_rgbw_uint8_t(particles[particleIndex].color);
	particles[particleIndex].color[3] /= 8;

	particleIndex++;

	particles[particleIndex].position = 0;
	velocityRandom = esp_random();
	particles[particleIndex].velocity = ((int8_t) velocityRandom & 0x7)
			* (velocityRandom & 0x80 ? -1 : 1);
	particles[particleIndex].velocity =
			particles[particleIndex].velocity ?
					particles[particleIndex].velocity : 1;
	random_rgbw_uint8_t(particles[particleIndex].color);
	particles[particleIndex].color[3] /= 8;

	vTaskDelay(COMMIT_DELAY_MS / portTICK_PERIOD_MS);

	while (1) {
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

				particles[particleIndex].position = configuration->width;

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

		DisplayBuffer *displayBuffer;

		if (xQueueReceive(AVAILABLE_DISPLAY_BUFFER, &displayBuffer,
		portMAX_DELAY) == pdPASS) {

			memset(displayBuffer->buffer, 0, displayBuffer->width * displayBuffer->height * 4);

			for (particleIndex = 0; particleIndex < PARTICLES;
					particleIndex++) {
				Particle *particle = &particles[particleIndex];

				for (uint8_t tail = 0; tail < 8; tail++) {
					int16_t direction = particle->velocity > 0 ? -1 : 1;
					int16_t position = particle->position + (tail * direction);

					if (position > 0 && position < 300) {
						displayBuffer->buffer[(position * 4) + 0] = particle->color[0] / (tail + 1);
						displayBuffer->buffer[(position * 4) + 1] = particle->color[1] / (tail + 1);
						displayBuffer->buffer[(position * 4) + 2] = particle->color[2] / (tail + 1);
						displayBuffer->buffer[(position * 4) + 3] = particle->color[3] / (tail + 1);
					}
				}


			}

			xQueueSend(COMMITTED_DISPLAY_BUFFER, &displayBuffer, portMAX_DELAY);
		} else {
			ESP_LOGW("ChaserTask", "Failed to obtain display buffer");
		}

		vTaskDelay(20 / portTICK_PERIOD_MS);
	}
}

ChaserTask::ChaserTask() {
	// TODO Auto-generated constructor stub

}

ChaserTask::~ChaserTask() {
	// TODO Auto-generated destructor stub
}

