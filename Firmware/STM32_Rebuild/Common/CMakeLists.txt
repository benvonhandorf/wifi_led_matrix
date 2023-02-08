cmake_minimum_required(VERSION 3.15.3)

add_library(Common "")

target_include_directories(Common PUBLIC .)

target_sources(Common
    PUBLIC
        configuration.hpp
        PixelMapping.cpp
        PixelMapping.hpp
        Protocol.hpp
    INTERFACE
        PixelMapping.hpp
        Protocol.hpp  
        configuration.hpp 
)

target_link_libraries(Common 
    INTERFACE
        CompilerDefines)