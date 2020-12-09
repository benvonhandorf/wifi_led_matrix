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
	length = (data[1] << 8) | data[2];

	if (length != dataLength - 3) {
		return false;
	}

	memcpy(this->data, data + 3, length);

	switch (type) {
	case RequestType::SetPixelData:
		return ParseSetPixelData();
	}

	return true;
}

bool Request::ParseSetPixelData() {
	if (length % 4 != 0 || length == 4) {
		return false;
	}

	return true;
}
