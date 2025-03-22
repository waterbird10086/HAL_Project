#ifndef __LED_H__
#define __LED_H__

#include "main.h"

void LED_Init(void);

#define LED1_CLK_ENABLE() 	__HAL_RCC_GPIOC_CLK_ENABLE()

#define LED1_Pin 			GPIO_PIN_13
#define LED1_GPIO_Port 		GPIOC

#define LED1_ON 			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET)

#define LED1_OFF 			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET)

#endif
