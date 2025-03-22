#include "Servo.h"

void Servo_Init(void)
{
	PWM_Init();
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
