/**
  * @file   userApp.c
  * @author  guoweilkd
  * @version V0.0.0
  * @date    2018/07/13
  * @brief  lkdGui整体使用演示
  */
	
#include "userApp.h"
#include "keyDriver.h"
#include "lkdGuiMenu.h"
#include "lkdGuiWin.h"
#include "lkdGuiFont.h"
#include "lkdGuiControl.h"
#include "stdio.h"

/* 菜单按键 */
enum MenuKeyIs keyStatus;
/* 菜单句柄 */
lkdMenu HmiMenu;
/* 菜单栈 */
MenuStack userMenuStack[MENUSTACK_NUM];

/* 窗口定义 */
lkdWin homeWin = {0,0,160,160,NULL,HomeWinFun,NULL};/* 桌面窗口 */
lkdWin menuWin = {0,0,160,160,"菜单管理窗口",MenuWinFun,NULL};/* 菜单窗口 */

lkdWin LkdGuiWin = {0,0,160,160,"lkdGui介绍",LkdGuiWinFun,NULL};
lkdWin FontWin = {0,0,160,160,"字体介绍",FontWinFun,NULL};
lkdWin DrawLineWin = {0,0,160,160,"画线窗口",DrawLineWinFun,NULL};
lkdWin DrawImageWin = {0,0,160,160,"画图窗口",DrawImageWinFun,NULL};
lkdWin VScrollWin = {0,0,160,160,"垂直滚动条窗口",VScrollWinFun,NULL};
lkdWin ProGressWin = {5,30,145,70,"进度条窗口",ProGressWinFun,NULL};
lkdWin ButtonWin = {20,30,120,60,"按钮窗口",ButtonWinFun,NULL};

/* 基本函数节点 */
lkdMenuNode ImageNode = {11,"画图窗口",NULL,NULL,&DrawImageWin};
lkdMenuNode LineNode = {10,"画线窗口",&ImageNode,NULL,&DrawLineWin};
/* 控件子节点 */
lkdMenuNode VScrollNode = {10,"垂直滚动条窗口",NULL,NULL,&VScrollWin};
lkdMenuNode HScrollNode = {10,"水平滚动条窗口",&VScrollNode,NULL,NULL};
lkdMenuNode ProGressNode = {10,"进度条窗口",&HScrollNode,NULL,&ProGressWin};
lkdMenuNode ButtonNode = {10,"按钮窗口",&ProGressNode,NULL,&ButtonWin};

/* 测试节点 */

lkdMenuNode TestNode003 = {12,"节点003",NULL,NULL,NULL};
lkdMenuNode TestNode002 = {12,"节点002",&TestNode003,NULL,NULL};
lkdMenuNode TestNode001 = {12,"节点001",&TestNode002,NULL,NULL};

lkdMenuNode TestNode11 = {12,"节点十一",NULL,&TestNode001,NULL};
lkdMenuNode TestNode10 = {12,"节点十",&TestNode11,NULL,NULL};
lkdMenuNode TestNode9 = {12,"节点九",&TestNode10,NULL,NULL};
lkdMenuNode TestNode8 = {12,"节点八",&TestNode9,NULL,NULL};
lkdMenuNode TestNode7 = {12,"节点七",&TestNode8,&TestNode002,NULL};
lkdMenuNode TestNode6 = {12,"节点六",&TestNode7,NULL,NULL};
lkdMenuNode TestNode5 = {12,"节点五",&TestNode6,NULL,NULL};
lkdMenuNode TestNode4 = {12,"节点四",&TestNode5,NULL,NULL};
lkdMenuNode TestNode3 = {12,"节点三",&TestNode4,&TestNode001,NULL};
lkdMenuNode TestNode2 = {12,"节点二",&TestNode3,NULL,NULL};
lkdMenuNode TestNode1 = {12,"节点一",&TestNode2,NULL,NULL};

