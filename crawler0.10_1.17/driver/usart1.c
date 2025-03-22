#include "usart1.h"

#include <stdio.h>
#include <string.h>

uint8_t rx_buffer[UART1_BUFFER_SIZE]; // ���ջ�����
uint16_t rx_index = 0; // ���ջ���������

//�������պ���
void usart1_Init(void)
{
	HAL_UART1_Receive_IT;
}

//int fputc(int ch,FILE *f)
//{
//	HAL_UART_Transmit(&huart1,(uint8_t*)&(ch),1,1000);
//	
//	return (ch);
//}

void usart1_process_data(uint8_t *data, uint16_t length)
{
    // ������Խ��յ������ݽ��д��������ӡ���������洢�ȵ�
    // ע�⣺���յ������ݳ���Ϊlength����������������'\n'
		if(strstr((char*)data, "LED1 ON\r\n"))
		{
			printf("LED1 is ON\r\n");
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
		}
		else if(strstr((char*)data, "LED1 OFF\r\n"))
		{
			printf("LED1 is OFF\r\n");
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);			
		}
		else if(strstr((char*)data, "LED2 ON\r\n"))
		{
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);			
		}
		else if(strstr((char*)data, "LED2 OFF\r\n"))
		{
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);			
		}
		memset(rx_buffer, 0, UART1_BUFFER_SIZE);//�����������������ȫ����0
}


void HAL_UART1_RxCpltCallback(UART_HandleTypeDef *huart)
{
        if (rx_index < UART1_BUFFER_SIZE - 1) // ���������пռ�
        {
            if (rx_buffer[rx_index - 1] != END_CHAR) // �����һ���ַ����ǽ�������
            {
                rx_buffer[rx_index++] = (uint8_t)(huart->Instance->DR & 0x00FF); // �����յ����ַ��洢����������
            }
            if(rx_buffer[rx_index - 1] == END_CHAR)// �����һ���ַ��ǽ�������
            {
                // �Խ��յ������ݽ��д���
                usart1_process_data(rx_buffer, rx_index - 1);
                rx_index = 0; // ��ջ�����
            }						
        }
        else // ����������
        {
            rx_index = 0; // ��ջ�����
						memset(rx_buffer, 0, UART1_BUFFER_SIZE);
        }
				HAL_UART1_Receive_IT;//������һ�ν���	
}


//����usrat.c������
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if(huart->Instance == USART1) // ������USART1���ڵĽ����ж�
//	{
//		HAL_UART1_RxCpltCallback(&huart1);
//	}
//	else if(huart->Instance == USART2) // ������USART1���ڵĽ����ж�
//	{
//		
//	}
//	else if(huart->Instance == USART3) // ������USART1���ڵĽ����ж�
//	{
//		HAL_UART3_RxCpltCallback(&huart3);
//	}
//}

//int fputc(int ch,FILE *f)
//{
//	HAL_UART_Transmit(&huart1,(uint8_t*)&(ch),1,1000);
//	
//	return (ch);
//}

