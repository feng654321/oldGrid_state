#define AP_PRICESWITCH_GLOBALS
#include "common.h"

//AA --切换时间更换时，相同时间是否继续切换  -- AA
#define CON_PRICESWITCH_SAMETIME_RESTORE_MODE GAL_YES

void PublicHolidayDataInit(void);
#if(CONFIG_METER_STEP_MODE==CONFIG_METER_STEP_MODE_ENABLE)
uchar NumofStepPriceChange(uchar*point);
uchar NumofPeriodPriceChange(uchar*point);
ulong GetPeriodPriceNumFromPeriodNum(uchar feeNo);
uchar GetStepNumFromUseEnergy(void);
ulong GetStepPriceFromStepNum(uchar stepNo);
#endif
uchar ucPriceSwitchModeMinute;
uchar ucPriceSwitchMOdeDay;
u16 uiLastDayPieceAddr;
// AA --年时区数的最大值--AA
uchar ucPriceSwitchSeasonTableMax;  // max =14
// AA --日时段表数的最大值--AA
uchar ucPriceSwitchDayTableMax;     // max =8
// AA --日时段数的最大值--AA
uchar ucPriceSwitchPeriodMax;       // max =14
// AA --费率数最大值--AA
uchar ucPriceSwitchPriceMax;            // max =14
// AA --公共节假日数的最大值--AA
uchar ucPriceSwitchHolidayMax;      // max =254
// AA --阶梯数最大值--AA
uchar ucPriceSwitchStepMax;         // max=14

// AA --下一2套时区表切换时间--AA
ulong ulNext2SeasonTableSwitchTime;
// AA --下一2套日时段表切换时间--AA
ulong ulNext2DayTableTableSwitchTime;
#if(CONFIG_METER_STEP_PERIODPRICE_MODE==CONFIG_METER_STEP_PERIODPRICE_MODE_ENABLE)
// AA --下一2套阶梯表切换时间--AA
ulong ulNext2StepTableSwitchTime;
// AA --下一2套费率表切换时间--AA
ulong ulNext2PriceTableSwitchTime;
#endif
// AA --下一日时段表切换时间--AA
//ulong ulNextDayTableSwitchTime; //不需要了，每天零点零分算一次就行
// AA --下一日时段切换时间--AA
//ulong ulNextDayPieceSwitchTime;  //暂时还没用上，暂时采用每分钟刷时段



void GetPriceSwitchTableMax(void);

void GetPriceSwitchTableMax(void)
{
// AA --年时区数的最大值--AA
    ucPriceSwitchSeasonTableMax=ValueHexFromBcd(RAM[RAM_COEF_SEASONTABLE_MAX_NUM]);
    if(ucPriceSwitchSeasonTableMax>CON_SEASONTABLELEN_MAX)
    {
        ucPriceSwitchSeasonTableMax=CON_SEASONTABLELEN_MAX;
    }
    if(0==ucPriceSwitchSeasonTableMax)
    {
        ucPriceSwitchSeasonTableMax=1;
    }
// AA --日时段表数的最大值--AA  
    ucPriceSwitchDayTableMax=ValueHexFromBcd(RAM[RAM_COEF_DAYTABLE_MAX_NUM]);
    if(ucPriceSwitchDayTableMax>CON_DAYTABLE_MAX)
    {
        ucPriceSwitchDayTableMax=CON_DAYTABLE_MAX;
    }
    if(0==ucPriceSwitchDayTableMax)
    {
        ucPriceSwitchDayTableMax=1;
    }
// AA --日时段数的最大值--AA
    ucPriceSwitchPeriodMax=ValueHexFromBcd(RAM[RAM_COEF_PERIOD_MAX_NUM]);
    if(ucPriceSwitchPeriodMax>CON_DAYTABLELEN_MAX)
    {
        ucPriceSwitchPeriodMax=CON_DAYTABLELEN_MAX;
    }
    if(0==ucPriceSwitchPeriodMax)
    {
        ucPriceSwitchPeriodMax=1;
    }
// AA --费率数最大值--AA
    ucPriceSwitchPriceMax=ValueHexFromBcd(RAM[RAM_COEF_PRICE_MAX_NUM]);
    if(ucPriceSwitchPriceMax>CON_PRICENUM_MAX)
    {
        ucPriceSwitchPriceMax=CON_PRICENUM_MAX;
    }
    if(0==ucPriceSwitchPriceMax)
    {
        ucPriceSwitchPriceMax=1;
    }
#if(CONFIG_METER_STEP_MODE==CONFIG_METER_STEP_MODE_ENABLE)  
// AA --阶梯数最大值--AA
    ucPriceSwitchStepMax=ValueHexFromBcd(RAM[RAM_COEF_STEP_NUM]);
    if(ucPriceSwitchStepMax>CON_STEPNUM_MAX)
    {
        ucPriceSwitchStepMax=CON_STEPNUM_MAX;
    }
    /*if(0==ucPriceSwitchStepMax)
    {
        ucPriceSwitchStepMax=1;
    }*/
#endif
// AA --公共节假日数的最大值--AA
    
    ucPriceSwitchHolidayMax=Bcd2DataToInt(&RAM[RAM_COEF_HOLIDAY_MAX_MUN]);
    if(ucPriceSwitchHolidayMax>CON_HOLIDAYNUM_MAX)
    {
        ucPriceSwitchHolidayMax=CON_HOLIDAYNUM_MAX;
    }
//  if(0==ucPriceSwitchHolidayMax)
//  {
//      ucPriceSwitchHolidayMax=1;
//  }
}


void InitPriceSwitch(void)
{
    ucPriceSwitchModeMinute=0xFF;
    ucPriceSwitchMOdeDay=0xFF;
    uiLastDayPieceAddr=0xFFFF;
    PriceSwitchModeParaInit();
}


uchar TestDayTableLen(uchar ucPoint)
{
    if((ucPoint>ucPriceSwitchPeriodMax)||(0==ucPoint))
    {
        return GAL_NO;
    }
    return GAL_YES;
}
uchar TestDayTableNum(uchar ucPoint)
{
    if((ucPoint>ucPriceSwitchDayTableMax)||(0==ucPoint))
    {
        return GAL_NO;
    }
    return GAL_YES;
}