lkdMenuNode TestNode = {12,"测试节点",NULL,&TestNode1,NULL};
lkdMenuNode VersionNode = {12,"版本信息",&TestNode,NULL,NULL};
lkdMenuNode ControlNode = {12,"控件使用",&VersionNode,&ButtonNode,NULL};
lkdMenuNode WinNode = {12,"窗口介绍",&ControlNode,NULL,NULL};
lkdMenuNode MenuNode = {12,"菜单介绍",&WinNode,NULL,NULL};
lkdMenuNode FontNode = {12,"字体介绍",&MenuNode,NULL,&FontWin};
lkdMenuNode BasicNode = {2,"基本函数",&FontNode,&LineNode,NULL};
lkdMenuNode IntroNode = {1,"Gui介绍",&BasicNode,NULL,&LkdGuiWin};
lkdMenuNode RootNode = {0,"root",NULL,&IntroNode,NULL};

/**
  *@brief  菜单初始化
  *@param  None
  *@retval None
  */
void UserMenuInit(void)
{
	HmiMenu.x = 1;
	HmiMenu.y = 16;
	HmiMenu.wide = 158;
	HmiMenu.hight = 142;
	HmiMenu.Itemshigh = 15;
	HmiMenu.ItemsWide = 70;
	HmiMenu.stack = userMenuStack;
	HmiMenu.stackNum = MENUSTACK_NUM;
	HmiMenu.Root = &RootNode;/* 菜单句柄跟菜单节点绑定到一起 */
	HmiMenu.MenuDealWithFun = MenuControlFun;/* 菜单控制回掉函数 */
	GuiMenuInit(&HmiMenu);
}

/**
  *@brief  菜单项处理
  *@param  step 步骤 pNode 菜单节点
  *@retval None
  */
static void MenuItemDealWith(lkdMenuNode *pNode)
{
	if(pNode->pSon != NULL){//展开选中节点的菜单
		GuiMenuCurrentNodeSonUnfold(&HmiMenu);
	}
	else if(pNode->user != NULL){//打开菜单对应的窗口
		GuiWinAdd(pNode->user);
	}
}

/**
  *@brief  菜单控制函数
  *@param  None
  *@retval None
  */
void MenuControlFun(void)
{
	switch(keyStatus){
	case MKEY_UP:GuiMenuItemUpMove(&HmiMenu);break;
	case MKEY_DOWN:GuiMenuItemDownMove(&HmiMenu);break;
	case MKEY_LEFT:
	case MKEY_CANCEL:
		GuiMenuCurrentNodeHide(&HmiMenu);
		if(HmiMenu.count == 0){//检测到菜单退出信号
			GuiWinDeleteTop();
		}break;
	case MKEY_RIGHT:
	case MKEY_OK:
		MenuItemDealWith(GuiMenuGetCurrentpNode(&HmiMenu));
		break;
	}
}

/**
  *@brief  桌面窗口函数
  *@param  param 入口参数
  *@retval None
  */
