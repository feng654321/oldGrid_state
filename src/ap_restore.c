#define AP_RESTORE_GLOBALS
#include "common.h"

#if(CONFIG_METER_AREA_MODE_SOUTHGRID==CONFIG_METER_AREA_MODE)
#define CON_HISTORY_POWER_COUNT_MAX     1   // 最多补1点
#define CON_HISTORY_POWERUSE_COUNT_MAX  1
#define CON_HISTORY_DEMAND_COUNT_MAX    1
#define CON_HISTORY_MONITER_COUNT_MAX   1
#elif (CONFIG_METER_AREA_MODE_SHANGHAI==CONFIG_METER_AREA_MODE)
#define CON_HISTORY_POWER_COUNT_MAX     12  // 最多补12点
#define CON_HISTORY_POWERUSE_COUNT_MAX  12
#define CON_HISTORY_DEMAND_COUNT_MAX    12
#define CON_HISTORY_MONITER_COUNT_MAX   12
#endif 
#define CON_BALANCE_DAY_NUM_MAX         31
#define CON_HISTORY_MONITER_LENGTH      27
/*********************************************************************
功能：  本文件做数据转存功能
范围：  应用层直接调用
注释：  无
作者：  张龙
版本：  V1.0
最后修改时间：2009-01-19
修改说明：创建
********************************************************************/

uchar ucRestoreRequestPower;
uchar ucRestoreRequestPowerUse;
uchar ucRestoreRequestDemand;
uchar ucRestoreRequestDemand0xff;
uchar ucRestoreRequestMoniter;
uchar ucRestoreRequestHourPower;
uchar ucRestoreRequestDayPower;

uchar ucRestoreMinute;

uchar  RestoreDemandNeedSaveFromTimeAddr(ulong ulTimeAddr);


void RestoreInit(void)
{
    ucRestoreRequestPower=GAL_NO;
    ucRestoreRequestPowerUse=GAL_NO;
    ucRestoreRequestDemand=GAL_NO;
    ucRestoreRequestDemand0xff=GAL_NO;
    ucRestoreRequestMoniter=GAL_NO;
    ucRestoreRequestDayPower=GAL_NO;
    ucRestoreRequestHourPower=GAL_NO;
    ucRestoreMinute=0xff;
}

void RestoreMoniterClr(void)
{
    memset(&RAM[RAM_VOLTAGE_ALL_MONITOR_STAT_BLOCK_START], 0x00, (4*CON_HISTORY_MONITER_LENGTH)+3);
    WriteDataDirect(&RAM[RAM_VOLTAGE_ALL_MONITOR_STAT_BLOCK_START], EPL_VOLTAGE_ALL_MONITOR_STAT_BLOCK_START, (4*CON_HISTORY_MONITER_LENGTH)+3);
}
void RestoreMoniter(uchar * ucPTime)
{
    ulong ulDataAddr;
    WriteDataDirect(ucPTime, EPL_RESTOREMONITER_LASTTIME, 5);
    ulDataAddr=SetTwoTableNextPoint(TYPE_MONITOR_VOLTAGE_ALL_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        WriteDataDirect(&RAM[RAM_VOLTAGE_ALL_MONITOR_STAT_BLOCK_START+3], ulDataAddr, CON_HISTORY_MONITER_LENGTH);
    }
    ClrFlashMode();
    ClearWatchDog();
    ulDataAddr=SetTwoTableNextPoint(TYPE_MONITOR_VOLTAGE_A_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        WriteDataDirect(&RAM[RAM_VOLTAGE_A_MONITOR_STAT_BLOCK_START], ulDataAddr, CON_HISTORY_MONITER_LENGTH);
    }
    ClrFlashMode();
    ClearWatchDog();
    ulDataAddr=SetTwoTableNextPoint(TYPE_MONITOR_VOLTAGE_B_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        WriteDataDirect(&RAM[RAM_VOLTAGE_B_MONITOR_STAT_BLOCK_START], ulDataAddr, CON_HISTORY_MONITER_LENGTH);
    }
    ClrFlashMode();
    ClearWatchDog();
    ulDataAddr=SetTwoTableNextPoint(TYPE_MONITOR_VOLTAGE_C_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        WriteDataDirect(&RAM[RAM_VOLTAGE_C_MONITOR_STAT_BLOCK_START], ulDataAddr, CON_HISTORY_MONITER_LENGTH);
    }
    ClrFlashMode();
    ClearWatchDog();
    Data3ByteBCDAdd1(EPL_TOTAL_CLR_MONITER_COUNT);
}
void RestorePower(uchar * ucPTime)
{
    ulong ulDataAddr;
    WriteDataDirect(ucPTime, EPL_RESTOREPOWER_LASTTIME, 5);
    ulDataAddr=SetTwoTableNextPoint(TYPE_HISTROY_POWER_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        memcpy(&Wr_data[5], &RAM[RAM_KWH_C_ALL], BYTES_KWH_TOTAL);
        memcpy(&Wr_data[BYTES_KWH_TOTAL+5], ucPTime,5);
        WriteDataDirect(&Wr_data[5], ulDataAddr, BYTES_KWH_TOTAL+5);
    }
    ClrFlashMode();
    Data3ByteBCDAdd1(EPL_TOTAL_CLR_KWH_COUNT);

}
void RestorePowerUse(uchar * ucPTime)
{
    ulong ulDataAddr;
    WriteDataDirect(ucPTime, EPL_RESTOREPOWERUSE_LASTTIME, 5);
    ulDataAddr=SetTwoTableNextPoint(TYPE_HISTROY_USEPOWER_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        memcpy(&Wr_data[0], &RAM[RAM_KWH_ALL_USE_START+0], BYTES_KWH_USE_TOTAL);
        memcpy(&Wr_data[BYTES_KWH_USE_TOTAL], ucPTime,5);
        WriteDataDirect(&Wr_data[0], ulDataAddr, BYTES_KWH_USE_TOTAL+5);
        memset( &RAM[RAM_KWH_ALL_USE_START+0],0, BYTES_KWH_USE_TOTAL);
        WriteDataDirect(&RAM[RAM_KWH_ALL_USE_START+0], EPL_KWH_ALL_USE_START, BYTES_KWH_USE_TOTAL);
    }
    ClrFlashMode();
    Data3ByteBCDAdd1(EPL_TOTAL_CLR_KWHUSE_COUNT);
    
}

#if 0
void RestoreDemandClr(void)
{
	memset(&RAM[RAM_DEMAND_DATA_START], 0x00, BYTES_DEMAND_TOTAL);
    SetDataDirrect(EPL_DEMAND_DATA_START, 0xff, BYTES_DEMAND_TOTAL);
    DemandDataInit();
        
}
#endif
void RestoreDemand0xFF(uchar * ucPTime)
{
    ulong ulDataAddr;
    WriteDataDirect(ucPTime, EPL_RESTOREDEMAND_LASTTIME, 5);
    ulDataAddr=SetTwoTableNextPoint(TYPE_HISTROY_DEMAND_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetDataDirrect(ulDataAddr, 0xff, BYTES_DEMAND_TOTAL);
    }
    ClrFlashMode();
    Data3ByteBCDAdd1(EPL_TOTAL_CLR_DEMAND_COUNT);
    
}

