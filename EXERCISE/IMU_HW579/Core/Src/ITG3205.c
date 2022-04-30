/*
 * ITG3205.c
 *
 *  Created on: Apr 29, 2022
 *      Author: s_coo
 */

#include "ITG3205.h"

extern I2C_HandleTypeDef hi2c1;

ITG3205 GYRO = {.gyro_address = 0xD0};

void Gyro_Writebyte(ITG3205 * SENSOR,uint8_t register_address,uint8_t data){
    uint8_t Trans[2]={register_address, data};
    HAL_I2C_Master_Transmit(&(SENSOR->i2c), SENSOR->gyro_address,Trans,2,10);
}

uint8_t Gyro_Readbyte(ITG3205 * SENSOR,uint8_t register_address){
    uint8_t Trans[1]={register_address};
    uint8_t Receive[1];
    HAL_I2C_Master_Transmit(&(SENSOR->i2c), SENSOR->gyro_address,Trans,1,10);
    HAL_I2C_Master_Receive(&(SENSOR->i2c),SENSOR->gyro_address,Receive,1,10);

    return Receive[0];
}

void Gyro_Init(ITG3205* SENSOR){

	SENSOR = &GYRO;
	SENSOR->i2c = hi2c1;

    Gyro_Writebyte(SENSOR,PWR_MGM,0x00);

    HAL_Delay(10);
    Gyro_Writebyte(SENSOR,PWR_MGM,0x01);

    Gyro_Writebyte(SENSOR,SMPLRT_DIV,0X00);

    Gyro_Writebyte(SENSOR,DLPFFS_FS_SEL, RANGE2000 << 3);

    Gyro_Writebyte(SENSOR,DLPFFS_DLPF_CFG, BW256_SR8);

    Gyro_Writebyte(SENSOR,PWRMGM_CLK_SEL, PLL_ZGYRO_REF);

    Gyro_Writebyte(SENSOR,INTCFG_ITG_RDY_EN, INTSTATUS_ITG_RDY);

    Gyro_Writebyte(SENSOR,INTCFG_RAW_RDY_EN, INTSTATUS_RAW_DATA_RDY);

    HAL_Delay(GYROSTART_UP_DELAY);

}

void Read_Gyro(ITG3205* SENSOR){
    uint8_t databuf[6];
    int16_t raw_X,raw_Y,raw_Z;

    SENSOR = &GYRO;
    SENSOR->i2c = hi2c1;

    HAL_I2C_Mem_Read(&(SENSOR->i2c), SENSOR->gyro_address,GYRO_XOUT,I2C_MEMADD_SIZE_8BIT,databuf,6,10);
    raw_X = ((databuf[0]<<8)|databuf[1]);
    raw_Y = ((databuf[2]<<8)|databuf[3]);
    raw_Z = ((databuf[4]<<8)|databuf[5]);

    SENSOR->raw_gyro_X = raw_X;
    SENSOR->raw_gyro_Y = raw_Y;
    SENSOR->raw_gyro_Z = raw_Z;


    SENSOR->gyro_X = ((float)(raw_X))/16.4 + 20;
    SENSOR->gyro_Y = ((float)(raw_Y))/16.4;
    SENSOR->gyro_Z = ((float)(raw_Z))/16.4;
}

void Calibrate_Gyro(ITG3205* SENSOR)
{
	uint8_t cal = 10;
	int temp_X = 0, temp_Y = 0, temp_Z = 0;

	for(uint8_t i=0; i<cal; i++)
	{
		Read_Gyro(SENSOR);

		temp_X += SENSOR->raw_gyro_X;
		temp_Y += SENSOR->raw_gyro_Y;
		temp_Z += SENSOR->raw_gyro_Z;

		HAL_Delay(100);
	}

	temp_X /= cal;
	temp_Y /= cal;
	temp_Z /= cal;

	SENSOR->base_gyro_X = temp_X;
	SENSOR->base_gyro_Y = temp_Y;
	SENSOR->base_gyro_Z = temp_Z;

}

void Get_Gyro(ITG3205* SENSOR)
{
	Read_Gyro(SENSOR);
	SENSOR->scaled_gyro_X = (SENSOR->raw_gyro_X - SENSOR->base_gyro_X)/DLPFFS_FS_SEL;	// FULL_SCALE
	SENSOR->scaled_gyro_Y = (SENSOR->raw_gyro_Y - SENSOR->base_gyro_Y)/DLPFFS_FS_SEL;
	SENSOR->scaled_gyro_Z = (SENSOR->raw_gyro_Z - SENSOR->base_gyro_Z)/DLPFFS_FS_SEL;
}




uint8_t Get_Gyro_SampleRateDiv(ITG3205* SENSOR)
{
	return Gyro_Readbyte(SENSOR, SMPLRT_DIV);
}

void Set_Gyro_SampleRateDiv(ITG3205* SENSOR, uint8_t _SampleRate)
{
	Gyro_Writebyte(SENSOR, SMPLRT_DIV, _SampleRate);
}

uint8_t Get_Gyro_FSRange(ITG3205* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Gyro_Readbyte(SENSOR, DLPF_FS);
	return (received_data & DLPFFS_FS_SEL) >> 3;
}

void Set_Gyro_FSRange(ITG3205* SENSOR, uint8_t _Range)
{
	uint8_t received_data[1];
	received_data[0] = Get_Gyro_FSRange(SENSOR);
	Gyro_Writebyte(SENSOR, DLPF_FS, (received_data[0] & ~DLPFFS_FS_SEL) |(_Range << 3) );
}

uint8_t Get_Gyro_FilterBW(ITG3205* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Gyro_Readbyte(SENSOR, DLPF_FS);
	return (received_data[0] & DLPFFS_DLPF_CFG);
}


