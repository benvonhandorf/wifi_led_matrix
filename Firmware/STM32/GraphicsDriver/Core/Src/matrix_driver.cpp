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
#define B0_SHIFT 2
#define R1_SHIFT 3
#define G1_SHIFT 4
#define B1_SHIFT 5

#define M1_R0_SHIFT 6
#define M1_G0_SHIFT 7
#define M1_B0_SHIFT 8
#define M1_R1_SHIFT 9
#define M1_G1_SHIFT 10
#define M1_B1_SHIFT	11

//LAT lives on PA11
#define LAT_SHIFT 11

//OE lives on PA12
#define OE_SHIFT 12

//CLK lives on PA1

//Select lines on PA
#define A_SHIFT 2
#define B_SHIFT 3
#define C_SHIFT 4
#define D_SHIFT 8
#define E_SHIFT 15

//CLK moves to A0 to allow PWM output of the clock

#define SET_SHIFT(x) (0x0001 << x)
#define RESET_SHIFT(x) (0x0001 << (x + 16))
#define BSRR_IF(cond, x) (cond ? SET_SHIFT(x) : RESET_SHIFT(x))

#define LINE_MASK (SET_SHIFT(A_SHIFT) | SET_SHIFT(B_SHIFT) | SET_SHIFT(C_SHIFT) | SET_SHIFT(D_SHIFT) | SET_SHIFT(E_SHIFT) )

static MatrixDriver *instance;

extern UART_HandleTypeDef huart1;

extern IWDG_HandleTypeDef hiwdg;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim1;
extern DMA_HandleTypeDef hdma_tim2_ch1;

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
	instance->handleNeeded = true;

	instance->Handle();
}

uint16_t MatrixDriver::BufferOffset(uint8_t x, uint8_t y, uint8_t plane) {
	return (plane * planeSize) + ((y % (height / 2)) * width) + x;
}

#define MIN(a,b) (((a)<(b))?(a):(b))

MatrixDriver::MatrixDriver(uint8_t width, uint8_t height, ScanType scanType) {
	this->width = width;
	this->height = height;
	this->scanType = scanType;
	this->planes = 4;

	this->planeSize = width * (height / 2);
	this->bufferSize = planeSize * planes;

	this->sendBufferA = true;
	this->bufferA = new uint16_t[bufferSize];
	this->bufferB = new uint16_t[bufferSize];

	for (uint8_t y = 0; y < height / 2; y++) {

		for (uint8_t plane = 0; plane < planes; plane++) {
			for (uint8_t x = 0; x < width; x++) {

				uint16_t offset = BufferOffset(x, y, plane);

				bufferA[offset] = 0x00;
				bufferB[offset] = 0x00;
			}
		}
	}

	//DMA must complete at the end of a row to allow
	//an opportunity to latch the data but it cannot exceed
	//32 DMA operations due to the TIM1 RCR being limited to a uint8_t
	//and an effective 7 RCR / operation.
	//RCR = (OPS * 7) - 1
	maxDmaOperations = MIN(32, width);

	instance = this;
}

void MatrixDriver::open() {
	sprintf(buffer, "CFG: %ux%u Buffers: %u Planes: %u@%u \n", width, height, bufferSize, planes, planeSize);

	HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 10);

	hdma_tim2_ch1.XferCpltCallback = DMA_Complete;

	HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);

	HAL_NVIC_EnableIRQ(TIM2_IRQn);

	__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_UPDATE);

	__HAL_TIM_ENABLE_DMA(&htim2, TIM_DMA_CC1);

	TIM_CCxChannelCmd(htim2.Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);
	TIM_CCxChannelCmd(htim2.Instance, TIM_CHANNEL_2, TIM_CCx_ENABLE);

	HAL_TIM_Base_Start(&htim2);

	TIM_CCxChannelCmd(htim1.Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);

	nextDmaOffset = 0;

	StartNextDma();
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
	}
}

void MatrixDriver::SwapBuffer() {
	sendBufferA = !sendBufferA;

	completeSwap = true;
}

void MatrixDriver::Handle() {
	if (handleNeeded) {
		if (!completeSwap && (nextDmaOffset % width) == 0) {
			Latch();
		} else if(completeSwap) {
			//If we're in the middle of a swap we can skip the latch
			//and simply start DMAing out the first part of the buffer
			completeSwap = false;
			nextDmaOffset = 0;
		}

		StartNextDma();

		handleNeeded = false;
	}
}

uint8_t const AAR_BY_PLANE[4] = { 1, 2, 4, 8 };

void MatrixDriver::StartNextDma() {
	uint16_t *outputBuffer = sendBufferA ? bufferA : bufferB;
	outputBuffer += nextDmaOffset;

	uint32_t operations = MIN(maxDmaOperations, bufferSize - nextDmaOffset);

	HAL_DMA_Start_IT(&hdma_tim2_ch1, (uint32_t) outputBuffer,
			(uint32_t) &(GPIOB->ODR), operations);

	//Number of TIM1 ticks to drive data_size elements.
	uint8_t rcr = (operations * 8) - 1;

	uint8_t plane = nextDmaOffset / planeSize;

	htim1.Instance->ARR = AAR_BY_PLANE[plane];
	htim1.Instance->RCR = rcr;
	htim1.Instance->EGR = TIM_EGR_UG; //Generate an update event to absorb RCR
	htim2.Instance->CNT = 0;

	HAL_TIM_Base_Stop(&htim1);

	HAL_TIM_Base_Start_IT(&htim1);

	nextDmaOffset += operations;

	if (nextDmaOffset >= bufferSize) {
		nextDmaOffset = 0;
	}
}

//uint32_t bsrr = 0x00;
//uint32_t lastOffset = 0x00;

void MatrixDriver::Latch() {
	HAL_IWDG_Refresh(&hiwdg);

	uint16_t row = (nextDmaOffset % planeSize) / width;

	uint8_t previousRow = row == 0 ? (height / 2) - 1 : row - 1;

//	uint32_t odra = GPIOA->ODR;
//
//	int32_t delta = nextDmaOffset - lastOffset;
//
//	if(delta != 64) {
//		uint32_t now = HAL_GetTick();
//
//		uint32_t duration = now - latchTicks;
//
//		sprintf(buffer, "LAT: %lu - %u %u %04lx vs %04lx - %d %d\n", duration, row, previousRow, bsrr & LINE_MASK, odra & LINE_MASK, nextDmaOffset, lastOffset);
//
//		HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 10);
//
//		latchTicks = HAL_GetTick();
//	}

//	lastOffset = nextDmaOffset;

	//Set or reset each specific line for selection
	uint32_t bsrr = BSRR_IF(previousRow & 0x01, A_SHIFT) |
					BSRR_IF(previousRow & 0x02, B_SHIFT) |
					BSRR_IF(previousRow & 0x04, C_SHIFT) |
					BSRR_IF(previousRow & 0x08, D_SHIFT) |
					BSRR_IF(previousRow & 0x10, E_SHIFT);

	//Disable output & latch
	GPIOA->BSRR = SET_SHIFT(OE_SHIFT);

	GPIOA->BSRR = SET_SHIFT(LAT_SHIFT);

	GPIOA->BSRR = RESET_SHIFT(LAT_SHIFT);
	//Configure row lines
	GPIOA->BSRR = bsrr;

	//Enable output
	GPIOA->BSRR = RESET_SHIFT(OE_SHIFT);
}
