/*************************************************************************************************
 * @brief   PS2接受以及数据处理
 * @version 2.0
 * @date    2021.12.24
 * @param		none
 * @retval  none
 * @author  ysl
 *************************************************************************************************/

#include "PS2.h"
#include "spi.h"

uint8_t cmd[3] = {0x01,0x42,0x00};  // 请求接受数据
uint8_t PS2data[9] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};   //存储手柄返回数据
uint16_t XY[4] = {500,500,500,500};  //摇杆模拟值
uint8_t i;
uint8_t All_But[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};  //所有按键状态值

uint8_t test[]= {0x01,0x42};
uint8_t data[] = {0x00};
extern uint8_t PS2data[];
//extern uint8_t but;
extern uint16_t XY[4];
extern uint8_t All_But[];
uint8_t i1;

uint8_t rxBuffer[10]; // 假设我们要接收10个字节

void delay_us(uint32_t udelay)    //定义hal库us级延迟
{
  uint32_t startval,tickn,delays,wait;
 
  startval = SysTick->VAL;
  tickn = HAL_GetTick();
  //sysc = 72000;  //SystemCoreClock / (1000U / uwTickFreq);
  delays =udelay * 72; //sysc / 1000 * udelay;
  if(delays > startval)
    {
      while(HAL_GetTick() == tickn)
        {
 
        }
      wait = 72000 + startval - delays;
      while(wait < SysTick->VAL)
        {
 
        }
    }
  else
    {
      wait = startval - delays;
      while(wait < SysTick->VAL && HAL_GetTick() == tickn)
        {
 
        }
    }
}

void PS2_Get(void)    //接受ps2数据
{
	short i = 0;
	
	HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,GPIO_PIN_RESET);  //拉高，开始通讯
		
	HAL_SPI_TransmitReceive(&hspi1,&cmd[0],&PS2data[0],1,0xffff); // 发送0x01，请求接受数据
	delay_us(10);
	HAL_SPI_TransmitReceive(&hspi1,&cmd[1],&PS2data[1],1,0xffff); // 发送0x42，接受0x01（PS2表示开始通信）
	delay_us(10);
	HAL_SPI_TransmitReceive(&hspi1,&cmd[2],&PS2data[2],1,0xffff); // 发送0x00，接受ID（红绿灯模式）
	delay_us(10);
	for(i = 3;i <9;i++)
	{
		HAL_SPI_TransmitReceive(&hspi1,&cmd[2],&PS2data[i],1,0xffff); // 接受数据
		delay_us(10);
		
	}
	
	HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,GPIO_PIN_SET);  //拉低，准备下次通讯
	
}


void GetData(void)  //数据处理
{
	
	PS2_Get();   //获取原始数据
	GetXY();   //将摇杆模拟值放大存储在数组里
	All_Button();
	CLear_Date();  //清空数据，以备下次使用

}

void GetXY(void)   //将摇杆模拟值放在0-1000变化，方便调试且不浪费精度
{
	int i;
	for(i = 5;i < 9;i++)
	{
		PS2data[i] =(int) PS2data[i];		
		XY[i-5] = (PS2data[i]* 1000) / 255;   //将手柄摇杆的值分到0-1000之间，不浪费模拟值精度
		if(XY[i-5] <503 && XY[i-5] > 497)  XY[i-5] = 500;   //死区
	}
	
}

void CLear_Date(void)
{
	for(i = 0;i<9;i++)
	{
		if(i == 3 || i == 4) PS2data[i] = 0xff;
		else PS2data[i] = 0x00;  //清除数据
	}
	
}

void All_Button(void)  //给每一个按键赋值，实现全按键无冲突
{
	uint8_t loc = 1;
	uint8_t set = 0;
//	uint8_t but = PS2data[3];

  for(loc = 8;loc > 0;loc--)  //位运算读取前八位
  {
		loc -= 1;
		All_But[set] = (PS2data[3]&(1<<loc))>>loc;
		loc += 1;
		set++;
  }
	for(loc = 8;loc > 0;loc--)   //位运算读取后八位
  {
		loc -= 1;
		All_But[set] = (PS2data[4]&(1<<loc))>>loc;
		loc += 1;
		set++;
  }
	for(set = 0;set < 16;set++)    //因为协议上按键按下为0，未按下为1，故需要对其进行反转
	{
		if(All_But[set] == 1)  All_But[set] = 0;
		else  All_But[set] = 1;			 
	}
}

PS2COORD COORD;
PS2MODE MODE;
uint8_t mode=1;
void PS2Data(void)
{
		GetData();
		COORD500();
//		printf("%d,%d,%d,%d\r\n",COORD.LeftX,COORD.LeftY,COORD.RightX,COORD.RightY);
		for(i1 = 0;i1 < 16;i1++)
		{
			if(All_But[i1]) 
			{
				switch(i1)
				{
					case(0): printf(" Left");break;
					case(1): printf(" Down");break;
					case(2): printf(" Right");break;
					case(3): printf(" Up");break;
					case(4): printf(" Start");break;
					
					case(5): printf(" Select");
									 break;
					case(6): printf(" Left");break;
					case(7): printf(" Select");break;
					case(8): printf(" Square");MODE.MODEFLAT = 0;break;
					case(9): printf(" Cross");MODE.MODEFLAT = 3;break;
					case(10): printf(" Circle");MODE.MODEFLAT = 2;break;
					case(11): printf(" Triangle");MODE.MODEFLAT = 1;break;
					case(12): printf(" R1");MODE.MODEFLAT = 4;break;
					case(13): printf(" L1");MODE.MODEFLAT = 5;break;
					case(14): printf(" R2");MODE.MODEFLAT = 6;break;
					case(15): printf(" L2");MODE.MODEFLAT = 7;break;			
				}
				
			}
			
		}
		mode = MODE.MODEFLAT;
		OLED_ShowString(1,1,"MODE:");
		OLED_ShowNum(1,6,mode,1);
		printf("\n");		
//		HAL_Delay(150);
}

void COORD0(void)
{
	COORD.LeftX = XY[2];
	COORD.LeftY = XY[3];
	COORD.RightX = XY[0];
	COORD.RightY = XY[1];
}

void COORD500(void)
{
	COORD.LeftX = XY[2]-500;
	COORD.LeftY = XY[3]-500;
	COORD.RightX = XY[0]-500;
	COORD.RightY = XY[1]-500;
}



