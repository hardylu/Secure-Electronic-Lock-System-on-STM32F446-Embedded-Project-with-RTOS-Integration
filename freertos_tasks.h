// freertos_tasks.h - 任務初始化與變數宣告（對應 freertos_tasks.c）
#ifndef FREERTOS_TASKS_H
#define FREERTOS_TASKS_H

#include "cmsis_os.h"           // 引入 RTOS 類型與 API

// 任務與通訊物件的外部宣告
extern osThreadId_t passwordTaskHandle;
extern osThreadId_t ledTaskHandle;
extern osThreadId_t keyTaskHandle;
extern osThreadId_t watchdogTaskHandle;
extern osMessageQueueId_t uartQueueHandle;
extern osSemaphoreId_t keySemaphoreHandle;
extern osMutexId_t passwordMutex;  // 新增 mutex 宣告

// 任務註冊與任務主函式宣告
void MX_FREERTOS_Init(void);
void StartPasswordTask(void *argument);
void StartLEDTask(void *argument);
void StartKeyTask(void *argument);
void StartWatchdogTask(void *argument);

#endif
