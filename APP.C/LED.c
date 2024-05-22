#include "Main.h"
//========================================
/* 8段数码管逻辑 */
#define		a 		0x01
#define		b 		0x02
#define		c 		0x04
#define		d 		0x08
#define		e 		0x10
#define		f 		0x20
#define		g 		0x40
#define		h 		0x80
/* FCRH%数码管逻辑 */
#define		_Dot 	0x01
#define		_a 		0x02
#define		_f 		0x04
#define		_g 		0x08
#define		_e 		0x10
#define		_d 		0x20
//========================================
// 		以下自动生成，无需修改
//========================================
const u8 T_DispNum[Shuzi_Max] = {			//ASCLL地址
	a | b | c | d | e | f,      // 0        0	  	0x30
	b | c,                		// 1        1		0x31		0x30		0
	a | b | d | e | g,          // 2        2								1
	a | b | c | d | g,          // 3        3
	b | c | f | g,              // 4        4
	a | c | d | f | g,          // 5        5
	a | c | d | e | f | g,      // 6        6
	a | b | c,              	// 7        7
	a | b | c | d | e | f | g,  // 8        8
	a | b | c | d | f | g,      // 9        9
	a | b | c | e | f | g,      // A		10 		0x41	    55 = 0x37	7
	c | d | e | f | g,          // b		11 		0x62		87 = 0x57	W
	a | f | e | d,        		// C		12 		0x43		55 = 0x37	7
	b | c | d | e | g,        	// d		13 		0x64		87 = 0x57	W
	a | d | e | f | g,        	// E		14 		0x45		55 = 0x37   7
	a | f | g | e,        		// F		15 		0x46		55 = 0x37	7
	f | g | e | d,        		// T		16 		0x54		68 = 0x44	D
	b | c | e | f | g,          // H		17 		0x48		55 = 0x37	7
	f | e | d,        			// L		18 		0x4C		58 = 0x3A	:
	a | b | e | f | g,        	// P		19 		0x50		61 = 0x3D	=
	a | f | g | c | d,        	// S		20 		0x53		63 = 0x3F	?
	0x00,               		// NULL		21
	g,                  		// -  		22 		0x2D		23 = 0x
	e | g,        				// r		23		0x72 = 114 114 -23 =91(0x5D)	[
	b | c | d | e | f | g,		// U
	_Dot | _a | _f | _e | _d,	/* *C */
	_Dot | _a | _f | _e | _g,	/* *F */
	_d | _f | _e | _g			/* *A */
};

const char T_ZimuBuf[D_TOTALNUM][4] = {
	"^CF",//	"CF "
	"^HC",//	"HC ",
	"^ST",//	"ST ",
	"^SP",//	"SP ",
	"^AH",//	"AH ",	0x5E - 21 =0x49
	"^AL",//	"AL ",
	"^PT",//	"PT ",
	"^CA",//	"CA ",

	"APP",//	"APP "
	"^P^",//	" P "
	"^H^",//	" P "
	"^C^",//	" C "
	"^F^",//	" F "
	"E1^",//	" E1 "
	"E2^",//	" E2 "
	"E3^",//	" E3 "
	"E4^",//	" E4 "
	"E5^",//	" E5 "
	"Er^",//	" Er "
	"^^^",//	" NULL "
};
const char T_ZimuBuf1[D_TOTALNUM][4] = {
	"I77",//"77 "  67-37 = 30
	"I77",//"77 "  67-37 = 30
	"I?D",//"D? ",
	"I?=",//"D? ",
	"I77",//"77 "  67-37 = 30
	"I7:",//"77 "  67-37 = 30
	"I=D",//"77 "  67-37 = 30
	"I77",//"77 "  67-37 = 30

	"7==",//"77 "
	"I=I",//"77 "
	"I7I",//"77 "
	"I7I",//"77 "
	"I7I",//"77 "
	"70I",//"77 "
	"70I",//"77 "
	"70I",//"77 "
	"70I",//"77 "
	"70I",//"77 "
	"7[I",//"77 "
	"III",//"77 "
};

