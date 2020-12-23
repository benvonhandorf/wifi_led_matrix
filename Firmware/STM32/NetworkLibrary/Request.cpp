/*
 * Request.cpp
 *
 *  Created on: Dec 6, 2020
 *      Author: benvh
 */

#include "Protocol.h"
#include "Request.h"
#include <string.h>

Request::Request() {

}

Request::~Request() {

}

bool Request::Parse(uint8_t *data, uint16_t dataLength) {
	if (dataLength < 3 || data == 0) {
		return false;
	}

	type = data[0];
	bodyLength = (data[1] << 8) | data[2];

	memcpy(this->body, data + 3, bodyLength);

	switch (type) {
	case RequestType::SetPixelData:
		return ParseSetPixelDataRequest();
	}

	return true;
}

bool Request::ParseSetPixelDataRequest() {
	if (bodyLength % 4 != 0 || bodyLength == 4) {
		return false;
	}

	return true;
}
