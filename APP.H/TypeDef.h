#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_

#define NULL	((void *)0)

#define FALSE	0
#define TRUE	1

#define _SUCC	0
#define _FAIL	1

#define _ON     0
#define _OFF    1

#define _OUTPUT 0
#define _IN     1

#define _ENABLE     1
#define _DISABLE    0

#define _SEG	    1
#define _COM     	0

#define _HIGH     1
#define _LOW      0

//	数据格式及错误返回代码
#define INVALID_DATA_8			((BYTE)0xff)
#define INVALID_DATA_16			((WORD)0xffff)
#define INVALID_DATA_32			((D32WORD)0x00ffffff)

#define NULL_DATA_8				((BYTE)0x7f)
#define NULL_DATA_16			((WORD)0x7fff)
#define NULL_DATA_32			((D32WORD)0x007fffff)

// Seletc Memory Mode
#if 1
    // C51 Core MCU
	#define BIG_ENDIAN
#else
	#define LITTLE_ENDIAN
#endif



// Typedef
#ifndef __BOOLEAN
	#define __BOOLEAN
	typedef unsigned char BOOL;
#endif

#ifndef __CHAR8
	#define __CHAR8
	typedef char	CHAR;
#endif /* #ifndef _CHAR8 */

#ifndef __UINT8
	#define __UINT8
	typedef unsigned char UINT8;
	#define BOOL UINT8
	#define BYTE UINT8
	#define u8 UINT8
#endif /* #ifndef _UINT8 */

#ifndef __INT8
	#define __INT8
	typedef signed char INT8;
	#define s8 INT8
#endif /* #ifndef _INT8 */

#ifndef __SHORT16
	#define __SHORT16
	typedef short SHORT16;
#endif /* #ifndef _SHORT16 */

#ifndef __INT16
	#define __INT16
	typedef int INT16;
	#define s16 INT16
#endif /* #ifndef _INT16 */

#ifndef __UINT16
	#define __UINT16
	typedef unsigned int UINT16;
	#define WORD UINT16
	#define u16 UINT16
#endif /* #ifndef _WORD */

#ifndef __INT32
	#define __INT32
	typedef long INT32;
	#define s32 INT32
#endif /* #ifndef _INT32 */

#ifndef __UINT32
	#define __UINT32
	typedef unsigned long UINT32;
//	#define DWORD UINT32
	#define D32WORD UINT32
	#define u32 UINT32
#endif /* #ifndef _UINT32 */

/*****************************************************************************/
/* Derived Data Structure                                     			     */
/*****************************************************************************/
#if defined(BIG_ENDIAN)
	typedef union
	{
		BYTE    ucVal;
		struct
		{
			BYTE  bit7      : 1;				/* bit 7 */
			BYTE  bit6      : 1;				/* bit 6 */
			BYTE  bit5      : 1;				/* bit 5 */
			BYTE  bit4      : 1;				/* bit 4 */
			BYTE  bit3      : 1;				/* bit 3 */
			BYTE  bit2      : 1;				/* bit 2 */
			BYTE  bit1      : 1;				/* bit 1 */
			BYTE  bit0      : 1;				/* bit 0 */
		}Bit;
	} UBYTE;

	typedef union
	{
		WORD wVal;
		struct
		{
			BYTE   byte1;					    /* bit 15 ~  8 */
			BYTE   byte0;					    /* bit 7  ~  0 */
		}Byte;
	} UWORD;

	typedef union
	{
		INT16 wVal;
		struct
		{
			INT8   byte1;					   /* bit 15 ~  8 */
			INT8   byte0;					   /* bit 7  ~  0 */
		}Byte;
	} SWORD;

	typedef union
	{
		UINT32 dwVal;
		struct
		{
			WORD  MSB;					   		/* MSB word code */
			WORD  LSB;				       		/* LSB word code */
		}Word;
		struct
		{
			BYTE   byte3;					    /* bit 31 ~ 24 */
			BYTE   byte2;					    /* bit 23 ~ 16 */
			BYTE   byte1;					 	/* bit 15 ~  8 */
			BYTE   byte0;					    /* bit 7  ~  0 */
		}Byte;
	} ULONG;

	typedef union
	{
		u8 value[4];
		INT32 lVal;
		struct
		{
			INT16  MSB;					      	/* MSB word code */
			INT16  LSB;					 	  	/* LSB word code */
		}Word;
		struct
		{
			INT8   byte3;					   	/* bit 31 ~ 24 */
			INT8   byte2;					   	/* bit 23 ~ 16 */
			INT8   byte1;					   	/* bit 15 ~  8 */
			INT8   byte0;					   	/* bit 7  ~  0 */
		}Byte;
	} SLONG;

	typedef union
	{
		struct
		{
			UINT32 MSB;
			UINT32 LSB;
		}Long;
		struct
		{
			WORD  word3;
			WORD  word2;
			WORD  word1;
			WORD  word0;
		}Word;
		struct
		{
			BYTE   byte7;					   /* bit 63 ~ 56 */
			BYTE   byte6;					   /* bit 55 ~ 48 */
			BYTE   byte5;					   /* bit 47 ~ 40 */
			BYTE   byte4;					   /* bit 39 ~ 32 */

			BYTE   byte3;					   /* bit 31 ~ 24 */
			BYTE   byte2;					   /* bit 23 ~ 16 */
			BYTE   byte1;					   /* bit 15 ~  8 */
			BYTE   byte0;					   /* bit 7  ~  0 */
		}Byte;
	} ULONGLONG;
