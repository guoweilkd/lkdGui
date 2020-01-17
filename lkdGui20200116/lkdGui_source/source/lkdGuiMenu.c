/**
  * @file   lkdGuiMenu.c
  * @author  guoweilkd
  * @version V0.0.0
  * @date    2018/06/05
  * @brief  lkdGui菜单管理
  */

#include "lkdGui.h"

/**
  *@brief  菜单兄弟节点插入
  *@param  bNode 前一个兄弟节点
  *@param  pNode 要插入的节点
  *@retval None
  */
void GuiMenuBroNodeInsert(lkdMenuNode *bNode, lkdMenuNode *pNode)
{
	lkdMenuNode *tNode;
	tNode = bNode->pBro;
	bNode->pBro = pNode;
	pNode->pBro = tNode;
}

/**
  *@brief  菜单子节点插入
  *@param  fNode 父节点
  *@param  pNode 要插入的节点
  *@retval None
  */
void GuiMenuSonNodeInsert(lkdMenuNode *fNode, lkdMenuNode *pNode)
{
	lkdMenuNode *tNode;
	tNode = fNode->pSon;
	fNode->pSon = pNode;
	pNode->pBro = tNode;
}

/**
  *@brief  菜单节点删除
  *@param  pMenu
  *@param  node 要删除的节点ID
  *@retval 0 删除成功 1 fbNode和thisNode没有关系
  */
uint8_t GuiMenuNodeDelete(lkdMenuNode *fbNode, lkdMenuNode *thisNode)
{
	if(fbNode->pSon == thisNode){
		fbNode->pSon = thisNode->pSon;
	}
	else if(fbNode->pBro == thisNode){
		fbNode->pBro = thisNode->pBro;
	}
	else{
		return 1;
	}
	return 0;
}

/**
  *@brief  获取兄弟节点数
  *@param  pbeginNode 起始节点
  *@retval 节点数
  */
static uint8_t GetbNodesNum(const lkdMenuNode *pbeginNode)
{
	uint8_t nodeNum = 0;
	while(pbeginNode != NULL){
		nodeNum ++;
		pbeginNode = pbeginNode->pBro;
	}
	return nodeNum;
}

/**
  *@brief  获取当前节点的指针
  *@param  pM 菜单句柄
  *@retval NULL 没找到 lkdMenuNode 当前节点的指针
  */
lkdMenuNode *GetpNodeFromIndex(lkdMenu *pM)
{
	lkdMenuNode *tpNode = pM->pDraw;
	uint8_t nodeNum = 0;
	while(tpNode != NULL){
		if(nodeNum == pM->index){
			return tpNode;
		}
		nodeNum ++;
		tpNode = tpNode->pBro;
	}
	return NULL;
}
/**
  *@brief  获取选中节点的绘制y坐标
  *@param  pM
  *@param  index 索引
  *@param  cy y开始绘制坐标
  *@retval y坐标
  */
static lkdCoord GetCheckedNodeDrawy(lkdMenu *pM, uint8_t index, lkdCoord cy)
{
	uint8_t cNum;
	cNum = (pM->hight - 1 - (cy - pM->y)) / pM->Itemshigh;
	if(index >= cNum){
		return (lkdCoord)(cy + (cNum - 1)*pM->Itemshigh);
	}
	else{
		return (lkdCoord)(cy + index*pM->Itemshigh);
	}
}

/**
  *@brief  获取应该绘制的节点数目，并修改绘制坐标参考
  *@param  pM 菜单句柄
  *@param  pDraw 绘制节点开始处
  *@param  drawy 开始绘制坐标参考
  *@retval 绘制节点数
  */
static uint8_t GetDrawNodes(const lkdMenu *pM,const lkdMenuNode *pDraw,lkdCoord *drawy)
{
	uint8_t nodeNum,DrawNodeNum;
	int16_t ty = *drawy;
	nodeNum = GetbNodesNum(pDraw);
	DrawNodeNum = (pM->hight - 1 - (*drawy - pM->y)) / pM->Itemshigh;
	if(DrawNodeNum >= nodeNum){//可绘制的节点多余总节点
		return nodeNum;
	}
	/* 可绘制的节点小于总节点 */
	while(1){
		DrawNodeNum ++;
		ty -= pM->Itemshigh;
		if(ty < pM->y){
			ty += pM->Itemshigh;
			DrawNodeNum --;
			break;
		}
		if(DrawNodeNum == nodeNum){
			break;
		}
	}
	*drawy = ty;
	return DrawNodeNum;
}

