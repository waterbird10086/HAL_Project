#include "JAY31.h"

uint8_t RX_dat=0;//接收变量

void JAY31_Init()
{
	HAL_UART_Receive_IT(&huart3,&RX_dat,1);//启动接收函数
}

//回调函数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == USART3)
  {
    if(RX_dat==0xa1)
    {
			LED1_ON;
			HAL_UART_Receive_IT(&huart3,&RX_dat,1);//启动接收函数
    }
    else if(RX_dat==0xa2)
    {
			LED1_OFF;
			HAL_UART_Receive_IT(&huart3,&RX_dat,1);//启动接收函数
    }
  }
}
