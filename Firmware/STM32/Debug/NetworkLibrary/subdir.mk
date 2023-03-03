################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../NetworkLibrary/Request.cpp 

CPP_DEPS += \
./NetworkLibrary/Request.d 

OBJS += \
./NetworkLibrary/Request.o 


# Each subdirectory must supply rules for building sources it contributes
NetworkLibrary/%.o: ../NetworkLibrary/%.cpp NetworkLibrary/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-NetworkLibrary

clean-NetworkLibrary:
	-$(RM) ./NetworkLibrary/Request.d ./NetworkLibrary/Request.o

.PHONY: clean-NetworkLibrary

