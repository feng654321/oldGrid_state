#ifndef __RTC_H__
#define __RTC_H__

#ifdef  __RTC_C__
    #define RTC_EXT
#else
    #define RTC_EXT extern
#endif



#define RTC_STR_SINGLE_BYTE_YEAR   1
#define RTC_STR_DOUBLE_BYTE_YEAR   2

#define RTC_STR_TYPE  RTC_STR_SINGLE_BYTE_YEAR
 

#if(RTC_STR_TYPE == RTC_STR_SINGLE_BYTE_YEAR)
    typedef uchar           YEAR_TYPE;
    #define YEARSTART       0
    #define YEAR_NUM        52
    #define YearBcdToHex(ptr)           (BCDToByte(*ptr) - YEARSTART)
    #define YearHexToBcd(pb, y_hex)     {*pb = ByteToBCD(y_hex);}
#elif(RTC_STR_TYPE == RTC_STR_DOUBLE_BYTE_YEAR)
    #define YEARSTART       0x1970
    typedef u16            YEAR_TYPE;
    #define YEAR_NUM        82
    #define YearBcdToHex(ptr)   (BCD2ToWord(ptr) - YEARSTART)
    #define YearHexToBcd(pb, y_hex)     {WordToBCD2(pb, y_hex);}
#endif

#define SUNDAY          0
#define MONDAY          1
#define TUESDAY         2
#define WEDNEDAY        3
#define THURSDAY        4
#define FRIDAY          5
#define SATURDAY        6

typedef struct
{
    uchar second;
    uchar minute;
    uchar hour;
    uchar day;
    uchar month;
    YEAR_TYPE year;
    uchar week;
}STR_CALENDAR;
typedef struct
{
    long softFrequencyEqualizeCoeff;
    uchar hardFrequencyEqualizeCoeff;
    uchar mode1224:1;                   //0:12 1:24
    uchar pulseFrequency:3;             //只有硬时钟时才有脉冲输出
    uchar tempEqualizeEn:1;             //0:close  1:open
    uchar frequencyEqualizeEn:1;        //0:close  1:open
    uchar hold:2;
}STR_RTC_PARA;
typedef struct
{
    uchar readRTCEn:1;
    uchar hold:7;
}STR_RTC_CONTROL;
RTC_EXT STR_CALENDAR realTime;
RTC_EXT STR_RTC_PARA RTCPara;
RTC_EXT STR_RTC_CONTROL RTCControl;
//RTC_EXT ulong ulNowMinTime;

//#define TIME_FASTER_TEST           1
#ifdef  TIME_FASTER_TEST
#define RAM_TIME_FASTER_TEST_FLAG   RAM_PASSWORD_LOCK_TIME_SECURITY
#define RAM_TIME_FASTER_TEST_MUL    (RAM_PASSWORD_LOCK_TIME_SECURITY+1)
RTC_EXT void TimeFasterTestPoweron(void);
RTC_EXT void TimeFasterTestPoweroff(void);
#if(CONFIG_METER_FACTORY_MODE_DISABLE== CONFIG_METER_FACTORY_MODE)
	print("千万不要将时间加速测试程序发布出去!~~~~~~~~~");
#endif
#endif

RTC_EXT const int DayTab[13];

/*日历时间转换为基准日开始的月，日，时，分，秒*/ 
RTC_EXT ushort CalendarToMon(STR_CALENDAR* datetime);
RTC_EXT ushort CalendarToDay(STR_CALENDAR* time);
RTC_EXT uchar CalendarToWeek(STR_CALENDAR* time);
RTC_EXT ulong CalendarToHour(STR_CALENDAR* datetime);
RTC_EXT ulong CalendarToMin( STR_CALENDAR* time );
RTC_EXT ulong CalendarToSec(STR_CALENDAR* datetime);
RTC_EXT uchar GetMounthDay(STR_CALENDAR* time);
/*从基准日开始的日，时，分，秒数转换为日历时间*/
RTC_EXT STR_CALENDAR DayToCalendar(ushort all_day);
RTC_EXT STR_CALENDAR MinToCalendar(ulong all_min);
RTC_EXT STR_CALENDAR SecToCalendar(ulong all_sec);
RTC_EXT STR_CALENDAR CalendarAddMin(STR_CALENDAR* point_data_start , ulong all_min);
RTC_EXT uchar CheckTimeFormat(STR_CALENDAR* time,uchar mode);


RTC_EXT void RunRTC(STR_CALENDAR* time);
// RTC_EXT void RTCCallBack(void);
RTC_EXT uchar SetRealTime(STR_CALENDAR* time);
RTC_EXT uchar GetRealTime(STR_CALENDAR* time);
RTC_EXT uchar StartRTC(const STR_RTC_PARA* para);
// RTC_EXT ulong GetRealTimeCount();

#define GetRealTimeCount() RTC_GetCounter()
#endif
