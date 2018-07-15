/**
  * @file   userApp.h
  * @author  guoweilkd
  * @version V0.0.0
  * @date    2018/07/13
  * @brief  lkdGui整体使用演示
  */

#ifndef __USERAPP_H
#define __USERAPP_H

#include "stdint.h"
/* 菜单栈大小 */
#define MENUSTACK_NUM 8

extern uint8_t lkdGuiImage[];
void MenuControlFun(void);
void HomeWinFun(void *param);
void MenuWinFun(void *param);
void LkdGuiWinFun(void *param);
void FontWinFun(void *param);
void ControlWinFun(void *param);
void DrawLineWinFun(void *param);
void DrawImageWinFun(void *param);
void ButtonWinFun(void *param);
void ProGressWinFun(void *param);
void HScrollWinFun(void *param);
void VScrollWinFun(void *param);
#endif /* __USERAPP_H */

/* END */






