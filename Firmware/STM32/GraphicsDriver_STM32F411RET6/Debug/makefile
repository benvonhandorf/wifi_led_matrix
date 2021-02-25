################################################################################
# Automatically-generated file. Do not edit!
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

BUILD_ARTIFACT_NAME := GraphicsDriver_STM32F411RET6
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX := 
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME).$(BUILD_ARTIFACT_EXTENSION)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
GraphicsDriver_STM32F411RET6.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
GraphicsDriver_STM32F411RET6.list \

OBJCOPY_BIN += \
GraphicsDriver_STM32F411RET6.bin \


# All Target
all: main-build

# Main-build Target
main-build: GraphicsDriver_STM32F411RET6.elf secondary-outputs

dependents:
	-cd /home/benvh/projects/wifi_led_matrix/Firmware/STM32/CommandLibrary/Debug_ARM && $(MAKE) clean all
	-cd /home/benvh/projects/wifi_led_matrix/Firmware/STM32/Common/Debug_ARM && $(MAKE) clean all
	-cd /home/benvh/projects/wifi_led_matrix/Firmware/STM32/DisplayDriverCommon/Debug_ARM && $(MAKE) clean all
	-cd /home/benvh/projects/wifi_led_matrix/Firmware/STM32/NetworkLibrary/Debug_ARM && $(MAKE) clean all

# Tool invocations
GraphicsDriver_STM32F411RET6.elf: $(OBJS) $(USER_OBJS) /home/benvh/projects/wifi_led_matrix/Firmware/STM32/CommandLibrary/Debug_ARM/libCommandLibrary.a /home/benvh/projects/wifi_led_matrix/Firmware/STM32/Common/Debug_ARM/libCommon.a /home/benvh/projects/wifi_led_matrix/Firmware/STM32/DisplayDriverCommon/Debug_ARM/libDisplayDriverCommon.a /home/benvh/projects/wifi_led_matrix/Firmware/STM32/NetworkLibrary/Debug_ARM/libNetworkLibrary.a /home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver_STM32F411RET6/STM32F411RETX_FLASH.ld
	arm-none-eabi-g++ -o "GraphicsDriver_STM32F411RET6.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/GraphicsDriver_STM32F411RET6/STM32F411RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="GraphicsDriver_STM32F411RET6.map" -Wl,--gc-sections -static -L"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/NetworkLibrary/Debug_ARM" -L"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/DisplayDriverCommon/Debug_ARM" -L"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/Common/Debug_ARM" -L"/home/benvh/projects/wifi_led_matrix/Firmware/STM32/CommandLibrary/Debug_ARM" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

GraphicsDriver_STM32F411RET6.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "GraphicsDriver_STM32F411RET6.list"
	@echo 'Finished building: $@'
	@echo ' '

GraphicsDriver_STM32F411RET6.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "GraphicsDriver_STM32F411RET6.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified
.SECONDARY:
/home/benvh/projects/wifi_led_matrix/Firmware/STM32/CommandLibrary/Debug_ARM/libCommandLibrary.a:
/home/benvh/projects/wifi_led_matrix/Firmware/STM32/Common/Debug_ARM/libCommon.a:
/home/benvh/projects/wifi_led_matrix/Firmware/STM32/DisplayDriverCommon/Debug_ARM/libDisplayDriverCommon.a:
/home/benvh/projects/wifi_led_matrix/Firmware/STM32/NetworkLibrary/Debug_ARM/libNetworkLibrary.a:

-include ../makefile.targets
