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
	MatrixDriver(uint8_t width, uint8_t height, ScanType scanType, TIM_HandleTypeDef *htim );

	void open();

	uint8_t PlaneBits(uint8_t value);

	void SetPixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b);

	void SwapBuffer();

	void Send();

	void Dump();

	void SendPlanePixel();
	void Clock();
	void Latch();
private:
	uint16_t BufferOffset(uint8_t x, uint8_t y, uint8_t plane);

	TIM_HandleTypeDef *htim;

	uint8_t width;
	uint8_t height;
	uint8_t planes;
	ScanType scanType;

	bool sendBufferA;

	uint16_t bufferSize;
	uint16_t *bufferA;
	uint16_t *bufferB;

	uint16_t nextOffset = 0;
};

#endif /* INC_MATRIX_DRIVER_H_ */
