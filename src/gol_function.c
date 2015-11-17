#ifndef __GOL_FUNCTION_C__
#define __GOL_FUNCTION_C__

#include "common.h"
#if 1

//用于数据初始化
const uchar ucZeroArray[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uchar BCDToByte(uchar Data)
{
    if (!TestBcd(Data))
    {
        return 0xff;
    }
    //else
    return(((Data>>4)&0x0f)*10+(Data&0x0f));
}
uchar ByteToBCD( uchar Data )
{
    Data = Data%100;
    return( Data/10*0x10 + Data%10 );
}

uchar OneByteHexToBcd(uchar a)
{
    uchar l;
    l=((a/10)<<4)+(a%10);
    return l;
}
uchar OneByteBcdToHex(uchar a)
{
    return (10*(a>>4)+(0xf&a));
}
uchar TestBcd(uchar a)
{
    if(((a>>4)<=9)&&((a&0xf)<=9))
        return  1;
       return 0;
}

//**********************************************************************
// test ADDR number
//**********************************************************************
uchar TestAddr(uchar a)
{
    /*if(((a>>4)<=10)&&((a&0xf)<=10))
        return  TEST_OK;
    else
        return TEST_FAIL;
    */
    if(a & 0xAA)
        return TEST_FAIL;
    return  TEST_OK;
}

uchar TestBcdNum(uchar *point, uchar num)
{
    uchar l,value;
    value=0;
    if(num==0) 
        return 0;
    for(l=0;l<num;l++)
        value=value+TestBcd(*(point+l));
    return value;
}

u16 TestBcdNum2(uchar *point, u16 num)
{
    u16 l,value;
    value=0;
    if(num==0) 
        return 0;
    for(l=0;l<num;l++)
        value=value+TestBcd(*(point+l));
    return value;
}

uchar TestZeroNum(uchar *point, uchar num)
{
    uchar l,value;
    value=0;
    if(num==0)
        return 0;

    for(l=0;l<num;l++)
    {
        if(0==*(point+l))
            value=value+1;
    }
    return value;
}

uchar Test99Num(uchar *point, uchar num)
{
    uchar l,value;
    value=0;
    if(num==0)
        return 0;

    for(l=0;l<num;l++)
    {
        if(0x99==*(point+l))
            value=value+1;
    }
    return value;
}


uchar TestYear(uchar a)
{
    if((TestBcd(a)==1)&&(a<=0x59))       // dao 2039 year
        return  1;
    return 0;
 }
    

uchar TestMonth(uchar a)
  {
    if((TestBcd(a)==1)&&(0!=a)&&(a<=0x12)) 
        return  1;
    return 0;
}

uchar TestDay(uchar a)
{
    if((TestBcd(a)==1)&&(0!=a)&&(a<=0x31)) 
        return  1;
    return 0;
}
uchar TestWeek(uchar a)
{
    if(a<7) 
        return  1;
    return 0;
}
uchar TestHour(uchar a)
{
    if((TestBcd(a)==1)&&(a<=0x23))
        return  1;
    return 0;
}
uchar TestMinute(uchar a)
{
    if((TestBcd(a)==1)&&(a<=0x59))   
        return  1;
    return 0;
}

uchar TestSecond(uchar a)
{
    if((TestBcd(a)==1)&&(a<=0x59)) 
        return  1;
    return 0;
}



uchar ValueBcdFromHex(uchar a)
{
    return (((a/10)<<4)+(a%10));
}


uchar ValueHexFromBcd(uchar a)
{
    return (10*(a>>4)+(0xf&a));
}

uchar  Byte1BcdAdd(uchar ucValue)
{
    return (ValueBcdFromHex(ValueHexFromBcd(ucValue)+1));
}

uchar Byte1PointBCDAdd1(uchar *Point)
{
    if((*Point)>=0x99)           // ==99 -->jin wei 
    {
        (*Point)=0;
        return 1;
    }

    if(((*Point)&0xf)>=9)
    {
        (*Point)=((*Point)&0xf0)+0x10; 
    }
    else 
    {
        (*Point)=(*Point)+1;
    }
    return 0;
}
uchar ByteNPointBCDAdd1(uchar * Point,uchar ucNum)
{
    uchar ucTemp;
    if(0==ucNum)
        return 0;
    for(ucTemp=0;ucTemp<ucNum;ucTemp++)
    {
        if(0==Byte1PointBCDAdd1(Point+ucTemp))
        {
            return 0;
        }
    }
    return 1;
}

ulong ValueHexFromRam3Bcd(ulong ulRamaddr)
{
    ulong l;
    l=ValueHexFromBcd(RAM[ulRamaddr+2]);
    l=l*100+ValueHexFromBcd(RAM[ulRamaddr+1]);
    l=l*100+ValueHexFromBcd(RAM[ulRamaddr]);
    return l;
}   


u16 ValueHexFromRam2Bcd(ulong ulRamaddr)
{
    u16 l;
    l=ValueHexFromBcd(RAM[ulRamaddr+1]);
    l=l*100+ValueHexFromBcd(RAM[ulRamaddr]);
    return l;
}   

ulong HexFromRam3Bcd(uchar *pSrc)
{
    ulong l;
    uchar ucBcd;

    ucBcd = *(pSrc+2);
    l=(10*(ucBcd>>4)+(ucBcd&0xf));
    ucBcd = *(pSrc+1);
    l=l*100+(10*(ucBcd>>4)+(ucBcd&0xf));
    ucBcd = *(pSrc+0);
    l=l*100+(10*(ucBcd>>4)+(ucBcd&0xf));
    
    return l;
}   

u16 HexFromRam2Bcd(uchar *pSrc)
{
    ulong l;
    uchar ucBcd;

    ucBcd = *(pSrc+1);
    l=(10*(ucBcd>>4)+(ucBcd&0xf));
    ucBcd = *(pSrc+0);
    l=l*100+(10*(ucBcd>>4)+(ucBcd&0xf));
    
    return l;
}   

uchar HexFromRam1Bcd(uchar *pSrc)
{
    uchar ucBcd;
    ucBcd = *(pSrc+0);
    return (10*(ucBcd>>4)+(ucBcd&0xf));
}

uchar Byte1BcdRamAdd10(ulong ulRamaddr)
{
    if(RAM[ulRamaddr]>0x89)
    {
        RAM[ulRamaddr]=0;
        return 1;
    }
    else
    {
        RAM[ulRamaddr]=RAM[ulRamaddr]+0x10;
        return 0;
    }
}


uchar Byte1BcdRamAdd(ulong ulRamaddr)
{
    if(RAM[ulRamaddr]>=0x99)           // ==99 -->jin wei 
    {
        RAM[ulRamaddr]=0;
        return 1;
    }

    if((RAM[ulRamaddr]&0xf)>=9)
    {
        RAM[ulRamaddr]=(RAM[ulRamaddr]&0xf0)+0x10; 
    }
    else 
    {
        RAM[ulRamaddr]=RAM[ulRamaddr]+1;
    }
    return 0;

}

void Byte2BcdRamAdd(ulong ulRamaddr)
{
    uchar l,value;
    if(Byte1BcdRamAdd(ulRamaddr)==1)
        Byte1BcdRamAdd(ulRamaddr+1);
    // bcd
    if(2!=TestBcdNum(&RAM[ulRamaddr],2))
    {
        for(l=0;l<2;l++)
        {
            value=ValueHexFromBcd(RAM[ulRamaddr+l])%100;
            RAM[ulRamaddr+l]=OneByteHexToBcd(value);
        }
    }
}


void Byte3BcdRamAdd(ulong ulRamaddr)
{
    uchar l,value;
    if(Byte1BcdRamAdd(ulRamaddr)==1)
        if(Byte1BcdRamAdd(ulRamaddr+1)==1) 
            Byte1BcdRamAdd(ulRamaddr+3);
    // bcd
    if(3!=TestBcdNum(&RAM[ulRamaddr],3))
    {
        for(l=0;l<3;l++)
        {
            value=ValueHexFromBcd(RAM[ulRamaddr+l])%100;
            RAM[ulRamaddr+l]=OneByteHexToBcd(value);
        }
    }
}

void Byte4BcdRamAdd(ulong ulRamaddr)
{
    uchar l,value;
    if(Byte1BcdRamAdd(ulRamaddr)==1)
        if(Byte1BcdRamAdd(ulRamaddr+1)==1) 
            if(Byte1BcdRamAdd(ulRamaddr+2)==1)
                Byte1BcdRamAdd(ulRamaddr+3);
    // bcd
    if(4!=TestBcdNum(&RAM[ulRamaddr],4))
    {
        for(l=0;l<4;l++)
        {
            value=ValueHexFromBcd(RAM[ulRamaddr+l])%100;
            RAM[ulRamaddr+l]=OneByteHexToBcd(value);
        }
    }
}




void Byte5BcdRamAdd(ulong ulRamaddr)
{
    uchar l,value;
    if(Byte1BcdRamAdd(ulRamaddr)==1)
        if(Byte1BcdRamAdd(ulRamaddr+1)==1) 
            if(Byte1BcdRamAdd(ulRamaddr+2)==1)
                if(Byte1BcdRamAdd(ulRamaddr+3)==1)
                    Byte1BcdRamAdd(ulRamaddr+4);
    // bcd
    if(5!=TestBcdNum(&RAM[ulRamaddr],5))
    {
        for(l=0;l<5;l++)
        {
            value=ValueHexFromBcd(RAM[ulRamaddr+l])%100;
            RAM[ulRamaddr+l]=OneByteHexToBcd(value);
        }
    }
}

void Byte1HexTo8Bit(uchar ucData,uchar * ucDataOut)
{
    uchar ucTemp;
    for(ucTemp=0;ucTemp<8;ucTemp++)
    {
        ucDataOut[7-ucTemp]=0;
        if(1==(ucData%2))
        {
            ucDataOut[7-ucTemp]=1;
        }
        ucData=ucData>>1;
    }
}





const uchar WeekTab2000To2099[13] = {
    0 ,// no have
    3 ,// 1month
    6 ,// 2month
    0 ,// 3month
    3 ,// 4month
    5 ,// 5month
    1 ,// 6month
    3 ,// 7month
    6 ,// 8month
    1 ,// 9month
    4 ,// 10month
    0 ,// 11month
    2  // 12month
};
uchar WeekDay20( uchar *upDay)
{
    uchar week;
    uchar y,m;
    m=*(upDay+1);
    y=*(upDay+2);
    week = WeekTab2000To2099[m]; 
    if ((m < 3) && (y & 0x03))
    { 
        week++; 
    }
    y = y + (y >> 2); 
    week = (week +  y + *(upDay) + 2) % 7; 
    return (week) ; 
}
const uchar table_week_year[]=// week of 2000----2005
                      {6,1,2,3,4,6,0,1,2,4,5,6,0,2,3,4,5,0,1,2,3,5,6,0,1,3,4,5,6,1,2,3,4,6,0,1,2,4,5,6,0,2,3,5,6};
const u16 table_month28[]={0,31,59,90,120,151,181,212,243,273,304,334};
const u16 table_month29[]={0,31,60,91,121,152,182,213,244,274,305,335};

u16 NumDayFromDate(uchar *ucpDay)
{
    u16 uiTempDayNum;
    if(3==TestDay(*ucpDay)+TestMonth(*(ucpDay+1))+TestYear(*(ucpDay+2)))
    {
        uiTempDayNum=ValueHexFromBcd(*(ucpDay+2));
        uiTempDayNum=uiTempDayNum*365+(uiTempDayNum+3)/4;
        if(0==((ValueHexFromBcd(*(ucpDay+2)))%4))
            uiTempDayNum=uiTempDayNum+table_month29[ValueHexFromBcd(*(ucpDay+1))-1];
        else 
            uiTempDayNum=uiTempDayNum+table_month28[ValueHexFromBcd(*(ucpDay+1))-1];
        uiTempDayNum=uiTempDayNum+ValueHexFromBcd(*ucpDay)-1;
        return uiTempDayNum;
    }
    else
    {
        return 0;
    }
}

ulong  mmHHDDMMYYToLong(uchar *ucPoint)
{
    ulong ulTime;
    ulTime=NumDayFromDate(&ucPoint[2]);
    ulTime=ulTime*24 + ValueHexFromBcd(ucPoint[1]);
    ulTime=ulTime*60 + ValueHexFromBcd(ucPoint[0]);
    return ulTime;
    // memcpy(ucPoint, (uchar*) &ulTime, 3);
}



void DateFromNumDay(u16 uiDataNum,uchar *ucpDay)
{
    uchar ucTemp;
    
    if((uiDataNum>0xfffe)||(0==uiDataNum))
    {
        memset(ucpDay, 0x00, 3);
        return;
    }
    uiDataNum++;
    ucTemp=uiDataNum/365;
    uiDataNum=uiDataNum%365;
    ucpDay[2]=ucTemp;
    ucTemp=(ucTemp+3)/4;
    if(ucTemp>=uiDataNum)
    {
        ucpDay[2]--;
        if(ucpDay[2]%4)
        {
            uiDataNum+=365;
        }
        else
        {
            uiDataNum+=366;
        }
        uiDataNum=uiDataNum-ucTemp;
        
    }
    else
    {
        uiDataNum=uiDataNum-ucTemp;
    }
    
    if(0==(ucpDay[2]%4))
    {
        for(ucTemp=12;ucTemp>0;ucTemp--)
        {
            if(table_month29[ucTemp-1]<uiDataNum)
            {
                ucpDay[1]=ucTemp;
                ucpDay[0]=uiDataNum-table_month29[ucTemp-1];
                break;
            }
        }
    }
    else
    {
        for(ucTemp=12;ucTemp>0;ucTemp--)
        {
            if(table_month28[ucTemp-1]<uiDataNum)
            {
                ucpDay[1]=ucTemp;
                ucpDay[0]=uiDataNum-table_month28[ucTemp-1];
                break;
            }
        }
    }
    for(ucTemp=0;ucTemp<3;ucTemp++)
    {
        ucpDay[ucTemp]=ValueBcdFromHex(ucpDay[ucTemp]);
    }
    
}




/*********************************************************************
原型：void LongDataTommHHDDMMYY(ulong ulData,uchar *ucPoint);
功能：初始化需量数据
参数：
        ulData 当前时间差
        ucPoint 返回的时间的地址
            数据格式为 分 时日月年
输入：无
返回：无
范围：应用层直接调用
注释：无
作者：张龙
版本：V1.0
最后修改时间：2009-05-04
修改说明：创建
********************************************************************/

void LongTommHHDDMMYY(ulong ulData,uchar *ucPoint)
{
    ucPoint[0]=ValueBcdFromHex(ulData%60);
    ulData=ulData/60;
    ucPoint[1]=ValueBcdFromHex(ulData%24);
    ulData=ulData/24;
    DateFromNumDay(ulData,ucPoint+2);
}



uchar WeekFromDayMonthYear(uchar *day)
{
    u16 l;
    uchar l1,l2; //,l3;
    l2=ValueHexFromBcd(*(day+1));
    if((ValueHexFromBcd(*(day+2))%4)==0)
        l=table_month29[l2-1];
    else 
        l=table_month28[l2-1];
    l=ValueHexFromBcd(*day)-1+table_week_year[ValueHexFromBcd(*(day+2))]+l;
    l1=l%7;
    return l1;
}
uchar TestDayMonthYear(uchar *day)
{
    uchar a7;
    if(3!=TestDay(*day)+TestMonth(*(day+1))+TestYear(*(day+2)))
    {
        return 0;
    }
    
    switch(*(day+1))// month
    {
        case 0x1:
        case 0x3:
        case 0x5:
        case 0x7:
        case 0x8:
        case 0x10:
        case 0x12: 
            a7=1;
            break;
        case 0x4:
        case 0x6:
        case 0x9:
        case 0x11:
            if((0!=*day)&&(*day<0x31)) 
            {
                a7=1;
            }
            else 
            {
                a7=0;
            }
            break;
            default:
            if((ValueHexFromBcd(*(day+2))%4)==0) 
            {
                if((0!=*day)&&(*day<0x30)) 
                {
                    a7=1;
                }
                else  
                {
                    a7=0;
                }
            }
            else
            {
                if((0!=*day)&&(*day<0x29)) 
                {
                    a7=1;
                }
                else  
                {
                    a7=0;
                }
            }
            break;
    }
    return a7;
}

uchar TestSecondMinuteHourDayMonthYear(second,day)
uchar *second,*day;
{
    uchar a7;
    a7=0;
    a7=TestSecond(*second)+TestMinute(*(second+1))+TestHour(*(second+2))+TestDay(*day)
        +TestMonth(*(day+1))+TestYear(*(day+2));
    if(a7!=6)
        return 0;
    else 
    {
        switch(*(day+1))// month
        {
        case 0x1:
        case 0x3:
        case 0x5:
        case 0x7:
        case 0x8:
        case 0x10:
        case 0x12: 
            a7=1;
            break;
        case 0x4:
        case 0x6:
        case 0x9:
        case 0x11:
            if((0!=*day)&&(*day<0x31)) 
                a7=1;
            else 
                a7=0;
            break;
            default:
            if((ValueHexFromBcd(*(day+2))%4)==0) 
            {
                if((0!=*day)&&(*day<0x30)) 
                    a7=1;
                else  
                    a7=0;
            }
            else
            {
                if((0!=*day)&&(*day<0x29)) 
                    a7=1;
                else  
                    a7=0;
            }
            break;
        }
    return a7;
    }
}

uchar TestMinuteHour(uchar *point)
{
    if(2==TestMinute(*point)+TestHour(*(point+1)))
        return 1;
    return 0;
}
uchar TestDayMonth(uchar *point)
{
    uchar time[6],l;
    for(l=0;l<6;l++)
        time[l]=0;
    time[3]=*point;
    time[4]=*(point+1);
    return TestSecondMinuteHourDayMonthYear(&time[0],&time[3]);
}

#if 1
void LongToData2BCD(ulong value, uchar *point)
{
    ulong l1, ultemp;
    uchar m,m1,m2;  
    l1=value;
    for(m2=0;m2<2;m2++)
    {
        ultemp = l1/10;
        m=l1-ultemp*10;
        
        l1 = ultemp;
        ultemp = l1/10;
        m1=l1-ultemp*10;
        
        *(point+m2)=(m1<<4)+m;  
        l1=ultemp;
    }  
}
void LongToData4BCD(ulong value, uchar *point)
{
    ulong l1, ultemp;
    uchar m,m1,m2;  
    l1=value;
    for(m2=0;m2<4;m2++)
    {
        ultemp = l1/10;
        m=l1-ultemp*10;
        
        l1 = ultemp;
        ultemp = l1/10;
        m1=l1-ultemp*10;
        
        *(point+m2)=(m1<<4)+m;  
        l1=ultemp;
    }  
}
#else
void LongToData4BCD1(ulong value, uchar *point);
void LongToData4BCD1(ulong value, uchar *point)
{
    ulong l1;
    uchar m,m1,m2;  
    l1=value;
    for(m2=0;m2<4;m2++)
    {
        m=l1%10;
        m1=(l1%100)/10;
        *(point+m2)=(m1<<4)+m;  
        l1=l1/100;
    }  
}
#endif

void LongToData5BCD(value,point)
ulong value;
uchar *point;
{ulong l1;
  uchar m,m1,m2;  
  l1=value/10;
  for(m2=1;m2<5;m2++)
    {
             m=l1%10;
             m1=(l1%100)/10;
            *(point+m2)=(m1<<4)+m;  
            l1=l1/100;
    }  
  *(point)=(value%10)<<4;
}



ulong Bcd5DataToLong(uchar *Ptr)
{
   return(  (ulong)OneByteBcdToHex(*Ptr)/10+
            (ulong)OneByteBcdToHex(*(Ptr+1))*10+
            (ulong)OneByteBcdToHex(*(Ptr+2))*1000+
            (ulong)OneByteBcdToHex(*(Ptr+3))*100000+
            (ulong)OneByteBcdToHex(*(Ptr+4))*10000000 );
}

ulong Bcd4DataToLong(uchar *Ptr)
{
   return(  (ulong)OneByteBcdToHex(*Ptr)+
            (ulong)OneByteBcdToHex(*(Ptr+1))*100+
            (ulong)OneByteBcdToHex(*(Ptr+2))*10000+
            (ulong)OneByteBcdToHex(*(Ptr+3))*1000000);
}

ulong Bcd3DataToLong(uchar *Ptr)
{
   return(  (ulong)OneByteBcdToHex(*Ptr)+
            (ulong)OneByteBcdToHex(*(Ptr+1))*100+
            (ulong)OneByteBcdToHex(*(Ptr+2))*10000);
}


u16 Bcd2DataToInt(uchar *Ptr)
{
   return(  (u16)OneByteBcdToHex(*Ptr)+
            (u16)OneByteBcdToHex(*(Ptr+1))*100);
}

void IntToData2BCD(u16 value,uchar *point)
{
    value=value%10000;
    *(point+0)=ValueBcdFromHex(value%100);
    *(point+1)=ValueBcdFromHex(value/100);
}


void LongToData3BCD(ulong value,uchar *point)
{ulong l1;
  uchar m,m1,m2;  
  l1=value;
  for(m2=0;m2<3;m2++)
    {
             m=l1%10;
             m1=(l1%100)/10;
            *(point+m2)=(m1<<4)+m;  
            l1=l1/100;
    }  
}
void Byte5BcdPointAdd10(uchar *point,uchar ucAddData)
{

    ulong ulTemp;
    ulTemp=ucAddData;
    ulTemp=ulTemp*10+Bcd5DataToLong(point);
    LongToData5BCD(ulTemp,point);
}

uchar CommCalChksum(uchar *ucStartPoint,uchar ucDataLen)
{
    uchar ucTemp;
    uchar ucReturn;
    
    ucReturn = 0;
    
    for(ucTemp=0;ucTemp<ucDataLen;ucTemp++)
        {
        ucReturn = ucReturn + *(ucStartPoint + ucTemp);
        }
    
    return ucReturn;
}








u16 ValueHexFrom3BcdRam(u16 uiRamAddr)
{
    u16 l;
    l=ValueHexFromBcd(RAM[uiRamAddr]);
    l=l+100*ValueHexFromBcd(RAM[uiRamAddr+1]);
    l=l+10000*ValueHexFromBcd(RAM[uiRamAddr+2]);
    return l;
}


uchar testcuofengshiduan(uchar *point)
{
    uchar l;
    uchar *fp;
    for(l=0;l<8;l++)
    {
        fp=point+2*l;
        if(2!=(TestMinute(*fp)+TestHour(*(fp+1))))
            return 0;
    }
    return 1;
}

//#else
// jiao shi yong 比较时间是否在误差范围内，参数允许误差（秒）， 秒分时日月年pppp

// return 1 true 0  false
// NOTE 10 MINUTE
uchar CompareDateTime(u16 l1,uchar *second,uchar *day)
{
    u16 j1,j2;
    ulong j3,j4,j5,j6;
    if(((ValueHexFromBcd(RSOFT_RTC_YEAR)-ValueHexFromBcd(*(day+2)))<2)||((ValueHexFromBcd(*(day+2))-ValueHexFromBcd(RSOFT_RTC_YEAR))<2))
    {
        j1=ValueHexFromBcd(RSOFT_RTC_YEAR);
        j1=j1*365+(j1+3)/4;
        if(((ValueHexFromBcd(RSOFT_RTC_YEAR))%4)==0)
            j1=j1+table_month29[ValueHexFromBcd(RSOFT_RTC_MONTH)-1];
        else 
            j1=j1+table_month28[ValueHexFromBcd(RSOFT_RTC_MONTH)-1];
        j1=j1+ValueHexFromBcd(RSOFT_RTC_DAY)-1;
        j2=ValueHexFromBcd(*(day+2));
        j2=j2*365+(j2+3)/4;// num day
        if((ValueHexFromBcd(*(day+2))%4)==0)
        {
            j2=j2+table_month29[ValueHexFromBcd(*(day+1))-1];
        }
        else 
        {
            j2=j2+table_month28[ValueHexFromBcd(*(day+1))-1];
        }
        j2=j2+ValueHexFromBcd(*day)-1;// num day
        j3=ValueHexFromBcd(RSOFT_RTC_SECOND);
        j6=(ValueHexFromBcd(RSOFT_RTC_HOUR));
        j3=(ValueHexFromBcd(RSOFT_RTC_MINUTE))*60+j6*3600+j3;
        // num second
        j4=ValueHexFromBcd(*second);
        j6=(ValueHexFromBcd(*(second+2)));
        j4=(ValueHexFromBcd(*(second+1)))*60+j6*3600+j4;
        if(j1>j2)
        {
            j5=j1-j2;// day 
            j3=j3+j5*24*3600;// second
        }
        else 
        {
            j5=j2-j1;//day
            j4=j4+j5*24*3600;// second
        }
        if(j3>j4)
        {
            j5=j3-j4;
        }
        else
        {
            j5=j4-j3;
        }
        if(j5<=l1)
        {
            return 1;
        }
    }
    return 0;
}
/*uchar BcdDataAdd1(uchar *pData)
{
    if( ((*pData)&0xf) < 9)
        (*pData)++;
    else
    {
        (*pData) += 7;
    }
}*/
uchar Data3ByteBCDAdd1(ulong ulAddr)
{
    ulong ulTemp;
    uchar ucTemp[4];
    if(1==ReadDataDirect(ulAddr,  3, &ucTemp[0]))
    {
        ulTemp=(Bcd3DataToLong(&ucTemp[0])+1);
        LongToData3BCD(ulTemp,&ucTemp[0]);
        if(WriteDataDirect(&ucTemp[0], ulAddr,  3))
        {
            return 1;
        }
    }
    return 0;
}

void SetEventStartDataLossVoltagetoAddr(uchar *ucPoint)
// ALL=125BYTE
{
	// TIME
	SetTimeDataToPoint(ucPoint);
	
	// ALL
	memcpy(ucPoint+6, &RAM[RAM_KWH_F_ALL], 5);
	memcpy(ucPoint+11, &RAM[RAM_KWH_R_ALL], 5);
	memcpy(ucPoint+16, &RAM[RAM_KVARH_C1_ALL], 5);
	memcpy(ucPoint+21, &RAM[RAM_KVARH_C2_ALL], 5);
	
	// A
	memcpy(ucPoint+26, &RAM[RAM_KWH_A_F_ALL], 5);
	memcpy(ucPoint+31, &RAM[RAM_KWH_A_R_ALL], 5);
	memcpy(ucPoint+36, &RAM[RAM_KVARH_A_C1_ALL], 5);
	memcpy(ucPoint+41, &RAM[RAM_KVARH_A_C2_ALL], 5);
	SetAPhaseCurrentDataToAddr(ucPoint+46);
	// B
	memcpy(ucPoint+59, &RAM[RAM_KWH_B_F_ALL], 5);
	memcpy(ucPoint+64, &RAM[RAM_KWH_B_R_ALL], 5);
	memcpy(ucPoint+69, &RAM[RAM_KVARH_B_C1_ALL], 5);
	memcpy(ucPoint+74, &RAM[RAM_KVARH_B_C2_ALL], 5);
	SetBPhaseCurrentDataToAddr(ucPoint+79);
	// C
	memcpy(ucPoint+92, &RAM[RAM_KWH_C_F_ALL], 5);
	memcpy(ucPoint+97, &RAM[RAM_KWH_C_R_ALL], 5);
	memcpy(ucPoint+102, &RAM[RAM_KVARH_C_C1_ALL], 5);
	memcpy(ucPoint+107, &RAM[RAM_KVARH_C_C2_ALL], 5);
	SetCPhaseCurrentDataToAddr(ucPoint+112);
}

void SetEventEndDataLossVoltagetoAddr(uchar *ucPoint)
// ALL=86 BYTE
{
    // TIME
    SetTimeDataToPoint(ucPoint);
    
    // ALL
    memcpy(ucPoint+6, &RAM[RAM_KWH_F_ALL], 5);
    memcpy(ucPoint+11, &RAM[RAM_KWH_R_ALL], 5);
    memcpy(ucPoint+16, &RAM[RAM_KVARH_C1_ALL], 5);
    memcpy(ucPoint+21, &RAM[RAM_KVARH_C2_ALL], 5);
    
    // A
    memcpy(ucPoint+26, &RAM[RAM_KWH_A_F_ALL], 5);
    memcpy(ucPoint+31, &RAM[RAM_KWH_A_R_ALL], 5);
	memcpy(ucPoint+36, &RAM[RAM_KVARH_A_C1_ALL], 5);
	memcpy(ucPoint+41, &RAM[RAM_KVARH_A_C2_ALL], 5);
    
    // B
    memcpy(ucPoint+46, &RAM[RAM_KWH_B_F_ALL], 5);
    memcpy(ucPoint+51, &RAM[RAM_KWH_B_R_ALL], 5);
	memcpy(ucPoint+56, &RAM[RAM_KVARH_B_C1_ALL], 5);
	memcpy(ucPoint+61, &RAM[RAM_KVARH_B_C2_ALL], 5);
    
    // C
    memcpy(ucPoint+66, &RAM[RAM_KWH_C_F_ALL], 5);
    memcpy(ucPoint+71, &RAM[RAM_KWH_C_R_ALL], 5);
	memcpy(ucPoint+76, &RAM[RAM_KVARH_C_C1_ALL], 5);
	memcpy(ucPoint+81, &RAM[RAM_KVARH_C_C2_ALL], 5);
    
}
void SetAPhaseCurrentDataToAddr(uchar *ucPoint)
{
    // VOLTAGE
    ucPoint[0]=(RAM[RAM_CURRENT_V_A+2]<<4)+ (RAM[RAM_CURRENT_V_A+1]>>4);
    ucPoint[1]=(RAM[RAM_CURRENT_V_A+3]<<4)+ (RAM[RAM_CURRENT_V_A+2]>>4);
    // CURRENT
    ucPoint[2]=(RAM[RAM_CURRENT_I_A+1]<<4)+ (RAM[RAM_CURRENT_I_A+0]>>4);
    ucPoint[3]=(RAM[RAM_CURRENT_I_A+2]<<4)+ (RAM[RAM_CURRENT_I_A+1]>>4);
    ucPoint[4]=(RAM[RAM_CURRENT_I_A+3]<<4)+ (RAM[RAM_CURRENT_I_A+2]>>4);
    // KW
    ucPoint[5]=RAM[RAM_CURRENT_KW_A+1]; 
    ucPoint[6]=RAM[RAM_CURRENT_KW_A+2]; 
    ucPoint[7]=RAM[RAM_CURRENT_KW_A+3]; 
    // KVAR
    ucPoint[8]=RAM[RAM_CURRENT_KVAR_A+1]; 
    ucPoint[9]=RAM[RAM_CURRENT_KVAR_A+2]; 
    ucPoint[10]=RAM[RAM_CURRENT_KVAR_A+3]; 
    // FACTOR
    ucPoint[11]=RAM[RAM_CURRENT_FACTOR_A+2];
    ucPoint[12]=RAM[RAM_CURRENT_FACTOR_A+3];
}
void SetBPhaseCurrentDataToAddr(uchar *ucPoint)
{
    // VOLTAGE
    ucPoint[0]=(RAM[RAM_CURRENT_V_B+2]<<4)+ (RAM[RAM_CURRENT_V_B+1]>>4);
    ucPoint[1]=(RAM[RAM_CURRENT_V_B+3]<<4)+ (RAM[RAM_CURRENT_V_B+2]>>4);
    // CURRENT
    ucPoint[2]=(RAM[RAM_CURRENT_I_B+1]<<4)+ (RAM[RAM_CURRENT_I_B+0]>>4);
    ucPoint[3]=(RAM[RAM_CURRENT_I_B+2]<<4)+ (RAM[RAM_CURRENT_I_B+1]>>4);
    ucPoint[4]=(RAM[RAM_CURRENT_I_B+3]<<4)+ (RAM[RAM_CURRENT_I_B+2]>>4);
    // KW
    ucPoint[5]=RAM[RAM_CURRENT_KW_B+1]; 
    ucPoint[6]=RAM[RAM_CURRENT_KW_B+2]; 
    ucPoint[7]=RAM[RAM_CURRENT_KW_B+3]; 
    // KVAR
    ucPoint[8]=RAM[RAM_CURRENT_KVAR_B+1]; 
    ucPoint[9]=RAM[RAM_CURRENT_KVAR_B+2]; 
    ucPoint[10]=RAM[RAM_CURRENT_KVAR_B+3]; 
    // FACTOR
    ucPoint[11]=RAM[RAM_CURRENT_FACTOR_B+2];
    ucPoint[12]=RAM[RAM_CURRENT_FACTOR_B+3];
}
void SetCPhaseCurrentDataToAddr(uchar *ucPoint)
{
    // VOLTAGE
    ucPoint[0]=(RAM[RAM_CURRENT_V_C+2]<<4)+ (RAM[RAM_CURRENT_V_C+1]>>4);
    ucPoint[1]=(RAM[RAM_CURRENT_V_C+3]<<4)+ (RAM[RAM_CURRENT_V_C+2]>>4);
    // CURRENT
    ucPoint[2]=(RAM[RAM_CURRENT_I_C+1]<<4)+ (RAM[RAM_CURRENT_I_C+0]>>4);
    ucPoint[3]=(RAM[RAM_CURRENT_I_C+2]<<4)+ (RAM[RAM_CURRENT_I_C+1]>>4);
    ucPoint[4]=(RAM[RAM_CURRENT_I_C+3]<<4)+ (RAM[RAM_CURRENT_I_C+2]>>4);
    // KW
    ucPoint[5]=RAM[RAM_CURRENT_KW_C+1]; 
    ucPoint[6]=RAM[RAM_CURRENT_KW_C+2]; 
    ucPoint[7]=RAM[RAM_CURRENT_KW_C+3]; 
    // KVAR
    ucPoint[8]=RAM[RAM_CURRENT_KVAR_C+1]; 
    ucPoint[9]=RAM[RAM_CURRENT_KVAR_C+2]; 
    ucPoint[10]=RAM[RAM_CURRENT_KVAR_C+3]; 
    // FACTOR
    ucPoint[11]=RAM[RAM_CURRENT_FACTOR_C+2];
    ucPoint[12]=RAM[RAM_CURRENT_FACTOR_C+3];
}


void SetAPhaseDataToRamAddr(u16 uiRamAddr)
{
    // VOLTAGE
    RAM[uiRamAddr+0]=(RAM[RAM_CURRENT_V_A+2]<<4)+ (RAM[RAM_CURRENT_V_A+1]>>4);
    RAM[uiRamAddr+1]=(RAM[RAM_CURRENT_V_A+3]<<4)+ (RAM[RAM_CURRENT_V_A+2]>>4);
    // CURRENT
    RAM[uiRamAddr+2]=(RAM[RAM_CURRENT_I_A+1]<<4)+ (RAM[RAM_CURRENT_I_A+0]>>4);
    RAM[uiRamAddr+3]=(RAM[RAM_CURRENT_I_A+2]<<4)+ (RAM[RAM_CURRENT_I_A+1]>>4);
    RAM[uiRamAddr+4]=(RAM[RAM_CURRENT_I_A+3]<<4)+ (RAM[RAM_CURRENT_I_A+2]>>4);
    // KW
    RAM[uiRamAddr+5]=RAM[RAM_CURRENT_KW_A+1]; // (RAM[RAM_CURRENT_KW_A+1]<<4)+ (RAM[RAM_CURRENT_KW_A+0]>>4);
    RAM[uiRamAddr+6]=RAM[RAM_CURRENT_KW_A+2]; // (RAM[RAM_CURRENT_KW_A+2]<<4)+ (RAM[RAM_CURRENT_KW_A+1]>>4);
    RAM[uiRamAddr+7]=RAM[RAM_CURRENT_KW_A+3]; // (RAM[RAM_CURRENT_KW_A+3]<<4)+ (RAM[RAM_CURRENT_KW_A+2]>>4);
    // KVAR
    RAM[uiRamAddr+8]=RAM[RAM_CURRENT_KVAR_A+1]; // (RAM[RAM_CURRENT_KVAR_A+1]<<4)+ (RAM[RAM_CURRENT_KVAR_A+0]>>4);
    RAM[uiRamAddr+9]=RAM[RAM_CURRENT_KVAR_A+2]; // (RAM[RAM_CURRENT_KVAR_A+2]<<4)+ (RAM[RAM_CURRENT_KVAR_A+1]>>4);
    RAM[uiRamAddr+10]=RAM[RAM_CURRENT_KVAR_A+3]; // (RAM[RAM_CURRENT_KVAR_A+3]<<4)+ (RAM[RAM_CURRENT_KVAR_A+2]>>4);
    // FACTOR
    RAM[uiRamAddr+11]=RAM[RAM_CURRENT_FACTOR_A+2];
    RAM[uiRamAddr+12]=RAM[RAM_CURRENT_FACTOR_A+3];
}
void SetBPhaseDataToRamAddr(u16 uiRamAddr)
{
    // VOLTAGE
    RAM[uiRamAddr+0]=(RAM[RAM_CURRENT_V_B+2]<<4)+ (RAM[RAM_CURRENT_V_B+1]>>4);
    RAM[uiRamAddr+1]=(RAM[RAM_CURRENT_V_B+3]<<4)+ (RAM[RAM_CURRENT_V_B+2]>>4);
    // CURRENT
    RAM[uiRamAddr+2]=(RAM[RAM_CURRENT_I_B+1]<<4)+ (RAM[RAM_CURRENT_I_B+0]>>4);
    RAM[uiRamAddr+3]=(RAM[RAM_CURRENT_I_B+2]<<4)+ (RAM[RAM_CURRENT_I_B+1]>>4);
    RAM[uiRamAddr+4]=(RAM[RAM_CURRENT_I_B+3]<<4)+ (RAM[RAM_CURRENT_I_B+2]>>4);
    // KW
    RAM[uiRamAddr+5]=RAM[RAM_CURRENT_KW_B+1]; // (RAM[RAM_CURRENT_KW_B+1]<<4)+ (RAM[RAM_CURRENT_KW_B+0]>>4);
    RAM[uiRamAddr+6]=RAM[RAM_CURRENT_KW_B+2]; // (RAM[RAM_CURRENT_KW_B+2]<<4)+ (RAM[RAM_CURRENT_KW_B+1]>>4);
    RAM[uiRamAddr+7]=RAM[RAM_CURRENT_KW_B+3]; // (RAM[RAM_CURRENT_KW_B+3]<<4)+ (RAM[RAM_CURRENT_KW_B+2]>>4);
    // KVAR
    RAM[uiRamAddr+8]=RAM[RAM_CURRENT_KVAR_B+1]; // (RAM[RAM_CURRENT_KVAR_B+1]<<4)+ (RAM[RAM_CURRENT_KVAR_B+0]>>4);
    RAM[uiRamAddr+9]=RAM[RAM_CURRENT_KVAR_B+2]; // (RAM[RAM_CURRENT_KVAR_B+2]<<4)+ (RAM[RAM_CURRENT_KVAR_B+1]>>4);
    RAM[uiRamAddr+10]=RAM[RAM_CURRENT_KVAR_B+3]; // (RAM[RAM_CURRENT_KVAR_B+3]<<4)+ (RAM[RAM_CURRENT_KVAR_B+2]>>4);
    // FACTOR
    RAM[uiRamAddr+11]=RAM[RAM_CURRENT_FACTOR_B+2];
    RAM[uiRamAddr+12]=RAM[RAM_CURRENT_FACTOR_B+3];
}
void SetCPhaseDataToRamAddr(u16 uiRamAddr)
{
    // VOLTAGE
    RAM[uiRamAddr+0]=(RAM[RAM_CURRENT_V_C+2]<<4)+ (RAM[RAM_CURRENT_V_C+1]>>4);
    RAM[uiRamAddr+1]=(RAM[RAM_CURRENT_V_C+3]<<4)+ (RAM[RAM_CURRENT_V_C+2]>>4);
    // CURRENT
    RAM[uiRamAddr+2]=(RAM[RAM_CURRENT_I_C+1]<<4)+ (RAM[RAM_CURRENT_I_C+0]>>4);
    RAM[uiRamAddr+3]=(RAM[RAM_CURRENT_I_C+2]<<4)+ (RAM[RAM_CURRENT_I_C+1]>>4);
    RAM[uiRamAddr+4]=(RAM[RAM_CURRENT_I_C+3]<<4)+ (RAM[RAM_CURRENT_I_C+2]>>4);
    // KW
    RAM[uiRamAddr+5]=RAM[RAM_CURRENT_KW_C+1]; // (RAM[RAM_CURRENT_KW_C+1]<<4)+ (RAM[RAM_CURRENT_KW_C+0]>>4);
    RAM[uiRamAddr+6]=RAM[RAM_CURRENT_KW_C+2]; // (RAM[RAM_CURRENT_KW_C+2]<<4)+ (RAM[RAM_CURRENT_KW_C+1]>>4);
    RAM[uiRamAddr+7]=RAM[RAM_CURRENT_KW_C+3]; // (RAM[RAM_CURRENT_KW_C+3]<<4)+ (RAM[RAM_CURRENT_KW_C+2]>>4);
    // KVAR
    RAM[uiRamAddr+8]=RAM[RAM_CURRENT_KVAR_C+1]; // (RAM[RAM_CURRENT_KVAR_C+1]<<4)+ (RAM[RAM_CURRENT_KVAR_C+0]>>4);
    RAM[uiRamAddr+9]=RAM[RAM_CURRENT_KVAR_C+2]; // (RAM[RAM_CURRENT_KVAR_C+2]<<4)+ (RAM[RAM_CURRENT_KVAR_C+1]>>4);
    RAM[uiRamAddr+10]=RAM[RAM_CURRENT_KVAR_C+3]; // (RAM[RAM_CURRENT_KVAR_C+3]<<4)+ (RAM[RAM_CURRENT_KVAR_C+2]>>4);
    // FACTOR
    RAM[uiRamAddr+11]=RAM[RAM_CURRENT_FACTOR_C+2];
    RAM[uiRamAddr+12]=RAM[RAM_CURRENT_FACTOR_C+3];
}

// status: 事件已发生标识；
// status_use: 之前的事件状态；
// continue_time: 事件已延时的时间；
// value: 要求延时的时间；
// input_status: 当前事件触发状态
/*
    该函数主要用来做状态切换。
    *status:        当前事件的稳态
    *status_use:    上一次的瞬时状态，或计时中的状态
    *continue_time: "status_use"的持续时间
    value:          事件稳态切换要求延时的时间
    input_status:   当前事件的即时状态
    
    Return: 0:  The related status isn't changed
            1:  The related status is changed
*/
uchar TranslateStatus0or1(uchar *status,uchar *status_use,uchar *continue_time,uchar value,uchar input_status)
{
        uchar l;
    //目前状态只支持0、1两种状态，大于则无效
        if (input_status>1)
        {
                *continue_time=0;
                return 0;
        }
        l=0;
        // 状态发生改变，重新计时
        if(*status_use!=input_status)
        {
                *status_use=input_status;
                *continue_time=0;
        }
    // 延时时间未到，继续延时等待
        if(*continue_time<=value)
                *continue_time=*continue_time+1;

    // 延时时间满足，则如果稳态和当前状态不同，则切换，并返回1
        if(*continue_time>=value)
        {
                *continue_time=0;
                if(*status!=input_status)
                        l=1;
                *status=input_status;
        }
        return l;
}
uchar TranslateStatusCommon(uchar *status,uchar *status_use,uchar *continue_time,uchar value,uchar input_status);
uchar TranslateStatusCommon(uchar *status,uchar *status_use,uchar *continue_time,uchar value,uchar input_status)
{
    uchar l;
    //目前状态只支持0、1两种状态，大于则无效
    if (input_status>1)
    {
        *continue_time=0;
        return 0;
    }
    l=0;
    
    // 状态发生改变，重新计时
    if(*status_use!=input_status)
    {
        *status_use=input_status;
        *continue_time=0;
    }
    // 延时时间未到，继续延时等待
    if(*continue_time<=value)
        *continue_time=*continue_time+1;

    // 延时时间满足，则如果稳态和当前状态不同，则切换，并返回1
    if(*continue_time>=value)
    {
        *continue_time=0;
        if(*status!=input_status)
            l=1;
        *status=input_status;
    }
    return l;
}
// 从给定时间开始，一天一天往前搜索
void PerDayFromPoint(uchar *ucPDay)
// AA  +0= day   AA
// AA  +1= month  AA
// AA  +2= year  AA
{
    uchar a,b;
    b=OneByteBcdToHex(*(ucPDay+0));
    if(b>1)
    {
        *(ucPDay+0)=OneByteHexToBcd(b-1);
        return ;
    }
    switch(*(ucPDay+1))
    {
        case 0x5:
        case 0x7:
        case 0x10:
        case 0x12: 
            *(ucPDay+1)=OneByteHexToBcd(OneByteBcdToHex(*(ucPDay+1))-1);
            *(ucPDay+0)=0x30;
            break;
        case 0x02:
        case 0x04:
        case 0x06:
        case 0x08:
        case 0x09:
        case 0x11:
            *(ucPDay+1)=*(ucPDay+1)-1;
            *(ucPDay+0)=0x31;
            break;
        case 0x01:
            *(ucPDay+2)=OneByteHexToBcd(OneByteBcdToHex(*(ucPDay+2))-1);
            *(ucPDay+1)=0x12;
            *(ucPDay+0)=0x31;
            break;
        case 0x03:
            a=OneByteBcdToHex(*(ucPDay+2));
            a=a%4;
            if(a==0)    
            {
                *(ucPDay+0)=0x29;
            }
            else
            {
                *(ucPDay+0)=0x28;
            }
            *(ucPDay+1)=0x02;
            break;
        default:
            break;
    }
}

void NextDayFromPoint(uchar *ucPDay)
// AA  +0= day   AA
// AA  +1= month  AA
// AA  +2= year  AA
{
    uchar a,b;
    b=OneByteHexToBcd(OneByteBcdToHex(*(ucPDay+0))+1);
    switch(*(ucPDay+1))
    {
        case 0x1:
        case 0x3:
        case 0x5:
        case 0x7:
        case 0x8:
        case 0x10:
        case 0x12: 
            if(b>0x31)
            {
                *(ucPDay+0)=1;
                *(ucPDay+1)=*(ucPDay+1)+1;
                if(*(ucPDay+1)>0x12)
                {
                    *(ucPDay+2)=OneByteHexToBcd(OneByteBcdToHex(*(ucPDay+2))+1);
                    *(ucPDay+1)=0x01;
                }
            }
            else
            {
                *(ucPDay+0)=b;
            }
            break;
        case 0x4:
        case 0x6:
        case 0x9:
        case 0x11: 
            if (b>0x30)
            {
                *(ucPDay+0)=1;
                b=*(ucPDay+1)+1;
                a=b&0x0f;
                if(a>9) 
                    *(ucPDay+1)=0x10;
                else 
                    *(ucPDay+1)=b;
            }
            else 
                *(ucPDay+0)=b;
            break;
        case 0x2:
            a=OneByteBcdToHex(*(ucPDay+2));
            a=a%4;
            if(a==0)    
            {
                if(b>0x29)
                {
                    *(ucPDay+0)=1;
                    *(ucPDay+1)=*(ucPDay+1)+1;
                }
                else 
                    *(ucPDay+0)=b;
            }
            else
            {
                if(b>0x28)
                {
                    *(ucPDay+0)=1;
                    *(ucPDay+1)=*(ucPDay+1)+1;
                }
                else 
                    *(ucPDay+0)=b;
            }
            break;  
        }
}

// 清历史记录，此处根据二次表只清次数，不清指针。
// ucType=1  工厂内总清，包括清电表清零事件、时钟和电量出错事件
// ucType=0  工厂外总清，不包括清电表清零事件、时钟和电量出错事件
void EventDataTotalClr(uchar ucType)
{
    uchar ucBlockName;
    uchar ucLens;
        
    for(ucBlockName=0;ucBlockName<GAL_TWOTABLE_LEN;ucBlockName++)
    {
        if((ucType ==0)&&((ucBlockName==TYPE_PROGRAM_METERCLR_RECORD)
            ||(ucBlockName==TYPE_ERR_TIME_RECORD)
            ||(ucBlockName==TYPE_ERR_POWER_RECORD)))
            continue;
        if(ucBlockName == TYPE_FREEZE_HOURTIME_RECORD)
            ucLens = 2;
        else
            ucLens = 1;
        WriteDataDirect(&Wr_data[0],EPL_TWOTABLE_ADDR_START+ucBlockName*2+ucLens,ucLens);
    }
}


// 总清
uchar EventAllDataClr(uchar ucType)
{
    ulong TempAddr;
    
    memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
    // AA  铜损铁损计算尾数  AA 
    WriteDataDirect(&Wr_data[0], EPL_KWH_RESIDUE_LOST_COPPER_IRON_START, 32 );
    // AA  安培小时数  AA
    APHourClr();
    
    //   二次表数据 ，主要是记录次数
    EventDataTotalClr(ucType);
    
    //---------------------- AA   累计统计数据 AA-------------------
    // 内部电池工作时间只允许在厂内清零
    if(GAL_YES==ucType)
    {
        WriteDataDirect(&Wr_data[0],EPL_CURRENT_BAT_USETIME,4);
        // 清复位统计次数
        /*uiPINRSTCounterClr;
        uiPORRSTCounterClr;
        uiSFTRSTCounterClr;
        uiIWDGRSTCounterClr;
        uiWWDGRSTCounterClr;
        uiLPWRRSTCounterClr;*/
        uiTaskStartCounterClr;
        uiPowerOnCounterClr;
        uiPowerOffCounterClr;
    }
    // 事件次数
    if(GAL_YES==ucType)
    {
        WriteDataDirect(&Wr_data[0], EPL_TOTAL_DATA_START, 72);
    }
    else
    {
        WriteDataDirect(&Wr_data[0], EPL_TOTAL_DATA_START, 4);
        WriteDataDirect(&Wr_data[0], EPL_CLR_DEMAND_COUNT, 64);
    }
    ClearWatchDog();
    // 电压监控数据和 电网事件总累计时间
    WriteDataDirect(&Wr_data[0], EPL_VOLTAGE_ALL_MONITOR_STAT_BLOCK_START, 236);

    memset(&RAM[RAM_VOLTAGE_ALL_MONITOR_STAT_BLOCK_START],0x00,236);
    
    // 电网事件总累计次数
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_LOSS_V_BLOCK_ALL_START, 216);
    
    ClearWatchDog();
    if(GAL_YES==ucType)
    {
        WriteDataDirect(&Wr_data[0], EPL_TOTAL_CLR_KWH_COUNT, 16);
    }   

    // 预付费部分操作次数
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_PROGRAM_DAYTABLE_MODULE_COUNT, 29);
    // 密码部分
    WriteDataDirect(&Wr_data[0], EPL_PASSWORD_ERR_COUNT_START, 33);
    memset(&RAM[RAM_PASSWORD_ERR_COUNT_START],0x00,33);
    ClearWatchDog();
    // 广播校时时间
    WriteDataDirect(&Wr_data[0], EPL_LAST_CHANNELS01_BROADCASTTIME, 6*3);
    // 清编程事件记录状态
    ProgramPointSet(0);
    ClearWatchDog();

    // 清负荷记录部分记录信息---ybf 修改  2010.08.06
    WriteDataDirect(&Wr_data[0], EPL_RECORD_LASTTIME_START, 13);    // 最近记录时间和指针清0
    WriteDataDirect(&Wr_data[0], EPL_RECORD_SECTOR_STATUS, 256);     // 清flash每个sector的状态
    SetRecordStatusPointStart(0);
    SetRecordStatusPointEnd(0);
    SetRecordStatusLastTime(0);
    ClearWatchDog();
    //擦除负荷记录第一个Block   
    if(isFlashBusy)
    {
        WaitFlashFree(ucProgramFlashWait);
    }
    TempAddr = RecordChangePointtoAddr(0);   
    WaitClrFlash(TempAddr);
    ClrFlashMode();

    return 1;
}

