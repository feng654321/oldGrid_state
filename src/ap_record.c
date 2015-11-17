#define AP_RECORD_GLOBALS
#include "common.h"


/*const uchar TB_RECORD_CHANNEL_STATUS[6]=
{
//  --1--   --2--   --3--   --4--   --5--   --6--
    0xFE,   0xFD,   0xFB,   0xF7,   0xEF,   0xDF        
};*/

const uchar TB_RECORD_CHANNEL_STATUS[6]=
{
//  --1--   --2--   --3--   --4--   --5--   --6--
    0x01,   0x02,   0x04,   0x08,   0x10,   0x20        
};

/*End of ybf on 2010-7-24 15:21 V1.0*/


/*********************************************************************
功能：  本文件做负荷记录功能
范围：  应用层直接调用
注释：  无
作者：  张龙
版本：  V1.0
最后修改时间：2009-01-19
修改说明：创建
********************************************************************/
uchar ucRecordModeMinute;
//uchar ucRecordModeMinute1,ucRecordModeMinute2,ucRecordModeMinute3,ucRecordModeMinute4;
//uchar ucRecordModeMinute5,ucRecordModeMinute6,ucRecordModeMinute7,ucRecordModeMinute8;

uchar ucRecordStep;
uchar ucRecordPointResetStatus;
const uchar TB_RECORD_ENABLE_ADDBIT[8]=
{
    0x01,0x02,0x04,0x08,0x10,0x20,0x00,0x00
};

//延时n毫秒
void Delayms(u16 n)
{ 
    n = n*4;
    for(;n!=0;n--)
        Delay1mS();
}

void RecordPointResetByStep(void);


/*********************************************************************************
 * Function:       RecordClrByType
 * Description:    根据通道,清除对应通道的负荷记录数据
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:           
        ucType ：负荷记录通道类别  （<CON_RECORD_CHANNELS_MAX）

 * Output:         
 * Return:         
 * Others:         
 *******************************************************************************/ 
void RecordClrByType( void)
{
    ulong TempAddr;
    
    
    memset(&Wr_data[0],0,CON_RECORD_FLASH_1FLASH_SECTOR);
    #if 0
    WriteDataDirect(&Wr_data[0], EPL_RECORD_STATUS_START, 8);
    WriteDataDirect(&Wr_data[0], EPL_RECORD_LASTTIME_START, 5);
    #endif
    SetRecordStatusPointStart(0);
    SetRecordStatusPointEnd(0);
    SetRecordStatusLastTime(0);
    // 清Sector状态
    WriteDataDirect(&Wr_data[0], EPL_RECORD_SECTOR_STATUS, 256);
    
    //擦除负荷记录第一个Block   
    TempAddr = RecordChangePointtoAddr(0);
    WaitClrFlash(TempAddr);
    ClrFlashMode();
    //ucSystemBusy += 2;
}


/*Start of ybf on 2010-7-24 15:21 V1.0*/

ulong RecordGetNowPoint(void)
{
    ulong ulTemp=COMM_RECORDPTR_NULL;
    
    #if 0
    if(!ReadDataDirect(EPL_RECORD_CHANNELS01_STATUS,4,(uchar *)&ulTemp))
    {
        if(!ReadDataDirect(EPL_RECORD_CHANNELS01_STATUS,4,(uchar *)&ulTemp))
        {
            return COMM_RECORDPTR_NULL;
        }
    }
    #endif

//#pragma diag_remark=Pa082
    ulTemp = ulGetRecordStatusPointStart;
//#pragma diag_default=Pa082
    if(ulTemp>=CON_RECORD_DATA_RECORD_MAX)
        ulTemp=0;
    return ulTemp;

}


ulong RecordGetLastPoint(void)
{
    ulong ulTemp=COMM_RECORDPTR_NULL;

    #if 0
    if(!ReadDataDirect(EPL_RECORD_CHANNELS01_STATUS+4,4,(uchar *)&ulTemp))
    {
        if(!ReadDataDirect(EPL_RECORD_CHANNELS01_STATUS+4,4,(uchar *)&ulTemp))
        {
            return COMM_RECORDPTR_NULL;
        }
    }
    #endif

//#pragma diag_remark=Pa082
    ulTemp = ulGetRecordStatusPointEnd;
//#pragma diag_default=Pa082

    if(ulTemp>=CON_RECORD_DATA_RECORD_MAX)
        ulTemp=0;
    return ulTemp;

}


void RecordSaveNowPoint(ulong ulNowPoint);
void RecordSaveNowPoint(ulong ulNowPoint)
{
    #if 0
    WriteDataDirect((uchar *)&ulNowPoint, EPL_RECORD_CHANNELS01_STATUS, 4);
    #endif
    if(ulNowPoint>=CON_RECORD_DATA_RECORD_MAX)                          // 防止指针超限
      ulNowPoint=0;
    SetRecordStatusPointStart(ulNowPoint);
}

void RecordSaveLastPoint(ulong ulLastPoint);
void RecordSaveLastPoint(ulong ulLastPoint)
{
    #if 0
    WriteDataDirect((uchar *)&ulLastPoint, EPL_RECORD_CHANNELS01_STATUS+4, 4);
    #endif
    
    SetRecordStatusPointEnd(ulLastPoint);
}



/*********************************************************************************
 * Function:       
 * Description:    
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:          
 * Output:         
 * Return:         
 * Others:         
        
 首先记住以下关键信息：
     每page有256字节，只能存储9条负荷数据，用Page_Len表示页长； 
     每个Block有16个page，共16*256=4K字节，用Block_Len表示Block长，第一个page用于存储Block信息，第二个page开始存储负荷数据，每个Block能存储15*9=135条负荷数据；
     假定每条记录长度为Record_Len，指针为PTR，记录区开始地址StAddr
 于是有：
     PTR/135可以找到对应的Block；
     PTR%135表示对应Block中的第几条记录；
     （PTR%135）/9则是该Block中的哪一个page；
     （PTR%135）%9表示对应Page中的第几条记录。
 
 
 有了以上信息之后，我们便可以很容易的得出寻址公式：
 StAddr + （PTR/135）*Block_Len+ （（PTR%135）/9）*Page_Len + （（PTR%135）%9）*Record_Len
 
 *******************************************************************************/ 

