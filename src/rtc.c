/*******************************************************************************
ģ����       : RTC
�ļ���       : 
����ļ�     : 
�ļ�ʵ�ֹ��� : 
����         : sun yang
�汾         : Ver 1.0��
-------------------------------------------------------------------------------
��ע         : 
-------------------------------------------------------------------------------
�޸ļ�¼ : 
�� ��        �汾     �޸���              �޸�����
YYYY/MM/DD   X.Y      <���߻��޸�����>    <�޸�����>
===============================================================================
����˵��:   �ޡ�
*******************************************************************************/
#ifndef __RTC_C__
#define __RTC_C__

#include "common.h"

#if 0
const char MonTabNotLeapYear[13] = 
{
  0,31,28,31,30,31,30,31,31,30,31,30,31
};
/*
const near char MonTabInLeapYear[13]= 
{
  0,31,29,31,30,31,30,31,31,30,31,30,31
};*/

const int DayTab[13] = 
{
  0,0,31,59,90,120,151,181,212,243,273,304,334
};



/*
const uchar weekTab[] =     //���������ڱ�
{
  (3 << 5) + 31,    //1��
  (6 << 5) + 29,    //2��
  (0 << 5) + 31,    //3��
  (3 << 5) + 30,    //4��
  (5 << 5) + 31,    //5��
  (1 << 5) + 30,    //6��
  (3 << 5) + 31,    //7��
  (6 << 5) + 31,    //8��
  (1 << 5) + 30,    //9��
  (4 << 5) + 31,    //10��
  (0 << 5) + 30,    //11��
  (2 << 5) + 31     //12��
};
*/

#if(REAL_TIME_TYPE == HARD_REALTIME)
    uchar SetReadRealTimeToCMOSChip(STR_CALENDAR* time);
    uchar ReadRealTimeFormCMOSChip(STR_CALENDAR* time);
    uchar SetCMOSChipPara(STR_RTC_PARA* para);
#endif
u16 GetGmDay(STR_CALENDAR* time);
ulong GetGmMin( STR_CALENDAR* time );
char GetWeek(STR_CALENDAR* time);
uchar GetMounthDay(STR_CALENDAR* time);
uchar CheckTimeFormat(STR_CALENDAR* time);
void AdjustTime(STR_CALENDAR* time);
#if(FREQUENCY_EQUALIZE == OK)
    void FrequencyEqualizeManage(STR_CALENDAR* time);
#endif
#if(TEMP_EQUALIZE == OK)
    void TempEqualizeManage(STR_CALENDAR* time);
#endif
void RTCCallBack(void);
uchar StartRTC(const STR_RTC_PARA* para);
void RunRTC(STR_CALENDAR* time);
uchar GetRealTime(STR_CALENDAR* time);
uchar SetRealTime(STR_CALENDAR* time);
int meter_time_valid_check(struct date_time_rec *mytime);

void DelayTime(vu32 nCount);
void DelayTime(vu32 nCount)
{
    for(; nCount != 0; nCount--);
}


#if(REAL_TIME_TYPE == HARD_REALTIME)
uchar SetReadRealTimeToCMOSChip(STR_CALENDAR* time)
{
    uchar returnData;
    
    returnData = 0;
    #if(HARD_REALTIME_CMOS_CHIP == RTC_PT4372)
        ;
    #elif(HARD_REALTIME_CMOS_CHIP == RX8025T)
        if(WriteCalendarTime((uchar*)time) != 0)
        {
            if(WriteCalendarTime((uchar*)time) != 0)
                returnData = 1;
        }
    #elif(HARD_REALTIME_CMOS_CHIP == RTC_PCF8563)
        ;
    #endif
    
    return(returnData);
}


uchar ReadRealTimeFormCMOSChip(STR_CALENDAR* time)
{
    uchar returnData;
    STR_CALENDAR iTime;
    
    returnData = 0;
    //notice if read CMOSChip failed do not reset the time
    #if(HARD_REALTIME_CMOS_CHIP == RTC_PT4372)
        ;
    #elif(HARD_REALTIME_CMOS_CHIP == RX8025T)
        if(ReadCalendarTime((uchar*)&iTime) != 0)
        {
            DelayTime(1000);
            if(ReadCalendarTime((uchar*)&iTime) != 0)
            {
                returnData = 1;

                DelayTime(1000);
            }
        }
    #elif(HARD_REALTIME_CMOS_CHIP == RTC_PCF8563)
        ;
    #endif
    if(!returnData)
    {
        if(0==CheckTimeFormat(&iTime))
        {
        memcpy(time,&iTime,sizeof(STR_CALENDAR));
        }
    }
        
    return(returnData);
}


