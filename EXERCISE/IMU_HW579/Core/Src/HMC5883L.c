/*
 * HMC5883L.c
 *
 *  Created on: Apr 29, 2022
 *      Author: s_coo
 */


#include "HMC5883L.h"

HMC5883L MAGNETO = {.magneto_address = 0x3C, .m_Scale = 1};
//extern I2C_HandleTypeDef hi2c1;

void Magneto_Writebyte(HMC5883L * SENSOR, uint8_t register_address, uint8_t data)
{
    uint8_t Trans[2]={register_address, data};
    HAL_I2C_Master_Transmit(&(SENSOR->i2c), SENSOR->magneto_address, Trans,2,10);
}

uint8_t Magneto_Readbyte(HMC5883L * SENSOR, uint8_t register_address)
{
	HAL_StatusTypeDef state;
    uint8_t Trans[1]={register_address};
    uint8_t Receive[1];

    HAL_I2C_Master_Transmit(&(SENSOR->i2c), SENSOR->magneto_address,Trans,1,10);
    state = HAL_I2C_Master_Receive(&(SENSOR->i2c),SENSOR->magneto_address, Receive,1,10);
    if(state != HAL_OK)
    {
    	SENSOR->status = 0;
    	SENSOR->error_code = 1;
    	while(HAL_I2C_GetState(&(SENSOR->i2c)) != HAL_I2C_STATE_READY);
    }


    return Receive[0];
}


void Magneto_Init(HMC5883L* SENSOR, float gauss)
{
	SENSOR->i2c = hi2c1;
	SENSOR->error_code = SetScale(SENSOR, gauss);
	if(SENSOR->error_code == 1)
	{
		printf("Set Scale Error.\r\n");
	}
	SENSOR->error_code = SetMeasurementMode(SENSOR, Measurement_Continuous);
	if(SENSOR->error_code == 1)
	{
		printf("Set Mode Error.\r\n");
	}

}


void ReadRawAxis(HMC5883L* SENSOR)
{
	uint8_t buffer[6];

	HAL_I2C_Mem_Read(&(SENSOR->i2c), SENSOR->magneto_address , DataRegisterBegin, I2C_MEMADD_SIZE_8BIT, buffer, sizeof(buffer), 10);
	SENSOR->XAxis = (int16_t)(buffer[0] << 8) | buffer[1];
	SENSOR->YAxis = (int16_t)(buffer[2] << 8) | buffer[3];
	SENSOR->ZAxis = (int16_t)(buffer[4] << 8) | buffer[5];
}

void ReadScaledAxis(HMC5883L* SENSOR)
{
	SENSOR->scaled_XAxis = SENSOR->XAxis * SENSOR->m_Scale;
	SENSOR->scaled_YAxis = SENSOR->YAxis * SENSOR->m_Scale;
	SENSOR->scaled_ZAxis = SENSOR->ZAxis * SENSOR->m_Scale;
}

void Read_Magneto(HMC5883L* SENSOR)
{
	uint8_t buffer[6];

	HAL_I2C_Mem_Read(&(SENSOR->i2c), SENSOR->magneto_address , DataRegisterBegin, I2C_MEMADD_SIZE_8BIT, buffer, sizeof(buffer), 10);
	SENSOR->XAxis = (int16_t)(buffer[0] << 8) | buffer[1];
	SENSOR->YAxis = (int16_t)(buffer[2] << 8) | buffer[3];
	SENSOR->ZAxis = (int16_t)(buffer[4] << 8) | buffer[5];

	SENSOR->scaled_XAxis = SENSOR->XAxis * SENSOR->m_Scale;
	SENSOR->scaled_YAxis = SENSOR->YAxis * SENSOR->m_Scale;
	SENSOR->scaled_ZAxis = SENSOR->ZAxis * SENSOR->m_Scale;


}

void Get_Heading_Magneto(HMC5883L* SENSOR)
{
	//static const double PI = 3.141592653589;
	float heading = atan2(SENSOR->scaled_YAxis, SENSOR->scaled_XAxis);
	//float declinationAngle = 0.0457;
	float declinationAngle = -0.1545;
    heading += declinationAngle;

    if(heading < 0) heading += 2*M_PI;

    if(heading > 2*M_PI) heading -= 2*M_PI;

    float headingDegrees = heading * 180/M_PI;

    SENSOR->heading = heading;
    SENSOR->headingDegrees = headingDegrees;
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
	Magneto_Writebyte(SENSOR, ConfigurationRegisterB, regValue);

	return regValue;
}


uint8_t SetMeasurementMode(HMC5883L* SENSOR , uint8_t mode)
{
	Magneto_Writebyte(SENSOR, ModeRegister, mode);
	if((mode == 0x00) | (mode == 0x01) | (mode == 0x03)) return 0;
	else return ErrorCode_1_Num;

}


char* GetErrorText(uint8_t errorCode)
{
	if(ErrorCode_1_Num == 1)
		return ErrorCode_1;

	return "Error not defined.";
}
