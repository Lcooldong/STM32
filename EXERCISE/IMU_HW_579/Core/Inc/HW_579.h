/*
 * HW_579.h
 *
 *  Created on: 2022. 4. 25.
 *      Author: s_coo
 */

#ifndef INC_HW_579_H_
#define INC_HW_579_H_


typedef struct __HW579{
	I2C_HandleTypeDef i2c;
	uint8_t magneto_address;
	uint8_t accel_address;
	uint8_t gyro_address;
}HW579;

//HW579 hw579 = {0, };

uint8_t* getI2C_Address(I2C_HandleTypeDef *hi2c);
void HW579_init(HW579 *I2C);
void HW579_Read(void);

#endif /* INC_HW_579_H_ */
