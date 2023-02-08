#include <stdint.h>
#include "PixelMapping.hpp"

SimplePixelMapping::SimplePixelMapping(uint8_t panelCount, uint16_t panelWidth, uint16_t panelHeight) {
		this->panelCount = panelCount;
		this->panelWidth = panelWidth;
		this->panelHeight = panelHeight;
	}


Pixel	SimplePixelMapping::mapVirtualPixelToPhysicalPixel(Pixel input) {
	input.y += input.x / panelWidth;
	input.x = input.x % panelWidth;

	return input;
}

LeftToRightPixelMapping::LeftToRightPixelMapping(uint8_t panelCount, uint16_t panelWidth, uint16_t panelHeight) {
	this->panelCount = panelCount;
	this->panelWidth = panelWidth;
	this->panelHeight = panelHeight;
}


Pixel	LeftToRightPixelMapping::mapVirtualPixelToPhysicalPixel(Pixel input) {
	input.y += input.x / panelWidth;
	input.x = input.x % panelWidth;

	//Panel counted from top-left
	uint16_t panel = input.y / panelHeight;
	uint16_t lineOnPanel = input.y % panelHeight;

	if(panel % 2 == 1) {
		//Odd panels are vertically reversed
		lineOnPanel = panelHeight - lineOnPanel;
	}

	uint16_t xOffset = (panelCount - 1) - panel * panelWidth;

	Pixel output(
		(uint16_t) (xOffset + input.x),
		lineOnPanel
	);

	return output;
}


SnakePixelMappingFedBottomRight::SnakePixelMappingFedBottomRight(uint8_t panelCount, uint16_t panelWidth, uint16_t panelHeight) {
	this->panelCount = panelCount;
	this->panelWidth = panelWidth;
	this->panelHeight = panelHeight;
}

Pixel	SnakePixelMappingFedBottomRight::mapVirtualPixelToPhysicalPixel(Pixel input) {
	//Panel counted from top-left
	input.y += input.x / panelWidth;
	input.x = input.x % panelWidth;

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

	Pixel output( x,
		lineOnPanel
	);

	return output;
}
