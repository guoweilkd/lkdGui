/**
  * @file   LM6029ADriver.c
  * @author  guoweilkd
  * @version V1.1.0
  * @date    2018/03/15
  * @brief  Lcd驱动
  * 本文件Lcd为LM6029ACW
  */

#include "LM6029ADriver.h"

/**
  *@brief 引脚初始化
  *@param  None
  *@retval None
  */
static void LcdGpioConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB, ENABLE);
	
	/* D0~D7 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |  GPIO_Pin_1 |\
		GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 |\
		GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	/* RD WE CS BLA */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	/* RS RES */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	LCD_BLA_ON();
	LCD_CS_HIGH();
}
static void delay(void)
{
	uint8_t i;
	for(i = 0;i < 50; i++);
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
	delay();
	LCD_WR_LOW();
	delay();
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
	LCD_DATABUS(data);
	delay();
	LCD_WR_LOW();
	delay();
	LCD_WR_HIGH();
}

/**
  *@brief 设置起始页
  *@param  page 页
  *@retval None
  */
void SetLcdPage(uint8_t page)
{
	page = page & 0x07;
	page = page | 0xB0;
	WriteLcdCommand(page);
}

/**
  *@brief 设置起始列
  *@param  col 列地址
  *@retval None
  */
void SetLcdCol(uint8_t col)
{
	uint8_t tempCol;
	tempCol = (col >> 4)&0x0F;
	tempCol |= 0x10;
	WriteLcdCommand(tempCol);
	tempCol = col&0x0F;
	WriteLcdCommand(tempCol);
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
	delay();
	LCD_RES_HIGH();
	WriteLcdCommand(0xA0);/* SEG 正向 0xA1 反向 */
	WriteLcdCommand(0xC8);/* COM 反向 0xC0 正向 */
	WriteLcdCommand(0xA2);/* 偏压比 */
	WriteLcdCommand(0x2F);/* 内部电源操作设置 */
	WriteLcdCommand(0x81);/* 对比度电流量调节 */
	WriteLcdCommand(0x29);/*  */
	WriteLcdCommand(0x40);/* DDRAM起始行地址 */
	WriteLcdCommand(OPEN_LCDDISPLAY);/* 开显示 */
}

/* END */
