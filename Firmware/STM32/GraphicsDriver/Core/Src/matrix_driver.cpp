/*
 * matrix_driver.cpp
 *
 *  Created on: Oct 9, 2020
 *      Author: benvh
 */

#include "main.h"
#include "matrix_driver.h"
#include <stdio.h>
#include <string.h>

#define R0_SHIFT 0
#define G0_SHIFT 1
#define B0_SHIFT 15
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

extern IWDG_HandleTypeDef hiwdg;

extern DMA_HandleTypeDef hdma_memtomem_dma1_channel3;

uint32_t cycles = 0;
extern char buffer[1024];
uint32_t latchTicks = 0;

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim) {
	//This will trigger DMA eventually
	instance->SendPlanePixel();
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	//This will trigger clock pulse
	instance->Clock();
}

void DMA_HalfComplete(DMA_HandleTypeDef *hdma) {
	HAL_UART_Transmit(&huart1, (uint8_t*) "Half\n", 5, 10);
}

void DMA_Complete(DMA_HandleTypeDef *hdma) {
	instance->Send();
}

uint16_t MatrixDriver::BufferOffset(uint8_t x, uint8_t y, uint8_t plane) {
	//TODO: Take plane into account for offset
	return ((y % (height / 2))  * width) + x;
}

MatrixDriver::MatrixDriver(uint8_t width, uint8_t height, ScanType scanType,
		TIM_HandleTypeDef *htim) {
	this->htim = htim;

	this->width = width;
	this->height = height;
	this->scanType = scanType;
	this->planes = 1;

	this->bufferSize = (width * (height / 2) * planes);

	this->sendBufferA = true;
	this->bufferA = new uint16_t[bufferSize];
	this->bufferB = new uint16_t[bufferSize];

	for (uint8_t y = 0; y < height / 2; y++) {
		uint8_t previousRow = y == 0 ? (height / 2) - 1 : y;

		uint16_t rowLines = (previousRow & 0x01 ? 0x0001 << A_SHIFT : 0)
				| (previousRow & 0x02 ? 0x0001 << B_SHIFT : 0)
				| (previousRow & 0x04 ? 0x0001 << C_SHIFT : 0)
				| (previousRow & 0x08 ? 0x0001 << D_SHIFT : 0);

		for (uint8_t x = 0; x < width; x++) {
			for (uint8_t plane = 0; plane < planes; plane++) {
				uint16_t offset = BufferOffset(x, y, plane);

				bufferA[offset] = rowLines;
				bufferB[offset] = rowLines;
			}
		}
	}

	instance = this;

	hdma_memtomem_dma1_channel3.XferHalfCpltCallback = DMA_HalfComplete;
	hdma_memtomem_dma1_channel3.XferCpltCallback = DMA_Complete;
}

void MatrixDriver::open() {
	Send();

	__HAL_TIM_ENABLE_IT(htim, TIM_IT_CC4);

//	__HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC4);

	HAL_TIM_Base_Start_IT(htim);
}

void MatrixDriver::Send() {
	HAL_UART_Transmit(&huart1, (uint8_t*) "Send\n", 5, 10);

	uint16_t *outputBuffer = sendBufferA ? bufferA : bufferB;

	HAL_DMA_Start_IT(&hdma_memtomem_dma1_channel3, (uint32_t) outputBuffer, (uint32_t)&(GPIOB->ODR), bufferSize);
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

void MatrixDriver::Dump() {
	uint16_t *outputBuffer = sendBufferA ? bufferB : bufferA;

	for (uint8_t y = 0; y < height / 2; y++) {
		for (uint8_t x = 0; x < width; x++) {
			for (uint8_t plane = 0; plane < planes; plane++) {
				uint16_t offset = BufferOffset(x, y, plane);

				uint16_t val = outputBuffer[offset];

				uint8_t r0, g0, b0, r1, g1, b1, a, b, c, d;

				r0 = (val & (0x0001 << R0_SHIFT)) > 0;
				g0 = (val & (0x0001 << G0_SHIFT)) > 0;
				b0 = (val & (0x0001 << B0_SHIFT)) > 0;

				r1 = (val & (0x0001 << R1_SHIFT)) > 0;
				g1 = (val & (0x0001 << G1_SHIFT)) > 0;
				b1 = (val & (0x0001 << B1_SHIFT)) > 0;

				a = (val & (0x0001 << A_SHIFT)) > 0;
				b = (val & (0x0001 << B_SHIFT)) > 0;
				c = (val & (0x0001 << C_SHIFT)) > 0;
				d = (val & (0x0001 << D_SHIFT)) > 0;

				uint8_t rowVal = a | b << 1 | c << 2 | d << 3;

				sprintf(buffer,
						"%02u, %02u @ %u: %02x - %x %x %x - %x %x %x @ %x %x %x %x - %d\n",
						x, y, plane, val, r0, g0, b0, r1, g1, b1, a, b, c, d,
						rowVal);

				HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer),
						10);
			}

		}
	}
}

