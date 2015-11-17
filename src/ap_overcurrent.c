#define AP_OVERCURRENT_GLOBALS
#include "common.h"







#define OVERCURRENT_TYPE_A 0
#define OVERCURRENT_TYPE_B 1
#define OVERCURRENT_TYPE_C 2

// uchar ucTempOverCurrentAStatus,ucTempOverCurrentAStatusUse,ucTempOverCurrentAContinueTime;
// uchar ucTempOverCurrentBStatus,ucTempOverCurrentBStatusUse,ucTempOverCurrentBContinueTime;
// uchar ucTempOverCurrentCStatus,ucTempOverCurrentCStatusUse,ucTempOverCurrentCContinueTime;

uchar ucTempOverCurrentAStatusUse,ucTempOverCurrentAContinueTime;
uchar ucTempOverCurrentBStatusUse,ucTempOverCurrentBContinueTime;
uchar ucTempOverCurrentCStatusUse,ucTempOverCurrentCContinueTime;

u16  uiOverCurrentStartI;
uchar ucOverCurrentStartTime;
uchar ucOverCurrentAContineTime,ucOverCurrentBContineTime,ucOverCurrentCContineTime;

void OverCurrentParaInit(void)
{
    ReadCoefDataWithCheck(EPL_COEF_OVER_CURRENT_CONDITION, 3, Ap_temp, 1);
    uiOverCurrentStartI=HexFromRam2Bcd(Ap_temp);
    ucOverCurrentStartTime=HexFromRam1Bcd((Ap_temp+2));
    if(ucOverCurrentStartTime<CONFIG_METER_EVENT_DELAY_MIN_TIME)
        ucOverCurrentStartTime=CONFIG_METER_EVENT_DELAY_MIN_TIME;
}

void OverCurrentInit(void)
{
    FLG_A_OVER_CURRENT_STATUS=0;
    FLG_B_OVER_CURRENT_STATUS=0;
    FLG_C_OVER_CURRENT_STATUS=0;
    ucTempOverCurrentAStatusUse=0;
    ucTempOverCurrentAContinueTime=0;
    ucTempOverCurrentBStatusUse=0;
    ucTempOverCurrentBContinueTime=0;
    ucTempOverCurrentCStatusUse=0;
    ucTempOverCurrentCContinueTime=0;
    OverCurrentParaInit();
    ucOverCurrentAContineTime = 0;
    ucOverCurrentBContineTime = 0;
    ucOverCurrentCContineTime = 0;
}

/*void OverCurrentReJudge(void);
void OverCurrentReJudge(void)
{
    OverCurrentSecond = 0xff;
}*/


void OverCurrentStart(uchar ucType)
{
    ulong ulDataAddr;

    if(OVERCURRENT_TYPE_A==ucType)
    {
        FLG_A_OVER_CURRENT_STATUS = GAL_YES;
        EVENT_CONTINUE_TIME_START_INIT(ucOverCurrentAContineTime, ucOverCurrentStartTime);
    }
    else if(OVERCURRENT_TYPE_B==ucType)
    {
        FLG_B_OVER_CURRENT_STATUS = GAL_YES;
        EVENT_CONTINUE_TIME_START_INIT(ucOverCurrentBContineTime, ucOverCurrentStartTime);
    }
    else if(OVERCURRENT_TYPE_C==ucType)
    {
        FLG_C_OVER_CURRENT_STATUS = GAL_YES;
        EVENT_CONTINUE_TIME_START_INIT(ucOverCurrentCContineTime, ucOverCurrentStartTime);
    }
    else
    {
        return ;
    }
    FLG_OVER_CURRENT_ALARM = GAL_CLR;
    // Total Count
    //Data3ByteBCDAdd1(EPL_TOTAL_OVER_I_COUNT_TOTAL);
    // Current Phase
    Data3ByteBCDAdd1(EPL_TOTAL_OVER_AI_COUNT_TOTAL+4*ucType);
    // Total StartTime
    //SetTimeDataToPoint(&Wr_data[0]);
    //memset(&Wr_data[6],0,6);
    //WriteDataDirect(&Wr_data[0], EPL_TOTAL_OVER_I_LAST_START,  12);
    
#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Current Phase StartTime Add End Time
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_OVER_AI_LAST_START+112*ucType,  12);
#endif

    
    ulDataAddr=SetTwoTableNextPoint(TYPE_OVER_A_CURRENT_RECORD+ucType);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetEventStartDataLossVoltagetoAddr(&Wr_data[0]);
        memset(&Wr_data[125], 0x00, 86);
        
        WriteDataDirect(&Wr_data[0], ulDataAddr,  211);
    }
    ClrFlashMode();
}


void OverCurrentStopIfStart(void)
{
    if(GAL_YES == FLG_A_OVER_CURRENT_STATUS)
    {
        OverCurrentEnd(OVERCURRENT_TYPE_A);
    }
    if(GAL_YES == FLG_B_OVER_CURRENT_STATUS)
    {
        OverCurrentEnd(OVERCURRENT_TYPE_B);
    }
    if(GAL_YES == FLG_C_OVER_CURRENT_STATUS)
    {
        OverCurrentEnd(OVERCURRENT_TYPE_C);
    }

}




