################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Src/stts22h.c \
../Drivers/BSP/Src/stts22h_reg.c 

OBJS += \
./Drivers/BSP/Src/stts22h.o \
./Drivers/BSP/Src/stts22h_reg.o 

C_DEPS += \
./Drivers/BSP/Src/stts22h.d \
./Drivers/BSP/Src/stts22h_reg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Src/%.o Drivers/BSP/Src/%.su Drivers/BSP/Src/%.cyclo: ../Drivers/BSP/Src/%.c Drivers/BSP/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5G9xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Src

clean-Drivers-2f-BSP-2f-Src:
	-$(RM) ./Drivers/BSP/Src/stts22h.cyclo ./Drivers/BSP/Src/stts22h.d ./Drivers/BSP/Src/stts22h.o ./Drivers/BSP/Src/stts22h.su ./Drivers/BSP/Src/stts22h_reg.cyclo ./Drivers/BSP/Src/stts22h_reg.d ./Drivers/BSP/Src/stts22h_reg.o ./Drivers/BSP/Src/stts22h_reg.su

.PHONY: clean-Drivers-2f-BSP-2f-Src

