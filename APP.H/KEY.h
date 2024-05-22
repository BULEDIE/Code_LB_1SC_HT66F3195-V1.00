#ifndef __KEY__H__
#define	__KEY__H__

#define GPIO_PIN_0        ((UINT8)0x01)  /*!< Pin 0 selected */
#define GPIO_PIN_1        ((UINT8)0x02)  /*!< Pin 1 selected */
#define GPIO_PIN_2        ((UINT8)0x04)  /*!< Pin 2 selected */
#define GPIO_PIN_3        ((UINT8)0x08)  /*!< Pin 3 selected */
#define GPIO_PIN_4        ((UINT8)0x10)  /*!< Pin 4 selected */
#define GPIO_PIN_5        ((UINT8)0x20)  /*!< Pin 5 selected */
#define GPIO_PIN_6        ((UINT8)0x40)  /*!< Pin 6 selected */
#define GPIO_PIN_7        ((UINT8)0x80)  /*!< Pin 7 selected */

//------------------------------------------------------------
//	按键全速扫描 消抖计数
//------------------------------------------------------------
#define KeyDebounceCnt 2


/*------------------------------------------------------------
						按键软件编码
--------------------------------------------------------------
			b7    b6    b5    b4  |   b3    b2    b1    b0
--------------------------------------------------------------
键值定义：	KEY2S   -    -	  -    |   -    DOWN   UP   SET
--------------------------------------------------------------*/

#define UPKEY_DIRE    _pdc0
#define UPKEY_PU      _pdpu0
#define UPKEY_IO      _pd0

#define SETKEY_DIRE   _pac5
#define SETKEY_PU     _papu5
#define SETKEY_IO     _pa5

#define DOWNKEY_DIRE  _pac6
#define DOWNKEY_PU    _papu6
#define DOWNKEY_IO    _pa6

#define KEY2S				GPIO_PIN_7
#define SET_KEY				GPIO_PIN_0
#define UP_KEY				GPIO_PIN_1
#define DOWN_KEY			GPIO_PIN_2
#define SET_KEY2S			(SET_KEY | KEY2S)
#define UP_KEY2S			(UP_KEY | KEY2S)
#define DOWN_KEY2S			(DOWN_KEY | KEY2S)

#define F_UP_KEY_IN_EN_and_PU_EN()  { set(_pdc, GPIO_PIN_0);set(_pdpu, GPIO_PIN_0);}
#define F_SET_KEY_IN_EN_and_PU_EN() { set(_pac, GPIO_PIN_5);set(_papu, GPIO_PIN_5);}
#define F_DOWN_KEY_IN_EN_and_PU_EN(){ set(_pac, GPIO_PIN_6);set(_papu, GPIO_PIN_6);}

#define F_UP_KEY_OUT_EN_and_PU_DN()  { clr(_pdc, GPIO_PIN_0);clr(_pdpu, GPIO_PIN_0);}
#define F_SET_KEY_OUT_EN_and_PU_DN() { clr(_pac, GPIO_PIN_5);clr(_papu, GPIO_PIN_5);}
#define F_DOWN_KEY_OUT_EN_and_PU_DN(){ clr(_pac, GPIO_PIN_6);clr(_papu, GPIO_PIN_6);}

typedef struct
{
	u8 Last;
	u8 Now;
	u8 Down;
	u8 Up;
	u8 ValueBuf;
	u8 Value;
	u16 KeepCnt;
	u8 Speed;
	u8 Lcd2Hz;
	u16 HoldTime;
}T_Key;
MyDef T_Key volatile Key;

#define D_64Hz	 64

MyDef UBYTE R_KeyFlag;
#define	B_Key64HzScan		R_KeyFlag.Bit.bit0		// Key Scan 16Hz
#define	B_Key64HzStep		R_KeyFlag.Bit.bit1		// Key Step 8Hz
#define	B_Key16HzStep		R_KeyFlag.Bit.bit2		// Key Step 8Hz
#define	B_Key8HzStep		R_KeyFlag.Bit.bit3		// inc或dec键按按住标志，当inc或dec键按住时，不闪烁设置数据

#define B_UPKEY				R_KeyFlag.Bit.bit5		//
#define B_KeyChange			R_KeyFlag.Bit.bit6		//

MyDef UBYTE R_KeyFlag1;
#define	B_IncDecKeyHold		R_KeyFlag1.Bit.bit0		// Key Scan 16Hz
// #define	B_Key64HzStep		R_KeyFlag1.Bit.bit1		// Key Step 8Hz
// #define	B_Key16HzStep		R_KeyFlag1.Bit.bit2		// Key Step 8Hz
// #define	B_Key8HzStep		R_KeyFlag1.Bit.bit3		// inc或dec键按按住标志，当inc或dec键按住时，不闪烁设置数据
#define KEY_Valid	   			(0xFF		  )	//设置菜单，长按连发设置参数抬起键音响了1次
#define KEY_NULL	   			(0			  )	//
#define D_KeyTimerOut	 		(16			  )	//64hz*16=250ms
#define D_LongKey1s	 		    (64*1		  )	//长按1秒
#define D_LongKey2s	 		    (64*2		  )	//长按2秒
#define D_LongKey3s	 		    (64*3		  )	//长按3秒
#define D_LongKey4s	 		    (64*4		  )	//长按3秒
#define D_LongKey5s	 		    (64*5		  )	//长按3秒
#define D_LongKey6s	 		    (64*6		  )	//长按5秒
#define D_LongKey_OF_Ctrl	 	(D_LongKey5s+1)	//避免长按计时溢出
#define D_Key_Union_Time   		(32			  ) //16hz*32 = 500ms
#define D_Key_Lcd_Disp_Time   	(64			  ) //16hz*48 = 750ms

void F_KeyInit();
void F_KeyRstFactory();
void F_GetKey();
void F_KeyScan();
void F_SetMenu();
void F_KeySever();
s16 F_SetADD(s16 R_Indexes, s16 R_HiValue);
s16 F_SetSUB(s16 R_Indexes, s16 R_LowValue);
void F_HEAT_COOL_MODE_SW();

#endif
