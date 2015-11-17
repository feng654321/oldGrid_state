#define AP_CUTVOLTAGE_GLOBALS
#include "common.h"






#define CUTVOLTAGE_TYPE_A 0
#define CUTVOLTAGE_TYPE_B 1
#define CUTVOLTAGE_TYPE_C 2

uchar ucTempCutVoltageAStatusUse,ucTempCutVoltageAContinueTime;
uchar ucTempCutVoltageBStatusUse,ucTempCutVoltageBContinueTime;
uchar ucTempCutVoltageCStatusUse,ucTempCutVoltageCContinueTime;

u16  uiCutVoltageStartV;
ulong ulCutVoltageStartI;
uchar ucCutVoltageStartTime;
uchar ucCutVoltageAContineTime,ucCutVoltageBContineTime,ucCutVoltageCContineTime;

void CutVoltageParaInit(void)
{
    ReadCoefDataWithCheck(EPL_COEF_CUT_VOLTAGE_CONDITION, 6, Ap_temp, 1);
    uiCutVoltageStartV=HexFromRam2Bcd(Ap_temp);
    ulCutVoltageStartI=HexFromRam3Bcd(Ap_temp+2);// xx dot xx
    ucCutVoltageStartTime=HexFromRam1Bcd((Ap_temp+5));
    if(ucCutVoltageStartTime<CONFIG_METER_EVENT_DELAY_MIN_TIME)
        ucCutVoltageStartTime=CONFIG_METER_EVENT_DELAY_MIN_TIME;
}
    

void CutVoltageInit(void)
{
    FLG_A_CUT_VOLTAGE_STATUS=0;
    FLG_B_CUT_VOLTAGE_STATUS=0;
    FLG_C_CUT_VOLTAGE_STATUS=0;
    ucTempCutVoltageAStatusUse=0;
    ucTempCutVoltageAContinueTime=0;
    ucTempCutVoltageBStatusUse=0;
    ucTempCutVoltageBContinueTime=0;
    ucTempCutVoltageCStatusUse=0;
    ucTempCutVoltageCContinueTime=0;
    CutVoltageParaInit();
    ucCutVoltageAContineTime = 0;
    ucCutVoltageBContineTime = 0;
    ucCutVoltageCContineTime = 0;
}

/*void CutVoltageReJudge(void);
void CutVoltageReJudge(void)
{
    CutVoltageSecond = 0xff;
}*/


void CutVoltageStart(uchar ucType)
{
    ulong ulDataAddr;
    
    if(CUTVOLTAGE_TYPE_A==ucType)
    {
        FLG_A_CUT_VOLTAGE_STATUS = GAL_YES;
        EVENT_CONTINUE_TIME_START_INIT(ucCutVoltageAContineTime, ucCutVoltageStartTime);
    }
    else if(CUTVOLTAGE_TYPE_B==ucType)
    {
        FLG_B_CUT_VOLTAGE_STATUS = GAL_YES;
        EVENT_CONTINUE_TIME_START_INIT(ucCutVoltageBContineTime, ucCutVoltageStartTime);
    }
    else if(CUTVOLTAGE_TYPE_C==ucType)
    {
        FLG_C_CUT_VOLTAGE_STATUS = GAL_YES;
        EVENT_CONTINUE_TIME_START_INIT(ucCutVoltageCContineTime, ucCutVoltageStartTime);
    }
    else
    {
        return ;
    }
    
    FLG_CUT_VOLTAGE_ALARM = GAL_CLR;
    
    //  Total Count
    //Data3ByteBCDAdd1(EPL_TOTAL_CUT_V_COUNT_TOTAL);
    
    //  Current Phase
    Data3ByteBCDAdd1(EPL_TOTAL_CUT_AV_COUNT_TOTAL+4*ucType);
    
    //  Total StartTime
    //SetTimeDataToPoint(&Wr_data[0]);
    //memset(&Wr_data[6],0,6);
    //WriteDataDirect(&Wr_data[0], EPL_TOTAL_CUT_V_LAST_START,  12);

#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)  
    //  Current Phase StartTime Add End Time
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_CUT_AV_LAST_START+132*ucType,  12);
#endif
    // CLR current ah data
    memset(&RAM[RAM_CURRENT_CUT_AV_AH_ALL+ucType*20],0x00,20);
    ulDataAddr=SetTwoTableNextPoint(TYPE_CUT_A_VOLTAGE_RECORD+ucType);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetEventStartDataLossVoltagetoAddr(&Wr_data[0]);
        memset(&Wr_data[125], 0x00, 106);
        
        WriteDataDirect(&Wr_data[0], ulDataAddr,  231);
    }
    ModuleEventAlarm(GAL_YES);
    ClrFlashMode();
}

