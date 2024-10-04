 main{
	HAL_UART_RegisterRxEventCallback(&huart3, RxCompleteCallback);
	HAL_UARTEx_ReceiveToIdle_DMA(&huart3, (uint8_t *)serialBuff, serialBuff_SIZE);
	__HAL_DMA_DISABLE_IT(huart3.hdmarx, DMA_IT_HT);

  fifo_init(&fifo);


  while(1){
  
  }
}



 void RxCompleteCallback(UART_HandleTypeDef *huart, uint16_t Size){
	fifo_write(&fifo, (uint8_t *)serialBuff, Size);
	HAL_UARTEx_ReceiveToIdle_DMA(huart, (uint8_t *)serialBuff, serialBuff_SIZE);
	__HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);

}