#endif

#if defined(LITTLE_ENDIAN)
	typedef union
	{
		BYTE    ucVal;
		struct
		{
			BYTE  bit0      : 1;				/* bit 0 */
			BYTE  bit1      : 1;				/* bit 1 */
			BYTE  bit2      : 1;				/* bit 2 */
			BYTE  bit3      : 1;				/* bit 3 */
			BYTE  bit4      : 1;				/* bit 4 */
			BYTE  bit5      : 1;				/* bit 5 */
			BYTE  bit6      : 1;				/* bit 6 */
			BYTE  bit7      : 1;				/* bit 7 */
		}Bit;
	} UBYTE;

	typedef union
	{
		WORD wVal;
		struct
		{
			BYTE   byte0;					    /* bit 7  ~  0 */
			BYTE   byte1;					    /* bit 15 ~  8 */
		}Byte;
		struct
		{
			BYTE  bit0      : 1;				/* bit 0 */
			BYTE  bit1      : 1;				/* bit 1 */
			BYTE  bit2      : 1;				/* bit 2 */
			BYTE  bit3      : 1;				/* bit 3 */
			BYTE  bit4      : 1;				/* bit 4 */
			BYTE  bit5      : 1;				/* bit 5 */
			BYTE  bit6      : 1;				/* bit 6 */
			BYTE  bit7      : 1;				/* bit 7 */

			BYTE  bit8      : 1;				/* bit 8  */
			BYTE  bit9      : 1;				/* bit 9  */
			BYTE  bit10     : 1;				/* bit 10 */
			BYTE  bit11     : 1;				/* bit 11 */
			BYTE  bit12     : 1;				/* bit 12 */
			BYTE  bit13     : 1;				/* bit 13 */
			BYTE  bit14     : 1;				/* bit 14 */
			BYTE  bit15     : 1;				/* bit 15 */
		}Bit;
	} UWORD;

	typedef union
	{
		INT16 wVal;
		struct
		{
			INT8   byte0;					   	/* bit 7  ~  0 */
			INT8   byte1;					   	/* bit 15 ~  8 */
		}Byte;
	} SWORD;

	typedef union
	{
		UINT32 dwVal;
		struct
		{
			WORD  LSB;				       		/* LSB word code */
			WORD  MSB;					  		/* MSB word code */
		}Word;
		struct
		{
			BYTE   byte0;					    /* bit 7  ~  0 */
			BYTE   byte1;					 	/* bit 15 ~  8 */
			BYTE   byte2;					    /* bit 23 ~ 16 */
			BYTE   byte3;					    /* bit 31 ~ 24 */
		}Byte;
	} ULONG;

	typedef union
	{
		INT32 lVal;
		struct
		{
			INT16  LSB;					 	  /* LSB word code */
			INT16  MSB;					      /* MSB word code */
		}Word;
		struct
		{
			INT8   byte0;					   /* bit 7  ~  0 */
			INT8   byte1;					   /* bit 15 ~  8 */
			INT8   byte2;					   /* bit 23 ~ 16 */
			INT8   byte3;					   /* bit 31 ~ 24 */
		}Byte;
	} SLONG;

	typedef union
	{
		struct
		{
			UINT32 LSB;
			UINT32 MSB;
		}Long;
		struct
		{
			WORD  word0;
			WORD  word1;
			WORD  word2;
			WORD  word3;
		}Word;
		struct
		{
			BYTE   byte0;					   /* bit 7  ~  0 */
			BYTE   byte1;					   /* bit 15 ~  8 */
			BYTE   byte2;					   /* bit 23 ~ 16 */
			BYTE   byte3;					   /* bit 31 ~ 24 */

			BYTE   byte4;					   /* bit 39 ~ 32 */
			BYTE   byte5;					   /* bit 47 ~ 40 */
			BYTE   byte6;					   /* bit 55 ~ 48 */
			BYTE   byte7;					   /* bit 63 ~ 56 */
		}Byte;
	} ULONGLONG;
#endif

// Bit
#define	set(val, bits) ((val) |= (bits))
#define	clr(val, bits) ((val) &= ~(bits))
#define	tst(val, bits) ((val) & (bits))
#define	tog(val, bits) ((val) ^= (bits))

// 函数指针
typedef void (*pFun)(void);
typedef void (*pFunc)(u8);

#endif
