#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"

esp_err_t event_handler(void *ctx, system_event_t *event) {
	return ESP_OK;
}

#define PIN_NUM_MISO 19
#define PIN_NUM_MOSI 23
#define PIN_NUM_CLK  18
#define PIN_NUM_CS   5

uint8_t txBuffer[1024];
uint8_t rxBuffer[1024];

void write_strand(spi_device_handle_t *spi, uint16_t x, uint16_t pixels,
		uint8_t *values) {
	spi_transaction_t txTrans = {

	};

	uint16_t offset = 0;

	txBuffer[offset++] = 0x01;
	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0x00;

	txBuffer[offset++] = x / 256;
	txBuffer[offset++] = x % 256;
	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0x00;

	uint16_t valueOffset = 0;

	for (uint16_t i = 0; i < pixels; i++) {
		txBuffer[offset++] = values[valueOffset++];
		txBuffer[offset++] = values[valueOffset++];
		txBuffer[offset++] = values[valueOffset++];
		txBuffer[offset++] = values[valueOffset++];
	}

	uint16_t bodyBytes = offset - 3;
	txBuffer[1] = ((uint8_t) (bodyBytes / 256));
	txBuffer[2] = ((uint8_t) (bodyBytes % 256));

	txTrans.rx_buffer = NULL;
	txTrans.tx_buffer = txBuffer;
	txTrans.length = 263 * 8;
	txTrans.rxlength = 0;

	esp_err_t ret;

	ESP_LOGI("StrandTask", "Data: %d - %d - %d  %d", x, txBuffer[1],
			txBuffer[2], bodyBytes);

	ret = spi_device_polling_transmit(*spi, &txTrans);
	ESP_ERROR_CHECK(ret);
}

void commit_strand(spi_device_handle_t *spi) {
	uint16_t offset = 0;
	txBuffer[offset++] = 0x02;
	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0x00;

	spi_transaction_t txTrans = {

	};

	txTrans.tx_buffer = txBuffer;
	txTrans.rx_buffer = NULL;
	txTrans.length = 263 * 8;
	txTrans.rxlength = 0;

	esp_err_t ret;

	ESP_LOGI("StrandTask", "Commit");

	ret = spi_device_polling_transmit(*spi, &txTrans);
	ESP_ERROR_CHECK(ret);
}

typedef struct {
	int16_t position;
	int8_t velocity;
	uint8_t color[4];
} Particle;

#define PARTICLES 4

Particle particles[PARTICLES];

void assign_strand(spi_device_handle_t *spi) {
	spi_transaction_t txTrans = {

	};

	uint16_t offset = 0;

	txBuffer[offset++] = 0x03;
	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0x00;

	for (uint16_t particleIndex = 0; particleIndex < PARTICLES;
			particleIndex++) {
		Particle *particle = particles + particleIndex;

		for(uint8_t tail = 0; tail < 8; tail++) {
			int16_t direction = particle->velocity > 0 ? -1 : 1;
			int16_t position = particle->position + (tail * direction );

			if(position > 0 && position < 300) {
				txBuffer[offset++] = position / 256;
				txBuffer[offset++] = position % 256;
				txBuffer[offset++] = 0x00;
				txBuffer[offset++] = 0x00;
				txBuffer[offset++] = particle->color[0] / (tail + 1);
				txBuffer[offset++] = particle->color[1] / (tail + 1);
				txBuffer[offset++] = particle->color[2] / (tail + 1);
				txBuffer[offset++] = particle->color[3] / (tail + 1);
			}
		}
	}

	uint16_t bodyBytes = offset - 3;
	txBuffer[1] = ((uint8_t) (bodyBytes / 256));
	txBuffer[2] = ((uint8_t) (bodyBytes % 256));

	txTrans.rx_buffer = NULL;
	txTrans.tx_buffer = txBuffer;
	txTrans.length = 263 * 8;
	txTrans.rxlength = 0;

	esp_err_t ret;

	ret = spi_device_polling_transmit(*spi, &txTrans);
	ESP_ERROR_CHECK(ret);
}

