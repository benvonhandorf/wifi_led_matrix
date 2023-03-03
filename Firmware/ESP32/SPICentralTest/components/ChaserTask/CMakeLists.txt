idf_component_register(SRCS "ChaserTask.cpp"
                       INCLUDE_DIRS "."
                       REQUIRES mbedtls Common driver esp_system esp_hw_support)