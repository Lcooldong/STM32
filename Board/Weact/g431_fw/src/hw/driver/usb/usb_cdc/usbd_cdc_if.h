/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_cdc_if.h
  * @version        : v3.0_Cube
  * @brief          : Header for usbd_cdc_if.c file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_CDC_IF_H__
#define __USBD_CDC_IF_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc.h"


#define APP_RX_DATA_SIZE  1000
#define APP_TX_DATA_SIZE  1000

extern USBD_CDC_ItfTypeDef USBD_Interface_fops_FS;

uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len);


bool     cdcIfInit(void);
uint32_t cdcIfAvailable(void);
uint8_t  cdcIfRead(void);
uint32_t cdcIfGetBaud(void);
uint32_t cdcIfWrite(uint8_t *p_data, uint32_t length);
bool     cdcIfIsConnected(void);


#ifdef __cplusplus
}
#endif

#endif /* __USBD_CDC_IF_H__ */

