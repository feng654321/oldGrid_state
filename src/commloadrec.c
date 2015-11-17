/*********************************************************************************
    版本号     :version 0.1
    模块名       : 远程控制模块
    文件名       : CommLoadRec.c
    相关文件     : 
    文件实现功能 : 通信读负荷记录模块
    作者         : 姚徐旭
    版本         : 0.1
----------------------------------------------------------------------------------------------------------------------
    备注         : <其它说明>
---------------------------------------------------------------------------------------------------------------------
    修改记录 : 
    日 期        版本     修改人              修改内容
    YYYY/MM/DD   X.Ymai      <作者或修改者名>    <修改内容>
    YYYY/MM/DD   X.Y      <作者或修改者名>    <修改内容>
==================================================================== 
其他说明： 
*******************************************************************************/
#include "common.h"
//////////////////////////////全局变量可见区域////////////
//ulong  LoadReachTmpBuf[COMM_COMMTYPE_NUM][COMM_LOADRECORD_CHENNL_NUM];
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////读状态字，获得负荷记录中是否存在该项
//////返回COMM_TURE代表有，COMM_FAIL代表没有

uchar ReadChannelNumByPtr(ulong RecPtr);
u16 SetMultRecDataToPack (uchar *Dest,TIMEMULITIINDEX *Src);
u16  ReadNRecFmMultToBuf(ulong ulPTR,ulong ulPtr,uchar ucFameNo,uchar ucNomber,uchar *Dest);


uchar GetLoadChannelState(uchar ucChannel);
uchar GetLoadChannelState(uchar ucChannel)
{
    uchar TmpWord;
    ReadDataDirect(RAM_CHARACTER_CHARGE_MODE,1,&TmpWord);
    switch (ucChannel)
    {
        case 0x00:
            if(TmpWord&BIT0) return COMM_TURE;
            break;
        case 0x01:
            if(TmpWord&BIT1) return COMM_TURE;
            break;
        case 0x02:
            if(TmpWord&BIT2) return COMM_TURE;
            break;
        case 0x03:
            if(TmpWord&BIT3) return COMM_TURE;
            break;
        case 0x04:
            if(TmpWord&BIT4) return COMM_TURE;
            break;
        case 0x05:
            if(TmpWord&BIT5) return COMM_TURE;
            break;
        default:
            break;  
    }
    return COMM_FAIL;
}

/*********************************************************************************
 * Function:       根据block中的第几条记录获取指针
 * Description:    
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:          
 * Output:         指针
 * Return:         
 * Others:         
 *******************************************************************************/ 
ulong ReadGetPtr(uchar Num,u16 Block)
{
    return (Block*CON_RECORD_FLASH_1BLOCK_RECORD+Num);
}


// 根据记录指针，获取记录时间
ulong ReadLoadTimeByPtr(ulong RecPtr)
{
    
    ulong ulTemp;
    ulong ucPageInBlock;
    ulong ucBlockPiont;
    ulong TimeTemp=0;

    ucBlockPiont =  RecPtr/CON_RECORD_FLASH_1BLOCK_RECORD;                              // 第几个block
    ucPageInBlock = RecPtr%CON_RECORD_FLASH_1BLOCK_RECORD;                              // block里第几条记录

    ulTemp = FL1_METER_RECORD_STARTADDR + ucBlockPiont*CON_RECORD_FLASH_1BLOCK_BYTE;    // block 地址
    ulTemp += ((ucPageInBlock+CON_RECORD_FLASH_1PAGE_RECORD)/CON_RECORD_FLASH_1PAGE_RECORD)*CON_RECORD_FLASH_1PAGE_BYTE;    //page地址
    ulTemp += (ucPageInBlock%CON_RECORD_FLASH_1PAGE_RECORD)*CON_RECORD_FLASH_1RECORD_BYTE;  // 记录地址

    ReadDataDirect(ulTemp,3,(uchar *)&TimeTemp);
    return TimeTemp;

}



  /**********************************************************************
函数名：u16 ReadRecDataByPtr (uchar nChannel,uchar *Dest,u16 uiLenth,ulong ulPtr)
功能：由给定的记录指针值，读出记录数据。
传入：通道号,读出的数据存放的位置，读出的数据长度
返回：读取是否正确，COMM_TURE代表有，COMM_FAIL代表没有
**********************************************************************/
u16 ReadRecDataByPtr (uchar *Dest,ulong ulPtr,u16 uiLenth);
u16 ReadRecDataByPtr (uchar *Dest,ulong ulPtr,u16 uiLenth)
{
    ulong TmAddr=NULLDATAADDR;
        
    TmAddr=RecordChangePointtoAddr(ulPtr);
    if(TmAddr==NULLDATAADDR)  return COMM_FAIL;
    ReadDataDirect(TmAddr+4,uiLenth,Dest);
        
    return COMM_TURE;
}


/*********************************************************************************
 * Function:       查找之前是否有相同的时间点记录
 * Description:    
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:          
 * Output:         
 * Return:         
 * Others:         
 *******************************************************************************/ 
ulong SearchSameTimeBefore(ulong ulPtr)
{
    uchar temp=CON_RECORD_CHANNELS_MAX;
    ulong ulTempTime1,ulTempTime2;
    ulong ulTempPtr;

    ulTempTime1 = ReadLoadTimeByPtr(ulPtr);
    ulTempPtr = ulPtr;
    while(temp)
    {
        if(ulTempPtr == 0)
            ulTempPtr = CON_RECORD_DATA_RECORD_MAX-1;
        else
            ulTempPtr--;
        ulTempTime2 = ReadLoadTimeByPtr(ulTempPtr);
        if((ulTempTime1 != ulTempTime2)||(ReadChannelNumByPtr(ulTempPtr)==0))
            return ((ulTempPtr+1)%CON_RECORD_DATA_RECORD_MAX);

        temp--;
            
    }
    return ulPtr;
}



