#ifndef __JAY31_H__
#define __JAY31_H__

#include "main.h"

#define UART3_BUFFER_SIZE 100 // ��������С
#define END_CHAR3 '1' // ��������

#define HAL_UART3_Receive_IT 	HAL_UART_Receive_IT(&huart3, &uart3_rx_buffer[uart3_rx_index], 1)			//������һ�ν���

extern UART_HandleTypeDef huart3;

void JAY31_Init(void);
void usart3_process_data(uint8_t *data, uint16_t length);
void HAL_UART3_RxCpltCallback(UART_HandleTypeDef *huart);

#endif
