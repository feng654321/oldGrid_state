#ifndef __GENERAL_H__
#define __GENERAL_H__

extern uchar Byte_BCD( uchar Data );
extern void Word_BCD2( uchar *Ptr, u16 Data );
extern void Long_BCD3(uchar *Ptr, ulong Data);
extern void Long_BCD4(uchar *Ptr, ulong Data);
extern uchar BCD_Byte(uchar Data);
extern u16 BCD2_Word(uchar *Ptr);
extern ulong BCD3_Long(uchar *Ptr);
extern ulong BCD4_Long(uchar *Ptr);
extern void BCD1Inc(uchar *Dest);
extern void BCD1Dec(uchar *Dest);
extern void BCD2Inc(uchar *Dest);
extern void BCD3Inc(uchar *Dest);
extern void BCD4Inc(uchar *Dest);
extern uchar TestBCD(uchar a);
//extern uchar TestBCDNum(uchar *point,uchar num); //ZD 此函数在整个程序中不用，并有同样的函数
extern long AbsoluteValue( long value);
extern uchar CheckSun(uchar* buf,u16 lens);
extern uchar SwapBuf(uchar* buf, u16 lens);
#endif

