#define AP_ALARM_GLOBALS
#include "common.h"

//error display
const ERROR_DISPLAY_INFORMATION errorDisplayInformation[ALARM_ERR_DISPLAY_NUM]=
{
	{0xffffff01, TYPE_LCD_DISPLAY_ERR_CONTROL        ,0x00,   0x01},
	{0xffffff02, TYPE_LCD_DISPLAY_ERR_ESAM           ,0x00,   0x02},
	{0xffffff03, TYPE_LCD_DISPLAY_ERR_CARD           ,0x00,   0x03},
	{0xffffff04, TYPE_LCD_DISPLAY_ERR_BATTIMELOW     ,0x00,   0x04},
	{0xffffff05, TYPE_LCD_DISPLAY_ERR_PROGRAMDATA    ,0x00,   0x05},
	{0xffffff06, TYPE_LCD_DISPLAY_ERR_HARD_ERR       ,0x00,   0x06},
	{0xffffff07, TYPE_LCD_DISPLAY_ERR_TIME_ERR       ,0x00,   0x07},
#if(CONFIG_METER_FACTORY_MODE_ENABLE == CONFIG_METER_FACTORY_MODE)
	{0xffffff08, TYPE_LCD_DISPLAY_ERR_ADC_ERR        ,0x00,   0x31},
	{0xffffff09, TYPE_LCD_DISPLAY_ERR_EPL_ERR        ,0x00,   0x32},
	{0xffffff0a, TYPE_LCD_DISPLAY_ERR_FLASH_ERR      ,0x00,   0x33},
	{0xffffff0a, TYPE_LCD_DISPLAY_ERR_RTC_ERR        ,0x00,   0x33},
#endif
};
  
 
//alarm display
const ERROR_DISPLAY_INFORMATION alarmDisplayInformation[ALARM_ALARM_DISPLAY_NUM]=
{
	{0xffffff11, TYPE_LCD_DISPLAY_ALARM_OVERPOWER,                   0x00,   0x51},
	{0xffffff12, TYPE_LCD_DISPLAY_ALARM_UNBALANCESEVERITYCURRENT,    0x00,   0x52},
	{0xffffff13, TYPE_LCD_DISPLAY_ALARM_OVERVOLTAGE,                 0x00,   0x53},
	{0xffffff14, TYPE_LCD_DISPLAY_ALARM_OVERTOTALCOS,                0x00,   0x54},
	{0xffffff15, TYPE_LCD_DISPLAY_ALARM_OVERDEMADNKW,                0x00,   0x55},
#if ((CONFIG_METER_AREA_MODE_QINGHAI == CONFIG_METER_AREA_MODE) && (GAL_YES == CONFIG_METER_MULTI_FUNCTION))
	{0xffffff16, TYPE_LCD_DISPLAY_ALARM_UNBALANCECURRENT,            0x00,   0x56},
#else
	{0xffffff16, TYPE_LCD_DISPLAY_ALARM_REVERSEKW_ALL,               0x00,   0x56},
#endif	
};

