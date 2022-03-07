################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := CommandLibrary_Test
BUILD_ARTIFACT_EXTENSION :=
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main-build

# Main-build Target
main-build: CommandLibrary_Test

dependents:
	-cd /home/benvh/projects/wifi_led_matrix/Firmware/STM32/CommandLibrary/Debug && $(MAKE) all
	-cd /home/benvh/projects/wifi_led_matrix/Firmware/STM32/Common/Debug && $(MAKE) all
	-cd /home/benvh/projects/wifi_led_matrix/Firmware/STM32/DisplayDriverCommon/Debug && $(MAKE) all
	-cd /home/benvh/projects/wifi_led_matrix/Firmware/STM32/NetworkLibrary/Debug && $(MAKE) all

# Tool invocations
CommandLibrary_Test: $(OBJS) $(USER_OBJS) /home/benvh/projects/wifi_led_matrix/Firmware/STM32/CommandLibrary/Debug/libCommandLibrary.a /home/benvh/projects/wifi_led_matrix/Firmware/STM32/Common/Debug/libCommon.a /home/benvh/projects/wifi_led_matrix/Firmware/STM32/DisplayDriverCommon/Debug/libDisplayDriverCommon.a /home/benvh/projects/wifi_led_matrix/Firmware/STM32/NetworkLibrary/Debug/libNetworkLibrary.a makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++ -L"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/NetworkLibrary/Debug" -L"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/DisplayDriverCommon/Debug" -L"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/Common/Debug" -L"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/CommandLibrary/Debug" -o "CommandLibrary_Test" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(C_DEPS)$(CPP_DEPS) CommandLibrary_Test
	-@echo ' '

.PHONY: all clean dependents main-build
/home/benvh/projects/wifi_led_matrix/Firmware/STM32/CommandLibrary/Debug/libCommandLibrary.a:
/home/benvh/projects/wifi_led_matrix/Firmware/STM32/Common/Debug/libCommon.a:
/home/benvh/projects/wifi_led_matrix/Firmware/STM32/DisplayDriverCommon/Debug/libDisplayDriverCommon.a:
/home/benvh/projects/wifi_led_matrix/Firmware/STM32/NetworkLibrary/Debug/libNetworkLibrary.a:

-include ../makefile.targets