void HomeWinFun(void *param)
{
	static uint8_t step = 0;
	uint8_t i,j;
	if(step == 0){//初始化
		lkdBitmap tImage;
		tImage.wide = 144;
		tImage.high = 40;
		tImage.beginx = 0;
		tImage.beginy = 0;
		tImage.bitmap = lkdGuiImage;
		GuiAreaBitMap(&tImage,homeWin.x + 7,homeWin.y + 20, 159, 60, 0);
		j = 110;
		for(i = 1; i < 24; i += 2){
			GuiHPointLine(homeWin.x + 1, i, j, 2, forecolor);
			j -= 2;
		}
		for(i=25;i<59;i+=2){
			GuiHPointLine(homeWin.x + 1, i, 159, 2, forecolor);
		}
		j = 70;
		for(i=59;i<78;i+=2){
			GuiHPointLine(homeWin.x + j, i, 159, 2, forecolor);
			j -= 2;
		}
		GuiHLine(homeWin.x+1,79,158,forecolor);
		GuiFillRect(homeWin.x+1,81,159,94, forecolor);
		GuiHLine(homeWin.x+1,96,158,forecolor);
		
		GuiRowText(homeWin.x+9,102,16,FONT_LEFT,"信");
		GuiRowText(homeWin.x+9,121,16,FONT_LEFT,"息");
		GuiRowText(homeWin.x+9,140,16,FONT_LEFT,"栏");
		GuiRLine(homeWin.x+30,96,158,forecolor);
		for(i = 0; i < 4; i++){
			GuiRowText(homeWin.x+31,96+2+i*16,90,FONT_MID,"----");
			GuiRPointLine(homeWin.x+31+91,96,96+15+i*16,2,forecolor);
			GuiRowText(homeWin.x+31+93,96+2+i*16,34,FONT_MID,"--");
			GuiHPointLine(homeWin.x+30,96+15+i*16,159,2,forecolor);
		}
		GuiUpdateDisplayAll();
		step = 1;
	}
	if(step == 1){
		uint8_t strTime[32];
		GuiExchangeColor();
		sprintf((char *)strTime,"20%02d-%02d-%02d   %02d:%02d:%02d",18,7,6,8,30,45);
		GuiRowText(homeWin.x+2,82,156,FONT_MID,strTime);
		GuiExchangeColor();
		GuiUpdateDisplayAll();
		step = 2;
	}
	if(step == 2){
	}
	/* 按键状态处理 */
	switch(keyStatus){
	case MKEY_UP:break;
	case MKEY_DOWN:break;
	case MKEY_LEFT:break;
	case MKEY_RIGHT:break;
	case MKEY_CANCEL:break;
	case MKEY_OK:
		step = 0;
		GuiWinAdd(&menuWin);/* 添加菜单窗口 */
		break;
	}
}

/**
  *@brief  菜单窗口函数
  *@param  param 入口参数
  *@retval None
  */
void MenuWinFun(void *param)
{
	if(HmiMenu.count == 0){
		GuiMenuCurrentNodeSonUnfold(&HmiMenu);
	}
	HmiMenu.MenuDealWithFun();
}

/**
  *@brief  lkdGui介绍窗口函数
  *@param  param 入口参数
  *@retval None
  */
void LkdGuiWinFun(void *param)
{
	static uint8_t step = 0;
	if(step == 0){
		uint8_t *textStr;
		fontTextInfo textInfo;
		textStr = "lkdGui是一款为单色显示屏制作的图形化界面,lkdGui主要定位在工业领域,用于设计简单漂亮的图形界面.";
		textInfo.x = 2;
		textInfo.y = 20;
		textInfo.wide = 156;
		textInfo.high = 120;
		textInfo.wInterval = 0;
		textInfo.hInterval = 3;
		textInfo.flag = 0;
		textInfo.beginOffset = thisFont->dwide * 2;
		GuiText(&textInfo, textStr);
		GuiUpdateDisplayAll();
		step = 1;
	}
	/* 按键状态处理 */
	switch(keyStatus){
	case MKEY_UP:break;
	case MKEY_DOWN:break;
	case MKEY_LEFT:break;
	case MKEY_RIGHT:break;
	case MKEY_CANCEL:
		step = 0;
		GuiWinDeleteTop();
		GuiMenuRedrawMenu(&HmiMenu);
		break;
	case MKEY_OK:break;
	}
}

/**
  *@brief  字体窗口函数
  *@param  param 入口参数
  *@retval None
  */
void FontWinFun(void *param)
{
	/* 按键状态处理 */
	switch(keyStatus){
	case MKEY_UP:break;
	case MKEY_DOWN:break;
	case MKEY_LEFT:break;
	case MKEY_RIGHT:break;
	case MKEY_CANCEL:
		GuiWinDeleteTop();
		GuiMenuRedrawMenu(&HmiMenu);
		break;
	case MKEY_OK:break;
	}
}