void OverCurrentEnd(uchar ucType)
{
    ulong ulDataAddr;
    
    if(OVERCURRENT_TYPE_A==ucType)
    {
        FLG_A_OVER_CURRENT_STATUS = GAL_NO;
    }
    else if(OVERCURRENT_TYPE_B==ucType)
    {
        FLG_B_OVER_CURRENT_STATUS = GAL_NO;
    }
    else if(OVERCURRENT_TYPE_C==ucType)
    {
        FLG_C_OVER_CURRENT_STATUS = GAL_NO;
    }
    else
    {
        return ;
    }
    OverCurrentMinTimeAdd();

    // Total End Time
    //SetTimeDataToPoint(&Wr_data[0]);
    //WriteDataDirect(&Wr_data[0], EPL_TOTAL_OVER_I_LAST_START+6,  6);

#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Current Phase  End Time
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_OVER_AI_LAST_START+6+112*ucType,  6);
#endif

    ulDataAddr=GetTwoTableAddrFromBlock(TYPE_OVER_A_CURRENT_RECORD+ucType,0,125);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetEventEndDataLossVoltagetoAddr(&Wr_data[0]);
        WriteDataDirect(&Wr_data[0], ulDataAddr,  86);
    }

}

void OverCurrentSecTimeAdd(void)
{
    if(GAL_YES == FLG_A_OVER_CURRENT_STATUS)
    {
        ucOverCurrentAContineTime++;
    }
    if(GAL_YES == FLG_B_OVER_CURRENT_STATUS)
    {
        ucOverCurrentBContineTime++;
    }
    if(GAL_YES == FLG_C_OVER_CURRENT_STATUS)
    {
        ucOverCurrentCContineTime++;
    }
}

void OverCurrentMinTimeAdd(void)
{
    if(ucOverCurrentAContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_OVER_AI_TIME_TOTAL);
        ucOverCurrentAContineTime -= 60;
    }
    if(ucOverCurrentBContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_OVER_BI_TIME_TOTAL);
        ucOverCurrentBContineTime -= 60;
    }
    if(ucOverCurrentCContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_OVER_CI_TIME_TOTAL);
        ucOverCurrentCContineTime -= 60;
    }
}

uchar OverCurrentMode_34(void)
{
    uchar ucTempA,ucTempB,ucTempC,ucStatus;
    ulong ulStartI;

    ulStartI=uiOverCurrentStartI*1000;
    ucTempA=0;
    ucTempB=0;
    ucTempC=0;
    
    if(ulStartI<ulNowCurrent[0])
    {
        ucTempA=1;
    }
    if(PROGFUNCTION_TYPE_METER_TYPE != METERTYPE_3_3)
    {
        if(ulStartI<ulNowCurrent[1])
        {
            ucTempB=1;
        }
    }
    if(ulStartI<ulNowCurrent[2])
    {
        ucTempC=1;
    }
    
    //========================================================
    // Phase A
    ucStatus=FLG_A_OVER_CURRENT_STATUS;
    
    if(1==TranslateStatus0or1(&ucStatus,&ucTempOverCurrentAStatusUse,
        &ucTempOverCurrentAContinueTime,ucOverCurrentStartTime,ucTempA))
    {
        
        if(GAL_YES==ucStatus)
        {
            OverCurrentStart(OVERCURRENT_TYPE_A);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED;
        }
        else
        {
            OverCurrentEnd(OVERCURRENT_TYPE_A);
        }
    }
    
    // Phase B
    if(PROGFUNCTION_TYPE_METER_TYPE != METERTYPE_3_3)
    {
        ucStatus=FLG_B_OVER_CURRENT_STATUS;
        if(1==TranslateStatus0or1(&ucStatus,&ucTempOverCurrentBStatusUse,
            &ucTempOverCurrentBContinueTime,ucOverCurrentStartTime,ucTempB))
        {
            if(GAL_YES==ucStatus)
            {
                OverCurrentStart(OVERCURRENT_TYPE_B);
                if(isFlashBusy)
                    return DLT_RET_UNFINISHED;
            }
            else
            {
                OverCurrentEnd(OVERCURRENT_TYPE_B);
            }
        }
    }
    else
    {
        FLG_B_OVER_CURRENT_STATUS=GAL_NO;
    }
    // Phase C
    ucStatus=FLG_C_OVER_CURRENT_STATUS;
    if(1==TranslateStatus0or1(&ucStatus,&ucTempOverCurrentCStatusUse,
        &ucTempOverCurrentCContinueTime,ucOverCurrentStartTime,ucTempC))
    {
        if(GAL_YES==ucStatus)
        {
            OverCurrentStart(OVERCURRENT_TYPE_C);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED2;
        }
        else
        {
            OverCurrentEnd(OVERCURRENT_TYPE_C);
        }
    }
    return DLT_RET_SUCC;    
}


uchar OverCurrentMode(void)
{

    if(isSystemResetUnfinisded)
        return DLT_RET_SUCC;
    
    if(GAL_NO == PROGFUNCTION_OVER_CURRENT )
    {
        FLG_A_OVER_CURRENT_STATUS=0;
        FLG_B_OVER_CURRENT_STATUS=0;
        FLG_C_OVER_CURRENT_STATUS=0;
        return DLT_RET_NO_HAPPEN;
    }
    else
    {
        if(isFlashFree)
        {
            return OverCurrentMode_34();
        }
        else
        {
            return DLT_RET_UNFINISHED;
        }
    }
}
















