/*
 * DisplayDriver.h
 *
 *  Created on: Nov 22, 2020
 *      Author: benvh
 */

#ifndef INC_DISPLAYDRIVER_H_
#define INC_DISPLAYDRIVER_H_

class DisplayDriver {
public:
	virtual void Open() = 0;
	virtual void Close() = 0;
	virtual void SetPixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t w) = 0;
	virtual void SwapBuffer() = 0;
};



#endif /* INC_DISPLAYDRIVER_H_ */
