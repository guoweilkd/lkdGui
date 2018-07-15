/**
  * @file   lkdGuiColour.h
  * @author  guoweilkd
  * @version V0.0.0
  * @date    2018/04/18
  * @brief  颜色管理 目前只有黑白
  */

#ifndef __LKDGUICOLOUR_H
#define	__LKDGUICOLOUR_H

#include "stdint.h"

typedef uint8_t lkdColour;

#define CWHITLE	0x00/* 白色 */
#define CBLACK	0x01/* 黑色 */

extern lkdColour forecolor,backcolor;

/* 获取前景色 */
lkdColour GuiGetForecolor(void);
/* 设置前景色 */
void GuiSetForecolor(lkdColour colour);
/* 获取背景色 */
lkdColour GuiGetbackcolor(void);
/* 设置背景色 */
void GuiSetbackcolor(lkdColour colour);
/* 交换前景色和背景色 */
void GuiExchangeColor(void);

#endif /* __LKDGUICOLOUR_H */

/* END */
