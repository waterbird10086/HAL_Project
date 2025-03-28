#include "pid.h"

PID_InitTypedef PID;

/**
 * 函数名:PID_Para_Init
 * 描述:PID参数初始化
 * 输入:无
 * 输出:无
 */
 void PID_Param_Init(void)
 {
	 /*位置式PID-电机1*/
	 PID.MotorA_Velocity_Kp=0.0; 
	 PID.MotorA_Velocity_Ki=0.0;
	 PID.MotorA_Velocity_Kd=0.0;
	 /*位置式PID-电机2*/
	 PID.MotorB_Velocity_Kp=10.0; 
	 PID.MotorB_Velocity_Ki=0.0;
	 PID.MotorB_Velocity_Kd=0.0;
 }
 
/**
 * 函数名:VelocityRing_PID_MOTOR1_Realize
 * 描述:电机1速度环PID实现
 * 输入:Velocity_Actual_Val:实际值
 * 输出:PWM_OUT:速度环PID输出值
 */
float VelocityRing_PID_MOTORA_Realize(float Velocity_Actual_Val)
{
	static float  Error,Error_Last,Integral_Error,PWM_OUT;
    //1.计算偏差
	Error=PID.MotorA_Velocity_Target_Val-Velocity_Actual_Val;
	
	//2.消除机械误差
	if((Error<0.5f)&&(Error>-0.5f))//实际运行1分钟，观察目标与实际位置差为1个轮子的周长 
	{
	 Error=0.0f;
	}
	
	//3.累计偏差
	Integral_Error+=Error;
	
	//4.积分限幅 (限幅值的确定为：PID.Velocity_Ki*限幅值等于PWM输出最大值)
	Integral_Error=(Integral_Error>690)?Integral_Error=690:((Integral_Error<-690)?Integral_Error=-690:Integral_Error);
	
	//5.PID算法实现
	PWM_OUT=PID.MotorA_Velocity_Kp*Error+PID.MotorA_Velocity_Ki*Integral_Error+PID.MotorA_Velocity_Kd*(Error-Error_Last);

  //6.更新上一次误差
	Error_Last=Error;

	//7.返回位置环当前输出值
	return PWM_OUT;
}

/**
 * 函数名:VelocityRing_PID_MOTOR2_Realize
 * 描述:电机2速度环PID实现
 * 输入:Velocity_Actual_Val:实际值
 * 输出:PWM_OUT:速度环PID输出值
 */
float VelocityRing_PID_MOTORB_Realize(float Velocity_Actual_Val)
{
    static float Error_Last = 0.0f;
    static float Integral_Error = 0.0f;
    float PWM_OUT;

    // 1. 计算偏差
    float Error = PID.MotorB_Velocity_Target_Val - Velocity_Actual_Val;

    // 2. 消除机械误差
//    if ((Error < 0.5f) && (Error > -0.5f))
//    {
//        Error = 0.0f;
//    }

    // 3. 累计偏差
    Integral_Error += Error;

//    // 4. 积分限幅
//    Integral_Error = (Integral_Error > MAX_INTEGRAL_ERROR) ? MAX_INTEGRAL_ERROR : ((Integral_Error < -MAX_INTEGRAL_ERROR) ? -MAX_INTEGRAL_ERROR : Integral_Error);

    // 5. PID算法实现
    PWM_OUT = PID.MotorB_Velocity_Kp * Error + PID.MotorB_Velocity_Ki * Integral_Error + PID.MotorB_Velocity_Kd * (Error - Error_Last);

    // 6. 更新上一次误差
    Error_Last = Error;

    // 7. 返回位置环当前输出值
    return PWM_OUT;
}

/**
 * 函数名:VelocityRing_MOTOR1_Control
 * 描述:速度环电机1输出
 * 输入:无
 * 输出:输出期望PWM
 */

float VelocityRing_MOTORA_Control(void)
{
    
	float ExpectPWM = 0.0;//当前控制值
//	  PID.Motor1_Velocity_Actual_Val=((float)Param.UnitTime_Motor1Pluse*1000.0*60.0)/(ENCODER_TOTAL_RESOLUTION*REDUCTION_RATIO*VELOCITY_PID_PERIOD);/*      	
//    实际速度=（单位时间电机脉冲数/总分辨率（11）*减速比（30）*定时器周期（10ms） ）*[单位换算 ]
		PID.MotorA_Velocity_Actual_Val=(float)encoder1.encoderA/ (500) * 1000 * 60;	
    ExpectPWM=VelocityRing_PID_MOTORA_Realize(PID.MotorA_Velocity_Actual_Val);

	  return ExpectPWM;
}

/**
 * 函数名:VelocityRing_MOTOR2_Control
 * 描述:速度环电机2输出
 * 输入:无
 * 输出:输出期望PWM
 */
float VelocityRing_MOTORB_Control(void)
{
    float ExpectPWM = 0.0;//当前控制值
	
	  PID.MotorB_Velocity_Actual_Val=(float)encoder1.encoderB/ (500) * 1000 * 60;
    ExpectPWM=VelocityRing_PID_MOTORB_Realize(PID.MotorB_Velocity_Actual_Val);
	
	  return ExpectPWM;
}
