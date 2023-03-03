################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../main/src/cpp_main.cpp 

CPP_DEPS += \
./main/src/cpp_main.d 

OBJS += \
./main/src/cpp_main.o 


# Each subdirectory must supply rules for building sources it contributes
main/src/%.o: ../main/src/%.cpp main/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-main-2f-src

clean-main-2f-src:
	-$(RM) ./main/src/cpp_main.d ./main/src/cpp_main.o

.PHONY: clean-main-2f-src

