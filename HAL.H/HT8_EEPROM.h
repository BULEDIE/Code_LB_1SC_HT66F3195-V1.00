#ifndef _HT8_EEPROM_H_
#define	_HT8_EEPROM_H_


//#include "HT8_MCU_IP_SEL.h"

/********** EEPROM Erase and Write time select **********/
//	#define		Erase_3200us_Write_2200us		(1)
//	#define		Erase_3700us_Write_3000us		(1)
/******* end of EEPROM Erase and Write time select ******/	
void EEPROM_Write_Byte(u8 Data,u8 adr);			//EEPROM Write byte mode,No interrupt
void EEPROM_Write_page(u8 *Data,u8 page,u8 len);			//EEPROM Write page mode,No interrupt
u8 EEPROM_Read_Byte(u8 adr);						//EEPROM Read byte mode,No interrupt
void EEPROM_Read_page(u8 *Data,u8 page,u8 len);			//EEPROM Read page mode,No interrupt
void EEPROM_Erase_page(u8 page,u8 len);					//EEPROM Erase page
void F_SaveDataToEEPROM();
void F_ReadEEPROMToRAM();
#endif

/******************* (C) COPYRIGHT 2020 Holtek Semiconductor Inc *****END OF FILE****/