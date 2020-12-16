/*
 * matrix_driver.cpp
 *
 *  Created on: Oct 9, 2020
 *      Author: benvh
 */

#include "main.h"
#include "DisplayDriver.h"
#include <stdio.h>
#include <string.h>
#include "MatrixDriver.h"

#define SET_IF(cond, x) (cond ? x : 0)
#define RESET_SHIFT(x) (x << 16)
#define BSRR_IF(cond, x) (cond ? x : RESET_SHIFT(x))

#define LINE_MASK (SET_SHIFT(A_SHIFT) | SET_SHIFT(B_SHIFT) | SET_SHIFT(C_SHIFT) | SET_SHIFT(D_SHIFT) | SET_SHIFT(E_SHIFT) )

#define PLANES 4
#define CYCLES_PER_PIXEL 2
#define ROW_END_CYCLES 4

static MatrixDriver *instance;

extern UART_HandleTypeDef huart1;

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

void DMA_Error(DMA_HandleTypeDef *hdma) {
#ifdef DEBUG_LOGGING
	sprintf(buffer, "DE - %d %d\n", hdma_tim1_ch1.State,
			hdma_tim1_ch1.ErrorCode);
#endif

	HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 10);
}


//Memory Layout:
// Plane - plane * planeSize
// -- Row - y % (height / 2) - Top and bottom half of the panel are in the same output cycle
// ---- Pixel - 0 and 1 data lines, select lines for previously sent row (to keep it displaying while new data is clocked in to the shift registers)
// ------ Offset - Set data
// ------ Offset + 1 - Clock data
// ---- OE & Latch
uint16_t MatrixDriver::BufferOffset(uint16_t x, uint16_t y, uint8_t plane) {
	uint16_t rowEntry = y % (height / 2);
	uint16_t rowOffset = rowEntry
			* ((width * CYCLES_PER_PIXEL) + ROW_END_CYCLES);
	uint16_t offsetInRow = ((width - 1) - x) * CYCLES_PER_PIXEL;

	return (plane * planeSize) + rowOffset + offsetInRow;
}

#define MIN(a,b) (((a)<(b))?(a):(b))

MatrixDriver::MatrixDriver(uint16_t width, uint16_t height, ScanType scanType) {
	this->width = width;
	this->height = height;
	this->scanType = scanType;
	this->planes = PLANES;

	this->planeSize = ((width * CYCLES_PER_PIXEL) + ROW_END_CYCLES)
			* (height / 2);
	this->bufferSize = planeSize * planes;

	this->sendBufferA = true;

	instance = this;
}

