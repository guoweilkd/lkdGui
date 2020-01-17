/**
  * @file   lkdGuiWin.c
  * @author  guoweilkd
  * @version V0.0.0
  * @date    2018/06/03
  * @brief  lkdGui窗口管理
  */

#include "lkdGui.h"

/* 窗口管理结构 */
static struct GuiWinManage winManage;

/**
  *@brief  绘制窗口
  *@param  pWindow 窗口指针
  *@retval None
  */
void GuiWinDraw(lkdWin *pWindow)
{
	lkdColour forecolor,backcolor; 

	forecolor = GuiGetForecolor();
	backcolor=  GuiGetbackcolor();

	if(pWindow->x + pWindow->wide - 1 > GUIXMAX || pWindow->y + pWindow->hight - 1 > GUIYMAX ||\
		 pWindow->x < 0 || pWindow->y < 0 || pWindow->wide == 0 || pWindow->hight == 0){
		   return;
	}
	GuiFillRect(pWindow->x, pWindow->y, pWindow->x + pWindow->wide - 1,\
		pWindow->y + pWindow->hight - 1, backcolor);
	GuiRect(pWindow->x, pWindow->y, pWindow->x + pWindow->wide - 1,\
		pWindow->y + pWindow->hight - 1, forecolor);
	if(pWindow->title != NULL){
		GuiHLine(pWindow->x, pWindow->y + 15,pWindow->x + pWindow->wide - 1, forecolor);
		GuiRowText(pWindow->x + 2, pWindow->y + 2, pWindow->wide - 4,\
			FONT_MID,pWindow->title);
	}
	GuiUpdateDisplayAll();
}

/**
  *@brief  添加窗口
  *@param  pWindow 窗口指针
  *@retval 0 成功 -1 失败
  */
int8_t GuiWinAdd(lkdWin *pWindow)
{
	GuiWinDraw(pWindow);
	if(winManage.pWin >= GUIWINMANAGE_NUM){
		return -1;
	}
	winManage.winStack[winManage.pWin] = pWindow;
	winManage.pWin ++;
	return 0;
}

/**
  *@brief  执行顶层窗口
  *@param  None
  *@retval None
  */
void GuiWinDisplay(void)
{
	if(winManage.pWin == 0 || winManage.pWin > GUIWINMANAGE_NUM){
		return;
	}
	lkdWin *pThis = winManage.winStack[winManage.pWin - 1];
	pThis->WindowFunction(pThis->param);
}

/**
  *@brief  删除当前窗口
  *@param  None
  *@retval None
  */
void GuiWinDeleteTop(void)
{
	if(winManage.pWin <= 1 || winManage.pWin > GUIWINMANAGE_NUM){
		return;
	}
	winManage.pWin --;
	GuiWinDraw(winManage.winStack[winManage.pWin - 1]);
}

/**
  *@brief  获取顶层窗口
  *@param  None
  *@retval 顶层窗口
  */
lkdWin *GuiGetTopWin(void)
{
	lkdWin *pTopWin = NULL;
	
	if(winManage.pWin >= 1){
		pTopWin = winManage.winStack[winManage.pWin - 1];
	}
	return pTopWin;
}

void GuiWinInit(void)
{
	winManage.pWin = 0;
}
/* END */