uchar TestOnePrice(uchar ucPrice)
{
#if 0   
    if((ucPrice>ucPriceSwitchPriceMax)||(0==ucPrice))
        return 0;
    else
        return 1;
#else
    if((ucPrice>ValueBcdFromHex(ucPriceSwitchPriceMax))||(0==ucPrice)||0==TestBcd(ucPrice))
        return 0;
    else
        return 1;
#endif
}
uchar NumofEveryDayPriceChangeComm(uchar*point)
{
//  +0  ==  num
//  +1  ==  minute
//  +2  ==  Hour

    uchar l; // ,n,m;
    uchar *fp;
    u16 uiCurrent,uiFirst,uiLast;// ,uiNow,uiNext
    uchar ucIsReturn;
    uchar ucCount;
    ucCount=0;
    ucIsReturn=0;
    uiFirst=256*(*(point+2))+(*(point+1));
    uiLast=0x0000;
    for(l=0;l<DLT_SEASON_TABLE_MAX;l++)
    {
        fp=point+3*l;
        uiCurrent=256*(*(fp+2))+(*(fp+1));
        
        if((l!=0)&&(uiFirst==uiCurrent))
        {
            l=DLT_SEASON_TABLE_MAX;
            continue;
        }
        
        if(3!=TestMinute(*(fp+1))+TestHour(*(fp+2))+TestOnePrice(*(fp+0)))
        // AA  如果数据不合法则退出统计  AA
        {
            l=DLT_SEASON_TABLE_MAX;
            continue;
        }
        if((l!=0)&&(uiLast==uiCurrent))
        {
            l=DLT_SEASON_TABLE_MAX;
            continue;
        }
        if(0==ucIsReturn)
        {
            if(uiLast>uiCurrent)
            {
                ucIsReturn=1;
                if(uiCurrent>=uiFirst)
                {
                    l=DLT_SEASON_TABLE_MAX;
                    continue;
                }
            }
            ucCount++;
        }
        else
        {
            if((uiLast>uiCurrent)||(uiCurrent>=uiFirst))
            {
                l=DLT_SEASON_TABLE_MAX;
                continue;
            }
            else
            {
                ucCount++;
            }
            
        }
        uiLast=uiCurrent;
        
    }
    return (ucCount);

}
uchar NumofEveryDayPriceChange(uchar*point)
{
//  +0  ==  num
//  +1  ==  minute
//  +2  ==  Hour

    uchar l; // ,n,m;
    uchar *fp;
    u16 uiCurrent,uiFirst,uiLast;// ,uiNow,uiNext
    uchar ucIsReturn;
    uchar ucCount;
    ucCount=0;
    ucIsReturn=0;
    uiFirst=256*(*(point+2))+(*(point+1));
    uiLast=0x0000;
    for(l=0;l<ucPriceSwitchPeriodMax;l++)
    {
        fp=point+3*l;
        uiCurrent=256*(*(fp+2))+(*(fp+1));
        
        if((l!=0)&&(uiFirst==uiCurrent))
        {
            l=ucPriceSwitchPeriodMax;
            continue;
        }
        
        if(3!=TestMinute(*(fp+1))+TestHour(*(fp+2))+TestOnePrice(*(fp+0)))
        // AA  如果数据不合法则退出统计  AA
        {
            l=ucPriceSwitchPeriodMax;
            continue;
        }
        if((l!=0)&&(uiLast==uiCurrent))
        {
            l=ucPriceSwitchPeriodMax;
            continue;
        }
        if(0==ucIsReturn)
        {
            if(uiLast>uiCurrent)
            {
                ucIsReturn=1;
                if(uiCurrent>=uiFirst)
                {
                    l=ucPriceSwitchPeriodMax;
                    continue;
                }
            }
            ucCount++;
        }
        else
        {
            if((uiLast>uiCurrent)||(uiCurrent>=uiFirst))
            {
                l=ucPriceSwitchPeriodMax;
                continue;
            }
            else
            {
                ucCount++;
            }
            
        }
        uiLast=uiCurrent;
        
    }
    return (ucCount);

}   
#if 0
uchar NumofEveryDayPriceChange(uchar*point)
{
//  +0  ==  NUM
//  +1  ==  minute
//  +2  ==  hour
    uchar l,n,m,*fp;
//  uchar ucMaxPrice;
//  ucMaxPrice=ValueBcdFromHex(CON_PRICENUM_MAX+1);
    n=0;
    for(l=0;l<DLT_SEASON_TABLE_MAX;l++)
    {
        m=0;
        fp=point+3*l;
        if(l!=0)
            if(*(point+1)==(*(fp+1)))
                if(*(point+2)==(*(fp+2)))
                    m=1;
        if((2==TestMinute(*(fp+1))+TestHour(*(fp+2)))
            &&(1==TestOnePrice(*(fp+0)))&&(m==0))
        {
            n=n+1;
        }
        else 
        {
            l=DLT_SEASON_TABLE_MAX;
        }
        if(l!=(DLT_SEASON_TABLE_MAX-1))
        {
            if(((*(fp+1))==(*(fp+1+3)))&&((*(fp+2))==(*(fp+2+3))))
            {
                l=DLT_SEASON_TABLE_MAX;
            }
        }
    }
    return (n);
}
#endif
#if 0
uchar NumofEverySeasonDayTableChange(uchar*point)
{
//  +0  ==  num
//  +1  ==  day
//  +2  ==  month

    uchar l,n,m,*fp;
    n=0;
    for(l=0;l<CON_SEASONTABLELEN_MAX;l++)
    {
        m=0;
        fp=point+3*l;
        if(l!=0)
            if(*(point+1)==(*(fp+1)))
                if(*(point+2)==(*(fp+2)))
                    m=1;
        if((2==TestMinute(*(fp+1))+TestHour(*(fp+2)))
            &&(*(fp+0)<DLT_SEASON_TABLE_MAX)&&(m==0))
        {
            n=n+1;
        }
        else 
        {
            l=CON_SEASONTABLELEN_MAX;
        }
        if(l!=(CON_SEASONTABLELEN_MAX-1))
        {
            if(((*(fp+1))==(*(fp+1+3)))&&((*(fp+2))==(*(fp+2+3))))
            {
                l=CON_SEASONTABLELEN_MAX;
            }
        }
    }
    return (n);
}
#endif
uchar NumofEverySeasonDayTableChangeComm(uchar*point)
{
//  +0  ==  num
//  +1  ==  day
//  +2  ==  month

    uchar l; // ,n,m;
    uchar *fp;
    u16 uiCurrent,uiFirst,uiLast;// ,uiNow,uiNext
    uchar ucIsReturn;
    uchar ucCount;
    ucCount=0;
    ucIsReturn=0;
    uiFirst=256*(*(point+2))+(*(point+1));
    uiLast=0x0000;
    for(l=0;l<CON_SEASONTABLELEN_MAX;l++)
    {
        fp=point+3*l;
        uiCurrent=256*(*(fp+2))+(*(fp+1));
        
        if((l!=0)&&(uiFirst==uiCurrent))
        {
            l=CON_SEASONTABLELEN_MAX;
            continue;
        }
        
        if(3!=TestDay(*(fp+1))+TestMonth(*(fp+2))+TestDayTableNum(*(fp+0)))
        // AA  如果数据不合法则退出统计  AA
        {
            l=CON_SEASONTABLELEN_MAX;
            continue;
        }
        if(uiLast==uiCurrent)
        {
            l=CON_SEASONTABLELEN_MAX;
            continue;
        }
        if(0==ucIsReturn)
        {
            if(uiLast>uiCurrent)
            {
                ucIsReturn=1;
                if(uiCurrent>=uiFirst)
                {
                    l=CON_SEASONTABLELEN_MAX;
                    continue;
                }
            }
            ucCount++;
        }
        else
        {
            if((uiLast>uiCurrent)||(uiCurrent>=uiFirst))
            {
                l=CON_SEASONTABLELEN_MAX;
                continue;
            }
            else
            {
                ucCount++;
            }
            
        }
        uiLast=uiCurrent;
        
    }
    return (ucCount);

}

uchar NumofEverySeasonDayTableChange(uchar*point)
{
//  +0  ==  num
//  +1  ==  day
//  +2  ==  month

    uchar l; // ,n,m;
    uchar *fp;
    u16 uiCurrent,uiFirst,uiLast;// ,uiNow,uiNext
    uchar ucIsReturn;
    uchar ucCount;
    ucCount=0;
    ucIsReturn=0;
    uiFirst=256*(*(point+2))+(*(point+1));
    uiLast=0x0000;
    for(l=0;l<ucPriceSwitchSeasonTableMax;l++)
    {
        fp=point+3*l;
        uiCurrent=256*(*(fp+2))+(*(fp+1));
        
        if((l!=0)&&(uiFirst==uiCurrent))
        {
            l=ucPriceSwitchSeasonTableMax;
            continue;
        }
        
        if(3!=TestDay(*(fp+1))+TestMonth(*(fp+2))+TestDayTableNum(*(fp+0)))
        // AA  如果数据不合法则退出统计  AA
        {
            l=ucPriceSwitchSeasonTableMax;
            continue;
        }
        if(uiLast==uiCurrent)
        {
            l=ucPriceSwitchSeasonTableMax;
            continue;
        }
        if(0==ucIsReturn)
        {
            if(uiLast>uiCurrent)
            {
                ucIsReturn=1;
                if(uiCurrent>=uiFirst)
                {
                    l=ucPriceSwitchSeasonTableMax;
                    continue;
                }
            }
            ucCount++;
        }
        else
        {
            if((uiLast>uiCurrent)||(uiCurrent>=uiFirst))
            {
                l=ucPriceSwitchSeasonTableMax;
                continue;
            }
            else
            {
                ucCount++;
            }
            
        }
        uiLast=uiCurrent;
        
    }
    return (ucCount);

}

