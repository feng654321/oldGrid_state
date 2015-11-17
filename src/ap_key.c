#define AP_KEYEVENT_GLOBALS
#include "common.h"
#if 0
#define CON_KEYEVENT_AB_CHANGE_TIME 0x4
uchar ucKeyEventMode;
uchar ucKeyEventClrDemandTime;
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)       
uchar ucKeyEventRelayOpenKeytime;
#endif
uchar ucKeyEventABChangeTime;



#if(CONFIG_METER_AREA_MODE_SICHUAN==CONFIG_METER_AREA_MODE)
uchar ucKeyEventABChangeTimeSichuan;

#endif


void KeyEventInit(void)
{
//  ucProgramTime=0;
    FLG_PROGRAM_STATUS=GAL_NO;
    DISPLAY_CHANGE_TO_A_STATUS=GAL_NO;
    DISPLAY_CHANGE_TO_B_STATUS=GAL_NO;
    #if(CONFIG_METER_AREA_MODE_SICHUAN==CONFIG_METER_AREA_MODE)
    DISPLAY_CHANGE_AtoB_STATUS=GAL_NO;
    #endif
    ucKeyStatusEvent.ucData=0;
    ucKeyStatusAll.ucData=0;
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)       
    ucKeyEventRelayOpenKeytime=0;
#endif
    SetKeyEvent(DISPLAY_EVENT_NO);


    ucCommFlgStatusChannel01=0;
    ucCommFlgStatusChannel02=0;
    ucCommFlgStatusChannel03=0;
    ucCommFlgStatusChannel04=0;
    ucCommFlgStatusChannel05=0;
#if(CONFIG_METER_SW_DEBUG_MODE == GAL_YES)
    TestTime1 = 0;
    TestTime2 = 0;
#endif
}

void KeyEventMode(void)
{
    if(GAL_YES==FLG_KEY_UPKEY_DOWNEVENT)
    {
        FLG_KEY_UPKEY_DOWNEVENT=GAL_NO;
        SetKeyEvent(DISPLAY_EVENT_KEYUP);
        AlarmSpeekAlarmClr();
        //AlarmSpeekAlarmCardReadTime(1,0);

    }
    if(GAL_YES==FLG_KEY_DOWNKEY_DOWNEVENT)
    {
        FLG_KEY_DOWNKEY_DOWNEVENT=GAL_NO;
        SetKeyEvent(DISPLAY_EVENT_KEYDOWN);
        AlarmSpeekAlarmClr();
    }
    if(GAL_YES==FLG_KEY_INFOKEY_UPEVENT)
    {
        FLG_KEY_INFOKEY_UPEVENT=GAL_NO;
        // SetKeyEvent(DISPLAY_EVENT_KEYINFO);
        // AlarmSpeekAlarmClr();
    }
    if(GAL_YES==FLG_KEY_PROGRAMKEY_DOWNEVENT)
    {
        FLG_KEY_PROGRAMKEY_DOWNEVENT=GAL_NO;
        SetKeyEvent(DISPLAY_EVENT_KEYPRO);
        AlarmSpeekAlarmClr();
        if((0 == ucProgramTime ) && IfPowerStateOn()) //停电时禁止设置，tzg
        {
            //ucProgramTime=ValueHexFromRam2Bcd(RAM_COEF_PROGRAM_TIME);
            ucProgramTime=CON_PROGRAM_TIME_MAX;
            if(0==ucProgramTime)
            {
                ucProgramTime=5;
            }
            FLG_PROGRAM_STATUS=GAL_YES;
            DISPLAY_CHANGE_TO_B_STATUS=GAL_YES;
            //EventProgramRecordReset();
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
            SpringStartTotalCommRecord(0);
#else
            EventProgramRecordReset();
#endif
        }
        else
        {
            ucProgramTime=0;
            FLG_PROGRAM_STATUS=GAL_NO;
            DISPLAY_CHANGE_TO_A_STATUS=GAL_YES;
            // EventProgramRecordReset();
        }
        //SaveProgramTime();
    }
    if( ucKeyEventMode != RSOFT_RTC_SECOND)
    {
        ucKeyEventMode=RSOFT_RTC_SECOND;
        if(ucProgramTime>0)
        {
            if((KEY_STATUS_DOWN== FLG_KEY_UP_STATUS)
                &&(KEY_STATUS_UP== FLG_KEY_PROGRAM_STATUS)
                &&(KEY_STATUS_DOWN== FLG_KEY_DOWN_STATUS))
                //&&(KEY_STATUS_UP== FLG_KEY_INFO_STATUS))
            {
                ucKeyEventClrDemandTime++;
                
                if(ucKeyEventClrDemandTime>10)
                {
                    ucKeyEventClrDemandTime=10;
                }
            }
            else
            {
                ucKeyEventClrDemandTime=0;
            }
        }
        else
        {
            ucKeyEventClrDemandTime=0;
        }
        switch(ucKeyEventClrDemandTime)
        {
            case 0:
                DISPLAY_FLG_ASK=GAL_NO;
                DISPLAY_FLG_CLR=GAL_NO;
                break;
            case 1:
                DISPLAY_FLG_ASK=GAL_YES;
                DISPLAY_FLG_CLR=GAL_YES;
                break;
            case 2:
                DISPLAY_FLG_ASK=GAL_NO;
                DISPLAY_FLG_CLR=GAL_YES;
                break;
            case 3:
                DemandDataClrAllCurrent();
                AlarmSpeekAlarmCardReadTime(1,00);
                DISPLAY_FLG_ASK=GAL_NO;
                DISPLAY_FLG_CLR=GAL_NO;
                break;
                
        }
        if((KEY_STATUS_DOWN== FLG_KEY_UP_STATUS)
                &&(KEY_STATUS_UP== FLG_KEY_PROGRAM_STATUS)
                &&(KEY_STATUS_UP== FLG_KEY_DOWN_STATUS)
                &&(KEY_STATUS_UP== FLG_KEY_INFO_STATUS))
        {
            ucKeyEventABChangeTime++;
            if(ucKeyEventABChangeTime>10)
                ucKeyEventABChangeTime=10;
            if(CON_KEYEVENT_AB_CHANGE_TIME == ucKeyEventABChangeTime)
            {
                DISPLAY_CHANGE_AB_STATUS=GAL_YES;
            }
        }
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)       
        if(((KEY_STATUS_DOWN== FLG_KEY_UP_STATUS)&&(KEY_STATUS_UP== FLG_KEY_DOWN_STATUS))
            ||((KEY_STATUS_UP== FLG_KEY_UP_STATUS)&&(KEY_STATUS_DOWN== FLG_KEY_DOWN_STATUS)))
        {
            if(ucKeyEventRelayOpenKeytime<100)
            {
                ucKeyEventRelayOpenKeytime++;
            }
            if(3==ucKeyEventRelayOpenKeytime)
            {
                RELAY_OPERATE_FLAG=1;
            }
        }
        else
        {
            ucKeyEventRelayOpenKeytime=0;
            //RELAY_OPERATE_FLAG=0;
        }
#endif      

        #if(CONFIG_METER_AREA_MODE_SICHUAN==CONFIG_METER_AREA_MODE)
        if((KEY_STATUS_DOWN== FLG_KEY_UP_STATUS)&&(KEY_STATUS_DOWN== FLG_KEY_DOWN_STATUS))
        {
            if(ucKeyEventABChangeTimeSichuan<CON_KEYEVENT_AB_CHANGE_TIME)
            {
                ucKeyEventABChangeTimeSichuan++;

                if(ucKeyEventABChangeTimeSichuan>=CON_KEYEVENT_AB_CHANGE_TIME)
                {
                    KeyDisplayAtoBChange();
                }
            }
        }
        else
        {
            ucKeyEventABChangeTimeSichuan=0;
        }
        #endif
    }
}


