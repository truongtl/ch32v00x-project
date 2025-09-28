/********************************** (C) COPYRIGHT  *******************************
 * File Name          : debug.h
 * Author             : truongtl
 * Version            : V1.0
 * Date               : 2022/08/08
 * Description        : This file contains all the functions prototypes for UART
 *                      Printf , Delay functions.
 *********************************************************************************
 * Copyright (c) 2025 Developed by truongtl (Truong Tran)
 *******************************************************************************/
#ifndef __DEBUG_H
#define __DEBUG_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>

void USART_Printf_Init(uint32_t baudrate);
void SDI_Printf_Enable(void);
extern UART_HandleTypeDef debug_uart_handle;
extern uint8_t debug_buff[20];

#ifdef __cplusplus
}
#endif

#endif /* __DEBUG_H */
