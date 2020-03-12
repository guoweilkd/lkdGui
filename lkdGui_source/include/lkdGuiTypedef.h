
#ifndef __LKDGUITYPEDEF_H
#define	__LKDGUITYPEDEF_H

#include <stdint.h>
#include "lkdGuiConfig.h"

#ifndef  NULL
#define NULL 0
#endif

/* lkdGui版本号 */
#define LKGGUI_VERSION "V000.000.001"

#define CWHITLE	0x00/* 白色 */
#define CBLACK	0x01/* 黑色 */

typedef int32_t lkdCoord;
typedef uint8_t lkdColour;

/* 定义位图结构体 */
typedef struct{
    uint8_t *bitmap;	/* 位图数组 */
    uint16_t wide;      /* 位图宽 */
    uint16_t high;      /* 位图高 */
    uint16_t beginx;    /* 位图开始坐标 */
    uint16_t beginy;    /* 位图开始坐标 */
}lkdBitmap;


/* lkd窗口定义 */
typedef struct{
    lkdCoord x;
    lkdCoord y;
    uint16_t wide;
    uint16_t hight;
    uint8_t   *title;   // 定义标题栏指针(NULL为不显示)
    void(*WindowFunction)(void *param); // 窗口对应的服务程序
    void * param;       //参数
}lkdWin;

/* lkd窗口管理 */
struct GuiWinManage{
    uint8_t pWin;
    lkdWin *winStack[GUIWINMANAGE_NUM];	
};

/* 滚动条 */
typedef struct{
    int16_t x;
    int16_t y;
    uint16_t hight;
    int16_t max;
    int16_t lump;
}lkdScroll;

/* 按钮 */
typedef struct{
    lkdCoord x;     /* 坐标 */
    lkdCoord y;
    uint8_t wide;
    uint8_t high;
    uint8_t flag;   /* 0 抬起状态 1 按下状态 */
    uint8_t *name;  /* 按键内容 */
}lkdButton;
enum ButtonState{
    BUTTON_UP,
    BUTTON_DOWN,
};

/* 进度条 */
typedef struct{
    lkdCoord x;     /* 坐标 */
    lkdCoord y;
    uint8_t wide;
    uint8_t high;
    uint8_t ratio; /* 当前进度 0~100 */
}lkdProgress;

/* lkd菜单节点定义 */
typedef struct lkdMenuNode{
	uint16_t nodeId;            /* 节点号 */
	uint8_t	*name;              /* 节点名称 */
	struct lkdMenuNode *pBro;   /* 下一个兄弟节点号 */
	struct lkdMenuNode *pSon;   /* 子节点号 */
	void *user;
}lkdMenuNode;

/* lkd菜单栈结构定义 */
typedef struct {
	uint8_t	index;
	lkdCoord cy;
	lkdMenuNode *pNode;
}MenuStack;

/* lkd菜单结构定义 */
typedef struct{
	lkdCoord x;         /* 菜单起始坐标 */
	lkdCoord y;
	uint16_t wide;
	uint16_t hight;
	uint8_t ItemsWide;  /* 菜单项宽 */
	uint8_t Itemshigh;  /* 菜单项高 */
	uint8_t index;      /* 菜单当前item */
	uint8_t count;      /* 菜单级数计数 */
	uint8_t stackNum;   /* 菜单栈大小 以MenuStack为单位 */
	MenuStack *stack;   /* 菜单栈 */
	lkdMenuNode *Root;  /* 菜单根节点 */
	void (* MenuDealWithFun)(void);/* 菜单处理函数 */
	
	/* 当前节点绘画临时保存 */
	lkdCoord cx;        /* 起始坐标 */
	lkdCoord cy;
	lkdMenuNode *pDraw; /* 绘画节点 */
	uint8_t nodeNum;    /* 当前父节点下的节点数 */
	uint8_t cNum;       /* 要绘画的节点数 */
}lkdMenu;

/* 字体对齐类型 */
typedef enum{
	FONT_LEFT,  /* 左对齐 */
	FONT_MID,   /* 居中 */
	FONT_RIGHT,	/* 右对齐 */
}FontFlag;

/* 字体结构 */
typedef struct{
	uint8_t *name;      /* 字体名称 */
	uint8_t swide;      /* ASCII取模宽 */
	uint8_t shigh;      /* ASCII取模高 */
	uint8_t dwide;      /* 汉字取模宽 */
	uint8_t dhigh;      /* 汉字取模高 */
	uint8_t *pZmBuff;   /* 存放单个字模buff */
	/* ASCII取模函数 */
	uint8_t (*getSfont)(uint8_t code1, uint8_t *pBuff);
	/* 汉字取模函数 */
	uint8_t (*getDfont)(uint8_t code1, uint8_t code2,uint8_t *pBuff);
}lkdFont;

/* 文本信息 */
typedef struct{
	lkdCoord x;         /* 坐标 */
	lkdCoord y;
	uint16_t wide;
	uint16_t high;
	uint16_t beginOffset;
	uint8_t wInterval;  /* 宽度间隔 */
	uint8_t hInterval;  /* 高度间隔 */
	uint8_t flag;       /* 0 正常显示 1反显 */
}fontTextInfo;

#endif /* __LKDGUITYPEDEF_H */

/* END */
