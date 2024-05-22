#ifndef __WIFI_H__
#define __WIFI_H__

//======================================
#define MCU_RX_VER              0x00    //模块发送帧协议版本号
#define MCU_TX_VER              0x03    //MCU 发送帧协议版本号(默认)
#define PROTOCOL_HEAD           0x07    //固定协议头长度
#define FRAME_FIRST             0x55    //帧头第一字节
#define FRAME_SECOND            0xaa    //帧头第二字节
//======================================

/******************************************************************************
                        1:dp数据点序列号重新定义
          **此为自动生成代码,如在开发平台有相关修改请重新下载MCU_SDK**
******************************************************************************/
//温标切换(可下发可上报)
//备注:0：摄氏度1：华氏度
#define DPID_CF 5
//工作模式(可下发可上报)
//备注:0:加热模式1：制冷模式
#define DPID_HC 101
//启动温度设定值(可下发可上报)
//备注:
#define DPID_ST 102
//停止温度设定值(可下发可上报)
//备注:
#define DPID_SP 103
//高温报警设定值(可下发可上报)
//备注:
#define DPID_AH 104
//低温报警设定值(可下发可上报)
//备注:
#define DPID_AL 105
//制冷延迟(可下发可上报)
//备注:
#define DPID_PT 106
//校准温度(可下发可上报)
//备注:
#define DPID_CA 107
//实时温度(只上报)
//备注:
#define DPID_TEMP_C 108
#define DPID_TEMP_F 109

//输出状态(只上报)
//备注:加热状态关闭，加热状态打开，制冷状态关闭，制冷状态打开。
#define DPID_STATE 110

//设备报警(只上报)
//备注:高温报警，低温报警，探头损坏报警
#define DPID_ALARM 111

//=============================================================================
//定义常量
//如果编译发生错误: #40: expected an identifier  DISABLE = 0, 类似这样的错误提示，可以包含头文件 #include "stm32f1xx.h" 来解决
//=============================================================================
#ifndef TRUE
#define      TRUE                1
#endif

#ifndef FALSE
#define         FALSE            0
#endif

#ifndef NULL
#define         NULL             ((void *) 0)
#endif

#ifndef SUCCESS
#define         SUCCESS          1
#endif

#ifndef ERROR
#define         ERROR            0
#endif

#ifndef INVALID
#define         INVALID          0xFF
#endif

#ifndef ENABLE
#define         ENABLE           1
#endif

#ifndef DISABLE
#define         DISABLE          0
#endif
//=============================================================================
//dp数据点类型
//=============================================================================
#define         DP_TYPE_RAW                     0x00        //RAW 类型
#define         DP_TYPE_BOOL                    0x01        //bool 类型
#define         DP_TYPE_VALUE                   0x02        //value 类型
#define         DP_TYPE_STRING                  0x03        //string 类型
#define         DP_TYPE_ENUM                    0x04        //enum 类型
#define         DP_TYPE_BITMAP                  0x05        //fault 类型

//=============================================================================
//WIFI工作状态
//=============================================================================
#define         SMART_CONFIG_STATE              0x00
#define         AP_STATE                        0x01
#define         WIFI_NOT_CONNECTED              0x02
#define         WIFI_CONNECTED                  0x03
#define         WIFI_CONN_CLOUD                 0x04
#define         WIFI_LOW_POWER                  0x05
#define         SMART_AND_AP_STATE              0x06
#define         WIFI_SATE_UNKNOW                0xff
//=============================================================================
//wifi配网的方式
//=============================================================================
#define         SMART_CONFIG                    0x0
#define         AP_CONFIG                       0x1

//=============================================================================
//wifi复位状态
//=============================================================================
#define         RESET_WIFI_ERROR                0
#define         RESET_WIFI_SUCCESS              1

//=============================================================================
//wifi配置复位状态
//=============================================================================
#define         SET_WIFICONFIG_ERROR            0
#define         SET_WIFICONFIG_SUCCESS          1

//=============================================================================
//MCU固件升级状态
//=============================================================================
#define         FIRM_STATE_UN_SUPPORT           0x00                            //不支持 MCU 升级
#define         FIRM_STATE_WIFI_UN_READY        0x01                            //模块未就绪
#define         FIRM_STATE_GET_ERROR            0x02                            //云端升级信息查询失败
#define         FIRM_STATE_NO                   0x03                            //无需升级（云端无更新版本）
#define         FIRM_STATE_START                0x04                            //需升级，等待模块发起升级操作

