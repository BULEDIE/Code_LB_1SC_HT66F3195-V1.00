#include "Main.h"

void F_Delay_Ms(u16 ms)
{
	while (ms--)
	{
		GCC_DELAY(2000);//编译器自带延时指定个周期，在主频8Mhz下，一个指令周期为0.5us
	//	GCC_CLRWDT();
	}
}

void F_IO_INIT()
{
	_rstc = 0B01010101;
	_scc = 0b00000000;//LIRC
	_hxtc = 0b00000100;
	_lxtc = 0b00000001;
	_hircc = 0b00000001;
	while (!_hircf);
	//_cmpc = 0b00000000;
	_wdtc = 0b01010111;//LIRC 32KHZ溢出时间8秒//WDT_ENABLE();
	//_lvdc = 0b00000101;
	//_lvrc = 0b10101010;
	//_lvpuc = 0b00000000;
	_psc0r = 0b00000001; //TimeBase0 clock fsys/4
	_psc1r = 0b00000001; //TimeBase0 clock fsys/4
	_tb0c = 0b10000011; //TB0_ENABLE();

	_savrs0 = 0b00000000;
	_savrs1 = 0b00000000;
	_sadol = 0b00000000;
	_sadoh = 0b00000000;
	_sadc0 = 0b00110000;//ADC_ENABLE();_adrfs = 1;
	_sadc1 = 0b00000000;
	_sadc2 = 0b00000000;
	_slcdc0 = 0b00000000;
	_slcds0 = 0b00000000;
	_slcds1 = 0b00000000;
	_slcds2 = 0b00000000;

	_sledc0 = 0b11111111;
	_sledc1 = 0b11111111;

	_papu = 0b00000000;
	_pa = 0b00000010;//1:输出高，0：输出低
	_pac = 0b00000000;//0:输出，1：输入
	_pawu = 0b00000000;

	_pbpu = 0b00000000;
	_pb = 0b00100000;
	_pbc = 0b00000000;

	_pcpu = 0b00000000;
	_pc = 0b01000000;
	_pcc = 0b00000000;

	_pdpu = 0b00000000;
	_pd = 0b00000000;
	_pdc = 0b00000010;

	_pas0 = 0b00000000;
	_pas1 = 0b00000000;
	_pbs0 = 0b00000000;
	_pbs1 = 0b00000011;//AN8复用口
	_pcs0 = 0b00000000;
	_pcs1 = 0b00000000;
	_pds0 = 0b00010100;//TX RX 复用口
	_ucr1 = 0b00000000;
	_ucr2 = 0b00000000;
	_txr_rxr = 0b00000000;
	_brg = 12;	//9600 Baud Rate values config

	TB0_CLEAR_FLAG();
	TB0_ISR_ENABLE();
}

void F_RAM_INIT()
{
	for (_mp0 = 0x7F;_mp0 < 0xFF;)
	{
		_mp0++;		  //sector0
		_iar0 = 0x00;
	}
	for (_mp1l = 0x7F;_mp1l < 0xFF;)
	{
		_mp1h = 1;    //sector1
		_mp1l++;
		_iar1 = 0x00;
	}
	for (_mp1l = 0x7F;_mp1l < 0xFF;)
	{
		_mp1h = 2;    //sector2
		_mp1l++;
		_iar1 = 0x00;
	}
	for (_mp1l = 0x7F;_mp1l < 0xFF;)
	{
		_mp1h = 3;    //sector3
		_mp1l++;
		_iar1 = 0x00;
	}
	B_LEDMode = D_LEDOFF;
	B_First_Display = 1;
	B_WifiReset = 1;
	B_WifiConfigState = 1;
	B_WifiConfigMode = D_SmartMode;
	B_PVNEG = _SEG_OFF;
	B_PVPOINT = _SEG_OFF;
	B_OUT_STATE_LAST = 0XFF;
	R_CheakSum = 0;
	E_ALARM = NO_ALARM;
	B_RST_SP = TRUE;
}

void F_UART_RAM_INIT()
{
	u8 i = 0;
	for (i = 0; i < 24; i++)
	{
		MCU_RX.DATA[i] = 0x00;
		MCU_TX.DATA[i] = 0x00;
	}
}

void F_DefaultSettings(u8 CF, u8 HC)
{
	S_SET.CF = CF;
	S_SET.HC = HC;
	if (S_SET.CF == D_F)
	{
		S_SET.ST = (HC == D_HEAT_MODE) ? 770 : 780;
		S_SET.SP = (HC == D_HEAT_MODE) ? 780 : 770;
		S_SET.AH = 1220;
		S_SET.AL = 230;
	}
	else {
		S_SET.ST = (HC == D_HEAT_MODE) ? 250 : 260;
		S_SET.SP = (HC == D_HEAT_MODE) ? 260 : 250;
		S_SET.AH = 500;
		S_SET.AL = -50;
	}
	S_SET.PT = 0;
	S_SET.CA = 0;
	B_CF = S_SET.CF;
	B_HC = S_SET.HC;
	B_KEYSET = 1;/* 等待1秒存储数据 */
	WIFI_DP_Update_Flag.ucVal = 0x00000FFF;
}

void System_Init()
{
	F_IO_INIT();
	TimeBase0_Init();
	F_RAM_INIT();
}

void System_Setting()
{
	WDT_ENABLE();
	TB0_CLEAR_FLAG();
	TB0_ISR_ENABLE();
	TB0_ENABLE();
	ADC_ENABLE();
	UART_ENABLE();
}

void UART_Init()
{
	UART_CLEAR_ISR_FLAG();
	UART_RIE_ENABLE();
	UART_ENABLE();
	UART_TX_ENABLE();
	UART_RX_ENABLE();
	UART_ISR_ENABLE();
}
