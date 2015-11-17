#define AP_ALLLOSSVOLTAGE_GLOBALS
#include "common.h"



#define ALLLOSSVOLTAGE_TYPE_A 0
#define ALLLOSSVOLTAGE_TYPE_B 1
#define ALLLOSSVOLTAGE_TYPE_C 2 



uchar AllLossVoltageMinute;
uchar ucTempAllLossVoltageStatusUse,ucTempAllLossVoltageContinueTime;
uchar ucAllLossVoltageContineTime;

void AllLossVoltageInit(void)
{
    FLG_ALL_LOSSVOLTAGE_STATUS=GAL_NO;
    fAllLostVoltageStatusClr;
    ucTempAllLossVoltageContinueTime=0;
    ucAllLossVoltageContineTime = 0;
    ucTempAllLossVoltageStatusUse=GAL_NO;
    Wr_data[0]=0x00;
    WriteDataDirect(&Wr_data[0], EPL_POWERDOWN_ALLLOSSVOLTAGE_STATUS, 1);
}

void AllLossVoltagePowerOnInit(void)
{
    ucTempAllLossVoltageContinueTime=0;
    ucTempAllLossVoltageStatusUse=GAL_NO;
}

void AllLossVoltageStopIfStart(void)
{
    //if(GAL_YES == FLG_ALL_LOSSVOLTAGE_STATUS)
    if(fGetAllLostVoltageStatus)
    {
        AllLossVoltageEnd();
    }
}

void PowerDownAllLossVoltageStopIfStart(void)
{
    if(POWERDOWN_ALLLOSSVOLTAGE_STATUS_YES == ucPowerDownAllLossVoltageStatus )
    {
        PowerDownAllLossVoltageEnd();
        ucPowerDownAllLossVoltageStatus=POWERDOWN_ALLLOSSVOLTAGE_STATUS_NO;
    }
}


#if (CONFIG_METER_AREA_MODE_SOUTHGRID==CONFIG_METER_AREA_MODE)

#else       //   国网规约的全失压记录

// 上电时计算掉电全失压的累计时间
void AllLossVoltagePoweronChange(ulong ulTime)
{
    ulong ulData;
    uchar ucBuffer[3];
    
    if(1==ReadDataDirect(RAM_ALLLOSS_VOLTAGE_TIME, 3, &ucBuffer[0]))
    {
        ulData=Bcd3DataToLong(&ucBuffer[0]);
        ulData=ulData+ulTime;
        
        LongToData3BCD(ulData,&ucBuffer[0]);
        WriteDataDirect(&ucBuffer[0], RAM_ALLLOSS_VOLTAGE_TIME,  3);
        AllLossVoltageMinute=RSOFT_RTC_MINUTE;
    }
}


void AllLossVoltageEnd(void)
{
    ulong ulDataAddr;
    
    FLG_ALL_LOSSVOLTAGE_STATUS = GAL_NO;
    fAllLostVoltageStatusClr;
    AllLossVoltageMinTimeAdd();    
    ulDataAddr=GetTwoTableAddrFromBlock(TYPE_LOSS_ALL_VOLTAGE_RECORD,0,9);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetTimeDataToPoint(&Wr_data[0]);
        WriteDataDirect(&Wr_data[0], ulDataAddr,  6);
    }
}

void AllLossVoltageStart(ulong ulMaxCurrent)
{
    ulong ulDataAddr;
    
    FLG_ALL_LOSSVOLTAGE_STATUS = GAL_YES;
    fAllLostVoltageStatusSet;
    ulMaxCurrent=ulMaxCurrent/10;
    EVENT_CONTINUE_TIME_START_INIT(ucAllLossVoltageContineTime, 60);
    
    // Total Count
    Data3ByteBCDAdd1(RAM_ALLLOSS_VOLTAGE_COUNT);

    ulDataAddr=SetTwoTableNextPoint(TYPE_LOSS_ALL_VOLTAGE_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetTimeDataToPoint(&Wr_data[0]);
        LongToData3BCD(ulMaxCurrent, &Wr_data[6]);
        memset(&Wr_data[9],0,6);
        WriteDataDirect(&Wr_data[0], ulDataAddr, 15);
    }
}


