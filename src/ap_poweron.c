#define AP_POWERON_GLOBALS
#include "common.h"

void PowerdDownMode_34(void);
void InitialCommExplainFrame(void);


/*********************************************************************
功能：  下电操作过程
范围：  应用层直接调用
注释：  无
作者：  张龙
版本：  V1.0
最后修改时间：2009-01-19
修改说明：创建
********************************************************************/


void PowerOnDataResume(void)
{
    g_OpenFlashPower = 0;
}

/*void PowerWakeupDataInit(void)
{
    KeyEventInit();
}*/


void PowerOnDataInit(void)
{
    PowerOnDataResume();
    //ADInit();
    //CoverOpenInit();
    CutCurrentInit();
    CutVoltageInit();
    DownVoltageInit();
    FreezeInit();
    LossCurrentInit();
    LossVoltageInit();
    AllLossVoltagePowerOnInit();
    MoniterInit();
    OrderCurrentInit();
    OrderVoltageInit();
    OverCurrentInit();
    OverPowerInit();
    OverVoltageInit();
    RecordInit();
    RestoreInit();
    ReversePowerInit();
    UnbalanceCurrentInit();
    UnbalanceVoltageInit();
    PowerClacInit();
    GetPowerClacResidue();
    //RemoteInit();
    DemandDataInit();
    DemandOverInit();
    //EventProgramRecordReset();
    //KeyEventInit();
    //RecordInit();  //it is no need to repeat
    AlarmInit();
    LossCopperIronResume();
    AngleInit();
    RelayInit();
    PluseOutInit();
    OverTotalCosInit();
    //MemoryStatusInit();//提前初始化，放在MeterPowerOnInit()
    AuxPowerPowerOnInit();
    ModuleInit();
    SaveDataInit();
    InitialCommExplainFrame();
    //ClockCompensateInit();
    LoadEventAccTime();
    InitPriceSwitch();
#ifdef TIME_FASTER_TEST
    TimeFasterTestPoweron();
#endif
#ifdef  VRAM_ENABLE
    vram_resume();
#endif
    if(get_program_key_status() == 1)
        FLG_PROGRAM_STATUS = GAL_YES;
    else
        FLG_PROGRAM_STATUS = GAL_NO;

}

//1 下面是掉电事件的检测
uchar ucTempPowerDownStatusUse,ucTempPowerDownContinueTime;
void PowerDownRecordStart(void)
{
    ulong ulDataAddr;
    ulDataAddr=SetTwoTableNextPoint(TYPE_POWER_DOWN_RECORD);
//fprintf(stderr, "%s-%d,Power off End Record Addr=%x\n", __FUNCTION__, __LINE__,ulDataAddr);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetTimeDataToPoint(&Wr_data[0]);
        memset(&Wr_data[6], 0x00, 6);
        WriteDataDirect(&Wr_data[0], ulDataAddr,  12);
        // AA 停电次数 + 1  AA
        Data3ByteBCDAdd1(EPL_POWER_DOWN_COUNT);
    }
    ClrFlashMode();
    FLG_SYSTEMPOWER_STATUS=GAL_YES;
    fPowerDownStatusSet;
    
}


void PowerDownRecordEnd(void)
{
    ulong ulDataAddr;
    ulDataAddr=GetTwoTableAddrFromBlock(TYPE_POWER_DOWN_RECORD,0,6);
//fprintf(stderr, "%s-%d,Power off End Record Addr=%x\n", __FUNCTION__, __LINE__,ulDataAddr);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetTimeDataToPoint(&Wr_data[0]);
        WriteDataDirect(&Wr_data[0], ulDataAddr,  6);
    }   
    FLG_SYSTEMPOWER_STATUS=GAL_NO;
    fPowerDownStatusClr;
}







