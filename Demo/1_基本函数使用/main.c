

/* 系统头文件 */
#include "stm32f10x.h"
#include "systemconfig.h"

/* lkdGui驱动相关文件 */
#include "lkdGui.h"


int main(void)
{
	SystemconfigInit();
	
	LcdInit();/* lcd初始化 */
	defaultFontInit();/* 字库初始化 */
	GuiUpdateDisplayAll();/* 更新屏幕-清屏 */
	
	/* 画点 */
	GuiPoint(10, 10, forecolor);
	GuiPoint(15, 15, forecolor);
	/* 画斜线 */
	GuiBiasLine(20, 0,40, 20,forecolor);
	GuiBiasLine(30, 0,60, 20,forecolor);
	GuiBiasLine(40, 0,100, 20,forecolor);
	GuiBiasLine(50, 0,159, 20,forecolor);
	/* 画水平点线 */
	GuiHPointLine(0, 22,160, 2, forecolor);
	GuiHPointLine(0, 32,160, 3, forecolor);
	GuiHPointLine(0, 42,160, 4, forecolor);
	GuiHPointLine(0, 52,160, 5, forecolor);
	/* 画水平线 */
	GuiHLine(0, 62, 160, forecolor);
	/* 画垂直点线 */
	GuiRPointLine(10, 63,100,2, forecolor);
	GuiRPointLine(20, 63,100,3, forecolor);
	GuiRPointLine(30, 63,100,4, forecolor);
	GuiRPointLine(40, 63,100,5, forecolor);
	/* 画垂直线 */
	GuiRLine(50, 63,100, forecolor);
	/* 画矩形 */
	GuiRect(0, 101, 159,159, forecolor);
	/* 画填充矩形 */
	GuiFillRect(10, 110, 150,150, forecolor);
	/* 画填充矩形 */
	GuiFillRect(30, 120, 130,140, backcolor);
	/* 更新 */
	GuiUpdateDisplayAll();
	while(1)
	{
		
	}
}
