/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "fatfs.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fatfs_sd.h"
#include "stdio.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

SPI_HandleTypeDef hspi2;
FATFS fs;
FATFS *pfs;
FIL fil;
FRESULT fres;
DWORD fre_clust;
uint32_t totalSpace, freeSpace;
char buffer[100];

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
int _write(int file, char* p, int len)
{
	if(HAL_UART_Transmit(&huart3, (uint8_t*)p, len, 10)==HAL_OK) return len;
	else return 0;
}
void _Error_Handler(char *file, int line);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_USART3_UART_Init();
  MX_FATFS_Init();
  MX_SPI2_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */


  /* Wait for SD module reset */
	HAL_Delay(1000);

	/* Waiting for the Micro SD module to initialize */
	HAL_Delay(500);

	fres = f_mount(&fs, "", 0);
	if (fres == FR_OK) {
		printf("Micro SD card is mounted successfully!\r\n");
	} else if (fres != FR_OK) {
		printf("Micro SD card's mount error!\r\n");
	}

	// FA_OPEN_APPEND opens file if it exists and if not then creates it,
	// the pointer is set at the end of the file for appending
	fres = f_open(&fil, "log-file.txt", FA_OPEN_APPEND | FA_WRITE | FA_READ);
	if (fres == FR_OK) {
		printf("File opened for reading and checking the free space.\r\n");
	} else if (fres != FR_OK) {
		printf("File was not opened for reading and checking the free space!\r\n");
	}

	fres = f_getfree("", &fre_clust, &pfs);
	totalSpace = (uint32_t) ((pfs->n_fatent - 2) * pfs->csize * 0.5);
	freeSpace = (uint32_t) (fre_clust * pfs->csize * 0.5);
	char mSz[100];
	sprintf(mSz, "%lu", (uint32_t)freeSpace);
	if (fres == FR_OK) {
		printf("The free space is: ");
		printf(mSz);
		printf("\r\n");
	} else if (fres != FR_OK) {
		printf("The free space could not be determined!\r\n");
	}

	for (uint8_t i = 0; i < 10; i++) {
		f_puts("This text is written in the file.\n", &fil);
	}

	fres = f_close(&fil);
	if (fres == FR_OK) {
		printf("The file is closed.\r\n");
	} else if (fres != FR_OK) {
		printf("The file was not closed.\r\n");
	}

	/* Open file to read */
	fres = f_open(&fil, "log-file.txt", FA_READ);
	if (fres == FR_OK) {
		printf("File opened for reading.\r\n");
	} else if (fres != FR_OK) {
		printf("File was not opened for reading!\r\n");
	}

	while (f_gets(buffer, sizeof(buffer), &fil)) {
		char mRd[100];
		sprintf(mRd, "%s", buffer);
		printf(mRd);

	}

	/* Close file */
	fres = f_close(&fil);
	if (fres == FR_OK) {
		printf("The file is closed.\r\n");
	} else if (fres != FR_OK) {
		printf("The file was not closed.\r\n");
	}

	f_mount(NULL, "", 1);
	if (fres == FR_OK) {
		printf("The Micro SD card is unmounted!\r\n");
	} else if (fres != FR_OK) {
		printf("The Micro SD was not unmounted!\r\n");
	}


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
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
void _Error_Handler(char *file, int line)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	while(1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	static uint32_t temp;
	if(GPIO_Pin == GPIO_PIN_10)	// PIN_3 Pressed
	{
		if(HAL_GetTick() - temp > 100){
			printf("%s\r\n", "PIN_10 Pressed");
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);

//			/* Wait for SD module reset */
//			HAL_Delay(500);
//
//			/* Waiting for the Micro SD module to initialize */
//			HAL_Delay(500);
//
//			fres = f_mount(&fs, "", 0);
//			if (fres == FR_OK) {
//				printf("Micro SD card is mounted successfully!\r\n");
//			} else if (fres != FR_OK) {
//				printf("Micro SD card's mount error!\r\n");
//			}
//
//			// FA_OPEN_APPEND opens file if it exists and if not then creates it,
//			// the pointer is set at the end of the file for appending
//			fres = f_open(&fil, "log-file.txt", FA_OPEN_APPEND | FA_WRITE | FA_READ);
//			if (fres == FR_OK) {
//				printf("File opened for reading and checking the free space.\r\n");
//			} else if (fres != FR_OK) {
//				printf("File was not opened for reading and checking the free space!\r\n");
//			}
//
//			fres = f_getfree("", &fre_clust, &pfs);
//			totalSpace = (uint32_t) ((pfs->n_fatent - 2) * pfs->csize * 0.5);
//			freeSpace = (uint32_t) (fre_clust * pfs->csize * 0.5);
//			char mSz[12];
//			sprintf(mSz, "%lu", freeSpace);
//			if (fres == FR_OK) {
//				printf("The free space is: ");
//				printf(mSz);
//				printf("\r\n");
//			} else if (fres != FR_OK) {
//				printf("The free space could not be determined!\r\n");
//			}
//
//			for (uint8_t i = 0; i < 10; i++) {
//				f_puts("This text is written in the file.\n", &fil);
//			}
//
//			fres = f_close(&fil);
//			if (fres == FR_OK) {
//				printf("The file is closed.\r\n");
//			} else if (fres != FR_OK) {
//				printf("The file was not closed.\r\n");
//			}
//
//			/* Open file to read */
//			fres = f_open(&fil, "log-file.txt", FA_READ);
//			if (fres == FR_OK) {
//				printf("File opened for reading.\r\n");
//			} else if (fres != FR_OK) {
//				printf("File was not opened for reading!\r\n");
//			}
//
//			while (f_gets(buffer, sizeof(buffer), &fil)) {
//				char mRd[100];
//				sprintf(mRd, "%s", buffer);
//				printf(mRd);
//
//			}
//
//			/* Close file */
//			fres = f_close(&fil);
//			if (fres == FR_OK) {
//				printf("The file is closed.\r\n");
//			} else if (fres != FR_OK) {
//				printf("The file was not closed.\r\n");
//			}
//
//			f_mount(NULL, "", 1);
//			if (fres == FR_OK) {
//				printf("The Micro SD card is unmounted!\r\n");
//			} else if (fres != FR_OK) {
//				printf("The Micro SD was not unmounted!\r\n");
//			}




		}

		//while(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3) == GPIO_PIN_RESET);
		while(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_10) == GPIO_PIN_RESET){
			//printf("%s\r\n", "wait for reset");
		}	// button -> 0
		temp = HAL_GetTick();	// check last time
	}



}

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

