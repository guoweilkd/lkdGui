/**
  * @file   userFontPort.c
  * @author  guoweilkd
  * @version V0.0.0
  * @date    2018/04/18
  * @brief  lkdGui字体驱动接口，由移植者填充函数的具体内容。
  */

/* 字模规则:横置横排 */

#include <stdint.h>
#include "lkdGui.h"
#include "GT21L16S2W.h"

extern const unsigned char gb2312_12_12[8178][24];
extern const unsigned char ASCII_6_12[128][12];
extern const unsigned char ASCII_64_64[128][64*8];
extern unsigned char ASCII_8_16[96][16];
/* 字体控制实体 */
static lkdFont defaultFont;

/**
  *@brief 获取汉字字模
  *@param  code1, 编码 
  *@param  pBuff 字模buff,规则遵循上面的字模规则
  *@retval 0
  */
static uint8_t GetDfontData(uint8_t code1, uint8_t code2,uint8_t *pBuff)
{
    /* 添加用户代码 */
//	uint16_t offset;
//	
//	offset = ((code1 - 0xA1)*94 + (code2 - 0xA1));
//	for(uint8_t i = 0; i < 24; i++){
//		pBuff[i] = gb2312_12_12[offset][i];
//	}
extern uint8_t GetFontGb2312_12_12(uint8_t codeH, uint8_t codeL, uint8_t *pBuff);
GetFontGb2312_12_12(code1,code2,pBuff);
	//gt_12_GetData(code1,code2,pBuff);
    return 0;
}


/**
  *@brief 获取ASCII字模
  *@param  code1, 编码 
  *@param  pBuff 字模buff,规则遵循上面的字模规则
  *@retval 0
  */
static uint8_t GetSfontData(uint8_t code1, uint8_t *pBuff)
{
	uint16_t offset = code1 - 32; 
    /* 添加用户代码 */
//	for(uint8_t i = 0; i < 16; i++){
//		pBuff[i] = ASCII_8_16[offset][i];
//	}
//	for(uint16_t i = 0; i < 512; i++){
//		pBuff[i] = ASCII_64_64[code1][i];
//	}
//extern uint8_t GetFontASCII_8_16(uint8_t code1, uint8_t *pBuff);
	//GetFontASCII_8_16(code1,pBuff);
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
    /* 根据字体要求做相应的修改 */

    /* 此buff的大小由最大字模大小决定 */
	static uint8_t dataBuff[64*8];

	defaultFont.name = "汉字字模为12*12的GB2312,ASCII字模为5*7";
	defaultFont.dhigh = 12;
	defaultFont.dwide = 12;
	defaultFont.shigh = 16;
	defaultFont.swide = 8;
	defaultFont.pZmBuff = dataBuff;
	defaultFont.getDfont = GetDfontData;
	defaultFont.getSfont = GetSfontData;

    /* 设置为系统默认字体 */
	GuiFontSet(&defaultFont);
}

/* END */