// 电表总清
// ucType=1  工厂内总清，包括清电表清零事件、时钟和电量出错事件
// ucType=0  工厂外总清，不包括清电表清零事件、时钟和电量出错事件
uchar MeterAllDataClr(uchar ucType)
{
    KwhAllDataClr();
    ClearWatchDog();
    DemandDataClrAllCurrent();
    ClearWatchDog();
    ClrCurrentADE7758Data(GAL_YES);
    
        CutCurrentInit();
        CutVoltageInit();
        DownVoltageInit();
        LossCurrentInit();
        LossVoltageInit();
        AllLossVoltagePowerOnInit();
        OrderCurrentInit();
        OrderVoltageInit();
        OverCurrentInit();
        OverPowerInit();
        OverVoltageInit();
        ReversePowerInit();
        UnbalanceCurrentInit();
        UnbalanceVoltageInit();
        DemandOverInit();
        OverTotalCosInit();
        AuxPowerPowerOnInit();

    ClearWatchDog();
    EventAllDataClr(ucType);
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
    ClearPrepay();
#endif
    return 1;
}

uchar EventLossVoltageClr(uchar ucType)
{
    uchar ucTemp;// ,ucTempStart;
    uchar ucTempLen;
    if(0xff==ucType)
        LossVoltageInit();
    memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
    switch(ucType)
    {
        case 0xff:  
            // AA   所有类型都运行   AA
        case 0x00:
            // AA   如果是FF, 则所有都运行,否则只运行00的内容   AA
            memset(&RAM[RAM_TOTAL_LOSS_V_TIME_TOTAL],0x00,3*4);
            WriteDataDirect(&Wr_data[0], EPL_TOTAL_LOSS_V_TIME_TOTAL, 3*4);
            WriteDataDirect(&Wr_data[0], EPL_TOTAL_LOSS_V_BLOCK_ALL_START, 28);
            if(0x00 == ucType)
            {
                break;
            }
        case 0x01:
        case 0x02:
        case 0x03:
        case 0x04:
        case 0x05:
        case 0x06:
        case 0x07:
            if(0xff != ucType)
            {
                ucTempLen=1;
                ucType--;
            }
            else
            {
                ucTempLen=7;
                ucType=0;
            }
            //RAM CLR
            for(ucTemp=0;ucTemp<ucTempLen;ucTemp++)
            {
                WriteDataDirect(&Wr_data[0], EPL_APHOUR_LOSS_V_START+ucType*6, 6);
                WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_LOSS_A_VOLTAGE_RECORD+2*ucType+1, 1);
                ucType++;
            }
            
            break;
    }
    return 1;
}
uchar EventDownVoltageClr(uchar ucType)
{
    uchar ucTemp; // ,ucTempStart;
    uchar ucTempLen;
    if(0xff==ucType)
        DownVoltageInit();
    memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
    switch(ucType)
    {
        case 0xff:  
            // AA   所有类型都运行   AA
        case 0x00:
            // AA   如果是FF, 则所有都运行,否则只运行00的内容   AA
            memset(&RAM[RAM_TOTAL_DOWN_AV_TIME_TOTAL],0x00,3*3);
            WriteDataDirect(&Wr_data[0], EPL_TOTAL_DOWN_AV_TIME_TOTAL, 3*3);
            WriteDataDirect(&Wr_data[0], EPL_TOTAL_DOWN_V_BLOCK_ALL_START, 12);
            if(0x00 == ucType)
            {
                break;
            }
        case 0x01:
        case 0x02:
        case 0x03:
            if(0xff != ucType)
            {
                ucTempLen=1;
                ucType--;
            }
            else
            {
                ucTempLen=3;
                ucType=0;
            }
            //RAM CLR
            for(ucTemp=0;ucTemp<ucTempLen;ucTemp++)
            {
                WriteDataDirect(&Wr_data[0], EPL_APHOUR_DOWN_V_START+ucType*6, 6);
                WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_DOWN_A_VOLTAGE_RECORD+2*ucType+1, 1);
                ucType++;
            }
            
            break;
    }   
    return 1;
}

