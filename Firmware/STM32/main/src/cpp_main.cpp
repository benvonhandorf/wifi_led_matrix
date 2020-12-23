#include "main.h"
#include "../inc/cpp_main.h"
#include <stdio.h>
#include <string.h>

#include "DisplayDriver.h"
#include "MatrixDriver.h"

#include "LedSingleWire.h"

#include "image.h"
#include "configuration.h"
#include "PixelMapping.h"

#include "Protocol.h"
#include "CommandProcessor.h"

//extern IWDG_HandleTypeDef hiwdg;

extern SPI_HandleTypeDef hspi1;

extern UART_HandleTypeDef huart1;

#define PANEL_WIDTH 64
#define PANEL_HEIGHT 32

uint8_t buffer[1024];

uint32_t lastUpdate = 0;

DisplayDriver *display = NULL;

Configuration configuration;
PixelMapping *pixelMapping = NULL;

void readConfiguration() {
	configuration.useMatrix = false;
	configuration.useStrands = true;

	if (configuration.useMatrix) {
		configuration.matrixFormat = MatrixDriver::SCAN_16;
		configuration.elementWidth = PANEL_WIDTH;
		configuration.elementHeight = PANEL_HEIGHT;
		configuration.elementCount = 2;
	} else if (configuration.useStrands) {
		configuration.strandFormat = LedSingleWire::GRBW;
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

//void draw(PixelMapping::Pixel pixel, uint8_t r, uint8_t g, uint8_t b,
//		uint8_t w) {
//	if (display != NULL) {
//		PixelMapping::Pixel physicalPixel =
//				pixelMapping->mapVirtualPixelToPhysicalPixel(pixel);
//
//		display->SetPixel(physicalPixel.x, physicalPixel.y, r, g, b, w);
//	}
//}

//void commit() {
//	if (display != NULL) {
//		display->SwapBuffer();
//	}
//}

//Test patterns.  Do not define for normal operation
//1 - test pattern
//2 - advancing pixel
//3 - image
//4 - Debugging
//#define DRAW 5
Request request;
CommandProcessor commandProcessor;

uint8_t spi_buffer[1024];

bool parseSpi = false;

//uint8_t state = 0;

void RxCpltCallback(SPI_HandleTypeDef *hspi) {
//	if (state == 0) {
//		sprintf((char *)buffer, "RX: %d - %01x %02x\n", hspi1.RxXferCount,
//				spi_buffer[0], spi_buffer[1]);
//
//		HAL_UART_Transmit(&huart1, buffer, strlen((char *)buffer), 2000);
//
//		if (spi_buffer[1] != 0) {
//			state = 1;
//
//			HAL_SPI_Receive_IT(&hspi1, spi_buffer + 2, spi_buffer[1]);
//		} else {
//			request.type = spi_buffer[0];
//			request.bodyLength = spi_buffer[1];
//			request.Parse(spi_buffer, spi_buffer[1] + 2);
//
//			state = 0;
//
//			HAL_SPI_Receive_IT(&hspi1, spi_buffer, 2);
//
//			commandProcessor.ProcessRequest(&request, display);
//		}
//	} else {
	parseSpi = true;
//	}
}

void HAL_SPI_Error(SPI_HandleTypeDef *hspi) {
	sprintf((char *)buffer, "ERROR\n");

	HAL_UART_Transmit(&huart1, buffer, strlen((char *)buffer), 2000);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == IPS_NCS_Pin) {
		if (IPS_NCS_GPIO_Port->IDR & IPS_NCS_Pin) {
			HAL_SPI_Abort_IT(&hspi1);

			hspi1.RxCpltCallback = RxCpltCallback;
			hspi1.AbortCpltCallback = RxCpltCallback;

			HAL_SPI_Receive_IT(&hspi1, spi_buffer, 1024);
		} else {
			if(parseSpi) {
				//We're running ahead of our ability to parse.  Asplode?
			}

		}
	}
}

extern "C" int cpp_main(void) {
	__HAL_DBGMCU_FREEZE_IWDG();

	readConfiguration();

	configure();

	open();

	HAL_NVIC_EnableIRQ(SPI1_IRQn);
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);

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
	Request input;

	input.type = RequestType::SetPixelData;
	uint8_t source[] = { 0x00, 0x01, 0x00, 0x00,
			0xFF, 0x00, 0x00, 0x00,
			0x00, 0xFF, 0x00, 0x00,
			0x00, 0x00, 0xFF, 0x00,
			0x00, 0x00, 0x00, 0xFF,
			 };
	input.bodyLength = 20;

	memcpy(input.body, source, input.bodyLength);

	commandProcessor.ProcessRequest(&input, display);

	input.type = RequestType::Commit;
	input.bodyLength = 0;

	commandProcessor.ProcessRequest(&input, display);
#endif

	lastUpdate = HAL_GetTick();

	color_shift++;

	uint32_t duration = HAL_GetTick() - start;

	sprintf((char *)buffer, "Setup Duration: %lu\n", duration);

	HAL_UART_Transmit(&huart1, buffer, strlen((char *)buffer), 500);

	while (1) {

		if(parseSpi) {
			request.Parse(spi_buffer, 1024);

			parseSpi = false;

			commandProcessor.ProcessRequest(&request, display);
		}

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

//		uint16_t row = 31;
//		uint16_t col = pos % 128;
//
//		uint8_t r = 255; //(row % 4) == 0 ? colVal * col : 0;
//		uint8_t g = 0; //((row + 1) % 4) == 0 ? colVal * col : 0;
//		uint8_t b = 0; //((row + 2) % 4) == 0 ? colVal * col : 0;
//
//		PixelMapping::Pixel physicalPixel =
//				pixelMapping->mapVirtualPixelToPhysicalPixel(
//						PixelMapping::Pixel(col, row));
//
//		display->SetPixel(col, row, r, g, b, 0);
//
//		pos++;
//
//		if (pos > (configuration.getWidth() * configuration.getHeight())) {
//			pos = 0;
//		}
//
//		commit();
//
//		HAL_Delay(10);
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
