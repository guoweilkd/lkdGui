/**
  * @file   lkdmyFont.c
  * @author  guoweilkd
  * @version V1.1.0
  * @date    2018/06/07
  * @brief  lkd字体库
  */

#include "lkdmyFont.h"
#include "lkdGuiFont.h"
#include "GT21L16S2W.h"
#include "zikuSpi.h"

/* lkd默认字体 */
lkdFont defaultFont;

/**
  *@brief 获取汉字字模
  *@param  code1,code2 汉字编码 高 低
  *@param  pBuff 字模buff
  *@retval 0
  */
static uint8_t f12GetDataD(uint8_t code1, uint8_t code2,uint8_t *pBuff)
{
	gt_12_GetData(code1,code2,pBuff);
	return 0;
}

/**
  *@brief 获取ASCII字模
  *@param  code1, 编码 
  *@param  pBuff 字模buff
  *@retval 0
  */
static uint8_t f12GetDataS(uint8_t code1,uint8_t *pBuff)
{
	ASCII_GetData(code1,ASCII_6X12,pBuff);
	return 0;
}

/**
  *@brief 字体初始化
  *@param  None
  *@retval None
  */
void defaultFontInit(void)
{
	static uint8_t f12Buff[24];
	
	ZiKuInit();
	
	defaultFont.name = "lkdTestFont";
	defaultFont.dhigh = 12;
	defaultFont.dwide = 12;
	defaultFont.pZmBuff = f12Buff;
	defaultFont.shigh = 12;
	defaultFont.swide = 6;
	defaultFont.getDfont = f12GetDataD;
	defaultFont.getSfont = f12GetDataS;
	GuiFontSet(&defaultFont);
}

/* END */
