/********************************** (C) COPYRIGHT *******************************
 * File Name          : system_ch32v00x.h
 * Author             : truongtl
 * Version            : V1.0
 * Date               : 2025/09/29
 * Description        : CH32V003 Device Peripheral Access Layer System Header File.
*********************************************************************************
 * Copyright (c) 2025 Developed by truongtl (Truong Tran)
*******************************************************************************/
#ifndef __SYSTEM_CH32V00x_H
#define __SYSTEM_CH32V00x_H

#ifdef __cplusplus
 extern "C" {
#endif 

extern uint32_t SystemCoreClock;          /* System Clock Frequency (Core Clock) */

/* System_Exported_Functions */  
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /*__CH32V00x_SYSTEM_H */
