/*
 * empty.cpp
 *
 *  Created on: Dec 12, 2020
 *      Author: benvh
 */

#include "DisplayDriver.h"

class StubDisplayDriver : DisplayDriver {
public:
	void Open(Configuration *configuration) {

	}
	void Close() {

	}
	void SetPixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {

	}
	void SwapBuffer() {

	}
};

