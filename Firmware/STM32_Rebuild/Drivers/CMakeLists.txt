cmake_minimum_required(VERSION 3.15.3)

target_include_directories(Core 
    PUBLIC
        CMSIS/Include
        CMSIS/Device/ST/STM32F4xx/Include
        STM32F4xx_HAL_Driver/Inc
)

file(GLOB_RECURSE hal_sources STM32F4xx_HAL_Driver/Src/*.c)

target_sources(Core
    PUBLIC
        ${hal_sources}
)