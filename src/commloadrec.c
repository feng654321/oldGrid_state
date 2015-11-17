/*********************************************************************************
    �汾��     :version 0.1
    ģ����       : Զ�̿���ģ��
    �ļ���       : CommLoadRec.c
    ����ļ�     : 
    �ļ�ʵ�ֹ��� : ͨ�Ŷ����ɼ�¼ģ��
    ����         : Ҧ����
    �汾         : 0.1
----------------------------------------------------------------------------------------------------------------------
    ��ע         : <����˵��>
---------------------------------------------------------------------------------------------------------------------
    �޸ļ�¼ : 
    �� ��        �汾     �޸���              �޸�����
    YYYY/MM/DD   X.Ymai      <���߻��޸�����>    <�޸�����>
    YYYY/MM/DD   X.Y      <���߻��޸�����>    <�޸�����>
==================================================================== 
����˵���� 
*******************************************************************************/
#include "common.h"
//////////////////////////////ȫ�ֱ����ɼ�����////////////
//ulong  LoadReachTmpBuf[COMM_COMMTYPE_NUM][COMM_LOADRECORD_CHENNL_NUM];
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////��״̬�֣���ø��ɼ�¼���Ƿ���ڸ���
//////����COMM_TURE�����У�COMM_FAIL����û��

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
 * Function:       ����block�еĵڼ�����¼��ȡָ��
 * Description:    
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:          
 * Output:         ָ��
 * Return:         
 * Others:         
 *******************************************************************************/ 
ulong ReadGetPtr(uchar Num,u16 Block)
{
    return (Block*CON_RECORD_FLASH_1BLOCK_RECORD+Num);
}


// ���ݼ�¼ָ�룬��ȡ��¼ʱ��
ulong ReadLoadTimeByPtr(ulong RecPtr)
{
    
    ulong ulTemp;
    ulong ucPageInBlock;
    ulong ucBlockPiont;
    ulong TimeTemp=0;

    ucBlockPiont =  RecPtr/CON_RECORD_FLASH_1BLOCK_RECORD;                              // �ڼ���block
    ucPageInBlock = RecPtr%CON_RECORD_FLASH_1BLOCK_RECORD;                              // block��ڼ�����¼

    ulTemp = FL1_METER_RECORD_STARTADDR + ucBlockPiont*CON_RECORD_FLASH_1BLOCK_BYTE;    // block ��ַ
    ulTemp += ((ucPageInBlock+CON_RECORD_FLASH_1PAGE_RECORD)/CON_RECORD_FLASH_1PAGE_RECORD)*CON_RECORD_FLASH_1PAGE_BYTE;    //page��ַ
    ulTemp += (ucPageInBlock%CON_RECORD_FLASH_1PAGE_RECORD)*CON_RECORD_FLASH_1RECORD_BYTE;  // ��¼��ַ

    ReadDataDirect(ulTemp,3,(uchar *)&TimeTemp);
    return TimeTemp;

}



  /**********************************************************************
��������u16 ReadRecDataByPtr (uchar nChannel,uchar *Dest,u16 uiLenth,ulong ulPtr)
���ܣ��ɸ����ļ�¼ָ��ֵ��������¼���ݡ�
���룺ͨ����,���������ݴ�ŵ�λ�ã����������ݳ���
���أ���ȡ�Ƿ���ȷ��COMM_TURE�����У�COMM_FAIL����û��
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
 * Function:       ����֮ǰ�Ƿ�����ͬ��ʱ����¼
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
��������void ChangeDataToTime(uchar *Dest,ulong  TimData)
���ܣ��ѱ�ʾʱ�������ת���ɱ�׼ʱ���ʽ
���룺ת����ŵĵ�ַ����ת�����ݵ�ֵ
**********************************************************************/
void ChangeDataToTime(uchar *Dest,ulong  TimData);
void ChangeDataToTime(uchar *Dest,ulong  TimData)
{
    LongTommHHDDMMYY(TimData,Dest);
}
/**********************************************************************
��������void ChangeTimeToData(uchar *Src,ulong  TimData)
���ܣ��ѱ�ʾʱ�������ת���ɱ�׼ʱ���ʽ
���룺ת����ŵĵ�ַ����ת�����ݵ�ֵ
���أ�ת������ֵ��ʱ��
**********************************************************************/
ulong ChangeTimeToData(uchar *Src);
ulong ChangeTimeToData(uchar *Src)
{
    return (mmHHDDMMYYToLong(Src));
}

 /**********************************************************************
��������u16 SetLoadRecDataToPack (uchar nChannel,uchar *Dest,uchar *Src,u16 uiLenth)
���ܣ�����ͨ�����ݶ�������֡Ϊ1��
���룺ͨ����,���������ݴ�ŵ�λ�ã���¼���ݵ�ַ����¼���ݳ��ȣ�
���أ�������֡������ݳ���
**********************************************************************/
u16 SetLoadRecDataToPack (uchar nChannel,uchar *Dest,uchar *Src,u16 uiLenth);
u16 SetLoadRecDataToPack (uchar nChannel,uchar *Dest,uchar *Src,u16 uiLenth)
{
    uchar TmpBuffer[5],i;   ////�������ʱ���
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
    TmpCS=CommCalChksum(Dest,TmpLen+3);//У��
    *(Dest+3+TmpLen)=TmpCS;
    *(Dest+3+TmpLen+1)=0xE5;
    
    return (TmpLen+5);
}

