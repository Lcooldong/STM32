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

uint8_t Accel_Readbyte(ADXL345 * SENSOR, uint8_t register_address)
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


void Accel_Init(ADXL345* SENSOR)
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
	//SENSOR->i2c = hi2c1;

	HAL_I2C_Mem_Read(&(SENSOR->i2c), SENSOR->accel_address , ADXL345_DATAX0, I2C_MEMADD_SIZE_8BIT, accel_buf, sizeof(accel_buf), 10);
	SENSOR->raw_accel_X = (int16_t)((accel_buf[1]) << 8) | accel_buf[0];
	SENSOR->raw_accel_Y = (int16_t)((accel_buf[3]) << 8) | accel_buf[2];
	SENSOR->raw_accel_Z = (int16_t)((accel_buf[5]) << 8) | accel_buf[4];

	SENSOR->scaled_accel_X = SENSOR->raw_accel_X * SENSOR->gain_X;
	SENSOR->scaled_accel_Y = SENSOR->raw_accel_Y * SENSOR->gain_Y;
	SENSOR->scaled_accel_Z = SENSOR->raw_accel_Z * SENSOR->gain_Z;


}

uint8_t Get_ACCEL_RangeSetting(ADXL345* SENSOR, uint8_t rangeSetting)
{
	uint8_t received_data[1];
	received_data[0] = Accel_Readbyte(SENSOR, ADXL345_DATA_FORMAT);
	return received_data[0] & 0x03;
}

void Set_ACCEL_RangeSetting(ADXL345* SENSOR, uint8_t val)
{
	uint8_t TEMP_DATA_FORMAT;
	uint8_t received_data[1];
	received_data[0] = Accel_Readbyte(SENSOR, ADXL345_DATA_FORMAT);

	switch (val){
		case 2:
			TEMP_DATA_FORMAT = ADXL345_DATA_FORMAT_2g;
			break;
		case 4:
			TEMP_DATA_FORMAT = ADXL345_DATA_FORMAT_4g;
			break;
		case 8:
			TEMP_DATA_FORMAT = ADXL345_DATA_FORMAT_8g;
			break;
		case 16:
			TEMP_DATA_FORMAT = ADXL345_DATA_FORMAT_16g;
			break;
	}

	TEMP_DATA_FORMAT = received_data[0] & 0b11101100; //0xEC
	Accel_Writebyte(SENSOR, ADXL345_DATA_FORMAT, TEMP_DATA_FORMAT);
}

bool Get_ACCEL_SelfTestBit(ADXL345* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Accel_Readbyte(SENSOR, ADXL345_DATA_FORMAT);
	//return Get_ACCEL_RegisterBit(SENSOR, ADXL345_DATA_FORMAT, 7);
	return (received_data[0] & DATA_FORMAT_SELF_TEST);
}

void Set_ACCEL_SelfTestBit(ADXL345* SENSOR, bool selfTestBit)
{
	uint8_t received_data[1];
	received_data[0] = Accel_Readbyte(SENSOR, ADXL345_DATA_FORMAT);
	//Set_ACCEL_RegisterBit(SENSOR, ADXL345_DATA_FORMAT, 7, selfTestBit);
	Accel_Writebyte(SENSOR, ADXL345_DATA_FORMAT, (received_data[0] & ~DATA_FORMAT_SELF_TEST ) | selfTestBit << 7);
}

bool Get_ACCEL_SpitBit(ADXL345* SENSOR)
{
	//uint8_t received_data[1];
	//received_data[0] = Accel_Readbyte(SENSOR, ADXL345_DATA_FORMAT);
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_DATA_FORMAT, 6);
	//return (received_data[0] & DATA_FORMAT_SELF_TEST);
}

void Set_ACCEL_SpiBit(ADXL345* SENSOR, bool spiBit)
{
	//uint8_t received_data[1];
	//received_data[0] = Accel_Readbyte(SENSOR, ADXL345_DATA_FORMAT);
	Set_ACCEL_RegisterBit(SENSOR, ADXL345_DATA_FORMAT, 6, spiBit);
	//Accel_Writebyte(SENSOR, ADXL345_DATA_FORMAT, (received_data[0] & ~DATA_FORMAT_SELF_TEST ) | selfTestBit << 6);
}

