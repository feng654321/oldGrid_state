#define AP_OVERPOWER_GLOBALS
#include "common.h"


#define POWEROVER_TYPE_ALL  0
#define POWEROVER_TYPE_A        1
#define POWEROVER_TYPE_B        2
#define POWEROVER_TYPE_C        3


uchar OverPowerSecond,OverPowerMinute;
uchar ucTempOverPowerAllStatusUse,ucTempOverPowerAllContinueTime;
uchar ucTempOverPowerAStatusUse,ucTempOverPowerAContinueTime;
uchar ucTempOverPowerBStatusUse,ucTempOverPowerBContinueTime;
uchar ucTempOverPowerCStatusUse,ucTempOverPowerCContinueTime;

uchar ucOverPowerStartTime;
uchar ucOverPowerAContineTime,ucOverPowerBContineTime,ucOverPowerCContineTime,ucOverPowerTContineTime;

void OverPowerParaInit(void)
{
    ReadCoefDataWithCheck(EPL_COEF_OVER_KW_CONDITION, 4, Ap_temp, 1);
    memcpy((uchar *)&RAM[RAM_COEF_OVER_KW_KW_START], &Ap_temp[0], 3);
    ucOverPowerStartTime=HexFromRam1Bcd((Ap_temp+3));
    if(ucOverPowerStartTime<CONFIG_METER_EVENT_DELAY_MIN_TIME)
        ucOverPowerStartTime=CONFIG_METER_EVENT_DELAY_MIN_TIME;
}

void OverPowerInit(void)
{
    FLG_ALL_OVER_KW_STATUS=GAL_NO;
    
    FLG_A_OVER_KW_STATUS=GAL_NO;
    FLG_B_OVER_KW_STATUS=GAL_NO;
    FLG_C_OVER_KW_STATUS=GAL_NO;
    
    ucTempOverPowerAllStatusUse=0;
    ucTempOverPowerAllContinueTime=0;
    
    ucTempOverPowerAStatusUse=0;
    ucTempOverPowerAContinueTime=0;
    
    ucTempOverPowerBStatusUse=0;
    ucTempOverPowerBContinueTime=0;
    
    ucTempOverPowerCStatusUse=0;
    ucTempOverPowerCContinueTime=0;
    
}

/*void OverPowerReJudge(void);
void OverPowerReJudge(void)
{
    OverPowerSecond = 0xff;
}*/


void OverPowerStart(uchar ucType)
{
    ulong ulDataAddr;

    switch(ucType)
    {
        case POWEROVER_TYPE_ALL:
            FLG_ALL_OVER_KW_STATUS=GAL_YES;
            EVENT_CONTINUE_TIME_START_INIT(ucOverPowerTContineTime, ucOverPowerStartTime);
            break;
        case POWEROVER_TYPE_A:
            FLG_A_OVER_KW_STATUS=GAL_YES;
            EVENT_CONTINUE_TIME_START_INIT(ucOverPowerAContineTime, ucOverPowerStartTime);
            break;
        case POWEROVER_TYPE_B:
            FLG_B_OVER_KW_STATUS=GAL_YES;
            EVENT_CONTINUE_TIME_START_INIT(ucOverPowerBContineTime, ucOverPowerStartTime);
            break;
        case POWEROVER_TYPE_C:
            FLG_C_OVER_KW_STATUS=GAL_YES;
            EVENT_CONTINUE_TIME_START_INIT(ucOverPowerCContineTime, ucOverPowerStartTime);
            break;
        default:
            return;
    }
    if(ucType >= POWEROVER_TYPE_A)
        FLG_OVERKW_ABC_ALARM = GAL_CLR;

    // Total Count
    Data3ByteBCDAdd1(EPL_TOTAL_POWEROVER_ALL_COUNT_TOTAL+ucType*4);

#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Total StartTime
    SetTimeDataToPoint(&Wr_data[0]);
    memset(&Wr_data[6],0,6);
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_POWEROVER_ALL_LAST_START+112*ucType,  12);
#endif  
    
    ulDataAddr=SetTwoTableNextPoint(TYPE_POWEROVER_ALL_RECORD+ucType);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetEventStartDataLossVoltagetoAddr(&Wr_data[0]);
        memset(&Wr_data[125], 0x00, 86);
        
        WriteDataDirect(&Wr_data[0], ulDataAddr,  211);
    }
    ClrFlashMode();
}


