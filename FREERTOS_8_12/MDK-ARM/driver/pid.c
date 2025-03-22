#include "pid.h"

PID_InitTypedef PID;

/**
 * ������:PID_Para_Init
 * ����:PID������ʼ��
 * ����:��
 * ���:��
 */
 void PID_Param_Init(void)
 {
	 /*λ��ʽPID-���1*/
	 PID.MotorA_Velocity_Kp=10; 
	 PID.MotorA_Velocity_Ki=0.0;
	 PID.MotorA_Velocity_Kd=0.0;
	 /*λ��ʽPID-���2*/
	 PID.MotorB_Velocity_Kp=10; 
	 PID.MotorB_Velocity_Ki=0;
	 PID.MotorB_Velocity_Kd=0;
 }
 
/**
 * ������:VelocityRing_PID_MOTOR1_Realize
 * ����:���1�ٶȻ�PIDʵ��
 * ����:Velocity_Actual_Val:ʵ��ֵ
 * ���:PWM_OUT:�ٶȻ�PID���ֵ
 */
float VelocityRing_PID_MOTORA_Realize(float Velocity_Actual_Val)
{
	static float  Error,Error_Last,Integral_Error,PWM_OUT;
    //1.����ƫ��
	Error=PID.MotorA_Velocity_Target_Val-Velocity_Actual_Val;
	
	//2.������е���
	if((Error<0.5f)&&(Error>-0.5f))//ʵ������1���ӣ��۲�Ŀ����ʵ��λ�ò�Ϊ1�����ӵ��ܳ� 
	{
	 Error=0.0f;
	}
	
	//3.�ۼ�ƫ��
	Integral_Error+=Error;
	
	//4.�����޷� (�޷�ֵ��ȷ��Ϊ��PID.Velocity_Ki*�޷�ֵ����PWM������ֵ)
	Integral_Error=(Integral_Error>690)?Integral_Error=690:((Integral_Error<-690)?Integral_Error=-690:Integral_Error);
	
	//5.PID�㷨ʵ��
	PWM_OUT=PID.MotorA_Velocity_Kp*Error+PID.MotorA_Velocity_Ki*Integral_Error+PID.MotorA_Velocity_Kd*(Error-Error_Last);

  //6.������һ�����
	Error_Last=Error;

	//7.����λ�û���ǰ���ֵ
	return PWM_OUT;
}

/**
 * ������:VelocityRing_PID_MOTOR2_Realize
 * ����:���2�ٶȻ�PIDʵ��
 * ����:Velocity_Actual_Val:ʵ��ֵ
 * ���:PWM_OUT:�ٶȻ�PID���ֵ
 */
float VelocityRing_PID_MOTORB_Realize(float Velocity_Actual_Val)
{
    static float Error_Last = 0.0f;
    static float Integral_Error = 0.0f;
    float PWM_OUT;

    // 1. ����ƫ��
    float Error = PID.MotorB_Velocity_Target_Val-Velocity_Actual_Val;

    // 2. ������е���
//    if ((Error < 0.5f) && (Error > -0.5f))
//    {
//        Error = 0.0f;
//    }

    // 3. �ۼ�ƫ��
    Integral_Error += Error;

    // 4. �����޷�
    Integral_Error = (Integral_Error > MAX_INTEGRAL_ERROR) ? MAX_INTEGRAL_ERROR : ((Integral_Error < -MAX_INTEGRAL_ERROR) ? -MAX_INTEGRAL_ERROR : Integral_Error);

    // 5. PID�㷨ʵ��
    PWM_OUT = PID.MotorB_Velocity_Kp * Error + PID.MotorB_Velocity_Ki * Integral_Error + PID.MotorB_Velocity_Kd * (Error - Error_Last);

    // 6. ������һ�����
    Error_Last = Error;

    // 7. ����λ�û���ǰ���ֵ
    return PWM_OUT;
}

/**
 * ������:VelocityRing_MOTOR1_Control
 * ����:�ٶȻ����1���
 * ����:��
 * ���:�������PWM
 */

float VelocityRing_MOTORA_Control(void)
{
		float ExpectPWM = 0.0;//��ǰ����ֵ
//	  PID.Motor1_Velocity_Actual_Val=((float)Param.UnitTime_Motor1Pluse*1000.0*60.0)/(ENCODER_TOTAL_RESOLUTION*REDUCTION_RATIO*VELOCITY_PID_PERIOD);/*      	
//    ʵ���ٶ�=����λʱ����������/�ֱܷ��ʣ�11��*���ٱȣ�30��*��ʱ�����ڣ�10ms�� ��*[��λ���� ]
		PID.MotorA_Velocity_Actual_Val = speed.encoderA;
    ExpectPWM=VelocityRing_PID_MOTORA_Realize(PID.MotorA_Velocity_Actual_Val);

	  return ExpectPWM;
}

/**
 * ������:VelocityRing_MOTOR2_Control
 * ����:�ٶȻ����2���
 * ����:��
 * ���:�������PWM
 */
float VelocityRing_MOTORB_Control(void)
{
    float ExpectPWM = 0.0;//��ǰ����ֵ
	
	  PID.MotorB_Velocity_Actual_Val=speed.encoderB;
    ExpectPWM=VelocityRing_PID_MOTORB_Realize(PID.MotorB_Velocity_Actual_Val);
	
	  return ExpectPWM;
}
