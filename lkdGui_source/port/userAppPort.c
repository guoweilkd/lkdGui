/**
  * @file   userAppPort.c
  * @author  guoweilkd
  * @version V0.0.0
  * @date    2019/01/17
  * @brief  lkdGui用户应用编写文件。
  */

#include "lkdGui.h"

static void UserMainWinFun(void *param);

/* 用户主窗口 */
lkdWin userMainWin = {
    .x = 10,
    .y = 10,
    .wide = 100,
    .hight = 100,
    .title = "主窗口",
    .param = NULL,
    .WindowFunction = UserMainWinFun,
};

/**
  *@brief gui初始化参考函数
  *@param  None
  *@retval None
  */
void userAppPortInit(void)
{
    /* 1. 初始化lcd */

    /* 2. 初始化用户字体 */
    //defaultFontInit();

    /* 3. 初始化窗口,添加窗口 */
    GuiWinInit();
    GuiWinAdd(&userMainWin);

    /* 4. 更新屏幕 */
    GuiClearScreen(GuiGetbackcolor());
    OpenLcdDisplay();
    GuiUpdateDisplayAll();
}

/**
  *@brief gui运行函数
  *@param  None
  *@retval None
  */
void userAppPortRun(void)
{
    /* 窗口调度管理 */
    GuiWinDisplay();
}


static void UserMainWinFun(void *param)
 {
     //用户自定义代码。
 }