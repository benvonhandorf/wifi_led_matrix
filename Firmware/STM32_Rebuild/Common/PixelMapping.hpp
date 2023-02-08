/*
 * PixelMapping.h
 *
 *  Created on: Nov 22, 2020
 *      Author: benvh
 */

#ifndef INC_PIXELMAPPING_H_
#define INC_PIXELMAPPING_H_

struct Pixel {
		Pixel(uint16_t x, uint16_t y) {
			this->x = x;
			this->y = y;
		}

		uint16_t x;
		uint16_t y;
	};

class PixelMapping {
public:
	virtual Pixel	mapVirtualPixelToPhysicalPixel(Pixel input) = 0;
};

class SimplePixelMapping : public PixelMapping {
public:
	SimplePixelMapping(uint8_t panelCount, uint16_t panelWidth, uint16_t panelHeight);

	Pixel	mapVirtualPixelToPhysicalPixel(Pixel input);
private:
	uint8_t	panelCount;
	uint16_t panelWidth;
	uint16_t panelHeight;
};

class LeftToRightPixelMapping : public PixelMapping {
public:
	LeftToRightPixelMapping(uint8_t panelCount, uint16_t panelWidth, uint16_t panelHeight) ;

	Pixel	mapVirtualPixelToPhysicalPixel(Pixel input) ;
private:
	uint8_t	panelCount;
	uint16_t panelWidth;
	uint16_t panelHeight;
};

class SnakePixelMappingFedBottomRight : public PixelMapping {
public:
	SnakePixelMappingFedBottomRight(uint8_t panelCount, uint16_t panelWidth, uint16_t panelHeight) ;
	Pixel	mapVirtualPixelToPhysicalPixel(Pixel input) ;
private:
	uint8_t	panelCount;
	uint16_t panelWidth;
	uint16_t panelHeight;
};

#endif /* INC_PIXELMAPPING_H_ */
