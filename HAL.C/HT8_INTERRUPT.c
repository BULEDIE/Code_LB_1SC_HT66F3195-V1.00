
#include "Main.h"

void __attribute((interrupt(0x1C))) TB0_ISR(void)
{
	////F_TESTTIME();
	EMI_ENABLE();//允许中断嵌套
	if (++R_1hz1sCnt >= D_1HzCnt)
	{
		R_Timer1HzCnt++;
		if (R_Timer1HzCnt > 999)
			R_Timer1HzCnt = 0;
		R_1hz1sCnt = 0;//1s
	}
	if (Tx_OK_Delay)
		Tx_OK_Delay--;

	if (R_RxRecvTimeOut)
	{	R_RxRecvTimeOut--;
		if (R_RxRecvTimeOut == 0)
		{
			if (R_Indexes < 6)
				R_Indexes = 0;
			}
	}
	R_1Khz1msCnt++;
	if(R_1Khz1msCnt >= D_64HzCnt)
	{
		R_1Khz1msCnt = 0;
		Count64Hz++;
		B_64HzFlag = 1;
		B_Key64HzScan = 1;
		B_Key64HzStep = 1;
		F_GetKey();
		F_KeyScan();
	}
 	F_Buz1KHzCntBiBi();
	F_Wifi_State();
	F_LEDSCAN();/* 101us=0.1ms扫描完毕 */
	////F_TESTTIME();/* 1ms时基中断测量处理耗时110us,加上按键任务处理最长耗时160us */
	//GCC_CLRWDT();/* UART1字节接收中断时间为，104us*(1+8+1) = 1.04ms */
}

void __attribute((interrupt(0x2C))) UART_ISR(void)
{
	if (B_LEDMode == D_LEDON)
		R_RxRecvTimeOut = 60;
	else
		R_RxRecvTimeOut = 2;
	if (R_Indexes < D_RxLen)
		R_Indexes++;
	else
		R_Indexes = 0;
	MCU_RX.DATA[R_Indexes-1] = _txr_rxr;
 	//F_PRINT_RX_DATA();
	UART_CLEAR_ISR_FLAG();
	F_TESTTIME();
}


/* void __attribute((interrupt(0x04))) INT0_ISR(void)
{

}

void __attribute((interrupt(0x08))) COMP_ISR(void)
{

}

void __attribute((interrupt(0x0C))) STM_ISR(void)
{

	if (_stmaf == 1)
	{
		_stmaf = 0;

	}
	if (_stmpf == 1)
	{
		_stmpf = 0;

	}
}

void __attribute((interrupt(0x10))) PTM_CTM_ISR(void)
{
	if (_ptmaf == 1)
	{
		_ptmaf = 0;

	}
	if (_ptmpf == 1)
	{
		_ptmpf = 0;

	}
	if (_ctmaf == 1)
	{
		_ctmaf = 0;

	}
	if (_ctmpf == 1)
	{
		_ctmpf = 0;

	}
}

void __attribute((interrupt(0x14))) LVD_EEPROM_ISR(void)
{
	if (_lvf == 1)
	{
		_lvf = 0;

	}
	if (_def == 1)
	{
		_def = 0;

	}
}

void __attribute((interrupt(0x18))) ADC_ISR(void)
{

}

void __attribute((interrupt(0x20))) TB1_ISR(void)
{

}

void __attribute((interrupt(0x24))) INT1_ISR(void)
{

} */