int F_CtoF(int temp)
{
	temp = temp * 18 + 3200;//度C转换度F,两位小数点、保留1位
	// 四舍五入
	if (temp < 0)
		temp -= 5;
	else
		temp += 5;
	temp /= 10;
	return temp;
}

int F_FtoC(int temp)
{
//	temp = (temp*10-3200+9)/18;
	temp = temp * 10 - 3200;
	if (temp < 0)
		temp -= 9;
	else
		temp += 9;
	return temp / 18;
}

void F_Change5BCD(long num, u8 Decimal)
{
/* 	Decimal = 1 有小数位显示。显示0.1（个位0）
	Decimal = 0 无小数位显示。显示1（个位1） */
	if (num < 0)
	{
		num = ~num + 1;
		R_Bcd[5] = Shuzi_NEG;
	}
	else
		R_Bcd[5] = Shuzi_NULL;
	R_Bcd[4] = 0;
	while (num >= 10000)
	{
		num -= 10000;
		R_Bcd[4]++;
	}
	R_Bcd[3] = 0;
	while (num >= 1000)
	{
		num -= 1000;
		R_Bcd[3]++;
	}
	R_Bcd[2] = 0;
	while (num >= 100)
	{
		num -= 100;
		R_Bcd[2]++;
	}
	R_Bcd[1] = 0;
	while (num >= 10)
	{
		num -= 10;
		R_Bcd[1]++;
	}
	R_Bcd[0] = num;

	if (R_Bcd[4] == 0)
	{
		R_Bcd[4] = R_Bcd[5];
		if (R_Bcd[3] == 0)
		{
			R_Bcd[3] = R_Bcd[4];
			R_Bcd[4] = Shuzi_NULL;
			if (R_Bcd[2] == 0)
			{
				R_Bcd[2] = R_Bcd[3];
				R_Bcd[3] = Shuzi_NULL;
				if (Decimal == _DEC)
				{
					B_PVPOINT = _SEG_ON;
					return;
				}
				if (R_Bcd[1] == 0)
				{
					R_Bcd[1] = R_Bcd[2];
					R_Bcd[2] = Shuzi_NULL;
					B_PVPOINT = _SEG_OFF;
				}
			}
		}
	}
	if (Decimal == _ONE)
		B_PVPOINT = _SEG_OFF;
	else if ((R_Bcd[3] != Shuzi_0) && (R_Bcd[3] != Shuzi_NULL) && (R_Bcd[3] != Shuzi_NEGATIVE))
	{  /* 数码管最多只能显示百位数，超过百位数据 小数点、及小数点第一位消除 */
		R_Bcd[0] = R_Bcd[1];
		R_Bcd[1] = R_Bcd[2];
		R_Bcd[2] = R_Bcd[3];
		R_Bcd[3] = R_Bcd[4];
		B_PVPOINT = _SEG_OFF; /* 不显示小数点 */
	}
	else
		B_PVPOINT = _SEG_ON; /* 显示小数点 */

	if (R_Bcd[3] == Shuzi_NULL)
		B_PVNEG = _SEG_OFF;
	else if (R_Bcd[3] == Shuzi_NEGATIVE)
		B_PVNEG = _SEG_ON;
}

/***********************************
填充显示区域
data: 0-显示  0xff-不显示
***********************************/
void F_SetBCDINIT()
{
	SegBuff[0].ucVal = T_DispNum[Shuzi_8];
	SegBuff[1].ucVal = T_DispNum[Shuzi_8];
	SegBuff[2].ucVal = T_DispNum[Shuzi_8];
}

void F_DISPVER()
{
	/* 显示版本号*/
	R_Bcd[2] = Shuzi_V;
	R_Bcd[1] = VERSION1;
	R_Bcd[0] = VERSION0;
	R_Bcd[4] = Shuzi_NULL;
}

void F_DISPWIFIRSSI(u8 flag, u16 rssi)
{
	//产测指定WIFI信号强度显示。
	F_Change5BCD(rssi, 0);
/* 	if ((R_Bcd[2] == Shuzi_NULL)
		&& (R_Bcd[1] == Shuzi_NULL)
		&& (R_Bcd[0] != Shuzi_NULL))
	{
		R_Bcd[2] = 0;
		R_Bcd[1] = 0;
	}
	else if ((R_Bcd[2] == Shuzi_NULL)
		&& (R_Bcd[1] != Shuzi_NULL)
		&& (R_Bcd[0] != Shuzi_NULL))
		R_Bcd[2] = 0;
 */
	R_Bcd[2] = Shuzi_NULL;
	R_Bcd[1] = flag;
	R_Bcd[0] = Shuzi_NULL;
	R_Bcd[4] = Shuzi_NULL;
}

