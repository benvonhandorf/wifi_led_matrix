/*
 * Server.cpp
 *
 *  Created on: Apr 4, 2021
 *      Author: benvh
 */

#include "Server.h"

#include "esp_http_server.h"

//#include "freertos/queue.h"
#include "esp_log.h"
#include <string.h>
//
//static void i2sMicrophoneInputTask(void *pvParameters) {
//
//}

static httpd_handle_t _server;

static const char* TAG = "Server";
static const char* CONTENT = "Henlo";

static esp_err_t get_handler(httpd_req_t *req) {

	httpd_resp_set_hdr(req, "Content-Type", "text/plain");

	httpd_resp_send(req, CONTENT, strlen(CONTENT));

    return ESP_OK;
}


static const httpd_uri_t get_d = {
        .uri        = "/ws",
        .method     = HTTP_GET,
        .handler    = get_handler,
        .user_ctx   = NULL
};

void Server::StartServer() {
	httpd_config_t config = HTTPD_DEFAULT_CONFIG();
	config.lru_purge_enable = true;

	// Start the httpd server
	ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
	if (httpd_start(&_server, &config) == ESP_OK) {
		// Set URI handlers
		ESP_LOGI(TAG, "Registering URI handlers");
		httpd_register_uri_handler(_server, &get_d);
	} else {
		ESP_LOGI(TAG, "Error starting server!");
	}
//	    return NULL;
}
