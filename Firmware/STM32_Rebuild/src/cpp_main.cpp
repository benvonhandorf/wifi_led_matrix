#include "../inc/cpp_main.h"
#include "main.h"

#include <stdio.h>
#include <string.h>

#include "DisplayDriver.hpp"
#include "MatrixDriver.hpp"

#include "LedSingleWire.hpp"

#include "image.h"
#include "configuration.hpp"
#include "PixelMapping.hpp"

#include "Protocol.hpp"
#include "CommandProcessor.hpp"

#include <stm32f4xx_hal.h>

//extern IWDG_HandleTypeDef hiwdg;
extern DMA_HandleTypeDef hdma_spi1_rx;

extern SPI_HandleTypeDef hspi1;

extern UART_HandleTypeDef huart1;

#define PANEL_WIDTH 64
#define PANEL_HEIGHT 32

uint8_t stringBuffer[1024];

uint32_t lastUpdate = 0;

MatrixDriver matrixDisplay;
LedSingleWire ledSingleWireDisplay;
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
		
		configuration.pixelConfiguration =
			Configuration::PixelConfiguration::SnakeStartBottomRight;
	} else if (configuration.useStrands) {
		configuration.strandFormat = LedSingleWire::GRBW;
		configuration.elementWidth = 300;
		configuration.elementHeight = 1;
		configuration.elementCount = 1;

		configuration.pixelConfiguration =
			Configuration::PixelConfiguration::Simple;
	}
}

void configure() {
	if(display != NULL) {
		display->Close();
		display = NULL;
	}

	if (configuration.useMatrix) {
		display = &matrixDisplay;
	} else if (configuration.useStrands) {

		display = &ledSingleWireDisplay;
	}

	if(pixelMapping != NULL) {
		delete pixelMapping;
		pixelMapping = NULL;
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
		pixelMapping = new SimplePixelMapping(configuration.elementCount,
				configuration.elementWidth, configuration.elementHeight);
		break;
	}
}

void open() {
	if (display != NULL) {
		display->Open(&configuration);
	}

	configuration.status = Configuration::Status::Ready;
}

void draw(Pixel pixel, uint8_t r, uint8_t g, uint8_t b,
		uint8_t w) {
	if (display != NULL) {
		Pixel physicalPixel =
				pixelMapping->mapVirtualPixelToPhysicalPixel(pixel);

		display->SetPixel(physicalPixel.x, physicalPixel.y, r, g, b, w);
	}
}

void commit() {
	if (display != NULL) {
		display->SwapBuffer();
	}
}

//Test patterns.  Do not define for normal operation
//1 - test pattern
//2 - advancing pixel
//3 - image
//4 - Debugging
//5 - Simulate receive
//6 - Repeating pattern
//#define DRAW 6

Request request;
CommandProcessor commandProcessor;

struct RxBuffer {
	RxBuffer() {
		for (int c = 0; c < NETWORK_PACKET_SIZE; c++) {
			buffer[c] = 0x00;
		}
	}
	volatile bool inUse = false;
	volatile bool ready = false;
	uint8_t buffer[NETWORK_PACKET_SIZE];
};

#define RX_BUFFERS 2
RxBuffer receiveBuffers[RX_BUFFERS];
volatile RxBuffer *currentBuffer = NULL;

#define MESSAGE_BODY_BYTES 2045

#define PROTOCOL_HEADER 3
#define MESSAGE_HEADER 4
#define BYTES_PER_PIXEL 4
constexpr uint16_t DATA_POSITION = PROTOCOL_HEADER + MESSAGE_HEADER;
constexpr uint16_t PIXELS_PER_MESSAGE = (MESSAGE_BODY_BYTES - MESSAGE_HEADER)
		/ BYTES_PER_PIXEL;

#define STATE_GPIO_Port LED_CLK_GPIO_Port
#define STATE_Pin LED_1_Pin

struct SystemStatus {
	uint32_t invalidCommands = 0;
	uint32_t commands = 0;
	uint8_t lastInvalidCommand = 0x00;
};

SystemStatus systemStatus;

//uint8_t state = 0;

