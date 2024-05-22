#include "Main.h"

void EEPROM_Write_Byte(u8 Data,u8 adr)
{
	u8 TempEMI,TempEEC;

	TempEMI = _emi;

	/*config EEPROM init*/
	_mp2h = 1;

	_mp2l = 0x40;

	TempEEC = _iar2;

	_iar2 &= 0x6f;
	/*config EEPROM address*/
	_eea = adr;

	/*Write data*/
	_eed = Data;

/********** EEPROM Erase and Write time select **********/
	#ifdef	Erase_3200us_Write_2200us
		_iar2 &= 0x7f;

	#else
		_iar2 |= 0x80;

	#endif
/******* end of EEPROM Erase and Write time select ******/
	_emi = 0;		//disable global interrupt
	/*config EEPROM Write mode*/
	_iar2 |= 0x08;
	_iar2 |= 0x04;

	_emi = TempEMI;		//enable global interrupt

	/* waitting for EEPROM write finishing */
	while(_iar2 & 0x04);
	_iar2 = TempEEC;
	_mp2h = 0;

	return;
}


/**
  * @brief EEPROM write page function.
  * @param[in] The array pointer to be written to EEPROM.
  * @param[in] Specifies EEPROM page.
  * It can be 0~7,page 0 is mapping to address 0x00~0x0f,
  * page 1 is mapping to address 0x10~0x1f,page n is mapping to address (n-1)*16~(n-1)*16+15.
  * @param[in] The Byte number, it's length can up to 16.
  * @retval None
  */
void EEPROM_Write_page(u8 *Data,u8 page,u8 len)
{
	/* HT66F489 内部EEPROM 共64字节 / 4页*/
	/* 1页 = 16个字节*/
	u8 i;
	u8 TempEMI,TempEEC;
	if (len > 16)	len = 16;

	EEPROM_Erase_page(page,len);

	TempEMI = _emi;

	/*config EEPROM init*/
	_mp2h = 1;

	_mp2l = 0x40;

	TempEEC = _iar2;

	_iar2 &= 0x6f;
	/*config EEPROM page*/

	_eea = page<<4;

/********** EEPROM Erase and Write time select **********/
	#ifdef	Erase_3200us_Write_2200us
		_iar2 &= 0x7f;

	#else
		_iar2 |= 0x80;

	#endif
/******* end of EEPROM Erase and Write time select ******/

	_iar2 |= 0x10;
	/*Write data*/
	for(i = 0; i < len; i++)
		_eed = Data[i];

	_mp2h = 1;
	_mp2l = 0x40;

	_emi = 0;		//disable global interrupt
	/*config EEPROM Write mode*/
	_iar2 |= 0x08;
	_iar2 |= 0x04;

	_emi = TempEMI;		//enable global interrupt

	/* waitting for EEPROM write finishing */
	while(_iar2 & 0x04);
	_iar2 = TempEEC;
	_mp2h = 0;

	return;
}


/**
  * @brief EEPROM read byte function.
  * @param[in] Specifies EEPROM address that you want to read.
  * It can be 0x00~0x7f.
  * @retval EEPROM data.
  */
u8 EEPROM_Read_Byte(u8 adr)
{
	u8 TempEEC;
	u8 EP_Read_Data;

	/* config EEPROM init */
	_mp2h = 1;
	_mp2l = 0x40;

	TempEEC = _iar2;

	_iar2 &= 0x6f;
	/*config EEPROM address*/

	_eea = adr;

	/*config EEPROM Read mode*/
	_iar2 |= 0x02;
	_iar2 |= 0x01;

	/* waitting for EEPROM Read finishing */
	while(_iar2 & 0x01);
	_iar2 = TempEEC;
	_mp2h = 0;

	EP_Read_Data = _eed;		//Read data
	return EP_Read_Data;
}

/**
  * @brief EEPROM read page function.
  * @param[in] The array pointer to be reading to EEPROM.
  * @param[in] Specifies EEPROM page.
  * It can be 0~7,page 0 is mapping to address 0x00~0x0f,
  * page 1 is mapping to address 0x10~0x1f,page n is mapping to address (n-1)*16~(n-1)*16+15.
  * @param[in] The Byte number, it's length can up to 16.
  * @retval None
  */
