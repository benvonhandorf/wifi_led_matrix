/*
 * matrix_driver.cpp
 *
 *  Created on: Oct 9, 2020
 *      Author: benvh
 */

#include "main.h"
#include "matrix_driver.h"

#define R0_SHIFT 0
#define G0_SHIFT 1
#define B0_SHIFT 2
#define R1_SHIFT 8
#define G1_SHIFT 9
#define B1_SHIFT 10

#define A_SHIFT 3
#define B_SHIFT 4
#define C_SHIFT 5
#define D_SHIFT 6
#define E_SHIFT 7

#define CLK_SHIFT 11
#define LAT_SHIFT 12
#define OE_SHIFT 13

static MatrixDriver *instance;

extern UART_HandleTypeDef huart1;

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim) {
	HAL_UART_Transmit(&huart1, (uint8_t *) "TX\n", 3, 10);

	//This will trigger DMA eventually
	instance->SendPlanePixel();
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	//This will trigger clock pulse
	HAL_UART_Transmit(&huart1, (uint8_t *) "CLK\n", 4, 10);

	instance->Clock();
}

uint16_t BufferOffset(uint8_t x, uint8_t y, uint8_t plane, uint8_t width, uint8_t planes) {
	//TODO: Take plane into account for offset
	return (y * width) + x;
}

MatrixDriver::MatrixDriver(uint8_t width, uint8_t height, ScanType scanType,
		TIM_HandleTypeDef *htim) {
	this->htim = htim;

	this->width = width;
	this->height = height;
	this->scanType = scanType;
	this->elementPerPlanePixel = 1;
	this->planes = 1;

	this->bufferSize = (width * (height / 2) * elementPerPlanePixel * planes);

	this->sendBufferA = true;
	this->bufferA = new uint16_t[bufferSize];
	this->bufferB = new uint16_t[bufferSize];

	for (uint8_t x = 0; x < width; x++) {
		for (uint8_t y = 0; y < height / 2; y++) {
			uint8_t previousRow = y == 0 ? (height / 2) - 1 : y;

			uint16_t rowLines =
					previousRow % 2 ? 0x0001 << A_SHIFT :
					0 | previousRow % 4 ? 0x0001 << B_SHIFT :
					0 | previousRow % 8 ? 0x0001 << C_SHIFT :
					0 | previousRow % 16 ? 0x0001 << D_SHIFT : 0;

			for (uint8_t plane = 0; plane < planes; plane++) {
				uint16_t offset = BufferOffset(x, y, plane, width, planes);

				bufferA[offset] = rowLines;
				bufferB[offset] = rowLines;
			}
		}
	}

	instance = this;
}

void MatrixDriver::open() {
	__HAL_TIM_ENABLE_IT(htim, TIM_IT_CC4);

	HAL_TIM_Base_Start_IT(htim);
}

uint8_t MatrixDriver::PlaneBits(uint8_t value) {
	uint8_t result = 0x00;

//	if (value > 127) {
//		result |= 0x08;
//		value -= 127;
//	}
//
//	if (value > 63) {
//		result |= 0x04;
//		value -= 63;
//	}
//
//	if (value > 31) {
//		result |= 0x02;
//		value -= 31;
//	}

	if (value > 1) {
		result |= 0x01;
		value -= 1;
	}

	return result;
}

void MatrixDriver::SetPixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g,
		uint8_t b) {
	uint8_t rShift, gShift, bShift;

	//Set data into the buffer we aren't sending at the moment
	uint16_t *buffer = sendBufferA ? bufferB : bufferA;

	if (y < this->height / 2) {
		rShift = R0_SHIFT;
		gShift = G0_SHIFT;
		bShift = B0_SHIFT;
	} else {
		rShift = R1_SHIFT;
		gShift = G1_SHIFT;
		bShift = B1_SHIFT;
	}

	uint16_t pixelMask = (0x01 << rShift) | (0x01 << gShift) | (0x01 << bShift);
	uint8_t rPlanes = PlaneBits(r);
	uint8_t gPlanes = PlaneBits(g);
	uint8_t bPlanes = PlaneBits(b);

	for (int plane = 0; plane < planes; plane++) {
		uint16_t planePixelBits = (
				(rPlanes & 0x01 << plane) ? 0x01 << rShift : 0)
				| ((gPlanes & 0x01 << plane) ? 0x01 << gShift : 0)
				| ((bPlanes & 0x01 << plane) ? 0x01 << bShift : 0);

		uint16_t offset = BufferOffset(x, y, plane, width, planes);

		for (int element = 0; element < elementPerPlanePixel; element++) {
			buffer[offset + element] = (buffer[offset] & ~pixelMask)
					| planePixelBits;
		}
	}
}

void MatrixDriver::SwapBuffer() {
	sendBufferA = !sendBufferA;

	nextOffset = 0;
}

void MatrixDriver::SendPlanePixel() {
	uint16_t *buffer = sendBufferA ? bufferA : bufferB;

	if((nextOffset % (width * planes)) == 0) {
		//Latch the previous row
		Latch();
	}

	GPIOB->ODR = (uint32_t) buffer[nextOffset++];
}

void MatrixDriver::Clock() {
	GPIOB->BSRR = (0x0001 << CLK_SHIFT);
	//Clock will be cleared on next output
}

void MatrixDriver::Latch() {
	HAL_UART_Transmit(&huart1, (uint8_t *) "LAT\n", 4, 10);

	//Disable output
	GPIOB->BSRR = (0x0001 << OE_SHIFT);
	//Latch output
	GPIOB->BSRR = (0x0001 << LAT_SHIFT);
	//Reset Latch
	GPIOB->BSRR = (0x0001 << (LAT_SHIFT + 16));
	//Reset ~OE
	GPIOB->BSRR = (0x0001 << (OE_SHIFT + 16));
}
