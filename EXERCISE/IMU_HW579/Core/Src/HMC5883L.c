/*
 * HMC5883L.c
 *
 *  Created on: Apr 29, 2022
 *      Author: s_coo
 */


#include "HMC5883L.h"

HMC5883L MAGNETO = {.m_Scale = 1};


void Magneto_init()
{
	//printf("0x%X\r\n", MAGNETO.magneto_address);
}


void ReadRawAxix(void)
{
	uint8_t buffer[6];
	HAL_I2C_Mem_Read(&(MAGNETO.i2c), MAGNETO.magneto_address , DataRegisterBegin, I2C_MEMADD_SIZE_8BIT, buffer, sizeof(buffer), 10);
	MAGNETO.XAxis = (buffer[0] << 8) | buffer[1];
	MAGNETO.YAxis = (buffer[2] << 8) | buffer[3];
	MAGNETO.ZAxis = (buffer[4] << 8) | buffer[5];
}

void ReadScaledAxis(void)
{
	MAGNETO.scaled_XAxis = MAGNETO.XAxis * MAGNETO.m_Scale;
	MAGNETO.scaled_YAxis = MAGNETO.YAxis * MAGNETO.m_Scale;
	MAGNETO.scaled_ZAxis = MAGNETO.ZAxis * MAGNETO.m_Scale;
}


uint8_t SetScale(float gauss)
{
	uint8_t regValue = 0x00;
	if(gauss == 0.88)
	{
		regValue = 0x00;
		MAGNETO.m_Scale = 0.73;
	}
	else if(gauss == 1.3)
	{
		regValue = 0x01;
		MAGNETO.m_Scale = 0.92;
	}
	else if(gauss == 1.9)
	{
		regValue = 0x02;
		MAGNETO.m_Scale = 1.22;
	}
	else if(gauss == 2.5)
	{
		regValue = 0x03;
		MAGNETO.m_Scale = 1.52;
	}
	else if(gauss == 4.0)
	{
		regValue = 0x04;
		MAGNETO.m_Scale = 2.27;
	}
	else if(gauss == 4.7)
	{
		regValue = 0x05;
		MAGNETO.m_Scale = 2.56;
	}
	else if(gauss == 5.6)
	{
		regValue = 0x06;
		MAGNETO.m_Scale = 3.03;
	}
	else if(gauss == 8.1)
	{
		regValue = 0x07;
		MAGNETO.m_Scale = 4.35;
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
