#ifndef __ENCODER_H
#define __ENCODER_H
#include "sys.h"
#include "stm32f10x.h" 

#define ENCODER_TIM_PERIOD (u16)(65535)   //不可大于65535 因为F103的定时器是16位的。

void Encoder_Init_TIM1(void);
void Encoder_Init_TIM4(void);
int Read_Encoder(u8 TIMX);
//s16 getTIMx_DetaCnt(TIM_TypeDef * TIMx);
//void Get_Motor_Speed(int *leftSpeed,int *rightSpeed);

#endif
