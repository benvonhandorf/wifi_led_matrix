/*
 * PerformanceCounters.cpp
 *
 *  Created on: Mar 12, 2021
 *      Author: benvh
 */

#include "PerformanceCounters.h"
#include "esp_log.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/atomic.h>

PerformanceCounters performanceCounters;

PerformanceCounters::PerformanceCounters() {
	// TODO Auto-generated constructor stub

}

PerformanceCounters::~PerformanceCounters() {
	// TODO Auto-generated destructor stub
}

char stats_buffer[1024];

void performanceCountersTask(void *pvParameters) {

	uint32_t previousTicks = xTaskGetTickCount();

	ESP_LOGI("PERF", "Frames, Packets");

	while(true) {
		uint32_t _framesDrawn = performanceCounters.framesDrawn;

		Atomic_Subtract_u32(&performanceCounters.framesDrawn, _framesDrawn);

		uint32_t _packetsSent = performanceCounters.packetsSent;

		Atomic_Subtract_u32(&performanceCounters.packetsSent, _packetsSent);

		ESP_LOGI("PERF", "%d, %d", _framesDrawn, _packetsSent);

//		vTaskGetRunTimeStats(stats_buffer);
//
//		ESP_LOGI("PERF", "%s", stats_buffer);

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}
