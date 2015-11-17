//============================================================================
//  File Name: ap_datastorage.c
//
//  Copyright PAX Hangzhou 2011.  All rights reserved.
//
//  Description:
//      数据存取接口
//
//  Modification History:
//      $Id:  Exp $
//      $Log: $
//      Revision 1.0 Create by Taozhiguo in 2011.04.28
//============================================================================
#ifndef __AP_DATASTORGE_C__
#define __AP_DATASTORGE_C__
#include "common.h"

extern void EspDisplayOfOp(const string *StrShow, uchar persent);
    
#if(MEM_ERR_RECORD_ENABLE == GAL_YES)
u16 MemErr[MEM_TYPE_MAX][2];

void MemErrCount(uchar isRead,uchar isRWOK,uchar ucMemoryType);
void MemErrCount(uchar isRead,uchar isRWOK,uchar ucMemoryType)
{
    uchar ucType=0;
    
    if(ucMemoryType >= MEM_TYPE_MAX)     
        return;
    ucType = ucMemoryType;
    // 读出错
    if(isRead == 1)
    {
        MemErr[ucType][0]++;
    }
    // 写出错
    else
    {
        MemErr[ucType][1]++;
    }

}

void MemErrCountResume(void);
void MemErrCountResume(void)
{
    ReadDataDirect(BAK_DATA_RWERR_START, sizeof(MemErr), (uchar*)&MemErr);
}

void MemErrCountSave(void);
void MemErrCountSave(void)
{
    WriteDataDirect((uchar*)&MemErr, BAK_DATA_RWERR_START, sizeof(MemErr));
}

#endif 

    
void MemoryStatusInit(void)
{
#if(GAL_YES == BKP_VIRTUAL_FEATURE)
    VirtualBPKRegResume();
#endif
#if(MEM_ERR_RECORD_ENABLE == GAL_YES)
    MemErrCountResume();
#endif 

    RAM[RAM_CURRENT_MEMORY_STATUS]=0;
}

extern uchar MeterFileClr(const string *FileName, ulong FileLen);
void SetMemoryStatus(uchar isRead,uchar isRWOK,uchar ucMemoryType);
void SetMemoryStatus(uchar isRead,uchar isRWOK,uchar ucMemoryType)
{
    uchar ucMemBitmap=0;
    if(ucMemoryType > MEM_TYPE_MAX)     
        return;
    
    ucMemBitmap = (1<<ucMemoryType);
    RAM[RAM_CURRENT_MEMORY_STATUS] &= ~ucMemBitmap;
    if(0==isRWOK)
    {
        RAM[RAM_CURRENT_MEMORY_STATUS] |=ucMemBitmap;
        if(ucMemoryType == MEM_TYPE_FLASH)
        {
            if(ulRunSecTime > FLASH_FILE_BUFF_SECOND)
            {
                //假设FLASH_FILE_BUFF_SECOND时间后，mnt分区mount完毕
                static u32 flash_err_time=0;
                if(++flash_err_time > 20)
                {
                    MeterFileClr(FILE_FLASH, FILE_LEN_FLASH);
                }
            }
        }

#if(MEM_ERR_RECORD_ENABLE == GAL_YES)
        MemErrCount(isRead, isRWOK, ucMemoryType);
#endif
    }
}

