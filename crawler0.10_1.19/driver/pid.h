#ifndef __PID_H 
#define	__PID_H

#include "main.h"
#include "gpio.h"

#define MAX_INTEGRAL_ERROR 200

typedef struct
{
	float MotorA_Velocity_Kp;//速度环Kp
	float MotorA_Velocity_Ki;//速度环Ki
	float MotorA_Velocity_Kd;//速度环Kd
	float MotorA_Velocity_Target_Val;//期望值
	float MotorA_Velocity_Actual_Val;//实际值
	int MotorA_Velocity_Out;//速度环输出变量
	
	float MotorB_Velocity_Kp;//速度环Kp
	float MotorB_Velocity_Ki;//速度环Ki
	float MotorB_Velocity_Kd;//速度环Kd
	float MotorB_Velocity_Target_Val;//期望值
	float MotorB_Velocity_Actual_Val;//实际值
	int MotorB_Velocity_Out;//速度环输出变量
}PID_InitTypedef;

extern PID_InitTypedef PID;
extern void   PID_Param_Init(void);
extern float  VelocityRing_PID_MOTORA_Realize(float Velocity_Actual_Val);
extern float  VelocityRing_PID_MOTORB_Realize(float Velocity_Actual_Val);
extern float  VelocityRing_MOTORA_Control(void);
extern float  VelocityRing_MOTORB_Control(void);
















#endif
