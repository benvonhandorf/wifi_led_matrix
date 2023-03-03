################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../devices/src/LedSingleWire.cpp \
../devices/src/MatrixDriver.cpp 

CPP_DEPS += \
./devices/src/LedSingleWire.d \
./devices/src/MatrixDriver.d 

OBJS += \
./devices/src/LedSingleWire.o \
./devices/src/MatrixDriver.o 


# Each subdirectory must supply rules for building sources it contributes
devices/src/%.o: ../devices/src/%.cpp devices/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-devices-2f-src

clean-devices-2f-src:
	-$(RM) ./devices/src/LedSingleWire.d ./devices/src/LedSingleWire.o ./devices/src/MatrixDriver.d ./devices/src/MatrixDriver.o

.PHONY: clean-devices-2f-src

