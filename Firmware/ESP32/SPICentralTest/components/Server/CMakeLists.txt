idf_component_register(SRCS "Server.cpp"
                       INCLUDE_DIRS "."
                       REQUIRES mbedtls Common esp_http_server)