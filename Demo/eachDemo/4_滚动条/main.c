

/* 系统头文件 */
#include "stm32f10x.h"
#include "systemconfig.h"

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
	
	lkdScroll tScroll;
	tScroll.x = 0;
	tScroll.y = 0;
	tScroll.hight = 160;
	while(1)
	{
		for(uint8_t tMax = 1; tMax < 10; tMax ++){
			tScroll.max = tMax;	
			for(uint8_t i = 0; i < tScroll.max; i ++){
				tScroll.lump = i;/* 进度快控制 */
				GuiVScroll(&tScroll);/* 水平进度条 */
				GuiHScroll(&tScroll);/* 垂直进度条 */
				GuiUpdateDisplayAll();/* 更新 */
				Delay_ms(500);
			}
		}
	}
}

/* END */
