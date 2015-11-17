
#define AP_TIME_GLOBALS
#include "common.h"

#if 0
void second_change_dis_use()
// when second change ,and display time   ---->drive 
{
//  if((RCURRENT_REFERENCE==8)||(RLCD_DISPLAY_STATUS==DISPLAY_DATE))
   //       RFLAG_DISPLAY_05SEC=1;
}

#if(BOARD_LOWCOST != HARD_WARE)
uchar rtc8025_timevalue[8];

uchar rtc_8025_3time_read()
{
    uchar l,value;
    value=0;
    for(l=0;l<3;l++)
    {
        if(1==ReadCalendarTime(&rtc8025_timevalue[0]))
        {
            value=1;
            l=3;
        }
        else 
        {
            Delay1mS();
        }
    }
    return value;
}
       
void rtc_use()
{
    uchar a;
    uchar b;//,c;
    // a=(RSOFT_RTC_SECOND>>4)*10+(RSOFT_RTC_SECOND&0xf);
    a=OneByteBcdToHex(RSOFT_RTC_SECOND);
    if(a>=59)
    {
        RSOFT_RTC_SECOND=0;
        if(remote_jiehuo_10day!=0) 
            remote_jiehuo_10day=remote_jiehuo_10day-1;  
        if(quanshiya_10day!=0) 
            quanshiya_10day=quanshiya_10day-1;
        if(remote_display_7day!=0)
            remote_display_7day=remote_display_7day-1;
        // a=RSOFT_RTC_MINUTE&0xf0; 
        // a=a>>4;
        // a=a*10;
        // a=a+(RSOFT_RTC_MINUTE&0x0f);
        a=OneByteBcdToHex(RSOFT_RTC_MINUTE);
        if(a>=59)
        {
            RSOFT_RTC_MINUTE=0;
            // a=RSOFT_RTC_HOUR&0xf0;   
            // a=a>>4;
            // a=a*10;
            // a=(0xf&RSOFT_RTC_HOUR)+a;    
            a=OneByteBcdToHex(RSOFT_RTC_HOUR);
            if (a>=23)
            {
                RSOFT_RTC_HOUR=0;
                tingchao_enabled=3;
                // a=RSOFT_RTC_DAY&0xf0;    
                // a=a>>4;
                // a=a*10;
                // a=a+(RSOFT_RTC_DAY&0x0f)+1;
                b=OneByteHexToBcd(OneByteBcdToHex(RSOFT_RTC_DAY)+1);
                if(RSOFT_RTC_WEEK>=6) 
                    RSOFT_RTC_WEEK=0;   
                else 
                    RSOFT_RTC_WEEK=RSOFT_RTC_WEEK+1;
                switch(RSOFT_RTC_MONTH)
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
                            RSOFT_RTC_DAY=1;
                            RSOFT_RTC_MONTH=RSOFT_RTC_MONTH+1;
                            if(RSOFT_RTC_MONTH>0x12)
                            {
                                //RSOFT_RTC_MONTH=1;
                                //a=10*(RSOFT_RTC_YEAR>>4)+(0xf&RSOFT_RTC_YEAR);
                                //a=a+1;
                                RSOFT_RTC_YEAR=OneByteHexToBcd(RSOFT_RTC_YEAR)+1;
                            }
                        }
                        else
                        {
                            RSOFT_RTC_DAY=b;
                        }
                        break;
                    case 0x4:
                    case 0x6:
                    case 0x9:
                    case 0x11: 
                        if (b>0x30)
                        {
                            RSOFT_RTC_DAY=1;
                            b=RSOFT_RTC_MONTH+1;
                            a=b&0x0f;
                            if(a>9) 
                                RSOFT_RTC_MONTH=0x10;
                            else 
                                RSOFT_RTC_MONTH=b;
                        }
                        else 
                            RSOFT_RTC_DAY=b;
                        break;
                    case 0x2:
                        a=OneByteBcdToHex(RSOFT_RTC_YEAR);
                        a=a%4;
                        if(a==0)    
                        {
                            if(b>0x29)
                            {
                                RSOFT_RTC_DAY=1;
                                RSOFT_RTC_MONTH=RSOFT_RTC_MONTH+1;
                            }
                            else 
                                RSOFT_RTC_DAY=b;
                        }
                        else
                        {
                            if(b>0x28)
                            {
                                RSOFT_RTC_DAY=1;
                                RSOFT_RTC_MONTH=RSOFT_RTC_MONTH+1;
                            }
                            else 
                                RSOFT_RTC_DAY=b;
                        }
                        break;  
                    }
                }
            else
            {
                a=a+1;
                RSOFT_RTC_HOUR=OneByteHexToBcd( a);
            }
        }
        else
        {
            a=a+1;
            RSOFT_RTC_MINUTE=OneByteHexToBcd(a);
        }   
    }
    else
    {
        a=a+1;
        RSOFT_RTC_SECOND=OneByteHexToBcd(a);
    }
}
#endif
/*
// fm copy
void rtc()
{
    static uchar second_pointer,num;
    uchar c;
    //uchar b;
    uchar baojing_use;
    c=0;
    if(second_rtc_point_timera0!=second_pointer)
    {
        second_pointer=second_rtc_point_timera0;
        uiPluseRestTimes=uiPluseRestTimes+1;
        if(uiPluseRestTimes>uiMeterPluseResetDelaySet)
        {
            InitADMode(GAL_YES, GAL_NO);
        }
        second_change_dis_use();
        rtc_use();      
        if((RSOFT_RTC_SECOND==0x30)&&((0xf&RSOFT_RTC_MINUTE)==0)) 
            c=1;  // 10 minute dui shi
        if(qingqiuduishi_rtc==1) 
        {
            c=1;
            qingqiuduishi_rtc=0;
        }

        // time_to_bianchengqian();
        baojing_use=1;
        if(0== TestSecondMinuteHourDayMonthYear(&RSOFT_RTC_SECOND,&RSOFT_RTC_DAY))
        {
            c=1;
            baojing_use=0;
        }
        if(c==1)
        {
            if(1==rtc_8025_3time_read())
            {
                if(1==TestSecondMinuteHourDayMonthYear(&rtc8025_timevalue[0],&rtc8025_timevalue[4]))
                {
                    if(0==CompareDateTime(3,&rtc8025_timevalue[0],&rtc8025_timevalue[4]))// <3second
                        baojing_use=0;
                    if((0==CompareDateTime(1,&rtc8025_timevalue[0],&rtc8025_timevalue[4]))||(num>20))// <=1 20num--->do
                    {
                        // move_rtc8025_to_softrtc();
                        num=0;
                    }
                    else 
                        num=num+1;
                }
                else 
                    baojing_use=0;
            }
            else 
                baojing_use=0;
        }
        AlarmDoLedSpeek(baojing_use,TYPE_ALARM_TIME_ERR);
        RSOFT_RTC_WEEK=WeekFromDayMonthYear(&RSOFT_RTC_DAY);
        if(baojing_use==0)  
        {
            // err_time_envent();
        // copy_ram_to_fm(R_SOFT_SECOND,7,R_SOFT_SECOND);
            
        }
    }
}
*/
void zhongduan_8025_second_set()
{
}
void zhongduan_8025_second()// power down
{
//
// ting dian rtc  wei hu
second_rtc_point_timerb1=second_rtc_point_timerb1+1;
}

