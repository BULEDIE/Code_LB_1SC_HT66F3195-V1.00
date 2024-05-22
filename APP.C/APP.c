#include "Main.h"

void F_ReturnNormalMode(u8 ReturnCnt)
{
	/* 如果在设置状态下，
		30秒内无任何按键操作\或者长按SET键2秒，
		退出且保存设置状态，返回正常工作模式。 */
	if ((R_Mode == D_SET) || (R_Mode1 == D_SET))
	{
		R_ReturnCnt++;
		if (R_ReturnCnt >= ReturnCnt)
		{
			R_Mode = D_NOR;
			R_Mode1 = D_NOR;
			R_ReturnCnt = 0;
			if (R_MENU != D_APP)
				R_MENU = D_CF;
			B_Menu_Enter = D_SET_Menu;
			B_RST_SP = TRUE;
		}
	}
}

void F_AppSendParaTimeOut()
{
	//////F_TESTTIME();
	if (R_TimeOutCnt)//125ms调用，400ms大于APP下发设置参数7帧时间。
	{
		R_TimeOutCnt--;
		if (R_TimeOutCnt == FALSE)
		{
			// F_TESTTIME();
			B_KEYSET = 1;/* 保存参数到EEPROM */
			// FLAG_TEMP_C = 1;
			// FLAG_TEMP_F = 1;
			// FLAG_OUT_STATE = 1;
		}
	}
}

void F_LookSeeStartHeat5sCnt()
{
	static u8 R_CHCnt = 0;
	if (B_LookStartWarmTemp)
	{	/* 查看加热设置温度时间5秒 */
		if (++R_CHCnt >= 8)
		{
			R_CHCnt = 0;
			B_LookStartWarmTemp = 0;//复位
		}
	}
}
void F_APPSymbolDisplay2sCnt()
{
	static u8 R_APPCnt = 0;
	if (R_MENU == D_APP)
	{
		B_PVPOINT = _SEG_OFF;
		B_PVPOINT = _SEG_OFF;
		B_Menu_Enter = D_SET_Menu;
		R_ReturnCnt = 0;
		R_APPCnt++;
		if (R_APPCnt == 2)//连续7帧为337ms,必须大于500ms//(R_APPCnt不能设置为1)
			F_SaveDataToEEPROM();//保存参数时，有关闭全局中断操作，会影响RX接收，设置参数后延时0.5秒保存参数
		else  if (R_APPCnt >= 4)	 //APP下发参数太快，。下发时间不能小于0.5s,必须先等待存储完毕后再下发，
		{
			R_APPCnt = 0;		 //避免突然断电，参数未保存
			R_MENU = D_CF;
			if (R_Mode != D_TES)
				R_Mode = D_NOR;
			R_Mode1 = D_NOR;
		}
	}
}

void F_LED8HzFlash()
{
	if ((B_WifiConfigState == _FAIL)
		&& (B_LEDMode == D_SmartMode)
		&& (R_MENU != D_APP))
	{
		//B_8HzFlash ^= 1;
		SEG8 = _SEG_OFF;/* 负号、及左上角LED点  */
	}
}
void F_LED2HzFlash()
{
	if ((B_WifiConfigState == _FAIL)
		&& (B_LEDMode == D_APMode)
		&& (R_MENU != D_APP))
	{
		//B_1HzFlash ^= 1;
		SEG8 = _SEG_OFF;/* 负号、及左上角LED点  */
	}
}

// 	制冷延时闪烁
void F_COOLFlash()
{
/* 	if ((B_HC == D_COOL_MODE)
		&& (Temp.Display >= S_SET.SP)
		&& (Runing_PT != FALSE)
		&& (B_FLASH_ST == TRUE)) */
	if (B_FLASH_ST == TRUE)
	{
		F_Cool_Led_Off();
		if (B_2HzFlash)
		{
			F_Cool_Led_On();
		}
	}
}

/******************************************************************************
 * @author :Liwenhua
 * @date   :2023:9:26
 * @brief  :单次倒计时
 * @param  :None
 * @retval :倒计时进行时标志位(TRUE)，倒计时结束标志位(FALSE)
 ******************************************************************************/
u8 F_Down_Cnt_Task(u8* temp)
{
	static u8 buf = 0;
	buf = *temp;
	if (buf)
	{
		buf--;
		*temp = buf;
		if (buf == FALSE)
			return FALSE;
	}
	return TRUE;
}

void F_SetHmi_Flash_Disp_DownCnt_Task()
{
	if (F_Down_Cnt_Task((u8*)&Key.Lcd2Hz) == FALSE)
		Key.HoldTime = FALSE;
	if (Key.Lcd2Hz)
	{
		if (Key.HoldTime <= D_LongKey6s)
			Key.HoldTime++;
		if (Key.HoldTime >= D_LongKey6s)
			Key.Speed = 0;
		else if (Key.HoldTime >= D_LongKey4s)
			Key.Speed = 5;
		else if (Key.HoldTime >= D_LongKey2s)
			Key.Speed = 10;
		else
			Key.Speed = 15;
		//   F_Printf_ASCLL(TX_PIN5, " Key.Speed:", Key.Speed, _ONE);
	}
}

void F_TimeService()
{
	while (B_64HzFlag)
	{
		B_64HzFlag--;
		F_SetHmi_Flash_Disp_DownCnt_Task();
		if (!(Count64Hz & 0x01))
		{
			B_32HzFlash ^= 1;
			F_LED8HzFlash();
			if (!(Count64Hz & 0x03))
			{
				B_16HzFlash ^= 1;
				if (!(Count64Hz & 0x07))
				{
					B_8HzFlash ^= 1;
					F_AppSendParaTimeOut();
					if (!(Count64Hz & 0x0F))
					{
						B_4HzFlash ^= 1;
						if (!(Count64Hz & 0x1F))
						{
							B_2HzFlash ^= 1;
							F_LED2HzFlash();
							F_COOLFlash();
							F_APPSymbolDisplay2sCnt();
							F_LookSeeStartHeat5sCnt();
							if (!(Count64Hz & 0x3F))
							{
								F_TESTTIME();
								Count64Hz = 0;
								B_First_Display = 0;
								B_1HzFlash ^= 1;
								F_GetTempValue();
								F_ReturnNormalMode(D_ReturnCnt);
							}
						}
					}
				}
			}
		}
	}
}