uchar EventOverVoltageClr(uchar ucType)
{
    uchar ucTemp; // ,ucTempStart;
    uchar ucTempLen;
    if(0xff==ucType)
        OverVoltageInit();
    memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
    switch(ucType)
    {
        case 0xff:  
            // AA   所有类型都运行   AA
        case 0x00:
            // AA   如果是FF, 则所有都运行,否则只运行00的内容   AA
            memset(&RAM[RAM_TOTAL_OVER_AV_TIME_TOTAL],0x00,3*3);
            WriteDataDirect(&Wr_data[0], EPL_TOTAL_OVER_AV_TIME_TOTAL, 3*3);
            WriteDataDirect(&Wr_data[0], EPL_TOTAL_OVER_V_BLOCK_ALL_START, 12);
            if(0x00 == ucType)
            {
                break;
            }
        case 0x01:
        case 0x02:
        case 0x03:
            if(0xff != ucType)
            {
                ucTempLen=1;
                ucType--;
            }
            else
            {
                ucTempLen=3;
                ucType=0;
            }
            //RAM CLR
            for(ucTemp=0;ucTemp<ucTempLen;ucTemp++)
            {
                WriteDataDirect(&Wr_data[0], EPL_APHOUR_OVER_V_START+ucType*6, 6);
                WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_OVER_A_VOLTAGE_RECORD+2*ucType+1, 1);
                ucType++;
            }
            
            break;
    }

    return 1;
}

