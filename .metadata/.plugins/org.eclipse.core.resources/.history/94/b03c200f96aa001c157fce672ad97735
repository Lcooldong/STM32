#ifndef _HAL_VS1003B_H
#define _HAL_VS1003B_H

#include "stm32f4xx_hal.h"

#define SPI_SPEED_HIGH 1
#define SPI_SPEED_LOW  0

/* reset */
#define MP3_RESET(x) x ? HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET)

/* /CS */
#define MP3_CCS(x) x ? HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET)

/* xDCS */
#define MP3_DCS(x)   x ? HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)

/* DREQ */
#define MP3_DREQ     HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7)


#define VS1003_WRITE_COMMAND 0x02
#define VS1003_READ_COMMAND  0x03


/* VS1003 Register */
#define SPI_MODE        0x00
#define SPI_STATUS      0x01
#define SPI_BASS        0x02
#define SPI_CLOCKF      0x03
#define SPI_DECODE_TIME 0x04
#define SPI_AUDATA      0x05
#define SPI_WRAM        0x06
#define SPI_WRAMADDR    0x07
#define SPI_HDAT0       0x08
#define SPI_HDAT1		0x09
#define SPI_AIADDR		0x0A
#define SPI_VOL			0x0B
#define SPI_AICTRL0		0x0C
#define SPI_AICTRL1		0x0D
#define SPI_AICTRL2		0x0E
#define SPI_AICTRL3		0x0F

#define SPI_CLKCKF      0x9800

#endif
