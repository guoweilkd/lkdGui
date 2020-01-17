#ifndef __UC1698DRIVER_H
#define	__UC1698DRIVER_H

#include "stm32f10x.h"

/* 片选 */
#define LCD_CS_HIGH() {GPIOE->BSRR = GPIO_Pin_14;}
#define LCD_CS_LOW() {GPIOE->BRR = GPIO_Pin_14;}
/* 复位 */
#define LCD_RES_HIGH() {GPIOE->BSRR = GPIO_Pin_13;}
#define LCD_RES_LOW() {GPIOE->BRR = GPIO_Pin_13;}
/* /RD */
#define LCD_RD_HIGH() {GPIOE->BSRR = GPIO_Pin_15;}
#define LCD_RD_LOW() {GPIOE->BRR = GPIO_Pin_15;}
/* /WR */
#define LCD_WR_HIGH() {GPIOB->BSRR = GPIO_Pin_10;}
#define LCD_WR_LOW() {GPIOB->BRR = GPIO_Pin_10;}
/* BLA */
#define LCD_BLA_ON() {GPIOE->BRR = GPIO_Pin_6;}
#define LCD_BLA_OFF() {GPIOE->BSRR = GPIO_Pin_6;}
/* RS */
#define LCD_RS_HIGH() {GPIOB->BSRR = GPIO_Pin_11;}
#define LCD_RS_LOW() {GPIOB->BRR = GPIO_Pin_11;}
/* 数据线 */
#define  LCD_DB0_HIGH()            	 {GPIOE->BSRR = GPIO_Pin_12;}//DB0
#define  LCD_DB0_LOW()               {GPIOE->BRR = GPIO_Pin_12;}
#define  LCD_DB1_HIGH()            	 {GPIOE->BSRR = GPIO_Pin_11;}//DB1
#define  LCD_DB1_LOW()               {GPIOE->BRR = GPIO_Pin_11;}
#define  LCD_DB2_HIGH()            	 {GPIOC->BSRR = GPIO_Pin_5;}//DB2
#define  LCD_DB2_LOW()               {GPIOC->BRR = GPIO_Pin_5;}
#define  LCD_DB3_HIGH()            	 {GPIOC->BSRR = GPIO_Pin_4;}//DB3
#define  LCD_DB3_LOW()               {GPIOC->BRR = GPIO_Pin_4;}
#define  LCD_DB4_HIGH()            	 {GPIOA->BSRR = GPIO_Pin_3;}//DB4
#define  LCD_DB4_LOW()               {GPIOA->BRR = GPIO_Pin_3;}
#define  LCD_DB5_HIGH()            	 {GPIOA->BSRR = GPIO_Pin_2;}//DB5
#define  LCD_DB5_LOW()               {GPIOA->BRR = GPIO_Pin_2;}
#define  LCD_DB6_HIGH()              {GPIOA->BSRR = GPIO_Pin_1;}//DB6
#define  LCD_DB6_LOW()               {GPIOA->BRR = GPIO_Pin_1;}
#define  LCD_DB7_HIGH()            	 {GPIOA->BSRR = GPIO_Pin_0;}//DB7
#define  LCD_DB7_LOW()               {GPIOA->BRR = GPIO_Pin_0;}
/* 数据总线 */
#define LCD_DATABUS(TxData)  \
  	if(TxData&0x01){LCD_DB0_HIGH();}else{LCD_DB0_LOW();}\
	if(TxData&0x02){LCD_DB1_HIGH();}else{LCD_DB1_LOW();}\
	if(TxData&0x04){LCD_DB2_HIGH();}else{LCD_DB2_LOW();}\
	if(TxData&0x08){LCD_DB3_HIGH();}else{LCD_DB3_LOW();}\
	if(TxData&0x10){LCD_DB4_HIGH();}else{LCD_DB4_LOW();}\
	if(TxData&0x20){LCD_DB5_HIGH();}else{LCD_DB5_LOW();}\
	if(TxData&0x40){LCD_DB6_HIGH();}else{LCD_DB6_LOW();}\
	if(TxData&0x80){LCD_DB7_HIGH();}else{LCD_DB7_LOW();}

