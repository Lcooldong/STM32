################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32U5xx_HAL_Driver/Src/subdir.mk
-include Drivers/BSP/STM32U5x9J-DK/subdir.mk
-include Drivers/BSP/Components/vl53l5cx/porting/subdir.mk
-include Drivers/BSP/Components/vl53l5cx/modules/subdir.mk
-include Drivers/BSP/Components/vl53l5cx/subdir.mk
-include Drivers/BSP/Components/stts22h/subdir.mk
-include Drivers/BSP/Components/sitronix/subdir.mk
-include Drivers/BSP/Components/mx25um51245g/subdir.mk
-include Drivers/BSP/Components/aps512xx/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := 03.I2C_TemperatureSensor
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
03.I2C_TemperatureSensor.elf \

MAP_FILES += \
03.I2C_TemperatureSensor.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
03.I2C_TemperatureSensor.list \


# All Target
all: main-build

# Main-build Target
main-build: 03.I2C_TemperatureSensor.elf secondary-outputs

# Tool invocations
03.I2C_TemperatureSensor.elf 03.I2C_TemperatureSensor.map: $(OBJS) $(USER_OBJS) D:\Github\STM32\STM32U5G9\03.I2C_TemperatureSensor\STM32U5G9NJHXQ_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "03.I2C_TemperatureSensor.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m33 -T"D:\Github\STM32\STM32U5G9\03.I2C_TemperatureSensor\STM32U5G9NJHXQ_FLASH.ld" --specs=nosys.specs -Wl,-Map="03.I2C_TemperatureSensor.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

03.I2C_TemperatureSensor.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "03.I2C_TemperatureSensor.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) 03.I2C_TemperatureSensor.elf 03.I2C_TemperatureSensor.list 03.I2C_TemperatureSensor.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
