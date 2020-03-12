/**
  * @file   lkdGuiBasic.c
  * @author  guoweilkd
  * @version V1.1.0
  * @date    2018/03/19
  * @brief  lkdGui基本函数库
  */
  
#include "lkdGui.h"

uint8_t const GetBit[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
/**
  *@brief 画点
  *@param  x,y 坐标
  *@param  color 颜色
  *@retval None
  */
void GuiPoint(lkdCoord x, lkdCoord y, lkdColour color)
{
	/* 坐标检测 */
	if(x >= GUIXMAX || y >= GUIYMAX || x < 0 || y < 0)
		return;
	GuiDrawPoint(x, y, color);
}

/**
  *@brief 画斜线
  *@param  x,y 坐标
  *@param  color 颜色
  *@retval None
  */
void GuiBiasLine(lkdCoord x0, lkdCoord y0,\
	lkdCoord x1, lkdCoord y1, lkdColour color)
{
	float offset,tf;	
	lkdCoord tempCoord;
	
	if(x0 > x1){
		tempCoord = x1;
		x1 = x0;
		x0 = tempCoord;
		tempCoord = y1;
		y1 = y0;
		y0 = tempCoord;
		
	}
	
	/* 坐标检查 */
	if(y0 >= GUIYMAX || x0 >= GUIXMAX || y1 < 0 || x1 < 0){
		return;
	}
	if(x1 >= GUIXMAX){
		x1 = GUIXMAX - 1;
	}
	if(y1 >= GUIYMAX){
		y1 = GUIYMAX - 1;
	}
	if(x0 < 0){
		x0 = 0;
	}
	if(y0 < 0){
		y0 = 0;
	}
	if(x0 == x1){
		GuiRPointLine(x0,y0,y1,1,color);
	}
	else if(y0 == y1){
		GuiHPointLine(x0,y0,x1,1,color);
	}
	else if(y1 - y0 > 0){
		if((y1 - y0) < (x1 - x0)){
			tf = y0;
			offset = ((float)(y1 - y0))/(x1 - x0);
			while(1){
				GuiDrawPoint(x0, (lkdCoord)tf, color);
				x0 ++;
				tf += offset;
				if(tf > y1){
					tf = y1;
				}
				if(x0 > x1){
					break;
				}
			}
		}
		else{
			tf = x0;
			offset = ((float)(x1 - x0))/(y1 - y0);
			while(1){
				GuiDrawPoint((lkdCoord)tf, y0, color);
				y0 ++;
				tf += offset;
				if(x0 > x1){
					x0 = x1;
				}
				if(y0 > y1){
					break;
				}
			}
		}
	}
	else{
		if((y0 - y1) < (x1 - x0)){
			tf = y0;
			offset = ((float)(y0 - y1))/(x1 - x0);
			while(1){
				GuiDrawPoint(x0, (lkdCoord)tf, color);
				x0 ++;
				tf -= offset;
				if(tf <= y1){
					tf = y1;
				}
				if(x0 > x1){
					break;
				}
			}
		}
		else{
			tf = x0;
			offset = ((float)(x1 - x0))/(y0 - y1);
			while(1){
				GuiDrawPoint((lkdCoord)tf, y0, color);
				y0 --;
				tf += offset;
				if(tf > x1){
					tf = x1;
				}
				if(y0 <= y1){
					break;
				}
			}
		}
	}
}
/**
  *@brief 画水平点线
  *@param  x0,y0 起始坐标
  *@param  x1 结束坐标
  *@param  interval 每隔N点画一个点
  *@param  color 颜色
  *@retval None
  */
void GuiHPointLine(lkdCoord x0, lkdCoord y0,\
	lkdCoord x1, uint8_t interval, lkdColour color)
{
	lkdCoord tx;
	
	if(x0 > x1){//检查,交换-> x0 < x1
		tx = x1;
		x1 = x0;
		x0 = tx;
	}
	
	/* 坐标检查 */
	if(y0 < 0 || y0 >= GUIYMAX){
		return;
	}
	if(x1 < 0){
		return;
	}
	if(x0 >= GUIXMAX){
		return;
	}
	if(x1 >= GUIXMAX){
		x1 = GUIXMAX - 1;
	}
	if(x0 < 0){
		x0 = 0;
	}
	
	/* 画线 */
	if(x0 == x1){
		GuiDrawPoint(x0, y0, color);
		return;
	}
	while(1){
		GuiDrawPoint(x0, y0, color);
		x0 += interval;
		if(x0 > x1){
			break;
		}
	}
}

/**
  *@brief 画垂直点线
  *@param  x0,y0 起始坐标
  *@param  y1 结束坐标
  *@param  interval 每隔N点画一个点
  *@param  color 颜色
  *@retval None
  */
void  GuiRPointLine(lkdCoord x0, lkdCoord y0,\
	lkdCoord y1,uint8_t interval, lkdColour color)
{
	lkdCoord ty;
	if(y0 > y1){//检查,交换-> y0 < y1
		ty = y1;
		y1 = y0;
		y0 = ty;
	}
	
	/* 坐标检查 */
	if(x0 < 0 || x0 >= GUIXMAX){
		return;
	}
	if(y1 < 0){
		return;
	}
	if(y0 >= GUIYMAX){
		return;
	}
	if(y1 >= GUIYMAX){
		y1 = GUIYMAX - 1;
	}
	if(y0 < 0){
		y0 = 0;
	}
	
	/* 画线 */
	if(y0 == y1){
		GuiDrawPoint(x0, y0, color);
		return;
	}
	while(1){
		GuiDrawPoint(x0, y0, color);
		y0 += interval;
		if(y0 > y1){
			break;
		}
	}
}
/**
  *@brief 画水平线
  *@param  x0,y0 起始坐标
  *@param  x1结束坐标
  *@param  color 颜色
  *@retval None
  */
void GuiHLine(lkdCoord x0, lkdCoord y0, lkdCoord x1, lkdColour color)
{
	GuiHPointLine(x0, y0, x1, 1, color);
}

/**
  *@brief 画垂直线
  *@param  x0,y0 起始坐标
  *@param  y1 结束坐标
  *@param  color 颜色
  *@retval None
  */
void  GuiRLine(lkdCoord x0, lkdCoord y0, lkdCoord y1, lkdColour color)
{
	GuiRPointLine(x0, y0, y1, 1, color);
}

/**
  *@brief 画矩形
  *@param  x0,y0 起始坐标
  *@param  x1,y1 结束坐标
  *@param  color 颜色
  *@retval None
  */
void GuiRect(lkdCoord x0, lkdCoord y0, lkdCoord x1,lkdCoord y1, lkdColour color)
{
	GuiHPointLine(x0, y0, x1, 1, color);
	GuiHPointLine(x0, y1, x1, 1, color);
	GuiRPointLine(x0, y0, y1, 1, color);
	GuiRPointLine(x1, y0, y1, 1, color);
}

/**
  *@brief 画填充矩形
  *@param  x0,y0 起始坐标
  *@param  x1,y1 结束坐标
  *@param  color 颜色
  *@retval None
  */
void GuiFillRect(lkdCoord x0, lkdCoord y0, lkdCoord x1,lkdCoord y1, lkdColour color)
{
	lkdCoord i;	
	lkdCoord tempCoord;
	
	if(y0 > y1){//排序
		tempCoord = y1;
		y1 = y0;
		y0 = tempCoord;
	}
	if(x0 > x1){
		tempCoord = x1;
		x1 = x0;
		x0 = tempCoord;
	}
	for(i = y0; i<= y1; i++){
		GuiHPointLine(x0, i, x1, 1, color);
	}
}

/**
  *@brief 画位图
  *@param  bitMap 位图数组
  *@param  x0,y0 起始坐标
  *@param  xlen,ylen 宽度和高度
  *@param  flag 0 正常显示 1反显
  *@retval None
  */
void GuiBitMap(uint8_t *bitMap,lkdCoord x0,\
	lkdCoord y0,uint32_t xlen,uint32_t ylen, uint8_t flag)
{
	uint8_t z,zMax;
	lkdColour colour;
	uint32_t i,j,tj,tx,eachRow;
	
	if(x0 < 0 || y0 < 0 || x0 >= GUIXMAX || y0 >= GUIYMAX){
		return;
	}
	/* 列像素单位为字节 */
	if(xlen%8 != 0){
		eachRow = xlen/8 + 1;
	}
	else{
		eachRow = xlen/8;
	}
	/* 检查坐标最大，超过不显示 */
	if(x0 + xlen >= GUIXMAX){
		xlen = GUIXMAX - x0 - 1;
	}
	if(y0 + ylen >= GUIYMAX){
		ylen = GUIYMAX - y0 - 1;
	}
	/* 画图 */
	for(j = 0; j < ylen; j++){
		tj = eachRow * j;
		zMax = 8;
		for(i = 0; i < xlen; i += 8){
			if(i + 8 >= xlen){
				zMax = xlen - i;
			}
			tx = i/8;
			for(z = 0; z < zMax; z++){//位处理
				colour = (bitMap[tj + tx]&GetBit[z])?CBLACK:CWHITLE;
				if(flag){//反显处理
					colour = colour?CWHITLE:CBLACK;
				}
				GuiDrawPoint(x0 + i + z,y0 + j,colour);
			}
		}
	}
}

/**
  *@brief 画指定范围的位图
  *@param  bitMap 位图数组
  *@param  x0,y0 起始坐标
  *@param  endx,endy 终点坐标
  *@param  flag 0 正常显示 1反显
  *@retval None
  */
void GuiAreaBitMap(lkdBitmap *bitMap,\
	lkdCoord x0, lkdCoord y0, lkdCoord endx, lkdCoord endy, uint8_t flag)
{
	lkdCoord tcoord;
	lkdColour colour;
	uint8_t str,z,zMax,tflag = 0;
	uint16_t rowWide,i,j,yNum,xNum,tx;
	uint32_t tj;
	if(x0 >= GUIXMAX || y0 >= GUIYMAX || endx >= GUIXMAX || endy >= GUIYMAX ||\
		 x0 < 0 || y0 < 0 || endx < 0 || endy < 0 || endx == x0 || endy == y0 ||\
		 bitMap->beginx >= bitMap->wide || bitMap->beginy >= bitMap->high)
	{
		return;
	}
	if(x0 > endx){
		tcoord = x0;
		x0 = endx; 
		endx = tcoord;
	}
	if(y0 > endy){
		tcoord = y0;
		y0 = endy; 
		endy = tcoord;
	}
	if(bitMap->wide - bitMap->beginx < endx - x0){
		endx = bitMap->wide - bitMap->beginx + x0;
	}
	if(bitMap->high - bitMap->beginy < endy - y0){
		endy = bitMap->high - bitMap->beginy + y0;
	}

	/* 列像素单位为字节 */
	rowWide = bitMap->wide / 8;
	if(bitMap->wide % 8 != 0){
		rowWide = rowWide + 1;
	}

	/* 处理开始不对齐部分  */
	xNum = endx - x0;
	yNum = endy - y0;
	z = bitMap->beginx % 8;
	if(z != 0){
		if(xNum + z >= 8){
			zMax = 8;
		}
		else{
			zMax = xNum + z;
		}
		tj = rowWide * bitMap->beginy;
		tx = bitMap->beginx / 8;
		for(j = 0; j < yNum; j ++){
			str = bitMap->bitmap[tj + tx];
			z = bitMap->beginx % 8;
			for( ; z < zMax; z ++){
				colour = (str & GetBit[z]) ? CBLACK : CWHITLE;
				if(flag){//反显处理
					colour = colour ? CWHITLE : CBLACK;
				}
				GuiDrawPoint(x0 + z,y0 + j,colour);
			}
			tj += rowWide;
		}
		tflag = 1;
	}
	/* 处理其他部分  */
	tx = tflag + bitMap->beginx / 8;
	tj = rowWide * bitMap->beginy;
	if(bitMap->beginx % 8){
		x0 += (8 - bitMap->beginx % 8);
	}
	xNum = endx - x0;
	for(j = 0; j < yNum; j ++){
		for(i = 0; i < xNum; i += 8){
			zMax = 8;
			str = bitMap->bitmap[tj + tx + i / 8];
			if(i + 8 >= xNum){
				zMax = xNum - i;
			}
			for(z = 0 ; z < zMax; z ++){
				colour = (str & GetBit[z]) ? CBLACK : CWHITLE;
				if(flag){//反显处理
					colour = colour ? CWHITLE : CBLACK;
				}
				GuiDrawPoint(x0 + i + z,y0 + j,colour);
			}
		}
		tj += rowWide;
	}
}

void GuiAreaBitMapNumber(lkdBitmap *bitMap,uint8_t number,\
	lkdCoord x0, lkdCoord y0, lkdCoord endx, lkdCoord endy, uint8_t flag)
{
	GuiAreaBitMap(bitMap,x0, y0, endx, endy, flag);
}

/* END */
