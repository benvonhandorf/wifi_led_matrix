################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/benvh/projects/wifi_led_matrix/Firmware/STM32/devices/src/LedSingleWire.cpp \
/home/benvh/projects/wifi_led_matrix/Firmware/STM32/devices/src/MatrixDriver.cpp 

OBJS += \
./devices/src/LedSingleWire.o \
./devices/src/MatrixDriver.o 

CPP_DEPS += \
./devices/src/LedSingleWire.d \
./devices/src/MatrixDriver.d 


# Each subdirectory must supply rules for building sources it contributes
devices/src/LedSingleWire.o: /home/benvh/projects/wifi_led_matrix/Firmware/STM32/devices/src/LedSingleWire.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver/../main/inc" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver/../devices/inc" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver/../data/inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"devices/src/LedSingleWire.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
devices/src/MatrixDriver.o: /home/benvh/projects/wifi_led_matrix/Firmware/STM32/devices/src/MatrixDriver.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver/../main/inc" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver/../devices/inc" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver/../data/inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"devices/src/MatrixDriver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

