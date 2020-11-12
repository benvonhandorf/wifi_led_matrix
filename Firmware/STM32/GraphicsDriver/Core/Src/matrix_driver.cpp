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
#define B0_SHIFT 14
#define R1_SHIFT 3
#define G1_SHIFT 4
#define B1_SHIFT 5

#define A_SHIFT 6
#define B_SHIFT 7
#define C_SHIFT 8
#define D_SHIFT 9
#define E_SHIFT 10

#define OE_SHIFT 11

#define LAT_SHIFT 12

#define CLK_SHIFT 13

#define SET_SHIFT(x) (0x0001 << x)
#define SET_IF(cond, x) (cond ? SET_SHIFT(x) : 0)
#define RESET_SHIFT(x) (0x0001 << (x + 16))
#define BSRR_IF(cond, x) (cond ? SET_SHIFT(x) : RESET_SHIFT(x))

#define LINE_MASK (SET_SHIFT(A_SHIFT) | SET_SHIFT(B_SHIFT) | SET_SHIFT(C_SHIFT) | SET_SHIFT(D_SHIFT) | SET_SHIFT(E_SHIFT) )

#define CYCLES_PER_PIXEL 2
#define ROW_END_CYCLES 4

static MatrixDriver *instance;

extern UART_HandleTypeDef huart1;

extern IWDG_HandleTypeDef hiwdg;

extern TIM_HandleTypeDef htim1;
extern DMA_HandleTypeDef hdma_tim1_ch1;

uint32_t cycles = 0;
extern char buffer[1024];
uint32_t latchTicks = 0;

//void DMA_HalfComplete(DMA_HandleTypeDef *hdma) {
////	HAL_UART_Transmit(&huart1, (uint8_t*) "Half\n", 5, 10);
//}

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//	if (htim == &htim1) {
//		instance->handleNeeded = true;
//		instance->Handle();
//	}
//}

void DMA_Complete(DMA_HandleTypeDef *hdma) {
	instance->Handle();
}

void DMA_Abort(DMA_HandleTypeDef *hdma) {
	instance->Handle();
}

uint16_t MatrixDriver::BufferOffset(uint8_t x, uint8_t y, uint8_t plane) {
	return (plane * planeSize)
			+ ((y % (height / 2)) * ((width * CYCLES_PER_PIXEL) + ROW_END_CYCLES))
			+ (x * CYCLES_PER_PIXEL);
}

#define MIN(a,b) (((a)<(b))?(a):(b))

MatrixDriver::MatrixDriver(uint8_t width, uint8_t height, ScanType scanType) {
	this->width = width;
	this->height = height;
	this->scanType = scanType;
	this->planes = 1;

	this->planeSize = ((width * CYCLES_PER_PIXEL) * (height / 2))
			+ ROW_END_CYCLES;
	this->bufferSize = planeSize * planes;

	this->sendBufferA = true;
	this->bufferA = new uint16_t[bufferSize];
	this->bufferB = new uint16_t[bufferSize];

	for (uint8_t y = 0; y < height / 2; y++) {

		uint8_t previousRow = y == 0 ? (height / 2) - 1 : y - 1;

		uint16_t rowSelects = SET_IF(previousRow & 0x01,
				A_SHIFT) |SET_IF(previousRow & 0x02, B_SHIFT)
				|SET_IF(previousRow & 0x04, C_SHIFT)
				|SET_IF(previousRow & 0x08, D_SHIFT)
				|SET_IF(previousRow & 0x10, E_SHIFT);

		for (uint8_t plane = 0; plane < planes; plane++) {
			for (uint8_t x = 0; x < width; x++) {

				uint16_t offset = BufferOffset(x, y, plane);

				bufferA[offset] = bufferB[offset] = rowSelects;
				bufferA[offset + 1] = bufferB[offset + 1] = rowSelects
						| SET_SHIFT(CLK_SHIFT);
			}

			//Setup the final bytes for the row, staring with the output after the last pixel on the current row & plane
			//Disable outputs
			uint16_t offset = BufferOffset(width - 1, y,
					plane) + CYCLES_PER_PIXEL;
			bufferA[offset] = bufferB[offset] = SET_SHIFT(OE_SHIFT)
					| rowSelects;
			offset++;

			uint16_t currentRowSelects = SET_IF(y & 0x01,
					A_SHIFT) |SET_IF(y & 0x02, B_SHIFT)
					|SET_IF(y & 0x04, C_SHIFT)
					|SET_IF(y & 0x08, D_SHIFT)
					|SET_IF(y & 0x10, E_SHIFT);

			//Latch data, select next row, outputs still off
			bufferA[offset] = bufferB[offset] = SET_SHIFT(LAT_SHIFT)
					| SET_SHIFT(OE_SHIFT) | currentRowSelects;

			offset++;
			bufferA[offset] = bufferB[offset] = currentRowSelects;

			//Bonus cycle to settle.  Probably not necessary but 3 trailing cycles feels odd
			offset++;
			bufferA[offset] = bufferB[offset] = currentRowSelects;
		}
	}

	instance = this;
}

void MatrixDriver::open() {
	sprintf(buffer, "CFG: %ux%u Buffers: %u Planes: %u@%u \n", width, height,
			bufferSize, planes, planeSize);

	HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 10);

	hdma_tim1_ch1.XferAbortCallback = DMA_Abort;
	hdma_tim1_ch1.XferCpltCallback = DMA_Complete;

	__HAL_TIM_ENABLE_DMA(&htim1, TIM_DMA_CC1);

	TIM_CCxChannelCmd(htim1.Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);

	HAL_TIM_Base_Start_IT(&htim1);

	nextDmaOffset = 0;

	StartNextDma();

	__HAL_IWDG_START(&hiwdg);
}

