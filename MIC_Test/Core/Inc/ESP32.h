#ifndef __EPS32_H
#define __ESP32_H

#include <stdint.h>
//#include "UART_ROS.h"
#include "usart.h"
#include "stm32f1xx_hal.h"
#include "Car_Solution.h"
#include "stdio.h"

//extren???,??extren???,????????,??????

extern uint8_t ESP32_QueData;
extern uint8_t ESP32_Data[10];
extern uint8_t flag_Mode;
extern char Test_Data[50];
extern uint8_t NowMode;

#ifdef __cplusplus
extern "C" {
#endif

uint8_t ESP32_Analysis();

#ifdef __cplusplus
}
#endif

#endif