ulong RecordChangePointtoAddr(ulong ulNowPoint)
{
    ulong ulTemp;
    ulong ucPageInBlock;
    ulong ucBlockPiont;

    ucBlockPiont =  ulNowPoint/CON_RECORD_FLASH_1BLOCK_RECORD;                              // 第几个block
    ucPageInBlock = ulNowPoint%CON_RECORD_FLASH_1BLOCK_RECORD;                              // block里第几条记录

    ulTemp = FL1_METER_RECORD_STARTADDR + ucBlockPiont*CON_RECORD_FLASH_1BLOCK_BYTE;    // block 地址
    ulTemp += ((ucPageInBlock+CON_RECORD_FLASH_1PAGE_RECORD)/CON_RECORD_FLASH_1PAGE_RECORD)*CON_RECORD_FLASH_1PAGE_BYTE;    //page地址
    ulTemp += (ucPageInBlock%CON_RECORD_FLASH_1PAGE_RECORD)*CON_RECORD_FLASH_1RECORD_BYTE;  // 记录地址
    
    return ulTemp;
}

/*End of ybf on 2010-7-24 15:22 V1.0*/


/*Start of ybf on 2010-7-24 16:2 V1.0*/

void RecordChangeLastPoint(u16 NowBlockNum);
void RecordChangeLastPoint(u16 NowBlockNum)
{
    u16 LastBlkNum;
    ulong ulLastPiont;
    
    NowBlockNum += 1;                                           // 头指针的下一block
    if(NowBlockNum>=CON_RECORD_FLASH_1FLASH_BLK_NUM)
        NowBlockNum = 0;
    ulLastPiont=RecordGetLastPoint();                       // 获取尾指针   
    if(ulLastPiont == COMM_RECORDPTR_NULL)
        return ;
    LastBlkNum=ulLastPiont/CON_RECORD_FLASH_1BLOCK_RECORD;      // 尾指针所在Block

    if(NowBlockNum == LastBlkNum)                                       //当头指针的下一block就是尾指针所在区域时，调整尾指针
    {
        LastBlkNum += 1;
        if(LastBlkNum>=CON_RECORD_FLASH_1FLASH_BLK_NUM)
            LastBlkNum = 0;
        ulLastPiont = LastBlkNum*CON_RECORD_FLASH_1BLOCK_RECORD;
        RecordSaveLastPoint(ulLastPiont);
    }
}





// 擦除头指针的下一block，并返回尾指针
void RecordClrNextBlock(ulong ulNowPoint);
void RecordClrNextBlock(ulong ulNowPoint)
{
    ulong uiTemp1;
    ulong ulTempPtr,ulTempAddr;
        
    
    uiTemp1=ulNowPoint/CON_RECORD_FLASH_1BLOCK_RECORD;          // 头指针所在Block
    uiTemp1 += 1;                                               // 下一block
    if(uiTemp1>=CON_RECORD_FLASH_1FLASH_BLK_NUM)
        uiTemp1 = 0;
    ulTempPtr = uiTemp1*CON_RECORD_FLASH_1BLOCK_RECORD;
            
    /*---------- 擦除下一个block-------------*/
    ulTempAddr=RecordChangePointtoAddr(ulTempPtr);
    WaitClrFlash(ulTempAddr);
    ClrFlashMode();
}
/*End of ybf on 2010-7-24 16:2 V1.0*/


/*Start of ybf on 2010-7-24 16:0 V1.0*/
ulong RecordReadCurrentBlockTime(ulong ulNowPoint);
ulong RecordReadCurrentBlockTime(ulong ulNowPoint)
{
    ulong ulTemp,ulRrturn=COMM_RECORDPTR_NULL;
        
    ulTemp=ulNowPoint/CON_RECORD_FLASH_1BLOCK_RECORD;
    ulTemp=ulTemp*CON_RECORD_FLASH_1BLOCK_BYTE+CON_RECORD_FLASH_BLOCK_STARTTIME_ADDR+FL1_METER_RECORD_STARTADDR;
    ReadDataDirect(ulTemp,3,(uchar *)&ulRrturn);
    return ulRrturn;
}

// 判断下一block是否被擦除
// 返回全f，表示被擦除
ulong IsNextBlockErased(ulong ulNowPoint);
ulong IsNextBlockErased(ulong ulNowPoint)
{
    ulong ulTemp,ulRrturn=COMM_RECORDPTR_NULL;

    ulNowPoint = (ulNowPoint + CON_RECORD_FLASH_1BLOCK_RECORD)%CON_RECORD_DATA_RECORD_MAX;
    ulTemp=ulNowPoint/CON_RECORD_FLASH_1BLOCK_RECORD;
    ulTemp=ulTemp*CON_RECORD_FLASH_1BLOCK_BYTE+CON_RECORD_FLASH_BLOCK_STARTTIME_ADDR+FL1_METER_RECORD_STARTADDR;
    ReadDataDirect(ulTemp,4,(uchar *)&ulRrturn);
    return ulRrturn;
}


/*End of ybf on 2010-7-24 16:0 V1.0*/



