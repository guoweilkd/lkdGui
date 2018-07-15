

/* 系统头文件 */
#include "stm32f10x.h"
#include "systemconfig.h"

/* lkdGui驱动相关文件 */
#include "UC1698Driver.h"
#include "lkdmyFont.h"

/* lkdGui库文件 */
#include "lkdGuiBasic.h"
#include "lkdGuiFont.h"

void TextDisplay1(void);
void TextDisplay2(void);

int main(void)
{
	SystemconfigInit();
	
	LcdInit();/* lcd初始化 */
	defaultFontInit();/* 字库初始化 */
	GuiUpdateDisplayAll();/* 更新屏幕-清屏 */
	
	
	while(1)
	{
		TextDisplay1();
		Delay_ms(2000);
		TextDisplay2();
		Delay_ms(2000);
	}
}

void TextDisplay1(void)
{
	uint8_t *textStr = "lkdGui是一款为单色屏制作的Gui，它移植方便,使用简单...。";
	
	fontTextInfo textInfo;/* 定义文本信息结构 */
	
	GuiFillRect(0, 0, 159,159, backcolor);/* 清屏 */
	
	/* -----------1--------------- */
	textInfo.x = 2;/* 文本起始坐标 */
	textInfo.y = 2;
	textInfo.wide = 156;/* 文本范围大小 */
	textInfo.high = 42;
	textInfo.wInterval = 0;/* 字符间距 */
	textInfo.hInterval = 2;/* 行间距 */
	textInfo.flag = 0;/* 不反显 */
	textInfo.beginOffset = thisFont->dwide * 2;/* 开始偏移,首行缩进 */
	GuiText(&textInfo, textStr);
	GuiRect(0, 0, 159,44, forecolor);
	
	/* -----------2--------------- */
	GuiFillRect(0, 48, 159,92, forecolor);
	textInfo.x = 2;/* 文本起始坐标 */
	textInfo.y = 50;
	textInfo.flag = 1;/* 反显 */
	textInfo.beginOffset = thisFont->dwide * 2;/* 开始偏移,首行缩进 */
	GuiText(&textInfo, textStr);
	
	/* -----------3---------------- */
	textInfo.x = 2;/* 文本起始坐标 */
	textInfo.y = 98;
	textInfo.flag = 1;/* 反显 */
	textInfo.beginOffset = thisFont->dwide * 2;/* 开始偏移,首行缩进 */
	GuiText(&textInfo, textStr);
	GuiRect(0, 96, 159,140, forecolor);
	
	/* 更新 */
	GuiUpdateDisplayAll();
}

void TextDisplay2(void)
{
	uint8_t *textStr;
	
	fontTextInfo textInfo;/* 定义文本信息结构 */
	
	GuiFillRect(0, 0, 159,159, backcolor);/* 清屏 */
	
	/* -----------4--------------- */
	textStr = "lkdGui文本显示测试，当前字符间距为0像素，行间距为0像素。";
	textInfo.x = 2;/* 文本起始坐标 */
	textInfo.y = 2;
	textInfo.wide = 156;/* 文本范围大小 */
	textInfo.high = 42;
	textInfo.wInterval = 0;/* 字符间距 */
	textInfo.hInterval = 0;/* 行间距 */
	textInfo.flag = 0;/* 不反显 */
	textInfo.beginOffset = thisFont->dwide * 2;/* 开始偏移,首行缩进 */
	GuiText(&textInfo, textStr);
	GuiRect(0, 0, 159,44, forecolor);
	
	/* -----------5--------------- */
	textStr = "lkdGui文本显示测试，当前字符间距为2像素，行间距为2像素。";
	textInfo.x = 2;/* 文本起始坐标 */
	textInfo.y = 50;
	textInfo.wInterval = 2;/* 字符间距 */
	textInfo.hInterval = 2;/* 行间距 */
	textInfo.flag = 0;/* 不反显 */
	textInfo.beginOffset = thisFont->dwide * 2;/* 开始偏移,首行缩进 */
	GuiText(&textInfo, textStr);
	GuiRect(0, 48, 159,92, forecolor);
	
	/* -----------6--------------- */
	textStr = "lkdGui文本显示测试，当前字符间距为4像素，行间距为3像素。";
	textInfo.x = 2;/* 文本起始坐标 */
	textInfo.y = 98;
	textInfo.high = 60;
	textInfo.wInterval = 4;/* 字符间距 */
	textInfo.hInterval = 3;/* 行间距 */
	textInfo.flag = 0;/* 不反显 */
	textInfo.beginOffset = thisFont->dwide * 2;/* 开始偏移,首行缩进 */
	GuiText(&textInfo, textStr);
	GuiRect(0, 96, 159,159, forecolor);
	
	/* 更新 */
	GuiUpdateDisplayAll();
}

/* END */