uchar   second_tingdian;
void rtc_tingdian()
{
// uchar a;
// uchar b,c;
// uchar baojing_use;
if(second_rtc_point_timerb1!=second_tingdian)
    {
        second_tingdian=second_rtc_point_timerb1;
            second_change_dis_use();
#if(BOARD_LOWCOST != HARD_WARE)
            rtc_use();
#endif
// bu shi zhong------------------>start
//      if(numlm75second<3600)
//              numlm75second= numlm75second+1;
// bu shi zhong------------------>end        
      }
}



UN_U8_PARAM ucKeyTempPer;
UN_U8_PARAM ucKeyTempNext;
UN_U8_PARAM ucKeyStatus;
#define rflag_key_prog_status ucKeyStatus.Bits.b0        
#define rflag_key_per_status ucKeyStatus.Bits.b1       
#define rflag_key_prog_envent_up ucKeyStatus.Bits.b2     
#define rflag_key_per_envent_up ucKeyStatus.Bits.b3    
#define rflag_key_prog_envent_down ucKeyStatus.Bits.b4   
#define rflag_key_per_envent_down ucKeyStatus.Bits.b5   
#define rflag_key_next_status ucKeyStatus.Bits.b6
#define rflag_key_next_envent_up ucKeyStatus.Bits.b7

