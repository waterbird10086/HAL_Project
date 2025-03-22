#include "exit.h"

void KEY_EXIT_Init(void)
{
//  GPIO_InitTypeDef GPIO_InitStruct = {0};

//  /* GPIO Ports Clock Enable */
//	KEY1__4_CLK_ENABLE();
//  
//  GPIO_InitStruct.Pin = KEY1_Pin|KEY2_Pin|KEY3_Pin|KEY4_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
//  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);
	
	HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);
}

//�ⲿ�ж�0�жϴ�����
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY1_Pin);
}

//�ⲿ�ж�1�жϴ�����
void EXTI1_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY2_Pin);
}

//�ⲿ�ж�2�жϴ�����
void EXTI2_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY3_Pin);
}

//�ⲿ�ж�3�жϴ�����
void EXTI3_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY4_Pin);
}

