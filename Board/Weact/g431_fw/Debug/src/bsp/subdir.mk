################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/bsp.c \
../src/bsp/stm32g4xx_hal_msp.c \
../src/bsp/stm32g4xx_it.c \
../src/bsp/syscalls.c \
../src/bsp/sysmem.c \
../src/bsp/system_stm32g4xx.c 

OBJS += \
./src/bsp/bsp.o \
./src/bsp/stm32g4xx_hal_msp.o \
./src/bsp/stm32g4xx_it.o \
./src/bsp/syscalls.o \
./src/bsp/sysmem.o \
./src/bsp/system_stm32g4xx.o 

C_DEPS += \
./src/bsp/bsp.d \
./src/bsp/stm32g4xx_hal_msp.d \
./src/bsp/stm32g4xx_it.d \
./src/bsp/syscalls.d \
./src/bsp/sysmem.d \
./src/bsp/system_stm32g4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/%.o src/bsp/%.su src/bsp/%.cyclo: ../src/bsp/%.c src/bsp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32G431xx -c -I"D:/Github/STM32/Board/Weact/g431_fw/src" -I"D:/Github/STM32/Board/Weact/g431_fw/src/ap" -I"D:/Github/STM32/Board/Weact/g431_fw/src/bsp" -I"D:/Github/STM32/Board/Weact/g431_fw/src/common" -I"D:/Github/STM32/Board/Weact/g431_fw/src/hw" -I"D:/Github/STM32/Board/Weact/g431_fw/src/lib" -I"D:/Github/STM32/Board/Weact/g431_fw/src/bsp/cmsis/device/Include" -I"D:/Github/STM32/Board/Weact/g431_fw/src/bsp/cmsis/Include" -I"D:/Github/STM32/Board/Weact/g431_fw/src/lib/STM32G4xx_HAL_Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src-2f-bsp

clean-src-2f-bsp:
	-$(RM) ./src/bsp/bsp.cyclo ./src/bsp/bsp.d ./src/bsp/bsp.o ./src/bsp/bsp.su ./src/bsp/stm32g4xx_hal_msp.cyclo ./src/bsp/stm32g4xx_hal_msp.d ./src/bsp/stm32g4xx_hal_msp.o ./src/bsp/stm32g4xx_hal_msp.su ./src/bsp/stm32g4xx_it.cyclo ./src/bsp/stm32g4xx_it.d ./src/bsp/stm32g4xx_it.o ./src/bsp/stm32g4xx_it.su ./src/bsp/syscalls.cyclo ./src/bsp/syscalls.d ./src/bsp/syscalls.o ./src/bsp/syscalls.su ./src/bsp/sysmem.cyclo ./src/bsp/sysmem.d ./src/bsp/sysmem.o ./src/bsp/sysmem.su ./src/bsp/system_stm32g4xx.cyclo ./src/bsp/system_stm32g4xx.d ./src/bsp/system_stm32g4xx.o ./src/bsp/system_stm32g4xx.su

.PHONY: clean-src-2f-bsp