uchar EventCutVoltageClr(uchar ucType)
{
    uchar ucTemp; // ,ucTempStart;
    uchar ucTempLen;
    if(0xff==ucType)
        CutVoltageInit();
    memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
    switch(ucType)
    {
        case 0xff:  
            // AA   所有类型都运行   AA
        case 0x00:
            // AA   如果是FF, 则所有都运行,否则只运行00的内容   AA
            memset(&RAM[RAM_TOTAL_CUT_AV_TIME_TOTAL],0x00,3*3);
            WriteDataDirect(&Wr_data[0], EPL_TOTAL_CUT_AV_TIME_TOTAL, 3*3);
            WriteDataDirect(&Wr_data[0], EPL_TOTAL_CUT_V_BLOCK_ALL_START, 12);
            if(0x00 == ucType)
            {
                break;
            }
        case 0x01:
        case 0x02:
        case 0x03:
            if(0xff != ucType)
            {
                ucTempLen=1;
                ucType--;
            }
            else
            {
                ucTempLen=3;
                ucType=0;
            }
            for(ucTemp=0;ucTemp<ucTempLen;ucTemp++)
            {
                WriteDataDirect(&Wr_data[0], EPL_APHOUR_CUT_V_START+ucType*6, 6);
                WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_CUT_A_VOLTAGE_RECORD+2*ucType+1, 1);
                ucType++;
            }
            
            break;
    }
    return 1;
}


