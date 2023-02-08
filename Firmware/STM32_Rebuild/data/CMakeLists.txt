cmake_minimum_required(VERSION 3.15.3)

add_library(data INTERFACE)

target_include_directories(data 
    INTERFACE
        inc
)

target_link_libraries(data INTERFACE CompilerDefines)