static uint8_t GetDrawNodesNum(const lkdMenu *pM,const lkdMenuNode *pDraw,lkdCoord drawy)
{
	uint8_t nodeNum,DrawNodeNum;
	nodeNum = GetbNodesNum(pDraw);
	DrawNodeNum = (pM->hight - 1 - (drawy - pM->y)) / pM->Itemshigh;
	if(DrawNodeNum >= nodeNum){//可绘制的节点多余总节点
		DrawNodeNum = nodeNum;
	}
	return DrawNodeNum;
}
/**
  *@brief  绘制的节点
  *@param  pM 菜单句柄
  *@param  pthisNode 绘制节点开始处
  *@param  beginy 开始绘制坐标
  *@param  index 索引
  *@param  cNum 可绘制节点数
  *@retval None
  */
static void DrawNodes(lkdMenu *pM,lkdMenuNode *pthisNode,lkdCoord x,\
	lkdCoord beginy,uint8_t index,uint8_t cNum)
{
	uint8_t indexOffset = 0;
	lkdColour forecolor,backcolor; 

	forecolor = GuiGetForecolor();
	backcolor=  GuiGetbackcolor();

	/* 确定从哪个节点开始画 */
	if(cNum <= index){
		indexOffset = index - cNum + 1;
		for(uint8_t i = 0; i < indexOffset; i ++){
			pthisNode = pthisNode->pBro;
		}
	}
	GuiFillRect(x,beginy,x + pM->ItemsWide - 1,beginy + cNum*pM->Itemshigh, backcolor);
	for(uint8_t i = 0; i < cNum; i ++){
		if(indexOffset + i == index){
			GuiFillRect(x + 1,beginy + 1 + i*pM->Itemshigh,\
				x + pM->ItemsWide - 1, beginy + (i+1)*pM->Itemshigh - 1, forecolor);
			GuiExchangeColor();
			GuiRowText(x + 2,beginy + 2 + i*pM->Itemshigh,pM->ItemsWide - 3,FONT_LEFT,pthisNode->name);
			if(pthisNode->pSon != NULL){
				GuiRowText(x + pM->ItemsWide - 8,beginy + 2 + i*pM->Itemshigh,6,FONT_LEFT,">");
			}
			GuiExchangeColor();
		}
		else{
			GuiRowText(x + 2,beginy + 2 + i*pM->Itemshigh,pM->ItemsWide - 3,FONT_LEFT,pthisNode->name);
			if(pthisNode->pSon != NULL){
				GuiRowText(x + pM->ItemsWide - 8,beginy + 2 + i*pM->Itemshigh,6,FONT_LEFT,">");
			}
		}
		GuiHLine(x + 1,beginy + (i+1)*pM->Itemshigh,x + pM->ItemsWide - 1, forecolor);
		pthisNode = pthisNode->pBro;
	}
	GuiHLine(x + 1,beginy,x + pM->ItemsWide - 1, forecolor);
	if(beginy + cNum*pM->Itemshigh + 1 <= pM->y + pM->hight - 1){
		GuiHLine(x + 1,beginy + cNum*pM->Itemshigh + 1,x + pM->ItemsWide - 1, forecolor);
	}
	GuiRLine(x, beginy,beginy + cNum*pM->Itemshigh + 1, forecolor);
	GuiRLine(x + pM->ItemsWide, beginy,beginy + cNum*pM->Itemshigh + 1, forecolor);
	if(pM->x + pM->wide > x + pM->ItemsWide){
		GuiRLine(x + pM->ItemsWide + 1, beginy,beginy + cNum*pM->Itemshigh + 1, forecolor);
	}
}

/**
  *@brief  画菜单
  *@param  pM
  *@retval None
  */
