################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/mx25um51245g/mx25um51245g.c 

OBJS += \
./Drivers/BSP/Components/mx25um51245g/mx25um51245g.o 

C_DEPS += \
./Drivers/BSP/Components/mx25um51245g/mx25um51245g.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/mx25um51245g/%.o Drivers/BSP/Components/mx25um51245g/%.su Drivers/BSP/Components/mx25um51245g/%.cyclo: ../Drivers/BSP/Components/mx25um51245g/%.c Drivers/BSP/Components/mx25um51245g/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5G9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-mx25um51245g

clean-Drivers-2f-BSP-2f-Components-2f-mx25um51245g:
	-$(RM) ./Drivers/BSP/Components/mx25um51245g/mx25um51245g.cyclo ./Drivers/BSP/Components/mx25um51245g/mx25um51245g.d ./Drivers/BSP/Components/mx25um51245g/mx25um51245g.o ./Drivers/BSP/Components/mx25um51245g/mx25um51245g.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-mx25um51245g