bool Get_ACCEL_InterruptLeveltBit(ADXL345* SENSOR)
{
	//uint8_t received_data[1];
	//received_data[0] = Accel_Readbyte(SENSOR, ADXL345_DATA_FORMAT);
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_DATA_FORMAT, 5);
	//return (received_data[0] & DATA_FORMAT_SELF_TEST);
}

void Set_ACCEL_InterruptLeveltBit(ADXL345* SENSOR, bool interruptLevelBit)
{
	//uint8_t received_data[1];
	//received_data[0] = Accel_Readbyte(SENSOR, ADXL345_DATA_FORMAT);
	Set_ACCEL_RegisterBit(SENSOR, ADXL345_DATA_FORMAT, 5, interruptLevelBit);
	//Accel_Writebyte(SENSOR, ADXL345_DATA_FORMAT, (received_data[0] & ~DATA_FORMAT_SELF_TEST ) | selfTestBit << 5);
}

bool Get_ACCEL_FullResBit(ADXL345* SENSOR)
{
	//uint8_t received_data[1];
	//received_data[0] = Accel_Readbyte(SENSOR, ADXL345_DATA_FORMAT);
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_DATA_FORMAT, 3);
	//return (received_data[0] & DATA_FORMAT_SELF_TEST);
}

void Set_ACCEL_FullResBit(ADXL345* SENSOR, bool fullResBit)
{
	//uint8_t received_data[1];
	//received_data[0] = Accel_Readbyte(SENSOR, ADXL345_DATA_FORMAT);
	Set_ACCEL_RegisterBit(SENSOR, ADXL345_DATA_FORMAT, 3, fullResBit);
	//Accel_Writebyte(SENSOR, ADXL345_DATA_FORMAT, (received_data[0] & ~DATA_FORMAT_SELF_TEST ) | selfTestBit << 3);
}

bool Get_ACCEL_JustifyBit(ADXL345* SENSOR)
{
	//uint8_t received_data[1];
	//received_data[0] = Accel_Readbyte(SENSOR, ADXL345_DATA_FORMAT);
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_DATA_FORMAT, 2);
	//return (received_data[0] & DATA_FORMAT_SELF_TEST);
}

void Set_ACCEL_JustifyBit(ADXL345* SENSOR, bool justifyBit)
{
	//uint8_t received_data[1];
	//received_data[0] = Accel_Readbyte(SENSOR, ADXL345_DATA_FORMAT);
	Set_ACCEL_RegisterBit(SENSOR, ADXL345_DATA_FORMAT, 2, justifyBit);
	//Accel_Writebyte(SENSOR, ADXL345_DATA_FORMAT, (received_data[0] & ~DATA_FORMAT_SELF_TEST ) | selfTestBit << 2);
}

uint8_t Get_ACCEL_TapThreadhold(ADXL345* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Accel_Readbyte(SENSOR, ADXL345_THRESH_TAP);
	return received_data[0];
}

void Set_ACCEL_TapThreadhold(ADXL345* SENSOR, uint8_t tapThreadhold)
{
	Accel_Writebyte(SENSOR, ADXL345_THRESH_TAP, tapThreadhold);
}

double* Get_ACCEL_AxisGain(ADXL345* SENSOR, double array[3])
{
	array[0] = SENSOR->gain_X;
	array[1] = SENSOR->gain_Y;
	array[2] = SENSOR->gain_Z;

	return array;
}

void Set_ACCEL_AxisGain(ADXL345* SENSOR, double array[3])
{
	SENSOR->gain_X = array[0];
	SENSOR->gain_Y = array[1];
	SENSOR->gain_Z = array[2];
}


int8_t* Get_ACCEL_AxisOffset(ADXL345* SENSOR, int8_t received_data[3])
{
	received_data[0] = Accel_Readbyte(SENSOR, ADXL345_OFSX);
	received_data[1] = Accel_Readbyte(SENSOR, ADXL345_OFSY);
	received_data[2] = Accel_Readbyte(SENSOR, ADXL345_OFSZ);

	SENSOR->offset_X = received_data[0];
	SENSOR->offset_Y = received_data[1];
	SENSOR->offset_Z = received_data[2];

	return received_data;
}

void Set_ACCEL_AxisOffset(ADXL345* SENSOR, int8_t _Xoffset, int8_t _Yoffset, int8_t _Zoffset)
{
	SENSOR->offset_X = _Xoffset;
	SENSOR->offset_Y = _Yoffset;
	SENSOR->offset_Z = _Zoffset;

	Accel_Writebyte(SENSOR, ADXL345_OFSX, SENSOR->offset_X);
	Accel_Writebyte(SENSOR, ADXL345_OFSY, SENSOR->offset_Y);
	Accel_Writebyte(SENSOR, ADXL345_OFSZ, SENSOR->offset_Z);
}


