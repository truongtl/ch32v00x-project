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

#define PAGE_WRITE_START_ADDR          ((uint32_t)0x08003000) /* Start from 12K */
#define PAGE_WRITE_END_ADDR            ((uint32_t)0x08004000) /* End at 16K */

void Flash_Test(void)
{
    FLASH_HandleTypeDef hflash;
    hflash.Flash_ProgramMethod = FLASH_PROG_METHOD_DEFAULT;
    hflash.Flash_ProgramType = FLASH_TYPE_PROGRAM_HALFWORD;
    hflash.Flash_EraseType = FLASH_TYPE_ERASE_SECTOR;

    uint8_t EraseCounter = 0;
    uint8_t NumOfSector = (PAGE_WRITE_END_ADDR - PAGE_WRITE_START_ADDR) / FLASH_PAGE_SIZE;
    HAL_StatusTypeDef status = HAL_OK;
    uint16_t data = 0xABCD;

    status = HAL_FLASH_Unlock(&hflash);

    if (status != HAL_OK)
    {
        printf("FLASH Unlock FAILED\r\n");
    }
    else
    {
        printf("FLASH Unlocked\r\n");
    }

    for (EraseCounter = 0; (EraseCounter < NumOfSector) && (status == HAL_OK); EraseCounter++)
    {
        hflash.Flash_EraseAddress = PAGE_WRITE_START_ADDR + (FLASH_PAGE_SIZE * EraseCounter);
        status = HAL_FLASH_Erase(&hflash);

        if (status != HAL_OK)
        {
            printf("FLASH Erase ERR at sector %d\r\n", EraseCounter + 60);
        }
        else
        {
            printf("FLASH Erase sector %d...\r\n", EraseCounter + 60);
        }
    }

    hflash.Flash_ProgramAdress = PAGE_WRITE_START_ADDR;
    printf("Programing...\r\n");
    while ((hflash.Flash_ProgramAdress < PAGE_WRITE_END_ADDR) && (status == HAL_OK))
    {
        status = HAL_FLASH_Program(&hflash, data);
        hflash.Flash_ProgramAdress += 2;
    }

    if (status != HAL_OK)
    {
        printf("Memory Program FAILED!\r\n");
    }
    else
    {
        printf("Memory Program PASSED!\r\n");
    }

    status = HAL_FLASH_Lock(&hflash);

    if (status != HAL_OK)
    {
        printf("FLASH Lock FAILED\r\n");
    }
    else
    {
        printf("FLASH Locked\r\n");
    }
}


int main(void)
{
    SystemCoreClockUpdate();
    HAL_TickInit();
    HAL_NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    USART_Printf_Init(115200);
    SystemCoreClockUpdate();
    printf("SystemClk:%d\r\n",SystemCoreClock);
    Flash_Test();

    while(1)
    {
    }
}

