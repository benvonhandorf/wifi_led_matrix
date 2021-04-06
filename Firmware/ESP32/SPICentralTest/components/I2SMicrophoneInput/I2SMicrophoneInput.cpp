/*
 * I2SMicrophoneInput.cpp
 *
 *  Created on: Jan 26, 2021
 *      Author: benvh
 */

#include "I2SMicrophoneInput.h"
#include "driver/i2s.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_event.h"
#include "dsps_wind_hann.h"
#include "dsps_fft2r.h"
#include "dsps_view.h"
#include "dsps_tone_gen.h"
#include <math.h>

#include <string.h>

#include "DisplayBuffer.h"

I2SMicrophoneInput::I2SMicrophoneInput() {
	// TODO Auto-generated constructor stub

}

I2SMicrophoneInput::~I2SMicrophoneInput() {
	// TODO Auto-generated destructor stub
}

#define SAMPLE_RATE 44100

static const i2s_config_t i2s_config = {
	.mode = (i2s_mode_t) (I2S_MODE_MASTER | I2S_MODE_RX),
	.sample_rate = SAMPLE_RATE,
	.bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
	.channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
	.communication_format = I2S_COMM_FORMAT_STAND_I2S,
	.intr_alloc_flags = 0, // default interrupt priority
	.dma_buf_count = 8,
	.dma_buf_len = 256,
	.use_apll = false };

static const i2s_pin_config_t pin_config = {
	.bck_io_num = 21,
	.ws_io_num = 22,
	.data_out_num = I2S_PIN_NO_CHANGE,
	.data_in_num = 27 };

#define BUFFER_SAMPLES 1024

uint8_t data[BUFFER_SAMPLES * 4] = {
	0 };

float tone[BUFFER_SAMPLES];

//int16_t i2s_data(uint8_t *data) {
//	return ((uint16_t) data[4] << 8) | data[3];
//}

//float dsp_sin_cos[512];
float fft_buffer[BUFFER_SAMPLES * 2];
float hann_window[BUFFER_SAMPLES];
//char output[100];

float fft_buffer_previous[BUFFER_SAMPLES / 2];

uint8_t pixel_values[] = {
	0,
	0,
	59,
	93,
	118,
	136,
	152,
	165,
	177,
	187,
	195,
	204,
	211,
	218,
	224,
	230,
	236,
	241,
	246,
	250,
	255 };

void valueToPixel(float val, uint8_t *pixel, float min, float max) {
	float range = (max - min) / 4;
	float mapping = 20 / range;

	if (val > ((3 * range) + min)) {
		val = val - ((3 * range) + min);
		uint8_t lookup = round(val * mapping);
		pixel[2] = pixel_values[lookup];
	} else if (val > ((2 * range) + min)) {
		val = val - ((2 * range) + min);
		uint8_t lookup = round(val * mapping);
		pixel[1] = pixel_values[lookup];
	} else if (val > ((1 * range) + min)) {
		val = val - ((1 * range) + min);
		uint8_t lookup = round(val * mapping);

//		ESP_LOGI("MIC_TASK", "val: %f mapping: %f lookup %d value %d", val,
//				mapping, lookup, pixel_values[lookup]);

		pixel[0] = pixel_values[lookup];
	}
}

void calculate_range(uint16_t buckets, float *min, float *max, float *mean) {
	for (uint32_t i = 0; i < buckets; i++) {
		*mean += fft_buffer[i];

		if (fft_buffer[i] > *max) {
			*max = fft_buffer[i];
		}
		if (fft_buffer[i] < *min) {
			*min = fft_buffer[i];
		}
	}

	*mean /= buckets;

	if (*mean < 15) {
		*mean = 15;
	}

	if (*max < 60) {
		*max = 60;
	}
}

void render_strand_linear(DisplayBuffer *displayBuffer, uint16_t buckets) {
	float min, max, mean;

	calculate_range(buckets, &min, &max, &mean);

	uint8_t pixelsPerBucket = 1; //displayBuffer->width / buckets;
//			pixelsPerBucket = pixelsPerBucket > 0 ? pixelsPerBucket : 1;

	memset(displayBuffer->buffer, 0,
			displayBuffer->width * displayBuffer->height * 4);

	for (uint32_t i = 0; i < buckets; i++) {
		for (uint8_t j = 0; j < pixelsPerBucket; j++) {
			uint16_t offset = ((i * pixelsPerBucket) + j) * 4;

			if (((i * pixelsPerBucket) + j) <= displayBuffer->width) {
				float val = (fft_buffer[i + 10] * 0.8)
						+ (fft_buffer_previous[i + 10] * 0.2);
				fft_buffer_previous[i + 10] = val;

				valueToPixel(val, displayBuffer->buffer + offset, mean, max);
			}
		}
	}

}

