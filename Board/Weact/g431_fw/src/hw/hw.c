/*
 * hw.c
 *
 *  Created on: Feb 4, 2025
 *      Author: UA
 */


#include "hw.h"

bool hwInit(void)
{
  bool ret = true;

  ret &= bspInit();
//
//  ret &= rtcInit();
//  ret &= resetInit();
  ret &= ledInit();
  ret &= usbInit();
  ret &= usbBegin(USB_CDC_MODE);
//
//  if(resetGetCount() == 2)
//  {
//    resetToSysBoot();
//  }

  return ret;
}