#if(CONFIG_METER_STEP_MODE==CONFIG_METER_STEP_MODE_ENABLE)
uchar NumofStepPriceChange(uchar*point)
{
    uchar k;
    ulong uiTemp[CON_STEPNUM_MAX];

    memcpy((uchar*)&uiTemp,point,4*CON_STEPNUM_MAX);
    if(4 != TestBcdNum((uchar*)&uiTemp[0],4))
    {
        return 0;
    }
    for(k=1;k<=(ucPriceSwitchStepMax);k++)
    {
        if ( (4!=TestBcdNum((uchar*)&uiTemp[k],4)) || (uiTemp[k-1] >= uiTemp[k] ) )
        {
            //The current k(st,from 0) step is not valid, So the step number is k(form 1) 
            break;
        }
    }

    if(k > ucPriceSwitchStepMax)
        k = ucPriceSwitchStepMax;
    
    return k;
}

uchar NumofPeriodPriceChange(uchar*point)
{
    uchar k;

    for(k=0;k<ucPriceSwitchPriceMax;k++)
    {
        if(4!=TestBcdNum((point+4*k),4))
        {
            break;
        }
    }
    
    return k;
}
#endif



void GetEveryDayTableMax(void)
{
    RAM[RAM_CURRENT_SEASON1CHANGENUM+0]=NumofEverySeasonDayTableChange(&RAM[RAM_SEASON1_DAYTABLE_CHANGE01]);
    RAM[RAM_CURRENT_DAYTABLECHANGE1NUM+0]=NumofEveryDayPriceChange(&RAM[RAM_SEASON1_DAYTABLE1_PERIOD01]);
    RAM[RAM_CURRENT_DAYTABLECHANGE1NUM+1]=NumofEveryDayPriceChange(&RAM[RAM_SEASON1_DAYTABLE2_PERIOD01]);
    RAM[RAM_CURRENT_DAYTABLECHANGE1NUM+2]=NumofEveryDayPriceChange(&RAM[RAM_SEASON1_DAYTABLE3_PERIOD01]);
    RAM[RAM_CURRENT_DAYTABLECHANGE1NUM+3]=NumofEveryDayPriceChange(&RAM[RAM_SEASON1_DAYTABLE4_PERIOD01]);
    RAM[RAM_CURRENT_DAYTABLECHANGE1NUM+4]=NumofEveryDayPriceChange(&RAM[RAM_SEASON1_DAYTABLE5_PERIOD01]);
    RAM[RAM_CURRENT_DAYTABLECHANGE1NUM+5]=NumofEveryDayPriceChange(&RAM[RAM_SEASON1_DAYTABLE6_PERIOD01]);
    RAM[RAM_CURRENT_DAYTABLECHANGE1NUM+6]=NumofEveryDayPriceChange(&RAM[RAM_SEASON1_DAYTABLE7_PERIOD01]);
    RAM[RAM_CURRENT_DAYTABLECHANGE1NUM+7]=NumofEveryDayPriceChange(&RAM[RAM_SEASON1_DAYTABLE8_PERIOD01]);

    RAM[RAM_CURRENT_SEASON2CHANGENUM+0]=NumofEverySeasonDayTableChange(&RAM[RAM_SEASON2_DAYTABLE_CHANGE01]);
    RAM[RAM_CURRENT_DAYTABLECHANGE2NUM+0]=NumofEveryDayPriceChange(&RAM[RAM_SEASON2_DAYTABLE1_PERIOD01]);
    RAM[RAM_CURRENT_DAYTABLECHANGE2NUM+1]=NumofEveryDayPriceChange(&RAM[RAM_SEASON2_DAYTABLE2_PERIOD01]);
    RAM[RAM_CURRENT_DAYTABLECHANGE2NUM+2]=NumofEveryDayPriceChange(&RAM[RAM_SEASON2_DAYTABLE3_PERIOD01]);
    RAM[RAM_CURRENT_DAYTABLECHANGE2NUM+3]=NumofEveryDayPriceChange(&RAM[RAM_SEASON2_DAYTABLE4_PERIOD01]);
    RAM[RAM_CURRENT_DAYTABLECHANGE2NUM+4]=NumofEveryDayPriceChange(&RAM[RAM_SEASON2_DAYTABLE5_PERIOD01]);
    RAM[RAM_CURRENT_DAYTABLECHANGE2NUM+5]=NumofEveryDayPriceChange(&RAM[RAM_SEASON2_DAYTABLE6_PERIOD01]);
    RAM[RAM_CURRENT_DAYTABLECHANGE2NUM+6]=NumofEveryDayPriceChange(&RAM[RAM_SEASON2_DAYTABLE7_PERIOD01]);
    RAM[RAM_CURRENT_DAYTABLECHANGE2NUM+7]=NumofEveryDayPriceChange(&RAM[RAM_SEASON2_DAYTABLE8_PERIOD01]);


#if(CONFIG_METER_STEP_MODE==CONFIG_METER_STEP_MODE_ENABLE)
    RAM[RAM_CURRENT_STEPPRICE_NUM+0]=NumofStepPriceChange(&RAM[RAM_STEP01_DATA01]);
    RAM[RAM_CURRENT_STEPPRICE_NUM+1]=NumofStepPriceChange(&RAM[RAM_STEP02_DATA01]);
    RAM[RAM_CURRENT_PERIODPRICE_NUM+0]=NumofPeriodPriceChange(&RAM[RAM_PERIODPRICE01_PRICE01]);
    RAM[RAM_CURRENT_PERIODPRICE_NUM+1]=NumofPeriodPriceChange(&RAM[RAM_PERIODPRICE02_PRICE01]);
#endif    
}