uchar EventAllLossVoltageClr(uchar ucType)
{
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], RAM_ALLLOSS_VOLTAGE_COUNT, 6);
        WriteDataDirect(&Wr_data[0], EPL_ALLLOSS_VOLTAGE_COUNT, 6);
        ClearWatchDog();
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_LOSS_ALL_VOLTAGE_RECORD+2*0+1, 1);
        AllLossVoltageInit();
    }
    //FLASH CLR
    return 1;
}
uchar EventAuxPowerClr(uchar ucType)
{
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], RAM_ACPOWER_LOSS_COUNT, 6);
        WriteDataDirect(&Wr_data[0], EPL_ACPOWER_LOSS_COUNT, 6);
        
        ClearWatchDog();
        //FLASH CLR
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_ACPOWER_LOSS_RECORD+2*0+1, 1);
        AuxPowerInit();
    }
    return 1;
}

uchar EventOrderVoltageClr(uchar ucType)
{
//  uchar ucTemp;
    if((0x00==ucType)||(0xff==ucType))
    {
        
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_TOTAL_ORDER_VOLTAGE_BLOCK_START, 4);
        memset(&RAM[RAM_TOTAL_ORDER_VOLTAGE_TIME_TOTAL],0x00,3);
        WriteDataDirect(&Wr_data[0], EPL_TOTAL_ORDER_VOLTAGE_TIME_TOTAL, 3);
        
        ClearWatchDog();
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_ORDER_VOLTAGE_RECORD+2*0+1, 1);
        //FLASH CLR
        OrderVoltageInit();
    }
    return 1;
}
uchar EventOrderCurrentClr(uchar ucType)
{
    if((0x00==ucType)||(0xff==ucType))
    {
        
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_TOTAL_ORDER_CURRENT_BLOCK_START, 4);
        memset(&RAM[RAM_TOTAL_ORDER_CURRENT_TIME_TOTAL],0x00,3);
        WriteDataDirect(&Wr_data[0], EPL_TOTAL_ORDER_CURRENT_TIME_TOTAL, 3);
        
        ClearWatchDog();
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_ORDER_CURRENT_RECORD+2*0+1, 1);
        //FLASH CLR
        OrderCurrentInit();
    }
    return 1;
}
uchar EventUnbalanceVoltageClr(uchar ucType)
{
//  uchar ucTemp;
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_TOTAL_UNBALANCE_VOLTAGE_BLOCK_START, 4);
        memset(&RAM[RAM_TOTAL_UNBALANCE_VOLTAGE_TIME_TOTAL],0x00,3);
        WriteDataDirect(&Wr_data[0], EPL_TOTAL_UNBALANCE_VOLTAGE_TIME_TOTAL, 3);
        
        ClearWatchDog();
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_UNBALANCE_VOLTAGE_RECORD+2*0+1, 1);
        UnbalanceVoltageInit();
    }
    return 1;
}
uchar EventUnbalanceCurrentClr(uchar ucType)
{
// uchar ucTemp;
    if((0x00==ucType)||(0xff==ucType))
    {
        //RAM CLR
        
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_TOTAL_UNBALANCE_CURRENT_BLOCK_START, 4);
        memset(&RAM[RAM_TOTAL_UNBALANCE_CURRENT_TIME_TOTAL],0x00,3);
        WriteDataDirect(&Wr_data[0], EPL_TOTAL_UNBALANCE_CURRENT_TIME_TOTAL, 3);
        
        ClearWatchDog();
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_UNBALANCE_CURRENT_RECORD+2*0+1, 1);
        UnbalanceCurrentInit();
    }
    return 1;
}

