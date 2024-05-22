#include "Main.h"

void F_KeyInit()
{
	Key.Last = 0;
	Key.Now = 0;
	Key.Down = 0;
	Key.Up = 0;
	Key.ValueBuf = 0;
	Key.Value = 0;
	Key.KeepCnt = 0;
}

void F_GetKey()
{
	u8 i;
	static u8 DebounceCnt = 0;
	if (B_Key64HzScan)
	{
		for (i = 0; i < 5; i++)//延时一点时间，等待配置生效，再读取IO口，
		{
			COM0 = _COM_OFF;
			COM1 = _COM_OFF;
			COM2 = _COM_OFF;
			COM3 = _COM_OFF;
			F_SET_KEY_IN_EN_and_PU_EN();
			F_UP_KEY_IN_EN_and_PU_EN();
			F_DOWN_KEY_IN_EN_and_PU_EN();
		}
		Key.Now = 0;//清除上一次消抖键值
		if (!UPKEY_IO)
		{
			Key.Now |= GPIO_PIN_1;
		// F_TESTTIME();
		}
		if (!DOWNKEY_IO)
		{
			Key.Now |= GPIO_PIN_2;
		// F_TESTTIME();
		// F_TESTTIME();
		}
		if (!SETKEY_IO)
		{
			Key.Now |= GPIO_PIN_0;
		// F_TESTTIME();
		// F_TESTTIME();
		// F_TESTTIME();
		}
		F_SET_KEY_OUT_EN_and_PU_DN();
		F_UP_KEY_OUT_EN_and_PU_DN();
		F_DOWN_KEY_OUT_EN_and_PU_DN();
		if (Key.Last != Key.Now)
		{
			if (++DebounceCnt > 2)
			{
				B_KeyChange ^= 1;
				DebounceCnt = 0;
			}
		}
		B_Key64HzScan = 0;
	}
}

void F_KeyScan()
{
	if (B_KeyChange)//消抖OK
	{
		Key.ValueBuf = Key.Now ^ Key.Last;		//(消抖OK锁存键值)  前、后沿消抖
		Key.Down = Key.ValueBuf ^ Key.Last;     //按下标志位
		Key.Up = Key.ValueBuf ^ Key.Now;		//抬起
		if (Key.Down)
		{
			Key.Lcd2Hz = D_Key_Lcd_Disp_Time;
			if (B_Key64HzStep)
			{
				B_Key64HzStep = 0;
				Key.KeepCnt++;
				if ((Key.KeepCnt == D_64Hz) && (B_FirstVALI == 0))
					Key.Value = Key.Last + KEY2S;	//长按超时赋键值
				else if (Key.KeepCnt >= D_LongKey1s + Key.Speed)
				{
					Key.KeepCnt = D_LongKey1s;			// 故长按超过2s,要=2s
					if ((Key.Last != SET_KEY)
						&& (B_FirstVALI == 0)
						&& (B_UPKEY == 0)
						&& (!B_KEYONOFF)
						&& (!(R_MENU == D_CF)))
					{
						Key.Value = Key.Last + KEY2S;
					}
					R_ReturnCnt = 0;
				}
			}
		}
		else if (Key.Up)							//有效抬起
		{
			if (Key.KeepCnt < D_64Hz)
			{
				//Key.Value = Key.Up;			//短按抬起键值
				if (B_FirstVALI)
					B_FirstVALI = 0;
				else
					Key.Value = Key.ValueBuf;	//短按抬起键值
			}
			else {
				Key.Value = 0;					//长按抬起无键值
				if (B_FirstVALI)
					B_FirstVALI = 0;
			}
			Key.KeepCnt = 0;					/* 清除长按计时器 */
			R_ReturnCnt = 0;
			B_UPKEY = 0;
			B_KEYONOFF = 0;
			Key.Lcd2Hz = D_Key_Lcd_Disp_Time;
		}
		Key.Last = Key.Now;						//赋予初始值
	}
}

