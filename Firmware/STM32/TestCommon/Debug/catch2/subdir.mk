################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../catch2/catch_amalgamated.cpp 

CPP_DEPS += \
./catch2/catch_amalgamated.d 

OBJS += \
./catch2/catch_amalgamated.o 


# Each subdirectory must supply rules for building sources it contributes
catch2/%.o: ../catch2/%.cpp catch2/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-catch2

clean-catch2:
	-$(RM) ./catch2/catch_amalgamated.d ./catch2/catch_amalgamated.o

.PHONY: clean-catch2

