#ifndef __MOTOR_H
#define __MOTOR_H

#include "main.h"

#define AIN1HIGH						HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET)
#define AIN1LOW							HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_RESET)
#define AIN2HIGH						HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_SET)
#define AIN2LOW							HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_RESET)
#define BIN1HIGH						HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_SET)
#define BIN1LOW 						HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET)
#define BIN2HIGH						HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET)
#define BIN2LOW 						HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_RESET)

#define Limit_Data 					500

void Limit(int *motorA,int *motorB );
int abs(int p);
void motor_speed(int motorA,int motorB);
void stop(void);

#endif
