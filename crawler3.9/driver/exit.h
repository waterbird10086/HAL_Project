#ifndef __EXIT_H__
#define __EXIT_H__

#include "main.h"

#define KEY1__4_CLK_ENABLE()		__HAL_RCC_GPIOC_CLK_ENABLE()

#define KEY1_Read 			HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)
#define KEY2_Read 			HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)
#define KEY3_Read 			HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)
#define KEY4_Read 			HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)

typedef struct
{
	uint32_t KEY1_val;
  uint32_t KEY2_val;
  uint32_t KEY3_val;
  uint32_t KEY4_val;
} KEY;

extern KEY KEY_t;

void KEY_EXIT_Init(void);
uint8_t GetKEY1val(void);
uint8_t GetKEY2val(void);
uint8_t GetKEY3val(void);
uint8_t GetKEY4val(void);

#endif
