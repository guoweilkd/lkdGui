/**
  * @file   menutest.h
  * @author  guoweilkd
  * @version V0.0.0
  * @date    2018/06/30
  * @brief  菜单使用Demo
  */
#include "menutest.h"
#include "keyDriver.h"
#include "lkdGuiMenu.h"
#include "lkdGuiWin.h"

/* 菜单按键 */
enum MenuKeyIs keyStatus;
/* 菜单句柄 */
lkdMenu HmiMenu;
/* 菜单栈 */
#define MENUSTACK_NUM 8
MenuStack userMenuStack[MENUSTACK_NUM];

/* 函数申明 */
static void HomeFun(void);
static void MenuFun(void);
static void Win0Fun(void);
static void Win1Fun(void);
static void Win2Fun(void);

/* 窗口定义 */
lkdWin homeWin = {0,0,160,160,NULL,HomeFun};/* 桌面窗口 */
lkdWin menuWin = {0,0,160,160,"菜单窗口",MenuFun};/* 菜单窗口 */
lkdWin win0 = {0,0,160,160,"lkdGui介绍",Win0Fun};
lkdWin win1 = {0,0,160,160,"测试窗口",Win1Fun};
lkdWin win2 = {20,20,140,100,"测试窗口",Win2Fun};

/* 菜单节点定义 */
lkdMenuNode Node33 = {33,"三级菜单4", NULL,   NULL,NULL};
lkdMenuNode Node32 = {32,"三级菜单3", &Node33,NULL,NULL};
lkdMenuNode Node31 = {31,"三级菜单2", &Node32,NULL,NULL};
lkdMenuNode Node30 = {30,"三级菜单1", &Node31,NULL,&win2};

lkdMenuNode Node29 = {29,"二级菜单17", NULL,    NULL,NULL};
lkdMenuNode Node28 = {28,"二级菜单16", &Node29, NULL,NULL};
lkdMenuNode Node27 = {27,"二级菜单15", &Node28, NULL,NULL};
lkdMenuNode Node26 = {26,"二级菜单14", &Node27, NULL,NULL};
lkdMenuNode Node25 = {25,"二级菜单13", &Node26, NULL,NULL};
lkdMenuNode Node24 = {24,"二级菜单12", &Node25, NULL,NULL};
lkdMenuNode Node23 = {23,"二级菜单11", &Node24, NULL,NULL};
lkdMenuNode Node22 = {22,"二级菜单10", &Node23, NULL,NULL};
lkdMenuNode Node21 = {21,"二级菜单9",  &Node22, NULL,NULL};
lkdMenuNode Node20 = {20,"二级菜单8",  &Node21, NULL,NULL};

lkdMenuNode Node19 = {19,"二级菜单7", NULL,    NULL,NULL};
lkdMenuNode Node18 = {18,"二级菜单6", &Node19, NULL,NULL};
lkdMenuNode Node17 = {17,"二级菜单5", &Node18, NULL,NULL};
lkdMenuNode Node16 = {16,"二级菜单4", &Node17, NULL,NULL};
lkdMenuNode Node15 = {15,"二级菜单3", &Node16, &Node30,NULL};
lkdMenuNode Node14 = {14,"二级菜单2", &Node15, NULL,&win1};
lkdMenuNode Node13 = {13,"二级菜单1", &Node14, NULL,NULL};

lkdMenuNode Node12 = {12,"一级菜单12",NULL,   NULL,   NULL};
lkdMenuNode Node11 = {11,"一级菜单11",&Node12,NULL,		NULL};
lkdMenuNode Node10 = {10,"一级菜单10",&Node11,NULL,		NULL};
lkdMenuNode Node9 = {9,"一级菜单9",		&Node10,&Node20,NULL};
lkdMenuNode Node8 = {8,"一级菜单8",		&Node9,	NULL,		NULL};
lkdMenuNode Node7 = {7,"一级菜单7",		&Node8,	NULL,		NULL};
lkdMenuNode Node6 = {6,"一级菜单6",		&Node7,	NULL,		NULL};
lkdMenuNode Node5 = {5,"一级菜单5",		&Node6,	NULL,		NULL};
lkdMenuNode Node4 = {4,"一级菜单4",		&Node5,	NULL,		NULL};
lkdMenuNode Node3 = {3,"一级菜单3",		&Node4,	NULL,		NULL};
lkdMenuNode Node2 = {2,"一级菜单2",		&Node3,	&Node13,NULL};
lkdMenuNode Node1 = {1,"一级菜单1",		&Node2,	NULL,		&win0};
lkdMenuNode Node0 = {0,"root",				NULL,	  &Node1,		NULL};


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
	HmiMenu.stackNum = 8;
	HmiMenu.Root = &Node0;/* 菜单句柄跟菜单节点绑定到一起 */
	HmiMenu.MenuDealWithFun = MenuControlFun;/* 菜单控制回掉函数 */
	GuiMenuInit(&HmiMenu);
}

/**
  *@brief  桌面窗口实体
  *@param  None
  *@retval None
  */
static void HomeFun(void)
{
	//用户应用代码:画图等
	static uint8_t step;
	if(step == 0){
		GuiRect(homeWin.x + 10,homeWin.y + 10,homeWin.x + 40,homeWin.y + 40,forecolor);
		step = 1;
	}
	/* 按键状态处理 */
	switch(keyStatus){
	case MKEY_UP:break;
	case MKEY_DOWN:break;
	case MKEY_LEFT:break;
	case MKEY_RIGHT:break;
	case MKEY_CANCEL:step = 0;break;
	case MKEY_OK:
		step = 0;
		GuiWinAdd(&menuWin);
		break;
	}
}

/**
  *@brief  菜单窗口实体
  *@param  None
  *@retval None
  */
static void MenuFun(void)
{
	if(HmiMenu.count == 0){
		GuiMenuCurrentNodeSonUnfold(&HmiMenu);
	}
	HmiMenu.MenuDealWithFun();
}

/**
  *@brief  窗口0实体函数
  *@param  None
  *@retval None
  */
static void Win0Fun(void)
{
	//用户应用代码:画图等
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
  *@brief  窗口1实体函数
  *@param  None
  *@retval None
  */
static void Win1Fun(void)
{
	//用户应用代码:画图等
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
  *@brief  窗口2实体函数
  *@param  None
  *@retval None
  */
static void Win2Fun(void)
{
	//用户应用代码:画图等
	
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

/* END */
