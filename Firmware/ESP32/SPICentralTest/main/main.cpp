#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"

#include "string.h"

#include "DisplayBuffer.h"
#include "TaskParameters.h"
#include "DisplayTask.h"

//#include "MatrixTask.h"
#include "ChaserTask.h"
#include "ControlTask.h"
#include "I2SMicrophoneInput.h"
#include "PerformanceCounters.h"

#include "esp_netif_ip_addr.h"

#include "Server.h"

esp_err_t event_handler(void *ctx, system_event_t *event) {
	return ESP_OK;
}

#define PIN_NUM_MISO 19
#define PIN_NUM_MOSI 23
#define PIN_NUM_CLK  18
#define PIN_NUM_CS   5

struct TaskParameters taskParameters;

static Configuration deviceConfiguration;

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
		.queue_size = 1, };

	//Initialize the SPI bus
	ret = spi_bus_initialize(SPI3_HOST, &buscfg, 2);
	ESP_ERROR_CHECK(ret);
	//Attach the LCD to the SPI bus
	ret = spi_bus_add_device(SPI3_HOST, &devcfg, &taskParameters.spiDevice);
	ESP_ERROR_CHECK(ret);
}

static void disconnect_handler(void* esp_netif, esp_event_base_t event_base,
                               int32_t event_id, void* event_data) {
	ESP_LOGI("MAIN", "Disconnected");
}

static void connect_handler(void* esp_netif, esp_event_base_t event_base,
                            int32_t event_id, void* event_data) {

	ESP_LOGI("MAIN", "Connected");
}

static void gotip_handler(void* esp_netif, esp_event_base_t event_base,
                            int32_t event_id, void* event_data) {

	ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;

	ESP_LOGI("MAIN", "Got IP:" IPSTR, IP2STR(&event->ip_info.ip));

	Server::StartServer();
}

extern "C" void app_main(void) {
	ESP_ERROR_CHECK(nvs_flash_init());
	ESP_ERROR_CHECK(esp_netif_init());

	ESP_ERROR_CHECK(esp_event_loop_create_default());

	ESP_ERROR_CHECK(
			esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP,
					&gotip_handler, NULL));

	ESP_ERROR_CHECK(
			esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_CONNECTED,
					&connect_handler, NULL));

	ESP_ERROR_CHECK(
			esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED,
					&disconnect_handler, NULL));

	esp_netif_create_default_wifi_sta();

	wifi_init_config_t cfg =
				WIFI_INIT_CONFIG_DEFAULT() ;

	ESP_ERROR_CHECK(esp_wifi_init(&cfg));

	ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));

    wifi_config_t sta_config ;
    sta_config.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;
    sta_config.sta.pmf_cfg.capable = true;
    sta_config.sta.pmf_cfg.required = false;

	strncpy((char *)sta_config.sta.ssid, CONFIG_ESP_WIFI_SSID, 32);
	strncpy((char *)sta_config.sta.password, CONFIG_ESP_WIFI_PASSWORD, 64);
//	sta_config.sta.bssid_set = false;
//
//	sta_config.sta.pmf_cfg.capable = false;
//	sta_config.sta.pmf_cfg.required = false;

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &sta_config) );

	ESP_ERROR_CHECK(esp_wifi_start());
	ESP_ERROR_CHECK(esp_wifi_connect());

	ESP_LOGI("main", "Before task creation");

	initializeSpi();

	deviceConfiguration.height = 1;
	deviceConfiguration.width = 300;

	taskParameters.configuration = &deviceConfiguration;

	xTaskHandle displayTaskHandle,
	chaserTaskHandle, controlTaskHandle, micTaskHandle,
			performanceMonitorHandle;

	xTaskCreate(performanceCountersTask, "PerformanceTask", 10000,
			&taskParameters,
			tskIDLE_PRIORITY + 5, &performanceMonitorHandle);

	xTaskCreatePinnedToCore(displayTask, "DisplayTask", 10000, &taskParameters,
	tskIDLE_PRIORITY + 10, &displayTaskHandle, 1);

//	xTaskCreate(chaserTask, "ChaserTask", 10000, &taskParameters,
//	tskIDLE_PRIORITY + 5, &chaserTaskHandle);

	xTaskCreate(i2sMicrophoneInputTask, "MicTask", 10000, NULL,
	tskIDLE_PRIORITY + 5, &micTaskHandle);

//	xTaskCreatePinnedToCore(matrixTask, "MatrixTask", 10000, &taskParameters,
//	tskIDLE_PRIORITY + 10, &taskHandle, 1);

	ESP_LOGI("main", "Before scheduler start");

	while (1) {
		vTaskDelay(50 / portTICK_PERIOD_MS);
	}

	ESP_LOGI("main", "After scheduler start");
}

