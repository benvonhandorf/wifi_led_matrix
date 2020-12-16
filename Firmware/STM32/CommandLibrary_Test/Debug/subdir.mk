################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CommandProcessor_SetPixel_SinglePixel_Test.cpp \
../DummyDisplayDriver.cpp \
../TestDisplay.cpp \
../main.cpp 

OBJS += \
./CommandProcessor_SetPixel_SinglePixel_Test.o \
./DummyDisplayDriver.o \
./TestDisplay.o \
./main.o 

CPP_DEPS += \
./CommandProcessor_SetPixel_SinglePixel_Test.d \
./DummyDisplayDriver.d \
./TestDisplay.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/NetworkLibrary" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/DisplayDriverCommon" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/Common" -I"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/CommandLibrary" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


