#define AP_OVERVOLTAGE_GLOBALS
#include "common.h"




#define OVERVOLTAGE_TYPE_A 0
#define OVERVOLTAGE_TYPE_B 1
#define OVERVOLTAGE_TYPE_C 2

// uchar ucTempOverVoltageAStatus,ucTempOverVoltageAStatusUse,ucTempOverVoltageAContinueTime;
// uchar ucTempOverVoltageBStatus,ucTempOverVoltageBStatusUse,ucTempOverVoltageBContinueTime;
// uchar ucTempOverVoltageCStatus,ucTempOverVoltageCStatusUse,ucTempOverVoltageCContinueTime;

uchar ucTempOverVoltageAStatusUse,ucTempOverVoltageAContinueTime;
uchar ucTempOverVoltageBStatusUse,ucTempOverVoltageBContinueTime;
uchar ucTempOverVoltageCStatusUse,ucTempOverVoltageCContinueTime;

u16  uiOverVoltageStartV;
uchar ucOverVoltageStartTime;
uchar ucOverVoltageAContineTime,ucOverVoltageBContineTime,ucOverVoltageCContineTime;

void OverVoltageParaInit(void)
{
    ReadCoefDataWithCheck(EPL_COEF_OVER_VOLTAGE_CONDITION, 3, Ap_temp, 1);
    uiOverVoltageStartV=HexFromRam2Bcd(Ap_temp);
    ucOverVoltageStartTime=HexFromRam1Bcd((Ap_temp+2));
    if(ucOverVoltageStartTime<CONFIG_METER_EVENT_DELAY_MIN_TIME)
        ucOverVoltageStartTime=CONFIG_METER_EVENT_DELAY_MIN_TIME;
}

void OverVoltageInit(void)
{
    FLG_A_OVER_VOLTAGE_STATUS=0;
    FLG_B_OVER_VOLTAGE_STATUS=0;
    FLG_C_OVER_VOLTAGE_STATUS=0;
    ucTempOverVoltageAStatusUse=0;
    ucTempOverVoltageAContinueTime=0;
    ucTempOverVoltageBStatusUse=0;
    ucTempOverVoltageBContinueTime=0;
    ucTempOverVoltageCStatusUse=0;
    ucTempOverVoltageCContinueTime=0;
    OverVoltageParaInit();
    ucOverVoltageAContineTime = 0;
    ucOverVoltageBContineTime = 0;
    ucOverVoltageCContineTime = 0;
}


/*void OverVoltageJudge(void);
void OverVoltageJudge(void)
{
    OverVoltageSecond = 0xff;
}*/


void OverVoltageStart(uchar ucType)
{
    ulong ulDataAddr;
    
    if(OVERVOLTAGE_TYPE_A==ucType)
    {
        FLG_A_OVER_VOLTAGE_STATUS = GAL_YES;
        EVENT_CONTINUE_TIME_START_INIT(ucOverVoltageAContineTime, ucOverVoltageStartTime);
    }
    else if(OVERVOLTAGE_TYPE_B==ucType)
    {
        FLG_B_OVER_VOLTAGE_STATUS = GAL_YES;
        EVENT_CONTINUE_TIME_START_INIT(ucOverVoltageBContineTime, ucOverVoltageStartTime);
    }
    else if(OVERVOLTAGE_TYPE_C==ucType)
    {
        FLG_C_OVER_VOLTAGE_STATUS = GAL_YES;
        EVENT_CONTINUE_TIME_START_INIT(ucOverVoltageCContineTime, ucOverVoltageStartTime);
    }
    else
    {
        return ;
    }
    
    FLG_OVER_VOLTAGE_ALARM = GAL_CLR;
    // Total Count
    //Data3ByteBCDAdd1(EPL_TOTAL_OVER_V_COUNT_TOTAL);
    // Current Phase
    Data3ByteBCDAdd1(EPL_TOTAL_OVER_AV_COUNT_TOTAL+4*ucType);
    // Total StartTime
    //SetTimeDataToPoint(&Wr_data[0]);
    //memset(&Wr_data[6],0,6);
    //WriteDataDirect(&Wr_data[0], EPL_TOTAL_OVER_V_LAST_START,  12);
    
#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Current Phase StartTime Add End Time
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_OVER_AV_LAST_START+132*ucType,  12);
#endif
    // CLR current ah data
    memset(&RAM[RAM_CURRENT_OVER_AV_AH_ALL+ucType*20],0x00,20);

    ulDataAddr=SetTwoTableNextPoint(TYPE_OVER_A_VOLTAGE_RECORD+ucType);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetEventStartDataLossVoltagetoAddr(&Wr_data[0]);
        memset(&Wr_data[125], 0x00, 106);
        
        WriteDataDirect(&Wr_data[0], ulDataAddr,  231);
    }
    ClrFlashMode();
}


void OverVoltageStopIfStart(void)
{
    if(GAL_YES == FLG_A_OVER_VOLTAGE_STATUS)
    {
        OverVoltageEnd(OVERVOLTAGE_TYPE_A);
    }
    if(GAL_YES == FLG_B_OVER_VOLTAGE_STATUS)
    {
        OverVoltageEnd(OVERVOLTAGE_TYPE_B);
    }
    if(GAL_YES == FLG_C_OVER_VOLTAGE_STATUS)
    {
        OverVoltageEnd(OVERVOLTAGE_TYPE_C);
    }
}

