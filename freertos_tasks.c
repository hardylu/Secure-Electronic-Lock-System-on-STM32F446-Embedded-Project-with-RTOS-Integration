#include "freertos_tasks.h"
#include "usart.h"
#include "gpio.h"
#include <string.h>

// 任務與資源的定義
osThreadId_t passwordTaskHandle;
osThreadId_t ledTaskHandle;
osThreadId_t keyTaskHandle;
osThreadId_t watchdogTaskHandle;
osMessageQueueId_t uartQueueHandle;
osSemaphoreId_t keySemaphoreHandle;
osMutexId_t passwordMutex;  // Mutex 變數實體

// 密碼與緩衝區
static char password[16] = "1234";           // 預設密碼
static char input_buffer[16];                // 輸入暫存區
static uint8_t change_mode = 0;              // 是否進入更改密碼模式

// 初始化所有任務與通訊資源
void MX_FREERTOS_Init(void)
{
  uartQueueHandle = osMessageQueueNew(32, sizeof(char), NULL); // 建立 UART 字元佇列
  keySemaphoreHandle = osSemaphoreNew(1, 0, NULL);              // 建立按鍵通知的 Semaphore
  passwordMutex = osMutexNew(NULL);                            // 建立 password 用的互斥鎖 Mutex

  const osThreadAttr_t taskAttr = {.stack_size = 128 * 4, .priority = osPriorityNormal};
  passwordTaskHandle = osThreadNew(StartPasswordTask, NULL, &taskAttr);  // 建立密碼任務
  ledTaskHandle = osThreadNew(StartLEDTask, NULL, &taskAttr);            // 建立 LED 控制任務
  keyTaskHandle = osThreadNew(StartKeyTask, NULL, &taskAttr);            // 建立按鍵任務
  watchdogTaskHandle = osThreadNew(StartWatchdogTask, NULL, &taskAttr);  // 建立看門狗任務
}

// 密碼比對與密碼變更任務
void StartPasswordTask(void *argument)
{
  char c;
  int idx = 0;
  for (;;) {
    if (osMessageQueueGet(uartQueueHandle, &c, NULL, osWaitForever) == osOK) {
      if (c == '\n' || c == '\r') {
        input_buffer[idx] = '\0';

        osMutexAcquire(passwordMutex, osWaitForever); // 加鎖：保護 password 共用區
        if (change_mode) {
          strncpy(password, input_buffer, sizeof(password));  // 修改密碼
          change_mode = 0;
          HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET); // 點亮綠燈
        } else {
          if (strcmp(password, input_buffer) == 0)
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET); // 正確 → 綠燈
          else
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); // 錯誤 → 紅燈
        }
        osMutexRelease(passwordMutex); // 解鎖

        idx = 0;  // 重設輸入索引
      } else {
        if (idx < sizeof(input_buffer) - 1)
          input_buffer[idx++] = c;  // 累積輸入字元
      }
    }
  }
}

// LED 控制任務，每 2 秒關掉燈（避免常亮）
void StartLEDTask(void *argument)
{
  for (;;) {
    osDelay(2000);  // 延遲 2 秒
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);  // 關紅燈
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);  // 關綠燈
  }
}

// 按鍵任務：等候 semaphore，收到就切換密碼模式
void StartKeyTask(void *argument)
{
  for (;;) {
    if (osSemaphoreAcquire(keySemaphoreHandle, osWaitForever) == osOK) {
      osMutexAcquire(passwordMutex, osWaitForever);  // 加鎖
      change_mode = 1;
      osMutexRelease(passwordMutex);                // 解鎖
    }
  }
}

// 看門狗任務：每秒餵狗一次，避免 MCU 被重設
void StartWatchdogTask(void *argument)
{
  for (;;) {
    IWDG->KR = 0xAAAA;  // 餵狗序列
    osDelay(1000);      // 每秒一次
  }
}