#include "usart1.h"

#include <stdio.h>
#include <string.h>

uint8_t rx_buffer[UART1_BUFFER_SIZE]; // 接收缓冲区
uint16_t rx_index = 0; // 接收缓冲区索引

//启动接收函数
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
    // 在这里对接收到的数据进行处理，例如打印、解析、存储等等
    // 注意：接收到的数据长度为length，不包括结束符号'\n'
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
		memset(rx_buffer, 0, UART1_BUFFER_SIZE);//将缓冲区里面的数据全部清0
}


void HAL_UART1_RxCpltCallback(UART_HandleTypeDef *huart)
{
        if (rx_index < UART1_BUFFER_SIZE - 1) // 缓冲区还有空间
        {
            if (rx_buffer[rx_index - 1] != END_CHAR) // 如果上一个字符不是结束符号
            {
                rx_buffer[rx_index++] = (uint8_t)(huart->Instance->DR & 0x00FF); // 将接收到的字符存储到缓冲区中
            }
            if(rx_buffer[rx_index - 1] == END_CHAR)// 如果上一个字符是结束符号
            {
                // 对接收到的数据进行处理
                usart1_process_data(rx_buffer, rx_index - 1);
                rx_index = 0; // 清空缓冲区
            }						
        }
        else // 缓冲区已满
        {
            rx_index = 0; // 清空缓冲区
						memset(rx_buffer, 0, UART1_BUFFER_SIZE);
        }
				HAL_UART1_Receive_IT;//启动下一次接收	
}


//放置usrat.c程序中
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if(huart->Instance == USART1) // 仅处理USART1串口的接收中断
//	{
//		HAL_UART1_RxCpltCallback(&huart1);
//	}
//	else if(huart->Instance == USART2) // 仅处理USART1串口的接收中断
//	{
//		
//	}
//	else if(huart->Instance == USART3) // 仅处理USART1串口的接收中断
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