uchar EventLossCurrentClr(uchar ucType)
{
    uchar ucTemp; // ,ucTempStart;
    uchar ucTempLen;
    if(0xff==ucType)
        LossCurrentInit();
    memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
    switch(ucType)
    {
        case 0xff:  
            // AA   所有类型都运行   AA
        case 0x00:
            // AA   如果是FF, 则所有都运行,否则只运行00的内容   AA
            memset(&RAM[RAM_TOTAL_LOSS_AI_TIME_TOTAL],0x00,3*3);
            WriteDataDirect(&Wr_data[0], EPL_TOTAL_LOSS_AI_TIME_TOTAL, 3*3);
            WriteDataDirect(&Wr_data[0], EPL_TOTAL_LOSS_I_BLOCK_ALL_START, 12);
            if(0x00 == ucType)
            {
                break;
            }
        case 0x01:
        case 0x02:
        case 0x03:
        case 0x04:
        case 0x05:
        case 0x06:
        case 0x07:
            if(0xff != ucType)
            {
                ucTempLen=1;
                ucType--;
            }
            else
            {
                ucTempLen=7;
                ucType=0;
            }
            //RAM CLR
            for(ucTemp=0;ucTemp<ucTempLen;ucTemp++)
            {
                WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_LOSS_A_CURRENT_RECORD+2*ucType+1, 1);
                ucType++;
            }
            
            break;
    }   
    return 1;
}

uchar EventOverCurrentClr(uchar ucType)
{
    uchar ucTemp; // ,ucTempStart;
    uchar ucTempLen;
    if(0xff==ucType)
        OverCurrentInit();
    memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
    switch(ucType)
    {
        case 0xff:  
            // AA   所有类型都运行   AA
        case 0x00:
            // AA   如果是FF, 则所有都运行,否则只运行00的内容   AA
            memset(&RAM[RAM_TOTAL_OVER_AI_TIME_TOTAL],0x00,3*3);
            WriteDataDirect(&Wr_data[0], EPL_TOTAL_OVER_AI_TIME_TOTAL, 3*3);
            WriteDataDirect(&Wr_data[0], EPL_TOTAL_OVER_I_BLOCK_ALL_START, 12);
            if(0x00 == ucType)
            {
                break;
            }
        case 0x01:
        case 0x02:
        case 0x03:
            if(0xff != ucType)
            {
                ucTempLen=1;
                ucType--;
            }
            else
            {
                ucTempLen=3;
                ucType=0;
            }
            //RAM CLR
            for(ucTemp=0;ucTemp<ucTempLen;ucTemp++)
            {
                
                WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_OVER_A_CURRENT_RECORD+2*ucType+1, 1);
                ucType++;
            }
            break;
            
    }
    return 1;
}
uchar EventCutCurrentClr(uchar ucType)
{
    uchar ucTemp; // ,ucTempStart;
    uchar ucTempLen;
    if(0xff==ucType)
        CutCurrentInit();
    memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
    switch(ucType)
    {
        case 0xff:  
            // AA   所有类型都运行   AA
        case 0x00:
            // AA   如果是FF, 则所有都运行,否则只运行00的内容   AA
            memset(&RAM[RAM_TOTAL_CUT_AI_TIME_TOTAL],0x00,3*3);
            WriteDataDirect(&Wr_data[0], EPL_TOTAL_CUT_AI_TIME_TOTAL, 3*3);
            WriteDataDirect(&Wr_data[0], EPL_TOTAL_CUT_I_BLOCK_ALL_START, 12);
            if(0x00 == ucType)
            {
                break;
            }
        case 0x01:
        case 0x02:
        case 0x03:
            if(0xff != ucType)
            {
                ucTempLen=1;
                ucType--;
            }
            else
            {
                ucTempLen=3;
                ucType=0;
            }
            for(ucTemp=0;ucTemp<ucTempLen;ucTemp++)
            {
                
                WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_CUT_A_CURRENT_RECORD+2*ucType+1, 1);
                ucType++;
            }
            break;
    }
    return 1;
}
uchar EventReversePowerClr(uchar ucType)
{
    uchar ucTemp; // ,ucTempStart;
    uchar ucTempLen;
    if(0xff==ucType)
        ReversePowerInit();
    memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
    switch(ucType)
    {
        case 0xff:  
            // AA   所有类型都运行   AA
        case 0x00:
            // AA   如果是FF, 则所有都运行,否则只运行00的内容   AA
            memset(&RAM[RAM_TOTAL_REVERSE_ALL_TIME_TOTAL],0x00,3*4);
            WriteDataDirect(&Wr_data[0], EPL_TOTAL_REVERSE_ALL_TIME_TOTAL, 3*4);
            WriteDataDirect(&Wr_data[0], EPL_TOTAL_REVERSE_ALL_BLOCK_START, 16);
            if(0x00 == ucType)
            {
                break;
            }
        case 0x01:
        case 0x02:
        case 0x03:
            if(0xff != ucType)
            {
                ucTempLen=1;
            }
            else
            {
                ucTempLen=4;
                ucType=0;
            }
            for(ucTemp=0;ucTemp<ucTempLen;ucTemp++)
            {
                WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_REVERSEPOWER_ALL_RECORD+2*ucType+1, 1);
                ucType++;
            }
            break;
    }
    return 1;
}

uchar EventOverPowerClr(uchar ucType)
{
    uchar ucTemp; // ,ucTempStart;
    uchar ucTempLen;
    if(0xff==ucType)
        OverPowerInit();
    memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
    switch(ucType)
    {
        case 0xff:  
            // AA   所有类型都运行   AA
        case 0x00:
            // AA   如果是FF, 则所有都运行,否则只运行00的内容   AA
            memset(&RAM[RAM_TOTAL_POWEROVER_ALL_TIME_TOTAL],0x00,3*4);
            WriteDataDirect(&Wr_data[0], EPL_TOTAL_POWEROVER_ALL_TIME_TOTAL, 3*4);
            WriteDataDirect(&Wr_data[0], EPL_TOTAL_POWEROVER_ALL_BLOCK_START, 16);
            if(0x00 == ucType)
            {
                break;
            }
        case 0x01:
        case 0x02:
        case 0x03:
            if(0xff != ucType)
            {
                ucTempLen=1;
            }
            else
            {
                ucTempLen=4;
                ucType=0;
            }
            for(ucTemp=0;ucTemp<ucTempLen;ucTemp++)
            {
                WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_POWEROVER_ALL_RECORD+2*ucType+1, 1);
                ucType++;
            }
            break;
    }
    return 1;
}
uchar EventRelayOpenClr(uchar ucType)
{
    memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
    if((0x00==ucType)||(0xff==ucType))
    {
        WriteDataDirect(&Wr_data[0], EPL_TOTAL_RELAY_OPEN_COUNT, 6);
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_RELAY_OPEN_RECORD+2*0+1, 1);
    }
    return 1;
}
uchar EventRelayCloseClr(uchar ucType)
{
    memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
    if((0x00==ucType)||(0xff==ucType))
    {
        WriteDataDirect(&Wr_data[0], EPL_TOTAL_RELAY_CLOSE_COUNT, 6);
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_RELAY_CLOSE_RECORD+2*0+1, 1);
    }
    return 1;
}
uchar EventOverTotalCosClr(uchar ucType)
{
// uchar ucTemp;
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_TOTAL_OVERTOTALCOS_BLOCK_START, 4);
        memset(&RAM[RAM_TOTAL_OVERTOTALCOS_TIME_TOTAL],0x00,3);
        WriteDataDirect(&Wr_data[0], EPL_TOTAL_OVERTOTALCOS_TIME_TOTAL, 3);
        
        ClearWatchDog();
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_OVERTOTALCOS_RECORD+2*0+1, 1);
        OverTotalCosInit();
    }
    return 1;
}
uchar EventBroadCastTimeClr(uchar ucType)
{
// uchar ucTemp;
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_TOTAL_BROADCASTTIME_COUNT, 6);
        
        ClearWatchDog();
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_BROADCASTTIME_RECORD+2*0+1, 1);
    }
    return 1;
}
uchar EventMoniterClr(uchar ucType)
{
    uchar ucTemp;
    uchar ucTempLen;
    if(0xff==ucType)
        MoniterInit();
    memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
    switch(ucType)
    {
        case 0xff:  
            // AA   所有类型都运行   AA
        case 0x00:
            // AA   如果是FF, 则所有都运行,否则只运行00的内容   AA
            memset(&RAM[RAM_VOLTAGE_ALL_MONITOR_STAT_BLOCK_START],0x00,3);
            WriteDataDirect(&Wr_data[0], EPL_VOLTAGE_ALL_MONITOR_STAT_BLOCK_START, 3);
        case 0x01:
        case 0x02:
        case 0x03:
            if(0xff != ucType)
            {
                ucTempLen=1;
            }
            else
            {
                ucTempLen=4;
                ucType=0;
            }
            for(ucTemp=0;ucTemp<ucTempLen;ucTemp++)
            {
                WriteDataDirect(&Wr_data[0], EPL_VOLTAGE_ALL_MONITOR_TIME+ucType*27, 27);
                memset( &RAM[RAM_VOLTAGE_ALL_MONITOR_TIME+ucType*27],0x00, 27);
                WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_MONITOR_VOLTAGE_ALL_RECORD+2*ucType+1, 1);
                ucType++;
            }
            break;
    }   
    return 1;
}
uchar EventPowerOffClr(uchar ucType)
{
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_POWER_DOWN_COUNT, 4);
        
        ClearWatchDog();
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_POWER_DOWN_RECORD+2*0+1, 1);
    }
    FLG_SYSTEMPOWER_STATUS=GAL_NO;
    fPowerDownStatusClr;
    return 1;
}
uchar EventDemandOverClr(uchar ucType)
{
    uchar ucTemp;
    uchar ucTempLen;
    if(0xff==ucType)
        DemandOverInit();
    memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
    switch(ucType)
    {
        case 0xff:  
            // AA   所有类型都运行   AA
        case 0x00:
            // AA   如果是FF, 则所有都运行,否则只运行00的内容   AA
            WriteDataDirect(&Wr_data[0], EPL_DEMAND_OVER_BLOCK_START, 32);
            if(0x00 == ucType)
            {
                break;
            }
        case 0x01:
        case 0x02:
        case 0x03:
        case 0x04:
        case 0x05:
        case 0x06:
        case 0x07:
        case 0x08:
            if(0xff != ucType)
            {
                ucTempLen=1;
                ucType--;
            }
            else
            {
                ucTempLen=8;
                ucType=0;
            }
            for(ucTemp=0;ucTemp<ucTempLen;ucTemp++)
            {
                WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_DEMAND_OVER_KW_F_RECORD+2*ucType+1, 1);
                ucType++;
            }
            break;
    }
    return 1;
}

