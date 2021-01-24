/*
 * Protocol.h
 *
 *  Created on: Jan 23, 2021
 *      Author: benvh
 */

#ifndef MAIN_PROTOCOL_H_
#define MAIN_PROTOCOL_H_

#define NETWORK_PACKET_SIZE	2048

#define PROTOCOL_HEADER 3

constexpr int MESSAGE_BODY_BYTES = NETWORK_PACKET_SIZE - PROTOCOL_HEADER;

#define MESSAGE_DELAY_MS 10

#define COMMIT_DELAY_MS 10

#define BYTES_TO_UINT16(bytes) (bytes[0] << 8 | bytes[1])
#define BYTES_TO_UINT16(byteH, byteL) (byteH << 8 | byteL)

#define UINT16_TO_HBYTE(i) ((uint8_t) (i >> 8))
#define UINT16_TO_LBYTE(i) ((uint8_t) (i & 0xFF))

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

#define CONFIGURATION_VERSION 1

enum ConfigurationDisplayType {
	Matrix = 1,
	WS2812Strand = 2,
};

struct __attribute__((__packed__)) ConfigurationDefinition {
	uint8_t version;
	uint8_t displayType;
	uint8_t widthH;
	uint8_t widthL;
	uint8_t heightH;
	uint8_t heightL;
	uint8_t elements;
	uint8_t pixelMappingType;
};

#endif /* MAIN_PROTOCOL_H_ */
