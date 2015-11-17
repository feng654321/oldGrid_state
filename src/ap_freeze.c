#define AP_FREEZE_GLOBALS
#include "common.h"
uchar FreezeKwhRecord(ulong ulDataAddr);
uchar FreezeCanFreezeHourData(void);


uchar ucFreezeModeSwitch;

void FreezeInit(void)
{
    ucFreezeModeSwitch=0;

    FlgFreezeSeasonChange=GAL_NO;
    FlgFreezeDayTableChange=GAL_NO;
    FlgFreezeStepPriceTableChange=GAL_NO;
    FlgFreezePeriodPriceTableChange=GAL_NO;
    
    FlgFreezeInstant=GAL_NO;
    FlgFreezeEveryTime=GAL_NO;
    FlgFreezeEveryDayZeroTime=GAL_NO;
    
    FlgFreezeFactoryEveryHour=GAL_NO;
    FlgFreezeFactoryEveryDay=GAL_NO;
    FlgFreezeEveryHalfHour=GAL_NO;
}

void FreezeDataWrite(ulong ulDataAddr)
{
#if 0   
    SetmmhhDDMMYYToPoint(&Wr_data[0]);
	memcpy(&Wr_data[5],&RAM[RAM_KWH_F_ALL+0],(512-5));
	WriteDataDirect(&Wr_data[0], ulDataAddr, 512);
    
	memcpy(&Wr_data[0],&RAM[RAM_KWH_F_ALL+512-5],(600-512+5));
	memcpy(&Wr_data[600-512+5],&RAM[RAM_DEMAND_DATA_START+0],270);
	memcpy(&Wr_data[600-512+5+270+0],&RAM[RAM_CURRENT_KW_ALL+1],3);
	memcpy(&Wr_data[600-512+5+270+3],&RAM[RAM_CURRENT_KW_A+1],3);
	memcpy(&Wr_data[600-512+5+270+6],&RAM[RAM_CURRENT_KW_B+1],3);
	memcpy(&Wr_data[600-512+5+270+9],&RAM[RAM_CURRENT_KW_C+1],3);
	memcpy(&Wr_data[600-512+5+270+12],&RAM[RAM_CURRENT_KVAR_ALL+1],3);
	memcpy(&Wr_data[600-512+5+270+15],&RAM[RAM_CURRENT_KVAR_A+1],3);
	memcpy(&Wr_data[600-512+5+270+18],&RAM[RAM_CURRENT_KVAR_B+1],3);
	memcpy(&Wr_data[600-512+5+270+21],&RAM[RAM_CURRENT_KVAR_C+1],3);
	WriteDataDirect(&Wr_data[0], ulDataAddr+512, 600-512+5+270+24);
#else
    SetmmhhDDMMYYToPoint(&Wr_data[0]);
	WriteDataDirect(&Wr_data[0], ulDataAddr, BYTES_FREEZE_TIME_TOTAL);
    ulDataAddr += BYTES_FREEZE_TIME_TOTAL;
    CpyDataDirrect(ulDataAddr, RAM_KWH_F_ALL, BYTES_FREEZE_KWH_TOTAL);
    ulDataAddr += BYTES_FREEZE_KWH_TOTAL;
    CpyDataDirrect(ulDataAddr, RAM_DEMAND_DATA_START, BYTES_FREEZE_DEMAND_TOTAL);
    ulDataAddr += BYTES_FREEZE_DEMAND_TOTAL;
    
	memcpy(&Wr_data[0],&RAM[RAM_CURRENT_KW_ALL+1],3);
	memcpy(&Wr_data[3],&RAM[RAM_CURRENT_KW_A+1],3);
	memcpy(&Wr_data[6],&RAM[RAM_CURRENT_KW_B+1],3);
	memcpy(&Wr_data[9],&RAM[RAM_CURRENT_KW_C+1],3);
	memcpy(&Wr_data[12],&RAM[RAM_CURRENT_KVAR_ALL+1],3);
	memcpy(&Wr_data[15],&RAM[RAM_CURRENT_KVAR_A+1],3);
	memcpy(&Wr_data[18],&RAM[RAM_CURRENT_KVAR_B+1],3);
	memcpy(&Wr_data[21],&RAM[RAM_CURRENT_KVAR_C+1],3);
	WriteDataDirect(&Wr_data[0], ulDataAddr, 24);

#endif
}
uchar FreezeKwhRecord(ulong ulDataAddr)
{
    uchar *ucpDataPoint;
    ucpDataPoint=&RAM[RAM_KWH_ALL_START+0];
    WriteDataDirect(ucpDataPoint, ulDataAddr, PT_KWH_TOTAL*BYTES_PER_PT_KWH);
    return 1;
}