void PowerDownAllLossVoltageEnd(void)
{
    ulong ulDataAddr;
    
    FLG_ALL_LOSSVOLTAGE_STATUS = GAL_NO;
    fAllLostVoltageStatusClr;
        
    ulDataAddr=GetTwoTableAddrFromBlock(TYPE_LOSS_ALL_VOLTAGE_RECORD,0,9);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        GetLastSaveTime((STR_CALENDAR* ) &Wr_data[0]);
        if(1!=TestSecondMinuteHourDayMonthYear(&Wr_data[0], &Wr_data[3]))
        {
            SetTimeDataToPoint(&Wr_data[0]);
        }
        WriteDataDirect(&Wr_data[0], ulDataAddr,  6);
    }
}

void PowerDownAllLossVoltageStart(ulong ulMaxCurrent)
{
    ulong ulDataAddr;
    
    FLG_ALL_LOSSVOLTAGE_STATUS = GAL_YES;
    fAllLostVoltageStatusSet;
    ulMaxCurrent=ulMaxCurrent/10;
    
    // Total Count
    Data3ByteBCDAdd1(EPL_ALLLOSS_VOLTAGE_COUNT);

    ulDataAddr=SetTwoTableNextPoint(TYPE_LOSS_ALL_VOLTAGE_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        GetLastSaveTime((STR_CALENDAR* ) &Wr_data[0]);
        if(1!=TestSecondMinuteHourDayMonthYear(&Wr_data[0], &Wr_data[3]))
        {
            SetTimeDataToPoint(&Wr_data[0]);
        }
        LongToData3BCD(ulMaxCurrent, &Wr_data[6]);
        memset(&Wr_data[9],0,6);
        WriteDataDirect(&Wr_data[0], ulDataAddr, 15);
    }
#if(CONFIG_METER_AUX_MODE_ENABLE == CONFIG_METER_AUX_MODE)
//--AA 在判断出全失压之后，结束掉现有的停电记录---->Start--AA--
    //if(GAL_YES==FLG_SYSTEMPOWER_STATUS)
    if(GAL_YES == fGetPowerDownStatus)
    {
        ulDataAddr=GetTwoTableAddrFromBlock(TYPE_POWER_DOWN_RECORD,0,6);
        if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
        {
            // aa时间之前就已经放在缓冲区里面了aa
            WriteDataDirect(&Wr_data[0], ulDataAddr,  6);
        }   
        FLG_SYSTEMPOWER_STATUS=GAL_NO;
        fPowerDownStatusClr;
    }
//--AA 在判断出全失压之后，结束掉现有的停电记录---->End--AA--
#endif

}


