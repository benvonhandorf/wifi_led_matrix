################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GraphicsDriver_STM32F411CEU/Core/Src/main.c \
../GraphicsDriver_STM32F411CEU/Core/Src/stm32f4xx_hal_msp.c \
../GraphicsDriver_STM32F411CEU/Core/Src/stm32f4xx_it.c \
../GraphicsDriver_STM32F411CEU/Core/Src/syscalls.c \
../GraphicsDriver_STM32F411CEU/Core/Src/sysmem.c \
../GraphicsDriver_STM32F411CEU/Core/Src/system_stm32f4xx.c 

C_DEPS += \
./GraphicsDriver_STM32F411CEU/Core/Src/main.d \
./GraphicsDriver_STM32F411CEU/Core/Src/stm32f4xx_hal_msp.d \
./GraphicsDriver_STM32F411CEU/Core/Src/stm32f4xx_it.d \
./GraphicsDriver_STM32F411CEU/Core/Src/syscalls.d \
./GraphicsDriver_STM32F411CEU/Core/Src/sysmem.d \
./GraphicsDriver_STM32F411CEU/Core/Src/system_stm32f4xx.d 

OBJS += \
./GraphicsDriver_STM32F411CEU/Core/Src/main.o \
./GraphicsDriver_STM32F411CEU/Core/Src/stm32f4xx_hal_msp.o \
./GraphicsDriver_STM32F411CEU/Core/Src/stm32f4xx_it.o \
./GraphicsDriver_STM32F411CEU/Core/Src/syscalls.o \
./GraphicsDriver_STM32F411CEU/Core/Src/sysmem.o \
./GraphicsDriver_STM32F411CEU/Core/Src/system_stm32f4xx.o 


# Each subdirectory must supply rules for building sources it contributes
GraphicsDriver_STM32F411CEU/Core/Src/%.o: ../GraphicsDriver_STM32F411CEU/Core/Src/%.c GraphicsDriver_STM32F411CEU/Core/Src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-GraphicsDriver_STM32F411CEU-2f-Core-2f-Src

clean-GraphicsDriver_STM32F411CEU-2f-Core-2f-Src:
	-$(RM) ./GraphicsDriver_STM32F411CEU/Core/Src/main.d ./GraphicsDriver_STM32F411CEU/Core/Src/main.o ./GraphicsDriver_STM32F411CEU/Core/Src/stm32f4xx_hal_msp.d ./GraphicsDriver_STM32F411CEU/Core/Src/stm32f4xx_hal_msp.o ./GraphicsDriver_STM32F411CEU/Core/Src/stm32f4xx_it.d ./GraphicsDriver_STM32F411CEU/Core/Src/stm32f4xx_it.o ./GraphicsDriver_STM32F411CEU/Core/Src/syscalls.d ./GraphicsDriver_STM32F411CEU/Core/Src/syscalls.o ./GraphicsDriver_STM32F411CEU/Core/Src/sysmem.d ./GraphicsDriver_STM32F411CEU/Core/Src/sysmem.o ./GraphicsDriver_STM32F411CEU/Core/Src/system_stm32f4xx.d ./GraphicsDriver_STM32F411CEU/Core/Src/system_stm32f4xx.o

.PHONY: clean-GraphicsDriver_STM32F411CEU-2f-Core-2f-Src