void GetNextHoliday(void)
{
    uchar ucTemp;
    UN_U32_PARAM unTemp;
    UN_U32_PARAM unNowTime;
    UN_U32_PARAM ucTempHoliday;
    uchar ucTempHolidayDayTable;
    uchar ucTempDayTable;
    uchar ucTempHolidayMax;
    unNowTime.cData.ucData0=0x00;
    unNowTime.cData.ucData1=RSOFT_RTC_DAY;
    unNowTime.cData.ucData2=RSOFT_RTC_MONTH;
    unNowTime.cData.ucData3=RSOFT_RTC_YEAR;
    
    ucTempHoliday.ulData=0xffffff00;
    ucTempHolidayDayTable=0xff;
    ucTempHolidayMax=ucPriceSwitchHolidayMax;
    
    if(ucTempHolidayMax > 0)
    {
        if(1==ReadDataDirect(RAM_PUBLIC_HOLIDAY_START+256*0,  256, &Wr_data[0]))
        {
            for(ucTemp=0;ucTemp<64;ucTemp++)
            {
                if(ucTempHolidayMax)
                {
                    ucTempHolidayMax--;
                }
                else
                {
                    break;
                }
                unTemp.ulData=0x00000000;
                ucTempDayTable=Wr_data[ucTemp*4+0];
                unTemp.cData.ucData1=Wr_data[ucTemp*4+1];
                unTemp.cData.ucData2=Wr_data[ucTemp*4+2];
                unTemp.cData.ucData3=Wr_data[ucTemp*4+3];
                if(0xff==unTemp.cData.ucData3)
                {
                    if((unTemp.cData.ucData2<RSOFT_RTC_MONTH)
                        ||((unTemp.cData.ucData2==RSOFT_RTC_MONTH)&&(unTemp.cData.ucData1<RSOFT_RTC_DAY)))
                    {
                        unTemp.cData.ucData3=Byte1BcdAdd(RSOFT_RTC_YEAR);
                    }
                    else
                    {
                        unTemp.cData.ucData3=RSOFT_RTC_YEAR;
                    }
                }
                if(2==(TestDayMonthYear(&unTemp.cData.ucData1)+TestDayTableNum(ucTempDayTable)))
                {
                    unTemp.cData.ucData0=0x00;
                    if((unNowTime.ulData<=unTemp.ulData)&&(ucTempHoliday.ulData>unTemp.ulData))
                    {
                        ucTempHoliday.ulData=unTemp.ulData;
                        ucTempHolidayDayTable=ucTempDayTable;
                    }
                }               
            }
        }
    }
    
    
    if(ucTempHolidayMax > 0)
    {
        if(1==ReadDataDirect(RAM_PUBLIC_HOLIDAY_START+256*1,  256, &Wr_data[0]))
        {
            for(ucTemp=0;ucTemp<64;ucTemp++)
            {
                if(ucTempHolidayMax)
                {
                    ucTempHolidayMax--;
                }
                else
                {
                    break;
                }
                unTemp.ulData=0x00000000;
                ucTempDayTable=Wr_data[ucTemp*4+0];
                unTemp.cData.ucData1=Wr_data[ucTemp*4+1];
                unTemp.cData.ucData2=Wr_data[ucTemp*4+2];
                unTemp.cData.ucData3=Wr_data[ucTemp*4+3];
                if(0xff==unTemp.cData.ucData3)
                {
                    if((unTemp.cData.ucData2<RSOFT_RTC_MONTH)
                        ||((unTemp.cData.ucData2==RSOFT_RTC_MONTH)
                        &&(unTemp.cData.ucData1<RSOFT_RTC_DAY)))
                    {
                        unTemp.cData.ucData3=Byte1BcdAdd(RSOFT_RTC_YEAR);
                    }
                    else
                    {
                        unTemp.cData.ucData3=RSOFT_RTC_YEAR;
                    }
                }
                if(2==(TestDayMonthYear(&unTemp.cData.ucData1)+TestDayTableNum(ucTempDayTable)))
                {
                    unTemp.cData.ucData0=0x00;
                    if((unNowTime.ulData<=unTemp.ulData)&&(ucTempHoliday.ulData>unTemp.ulData))
                    {
                        ucTempHoliday.ulData=unTemp.ulData;
                        ucTempHolidayDayTable=ucTempDayTable;
                    }
                }               
            }
        }
    }
    
    
    
    if(ucTempHolidayMax > 0)
    {
        if(1==ReadDataDirect(RAM_PUBLIC_HOLIDAY_START+256*2,  256, &Wr_data[0]))
        {
            for(ucTemp=0;ucTemp<64;ucTemp++)
            {
                if(ucTempHolidayMax)
                {
                    ucTempHolidayMax--;
                }
                else
                {
                    break;
                }
                unTemp.ulData=0x00000000;
                ucTempDayTable=Wr_data[ucTemp*4+0];
                unTemp.cData.ucData1=Wr_data[ucTemp*4+1];
                unTemp.cData.ucData2=Wr_data[ucTemp*4+2];
                unTemp.cData.ucData3=Wr_data[ucTemp*4+3];
                if(0xff==unTemp.cData.ucData3)
                {
                    if((unTemp.cData.ucData2<RSOFT_RTC_MONTH)
                        ||((unTemp.cData.ucData2==RSOFT_RTC_MONTH)
                        &&(unTemp.cData.ucData1<RSOFT_RTC_DAY)))
                    {
                        unTemp.cData.ucData3=Byte1BcdAdd(RSOFT_RTC_YEAR);
                    }
                    else
                    {
                        unTemp.cData.ucData3=RSOFT_RTC_YEAR;
                    }
                }
                if(2==(TestDayMonthYear(&unTemp.cData.ucData1)+TestDayTableNum(ucTempDayTable)))
                {
                    unTemp.cData.ucData0=0x00;
                    if((unNowTime.ulData<=unTemp.ulData)&&(ucTempHoliday.ulData>unTemp.ulData))
                    {
                        ucTempHoliday.ulData=unTemp.ulData;
                        ucTempHolidayDayTable=ucTempDayTable;
                    }
                }               
            }
        }
    }
    
    
    if(ucTempHolidayMax > 0)
    {
        if(1==ReadDataDirect(RAM_PUBLIC_HOLIDAY_START+256*3,  252, &Wr_data[0]))
        {
            for(ucTemp=0;ucTemp<63;ucTemp++)
            {
                if(ucTempHolidayMax)
                {
                    ucTempHolidayMax--;
                }
                else
                {
                    break;
                }
                unTemp.ulData=0x00000000;
                ucTempDayTable=Wr_data[ucTemp*4+0];
                unTemp.cData.ucData1=Wr_data[ucTemp*4+1];
                unTemp.cData.ucData2=Wr_data[ucTemp*4+2];
                unTemp.cData.ucData3=Wr_data[ucTemp*4+3];
                if(0xff==unTemp.cData.ucData3)
                {
                    if((unTemp.cData.ucData2<RSOFT_RTC_MONTH)
                        ||((unTemp.cData.ucData2==RSOFT_RTC_MONTH)
                        &&(unTemp.cData.ucData1<RSOFT_RTC_DAY)))
                    {
                        unTemp.cData.ucData3=Byte1BcdAdd(RSOFT_RTC_YEAR);
                    }
                    else
                    {
                        unTemp.cData.ucData3=RSOFT_RTC_YEAR;
                    }
                }
                if(2==(TestDayMonthYear(&unTemp.cData.ucData1)+TestDayTableNum(ucTempDayTable)))
                {
                    unTemp.cData.ucData0=0x00;
                    if((unNowTime.ulData<=unTemp.ulData)&&(ucTempHoliday.ulData>unTemp.ulData))
                    {
                        ucTempHoliday.ulData=unTemp.ulData;
                        ucTempHolidayDayTable=ucTempDayTable;
                    }
                }               
            }
        }
    }
    ucTempHoliday.cData.ucData0=ucTempHolidayDayTable;
    
    RAM[RAM_NEXT_PUBLIC_HOLIDAY+0]=ucTempHoliday.ucbData[0];
    RAM[RAM_NEXT_PUBLIC_HOLIDAY+1]=ucTempHoliday.ucbData[1];
    RAM[RAM_NEXT_PUBLIC_HOLIDAY+2]=ucTempHoliday.ucbData[2];
    RAM[RAM_NEXT_PUBLIC_HOLIDAY+3]=ucTempHoliday.ucbData[3];
    //ucCurrentHoliday.ulData=ucTempHoliday.ulData;
    
}

#if(CONFIG_METER_STEP_MODE==CONFIG_METER_STEP_MODE_ENABLE)

// 带入当前费率号，返回当前费率电价
ulong GetPeriodPriceNumFromPeriodNum(uchar feeNo)
{
    ulong uiDataAddr,uiTemp;

    if(2==STATUS_PERIODPRICE_POINT)
    {
        uiDataAddr=RAM_PERIODPRICE02_PRICE01;
    }
    else
    {
        uiDataAddr=RAM_PERIODPRICE01_PRICE01;
    }
    if((0==feeNo)||(feeNo>ucPriceSwitchPriceMax))
    {
        STATUS_PERIODPRICE_NUM=1;
    }
    else
    {
        STATUS_PERIODPRICE_NUM=feeNo;
    }

    memcpy((uchar*)&uiTemp,(uchar*)&RAM[uiDataAddr+4*(STATUS_PERIODPRICE_NUM-1)],4);
    memcpy((uchar*)&RAM[RAM_CURRENT_PERIODPRICE_PRICE],(uchar*)&RAM[uiDataAddr+4*(STATUS_PERIODPRICE_NUM-1)],4);

    return uiTemp;
}



// 返回当前阶梯号
uchar GetStepNumFromUseEnergy(void)
{
    ulong uiDataAddr,useEnergy,lddderEnergy[CON_STEPNUM_MAX];
    uchar stepNum,stepNo,k;

    if(2==STATUS_STEPPRICE_POINT)
    {
        uiDataAddr=RAM_STEP02_DATA01;
        stepNum=RAM[RAM_CURRENT_STEPPRICE_NUM+1];
    }
    else
    {
        uiDataAddr=RAM_STEP01_DATA01;
        stepNum=RAM[RAM_CURRENT_STEPPRICE_NUM+0];
    }
    if(( stepNum == 0 ) || (ucPriceSwitchStepMax < 1))
    {
        stepNo = 0;
        STATUS_STEPPRICE_NUM = stepNo;
        return stepNo;
    }
    memcpy((uchar*)&lddderEnergy[0],(uchar*)&RAM[uiDataAddr],4*CON_STEPNUM_MAX);
    memcpy((uchar*)&useEnergy,(uchar*)&RAM[RAM_KWH_C_USE_ALL+1],4);
    //if(( stepNum == 0 )||( stepNum > (ucPriceSwitchStepMax+1) ))
    if(( stepNum > (ucPriceSwitchStepMax) ))
    {
        stepNum = ucPriceSwitchStepMax;
    }
    stepNo=1;
    if(useEnergy>0)
    {
        for( k=1; k<=stepNum; k++ )
        {
            if ( useEnergy <= lddderEnergy[k-1] )
            {
                stepNo = k;
                break;
            }
            else
            {
                stepNo = k+1;
            }
        }
    } 
    if(stepNo > stepNum+1)
        stepNo = stepNum+1;
    
    STATUS_STEPPRICE_NUM =stepNo;

    return stepNo;
}