void EEPROM_Read_page(u8 *Data,u8 page,u8 len)
{
	u8 i;
	u8 TempEEC;

	if (len > 16)	len = 16;

	/*config EEPROM init*/
	_mp2h = 1;

	_mp2l = 0x40;

	TempEEC = _iar2;

	_iar2 &= 0x6f;
	/*config EEPROM page*/

	_eea = page<<4;

	/*config EEPROM Read mode*/
	_iar2 |= 0x10;
	_iar2 |= 0x02;

	/*Read data*/
	for(i = 0; i < len; i++)
	{
		_mp2h = 1;
		_mp2l = 0x40;
		_iar2 |= 0x01;
		while(_iar2 & 0x01);
		Data[i] = _eed;
		//Data[i] = EEPROM_Read_Byte(i);
	}
	_iar2 = TempEEC;
	_mp2h = 0;

	return;
}



/**
  * @brief EEPROM erase page function.
  * @param[in] Specifies EEPROM page, It can be 0x00,0x10,0x20~0x70.
  * It can be 0~7,page 0 is mapping to address 0x00~0x0f,
  * page 1 is mapping to address 0x10~0x1f,page n is mapping to address (n-1)*16~(n-1)*16+15.
  * @param[in] The Byte number, it's length can up to 16.
  * @retval None
  */
void EEPROM_Erase_page(u8 page,u8 len)
{
	u8 i;
	u8 TempEMI,TempEEC;

	if (len > 16)	len = 16;

	TempEMI = _emi;

	/*config EEPROM init*/
	_mp2h = 1;

	_mp2l = 0x40;
	TempEEC = _iar2;

	_iar2 &= 0x6f;
	/*config EEPROM page*/

	_eea = page<<4;

/********** EEPROM Erase and Write time select **********/
	#ifdef	Erase_3200us_Write_2200us
		_iar2 &= 0x7f;

	#else
		_iar2 |= 0x80;

	#endif
/******* end of EEPROM Erase and Write time select ******/

	_iar2 |= 0x10;
	/*Write data*/
	for(i = 0; i < 16; i++)
		_eed = 0x55;

	_mp2h = 1;
	_mp2l = 0x40;

	_emi = 0;		//disable global interrupt

	/*config EEPROM Write mode*/
	_iar2 |= 0x40;
	_iar2 |= 0x20;

	_emi = TempEMI;		//enable global interrupt
	/* waitting for EEPROM write finishing */
	while(_iar2 & 0x20);
	_iar2 = TempEEC;
	_mp2h = 0;

	return;
}
void F_SaveDataToEEPROM()
{	/* 存放参数至EEPROM耗时77.86ms */
	u8 i;
	u8 len = sizeof(S_SET);
	if((B_KEYSET)&&(R_ReturnCnt == 0))
	{
		B_KEYSET = 0;
		// S_SET.CF = B_CF;
		// S_SET.HC = B_HC;
		memcpy((u8*)&(SaveOrRead), (u8*)&(S_SET), len);
		for (i = 0; i < len; i++)
			EEPROM_Write_Byte(SaveOrRead[i], i);
		for (i = 0; i < len; i++)
			SaveOrRead[i] = EEPROM_Read_Byte(i);
		//GCC_CLRWDT();
		/* 看门狗溢出时间是多少 > 写操作时间 */
		/* 页写函数 与页读函数有些问题 */
	}
	/* 按键设置后保存数据 */
	/* 避免突然断电没保存数据 */
	/* 下发数据保存数据 */
}
void F_ReadEEPROMToRAM()
{
	u8 i;
	u8 len = sizeof(S_SET);
	for (i = 0; i < len; i++)
		SaveOrRead[i] = EEPROM_Read_Byte(i);

	memcpy((u8*)&(S_SET), (u8*)&(SaveOrRead), len);
	memcpy((u8*)&(S_SET_LAST), (u8*)&(S_SET), len);

	if ((S_SET.ST == S_SET.SP)
	 &&(S_SET.ST == S_SET.AH)
	 &&(S_SET.ST == S_SET.AL)
	 &&(S_SET.ST == S_SET.PT)
	 &&(S_SET.ST == S_SET.CA)
	 &&(S_SET.ST == S_SET.CF)
	 &&(S_SET.ST == S_SET.HC)
	 &&(S_SET.ST == 0x00))
	{
		F_DefaultSettings(D_F, D_HEAT_MODE);
		B_KEYSET = 1;
	}
	/* 页写函数 与页读函数有些问题 */
}
/******************* (C) COPYRIGHT 2020 Holtek Semiconductor Inc *****END OF FILE****/