/*
 * HW_579.c
 *
 *  Created on: Apr 29, 2022
 *      Author: s_coo
 */


#include "HW_579.h"

extern HMC5883L MAGNETO;
extern ADXL345 ACCEL;
extern ITG3205 GYRO;

HW579 hw579 = {.MAGNETO_HW579 = &MAGNETO, .ACCEL_HW579 = &ACCEL, .GYRO_HW579 = &GYRO};
SENSOR_ENUM sensor_enum;

uint8_t* getI2C_Address(I2C_HandleTypeDef * hi2c, HW579 * SENSOR)
{
	HAL_StatusTypeDef state;
	uint8_t slave_address;
	uint8_t numSensors = 0;
	static uint8_t sensors[3] = {0, };

	SENSOR->i2c = *hi2c;

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


	SENSOR->MAGNETO_HW579->magneto_address = sensors[0] << 1;
	SENSOR->ACCEL_HW579->accel_address	   = sensors[1] << 1;
	SENSOR->GYRO_HW579->gyro_address   	   = sensors[2] << 1;


	printf("enum : %d %d %d\r\n", magneto, accel ,gyro);
	printf("MAGNETO : 0x%X  = 0x%X\r\n", SENSOR->MAGNETO_HW579->magneto_address, sensors[0]<< 1);
	printf("ACCEL   : 0x%X  = 0x%X\r\n", SENSOR->ACCEL_HW579->accel_address, sensors[1]<< 1);
	printf("GYRO    : 0x%X  = 0x%X\r\n", SENSOR->GYRO_HW579->gyro_address, sensors[2]<< 1);


#ifdef DEBUG_PRINT
	printf("MAGNETO : 0x%X\r\n", sensors[0] << 1);
	printf("ACCEL   : 0x%X\r\n", sensors[1] << 1);
	printf("GYRO    : 0x%X\r\n", sensors[2] << 1);
#endif

	return sensors;
}


void HW579_Init(HW579* SENSOR, float _MagnetoGauss)
{
	Magneto_Init(SENSOR->MAGNETO_HW579, _MagnetoGauss);
	Accel_Init(SENSOR->ACCEL_HW579);
	Gyro_Init(SENSOR->GYRO_HW579);


}


void I2C_Writebyte(void * SENSOR, uint8_t register_address, uint8_t data, uint8_t TYPE)
{
	uint8_t Trans[2] = {register_address, data};

	switch(TYPE)
	{
		case magneto:
			HAL_I2C_Master_Transmit(&(((HMC5883L *)SENSOR)->i2c), ((HMC5883L *)SENSOR)->magneto_address, Trans, 2, 10);
			printf("M : 0x%X\r\n", ((HMC5883L *)SENSOR)->magneto_address);
			break;

		case accel:
			HAL_I2C_Master_Transmit(&(((ADXL345 *)SENSOR)->i2c), hw579.ACCEL_HW579->accel_address, Trans, 2, 10);
			printf("A : 0x%X\r\n", hw579.ACCEL_HW579->accel_address);
			break;

		case gyro:
			HAL_I2C_Master_Transmit(&(((ITG3205 *)SENSOR)->i2c), ((ITG3205 *)SENSOR)->gyro_address, Trans, 2, 10);
			printf("G : 0x%X\r\n",  ((ITG3205 *)SENSOR)->gyro_address);
			break;

		default:
			printf("Wrong TYPE");
			break;
	}


}

uint8_t I2C_Readbyte(void * SENSOR, uint8_t register_address, uint8_t TYPE)
{
	uint8_t Trans[1] = {register_address};
	uint8_t Receive[1];

	switch(TYPE)
	{
		case magneto:
			HAL_I2C_Master_Transmit(&(((HMC5883L *)SENSOR)->i2c), ((HMC5883L *)SENSOR)->magneto_address, Trans, 1, 10);
			HAL_I2C_Master_Receive(&(((HMC5883L *)SENSOR)->i2c), ((HMC5883L *)SENSOR)->magneto_address, Receive, 1, 10);
			break;

		case accel:
			HAL_I2C_Master_Transmit(&(((ADXL345 *)SENSOR)->i2c), ((ADXL345 *)SENSOR)->accel_address, Trans, 1, 10);
			HAL_I2C_Master_Receive(&(((ADXL345 *)SENSOR)->i2c), ((ADXL345 *)SENSOR)->accel_address, Receive, 1, 10);
			break;

		case gyro:
			HAL_I2C_Master_Transmit(&(((ITG3205 *)SENSOR)->i2c), ((ITG3205 *)SENSOR)->gyro_address, Trans, 1, 10);
			HAL_I2C_Master_Receive(&(((ITG3205 *)SENSOR)->i2c), ((ITG3205 *)SENSOR)->gyro_address, Receive, 1, 10);
			break;

		default:
			printf("Wrong TYPE");
			break;
	}


	return Receive[0];
}
