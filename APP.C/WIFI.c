#include "Main.h"

/**
 * @brief  内存拷贝
 * @param[out] {dest} 目标地址
 * @param[in] {src} 源地址
 * @param[in] {count} 拷贝数据个数
 * @return 数据处理完后的源地址
 */
void *my_memcpy(void *dest, const void *src, unsigned short count)
{
    u8 *pdest = (u8 *)dest;
    const u8 *psrc  = (const u8 *)src;
    unsigned short i;

    if(dest == NULL || src == NULL) {
        return NULL;
    }

    if((pdest <= psrc) || (pdest > psrc + count)) {
        for(i = 0; i < count; i ++) {
            pdest[i] = psrc[i];
        }
    }else {
        for(i = count; i > 0; i --) {
            pdest[i - 1] = psrc[i - 1];
        }
    }

    return dest;
}

/**
 * @brief  写wifi_uart_buffer
 * @param[in] {dest} 目标地址
 * @param[in] {src} 源地址
 * @param[in] {len} 数据长度
 * @return 写入结束的缓存地址
 */
unsigned short set_wifi_uart_buffer(unsigned short dest, const u8 *src, unsigned short len)
{
    u8 *obj = (u8 *)MCU_TX.DATA + DATA_START + dest;

    my_memcpy(obj,src,len);

    dest += len;
    return dest;
}

/**
 * @brief  求字符串长度
 * @param[in] {str} 字符串地址
 * @return 数据长度
 */
u32 my_strlen(u8 *str)
{
    //u32 len = 0;
    u8 len = 0;
    if(str == NULL) {
        return 0;
    }
    for(len = 0; *str ++ != '\0'; ) {
        len ++;
    }
    return len;
}

/**
 * @brief  写wifi_uart字节
 * @param[in] {dest} 缓存区其实地址
 * @param[in] {byte} 写入字节值
 * @return 写入完成后的总长度
 */
unsigned short set_wifi_uart_byte(unsigned short dest, u8 byte)
{
    u8 *obj = (u8 *)MCU_TX.DATA + DATA_START + dest;
    *obj = byte;
    dest += 1;

    return dest;
}
/**
 * @brief  串口发送一段数据
 * @param[in] {in} 发送缓存指针
 * @param[in] {len} 数据发送长度
 * @return Null
 */
void wifi_uart_write_data(u8 *in, unsigned short len)
{
    if((NULL == in) || (0 == len)) {
        return;
    }

    while(len --) {
        while(_tidle==0||_txif==0);
        _txr_rxr = *in;
        in++;
    }
}

u8 F_GetSum(u8 *addr, u8 Length)
{
	u8 i;
	u8 sum = 0;
	for(i=0; i<Length; i++)
		sum += *addr++;
	return sum;
}

