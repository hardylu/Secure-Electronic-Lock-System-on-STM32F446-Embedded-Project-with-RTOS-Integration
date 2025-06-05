#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f446_hal.h"   // 基本 HAL 函式
#include "cmsis_os.h"        // RTOS 核心 API（如果用到）

/* 用來在 main.c 呼叫系統時鐘設定 */
void SystemClock_Config(void);

/* 你也可以在這裡宣告全域變數（不推薦太多） */
extern UART_HandleTypeDef huart2;

/* 你也可以定義一些常用的 LED 宏（可選） */
#define LED_RED_GPIO_PORT GPIOA
#define LED_RED_PIN       GPIO_PIN_5
#define LED_GREEN_GPIO_PORT GPIOA
#define LED_GREEN_PIN       GPIO_PIN_6

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
