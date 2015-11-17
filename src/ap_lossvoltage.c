#define AP_LOSSVOLTAGE_GLOBALS
#include "common.h"



#define LOSSVOLTAGE_TYPE_A 0
#define LOSSVOLTAGE_TYPE_B 1
#define LOSSVOLTAGE_TYPE_C 2

uchar ucTempLossVoltageAStatusUse,ucTempLossVoltageAContinueTime;
uchar ucTempLossVoltageBStatusUse,ucTempLossVoltageBContinueTime;
uchar ucTempLossVoltageCStatusUse,ucTempLossVoltageCContinueTime;

    
u16  uiLossVoltageStartV, uiLossVoltageReturnV;
ulong ulLossVoltageStartI;
uchar ucLossVoltageStartTime;
uchar ucLossVoltageAContineTime,ucLossVoltageBContineTime,ucLossVoltageCContineTime,ucLossVoltageTContineTime;
void LossVoltageParaInit(void)
{
    ReadCoefDataWithCheck(EPL_COEF_LOSS_VOLTAGE_CONDITION, 8, Ap_temp, 1);
    uiLossVoltageStartV=HexFromRam2Bcd(Ap_temp);
    uiLossVoltageReturnV=HexFromRam2Bcd(Ap_temp+2);
    if(uiLossVoltageReturnV < uiLossVoltageStartV)
    {
        uiLossVoltageReturnV = uiLossVoltageStartV;
    }
    ulLossVoltageStartI=HexFromRam3Bcd(Ap_temp+4);
    ucLossVoltageStartTime=HexFromRam1Bcd((Ap_temp+7));
    if(ucLossVoltageStartTime<CONFIG_METER_EVENT_DELAY_MIN_TIME)
        ucLossVoltageStartTime=CONFIG_METER_EVENT_DELAY_MIN_TIME;
}

void LossVoltageInit(void)
{
    FLG_A_LOSS_VOLTAGE_STATUS=0;
    FLG_B_LOSS_VOLTAGE_STATUS=0;
    FLG_C_LOSS_VOLTAGE_STATUS=0;
    ucTempLossVoltageAStatusUse=0;
    ucTempLossVoltageAContinueTime=0;
    ucTempLossVoltageBStatusUse=0;
    ucTempLossVoltageBContinueTime=0;
    ucTempLossVoltageCStatusUse=0;
    ucTempLossVoltageCContinueTime=0;
    LossVoltageParaInit();
}


/*void LossVoltageReJudge(void);
void LossVoltageReJudge(void)
{
    LossVoltageSecond = 0xff;
}*/

void LossVoltageStart(uchar ucType)
{
    ulong ulDataAddr;
    
    if(LOSSVOLTAGE_TYPE_A==ucType)
    {
        FLG_A_LOSS_VOLTAGE_STATUS = GAL_YES;
        EVENT_CONTINUE_TIME_START_INIT(ucLossVoltageAContineTime, ucLossVoltageStartTime);
    }
    else if(LOSSVOLTAGE_TYPE_B==ucType)
    {
        FLG_B_LOSS_VOLTAGE_STATUS = GAL_YES;
        EVENT_CONTINUE_TIME_START_INIT(ucLossVoltageBContineTime, ucLossVoltageStartTime);
    }
    else if(LOSSVOLTAGE_TYPE_C==ucType)
    {
        FLG_C_LOSS_VOLTAGE_STATUS = GAL_YES;
        EVENT_CONTINUE_TIME_START_INIT(ucLossVoltageCContineTime, ucLossVoltageStartTime);
    }
    else
    {
        return;
    }
    //合相事件时间初始化
    if((FLG_A_LOSS_VOLTAGE_STATUS+FLG_B_LOSS_VOLTAGE_STATUS+FLG_C_LOSS_VOLTAGE_STATUS) == 1)
    {
        EVENT_CONTINUE_TIME_START_INIT(ucLossVoltageTContineTime, ucCutCurrentStartTime);
    }
    FLG_LOSS_VOLTAGE_ALARM = GAL_CLR;
    // Total Count
    Data3ByteBCDAdd1(EPL_TOTAL_LOSS_V_COUNT_TOTAL);
    // Current Phase
    Data3ByteBCDAdd1(EPL_TOTAL_LOSS_AV_COUNT_TOTAL+4*ucType);
    // Total StartTime
    SetTimeDataToPoint(&Wr_data[0]);
    memset(&Wr_data[6],0,6);
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_LOSS_V_LAST_START,  12);
    
