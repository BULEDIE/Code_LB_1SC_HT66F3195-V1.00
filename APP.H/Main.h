#ifndef _Main_H_
#define _Main_H_

#ifdef MainS
	#define MyDef
#else
	#define MyDef extern
#endif
#define VERSION1 0 //
#define VERSION0 1 //V01

enum {	/* BOOL 变量枚举值 */
	_FALSE,
	_TRUE,
};
enum {  /* 使能位 变量枚举值 */
	D_DISABLE,
	D_ENABLE,
};
enum {  /* 继电器 开关枚举值 */
	D_OFF,
	D_ON,
};
enum {	/* 正常模式菜单枚举值 */
	D_NOR,
	D_SET,
	D_SET1,
	D_TES,
};
enum{	/* 温度单位菜单枚举值 */
	D_C,
	D_F,
};
enum{
	D_SET_Menu, /* 设置菜单字符显示 */
	D_SET_Param,/* 设置菜单对应参数显示 */
};
enum{	/* 工作模式菜单枚举值 */
	D_HEAT_MODE,
	D_COOL_MODE,
};

#include "string.h"
#include "HT66F3195.h"//无仿真芯片
#include "TypeDef.h"
#include "HT8_SYS_Clock.h"
#include "HT8_TimeBase.h"
#include "HT8_WDT.h"
#include "HT8_GPIO.h"
#include "HT8_ADC.h"
#include "HT8_EEPROM.h"
#include "HT8_INTERRUPT.h"
#include "SYSINIT.h"
#include "APP.h"
#include "NTC.h"
#include "LED.h"
#include "BUZ.h"
#include "UART.h"
#include "KEY.h"
#include "KEY_Sub.h"
#include "WIFI.h"
#include "WIFI_Sub.h"

#define EV_IC 0
#if EV_IC
	#define  D_1HzCnt	1089	//仿真芯片的1s计数值时间
	#define  D_64HzCnt	17		//仿真芯片15.625ms//64Hz
	#define  D_9600		61//57	//仿真芯片 = HIRC时钟8.7Mhz
	#define  D_BUZ10HZ	87		//仿真芯片100MS间隔蜂鸣器鸣叫
#else
	#define  D_1HzCnt	981		//烧录芯片的1s计数值时间//每秒少0.3ms
	#define  D_64HzCnt	15		//烧录芯片15.42ms//15.625ms
	#define  D_9600		51		//烧录芯片 = HIRC时钟8.0Mhz
	#define  D_BUZ10HZ	100		//烧录芯片100MS间隔蜂鸣器鸣叫
#endif

#endif
