/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int count = 0;

uint8_t TxData[32];

char tempBuffer[64] ={};
uint8_t RxData[20];
uint8_t RxDMAData[20];
uint8_t RxTemp[2];
int RxIndx = 0;

uint8_t RxDMALarge[4096];

int isNumber = 1;


int counthalf_DMA = 0;
int countfull_DMA = 0;


uint8_t RxDataFlash[256];
uint8_t flashBuffer[4096];
int HTC=0;
int FTC=0;
uint32_t flashIndx=0;
int isSizeRxed = 0;
uint32_t size = 0;



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len)
{
	HAL_UART_Transmit(&huart3, (uint8_t*)ptr, len, 10);
	for(uint32_t i=0; i<len; i++)
	{
		ITM_SendChar((*ptr++));
	}
	return len;
}
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	memcpy(RxData+RxIndx, RxTemp, 1);
//	if(++RxIndx >= 20){RxIndx = 0;}
//	HAL_UART_Receive_IT(&huart2, RxTemp, 1);
//
//}

// 1.DMA_Simple_Test
//void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)
//{
//	counthalf_DMA++;
//}
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	countfull_DMA++;
//	HAL_UART_Receive_DMA(&huart2, RxDMAData, 10);
//}

//// 2. DMA_Large_Data_Receive
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if(isSizeRxed == 0)
//	{
//		// 4 byte data character (48 == '0') -> number
//		for(int i=0; i<4; i++)
//		{
//			if(RxDMALarge[i] >= '0' && RxDMALarge[i] <= '9')
//			{
//				isNumber = 1;
//			}
//			else
//			{
//				isNumber = 0;
//				break;
//			}
//		}
//
//		if(isNumber == 1)
//		{
//			size = ((RxDMALarge[0] - 48)*1000) + ((RxDMALarge[1] - 48)*100) + ((RxDMALarge[2] - 48)*10) + ((RxDMALarge[3] - 48));	// 4 Digit
//			printf("Prepare : %d byte\n\r", (int)size);
//			HAL_UART_Receive_DMA(&huart2, RxDMALarge, size);
//			isSizeRxed = 1;
//		}
//		else if(isNumber == 0)
//		{
//			isNumber = 1;
//			//memset(RxDMALarge, 0, 4);
//			memset(tempBuffer, 0, strlen(tempBuffer));
//			char txText[] = "Only write Number\n\r";
//			char uart2Target[] = "UART2: ";
//
//
//
//			int offset = 0;
//			int ret = snprintf(tempBuffer + offset, sizeof(tempBuffer)-offset, uart2Target);
//			//assert(ret == strlen(uart2Target));
//			offset += ret;
//
//			for(int j=0; j<strlen(txText);j++)
//			{
//				ret = snprintf(tempBuffer + offset, sizeof(tempBuffer)-offset, "%c", txText[j]);
//				offset += ret;
//			}
//			//ret = snprintf(tempBuffer + offset, sizeof(tempBuffer)-offset, "\n\r");
//			//assert(ret == 2);
//			printf(txText);
//			HAL_UART_Transmit_IT(&huart2, (uint8_t*)tempBuffer, strlen((char*)tempBuffer));
//			//memset(tempBuffer, 0, strlen(tempBuffer));
//			HAL_UART_Receive_DMA(&huart2, RxDMALarge, 4);
//		}
//
//
//	}
//	else if(isSizeRxed == 1)
//	{
//		isSizeRxed = 0;
//		printf("Received : %d byte\n\r", (int)size);
//		HAL_UART_Receive_DMA(&huart2, RxDMALarge, 4);
//	}
//}


void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)
{
	if(isSizeRxed == 0)
	{
		size = ((RxDataFlash[0] - 48)*1000) + ((RxDataFlash[1] - 48)*100) + ((RxDataFlash[2] - 48)*10) + ((RxDataFlash[3] - 48));
		printf("Start to Send File => %d byte\r\n", (int)size);
		flashIndx = 0;
		memcpy(flashBuffer+flashIndx, RxDataFlash + 4, 124);	// Receive 128( 4(size) + 124(First Data)) => flash <- 124 byte
		memset(RxDataFlash, '\0', 128);
		flashIndx += 128;
		isSizeRxed = 1;
	}
	else
	{
		memcpy(flashBuffer+flashIndx, RxDataFlash, 128);
		memset(RxDataFlash, '\0', 128);
		flashIndx +=128;
	}

	HTC=1;
	FTC=0;

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	memcpy(flashBuffer+flashIndx, RxDataFlash+128, 128);
	memset(RxDataFlash+128, '\0', 128);
	flashIndx += 128;
	HTC=0;
	FTC=1;
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

//  HAL_UART_Receive_DMA(&huart2, RxDMAData, 10);
//  HAL_UART_Receive_DMA(&huart2, RxDMALarge, 4);	// 4 byte -> length
  HAL_UART_Receive_DMA(&huart2, RxDataFlash, 256);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  // left Data Under 128
	  if( ((size-flashIndx)>0) && ((size-flashIndx)<128) )
	  {
		  if(HTC == 1)
		  {
			  memcpy(flashBuffer+flashIndx, RxDataFlash+128, (size-flashIndx));
			  //strcpy((char*)flashBuffer+flashIndx, (char*)RxDataFlash+128);
			  flashIndx = size;
			  isSizeRxed = 0;
			  HTC = 0;
			  HAL_UART_DMAStop(&huart2);
			  HAL_UART_Receive_DMA(&huart2, RxDataFlash, 256);


		  }
		  else if(FTC == 1)
		  {
			  memcpy(flashBuffer+flashIndx, RxDataFlash, (size-flashIndx));	// Existing Buffer with additional size
			  //strcpy((char*)flashBuffer+flashIndx, (char*)RxDataFlash);
			  flashIndx = size;
			  isSizeRxed = 0;
			  FTC = 0;
			  HAL_UART_DMAStop(&huart2);
			  HAL_UART_Receive_DMA(&huart2, RxDataFlash, 256);

		  }
		  printf("File Received in flash => %d byte\r\n", (int)flashIndx);
	  }
	  else if( (flashIndx == size) && ((HTC==1) || (FTC==1)) )
	  {

		  isSizeRxed = 0;
		  FTC = 0;
		  HTC = 0;
		  HAL_UART_DMAStop(&huart2);
		  HAL_UART_Receive_DMA(&huart2, RxDataFlash, 256);
		  printf("File Received in flash => %d byte\r\n", (int)flashIndx);
	  }

	  count++;
	  printf("VCP:[%d]\n\r", count);
	  sprintf((char*)TxData, "UART2: [%5d]\n\r", count);
	  HAL_UART_Transmit_IT(&huart2, TxData, sizeof(TxData));
	  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
	  HAL_Delay(1000);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
