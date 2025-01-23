/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fdcan.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "test.h"
#include "stdio.h"
#include "string.h"
#include "usbd_cdc_if.h"
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
char countBuffer[32];
char buffer[32];
uint8_t RxTemp[2];
uint8_t RxData[32];
uint8_t FinalData[32];
uint8_t rx;
int RxIndx = 0;
int length = 0;

int ledState = 0;

FDCAN_FilterTypeDef sFilterConfig;
FDCAN_TxHeaderTypeDef TxHeader;
FDCAN_RxHeaderTypeDef RxHeader;

uint8_t RxCANData[8];
uint8_t TxCANData[8];

uint32_t lastMillis = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len)
{
  HAL_UART_Transmit(&huart4, (uint8_t*)ptr, len, 10);

  return len;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{ 
  if(huart->Instance == UART4)
  {
    memset(buffer, 0, sizeof(buffer));
    
    // HAL_UART_Receive_IT(&huart4, &rx, 1);
    // HAL_UART_Transmit(&huart4, &rx, 1, 10);
    HAL_UART_Receive_IT(&huart4, RxTemp, 1);
    // HAL_UART_Transmit(&huart4, RxTemp, 1, 10);
    
    sprintf(buffer, "Receivecd[%d] : %c\r\n", strlen(buffer), RxTemp[0]);
    HAL_UART_Transmit(&huart4, (uint8_t*)buffer, strlen(buffer), 10);
    memset(RxTemp, 0, sizeof(RxTemp));
  }
  //memcpy(RxData + RxIndx, RxTemp,1);
  

  //HAL_UART_Transmit_IT(&huart4, RxTemp, 1);
  

  
  // if(++RxIndx >= 1)
  // {
    
  //   printf(RxData);
  //   RxIndx = 0;
  // }
  // HAL_UART_Receive_IT(&huart4, RxData, 1);
}



void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
  
  if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
  {
    uint8_t usb_buf[32];
    
    // sprintf(usb_buf, "Received[%d] => \r\n", count);
    // CDC_Transmit_FS(usb_buf, strlen(usb_buf));
    // memset(usb_buf, 0,strlen(usb_buf));

    /* Retreive Rx messages from RX FIFO0 */
    if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxCANData) != HAL_OK)
    {
    /* Reception Error */
      Error_Handler();
    }

    if(hfdcan->Instance == FDCAN2)
    {

      // uint8_t TxData1[] = { 0x11, 0x22, 0x33, 0x44, 0x98, 0x55, 0x66, 0x77};	// 보낼데이터
      // if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &TxHeader, TxData1) != HAL_OK) {
      //   Error_Handler();
      // }
      
      uint32_t receivedID = RxHeader.Identifier;
      sprintf(usb_buf, "[%d] 0x%X\r\n", count, receivedID);
      CDC_Transmit_FS(usb_buf, strlen(usb_buf));
      memset(usb_buf, 0, strlen(usb_buf));

      if(RxHeader.Identifier == 0x125)
      {

      }
    }

    if (HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
    {
      /* Notification Error */
      Error_Handler();
    }
  }
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
  MX_UART4_Init();
  MX_USB_Device_Init();
  MX_FDCAN2_Init();
  /* USER CODE BEGIN 2 */

  
  // HAL_UART_Receive_IT(&huart4, RxData, 1);
  HAL_UART_Receive_IT(&huart4, RxTemp, 1);
  // HAL_UART_Receive_IT(&huart4, &rx, 1);

  sFilterConfig.IdType = FDCAN_STANDARD_ID;
  sFilterConfig.FilterIndex = 0;
  sFilterConfig.FilterType = FDCAN_FILTER_MASK;
  sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
  // sFilterConfig.FilterID1 = 0x123;
  // sFilterConfig.FilterID2 = 0x125;
  sFilterConfig.FilterID1 = 0x000;
  sFilterConfig.FilterID2 = 0x000;

  if (HAL_FDCAN_ConfigFilter(&hfdcan2, &sFilterConfig) != HAL_OK) {
    Error_Handler();
  }

  // if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan2, FDCAN_REJECT, FDCAN_REJECT,
  // FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE) != HAL_OK) {
  //   Error_Handler();
  // }

  // FDCAN 시작
  if (HAL_FDCAN_Start(&hfdcan2) != HAL_OK) {
	  Error_Handler();
  }

  // 수신인터럽트 설정
  if (HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO0_NEW_MESSAGE,
      0) != HAL_OK) {
    Error_Handler();
  }

  TxHeader.Identifier = 0x123;
  TxHeader.IdType = FDCAN_STANDARD_ID;	
  TxHeader.TxFrameType = FDCAN_DATA_FRAME;
  TxHeader.DataLength = FDCAN_DLC_BYTES_8;	// 데이터 길이
  TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
  TxHeader.BitRateSwitch = FDCAN_BRS_OFF;	
  TxHeader.FDFormat = FDCAN_FD_CAN;
  TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
  TxHeader.MessageMarker = 0x00;

  uint8_t TxData0[] = { 0x11, 0x32, 0x54, 0x76, 0x98, 0x00, 0x11, 0x22};	// 보낼데이터



  
  // 데이터 전송
  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

  // FDCAN_RxHeaderTypeDef rxHeader1;
  // uint8_t rxData1[8];
  // uint8_t temp_buf[32];

  

  // if (HAL_FDCAN_GetRxMessage(&hfdcan2, FDCAN_RX_FIFO0, &rxHeader1, rxData1) == HAL_OK)
  // {
  //   uint32_t receivedID = rxHeader1.Identifier;
  //   sprintf(temp_buf, "[%d] 0x%X\r\n", count, receivedID);
  //   CDC_Transmit_FS(temp_buf, strlen(temp_buf));
  //   memset(temp_buf, 0, strlen(temp_buf));
    
  // }

  uint32_t currentMillis = HAL_GetTick();

  if(currentMillis - lastMillis >= 1000)
  {
    lastMillis = currentMillis;
    count++;
    sprintf(countBuffer, "[%d]\r\n", count);
    CDC_Transmit_FS(countBuffer, strlen(countBuffer));
    HAL_UART_Transmit(&huart4, (uint8_t*)countBuffer, sizeof(countBuffer) -1, 10);
    memset(countBuffer, 0,strlen(countBuffer));
    
    for (int i = 0; i < 8; i++)
    {
      TxCANData[i] = i + count;
    }
    
    // If CAN is not connected => STOP
    if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &TxHeader, TxCANData) != HAL_OK) {
      Error_Handler();
    }
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  }

    // HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    // // printf("[%d]\r\n", count);
    
    // count++;
    // sprintf(countBuffer, "[%d]\r\n", count);
    // CDC_Transmit_FS(countBuffer, strlen(countBuffer));
    // HAL_UART_Transmit(&huart4, (uint8_t*)countBuffer, sizeof(countBuffer) -1, 10);
    // memset(countBuffer, 0,strlen(countBuffer));

    // // // 보낼 데이터 설정
    // TxHeader.Identifier = 0x123;
    // TxHeader.IdType = FDCAN_STANDARD_ID;	
    // TxHeader.TxFrameType = FDCAN_DATA_FRAME;
    // TxHeader.DataLength = FDCAN_DLC_BYTES_8;	// 데이터 길이
    // TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    // TxHeader.BitRateSwitch = FDCAN_BRS_ON;	
    // TxHeader.FDFormat = FDCAN_FD_CAN;
    // TxHeader.TxEventFifoControl = FDCAN_STORE_TX_EVENTS;
    // TxHeader.MessageMarker = 0x52;
    // if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &TxHeader, TxData0) != HAL_OK) {
    //   Error_Handler();
    // }
    // HAL_Delay(500);

    // if (RxTemp[0] == '\n' && RxIndx > 0)
	  // {
		//   memset(FinalData, 0, sizeof(FinalData));
		//   memcpy(FinalData, RxData, RxIndx);

		//   length = sprintf(buffer , "[%d]=>", RxIndx);
		//   for(uint8_t i = 0; i < RxIndx; i++)
		//   {
		// 	  length += sprintf(buffer + length, "%c", FinalData[i]);
		//   }

		//   HAL_UART_Transmit_IT(&huart4, (uint8_t*)buffer, length);

		//   memset(RxData, 0, sizeof(RxData));
		//   RxIndx = 0;

	  // }
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 42;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV4;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
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
