/*
 * DisplayBuffer.h
 *
 *  Created on: Mar 7, 2021
 *      Author: benvh
 */

#ifndef COMPONENTS_COMMON_DISPLAYBUFFER_H_
#define COMPONENTS_COMMON_DISPLAYBUFFER_H_

#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

class DisplayBuffer {
public:
	uint16_t width;
	uint16_t height;

	uint8_t *buffer;
};

//Owned by the DisplayTask
extern QueueHandle_t AVAILABLE_DISPLAY_BUFFER;
extern QueueHandle_t COMMITTED_DISPLAY_BUFFER;

#endif /* COMPONENTS_COMMON_DISPLAYBUFFER_H_ */
