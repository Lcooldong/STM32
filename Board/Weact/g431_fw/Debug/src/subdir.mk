################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c 

OBJS += \
./src/main.o 

C_DEPS += \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o src/%.su src/%.cyclo: ../src/%.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32G431xx -c -I"D:/Github/STM32/Board/Weact/g431_fw/src" -I"D:/Github/STM32/Board/Weact/g431_fw/src/ap" -I"D:/Github/STM32/Board/Weact/g431_fw/src/bsp" -I"D:/Github/STM32/Board/Weact/g431_fw/src/common" -I"D:/Github/STM32/Board/Weact/g431_fw/src/common/core" -I"D:/Github/STM32/Board/Weact/g431_fw/src/common/hw/include" -I"D:/Github/STM32/Board/Weact/g431_fw/src/hw" -I"D:/Github/STM32/Board/Weact/g431_fw/src/lib" -I"D:/Github/STM32/Board/Weact/g431_fw/src/bsp/cmsis/device/Include" -I"D:/Github/STM32/Board/Weact/g431_fw/src/bsp/cmsis/Include" -I"D:/Github/STM32/Board/Weact/g431_fw/src/lib/STM32G4xx_HAL_Driver/Inc" -I"D:/Github/STM32/Board/Weact/g431_fw/src/hw/driver/usb" -I"D:/Github/STM32/Board/Weact/g431_fw/src/hw/driver/usb/core" -I"D:/Github/STM32/Board/Weact/g431_fw/src/hw/driver/usb/usb_cdc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src

clean-src:
	-$(RM) ./src/main.cyclo ./src/main.d ./src/main.o ./src/main.su

.PHONY: clean-src

