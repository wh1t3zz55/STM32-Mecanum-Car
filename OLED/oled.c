//////////////////////////////////////////////////////////////////////////////////	 
// STM32F1屏幕库驱动程序
// 修改历史   : 改为stm32硬件SPI驱动模式和硬件IIC驱动模式,使用时只需要定义IIC还是SPI的宏定义和修改对应的硬件引脚的宏定义即可
// 修改内容   : 修改void OLED_Init(void);void OLED_WR_Byte(uint8_t dat,uint8_t cmd);新增uint8_t SPI_ReadWriteByte(uint8_t TxData)
// 优化效果   : 提高代码效率,减少屏幕对系统资源的占用,使屏幕显示函数可以写在中断服务函数里！传输默认STM32F1系列最大速率 IIC(400K) SPI(18MHZ)。无需延时函数支持,内部自定义延时。
//******************************************************************************/

#include "oled.h"
#include "oledfont.h"  
#include "bmp.h"  
//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   


//向SSD1106写入一个字节。
//dat:要写入的数据/命令
//cmd:数据/命令标志 0,表示命令;1,表示数据;

void OLED_WR_Byte(uint8_t dat,uint8_t cmd)
{
	if(cmd){
		#if OLED_MODE==1
			I2C_WriteByte(0x40, dat);	    
		#else
			OLED_DC_Set();
			SPI_ReadWriteByte(dat);
		#endif
	}
	 
	else{
		#if OLED_MODE==1
			I2C_WriteByte(0x00, dat);	   	    
		#else
			OLED_DC_Clr();
			SPI_ReadWriteByte(dat);
		#endif
	}
}



//寻址方式发命令给芯片
	void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
}   	  
//开启OLED显示    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //更新显示
}


//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12 
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//得到偏移后的值			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(SIZE ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
				OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
				OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
				OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y+1);
			for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
				
			}
}
//m^n函数
uint32_t oled_pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ');
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0'); 
	}
} 
//显示一个字符号串
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j]);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}
//显示汉字
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no)
{      			    
	uint8_t t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}
/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
} 

void OLED_Init(void)        
{
	#if OLED_MODE==1
	IIC_Configuration();   	    
	#else
	SPI_Configuration();
	#endif

	
//初始化命令		  
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
	OLED_Clear();
	OLED_Set_Pos(0,0);
}
			    


  
void SPI_Configuration(void)        
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	
	RCC_APB2PeriphClockCmd(	SPI_ALL_IO_CLOCK|RCC_APB2Periph_AFIO, ENABLE );//IO时钟使能 
	
	//**DC和CS和RES初始化成普通**//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;													
	
	// DC(就是MISO,但是屏幕不需要发数据给32,所以当DC使用) 初始化(命令或数据引脚)

	GPIO_InitStructure.GPIO_Pin = DC_IO;
	GPIO_Init(DC_GPIOx, &GPIO_InitStructure);
	
	// CS (就是SPI标准片选,因为不需要多个屏幕,所以直接拉低)初始化(使能引脚)
	GPIO_InitStructure.GPIO_Pin = CS_IO;
 	GPIO_Init(CS_GPIOx, &GPIO_InitStructure);
	GPIO_ResetBits(CS_GPIOx,CS_IO);//CS拉低表示使能
	
	
	//RES 初始化 (高电平关,低电平开，关+开=复位)
 
	GPIO_InitStructure.GPIO_Pin = RES_IO;
 	GPIO_Init(RES_GPIOx, &GPIO_InitStructure);
	

	/**SPI_IO(SCK+MOSI)功能 初始化***/
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //SCK.MOSI复用推挽输出 

	GPIO_InitStructure.GPIO_Pin =SCK_IO ;
	GPIO_Init(SCK_GPIOx, &GPIO_InitStructure);
	GPIO_SetBits(SCK_GPIOx,SCK_IO);//SCK

	GPIO_InitStructure.GPIO_Pin =MOSI_IO ;
	GPIO_Init(MOSI_GPIOx, &GPIO_InitStructure);
	GPIO_SetBits(MOSI_GPIOx,MOSI_IO);//MOSI
	
	
 /*SPI初始化*/
