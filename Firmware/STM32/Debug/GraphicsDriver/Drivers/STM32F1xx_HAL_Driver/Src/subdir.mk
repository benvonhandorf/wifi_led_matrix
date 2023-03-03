################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c \
../GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c \
../GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c \
../GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c \
../GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c \
../GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c \
../GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c \
../GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c \
../GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_iwdg.c \
../GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c \
../GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c \
../GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c \
../GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_spi.c \
../GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c \
../GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c \
../GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c 

C_DEPS += \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.d \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.d \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.d \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.d \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.d \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.d \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.d \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.d \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_iwdg.d \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.d \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.d \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.d \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_spi.d \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.d \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.d \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.d 

OBJS += \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.o \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.o \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.o \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.o \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.o \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.o \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.o \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.o \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_iwdg.o \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.o \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.o \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.o \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_spi.o \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.o \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.o \
./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.o 


# Each subdirectory must supply rules for building sources it contributes
GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/%.o: ../GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/%.c GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-GraphicsDriver-2f-Drivers-2f-STM32F1xx_HAL_Driver-2f-Src

clean-GraphicsDriver-2f-Drivers-2f-STM32F1xx_HAL_Driver-2f-Src:
	-$(RM) ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.d ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.o ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.d ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.o ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.d ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.o ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.d ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.o ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.d ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.o ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.d ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.o ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.d ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.o ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.d ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.o ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_iwdg.d ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_iwdg.o ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.d ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.o ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.d ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.o ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.d ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.o ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_spi.d ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_spi.o ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.d ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.o ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.d ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.o ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.d ./GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.o

.PHONY: clean-GraphicsDriver-2f-Drivers-2f-STM32F1xx_HAL_Driver-2f-Src

