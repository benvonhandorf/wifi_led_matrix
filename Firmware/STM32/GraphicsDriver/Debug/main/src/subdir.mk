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
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver/../main/inc" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver/../devices/inc" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver/../data/inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"main/src/cpp_main.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
