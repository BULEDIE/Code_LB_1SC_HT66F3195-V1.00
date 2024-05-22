
#ifndef _WDT_H_
#define _WDT_H_

#define	WDT_ENABLE()			{_we4=0;_we3=1;_we2=0;_we1=1;_we0=0;}
#define	WDT_DISABLE()			{_we4=1;_we3=0;_we2=1;_we1=0;_we0=1;}

/********** WDT overflow time select **********/
//	#define	WDT_OF_TIME_2_8			1	//WDT overflow time 2^8 *Tsub
//	#define	WDT_OF_TIME_2_10		1	//WDT overflow time 2^10*Tsub
//	#define	WDT_OF_TIME_2_12		1	//WDT overflow time 2^12*Tsub
	#define	WDT_OF_TIME_2_14		1	//WDT overflow time 2^14*Tsub
//	#define	WDT_OF_TIME_2_15		1	//WDT overflow time 2^15*Tsub
//	#define	WDT_OF_TIME_2_16		1	//WDT overflow time 2^16*Tsub
//	#define	WDT_OF_TIME_2_17		1	//WDT overflow time 2^17*Tsub
//	#define	WDT_OF_TIME_2_18		1	//WDT overflow time 2^18*Tsub
/****** end of WDT overflow time select ******/

void WDT_Init();

#endif

