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

void CommandProcessor::ProcessRequest(Request *request,
		DisplayDriver *display) {
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

			display->SetPixel(x, y, r, g, b, w);

			pixelStart += 4;
			x++;
		}

		break;
	}
	}
}

