//#include "timer.h"
//#include "delay.h"

///*��¼��ʱ���������*/
//u16 overcount=0;
////extern int z;
////extern int d;
////arr���Զ���װֵ��
////psc��ʱ��Ԥ��Ƶ��

//void TIM2_Int_Init(u16 arr,u16 psc)
//{
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��

//	TIM_TimeBaseStructure.TIM_Period = arr-1;              //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
//	TIM_TimeBaseStructure.TIM_Prescaler =psc-1;            //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0;         //����ʱ�ӷָ�:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
//	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);      //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
// 
//	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
//		TIM2,      //TIM2
//		TIM_IT_Update ,
//		ENABLE     //ʹ��
//		);
//	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;            //TIM3�ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;         //�����ȼ�3��
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //IRQͨ����ʹ��
//	NVIC_Init(&NVIC_InitStructure);                            //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

//	TIM_Cmd(TIM2, DISABLE);  //ʹ��TIMx����
//							 
//}

//void Hcsr06Init(void)
//{ 
//		GPIO_InitTypeDef GPIO_InitStructure;
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
//		//PC0
//    GPIO_InitStructure.GPIO_Pin =HCSR06_TRIG_1;      
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_Init(HCSR06_PORT, &GPIO_InitStructure);
//    
//		//PC1
//    GPIO_InitStructure.GPIO_Pin =   HCSR06_ECHO_1;     
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//    GPIO_Init(HCSR06_PORT, &GPIO_InitStructure);  

//}

//float Senor_Using(void)
//{
//		float length=0,sum=0;
//		u16 tim;
//		u16  i=0;
//		/*��5�����ݼ���һ��ƽ��ֵ*/
//		while(i!=5)
//		{
//		PCout(0)=1;  //�����źţ���Ϊ�����ź�
//		delay_us(20);  //�ߵ�ƽ�źų���10us
//		PCout(0)=0;
//		/*�ȴ������ź�*/
//		while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==RESET);
//		TIM_Cmd(TIM2,ENABLE);//�����źŵ�����������ʱ������

//		i+=1; //ÿ�յ�һ�λ����ź�+1���յ�5�ξͼ����ֵ
//		while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==SET);//�����ź���ʧ
//		TIM_Cmd(TIM2,DISABLE);//�رն�ʱ��

//		tim=TIM_GetCounter(TIM2);//��ȡ��TIM2���Ĵ����еļ���ֵ��һ�߼�������ź�ʱ��

//		length=(tim + overcount*1000)/58.0;//ͨ�������źż������

//		sum=length+sum;
//		TIM2->CNT=0;  //��TIM2�����Ĵ����ļ���ֵ����
//		overcount=0;  //�ж������������
//		delay_ms(100);
//		}
//		length=sum/5;
//		return length;//������Ϊ��������ֵ
//}

////5ms ��ʱ���жϷ�����

//void TIM2_IRQHandler(void)                            //TIM2�ж�
//{
//	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
//	{
//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);   //���TIMx���жϴ�����λ:TIM �ж�Դ 


////		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);	//�������жϱ�־λ
//		
//		overcount++;
//	}
//}












