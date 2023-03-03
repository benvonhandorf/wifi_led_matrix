################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DisplayDriverCommon/empty.cpp 

CPP_DEPS += \
./DisplayDriverCommon/empty.d 

OBJS += \
./DisplayDriverCommon/empty.o 


# Each subdirectory must supply rules for building sources it contributes
DisplayDriverCommon/%.o: ../DisplayDriverCommon/%.cpp DisplayDriverCommon/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-DisplayDriverCommon

clean-DisplayDriverCommon:
	-$(RM) ./DisplayDriverCommon/empty.d ./DisplayDriverCommon/empty.o

.PHONY: clean-DisplayDriverCommon