/**
  *@brief  垂直滚动条函数
  *@param  param 入口参数
  *@retval None
  */
void VScrollWinFun(void *param)
{
	static uint8_t step = 0;
	static lkdScroll scroll;
	if(step == 0){
		scroll.x = 60;
		scroll.y = 20;
		scroll.hight = 120;
		scroll.max = 1;
		scroll.lump = 0;
		step = 1;
	}
	if(step == 1){
		GuiVScroll(&scroll);
		GuiUpdateDisplayAll();
		step = 2;
	}
	/* 按键状态处理 */
	switch(keyStatus){
	case MKEY_UP:
		scroll.lump --;
		if(scroll.lump < 0){
			scroll.lump = scroll.max - 1;
		}
		step = 1;
		break;
	case MKEY_DOWN:
		scroll.lump ++;
		if(scroll.lump >= scroll.max){
			scroll.lump = 0;
		}
		step = 1;
	break;
	case MKEY_LEFT:
		scroll.max --;
		if(scroll.max < 1){
			scroll.lump = 15;
		}
		step = 1;
		break;
	case MKEY_RIGHT:
		scroll.max ++;
		if(scroll.max >= 15){
			scroll.lump = 1;
		}
		step = 1;
		break;
	case MKEY_CANCEL:
		step = 0;
		GuiWinDeleteTop();
		GuiMenuRedrawMenu(&HmiMenu);
		break;
	case MKEY_OK:break;
	}
}

/**
  *@brief  水平滚动条函数
  *@param  param 入口参数
  *@retval None
  */
void HScrollWinFun(void *param)
{
	static uint8_t step = 0;
	if(step == 0){
		step = 1;
	}
	/* 按键状态处理 */
	switch(keyStatus){
	case MKEY_UP:break;
	case MKEY_DOWN:break;
	case MKEY_LEFT:break;
	case MKEY_RIGHT:break;
	case MKEY_CANCEL:
		GuiWinDeleteTop();
		GuiMenuRedrawMenu(&HmiMenu);
		break;
	case MKEY_OK:break;
	}
}

/**
  *@brief  进度条函数
  *@param  param 入口参数
  *@retval None
  */
void ProGressWinFun(void *param)
{
	static uint8_t step = 0;
	static lkdProgress progress;
	lkdWin *pWin = &ProGressWin;
	if(step == 0){
		progress.x = pWin->x + 5;
		progress.y = pWin->y + 30;
		progress.wide = pWin->wide - 35;
		progress.ratio = 0;
		progress.high = thisFont->dhigh;
		GuiRowText(progress.x + progress.wide + 19,progress.y,6,FONT_MID,"%");
		step = 1;
	}
	if(step == 1){
		GuiProGress(&progress);
		GuiFillRect(progress.x + progress.wide + 1,progress.y,\
			progress.x + progress.wide + 18,progress.y + thisFont->dhigh, backcolor);
		char strRatio[4];
		sprintf(strRatio,"%d%",progress.ratio);
		GuiRowText(progress.x + progress.wide + 1,progress.y,18,FONT_MID,(uint8_t *)strRatio);
		GuiUpdateDisplayAll();
		step = 2;
	}
	/* 按键状态处理 */
	switch(keyStatus){
	case MKEY_UP:
		progress.ratio += 5;
		if(progress.ratio > 100){
			progress.ratio = 0;
		}
		step = 1;
		break;
	case MKEY_DOWN:break;
	case MKEY_LEFT:break;
	case MKEY_RIGHT:break;
	case MKEY_CANCEL:
		step = 0;
		GuiWinDeleteTop();
		GuiMenuRedrawMenu(&HmiMenu);
		break;
	case MKEY_OK:break;
	}
}

/**
  *@brief  按钮窗口函数
  *@param  param 入口参数
  *@retval None
  */