uint8_t Get_ACCEL_TapDuration(ADXL345* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = (int8_t)Accel_Readbyte(SENSOR, ADXL345_DUR);
	return received_data[0];
}

void Set_ACCEL_TapDuration(ADXL345* SENSOR, uint8_t tapDuration)
{
	Accel_Writebyte(SENSOR, ADXL345_DUR, tapDuration);
}


uint8_t Get_ACCEL_DoubleTapLatency(ADXL345* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Accel_Readbyte(SENSOR, ADXL345_LATENT);
	return received_data[0];
}



void Set_ACCEL_DoubleTapLatency(ADXL345* SENSOR, uint8_t doubleTapLatency)
{
	Accel_Writebyte(SENSOR, ADXL345_LATENT, doubleTapLatency);
}

uint8_t Get_ACCEL_DoubleTapWindow(ADXL345* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Accel_Readbyte(SENSOR, ADXL345_WINDOW);
	return received_data[0];
}

void Set_ACCEL_DoubleTapWindow(ADXL345* SENSOR, uint8_t doubleTapWindow)
{
	Accel_Writebyte(SENSOR, ADXL345_WINDOW, doubleTapWindow);
}


uint8_t Get_ACCEL_ActivityThreshold(ADXL345* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Accel_Readbyte(SENSOR, ADXL345_THRESH_ACT);
	return received_data[0];
}

void Set_ACCEL_ActivityThreshold(ADXL345* SENSOR, uint8_t activityThreshold)
{
	Accel_Writebyte(SENSOR, ADXL345_THRESH_ACT, activityThreshold);
}


uint8_t Get_ACCEL_InactivityThreshold(ADXL345* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Accel_Readbyte(SENSOR, ADXL345_THRESH_INACT);
	return received_data[0];
}

void Set_ACCEL_InactivityThreshold(ADXL345* SENSOR, uint8_t inactivityThreshold)
{
	Accel_Writebyte(SENSOR, ADXL345_THRESH_INACT, inactivityThreshold);
}


uint8_t Get_ACCEL_TimeInactivity(ADXL345* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Accel_Readbyte(SENSOR, ADXL345_TIME_INACT);
	return received_data[0];
}

void Set_ACCEL_TimeInactivity(ADXL345* SENSOR, uint8_t timeInactivity)
{
	Accel_Writebyte(SENSOR, ADXL345_TIME_INACT, timeInactivity);
}

uint8_t Get_ACCEL_FreeFallThreshold(ADXL345* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Accel_Readbyte(SENSOR, ADXL345_THRESH_FF);
	return received_data[0];
}

void Set_ACCEL_FreeFallThreshold(ADXL345* SENSOR, uint8_t freeFallThreshold)
{
	Accel_Writebyte(SENSOR, ADXL345_THRESH_FF, freeFallThreshold);
}

uint8_t Get_ACCEL_FreeFallDuration(ADXL345* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Accel_Readbyte(SENSOR, ADXL345_TIME_FF);
	return received_data[0];
}

void Set_ACCEL_FreeFallDuration(ADXL345* SENSOR, uint8_t freeFallDuration)
{
	Accel_Writebyte(SENSOR, ADXL345_TIME_FF, freeFallDuration);
}



bool is_ACCEL_ActivityXEnabled(ADXL345* SENSOR)
{
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_ACT_INACT_CTL, 6);
}

bool is_ACCEL_ActivityYEnabled(ADXL345* SENSOR)
{
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_ACT_INACT_CTL, 5);
}

bool is_ACCEL_ActivityZEnabled(ADXL345* SENSOR)
{
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_ACT_INACT_CTL, 4);
}

bool is_ACCEL_InactivityXEnabled(ADXL345* SENSOR)
{
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_ACT_INACT_CTL, 2);
}

bool is_ACCEL_InactivityYEnabled(ADXL345* SENSOR)
{
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_ACT_INACT_CTL, 1);
}

bool is_ACCEL_InactivityZEnabled(ADXL345* SENSOR)
{
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_ACT_INACT_CTL, 0);
}



void Set_ACCEL_ActivityX(ADXL345* SENSOR, bool _State)
{
	Set_ACCEL_RegisterBit(SENSOR, ADXL345_ACT_INACT_CTL, 6, _State);
}

