#define AP_UNBALANCECURRENT_GLOBALS
#include "common.h"

uchar ucTempUnbalanceCurrentStatusUse,ucTempUnbalanceCurrentContinueTime;
uchar ucTempUnbalanceSeverityCurrentStatusUse,ucTempUnbalanceSeverityCurrentContinueTime;

u16 uiUnbalanceCurrentStartI;
uchar ucUnbalanceCurrentStartTime;
u16 uiUnbalanceSeverityCurrentStartI;
uchar ucUnbalanceSeverityCurrentStartTime;
uchar ucUnbalanceCurrentContineTime;
//uchar ucUnbalanceSeverityCurrentContineTime;

void UnbalanceCurrentParaInit(void)
{
    ReadCoefDataWithCheck(EPL_COEF_UNBALANCE_CURRENT_CONDITION, 3, Ap_temp, 1);
    uiUnbalanceCurrentStartI=HexFromRam2Bcd(Ap_temp);
    ucUnbalanceCurrentStartTime=HexFromRam1Bcd((Ap_temp+2));
    if(ucUnbalanceCurrentStartTime<CONFIG_METER_EVENT_DELAY_MIN_TIME)
        ucUnbalanceCurrentStartTime=CONFIG_METER_EVENT_DELAY_MIN_TIME;
    
    ReadCoefDataWithCheck(EPL_COEF_UNBALANCE_SEVERITY_CURRENT_CONDITION, 3, Ap_temp, 1);
    uiUnbalanceSeverityCurrentStartI=HexFromRam2Bcd(Ap_temp);
    ucUnbalanceSeverityCurrentStartTime=HexFromRam1Bcd((Ap_temp+2));
    if(ucUnbalanceSeverityCurrentStartTime<CONFIG_METER_EVENT_DELAY_MIN_TIME)
        ucUnbalanceSeverityCurrentStartTime=CONFIG_METER_EVENT_DELAY_MIN_TIME;
}

void UnbalanceCurrentInit(void)
{
    FLG_UNBALANCE_CURRENT_STATUS=0;
    FLG_UNBALANCE_SEVERITY_CURRENT_STATUS = 0;
    ucTempUnbalanceCurrentStatusUse=0;
    ucTempUnbalanceCurrentContinueTime=0;
    UnbalanceCurrentParaInit();
    ucUnbalanceCurrentContineTime = 0;
    //ucUnbalanceSeverityCurrentContineTime=0;
}

void UnbalanceCurrentStart(void)
{
    ulong ulDataAddr;

    FLG_UNBALANCE_CURRENT_STATUS=GAL_YES;
    EVENT_CONTINUE_TIME_START_INIT(ucUnbalanceCurrentContineTime, ucUnbalanceCurrentStartTime);

    // Total Count
    Data3ByteBCDAdd1(EPL_TOTAL_UNBALANCE_CURRENT_COUNT_TOTAL);

#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Total StartTime
    SetTimeDataToPoint(&Wr_data[0]);
    memset(&Wr_data[6],0,6);
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_UNBALANCE_CURRENT_LAST_START,  12);
#endif  
    
    memset(&RAM[RAM_CURRENT_UNBALANCE_CURRENT_MAXDATA],0,3);
    ulDataAddr=SetTwoTableNextPoint(TYPE_UNBALANCE_CURRENT_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetEventStartDataLossVoltagetoAddr(&Wr_data[0]);
        memset(&Wr_data[125], 0x00, 89);
        
        WriteDataDirect(&Wr_data[0], ulDataAddr,  214);
    }
    ClrFlashMode();
}

void UnbalanceCurrentStopIfStart(void)
{
    if(GAL_YES == FLG_UNBALANCE_CURRENT_STATUS)
    {
        UnbalanceCurrentEnd();
    }
    
}


void UnbalanceCurrentEnd(void)
{
    ulong ulDataAddr;
    
    FLG_UNBALANCE_CURRENT_STATUS=GAL_NO;
    UnbalanceCurrentMinTimeAdd();
    
#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Total End Time
    SetTimeDataToPoint(&Wr_data[0]);
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_UNBALANCE_CURRENT_LAST_START+6,  6);
#endif  
    
    ulDataAddr=GetTwoTableAddrFromBlock(TYPE_UNBALANCE_CURRENT_RECORD,0,125);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        memcpy(&Wr_data[0],&RAM[RAM_CURRENT_UNBALANCE_CURRENT_MAXDATA],3);
        SetEventEndDataLossVoltagetoAddr(&Wr_data[3]);
        WriteDataDirect(&Wr_data[0], ulDataAddr,  89);
    }

}


void UnbalanceCurrentSecTimeAdd(void)
{
    if(GAL_YES == FLG_UNBALANCE_CURRENT_STATUS)
    {
        ucUnbalanceCurrentContineTime++;
    }
}

void UnbalanceCurrentMinTimeAdd(void)
{
    if(ucUnbalanceCurrentContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_UNBALANCE_CURRENT_TIME_TOTAL);
        ucUnbalanceCurrentContineTime -= 60;
    }
}

