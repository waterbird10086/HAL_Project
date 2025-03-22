#include "exit.h"

uint8_t SW2_val = 0;
uint8_t SW3_val = 0;
uint8_t SW4_val = 0;

void KEY_EXIT_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  SW2_CLK_ENABLE();
  SW3_CLK_ENABLE();
  SW4_CLK_ENABLE();
  
  /*Configure GPIO pins : PB1 PB4 */
  GPIO_InitStruct.Pin = SW2_Pin|SW3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA12 */
  GPIO_InitStruct.Pin = SW4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SW4_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

//�ⲿ�ж�1�жϴ�����
void EXTI1_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(SW2_Pin);
}

//�ⲿ�ж�4�жϴ�����
void EXTI4_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(SW3_Pin);
}

//�ⲿ�ж�15_10�жϴ�����
void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(SW4_Pin);
}

//�ⲿ�жϻص�����
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == SW2_Pin)
	{
		SW2_val = SW2_Read;
	}
	else if(GPIO_Pin == SW3_Pin)
	{
		SW3_val = SW3_Read;
	}
	else if(GPIO_Pin == SW4_Pin)
	{
		SW4_val = SW4_Read;
	}
}

//����SW2����ֵ
uint8_t GetSW2val(void)
{
	return SW2_val;
}

//����SW3����ֵ
uint8_t GetSW3val(void)
{
	return SW3_val;
}

//����SW4����ֵ
uint8_t GetSW4val(void)
{
	return SW4_val;
}