/**********************************************************************
函数名：void ChangeDataToTime(uchar *Dest,ulong  TimData)
功能：把表示时间的数据转换成标准时间格式
传入：转换后放的地址，被转换数据的值
**********************************************************************/
void ChangeDataToTime(uchar *Dest,ulong  TimData);
void ChangeDataToTime(uchar *Dest,ulong  TimData)
{
    LongTommHHDDMMYY(TimData,Dest);
}
/**********************************************************************
函数名：void ChangeTimeToData(uchar *Src,ulong  TimData)
功能：把表示时间的数据转换成标准时间格式
传入：转换后放的地址，被转换数据的值
返回：转换成数值的时间
**********************************************************************/
ulong ChangeTimeToData(uchar *Src);
ulong ChangeTimeToData(uchar *Src)
{
    return (mmHHDDMMYYToLong(Src));
}

 /**********************************************************************
函数名：u16 SetLoadRecDataToPack (uchar nChannel,uchar *Dest,uchar *Src,u16 uiLenth)
功能：单个通道数据读出的组帧为1包
传入：通道号,读出的数据存放的位置，记录数据地址，记录数据长度，
返回：返回组帧后的数据长度
**********************************************************************/
u16 SetLoadRecDataToPack (uchar nChannel,uchar *Dest,uchar *Src,u16 uiLenth);
u16 SetLoadRecDataToPack (uchar nChannel,uchar *Dest,uchar *Src,u16 uiLenth)
{
    uchar TmpBuffer[5],i;   ////用来存放时间的
    uchar TmpLen=0;      
    ulong TmpTime=0;
    uchar TmpCS;
    u16  TmpDataSize=0;
    TmpDataSize=uiLenth-COMM_LOADRECORD_TIME_SIZE;
    *Dest=0xA0;
    *(Dest+1)=0xA0;
    memcpy(&TmpTime,Src,COMM_LOADRECORD_TIME_SIZE);
    ChangeDataToTime(TmpBuffer,TmpTime);
    memcpy(Dest+3,TmpBuffer,5);
    TmpLen+=5;
    for(i=0;i<COMM_LOADRECORD_CHENNL_NUM;i++)
    {
        if(nChannel==i)
        {
            memcpy(Dest+3+TmpLen,Src+COMM_LOADRECORD_TIME_SIZE,TmpDataSize);
            *(Dest+3+TmpLen+TmpDataSize)=0xAA;
            TmpLen+=1+TmpDataSize;
        }
        else
        {
            *(Dest+3+TmpLen)=0xAA;
            TmpLen+=1;
        }
    }
    *(Dest+2)=TmpLen;
    TmpCS=CommCalChksum(Dest,TmpLen+3);//校验
    *(Dest+3+TmpLen)=TmpCS;
    *(Dest+3+TmpLen+1)=0xE5;
    
    return (TmpLen+5);
}

/****************************************************************
函数名为：u16 GetRecordDataLen(uchar nChannel)
功能：获得记录内容长度。
入口：通道号。
传出：返回的数据长度，0代表没有数据。
****************************************************************/
u16 GetRecordDataLen(uchar nChannel);
u16 GetRecordDataLen(uchar nChannel)
{
  if(nChannel>=COMM_LOADRECORD_CHENNL_NUM) return 0;
  
  return (stRecordBuffer[nChannel].ucBlockLen-COMM_LOADRECORD_TIME_SIZE-CON_RECORD_DATA_HAVE_CHANNEL);
}

/****************************************************************
函数名为：u16 GetRecordDataMaxLen(uchar nChannel)
功能：获得最大的能读出长度
入口：通道号。
传出：返回的数据长度，0代表没有数据。
****************************************************************/
u16 GetRecordDataMaxLen(uchar nChannel);
u16 GetRecordDataMaxLen(uchar nChannel)
{
    switch (nChannel) 
    {
        case 0x00:
            return (COMM_LOADRECORD_CHANNEL0_MAXSIZE);
        case 0x01:
            return (COMM_LOADRECORD_CHANNEL1_MAXSIZE);
        case 0x02:
            return (COMM_LOADRECORD_CHANNEL2_MAXSIZE);
        case 0x03:
            return (COMM_LOADRECORD_CHANNEL3_MAXSIZE);
        case 0x04:
            return (COMM_LOADRECORD_CHANNEL4_MAXSIZE);
        case 0x05:
            return (COMM_LOADRECORD_CHANNEL5_MAXSIZE);
        default:
            return 0;
    }   
}

// 计算block首地址
ulong ReadGetBlockAddr(u16 Block)
{
    return Block*CON_RECORD_FLASH_1BLOCK_BYTE+CON_RECORD_FLASH_BLOCK_BLOCKSTATUS_ADDR+FL1_METER_RECORD_STARTADDR;
}


/*********************************************************************************
 * Function:       搜索block
 * Description:    
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:          
 * Output:         
 * Return:         
 * Others:         
 *******************************************************************************/ 
ulong ReadSearchLastChanBlock(uchar Channel,ulong Ptr);
ulong ReadSearchLastChanBlock(uchar Channel,ulong Ptr)
{
    uchar ChanBuffer[135];
    uchar ucStaus;
    uchar i,j,lens;
    u16 BlockNum,BlockNum1,RemainBlock,NumInBlock;
    ulong ulTempAddr;
    ulong ulNowPtr;
    ulong ulTempPtr=COMM_RECORDPTR_NULL;

    ulNowPtr = RecordGetNowPoint();
    if(ulNowPtr == COMM_RECORDPTR_NULL)
        return (COMM_RECORDPTR_NULL-1);
    ulNowPtr = (ulNowPtr+CON_RECORD_DATA_RECORD_MAX-1)%CON_RECORD_DATA_RECORD_MAX;
    BlockNum1 = ulNowPtr/CON_RECORD_FLASH_1BLOCK_RECORD;    //最近指针所在block
    BlockNum = Ptr/CON_RECORD_FLASH_1BLOCK_RECORD;      // 在第几个block
    RemainBlock = CON_RECORD_FLASH_1SECTOR_BLOCK-BlockNum%CON_RECORD_FLASH_1SECTOR_BLOCK;// Sector中剩下还有几个block需要搜索
    
    // 查询sector中的每个block
    for(i=0;i<RemainBlock;i++)
    {
        ulTempAddr = ReadGetBlockAddr(BlockNum);
        ReadDataDirect(ulTempAddr,1,&ucStaus);
        if( (ucStaus & Channel) == Channel )
        {
            if(i==0)        //第一个Block，指针指向Block的中间，指针之前的不需要搜索
            {
                NumInBlock = Ptr%CON_RECORD_FLASH_1BLOCK_RECORD;    // 在block中的第几条
            }
            else                    // 从第二个Block开始，全部搜索
            {
                NumInBlock = 0;
            }
            ReadDataDirect(ulTempAddr+1+NumInBlock,CON_RECORD_FLASH_1BLOCK_RECORD-NumInBlock,&ChanBuffer[0]);
            lens = CON_RECORD_FLASH_1BLOCK_RECORD-NumInBlock;
            for(j=0;j<lens;j++)
            {
                if( ChanBuffer[j] == Channel )
                {
                    ulTempPtr = ReadGetPtr(j+NumInBlock,BlockNum);  // 获取指针
                    return ulTempPtr;
                }
            }
            //在最近记录指针所在的block也没查到记录，搜索完毕
            if( BlockNum == BlockNum1 )
                return (COMM_RECORDPTR_NULL-1);
        }
        else if(ucStaus == 0x00)                // 越界，停止搜索
            return (COMM_RECORDPTR_NULL-1);
        BlockNum++;
        BlockNum %= CON_RECORD_FLASH_1FLASH_BLK_NUM;
    }
    return COMM_RECORDPTR_NULL;

}

