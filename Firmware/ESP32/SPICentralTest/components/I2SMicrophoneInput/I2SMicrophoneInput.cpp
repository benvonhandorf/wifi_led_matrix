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
#include <math.h>

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
	.channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
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

#define BUFFER_SAMPLES 8192

uint8_t data[BUFFER_SAMPLES * 2 * 4];

int16_t i2s_data(uint8_t *data) {
	return ((uint16_t) data[4] << 8) | data[3];
}

int16_t dsp_sin_cos[512];
int16_t fft_buffer[BUFFER_SAMPLES * 2];
float hann_window[BUFFER_SAMPLES];
char output[100];

#define RESULT_BUCKETS 80
int16_t results[RESULT_BUCKETS];
constexpr int result_hz_per_bucket = (SAMPLE_RATE / 2) / RESULT_BUCKETS;


void i2sMicrophoneInputTask(void *pvParameters) {

	ESP_ERROR_CHECK(i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL));
	ESP_ERROR_CHECK(i2s_set_pin(I2S_NUM_0, &pin_config));

	ESP_ERROR_CHECK(dsps_fft2r_init_sc16(dsp_sin_cos, 512));
	dsps_wind_hann_f32(hann_window, BUFFER_SAMPLES);

	size_t bytes_read;

	float hzPerBucket = ((float)SAMPLE_RATE)/BUFFER_SAMPLES;

	ESP_LOGI("MIC_TASK", "%f", hzPerBucket);

	while (1) {
//		ESP_ERROR_CHECK(
//				i2s_read(I2S_NUM_0, data, BUFFER_SAMPLES * 2 * 4, &bytes_read, 100 * portTICK_RATE_MS));



//		float mean = 0.0f;
//
//		for (uint32_t i = 0; i < BUFFER_SAMPLES; i++) {
//			uint32_t msb_index = (i * 8);
//			int16_t lvalue = data[msb_index + 1] << 8 | data[msb_index + 2];
//
//			mean += lvalue;
//
//			fft_buffer[(i * 2)] = lvalue * hann_window[i];
//			fft_buffer[(i * 2) + 1] = 0;
//		}

		float mean = 0.0f;

		double samples_per_iteration = ((double)SAMPLE_RATE) / 10000;
		double multiplier = (2 * 3.14159) / samples_per_iteration;
		double scale = 500;

		for (uint32_t i = 0; i < BUFFER_SAMPLES; i++) {
			int16_t lvalue = sin(i * multiplier) * scale;
			mean += lvalue;

			fft_buffer[(i * 2)] = lvalue * hann_window[i];
			fft_buffer[(i * 2) + 1] = 0;

			ESP_LOGI("MIC_TASK", "%d - %d", i, lvalue);

			vTaskDelay(1);
		}

		mean /= BUFFER_SAMPLES;

		ESP_LOGI("MIC_TASK", "Sample mean: %f", mean);

		ESP_ERROR_CHECK(
				dsps_fft2r_sc16_ae32_(fft_buffer, BUFFER_SAMPLES, dsp_sin_cos));

		ESP_ERROR_CHECK(dsps_bit_rev_sc16_ansi(fft_buffer, BUFFER_SAMPLES));

		ESP_ERROR_CHECK(dsps_cplx2reC_sc16(fft_buffer, BUFFER_SAMPLES));

		for (uint32_t i = 0; i < RESULT_BUCKETS; i++) {
			results[i] = 0;
		}

		for (uint32_t i = 0; i < (BUFFER_SAMPLES / 2); i++) {
			int16_t combined = ((fft_buffer[(i * 2)] * fft_buffer[(i * 2)]) + (fft_buffer[(i * 2) +1] * fft_buffer[(i * 2) +1])) / BUFFER_SAMPLES;
			int16_t frequency = i * hzPerBucket;

			int16_t frequency_bucket = frequency / result_hz_per_bucket;

			results[frequency_bucket] += combined;
		}

		mean = 0.0f;

		for (uint32_t i = 0; i < RESULT_BUCKETS; i++) {
			mean += results[i];
//			ESP_LOGI("MIC_TASK", "%d - %d\t=\t%d", i, i * result_hz_per_bucket,
//					results[i]);
		}

		mean /= RESULT_BUCKETS;

		ESP_LOGI("MIC_TASK", "Mean: %f", mean);

		vTaskDelay(10 * portTICK_PERIOD_MS);
	}
}