#define key_value_per ucKeyTempPer.ucData    
#define key_value_next ucKeyTempNext.ucData    

UN_U8_PARAM ucTempValueKeyUp;
UN_U8_PARAM ucTempValueKeyDOWN;
UN_U8_PARAM ucTempValueKeyINFO;
UN_U8_PARAM ucTempValueKeyPROGRAM;

uchar GetKeyStatus(void)
{
    return (ucKeyStatusAll.ucData);
}


uchar rKeyStatusEvent;
uchar  PopKeyEvent(void)
{
    /*uchar uctemp;
    uctemp = rKeyStatusEvent;
    rKeyStatusEvent = DISPLAY_EVENT_NO;
    return uctemp;*/
    return DISPLAY_EVENT_COMMDISPLAY;
}

void SetKeyEvent(uchar ucEvent)
{
    rKeyStatusEvent=ucEvent;
    
    if(DISPLAY_EVENT_NO !=ucEvent)
    {
        if(ucEvent<DISPLAY_EVENT_REMOTEOPEN)
        {
            uiBackLightTime=LCD_BACKLIGHT_TIME_EVENT;
        }
        else
        {
            uiBackLightTime=2*GetShowAutoDisplay1Cycle();
        }
        if(uiBackLightTime)
        {
            SetLedBackLight();
        }
        uiWakeUpAllTimes = WAKEUP_TIME_EVENT;
    }
}


