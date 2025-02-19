/*
 * Server.cpp
 *
 *  Created on: Apr 4, 2021
 *      Author: benvh
 */

#include "esp_http_server.h"

// #include "freertos/queue.h"
#include <string.h>

#include <array>

#include "CommandInterface.h"
#include "ServerExternal.h"
#include "Server.h"
#include "esp_log.h"

static httpd_handle_t _server;

static const char* TAG = "Server";
static const char* CONTENT = "Henlo";
static Server server;

void start_http_server(CommandInterface* itf){
	server.StartServer(itf);
}

static esp_err_t get_handler(httpd_req_t* req) {
    httpd_resp_set_hdr(req, "Content-Type", "text/plain");

    httpd_resp_send(req, CONTENT, strlen(CONTENT));

    return ESP_OK;
}

static esp_err_t particle_handler(httpd_req_t* req) {
    if (req->user_ctx != NULL) {
        Server* server = (Server*)req->user_ctx;

        return server->particle_handler(req);
    } else {
        httpd_resp_send_500(req);

		return ESP_OK;
    }
}

static esp_err_t state_handler(httpd_req_t* req) {
    if (req->user_ctx != NULL) {
        Server* server = (Server*)req->user_ctx;

        return server->state_handler(req);
    } else {
        httpd_resp_send_500(req);

		return ESP_OK;
    }
}

static esp_err_t color_handler(httpd_req_t* req) {
    if (req->user_ctx != NULL) {
        Server* server = (Server*)req->user_ctx;

        return server->color_handler(req);
    } else {
        httpd_resp_send_500(req);

		return ESP_OK;
    }
}

static httpd_uri_t particle_handlers[] = {
    {.uri = "/ws",
     .method = HTTP_GET,
     .handler = get_handler,
     .user_ctx = NULL},
    {.uri = "/particle",
     .method = HTTP_POST,
     .handler = particle_handler,
     .user_ctx = NULL},
    {.uri = "/particle",
     .method = HTTP_DELETE,
     .handler = particle_handler,
     .user_ctx = NULL},
    {.uri = "/state",
     .method = HTTP_POST,
     .handler = state_handler,
     .user_ctx = NULL},
    {.uri = "/color",
     .method = HTTP_POST,
     .handler = color_handler,
     .user_ctx = NULL},
};

void Server::StartServer(CommandInterface* itf) {
	interface_ = itf;

    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.lru_purge_enable = true;

    // Start the httpd server
    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    if (httpd_start(&_server, &config) == ESP_OK) {
        // Set URI handlers
        ESP_LOGI(TAG, "Registering URI handlers");

        for (auto& uri : particle_handlers) {
            uri.user_ctx = this;

            httpd_register_uri_handler(_server, &uri);
        }

    } else {
        ESP_LOGI(TAG, "Error starting server!");
    }
    //	    return NULL;
}

esp_err_t Server::particle_handler(httpd_req_t* req) {
    httpd_resp_set_hdr(req, "Content-Type", "text/plain");

    httpd_resp_send(req, CONTENT, strlen(CONTENT));

    ESP_LOGI(TAG, "Particle request: %d", req->method);

    switch (req->method) {
        case HTTP_DELETE:
            interface_->dec();
            break;
        case HTTP_POST:
            interface_->inc();
            break;
    }

    return ESP_OK;
}

esp_err_t Server::state_handler(httpd_req_t* req) {
    httpd_resp_set_hdr(req, "Content-Type", "text/plain");

    httpd_resp_send(req, CONTENT, strlen(CONTENT));

    ESP_LOGI(TAG, "Randomize request: %d", req->method);

    switch (req->method) {
        case HTTP_POST:
            interface_->randomize();
            break;
    }

    return ESP_OK;
}

esp_err_t Server::color_handler(httpd_req_t* req) {
    httpd_resp_set_hdr(req, "Content-Type", "text/plain");

    httpd_resp_send(req, CONTENT, strlen(CONTENT));

    ESP_LOGI(TAG, "Color request: %d - %d body bytes", req->method, req->content_len);

    switch (req->method) {
        case HTTP_POST:
            interface_->color_data(NULL);
            break;
    }

    return ESP_OK;
}