void DmaTransactionComplete(DMA_HandleTypeDef *hdma) {
	currentBuffer->ready = true;
	currentBuffer->inUse = false;
	currentBuffer =
			(hdma_spi1_rx.Instance->CR & DMA_SxCR_CT_Msk) ?
					&receiveBuffers[1] : &receiveBuffers[0];
	currentBuffer->inUse = true;
}

void DmaErrors(DMA_HandleTypeDef *hdma) {
	sprintf((char*) stringBuffer, "DMA Error %x\n", hdma->ErrorCode);

	HAL_UART_Transmit(&huart1, stringBuffer, strlen((char*) stringBuffer),
			2000);
}

void HAL_SPI_Error(SPI_HandleTypeDef *hspi) {
	sprintf((char*) stringBuffer, "ERROR\n");

	HAL_UART_Transmit(&huart1, stringBuffer, strlen((char*) stringBuffer),
			2000);
}

void BeginReceive() {
	hdma_spi1_rx.XferCpltCallback = DmaTransactionComplete;
	hdma_spi1_rx.XferM1CpltCallback = DmaTransactionComplete;
	hdma_spi1_rx.XferErrorCallback = DmaErrors;

	HAL_StatusTypeDef result;

	currentBuffer =
			(hdma_spi1_rx.Instance->CR & DMA_SxCR_CT_Msk) ?
					&receiveBuffers[1] : &receiveBuffers[0];
	currentBuffer->ready = false;
	currentBuffer->inUse = true;

	result = HAL_DMAEx_MultiBufferStart_IT(&hdma_spi1_rx,
			(uint32_t) &hspi1.Instance->DR, (uint32_t) receiveBuffers[0].buffer,
			(uint32_t) receiveBuffers[1].buffer, NETWORK_PACKET_SIZE);

	if (result != HAL_OK) {
		sprintf((char*) stringBuffer, "DMA Start Failure: %lu\n", result);

		HAL_UART_Transmit(&huart1, stringBuffer, strlen((char*) stringBuffer),
				500);
	}

	//Turn on the SPI peripheral and interrupt
	__HAL_SPI_ENABLE(&hspi1);
	__HAL_SPI_ENABLE_IT(&hspi1, (SPI_IT_ERR));

	/* Enable RX DMA Request */
	SET_BIT((&hspi1)->Instance->CR2, SPI_CR2_RXDMAEN);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == SPI1_NCS_Pin) {
		if (SPI1_NCS_GPIO_Port->IDR & SPI1_NCS_Pin) {
			HAL_NVIC_DisableIRQ(EXTI4_IRQn);
			BeginReceive();
		}
	}
}

extern "C" int cpp_main(void) {
	__HAL_DBGMCU_FREEZE_IWDG();

	readConfiguration();

	configure();

	sprintf((char*) stringBuffer, "Configuration: %lu %lu\n", configuration.getWidth(), configuration.getHeight());

	HAL_UART_Transmit(&huart1, stringBuffer, strlen((char*) stringBuffer),
		500);

	open();

	HAL_NVIC_EnableIRQ(SPI1_IRQn);
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);

//	BeginReceive();

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

#elif DRAW == 6

	uint8_t source[] = { 
			0x00, 0x00, 0x00, 0x00,
			0xFF, 0x00, 0x00, 0x00,
			0x00, 0xFF, 0x00, 0x00,
			0x00, 0x00, 0xFF, 0x00,
			0x00, 0x00, 0x00, 0xFF,
			 };
	uint16_t source_length = sizeof(source);

	for (uint16_t col = 0; col < configuration.getWidth(); col++) {

		for (uint16_t row = 0; row < configuration.getHeight(); row++) {
			uint16_t pixel_position = (row * configuration.getWidth()) + col + pos;

			uint8_t r =
					source[((pixel_position * 4) + 0) % source_length];
			uint8_t g =
					source[((pixel_position * 4) + 1) % source_length];
			uint8_t b =
					source[((pixel_position * 4) + 2) % source_length];
			uint8_t w =
					source[((pixel_position * 4) + 3) % source_length];

			draw(Pixel(col, row), r, g, b, w);
		}
	}

