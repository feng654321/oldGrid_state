#ifndef __AP_DATASAVE_C__
#define __AP_DATASAVE_C__

#include "common.h"

void GetLastSaveTime(STR_CALENDAR* usTime)
{
//  ulong ulTemp;
//  ulTemp=uiLastSaveTimeHigh;
//  ulTemp=(ulTemp>>16)+uiLastSaveTimeLow;
////#pragma diag_remark=Pa082
    *usTime=SecToCalendar(ulGetLastSaveTime);
////#pragma diag_default=Pa082
}

// 数据定时保存标志初始化
void SaveDataInit(void)
{
    g_SaveDataFlag.ucData = 0;
    SavePowerPerMin = 0xFF;
    g_KwhSavedMode = KWH_SAVED_MODE_INIT;
}

// 从E2PROM中加载所有事件的总累计时间到RAM
// 调用条件: 上电
// 中间有17个字节的RAM浪费
void LoadEventAccTime(void)
{
    ReadDataDirect(EPL_VOLTAGE_ALL_MONITOR_STAT_BLOCK_START, 236,&RAM[RAM_VOLTAGE_ALL_MONITOR_STAT_BLOCK_START]);
    FLG_ACPOWER_STATUS = fGetAuxPowerDownStatus;
    FLG_POWER_STATUS = fGetPowerDownStatus;
    FLG_ALL_LOSSVOLTAGE_STATUS = fGetAllLostVoltageStatus;
}

// 在E2PROM中保存所有事件的总累计时间
// 调用条件: 掉电、每小时的21分钟37秒保存
void SaveEventAccTime(void)
{
    WriteDataDirect(&RAM[RAM_VOLTAGE_ALL_MONITOR_STAT_BLOCK_START], EPL_VOLTAGE_ALL_MONITOR_STAT_BLOCK_START, 236);
}

UN_U8_PARAM g_SaveDataFlag;
uchar SavePowerPerMin;
// 数据定时存储函数
// 此函数的数据存储非规约要求的，对实时性行不强，而且掉电的时候还会一并保存。所以单次运行一种足以
uchar SaveDataMode(void)
{
    static uchar ucSaveStep = 0;
    u16 i;
    ulong ulAddr;
    uchar ucCheckSum;

//log_printf("---LXC---, %s-%d, isSystemResetUnfinisded = %d, isFlashFree=%d, SavePowerPerMin=%d, RSOFT_RTC_MINUTE=%d, RSOFT_RTC_SECOND=%d,FLG_SAVE_EC=%d\n", __FUNCTION__, __LINE__, isSystemResetUnfinisded, isFlashFree,SavePowerPerMin,RSOFT_RTC_MINUTE,RSOFT_RTC_SECOND,FLG_SAVE_EC); 

    if(isSystemResetUnfinisded)
        return DLT_RET_SUCC;
    
    if((SavePowerPerMin != RSOFT_RTC_MINUTE)&&isFlashFree)
    {
        //每1分钟保存一次
        {
            if((RSOFT_RTC_SECOND >= 3) && (FLG_SAVE_EC))
            {
                ulAddr = SetTwoTableNextPoint(TYPE_MIN_POWER_RECORD);
                if(GAL_GETTWOTABLE_ADDRERR != ulAddr)
                {
                    ucCheckSum = 0x33;
                    for(i=0; i<PT_KWH_TOTAL*BYTES_PER_PT_KWH; i++)
                    {
                        ucCheckSum += RAM[i];
                    }
                    
                    RAM[RAM_KWH_ALL_END] = ucCheckSum;
                    memcpy(&RAM[RAM_KWH_ALL_END+1], (uchar*)&ulNowSecTime, 4);
                    WriteDataDirect(&RAM[RAM_KWH_ALL_START], ulAddr, BYTES_KWH_TOTAL+5);
                    MTRACE("Kwh Min saved 0x%x!\n", g_KwhSavedMode);
//log_printf("---LXC---, %s-%d, ulNowSecTime = %lu, g_KwhSavedMode=0x%x\n", __FUNCTION__, __LINE__, ulNowSecTime, g_KwhSavedMode); 
                    if(g_KwhSavedMode == KWH_SAVED_MODE_INIT)
                    {
                        u32 ulTemp;
                        //更正E2保留时标
                        ulTemp = ulNowSecTime-2;
                        memcpy(&RAM[RAM_KWH_ALL_END+1], (uchar*)&ulTemp, 4);
                        WriteDataDirect(&RAM[RAM_KWH_ALL_END+1], EPL_KWH_ALL_END+1, 4);
                        g_KwhSavedMode = KWH_SAVED_MODE_MIN_SAVED;
                    }
                    FLG_SAVE_EC = 0;
                }
                ClrFlashMode();
                SavePowerPerMin = RSOFT_RTC_MINUTE;
                return DLT_RET_SUCC;
            }
        }
    }
    // --AA 缺点:每次上电ucSaveStep都等于0，如果时间大于12，这每次都从保存电量开始。改进是在初始化时给ucSaveStep算初值 AA--
    switch(ucSaveStep)
    {
        case 0:     // 电量数据存储
            if((RSOFT_RTC_MINUTE >= 0x12)&&(RSOFT_RTC_SECOND >= 0x20))
            {
                /*if(FLG_SAVE_EC)
                {
                    WritePower2rom(0xff);
                    WriteAlluse2rom();
                    SetPowerClacResidue();
                    FLG_SAVE_EC = 0;
                }*/
                ucSaveStep++;
            }        
            break;
            
        case 1:     // 需量数据存储
            if((RSOFT_RTC_MINUTE >= 0x17)&&(RSOFT_RTC_SECOND >= 0x23))
            {
                if(FLG_SAVE_MD)
                {
                    SaveMDByTimeStamp();
                    FLG_SAVE_MD = 0;
                }
                ucSaveStep++;
            }
            break;
    
    
        case 2:     // 事件数据存储
            if((RSOFT_RTC_MINUTE >= 0x21) && (RSOFT_RTC_SECOND >= 0x37))
            {
                // 事件累计时间存储由于电压检测时间每分钟都变化，可以考虑不需要标志位
                //if(FLG_SAVE_EVENT)
                {
                    SaveEventAccTime();
                    FLG_SAVE_EVENT = 0;
                }
                ucSaveStep++;
            }            
            break;

        case 3:     // 定时保存负荷记录指针
            if((RSOFT_RTC_MINUTE >= 0x23)&&(RSOFT_RTC_SECOND >= 0x13))
            {
                if(FLG_SAVE_LOAD)
                {
                    SaveLoadPtrToEE();
                    FLG_SAVE_LOAD = 0;
                }
                ucSaveStep++;
            }
            break;
            
        case 4:     // 定时保存BKP数据 BAK1
            if((RSOFT_RTC_MINUTE >= 0x27)&&(RSOFT_RTC_SECOND >= 0x13))
            {
                VirtualBPKRegSave(BAK_BKP_DATA_BAK1_START);
                ucSaveStep++;
            }
            break;
            
        case 5:     // 定时保存BKP数据 BAK2
            if((RSOFT_RTC_MINUTE >= 0x30)&&(RSOFT_RTC_SECOND >= 0x13))
            {
                VirtualBPKRegSave(BAK_BKP_DATA_BAK1_START);
                ucSaveStep++;
            }
            break;
            
        case 6:
            ucSaveStep = 0xff;
            break;
            
        default:
            if((RSOFT_RTC_MINUTE <= 0x05))
            {
                ucSaveStep = 0;
            }
            break;
    }
    return DLT_RET_SUCC;
}