/* 第七步 */
void F_MCU_TX_Service(void)
{
    u8 i = 0;
    if((!B_WIFI_Reset)&&(!B_WIFI_ModeSwi)){
        if(!(B_LEDMode == D_LEDON
            ||B_LEDMode == D_LEDOFF
            ||B_LEDMode == D_LEDON1))
        return;
    }
    if (!((R_Mode == D_NOR) && (R_Mode1 == D_NOR) && (R_ReturnCnt == 0)))/* 退出设置模式才去判断 */
        return;
    if (Tx_OK_Delay)
        return;
    if (R_MENU == D_APP)//接收完毕再上传
        return;
    if(R_Indexes != 0)//接收完毕再上传
        return;
    if(Key.Up&&Key.Now)// 按键没有抬起
       return;/* 退出设置状态再上传设置参数，避免按键设置参数显示卡顿 */
    if(Tx_Index != 0)//接收完毕再上传
        return;
    if(WIFI_DP_Update_Flag.ucVal)
    {
        if(FLAG_FAULT_ALARM)
        {
            mcu_dp_enum_update(DPID_ALARM, E_ALARM);
            FLAG_FAULT_ALARM = 0;
        }
        else if(FLAG_CF)
        {
            mcu_dp_enum_update(DPID_CF, B_CF);
            FLAG_CF = 0;
        }
        else if (FLAG_HC)
        {
            mcu_dp_enum_update(DPID_HC, B_HC);
            FLAG_HC = 0;
        }
        else if(FLAG_TEMP_C)
        {
            mcu_dp_value_update(DPID_TEMP_C, Temp.C);
            FLAG_TEMP_C = 0;
        }
        else if(FLAG_TEMP_F)
        {
            mcu_dp_value_update(DPID_TEMP_F, Temp.F);
            FLAG_TEMP_F = 0;
        }
        else if(FLAG_ST)
        {
            mcu_dp_value_update(DPID_ST, S_SET.ST);
            FLAG_ST = 0;
        }
        else if(FLAG_SP)
        {
            mcu_dp_value_update(DPID_SP, S_SET.SP);
            FLAG_SP = 0;
        }
        else if(FLAG_AH)
        {   mcu_dp_value_update(DPID_AH,S_SET.AH);
            FLAG_AH = 0;
        }
        else if(FLAG_AL)
        {   mcu_dp_value_update(DPID_AL,S_SET.AL);
            FLAG_AL = 0;
        }
        else if(FLAG_CA)
        {   mcu_dp_value_update(DPID_CA,S_SET.CA);
            FLAG_CA = 0;
        }
        else if (FLAG_PT)
        {
            mcu_dp_value_update(DPID_PT, S_SET.PT);
            FLAG_PT = 0;
        }
        else if(FLAG_OUT_STATE)
        {
            mcu_dp_enum_update(DPID_STATE, B_OUT_STATE);
            FLAG_OUT_STATE = 0;
        }else if(B_WIFI_Reset)
        {
        	F_WifiConfigModeReset(D_SmartMode);
            B_WIFI_Reset = 0;
        }
        else if(B_WIFI_ModeSwi)
        {   F_WifiConfigModeSwitch(B_WifiConfigMode);
            B_WIFI_ModeSwi = 0;
        }
    }
    i = 0;
    while(Tx_Index!=0)
    {
        while(_tidle==0||_txif==0);
            _txr_rxr = MCU_TX.DATA[i++];
        Tx_Index--;
    }
    Tx_Index = 0;
    Tx_OK_Delay = D_Tx_OK_Delay_Interval;
}

void F_GetNetworkTime()
{
    if(MCU_RX.DATA[6])
    {   /* 获取网络时间成功 */
        S_SysTime.R_Year   = MCU_RX.DATA[7];
        S_SysTime.R_Month  = MCU_RX.DATA[8];
        S_SysTime.R_Day    = MCU_RX.DATA[9];
        S_SysTime.R_Hour   = MCU_RX.DATA[10];
        S_SysTime.R_Minute = MCU_RX.DATA[11];
        S_SysTime.R_Second = MCU_RX.DATA[12];
        S_SysTime.R_Week   = MCU_RX.DATA[13];
        S_SysTime.R_GetTimeOK  = 1;
    }
}

void F_GetRssi()
{
    //获取指定wifi产测信号强度。/上电等待时间5秒。
    //获取当前 Wi-Fi 信号强度,命令不一样。
    R_CONFIG = MCU_RX.DATA[6];
	R_RSSI = MCU_RX.DATA[7];
}

s32 F_GetSetValue()
{
    SLONG value;
    /* 大端低位地址存放高位 */
    value.Byte.byte0 = MCU_RX.BUFF.DAT10;
    value.Byte.byte1 = MCU_RX.BUFF.DAT11;
    value.Byte.byte2 = MCU_RX.BUFF.DAT12;
    value.Byte.byte3 = MCU_RX.BUFF.DAT13;
    return value.lVal;
}
#define F_WIFI_FLAG()   {R_MENU = D_APP; R_TimeOutCnt = 4; B_KEYSET = 1;}

void F_TXParameter(u8 temp)
{
     while(_tidle==0||_txif==0);
     _txr_rxr = temp;
}

void F_Wifi_State(void)
{
    if (B_LEDMode == D_LEDOFF) 		R_Wifi_State = _SEG_OFF;/* 左上角LED点2 */
    else if (B_LEDMode == D_LEDON)	R_Wifi_State = _SEG_ON; /* 左上角LED点2 */
    else if (B_LEDMode == D_LEDON1)	R_Wifi_State = _SEG_ON; /* 左上角LED点2 */
    else if ((B_WifiConfigState == _FAIL) && (R_MENU != D_APP))
    {
        if (!B_First_Display)
        {
            if (((B_LEDMode == D_SmartMode) && (B_8HzFlash))
                || ((B_LEDMode == D_APMode) && (B_1HzFlash)))
                R_Wifi_State = _SEG_ON;
            else
                R_Wifi_State = _SEG_OFF;
        }
    }
    else
        R_Wifi_State = _SEG_OFF;
}

