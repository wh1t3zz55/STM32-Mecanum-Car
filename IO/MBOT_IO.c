#include "MBOT_IO.h"
extern int a,h,c,d,e,f,g;

void MBOT_IO_Init(void)
{
  GPIO_InitTypeDef MBOTIO;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOA,ENABLE); 

	//P5 RIN3 10;RIN4 11
	MBOTIO.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;//����
	MBOTIO.GPIO_Mode=GPIO_Mode_Out_PP;
	MBOTIO.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&MBOTIO);
	
	
	MBOTIO.GPIO_Pin=GPIO_Pin_0;
	MBOTIO.GPIO_Mode=GPIO_Mode_Out_PP;
	MBOTIO.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&MBOTIO);
		

	MBOTIO.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5;
	MBOTIO.GPIO_Mode=GPIO_Mode_Out_PP;
	MBOTIO.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&MBOTIO);
	
	MBOTIO.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_15|GPIO_Pin_7;//����
	MBOTIO.GPIO_Mode=GPIO_Mode_Out_PP;
	MBOTIO.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&MBOTIO);
	
	/*������IO*/
	
	GPIO_PinRemapConfig(GPIO_Remap_PD01,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);  //����JTAG ���� SWD
	MBOTIO.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7;
	MBOTIO.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD,&MBOTIO);
	
}
void STOP(void)
{

	//����
		TIM_SetCompare4 (TIM3,0);
		GPIO_ResetBits(GPIOD,GPIO_Pin_10);
		GPIO_ResetBits(GPIOD,GPIO_Pin_11);

			//����
		TIM_SetCompare2 (TIM3,0);
		GPIO_ResetBits(GPIOC,GPIO_Pin_5);
		GPIO_ResetBits(GPIOC,GPIO_Pin_4);
		
			//����
		TIM_SetCompare1 (TIM3,0);
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);
		GPIO_ResetBits(GPIOE,GPIO_Pin_7);
		
			//����
		TIM_SetCompare3 (TIM3,0);
		GPIO_ResetBits(GPIOE,GPIO_Pin_15);
		GPIO_ResetBits(GPIOE,GPIO_Pin_8);
}
void leftmove(void)
{
	//����
		TIM_SetCompare3 (TIM3,550);
		GPIO_SetBits(GPIOE,GPIO_Pin_8);
		GPIO_ResetBits(GPIOE,GPIO_Pin_15);
	//����
		TIM_SetCompare2 (TIM3,550);
		GPIO_SetBits(GPIOC,GPIO_Pin_5);
		GPIO_ResetBits(GPIOC,GPIO_Pin_4);
	//����
		TIM_SetCompare1 (TIM3,550);
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);
		GPIO_SetBits(GPIOE,GPIO_Pin_7);
	//����
		TIM_SetCompare4 (TIM3,550);//700
		GPIO_SetBits(GPIOD,GPIO_Pin_10);
		GPIO_ResetBits(GPIOD,GPIO_Pin_11);
	
}
void rightmove(void)
{
	//����
		TIM_SetCompare3 (TIM3,550);
		GPIO_SetBits(GPIOE,GPIO_Pin_15);
		GPIO_ResetBits(GPIOE,GPIO_Pin_8);
	//����
		TIM_SetCompare2 (TIM3,550);
		GPIO_SetBits(GPIOC,GPIO_Pin_4);
		GPIO_ResetBits(GPIOC,GPIO_Pin_5);
	//����
		TIM_SetCompare4 (TIM3,550);//700
		GPIO_SetBits(GPIOD,GPIO_Pin_11);
		GPIO_ResetBits(GPIOD,GPIO_Pin_10);
	//����
		TIM_SetCompare1 (TIM3,550);
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
		GPIO_ResetBits(GPIOE,GPIO_Pin_7);
	
}
void regrogress(void)
{
			//����
		TIM_SetCompare4 (TIM3,550);//700
		GPIO_SetBits(GPIOD,GPIO_Pin_10);
		GPIO_ResetBits(GPIOD,GPIO_Pin_11);

			//����
		TIM_SetCompare2 (TIM3,550);
		GPIO_SetBits(GPIOC,GPIO_Pin_4);
		GPIO_ResetBits(GPIOC,GPIO_Pin_5);
		
			//����
		TIM_SetCompare1 (TIM3,550);
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);
		GPIO_SetBits(GPIOE,GPIO_Pin_7);
	
			//����
		TIM_SetCompare3 (TIM3,550);
		GPIO_SetBits(GPIOE,GPIO_Pin_15);
		GPIO_ResetBits(GPIOE,GPIO_Pin_8);
	
}
void FORDWARD(void)
{
			//����
		TIM_SetCompare4 (TIM3,550);//700
		GPIO_ResetBits(GPIOD,GPIO_Pin_10);
		GPIO_SetBits(GPIOD,GPIO_Pin_11);

			//����
		TIM_SetCompare2 (TIM3,550);
		GPIO_ResetBits(GPIOC,GPIO_Pin_4);
		GPIO_SetBits(GPIOC,GPIO_Pin_5);
		
			//����
		TIM_SetCompare1 (TIM3,550);
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
		GPIO_ResetBits(GPIOE,GPIO_Pin_7);
	
			//����
		TIM_SetCompare3 (TIM3,550);
		GPIO_ResetBits(GPIOE,GPIO_Pin_15);
		GPIO_SetBits(GPIOE,GPIO_Pin_8);
}

