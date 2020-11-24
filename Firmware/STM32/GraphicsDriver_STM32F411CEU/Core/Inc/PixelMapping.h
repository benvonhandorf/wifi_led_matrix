/*
 * PixelMapping.h
 *
 *  Created on: Nov 22, 2020
 *      Author: benvh
 */

#ifndef INC_PIXELMAPPING_H_
#define INC_PIXELMAPPING_H_

class PixelMapping {
public:
	struct Pixel {
		Pixel(uint16_t x, uint16_t y) {
			this->x = x;
			this->y = y;
		}

		uint16_t x;
		uint16_t y;
	};

	virtual Pixel	mapVirtualPixelToPhysicalPixel(Pixel input) = 0;
};

class SimplePixelMapping : public PixelMapping {
public:
	Pixel	mapVirtualPixelToPhysicalPixel(Pixel input) {
		return input;
	}
};

class LeftToRightPixelMapping : public PixelMapping {
public:
	LeftToRightPixelMapping(uint8_t panelCount, uint16_t panelWidth, uint16_t panelHeight) {
		this->panelCount = panelCount;
		this->panelWidth = panelWidth;
		this->panelHeight = panelHeight;
	}

	Pixel	mapVirtualPixelToPhysicalPixel(Pixel input) {
		//Panel counted from top-left
		uint16_t panel = input.y / panelHeight;
		uint16_t lineOnPanel = input.y % panelHeight;

		if(panel % 2 == 1) {
			//Odd panels are vertically reversed
			lineOnPanel = panelHeight - lineOnPanel;
		}

		uint16_t xOffset = (panelCount - 1) - panel * panelWidth;

		PixelMapping::Pixel output {
			.x= xOffset + input.x,
			.y = lineOnPanel
		};

		return output;
	}
private:
	uint8_t	panelCount;
	uint16_t panelWidth;
	uint16_t panelHeight;
};

class SnakePixelMappingFedBottomRight : public PixelMapping {
public:
	SnakePixelMappingFedBottomRight(uint8_t panelCount, uint16_t panelWidth, uint16_t panelHeight) {
		this->panelCount = panelCount;
		this->panelWidth = panelWidth;
		this->panelHeight = panelHeight;
	}

	Pixel	mapVirtualPixelToPhysicalPixel(Pixel input) {
		//Panel counted from top-left
		uint16_t panel = input.y / panelHeight;
		uint16_t lineOnPanel = input.y % panelHeight;

		uint16_t xOffset = ((panelCount - 1) - panel) * panelWidth;
		uint16_t x;

		if(((panelCount - 1) - panel) % 2 == 1) {
			//Even panels (from feedpoint) are vertically reversed
			lineOnPanel = (panelHeight - 1) - lineOnPanel;
			x = xOffset + input.x;
		} else {
			x= xOffset + ((panelWidth -1) - input.x);
		}

		Pixel output {
			.x= x,
			.y = lineOnPanel
		};

		return output;
	}
private:
	uint8_t	panelCount;
	uint16_t panelWidth;
	uint16_t panelHeight;
};

#endif /* INC_PIXELMAPPING_H_ */
