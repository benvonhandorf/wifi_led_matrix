#include "main.h"
#include <stdio.h>
#include <string.h>

#include "matrix_driver.h"
extern IWDG_HandleTypeDef hiwdg;

extern SPI_HandleTypeDef hspi1;

extern UART_HandleTypeDef huart1;

extern DMA_HandleTypeDef hdma_memtomem_dma1_channel3;

MatrixDriver matrix(64, 32, MatrixDriver::ScanType::SCAN_16);

char buffer[1024];

extern "C" int cpp_main(void) {
	__HAL_DBGMCU_FREEZE_IWDG();

	uint32_t start = HAL_GetTick();

	uint16_t color_shift = 1;

	for (uint16_t row = 0; row < 32; row++) {
		for (uint16_t col = 0; col < 64; col++) {
			uint8_t r, g, b;

			r = ((row  + col + color_shift) % 4) == 0 ? 255 : 0;
			g = ((row + col + color_shift) % 4) == 1 ? 255 : 0;
			b = ((row + col + color_shift) % 4) == 2 ? 255 : 0;

			matrix.SetPixel(col, row, r, g, b);
		}
	}

	color_shift++;

//	matrix.Dump();

	matrix.SwapBuffer();

	uint32_t duration = HAL_GetTick() - start;

	sprintf(buffer, "Setup Duration: %lu\n", duration);

	HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 500);

//	HAL_IWDG_Init(&hiwdg);

//	HAL_TIM_OC_Start(&htim2, TIM_IT_CC1);

	matrix.open();

	while (1) {

//		for (uint16_t row = 0; row < 32; row++) {
//			for (uint16_t col = 0; col < 64; col++) {
//				uint8_t r, g, b;
//
//				r = ((row  + col + color_shift) % 3) == 0 ? 255 : 0;
//				g = ((row + col + color_shift) % 3) == 1 ? 255 : 0;
//				b = ((row + col + color_shift) % 3) == 2 ? 255 : 0;
//
//				matrix.SetPixel(col, row, r, g, b);
//			}
//		}
//
//		matrix.SwapBuffer();
//
//		color_shift++;
//
//		HAL_Delay(100);
	}
}