void F_MCU_RX_Service(void)
{
    s16 temp = 0;
    u8 length = 0;
    if ((R_Indexes > 6) && (R_RxRecvTimeOut == 0))
    {   //必须大于6//否则开关命令0x550xaa0x000x060x00 = 0x05

        F_TESTTIME();
        F_TESTTIME();
        F_TESTTIME();
        R_CheakSum = F_GetSum(MCU_RX.DATA, (R_Indexes - 1));
        if (MCU_RX.DATA[R_Indexes - 1] == R_CheakSum)
        {
            F_TESTTIME();
            F_TESTTIME();
            F_TESTTIME();
            F_TESTTIME();
            F_TESTTIME();
            F_TESTTIME();
            if (MCU_RX.DATA[3] == HEAT_BEAT_CMD)
            {
                R_Indexes = 0;//心跳包收到后立即清除索引，避免下发命令索引重合
                F_UART_RAM_INIT();
                if (B_WifiReset) {
                    B_WifiReset = 0;
                    mcu_Send_Cmd(HEAT_BEAT_CMD, 0x00);
                }
                else
                    mcu_Send_Cmd(HEAT_BEAT_CMD, 0x01);
                if (B_LEDMode == D_LEDON)
                {
                    FLAG_TEMP_C = 1;
                    FLAG_TEMP_F = 1;
                }
            }
            else if (MCU_RX.DATA[3] == PRODUCT_INFO_CMD)
            {
                length = 0;
                length = set_wifi_uart_buffer(length, (u8*)_P_, my_strlen((u8*)_P_));
                length = set_wifi_uart_buffer(length, (u8*)PRODUCT_KEY, my_strlen((u8*)PRODUCT_KEY));
                length = set_wifi_uart_buffer(length, (u8*)_V_, my_strlen((u8*)_V_));
                length = set_wifi_uart_buffer(length, (u8*)MCU_VER, my_strlen((u8*)MCU_VER));
                length = set_wifi_uart_buffer(length, (u8*)_M_, my_strlen((u8*)_M_));
                length = set_wifi_uart_buffer(length, (u8*)CONFIG_MODE, my_strlen((u8*)CONFIG_MODE));
                length = set_wifi_uart_buffer(length, (u8*)_Y_, my_strlen((u8*)_Y_));
                wifi_uart_write_frame(PRODUCT_INFO_CMD, 0x00, length);
            }
            else if (MCU_RX.DATA[3] == WORK_MODE_CMD)
            {
                wifi_uart_write_frame(WORK_MODE_CMD, 0x00, 0x0000);
            }
            else if (MCU_RX.DATA[3] == WIFI_STATE_CMD)
            {
                B_LEDMode = MCU_RX.DATA[6];
                wifi_uart_write_frame(WIFI_STATE_CMD, 0x00, 0);
                if (B_LEDMode == D_LEDON)
                    WIFI_DP_Update_Flag.ucVal = 0x00000FFF;
            }
            else if (MCU_RX.DATA[3] == WIFI_RESET_CMD)
            {
                _nop();//WIFI上报
            }
            else if (MCU_RX.DATA[3] == WIFI_MODE_CMD)
            {
                mcu_Send_Cmd(WIFI_MODE_CMD, B_WifiConfigMode);
            }
            else if (MCU_RX.DATA[3] == STATE_QUERY_CMD)
            {     WIFI_DP_Update_Flag.ucVal = 0x00000FFF;
                Tx_OK_Delay = 80;
            }
            else if (MCU_RX.DATA[3] == GET_LOCAL_TIME_CMD)/* 获取本地时间 */
                F_GetNetworkTime();
            else if(MCU_RX.DATA[3] == WIFI_TEST_CMD)/* WiFi功能 产测( 注：扫描 tuya_mde v_test的 指定SSID) */
                F_GetRssi();
            else
            {
                temp = F_GetSetValue();
                if(MCU_RX.DATA[6] == DPID_CF)
                {
                    /* app,下发只有状态发生变化，才能下发。注意这里给可能有问题 */
                    B_CF = MCU_RX.DATA[10];
                    F_DefaultSettings(B_CF, B_HC);
                    FLAG_CF = 1;
                    F_WIFI_FLAG();
                }
                if (MCU_RX.DATA[6] == DPID_HC)
                {
                    S_SET_LAST.HC = B_HC;
                    B_HC = MCU_RX.DATA[10];
                    if (S_SET_LAST.HC != B_HC)
                    {
                        S_SET_LAST.HC = B_HC;
                        F_HEAT_COOL_MODE_SW();
                    }
                    FLAG_HC = 1;
                    F_WIFI_FLAG();
                }
                if (MCU_RX.DATA[6] == DPID_PT)
                {
                    S_SET.PT = temp;
                    FLAG_PT = 1;
                    F_WIFI_FLAG();
                }
                else if (MCU_RX.DATA[6] == DPID_ST)
                {
                    S_SET.ST = temp;
                    FLAG_ST = 1;
                    F_WIFI_FLAG();
                }
                else if (MCU_RX.DATA[6] == DPID_SP)
                {
                    S_SET.SP = temp;
                    FLAG_SP = 1;
                    F_WIFI_FLAG();
                }
                else if (MCU_RX.DATA[6] == DPID_AH)
                {   S_SET.AH = temp;
                    FLAG_AH = 1;
                    F_WIFI_FLAG();
                }
                else if(MCU_RX.DATA[6] == DPID_AL)
                {   S_SET.AL = temp;
                    FLAG_AL = 1;
                    F_WIFI_FLAG();
                }
                else if (MCU_RX.DATA[6] == DPID_CA)
                {
                    S_SET_LAST.CA = temp;
                    if (S_SET.CA != S_SET_LAST.CA)
                    {
                        Temp.Display -= S_SET.CA;
                        S_SET.CA = S_SET_LAST.CA;
                        Temp.Display += S_SET.CA;
                    }
                    FLAG_CA = 1;
                    F_WIFI_FLAG();
                }
                // F_TXParameter((u8)(temp>>8));
                // F_TXParameter((u8)temp);
            }
            R_Indexes = 0;/* 校验通过说明下发一帧数据完成 */
            F_UART_RAM_INIT();
        }
        R_Indexes = 0;/* 校验通过说明下发一帧数据完成 */
        F_UART_RAM_INIT();
    }
}

