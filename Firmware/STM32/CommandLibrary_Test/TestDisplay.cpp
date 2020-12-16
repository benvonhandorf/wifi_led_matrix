/*
 * TestDisplay.cpp
 *
 *  Created on: Dec 15, 2020
 *      Author: benvh
 */

#include "TestDisplay.h"

TestDisplay::TestDisplay() {
	// TODO Auto-generated constructor stub

}

TestDisplay::~TestDisplay() {
	// TODO Auto-generated destructor stub
}

void TestDisplay::Open(){}

void TestDisplay::Close() {}

void TestDisplay::SetPixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g,
		uint8_t b, uint8_t w) {
	pixelCount++;

	PixelResult result = PixelResult {
		.x = x,
				.y = y,
				.r = r,
				.g = g,
				.b = b,
				.w = w
	};

	pixels.push_back(result);
}

void TestDisplay::SwapBuffer() {
	swapCount++;
}
