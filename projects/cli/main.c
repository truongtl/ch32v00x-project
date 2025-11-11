/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : truongtl
 * Version            : V1.0
 * Date               : 2025/11/12
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2025 Developed by truongtl (Truong Tran)
 *******************************************************************************/

#include "ch32v00x_hal.h"
#include "uart.h"
#include "cli.h"

UART_HandleTypeDef uart_handle;

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

void GPIO_Init(void)
{
    __HAL_RCC_GPIOD_CLK_ENABLE();
    GPIO_InitTypeDef cfg;
    cfg.GPIO_Pin = GPIO_Pin_2;
    cfg.GPIO_Mode = GPIO_Mode_Out_PP;
    cfg.GPIO_Speed = GPIO_Speed_2MHz;
    HAL_GPIO_Init(GPIOD, &cfg);
}

void UART_Init(void)
{
    uart_handle.Instance = USART1;
    uart_handle.Init.UART_BaudRate = 115200;
    uart_handle.Init.UART_WordLength = UART_WORDLENGTH_8B;
    uart_handle.Init.UART_StopBits = UART_STOPBITS_1;
    uart_handle.Init.UART_Parity = UART_PARITY_NONE;
    uart_handle.Init.UART_Mode = UART_MODE_TX_RX;
    uart_handle.Init.UART_HardwareFlowControl = UART_HWCONTROL_NONE;
    HAL_UART_Init(&uart_handle);
}

int main(void)
{
    SystemCoreClockUpdate();
    HAL_TickInit();
    GPIO_Init();
    UART_Init();
    uart_start_rx();

    cli_register_default_table();

    uart_println("UART-CLI ready. Try 'help'.");
    while(1)
    {
        uint8_t ch;
        if (uart_getc(&ch))
        {
            cli_process_byte(ch);
        }
    }
}
