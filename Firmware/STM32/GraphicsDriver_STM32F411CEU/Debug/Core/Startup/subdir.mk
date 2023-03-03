################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f411ceux.s 

S_DEPS += \
./Core/Startup/startup_stm32f411ceux.d 

OBJS += \
./Core/Startup/startup_stm32f411ceux.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/NetworkLibrary" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/CommandLibrary" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/DisplayDriverCommon" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/Common" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver_STM32F411CEU/../main/inc" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver_STM32F411CEU/../data/inc" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver_STM32F411CEU/../devices/inc" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f411ceux.d ./Core/Startup/startup_stm32f411ceux.o

.PHONY: clean-Core-2f-Startup

