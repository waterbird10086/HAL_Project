#include "PWM_motor.h"

/**TIM1 GPIO Configuration
PA8     ------> TIM1_CH1
PA11     ------> TIM1_CH4
*/
//Õ¼¿Õ±È=Compare(CCR)/ARR(1000),ÆµÂÊf=72M/ARR/PSC=72M/1000/72=0.1ms
void PWM1_SetCH1(uint16_t Compare)										
{
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	TIM1 -> CCR1 = Compare;
}

void PWM1_SetCH4(uint16_t Compare)										
{
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
	TIM1 -> CCR4 = Compare;
}
