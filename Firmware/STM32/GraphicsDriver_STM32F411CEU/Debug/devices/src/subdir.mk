################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
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
devices/src/LedSingleWire.o: /home/benvh/projects/wifi_led_matrix/Firmware/STM32/devices/src/LedSingleWire.cpp devices/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -c -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/NetworkLibrary" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/CommandLibrary" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/DisplayDriverCommon" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/Common" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver_STM32F411CEU/../main/inc" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver_STM32F411CEU/../data/inc" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver_STM32F411CEU/../devices/inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
devices/src/MatrixDriver.o: /home/benvh/projects/wifi_led_matrix/Firmware/STM32/devices/src/MatrixDriver.cpp devices/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -c -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/NetworkLibrary" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/CommandLibrary" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/DisplayDriverCommon" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/Common" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver_STM32F411CEU/../main/inc" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver_STM32F411CEU/../data/inc" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver_STM32F411CEU/../devices/inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-devices-2f-src

clean-devices-2f-src:
	-$(RM) ./devices/src/LedSingleWire.d ./devices/src/LedSingleWire.o ./devices/src/LedSingleWire.su ./devices/src/MatrixDriver.d ./devices/src/MatrixDriver.o ./devices/src/MatrixDriver.su

.PHONY: clean-devices-2f-src

