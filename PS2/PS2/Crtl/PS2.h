/*************************************************************************************************
 * @brief   PS2����ͷ�ļ�
 * @version 2.0
 * @date    2021.12.24
 * @param		none
 * @retval  none
 * @author  ysl
 *************************************************************************************************/



#include "main.h"

#define PSS_Lx 2                //��ҡ��X������
#define PSS_Ly 3
#define PSS_Rx 0
#define PSS_Ry 1

/**********���а���״̬�ж�Ӧ��ֵ(���ALl_But)**********/
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


void PS2_Get(void);  //��ȡԭʼ����
void delay_us(uint32_t udelay); //��������ӳ�
void GetData(void);  //�ܺ���
void GetXY(void); //��ԭʼ������xy������ת����0-1000
void CLear_Date(void);//�������
void All_Button(void);//��ÿһ������״̬����������ȫ����״̬�洢