void RestoreDemand(uchar * ucPTime)
{
    ulong ulDataAddr;
    WriteDataDirect(ucPTime, EPL_RESTOREDEMAND_LASTTIME, 5);
    ulDataAddr=SetTwoTableNextPoint(TYPE_HISTROY_DEMAND_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        CpyDataDirrect(ulDataAddr, RAM_DEMAND_DATA_START, BYTES_DEMAND_TOTAL);
    }
    Data3ByteBCDAdd1(EPL_TOTAL_CLR_DEMAND_COUNT);
    ClrFlashMode();
}
uchar  RestoreDemandNeedSaveFromTimeAddr(ulong ulTimeAddr)
{
    uchar ucValue;
    ucValue=GAL_NO;
    if(1==ReadDataDirect(ulTimeAddr, 5, &Wr_data[0]))
    {
        if(Wr_data[3] != RSOFT_RTC_MONTH)
            ucValue=GAL_YES;
        if(Wr_data[4] != RSOFT_RTC_YEAR)
            ucValue=GAL_YES;
    }
    return ucValue;
}

uchar RestoreMode(void)
{
    uchar ucTemp;
    uchar ucBalanceDayNum;
    
    if(ucRestoreMinute!= RSOFT_RTC_MINUTE)
    {
        ucRestoreMinute=RSOFT_RTC_MINUTE;
        if((0x00==RSOFT_RTC_MINUTE))
        {
            ucRestoreRequestHourPower=GAL_YES;
            if(0x00==RSOFT_RTC_HOUR)
            {
                ucRestoreRequestDayPower=GAL_YES;
//ZD 在集中器和专变中，无此功能
/*
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
                ClearAllFarCtlCount();
#endif
*/
            }
        }
        ucBalanceDayNum = PROGFUNCTION_COEF_BALANCE_DAY_NUM;
        if(ucBalanceDayNum>CON_BALANCE_DAY_NUM_MAX)
            ucBalanceDayNum=3;
        if(0x00==RSOFT_RTC_MINUTE)
        {
            for(ucTemp=0;ucTemp<ucBalanceDayNum;ucTemp++)
            {
                if((RAM[RAM_BALANCE_DAY_01+ucTemp*2 +0] == RSOFT_RTC_HOUR) 
                    &&(RAM[RAM_BALANCE_DAY_01+ucTemp*2 +1] == RSOFT_RTC_DAY))
                {
#if(CONFIG_METER_AREA_MODE_SHANGHAI==CONFIG_METER_AREA_MODE)
                    ReadDataDirect(EPL_RESTOREPOWER_LASTTIME, 5, &Wr_data[10]);
                    if(ulNowMinTime>mmHHDDMMYYToLong(&Wr_data[10]))
                    {
                        RestoreModePowerOn();
                        ucRestoreRequestPower=GAL_NO;
                        ucRestoreRequestPowerUse=GAL_NO;
                        ucRestoreRequestDemand=GAL_NO;
                    }
                    else
#endif
                    {
                        if(GAL_YES ==TimeChangedhhDDMMYYFromAddr(EPL_RESTOREPOWER_LASTTIME))
                        {
                            ucRestoreRequestPower=GAL_YES;
                        }
                        if(GAL_YES ==TimeChangedhhDDMMYYFromAddr(EPL_RESTOREPOWERUSE_LASTTIME))
                        {
                            ucRestoreRequestPowerUse=GAL_YES;
                        }
                        if(GAL_YES ==TimeChangedhhDDMMYYFromAddr(EPL_RESTOREDEMAND_LASTTIME))
                        {
        // AA --如果是第一个抄表日则转存需量，否则，需量转存FF--AA
                            if(0==ucTemp)
                            {
                                ucRestoreRequestDemand=GAL_YES;
        //                      ucRestoreRequestDemand0xff=GAL_NO;
                            }
                            else
                            {
        //                      ucRestoreRequestDemand=GAL_NO;
                                ucRestoreRequestDemand0xff=GAL_YES;
                            }
                        }
                    }
                }
            }
        }
        // AA--防止多个抄表日跟第一个抄表日相同而引起需量转存错误--AA
        if(GAL_YES==ucRestoreRequestDemand)
        {
            ucRestoreRequestDemand0xff=GAL_NO;
        }

        if((0x00==RSOFT_RTC_MINUTE)&&(0x00 == RSOFT_RTC_HOUR)&&(0x01 == RSOFT_RTC_DAY))
        {
#if(CONFIG_METER_AREA_MODE_SHANGHAI==CONFIG_METER_AREA_MODE)
            ReadDataDirect(EPL_RESTOREMONITER_LASTTIME, 5, &Wr_data[10]);
            if(ulNowMinTime>mmHHDDMMYYToLong(&Wr_data[10]))
            {
                RestoreModePowerOn();
                ucRestoreRequestMoniter=GAL_NO;
            }
            else
#endif
            {
                if(GAL_YES ==TimeChangedhhDDMMYYFromAddr(EPL_RESTOREMONITER_LASTTIME))
                {
                    ucRestoreRequestMoniter=GAL_YES;
                }
            }
        }
    }
    
    if(isFlashBusy)       // Flash 繁忙，暂不存储
        return DLT_RET_UNFINISHED;

    if((GAL_YES==ucRestoreRequestPower))
    {
        ucRestoreRequestPower=GAL_NO;
        SetmmhhDDMMYYToPoint(&Wr_data[0]);
        RestorePower(&Wr_data[0]);
    }
    
    if(isFlashBusy)       // Flash 繁忙，暂不存储
        return DLT_RET_UNFINISHED;
    
    if((GAL_YES==ucRestoreRequestPowerUse))
    {
        ucRestoreRequestPowerUse=GAL_NO;
        SetmmhhDDMMYYToPoint(&Wr_data[0]);
        RestorePowerUse(&Wr_data[0]);
    }
    
    if(isFlashBusy)       // Flash 繁忙，暂不存储
        return DLT_RET_UNFINISHED;
    
    if((GAL_YES==ucRestoreRequestDemand))
    {
        ucRestoreRequestDemand=GAL_NO;
        SetmmhhDDMMYYToPoint(&Wr_data[0]);
        RestoreDemand(&Wr_data[0]);
        DemandDataClrAllCurrent();
    }
    
    if(isFlashBusy)       // Flash 繁忙，暂不存储
        return DLT_RET_UNFINISHED;
    
    if((GAL_YES==ucRestoreRequestDemand0xff))
    {
        ucRestoreRequestDemand0xff=GAL_NO;
        SetmmhhDDMMYYToPoint(&Wr_data[0]);
        RestoreDemand0xFF(&Wr_data[0]);
        // RestoreDemandClr();
    }
    
    if(isFlashBusy)       // Flash 繁忙，暂不存储
        return DLT_RET_UNFINISHED;
    
    if((GAL_YES==ucRestoreRequestMoniter))
    {
        ucRestoreRequestMoniter=GAL_NO;
        SetmmhhDDMMYYToPoint(&Wr_data[0]);
        RestoreMoniter(&Wr_data[0]);
        RestoreMoniterClr();
    }
    
    if(isFlashBusy)       // Flash 繁忙，暂不存储
        return DLT_RET_UNFINISHED;
    
    if((GAL_YES==ucRestoreRequestHourPower))
    {
        ucRestoreRequestHourPower=GAL_NO;
        //WriteDataDirect(&uKwhBCopyData[0][0], FL1_LAST_PER_HOUR_POWER+0*512, 512);
        //WriteDataDirect((&uKwhBCopyData[0][0])+512, FL1_LAST_PER_HOUR_POWER+1*512, 512);
        //WriteDataDirect((&uKwhBCopyData[0][0])+1024, FL1_LAST_PER_HOUR_POWER+2*512, 194);
    }
    
    if((GAL_YES==ucRestoreRequestDayPower))
    {
        ucRestoreRequestDayPower=GAL_NO;
        //WriteDataDirect(&uKwhBCopyData[0][0], FL1_LAST_PER_DAY_POWER+0*512, 512);
        //WriteDataDirect((&uKwhBCopyData[0][0])+512, FL1_LAST_PER_DAY_POWER+1*512, 512);
        //WriteDataDirect((&uKwhBCopyData[0][0])+1024, FL1_LAST_PER_DAY_POWER+2*512, 194);
    }
    return DLT_RET_SUCC;
}


