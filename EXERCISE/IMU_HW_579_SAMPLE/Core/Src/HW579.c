/*
 * HW579.c
 *
 *  Created on: Apr 28, 2022
 *      Author: user
 */
#include "HW579.h"

extern I2C_HandleTypeDef hi2c1;

HW579 hw579 = {.gyro_address = 0xD0};

void Gyro_Writebyte(HW579 * I2C,uint8_t register_address,uint8_t data){
    uint8_t Trans[2]={register_address, data};
    HAL_I2C_Master_Transmit(&(I2C->i2c), I2C->gyro_address,Trans,2,10);
}

uint8_t Gyro_Readbyte(HW579 * I2C,uint8_t register_address){
    uint8_t Trans[1]={register_address};
    uint8_t Receive[1];
    HAL_I2C_Master_Transmit(&(I2C->i2c), I2C->gyro_address,Trans,1,10);
    HAL_I2C_Master_Receive(&(I2C->i2c),I2C->gyro_address,Receive,1,10);

    return Receive[0];
}

void init_HW579(HW579* I2C){

	I2C = &hw579;
	I2C->i2c = hi2c1;

    Gyro_Writebyte(I2C,PWR_MGM,0x00);

    HAL_Delay(100);
    Gyro_Writebyte(I2C,PWR_MGM,0x01);

    Gyro_Writebyte(I2C,SMPLRT_DIV,0X00);

    Gyro_Writebyte(I2C,DLPFFS_FS_SEL, 0x03 << 3);

    Gyro_Writebyte(I2C,DLPFFS_DLPF_CFG, BW256_SR8);

    Gyro_Writebyte(I2C,PWRMGM_CLK_SEL, PLL_ZGYRO_REF);

    Gyro_Writebyte(I2C,INTCFG_ITG_RDY_EN, 0x01 <<2);

    Gyro_Writebyte(I2C,INTCFG_RAW_RDY_EN, 0x01);

    HAL_Delay(GYROSTART_UP_DELAY);

}

void MPU_read_acc_gyro(HW579* I2C){
    uint8_t databuf[6];
    int16_t tempmpugyx,tempmpugyy,tempmpugyz;

    I2C = &hw579;
    I2C->i2c = hi2c1;

    HAL_I2C_Mem_Read(&(I2C->i2c), I2C->gyro_address,GYRO_XOUT,I2C_MEMADD_SIZE_8BIT,databuf,6,10);
    tempmpugyx=((databuf[0]<<8)|databuf[1]);
    tempmpugyy=((databuf[2]<<8)|databuf[3]);
    tempmpugyz=((databuf[4]<<8)|databuf[5]);


    I2C->gyro_X = ((float)(tempmpugyx))/16.4;
    I2C->gyro_Y = ((float)(tempmpugyy))/16.4;
    I2C->gyro_Z = ((float)(tempmpugyz))/16.4;
}
