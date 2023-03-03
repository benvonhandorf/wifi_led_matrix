################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../devices/src/LedSingleWire.cpp \
../devices/src/MatrixDriver.cpp 

OBJS += \
./devices/src/LedSingleWire.o \
./devices/src/MatrixDriver.o 

CPP_DEPS += \
./devices/src/LedSingleWire.d \
./devices/src/MatrixDriver.d 


# Each subdirectory must supply rules for building sources it contributes
devices/src/%.o devices/src/%.su: ../devices/src/%.cpp devices/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/NetworkLibrary" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/CommandLibrary" -I../data/inc -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/Common" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/DisplayDriverCommon" -I../devices/inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../main/inc -I/GraphicsDriver_STM32F411RET6/devices/inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-devices-2f-src

clean-devices-2f-src:
	-$(RM) ./devices/src/LedSingleWire.d ./devices/src/LedSingleWire.o ./devices/src/LedSingleWire.su ./devices/src/MatrixDriver.d ./devices/src/MatrixDriver.o ./devices/src/MatrixDriver.su

.PHONY: clean-devices-2f-src

