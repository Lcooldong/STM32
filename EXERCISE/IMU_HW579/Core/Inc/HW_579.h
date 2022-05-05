/*
 * HW_579.h
 *
 *  Created on: Apr 29, 2022
 *      Author: s_coo
 */

#ifndef INC_HW_579_H_
#define INC_HW_579_H_

#include "HMC5883L.h"
#include "ADXL345.h"
#include "ITG3205.h"

typedef struct __HW579{
	I2C_HandleTypeDef i2c;

	struct __HMC5883L *MAGNETO_HW579;
	struct __ADXL345 *ACCEL_HW579;
	struct __ITG3205 *GYRO_HW579;

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

uint8_t* getI2C_Address(I2C_HandleTypeDef * hi2c, HW579 * SENSOR);
void HW579_Init(HW579* SENSOR, float _MagnetoGauss);


#endif /* INC_HW_579_H_ */
