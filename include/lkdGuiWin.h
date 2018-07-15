/**
  * @file   lkdGuiWin.h
  * @author  guoweilkd
  * @version V0.0.0
  * @date    2018/06/03
  * @brief  lkdGui窗口管理
  */

#ifndef __LKDGUIWIN_H
#define	__LKDGUIWIN_H

#include "lkdGuiBasic.h"

/* 窗口最大嵌套数量 */
#define GUIWINMANAGE_NUM 16

/* lkd窗口定义 */
typedef struct{
	lkdCoord x;
	lkdCoord y;
	uint16_t wide;
	uint16_t hight;
	uint8_t   *title;// 定义标题栏指针(NULL为不显示)
	void(*WindowFunction)(void *param);// 窗口对应的服务程序
	void * param;//参数
}lkdWin;

/* lkd窗口管理 */
struct GuiWinManage{
	uint8_t pWin;
	lkdWin *winStack[GUIWINMANAGE_NUM];	
};

/* 添加窗口 */
int8_t GuiWinAdd(lkdWin *pWindow);
/* 显示窗口 */
void GuiWinDisplay(void);
/* 删除顶层窗口 */
void GuiWinDeleteTop(void);

#endif /* __LKDGUIWIN_H */

/* END */
