#include "main.h"
#include "../inc/cpp_main.h"
#include <stdio.h>
#include <string.h>

#include "DisplayDriver.h"
#include "matrix_driver.h"

#include "LedSingleWire.h"

#include "image.h"
#include "configuration.h"
#include "PixelMapping.h"

//extern IWDG_HandleTypeDef hiwdg;

extern SPI_HandleTypeDef hspi1;

extern UART_HandleTypeDef huart1;

#define PANEL_WIDTH 64
#define PANEL_HEIGHT 32

char buffer[1024];

uint32_t lastUpdate = 0;

DisplayDriver *display = NULL;

Configuration configuration;
PixelMapping *pixelMapping = NULL;

void readConfiguration() {
	configuration.useMatrix = true;
	configuration.useStrands = false;

	if (configuration.useMatrix) {
		configuration.matrixFormat = MatrixDriver::SCAN_16;
		configuration.elementWidth = PANEL_WIDTH;
		configuration.elementHeight = PANEL_HEIGHT;
		configuration.elementCount = 2;
	} else if (configuration.useStrands) {
		configuration.strandFormat = LedSingleWire::RGBW;
		configuration.elementWidth = 300;
		configuration.elementHeight = 1;
		configuration.elementCount = 1;
	}

	configuration.pixelConfiguration =
			Configuration::PixelConfiguration::SnakeStartBottomRight;
}

void configure() {
	if (configuration.useMatrix) {
		display = new MatrixDriver(
				configuration.elementWidth * configuration.elementCount,
				configuration.elementHeight,
				(MatrixDriver::ScanType) configuration.matrixFormat);
	} else if (configuration.useStrands) {

		display = new LedSingleWire(
				(LedSingleWire::Format) configuration.strandFormat,
				configuration.elementCount, configuration.elementWidth);
	}

	switch (configuration.pixelConfiguration) {
	case Configuration::PixelConfiguration::LeftToRight:
		pixelMapping = new LeftToRightPixelMapping(configuration.elementCount,
				configuration.elementWidth, configuration.elementHeight);
		break;
	case Configuration::PixelConfiguration::SnakeStartBottomRight:
		pixelMapping = new SnakePixelMappingFedBottomRight(
				configuration.elementCount, configuration.elementWidth,
				configuration.elementHeight);
		break;
	default:
		pixelMapping = new SimplePixelMapping();
		break;
	}
}

void open() {
	if (display != NULL) {
		display->Open();
	}

	configuration.status = Configuration::Status::Ready;
}

void draw(PixelMapping::Pixel pixel, uint8_t r, uint8_t g, uint8_t b,
		uint8_t w) {
	if (display != NULL) {
		PixelMapping::Pixel physicalPixel =
				pixelMapping->mapVirtualPixelToPhysicalPixel(pixel);

		display->SetPixel(physicalPixel.x, physicalPixel.y, r, g, b, w);
	}
}

void commit() {
	if (display != NULL) {
		display->SwapBuffer();
	}
}

//1 - test pattern
//2 - advancing pixel
//3 - image
//4 - Debugging
#define DRAW 3

