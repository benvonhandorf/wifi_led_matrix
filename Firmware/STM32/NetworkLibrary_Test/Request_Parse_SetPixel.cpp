/*
 * Request_Parse_SetPixel.cpp
 *
 *  Created on: Dec 6, 2020
 *      Author: benvh
 */


#include "catch.hpp"
#include "Protocol.h"
#include "Request.h"

TEST_CASE("Request Parsing - SetPixelData") {
	Request underTest;

	SECTION("Only x and y - fails parsing") {
		uint8_t	data[] = {RequestType::SetPixelData,
				0x00, 0x04, //Length
		0x00, 0x00, //x
		0x00, 0x00, //y
		};

		uint16_t length = 7;

		REQUIRE_FALSE(underTest.Parse(data, length));
	}

	SECTION("One pixel of data - parses successfully") {
		uint8_t	data[] = {RequestType::SetPixelData,
				0x00, 0x08, //Length
		0x00, 0x00, //x
		0x00, 0x00, //y
		0x7F, //r
		0x10, //g
		0x07, //b
		0x02 //w
		};

		uint16_t length = 11;

		REQUIRE(underTest.Parse(data, length));
		REQUIRE(underTest.type == RequestType::SetPixelData);
		REQUIRE(underTest.bodyLength == 8);
		uint16_t x = underTest.body[0] << 8 | underTest.body[1];
		uint16_t y = underTest.body[2] << 8 | underTest.body[3];
		REQUIRE(x == 0);
		REQUIRE(y == 0);
		REQUIRE(underTest.body[4] == 0x7F);
	}

	SECTION("Two pixel of data - parses successfully") {
		uint8_t	data[] = {RequestType::SetPixelData,
				0x00, 12, //Length
		0x00, 0x00, //x
		0x00, 0x00, //y
		0x7F, //r
		0x10, //g
		0x07, //b
		0x02, //w
		0x7F, //r
		0x10, //g
		0x07, //b
		0x02 //w
		};

		uint16_t length = 15;

		REQUIRE(underTest.Parse(data, length));
		REQUIRE(underTest.type == RequestType::SetPixelData);
		REQUIRE(underTest.bodyLength == 12);
		uint16_t x = underTest.body[0] << 8 | underTest.body[1];
		uint16_t y = underTest.body[2] << 8 | underTest.body[3];
		REQUIRE(x == 0);
		REQUIRE(y == 0);
		REQUIRE(underTest.body[8] == 0x7F);
		REQUIRE(underTest.body[8] == 0x7F);
	}
}



