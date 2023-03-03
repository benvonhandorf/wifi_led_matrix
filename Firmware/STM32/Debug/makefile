################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include main/src/subdir.mk
-include devices/src/subdir.mk
-include SPISpike/Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include SPISpike/Debug/Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include SPISpike/Debug/Core/Startup/subdir.mk
-include SPISpike/Debug/Core/Src/subdir.mk
-include SPISpike/Core/Src/subdir.mk
-include NetworkLibrary_Test/subdir.mk
-include NetworkLibrary/Debug_ARM/subdir.mk
-include NetworkLibrary/subdir.mk
-include GraphicsDriver_STM32F411RET6_OLD/Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include GraphicsDriver_STM32F411RET6_OLD/Core/Src/subdir.mk
-include GraphicsDriver_STM32F411RET6/Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include GraphicsDriver_STM32F411RET6/Core/Src/subdir.mk
-include GraphicsDriver_STM32F411CEU/Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include GraphicsDriver_STM32F411CEU/Debug/Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include GraphicsDriver_STM32F411CEU/Debug/Core/Startup/subdir.mk
-include GraphicsDriver_STM32F411CEU/Debug/Core/Src/subdir.mk
-include GraphicsDriver_STM32F411CEU/Core/Src/subdir.mk
-include GraphicsDriver_F411/Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include GraphicsDriver_F411/Debug/Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include GraphicsDriver_F411/Debug/Core/Startup/subdir.mk
-include GraphicsDriver_F411/Debug/Core/Src/subdir.mk
-include GraphicsDriver_F411/Core/Src/subdir.mk
-include GraphicsDriver/Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include GraphicsDriver/Debug/Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include GraphicsDriver/Debug/Core/Startup/subdir.mk
-include GraphicsDriver/Debug/Core/Src/subdir.mk
-include GraphicsDriver/Core/Src/subdir.mk
-include DisplayDriverCommon/Debug_ARM/subdir.mk
-include DisplayDriverCommon/Debug/subdir.mk
-include DisplayDriverCommon/subdir.mk
-include Common/Debug_ARM/subdir.mk
-include Common/subdir.mk
-include CommandLibrary_Test/Debug/subdir.mk
-include CommandLibrary_Test/subdir.mk
-include CommandLibrary/Debug_ARM/subdir.mk
-include CommandLibrary/Debug/subdir.mk
-include CommandLibrary/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Common
BUILD_ARTIFACT_EXTENSION := a
BUILD_ARTIFACT_PREFIX := lib
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main-build

# Main-build Target
main-build: libCommon.a

# Tool invocations
libCommon.a: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Archiver'
	ar -r  "libCommon.a" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) libCommon.a
	-@echo ' '

.PHONY: all clean dependents main-build

-include ../makefile.targets
