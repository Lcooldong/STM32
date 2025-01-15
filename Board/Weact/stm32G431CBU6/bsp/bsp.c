#include "bsp.h"


void SystemClock_Config(void);


void bspInit(void)
{
    //HAL_Init
    SystemClock_Config();

    
}

void delay(uint32_t ms)
{

#ifdef _USB_HW_RTOS
    
#else
    HAL_Delay(ms);
#endif


}

uint32_t millis(void)
{
    return HAL_GetTick();
}