uchar EventProgramRecordClr(uchar ucType)
{
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_PROGRAM_COUNT, 4);
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_PROGRAM_RECORD+2*0+1, 1);
        ProgramPointSet(0);
    }
    return 1;
}

uchar EventProgramPowerClrRecordClr(uchar ucType)
{
//  uchar ucTemp;
#if 0
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_CLR_METER_COUNT, 4);
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_PROGRAM_METERCLR_RECORD+2*0, 2);
//      for(ucTemp=0;ucTemp<144;ucTemp++)
//      {
//          WriteDataDirect(&Wr_data[0], FL1_LAST_PROGRAM_POWERCLR_RECORD_START+512*ucTemp, 512);
//          ClearWatchDog();
//      }
    }
#endif
    return 1;
}
uchar EventProgramDemandClrRecordClr(uchar ucType)
{
//  u16 ucTemp;
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_CLR_DEMAND_COUNT, 4);
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_PROGRAM_DEMANDCLR_RECORD+2*0+1, 1);
    }
    return 1;
}

uchar EventProgramEventClrRecordClr(uchar ucType)
{
#if 0   
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_CLR_EVENT_COUNT, 4);
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_PROGRAM_EVENTCLR_RECORD+2*0, 2);
        // WriteDataDirect(&Wr_data[0], FL1_LAST_PROGRAM_EVENTCLR_RECORD_START+512*0, 512);

    }
#endif
    return 1;
}

uchar EventProgramTimeRecordClr(uchar ucType)
{
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_PROGRAM_TIME_COUNT, 4);
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_PROGRAM_TIME_RECORD+2*0+1, 1);
    }
    return 1;
}

uchar EventProgramDayTableRecordClr(uchar ucType)
{
//  uchar ucTemp;
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_PROGRAM_PERIOD_COUNT, 4);
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_PROGRAM_DAYTABLE_RECORD+2*0+1, 1);
    }
    return 1;
}
uchar EventProgramSeasonTableRecordClr(uchar ucType)
{
//  uchar ucTemp;
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_PROGRAM_SEASON_COUNT, 4);
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_PROGRAM_SEASON_RECORD+2*0+1, 1);
    }
    return 1;
}
uchar EventProgramCharacterRestRecordClr(uchar ucType)
{
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_PROGRAM_CHARACTER_REST_COUNT, 4);
                
        ClearWatchDog();
        //FLASH CLR
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_PROGRAM_RESTDAY_RECORD+2*0+1, 1);
        ClearWatchDog();
    }
    return 1;
}

uchar EventProgramHolidayRecordClr(uchar ucType)
{
//  uchar ucTemp;
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_PROGRAM_PUBLIC_HOLIDAY_COUNT, 4);
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_PROGRAM_HOLIDAY_RECORD+2*0+1, 1);
    }
    return 1;
}
uchar EventProgramCharacterActiveRecordClr(uchar ucType)
{
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_PROGRAM_ACTIVE_COM_COUNT, 4);
                
        ClearWatchDog();
        //FLASH CLR
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_PROGRAM_CHARACTER_ACTIVE_RECORD+2*0+1, 1);
        ClearWatchDog();
    }
    return 1;
}

uchar EventProgramCharacterReActive01RecordClr(uchar ucType)
{
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_PROGRAM_REACTIVE1_COM_COUNT, 4);
                
        ClearWatchDog();
        //FLASH CLR
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_PROGRAM_CHARACTER_REACTIVE01_RECORD+2*0+1, 1);
        ClearWatchDog();
    }
    return 1;
}

uchar EventProgramCharacterReActive02RecordClr(uchar ucType)
{
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_PROGRAM_REACTIVE2_COM_COUNT, 4);
                
        ClearWatchDog();
        //FLASH CLR
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_PROGRAM_CHARACTER_REACTIVE02_RECORD+2*0+1, 1);
        ClearWatchDog();
    }
    return 1;
}

uchar EventProgramBalanceDayRecordClr(uchar ucType)
{
//  uchar ucTemp;
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_PROGRAM_BALANCE_DAY_COUNT, 4);
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_PROGRAM_BALANCE_DAY_RECORD+2*0+1, 1);
    }
    return 1;
}


uchar EventBuyMoneyRecordClr(uchar ucType)
{
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, 4);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_BUY_MONEY_RECORD+2*0+1, 1);
    }
    return 1;
}
#if(CONFIG_METER_STEP_PERIODPRICE_MODE==CONFIG_METER_STEP_PERIODPRICE_MODE_ENABLE)
uchar EventBuyKwhRecordClr(uchar ucType)
{
#if 0
    //Acturally, it is no use
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, 4);
        // FM ALL
//      WriteDataDirect(&Wr_data[0], EPL_PROGRAM_BALANCE_DAY_COUNT, 3);
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_BUY_KWH_RECORD+2*0+1, 1);
    }
#endif    
    return 1;
}

#endif


uchar EventCoverOpenClr(uchar ucType)
{
    #if 0
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_TOTAL_COVER_BLOCK_START, 4);
        
        ClearWatchDog();
        //FLASH CLR
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_COVER_OPEN_RECORD+2*0+1, 1);
        FLG_COVER_OPEN_STATUS=GAL_NO;
        fCoverOpenStatusClr;
        ucTempCoverOpenStatusUse=0;
        ucTempCoverOpenContinueTime=0;
    }
    #endif
    return 1;
}
uchar EventTerminalOpenOpenClr(uchar ucType)
{
    #if 0
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_TOTAL_TERMINAL_BLOCK_START, 4);
        
        ClearWatchDog();
        //FLASH CLR
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_TERMINAL_OPEN_RECORD+2*0+1, 1);
        FLG_TERMINAL_OPEN_STATUS=GAL_NO;
        fTerminalOpenStatusClr;
        ucTempTerminalOpenStatusUse=0;
        ucTempTerminalOpenContinueTime=0;
    }
    #endif
    return 1;
}

#if 0
uchar EventProgramOpenOpenClr(uchar ucType)
{
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_TOTAL_PROGRAM_BLOCK_START, 4);
        
        ClearWatchDog();
        //FLASH CLR
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_RELAY_OPEN_RECORD+2*0+1, 1);
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_RELAY_CLOSE_RECORD+2*0+1, 1);
        FLG_PROGRAM_OPEN_STATUS=GAL_NO;
        ucTempProgramOpenStatusUse=0;
        ucTempProgramOpenContinueTime=0;
    }
    return 1;
}
#endif
uchar EventProgramDayTableModuleChangeClr(uchar ucType);
uchar EventProgramDayTableModuleChangeClr(uchar ucType)
{
    if((0x00==ucType)||(0xff==ucType))
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        // FM ALL
        WriteDataDirect(&Wr_data[0], EPL_TOTAL_PROGRAM_DAYTABLE_MODULE_COUNT, 4);
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_DAYTABLE_MODULE_RECORD+2*0+1, 1);

    }
    return 1;
}


typedef  uchar  (*ucFunction)(uchar aa);    
typedef struct
{
    ulong ulCode;
    ucFunction callBack;
    uchar ucCoef;
}ST_METER_EVENT_CLR_PARAM;

