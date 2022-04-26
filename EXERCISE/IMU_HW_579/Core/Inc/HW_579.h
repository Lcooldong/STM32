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

typedef struct __HW579{
	I2C_HandleTypeDef i2c;

	HMC5883L MAGNETO;
	ITG3205 GYRO;
	ADXL345 ACCEL;

	uint8_t magneto_address;
	uint8_t accel_address;
	uint8_t gyro_address;
}HW579;

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
void I2C_Writebyte(HW579 * I2C, uint8_t register_address, uint8_t data, uint8_t TYPE);
uint8_t I2C_Readbyte(HW579 * I2C, uint8_t register_address, uint8_t TYPE);

#endif /* INC_HW_579_H_ */
