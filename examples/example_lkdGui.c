#include <rtthread.h>
#if defined(RT_USING_FINSH)
#include <finsh.h>
#endif

#include "lkdGui.h"

void lkdGui_test(int argc, char** argv)
{

    /* 1.begin 移植相关
     * 1.1 添加用户字体：根据字体需求选择合适字体文件添加到项目工程(字体文件
     *     位于/lkdGui_source/port/fontDriver/,如果没有合适字体需要用户自
     *     己编写)。如选择ASCII_6_12.c和GB2312_12_12.c到项目工程。
     * 1.2 在userFontPort.c中填充相关函数。填充示例见下面的注释1.1:userFontPort.c填充。
     * 1.3 添加LCD显示驱动:根据液晶型号选择合适的液晶驱动到项目工程。(液晶驱动
     *     位于/lkdGui_source/port/lcdDriver/,如果没有合适驱动需要用户自
     *     己编写)。如选择UC1689Driver.c到项目工程,并添加头文件到项目路径。
     * 1.4 在lcdDriverPort.c中填充相关函数。填充示例见下面的注释1.2:lcdDriverPort.c填充。
     * 1.end 移植结束
     */

    /* 2.begin lkdGui使用
     * 2.1 lkdGui初始化:userAppPort.c是用户层接口。里面已经写好了初始化模板。
     *     用户只需要根据提示填充userAppPortInit()函数。
     * 2.2 在main函数的初始化程序中调用userAppPortInit()。完成lkdGui初始化。
     * 2.3 lkdGui运行:userAppPortRun()函数是Gui的调度运行函数。需要放在main
     *     函数的死循环中使其一直运行(运行频率用户自己决定,建议10ms执行一次)。
     * 2.4 用户程序添加位置:lkdGui使用窗口管理。用户在窗口的回调函数中添加相关程序。
     *     如userAppPort.c已经创建好了主窗口,其回调函数为UserMainWinFun().
     *     用户可以此函数中执行任何程序。关于窗口的具体使用可以参看doc文件夹中
     *     的program例程。填充示例见下面的注释2.1:UserMainWinFun()填充。
     */

    extern void userAppPortInit(void);
    extern void userAppPortRun(void);
    userAppPortInit();

    while(1){
        userAppPortRun();
        //msleep(10);
    };

}
#if defined(RT_USING_FINSH)
MSH_CMD_EXPORT(lkdGui_test, lkdGui API test);
#endif


/* 注释1.1:userFontPort.c填充 */
//1. 填充获取汉字函数
// static uint8_t GetDfontData(uint8_t code1, uint8_t code2,uint8_t *pBuff)
// {
//     /* 添加用户代码 */
//     extern uint8_t GetFontGb2312_12_12(uint8_t codeH, uint8_t codeL, uint8_t *pBuff);
//     GetFontGb2312_12_12(code1,code2,pBuff);
//     return 0;
// }
// //2. 填充获取ASCII函数
// static uint8_t GetSfontData(uint8_t code1, uint8_t *pBuff)
// {
//     /* 添加用户代码 */
//     extern uint8_t GetFontASCII_6_12(uint8_t code1, uint8_t *pBuff);
//     GetFontASCII_6_12(code1, pBuff);
//     return 0;
// }

// //2. 填充初始化函数
// void defaultFontInit(void)
// {
//     /* 根据字体要求做相应的修改 */

//     /* 此buff的大小由最大字模大小决定 */
// 	static uint8_t dataBuff[12*2];

// 	defaultFont.name = "汉字字模为12*12的GB2312,ASCII字模为6*12";
// 	defaultFont.dhigh = 12;
// 	defaultFont.dwide = 12;
// 	defaultFont.shigh = 6;
// 	defaultFont.swide = 12;
// 	defaultFont.pZmBuff = dataBuff;
// 	defaultFont.getDfont = GetDfontData;
// 	defaultFont.getSfont = GetSfontData;

//     /* 设置为系统默认字体 */
// 	GuiFontSet(&defaultFont);
//   GuiSetbackcolor(CWHITLE);
//   GuiSetForecolor(CBLACK);
// }

/* 注释1.2:lcdDriverPort.c填充 */
// //1. 必须填充此函数:将lkdGui缓冲区数据刷新到lcd.可以参考doc/program中的填充方式
// void GuiUpdateDisplayAll(void)
// {
//   /* 添加用户代码 */
// }
// //2. 必须填充此函数:gui最后所有的画图函数都会调用此函数，
// //   此函数决定绘图数据的存放。一般定义一个数组存放。可以参考doc/program中的使用方式。
// void GuiDrawPoint(lkdCoord x, lkdCoord y, lkdColour color)
// {
//   /* 添加用户代码 */
// }

// //3. 可选填充此函数:打开lcd显示
// void OpenLcdDisplay(void)
// {
//   /* 添加用户代码 */
// }

// //4. 此文件的其余函数也为可选填充此函数

/* 注释2.1:UserMainWinFun()填充 */
/* static void UserMainWinFun(void *param)
{
     static flag;

     if(flag == 0){//绘图等第一次进入窗口的相关执行动作
        GuiRowText(10,10,100,"lkdGui");
        flag = 1;
     }

     switch(keyIs){//根据按建值做相应动作。
         case UP  :xxx;break;
         case DOWN:xxx;break;
         case LEFT:xxx;break;
         case RIGHT:xxx;break;
         case OK   :xxx;break;//添加窗口等相关操作
         case CANCEL:
            flag = 0;break;//当取消按建执行时,销毁窗口，恢复窗口相关变量。
     }
} */
