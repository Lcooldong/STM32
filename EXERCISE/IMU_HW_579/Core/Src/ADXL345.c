/*
 * ADXL345.c
 *
 *  Created on: 2022. 4. 26.
 *      Author: s_coo
 */


#include "ADXL345.h"


uint8_t error_code;       // Initial state
double gains[3] = {0.00376390, 0.00376009, 0.00349265};        // counts to Gs
uint8_t accel_buff[6] ;
ADXL345 ACCEL;
extern HW579 hw579;

void powerOn(HW579 *I2C)
{
	I2C_Writebyte(I2C, ADXL345_POWER_CTL, 0, accel);
	I2C_Writebyte(I2C, ADXL345_POWER_CTL, 16, accel);
	I2C_Writebyte(I2C, ADXL345_POWER_CTL, 8, accel);

}

void Accel_Read(HW579 *I2C)
{
	HAL_I2C_Mem_Read(&(I2C->i2c), I2C->accel_address , ADXL345_DATAX0, I2C_MEMADD_SIZE_8BIT, accel_buff, sizeof(accel_buff), 10);
	ACCEL.accel_x = (((int)accel_buf[1]) << 8) | accel_buf[0];
	ACCEL.accel_y = (((int)accel_buf[3]) << 8) | accel_buf[2];
	ACCEL.accel_z = (((int)accel_buf[5]) << 8) | accel_buf[4];
}

void get_Gxyz(double *xyz)
{
	uint16_t i;
	uint16_t xyz_int[3];
	Accel_Read_Array(&hw579, xyz_int);
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


