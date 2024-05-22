#ifndef __SYSINIT_H__
#define __SYSINIT_H__


#define F_UART_RUN()   {_uare=1;}
#define F_UART_STOP()  {_uare=0;}

#define F_CLR_CTMA_INT()   {_ctmaf=0;}
#define F_CLR_UART_RXINT() {_uarf=0;}

#define F_PRINT_RX_LEN() { while(_tidle==0||_txif==0);_txr_rxr = R_Indexes; }
#define F_PRINT_RX_DATA(){ while(_tidle==0||_txif==0);_txr_rxr = MCU_RX.DATA[R_Indexes-1];}


void F_UART_RAM_INIT();
void F_Delay_Ms(u16 ms);

void F_IO_INIT();
void F_RAM_INIT();
void F_Time_Base0_INIT();
void F_DefaultSettings(u8 CF, u8 HC);

void SysClock_Init();
void System_Init();
void System_Setting();
void UART_Init();
#endif