#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Current Phase StartTime Add End Time
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_LOSS_AV_LAST_START+132*ucType,  12);
#endif
    // CLR current ah data
    memset(&RAM[RAM_CURRENT_LOSS_AV_AH_ALL+ucType*20],0x00,20);
    ulDataAddr=SetTwoTableNextPoint(TYPE_LOSS_A_VOLTAGE_RECORD+ucType);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetEventStartDataLossVoltagetoAddr(&Wr_data[0]);
        memset(&Wr_data[125], 0x00, 106);
        
        WriteDataDirect(&Wr_data[0], ulDataAddr,  231);
    }
    ClrFlashMode();
    ModuleEventAlarm(GAL_YES);

}
void LossVoltageStopIfStart(void)
{
    if(GAL_YES==FLG_A_LOSS_VOLTAGE_STATUS)
    {
        LossVoltageEnd(LOSSVOLTAGE_TYPE_A);
    }
    if(GAL_YES==FLG_B_LOSS_VOLTAGE_STATUS)
    {
        LossVoltageEnd(LOSSVOLTAGE_TYPE_B);
    }
    if(GAL_YES==FLG_C_LOSS_VOLTAGE_STATUS)
    {
        LossVoltageEnd(LOSSVOLTAGE_TYPE_C);
    }
    
}


void LossVoltageEnd(uchar ucType)
{
    ulong ulDataAddr;
    
    if(LOSSVOLTAGE_TYPE_A==ucType)
    {
        FLG_A_LOSS_VOLTAGE_STATUS = GAL_NO;
    }
    else if(LOSSVOLTAGE_TYPE_B==ucType)
    {
        FLG_B_LOSS_VOLTAGE_STATUS = GAL_NO;
    }
    else if(LOSSVOLTAGE_TYPE_C==ucType)
    {
        FLG_C_LOSS_VOLTAGE_STATUS = GAL_NO;
    }
    else
    {
        return;
    }
    LossVoltageMinTimeAdd();
    // Total End Time
    SetTimeDataToPoint(&Wr_data[0]);
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_LOSS_V_LAST_START+6,  6);
    
#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Current Phase  End Time
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_LOSS_AV_LAST_START+6+132*ucType,  6);
#endif

    ulDataAddr=GetTwoTableAddrFromBlock(TYPE_LOSS_A_VOLTAGE_RECORD+ucType,0,125);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        memcpy(&Wr_data[0], &RAM[RAM_CURRENT_LOSS_AV_AH_ALL+ucType*20], 20);
        SetEventEndDataLossVoltagetoAddr(&Wr_data[20]);
        WriteDataDirect(&Wr_data[0], ulDataAddr,  86+20);
    }
    ModuleEventAlarm(GAL_NO);

}

void LossVoltageSecTimeAdd(void)
{
    uchar ucValue=0;
    if(GAL_YES == FLG_A_LOSS_VOLTAGE_STATUS)
    {
        ucLossVoltageAContineTime++;
        ucValue=1;
    }
    if(GAL_YES == FLG_B_LOSS_VOLTAGE_STATUS)
    {
        ucLossVoltageBContineTime++;
        ucValue=1;
    }
    if(GAL_YES == FLG_C_LOSS_VOLTAGE_STATUS)
    {
        ucLossVoltageCContineTime++;
        ucValue=1;
    }
    if(ucValue>0)
    {
        ucLossVoltageTContineTime++;
    }
}

void LossVoltageMinTimeAdd(void)
{
    uchar ucValue=0;    //为了时间累加同步，同时为了总时间不会大于三相累计
    if(ucLossVoltageAContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_LOSS_AV_TIME_TOTAL);
        ucLossVoltageAContineTime -= 60;
        ucValue = 1;
    }
    if(ucLossVoltageBContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_LOSS_BV_TIME_TOTAL);
        ucLossVoltageBContineTime -= 60;
        ucValue = 1;
    }
    if(ucLossVoltageCContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_LOSS_CV_TIME_TOTAL);
        ucLossVoltageCContineTime -= 60;
        ucValue = 1;
    }
    if(ucLossVoltageTContineTime >= 60)
    {
        if(ucValue == 1)
        {
            Data3ByteBCDAdd1(RAM_TOTAL_LOSS_V_TIME_TOTAL);
            ucLossVoltageTContineTime -= 60;
        }
    }
}

