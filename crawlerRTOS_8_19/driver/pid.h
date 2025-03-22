#ifndef __PID_H 
#define	__PID_H

#include "main.h"
#include "gpio.h"

#define MAX_INTEGRAL_ERROR 200

typedef struct
{
	float MotorA_Velocity_Kp;//�ٶȻ�Kp
	float MotorA_Velocity_Ki;//�ٶȻ�Ki
	float MotorA_Velocity_Kd;//�ٶȻ�Kd
	float MotorA_Velocity_Target_Val;//����ֵ
	float MotorA_Velocity_Actual_Val;//ʵ��ֵ
	int MotorA_Velocity_Out;//�ٶȻ��������
	
	float MotorB_Velocity_Kp;//�ٶȻ�Kp
	float MotorB_Velocity_Ki;//�ٶȻ�Ki
	float MotorB_Velocity_Kd;//�ٶȻ�Kd
	float MotorB_Velocity_Target_Val;//����ֵ
	float MotorB_Velocity_Actual_Val;//ʵ��ֵ
	int MotorB_Velocity_Out;//�ٶȻ��������
}PID_InitTypedef;

extern PID_InitTypedef PID;
extern void   PID_Param_Init(void);
extern float  VelocityRing_PID_MOTORA_Realize(float Velocity_Actual_Val);
extern float  VelocityRing_PID_MOTORB_Realize(float Velocity_Actual_Val);
extern float  VelocityRing_MOTORA_Control(void);
extern float  VelocityRing_MOTORB_Control(void);
















#endif
