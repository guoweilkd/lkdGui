/**
  ******************************************************************************
  * @file    systemconfig.c
  * @author  guoweilkd
  * @version V1.1.0
  * @date    09-10-2017
  * @brief   M3核Systick定时计数器作为整个文件 计数
  ******************************************************************************
  */
#include "systemconfig.h"

/* 1us时间的节拍数 */
static uint32_t Fac_us;	
/* LSI频率 */
__IO uint32_t LsiFreq = 40000; 

static uint32_t timeCount;
/**
  *@brief 系统优先级配置
  *@param  None
  *@retval None
  */
void NVIC_Configuration(void)
{  
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	/* Enable the USARTy Interrupt */		
}

void SysTick_Init(int16_t clock_div)
{
	/* SystemCoreClock / 1000   1ms */
   if (SysTick_Config(SystemCoreClock / clock_div)){ 
		/* Capture error */ 
		while (1);
	}
    Fac_us = SystemCoreClock/1000000;/* 1us时间的节拍数,用于延时函数 */
	OPen_SysTick();
}

/**
  *@brief 精确微秒延时
  *@param  nus  要延时的微秒数
  *@retval None
  */
void Delay_us(uint32_t nus)
{		
	uint32_t ticks;
	uint32_t told,tnow,tcnt=0;
	uint32_t reload=SysTick->LOAD;				/* LOAD的值	 */    	 
	ticks=nus*Fac_us; 						/* 需要的节拍数	  */ 		 
	tcnt=0;
	told=SysTick->VAL;        				/* 刚进入时的计数器值 */
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)
				tcnt+=told-tnow;			/* 这里注意一下SYSTICK是一个递减的计数器就可以了. */
			else 
				tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)
				break;						/* 时间超过/等于要延迟的时间,则退出. */
		}  
	}							    
}

/**
  *@brief 精确ms延时
  *@param  nms 要延时的毫秒数
  *@retval None
  */
void Delay_ms(uint16_t nms)
{	    		  
	Delay_us((uint32_t)(nms*1000));
}

void SystemconfigInit(void)
{
	
	NVIC_Configuration();	
	SysTick_Init((int16_t)1000);/* 1ms */
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	timeCount ++;
}

/**
  *@brief 获取开始计时数
  *@param  None
  *@retval beginTick  计时开始数，
  */
uint32_t GetTimer1Tick(void)
{
	return timeCount;
}

/**
  *@brief 获取间隔周期数
  *@param  beginTick  计时开始数，由GetTimer1Tick()函数获得
  *@retval 间隔周期数
  */
uint32_t GetTimer1IntervalTick(uint32_t beginTick)
{
	uint32_t temptick;
	temptick = GetTimer1Tick();
	if(beginTick <= temptick){
		return (temptick - beginTick);
	}
	else{
		return ((0xFFFFFFFF - beginTick)+temptick);
	}
}
