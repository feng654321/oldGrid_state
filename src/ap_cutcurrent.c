#ifndef __AP_CUTCURRENT_C__
#define __AP_CUTCURRENT_C__
#include "common.h"

#define CUTCURRENT_TYPE_A 0
#define CUTCURRENT_TYPE_B 1
#define CUTCURRENT_TYPE_C 2

void CutCurrentStart(uchar ucType);
void CutCurrentEnd(uchar ucType);
void CutCurrentTimeAdd(void);
uchar CutCurrentMode_34(void);

uchar ucTempCutCurrentAStatusUse,ucTempCutCurrentAContinueTime;
uchar ucTempCutCurrentBStatusUse,ucTempCutCurrentBContinueTime;
uchar ucTempCutCurrentCStatusUse,ucTempCutCurrentCContinueTime;
uchar ucTempCurrentANoHaveStatusUse,ucTempCurrentANoHaveContinueTime;
uchar ucTempCurrentBNoHaveStatusUse,ucTempCurrentBNoHaveContinueTime;
uchar ucTempCurrentCNoHaveStatusUse,ucTempCurrentCNoHaveContinueTime;
u16  uiCutCurrentStartV;
ulong ulCutCurrentStartI;
uchar ucCutCurrentStartTime;
uchar ucCutCurrentAContineTime,ucCutCurrentBContineTime,ucCutCurrentCContineTime;

void CutCurrentParaInit(void)
{
    ReadCoefDataWithCheck(EPL_COEF_CUT_CURRENT_CONDITION, 6, Ap_temp, 1);
    uiCutCurrentStartV= HexFromRam2Bcd(Ap_temp);
    ulCutCurrentStartI= HexFromRam3Bcd(Ap_temp+2);// xx dot xx
    ucCutCurrentStartTime=HexFromRam1Bcd((Ap_temp+5));
    if(ucCutCurrentStartTime<CONFIG_METER_EVENT_DELAY_MIN_TIME)
        ucCutCurrentStartTime=CONFIG_METER_EVENT_DELAY_MIN_TIME;
}

void CutCurrentInit(void)
{
    FLG_A_CUT_CURRENT_STATUS=0;
    FLG_B_CUT_CURRENT_STATUS=0;
    FLG_C_CUT_CURRENT_STATUS=0;
    ucTempCutCurrentAStatusUse=0;
    ucTempCutCurrentAContinueTime=0;
    ucTempCutCurrentBStatusUse=0;
    ucTempCutCurrentBContinueTime=0;
    ucTempCutCurrentCStatusUse=0;
    ucTempCutCurrentCContinueTime=0;
    CutCurrentParaInit();
    ucCutCurrentAContineTime = 0;
    ucCutCurrentBContineTime = 0;
    ucCutCurrentCContineTime = 0;
}

/*void CutCurrentReJudge(void);
void CutCurrentReJudge(void)
{
    CutCurrentSecond = 0xff;
}*/


void CutCurrentStart(uchar ucType)
{
    ulong ulDataAddr;
    
    if(CUTCURRENT_TYPE_A==ucType)
    {
        FLG_A_CUT_CURRENT_STATUS = GAL_YES;
        EVENT_CONTINUE_TIME_START_INIT(ucCutCurrentAContineTime, ucCutCurrentStartTime);
    }
    else if(CUTCURRENT_TYPE_B==ucType)
    {
        FLG_B_CUT_CURRENT_STATUS = GAL_YES;
        EVENT_CONTINUE_TIME_START_INIT(ucCutCurrentBContineTime, ucCutCurrentStartTime);
    }
    else if(CUTCURRENT_TYPE_C==ucType)
    {
        FLG_C_CUT_CURRENT_STATUS = GAL_YES;
        EVENT_CONTINUE_TIME_START_INIT(ucCutCurrentCContineTime, ucCutCurrentStartTime);
    }
    else
    {
        return ;
    }
    FLG_CUT_CURRENT_ALARM = GAL_CLR;
    
    // Total Count
    //Data3ByteBCDAdd1(EPL_TOTAL_CUT_I_COUNT_TOTAL);
    
    // Current Phase
    Data3ByteBCDAdd1(EPL_TOTAL_CUT_AI_COUNT_TOTAL+4*ucType);
    
    // Total StartTime
    //SetTimeDataToPoint(&Wr_data[0]);
    //memset(&Wr_data[6],0,6);
    //WriteDataDirect(&Wr_data[0], EPL_TOTAL_CUT_I_LAST_START,  12);
    
#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Current Phase StartTime Add End Time
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_CUT_AI_LAST_START+112*ucType,  12);
#endif
    
    ulDataAddr=SetTwoTableNextPoint(TYPE_CUT_A_CURRENT_RECORD+ucType);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetEventStartDataLossVoltagetoAddr(&Wr_data[0]);
        memset(&Wr_data[125], 0x00, 86);
        
        WriteDataDirect(&Wr_data[0], ulDataAddr,  211);
    }
    ClrFlashMode();
}