void AlarmDisplayLcdDataInit(void)
{
    errorDisplaycurrentItem = 0;
    alarmDisplaycurrentItem = 0;
}
void GetAlarmDisplayLcdData(uchar *ucReturnBuffer,uchar ucDataId,uchar ucType)
{
    uchar ucTemp;
    uchar ucCount;
    
    if(CON_DISPLAY_ALARM_DATATYPE_ERR==ucType)
    {
        ucCount=sizeof(errorDisplayInformation)/sizeof(ERROR_DISPLAY_INFORMATION);
        for(ucTemp=0;ucTemp<ucCount;ucTemp++)
        {
            if(ucDataId==(errorDisplayInformation[ucTemp].id&0xff))
            {
                ucReturnBuffer[6]=errorDisplayInformation[ucTemp].ucErrShow;
                ucTemp=0xf0;
                break;
            }
        }
    }
    else
    {
        ucCount=sizeof(alarmDisplayInformation)/sizeof(ERROR_DISPLAY_INFORMATION);
        for(ucTemp=0;ucTemp<ucCount;ucTemp++)
        {
            if(ucDataId==(alarmDisplayInformation[ucTemp].id&0xff))
            {
                ucReturnBuffer[6]=alarmDisplayInformation[ucTemp].ucErrShow;
                ucTemp=0xf0;
                break;
            }
        }
    }
    if(0xf0==ucTemp)
    {
        ucTemp=ucReturnBuffer[6];
        
        ucReturnBuffer[7]=((ucTemp&0x0f))+0x30;
        ucReturnBuffer[6]=((ucTemp&0xf0)>>4)+0x30;
        ucReturnBuffer[5] ='-';         
        ucReturnBuffer[4]='r';  
        ucReturnBuffer[3]='r';  
        ucReturnBuffer[2]='E';  
        ucReturnBuffer[1] =' ';         
        ucReturnBuffer[0] =' ';     
    }
    else
    {
        ucReturnBuffer[7]='5';
        ucReturnBuffer[6]='0';
        ucReturnBuffer[5] ='-';         
        ucReturnBuffer[4]='r';  
        ucReturnBuffer[3]='r';  
        ucReturnBuffer[2]='E';  
        ucReturnBuffer[1] =' ';         
        ucReturnBuffer[0] =' ';     
    }
}

uchar SearchErrorDisplayInformation(ulong *id, uchar *idSerialNumber)
{
    uchar i,ucErrDefNum;
    uchar ucType;
    
#if(CONFIG_METER_AREA_MODE_SHANGHAI==CONFIG_METER_AREA_MODE)
    return 0xff;
#else

    //uchar flag;
    //flag=0;
    ucErrDefNum = sizeof(errorDisplayInformation)/sizeof(ERROR_DISPLAY_INFORMATION);
    //while(!flag)
    {
        for(i=errorDisplaycurrentItem; i<ucErrDefNum; i++)
        {
            ucType = errorDisplayInformation[i].errorType;
            if(ucAlarmStatusLcdError[ucType>>3] & 1<<(ucType&0x7))
            {
                errorDisplaycurrentItem = i+1;
                *id = errorDisplayInformation[i].id;
                *idSerialNumber = errorDisplayInformation[i].idSerialNumber;
                //flag = 1;
                break;
            }
        }
        if(i==ucErrDefNum)
        {
            i=0xff;
            errorDisplaycurrentItem = 0;
            //flag = 1;
        }
    }

    return i;
#endif
}

uchar SearchAlarmDisplayInformation(ulong *id, uchar *idSerialNumber)
{
    uchar i,ucErrDefNum;
    uchar ucType;
    
#if(CONFIG_METER_AREA_MODE_SHANGHAI==CONFIG_METER_AREA_MODE)
    return 0xff;
#else

    ucErrDefNum = sizeof(alarmDisplayInformation)/sizeof(ERROR_DISPLAY_INFORMATION);
    for(i=alarmDisplaycurrentItem;i<ucErrDefNum;i++)
    {
        ucType = alarmDisplayInformation[i].errorType;
        if(ucAlarmStatusLcdDisplay[ucType>>3] & 1<<(ucType&0x7))
        {
            alarmDisplaycurrentItem = i+1;
            *id = alarmDisplayInformation[i].id;
            *idSerialNumber = alarmDisplayInformation[i].idSerialNumber;
            break;
        }
    }
    if(i==ucErrDefNum)
    {
        i=0xff;
        alarmDisplaycurrentItem = 0;
    }

    return i;
#endif
}
void AlarmParaInit(void)
{
    //ReadCoefDataWithCheck(EPL_COEF_ALARM_SPEEK, 20, &RAM[RAM_COEF_ALARM_SPEEK], 0);
#if(CON_ALARM_LEDGREEN_ENABLE == GAL_YES)
    memset(&RAM[RAM_COEF_ALARM_LEDGREEN],0xFF,CON_ALARM_TYPE_BYTE_MAX);
#endif
}

