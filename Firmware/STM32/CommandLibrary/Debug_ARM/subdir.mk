################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CommandProcessor.cpp 

OBJS += \
./CommandProcessor.o 

CPP_DEPS += \
./CommandProcessor.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-none-eabi-g++ -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/Common" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/NetworkLibrary" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/DisplayDriverCommon" -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=cortex-m4 -specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

