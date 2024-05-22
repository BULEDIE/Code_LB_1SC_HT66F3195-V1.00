#include "Main.h"

void SysClock_Init()
{
  /***************** High Frequency clock selection ******************/
  #ifdef	FH_HIRC_8M	
    _hircen = 1; _hirc1 = 0;  _hirc0 = 0; while(!_hircf); _fhs = 0;		
      
  #elif   FH_HIRC_12M	
    _hircen = 1; _hirc1 = 0;  _hirc0 = 1; while(!_hircf); _fhs = 0;			
        
  #elif	FH_HIRC_16M	
    _hircen = 1; _hirc1 = 1;  _hirc0 = 0; while(!_hircf); _fhs = 0;		
      
  #elif	FH_HXT_SE10M	//HXT frequency is smaller or equal than 10MHz
    _pcs01 = 1; _pcs00 = 1; _pcs03 = 1; _pcs02 = 1;	
    _hxtm = 0; _hxten = 1; while(!_hxtf); _fhs = 1;	
      
  #elif	FH_HXT_L10M		//HXT frequency is larger than 10MHz
    _pcs01 = 1; _pcs00 = 1; _pcs03 = 1; _pcs02 = 1;	
    _hxtm = 1; _hxten = 1; while(!_hxtf); _fhs = 1;		
  #endif			
  /************** end of High Frequency clock selection **************/

  /***************** Low Frequency clock selection ******************/
  #ifdef	FSUB_LIRC
    _fss = 0;
        
  #elif 	FSUB_LXT
    _pbs01 = 1; _pbs00 = 1;	_pbs03 = 1; _pbs02 = 1; 	
    _lxten = 1; while(!_lxtf); _fss = 1;
  #endif			
  /************** end of Low Frequency clock selection **************/	
    
  /********************** system clock prescaler select **********************/
  #ifdef	SYSCLOCK_FH
    _cks2 = 0; _cks1 = 0; _cks0 = 0;	//set Fsys as FH
    
  #elif	SYSCLOCK_FH_DIV2
    _cks2 = 0; _cks1 = 0; _cks0 = 1;	//set Fsys as FH/2
    
  #elif	SYSCLOCK_FH_DIV4
    _cks2 = 0; _cks1 = 1; _cks0 = 0;	//set Fsys as FH/4
    
  #elif	SYSCLOCK_FH_DIV8
    _cks2 = 0; _cks1 = 1; _cks0 = 1;	//set Fsys as FH/8
    
  #elif	SYSCLOCK_FH_DIV16
    _cks2 = 1; _cks1 = 0; _cks0 = 0;	//set Fsys as FH/16
    
  #elif	SYSCLOCK_FH_DIV32
    _cks2 = 1; _cks1 = 0; _cks0 = 1;	//set Fsys as FH/32
    
  #elif	SYSCLOCK_FH_DIV64
    _cks2 = 1; _cks1 = 1; _cks0 = 0;	//set Fsys as FH/64
    
  #elif	SYSCLOCK_FSUB
    _cks2 = 1; _cks1 = 1; _cks0 = 1;	//set Fsys as FSUB(32.768K or 32K)
  #endif	
  /****************** end of system clock prescaler select *******************/
}


void EnterHaltMode(u8 Halt_Mode)
{
	_scc &= 0xfc;
	_scc |= Halt_Mode;
	_halt();		
}
/* end of EnterHaltMode(u8 Halt_Mode) */

/******************* (C) COPYRIGHT 2019 Holtek Semiconductor Inc *****END OF FILE****/