void CutCurrentEnd(uchar ucType)
{
    ulong ulDataAddr;
        
    if(CUTCURRENT_TYPE_A==ucType)
        FLG_A_CUT_CURRENT_STATUS = GAL_NO;
    else if(CUTCURRENT_TYPE_B==ucType)
        FLG_B_CUT_CURRENT_STATUS = GAL_NO;
    else if(CUTCURRENT_TYPE_C==ucType)
        FLG_C_CUT_CURRENT_STATUS = GAL_NO;
    else 
        return;

    CutCurrentMinTimeAdd();
    
    // Total End Time
    //SetTimeDataToPoint(&Wr_data[0]);
    //WriteDataDirect(&Wr_data[0], EPL_TOTAL_CUT_I_LAST_START+6,  6);

#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Current Phase  End Time
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_CUT_AI_LAST_START+6+112*ucType,  6);
#endif

    ulDataAddr=GetTwoTableAddrFromBlock(TYPE_CUT_A_CURRENT_RECORD+ucType,0,125);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetEventEndDataLossVoltagetoAddr(&Wr_data[0]);
        WriteDataDirect(&Wr_data[0], ulDataAddr,  86);
    }

}

void CutCurrentStopIfStart(void)
{
    if(GAL_YES == FLG_A_CUT_CURRENT_STATUS)
    {
        CutCurrentEnd(CUTCURRENT_TYPE_A);
    }
    if(GAL_YES == FLG_B_CUT_CURRENT_STATUS)
    {
        CutCurrentEnd(CUTCURRENT_TYPE_B);
    }
    if(GAL_YES == FLG_C_CUT_CURRENT_STATUS)
    {
        CutCurrentEnd(CUTCURRENT_TYPE_C);
    }
    FLG_A_CURRENT_NOHAVE_STATUS=GAL_NO;
    FLG_B_CURRENT_NOHAVE_STATUS=GAL_NO;
    FLG_C_CURRENT_NOHAVE_STATUS=GAL_NO;
}

void CutCurrentSecTimeAdd(void)
{
    if(GAL_YES == FLG_A_CUT_CURRENT_STATUS)
    {
        ucCutCurrentAContineTime++;
    }
    if(GAL_YES == FLG_B_CUT_CURRENT_STATUS)
    {
        ucCutCurrentBContineTime++;
    }
    if(GAL_YES == FLG_C_CUT_CURRENT_STATUS)
    {
        ucCutCurrentBContineTime++;
    }
}

