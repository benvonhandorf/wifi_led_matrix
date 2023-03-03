/*
 * LedSingleWire.cpp
 *
 *  Created on: Nov 17, 2020
 *      Author: benvh
 */

#include "main.h"
#include <DisplayDriver.hpp>
#include "LedSingleWire.hpp"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern DMA_HandleTypeDef hdma_tim1_ch1;

#define SLOTS_PER_BIT 4

#define LEAD_IN 4
#define LEAD_OUT 4

LedSingleWire *instance;

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim) {
	instance->StartNextDma();
}

LedSingleWire::LedSingleWire() {
	instance = this;
}

void LedSingleWire::Open(Configuration *configuration) {
	this->format = (LedSingleWire::Format) configuration->strandFormat;
	this->strandCount = configuration->elementCount;

	switch (this->format) {
	case RGBW:
	case GRBW:
		this->bytesPerPixel = 4;
		break;
	}

	//Each time division will be ~ 0.3uS.  0 looks like 0.3us/0.9us.  1 looks like 0.6us/0.6us so
	//each bit requires 4 time divisions
	this->pixelCount = configuration->elementWidth;
	this->bufferLength = (SLOTS_PER_BIT * bytesPerPixel * 8 * pixelCount)
			+ LEAD_IN + LEAD_OUT;

	buffer = new uint16_t[this->bufferLength];

	//Blanks the string

	for (uint16_t offset = 0; offset < bufferLength; offset++) {
		if (offset < LEAD_IN || offset > LEAD_OUT) {
			buffer[offset] = 0x0000;
		} else {
			buffer[offset] = 0xFFFF;
		}
	}

	for (uint8_t strand = 0; strand < strandCount; strand++) {
		for (uint16_t pixel = 0; pixel < pixelCount; pixel++) {
			SetPixel(pixel, strand, 0, 0, 0, 0);
		}
	}

	__HAL_TIM_ENABLE_DMA(&htim1, TIM_DMA_CC1);

	TIM_CCxChannelCmd(htim1.Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);

	__HAL_TIM_ENABLE_IT(&htim3, TIM_IT_CC1);

//	htim3.OC_DelayElapsedCallback = ResetDelayElapsed;

	HAL_StatusTypeDef result = HAL_TIM_Base_Start_IT(&htim1);

	SendStands();
}

void LedSingleWire::Close() {
	delete buffer;
}

void LedSingleWire::SetPixel(uint16_t pixel, uint16_t strand, uint8_t r,
		uint8_t g, uint8_t b, uint8_t w) {
	if (pixel >= pixelCount || strand >= strandCount) {
		return;
	}

	uint16_t strandMask = 0x00;

	uint16_t offset = (SLOTS_PER_BIT * bytesPerPixel * 8 * pixel) + LEAD_IN;

	switch (strand) {
	case 0:
		//Debugging - Mirror data onto LED 1
		strandMask = LED_0_Pin ;//| LED_1_Pin;
		break;
	default:
		//Strand is not configured
		return;
	}

	uint32_t data = 0;

	switch (format) {
	case RGBW:
		data = r << 24 | g << 16 | b << 8 | w;
		break;
	case GRBW:
		data = g << 24 | r << 16 | b << 8 | w;
		break;
	}

	for (int8_t bit = 31; bit >= 0; bit--) {
		buffer[offset] = buffer[offset] | strandMask;
		offset++;
		if (data & (0x01 << bit)) {
			buffer[offset] = buffer[offset] | strandMask;
			offset++;
		} else {
			buffer[offset] = buffer[offset] & ~strandMask;
			offset++;
		}
		buffer[offset] = buffer[offset] & ~strandMask;
		offset++;
		buffer[offset] = buffer[offset] & ~strandMask;
		offset++;
	}
}

void LedSingleWire::SwapBuffer() {
	SendStands();
}

uint16_t counter = 0;

void LedSingleWire::SendStands() {
	//Reset signal
	LED_CLK_GPIO_Port->ODR = 0x00;

	htim3.Instance->EGR = TIM_EGR_UG;
	
	//Stop/reset the timer
	HAL_TIM_Base_Stop_IT(&htim3);

	HAL_StatusTypeDef result = HAL_TIM_Base_Start_IT(&htim3);

	if(result == HAL_ERROR) {
		//We're unable to start the reset timer.
		counter = 0xFFFF;
	} else {
		counter = 0;
	}
}

void LedSingleWire::StartNextDma() {
	counter++;
	//14 is 300nS
	htim1.Instance->ARR = 30;	//17;//18
	htim1.Instance->EGR = TIM_EGR_UG;

	HAL_DMA_Start_IT(&hdma_tim1_ch1, (uint32_t) buffer,
			(uint32_t) &(LED_CLK_GPIO_Port->ODR), bufferLength);
}

