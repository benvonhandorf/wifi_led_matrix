/*
 * ControlTask.cpp
 *
 *  Created on: Jan 24, 2021
 *      Author: benvh
 */
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "esp_system.h"
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
	
}

static ControlTask controlTaskInstance;

void controlTask(void *pvParameters) {
	controlTaskInstance.Run();
}
