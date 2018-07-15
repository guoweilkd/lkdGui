/**
  * @file   lkdGuiControl.h
  * @author  guoweilkd
  * @version V1.1.0
  * @date    2018/06/03
  * @brief  lkdGui控件库
  */

#ifndef __LKDGUICONTROL_H
#define	__LKDGUICONTROL_H

#include "lkdGuiBasic.h"

/* 滚动条 */
typedef struct{
	int16_t x;
	int16_t y;
	uint16_t hight;
	int16_t max;
	int16_t lump;
}lkdScroll;

/* 按钮 */
typedef struct{
	lkdCoord x;		/* 坐标 */
	lkdCoord y;
	uint8_t wide;
	uint8_t high;
	uint8_t flag; /* 0 抬起状态 1 按下状态 */
	uint8_t *name;/* 按键内容 */
}lkdButton;
enum ButtonState{
	BUTTON_UP,
	BUTTON_DOWN,
};

/* 进度条 */
typedef struct{
	lkdCoord x;		/* 坐标 */
	lkdCoord y;
	uint8_t wide;
	uint8_t high;
	uint8_t ratio; /* 当前进度 0~100 */
}lkdProgress;

/* 垂直滚动条 */
void GuiVScroll(lkdScroll *pScroll);
/* 水平滚动条 */
void GuiHScroll(lkdScroll *pScroll);
/* 按钮 */
void GuiButton(lkdButton *pButton);
/* 进度条 */
void GuiProGress(lkdProgress *pProg);

#endif /* __LKDGUICONTROL_H */

/* END */
