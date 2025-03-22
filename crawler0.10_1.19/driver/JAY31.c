#include "JAY31.h"

#include <stdio.h>
#include <string.h>

uint8_t uart3_rx_buffer[UART3_BUFFER_SIZE]; // 接收缓冲区
uint16_t uart3_rx_index = 0; // 接收缓冲区索引

void JAY31_Init()
{
	HAL_UART3_Receive_IT;//启动接收函数
}

void usart3_process_data(uint8_t *data, uint16_t length)
{
    // 在这里对接收到的数据进行处理，例如打印、解析、存储等等
    // 注意：接收到的数据长度为length，不包括结束符号'\n'
		if(strstr((char*)data, "LED ON1"))
		{
			OLED_ShowString(1,6,"LED1 ON");
		}
		else if(strstr((char*)data, "LED1"))
		{
			OLED_ShowString(1,6,"LED1");			
		}

		memset(uart3_rx_buffer, 0, UART3_BUFFER_SIZE);//将缓冲区里面的数据全部清0
}


void HAL_UART3_RxCpltCallback(UART_HandleTypeDef *huart)
{
        if (uart3_rx_index < UART3_BUFFER_SIZE - 1) // 缓冲区还有空间
        {
            if (uart3_rx_buffer[uart3_rx_index - 1] != END_CHAR3) // 如果上一个字符不是结束符号
            {
                uart3_rx_buffer[uart3_rx_index++] = (uint8_t)(huart->Instance->DR & 0x00FF); // 将接收到的字符存储到缓冲区中
            }
            if(uart3_rx_buffer[uart3_rx_index - 1] == END_CHAR3)// 如果上一个字符是结束符号
            {
                // 对接收到的数据进行处理
                usart3_process_data(uart3_rx_buffer, uart3_rx_index - 1);
                uart3_rx_index = 0; // 清空缓冲区
            }						
        }
        else // 缓冲区已满
        {
            uart3_rx_index = 0; // 清空缓冲区
						memset(uart3_rx_buffer, 0, UART3_BUFFER_SIZE);
        }
				HAL_UART3_Receive_IT;//启动下一次接收	
}


////回调函数
//void HAL_UART3_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//			OLED_ShowHexNum(1,6,RX_dat,2);
//			HAL_UART_Receive_IT(&huart3,&RX_dat,1);//启动接收函数
//}