// 根据Sector确定头指针
ulong GetSectorStartPtr(uchar SectorNum);
ulong GetSectorStartPtr(uchar SectorNum)
{
    return (SectorNum*CON_RECORD_FLASH_1SECTOR_RECORD);
}
/*********************************************************************************
 * Function:       搜索某通道历史N条负荷记录
 * Description:    该函数查找Sector
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:          通道号，搜索起始指针
 * Output:         搜索到的指针
 * Return:         
 * Others:         
 *******************************************************************************/ 
ulong SearchLastChanRecByPtr(uchar nChannel,ulong ulPtr);
ulong SearchLastChanRecByPtr(uchar nChannel,ulong ulPtr)
{
    uchar SectorNum;
    uchar i;
    uchar ChannelBit;
    uchar ucStatus;
    ulong ulTempPtr=COMM_RECORDPTR_NULL;

    ChannelBit = TB_RECORD_CHANNEL_STATUS[nChannel];     // 通道
    SectorNum = ulPtr/CON_RECORD_FLASH_1SECTOR_RECORD;    // 哪一个sector

        // 搜索64个sector，从最近的开始
    for(i=0;i<CON_RECORD_FLASH_1FLASH_SECTOR;i++)
    {
        ReadDataDirect( EPL_RECORD_SECTOR_STATUS+SectorNum,1,&ucStatus);
        if((ucStatus & ChannelBit) == ChannelBit)
        {
            ulTempPtr = ReadSearchLastChanBlock(ChannelBit,ulPtr);    // 从当前指针开始的block开始搜索
            if(ulTempPtr == (COMM_RECORDPTR_NULL-1))
                break;
            else if( ulTempPtr != COMM_RECORDPTR_NULL )
            {
                return ulTempPtr;
            }
        }
        
        SectorNum++;
        SectorNum %= CON_RECORD_FLASH_1FLASH_SECTOR;
        ulPtr = GetSectorStartPtr(SectorNum);                                       // 切换Sector，更新指针
    }
    return COMM_RECORDPTR_NULL;

}


///////////单通道读N条记录到缓存中（发送缓存或后续帧缓存）
///负荷通道号，当前指针，帧序号，读出N条，读出数据放的目标处
u16   ReadNRecFmOneChToBuf(uchar nChannel,ulong ulPtr,uchar ucFameNo,uchar ucNomber,uchar *Dest);
u16   ReadNRecFmOneChToBuf(uchar nChannel,ulong ulPtr,uchar ucFameNo,uchar ucNomber,uchar *Dest)
{
  ulong i,ulNowPiont,ulLastPiont,tempTime;  
  STR_LASTFRAME_IN_PARA  TmpPara;
  STR_LAST_LOADREC_ONE  TmpLastData;
  TIMEMULITIINDEX  TmpMultArry;
  u16  TmpMaxSize,TmpLenth=0,ReturnLenth=0;
  uchar buf[5];
  TmpMaxSize = GetRecordDataMaxLen(nChannel);
  ulNowPiont = RecordGetNowPoint();
  if(ulNowPiont == COMM_RECORDPTR_NULL)
      return ReturnLenth;
  ulNowPiont = (ulNowPiont+CON_RECORD_DATA_RECORD_MAX-1)%CON_RECORD_DATA_RECORD_MAX;
  
  ulLastPiont = RecordGetLastPoint();
  if(ulLastPiont == COMM_RECORDPTR_NULL)
      return ReturnLenth;
//  if(ulLastPiont == COMM_RECORDPTR_NULL)
//      return ReturnLenth;

  for(i=0;i<ucNomber;i++)
  {
        memset(&TmpMultArry,0xFF,sizeof(TIMEMULITIINDEX));
        TmpMultArry.Ptr[nChannel] = SearchLastChanRecByPtr(nChannel,ulPtr);   // 搜索主函数，搜索ulPtr后的最近的记录
        if( TmpMultArry.Ptr[nChannel] == COMM_RECORDPTR_NULL )
            return ReturnLenth;
        ulPtr = TmpMultArry.Ptr[nChannel];
        /*--------下段程序防止越界读取-------*/
        if(ulNowPiont >= ulLastPiont) //中间部分
        {
            if(ulPtr > ulNowPiont)
                return ReturnLenth;
        }
        else                         //两头部分
        {
            if((ulPtr > ulNowPiont) && (ulPtr < ulLastPiont))
                return ReturnLenth;
        }
        /*--------上段程序防止越界读取-------*/
        tempTime = ReadLoadTimeByPtr(TmpMultArry.Ptr[nChannel]);
        LongTommHHDDMMYY(tempTime,&buf[0]);
        memcpy(&(TmpMultArry.time),&tempTime,sizeof(RECORDTIM));

        TmpLenth = SetMultRecDataToPack(Dest+ReturnLenth,&TmpMultArry);
        ReturnLenth+=TmpLenth;
        if(ReturnLenth>TmpMaxSize) 
        {
                ReturnLenth-=TmpLenth;
                break;    /////以后的就超长了。
        }

        ulPtr++;
        ulPtr %= CON_RECORD_DATA_RECORD_MAX;
  } 

  
    ///////////////////把后续数据的指针传给后续函数，做后续处理，以便后面调用
    if(i<ucNomber) 
    {
        TmpPara.ucFrameNo=ucFameNo+1;
        TmpPara.ucFormatLen=sizeof(STR_LAST_LOADREC_ONE);
  
        TmpPara.ucUsed=COMM_PARAMETER_USED;
        //////////该负荷记录方式默认为07版规约//////
            TmpPara.ulID=GetCommReadData645ID(COMMTYPE_07);
      
        TmpLastData.Ptr=ulPtr; 
        TmpLastData.OddNum=ucNomber-i;
        TmpLastData.LoadNum=nChannel;
        SaveLastFrameInBuffer(TmpPara,(uchar*)&TmpLastData);
                
                //////////有后续标志
        ReturnLenth|=COMM_READ_RETURN_FRAME_FLAG;

    }
  
  return ReturnLenth;
}


/****************************************************************
函数名为：u16 ReadLastNLoadRec(uchar nChannel,uchar ucNomber,uchar *Dest)
功能：读取最早N条记录。
入口：通道号。读出N条。读出数据的目的指针。读出数据长度。
传出：返回的数据长度，0代表没有数据。
****************************************************************/
u16 ReadLastNLoadRec(uchar nChannel,uchar ucNomber,uchar *Dest);
u16 ReadLastNLoadRec(uchar nChannel,uchar ucNomber,uchar *Dest)
{
    u16  ReturnLenth=0;
    ulong ulRecentPtr,ulLastPtr;

    ulRecentPtr = RecordGetNowPoint();
    
    if(ulRecentPtr == COMM_RECORDPTR_NULL)
        return ReturnLenth;
    ulLastPtr = RecordGetLastPoint();   
    if(ulLastPtr == COMM_RECORDPTR_NULL)
        return ReturnLenth;
    if(ulRecentPtr==ulLastPtr)
    {
        return ReturnLenth;
    }
    
    ReturnLenth=ReadNRecFmOneChToBuf(nChannel,ulLastPtr,0,ucNomber,Dest);
     
    return ReturnLenth;
}
/*********************************************************************
功能：比较2值的大小
传入：被比较数，比较数。
输出：COMM_LOADRECORD_EQU，COMM_LOADRECORD_HT，COMM_LOADRECORD_LT
***********************************************************************/
uchar   CompareValue(u32 FlashValue,u32 SearchValue);
uchar   CompareValue(u32 FlashValue,u32 SearchValue)
{
    if(FlashValue>SearchValue) return COMM_LOADRECORD_HT;
    else 
    {
        if(FlashValue<SearchValue) return COMM_LOADRECORD_LT;
        else  return COMM_LOADRECORD_EQU;
    }
}