void MatrixDriver::SetPixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g,
		uint8_t b) {
	uint8_t rShift, gShift, bShift;

	//Set data into the buffer we aren't sending at the moment
	uint16_t *outputBuffer = sendBufferA ? bufferB : bufferA;

	if (y < (height / 2)) {
		rShift = R0_SHIFT;
		gShift = G0_SHIFT;
		bShift = B0_SHIFT;
	} else {
		rShift = R1_SHIFT;
		gShift = G1_SHIFT;
		bShift = B1_SHIFT;
	}

	uint16_t pixelMask = (0x0001 << rShift) | (0x0001 << gShift)
			| (0x0001 << bShift);
	uint8_t rPlanes = PlaneBits(r);
	uint8_t gPlanes = PlaneBits(g);
	uint8_t bPlanes = PlaneBits(b);

	for (int plane = 0; plane < planes; plane++) {
		uint16_t planePixelBits = (
				(rPlanes & (0x01 << plane)) ? 0x0001 << rShift : 0)
				| ((gPlanes & (0x01 << plane)) ? 0x0001 << gShift : 0)
				| ((bPlanes & (0x01 << plane)) ? 0x0001 << bShift : 0);

//		sprintf(buffer,
//				"%02u, %02u : %02x %02x %02x %04x %04x\n",
//				x, y, rPlanes, gPlanes, bPlanes, planePixelBits, pixelMask);

//		HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer),
//				10);

		uint16_t offset = BufferOffset(x, y, plane);

		outputBuffer[offset] = (outputBuffer[offset] & ~pixelMask)
				| planePixelBits;
	}
}

void MatrixDriver::SwapBuffer() {
	sendBufferA = !sendBufferA;

	nextOffset = 0;
}

void MatrixDriver::SendPlanePixel() {
	uint16_t *outputBuffer = sendBufferA ? bufferA : bufferB;

	if ((nextOffset % (width * planes)) == 0) {
		//Latch the previous row
		Latch();
	}

	GPIOB->ODR = (uint32_t) outputBuffer[nextOffset++];

	if (nextOffset >= bufferSize) {
		nextOffset = 0;
	}
}

void MatrixDriver::Clock() {
	GPIOB->BSRR = (0x0001 << CLK_SHIFT);
	//Clock will be cleared on next output
}

void MatrixDriver::Latch() {
	uint32_t now = HAL_GetTick();

	uint32_t duration = now - latchTicks;
	latchTicks = now;

	sprintf(buffer, "LAT Duration: %lu\n", duration);

	//HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 10);

	HAL_IWDG_Refresh(&hiwdg);

	//Disable output
	GPIOB->BSRR = (0x0001 << OE_SHIFT);
	//Latch output
	GPIOB->BSRR = (0x0001 << LAT_SHIFT);
	//Reset Latch
	GPIOB->BSRR = (0x0001 << (LAT_SHIFT + 16));
	//Reset ~OE
	GPIOB->BSRR = (0x0001 << (OE_SHIFT + 16));
}
