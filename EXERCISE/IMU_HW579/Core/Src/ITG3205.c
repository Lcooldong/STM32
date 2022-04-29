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

    HAL_Delay(100);
    Gyro_Writebyte(SENSOR,PWR_MGM,0x01);

    Gyro_Writebyte(SENSOR,SMPLRT_DIV,0X00);

    Gyro_Writebyte(SENSOR,DLPFFS_FS_SEL, 0x03 << 3);

    Gyro_Writebyte(SENSOR,DLPFFS_DLPF_CFG, BW256_SR8);

    Gyro_Writebyte(SENSOR,PWRMGM_CLK_SEL, PLL_ZGYRO_REF);

    Gyro_Writebyte(SENSOR,INTCFG_ITG_RDY_EN, 0x01 <<2);

    Gyro_Writebyte(SENSOR,INTCFG_RAW_RDY_EN, 0x01);

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


    SENSOR->gyro_X = ((float)(raw_X))/16.4 + 20;
    SENSOR->gyro_Y = ((float)(raw_Y))/16.4;
    SENSOR->gyro_Z = ((float)(raw_Z))/16.4;
}