void RecordGetNearestActivePtr(ulong *RecentPtr);
void RecordGetNearestActivePtr(ulong *RecentPtr)
{
    uchar j;
    u16 BlkNum;
    ulong TempAddr;
        
    BlkNum = (*RecentPtr)/CON_RECORD_FLASH_1BLOCK_RECORD;
        //读取当前block最近的有效记录指针和时间
    TempAddr = ReadGetBlockAddr(BlkNum)+1;
    ReadDataDirect(TempAddr,CON_RECORD_FLASH_1BLOCK_RECORD,&Wr_data[0]);
    for(j=CON_RECORD_FLASH_1BLOCK_RECORD;j !=0; j-- )
    {
        if((Wr_data[j-1] !=0 )&&(Wr_data[j-1] !=0xFF ))
        {
            (*RecentPtr) = ReadGetPtr(j-1,BlkNum);
            break;
        }
    }
}

/**********************************************************************
函数名：u16 SearchPtrByTim(uchar nChannel,ulong ulTime)
功能：从给定的时间查找到最近一条不大于给定时间的地址。
传入：通道号。给定的时间，读出的N掉记录，读出的数据存放的位置。读出的数据长度。
返回：数据长度。0XFFFF代表没有数据。
**********************************************************************/
ulong SearchPtrByTim(ulong ulGivenTime);
ulong SearchPtrByTim(ulong ulGivenTime)
{
    
    uchar   i,j,ucCompValue,ucStatus;
    u16 BlockNum;
    ulong  y,ymax,ymin;
    ulong StartPtr,RecentPtr,MidPtr,TempPtr1=0,TempPtr2;
    ulong ulTempTime,TempTime1=0,TempTime2;
    ulong TempAddr;

    // 获取头尾指针
    StartPtr = RecordGetLastPoint();
    if(StartPtr == COMM_RECORDPTR_NULL)
        return COMM_RECORDPTR_NULL;
    
    RecentPtr = RecordGetNowPoint();    
    if(RecentPtr == COMM_RECORDPTR_NULL)
        return COMM_RECORDPTR_NULL;
    
    if( StartPtr == RecentPtr)
        return COMM_RECORDPTR_NULL;
    
    RecentPtr = (RecentPtr+CON_RECORD_DATA_RECORD_MAX-1)%CON_RECORD_DATA_RECORD_MAX;
    RecordGetNearestActivePtr(&RecentPtr);
    // 给定时间与尾指针的记录时间比较
    // 给定时间在尾指针之前
    ulTempTime = ReadLoadTimeByPtr(StartPtr);
    if( ulGivenTime < ulTempTime )
        return StartPtr;
    
    // 给定时间与头指针的记录时间比较
    // 给定时间在头指针之后，无数据记录
    ulTempTime = ReadLoadTimeByPtr(RecentPtr);
    if( ulGivenTime > ulTempTime )
        return COMM_RECORDPTR_NULL;
    
    if( RecentPtr < StartPtr )     //两头部分有效
    {
        RecentPtr += CON_RECORD_DATA_RECORD_MAX;
    }
    ymax=RecentPtr;
    ymin=StartPtr;
    y=(ymax+ymin)/2;
    
    for (i=0;i<COMM_LOADRECORD_SEARCH_NUM;i++)
    {
        MidPtr = y%CON_RECORD_DATA_RECORD_MAX;
        
        /*Start of ybf on 2010-8-6 11:10 V1.0*/
        ucStatus=ReadChannelNumByPtr(MidPtr);       // 读记录通道
        // 异常搜索，如记录被擦除等，跳过删除区继续搜索
        if(ucStatus == 0)                                  
        {
            BlockNum = MidPtr/CON_RECORD_FLASH_1BLOCK_RECORD;
            //读取当前block最近的有效记录指针和时间
            TempAddr = ReadGetBlockAddr(BlockNum)+1;
            ReadDataDirect(TempAddr,CON_RECORD_FLASH_1BLOCK_RECORD,&Wr_data[0]);
            for(j=CON_RECORD_FLASH_1BLOCK_RECORD;j !=0; j-- )
            {
                if((Wr_data[j-1] !=0 )&&(Wr_data[j-1] !=0xFF ))
                {
                    TempPtr1 = ReadGetPtr(j-1,BlockNum);
                    TempTime1 = ReadLoadTimeByPtr(TempPtr1);
                    break;
                }
            }
            
            // 读取下一block的起始指针和时间
            BlockNum = (BlockNum+1)%CON_RECORD_DATA_RECORD_MAX;
            TempPtr2 = ReadGetPtr(0,BlockNum);
            TempTime2 = ReadLoadTimeByPtr(TempPtr2);
            
            // 当前时间== 当前block最近的有效记录时间，
            // 将当前block最近的有效记录指针作为目的指针
            if(ulGivenTime == TempTime1)
            {
                y = TempPtr1;
                return (y%CON_RECORD_DATA_RECORD_MAX);
            }
            
            // 当前时间== 下一block起始记录时间，
            // 将下一block起始记录指针作为目的指针
            if(ulGivenTime == TempTime2)
            {
                y = TempPtr2;
                return (y%CON_RECORD_DATA_RECORD_MAX);
            }
            
            // 当前时间< 当前block最近的有效记录时间，
            // 将当前block最近的有效记录指针作为搜索上限指针，继续搜索
            if(ulGivenTime<TempTime1)
            {
                ymax = TempPtr1;
            }
            
            // 当前时间>下一block起始记录时间，
            // 将下一block起始记录指针作为搜索下限指针，继续搜索
            else if(ulGivenTime>TempTime2)
            {
                ymin = TempPtr2;
            }
            
            // 当前时间> 当前block最近的有效记录时间 且当前时间<下一block起始记录时间，
            // 将下一block起始记录指针作为目的指针
            else if((ulGivenTime>TempTime1)&&(ulGivenTime<TempTime2))
            {
                y = TempPtr2;
                return (y%CON_RECORD_DATA_RECORD_MAX);
            }

        }
        else
        {
            /*End of ybf on 2010-8-6 11:10 V1.0*/
            
            ulTempTime = ReadLoadTimeByPtr(MidPtr);
            ucCompValue=CompareValue(ulGivenTime,ulTempTime);
            if(ucCompValue==COMM_LOADRECORD_EQU) 
                return MidPtr ;
            if(ucCompValue==COMM_LOADRECORD_HT)
            {
                    ymin=y;
            }
            else  
            {
                    ymax=y;
            }
        }
        y=(ymax+ymin)/2;
    }

    //不小于比较值的存储空间中的第一个值
    MidPtr=y%CON_RECORD_DATA_RECORD_MAX;
    ulTempTime = ReadLoadTimeByPtr(MidPtr);
    
    if(COMM_LOADRECORD_EQU==CompareValue(ulTempTime,ulGivenTime)) 
        return  MidPtr;
    if(COMM_LOADRECORD_LT==CompareValue(ulTempTime,ulGivenTime))
    {
            MidPtr=ymax%CON_RECORD_DATA_RECORD_MAX;
            ulTempTime = ReadLoadTimeByPtr(MidPtr);
            if(COMM_LOADRECORD_LT!=CompareValue(ulTempTime,ulGivenTime))
            {
                return  MidPtr;
            }
            else 
                return(COMM_RECORDPTR_NULL);
    }
    
    //LT
    //next 2 record
    for(i=0;i<2;i++)
    {
        if(y!=0)
            y--;
        MidPtr=y%CON_RECORD_DATA_RECORD_MAX;
        ulTempTime = ReadLoadTimeByPtr(MidPtr);
        if(COMM_LOADRECORD_LT!=CompareValue(ulTempTime,ulGivenTime))
        {
             return  MidPtr;
        }      
    }
    return  COMM_RECORDPTR_NULL;
}
    



