################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CommandLibrary/CommandProcessor.cpp 

CPP_DEPS += \
./CommandLibrary/CommandProcessor.d 

OBJS += \
./CommandLibrary/CommandProcessor.o 


# Each subdirectory must supply rules for building sources it contributes
CommandLibrary/%.o: ../CommandLibrary/%.cpp CommandLibrary/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-CommandLibrary

clean-CommandLibrary:
	-$(RM) ./CommandLibrary/CommandProcessor.d ./CommandLibrary/CommandProcessor.o

.PHONY: clean-CommandLibrary

