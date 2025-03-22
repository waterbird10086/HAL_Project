#ifndef __USART1_H__
#define __USART1_H__

#include "main.h"

#define UART1_BUFFER_SIZE 100 // 缓冲区大小
#define END_CHAR '\n' // 结束符号
	
#define HAL_UART1_Receive_IT 	HAL_UART_Receive_IT(&huart1, &rx_buffer[rx_index], 1)			//启动下一次接收

extern UART_HandleTypeDef huart1;

void usart1_Init(void);																																	//启动接收函数
void usart1_process_data(uint8_t *data, uint16_t length);
void HAL_UART1_RxCpltCallback(UART_HandleTypeDef *huart);

#endif 

