#ifndef __EXIT_H__
#define __EXIT_H__

#include "main.h"

#define SW2_CLK_ENABLE() 	__HAL_RCC_GPIOB_CLK_ENABLE()
#define SW3_CLK_ENABLE() 	__HAL_RCC_GPIOB_CLK_ENABLE()
#define SW4_CLK_ENABLE() 	__HAL_RCC_GPIOA_CLK_ENABLE()

#define SW2_Pin 			GPIO_PIN_1
#define SW2_GPIO_Port 		GPIOB
#define SW3_Pin 			GPIO_PIN_4
#define SW3_GPIO_Port 		GPIOB
#define SW4_Pin 			GPIO_PIN_12
#define SW4_GPIO_Port 		GPIOA

#define SW2_Read 			HAL_GPIO_ReadPin(SW2_GPIO_Port,SW2_Pin)
#define SW3_Read 			HAL_GPIO_ReadPin(SW3_GPIO_Port,SW3_Pin)
#define SW4_Read 			HAL_GPIO_ReadPin(SW4_GPIO_Port,SW4_Pin)

typedef struct
{
  uint32_t SW2_val;
  uint32_t SW3_val;
  uint32_t SW4_val;
} SW;

void KEY_EXIT_Init(void);
uint8_t GetSW2val(void);
uint8_t GetSW3val(void);
uint8_t GetSW4val(void);

#endif
