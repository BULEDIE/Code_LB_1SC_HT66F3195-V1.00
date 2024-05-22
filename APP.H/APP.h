#ifndef __APP_H__
#define	__APP_H__

typedef union
{
    u32 ucVal;
    u8 uVal[4];
    struct
    {
        u8  bit0 : 1;
        u8  bit1 : 1;
        u8  bit2 : 1;
        u8	bit3 : 1;
        u8  bit4 : 1;
        u8  bit5 : 1;
        u8  bit6 : 1;
        u8  bit7 : 1;
        u8  bit8 : 1;
        u8  bit9 : 1;
        u8  bit10 : 1;
        u8	bit11 : 1;
        u8  bit12 : 1;
        u8  bit13 : 1;
        u8  bit14 : 1;
        u8  bit15 : 1;
        u8  bit16 : 1;
        u8  bit17 : 1;
        u8  bit18 : 1;
        u8	bit19 : 1;
        u8  bit20 : 1;
        u8  bit21 : 1;
        u8  bit22 : 1;
        u8  bit23 : 1;
        u8  bit24 : 1;
        u8  bit25 : 1;
        u8  bit26 : 1;
        u8	bit27 : 1;
        u8  bit28 : 1;
        u8  bit29 : 1;
        u8  bit30 : 1;
        u8  bit31 : 1;
    }Bit;
}AppFlag;

MyDef AppFlag AFlag;
#define B_64HzFlag              AFlag.Bit.bit0
#define B_32HzFlash 		    AFlag.Bit.bit1
#define B_16HzFlash 		    AFlag.Bit.bit2
#define B_8HzFlash 			    AFlag.Bit.bit3
#define B_4HzFlash 		        AFlag.Bit.bit4
#define B_2HzFlash 			    AFlag.Bit.bit5
#define B_1HzFlash 			    AFlag.Bit.bit6
#define B_PVNEG 			    AFlag.Bit.bit7
#define B_PVPOINT               AFlag.Bit.bit8   /* 1:SV显示负号,0:显示空 */
#define B_LookStartWarmTemp     AFlag.Bit.bit9
#define B_TempChange            AFlag.Bit.bit10
#define B_First_Display         AFlag.Bit.bit11
#define B_FirstVALI             AFlag.Bit.bit12
#define B_WifiReset             AFlag.Bit.bit13
#define B_WifiConfigMode	    AFlag.Bit.bit14
#define B_WifiConfigState       AFlag.Bit.bit15
#define B_SetDataFlag           AFlag.Bit.bit16
#define B_KEYSET 	            AFlag.Bit.bit17
#define B_KEYONOFF              AFlag.Bit.bit18
#define B_BuzKeyBreak           AFlag.Bit.bit19
#define B_BuzAlramEn            AFlag.Bit.bit20
#define B_BuzKeyAlramEn         AFlag.Bit.bit21
#define B_XOR_LED_TEST          AFlag.Bit.bit22
#define B_RST_SP                AFlag.Bit.bit23 // 上电或者退出设置，C,WM的SP判断
#define B_FLASH_ST              AFlag.Bit.bit24 // 延时闪烁：>=ST的时候才开始计数

// #define B_TestMode  	        AFlag.Bit.bit30

MyDef UBYTE R_RxFlag;
#define B_HEAT              R_RxFlag.Bit.bit0
#define B_PRODUCT           R_RxFlag.Bit.bit1
#define B_WifiMode          R_RxFlag.Bit.bit2
#define B_WIFI_STATE        R_RxFlag.Bit.bit3


/* 状态发生变化，设置上传标志位，上传完成，标志位清零
   使用此标志位可单独上报数据点*/
