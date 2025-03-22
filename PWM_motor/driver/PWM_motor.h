#ifndef __PWM_MOTOR_H__
#define __PWM_MOTOR_H__

#include "main.h"

#define PWMA_Pin 						GPIO_PIN_8
#define PWMA_GPIO_Port 			GPIOA
#define PWMB_Pin 						GPIO_PIN_11
#define PWMB_GPIO_Port 			GPIOA

void PWM_motor_Init(void);
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle);
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle);
void PWM1_SetCH1(uint16_t Compare);
void PWM1_SetCH4(uint16_t Compare);

#endif
