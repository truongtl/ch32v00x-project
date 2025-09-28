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

void GoToIAP(void)
{
    FLASH_HandleTypeDef hflash;
    hflash.Flash_ProgramMethod = FLASH_PROG_METHOD_DEFAULT;
    SET_BIT(RCC->RSTSCKR, RCC_RMVF);
    HAL_FLASH_SystemReset(&hflash, Start_Mode_BOOT);
    HAL_NVIC_SystemReset();
}

uint8_t CompareBuf(void)
{
    uint8_t ref_buf[] = "iap";

    for (uint8_t i = 0; i < 3; i++)
    {
        if (debug_buff[i] != ref_buf[i]) return 0;
    }

    return 1;
}

int main(void)
{
    SystemCoreClockUpdate();
    HAL_TickInit();
    USART_Printf_Init(115200);
    printf("IAP app started!\r\n");
    printf("SystemClk:%d\r\n",SystemCoreClock);

    while (1)
    {
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        if (CompareBuf() == 1)
        {
            printf("Go to IAP...\r\n");
            GoToIAP();
        }
    }
}