MyDef AppFlag WIFI_DP_Update_Flag;
#define FLAG_CF 		    WIFI_DP_Update_Flag.Bit.bit0
#define FLAG_HC        		WIFI_DP_Update_Flag.Bit.bit1
#define FLAG_ST 	        WIFI_DP_Update_Flag.Bit.bit2
#define FLAG_SP 		    WIFI_DP_Update_Flag.Bit.bit3
#define FLAG_AH        		WIFI_DP_Update_Flag.Bit.bit4
#define FLAG_AL         	WIFI_DP_Update_Flag.Bit.bit5
#define FLAG_PT         	WIFI_DP_Update_Flag.Bit.bit6
#define FLAG_CA      	    WIFI_DP_Update_Flag.Bit.bit7
#define FLAG_TEMP_C 	    WIFI_DP_Update_Flag.Bit.bit8
#define FLAG_TEMP_F         WIFI_DP_Update_Flag.Bit.bit9
#define FLAG_OUT_STATE      WIFI_DP_Update_Flag.Bit.bit10
#define FLAG_FAULT_ALARM 	WIFI_DP_Update_Flag.Bit.bit11

//  #define B_HEAT               WIFI_DP_Update_Flag.Bit.bit19
//  #define B_PRODUCT            WIFI_DP_Update_Flag.Bit.bit20
//  #define B_WifiMode           WIFI_DP_Update_Flag.Bit.bit21
//  #define B_WIFI_STATE         WIFI_DP_Update_Flag.Bit.bit22
#define B_WIFI_Reset         WIFI_DP_Update_Flag.Bit.bit23
#define B_WIFI_ModeSwi       WIFI_DP_Update_Flag.Bit.bit24

typedef enum
{
    HEAT_OFF, HEAT_ON, COOL_OFF, COOL_ON,
} Ctrl_OUT;
MyDef Ctrl_OUT B_OUT_STATE;
MyDef Ctrl_OUT B_OUT_STATE_LAST;

typedef enum
{
    NO_ALARM, ER_ALARM, AH_ALARM, AL_ALARM,
} ALARM_STATE;
MyDef ALARM_STATE E_ALARM;
MyDef ALARM_STATE E_ALARM_LAST;

MyDef volatile u8 B_DispMode;
MyDef volatile u8 R_Mode;
MyDef volatile u8 R_Mode1;

MyDef volatile u8 R_TestMode;
MyDef volatile u8 R_RSSI;
MyDef volatile u8 R_CONFIG;

MyDef volatile u16 R_Timer1HzCnt;
MyDef volatile u8 R_TimeOutCnt; /* 超时机制 */
MyDef volatile u8 R_1Khz1msCnt;/* 2.048ms * 488 = 1s */
MyDef volatile u16 R_1hz1sCnt;
MyDef volatile u8 R_Buz10HzCnt;/* 100ms 蜂鸣器鸣叫间隔 */

MyDef volatile u8 R_BuzCycleCnt;/* 62.5ms 蜂鸣器鸣叫间隔 */
MyDef volatile u8 R_ReturnCnt;
MyDef volatile u8 R_Indexes;
MyDef volatile u8 R_CheakSum;
MyDef volatile u8 R_MENU;
MyDef volatile u8 B_Menu_Enter;

MyDef volatile u8 Indx;
MyDef volatile u8 R_RxRecvTimeOut;
MyDef volatile u16 Count64Hz;
MyDef volatile u16 Tx_Index;
MyDef volatile u16 Tx_OK_Delay;/* 间隔10ms */

#define     D_Tx_OK_Delay_Interval 10
#define     D_ReturnCnt	     30

MyDef u8 R_Wifi_State;
MyDef u8 B_LEDMode;
#define D_SmartMode  0x00   //Smart配网
#define D_APMode     0x01   //AP配网
#define D_LEDOFF     0x02
#define D_LEDON1     0x03
#define D_LEDON      0x04

typedef struct {
    u8 R_Second;
    u8 R_Minute;
    u8 R_Hour;
    u8 R_Day;
    u8 R_Month;
    u8 R_Year;
    u8 R_Week;
    u8 R_GetTimeOK;
}SYSTEMTIME;
MyDef SYSTEMTIME S_SysTime;

void F_TimeService();

#endif