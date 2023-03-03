################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Common/empty.cpp 

CPP_DEPS += \
./Common/empty.d 

OBJS += \
./Common/empty.o 


# Each subdirectory must supply rules for building sources it contributes
Common/%.o: ../Common/%.cpp Common/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Common

clean-Common:
	-$(RM) ./Common/empty.d ./Common/empty.o

.PHONY: clean-Common

