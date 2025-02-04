/*
 * bsp.h
 *
 *  Created on: Feb 4, 2025
 *      Author: UA
 */

#ifndef SRC_BSP_BSP_H_
#define SRC_BSP_BSP_H_

#include "def.h"
#include "stm32g4xx_hal.h"

bool bspInit(void);

void delay(uint32_t time_ms);
uint32_t miilis(void);
void Error_Handler(void);

#endif /* SRC_BSP_BSP_H_ */
