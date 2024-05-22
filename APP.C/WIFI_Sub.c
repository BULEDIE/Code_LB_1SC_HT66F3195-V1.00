#include "Main.h"

void mcu_Send_Cmd(u8 cmd,u8 Mode)
{
	u8 i;
	u8 sum = 0;
    MCU_TX.DATA[HEAD_FIRST] = 0x55;
    MCU_TX.DATA[HEAD_SECOND] = 0xaa;
    MCU_TX.DATA[PROTOCOL_VERSION] = MCU_TX_VER;
    MCU_TX.DATA[FRAME_TYPE] = cmd;
    MCU_TX.DATA[LENGTH_HIGH] = 0x00;
    MCU_TX.DATA[LENGTH_LOW] = 0x01;
    MCU_TX.DATA[DATA_START] = Mode;
	for(i=0; i<(DATA_START+1); i++)
		sum += MCU_TX.DATA[i];
	MCU_TX.DATA[DATA_START+1] = sum;
	for(i=0; i<(DATA_START+2); i++)
	{   while(_tidle==0||_txif==0);
            _txr_rxr = MCU_TX.DATA[i];
    }
}
void mcu_dp_value_update(u8 dpid,s16 Param)
{
	u8 i;
    SLONG value;
    value.lVal = (s32)Param;
    MCU_TX.DATA[HEAD_FIRST] = 0x55;
    MCU_TX.DATA[HEAD_SECOND] = 0xaa;
    MCU_TX.DATA[PROTOCOL_VERSION] = MCU_TX_VER;
    MCU_TX.DATA[FRAME_TYPE] = STATE_UPLOAD_CMD;
    MCU_TX.DATA[LENGTH_HIGH] = 0x00;
    MCU_TX.DATA[LENGTH_LOW] = 0x08;
    MCU_TX.DATA[DATA_START] = dpid;
    MCU_TX.DATA[DATA_START+1] = DP_TYPE_VALUE;
    MCU_TX.DATA[DATA_START+2] = 0x00;
    MCU_TX.DATA[DATA_START+3] = 0x04;
    /* 大端低位地址存放高位 */
    MCU_TX.DATA[DATA_START+4] = value.Byte.byte0;
    MCU_TX.DATA[DATA_START+5] = value.Byte.byte1;
    MCU_TX.DATA[DATA_START+6] = value.Byte.byte2;
    MCU_TX.DATA[DATA_START+7] = value.Byte.byte3;
    MCU_TX.DATA[DATA_START+8] = 0;
	for(i=0; i<(DATA_START+8); i++)
	    MCU_TX.DATA[DATA_START+8] += MCU_TX.DATA[i];
    Tx_Index = DATA_START+9;
    //Tx_Index += 1;//适应发射函数
}

void mcu_dp_bool_update(u8 dpid,u8 value)
{
	u8 i;
    MCU_TX.DATA[HEAD_FIRST] = 0x55;
    MCU_TX.DATA[HEAD_SECOND] = 0xaa;
    MCU_TX.DATA[PROTOCOL_VERSION] = MCU_TX_VER;
    MCU_TX.DATA[FRAME_TYPE] = STATE_UPLOAD_CMD;
    MCU_TX.DATA[LENGTH_HIGH] = 0x00;
    MCU_TX.DATA[LENGTH_LOW] = 0x05;
    MCU_TX.DATA[DATA_START] = dpid;
    MCU_TX.DATA[DATA_START+1] = DP_TYPE_BOOL;
    MCU_TX.DATA[DATA_START+2] = 0x00;
    MCU_TX.DATA[DATA_START+3] = 0x01;
    MCU_TX.DATA[DATA_START+4] = value;
    MCU_TX.DATA[DATA_START+5] = 0;
	for(i=0; i<(DATA_START+5); i++)
		MCU_TX.DATA[DATA_START+5] += MCU_TX.DATA[i];
    Tx_Index = DATA_START+6;
    //Tx_Index += 1;//适应发射函数
}

void mcu_dp_enum_update(u8 dpid,u8 value)
{
	u8 i;
    MCU_TX.DATA[HEAD_FIRST] = 0x55;
    MCU_TX.DATA[HEAD_SECOND] = 0xaa;
    MCU_TX.DATA[PROTOCOL_VERSION] = MCU_TX_VER;
    MCU_TX.DATA[FRAME_TYPE] = STATE_UPLOAD_CMD;
    MCU_TX.DATA[LENGTH_HIGH] = 0x00;
    MCU_TX.DATA[LENGTH_LOW] = 0x05;
    MCU_TX.DATA[DATA_START] = dpid;
    MCU_TX.DATA[DATA_START+1] = DP_TYPE_ENUM;
    MCU_TX.DATA[DATA_START+2] = 0x00;
    MCU_TX.DATA[DATA_START+3] = 0x01;
    MCU_TX.DATA[DATA_START+4] = value;
    MCU_TX.DATA[DATA_START+5] = 0;//必须清除为0
	for(i=0; i<(DATA_START+5); i++)
	    MCU_TX.DATA[DATA_START+5] += MCU_TX.DATA[i];
    Tx_Index = DATA_START+6;
    //Tx_Index += 1;//适应发射函数
}

