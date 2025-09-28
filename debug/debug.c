/********************************** (C) COPYRIGHT  *******************************
 * File Name          : debug.c
 * Author             : truongtl
 * Version            : V1.0
 * Date               : 2022/08/08
 * Description        : This file contains all the functions prototypes for UART
 *                      Printf , Delay functions.
 *********************************************************************************
 * Copyright (c) 2025 Developed by truongtl (Truong Tran)
 *******************************************************************************/
#include <ch32v00x_hal.h>
#include <debug.h>

#define DEBUG_DATA0_ADDRESS  ((volatile uint32_t*)0xE00000F4)
#define DEBUG_DATA1_ADDRESS  ((volatile uint32_t*)0xE00000F8)
UART_HandleTypeDef debug_uart_handle;
uint8_t debug_buff[20] = {0};
/*********************************************************************
 * @fn      USART_Printf_Init
 *
 * @brief   Initializes the USARTx peripheral.
 *
 * @param   baudrate - USART communication baud rate.
 *
 * @return  None
 */
void USART_Printf_Init(uint32_t baudrate)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE();

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);

    NVIC_InitTypeDef NVIC_InitStructure = {0};
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    HAL_NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    HAL_NVIC_Init(&NVIC_InitStructure);

    debug_uart_handle.Instance = USART1;
    debug_uart_handle.Init.UART_BaudRate = baudrate;
    debug_uart_handle.Init.UART_WordLength = UART_WORDLENGTH_8B;
    debug_uart_handle.Init.UART_StopBits = UART_STOPBITS_1;
    debug_uart_handle.Init.UART_Parity = UART_PARITY_NONE;
    debug_uart_handle.Init.UART_Mode = UART_MODE_TX_RX;
    debug_uart_handle.Init.UART_HardwareFlowControl = UART_HWCONTROL_NONE;
    HAL_UART_Init(&debug_uart_handle);
    HAL_UART_Receive_IT(&debug_uart_handle, debug_buff, 3);
}

/*********************************************************************
 * @fn      SDI_Printf_Enable
 *
 * @brief   Initializes the SDI printf Function.
 *
 * @param   None
 *
 * @return  None
 */
void SDI_Printf_Enable(void)
{
    // Do nothing
}

/*********************************************************************
 * @fn      _write
 *
 * @brief   Support Printf Function
 *
 * @param   *buf - UART send Data.
 *          size - Data length.
 *
 * @return  size - Data length
 */
__attribute__((used)) 
int _write(int fd, char *buf, int size)
{
    int i = 0;
    int writeSize = size;

    HAL_UART_Transmit(&debug_uart_handle, buf, writeSize, 100);

    return writeSize;
}

/*********************************************************************
 * @fn      _sbrk
 *
 * @brief   Change the spatial position of data segment.
 *
 * @return  size: Data length
 */
__attribute__((used)) 
void *_sbrk(ptrdiff_t incr)
{
    extern char _end[];
    extern char _heap_end[];
    static char *curbrk = _end;

    if ((curbrk + incr < _end) || (curbrk + incr > _heap_end))
    return NULL - 1;

    curbrk += incr;
    return curbrk - incr;
}