uchar SetCMOSChipPara(STR_RTC_PARA* para)
{
    uchar returnData;
    
    returnData = 0;
    #if(HARD_REALTIME_CMOS_CHIP == RTC_PT4372)
        ;
    #elif(HARD_REALTIME_CMOS_CHIP == RX8025T)
        if(SetCalendarMode(para->mode1224) != 0)
        {
            if(SetCalendarMode(para->mode1224) != 0)
                returnData = 1;
        }
        if(!returnData)
        {
            SetCalendarPulseMode(para->pulseFrequency);
            /*
            if(SetCalendarPulseMode(para->pulseFrequency) != 0)
            {
                if(SetCalendarPulseMode(para->pulseFrequency) != 0)
                    returnData = 1;
            }
            */
        }
    #elif(HARD_REALTIME_CMOS_CHIP == RTC_PCF8563)
        ;
    #endif
    
    return(returnData);
}

#endif


/*************************************************************
Function: 
Input: time:��ǰʱ��
Output: 
Application area: 
Explain: 
Modification register:
**************************************************************/
u16 GetGmDay(STR_CALENDAR* time)
{
  u16 Day,Mon,Year;

    Mon = BCD_Byte(time->month);
    Year= BCD_Byte(time->year);
    Day = BCD_Byte(time->day) + DayTab[Mon] + Year*365 + (Year>>2) + 1;
    if( (Year&0x03)==0 && Mon<=2 ) 
        Day--;
    return Day;
}


/*************************************************************
Function: 
Input: time:��ǰʱ��
Output: 
Application area: 
Explain: 
Modification register:
**************************************************************/
ulong GetGmMin( STR_CALENDAR* time )
{
    return (ulong)BCD_Byte(time->minute)
        + (ulong)BCD_Byte(time->hour)*60
        + (ulong)GetGmDay(time)*60*24;
}


/*************************************************************
Function: ��õ������ڼ�
Input: time:��ǰʱ��
Output: 
Application area: 
Explain: 
Modification register:
**************************************************************/
char GetWeek(STR_CALENDAR* time)
{
   return (char)((GetGmDay(time)+5)%7);
}
/*
uchar GetTodayWeek(STR_CALENDAR* iTime)
{
    uchar week, day;
    STR_CALENDAR time;
    
    memcpy(&time,iTime,sizeof(STR_CALENDAR));
    day = weekTab[time.month - 1];  //�±�
    week = day >> 5;    //��������
    //day &= 0x1f;  //������
    if ((time.month < 3) && (time.year & 0x03)) //ƽ��
    {
        //if (time.month == 2) 
        //  day--;  //ƽ��������
        week++; //ƽ���±�+1
    }
    time.year = time.year + (time.year >> 2);   //��+��/4
    week = (week +  time.year + time.day + 2) % 7;  //(����=��+��/4+�±�+2��)%7
    //return (week << 5) | day; //�������ں�������
    return(week);
}
*/


/*************************************************************
Function: ��õ�������
Input: time:��ǰʱ��
Output: 
Application area: 
Explain: 
Modification register:
**************************************************************/
uchar GetMounthDay(STR_CALENDAR* time)  
{
    uchar i,j;
    
    i = BCD_Byte(time->month);
    i = Byte_BCD(MonTabNotLeapYear[i]);
    
    j = ((time->month==2)&&(BCD_Byte( time->year )&0x03)==0)? 0x29:i;
    
    return(j);
    //if(time->day > j)
    //  return(1);
    //return(0);
}


