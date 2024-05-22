#ifndef __NTC__H__
#define __NTC__H__

#define AD4_DIRE  _pdc3
#define AD4_PU    _pdpu3
#define AD4_IO    _pd3

#define AD5_DIRE  _pbc4
#define AD5_PU    _pbpu4
#define AD5_IO    _pb4

#define D_CH1   8
#define D_OpenCircuit    -501
#define D_ShortCircuit   1201


MyDef volatile u16 R_Ch1ADC;
MyDef volatile u16 R_Ch1LastADC;
MyDef volatile s16 R_Ch1Temp;

typedef struct
{
    UBYTE Flag;
    s16 C;
    s16 F;
    // s16 C_Buf[3];
    // s16 F_Buf[3];
    // s16 C_Last;
    // s16 F_Last;
    s16 Display;
    u8 Cnt;
} T_Temp;
MyDef T_Temp Temp;
MyDef T_Temp Temp_LA;
#define B_GetTemp Temp.Flag.Bit.bit0
#define B_Read_Temp_Change Temp.Flag.Bit.bit1


u16 F_GetADC(u8 ch);
s16 F_GetTemp(u16 Value);
void F_GetTempValue();
void F_Move(u16 *R_History,u16 Current,u8 size);
void F_RxMove(u16 *R_History,u16 offset,u8 size);

u16 F_GetTrueADC(u8 ch,u16 LastAdc);
#endif