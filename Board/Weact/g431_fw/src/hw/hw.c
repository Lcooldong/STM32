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


  return ret;
}