/****************************************************************
������Ϊ��u16 GetRecordDataLen(uchar nChannel)
���ܣ���ü�¼���ݳ��ȡ�
��ڣ�ͨ���š�
���������ص����ݳ��ȣ�0����û�����ݡ�
****************************************************************/
u16 GetRecordDataLen(uchar nChannel);
u16 GetRecordDataLen(uchar nChannel)
{
  if(nChannel>=COMM_LOADRECORD_CHENNL_NUM) return 0;
  
  return (stRecordBuffer[nChannel].ucBlockLen-COMM_LOADRECORD_TIME_SIZE-CON_RECORD_DATA_HAVE_CHANNEL);
}

/****************************************************************
������Ϊ��u16 GetRecordDataMaxLen(uchar nChannel)
���ܣ���������ܶ�������
��ڣ�ͨ���š�
���������ص����ݳ��ȣ�0����û�����ݡ�
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

// ����block�׵�ַ
ulong ReadGetBlockAddr(u16 Block)
{
    return Block*CON_RECORD_FLASH_1BLOCK_BYTE+CON_RECORD_FLASH_BLOCK_BLOCKSTATUS_ADDR+FL1_METER_RECORD_STARTADDR;
}


/*********************************************************************************
 * Function:       ����block
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
    BlockNum1 = ulNowPtr/CON_RECORD_FLASH_1BLOCK_RECORD;    //���ָ������block
    BlockNum = Ptr/CON_RECORD_FLASH_1BLOCK_RECORD;      // �ڵڼ���block
    RemainBlock = CON_RECORD_FLASH_1SECTOR_BLOCK-BlockNum%CON_RECORD_FLASH_1SECTOR_BLOCK;// Sector��ʣ�»��м���block��Ҫ����
    
    // ��ѯsector�е�ÿ��block
    for(i=0;i<RemainBlock;i++)
    {
        ulTempAddr = ReadGetBlockAddr(BlockNum);
        ReadDataDirect(ulTempAddr,1,&ucStaus);
        if( (ucStaus & Channel) == Channel )
        {
            if(i==0)        //��һ��Block��ָ��ָ��Block���м䣬ָ��֮ǰ�Ĳ���Ҫ����
            {
                NumInBlock = Ptr%CON_RECORD_FLASH_1BLOCK_RECORD;    // ��block�еĵڼ���
            }
            else                    // �ӵڶ���Block��ʼ��ȫ������
            {
                NumInBlock = 0;
            }
            ReadDataDirect(ulTempAddr+1+NumInBlock,CON_RECORD_FLASH_1BLOCK_RECORD-NumInBlock,&ChanBuffer[0]);
            lens = CON_RECORD_FLASH_1BLOCK_RECORD-NumInBlock;
            for(j=0;j<lens;j++)
            {
                if( ChanBuffer[j] == Channel )
                {
                    ulTempPtr = ReadGetPtr(j+NumInBlock,BlockNum);  // ��ȡָ��
                    return ulTempPtr;
                }
            }
            //�������¼ָ�����ڵ�blockҲû�鵽��¼���������
            if( BlockNum == BlockNum1 )
                return (COMM_RECORDPTR_NULL-1);
        }
        else if(ucStaus == 0x00)                // Խ�磬ֹͣ����
            return (COMM_RECORDPTR_NULL-1);
        BlockNum++;
        BlockNum %= CON_RECORD_FLASH_1FLASH_BLK_NUM;
    }
    return COMM_RECORDPTR_NULL;

}

// ����Sectorȷ��ͷָ��
ulong GetSectorStartPtr(uchar SectorNum);
ulong GetSectorStartPtr(uchar SectorNum)
{
    return (SectorNum*CON_RECORD_FLASH_1SECTOR_RECORD);
}
/*********************************************************************************
 * Function:       ����ĳͨ����ʷN�����ɼ�¼
 * Description:    �ú�������Sector
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:          ͨ���ţ�������ʼָ��
 * Output:         ��������ָ��
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

    ChannelBit = TB_RECORD_CHANNEL_STATUS[nChannel];     // ͨ��
    SectorNum = ulPtr/CON_RECORD_FLASH_1SECTOR_RECORD;    // ��һ��sector

        // ����64��sector��������Ŀ�ʼ
    for(i=0;i<CON_RECORD_FLASH_1FLASH_SECTOR;i++)
    {
        ReadDataDirect( EPL_RECORD_SECTOR_STATUS+SectorNum,1,&ucStatus);
        if((ucStatus & ChannelBit) == ChannelBit)
        {
            ulTempPtr = ReadSearchLastChanBlock(ChannelBit,ulPtr);    // �ӵ�ǰָ�뿪ʼ��block��ʼ����
            if(ulTempPtr == (COMM_RECORDPTR_NULL-1))
                break;
            else if( ulTempPtr != COMM_RECORDPTR_NULL )
            {
                return ulTempPtr;
            }
        }
        
        SectorNum++;
        SectorNum %= CON_RECORD_FLASH_1FLASH_SECTOR;
        ulPtr = GetSectorStartPtr(SectorNum);                                       // �л�Sector������ָ��
    }
    return COMM_RECORDPTR_NULL;

}


///////////��ͨ����N����¼�������У����ͻ�������֡���棩
///����ͨ���ţ���ǰָ�룬֡��ţ�����N�����������ݷŵ�Ŀ�괦
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
        TmpMultArry.Ptr[nChannel] = SearchLastChanRecByPtr(nChannel,ulPtr);   // ����������������ulPtr�������ļ�¼
        if( TmpMultArry.Ptr[nChannel] == COMM_RECORDPTR_NULL )
            return ReturnLenth;
        ulPtr = TmpMultArry.Ptr[nChannel];
        /*--------�¶γ����ֹԽ���ȡ-------*/
        if(ulNowPiont >= ulLastPiont) //�м䲿��
        {
            if(ulPtr > ulNowPiont)
                return ReturnLenth;
        }
        else                         //��ͷ����
        {
            if((ulPtr > ulNowPiont) && (ulPtr < ulLastPiont))
                return ReturnLenth;
        }
        /*--------�϶γ����ֹԽ���ȡ-------*/
        tempTime = ReadLoadTimeByPtr(TmpMultArry.Ptr[nChannel]);
        LongTommHHDDMMYY(tempTime,&buf[0]);
        memcpy(&(TmpMultArry.time),&tempTime,sizeof(RECORDTIM));

        TmpLenth = SetMultRecDataToPack(Dest+ReturnLenth,&TmpMultArry);
        ReturnLenth+=TmpLenth;
        if(ReturnLenth>TmpMaxSize) 
        {
                ReturnLenth-=TmpLenth;
                break;    /////�Ժ�ľͳ����ˡ�
        }

        ulPtr++;
        ulPtr %= CON_RECORD_DATA_RECORD_MAX;
  } 

  
    ///////////////////�Ѻ������ݵ�ָ�봫�����������������������Ա�������
    if(i<ucNomber) 
    {
        TmpPara.ucFrameNo=ucFameNo+1;
        TmpPara.ucFormatLen=sizeof(STR_LAST_LOADREC_ONE);
  
        TmpPara.ucUsed=COMM_PARAMETER_USED;
        //////////�ø��ɼ�¼��ʽĬ��Ϊ07���Լ//////
            TmpPara.ulID=GetCommReadData645ID(COMMTYPE_07);
      
        TmpLastData.Ptr=ulPtr; 
        TmpLastData.OddNum=ucNomber-i;
        TmpLastData.LoadNum=nChannel;
        SaveLastFrameInBuffer(TmpPara,(uchar*)&TmpLastData);
                
                //////////�к�����־
        ReturnLenth|=COMM_READ_RETURN_FRAME_FLAG;

    }
  
  return ReturnLenth;
}