const s16 T_C_HLValue[8][2] = {
	{D_C , 	D_F	},	//	"CF",
	{D_HEAT_MODE , 	D_COOL_MODE	},	//	"HC",
	{450 , 	0	},	//	"TS1",
	{450 , 	0	},	//	"TS1",
	{500,	-49 },	//	"AH ",
	{499,	-50 },	//	"AL ",
	{10  ,	0	},	//	"PT ",
	{55  ,	-55	}	//	"CA ",
};
const s16 T_F_HLValue[8][2] = {
	{D_C , 	D_F	},	//	"CF",
	{D_HEAT_MODE , 	D_COOL_MODE	},	//	"HC",
	{1130 , 320	},	//	"TS1",
	{1130 , 320 },	//	"TS1",
	{1220,	240 },	//	"AH ",
	{1210,	230 },	//	"AL ",
	{10  ,	0	},	//	"PT ",
	{99  ,	-99 }	//	"CA ",
};

s16 F_SetADD(s16 R_Indexes, s16 R_HiValue)
{
	s16 temp;
	temp = R_Indexes;
	if (temp >= 1000)
		temp += 10;
	else
		temp++;
	if (temp > R_HiValue)
		temp = R_HiValue;
	return temp;
}

s16 F_SetSUB(s16 R_Indexes, s16 R_LowValue)
{
	s16 temp;
	temp = R_Indexes;
	if (temp > 1000)
		temp -= 10;
	else
		temp--;
	if (temp < R_LowValue)
		temp = R_LowValue;
	return temp;
}

#define D_Min_Temp_C	5
#define D_Min_Temp_F	10

void F_SetMenu()
{
	static s16 R_HiValue = 0;
	static s16 R_LowValue = 0;
	if (B_Menu_Enter == D_SET_Param)
	{
		if (!B_SetDataFlag)
			return;
		B_SetDataFlag = 0;
		if (B_CF == D_C)
		{
			R_HiValue = T_C_HLValue[R_MENU][0];
			R_LowValue = T_C_HLValue[R_MENU][1];
		}
		else
		{
			R_HiValue = T_F_HLValue[R_MENU][0];
			R_LowValue = T_F_HLValue[R_MENU][1];
		}
		switch (R_MENU)
		{
		case D_CF:	break;
		case D_ST:
			if (B_HC == D_HEAT_MODE) {
				R_HiValue = S_SET.SP - ((B_CF == D_C) ? D_Min_Temp_C : D_Min_Temp_F);
			}
			else {
				R_LowValue = S_SET.SP + ((B_CF == D_C) ? D_Min_Temp_C : D_Min_Temp_F);
			}
			break;
		case D_SP:
			if (B_HC == D_HEAT_MODE) {
				R_LowValue = S_SET.ST + ((B_CF == D_C) ? D_Min_Temp_C : D_Min_Temp_F);
			}
			else {
				R_HiValue = S_SET.ST - ((B_CF == D_C) ? D_Min_Temp_C : D_Min_Temp_F);
			}
			break;
		case D_AH:	R_LowValue = S_SET.AL + 1; 	break;
		case D_AL:	R_HiValue = S_SET.AH - 1; 	break;
		default:break;
		}
		switch (R_MENU)
		{
		case D_CF:	B_CF ^= D_F;		 F_DefaultSettings(B_CF, B_HC);	 break;
		case D_HC:	B_HC ^= D_COOL_MODE; F_HEAT_COOL_MODE_SW(); 		 break;
		case D_ST:	if (Key.Value & UP_KEY) S_SET.ST = F_SetADD(S_SET.ST, R_HiValue);else if (Key.Value & DOWN_KEY) S_SET.ST = F_SetSUB(S_SET.ST, R_LowValue);FLAG_ST = D_ENABLE;	break;
		case D_SP:	if (Key.Value & UP_KEY) S_SET.SP = F_SetADD(S_SET.SP, R_HiValue);else if (Key.Value & DOWN_KEY) S_SET.SP = F_SetSUB(S_SET.SP, R_LowValue);FLAG_SP = D_ENABLE; 	break;
		case D_AH:	if (Key.Value & UP_KEY) S_SET.AH = F_SetADD(S_SET.AH, R_HiValue);else if (Key.Value & DOWN_KEY) S_SET.AH = F_SetSUB(S_SET.AH, R_LowValue);FLAG_AH = D_ENABLE; 	break;
		case D_AL:	if (Key.Value & UP_KEY) S_SET.AL = F_SetADD(S_SET.AL, R_HiValue);else if (Key.Value & DOWN_KEY) S_SET.AL = F_SetSUB(S_SET.AL, R_LowValue);FLAG_AL = D_ENABLE; 	break;
		case D_PT:  if (Key.Value & UP_KEY) S_SET.PT = F_SetADD(S_SET.PT, R_HiValue);else if (Key.Value & DOWN_KEY) S_SET.PT = F_SetSUB(S_SET.PT, R_LowValue);FLAG_PT = D_ENABLE;	break;
		case D_CA:	if (Key.Value & UP_KEY) S_SET.CA = F_SetADD(S_SET.CA, R_HiValue);else if (Key.Value & DOWN_KEY) S_SET.CA = F_SetSUB(S_SET.CA, R_LowValue);FLAG_CA = D_ENABLE; 	break;
		default:break;
		}
		B_KEYSET = 1;
		Key.Value = 0;
	}
}