//时间回调引起的清部分负荷记录
// block内回调，删除部分负荷记录，指针指向下一block
// 跨block回调，删除目的block内的部分负荷记录，擦除下一block，指针指向下一block
void RecordClrByTimeBack(ulong OldNowPtr,ulong NewNowPtr);
void RecordClrByTimeBack(ulong OldNowPtr,ulong NewNowPtr)
{
    uchar NumInBlock1,NumInBlock2;
    uchar ClrRecordNum;
    uchar EraseFlag=0;
    //uchar flag;
    u16 BlockNum1,BlockNum2;
    ulong ulTempAddr;
                    //SetLedAlarm();      //4 红灯
    BlockNum1 = OldNowPtr/CON_RECORD_FLASH_1BLOCK_RECORD; // 旧的头指针所在的Block
    BlockNum2 = NewNowPtr/CON_RECORD_FLASH_1BLOCK_RECORD; // 新的头指针所在的Block
    
    NumInBlock1 = OldNowPtr%CON_RECORD_FLASH_1BLOCK_RECORD; // 旧的头指针所在的Block中的第几条
    NumInBlock2 = NewNowPtr%CON_RECORD_FLASH_1BLOCK_RECORD; // 新的头指针所在的Block中的第几条
    
    if( BlockNum1 == BlockNum2 )                          // 同1个block内的时间回调
    {
        ClrRecordNum = NumInBlock1-NumInBlock2+1;
    }
    else                                                  // 跨block的时间回调
    {
        ClrRecordNum = CON_RECORD_FLASH_1BLOCK_RECORD-NumInBlock2;
        EraseFlag = 1;
    }
    
    // 清block信息中被删除的负荷记录
    ulTempAddr = ReadGetBlockAddr(BlockNum2);
    ulTempAddr += 1;           // block信息地址
    memset(&Wr_data[0],0xFF,ClrRecordNum);
    WriteDataDirect(&Wr_data[0],ulTempAddr+NumInBlock2,ClrRecordNum);   // 清block信息地址内删除的负荷记录信息

    // 调整头指针，指向下一block的首地址，并保存指针
    BlockNum2 = (BlockNum2+1)%CON_RECORD_FLASH_1FLASH_BLOCK;
    NewNowPtr = ReadGetPtr(0,BlockNum2);
    #if 0
    WriteDataDirect((uchar*)&NewNowPtr, EPL_RECORD_STATUS_START,4);
    #endif
    SetRecordStatusPointStart(NewNowPtr);
    
    // 跨block回调，需擦除头指针下一个block内容
    if( EraseFlag == 1 )
    {
        ulTempAddr = ReadGetBlockAddr(BlockNum2);
        WaitClrFlash(ulTempAddr);
        ClrFlashMode();
        //ucSystemBusy += 2;
    }
}

//向后搜索相同时间点上的最后的记录指针
ulong SearchSameTimeAfter(ulong ulPtr);
ulong SearchSameTimeAfter(ulong ulPtr)
{
    uchar temp=CON_RECORD_CHANNELS_MAX;
    ulong ulTempTime1,ulTempTime2;
    ulong ulTempPtr;

    ulTempTime1 = ReadLoadTimeByPtr(ulPtr);
    ulTempPtr = ulPtr;
    while(temp)
    {
        ulTempPtr = (ulTempPtr+1)%CON_RECORD_DATA_RECORD_MAX;
        ulTempTime2 = ReadLoadTimeByPtr(ulTempPtr);
        if((ulTempTime1 != ulTempTime2)||(ReadChannelNumByPtr(ulTempPtr)==0))
            return ulTempPtr;
        temp--;
    }
    return ulPtr;
}

void RecordPointResetByStep(void)
{
    uchar ucFlgErr,ucStatus,i;
    u16 BlockNum;
    ulong TempPtr=0,TempPtr1=0,TempPtr2,ulTempMaxPoint,ulTempMinPoint,ulTempMidPoint;
    ulong TempTime1,TempTime2,ulNowTime,ulMaxTime,ulMinTime,ulMidTime;
    ulong ulLastPiont,ulRecentPiont;
    ulong TempAddr;

    ulNowTime = ulNowMinTime;
//#pragma diag_remark=Pa082
    TempTime1 = ulGetRecordStatusLastTime;
//#pragma diag_default=Pa082
    // 如果更改后的时间在最近1次记录之后，则不需要调整
    // 所以，可以自动退出 
    if(ulNowTime>=TempTime1)
        return;
    
    ucFlgErr=GAL_NO;
    // 如果读不出指针，则退出
    #if 0
    if(0==ReadDataDirect(EPL_RECORD_STATUS_START, 8, &Wr_data[0]))
    {
        ucFlgErr=GAL_YES;
    }
    memcpy((uchar * )&ulRecentPiont, (uchar *) &Wr_data[0], 4);
    memcpy((uchar * )&ulLastPiont, (uchar *) &Wr_data[4], 4);
    #endif
    ulRecentPiont=RecordGetNowPoint();
    ulLastPiont = RecordGetLastPoint();
    ulRecentPiont = (ulRecentPiont+CON_RECORD_DATA_RECORD_MAX-1)%CON_RECORD_DATA_RECORD_MAX;
    // 指针异常错误则退出
    if((ulRecentPiont>=CON_RECORD_DATA_RECORD_MAX)||(ulLastPiont>CON_RECORD_DATA_RECORD_MAX)||(ulRecentPiont==ulLastPiont))
    {
        ucFlgErr=GAL_YES;
    }
    
    // 最近1次的时间
    ulMaxTime=ReadLoadTimeByPtr(ulRecentPiont);
    //ulTemp=(ulPoint+CON_RECORD_BLOCK_MAX-ulCount+1)%CON_RECORD_BLOCK_MAX;
    //最远1次的时间
    ulMinTime=ReadLoadTimeByPtr(ulLastPiont);
    // 如果最早的时间都大于当前系统时间，则所有数据清零
    if((ulMinTime>ulNowTime)||(ulNowTime>ulMaxTime))
    {
        ucFlgErr=GAL_YES;
    }
    if(ulMinTime>ulMaxTime)
    {
        ucFlgErr=GAL_YES;
    }
    
    if(GAL_YES==ucFlgErr)
    {
        RecordClrByType();
        return;
    }
        
    if( ulRecentPiont < ulLastPiont )     //两头部分有效
    {
        ulRecentPiont += CON_RECORD_DATA_RECORD_MAX;
    }
        
    // 以下使用二分法查找目的时间点的指针
    ulTempMaxPoint=ulRecentPiont;
    ulTempMinPoint=ulLastPiont;
    ucFlgErr=0;
    while(ulTempMinPoint<=ulTempMaxPoint)
    {
        TempPtr=(ulTempMaxPoint+ulTempMinPoint)/2;
        ulTempMidPoint=TempPtr%CON_RECORD_DATA_RECORD_MAX;    // 中间指针
        ucStatus=ReadChannelNumByPtr(ulTempMidPoint);       // 读记录通道
        // 异常搜索，如记录被擦除等，跳过删除区继续搜索
        if(ucStatus == 0)                                  
        {
            BlockNum = ulTempMidPoint/CON_RECORD_FLASH_1BLOCK_RECORD;
            //读取当前block最近的有效记录指针和时间
            TempAddr = ReadGetBlockAddr(BlockNum)+1;
            ReadDataDirect(TempAddr,CON_RECORD_FLASH_1BLOCK_RECORD,&Wr_data[0]);
            for(i=CON_RECORD_FLASH_1BLOCK_RECORD-1;i !=0; i-- )
            {
                if((Wr_data[i] !=0 )&&(Wr_data[i] !=0xFF ))
                {
                    TempPtr1 = ReadGetPtr(i,BlockNum);
                    TempTime1 = ReadLoadTimeByPtr(TempPtr1);
                    break;
                }
            }
            
            // 读取下一block的起始指针和时间
            BlockNum = (BlockNum+1)%CON_RECORD_FLASH_1FLASH_BLK_NUM;
            TempPtr2 = ReadGetPtr(0,BlockNum);
            TempTime2 = ReadLoadTimeByPtr(TempPtr2);
            
            // 当前时间== 当前block最近的有效记录时间，
            // 将当前block最近的有效记录指针作为目的指针
            if(ulNowTime == TempTime1)
            {
                TempPtr = TempPtr1;
                break;
            }
            
            // 当前时间== 下一block起始记录时间，
            // 将下一block起始记录指针作为目的指针
            if(ulNowTime == TempTime2)
            {
                TempPtr = TempPtr2;
                break;
            }
            
            // 当前时间< 当前block最近的有效记录时间，
            // 将当前block最近的有效记录指针作为搜索上限指针，继续搜索
            if(ulNowTime<TempTime1)
            {
                ulTempMaxPoint = TempPtr1;
            }
            
            // 当前时间>下一block起始记录时间，
            // 将下一block起始记录指针作为搜索下限指针，继续搜索
            else if(ulNowTime>TempTime2)
            {
                ulTempMinPoint = TempPtr2;
            }
            
            // 当前时间> 当前block最近的有效记录时间 且当前时间<下一block起始记录时间，
            // 将下一block起始记录指针作为目的指针
            else if((ulNowTime>TempTime1)&&(ulNowTime<TempTime2))
            {
                TempPtr = TempPtr1;
                break;
            }

        }
        // 正常搜索
        else                                                
        {
        
            ulMidTime = ReadLoadTimeByPtr(ulTempMidPoint);               // 中间指针对应记录的时间
            if(ulNowTime>ulMidTime)
            {
                ulTempMinPoint=TempPtr+1;
            }
            else
            {
                if(ulNowTime<ulMidTime)
                {
                    ulTempMaxPoint=TempPtr-1;
                    TempPtr--;
                }
                else
                {
                    ucFlgErr=0x81;
                    break;
                }
            }
        }
        ucFlgErr++;
        if(ucFlgErr>25)
        {
            ucFlgErr=0xf1;
            break;
        }
    }
    if(ucFlgErr>0xf0)
    {
        RecordClrByType();
        return;
    }
    
    //  当前的指针
    TempPtr=TempPtr%CON_RECORD_DATA_RECORD_MAX;
    //  重新推导出最近1次的数据保存时间 
    ulMaxTime=ReadLoadTimeByPtr(TempPtr);
    SetRecordStatusLastTime(ulMaxTime);
    #if 0
    LongTommHHDDMMYY(ulMaxTime,&Wr_data[0]);
    WriteDataDirect(&Wr_data[0],EPL_RECORD_LASTTIME_START,5);
    #endif
    
    TempPtr = SearchSameTimeAfter(TempPtr);
    RecordClrByTimeBack(ulRecentPiont,TempPtr);        // 时间回调引起的删除部分负荷记录
}

