/*
 * user_def.h
 *
 *  Created on: Jun 2, 2022
 *      Author: user
 */

#ifndef INC_USER_DEF_H_
#define INC_USER_DEF_H_

#include "stdint.h"

uint32_t DWT_Delay_Init(void);
void DWT_Delay_us(volatile uint32_t microseconds);

#endif /* INC_USER_DEF_H_ */
