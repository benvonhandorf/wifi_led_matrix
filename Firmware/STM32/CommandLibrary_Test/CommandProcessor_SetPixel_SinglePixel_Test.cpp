#include "catch.hpp"
#include "Protocol.h"
#include "Request.h"
#include "CommandProcessor.h"
#include "TestDisplay.h"

#include <string.h>

//TEST_CASE("Command Processing - Pixel Data - Single Pixel") {
//	CommandProcessor underTest;
//
//	Request input;
//
//	input.type = RequestType::SetPixelData;
//	uint8_t source[] = { 0x00, 0x01, 0x02, 0x03, 0xF7, 0x55, 0x22, 0x11 };
//	input.bodyLength = 8;
//
//	memcpy(input.body, source, input.bodyLength);
//
//	TestDisplay output;
//
//	underTest.ProcessRequest(&input, &output);
//
//	SECTION("One pixel into display") {
//		REQUIRE(output.pixelCount == 1);
//		REQUIRE(output.swapCount == 0);
//	}
//
//	PixelResult pixel = output.pixels.at(0);
//
//	SECTION("Pixel is at correct coordinates") {
//		REQUIRE(pixel.x == 1);
//		REQUIRE(pixel.y == 0x0203);
//	}
//
//	SECTION("Pixel color values are correct") {
//		REQUIRE(pixel.r == 0xF7);
//		REQUIRE(pixel.g == 0x55);
//		REQUIRE(pixel.b == 0x22);
//		REQUIRE(pixel.w == 0x11);
//	}
//}

