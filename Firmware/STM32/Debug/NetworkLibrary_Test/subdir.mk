################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../NetworkLibrary_Test/Request_Parse_SetPixel.cpp \
../NetworkLibrary_Test/Request_Parse_Test.cpp \
../NetworkLibrary_Test/main.cpp 

CPP_DEPS += \
./NetworkLibrary_Test/Request_Parse_SetPixel.d \
./NetworkLibrary_Test/Request_Parse_Test.d \
./NetworkLibrary_Test/main.d 

OBJS += \
./NetworkLibrary_Test/Request_Parse_SetPixel.o \
./NetworkLibrary_Test/Request_Parse_Test.o \
./NetworkLibrary_Test/main.o 


# Each subdirectory must supply rules for building sources it contributes
NetworkLibrary_Test/%.o: ../NetworkLibrary_Test/%.cpp NetworkLibrary_Test/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-NetworkLibrary_Test

clean-NetworkLibrary_Test:
	-$(RM) ./NetworkLibrary_Test/Request_Parse_SetPixel.d ./NetworkLibrary_Test/Request_Parse_SetPixel.o ./NetworkLibrary_Test/Request_Parse_Test.d ./NetworkLibrary_Test/Request_Parse_Test.o ./NetworkLibrary_Test/main.d ./NetworkLibrary_Test/main.o

.PHONY: clean-NetworkLibrary_Test

