//////////////////////////////////////////////////////////////////////////////////	 
// STM32F1屏幕库驱动程序
// 修改历史   : 改为stm32硬件SPI驱动模式和硬件IIC驱动模式,使用时只需要定义IIC还是SPI的宏定义和修改对应的硬件引脚的宏定义即可
// 修改内容   : 修改void OLED_Init(void);void OLED_WR_Byte(uint8_t dat,uint8_t cmd);新增uint8_t SPI_ReadWriteByte(uint8_t TxData)
// 优化效果   : 提高代码效率,减少屏幕对系统资源的占用,使屏幕显示函数可以写在中断服务函数里！传输默认STM32F1系列最大速率 IIC(400K) SPI(18MHZ)。无需延时函数支持,内部自定义延时。
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

//-----------------以上部分禁止修改----------------//	
//-----------------OLED模式设置----------------//

#define OLED_MODE 1 // IIC->1  SPI->0

//-----------------END-----------------------//	
//-----------------OLED_SPI端口定义----------------//	


#define SPI_ALL_IO_CLOCK 	RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC //参考 RCC_APB2Periph_GPIOx如果多个用 |。

#define DC_IO							GPIO_Pin_12//※其实是SPI的MISO引脚,因为屏幕不需要给32发东西,所以直接将该引脚用作数据命令切换引脚(DC)。参考IS_GET_GPIO_PIN
#define DC_GPIOx      		GPIOB//参考IS_GPIO_ALL_PERIPH

#define CS_IO							GPIO_Pin_12//※其实是SPI的NSS引脚,因为一般不接多个屏幕,所以初始化为普通IO拉低或直接接地使能,这是(CS片选引脚)(本实验代码物理拉低所以，随便写)。参考IS_GET_GPIO_PIN
#define CS_GPIOx      		GPIOG//参考IS_GPIO_ALL_PERIPH

#define RES_IO						GPIO_Pin_8//※任意IO,用于初始化时重启(RES引脚)。参考IS_GET_GPIO_PIN
#define RES_GPIOx      		GPIOB//参考IS_GPIO_ALL_PERIPH

#define SCK_IO						GPIO_Pin_13//※硬件SPI时钟(CLK)脚屏幕的(D0或CLK)。参考IS_GET_GPIO_PIN
#define SCK_GPIOx      		GPIOB//参考IS_GPIO_ALL_PERIPH

#define MOSI_IO						GPIO_Pin_15//※硬件SPI数据脚(MOSI)脚,屏幕的(D1/DAT)。参考IS_GET_GPIO_PIN
#define MOSI_GPIOx      	GPIOB//参考IS_GPIO_ALL_PERIPH

#define SPI_Std_PORT			SPI2//参考IS_SPI_ALL_PERIPH选中直接右键GOTO。
#define SPI_CLOCK 				RCC_APB1Periph_SPI2//参考	//RCC_APB2Periph_SPI1
																										//RCC_APB1Periph_SPI2     
																										//RCC_APB1Periph_SPI3


//-----------------OLED_IIC端口定义----------------//	

#define OLED_Address      0x78//默认(根据屏幕背后的电阻决定)

#define IIC_Std_PORT			I2C2//参考IS_I2C_ALL_PERIPH选中直接右键GOTO。
#define IIC_CLOCK 				RCC_APB1Periph_I2C2//参考//RCC_APB1Periph_I2C1         
																									//RCC_APB1Periph_I2C2 
#define IIC_ALL_IO_CLOCK 	RCC_APB2Periph_GPIOB //参考 RCC_APB2Periph_GPIOx如果多个用 |。

#define SDA_IO						GPIO_Pin_11//※硬件IIC数据(SDA)脚屏幕的(SDA)。参考IS_GET_GPIO_PIN
#define SDA_GPIOx 				GPIOB//参考IS_GPIO_ALL_PERIPH

#define SCL_IO						GPIO_Pin_10//※硬件IIC时钟(CLK)脚屏幕的(CLK)。参考IS_GET_GPIO_PIN
#define SCL_GPIOx 				GPIOB//参考IS_GPIO_ALL_PERIPH

//-----------------END-----------------------//	


//-----------------以下部分禁止修改----------------//	

#define OLED_RST_Clr() GPIO_ResetBits(RES_GPIOx,RES_IO)//RES                                          
#define OLED_RST_Set() GPIO_SetBits(RES_GPIOx,RES_IO)

#define OLED_DC_Clr() GPIO_ResetBits(DC_GPIOx,DC_IO)//DC
#define OLED_DC_Set() GPIO_SetBits(DC_GPIOx,DC_IO)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


//OLED控制用函数
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
/**SPI初始化函数**/
void SPI_Configuration(void);
/**SPI发送函数**/
uint8_t SPI_ReadWriteByte(uint8_t TxData);
/**IIC初始化函数**/
void IIC_Configuration(void);
/**IIC发送函数**/
void I2C_WriteByte(uint8_t addr,uint8_t data);
#endif

	 