void render_strand_center_reflected(DisplayBuffer *displayBuffer,
		uint16_t buckets) {
	float min, max, mean;

	calculate_range(buckets, &min, &max, &mean);

	uint16_t pixels = displayBuffer->width / 2;

	uint8_t pixelsPerBucket = 1; //displayBuffer->width / buckets;
//			pixelsPerBucket = pixelsPerBucket > 0 ? pixelsPerBucket : 1;
	uint8_t buckets_per_pixel = buckets / pixels;

	memset(displayBuffer->buffer, 0,
			displayBuffer->width * displayBuffer->height * 4);

	for (uint32_t bucket = 0; bucket <= (buckets - buckets_per_pixel); bucket +=
			buckets_per_pixel) {
		for (uint8_t j = 0; j < pixelsPerBucket; j++) {

			float val = 0.0;
			for (uint32_t pixelBucket = 0; pixelBucket < buckets_per_pixel;
					pixelBucket++) {
				float pixel_val =
						(fft_buffer[bucket + pixelBucket + 10] * 0.8)
								+ (fft_buffer_previous[bucket + pixelBucket + 10]
										* 0.2);

				fft_buffer_previous[bucket + pixelBucket + 10] = pixel_val;

				val += pixel_val;
			}

			val /= buckets_per_pixel;

			//Set this to the pixels above and below the center

			int16_t pixel = (pixels + ((bucket * pixelsPerBucket) + j));

			int16_t offset = pixel * 4;

			if (pixel >= 0 && pixel < displayBuffer->width) {
				valueToPixel(val, displayBuffer->buffer + offset, mean, max);
			}

			pixel = ((pixels - 1) - ((bucket * pixelsPerBucket) + j));

			offset = pixel * 4;

			if (pixel >= 0 && pixel < displayBuffer->width) {
				valueToPixel(val, displayBuffer->buffer + offset, mean, max);
			}
		}
	}

}

void i2sMicrophoneInputTask(void *pvParameters) {

	ESP_ERROR_CHECK(i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL));
	ESP_ERROR_CHECK(i2s_set_pin(I2S_NUM_0, &pin_config));

	ESP_ERROR_CHECK(dsps_fft2r_init_fc32(NULL, CONFIG_DSP_MAX_FFT_SIZE));
	dsps_wind_hann_f32(hann_window, BUFFER_SAMPLES);

	size_t bytes_read;

	float hzPerBucket = ((float) SAMPLE_RATE) / BUFFER_SAMPLES;

	ESP_LOGI("MIC_TASK", "%f", hzPerBucket);

	memset(fft_buffer_previous, 0, sizeof(fft_buffer_previous));

	while (1) {
		ESP_ERROR_CHECK(
				i2s_read(I2S_NUM_0, data, BUFFER_SAMPLES * 4, &bytes_read, 100 * portTICK_RATE_MS));

		float mean = 0.0f;
		float max = 0.0f;

		for (uint32_t i = 0; i < BUFFER_SAMPLES; i++) {
			uint32_t msb_index = (i * 4);
			int16_t value = data[msb_index + 3] << 8 | data[msb_index + 2];

			mean += value;

			if (value > max) {
				max = value;
			}

			fft_buffer[(i * 2)] = value * hann_window[i];
			fft_buffer[(i * 2) + 1] = 0.0f; //Complex portion
		}

		mean /= BUFFER_SAMPLES;

		//Remove DC Offset
		for (uint32_t i = 0; i < BUFFER_SAMPLES; i++) {
			fft_buffer[(i * 2)] -= mean;
		}

		ESP_ERROR_CHECK(dsps_fft2r_fc32(fft_buffer, BUFFER_SAMPLES));

		ESP_ERROR_CHECK(dsps_bit_rev_fc32(fft_buffer, BUFFER_SAMPLES));

		ESP_ERROR_CHECK(dsps_cplx2reC_fc32(fft_buffer, BUFFER_SAMPLES));

		for (uint32_t i = 0; i < (BUFFER_SAMPLES / 2); i++) {
			//Do the power calculation and reduce the data down into the first
			//half of the array at the same time.
			float combined = 10
					* log10f(
							((fft_buffer[(i * 2)] * fft_buffer[(i * 2)])
									+ (fft_buffer[(i * 2) + 1]
											* fft_buffer[(i * 2) + 1]))
									/ BUFFER_SAMPLES);

			fft_buffer[i] = combined;
		}

		//Sampling at 44kHz, 22kHz but let's take the bottom half of that to make it slightly approximate hearing & music.
		uint16_t buckets = (BUFFER_SAMPLES / 4);

		DisplayBuffer *displayBuffer;

		if (xQueueReceive(AVAILABLE_DISPLAY_BUFFER, &displayBuffer,
		portMAX_DELAY) == pdPASS) {

//			render_strand_linear(displayBuffer, buckets);
			render_strand_center_reflected(displayBuffer, buckets);

			xQueueSend(COMMITTED_DISPLAY_BUFFER, &displayBuffer, portMAX_DELAY);
		} else {
			ESP_LOGW("MIC_TASK", "Failed to obtain display buffer");
		}

//		dsps_view(fft_buffer, BUFFER_SAMPLES/2, 64, 10,  -20.0f, 0.0f, '|');

//		ESP_LOGI("MIC_TASK", "Mean: %f Peak: %f Min: %f Samples: %d", mean, peak, min, buckets);

		vTaskDelay(1 / portTICK_PERIOD_MS);
	}
}