void F_HEAT_COOL_MODE_SW()
{
	RELAY_IO = D_OFF;
	F_Heat_Led_Off();
	F_Cool_Led_Off();
	B_OUT_STATE = (B_HC == D_HEAT_MODE) ? HEAT_OFF : COOL_OFF;
	//制冷延时时间不恢复
	S_SET_LAST.PT = S_SET.PT;
	S_SET_LAST.CA = S_SET.CA;
	F_DefaultSettings(B_CF, B_HC);
	S_SET.PT = S_SET_LAST.PT;
	S_SET.CA = S_SET_LAST.CA;
}

void F_KeyRstFactory()
{
	volatile u8 R_FirstCnt = 100;
	F_Delay_Ms(1000);
	while (R_FirstCnt)
	{
		R_FirstCnt--;
		F_Delay_Ms(10);
		if (Key.Value == DOWN_KEY2S)
		{
			B_FirstVALI = 1;
			F_DefaultSettings(D_F, D_HEAT_MODE);//延迟1秒存EEPROM
			R_MENU = D_CF;
			R_BuzCycleCnt = 8;
			B_BuzKeyAlramEn = 1;
			break;
		}
		if (Key.Value == SET_KEY2S) {
			R_TestMode = 4;
			R_Mode = D_TES;//产测模式
			Key.Value = 0;
			R_BuzCycleCnt = 8;
			B_BuzKeyAlramEn = 1;
			// B_TestMode = 1;
			F_DefaultSettings(D_F, D_HEAT_MODE);//延迟1秒存EEPROM
			F_SaveDataToEEPROM();
			break;
		}
		else {
			B_First_Display = 1;
			F_SetBCDINIT();
		}
	}
	if (B_FirstVALI == 0)
	{
		F_ReadEEPROMToRAM();
	}
	// 避免显示0
	// F_GetTempValue();
	R_FirstCnt = 0;
	FLAG_OUT_STATE = 0;
	FLAG_FAULT_ALARM = 0;
	Key.Value = 0;
	// Count64Hz = 0x40;
}

