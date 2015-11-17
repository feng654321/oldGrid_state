#define AP_REVERSEPOWER_GLOBALS
#include "common.h"


#define REVERSEPOWER_TYPE_ALL       0
#define REVERSEPOWER_TYPE_A     1
#define REVERSEPOWER_TYPE_B     2
#define REVERSEPOWER_TYPE_C     3

uchar ucTempReversePowerAllStatusUse,ucTempReversePowerAllContinueTime;
uchar ucTempReversePowerAStatusUse,ucTempReversePowerAContinueTime;
uchar ucTempReversePowerBStatusUse,ucTempReversePowerBContinueTime;
uchar ucTempReversePowerCStatusUse,ucTempReversePowerCContinueTime;

uchar ucReversePowerStartTime;
uchar ucReversePowerAContineTime,ucReversePowerBContineTime,ucReversePowerCContineTime,ucReversePowerTContineTime;

void ReversePowerParaInit(void)
{
    ReadCoefDataWithCheck(EPL_COEF_REVERSEPOWER_CONDITION, 4, Ap_temp, 1);
    memcpy((uchar *)&RAM[RAM_COEF_REVERSEPOWER_KW_START], &Ap_temp[0], 3);
    ucReversePowerStartTime=HexFromRam1Bcd((Ap_temp+3));
    if(ucReversePowerStartTime<CONFIG_METER_EVENT_DELAY_MIN_TIME)
        ucReversePowerStartTime=CONFIG_METER_EVENT_DELAY_MIN_TIME;
}
    
void ReversePowerInit(void)
{
    FLG_ALL_REVERSEKW_STATUS=GAL_NO;
    
    FLG_A_REVERSEKW_STATUS=GAL_NO;
    FLG_B_REVERSEKW_STATUS=GAL_NO;
    FLG_C_REVERSEKW_STATUS=GAL_NO;
    
    ucTempReversePowerAllStatusUse=0;
    ucTempReversePowerAllContinueTime=0;
    
    ucTempReversePowerAStatusUse=0;
    ucTempReversePowerAContinueTime=0;
    
    ucTempReversePowerBStatusUse=0;
    ucTempReversePowerBContinueTime=0;
    
    ucTempReversePowerCStatusUse=0;
    ucTempReversePowerCContinueTime=0;
    ReversePowerParaInit();
    ucReversePowerAContineTime=0;
    ucReversePowerBContineTime=0;
    ucReversePowerCContineTime=0;
    ucReversePowerTContineTime=0;
}

/*void ReversePowerReJudge(void);
void ReversePowerReJudge(void)
{
    ReversePowerSecond=0xff;
}*/

void ReversePowerStart(uchar ucType)
{
    ulong ulDataAddr;

    switch(ucType)
    {
        case REVERSEPOWER_TYPE_ALL:
            FLG_ALL_REVERSEKW_STATUS=GAL_YES;
            EVENT_CONTINUE_TIME_START_INIT(ucReversePowerTContineTime, ucReversePowerStartTime);
            break;
        case REVERSEPOWER_TYPE_A:
            FLG_A_REVERSEKW_STATUS=GAL_YES;
            EVENT_CONTINUE_TIME_START_INIT(ucReversePowerAContineTime, ucReversePowerStartTime);
            break;
        case REVERSEPOWER_TYPE_B:
            FLG_B_REVERSEKW_STATUS=GAL_YES;
            EVENT_CONTINUE_TIME_START_INIT(ucReversePowerBContineTime, ucReversePowerStartTime);
            break;
        case REVERSEPOWER_TYPE_C:
            FLG_C_REVERSEKW_STATUS=GAL_YES;
            EVENT_CONTINUE_TIME_START_INIT(ucReversePowerCContineTime, ucReversePowerStartTime);
            break;
        default: 
            return ;
            //break;
    }

    if(ucType >= REVERSEPOWER_TYPE_A)
        FLG_REVERSEKW_ABC_ALARM = GAL_CLR;

    // Total Count
    Data3ByteBCDAdd1(EPL_TOTAL_REVERSE_ALL_COUNT_TOTAL+ucType*4);
    
#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Total StartTime
    SetTimeDataToPoint(&Wr_data[0]);
    memset(&Wr_data[6],0,6);
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_REVERSE_ALL_LAST_START+112*ucType,  12);
#endif  
    
    ulDataAddr=SetTwoTableNextPoint(TYPE_REVERSEPOWER_ALL_RECORD+ucType);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetEventStartDataLossVoltagetoAddr(&Wr_data[0]);
        memset(&Wr_data[125], 0x00, 86);
        
        WriteDataDirect(&Wr_data[0], ulDataAddr,  211);
    }
    ClrFlashMode();
}

