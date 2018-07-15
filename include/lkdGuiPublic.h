/**
  * @file   lkdGuiPublic.h
  * @author  guoweilkd
  * @version V1.1.0
  * @date    2018/05/30
  * @brief  lkdGui公共函数库
  */

#ifndef __LKDGUIPUBLIC_H
#define	__LKDGUIPUBLIC_H

#include "stdint.h"

/* 全局错误变量记录 */
void SetlkdErrorCode(uint8_t fileCode,uint16_t funCode, uint8_t errorCode);
/* 获取全局错误变量记录 */
uint32_t GetlkdErrorCode(void);

#endif /* __LKDGUIPUBLIC_H */

/* END */