uchar  FreezeRecord(uchar ucTypeName)
{
    ulong ulDataAddr;
    
    ulDataAddr=SetTwoTableNextPoint(ucTypeName);
    if(GAL_GETTWOTABLE_ADDRERR == ulDataAddr)
    {
        return 0;
    }
    FreezeDataWrite(ulDataAddr);
    ClrFlashMode();
    return 1;
    
}

uchar FreezeHalfHourRecord(void);
uchar FreezeHalfHourRecord(void)
{
    ulong ulDataAddr;
    ulDataAddr=SetTwoTableNextPoint(TYPE_FREEZE_HOURTIME_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR==ulDataAddr)
    {
        return 0;
    }
    else
    {
        SetmmhhDDMMYYToPoint(&Wr_data[0]);
        memcpy(&Wr_data[5], &RAM[RAM_KWH_F_ALL+0], 5);
        memcpy(&Wr_data[10], &RAM[RAM_KWH_R_ALL+0], 5);
        WriteDataDirect(&Wr_data[0], ulDataAddr,15);
    }
    ClrFlashMode();
    return 1;
}
uchar FreezeCanFreezeHourData(void)
{
    ulong ulNowtime;
    uchar ucTemp;
    if(ulNowMinTime>=mmHHDDMMYYToLong(&RAM[RAM_CHARACTER_FREEZE_EVERYHOUR_STARTTIME+0]))
    {
        ulNowtime=ValueHexFromBcd(RSOFT_RTC_HOUR);
        ulNowtime=ulNowtime*60+ValueHexFromBcd(RSOFT_RTC_MINUTE);
        ucTemp=ValueHexFromBcd(RAM[ RAM_CHARACTER_FREEZE_EVERYHOUR_INTERVAL]);
        if(0==ucTemp)
        {
            ucTemp=60;
        }
        if(1!=TestBcd(RAM[ RAM_CHARACTER_FREEZE_EVERYHOUR_INTERVAL]))
        {
            ucTemp=60;
        }
        if(0==(ulNowtime%ucTemp))
        {
            return 1;
        }
    }
    return 0;
}

uchar ucFreezeModeMinute;


