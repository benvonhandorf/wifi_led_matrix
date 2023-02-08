cmake_minimum_required(VERSION 3.15.3)

add_library(CommandProcessor "")

target_sources(CommandProcessor
    PUBLIC
        CommandProcessor.hpp
        CommandProcessor.cpp
)

target_include_directories(CommandProcessor PUBLIC .)

target_link_libraries(CommandProcessor 
    PUBLIC 
        Common 
        NetworkLibrary 
        DisplayDriverCommon
    INTERFACE
        CompilerDefines
)