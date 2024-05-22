#ifndef _HT8_SYS_Clock_H_
#define _HT8_SYS_Clock_H_

/* attention¡GWhen selecting the HIRC clock, 
 * you need to select the corresponding HIRC frequency in the configuration options.
 */
/***** High Frequency clock selection ******/
	#define FH_HIRC_8M				(1)
//	#define FH_HIRC_12M				(1)
//	#define FH_HIRC_16M				(1)
//	#define FH_HXT_SE10M			(1)		//HXT frequency is smaller or equal than 10MHz
//	#define FH_HXT_L10M				(1)		//HXT frequency is larger than 10MHz
/** end of High Frequency clock selection **/

/***** Low Frequency clock selection ******/
//	#define FSUB_LIRC				(1)
//	#define FSUB_LXT				(1)
/** end of Low Frequency clock selection **/

/****** system clock prescaler select ******/
	#define	SYSCLOCK_FH				(1)	
//	#define	SYSCLOCK_FH_DIV2		(1)	
//	#define	SYSCLOCK_FH_DIV4		(1)	
//	#define	SYSCLOCK_FH_DIV8		(1)	
//	#define	SYSCLOCK_FH_DIV16		(1)	
//	#define	SYSCLOCK_FH_DIV32		(1)	
//	#define	SYSCLOCK_FH_DIV64		(1)	
//	#define	SYSCLOCK_FSUB			(1)	
/** end of system clock prescaler select **/



/**
  * @brief HALT mode selection list
  */
typedef enum 
{
	HALT_SLEEP  = (u8)0x00, /**< Sleep mode */
	HALT_IDLE0  = (u8)0x01, /**< IDLE0 mode */
	HALT_IDLE1  = (u8)0x03, /**< IDLE1 mode */
	HALT_IDLE2  = (u8)0x02, /**< IDLE2 mode */ 
}HALT_Mode_TypeDef;


void SysClock_Init();
void EnterHaltMode(u8 Halt_Mode);

#endif