void AlarmInit(void)
{
    memset(&(ucAlarmStatusSpeek[0]),0x00, CON_ALARM_TYPE_BYTE_MAX);
    memset(&ucAlarmStatusSpeekLast[0],0x00,sizeof(ucAlarmStatusSpeekLast));
#if(CON_ALARM_LEDGREEN_ENABLE == GAL_YES)
    memset(&ucAlarmStatusLedGreen[0],0x00,CON_ALARM_TYPE_BYTE_MAX);
#endif
    memset(&ucAlarmStatusLedYellow[0],0x00,CON_ALARM_TYPE_BYTE_MAX);
    memset(&ucAlarmStatusLcdDisplay[0],0x00,CON_ALARM_TYPE_BYTE_MAX);
    memset(&ucAlarmStatusLcdError[0],0x00,CON_ALARM_TYPE_BYTE_MAX);
    uiAlarmSpeekAlarmTime=0;
    ucAlarmSpeekCardReadSpeek=GAL_NO;
    ucAlarmErrBlackLightHave=0;
    AlarmParaInit();
}


void AlarmSpeekAlarmClr(void)
{
    uiAlarmSpeekAlarmTime=0;    
}

void AlarmDoLedSpeek(uchar value,uchar type)
{
    uchar ucTempName,ucTempBit;
    if (type>=TYPE_ALARM_TOTAL)
        return;
    ucTempName = type>>3;
    ucTempBit  = 1<<(type&0x7);
    
    //  AA  声音报警信号   AA
    ucAlarmStatusSpeek[ucTempName] &= ~ucTempBit;
    if(ucTempBit==(RAM[RAM_COEF_ALARM_SPEEK +ucTempName]&ucTempBit))
    // AA if Alarm is Open  AA
    {
        if (CON_ALARM_STATUS_START ==value)
        {
            ucAlarmStatusSpeek[ucTempName] |= ucTempBit;
        }
    }
#if(CON_ALARM_LEDGREEN_ENABLE == GAL_YES)
    //  AA  绿色灯光报警信号   AA
    ucAlarmStatusLedGreen[ucTempName] &= ~ucTempBit;
    if(ucTempBit==(RAM[RAM_COEF_ALARM_LEDGREEN +ucTempName]&ucTempBit))
    // AA if Alarm is Open  AA
    {
        if (CON_ALARM_STATUS_START ==value)
        {
            ucAlarmStatusLedGreen[ucTempName] |= ucTempBit;
        }
    }
#endif    
    //  AA  黄色灯光报警信号   AA
    ucAlarmStatusLedYellow[ucTempName] &= ~ucTempBit;
    if(ucTempBit==(RAM[RAM_COEF_ALARM_LEDYELLOW +ucTempName]&ucTempBit))
    // AA if Alarm is Open  AA
    {
        if (CON_ALARM_STATUS_START ==value)
        {
            ucAlarmStatusLedYellow[ucTempName] |= ucTempBit;
        }
    }
        
    //  AA  LCD 液晶显示内容   AA
    ucAlarmStatusLcdDisplay[ucTempName] &= ~ucTempBit;
    if(ucTempBit==(RAM[RAM_COEF_ALARM_LCD_DISPLLAY +ucTempName]&ucTempBit))
    // AA if Alarm is Open  AA
    {
        if (CON_ALARM_STATUS_START ==value)
        {
            ucAlarmStatusLcdDisplay[ucTempName] |= ucTempBit;
        }
    }
    
    
    //  AA  LCD 液晶显示报警   AA
    ucAlarmStatusLcdError[ucTempName] &= ~ucTempBit;
    if(ucTempBit==(RAM[RAM_COEF_ALARM_LCD_ERROR +ucTempName]&ucTempBit))
    // AA if Alarm is Open  AA
    {
        if (CON_ALARM_STATUS_START ==value)
        {
            ucAlarmStatusLcdError[ucTempName] |= ucTempBit;
        }
    }
}
void AlarmSpeekAlarmCardReadTime(u16 uiTimes,uchar ucTimeStart)
{
    if((0!=RAM[RAM_COEF_ALARM_SPEEK+0])||(0!=RAM[RAM_COEF_ALARM_SPEEK+1])
        ||(0!=RAM[RAM_COEF_ALARM_SPEEK+2])||(0!=RAM[RAM_COEF_ALARM_SPEEK+3]))
    {
        ucAlarmSpeekCardReadSpeek=uiTimes;
        if(0xff!=ucTimeStart)
        {
            ucAlarmSpeekTempTimer=ucTimeStart;
        }
    }
}
void AlarmClrAll(void)
{
    ucAlarmLedStatus=GAL_NO;
    uiBackLightTime=0;
    ucAlarmErrBlackLightHave=0;
#if(CONFIG_METER_PREPAY_MODE!=CONFIG_METER_PREPAY_MODE_DISABLE)
    LCDBackTime=0;
#endif
    memset(&(ucAlarmStatusSpeek[0]), 0x00, RAM_ALARM_SPEEK_STATUS_LEN);     //ZD 原来获取的长度不妥
    memset(&ucAlarmStatusSpeekLast[0], 0x00, CON_ALARM_TYPE_BYTE_MAX);
#if(CON_ALARM_LEDGREEN_ENABLE == GAL_YES)
    memset(&ucAlarmStatusLedGreen[0], 0x00, RAM_ALARM_LEDGREEN_STATUS_LEN);
#endif
    memset(&ucAlarmStatusLedYellow[0], 0x00, RAM_ALARM_LEDYELLOW_STATUS_LEN);
    memset(&ucAlarmStatusLcdDisplay[0], 0x00, RAM_ALARM_LCD_DISPLLAY_STATUS_LEN);
    memset(&ucAlarmStatusLcdError[0], 0x00, RAM_ALARM_LCD_ERROR_STATUS_LEN);
    ClrLedAlarm();
    ClrRelayAlarmLed();
    ClrRelayAlarmPluse();
    uiAlarmSpeekAlarmTime=0;
    ucAlarmSpeekCardReadSpeek=0;
}


