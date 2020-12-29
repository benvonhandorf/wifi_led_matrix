/*
 * Request.h
 *
 *  Created on: Dec 6, 2020
 *      Author: benvh
 */

#ifndef REQUEST_H_
#define REQUEST_H_

#include <stdint.h>
#include "Protocol.h"

class Request {
public:
	Request();
	virtual ~Request();

	bool Parse(uint8_t *data, uint16_t length);

	uint8_t type;
	uint16_t bodyLength;
	uint8_t body[NETWORK_PACKET_MAXIMUM_SIZE];

private:
	bool ParseSetPixelDataRequest();
	bool ParseClearPixelDataRequest();
};

#endif /* REQUEST_H_ */
