/*
 * HMC5883L.h
 *
 *  Created on: Apr 29, 2022
 *      Author: s_coo
 */

#ifndef INC_HMC5883L_H_
#define INC_HMC5883L_H_

#include "i2c.h"
#include "stdbool.h"
#include "stdio.h"
#include "math.h"

#define HMC5883L_Address 0x1E
#define ConfigurationRegisterA 0x00
#define ConfigurationRegisterB 0x01
#define ModeRegister 0x02
#define DataRegisterBegin 0x03

#define Measurement_Continuous 0x00
#define Measurement_SingleShot 0x01
#define Measurement_Idle 0x03

#define ErrorCode_1 "Entered scale was not valid, valid gauss values are: 0.88, 1.3, 1.9, 2.5, 4.0, 4.7, 5.6, 8.1"
#define ErrorCode_1_Num 1


typedef struct __HMC5883L{
	I2C_HandleTypeDef i2c;
	uint8_t magneto_address;
	uint8_t magneto_address_read;

	int16_t XAxis;
	int16_t YAxis;
	int16_t ZAxis;

	float scaled_XAxis;
	float scaled_YAxis;
	float scaled_ZAxis;

	float m_Scale;

	float heading;
	float headingDegrees;

	uint8_t status;
	uint8_t error_code;

}HMC5883L, *pHMC5883L;

void Magneto_Writebyte(HMC5883L * SENSOR, uint8_t register_address, uint8_t data);
uint8_t Magneto_Readbyte(HMC5883L * SENSOR, uint8_t register_address);
void Magneto_Init(HMC5883L* SENSOR, float gauss);
void ReadRawAxis(HMC5883L* SENSOR);
void ReadScaledAxis(HMC5883L* SENSOR);
void Read_Magneto(HMC5883L* SENSOR);
uint8_t SetScale(HMC5883L* SENSOR, float gauss);
uint8_t SetMeasurementMode(HMC5883L* SENSOR, uint8_t mode);
char* GetErrorText(uint8_t errorCode);
void Get_Heading_Magneto(HMC5883L* SENSOR);

#endif /* INC_HMC5883L_H_ */