uchar ReadDataDirect(ulong DataName,   u16 nLen, uchar* pSrc)
{
    uchar value;
    u16 ucTemp;
    //uchar *ucpData;
    uchar uMedia;
    uchar ucMemoryType;
    value=0;
    ucMemoryType=0;
    if(0!=nLen)
    {
        uMedia=(DataName>>24);
        DataName=DataName&0x00ffffff;
#if(CONFIG_METER_FLASH_MODE_2_AT25FLASH==CONFIG_METER_FLASH_MODE)
        if(GAL_FLASH1==uMedia)
        {
            if(DataName&0x00800000)
            {
                uMedia=GAL_FLASH2;
                DataName=0x007fffff&DataName;
            }
        }
#endif
        switch(uMedia)
        {
            case GAL_RAWRAM:
                value=1;
                for(ucTemp=0;ucTemp<nLen;ucTemp++)
                {
                    {
                        *(pSrc+ucTemp)=*(uchar*)(DataName | 0x20000000);
                    }
                    DataName++;
                }
                break;

            case GAL_BKP:
                value=1;
                value = DataName&0xf;
                value += ((DataName>>4)&0xf)*10;
                DataName=value;
                value=1;
                for(ucTemp=0;ucTemp<nLen;)
                {
                    u16 uiTemp;
                    ulong ulTemp;
                    if(DataName<11)
                        ulTemp = (ulong)(BKP_BASE + BKP_DR1 + (DataName-1)*BKP_REG_SKIP);
                    else
                        ulTemp = (ulong)(BKP_BASE + BKP_DR11 + (DataName-11)*BKP_REG_SKIP);
#if(GAL_YES == BKP_VIRTUAL_FEATURE)
                    if(IS_BKP_DR(ulTemp))
#else
                    if(IS_BKP_DR(ulTemp&0xff))
#endif                        
                    {
                        uiTemp = (*(vu16 *)ulTemp  );
                        *(pSrc+ucTemp) = (uiTemp)&0xff;
                        ucTemp++;
                        if(ucTemp<nLen)
                        {
                            *(pSrc+ucTemp) = (uiTemp>>8)&0xff;
                            ucTemp++;
                        }
                    }
                    DataName++;
                }
                break;

            case GAL_RAM:
                value=1;
                for(ucTemp=0;ucTemp<nLen;ucTemp++)
                {
                    if(DataName<CONST_RAM_LEN)
                    {
                        *(pSrc+ucTemp)=RAM[DataName];
                    }
                    DataName++;
                }
                break;
            case GAL_PWD:
                //为了兼容老表的2级密码地址，便于模块读取
                if((DataName >= 0x16A0) && (DataName+nLen <= 0x16C8))
                {
                    DataName = (EPL_PASSWORD_START & 0xffff) + (DataName - 0x16A0);
                    for(ucTemp=0;ucTemp<3;ucTemp++)
                    {
                        if(0==ReadAt24c256b(pSrc,DataName,nLen))
                        {
                            ucTemp=4;
                            value=1;
                        }
                    }
                }
                break;
#if 0                
            case GAL_FM1:
                ucMemoryType=MEM_TYPE_FM1;
                for(ucTemp=0;ucTemp<3;ucTemp++)
                {
                    if(0==ReadFm24c64a(pSrc,DataName,nLen))
                    {
                        ucTemp=4;
                        value=1;
                    }
                }
                break;
            case GAL_FM2:
                ucMemoryType=MEM_TYPE_FM2;
                for(ucTemp=0;ucTemp<3;ucTemp++)
                {
                    if(0==ReadFm24c64b(pSrc,DataName,nLen))
                    {
                        ucTemp=4;
                        value=1;
                    }
                }
                break;
            case GAL_EEPROM2:
                for(ucTemp=0;ucTemp<3;ucTemp++)
                {
                    if(0==ReadAt24c256c(pSrc,DataName,nLen))
                    {
                        ucTemp=4;
                        value=1;
                    }
                }
                break;
#endif                
            case GAL_COEFDATA:
                ReadCoefDataWithCheck(DataName+0x05000000, nLen, pSrc, 0);
                value=1;
                break;

            case GAL_EPLOCK:
                ucMemoryType=MEM_TYPE_EPL;
                for(ucTemp=0;ucTemp<3;ucTemp++)
                {
                    if(0==ReadAt24c256b(pSrc,DataName,nLen))
                    {
                        ucTemp=4;
                        value=1;
                    }
                }
                break;
                
            case GAL_DATABAK:
                ucMemoryType=MEM_TYPE_BAK;
                for(ucTemp=0;ucTemp<3;ucTemp++)
                {
                    if(0==ReadBakData(pSrc,DataName,nLen))
                    {
                        ucTemp=4;
                        value=1;
                    }
                }
                break;

            case GAL_CFG:
                value=1;
                for(ucTemp=0;ucTemp<nLen;ucTemp++)
                {
                    if(DataName<CON_SYSTEMPROFUNCTION_LEN)
                    {
                        *(pSrc+ucTemp)=SYSTEMPROGFUNCTION[DataName];
                    }
                    DataName++;
                }
                break;
            case GAL_FLASH1ADD:
                DataName=DataName+256;
            case GAL_FLASH1:
                ucMemoryType=MEM_TYPE_FLASH;
                if(isFlashBusy)
                {
                    WaitFlashFree(ucProgramFlashWait);
                }
                for(ucTemp=0;ucTemp<3;ucTemp++)
                {
                    
                    if(0 == ReadDataFromFlash( FIRST_FLASH,pSrc,DataName,nLen))                     
                    {
                    
                        ucTemp=4;
                        value=1;
                    }
                }
                
                break;

#if(CONFIG_METER_FLASH_MODE==CONFIG_METER_FLASH_MODE_2_AT25FLASH)                
            case GAL_FLASH2ADD:
                DataName=DataName+256;
            case GAL_FLASH2:
                ucMemoryType=MEM_TYPE_FLASH2;
                
                if(isFlashBusy)
                {
                    WaitFlashFree(ucProgramFlashWait);
                }
                for(ucTemp=0;ucTemp<3;ucTemp++)
                {
                    
                    if(0 == ReadDataFromFlash( SECOND_FLASH,pSrc,DataName,nLen))                        
                    {
                    
                        ucTemp=4;
                        value=1;
                    }
                }
                break;
#endif                
            /*case GAL_ADE7758:
                
                value=ReadADReg((u16)(0xffff&DataName), nLen, pSrc);
                break;
            case GAL_POWERBUFFER:
                ucpData=(uchar*)&ulPowerBuffer[0];
                for(ucTemp=0;ucTemp<nLen;ucTemp++)
                {
                    *(pSrc+ucTemp)=*(ucpData+ucTemp);
                }
                value=1;
                break;
            case GAL_DEMANDBUFFER:
                ucpData=(uchar*)&ulKwPerMinute[0];
                for(ucTemp=0;ucTemp<nLen;ucTemp++)
                {
                    *(pSrc+ucTemp)=*(ucpData+ucTemp);
                }
                value=1;
                break;
            case GAL_DEMANDMINUTEBUFFER:
                ucTemp=DataName>>16;
                ucpData=(uchar*)&uiDemandClacBuffer[ucTemp][0];
                for(ucTemp=0;ucTemp<nLen;ucTemp++)
                {
                    *(pSrc+ucTemp)=*(ucpData+ucTemp);
                }
                value=1;
                break;*/
            case GAL_CFLASH:
                value=1;
                memcpy(pSrc, TB_CON_METER_WARE_INF[DataName&0xFF],METER_CON_INF_STR_LENGTH);
                #if(PROFUNCTION_METER_TYPE != PROFUNCTION_METER_TYPE_ALL)
                #if(METER_CON_INF_STR_LENGTH >= 27)
                    if(((EN_WARE_INF)(DataName&0xFF) == METER_SW_VER_INF_ID))
                    {
                        ucTemp = (PROFUNCTION_METER_TYPE & 0xF0) >>4;
                        if(ucTemp >= 0x0A)
                            pSrc[24] = 'A' + ucTemp-0x0A;
                        else
                            pSrc[24] = '0' + ucTemp;
                        
                        ucTemp = (PROFUNCTION_METER_TYPE & 0x0F);
                        if(ucTemp >= 0x0A)
                            pSrc[25] = 'A' + ucTemp-0x0A;
                        else
                            pSrc[25] = '0' + ucTemp;
                        pSrc[26] = 0;
                        pSrc[27] = 0;
                    }
                #endif
                #endif
                break;
            case GAL_RECORD:
                value=1;
                //DataName=GetCurrentRecordAddr((DataName>>16),0x0000ffff&DataName);
                // DataName=DataName&0x00ffffff;
                //value= ReadDataDirect( DataName,   nLen,  pSrc);
                break;
            case GAL_MEDIA_ERR:
                value=1;
                memset(pSrc, 0x00, nLen);
                break;
#ifdef VRAM_ENABLE
            case 0x55:
                value=1;
                for(ucTemp=0;ucTemp<nLen;ucTemp++)
                {
                    //if(DataName<CONST_RAM_LEN)
                    {
                        *(pSrc+ucTemp)=VRAM[DataName];
                    }
                    DataName++;
                }
                break;

#endif                
            default:
                value=0;
            break;
        }
    }
    SetMemoryStatus(1, value,ucMemoryType); 
    
    return value;
}

