
#include "common.h"

//**********************************************************************
// turn byte data to BCD data
//**********************************************************************
uchar Byte_BCD( uchar Data )
{
    if( Data > 99 ) 
    {
        Data = Data - 100;
        //return 0x00;
    }
    return( Data/10*0x10 + Data%10 );
}
//**********************************************************************
// turn word data to BCD data
//**********************************************************************
void Word_BCD2( uchar *Ptr, u16 Data )
{
    if( Data > 9999 ) 
    {
        Data = Data - 10000;
        //*(Ptr+1) = 0x00;
        //*Ptr = 0x00;
        //return;
    }

    *(Ptr+1) = Byte_BCD( (uchar)(Data/100) );
    *Ptr = Byte_BCD( (uchar)(Data%100) );
}
//**********************************************************************
// turn long data to BCD3 data
//**********************************************************************

void Long_BCD3(uchar *Ptr, ulong Data)
{
    if( Data > 999999 ) 
    {
        Data = Data - 1000000;
        //*(Ptr+2) = 0x00;
            //*(Ptr+1) = 0x00;
            //*Ptr = 0x00;
            //return;
    }
    *(Ptr+2) = Byte_BCD( (uchar)(Data/10000));
    Word_BCD2(Ptr, (u16)(Data%10000));
}

//**********************************************************************
// turn long data to BCD4 data
//**********************************************************************
void Long_BCD4(uchar *Ptr, ulong Data)
{
    if( Data > 99999999 ) 
    {
        Data = Data - 100000000;
        //*(Ptr+3) = 0x00;
        //*(Ptr+2) = 0x00;
        //*(Ptr+1) = 0x00;
        //*Ptr = 0x00;
        //return;
    }
    Word_BCD2(Ptr+2, Data/10000);
    Word_BCD2(Ptr, Data%10000);
}
//**********************************************************************
// turn BCD data to byte data
//**********************************************************************
uchar BCD_Byte(uchar Data)
{
   return(((Data>>4)&0x0f)*10+(Data&0x0f));
}
//**********************************************************************
// turn BCD2 data to word data
//**********************************************************************
u16 BCD2_Word(uchar *Ptr)
{
   return(  (u16)BCD_Byte(*Ptr)+
            (u16)BCD_Byte(*(Ptr+1))*100 );
}
//**********************************************************************
// turn BCD3 data to word data
//**********************************************************************

ulong BCD3_Long(uchar *Ptr)
{
   return(  (ulong)BCD_Byte(*Ptr)+
            (ulong)BCD_Byte(*(Ptr+1))*100+
            (ulong)BCD_Byte(*(Ptr+2))*10000 );
}

//**********************************************************************
// turn BCD4 data to word data
//**********************************************************************
ulong BCD4_Long(uchar *Ptr)
{
   return(  (ulong)BCD_Byte(*Ptr)+
            (ulong)BCD_Byte(*(Ptr+1))*100+
            (ulong)BCD_Byte(*(Ptr+2))*10000+
            (ulong)BCD_Byte(*(Ptr+3))*1000000 );
}
//**********************************************************************
// BCD data 1 byte add 1
//**********************************************************************
void BCD1Inc(uchar *Dest)
{
    uchar i;
    
    i = BCD_Byte(*Dest);
    i++;
    i = Byte_BCD(i);
    *Dest = i;
}


void BCD1Dec(uchar *Dest)
{
    uchar i;
    
    i = BCD_Byte(*Dest);
    i--;
    i = Byte_BCD(i);
    *Dest = i;
}
//**********************************************************************
// BCD data 2 byte add 1
//**********************************************************************
/*void BCD2Inc(uchar *Dest)
{
    
}*/
//**********************************************************************
// BCD data 3 byte add 1
//**********************************************************************
/*void BCD3Inc(uchar *Dest)
{
    
}*/
//**********************************************************************
// BCD data 4 byte add 1
//**********************************************************************
/*void BCD4Inc(uchar *Dest)
{
    
}*/

//**********************************************************************
// test BCD number
//**********************************************************************
uchar TestBCD(uchar a)
{
    if(((a>>4)<=9)&&((a&0xf)<=9))
        return  1;
    else
        return 0;
}

//**********************************************************************
// test BCD number
//**********************************************************************
//ZD 此函数在整个程序中不用，并有同样的函数
/*
uchar TestBCDNum(uchar *point,uchar num)
{
    uchar l,value;
    
    value=0;
    if(num==0) 
    {
        value=0;
    }
    else
    {
        for(l=0;l<num;l++)
        {
            value=value+TestBCD(*(point+l));
        }
    }
    
    return value;
}*/



long AbsoluteValue( long value)
{
    if(value < 0)
    {
        value = -value;
    }
    return(value);
}


uchar CheckSun(uchar* buf,u16 lens)
{
    uchar returnData;
    u16 i;
    
    returnData = 0;
    for(i=0;i<lens;i++)
    {
        returnData += buf[i];
    }
    
    return(returnData);
}

//转换顺序
uchar SwapBuf(uchar* buf, u16 lens)
{
    u16 i;
    uchar uctemp;
    if(buf == NULL)
        return 0;
    for(i=0; i<lens/2; i++)
    {
        uctemp = buf[i];
        buf[i] = buf[lens-1-i];
        buf[lens-1-i] = uctemp;
    }
    return 1;
}







