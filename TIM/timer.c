//#include "timer.h"
//#include "delay.h"

///*记录定时器溢出次数*/
//u16 overcount=0;
////extern int z;
////extern int d;
////arr：自动重装值。
////psc：时钟预分频数

//void TIM2_Int_Init(u16 arr,u16 psc)
//{
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能

//	TIM_TimeBaseStructure.TIM_Period = arr-1;              //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
//	TIM_TimeBaseStructure.TIM_Prescaler =psc-1;            //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0;         //设置时钟分割:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
//	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);      //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
// 
//	TIM_ITConfig(  //使能或者失能指定的TIM中断
//		TIM2,      //TIM2
//		TIM_IT_Update ,
//		ENABLE     //使能
//		);
//	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;            //TIM3中断
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;         //从优先级3级
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //IRQ通道被使能
//	NVIC_Init(&NVIC_InitStructure);                            //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

//	TIM_Cmd(TIM2, DISABLE);  //使能TIMx外设
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
//		/*测5次数据计算一次平均值*/
//		while(i!=5)
//		{
//		PCout(0)=1;  //拉高信号，作为触发信号
//		delay_us(20);  //高电平信号超过10us
//		PCout(0)=0;
//		/*等待回响信号*/
//		while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==RESET);
//		TIM_Cmd(TIM2,ENABLE);//回响信号到来，开启定时器计数

//		i+=1; //每收到一次回响信号+1，收到5次就计算均值
//		while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==SET);//回响信号消失
//		TIM_Cmd(TIM2,DISABLE);//关闭定时器

//		tim=TIM_GetCounter(TIM2);//获取计TIM2数寄存器中的计数值，一边计算回响信号时间

//		length=(tim + overcount*1000)/58.0;//通过回响信号计算距离

//		sum=length+sum;
//		TIM2->CNT=0;  //将TIM2计数寄存器的计数值清零
//		overcount=0;  //中断溢出次数清零
//		delay_ms(100);
//		}
//		length=sum/5;
//		return length;//距离作为函数返回值
//}

////5ms 定时器中断服务函数

//void TIM2_IRQHandler(void)                            //TIM2中断
//{
//	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
//	{
//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);   //清除TIMx的中断待处理位:TIM 中断源 


////		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);	//最后清除中断标志位
//		
//		overcount++;
//	}
//}