uchar WriteDataDirect(const uchar* pSrc, ulong DataName,   u16 nLen)
{
    uchar value;
    u16 ucTemp;
    uchar uMedia;
    uchar ucMemoryType;
    value=0;
    ucMemoryType=0;
    
    if(0!=nLen)
    {
        uMedia=(DataName>>24);
        DataName=DataName&0x00ffffff;
#if(CONFIG_METER_FLASH_MODE_2_AT25FLASH==CONFIG_METER_FLASH_MODE)
        if(GAL_FLASH1==uMedia)
        {
            if(DataName&0x00800000)
            {
                uMedia=GAL_FLASH2;
                DataName=0x007fffff&DataName;
            }
        }
#endif
        switch(uMedia)
        {
#if(CONFIG_METER_SW_DEBUG_MODE == GAL_YES)
            case GAL_RAWRAM:
                value=1;
                for(ucTemp=0;ucTemp<nLen;ucTemp++)
                {
                    //if(DataName<CONST_RAM_LEN)
                    {
                        *((uchar*)(DataName | 0x20000000))=*(pSrc+ucTemp);
                    }
                    DataName++;
                }
                break;
#endif       

            case GAL_BKP:
                value=1;
                value = DataName&0xf;
                value += ((DataName>>4)&0xf)*10;
                DataName=value;
                value=1;
                for(ucTemp=0;ucTemp<nLen;)
                {
                    u16 uiTemp;
                    ulong ulTemp;
                    if(DataName<11)
                        ulTemp = (ulong)(BKP_BASE + BKP_DR1 + (DataName-1)*BKP_REG_SKIP);
                    else
                        ulTemp = (ulong)(BKP_BASE + BKP_DR11 + (DataName-11)*BKP_REG_SKIP);
#if(GAL_YES == BKP_VIRTUAL_FEATURE)
                    if(IS_BKP_DR(ulTemp))
#else
                    if(IS_BKP_DR(ulTemp&0xff))
#endif                        
                        
                    {
                        uiTemp = *(pSrc+ucTemp);
                        ucTemp++;
                        if(ucTemp<nLen)
                        {
                            uiTemp += (*(pSrc+ucTemp))*256;
                            ucTemp++;
                        }
                        
                        (*(vu16 *)ulTemp ) = uiTemp;
                    }
                    DataName++;
                }
                break;

#ifdef VRAM_ENABLE
            case 0x55:
                value=1;
                for(ucTemp=0;ucTemp<nLen;ucTemp++)
                {
                    //if(DataName<CONST_RAM_LEN)
                    {
                        VRAM[DataName]=*(pSrc+ucTemp);
                    }
                    DataName++;
                }
                break;
                
            case GAL_PWD: 
                if(0==vVarSet(DataName, pSrc, nLen))
                {
                    ucTemp=4;
                    value=1;
                }                
                break;
#endif                
            case GAL_RAM:
                value=1;
                for(ucTemp=0;ucTemp<nLen;ucTemp++)
                {
                    if(DataName<CONST_RAM_LEN)
                    {
                        RAM[DataName]=*(pSrc+ucTemp);
                    }
                    DataName++;
                    
                    #if 0
                    if((DataName>=0x000002C0)&&(DataName<=0x00000844))
                    {
                        value--;
                        value=1;
                    }
                    #endif
                }
                break;
#if 0                
            case GAL_FM1:
                ucMemoryType=MEM_TYPE_FM1;
                for(ucTemp=0;ucTemp<3;ucTemp++)
                {
                    if(0==WriteFm24c64a(DataName,pSrc,nLen))
                    {
                        ucTemp=4;
                        value=1;
                    }
                }
                break;
            case GAL_FM2:
                ucMemoryType=MEM_TYPE_FM2;
                for(ucTemp=0;ucTemp<3;ucTemp++)
                {
                    if(0==WriteFm24c64b(DataName,pSrc,nLen))
                    {
                        ucTemp=4;
                        value=1;
                    }
                }
                break;
            case GAL_EEPROM2:
                for(ucTemp=0;ucTemp<3;ucTemp++)
                {
                    if(0==WriteAt24c256c(DataName,pSrc,nLen))
                    {
                        ucTemp=4;
                        value=1;
                    }
                }
                break;
            case GAL_EEPROM3:
                for(ucTemp=0;ucTemp<3;ucTemp++)
                {
                    if(0==WriteAt24c256d(DataName,pSrc,nLen))
                    {
                        ucTemp=4;
                        value=1;
                    }
                }
                break;
#endif                
            case GAL_COEFDATA:
                WriteCoefDataWithSync(pSrc, DataName+0x05000000, nLen);
                value=1;
                break;
                
            case GAL_EPLOCK:
                ucMemoryType=MEM_TYPE_EPL;
                for(ucTemp=0;ucTemp<3;ucTemp++)
                {
                    #if 0
                    if((DataName>=0x000002C0)&&(DataName<=0x0000189E))
                    {
                        value--;
                        value++;
                    }
                    #endif
                    if(0==WriteAt24c256b(DataName,pSrc,nLen))
                    {
                        ucTemp=4;
                        value=1;
                    }
                }
                break;
                
            case GAL_DATABAK:
                ucMemoryType=MEM_TYPE_BAK;
                for(ucTemp=0;ucTemp<3;ucTemp++)
                {
                    #if 0
                    if((DataName>=0x000002C0)&&(DataName<=0x0000189E))
                    {
                        value--;
                        value++;
                    }
                    #endif
                    if(0==WriteBakData(DataName,pSrc,nLen))
                    {
                        ucTemp=4;
                        value=1;
                    }
                }
                break;

            case GAL_FLASH1ADD:
                DataName=DataName+256;
            case GAL_FLASH1:
                ucMemoryType=MEM_TYPE_FLASH;
                if(isFlashBusy)
                {
                    WaitFlashFree(ucProgramFlashWait);
                }
                for(ucTemp=0;ucTemp<3;ucTemp++)
                {
                    if(0 == WriteDataToFlash( FIRST_FLASH,pSrc,DataName,nLen))
                    {
                        ucTemp=4;
                        value=1;
                    }
                }
                
                break;
#if(CONFIG_METER_FLASH_MODE==CONFIG_METER_FLASH_MODE_2_AT25FLASH)                
            case GAL_FLASH2ADD:
                DataName=DataName+256;
            case GAL_FLASH2:
                ucMemoryType=MEM_TYPE_FLASH;
                if(isFlashBusy)
                {
                    WaitFlashFree(ucProgramFlashWait);
                }

                for(ucTemp=0;ucTemp<3;ucTemp++)
                {
                    if(0 == WriteDataToFlash( SECOND_FLASH,pSrc,DataName,nLen))                     
                    {
                        ucTemp=4;
                        value=1;
                    }
                }
                break;
#endif                
            /*case GAL_ADE7758:
                value=WriteADReg(pSrc,(u16)(0xffff&DataName), nLen);
                break;*/
#if 0
            case GAL_KWH:
                if(5==nLen)
                {
                    if((DataName<(BYTES_KWH_TOTAL))&&(0==(DataName%5)))
                    {
                        memcpy(&RAM[DataName], pSrc, 5);
                        WritePower3Copy(DataName/5);
                        value=1;
                    }
                    else
                    {
                        value=0;
                    }
                }
                else
                {
                    value=0;
                }
                break;
#endif
            case GAL_MEDIA_ERR:
                value = 1;
                break;
            default:
                value=0;
                break;
        }
    }
    SetMemoryStatus(0, value,ucMemoryType); 
    return value;

}

