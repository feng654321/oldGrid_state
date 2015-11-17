/***************************************************************************
 *
 *
 *
 * COPYRIGHT (C) 2009 PaxHZ, ALL RIGHTS RESERVED
 * $Abstract: ���Ͷ���
 *
 * $Source: src\include\basetype.h$
 * $Author: wudengben$
 * $Date:2009-6-29 15:17$ 
 * $Revision:1.0 ���Ͷ���$
 *
 * $Log:basetype.h$
 * Revision 1.0  2009-6-29 15:15  wudengben
 * ���Ͷ���
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
    uint32 day;  /*Ŀǰ�·ݵ���������Χ01-31*/
    uint32 month;/*����Ŀǰ�·ݣ���һ�����𣬷�Χ��0-11*/
    uint32 year; /*��1900 ���������������*/
};


#define xprintf      //printf



#endif

