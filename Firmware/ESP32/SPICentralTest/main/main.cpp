#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"

#include "string.h"

#include "TaskParameters.h"
#include "MatrixTask.h"
#include "StrandTask.h"

esp_err_t event_handler(void *ctx, system_event_t *event) {
	return ESP_OK;
}

#define PIN_NUM_MISO 19
#define PIN_NUM_MOSI 23
#define PIN_NUM_CLK  18
#define PIN_NUM_CS   5

uint8_t txBufferA[2048];
uint8_t txBufferB[2048];

struct TaskParameters taskParameters;

void initializeSpi() {
	esp_err_t ret;

	spi_bus_config_t buscfg = {
		.mosi_io_num =
		PIN_NUM_MOSI,
		.miso_io_num = PIN_NUM_MISO,
		.sclk_io_num = PIN_NUM_CLK,
		.quadwp_io_num = -1,
		.quadhd_io_num = -1 };
	spi_device_interface_config_t devcfg = {
		.command_bits = 0,
				.address_bits = 0,
				.dummy_bits = 0,
				.mode = 0,          //SPI mode 0
				.clock_speed_hz = SPI_MASTER_FREQ_20M,

		.spics_io_num = PIN_NUM_CS, //CS pin
		.queue_size = 1,
		 };

	//Initialize the SPI bus
	ret = spi_bus_initialize(SPI3_HOST, &buscfg, 2);
	ESP_ERROR_CHECK(ret);
	//Attach the LCD to the SPI bus
	ret = spi_bus_add_device(SPI3_HOST, &devcfg, &taskParameters.spiDevice);
	ESP_ERROR_CHECK(ret);
}

extern "C" void app_main(void) {
	nvs_flash_init();
	tcpip_adapter_init();
	ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));
	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT()
	;
	ESP_ERROR_CHECK(esp_wifi_init(&cfg));
	ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
	wifi_config_t sta_config ;
	strncpy((char *)sta_config.sta.ssid, CONFIG_ESP_WIFI_SSID, 32);
	strncpy((char *)sta_config.sta.password, CONFIG_ESP_WIFI_PASSWORD, 64);
	sta_config.sta.bssid_set = false;

	ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &sta_config));
	ESP_ERROR_CHECK(esp_wifi_start());
	ESP_ERROR_CHECK(esp_wifi_connect());

	ESP_LOGI("main", "Before task creation");

	initializeSpi();

	xTaskHandle taskHandle;

	xTaskCreatePinnedToCore(strandTask, "StrandTask", 10000, &taskParameters,
	tskIDLE_PRIORITY + 10, &taskHandle, 1);

//	xTaskCreatePinnedToCore(matrixTask, "MatrixTask", 10000, &taskParameters,
//	tskIDLE_PRIORITY + 10, &taskHandle, 1);

	ESP_LOGI("main", "Before scheduler start");

	while (1) {
		vTaskDelay(50 / portTICK_PERIOD_MS);
	}

	ESP_LOGI("main", "After scheduler start");
}

