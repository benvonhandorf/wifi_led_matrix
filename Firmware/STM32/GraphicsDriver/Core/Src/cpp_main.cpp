
#include "main.h"
#include <stdio.h>
#include <string.h>

#include "matrix_driver.h"

extern SPI_HandleTypeDef hspi1;

extern TIM_HandleTypeDef htim3;

extern UART_HandleTypeDef huart1;

extern DMA_HandleTypeDef hdma_memtomem_dma1_channel3;

MatrixDriver matrix(64, 32, MatrixDriver::ScanType::SCAN_16, &htim3);

char buffer[1024];

extern "C" int cpp_main(void) {

	uint32_t start = HAL_GetTick();

	//Setup some default colors for the matrix
	for (int row = 0; row < 32; row++) {
		GPIOB->ODR = (uint32_t) (0x1 << row);
		for (int col = 0; col < 64; col++) {
			matrix.SetPixel(col, row, (row + col) % 2 ? 255 : 0,
					(row + col) % 3 ? 255 : 0, (row + col) % 5 ? 255 : 0);
		}
	}

	uint32_t duration = HAL_GetTick() - start;

	sprintf(buffer, "Setup Duration: %lu\n", duration);

	HAL_UART_Transmit(&huart1, (uint8_t *)buffer, strlen(buffer), 500);

	matrix.SwapBuffer();

	matrix.open();

	while (1) {
	}
}