void OverVoltageEnd(uchar ucType)
{
    ulong ulDataAddr;
    
    if(OVERVOLTAGE_TYPE_A==ucType)
    {
        FLG_A_OVER_VOLTAGE_STATUS = GAL_NO;
    }
    else if(OVERVOLTAGE_TYPE_B==ucType)
    {
        FLG_B_OVER_VOLTAGE_STATUS = GAL_NO;
    }
    else if(OVERVOLTAGE_TYPE_C==ucType)
    {
        FLG_C_OVER_VOLTAGE_STATUS = GAL_NO;
    }
    else
    {
        return ;
    }
    OverVoltageMinTimeAdd();
    
    // Total End Time
    //SetTimeDataToPoint(&Wr_data[0]);
    //WriteDataDirect(&Wr_data[0], EPL_TOTAL_OVER_V_LAST_START+6,  6);
    
#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Current Phase  End Time
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_OVER_AV_LAST_START+6+132*ucType,  6);
#endif

    ulDataAddr=GetTwoTableAddrFromBlock(TYPE_OVER_A_VOLTAGE_RECORD+ucType,0,125);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        memcpy(&Wr_data[0], &RAM[RAM_CURRENT_OVER_AV_AH_ALL+ucType*20], 20);
        SetEventEndDataLossVoltagetoAddr(&Wr_data[20]);
        WriteDataDirect(&Wr_data[0], ulDataAddr,  86+20);
    }
    
}

void OverVoltageSecTimeAdd(void)
{
    if(GAL_YES == FLG_A_OVER_VOLTAGE_STATUS)
    {
        ucOverVoltageAContineTime++;
    }
    if(GAL_YES == FLG_B_OVER_VOLTAGE_STATUS)
    {
        ucOverVoltageBContineTime++;
    }
    if(GAL_YES == FLG_C_OVER_VOLTAGE_STATUS)
    {
        ucOverVoltageCContineTime++;
    }
}

void OverVoltageMinTimeAdd(void)
{
    if(ucOverVoltageAContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_OVER_AV_TIME_TOTAL);
        ucOverVoltageAContineTime -= 60;
    }
    if(ucOverVoltageBContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_OVER_BV_TIME_TOTAL);
        ucOverVoltageBContineTime -= 60;
    }
    if(ucOverVoltageCContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_OVER_CV_TIME_TOTAL);
        ucOverVoltageCContineTime -= 60;
    }
}


uchar OverVoltageMode_34(void)
{
    uchar ucTempA,ucTempB,ucTempC,ucStatus;

    ucTempA=0;
    ucTempB=0;
    ucTempC=0;
    if(uiOverVoltageStartV<uiNowVoltage[0])
    {
        ucTempA=1;
    }
    if(PROGFUNCTION_TYPE_METER_TYPE != METERTYPE_3_3)
    {
        if(uiOverVoltageStartV<uiNowVoltage[1])
        {
            ucTempB=1;
        }
    }
    if(uiOverVoltageStartV<uiNowVoltage[2])
    {
        ucTempC=1;
    }

    //========================================================
    // Phase A
    ucStatus=FLG_A_OVER_VOLTAGE_STATUS;
    
    if(1==TranslateStatus0or1(&ucStatus,&ucTempOverVoltageAStatusUse,
        &ucTempOverVoltageAContinueTime,ucOverVoltageStartTime,ucTempA))
    {
        
        if(GAL_YES==ucStatus)
        {
            OverVoltageStart(OVERVOLTAGE_TYPE_A);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED;
        }
        else
        {
            OverVoltageEnd(OVERVOLTAGE_TYPE_A);
        }
    }
    
    // Phase B
    if(METERTYPE_3_3!=PROGFUNCTION_TYPE_METER_TYPE  )
    {
        ucStatus=FLG_B_OVER_VOLTAGE_STATUS;
        if(1==TranslateStatus0or1(&ucStatus,&ucTempOverVoltageBStatusUse,
            &ucTempOverVoltageBContinueTime,ucOverVoltageStartTime,ucTempB))
        {
            if(GAL_YES==ucStatus)
            {
                OverVoltageStart(OVERVOLTAGE_TYPE_B);
                if(isFlashBusy)
                    return DLT_RET_UNFINISHED;
            }
            else
            {
                OverVoltageEnd(OVERVOLTAGE_TYPE_B);
            }
        }
    }
    else
    {
        FLG_B_OVER_VOLTAGE_STATUS=GAL_NO;
    }
    // Phase C
    ucStatus=FLG_C_OVER_VOLTAGE_STATUS;
    if(1==TranslateStatus0or1(&ucStatus,&ucTempOverVoltageCStatusUse,
        &ucTempOverVoltageCContinueTime,ucOverVoltageStartTime,ucTempC))
    {
        if(GAL_YES==ucStatus)
        {
            OverVoltageStart(OVERVOLTAGE_TYPE_C);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED2;
        }
        else
        {
            OverVoltageEnd(OVERVOLTAGE_TYPE_C);
        }
    }
    return DLT_RET_SUCC;
}


uchar OverVoltageMode(void)
{

    if(isSystemResetUnfinisded)
        return DLT_RET_SUCC;
    
    if(GAL_NO == PROGFUNCTION_OVER_VOLTAGE )
    {
        FLG_A_OVER_VOLTAGE_STATUS=0;
        FLG_B_OVER_VOLTAGE_STATUS=0;
        FLG_C_OVER_VOLTAGE_STATUS=0;
        return DLT_RET_NO_HAPPEN;
    }
    else
    {
        if(isFlashFree)
        {
            return OverVoltageMode_34();
        }
        else
        {
            return DLT_RET_UNFINISHED;
        }
    }
}











