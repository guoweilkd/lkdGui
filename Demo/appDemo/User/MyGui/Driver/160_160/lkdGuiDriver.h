/**
  * @file   lkdGuiDriver.h
  * @author  guoweilkd
  * @version V0.0.0
  * @date    2018/04/18
  * @brief  lkdGui驱动
  */

#ifndef __LKDGUIDRIVER_H
#define	__LKDGUIDRIVER_H

#include "lkdGuiColour.h"

/* 定义坐标类型 */
typedef int32_t lkdCoord;

/* 总行数y 总列数 x */
#define  GUI_LCM_XMAX	160
#define  GUI_LCM_YMAX	160
#define  GUIXMAX	GUI_LCM_XMAX
#define  GUIYMAX	GUI_LCM_YMAX

/* 更新 */
void GuiUpdateDisplayAll(void);
/* 更新指定范围 */
void GuiRangeUpdateDisplay(lkdCoord beginx, lkdCoord beginy,lkdCoord endx, lkdCoord endy);
/* 画点 */
void GuiDrawPoint(lkdCoord x, lkdCoord y, lkdColour color);
/* 读点 */
void  GuiReadPoint(lkdCoord x, lkdCoord y, lkdColour *pColor);

#endif /* __LKDGUIDRIVER_H */

/* END */
