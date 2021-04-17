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
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &sta_config) );

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
