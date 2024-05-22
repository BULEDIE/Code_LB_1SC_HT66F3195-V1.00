#include "Main.h"

void TimeBase0_Init(void)
{
/***************** TimeBase0 clock select *****************/
	#ifdef	TB0_CLOCK_FSYS
		{
			/* select TimeBase0 clock fsys */
			_clksel01 = 0; 	_clksel00 = 0; 
		}		
	#elif	TB0_CLOCK_FSYS_DIV4
		{
			/* select TimeBase0 clock fsys/4 */
			_clksel01 = 0; 	_clksel00 = 1; 
		}
	#elif	TB0_CLOCK_FSUB
		{
			/* select TimeBase0 clock fsub */
			_clksel01 = 1; 	_clksel00 = 0; 
		}
	#endif	
/*************** end of TimeBase0 clock select ******************/	

						
/******** TimeBase0 time-out period select**********/
	#ifdef	TB0_Period_2_8		
		{
			/* select TimeBase0 time-out period 2^8(256)	*/
			_tb02 = 0;	_tb01 = 0;	_tb00 = 0;
		}	
	#elif	TB0_Period_2_9		
		{
			/* select TimeBase0 time-out period 2^9(512)	*/
			_tb02 = 0;	_tb01 = 0;	_tb00 = 1;
		}
	#elif	TB0_Period_2_10		
		{
			/* select TimeBase0 time-out period 2^10(1024) */
			_tb02 = 0;	_tb01 = 1;	_tb00 = 0;
		}
	#elif	TB0_Period_2_11		
		{
			/* select TimeBase0 time-out period 2^11(2048)	*/
			_tb02 = 0;	_tb01 = 1;	_tb00 = 1;
		}
	#elif	TB0_Period_2_12		
		{
			/* select TimeBase0 time-out period 2^12(4096)	*/
			_tb02 = 1;	_tb01 = 0;	_tb00 = 0;
		}	
	#elif	TB0_Period_2_13		
		{
			/* select TimeBase0 time-out period 2^13(8192)	*/
			_tb02 = 1;	_tb01 = 0;	_tb00 = 1;
		}
	#elif	TB0_Period_2_14		
		{
			/* select TimeBase0 time-out period 2^14(16384)	*/
			_tb02 = 1;	_tb01 = 1;	_tb00 = 0;
		}
	#elif	TB0_Period_2_15		
		{
			/* select TimeBase0 time-out period 2^15(32768)	*/
			_tb02 = 1;	_tb01 = 1;	_tb00 = 1;
		}
	#endif
/***** end of TimeBase0 time-out period select ******/
}


/**
  * @brief Initializes the TimeBase1 peripheral according to the specified parameters
  * @retval None
  */
void TimeBase1_Init(void)
{
/***************** TimeBase1 clock select *****************/
	#ifdef	TB1_CLOCK_FSYS
		{
			/* select TimeBase1 clock fsys */
			_clksel11 = 0; 	_clksel10 = 0; 
		}		
	#elif	TB1_CLOCK_FSYS_DIV4
		{
			/* select TimeBase1 clock fsys/4 */
			_clksel11 = 0; 	_clksel10 = 1; 
		}
	#elif	TB1_CLOCK_FSUB
		{
			/* select TimeBase1 clock fsub */
			_clksel11 = 1; 	_clksel10 = 0; 
		}
	#endif	
/*************** end of TimeBase1 clock select ******************/	

						
/******** TimeBase1 time-out period select**********/
	#ifdef	TB1_Period_2_8		
		{
			/* select TimeBase1 time-out period 2^8(256)	*/
			_tb12 = 0;	_tb11 = 0;	_tb10 = 0;
		}	
	#elif	TB1_Period_2_9		
		{
			/* select TimeBase1 time-out period 2^9(512)	*/
			_tb12 = 0;	_tb11 = 0;	_tb10 = 1;
		}
	#elif	TB1_Period_2_10		
		{
			/* select TimeBase1 time-out period 2^10(1024) */
			_tb12 = 0;	_tb11 = 1;	_tb10 = 0;
		}
	#elif	TB1_Period_2_11		
		{
			/* select TimeBase1 time-out period 2^11(2048)	*/
			_tb12 = 0;	_tb11 = 1;	_tb10 = 1;
		}
	#elif	TB1_Period_2_12		
		{
			/* select TimeBase1 time-out period 2^12(4096)	*/
			_tb12 = 1;	_tb11 = 0;	_tb10 = 0;
		}	
	#elif	TB1_Period_2_13		
		{
			/* select TimeBase1 time-out period 2^13(8192)	*/
			_tb12 = 1;	_tb11 = 0;	_tb10 = 1;
		}
	#elif	TB1_Period_2_14		
		{
			/* select TimeBase1 time-out period 2^14(16384)	*/
			_tb12 = 1;	_tb11 = 1;	_tb10 = 0;
		}
	#elif	TB1_Period_2_15		
		{
			/* select TimeBase1 time-out period 2^15(32768)	*/
			_tb12 = 1;	_tb11 = 1;	_tb10 = 1;
		}
	#endif
/***** end of TimeBase1 time-out period select ******/
}

/******************* (C) COPYRIGHT 2019 Holtek Semiconductor Inc *****END OF FILE****/