void MatrixDriver::Open() {
	this->bufferA = new uint16_t[bufferSize];
	this->bufferB = new uint16_t[bufferSize];

	for (uint8_t y = 0; y < height / 2; y++) {

		uint8_t previousRow = y == 0 ? (height / 2) - 1 : y - 1;

		uint16_t rowSelects =
		SET_IF(previousRow & 0x01,
				Matrix_A_Pin) |SET_IF(previousRow & 0x02, Matrix_B_Pin)
				|SET_IF(previousRow & 0x04, Matrix_C_Pin)
				|SET_IF(previousRow & 0x08, Matrix_D_Pin)
				|SET_IF(previousRow & 0x10, Matrix_E_Pin);

		for (uint8_t plane = 0; plane < planes; plane++) {
			for (uint8_t x = 0; x < width; x++) {

				uint16_t offset = BufferOffset(x, y, plane);

				bufferA[offset] = rowSelects;
				bufferB[offset] = rowSelects;
				bufferA[offset + 1] = rowSelects | Matrix_CLK_Pin;
				bufferB[offset + 1] = rowSelects | Matrix_CLK_Pin;
			}

			//Setup the final bytes for the row, staring with the output after the last pixel on the current row & plane
			//Disable outputs
			uint16_t offset = BufferOffset(0, y,
					plane) + CYCLES_PER_PIXEL;

			bufferA[offset] = bufferB[offset] = Matrix_OE_Pin | rowSelects;
			offset++;

			uint16_t currentRowSelects =
			SET_IF(y & 0x01, Matrix_A_Pin) |SET_IF(y & 0x02, Matrix_B_Pin)
			|SET_IF(y & 0x04, Matrix_C_Pin)
			|SET_IF(y & 0x08, Matrix_D_Pin)
			|SET_IF(y & 0x10, Matrix_E_Pin);

			//Latch data, select next row, outputs still off
			bufferA[offset] = bufferB[offset] = Matrix_LAT_Pin | Matrix_OE_Pin
					| currentRowSelects;

			offset++;
			bufferA[offset] = bufferB[offset] = currentRowSelects;

			//Bonus cycle to settle.  Probably not necessary but 3 trailing cycles feels odd
			offset++;
			bufferA[offset] = bufferB[offset] = currentRowSelects;
		}
	}

	sprintf(buffer, "CFG: %ux%u Buffers: %u Planes: %u@%u \n", width, height,
			bufferSize, planes, planeSize);

	HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 10);

	hdma_tim1_ch1.XferAbortCallback = DMA_Abort;
	hdma_tim1_ch1.XferCpltCallback = DMA_Complete;
	hdma_tim1_ch1.XferErrorCallback = DMA_Error;

	__HAL_TIM_ENABLE_DMA(&htim1, TIM_DMA_CC1);

	TIM_CCxChannelCmd(htim1.Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);

	HAL_TIM_Base_Start_IT(&htim1);

	nextDmaOffset = 0;

	StartNextDma();
}

void MatrixDriver::Close() {
	HAL_DMA_Abort_IT(&hdma_tim1_ch1);

	HAL_TIM_Base_Stop_IT(&htim1);

	nextDmaOffset = 0;

	delete this->bufferA;
	delete this->bufferB;
}

uint8_t gamma8[256] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

uint8_t MatrixDriver::PlaneBits(uint8_t value) {
	value = gamma8[value];

#if PLANES == 8
	return value;
#elif PLANES == 4
	uint8_t result = 0;

	if(value > 128) {
		result |= 0x08;
		value -=128;
	}

	if(value > 64) {
		result |= 0x03;
		value -=128;
	}

	if(value > 32) {
		result |= 0x02;
		value -=128;
	}

	if(value > 8) {
		result |= 0x01;
	}

	return result;
#elif PLANES == 2
	uint8_t result =
			(value > 128 ? 0x02 : 0x00) |
			(value > 0 ? 0x01 : 0x00) ;

	return result;
#elif PLANES == 1
	return value > 0 ? 0x01 : 0x00;
#endif
}

void MatrixDriver::Dump() {
	uint16_t *outputBuffer = sendBufferA ? bufferB : bufferA;

	for (uint16_t offset = 14784; offset < bufferSize; offset++) {
		uint16_t val = outputBuffer[offset];

//		if (val & Matrix_LAT_Pin || val & Matrix_OE_Pin) {
		uint8_t r0, g0, b0, r1, g1, b1, a, b, c, d, lat, oe, clk;

		r0 = (val & Matrix_R0_Pin) > 0;
		g0 = (val & Matrix_G0_Pin) > 0;
		b0 = (val & Matrix_B0_Pin) > 0;

		r1 = (val & Matrix_R1_Pin) > 0;
		g1 = (val & Matrix_G1_Pin) > 0;
		b1 = (val & Matrix_B1_Pin) > 0;

		a = (val & Matrix_A_Pin) > 0;
		b = (val & Matrix_B_Pin) > 0;
		c = (val & Matrix_C_Pin) > 0;
		d = (val & Matrix_D_Pin) > 0;

		lat = (val & Matrix_LAT_Pin) > 0;
		oe = (val & Matrix_OE_Pin) > 0;
		clk = (val & Matrix_CLK_Pin) > 0;

		uint8_t rowVal = a | b << 1 | c << 2 | d << 3;

		if (r0 != 0) {

			sprintf(buffer,
					"%04u : %04x - %x %x %x - %x %x %x @ %x %x %x %x - %d - %u - %u - %u\n",
					offset, val, r0, g0, b0, r1, g1, b1, a, b, c, d, rowVal,
					lat, oe, clk);

			HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 50);
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

void MatrixDriver::SetPixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
	uint16_t rBit, gBit, bBit;

//Set data into the buffer we aren't sending at the moment
	uint16_t *outputBuffer = sendBufferA ? bufferB : bufferA;

	if (y < (height / 2)) {
		rBit = Matrix_R0_Pin;
		gBit = Matrix_G0_Pin;
		bBit = Matrix_B0_Pin;
	} else {
		rBit = Matrix_R1_Pin;
		gBit = Matrix_G1_Pin;
		bBit = Matrix_B1_Pin;
	}

	uint16_t pixelMask = rBit | gBit | bBit;

	uint8_t rPlanes = PlaneBits(r);
	uint8_t gPlanes = PlaneBits(g);
	uint8_t bPlanes = PlaneBits(b);

#ifdef DEBUG_LOGGING
	sprintf(buffer,
			"%02u, %02u : %02x %02x %02x %04x\n",
			x, y, rPlanes, gPlanes, bPlanes, pixelMask);

	HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer),
			10);
