#include "gpio.h"

void MX_GPIO_Init(void)
{
  __HAL_RCC_GPIOA_CLK_ENABLE(); // 啟用 GPIOA 時鐘
  __HAL_RCC_GPIOC_CLK_ENABLE(); // 啟用 GPIOC 時鐘

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  // 設定 PA5（紅燈）
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  // 設定 PA6（綠燈）
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  // 設定 PC13（按鍵）為外部中斷輸入
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}