void Time10mSInterrupt(void)
{
    
    ucTime500mSCount++;
    if(ucTime500mSCount>49)
    {
        ucTime500mSCount=0;
        // display_flash=1;
    }
//  RefreshHc595();

    if(0==uiPluseTime1)  
    {
        ClrPulseOut1();
        uiPluseTime1 = 0xffff;
    }
    else if(uiPluseTime1 != 0xffff)
    {
        uiPluseTime1--;
    }

    // AA  上翻键处理  AA
    ucTempValueKeyUp.ucData=ucTempValueKeyUp.ucData<<1;
    ucTempValueKeyUp.Bits.b0=GetUpKeyStatus();
    switch(ucTempValueKeyUp.bit4.bLow4)
    {
        case KEY_UP_MAP:
            if(KEY_STATUS_UP != FLG_KEY_UP_STATUS)
            {
                FLG_KEY_UP_STATUS=KEY_STATUS_UP;
                FLG_KEY_UPKEY_UPEVENT=GAL_YES;
            }
            break;
        case KEY_DOWN_MAP:
            if(KEY_STATUS_DOWN != FLG_KEY_UP_STATUS)
            {
                FLG_KEY_UP_STATUS=KEY_STATUS_DOWN;
                FLG_KEY_UPKEY_DOWNEVENT=GAL_YES;
            }
            break;
        default:
            break;
    }
    // AA  下翻键处理  AA
    ucTempValueKeyDOWN.ucData=ucTempValueKeyDOWN.ucData<<1;
    ucTempValueKeyDOWN.Bits.b0=GetDownKeyStatus();
    switch(ucTempValueKeyDOWN.bit4.bLow4)
    {
        case KEY_UP_MAP:
            if(KEY_STATUS_UP != FLG_KEY_DOWN_STATUS)
            {
                FLG_KEY_DOWN_STATUS=KEY_STATUS_UP;
                FLG_KEY_DOWNKEY_UPEVENT=GAL_YES;
            }
            break;
        case KEY_DOWN_MAP:
            if(KEY_STATUS_DOWN != FLG_KEY_DOWN_STATUS)
            {
                FLG_KEY_DOWN_STATUS=KEY_STATUS_DOWN;
                FLG_KEY_DOWNKEY_DOWNEVENT=GAL_YES;
            }
            break;
        default:
            break;
    }
    // AA  编辑键处理  AA
    ucTempValueKeyINFO.ucData=ucTempValueKeyINFO.ucData<<1;
    ucTempValueKeyINFO.Bits.b0=GetInfoKeyStatus();
    switch(ucTempValueKeyINFO.bit4.bLow4)
    {
        case KEY_UP_MAP:
            if(KEY_STATUS_UP != FLG_KEY_INFO_STATUS)
            {
                FLG_KEY_INFO_STATUS=KEY_STATUS_UP;
                FLG_KEY_INFOKEY_UPEVENT=GAL_YES;
            }
            break;
        case KEY_DOWN_MAP:
            if(KEY_STATUS_DOWN != FLG_KEY_INFO_STATUS)
            {
                // SetKeyEvent(DISPLAY_EVENT_KEYINFO);
                FLG_KEY_INFO_STATUS=KEY_STATUS_DOWN;
                FLG_KEY_INFOKEY_DOWNEVENT=GAL_YES;
            }
            break;
        default:
            break;
    }

    if(IfPowerStateOn())  //for Bug #1472 by centry
    {
        // AA  编程键处理  AA
        ucTempValueKeyPROGRAM.ucData=ucTempValueKeyPROGRAM.ucData<<1;
        ucTempValueKeyPROGRAM.Bits.b0=GetProgramKeyStatus();
        switch(ucTempValueKeyPROGRAM.bit4.bLow4)
        {
            case KEY_UP_MAP:
                if(KEY_STATUS_UP != FLG_KEY_PROGRAM_STATUS)
                {
                    FLG_KEY_PROGRAM_STATUS=KEY_STATUS_UP;
                    FLG_KEY_PROGRAMKEY_UPEVENT=GAL_YES;
                }
                break;
            case KEY_DOWN_MAP:
                if(KEY_STATUS_DOWN != FLG_KEY_PROGRAM_STATUS)
                {
                    // SetKeyEvent(DISPLAY_EVENT_KEYPRO);
                    FLG_KEY_PROGRAM_STATUS=KEY_STATUS_DOWN;
                    FLG_KEY_PROGRAMKEY_DOWNEVENT=GAL_YES;
                }
                break;
            default:
                break;
        }
    }
    
    // AA  继电器操作部分-------->Start    AA   
#if(CONFIG_METER_RELAY_MODE_INSIDE == CONFIG_METER_RELAY_MODE)
    if(uiRelayStatusChangeDelayTime)
    {
        uiRelayStatusChangeDelayTime--;
    }
    if(0==uiRelayStatusChangeDelayTime)
    {
        RelayStatusHolding();
    }
#endif
#if(CONFIG_METER_RELAY_MODE_OUTSIDE== CONFIG_METER_RELAY_MODE)
    // ljc 20100716  start
    if(0x01 & RAM[RAM_CHARACTER_METER_RUN])
    {
        if(uiRelayStatusChangeDelayTime<CON_RELAY_STATUS_CHANGE_START_TIME_10MS)
        {
            if(GAL_YES==ucRelayOutsideOpen)
            {
                SetRelayControlOn();
            }
            else
            {
                ClrRelayControlOn();
            }
        }
        else
        {
            ClrRelayControlOn();
        }
    }
    else
    {
        if(GAL_YES==ucRelayOutsideOpen)
        {
            SetRelayControlOn();
        }
        else
        {
            ClrRelayControlOn();
        }
    }
    // ljc 20100716  end
    if(uiRelayStatusChangeDelayTime<CON_RELAY_STATUS_MAX_TIME_10MS)
    {
        uiRelayStatusChangeDelayTime++;
    }
#endif      
    // AA  继电器操作部分-------->End   AA  
#if(CONFIG_METER_AREA_MODE_SHANGHAI!=CONFIG_METER_AREA_MODE)
    if(ucAlarmSpeekTempTimer>200)
    {
        ucAlarmSpeekTempTimer=0xff;
        if(ucAlarmSpeekCardReadSpeek)
        {
            ucAlarmSpeekCardReadSpeek--;
        }
    }
    ucAlarmSpeekTempTimer++;
    if(ucAlarmSpeekTempTimer<100)
    {
        if((uiAlarmSpeekAlarmTime)||(ucAlarmSpeekCardReadSpeek))
        {
            SetSpeekAlarm();
        }
    }
    else
#endif
    {
        ClrSpeekAlarm();
    }
    if(PowerOffWaitTimeStep10mS)
    {
        PowerOffWaitTimeStep10mS--;
    }
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
        if( cardTime ) 
        {
            cardTime--;
        }
        if( esamTime )
        {
            esamTime--;
        }
        if(0!=uiAlarmDisplayCardReadTimes)
        {
            uiAlarmDisplayCardReadTimes--;
        }
#endif
    if(ucProgramFlashWait)
    {
        ucProgramFlashWait--;
    }
}


