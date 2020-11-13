################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/benvh/projects/wifi_led_matrix/Firmware/STM32/devices/src/matrix_driver.cpp 

OBJS += \
./devices/src/matrix_driver.o 

CPP_DEPS += \
./devices/src/matrix_driver.d 


# Each subdirectory must supply rules for building sources it contributes
devices/src/matrix_driver.o: /home/benvh/projects/wifi_led_matrix/Firmware/STM32/devices/src/matrix_driver.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver/../main/inc" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver/../devices/inc" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver/../data/inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"devices/src/matrix_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