#if(CONFIG_METER_AREA_MODE_SOUTHGRID==CONFIG_METER_AREA_MODE)
void RestoreModePowerOn(void)
{
    ST_BALANCEDAY_POWERON_BUFFER_PARAM stBanlancePower[CON_HISTORY_POWER_COUNT_MAX+1];
    UN_BALANCEDAY_TYPE_PARAM ucBanlanceDayBuffer[CON_BALANCE_DAY_NUM_MAX+1];            // 将每月的几个结算日从小到大排序
    // uchar ucBanlanceEnable[CON_BALANCE_DAY_NUM_MAX];
    uchar ucBalanceDayNum,ucBalanceDayNumEveryMonth;//ucBalanceDayNumEveryMonth为每月结算日数
    uchar ucTemp,ucDay,ucHour,ucTempMove,ucTempAdd;
    uchar ucCanWhile;
    uchar ucBalanceDayPoint,ucBalanceDayCount;//ucBalanceDayCount为补的点数
    u16 uiTempData;
    ulong ulStart,ulEnd,ulTem;
    uchar ucTimeBuffer[3];
    ucBalanceDayNum = PROGFUNCTION_COEF_BALANCE_DAY_NUM;
    if(ucBalanceDayNum>CON_BALANCE_DAY_NUM_MAX)
        ucBalanceDayNum=3;

    memset(&(ucBanlanceDayBuffer[0].ucStart), 0x00, 31*2);
    ucBalanceDayNumEveryMonth=0;


    // AA 下面内容重新排序抄表日以及统计总的抄表日数目  AA
    if(0!=ucBalanceDayNum)
    {
        // AA 结算日数据按照时间从大到小排序   AA
        // AA 如果是同一日的数据，则按照小时排序   AA
        // AA 如果有相同的结算日数据，则只取其中的一个   AA
        // AA 如果时间日期时间不合法，则不统计这个数据   AA
        for(ucTemp=0;ucTemp<ucBalanceDayNum;ucTemp++)
        {
            ucDay=RAM[RAM_BALANCE_DAY_01+ucTemp*2+1];
            ucHour=RAM[RAM_BALANCE_DAY_01+ucTemp*2+0];
            if(2==TestDay(ucDay)+TestHour(ucHour))
            //  AA   数据判断条件，满足条件才处理   AA
            {
                if(0 != ucBalanceDayNumEveryMonth)
                {
                    for(ucTempAdd=0;ucTempAdd<ucBalanceDayNum;ucTempAdd++)
                    {
                        uiTempData=ucDay;
                        uiTempData=(uiTempData<<8)+ucHour;
                        // AA 如果相等---> 则不需要增加----AA
                        if(uiTempData == ucBanlanceDayBuffer[ucTempAdd].uiDataCode)
                        {
                            ucTempAdd=ucBalanceDayNum;
                        }
                        else
                        {
                            // AA  数据小，则增加 AA
                            if(uiTempData > ucBanlanceDayBuffer[ucTempAdd].uiDataCode)
                            {
                                // AA   移动数据 AA
                                for(ucTempMove=(ucBalanceDayNum);ucTempMove>ucTempAdd;ucTempMove--)
                                {
                                    ucBanlanceDayBuffer[ucTempMove].uiDataCode = ucBanlanceDayBuffer[ucTempMove-1].uiDataCode;
                                }
                                // AA  添加数据 AA
                                ucBanlanceDayBuffer[ucTempAdd].uiDataCode=uiTempData;
                                
                                ucBalanceDayNumEveryMonth++;
                                ucBanlanceDayBuffer[ucBalanceDayNumEveryMonth].uiDataCode=0x0000;
                                ucTempAdd=ucBalanceDayNum; // break;
                            }
                            // AA  数据大，则跳过   AA
                            else
                            {
                                ;// no do
                            }
                        }
                    }
                }
                else
                {
                    ucBanlanceDayBuffer[0].uInChar.ucDay=ucDay;
                    ucBanlanceDayBuffer[0].uInChar.ucHour=ucHour;
                    ucBalanceDayNumEveryMonth++;
                }
            }
        }
    }
    // 如果每月的结算日数为0，则上电不补结算
    ucCanWhile=GAL_NO;
    if(ucBalanceDayNumEveryMonth>0)
    {
        ucCanWhile=GAL_YES;
    }

    // AA 当前时间和停电时间差正确---当前时间应该大于停电时间   AA  
    ulEnd=RSOFT_RTC_YEAR;
    ulEnd=(ulEnd<<8) + RSOFT_RTC_MONTH;
    ulEnd=(ulEnd<<8) + RSOFT_RTC_DAY;
    ulStart=ucTimeLastSave[6];  // year
    ulStart=(ulStart<<8) + ucTimeLastSave[5];// month
    ulStart=(ulStart<<8) + ucTimeLastSave[4];// day
    // 如果当前时间比上次掉电时间大，计算补结算的数目
    if(ulEnd<ulStart)
    {
        ucCanWhile=GAL_NO;
    }
    else
    {
        if(ulEnd==ulStart)
        {
            if(RSOFT_RTC_HOUR<=ucTimeLastSave[2])
            {
                ucCanWhile=GAL_NO;
            }
        }
    }
    ucBalanceDayCount=0;
    if(GAL_YES == ucCanWhile)
    {
        ucBalanceDayPoint=CON_HISTORY_POWER_COUNT_MAX-1;
        ucTimeBuffer[0]=RSOFT_RTC_DAY;
        ucTimeBuffer[1]=RSOFT_RTC_MONTH;
        ucTimeBuffer[2]=RSOFT_RTC_YEAR;
        // AA  开始追溯最近的结算时间  AA
        // AA  追溯的长度由 CON_HISTORY_POWER_COUNT_MAX 决定，基本上为12次  AA
        // AA  追溯的结果数据保存在stBanlancePower 中，这样方便后续处理  AA
        // AA  追溯过程分成当前日，之前日等处理。  AA
        
        // AA  查找今天是否有计算数据  AA
        for(ucTemp=0;ucTemp<ucBalanceDayNumEveryMonth;ucTemp++)
        {
            ucHour=ucBanlanceDayBuffer[ucTemp].uInChar.ucHour;
            if((ucBanlanceDayBuffer[ucTemp].uInChar.ucDay==ucTimeBuffer[0])
                &&(ucHour<=RSOFT_RTC_HOUR))
            {
                // AA  增加一条记录  AA---------->Start
                if(ucBalanceDayCount<CON_HISTORY_POWER_COUNT_MAX)
                {
                    stBanlancePower[ucBalanceDayPoint].ucHour=ucHour;
                    stBanlancePower[ucBalanceDayPoint].ucDay=ucTimeBuffer[0];
                    stBanlancePower[ucBalanceDayPoint].ucMonth=ucTimeBuffer[1];
                    stBanlancePower[ucBalanceDayPoint].ucYear=ucTimeBuffer[2];
                    ucBalanceDayCount++;
                    if(ucBalanceDayPoint>0)
                    {
                        ucBalanceDayPoint--;
                    }
                }
                if(ucBalanceDayCount>=CON_HISTORY_POWER_COUNT_MAX)
                {
                    ucTemp=ucBalanceDayNumEveryMonth;
                    ucCanWhile=GAL_NO;
                }
                // AA  增加一条记录  AA---------->end
            }
        }
        // 搜索今天以前的结算日，统计补点数
        while(GAL_YES==ucCanWhile)
        {
            PerDayFromPoint(&ucTimeBuffer[0]);
            ulEnd=ucTimeBuffer[2];
            ulEnd=(ulEnd<<8) + ucTimeBuffer[1];
            ulEnd=(ulEnd<<8) + ucTimeBuffer[0];
            if(ulStart<ulEnd)
            //AA 查找之前的日子是否有计算数据  AA
            {
                for(ucTemp=0;ucTemp<ucBalanceDayNumEveryMonth;ucTemp++)
                {
                    ucHour=ucBanlanceDayBuffer[ucTemp].uInChar.ucHour;
                    if((ucBanlanceDayBuffer[ucTemp].uInChar.ucDay==ucTimeBuffer[0]))
                    {
                        // AA  增加一条记录  AA---------->Start
                        if(ucBalanceDayCount<CON_HISTORY_POWER_COUNT_MAX)
                        {
                            stBanlancePower[ucBalanceDayPoint].ucHour=ucHour;
                            stBanlancePower[ucBalanceDayPoint].ucDay=ucTimeBuffer[0];
                            stBanlancePower[ucBalanceDayPoint].ucMonth=ucTimeBuffer[1];
                            stBanlancePower[ucBalanceDayPoint].ucYear=ucTimeBuffer[2];
                            ucBalanceDayCount++;
                            if(ucBalanceDayPoint>0)
                            {
                                ucBalanceDayPoint--;
                            }
                        }
                        else
                        {
                            ucTemp=ucBalanceDayNumEveryMonth;
                            ucCanWhile=GAL_NO;
                        }
                        // AA  增加一条记录  AA---------->end
                    }
                }
            }
            else
            {
                if(ulStart==ulEnd)
                // AA 超找停电日是否有计算数据 AA
                {
                    for(ucTemp=0;ucTemp<ucBalanceDayNumEveryMonth;ucTemp++)
                    {
                        ucHour=ucBanlanceDayBuffer[ucTemp].uInChar.ucHour;
                        if((ucBanlanceDayBuffer[ucTemp].uInChar.ucDay==ucTimeBuffer[0])
                            &&(ucHour > ucTimeLastSave[2]))
                        {
                            // AA  增加一条记录  AA---------->Start
                            if(ucBalanceDayCount<CON_HISTORY_POWER_COUNT_MAX)
                            {
                                stBanlancePower[ucBalanceDayPoint].ucHour=ucHour;
                                stBanlancePower[ucBalanceDayPoint].ucDay=ucTimeBuffer[0];
                                stBanlancePower[ucBalanceDayPoint].ucMonth=ucTimeBuffer[1];
                                stBanlancePower[ucBalanceDayPoint].ucYear=ucTimeBuffer[2];
                                ucBalanceDayCount++;
                                if(ucBalanceDayPoint>0)
                                {
                                    ucBalanceDayPoint--;
                                }
                            }
                            else
                            {
                                ucTemp=ucBalanceDayNumEveryMonth;
                                ucCanWhile=GAL_NO;
                            }
                            // AA  增加一条记录  AA---------->end
                        }
                    }
                }
                else
                {
                    ucCanWhile=GAL_NO;
                }
            }
        }

    }
    
    if(ucBalanceDayCount>0)
    {
        // AA  发现需要结算数据  AA
        // AA 开始转存数据AA
        ucBalanceDayPoint=CON_HISTORY_POWER_COUNT_MAX-1;
        for(ucTemp=0;ucTemp<ucBalanceDayCount;ucTemp++)
        {
            if(ucBalanceDayPoint>=CON_HISTORY_POWER_COUNT_MAX)
            // AA 防止异常错误 AA
            {
                ucBalanceDayPoint=CON_HISTORY_POWER_COUNT_MAX-1;
            }
            
            // AA 结算需量数据 AA
            memcpy(&Wr_data[1], &stBanlancePower[ucBalanceDayPoint].ucHour, 4);
            Wr_data[0]=0x00;
            RestoreDemand(&Wr_data[0]);
            if(0==ucTemp)
            {
                // AA 只有在第一次的时候，才清除当前需量 AA
                DemandDataClrAllCurrent();
            }
            // AA 结算电量数据 AA
            memcpy(&Wr_data[1], &stBanlancePower[ucBalanceDayPoint].ucHour, 4);
            Wr_data[0]=0x00;
            RestorePower(&Wr_data[0]);
            // AA 结算用电量数据 AA         
            memcpy(&Wr_data[1], &stBanlancePower[ucBalanceDayPoint].ucHour, 4);
            Wr_data[0]=0x00;
            RestorePowerUse(&Wr_data[0]);
            ucBalanceDayPoint--;
        }
        ucBalanceDayPoint=CON_HISTORY_POWER_COUNT_MAX-1;
        memcpy(&Wr_data[1], &stBanlancePower[ucBalanceDayPoint].ucHour, 4);
        Wr_data[0]=0x00;
        WriteDataDirect(&Wr_data[0], EPL_RESTOREDEMAND_LASTTIME, 5);
        WriteDataDirect(&Wr_data[0], EPL_RESTOREPOWER_LASTTIME, 5);
        WriteDataDirect(&Wr_data[0], EPL_RESTOREPOWERUSE_LASTTIME, 5);      
    }


#if 0
// ==============================================================================

    // AA 下面内容重新排序抄表日以及统计总的抄表日数目  AA
    if(0!=ucBalanceDayNum)
    {
        // AA 结算日数据按照时间从大到小排序   AA
        // AA 如果是同一日的数据，则按照小时排序   AA
        // AA 如果有相同的结算日数据，则只取其中的一个   AA
        // AA 如果时间日期时间不合法，则不统计这个数据   AA
        for(ucTemp=0;ucTemp<ucBalanceDayNum;ucTemp++)
        {
            ucDay=RAM[RAM_BALANCE_DAY_01+ucTemp*2+1];
            ucHour=RAM[RAM_BALANCE_DAY_01+ucTemp*2+0];
            // AA  特别处理,日期只能为1才操作  AA
            if(2==TestDay(ucDay)+TestHour(ucHour))
            //  AA   数据判断条件，满足条件才处理   AA
            {
                if(0 != ucBalanceDayNumEveryMonth)
                {
                    for(ucTempAdd=0;ucTempAdd<ucBalanceDayNum;ucTempAdd++)
                    {
                        uiTempData=ucDay;
                        uiTempData=(uiTempData<<8)+ucHour;
                        // AA 如果相等---> 则不需要增加----AA
                        if(uiTempData == ucBanlanceDayBuffer[ucTempAdd].uiDataCode)
                        {
                            ucTempAdd=ucBalanceDayNum;
                        }
                        else
                        {
                            // AA  数据小，则增加 AA
                            if(uiTempData > ucBanlanceDayBuffer[ucTempAdd].uiDataCode)
                            {
                                // AA   移动数据 AA
                                for(ucTempMove=(ucBalanceDayNum);ucTempMove>ucTempAdd;ucTempMove--)
                                {
                                    ucBanlanceDayBuffer[ucTempMove].uiDataCode = ucBanlanceDayBuffer[ucTempMove-1].uiDataCode;
                                }
                                // AA  添加数据 AA
                                ucBanlanceDayBuffer[ucTempAdd].uiDataCode=uiTempData;
                                
                                ucBalanceDayNumEveryMonth++;
                                ucBanlanceDayBuffer[ucBalanceDayNumEveryMonth].uiDataCode=0x0000;
                                ucTempAdd=ucBalanceDayNum; // break;
                            }
                            // AA  数据大，则跳过   AA
                            else
                            {
                                ;// no do
                            }
                        }
                    }
                }
                else
                {
                    ucBanlanceDayBuffer[0].uInChar.ucDay=ucDay;
                    ucBanlanceDayBuffer[0].uInChar.ucHour=ucHour;
                    ucBalanceDayNumEveryMonth++;
                }
            }
        }
    }
    // AA  特别处理---->Start  AA
    if(ucBalanceDayNumEveryMonth>1)
        ucBalanceDayNumEveryMonth=1;
    // AA  特别处理---->End  AA
    ucCanWhile=GAL_NO;
    if(ucBalanceDayNumEveryMonth>0)
    {
        ucCanWhile=GAL_YES;
    }
    // AA  停电时间读取正确  AA
//  if(0==ReadDataDirect(EPL_SOFT_SECOND, 7, &ucTimeLastSave[0]))
//  {
//      ucCanWhile=GAL_NO;
//  }
    // AA  停电时间数据格式正确  AA 
//  if(0==TestSecondMinuteHourDayMonthYear(&ucTimeLastSave[0], &ucTimeLastSave[4]))
//  {
//      ucCanWhile=GAL_NO;
//  }
    // AA 当前时间和停电时间差正确---当前时间应该大于停电时间   AA  
    ulEnd=RSOFT_RTC_YEAR;
    ulEnd=(ulEnd<<8) + RSOFT_RTC_MONTH;
    ulEnd=(ulEnd<<8) + RSOFT_RTC_DAY;
//  ulEnd=(ulEnd<<8) + RSOFT_RTC_HOUR;
    ulStart=ucTimeLastSave[6];  // year
    ulStart=(ulStart<<8) + ucTimeLastSave[5];// month
    ulStart=(ulStart<<8) + ucTimeLastSave[4];// day
//  ulStart=(ulStart<<8) + ucTimeLastSave[2];// hour
    if(ulEnd<ulStart)
    {
        ucCanWhile=GAL_NO;
    }
    else
    {
        if(ulEnd==ulStart)
        {
            if(RSOFT_RTC_HOUR<=ucTimeLastSave[2])
            {
                ucCanWhile=GAL_NO;
            }
        }
    }
    ucBalanceDayCount=0;
    if(GAL_YES == ucCanWhile)
    {
        ucBalanceDayPoint=CON_HISTORY_POWER_COUNT_MAX-1;
        ucTimeBuffer[0]=RSOFT_RTC_DAY;
        ucTimeBuffer[1]=RSOFT_RTC_MONTH;
        ucTimeBuffer[2]=RSOFT_RTC_YEAR;
        // AA  开始追溯最近的结算时间  AA
        // AA  追溯的长度由 CON_HISTORY_POWER_COUNT_MAX 决定，基本上为12次  AA
        // AA  追溯的结果数据保存在stBanlancePower 中，这样方便后续处理  AA
        // AA  追溯过程分成当前日，之前日等处理。  AA
        
        // AA  查找今天是否有计算数据  AA
        for(ucTemp=0;ucTemp<ucBalanceDayNumEveryMonth;ucTemp++)
        {
            ucHour=ucBanlanceDayBuffer[ucTemp].uInChar.ucHour;
            if((ucBanlanceDayBuffer[ucTemp].uInChar.ucDay==ucTimeBuffer[0])
                &&(ucHour<=RSOFT_RTC_HOUR))
            {
                // AA  增加一条记录  AA---------->Start
                if(ucBalanceDayCount<CON_HISTORY_POWER_COUNT_MAX)
                {
                    stBanlancePower[ucBalanceDayPoint].ucHour=ucHour;
                    stBanlancePower[ucBalanceDayPoint].ucDay=ucTimeBuffer[0];
                    stBanlancePower[ucBalanceDayPoint].ucMonth=ucTimeBuffer[1];
                    stBanlancePower[ucBalanceDayPoint].ucYear=ucTimeBuffer[2];
                    ucBalanceDayCount++;
                    if(ucBalanceDayPoint>0)
                    {
                        ucBalanceDayPoint--;
                    }
                }
                if(ucBalanceDayCount>=CON_HISTORY_POWER_COUNT_MAX)
                {
                    ucTemp=ucBalanceDayNumEveryMonth;
                    ucCanWhile=GAL_NO;
                }
                // AA  增加一条记录  AA---------->end
            }
        }
        while(GAL_YES==ucCanWhile)
        {
            PerDayFromPoint(&ucTimeBuffer[0]);
            ulEnd=ucTimeBuffer[2];
            ulEnd=(ulEnd<<8) + ucTimeBuffer[1];
            ulEnd=(ulEnd<<8) + ucTimeBuffer[0];
            if(ulStart<ulEnd)
            //AA 查找之前的日子是否有计算数据  AA
            {
                for(ucTemp=0;ucTemp<ucBalanceDayNumEveryMonth;ucTemp++)
                {
                    ucHour=ucBanlanceDayBuffer[ucTemp].uInChar.ucHour;
                    if((ucBanlanceDayBuffer[ucTemp].uInChar.ucDay==ucTimeBuffer[0]))
                    {
                        // AA  增加一条记录  AA---------->Start
                        if(ucBalanceDayCount<CON_HISTORY_POWER_COUNT_MAX)
                        {
                            stBanlancePower[ucBalanceDayPoint].ucHour=ucHour;
                            stBanlancePower[ucBalanceDayPoint].ucDay=ucTimeBuffer[0];
                            stBanlancePower[ucBalanceDayPoint].ucMonth=ucTimeBuffer[1];
                            stBanlancePower[ucBalanceDayPoint].ucYear=ucTimeBuffer[2];
                            ucBalanceDayCount++;
                            if(ucBalanceDayPoint>0)
                            {
                                ucBalanceDayPoint--;
                            }
                        }
                        else
                        {
                            ucTemp=ucBalanceDayNumEveryMonth;
                            ucCanWhile=GAL_NO;
                        }
                        // AA  增加一条记录  AA---------->end
                    }
                }
            }
            else
            {
                if(ulStart==ulEnd)
                // AA 超找停电日是否有计算数据 AA
                {
                    for(ucTemp=0;ucTemp<ucBalanceDayNumEveryMonth;ucTemp++)
                    {
                        ucHour=ucBanlanceDayBuffer[ucTemp].uInChar.ucHour;
                        if((ucBanlanceDayBuffer[ucTemp].uInChar.ucDay==ucTimeBuffer[0])
                            &&(ucHour > ucTimeLastSave[2]))
                        {
                            // AA  增加一条记录  AA---------->Start
                            if(ucBalanceDayCount<CON_HISTORY_POWER_COUNT_MAX)
                            {
                                stBanlancePower[ucBalanceDayPoint].ucHour=ucHour;
                                stBanlancePower[ucBalanceDayPoint].ucDay=ucTimeBuffer[0];
                                stBanlancePower[ucBalanceDayPoint].ucMonth=ucTimeBuffer[1];
                                stBanlancePower[ucBalanceDayPoint].ucYear=ucTimeBuffer[2];
                                ucBalanceDayCount++;
                                if(ucBalanceDayPoint>0)
                                {
                                    ucBalanceDayPoint--;
                                }
                            }
                            else
                            {
                                ucTemp=ucBalanceDayNumEveryMonth;
                                ucCanWhile=GAL_NO;
                            }
                            // AA  增加一条记录  AA---------->end
                        }
                    }
                }
                else
                {
                    ucCanWhile=GAL_NO;
                }
            }
        }

    }
    
    if(ucBalanceDayCount>0)
    {
        // AA  发现需要结算数据  AA
        // AA 开始转存数据AA
        ucBalanceDayPoint=CON_HISTORY_POWER_COUNT_MAX-1;
        for(ucTemp=0;ucTemp<ucBalanceDayCount;ucTemp++)
        {
            if(ucBalanceDayPoint>=CON_HISTORY_POWER_COUNT_MAX)
            // AA 防止异常错误 AA
            {
                ucBalanceDayPoint=CON_HISTORY_POWER_COUNT_MAX-1;
            }
            
            // AA 结算需量数据 AA
            memcpy(&Wr_data[1], &stBanlancePower[ucBalanceDayPoint].ucHour, 4);
            Wr_data[0]=0x00;
            RestoreDemand(&Wr_data[0]);
            if(0==ucTemp)
            {
                // AA 只有在第一次的时候，才清除当前需量 AA
                DemandDataClrAllCurrent();
            }
            ucBalanceDayPoint--;
        }
    }



// ==============================================================================
#endif
    
    ulEnd=ValueHexFromBcd(RSOFT_RTC_YEAR);
    ulEnd=ulEnd*12 + ValueHexFromBcd(RSOFT_RTC_MONTH);
    ulStart=ValueHexFromBcd(ucTimeLastSave[6]);
    ulStart=ulStart*12 + ValueHexFromBcd(ucTimeLastSave[5]);
    
    if(ulStart<ulEnd)
    {
        ulTem=ulEnd-ulStart;
        if(ulTem>=CON_HISTORY_MONITER_COUNT_MAX)
        {
            ulStart=ulEnd-CON_HISTORY_MONITER_COUNT_MAX;
        }
        for(ucTemp=0;ucTemp<CON_HISTORY_MONITER_COUNT_MAX;ucTemp++)
        {
            ulStart++;
            if(ulStart>ulEnd)
            {
                ucTemp=CON_HISTORY_MONITER_COUNT_MAX;
            }
            else
            {
                Wr_data[0]=0x00;
                Wr_data[1]=0x00;
                Wr_data[2]=0x01;
                Wr_data[3]=ValueBcdFromHex(ulStart%12);
                if(0==Wr_data[3])
                {
                    Wr_data[3]=0x12;
                    // AA 前面ulStart 已经增加过了，保证是一个大于0 的数字 AA AA
                    Wr_data[4]=ValueBcdFromHex((ulStart-1)/12);
                }
                else
                {
                    Wr_data[4]=ValueBcdFromHex(ulStart/12);
                }
                RestoreMoniter(&Wr_data[0]);
                if(0==ucTemp)
                {
                    RestoreMoniterClr();
                }
                
            }
        }
        
    }
    
}

