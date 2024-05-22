#ifndef __WIFI_Sub_H__
#define __WIFI_Sub_H__

/* 第一步 */
void F_Heat_beat_check();
void F_Product_info_update(void);
void F_WifiConfigModeReset(u8 CMD);
void F_WifiConfigModeSwitch(u8 CMD);
void F_MCU_FIRM_UPDATE_START();
void F_MCU_FIRM_UPDATE_TRANS();
void F_GET_LOCAL_TIME();
void wifi_test_result(u8 result,u8 rssi);


enum {
    D_HEAT_BEAT = 0,    //心跳检测
    D_PRODUCT_INFO,     //查询产品信息
    D_WORK_MODE,        //查询 MCU 设定模块工作方式
    D_WIFI_STATE,       //报告 WiFi 工作状态
    D_WIFI_RESET,       //重置 WiFi
    D_WIFI_MODE,        //重置 WiFi 选择模式（MCU上报二选一）
    D_STATE_QUERY,      //查询 mcu 工作状态
    D_UPDATE_START,     //升级启动
    D_UPDATE_TRANS,     //升级包传输
    D_GET_LOCAL_TIME,   //获取本地时间(可选)
    D_WIFI_TEST,        //WiFi功能 产测( 注：扫描 tuya_mde v_test的 指定SSID)
    D_WIFI_TX_BASIC_TOTALNUM
};

#define D_lenfault 0x0005
#define D_lenbool 0x0005
#define D_lenenum 0x0005
#define D_lenvalue 0x0008

#define D_len2fault 0x0001
#define D_len2bool  0x0001
#define D_len2enum  0x0001
#define D_len2value 0x0004

void F_PROTOCOL_HEAD(u8 fr_ver, u8 fr_type, u16 fr_len);
void F_PROTOCOL_HEAD1(u8 dpid,u8 TYPE,u16 len);
void mcu_Send_Cmd(u8 cmd,u8 Mode);
void mcu_dp_value_update(u8 dpid,s16 Param);
void mcu_dp_bool_update(u8 dpid,u8 value);
void mcu_dp_enum_update(u8 dpid,u8 value);
void mcu_dp_fault_update(u8 dpid,u8 value);
void wifi_uart_write_frame(u8 fr_type, u8 fr_ver, unsigned short len);

#endif
