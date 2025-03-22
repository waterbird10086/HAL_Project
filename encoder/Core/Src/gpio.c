/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 2 */
int32_t SpeedA = 0,SpeedB = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    int16_t zjA,zjB;
    if (htim == &htim1) //����ת��10ms
    {
        zjA = __HAL_TIM_GetCounter(&htim2);//��ȡ����ֵ
        __HAL_TIM_SetCounter(&htim2, 0);//��ռ���ֵ
        SpeedA = (float)zjA / (4 * 96) * 1000 * 60;//����ת��
			
				zjB = __HAL_TIM_GetCounter(&htim4);//��ȡ����ֵ
        __HAL_TIM_SetCounter(&htim4, 0);//��ռ���ֵ
        SpeedB = (float)zjB / (4 * 96) * 1000 * 60;//����ת��
//			printf("SpeedA: %d , SpeedB: %d\r\n" , SpeedA , SpeedB);//���ת��
    }
}
/* USER CODE END 2 */