//#define LCD_DATATOBIT(TxData)	\
//	if(TxData == 0){\
//		LCD_DB0_LOW();LCD_DB1_LOW();LCD_DB2_LOW();LCD_DB3_LOW();\
//		LCD_DB4_LOW();LCD_DB5_LOW();LCD_DB6_LOW();LCD_DB7_LOW();}\
//	else if(TxData == 1){\
//		LCD_DB0_HIGH();LCD_DB1_HIGH();LCD_DB2_HIGH();LCD_DB3_HIGH();\
//		LCD_DB4_LOW();LCD_DB5_LOW();LCD_DB6_LOW();LCD_DB7_LOW();}\
//	else if(TxData == 2){\
//		LCD_DB0_LOW();LCD_DB1_LOW();LCD_DB2_LOW();LCD_DB3_LOW();\
//		LCD_DB4_HIGH();LCD_DB5_HIGH();LCD_DB6_HIGH();LCD_DB7_HIGH();}\
//	else if(TxData == 3){\
//		LCD_DB0_HIGH();LCD_DB1_HIGH();LCD_DB2_HIGH();LCD_DB3_HIGH();\
//		LCD_DB4_HIGH();LCD_DB5_HIGH();LCD_DB6_HIGH();LCD_DB7_HIGH();}
	
#define LCD_DATATOBIT(TxData)	\
	if(TxData == 0){LCD_DB3_LOW();LCD_DB7_LOW();}\
	else if(TxData == 1){LCD_DB3_HIGH();LCD_DB7_LOW();}\
	else if(TxData == 2){LCD_DB3_LOW();LCD_DB7_HIGH();}\
	else if(TxData == 3){LCD_DB3_HIGH();LCD_DB7_HIGH();}

#define OPEN_LCDDISPLAY 	0xAD/* 开显示 */
#define CLOSE_LCDDISPLAY	0xAC/* 关显示 */
#define CMD_ROWADDRH			0x70/* 行高位CMD */
#define CMD_ROWADDRL			0x60/* 行低位CMD */
#define CMD_COLADDRH			0x10/* 列高位CMD */
#define CMD_COLADDRL			0x00/* 列低位CMD */

	
#define BR			0X01	   	//Set LCD Bias Ratio:1/10 bias	  
#define PC1     0X03      //power control set as internal power
#define TC      0x00      //set temperate compensation as 0%
#define PM      192       //Set Vbias Potentiometer       
#define LC_210  0X05      //set LCD Control
#define LC_43   0x03
#define LC_5    0X01
#define LC_76   0x01
#define LC_8    0X00
#define NIV     0X10      //n-line inversion
#define CSF     0X02      //23:enable FRC,PWM,LRM sequence      
#define WPC0    0x25      //Starting Column Address
#define WPP0    0         //Starting Row Address
#define WPC1		0x5A			//Ending Column Address
#define WPP1		159		    //Ending Row Address
#define	AC    	0x01			//Address  Control	  
#define CEN 		159 			//COM scanning end (last COM with full line cycle,0 based index)

/* lcd初始化 */	
void LcdInit(void);
/* 设置页地址 */	
void SetLcdRow(uint8_t row);
/* 设置列地址 */
void SetLcdCol(uint8_t col);
/* 写数据 */
void WriteLcdData(uint8_t data);
/* 写命令 */
void WriteLcdCommand(uint8_t cmd);

void Write8DotsUC1698U(uint8_t Data);
/* 开显示 */
void OpenLcdDisplay(void);
/* 关显示 */
void CloseLcdDisplay(void);

extern void Delay_ms(uint16_t nms);
extern void Delay_us(uint32_t nus);
#endif /* __UC1698DRIVER_H */

/* END */
