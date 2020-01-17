/**
  * @file   lkdGuiFont.c
  * @author  guoweilkd
  * @version V1.1.0
  * @date    2018/03/27
  * @brief  gwGui字体文件
  */
 
#include "lkdGui.h"

/* lkd字体 */
static lkdFont *thisFont;

/**
  *@brief  设置当前要使用的字体指针
  *@param  pFont 要使用的字体指针
  *@retval None
  */
void GuiFontSet(lkdFont *pFont)
{
	thisFont = pFont;
}

/**
  *@brief  获取当前字体
  *@param  None
  *@retval 当前字体指针
  */
lkdFont *GetCurrentFont(void)
{
	return thisFont;
}

/**
  *@brief  写文本
  *@param  tInfo 写文本相关信息
  *@param  str 文本
  *@retval None
  */
void GuiText(fontTextInfo *tInfo, uint8_t *str)
{
	uint16_t endx = tInfo->x + tInfo->wide;
	uint16_t endy = tInfo->y + tInfo->high;
	lkdCoord tx = tInfo->x + tInfo->beginOffset;
	uint16_t fontWide;
	while(*str != '\0'){
		/* 计算当前字体的宽度 */
		if(*str > 0x7f){
			fontWide = thisFont->dwide;
		}
		else{
			fontWide = thisFont->swide;
		}
		/* 计算当前x打印坐标 */
		if(tx + fontWide + tInfo->wInterval > endx){
			tx = tInfo->x;
			tInfo->y += (thisFont->dhigh + tInfo->hInterval);
		}
		/* 是否达到结束坐标 */
		if(tInfo->y + thisFont->dhigh + tInfo->hInterval > endy){
			break;
		}
		if(*str > 0x7f){
			thisFont->getDfont(*str,*(str+1),thisFont->pZmBuff);
			GuiBitMap(thisFont->pZmBuff,tx,tInfo->y,\
				thisFont->dwide,thisFont->dhigh, tInfo->flag);
			str += 2;
			tx += (thisFont->dwide + tInfo->wInterval);	
		}
		else{
			thisFont->getSfont(*str,thisFont->pZmBuff);
			GuiBitMap(thisFont->pZmBuff,tx,tInfo->y,\
				thisFont->swide,thisFont->shigh, tInfo->flag);
			str ++;
			tx += (thisFont->swide + tInfo->wInterval);
		}
	}
}

/**
  *@brief  获取文本所占像素长度
  *@param  str 文本
  *@retval 像素长度
  */
uint16_t GetTextPixLen(uint8_t *str)
{
	uint16_t len = 0;
	while(*str != '\0'){
		if(*str > 0x7f){
			len += thisFont->dwide;
			str += 2;
		}
		else{
			len += thisFont->swide;
			str ++;
		}
	}
	return len;
}

/**
  *@brief  写单行文本
  *@param  x,y 起始坐标
  *@param  wide 单行文本宽度
  *@param  flag 字体对齐标志
  *@param  str 文本
  *@retval 像素长度
  */
void GuiRowText(lkdCoord x, lkdCoord y,uint16_t wide, FontFlag flag,uint8_t *str)
{
	uint16_t pixLen;
	fontTextInfo tInfo;
	lkdColour backcolor; 

	backcolor = GuiGetbackcolor();

	pixLen = GetTextPixLen(str);
	if(pixLen <= wide){
		if(flag == FONT_MID){
			tInfo.beginOffset = (wide - pixLen) / 2;
		}
		else if(flag == FONT_RIGHT){
			tInfo.beginOffset = wide - pixLen;
		}
		else{
			tInfo.beginOffset = 0;
		}
	}
	else{
		tInfo.beginOffset = 0;
	}
	tInfo.hInterval = 0;
	tInfo.wInterval = 0;
	tInfo.x = x;
	tInfo.y = y;
	tInfo.wide = wide;
	tInfo.high = thisFont->dhigh;
	if(backcolor == CWHITLE){
		tInfo.flag = 0;
	}
	else{//反显
		tInfo.flag = 1;
	}
	GuiText(&tInfo, str);
}

void GuiFont12Align(lkdCoord x, lkdCoord y,uint16_t wide, FontFlag flag,uint8_t *str)
{
	GuiRowText(x, y,wide,flag,str);
}

void GuiFont12(lkdCoord x, lkdCoord y, uint8_t *str)
{
	GuiRowText(x, y,159,FONT_LEFT,str);
}
/* END */