#if 0
void Time100uSInterrupt(void)
{
    if(uiTime100usCount<20000)
            uiTime100usCount++;
    
    if(0==uiPluseTime1)  
    {
        ClrPulseOut1();
    }
    else
    {
        uiPluseTime1--;
    }
#if 0   
    if(0==uiPluseTime2)  
    {
        ClrPulseOut2();
    }
    else
    {
        uiPluseTime2--;
    }
    
    if(0==uiPluseTime3)  
    {
        ClrPulseOut3();
    }
    else
    {
        uiPluseTime3--;
    }
    
    if(0==uiPluseTime4)  
    {
        ClrPulseOut4();
    }
    else
    {
        uiPluseTime4--;
    }
    if(0==uiPluseTime5)  
    {
        ClrPulseOut5();
    }
    else
    {
        uiPluseTime5--;
    }
#endif
    if(0==uiPluseCFKwh)  
    {
        ClrPulseCFKwh();
    }
    else
    {
        uiPluseCFKwh--;
    }

    if(0==uiPluseCFkvarh)  
    {
        ClrPulseCFKvarh();
    }
    else
    {
        uiPluseCFkvarh--;
    }
    // RefreshHc595();
}
#endif









void Start10msInt(void)
{
     StartTime10ms(T10MSID_10MS_INT, 1, TIMER_MODE_CONTINUE, &Time10mSInterrupt);
     //Manage100usEvent=&Time100uSInterrupt;
}