void AlarmMode(void)
{
    uchar ucTemp;
    uchar ucValue;
    //if(ucAlarmModeSecond != RSOFT_RTC_SECOND)
    {
        //ucAlarmModeSecond = RSOFT_RTC_SECOND;
        //查看时间
        TimeDeal(GAL_YES);

        // 数据读写错误
        if(RAM[RAM_CURRENT_MEMORY_STATUS])
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_HARD_ERR); 
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_HARD_ERR); 
        }

        //  AA  全失压报警 AA
        if(fGetAllLostVoltageStatus)
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_ALLLOSSVOLTAGE);
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_ALLLOSSVOLTAGE);
        }
        
        //  AA  失压报警  AA
        if((FLG_A_LOSS_VOLTAGE_STATUS)||(FLG_B_LOSS_VOLTAGE_STATUS)||(FLG_C_LOSS_VOLTAGE_STATUS))
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_LOSSVOLTAGE);
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_LOSSVOLTAGE);
        }
        
        //  AA  过压报警  AA
        if((FLG_A_OVER_VOLTAGE_STATUS)||(FLG_B_OVER_VOLTAGE_STATUS)||(FLG_C_OVER_VOLTAGE_STATUS))
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_OVERVOLTAGE);
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_OVERVOLTAGE);
        }
        
        //  AA 欠压报警  AA
        if((FLG_A_DOWN_VOLTAGE_STATUS)||(FLG_B_DOWN_VOLTAGE_STATUS)||(FLG_C_DOWN_VOLTAGE_STATUS))
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_DOWNVOLTAGE);
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_DOWNVOLTAGE);
        }
        
        //  AA  断相报警  AA
        if((FLG_A_CUT_VOLTAGE_STATUS)||(FLG_B_CUT_VOLTAGE_STATUS)||(FLG_C_CUT_VOLTAGE_STATUS))
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_CUTVOLTAGE);
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_CUTVOLTAGE);
        }
        
        //  AA  失流报警  AA
        if((FLG_A_LOSS_CURRENT_STATUS)||(FLG_B_LOSS_CURRENT_STATUS)||(FLG_C_LOSS_CURRENT_STATUS))
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_LOSSCURRENT);
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_LOSSCURRENT);
        }
        
        //  AA  过流报警  AA
        if((FLG_A_OVER_CURRENT_STATUS)||(FLG_B_OVER_CURRENT_STATUS)||(FLG_C_OVER_CURRENT_STATUS))
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_OVERCURRENT);
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_OVERCURRENT);
        }
        
        //  AA  断流报警  AA
        if((FLG_A_CUT_CURRENT_STATUS)||(FLG_B_CUT_CURRENT_STATUS)||(FLG_C_CUT_CURRENT_STATUS))
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_CUTCURRENT);
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_CUTCURRENT);
        }
        
        //  AA 电压逆向序报警  AA
        if(FLG_ORDER_VOLTAGE_STATUS)
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_ORDERVOLTAGE);
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_ORDERVOLTAGE);
        }
        
        //  AA 电流逆向序报警  AA
        if(FLG_ORDER_CURRENT_STATUS)
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_ORDERCURRENT);
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_ORDERCURRENT);
        }
        //  AA 总功率反向报警  AA
        if(FLG_ALL_REVERSEKW_STATUS)
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_REVERSEKW_ALL);
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_REVERSEKW_ALL);
        }
        
        //  AA 分相功率反向报警  AA
        if((FLG_A_REVERSEKW_STATUS)||(FLG_B_REVERSEKW_STATUS)||(FLG_C_REVERSEKW_STATUS))
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_REVERSEKW_ABC);
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_REVERSEKW_ABC);
        }
        
        
        //  AA 总功率过载报警  AA
        if(FLG_ALL_OVER_KW_STATUS)
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_OVERKW_ALL);
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_OVERKW_ALL);
        }
        
        //  AA 分相功率过载报警  AA
        if((FLG_A_OVER_KW_STATUS)||(FLG_B_OVER_KW_STATUS)||(FLG_C_OVER_KW_STATUS))
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_OVERKW_ABC);
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_OVERKW_ABC);
        }
        
        
        //  AA 电压不平衡报警  AA
        if(FLG_UNBALANCE_VOLTAGE_STATUS)
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_UNBALANCEVOLTAGE);
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_UNBALANCEVOLTAGE);
        }
        
        //  AA 电流不平衡报警  AA
        if(FLG_UNBALANCE_CURRENT_STATUS)
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_UNBALANCECURRENT);
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_UNBALANCECURRENT);
        }
        
        //  AA 需量过载报警  AA
        if(FLG_DEMANDOVER_STATUS)
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_OVERDEMAND);
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_OVERDEMAND);
        }

        //  AA 电流严重不平衡报警  AA
        if(FLG_UNBALANCE_SEVERITY_CURRENT_STATUS)
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_UNBALANCESEVERITYCURRENT);
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_UNBALANCESEVERITYCURRENT);
        }

        //  AA 总功率因数越限  AA
        if(FLG_OVERTOTALCOS_STATUS)
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_OVERTOTALCOS);
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_OVERTOTALCOS);
        }
