#define AP_LOSSCURRENT_GLOBALS
#include "common.h"

#define LOSSCURRENT_TYPE_A 0
#define LOSSCURRENT_TYPE_B 1
#define LOSSCURRENT_TYPE_C 2

uchar ucTempLossCurrentAStatusUse,ucTempLossCurrentAContinueTime;
uchar ucTempLossCurrentBStatusUse,ucTempLossCurrentBContinueTime;
uchar ucTempLossCurrentCStatusUse,ucTempLossCurrentCContinueTime;

u16  uiLossCurrentStartV;
ulong ulLossCurrentStartI;
ulong ulLossCurrentulMinI;
uchar ucLossCurrentStartTime;
uchar ucLossCurrentAContineTime,ucLossCurrentBContineTime,ucLossCurrentCContineTime;

void LossCurrentParaInit(void)
{
    ReadCoefDataWithCheck(EPL_COEF_LOSS_CURRENT_CONDITION, 9, Ap_temp, 1);
    uiLossCurrentStartV=HexFromRam2Bcd(Ap_temp);
    ulLossCurrentStartI=HexFromRam3Bcd(Ap_temp+2);
    ulLossCurrentulMinI=HexFromRam3Bcd(Ap_temp+5);
    if(ulLossCurrentulMinI<ulLossCurrentStartI)
    {
        ulLossCurrentulMinI=ulLossCurrentStartI;
    }
    ucLossCurrentStartTime=HexFromRam1Bcd((Ap_temp+8));
    if(ucLossCurrentStartTime<CONFIG_METER_EVENT_DELAY_MIN_TIME)
        ucLossCurrentStartTime=CONFIG_METER_EVENT_DELAY_MIN_TIME;
}
    
void LossCurrentInit(void)
{
    FLG_A_LOSS_CURRENT_STATUS=0;
    FLG_B_LOSS_CURRENT_STATUS=0;
    FLG_C_LOSS_CURRENT_STATUS=0;
    ucTempLossCurrentAStatusUse=0;
    ucTempLossCurrentAContinueTime=0;
    ucTempLossCurrentBStatusUse=0;
    ucTempLossCurrentBContinueTime=0;
    ucTempLossCurrentCStatusUse=0;
    ucTempLossCurrentCContinueTime=0;
    LossCurrentParaInit();
}

/*void LossCurrentReJudge(void);
void LossCurrentReJudge(void)
{
    LossCurrentSecond = 0xff;
}*/


void LossCurrentStart(uchar ucType)
{
    ulong ulDataAddr;
        
    if(LOSSCURRENT_TYPE_A==ucType)
    {
        FLG_A_LOSS_CURRENT_STATUS = GAL_YES;
        EVENT_CONTINUE_TIME_START_INIT(ucLossCurrentAContineTime, ucLossCurrentStartTime);
    }
    else if(LOSSCURRENT_TYPE_B==ucType)
    {
        FLG_B_LOSS_CURRENT_STATUS = GAL_YES;
        EVENT_CONTINUE_TIME_START_INIT(ucLossCurrentBContineTime, ucLossCurrentStartTime);
    }
    else if(LOSSCURRENT_TYPE_C==ucType)
    {
        FLG_C_LOSS_CURRENT_STATUS = GAL_YES;
        EVENT_CONTINUE_TIME_START_INIT(ucLossCurrentCContineTime, ucLossCurrentStartTime);
    }
    else
    {
        return ;
    }

    FLG_LOSS_CURRENT_ALARM = GAL_CLR;
    // Total Count
//  Data3ByteBCDAdd1(EPL_TOTAL_LOSS_I_COUNT_TOTAL);
    // Current Phase
    Data3ByteBCDAdd1(EPL_TOTAL_LOSS_AI_COUNT_TOTAL+4*ucType);
    // Total StartTime
//  SetTimeDataToPoint(&Wr_data[0]);
//  memset(&Wr_data[6],0,6);
//  WriteDataDirect(&Wr_data[0], EPL_TOTAL_LOSS_I_LAST_START,  12);
    
#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Current Phase StartTime Add End Time
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_LOSS_AI_LAST_START+112*ucType,  12);
#endif
    
    ulDataAddr=SetTwoTableNextPoint(TYPE_LOSS_A_CURRENT_RECORD+ucType);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetEventStartDataLossVoltagetoAddr(&Wr_data[0]);
        memset(&Wr_data[125], 0x00, 86);
        
        WriteDataDirect(&Wr_data[0], ulDataAddr,  211);
    }
    ClrFlashMode();
}
void LossCurrentStopIfStart(void)
{
    if(GAL_YES==FLG_A_LOSS_CURRENT_STATUS)
    {
        LossCurrentEnd(LOSSCURRENT_TYPE_A);
    }
    if(GAL_YES==FLG_B_LOSS_CURRENT_STATUS)
    {
        LossCurrentEnd(LOSSCURRENT_TYPE_B);
    }
    if(GAL_YES==FLG_C_LOSS_CURRENT_STATUS)
    {
        LossCurrentEnd(LOSSCURRENT_TYPE_C);
    }

}