/**********************************************************************
函数名：u16 ReadLastNRecByTime(uchar nChannel,ulong ulTime, uchar ucNomber,uchar *Dest)
功能：从给定的时间开始读后续的N条记录。
传入：通道号。给定的时间，读出的N掉记录，读出的数据存放的位置。读出的数据长度。
返回：数据长度。0代表没有数据。
**********************************************************************/
u16 ReadLastNRecByTime(uchar nChannel,ulong ulTime, uchar ucNomber,uchar *Dest);
u16 ReadLastNRecByTime(uchar nChannel,ulong ulTime, uchar ucNomber,uchar *Dest)
{
       
    ulong   ulTempPtr=COMM_RECORDPTR_NULL;
    u16    ReturnLenth=0;
    
    
    ulTempPtr = SearchPtrByTim(ulTime);
    if(ulTempPtr==COMM_RECORDPTR_NULL)  
        return ReturnLenth;

    ulTempPtr=SearchSameTimeBefore(ulTempPtr);
        
    ReturnLenth=ReadNRecFmOneChToBuf(nChannel,ulTempPtr,0,ucNomber,Dest);
        
    return ReturnLenth;
}


////////////获得组合记录的最大长度
u16  GetRecordMultDataMaxLen(void);
u16  GetRecordMultDataMaxLen(void)
{
   return (COMM_LOADRECORD_CHANNEL5_MAXSIZE);  
}

// 读取历史N条组合记录，放到缓存区
u16  ReadNRecFmMultToBuf(ulong ulPTR,ulong ulPtr,uchar ucFameNo,uchar ucNomber,uchar *Dest)
{
    uchar ucChannel,ucScanChannel;
    uchar TmpMaxSize;
    //uchar ucStatus=0;
    uchar sflag=1;
    u16   i,j,TmpLenth=0,ReturnLenth=0;
    ulong ulLastPiont;
    ulong   ulLastTime,ulTempTime;
    TIMEMULITIINDEX  TmpMultArry;
    STR_LAST_LOADREC_MULT  TmpLastData;
    STR_LASTFRAME_IN_PARA  TmpPara;
    
    TmpMaxSize = GetRecordMultDataMaxLen();         // 读一帧负荷记录的最大长度
    ulLastPiont = ulPtr;
    for(i=0;i<ucNomber;i++)
    {   
        while(sflag)
        {
            ucChannel = ReadChannelNumByPtr(ulPtr);         // 读取通道号
            //记录被删除，继续搜索
            if(ucChannel == 0)  
            {
                ulPtr=(ulPtr+CON_RECORD_FLASH_1BLOCK_RECORD-ulPtr%CON_RECORD_FLASH_1BLOCK_RECORD)%CON_RECORD_DATA_RECORD_MAX;
                if((ulPTR > ulLastPiont) && (ulPtr >= ulPTR) )  //中间部分有效
                    return ReturnLenth;
                if( (ulPTR < ulLastPiont) && ((ulPtr >= ulPTR) && (ulPtr< ulLastPiont)))    //两头部分有效
                    return ReturnLenth;
            }
            else
                break;
        }
        //记录错误，退出
        if(ucChannel>COMM_LOADRECORD_CHENNL_NUM)
            return ReturnLenth;

        memset((uchar*)&TmpMultArry,0xFF,sizeof(TIMEMULITIINDEX));      
        ulLastTime = ReadLoadTimeByPtr(ulPtr);              // 读取时间点
        if( ulLastTime == 0xFFFFFF)
            return ReturnLenth;
        memcpy(&(TmpMultArry.time),&ulLastTime,sizeof(RECORDTIM));

        TmpMultArry.Ptr[ucChannel-1] = ulPtr;

        // 比剩余的通道多搜索一次，一定可以搜到下一个时间点
        for(j=0;j<COMM_LOADRECORD_CHENNL_NUM-ucChannel+1;j++)
        {   
            ulPtr++;
            if( ulPtr >= CON_RECORD_DATA_RECORD_MAX )
                ulPtr = 0;
            
            ulTempTime = ReadLoadTimeByPtr(ulPtr);
            ucScanChannel = ReadChannelNumByPtr(ulPtr);
            if( (ulTempTime == ulLastTime) && (ucScanChannel != 0) )
                TmpMultArry.Ptr[ucScanChannel-1] = ulPtr;   
            else
                break;
        }

        ///数据组包
        TmpLenth=SetMultRecDataToPack(Dest+ReturnLenth,&TmpMultArry);
        
        ReturnLenth+=TmpLenth;
        if(ReturnLenth>TmpMaxSize)  /////以后的就超长了。
        {
            ReturnLenth-=TmpLenth;
            ulPtr = (ulPtr+CON_RECORD_DATA_RECORD_MAX-1-j)%CON_RECORD_DATA_RECORD_MAX;
            break;    
        }
        
    }
        
    //把后续数据的指针传给后续函数，做后续处理，以便后面调用
    if(i<ucNomber) 
    {
        TmpPara.ucFrameNo=ucFameNo+1;                       // 帧序号
        TmpPara.ucFormatLen=sizeof(STR_LAST_LOADREC_MULT);  // 缓存的长度
        TmpPara.ucUsed=COMM_PARAMETER_USED;                 // 已使用
        TmpPara.ulID=GetCommReadData645ID(COMMTYPE_07); //该负荷记录方式默认为07版规约
  
        TmpLastData.Ptr=ulPtr;              // 保存当前读取的指针，下次继续从此开始读取
        TmpLastData.OddNum=ucNomber-i;      // 剩余读取的负荷记录条数
        SaveLastFrameInBuffer(TmpPara,(uchar*)&TmpLastData);
                    
        //////////有后续标志
        ReturnLenth|=COMM_READ_RETURN_FRAME_FLAG;
    }
    return (ReturnLenth);
  
}