/*********************************************************************************
 * Function:       change page or not
 * Description:    
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:          
 * Output:         1:change   0:not
 * Return:         
 * Others:         
 *******************************************************************************/ 
/*Start of ybf on 2010-7-24 15:23 V1.0*/
uchar RecordIsNeedNextPage(ulong ulNowPoint);
uchar RecordIsNeedNextPage(ulong ulNowPoint)
{
    if(8==(ulNowPoint%CON_RECORD_FLASH_1PAGE_RECORD))
    {
        return 1;
    }
    return 0;
}
/*End of ybf on 2010-7-24 15:23 V1.0*/


void RecordInit(void )
{
    ucRecordStep=0;
    ucRecordPointResetStatus = 0;
    ucRecordModeMinute = RSOFT_RTC_MINUTE;
    MTRACE("RecordInit0  0x%08x, 0x%08x, 0x%08x\n", ulGetRecordStatusLastTime, ulGetRecordStatusPointStart, ulGetRecordStatusPointEnd);
    /*
    //既然ulGetRecordStatusLastTime等三个数据本来就是保存，何必再从EPL读
    {
        ulong t1,t2,t3;

        ReadDataDirect(EPL_RECORD_CHANNELS01_LASTTIME, 5+8 , &Wr_data[0]);
        t1 = mmHHDDMMYYToLong(&Wr_data[0]);
        memcpy((u8*)&t2, &Wr_data[5], 4);
        memcpy((u8*)&t3, &Wr_data[9], 4);
    	SetRecordStatusLastTime(t1);
    	SetRecordStatusPointStart(t2);
    	SetRecordStatusPointEnd(t3);
        MTRACE("RecordInit1  0x%08x, 0x%08x, 0x%08x\n", ulGetRecordStatusLastTime, ulGetRecordStatusPointStart, ulGetRecordStatusPointEnd);
    }*/
}

void SaveLoadPtrToEE(void)
{
    ulong t1,t2,t3;
    MTRACE("SaveLoadPtrToEE  0x%08x, 0x%08x, 0x%08x\n", ulGetRecordStatusLastTime, ulGetRecordStatusPointStart, ulGetRecordStatusPointEnd);
    
//#pragma diag_remark=Pa082
    t1 = ulGetRecordStatusLastTime;
//#pragma diag_default=Pa082
    LongTommHHDDMMYY(t1, &Wr_data[0]);
    
    t2 = RecordGetNowPoint();
    t3 = RecordGetLastPoint();
    memcpy(&Wr_data[5], (u8*)&t2, 4);
    memcpy(&Wr_data[9], (u8*)&t3, 4);
    WriteDataDirect(&Wr_data[0], EPL_RECORD_CHANNELS01_LASTTIME, 5+8);
    /*{
        //回读测试代码
        ReadDataDirect(EPL_RECORD_CHANNELS01_LASTTIME, 5+8 , &Wr_data[0]);
        t1 = mmHHDDMMYYToLong(&Wr_data[0]);
        memcpy((u8*)&t2, &Wr_data[5], 4);
        memcpy((u8*)&t3, &Wr_data[9], 4);
        MTRACE("SaveLoadPtrToEE1  0x%08x, 0x%08x, 0x%08x\n", t1, t2, t3);
    }*/
}

