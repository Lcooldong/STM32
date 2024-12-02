################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/dma2d.c \
../Core/Src/dsihost.c \
../Core/Src/gfxmmu.c \
../Core/Src/gfxtim.c \
../Core/Src/gpio.c \
../Core/Src/hspi.c \
../Core/Src/i2c.c \
../Core/Src/icache.c \
../Core/Src/ltdc.c \
../Core/Src/main.c \
../Core/Src/memorymap.c \
../Core/Src/octospi.c \
../Core/Src/sdmmc.c \
../Core/Src/stm32u5xx_hal_msp.c \
../Core/Src/stm32u5xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32u5xx.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/dma2d.o \
./Core/Src/dsihost.o \
./Core/Src/gfxmmu.o \
./Core/Src/gfxtim.o \
./Core/Src/gpio.o \
./Core/Src/hspi.o \
./Core/Src/i2c.o \
./Core/Src/icache.o \
./Core/Src/ltdc.o \
./Core/Src/main.o \
./Core/Src/memorymap.o \
./Core/Src/octospi.o \
./Core/Src/sdmmc.o \
./Core/Src/stm32u5xx_hal_msp.o \
./Core/Src/stm32u5xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32u5xx.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/dma2d.d \
./Core/Src/dsihost.d \
./Core/Src/gfxmmu.d \
./Core/Src/gfxtim.d \
./Core/Src/gpio.d \
./Core/Src/hspi.d \
./Core/Src/i2c.d \
./Core/Src/icache.d \
./Core/Src/ltdc.d \
./Core/Src/main.d \
./Core/Src/memorymap.d \
./Core/Src/octospi.d \
./Core/Src/sdmmc.d \
./Core/Src/stm32u5xx_hal_msp.d \
./Core/Src/stm32u5xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32u5xx.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5G9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/dma2d.cyclo ./Core/Src/dma2d.d ./Core/Src/dma2d.o ./Core/Src/dma2d.su ./Core/Src/dsihost.cyclo ./Core/Src/dsihost.d ./Core/Src/dsihost.o ./Core/Src/dsihost.su ./Core/Src/gfxmmu.cyclo ./Core/Src/gfxmmu.d ./Core/Src/gfxmmu.o ./Core/Src/gfxmmu.su ./Core/Src/gfxtim.cyclo ./Core/Src/gfxtim.d ./Core/Src/gfxtim.o ./Core/Src/gfxtim.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/hspi.cyclo ./Core/Src/hspi.d ./Core/Src/hspi.o ./Core/Src/hspi.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/icache.cyclo ./Core/Src/icache.d ./Core/Src/icache.o ./Core/Src/icache.su ./Core/Src/ltdc.cyclo ./Core/Src/ltdc.d ./Core/Src/ltdc.o ./Core/Src/ltdc.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/memorymap.cyclo ./Core/Src/memorymap.d ./Core/Src/memorymap.o ./Core/Src/memorymap.su ./Core/Src/octospi.cyclo ./Core/Src/octospi.d ./Core/Src/octospi.o ./Core/Src/octospi.su ./Core/Src/sdmmc.cyclo ./Core/Src/sdmmc.d ./Core/Src/sdmmc.o ./Core/Src/sdmmc.su ./Core/Src/stm32u5xx_hal_msp.cyclo ./Core/Src/stm32u5xx_hal_msp.d ./Core/Src/stm32u5xx_hal_msp.o ./Core/Src/stm32u5xx_hal_msp.su ./Core/Src/stm32u5xx_it.cyclo ./Core/Src/stm32u5xx_it.d ./Core/Src/stm32u5xx_it.o ./Core/Src/stm32u5xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32u5xx.cyclo ./Core/Src/system_stm32u5xx.d ./Core/Src/system_stm32u5xx.o ./Core/Src/system_stm32u5xx.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

