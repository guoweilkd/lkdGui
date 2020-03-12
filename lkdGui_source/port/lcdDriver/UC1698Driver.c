/**
  * @file   UC1698Driver.c
  * @author  guoweilkd
  * @version V1.1.0
  * @date    2018/05/09
  * @brief  Lcd驱动
  * 本文件Lcd为UC1698
  */

#include "UC1698Driver.h"

const uint8_t DataToBit2[] = {0x00,0x0f,0xf0,0xff};


/**
  *@brief 引脚初始化
  *@param  None
  *@retval None
  */
static void LcdGpioConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | \
					RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOE, ENABLE);
	/* DB0 DB1 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	/* DB2 DB3 */	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_4;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	/* DB4 DB5 DB6 DB7 */							   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_2 | GPIO_Pin_1 | GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* RS WR */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_10;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	/* RD CS */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14;
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	/* REST */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	//背光
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	LCD_BLA_ON();
	LCD_CS_HIGH();
}

/**
  *@brief 写命令
  *@param  cmd 命令
  *@retval None
  */
void WriteLcdCommand(uint8_t cmd)
{
	LCD_RS_LOW();
	LCD_RD_HIGH();
	LCD_DATABUS(cmd);
	__NOP();
	LCD_WR_LOW();
	__NOP();
	LCD_WR_HIGH();
}

/**
  *@brief 写数据
  *@param  data 数据
  *@retval None
  */
void WriteLcdData(uint8_t data)
{
	LCD_RS_HIGH();
	LCD_RD_HIGH();
	LCD_DATATOBIT((data&0x03));;
	LCD_WR_LOW();
	LCD_WR_HIGH();
}

/**
  *@brief 设置起始行
  *@param  row 行
  *@retval None
  */
void SetLcdRow(uint8_t row)
{
	WriteLcdCommand(CMD_ROWADDRH | ((row & 0xF0) >> 4));
	WriteLcdCommand(CMD_ROWADDRL | (row & 0x0F));
}

/**
  *@brief 设置起始列
  *@param  col 列地址
  *@retval None
  */
void SetLcdCol(uint8_t col)
{
	WriteLcdCommand(CMD_COLADDRH | ((col & 0x70) >> 4));
	WriteLcdCommand(CMD_COLADDRL | (col & 0x0F));
}

/**
  *@brief 开显示
  *@param  None
  *@retval None
  */
void OpenLcdDisplay(void)
{
	LCD_CS_LOW();
	WriteLcdCommand(OPEN_LCDDISPLAY);
	LCD_CS_HIGH();
	LCD_BLA_ON();
}

/**
  *@brief  UC1698U横向写8个点的子函数
  *@param  Data:要显示的数据
  *@retval None
  */
void Write8DotsUC1698U(uint8_t Data)
{
	LCD_DATATOBIT((Data >> 6));
	LCD_WR_LOW();
	LCD_WR_HIGH();
	LCD_DATATOBIT(((Data >> 4)&0x03));
	LCD_WR_LOW();
	LCD_WR_HIGH();
	LCD_DATATOBIT(((Data >> 2)&0x03));
	LCD_WR_LOW();
	LCD_WR_HIGH();
	LCD_DATATOBIT((Data & 0x03));
	LCD_WR_LOW();
	LCD_WR_HIGH();
}

/**
  *@brief 关显示
  *@param  None
  *@retval None
  */
void CloseLcdDisplay(void)
{
	LCD_CS_LOW();
	WriteLcdCommand(CLOSE_LCDDISPLAY);
	LCD_CS_HIGH();
	LCD_BLA_OFF();
}

/**
  *@brief LCD初始化
  *@param  None
  *@retval None
  */
void LcdInit(void)
{
	LcdGpioConfig();
	LCD_CS_LOW();
	LCD_RES_LOW();
	Delay_ms(100);
	LCD_RES_HIGH();
	Delay_ms(100);
	WriteLcdCommand(0xE8|(BR&0X03));//偏离率			
	WriteLcdCommand(0x28|(PC1&0X03));//power控制		
	WriteLcdCommand(0x24|(TC&0x03));//温度补偿		
	WriteLcdCommand(0x81);//设置电位命令		
	WriteLcdCommand(PM ); //值
	WriteLcdCommand(0xc0|(LC_210&0X07) ); 				
	WriteLcdCommand(0xa0|(LC_43 &0X03) ); 					
	WriteLcdCommand(0xd0|(LC_5  &0X01) ); 				
	WriteLcdCommand(0xd4|(LC_76 &0X03) );				
	WriteLcdCommand(0x84|(LC_8  &0X01) );		
	WriteLcdCommand(0xc8);	//设置N-line 			 			
	WriteLcdCommand( NIV);				 		
	WriteLcdCommand(0xd8|(CSF&0X07) );	 		
	WriteLcdCommand(0xf4);				 	
	WriteLcdCommand(WPC0);				 		
	WriteLcdCommand(0xf6);				 		
	WriteLcdCommand(WPC1);				 		
	WriteLcdCommand(0xf5);				 	 	
	WriteLcdCommand(WPP0);				 		
	WriteLcdCommand(0xf7);				 	 	
	WriteLcdCommand(WPP1); 			 	 	
	WriteLcdCommand(0xf8|((AC>>3)&0x01));	 										  
	WriteLcdCommand(0x88| (0x07&AC));	 	
	WriteLcdCommand(0xf1);			
	WriteLcdCommand(CEN);		 	
	WriteLcdCommand(OPEN_LCDDISPLAY);/* 开显示 */
	Delay_ms(20);
	LCD_CS_HIGH();
}

/* END */
