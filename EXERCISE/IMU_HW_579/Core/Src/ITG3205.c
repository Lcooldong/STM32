/*
 * ITG3205.c
 *
 *  Created on: 2022. 4. 24.
 *      Author: s_coo
 */

#include "ITG3205.h"


ITG3205 GYRO;
extern HW579 hw579;

void Gyro_Writebyte(uint8_t register_address, uint8_t data)
{
	uint8_t Trans[2] = {register_address, data};
	HAL_I2C_Master_Transmit(&(GYRO.i2c), GYRO.gyro_address, Trans, 2, 10);
}

uint8_t Gyro_Readbyte(uint8_t register_address)
{
	uint8_t Trans[1] = {register_address};
	uint8_t Receive[1];
	HAL_I2C_Master_Transmit(&(GYRO.i2c), GYRO.gyro_address, Trans, 1, 10);
	HAL_I2C_Master_Receive(&(GYRO.i2c), GYRO.gyro_address, Receive, 1, 10);

	return Receive[0];
}


void Gyro_init(ITG3205* SENSOR)	// struct -> i2c
{

	printf("INIT G : 0x%X\r\n", GYRO.gyro_address);
	GYRO.i2c = SENSOR->i2c;

	I2C_Writebyte(&GYRO, PWR_MGM, 0x00, gyro);
	HAL_Delay(100);
	I2C_Writebyte(&GYRO, PWR_MGM, 0x01, gyro);
	I2C_Writebyte(&GYRO, SMPLRT_DIV, NOSRDIVIDER, gyro);
	I2C_Writebyte(&GYRO, DLPFFS_FS_SEL, RANGE2000 << 3, gyro);
	I2C_Writebyte(&GYRO, DLPFFS_DLPF_CFG, BW256_SR8, gyro);
	I2C_Writebyte(&GYRO, PWRMGM_CLK_SEL, PLL_ZGYRO_REF, gyro);
	I2C_Writebyte(&GYRO, INTCFG_ITG_RDY_EN, INTSTATUS_ITG_RDY, gyro);
	I2C_Writebyte(&GYRO, INTCFG_RAW_RDY_EN, INTSTATUS_RAW_DATA_RDY, gyro);


	HAL_Delay(GYROSTART_UP_DELAY);
}

void Gyro_Read(I2C_HandleTypeDef *i2c)
{


	//GYRO.i2c = *i2c;
	GYRO.i2c = hi2c1;
	//printf("Gyro_Read : 0x%X\r\n", GYRO.gyro_address);

	//readGyroRaw();
	uint8_t gyro_buf[8];
	HAL_I2C_Mem_Read(&(GYRO.i2c), GYRO.gyro_address, TEMP_OUT, I2C_MEMADD_SIZE_8BIT, gyro_buf, sizeof(gyro_buf), 10);
	//HAL_I2C_Mem_Read(&(SENSOR->i2c), SENSOR->gyro_address, TEMP_OUT, I2C_MEMADD_SIZE_8BIT, gyro_buf, sizeof(gyro_buf), 10);
	GYRO.scaled_gyro_temp = ((float)((gyro_buf[0] << 8) | gyro_buf[1]))/16.4;
	GYRO.scaled_gyro_X = ((float)((gyro_buf[2] << 8) | gyro_buf[3]))/16.4;
	GYRO.scaled_gyro_Y = ((float)((gyro_buf[4] << 8) | gyro_buf[5]))/16.4;
	GYRO.scaled_gyro_Z = ((float)((gyro_buf[6] << 8) | gyro_buf[7]))/16.4;


	printf("%8.2f %8.2f %8.2f\r\n", GYRO.scaled_gyro_X, GYRO.scaled_gyro_Y, GYRO.scaled_gyro_Z);

}


void readGyroRaw(void)
{
	uint8_t databuf[6];
	HAL_I2C_Mem_Read(&(GYRO.i2c), GYRO.gyro_address , GYRO_XOUT, I2C_MEMADD_SIZE_8BIT, databuf, sizeof(databuf), 10);
	GYRO.gyro_X = databuf[0] << 8 | databuf[1];
	GYRO.gyro_Y = databuf[2] << 8 | databuf[3];
	GYRO.gyro_Z = databuf[4] << 8 | databuf[5];

}


void setDevAddr(uint8_t _addr)
{

}


void setSampleRateDiv()
{

}

void setFSRange()
{

}

void setFilterBW()
{

}

void setINTLogiclvl()
{

}

void setINTDriveType()
{

}

void setLatchMode()
{

}

void setLatchClearMode()
{

}

void setITGReady()
{

}

void setRawDataReady()
{

}

bool isRawDataReady(void)
{
	uint8_t buff[6];
	HAL_StatusTypeDef state;
	state = HAL_I2C_Mem_Read(&hw579.i2c, hw579.GYRO_HW579->gyro_address, INT_STATUS, 1, buff, 1, 10);
	if(state != HAL_OK) while(HAL_I2C_GetState(&hw579.i2c) != HAL_I2C_STATE_READY);
	return (buff[0] & INTSTATUS_RAW_DATA_RDY);
}


void setScaleFactor(float _Xcoeff, float _Ycoeff, float _Zcoeff, bool _Radians)
{
	GYRO.scalefactor_X = 14.375 * _Xcoeff;
	GYRO.scalefactor_Y = 14.375 * _Ycoeff;
	GYRO.scalefactor_Z = 14.375 * _Zcoeff;


	if (_Radians){
		GYRO.scalefactor_X /= 0.0174532925;//0.0174532925 = PI/180
		GYRO.scalefactor_Y /= 0.0174532925;
		GYRO.scalefactor_Z /= 0.0174532925;
	}
}

void setOffsets(uint16_t _Xoffset, uint16_t _Yoffset, uint16_t _Zoffset )
{
	GYRO.offset_X = _Xoffset;
	GYRO.offset_Y = _Yoffset;
	GYRO.offset_Z = _Zoffset;
}

void zeroCalibrate(uint16_t totSamples, uint16_t sampleDelayMS)
{
	float tmpOffsets[] = {0, 0, 0};


	for(int i = 0; i < totSamples; i++)
	{
		HAL_Delay(sampleDelayMS);
		readGyroRaw();
		tmpOffsets[0] += GYRO.gyro_X;
		tmpOffsets[1] += GYRO.gyro_Y;
		tmpOffsets[2] += GYRO.gyro_Z;

	}
	setOffsets(-tmpOffsets[0] / totSamples + 0.5, -tmpOffsets[1] / totSamples + 0.5, -tmpOffsets[2] / totSamples + 0.5);
}