static void DrawMenu(lkdMenu *pM)
{
	int8_t tCount;
	lkdColour backcolor; 

	backcolor = GuiGetbackcolor();

	/* 菜单范围可显示的级数 */
	tCount = pM->wide / pM->ItemsWide;
	if(tCount - pM->count >= 0){
		/* 根据上一级计算本级变量信息 */
		pM->cy = GetCheckedNodeDrawy(pM,pM->stack[pM->count - 1].index,\
			pM->stack[pM->count - 1].cy);
		pM->cNum = GetDrawNodes(pM, pM->pDraw, &pM->cy);
		pM->cx = (pM->count - 1)*pM->ItemsWide + pM->x;
		DrawNodes(pM, pM->pDraw, pM->cx,pM->cy, pM->index, pM->cNum);
	}
	else{
		uint8_t index,cNum;
		int16_t cy;
		GuiFillRect(pM->x, pM->y, pM->x + pM->wide - 1, pM->y + pM->hight - 1, backcolor);
		for(uint8_t i = 1; i < tCount; i++){/* 补全上级菜单 */
			index = pM->stack[pM->count - tCount + i].index;
			cy = pM->stack[pM->count - tCount + i].cy;
			cNum = GetDrawNodesNum(pM,pM->stack[pM->count - tCount + i].pNode,cy);
			DrawNodes(pM, pM->stack[pM->count - tCount + i].pNode,\
				(i-1)*pM->ItemsWide + pM->x, cy, index, cNum);
		}
		/* 画最新菜单 */
		pM->cy = GetCheckedNodeDrawy(pM,pM->stack[pM->count - 1].index,pM->stack[pM->count - 1].cy);
		pM->cNum = GetDrawNodes(pM, pM->pDraw, &pM->cy);
		pM->cx = (tCount - 1)*pM->ItemsWide + pM->x;
		DrawNodes(pM, pM->pDraw, pM->cx, pM->cy, pM->index, pM->cNum);
	}
}

/**
  *@brief  画菜单
  *@param  pM
  *@retval None
  */
static void DrawAllMenu(lkdMenu *pM)
{
	int8_t tCount;
	lkdColour backcolor; 

	backcolor = GuiGetbackcolor();

	/* 菜单范围可显示的级数 */
	tCount = pM->wide / pM->ItemsWide;
	if(tCount - pM->count >= 0){
		lkdCoord tcy;
		for(uint8_t i = 1; i < pM->count; i ++){
			tcy = GetCheckedNodeDrawy(pM,pM->stack[i- 1].index,pM->stack[i-1].cy);
			pM->cNum = GetDrawNodes(pM, pM->stack[i].pNode, &tcy);
			pM->cx = (i - 1)*pM->ItemsWide + pM->x;
			DrawNodes(pM, pM->stack[i].pNode, pM->cx,tcy, pM->stack[i].index, pM->cNum);
		}
		pM->cNum = GetDrawNodes(pM, pM->pDraw, &pM->cy);
		pM->cx = (pM->count - 1)*pM->ItemsWide + pM->x;
		DrawNodes(pM, pM->pDraw, pM->cx,pM->cy, pM->index, pM->cNum);
	}
	else{
		uint8_t index,cNum;
		int16_t cy;
		GuiFillRect(pM->x, pM->y, pM->x + pM->wide - 1, pM->y + pM->hight - 1, backcolor);
		for(uint8_t i = 1; i < tCount; i++){/* 补全上级菜单 */
			index = pM->stack[pM->count - tCount + i].index;
			cy = pM->stack[pM->count - tCount + i].cy;
			cNum = GetDrawNodesNum(pM,pM->stack[pM->count - tCount + i].pNode,cy);
			DrawNodes(pM, pM->stack[pM->count - tCount + i].pNode,\
				(i-1)*pM->ItemsWide + pM->x, cy, index, cNum);
		}
		/* 画最新菜单 */
		pM->cy = GetCheckedNodeDrawy(pM,pM->stack[pM->count - 1].index,pM->stack[pM->count - 1].cy);
		pM->cNum = GetDrawNodes(pM, pM->pDraw, &pM->cy);
		pM->cx = (tCount - 1)*pM->ItemsWide + pM->x;
		DrawNodes(pM, pM->pDraw, pM->cx, pM->cy, pM->index, pM->cNum);
	}
}

/**
  *@brief  重绘菜单
  *@param  pM
  *@retval None
  */
static void RedrawMenu(lkdMenu *pM)
{
	int8_t tCount,offset;
	lkdColour backcolor; 
	
	backcolor = GuiGetbackcolor();

	/* 菜单范围可显示的级数 */
	tCount = pM->wide / pM->ItemsWide;
	if(tCount - pM->count >= 0){
		offset = 1;
		tCount = pM->count;
	}
	else{
		offset = pM->count - tCount + 1;
	}
	GuiFillRect(pM->x,pM->y,pM->x + pM->wide - 1,pM->y + pM->hight - 1, backcolor);
	for(uint8_t i = 0; i < tCount; i++){
		pM->cy = pM->stack[i + offset].cy;
		pM->cNum = GetDrawNodesNum(pM,pM->stack[i + offset].pNode,pM->cy);
		pM->cx = i*pM->ItemsWide + pM->x;
		pM->index = pM->stack[i + offset].index;
		DrawNodes(pM, pM->stack[i + offset].pNode, pM->cx, pM->cy, pM->index, pM->cNum);
	}
}

