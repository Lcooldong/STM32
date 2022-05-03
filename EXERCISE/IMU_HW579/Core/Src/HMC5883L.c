/*
 * HMC5883L.c
 *
 *  Created on: Apr 29, 2022
 *      Author: s_coo
 */


#include "HMC5883L.h"

HMC5883L MAGNETO = {.m_Scale = 1};
//extern I2C_HandleTypeDef hi2c1;

void Magneto_Init(HMC5883L* SENSOR)
{
	SENSOR->i2c = hi2c1;
	//printf("0x%X\r\n", MAGNETO.magneto_address);
}


void ReadRawAxis(HMC5883L* SENSOR)
{
	uint8_t buffer[6];


	HAL_I2C_Mem_Read(&(SENSOR->i2c), SENSOR->magneto_address , DataRegisterBegin, I2C_MEMADD_SIZE_8BIT, buffer, sizeof(buffer), 10);
	SENSOR->XAxis = (buffer[0] << 8) | buffer[1];
	SENSOR->YAxis = (buffer[2] << 8) | buffer[3];
	SENSOR->ZAxis = (buffer[4] << 8) | buffer[5];
}

void ReadScaledAxis(HMC5883L* SENSOR)
{
	SENSOR->scaled_XAxis = SENSOR->XAxis * SENSOR->m_Scale;
	SENSOR->scaled_YAxis = SENSOR->YAxis * SENSOR->m_Scale;
	SENSOR->scaled_ZAxis = SENSOR->ZAxis * SENSOR->m_Scale;
}

void Read_Magneto(HMC5883L* SENSOR)
{

}


uint8_t SetScale(HMC5883L* SENSOR, float gauss)
{
	uint8_t regValue = 0x00;
	if(gauss == 0.88)
	{
		regValue = 0x00;
		SENSOR->m_Scale = 0.73;
	}
	else if(gauss == 1.3)
	{
		regValue = 0x01;
		SENSOR->m_Scale = 0.92;
	}
	else if(gauss == 1.9)
	{
		regValue = 0x02;
		SENSOR->m_Scale = 1.22;
	}
	else if(gauss == 2.5)
	{
		regValue = 0x03;
		SENSOR->m_Scale = 1.52;
	}
	else if(gauss == 4.0)
	{
		regValue = 0x04;
		SENSOR->m_Scale = 2.27;
	}
	else if(gauss == 4.7)
	{
		regValue = 0x05;
		SENSOR->m_Scale = 2.56;
	}
	else if(gauss == 5.6)
	{
		regValue = 0x06;
		SENSOR->m_Scale = 3.03;
	}
	else if(gauss == 8.1)
	{
		regValue = 0x07;
		SENSOR->m_Scale = 4.35;
	}
	else
		return ErrorCode_1_Num;

	regValue = regValue << 5;
	//I2C_Writebyte(&MAGNETO, ConfigurationRegisterB, regValue, magneto);

	return regValue;
}


void SetMeasurementMode(uint8_t mode)
{
	//I2C_Writebyte(&MAGNETO, ModeRegister, mode, magneto);
}


char* GetErrorText(uint8_t errorCode)
{
	if(ErrorCode_1_Num == 1)
		return ErrorCode_1;

	return "Error not defined.";
}
