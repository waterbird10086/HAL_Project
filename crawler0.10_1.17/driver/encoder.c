#include "encoder.h"

/* USER CODE BEGIN 1 */
/**************************************************************************
�������ܣ���λʱ���ȡ������A����
��ڲ�������
����  ֵ������ֵ
**************************************************************************/
float Read_EncoderA(void)
{
	int Encoder_TIM = 0;  
	Encoder_TIM = __HAL_TIM_GET_COUNTER(&htim2);
	return Encoder_TIM;
}
/**************************************************************************
�������ܣ���λʱ���ȡ������B����
��ڲ�������
����  ֵ������ֵ
**************************************************************************/
float Read_EncoderB(void)
{
	int Encoder_TIM = 0;  
	Encoder_TIM = __HAL_TIM_GET_COUNTER(&htim4);
	return 65535 - Encoder_TIM;
}
/* USER CODE END 1 */