#endif

	for (int plane = 0; plane < planes; plane++) {
		uint16_t planePixelBits = ((rPlanes & (0x01 << plane)) ? rBit : 0)
				| ((gPlanes & (0x01 << plane)) ? gBit : 0)
				| ((bPlanes & (0x01 << plane)) ? bBit : 0);

		uint16_t offset = BufferOffset(x, y, plane);

		outputBuffer[offset] = (outputBuffer[offset] & ~pixelMask)
				| planePixelBits;
		outputBuffer[offset + 1] = (outputBuffer[offset + 1] & ~pixelMask)
				| planePixelBits;
	}
}

void MatrixDriver::SwapBuffer() {
	completeSwap = true;

	HAL_DMA_Abort_IT(&hdma_tim1_ch1);
}

void MatrixDriver::Handle() {
	bool cloneBuffer = completeSwap;

	if (completeSwap) {
		completeSwap = false;
		sendBufferA = !sendBufferA;
		nextDmaOffset = 0;
	}

	StartNextDma();

//	if (cloneBuffer) {
//		uint16_t *outputBuffer = (sendBufferA ? bufferA : bufferB);
//		uint16_t *targetBuffer = (!sendBufferA ? bufferA : bufferB);
//
//		memcpy(targetBuffer, outputBuffer, bufferSize * 2);
//	}

}

#if PLANES == 8
uint8_t const AAR_BY_PLANE[] = { 1, 2, 4, 8, 16, 32, 64 };
#elif PLANES == 4
uint8_t const AAR_BY_PLANE[] = { 1, 8, 16, 28 };
#endif

void MatrixDriver::StartNextDma() {
	uint16_t plane = nextDmaOffset / planeSize;
	uint16_t *outputBuffer = (sendBufferA ? bufferA : bufferB);
	uint16_t *ouputOffset = outputBuffer + (plane * planeSize);

	htim1.Instance->ARR = AAR_BY_PLANE[plane];
	htim1.Instance->EGR = TIM_EGR_UG;

#ifdef DEBUG_LOGGING
	if (hdma_tim1_ch1.State != HAL_DMA_STATE_READY) {
		sprintf(buffer, "DS - %d %l\n", hdma_tim1_ch1.State,
				hdma_tim1_ch1.ErrorCode);

		HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 10);
	}
#endif

	HAL_DMA_Start_IT(&hdma_tim1_ch1, (uint32_t) ouputOffset,
			(uint32_t) &(GPIOB->ODR), planeSize);

	nextDmaOffset += planeSize;

	if (nextDmaOffset >= bufferSize) {
		nextDmaOffset = 0;
	}

#ifdef DebugPin_GPIO_Port
	HAL_GPIO_WritePin(DebugPin_GPIO_Port, DebugPin_Pin,
			plane & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
#endif
}

