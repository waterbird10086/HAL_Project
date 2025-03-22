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

//外部中断0中断处理函数
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY1_Pin);
}

//外部中断1中断处理函数
void EXTI1_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY2_Pin);
}

//外部中断2中断处理函数
void EXTI2_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY3_Pin);
}

//外部中断3中断处理函数
void EXTI3_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY4_Pin);
}

