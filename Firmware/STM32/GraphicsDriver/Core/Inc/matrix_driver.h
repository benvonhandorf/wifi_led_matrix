/*
 * matrix_driver.h
 *
 *  Created on: Oct 9, 2020
 *      Author: benvh
 */

#ifndef INC_MATRIX_DRIVER_H_
#define INC_MATRIX_DRIVER_H_

class MatrixDriver {
public:
	enum ScanType { SCAN_16 };
	MatrixDriver(uint8_t width, uint8_t height, ScanType scanType);

	void open();

	uint8_t PlaneBits(uint8_t value);

	void SetPixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b);

	void SwapBuffer();

	void Handle();

	void Send();

	void Dump();

	void SendPlanePixel();
	void Clock();
	void Latch();

	void StartNextDma();

	bool handleNeeded = false;
private:
	uint16_t BufferOffset(uint8_t x, uint8_t y, uint8_t plane);

	uint8_t rowLeadIn; //Extra entries at the start of a row.  Used to give DMA and CLK a chance to sync up.  They'll be clocked out at the start of a row so will be driven off the end
	uint8_t width;
	uint8_t height;
	uint8_t planes;
	ScanType scanType;

	bool sendBufferA;

	uint16_t bufferSize;
	uint16_t *bufferA;
	uint16_t *bufferB;

	uint16_t rowPlane = 0;
	uint16_t rowPlaneSize = 0;

	uint16_t nextOffset = 0;
};

#endif /* INC_MATRIX_DRIVER_H_ */
