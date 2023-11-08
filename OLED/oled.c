//////////////////////////////////////////////////////////////////////////////////	 
// STM32F1��Ļ����������
// �޸���ʷ   : ��Ϊstm32Ӳ��SPI����ģʽ��Ӳ��IIC����ģʽ,ʹ��ʱֻ��Ҫ����IIC����SPI�ĺ궨����޸Ķ�Ӧ��Ӳ�����ŵĺ궨�弴��
// �޸�����   : �޸�void OLED_Init(void);void OLED_WR_Byte(uint8_t dat,uint8_t cmd);����uint8_t SPI_ReadWriteByte(uint8_t TxData)
// �Ż�Ч��   : ��ߴ���Ч��,������Ļ��ϵͳ��Դ��ռ��,ʹ��Ļ��ʾ��������д���жϷ����������Ĭ��STM32F1ϵ��������� IIC(400K) SPI(18MHZ)��������ʱ����֧��,�ڲ��Զ�����ʱ��
//******************************************************************************/

#include "oled.h"
#include "oledfont.h"  
#include "bmp.h"  
//OLED���Դ�
//��Ÿ�ʽ����.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   


//��SSD1106д��һ���ֽڡ�
//dat:Ҫд�������/����
//cmd:����/�����־ 0,��ʾ����;1,��ʾ����;

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



//Ѱַ��ʽ�������оƬ
	void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
}   	  
//����OLED��ʾ    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//�ر�OLED��ʾ     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!	  
void OLED_Clear(void)  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //������ʾ
}


//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ				 
//size:ѡ������ 16/12 
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//�õ�ƫ�ƺ��ֵ			
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
//m^n����
uint32_t oled_pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//��ʾ2������
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);	 		  
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
//��ʾһ���ַ��Ŵ�
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
//��ʾ����
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
/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
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

	
//��ʼ������		  
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
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
	
	RCC_APB2PeriphClockCmd(	SPI_ALL_IO_CLOCK|RCC_APB2Periph_AFIO, ENABLE );//IOʱ��ʹ�� 
	
	//**DC��CS��RES��ʼ������ͨ**//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;													
	
	// DC(����MISO,������Ļ����Ҫ�����ݸ�32,���Ե�DCʹ��) ��ʼ��(�������������)

	GPIO_InitStructure.GPIO_Pin = DC_IO;
	GPIO_Init(DC_GPIOx, &GPIO_InitStructure);
	
	// CS (����SPI��׼Ƭѡ,��Ϊ����Ҫ�����Ļ,����ֱ������)��ʼ��(ʹ������)
	GPIO_InitStructure.GPIO_Pin = CS_IO;
 	GPIO_Init(CS_GPIOx, &GPIO_InitStructure);
	GPIO_ResetBits(CS_GPIOx,CS_IO);//CS���ͱ�ʾʹ��
	
	
	//RES ��ʼ�� (�ߵ�ƽ��,�͵�ƽ������+��=��λ)
 
	GPIO_InitStructure.GPIO_Pin = RES_IO;
 	GPIO_Init(RES_GPIOx, &GPIO_InitStructure);
	

	/**SPI_IO(SCK+MOSI)���� ��ʼ��***/
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //SCK.MOSI����������� 

	GPIO_InitStructure.GPIO_Pin =SCK_IO ;
	GPIO_Init(SCK_GPIOx, &GPIO_InitStructure);
	GPIO_SetBits(SCK_GPIOx,SCK_IO);//SCK

	GPIO_InitStructure.GPIO_Pin =MOSI_IO ;
	GPIO_Init(MOSI_GPIOx, &GPIO_InitStructure);
	GPIO_SetBits(MOSI_GPIOx,MOSI_IO);//MOSI
	
	
 /*SPI��ʼ��*/
if (SPI_Std_PORT==SPI1){
	RCC_APB2PeriphClockCmd(SPI_CLOCK,  ENABLE );}//SPI1ʱ��ʹ�� 
else{
	RCC_APB1PeriphClockCmd(SPI_CLOCK,  ENABLE );}//SPI2/3ʱ��ʹ�� 

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	//SPI�����Ϊ18MHZ
	
	if (SPI_Std_PORT==SPI1){
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;}//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ4 72MHZ/4=18MHZ
	else{
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;}//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ2 36MHZ/2=18MHZ
	
	SPI_Init(SPI_Std_PORT, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
		
	SPI_Cmd(SPI_Std_PORT, ENABLE); //ʹ��SPI����
		
	SPI_ReadWriteByte(0xff);//��������		
	

	/*RES����*/
  OLED_RST_Set();
	uint32_t Delay100ms=7200000;//��Ϊ��Ƶ��72MHZ,������ѭ��תһ��1/72M��,����������
	while(Delay100ms--);//��ʱ100ms
	OLED_RST_Clr();
	Delay100ms=7200000;
	while(Delay100ms--);//��ʱ100ms
	OLED_RST_Set(); 
} 


uint8_t SPI_ReadWriteByte(uint8_t TxData)//SPI�շ�����
{		
	uint8_t retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI_Std_PORT, SPI_I2S_FLAG_TXE) == RESET){ //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
				retry++;
				if(retry>200)return 0;
			}			  
	SPI_I2S_SendData(SPI_Std_PORT, TxData); //ͨ������SPIx����һ������
	retry=0;
	while (SPI_I2S_GetFlagStatus(SPI_Std_PORT, SPI_I2S_FLAG_RXNE) == RESET){ //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
				retry++;
				if(retry>200)return 0;
			}	  						    
	return SPI_I2S_ReceiveData(SPI_Std_PORT); //����ͨ��SPIx������յ�����					    
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
	I2C_InitStructure.I2C_OwnAddress1 = 0x30;//STM32IIC�Լ��ĵ�ַ��������ã����ظ��ͺ�
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 400000;//IIC�����Ϊ400K

	I2C_Cmd(IIC_Std_PORT, ENABLE);
	I2C_Init(IIC_Std_PORT, &I2C_InitStructure);
	
	uint32_t Delay100ms=7200000;
	while(Delay100ms--); 

}
























