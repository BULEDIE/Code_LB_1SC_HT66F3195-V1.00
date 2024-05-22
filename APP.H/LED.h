#ifndef __LED__H__
#define __LED__H__

MyDef volatile UBYTE SegBuff[4];//定义显示缓存，可以位寻址
                         /* 后面三个ram缓存字符标识索引号 */
enum
{
    _ONE, // 显示个位
    _DEC, // 显示十位
    _ASC, // 显示ASCLL小数点
};
/* SEG= _SEG_ON (0)，COM=_COM_ON (1),方能点亮 */
enum {
    _SEG_ON,
    _SEG_OFF,
};
enum {
    _COM_OFF,
    _COM_ON,
};

    //定义seg的com口 方向口 及对应的io
    #define COM0_DIRE _pcc1
    #define COM1_DIRE _pcc0
    #define COM2_DIRE _pbc0
    #define COM3_DIRE _pbc1

    #define COM0 _pc1
    #define COM1 _pc0
    #define COM2 _pb0
    #define COM3 _pb1

    //定义seg的com口 方向口 及对应的io
    #define SEG0_DIRE _pac7
    #define SEG1_DIRE _pac6
    #define SEG2_DIRE _pac5
    #define SEG3_DIRE _pdc0
    #define SEG4_DIRE _pcc5
    #define SEG5_DIRE _pcc3
    #define SEG6_DIRE _pdc3
    #define SEG7_DIRE _pac4
    #define SEG8_DIRE _pbc2

    #define SEG0 _pa7
    #define SEG1 _pa6
    #define SEG2 _pa5
    #define SEG3 _pd0
    #define SEG4 _pc5
    #define SEG5 _pc3
    #define SEG6 _pd3
    #define SEG7 _pa4
    #define SEG8 _pb2

#define D_LEN 16
typedef struct
{               /* 参数设定范围 */
    s16 CF;		/* C F */
    s16 HC;		/* H C */
    s16 ST;	    /* 20.0℃～35.0℃ (68.0℉~95.0℉)  */
    s16 SP;     /* 20.0℃～35.0℃ (68.0℉~95.0℉)  */
    s16 AH; 	/* 0.0℃～100℃   (32.0℉~212℉)     */
    s16 AL;	    /* 0.0℃～100℃   (32.0℉~212℉) 	   */
    s16 PT;     /* 0～10 Hours  				  */
    s16 CA;     /* -9.9℃～9.9℃  (-15.0℉~15.0℉)  */
}T_DATA;
MyDef T_DATA S_SET;
MyDef T_DATA S_SET_LAST;

#define B_HC S_SET.HC
#define B_CF S_SET.CF
#define B_CF_BUFF S_SET_LAST.CF
#define Runing_PT S_SET_LAST.PT

MyDef volatile u8 SaveOrRead[sizeof(S_SET)];
/* APP 下发命令 同步显示缓存 */ /* APP 下发命令 间隔38.5ms连续7帧 300ms导致延时显示 */


enum {
    D_CF,
    D_HC,
    D_ST,
    D_SP,
    D_AH,
    D_AL,
    D_PT,
    D_CA,
    // D_CT,
    D_APP, /* 显示2秒后,返回正常模式 */
    D__P,
    D__H,
    D__C,
    D__F,
    D_E1,
    D_E2,
    D_E3,
    D_E4,
    D_E5,
    D_Er,
    D__NULL,
    D_TOTALNUM
};
extern const char T_ZimuBuf[D_TOTALNUM][4];
enum{
    Shuzi_0 = 0,
    Shuzi_1,
    Shuzi_2,
    Shuzi_3,
    Shuzi_4,
    Shuzi_5,
    Shuzi_6,
    Shuzi_7,
    Shuzi_8,
    Shuzi_9,
    Shuzi_A,
    Shuzi_b,
    Shuzi_C,
    Shuzi_d,
    Shuzi_E,
    Shuzi_F,
    Shuzi_T,
    Shuzi_H,
    Shuzi_L,
    Shuzi_P,
    Shuzi_S,
    Shuzi_NULL,
    Shuzi_NEGATIVE,
    Shuzi_r,
    Shuzi_V,
    D_Temp_C,
    D_Temp_F,
    D_Temp_A,
    Shuzi_Max

    /* Shuzi_N,
    Shuzi_n,
    Shuzi_o,
    Shuzi_V, */
};

#define Shuzi_INVALID Shuzi_NEGATIVE//无效- 负号-
#define Shuzi_NEG     Shuzi_NEGATIVE//无效- 负号-

MyDef u8 R_Bcd[6];
MyDef u8 volatile BCD;
void F_DISPWIFIRSSI(u8 flag, u16 rssi);
int F_CtoF(int temp);
int F_FtoC(int temp);
void F_Change5BCD(long num, u8 Decimal);
void F_SetBCDINIT();
void F_DISPVER();
void F_GetBCD();
void F_GetDispFlag();
void F_LEDSCAN();
extern const u8 T_DispNum[Shuzi_Max];

#endif