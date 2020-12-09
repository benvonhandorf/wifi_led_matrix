/*
 * Request_Parse_SetPixel.cpp
 *
 *  Created on: Dec 6, 2020
 *      Author: benvh
 */



#include "catch.hpp"
#include "Request.h"

TEST_CASE("Request Parsing - Bad inputs") {
	Request underTest;

	SECTION("NULL data") {
		uint8_t	*data = NULL;
		uint16_t length = 10;

		REQUIRE_FALSE(underTest.Parse(data, length));
	}

	SECTION("Zero length") {
		uint8_t	data[] = {0x01,0x00};
		uint16_t length = 0;

		REQUIRE_FALSE(underTest.Parse(data, length));
	}


	SECTION("Two length") {
		uint8_t	data[] = {0x01,0x00};
		uint16_t length = 2;

		REQUIRE_FALSE(underTest.Parse(data, length));
	}

	SECTION("Seven length") {
		uint8_t	data[] = {0x01,0x00,0x00,0x00,0x00,0x00,0x00};
		uint16_t length = 7;

		REQUIRE_FALSE(underTest.Parse(data, length));
	}
}