void PowerdDownMode_34(void)
{
    uchar ucTemp,ucContinueTime,ucStatus;
    u16 uiStartV;
    ulong ulStartI;//,ulReturnI;
//  ulong uiTempVACsub;

#if(CONFIG_METER_AUX_MODE_ENABLE == CONFIG_METER_AUX_MODE)
// AA --“掉电判断条件”，由“电压电流小于设定阈值（60%，5%）”改为“实际电表主电源掉电”。-- AA    
// AA --但是带辅助电源情况下，表具不会掉电，就只能检测测量电压。但阈值相应可以缩小-- AA 
    //if(fGetAuxPowerDownStatus == GAL_NO)
    if(GetAuxPowerStatus())
        uiStartV = ulTypeUn*6/10;
    else
        uiStartV=100;       //10V
#else
// AA --电压判断条件60% Un-- AA 
// AA --该参数固定-- AA 
    uiStartV=100;       //10V
#endif
    ulStartI=ulTypeIb*50;
    ucTemp=GAL_NO;
    if(PROGFUNCTION_TYPE_METER_TYPE==METERTYPE_3_3)
    {
        if(((uiNowVoltage[0]+uiNowVoltage[2])<uiStartV)&&((ulNowCurrent[0]<ulStartI)&&(ulNowCurrent[2]<ulStartI)))
        {
            ucTemp=GAL_YES;
        }
    }
    else
    {
		if((uiStartV>uiNowVoltage[0])&&(uiStartV>uiNowVoltage[1])&&(uiStartV>uiNowVoltage[2]))
        {
            if((ulNowCurrent[0]<ulStartI)&&(ulNowCurrent[1]<ulStartI)&&(ulNowCurrent[2]<ulStartI))
            {
                ucTemp=GAL_YES;
            }
        }
    }
    ucContinueTime=60;
    
    //ucStatus=FLG_SYSTEMPOWER_STATUS;
    ucStatus = fGetPowerDownStatus;
    if(1==TranslateStatus0or1(&ucStatus,&ucTempPowerDownStatusUse,
        &ucTempPowerDownContinueTime,ucContinueTime,ucTemp))
    {
        
        if(GAL_YES==ucStatus)
        {       
            PowerDownRecordStart();
//fprintf(stderr, "%s-%d,\n", __FUNCTION__, __LINE__);
        }
        else
        {
            PowerDownRecordEnd();
        }
    }
    

}

uchar PowerdDownMode(void)
{

    if(isSystemResetUnfinisded)
        return DLT_RET_SUCC;
    
    //if(isFlashFree)
    if(1)
    {
        PowerdDownMode_34();
    }
    return DLT_RET_SUCC;
}

void PowerDownWhenPowerOnRecord(uchar * ucStartTime)
{
  //  ulong ulDataAddr;
    u16 uiStartTime;
    u16 uiNowTime;
    uchar ucStatus;
    ucTempPowerDownStatusUse=GAL_NO;
    ucTempPowerDownContinueTime=0;

    //if(GAL_YES!=FLG_SYSTEMPOWER_STATUS)
    if(GAL_YES != fGetPowerDownStatus)
    {
        ucStatus=GAL_NO;
        uiStartTime=NumDayFromDate(&ucTimeLastSave[3]);
        uiNowTime=NumDayFromDate(&RSOFT_RTC_DAY);
        if(uiNowTime>=uiStartTime)
        {
            uiNowTime=uiNowTime-uiStartTime;
            if(uiNowTime>1)
            {
                ucStatus=GAL_YES;
            }
            else
            {
                uiNowTime=uiNowTime*24+OneByteBcdToHex(RSOFT_RTC_HOUR);
                uiStartTime=OneByteBcdToHex(ucTimeLastSave[2]);
                if(uiNowTime>=uiStartTime)
                {
                    uiNowTime=uiNowTime-uiStartTime;
                    if(uiNowTime>1)
                    {
                        ucStatus=GAL_YES;
                    }
                    else
                    {
                        uiNowTime=uiNowTime*60+OneByteBcdToHex(RSOFT_RTC_MINUTE);
                        uiStartTime=OneByteBcdToHex(ucTimeLastSave[1]);
                        if(uiNowTime>=uiStartTime)
                        {
                            uiNowTime=uiNowTime-uiStartTime;
                            if(uiNowTime>1)
                            {
                                ucStatus=GAL_YES;
                            }
                            else
                            {
                                uiNowTime=uiNowTime*60+OneByteBcdToHex(RSOFT_RTC_SECOND)-OneByteBcdToHex(ucTimeLastSave[0]);
                                if(uiNowTime>58)
                                {
                                    ucStatus=GAL_YES;
                                }
                            }
                        }
                    }
                }
            }
        }
        if(GAL_YES==ucStatus)
        {						//停电发生时间的记录改放到停电时产生，所以这里屏蔽
        	fPowerDownStatusSet;
           /* ulDataAddr=SetTwoTableNextPoint(TYPE_POWER_DOWN_RECORD);
            if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
            {
                memcpy(&Wr_data[0], ucStartTime, 6);
                memset(&Wr_data[6], 0x00, 6);
               // WriteDataDirect(&Wr_data[0], ulDataAddr,  12);
                // AA 停电次数 + 1  AA
                Data3ByteBCDAdd1(EPL_POWER_DOWN_COUNT);
                FLG_SYSTEMPOWER_STATUS=GAL_YES;
                fPowerDownStatusSet;
            }
            ClrFlashMode();*/
        }
    }
}



volatile uchar g_OpenFlashPower; 
void CloseFlashPowerMode(void)
{
    if(g_OpenFlashPower)
    {
        g_OpenFlashPower--;
        OpenFlashPowerFromBat();
    }
    else
    {
        CloseFlashPowerFromBat();
    }
}