uchar LossVoltageMode_33(void)
{
    uchar ucTempA,ucTempC,ucStatus;
    uchar ucTempB,ucTempCurrentB;
    u16 uiTempVACsub;
    
    ucTempA=GAL_UNKNOW;
    ucTempB=GAL_UNKNOW;
    ucTempC=GAL_UNKNOW;
    ucTempCurrentB=GAL_NO;
    ucStatus=GAL_NO;
    if((ulLossVoltageStartI<ulNowCurrent[0])||(ulLossVoltageStartI<ulNowCurrent[2]))
    {
        ucTempCurrentB=GAL_YES;
    }
    

    if(((uiNowVoltage[0]+uiNowVoltage[2])<uiLossVoltageStartV)&&(GAL_YES==ucTempCurrentB))
    {
        ucTempB=GAL_YES;
        ucStatus=GAL_YES;
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
            if(GAL_YES==ucTempCurrentB)
            {
                ucTempB=GAL_YES;
            }
//          else
//          {
//              ucTempB=GAL_UNKNOW;
//          }
        }
        else
        {
            ucTempB=GAL_NO;
        }
    }
    if((GAL_UNKNOW==ucTempB)&&(FLG_B_LOSS_VOLTAGE_STATUS))
    {
        ucTempB=GAL_YES;
    }
    
    if(GAL_NO==ucTempB)
    {
        if((uiLossVoltageStartV>uiNowVoltage[0])&&(ulLossVoltageStartI<ulNowCurrent[0]))
        {
            ucTempA=GAL_YES;
        }
        if((uiLossVoltageStartV>uiNowVoltage[2])&&(ulLossVoltageStartI<ulNowCurrent[2]))
        {
            ucTempC=GAL_YES;
        }
#if(CONFIG_METER_AREA_MODE_SHANGHAI!=CONFIG_METER_AREA_MODE)        
        if((uiLossVoltageReturnV<uiNowVoltage[0]))
        {
            ucTempA=GAL_NO;
        }
        if((uiLossVoltageReturnV<uiNowVoltage[2]))
        {
            ucTempC=GAL_NO;
        }
#else
        if((uiLossVoltageReturnV<uiNowVoltage[0])||(ulLossVoltageStartI>=ulNowCurrent[0]))
        {
            ucTempA=GAL_NO;
        }       
        if((uiLossVoltageReturnV<uiNowVoltage[2])||(ulLossVoltageStartI>=ulNowCurrent[2]))
        {
            ucTempC=GAL_NO;
        }
            
#endif
    }
    else
    {
        ucTempA=GAL_NO;
        ucTempC=GAL_NO;     
    }
    if(GAL_YES==ucStatus)
    {
        ucTempA=GAL_YES;
        ucTempB=GAL_YES;
        ucTempC=GAL_YES;
    }
    
    //========================================================
    // Phase A
    ucStatus=FLG_A_LOSS_VOLTAGE_STATUS;
    
    if(1==TranslateStatus0or1(&ucStatus,&ucTempLossVoltageAStatusUse,
        &ucTempLossVoltageAContinueTime,ucLossVoltageStartTime,ucTempA))
    {
        
        if(GAL_YES==ucStatus)
        {
            LossVoltageStart(LOSSVOLTAGE_TYPE_A);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED;
        }
        else
        {
            LossVoltageEnd(LOSSVOLTAGE_TYPE_A);
        }
    }
    
    // Phase B
    ucStatus=FLG_B_LOSS_VOLTAGE_STATUS;
    if(1==TranslateStatus0or1(&ucStatus,&ucTempLossVoltageBStatusUse,
        &ucTempLossVoltageBContinueTime,ucLossVoltageStartTime,ucTempB))
    {
        if(GAL_YES==ucStatus)
        {
            LossVoltageStart(LOSSVOLTAGE_TYPE_B);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED;
        }
        else
        {
            LossVoltageEnd(LOSSVOLTAGE_TYPE_B);
        }
    }
    // Phase C
    ucStatus=FLG_C_LOSS_VOLTAGE_STATUS;
    if(1==TranslateStatus0or1(&ucStatus,&ucTempLossVoltageCStatusUse,
        &ucTempLossVoltageCContinueTime,ucLossVoltageStartTime,ucTempC))
    {
        if(GAL_YES==ucStatus)
        {
            LossVoltageStart(LOSSVOLTAGE_TYPE_C);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED2;
        }
        else
        {
            LossVoltageEnd(LOSSVOLTAGE_TYPE_C);
        }
    }
    return DLT_RET_SUCC;
}
uchar LossVoltageMode_34(void)
{
    uchar ucTempA,ucTempB,ucTempC,ucStatus;
    
    ucTempA=GAL_UNKNOW;
    ucTempB=GAL_UNKNOW;
    ucTempC=GAL_UNKNOW;
    
    
    if((uiLossVoltageStartV>uiNowVoltage[0])&&(ulLossVoltageStartI<ulNowCurrent[0]))
    {
        ucTempA=GAL_YES;
    }
    
    if((uiLossVoltageStartV>uiNowVoltage[1])&&(ulLossVoltageStartI<ulNowCurrent[1]))
    {
        ucTempB=GAL_YES;
    }
    
    if((uiLossVoltageStartV>uiNowVoltage[2])&&(ulLossVoltageStartI<ulNowCurrent[2]))
    {
        ucTempC=GAL_YES;
    }
#if(CONFIG_METER_AREA_MODE_SHANGHAI!=CONFIG_METER_AREA_MODE)    
    if((uiLossVoltageReturnV<uiNowVoltage[0]))
    {
        ucTempA=GAL_NO;
    }
    
    if((uiLossVoltageReturnV<uiNowVoltage[1]))
    {
        ucTempB=GAL_NO;
    }
    
    if((uiLossVoltageReturnV<uiNowVoltage[2]))
    {
        ucTempC=GAL_NO;
    }
#else
    if((uiLossVoltageReturnV<uiNowVoltage[0])||(ulLossVoltageStartI>=ulNowCurrent[0]))
    {
        ucTempA=GAL_NO;
    }
    
    if((uiLossVoltageReturnV<uiNowVoltage[1])||(ulLossVoltageStartI>=ulNowCurrent[1]))
    {
        ucTempB=GAL_NO;
    }
    
    if((uiLossVoltageReturnV<uiNowVoltage[2])||(ulLossVoltageStartI>=ulNowCurrent[2]))
    {
        ucTempC=GAL_NO;
    }
#endif
    
    //========================================================
    // Phase A
    ucStatus=FLG_A_LOSS_VOLTAGE_STATUS;
    
    if(1==TranslateStatus0or1(&ucStatus,&ucTempLossVoltageAStatusUse,
        &ucTempLossVoltageAContinueTime,ucLossVoltageStartTime,ucTempA))
    {
        
        if(GAL_YES==ucStatus)
        {
            LossVoltageStart(LOSSVOLTAGE_TYPE_A);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED;
        }
        else
        {
            LossVoltageEnd(LOSSVOLTAGE_TYPE_A);
        }
    }
    
    // Phase B
    ucStatus=FLG_B_LOSS_VOLTAGE_STATUS;
    if(1==TranslateStatus0or1(&ucStatus,&ucTempLossVoltageBStatusUse,
        &ucTempLossVoltageBContinueTime,ucLossVoltageStartTime,ucTempB))
    {
        if(GAL_YES==ucStatus)
        {
            LossVoltageStart(LOSSVOLTAGE_TYPE_B);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED;
        }
        else
        {
            LossVoltageEnd(LOSSVOLTAGE_TYPE_B);
        }
    }
    
    // Phase C
    ucStatus=FLG_C_LOSS_VOLTAGE_STATUS;
    if(1==TranslateStatus0or1(&ucStatus,&ucTempLossVoltageCStatusUse,
        &ucTempLossVoltageCContinueTime,ucLossVoltageStartTime,ucTempC))
    {
        if(GAL_YES==ucStatus)
        {
            LossVoltageStart(LOSSVOLTAGE_TYPE_C);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED2;
        }
        else
        {
            LossVoltageEnd(LOSSVOLTAGE_TYPE_C);
        }
    }
    return DLT_RET_SUCC;
    
}


uchar LossVoltageMode(void)
{

    if(isSystemResetUnfinisded)
        return DLT_RET_SUCC;
    
    if(GAL_NO == PROGFUNCTION_LOSS_VOLTAGE )
    {
        FLG_A_LOSS_VOLTAGE_STATUS=0;
        FLG_B_LOSS_VOLTAGE_STATUS=0;
        FLG_C_LOSS_VOLTAGE_STATUS=0;
        return DLT_RET_NO_HAPPEN;
    }
    else
    {
        if(isFlashFree)
        {
            if(PROGFUNCTION_TYPE_METER_TYPE==METERTYPE_3_3)
            {
                return LossVoltageMode_33();
            }
            else
            {
                return LossVoltageMode_34();
            }
        }
        else
        {
            return DLT_RET_UNFINISHED;
        }
    }
}