void CutVoltageStopIfStart(void)
{
    if(GAL_YES==FLG_A_CUT_VOLTAGE_STATUS)
    {
        CutVoltageEnd(CUTVOLTAGE_TYPE_A);
    }
    if(GAL_YES==FLG_B_CUT_VOLTAGE_STATUS)
    {
        CutVoltageEnd(CUTVOLTAGE_TYPE_B);
    }
    if(GAL_YES==FLG_C_CUT_VOLTAGE_STATUS)
    {
        CutVoltageEnd(CUTVOLTAGE_TYPE_C);
    }
}


void CutVoltageEnd(uchar ucType)
{
    ulong ulDataAddr;
    
    if(CUTVOLTAGE_TYPE_A==ucType)
    {
        FLG_A_CUT_VOLTAGE_STATUS = GAL_NO;
    }
    else if(CUTVOLTAGE_TYPE_B==ucType)
    {
        FLG_B_CUT_VOLTAGE_STATUS = GAL_NO;
    }
    else if(CUTVOLTAGE_TYPE_C==ucType)
    {
        FLG_C_CUT_VOLTAGE_STATUS = GAL_NO;
    }
    else
    {
        return ;
    }
    CutVoltageMinTimeAdd();

    //  Total End Time
    //SetTimeDataToPoint(&Wr_data[0]);
    //WriteDataDirect(&Wr_data[0], EPL_TOTAL_CUT_V_LAST_START+6,  6);
    
#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    //  Current Phase  End Time
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_CUT_AV_LAST_START+6+132*ucType,  6);
#endif
    
    ulDataAddr=GetTwoTableAddrFromBlock(TYPE_CUT_A_VOLTAGE_RECORD+ucType,0,125);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        memcpy(&Wr_data[0], &RAM[RAM_CURRENT_CUT_AV_AH_ALL+ucType*20], 20);
        SetEventEndDataLossVoltagetoAddr(&Wr_data[20]);
        WriteDataDirect(&Wr_data[0], ulDataAddr,  86+20);
    }
    ModuleEventAlarm(GAL_NO);

}

void CutVoltageSecTimeAdd(void)
{
    if(GAL_YES == FLG_A_CUT_VOLTAGE_STATUS)
    {
        ucCutVoltageAContineTime++;
    }
    if(GAL_YES == FLG_B_CUT_VOLTAGE_STATUS)
    {
        ucCutVoltageBContineTime++;
    }
    if(GAL_YES == FLG_C_CUT_VOLTAGE_STATUS)
    {
        ucCutVoltageCContineTime++;
    }
}

void CutVoltageMinTimeAdd(void)
{
    if(ucCutVoltageAContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_CUT_AV_TIME_TOTAL);
        ucCutVoltageAContineTime -= 60;
    }
    if(ucCutVoltageBContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_CUT_BV_TIME_TOTAL);
        ucCutVoltageBContineTime -= 60;
    }
    if(ucCutVoltageCContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_CUT_CV_TIME_TOTAL);
        ucCutVoltageCContineTime -= 60;
    }
}

