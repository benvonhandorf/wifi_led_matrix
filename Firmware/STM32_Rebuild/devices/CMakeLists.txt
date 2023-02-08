cmake_minimum_required(VERSION 3.15.3)

add_library(devices "")

target_include_directories(devices 
    PUBLIC
        inc
)

target_sources(devices
    PUBLIC
        src/LedSingleWire.cpp
        src/MatrixDriver.cpp
)

target_link_libraries(devices 
    PUBLIC
        Core 
        CompilerDefines 
        Common
        DisplayDriverCommon
)