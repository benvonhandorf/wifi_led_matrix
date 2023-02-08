cmake_minimum_required(VERSION 3.15.3)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arm-none-eabi-gcc.cmake)

project(GraphicsDriver_STM32F411RET6)

set(TARGET_NAME ${PROJECT_NAME}.elf)
set(LINKER_FILE ${CMAKE_SOURCE_DIR}/device/STM32F411RETX_FLASH.ld)

enable_language(CXX C ASM)

add_subdirectory(Common)
add_subdirectory(CommandProcessor)
add_subdirectory(data)
add_subdirectory(devices)
add_subdirectory(NetworkLibrary)

add_subdirectory(DisplayDriverCommon)

add_subdirectory(Core)
add_subdirectory(Drivers)

add_executable(${TARGET_NAME} 
    src/cpp_main.cpp
)

add_library(cpp_interface INTERFACE)

target_sources(cpp_interface
    INTERFACE
        inc/cpp_main.h)

target_include_directories(cpp_interface INTERFACE inc)

target_link_libraries(${TARGET_NAME} Common CommandProcessor cpp_interface data Core devices NetworkLibrary DisplayDriverCommon CompilerDefines)

set_target_properties(${TARGET_NAME} PROPERTIES LINK_DEPENDS ${LINKER_FILE})

# List of compiler defines, prefix with -D compiler option
add_library(CompilerDefines INTERFACE "")

target_compile_definitions(CompilerDefines INTERFACE
        USE_HAL_DRIVER
        STM32F411xE
        )

# Compiler options
target_compile_options(CompilerDefines INTERFACE
        -mcpu=cortex-m4
        -mthumb

        -mfpu=fpv4-sp-d16 
        -mfloat-abi=hard

        -fdata-sections
        -ffunction-sections

        -fstack-usage

        -Wall
        -O0
        -g3
        )

# Linker options

target_link_options(${TARGET_NAME} PRIVATE
        -T${LINKER_FILE}
        -mcpu=cortex-m4
        -mthumb
        -mfpu=fpv4-sp-d16 
        -mfloat-abi=hard
        -lc
        -lm
        -lnosys
        -lstdc++ 
        -lsupc++
        -Wl,-Map=${PROJECT_NAME}.map,--cref
        -Wl,--gc-sections
        -Xlinker -print-memory-usage -Xlinker
        )

# Optional: Print executable size as part of the post build process
add_custom_command(TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND ${CMAKE_SIZE_UTIL} ${TARGET_NAME})

# Optional: Create hex, bin and S-Record files after the build
add_custom_command(TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O srec --srec-len=64 ${TARGET_NAME} ${PROJECT_NAME}.s19
        COMMAND ${CMAKE_OBJCOPY} -O ihex ${TARGET_NAME} ${PROJECT_NAME}.hex
        COMMAND ${CMAKE_OBJCOPY} -O binary ${TARGET_NAME} ${PROJECT_NAME}.bin)