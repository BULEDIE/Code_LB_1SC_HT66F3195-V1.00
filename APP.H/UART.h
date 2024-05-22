#ifndef __UART_H__
#define __UART_H__


#define	UART_ENABLE()			{_uarten = 1;}				//UART function enable
#define	UART_DISABLE()			{_uarten = 0;}				//UART function disable

#define	UART_TX_ENABLE()		{_txen = 1;}				//TX function enable
#define	UART_TX_DISABLE()		{_txen = 0;}				//TX function disable

#define	UART_RX_ENABLE()		{_rxen = 1;}				//RX function enable
#define	UART_RX_DISABLE()		{_rxen = 0;}				//RX function disable

#define	UART_ISR_ENABLE()		{_uarte = 1;}				//UART interrupt enable
#define	UART_ISR_DISABLE()		{_uarte = 0;}				//UART interrupt disable
#define	UART_CLEAR_ISR_FLAG()	{_uartf = 0;}				//clear UART interrupt flag
#define	UART_SET_ISR_FLAG()		{_uartf = 1;}				//set UART interrupt flag

#define UART_RIE_ENABLE()		{_rie = 1;}                 //UART receiver interrupt enable
#define UART_RIE_DISABLE()		{_rie = 0;}                 //UART receiver interrupt disable

#define UART_TIIE_ENABLE()		{_tiie = 1;}                 //UART transmitter idle interrupt enable
#define UART_TIIE_DISABLE()		{_tiie = 0;}                 //UART transmitter idle interrupt disable

#define UART_TEIE_ENABLE()		{_teie = 1;}                 //UART transmitter empty interrupt enable
#define UART_TEIE_DISABLE()		{_teie = 0;}                 //UART transmitter empty interrupt disable

#define UART_Addr_Det_ENABLE()	{_adden = 1;}                //UART Address detect function enable
#define UART_Addr_Det_DISABLE()	{_adden = 0;}                //UART Address detect function disable

#define UART_RX_Wake_ENABLE()	{_wake = 1;}                 //UART RX pin falling edge wake-up function enable
#define UART_RX_Wake_DISABLE()	{_wake = 0;}                 //UART RX pin falling edge wake-up function disable

#define UART_TXBRK_ENABLE()		{_txbrk = 1;}                //UART transmit break character function enable
#define UART_TXBRK_DISABLE()	{_txbrk = 0;}                //UART transmit break character function disable


void UART_SendChar(u8 data);
void SendString(u8 *ch);

#endif
