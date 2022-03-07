/*
 * ControlTask.cpp
 *
 *  Created on: Jan 24, 2021
 *      Author: benvh
 */
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "driver/gpio.h"
#include "driver/touch_pad.h"
#include "driver/touch_sensor.h"

#include "TaskParameters.h"

#include "ControlTask.h"

#define TASK_NAME "ControlTask"

#define TOUCH_PAD_A TOUCH_PAD_NUM7
#define TOUCH_PAD_B TOUCH_PAD_NUM8
#define TOUCH_PAD_C TOUCH_PAD_NUM9

#define TOUCHPAD_FILTER_TOUCH_PERIOD 10

ControlTask::ControlTask() {

}

ControlTask::~ControlTask() {

}

void ControlTask::Run() {
//	ESP_LOGI(TASK_NAME, "Running");
//
//	ESP_ERROR_CHECK(touch_pad_init());
//
//	ESP_ERROR_CHECK(touch_pad_set_voltage(TOUCH_HVOLT_2V7, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_1V));
//
//	ESP_ERROR_CHECK(touch_pad_io_init(TOUCH_PAD_A));
//	ESP_ERROR_CHECK(touch_pad_io_init(TOUCH_PAD_B));
//	ESP_ERROR_CHECK(touch_pad_io_init(TOUCH_PAD_C));
//
//	ESP_ERROR_CHECK(touch_pad_config(TOUCH_PAD_A, 0));
//
//	ESP_ERROR_CHECK(touch_pad_filter_read_smooth(TOUCHPAD_FILTER_TOUCH_PERIOD));
//
//	uint16_t touchValue, filteredValue;
//
//	while(1) {
//		vTaskDelay(100 / portTICK_PERIOD_MS);
//
//		ESP_ERROR_CHECK(touch_pad_read_raw_data(TOUCH_PAD_A, &touchValue));
//		ESP_ERROR_CHECK(touch_pad_read_filtered(TOUCH_PAD_A, &filteredValue));
//
//		ESP_LOGI(TASK_NAME, "Reading: %d - %d", touchValue, filteredValue);
//	}
}

static ControlTask controlTaskInstance;

void controlTask(void *pvParameters) {
	controlTaskInstance.Run();
}
