#ifndef __PS2_H__
#define __PS2_H__

/*************************************************************************************************
 * @brief   PS2控制头文件
 * @version 2.0
 * @date    2021.12.24
 * @param		none
 * @retval  none
 * @author  ysl
 *************************************************************************************************/

#include "main.h"

#define PSS_Lx 2                //右摇杆X轴数据
#define PSS_Ly 3
#define PSS_Rx 0
#define PSS_Ry 1

/**********所有按键状态中对应数值(针对ALl_But)**********/
#define PSB_Left        0
#define PSB_Down        1
#define PSB_Right       2
#define PSB_Up          3
#define PSB_Start       4
#define PSB_Select      7
#define PSB_Square      8
#define PSB_Cross       9
#define PSB_Circle      10
#define PSB_Triangle    11
#define PSB_R1          12
#define PSB_L1          13
#define PSB_R2          14
#define PSB_L2          15

typedef struct
{
	int32_t LeftX;
  int32_t LeftY;
  int32_t RightX;
  int32_t RightY;
} PS2COORD;
extern PS2COORD COORD;

typedef struct
{
	uint32_t MODE0;
  uint32_t MODE1;
  uint32_t MODE2;
  uint32_t MODE3;
	uint32_t MODEFLAT;
} PS2MODE;
extern PS2MODE MODE;

void PS2_Get(void);  //获取原始数据
void delay_us(uint32_t udelay); //定义毫秒延迟
void GetData(void);  //总函数
void GetXY(void); //将原始数据中xy轴数据转换到0-1000
void CLear_Date(void);//清除数据
void All_Button(void);//将每一个按键状态单独分析，全按键状态存储
void PS2Data(void);
void COORD0(void);
void COORD500(void);

#endif
