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

void setup_strand() {
	esp_err_t ret;
	spi_device_handle_t spi;
	spi_bus_config_t buscfg = { .miso_io_num = PIN_NUM_MISO, .mosi_io_num =
	PIN_NUM_MOSI, .sclk_io_num = PIN_NUM_CLK, .quadwp_io_num = -1,
			.quadhd_io_num = -1, .max_transfer_sz = 1024 };
	spi_device_interface_config_t devcfg = { .clock_speed_hz = 1 * 1000 * 1000, //Clock out at 10 MHz
			.mode = 0,                                //SPI mode 0
			.spics_io_num = PIN_NUM_CS,               //CS pin
			.queue_size = 1, .command_bits = 0, .address_bits = 0 };

	spi_transaction_t txTrans = {

	};
	//Initialize the SPI bus
	ret = spi_bus_initialize(SPI3_HOST, &buscfg, 2);
	ESP_ERROR_CHECK(ret);
	//Attach the LCD to the SPI bus
	ret = spi_bus_add_device(SPI3_HOST, &devcfg, &spi);
	ESP_ERROR_CHECK(ret);

	uint16_t offset = 0;

	txBuffer[offset++] = 0x01;
	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0x00;

	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0x00;

	txBuffer[offset++] = 0xFF;
	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0x00;

	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0xFF;
	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0x00;

	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0xFF;
	txBuffer[offset++] = 0x00;

	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0xFF;

	txBuffer[offset++] = 0xFF;
	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0x00;

	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0xFF;
	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0x00;

	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0xFF;
	txBuffer[offset++] = 0x00;

	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0xFF;

	txBuffer[1] = (offset - 3) / 255;
	txBuffer[2] = (offset - 3) % 255;

	txTrans.rx_buffer = rxBuffer;
	txTrans.tx_buffer = txBuffer;
	txTrans.length = offset * 8;
	txTrans.rxlength = txTrans.length;

	ret = spi_device_polling_transmit(spi, &txTrans);
	ESP_ERROR_CHECK(ret);

	vTaskDelay(1000 / portTICK_PERIOD_MS);

	offset = 0;
	txBuffer[offset++] = 0x02;
	txBuffer[offset++] = 0x00;
	txBuffer[offset++] = 0x00;

	txBuffer[1] = (offset - 3) / 255;
	txBuffer[2] = (offset - 3) / 255;

	txTrans.tx_buffer = txBuffer;
	txTrans.length = offset * 8;
	txTrans.rxlength = txTrans.length;

	ret = spi_device_polling_transmit(spi, &txTrans);
	ESP_ERROR_CHECK(ret);

	ESP_LOGI("SPI", "Serial data sent\n");
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
	wifi_config_t sta_config = { .sta = { .ssid = CONFIG_ESP_WIFI_SSID,
			.password = CONFIG_ESP_WIFI_PASSWORD, .bssid_set = false } };
	ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &sta_config));
	ESP_ERROR_CHECK(esp_wifi_start());
	ESP_ERROR_CHECK(esp_wifi_connect());

	setup_strand();

	gpio_set_direction(GPIO_NUM_4, GPIO_MODE_OUTPUT);
	int level = 0;
	while (true) {
		gpio_set_level(GPIO_NUM_4, level);
		level = !level;
		vTaskDelay(300 / portTICK_PERIOD_MS);
	}
}

