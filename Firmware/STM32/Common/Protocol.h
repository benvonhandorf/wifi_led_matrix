/*
 * Protocol.h
 *
 *  Created on: Dec 6, 2020
 *      Author: benvh
 */

#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <stdint.h>

#define NETWORK_PACKET_MAXIMUM_SIZE	1024

//Multi-byte entities are sent in network byte order

/**
 * Frame Layout:
 * Frame Type: 1 byte
 * Data Length: 2 bytes - length of frame data, not including type and data length.
 * Data: 0-n bytes, limitations defined by frame type
 */

enum RequestType : uint8_t {
	/**
	 * Assign pixel data
	 * Coordinate Data: 2 + 2 bytes
	 * Pixel data: 4 bytes per pixel specified
	 *
	 * Total length minus 7 must be evenly divisible by 4.
	 *
	 * Frame Data:
	 * uint16_t	starting x coordinate
	 * uint16_t starting y coordinate
	 * [uint8_t r uint8_t g uint8_t b uint8_t w] RGBW data for each pixel
	 *
	 * Multiple pixels can be provided at once, up to the limit of the maxumum network frame size.
	 *
	 */
	SetPixelData = 0x01,

	/**
	 * Commit assigned pixel data to the display.
	 */
	Commit = 0x02,

	/**
	 * Clear all pixel data and assign the specified values to the designated positions.
	 * Pixel data: 8 bytes per pixel specified
	 *
	 * Total length minus 7 must be evenly divisible by 8.
	 *
	 * Frame Data:
	 * [uint16_t x, uint16_t y uint8_t r uint8_t g uint8_t b uint8_t w] Position and RGBW data for each pixel
	 */
	ClearAssignPixelData = 0x03,

	/**
	 * Assign the specified values to the designated positions.
	 * Pixel data: 8 bytes per pixel specified
	 *
	 * Total length minus 7 must be evenly divisible by 8.
	 *
	 * Frame Data:
	 * [uint16_t x, uint16_t y uint8_t r uint8_t g uint8_t b uint8_t w] Position and RGBW data for each pixel
	 */
	AssignPixelData = 0x04,

	/***
	 * Reconfigure the output device with the supplied data.
	 */
	Configure = 0x80
};

#endif /* PROTOCOL_H_ */