void LossCurrentEnd(uchar ucType)
{
    ulong ulDataAddr;
    
    if(LOSSCURRENT_TYPE_A==ucType)
    {
        FLG_A_LOSS_CURRENT_STATUS = GAL_NO;
    }
    else if(LOSSCURRENT_TYPE_B==ucType)
    {
        FLG_B_LOSS_CURRENT_STATUS = GAL_NO;
    }
    else if(LOSSCURRENT_TYPE_C==ucType)
    {
        FLG_C_LOSS_CURRENT_STATUS = GAL_NO;
    }
    else
    {
        return ;
    }
    LossCurrentMinTimeAdd();
    
    // Total End Time
    //SetTimeDataToPoint(&Wr_data[0]);
    //WriteDataDirect(&Wr_data[0], EPL_TOTAL_LOSS_I_LAST_START+6,  6);

#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Current Phase  End Time
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_LOSS_AI_LAST_START+6+112*ucType,  6);
#endif

    ulDataAddr=GetTwoTableAddrFromBlock(TYPE_LOSS_A_CURRENT_RECORD+ucType,0,125);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetEventEndDataLossVoltagetoAddr(&Wr_data[0]);
        WriteDataDirect(&Wr_data[0], ulDataAddr,  86);
    }

}

void LossCurrentSecTimeAdd(void)
{
    if(GAL_YES == FLG_A_LOSS_CURRENT_STATUS)
    {
        ucLossCurrentAContineTime++;
    }
    if(GAL_YES == FLG_B_LOSS_CURRENT_STATUS)
    {
        ucLossCurrentBContineTime++;
    }
    if(GAL_YES == FLG_C_LOSS_CURRENT_STATUS)
    {
        ucLossCurrentCContineTime++;
    }
}

void LossCurrentMinTimeAdd(void)
{
    if(ucLossCurrentAContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_LOSS_AI_TIME_TOTAL);
        ucLossCurrentAContineTime -= 60;
    }
    if(ucLossCurrentBContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_LOSS_BI_TIME_TOTAL);
        ucLossCurrentBContineTime -= 60;
    }
    if(ucLossCurrentCContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_LOSS_CI_TIME_TOTAL);
        ucLossCurrentCContineTime -= 60;
    }
}