if (SPI_Std_PORT==SPI1){
	RCC_APB2PeriphClockCmd(SPI_CLOCK,  ENABLE );}//SPI1时钟使能 
else{
	RCC_APB1PeriphClockCmd(SPI_CLOCK,  ENABLE );}//SPI2/3时钟使能 

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//串行同步时钟的空闲状态为高电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
	//SPI最高速为18MHZ
	
	if (SPI_Std_PORT==SPI1){
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;}//定义波特率预分频的值:波特率预分频值为4 72MHZ/4=18MHZ
	else{
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;}//定义波特率预分频的值:波特率预分频值为2 36MHZ/2=18MHZ
	
	SPI_Init(SPI_Std_PORT, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
		
	SPI_Cmd(SPI_Std_PORT, ENABLE); //使能SPI外设
		
	SPI_ReadWriteByte(0xff);//启动传输		
	

	/*RES重启*/
  OLED_RST_Set();
	uint32_t Delay100ms=7200000;//因为主频是72MHZ,所以死循环转一次1/72M秒,所以这样是
	while(Delay100ms--);//延时100ms
	OLED_RST_Clr();
	Delay100ms=7200000;
	while(Delay100ms--);//延时100ms
	OLED_RST_Set(); 
} 


uint8_t SPI_ReadWriteByte(uint8_t TxData)//SPI收发函数
{		
	uint8_t retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI_Std_PORT, SPI_I2S_FLAG_TXE) == RESET){ //检查指定的SPI标志位设置与否:发送缓存空标志位
				retry++;
				if(retry>200)return 0;
			}			  
	SPI_I2S_SendData(SPI_Std_PORT, TxData); //通过外设SPIx发送一个数据
	retry=0;
	while (SPI_I2S_GetFlagStatus(SPI_Std_PORT, SPI_I2S_FLAG_RXNE) == RESET){ //检查指定的SPI标志位设置与否:接受缓存非空标志位
				retry++;
				if(retry>200)return 0;
			}	  						    
	return SPI_I2S_ReceiveData(SPI_Std_PORT); //返回通过SPIx最近接收的数据					    
}






/**********************************************
// IIC Write Byte
**********************************************/
void I2C_WriteByte(uint8_t addr,uint8_t data)
{
  while(I2C_GetFlagStatus(IIC_Std_PORT, I2C_FLAG_BUSY));
	
	I2C_GenerateSTART(IIC_Std_PORT, ENABLE);
	while(!I2C_CheckEvent(IIC_Std_PORT, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(IIC_Std_PORT,OLED_Address, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(IIC_Std_PORT, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(IIC_Std_PORT, addr);
	while (!I2C_CheckEvent(IIC_Std_PORT, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(IIC_Std_PORT, data);
	while (!I2C_CheckEvent(IIC_Std_PORT, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTOP(IIC_Std_PORT, ENABLE);
}


void IIC_Configuration(void)
{
	I2C_InitTypeDef  I2C_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure; 

	RCC_APB1PeriphClockCmd(IIC_CLOCK,ENABLE);
	RCC_APB2PeriphClockCmd(IIC_ALL_IO_CLOCK|RCC_APB2Periph_AFIO,ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	
	GPIO_InitStructure.GPIO_Pin =  SDA_IO;
	GPIO_Init(SDA_GPIOx, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin =  SCL_IO;
	GPIO_Init(SCL_GPIOx, &GPIO_InitStructure);
	
	I2C_DeInit(IIC_Std_PORT);
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0x30;//STM32IIC自己的地址，随便设置，不重复就好
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 400000;//IIC最高速为400K

	I2C_Cmd(IIC_Std_PORT, ENABLE);
	I2C_Init(IIC_Std_PORT, &I2C_InitStructure);
	
	uint32_t Delay100ms=7200000;
	while(Delay100ms--); 

}
























