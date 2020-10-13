#include "main.h"
#include <stdio.h>
#include <string.h>

#include "matrix_driver.h"
extern IWDG_HandleTypeDef hiwdg;

extern SPI_HandleTypeDef hspi1;

extern TIM_HandleTypeDef htim3;

extern UART_HandleTypeDef huart1;

extern DMA_HandleTypeDef hdma_memtomem_dma1_channel3;

MatrixDriver matrix(128, 32, MatrixDriver::ScanType::SCAN_16, &htim3);

char buffer[1024];

extern "C" int cpp_main(void) {

//	__HAL_DBGMCU_FREEZE_IWDG();

	uint32_t start = HAL_GetTick();

	uint8_t color_shift = 1;

	for (uint8_t row = 0; row < 32; row++) {
		for (uint8_t col = 0; col < 128; col++) {
			uint8_t r, g, b;

			r = ((row + color_shift) % 3) == 0 ? 255 : 0;
			g = ((row + color_shift) % 3) == 1 ? 255 : 0;
			b = ((row + color_shift) % 3) == 2 ? 255 : 0;

			matrix.SetPixel(col, row, r, g, b);
		}
	}

	color_shift++;

	matrix.SwapBuffer();

	uint32_t duration = HAL_GetTick() - start;

	//matrix.Dump();

	sprintf(buffer, "Setup Duration: %lu\n", duration);

	HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 500);

	HAL_IWDG_Init(&hiwdg);

	matrix.open();

	while (1) {
//		for (uint8_t row = 0; row < 32; row++) {
//			for (uint8_t col = 0; col < 128; col++) {
//				uint8_t r, g, b;
//
//				r = ((row + color_shift) % 3) == 0 ? 255 : 0;
//				g = ((row + color_shift) % 3) == 1 ? 255 : 0;
//				b = ((row + color_shift) % 3) == 2 ? 255 : 0;
//
//				matrix.SetPixel(col, row, r, g, b);
//			}
//		}
//
//		color_shift++;
//
//		color_shift = color_shift % 3;
//
//		matrix.SwapBuffer();
//
//		HAL_Delay(1000);
	}
}