#if 0
uchar ReadDataDirectByComm(ulong DataName,   u16 nLen, uchar* pSrc)
{
    return (ReadDataDirect(DataName,    nLen,  pSrc));
}

uchar WriteDataDirectByComm(uchar* pSrc, ulong DataName,   u16 nLen)
{
    return ( WriteDataDirect( pSrc,  DataName,   nLen));
}
#endif
uchar WriteDataDirectEX (uchar *Src,ulong Address,ulong offset,u16 Lens)
// AA ---读取和写入的数据长度不可以超过256 字节-----   AA
{
    Address +=offset;
#if 0
    if((EPL_PREPAY_DATA_START<=Address)&&((Address+Lens)<EPL_PREPAY_DATA_START_BAK))
    {
        WriteDataDirect(Src, Address, Lens);
        WriteDataDirect(Src, Address-EPL_PREPAY_DATA_START+EPL_PREPAY_DATA_START, Lens);
        memcpy(&Wr_data[256], Src, Lens);
        for(offset=0;offset<Lens;offset++)
        {
            Wr_data[256+offset]+=0x33;
        }
        WriteDataDirect(&Wr_data[256], Address-EPL_PREPAY_DATA_START+EPL_PREPAY_DATA_START_BAK, Lens);
        return 1;
    }
    else
#endif
    {
        return WriteDataDirect(Src, Address, Lens);
    }
    
    //return 0;
}
uchar ReadDataDirectEX(uchar *Dst,ulong Address,ulong offset,u16 Lens)
// AA ---读取和写入的数据长度不可以超过128 字节-----   AA
{
    Address +=offset;
    ReadDataDirect(Address, Lens, Dst);
    return 0;
}

