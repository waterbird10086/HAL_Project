#include "encoder.h"

/* USER CODE BEGIN 1 */
/**************************************************************************
函数功能：单位时间读取编码器A计数
入口参数：无
返回  值：计数值
**************************************************************************/
float Read_EncoderA(void)
{
	int Encoder_TIM = 0;  
	Encoder_TIM = __HAL_TIM_GET_COUNTER(&htim2);
	return Encoder_TIM;
}
/**************************************************************************
函数功能：单位时间读取编码器B计数
入口参数：无
返回  值：计数值
**************************************************************************/
float Read_EncoderB(void)
{
	int Encoder_TIM = 0;  
	Encoder_TIM = __HAL_TIM_GET_COUNTER(&htim4);
	return 65535 - Encoder_TIM;
}
/* USER CODE END 1 */
