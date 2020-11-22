/*
 * configuration.h
 *
 *  Created on: Nov 22, 2020
 *      Author: benvh
 */

#ifndef INC_CONFIGURATION_H_
#define INC_CONFIGURATION_H_

struct Configuration {
public:
	bool useMatrix;
	uint8_t matrixFormat;

	bool useStrands;
	uint8_t strandFormat;

	uint16_t elementCount;
	uint16_t elementWidth;
	uint16_t elementHeight;

	enum PixelConfiguration : uint8_t {
		Simple = 0, LeftToRight = 1, SnakeStartBottomRight = 2
	};

	PixelConfiguration pixelConfiguration = PixelConfiguration::Simple;

	enum Status : uint8_t {
		Uninitialized = 0, Ready = 1
	};

	Status status = Uninitialized;

	uint16_t getWidth() {
		switch (pixelConfiguration) {
		Simple:
			return elementWidth * elementCount;
		default:
			return elementWidth;
		}
	}

	uint16_t getHeight() {
		switch (pixelConfiguration) {
		LeftToRight:
			return elementHeight * elementCount;
		default:
			return elementWidth;
		}
	}
};

#endif /* INC_CONFIGURATION_H_ */