#endif

	lastUpdate = HAL_GetTick();

	color_shift++;

	uint32_t duration = HAL_GetTick() - start;

	sprintf((char*) stringBuffer, "Setup Duration: %lu\n", duration);

	HAL_UART_Transmit(&huart1, stringBuffer, strlen((char*) stringBuffer), 500);

	while (1) {
#ifndef DRAW

		for (int i = 0; i < RX_BUFFERS; i++) {
//			start = HAL_GetTick();

			if (receiveBuffers[i].ready && !receiveBuffers[i].inUse) {

#ifdef STATE_GPIO_Port
				HAL_GPIO_WritePin(STATE_GPIO_Port, STATE_Pin, GPIO_PIN_SET);
#endif

				if (!request.Parse(receiveBuffers[i].buffer, MESSAGE_BODY_BYTES)) {
					systemStatus.invalidCommands++;
					systemStatus.lastInvalidCommand = receiveBuffers[i].buffer[0];
//					sprintf((char*) stringBuffer, "UNK: %d %02x - %d\r\n", i,
//							request.type, request.bodyLength);
//
//					HAL_UART_Transmit(&huart1, stringBuffer, strlen((char*) stringBuffer),
//							100);
				} else {
					systemStatus.commands++;

					commandProcessor.ProcessRequest(&request, display,
							&configuration, pixelMapping);

					if(request.type == RequestType::Configure) {
						//Reconfigure the display to match the new information
						configure();

						open();
					}
				}

				receiveBuffers[i].ready = false;

#ifdef STATE_GPIO_Port
				HAL_GPIO_WritePin(STATE_GPIO_Port, STATE_Pin, GPIO_PIN_RESET);
#endif
			}
		}

#elif DRAW == 1
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

	HAL_Delay(5);

#elif DRAW == 2
		//pos 64:
		//Panel 1: Red on row 1, Green on row 2, faint green on row 13, flickering red on row 15, all in col 0
		//flickering red about halfway across row 15
		//Panel 2: Red on row 1, Blue on row 2, looks steady
//			pos = 65;

//		HAL_GPIO_WritePin(STATE_GPIO_Port, STATE_Pin, GPIO_PIN_SET);

		for (uint16_t col = 0; col < configuration.getWidth(); col++) {
			for (uint16_t row = 0; row < configuration.getHeight(); row++) {

				uint8_t r = row == (pos / 64) && col == (pos % 64) ? 255 : 0;
				uint8_t g =
						row == (pos / 64) + 1 && col == (pos % 64) ? 255 : 0;
				uint8_t b =
						row == (pos / 64) + 2 && col == (pos % 64) ? 255 : 0;

				if (r > 0 || g > 0 || b > 0) {
					draw(Pixel(col, row), r, g, b, 0);
				}
			}
		}
		pos++;

		if (pos > (configuration.getWidth() * configuration.getHeight())) {
			pos = 0;
		}

		commit();

//		HAL_GPIO_WritePin(STATE_GPIO_Port, STATE_Pin, GPIO_PIN_RESET);
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

#elif DRAW == 6

	duration = HAL_GetTick() - lastUpdate;

	if(duration > 1000) {
		pos++;

		lastUpdate = HAL_GetTick();

		uint8_t source[] = { 
				0x00, 0x00, 0x00, 0x00,
				0xFF, 0x00, 0x00, 0x00,
				0x00, 0xFF, 0x00, 0x00,
				0x00, 0x00, 0xFF, 0x00,
				0x00, 0x00, 0x00, 0xFF,
				};
		uint16_t source_length = sizeof(source);

		for (uint16_t col = 0; col < configuration.getWidth(); col++) {

			for (uint16_t row = 0; row < configuration.getHeight(); row++) {
				uint16_t pixel_position = (row * configuration.getWidth()) + col + pos;

				uint8_t r =
						source[((pixel_position * 4) + 0) % source_length];
				uint8_t g =
						source[((pixel_position * 4) + 1) % source_length];
				uint8_t b =
						source[((pixel_position * 4) + 2) % source_length];
				uint8_t w =
						source[((pixel_position * 4) + 3) % source_length];

				draw(Pixel(col, row), r, g, b, w);
			}
		}

		commit();
	}

#endif
	}
}
