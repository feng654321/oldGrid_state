#ifndef __AP_DOWNVOLTAGE_C__
#define __AP_DOWNVOLTAGE_C__

#include "common.h"

#define DOWNVOLTAGE_TYPE_A 0
#define DOWNVOLTAGE_TYPE_B 1
#define DOWNVOLTAGE_TYPE_C 2



// uchar ucTempDownVoltageAStatus,ucTempDownVoltageAStatusUse,ucTempDownVoltageAContinueTime;
// uchar ucTempDownVoltageBStatus,ucTempDownVoltageBStatusUse,ucTempDownVoltageBContinueTime;
// uchar ucTempDownVoltageCStatus,ucTempDownVoltageCStatusUse,ucTempDownVoltageCContinueTime;

uchar ucTempDownVoltageAStatusUse,ucTempDownVoltageAContinueTime;
uchar ucTempDownVoltageBStatusUse,ucTempDownVoltageBContinueTime;
uchar ucTempDownVoltageCStatusUse,ucTempDownVoltageCContinueTime;

u16  uiDownVoltageStartV;
uchar ucDownVoltageStartTime;
uchar ucDownVoltageAContineTime,ucDownVoltageBContineTime,ucDownVoltageCContineTime;

void DownVoltageParaInit(void)
{
    ReadCoefDataWithCheck(EPL_COEF_DOWN_VOLTAGE_CONDITION, 3, Ap_temp, 1);
    uiDownVoltageStartV=HexFromRam2Bcd(Ap_temp);
    ucDownVoltageStartTime=HexFromRam1Bcd((Ap_temp+2));
    if(ucDownVoltageStartTime<CONFIG_METER_EVENT_DELAY_MIN_TIME)
        ucDownVoltageStartTime=CONFIG_METER_EVENT_DELAY_MIN_TIME;
}
    

void DownVoltageInit(void)
{
    FLG_A_DOWN_VOLTAGE_STATUS=0;
    FLG_B_DOWN_VOLTAGE_STATUS=0;
    FLG_C_DOWN_VOLTAGE_STATUS=0;
    ucTempDownVoltageAStatusUse=0;
    ucTempDownVoltageAContinueTime=0;
    ucTempDownVoltageBStatusUse=0;
    ucTempDownVoltageBContinueTime=0;
    ucTempDownVoltageCStatusUse=0;
    ucTempDownVoltageCContinueTime=0;
    DownVoltageParaInit();
    ucDownVoltageAContineTime = 0;
    ucDownVoltageBContineTime = 0;
    ucDownVoltageCContineTime = 0;
}

/*void DownVoltageReJudge(void);
void DownVoltageReJudge(void)
{
    DownVoltageSecond = 0xff;
}*/


void DownVoltageStart(uchar ucType)
{
    ulong ulDataAddr;

    if(DOWNVOLTAGE_TYPE_A==ucType)
    {
        FLG_A_DOWN_VOLTAGE_STATUS = GAL_YES;
        EVENT_CONTINUE_TIME_START_INIT(ucDownVoltageAContineTime, ucDownVoltageStartTime);
    }
    else if(DOWNVOLTAGE_TYPE_B==ucType)
    {
        FLG_B_DOWN_VOLTAGE_STATUS = GAL_YES;
        EVENT_CONTINUE_TIME_START_INIT(ucDownVoltageBContineTime, ucDownVoltageStartTime);
    }
    else if(DOWNVOLTAGE_TYPE_C==ucType)
    {
        FLG_C_DOWN_VOLTAGE_STATUS = GAL_YES;
        EVENT_CONTINUE_TIME_START_INIT(ucDownVoltageCContineTime, ucDownVoltageStartTime);
    }
    else
    {
        return ;
    }
    
    FLG_DOWN_VOLTAGE_ALARM = GAL_CLR;
    // Total Count
    //Data3ByteBCDAdd1(EPL_TOTAL_DOWN_V_COUNT_TOTAL);
    // Current Phase
    Data3ByteBCDAdd1(EPL_TOTAL_DOWN_AV_COUNT_TOTAL+4*ucType);
    // Total StartTime
    //SetTimeDataToPoint(&Wr_data[0]);
    //memset(&Wr_data[6],0,6);
    //WriteDataDirect(&Wr_data[0], EPL_TOTAL_DOWN_V_LAST_START,  12);
    
#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Current Phase StartTime Add End Time
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_DOWN_AV_LAST_START+132*ucType,  12);
#endif
    // CLR current ah data
    memset(&RAM[RAM_CURRENT_DOWN_AV_AH_ALL+ucType*20],0x00,20);
    ulDataAddr=SetTwoTableNextPoint(TYPE_DOWN_A_VOLTAGE_RECORD+ucType);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetEventStartDataLossVoltagetoAddr(&Wr_data[0]);
        memset(&Wr_data[125], 0x00, 106);
        
        WriteDataDirect(&Wr_data[0], ulDataAddr,  231);
    }
    ClrFlashMode();
}
void DownVoltageStopIfStart(void)
{
    if(GAL_YES==FLG_A_DOWN_VOLTAGE_STATUS)
    {
        DownVoltageEnd(DOWNVOLTAGE_TYPE_A);
    }
    if(GAL_YES==FLG_B_DOWN_VOLTAGE_STATUS)
    {
        DownVoltageEnd(DOWNVOLTAGE_TYPE_B);
    }
    if(GAL_YES==FLG_C_DOWN_VOLTAGE_STATUS)
    {
        DownVoltageEnd(DOWNVOLTAGE_TYPE_C);
    }
}
void DownVoltageEnd(uchar ucType)
{
    ulong ulDataAddr;
    
    if(DOWNVOLTAGE_TYPE_A==ucType)
    {
        FLG_A_DOWN_VOLTAGE_STATUS = GAL_NO;
    }
    else if(DOWNVOLTAGE_TYPE_B==ucType)
    {
        FLG_B_DOWN_VOLTAGE_STATUS = GAL_NO;
    }
    else if(DOWNVOLTAGE_TYPE_C==ucType)
    {
        FLG_C_DOWN_VOLTAGE_STATUS = GAL_NO;
    }
    else
    {
        return ;
    }
    DownVoltageMinTimeAdd();

    // Total End Time
    //SetTimeDataToPoint(&Wr_data[0]);
    //WriteDataDirect(&Wr_data[0], EPL_TOTAL_DOWN_V_LAST_START+6,  6);

#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Current Phase  End Time
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_DOWN_AV_LAST_START+6+132*ucType,  6);
#endif

    ulDataAddr=GetTwoTableAddrFromBlock(TYPE_DOWN_A_VOLTAGE_RECORD+ucType,0,125);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        memcpy(&Wr_data[0], &RAM[RAM_CURRENT_DOWN_AV_AH_ALL+ucType*20], 20);
        SetEventEndDataLossVoltagetoAddr(&Wr_data[20]);
        WriteDataDirect(&Wr_data[0], ulDataAddr,  86+20);
    }

}