/*************************************************************
Function: ʱ�Ӹ�ʽУ��
Input: time:��ǰʱ��
Output: 
Application area: 
Explain: 
Modification register:
**************************************************************/
uchar CheckTimeFormat(STR_CALENDAR* time)
{
    if((((time->second)&0x0f)<=9)&&((((time->second)>>4)&0x0f)<=5))
    {
        if((((time->minute)&0x0f)<=9)&&((((time->minute)>>4)&0x0f)<=5))
        {
            if((((time->hour)&0x0f)<=9)&&((((time->hour)>>4)&0x0f)<=9))
            {
                if(time->hour<=0x23)
                {
                    if((((time->day)&0x0f)<=9)&&((((time->day)>>4)&0x0f)<=9))
                    {
                        if(time->day <= GetMounthDay(time))
                        {
                            if((((time->month)&0x0f)<=9)&&((((time->month)>>4)&0x0f)<=9))
                            {
                                if(time->month<=0x12)
                                {
                                    if((((time->year)&0x0f)<=9)&&((((time->year)>>4)&0x0f)<=9))
                                    {
                                        if((time->week) <= SATUIDAY)
                                        {
                                            if(time->week == GetWeek(time))
                                            {
                                                return(0);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }               
            }
        }
    }
    
    return(1);
}


void AdjustTime(STR_CALENDAR* time)
{
    BCD1Inc(&time->second);
    if(time->second >= 0x60)    // Second
    {               
        time->second = 0;
        BCD1Inc(&time->minute);
        if(time->minute >= 0x60)    // Minute
        {           
            time->minute = 0;
            BCD1Inc(&time->hour);
            if(time->hour >= 0x24)  // Hour
            {       
                time->hour = 0;
                BCD1Inc(&time->week);
                if(time->week > SATUIDAY)   // Week 
                    time->week = SUNDAY;                
                BCD1Inc(&time->day);
                if(time->day > GetMounthDay(time))  //day
                {   
                    time->day = 1;
                    BCD1Inc(&time->month);
                    if(time->month > 0x12)  // Month
                    {                           
                        time->month = 1;
                        BCD1Inc(&time->year);
                        if(time->year > 0x99)   // Year
                            time->year = 0; 
                    }
                }
            }
        }
     }
    time->week=GetWeek(time);
}



/*************************************************************
Function: Ƶ�ʲ���
Input: time:��ǰʱ��
Output: 
Application area: 
Explain: 
Modification register:
**************************************************************/
#if(FREQUENCY_EQUALIZE == OK)
void FrequencyEqualizeManage(STR_CALENDAR* time)
{
    if(RTCPara.frequencyEqualizeEn)
    {
        if(frequencyEqualizeCount < 0xffffffff)
            frequencyEqualizeCount++;
        if(frequencyEqualizeCount >= AbsoluteValue(RTCPara.softFrequencyEqualizeCoeff))
        {
            if((time->second >= 0x02)&&(time->second <= 0x58))
            {
                //#if(TIME_TYPE==HARD_REALTIME)
                //  ReadRealTimeFormCMOSChip(time);
                //#endif
                if(RTCPara.softFrequencyEqualizeCoeff > 0)
                    BCD1Inc(&time->second);
                else
                    BCD1Dec(&time->second);
                frequencyEqualizeCount -= AbsoluteValue(RTCPara.softFrequencyEqualizeCoeff);
                //#if(TIME_TYPE==HARD_REALTIME)
                //  SetReadRealTimeToCMOSChip(time);
                //#endif
            }   
        }
    }
}
#endif


/*************************************************************
Function: �¶Ȳ���
Input: time:��ǰʱ��
Output: 
Application area: 
Explain: 
Modification register:
**************************************************************/
#if(TEMP_EQUALIZE == OK)
void TempEqualizeManage(STR_CALENDAR* time)
{
    //#if(TIME_TYPE==HARD_REALTIME)
    //  ReadRealTimeFormCMOSChip(time);
    //#endif
    //#if(TIME_TYPE==HARD_REALTIME)
    //  SetReadRealTimeToCMOSChip(time);
    //#endif
    ;
}
#endif




/*************************************************************
Function: RTC�жϻص�����
Input: para:
Output: ��
Application area: 
Explain: 
Modification register:
**************************************************************/
void RTCCallBack(void)
{
    RTCControl.readRTCEn = 1;
}

/*************************************************************
Function: RTC��ʼ��
Input: para:RTC����
Output: 0���ɹ�  1���ɰ�
Application area: ϵͳ����ʱ����
Explain: 
Modification register:
**************************************************************/
uchar StartRTC(const STR_RTC_PARA* para)
{
    memcpy(&RTCPara,para,sizeof(STR_RTC_PARA));
    RTCControl.readRTCEn = 0;
    StartTime1s(T1SID_RTC_TEMER_NUM, 1, TIMER_MODE_CONTINUE, RTCCallBack);
    
    //#if(TIME_TYPE==SOFT_REALTIME)
    //  GetInitTime();
    //#endif
    
    #if(REAL_TIME_TYPE == HARD_REALTIME)
        if(SetCMOSChipPara(para))
            return(1);
        if(ReadRealTimeFormCMOSChip(&realTime)) //read real time to buf HardTime form real time CMOS chip 
        {
            if(ReadRealTimeFormCMOSChip(&realTime))
                return(1);//RTC error alarm 
        }
    #endif

    return(0);
}


/*************************************************************
Function: ����RTC����
Input: time:��ǰʱ��
Output: ��
Application area: 
Explain: 
Modification register:
**************************************************************/
void RunRTC(STR_CALENDAR* time)
{
    //STR_CALENDAR HardTime;
    
    if(RTCControl.readRTCEn)
    {
        RTCControl.readRTCEn = 0;
        AdjustTime(time);
//      SetReadRealTimeToCMOSChip(time);
        #if(REAL_TIME_TYPE == HARD_REALTIME)    //ע��Ӳ��ʱ��ʱ����Ӳ��ʱ��Ҫ1�������϶�һ�Σ�����Ҫע��Ƶ�ʺ��¶ȵ���ʱ�� 
            readHardRealTimeCount++;
            if(readHardRealTimeCount >= MAX_READHARDTIME_COUNT)
            {
                readHardRealTimeCount = 0;
                if(ReadRealTimeFormCMOSChip(time))  //read real time to buf HardTime form real time CMOS chip 
                {
                    if(ReadRealTimeFormCMOSChip(time))
                        ;//RTC error alarm 
                }
            }
        #endif
        #if(FREQUENCY_EQUALIZE == OK)
            FrequencyEqualizeManage(time);
        #endif
        #if(TEMP_EQUALIZE == OK)
            TempEqualizeManage(time);
        #endif      
    }
}


/*************************************************************
Function: ���RTC����
Input: time:���ʱ��
Output: 
Application area: 
Explain: 
Modification register:
**************************************************************/
uchar GetRealTime(STR_CALENDAR* time)
{
    memcpy(time,&realTime,sizeof(STR_CALENDAR));
    return(0);
}


/*************************************************************
Function: ����RTC����
Input: time:����ʱ��
Output: 0���ɹ� 1���ɰ�
Application area: 
Explain: 
Modification register:
**************************************************************/
uchar SetRealTime(STR_CALENDAR* time)
{   
    if(CheckTimeFormat(time))
        return(1);
    
    #if(REAL_TIME_TYPE == HARD_REALTIME)
        if(SetReadRealTimeToCMOSChip(time)) //set real time CMOS chip
        {
            return(1);
        }
    #endif
    ReadRealTimeFormCMOSChip(time);
    memcpy(&realTime,time,sizeof(STR_CALENDAR));
    
    return(0);
}
#endif






#define A_DAY_MIN  1440 // (24*60)

#define A_DAY_SEC   86400 // (A_DAY_MIN * 60)

#define IS_LEAPYEAR(y)    ( (y%4==0) && ((y%100!=0) || (y%400==0)) ) // ԭ���ĺ����ɶ��Բ��ߣ������Ϊ����׶�

/*cong 2000 nian kai shi ji , dao 2051*/
const char MonTabNotLeapYear[13] = 
{
  0,31,28,31,30,31,30,31,31,30,31,30,31
};

const int DayTab[13] = 
{
  0,0,31,59,90,120,151,181,212,243,273,304,334
};

//�����޸ģ�
#if(RTC_STR_TYPE == RTC_STR_SINGLE_BYTE_YEAR)
        static  const ushort year_days[YEAR_NUM]=
        {
            0,366,731,1096,1461,1827,2192,2557,2922,3288,3653,4018,4383,4749,5114,5479,5844,
            6210,6575,6940,7305,7671,8036,8401,8766,9132,9497,9862,10227,10593,10958,11323,
            11688,12054,12419,12784,13149,13515,13880,14245,14610,14976,15341,15706,16071,
            16437,16802,17167,17532,17898,18263,18628   
        }; 
#endif
#if (RTC_STR_TYPE == RTC_STR_DOUBLE_BYTE_YEAR)
        static  const ushort year_days[YEAR_NUM]=
        {
            0,365,730,1096,1461,1826,2191,2557,2922,3287,3652,4018,4383,4748,5113,5479,5844,
            6209,6574,6940,7305,7670,8035,8401,8766,9131,9496,9862,10227,10592,10957,11323,
            11688,12053,12418,12784,13149,13514,13879,14245,14610,14975,15340,15706,16071,
            16436,16801,17167,17532,17897,18262,18628,18993,19358,19723,20089,20454,20819,
            21184,21550,21915,22280,22645,23011,23376,23741,24106,24472,24837,25202,25567,
            25933,26298,26663,27028,27394,27759,28124,28489,28855,29220,29585
        }; 
#endif

static  const ushort month_days[12]=
{
0,
31,
31+28,
31+28+31,
31+28+31+30,
31+28+31+30+31,
31+28+31+30+31+30,
31+28+31+30+31+30+31,
31+28+31+30+31+30+31+31,
31+28+31+30+31+30+31+31+30,
31+28+31+30+31+30+31+31+30+31,
31+28+31+30+31+30+31+31+30+31+30,
};

static const ushort month_ldays[12]=
{
0,
31,
31+29,
31+29+31,
31+29+31+30,
31+29+31+30+31,
31+29+31+30+31+30,
31+29+31+30+31+30+31,
31+29+31+30+31+30+31+31,
31+29+31+30+31+30+31+31+30,
31+29+31+30+31+30+31+31+30+31,
31+29+31+30+31+30+31+31+30+31+30,
};

/*********************************************************************************
 * Function:     ����ʱ��תΪ��׼�տ�ʼ������ 
 * Description:    
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:   ����Ҫ���ǺϷ���ʱ�䣬�Ҵ��ڵ��ڻ�׼�գ�����ֻ���µĺϷ������ж�       
 * Output:  ����2050��ǰ�����ڣ������ؿ����������       
 * Return:         
 * Others:         
 *******************************************************************************/ 
ushort CalendarToMon(STR_CALENDAR* datetime)
{
    YEAR_TYPE year;               
    uchar  mon;
    
    year = YearBcdToHex((uchar*) &(datetime->year));

    mon = BCDToByte(datetime->month);
    
    // ֻУ�����Ƿ�Ϸ��� �Է�ֹ����������´�0��
    //if ((mon < 1)||(mon > 12))
    //    return (ushort) - 1 ;
    //else    
        return year * 12 + mon - 1; 
}

ushort CalendarToDay(STR_CALENDAR* time)
{
    YEAR_TYPE year;
    ushort allday = 0;  
    uchar mon,day;
        
    year = YearBcdToHex((uchar*) &(time->year));
    mon = BCDToByte(time->month);
    day = BCDToByte(time->day);
    // ֻУ�����Ƿ�Ϸ��� �Է�ֹ�������
    //if ((mon < 1)||(mon > 12))
    //    return (ushort) - 1 ;
    //else 
    {
        allday=(year)*365+1+(year)/4; // �м���������1 (������1900��2100 �������������)
        if((0 != IS_LEAPYEAR(year) )&& (mon < 3)) 
            allday -= 1;    //�������꣬1,2�²�����Ӧ�÷ŵ������ֹ��δ�������1��2002��������£���1.
        allday += month_days[mon-1];
        allday = allday + day - 1;              // -1 by xcgang,���� Start���1��1��Ϊ0��ԭ��Ϊ1 
        return allday;
    }

}

/*********************************************************************************
 * Function:     ����ʱ��תΪ��׼�տ�ʼ��Сʱ�� 
 * Description:    
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:   ����Ҫ���ǺϷ���BCD��    
 * Output:  ����2050��ǰ�����ڣ������ؿ����������       
 * Return:         
 * Others:         
 *******************************************************************************/ 
ulong CalendarToHour(STR_CALENDAR* datetime)
{
    ulong h;
    ushort allday;  
    allday = CalendarToDay(datetime);
    h = BCDToByte(datetime->hour);  
    return ((ulong)(allday) * 24) + h ;  /*   now   have   hours   */   
} 

  
//=================================================================================
 // Function:     ����ʱ��תΪ��׼�տ�ʼ�ķ����� 
 // Description:    
 // Calls:          
 // Called By:      
 // Data Accessed: 
 // Data Updated:  
 // Input:   ����Ҫ���ǺϷ���BCD��    
 // Output:  ˫�ֽڣ�����2050��ǰ�����ڣ������ؿ����������       
 // Return:         
 // Others:         
 //================================================================================== 

ulong CalendarToMin( STR_CALENDAR* time )
{
    return (ulong)BCDToByte(time->minute)
        + (ulong)BCDToByte(time->hour)*60
        + (ulong)CalendarToDay(time)*60*24;
}


/*********************************************************************************
 * Function:     ����ʱ��תΪ��׼�տ�ʼ������ 
 * Description:    
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:   ����Ҫ���ǺϷ���BCD��    
 * Output:  ˫�ֽڣ�����2050��ǰ�����ڣ������ؿ����������       
 * Return:         
 * Others:         
 *******************************************************************************/ 
ulong CalendarToSec(STR_CALENDAR* datetime)
{
    ulong min , sec;
    min = CalendarToMin(datetime);
    sec = BCDToByte(datetime->second);  
    return  min * 60 + sec ;  /*   now   have   seconds   */   
}  




/*************************************************************
Function: ��õ������ڼ�
Input: time:��ǰʱ��
Output: 
Application area: 
Explain: 
Modification register:
**************************************************************/
uchar CalendarToWeek(STR_CALENDAR* time)
{
    ulong k;
    uchar i;
   
    k = CalendarToDay(time);
    i = (uchar)((k+6)%7);
    return i;
}
 
/*********************************************************************************
 * Function:     ��׼�տ�ʼ������ תΪ ����ʱ��
 * Description:    
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:   ����Ҫ���ǺϷ��ķ�Χ�������ж�     
 * Output:      
 * Return:         
 * Others:         
 *******************************************************************************/ 
STR_CALENDAR DayToCalendar(ushort all_day)
{
    YEAR_TYPE year=0xff;    
    uchar month=0xff,i,j;
    ushort day=0xffff;        
    STR_CALENDAR    stRetDateTime;
     
    for(i=0;i<YEAR_NUM;i++)
    {
        if(all_day < year_days[i]) 
            break;
    }
    
    if(i>=1)
    {
        year=YEARSTART+i-1;
        day=all_day-year_days[i-1]; 
        
        if( ( (year % 4==0) && (year % 100!=0) ) || (year % 400==0) )  // ����
        {
            for (j=0; j<12; j++)
            {
                if (day < month_ldays[j])break;
            }
            month = j ;
            day -= month_ldays[j-1];
        }
        else
        {
             for (j=0; j<12; j++)
            {
                if (day < month_days[j]) break;
            }
               month = j ;
               day -= month_days[j-1];
        }
    }

    stRetDateTime.year = 0;
    YearHexToBcd((uchar*)&stRetDateTime.year, year);

    stRetDateTime.month = ByteToBCD(month);
    stRetDateTime.day   = ByteToBCD((uchar)(day+1));//  �����ʼ���1��1�ռ�Ϊ0����+1
    stRetDateTime.week = (all_day + 6)%7;
    stRetDateTime.hour  = 0;
    stRetDateTime.minute    = 0;
    stRetDateTime.second    = 0;
    
    return stRetDateTime;
}


/*********************************************************************************
 * Function:     ��׼�տ�ʼ�ķ����� תΪ ����ʱ��
 * Description:    
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:   ����Ҫ���ǺϷ��ķ�Χ�������ж�     
 * Output:      
 * Return:         
 * Others:         
 *******************************************************************************/ 
STR_CALENDAR MinToCalendar(ulong all_min)
{
    ushort all_day;
    uchar h,min;
    STR_CALENDAR    stRetDateTime;
    
    all_day = (ushort) (all_min / A_DAY_MIN) ;
    all_min = all_min % A_DAY_MIN;
    h = (uchar)(all_min / 60);
    min = (uchar)(all_min % 60);

    stRetDateTime = DayToCalendar(all_day);
    stRetDateTime.hour  = ByteToBCD(h);
    stRetDateTime.minute    = ByteToBCD(min);
    stRetDateTime.second    = 0;
    return stRetDateTime;
}


/*********************************************************************************
 * Function:    �����������ʱ���������ķ��������õ��µ�����ʱ��(For Guangwei)
 * Description: 
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:   ����Ҫ���ǺϷ��ķ�Χ�������ж�     
 * Output:      
 * Return:         
 * Others:         
 *******************************************************************************/ 
STR_CALENDAR CalendarAddMin(STR_CALENDAR *point_data_start , ulong all_min)
{
    ulong last_min;
    ushort all_day;
    uchar h,min;
    STR_CALENDAR    stRetDateTime;

    last_min = CalendarToMin(point_data_start);
        all_min += last_min;

    all_day = (ushort) (all_min / A_DAY_MIN) ;
    all_min = all_min % A_DAY_MIN;
    h = (uchar)(all_min / 60);
    min = (uchar)(all_min % 60);

    stRetDateTime = DayToCalendar(all_day);
    stRetDateTime.hour  = ByteToBCD(h);
    stRetDateTime.minute    = ByteToBCD(min);
    stRetDateTime.second    = 0;
    return stRetDateTime;
}


/*********************************************************************************
 * Function:     ��׼�տ�ʼ������ תΪ ����ʱ��
 * Description:    
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:   ����Ҫ���ǺϷ��ķ�Χ�������ж�     
 * Output:      
 * Return:         
 * Others:         
 *******************************************************************************/ 
STR_CALENDAR SecToCalendar(ulong all_sec)
{
    ushort all_day;
    uchar h,min,sec;
    STR_CALENDAR    stRetDateTime;
    // TODO: ��GCC�������У��ƺ��ֽڶ��뷽ʽ���ԣ�����û��
    all_day = (ushort)(all_sec / A_DAY_SEC);
    all_sec = all_sec % A_DAY_SEC;
    sec = (uchar)(all_sec % 60);
    h = (uchar)(all_sec / 3600);
    min = (uchar)(all_sec % 3600 / 60);

    stRetDateTime = DayToCalendar(all_day);
    stRetDateTime.hour  = ByteToBCD(h);
    stRetDateTime.minute    = ByteToBCD(min);
    stRetDateTime.second    = ByteToBCD(sec);
    return stRetDateTime;
}



/*************************************************************
Function: ��õ�������
Input: time:��ǰʱ��
Output: 
Application area: 
Explain: 
Modification register:
**************************************************************/
uchar GetMounthDay(STR_CALENDAR* time)  
{
    uchar i,j;
    
    i = BCDToByte(time->month);
    i = ByteToBCD(MonTabNotLeapYear[i]);
    
    j = ((time->month==2)&&(BCDToByte( time->year )&0x03)==0)? 0x29:i;
    
    return(j);
}


/*************************************************************
Function: ʱ�Ӹ�ʽУ��
Input: time:��ǰʱ��
Output: 
Application area: 
Explain: 
Modification register:
**************************************************************/
uchar CheckTimeFormat(STR_CALENDAR* time,uchar mode)
{
    if((((time->second)&0x0f)<=9)&&((((time->second)>>4)&0x0f)<=5))
    {
        if((((time->minute)&0x0f)<=9)&&((((time->minute)>>4)&0x0f)<=5))
        {
            if((((time->hour)&0x0f)<=9)&&((((time->hour)>>4)&0x0f)<=9))
            {
                if(time->hour<=0x23)
                {
                    if((((time->day)&0x0f)<=9)&&((((time->day)>>4)&0x0f)<=9)&&(time->day!=0))
                    {
                        if(time->day <= GetMounthDay(time))
                        {
                            if((((time->month)&0x0f)<=9)&&((((time->month)>>4)&0x0f)<=9)&&(time->month!=0))
                            {
                                if(time->month<=0x12)
                                {
                                    if((((time->year)&0x0f)<=9)&&((((time->year)>>4)&0x0f)<=9))
                                    {
                                        if(mode == 0)
                                        {
                                            if((time->week) <= SATURDAY)
                                            {
                                                if(time->week == CalendarToWeek(time))
                                                {
                                                    return(0);
                                                }
                                            }
                                        }
                                        else
                                            return(0);
                                    }
                                }
                            }
                        }
                    }
                }               
            }
        }
    }
    
    return(1);
}
























/*************************************************************
Function: RTC�жϻص�����
Input: para:
Output: ��
Application area: 
Explain: 
Modification register:
**************************************************************/
#if 0
void RTCCallBack(void)
{
    RTCControl.readRTCEn = 1;
}
#endif

/*************************************************************
Function: RTC��ʼ��
Input: para:RTC����
Output: 0���ɹ�  1���ɰ�
Application area: ϵͳ����ʱ����
Explain: 
Modification register:
**************************************************************/
uchar StartRTC(const STR_RTC_PARA* para)
{
//  memcpy(&RTCPara,para,sizeof(STR_RTC_PARA));
//  RTCControl.readRTCEn = 0;
//  StartTime1s(T1SID_RTC_TEMER_NUM, 1, TIMER_MODE_CONTINUE, RTCCallBack);
    GetRealTime(&realTime);
    return(0);
}


void SoftTimer(void);
void SoftTimer(void)
{
    static uchar last_min=0xff;
    TimerManage1s();
    RSOFT_RTC_SECOND    = realTime.second;
    RSOFT_RTC_MINUTE    = realTime.minute;
    RSOFT_RTC_HOUR      = realTime.hour;
    RSOFT_RTC_WEEK      = realTime.week;
    RSOFT_RTC_DAY       = realTime.day;
    RSOFT_RTC_MONTH     = realTime.month;
    RSOFT_RTC_YEAR      = realTime.year;
    if(last_min != RSOFT_RTC_MINUTE)
    {
        //SetmmhhDDMMYYToPoint(&Wr_data[0]);
        //ulNowMinTime = mmHHDDMMYYToLong(&Wr_data[0]);
        ulNowMinTime = mmHHDDMMYYToLong(&(RSOFT_RTC_MINUTE));
        last_min = RSOFT_RTC_MINUTE;
    }
}

/*************************************************************
Function: ����RTC����
Input: time:��ǰʱ��
Output: ��
Application area: 
Explain: 
Modification register:
**************************************************************/
void RunRTC(STR_CALENDAR* time)
{
    if(RTCControl.readRTCEn)
    {
        Delay1mS(); // TODO: ��Ҫ��취�ܿ�
        RTCControl.readRTCEn = 0;
        GetRealTime(time);
        SoftTimer();
    }
}

#ifdef  TIME_FASTER_TEST
#include "..\..\ap\inc\gol_ram.h"
extern uchar RAM[];
extern uchar ReadDataDirect(ulong DataName,   u16 nLen, uchar* pSrc);
extern uchar WriteDataDirect(uchar* pSrc, ulong DataName,   u16 nLen);

ulong ulTimeFasterTestBegin;
ulong ulTimeFasterTestLastCount;
void TimeFasterTestPoweron(void)
{
    ReadDataDirect(0x05003FB0, 2, &RAM[RAM_TIME_FASTER_TEST_FLAG]);
    ReadDataDirect(0x05003FB4, 4, (uchar*)&ulTimeFasterTestBegin);
    ReadDataDirect(0x05003FB8, 4, (uchar*)&ulTimeFasterTestLastCount);
}
void TimeFasterTestPoweroff(void)
{
    WriteDataDirect(&RAM[RAM_TIME_FASTER_TEST_FLAG], 0x05003FB0, 2);
    WriteDataDirect((uchar*)&ulTimeFasterTestBegin, 0x05003FB4, 4);
    WriteDataDirect((uchar*)&ulTimeFasterTestLastCount, 0x05003FB8, 4);
}
#endif

/*************************************************************
Function: ���RTC����
Input: time:���ʱ��
Output: 
Application area: 
Explain: 
Modification register:
**************************************************************/
uchar GetRealTime(STR_CALENDAR* time)
{
#if 1
    time->second = RSOFT_RTC_SECOND;
    time->minute = RSOFT_RTC_MINUTE;
    time->hour = RSOFT_RTC_HOUR;
    time->day = RSOFT_RTC_DAY;
    time->month = RSOFT_RTC_MONTH;
    time->year = RSOFT_RTC_YEAR;
    time->week = RSOFT_RTC_WEEK;
#else
    ulong i;

    i = RTC_GetCounter();
#ifdef  TIME_FASTER_TEST
    if((RAM[RAM_TIME_FASTER_TEST_FLAG] == 0x55))
    {
        /*if(i > ulTimeFasterTestBegin)
        {
            i = ulTimeFasterTestBegin + (i-ulTimeFasterTestBegin)*RAM[RAM_TIME_FASTER_TEST_MUL];
        }*/
        ulTimeFasterTestBegin += (i-ulTimeFasterTestLastCount)*RAM[RAM_TIME_FASTER_TEST_MUL];
        ulTimeFasterTestLastCount = i;
        i = ulTimeFasterTestBegin;
    }
    else
    {
        ulTimeFasterTestBegin = i;
        ulTimeFasterTestLastCount = i;
    }
#endif

    *time = SecToCalendar(i>>1);
#endif
    return 0;
}

/*
ʱ����Ч�Լ��
0��Ч�� -1����������Ч
*/
int meter_time_valid_check(struct date_time_rec *mytime)
{
	if(mytime->year < 1990)
		return -1;
	if(mytime->year > 2037)						//linux ϵͳʱ�����Ƶ�2038-01-19
		return -1;
	if(mytime->month < 1 || mytime->month > 12)
		return -1;

	if(mytime->month == 1 || mytime->month == 3 || mytime->month == 5 || mytime->month == 7 || 
		mytime->month == 8 || mytime->month == 10 || mytime->month == 12)
	{
		if(mytime->day < 1 || mytime->day > 31)
			return -1;
	}
	else if(mytime->month == 4 || mytime->month == 6 || mytime->month == 9 || mytime->month == 11)
	{
		if(mytime->day < 1 || mytime->day > 30)
			return -1;
	}
	else if(mytime->year%4 != 0 || (mytime->year%100==0 && mytime->year%400!=0))
	{//ƽ��2��
		if(mytime->day < 1 || mytime->day > 28)
			return -1;
	}
	else
	{//����2��
		if(mytime->day < 1 || mytime->day > 29)
			return -1;
	}

	if(mytime->hour > 23)
		return -1;
	if(mytime->minute > 59)
		return -1;
	if(mytime->second > 59)
		return -1;
	return 0;
}

/*************************************************************
Function: ����RTC����
Input: time:����ʱ��
Output: 0���ɹ� 1���ɰ�
Application area: 
Explain: 
Modification register:
**************************************************************/
uchar SetRealTime(STR_CALENDAR* time)
{
	//xwh 20110526 start	��������Ҫ����Ҫ֧������ʱ��
	struct date_time_rec tmp_time;
	int ret;
	tmp_time.year = (unsigned short)BCDToByte((time->year));
	tmp_time.year += 2000;
	tmp_time.month = (unsigned char)BCDToByte((time->month));
	tmp_time.day = (unsigned char)BCDToByte((time->day));
	tmp_time.hour = (unsigned char)BCDToByte((time->hour));
	tmp_time.minute = (unsigned char)BCDToByte((time->minute));
	tmp_time.second = (unsigned char)BCDToByte((time->second));

	if(meter_time_valid_check(&tmp_time) == 0)
	{
		ret = rtc_set(&tmp_time);
		LOGTRACE("settime %04d-%02d-%02d %02d:%02d:%02d  result %d\n",
			tmp_time.year,tmp_time.month,tmp_time.day,
			tmp_time.hour,tmp_time.minute,tmp_time.second,ret);
	}
	else
	{
		LOGTRACE("checktime %04d-%02d-%02d %02d:%02d:%02d not ok\n",
			tmp_time.year,tmp_time.month,tmp_time.day,
			tmp_time.hour,tmp_time.minute,tmp_time.second);
	}
    MeterTimeUpdateSimply();
	//xwh 20110526 end

//-----------------------------------------------------------------
    //���ʱ�����Լ������Ĳ���ϵͳ����Ʊ����ݲ�֧��ʱ������
#if 0    
    ulong i;

    i = CalendarToSec(time);
    RTC_WaitForLastTask();
    RTC_SetCounter((i<<1)+1);
#ifdef  TIME_FASTER_TEST
    if(RAM[RAM_TIME_FASTER_TEST_FLAG] == 0x55)
    {
        ulTimeFasterTestBegin = i;
        ulTimeFasterTestLastCount = i;
    }
#endif
#endif
    return 0;
}

#endif