#if(CONFIG_METER_AUX_MODE==CONFIG_METER_AUX_MODE_ENABLE)
        //  AA 辅助电源报警  AA
        //if(FLG_ACPOWER_STATUS)
        if(fGetAuxPowerDownStatus)
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_LOSSACPOWER);
        }
        else
#endif
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_LOSSACPOWER);
        }
        
        //  AA 表盖开启报警  AA
        //if(FLG_COVER_OPEN_STATUS)
        if(fGetCoverOpenStatus)
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_COVEROPEN);
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_COVEROPEN);
        }
        
        //  AA 端钮盖开启报警  AA
        //if(FLG_TERMINAL_OPEN_STATUS)
        if(fGetTerminalOpenStatus)
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_TERMINALOPEN);
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_TERMINALOPEN);
        }
#if 0       
        
        //  AA 编程盖开启报警  AA
//      if(FLG_PROGRAM_OPEN_STATUS)
//      {
//          AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_PROGRAMOPEN);
//      }
//      else
//      {
//          AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_PROGRAMOPEN);
//      }
#endif      
        //  AA 停抄电池欠压报警  AA
        if(FLG_BATWAKEUP_STATUS)
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_BATWAKEUP);
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_BATWAKEUP);
        }
        
        //  AA 时钟电池欠压报警  AA
        if(FLG_BATTIMELOW_STATUS)
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_BATTIMELOW);
        }
        else
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_BATTIMELOW);
        }
        
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)       
        //  AA ESAM报警错误  AA
        if(EsamERRFlag)
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_ESAM_ERR);
        }
        else