void ButtonWinFun(void *param)
{
	static uint8_t step = 0;
	static lkdButton button,button2;
	if(step == 0){
		button.x = ButtonWin.x + 5;
		button.y = ButtonWin.y + 30;
		button.high = thisFont->dhigh + 5;
		button.wide = thisFont->dwide * 2 + 15;
		button.name = "确认";
		
		button2.x = ButtonWin.x + 70;
		button2.y = ButtonWin.y + 30;
		button2.high = thisFont->dhigh + 5;
		button2.wide = thisFont->dwide * 2 + 15;
		button2.name = "取消";
		
		button.flag = 0;
		button2.flag = 1;
		
		step = 1;
	}
	if(step == 1){
		GuiButton(&button);
		GuiButton(&button2);
		GuiUpdateDisplayAll();
		step = 2;
	}
	
	/* 按键状态处理 */
	switch(keyStatus){
	case MKEY_UP:break;
	case MKEY_DOWN:break;
	case MKEY_LEFT:
		if(button.flag == 0){
			button.flag = 1;
			button2.flag = 0;
		}
		else{
			button.flag = 0;
			button2.flag = 1;
		}
		step = 1;
		break;
	case MKEY_RIGHT:break;
	case MKEY_CANCEL:
		step = 0;
		GuiWinDeleteTop();
		GuiMenuRedrawMenu(&HmiMenu);
		break;
	case MKEY_OK:break;
	}
}

/**
  *@brief  画线窗口
  *@param  param 入口参数
  *@retval None
  */
void DrawLineWinFun(void *param)
{
	static uint8_t step = 0;
	if(step == 0){
		for(uint8_t i = 0; i < 6; i++){
			GuiHPointLine(1, 20  + i*5,159, 6 - i, forecolor);
		}
		for(uint8_t i = 0; i < 9; i++){
			GuiRPointLine(3 + i *5, 46,159, 9 - i, forecolor);
		}
		GuiFillRect(50, 50, 150,150, forecolor);
		GuiRect(65, 65, 135,135, backcolor);
		GuiFillRect(80, 80, 120,120, backcolor);
		GuiBiasLine(80, 80,120, 120,forecolor);
		GuiBiasLine(80, 120,120, 80,forecolor);
		GuiUpdateDisplayAll();
		step = 1;
	}
	
	/* 按键状态处理 */
	switch(keyStatus){
	case MKEY_UP:break;
	case MKEY_DOWN:break;
	case MKEY_LEFT:break;
	case MKEY_RIGHT:break;
	case MKEY_CANCEL:
		step = 0;
		GuiWinDeleteTop();
		GuiMenuRedrawMenu(&HmiMenu);
		break;
	case MKEY_OK:break;
	}
}

/**
  *@brief  画图窗口
  *@param  param 入口参数
  *@retval None
  */
void DrawImageWinFun(void *param)
{
	static uint8_t step = 0;
	static lkdBitmap tImage;
	if(step == 0){
		tImage.wide = 144;
		tImage.high = 40;
		tImage.beginx = 0;
		tImage.beginy = 0;
		tImage.bitmap = lkdGuiImage;
		step = 1;
	}
	if(step == 1){
		GuiAreaBitMap(&tImage,homeWin.x + 8,homeWin.y + 61, 151, 99, 0);
		GuiRect(homeWin.x + 7,homeWin.y + 60, 152, 100, forecolor);
		GuiUpdateDisplayAll();
		step = 2;
	}
	/* 按键状态处理 */
	switch(keyStatus){
	case MKEY_UP:
		if(tImage.beginy < tImage.high){
			GuiFillRect(homeWin.x + 8,homeWin.y + 61, 151, 99, backcolor);
			tImage.beginy += 5;
		}
		step = 1;
		break;
	case MKEY_DOWN:
		if(tImage.beginy >= 5){
			tImage.beginy -= 5;
		}
		step = 1;
		break;
	case MKEY_LEFT:
		if(tImage.beginx < tImage.wide){
			tImage.beginx += 5;
		}
		step = 1;
		break;
	case MKEY_RIGHT:
		if(tImage.beginx >= 5){
			tImage.beginx -= 5;
		}
		step = 1;
		break;
	case MKEY_CANCEL:
		step = 0;
		GuiWinDeleteTop();
		GuiMenuRedrawMenu(&HmiMenu);
		break;
	case MKEY_OK:break;
	}
}