// 带入当前梯度号，返回当前阶梯电价
ulong GetStepPriceFromStepNum(uchar stepNo)
{
    ulong uiDataAddr,uiPrice;

    if(2==STATUS_STEPPRICE_POINT)
    {
        uiDataAddr=RAM_STEPPRICE02_PRICE01;
    }
    else
    {
        uiDataAddr=RAM_STEPPRICE01_PRICE01;
    }
    //if((0==stepNo)||(stepNo>(ucPriceSwitchStepMax+1)))
    if((stepNo>(ucPriceSwitchStepMax+1)))
    {
        STATUS_STEPPRICE_NUM=1;
    }
    else
    {
        STATUS_STEPPRICE_NUM=stepNo;
    }
    if(stepNo!=0)
    {
        memcpy((uchar*)&uiPrice,(uchar*)&RAM[uiDataAddr+4*(STATUS_STEPPRICE_NUM-1)],4);
        memcpy((uchar*)&RAM[RAM_CURRENT_STEPPRICE_PRICE],(uchar*)&RAM[uiDataAddr+4*(STATUS_STEPPRICE_NUM-1)],4);
    }
    else
    {
        uiPrice = 0;
        memset((uchar*)&RAM[RAM_CURRENT_STEPPRICE_PRICE],0,4);
    }
    return uiPrice;
}


ulong GetStepPrice(void)
{
    ulong uiPrice;
    uchar stepNo;

    stepNo = GetStepNumFromUseEnergy();
    uiPrice = GetStepPriceFromStepNum(stepNo);
    return uiPrice;
}
#endif

void GetDayTableNumFromSeasonNum(void)
{
    uchar ucTemp,ucTimes;
    // uchar ucValue;
    u16 uiDataAddr;
    u16 y0,y1,y;
    if(2==STATUS_SEASONTABLEPOINT)
    {
        uiDataAddr=RAM_SEASON2_DAYTABLE_CHANGE01;
        ucTimes=(RAM[RAM_CURRENT_SEASON2CHANGENUM+0]);
    }
    else
    {
        uiDataAddr=RAM_SEASON1_DAYTABLE_CHANGE01;
        ucTimes=(RAM[RAM_CURRENT_SEASON1CHANGENUM+0]);
    }
    if((0==ucTimes)||(1==ucTimes)||(ucTimes>ucPriceSwitchSeasonTableMax))
    {
        STATUS_SEASONNUM=1;
        ucTemp=0;
    }
    else
    {   // ucTimes--;
        y=RSOFT_RTC_MONTH*256+RSOFT_RTC_DAY;
        STATUS_SEASONNUM=ucTimes;
        for(ucTemp=0;ucTemp<ucTimes;ucTemp++)
        {
            y0=RAM[uiDataAddr+3*ucTemp+2]*256+RAM[uiDataAddr+3*ucTemp+1];
            y1=RAM[uiDataAddr+3*ucTemp+2+3]*256+RAM[uiDataAddr+3*ucTemp+1+3];
            if(y0<=y1)
            {
                if((y>=y0)&&(y<y1)) 
                {
                    STATUS_SEASONNUM=ucTemp+1;
                    ucTemp=ucTimes;
                    // break;
                }
            }
            else
            {
                if((y>=y0)||(y<y1))
                {
                    STATUS_SEASONNUM=ucTemp+1;
                    ucTemp=ucTimes;
                    // break;
                }
            }
        }
    }
// aa----AA
    if(STATUS_SEASONNUM >ucPriceSwitchSeasonTableMax)
    {
        STATUS_SEASONNUM=ucPriceSwitchSeasonTableMax;
    }
    if((0==STATUS_SEASONNUM)||(STATUS_SEASONNUM>ucPriceSwitchSeasonTableMax))
    {
        STATUS_SEASONNUM=1;
    }
    STATUS_DAYTABLE=RAM[uiDataAddr+3*(STATUS_SEASONNUM-1)+0];
    STATUS_SEASONNUM=ValueBcdFromHex(STATUS_SEASONNUM);
    RAM[RAM_CURRENT_PRICESWITCHMODE]=DLT_PRICE_SWITCH_MODE_SEASON;
}



void GetDayTableNumFromHoliday(void)
{
    if((RAM[RAM_NEXT_PUBLIC_HOLIDAY+3]==RSOFT_RTC_YEAR)
        &&(RAM[RAM_NEXT_PUBLIC_HOLIDAY+2]==RSOFT_RTC_MONTH)
        &&(RAM[RAM_NEXT_PUBLIC_HOLIDAY+1]==RSOFT_RTC_DAY))
    {
        STATUS_DAYTABLE=RAM[RAM_NEXT_PUBLIC_HOLIDAY+0];
        RAM[RAM_CURRENT_PRICESWITCHMODE]=DLT_PRICE_SWITCH_MODE_HOLIDAY;
    }
}

 
void GetDayTableNumFromWeekDay(void)
{
    if(0==(RAM[RAM_CHARACTER_REST_DAY]&ConWeekDayWordTable[RSOFT_RTC_WEEK]))
    {
        STATUS_DAYTABLE=RAM[RAM_CHARACTER_REST_DAYNO];
        RAM[RAM_CURRENT_PRICESWITCHMODE]=DLT_PRICE_SWITCH_MODE_RESET;
    }

}

/*==================================================================
//函数名：  PublicHolidayDataInit
//作者：    陶治国
//日期：    
//功能：    读取节假日数据到内存
//          可以在初始化、参数更改后、参数校验 时调用一次
//输入参数：无
//输出参数：无
//返回值：  无
//=================================================================*/
void PublicHolidayDataInit(void)
{
    uint uiLen, uiOffset;
    //暂时将所有数据读到RAM
    uiLen = 128;
    for(uiOffset=0; uiOffset<(1024-128); uiOffset=uiOffset+uiLen)
    {
        ReadCoefDataWithCheck(EPL_PUBLIC_HOLIDAY_START+uiOffset, uiLen, &RAM[RAM_PUBLIC_HOLIDAY_START+uiOffset], 1);
    }

}

/*==================================================================
//函数名：  PriceSwitchModeParaInit
//作者：    陶治国
//日期：    
//功能：    初始化当前运行套数
//          可以在初始化、参数更改后、参数校验 时调用一次
//输入参数：无
//输出参数：无
//返回值：  无
//=================================================================*/
void PriceSwitchModeParaInit(void)
{
    //初始化当前运行套数
    GetCurSheetNum();
    //换成变量参数，便于之后调用计算
    GetPriceSwitchTableMax();       //初始化时区表时段表参数--最大值
    GetEveryDayTableMax();          //初始化时区表时段表参数--设置值
    GetNext2SheetSwitchTime();      //计算下一个2套参数切换时间
}

