#define AP_RESTORE_GLOBALS
#include "common.h"

#if(CONFIG_METER_AREA_MODE_SOUTHGRID==CONFIG_METER_AREA_MODE)
#define CON_HISTORY_POWER_COUNT_MAX     1   // ��ಹ1��
#define CON_HISTORY_POWERUSE_COUNT_MAX  1
#define CON_HISTORY_DEMAND_COUNT_MAX    1
#define CON_HISTORY_MONITER_COUNT_MAX   1
#elif (CONFIG_METER_AREA_MODE_SHANGHAI==CONFIG_METER_AREA_MODE)
#define CON_HISTORY_POWER_COUNT_MAX     12  // ��ಹ12��
#define CON_HISTORY_POWERUSE_COUNT_MAX  12
#define CON_HISTORY_DEMAND_COUNT_MAX    12
#define CON_HISTORY_MONITER_COUNT_MAX   12
#endif 
#define CON_BALANCE_DAY_NUM_MAX         31
#define CON_HISTORY_MONITER_LENGTH      27
/*********************************************************************
���ܣ�  ���ļ�������ת�湦��
��Χ��  Ӧ�ò�ֱ�ӵ���
ע�ͣ�  ��
���ߣ�  ����
�汾��  V1.0
����޸�ʱ�䣺2009-01-19
�޸�˵��������
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
//ZD �ڼ�������ר���У��޴˹���
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
        // AA --����ǵ�һ����������ת����������������ת��FF--AA
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
        // AA--��ֹ��������ո���һ����������ͬ����������ת�����--AA
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
    
    if(isFlashBusy)       // Flash ��æ���ݲ��洢
        return DLT_RET_UNFINISHED;

    if((GAL_YES==ucRestoreRequestPower))
    {
        ucRestoreRequestPower=GAL_NO;
        SetmmhhDDMMYYToPoint(&Wr_data[0]);
        RestorePower(&Wr_data[0]);
    }
    
    if(isFlashBusy)       // Flash ��æ���ݲ��洢
        return DLT_RET_UNFINISHED;
    
    if((GAL_YES==ucRestoreRequestPowerUse))
    {
        ucRestoreRequestPowerUse=GAL_NO;
        SetmmhhDDMMYYToPoint(&Wr_data[0]);
        RestorePowerUse(&Wr_data[0]);
    }
    
    if(isFlashBusy)       // Flash ��æ���ݲ��洢
        return DLT_RET_UNFINISHED;
    
    if((GAL_YES==ucRestoreRequestDemand))
    {
        ucRestoreRequestDemand=GAL_NO;
        SetmmhhDDMMYYToPoint(&Wr_data[0]);
        RestoreDemand(&Wr_data[0]);
        DemandDataClrAllCurrent();
    }
    
    if(isFlashBusy)       // Flash ��æ���ݲ��洢
        return DLT_RET_UNFINISHED;
    
    if((GAL_YES==ucRestoreRequestDemand0xff))
    {
        ucRestoreRequestDemand0xff=GAL_NO;
        SetmmhhDDMMYYToPoint(&Wr_data[0]);
        RestoreDemand0xFF(&Wr_data[0]);
        // RestoreDemandClr();
    }
    
    if(isFlashBusy)       // Flash ��æ���ݲ��洢
        return DLT_RET_UNFINISHED;
    
    if((GAL_YES==ucRestoreRequestMoniter))
    {
        ucRestoreRequestMoniter=GAL_NO;
        SetmmhhDDMMYYToPoint(&Wr_data[0]);
        RestoreMoniter(&Wr_data[0]);
        RestoreMoniterClr();
    }
    
    if(isFlashBusy)       // Flash ��æ���ݲ��洢
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
    UN_BALANCEDAY_TYPE_PARAM ucBanlanceDayBuffer[CON_BALANCE_DAY_NUM_MAX+1];            // ��ÿ�µļ��������մ�С��������
    // uchar ucBanlanceEnable[CON_BALANCE_DAY_NUM_MAX];
    uchar ucBalanceDayNum,ucBalanceDayNumEveryMonth;//ucBalanceDayNumEveryMonthΪÿ�½�������
    uchar ucTemp,ucDay,ucHour,ucTempMove,ucTempAdd;
    uchar ucCanWhile;
    uchar ucBalanceDayPoint,ucBalanceDayCount;//ucBalanceDayCountΪ���ĵ���
    u16 uiTempData;
    ulong ulStart,ulEnd,ulTem;
    uchar ucTimeBuffer[3];
    ucBalanceDayNum = PROGFUNCTION_COEF_BALANCE_DAY_NUM;
    if(ucBalanceDayNum>CON_BALANCE_DAY_NUM_MAX)
        ucBalanceDayNum=3;

    memset(&(ucBanlanceDayBuffer[0].ucStart), 0x00, 31*2);
    ucBalanceDayNumEveryMonth=0;


    // AA ���������������򳭱����Լ�ͳ���ܵĳ�������Ŀ  AA
    if(0!=ucBalanceDayNum)
    {
        // AA ���������ݰ���ʱ��Ӵ�С����   AA
        // AA �����ͬһ�յ����ݣ�����Сʱ����   AA
        // AA �������ͬ�Ľ��������ݣ���ֻȡ���е�һ��   AA
        // AA ���ʱ������ʱ�䲻�Ϸ�����ͳ���������   AA
        for(ucTemp=0;ucTemp<ucBalanceDayNum;ucTemp++)
        {
            ucDay=RAM[RAM_BALANCE_DAY_01+ucTemp*2+1];
            ucHour=RAM[RAM_BALANCE_DAY_01+ucTemp*2+0];
            if(2==TestDay(ucDay)+TestHour(ucHour))
            //  AA   �����ж����������������Ŵ���   AA
            {
                if(0 != ucBalanceDayNumEveryMonth)
                {
                    for(ucTempAdd=0;ucTempAdd<ucBalanceDayNum;ucTempAdd++)
                    {
                        uiTempData=ucDay;
                        uiTempData=(uiTempData<<8)+ucHour;
                        // AA ������---> ����Ҫ����----AA
                        if(uiTempData == ucBanlanceDayBuffer[ucTempAdd].uiDataCode)
                        {
                            ucTempAdd=ucBalanceDayNum;
                        }
                        else
                        {
                            // AA  ����С�������� AA
                            if(uiTempData > ucBanlanceDayBuffer[ucTempAdd].uiDataCode)
                            {
                                // AA   �ƶ����� AA
                                for(ucTempMove=(ucBalanceDayNum);ucTempMove>ucTempAdd;ucTempMove--)
                                {
                                    ucBanlanceDayBuffer[ucTempMove].uiDataCode = ucBanlanceDayBuffer[ucTempMove-1].uiDataCode;
                                }
                                // AA  ������� AA
                                ucBanlanceDayBuffer[ucTempAdd].uiDataCode=uiTempData;
                                
                                ucBalanceDayNumEveryMonth++;
                                ucBanlanceDayBuffer[ucBalanceDayNumEveryMonth].uiDataCode=0x0000;
                                ucTempAdd=ucBalanceDayNum; // break;
                            }
                            // AA  ���ݴ�������   AA
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
    // ���ÿ�µĽ�������Ϊ0�����ϵ粻������
    ucCanWhile=GAL_NO;
    if(ucBalanceDayNumEveryMonth>0)
    {
        ucCanWhile=GAL_YES;
    }

    // AA ��ǰʱ���ͣ��ʱ�����ȷ---��ǰʱ��Ӧ�ô���ͣ��ʱ��   AA  
    ulEnd=RSOFT_RTC_YEAR;
    ulEnd=(ulEnd<<8) + RSOFT_RTC_MONTH;
    ulEnd=(ulEnd<<8) + RSOFT_RTC_DAY;
    ulStart=ucTimeLastSave[6];  // year
    ulStart=(ulStart<<8) + ucTimeLastSave[5];// month
    ulStart=(ulStart<<8) + ucTimeLastSave[4];// day
    // �����ǰʱ����ϴε���ʱ��󣬼��㲹�������Ŀ
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
        // AA  ��ʼ׷������Ľ���ʱ��  AA
        // AA  ׷�ݵĳ����� CON_HISTORY_POWER_COUNT_MAX ������������Ϊ12��  AA
        // AA  ׷�ݵĽ�����ݱ�����stBanlancePower �У����������������  AA
        // AA  ׷�ݹ��̷ֳɵ�ǰ�գ�֮ǰ�յȴ���  AA
        
        // AA  ���ҽ����Ƿ��м�������  AA
        for(ucTemp=0;ucTemp<ucBalanceDayNumEveryMonth;ucTemp++)
        {
            ucHour=ucBanlanceDayBuffer[ucTemp].uInChar.ucHour;
            if((ucBanlanceDayBuffer[ucTemp].uInChar.ucDay==ucTimeBuffer[0])
                &&(ucHour<=RSOFT_RTC_HOUR))
            {
                // AA  ����һ����¼  AA---------->Start
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
                // AA  ����һ����¼  AA---------->end
            }
        }
        // ����������ǰ�Ľ����գ�ͳ�Ʋ�����
        while(GAL_YES==ucCanWhile)
        {
            PerDayFromPoint(&ucTimeBuffer[0]);
            ulEnd=ucTimeBuffer[2];
            ulEnd=(ulEnd<<8) + ucTimeBuffer[1];
            ulEnd=(ulEnd<<8) + ucTimeBuffer[0];
            if(ulStart<ulEnd)
            //AA ����֮ǰ�������Ƿ��м�������  AA
            {
                for(ucTemp=0;ucTemp<ucBalanceDayNumEveryMonth;ucTemp++)
                {
                    ucHour=ucBanlanceDayBuffer[ucTemp].uInChar.ucHour;
                    if((ucBanlanceDayBuffer[ucTemp].uInChar.ucDay==ucTimeBuffer[0]))
                    {
                        // AA  ����һ����¼  AA---------->Start
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
                        // AA  ����һ����¼  AA---------->end
                    }
                }
            }
            else
            {
                if(ulStart==ulEnd)
                // AA ����ͣ�����Ƿ��м������� AA
                {
                    for(ucTemp=0;ucTemp<ucBalanceDayNumEveryMonth;ucTemp++)
                    {
                        ucHour=ucBanlanceDayBuffer[ucTemp].uInChar.ucHour;
                        if((ucBanlanceDayBuffer[ucTemp].uInChar.ucDay==ucTimeBuffer[0])
                            &&(ucHour > ucTimeLastSave[2]))
                        {
                            // AA  ����һ����¼  AA---------->Start
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
                            // AA  ����һ����¼  AA---------->end
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
        // AA  ������Ҫ��������  AA
        // AA ��ʼת������AA
        ucBalanceDayPoint=CON_HISTORY_POWER_COUNT_MAX-1;
        for(ucTemp=0;ucTemp<ucBalanceDayCount;ucTemp++)
        {
            if(ucBalanceDayPoint>=CON_HISTORY_POWER_COUNT_MAX)
            // AA ��ֹ�쳣���� AA
            {
                ucBalanceDayPoint=CON_HISTORY_POWER_COUNT_MAX-1;
            }
            
            // AA ������������ AA
            memcpy(&Wr_data[1], &stBanlancePower[ucBalanceDayPoint].ucHour, 4);
            Wr_data[0]=0x00;
            RestoreDemand(&Wr_data[0]);
            if(0==ucTemp)
            {
                // AA ֻ���ڵ�һ�ε�ʱ�򣬲������ǰ���� AA
                DemandDataClrAllCurrent();
            }
            // AA ����������� AA
            memcpy(&Wr_data[1], &stBanlancePower[ucBalanceDayPoint].ucHour, 4);
            Wr_data[0]=0x00;
            RestorePower(&Wr_data[0]);
            // AA �����õ������� AA         
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

    // AA ���������������򳭱����Լ�ͳ���ܵĳ�������Ŀ  AA
    if(0!=ucBalanceDayNum)
    {
        // AA ���������ݰ���ʱ��Ӵ�С����   AA
        // AA �����ͬһ�յ����ݣ�����Сʱ����   AA
        // AA �������ͬ�Ľ��������ݣ���ֻȡ���е�һ��   AA
        // AA ���ʱ������ʱ�䲻�Ϸ�����ͳ���������   AA
        for(ucTemp=0;ucTemp<ucBalanceDayNum;ucTemp++)
        {
            ucDay=RAM[RAM_BALANCE_DAY_01+ucTemp*2+1];
            ucHour=RAM[RAM_BALANCE_DAY_01+ucTemp*2+0];
            // AA  �ر���,����ֻ��Ϊ1�Ų���  AA
            if(2==TestDay(ucDay)+TestHour(ucHour))
            //  AA   �����ж����������������Ŵ���   AA
            {
                if(0 != ucBalanceDayNumEveryMonth)
                {
                    for(ucTempAdd=0;ucTempAdd<ucBalanceDayNum;ucTempAdd++)
                    {
                        uiTempData=ucDay;
                        uiTempData=(uiTempData<<8)+ucHour;
                        // AA ������---> ����Ҫ����----AA
                        if(uiTempData == ucBanlanceDayBuffer[ucTempAdd].uiDataCode)
                        {
                            ucTempAdd=ucBalanceDayNum;
                        }
                        else
                        {
                            // AA  ����С�������� AA
                            if(uiTempData > ucBanlanceDayBuffer[ucTempAdd].uiDataCode)
                            {
                                // AA   �ƶ����� AA
                                for(ucTempMove=(ucBalanceDayNum);ucTempMove>ucTempAdd;ucTempMove--)
                                {
                                    ucBanlanceDayBuffer[ucTempMove].uiDataCode = ucBanlanceDayBuffer[ucTempMove-1].uiDataCode;
                                }
                                // AA  ������� AA
                                ucBanlanceDayBuffer[ucTempAdd].uiDataCode=uiTempData;
                                
                                ucBalanceDayNumEveryMonth++;
                                ucBanlanceDayBuffer[ucBalanceDayNumEveryMonth].uiDataCode=0x0000;
                                ucTempAdd=ucBalanceDayNum; // break;
                            }
                            // AA  ���ݴ�������   AA
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
    // AA  �ر���---->Start  AA
    if(ucBalanceDayNumEveryMonth>1)
        ucBalanceDayNumEveryMonth=1;
    // AA  �ر���---->End  AA
    ucCanWhile=GAL_NO;
    if(ucBalanceDayNumEveryMonth>0)
    {
        ucCanWhile=GAL_YES;
    }
    // AA  ͣ��ʱ���ȡ��ȷ  AA
//  if(0==ReadDataDirect(EPL_SOFT_SECOND, 7, &ucTimeLastSave[0]))
//  {
//      ucCanWhile=GAL_NO;
//  }
    // AA  ͣ��ʱ�����ݸ�ʽ��ȷ  AA 
//  if(0==TestSecondMinuteHourDayMonthYear(&ucTimeLastSave[0], &ucTimeLastSave[4]))
//  {
//      ucCanWhile=GAL_NO;
//  }
    // AA ��ǰʱ���ͣ��ʱ�����ȷ---��ǰʱ��Ӧ�ô���ͣ��ʱ��   AA  
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
        // AA  ��ʼ׷������Ľ���ʱ��  AA
        // AA  ׷�ݵĳ����� CON_HISTORY_POWER_COUNT_MAX ������������Ϊ12��  AA
        // AA  ׷�ݵĽ�����ݱ�����stBanlancePower �У����������������  AA
        // AA  ׷�ݹ��̷ֳɵ�ǰ�գ�֮ǰ�յȴ���  AA
        
        // AA  ���ҽ����Ƿ��м�������  AA
        for(ucTemp=0;ucTemp<ucBalanceDayNumEveryMonth;ucTemp++)
        {
            ucHour=ucBanlanceDayBuffer[ucTemp].uInChar.ucHour;
            if((ucBanlanceDayBuffer[ucTemp].uInChar.ucDay==ucTimeBuffer[0])
                &&(ucHour<=RSOFT_RTC_HOUR))
            {
                // AA  ����һ����¼  AA---------->Start
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
                // AA  ����һ����¼  AA---------->end
            }
        }
        while(GAL_YES==ucCanWhile)
        {
            PerDayFromPoint(&ucTimeBuffer[0]);
            ulEnd=ucTimeBuffer[2];
            ulEnd=(ulEnd<<8) + ucTimeBuffer[1];
            ulEnd=(ulEnd<<8) + ucTimeBuffer[0];
            if(ulStart<ulEnd)
            //AA ����֮ǰ�������Ƿ��м�������  AA
            {
                for(ucTemp=0;ucTemp<ucBalanceDayNumEveryMonth;ucTemp++)
                {
                    ucHour=ucBanlanceDayBuffer[ucTemp].uInChar.ucHour;
                    if((ucBanlanceDayBuffer[ucTemp].uInChar.ucDay==ucTimeBuffer[0]))
                    {
                        // AA  ����һ����¼  AA---------->Start
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
                        // AA  ����һ����¼  AA---------->end
                    }
                }
            }
            else
            {
                if(ulStart==ulEnd)
                // AA ����ͣ�����Ƿ��м������� AA
                {
                    for(ucTemp=0;ucTemp<ucBalanceDayNumEveryMonth;ucTemp++)
                    {
                        ucHour=ucBanlanceDayBuffer[ucTemp].uInChar.ucHour;
                        if((ucBanlanceDayBuffer[ucTemp].uInChar.ucDay==ucTimeBuffer[0])
                            &&(ucHour > ucTimeLastSave[2]))
                        {
                            // AA  ����һ����¼  AA---------->Start
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
                            // AA  ����һ����¼  AA---------->end
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
        // AA  ������Ҫ��������  AA
        // AA ��ʼת������AA
        ucBalanceDayPoint=CON_HISTORY_POWER_COUNT_MAX-1;
        for(ucTemp=0;ucTemp<ucBalanceDayCount;ucTemp++)
        {
            if(ucBalanceDayPoint>=CON_HISTORY_POWER_COUNT_MAX)
            // AA ��ֹ�쳣���� AA
            {
                ucBalanceDayPoint=CON_HISTORY_POWER_COUNT_MAX-1;
            }
            
            // AA ������������ AA
            memcpy(&Wr_data[1], &stBanlancePower[ucBalanceDayPoint].ucHour, 4);
            Wr_data[0]=0x00;
            RestoreDemand(&Wr_data[0]);
            if(0==ucTemp)
            {
                // AA ֻ���ڵ�һ�ε�ʱ�򣬲������ǰ���� AA
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
                    // AA ǰ��ulStart �Ѿ����ӹ��ˣ���֤��һ������0 ������ AA AA
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
    // AA ���������������򳭱����Լ�ͳ���ܵĳ�������Ŀ  AA
    if(0!=ucBalanceDayNum)
    {
        // AA ���������ݰ���ʱ��Ӵ�С����   AA
        // AA �����ͬһ�յ����ݣ�����Сʱ����   AA
        // AA �������ͬ�Ľ��������ݣ���ֻȡ���е�һ��   AA
        // AA ���ʱ������ʱ�䲻�Ϸ�����ͳ���������   AA
        for(ucTemp=0;ucTemp<ucBalanceDayNum;ucTemp++)
        {
            ucDay=RAM[RAM_BALANCE_DAY_01+ucTemp*2+1];
            ucHour=RAM[RAM_BALANCE_DAY_01+ucTemp*2+0];
            if(2==TestDay(ucDay)+TestHour(ucHour))
            //  AA   �����ж����������������Ŵ���   AA
            {
                if(0 != ucBalanceDayNumEveryMonth)
                {
                    for(ucTempAdd=0;ucTempAdd<ucBalanceDayNum;ucTempAdd++)
                    {
                        uiTempData=ucDay;
                        uiTempData=(uiTempData<<8)+ucHour;
                        // AA ������---> ����Ҫ����----AA
                        if(uiTempData == ucBanlanceDayBuffer[ucTempAdd].uiDataCode)
                        {
                            ucTempAdd=ucBalanceDayNum;
                        }
                        else
                        {
                            // AA  ����С�������� AA
                            if(uiTempData > ucBanlanceDayBuffer[ucTempAdd].uiDataCode)
                            {
                                // AA   �ƶ����� AA
                                for(ucTempMove=(ucBalanceDayNum);ucTempMove>ucTempAdd;ucTempMove--)
                                {
                                    ucBanlanceDayBuffer[ucTempMove].uiDataCode = ucBanlanceDayBuffer[ucTempMove-1].uiDataCode;
                                }
                                // AA  ������� AA
                                ucBanlanceDayBuffer[ucTempAdd].uiDataCode=uiTempData;
                                
                                ucBalanceDayNumEveryMonth++;
                                ucBanlanceDayBuffer[ucBalanceDayNumEveryMonth].uiDataCode=0x0000;
                                ucTempAdd=ucBalanceDayNum; // break;
                            }
                            // AA  ���ݴ�������   AA
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
    // AA  ͣ��ʱ���ȡ��ȷ  AA
//  if(0==ReadDataDirect(EPL_SOFT_SECOND, 7, &ucRestorLastSave[0]))
//  {
//      ucCanWhile=GAL_NO;
//  }
    // AA  ͣ��ʱ�����ݸ�ʽ��ȷ  AA 
//  if(0==TestSecondMinuteHourDayMonthYear(&ucRestorLastSave[0], &ucRestorLastSave[4]))
//  {
//      ucCanWhile=GAL_NO;
//  }
    // AA ��ǰʱ���ͣ��ʱ�����ȷ---��ǰʱ��Ӧ�ô���ͣ��ʱ��   AA  
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
        // AA  ��ʼ׷������Ľ���ʱ��  AA
        // AA  ׷�ݵĳ����� CON_HISTORY_POWER_COUNT_MAX ������������Ϊ12��  AA
        // AA  ׷�ݵĽ�����ݱ�����stBanlancePower �У����������������  AA
        // AA  ׷�ݹ��̷ֳɵ�ǰ�գ�֮ǰ�յȴ���  AA
        
        // AA  ���ҽ����Ƿ��м�������  AA
        for(ucTemp=0;ucTemp<ucBalanceDayNumEveryMonth;ucTemp++)
        {
            ucHour=ucBanlanceDayBuffer[ucTemp].uInChar.ucHour;
            if((ucBanlanceDayBuffer[ucTemp].uInChar.ucDay==ucTimeBuffer[0])
                &&(ucHour<=RSOFT_RTC_HOUR))
            {
                // AA  ����һ����¼  AA---------->Start
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
                // AA  ����һ����¼  AA---------->end
            }
        }
        while(GAL_YES==ucCanWhile)
        {
            PerDayFromPoint(&ucTimeBuffer[0]);
            ulEnd=ucTimeBuffer[2];
            ulEnd=(ulEnd<<8) + ucTimeBuffer[1];
            ulEnd=(ulEnd<<8) + ucTimeBuffer[0];
            if(ulStart<ulEnd)
            //AA ����֮ǰ�������Ƿ��м�������  AA
            {
                for(ucTemp=0;ucTemp<ucBalanceDayNumEveryMonth;ucTemp++)
                {
                    ucHour=ucBanlanceDayBuffer[ucTemp].uInChar.ucHour;
                    if((ucBanlanceDayBuffer[ucTemp].uInChar.ucDay==ucTimeBuffer[0]))
                    {
                        // AA  ����һ����¼  AA---------->Start
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
                        // AA  ����һ����¼  AA---------->end
                    }
                }
            }
            else
            {
                if(ulStart==ulEnd)
                // AA ����ͣ�����Ƿ��м������� AA
                {
                    for(ucTemp=0;ucTemp<ucBalanceDayNumEveryMonth;ucTemp++)
                    {
                        ucHour=ucBanlanceDayBuffer[ucTemp].uInChar.ucHour;
                        if((ucBanlanceDayBuffer[ucTemp].uInChar.ucDay==ucTimeBuffer[0])
                            &&(ucHour > ucRestorLastSave[2]))
                        {
                            // AA  ����һ����¼  AA---------->Start
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
                            // AA  ����һ����¼  AA---------->end
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
        // AA  ������Ҫ��������  AA
        // AA ��ʼת������AA
        ucBalanceDayPoint=CON_HISTORY_POWER_COUNT_MAX-1;
        for(ucTemp=0;ucTemp<ucBalanceDayCount;ucTemp++)
        {
            if(ucBalanceDayPoint>=CON_HISTORY_POWER_COUNT_MAX)
            // AA ��ֹ�쳣���� AA
            {
                ucBalanceDayPoint=CON_HISTORY_POWER_COUNT_MAX-1;
            }
            
            // AA ������������ AA
            memcpy(&Wr_data[1], &stBanlancePower[ucBalanceDayPoint].ucHour, 4);
            Wr_data[0]=0x00;
            RestoreDemand(&Wr_data[0]);
            if(0==ucTemp)
            {
                // AA ֻ���ڵ�һ�ε�ʱ�򣬲������ǰ���� AA
                DemandDataClrAllCurrent();
            }
            // AA ����������� AA
            memcpy(&Wr_data[1], &stBanlancePower[ucBalanceDayPoint].ucHour, 4);
            Wr_data[0]=0x00;
            RestorePower(&Wr_data[0]);
            // AA �����õ������� AA         
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

// ��ѹ������ݵĲ�����
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
                    // AA ǰ��ulStart �Ѿ����ӹ��ˣ���֤��һ������0 ������ AA AA
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





