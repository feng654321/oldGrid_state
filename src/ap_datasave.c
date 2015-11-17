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

// ���ݶ�ʱ�����־��ʼ��
void SaveDataInit(void)
{
    g_SaveDataFlag.ucData = 0;
    SavePowerPerMin = 0xFF;
    g_KwhSavedMode = KWH_SAVED_MODE_INIT;
}

// ��E2PROM�м��������¼������ۼ�ʱ�䵽RAM
// ��������: �ϵ�
// �м���17���ֽڵ�RAM�˷�
void LoadEventAccTime(void)
{
    ReadDataDirect(EPL_VOLTAGE_ALL_MONITOR_STAT_BLOCK_START, 236,&RAM[RAM_VOLTAGE_ALL_MONITOR_STAT_BLOCK_START]);
    FLG_ACPOWER_STATUS = fGetAuxPowerDownStatus;
    FLG_POWER_STATUS = fGetPowerDownStatus;
    FLG_ALL_LOSSVOLTAGE_STATUS = fGetAllLostVoltageStatus;
}

// ��E2PROM�б��������¼������ۼ�ʱ��
// ��������: ���硢ÿСʱ��21����37�뱣��
void SaveEventAccTime(void)
{
    WriteDataDirect(&RAM[RAM_VOLTAGE_ALL_MONITOR_STAT_BLOCK_START], EPL_VOLTAGE_ALL_MONITOR_STAT_BLOCK_START, 236);
}

UN_U8_PARAM g_SaveDataFlag;
uchar SavePowerPerMin;
// ���ݶ�ʱ�洢����
// �˺��������ݴ洢�ǹ�ԼҪ��ģ���ʵʱ���в�ǿ�����ҵ����ʱ�򻹻�һ�����档���Ե�������һ������
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
        //ÿ1���ӱ���һ��
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
                        //����E2����ʱ��
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
    // --AA ȱ��:ÿ���ϵ�ucSaveStep������0�����ʱ�����12����ÿ�ζ��ӱ��������ʼ���Ľ����ڳ�ʼ��ʱ��ucSaveStep���ֵ AA--
    switch(ucSaveStep)
    {
        case 0:     // �������ݴ洢
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
            
        case 1:     // �������ݴ洢
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
    
    
        case 2:     // �¼����ݴ洢
            if((RSOFT_RTC_MINUTE >= 0x21) && (RSOFT_RTC_SECOND >= 0x37))
            {
                // �¼��ۼ�ʱ��洢���ڵ�ѹ���ʱ��ÿ���Ӷ��仯�����Կ��ǲ���Ҫ��־λ
                //if(FLG_SAVE_EVENT)
                {
                    SaveEventAccTime();
                    FLG_SAVE_EVENT = 0;
                }
                ucSaveStep++;
            }            
            break;

        case 3:     // ��ʱ���渺�ɼ�¼ָ��
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
            
        case 4:     // ��ʱ����BKP���� BAK1
            if((RSOFT_RTC_MINUTE >= 0x27)&&(RSOFT_RTC_SECOND >= 0x13))
            {
                VirtualBPKRegSave(BAK_BKP_DATA_BAK1_START);
                ucSaveStep++;
            }
            break;
            
        case 5:     // ��ʱ����BKP���� BAK2
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

