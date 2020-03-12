

/* 系统头文件 */
#include "stm32f10x.h"
#include "systemconfig.h"

/* lkdGui驱动相关文件 */
#include "UC1698Driver.h"
#include "lkdGui.h"

void test1WinInit(void);

static lkdWin test1Win,MainWin;
void MainWinInit(void);



int main(void)
{
	SystemconfigInit();
	
	LcdInit();/* lcd初始化 */
	defaultFontInit();/* 字库初始化 */
	GuiUpdateDisplayAll();/* 更新屏幕-清屏 */
	MainWinInit();
	GuiWinAdd(&MainWin);
	while(1)
	{
		GuiWinDisplay();
	}
}

void test1Winfun(void)
{
	/* 窗口内容具体代码实现 */
	static uint8_t flag;
	static uint32_t testTick;
	static lkdProgress progress1;
	if(flag == 0){
		progress1.x = 5;
		progress1.y = 30;
		progress1.ratio = 0;
		progress1.wide = 130;
		progress1.high = 15;
		flag = 1;
	}
	if(flag == 1){
		GuiProGress(&progress1);
		GuiUpdateDisplayAll();
		testTick = GetTimer1Tick();
		flag = 2;
	}
	if(flag == 2){
		if(GetTimer1IntervalTick(testTick) > 1000){//两秒刷新一次
			progress1.ratio += 5;
			flag = 1;
			if(progress1.ratio >= 100){
				flag = 3;
			}
		}
	}
	if(flag == 3){
		GuiWinDeleteTop();
		GuiUpdateDisplayAll();
		flag = 0;
	}
}

void test1WinInit(void)
{
	test1Win.x = 0;
	test1Win.y = 0;
	test1Win.hight = 160;
	test1Win.wide = 160;
	test1Win.title = "测试窗口1";
	test1Win.WindowFunction = test1Winfun;
}

void MainWinfun(void)
{
	/* 窗口内容具体代码实现 */
	static uint8_t flag;
	static uint32_t testTick;
	if(flag == 0){
		flag = 1;
	}
	if(flag == 1){
		GuiRowText(0, 20,160, FONT_MID, "此窗口为主窗口");
		GuiUpdateDisplayAll();
		testTick = GetTimer1Tick();
		flag = 2;
	}
	if(flag == 2){
		if(GetTimer1IntervalTick(testTick) > 5000){//两秒刷新一次
			test1WinInit();
			GuiWinAdd(&test1Win);
			flag = 0;
		}
	}
}

void MainWinInit(void)
{
	MainWin.x = 0;
	MainWin.y = 0;
	MainWin.hight = 160;
	MainWin.wide = 160;
	MainWin.title = NULL;
	MainWin.WindowFunction = MainWinfun;
}

/* END */