// 全失压判断条件:
// 三相电压全部低于临界电压(60%Un)
// 任一相电流大于5%基本电流
void PowerDownAllLossVoltageMode(void)
{
    u16 uiVoltage;
    ulong ulCurrent;
    uchar ucTemp;
    uchar ucTempStatus;
    UN_U32_PARAM unTempData;
    ulong ulMaxCurrent;

    uiVoltage=ulTypeUn*6/10;
    ulCurrent=ulTypeIb*50;
    ucTempStatus=GAL_YES;
    ulMaxCurrent=0;
    for(ucTemp=0;ucTemp<3;ucTemp++)
    {
        if(1==ReadADReg(TB_ADE7878_VOLTAGE_RMS[ucTemp],4, &Wr_data[0]))
        {
            unTempData.cData.ucData0=Wr_data[3];
            unTempData.cData.ucData1=Wr_data[2];
            unTempData.cData.ucData2=Wr_data[1];
            unTempData.cData.ucData3=Wr_data[0];;
            unTempData.ulData=(unTempData.ulData/2)/uiClacMeterVoltageCoef;
            if(unTempData.ulData>5000)
            {
                unTempData.ulData=0;
            }
            if(unTempData.ulData>uiVoltage)
            {
                ucTempStatus=GAL_NO;
            }       
        }
    }
    if(GAL_YES==ucTempStatus)
    {
#if 0
        for(ucTemp=0;ucTemp<3;ucTemp++)
        {
            Wr_data[0]=0;
            Wr_data[1]=0;
            if(GAL_YES==ReadADRegResumeData(ADREG_VIRTUAL_ACURRENT+ucTemp,2,&Wr_data[0]))
            {
                uiTempCoef[ucTemp]=Wr_data[0]*256+Wr_data[1];  
            }
            if(uiTempCoef[ucTemp]==0) 
            {
                uiTempCoef[ucTemp]=21900;
            }
        }
#endif
        ulMaxCurrent=0;
        ucTempStatus=GAL_NO;
        for(ucTemp=0;ucTemp<3;ucTemp++)
        {
            if(1==ReadADReg(TB_ADE7878_CURRENT_RMS[ucTemp],4, &Wr_data[0]))
            {
                unTempData.cData.ucData0=Wr_data[3];
                unTempData.cData.ucData1=Wr_data[2];
                unTempData.cData.ucData2=Wr_data[1];
                unTempData.cData.ucData3=Wr_data[0];

                if(unTempData.ulData>=0x7f0000)
                {
                    unTempData.ulData=0;
                }

                if(CURRENT_TYPE_BIG == CURRENT_TYPE)
                {
                    unTempData.ulData=(500*(unTempData.ulData/uiCoefCurrentGAIN[ucTemp]))+((500*(unTempData.ulData%uiCoefCurrentGAIN[ucTemp]))/uiCoefCurrentGAIN[ucTemp]);
                }
                else
                {
                    unTempData.ulData=(50*(unTempData.ulData/uiCoefCurrentGAIN[ucTemp]))+((50*(unTempData.ulData%uiCoefCurrentGAIN[ucTemp]))/uiCoefCurrentGAIN[ucTemp]);
                }
                if(unTempData.ulData<uiMeter0d001PerCurrent)    /// 电流小于启动电流
                {
                    unTempData.ulData=0;
                }
                if(unTempData.ulData>3000000)
                {
                    unTempData.ulData=0;
                }

                if((METERTYPE_3_3==PROGFUNCTION_TYPE_METER_TYPE)&&(1==ucTemp))
                {
                    unTempData.ulData=0;
                }

                if(unTempData.ulData>ulCurrent)
                {
                    ucTempStatus=GAL_YES;
                }
                ulMaxCurrent=ulMaxCurrent+unTempData.ulData;
            }
        }
    }
    if(GAL_YES==ucTempStatus)
    {   
        if(METERTYPE_3_3==PROGFUNCTION_TYPE_METER_TYPE)
        {
            ulMaxCurrent=ulMaxCurrent/2;
        }
        else
        {
            ulMaxCurrent=ulMaxCurrent/3;
        }
        if(GAL_YES==AllLossVoltageStatuscheck())
        {
            // aa--如果原先处于全失压状态，则无操作--aa
        }
        else
        {
            PowerDownAllLossVoltageStart(ulMaxCurrent);
        }

    }
    else
    {
        if(GAL_YES==AllLossVoltageStatuscheck())
        {
            PowerDownAllLossVoltageEnd();
        }
        else
        {
            //AA --如果原先不处于全失压状态，则不操作--AA
        }
    }
}
#endif

uchar  GetLastSaveTimeToAddr(uchar * upData)
{
    uchar ucTempBuffer[7];
    
    if(1==ReadDataDirect(EPL_SOFT_TIME, 7, &ucTempBuffer[0]))
    {
        upData[0]=ucTempBuffer[0];
        upData[1]=ucTempBuffer[1];
        upData[2]=ucTempBuffer[2];
        upData[3]=ucTempBuffer[4];
        upData[4]=ucTempBuffer[5];
        upData[5]=ucTempBuffer[6];
        return 1;
    }
    return 0;
}



