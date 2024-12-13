/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gfxtim.c
  * @brief   This file provides code for the configuration
  *          of the GFXTIM instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "gfxtim.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

GFXTIM_HandleTypeDef hgfxtim;

/* GFXTIM init function */
void MX_GFXTIM_Init(void)
{

  /* USER CODE BEGIN GFXTIM_Init 0 */

  /* USER CODE END GFXTIM_Init 0 */

  GFXTIM_ClockGeneratorConfigTypeDef pClockGeneratorConfig = {0};

  /* USER CODE BEGIN GFXTIM_Init 1 */

  /* USER CODE END GFXTIM_Init 1 */
  hgfxtim.Instance = GFXTIM;
  hgfxtim.Init.SynchroSrc = GFXTIM_SYNC_SRC_HSYNC_VSYNC_0;
  if (HAL_GFXTIM_Init(&hgfxtim) != HAL_OK)
  {
    Error_Handler();
  }
  pClockGeneratorConfig.LineClockSrc = GFXTIM_LINE_CLK_SRC_LCC_UNDERFLOW;
  pClockGeneratorConfig.FrameClockSrc = GFXTIM_FRAME_CLK_SRC_LCC_UNDERFLOW;
  pClockGeneratorConfig.LineClockCalib = GFXTIM_LINE_CLK_CALIB_DISABLE;
  pClockGeneratorConfig.FrameClockCalib = GFXTIM_FRAME_CLK_CALIB_DISABLE;
  if (HAL_GFXTIM_ClockGenerator_Config(&hgfxtim, &pClockGeneratorConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN GFXTIM_Init 2 */

  /* USER CODE END GFXTIM_Init 2 */

}

void HAL_GFXTIM_MspInit(GFXTIM_HandleTypeDef* gfxtimHandle)
{

  if(gfxtimHandle->Instance==GFXTIM)
  {
  /* USER CODE BEGIN GFXTIM_MspInit 0 */

  /* USER CODE END GFXTIM_MspInit 0 */
    /* GFXTIM clock enable */
    __HAL_RCC_GFXTIM_CLK_ENABLE();

    /* GFXTIM interrupt Init */
    HAL_NVIC_SetPriority(GFXTIM_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(GFXTIM_IRQn);
  /* USER CODE BEGIN GFXTIM_MspInit 1 */

  /* USER CODE END GFXTIM_MspInit 1 */
  }
}

void HAL_GFXTIM_MspDeInit(GFXTIM_HandleTypeDef* gfxtimHandle)
{

  if(gfxtimHandle->Instance==GFXTIM)
  {
  /* USER CODE BEGIN GFXTIM_MspDeInit 0 */

  /* USER CODE END GFXTIM_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_GFXTIM_CLK_DISABLE();

    /* GFXTIM interrupt Deinit */
    HAL_NVIC_DisableIRQ(GFXTIM_IRQn);
  /* USER CODE BEGIN GFXTIM_MspDeInit 1 */

  /* USER CODE END GFXTIM_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
