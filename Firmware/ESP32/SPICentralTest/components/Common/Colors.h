/*
 * Colors.h
 *
 *  Created on: Jan 24, 2021
 *      Author: benvh
 */

#ifndef MAIN_COLORS_H_
#define MAIN_COLORS_H_

#include <stdint.h>
#include "esp_system.h"

void random_rgb_uint8_t(uint8_t *rgb) {
	uint8_t h = (uint8_t) esp_random();
	uint8_t s = (uint8_t) esp_random();
	uint8_t v = (uint8_t) esp_random();

	uint8_t r, g, b;

	if (s == 0) {
		r = v;
		g = v;
		b = v;
	} else {
		uint8_t region = h / 43;
		uint8_t remainder = (h % 43) * 6;

		uint8_t p = (v * (255 - s)) >> 8;
		uint8_t q = (v * (255 - ((s * remainder) >> 8))) >> 8;
		uint8_t t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

		switch (region) {
		case 0:
			r = v;
			g = t;
			b = p;
			break;
		case 1:
			r = q;
			g = v;
			b = p;
			break;
		case 2:
			r = p;
			g = v;
			b = t;
			break;
		case 3:
			r = p;
			g = q;
			b = v;
			break;
		case 4:
			r = t;
			g = p;
			b = v;
			break;
		default:
			r = v;
			g = p;
			b = q;
			break;
		}
	}

	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
}

void random_rgbw_uint8_t(uint8_t *rgbw) {
	random_rgb_uint8_t(rgbw);
	rgbw[4] = 0;
}

#endif /* MAIN_COLORS_H_ */
