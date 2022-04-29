/*
 * HMC5883L.h
 *
 *  Created on: Apr 29, 2022
 *      Author: s_coo
 */

#ifndef INC_HMC5883L_H_
#define INC_HMC5883L_H_

#include "i2c.h"

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

	uint16_t XAxis;
	uint16_t YAxis;
	uint16_t ZAxis;

	float scaled_XAxis;
	float scaled_YAxis;
	float scaled_ZAxis;

	float m_Scale;


}HMC5883L, *pHMC5883L;


void Magneto_init(void);
void ReadRawAxix(void);
void ReadScaledAxis(void);
uint8_t SetScale(float gauss);
void SetMeasurementMode(uint8_t mode);
char* GetErrorText(uint8_t errorCode);

#endif /* INC_HMC5883L_H_ */
