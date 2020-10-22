#include "main.h"
#include <stdio.h>
#include <string.h>

#include "matrix_driver.h"

#include "image.h"

extern IWDG_HandleTypeDef hiwdg;

extern SPI_HandleTypeDef hspi1;

extern UART_HandleTypeDef huart1;

MatrixDriver matrix(64, 32, MatrixDriver::ScanType::SCAN_16);

char buffer[1024];

uint32_t lastUpdate = 0;

//1 - test pattern
//2 - advancing pixel
//3 - image
//4 - Debugging
#define DRAW 4

extern "C" int cpp_main(void) {
	__HAL_DBGMCU_FREEZE_IWDG();

	uint32_t start = HAL_GetTick();

	uint16_t color_shift = 1;

	uint16_t pos = 0;

#if DRAW == 1
	for (uint16_t col = 0; col < IMAGE_WIDTH; col++) {
		for (uint16_t row = 0; row < IMAGE_HEIGHT; row++) {

			uint8_t r, g, b;

			r = ((row + col + color_shift) % 4) == 0 ? 255 : 0;
			g = ((row + col + color_shift) % 4) == 1 ? 255 : 0;
			b = ((row + col + color_shift) % 4) == 2 ? 255 : 0;

			matrix.SetPixel(row, col, r, g, b);
		}
	}
#elif DRAW == 2
	for (uint16_t row = 0; row < 32; row++) {
		for (uint16_t col = 0; col < 64; col++) {
			uint8_t r = ((row == (pos / 64)) && (col == pos % 64)) ? 255 : 0;
			uint8_t g = ((row == (pos / 64) + 1) && (col == pos % 64)) ? 255 : 0;
			uint8_t b = ((row == (pos / 64) + 2) && (col == pos % 64)) ? 255 : 0;

			matrix.SetPixel(col, row, r, g, b);
		}
	}
#elif DRAW == 3
		for (uint16_t col = 0; col < IMAGE_WIDTH; col++) {
			for (uint16_t row = 0; row < IMAGE_HEIGHT; row++) {
				uint8_t r = IMAGE_DATA[col][row][0];
				uint8_t g = IMAGE_DATA[col][row][1];
				uint8_t b = IMAGE_DATA[col][row][2];

				matrix.SetPixel(col, row, r, g, b);
			}
		}
#elif DRAW == 4
	for (uint16_t col = 0; col < IMAGE_WIDTH; col++) {
		for (uint16_t row = 0; row < IMAGE_HEIGHT; row++) {
			uint8_t r = 0;
			uint8_t g = 0;
			uint8_t b = (col > 32) ? 255 : 0;

			matrix.SetPixel(col, row, r, g, b);
		}
	}
#endif

	lastUpdate = HAL_GetTick();

	color_shift++;

//	matrix.Dump();

	matrix.SwapBuffer();

	uint32_t duration = HAL_GetTick() - start;

	sprintf(buffer, "Setup Duration: %lu\n", duration);

	HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 500);

	matrix.open();

	while (1) {

		uint32_t now = HAL_GetTick();

		if ((now - lastUpdate) > 10) {

#if DRAW == 1
			for (uint16_t col = 0; col < IMAGE_WIDTH; col++) {
				for (uint16_t row = 0; row < IMAGE_HEIGHT; row++) {

					uint8_t r, g, b;

					r = ((row + col + color_shift) % 4) == 0 ? 255 : 0;
					g = ((row + col + color_shift) % 4) == 1 ? 255 : 0;
					b = ((row + col + color_shift) % 4) == 2 ? 255 : 0;

					matrix.SetPixel(col, row, r, g, b);
				}
			}
			color_shift++;

			matrix.SwapBuffer();

#elif DRAW == 2
			for (uint16_t row = 0; row < 32; row++) {
				for (uint16_t col = 0; col < 64; col++) {
					uint8_t r = row == pos / 64 && col == pos % 64 ? 255 : 0;
					uint8_t g = row == (pos / 64) + 1 && col == pos % 64 ? 255 : 0;
					uint8_t b = row == (pos / 64) + 2 && col == pos % 64 ? 255 : 0;

					matrix.SetPixel(col, row, r, g, b);
				}
			}
			pos++;

			if (pos > (32 * 64)) {
				pos = 0;
			}

			matrix.SwapBuffer();
#endif

//			for (uint16_t row = 0; row < 32; row++) {
//				for (uint16_t col = 0; col < 64; col++) {
//					uint8_t r, g, b;
//
//					r = ((row + col + color_shift) % 4) == 0 ? 255 : 0;
//					g = ((row + col + color_shift) % 4) == 1 ? 255 : 0;
//					b = ((row + col + color_shift) % 4) == 2 ? 255 : 0;
//
//					matrix.SetPixel(col, row, r, g, b);
//				}
//			}

			lastUpdate = now;
		}
	}
}