// 以前在掉电时刻结束电网异常事件，现在这些事件在掉电时刻只记录标志，
// 在上电时刻调用此函数结束事件。
// 返回1，掉电；返回0，所有事件正常结束。
uchar EventRecordPowerOn(void)
{
    uchar temp;

    temp = 0;
#if(CONFIG_METER_STOPEVENT_POWERON == GAL_YES)    
    ReadDataDirect(EPL_POWEROFF_SAVEDATA_ADDR,246,&RAM[RAM_CURRENT_LOSS_AV_AH_ALL]);
    ReadDataDirect(EPL_POWEROFF_SAVEDATA_ADDR+246, 19, &RAM[RAM_CURRENT_METER_STATUS01]);
    if(FLG_DEMANDOVER_STATUS)
    {
        ReadDataDirect(EPL_POWEROFF_SAVEDATA_ADDR+246+19, DEMAND_OVER_NUM*BYTES_PER_DEMAND, (uchar*)&DemandOverData[0]);
    }
    memcpy(&RAM[RAM_SOFT_SECOND],&ucTimeLastSave[0],sizeof(STR_CALENDAR));
    if(IfPowerDown())
        return 1;
    while(temp < 15)
    {
        switch(temp)
        {
            case 0:
                CutCurrentStopIfStart();
                break;
        
            case 1:
                CutVoltageStopIfStart();
                break;
            
            case 2:
                DownVoltageStopIfStart();
                break;
            
            case 3:
                DemandOverStopIfStart();
                memset((uchar*)&DemandOverData[0],0x00,DEMAND_OVER_NUM*BYTES_PER_DEMAND);
                WriteDataDirect((uchar*)&DemandOverData[0], EPL_POWEROFF_SAVEDATA_ADDR+246+19, DEMAND_OVER_NUM*BYTES_PER_DEMAND);
                break;
            
            case 4:
                LossCurrentStopIfStart();
                break;
            
            case 5:
                LossVoltageStopIfStart();
                break;
            
            case 6:
                OrderCurrentStopIfStart();
                break;
            
            case 7:
                OrderVoltageStopIfStart();
                break;
            
            case 8:
                OverCurrentStopIfStart();
                break;
            
            case 9:
                OverPowerStopIfStart();
                break;
            
            case 10:
                OverVoltageStopIfStart();
                break;
            
            case 11:
                ReversePowerStopIfStart();
                break;
            
            case 12:
                UnbalanceCurrentStopIfStart();
                break;
            
            case 13:
                UnbalanceVoltageStopIfStart();
                break;
            
            case 14:
                OverTotalCosStopIfStart();
                break;
            default:
                break;
        }
        if(IfPowerDown())
        {
            WriteDataDirect(&RAM[RAM_CURRENT_METER_STATUS01], EPL_POWEROFF_SAVEDATA_ADDR+246, 19);
            return 1;
        }
        temp++;
    }
    // 记录完成后，清相关数据和状态字
    memset(&Wr_data[0],0x00,246+19);
    memset(&RAM[RAM_CURRENT_LOSS_AV_AH_ALL],0x00,246);
    memset(&RAM[RAM_CURRENT_METER_STATUS01],0x00,19);
    WriteDataDirect(&Wr_data[0], EPL_POWEROFF_SAVEDATA_ADDR, 246+19);
#else
    memset(&RAM[RAM_CURRENT_LOSS_AV_AH_ALL],0x00,246);
#endif    
    return 0;
}


// 上电擦除flash,  死等直到擦除完毕，清标志
// 如果擦除过程中掉电，等下次上电完成擦除。
void EraseFlashPowerOn(void)
{
    ulong ulTempAddr;
    
    if(fGetEraseFlashStatus)
    {
//#pragma diag_remark=Pa082
        ulTempAddr = ulGetEraseFlashAddr;
//#pragma diag_default=Pa082
        WaitClrFlash(ulTempAddr);
        ClrFlashMode();
        while(ucProgramFlashWait)
        {
            Delayms(10);
            ucProgramFlashWait--;
        }
        if(ucProgramFlashWait== 0)
        {
            fEraseFlashStatusClr;
            SetEraseFlashAddr(NULLDATAADDR);
        }
        #if 0
        for(i=0;i<8;i++)
        {
            ReadDataDirect(ulTempAddr&0xFFFFF000,512,&Wr_data[0]);
            for(j=0;j<512;j++)
            {
                if(Wr_data[j] != 0)
                {
                    return;
                }
            }
        }
        if(i>=8)
        {
            fEraseFlashStatusClr;
            SetEraseFlashAddr(NULLDATAADDR);
        }
        #endif
    }
}


