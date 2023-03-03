################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include main/src/subdir.mk
-include devices/src/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
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
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
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


BUILD_ARTIFACT_NAME := GraphicsDriver_STM32F411CEU
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
GraphicsDriver_STM32F411CEU.elf \

MAP_FILES += \
GraphicsDriver_STM32F411CEU.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
GraphicsDriver_STM32F411CEU.list \


# All Target
all: main-build

# Main-build Target
main-build: GraphicsDriver_STM32F411CEU.elf secondary-outputs

dependents:
	-cd /home/benvh/projects/wifi_led_matrix/Firmware/STM32/Common/Debug_ARM && $(MAKE) clean all
	-cd /home/benvh/projects/wifi_led_matrix/Firmware/STM32/DisplayDriverCommon/Debug_ARM && $(MAKE) clean all
	-cd /home/benvh/projects/wifi_led_matrix/Firmware/STM32/CommandLibrary/Debug_ARM && $(MAKE) clean all
	-cd /home/benvh/projects/wifi_led_matrix/Firmware/STM32/NetworkLibrary/Debug_ARM && $(MAKE) clean all

# Tool invocations
GraphicsDriver_STM32F411CEU.elf GraphicsDriver_STM32F411CEU.map: $(OBJS) $(USER_OBJS) /home/benvh/projects/wifi_led_matrix/Firmware/STM32/Common/Debug_ARM/libCommon.a /home/benvh/projects/wifi_led_matrix/Firmware/STM32/DisplayDriverCommon/Debug_ARM/libDisplayDriverCommon.a /home/benvh/projects/wifi_led_matrix/Firmware/STM32/CommandLibrary/Debug_ARM/libCommandLibrary.a /home/benvh/projects/wifi_led_matrix/Firmware/STM32/NetworkLibrary/Debug_ARM/libNetworkLibrary.a /home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver_STM32F411CEU/STM32F411CEUX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-g++ -o "GraphicsDriver_STM32F411CEU.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver_STM32F411CEU/STM32F411CEUX_FLASH.ld" --specs=nosys.specs -Wl,-Map="GraphicsDriver_STM32F411CEU.map" -Wl,--gc-sections -static -L"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/NetworkLibrary/Debug_ARM" -L"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/CommandLibrary/Debug_ARM" -L"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/DisplayDriverCommon/Debug_ARM" -L"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/Common/Debug_ARM" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

GraphicsDriver_STM32F411CEU.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "GraphicsDriver_STM32F411CEU.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) GraphicsDriver_STM32F411CEU.elf GraphicsDriver_STM32F411CEU.list GraphicsDriver_STM32F411CEU.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified
/home/benvh/projects/wifi_led_matrix/Firmware/STM32/Common/Debug_ARM/libCommon.a:
/home/benvh/projects/wifi_led_matrix/Firmware/STM32/DisplayDriverCommon/Debug_ARM/libDisplayDriverCommon.a:
/home/benvh/projects/wifi_led_matrix/Firmware/STM32/CommandLibrary/Debug_ARM/libCommandLibrary.a:
/home/benvh/projects/wifi_led_matrix/Firmware/STM32/NetworkLibrary/Debug_ARM/libNetworkLibrary.a:

-include ../makefile.targets
