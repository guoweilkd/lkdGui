/**
  * @file   lkdGuiDriver.c
  * @author  guoweilkd
  * @version V0.0.0
  * @date    2018/04/18
  * @brief  lkdGui驱动
  */

#include "lkdGuiDriver.h"
/* lcd驱动文件引用 */
#include "LM6029ADriver.h"

/* Gui显示缓冲区 */
static uint8_t  lkdGuiBuff[GUIXMAX][GUIYMAX/8 + GUIYMAX%8];
/* 行位获取数组 */
const static uint8_t colBit[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

/**
  *@brief 将Gui缓冲区数据显示到lcd上
  *@param  None
  *@retval None
  */
void GuiUpdateDisplayAll(void)
{
	uint32_t x,y,ymax;
	LCD_CS_LOW();
	ymax = GUI_LCM_YMAX/8 + GUI_LCM_YMAX%8;
	for(y = 0; y < ymax; y++){
		SetLcdCol(0);
		SetLcdPage(y);	
		for(x = 0;x < GUI_LCM_XMAX; x++){
			WriteLcdData(lkdGuiBuff[x][y]);
		}	
	}
	LCD_CS_HIGH();
}

/**
  *@brief 画点
  *@param  x,y 坐标
  *@param  color 颜色 <目前只有黑白>
  *@retval None
  */
void GuiDrawPoint(lkdCoord x, lkdCoord y, lkdColour color)
{
	if(color == CWHITLE){//白色
		lkdGuiBuff[x][y >> 3] &= ~colBit[y & 0x07];
	}
	else{//黑色
		lkdGuiBuff[x][y >> 3] |= colBit[y & 0x07];
	}
}

/**
  *@brief 读点
  *@param  x,y 坐标
  *@param  color 颜色 <目前只有黑白>
  *@retval None
  */
void  GuiReadPoint(lkdCoord x, lkdCoord y, lkdColour *pColor)
{
	
}
