//////////////////////////////////////////////////////////////////////////////////	 
// STM32F1��Ļ����������
// �޸���ʷ   : ��Ϊstm32Ӳ��SPI����ģʽ��Ӳ��IIC����ģʽ,ʹ��ʱֻ��Ҫ����IIC����SPI�ĺ궨����޸Ķ�Ӧ��Ӳ�����ŵĺ궨�弴��
// �޸�����   : �޸�void OLED_Init(void);void OLED_WR_Byte(uint8_t dat,uint8_t cmd);����uint8_t SPI_ReadWriteByte(uint8_t TxData)
// �Ż�Ч��   : ��ߴ���Ч��,������Ļ��ϵͳ��Դ��ռ��,ʹ��Ļ��ʾ��������д���жϷ����������Ĭ��STM32F1ϵ��������� IIC(400K) SPI(18MHZ)��������ʱ����֧��,�ڲ��Զ�����ʱ��
//******************************************************************************/



#ifndef __OLED_H
#define __OLED_H			  	 
#include "stm32f10x.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_i2c.h"         

#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    

//-----------------���ϲ��ֽ�ֹ�޸�----------------//	
//-----------------OLEDģʽ����----------------//

#define OLED_MODE 1 // IIC->1  SPI->0

//-----------------END-----------------------//	
//-----------------OLED_SPI�˿ڶ���----------------//	


#define SPI_ALL_IO_CLOCK 	RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC //�ο� RCC_APB2Periph_GPIOx�������� |��

#define DC_IO							GPIO_Pin_12//����ʵ��SPI��MISO����,��Ϊ��Ļ����Ҫ��32������,����ֱ�ӽ��������������������л�����(DC)���ο�IS_GET_GPIO_PIN
#define DC_GPIOx      		GPIOB//�ο�IS_GPIO_ALL_PERIPH

#define CS_IO							GPIO_Pin_12//����ʵ��SPI��NSS����,��Ϊһ�㲻�Ӷ����Ļ,���Գ�ʼ��Ϊ��ͨIO���ͻ�ֱ�ӽӵ�ʹ��,����(CSƬѡ����)(��ʵ����������������ԣ����д)���ο�IS_GET_GPIO_PIN
#define CS_GPIOx      		GPIOG//�ο�IS_GPIO_ALL_PERIPH

#define RES_IO						GPIO_Pin_8//������IO,���ڳ�ʼ��ʱ����(RES����)���ο�IS_GET_GPIO_PIN
#define RES_GPIOx      		GPIOB//�ο�IS_GPIO_ALL_PERIPH

#define SCK_IO						GPIO_Pin_13//��Ӳ��SPIʱ��(CLK)����Ļ��(D0��CLK)���ο�IS_GET_GPIO_PIN
#define SCK_GPIOx      		GPIOB//�ο�IS_GPIO_ALL_PERIPH

#define MOSI_IO						GPIO_Pin_15//��Ӳ��SPI���ݽ�(MOSI)��,��Ļ��(D1/DAT)���ο�IS_GET_GPIO_PIN
#define MOSI_GPIOx      	GPIOB//�ο�IS_GPIO_ALL_PERIPH

#define SPI_Std_PORT			SPI2//�ο�IS_SPI_ALL_PERIPHѡ��ֱ���Ҽ�GOTO��
#define SPI_CLOCK 				RCC_APB1Periph_SPI2//�ο�	//RCC_APB2Periph_SPI1
																										//RCC_APB1Periph_SPI2     
																										//RCC_APB1Periph_SPI3


//-----------------OLED_IIC�˿ڶ���----------------//	

#define OLED_Address      0x78//Ĭ��(������Ļ����ĵ������)

#define IIC_Std_PORT			I2C2//�ο�IS_I2C_ALL_PERIPHѡ��ֱ���Ҽ�GOTO��
#define IIC_CLOCK 				RCC_APB1Periph_I2C2//�ο�//RCC_APB1Periph_I2C1         
																									//RCC_APB1Periph_I2C2 
#define IIC_ALL_IO_CLOCK 	RCC_APB2Periph_GPIOB //�ο� RCC_APB2Periph_GPIOx�������� |��

#define SDA_IO						GPIO_Pin_11//��Ӳ��IIC����(SDA)����Ļ��(SDA)���ο�IS_GET_GPIO_PIN
#define SDA_GPIOx 				GPIOB//�ο�IS_GPIO_ALL_PERIPH

#define SCL_IO						GPIO_Pin_10//��Ӳ��IICʱ��(CLK)����Ļ��(CLK)���ο�IS_GET_GPIO_PIN
#define SCL_GPIOx 				GPIOB//�ο�IS_GPIO_ALL_PERIPH

//-----------------END-----------------------//	


//-----------------���²��ֽ�ֹ�޸�----------------//	

#define OLED_RST_Clr() GPIO_ResetBits(RES_GPIOx,RES_IO)//RES                                          
#define OLED_RST_Set() GPIO_SetBits(RES_GPIOx,RES_IO)

#define OLED_DC_Clr() GPIO_ResetBits(DC_GPIOx,DC_IO)//DC
#define OLED_DC_Set() GPIO_SetBits(DC_GPIOx,DC_IO)

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����


//OLED�����ú���
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);
void OLED_ShowString(uint8_t x,uint8_t y, uint8_t *p);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
/**SPI��ʼ������**/
void SPI_Configuration(void);
/**SPI���ͺ���**/
uint8_t SPI_ReadWriteByte(uint8_t TxData);
/**IIC��ʼ������**/
void IIC_Configuration(void);
/**IIC���ͺ���**/
void I2C_WriteByte(uint8_t addr,uint8_t data);
#endif

	 



