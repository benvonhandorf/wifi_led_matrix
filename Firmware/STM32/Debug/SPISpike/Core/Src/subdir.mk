################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SPISpike/Core/Src/main.c \
../SPISpike/Core/Src/stm32f4xx_hal_msp.c \
../SPISpike/Core/Src/stm32f4xx_it.c \
../SPISpike/Core/Src/syscalls.c \
../SPISpike/Core/Src/sysmem.c \
../SPISpike/Core/Src/system_stm32f4xx.c 

C_DEPS += \
./SPISpike/Core/Src/main.d \
./SPISpike/Core/Src/stm32f4xx_hal_msp.d \
./SPISpike/Core/Src/stm32f4xx_it.d \
./SPISpike/Core/Src/syscalls.d \
./SPISpike/Core/Src/sysmem.d \
./SPISpike/Core/Src/system_stm32f4xx.d 

OBJS += \
./SPISpike/Core/Src/main.o \
./SPISpike/Core/Src/stm32f4xx_hal_msp.o \
./SPISpike/Core/Src/stm32f4xx_it.o \
./SPISpike/Core/Src/syscalls.o \
./SPISpike/Core/Src/sysmem.o \
./SPISpike/Core/Src/system_stm32f4xx.o 


# Each subdirectory must supply rules for building sources it contributes
SPISpike/Core/Src/%.o: ../SPISpike/Core/Src/%.c SPISpike/Core/Src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-SPISpike-2f-Core-2f-Src

clean-SPISpike-2f-Core-2f-Src:
	-$(RM) ./SPISpike/Core/Src/main.d ./SPISpike/Core/Src/main.o ./SPISpike/Core/Src/stm32f4xx_hal_msp.d ./SPISpike/Core/Src/stm32f4xx_hal_msp.o ./SPISpike/Core/Src/stm32f4xx_it.d ./SPISpike/Core/Src/stm32f4xx_it.o ./SPISpike/Core/Src/syscalls.d ./SPISpike/Core/Src/syscalls.o ./SPISpike/Core/Src/sysmem.d ./SPISpike/Core/Src/sysmem.o ./SPISpike/Core/Src/system_stm32f4xx.d ./SPISpike/Core/Src/system_stm32f4xx.o

.PHONY: clean-SPISpike-2f-Core-2f-Src