const ST_METER_EVENT_CLR_PARAM TB_METER_EVENT_CLR[]=
{
    {0x1000ffff,EventLossVoltageClr,0x00},
    {0x1001ffff,EventLossVoltageClr,0x01},
    {0x1002ffff,EventLossVoltageClr,0x02},
    {0x1003ffff,EventLossVoltageClr,0x03},
    {0x10ffffff,EventLossVoltageClr,0xff},
    
    {0x1101ffff,EventDownVoltageClr,0x01},
    {0x1102ffff,EventDownVoltageClr,0x02},
    {0x1103ffff,EventDownVoltageClr,0x03},
    {0x11ffffff,EventDownVoltageClr,0xff},
    
    {0x1201ffff,EventOverVoltageClr,0x01},
    {0x1202ffff,EventOverVoltageClr,0x02},
    {0x1203ffff,EventOverVoltageClr,0x03},
    {0x12ffffff,EventOverVoltageClr,0xff},
        
    {0x1301ffff,EventCutVoltageClr,0x01},
    {0x1302ffff,EventCutVoltageClr,0x02},
    {0x1303ffff,EventCutVoltageClr,0x03},
    {0x13ffffff,EventCutVoltageClr,0xff},
    
    {0x1400ffff,EventOrderVoltageClr,0x00},
    {0x14ffffff,EventOrderVoltageClr,0xff},
    
    {0x1500ffff,EventOrderCurrentClr,0x00},
    {0x15ffffff,EventOrderCurrentClr,0xff},
    
    {0x1600ffff,EventUnbalanceVoltageClr,0x00},
    {0x16ffffff,EventUnbalanceVoltageClr,0xff},
    
    {0x1700ffff,EventUnbalanceCurrentClr,0x00},
    {0x17ffffff,EventUnbalanceCurrentClr,0xff},

    {0x1801ffff,EventLossCurrentClr,0x01},
    {0x1802ffff,EventLossCurrentClr,0x02},
    {0x1803ffff,EventLossCurrentClr,0x03},
    {0x18ffffff,EventLossCurrentClr,0xff},
    
    {0x1901ffff,EventOverCurrentClr,0x01},
    {0x1902ffff,EventOverCurrentClr,0x02},
    {0x1903ffff,EventOverCurrentClr,0x03},
    {0x19ffffff,EventOverCurrentClr,0xff},
    
    {0x1a01ffff,EventCutCurrentClr,0x01},
    {0x1a02ffff,EventCutCurrentClr,0x02},
    {0x1a03ffff,EventCutCurrentClr,0x03},
    {0x1affffff,EventCutCurrentClr,0xff},
    
    {0x1b01ffff,EventReversePowerClr,0x01},
    {0x1bb2ffff,EventReversePowerClr,0x02},
    {0x1b03ffff,EventReversePowerClr,0x03},
    {0x1bffffff,EventReversePowerClr,0xff},
    
    {0x1c01ffff,EventOverPowerClr,0x01},
    {0x1cb2ffff,EventOverPowerClr,0x02},
    {0x1c03ffff,EventOverPowerClr,0x03},
    {0x1cffffff,EventOverPowerClr,0xff},
    
    {0x1d00ffff,EventRelayOpenClr,0x00},
    {0x1dffffff,EventRelayOpenClr,0xff},
    
    {0x1e00ffff,EventRelayCloseClr,0x00},
    {0x1effffff,EventRelayCloseClr,0xff},
    
    {0x1f00ffff,EventOverTotalCosClr,0x00},
    {0x1fffffff,EventOverTotalCosClr,0xff},
    
#if(CONFIG_METER_TYPE==CONFIG_METER_TYPE_SD39C)
    {0x1f00ffff,EventBroadCastTimeClr,0x00},
    {0x1fffffff,EventBroadCastTimeClr,0xff},
#endif
    {0x030500ff,EventAllLossVoltageClr,0x00},
    {0x0305ffff,EventAllLossVoltageClr,0xff},
    
    {0x030600ff,EventAuxPowerClr,0x00},
    {0x0306ffff,EventAuxPowerClr,0xff},
    
    {0x031000ff,EventMoniterClr,0x00},
    {0x031001ff,EventMoniterClr,0x01},
    {0x031002ff,EventMoniterClr,0x02},
    {0x031003ff,EventMoniterClr,0x03},
    {0x0310ffff,EventMoniterClr,0xff},

    {0x031100ff,EventPowerOffClr,0xff},
    
    {0x031200ff,EventDemandOverClr,0x00},
    {0x031201ff,EventDemandOverClr,0x01},
    {0x031202ff,EventDemandOverClr,0x02},
    {0x031203ff,EventDemandOverClr,0x03},
    {0x031204ff,EventDemandOverClr,0x04},
    {0x031205ff,EventDemandOverClr,0x05},
    {0x031206ff,EventDemandOverClr,0x06},
    {0x031207ff,EventDemandOverClr,0x07},
    {0x031208ff,EventDemandOverClr,0x08},
    {0x0312ffff,EventDemandOverClr,0xff},
    
    {0x033000ff,EventProgramRecordClr,0xff},
#if 0
    //电表清零记录不允许清楚
    {0x033001ff,EventProgramPowerClrRecordClr,0xff},
#endif
    {0x033002ff,EventProgramDemandClrRecordClr,0xff},
    {0x033003ff,EventProgramEventClrRecordClr,0xff},
    {0x033004ff,EventProgramTimeRecordClr,0xff},
    {0x033005ff,EventProgramDayTableRecordClr,0xff},
    {0x033006ff,EventProgramSeasonTableRecordClr,0xff},
    {0x033007ff,EventProgramCharacterRestRecordClr,0xff},
    {0x033008ff,EventProgramHolidayRecordClr,0xff},
    {0x033009ff,EventProgramCharacterActiveRecordClr,0xff},
    {0x03300aff,EventProgramCharacterReActive01RecordClr,0xff},
    {0x03300bff,EventProgramCharacterReActive02RecordClr,0xff},
    {0x03300cff,EventProgramBalanceDayRecordClr,0xff},
    {0x03300dff,EventCoverOpenClr,0xff},
    {0x03300eff,EventTerminalOpenOpenClr,0xff},
    {0x03300fff,EventProgramDayTableModuleChangeClr,0xff},
//  0x033010ff,EventProgramOpenOpenClr,0xff},
    
#if(CONFIG_METER_STEP_PERIODPRICE_MODE==CONFIG_METER_STEP_PERIODPRICE_MODE_ENABLE)
    {0x0332ffff,EventBuyKwhRecordClr,0xff},
    {0x0333ffff,EventBuyMoneyRecordClr,0xff},
#endif  
};
/*
uchar EventRelayOpenCloseClr(uchar ucType);

uchar EventRelayOpenCloseClr(uchar ucType)
{
    
    memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
    if((0x00==ucType)||(0xff==ucType))
    {
        WriteDataDirect(&Wr_data[0], EPL_TOTAL_RELAY_OPEN_COUNT, 6);
    }
    if((0x01==ucType)||(0xff==ucType))
    {
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_RELAY_OPEN_RECORD+2*0, 2);
    }
    if((0x02==ucType)||(0xff==ucType))
    {
        WriteDataDirect(&Wr_data[0], EPL_TWOTABLE_ADDR_START+2*TYPE_RELAY_CLOSE_RECORD+2*0, 2);
    }
    return 1;
    
}
*/
uchar GetEventClrListLens(void);

uchar GetEventClrListLens(void)
{
    return(sizeof(TB_METER_EVENT_CLR)/sizeof(ST_METER_EVENT_CLR_PARAM));
}

uchar EventClrFromCodeCan(ulong ulTCode)
{
    uchar ucTemp;
    uchar ucListCount;
    
    if(0xffffffff==ulTCode)
    {
        return 1;
    }
    else
    {
        ucListCount=GetEventClrListLens();
        for(ucTemp=0;ucTemp<ucListCount;ucTemp++)
        {
            if(TB_METER_EVENT_CLR[ucTemp].ulCode== ulTCode)
            {
                return 1;
            }
        }
    }
    return 0;
}
uchar EventClrFromCode(ulong ulTCode)
{
    uchar ucTemp;
    uchar ucListCount;
    ucListCount=GetEventClrListLens();
    if(0xffffffff==ulTCode)
    {
        for(ucTemp=0;ucTemp<ucListCount;ucTemp++)
        {
            if(0xff==TB_METER_EVENT_CLR[ucTemp].ucCoef)
            {
                TB_METER_EVENT_CLR[ucTemp].callBack(0xff);
            }
        }
        return 1;
    }
    else
    {
        for(ucTemp=0;ucTemp<ucListCount;ucTemp++)
        {
            if(TB_METER_EVENT_CLR[ucTemp].ulCode== ulTCode)
            {
                TB_METER_EVENT_CLR[ucTemp].callBack(TB_METER_EVENT_CLR[ucTemp].ucCoef);
                return 1;
            }
        }
    }
    return 0;
}

void SetTimeDataToPoint(uchar *ucPoint)
{
    *(ucPoint+0)=RSOFT_RTC_SECOND;
    *(ucPoint+1)=RSOFT_RTC_MINUTE;
    *(ucPoint+2)=RSOFT_RTC_HOUR;
    *(ucPoint+3)=RSOFT_RTC_DAY;
    *(ucPoint+4)=RSOFT_RTC_MONTH;
    *(ucPoint+5)=RSOFT_RTC_YEAR;
}
void SetmmhhDDMMYYToPoint(uchar *ucPoint)
{
    *(ucPoint+0)=RSOFT_RTC_MINUTE;
    *(ucPoint+1)=RSOFT_RTC_HOUR;
    *(ucPoint+2)=RSOFT_RTC_DAY;
    *(ucPoint+3)=RSOFT_RTC_MONTH;
    *(ucPoint+4)=RSOFT_RTC_YEAR;
}

void SavemmhhDDMMYYtoAddr(ulong ulTimeAddr)
{
    SetmmhhDDMMYYToPoint(&Wr_data[0]);
    WriteDataDirect(&Wr_data[0], ulTimeAddr, 5);
}

uchar  TimeChangedhhDDMMYYFromAddr(ulong ulTimeAddr)
{
    uchar ucValue;
    ucValue=GAL_NO;
    if(1==ReadDataDirect(ulTimeAddr, 5, &Wr_data[0]))
    {
        if(Wr_data[1] != RSOFT_RTC_HOUR)
            ucValue=GAL_YES;
        if(Wr_data[2] != RSOFT_RTC_DAY)
            ucValue=GAL_YES;
        if(Wr_data[3] != RSOFT_RTC_MONTH)
            ucValue=GAL_YES;
        if(Wr_data[4] != RSOFT_RTC_YEAR)
            ucValue=GAL_YES;
    }
    return ucValue;
}


uchar  TimeChangedmmhhDDMMYYFromAddr(ulong ulTimeAddr)
{
    uchar ucValue;
    ucValue=GAL_NO;
    if(1==ReadDataDirect(ulTimeAddr, 5, &Wr_data[0]))
    {
        if(Wr_data[0] != RSOFT_RTC_MINUTE)
            ucValue=GAL_YES;
        if(Wr_data[1] != RSOFT_RTC_HOUR)
            ucValue=GAL_YES;
        if(Wr_data[2] != RSOFT_RTC_DAY)
            ucValue=GAL_YES;
        if(Wr_data[3] != RSOFT_RTC_MONTH)
            ucValue=GAL_YES;
        if(Wr_data[4] != RSOFT_RTC_YEAR)
            ucValue=GAL_YES;
    }
    return ucValue;
}

/*void SaveProgramTime(void)
{
    WriteDataDirect((uchar * )&ucProgramTime, EPL_PROGRAM_TIME_REMAIN, 2);
}*/
void SavePasswordInf(void)
{
    WriteDataDirect(&RAM[RAM_PASSWORD_ERR_COUNT_START], EPL_PASSWORD_ERR_COUNT_START, 33);
}
uchar ZeroNumClac(ulong ulData);

// AA --计算真实数据的起始---AA
uchar ZeroNumClac(ulong ulData)
{
//  ulong ulTemp;
//  uchar ucTemp;
    if(0xff000000&ulData)
    {
        if(0xffff0000&ulData)
        {
            if(0xffffff00&ulData)
            {
                return 1;
            }
            else
            {
                return 2;
            }
        }
        else
        {
            return 3;
        }
    }
    else
    {
        return 4;
    }
}
const uchar wordBitMap[]=
{
	BIT0, BIT1, BIT2, BIT3, BIT4, BIT5, BIT6, BIT7,
};
uchar JudgeUartParaWord(uchar word,uchar* uartPara)
{
	uchar i,j;
	
	j = 0;
	for(i=1;i<7;i++)
	{
		if((wordBitMap[i]&word) != 0)
		{
			j++;
			*uartPara = i;
		}
	}
	if(j!=1)
	{
		return 0;//find fail
	}
	return 1;//find succ
}
u16 Sqrt32to16(ulong m) 
{ 
    u16 n=0,i; 
    ulong temp, ttp;
    if(m==0) 
        return 0;
    temp=m>>30;
    m<<=2; 
    if(temp>1)
    { 
        n=1; 
        temp-=n; 
    }
    for(i=15;i>0;i--)
    { 
        n<<=1; 
        temp<<=2; 
        temp=(m>>30)+temp; 
        ttp=n; 
        ttp=(ttp<<1)+1;
        m<<=2; 
        if(temp>=ttp) 
        { 
            temp-=ttp; 
            n+=1; 
        }
    }
    return n; 
}
void SetCurrentTime(void)
{
    ulong ulTemp;
    ulTemp=CalendarToSec((STR_CALENDAR*)&RSOFT_RTC_SECOND);
    SetLastSaveTime(ulTemp);
}

uchar JudjeFunction01Ib(void)
//AA--判断电流是否小于1%--AA
//AA--如果大于1%，对应象限加1--AA
{
    uchar ucReturn;
    ulong ulTempTypeIb;
    ucReturn=0;
    ulTempTypeIb=ulTypeIb*10;
    if(ulNowCurrent[0]>=ulTempTypeIb) 
    {
        ucReturn=ucReturn+1;
    }
    if(ulNowCurrent[1]>=ulTempTypeIb) 
    {
        ucReturn=ucReturn+2;
    }
    if(ulNowCurrent[2]>=ulTempTypeIb) 
    {
        ucReturn=ucReturn+4;
    }
    return ucReturn;
}

uchar JudjeFunction05Ib(uchar ucType)
{   
    if(ulNowCurrent[ucType]>=(ulTypeIb*50)) 
        return 1;  
    else 
        return 0;
}

//系统delay nMs毫秒
void SysDelayMs(vu32 nMs)
{
    usleep(nMs*1000);
}

/*******************************************************************************
* Function Name  : Delay
* Description    : Inserts a delay time.
* Input          : nCount: specifies the delay time length.
* Output         : None
* Return         : None
*******************************************************************************/
void Delay(vu32 nCount)
{
    for(; nCount != 0; nCount--);
}

#endif
#endif

