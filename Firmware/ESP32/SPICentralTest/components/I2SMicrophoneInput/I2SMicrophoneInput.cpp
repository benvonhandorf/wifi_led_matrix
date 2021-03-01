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

uint8_t data[BUFFER_SAMPLES * 4] = {0};

float tone[BUFFER_SAMPLES];

//int16_t i2s_data(uint8_t *data) {
//	return ((uint16_t) data[4] << 8) | data[3];
//}

//float dsp_sin_cos[512];
float fft_buffer[BUFFER_SAMPLES * 2];
float hann_window[BUFFER_SAMPLES];
//char output[100];

float x1[BUFFER_SAMPLES];
float x2[BUFFER_SAMPLES];

//float y_cf[BUFFER_SAMPLES*2];
// Pointers to result arrays
float* y1_cf = &fft_buffer[0];
float* y2_cf = &fft_buffer[BUFFER_SAMPLES]; //We reuse the second half of the array since after the FFT anything at sampling rate / 2 or greater is useless.  Nyquist.


//constexpr int result_hz_per_bucket = (SAMPLE_RATE / 2) / RESULT_BUCKETS;


void i2sMicrophoneInputTask(void *pvParameters) {

	ESP_ERROR_CHECK(i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL));
	ESP_ERROR_CHECK(i2s_set_pin(I2S_NUM_0, &pin_config));

	ESP_ERROR_CHECK(dsps_fft2r_init_fc32(NULL, CONFIG_DSP_MAX_FFT_SIZE));
	dsps_wind_hann_f32(hann_window, BUFFER_SAMPLES);

	size_t bytes_read;

	float hzPerBucket = ((float)SAMPLE_RATE)/BUFFER_SAMPLES;

	ESP_LOGI("MIC_TASK", "%f", hzPerBucket);

	while (1) {
		ESP_ERROR_CHECK(
				i2s_read(I2S_NUM_0, data, BUFFER_SAMPLES * 4, &bytes_read, 100 * portTICK_RATE_MS));

		float mean = 0.0f;
		float peak = 0.0f;

		for (uint32_t i = 0; i < BUFFER_SAMPLES; i++) {
			uint32_t msb_index = (i * 4);
			int16_t value = data[msb_index + 3] << 8 | data[msb_index + 2];

			mean += value;

			if(value > peak) {
				peak = value;
			}

			fft_buffer[(i * 2)] = value * hann_window[i];
			fft_buffer[(i * 2) + 1] = 0.0f;//Complex portion
		}

		mean /= BUFFER_SAMPLES;

		for (uint32_t i = 0; i < BUFFER_SAMPLES; i++) {
			fft_buffer[(i * 2)] -= mean;
		}

		ESP_LOGI("MIC_TASK", "Sample mean: %f Peak %f over %d bytes", mean, peak, bytes_read);

		ESP_ERROR_CHECK(
				dsps_fft2r_fc32(fft_buffer, BUFFER_SAMPLES));

		ESP_ERROR_CHECK(dsps_bit_rev_fc32(fft_buffer, BUFFER_SAMPLES));

		ESP_ERROR_CHECK(dsps_cplx2reC_fc32(fft_buffer, BUFFER_SAMPLES));

		for (uint32_t i = 0; i < (BUFFER_SAMPLES / 2); i++) {
			float combined = 10 * log10f(((fft_buffer[(i * 2)] * fft_buffer[(i * 2)]) + (fft_buffer[(i * 2) +1] * fft_buffer[(i * 2) +1])) / BUFFER_SAMPLES);

			fft_buffer[i] = combined;
		}

		mean = 0.0f;
		peak = 0.0f;
		float min = 0.0f;

		for (uint32_t i = 0; i < BUFFER_SAMPLES / 2; i++) {
			mean += y1_cf[i];
			if(fft_buffer[i] > peak) {
				peak = fft_buffer[i];
			}
			if(fft_buffer[i] < min) {
				min = fft_buffer[i];
			}
		}

		mean /= BUFFER_SAMPLES;

//		dsps_view(fft_buffer, BUFFER_SAMPLES/2, 64, 10,  -20.0f, 0.0f, '|');

		ESP_LOGI("MIC_TASK", "Mean: %f Peak: %f Min: %f", mean, peak, min);

		vTaskDelay(1 * portTICK_PERIOD_MS);
	}
}
