#include "Main.h"
#define N 15//21
#define NNEG -15//-21
u16 T_Adc[N];
//u8 T_EqualCnt[N] = {0};

#define D_TEMP_MIN 0
#define D_TEMP_MAX 141 //-40+101度数
//#define D_TEMP_MAX 171 //-50+121度数
//#define D_NEGTEMPLEN   50//-50温度
#define D_NEGTEMPLEN   40//-40温度
/***********************************************************************
** 函数名 : T_temptab
** 返回值 :
** 参  数 :
** 描  述 :
***********************************************************************/

const unsigned int T_temptab[D_TEMP_MAX] = {  //0 to 99℃   10k ntc 3950
	/* ADC 测量温度 */
	/* 热敏电阻与10K参考电阻分压电路 */
// 	3975,3968,3961,3953,3945,3937,3928,3919,3909,3899, // -50C ~ -41C
	3894,3883,3872,3860,3848,3835,3822,3808,3794,3779, // -40C ~ -31C
	3764,3748,3731,3714,3696,3677,3658,3638,3618,3597, // -30C ~ -21C
	3575,3553,3529,3506,3481,3456,3430,3403,3376,3348, // -20C ~ -11C
	3320,3291,3261,3230,3199,3167,3135,3102,3069,3035, // -10C ~ -1C
	3000,2966,2930,2894,2858,2821,2784,2747,2709,2671, //  0C ~  9C
	2632,2594,2555,2516,2477,2438,2399,2360,2320,2281, //  10C ~ 19C
	2242,2203,2164,2125,2086,2048,2009,1971,1933,1896, //  20C ~ 29C
	1858,1821,1785,1749,1713,1677,1642,1608,1574,1540, //  30C ~ 39C
	1507,1474,1442,1410,1379,1348,1318,1288,1259,1230, //  40C ~ 49C
	1202,1175,1147,1121,1095,1069,1044,1020,996,972,   //  50C ~ 59C
	949,927,905,883,862,842,822,802,783,764,           //  60C ~ 69C
	746,728,711,694,677,661,645,629,614,599,           //  70C ~ 79C
	585,571,557,544,531,519,506,494,483,471,           //  80C ~ 89C
	460,449,438,428,418,408,399,389,380,371,           //  90C ~ 99C
	363, //354,346,338,331,323,316,308,301,295,           //  100C ~ 109C
	//288,282,275,269,263,257,252,246,241,236,231,       //  110C ~ 120C

};

/***********************************************************************
** 函数名 : F_GetADC
** 返回值 : adc值
** 参  数 : ch
** 描  述 : 获取指定通道的adc值
***********************************************************************/
u16 F_GetADC(u8 ch)
{
	u16 temp;
	//_adrfs = 1;//1：ADC 数据高字节是 ADRH 的 bit 3~bit 0，低字节是 ADRL 的 bit 7~bit 0
	_sadc0 &= 0xF0;/* 单通道采集 */
	_sadc0 |= ch;
	_start = 0;//0->1->0  启动转换
	_start = 1;
	_start = 0;
	while (_adbz);//bit6 = 0(ADC转换结束)等待转换结束
	temp = _sadoh;
	temp <<= 8;
	temp |= _sadol;
	//temp &= 0x0FFF;/* 12位ADC*/
	return temp;
}

