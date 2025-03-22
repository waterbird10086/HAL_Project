#include "PWM_motor.h"

/**TIM1 GPIO Configuration
PC6     ------> TIM8_CH1
PC7     ------> TIM8_CH2
*/
//Õ¼¿Õ±È=Compare(CCR)/ARR(1000),ÆµÂÊf=72M/ARR/PSC=72M/1000/72=0.1ms
void PWM8_SetCH1(uint16_t Compare)										
{
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);
	TIM8 -> CCR1 = Compare;
}

void PWM8_SetCH2(uint16_t Compare)										
{
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
	TIM8 -> CCR2 = Compare;
}
