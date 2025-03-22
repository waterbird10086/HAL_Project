#include "em_alg.h"

void alg_Init(void)
{
	alg_positive_operation(90,90,180);
}

void alg_positive_operation(float angleA,float angleB,float angleC)
{
	int angleA_int = (int)angleA;
  int angleB_int = (int)angleB;
  int angleC_int = (int)angleC;
	
	PCA_MG9XX(0,angleA_int);
	PCA_MG9XX(1,angleB_int);
	PCA_MG9XX(2,angleC_int);
	
	printf("%d,%d,%d\r\n",angleA_int,angleB_int,angleC_int);
}

//移动方向
int moveX;
int moveY;
int moveZ;

//舵机角度
float angleA;
float angleB;
float angleC;
//夹爪绝对坐标
float  absoluteX;
float  absoluteY;
float  absoluteZ;

#define MIN(a, b) ((a) < (b) ? (a) : (b))

float square(float n) {
  return n * n;
}

float sgn(float num)
{
    if(num > 0) {
        return 1.0;
    } else if(num < 0) {
        return -1.0;
    } else {
        return 0.0;
    }
}

// 自定义函数 degrees() 将弧度转换为角度
float degrees(float radians) {
    return radians * (180.0 / M_PI); // 使用 M_PI 表示圆周率
}

/**
 * @brief 输入绝对坐标、输出舵机角度
 * 
 * @param x 
 * @param y 
 * @param z 
 */
//void inverse_operation(float x,float y,float z){
//	x = -x;
//  angleA = -degrees(atan(z/x))*(72.0/28.0)+90.0;

//  float temp1 = degrees(atan((y-42.0-95.5)/(-sgn(x)*sqrt(x*x+z*z)-7.0-43.0)));
//	printf("temp1 = %f\n",temp1);
//  float temp2 = degrees(acos((135.0*135.0+square(-sgn(x)*sqrt(x*x+z*z)-7.0-43.0)
//								+square(y-42.0-95.5)-145.0*145.0)/(2.0*135.0*sqrt(square(-sgn(x)*sqrt(x*x+z*z)-7.0-43.0)+square(y-42.0-95.5)))));
//  printf("temp2 = %f\n",temp2);
//  angleB = 180.0-69.0-temp2-temp1+90.0;
//  // Serial.printf("angleB = %f\n",angleB);
//	
//  float temp3 = degrees(acos((145.0*145.0+135.0*135.0-square(-sgn(x)*sqrt(x*x+z*z)-43.0-7.0)-square(y-42.0-95.5))/(2.0*145.0*135.0)));
//  angleC =180.0-83.5-(180.0-69.0-temp2-temp1)+temp3;
//  // Serial.printf("angleC = %f\n",angleC);

//  printf("angle=[%f,%f,%f]\n",angleA,angleB,angleC);
//}

void inverse_operation(float x,float y,float z){
  angleA = degrees(atan(z/x))*(72.0/28.0)+90.0;

  float temp1 = degrees(atan((y-45.0-95.5)/(sgn(x)*sqrt(x*x+z*z)-7.0-30.0)));
	printf("temp1 = %f\n",temp1);
  float temp2 = degrees(acos((135.0*135.0+square(sgn(x)*sqrt(x*x+z*z)-7.0-30.0)
								+square(y-45.0-95.5)-145.0*145.0)/(2.0*135.0*sqrt(square(sgn(x)*sqrt(x*x+z*z)-7.0-30.0)+square(y-45.0-95.5)))));
  printf("temp2 = %f\n",temp2);
  angleB = 180.0-temp2-temp1+11;
  // Serial.printf("angleB = %f\n",angleB);
	
  float temp3 = degrees(acos((145.0*145.0+135.0*135.0-square(sgn(x)*sqrt(x*x+z*z)-30.0-7.0)-square(y-45.0-95.5))/(2.0*145.0*135.0)));
  angleC =180.0-83.5-(180.0-69.0-temp2-temp1+90)+temp3;
  // Serial.printf("angleC = %f\n",angleC);

  printf("angle=[%f,%f,%f]\n",angleA,angleB,angleC);
}

/**
 * @brief 判断角度是否在可到达范围内
 * 
 * @param angleA 
 * @param angleB 
 * @param angleC 
 * @return true 
 * @return false 
 */
bool check_angle(int angleA,int angleB,int angleC){
  if(angleA < 0 || angleA > 180){
    printf("angleA error %d , must in 0<a<180\n",angleA);
//				OLED_ShowString(1,10,"ANO");
    return false;
  }

  if(angleB < 80 || angleB > 180){
    printf("angleB error %d , must in 90<b<180\n",angleB);
//				OLED_ShowString(1,10,"BNO");
    return false;
  }

  float angleCMin = 140-angleB;											//140
  float angleCMax = MIN((196-angleB+90),180);				//196
  if(angleC < angleCMin || angleC > angleCMax){
    printf("angleC error %d , must in %f<c<%f\n",angleC,angleCMin,angleCMax);
				OLED_ShowString(1,10,"CNO");
    return false;
  }
  return true;
}

/**
 * @brief 设置移动坐标
 * 
 */
void alg_set_move_action(int *data){
  moveX = data[0];
  moveY = data[1];
  moveZ = data[2];
  if(moveX == 255)
    moveX = -1;
  if(moveY == 255)
    moveY = -1;
  if(moveZ == 255)
    moveZ = -1;
}

void alg_move_run(void){
//  if(moveX == 0 && moveY == 0 && moveZ == 0){
//    return;
//  }

  if(check_angle(angleA,angleB,angleC) == true){
    //TODO run
    alg_positive_operation(angleA,angleB,angleC);
//		OLED_ShowString(1,10,"AOK");
  }else{

		return;
	}
    //TODO reset
}

void alg_Yolo(int YoloX,int YoloY,int Percent)
{
	int temp_X,temp_Y;
	temp_X = YoloX;
	temp_Y = YoloY;
	if(temp_X<30)
	{
		moveZ = moveZ + 5; 
	}
	else if(temp_X>60){
		moveZ = moveZ - 5; 
	}
	if(temp_Y<40)
	{
		moveY = moveY + 5; 
	}
	else if(temp_Y>80){
		moveY = moveY - 5; 
	}
	if(Percent<20)
	{
		moveX = moveX - 5; 
	}
	else if(Percent>40){
		moveX = moveX + 5; 
	}
	inverse_operation(moveX,moveY,moveZ);
	alg_move_run();
}

//void alg_motion(void)
//{
//	
//}
