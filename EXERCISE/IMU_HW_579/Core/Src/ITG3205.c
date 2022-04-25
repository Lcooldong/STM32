/*
 * ITG3205.c
 *
 *  Created on: 2022. 4. 24.
 *      Author: s_coo
 */

#include "ITG3205.h"



float scalefactor[3];
uint16_t offsets[3];
uint8_t gyro_buff[6];
extern HW579 hw579;

void Gyro_Writebyte(HW579 * I2C, uint8_t register_address, uint8_t data)
{
	uint8_t Trans[2] = {register_address, data};
	HAL_I2C_Master_Transmit(&(I2C->i2c), I2C->gyro_address, Trans, 2, 10);
}

uint8_t Gyro_Readbyte(HW579 * I2C, uint8_t register_address)
{
	uint8_t Trans[1] = {register_address};
	uint8_t Receive[1];
	HAL_I2C_Master_Transmit(&(I2C->i2c), I2C->gyro_address, Trans, 1, 10);
	HAL_I2C_Master_Receive(&(I2C->i2c), I2C->gyro_address, Receive, 1, 10);

	return Receive[0];
}


void Gyro_init(HW579 *I2C)	// struct -> i2c
{
//	Gyro_Writebyte(I2C, PWR_MGM, 0x00);
//	HAL_Delay(100);
//	Gyro_Writebyte(I2C, PWR_MGM, PLL_XGYRO_REF);
//	Gyro_Writebyte(I2C, SMPLRT_DIV, NOSRDIVIDER);
//	Gyro_Writebyte(I2C, DLPF_FS, RANGE2000);
//	Gyro_Writebyte(I2C, DLPF_FS, BW256_SR8);
//	Gyro_Writebyte(I2C, INT_CFG, INTCFG_ITG_RDY_EN);
//	Gyro_Writebyte(I2C, INT_CFG, INTCFG_RAW_RDY_EN);

	I2C_Writebyte(I2C, PWR_MGM, 0x00, magneto);
	HAL_Delay(100);
	I2C_Writebyte(I2C, PWR_MGM, PLL_XGYRO_REF, magneto);
	I2C_Writebyte(I2C, SMPLRT_DIV, NOSRDIVIDER, magneto);
	I2C_Writebyte(I2C, DLPF_FS, RANGE2000, magneto);
	I2C_Writebyte(I2C, DLPF_FS, BW256_SR8, magneto);
	I2C_Writebyte(I2C, INT_CFG, INTCFG_ITG_RDY_EN, magneto);
	I2C_Writebyte(I2C, INT_CFG, INTCFG_RAW_RDY_EN, magneto);

	HAL_Delay(GYROSTART_UP_DELAY);
}

void Gyro_Read(HW579 *hw579)
{
	uint8_t databuf[8];
	int16_t tempature, raw_x, raw_y, raw_z;
	HAL_I2C_Mem_Read(&(hw579->i2c), hw579->gyro_address , TEMP_OUT, I2C_MEMADD_SIZE_8BIT, databuf, sizeof(databuf), 10);
	tempature = (databuf[0] << 8) | databuf[1];
	raw_x = (databuf[2] << 8) | databuf[3];
	raw_y = (databuf[4] << 8) | databuf[5];
	raw_z = (databuf[6] << 8) | databuf[7];

	for(int i=0; i < 6; i++)
	{
		printf("%u\r\n", databuf[i]);
	}

	printf("%d %u %u %u\r\n", tempature, raw_x, raw_y, raw_z);
}


void readGyroRaw(uint16_t _GyroXYZ[3], HW579 *hw579)
{
	uint8_t databuf[6];
	HAL_I2C_Mem_Read(&(hw579->i2c), hw579->gyro_address , GYRO_XOUT, I2C_MEMADD_SIZE_8BIT, databuf, sizeof(databuf), 10);
	_GyroXYZ[0] = databuf[0] << 8 | databuf[1];
	_GyroXYZ[1] = databuf[2] << 8 | databuf[3];
	_GyroXYZ[2] = databuf[4] << 8 | databuf[5];
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
	state = HAL_I2C_Mem_Read(&(hw579.i2c), hw579.gyro_address, INT_STATUS, 1, buff, 1, 10);
	if(state != HAL_OK) while(HAL_I2C_GetState(&hw579.i2c) != HAL_I2C_STATE_READY);
	return (buff[0] & INTSTATUS_RAW_DATA_RDY);
}


void setScaleFactor(float _Xcoeff, float _Ycoeff, float _Zcoeff, bool _Radians)
{
	scalefactor[0] = 14.375 * _Xcoeff;
	scalefactor[1] = 14.375 * _Ycoeff;
	scalefactor[2] = 14.375 * _Zcoeff;


	if (_Radians){
		scalefactor[0] /= 0.0174532925;//0.0174532925 = PI/180
		scalefactor[1] /= 0.0174532925;
		scalefactor[2] /= 0.0174532925;
	}
}

void setOffsets(uint16_t _Xoffset, uint16_t _Yoffset, uint16_t _Zoffset )
{
	offsets[0] = _Xoffset;
	offsets[1] = _Yoffset;
	offsets[2] = _Zoffset;
}

void zeroCalibrate(uint16_t totSamples, uint16_t sampleDelayMS)
{
	float tmpOffsets[] = {0,0, 0};
	uint16_t xyz[3];

	for(int i = 0; i < totSamples; i++)
	{
		HAL_Delay(sampleDelayMS);
		readGyroRaw(xyz, &hw579);
		tmpOffsets[0] += xyz[0];
		tmpOffsets[1] += xyz[1];
		tmpOffsets[2] += xyz[2];

	}
	setOffsets(-tmpOffsets[0] / totSamples + 0.5, -tmpOffsets[1] / totSamples + 0.5, -tmpOffsets[2] / totSamples + 0.5);
}

