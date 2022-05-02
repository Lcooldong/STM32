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

    SENSOR->i2c = hi2c1;

    HAL_I2C_Mem_Read(&(SENSOR->i2c), SENSOR->gyro_address,GYRO_XOUT,I2C_MEMADD_SIZE_8BIT,databuf,6,10);
    raw_X = ((databuf[0]<<8)|databuf[1]);
    raw_Y = ((databuf[2]<<8)|databuf[3]);
    raw_Z = ((databuf[4]<<8)|databuf[5]);

    SENSOR->raw_gyro_X = raw_X;
    SENSOR->raw_gyro_Y = raw_Y;
    SENSOR->raw_gyro_Z = raw_Z;


    SENSOR->gyro_X = ((float)(raw_X))/16.4 + SENSOR->offset_X;
    SENSOR->gyro_Y = ((float)(raw_Y))/16.4 + SENSOR->offset_Y;
    SENSOR->gyro_Z = ((float)(raw_Z))/16.4 + SENSOR->offset_Z;
}

void Calibrate_Gyro(ITG3205* SENSOR, uint16_t totSamples, uint16_t sampleDelayMS)
{
	int temp_X = 0, temp_Y = 0, temp_Z = 0;

	for(uint8_t i=0; i<totSamples; i++)
	{
		HAL_Delay(sampleDelayMS);

		Read_Gyro(SENSOR);

		temp_X += SENSOR->raw_gyro_X;
		temp_Y += SENSOR->raw_gyro_Y;
		temp_Z += SENSOR->raw_gyro_Z;
	}

	temp_X /= totSamples;
	temp_Y /= totSamples;
	temp_Z /= totSamples;

	SENSOR->base_gyro_X = temp_X;
	SENSOR->base_gyro_Y = temp_Y;
	SENSOR->base_gyro_Z = temp_Z;

	SENSOR->scaled_gyro_X = (SENSOR->raw_gyro_X - SENSOR->base_gyro_X)/DLPFFS_FS_SEL;	// FULL_SCALE
	SENSOR->scaled_gyro_Y = (SENSOR->raw_gyro_Y - SENSOR->base_gyro_Y)/DLPFFS_FS_SEL;
	SENSOR->scaled_gyro_Z = (SENSOR->raw_gyro_Z - SENSOR->base_gyro_Z)/DLPFFS_FS_SEL;

}

void Read_Gyro_Temperature(ITG3205* SENSOR)
{
	uint8_t databuf[2];
	uint16_t raw_Temp;

	SENSOR = &GYRO;
	SENSOR->i2c = hi2c1;

	HAL_I2C_Mem_Read(&(SENSOR->i2c), SENSOR->gyro_address,TEMP_OUT,I2C_MEMADD_SIZE_8BIT,databuf,sizeof(databuf),10);
	raw_Temp = ((databuf[0]<<8)|databuf[1]);

	SENSOR->gyro_Temp = ((raw_Temp -13200) / 280.0 -32 ) *5 /9 - 31;
	//SENSOR->gyro_Temp = raw_Temp;
}



void Set_Gyro_ScaledFactor(ITG3205* SENSOR, float _Xcoeff, float _Ycoeff, float _Zcoeff, bool _Radians)
{
	SENSOR->scaleFactor_X = 14.375 * _Xcoeff;
	SENSOR->scaleFactor_Y = 14.375 * _Ycoeff;
	SENSOR->scaleFactor_Z = 14.375 * _Zcoeff;

	if(_Radians)
	{
		SENSOR->scaleFactor_X /= 0.0174532925;
		SENSOR->scaleFactor_Y /= 0.0174532925;
		SENSOR->scaleFactor_Z /= 0.0174532925;
	}

}