void TimeDeal(uchar ucRunType)
{
    static uchar ucTimeDealSecond=0;
    if((ucTimeDealSecond != RSOFT_RTC_SECOND)&&(GAL_YES==ucRunType))
    {
        ucTimeDealSecond = RSOFT_RTC_SECOND;
        if((1==TestSecondMinuteHourDayMonthYear(&RSOFT_RTC_SECOND, &RSOFT_RTC_DAY)))
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_TIME_ERR);
            if(GAL_YES==ucRunType)
            {
                SetCurrentTime();
            }
        }
        else
        {
            if(GAL_YES==ucRunType)
            {
                AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_TIME_ERR);
            }
        }
    }
    
}
uchar ucTimeOneSecondChangeSecond;
uchar ucTimeOneSecondChangeMinute;
void TimeOneSecondChange(void)
{
    uchar ucTemp;
    u16 uiData;
    if(ucTimeOneSecondChangeSecond != RSOFT_RTC_SECOND)
    {
        ucTimeOneSecondChangeSecond = RSOFT_RTC_SECOND;
        RAM[RAM_CURRENT_METER_STATUS02]=((0x07&status_5460_0)<<4) +(0x07&(status_5460_0>>4));
        if((status_5460_0&0x80)>0)
        {
            FLG_REVERSEKW_ALL_STATUS=1;
        }
        else
        {
            FLG_REVERSEKW_ALL_STATUS=0;
        }
        if((status_5460_0&0x08)>0)
        {
            FLG_REVERSEKVAR_ALL_STATUS=1;
        }
        else
        {
            FLG_REVERSEKVAR_ALL_STATUS=0;
        }

        if(0==ucProgramTime)
        {
            FLG_PROGRAM_STATUS=GAL_NO;
/*      //ZD 内表不涉及到PLC模块，此段程序不用
#if(CONFIG_METER_NO2COMM_MODE_PLC==CONFIG_METER_NO2COMM_MODE)
    #if(CONFIG_METER_TYPE_SD39C==CONFIG_METER_TYPE)
            SetPlcMacAddrEnable(GAL_NO);
    #endif
#endif
*/
        }
        else
        {
            FLG_PROGRAM_STATUS=GAL_YES;
/*      //ZD 内表不涉及PLC模块，此段程序不用
#if(CONFIG_METER_NO2COMM_MODE_PLC==CONFIG_METER_NO2COMM_MODE)
    #if(CONFIG_METER_TYPE_SD39C==CONFIG_METER_TYPE)
            SetPlcMacAddrEnable(GAL_YES);
    #endif
#endif
*/
        }
        if(ucTimeOneSecondChangeMinute != RSOFT_RTC_MINUTE)
        {
            //EventMinTimeAdd();
            
            ucTimeOneSecondChangeMinute=RSOFT_RTC_MINUTE;
#if(CONFIG_METER_AREA_MODE_SHANGHAI==CONFIG_METER_AREA_MODE)    //tzg
            //过零点
            if((RSOFT_RTC_HOUR== 0) && (RSOFT_RTC_MINUTE == 0))
            {
                ClearAllPasswordErrCount();
            }
#endif            
/*    //ZD 内表不涉及预付费，此段程序不用
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
            if((0==RSOFT_RTC_MINUTE)&&(0==RSOFT_RTC_HOUR))
            {
                ClearAllFarCtlCount();
            }
#endif
*/
            if(ucProgramTime >0)
            {
                ucProgramTime--;
                if(ucProgramTime == 0)
                    SaveProgramTime();
            }
            //SaveProgramTime();
            if(20!=TestZeroNum(&RAM[RAM_PASSWORD_LOCK_TIME_START], 20))
            {
                for(ucTemp=0;ucTemp<10;ucTemp++)
                {
                    memcpy((uchar *)&uiData, &RAM[RAM_PASSWORD_LOCK_TIME_START+ucTemp*2], 2);
                    if(0!=uiData)
                    {
                        uiData--;
                        memcpy(&RAM[RAM_PASSWORD_LOCK_TIME_START+ucTemp*2], (uchar *)&uiData, 2);
                        if(0==uiData)
                        {
                            RAM[RAM_PASSWORD_ERR_COUNT_START+ucTemp]=0;
                        }
                    }
                }
                //WriteDataDirect(&RAM[RAM_PASSWORD_ERR_COUNT_START], EPL_PASSWORD_ERR_COUNT_START, 33);
                
            }

            #if(CONFIG_METER_AREA_MODE_SICHUAN==CONFIG_METER_AREA_MODE)
            PowerOverTimeCount();
            #endif  
        }
		//ZD 内表没有预付费功能，此段程序不用
//#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
//        RelayCount();
//        FLG_RELAYCOMMAND_STATUS=RELAY_COMMAND_STATE_FLAG;
//        FLG_RELAYPREALARM_STATUS=RELAY_ORDER_ALARM_FLAG;
//        FLG_METERPREPAY_TYPE=02;
//        FLG_RELAY_STATUS=RELAY_STATE_FLAG;
//#else
        FLG_RELAYCOMMAND_STATUS=GAL_NO;
        FLG_RELAYPREALARM_STATUS=GAL_NO;
        FLG_METERPREPAY_TYPE=0;
        FLG_RELAY_STATUS=0;
//#endif
        if(0!= uiAlarmSpeekAlarmTime)
        {
            uiAlarmSpeekAlarmTime--;
        }
        if(0  !=  uiBackLightTime)
        {
            uiBackLightTime--;
        }
		//ZD 内表没有预付费功能，此段程序不用
/*
#if(CONFIG_METER_PREPAY_MODE!=CONFIG_METER_PREPAY_MODE_DISABLE)
        if(0 !=LCDBackTime)
        {
            LCDBackTime--;
        }
#endif
*/
		//ZD 内表没有预付费功能，此段程序不用
//#if(CONFIG_METER_PREPAY_MODE!=CONFIG_METER_PREPAY_MODE_DISABLE)
//        if(((uiBackLightTime)||(LCDBackTime)||(ucAlarmErrBlackLightHave))&&(CON_POWER_STATUS_USE_WAKEUPBAT != FLG_POWER_STATUS))
//#else
        if(((uiBackLightTime)||(ucAlarmErrBlackLightHave))&&(CON_POWER_STATUS_USE_WAKEUPBAT != FLG_POWER_STATUS))
//#endif
        //ZD 内表没有背光，此段程序不用
/*
        {
            SetLedBackLight();
        }
        else
        {
            ClrLedBackLight();
        }*/

        uiPluseRestTimes=uiPluseRestTimes+1;
        if(uiPluseRestTimes>uiMeterPluseResetDelaySet)
        {
            InitADMode(GAL_YES, GAL_NO);        //初始化计量芯片
            PowerClacInit();
        }
        //RefreshHc595();
		//ZD 内表没有预付费功能，此段程序不用
/*
#if(CONFIG_METER_PREPAY_MODE == CONFIG_METER_PREPAY_MODE_LOCATION)
        if(readCardTime>0)
        {
            readCardTime--;
        }
        else
        {
            readCardStatus=0;
            / *Start of lgw on 2009-3-17 9:4 pax* /
            if(taskName == TASK_CARD_OPERATE)
            {
                EndPrepayTask();
                DisplayReadCardState(READ_CARD_ERROR);
                //DisplayReadICErrorCode(CARD_ERROR_TYPE03);
            }
            / *End of lgw on 2009-3-17 9:4 pax* /
        }
#endif      */

        //ZD 内表没有预付费功能，此段程序不用
/*
#if(CONFIG_METER_RELAY_MODE_DISABLE !=CONFIG_METER_RELAY_MODE)
        relayCheckFlag = 1;
#endif
*/
    }
    TimeOneSecondPowerOffChange();
}