void strandTask(void *pvParameters) {
	ESP_LOGI("StrandTask", "Task start");

	uint8_t particleIndex = 0;
	uint32_t velocityRandom;

	particles[particleIndex].position = 0;
	velocityRandom = esp_random();
	particles[particleIndex].velocity = ((int8_t) velocityRandom & 0x7) * (velocityRandom & 0x80 ? -1 : 1) ;
	particles[particleIndex].velocity = particles[particleIndex].velocity ? particles[particleIndex].velocity : 1;
	esp_fill_random(particles[particleIndex].color, 4);
	particles[particleIndex].color[3] /= 8;

	particleIndex++;

	particles[particleIndex].position = 0;
	velocityRandom = esp_random();
	particles[particleIndex].velocity = ((int8_t) velocityRandom & 0x7) * (velocityRandom & 0x80 ? -1 : 1) ;
	particles[particleIndex].velocity = particles[particleIndex].velocity ? particles[particleIndex].velocity : 1;
	esp_fill_random(particles[particleIndex].color, 4);
	particles[particleIndex].color[3] /= 8;

	particleIndex++;

	particles[particleIndex].position = 0;
	velocityRandom = esp_random();
	particles[particleIndex].velocity = ((int8_t) velocityRandom & 0x7) * (velocityRandom & 0x80 ? -1 : 1) ;
	particles[particleIndex].velocity = particles[particleIndex].velocity ? particles[particleIndex].velocity : 1;
	esp_fill_random(particles[particleIndex].color, 4);
	particles[particleIndex].color[3] /= 8;

	particleIndex++;

	particles[particleIndex].position = 0;
	velocityRandom = esp_random();
	particles[particleIndex].velocity = ((int8_t) velocityRandom & 0x7) * (velocityRandom & 0x80 ? -1 : 1) ;
	particles[particleIndex].velocity = particles[particleIndex].velocity ? particles[particleIndex].velocity : 1;
	esp_fill_random(particles[particleIndex].color, 4);
	particles[particleIndex].color[3] /= 8;

	esp_err_t ret;

	gpio_config_t gpio_conf = {
		.pin_bit_mask = 1 << 4,
		.mode = GPIO_MODE_OUTPUT };

	ESP_ERROR_CHECK(gpio_config(&gpio_conf));
	ESP_ERROR_CHECK(gpio_set_level(4, 0));

	spi_device_handle_t spi;
	spi_bus_config_t buscfg = {
		.miso_io_num = PIN_NUM_MISO,
		.mosi_io_num =
		PIN_NUM_MOSI,
		.sclk_io_num = PIN_NUM_CLK,
		.quadwp_io_num = -1,
		.quadhd_io_num = -1 };
	spi_device_interface_config_t devcfg = {
		.clock_speed_hz = (APB_CLK_FREQ / 20), //SPI_MASTER_FREQ_8M,
		.mode = 0,          //SPI mode 0
		.spics_io_num = PIN_NUM_CS, //CS pin
		.queue_size = 1,
		.command_bits = 0,
		.address_bits = 0,
		.dummy_bits = 0 };

	spi_transaction_t txTrans = {

	};
	//Initialize the SPI bus
	ret = spi_bus_initialize(SPI3_HOST, &buscfg, 2);
	ESP_ERROR_CHECK(ret);
	//Attach the LCD to the SPI bus
	ret = spi_bus_add_device(SPI3_HOST, &devcfg, &spi);
	ESP_ERROR_CHECK(ret);

	uint16_t shift = 0;
	uint16_t pixels = 64;
	uint8_t pixelData[4 * pixels];

	while (1) {
		ESP_LOGI("StrandTask", "Loop, shift %d", shift);

		for (particleIndex = 0; particleIndex < PARTICLES; particleIndex++) {
			particles[particleIndex].position +=
					particles[particleIndex].velocity;
			if (particles[particleIndex].position < -10) {
				velocityRandom = esp_random();
				if((velocityRandom & 0x3) == 0x3) {
					particles[particleIndex].velocity -= 1;
					particles[particleIndex].velocity = particles[particleIndex].velocity ? particles[particleIndex].velocity : -1;
				} else if ((velocityRandom & 0x1) == 0x1) {
					particles[particleIndex].velocity += 1;
					particles[particleIndex].velocity = particles[particleIndex].velocity ? particles[particleIndex].velocity : 1;
				}

				particles[particleIndex].position = 300;

			} else if (particles[particleIndex].position > 310) {
				velocityRandom = esp_random();
				if((velocityRandom & 0x3) == 0x3) {
					particles[particleIndex].velocity -= 1;
					particles[particleIndex].velocity = particles[particleIndex].velocity ? particles[particleIndex].velocity : -1;
				} else if ((velocityRandom & 0x1) == 0x1) {
					particles[particleIndex].velocity += 1;
					particles[particleIndex].velocity = particles[particleIndex].velocity ? particles[particleIndex].velocity : 1;
				}


				particles[particleIndex].position = 0;
			}
		}

		assign_strand(&spi);

		vTaskDelay(20 / portTICK_PERIOD_MS);

		ESP_ERROR_CHECK(gpio_set_level(4, 1));
		commit_strand(&spi);
		ESP_ERROR_CHECK(gpio_set_level(4, 0));

		vTaskDelay(20 / portTICK_PERIOD_MS);

		shift++;
	}
}

void app_main(void) {
	nvs_flash_init();
	tcpip_adapter_init();
	ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));
	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT()
	;
	ESP_ERROR_CHECK(esp_wifi_init(&cfg));
	ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
	wifi_config_t sta_config = {
		.sta = {
			.ssid = CONFIG_ESP_WIFI_SSID,
			.password = CONFIG_ESP_WIFI_PASSWORD,
			.bssid_set = false } };
	ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &sta_config));
	ESP_ERROR_CHECK(esp_wifi_start());
	ESP_ERROR_CHECK(esp_wifi_connect());

	ESP_LOGI("main", "Before task creation");

	xTaskHandle taskHandle;

	xTaskCreatePinnedToCore(strandTask, "StrandTask", 10000, NULL,
	tskIDLE_PRIORITY + 10, &taskHandle, 1);

	ESP_LOGI("main", "Before scheduler start");

	while (1) {
		vTaskDelay(5000 / portTICK_PERIOD_MS);
	}

	ESP_LOGI("main", "After scheduler start");
}