void Set_ACCEL_ActivityY(ADXL345* SENSOR, bool _State)
{
	Set_ACCEL_RegisterBit(SENSOR, ADXL345_ACT_INACT_CTL, 5, _State);
}

void Set_ACCEL_ActivityZ(ADXL345* SENSOR, bool _State)
{
	Set_ACCEL_RegisterBit(SENSOR, ADXL345_ACT_INACT_CTL, 4, _State);

}
void Set_ACCEL_InactivityX(ADXL345* SENSOR, bool _State)
{
	Set_ACCEL_RegisterBit(SENSOR, ADXL345_ACT_INACT_CTL, 2, _State);

}
void Set_ACCEL_InactivityY(ADXL345* SENSOR, bool _State)
{
	Set_ACCEL_RegisterBit(SENSOR, ADXL345_ACT_INACT_CTL, 1, _State);

}
void Set_ACCEL_InactivityZ(ADXL345* SENSOR, bool _State)
{
	Set_ACCEL_RegisterBit(SENSOR, ADXL345_ACT_INACT_CTL, 0, _State);
}



bool is_ACCEL_ActivityAc(ADXL345* SENSOR)
{
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_ACT_INACT_CTL, 7);
}

bool is_ACCEL_InactivityAc(ADXL345* SENSOR)
{
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_ACT_INACT_CTL, 3);
}


void Set_ACCEL_ActivityAc(ADXL345* SENSOR, bool _State)
{
	Set_ACCEL_RegisterBit(SENSOR, ADXL345_ACT_INACT_CTL, 7, _State);
}

void Set_ACCEL_InactivityAc(ADXL345* SENSOR, bool _State)
{
	Set_ACCEL_RegisterBit(SENSOR, ADXL345_ACT_INACT_CTL, 3, _State);
}


bool Get_ACCEL_SuppressBit(ADXL345* SENSOR)
{
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_TAP_AXES, 3);
}

void Set_ACCEL_SuppressBit(ADXL345* SENSOR, bool _State)
{
	Set_ACCEL_RegisterBit(SENSOR, ADXL345_TAP_AXES, 3, _State);
}

bool is_ACCEL_TapDetectionOnX(ADXL345* SENSOR)
{
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_TAP_AXES, 2);
}

void Set_ACCEL_TapDetectionOnX(ADXL345* SENSOR, bool _State)
{
	Set_ACCEL_RegisterBit(SENSOR, ADXL345_TAP_AXES, 2, _State);
}

bool is_ACCEL_TapDetectionOnY(ADXL345* SENSOR)
{
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_TAP_AXES, 1);
}

void Set_ACCEL_TapDetectionOnY(ADXL345* SENSOR, bool _State)
{
	Set_ACCEL_RegisterBit(SENSOR, ADXL345_TAP_AXES, 1, _State);
}

bool is_ACCEL_TapDetectionOnZ(ADXL345* SENSOR)
{
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_TAP_AXES, 0);
}

void Set_ACCEL_TapDetectionOnZ(ADXL345* SENSOR, bool _State)
{
	Set_ACCEL_RegisterBit(SENSOR, ADXL345_TAP_AXES, 0, _State);
}

bool is_ACCEL_ActivitySourceOnX(ADXL345* SENSOR)
{
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_ACT_TAP_STATUS, 6);
}

bool is_ACCEL_ActivitySourceOnY(ADXL345* SENSOR)
{
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_ACT_TAP_STATUS, 5);
}

bool is_ACCEL_ActivitySourceOnZ(ADXL345* SENSOR)
{
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_ACT_TAP_STATUS, 4);
}

bool is_ACCEL_TapSourceOnX(ADXL345* SENSOR)
{
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_ACT_TAP_STATUS, 2);
}

bool is_ACCEL_TapSourceOnY(ADXL345* SENSOR)
{
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_ACT_TAP_STATUS, 1);
}

bool is_ACCEL_TapSourceOnZ(ADXL345* SENSOR)
{
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_ACT_TAP_STATUS, 0);
}

bool is_ACCEL_Asleep(ADXL345* SENSOR)
{
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_ACT_TAP_STATUS, 3);
}

bool is_ACCEL_LowPower(ADXL345* SENSOR)
{
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_BW_RATE, 4);
}

