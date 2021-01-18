/*
 * Command.cpp
 *
 *  Created on: Dec 6, 2020
 *      Author: benvh
 */

#include "CommandProcessor.h"

CommandProcessor::CommandProcessor() {
	// TODO Auto-generated constructor stub

}

CommandProcessor::~CommandProcessor() {
	// TODO Auto-generated destructor stub
}

void CommandProcessor::ProcessRequest(Request *request, DisplayDriver *display,
		Configuration *configuration, PixelMapping *pixelMapping) {
	switch (request->type) {
	case RequestType::SetPixelData: {
		uint16_t x = request->body[0] << 8 | request->body[1];
		uint16_t y = request->body[2] << 8 | request->body[3];

		uint16_t pixelStart = 4;

		while (pixelStart < request->bodyLength) {
			uint8_t r = request->body[pixelStart + 0];
			uint8_t g = request->body[pixelStart + 1];
			uint8_t b = request->body[pixelStart + 2];
			uint8_t w = request->body[pixelStart + 3];

			PixelMapping::Pixel physicalPixel = pixelMapping->mapVirtualPixelToPhysicalPixel(PixelMapping::Pixel(x, y));

			display->SetPixel(physicalPixel.x, physicalPixel.y, r, g, b, w);

			pixelStart += 4;
			x++;
		}

		break;
	}

	case RequestType::ClearAssignPixelData: {
		for (uint16_t x = 0; x < configuration->getWidth(); x++) {
			for (uint16_t y = 0; y < configuration->getHeight(); y++) {
				PixelMapping::Pixel physicalPixel = pixelMapping->mapVirtualPixelToPhysicalPixel(PixelMapping::Pixel(x, y));

				display->SetPixel(physicalPixel.x, physicalPixel.y, 0, 0, 0, 0);
			}
		}
		//No break.  Proceed to assign pixel data
	}
	case RequestType::AssignPixelData: {
		for (uint16_t offset = 0; offset < request->bodyLength; offset += 8) {

			uint16_t x = request->body[offset + 0] << 8
					| request->body[offset + 1];
			uint16_t y = request->body[offset + 2] << 8
					| request->body[offset + 3];

			uint8_t r = request->body[offset + 4];
			uint8_t g = request->body[offset + 5];
			uint8_t b = request->body[offset + 6];
			uint8_t w = request->body[offset + 7];

			PixelMapping::Pixel physicalPixel = pixelMapping->mapVirtualPixelToPhysicalPixel(PixelMapping::Pixel(x, y));

			display->SetPixel(physicalPixel.x, physicalPixel.y, r, g, b, w);
		}

		break;
	}
	case RequestType::Commit: {
		display->SwapBuffer();
		break;
	}
	}
}

