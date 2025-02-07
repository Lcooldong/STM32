################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hw/driver/cdc.c \
../src/hw/driver/led.c \
../src/hw/driver/reset.c \
../src/hw/driver/rtc.c \
../src/hw/driver/uart.c \
../src/hw/driver/usb.c 

OBJS += \
./src/hw/driver/cdc.o \
./src/hw/driver/led.o \
./src/hw/driver/reset.o \
./src/hw/driver/rtc.o \
./src/hw/driver/uart.o \
./src/hw/driver/usb.o 

C_DEPS += \
./src/hw/driver/cdc.d \
./src/hw/driver/led.d \
./src/hw/driver/reset.d \
./src/hw/driver/rtc.d \
./src/hw/driver/uart.d \
./src/hw/driver/usb.d 


# Each subdirectory must supply rules for building sources it contributes
src/hw/driver/%.o src/hw/driver/%.su src/hw/driver/%.cyclo: ../src/hw/driver/%.c src/hw/driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32G431xx -c -I"D:/Github/STM32/Board/Weact/g431_fw/src" -I"D:/Github/STM32/Board/Weact/g431_fw/src/ap" -I"D:/Github/STM32/Board/Weact/g431_fw/src/bsp" -I"D:/Github/STM32/Board/Weact/g431_fw/src/common" -I"D:/Github/STM32/Board/Weact/g431_fw/src/common/core" -I"D:/Github/STM32/Board/Weact/g431_fw/src/common/hw/include" -I"D:/Github/STM32/Board/Weact/g431_fw/src/hw" -I"D:/Github/STM32/Board/Weact/g431_fw/src/lib" -I"D:/Github/STM32/Board/Weact/g431_fw/src/bsp/cmsis/device/Include" -I"D:/Github/STM32/Board/Weact/g431_fw/src/bsp/cmsis/Include" -I"D:/Github/STM32/Board/Weact/g431_fw/src/lib/STM32G4xx_HAL_Driver/Inc" -I"D:/Github/STM32/Board/Weact/g431_fw/src/hw/driver/usb" -I"D:/Github/STM32/Board/Weact/g431_fw/src/hw/driver/usb/core" -I"D:/Github/STM32/Board/Weact/g431_fw/src/hw/driver/usb/usb_cdc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src-2f-hw-2f-driver

clean-src-2f-hw-2f-driver:
	-$(RM) ./src/hw/driver/cdc.cyclo ./src/hw/driver/cdc.d ./src/hw/driver/cdc.o ./src/hw/driver/cdc.su ./src/hw/driver/led.cyclo ./src/hw/driver/led.d ./src/hw/driver/led.o ./src/hw/driver/led.su ./src/hw/driver/reset.cyclo ./src/hw/driver/reset.d ./src/hw/driver/reset.o ./src/hw/driver/reset.su ./src/hw/driver/rtc.cyclo ./src/hw/driver/rtc.d ./src/hw/driver/rtc.o ./src/hw/driver/rtc.su ./src/hw/driver/uart.cyclo ./src/hw/driver/uart.d ./src/hw/driver/uart.o ./src/hw/driver/uart.su ./src/hw/driver/usb.cyclo ./src/hw/driver/usb.d ./src/hw/driver/usb.o ./src/hw/driver/usb.su

.PHONY: clean-src-2f-hw-2f-driver

