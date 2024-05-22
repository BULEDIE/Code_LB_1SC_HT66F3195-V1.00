#ifndef __BUZ_H__
#define __BUZ_H__

#define BZ_DIRE  _pbc5
#define BZ_PU    _pbpu5
#define BZ_IO    _pb5

#define RELAY_DIRE  _pbc6
#define RELAY_PU    _pbpu6
#define RELAY_IO    _pb6

#define H_LED_DIRE  _pcc6
#define H_LED_PU    _pcpu6
#define H_LED_IO    _pc6

#define C_LED_DIRE  _pac1
#define C_LED_PU    _papu1
#define C_LED_IO    _pa1

#define F_BUZON() 	  ( clr(_pb, GPIO_PIN_5))
#define F_BUZOFF()    ( set(_pb, GPIO_PIN_5))
#define F_TESTTIME()  { tog(_pb, GPIO_PIN_3);tog(_pb, GPIO_PIN_3);}
#define F_LEDFLASH()  ( tog(_pb, GPIO_PIN_3))

#define F_Cool_Led_On()   clr(_pc, GPIO_PIN_6)
#define F_Cool_Led_Off()  set(_pc, GPIO_PIN_6)

#define F_Heat_Led_On()   clr(_pa, GPIO_PIN_1)
#define F_Heat_Led_Off()  set(_pa, GPIO_PIN_1)

#define F_AN8_EN()   set(_pbs1, 0x03)
#define F_AN8_DN()   clr(_pbs1, 0x03)
#define F_AN9_EN()   set(_pds0, 0x0C)
#define F_AN9_DN()   clr(_pds0, 0x0C)

void F_Buz1KHzCntBiBi();
u8 F_KeyBreakFault();

#endif
