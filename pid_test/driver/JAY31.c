#include "JAY31.h"

#include <stdio.h>
#include <string.h>

uint8_t uart3_rx_buffer[UART3_BUFFER_SIZE]; // ���ջ�����
uint16_t uart3_rx_index = 0; // ���ջ���������

void JAY31_Init()
{
	HAL_UART3_Receive_IT;//�������պ���
}

void usart3_process_data(uint8_t *data, uint16_t length)
{
    // ������Խ��յ������ݽ��д��������ӡ���������洢�ȵ�
    // ע�⣺���յ������ݳ���Ϊlength����������������'\n'
		if(strstr((char*)data, "LED ON1"))
		{
			OLED_ShowString(1,6,"LED1 ON");
		}
		else if(strstr((char*)data, "LED1"))
		{
			OLED_ShowString(1,6,"LED1");			
		}

		memset(uart3_rx_buffer, 0, UART3_BUFFER_SIZE);//�����������������ȫ����0
}


void HAL_UART3_RxCpltCallback(UART_HandleTypeDef *huart)
{
        if (uart3_rx_index < UART3_BUFFER_SIZE - 1) // ���������пռ�
        {
            if (uart3_rx_buffer[uart3_rx_index - 1] != END_CHAR3) // �����һ���ַ����ǽ�������
            {
                uart3_rx_buffer[uart3_rx_index++] = (uint8_t)(huart->Instance->DR & 0x00FF); // �����յ����ַ��洢����������
            }
            if(uart3_rx_buffer[uart3_rx_index - 1] == END_CHAR3)// �����һ���ַ��ǽ�������
            {
                // �Խ��յ������ݽ��д���
                usart3_process_data(uart3_rx_buffer, uart3_rx_index - 1);
                uart3_rx_index = 0; // ��ջ�����
            }						
        }
        else // ����������
        {
            uart3_rx_index = 0; // ��ջ�����
						memset(uart3_rx_buffer, 0, UART3_BUFFER_SIZE);
        }
				HAL_UART3_Receive_IT;//������һ�ν���	
}


////�ص�����
//void HAL_UART3_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//			OLED_ShowHexNum(1,6,RX_dat,2);
//			HAL_UART_Receive_IT(&huart3,&RX_dat,1);//�������պ���
//}