void RecordPointReset(void)
{
    ucRecordPointResetStatus=CON_RECORD_CHANNELS_MAX;
}

void  RecordTimetoPoint(uchar *ucPoint)
{
    ulong ulTime;
    ulTime=ulNowMinTime;
    memcpy(ucPoint, (uchar*) &ulTime, 3);
}

/*Start of ybf on 2010-7-24 15:23 V1.0*/
void RecordChangeBlockStatus(ulong ulNowPoint,uchar ucStatus);
void RecordChangeBlockStatus(ulong ulNowPoint,uchar ucStatus)
{
    ulong ulTemp;
    uchar ucTempStatus;

    // bock状态字节地址
    ulTemp=ulNowPoint/CON_RECORD_FLASH_1BLOCK_RECORD;
    ulTemp=ulTemp*CON_RECORD_FLASH_1BLOCK_BYTE+CON_RECORD_FLASH_BLOCK_BLOCKSTATUS_ADDR+FL1_METER_RECORD_STARTADDR;
    
    if(GAL_YES==ReadDataDirect(ulTemp,1,&ucTempStatus))
    {
        if((ucTempStatus | ucStatus) != ucTempStatus)                       // 状态字节发生变化才写
        {
            ucTempStatus=ucTempStatus | ucStatus;
            WriteDataDirect(&ucTempStatus, ulTemp, 1);
        }
    }
}

// 记录block信息内各个通道号
void RecordChannelNo(ulong ulRecStatPtr,uchar ucStatus);
void RecordChannelNo(ulong ulRecStatPtr,uchar ucStatus)
{
    ulong ulTemp1,ulTemp2;
    uchar i;
    int k=0;
    uchar ChannelBuff[COMM_LOADRECORD_CHENNL_NUM];
        //uchar bit[6]={0x01,0x02,0x04,0x08,0x10,0x20};
    // bock状态字节地址
    ulTemp1=ulRecStatPtr/CON_RECORD_FLASH_1BLOCK_RECORD;
    ulTemp1=FL1_METER_RECORD_STARTADDR+ulTemp1*CON_RECORD_FLASH_1BLOCK_BYTE+CON_RECORD_FLASH_BLOCK_RECORDSTATUS_ADDR;   // 指针所在block的通道号的存储地址
    ulTemp2=ulRecStatPtr%CON_RECORD_FLASH_1BLOCK_RECORD;                                        // block内第几条
    ulTemp1 += ulTemp2;                                                                     // 指针指向的通道记录地址                                                   

    // 先将通道号按顺序缓存
    for(i=0;i<COMM_LOADRECORD_CHENNL_NUM;i++)
    {
        if((ucStatus & TB_RECORD_CHANNEL_STATUS[i]) == TB_RECORD_CHANNEL_STATUS[i] )
            ChannelBuff[k++] = TB_RECORD_CHANNEL_STATUS[i];
    }
    // 将通道号一次性写入Flash
    WriteDataDirect(&ChannelBuff[0], ulTemp1, k);
}

void RecordChangeSectorStatus(ulong LstNowPtr,ulong ulNowPoint,uchar *ucStatus);
void RecordChangeSectorStatus(ulong LstNowPtr,ulong ulNowPoint,uchar *ucStatus)
{
    uchar ucTempStatus[2];
    uchar ChangeSectorFlg;
    ulong ulTemp0,ulTemp1;

    if(*(ucStatus) == 0)
        return;
    
    ucTempStatus[0] = 0;
    ucTempStatus[1] = 0;
    ChangeSectorFlg = 0;

    // 铁电中Sector  状态信息字节地址
    ulTemp0=LstNowPtr/CON_RECORD_FLASH_1SECTOR_RECORD;
    ulTemp1=ulNowPoint/CON_RECORD_FLASH_1SECTOR_RECORD;
    // 判断是否换sector
    if((ulTemp0 != ulTemp1) &&(*(ucStatus+1) != 0))
    {
        ChangeSectorFlg = 1;
        ulTemp1=EPL_RECORD_SECTOR_STATUS+ulTemp1;
    }
    ulTemp0=EPL_RECORD_SECTOR_STATUS+ulTemp0;
    if(GAL_YES==ReadDataDirect(ulTemp0,1,&ucTempStatus[0]))
    {
        // 如果先一个sector发生改变，同时写两个字节
        if((ucTempStatus[0] | (*ucStatus)) != ucTempStatus[0])                      // 状态字节发生变化才写
        {
            ucTempStatus[0]=ucTempStatus[0] | (*ucStatus);
            ucTempStatus[1]=*(ucStatus+1);
            WriteDataDirect(&ucTempStatus[0], ulTemp0, 1+ChangeSectorFlg);
        }
        // 如股先一个sector未发生改变，只写当前sector
        else if(ChangeSectorFlg)
        {
            ucTempStatus[1]=*(ucStatus+1);
            WriteDataDirect(&ucTempStatus[1], ulTemp1, 1);
        }
    }
}

/*End of ybf on 2010-7-24 15:23 V1.0*/
//ulStatPtr 记录前指针，ulNowPoint 记录后指针，ucTempStauts  状态字节，ulDataAddr  数据地址
void RecordLoadInfoAndData(ulong ulStatPtr,ulong ulNowPoint,uchar ucTempStauts,ulong ulDataAddr,uchar ucBufferLen);
void RecordLoadInfoAndData(ulong ulStatPtr,ulong ulNowPoint,uchar ucTempStauts,ulong ulDataAddr,uchar ucBufferLen)
{
    
    WriteDataDirect(&Wr_data[0], ulDataAddr, ucBufferLen);      // 先写已缓存的数据
    RecordChangeBlockStatus(ulNowPoint,ucTempStauts);               // 更新block首page中写状态字节
    RecordChannelNo(ulStatPtr,ucTempStauts);                        // 在block信息内保存通道号
}