uchar ucTimeOneSecondPowerOffChangeSecond;
void TimeOneSecondPowerOffChange(void)
{
    if(ucTimeOneSecondPowerOffChangeSecond != RSOFT_RTC_SECOND)
    {
        ucTimeOneSecondPowerOffChangeSecond = RSOFT_RTC_SECOND;
        
        if(0!=ucCommFlgStatusChannel01)
            ucCommFlgStatusChannel01--;
        if(0!=ucCommFlgStatusChannel02)
            ucCommFlgStatusChannel02--;
        if(0!=ucCommFlgStatusChannel03)
            ucCommFlgStatusChannel03--;
        if(0!=ucCommFlgStatusChannel04)
            ucCommFlgStatusChannel04--;
        if(0!=ucCommFlgStatusChannel05)
            ucCommFlgStatusChannel05--;
        if(0 != uiWakeUpAllTimes)
        {  
            uiWakeUpAllTimes--;
        }
		//ZD 内表没有预付费功能，此段程序不用
//#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
//        FLG_RELAYCOMMAND_STATUS=RELAY_COMMAND_STATE_FLAG;
//        FLG_RELAYPREALARM_STATUS=RELAY_ORDER_ALARM_FLAG;
//        FLG_METERPREPAY_TYPE=02;
//        FLG_RELAY_STATUS=RELAY_STATE_FLAG;
//#else
        FLG_RELAYCOMMAND_STATUS=0;
        FLG_RELAYPREALARM_STATUS=0;
        FLG_METERPREPAY_TYPE=0;
        FLG_RELAY_STATUS=0;
//#endif
    }   
}

