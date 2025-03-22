#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "main.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;

void encoder_TIM2_Init(void);
void encoder_TIM4_Init(void);
float Read_EncoderA(void);
float Read_EncoderB(void);

#endif