uchar FreezeMode(void)
{
    if(ucFreezeModeMinute !=RSOFT_RTC_MINUTE)
    {
        ucFreezeModeMinute =RSOFT_RTC_MINUTE;
// AA  ----立即冻结---->Start----  AA       
        if((RAM[RAM_COEF_FREEZE_TIME+3]==RSOFT_RTC_MONTH)||(0x99==RAM[RAM_COEF_FREEZE_TIME+3]))
        {
            if((RAM[RAM_COEF_FREEZE_TIME+2]==RSOFT_RTC_DAY)||(0x99==RAM[RAM_COEF_FREEZE_TIME+2]))
            {
                if((RAM[RAM_COEF_FREEZE_TIME+1]==RSOFT_RTC_HOUR)||(0x99==RAM[RAM_COEF_FREEZE_TIME+1]))
                {
                    if(RAM[RAM_COEF_FREEZE_TIME+0]==RSOFT_RTC_MINUTE)
                    {
                        if(1==TimeChangedmmhhDDMMYYFromAddr(EPL_FREEZE_EVERYTIME_LASTTIME))
                        {
                            FlgFreezeEveryTime=GAL_YES;
                        }
                    }
                }
            }
        }
// AA  ----立即冻结---->End----  AA     
// AA  ----整点冻结(冻结时分可设置)---->Start----  AA       
//      if(0==RSOFT_RTC_MINUTE)
        {
            if(1==FreezeCanFreezeHourData())
            {
                if(1==TimeChangedmmhhDDMMYYFromAddr(EPL_FREEZE_EVERYHOUR_LASTTIME))
                {
                    FlgFreezeEveryHalfHour=GAL_YES;
                }
            }
        }
// AA  ----整点冻结(冻结时分可设置)---->End----  AA       

// AA  ----日零点冻结(冻结时分可设置)---->Start----  AA       
        if(RAM[RAM_CHARACTER_FREEZE_EVERYDAY_TIME+0]==RSOFT_RTC_MINUTE)
        {
            if(RAM[RAM_CHARACTER_FREEZE_EVERYDAY_TIME+1]==RSOFT_RTC_HOUR)
            {
                if(1==TimeChangedmmhhDDMMYYFromAddr(EPL_FREEZE_EVERYDAY_LASTTIME))
                {
                    FlgFreezeEveryDayZeroTime=GAL_YES;
                }
            }
        }
// AA  ----日零点冻结(冻结时分可设置)---->End----  AA       
// AA  ----程序自动冻结数据---->Start----  AA       
#if 0
        // 25的flash需要删除操作，目前没加。所以加了没意义
        if(0==RSOFT_RTC_MINUTE)
        {
            FlgFreezeFactoryEveryHour=GAL_YES;
            if(0==RSOFT_RTC_HOUR)
            {
                FlgFreezeFactoryEveryDay=GAL_YES;
            }
        }
#endif        
// AA  ----程序自动冻结数据---->Start----  AA       
    }
    if(isFlashBusy)
    {
        return DLT_RET_UNFINISHED;
    }
    else
    {
        switch(ucFreezeModeSwitch)

        {
            case 1:
                if(GAL_YES==FlgFreezeSeasonChange)     // 时区表改变
                {
                    FlgFreezeSeasonChange=GAL_NO;
                    FreezeRecord(TYPE_FREEZE_SEASONCHANGE_RECORD);
                    break;
                }
                else
                {
                    ucFreezeModeSwitch++;
                }
            case 2:
                if(GAL_YES==FlgFreezeDayTableChange)   //时段表
                {
                    FlgFreezeDayTableChange=GAL_NO;
                    FreezeRecord(TYPE_FREEZE_DAYTABLECHANGE_RECORD);
                    break;
                }
                else
                {
                    ucFreezeModeSwitch++;
                }
            case 3:
                 if(GAL_YES==FlgFreezeInstant)          // 瞬时
                 {
                    FlgFreezeInstant=GAL_NO;
                    FreezeRecord(TYPE_FREEZE_INSTANT_RECORD);
                    break;
                }
                else
                {
                    ucFreezeModeSwitch++;
                }
            case 4:
                 if(GAL_YES==FlgFreezeEveryTime)        // 定时
                 {
                    FlgFreezeEveryTime=GAL_NO;
                    FreezeRecord(TYPE_FREEZE_EVERYTIME_RECORD);
                    SavemmhhDDMMYYtoAddr(EPL_FREEZE_EVERYTIME_LASTTIME);
                    break;
                }
                else
                {
                    ucFreezeModeSwitch++;
                }
            case 5:
                 if(GAL_YES==FlgFreezeFactoryEveryHour) //上1小时的电量数据保存
                 {
                    FlgFreezeFactoryEveryHour=GAL_NO;
                    FreezeKwhRecord(FL1_LAST_PER_HOUR_POWER);
                    break;
                }
                else
                {
                    ucFreezeModeSwitch++;
                }
            case 6:
                 if(GAL_YES==FlgFreezeFactoryEveryDay)  // 上1天的电量数据保存
                 {
                    FlgFreezeFactoryEveryDay=GAL_NO;
                    FreezeKwhRecord(FL1_LAST_PER_DAY_POWER);
                    break;
                }
                else
                {
                    ucFreezeModeSwitch++;
                }
            case 7:
                if(GAL_YES == FlgFreezeStepPriceTableChange)
                {
                    FlgFreezeStepPriceTableChange=GAL_NO;
                    FreezeRecord(TYPE_FREEZE_STEPPRICE_TABLECHANGE_RECORD);
                    break;
                }
                else
                {
                    ucFreezeModeSwitch++;
                }
            case 8:
                if(GAL_YES == FlgFreezePeriodPriceTableChange)
                {
                    FlgFreezePeriodPriceTableChange=GAL_NO;
                    FreezeRecord(TYPE_FREEZE_PERIODPRICE_TABLECHANGE_RECORD);
                    break;
                }
                else
                {
                    ucFreezeModeSwitch++;
                }
            case 9:
                if(GAL_YES == FlgFreezeEveryDayZeroTime)        // 日零点冻结
                {
                    FlgFreezeEveryDayZeroTime=GAL_NO;
                    FreezeRecord(TYPE_FREEZE_EVERYZERO_RECORD);
                    SavemmhhDDMMYYtoAddr(EPL_FREEZE_EVERYDAY_LASTTIME);
                    break;
                }
                else
                {
                    ucFreezeModeSwitch++;
                }
            case 10:
                if(GAL_YES == FlgFreezeEveryHalfHour)   // 整点半点电量冻结
                {
                    FlgFreezeEveryHalfHour=GAL_NO;
                    FreezeHalfHourRecord();
                    SavemmhhDDMMYYtoAddr(EPL_FREEZE_EVERYHOUR_LASTTIME);
                }
            default:
                ucFreezeModeSwitch=1;
                return DLT_RET_SUCC;
                //break;
        }
        ucFreezeModeSwitch++;
        return DLT_RET_UNFINISHED;
    }
    //return DLT_RET_SUCC;
}






















