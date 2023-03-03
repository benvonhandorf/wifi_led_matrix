################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Request.cpp 

CPP_DEPS += \
./Request.d 

OBJS += \
./Request.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-none-eabi-g++ -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/Common" -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=cortex-m4 -specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./Request.d ./Request.o

.PHONY: clean--2e-

