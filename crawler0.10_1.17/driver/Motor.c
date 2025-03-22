#include "PWM_motor.h"
#include "Motor.h"

/*限幅函数*/
void Limit(int *motorA,int *motorB )
{
	if(*motorA>=900)*motorA=900;
	if(*motorA<=-900)*motorA=-900;
	
	if(*motorB>=900)*motorB=900;
	if(*motorB<=-900)*motorB=-900;
	
}

/*绝对值函数*/
int abs(int p)
{
	int q;
	q=p>0?p:(-p);
	return q;
}

/*赋值函数*/
/*入口参数：PID运算完成后的最终PWM值*/
void motor_speed(int motorA,int motorB)
{
	if(motorA>0)   //电机正转
	{
		AIN1HIGH;
		AIN2LOW;
	}
	else if(motorA<0)  //电机反转
	{
		AIN1LOW;  //低电平
		AIN2HIGH;  //高电平
	}
	else              //电机停止
	{
		AIN1LOW;  //低电平
		AIN2LOW;  //低电平
	}
	if(motorB>0)   //电机正转
	{
		BIN1HIGH;
		BIN2LOW;
	}
	else if(motorB<0)  //电机反转
	{
		BIN1LOW;
		BIN2HIGH;
	}
	else              //电机停止
	{
		BIN1LOW;
		BIN2LOW;
	}
	
	//设置PWM
	PWM1_SetCH1(abs(motorA));
	PWM1_SetCH4(abs(motorB));
}

void stop(void)
{
	PWM1_SetCH1(0);
	PWM1_SetCH4(0);
}

