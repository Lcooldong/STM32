/*
 * ADXL345.c
 *
 *  Created on: Apr 29, 2022
 *      Author: s_coo
 */


#include "ADXL345.h"


ADXL345 ACCEL = { .accel_address = 0xA6, .gain_X = 0.00376390, .gain_Y = 0.00376009, .gain_Z = 0.00349265};


void Accel_Writebyte(ADXL345 * SENSOR, uint8_t register_address, uint8_t data)
{
    uint8_t Trans[2]={register_address, data};
    HAL_I2C_Master_Transmit(&(SENSOR->i2c), SENSOR->accel_address, Trans,2,10);
}

uint8_t Accel_Readbyte(ADXL345 * SENSOR,uint8_t register_address)
{
	HAL_StatusTypeDef state;
    uint8_t Trans[1]={register_address};
    uint8_t Receive[1];

    HAL_I2C_Master_Transmit(&(SENSOR->i2c), SENSOR->accel_address,Trans,1,10);
    state = HAL_I2C_Master_Receive(&(SENSOR->i2c),SENSOR->accel_address, Receive,1,10);
    if(state != HAL_OK)
    {
    	SENSOR->status = ADXL345_ERROR;
    	SENSOR->error_code = ADXL345_READ_ERROR;
    	while(HAL_I2C_GetState(&(SENSOR->i2c)) != HAL_I2C_STATE_READY);
    }


    return Receive[0];
}


void Accel_init(ADXL345* SENSOR)
{
	SENSOR->i2c = hi2c1;

	Accel_Writebyte(SENSOR, ADXL345_POWER_CTL, 0);
	Accel_Writebyte(SENSOR, ADXL345_POWER_CTL, 16);
	Accel_Writebyte(SENSOR, ADXL345_DATA_FORMAT, 2);
	Accel_Writebyte(SENSOR, ADXL345_POWER_CTL, 8);

}



void Read_Accel(ADXL345* SENSOR)
{
	uint8_t accel_buf[6];
	SENSOR->i2c = hi2c1;

	HAL_I2C_Mem_Read(&(SENSOR->i2c), SENSOR->accel_address , ADXL345_DATAX0, I2C_MEMADD_SIZE_8BIT, accel_buf, sizeof(accel_buf), 10);
	SENSOR->raw_accel_X = (int16_t)((accel_buf[1]) << 8) | accel_buf[0];
	SENSOR->raw_accel_Y = (int16_t)((accel_buf[3]) << 8) | accel_buf[2];
	SENSOR->raw_accel_Z = (int16_t)((accel_buf[5]) << 8) | accel_buf[4];

	SENSOR->scaled_accel_X = SENSOR->raw_accel_X * SENSOR->gain_X;
	SENSOR->scaled_accel_Y = SENSOR->raw_accel_Y * SENSOR->gain_Y;
	SENSOR->scaled_accel_Z = SENSOR->raw_accel_Z * SENSOR->gain_Z;


}

void Get_Accel(ADXL345* SENSOR)
{
	Read_Accel(SENSOR);

}




















