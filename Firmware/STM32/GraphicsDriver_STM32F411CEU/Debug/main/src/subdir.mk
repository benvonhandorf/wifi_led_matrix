################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/benvh/projects/wifi_led_matrix/Firmware/STM32/main/src/cpp_main.cpp 

OBJS += \
./main/src/cpp_main.o 

CPP_DEPS += \
./main/src/cpp_main.d 


# Each subdirectory must supply rules for building sources it contributes
main/src/cpp_main.o: /home/benvh/projects/wifi_led_matrix/Firmware/STM32/main/src/cpp_main.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER '-DUSE_HAL_SPI_REGISTER_CALLBACKS=1' -DSTM32F411xE -DDEBUG -c -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/NetworkLibrary" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/CommandLibrary" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/DisplayDriverCommon" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/Common" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver_STM32F411CEU/../main/inc" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver_STM32F411CEU/../data/inc" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver_STM32F411CEU/../devices/inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"main/src/cpp_main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