void RecordLastRecordTime(void);
void RecordLastRecordTime(void)
{
    ulong TempTime=0;
    
    TempTime = ulNowMinTime;
    SetRecordStatusLastTime(TempTime);
    #if 0
    WriteDataDirect(&Wr_data[0], EPL_RECORD_CHANNELS01_LASTTIME, 5);
    #endif
}

/*End of ybf on 2010-7-24 15:25 V1.0*/

/*Start of ybf on 2010-7-24 16:1 V1.0*/
void  RecordWriteCurrentBlockTime(ulong ulNowPoint,uchar * ulPointTime);
void  RecordWriteCurrentBlockTime(ulong ulNowPoint,uchar * ulPointTime)
{
    ulong ulTemp;
    ulTemp=ulNowPoint/CON_RECORD_FLASH_1BLOCK_RECORD;
    ulTemp=ulTemp*CON_RECORD_FLASH_1BLOCK_BYTE+CON_RECORD_FLASH_BLOCK_STARTTIME_ADDR+FL1_METER_RECORD_STARTADDR;
    WriteDataDirect(ulPointTime, ulTemp, 3);
    Delay(OPERATE_FLASH_WAIT);
}
/*End of ybf on 2010-7-24 16:1 V1.0*/


/*Start of ybf on 2010-7-24 15:22 V1.0*/
void RecordSetChannel01Data(uchar * ucPoint);
void RecordSetChannel01Data(uchar * ucPoint)
{
    // VOLTAGE
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+3+0]=(RAM[RAM_CURRENT_V_A+2]<<4)+ (RAM[RAM_CURRENT_V_A+1]>>4);
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+3+1]=(RAM[RAM_CURRENT_V_A+3]<<4)+ (RAM[RAM_CURRENT_V_A+2]>>4);

    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+5+0]=(RAM[RAM_CURRENT_V_B+2]<<4)+ (RAM[RAM_CURRENT_V_B+1]>>4);
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+5+1]=(RAM[RAM_CURRENT_V_B+3]<<4)+ (RAM[RAM_CURRENT_V_B+2]>>4);

    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+7+0]=(RAM[RAM_CURRENT_V_C+2]<<4)+ (RAM[RAM_CURRENT_V_C+1]>>4);
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+7+1]=(RAM[RAM_CURRENT_V_C+3]<<4)+ (RAM[RAM_CURRENT_V_C+2]>>4);

    // CURRENT
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+9+0]=(RAM[RAM_CURRENT_I_A+1]<<4)+ (RAM[RAM_CURRENT_I_A+0]>>4);
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+9+1]=(RAM[RAM_CURRENT_I_A+2]<<4)+ (RAM[RAM_CURRENT_I_A+1]>>4);
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+9+2]=(RAM[RAM_CURRENT_I_A+3]<<4)+ (RAM[RAM_CURRENT_I_A+2]>>4);

    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+12+0]=(RAM[RAM_CURRENT_I_B+1]<<4)+ (RAM[RAM_CURRENT_I_B+0]>>4);
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+12+1]=(RAM[RAM_CURRENT_I_B+2]<<4)+ (RAM[RAM_CURRENT_I_B+1]>>4);
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+12+2]=(RAM[RAM_CURRENT_I_B+3]<<4)+ (RAM[RAM_CURRENT_I_B+2]>>4);

    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+15+0]=(RAM[RAM_CURRENT_I_C+1]<<4)+ (RAM[RAM_CURRENT_I_C+0]>>4);
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+15+1]=(RAM[RAM_CURRENT_I_C+2]<<4)+ (RAM[RAM_CURRENT_I_C+1]>>4);
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+15+2]=(RAM[RAM_CURRENT_I_C+3]<<4)+ (RAM[RAM_CURRENT_I_C+2]>>4);

    // FREQ
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+18]=RAM[RAM_CURRENT_FREQ_A+0];
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+19]=RAM[RAM_CURRENT_FREQ_A+1];
    
}

void RecordSetChannel02Data(uchar * ucPoint);
void RecordSetChannel02Data(uchar * ucPoint)
{
    // KW
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+3+0]=RAM[RAM_CURRENT_KW_ALL+1]; 
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+3+1]=RAM[RAM_CURRENT_KW_ALL+2]; 
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+3+2]=RAM[RAM_CURRENT_KW_ALL+3]; 

    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+6+0]=RAM[RAM_CURRENT_KW_A+1]; 
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+6+1]=RAM[RAM_CURRENT_KW_A+2]; 
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+6+2]=RAM[RAM_CURRENT_KW_A+3]; 

    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+9+0]=RAM[RAM_CURRENT_KW_B+1]; 
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+9+1]=RAM[RAM_CURRENT_KW_B+2]; 
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+9+2]=RAM[RAM_CURRENT_KW_B+3]; 

    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+12+0]=RAM[RAM_CURRENT_KW_C+1]; 
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+12+1]=RAM[RAM_CURRENT_KW_C+2]; 
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+12+2]=RAM[RAM_CURRENT_KW_C+3]; 

    // KVAR
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+15+0]=RAM[RAM_CURRENT_KVAR_ALL+1]; 
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+15+1]=RAM[RAM_CURRENT_KVAR_ALL+2]; 
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+15+2]=RAM[RAM_CURRENT_KVAR_ALL+3]; 

    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+18+0]=RAM[RAM_CURRENT_KVAR_A+1]; 
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+18+1]=RAM[RAM_CURRENT_KVAR_A+2]; 
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+18+2]=RAM[RAM_CURRENT_KVAR_A+3]; 

    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+21+0]=RAM[RAM_CURRENT_KVAR_B+1]; 
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+21+1]=RAM[RAM_CURRENT_KVAR_B+2]; 
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+21+2]=RAM[RAM_CURRENT_KVAR_B+3]; 

    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+24+0]=RAM[RAM_CURRENT_KVAR_C+1]; 
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+24+1]=RAM[RAM_CURRENT_KVAR_C+2]; 
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+24+2]=RAM[RAM_CURRENT_KVAR_C+3]; 
}