/*==================================================================
//函数名：  Do2SheetSwitch
//作者：    陶治国
//日期：    
//功能：    执行2套时区表、时段表、费率阶梯表的切换
//          每分钟判断执行一次
//输入参数：无
//输出参数：无
//返回值：  无
//=================================================================*/
uchar Do2SheetSwitch(void)
{
    uchar ucTemp;
    uchar SomethingSwith=0;
#if(GAL_NO==CON_PRICESWITCH_SAMETIME_RESTORE_MODE)
    ulong ulLastChangeTime;
#endif    

    ucTemp=1;
    //当前的时间到达或超过切换时间，则立即执行切换
    if(ulNowMinTime>=ulNext2SeasonTableSwitchTime)
    {
        if(1==ReadDataDirect(EPL_HADECHANGE_2SEASONTABLECHANGETIME,  6, &Wr_data[0]))
        {
#if(GAL_YES==CON_PRICESWITCH_SAMETIME_RESTORE_MODE)
            ucTemp=1;
#else
            ulLastChangeTime = mmHHDDMMYYToLong(&Wr_data[0]);
            if(ulLastChangeTime == ulNext2SeasonTableSwitchTime)
            {
                ucTemp = 0;
            }
#endif
            if(ucTemp == 1)
            {
                STATUS_SEASONTABLEPOINT=Wr_data[5];
                if(STATUS_SEASONTABLEPOINT == 0)
                {
                    STATUS_SEASONTABLEPOINT = 1;
                }
                STATUS_SEASONTABLEPOINT++;
                if(STATUS_SEASONTABLEPOINT>2)
                    STATUS_SEASONTABLEPOINT=1;
                FLG_SEASON_STATUS = STATUS_SEASONTABLEPOINT-1;
                SomethingSwith = 1;
                Wr_data[5]=STATUS_SEASONTABLEPOINT;
                memcpy(&Wr_data[0], &RAM[RAM_COEF_2SEASONCHANGE_TIME+0], 5);
                // TODO: EPL_HADECHANGE_2SEASONTABLECHANGETIME是个软肋，万一存错了不可想象
                WriteDataDirect(&Wr_data[0], EPL_HADECHANGE_2SEASONTABLECHANGETIME,  6);
                FlgFreezeSeasonChange=GAL_YES;
                LOGTRACE("FlgFreezeSeasonChange=GAL_YES, %d, %d\n", ulNowMinTime, ulNext2SeasonTableSwitchTime);
                // AA 两套时区切换，重新开始算 AA
                //DemandDataInit();
            }
            // AA  把当前的切换时间初始化为0  AA
            WriteCoefDataWithSync(&ucZeroArray[0], EPL_COEF_2SEASONCHANGE_TIME, 5);
            //为了安全期间，切换已执行的情况下，重新初始化切换时间变量
            ulNext2SeasonTableSwitchTime = 0xFFFFFFFF;
            //GetNext2SheetSwitchTime();
        }
    }

    ucTemp=1;
    if(ulNowMinTime>=ulNext2DayTableTableSwitchTime)
    {
        if(1==ReadDataDirect(EPL_HADECHANGE_2DAYTABLECHANGETIME,  6, &Wr_data[0]))
        {
#if(GAL_YES==CON_PRICESWITCH_SAMETIME_RESTORE_MODE)
            ucTemp=1;
#else
            ulLastChangeTime = mmHHDDMMYYToLong(&Wr_data[0]);
            if(ulLastChangeTime == ulNext2DayTableTableSwitchTime)
            {
                ucTemp = 0;
            }
#endif
            if(ucTemp == 1)
            {
                STATUS_DAYTABLEPOINT=Wr_data[5];
                if(STATUS_DAYTABLEPOINT == 0)
                {
                    STATUS_DAYTABLEPOINT = 1;
                }
                STATUS_DAYTABLEPOINT++;
                if(STATUS_DAYTABLEPOINT>2)
                    STATUS_DAYTABLEPOINT=1;
                FLG_DAYTABLE_STATUS = STATUS_DAYTABLEPOINT-1;
                SomethingSwith = 1;
                Wr_data[5]=STATUS_DAYTABLEPOINT;
                memcpy(&Wr_data[0], &RAM[RAM_COEF_2DAYTABLECHANGE_TIME+0], 5);
                WriteDataDirect(&Wr_data[0], EPL_HADECHANGE_2DAYTABLECHANGETIME,  6);
                FlgFreezeDayTableChange=GAL_YES;
                LOGTRACE("FlgFreezeDayTableChange=GAL_YES, %d, %d\n", ulNowMinTime, ulNext2DayTableTableSwitchTime);
                // AA 两套时区切换，重新开始算 AA
                //DemandDataInit();
            }
            // AA  把当前的切换时间初始化为0  AA
            WriteCoefDataWithSync(&ucZeroArray[0], EPL_COEF_2DAYTABLECHANGE_TIME, 5);
            //为了安全期间，切换已执行的情况下，重新初始化切换时间变量
            ulNext2DayTableTableSwitchTime = 0xFFFFFFFF;
            //GetNext2SheetSwitchTime();
        }
    }
#if(CONFIG_METER_STEP_PERIODPRICE_MODE==CONFIG_METER_STEP_PERIODPRICE_MODE_ENABLE)
    ucTemp=1;
    if(ulNowMinTime>=ulNext2StepTableSwitchTime)
    {
        if(1==ReadDataDirect(EPL_HADECHANGE_STEPPRICE_CHANGETIME,  6, &Wr_data[0]))
        {
#if(GAL_YES==CON_PRICESWITCH_SAMETIME_RESTORE_MODE)
            ucTemp=1;
#else
            ulLastChangeTime = mmHHDDMMYYToLong(&Wr_data[0]);
            if(ulLastChangeTime == ulNext2StepTableSwitchTime)
            {
                ucTemp = 0;
            }
#endif
            if(ucTemp == 1)
            {
                STATUS_STEPPRICE_POINT=Wr_data[5];
                STATUS_STEPPRICE_POINT++;
                if(STATUS_STEPPRICE_POINT>2)
                    STATUS_STEPPRICE_POINT=1;
                FLG_STEPPRICETABLE_STATUS = STATUS_STEPPRICE_POINT-1;
                SomethingSwith = 1;
                Wr_data[5]=STATUS_STEPPRICE_POINT;
                memcpy(&Wr_data[0], &RAM[RAM_COEF_STEPPRICE_CHANGETIME+0], 5);
                WriteDataDirect(&Wr_data[0], EPL_HADECHANGE_STEPPRICE_CHANGETIME,  6);
                FlgFreezeStepPriceTableChange=GAL_YES;
                LOGTRACE("FlgFreezeStepPriceTableChange=GAL_YES, %d, %d\n", ulNowMinTime, ulNext2StepTableSwitchTime);
            }
            // AA  把当前的切换时间初始化为0  AA
            WriteCoefDataWithSync(&ucZeroArray[0], EPL_COEF_STEPPRICE_CHANGETIME, 5);
            //为了安全期间，切换已执行的情况下，重新初始化切换时间变量
            ulNext2StepTableSwitchTime = 0xFFFFFFFF;
            //GetNext2SheetSwitchTime();
        }
    }

    ucTemp=1;
    if(ulNowMinTime>=ulNext2PriceTableSwitchTime)
    {
        if(1==ReadDataDirect(EPL_HADECHANGE_PERIODPRICE_CHANGENUM,  6, &Wr_data[0]))
        {
#if(GAL_YES==CON_PRICESWITCH_SAMETIME_RESTORE_MODE)
            ucTemp=1;
#else
            ulLastChangeTime = mmHHDDMMYYToLong(&Wr_data[0]);
            if(ulLastChangeTime == ulNext2PriceTableSwitchTime)
            {
                ucTemp = 0;
            }
#endif
            if(ucTemp == 1)
            {
                STATUS_PERIODPRICE_POINT=Wr_data[5];
                STATUS_PERIODPRICE_POINT++;
                if(STATUS_PERIODPRICE_POINT>2)
                    STATUS_PERIODPRICE_POINT=1;
                FLG_PERIODPRICETABLE_STATUS = STATUS_PERIODPRICE_POINT-1;
                SomethingSwith = 1;
                Wr_data[5]=STATUS_PERIODPRICE_POINT;
                memcpy(&Wr_data[0], &RAM[RAM_COEF_PERIODPRICE_CHANGETIME+0], 5);
                WriteDataDirect(&Wr_data[0], EPL_HADECHANGE_PERIODPRICE_CHANGETIME,  6);
                FlgFreezePeriodPriceTableChange=GAL_YES;
                LOGTRACE("FlgFreezePeriodPriceTableChange=GAL_YES, %d, %d\n", ulNowMinTime, ulNext2PriceTableSwitchTime);
            }
            // AA  把当前的切换时间初始化为0  AA
            WriteCoefDataWithSync(&Wr_data[0], EPL_COEF_PERIODPRICE_CHANGETIME, 5);
            //为了安全期间，切换已执行的情况下，重新初始化切换时间变量
            ulNext2PriceTableSwitchTime = 0xFFFFFFFF;
            //GetNext2SheetSwitchTime();
        }
    }
    
#endif    
    return SomethingSwith;
}