/*
    ITC306A_5D26H_D5CBH_HT66F489_SOP28_V03
    1.增加以下功能。
      由于数码管只能显示3位数，TS1和TS2在大于100.0F时，不显示小数点。
      度F单位下，TS1与TS2的最小回差值为0.5F
      假如：TS1=100.0F,TS2=100.5F，数码管TS1和TS2都会显示100，
      避免客户误会，在设置TS1TS2参数大于。100.0F 时，
      TS1与TS2的回差值自动切换为1.0F。
    2.增加出现任意故障，蜂鸣器BiBi报警时，APP下发关机命令，依然报警问题。
      即为APP下发关机命令可以打断蜂鸣器报警声音。
    3.修改在产测模式下和设置度温度单位时，快速按按键，蜂鸣器连续Bi问题。
 */
/*
    1.修改，AL低温报警时候，按键打断蜂鸣器响声，加热状态指示灯也被关闭问题。
    //2.修改，产测模式下，按UP键，0.5s间隔打开继电器，红色指示灯点亮的同时。关闭绿色指示灯。
    //  修改，产测模式下，按down键，0.5s间隔关闭继电器，红色指示灯点灭的同时。打开绿色指示灯。
    //  修改，产测模式下，按set键，关闭继电器及红色、绿色指示灯。
    3.每次有UART\TB0时基中断、产生、全局中断被清除，退出中断再恢复全局中断使能，
      导致在UART中断接收数据时候，此时产生TB0时基中断，导致UART数据接收失败。
      解决方法使能，嵌套使能，堆栈。
    4.等待解决，中断溢出问题。
        每次有下发命令，延时到显示D_APP执行任务，错开堆栈溢出问题。

    5.样机，问题
    1.主机设置参数的时候，此时APP下发设置参数，导致温度单位不对


 */