void RecordSetChannel03Data(uchar * ucPoint);
void RecordSetChannel03Data(uchar * ucPoint)
{
    // FACTOR
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+3+0]=RAM[RAM_CURRENT_FACTOR_ALL+2];
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+3+1]=RAM[RAM_CURRENT_FACTOR_ALL+3];

    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+5+0]=RAM[RAM_CURRENT_FACTOR_A+2];
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+5+1]=RAM[RAM_CURRENT_FACTOR_A+3];

    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+7+0]=RAM[RAM_CURRENT_FACTOR_B+2];
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+7+1]=RAM[RAM_CURRENT_FACTOR_B+3];

    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+9+0]=RAM[RAM_CURRENT_FACTOR_C+2];
    ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+9+1]=RAM[RAM_CURRENT_FACTOR_C+3];

}

void RecordSetChannel04Data(uchar * ucPoint);
void RecordSetChannel04Data(uchar * ucPoint)
{
    // KWH +
    memcpy(&ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+3], &RAM[RAM_KWH_F_ALL+1], 4);
    // KWH -
    memcpy(&ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+7], &RAM[RAM_KWH_R_ALL+1], 4);
    // KVARH C1
    memcpy(&ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+11], &RAM[RAM_KVARH_C1_ALL+1], 4);
    // KVARH C2
    memcpy(&ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+15], &RAM[RAM_KVARH_C2_ALL+1], 4);
}

void RecordSetChannel05Data(uchar * ucPoint);
void RecordSetChannel05Data(uchar * ucPoint)
{
    // KVARH Q1
    memcpy(&ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+3], &RAM[RAM_KVARH_Q1_ALL+1], 4);
    // KVARH Q2
    memcpy(&ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+7], &RAM[RAM_KVARH_Q2_ALL+1], 4);
    // KVARH Q3
    memcpy(&ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+11], &RAM[RAM_KVARH_Q3_ALL+1], 4);
    // KVARH Q4
    memcpy(&ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+15], &RAM[RAM_KVARH_Q4_ALL+1], 4);
}

void RecordSetChannel06Data(uchar * ucPoint);
void RecordSetChannel06Data(uchar * ucPoint)
{
    // KW ALL
    memcpy(&ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+3], &RAM[RAM_CURRENT_DEMAND_KW_TOTAL+1], 3);
    // KVAR ALL
    memcpy(&ucPoint[CON_RECORD_DATA_HAVE_CHANNEL+6], &RAM[RAM_CURRENT_DEMAND_KVAR_TOTAL+1], 3);

}
/*End of ybf on 2010-7-24 15:22 V1.0*/


/*********************************************************************************
 * Function:       put  record data to buffer
 * Description:    
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:         
 * Output:         
 * Return:         
 * Others:         
 一条负荷记录数据格式:
 时间+ 通道号 + 负荷时间
 *******************************************************************************/ 
/*Start of ybf on 2010-7-24 15:22 V1.0*/
void RecordSetChannelData(uchar ChannelNo,uchar *ucBuffer);
void RecordSetChannelData(uchar ChannelNo,uchar *ucBuffer)
{
    RecordTimetoPoint(&ucBuffer[0]);

    if (GAL_YES==CON_RECORD_DATA_HAVE_CHANNEL)
    {
        ucBuffer[3+0]=TB_RECORD_CHANNEL_STATUS[ChannelNo];
    }

    switch(ChannelNo)
    {
        case 0:
            RecordSetChannel01Data(&ucBuffer[0]);
            break;
        case 1:
            RecordSetChannel02Data(&ucBuffer[0]);
            break;
        case 2:
            RecordSetChannel03Data(&ucBuffer[0]);
            break;      
        case 3:
            RecordSetChannel04Data(&ucBuffer[0]);
            break;
        case 4:
            RecordSetChannel05Data(&ucBuffer[0]);
            break;
        case 5:
            RecordSetChannel06Data(&ucBuffer[0]);
            break;
        default:
            break;
    }
}
/*End of ybf on 2010-7-24 15:22 V1.0*/


uchar RecordIsNeedRecord(uchar ucType)
{
    u16 uiTimeBlock;
    u16 uiTimeNow;
    ulong ulTimeLast,ulTimeNow;
    
    uiTimeBlock=Bcd2DataToInt(&RAM[RAM_CHARGE_RECORD_1_TIME+ucType*2]);
    // AA  如果时间间隔为0--表示不记录  AA
    if(0==uiTimeBlock)
    {
        return GAL_NO;
    }
    // AA  如果负荷标志位0--表示不记录  AA
    if(0==(RAM[RAM_CHARACTER_CHARGE_MODE]&TB_RECORD_ENABLE_ADDBIT[ucType]))
    {
        return GAL_NO;
    }
    uiTimeNow=ValueHexFromBcd(RSOFT_RTC_HOUR);
    uiTimeNow=uiTimeNow*60 + ValueHexFromBcd(RSOFT_RTC_MINUTE);
    // AA 时间间隔正确   AA
    if(0==(uiTimeNow%uiTimeBlock))
    {
        /*Start of ybf on 2010-8-16 11:34 V1.0*/
        #if 0
        if(1==ReadDataDirect(EPL_RECORD_LASTTIME_START, 5 ,&ucTimeBuff[0]))
        #endif
        /*End of ybf on 2010-8-16 11:34 V1.0*/
        {
//#pragma diag_remark=Pa082
            ulTimeLast = ulGetRecordStatusLastTime;
//#pragma diag_default=Pa082
            ulTimeNow=ulNowMinTime;
            if(ulTimeNow>ulTimeLast)
            {
                return GAL_YES;
            }
            else
            {
                ulTimeNow=ulTimeLast-ulTimeNow;
                if(ulTimeNow>30)
                {
                    return GAL_YES;
                }
            }
        }
    }
    return GAL_NO;
}
uchar ucRecordModeWaitTime;

/*********************************************************************************
 * Function:        load  record
 * Description:    save load data in Flash
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:          
 * Output:         
 * Return:         
 * Others:         base  on  25-series  DataFlash chip
 *******************************************************************************/ 
