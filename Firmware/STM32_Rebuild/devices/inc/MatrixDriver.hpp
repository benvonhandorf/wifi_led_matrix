/*
 * matrix_driver.h
 *
 *  Created on: Oct 9, 2020
 *      Author: benvh
 */

#ifndef INC_MATRIX_DRIVER_H_
#define INC_MATRIX_DRIVER_H_

#include <stdint.h>

#include "configuration.hpp"

class MatrixDriver : public DisplayDriver {
public:
	enum ScanType { SCAN_16 };
	MatrixDriver();

	void Open(Configuration *configuration);

	void Close();

	uint8_t PlaneBits(uint8_t value);

	void SetPixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t w);

	void SwapBuffer();

	void Handle();

	void Dump();
private:
	uint16_t BufferOffset(uint16_t x, uint16_t y, uint8_t plane);

	void StartNextDma();

	uint16_t width;
	uint16_t height;
	uint8_t planes;
	ScanType scanType;

	bool sendBufferA;
	bool completeSwap = false;

	uint16_t planeSize;
	uint16_t bufferSize;
	uint16_t *bufferA;
	uint16_t *bufferB;

	uint16_t nextDmaOffset;
};

#endif /* INC_MATRIX_DRIVER_H_ */
