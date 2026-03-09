/*main.h*/
#ifndef __MAIN_H
#define __MAIN_H
    
#include "stm32f3xx_ll_bus.h"
#include "stm32f3xx_ll_rcc.h"
#include "stm32f3xx_ll_system.h"
#include "stm32f3xx_ll_utils.h"
#include "stm32f3xx_ll_gpio.h"
#include "stm32f3xx_ll_cortex.h"
#include "stm32f3xx_ll_usart.h"
#include "stm32f3xx_ll_dma.h"
#include "stm32f3xx_ll_i2c.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#define TM1_START_CMD "tm1"
#define TM2_START_CMD "tm2"
#define TM1_STOP_CMD  "stop1"
#define TM2_STOP_CMD  "stop2"

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
