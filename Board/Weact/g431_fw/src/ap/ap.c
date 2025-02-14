/*
 * ap.c
 *
 *  Created on: Feb 4, 2025
 *      Author: UA
 */


#include "ap.h"

void apInit(void)
{

}

void apMain(void)
{
  uint32_t pre_time[2];

  for(int i=0; i<sizeof(pre_time); i++)
  {
    pre_time[i] = millis();
  }

  while(1)
  {
    uint32_t cur_time = millis();
    if(cur_time - pre_time[0] >= 500)
    {
      pre_time[0] = cur_time;
      ledToggle(_DEF_LED1);
    }


    if(cdcIsConnect() == true)
    {
      if(cur_time - pre_time[1] >= 500)
      {
        pre_time[1] = cur_time;
        ledToggle(_DEF_LED2);
      }
    }
    else
    {
      ledOff(_DEF_LED2);
    }

    if(cdcAvailable() > 0)
    {
      uint8_t rx_data;
      char *startText = "RX : ";
      char *endText = "\r\n";

      rx_data = cdcRead();

      cdcWrite((uint8_t*)startText, sizeof(startText));
      cdcWrite(&rx_data, 1);
      cdcWrite((uint8_t*)endText, sizeof(endText));

    }

  }
}
