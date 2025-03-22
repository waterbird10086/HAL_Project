#include "PWM_motor.h"
#include "Motor.h"

/*限幅函数*/
void Limit(int *motorA,int *motorB )
{
	if(*motorA>=Limit_Data)*motorA=Limit_Data;
	if(*motorA<=-Limit_Data)*motorA=-Limit_Data;
	
	if(*motorB>=Limit_Data)*motorB=Limit_Data;
	if(*motorB<=-Limit_Data)*motorB=-Limit_Data;
	
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
	Limit(&motorA,&motorB);
	PWM8_SetCH1(abs(motorA));
	PWM8_SetCH2(abs(motorB));
}

void stop(void)
{
	PWM8_SetCH1(0);
	PWM8_SetCH2(0);
}


#define MAX_ACCEL_CHANGE 30
#define MAX_DIREC_CHANGE 30
#define DELAY_TIME 100

int current_accel = 0;
int current_direc = 0;
int speed_step = 0;

void step_run(void)
{
	if(MODE.MODEFLAT == 6)
	{
		speed_step = 1;
	}
	if(MODE.MODEFLAT == 7)
	{
		speed_step = 2;
	}
    int target_accel = COORD.LeftY / speed_step;
    int target_direc = COORD.RightX / 5;

    // 平滑过渡加速度
    if (target_accel > current_accel)
    {
        current_accel = (target_accel - current_accel > MAX_ACCEL_CHANGE) ? current_accel + MAX_ACCEL_CHANGE : target_accel;
    }
    else
    {
        current_accel = (current_accel - target_accel > MAX_ACCEL_CHANGE) ? current_accel - MAX_ACCEL_CHANGE : target_accel;
    }

    // 平滑过渡方向
    if (target_direc > current_direc)
    {
        current_direc = (target_direc - current_direc > MAX_DIREC_CHANGE) ? current_direc + MAX_DIREC_CHANGE : target_direc;
    }
    else
    {
        current_direc = (current_direc - target_direc > MAX_DIREC_CHANGE) ? current_direc - MAX_DIREC_CHANGE : target_direc;
    }

    // 使用PID控制器调整目标速度
    PID.MotorA_Velocity_Target_Val = -current_accel + current_direc;
    PID.MotorB_Velocity_Target_Val = -current_accel - current_direc;
		
		OLED_ShowSignedNum(2,4,PID.MotorA_Velocity_Target_Val,4);
		OLED_ShowSignedNum(2,12,PID.MotorB_Velocity_Target_Val,4);

    HAL_Delay(DELAY_TIME);
}

