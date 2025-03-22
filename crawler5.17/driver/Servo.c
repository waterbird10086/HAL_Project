#include "Servo.h"

/**TIM3 GPIO Configuration
PA6     ------> TIM3_CH1
PA7     ------> TIM3_CH2
PB0     ------> TIM3_CH3
*/
//Õ¼¿Õ±È=Compare(CCR)/ARR(100),ÆµÂÊf=72M/ARR/PSC=72M/1000/72=0.1ms
void PWM3_SetCH1(uint16_t Compare31)										
{
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	TIM3 -> CCR1 = Compare31;
}

void PWM3_SetCH2(uint16_t Compare32)										
{
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
	TIM3 -> CCR2 = Compare32;
}

void PWM3_SetCH3(uint16_t Compare33)										
{
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
	TIM3 -> CCR3 = Compare33;
}

void PWM3_SetCH4(uint16_t Compare34)										
{
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
	TIM3 -> CCR4 = Compare34;
}

void Servo1_SetAngle(float Angle1)
{
	PWM3_SetCH1(Angle1 / 180 * 200 + 50);
}

void Servo2_SetAngle(float Angle2)
{
	PWM3_SetCH2(Angle2 / 180 * 200 + 50);
}

void Servo3_SetAngle(float Angle3)
{
	PWM3_SetCH3(Angle3 / 180 * 200 + 50);
}

void Servo4_SetAngle(float Angle1)
{
	PWM3_SetCH4(Angle1 / 180 * 200 + 50);
}

int Angle_A,Angle_B,Angle_C;
void PS2Servo(void)
{
	Angle_A=90+COORD.RightX*0.18;
	if(Angle_A>=180)Angle_A=180;
	if(Angle_A<=0)Angle_A=0;
	PCA_MG9XX(0,Angle_A);

	Angle_B=COORD.RightY*0.06+90;
	if(Angle_B>=120)Angle_B=120;
	if(Angle_B<=90)Angle_B=90;
	PCA_MG9XX(1,Angle_B);

	Angle_C=COORD.LeftY*0.2+180;
	if(Angle_C>=180)Angle_C=180;
	if(Angle_C<=140)Angle_C=140;
	PCA_MG9XX(2,Angle_C);
}