void KeyEventMode(void)
{
    //if(mesreceive())
    {
        //AlarmSpeekAlarmClr();
        //收到编程状态消息
        if(1)
        {
            //进入编程状态
            ucProgramTime=CON_PROGRAM_TIME_MAX;
            if(0==ucProgramTime)
            {
                ucProgramTime=5;
            }
            FLG_PROGRAM_STATUS=GAL_YES;
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
            SpringStartTotalCommRecord(0);
#else
            EventProgramRecordReset();
#endif
        }
        else
        {
            //退出编程状态
            ucProgramTime = 0;

        }
        FLG_KEY_PROGRAMKEY_DOWNEVENT=GAL_NO;
        SetKeyEvent(DISPLAY_EVENT_KEYPRO);
        AlarmSpeekAlarmClr();
        if((0 == ucProgramTime ) && IfPowerStateOn()) //停电时禁止设置，tzg
        {
            //ucProgramTime=ValueHexFromRam2Bcd(RAM_COEF_PROGRAM_TIME);
            ucProgramTime=CON_PROGRAM_TIME_MAX;
            if(0==ucProgramTime)
            {
                ucProgramTime=5;
            }
            FLG_PROGRAM_STATUS=GAL_YES;
            DISPLAY_CHANGE_TO_B_STATUS=GAL_YES;
            //EventProgramRecordReset();
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
            SpringStartTotalCommRecord(0);
#else
            EventProgramRecordReset();
#endif
        }
        else
        {
            ucProgramTime=0;
            FLG_PROGRAM_STATUS=GAL_NO;
            DISPLAY_CHANGE_TO_A_STATUS=GAL_YES;
            // EventProgramRecordReset();
        }
        //SaveProgramTime();
    }
}
#endif
void KeyEventMode(void)
{
    if(get_program_key_status() == 1)
    {
        if(FLG_PROGRAM_STATUS == GAL_NO)
        {
            FLG_PROGRAM_STATUS = GAL_YES;
            ProgramPointSet(0);
            AlarmSpeekAlarmClr();
        }
    }
    else
    {
        if(FLG_PROGRAM_STATUS == GAL_YES)
        {
            FLG_PROGRAM_STATUS = GAL_NO;
            //ProgramPointSet(1);
            AlarmSpeekAlarmClr();
        }
    }
}