/****************************************************************
������Ϊ��u16 ReadLastNLoadRec(uchar nChannel,uchar ucNomber,uchar *Dest)
���ܣ���ȡ����N����¼��
��ڣ�ͨ���š�����N�����������ݵ�Ŀ��ָ�롣�������ݳ��ȡ�
���������ص����ݳ��ȣ�0����û�����ݡ�
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
���ܣ��Ƚ�2ֵ�Ĵ�С
���룺���Ƚ������Ƚ�����
�����COMM_LOADRECORD_EQU��COMM_LOADRECORD_HT��COMM_LOADRECORD_LT
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
        //��ȡ��ǰblock�������Ч��¼ָ���ʱ��
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
��������u16 SearchPtrByTim(uchar nChannel,ulong ulTime)
���ܣ��Ӹ�����ʱ����ҵ����һ�������ڸ���ʱ��ĵ�ַ��
���룺ͨ���š�������ʱ�䣬������N����¼�����������ݴ�ŵ�λ�á����������ݳ��ȡ�
���أ����ݳ��ȡ�0XFFFF����û�����ݡ�
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

    // ��ȡͷβָ��
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
    // ����ʱ����βָ��ļ�¼ʱ��Ƚ�
    // ����ʱ����βָ��֮ǰ
    ulTempTime = ReadLoadTimeByPtr(StartPtr);
    if( ulGivenTime < ulTempTime )
        return StartPtr;
    
    // ����ʱ����ͷָ��ļ�¼ʱ��Ƚ�
    // ����ʱ����ͷָ��֮�������ݼ�¼
    ulTempTime = ReadLoadTimeByPtr(RecentPtr);
    if( ulGivenTime > ulTempTime )
        return COMM_RECORDPTR_NULL;
    
    if( RecentPtr < StartPtr )     //��ͷ������Ч
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
        ucStatus=ReadChannelNumByPtr(MidPtr);       // ����¼ͨ��
        // �쳣���������¼�������ȣ�����ɾ������������
        if(ucStatus == 0)                                  
        {
            BlockNum = MidPtr/CON_RECORD_FLASH_1BLOCK_RECORD;
            //��ȡ��ǰblock�������Ч��¼ָ���ʱ��
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
            
            // ��ȡ��һblock����ʼָ���ʱ��
            BlockNum = (BlockNum+1)%CON_RECORD_DATA_RECORD_MAX;
            TempPtr2 = ReadGetPtr(0,BlockNum);
            TempTime2 = ReadLoadTimeByPtr(TempPtr2);
            
            // ��ǰʱ��== ��ǰblock�������Ч��¼ʱ�䣬
            // ����ǰblock�������Ч��¼ָ����ΪĿ��ָ��
            if(ulGivenTime == TempTime1)
            {
                y = TempPtr1;
                return (y%CON_RECORD_DATA_RECORD_MAX);
            }
            
            // ��ǰʱ��== ��һblock��ʼ��¼ʱ�䣬
            // ����һblock��ʼ��¼ָ����ΪĿ��ָ��
            if(ulGivenTime == TempTime2)
            {
                y = TempPtr2;
                return (y%CON_RECORD_DATA_RECORD_MAX);
            }
            
            // ��ǰʱ��< ��ǰblock�������Ч��¼ʱ�䣬
            // ����ǰblock�������Ч��¼ָ����Ϊ��������ָ�룬��������
            if(ulGivenTime<TempTime1)
            {
                ymax = TempPtr1;
            }
            
            // ��ǰʱ��>��һblock��ʼ��¼ʱ�䣬
            // ����һblock��ʼ��¼ָ����Ϊ��������ָ�룬��������
            else if(ulGivenTime>TempTime2)
            {
                ymin = TempPtr2;
            }
            
            // ��ǰʱ��> ��ǰblock�������Ч��¼ʱ�� �ҵ�ǰʱ��<��һblock��ʼ��¼ʱ�䣬
            // ����һblock��ʼ��¼ָ����ΪĿ��ָ��
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

    //��С�ڱȽ�ֵ�Ĵ洢�ռ��еĵ�һ��ֵ
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
��������u16 ReadLastNRecByTime(uchar nChannel,ulong ulTime, uchar ucNomber,uchar *Dest)
���ܣ��Ӹ�����ʱ�俪ʼ��������N����¼��
���룺ͨ���š�������ʱ�䣬������N����¼�����������ݴ�ŵ�λ�á����������ݳ��ȡ�
���أ����ݳ��ȡ�0����û�����ݡ�
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


////////////�����ϼ�¼����󳤶�
u16  GetRecordMultDataMaxLen(void);
u16  GetRecordMultDataMaxLen(void)
{
   return (COMM_LOADRECORD_CHANNEL5_MAXSIZE);  
}

// ��ȡ��ʷN����ϼ�¼���ŵ�������
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
    
    TmpMaxSize = GetRecordMultDataMaxLen();         // ��һ֡���ɼ�¼����󳤶�
    ulLastPiont = ulPtr;
    for(i=0;i<ucNomber;i++)
    {   
        while(sflag)
        {
            ucChannel = ReadChannelNumByPtr(ulPtr);         // ��ȡͨ����
            //��¼��ɾ������������
            if(ucChannel == 0)  
            {
                ulPtr=(ulPtr+CON_RECORD_FLASH_1BLOCK_RECORD-ulPtr%CON_RECORD_FLASH_1BLOCK_RECORD)%CON_RECORD_DATA_RECORD_MAX;
                if((ulPTR > ulLastPiont) && (ulPtr >= ulPTR) )  //�м䲿����Ч
                    return ReturnLenth;
                if( (ulPTR < ulLastPiont) && ((ulPtr >= ulPTR) && (ulPtr< ulLastPiont)))    //��ͷ������Ч
                    return ReturnLenth;
            }
            else
                break;
        }
        //��¼�����˳�
        if(ucChannel>COMM_LOADRECORD_CHENNL_NUM)
            return ReturnLenth;

        memset((uchar*)&TmpMultArry,0xFF,sizeof(TIMEMULITIINDEX));      
        ulLastTime = ReadLoadTimeByPtr(ulPtr);              // ��ȡʱ���
        if( ulLastTime == 0xFFFFFF)
            return ReturnLenth;
        memcpy(&(TmpMultArry.time),&ulLastTime,sizeof(RECORDTIM));

        TmpMultArry.Ptr[ucChannel-1] = ulPtr;

        // ��ʣ���ͨ��������һ�Σ�һ�������ѵ���һ��ʱ���
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

        ///�������
        TmpLenth=SetMultRecDataToPack(Dest+ReturnLenth,&TmpMultArry);
        
        ReturnLenth+=TmpLenth;
        if(ReturnLenth>TmpMaxSize)  /////�Ժ�ľͳ����ˡ�
        {
            ReturnLenth-=TmpLenth;
            ulPtr = (ulPtr+CON_RECORD_DATA_RECORD_MAX-1-j)%CON_RECORD_DATA_RECORD_MAX;
            break;    
        }
        
    }
        
    //�Ѻ������ݵ�ָ�봫�����������������������Ա�������
    if(i<ucNomber) 
    {
        TmpPara.ucFrameNo=ucFameNo+1;                       // ֡���
        TmpPara.ucFormatLen=sizeof(STR_LAST_LOADREC_MULT);  // ����ĳ���
        TmpPara.ucUsed=COMM_PARAMETER_USED;                 // ��ʹ��
        TmpPara.ulID=GetCommReadData645ID(COMMTYPE_07); //�ø��ɼ�¼��ʽĬ��Ϊ07���Լ
  
        TmpLastData.Ptr=ulPtr;              // ���浱ǰ��ȡ��ָ�룬�´μ����Ӵ˿�ʼ��ȡ
        TmpLastData.OddNum=ucNomber-i;      // ʣ���ȡ�ĸ��ɼ�¼����
        SaveLastFrameInBuffer(TmpPara,(uchar*)&TmpLastData);
                    
        //////////�к�����־
        ReturnLenth|=COMM_READ_RETURN_FRAME_FLAG;
    }
    return (ReturnLenth);
  
}



/**********************************************************************
��������u16 ReadMultLastNRec (uchar Number,uchar *Dest)
���ܣ���϶�����N����¼
���룺�����Ŀ���,���������ݴ�ŵ�λ�ã����������ݳ���
���أ����ݳ��ȡ�0����û�����ݡ�
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
��������u16 ReadMultNRecByTim (uchar ReadNumber ,uchar *Dest��u16 uiLenth)
���ܣ���϶�����ʱ����N����¼
���룺�����Ŀ���,���������ݴ�ŵ�λ�ã�������ʱ��
���أ����ݳ��ȡ�0����û�����ݡ�
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

/////////��鸺�ɸ�����ʱ���ʽ�Ƿ���Ч
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
     uchar TmpBuffer[10],i;   ////�������ʱ���
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
     TmpCS=CommCalChksum(Dest,TmpLen+3);//У��
     *(Dest+2+TmpLen+1)=TmpCS;
     *(Dest+2+TmpLen+2)=0xE5;
     
     return (TmpLen+5);
 }


//////////��϶�����N����¼
/////�洢λ�õ�ָ�����飬֡��ţ�����N����¼���������洢�ĵ�ַ


////////////���ɼ�¼����֡�Ķ���

u16   CommLoadLastFrameRead(uchar ucPtr,ulong ID,uchar* Dest)
{
    uchar ID2=(uchar)(ID>>16);
    STR_LAST_LOADREC_ONE   TmpLastRec;
    STR_LAST_LOADREC_MULT  TmpLastMult;
    //SEARCHPTRARR           TmpSearchPtr;  
    uchar TmpChannelNo=0;
    u16 ReturnLen=0;
    ulong ulRecentPtr;
    
    if(ID2==0x00)  /////���
    {
          memcpy((uchar*)&TmpLastMult,LastFrameData[ucPtr].Buffer,sizeof(STR_LAST_LOADREC_MULT));
          //memcpy(&TmpSearchPtr,&TmpLastMult,sizeof(SEARCHPTRARR));
          ulRecentPtr = RecordGetNowPoint();    
          if(ulRecentPtr == COMM_RECORDPTR_NULL)
              return ReturnLen;

          ReturnLen=ReadNRecFmMultToBuf(ulRecentPtr,TmpLastMult.Ptr,LastFrameData[ucPtr].HeadPara.ucFrameNo,TmpLastMult.OddNum,Dest);
    }
    else   ////����ͨ��
    {
          TmpChannelNo=ID2-1;
          memcpy((uchar*)&TmpLastRec,LastFrameData[ucPtr].Buffer,sizeof(STR_LAST_LOADREC_ONE));    
          /////////�ȽϺ���֡�����ݵ�ͨ�����Ƿ���ID�ܹ�һ��
           if(TmpChannelNo==TmpLastRec.LoadNum)
           {
               ReturnLen=ReadNRecFmOneChToBuf(TmpChannelNo,TmpLastRec.Ptr,LastFrameData[ucPtr].HeadPara.ucFrameNo,TmpLastRec.OddNum,Dest);
           }
           else   /////��һ��
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
 * Output:         ͨ���ţ�1~6
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

    ucBlockPiont =  RecPtr/CON_RECORD_FLASH_1BLOCK_RECORD;                                  // �ڼ���block
    ucPageInBlock = RecPtr%CON_RECORD_FLASH_1BLOCK_RECORD;                                  // block��ڼ�����¼

    ulTemp = FL1_METER_RECORD_STARTADDR + ucBlockPiont*CON_RECORD_FLASH_1BLOCK_BYTE;        // block ��ַ

    ReadDataDirect(ulTemp+CON_RECORD_FLASH_BLOCK_RECORDSTATUS_ADDR+ucPageInBlock,1,(uchar *)&ChannelTemp);   // ��ȡͨ����
    if( (ChannelTemp == 0) || (ChannelTemp == 0xff) )                                      // ͨ����ɾ��
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
��������u16 ReadMultRecentRec (uchar *Dest)
���ܣ���϶������һ����¼
���룺���������ݴ�ŵ�λ�ã����������ݳ���
���أ����ݳ��ȡ�0����û�����ݡ�
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

    RecentTime = ReadLoadTimeByPtr(RecentPtr);              // ��ȡʱ���
    if( RecentTime == 0xFFFFFF)
        return 0;
    memcpy(&(TmpMultArry.time),&RecentTime,sizeof(RECORDTIM));
    
    ucNowChannel = ReadChannelNumByPtr(RecentPtr);          // ��ȡͨ����
    if(ucNowChannel>COMM_LOADRECORD_CHENNL_NUM)
        return 0;
    TmpMultArry.Ptr[ucNowChannel-1] = RecentPtr;
        
    TempPtr = RecentPtr;
    // ��ǰ��ѯ��ϼ�¼��
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

    
  ///�������
    TmpLenth=SetMultRecDataToPack(Dest,&TmpMultArry);
    return (TmpLenth);
}


/*********************************************************************************
 * Function:       ����ͨ�������¼��block
 * Description:    
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:          
 * Output:         ָ�룬0xffffffff��ʾ�Ҳ���
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

    BlockNum = Ptr/CON_RECORD_FLASH_1BLOCK_RECORD;      // �ڵڼ���block
    WhichBlock = BlockNum%CON_RECORD_FLASH_1SECTOR_BLOCK;   // Sector�еĵڼ���block

    // ��ѯsector�е�ÿ��block
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
 * Function:       ����ĳͨ������ĸ��ɼ�¼
 * Description:    
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:          nChannel   ͨ����0~5��ulNowPiont   ��ǰָ��
 * Output:         Ŀ��ָ��
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
 * Function:       ����ͨ��������ɼ�¼
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
    uchar ucNumber,TmpFlag=0;           ////(TmpFlag=0��ʾ����
                                        ////TmpFlag=1��ʾû�и������ݵ��뷵��ID�ģ�TmpFlag=2��ʾ������ȷû�к���֡��TmpFlag=2��ʾ������ȷ�к���֡)
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
                if(ID2==0x00)  /////���
                {
                    switch(ID0)
                    {
                        case 0x00:                                          ////��������¼��
                            ReturnLen=ReadMultLastNRec(ucNumber,CommExpDataBuff->Buffer);
                            break;
                        case 0x01:                                          ////��ϸ���ʱ���¼��
                            ///////////����ʱ���ʽ�Ƿ���ȷ
                            if(CheckLoadTim(&COMM_LOADRECORD_READOUT_TIME)==COMM_FAIL)
                            {
                                    TmpFlag=0;
                                    ReturnLen=1;
                                    break;
                            }
                            
                            SearchTim=ChangeTimeToData(&COMM_LOADRECORD_READOUT_TIME);
                            ReturnLen=ReadMultNRecByTim (ucNumber,CommExpDataBuff->Buffer,SearchTim);
                            break;
                        case 0x02:                                          /////������һ����¼��
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
                else   ///����ͨ��
                {
                        ucChannelNo=ID2-1;  //  ͨ����  0~5
                        if(GetLoadChannelState(ucChannelNo)==COMM_TURE)     // ���ɼ�¼ģʽ��
                        {
                                switch (ID0)
                                {
                                    case 0x00:     ////�����¼��
                                        ReturnLen=ReadLastNLoadRec(ucChannelNo,ucNumber,CommExpDataBuff->Buffer);
                                        break;
                                    case 0x01:     ////����ʱ���¼��
                                        SearchTim=ChangeTimeToData(&COMM_LOADRECORD_READOUT_TIME);
                                        ReturnLen=ReadLastNRecByTime(ucChannelNo,SearchTim,ucNumber,CommExpDataBuff->Buffer);
                                        break;      
                                    case 0x02:    /////���һ����¼��
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
                        else  ////û�и�����뷵�ش�ID����ȷӦ��֡
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
    else   ////û�и�ID
    {
        TmpFlag=0;
    }   
        
    Dest->strReturnData.ReturnFail=0;
    switch (TmpFlag)
    {
        case 0:
            Dest->strReturnData.ReturnFail=1; ////û�и���
            break;
        case 1:   ////û�и�����뷵�ش�ID����ȷӦ��֡
            Dest->strReturnData.Lenth=0;   
            break;
        case 2:   ////û�з���֡������Ӧ��
            Dest->strReturnData.Lenth=ReturnLen;
            break;
        case 3: ////�з���֡������Ӧ��
            Dest->strReturnData.Lenth=ReturnLen;
            Dest->strReturnData.LastFrame=1;
            break;
        default:
            Dest->strReturnData.ReturnFail=1;  ////û�и���
            break;
    }
    
}