uchar RecordMode(void)
{
    uchar ucTempStauts[2];  // 通道信息，bit0~bit5 分别代表通道1~6,
    uchar ucBufferLen;      //缓存数据长度
    uchar uchannel;
    uchar ucRecFlag=0;
    uchar L_ChangePageFlg;  // 换页标志
    u16  uiBlockNum1,uiBlockNum2; 
    ulong ulDataAddr;       // load data address in Flash
    ulong ulNowPoint,RecStatPtr;        // recent pionter of record 
    ulong Lul_TempPtr;

    if(ucSystemResetOk < 3)
        return DLT_RET_SUCC;
    
    //if(GAL_NO==ucSystemBusy)
    {
        //if((ucRecordPointResetStatus)&&(0==ucRecordStep))
        if(ucRecordPointResetStatus)
        {
            RecordPointResetByStep();
            //ucSystemBusy=ucSystemBusy+2;
            ucRecordPointResetStatus=0;
        }
    }
    
    if(ucRecordModeMinute != RSOFT_RTC_MINUTE) 
    {
        
        //if(GAL_NO==ucSystemBusy)
        {
            if(ucAde7878CfModeTime<CON_ADE7878_CFMODE_TIME_DEAL)
            {
                return DLT_RET_SUCC;
            }
            if(ucRecordModeWaitTime<15)
            {
                ucRecordModeWaitTime++;
            }
            else
            {
                if(isFlashBusy)
                    return DLT_RET_UNFINISHED;
                ulNowPoint=RecordGetNowPoint();                         // 获取头指针
                if(ulNowPoint == COMM_RECORDPTR_NULL)
                    return DLT_RET_SUCC;
                RecStatPtr=ulNowPoint;                  // 记录的起始指针，可以一次性记录多条
                Lul_TempPtr = ulNowPoint;
                uiBlockNum1 = ((ulNowPoint+CON_RECORD_DATA_RECORD_MAX-1)%CON_RECORD_DATA_RECORD_MAX)/CON_RECORD_FLASH_1BLOCK_RECORD;
                ulDataAddr=RecordChangePointtoAddr(ulNowPoint);         // 指针得到地址
                memset(&Wr_data[0],0, 168);                         // 缓存区初始化
                ucTempStauts[0] = 0;                              // 通道信息字节初始化
                ucTempStauts[1] = 0;
                ucBufferLen=0;
                L_ChangePageFlg = 0;
//                Lul_TempPtr = 0;


                // 依次查询6个通道是否记录负荷
                for(uchannel=0;uchannel<COMM_LOADRECORD_CHENNL_NUM;uchannel++)
                {
                    if(GAL_YES==RecordIsNeedRecord(uchannel))                               // 查询单通道是否满足负荷记录的条件
                    {
                        ucRecFlag = 0x01;
                        
                        RecordSaveNowPoint(ulNowPoint+1);                               // 保存头指针
                        ucTempStauts[L_ChangePageFlg]=ucTempStauts[L_ChangePageFlg] |TB_RECORD_CHANNEL_STATUS[uchannel];    // 状态字节
                        RecordSetChannelData(uchannel,&Wr_data[ucBufferLen]);           // 负荷数据放到缓存区
                        ucBufferLen=ucBufferLen+CON_RECORD_FLASH_1RECORD_BYTE;  
                        if(GAL_YES==RecordIsNeedNextPage(ulNowPoint))                       // 是否需要换页处理
                        {
                            L_ChangePageFlg = 1;
                            RecordLoadInfoAndData(RecStatPtr,ulNowPoint,ucTempStauts[0],ulDataAddr,ucBufferLen);    // 记录负荷信息和负荷数据
                            // 另起一页，相关参数初始化                     
                            ucBufferLen=0;
                            //ucTempStauts=0;
                            memset(&Wr_data[0],0, 168);                     // 缓存区初始化
                            RecStatPtr=ulNowPoint+1;
                            if(RecStatPtr>=CON_RECORD_DATA_RECORD_MAX)                          // 防止指针超限
                                RecStatPtr=0;
                            ulDataAddr=RecordChangePointtoAddr(RecStatPtr); 
                        }
                        ulNowPoint++;                       
                        if(ulNowPoint>=CON_RECORD_DATA_RECORD_MAX)                          // 防止指针超限
                            ulNowPoint=0;
                    }
                }
                // 6个通道查询完成，判断是否需要写数据到Flash
                if((L_ChangePageFlg == 0) && ((ucTempStauts[0]&0x3F) != 0x00))
                {
                    RecordLoadInfoAndData(RecStatPtr,ulNowPoint,ucTempStauts[0],ulDataAddr,ucBufferLen);        // 记录负荷信息和负荷数据
                } 
                else if((L_ChangePageFlg == 1) && ((ucTempStauts[1]&0x3F) != 0x00))
                {
                    RecordLoadInfoAndData(RecStatPtr,ulNowPoint,ucTempStauts[1],ulDataAddr,ucBufferLen);        // 记录负荷信息和负荷数据
                }
                // 有记录
                if(ucRecFlag == 0x01)
                {
                    RecStatPtr = ulNowPoint-1;
                    if(ulNowPoint==0)                                                   // 防止指针超限
                        RecStatPtr=CON_RECORD_DATA_RECORD_MAX-1;                    
                    uiBlockNum2 = RecStatPtr/CON_RECORD_FLASH_1BLOCK_RECORD;
                    RecordLastRecordTime();                                             // 保存最近一次记录时间

                    // 当出现在一新的Block记录时，记录Block开始时间
                    if((uiBlockNum1 != uiBlockNum2))    //||(0xff000000==RecordReadCurrentBlockTime(RecStatPtr))                    // 如果block尚未记录时间，记录block时间
                    {
                        RecordTimetoPoint(&Wr_data[0]);                         // 将时间转换为min
                        RecordWriteCurrentBlockTime(RecStatPtr,&Wr_data[0]);    //保存时间
                    }
                    
                    RecordChangeLastPoint(uiBlockNum2);                         // 更新尾指针
                    
                    // 每记录一次，判断下一block是否被擦除，如果没被擦除，擦除下一block
                    if(0!=IsNextBlockErased(RecStatPtr))
                    {
                        RecordClrNextBlock(RecStatPtr);                         // 擦除下一Block
                        //ucSystemBusy += 2;
                    }
                    
                    RecordChangeSectorStatus(Lul_TempPtr,ulNowPoint,&ucTempStauts[0]);              // 更新铁电中Sector 状态字节
                    FLG_SAVE_LOAD = 1;
                }
                ucRecordModeMinute = RSOFT_RTC_MINUTE;
                ucRecordModeWaitTime = 0;
            }
        } 
    }
    return DLT_RET_SUCC;
}






