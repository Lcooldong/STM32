/*
 * ITG3205.h
 *
 *  Created on: Apr 22, 2022
 *      Author: user
 */

#ifndef INC_ITG3205_H_
#define INC_ITG3205_H_


#include "HW_579.h"



#define ITG3205_ADDR_AD0_HIGH	0x69
#define ITG3205_ADDR_AD0_LOW 	0x68

#define ITG3205_MPU_ADDRESS (ITG3205_ADDR_AD0_LOW << 1)
#define ITG3205_MPU_ADDRESS_Rd (ITG3205_ADDR_AD0_LOW << 1) | 0x01



#define GYROSTART_UP_DELAY  70    // 50ms from gyro startup + 20ms register r/w startup

/* ---- Registers ---- */
#define WHO_AM_I           0x00  // RW   SETUP: I2C address
#define SMPLRT_DIV         0x15  // RW   SETUP: Sample Rate Divider
#define DLPF_FS            0x16  // RW   SETUP: Digital Low Pass Filter/ Full Scale range
#define INT_CFG            0x17  // RW   Interrupt: Configuration
#define INT_STATUS         0x1A  // R	Interrupt: Status
#define TEMP_OUT           0x1B  // R	SENSOR: Temperature 2bytes
#define GYRO_XOUT          0x1D  // R	SENSOR: Gyro X 2bytes
#define GYRO_YOUT          0x1F  // R	SENSOR: Gyro Y 2bytes
#define GYRO_ZOUT          0x21  // R	SENSOR: Gyro Z 2bytes
#define PWR_MGM            0x3E  // RW	Power Management

/* ---- bit maps ---- */
#define DLPFFS_FS_SEL             0x18  // 00011000
#define DLPFFS_DLPF_CFG           0x07  // 00000111
#define INTCFG_ACTL               0x80  // 10000000
#define INTCFG_OPEN               0x40  // 01000000
#define INTCFG_LATCH_INT_EN       0x20  // 00100000
#define INTCFG_INT_ANYRD_2CLEAR   0x10  // 00010000
#define INTCFG_ITG_RDY_EN         0x04  // 00000100
#define INTCFG_RAW_RDY_EN         0x01  // 00000001
#define INTSTATUS_ITG_RDY         0x04  // 00000100
#define INTSTATUS_RAW_DATA_RDY    0x01  // 00000001
#define PWRMGM_HRESET             0x80  // 10000000
#define PWRMGM_SLEEP              0x40  // 01000000
#define PWRMGM_STBY_XG            0x20  // 00100000
#define PWRMGM_STBY_YG            0x10  // 00010000
#define PWRMGM_STBY_ZG            0x08  // 00001000
#define PWRMGM_CLK_SEL            0x07  // 00000111

/************************************/
/*    REGISTERS PARAMETERS    */
/************************************/
// Sample Rate Divider
#define NOSRDIVIDER         0 // default    FsampleHz=SampleRateHz/(divider+1)
// Gyro Full Scale Range
#define RANGE2000           3   // default
// Digital Low Pass Filter BandWidth and SampleRate
#define BW256_SR8           0   // default    256Khz BW and 8Khz SR
#define BW188_SR1           1
#define BW098_SR1           2
#define BW042_SR1           3
#define BW020_SR1           4
#define BW010_SR1           5
#define BW005_SR1           6
// Interrupt Active logic lvl
#define ACTIVE_ONHIGH       0 // default
#define ACTIVE_ONLOW        1
// Interrupt drive type
#define PUSH_PULL           0 // default
#define OPEN_DRAIN          1
// Interrupt Latch mode
#define PULSE_50US          0 // default
#define UNTIL_INT_CLEARED   1
// Interrupt Latch clear method
#define READ_STATUSREG      0 // default
#define READ_ANYREG         1
// Power management
#define NORMAL              0 // default
#define STANDBY             1
// Clock Source - user parameters
#define INTERNALOSC         0   // default
#define PLL_XGYRO_REF       1
#define PLL_YGYRO_REF       2
#define PLL_ZGYRO_REF       3
#define PLL_EXTERNAL32      4   // 32.768 kHz
#define PLL_EXTERNAL19      5   // 19.2 Mhz



typedef struct __ITG3205{
	I2C_HandleTypeDef i2c;
	uint8_t gyro_address;
	uint8_t gyro_address_read;

	uint16_t offset_X;
	uint16_t offset_Y;
	uint16_t offset_Z;

	float scalefactor_X;
	float scalefactor_Y;
	float scalefactor_Z;

	uint16_t gyro_temp;
	uint16_t gyro_X;
	uint16_t gyro_Y;
	uint16_t gyro_Z;


	float scaled_gyro_temp;
	float scaled_gyro_X;
	float scaled_gyro_Y;
	float scaled_gyro_Z;
}ITG3205, *pITG3205;



void Gyro_Writebyte(uint8_t register_address, uint8_t data);
void Gyro_init(ITG3205* SENSOR);
void Gyro_Read(I2C_HandleTypeDef *i2c);

bool isRawDataReady(void);
void readGyroRaw(void);
void setScaleFactor(float _Xcoeff, float _Ycoeff, float _Zcoeff, bool _Radians);
void setOffsets(uint16_t _Xoffset, uint16_t _Yoffset, uint16_t _Zoffset);
void zeroCalibrate(uint16_t totSamples, uint16_t sampleDelayMS);

#endif /* INC_ITG3205_H_ */