void F_KeySever()
{
	if (Key.Value)
	{
		if (F_KeyBreakFault())
			return;
		if (R_MENU == D_APP) {
			Key.Value = 0;
			return;
		}

		if (R_Mode == D_TES)
		{
			if (R_BuzCycleCnt == 0)
			{
				switch (Key.Value)
				{
				case SET_KEY2S:
					R_TestMode = 0; //退出产测模式
					R_Mode = D_NOR;	//退出产测模式
					// B_TestMode = 0; //退出产测模式
					break;
				case SET_KEY:
					R_TestMode = 3;
					F_Heat_Led_Off();
					F_Cool_Led_Off();
					B_PVPOINT = _SEG_OFF;
					break;
				case UP_KEY:
						//mcu_start_wifitest();//查询WIFI信号强度
						/* mcu发起wifi功能测试 */
					R_TestMode = 1;
					R_CONFIG = 0;
					R_RSSI = 0;
					wifi_uart_write_frame(WIFI_TEST_CMD, MCU_TX_VER, 0);
					RELAY_IO = D_OFF;
					F_Heat_Led_Off();
					F_Cool_Led_Off();
					break;
				case DOWN_KEY:
					R_TestMode = 2;//显示正常温度
					RELAY_IO = D_ON;
					B_XOR_LED_TEST ^= 1;
					(B_XOR_LED_TEST) ? F_Heat_Led_On() : F_Cool_Led_On();
					(B_XOR_LED_TEST) ? F_Cool_Led_Off() : F_Heat_Led_Off();
					break;
				default:break;
				}
				R_BuzCycleCnt = 8;
				B_BuzKeyAlramEn = 1;
			}
		}
		else if (R_Mode == D_NOR)
		{
			switch (Key.Value)
			{
			case SET_KEY:
				F_Look_Menu();
				break;
			case SET_KEY2S:
				if (R_Mode1 == D_NOR)
					R_Mode ^= 1;
				if (R_Mode == D_SET)
					R_MENU = D_CF;
				break;
			case UP_KEY:
				F_KEY_WifiConfig();
				break;
			case UP_KEY2S:
				F_KEY_WifiConfig1();
				break;
			case DOWN_KEY:
				break;
			case DOWN_KEY2S:
				break;
			default:
				break;
			}
		}
		else if ((R_Mode == D_SET) || (R_Mode == D_SET1))
		{
			switch (Key.Value)
			{
			case SET_KEY:
				B_Menu_Enter ^= D_SET_Param;
				break;
			case SET_KEY2S:
				R_MENU = D_APP;
				Runing_PT = FALSE;
				B_RST_SP = TRUE;
				break;
			case UP_KEY2S:
				if (B_Menu_Enter == D_SET_Param) {
					B_SetDataFlag = 1;
				}
				break;
			case UP_KEY:
				if (B_Menu_Enter == D_SET_Param) {
					B_SetDataFlag = 1;
				}
				else if (B_Menu_Enter == D_SET_Menu)
				{
					if (++R_MENU > D_CA)
						R_MENU = D_CF;
					if (B_HC == D_HEAT_MODE)
					{
						if (R_MENU == D_PT)
							R_MENU++;
					}
				}
				break;

			case DOWN_KEY2S:
				if (B_Menu_Enter == D_SET_Param) {
					B_SetDataFlag = 1;
				}
				break;
			case DOWN_KEY:
				if (B_Menu_Enter == D_SET_Param) {
					B_SetDataFlag = 1;
				}
				else if (B_Menu_Enter == D_SET_Menu)
				{
					if (--R_MENU == 0xFF)
						R_MENU = D_CA;
					if (B_HC == D_HEAT_MODE)
					{
						if (R_MENU == D_PT)
							R_MENU--;
					}
				}
				break;
			default:
				break;
			}
		}
		if (!B_SetDataFlag)
			Key.Value = 0;
	}
}
/*
	按键需要定义：WIFI配网功能。WIFI复位功能
	短按快速设置功能就不要了。一个循环也不一定设置成功。

 */

 /* 快速设置控制温度模式
	轻按“SET”键，进入快速设置控制温度模式，此时SV显示设置温度T1并闪烁，
	此时短按或增加或减小设置值，长按或键快速增加或减少设置值，
	再次短按SET键，此时SV显示设置温度T2并闪烁，
	此时短按或增加或减小设置值，长按或键快速增加或减少设置值，
	再次短按SET键确认并退出。若无任何操作，10秒后自动退出且保存设置值。 */

 /* 6.6 连续加热时间报警：
	  当控制器测量温度≤开始加热温度时，
	  打开输出控制，若连续加热时间到达，
	  但测量温度还没有升到停止加热温度时，
	  此时表示加热器异常或者探头异常，强制关闭输出。
	  PV显示E5，蜂鸣器一直响，
	  同时会针报警状态推送至手机APP端，
	  提醒客户该产品处于报警状态，及时检查。 */

 /* 6.7 温度校正（CA）
		当测量温度和标准温度有偏差时，
		可使用温度校正功能，
		使仪表的测量值与标准值一致，
		校正后的温度等于当前温度值+校正值。 */
 /* 6.8 华氏或摄氏设置 （CF）
		用户可以根据使用习惯，设置显示单位为华氏或摄氏，
		默认的温度为华氏。如果需要显示单位为摄氏，
		那么将CF值设置为C即可。
		注意，当CF改变状态时，所有的设置值，
		恢复到出厂设定状态，且蜂鸣器短叫一声提示。 */

 /* 8.APP */
	/* 在AppStore或GooglePlay中搜索关键字“InkbirdSmart”，
		或扫描以下QR代码下载和安装应用程序。 */
	/* ③如果控制器处于正常工作状态，您可以 （长按UP键） 2秒重置WIFI。
		默认情况下，它将进入（智能配置配置状态）。
		您可以（短按UP键) 以切换 (智能配置状态)和AP模式。
		如果更改WiFi状态，则需要大约5秒才能显示相应的LED符号和状态，
		因为WiFi模块的数据处理 g. */

