cmake_minimum_required(VERSION 3.15.3)

add_library(Core "")

target_include_directories(Core 
    PUBLIC
        Inc
)

file(GLOB_RECURSE sources Src/*)

target_sources(Core
    PUBLIC
        ${sources}
        Startup/startup_stm32f411retx.s
)

target_link_libraries(Core  
    PUBLIC 
        cpp_interface 
        Drivers 
        CompilerDefines)