#define AP_ORDERVOLTAGE_GLOBALS
#include "common.h"

uchar ucTempOrderVoltageStatusUse,ucTempOrderVoltageContinueTime;
uchar ucOrderVoltageContineTime;

void OrderVoltageInit(void)
{
    FLG_ORDER_VOLTAGE_STATUS=0;
    ucTempOrderVoltageStatusUse=0;
    ucTempOrderVoltageContinueTime=0;
    ucOrderVoltageContineTime=0;
}

void OrderVoltageStart(void)
{
    ulong ulDataAddr;

    FLG_ORDER_VOLTAGE_STATUS=GAL_YES;
#if(CONFIG_METER_AREA_MODE_SHANDONG==CONFIG_METER_AREA_MODE)
    EVENT_CONTINUE_TIME_START_INIT(ucOrderVoltageContineTime, CONFIG_METER_EVENT_DELAY_MIN_TIME);
#else
    EVENT_CONTINUE_TIME_START_INIT(ucOrderVoltageContineTime, 60);
#endif  

    // Total Count
    Data3ByteBCDAdd1(EPL_TOTAL_ORDER_VOLTAGE_COUNT_TOTAL);

#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Total StartTime
    SetTimeDataToPoint(&Wr_data[0]);
    memset(&Wr_data[6],0,6);
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_ORDER_VOLTAGE_LAST_START,  12);
#endif  
    
    ulDataAddr=SetTwoTableNextPoint(TYPE_ORDER_VOLTAGE_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetEventStartDataLossVoltagetoAddr(&Wr_data[0]);
        memset(&Wr_data[125], 0x00, 56);
        
        WriteDataDirect(&Wr_data[0], ulDataAddr,  211);
    }
    ClrFlashMode();
}

void OrderVoltageStopIfStart(void)
{
    if(GAL_YES == FLG_ORDER_VOLTAGE_STATUS)
    {
        OrderVoltageEnd();
    }
}


void OrderVoltageEnd(void)
{
    ulong ulDataAddr;
    
    FLG_ORDER_VOLTAGE_STATUS=GAL_NO;
    OrderVoltageMinTimeAdd();
    
#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Total End Time
    SetTimeDataToPoint(&Wr_data[0]);
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_ORDER_VOLTAGE_LAST_START+6,  6);
#endif  
    
    ulDataAddr=GetTwoTableAddrFromBlock(TYPE_ORDER_VOLTAGE_RECORD,0,125);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetEventEndDataLossVoltagetoAddr(&Wr_data[0]);
        WriteDataDirect(&Wr_data[0], ulDataAddr,  86);
    }

}

void OrderVoltageSecTimeAdd(void)
{
    if(GAL_YES == FLG_ORDER_VOLTAGE_STATUS)
    {
        ucOrderVoltageContineTime++;
    }
}

void OrderVoltageMinTimeAdd(void)
{
    if(ucOrderVoltageContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_ORDER_VOLTAGE_TIME_TOTAL);
        ucOrderVoltageContineTime -= 60;
    }
}

uchar OrderVoltageMode_34(void)
{
    uchar ucTemp,ucContinueTime,ucStatus;
    u16 uiStartV;
    

    uiStartV=ulTypeUn*6/10;


    ucTemp=status_5460_1>>7;
    
    if(uiStartV>uiNowVoltage[0])
    {
        ucTemp=0;
    }
    if(PROGFUNCTION_TYPE_METER_TYPE != METERTYPE_3_3)
    {
        if(uiStartV>uiNowVoltage[1])
        {
            ucTemp=0;
        }
    }
    if(uiStartV>uiNowVoltage[2])
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
    ucStatus=FLG_ORDER_VOLTAGE_STATUS;
    
    if(1==TranslateStatus0or1(&ucStatus,&ucTempOrderVoltageStatusUse,
        &ucTempOrderVoltageContinueTime,ucContinueTime,ucTemp))
    {
        
        if(GAL_YES==ucStatus)
        {
            OrderVoltageStart();
        }
        else
        {
            OrderVoltageEnd();
        }
    }
    
    return DLT_RET_SUCC;
}


uchar OrderVoltageMode(void)
{

    if(isSystemResetUnfinisded)
        return DLT_RET_SUCC;
    
    if(GAL_NO== PROGFUNCTION_ORDER_VOLTAGE )
    {
        FLG_ORDER_VOLTAGE_STATUS=0;
        return DLT_RET_UNSUPPORT;
    }
    else
    {
        if(isFlashFree)
        {
            return OrderVoltageMode_34();
        }
        else
        {
            return DLT_RET_UNFINISHED;
        }
    }
}



