uchar AllLossVoltageStatuscheck(void)
{
    //if(GAL_YES==FLG_ALL_LOSSVOLTAGE_STATUS)
    if(fGetAllLostVoltageStatus)
    {
        return GAL_YES;
    }
    return GAL_NO;
}

void AllLossVoltageSecTimeAdd(void)
{
    if(fGetAllLostVoltageStatus)
    {
        ucAllLossVoltageContineTime++;
    }
}

void AllLossVoltageMinTimeAdd(void)
{
    if(ucAllLossVoltageContineTime >= 60)
    {
        Data3ByteBCDAdd1(RAM_ALLLOSS_VOLTAGE_TIME);
        ucAllLossVoltageContineTime -= 60;
    }
}

void  AllLossVoltageMode_34(void)
{
    uchar ucTemp,ucContinueTime,ucStatus;
    u16 uiStartV;
    ulong ulStartI;//,ulReturnI;
//  ulong uiTempVACsub;
    
// AA --电压判断条件60% Un-- AA 
// AA --该参数固定-- AA 
    uiStartV=ulTypeUn*6/10;
    
    ulStartI=ulTypeIb*50;
    ucTemp=GAL_NO;
    if(PROGFUNCTION_TYPE_METER_TYPE==METERTYPE_3_3)
    {
//      if(uiNowVoltage[0]>uiNowVoltage[2])
//      {
//          uiTempVACsub=uiNowVoltage[0]-uiNowVoltage[2];
//      }
//      else
//      {
//          uiTempVACsub=uiNowVoltage[2]-uiNowVoltage[0];
//      }
        if(((uiNowVoltage[0]+uiNowVoltage[2])<uiStartV)&&((ulStartI<ulNowCurrent[0])||(ulStartI<ulNowCurrent[2])))
        {
            ucTemp=GAL_YES;
        }
    }
    else
    {
        if((uiStartV>uiNowVoltage[0])&&(uiStartV>uiNowVoltage[1])&&(uiStartV>uiNowVoltage[2]))
        {
            if((ulStartI<ulNowCurrent[0])||(ulStartI<ulNowCurrent[1])||(ulStartI<ulNowCurrent[2]))
            {
                ucTemp=GAL_YES;
            }
        }
    }
    
    ucContinueTime=60;
    
    //ucStatus=FLG_ALL_LOSSVOLTAGE_STATUS;
    ucStatus=fGetAllLostVoltageStatus;
    if(1==TranslateStatus0or1(&ucStatus,&ucTempAllLossVoltageStatusUse,
        &ucTempAllLossVoltageContinueTime,ucContinueTime,ucTemp))
    {
        
        if(GAL_YES==ucStatus)
        {
            if(PROGFUNCTION_TYPE_METER_TYPE==METERTYPE_3_3)
            {
                ulStartI=ulNowCurrent[0]+ulNowCurrent[2];
                ulStartI=ulStartI/2;
            }
            else
            {
                ulStartI=ulNowCurrent[0]+ulNowCurrent[1]+ulNowCurrent[2];
                ulStartI=ulStartI/3;
            }
            
            AllLossVoltageStart(ulStartI);
        }
        else
        {
            AllLossVoltageEnd();
        }
    }
}


uchar AllLossVoltageMode(void)
{

    if(isSystemResetUnfinisded)
        return DLT_RET_SUCC;
    
    if(GAL_NO == PROGFUNCTION_ALLLOSTV )
    {
        FLG_ALL_LOSSVOLTAGE_STATUS = GAL_NO;
        fAllLostVoltageStatusClr;
        return DLT_RET_UNSUPPORT;
    }
    else
    {
        //if(isFlashFree)
        if(1)
        {
            AllLossVoltageMode_34();
            return DLT_RET_SUCC;
        }
        else
        {
            return DLT_RET_UNFINISHED;
        }
    }
}