/**
  *@brief  菜单节点所有子节点的显示
  *@param  pM
  *@param  fNode 父节点
  *@retval 0 显示添加成功 1 栈不够用了
  */
static uint8_t GuiMenuNodesDisplay(lkdMenu *pM,lkdMenuNode *node)
{
	if(pM->count < pM->stackNum){//判断栈是否溢出
		/* 压栈上一级节点有用信息 */
		pM->stack[pM->count].index = pM->index;
		pM->stack[pM->count].pNode = pM->pDraw;
		pM->stack[pM->count].cy = pM->cy;
		
		/* 初始化此级节点有关信息 */
		pM->count ++;
		pM->index = 0;
		pM->pDraw = node;
		pM->nodeNum = GetbNodesNum(pM->pDraw);
		DrawMenu(pM);
		return 0;
	}
	return 1;
}

/**
  *@brief  菜单当前节点隐藏
  *@param  pM
  *@retval 0 显示添加成功 1 没有可隐藏的
  */
uint8_t GuiMenuCurrentNodeHide(lkdMenu *pM)
{
	if(pM->count >= 1){
		pM->count --;
	}
	if(pM->count < pM->stackNum){//判断栈是否为空
		RedrawMenu(pM);
		pM->index = pM->stack[pM->count].index;
		pM->pDraw = pM->stack[pM->count].pNode;
		pM->cy = pM->stack[pM->count].cy;
		pM->nodeNum = GetbNodesNum(pM->pDraw);
		GuiUpdateDisplayAll();
		return 0;
	}
	return 1;
}

/**
  *@brief  菜单当前节点展开
  *@param  pM
  *@retval 0 成功 1 失败
  */
uint8_t GuiMenuCurrentNodeSonUnfold(lkdMenu *pM)
{
	lkdMenuNode *thisNode;
	thisNode = GetpNodeFromIndex(pM);
	if(thisNode != NULL && thisNode->pSon != NULL){
		GuiMenuNodesDisplay(pM,thisNode->pSon);
		GuiUpdateDisplayAll();
		return 0;
	}
	return 1;
}

/**
  *@brief  重绘菜单
  *@param  pM 菜单句柄
  *@retval None
  */
void GuiMenuRedrawMenu(lkdMenu *pM)
{
	if(pM->count >= 1){
		DrawAllMenu(pM);
		GuiUpdateDisplayAll();
	}
}
/**
  *@brief  菜单项向上移动
  *@param  pM
  *@retval None
  */
void GuiMenuItemUpMove(lkdMenu *pM)
{
	if(pM->index - 1 < 0){
		pM->index = pM->nodeNum - 1;
	}
	else{
		pM->index --;
	}
	DrawNodes(pM, pM->pDraw, pM->cx, pM->cy, pM->index, pM->cNum);
	GuiUpdateDisplayAll();
}

/**
  *@brief  菜单项向下移动
  *@param  pM
  *@retval None
  */
void GuiMenuItemDownMove(lkdMenu *pM)
{
	pM->index ++;
	if(pM->index >= pM->nodeNum){
		pM->index = 0;
	}
	DrawNodes(pM, pM->pDraw, pM->cx, pM->cy, pM->index, pM->cNum);
	GuiUpdateDisplayAll();
}

/**
  *@brief  获取当前节点ID
  *@param  pM 菜单句柄
  *@retval nodeId
  */
uint16_t GuiMenuGetCurrentNodeID(lkdMenu *pM)
{
	lkdMenuNode *pNode;
	pNode = GetpNodeFromIndex(pM);
	return pNode->nodeId;
}
/**
  *@brief  获取当前节点指针
  *@param  pM 菜单句柄
  *@retval 节点指针
  */
lkdMenuNode *GuiMenuGetCurrentpNode(lkdMenu *pM)
{
	return GetpNodeFromIndex(pM);
}

/**
  *@brief  菜单初始化
  *@param  pM 菜单句柄
  *@retval NULL
  */
void GuiMenuInit(lkdMenu *pM)
{
	pM->count = 0;
	pM->index = 0;
	pM->cx = pM->x;
	pM->cy = pM->y;
	pM->pDraw = pM->Root;
}

/* END */
