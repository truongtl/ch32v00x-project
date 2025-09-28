/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : truongtl
 * Version            : V1.0
 * Date               : 2025/08/26
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2025 Developed by truongtl (Truong Tran)
 *******************************************************************************/

#include "ch32v00x_hal.h"
#include <string.h>
UART_HandleTypeDef uart_handle;
uint8_t rx_buff[20] = {0};

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE();

    GPIO_InitTypeDef gpio;
    gpio.GPIO_Pin = GPIO_Pin_5;
    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio.GPIO_Speed = GPIO_Speed_30MHz;
    HAL_GPIO_Init(GPIOD, &gpio);

    gpio.GPIO_Pin = GPIO_Pin_6;
    gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    HAL_GPIO_Init(GPIOD, &gpio);

    NVIC_InitTypeDef  NVIC_InitStructure = {0};
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    HAL_NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    HAL_NVIC_Init(&NVIC_InitStructure);
}

int main(void)
{
    SystemCoreClockUpdate();
    HAL_TickInit();

    uart_handle.Instance = USART1;
    uart_handle.Init.UART_BaudRate = 115200;
    uart_handle.Init.UART_WordLength = UART_WORDLENGTH_8B;
    uart_handle.Init.UART_StopBits = UART_STOPBITS_1;
    uart_handle.Init.UART_Parity = UART_PARITY_NONE;
    uart_handle.Init.UART_Mode = UART_MODE_TX_RX;
    uart_handle.Init.UART_HardwareFlowControl = UART_HWCONTROL_NONE;
    HAL_UART_Init(&uart_handle);

    uint8_t hello[]  = "Hello UART!\r\n";
    HAL_UART_Transmit(&uart_handle, hello, sizeof(hello), 100);
    HAL_UART_Receive_IT(&uart_handle, rx_buff, 5);

    while(1)
    {
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        HAL_UART_Transmit(&uart_handle, rx_buff, 5, 50);
        HAL_UART_Receive_IT(&uart_handle, rx_buff, 5);
    }
}
