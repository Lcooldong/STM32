/*
 * HW_579.c
 *
 *  Created on: 2022. 4. 25.
 *      Author: s_coo
 */

#define DEBUG_PRINT

#include "ITG3205.h"
#include "HW_579.h"
#include "stdio.h"

HW579 hw579;

uint8_t* getI2C_Address(I2C_HandleTypeDef *hi2c)
{
	HAL_StatusTypeDef state;
	uint8_t slave_address;
	uint8_t numSensors = 0;
	static uint8_t sensors[3] = {0, };

	for(slave_address = 1; slave_address < 128; slave_address++)
	{
		state = HAL_I2C_IsDeviceReady(hi2c, (uint16_t)(slave_address << 1), 3, 10);
	    if (state == HAL_OK)
		{
		  sensors[numSensors] = slave_address;
		  numSensors++;

#ifdef DEBUG_PRINT
		  printf("Address : 0x%X\r\n", slave_address);	// !HAL_OK = 1
#endif
	    }
	    else
	    {
		  while(HAL_I2C_GetState(hi2c) != HAL_I2C_STATE_READY);
	    }
	}

	hw579.magneto_address = sensors[0] << 1;
	hw579.accel_address   = sensors[1] << 1;
	hw579.gyro_address    = sensors[2] << 1;

#ifdef DEBUG_PRINT
	printf("MAGNETO : 0x%X\r\n", sensors[0] << 1);
	printf("ACCEL   : 0x%X\r\n", sensors[1] << 1);
	printf("GYRO    : 0x%X\r\n", sensors[2] << 1);
#endif

	return sensors;
}

void HW579_init(HW579 *I2C)
{
	Gyro_init(I2C);
}

void HW579_Read(void)
{
	Gyro_Read(&hw579);
}




