################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery.c \
../Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_bus.c \
../Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_env_sensors.c \
../Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_hspi.c \
../Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_lcd.c \
../Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_mmc.c \
../Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_ospi.c \
../Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_ranging_sensor.c \
../Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_ts.c 

OBJS += \
./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery.o \
./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_bus.o \
./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_env_sensors.o \
./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_hspi.o \
./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_lcd.o \
./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_mmc.o \
./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_ospi.o \
./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_ranging_sensor.o \
./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_ts.o 

C_DEPS += \
./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery.d \
./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_bus.d \
./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_env_sensors.d \
./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_hspi.d \
./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_lcd.d \
./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_mmc.d \
./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_ospi.d \
./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_ranging_sensor.d \
./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_ts.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32U5x9J-DK/%.o Drivers/BSP/STM32U5x9J-DK/%.su Drivers/BSP/STM32U5x9J-DK/%.cyclo: ../Drivers/BSP/STM32U5x9J-DK/%.c Drivers/BSP/STM32U5x9J-DK/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5G9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32U5x9J-2d-DK

clean-Drivers-2f-BSP-2f-STM32U5x9J-2d-DK:
	-$(RM) ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery.cyclo ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery.d ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery.o ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery.su ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_bus.cyclo ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_bus.d ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_bus.o ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_bus.su ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_env_sensors.cyclo ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_env_sensors.d ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_env_sensors.o ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_env_sensors.su ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_hspi.cyclo ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_hspi.d ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_hspi.o ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_hspi.su ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_lcd.cyclo ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_lcd.d ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_lcd.o ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_lcd.su ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_mmc.cyclo ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_mmc.d ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_mmc.o ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_mmc.su ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_ospi.cyclo ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_ospi.d ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_ospi.o ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_ospi.su ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_ranging_sensor.cyclo ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_ranging_sensor.d ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_ranging_sensor.o ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_ranging_sensor.su ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_ts.cyclo ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_ts.d ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_ts.o ./Drivers/BSP/STM32U5x9J-DK/stm32u5x9j_discovery_ts.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32U5x9J-2d-DK