void F_Get_Set_Menu_Bcd()
{
	/* PV：设置模式下，显示菜单标识 */
	R_Bcd[2] = T_ZimuBuf[Indx][0] - T_ZimuBuf1[Indx][0];
	R_Bcd[1] = T_ZimuBuf[Indx][1] - T_ZimuBuf1[Indx][1];
	R_Bcd[0] = T_ZimuBuf[Indx][2] - T_ZimuBuf1[Indx][2];
	R_Bcd[4] = Shuzi_NULL;
	B_PVPOINT = _SEG_OFF;
	B_PVNEG = _SEG_OFF;
}

void F_Get_Temp_Bcd()
{
	if (E_ALARM && !B_1HzFlash)
	{
		switch (E_ALARM)
		{
			case ER_ALARM:Indx = D_Er;break;
			case AH_ALARM:Indx = D_AH;break;
			case AL_ALARM:Indx = D_AL;break;
			default:break;
		}
		F_Get_Set_Menu_Bcd();
	}
	else
	{
		F_Change5BCD(Temp.Display, 1);
		R_Bcd[4] = (B_CF) ? D_Temp_F : D_Temp_C;
	}
}

void F_GetBCD()
{
	if (R_Mode == D_TES)
		B_DispMode = D_TES;
	else if ((R_Mode == D_NOR) && (R_MENU != D_APP))
	{
		if (B_First_Display)
			return;
		B_DispMode = D_NOR;
	}
	else
		B_DispMode = D_SET;
	/* 设置模式下，显示菜单设置值 */
	Indx = R_MENU;
	switch (B_DispMode)
	{
		case D_NOR:
			if (R_Mode1 == D_NOR)
			{
				F_Get_Temp_Bcd();
			}
			else if (R_Mode1 == D_SET)
			{
				if (R_MENU == D_ST)
					F_Change5BCD(S_SET.ST, 1);
				else if (R_MENU == D_SP)
					F_Change5BCD(S_SET.SP, 1);
				R_Bcd[4] = (B_CF) ? D_Temp_F : D_Temp_C;
			}
			break;
		case D_SET:
			if (B_Menu_Enter == D_SET_Menu) {
				F_Get_Set_Menu_Bcd();
			}
			else if (B_Menu_Enter == D_SET_Param) {
				if ((B_1HzFlash) || (Key.Lcd2Hz))
				{
					switch (R_MENU)
					{
						case D_CF:	Indx = D__C + B_CF; F_Get_Set_Menu_Bcd();break;
						case D_HC:	Indx = D__H + B_HC; F_Get_Set_Menu_Bcd();break;
						case D_ST:	F_Change5BCD(S_SET.ST, 1);R_Bcd[4] = (B_CF) ? D_Temp_F : D_Temp_C; 	break;
						case D_SP:	F_Change5BCD(S_SET.SP, 1);R_Bcd[4] = (B_CF) ? D_Temp_F : D_Temp_C; 	break;
						case D_AH:	F_Change5BCD(S_SET.AH, 1);R_Bcd[4] = (B_CF) ? D_Temp_F : D_Temp_C; 	break;
						case D_AL:	F_Change5BCD(S_SET.AL, 1);R_Bcd[4] = (B_CF) ? D_Temp_F : D_Temp_C; 	break;
						case D_PT:  F_Change5BCD(S_SET.PT, 0);R_Bcd[4] = Shuzi_NULL;					break;
						case D_CA:	F_Change5BCD(S_SET.CA, 1);R_Bcd[4] = (B_CF) ? D_Temp_F : D_Temp_C; 	break;
						case D_APP:	Indx = D__NULL; 	F_Get_Set_Menu_Bcd();break;
						default:break;
					}
				}
				else {
				/* 1hz闪烁速率 */
					R_Bcd[2] = Shuzi_NULL;
					R_Bcd[1] = Shuzi_NULL;
					R_Bcd[0] = Shuzi_NULL;
					R_Bcd[4] = Shuzi_NULL;
					B_PVNEG = _SEG_OFF;
					B_PVPOINT = _SEG_OFF;
				}
			}
			break;
		case D_TES:
			switch (R_TestMode)
			{
				case 4:F_DISPVER();break;
				case 3:F_DISPVER();break;
				case 2:F_Get_Temp_Bcd();break;
				case 1:F_DISPWIFIRSSI(R_CONFIG, R_RSSI);break;
				default:break;
			}
			break;
		default:
			break;
	}
	SegBuff[0].ucVal = T_DispNum[R_Bcd[2]];
	SegBuff[1].ucVal = T_DispNum[R_Bcd[1]];
	SegBuff[2].ucVal = T_DispNum[R_Bcd[0]];
	SegBuff[3].ucVal = T_DispNum[R_Bcd[4]];
}

