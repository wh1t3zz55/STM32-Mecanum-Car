//#include "encoder.h"

///**************************************************************************
//�������ܣ���TIM1��ʼ��Ϊ�������ӿ�ģʽ
//��ڲ�������
//����  ֵ����
//**************************************************************************/
//void Encoder_Init_TIM1(void)
//{
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
//	TIM_ICInitTypeDef TIM_ICInitStructure;  
//	GPIO_InitTypeDef GPIO_InitStructure;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);    //ʹ�ܶ�ʱ��1��ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO, ENABLE);   //ʹ��PE�˿�ʱ��
//	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE);

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_11;	//�˿�����
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //��������
//	GPIO_Init(GPIOE, &GPIO_InitStructure);					//�����趨������ʼ��GPIOA

//	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
//	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;              //Ԥ��Ƶ�� 
//	TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;  //�趨�������Զ���װֵ
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ѡ��ʱ�ӷ�Ƶ������Ƶ
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM���ϼ���  
//	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
//	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
//	
//	TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
//	
//	TIM_ICStructInit(&TIM_ICInitStructure);
//	TIM_ICInitStructure.TIM_ICFilter = 10;
//	TIM_ICInit(TIM1, &TIM_ICInitStructure);
//	
//	TIM_ClearFlag(TIM1, TIM_FLAG_Update);                   //���TIM�ĸ��±�־λ
//	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
//	//Reset counter
//	TIM_SetCounter(TIM1,0);
////	//===============================================
////	TIM1->CNT = 0x7fff;
////	//===============================================
//	TIM_Cmd(TIM1, ENABLE); 
//}
///**************************************************************************
//�������ܣ���TIM4��ʼ��Ϊ�������ӿ�ģʽ
//��ڲ�������
//����  ֵ����
//**************************************************************************/
//void Encoder_Init_TIM4(void)
//{
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
//	TIM_ICInitTypeDef TIM_ICInitStructure;  
//	GPIO_InitTypeDef GPIO_InitStructure;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);    //ʹ�ܶ�ʱ��4��ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO, ENABLE);   //ʹ��PD�˿�ʱ��
//	GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;	//�˿�����
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //��������
//	GPIO_Init(GPIOD, &GPIO_InitStructure);					//�����趨������ʼ��GPIOB

//	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
//	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;              // Ԥ��Ƶ�� 
//	TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;  //�趨�������Զ���װֵ
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ѡ��ʱ�ӷ�Ƶ������Ƶ
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM���ϼ���  
//	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
//	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ
//	TIM_ICStructInit(&TIM_ICInitStructure);
//	TIM_ICInitStructure.TIM_ICFilter = 10;
//	TIM_ICInit(TIM4, &TIM_ICInitStructure);
//	TIM_ClearFlag(TIM4, TIM_FLAG_Update);                   //���TIM�ĸ��±�־λ
//	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
//	//Reset counter
//	TIM_SetCounter(TIM4,0);
////	//===============================================
////	TIM4->CNT = 0x7fff;
////	//===============================================
//	TIM_Cmd(TIM4, ENABLE); 
//}

///**************************************************************************
//�������ܣ���ȡ�����������ֵ
//��ڲ�����TIM_TypeDef * TIMx
//����  ֵ����
//**************************************************************************/
////s16 getTIMx_DetaCnt(TIM_TypeDef * TIMx)
////{
////	s16 cnt;
////	cnt = TIMx->CNT-0x7fff;
////	TIMx->CNT = 0x7fff;
////	return cnt;
////}
//int Read_Encoder(u8 TIMX)
//{
//int Encoder_TIM;
//	switch(TIMX)
//	{
//		case 1:Encoder_TIM=(short )TIM1 ->CNT; TIM1 ->CNT =0;break;
//		case 4:Encoder_TIM=(short )TIM4 ->CNT; TIM4 ->CNT =0;break;
//		default:Encoder_TIM=0;
//	}
//	return Encoder_TIM;
//}
///**************************************************************************
//�������ܣ�������������
//��ڲ�����int *leftSpeed,int *rightSpeed
//����  ֵ����
//		//�������ҳ������ٶȣ������ٶ�Ϊ��ֵ �������ٶ�Ϊ��ֵ���ٶ�Ϊ����1000֮����ٶ� mm/s
//		//һ��ʱ���ڵı������仯ֵ*ת���ʣ�ת��Ϊֱ���ϵľ���m��*200s��5ms����һ�Σ� �õ� m/s *1000ת��Ϊint����

//		һȦ����������
//			��1560
//			�ң�1040
//		���Ӱ뾶��0.03m
//		�����ܳ���2*pi*r
//		һ������ľ��룺
//			��0.000120830m
//			�ң�0.000181245m
//		�ٶȷֱ��ʣ�
//			��0.0120m/s 12.0mm/s
//			�ң�0.0181m/s 18.1mm/s
//**************************************************************************/

////void Get_Motor_Speed(int *leftSpeed,int *rightSpeed)
////{
////	static int leftWheelEncoderNow    = 0;
////	static int rightWheelEncoderNow   = 0;
////	static int leftWheelEncoderLast   = 0;
////	static int rightWheelEncoderLast  = 0;	
////	
////	//��¼�������ұ���������
////	leftWheelEncoderNow += getTIMx_DetaCnt(TIM4);
////	rightWheelEncoderNow+= getTIMx_DetaCnt(TIM1);
////		
////	//5ms����    	
////	*leftSpeed   = (leftWheelEncoderNow - leftWheelEncoderLast)*1000*200*0.000120830;  
////	*rightSpeed  = (rightWheelEncoderNow - rightWheelEncoderLast)*1000*200*0.000181245;

////	//��¼�ϴα���������
////	leftWheelEncoderLast  = leftWheelEncoderNow;                    
////	rightWheelEncoderLast = rightWheelEncoderNow;                   
////}