void CutCurrentMinTimeAdd(void)
{
    if(ucCutCurrentAContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_CUT_AI_TIME_TOTAL);
        ucCutCurrentAContineTime -= 60;
    }
    if(ucCutCurrentBContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_CUT_BI_TIME_TOTAL);
        ucCutCurrentBContineTime -= 60;
    }
    if(ucCutCurrentCContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_CUT_CI_TIME_TOTAL);
        ucCutCurrentCContineTime -= 60;
    }
}
uchar CutCurrentMode_34(void)
{
    uchar ucTempA,ucTempB,ucTempC,ucStatus;

    ucTempA=0;
    ucTempB=0;
    ucTempC=0;
    if((ulCutCurrentStartI>ulNowCurrent[0]) && (uiCutCurrentStartV<=uiNowVoltage[0]))
    {
        ucTempA=1;
    }
    if(METERTYPE_3_3!=PROGFUNCTION_TYPE_METER_TYPE  )
    {
        if((ulCutCurrentStartI>ulNowCurrent[1]) && (uiCutCurrentStartV<=uiNowVoltage[1]))
        {
            ucTempB=1;
        }
    }
    if((ulCutCurrentStartI>ulNowCurrent[2]) && (uiCutCurrentStartV<=uiNowVoltage[2]))
    {
        ucTempC=1;
    }

       
    //========================================================
    // Phase A
    ucStatus=FLG_A_CUT_CURRENT_STATUS;
    
    if(1==TranslateStatus0or1(&ucStatus,&ucTempCutCurrentAStatusUse,
        &ucTempCutCurrentAContinueTime,ucCutCurrentStartTime,ucTempA))
    {
        if(GAL_YES==ucStatus)
        {
            CutCurrentStart(CUTCURRENT_TYPE_A);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED;
        }
        else
        {
            CutCurrentEnd(CUTCURRENT_TYPE_A);
        }
    }
    
    // Phase B
    if(METERTYPE_3_3!=PROGFUNCTION_TYPE_METER_TYPE  )
    {
        ucStatus=FLG_B_CUT_CURRENT_STATUS;
        if(1==TranslateStatus0or1(&ucStatus,&ucTempCutCurrentBStatusUse,
            &ucTempCutCurrentBContinueTime,ucCutCurrentStartTime,ucTempB))
        {
            if(GAL_YES==ucStatus)
            {
                CutCurrentStart(CUTCURRENT_TYPE_B);
                if(isFlashBusy)
                    return DLT_RET_UNFINISHED;
            }
            else
            {
                CutCurrentEnd(CUTCURRENT_TYPE_B);
            }
        }
    }
    else
    {
        FLG_B_CUT_CURRENT_STATUS=GAL_NO;
    }
    // Phase C
    ucStatus=FLG_C_CUT_CURRENT_STATUS;
    if(1==TranslateStatus0or1(&ucStatus,&ucTempCutCurrentCStatusUse,
        &ucTempCutCurrentCContinueTime,ucCutCurrentStartTime,ucTempC))
    {
        if(GAL_YES==ucStatus)
        {
            CutCurrentStart(CUTCURRENT_TYPE_C);
            //后面还有纯内存操作，可以同步让他做完
            //if(isFlashBusy)
            //    return DLT_RET_UNFINISHED;
        }
        else
        {
            CutCurrentEnd(CUTCURRENT_TYPE_C);
        }
    }
//----------无电流判断条件-----------------------------------   
    if(ulCutCurrentStartI>=ulNowCurrent[0])
    {
        ucTempA=1;
    }
    if(METERTYPE_3_3!=PROGFUNCTION_TYPE_METER_TYPE  )
    {
        if(ulCutCurrentStartI>=ulNowCurrent[1])
        {
            ucTempB=1;
        }
    }
    if(ulCutCurrentStartI>=ulNowCurrent[2])
    {
        ucTempC=1;
    }
    ucStatus=FLG_A_CURRENT_NOHAVE_STATUS;
    if(1==TranslateStatus0or1(&ucStatus,&ucTempCurrentANoHaveStatusUse,
        &ucTempCurrentANoHaveContinueTime,ucCutCurrentStartTime,ucTempA))
    {
        if(GAL_YES==ucStatus)
        {
            FLG_A_CURRENT_NOHAVE_STATUS=GAL_YES;
        }
        else
        {
            FLG_A_CURRENT_NOHAVE_STATUS=GAL_NO;
        }
    }
    if(METERTYPE_3_3!=PROGFUNCTION_TYPE_METER_TYPE  )
    {
        ucStatus=FLG_B_CURRENT_NOHAVE_STATUS;
        if(1==TranslateStatus0or1(&ucStatus,&ucTempCurrentBNoHaveStatusUse,
            &ucTempCurrentBNoHaveContinueTime,ucCutCurrentStartTime,ucTempB))
        {
            if(GAL_YES==ucStatus)
            {
                FLG_B_CURRENT_NOHAVE_STATUS=GAL_YES;
            }
            else
            {
                FLG_B_CURRENT_NOHAVE_STATUS=GAL_NO;
            }
        }
    }
    else
    {
        FLG_B_CURRENT_NOHAVE_STATUS=GAL_NO;
    }
    ucStatus=FLG_C_CURRENT_NOHAVE_STATUS;
    if(1==TranslateStatus0or1(&ucStatus,&ucTempCurrentCNoHaveStatusUse,
        &ucTempCurrentCNoHaveContinueTime,ucCutCurrentStartTime,ucTempC))
    {
        if(GAL_YES==ucStatus)
        {
            FLG_C_CURRENT_NOHAVE_STATUS=GAL_YES;
        }
        else
        {
            FLG_C_CURRENT_NOHAVE_STATUS=GAL_NO;
        }
    }
    return DLT_RET_SUCC;
}


uchar CutCurrentMode(void)
{

    if(isSystemResetUnfinisded)
        return DLT_RET_SUCC;
    
    if(GAL_NO == PROGFUNCTION_CUT_CURRENT )
    {
        FLG_A_CUT_CURRENT_STATUS=0;
        FLG_B_CUT_CURRENT_STATUS=0;
        FLG_C_CUT_CURRENT_STATUS=0;
        return DLT_RET_NO_HAPPEN;
    }
    else
    {
        if(isFlashFree)
        {
            return CutCurrentMode_34();
        }
        else
        {
            return DLT_RET_UNFINISHED;
        }
    }
}

#endif