#else

//uchar ucTimeOneSecondChangeSecond;
uchar ucTimeOneSecondChangeMinute;
void TimeOneSecondChange(void)
{
    uchar ucTemp;
    u16 uiData;
    //if(ucTimeOneSecondChangeSecond != RSOFT_RTC_SECOND)
    {
        //ucTimeOneSecondChangeSecond = RSOFT_RTC_SECOND;
        RAM[RAM_CURRENT_METER_STATUS02]=((0x07&status_5460_0)<<4) +(0x07&(status_5460_0>>4));
        if((status_5460_0&0x80)>0)
        {
            FLG_REVERSEKW_ALL_STATUS=1;
        }
        else
        {
            FLG_REVERSEKW_ALL_STATUS=0;
        }
        if((status_5460_0&0x08)>0)
        {
            FLG_REVERSEKVAR_ALL_STATUS=1;
        }
        else
        {
            FLG_REVERSEKVAR_ALL_STATUS=0;
        }

        if(ucTimeOneSecondChangeMinute != RSOFT_RTC_MINUTE)
        {            
            ucTimeOneSecondChangeMinute=RSOFT_RTC_MINUTE;
#if(CONFIG_METER_AREA_MODE_SHANGHAI==CONFIG_METER_AREA_MODE)
            //过零点
            if((RSOFT_RTC_HOUR== 0) && (RSOFT_RTC_MINUTE == 0))
            {
                ClearAllPasswordErrCount();
            }
#endif            
            if(20!=TestZeroNum(&RAM[RAM_PASSWORD_LOCK_TIME_START], 20))
            {
                for(ucTemp=0;ucTemp<10;ucTemp++)
                {
                    memcpy((uchar *)&uiData, &RAM[RAM_PASSWORD_LOCK_TIME_START+ucTemp*2], 2);
                    if(0!=uiData)
                    {
                        uiData--;
                        memcpy(&RAM[RAM_PASSWORD_LOCK_TIME_START+ucTemp*2], (uchar *)&uiData, 2);
                        if(0==uiData)
                        {
                            RAM[RAM_PASSWORD_ERR_COUNT_START+ucTemp]=0;
                        }
                    }
                }
                //WriteDataDirect(&RAM[RAM_PASSWORD_ERR_COUNT_START], EPL_PASSWORD_ERR_COUNT_START, 33);

            }

        }
        uiPluseRestTimes=uiPluseRestTimes+1;
        if(uiPluseRestTimes>uiMeterPluseResetDelaySet)
        {
            InitADMode(GAL_YES, GAL_NO);        //初始化计量芯片
            PowerClacInit();
        }
    }
}
void SetKeyEvent(uchar ucEvent)
{
}
uchar  PopKeyEvent(void)
{
    return DISPLAY_EVENT_COMMDISPLAY;
}

void TimeDeal(uchar ucRunType)
{
    static uchar ucTimeDealSecond=0;
    if((ucTimeDealSecond != RSOFT_RTC_SECOND)&&(GAL_YES==ucRunType))
    {
        ucTimeDealSecond = RSOFT_RTC_SECOND;
        if((1==TestSecondMinuteHourDayMonthYear(&RSOFT_RTC_SECOND, &RSOFT_RTC_DAY)))
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_TIME_ERR);
            if(GAL_YES==ucRunType)
            {
                SetCurrentTime();
            }
        }
        else
        {
            if(GAL_YES==ucRunType)
            {
                AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_TIME_ERR);
            }
        }
    }

}

#endif