#endif      
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_ESAM_ERR);
        }
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)       
        //  AA 控制回路错误 AA
        if(RELAY_FAULT_FLAG)
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_CONTROL_ERR);
        }
        else
#endif
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_CONTROL_ERR);
        }

#if(CONFIG_METER_AREA_MODE_ZHEJIANG_HANGZHOU == CONFIG_METER_AREA_MODE)
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
        if((RELAY_ORDER_ALARM_FLAG))
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_PREPAY_RELAY_CTRL);
        }
        else
#endif
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_PREPAY_RELAY_CTRL);
        }

#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
        if((RELAY_ORDER_STATE_FLAG))
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_PREPAY_RELAY_ORDER_STATE);
        }
        else
#endif
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_PREPAY_RELAY_ORDER_STATE);
        }
#else
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
        if((RELAY_ORDER_ALARM_FLAG)||(RELAY_ORDER_STATE_FLAG))
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_PREPAY_RELAY_CTRL);
        }
        else
#endif
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_PREPAY_RELAY_CTRL);
        }
#endif

#if(CONFIG_METER_PREPAY_MODE == CONFIG_METER_PREPAY_MODE_LOCATION)
        if((PREPAY_ALARM1_FLAG)||(PREPAY_ALARM2_FLAG)||(PREPAY_ALARM3_FLAG))
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_START,TYPE_ALARM_PREPAY_MOMEY_CTRL);
        }
        else
#endif
        {
            AlarmDoLedSpeek(CON_ALARM_STATUS_STOP,TYPE_ALARM_PREPAY_MOMEY_CTRL);
        }

        //Green Led show
#if(CON_ALARM_LEDGREEN_ENABLE == GAL_YES)
        if((CON_ALARM_TYPE_BYTE_MAX!=TestZeroNum(&ucAlarmStatusLedGreen[0], CON_ALARM_TYPE_BYTE_MAX)))
        {
            SetLedAlarmGreen();
        }        
        else
        {
            ClrLedAlarmGreen();
        }
#endif

        ucValue=GAL_NO;
        ucAlarmErrBlackLightHave=0;
        if((CON_ALARM_TYPE_BYTE_MAX!=TestZeroNum(&ucAlarmStatusLcdError[0], CON_ALARM_TYPE_BYTE_MAX)))
        {
            ucAlarmErrBlackLightHave=1;
        }
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
#if(CONFIG_METER_AREA_MODE_ZHEJIANG_HANGZHOU == CONFIG_METER_AREA_MODE)
        if(ucAlarmStatusLedYellow[TYPE_ALARM_PREPAY_RELAY_CTRL/8] & (1<<(TYPE_ALARM_PREPAY_RELAY_CTRL&0x7)))
        {
            ucAlarmErrBlackLightHave=1;
        }
        if(ucAlarmStatusLedYellow[TYPE_ALARM_PREPAY_RELAY_ORDER_STATE/8] & (1<<TYPE_ALARM_PREPAY_RELAY_ORDER_STATE&0x7))
        {
            ucAlarmErrBlackLightHave=1;
        }
#else        
    #if(CONFIG_METER_AREA_MODE_SHANDONG==CONFIG_METER_AREA_MODE)
        if((RELAY_STATE_FLAG)||(RELAY_COMMAND_STATE_FLAG)||(RELAY_ORDER_ALARM_FLAG)||(RELAY_ORDER_STATE_FLAG))
    #else
        if((RELAY_ORDER_ALARM_FLAG)||(RELAY_ORDER_STATE_FLAG))
    #endif
        {
            ucAlarmErrBlackLightHave=1;
            ucValue=GAL_YES;
        }
