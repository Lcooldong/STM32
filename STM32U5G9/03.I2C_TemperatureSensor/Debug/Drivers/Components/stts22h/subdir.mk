################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Components/stts22h/stts22h.c \
../Drivers/Components/stts22h/stts22h_reg.c 

OBJS += \
./Drivers/Components/stts22h/stts22h.o \
./Drivers/Components/stts22h/stts22h_reg.o 

C_DEPS += \
./Drivers/Components/stts22h/stts22h.d \
./Drivers/Components/stts22h/stts22h_reg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Components/stts22h/%.o Drivers/Components/stts22h/%.su Drivers/Components/stts22h/%.cyclo: ../Drivers/Components/stts22h/%.c Drivers/Components/stts22h/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5G9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Components-2f-stts22h

clean-Drivers-2f-Components-2f-stts22h:
	-$(RM) ./Drivers/Components/stts22h/stts22h.cyclo ./Drivers/Components/stts22h/stts22h.d ./Drivers/Components/stts22h/stts22h.o ./Drivers/Components/stts22h/stts22h.su ./Drivers/Components/stts22h/stts22h_reg.cyclo ./Drivers/Components/stts22h/stts22h_reg.d ./Drivers/Components/stts22h/stts22h_reg.o ./Drivers/Components/stts22h/stts22h_reg.su

.PHONY: clean-Drivers-2f-Components-2f-stts22h

