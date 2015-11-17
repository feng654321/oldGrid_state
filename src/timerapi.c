/*******************************************************************************
ģ����       : soft timer
�ļ���       : 
����ļ�     : 
�ļ�ʵ�ֹ��� : 
����         : taozhiguo
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
#ifndef __TIMERAPI_C__
#define __TIMERAPI_C__

#include "common.h"

#if 0
void EmptyTask(void);
void EmptyTask(void)
{
    ;
}

void Timer2Switch(uchar switchEn);
void RTCSwitch(uchar switchEn);


void Timer2Switch(uchar switchEn)
{
    if(switchEn)
    {
        Manage100usEvent = EmptyTask;
        #if(TIMEER_10MS_ENABLE != 0)
            memset(timeInf10ms,0,sizeof(timeInf10ms));
        #endif
        InitTimer2();
#if(CONFIG_METER_SW_DEBUG_MODE == GAL_YES)
        InitTimer5();
        #endif
    }
    else
    {
        ;
    }
}


void RTCSwitch(uchar switchEn)
{
    ulong i;
    if(switchEn)
    {
        Manage100usEvent = EmptyTask;
        #if(TIMEER_1S_ENABLE != 0)
            memset(timeInf1s,0,sizeof(timeInf1s));
            for(i=0;i<MAX_TIMENUM_1S;i++)
                timeInf1s[i].callback = NULL;
        #endif
    }
    else
    {
        ;
    }
}
#endif


#if(TIMEER_10MS_ENABLE != 0)
uchar StartTime10ms(uchar timeNumber, TIMER_WORDTYPE timeLen, uchar mode, PEFUNCTION callBack);
uchar CloseTime10ms(uchar timeNumber);
void TimerManage10ms(void);
/*************************************************************
Function: �������Ϊ5MS�Ķ�ʱ����
Input: TimeNumber����ʱ����  TimeLen����ʱʱ�䳤��  CallBack���ص�����
Output: 0���ɹ�;1��ʧ��
Application area:  
Explain: 
Modification register:
**************************************************************/
uchar StartTime10ms(uchar timeNumber, TIMER_WORDTYPE timeLen, uchar mode, PEFUNCTION callBack)    
{
    if((timeNumber < MAX_TIMENUM_10MS)&&(timeLen > 0))
    {
        timeInf10ms[timeNumber].number = timeNumber;
        timeInf10ms[timeNumber].timeLen = timeLen;
        timeInf10ms[timeNumber].timeCount = 0;
        timeInf10ms[timeNumber].timerMode = mode;
        timeInf10ms[timeNumber].callback = callBack;
        timeInf10ms[timeNumber].timeswitch = TIMR_ON;
        return(0);
    }
    return(1);
}

/*************************************************************
Function: �رջ���Ϊ5MS�Ķ�ʱ����
Input: TimeNumber����ʱ����
Output: 0���ɹ�;1��ʧ��
Application area:  
Explain: 
Modification register:
**************************************************************/
uchar CloseTime10ms(uchar timeNumber)
{
    if(timeNumber < MAX_TIMENUM_10MS)
    {   
        //timeInf10ms[timeNumber].number = 0;
        timeInf10ms[timeNumber].timeswitch = TIMR_OFF;
        //timeInf10ms[timeNumber].timeLen = 0;
        //timeInf10ms[timeNumber].timeCount = 0;
        //timeInf10ms[timeNumber].callback = NULL;
        return(0);
    }
    return(1);
}

void TimerManage10ms(void)
{
    uchar i;
    //MTRACE("TimerManage10ms\n");
    
    for(i=0;i<MAX_TIMENUM_10MS;i++)
    {
        if(timeInf10ms[i].timeswitch == TIMR_ON)
        {
            timeInf10ms[i].timeCount++;
            if(timeInf10ms[i].timeCount >= timeInf10ms[i].timeLen)
            {
                timeInf10ms[i].timeCount=0;
                if(timeInf10ms[i].callback != NULL)
                {
                    timeInf10ms[i].callback();
                }
                if(timeInf10ms[i].timerMode == TIMER_MODE_ONCE)
                    timeInf10ms[i].timeswitch = TIMR_OFF;
            }       
        }
    }
}
#endif


#if(TIMEER_1S_ENABLE != 0)
uchar StartTime1s(uchar timeNumber, TIMER_WORDTYPE timeLen, uchar mode, PEFUNCTION callBack);
uchar CloseTime1s(uchar timeNumber);
void TimerManage1s(void);
/*************************************************************
Function: �������Ϊ1S�Ķ�ʱ����
Input: TimeNumber����ʱ����  TimeLen����ʱʱ�䳤��  CallBack���ص�����
Output: 0���ɹ�;1��ʧ��
Application area:  
Explain: 
Modification register:
**************************************************************/
uchar StartTime1s(uchar timeNumber, TIMER_WORDTYPE timeLen, uchar mode, PEFUNCTION callBack)  
{
    if((timeNumber < MAX_TIMENUM_1S)&&(timeLen > 0))
    {
        timeInf1s[timeNumber].number = timeNumber;
        timeInf1s[timeNumber].timeLen = timeLen;
        timeInf1s[timeNumber].timeCount = 0;
        timeInf1s[timeNumber].timerMode = mode;
        timeInf1s[timeNumber].callback = callBack;
        timeInf1s[timeNumber].timeswitch = TIMR_ON;
        return(0);
    }
    return(1);
}

/*************************************************************
Function: �رջ���Ϊ1S�Ķ�ʱ����
Input: TimeNumber����ʱ����
Output: 0���ɹ�;1��ʧ��
Application area:  
Explain: 
Modification register:
**************************************************************/
uchar CloseTime1s(uchar timeNumber)
{
    if(timeNumber < MAX_TIMENUM_1S)
    {   
        //timeInf1s[timeNumber].number = 0;
        timeInf1s[timeNumber].timeswitch = TIMR_OFF;
        //timeInf1s[timeNumber].timeLen = 0;
        //timeInf1s[timeNumber].timeCount = 0;
        //timeInf1s[timeNumber].callback = NULL;
        return(0);
    }
    return(1);
}

void TimerManage1s(void)
{
    uchar i;
    
    for(i=0;i<MAX_TIMENUM_1S;i++)
    {
        if(timeInf1s[i].timeswitch == TIMR_ON)
        {
            timeInf1s[i].timeCount++;
            if(timeInf1s[i].timeCount >= timeInf1s[i].timeLen)
            {
                timeInf1s[i].timeCount = 0;
                if(timeInf1s[i].callback != NULL)
                {
                    // TODO: Need check to protect more
                    timeInf1s[i].callback();
                }
                if(timeInf1s[i].timerMode == TIMER_MODE_ONCE)
                    timeInf1s[i].timeswitch = TIMR_OFF;
            }           
        }
    }
}
#endif
#endif