#if(GAL_YES == BKP_VIRTUAL_FEATURE)
void VirtualBPKRegResume(void)
{
    u16 idx, uiCheckSum;
    uchar ret;
    ret = ReadDataDirect(EPL_BKP_VIRTURL_BAK_ADDR, BKP_VIRTUAL_DATA_LEN, (uchar*)(&BKP_VIRTUAL_REG[0]));
    if(ret == 1)
    {
        uiCheckSum = 0;
        for(idx=1; idx<=BKP_VIRTUAL_REG_NUM; idx++)
        {
            uiCheckSum += BKP_VIRTUAL_REG[idx];
        }
        if(uiCheckSum == BKP_VIRTUAL_REG[0])
            return;
    }
    ErrPrint("BKP data resume from EPL failed !");
    ret = ReadDataDirect(BAK_BKP_DATA_BAK1_START, BKP_VIRTUAL_DATA_LEN, (uchar*)(&BKP_VIRTUAL_REG[0]));
    if(ret == 1)
    {
        uiCheckSum = 0;
        for(idx=1; idx<=BKP_VIRTUAL_REG_NUM; idx++)
        {
            uiCheckSum += BKP_VIRTUAL_REG[idx];
        }
        if(uiCheckSum == BKP_VIRTUAL_REG[0])
            return;
    }
    ErrPrint("BKP data resume from bak1 failed !");
    ret = ReadDataDirect(BAK_BKP_DATA_BAK2_START, BKP_VIRTUAL_DATA_LEN, (uchar*)(&BKP_VIRTUAL_REG[0]));
    if(ret == 1)
    {
        uiCheckSum = 0;
        for(idx=1; idx<=BKP_VIRTUAL_REG_NUM; idx++)
        {
            uiCheckSum += BKP_VIRTUAL_REG[idx];
        }
        if(uiCheckSum == BKP_VIRTUAL_REG[0])
            return;
    }
    ErrPrint("BKP data resume from bak2 failed !");
}
void VirtualBPKRegSave(ulong ulStartAddr)
{
    u16 idx;
    BKP_VIRTUAL_REG[0] = 0;
    for(idx=1; idx<=BKP_VIRTUAL_REG_NUM; idx++)
    {
        BKP_VIRTUAL_REG[0] += BKP_VIRTUAL_REG[idx];
    }
    WriteDataDirect((uchar*)(&BKP_VIRTUAL_REG[0]), ulStartAddr, BKP_VIRTUAL_DATA_LEN);
}
#endif

#endif