//=============================================================================
//WIFI和mcu的工作方式
//=============================================================================
#define         UNION_WORK                      0x0                             //mcu模块与wifi配合处理
#define         WIFI_ALONE                      0x1                             //wifi模块自处理

//=============================================================================
//系统工作模式
//=============================================================================
#define         NORMAL_MODE                     0x00                            //正常工作状态
#define         FACTORY_MODE                    0x01                            //工厂模式
#define         UPDATE_MODE                     0x02                            //升级模式

//=============================================================================
//配网方式选择
//=============================================================================
#define         CONFIG_MODE_DEFAULT             "0"                             //默认配网方式
#define         CONFIG_MODE_LOWPOWER            "1"                             //低功耗配网方式
#define         CONFIG_MODE_SPECIAL             "2"                             //特殊配网方式




//=============================================================================
//下发命令
//=============================================================================
/* typedef struct {
  u8 dp_id;                              //dp序号
  u8 dp_type;                            //dp类型
} DOWNLOAD_CMD_S;

 */


/******************************************************************************
                         3:定义收发缓存:
                    如当前使用MCU的RAM不够,可修改为24
******************************************************************************/
#ifndef SUPPORT_MCU_FIRM_UPDATE
#define WIFI_UART_RECV_BUF_LMT          16              //串口数据接收缓存区大小,如MCU的RAM不够,可缩小
#define WIFI_DATA_PROCESS_LMT           24              //串口数据处理缓存区大小,根据用户DP数据大小量定,必须大于24
#else
#define WIFI_UART_RECV_BUF_LMT          128             //串口数据接收缓存区大小,如MCU的RAM不够,可缩小

//请在此处选择合适的串口数据处理缓存大小（根据上面MCU固件升级包选择的大小和是否开启天气服务来选择开启多大的缓存）
#define WIFI_DATA_PROCESS_LMT           300             //串口数据处理缓存大小,如需MCU固件升级,若单包大小选择256,则缓存必须大于260,若开启天气服务,则需要更大
//#define WIFI_DATA_PROCESS_LMT           600             //串口数据处理缓存大小,如需MCU固件升级,若单包大小选择512,则缓存必须大于520,若开启天气服务,则需要更大
//#define WIFI_DATA_PROCESS_LMT           1200            //串口数据处理缓存大小,如需MCU固件升级,若单包大小选择1024,则缓存必须大于1030,若开启天气服务,则需要更大

#endif

#define WIFIR_UART_SEND_BUF_LMT         48              //根据用户DP数据大小量定,必须大于48

//=============================================================================
//Byte order of the frame
//=============================================================================
#define         HEAD_FIRST                      0
#define         HEAD_SECOND                     1
#define         PROTOCOL_VERSION                2
#define         FRAME_TYPE                      3
#define         LENGTH_HIGH                     4
#define         LENGTH_LOW                      5
#define         DATA_START                      6

