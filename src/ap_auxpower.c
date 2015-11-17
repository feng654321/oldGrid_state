#define AP_AUXPOWER_GLOBALS
#include "common.h"
uchar ucAuxPowerMinute;
uchar ucTempAuxPowerStatusUse,ucTempAuxPowerContinueTime;
uchar ucAuxPowerContineTime;


void AuxPowerStart(void);
void AuxPowerEnd(void);


void AuxPowerInit(void)
{
    FLG_ACPOWER_STATUS=GAL_NO;
    fAuxPowerDownStatusClr;
    ucTempAuxPowerStatusUse=GAL_NO;
    ucTempAuxPowerContinueTime=0;
    ucAuxPowerContineTime=0;
}
void AuxPowerPowerOnInit(void)
{
    ucTempAuxPowerStatusUse=GAL_NO;
    ucTempAuxPowerContinueTime=0;
}
void AuxPowerStart(void)
{
    ulong ulDataAddr;
    
    FLG_ACPOWER_STATUS=GAL_YES;
    fAuxPowerDownStatusSet;
    EVENT_CONTINUE_TIME_START_INIT(ucAuxPowerContineTime, CON_AUXPOWER_CONTINUETIME);

    Data3ByteBCDAdd1(RAM_ACPOWER_LOSS_COUNT);
    
    ulDataAddr=SetTwoTableNextPoint(TYPE_ACPOWER_LOSS_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetTimeDataToPoint(&Wr_data[0]);
        memset(&Wr_data[6],0,6);
        WriteDataDirect(&Wr_data[0], ulDataAddr,  12);
    }
    ClrFlashMode();
}

void AuxPowerEnd(void)
{
    ulong ulDataAddr;
    
    FLG_ACPOWER_STATUS=GAL_NO;
    fAuxPowerDownStatusClr;
    AuxPowerMinTimeAdd();
    ulDataAddr=GetTwoTableAddrFromBlock(TYPE_ACPOWER_LOSS_RECORD,0,6);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetTimeDataToPoint(&Wr_data[0]);
        WriteDataDirect(&Wr_data[0], ulDataAddr,  6);
    }

}



#if 0
void AuxPowerStopIfStart(void)
{
#if(CONFIG_METER_AUX_MODE==CONFIG_METER_AUX_MODE_ENABLE)
    //if(GAL_YES==FLG_ACPOWER_STATUS)
    if(GAL_YES == fGetAuxPowerDownStatus)
    {
        AuxPowerEnd();
    }
#else
    FLG_ACPOWER_STATUS=GAL_NO;
    fAuxPowerDownStatusClr;

#endif
}
#endif

void AuxPowerSecTimeAdd(void)
{
    if(GAL_YES == fGetAuxPowerDownStatus)
    {
        ucAuxPowerContineTime++;
    }
}

void AuxPowerMinTimeAdd(void)
{
    if(ucAuxPowerContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_ACPOWER_LOSS_TIME);
        ucAuxPowerContineTime -= 60;
    }
}


void AuxPowerMode(void)
{
#if(CONFIG_METER_AUX_MODE==CONFIG_METER_AUX_MODE_ENABLE)
    uchar ucTemp,ucStatus;
#endif
    if(GAL_YES!=PROGFUNCTION_ACPOWER_LOSS)
    {
        FLG_ACPOWER_STATUS=GAL_NO;
        fAuxPowerDownStatusClr;
        FLG_POWER_STATUS=CON_POWER_STATUS_USE_MAINPOWER;
    }
#if(CONFIG_METER_AUX_MODE==CONFIG_METER_AUX_MODE_ENABLE)
    else
    {
        //if(isFlashFree)
        {
            ucTemp=1;
            if(GetAuxPowerStatus())
            {
                ucTemp=0;
            }
            ucStatus=FLG_ACPOWER_STATUS;
            if(1==TranslateStatus0or1(&ucStatus,&ucTempAuxPowerStatusUse,
                &ucTempAuxPowerContinueTime,CON_AUXPOWER_CONTINUETIME,ucTemp))
            {
                
                if(GAL_YES==ucStatus)
                {
                    AuxPowerStart();
                }
                else
                {
                    AuxPowerEnd();
                }
            }
            //if(FLG_ACPOWER_STATUS)
            //具备辅助电源的电能表，应以辅助电源供电优先；线路和辅助电源两种供电方式应能实现无间断自动转换。
            if(GAL_YES == fGetAuxPowerDownStatus)
            {
                FLG_POWER_STATUS=CON_POWER_STATUS_USE_MAINPOWER;
            }
            else
            {
                FLG_POWER_STATUS=CON_POWER_STATUS_USE_AUXPOWER;
            }
        }
    }
#endif
}

void AuxPowerPowerOn(uchar *ucStartTime,ulong ulTime)
{
#if(CONFIG_METER_AUX_MODE==CONFIG_METER_AUX_MODE_ENABLE)
    ulong ulDataAddr;
    //if(GAL_YES!=FLG_ACPOWER_STATUS)
    if(GAL_YES != fGetAuxPowerDownStatus)
    {
        
        ulDataAddr=SetTwoTableNextPoint(TYPE_ACPOWER_LOSS_RECORD);
        if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
        {
            memcpy(&Wr_data[0], &ucStartTime[0], 6);
            if(1!=TestSecondMinuteHourDayMonthYear(&Wr_data[0], &Wr_data[3]))
            {
                SetTimeDataToPoint(&Wr_data[0]);
                ulTime=0;
            }
            memset(&Wr_data[6],0,6);
            WriteDataDirect(&Wr_data[0], ulDataAddr,  12);
            /*if(0!=ulTime)
            {
                if(1==ReadDataDirect(EPL_ACPOWER_LOSS_TIME, 3, &Wr_data[0]))
                {
                    ulDataAddr=Bcd3DataToLong(&Wr_data[0]);
                    ulDataAddr=ulDataAddr+ulTime;
                    
                    LongToData3BCD(ulDataAddr,&Wr_data[0]);
                    WriteDataDirect(&Wr_data[0], EPL_ACPOWER_LOSS_TIME,  3);
                    ucAuxPowerMinute=RSOFT_RTC_MINUTE;
                }               
            }*/

            FLG_ACPOWER_STATUS=GAL_YES;
            fAuxPowerDownStatusSet;
            Data3ByteBCDAdd1(RAM_ACPOWER_LOSS_COUNT);
        }
        
    }
    if(0!=ulTime)
    {
        if(1==ReadDataDirect(RAM_ACPOWER_LOSS_TIME, 3, &Wr_data[0]))
        {
            ulDataAddr=Bcd3DataToLong(&Wr_data[0]);
            ulDataAddr=ulDataAddr+ulTime;
            
            LongToData3BCD(ulDataAddr,&Wr_data[0]);
            WriteDataDirect(&Wr_data[0], RAM_ACPOWER_LOSS_TIME,  3);
            ucAuxPowerMinute=RSOFT_RTC_MINUTE;
        }               
    }
#else
    FLG_ACPOWER_STATUS=GAL_NO;
    fAuxPowerDownStatusClr;
#endif  
}












































