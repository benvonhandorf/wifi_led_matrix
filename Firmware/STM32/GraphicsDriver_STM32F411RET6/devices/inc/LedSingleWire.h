/*
 * LedSingleWire.h
 *
 *  Created on: Nov 17, 2020
 *      Author: benvh
 */

#ifndef SRC_LEDSINGLEWIRE_H_
#define SRC_LEDSINGLEWIRE_H_

#include "configuration.h"

class LedSingleWire : public DisplayDriver {
public:
	enum Format { RGBW, GRBW };

	LedSingleWire();

	void Open(Configuration *configuration);

	void Close();

	void SetPixel(uint16_t pixel, uint16_t strand, uint8_t r,
			uint8_t g, uint8_t b, uint8_t w);

	void SwapBuffer();

	void StartNextDma();

private:
	void SendStands();

	Format format;
	uint8_t bytesPerPixel;

	uint8_t	strandCount;
	uint16_t pixelCount;
	uint16_t bufferLength;

	uint16_t *buffer;
};

#endif /* SRC_LEDSINGLEWIRE_H_ */