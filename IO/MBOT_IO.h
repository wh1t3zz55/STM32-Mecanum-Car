#ifndef __MBOT_IO_H
#define __MBOT_IO_H
#include "stm32f10x.h"
void MBOT_IO_Init(void);
void STOP(void);
void FORDWARD(void);
void TURNLEFT(void)	;
void turnleft(void);
void TURNRIGHT(void);
void turnright(void);
void STATE(void);
void regrogress(void);
void leftmove(void);
void rightmove(void);

#endif