#endif
#endif
#if(CONFIG_METER_PREPAY_MODE == CONFIG_METER_PREPAY_MODE_LOCATION)
        if((PREPAY_ALARM1_FLAG)||(PREPAY_ALARM2_FLAG)||(PREPAY_ALARM3_FLAG))
        {
            ucValue=GAL_YES;
        }
#endif
#if(CONFIG_METER_AREA_MODE_SHANGHAI==CONFIG_METER_AREA_MODE)
        ucAlarmErrBlackLightHave=0;
#endif
        if((CON_ALARM_TYPE_BYTE_MAX!=TestZeroNum(&ucAlarmStatusLedYellow[0], CON_ALARM_TYPE_BYTE_MAX)))
        {
            ucValue=GAL_YES;
        }
        if(GAL_YES==ucValue)
        {
#if(CONFIG_METER_AREA_MODE_SHANGHAI!=CONFIG_METER_AREA_MODE)
            SetLedAlarm();
#else
            ClrLedAlarm();
#endif
#if(CONFIG_METER_AREA_MODE_SHANDONG!=CONFIG_METER_AREA_MODE)
            SetRelayAlarmPluseStatus(GAL_YES);
#endif
            ucAlarmLedStatus=GAL_YES;
        }
        else
        {
            ClrLedAlarm();
#if(CONFIG_METER_AREA_MODE_SHANDONG!=CONFIG_METER_AREA_MODE)
            SetRelayAlarmPluseStatus(GAL_NO);
#endif
            ucAlarmLedStatus=GAL_NO;
        }

#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
#if(CONFIG_METER_AREA_MODE_SHANDONG==CONFIG_METER_AREA_MODE)
        if((RELAY_STATE_FLAG)||(RELAY_COMMAND_STATE_FLAG)||(RELAY_ORDER_ALARM_FLAG)||(RELAY_ORDER_STATE_FLAG))
        {
            SetRelayAlarmPluseStatus(GAL_YES);
        }
        else
        {
            SetRelayAlarmPluseStatus(GAL_NO);
        }
#endif                  
#endif



        // Relay Alarm Led start       
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
        ucValue=GAL_NO;
        if(FLG_RELAY_ON_ALARM_STATUS)
        {
            if((ucAlarmModeSecond%2) == 1)  
            {
                ucValue=GAL_YES;
            }
        }
        else
        {
            ucValue= RELAY_ORDER_STATE_FLAG;
        }
        
        if(GAL_YES==ucValue)
        {
            SetRelayAlarmLed();
        }
        else
        {
            ClrRelayAlarmLed();
        }
#endif

        for(ucTemp=0;ucTemp<CON_ALARM_TYPE_BYTE_MAX;ucTemp++)
        {
            if(((ucAlarmStatusSpeekLast[ucTemp]|ucAlarmStatusSpeek[ucTemp]) - (ucAlarmStatusSpeekLast[ucTemp]&ucAlarmStatusSpeek[ucTemp])) & ucAlarmStatusSpeek[ucTemp])
            {
                if(0==uiAlarmSpeekAlarmTime)
                {
                    ucAlarmSpeekTempTimer=0;
                }
                uiAlarmSpeekAlarmTime=CON_ALARM_SPEEK_ALRAM_TIME_MAX;
            }
        }
        memcpy(&ucAlarmStatusSpeekLast[0], &(ucAlarmStatusSpeek[0]), CON_ALARM_TYPE_BYTE_MAX);
        if(CON_ALARM_TYPE_BYTE_MAX==TestZeroNum(&(ucAlarmStatusSpeek[0]), CON_ALARM_TYPE_BYTE_MAX))
        {
            memset(&ucAlarmStatusSpeekLast[0], 0x00, sizeof(ucAlarmStatusSpeekLast));
            uiAlarmSpeekAlarmTime=0;
        }
    }
}

