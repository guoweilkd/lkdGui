/**
  * @file   lkdGuiPublic.c
  * @author  guoweilkd
  * @version V1.1.0
  * @date    2018/05/30
  * @brief  lkdGui公共函数库
  */

#include "lkdGuiPublic.h"

/* lkd全局错误代码 */
uint32_t lkdErrorCode;

/**
  *@brief  全局错误变量记录
  *@param  fileCode 文件代号
  *@param  funCode 函数代号
  *@param  errorCode 错误代号
  *@retval None
  */
void SetlkdErrorCode(uint8_t fileCode,uint16_t funCode, uint8_t errorCode)
{
	lkdErrorCode = (fileCode << 24) + (funCode << 8) + (errorCode);
}

/**
  *@brief  获取全局错误变量记录
  *@param  None
  *@retval None
  */
uint32_t GetlkdErrorCode(void)
{
	return lkdErrorCode;
}

/* END */
