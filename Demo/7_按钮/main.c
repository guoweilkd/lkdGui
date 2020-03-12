

/* 系统头文件 */
#include "stm32f10x.h"
#include "systemconfig.h"
#include "stdio.h"

/* lkdGui驱动相关文件 */
#include "UC1698Driver.h"
#include "lkdGui.h"

int main(void)
{
	SystemconfigInit();
	
	LcdInit();/* lcd初始化 */
	defaultFontInit();/* 字库初始化 */
	GuiUpdateDisplayAll();/* 更新屏幕-清屏 */
	
	lkdButton tButton;
	
	tButton.x = 20;
	tButton.y = 50;
	tButton.wide = thisFont->dwide * 2 + 15;
	tButton.high = thisFont->dhigh + 5;
	tButton.name = "确认";
	tButton.flag = 0;/* 抬起状态 */
	
	GuiButton(&tButton);
	tButton.x = 80;
	tButton.y = 50;
	tButton.wide = thisFont->dwide * 2 + 15;
	tButton.high = thisFont->dhigh + 5;
	tButton.name = "取消";
	tButton.flag = 1;/* 按下状态 */
	GuiButton(&tButton);
	
	tButton.x = 10;
	tButton.y = 80;
	tButton.wide = thisFont->dwide * 4 + 15;
	tButton.high = thisFont->dhigh + 5;
	tButton.name = "确定执行";
	tButton.flag = 0;/* 抬起状态 */
	
	GuiButton(&tButton);
	tButton.x = 80;
	tButton.y = 80;
	tButton.wide = thisFont->dwide * 4 + 15;
	tButton.high = thisFont->dhigh + 5;
	tButton.name = "确定执行";
	tButton.flag = 1;/* 按下状态 */
	GuiButton(&tButton);
	
	tButton.x = 10;
	tButton.y = 110;
	tButton.wide = thisFont->dwide * 4 + 15;
	tButton.high = thisFont->dhigh * 2 + 5;
	tButton.name = "确定执行";
	tButton.flag = 0;/* 抬起状态 */
	
	GuiButton(&tButton);
	tButton.x = 80;
	tButton.y = 110;
	tButton.wide = thisFont->dwide * 4 + 15;
	tButton.high = thisFont->dhigh * 2 + 5;
	tButton.name = "确定执行";
	tButton.flag = 1;/* 按下状态 */
	GuiButton(&tButton);
	
	GuiUpdateDisplayAll();/* 更新 */
	while(1)
	{
	}
}

/* END */
