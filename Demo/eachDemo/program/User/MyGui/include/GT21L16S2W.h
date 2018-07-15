


#ifndef _GT21L16S2W_H_
#define _GT21L16S2W_H_


extern unsigned char r_dat_bat(unsigned long address,unsigned long byte_long,unsigned char *p_arr);

#define ASCII_5X7              1
#define ASCII_7X8              2
#define ASCII_6X12             4
#define ASCII_8X16             5
#define ASCII_12_A   	         11
#define ASCII_16_A             13


unsigned char ASCII_GetData(unsigned char ASCIICode,unsigned long ascii_kind,unsigned char* DZ_Data);
void gt_12_GetData (unsigned char MSB,unsigned char LSB,unsigned char *DZ_Data);
void gt_16_GetData (unsigned char MSB,unsigned char LSB,unsigned char *DZ_Data);
void GB_EXT_612(unsigned short FontCode,unsigned char *DZ_Data);
void GB_EXT_816(unsigned short FontCode,unsigned char *DZ_Data);
unsigned char UnicodeToGB2312(unsigned char *srcCode,unsigned char *destCode);
unsigned long Gb2311ToIndex(unsigned char *incode);
unsigned char GB2312ToUnicode(unsigned char *srcCode,unsigned char *destCode);


#endif
