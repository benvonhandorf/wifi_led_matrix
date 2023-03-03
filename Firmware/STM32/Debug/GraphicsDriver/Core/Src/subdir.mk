################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GraphicsDriver/Core/Src/main.c \
../GraphicsDriver/Core/Src/stm32f1xx_hal_msp.c \
../GraphicsDriver/Core/Src/stm32f1xx_it.c \
../GraphicsDriver/Core/Src/syscalls.c \
../GraphicsDriver/Core/Src/sysmem.c \
../GraphicsDriver/Core/Src/system_stm32f1xx.c 

C_DEPS += \
./GraphicsDriver/Core/Src/main.d \
./GraphicsDriver/Core/Src/stm32f1xx_hal_msp.d \
./GraphicsDriver/Core/Src/stm32f1xx_it.d \
./GraphicsDriver/Core/Src/syscalls.d \
./GraphicsDriver/Core/Src/sysmem.d \
./GraphicsDriver/Core/Src/system_stm32f1xx.d 

OBJS += \
./GraphicsDriver/Core/Src/main.o \
./GraphicsDriver/Core/Src/stm32f1xx_hal_msp.o \
./GraphicsDriver/Core/Src/stm32f1xx_it.o \
./GraphicsDriver/Core/Src/syscalls.o \
./GraphicsDriver/Core/Src/sysmem.o \
./GraphicsDriver/Core/Src/system_stm32f1xx.o 


# Each subdirectory must supply rules for building sources it contributes
GraphicsDriver/Core/Src/%.o: ../GraphicsDriver/Core/Src/%.c GraphicsDriver/Core/Src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-GraphicsDriver-2f-Core-2f-Src

clean-GraphicsDriver-2f-Core-2f-Src:
	-$(RM) ./GraphicsDriver/Core/Src/main.d ./GraphicsDriver/Core/Src/main.o ./GraphicsDriver/Core/Src/stm32f1xx_hal_msp.d ./GraphicsDriver/Core/Src/stm32f1xx_hal_msp.o ./GraphicsDriver/Core/Src/stm32f1xx_it.d ./GraphicsDriver/Core/Src/stm32f1xx_it.o ./GraphicsDriver/Core/Src/syscalls.d ./GraphicsDriver/Core/Src/syscalls.o ./GraphicsDriver/Core/Src/sysmem.d ./GraphicsDriver/Core/Src/sysmem.o ./GraphicsDriver/Core/Src/system_stm32f1xx.d ./GraphicsDriver/Core/Src/system_stm32f1xx.o

.PHONY: clean-GraphicsDriver-2f-Core-2f-Src

