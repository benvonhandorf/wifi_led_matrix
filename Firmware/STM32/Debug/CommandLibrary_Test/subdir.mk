################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CommandLibrary_Test/CommandProcessor_SetPixel_MultiplePixel_Test.cpp \
../CommandLibrary_Test/CommandProcessor_SetPixel_SinglePixel_Test.cpp \
../CommandLibrary_Test/DummyDisplayDriver.cpp \
../CommandLibrary_Test/TestDisplay.cpp \
../CommandLibrary_Test/main.cpp 

CPP_DEPS += \
./CommandLibrary_Test/CommandProcessor_SetPixel_MultiplePixel_Test.d \
./CommandLibrary_Test/CommandProcessor_SetPixel_SinglePixel_Test.d \
./CommandLibrary_Test/DummyDisplayDriver.d \
./CommandLibrary_Test/TestDisplay.d \
./CommandLibrary_Test/main.d 

OBJS += \
./CommandLibrary_Test/CommandProcessor_SetPixel_MultiplePixel_Test.o \
./CommandLibrary_Test/CommandProcessor_SetPixel_SinglePixel_Test.o \
./CommandLibrary_Test/DummyDisplayDriver.o \
./CommandLibrary_Test/TestDisplay.o \
./CommandLibrary_Test/main.o 


# Each subdirectory must supply rules for building sources it contributes
CommandLibrary_Test/%.o: ../CommandLibrary_Test/%.cpp CommandLibrary_Test/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-CommandLibrary_Test

clean-CommandLibrary_Test:
	-$(RM) ./CommandLibrary_Test/CommandProcessor_SetPixel_MultiplePixel_Test.d ./CommandLibrary_Test/CommandProcessor_SetPixel_MultiplePixel_Test.o ./CommandLibrary_Test/CommandProcessor_SetPixel_SinglePixel_Test.d ./CommandLibrary_Test/CommandProcessor_SetPixel_SinglePixel_Test.o ./CommandLibrary_Test/DummyDisplayDriver.d ./CommandLibrary_Test/DummyDisplayDriver.o ./CommandLibrary_Test/TestDisplay.d ./CommandLibrary_Test/TestDisplay.o ./CommandLibrary_Test/main.d ./CommandLibrary_Test/main.o

.PHONY: clean-CommandLibrary_Test