void OverPowerStopIfStart(void)
{
    if(GAL_YES == FLG_ALL_OVER_KW_STATUS)
    {
        OverPowerEnd(POWEROVER_TYPE_ALL);
    }
    if(GAL_YES == FLG_A_OVER_KW_STATUS)
    {
        OverPowerEnd(POWEROVER_TYPE_A);
    }
    if(GAL_YES == FLG_B_OVER_KW_STATUS)
    {
        OverPowerEnd(POWEROVER_TYPE_B);
    }
    if(GAL_YES == FLG_C_OVER_KW_STATUS)
    {
        OverPowerEnd(POWEROVER_TYPE_C);
    }
}



void OverPowerEnd(uchar ucType)
{
    ulong ulDataAddr;
    
    if(ucType>POWEROVER_TYPE_C)
        return ;
    switch(ucType)
    {
        case POWEROVER_TYPE_ALL:
            FLG_ALL_OVER_KW_STATUS=GAL_NO;
            break;
        case POWEROVER_TYPE_A:
            FLG_A_OVER_KW_STATUS=GAL_NO;
            break;
        case POWEROVER_TYPE_B:
            FLG_B_OVER_KW_STATUS=GAL_NO;
            break;
        case POWEROVER_TYPE_C:
            FLG_C_OVER_KW_STATUS=GAL_NO;
            break;
        default:
            return;
    }
    OverPowerMinTimeAdd();
    
#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Total End Time
    SetTimeDataToPoint(&Wr_data[0]);
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_POWEROVER_ALL_LAST_START+ucType*112+6,  6);
#endif  
    
    ulDataAddr=GetTwoTableAddrFromBlock(TYPE_POWEROVER_ALL_RECORD + ucType,0,125);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetEventEndDataLossVoltagetoAddr(&Wr_data[0]);
        WriteDataDirect(&Wr_data[0], ulDataAddr,  86);
    }

}

void OverPowerSecTimeAdd(void)
{
    if(GAL_YES==FLG_ALL_OVER_KW_STATUS)
    {
        ucOverPowerTContineTime++;
    }
    if(GAL_YES == FLG_A_OVER_KW_STATUS)
    {
        ucOverPowerAContineTime++;
    }
    if(GAL_YES == FLG_B_OVER_KW_STATUS)
    {
        ucOverPowerBContineTime++;
    }
    if(GAL_YES == FLG_C_OVER_KW_STATUS)
    {
        ucOverPowerCContineTime++;
    }
}

void OverPowerMinTimeAdd(void)
{
    if(ucOverPowerTContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_POWEROVER_ALL_TIME_TOTAL);
        ucOverPowerTContineTime -= 60;
    }
    if(ucOverPowerAContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_POWEROVER_A_TIME_TOTAL);
        ucOverPowerAContineTime -= 60;
    }
    if(ucOverPowerBContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_POWEROVER_B_TIME_TOTAL);
        ucOverPowerBContineTime -= 60;
    }
    if(ucOverPowerCContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_POWEROVER_C_TIME_TOTAL);
        ucOverPowerCContineTime -= 60;
    }
}

