/*
 * HW_579.h
 *
 *  Created on: 2022. 4. 25.
 *      Author: s_coo
 */

#ifndef INC_HW_579_H_
#define INC_HW_579_H_

#include "stdio.h"
#include "stdbool.h"
#include "i2c.h"
#include "ITG3205.h"
#include "ADXL345.h"
#include "HMC5883L.h"



typedef struct __HW579{
	I2C_HandleTypeDef i2c;

	struct __HMC5883L *MAGNETO;
	struct __ADXL345 *ACCEL;
	struct __ITG3205 *GYRO;


	uint8_t magneto_address;
	uint8_t accel_address;
	uint8_t gyro_address;
}HW579, *pHW579;

typedef enum
{
	magneto = 0,
	accel,
	gyro
}SENSOR_ENUM;




//HW579 hw579 = {0, };

uint8_t* getI2C_Address(I2C_HandleTypeDef *hi2c);
void HW579_init(I2C_HandleTypeDef *hi2c);
void HW579_Read(void);
void I2C_Writebyte(void * SENSOR, uint8_t register_address, uint8_t data, uint8_t TYPE);
uint8_t I2C_Readbyte(void * SENSOR, uint8_t register_address, uint8_t TYPE);

#endif /* INC_HW_579_H_ */