/**
  *@brief  用户菜单主函数
  *@param  None
  *@retval None
  */
void userAppMain(void)
{
	keyStatus = GetMenuKeyState();
	SetMenuKeyIsNoKey();
	GuiWinDisplay();
}

/**
  *@brief  用户应用初始化
  *@param  None
  *@retval None
  */
void userAppInit(void)
{
	UserMenuInit();
	GuiSetForecolor(1);
	GuiSetbackcolor(0);
	GuiWinAdd(&homeWin);
}

uint8_t lkdGuiImage[] = {
/*--  lkdGui = 144 x 40  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0xFF,0xE7,0xFE,0x00,0x00,
0x00,0x3F,0xF0,0x00,0x1F,0xFE,0x00,0x00,0x00,0x3F,0x80,0x00,0x00,0xFF,0xE7,0xFE,
0x00,0x00,0x00,0x3F,0xF0,0x00,0x7F,0xFE,0x00,0x00,0x00,0x7F,0xC0,0x00,0x00,0xFF,
0xE7,0xFE,0x00,0x00,0x00,0x3F,0xF0,0x01,0xFF,0xFE,0x00,0x00,0x00,0x7F,0xC0,0x00,
0x00,0xFF,0xE7,0xFE,0x00,0x00,0x00,0x3F,0xF0,0x03,0xFF,0xFE,0x00,0x00,0x00,0x7F,
0xC0,0x00,0x00,0xFF,0xE7,0xFE,0x00,0x00,0x00,0x3F,0xF0,0x07,0xFF,0xFE,0x00,0x00,
0x00,0x7F,0xC0,0x00,0x00,0xFF,0xE7,0xFE,0x00,0x00,0x00,0x3F,0xF0,0x0F,0xFF,0xFE,
0x00,0x00,0x00,0x7F,0xC0,0x00,0x00,0xFF,0xE7,0xFE,0x00,0x00,0x00,0x3F,0xF0,0x1F,
0xFF,0xFE,0x00,0x00,0x00,0x3F,0x80,0x00,0x00,0xFF,0xE7,0xFE,0x00,0x00,0x00,0x3F,
0xF0,0x1F,0xFF,0xFE,0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0xFF,0xE7,0xFE,0x3F,0xF0,
0x1F,0xFF,0xF0,0x3F,0xFF,0xFE,0x7F,0xCF,0xFC,0xFF,0xE0,0x00,0x00,0xFF,0xE7,0xFE,
0x7F,0xF0,0x7F,0xFF,0xF0,0x3F,0xFF,0xFE,0x7F,0xCF,0xFC,0xFF,0xE0,0x00,0x00,0xFF,
0xE7,0xFE,0xFF,0xE0,0xFF,0xFF,0xF0,0x7F,0xFF,0xFE,0x7F,0xCF,0xFC,0xFF,0xE0,0x00,
0x00,0xFF,0xE7,0xFE,0xFF,0xE1,0xFF,0xFF,0xF0,0x7F,0xFC,0x00,0x7F,0xCF,0xFC,0xFF,
0xE0,0x00,0x00,0xFF,0xE7,0xFF,0xFF,0xC3,0xFF,0xFF,0xF0,0x7F,0xF8,0x00,0x7F,0xCF,
0xFC,0xFF,0xE0,0x00,0x00,0xFF,0xE7,0xFF,0xFF,0xC7,0xFF,0xFF,0xF0,0x7F,0xF1,0xFF,
0xFF,0xCF,0xFC,0xFF,0xE0,0x00,0x00,0xFF,0xE7,0xFF,0xFF,0x87,0xFF,0xFF,0xF0,0x7F,
0xF1,0xFF,0xFF,0xCF,0xFC,0xFF,0xE0,0x00,0x00,0xFF,0xE7,0xFF,0xFF,0x8F,0xFF,0xFF,
0xF0,0x7F,0xE1,0xFF,0xFF,0xCF,0xFC,0xFF,0xE0,0x00,0x00,0xFF,0xE7,0xFF,0xFF,0x0F,
0xFF,0xFF,0xF0,0x7F,0xE1,0xFF,0xFF,0xCF,0xFC,0xFF,0xE0,0x00,0x00,0xFF,0xE7,0xFF,
0xFF,0x0F,0xFF,0xFF,0xF0,0x7F,0xE1,0xFF,0xFF,0xCF,0xFC,0xFF,0xE0,0x00,0x00,0xFF,
0xE7,0xFF,0xFF,0x0F,0xFC,0x3F,0xF0,0x7F,0xF1,0xFF,0xFF,0xCF,0xFC,0xFF,0xE0,0x00,
0x00,0xFF,0xE7,0xFF,0xFF,0x8F,0xFC,0x3F,0xF0,0x7F,0xF1,0xFF,0xFF,0xCF,0xFC,0xFF,
0xE0,0x00,0x00,0xFF,0xE7,0xFF,0xFF,0x8F,0xFC,0x3F,0xF0,0x7F,0xF9,0xFF,0xFF,0xCF,
0xFC,0xFF,0xE0,0x00,0x00,0xFF,0xE7,0xFF,0xFF,0xCF,0xFC,0x3F,0xF0,0x3F,0xFF,0xFF,
0xFF,0xCF,0xFC,0xFF,0xE0,0x00,0x00,0xFF,0xE7,0xFE,0xFF,0xCF,0xFF,0xFF,0xF0,0x3F,
0xFF,0xFF,0xFF,0xFF,0xFC,0xFF,0xE0,0x00,0x00,0xFF,0xE7,0xFE,0xFF,0xCF,0xFF,0xFF,
0xF0,0x1F,0xFF,0xFF,0xFF,0xFF,0xFC,0xFF,0xE0,0x00,0x00,0xFF,0xE7,0xFE,0xFF,0xE7,
0xFF,0xFF,0xE0,0x0F,0xFF,0xFF,0xFF,0xFF,0xFC,0xFF,0xE0,0x00,0x00,0xFF,0xE7,0xFE,
0x7F,0xE7,0xFF,0xFF,0xE0,0x0F,0xFF,0xFF,0xFF,0xFF,0xF8,0xFF,0xE0,0x00,0x00,0xFF,
0xE7,0xFE,0x7F,0xF3,0xFF,0xFF,0xC0,0x07,0xFF,0xFF,0xFF,0xFF,0xF8,0xFF,0xE0,0x00,
0x00,0xFF,0xE7,0xFE,0x7F,0xF1,0xFF,0xFF,0xC0,0x03,0xFF,0xFF,0xDF,0xFF,0xF0,0xFF,
0xE0,0x00,0x00,0xFF,0xE7,0xFE,0x3F,0xF8,0xFF,0xFF,0x80,0x01,0xFF,0xFF,0x8F,0xFF,
0xF0,0xFF,0xE0,0x00,0x00,0xFF,0xE7,0xFE,0x3F,0xF8,0xFF,0xFF,0x00,0x01,0xFF,0xFF,
0x0F,0xFF,0xE0,0xFF,0xE0,0x00,0x00,0xFF,0xE7,0xFE,0x1F,0xF8,0x7F,0xFE,0x00,0x00,
0x7F,0xFE,0x07,0xFF,0xC0,0xFF,0xE0,0x00,0x00,0xFF,0xE7,0xFE,0x1F,0xF8,0x3F,0xF8,
0x00,0x00,0x1F,0xF8,0x03,0xFF,0x00,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
/* END */
