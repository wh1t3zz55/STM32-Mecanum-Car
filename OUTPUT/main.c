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
 
 
// /*������
//len�����ݳ���
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
////������
//float length_1 = 0;

int main(void)
{ 

	
//	OLED_Init();//��Ļ��ʼ��
//	OLED_Clear();//OLED����	
//	IIC_Configuration();
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//=====�����жϷ���
	MBOT_IO_Init();
//	Hcsr06Init();
	delay_init();	    	        //=====��ʱ������ʼ��                  
  PWM_GPIOInitial();
  TIM3_Initial();
  PWM_Initial();
	uart_init(9600);
//	Encoder_Init_TIM1();            //=====��ʼ��������1�ӿ�
//	Encoder_Init_TIM4();            //=====��ʼ��������2�ӿ�

//	TIM2_Int_Init(1000,72);     //=====��ʱ����ʼ�� 5msһ���ж�

	while(1)
	{ 
		
				if(res=='1'){	    //ǰ��
					FORDWARD();
					printf("Forward\n");
					}
				if(res=='2'){             //����
					regrogress();
					printf("Regrogress\n");
				}
				if(res=='3'){         //��ת
					TURNLEFT();
					printf("TurnLeft\n");
				}
				if(res=='4'){        //��ת
					TURNRIGHT();
					printf("TurnRight\n");
				}
				if(res=='0'){     
					 STOP(); //ͣ
					printf("Stop\n");
				}
				if(res=='5'){     
					 leftmove(); //��ƽ��
					printf("leftmove\n");
				}
				if(res=='6'){     
					 rightmove(); //��ƽ��
					printf("rightmove\n");
				}
				


	}
}


