#include "Main.h"

void F_Look_Menu()
{
	if (R_Mode1 == D_NOR)
	{
		if (R_MENU == D_CF)
		{	R_Mode1 = D_SET;
			R_MENU = D_ST;
			B_LookStartWarmTemp = 1;
		}
	}
	else if (++R_MENU > D_SP)
	{
		R_MENU = D_CF;//复位
		R_Mode1 = D_NOR;
	}
}

void F_KEY_WifiConfig()
{
	if ((R_Mode == D_NOR) && (R_Mode1 == D_NOR))
	{	/* 配网失败情况下 */
		B_WifiConfigMode ^= 1;
		// B_LEDMode = B_WifiConfigMode;
		if (B_LEDMode == D_SmartMode)
			B_LEDMode = D_APMode;
		else if(B_LEDMode == D_APMode)
			B_LEDMode = D_SmartMode;
		B_WIFI_ModeSwi = 1;
		F_WifiConfigModeSwitch(B_WifiConfigMode);
		R_MENU = D_APP;
	}
}

void F_KEY_WifiConfig1()
{
	if ((R_Mode == D_NOR)&&(R_Mode1 == D_NOR))
	{	B_UPKEY = 1;
		B_WifiConfigMode = D_SmartMode;
		B_LEDMode = D_SmartMode;
		B_WIFI_Reset = 1;
		R_MENU = D_APP;
	}
}
