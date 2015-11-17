/***************************************************************************
 *
 *
 *
 * COPYRIGHT (C) 2009 PaxHZ, ALL RIGHTS RESERVED
 * $Abstract: 类型定义
 *
 * $Source: src\include\basetype.h$
 * $Author: wudengben$
 * $Date:2009-6-29 15:17$ 
 * $Revision:1.0 类型定义$
 *
 * $Log:basetype.h$
 * Revision 1.0  2009-6-29 15:15  wudengben
 * 类型定义
 *
 *
 ***************************************************************************/


#ifndef  BASETYPE_H
    #define BASETYPE_H    

#include <stdint.h>

typedef unsigned char uint8;
typedef signed   char  int8;
typedef unsigned short int uint16;
typedef signed short int int16;
typedef unsigned long int uint32;
typedef signed long int int32;
typedef unsigned long long uint64;
typedef signed long long int64;
typedef uint8 bool;



#define suint8  static unsigned char 
#define sint8   static signed   char
#define suint16 static unsigned short int 
#define sint16  static signed   short int 
#define suint32 static unsigned long int  
#define sint32  static signed   long int  
#define suint64 static unsigned long long 
#define sint64  static signed   long long 
#define sbool   static uint8       


       
#define false 0
#define true  1


struct day_data_st
{
    uint32 day;  /*目前月份的日数，范围01-31*/
    uint32 month;/*代表目前月份，从一月算起，范围从0-11*/
    uint32 year; /*从1900 年算起至今的年数*/
};


#define xprintf      //printf



#endif

