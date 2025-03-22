#ifndef __SERVO_H__
#define __SERVO_H__

#include "main.h"
#include "PWM.h"

void Servo_Init(void);
void Servo1_SetAngle(float Angle1);
void Servo2_SetAngle(float Angle2);
void Servo3_SetAngle(float Angle3);

#endif
