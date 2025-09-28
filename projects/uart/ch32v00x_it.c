/********************************** (C) COPYRIGHT *******************************
 * File Name          : ch32v00x_it.c
 * Author             : truongtl
 * Version            : V1.0
 * Date               : 2025/09/29
 * Description        : Main Interrupt Service Routines.
*********************************************************************************
 * Copyright (c) 2025 Developed by truongtl (Truong Tran)
*******************************************************************************/
#include "ch32v00x_hal.h"

void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI7_0_IRQHandler(void);
extern UART_HandleTypeDef uart_handle;

/*********************************************************************
 * @fn      NMI_Handler
 *
 * @brief   This function handles NMI exception.
 *
 * @return  none
 */
void NMI_Handler(void)
{
  while (1)
  {
  }
}

/*********************************************************************
 * @fn      HardFault_Handler
 *
 * @brief   This function handles Hard Fault exception.
 *
 * @return  none
 */
void HardFault_Handler(void)
{
  HAL_NVIC_SystemReset();
  while (1)
  {
  }
}

void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler(&uart_handle);
}
