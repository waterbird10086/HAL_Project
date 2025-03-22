#ifndef __PWM_H__
#define __PWM_H__

#include "main.h"

void PWM_Init(void);
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle);
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle);
void PWM3_SetCH1(uint16_t Compare);
void PWM3_SetCH2(uint16_t Compare);

#endif
