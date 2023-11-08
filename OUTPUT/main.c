#include "PWM.h"
#include "delay.h"
//#include "encoder.h"
//#include "timer.h"
#include <stdio.h>
#include "MBOT_IO.h"
#include "oled.h" 
#include "usart.h"
#include "sys.h"
#include "stm32f10x_i2c.h"              // Keil::Device:StdPeriph Drivers:I2C
#include "stm32f10x.h" 
 
 
// /*串口用
//len：数据长度
//Res
//*/
u16 t,len;
u8 Res;
extern u8 res;
//void USART_GET(void);
////int leftSpeedNow  =0;
////int rightSpeedNow =0;

//char str1[20];
////char str2[20];
int a,h,c,d,e,f,g,z;
int i=0;
////超声波
//float length_1 = 0;

int main(void)
{ 

	
//	OLED_Init();//屏幕初始化
//	OLED_Clear();//OLED清屏	
//	IIC_Configuration();
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//=====设置中断分组
	MBOT_IO_Init();
//	Hcsr06Init();
	delay_init();	    	        //=====延时函数初始化                  
  PWM_GPIOInitial();
  TIM3_Initial();
  PWM_Initial();
	uart_init(9600);
//	Encoder_Init_TIM1();            //=====初始化编码器1接口
//	Encoder_Init_TIM4();            //=====初始化编码器2接口

//	TIM2_Int_Init(1000,72);     //=====定时器初始化 5ms一次中断

	while(1)
	{ 
		
				if(res=='1'){	    //前进
					FORDWARD();
					printf("Forward\n");
					}
				if(res=='2'){             //后退
					regrogress();
					printf("Regrogress\n");
				}
				if(res=='3'){         //左转
					TURNLEFT();
					printf("TurnLeft\n");
				}
				if(res=='4'){        //右转
					TURNRIGHT();
					printf("TurnRight\n");
				}
				if(res=='0'){     
					 STOP(); //停
					printf("Stop\n");
				}
				if(res=='5'){     
					 leftmove(); //左平移
					printf("leftmove\n");
				}
				if(res=='6'){     
					 rightmove(); //右平移
					printf("rightmove\n");
				}
				


	}
}


