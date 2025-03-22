#ifndef __MOTOR_H
#define __MOTOR_H

#include "main.h"

#define BIN2_Pin 						GPIO_PIN_12
#define BIN2_GPIO_Port 			GPIOB
#define BIN1_Pin 						GPIO_PIN_13
#define BIN1_GPIO_Port 			GPIOB
#define AIN1_Pin 						GPIO_PIN_14
#define AIN1_GPIO_Port 			GPIOB
#define AIN2_Pin 						GPIO_PIN_15
#define AIN2_GPIO_Port 			GPIOB

#define AIN1HIGH						HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET)
#define AIN1LOW							HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_RESET)
#define AIN2HIGH						HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_SET)
#define AIN2LOW							HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_RESET)
#define BIN1HIGH						HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_SET)
#define BIN1LOW 						HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET)
#define BIN2HIGH						HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET)
#define BIN2LOW 						HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_RESET)


void Motor_Init(void);
void Limit(int *motorA,int *motorB );
int abs(int p);
void motor_speed(int motorA,int motorB);
void stop(void);

#endif
