#include "PWM.h"

void PWM_GPIOInitial(void)
{
	GPIO_InitTypeDef gpioconfig;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
	gpioconfig.GPIO_Mode=GPIO_Mode_AF_PP;
	gpioconfig.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6;
	gpioconfig.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&gpioconfig);
}

void TIM3_Initial(void)
{
	TIM_TimeBaseInitTypeDef tim3;
	tim3.TIM_Period = 999;
	tim3.TIM_Prescaler = 719;
	tim3.TIM_ClockDivision = 0;
	tim3.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&tim3);
	TIM_Cmd(TIM3,ENABLE);
}	

void PWM_Initial(void)
{
	TIM_OCInitTypeDef pwmoftim3;
	pwmoftim3.TIM_OCMode = TIM_OCMode_PWM2;
	pwmoftim3.TIM_OCNPolarity = TIM_OCPolarity_High;
	pwmoftim3.TIM_OutputState = TIM_OutputState_Enable;
	pwmoftim3.TIM_Pulse = 600;
	TIM_OC4Init(TIM3,&pwmoftim3);
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);

	pwmoftim3.TIM_OutputState = TIM_OutputState_Enable;
	pwmoftim3.TIM_Pulse = 600;
	TIM_OC3Init(TIM3,&pwmoftim3);
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	pwmoftim3.TIM_OutputState = TIM_OutputState_Enable;
	pwmoftim3.TIM_Pulse = 600;
	TIM_OC2Init(TIM3,&pwmoftim3);
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	pwmoftim3.TIM_OutputState = TIM_OutputState_Enable;
	pwmoftim3.TIM_Pulse = 600;
	TIM_OC1Init(TIM3,&pwmoftim3);
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	TIM_Cmd (TIM3,ENABLE);
}
