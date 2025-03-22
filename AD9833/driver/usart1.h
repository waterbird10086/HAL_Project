#ifndef __USART1_H__
#define __USART1_H__

#include "main.h"

#define UART1_BUFFER_SIZE 100 // ��������С
#define END_CHAR '\n' // ��������
	
#define HAL_UART1_Receive_IT 	HAL_UART_Receive_IT(&huart1, &rx_buffer[rx_index], 1)			//������һ�ν���

extern UART_HandleTypeDef huart1;

void usart1_Init(void);																																	//�������պ���
void usart1_process_data(uint8_t *data, uint16_t length);
void HAL_UART1_RxCpltCallback(UART_HandleTypeDef *huart);

#endif 

