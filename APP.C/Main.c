#define MainS
#include "Main.h"

void main()
{
	F_IO_INIT();
	F_RAM_INIT();
	System_Setting();
	EMI_ENABLE();
	F_KeyRstFactory();
	UART_Init();
	while (1)
	{
		// F_TESTTIME();
		F_TimeService();
		F_KeySever();
		F_SetMenu();
		F_GetBCD();
		// F_MCU_RX_Service();
		// F_MCU_TX_Service();
		GCC_CLRWDT();
	}
}
/*
	1.制冷延迟功能实现：
	2. 设备短按配网，长按配网。移除功能。
	3.温度检测优化功能
	4.产测模式，WIFI,不存在检测功能，验证。

 */