#pragma once

#define LED_PORT    GPIOD
#define LED_PIN     GPIO_Pin_2

typedef struct {
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint16_t year;
} rtc_time_t;