uchar LossCurrentMode_34(void)
{
    uchar ucTempA,ucTempB,ucTempC,ucStatus;

    ucTempA=0;
    ucTempB=0;
    ucTempC=0;
    ucStatus=1;
    if(uiNowVoltage[0]<uiLossCurrentStartV)
    {
        ucStatus=0;
    }
    if(METERTYPE_3_3!=PROGFUNCTION_TYPE_METER_TYPE  )
    {
        if(uiNowVoltage[1]<uiLossCurrentStartV)
        {
            ucStatus=0;
        }
    }
    if(uiNowVoltage[2]<uiLossCurrentStartV)
    {
        ucStatus=0;
    }


    if((1==ucStatus)&&((ulNowCurrent[0]>ulLossCurrentulMinI)||(ulNowCurrent[1]>ulLossCurrentulMinI)||(ulNowCurrent[2]>ulLossCurrentulMinI)))
    {
        if((ulLossCurrentStartI>ulNowCurrent[0]))
        {
            ucTempA=GAL_YES;
        }
        if(METERTYPE_3_3!=PROGFUNCTION_TYPE_METER_TYPE  )
        {
            if((ulLossCurrentStartI>ulNowCurrent[1]))
            {
                ucTempB=GAL_YES;
            }
        }
        
        if((ulLossCurrentStartI>ulNowCurrent[2]))
        {
            ucTempC=GAL_YES;
        }
    }
    
    // AA  没有全失流概念，所以如果是全失流，则全部都不失流  AA
    if((GAL_YES==ucTempA)&&(GAL_YES==ucTempB)&&(GAL_YES==ucTempC)&&(METERTYPE_3_3!=PROGFUNCTION_TYPE_METER_TYPE  ))
    {
        ucTempA=GAL_NO;
        ucTempB=GAL_NO;
        ucTempC=GAL_NO;
    }
    if((GAL_YES==ucTempA)&&(GAL_YES==ucTempC)&&(METERTYPE_3_3==PROGFUNCTION_TYPE_METER_TYPE  ))
    {
        ucTempA=GAL_NO;
        ucTempC=GAL_NO;
    }
    if(METERTYPE_3_3==PROGFUNCTION_TYPE_METER_TYPE  )
    {
        ucTempB=GAL_NO;
    }
        
    //========================================================
    // Phase A
    ucStatus=FLG_A_LOSS_CURRENT_STATUS;
    
    if(1==TranslateStatus0or1(&ucStatus,&ucTempLossCurrentAStatusUse,
        &ucTempLossCurrentAContinueTime,ucLossCurrentStartTime,ucTempA))
    {
        
        if(GAL_YES==ucStatus)
        {
            LossCurrentStart(LOSSCURRENT_TYPE_A);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED;
        }
        else
        {
            LossCurrentEnd(LOSSCURRENT_TYPE_A);
        }
    }
    
    // Phase B
    if(METERTYPE_3_3!=PROGFUNCTION_TYPE_METER_TYPE  )
    {
        ucStatus=FLG_B_LOSS_CURRENT_STATUS;
        if(1==TranslateStatus0or1(&ucStatus,&ucTempLossCurrentBStatusUse,
            &ucTempLossCurrentBContinueTime,ucLossCurrentStartTime,ucTempB))
        {
            if(GAL_YES==ucStatus)
            {
                LossCurrentStart(LOSSCURRENT_TYPE_B);
                if(isFlashBusy)
                    return DLT_RET_UNFINISHED;
            }
            else
            {
                LossCurrentEnd(LOSSCURRENT_TYPE_B);
            }
        }
    }
    else
    {
        FLG_B_LOSS_CURRENT_STATUS=GAL_NO;
    }
    
    // Phase C
    ucStatus=FLG_C_LOSS_CURRENT_STATUS;
    if(1==TranslateStatus0or1(&ucStatus,&ucTempLossCurrentCStatusUse,
        &ucTempLossCurrentCContinueTime,ucLossCurrentStartTime,ucTempC))
    {
        if(GAL_YES==ucStatus)
        {
            LossCurrentStart(LOSSCURRENT_TYPE_C);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED2;
        }
        else
        {
            LossCurrentEnd(LOSSCURRENT_TYPE_C);
        }
    }
    return DLT_RET_SUCC;
}

uchar LossCurrentMode(void)
{

    if(isSystemResetUnfinisded)
        return DLT_RET_SUCC;
    
    if(GAL_NO == PROGFUNCTION_LOSS_CURRENT )
    {
        FLG_A_LOSS_CURRENT_STATUS=0;
        FLG_B_LOSS_CURRENT_STATUS=0;
        FLG_C_LOSS_CURRENT_STATUS=0;
        return DLT_RET_NO_HAPPEN;
    }
    else
    {
        if(isFlashFree)
        {
            return LossCurrentMode_34();
        }
        else
        {
            return DLT_RET_UNFINISHED;
        }
    }
}
























