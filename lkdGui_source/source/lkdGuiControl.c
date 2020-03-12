/**
  * @file   lkdGuiControl.c
  * @author  guoweilkd
  * @version V1.1.0
  * @date    2018/06/03
  * @brief  lkdGui控件库
  */

#include "lkdGui.h"

/**
  *@brief 垂直滚动条
  *@param  pScroll 滚动条
  *@retval None
  */
void GuiVScroll(lkdScroll *pScroll)
{
	uint8_t lumpsize;
	uint8_t lumpAdd;
	float eachSize;
	lkdColour forecolor,backcolor; 

	forecolor = GuiGetForecolor();
	backcolor=  GuiGetbackcolor();

	if(pScroll->x + 3 > GUIXMAX || pScroll->y + pScroll->hight > GUIYMAX){
		return;
	}	
	GuiFillRect(pScroll->x,pScroll->y,pScroll->x + 3,pScroll->y + pScroll->hight - 1,forecolor);
	if(pScroll->max > 5){//进度条滑动块选择
		lumpsize = pScroll->hight/7;
	}
	else if(pScroll->max < 1){
		return;
	}
	else{
		lumpsize = pScroll->hight/pScroll->max;
	}
	
	if(pScroll->lump < 0){
		pScroll->lump = 0;
	}
	else if(pScroll->lump >= pScroll->max){
		pScroll->lump = pScroll->max - 1;
	}
	
	GuiRPointLine(pScroll->x+1,pScroll->y + 1,pScroll->y + pScroll->hight - 2,2,backcolor);
	GuiRPointLine(pScroll->x + 2,pScroll->y + 2,pScroll->y + pScroll->hight-2,2,backcolor);
	/* 画进度块 */
	eachSize = ((float)(pScroll->hight))/pScroll->max;
	lumpAdd = pScroll->y + (uint8_t)(pScroll->lump * eachSize);
	if(pScroll->lump < pScroll->max - 1){
		GuiFillRect(pScroll->x+1,lumpAdd,pScroll->x + 2,lumpAdd + lumpsize,forecolor);
	}
	else{
		GuiFillRect(pScroll->x+1,pScroll->y+pScroll->hight - lumpsize,\
			pScroll->x + 2,pScroll->y+pScroll->hight - 1,forecolor);
	}
}

/**
  *@brief 水平滚动条
  *@param  pScroll 滚动条
  *@retval None
  */
void GuiHScroll(lkdScroll *pScroll)
{
	uint8_t lumpsize;
	uint8_t lumpAdd;
	float eachSize;
	lkdColour forecolor,backcolor; 

	forecolor = GuiGetForecolor();
	backcolor=  GuiGetbackcolor();

	if(pScroll->x + pScroll->hight > GUIXMAX || pScroll->y + 3 > GUIYMAX){
		return;
	}
	GuiFillRect(pScroll->x,pScroll->y,pScroll->x + pScroll->hight - 1,pScroll->y + 3,forecolor);
	if(pScroll->max >= 5){//进度条滑动块选择
		lumpsize = pScroll->hight/7;
	}
	else if(pScroll->max < 1){
		return;
	}
	else{
		lumpsize = pScroll->hight/pScroll->max;
	}
	
	if(pScroll->lump < 0){
		pScroll->lump = 0;
	}
	else if(pScroll->lump >= pScroll->max){
		pScroll->lump = pScroll->max - 1;
	}	
	
	GuiHPointLine(pScroll->x+1,pScroll->y + 1,pScroll->x + pScroll->hight - 2,2,backcolor);
	GuiHPointLine(pScroll->x + 2,pScroll->y + 2,pScroll->x + pScroll->hight-2,2,backcolor);
	/* 画进度块 */
	eachSize = ((float)(pScroll->hight))/pScroll->max;
	lumpAdd = pScroll->x + (uint8_t)(pScroll->lump * eachSize);
	if(pScroll->lump < pScroll->max - 1){
		GuiFillRect(lumpAdd,pScroll->y+1,lumpAdd + lumpsize,pScroll->y + 2,forecolor);
	}
	else{
		GuiFillRect(pScroll->x+pScroll->hight-lumpsize,pScroll->y+1,\
			pScroll->x+pScroll->hight - 1,pScroll->y + 2,forecolor);
	}
}

/**
  *@brief 按键
  *@param  pButton 按键信息
  *@retval None
  */
void GuiButton(lkdButton *pButton)
{
	uint16_t endx = pButton->x + pButton->wide;
	uint16_t endy = pButton->y + pButton->high;
	lkdFont *pFont;
	lkdColour forecolor,backcolor; 

	pFont = GetCurrentFont();
	forecolor = GuiGetForecolor();
	backcolor=  GuiGetbackcolor();

	if(pButton->wide < 6 || pButton->high < 6 || pButton->high - pFont->dhigh - 3 < 0){
		return;
	}
	if(pButton->flag == BUTTON_UP){//非选中
		GuiFillRect(pButton->x,pButton->y,endx,endy, backcolor);
		GuiRect(pButton->x,pButton->y,endx - 1,endy - 1, forecolor);
		lkdCoord ty;
		ty = pButton->y + (pButton->high - pFont->dhigh - 3)/2 + 1;
		GuiRowText(pButton->x + 2,ty,pButton->wide - 3,FONT_MID,pButton->name);
		GuiRLine(endx,pButton->y + 1,endy,forecolor);
		GuiHLine(pButton->x + 1,endy,endx,forecolor);
	}
	else{
		GuiFillRect(pButton->x,pButton->y,endx,endy, backcolor);
		GuiRect(pButton->x,pButton->y,endx,endy, forecolor);
		GuiExchangeColor();
		lkdCoord ty;
		ty = pButton->y + (pButton->high - pFont->dhigh - 3)/2 + 1;
		GuiFillRect(pButton->x + 2,pButton->y + 2,endx - 2,endy - 2, backcolor);
		GuiRowText(pButton->x + 2,ty,pButton->wide - 2,FONT_MID,pButton->name);
		GuiExchangeColor();
	}
}

/**
  *@brief 进度条
  *@param  pProg 进度条信息
  *@retval None
  */
void GuiProGress(lkdProgress *pProg)
{
	lkdColour forecolor,backcolor; 

	forecolor = GuiGetForecolor();
	backcolor=  GuiGetbackcolor();

	if(pProg->wide < 5||pProg->high < 5){
		return;
	}
	if(pProg->ratio > 100){
		pProg->ratio = 100;
	}
	uint16_t endx = pProg->x + pProg->wide;
	uint16_t endy = pProg->y + pProg->high;
	lkdCoord tx;
	float lump = pProg->wide / 100.0;
	tx = pProg->x + lump * pProg->ratio;
	GuiFillRect(pProg->x,pProg->y,endx,endy, backcolor);
	GuiRect(pProg->x,pProg->y,endx,endy, forecolor);
	GuiFillRect(pProg->x + 1,pProg->y + 1,tx,endy - 1, forecolor);
}

/* END */