/* SmartConfig *//* 智能配置状态 */
	/* 添加处于快速连接中的设备： */
	/* ●将该设备插入插槽中，并确保该设备在智能配置中。 */
	/* ●配置状态（LED符号闪烁，间隔闪烁250ms）。
		点击“确认指示灯快速闪烁”，然后选择Wi-Fi网络，进入 */
	/* Wi-Fi密码，点击“确认”进入连接过程。  */
	/* ●：该设备只支持2.4千兆赫兹的Wi-Fi路由器。 */

/* APConfig： *//* wifi模块发射热点 */
	/* ●将设备插入插座，并确保设备处于AP配置状态
		(LED符号缓慢闪烁，间隔闪烁1500ms)。 */
	/* ●点击“确认指示灯缓慢闪烁”，
		然后选择Wi-Fi网络，输入Wi-Fi密码，
		点击“确认”进入连接过程。 */
	/* ●按“立即连接”，它将转到您的WLAN设置在您的智能手机，
		选择“SmartLife-xxxx”直接连接到涂鸦wifi模块热点，没有密码。 */
	/* ●回到APP进入自动连接界面。 */
	/* ④成功后点击“完成”，进入设备控制界面。 */
	/* ⑤在温度控制模式下，用户可以通过APP设置控制功能。 */

/* SmartConfig */
/* 智能配置状态 */
/* 1.手机连接可上网路由器：WIFI热点 输入密码 */
/* 2.添加设备：ITC-306  且处于LED 250ms闪烁 (智能配置状态下)*/
/*   再次 WIFI热点 及密码 */
/* 此时 ITC-306 设备将通过路由器 wifi 热点成功连接手机，实现通讯 */
/* 具有保存记忆功能，无需再次配对 */

/* 具有多台 ITC-306 设备的时候，同时配网*/
/* 步骤：首先 每一台单独设置 智能配置状态*/
/* 步骤：避免干扰*/
/* SmartConfig属于 客户端？*/

/* 客户端：用户端 */
/* 服务端：服务器 */


/* 在AP模式下添加设备： */
/* WIFI模块 发射wifi热点，及密码，建立服务器 */
/* 手机APP 主动连接 */