uchar OverPowerMode_34(void)
{
    uchar ucTempAll,ucTempA,ucTempB,ucTempC,ucStatus;
    UN_U32_PARAM unPan,unCurrent;
    
    ucTempAll=0;
    ucTempA=0;
    ucTempB=0;
    ucTempC=0;

    
    memcpy((uchar * )&unPan.cData.ucData0, (uchar *) &RAM[RAM_COEF_OVER_KW_KW_START-1], 4);
    unPan.cData.ucData0=0x00;
#if (CONFIG_METER_AREA_MODE_SHANDONG == CONFIG_METER_AREA_MODE)    
    memcpy((uchar * )&unCurrent.cData.ucData0, (uchar *)&RAM[RAM_CURRENT_KVA_A], 4);
#else
    memcpy((uchar * )&unCurrent.cData.ucData0, (uchar *)&RAM[RAM_CURRENT_KW_A], 4);
#endif
    unCurrent.cData.ucData3 &=0x7F;
    if(unCurrent.ulData>unPan.ulData)
    {
        ucTempA=GAL_YES;
    }
    
    if(METERTYPE_3_3!=PROGFUNCTION_TYPE_METER_TYPE  )
    {
#if (CONFIG_METER_AREA_MODE_SHANDONG == CONFIG_METER_AREA_MODE)    
        memcpy((uchar * )&unCurrent.cData.ucData0, (uchar *)&RAM[RAM_CURRENT_KVA_B], 4);
#else
        memcpy((uchar * )&unCurrent.cData.ucData0, (uchar *)&RAM[RAM_CURRENT_KW_B], 4);
#endif
        unCurrent.cData.ucData3 &=0x7F;
        if(unCurrent.ulData>unPan.ulData)
        {
            ucTempB=GAL_YES;
        }
    }
    
#if (CONFIG_METER_AREA_MODE_SHANDONG == CONFIG_METER_AREA_MODE)    
    memcpy((uchar * )&unCurrent.cData.ucData0, (uchar *)&RAM[RAM_CURRENT_KVA_C], 4);
#else
    memcpy((uchar * )&unCurrent.cData.ucData0, (uchar *)&RAM[RAM_CURRENT_KW_C], 4);
#endif
    unCurrent.cData.ucData3 &=0x7F;
    if(unCurrent.ulData>unPan.ulData)
    {
        ucTempC=GAL_YES;
    }
    
    
//  if((status_5460_0&0x80)!=0)// ALL-
//  {
//      ucTempAll=1;
//  }

    //========================================================
    // Phase ALL
    ucStatus=FLG_ALL_OVER_KW_STATUS;
    if(1==TranslateStatus0or1(&ucStatus,&ucTempOverPowerAllStatusUse,
        &ucTempOverPowerAllContinueTime,ucOverPowerStartTime,ucTempAll))
    {
        if(GAL_YES==ucStatus)
        {
            OverPowerStart(POWEROVER_TYPE_ALL);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED;
        }
        else
        {
            OverPowerEnd(POWEROVER_TYPE_ALL);
        }
    }
    
    //========================================================
    // Phase A
    ucStatus=FLG_A_OVER_KW_STATUS;
    if(1==TranslateStatus0or1(&ucStatus,&ucTempOverPowerAStatusUse,
        &ucTempOverPowerAContinueTime,ucOverPowerStartTime,ucTempA))
    {
        if(GAL_YES==ucStatus)
        {
            OverPowerStart(POWEROVER_TYPE_A);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED;
        }
        else
        {
            OverPowerEnd(POWEROVER_TYPE_A);
        }
    }
    
    //========================================================
    // Phase B
    if(PROGFUNCTION_TYPE_METER_TYPE!=METERTYPE_3_3)
    {
        ucStatus=FLG_B_OVER_KW_STATUS;
        if(1==TranslateStatus0or1(&ucStatus,&ucTempOverPowerBStatusUse,
            &ucTempOverPowerBContinueTime,ucOverPowerStartTime,ucTempB))
        {
            if(GAL_YES==ucStatus)
            {
                OverPowerStart(POWEROVER_TYPE_B);
                if(isFlashBusy)
                    return DLT_RET_UNFINISHED;
            }
            else
            {
                OverPowerEnd(POWEROVER_TYPE_B);
            }
        }
    }
    else
    {

        FLG_B_OVER_KW_STATUS=GAL_NO;
    }
    //========================================================
    // Phase C
    ucStatus=FLG_C_OVER_KW_STATUS;
    if(1==TranslateStatus0or1(&ucStatus,&ucTempOverPowerCStatusUse,
        &ucTempOverPowerCContinueTime,ucOverPowerStartTime,ucTempC))
    {
        if(GAL_YES==ucStatus)
        {
            OverPowerStart(POWEROVER_TYPE_C);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED2;
        }
        else
        {
            OverPowerEnd(POWEROVER_TYPE_C);
        }
    }
    return DLT_RET_SUCC;

}


uchar OverPowerMode(void)
{

    if(isSystemResetUnfinisded)
        return DLT_RET_SUCC;
    
    if(GAL_NO== PROGFUNCTION_POWEROVER_ALL)
    {
        FLG_A_OVER_KW_STATUS=GAL_NO;
        FLG_B_OVER_KW_STATUS=GAL_NO;
        FLG_C_OVER_KW_STATUS=GAL_NO;
        FLG_ALL_OVER_KW_STATUS=GAL_NO;
        return DLT_RET_NO_HAPPEN;
    }
    else
    {
        if(isFlashFree)
        {
            return OverPowerMode_34();
        }
        else
        {
            return DLT_RET_UNFINISHED;
        }
    }
}


















































