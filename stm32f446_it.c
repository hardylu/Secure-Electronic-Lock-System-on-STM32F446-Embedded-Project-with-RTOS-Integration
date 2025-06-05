// stm32f4xx_it.c - 中斷處理函式
void USART2_IRQHandler(void)
{
  if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE)) {
    char c;
    HAL_UART_Receive(&huart2, (uint8_t*)&c, 1, HAL_MAX_DELAY);
    osMessageQueuePut(uartQueueHandle, &c, 0, 0); // 放入佇列
  }
  HAL_UART_IRQHandler(&huart2);
}

void EXTI15_10_IRQHandler(void)
{
  if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_13) != RESET) {
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13);
    osSemaphoreRelease(keySemaphoreHandle); // 通知任務
  }
}