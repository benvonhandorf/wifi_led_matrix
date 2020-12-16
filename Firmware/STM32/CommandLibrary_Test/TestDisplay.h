/*
 * TestDisplay.h
 *
 *  Created on: Dec 15, 2020
 *      Author: benvh
 */

#ifndef TESTDISPLAY_H_
#define TESTDISPLAY_H_

#include "DisplayDriver.h"

#include <vector>

struct PixelResult {
	uint16_t x;
	uint16_t y;
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t w;
};

class TestDisplay : public DisplayDriver {
public:
	TestDisplay();
	virtual ~TestDisplay();

	virtual void Open();
	virtual void Close();

	virtual void SetPixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t w);
	virtual void SwapBuffer();

	uint16_t pixelCount = 0;
	uint16_t swapCount = 0;

	std::vector<PixelResult> pixels;
};

#endif /* TESTDISPLAY_H_ */
