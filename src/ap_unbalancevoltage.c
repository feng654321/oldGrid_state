#define AP_UNBALANCEVOLTAGE_GLOBALS
#include "common.h"

uchar ucTempUnbalanceVoltageStatusUse,ucTempUnbalanceVoltageContinueTime;

u16  uiUnbalanceVoltageStartV;
uchar ucUnbalanceVoltageStartTime;
uchar ucUnbalanceVoltageContineTime;

void UnbalanceVoltageParaInit(void)
{
    ReadCoefDataWithCheck(EPL_COEF_UNBALANCE_VOLTAGE_CONDITION, 3, Ap_temp, 1);
    uiUnbalanceVoltageStartV=HexFromRam2Bcd(Ap_temp);
    ucUnbalanceVoltageStartTime=HexFromRam1Bcd((Ap_temp+2));
    if(ucUnbalanceVoltageStartTime<CONFIG_METER_EVENT_DELAY_MIN_TIME)
        ucUnbalanceVoltageStartTime=CONFIG_METER_EVENT_DELAY_MIN_TIME;
}

void UnbalanceVoltageInit(void)
{
    FLG_UNBALANCE_VOLTAGE_STATUS=0;
    ucTempUnbalanceVoltageStatusUse=0;
    ucTempUnbalanceVoltageContinueTime=0;
    UnbalanceVoltageParaInit();
    ucUnbalanceVoltageContineTime=0;
}

void UnbalanceVoltageStart(void)
{
    ulong ulDataAddr;

    FLG_UNBALANCE_VOLTAGE_STATUS=GAL_YES;
    EVENT_CONTINUE_TIME_START_INIT(ucUnbalanceVoltageContineTime, ucUnbalanceVoltageStartTime);
    

    // Total Count
    Data3ByteBCDAdd1(EPL_TOTAL_UNBALANCE_VOLTAGE_COUNT_TOTAL);

#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Total StartTime
    SetTimeDataToPoint(&Wr_data[0]);
    memset(&Wr_data[6],0,6);
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_UNBALANCE_VOLTAGE_LAST_START,  12);
#endif  
    
    memset(&RAM[RAM_CURRENT_UNBALANCE_VOLTAGE_MAXDATA],0,3);
    ulDataAddr=SetTwoTableNextPoint(TYPE_UNBALANCE_VOLTAGE_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetEventStartDataLossVoltagetoAddr(&Wr_data[0]);
        memset(&Wr_data[125], 0x00, 89);
        
        WriteDataDirect(&Wr_data[0], ulDataAddr,  214);
    }
    ClrFlashMode();
}
void UnbalanceVoltageStopIfStart(void)
{
    if(GAL_YES == FLG_UNBALANCE_VOLTAGE_STATUS)
    {
        UnbalanceVoltageEnd();
    }
    
}

void UnbalanceVoltageEnd(void)
{
    ulong ulDataAddr;
    
    FLG_UNBALANCE_VOLTAGE_STATUS=GAL_NO;
    
    UnbalanceVoltageMinTimeAdd();

#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Total End Time
    SetTimeDataToPoint(&Wr_data[0]);
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_UNBALANCE_VOLTAGE_LAST_START+6,  6);
#endif  
    
    ulDataAddr=GetTwoTableAddrFromBlock(TYPE_UNBALANCE_VOLTAGE_RECORD,0,125);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        memcpy(&Wr_data[0],&RAM[RAM_CURRENT_UNBALANCE_VOLTAGE_MAXDATA],3);
        SetEventEndDataLossVoltagetoAddr(&Wr_data[3]);
        WriteDataDirect(&Wr_data[0], ulDataAddr,  89);
    }

}

void UnbalanceVoltageSecTimeAdd(void)
{
    if(GAL_YES == FLG_UNBALANCE_VOLTAGE_STATUS)
    {
        ucUnbalanceVoltageContineTime++;
    }
}

void UnbalanceVoltageMinTimeAdd(void)
{
    if(ucUnbalanceVoltageContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_UNBALANCE_VOLTAGE_TIME_TOTAL);
        ucUnbalanceVoltageContineTime -= 60;
    }
}

uchar UnbalanceVoltageMode_34(void)
{
    uchar ucTemp,ucStatus;
    u16 uiStartV;
    u16 uiMax,uiMin,uiPinJun;
    ulong ulData;

    
    if(uiNowVoltage[0]>uiNowVoltage[2]) // A>C
    {
        uiMax=uiNowVoltage[0];
        uiMin=uiNowVoltage[2];
    }
    else
    {
        uiMax=uiNowVoltage[2];
        uiMin=uiNowVoltage[0];
    }
    
    if(PROGFUNCTION_TYPE_METER_TYPE != METERTYPE_3_3)
    {
        if(uiNowVoltage[1]>uiMax)
        {
            uiMax=uiNowVoltage[1];
        }
        else
        {
            if(uiNowVoltage[1]<uiMin)
            {
                uiMin=uiNowVoltage[1];
            }
        }
        uiPinJun=(uiNowVoltage[0]+uiNowVoltage[1]+uiNowVoltage[2])/3;
    }
    else
    {
        uiPinJun=(uiNowVoltage[0]+uiNowVoltage[2])/2;
    }
    
    ucTemp=GAL_NO;
    ulData=(uiMax-uiMin);
    if(uiPinJun == 0) 
    {
        //ErrPrint("UnbalanceVoltageMode_34 uiPinJun = 0\n");
        uiPinJun=1;
    }
    uiMin=ulData*10000/uiPinJun;
    if(uiMin>30000)
    {
        uiMin=30000;
    }
    
    //  AA   自己内部固定有5%Un的最低限值     AA
    uiStartV=5*ulTypeUn/100;  // xxx dot x
    
    if((uiMax>uiStartV))
    {
        uiStartV=uiUnbalanceVoltageStartV;
        if(uiMin>uiStartV)
        {
            ucTemp=GAL_YES;
        }
    }
    
    //========================================================
    ucStatus=FLG_UNBALANCE_VOLTAGE_STATUS;
    
    if(1==TranslateStatus0or1(&ucStatus,&ucTempUnbalanceVoltageStatusUse,
        &ucTempUnbalanceVoltageContinueTime,ucUnbalanceVoltageStartTime,ucTemp))
    {
        
        if(GAL_YES==ucStatus)
        {
            UnbalanceVoltageStart();
        }
        else
        {
            UnbalanceVoltageEnd();
        }
    }
//  -----最大数据更新----------------->start
    if(GAL_YES==FLG_UNBALANCE_VOLTAGE_STATUS)
    {
        uiMax=Bcd3DataToLong(&RAM[RAM_CURRENT_UNBALANCE_VOLTAGE_MAXDATA]);
        if(uiMin>uiMax)
        {
            LongToData3BCD(uiMin, &RAM[RAM_CURRENT_UNBALANCE_VOLTAGE_MAXDATA]);
        }
    }
//  -----最大数据更新----------------->end
    return DLT_RET_SUCC;
}


uchar UnbalanceVoltageMode(void)
{

    if(isSystemResetUnfinisded)
        return DLT_RET_SUCC;
    
    if(GAL_NO== PROGFUNCTION_UNBALANCE_VOLTAGE )
    {
        FLG_UNBALANCE_VOLTAGE_STATUS=0;
        return DLT_RET_UNSUPPORT;
    }
    else
    {
        if(isFlashFree)
        {
            return UnbalanceVoltageMode_34();
        }
        else
        {
            return DLT_RET_UNFINISHED;
        }
    }
}










