#elif(CONFIG_METER_AREA_MODE_SHANGHAI==CONFIG_METER_AREA_MODE)
void RestoreModePowerOn(void)
{
    ST_BALANCEDAY_POWERON_BUFFER_PARAM stBanlancePower[CON_HISTORY_POWER_COUNT_MAX+1];
    UN_BALANCEDAY_TYPE_PARAM ucBanlanceDayBuffer[CON_BALANCE_DAY_NUM_MAX+1];
    // uchar ucBanlanceEnable[CON_BALANCE_DAY_NUM_MAX];
    uchar ucBalanceDayNum,ucBalanceDayNumEveryMonth;
    uchar ucTemp,ucDay,ucHour,ucTempMove,ucTempAdd;
    uchar ucCanWhile;
    uchar ucBalanceDayPoint,ucBalanceDayCount;
    u16 uiTempData;
    ulong ulStart,ulEnd,ulTem;
    uchar ucTimeBuffer[3];
    uchar ucRestorLastSave[8];
    ucBalanceDayNum = PROGFUNCTION_COEF_BALANCE_DAY_NUM;
    if(ucBalanceDayNum>CON_BALANCE_DAY_NUM_MAX)
        ucBalanceDayNum=3;

    memset(&(ucBanlanceDayBuffer[0].ucStart), 0x00, 31*2);
    ucBalanceDayNumEveryMonth=0;
    if(0==ReadDataDirect(EPL_RESTOREPOWER_LASTTIME, sizeof(ucRestorLastSave), &Wr_data[0]))
    {
        memcpy(&ucRestorLastSave[0], &ucTimeLastSave[0], sizeof(ucRestorLastSave));
    }
    else
    {
        ucRestorLastSave[0]=0x30;   // second
        ucRestorLastSave[1]=Wr_data[0]; // minute
        ucRestorLastSave[2]=Wr_data[1]; // hour
        ucRestorLastSave[3]=0;  // week
        ucRestorLastSave[4]=Wr_data[2]; // day
        ucRestorLastSave[5]=Wr_data[3]; // month
        ucRestorLastSave[6]=Wr_data[4]; // year
    }
    // AA 下面内容重新排序抄表日以及统计总的抄表日数目  AA
    if(0!=ucBalanceDayNum)
    {
        // AA 结算日数据按照时间从大到小排序   AA
        // AA 如果是同一日的数据，则按照小时排序   AA
        // AA 如果有相同的结算日数据，则只取其中的一个   AA
        // AA 如果时间日期时间不合法，则不统计这个数据   AA
        for(ucTemp=0;ucTemp<ucBalanceDayNum;ucTemp++)
        {
            ucDay=RAM[RAM_BALANCE_DAY_01+ucTemp*2+1];
            ucHour=RAM[RAM_BALANCE_DAY_01+ucTemp*2+0];
            if(2==TestDay(ucDay)+TestHour(ucHour))
            //  AA   数据判断条件，满足条件才处理   AA
            {
                if(0 != ucBalanceDayNumEveryMonth)
                {
                    for(ucTempAdd=0;ucTempAdd<ucBalanceDayNum;ucTempAdd++)
                    {
                        uiTempData=ucDay;
                        uiTempData=(uiTempData<<8)+ucHour;
                        // AA 如果相等---> 则不需要增加----AA
                        if(uiTempData == ucBanlanceDayBuffer[ucTempAdd].uiDataCode)
                        {
                            ucTempAdd=ucBalanceDayNum;
                        }
                        else
                        {
                            // AA  数据小，则增加 AA
                            if(uiTempData > ucBanlanceDayBuffer[ucTempAdd].uiDataCode)
                            {
                                // AA   移动数据 AA
                                for(ucTempMove=(ucBalanceDayNum);ucTempMove>ucTempAdd;ucTempMove--)
                                {
                                    ucBanlanceDayBuffer[ucTempMove].uiDataCode = ucBanlanceDayBuffer[ucTempMove-1].uiDataCode;
                                }
                                // AA  添加数据 AA
                                ucBanlanceDayBuffer[ucTempAdd].uiDataCode=uiTempData;
                                
                                ucBalanceDayNumEveryMonth++;
                                ucBanlanceDayBuffer[ucBalanceDayNumEveryMonth].uiDataCode=0x0000;
                                ucTempAdd=ucBalanceDayNum; // break;
                            }
                            // AA  数据大，则跳过   AA
                            else
                            {
                                ;// no do
                            }
                        }
                    }
                }
                else
                {
                    ucBanlanceDayBuffer[0].uInChar.ucDay=ucDay;
                    ucBanlanceDayBuffer[0].uInChar.ucHour=ucHour;
                    ucBalanceDayNumEveryMonth++;
                }
            }
        }
    }

    
    ucCanWhile=GAL_NO;
    if(ucBalanceDayNumEveryMonth>0)
    {
        ucCanWhile=GAL_YES;
    }
    // AA  停电时间读取正确  AA
//  if(0==ReadDataDirect(EPL_SOFT_SECOND, 7, &ucRestorLastSave[0]))
//  {
//      ucCanWhile=GAL_NO;
//  }
    // AA  停电时间数据格式正确  AA 
//  if(0==TestSecondMinuteHourDayMonthYear(&ucRestorLastSave[0], &ucRestorLastSave[4]))
//  {
//      ucCanWhile=GAL_NO;
//  }
    // AA 当前时间和停电时间差正确---当前时间应该大于停电时间   AA  
    ulEnd=RSOFT_RTC_YEAR;
    ulEnd=(ulEnd<<8) + RSOFT_RTC_MONTH;
    ulEnd=(ulEnd<<8) + RSOFT_RTC_DAY;
//  ulEnd=(ulEnd<<8) + RSOFT_RTC_HOUR;
    ulStart=ucRestorLastSave[6];    // year
    ulStart=(ulStart<<8) + ucRestorLastSave[5];// month
    ulStart=(ulStart<<8) + ucRestorLastSave[4];// day
//  ulStart=(ulStart<<8) + ucRestorLastSave[2];// hour
    if(ulEnd<ulStart)
    {
        ucCanWhile=GAL_NO;
    }
    else
    {
        if(ulEnd==ulStart)
        {
            if(RSOFT_RTC_HOUR<=ucRestorLastSave[2])
            {
                ucCanWhile=GAL_NO;
            }
        }
    }
    ucBalanceDayCount=0;
    if(GAL_YES == ucCanWhile)
    {
        ucBalanceDayPoint=CON_HISTORY_POWER_COUNT_MAX-1;
        ucTimeBuffer[0]=RSOFT_RTC_DAY;
        ucTimeBuffer[1]=RSOFT_RTC_MONTH;
        ucTimeBuffer[2]=RSOFT_RTC_YEAR;
        // AA  开始追溯最近的结算时间  AA
        // AA  追溯的长度由 CON_HISTORY_POWER_COUNT_MAX 决定，基本上为12次  AA
        // AA  追溯的结果数据保存在stBanlancePower 中，这样方便后续处理  AA
        // AA  追溯过程分成当前日，之前日等处理。  AA
        
        // AA  查找今天是否有计算数据  AA
        for(ucTemp=0;ucTemp<ucBalanceDayNumEveryMonth;ucTemp++)
        {
            ucHour=ucBanlanceDayBuffer[ucTemp].uInChar.ucHour;
            if((ucBanlanceDayBuffer[ucTemp].uInChar.ucDay==ucTimeBuffer[0])
                &&(ucHour<=RSOFT_RTC_HOUR))
            {
                // AA  增加一条记录  AA---------->Start
                if(ucBalanceDayCount<CON_HISTORY_POWER_COUNT_MAX)
                {
                    stBanlancePower[ucBalanceDayPoint].ucHour=ucHour;
                    stBanlancePower[ucBalanceDayPoint].ucDay=ucTimeBuffer[0];
                    stBanlancePower[ucBalanceDayPoint].ucMonth=ucTimeBuffer[1];
                    stBanlancePower[ucBalanceDayPoint].ucYear=ucTimeBuffer[2];
                    ucBalanceDayCount++;
                    if(ucBalanceDayPoint>0)
                    {
                        ucBalanceDayPoint--;
                    }
                }
                if(ucBalanceDayCount>=CON_HISTORY_POWER_COUNT_MAX)
                {
                    ucTemp=ucBalanceDayNumEveryMonth;
                    ucCanWhile=GAL_NO;
                }
                // AA  增加一条记录  AA---------->end
            }
        }
        while(GAL_YES==ucCanWhile)
        {
            PerDayFromPoint(&ucTimeBuffer[0]);
            ulEnd=ucTimeBuffer[2];
            ulEnd=(ulEnd<<8) + ucTimeBuffer[1];
            ulEnd=(ulEnd<<8) + ucTimeBuffer[0];
            if(ulStart<ulEnd)
            //AA 查找之前的日子是否有计算数据  AA
            {
                for(ucTemp=0;ucTemp<ucBalanceDayNumEveryMonth;ucTemp++)
                {
                    ucHour=ucBanlanceDayBuffer[ucTemp].uInChar.ucHour;
                    if((ucBanlanceDayBuffer[ucTemp].uInChar.ucDay==ucTimeBuffer[0]))
                    {
                        // AA  增加一条记录  AA---------->Start
                        if(ucBalanceDayCount<CON_HISTORY_POWER_COUNT_MAX)
                        {
                            stBanlancePower[ucBalanceDayPoint].ucHour=ucHour;
                            stBanlancePower[ucBalanceDayPoint].ucDay=ucTimeBuffer[0];
                            stBanlancePower[ucBalanceDayPoint].ucMonth=ucTimeBuffer[1];
                            stBanlancePower[ucBalanceDayPoint].ucYear=ucTimeBuffer[2];
                            ucBalanceDayCount++;
                            if(ucBalanceDayPoint>0)
                            {
                                ucBalanceDayPoint--;
                            }
                        }
                        else
                        {
                            ucTemp=ucBalanceDayNumEveryMonth;
                            ucCanWhile=GAL_NO;
                        }
                        // AA  增加一条记录  AA---------->end
                    }
                }
            }
            else
            {
                if(ulStart==ulEnd)
                // AA 超找停电日是否有计算数据 AA
                {
                    for(ucTemp=0;ucTemp<ucBalanceDayNumEveryMonth;ucTemp++)
                    {
                        ucHour=ucBanlanceDayBuffer[ucTemp].uInChar.ucHour;
                        if((ucBanlanceDayBuffer[ucTemp].uInChar.ucDay==ucTimeBuffer[0])
                            &&(ucHour > ucRestorLastSave[2]))
                        {
                            // AA  增加一条记录  AA---------->Start
                            if(ucBalanceDayCount<CON_HISTORY_POWER_COUNT_MAX)
                            {
                                stBanlancePower[ucBalanceDayPoint].ucHour=ucHour;
                                stBanlancePower[ucBalanceDayPoint].ucDay=ucTimeBuffer[0];
                                stBanlancePower[ucBalanceDayPoint].ucMonth=ucTimeBuffer[1];
                                stBanlancePower[ucBalanceDayPoint].ucYear=ucTimeBuffer[2];
                                ucBalanceDayCount++;
                                if(ucBalanceDayPoint>0)
                                {
                                    ucBalanceDayPoint--;
                                }
                            }
                            else
                            {
                                ucTemp=ucBalanceDayNumEveryMonth;
                                ucCanWhile=GAL_NO;
                            }
                            // AA  增加一条记录  AA---------->end
                        }
                    }
                }
                else
                {
                    ucCanWhile=GAL_NO;
                }
            }
        }

    }
    
    if(ucBalanceDayCount>0)
    {
        // AA  发现需要结算数据  AA
        // AA 开始转存数据AA
        ucBalanceDayPoint=CON_HISTORY_POWER_COUNT_MAX-1;
        for(ucTemp=0;ucTemp<ucBalanceDayCount;ucTemp++)
        {
            if(ucBalanceDayPoint>=CON_HISTORY_POWER_COUNT_MAX)
            // AA 防止异常错误 AA
            {
                ucBalanceDayPoint=CON_HISTORY_POWER_COUNT_MAX-1;
            }
            
            // AA 结算需量数据 AA
            memcpy(&Wr_data[1], &stBanlancePower[ucBalanceDayPoint].ucHour, 4);
            Wr_data[0]=0x00;
            RestoreDemand(&Wr_data[0]);
            if(0==ucTemp)
            {
                // AA 只有在第一次的时候，才清除当前需量 AA
                DemandDataClrAllCurrent();
            }
            // AA 结算电量数据 AA
            memcpy(&Wr_data[1], &stBanlancePower[ucBalanceDayPoint].ucHour, 4);
            Wr_data[0]=0x00;
            RestorePower(&Wr_data[0]);
            // AA 结算用电量数据 AA         
            memcpy(&Wr_data[1], &stBanlancePower[ucBalanceDayPoint].ucHour, 4);
            Wr_data[0]=0x00;
            RestorePowerUse(&Wr_data[0]);
            ucBalanceDayPoint--;
        }
        ucBalanceDayPoint=CON_HISTORY_POWER_COUNT_MAX-1;
        memcpy(&Wr_data[1], &stBanlancePower[ucBalanceDayPoint].ucHour, 4);
        Wr_data[0]=0x00;
        WriteDataDirect(&Wr_data[0], EPL_RESTOREDEMAND_LASTTIME, 5);
        WriteDataDirect(&Wr_data[0], EPL_RESTOREPOWER_LASTTIME, 5);
        WriteDataDirect(&Wr_data[0], EPL_RESTOREPOWERUSE_LASTTIME, 5);      
    }

// 电压监控数据的补结算
    if(0==ReadDataDirect(EPL_RESTOREMONITER_LASTTIME, sizeof(ucRestorLastSave), &Wr_data[0]))
    {
        memcpy(&ucRestorLastSave[0], &ucTimeLastSave[0], sizeof(ucRestorLastSave));
    }
    else
    {
        ucRestorLastSave[0]=0x30;   // second
        ucRestorLastSave[1]=Wr_data[0]; // minute
        ucRestorLastSave[2]=Wr_data[1]; // hour
        ucRestorLastSave[3]=0;  // week
        ucRestorLastSave[4]=Wr_data[2]; // day
        ucRestorLastSave[5]=Wr_data[3]; // month
        ucRestorLastSave[6]=Wr_data[4]; // year
    }
    ulEnd=ValueHexFromBcd(RSOFT_RTC_YEAR);
    ulEnd=ulEnd*12 + ValueHexFromBcd(RSOFT_RTC_MONTH);
    ulStart=ValueHexFromBcd(ucRestorLastSave[6]);
    ulStart=ulStart*12 + ValueHexFromBcd(ucRestorLastSave[5]);
    
    if(ulStart<ulEnd)
    {
        ulTem=ulEnd-ulStart;
        if(ulTem>=CON_HISTORY_MONITER_COUNT_MAX)
        {
            ulStart=ulEnd-CON_HISTORY_MONITER_COUNT_MAX;
        }
        for(ucTemp=0;ucTemp<CON_HISTORY_MONITER_COUNT_MAX;ucTemp++)
        {
            ulStart++;
            if(ulStart>ulEnd)
            {
                ucTemp=CON_HISTORY_MONITER_COUNT_MAX;
            }
            else
            {
                Wr_data[0]=0x00;
                Wr_data[1]=0x00;
                Wr_data[2]=0x01;
                Wr_data[3]=ValueBcdFromHex(ulStart%12);
                if(0==Wr_data[3])
                {
                    Wr_data[3]=0x12;
                    // AA 前面ulStart 已经增加过了，保证是一个大于0 的数字 AA AA
                    Wr_data[4]=ValueBcdFromHex((ulStart-1)/12);
                }
                else
                {
                    Wr_data[4]=ValueBcdFromHex(ulStart/12);
                }
                RestoreMoniter(&Wr_data[0]);
                if(0==ucTemp)
                {
                    RestoreMoniterClr();
                }
                
            }
        }
        
    }
    
}


#endif





