#ifndef __DATATYPE_H__
#define __DATATYPE_H__

//#define NO_CLEAR  __no_init
//#define NO_OPTIMIZE  __root
#define NO_CLEAR   
#define NO_OPTIMIZE   
typedef char string;
typedef unsigned char uchar;
typedef signed char schar;
//typedef unsigned short u16;
typedef unsigned short ushort;
typedef signed short sint;
typedef unsigned long  ulong;
typedef signed long  slong;
typedef unsigned long long ulLong;
typedef volatile unsigned long vu32;
typedef volatile unsigned short vu16;
typedef void (*func)(void);

typedef unsigned char       u8;   
typedef unsigned short      u16;   
typedef unsigned long       u32;    
typedef unsigned long long  u64;  

typedef signed char         s8;   
typedef signed short        s16;  
typedef signed long         s32;  
typedef signed long long    s64;  

//typedef enum {FALSE = 0, TRUE = !FALSE} bool;

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

//typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

#endif