uchar CutVoltageMode_33(void)
{
    uchar ucTempA,ucTempC,ucStatus;
    uchar ucTempB,ucTempCurrentB;
    u16 uiTempVACsub;
        
    ucTempA=GAL_NO;
    ucTempB=GAL_NO;
    ucTempC=GAL_NO;
    ucTempCurrentB=GAL_NO;
    
    if((ulCutVoltageStartI<ulNowCurrent[0])||(ulCutVoltageStartI<ulNowCurrent[2]))
    {
        ucTempCurrentB=GAL_YES;
    }
    

    if(((uiNowVoltage[0]+uiNowVoltage[2])<uiCutVoltageStartV)&&(GAL_NO==ucTempCurrentB))
    {
        ucTempB=GAL_YES;
    }
    else
    {
        if(uiNowVoltage[0]>uiNowVoltage[2])
        {
            uiTempVACsub=uiNowVoltage[0]-uiNowVoltage[2];
        }
        else
        {
            uiTempVACsub=uiNowVoltage[2]-uiNowVoltage[0];
        }
        
        if(((uiNowVoltage[0]+uiNowVoltage[2])<PROFUNCTION_3P3W_ADD_VOLTAGE)&&(uiTempVACsub<PROFUNCTION_3P3W_SUB_VOLTAGE))
        {
            if(GAL_NO==ucTempCurrentB)
            {
                ucTempB=GAL_YES;
            }
//          else
//          {
//              ucTempB=GAL_NO;
//          }
        }
        else
        {
            ucTempB=GAL_NO;
        }
    }
    if((GAL_YES==ucTempB))
    {
        ucTempA=GAL_NO;
        ucTempC=GAL_NO;
    }
    else
    {
        if((uiCutVoltageStartV>uiNowVoltage[0])&&(ulCutVoltageStartI>ulNowCurrent[0]))
        {
            ucTempA=GAL_YES;
        }
        if((uiCutVoltageStartV>uiNowVoltage[2])&&(ulCutVoltageStartI>ulNowCurrent[2]))
        {
            ucTempC=GAL_YES;
        }
    }
    
    
    
    //  ========================================================
    //  Phase A
    ucStatus=FLG_A_CUT_VOLTAGE_STATUS;
    
    if(1==TranslateStatus0or1(&ucStatus,&ucTempCutVoltageAStatusUse,
        &ucTempCutVoltageAContinueTime,ucCutVoltageStartTime,ucTempA))
    {
        
        if(GAL_YES==ucStatus)
        {
            CutVoltageStart(CUTVOLTAGE_TYPE_A);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED;
        }
        else
        {
            CutVoltageEnd(CUTVOLTAGE_TYPE_A);
        }
    }
    
    //  Phase B
    ucStatus=FLG_B_CUT_VOLTAGE_STATUS;
    if(1==TranslateStatus0or1(&ucStatus,&ucTempCutVoltageBStatusUse,
        &ucTempCutVoltageBContinueTime,ucCutVoltageStartTime,ucTempB))
    {
        if(GAL_YES==ucStatus)
        {
            CutVoltageStart(CUTVOLTAGE_TYPE_B);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED;
        }
        else
        {
            CutVoltageEnd(CUTVOLTAGE_TYPE_B);
        }
    }
    //  Phase C
    ucStatus=FLG_C_CUT_VOLTAGE_STATUS;
    if(1==TranslateStatus0or1(&ucStatus,&ucTempCutVoltageCStatusUse,
        &ucTempCutVoltageCContinueTime,ucCutVoltageStartTime,ucTempC))
    {
        if(GAL_YES==ucStatus)
        {
            CutVoltageStart(CUTVOLTAGE_TYPE_C);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED2;
        }
        else
        {
            CutVoltageEnd(CUTVOLTAGE_TYPE_C);
        }
    }
    return DLT_RET_SUCC;
}
uchar CutVoltageMode_34(void)
{
    uchar ucTempA,ucTempB,ucTempC,ucStatus;
    
    ucTempA=0;
    ucTempB=0;
    ucTempC=0;
    
    
    if((uiCutVoltageStartV>uiNowVoltage[0])&&(ulCutVoltageStartI>ulNowCurrent[0]))
    {
        ucTempA=1;
    }
    
    if((uiCutVoltageStartV>uiNowVoltage[1])&&(ulCutVoltageStartI>ulNowCurrent[1]))
    {
        ucTempB=1;
    }
    
    if((uiCutVoltageStartV>uiNowVoltage[2])&&(ulCutVoltageStartI>ulNowCurrent[2]))
    {
        ucTempC=1;
    }
    

    //  ========================================================
    //  Phase A
    ucStatus=FLG_A_CUT_VOLTAGE_STATUS;
    
    if(1==TranslateStatus0or1(&ucStatus,&ucTempCutVoltageAStatusUse,
        &ucTempCutVoltageAContinueTime,ucCutVoltageStartTime,ucTempA))
    {
        
        if(GAL_YES==ucStatus)
        {
            CutVoltageStart(CUTVOLTAGE_TYPE_A);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED;
        }
        else
        {
            CutVoltageEnd(CUTVOLTAGE_TYPE_A);
        }
    }
    
    //  Phase B
    ucStatus=FLG_B_CUT_VOLTAGE_STATUS;
    if(1==TranslateStatus0or1(&ucStatus,&ucTempCutVoltageBStatusUse,
        &ucTempCutVoltageBContinueTime,ucCutVoltageStartTime,ucTempB))
    {
        if(GAL_YES==ucStatus)
        {
            CutVoltageStart(CUTVOLTAGE_TYPE_B);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED;
        }
        else
        {
            CutVoltageEnd(CUTVOLTAGE_TYPE_B);
        }
    }
    
    //  Phase C
    ucStatus=FLG_C_CUT_VOLTAGE_STATUS;
    if(1==TranslateStatus0or1(&ucStatus,&ucTempCutVoltageCStatusUse,
        &ucTempCutVoltageCContinueTime,ucCutVoltageStartTime,ucTempC))
    {
        if(GAL_YES==ucStatus)
        {
            CutVoltageStart(CUTVOLTAGE_TYPE_C);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED2;
        }
        else
        {
            CutVoltageEnd(CUTVOLTAGE_TYPE_C);
        }
    }
    return DLT_RET_SUCC;
    
}


uchar CutVoltageMode(void)
{

    if(isSystemResetUnfinisded)
        return DLT_RET_SUCC;
    
    if(GAL_NO== PROGFUNCTION_CUT_VOLTAGE )
    {
        FLG_A_CUT_VOLTAGE_STATUS=0;
        FLG_B_CUT_VOLTAGE_STATUS=0;
        FLG_C_CUT_VOLTAGE_STATUS=0;
        return DLT_RET_NO_HAPPEN;
    }
    else
    {
        if(isFlashFree)
        {
            if(PROGFUNCTION_TYPE_METER_TYPE==METERTYPE_3_3)
            {
                return CutVoltageMode_33();
            }
            else
            {
                return CutVoltageMode_34();
            }
        }
        else
        {
            return DLT_RET_UNFINISHED;
        }
    }
}



