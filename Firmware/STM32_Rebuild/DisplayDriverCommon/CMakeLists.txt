cmake_minimum_required(VERSION 3.15.3)

add_library(DisplayDriverCommon INTERFACE)

target_sources(DisplayDriverCommon 
    PUBLIC
        DisplayDriver.hpp
)

target_link_libraries(DisplayDriverCommon
    INTERFACE
        CompilerDefines)

target_include_directories(DisplayDriverCommon INTERFACE .)