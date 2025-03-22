#ifndef __EM_ALG_H__
#define __EM_ALG_H__

#include <math.h>
#include "main.h"

#define M_PI 3.14

void alg_Init(void);

void alg_positive_operation(float angleA,float angleB,float angleC);

void inverse_operation(float x,float y,float z);

void alg_set_move_action(int *data);

void alg_move_run(void);

void alg_Yolo(int YoloX,int YoloY,int Percent);

#endif
