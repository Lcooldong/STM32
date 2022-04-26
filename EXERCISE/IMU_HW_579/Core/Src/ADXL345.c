/*
 * ADXL345.c
 *
 *  Created on: 2022. 4. 26.
 *      Author: s_coo
 */


#include "ADXL345.h"


uint8_t error_code;       // Initial state
double gains[3] = {0.00376390, 0.00376009, 0.00349265};        // counts to Gs
uint8_t accel_buf[6] ;
ADXL345 ACCEL;
extern HW579 hw579;

void powerOn(ADXL345 *ACCEL)
{
	I2C_Writebyte(ACCEL, ADXL345_POWER_CTL, 0, accel);
	I2C_Writebyte(ACCEL, ADXL345_POWER_CTL, 16, accel);
	I2C_Writebyte(ACCEL, ADXL345_POWER_CTL, 8, accel);

}

void Accel_Read()
{
	HAL_I2C_Mem_Read(&(ACCEL.i2c), ACCEL.accel_address , ADXL345_DATAX0, I2C_MEMADD_SIZE_8BIT, accel_buf, sizeof(accel_buf), 10);
	ACCEL.accel_X = (((int)accel_buf[1]) << 8) | accel_buf[0];
	ACCEL.accel_Y = (((int)accel_buf[3]) << 8) | accel_buf[2];
	ACCEL.accel_Z = (((int)accel_buf[5]) << 8) | accel_buf[4];
}

void get_Gxyz(double *xyz)
{
	uint16_t i;
	uint16_t xyz_int[3];
	Accel_Read(&ACCEL);
	for(i=0; i<3; i++)
	{
		xyz[i] = xyz_int[i] * gains[i];
	}
}

void Accel_Writebyte(uint8_t address, uint8_t val)
{

}

uint8_t Accel_Readbyte()
{

	return 0;
}


