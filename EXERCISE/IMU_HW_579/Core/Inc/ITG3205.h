/*
 * ITG3205.h
 *
 *  Created on: Apr 22, 2022
 *      Author: user
 */

#ifndef INC_ITG3205_H_
#define INC_ITG3205_H_

#define ITG3205_ADDR_AD0_HIGH	0x69
#define ITG3205_ADDR_AD0_LOW 	0x68

#define GYROSTART_UP_DELAY		70



/*------------Registers------------*/
#define WHO_AM_I				0x00
#define	SMPLRT_DIV				0x15
#define DLPF_FS					0x16
#define INT_CFG					0x17
#define	INT_STATUS				0x1A
#define TEMP_OUT_H				0x1B
#define TEMP_OUT_L				0x1C
#define GYRO_XOUT_H				0x1D
#define GYRO_XOUT_L				0x1E
#define GYRO_YOUT_H				0x1F
#define GYRO_YOUT_L				0x20
#define GYRO_ZOUT_H				0x21
#define GYRO_ZOUT_L				0x22
#define PWR_MGM					0x3E


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





#endif /* INC_ITG3205_H_ */