/**********************************************************************
函数名：u16 ReadMultLastNRec (uchar Number,uchar *Dest)
功能：组合读最早N条记录
传入：读出的块数,读出的数据存放的位置，读出的数据长度
返回：数据长度。0代表没有数据。
**********************************************************************/
u16 ReadMultLastNRec (uchar ucNomber,uchar *Dest);
u16 ReadMultLastNRec (uchar ucNomber,uchar *Dest)
{
    u16   ReturnLenth=0;
    ulong  ulRecentPtr,ulLastPtr;

    ulRecentPtr = RecordGetNowPoint();      
    if(ulRecentPtr == COMM_RECORDPTR_NULL)
        return ReturnLenth;
    ulLastPtr = RecordGetLastPoint();   
    if(ulLastPtr == COMM_RECORDPTR_NULL)
        return ReturnLenth;
    if(ulRecentPtr==ulLastPtr)
    {
        return ReturnLenth;
    }

    ReturnLenth=ReadNRecFmMultToBuf(ulRecentPtr,ulLastPtr,0,ucNomber,Dest);
        
    return(ReturnLenth);
}




/**********************************************************************
函数名：u16 ReadMultNRecByTim (uchar ReadNumber ,uchar *Dest，u16 uiLenth)
功能：组合读给定时间后的N条记录
传入：读出的块数,读出的数据存放的位置，给定的时间
返回：数据长度。0代表没有数据。
**********************************************************************/
u16 ReadMultNRecByTim (uchar ucNomber,uchar *Dest,ulong SearchTim);
u16 ReadMultNRecByTim (uchar ucNomber,uchar *Dest,ulong SearchTim)
{
    //SEARCHPTRARR  TmpPtrArry;
        
    u16   TmpLenth=0;
    ulong  ulTempPtr=COMM_RECORDPTR_NULL,ulRecentPtr;
    
    ulTempPtr = SearchPtrByTim(SearchTim);
    if(ulTempPtr==COMM_RECORDPTR_NULL)  
        return TmpLenth;

    ulTempPtr=SearchSameTimeBefore(ulTempPtr);
    ulRecentPtr = RecordGetNowPoint();  
    if(ulRecentPtr == COMM_RECORDPTR_NULL)
        return TmpLenth;

    TmpLenth = ReadNRecFmMultToBuf(ulRecentPtr,ulTempPtr,0,ucNomber,Dest);
        
    return(TmpLenth);
}

/////////检查负荷给定的时间格式是否有效
uchar CheckLoadTim(uchar *Dest);
uchar CheckLoadTim(uchar *Dest)
{
    uchar ucFlag=COMM_FAIL;
    
    ucFlag=TestMinute(*Dest);
    if(ucFlag==0) return (COMM_FAIL);
        
    ucFlag=TestHour(*(Dest+1));
    if(ucFlag==0) return (COMM_FAIL);
        
    ucFlag=TestDayMonthYear((Dest+2));
    if(ucFlag==0) return (COMM_FAIL);   
        
//  ucFlag=TestMonth(*(Dest+3));
//  if(ucFlag==0) return (COMM_FAIL);
        
//  ucFlag=TestYear(*(Dest+4));
//  if(ucFlag==0) return (COMM_FAIL);       
        
    return COMM_TURE;
}





 u16 SetMultRecDataToPack (uchar *Dest,TIMEMULITIINDEX *Src)
 {
     uchar TmpBuffer[10],i;   ////用来存放时间的
     uchar TmpLen=0;      
     ulong TmpTime=0;
     uchar TmpCS;
     u16  TmpDataSize=0;
         
     *Dest=0xA0;
     *(Dest+1)=0xA0;
     memcpy(&TmpTime,&(Src->time),COMM_LOADRECORD_TIME_SIZE);
     ChangeDataToTime(TmpBuffer,TmpTime);
     memcpy(Dest+3,TmpBuffer,5);
     TmpLen+=5;
     for(i=0;i<COMM_LOADRECORD_CHENNL_NUM;i++)
     {
         if(Src->Ptr[i]!=COMM_RECORDPTR_NULL)
         {
             TmpDataSize=GetRecordDataLen(i);
             ReadRecDataByPtr(Dest+3+TmpLen,Src->Ptr[i],TmpDataSize);
             *(Dest+3+TmpLen+TmpDataSize)=0xAA;
             TmpLen+=1+TmpDataSize;
         }
         else
         {
             *(Dest+3+TmpLen)=0xAA;
             TmpLen+=1;
         }
     }
     *(Dest+2)=TmpLen;
     TmpCS=CommCalChksum(Dest,TmpLen+3);//校验
     *(Dest+2+TmpLen+1)=TmpCS;
     *(Dest+2+TmpLen+2)=0xE5;
     
     return (TmpLen+5);
 }


//////////组合读后续N条记录
/////存储位置的指针数组，帧序号，读出N条记录，读出所存储的地址


////////////负荷记录后续帧的读出

u16   CommLoadLastFrameRead(uchar ucPtr,ulong ID,uchar* Dest)
{
    uchar ID2=(uchar)(ID>>16);
    STR_LAST_LOADREC_ONE   TmpLastRec;
    STR_LAST_LOADREC_MULT  TmpLastMult;
    //SEARCHPTRARR           TmpSearchPtr;  
    uchar TmpChannelNo=0;
    u16 ReturnLen=0;
    ulong ulRecentPtr;
    
    if(ID2==0x00)  /////组合
    {
          memcpy((uchar*)&TmpLastMult,LastFrameData[ucPtr].Buffer,sizeof(STR_LAST_LOADREC_MULT));
          //memcpy(&TmpSearchPtr,&TmpLastMult,sizeof(SEARCHPTRARR));
          ulRecentPtr = RecordGetNowPoint();    
          if(ulRecentPtr == COMM_RECORDPTR_NULL)
              return ReturnLen;

          ReturnLen=ReadNRecFmMultToBuf(ulRecentPtr,TmpLastMult.Ptr,LastFrameData[ucPtr].HeadPara.ucFrameNo,TmpLastMult.OddNum,Dest);
    }
    else   ////单个通道
    {
          TmpChannelNo=ID2-1;
          memcpy((uchar*)&TmpLastRec,LastFrameData[ucPtr].Buffer,sizeof(STR_LAST_LOADREC_ONE));    
          /////////比较后续帧的数据的通道号是否与ID能够一致
           if(TmpChannelNo==TmpLastRec.LoadNum)
           {
               ReturnLen=ReadNRecFmOneChToBuf(TmpChannelNo,TmpLastRec.Ptr,LastFrameData[ucPtr].HeadPara.ucFrameNo,TmpLastRec.OddNum,Dest);
           }
           else   /////不一致
           {
              ReturnLen=0;
           }
    }
    LastFrameData[ucPtr].HeadPara.ucUsed=COMM_PARAMETER_NO_USED;
    return ReturnLen;
}


