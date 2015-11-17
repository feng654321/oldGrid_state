#ifndef TIMERAPI_H
    #define TIMERAPI_H

#ifdef  __TIMERAPI_C__
    #define TIMERAPI_EXT
#else
    #define TIMERAPI_EXT extern
#endif

    
#define TIMR_ON         1
#define TIMR_OFF        0

typedef  void  (*PEFUNCTION)(void); 
#define TIMER_WORDTYPE  uchar
#define TIMER_MODE_ONCE         0
#define TIMER_MODE_CONTINUE     1
typedef  struct TIMERINF        
{
  uchar number:6;               //定时器序号
  uchar timeswitch:1;           //定时器开关
  uchar timerMode:1;            //定时器模式   0:once   1:continue
  TIMER_WORDTYPE timeLen;       //定时长度
  TIMER_WORDTYPE timeCount;     //定时技术
  PEFUNCTION callback;          //回掉函数
}STR_TIMER;

#define TIMEER_1S_ENABLE        1
#define TIMEER_10MS_ENABLE      1

enum
{
    T1SID_SOURCE_IR_LFCLR,
    T1SID_SOURCE_485_LFCLR,
    T1SID_SOURCE_COMM_SECOND_LFCLR,
    T1SID_SOURCE_VIRTUAL_LFCLR,
    //T1SID_RTC_TEMER_NUM,
    T1SID_REFALSH_DISPLAY_TIMER_NUM,
    T1SID_TURN_PAGE_TIMER_NUM,
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)    
    T1SID_FARCTL_COUNT_TIM,
    T1SID_FARCTL_SUB_TIM,
    T1SID_CERTIFICATION_TIMEDEC,
    T1SID_SET_SUBMONEY_FLAG,
#endif    
    MAX_TIMENUM_1S,    
};
enum
{
    T10MSID_10MS_INT,
    T10MSID_UART0_CHANNEL,
    T10MSID_UART1_CHANNEL,
    T10MSID_UART2_CHANNEL,
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)    
    T10MSID_PREPAY_TASK_FLAG,
#endif    
    MAX_TIMENUM_10MS,    
};

TIMERAPI_EXT PEFUNCTION Manage100usEvent;
#if(TIMEER_10MS_ENABLE != 0)
    TIMERAPI_EXT STR_TIMER timeInf10ms[MAX_TIMENUM_10MS];
#endif


#if(TIMEER_1S_ENABLE != 0)
    TIMERAPI_EXT STR_TIMER timeInf1s[MAX_TIMENUM_1S];
#endif
    

#if(TIMEER_10MS_ENABLE != 0)
    TIMERAPI_EXT void TimerManage10ms(void);
    TIMERAPI_EXT uchar StartTime10ms(uchar timeNumber, TIMER_WORDTYPE timeLen, uchar mode, PEFUNCTION callBack);
    TIMERAPI_EXT uchar CloseTime10ms(uchar timeNumber);
#endif

#if(TIMEER_1S_ENABLE != 0)
    TIMERAPI_EXT void TimerManage1s(void);
    TIMERAPI_EXT uchar StartTime1s(uchar timeNumber, TIMER_WORDTYPE timeLen, uchar mode, PEFUNCTION callBack);
    TIMERAPI_EXT uchar CloseTime1s(uchar timeNumber);
#endif  
    
#endif


