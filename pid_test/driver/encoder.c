#include "encoder.h"


float Read_EncoderA(void)
{
	int Encoder_TIM = 0;  
	Encoder_TIM = __HAL_TIM_GET_COUNTER(&htim2);
	return Encoder_TIM;
}

float Read_EncoderB(void)
{
	int Encoder_TIM = 0;  
	Encoder_TIM = __HAL_TIM_GET_COUNTER(&htim4);
	return Encoder_TIM;
}

float Read_SPEEDA(void)
{
	int Encoder_TIM = 0,DirectionA; 
	float SPEED = 0;
	DirectionA = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim2); 
	Encoder_TIM = __HAL_TIM_GET_COUNTER(&htim2);
	if(DirectionA)
	{
		SPEED = ((float)Encoder_TIM-65535) / (500) * 100 * 60;
	}else {
		SPEED = ((float)Encoder_TIM) / (500) * 100 * 60;				//计算转速
	}
	DirectionA = 0;

	return SPEED;
}

float Read_SPEEDB(void)
{
	int Encoder_TIM = 0,DirectionB; 
	float SPEED = 0;
	DirectionB = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim4); 
	Encoder_TIM = __HAL_TIM_GET_COUNTER(&htim4);
	if(DirectionB)
	{
		SPEED = -((float)Encoder_TIM-65535) / (500) * 100 * 60;
	}
	else {
		SPEED = (-(float)Encoder_TIM) / (500) * 100 * 60;				//计算转速
	}
	DirectionB = 0;

	return SPEED;
}

