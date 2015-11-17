#define AP_ORDERCURRENT_GLOBALS
#include "common.h"

uchar ucTempOrderCurrentStatusUse,ucTempOrderCurrentContinueTime;
uchar ucOrderCurrentContineTime;

void OrderCurrentEnd(void);
void OrderCurrentStart(void);
void OrderCurrentTimeAdd(void);
uchar OrderCurrentMode_34(void);

void OrderCurrentInit(void)
{
    FLG_ORDER_CURRENT_STATUS=0;
    ucTempOrderCurrentStatusUse=0;
    ucTempOrderCurrentContinueTime=0;
    ucOrderCurrentContineTime=0;
}

void OrderCurrentStart(void)
{
    ulong ulDataAddr;

    FLG_ORDER_CURRENT_STATUS=GAL_YES;

#if(CONFIG_METER_AREA_MODE_SHANDONG==CONFIG_METER_AREA_MODE)
    EVENT_CONTINUE_TIME_START_INIT(ucOrderCurrentContineTime, CONFIG_METER_EVENT_DELAY_MIN_TIME);
#else
    EVENT_CONTINUE_TIME_START_INIT(ucOrderCurrentContineTime, 60);
#endif  

    // Total Count
    Data3ByteBCDAdd1(EPL_TOTAL_ORDER_CURRENT_COUNT_TOTAL);
#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Total StartTime
    SetTimeDataToPoint(&Wr_data[0]);
    memset(&Wr_data[6],0,6);
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_ORDER_CURRENT_LAST_START,  12);
#endif  
    
    ulDataAddr=SetTwoTableNextPoint(TYPE_ORDER_CURRENT_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetEventStartDataLossVoltagetoAddr(&Wr_data[0]);
        memset(&Wr_data[125], 0x00, 86);
        
        WriteDataDirect(&Wr_data[0], ulDataAddr,  211);
    }
    ClrFlashMode();
}

void OrderCurrentStopIfStart(void)
{
    if(GAL_YES == FLG_ORDER_CURRENT_STATUS)
    {
        OrderCurrentEnd();
    }
}


void OrderCurrentEnd(void)
{
    ulong ulDataAddr;
    
    FLG_ORDER_CURRENT_STATUS=GAL_NO;
    
    OrderCurrentMinTimeAdd();
    
#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Total End Time
    SetTimeDataToPoint(&Wr_data[0]);
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_ORDER_CURRENT_LAST_START+6,  6);
#endif  
    
    ulDataAddr=GetTwoTableAddrFromBlock(TYPE_ORDER_CURRENT_RECORD,0,125);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetEventEndDataLossVoltagetoAddr(&Wr_data[0]);
        WriteDataDirect(&Wr_data[0], ulDataAddr,  86);
    }

}

void OrderCurrentSecTimeAdd(void)
{
    if(GAL_YES == FLG_ORDER_CURRENT_STATUS)
    {
        ucOrderCurrentContineTime++;
    }
}

void OrderCurrentMinTimeAdd(void)
{
    if(ucOrderCurrentContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_ORDER_CURRENT_TIME_TOTAL);
        ucOrderCurrentContineTime -= 60;
    }
}

uchar OrderCurrentMode_34(void)
{
    uchar ucTemp,ucContinueTime,ucStatus;
    u16 uiStartV;
    

    uiStartV=ulTypeIb*5;    // 0.5%的电流限制


    ucTemp=(0x0F&status_5460_1)>>3;
    
    if(uiStartV>ulNowCurrent[0])
    {
        ucTemp=0;
    }
    if(PROGFUNCTION_TYPE_METER_TYPE != METERTYPE_3_3)
    {
        if(uiStartV>ulNowCurrent[1])
        {
            ucTemp=0;
        }
    }
    if(uiStartV>ulNowCurrent[2])
    {
        ucTemp=0;
    }

    
#if(CONFIG_METER_AREA_MODE_SHANDONG==CONFIG_METER_AREA_MODE)
    ucContinueTime=CONFIG_METER_EVENT_DELAY_MIN_TIME;
#else
    ucContinueTime=60;
#endif  
    
    //========================================================
    // Phase A
    ucStatus=FLG_ORDER_CURRENT_STATUS;
    
    if(1==TranslateStatus0or1(&ucStatus,&ucTempOrderCurrentStatusUse,
        &ucTempOrderCurrentContinueTime,ucContinueTime,ucTemp))
    {
        
        if(GAL_YES==ucStatus)
        {
            OrderCurrentStart();
        }
        else
        {
            OrderCurrentEnd();
        }
    }
    return DLT_RET_SUCC;
}


uchar OrderCurrentMode(void)
{

    if(isSystemResetUnfinisded)
        return DLT_RET_SUCC;
    
    if(GAL_NO== PROGFUNCTION_ORDER_CURRENT )
    {
        FLG_ORDER_CURRENT_STATUS=0;
        return DLT_RET_UNSUPPORT;
    }
    else
    {
        if(isFlashFree)
        {
            return OrderCurrentMode_34();
        }
        else
        {
            return DLT_RET_UNFINISHED;
        }
    }
}





















