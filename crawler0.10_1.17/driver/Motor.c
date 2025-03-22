#include "PWM_motor.h"
#include "Motor.h"

/*�޷�����*/
void Limit(int *motorA,int *motorB )
{
	if(*motorA>=900)*motorA=900;
	if(*motorA<=-900)*motorA=-900;
	
	if(*motorB>=900)*motorB=900;
	if(*motorB<=-900)*motorB=-900;
	
}

/*����ֵ����*/
int abs(int p)
{
	int q;
	q=p>0?p:(-p);
	return q;
}

/*��ֵ����*/
/*��ڲ�����PID������ɺ������PWMֵ*/
void motor_speed(int motorA,int motorB)
{
	if(motorA>0)   //�����ת
	{
		AIN1HIGH;
		AIN2LOW;
	}
	else if(motorA<0)  //�����ת
	{
		AIN1LOW;  //�͵�ƽ
		AIN2HIGH;  //�ߵ�ƽ
	}
	else              //���ֹͣ
	{
		AIN1LOW;  //�͵�ƽ
		AIN2LOW;  //�͵�ƽ
	}
	if(motorB>0)   //�����ת
	{
		BIN1HIGH;
		BIN2LOW;
	}
	else if(motorB<0)  //�����ת
	{
		BIN1LOW;
		BIN2HIGH;
	}
	else              //���ֹͣ
	{
		BIN1LOW;
		BIN2LOW;
	}
	
	//����PWM
	PWM1_SetCH1(abs(motorA));
	PWM1_SetCH4(abs(motorB));
}

void stop(void)
{
	PWM1_SetCH1(0);
	PWM1_SetCH4(0);
}

