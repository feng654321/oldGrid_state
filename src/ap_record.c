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
���ܣ�  ���ļ������ɼ�¼����
��Χ��  Ӧ�ò�ֱ�ӵ���
ע�ͣ�  ��
���ߣ�  ����
�汾��  V1.0
����޸�ʱ�䣺2009-01-19
�޸�˵��������
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

//��ʱn����
void Delayms(u16 n)
{ 
    n = n*4;
    for(;n!=0;n--)
        Delay1mS();
}

void RecordPointResetByStep(void);


/*********************************************************************************
 * Function:       RecordClrByType
 * Description:    ����ͨ��,�����Ӧͨ���ĸ��ɼ�¼����
 * Calls:          
 * Called By:      
 * Data Accessed: 
 * Data Updated:  
 * Input:           
        ucType �����ɼ�¼ͨ�����  ��<CON_RECORD_CHANNELS_MAX��

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
    // ��Sector״̬
    WriteDataDirect(&Wr_data[0], EPL_RECORD_SECTOR_STATUS, 256);
    
    //�������ɼ�¼��һ��Block   
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
    if(ulNowPoint>=CON_RECORD_DATA_RECORD_MAX)                          // ��ָֹ�볬��
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
        
 ���ȼ�ס���¹ؼ���Ϣ��
     ÿpage��256�ֽڣ�ֻ�ܴ洢9���������ݣ���Page_Len��ʾҳ���� 
     ÿ��Block��16��page����16*256=4K�ֽڣ���Block_Len��ʾBlock������һ��page���ڴ洢Block��Ϣ���ڶ���page��ʼ�洢�������ݣ�ÿ��Block�ܴ洢15*9=135���������ݣ�
     �ٶ�ÿ����¼����ΪRecord_Len��ָ��ΪPTR����¼����ʼ��ַStAddr
 �����У�
     PTR/135�����ҵ���Ӧ��Block��
     PTR%135��ʾ��ӦBlock�еĵڼ�����¼��
     ��PTR%135��/9���Ǹ�Block�е���һ��page��
     ��PTR%135��%9��ʾ��ӦPage�еĵڼ�����¼��
 
 
 ����������Ϣ֮�����Ǳ���Ժ����׵ĵó�Ѱַ��ʽ��
 StAddr + ��PTR/135��*Block_Len+ ����PTR%135��/9��*Page_Len + ����PTR%135��%9��*Record_Len
 
 *******************************************************************************/ 

ulong RecordChangePointtoAddr(ulong ulNowPoint)
{
    ulong ulTemp;
    ulong ucPageInBlock;
    ulong ucBlockPiont;

    ucBlockPiont =  ulNowPoint/CON_RECORD_FLASH_1BLOCK_RECORD;                              // �ڼ���block
    ucPageInBlock = ulNowPoint%CON_RECORD_FLASH_1BLOCK_RECORD;                              // block��ڼ�����¼

    ulTemp = FL1_METER_RECORD_STARTADDR + ucBlockPiont*CON_RECORD_FLASH_1BLOCK_BYTE;    // block ��ַ
    ulTemp += ((ucPageInBlock+CON_RECORD_FLASH_1PAGE_RECORD)/CON_RECORD_FLASH_1PAGE_RECORD)*CON_RECORD_FLASH_1PAGE_BYTE;    //page��ַ
    ulTemp += (ucPageInBlock%CON_RECORD_FLASH_1PAGE_RECORD)*CON_RECORD_FLASH_1RECORD_BYTE;  // ��¼��ַ
    
    return ulTemp;
}

/*End of ybf on 2010-7-24 15:22 V1.0*/


/*Start of ybf on 2010-7-24 16:2 V1.0*/

void RecordChangeLastPoint(u16 NowBlockNum);
void RecordChangeLastPoint(u16 NowBlockNum)
{
    u16 LastBlkNum;
    ulong ulLastPiont;
    
    NowBlockNum += 1;                                           // ͷָ�����һblock
    if(NowBlockNum>=CON_RECORD_FLASH_1FLASH_BLK_NUM)
        NowBlockNum = 0;
    ulLastPiont=RecordGetLastPoint();                       // ��ȡβָ��   
    if(ulLastPiont == COMM_RECORDPTR_NULL)
        return ;
    LastBlkNum=ulLastPiont/CON_RECORD_FLASH_1BLOCK_RECORD;      // βָ������Block

    if(NowBlockNum == LastBlkNum)                                       //��ͷָ�����һblock����βָ����������ʱ������βָ��
    {
        LastBlkNum += 1;
        if(LastBlkNum>=CON_RECORD_FLASH_1FLASH_BLK_NUM)
            LastBlkNum = 0;
        ulLastPiont = LastBlkNum*CON_RECORD_FLASH_1BLOCK_RECORD;
        RecordSaveLastPoint(ulLastPiont);
    }
}





