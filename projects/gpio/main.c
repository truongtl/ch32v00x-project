/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : truongtl
 * Version            : V1.0
 * Date               : 2025/09/29
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2025 Developed by truongtl (Truong Tran)
 *******************************************************************************/

#include "ch32v00x_hal.h"

void GPIO_Cfg(void)
{
    __HAL_RCC_GPIOD_CLK_ENABLE();
    GPIO_InitTypeDef cfg;
    cfg.GPIO_Pin = GPIO_Pin_2;
    cfg.GPIO_Mode = GPIO_Mode_Out_PP;
    cfg.GPIO_Speed = GPIO_Speed_2MHz;
    HAL_GPIO_Init(GPIOD, &cfg);
}

int main(void)
{
    SystemCoreClockUpdate();
    HAL_TickInit();
    GPIO_Cfg();

    while (1)
    {
        HAL_GPIO_Write(GPIOD, GPIO_Pin_2, GPIO_PIN_SET);
        HAL_Delay(100);
        HAL_GPIO_Write(GPIOD, GPIO_Pin_2, GPIO_PIN_RESET);
        HAL_Delay(100);
    }
}