void Set_ACCEL_LowPower(ADXL345* SENSOR, bool _State)
{
	Set_ACCEL_RegisterBit(SENSOR, ADXL345_BW_RATE, 4, _State);
}


double Get_ACCEL_Rate(ADXL345* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Accel_Readbyte(SENSOR, ADXL345_BW_RATE);
	received_data[0] &= 0x0F;

	return  (pow(2, received_data[0] - 6))*6.25;
}



void Set_ACCEL_Rate(ADXL345* SENSOR, double rate)
{
	uint8_t result_rate;

	uint8_t val = (uint8_t)(rate/6.25);
	uint8_t cnt = 0;
	while(val >>= 1)
	{
		cnt++;
	}
	if(cnt <= 9)
	{
		uint8_t received_data[1];
		received_data[0] = Accel_Readbyte(SENSOR, ADXL345_BW_RATE);
		result_rate = (uint8_t)((cnt + 6) | (received_data[0] & 0xF0));
		Accel_Writebyte(SENSOR, ADXL345_BW_RATE, result_rate);
	}
}

uint8_t Get_ACCEL_bw_code(ADXL345* SENSOR)
{
	uint8_t bw_code[1];
	bw_code[0] = Accel_Readbyte(SENSOR, ADXL345_BW_RATE);
	return bw_code[0];
}

void Set_ACCEL_bw_code(ADXL345* SENSOR, uint8_t bw_code)
{
	if((bw_code < ADXL345_BW_3) || (bw_code > ADXL345_BW_1600))
	{
		SENSOR->status = false;
		SENSOR->error_code = ADXL345_BAD_ARG;
	}
	else
	{
		Accel_Writebyte(SENSOR, ADXL345_BW_RATE, bw_code);
	}
}



bool ACCEL_triggered(uint8_t interrupts, uint8_t mask)
{
	return (interrupts >> mask) & 1;
}

uint8_t Get_ACCEL_InterruptSource(ADXL345* SENSOR)
{
	uint8_t received_data[1];
	received_data[0] = Accel_Readbyte(SENSOR, ADXL345_INT_SOURCE);
	return received_data[0];
}

bool Get_ACCEL_InterruptMapping(ADXL345* SENSOR, uint8_t interruptBit)
{
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_INT_MAP, interruptBit);
}

void Set_ACCEL_InterruptMapping(ADXL345* SENSOR, uint8_t interruptBit, bool interruptPin)
{
	Set_ACCEL_RegisterBit(SENSOR, ADXL345_INT_MAP, interruptBit, interruptPin);
}

bool is_ACCEL_InterruptEnabled(ADXL345* SENSOR, uint8_t interruptBit)
{
	return Get_ACCEL_RegisterBit(SENSOR, ADXL345_INT_ENABLE, interruptBit);
}

void Set_ACCEL_Interrupt(ADXL345* SENSOR, uint8_t interruptBit, bool _State)
{
	Set_ACCEL_RegisterBit(SENSOR, ADXL345_INT_ENABLE, interruptBit, _State);
}


bool Get_ACCEL_RegisterBit(ADXL345* SENSOR, uint8_t register_address, uint8_t bitPos)
{
	uint8_t received_data[1];
	received_data[0] = Accel_Readbyte(SENSOR, register_address);
	return ((received_data[0] >> bitPos) & 1);
}

void Set_ACCEL_RegisterBit(ADXL345* SENSOR, uint8_t register_address, uint8_t bitPos, bool _State)
{
	uint8_t received_data[1];
	received_data[0] = Accel_Readbyte(SENSOR, register_address);
	if(_State)
	{
		received_data[0] |= (1 << bitPos);
	}
	else
	{
		received_data[0] = ~(1 << bitPos);
	}
	Accel_Writebyte(SENSOR, register_address, received_data[0]);
}

void printAllRegister(ADXL345* SENSOR) {
	uint8_t received_data[1];
	printf("0x00: ");
	received_data[0] = Accel_Readbyte(SENSOR, 0x00);
	printf("0x%X\r\n", received_data[0]);
	int i;
	for (i=29;i<=57;i++){
		printf("0x%X : ", i);
		received_data[0] = Accel_Readbyte(SENSOR, i);
		printf("0x%X\r\n", received_data[0]);
	}
}

void print_byte(uint8_t val){
	int i;
	printf("Binary : ");
	for(i=7; i>=0; i--){
		printf("%d",val >> i & 1);
	}
	printf("\r\n");
}



