/***********************************************************************
** 函数名 : F_GetMid
** 返回值 : 中间值
** 参  数 : length
** 描  述 : 排序函数
***********************************************************************/
u16 F_GetMid(u16* p, u8 length)
{
	u8 i, j;
	u16 temp;
	for (i = 1; i < length; i++)
	{
		for (j = 0; j < length - i; j++)
		{
			if (p[j] < p[j + 1])
			{
				temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
		}
	}
	return p[length >> 1];
}
/***********************************************************************
** 函数名 : F_GetAvg
** 返回值 : 平均值
** 参  数 : length
** 描  述 :
***********************************************************************/
u16 F_GetAvg(u16* p, u8 length)
{
	u8 i = 0;
	u32 temp = 0;
	for (i = 0; i < length; i++)
		temp += *p++;
	temp /= length;
	return temp;
}
/***********************************************************************
** 函数名 : F_GetMore
** 返回值 : 数组元素中出现次数最多的值
** 参  数 : n
** 描  述 :
***********************************************************************/
u16 F_GetMore(u16* arr, u16 len)
{
	u8 i, j;
	u8 m;
	u8 T_EqualCnt[N] = { 0 };
	//数组初始化
	for (i = 0; i < len; i++) {
		T_EqualCnt[i] = 0;
	}
	//对数组中的元素进行count
	for (i = 0; i < len; i++) {
		for (j = i; j < len; j++) {
			if (arr[i] == arr[j]) {
				T_EqualCnt[i]++;
			}
		}
	}
	   //取出数组中元素的最多计数值
	m = 0;
	for (i = 0; i < len; i++) {
		if (T_EqualCnt[m] < T_EqualCnt[i]) {
			m = i;
		}
	}
	return arr[m];
}

/***********************************************************************
** 函数名 :
** 返回值 : 温度值
** 参  数 : ch
** 描  述 : ADC连续采集9次取中间值 作为NTC温度查表参数
***********************************************************************/
void F_RxMove(u16* R_History, u16 offset, u8 size)
{
	u8 i;
	for (i = 0; i < size; i++)
		R_History[i] = R_History[i + offset];
}
void F_Move(u16* R_History, u16 Current, u8 size)
{
	u8 i;
	for (i = 0; i < size; i++)
		R_History[i] = R_History[i + 1];
	R_History[size - 1] = Current;
}
u16 F_GetMin(u16* R_History, u8 size)
{
	u8 i;
	u16 temp = 0;
	temp = R_History[0];
	for (i = 0; i < size; i++)
	{
		if (temp > R_History[i])
			temp = R_History[i];
	}
	return temp;
}
u16 F_GetMax(u16* R_History, u8 size)
{
	u8 i;
	u16 temp = 0;
	temp = R_History[0];
	for (i = 0; i < size; i++)
	{
		if (temp < R_History[i])
			temp = R_History[i];
	}
	return temp;
}
s16 iyy;
s16 PointTemp;
s16 F_GetTemp(u16 Value)
{
	//s16 iyy = 0;//不能用 s8 128 <171
	///s16 PointTemp = 0;	/* 负温度小数位符号存储 */

	if (Value > T_temptab[D_TEMP_MIN] + 35)//-45度故障
		return D_OpenCircuit;
	else if (Value < T_temptab[D_TEMP_MAX - 1] - 35)//105故障
		return D_ShortCircuit;
	else
	{
		for (iyy = 0;iyy < D_TEMP_MAX;iyy++)//查表获取温度值
		{
			if (T_temptab[iyy] <= Value)
				break;
		}
		if (iyy >= D_NEGTEMPLEN + 1)
			PointTemp = (10 * (T_temptab[iyy - 1] - Value));/* 正温度,小数点温度取值公式 */
		else
			PointTemp = (10 * (Value - T_temptab[iyy]));/* 负温度,小数点温度取值公式 */
		PointTemp /= (T_temptab[iyy - 1] - T_temptab[iyy]);
		iyy -= D_NEGTEMPLEN;/* 加上偏移值 */
		if (Value != T_temptab[iyy])
		{
			if (iyy <= 0)
				return iyy * 10 - PointTemp;/* 负温度 */
			else
				return (iyy - 1) * 10 + PointTemp;/* 正温度 */
		}
		return iyy * 10;
	}
}

u16 F_GetTrueADC(u8 ch, u16 LastAdc)
{
	u8 i = 0;
	// u8 Cnt = 0;
	u16 Value = 0;
	for (i = 0; i < 8; i++)
	{
		F_GetADC(ch);
	}
	for (i = 0; i < N; i++)
	{
		T_Adc[i] = F_GetADC(ch);
		T_Adc[i] -= 21;

		// if (T_Adc[i] == LastAdc)	Cnt++;
		// else	Cnt--;


		//if (T_Adc[i] > LastAdc)		Cnt++;/* 降温 */
		//else if (T_Adc[i] < LastAdc)	Cnt--;/* 升温 */

		// _txr_rxr = T_Adc[i] >> 8;
		// while (_tidle == 0 || _txif == 0);
		// _txr_rxr = T_Adc[i];
		// while (_tidle == 0 || _txif == 0);
	}
	F_GetMid(T_Adc, N);// 排序

 	for (i = 0; i < N; i++)		//查看排完序的AD值（用串口）
	{
		_txr_rxr = T_Adc[i] >> 8;
		while (_tidle == 0 || _txif == 0);
		_txr_rxr = T_Adc[i];
		while (_tidle == 0 || _txif == 0);
	}

	// if (Cnt >= N)
	// 	Value = T_Adc[N - 2];
	// else if (Cnt <= NNEG)
	// 	Value = T_Adc[0 + 2];
	// else
	// Value = LastAdc;



	// if ((LastAdc - T_Adc[6] <= 2) && (LastAdc - T_Adc[6] >= -2))	//去除温度抖动，取中间值（前后变化太大）,
	// {
	// 	Value = LastAdc;
	// }else
	Value = T_Adc[8];
	return Value;
}

void F_Ctrl_220V_OnOff()
{
	// if (WIFI_DP_Update_Flag.ucVal & 0x00000FFF)//必须要有
		// return;/* 收完设置参数再判断高低温故障 */
	if ((R_Mode == D_NOR) && (R_Mode1 == D_NOR) && (R_ReturnCnt == 0)/* && (B_TestMode == 0) */)/* 非产测模式下 */
	{
		if (B_HC == D_HEAT_MODE)
		{
			// 摄氏度：S_SET.ST <= S_SET.SP - 3;
			// 华氏度：S_SET.ST <= S_SET.SP - 5;
			if (B_RST_SP == TRUE)
			{
				B_RST_SP = FALSE;
				if (Temp.Display <= S_SET.SP)
				{
					RELAY_IO = D_ON;
					F_Heat_Led_On();
					F_Cool_Led_Off();
					B_OUT_STATE = HEAT_ON;
				}
				else
				{
					RELAY_IO = D_OFF;
					F_Heat_Led_Off();
					F_Cool_Led_Off();
					B_OUT_STATE = HEAT_OFF;
				}
			}

			if (Temp.Display <= S_SET.ST)
			{
				RELAY_IO = D_ON;
				F_Heat_Led_On();
				F_Cool_Led_Off();
				B_OUT_STATE = HEAT_ON;
			}
			else if (Temp.Display >= S_SET.SP)
			{
				RELAY_IO = D_OFF;
				F_Heat_Led_Off();
				F_Cool_Led_Off();
				B_OUT_STATE = HEAT_OFF;
			}
		}
		else if (B_HC == D_COOL_MODE)
		{
			// 摄氏度：S_SET.ST >= S_SET.SP - 3;
			// 华氏度：S_SET.ST >= S_SET.SP - 5;
			if (B_RST_SP == TRUE)	//上电或者退出设置判断是否启动制冷功能
			{
				B_RST_SP = FALSE;
				if (Temp.Display >= S_SET.SP)
				{
					RELAY_IO = D_ON;
					F_Cool_Led_On();
					F_Heat_Led_Off();
					B_OUT_STATE = COOL_ON;
				}
				else
				{
					RELAY_IO = D_OFF;
					F_Heat_Led_Off();
					F_Cool_Led_Off();
					B_OUT_STATE = COOL_OFF;
				}
			}

			if ((Runing_PT)
				&& (Temp.Display >= S_SET.SP)
				&& (S_SET.PT)
				&& (B_FLASH_ST == TRUE))	//延时闪烁
			{
				Runing_PT--;
				if (Runing_PT)
				{
					return;
				}
				else
				{
					B_FLASH_ST = FALSE;
					RELAY_IO = D_ON;
					F_Cool_Led_On();
					F_Heat_Led_Off();
					B_OUT_STATE = COOL_ON;
				}
			}
			else if (Temp.Display >= S_SET.ST)
			{
				if (Runing_PT && S_SET.PT)
				{
					B_FLASH_ST = TRUE;
					return;
				}
				B_FLASH_ST = FALSE;
				RELAY_IO = D_ON;
				F_Cool_Led_On();
				F_Heat_Led_Off();
				B_OUT_STATE = COOL_ON;
			}
			else if (Temp.Display <= S_SET.SP)
			{
				B_FLASH_ST = FALSE;
				RELAY_IO = D_OFF;
				F_Heat_Led_Off();
				F_Cool_Led_Off();
				B_OUT_STATE = COOL_OFF;
				Runing_PT = S_SET.PT * 60;
			}
		}
		if (B_OUT_STATE_LAST != B_OUT_STATE)
		{
			B_OUT_STATE_LAST = B_OUT_STATE;
			FLAG_OUT_STATE = D_ENABLE;
		}
	}
}

void F_GetTempValue()
{
	R_Ch1ADC = F_GetTrueADC(D_CH1, R_Ch1LastADC);
	R_Ch1Temp = F_GetTemp(R_Ch1ADC);
	R_Ch1LastADC = R_Ch1ADC;

	//探头出现短路或开路故障
	E_ALARM = ((R_Ch1Temp == D_OpenCircuit) || (R_Ch1Temp == D_ShortCircuit)) ? ER_ALARM : NO_ALARM;
	// 蜂鸣器报警处理
	Temp.C = R_Ch1Temp;
	Temp.F = F_CtoF(Temp.C);
	Temp.Display = (B_CF == D_C) ? Temp.C : Temp.F;
	Temp.Display += S_SET.CA;
	if (B_CF == D_C)
	{
		Temp.C = Temp.Display;
		Temp.F = F_CtoF(Temp.C);
	}
	else {
		Temp.F = Temp.Display;
		Temp.C = F_FtoC(Temp.F);
	}

	if (E_ALARM != ER_ALARM)
	{
		E_ALARM = (Temp.Display >= S_SET.AH) ? AH_ALARM : (Temp.Display <= S_SET.AL) ? AL_ALARM : NO_ALARM;
	}
	// B_BuzAlramEn = (E_ALARM == NO_ALARM) ? D_DISABLE : D_ENABLE;
	// if (E_ALARM == NO_ALARM)
	// 	B_BuzKeyBreak = D_DISABLE;
	if (E_ALARM == NO_ALARM)
	{
		if (!B_BuzKeyAlramEn)
		{   //没有按键
			R_Buz10HzCnt = 0;
			R_BuzCycleCnt = 0;
			F_BUZOFF();
		}
	}
	F_Ctrl_220V_OnOff();
	if (Temp_LA.C != Temp.C)
	{
		Temp_LA.C = Temp.C;
		B_TempChange = 1;
	}
	if (B_LEDMode == D_LEDON)
	{
		if (B_TempChange)
		{
			B_TempChange = 0;
			FLAG_TEMP_C = 1;
			FLAG_TEMP_F = 1;
		}
	}
	if (E_ALARM_LAST != E_ALARM)
	{
		E_ALARM_LAST = E_ALARM;
		FLAG_FAULT_ALARM = 1;			// 故障状态发生变化上传
	}
}