void DownVoltageSecTimeAdd(void)
{
    if(GAL_YES == FLG_A_DOWN_VOLTAGE_STATUS)
    {
        ucDownVoltageAContineTime++;
    }
    if(GAL_YES == FLG_B_DOWN_VOLTAGE_STATUS)
    {
        ucDownVoltageBContineTime++;
    }
    if(GAL_YES == FLG_C_DOWN_VOLTAGE_STATUS)
    {
        ucDownVoltageCContineTime++;
    }
}

void DownVoltageMinTimeAdd(void)
{
    if(ucDownVoltageAContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_DOWN_AV_TIME_TOTAL);
        ucDownVoltageAContineTime -= 60;
    }
    if(ucDownVoltageBContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_DOWN_BV_TIME_TOTAL);
        ucDownVoltageBContineTime -= 60;
    }
    if(ucDownVoltageCContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_DOWN_CV_TIME_TOTAL);
        ucDownVoltageCContineTime -= 60;
    }
}


uchar DownVoltageMode_34(void)
{
    uchar ucTempA,ucTempB,ucTempC,ucStatus;
    
    ucTempA=0;
    ucTempB=0;
    ucTempC=0;
    if(uiDownVoltageStartV>uiNowVoltage[0])
    {
        ucTempA=1;
    }
    if(PROGFUNCTION_TYPE_METER_TYPE != METERTYPE_3_3)
    {
        if(uiDownVoltageStartV>uiNowVoltage[1])
        {
            ucTempB=1;
        }
    }
    if(uiDownVoltageStartV>uiNowVoltage[2])
    {
        ucTempC=1;
    }

    
    //========================================================
    // Phase A
    ucStatus=FLG_A_DOWN_VOLTAGE_STATUS;
    
    if(1==TranslateStatus0or1(&ucStatus,&ucTempDownVoltageAStatusUse,
        &ucTempDownVoltageAContinueTime,ucDownVoltageStartTime,ucTempA))
    {
        
        if(GAL_YES==ucStatus)
        {
            DownVoltageStart(DOWNVOLTAGE_TYPE_A);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED;
        }
        else
        {
            DownVoltageEnd(DOWNVOLTAGE_TYPE_A);
        }
    }
    
    // Phase B
    if(PROGFUNCTION_TYPE_METER_TYPE != METERTYPE_3_3)
    {
        ucStatus=FLG_B_DOWN_VOLTAGE_STATUS;
        if(1==TranslateStatus0or1(&ucStatus,&ucTempDownVoltageBStatusUse,
            &ucTempDownVoltageBContinueTime,ucDownVoltageStartTime,ucTempB))
        {
            if(GAL_YES==ucStatus)
            {
                DownVoltageStart(DOWNVOLTAGE_TYPE_B);
                if(isFlashBusy)
                    return DLT_RET_UNFINISHED;
            }
            else
            {
                DownVoltageEnd(DOWNVOLTAGE_TYPE_B);
            }
        }
    }
    else
    {
        FLG_B_DOWN_VOLTAGE_STATUS=GAL_NO;
    }
    
    // Phase C
    ucStatus=FLG_C_DOWN_VOLTAGE_STATUS;
    if(1==TranslateStatus0or1(&ucStatus,&ucTempDownVoltageCStatusUse,
        &ucTempDownVoltageCContinueTime,ucDownVoltageStartTime,ucTempC))
    {
        if(GAL_YES==ucStatus)
        {
            DownVoltageStart(DOWNVOLTAGE_TYPE_C);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED2;
        }
        else
        {
            DownVoltageEnd(DOWNVOLTAGE_TYPE_C);
        }
    }

    return DLT_RET_SUCC;    
}


uchar DownVoltageMode(void)
{

    if(isSystemResetUnfinisded)
        return DLT_RET_SUCC;
    
    if(GAL_NO == PROGFUNCTION_DOWN_VOLTAGE )
    {
        FLG_A_DOWN_VOLTAGE_STATUS=0;
        FLG_B_DOWN_VOLTAGE_STATUS=0;
        FLG_C_DOWN_VOLTAGE_STATUS=0;
        return DLT_RET_NO_HAPPEN;
    }
    else
    {
        if(isFlashFree)
        {
            return DownVoltageMode_34();
        }
        else
        {
            return DLT_RET_UNFINISHED;
        }
    }
}

#endif