void ReversePowerStopIfStart(void)
{
    if(GAL_YES == FLG_ALL_REVERSEKW_STATUS)
    {
        ReversePowerEnd(REVERSEPOWER_TYPE_ALL);
    }
    if(GAL_YES == FLG_A_REVERSEKW_STATUS)
    {
        ReversePowerEnd(REVERSEPOWER_TYPE_A);
    }
    if(GAL_YES == FLG_B_REVERSEKW_STATUS)
    {
        ReversePowerEnd(REVERSEPOWER_TYPE_B);
    }
    if(GAL_YES == FLG_C_REVERSEKW_STATUS)
    {
        ReversePowerEnd(REVERSEPOWER_TYPE_C);
    }
}



void ReversePowerEnd(uchar ucType)
{
    ulong ulDataAddr;
    
    switch(ucType)
    {
        case REVERSEPOWER_TYPE_ALL:
            FLG_ALL_REVERSEKW_STATUS=GAL_NO;
            break;
        case REVERSEPOWER_TYPE_A:
            FLG_A_REVERSEKW_STATUS=GAL_NO;
            break;
        case REVERSEPOWER_TYPE_B:
            FLG_B_REVERSEKW_STATUS=GAL_NO;
            break;
        case REVERSEPOWER_TYPE_C:
            FLG_C_REVERSEKW_STATUS=GAL_NO;
            break;
        default:
            return;
    }
    ReversePowerMinTimeAdd();
    
#if(GAL_YES==CONFIG_METER_EVENT_LASTTIME_SAVEMODE)
    // Total End Time
    SetTimeDataToPoint(&Wr_data[0]);
    WriteDataDirect(&Wr_data[0], EPL_TOTAL_REVERSE_ALL_LAST_START+ucType*112+6,  6);
#endif  
    
    ulDataAddr=GetTwoTableAddrFromBlock(TYPE_REVERSEPOWER_ALL_RECORD + ucType,0,125);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetEventEndDataLossVoltagetoAddr(&Wr_data[0]);
        WriteDataDirect(&Wr_data[0], ulDataAddr,  86);
    }

}

void ReversePowerSecTimeAdd(void)
{
    if(GAL_YES==FLG_ALL_REVERSEKW_STATUS)
    {
        ucReversePowerTContineTime++;
    }
    if(GAL_YES == FLG_A_REVERSEKW_STATUS)
    {
        ucReversePowerAContineTime++;
    }
    if(GAL_YES == FLG_B_REVERSEKW_STATUS)
    {
        ucReversePowerBContineTime++;
    }
    if(GAL_YES == FLG_C_REVERSEKW_STATUS)
    {
        ucReversePowerCContineTime++;
    }
}

void ReversePowerMinTimeAdd(void)
{
    if(ucReversePowerTContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_REVERSE_ALL_TIME_TOTAL);
        ucReversePowerTContineTime -= 60;
    }
    if(ucReversePowerAContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_REVERSE_A_TIME_TOTAL);
        ucReversePowerAContineTime -= 60;
    }
    if(ucReversePowerBContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_REVERSE_B_TIME_TOTAL);
        ucReversePowerBContineTime -= 60;
    }
    if(ucReversePowerCContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_TOTAL_REVERSE_C_TIME_TOTAL);
        ucReversePowerCContineTime -= 60;
    }
}

