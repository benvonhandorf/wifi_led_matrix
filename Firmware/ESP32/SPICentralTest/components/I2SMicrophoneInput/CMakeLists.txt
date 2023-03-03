idf_component_register(SRCS "I2SMicrophoneInput.cpp"
                       INCLUDE_DIRS "."
                       REQUIRES mbedtls Common driver esp_system esp_event freertos esp-dsp)