/*==================================================================
//函数名：  GetCurSheetNum
//作者：    陶治国
//日期：    
//功能：    初始化当前时区表、时段表、费率阶梯表的使用的套索引
//          可以在初始化、参数更改后、参数校验 时调用一次
//输入参数：无
//输出参数：无
//返回值：  无
//=================================================================*/
void GetCurSheetNum(void)
{
    // AA  重新更新当前2套时区表的切换数据  AA
    if(1==ReadDataDirect(EPL_HADECHANGE_2SEASONTABLECHANGETIME,  6, &Wr_data[0]))
    {
        STATUS_SEASONTABLEPOINT=Wr_data[5];
    }
    #if(CONFIG_METER_AREA_MODE_SICHUAN==CONFIG_METER_AREA_MODE)
    if(5==Test99Num(&RAM[RAM_COEF_2SEASONCHANGE_TIME+0], 5))
    {
        STATUS_SEASONTABLEPOINT=1;
    }
    #endif
    
    // AA  纠错处理  AA
    if(2!=STATUS_SEASONTABLEPOINT)
    {
        STATUS_SEASONTABLEPOINT=0x01;
        FLG_SEASON_STATUS=0;
    }
    else
    {
        FLG_SEASON_STATUS=1;
    }

    // AA  重新更新当前2套日时段表的切换数据  AA
    if(1==ReadDataDirect(EPL_HADECHANGE_2DAYTABLECHANGETIME,  6, &Wr_data[0]))
    {
        STATUS_DAYTABLEPOINT=Wr_data[5];
    }
    #if(CONFIG_METER_AREA_MODE_SICHUAN==CONFIG_METER_AREA_MODE)
    if(5==Test99Num(&RAM[RAM_COEF_2DAYTABLECHANGE_TIME+0], 5))
    {
        STATUS_DAYTABLEPOINT=1;
    }
    #endif
    
    // AA  纠错处理  AA
    if(2!=STATUS_DAYTABLEPOINT)
    {
        STATUS_DAYTABLEPOINT=0x01;
        FLG_DAYTABLE_STATUS=0;
    }
    else
    {
        FLG_DAYTABLE_STATUS=1;
    }

#if(CONFIG_METER_STEP_MODE==CONFIG_METER_STEP_MODE_ENABLE)
    // AA  重新更新当前2套阶梯表的切换数据  AA
    if(1==ReadDataDirect(EPL_HADECHANGE_STEPPRICE_CHANGENUM,  1, &Wr_data[0]))
    {
        STATUS_STEPPRICE_POINT=Wr_data[0];
    }
    
    #if(CONFIG_METER_AREA_MODE_SICHUAN==CONFIG_METER_AREA_MODE)
    if(5==Test99Num(&RAM[RAM_COEF_STEPPRICE_CHANGETIME+0], 5))
    {
        STATUS_STEPPRICE_POINT=1;
    }
    #endif
    
    // AA  纠错处理  AA
    if(2!=STATUS_STEPPRICE_POINT)
    {
        STATUS_STEPPRICE_POINT=0x01;
        FLG_STEPPRICETABLE_STATUS=0;
    }
    else
    {
        FLG_STEPPRICETABLE_STATUS=1;
    }
    // AA  重新更新当前2套费率表的切换数据  AA
    if(1==ReadDataDirect(EPL_HADECHANGE_PERIODPRICE_CHANGENUM,  1, &Wr_data[0]))
    {
        STATUS_PERIODPRICE_POINT=Wr_data[0];
    }
    
    #if(CONFIG_METER_AREA_MODE_SICHUAN==CONFIG_METER_AREA_MODE)
    if(5==Test99Num(&RAM[RAM_COEF_PERIODPRICE_CHANGETIME+0], 5))
    {
        STATUS_PERIODPRICE_POINT=1;
    }
    #endif
    
    // AA  纠错处理  AA
    if(2!=STATUS_PERIODPRICE_POINT)
    {
        STATUS_PERIODPRICE_POINT=0x01;
        FLG_PERIODPRICETABLE_STATUS=0;
    }
    else
    {
        FLG_PERIODPRICETABLE_STATUS=1;
    }
#else
    // AA  重新更新当前2套阶梯表的切换数据  AA
    STATUS_STEPPRICE_POINT=0x01;
    FLG_STEPPRICETABLE_STATUS=0;
    // AA  重新更新当前2套费率表的切换数据  AA
    STATUS_PERIODPRICE_POINT=0x01;
    FLG_PERIODPRICETABLE_STATUS=0;
#endif
}

/*==================================================================
//函数名：  GetNext2SheetSwitchTime
//作者：    陶治国
//日期：    
//功能：    计算下一个2套参数切换时间
//          可以在初始化、参数更改后、参数校验 时调用一次
//输入参数：无
//输出参数：无
//返回值：  无
//=================================================================*/
void GetNext2SheetSwitchTime(void)
{
    ulong ulChangeTime;
    // AA ======== 切换2 套时区---->START ======== AA   
    LOGTRACE("In GetNext2SheetSwitchTime\n");
    ulNext2SeasonTableSwitchTime = 0xFFFFFFFF;
    if(5!=TestZeroNum(&RAM[RAM_COEF_2SEASONCHANGE_TIME+0], 5))
    {
        // AA  如果是0，则表示不用切换，或者已经切换  AA
        if(3==TestDayMonthYear(&RAM[RAM_COEF_2SEASONCHANGE_TIME+2])
            +TestHour(RAM[RAM_COEF_2SEASONCHANGE_TIME+1])
            +TestMinute(RAM[RAM_COEF_2SEASONCHANGE_TIME+0]))
        {
            ulChangeTime=mmHHDDMMYYToLong(&RAM[RAM_COEF_2SEASONCHANGE_TIME+0]);
            //if(ulNowMinTime<=ulChangeTime)
            //不用比较，因为切换完自动清零。不比较也正好用来掉电时间的补切换
            {
                ulNext2SeasonTableSwitchTime = ulChangeTime;
            }
        }
    }      
    /*else
    {
        ulNext2SeasonTableSwitchTime = 0xFFFFFFFF;
    }*/
    // AA ======== 切换2 套时区---->END ======== AA   
    
    // AA ======== 切换2 套时段---->START ======== AA   
    ulNext2DayTableTableSwitchTime = 0xFFFFFFFF;
    if(5!=TestZeroNum(&RAM[RAM_COEF_2DAYTABLECHANGE_TIME+0], 5))
    {
        LOGTRACE("DAYTABLECHANGE_TIME %02X %02X %02X %02X %02X\n", RAM[RAM_COEF_2DAYTABLECHANGE_TIME+0],    \
            RAM[RAM_COEF_2DAYTABLECHANGE_TIME+1], RAM[RAM_COEF_2DAYTABLECHANGE_TIME+2], 
            RAM[RAM_COEF_2DAYTABLECHANGE_TIME+3], RAM[RAM_COEF_2DAYTABLECHANGE_TIME+4]);
        // AA  如果是0，则表示不用切换，或者已经切换  AA
        if(3==TestDayMonthYear(&RAM[RAM_COEF_2DAYTABLECHANGE_TIME+2])
            +TestHour(RAM[RAM_COEF_2DAYTABLECHANGE_TIME+1])
            +TestMinute(RAM[RAM_COEF_2DAYTABLECHANGE_TIME+0]))
        {
            ulChangeTime=mmHHDDMMYYToLong(&RAM[RAM_COEF_2DAYTABLECHANGE_TIME+0]);
            //if(ulNowMinTime<=ulChangeTime)
            //不用比较，因为切换完自动清零。不比较也正好用来掉电时间的补切换
            {
                ulNext2DayTableTableSwitchTime = ulChangeTime;
                LOGTRACE("ulNext2DayTableTableSwitchTime = %d\n", ulNext2DayTableTableSwitchTime);
            }
        }
    }       
    /*else
    {
        ulNext2DayTableTableSwitchTime = 0xFFFFFFFF;
    }*/
    // AA ======== 切换2 套时段---->END ======== AA   


#if(CONFIG_METER_STEP_MODE==CONFIG_METER_STEP_MODE_ENABLE)

    // AA ======== 切换2 套运行阶梯---->START ======== AA   
    ulNext2StepTableSwitchTime = 0xFFFFFFFF;
    if(5!=TestZeroNum(&RAM[RAM_COEF_STEPPRICE_CHANGETIME+0], 5))
    {
        // AA  如果是0，则表示不用切换，或者已经切换  AA
        if(3==TestDayMonthYear(&RAM[RAM_COEF_STEPPRICE_CHANGETIME+2])
            +TestHour(RAM[RAM_COEF_STEPPRICE_CHANGETIME+1])
            +TestMinute(RAM[RAM_COEF_STEPPRICE_CHANGETIME+0]))
        {
            ulChangeTime=mmHHDDMMYYToLong(&RAM[RAM_COEF_STEPPRICE_CHANGETIME+0]);
            //if(ulNowMinTime<ulChangeTime)
            //不用比较，因为切换完自动清零。不比较也正好用来掉电时间的补切换
            {
                ulNext2StepTableSwitchTime = ulChangeTime;
            }
        }
    }       
    /*else
    {
        ulNext2StepTableSwitchTime = 0xFFFFFFFF;
    }*/
    // AA ======== 切换2 套运行阶梯---->END ======== AA   
#endif
#if(CONFIG_METER_STEP_PERIODPRICE_MODE==CONFIG_METER_STEP_PERIODPRICE_MODE_ENABLE)

    // AA ======== 切换2 套运行费率---->START ======== AA   
    ulNext2PriceTableSwitchTime = 0xFFFFFFFF;
    if(5!=TestZeroNum(&RAM[RAM_COEF_PERIODPRICE_CHANGETIME+0], 5))
    {
        // AA  如果是0，则表示不用切换，或者已经切换  AA
        if(3==TestDayMonthYear(&RAM[RAM_COEF_PERIODPRICE_CHANGETIME+2])
            +TestHour(RAM[RAM_COEF_PERIODPRICE_CHANGETIME+1])
            +TestMinute(RAM[RAM_COEF_PERIODPRICE_CHANGETIME+0]))
        {
            ulChangeTime=mmHHDDMMYYToLong(&RAM[RAM_COEF_STEPPRICE_CHANGETIME+0]);
            //if(ulNowMinTime<ulChangeTime)
            //不用比较，因为切换完自动清零。不比较也正好用来掉电时间的补切换
            {
                ulNext2PriceTableSwitchTime = ulChangeTime;
            }
        }
    }       
    /*else
    {
        ulNext2PriceTableSwitchTime = 0xFFFFFFFF;
    }*/
    // AA ======== 切换2 套运行费率---->END ======== AA   
#endif

}