extern "C" int cpp_main(void) {
	__HAL_DBGMCU_FREEZE_IWDG();

	readConfiguration();

	configure();

	open();

	uint16_t color_shift = 1;

	uint32_t start = HAL_GetTick();

	uint16_t pos = 0;

#if DRAW == 3
	for (uint16_t col = 0; col < configuration.getWidth(); col++) {

		for (uint16_t row = 0; row < configuration.getHeight(); row++) {
			uint8_t r =
					IMAGE_DATA[pos][col % IMAGE_WIDTH][row % IMAGE_HEIGHT][0];
			uint8_t g =
					IMAGE_DATA[pos][col % IMAGE_WIDTH][row % IMAGE_HEIGHT][1];
			uint8_t b =
					IMAGE_DATA[pos][col % IMAGE_WIDTH][row % IMAGE_HEIGHT][2];

			draw(PixelMapping::Pixel(col, row), r, g, b, 0);
		}
	}

#elif DRAW == 4

	draw(PixelMapping::Pixel(0, 0), 255, 0, 0, 0);
	draw(PixelMapping::Pixel(configuration.getWidth() - 1, 0), 0, 255, 0, 0);
	draw(PixelMapping::Pixel(0, configuration.getHeight() - 1), 0, 0, 255, 0);
	draw(
			PixelMapping::Pixel(configuration.getWidth() - 1,
					configuration.getHeight() - 1), 255, 255, 255, 0);

	draw(PixelMapping::Pixel(32, 9), 255, 255, 255, 0);
#elif DRAW == 5

//	uint8_t colVal = 255 / configuration->getWidth();
//
//	for (uint16_t col = 0; col < configuration.getWidth(); col++) {
////		HAL_IWDG_Refresh(&hiwdg);
//
//		for (uint16_t row = 0; row < configuration.getHeight(); row++) {
//			uint8_t r = colVal * col; //(row % 4) == 0 ? colVal * col : 0;
//			uint8_t g = 0;//((row + 1) % 4) == 0 ? colVal * col : 0;
//			uint8_t b = 0;//((row + 2) % 4) == 0 ? colVal * col : 0;
//
//			draw(PixelMapping::Pixel(col, row), r, g, b, 0);
//		}
//	}
#endif

	lastUpdate = HAL_GetTick();

	color_shift++;

	uint32_t duration = HAL_GetTick() - start;

	sprintf(buffer, "Setup Duration: %lu\n", duration);

	HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 500);

	commit();

	while (1) {

//		HAL_IWDG_Refresh(&hiwdg);

//		HAL_Delay(5);

#if DRAW == 1
	for (uint16_t col = 0; col < configuration.getWidth(); col++) {
		for (uint16_t row = 0; row < configuration.getHeight(); row++) {

			uint8_t r, g, b;

			r = ((row + col + color_shift) % 4) == 0 ? 255 : 0;
			g = ((row + col + color_shift) % 4) == 1 ? 255 : 0;
			b = ((row + col + color_shift) % 4) == 2 ? 255 : 0;

			draw(PixelMapping::Pixel(col, row), r, g, b, 0);
		}
	}
	color_shift++;

	commit();

//		HAL_Delay(5);

#elif DRAW == 2
	//pos 64:
	//Panel 1: Red on row 1, Green on row 2, faint green on row 13, flickering red on row 15, all in col 0
	//flickering red about halfway across row 15
	//Panel 2: Red on row 1, Blue on row 2, looks steady
//			pos = 65;

	for (uint16_t col = 0; col < configuration.getWidth(); col++) {
		for (uint16_t row = 0; row < configuration.getHeight(); row++) {

			uint8_t r =
			row == (pos / 64) && col == (pos % 64) ? 255 : 0;
			uint8_t g =
			row == (pos / 64) + 1 && col == (pos % 64) ?
			255 : 0;
			uint8_t b =
			row == (pos / 64) + 2 && col == (pos % 64) ?
			255 : 0;

			if(r > 0 || g > 0 || b > 0 ) {
				display->(PixelMapping::Pixel(col, row), r, g, b, 0);
			}
		}
	}
	pos++;

	if (pos > (configuration.getWidth() * configuration.getHeight())) {
		pos = 0;
	}

	commit();
#elif DRAW == 3

//		HAL_Delay(5);

		start = HAL_GetTick();

		for (uint16_t col = 0; col < configuration.getWidth(); col++) {

			for (uint16_t row = 0; row < configuration.getHeight(); row++) {
				uint8_t r = IMAGE_DATA[pos][col % IMAGE_WIDTH][row
						% IMAGE_HEIGHT][0];
				uint8_t g = IMAGE_DATA[pos][col % IMAGE_WIDTH][row
						% IMAGE_HEIGHT][1];
				uint8_t b = IMAGE_DATA[pos][col % IMAGE_WIDTH][row
						% IMAGE_HEIGHT][2];

				draw(PixelMapping::Pixel(col, row), r, g, b, 0);
			}
		}

		commit();

//		uint32_t duration = HAL_GetTick() - start;
//
//		sprintf(buffer, "Setup Duration: %lu\n", duration);
//
//		HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 500);

		pos += 1;

		if (pos >= IMAGE_FRAMES) {
			pos = 0;
		}
#elif DRAW == 5

	uint16_t row = 31;
	uint16_t col = pos % 128;

	uint8_t r = 255; //(row % 4) == 0 ? colVal * col : 0;
	uint8_t g = 0;//((row + 1) % 4) == 0 ? colVal * col : 0;
	uint8_t b = 0;//((row + 2) % 4) == 0 ? colVal * col : 0;

	PixelMapping::Pixel physicalPixel = pixelMapping->mapVirtualPixelToPhysicalPixel(PixelMapping::Pixel(col, row));

	display->SetPixel(col, row, r, g, b, 0);

	pos++;

	if (pos > (configuration.getWidth() * configuration.getHeight())) {
		pos = 0;
	}

	commit();

	HAL_Delay(10);
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
