#include "Main.h"

//发送单个字符
void UART_SendChar(u8 data)
{
	if(_txif)						//判断发送数据寄存器为空
	{
		_txr_rxr=data;				//写入TXR--------清标志位TXIF，TXIF=1标志TXR写入TSR,0标志禁止写入TXR中已有数据
		while(!_txif);				//等待数据写入TSR
		while(!_tidle);				//等待数据传输结束
	}
}

//发送字符串
void SendString(u8 *ch)
{
	while(*ch!=0)
	{
		UART_SendChar(*(ch++));
	}
}