void Set_Gyro_Offsets(ITG3205* SENSOR, uint16_t _Xoffset, uint16_t _Yoffset, uint16_t _Zoffset)
{
	SENSOR->offset_X = _Xoffset;
	SENSOR->offset_Y = _Yoffset;
	SENSOR->offset_Z = _Zoffset;
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
	return (received_data[0] & DLPFFS_FS_SEL) >> 3;
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

void Set_Gyro_FilterBW(ITG3205* SENSOR, uint8_t _BW)
{
	uint8_t received_data[1];
	received_data[0] = Gyro_Readbyte(SENSOR, DLPF_FS);
	Gyro_Writebyte(SENSOR, DLPF_FS, (received_data[0] & ~DLPFFS_DLPF_CFG) | _BW);
}

bool is_Gyro_INTActiveOnLow(ITG3205* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Gyro_Readbyte(SENSOR, INT_CFG);
	return ((received_data[0] & INTCFG_ACTL) >> 7);
}

void Set_Gyro_INTDriveType(ITG3205* SENSOR, bool _State)
{
	uint8_t received_data[1];
	received_data[0] = Gyro_Readbyte(SENSOR, INT_CFG);
	Gyro_Writebyte(SENSOR, INT_CFG, ((received_data[0]& ~INTCFG_OPEN)| _State << 6) );
}

bool is_Gyro_LatchUntilCleard(ITG3205* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Gyro_Readbyte(SENSOR, INT_CFG);
	return ((received_data[0] & INTCFG_LATCH_INT_EN)>> 5);
}

void Set_Gyro_LatchMode(ITG3205* SENSOR, bool _State)
{
	uint8_t received_data[1];
	received_data[0] = Gyro_Readbyte(SENSOR, INT_CFG);
	Gyro_Writebyte(SENSOR, INT_CFG, ((received_data[0] & ~INTCFG_LATCH_INT_EN)| _State << 5));
}

bool is_Gyro_AnyRegClrMode(ITG3205* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Gyro_Readbyte(SENSOR, INT_CFG);
	return ((received_data[0] & INTCFG_INT_ANYRD_2CLEAR) >> 4);
}

void Set_Gyro_LatchClearMode(ITG3205* SENSOR, bool _State)
{
	uint8_t received_data[1];
	received_data[0] = Gyro_Readbyte(SENSOR, INT_CFG);
	Gyro_Writebyte(SENSOR, INT_CFG, ((received_data[0] & ~INTCFG_INT_ANYRD_2CLEAR) | _State << 4));
}

bool is_Gyro_RawDataReadyOn(ITG3205* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Gyro_Readbyte(SENSOR, INT_CFG);
	return (received_data[0] & INTCFG_RAW_RDY_EN);
}

void Set_Gyro_RawDataReady(ITG3205* SENSOR, bool _State)
{
	uint8_t received_data[1];
	received_data[0] = Gyro_Readbyte(SENSOR, INT_CFG);
	Gyro_Writebyte(SENSOR, INT_CFG, ((received_data[0] & ~INTCFG_RAW_RDY_EN)| _State));
}

bool is_Gyro_ITGReady(ITG3205* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Gyro_Readbyte(SENSOR, INT_STATUS);
	return ((received_data[0] & INTSTATUS_ITG_RDY) >> 2);
}

bool is_Gyro_RawDataReady(ITG3205* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Gyro_Readbyte(SENSOR, INT_STATUS);
	return (received_data[0] & INTSTATUS_RAW_DATA_RDY);
}




void Reset_Gyro(ITG3205* SENSOR)
{
	Gyro_Writebyte(SENSOR, PWR_MGM, PWRMGM_HRESET);
	HAL_Delay(GYROSTART_UP_DELAY);
}

bool is_Gyro_LowPower(ITG3205* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Gyro_Readbyte(SENSOR, PWR_MGM);
	return ((received_data[0] & PWRMGM_SLEEP) >> 6) ;
}

void Set_Gyro_PowerMode(ITG3205* SENSOR, bool _State)
{
	uint8_t received_data[1];
	received_data[0] = Gyro_Readbyte(SENSOR, PWR_MGM);
	Gyro_Writebyte(SENSOR, PWR_MGM, ((received_data[0]& ~PWRMGM_SLEEP) | _State << 6));
}

bool is_XgyroStandby(ITG3205* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Gyro_Readbyte(SENSOR, PWR_MGM);
	return ((received_data[0] & PWRMGM_STBY_XG) >> 5);
}


bool is_YgyroStandby(ITG3205* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Gyro_Readbyte(SENSOR, PWR_MGM);
	return ((received_data[0] & PWRMGM_STBY_YG) >> 4);
}

bool is_ZgyroStandby(ITG3205* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Gyro_Readbyte(SENSOR, PWR_MGM);
	return ((received_data[0] & PWRMGM_STBY_ZG) >> 3);
}


void Set_XgyroStandby(ITG3205* SENSOR, bool _Status)
{
	uint8_t received_data[1];
	received_data[0] = Gyro_Readbyte(SENSOR, PWR_MGM);
	Gyro_Writebyte(SENSOR, PWR_MGM, ((received_data[0] & PWRMGM_STBY_XG)| _Status << 5));
}

void Set_YgyroStandby(ITG3205* SENSOR, bool _Status)
{
	uint8_t received_data[1];
	received_data[0] = Gyro_Readbyte(SENSOR, PWR_MGM);
	Gyro_Writebyte(SENSOR, PWR_MGM, ((received_data[0] & PWRMGM_STBY_YG)| _Status << 4));
}

void Set_ZgyroStandby(ITG3205* SENSOR, bool _Status)
{
	uint8_t received_data[1];
	received_data[0] = Gyro_Readbyte(SENSOR, PWR_MGM);
	Gyro_Writebyte(SENSOR, PWR_MGM, ((received_data[0] & PWRMGM_STBY_ZG)| _Status << 3));
}


uint16_t Get_ClockSource(ITG3205* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Gyro_Readbyte(SENSOR, PWR_MGM);
	return (received_data[0] & PWRMGM_CLK_SEL);
}

void Set_Gyro_ClockSource(ITG3205* SENSOR, uint8_t _CLKsource)
{
	uint8_t received_data[1];
	received_data[0] = Gyro_Readbyte(SENSOR, PWR_MGM);
	Gyro_Writebyte(SENSOR, PWR_MGM, ((received_data[0] & ~PWRMGM_CLK_SEL)| _CLKsource));
}




















