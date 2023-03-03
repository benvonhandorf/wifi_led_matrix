################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
../GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
../GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
../GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
../GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c \
../GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
../GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
../GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
../GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
../GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
../GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
../GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
../GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
../GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
../GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c 

C_DEPS += \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.d \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.d \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.d \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.d \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.d \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.d \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.d \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.d \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.d \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.d \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.d \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.d \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.d \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.d \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.d 

OBJS += \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.o \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.o \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.o \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.o \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.o \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.o \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.o \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.o \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.o \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.o \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.o \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.o \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.o \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.o \
./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.o 


# Each subdirectory must supply rules for building sources it contributes
GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/%.o: ../GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/%.c GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-GraphicsDriver_F411-2f-Drivers-2f-STM32F4xx_HAL_Driver-2f-Src

clean-GraphicsDriver_F411-2f-Drivers-2f-STM32F4xx_HAL_Driver-2f-Src:
	-$(RM) ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.d ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.o ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.d ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.o ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.d ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.o ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.d ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.o ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.d ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.o ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.d ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.o ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.d ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.o ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.d ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.o ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.d ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.o ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.d ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.o ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.d ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.o ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.d ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.o ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.d ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.o ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.d ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.o ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.d ./GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.o

.PHONY: clean-GraphicsDriver_F411-2f-Drivers-2f-STM32F4xx_HAL_Driver-2f-Src

