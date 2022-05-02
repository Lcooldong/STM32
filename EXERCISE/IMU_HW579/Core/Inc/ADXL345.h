/*
 * ADXL345.h
 *
 *  Created on: Apr 29, 2022
 *      Author: s_coo
 */

#ifndef INC_ADXL345_H_
#define INC_ADXL345_H_

#include "i2c.h"
#include "stdbool.h"
#include "stdio.h"
#include "math.h"

/* ------- Register names ------- */
#define ADXL345_DEVID 0x00
#define ADXL345_RESERVED1 0x01
#define ADXL345_THRESH_TAP 0x1d
#define ADXL345_OFSX 0x1e
#define ADXL345_OFSY 0x1f
#define ADXL345_OFSZ 0x20
#define ADXL345_DUR 0x21
#define ADXL345_LATENT 0x22
#define ADXL345_WINDOW 0x23
#define ADXL345_THRESH_ACT 0x24
#define ADXL345_THRESH_INACT 0x25
#define ADXL345_TIME_INACT 0x26
#define ADXL345_ACT_INACT_CTL 0x27
#define ADXL345_THRESH_FF 0x28
#define ADXL345_TIME_FF 0x29
#define ADXL345_TAP_AXES 0x2a
#define ADXL345_ACT_TAP_STATUS 0x2b
#define ADXL345_BW_RATE 0x2c
#define ADXL345_POWER_CTL 0x2d
#define ADXL345_INT_ENABLE 0x2e
#define ADXL345_INT_MAP 0x2f
#define ADXL345_INT_SOURCE 0x30
#define ADXL345_DATA_FORMAT 0x31
#define ADXL345_DATAX0 0x32
#define ADXL345_DATAX1 0x33
#define ADXL345_DATAY0 0x34
#define ADXL345_DATAY1 0x35
#define ADXL345_DATAZ0 0x36
#define ADXL345_DATAZ1 0x37
#define ADXL345_FIFO_CTL 0x38
#define ADXL345_FIFO_STATUS 0x39


/* Data Rata Bandwidth (bw_code) */
#define ADXL345_BW_1600 0xF // 1111
#define ADXL345_BW_800  0xE // 1110
#define ADXL345_BW_400  0xD // 1101
#define ADXL345_BW_200  0xC // 1100
#define ADXL345_BW_100  0xB // 1011
#define ADXL345_BW_50   0xA // 1010
#define ADXL345_BW_25   0x9 // 1001
#define ADXL345_BW_12   0x8 // 1000
#define ADXL345_BW_6    0x7 // 0111
#define ADXL345_BW_3    0x6 // 0110



#define DATA_FORMAT_SELF_TEST 	0x80
#define DATA_FORMAT_SPI		  	0x40
#define DATA_FORMAT_INT_INVERT	0x20
#define DATA_FORMAT_FULL_RES	0x08
#define DATA_FORMAT_Justify		0x04
#define ADXL345_DATA_FORMAT_16g	0x03
#define ADXL345_DATA_FORMAT_8g	0x02
#define ADXL345_DATA_FORMAT_4g	0x01
#define ADXL345_DATA_FORMAT_2g 	0x00




/*
 Interrupt PINs
 INT1: 0
 INT2: 1
 */
#define ADXL345_INT1_PIN 0x00
#define ADXL345_INT2_PIN 0x01

/*
 Interrupt bit position
 */
#define ADXL345_INT_DATA_READY_BIT 0x07
#define ADXL345_INT_SINGLE_TAP_BIT 0x06
#define ADXL345_INT_DOUBLE_TAP_BIT 0x05
#define ADXL345_INT_ACTIVITY_BIT   0x04
#define ADXL345_INT_INACTIVITY_BIT 0x03
#define ADXL345_INT_FREE_FALL_BIT  0x02
#define ADXL345_INT_WATERMARK_BIT  0x01
#define ADXL345_INT_OVERRUNY_BIT   0x00

#define ADXL345_DATA_READY 0x07
#define ADXL345_SINGLE_TAP 0x06
#define ADXL345_DOUBLE_TAP 0x05
#define ADXL345_ACTIVITY   0x04
#define ADXL345_INACTIVITY 0x03
#define ADXL345_FREE_FALL  0x02
#define ADXL345_WATERMARK  0x01
#define ADXL345_OVERRUNY   0x00




#define ADXL345_OK    1 // no error
#define ADXL345_ERROR 0 // indicates error is predent

#define ADXL345_NO_ERROR   0 // initial state
#define ADXL345_READ_ERROR 1 // problem reading accel
#define ADXL345_BAD_ARG    2 // bad method argument

typedef struct __ADXL345{
	I2C_HandleTypeDef i2c;
	uint8_t accel_address;
	uint8_t accel_address_read;

	int8_t offset_X;
	int8_t offset_Y;
	int8_t offset_Z;

	double gain_X;
	double gain_Y;
	double gain_Z;

	int16_t raw_accel_X;
	int16_t raw_accel_Y;
	int16_t raw_accel_Z;

	float scaled_accel_X;
	float scaled_accel_Y;
	float scaled_accel_Z;

	bool status;
	uint8_t error_code;

}ADXL345, *pADXL345;

void Accel_Writebyte(ADXL345 * SENSOR, uint8_t register_address, uint8_t data);
uint8_t Accel_Readbyte(ADXL345 * SENSOR,uint8_t register_address);
void Accel_Init(ADXL345* SENSOR);
void Read_Accel(ADXL345* SENSOR);
void Get_Accel(ADXL345* SENSOR);


bool Get_ACCEL_RegisterBit(ADXL345* SENSOR, uint8_t register_address, uint8_t bitPos);
void Set_ACCEL_RegisterBit(ADXL345* SENSOR, uint8_t register_address, uint8_t bitPos, bool _State);

#endif /* INC_ADXL345_H_ */
