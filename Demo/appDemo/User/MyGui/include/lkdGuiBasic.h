/**
  * @file   lkdGuiBasic.h
  * @author  guoweilkd
  * @version V1.1.0
  * @date    2018/03/19
  * @brief
  */

#ifndef __LKDGUIBASIC_H
#define	__LKDGUIBASIC_H

#include "lkdGuiDriver.h"

#ifndef NULL
#define NULL 0
#endif


/* 定义位图结构体 */
typedef struct{
	uint8_t *bitmap;/* 位图数组 */
	uint16_t wide;/* 位图宽 */
	uint16_t high;/* 位图高 */
	uint16_t beginx;/* 位图开始坐标 */
	uint16_t beginy;/* 位图开始坐标 */
}lkdBitmap;

/* 画点 */
void GuiPoint(lkdCoord x, lkdCoord y, lkdColour color);
/* 画斜线 */
void GuiBiasLine(lkdCoord x0, lkdCoord y0,lkdCoord x1, lkdCoord y1, lkdColour color);
/* 画水平线 */
void GuiHLine(lkdCoord x0, lkdCoord y0, lkdCoord x1, lkdColour color);
/* 画垂直线 */
void GuiRLine(lkdCoord x0, lkdCoord y0, lkdCoord y1, lkdColour color);
/* 画水平点线 */
void GuiHPointLine(lkdCoord x0, lkdCoord y0, lkdCoord x1, uint8_t interval, lkdColour color);
/* 画垂直点线 */
void GuiRPointLine(lkdCoord x0, lkdCoord y0, lkdCoord y1, uint8_t interval, lkdColour color);
/* 画矩形 */
void GuiRect(lkdCoord x0, lkdCoord y0, lkdCoord x1,lkdCoord y1, lkdColour color);
/* 画填充矩形 */
void GuiFillRect(lkdCoord x0, lkdCoord y0, lkdCoord x1,lkdCoord y1, lkdColour color);
/* 画位图 */
void GuiBitMap(uint8_t *bitMap,lkdCoord x0, lkdCoord y0,uint32_t xlen,uint32_t ylen,uint8_t flag);
/* 画自定义位图 */
void GuiAreaBitMap(lkdBitmap *bitMap,lkdCoord x0, lkdCoord y0, lkdCoord endx, lkdCoord endy, uint8_t flag);


#endif /* __LKDGUIBASIC_H */

/* END */