uchar UnbalanceCurrentMode_34(void)
{
    uchar ucTemp,ucStatus;
    uchar ucTempSeverity;
    ulong ulStartI;
    ulong ulMax,ulMin,ulPinJun;
    ulong ulData;
    
    if(ulNowCurrent[0]>ulNowCurrent[2]) // A>C
    {
        ulMax=ulNowCurrent[0];
        ulMin=ulNowCurrent[2];
    }
    else
    {
        ulMax=ulNowCurrent[2];
        ulMin=ulNowCurrent[0];
    }
    
    if(PROGFUNCTION_TYPE_METER_TYPE!=METERTYPE_3_3)
    {
        if(ulNowCurrent[1]>ulMax)
        {
            ulMax=ulNowCurrent[1];
        }
        else
        {
            if(ulNowCurrent[1]<ulMin)
            {
                ulMin=ulNowCurrent[1];
            }
        }
        ulPinJun=(ulNowCurrent[0]+ulNowCurrent[1]+ulNowCurrent[2])/3;
    }
    else
    {
        ulPinJun=(ulNowCurrent[0]+ulNowCurrent[2])/2;
    }
    
    ucTemp=0;
    ucTempSeverity=0;
    
    ulData=(ulMax-ulMin);
    if(ulPinJun == 0) 
    {
        //ErrPrint("UnbalanceCurrentMode_34 ulPinJun = 0\n");
        ulPinJun=1;
    }

    ulMin=ulData*10000/ulPinJun;
    if(ulMin>30000)
    {
        ulMin=30000;
    }
    //  AA----   最低要有5%的限制   ----AA
    ulStartI=ulTypeIb*50;  // xxx dot x
    if(ulMax>ulStartI)
    {
        ulStartI=uiUnbalanceCurrentStartI;
        if((ulMin)>ulStartI)
        {
            ucTemp=GAL_YES;
        }
        ulStartI=uiUnbalanceSeverityCurrentStartI;
        if((ulMin)>ulStartI)
        {
            ucTempSeverity=GAL_YES;
        }
    }
    
    //========================================================
    ucStatus=FLG_UNBALANCE_CURRENT_STATUS;
    
    if(1==TranslateStatus0or1(&ucStatus,&ucTempUnbalanceCurrentStatusUse,
        &ucTempUnbalanceCurrentContinueTime,ucUnbalanceCurrentStartTime,ucTemp))
    {
        
        if(GAL_YES==ucStatus)
        {
            UnbalanceCurrentStart();
        }
        else
        {
            UnbalanceCurrentEnd();
        }
    }
//  -----最大数据更新----------------->start
    if(GAL_YES==FLG_UNBALANCE_CURRENT_STATUS)
    {
        ulMax=Bcd3DataToLong(&RAM[RAM_CURRENT_UNBALANCE_CURRENT_MAXDATA]);
        if(ulMin>ulMax)
        {
            LongToData3BCD(ulMin, &RAM[RAM_CURRENT_UNBALANCE_CURRENT_MAXDATA]);
        }
    }
//  -----最大数据更新----------------->end

    //========================================================
    ucStatus=FLG_UNBALANCE_SEVERITY_CURRENT_STATUS;
    
    if(1==TranslateStatus0or1(&ucStatus,&ucTempUnbalanceSeverityCurrentStatusUse,
        &ucTempUnbalanceSeverityCurrentContinueTime,ucUnbalanceSeverityCurrentStartTime,ucTempSeverity))
    {
        FLG_UNBALANCE_SEVERITY_CURRENT_STATUS=ucStatus;
        
//      if(GAL_YES==ucStatus)
//      {
//          UnbalanceCurrentStart();
//      }
//      else
//      {
//          UnbalanceCurrentEnd();
//      }
    }
//  -----最大数据更新----------------->start
//  if(GAL_YES==FLG_UNBALANCE_SEVERITY_CURRENT_STATUS)
//  {
//      ulMax=Bcd2DataToInt(&RAM[RAM_CURRENT_UNBALANCE_SEVERITY_CURRENT_MAXDATA]);
//      if(ulMin>ulMax)
//      {
//          IntToData2BCD(ulMin, &RAM[RAM_CURRENT_UNBALANCE_SEVERITY_CURRENT_MAXDATA]);
//      }
//  }
//  -----最大数据更新----------------->end
    return DLT_RET_SUCC;

}


uchar UnbalanceCurrentMode(void)
{

    if(isSystemResetUnfinisded)
        return DLT_RET_SUCC;
    
    if(GAL_NO== PROGFUNCTION_UNBALANCE_CURRENT )
    {
        FLG_UNBALANCE_CURRENT_STATUS=0;
        return DLT_RET_UNSUPPORT;
    }
    else
    {
        if(isFlashFree)
        {
            return UnbalanceCurrentMode_34();
        }
        else
        {
            return DLT_RET_UNFINISHED;
        }
    }
}






















