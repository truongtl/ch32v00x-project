/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : truongtl
 * Version            : V1.0
 * Date               : 2025/09/29
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2025 Developed by truongtl (Truong Tran)
 *******************************************************************************/

#include <ch32v00x_hal.h>
#include <debug.h>

int main(void)
{
    SystemCoreClockUpdate();
    HAL_TickInit();

    GPIO_InitTypeDef  GPIO_InitStructure={0};
    RCC_ClocksTypeDef RCC_ClocksStatus={0};

    HAL_NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    USART_Printf_Init(115200);
    SystemCoreClockUpdate();
    printf("APP START\r\n");
    printf("SystemClk:%d\r\n",SystemCoreClock);

    HAL_RCC_GetClocksFreq(&RCC_ClocksStatus);
    printf("SYSCLK_Frequency-%d\r\n", RCC_ClocksStatus.SYSCLK_Frequency);
    printf("HCLK_Frequency-%d\r\n", RCC_ClocksStatus.HCLK_Frequency);
    printf("PCLK1_Frequency-%d\r\n", RCC_ClocksStatus.PCLK1_Frequency);
    printf("PCLK2_Frequency-%d\r\n", RCC_ClocksStatus.PCLK2_Frequency);

    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* MCO Output GPIOC 4 */
    HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO_SYSCLK);
    // HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO_HSI);
    // HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO_HSE);
    // HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO_PLLCLK);

    while(1)
    {
    }
}

