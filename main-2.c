// main.c - 系統進入點與 RTOS 啟動
#include "main.h"               // 包含系統初始化的函式原型
#include "cmsis_os.h"           // CMSIS RTOS 的 API 定義
#include "gpio.h"               // GPIO 初始化相關
#include "usart.h"              // UART 初始化相關
#include "freertos_tasks.h"     // 我們自定義的 RTOS 任務初始化頭檔

int main(void)
{
  HAL_Init();                   // 初始化 HAL 庫（包括 Flash, SysTick, NVIC 等）
  SystemClock_Config();         // 設定系統時鐘頻率（例如 180MHz）

  MX_GPIO_Init();               // 初始化所有使用到的 GPIO（LED、按鍵）
  MX_USART2_UART_Init();       // 初始化 USART2，做為 UART 通訊介面

  MX_FREERTOS_Init();          // 建立 RTOS 任務與通訊資源（Queue、Semaphore、Mutex）
  osKernelStart();             // 啟動 RTOS 核心，開始多工排程

  while (1) {}                  // 此處不再執行，因為任務將由 RTOS 控制
}