void mcu_dp_fault_update(u8 dpid,u8 value)
{
	u8 i = 0;
    MCU_TX.DATA[HEAD_FIRST] = 0x55;
    MCU_TX.DATA[HEAD_SECOND] = 0xaa;
    MCU_TX.DATA[PROTOCOL_VERSION] = MCU_TX_VER;
    MCU_TX.DATA[FRAME_TYPE] = STATE_UPLOAD_CMD;
    MCU_TX.DATA[LENGTH_HIGH] = 0x00;
    MCU_TX.DATA[LENGTH_LOW] = 0x05;
    MCU_TX.DATA[DATA_START] = dpid;
    MCU_TX.DATA[DATA_START+1] = DP_TYPE_BITMAP;
    MCU_TX.DATA[DATA_START+2] = 0x00;
    MCU_TX.DATA[DATA_START+3] = 0x01;
    MCU_TX.DATA[DATA_START+4] = value;
    MCU_TX.DATA[DATA_START+5] = 0;
	for(i=0; i<(DATA_START+5); i++)
	    MCU_TX.DATA[DATA_START+5] += MCU_TX.DATA[i];
    Tx_Index = DATA_START+6;
    //Tx_Index += 1;//适应发射函数
}
void wifi_uart_write_frame(u8 fr_type, u8 fr_ver, unsigned short len)
{
	u8 i;
    MCU_TX.DATA[HEAD_FIRST] = 0x55;
    MCU_TX.DATA[HEAD_SECOND] = 0xaa;
    MCU_TX.DATA[PROTOCOL_VERSION] = fr_ver;
    MCU_TX.DATA[FRAME_TYPE] = fr_type;
    MCU_TX.DATA[LENGTH_HIGH] = len >> 8;
    MCU_TX.DATA[LENGTH_LOW] = len & 0xff;

    len += DATA_START;
		MCU_TX.DATA[len] = 0;

	for(i=0; i<len; i++)
		MCU_TX.DATA[len] += MCU_TX.DATA[i];
	for(i=0; i<(len+1); i++)
	{   while(_tidle==0||_txif==0);
            _txr_rxr = MCU_TX.DATA[i];
    }
}

void F_WifiConfigModeReset(u8 CMD)
{
    u8 i = 0;
    if(!B_WIFI_Reset)
        return;
    B_WIFI_Reset = 0;
    B_WifiReset = 1;
    MCU_TX.DATA[HEAD_FIRST] = 0x55;
    MCU_TX.DATA[HEAD_SECOND] = 0xaa;
    MCU_TX.DATA[PROTOCOL_VERSION] = 0x00;
    MCU_TX.DATA[FRAME_TYPE] = WIFI_RESET_CMD;
    MCU_TX.DATA[LENGTH_HIGH] = 0x00;
    MCU_TX.DATA[LENGTH_LOW] = CMD;
    MCU_TX.DATA[DATA_START] = 0;
	for(i=0; i<(DATA_START); i++)
	    MCU_TX.DATA[DATA_START] += MCU_TX.DATA[i];
    Tx_Index = DATA_START+1;
    //MCU_TX.DATA[DATA_START+1] = F_GetSum((u8 *)MCU_TX.DATA, DATA_START+1);
    //wifi_uart_write_data((u8 *)MCU_TX.DATA, DATA_START+2);
}

void F_WifiConfigModeSwitch(u8 CMD)
{
    u8 i = 0;
    // if(!B_WIFI_ModeSwi)
    //     return;
    // B_WIFI_ModeSwi = 0;
    MCU_TX.DATA[HEAD_FIRST] = 0x55;
    MCU_TX.DATA[HEAD_SECOND] = 0xaa;
    MCU_TX.DATA[PROTOCOL_VERSION] = 0x00;
    MCU_TX.DATA[FRAME_TYPE] = WIFI_MODE_CMD;
    MCU_TX.DATA[LENGTH_HIGH] = 0x00;
    MCU_TX.DATA[LENGTH_LOW] = 0x01;/* Smartconfig */
    MCU_TX.DATA[DATA_START] = CMD;//0;
    MCU_TX.DATA[DATA_START+1] = 0;
	for(i=0; i<(DATA_START+1); i++)
	    MCU_TX.DATA[DATA_START+1] += MCU_TX.DATA[i];
    Tx_Index = DATA_START+2;
    MCU_TX.DATA[DATA_START+1] = F_GetSum((u8 *)MCU_TX.DATA, DATA_START+1);
    wifi_uart_write_data((u8 *)MCU_TX.DATA, DATA_START+2);
}
