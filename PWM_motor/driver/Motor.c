#include "PWM_motor.h"
#include "Motor.h"

void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, BIN2_Pin|BIN1_Pin|AIN1_Pin|AIN2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = BIN2_Pin|BIN1_Pin|AIN1_Pin|AIN2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	PWM_motor_Init();
}

/*�޷�����*/
void Limit(int *motorA,int *motorB )
{
	if(*motorA>=900)*motorA=900;
	if(*motorA<=-900)*motorA=-900;
	
	if(*motorB>=900)*motorB=900;
	if(*motorB<=-900)*motorB=-900;
	
}

/*����ֵ����*/
int abs(int p)
{
	int q;
	q=p>0?p:(-p);
	return q;
}

/*��ֵ����*/
/*��ڲ�����PID������ɺ������PWMֵ*/
void motor_speed(int motorA,int motorB)
{
	if(motorA>0)   //�����ת
	{
		AIN1HIGH;
		AIN2LOW;
	}
	else if(motorA<0)  //�����ת
	{
		AIN1LOW;  //�͵�ƽ
		AIN2HIGH;  //�ߵ�ƽ
	}
	else              //���ֹͣ
	{
		AIN1LOW;  //�͵�ƽ
		AIN2LOW;  //�͵�ƽ
	}
	if(motorB>0)   //�����ת
	{
		BIN1HIGH;
		BIN2LOW;
	}
	else if(motorB<0)  //�����ת
	{
		BIN1LOW;
		BIN2HIGH;
	}
	else              //���ֹͣ
	{
		BIN1LOW;
		BIN2LOW;
	}
	
	//����PWM
	PWM1_SetCH1(abs(motorA));
	PWM1_SetCH4(abs(motorB));
}

void stop(void)
{
	PWM1_SetCH1(0);
	PWM1_SetCH4(0);
}

