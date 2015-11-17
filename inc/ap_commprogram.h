
#ifndef EVENT_PROGRAM_H
    #define EVENT_PROGRAM_H

#ifdef  AP_COMMPROGRAM_H
    #define EVENT_PROGRAM_EXT
#else
    #define EVENT_PROGRAM_EXT extern
#endif

#define     PROGRAM_CLEAR_ENABLE_SWITCH1        0xA55A
#define     PROGRAM_CLEAR_ENABLE_SWITCH2        0x5AA5


EVENT_PROGRAM_EXT   u16 programEnableCount;



/*
///////针对07版的
//////各种编程事件的数据定义            
#define COMM_EVEN_MeterClear    0x01
#define COMM_EVEN_MDClear               0x02
#define COMM_EVEN_EvenClear         0x03
#define COMM_EVEN_CHECKTIME         0x04
#define COMM_EVEN_FEETABLEP_ROGRAM  0x05
#define COMM_EVEN_SEASONTABLE_PROGRAM 0x06
#define COMM_EVEN_WEEKTABLE_PROGRAM 0x07
#define COMM_EVEN_HOLIDAY_PROGRAM       0x08
#define COMM_EVEN_ACTIVECOMBINE_1_PROGRAM           0x09
#define COMM_EVEN_NACTIVECOMBINE_2_PROGRAM      0x0A
#define COMM_EVEN_NACTIVECOMBINE_3_PROGRAM                  0X0B

*/



// 记录事件类型
#define PROGRAM_RECORD_COMMOM           0x01        ////编程事件数据记录
#define PROGRAM_RECORD_METER_CLR            0x02        ////电表清零编程事件数据记录
#define PROGRAM_RECORD_ENERGY_CLR       0x03        ////电量清零编程事件数据记录
#define PROGRAM_RECORD_DEMAND_CLR       0x04        ////需量清零编程事件数据记录
#define PROGRAM_RECORD_EVENT_CLR            0x05        ////事件清零编程事件数据记录
#define PROGRAM_RECORD_ADJUST_TIME      0x06        ////校时编程事件数据记录
#define PROGRAM_RECORD_TIMING_SEG       0x07        ////时段表编程事件数据记录
#define PROGRAM_RECORD_TIMING_ZONE      0x08        ////时区表编程事件数据记录
#define PROGRAM_RECORD_WEEK_REST            0x09        ////周休日编程事件数据记录
#define PROGRAM_RECORD_HOLIDAY          0x10        ////节假日编程事件数据记录
#define PROGRAM_RECORD_ACTIVE_COM       0x11        ////有功组合方式特征字编程事件
#define PROGRAM_RECORD_REACTIVE_COM1    0x12        ////无功组合1方式特征字编程事件数据记录
#define PROGRAM_RECORD_REACTIVE_COM2    0x13        ////无功组合2方式特征字编程事件数据记录
#define PROGRAM_RECORD_BALANCE_DAY      0x14        ////结算日编程事件数据记录
#define PROGRAM_RECORD_RELAY_ON         0x15        ////继电器接通事件数据记录
#define PROGRAM_RECORD_RELAY_OFF            0x16        ////继电器断开事件数据记录





typedef struct
{
    uchar EvenType;    /////事件类型,
    ulong ID;  /////通信ID,(没有ID的编程高位用FFFFFF代替,低位为控制码)
    ulong HanderNum;  ////操作者代码,
    uchar CommNo;  ///通信通道号码
    uchar CommType;  ///规约类型.
}STR_PROGRAM_RECORD_INDATA; 

//////传入数据,传入数据,数据长度,
EVENT_PROGRAM_EXT u16 EvenProgramRecord(STR_PROGRAM_RECORD_INDATA CommProgramdata,uchar*Src,u16 Lenth);


EVENT_PROGRAM_EXT void EventProgramRecordReset(void);

EVENT_PROGRAM_EXT uchar ucProgramPoint; //编程事件记录状态(0未记录；1已经记录）
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
EVENT_PROGRAM_EXT void CardProgramRecord(CARD_PROGRAM_RECORD_STRUCT* dataDI);
#endif
EVENT_PROGRAM_EXT void SpringStartTotalCommRecord(uchar type);

EVENT_PROGRAM_EXT void ProgramPointSet(uchar isSet);

#endif