/*=====================================================================================


=====================================================================================*/

/*********************************************************************************
 * Function:       
 * Description:    
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:          
 * Output:         通道号，1~6
 * Return:         
 * Others:         
 *******************************************************************************/ 
uchar ReadChannelNumByPtr(ulong RecPtr)
{
    
    ulong ulTemp;
    ulong ucPageInBlock;
    ulong ucBlockPiont;
    uchar ChannelTemp=0;
    uchar i,j=0x01;

    ucBlockPiont =  RecPtr/CON_RECORD_FLASH_1BLOCK_RECORD;                                  // 第几个block
    ucPageInBlock = RecPtr%CON_RECORD_FLASH_1BLOCK_RECORD;                                  // block里第几条记录

    ulTemp = FL1_METER_RECORD_STARTADDR + ucBlockPiont*CON_RECORD_FLASH_1BLOCK_BYTE;        // block 地址

    ReadDataDirect(ulTemp+CON_RECORD_FLASH_BLOCK_RECORDSTATUS_ADDR+ucPageInBlock,1,(uchar *)&ChannelTemp);   // 读取通道号
    if( (ChannelTemp == 0) || (ChannelTemp == 0xff) )                                      // 通道被删除
         return 0;
    for(i=1;i<=COMM_LOADRECORD_CHENNL_NUM;i++)
    {
        if( j == ChannelTemp )
            break;
        else
            j=j<<1;
    }
    return i;
}


 /**********************************************************************
函数名：u16 ReadMultRecentRec (uchar *Dest)
功能：组合读最近的一条记录
传入：读出的数据存放的位置，读出的数据长度
返回：数据长度。0代表没有数据。
**********************************************************************/
u16 ReadMultRecentRec (uchar *Dest);
u16 ReadMultRecentRec (uchar *Dest)
{
    uchar i;
    uchar ucNowChannel;
    ulong RecentPtr,ulLastPtr;
    ulong TempPtr;
    ulong RecentTime;
    ulong TempTime;
    TIMEMULITIINDEX  TmpMultArry;
    u16  TmpLenth=0;

    RecentPtr = RecordGetNowPoint();        
    if(RecentPtr == COMM_RECORDPTR_NULL)
        return TmpLenth;
    ulLastPtr = RecordGetLastPoint();
    if(ulLastPtr == COMM_RECORDPTR_NULL)
        return TmpLenth;
    if(RecentPtr==ulLastPtr)
    {
        return TmpLenth;
    }
    RecentPtr = (RecentPtr+CON_RECORD_DATA_RECORD_MAX-1)%CON_RECORD_DATA_RECORD_MAX;
        
    memset((uchar*)&TmpMultArry,0xFF,sizeof(TIMEMULITIINDEX));

    RecentTime = ReadLoadTimeByPtr(RecentPtr);              // 读取时间点
    if( RecentTime == 0xFFFFFF)
        return 0;
    memcpy(&(TmpMultArry.time),&RecentTime,sizeof(RECORDTIM));
    
    ucNowChannel = ReadChannelNumByPtr(RecentPtr);          // 读取通道号
    if(ucNowChannel>COMM_LOADRECORD_CHENNL_NUM)
        return 0;
    TmpMultArry.Ptr[ucNowChannel-1] = RecentPtr;
        
    TempPtr = RecentPtr;
    // 向前查询组合记录。
    for(i=0;i<ucNowChannel-1;i++)
    {   
        if( TempPtr == 0 )
            TempPtr = CON_RECORD_DATA_RECORD_MAX-1;
        else
            TempPtr--;
        
        TempTime = ReadLoadTimeByPtr(TempPtr);
        if( TempTime == RecentTime )
        {
            TmpMultArry.Ptr[ReadChannelNumByPtr(TempPtr)-1] = TempPtr;
            //TmpMultArry.Ptr[ucNowChannel-2-i] = TempPtr;  
        }
        else
            break;
    }

    
  ///数据组包
    TmpLenth=SetMultRecDataToPack(Dest,&TmpMultArry);
    return (TmpLenth);
}


/*********************************************************************************
 * Function:       查找通道最近记录的block
 * Description:    
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:          
 * Output:         指针，0xffffffff表示找不到
 * Return:         
 * Others:         
 *******************************************************************************/ 
ulong ReadSearchRecentChanBlock(uchar Channel,ulong Ptr);
ulong ReadSearchRecentChanBlock(uchar Channel,ulong Ptr)
{
    uchar ChanBuffer[135];
    uchar ucStaus;
    uchar i,j;
    u16 BlockNum,WhichBlock;
    ulong ulTempAddr;
    ulong ulTempPtr=COMM_RECORDPTR_NULL;

    BlockNum = Ptr/CON_RECORD_FLASH_1BLOCK_RECORD;      // 在第几个block
    WhichBlock = BlockNum%CON_RECORD_FLASH_1SECTOR_BLOCK;   // Sector中的第几个block

    // 查询sector中的每个block
    for(i=0;i<=WhichBlock;i++)
    {
        ulTempAddr = ReadGetBlockAddr(BlockNum);
        ReadDataDirect(ulTempAddr,1,&ucStaus);
        if( (ucStaus & Channel) == Channel )
        {
            ReadDataDirect(ulTempAddr+1,CON_RECORD_FLASH_1BLOCK_RECORD,&ChanBuffer[0]);
            for(j=CON_RECORD_FLASH_1BLOCK_RECORD;j!=0;j--)
            {
                if( ChanBuffer[j-1] == Channel )
                {
                    ulTempPtr = ReadGetPtr(j-1,BlockNum);
                    return ulTempPtr;
                }
            }
        }
        if( (BlockNum%CON_RECORD_FLASH_1BLOCK_RECORD) == 0)
            return COMM_RECORDPTR_NULL;
        else
            BlockNum--;
    }
    return COMM_RECORDPTR_NULL;
}

/*********************************************************************************
 * Function:       查找某通道最近的负荷记录
 * Description:    
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:          nChannel   通道号0~5；ulNowPiont   当前指针
 * Output:         目的指针
 * Return:         
 * Others:         
 *******************************************************************************/ 
