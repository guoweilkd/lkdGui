/**
  * @file    keyDriver.h
  * @author  guoweilkd
  * @version V1.1.0
  * @date    2018/05/16
  * @brief  
  */

#ifndef _KEYDRIVER_H_
#define _KEYDRIVER_H_

#include "stm32f10x.h"

#define KEY_NUM_ALL 13

#define RCC_APB2Periph_KEY (RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOC)

#define PORT_KEY0		GPIOB
#define PIN_KEY0		GPIO_Pin_12
#define PORT_KEY1		GPIOB
#define PIN_KEY1		GPIO_Pin_14
#define PORT_KEY2		GPIOB
#define PIN_KEY2		GPIO_Pin_13
#define PORT_KEY3		GPIOE
#define PIN_KEY3		GPIO_Pin_5
#define PORT_KEY4		GPIOE
#define PIN_KEY4		GPIO_Pin_3
#define PORT_KEY5		GPIOE
#define PIN_KEY5		GPIO_Pin_4

#define PORT_KEY6		GPIOB
#define PIN_KEY6		GPIO_Pin_8
#define PORT_KEY7		GPIOB
#define PIN_KEY7		GPIO_Pin_7
#define PORT_KEY8		GPIOB
#define PIN_KEY8		GPIO_Pin_6
#define PORT_KEY9		GPIOB
#define PIN_KEY9		GPIO_Pin_5

#define PORT_KEY10	GPIOC
#define PIN_KEY10		GPIO_Pin_0
#define PORT_KEY11	GPIOC
#define PIN_KEY11		GPIO_Pin_1
#define PORT_KEY12	GPIOC
#define PIN_KEY12		GPIO_Pin_2

/* 和硬件相关 */
#define KEY_HARDWARE_UP			1	
#define LED_HARDWARE_DOWN		0

/* 按键状态 */
typedef enum{
	KEYUP,
	KEYDOWN,
	KEYERROR
}KeyStatus;

/* 按键处理 */
struct KeyInfo{
	uint32_t filterCount[KEY_NUM_ALL];
	uint8_t  stepFlag[KEY_NUM_ALL];
	uint8_t  currentStatus[KEY_NUM_ALL];
};

#define MENUY_UP				0
#define MENUKEY_DOWN		2
#define MENUKEY_LEFT		1
#define MENUKEY_RIGHT		3
#define MENUKEY_OK			5
#define MENUKEY_CANCEL	4

enum MenuKeyIs{
	MKEY_NO,
	MKEY_UP,
	MKEY_DOWN,
	MKEY_LEFT,
	MKEY_RIGHT,
	MKEY_OK,
	MKEY_CANCEL
};


void ScanKeyStatus(void);
void KeyDriverInit(void);

void SetMenuKeyIsNoKey(void);
enum MenuKeyIs GetMenuKeyState(void);

/* 调用外部函数 */
extern uint32_t GetTimer1Tick(void);
extern uint32_t GetTimer1IntervalTick(uint32_t beginTick);

#endif /* END _KEYDRIVER_H_ */
