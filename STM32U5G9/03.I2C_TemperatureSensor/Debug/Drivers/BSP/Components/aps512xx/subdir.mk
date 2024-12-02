################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/aps512xx/aps512xx.c 

OBJS += \
./Drivers/BSP/Components/aps512xx/aps512xx.o 

C_DEPS += \
./Drivers/BSP/Components/aps512xx/aps512xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/aps512xx/%.o Drivers/BSP/Components/aps512xx/%.su Drivers/BSP/Components/aps512xx/%.cyclo: ../Drivers/BSP/Components/aps512xx/%.c Drivers/BSP/Components/aps512xx/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5G9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-aps512xx

clean-Drivers-2f-BSP-2f-Components-2f-aps512xx:
	-$(RM) ./Drivers/BSP/Components/aps512xx/aps512xx.cyclo ./Drivers/BSP/Components/aps512xx/aps512xx.d ./Drivers/BSP/Components/aps512xx/aps512xx.o ./Drivers/BSP/Components/aps512xx/aps512xx.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-aps512xx

