

/* 系统头文件 */
#include "stm32f10x.h"
#include "systemconfig.h"

/* lkdGui驱动相关文件 */
#include "UC1698Driver.h"
#include "lkdmyFont.h"

/* lkdGui库文件 */
#include "lkdGuiBasic.h"
#include "lkdGuiFont.h"
#include "lkdGuiWin.h"
#include "lkdGuiControl.h"
#include "lkdGuiMenu.h"
#include "menutest.h"
#include "keyDriver.h"

int main(void)
{
	SystemconfigInit();
	
	LcdInit();/* lcd初始化 */
	defaultFontInit();/* 字库初始化 */
	GuiUpdateDisplayAll();/* 更新屏幕-清屏 */
	userAppInit();
	KeyDriverInit();
	while(1)
	{
		userAppMain();
		ScanKeyStatus();
	}
}


/* END */