// ����ͷָ�����һblock��������βָ��
void RecordClrNextBlock(ulong ulNowPoint);
void RecordClrNextBlock(ulong ulNowPoint)
{
    ulong uiTemp1;
    ulong ulTempPtr,ulTempAddr;
        
    
    uiTemp1=ulNowPoint/CON_RECORD_FLASH_1BLOCK_RECORD;          // ͷָ������Block
    uiTemp1 += 1;                                               // ��һblock
    if(uiTemp1>=CON_RECORD_FLASH_1FLASH_BLK_NUM)
        uiTemp1 = 0;
    ulTempPtr = uiTemp1*CON_RECORD_FLASH_1BLOCK_RECORD;
            
    /*---------- ������һ��block-------------*/
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

// �ж���һblock�Ƿ񱻲���
// ����ȫf����ʾ������
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



//ʱ��ص�������岿�ָ��ɼ�¼
// block�ڻص���ɾ�����ָ��ɼ�¼��ָ��ָ����һblock
// ��block�ص���ɾ��Ŀ��block�ڵĲ��ָ��ɼ�¼��������һblock��ָ��ָ����һblock
void RecordClrByTimeBack(ulong OldNowPtr,ulong NewNowPtr);
void RecordClrByTimeBack(ulong OldNowPtr,ulong NewNowPtr)
{
    uchar NumInBlock1,NumInBlock2;
    uchar ClrRecordNum;
    uchar EraseFlag=0;
    //uchar flag;
    u16 BlockNum1,BlockNum2;
    ulong ulTempAddr;
                    //SetLedAlarm();      //4 ���
    BlockNum1 = OldNowPtr/CON_RECORD_FLASH_1BLOCK_RECORD; // �ɵ�ͷָ�����ڵ�Block
    BlockNum2 = NewNowPtr/CON_RECORD_FLASH_1BLOCK_RECORD; // �µ�ͷָ�����ڵ�Block
    
    NumInBlock1 = OldNowPtr%CON_RECORD_FLASH_1BLOCK_RECORD; // �ɵ�ͷָ�����ڵ�Block�еĵڼ���
    NumInBlock2 = NewNowPtr%CON_RECORD_FLASH_1BLOCK_RECORD; // �µ�ͷָ�����ڵ�Block�еĵڼ���
    
    if( BlockNum1 == BlockNum2 )                          // ͬ1��block�ڵ�ʱ��ص�
    {
        ClrRecordNum = NumInBlock1-NumInBlock2+1;
    }
    else                                                  // ��block��ʱ��ص�
    {
        ClrRecordNum = CON_RECORD_FLASH_1BLOCK_RECORD-NumInBlock2;
        EraseFlag = 1;
    }
    
    // ��block��Ϣ�б�ɾ���ĸ��ɼ�¼
    ulTempAddr = ReadGetBlockAddr(BlockNum2);
    ulTempAddr += 1;           // block��Ϣ��ַ
    memset(&Wr_data[0],0xFF,ClrRecordNum);
    WriteDataDirect(&Wr_data[0],ulTempAddr+NumInBlock2,ClrRecordNum);   // ��block��Ϣ��ַ��ɾ���ĸ��ɼ�¼��Ϣ

    // ����ͷָ�룬ָ����һblock���׵�ַ��������ָ��
    BlockNum2 = (BlockNum2+1)%CON_RECORD_FLASH_1FLASH_BLOCK;
    NewNowPtr = ReadGetPtr(0,BlockNum2);
    #if 0
    WriteDataDirect((uchar*)&NewNowPtr, EPL_RECORD_STATUS_START,4);
    #endif
    SetRecordStatusPointStart(NewNowPtr);
    
    // ��block�ص��������ͷָ����һ��block����
    if( EraseFlag == 1 )
    {
        ulTempAddr = ReadGetBlockAddr(BlockNum2);
        WaitClrFlash(ulTempAddr);
        ClrFlashMode();
        //ucSystemBusy += 2;
    }
}

//���������ͬʱ����ϵ����ļ�¼ָ��
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
    // ������ĺ��ʱ�������1�μ�¼֮������Ҫ����
    // ���ԣ������Զ��˳� 
    if(ulNowTime>=TempTime1)
        return;
    
    ucFlgErr=GAL_NO;
    // ���������ָ�룬���˳�
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
    // ָ���쳣�������˳�
    if((ulRecentPiont>=CON_RECORD_DATA_RECORD_MAX)||(ulLastPiont>CON_RECORD_DATA_RECORD_MAX)||(ulRecentPiont==ulLastPiont))
    {
        ucFlgErr=GAL_YES;
    }
    
    // ���1�ε�ʱ��
    ulMaxTime=ReadLoadTimeByPtr(ulRecentPiont);
    //ulTemp=(ulPoint+CON_RECORD_BLOCK_MAX-ulCount+1)%CON_RECORD_BLOCK_MAX;
    //��Զ1�ε�ʱ��
    ulMinTime=ReadLoadTimeByPtr(ulLastPiont);
    // ��������ʱ�䶼���ڵ�ǰϵͳʱ�䣬��������������
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
        
    if( ulRecentPiont < ulLastPiont )     //��ͷ������Ч
    {
        ulRecentPiont += CON_RECORD_DATA_RECORD_MAX;
    }
        
    // ����ʹ�ö��ַ�����Ŀ��ʱ����ָ��
    ulTempMaxPoint=ulRecentPiont;
    ulTempMinPoint=ulLastPiont;
    ucFlgErr=0;
    while(ulTempMinPoint<=ulTempMaxPoint)
    {
        TempPtr=(ulTempMaxPoint+ulTempMinPoint)/2;
        ulTempMidPoint=TempPtr%CON_RECORD_DATA_RECORD_MAX;    // �м�ָ��
        ucStatus=ReadChannelNumByPtr(ulTempMidPoint);       // ����¼ͨ��
        // �쳣���������¼�������ȣ�����ɾ������������
        if(ucStatus == 0)                                  
        {
            BlockNum = ulTempMidPoint/CON_RECORD_FLASH_1BLOCK_RECORD;
            //��ȡ��ǰblock�������Ч��¼ָ���ʱ��
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
            
            // ��ȡ��һblock����ʼָ���ʱ��
            BlockNum = (BlockNum+1)%CON_RECORD_FLASH_1FLASH_BLK_NUM;
            TempPtr2 = ReadGetPtr(0,BlockNum);
            TempTime2 = ReadLoadTimeByPtr(TempPtr2);
            
            // ��ǰʱ��== ��ǰblock�������Ч��¼ʱ�䣬
            // ����ǰblock�������Ч��¼ָ����ΪĿ��ָ��
            if(ulNowTime == TempTime1)
            {
                TempPtr = TempPtr1;
                break;
            }
            
            // ��ǰʱ��== ��һblock��ʼ��¼ʱ�䣬
            // ����һblock��ʼ��¼ָ����ΪĿ��ָ��
            if(ulNowTime == TempTime2)
            {
                TempPtr = TempPtr2;
                break;
            }
            
            // ��ǰʱ��< ��ǰblock�������Ч��¼ʱ�䣬
            // ����ǰblock�������Ч��¼ָ����Ϊ��������ָ�룬��������
            if(ulNowTime<TempTime1)
            {
                ulTempMaxPoint = TempPtr1;
            }
            
            // ��ǰʱ��>��һblock��ʼ��¼ʱ�䣬
            // ����һblock��ʼ��¼ָ����Ϊ��������ָ�룬��������
            else if(ulNowTime>TempTime2)
            {
                ulTempMinPoint = TempPtr2;
            }
            
            // ��ǰʱ��> ��ǰblock�������Ч��¼ʱ�� �ҵ�ǰʱ��<��һblock��ʼ��¼ʱ�䣬
            // ����һblock��ʼ��¼ָ����ΪĿ��ָ��
            else if((ulNowTime>TempTime1)&&(ulNowTime<TempTime2))
            {
                TempPtr = TempPtr1;
                break;
            }

        }
        // ��������
        else                                                
        {
        
            ulMidTime = ReadLoadTimeByPtr(ulTempMidPoint);               // �м�ָ���Ӧ��¼��ʱ��
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
    
    //  ��ǰ��ָ��
    TempPtr=TempPtr%CON_RECORD_DATA_RECORD_MAX;
    //  �����Ƶ������1�ε����ݱ���ʱ�� 
    ulMaxTime=ReadLoadTimeByPtr(TempPtr);
    SetRecordStatusLastTime(ulMaxTime);
    #if 0
    LongTommHHDDMMYY(ulMaxTime,&Wr_data[0]);
    WriteDataDirect(&Wr_data[0],EPL_RECORD_LASTTIME_START,5);
    #endif
    
    TempPtr = SearchSameTimeAfter(TempPtr);
    RecordClrByTimeBack(ulRecentPiont,TempPtr);        // ʱ��ص������ɾ�����ָ��ɼ�¼
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
    //��ȻulGetRecordStatusLastTime���������ݱ������Ǳ��棬�α��ٴ�EPL��
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
        //�ض����Դ���
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

    // bock״̬�ֽڵ�ַ
    ulTemp=ulNowPoint/CON_RECORD_FLASH_1BLOCK_RECORD;
    ulTemp=ulTemp*CON_RECORD_FLASH_1BLOCK_BYTE+CON_RECORD_FLASH_BLOCK_BLOCKSTATUS_ADDR+FL1_METER_RECORD_STARTADDR;
    
    if(GAL_YES==ReadDataDirect(ulTemp,1,&ucTempStatus))
    {
        if((ucTempStatus | ucStatus) != ucTempStatus)                       // ״̬�ֽڷ����仯��д
        {
            ucTempStatus=ucTempStatus | ucStatus;
            WriteDataDirect(&ucTempStatus, ulTemp, 1);
        }
    }
}

// ��¼block��Ϣ�ڸ���ͨ����
void RecordChannelNo(ulong ulRecStatPtr,uchar ucStatus);
void RecordChannelNo(ulong ulRecStatPtr,uchar ucStatus)
{
    ulong ulTemp1,ulTemp2;
    uchar i;
    int k=0;
    uchar ChannelBuff[COMM_LOADRECORD_CHENNL_NUM];
        //uchar bit[6]={0x01,0x02,0x04,0x08,0x10,0x20};
    // bock״̬�ֽڵ�ַ
    ulTemp1=ulRecStatPtr/CON_RECORD_FLASH_1BLOCK_RECORD;
    ulTemp1=FL1_METER_RECORD_STARTADDR+ulTemp1*CON_RECORD_FLASH_1BLOCK_BYTE+CON_RECORD_FLASH_BLOCK_RECORDSTATUS_ADDR;   // ָ������block��ͨ���ŵĴ洢��ַ
    ulTemp2=ulRecStatPtr%CON_RECORD_FLASH_1BLOCK_RECORD;                                        // block�ڵڼ���
    ulTemp1 += ulTemp2;                                                                     // ָ��ָ���ͨ����¼��ַ                                                   

    // �Ƚ�ͨ���Ű�˳�򻺴�
    for(i=0;i<COMM_LOADRECORD_CHENNL_NUM;i++)
    {
        if((ucStatus & TB_RECORD_CHANNEL_STATUS[i]) == TB_RECORD_CHANNEL_STATUS[i] )
            ChannelBuff[k++] = TB_RECORD_CHANNEL_STATUS[i];
    }
    // ��ͨ����һ����д��Flash
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

    // ������Sector  ״̬��Ϣ�ֽڵ�ַ
    ulTemp0=LstNowPtr/CON_RECORD_FLASH_1SECTOR_RECORD;
    ulTemp1=ulNowPoint/CON_RECORD_FLASH_1SECTOR_RECORD;
    // �ж��Ƿ�sector
    if((ulTemp0 != ulTemp1) &&(*(ucStatus+1) != 0))
    {
        ChangeSectorFlg = 1;
        ulTemp1=EPL_RECORD_SECTOR_STATUS+ulTemp1;
    }
    ulTemp0=EPL_RECORD_SECTOR_STATUS+ulTemp0;
    if(GAL_YES==ReadDataDirect(ulTemp0,1,&ucTempStatus[0]))
    {
        // �����һ��sector�����ı䣬ͬʱд�����ֽ�
        if((ucTempStatus[0] | (*ucStatus)) != ucTempStatus[0])                      // ״̬�ֽڷ����仯��д
        {
            ucTempStatus[0]=ucTempStatus[0] | (*ucStatus);
            ucTempStatus[1]=*(ucStatus+1);
            WriteDataDirect(&ucTempStatus[0], ulTemp0, 1+ChangeSectorFlg);
        }
        // �����һ��sectorδ�����ı䣬ֻд��ǰsector
        else if(ChangeSectorFlg)
        {
            ucTempStatus[1]=*(ucStatus+1);
            WriteDataDirect(&ucTempStatus[1], ulTemp1, 1);
        }
    }
}

/*End of ybf on 2010-7-24 15:23 V1.0*/
//ulStatPtr ��¼ǰָ�룬ulNowPoint ��¼��ָ�룬ucTempStauts  ״̬�ֽڣ�ulDataAddr  ���ݵ�ַ
void RecordLoadInfoAndData(ulong ulStatPtr,ulong ulNowPoint,uchar ucTempStauts,ulong ulDataAddr,uchar ucBufferLen);
void RecordLoadInfoAndData(ulong ulStatPtr,ulong ulNowPoint,uchar ucTempStauts,ulong ulDataAddr,uchar ucBufferLen)
{
    
    WriteDataDirect(&Wr_data[0], ulDataAddr, ucBufferLen);      // ��д�ѻ��������
    RecordChangeBlockStatus(ulNowPoint,ucTempStauts);               // ����block��page��д״̬�ֽ�
    RecordChannelNo(ulStatPtr,ucTempStauts);                        // ��block��Ϣ�ڱ���ͨ����
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
 һ�����ɼ�¼���ݸ�ʽ:
 ʱ��+ ͨ���� + ����ʱ��
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
    // AA  ���ʱ����Ϊ0--��ʾ����¼  AA
    if(0==uiTimeBlock)
    {
        return GAL_NO;
    }
    // AA  ������ɱ�־λ0--��ʾ����¼  AA
    if(0==(RAM[RAM_CHARACTER_CHARGE_MODE]&TB_RECORD_ENABLE_ADDBIT[ucType]))
    {
        return GAL_NO;
    }
    uiTimeNow=ValueHexFromBcd(RSOFT_RTC_HOUR);
    uiTimeNow=uiTimeNow*60 + ValueHexFromBcd(RSOFT_RTC_MINUTE);
    // AA ʱ������ȷ   AA
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
    uchar ucTempStauts[2];  // ͨ����Ϣ��bit0~bit5 �ֱ����ͨ��1~6,
    uchar ucBufferLen;      //�������ݳ���
    uchar uchannel;
    uchar ucRecFlag=0;
    uchar L_ChangePageFlg;  // ��ҳ��־
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
                ulNowPoint=RecordGetNowPoint();                         // ��ȡͷָ��
                if(ulNowPoint == COMM_RECORDPTR_NULL)
                    return DLT_RET_SUCC;
                RecStatPtr=ulNowPoint;                  // ��¼����ʼָ�룬����һ���Լ�¼����
                Lul_TempPtr = ulNowPoint;
                uiBlockNum1 = ((ulNowPoint+CON_RECORD_DATA_RECORD_MAX-1)%CON_RECORD_DATA_RECORD_MAX)/CON_RECORD_FLASH_1BLOCK_RECORD;
                ulDataAddr=RecordChangePointtoAddr(ulNowPoint);         // ָ��õ���ַ
                memset(&Wr_data[0],0, 168);                         // ��������ʼ��
                ucTempStauts[0] = 0;                              // ͨ����Ϣ�ֽڳ�ʼ��
                ucTempStauts[1] = 0;
                ucBufferLen=0;
                L_ChangePageFlg = 0;
//                Lul_TempPtr = 0;


                // ���β�ѯ6��ͨ���Ƿ��¼����
                for(uchannel=0;uchannel<COMM_LOADRECORD_CHENNL_NUM;uchannel++)
                {
                    if(GAL_YES==RecordIsNeedRecord(uchannel))                               // ��ѯ��ͨ���Ƿ����㸺�ɼ�¼������
                    {
                        ucRecFlag = 0x01;
                        
                        RecordSaveNowPoint(ulNowPoint+1);                               // ����ͷָ��
                        ucTempStauts[L_ChangePageFlg]=ucTempStauts[L_ChangePageFlg] |TB_RECORD_CHANNEL_STATUS[uchannel];    // ״̬�ֽ�
                        RecordSetChannelData(uchannel,&Wr_data[ucBufferLen]);           // �������ݷŵ�������
                        ucBufferLen=ucBufferLen+CON_RECORD_FLASH_1RECORD_BYTE;  
                        if(GAL_YES==RecordIsNeedNextPage(ulNowPoint))                       // �Ƿ���Ҫ��ҳ����
                        {
                            L_ChangePageFlg = 1;
                            RecordLoadInfoAndData(RecStatPtr,ulNowPoint,ucTempStauts[0],ulDataAddr,ucBufferLen);    // ��¼������Ϣ�͸�������
                            // ����һҳ����ز�����ʼ��                     
                            ucBufferLen=0;
                            //ucTempStauts=0;
                            memset(&Wr_data[0],0, 168);                     // ��������ʼ��
                            RecStatPtr=ulNowPoint+1;
                            if(RecStatPtr>=CON_RECORD_DATA_RECORD_MAX)                          // ��ָֹ�볬��
                                RecStatPtr=0;
                            ulDataAddr=RecordChangePointtoAddr(RecStatPtr); 
                        }
                        ulNowPoint++;                       
                        if(ulNowPoint>=CON_RECORD_DATA_RECORD_MAX)                          // ��ָֹ�볬��
                            ulNowPoint=0;
                    }
                }
                // 6��ͨ����ѯ��ɣ��ж��Ƿ���Ҫд���ݵ�Flash
                if((L_ChangePageFlg == 0) && ((ucTempStauts[0]&0x3F) != 0x00))
                {
                    RecordLoadInfoAndData(RecStatPtr,ulNowPoint,ucTempStauts[0],ulDataAddr,ucBufferLen);        // ��¼������Ϣ�͸�������
                } 
                else if((L_ChangePageFlg == 1) && ((ucTempStauts[1]&0x3F) != 0x00))
                {
                    RecordLoadInfoAndData(RecStatPtr,ulNowPoint,ucTempStauts[1],ulDataAddr,ucBufferLen);        // ��¼������Ϣ�͸�������
                }
                // �м�¼
                if(ucRecFlag == 0x01)
                {
                    RecStatPtr = ulNowPoint-1;
                    if(ulNowPoint==0)                                                   // ��ָֹ�볬��
                        RecStatPtr=CON_RECORD_DATA_RECORD_MAX-1;                    
                    uiBlockNum2 = RecStatPtr/CON_RECORD_FLASH_1BLOCK_RECORD;
                    RecordLastRecordTime();                                             // �������һ�μ�¼ʱ��

                    // ��������һ�µ�Block��¼ʱ����¼Block��ʼʱ��
                    if((uiBlockNum1 != uiBlockNum2))    //||(0xff000000==RecordReadCurrentBlockTime(RecStatPtr))                    // ���block��δ��¼ʱ�䣬��¼blockʱ��
                    {
                        RecordTimetoPoint(&Wr_data[0]);                         // ��ʱ��ת��Ϊmin
                        RecordWriteCurrentBlockTime(RecStatPtr,&Wr_data[0]);    //����ʱ��
                    }
                    
                    RecordChangeLastPoint(uiBlockNum2);                         // ����βָ��
                    
                    // ÿ��¼һ�Σ��ж���һblock�Ƿ񱻲��������û��������������һblock
                    if(0!=IsNextBlockErased(RecStatPtr))
                    {
                        RecordClrNextBlock(RecStatPtr);                         // ������һBlock
                        //ucSystemBusy += 2;
                    }
                    
                    RecordChangeSectorStatus(Lul_TempPtr,ulNowPoint,&ucTempStauts[0]);              // ����������Sector ״̬�ֽ�
                    FLG_SAVE_LOAD = 1;
                }
                ucRecordModeMinute = RSOFT_RTC_MINUTE;
                ucRecordModeWaitTime = 0;
            }
        } 
    }
    return DLT_RET_SUCC;
}