//=============================================================================
//Data frame type
//=============================================================================
#define         HEAT_BEAT_CMD                   0                               //心跳包
#define         PRODUCT_INFO_CMD                1                               //产品信息
#define         WORK_MODE_CMD                   2                               //查询MCU 设定的模块工作模式
#define         WIFI_STATE_CMD                  3                               //wifi工作状态
#define         WIFI_RESET_CMD                  4                               //重置wifi
#define         WIFI_MODE_CMD                   5                               //选择smartconfig/AP模式
#define         DATA_QUERT_CMD                  6                               //命令下发
#define         STATE_UPLOAD_CMD                7                               //状态上报
#define         STATE_QUERY_CMD                 8                               //状态查询
#define         UPDATE_START_CMD                0x0a                            //升级开始
#define         UPDATE_TRANS_CMD                0x0b                            //升级传输
#define         GET_ONLINE_TIME_CMD             0x0c                            //获取系统时间(格林威治时间)
#define         FACTORY_MODE_CMD                0x0d                            //进入产测模式
#define         WIFI_TEST_CMD                   0x0e                            //wifi功能测试
#define         GET_LOCAL_TIME_CMD              0x1c                            //获取本地时间
#define         WEATHER_OPEN_CMD                0x20                            //打开天气
#define         WEATHER_DATA_CMD                0x21                            //天气数据
#define         STATE_UPLOAD_SYN_CMD            0x22                            //状态上报（同步）
#define         STATE_UPLOAD_SYN_RECV_CMD       0x23                            //状态上报结果通知（同步）
#define         HEAT_BEAT_STOP                  0x25                            //关闭WIFI模组心跳
#define         STREAM_TRANS_CMD                0x28                            //流数据传输
#define         GET_WIFI_STATUS_CMD             0x2b                            //获取当前wifi联网状态
#define         WIFI_CONNECT_TEST_CMD           0x2c                            //wifi功能测试(连接指定路由)
#define         GET_MAC_CMD                     0x2d                            //获取模块mac
#define         GET_IR_STATUS_CMD               0x2e                            //红外状态通知
#define         IR_TX_RX_TEST_CMD               0x2f                            //红外进入收发产测
#define         MAPS_STREAM_TRANS_CMD           0x30                            //流数据传输(支持多张地图)
#define         FILE_DOWNLOAD_START_CMD         0x31                            //文件下载启动
#define         FILE_DOWNLOAD_TRANS_CMD         0x32                            //文件下载数据传输
#define         MODULE_EXTEND_FUN_CMD           0x34                            //模块拓展服务
#define         BLE_TEST_CMD                    0x35                            //蓝牙功能性测试（扫描指定蓝牙信标）
#define         GET_VOICE_STATE_CMD             0x60                            //获取语音状态码
#define         MIC_SILENCE_CMD                 0x61                            //MIC静音设置
#define         SET_SPEAKER_VOLUME_CMD          0x62                            //speaker音量设置
#define         VOICE_TEST_CMD                  0x63                            //语音模组音频产测
#define         VOICE_AWAKEN_TEST_CMD           0x64                            //语音模组唤醒产测
#define         VOICE_EXTEND_FUN_CMD            0x65                            //语音模组扩展功能


#define         D_RxLen   24

typedef union
{
    u8 DATA[D_RxLen/* PROTOCOL_HEAD + WIFI_UART_RECV_BUF_LMT */];
    /* 串口接收缓存 */
    struct
    {
      u8 DAT0;
      u8 DAT1;
      u8 DAT2;
      u8 DAT3;
      u8 DAT4;
      u8 DAT5;
      u8 DAT6;
      u8 DAT7;
      u8 DAT8;
      u8 DAT9;
      u8 DAT10;
      u8 DAT11;
      u8 DAT12;
      u8 DAT13;
     // SLONG DATA;
      u8 DAT14;
      u8 DA[8];
    }BUFF;
}T_RX;
MyDef T_RX MCU_RX;

typedef union
{
    u8 DATA[PROTOCOL_HEAD + WIFIR_UART_SEND_BUF_LMT];
    /* 串口发送缓存 */
    struct
    {
      u8 DAT0;
      u8 DAT1;
      u8 DAT2;
      u8 DAT3;
      u8 DAT4;
      u8 DAT5;
      u8 DAT6;
      u8 DAT7;
      u8 DAT8;
      u8 DAT9;
      SLONG DATA;
      u8 DAT14;
      u8 DA[8];
    }BUFF;
}T_TX;
MyDef T_TX MCU_TX;



#ifdef WIFI_STREAM_ENABLE
MyDef volatile u8 stream_status;                                                             //流服务发包返回状态
MyDef volatile u8 maps_stream_status;                                                        //多地图流服务发包返回状态
#endif

u8 F_GetSum(u8 *addr, u8 Length);
void F_MCU_TX_Service(void);
void F_MCU_RX_Service(void);

#define _P_ "{\"p\":\""
#define _V_ "\",\"v\":\""
#define _M_ "\",\"m\":"
#define _Y_ "}"
#define PRODUCT_KEY "xalrjhoc0rbu1gnv"    //开发平台创建产品后生成的16位字符产品唯一标识

#define MCU_VER "1.0.0"         //用户的软件版本,用于MCU固件升级,MCU升级版本需修改

/*  模块工作方式选择,只能三选一,推荐使用防误触模式  */
//#define CONFIG_MODE     CONFIG_MODE_DEFAULT             //默认工作模式
//#define CONFIG_MODE     CONFIG_MODE_LOWPOWER            //安全模式 (低功耗配网方式)
#define CONFIG_MODE     CONFIG_MODE_SPECIAL             //防误触模式(特殊配网方式)
void wifi_uart_write_data(u8 *in, unsigned short len);
void F_Wifi_State(void);

#endif
