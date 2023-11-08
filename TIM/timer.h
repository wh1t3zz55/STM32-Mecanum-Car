#ifndef __TIMER_H
#define __TIMER_H
#include "stm32f10x.h"
 #include "MBOT_IO.h"

#include "sys.h"


	//超声波硬件接口定义
#define HCSR06_PORT     GPIOC
#define HCSR06_CLK      RCC_APB2Periph_TIM2


#define HCSR06_TRIG_1     GPIO_Pin_0//PCO
#define HCSR06_ECHO_1     GPIO_Pin_1//PC1

void Hcsr06Init(void);
float Senor_Using(void);









void TIM2_Int_Init(u16 arr,u16 psc); 

#endif