void MatrixDriver::close() {
	HAL_DMA_Abort_IT(&hdma_tim1_ch1);

	HAL_TIM_Base_Stop_IT(&htim1);

	nextDmaOffset = 0;
}

uint8_t MatrixDriver::PlaneBits(uint8_t value) {
	uint8_t result = 0x00;

	if (value > 127) {
		result |= 0x08;
		value -= 127;
	}

	if (value > 64) {
		result |= 0x04;
		value -= 32;
	}

	if (value > 32) {
		result |= 0x02;
		value -= 8;
	}

	if (value > 16) {
		result |= 0x01;
		value -= 16;
	}

	return result;
}

void MatrixDriver::Dump() {
	uint16_t *outputBuffer = sendBufferA ? bufferB : bufferA;

	for (uint16_t offset = 0; offset < bufferSize; offset++) {
		uint16_t val = outputBuffer[offset];

		if (val & SET_SHIFT(LAT_SHIFT) || val & SET_SHIFT(OE_SHIFT)) {
			uint8_t r0, g0, b0, r1, g1, b1, a, b, c, d, lat, oe, clk;

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

			lat = (val & SET_SHIFT(LAT_SHIFT)) > 0;
			oe = (val & SET_SHIFT(OE_SHIFT)) > 0;
			clk = (val & SET_SHIFT(CLK_SHIFT)) > 0;

			uint8_t rowVal = a | b << 1 | c << 2 | d << 3;

			sprintf(buffer,
					"%04u : %02x - %x %x %x - %x %x %x @ %x %x %x %x - %d - %u - %u - %u\n",
					offset, val, r0, g0, b0, r1, g1, b1, a, b, c, d,
					rowVal, lat, oe, clk);

			HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 10);
		}

	}

//	for (uint8_t y = 0; y < height / 2; y++) {
//		for (uint8_t x = 0; x < width; x++) {
//			for (uint8_t plane = 0; plane < planes; plane++) {
//				uint16_t offset = BufferOffset(x, y, plane);
//
//				for (uint8_t entry = 0; entry <= 1; entry++) {
//					uint16_t val = outputBuffer[offset + entry];
//
//					uint8_t r0, g0, b0, r1, g1, b1, a, b, c, d, lat, oe, clk;
//
//					r0 = (val & (0x0001 << R0_SHIFT)) > 0;
//					g0 = (val & (0x0001 << G0_SHIFT)) > 0;
//					b0 = (val & (0x0001 << B0_SHIFT)) > 0;
//
//					r1 = (val & (0x0001 << R1_SHIFT)) > 0;
//					g1 = (val & (0x0001 << G1_SHIFT)) > 0;
//					b1 = (val & (0x0001 << B1_SHIFT)) > 0;
//
//					a = (val & (0x0001 << A_SHIFT)) > 0;
//					b = (val & (0x0001 << B_SHIFT)) > 0;
//					c = (val & (0x0001 << C_SHIFT)) > 0;
//					d = (val & (0x0001 << D_SHIFT)) > 0;
//
//					lat = (val & SET_SHIFT(LAT_SHIFT)) > 0;
//							oe = (val & SET_SHIFT(OE_SHIFT)) > 0;
//							clk = (val & SET_SHIFT(CLK_SHIFT)) > 0;
//
//					uint8_t rowVal = a | b << 1 | c << 2 | d << 3;
//
//					sprintf(buffer,
//							"%02u, %02u @ %u - %u: %02x - %x %x %x - %x %x %x @ %x %x %x %x - %d - %u - %u - %u\n",
//							x, y, plane, entry, val, r0, g0, b0, r1, g1, b1, a, b, c,
//							d, rowVal, lat, oe, clk);
//
//					HAL_UART_Transmit(&huart1, (uint8_t*) buffer,
//							strlen(buffer), 10);
//				}
//			}
//
//		}
//	}
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
				(rPlanes & (0x01 << plane)) ? SET_SHIFT(rShift) : 0)
				| ((gPlanes & (0x01 << plane)) ? SET_SHIFT(gShift) : 0)
				| ((bPlanes & (0x01 << plane)) ? SET_SHIFT(bShift) : 0);

//		sprintf(buffer,
//				"%02u, %02u : %02x %02x %02x %04x %04x\n",
//				x, y, rPlanes, gPlanes, bPlanes, planePixelBits, pixelMask);

//		HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer),
//				10);

		uint16_t offset = BufferOffset(x, y, plane);

		outputBuffer[offset] = (outputBuffer[offset] & ~pixelMask)
				| planePixelBits;
		outputBuffer[offset + 1] = (outputBuffer[offset + 1] & ~pixelMask)
				| planePixelBits;
	}
}

void MatrixDriver::SwapBuffer() {
	sendBufferA = !sendBufferA;

	completeSwap = true;

	HAL_DMA_Abort_IT(&hdma_tim1_ch1);
}

void MatrixDriver::Handle() {
	HAL_IWDG_Refresh(&hiwdg);

	if (completeSwap) {
		completeSwap = false;
	}

	StartNextDma();
}

uint8_t const AAR_BY_PLANE[] = { 1, 2, 4, 8, 16, 32, 64 };

void MatrixDriver::StartNextDma() {
	uint16_t plane = nextDmaOffset / planeSize;
	uint16_t *outputBuffer = (sendBufferA ? bufferA : bufferB);

	htim1.Instance->ARR = AAR_BY_PLANE[plane];
	htim1.Instance->EGR = TIM_EGR_UG;

	HAL_DMA_Start_IT(&hdma_tim1_ch1, (uint32_t) outputBuffer,
			(uint32_t) &(GPIOB->ODR), planeSize);

	nextDmaOffset += planeSize;

	if (nextDmaOffset > bufferSize) {
		nextDmaOffset = 0;
	}
}