//void FORDWARD(void)
//{
//			//����
//		TIM_SetCompare4 (TIM3,600);//700
//		GPIO_SetBits(GPIOD,GPIO_Pin_10);
//		GPIO_ResetBits(GPIOD,GPIO_Pin_11);

//			//����
//		TIM_SetCompare2 (TIM3,600);
//		GPIO_SetBits(GPIOC,GPIO_Pin_5);
//		GPIO_ResetBits(GPIOC,GPIO_Pin_4);
//		
//			//����
//		TIM_SetCompare1 (TIM3,600);
//		GPIO_SetBits(GPIOA,GPIO_Pin_0);
//		GPIO_ResetBits(GPIOE,GPIO_Pin_7);
//		
//			//����
//		TIM_SetCompare3 (TIM3,600);
//		GPIO_SetBits(GPIOE,GPIO_Pin_15);
//		GPIO_ResetBits(GPIOE,GPIO_Pin_8);
//}

void TURNLEFT(void)
{
	//����
		TIM_SetCompare4 (TIM3,400);
		GPIO_SetBits(GPIOD,GPIO_Pin_11);
		GPIO_ResetBits(GPIOD,GPIO_Pin_10);

			//����
		TIM_SetCompare2 (TIM3,500);
		GPIO_SetBits(GPIOC,GPIO_Pin_5);
		GPIO_ResetBits(GPIOC,GPIO_Pin_4);
		
			//����
		TIM_SetCompare1 (TIM3,400);
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);
		GPIO_SetBits(GPIOE,GPIO_Pin_7);
		
			//����
		TIM_SetCompare3 (TIM3,500);
		GPIO_SetBits(GPIOE,GPIO_Pin_15);
		GPIO_ResetBits(GPIOE,GPIO_Pin_8);
}


void turnleft(void)
{
			//����
		TIM_SetCompare4 (TIM3,250);
		GPIO_SetBits(GPIOD,GPIO_Pin_10);
		GPIO_ResetBits(GPIOD,GPIO_Pin_11);

			//����
		TIM_SetCompare2 (TIM3,500);
		GPIO_SetBits(GPIOC,GPIO_Pin_5);
		GPIO_ResetBits(GPIOC,GPIO_Pin_4);
		
			//����
		TIM_SetCompare1 (TIM3,250);
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
		GPIO_ResetBits(GPIOE,GPIO_Pin_7);
		
			//����
		TIM_SetCompare3 (TIM3,500);
		GPIO_SetBits(GPIOE,GPIO_Pin_15);
		GPIO_ResetBits(GPIOE,GPIO_Pin_8);
}

void TURNRIGHT(void)
{

		//����
		TIM_SetCompare4 (TIM3,500);
		GPIO_SetBits(GPIOD,GPIO_Pin_10);
		GPIO_ResetBits(GPIOD,GPIO_Pin_11);

			//����
		TIM_SetCompare2 (TIM3,400);
		GPIO_SetBits(GPIOC,GPIO_Pin_4);
		GPIO_ResetBits(GPIOC,GPIO_Pin_5);
		
			//����
		TIM_SetCompare1 (TIM3,500);
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
		GPIO_ResetBits(GPIOE,GPIO_Pin_7);
		
			//����
		TIM_SetCompare3 (TIM3,400);
		GPIO_SetBits(GPIOE,GPIO_Pin_8);
		GPIO_ResetBits(GPIOE,GPIO_Pin_15);
}
void turnright(void)
{
			//����
		TIM_SetCompare4 (TIM3,500);
		GPIO_SetBits(GPIOD,GPIO_Pin_10);
		GPIO_ResetBits(GPIOD,GPIO_Pin_11);

			//����
		TIM_SetCompare2 (TIM3,250);
		GPIO_SetBits(GPIOC,GPIO_Pin_5);
		GPIO_ResetBits(GPIOC,GPIO_Pin_4);
		
			//����
		TIM_SetCompare1 (TIM3,500);
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
		GPIO_ResetBits(GPIOE,GPIO_Pin_7);
		
			//����
		TIM_SetCompare3 (TIM3,250);
		GPIO_SetBits(GPIOE,GPIO_Pin_15);
		GPIO_ResetBits(GPIOE,GPIO_Pin_8);
}

void STATE(void)
{   
	//��1
		a	=	GPIO_ReadInputDataBit(GPIOD,  GPIO_Pin_0);
		//b =	GPIO_ReadInputDataBit(GPIOD,  GPIO_Pin_1);
		//��2
		c	=	GPIO_ReadInputDataBit(GPIOD,  GPIO_Pin_2);
	//��3
		d	=	GPIO_ReadInputDataBit(GPIOD,  GPIO_Pin_3);
	//�м�
	e	=	GPIO_ReadInputDataBit(GPIOD,  GPIO_Pin_4);
	//��3
		f	=	GPIO_ReadInputDataBit(GPIOD,  GPIO_Pin_5);
//��1
 		g	=	GPIO_ReadInputDataBit(GPIOD,  GPIO_Pin_7);



}
