cmake_minimum_required(VERSION 3.15.3)

add_library(NetworkLibrary "")

target_sources(NetworkLibrary
    PUBLIC
        Request.hpp
        Request.cpp
)

target_link_libraries(NetworkLibrary Common CompilerDefines)

target_include_directories(NetworkLibrary PUBLIC .)