#define AP_OVERTOTALCOS_GLOBALS
#include "common.h"

uchar ucTempOverTotalCosStatusUse,ucTempOverTotalCosContinueTime;

u16  uiOverTotalCosStart;
uchar ucOverTotalCosStartTime;
uchar ucOverTotalCosContineTime;

void OverTotalCosParaInit(void)
{
    ReadCoefDataWithCheck(EPL_COEF_OVERTOTALCOS_CONDITION, 3, Ap_temp, 1);
    uiOverTotalCosStart=HexFromRam2Bcd(Ap_temp);
    ucOverTotalCosStartTime=HexFromRam1Bcd((Ap_temp+2));
    if(ucOverTotalCosStartTime<CONFIG_METER_EVENT_DELAY_MIN_TIME)
        ucOverTotalCosStartTime=CONFIG_METER_EVENT_DELAY_MIN_TIME;
}

void OverTotalCosInit(void)
{
    FLG_OVERTOTALCOS_STATUS=0;
    ucTempOverTotalCosStatusUse=0;
    ucTempOverTotalCosContinueTime=0;
    OverTotalCosParaInit();
    ucOverTotalCosContineTime=0;
}

void OverTotalCosStart(void)
{
    ulong ulDataAddr;

    FLG_OVERTOTALCOS_STATUS=GAL_YES;
    EVENT_CONTINUE_TIME_START_INIT(ucOverTotalCosContineTime, ucOverTotalCosStartTime);

    // Total Count
    Data3ByteBCDAdd1(EPL_TOTAL_OVERTOTALCOS_COUNT_TOTAL);

#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Total StartTime
    SetTimeDataToPoint(&Wr_data[0]);
    memset(&Wr_data[6],0,6);
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_OVERTOTALCOS_LAST_START,  12);
#endif  
    
    ulDataAddr=SetTwoTableNextPoint(TYPE_OVERTOTALCOS_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetEventStartDataLossVoltagetoAddr(&Wr_data[0]);
        memset(&Wr_data[125], 0x00, 88);
        
        WriteDataDirect(&Wr_data[0], ulDataAddr,  213);
    }
    ClrFlashMode();

}
void OverTotalCosStopIfStart(void)
{
    if(GAL_YES == FLG_OVERTOTALCOS_STATUS)
    {
        OverTotalCosEnd();
    }
    
}

void OverTotalCosEnd(void)
{
    ulong ulDataAddr;
    
    FLG_OVERTOTALCOS_STATUS=GAL_NO;
    
    OverTotalCosMinTimeAdd();
    
    // Total End Time
    SetTimeDataToPoint(&Wr_data[0]);
    //WriteDataDirect(&Wr_data[0], EPL_TOTAL_OVERTOTALCOS_LAST_START+6,  6);
    
    
    ulDataAddr=GetTwoTableAddrFromBlock(TYPE_OVERTOTALCOS_RECORD,0,125);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetEventEndDataLossVoltagetoAddr(&Wr_data[0]);
        WriteDataDirect(&Wr_data[0], ulDataAddr,  86);
    }
}

void OverTotalCosSecTimeAdd(void)
{
    if(GAL_YES == FLG_OVERTOTALCOS_STATUS)
    {
        ucOverTotalCosContineTime++;
    }
}

void OverTotalCosMinTimeAdd(void)
{
    if(ucOverTotalCosContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_OVERTOTALCOS_TIME_TOTAL);
        ucOverTotalCosContineTime -= 60;
    }
}

uchar OverTotalCosMode_34(void)
{
    uchar ucTemp,ucStatus;
    
    u16 uiCurrent;
 
    
    ucTemp=GAL_NO;
    
    uiCurrent=ValueHexFromRam2Bcd(RAM_CURRENT_FACTOR_ALL+2);
    if(uiCurrent>=8000)
        uiCurrent=uiCurrent-8000;
    
    if(uiOverTotalCosStart>=uiCurrent)
    {
        ucTemp=GAL_YES;
    }
    
    //========================================================
    ucStatus=FLG_OVERTOTALCOS_STATUS;
    
    if(1==TranslateStatus0or1(&ucStatus,&ucTempOverTotalCosStatusUse,
        &ucTempOverTotalCosContinueTime,ucOverTotalCosStartTime,ucTemp))
    {
        
        if(GAL_YES==ucStatus)
        {
            OverTotalCosStart();
        }
        else
        {
            OverTotalCosEnd();
        }
    }
    return DLT_RET_SUCC;
}


uchar OverTotalCosMode(void)
{

    if(isSystemResetUnfinisded)
        return DLT_RET_SUCC;
    
    if(isFlashFree)
    {
        return OverTotalCosMode_34();
    }
    else
    {
        return DLT_RET_UNFINISHED;
    }
}










