void EraseAllFlash(void)
{
    //ulong temp,max;
    //uchar persent=0;
    
    GetFlash_control_wait();
    
    EraseFullFlash(FIRST_FLASH);
#if (CONFIG_METER_FLASH_MODE_2_AT25FLASH ==CONFIG_METER_FLASH_MODE)
    EraseFullFlash(SECOND_FLASH);
#endif
#if 0
    max = ERASE_CHIP_DELAY*10;
    temp = max;
    EspDisplayOfOp("ERS-FLSH", 100);
    while(temp)
    {
        temp--;
        ClearWatchDog();
        SysDelayMs(100);
        LCDRefalshEn = 1;
        persent = temp*100/max;
        EspDisplayOfOp("ERS-FLSH", persent);
    }
#endif    
}

#if(CONFIG_METER_FACTORY_MODE==CONFIG_METER_FACTORY_MODE_ENABLE)
//68 AA AA AA AA AA AA 68 05 07 38 F1 35 33 33 33 33 02 16 
void InitParameterChipInfactory(uchar value)
{
    u16 uiAddr;
    MeterCmdOpStateSet(1);
    // 擦除参数存储芯片时显示'BE05-00'
    EspDisplayOfOp("BE05-00  ", 0);
    memset(&Wr_data[0], value, CON_WR_DATA_LEN_MAX);
    uiAddr = 0;
    for(uiAddr=0; uiAddr<0x8000; uiAddr += 64)
    {
        WriteAt24c256b(uiAddr, &Wr_data[0], 64);
        ClearWatchDog();
    }
    memcpy(&Wr_data[0], "BE05-00 ", 8);
    WriteAt24c256b((u16)(EPL_FACTORY_INIT_INDICATE&0xFFFF), &Wr_data[0], 8);
    DisplayFullScreen();
    MeterCmdOpStateSet(0);
}
//68 AA AA AA AA AA AA 68 05 07 39 F1 35 33 33 33 33 03 16 
void InitParameterChipInfactory_withMeterAbout(uchar value)
{
    u16 uiAddr, uiPerlen=0, uiAddrMax=0;
    MeterCmdOpStateSet(1);
    // 擦除参数存储芯片时显示'BE06-00'
    EspDisplayOfOp("BE06-00   ", 0);
    memset(&Wr_data[0], value, CON_WR_DATA_LEN_MAX);
    uiAddr = 0;
    uiAddrMax = EPL_DATA_ADREG_START&0xFFFF;
    for(uiAddr=0; uiAddr<uiAddrMax; )
    {
        if((uiAddrMax - uiAddr) >= 64)
        {
            uiPerlen = 64;
        }
        else
        {
            uiPerlen = (uiAddrMax - uiAddr);
        }
        WriteAt24c256b(uiAddr, &Wr_data[0], uiPerlen);
        ClearWatchDog();
        uiAddr += uiPerlen;
    }
    // 保留   时钟基准、内部固定配置参数(地址固定)、计量芯片补偿数据(地址固定)
    uiAddrMax = 0x8000&0xFFFF;
    for(uiAddr=EPL_DATA_COEF_START&0xFFFF; uiAddr<uiAddrMax; )
    {
        if((uiAddrMax - uiAddr) >= 64)
        {
            uiPerlen = 64;
        }
        else
        {
            uiPerlen = (uiAddrMax - uiAddr);
        }
        WriteAt24c256b(uiAddr, &Wr_data[0], uiPerlen);
        ClearWatchDog();
        uiAddr += uiPerlen;
    }
    memcpy(&Wr_data[0], "BE06-00 ", 8);
    WriteAt24c256b(EPL_FACTORY_INIT_INDICATE&0xFFFF, &Wr_data[0], 8);
    DisplayFullScreen();
    MeterCmdOpStateSet(0);
}
//68 AA AA AA AA AA AA 68 05 07 3A F1 35 33 33 33 33 04 16 
void InitParameterInfactory(void)
{
    u16 uiAddr;
    MeterCmdOpStateSet(1);
    // 擦除参数存储芯片时显示'BE07-00'
    EspDisplayOfOp("BE07-00   ", 0);
    memset(&Wr_data[0], 00, CON_WR_DATA_LEN_MAX);
    uiAddr = 0;
    for(uiAddr=0; uiAddr<0x8000; uiAddr += 64)
    {
        WriteAt24c256b(uiAddr, &Wr_data[0], 64);
        ClearWatchDog();
    }
    
    AddDataInit();
    ClearWatchDog();

    DefaultParaInit();
    ClearWatchDog();
    memcpy(&Wr_data[0], "BE07-00 ", 8);
    WriteAt24c256b(EPL_FACTORY_INIT_INDICATE&0xFFFF, &Wr_data[0], 8);
    DisplayFullScreen();
    MeterCmdOpStateSet(0);
}
#endif