void F_LEDSCAN()
{
	u8 LED_STATE;
	if (R_TestMode == 4)
	{
		COM0 = _COM_ON;COM1 = _COM_ON;COM2 = _COM_ON;COM3 = _COM_ON;
		SEG8 = _SEG_ON;SEG7 = _SEG_ON;SEG6 = _SEG_ON;SEG5 = _SEG_ON;
		SEG4 = _SEG_ON;SEG3 = _SEG_ON;SEG2 = _SEG_ON;SEG1 = _SEG_ON;SEG0 = _SEG_ON;
		return;//产测功能全显示
	}
	if (++BCD > 3)
		BCD = 0;
	/* 清显示 */
	COM0 = _COM_OFF;COM1 = _COM_OFF;COM2 = _COM_OFF;COM3 = _COM_OFF;
	SEG7 = _SEG_OFF;SEG8 = _SEG_OFF;
	LED_STATE = ((B_First_Display == FALSE) && (R_Mode == D_NOR) && (R_Mode1 == D_NOR) && (R_MENU != D_APP)) ? TRUE : FALSE;
	switch (BCD)
	{
		case 0:	SEG8 = ((B_HC == D_HEAT_MODE) && (LED_STATE)) ? _SEG_ON : _SEG_OFF;break;
		case 1: SEG7 = ((B_PVPOINT == _SEG_ON) && (B_First_Display == FALSE)) ? _SEG_ON : _SEG_OFF;
			SEG8 = ((R_Wifi_State == _SEG_ON) && (LED_STATE)) ? _SEG_ON : _SEG_OFF;
			break;
		case 2: SEG7 = ((B_HC == D_COOL_MODE) && (LED_STATE)) ? _SEG_ON : _SEG_OFF;
			SEG8 = ((B_PVNEG == _SEG_ON) && (B_First_Display == FALSE)) ? _SEG_ON : _SEG_OFF;
			break;
		default:
			break;
	}
	/* 大端模式  低地址存放高位 */
	SEG6 = (SegBuff[BCD].Bit.bit1 == TRUE) ? _SEG_ON : _SEG_OFF;
	SEG5 = (SegBuff[BCD].Bit.bit2 == TRUE) ? _SEG_ON : _SEG_OFF;
	SEG4 = (SegBuff[BCD].Bit.bit3 == TRUE) ? _SEG_ON : _SEG_OFF;
	SEG3 = (SegBuff[BCD].Bit.bit4 == TRUE) ? _SEG_ON : _SEG_OFF;
	SEG2 = (SegBuff[BCD].Bit.bit5 == TRUE) ? _SEG_ON : _SEG_OFF;
	SEG1 = (SegBuff[BCD].Bit.bit6 == TRUE) ? _SEG_ON : _SEG_OFF;
	SEG0 = (SegBuff[BCD].Bit.bit7 == TRUE) ? _SEG_ON : _SEG_OFF;
	switch (BCD)
	{
		case 0:	COM0 = _COM_ON; break;
		case 1: COM1 = _COM_ON; break;
		case 2: COM2 = _COM_ON; break;
		case 3: COM3 = _COM_ON; break;
		default: break;
	}
}
