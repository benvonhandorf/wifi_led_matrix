#include "main.h"
#include "../inc/cpp_main.h"
#include <stdio.h>
#include <string.h>

#include "matrix_driver.h"

#include "image.h"

extern IWDG_HandleTypeDef hiwdg;

extern SPI_HandleTypeDef hspi1;

extern UART_HandleTypeDef huart1;

#define PANEL_WIDTH 64
#define PANEL_HEIGHT 32

MatrixDriver matrix(PANEL_WIDTH, PANEL_HEIGHT, MatrixDriver::ScanType::SCAN_16);

char buffer[1024];

uint32_t lastUpdate = 0;

//1 - test pattern
//2 - advancing pixel
//3 - image
//4 - Debugging
#define DRAW 1

extern "C" int cpp_main(void) {
	__HAL_DBGMCU_FREEZE_IWDG();

	uint32_t start = HAL_GetTick();

	uint16_t color_shift = 1;

	uint16_t pos = 0;

#if DRAW == 1
	for (uint16_t col = 0; col < PANEL_WIDTH; col++) {
		for (uint16_t row = 0; row < PANEL_HEIGHT; row++) {

			uint8_t r, g, b;

			r = ((row + col + color_shift) % 4) == 0 ? 255 / col : 0;
			g = ((row + col + color_shift) % 4) == 1 ? 255 / row : 0;
			b = ((row + col + color_shift) % 4) == 2 ? 4 * col : 0;

			matrix.SetPixel(row, col, r, g, b);
		}
	}
#elif DRAW == 2
	for (uint16_t col = 0; col < PANEL_WIDTH; col++) {
		for (uint16_t row = 0; row < PANEL_HEIGHT; row++) {
			uint8_t r = ((row == (pos / 64)) && (col == pos % 64)) ? 255 : 0;
			uint8_t g =
					((row == (pos / 64) + 1) && (col == pos % 64)) ? 255 : 0;
			uint8_t b =
					((row == (pos / 64) + 2) && (col == pos % 64)) ? 255 : 0;

			matrix.SetPixel(col, row, r, g, b);
		}
	}
#elif DRAW == 3
	for (uint16_t col = 0; col < PANEL_WIDTH; col++) {
		for (uint16_t row = 0; row < PANEL_HEIGHT; row++) {
			uint8_t r = IMAGE_DATA[col % IMAGE_WIDTH][row][0];
			uint8_t g = IMAGE_DATA[col % IMAGE_WIDTH][row][1];
			uint8_t b = IMAGE_DATA[col % IMAGE_WIDTH][row][2];

			matrix.SetPixel(col, row, r, g, b);
		}
	}
#elif DRAW == 4
	for (uint16_t col = 0; col < PANEL_WIDTH; col++) {
		for (uint16_t row = 0; row < PANEL_HEIGHT; row++) {
			uint8_t r = 0;
			uint8_t g = 0;
			uint8_t b = (col > 32) ? (row %2 == 0) ? 255 : 75 : 0;

			matrix.SetPixel(col, row, r, g, b);
		}
	}
#endif

	lastUpdate = HAL_GetTick();

	color_shift++;

	matrix.Dump();

	matrix.SwapBuffer();

	uint32_t duration = HAL_GetTick() - start;

	sprintf(buffer, "Setup Duration: %lu\n", duration);

	HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 500);

	matrix.open();

	while (1) {

//		HAL_Delay(5);

#if DRAW == 1
		for (uint16_t col = 0; col < PANEL_WIDTH; col++) {
			for (uint16_t row = 0; row < PANEL_HEIGHT; row++) {

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
			//pos 64:
			//Panel 1: Red on row 1, Green on row 2, faint green on row 13, flickering red on row 15, all in col 0
			//flickering red about halfway across row 15
			//Panel 2: Red on row 1, Blue on row 2, looks steady
//			pos = 65;

			for (uint16_t col = 0; col < PANEL_WIDTH; col++) {
				for (uint16_t row = 0; row < PANEL_HEIGHT; row++) {

					uint8_t r =
							row == (pos / 64) && col == (pos % 64) ? 255 : 0;
					uint8_t g =
							row == (pos / 64) + 1 && col == (pos % 64) ?
									255 : 0;
					uint8_t b =
							row == (pos / 64) + 2 && col == (pos % 64) ?
									255 : 0;

					matrix.SetPixel(col, row, r, g, b);
				}
			}
			pos++;

			if (pos > (IMAGE_WIDTH /* IMAGE_HEIGHT*/)) {
				pos = 0;
			}

			matrix.SwapBuffer();
#endif

//			for (uint16_t row = 0; row < PANEL_HEIGHT; row++) {
//				for (uint16_t col = 0; col < PANEL_WIDTH; col++) {
//					uint8_t r, g, b;
//
//					r = ((row + col + color_shift) % 4) == 0 ? 255 : 0;
//					g = ((row + col + color_shift) % 4) == 1 ? 255 : 0;
//					b = ((row + col + color_shift) % 4) == 2 ? 255 : 0;
//
//					matrix.SetPixel(col, row, r, g, b);
//				}
//			}
	}
}