/*********************************************************************
函数：SetDataDirrect
功能：针对DataDirrect,like memset
参数：
Input:
Output:
********************************************************************/
uchar SetDataDirrect(u32 DataName, u8 ucValue, u16 nLen)
{
    u16 setLen=0;
    
    if( (DataName>>24) == GAL_RAM )
    {
        if( (DataName+nLen) < CONST_RAM_LEN )
        {
            memset(&RAM[DataName], ucValue, nLen);
            return DLT_RET_SUCC;
        }
    }
    memset(&Wr_data[0], ucValue, DATA_STORAGE_BLOCK_SIZE);
    for(setLen=0; setLen<nLen; setLen=setLen+DATA_STORAGE_BLOCK_SIZE)
    {
        if(setLen+DATA_STORAGE_BLOCK_SIZE <= nLen)
	        WriteDataDirect(&Wr_data[0], DataName+setLen, DATA_STORAGE_BLOCK_SIZE);
        else
	        WriteDataDirect(&Wr_data[0], DataName+setLen, nLen-setLen);
    }
    return DLT_RET_SUCC;
}

/*********************************************************************
函数：SetDataDirrect
功能：针对DataDirrect,like memcpy
参数：
Input:
Output:
********************************************************************/
uchar CpyDataDirrect(u32 DstDataName, u32 SrcDataName, u16 nLen)
{
    u16 setLen=0;
    
    if( (SrcDataName>>24) == GAL_RAM )
    {
        if( (SrcDataName+nLen) < CONST_RAM_LEN )
        {
            WriteDataDirect(&RAM[SrcDataName], DstDataName, nLen);
            return DLT_RET_SUCC;
        }
    }
    for(setLen=0; setLen<nLen; setLen=setLen+DATA_STORAGE_BLOCK_SIZE)
    {
        if(setLen+DATA_STORAGE_BLOCK_SIZE <= nLen)
        {
            if(1==ReadDataDirect(SrcDataName+setLen, DATA_STORAGE_BLOCK_SIZE, &Wr_data[0]))
	            WriteDataDirect(&Wr_data[0], DstDataName+setLen, DATA_STORAGE_BLOCK_SIZE);
        }
        else
        {
            if(1==ReadDataDirect(SrcDataName+setLen, nLen-setLen, &Wr_data[0]))
	            WriteDataDirect(&Wr_data[0], DstDataName+setLen, nLen-setLen);
        }
    }
    return DLT_RET_SUCC;
}
#endif