uchar ReversePowerMode_34(void)
{
    uchar ucTempAll,ucTempA,ucTempB,ucTempC,ucStatus;
    UN_U32_PARAM unPan,unCurrent;
    

    ucTempAll=0;
    ucTempA=0;
    ucTempB=0;
    ucTempC=0;

    if((status_5460_0&0x10)!=0) // a-
    {
        ucTempA=GAL_YES;
    }   
    if(PROGFUNCTION_TYPE_METER_TYPE != METERTYPE_3_3)
    {
        if((status_5460_0&0x20)!=0)// b-
        {
            ucTempB=GAL_YES;
        }
    }
    
    if((status_5460_0&0x40)!=0)// c-
    {
        ucTempC=GAL_YES;
    }
    
    if((status_5460_0&0x80)!=0)// ALL-
    {
        ucTempAll=1;
    }

    
    memcpy((uchar * )&unPan.cData.ucData0, (uchar *) &RAM[RAM_COEF_REVERSEPOWER_CONDITION-1], 4);
    unPan.cData.ucData0=0x00;
    
    memcpy((uchar * )&unCurrent.cData.ucData0, (uchar *)&RAM[RAM_CURRENT_KW_A], 4);
    unCurrent.cData.ucData3 &=0x7F;
    if(unCurrent.ulData<unPan.ulData)
    {
        ucTempA=GAL_NO;
    }
    memcpy((uchar * )&unCurrent.cData.ucData0, (uchar *)&RAM[RAM_CURRENT_KW_B], 4);
    unCurrent.cData.ucData3 &=0x7F;
    if(unCurrent.ulData<unPan.ulData)
    {
        ucTempB=GAL_NO;
    }
    memcpy((uchar * )&unCurrent.cData.ucData0, (uchar *)&RAM[RAM_CURRENT_KW_C], 4);
    unCurrent.cData.ucData3 &=0x7F;
    if(unCurrent.ulData<unPan.ulData)
    {
        ucTempC=GAL_NO;
    }
    memcpy((uchar * )&unCurrent.cData.ucData0, (uchar *)&RAM[RAM_CURRENT_KW_ALL], 4);
    unCurrent.cData.ucData3 &=0x7F;
    if(unCurrent.ulData<unPan.ulData)
    {
        ucTempAll=GAL_NO;
    }
    
    //========================================================
    // Phase ALL
    ucStatus=FLG_ALL_REVERSEKW_STATUS;
    if(1==TranslateStatus0or1(&ucStatus,&ucTempReversePowerAllStatusUse,
        &ucTempReversePowerAllContinueTime,ucReversePowerStartTime,ucTempAll))
    {
        if(GAL_YES==ucStatus)
        {
            ReversePowerStart(REVERSEPOWER_TYPE_ALL);
            if(isFlashBusy)
                return DLT_RET_UNFINISHED;
        }
        else
        {
            ReversePowerEnd(REVERSEPOWER_TYPE_ALL);
        }
    }
    
    //========================================================
    // Phase A
    ucStatus=FLG_A_REVERSEKW_STATUS;
    if(1==TranslateStatus0or1(&ucStatus,&ucTempReversePowerAStatusUse,
        &ucTempReversePowerAContinueTime,ucReversePowerStartTime,ucTempA))
    {
        if(GAL_YES==ucStatus)
        {
            ReversePowerStart(REVERSEPOWER_TYPE_A);         
            if(isFlashBusy)
                return DLT_RET_UNFINISHED;
        }
        else
        {
            ReversePowerEnd(REVERSEPOWER_TYPE_A);
        }
    }
    
    //========================================================
    // Phase B
    if(PROGFUNCTION_TYPE_METER_TYPE != METERTYPE_3_3)
    {
        ucStatus=FLG_B_REVERSEKW_STATUS;
        if(1==TranslateStatus0or1(&ucStatus,&ucTempReversePowerBStatusUse,
            &ucTempReversePowerBContinueTime,ucReversePowerStartTime,ucTempB))
        {
            if(GAL_YES==ucStatus)
            {
                ReversePowerStart(REVERSEPOWER_TYPE_B);             
                if(isFlashBusy)
                    return DLT_RET_UNFINISHED;
            }
            else
            {
                ReversePowerEnd(REVERSEPOWER_TYPE_B);
            }
        }
    }
    else
    {
        FLG_B_REVERSEKW_STATUS=GAL_NO;
    }
    //========================================================
    // Phase C
    ucStatus=FLG_C_REVERSEKW_STATUS;
    if(1==TranslateStatus0or1(&ucStatus,&ucTempReversePowerCStatusUse,
        &ucTempReversePowerCContinueTime,ucReversePowerStartTime,ucTempC))
    {
        if(GAL_YES==ucStatus)
        {
            ReversePowerStart(REVERSEPOWER_TYPE_C);         
            if(isFlashBusy)
                return DLT_RET_UNFINISHED2;
        }
        else
        {
            ReversePowerEnd(REVERSEPOWER_TYPE_C);
        }
    }
    return DLT_RET_SUCC;
}


uchar ReversePowerMode(void)
{

    if(isSystemResetUnfinisded)
        return DLT_RET_SUCC;
    
    if(GAL_NO== PROGFUNCTION_REVERSEPOWER_ALL )
    {
        FLG_ALL_REVERSEKW_STATUS=0;
        FLG_A_REVERSEKW_STATUS=0;
        FLG_B_REVERSEKW_STATUS=0;
        FLG_C_REVERSEKW_STATUS=0;
        return DLT_RET_NO_HAPPEN;
    }
    else
    {
        if(isFlashFree)
        {
            return ReversePowerMode_34();
        }
        else
        {
            return DLT_RET_UNFINISHED;
        }
    }
}


















































