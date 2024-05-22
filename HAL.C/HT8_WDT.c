#include "Main.h"
void WDT_Init()
{
	#ifdef	WDT_OF_TIME_2_8
		_ws2=0;_ws1=0;_ws0=0;
		
	#elif	WDT_OF_TIME_2_10
		_ws2=0;_ws1=0;_ws0=1;
		
	#elif	WDT_OF_TIME_2_12
		_ws2=0;_ws1=1;_ws0=0;
		
	#elif	WDT_OF_TIME_2_14
		_ws2=0;_ws1=1;_ws0=1;
		
	#elif	WDT_OF_TIME_2_15
		_ws2=1;_ws1=0;_ws0=0;
		
	#elif	WDT_OF_TIME_2_16
		_ws2=1;_ws1=0;_ws0=1;
		
	#elif	WDT_OF_TIME_2_17
		_ws2=1;_ws1=1;_ws0=0;
		
	#elif	WDT_OF_TIME_2_18
		_ws2=1;_ws1=1;_ws0=1;
	#endif
}
