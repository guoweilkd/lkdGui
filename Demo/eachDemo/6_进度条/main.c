

/* 系统头文件 */
#include "stm32f10x.h"
#include "systemconfig.h"
#include "stdio.h"

/* lkdGui驱动相关文件 */
#include "UC1698Driver.h"
#include "lkdmyFont.h"

/* lkdGui库文件 */
#include "lkdGuiBasic.h"
#include "lkdGuiFont.h"
#include "lkdGuiControl.h"

int main(void)
{
	SystemconfigInit();
	
	LcdInit();/* lcd初始化 */
	defaultFontInit();/* 字库初始化 */
	GuiUpdateDisplayAll();/* 更新屏幕-清屏 */
	
	lkdProgress tProGress;
	uint8_t ratioStr[8];
	tProGress.x = 5;
	tProGress.y = 20;
	tProGress.wide = 130;
	tProGress.high = thisFont->dhigh;
	tProGress.ratio = 0;
	while(1)
	{
		for(uint8_t i = 0; i < 100; i ++){
			tProGress.ratio = i;/* 进度控制 */
			GuiProGress(&tProGress);/* 画进度条 */
			sprintf((char *)ratioStr,"%d%%",tProGress.ratio);
			GuiFillRect(137,21,157,33,backcolor);
			GuiRowText(137,21,20,FONT_RIGHT,ratioStr);
			GuiUpdateDisplayAll();/* 更新 */
			Delay_ms(500);
		}
	}
}

/* END */
