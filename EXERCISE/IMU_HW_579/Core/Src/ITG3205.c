/*
 * ITG3205.c
 *
 *  Created on: 2022. 4. 24.
 *      Author: s_coo
 */

#include "ITG3205.h"





void Gyro_Writebyte(ITG3205 * I2C, uint8_t register_address, uint8_t data)
{
	uint8_t Trans[2] = {register_address, data};
	HAL_I2C_Master_Transmit(&(I2C->i2c), I2C->gyro_address, Trans, 2, 10);
}

uint8_t Gyro_Readbyte(ITG3205 * I2C, uint8_t register_address)
{
	uint8_t Trans[1] = {register_address};
	uint8_t Receive[1];
	HAL_I2C_Master_Transmit(&(I2C->i2c), I2C->gyro_address, Trans, 1, 10);
	HAL_I2C_Master_Receive(&(I2C->i2c), I2C->gyro_address, Receive, 1, 10);

	return Receive[0];
}

void Gyro_init(ITG3205 * itg3205)
{
	Gyro_Writebyte(itg3205, PWR_MGM, 0x00);
	HAL_Delay(100);
	Gyro_Writebyte(itg3205, PWR_MGM, 0x01);
	Gyro_Writebyte(itg3205, SMPLRT_DIV, 0x01);
	Gyro_Writebyte(itg3205, PWR_MGM, 0x01);
	Gyro_Writebyte(itg3205, PWR_MGM, 0x01);


}