ulong ReadSearchRecentChanSector(uchar nChannel,ulong ulNowPiont);
ulong ReadSearchRecentChanSector(uchar nChannel,ulong ulNowPiont)
{
    uchar SectorNum;
    uchar i;
    uchar ChannelBit;
    uchar ucStatus;
    ulong ulTempPtr=COMM_RECORDPTR_NULL;

    ChannelBit = TB_RECORD_CHANNEL_STATUS[nChannel];
    SectorNum = ulNowPiont/CON_RECORD_FLASH_1SECTOR_RECORD;

    for(i=0;i<CON_RECORD_FLASH_1FLASH_SECTOR;i++)
    {
        ReadDataDirect( EPL_RECORD_SECTOR_STATUS+SectorNum,1,&ucStatus);
        if((ucStatus & ChannelBit) == ChannelBit)
        {
            ulTempPtr = ReadSearchRecentChanBlock(ChannelBit,ulNowPiont);
            if( ulTempPtr != COMM_RECORDPTR_NULL )
            {
                return ulTempPtr;

            }               
        }
        
        if(SectorNum == 0)
            SectorNum = CON_RECORD_FLASH_1FLASH_SECTOR-1;
        else
            SectorNum--;
            
    }
    return COMM_RECORDPTR_NULL;

}




/*********************************************************************************
 * Function:       读单通道最近负荷记录
 * Description:    
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:          
 * Output:         
 * Return:         
 * Others:         
 *******************************************************************************/ 
u16 ReadRecentLoadRec(uchar nChannel,uchar *Dest);
u16 ReadRecentLoadRec(uchar nChannel,uchar *Dest)
{
    TIMEMULITIINDEX  TmpMultArry;
    u16   TmpLenth=0;
    ulong  ulNowPiont,ulLastPtr,tempTime;

    ulNowPiont = RecordGetNowPoint();   
    if(ulNowPiont == COMM_RECORDPTR_NULL)
        return TmpLenth;
    
    ulLastPtr = RecordGetLastPoint();   
    if(ulLastPtr == COMM_RECORDPTR_NULL)
        return TmpLenth;
    
    if(ulNowPiont==ulLastPtr)
    {
        return TmpLenth;
    }
    ulNowPiont = (ulNowPiont+CON_RECORD_DATA_RECORD_MAX-1)%CON_RECORD_DATA_RECORD_MAX;
        
    memset(&TmpMultArry,0xFF,sizeof(TIMEMULITIINDEX));

    TmpMultArry.Ptr[nChannel] = ReadSearchRecentChanSector(nChannel,ulNowPiont);
    if( TmpMultArry.Ptr[nChannel] == COMM_RECORDPTR_NULL )
        return TmpLenth;
    tempTime = ReadLoadTimeByPtr(TmpMultArry.Ptr[nChannel]);
    memcpy(&(TmpMultArry.time),&tempTime,sizeof(RECORDTIM));

    TmpLenth=SetMultRecDataToPack(Dest,&TmpMultArry);
    return (TmpLenth);
    
}



void CommReadLoadData (STR_READ_RETURN_PARA *Dest,ulong ID)
{
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
    uchar ID2=(uchar)(ID>>16);
    uchar ucChannelNo=0;
    uchar ucNumber,TmpFlag=0;           ////(TmpFlag=0表示错误，
                                        ////TmpFlag=1表示没有该项数据但须返回ID的，TmpFlag=2表示返回正确没有后续帧，TmpFlag=2表示返回正确有后续帧)
    ulong SearchTim=0;
    u16  ReturnLen=0;
    
    if((ID2<=0x06)&&(ID1==0)&&(ID0<0x03))
    {
            ucNumber=OneByteBcdToHex(COMM_LOADRECORD_READOUT_NO);
            if(ucNumber>99)  
            {
                TmpFlag=0;
            }
            else
            {
                if(ID2==0x00)  /////组合
                {
                    switch(ID0)
                    {
                        case 0x00:                                          ////组合最早记录块
                            ReturnLen=ReadMultLastNRec(ucNumber,CommExpDataBuff->Buffer);
                            break;
                        case 0x01:                                          ////组合给定时间记录块
                            ///////////测试时间格式是否正确
                            if(CheckLoadTim(&COMM_LOADRECORD_READOUT_TIME)==COMM_FAIL)
                            {
                                    TmpFlag=0;
                                    ReturnLen=1;
                                    break;
                            }
                            
                            SearchTim=ChangeTimeToData(&COMM_LOADRECORD_READOUT_TIME);
                            ReturnLen=ReadMultNRecByTim (ucNumber,CommExpDataBuff->Buffer,SearchTim);
                            break;
                        case 0x02:                                          /////组合最近一条记录块
                            if(ucNumber!=1) 
                            {
                                TmpFlag=0;
                            }
                            else
                            {
                                ReturnLen=ReadMultRecentRec(CommExpDataBuff->Buffer);
                            }
                            break;
                    }
                }
                else   ///各个通道
                {
                        ucChannelNo=ID2-1;  //  通道号  0~5
                        if(GetLoadChannelState(ucChannelNo)==COMM_TURE)     // 负荷记录模式字
                        {
                                switch (ID0)
                                {
                                    case 0x00:     ////最早记录块
                                        ReturnLen=ReadLastNLoadRec(ucChannelNo,ucNumber,CommExpDataBuff->Buffer);
                                        break;
                                    case 0x01:     ////给定时间记录块
                                        SearchTim=ChangeTimeToData(&COMM_LOADRECORD_READOUT_TIME);
                                        ReturnLen=ReadLastNRecByTime(ucChannelNo,SearchTim,ucNumber,CommExpDataBuff->Buffer);
                                        break;      
                                    case 0x02:    /////最近一条记录块
                                        if(ucNumber!=1) 
                                        {
                                            TmpFlag=0;
                                        }
                                        else
                                        {
                                            ReturnLen=ReadRecentLoadRec(ucChannelNo,CommExpDataBuff->Buffer);
                                        }
                                        break;  
                                }
                        }
                        else  ////没有该项但是须返回带ID的正确应答帧
                        {
                                TmpFlag=1;
                        }
                }
            
                if((ReturnLen==0)||(ReturnLen==0xFFFF))
                {
                    TmpFlag=1;
                }
                else
                {
                    if(ReturnLen==0xFFFF)
                    {
                          TmpFlag=1;
                    }
                    else
                    {
                          if(ReturnLen&COMM_READ_RETURN_FRAME_FLAG)
                          {
                              TmpFlag=3;
                          }
                          else
                          {
                              TmpFlag=2;
                          }
                    }
                }
        }
    }
    else   ////没有该ID
    {
        TmpFlag=0;
    }   
        
    Dest->strReturnData.ReturnFail=0;
    switch (TmpFlag)
    {
        case 0:
            Dest->strReturnData.ReturnFail=1; ////没有该项
            break;
        case 1:   ////没有该项但是须返回带ID的正确应答帧
            Dest->strReturnData.Lenth=0;   
            break;
        case 2:   ////没有返回帧的正常应答
            Dest->strReturnData.Lenth=ReturnLen;
            break;
        case 3: ////有返回帧的正常应答
            Dest->strReturnData.Lenth=ReturnLen;
            Dest->strReturnData.LastFrame=1;
            break;
        default:
            Dest->strReturnData.ReturnFail=1;  ////没有该项
            break;
    }
    
}