/*==================================================================
//函数名：  GetCurDayTableNum
//作者：    陶治国
//日期：    
//功能：    取得当前日时段表号
//          可以在初始化、参数更改后、日期中天变化 时调用一次
//输入参数：无
//输出参数：无
//返回值：  无
//=================================================================*/
void GetCurDayTableNum(void)
{
    LOGTRACE("GetCurDayTableNum\n");
    //读取节假日数据到内存，并计算出当前节假日
    PublicHolidayDataInit();        //读取节假日数据到内存
    GetNextHoliday();               //取得当前节假日
    //取得当前日时段表号，根据优先次序:节假日、公休日、普通时区表
    GetDayTableNumFromSeasonNum();  //取得当前时区表对应日时段表 
    GetDayTableNumFromWeekDay();    //取得当前公休日日时段表
    GetDayTableNumFromHoliday();    //取得当前节假日日时段表
}

void PriceSwitchMode(void)
{
    uchar ucCurValue, ucNextValue, ucCount;
    ulong uiAddr;
    uchar ucTemp;
    u16 y0,y1,y;
    uchar isTwoSetChannged=0;
    
    if(ucPriceSwitchModeMinute == RSOFT_RTC_MINUTE)
        return;
    ucPriceSwitchModeMinute = RSOFT_RTC_MINUTE;

    //各2套参数切换
    isTwoSetChannged = Do2SheetSwitch();

    //过天重新算日时段表、或者两套配置切换了，则重新计算
    if( (ucPriceSwitchMOdeDay != RSOFT_RTC_DAY) || (isTwoSetChannged == 1) )
    {
        //PriceSwitchModeParaInit();
        GetCurDayTableNum();
        ucPriceSwitchMOdeDay = RSOFT_RTC_DAY;
    }

    //计算当前的时段
    if((STATUS_DAYTABLE>ucPriceSwitchDayTableMax)||(0==STATUS_DAYTABLE))
        STATUS_DAYTABLE=1;
    uiAddr=STATUS_DAYTABLE-1;
    uiAddr=uiAddr*DLT_DAY_TABLE_DATA_LEN;
    
    if(2==STATUS_DAYTABLEPOINT)
    {
        uiAddr=uiAddr+RAM_SEASON2_DAYTABLE1_PERIOD01;
        ucCount=RAM[RAM_CURRENT_DAYTABLECHANGE2NUM+STATUS_DAYTABLE-1];
    }
    else
    {
        uiAddr=uiAddr+RAM_SEASON1_DAYTABLE1_PERIOD01;
        ucCount=RAM[RAM_CURRENT_DAYTABLECHANGE1NUM+STATUS_DAYTABLE-1];
    }
    if(ucCount>ucPriceSwitchPeriodMax)
    {
        ucCount=0;
    }
    ucCurValue=0;
    ucNextValue=0;
    if(0==ucCount)
    {
        STATUS_PRICE=1;
    }
    else
    {
        if(1==ucCount)
        {
            ucCurValue=0;
        }
        else
        {
            ucCount--;
            ucCurValue=ucCount;
            y=RSOFT_RTC_HOUR*256+RSOFT_RTC_MINUTE;
            for(ucTemp=0;ucTemp<ucCount;ucTemp++)
            {
                y0=RAM[uiAddr+DLT_DAY_PIECE_DATA_LEN*ucTemp+2]*256+RAM[uiAddr+DLT_DAY_PIECE_DATA_LEN*ucTemp+1];
                y1=RAM[uiAddr+DLT_DAY_PIECE_DATA_LEN*(ucTemp+1)+2]*256+RAM[uiAddr+DLT_DAY_PIECE_DATA_LEN*(ucTemp+1)+1];
                if(y0<=y1)
                {
                    if((y>=y0)&&(y<y1))
                    {
                        ucCurValue=ucTemp;
                        ucNextValue=ucTemp+1;
                        break;
                    }
                }
                else
                {
                    if((y>=y0)||(y<y1))
                    {
                        ucCurValue=ucTemp;
                        ucNextValue=ucCurValue;
                        break;
                    }
                }
            }
        }
        STATUS_PRICE=RAM[uiAddr+DLT_DAY_PIECE_DATA_LEN*ucCurValue+0];
    }
    
    if(0==TestOnePrice(STATUS_PRICE))
    {
        STATUS_PRICE=1;
    }
    ucCurrentPriceHEX=ValueHexFromBcd(STATUS_PRICE);
    //ucCurrentPriceHEX=STATUS_PRICE;

    if(uiLastDayPieceAddr!=(uiAddr+DLT_DAY_PIECE_DATA_LEN*ucCurValue+0))
    {
        uiLastDayPieceAddr=(uiAddr+DLT_DAY_PIECE_DATA_LEN*ucCurValue+0);
        SetPluseValue(PULSE_MODE_DAYTABLECHANGE,800);
        ucDemandPriceDemandTimeChange=GAL_YES;
    }
#if(CONFIG_METER_STEP_MODE==CONFIG_METER_STEP_MODE_ENABLE)
    // 查询费率和阶梯电价
    GetPeriodPriceNumFromPeriodNum(ucCurrentPriceHEX);
    // 查询阶梯和阶梯电价
    GetStepPrice();
#endif
    //MTRACE("Cur set season=%d, daytable=%d\n", STATUS_SEASONTABLEPOINT, STATUS_DAYTABLEPOINT);
    //MTRACE("Cur season=%d, daytable=%d, price=%d\n", STATUS_SEASONNUM, STATUS_DAYTABLE, STATUS_PRICE);

}

