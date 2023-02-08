/*
 * Command.cpp
 *
 *  Created on: Dec 6, 2020
 *      Author: benvh
 */

#include "CommandProcessor.hpp"
#include "string.h"

CommandProcessor::CommandProcessor() {
	// TODO Auto-generated constructor stub

}

CommandProcessor::~CommandProcessor() {
	// TODO Auto-generated destructor stub
}

void CommandProcessor::SetPixelData(Request *request, DisplayDriver *display,
		Configuration *configuration, PixelMapping *pixelMapping) {
	uint16_t x = request->body[0] << 8 | request->body[1];
	uint16_t y = request->body[2] << 8 | request->body[3];

	uint16_t pixelStart = 4;

	while (pixelStart < request->bodyLength) {
		uint8_t r = request->body[pixelStart + 0];
		uint8_t g = request->body[pixelStart + 1];
		uint8_t b = request->body[pixelStart + 2];
		uint8_t w = request->body[pixelStart + 3];

		Pixel physicalPixel =
				pixelMapping->mapVirtualPixelToPhysicalPixel(
						Pixel(x, y));

		display->SetPixel(physicalPixel.x, physicalPixel.y, r, g, b, w);

		pixelStart += 4;
		x++;
	}
}

void CommandProcessor::Clear(Request *request, DisplayDriver *display,
		Configuration *configuration, PixelMapping *pixelMapping) {
	for (uint16_t x = 0; x < configuration->getWidth(); x++) {
		for (uint16_t y = 0; y < configuration->getHeight(); y++) {
			Pixel physicalPixel =
					pixelMapping->mapVirtualPixelToPhysicalPixel(
							Pixel(x, y));

			display->SetPixel(physicalPixel.x, physicalPixel.y, 0, 0, 0, 0);
		}
	}
}

void CommandProcessor::AssignPixelData(Request *request, DisplayDriver *display,
		Configuration *configuration, PixelMapping *pixelMapping) {
	for (uint16_t offset = 0; offset < request->bodyLength; offset += 8) {

		uint16_t x = request->body[offset + 0] << 8 | request->body[offset + 1];
		uint16_t y = request->body[offset + 2] << 8 | request->body[offset + 3];

		uint8_t r = request->body[offset + 4];
		uint8_t g = request->body[offset + 5];
		uint8_t b = request->body[offset + 6];
		uint8_t w = request->body[offset + 7];

		Pixel physicalPixel =
				pixelMapping->mapVirtualPixelToPhysicalPixel(
						Pixel(x, y));

		display->SetPixel(physicalPixel.x, physicalPixel.y, r, g, b, w);
	}
}

void CommandProcessor::Commit(Request *request, DisplayDriver *display,
		Configuration *configuration, PixelMapping *pixelMapping) {
	display->SwapBuffer();
}

void CommandProcessor::Configure(Request *request, DisplayDriver *display,
		Configuration *configuration, PixelMapping *pixelMapping) {
	if(request->bodyLength == sizeof(struct ConfigurationDefinition)) {
		struct ConfigurationDefinition configurationDefinition;

		memcpy(&configurationDefinition, request->body, sizeof(struct ConfigurationDefinition));

		if(configurationDefinition.version == CONFIGURATION_VERSION) {
			configuration->useMatrix = configurationDefinition.displayType == ConfigurationDisplayType::Matrix;
			configuration->useStrands = configurationDefinition.displayType == ConfigurationDisplayType::WS2812Strand;
			configuration->elementWidth = BYTES_TO_UINT16(configurationDefinition.widthH, configurationDefinition.widthL);
			configuration->elementHeight = BYTES_TO_UINT16(configurationDefinition.heightH, configurationDefinition.heightL);
			configuration->elementCount = configurationDefinition.elements;
			configuration->pixelConfiguration = (Configuration::PixelConfiguration) configurationDefinition.pixelMappingType;
		}
 	}
}

void CommandProcessor::ProcessRequest(Request *request, DisplayDriver *display,
		Configuration *configuration, PixelMapping *pixelMapping) {
	switch (request->type) {
	case RequestType::SetPixelData: {
		SetPixelData(request, display, configuration, pixelMapping);

		break;
	}

	case RequestType::ClearAssignPixelData: {
		Clear(request, display, configuration, pixelMapping);
		AssignPixelData(request, display, configuration, pixelMapping);

		break;
	}
	case RequestType::AssignPixelData: {
		AssignPixelData(request, display, configuration, pixelMapping);

		break;
	}
	case RequestType::Commit: {
		Commit(request, display, configuration, pixelMapping);
		break;
	}
	case RequestType::Configure: {
		Configure(request, display, configuration, pixelMapping);
		break;
	}
	}
}

