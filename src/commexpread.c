/*********************************************************************************
    �汾��     :version 0.1
    ģ����       : Զ�̿���ģ��
    �ļ���       : CommExpRead.c
    ����ļ�     : 
    �ļ�ʵ�ֹ��� : ͨ�Ŷ�����ģ��
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

u16 GetCommReadECTypeNum(uchar ControlData);
u16 GetCommReadECBlockNum(uchar ControlData);
u16 GetECDataHistoryOffset(uchar ControlData);
uchar  GetECTBlockFFData(ulong ID,u16 ECBlockPtr,uchar *Dest);
uchar  GetECHistoryFFData(ulong ID,u16 ECBlockPtr,uchar *Dest);
void CommReadECData(STR_READ_RETURN_PARA *Dest,ulong ID);
u16 GetMDDataHistoryOffset(uchar ControlData);
uchar  GetMDTBlockFFData(ulong ID,u16 ECBlockPtr,uchar *Dest);
uchar  GetMDHistoryFFData(ulong ID,u16 ECBlockPtr,uchar *Dest);
void CommReadMDData(STR_READ_RETURN_PARA *Dest,ulong ID);
u16 GetVariableTypeNum(uchar ControlData);
u16 GetEscepecialVariablePtr(uchar ControlData);
void  CommVariableData(STR_READ_RETURN_PARA *Dest,ulong ID);
u16 GetEvenBlockPtr(uchar ControlData);
u16 CommSwitchEvenFailurePtr(uchar ControlData);
u16 CommEvenReadEvenLoseVoltage(ulong ID,uchar *Dest);
u16 CommEvenReadAllLoseVoltage(ulong ID,uchar *Dest);
u16 CommEvenACPLosePower(ulong ID,uchar *Dest);
u16 CommEvenConverse(ulong ID,uchar *Dest);
u16 CommEvenUnblance(ulong ID,uchar *Dest);
u16 CommEvenReverAndOver(ulong ID,uchar *Dest);
u16 CommEvenLoseCurrent(ulong ID,uchar *Dest);
u16 CommEvenPowerOff(ulong ID,uchar *Dest);
u16 CommEvenTypeFailue(ulong ID,uchar *Dest);
u16 CommEvenCheckOutVoltage(ulong ID,uchar *Dest);
u16 CommEvenMDLoad(ulong ID,uchar *Dest);
u16 CommEvenMeterHandle(ulong ID,uchar *Dest);
void CommEvenRecordData(STR_READ_RETURN_PARA *Dest,ulong ID);
void CommReadParaData(STR_READ_RETURN_PARA *Dest,ulong ID);
u16 CommReadFeeze(uchar ucTwoTableaddr,ulong ulID,uchar *Dest);
void CommReadFeezeData(STR_READ_RETURN_PARA *Dest,ulong ID);
uchar GetCommFreezeWord(uchar ucType);
uchar  MDDataToFormat(ulong ID,uchar Lenth,uchar *Dest);
uchar  ECDataToFormat(ulong ID,uchar Lenth,uchar *Dest);
//uchar VariableParaToFormat(ulong ID,uchar Lenth,uchar *Dest);
uchar EvenDataToFormat(ulong ID,uchar Lenth,uchar *Dest);
/////��������ת���ɹ�ԼҪ���ʽ
uchar FreezeDataToFormat(ulong ID,uchar Lenth,uchar *Dest);
////���ڴ洢�ĸ�ʽ�п������Լ�Ĳ���Ӧ,�ʶ����ݽ�����������(����,����,)
//����ID,���ݳ���,���ݵĵ�ַ
uchar  SettleDataToFormat(ulong ID,uchar Lenth,uchar *Dest);
uchar EventDataFormat2(ulong ulID, uchar ucLen, uchar *pucBuf);

/////����ͨ����
void CommControlReadData(void);
////У��ID�Ƿ���Ч
uchar CheckTheIDUsed(ulong ID);

/////��ö������д����������ָ��
u16 GetCommReadTypePtr(uchar ControlData)
{
    u16 i;
    u16 TableNum;
    TableNum=GetCommReadTypeNum();
    
    for (i=0;i<TableNum;i++)
    {
        if (ControlData==TableCommReadBlock[i].ucIDBlockType)
            {
                return i;
            }
    }
    return SWITCH_TABLE_ERR ;
}

/***********************��������*********************************************/
////���������ڵ�����������������һ��
///����������MODE 4��������
u16 GetCommReadECTypeNum(uchar ControlData)
{
    u16 i;
    u16 TableNum;
    
    TableNum=GetECBlockPhaseTableNum();     //��ȡ������ݵı�񳤶�
    
    for (i=0;i<TableNum;i++)
    {
        if ((ControlData>=TableCommPhaseBlock[i].Block1Start)&&(ControlData<=TableCommPhaseBlock[i].Block1END))
        {
            return i;                       //���ش�����ݶ�Ӧ��λ��
        }
    }
    return SWITCH_TABLE_ERR;
}

#if 0
////���ҵ���С���
///����ID��
u16 GetCommReadECBlockNum(uchar ControlData)
{
    u16 i;
    u16 TableNum;
    
    if (ControlData==ECDI2WITHNO) return SWITCH_TABLE_ERR;

    TableNum=GetECTypeBlockTableNum();
            
    for (i=0;i<TableNum;i++)
    {
         if (ControlData==TableReadECBlock[i].ECTypeID)
            {
                return i;
            }
    }
    return SWITCH_TABLE_ERR;
}

////���������ַƫ��
///TableReadECBlock����λ��
///���ص�����ʷ�����ĵ�ַ
u16 GetECDataHistoryOffset(uchar ControlData)
{
    u16 i,Ptr=0,TableNum;
    u16 uiAddr=0;
    
        
    TableNum=GetECTypeBlockTableNum();
    for(Ptr=0;Ptr<TableNum;Ptr++)
    {
      if(TableReadECBlock[Ptr].ECTypeID==ControlData) break;
    }
    
    if(Ptr>=TableNum)  return SWITCH_TABLE_ERR;
    
    if(TableReadECBlock[Ptr].ECUseState==0)  return SWITCH_TABLE_ERR;
    if(TableReadECBlock[Ptr].ECHistoryState==0)  return SWITCH_TABLE_ERR;
        
    for(i=0;i<Ptr;i++)
    {
        if(TableReadECBlock[i].ECHistoryState==1)
        {
            if (TableReadECBlock[i].ECHistoryFeeState==1)
            {
                uiAddr+=(COMM_READ_EC_LENTH*COMM_READ_EC_FEE_MAXSIZE);
            }
            else
            {
                uiAddr+=COMM_READ_EC_LENTH;
            }
        }
    }
        
    return (uiAddr);
}

///00,�ɹ�,01,ʧ��(����С���Ķ���ΪȫFF�Ĳ���)
uchar  GetECTBlockFFData(ulong ID,u16 ECBlockPtr,uchar *Dest)
{
    ulong ECAddr;
    u16  OffsetAddr;
    u16  Lenth;
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
    uchar ID2=(uchar)(ID>>16);
    uchar  TFeeNum=GetSetFeeNumber()+1;
    if (ID1==0xFF)
    {
        if (ID0>COMM_READ_EC_HISTORY)   return COMM_FAIL;
    }
    else
    {
        if (ID1>=TFeeNum) return COMM_FAIL;
        if (ID0>COMM_READ_EC_HISTORY)   return COMM_FAIL;
    }
    
    if (ID0==0)///��ǰ
    {
        ECAddr=TableReadECBlock[ECBlockPtr].ECAddr;
        OffsetAddr=0;
    }
    else //��ʷ
    {
#if (HISTORY_TEST)
        ECAddr=GetTwoTableAddrFromBlock(TYPE_HISTROY_POWER_RECORD,(ID0-1),0);
        if (ECAddr==COMM_READ_EC_GETTWOTABLE_ADDRERR) return COMM_FAIL;     
        OffsetAddr=GetECDataHistoryOffset(ID2);
        if(OffsetAddr==SWITCH_TABLE_ERR) return COMM_FAIL;  
#endif
    }
    
    ECAddr+=OffsetAddr;
    
    if (ID1==0xFF)
    {
    ////�������
        Lenth=COMM_READ_EC_FEE_MAXSIZE;
        Lenth*=COMM_READ_EC_LENTH;
        if (Lenth>COMM_READMAXSIZE)
        {
            ///�������֡������BUFFER��
            /**********************************/
        }
        ReadDataDirect(ECAddr,Lenth,Dest);
    }
    else
    {
        ECAddr+=COMM_READ_EC_LENTH*ID1;
        ReadDataDirect(ECAddr,COMM_READ_EC_LENTH,Dest);
    }
    return COMM_TURE;
}
///00,�ɹ�,����ʧ��
uchar  GetECHistoryFFData(ulong ID,u16 ECBlockPtr,uchar *Dest)
{
    uchar i;
    uchar ID1=(uchar)(ID>>8);
    uchar ID2=(uchar)(ID>>16);
    ulong ECAddr;
    u16  OffsetAddr;
        uchar  TFeeNum=GetSetFeeNumber()+1;
    ////������Χ�ľͷ��ش���
    if (ID1>=TFeeNum) return COMM_FAIL;
  if (TableReadECBlock[ECBlockPtr].ECHistoryState==0) return COMM_FAIL;
    
    ECAddr=TableReadECBlock[ECBlockPtr].ECAddr;
    ECAddr+=ID1*COMM_READ_EC_LENTH;
    ReadDataDirect(ECAddr,COMM_READ_EC_LENTH,Dest);
    
  OffsetAddr=GetECDataHistoryOffset(ID2);
  
#if HISTORY_TEST
    for(i=1;i<=COMM_READ_EC_HISTORY;i++)
    {
        ECAddr=GetTwoTableAddrFromBlock(COMM_EC_HISTORYDATA_START_ADDR,(i-1),0x00);
        if (ECAddr==COMM_READ_EC_GETTWOTABLE_ADDRERR) return COMM_FAIL; 
        ECAddr+=OffsetAddr+COMM_READ_EC_LENTH*ID1;
        ReadDataDirect(ECAddr,COMM_READ_EC_LENTH,Dest+i*COMM_READ_EC_LENTH);
    }
#endif
    return COMM_TURE;
}

#endif
///��������ĵ�������
//����ΪID������Ϊ0�Ļ���ʧ�ܣ�����������ݳ���
#if 0
u16 CommReadECCardData(ulong ID);
u16 CommReadECCardData(ulong ID)
{
    
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
#if(CONFIG_METER_STEP_PERIODPRICE_MODE==CONFIG_METER_STEP_PERIODPRICE_MODE_ENABLE)
    if(ID==0x00900200)
    {
        if(0!=JudgeRemainSign(0,CommExpDataBuff.Buffer))
        // aa �������ʣ����� aa
        {
            memset(CommExpDataBuff.Buffer, 0x00, 4);
        }
        return 4;
    }
    else
    {
        if(ID==0x00900201)
        {
            if(0==JudgeRemainSign(0,CommExpDataBuff.Buffer))
            // aa �������ʣ����� aa
            {
                memset(CommExpDataBuff.Buffer, 0x00, 4);
            }
            return 4;
        }
    }
#endif
#endif
//        return 4;
    return 0;
}
#endif
//////����������
void CommReadECData(STR_READ_RETURN_PARA *Dest,ulong ID)
{
#if 1  
    u16 TmpLen;
    if( GetECDataByID(CommExpDataBuff->Buffer, &TmpLen, ID, COMM_READMAXSIZE)== DLT_RET_SUCC)
    {
        Dest->strReturnData.ReturnFail=0;
        Dest->strReturnData.Lenth=TmpLen;
    }
    else
        Dest->strReturnData.ReturnFail=1;
#else
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
    uchar ID2=(uchar)(ID>>16);
    u16 ECTypePtr;
    u16 ECBlockPtr;
    u16 TmpLen;
    ////�������еĴ���
    ECTypePtr=GetCommReadECTypeNum(ID2);
    if(ECTypePtr!=SWITCH_TABLE_ERR)
    {     
             if(ID2==0x90)    ///��������
             {
                 TmpLen=CommReadECCardData(ID);
                 if(TmpLen==0)
                 {
                    Dest->strReturnData.ReturnFail=1;   
                 }
                 else
                 {
                    Dest->strReturnData.ReturnFail=0;
                    Dest->strReturnData.Lenth=TmpLen;
                 }
             }
             else if(ID2 == 0x0B)   //������������й��ۼ��õ���
             {
                if(ID == 0x000B0000)
                {
                    ReadDataDirect(RAM_KWH_ALL_USE_START, COMM_READ_EC_LENTH, CommExpDataBuff->Buffer);
                    Dest->strReturnData.Lenth=COMM_READ_EC_LENTH;
                    Dest->strReturnData.ReturnFail=0;
                }
                else if(ID == 0x000B0001)
                {
                    ulong ECAddr=GetTwoTableAddrFromBlock(TYPE_HISTROY_USEPOWER_RECORD,(ID0-1),0);
                    //if (ECAddr==COMM_READ_EC_GETTWOTABLE_ADDRERR) return COMM_FAIL;
                    ReadDataDirect(ECAddr, COMM_READ_EC_LENTH, CommExpDataBuff->Buffer);
                    Dest->strReturnData.Lenth=COMM_READ_EC_LENTH;
                    Dest->strReturnData.ReturnFail=0;
                }
                else
                {
                    Dest->strReturnData.ReturnFail=1;
                }
             }
             else
             {
                ECBlockPtr=GetCommReadECBlockNum(ID2);
                if (ECBlockPtr==SWITCH_TABLE_ERR)//û�ҵ�ID
                {
                    Dest->strReturnData.ReturnFail=1;   
                }
                else
                {
                    if (TableReadECBlock[ECBlockPtr].ECUseState==0)   ///û��ʹ�õ�ǰID
                    {
                        Dest->strReturnData.ReturnFail=1;   
                    }
                    else
                    {
                    ///����ô���û�з�����,��ID1ȴ�и��������
                        if ((ID1>0)&&(TableReadECBlock[ECBlockPtr].ECFeeState==0)) //û�и�ID
                        {
                            Dest->strReturnData.ReturnFail=1;
                        }
                        else
                        {
                            if (ID0==0xFF)   ////�������еĵ����������(��ǰ,��ʷ,)
                            {
                                if(GetECHistoryFFData(ID,ECBlockPtr,CommExpDataBuff->Buffer)==COMM_TURE)
                                {
                                    Dest->strReturnData.Lenth=COMM_READ_EC_LENTH*(COMM_READ_EC_HISTORY+1);
                                    Dest->strReturnData.ReturnFail=0;
                                }
                                else 
                                {
                                    Dest->strReturnData.ReturnFail=1;
                                }
                            }
                            else
                            {
                                if (GetECTBlockFFData(ID,ECBlockPtr,CommExpDataBuff->Buffer)==COMM_TURE)  ///��ȷ
                                {
                                    if(ID2==0xFF)
                                    {
                                        Dest->strReturnData.Lenth=COMM_READ_EC_LENTH*COMM_READ_EC_FEE_MAXSIZE;
                                        //��������֡�Ļ���ֱ�ӰѺ���֡��λ
                                        //Dest->strReturnData.LastFrame=1;
                                    }
                                    else
                                    {
                                        Dest->strReturnData.Lenth=COMM_READ_EC_LENTH;
                                    }
                                    
                                    Dest->strReturnData.ReturnFail=0;
                                }
                                else   ///ʧ��
                                {
                                    Dest->strReturnData.ReturnFail=1;
                                }
                            }   
                        }
                    }
                }
             }
    }
    else   ////û�ҵ�ID
    {
            Dest->strReturnData.ReturnFail=1;
    }
#endif    
}
#if 0
/**********************��������*********************************************************/
////����������ʷ��ַƫ��
///TableReadECBlock����λ��
///���ص�����ʷ�����ĵ�ַ
u16 GetMDDataHistoryOffset(uchar ControlData)
{
    u16 i,Ptr,TableNum;
    u16 uiAddr=0;
        
        TableNum=GetECTypeBlockTableNum();
        for(Ptr=0;Ptr<TableNum;Ptr++)
        {
          if(TableReadECBlock[Ptr].ECTypeID==ControlData) break;
        }
        
        if(Ptr>=TableNum)  return SWITCH_TABLE_ERR;
        
        if(TableReadECBlock[Ptr].MDUseState==0)  return SWITCH_TABLE_ERR;
        if(TableReadECBlock[Ptr].MDHistoryState==0)  return SWITCH_TABLE_ERR;
        
    for(i=0;i<Ptr;i++)
    {
                if(TableReadECBlock[i].MDHistoryState==1)
                    {
                        if (TableReadECBlock[i].MDHistoryFeeState==1)
                            {
                                uiAddr+=(COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH)*COMM_READ_MD_FEE_MAXSIZE;
                            }
                        else
                            {
                                uiAddr+=COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH;
                            }
                    }
    }
    return (uiAddr);
}


///00,�ɹ�,01,ʧ��(����С���Ķ���ΪȫFF�Ĳ���)
uchar  GetMDTBlockFFData(ulong ID,u16 ECBlockPtr,uchar *Dest)
{
    ulong ECAddr;
    u16  OffsetAddr;
    u16  Lenth;
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
    uchar ID2=(uchar)(ID>>16);
    
         uchar  TFeeNum=GetSetFeeNumber()+1;
        
    if (ID1==0xFF)
    {
        if (ID0>COMM_READ_MD_HISTORY)       return COMM_FAIL;
    }
    else
    {
        if (ID1>=TFeeNum)  return COMM_FAIL;
        
                if (ID0>COMM_READ_MD_HISTORY)       return COMM_FAIL;
    }
    
    if (ID0==0)///��ǰ
    {
        ECAddr=TableReadECBlock[ECBlockPtr].MDAddr;
        OffsetAddr=0;
    }
    else //��ʷ
    {
#if (HISTORY_TEST)
               // if(ID0>COMM_READ_EC_HISTORY)  return COMM_FAIL;
        ECAddr=GetTwoTableAddrFromBlock(COMM_MD_HISTORYDATA_START_ADDR,(ID0-1),0);
        if (ECAddr==COMM_READ_EC_GETTWOTABLE_ADDRERR) return COMM_FAIL;     
        OffsetAddr=GetMDDataHistoryOffset(ID2);
                if(OffsetAddr==SWITCH_TABLE_ERR) return COMM_FAIL;
#endif
    }
    
    ECAddr+=OffsetAddr;
    
    if (ID1==0xFF)
    {
        //////������õķ��ʸ���
        Lenth=COMM_READ_MD_FEE_MAXSIZE;
        Lenth*=(COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH);
        if (Lenth>COMM_READMAXSIZE)
        {
            ///�������֡������BUFFER��
            /**********************************/
        }
        ReadDataDirect(ECAddr,Lenth,Dest);
    }
    else
    {
        ECAddr+=(COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH)*ID1;
        ReadDataDirect(ECAddr,(COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH),Dest);
    }
    return COMM_TURE;
}

///00,�ɹ�,����ʧ��
uchar  GetMDHistoryFFData(ulong ID,u16 ECBlockPtr,uchar *Dest)
{
    uchar i;
    uchar ID1=(uchar)(ID>>8);
    uchar ID2=(uchar)(ID>>16);
    ulong ECAddr;
    u16  OffsetAddr;
        uchar  TFeeNum=GetSetFeeNumber()+1;
    ////������Χ�ľͷ��ش���
    if (ID1>=TFeeNum) return COMM_FAIL;
  if (TableReadECBlock[ECBlockPtr].MDHistoryState==0) return COMM_FAIL;
    
    ECAddr=TableReadECBlock[ECBlockPtr].MDAddr;
    ECAddr+=ID1*(COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH);
    ReadDataDirect(ECAddr,(COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH),Dest);
    
  OffsetAddr=GetMDDataHistoryOffset(ID2);

#if (HISTORY_TEST) 
    for(i=1;i<=COMM_READ_MD_HISTORY;i++)
    {
        ECAddr=GetTwoTableAddrFromBlock(COMM_MD_HISTORYDATA_START_ADDR,i-1,0x00);
        if (ECAddr==COMM_READ_EC_GETTWOTABLE_ADDRERR) return COMM_FAIL; 
        ECAddr+=OffsetAddr+(COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH)*ID1;
        ReadDataDirect(ECAddr,(COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH),Dest+i*(COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH));
    }
#endif
    return COMM_TURE;
}
#endif
////����������(����������ǹ��ܺ����ݽṹ����ʿ������������һ�ֱ�)
void CommReadMDData(STR_READ_RETURN_PARA *Dest,ulong ID)
{
#if 1  
    u16 TmpLen;
    if( GetMDDataByID(CommExpDataBuff->Buffer, &TmpLen, ID, COMM_READMAXSIZE)== DLT_RET_SUCC)
    {
        Dest->strReturnData.ReturnFail=0;
        Dest->strReturnData.Lenth=TmpLen;
    }
    else
        Dest->strReturnData.ReturnFail=1;
#else
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
    uchar ID2=(uchar)(ID>>16);
    
    u16 MDTypePtr;
    u16 MDBlockPtr;
    
    MDTypePtr = GetCommReadECTypeNum(ID2);          //����ID2����Ҫ������������ABC�����ܵ�
    
    if ((MDTypePtr>3)||(ID2==0))  ///ID����
    {
        Dest->strReturnData.ReturnFail=1;
    } 
    else
    {   //  ��Ϊ�����������õ���ͬһ�ŵ���С���б���������֧�ַ��࣬�ʴ˴�����ID2ֱ���ж������Ƿ�Ϸ�
        if(ID2>=0x15)
        {
            MDBlockPtr = SWITCH_TABLE_ERR;
        }
        else
        {
            MDBlockPtr=GetCommReadECBlockNum(ID2);   ////����ָ��
        }
        if (MDBlockPtr==SWITCH_TABLE_ERR)//û�ҵ�ID
        {
            Dest->strReturnData.ReturnFail=1;
        }
        else
        {
            if (TableReadECBlock[MDBlockPtr].MDUseState==0x00)   ///û��ʹ�ø�ID
            {
                    Dest->strReturnData.ReturnFail=1;
            }
            else  ///
            {
                ///����ô���û�з�����,��ID1ȴ�и��������
                    if ((ID1>0)&&(TableReadECBlock[MDBlockPtr].MDFeeState==0)) //û�и�ID
                    {
                        Dest->strReturnData.ReturnFail=1;
                    }
                    else
                    {
                        if (ID0==0xFF)   ////�������еĵ����������(��ǰ,��ʷ,)
                        {
                            if(GetMDHistoryFFData(ID,MDBlockPtr,CommExpDataBuff->Buffer)==COMM_TURE)
                            {
                              Dest->strReturnData.Lenth=(COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH)*(COMM_READ_MD_HISTORY+1);
                              Dest->strReturnData.ReturnFail=0;
                            }
                            else {Dest->strReturnData.ReturnFail=1;}
                        }
                        else
                        {
                            if (GetMDTBlockFFData(ID,MDBlockPtr,CommExpDataBuff->Buffer)==0)  ///��ȷ
                            {
                                if(ID2==0xFF)
                                {
                                    Dest->strReturnData.Lenth=(COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH)*COMM_READ_EC_FEE_MAXSIZE;
                                    //��������֡�Ļ���ֱ�ӰѺ���֡��λ
                                    //Dest->strReturnData.LastFrame=1;
                                }
                                else
                                {
                                    Dest->strReturnData.Lenth=(COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH);
                                }
                                Dest->strReturnData.ReturnFail=0;
                            }
                            else   ///ʧ��
                            {
                                Dest->strReturnData.ReturnFail=1;
                            }
                          } 
                    }
            }
        }
    }   
#endif    
}

#if 0
/*****************************����******************************************************/
////���ID�ڱ��������ݱ��е�ƫ��
u16 GetVariableTypeNum(uchar ControlData)
{
    uchar i;
    u16  TableNum;
    TableNum=GetVariableTableNum();
    for(i=0;i<TableNum;i++)
    {
        if (ControlData==TableVariable[i].IDType)
        {
                return i;
        }
    }
    return SWITCH_TABLE_ERR;
}

u16 GetEscepecialVariablePtr(uchar ControlData)
{
    uchar i;
    u16  TableNum;
    TableNum=GetEscepecialVariableNum();
    for(i=0;i<TableNum;i++)
    {
        if (ControlData==TableVariableEscipe[i].IDType)
        {
                return i;
        }
    }
    return SWITCH_TABLE_ERR;
}
#endif
/////�������ݵĶ���
void  CommVariableData(STR_READ_RETURN_PARA *Dest,ulong ID)
{
#if 1  
    u16 TmpLen;
    if( GetVRDataByID(CommExpDataBuff->Buffer, &TmpLen, ID, COMM_READMAXSIZE)== DLT_RET_SUCC)
    {
        Dest->strReturnData.ReturnFail=0;
        Dest->strReturnData.Lenth=TmpLen;
    }
    else
        Dest->strReturnData.ReturnFail=1;
#else
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
    uchar ID2=(uchar)(ID>>16);
    u16  DataTypePtr;
    ulong  ECAddr;
    if (ID2==0x80)    ///���������
    {
        if(ID1==0x00)
        {
             DataTypePtr=GetEscepecialVariablePtr(ID0);
             if(DataTypePtr==SWITCH_TABLE_ERR)
             {
                    Dest->strReturnData.ReturnFail=1;
             }
             else
             {
                 if (TableVariableEscipe[DataTypePtr].Used==1)
                    {
                        ReadDataDirect(TableVariableEscipe[DataTypePtr].Addr,TableVariableEscipe[DataTypePtr].UsedLenth,CommExpDataBuff->Buffer);
                        Dest->strReturnData.Lenth=TableVariableEscipe[DataTypePtr].UsedLenth;
                      Dest->strReturnData.ReturnFail=0;
                    }
                    else
                    {
                            Dest->strReturnData.ReturnFail=1;
                    }
             }
        }
        else
        {
            Dest->strReturnData.ReturnFail=1;
        }
    }
    else
    {
            DataTypePtr=GetVariableTypeNum(ID2);
            if (DataTypePtr==SWITCH_TABLE_ERR)  ///����û��
            {
                    Dest->strReturnData.ReturnFail=1;
            }
            else
            {
                    if(TableVariable[DataTypePtr].Used==0) ///û�и�ID
                    {
                            Dest->strReturnData.ReturnFail=1;
                    }
                    else 
                    {
                                if (ID1==0xFF)
                                {
                                    if(TableVariable[DataTypePtr].WithFF==COMM_USE)
                                    {
                                        if(ID0!=0x00)     ////����DI2
                                        {
                                            Dest->strReturnData.ReturnFail=1;
                                        }
                                        else
                                        {
                                            Dest->strReturnData.Lenth=TableVariable[DataTypePtr].UseFormat*TableVariable[DataTypePtr].UsedID1Num;
                                            ReadDataDirect(TableVariable[DataTypePtr].Addr,Dest->strReturnData.Lenth,CommExpDataBuff->Buffer);
                                        Dest->strReturnData.ReturnFail=0;
                                        }
                                    }
                                    else
                                    {
                                            Dest->strReturnData.ReturnFail=1;
                                    }
                                }
                                else
                                {                           
                                        if ((ID1<TableVariable[DataTypePtr].StartID)||(ID1>(TableVariable[DataTypePtr].StartID+TableVariable[DataTypePtr].UsedID1Num-1)))  ///����
                                        {
                                            Dest->strReturnData.ReturnFail=1;
                                        }
                                        else
                                        {
                                            if(ID0==0xFF)
                                            {
                                                    if (TableVariable[DataTypePtr].RecordTim==0)
                                                    {
                                                            Dest->strReturnData.ReturnFail=1;
                                                    }
                                                    else
                                                    {
                                                          Dest->strReturnData.Lenth=TableVariable[DataTypePtr].UseFormat*TableVariable[DataTypePtr].UsedID1Num;
                                                          ReadDataDirect(TableVariable[DataTypePtr].Addr,Dest->strReturnData.Lenth,CommExpDataBuff->Buffer); 
                                                            Dest->strReturnData.ReturnFail=0;
                                                    }
                                            }
                                            else
                                            {
                                                    if(TableVariable[DataTypePtr].RecordTim<ID0)
                                                    {
                                                            Dest->strReturnData.ReturnFail=1;
                                                    }
                                                    else
                                                    {
                                                        if(ID0==0)////(01----09)
                                                        {
                                                                if((ID2<0x01)||(ID2>0x09))
                                                                {
                                                                  Dest->strReturnData.ReturnFail=1;
                                                                }
                                                                else
                                                                {
                                                                  Dest->strReturnData.Lenth=TableVariable[DataTypePtr].UseFormat;
                                                                  ReadDataDirect(TableVariable[DataTypePtr].Addr+TableVariable[DataTypePtr].UseFormat*(ID1-TableVariable[DataTypePtr].StartID),Dest->strReturnData.Lenth,CommExpDataBuff->Buffer); 
                                                                  Dest->strReturnData.ReturnFail=0;
                                                                }
                                                        }
                                                        else    ////(0A---0B)
                                                        {         
                                                                if((ID2>=0x01)&&(ID2<=0x09))
                                                                {
                                                                  Dest->strReturnData.ReturnFail=1;
                                                                }
                                                                else
                                                                {
                                                                  ECAddr=TableVariable[DataTypePtr].Addr+(ID1-TableVariable[DataTypePtr].StartID)*TableVariable[DataTypePtr].RecordTim*TableVariable[DataTypePtr].UseFormat;
                                                                  ECAddr+=(ID0-1)*TableVariable[DataTypePtr].UseFormat;
                                                                  ReadDataDirect(ECAddr,TableVariable[DataTypePtr].UseFormat,CommExpDataBuff->Buffer); 
                                                                  Dest->strReturnData.Lenth=TableVariable[DataTypePtr].UseFormat;
                                                                  Dest->strReturnData.ReturnFail=0;
                                                                }
                                                        }       
                                                    }
                                            }
                                        }
                                }   
                    }       
            }
    }
#endif    
}

/*********************�¼���¼*********************************************/
u16 GetEvenBlockPtr(uchar ControlData)
{
    uchar i;
    u16  TabNum=0;
    TabNum=GetEvenBlockTypeNum();
    for(i=0;i<TabNum;i++)
    {
        if((ControlData>=TableCommEvenType[i].IDTypeStart)&&(ControlData<=TableCommEvenType[i].IDTypeEnd))
        {
            return i;
        }
    }
    return SWITCH_TABLE_ERR;
}

/////�����ڹ������¼�����λ��
u16 CommSwitchEvenFailurePtr(uchar ControlData)
{
    u16    i,TabNum=0;
    TabNum=GetEvenTypeFailureNum();
    for(i=0;i<TabNum;i++)
    {
        if(ControlData==TableCommEvenFAILURE[i].EvenRecordID)
        {
                if(TableCommEvenFAILURE[i].RecordTim==0x00)
                {
                        return SWITCH_TABLE_ERR;
                }
                else
                {
                    return i;
                }
        }
    }
    return SWITCH_TABLE_ERR;
}

////����1���¼��Ĵ���(ʧѹ,Ƿѹ,����,����)
u16 CommEvenReadEvenLoseVoltage(ulong ID,uchar *Dest)
{
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
    uchar ID2=(uchar)(ID>>16);
    u16    TabNum=0;
    uchar k;
    u16  Lenth=0;
    uchar  Addr=0;
    ulong  EvenAddr=0;
    
    TabNum=GetEvenLoseVoltageNum();
    for(k=0;k<TabNum;k++)
    {
        Lenth+=ucEvenLosevoltageLenth[k];
    }
    
    TabNum=GetEvenLoseVoltagePhaseNum();
    for(k=0;k<TabNum;k++)
    {
        if(ID2==TableTwotableAddr[k].IDType)
        {
                break;
        }   
    }
    if (k>=TabNum) return SWITCH_TABLE_ERR;
    switch (ID1)    
    {
        case 0x01:
            Addr=TableTwotableAddr[k].APhaseAddr;
        break;
        case 0x02:
            Addr=TableTwotableAddr[k].BPhaseAddr;
            break;
        case 0x03:
            Addr=TableTwotableAddr[k].CPhaseAddr;
            break;
        default:
            return SWITCH_TABLE_ERR;
    }
    
    EvenAddr=GetTwoTableAddrFromBlock(Addr,ID0-1,0);
    if (EvenAddr==COMM_READ_EC_GETTWOTABLE_ADDRERR) return SWITCH_TABLE_ERR;
#if(COMM_METER_TYPE ==METER_TYPE_THERRPHASE_MORE)  ////�๦��
    ReadDataDirect(EvenAddr,32,Dest);
    ReadDataDirect(EvenAddr+32+20,Lenth-20,Dest+32);     
#elif (COMM_METER_TYPE ==METER_TYPE_THERRPHASE)
    ReadDataDirect(EvenAddr,Lenth,Dest);
#endif  
    return (Lenth); 
}


/////�������¼��е�ȫʧѹ
u16 CommEvenReadAllLoseVoltage(ulong ID,uchar *Dest)
{
    uchar ID0=(uchar)(ID);
    ulong  EvenAddr=0;
        
        uchar ID1=(uchar)(ID>>8);
         if(ID1!=0)  {return SWITCH_TABLE_ERR;}
        
        
    EvenAddr=GetTwoTableAddrFromBlock(TYPE_LOSS_ALL_VOLTAGE_RECORD,ID0-1,0);
    if (EvenAddr==COMM_READ_EC_GETTWOTABLE_ADDRERR) 
        return SWITCH_TABLE_ERR;
    ReadDataDirect(EvenAddr,COMM_EVEN_FAILURE_ALL_LOSEVOLTAGE_LENTH,Dest);
    return (COMM_EVEN_FAILURE_ALL_LOSEVOLTAGE_LENTH);
}

/////�������¼��еĸ�����Դʧ��
u16 CommEvenACPLosePower(ulong ID,uchar *Dest)
{
    uchar ID0=(uchar)(ID);
    ulong EvenAddr=0;
        
        uchar ID1=(uchar)(ID>>8);
         if(ID1!=0)  {return SWITCH_TABLE_ERR;}
        
    EvenAddr=GetTwoTableAddrFromBlock(TYPE_ACPOWER_LOSS_RECORD,ID0-1,0);
    if (EvenAddr==COMM_READ_EC_GETTWOTABLE_ADDRERR) 
        return SWITCH_TABLE_ERR;
    ReadDataDirect(EvenAddr,COMM_EVEN_FAILURE_LOSE_ACPPOWER_LENTH,Dest);
    return COMM_EVEN_FAILURE_LOSE_ACPPOWER_LENTH;
}

/////////��ѹ/����������
u16 CommEvenConverse(ulong ID,uchar *Dest)
{
    uchar ID0=(uchar)(ID);
    uchar ID2=(uchar)(ID>>16);
    u16    TabNum=0;
    uchar k;
    u16  Lenth=0;
    ulong EvenAddr=0;
    uchar ID1=(uchar)(ID>>8);
        
         if(ID1!=0)  {return SWITCH_TABLE_ERR;}
         
    if(ID2==0x07)  ///��ѹ������
    {
            Lenth=TYPE_ORDER_VOLTAGE_RECORD;
    }
    else          
    {
            if(ID2==0x08)   ///����������
            {
                Lenth=TYPE_ORDER_CURRENT_RECORD;
            }
            else {return SWITCH_TABLE_ERR;}
    }
    EvenAddr=GetTwoTableAddrFromBlock(Lenth,ID0-1,0);
    if (EvenAddr==COMM_READ_EC_GETTWOTABLE_ADDRERR) return SWITCH_TABLE_ERR;
    
    TabNum=GetEvenConverseNum();
    Lenth=0;
    for(k=0;k<TabNum;k++)
    {
        Lenth+=ucEvenConverseLenth[k];
    }
        ////2009��07��03 yaoxuxu
        ////zhonglong �����ݽṹ�������µĶ��壬�ʷ��ǵ�ѹ�������������¼��࣬������������Ķ���Ҫ������
        //ReadDataDirect(EvenAddr,Lenth,Dest);  
        ReadDataDirect(EvenAddr,32,Dest);
        ReadDataDirect(EvenAddr+32+20,Lenth-32,Dest+32);

    return (Lenth);
}


/////////��ѹ/������ƽ��
u16 CommEvenUnblance(ulong ID,uchar *Dest)
{
    uchar ID0=(uchar)(ID);
    uchar ID2=(uchar)(ID>>16);
        uchar ID1=(uchar)(ID>>8);
    u16    TabNum=0;
    uchar k;
    u16  Lenth=0;
    ulong EvenAddr=0;
    
    if(ID2==0x09)  ///��ѹ��ƽ��
    {
        Lenth=TYPE_UNBALANCE_VOLTAGE_RECORD;
    }
    else
    {
            if (ID2==0x0A)  ////������ƽ��
            {
                    Lenth=TYPE_UNBALANCE_CURRENT_RECORD;
            }
            else {return SWITCH_TABLE_ERR;}
    }
    
        
        if(ID1!=0)  {return SWITCH_TABLE_ERR;}
          
    EvenAddr=GetTwoTableAddrFromBlock(Lenth,ID0-1,0);
    TabNum=GetEvenVolCurUnblanceNum();
    Lenth=0;
    for(k=0;k<TabNum;k++)
    {
        Lenth+=ucEvenUblanceLenth[k];
    }
        ////////�๦�ܱ�Ƚ����⣬�ȹ�Լ�е�����Ҫ�༸�ֵ���
        ReadDataDirect(EvenAddr,34,Dest);
        ReadDataDirect(EvenAddr+34+20,Lenth-34,Dest+34);
    return (Lenth);
}

////��������,����
u16 CommEvenReverAndOver(ulong ID,uchar *Dest)
{
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
    uchar ID2=(uchar)(ID>>16);
    u16    TabNum=0;
    uchar k;
    u16  Lenth=0;
    ulong EvenAddr=0;
    u16  Addr;
    TabNum=GetEvenConverseNum();
    for(k=0;k<TabNum;k++)
    {
        Lenth+=ucEvenConverseLenth[k];
    }
    
    TabNum=GetEvenLoseVoltagePhaseNum();
    for(k=0;k<TabNum;k++)
    {
        if(ID2==TableTwotableAddr[k].IDType)
        {
                break;
        }   
    }
    if (k>=TabNum) return SWITCH_TABLE_ERR;
    switch (ID1)    
    {
        case 0x01:
            Addr=TableTwotableAddr[k].APhaseAddr;
        break;
        case 0x02:
            Addr=TableTwotableAddr[k].BPhaseAddr;
            break;
        case 0x03:
            Addr=TableTwotableAddr[k].CPhaseAddr;
            break;
        default:
            return SWITCH_TABLE_ERR;
    }
    
    EvenAddr=GetTwoTableAddrFromBlock(Addr,ID0-1,0);
    if (EvenAddr==GAL_GETTWOTABLE_ADDRERR) return SWITCH_TABLE_ERR;
     ////2009��07��03 yaoxuxu
        ////zhonglong �����ݽṹ�������µĶ��壬�ʷ��ǵ�ѹ�������������¼��࣬������������Ķ���Ҫ������
        //ReadDataDirect(EvenAddr,Lenth,Dest);  
        ReadDataDirect(EvenAddr,32,Dest);
        ReadDataDirect(EvenAddr+32+20,Lenth-32,Dest+32);
    return (Lenth); 
        
}


///////����,ʧ��,����
u16 CommEvenLoseCurrent(ulong ID,uchar *Dest)
{
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
    uchar ID2=(uchar)(ID>>16);
    u16    TabNum=0;
    uchar k;
    u16  Lenth=0;
    ulong EvenAddr=0;
    u16  Addr;
    
        TabNum=GetEvenLoseCurrentNum();
        for(k=0;k<TabNum;k++)
        {
            Lenth+=ucEvenLoseCurrentLenth[k];
        }
        
        TabNum=GetEvenLoseVoltagePhaseNum();
        for(k=0;k<TabNum;k++)
        {
            if(ID2==TableTwotableAddr[k].IDType)
            {
                break;
            }   
        }
        if (k>=TabNum) return SWITCH_TABLE_ERR;
        switch (ID1)    
        {
            case 0x01:
                Addr=TableTwotableAddr[k].APhaseAddr;
            break;
            case 0x02:
                Addr=TableTwotableAddr[k].BPhaseAddr;
                break;
            case 0x03:
                Addr=TableTwotableAddr[k].CPhaseAddr;
                break;
            default:
                return SWITCH_TABLE_ERR;
        }
        EvenAddr=GetTwoTableAddrFromBlock(Addr,ID0-1,0);
        if (EvenAddr==GAL_GETTWOTABLE_ADDRERR) return SWITCH_TABLE_ERR;
#if (COMM_METER_TYPE ==METER_TYPE_THERRPHASE)
        ReadDataDirect(EvenAddr,Lenth,Dest);
#elif(COMM_METER_TYPE ==METER_TYPE_THERRPHASE_MORE)
        ReadDataDirect(EvenAddr,32,Dest);
        ReadDataDirect(EvenAddr+32+20,Lenth-20,Dest+32);
#endif
        return (Lenth); 
        
}

////����
u16 CommEvenPowerOff(ulong ID,uchar *Dest)
{
    uchar ID0=(uchar)(ID);
    ulong EvenAddr=0;

    EvenAddr=GetTwoTableAddrFromBlock(TYPE_POWER_DOWN_RECORD,ID0-1,0);
    if (EvenAddr==GAL_GETTWOTABLE_ADDRERR) 
        return SWITCH_TABLE_ERR;
    ReadDataDirect(EvenAddr,COMM_EVEN_FAILURE_POWER_OFF_LENTH,Dest);
    return COMM_EVEN_FAILURE_POWER_OFF_LENTH;
}

///���й������¼���ȫʧѹ��������Դ���硢������
u16 CommEvenTypeFailue(ulong ID,uchar *Dest)
{
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
    uchar ID2=(uchar)(ID>>16);
    u16  uiLenth=0;
    u16  i;
    
    i=CommSwitchEvenFailurePtr(ID2);
    if(i==SWITCH_TABLE_ERR) 
        return SWITCH_TABLE_ERR;
    if(ID0>TableCommEvenFAILURE[i].RecordTim) 
        return SWITCH_TABLE_ERR;
    ////�����ۼ�ʱ��,�ۼƴ���
    if((ID0==0)&&(ID1==0))
    {
        ReadDataDirect(TableCommEvenFAILURE[i].TotalAddr,TableCommEvenFAILURE[i].TotalLenth,Dest);
        return (TableCommEvenFAILURE[i].TotalLenth);
    }
    else
    {
            if (ID0==0)  
                return SWITCH_TABLE_ERR;
            switch(TableCommEvenFAILURE[i].EvenType)
            {
                //case COMM_EVEN_TYPE_VOLTAGE:
                //      uiLenth=CommEvenReadEvenLoseVoltage(ID,Dest);
                //  break;
                case COMM_EVEN_TYPE_ALLLOSEVOLTAGE:
                        uiLenth=CommEvenReadAllLoseVoltage(ID,Dest);
                    break;
                case COMM_EVEN_TYPE_ASSISTANT_POWERLOSE:
                        uiLenth=CommEvenACPLosePower(ID,Dest);
                    break;
                //case COMM_EVEN_TYPE_CONVERSE:
                //    uiLenth=CommEvenConverse(ID,Dest);
                //  break;
                //case COMM_EVEN_TYPE_UNBLANCE:
                //      uiLenth=CommEvenUnblance(ID,Dest);
                //  break;
                //case COMM_EVEN_TYPE_SWIM_OVERLOAD:
                //      uiLenth=CommEvenReverAndOver(ID,Dest);
                //  break;
                //case COMM_EVEN_TYPE_CURRENT_FAILUE:
                //      uiLenth=CommEvenLoseCurrent(ID,Dest);
                //  break;
                case COMM_EVEN_TYPE_POWEROFF:
                        uiLenth=CommEvenPowerOff(ID,Dest);
                    break;
                default:
                    return SWITCH_TABLE_ERR;
            }
            return (uiLenth);
    }
}

/////��ѹ�ϸ���ͳ������
u16 CommEvenCheckOutVoltage(ulong ID,uchar *Dest)
{
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
    
    u16  i;
    u16  TabNum;
    u16  uiLenth=0;
    u16  k;
    ulong EvenAddr;
    TabNum=GetCheckOutVoltageType();
    for(i=0;i<TabNum;i++)
    {
        if(TableVoltagecheckOutaddr[i].IDType==ID1) break;
    }
    if(i>=TabNum) return SWITCH_TABLE_ERR;
    /////��¼����
    TabNum=GetCheckOutVoltageNum();
    for(k=0;k<TabNum;k++)
    {
        uiLenth+=ucEvenVoltagecheckOut[k];
    }
    
    if(ID0==0x00) ///��ǰ
    {
            ReadDataDirect(TableVoltagecheckOutaddr[i].Currently,uiLenth,Dest);
    }
    else   ////��ʷ
    {
            if (ID0>COMM_EVEN_FAILURE_VOLTAGECHECKOUT_RECORD) 
                return SWITCH_TABLE_ERR;
            EvenAddr=GetTwoTableAddrFromBlock(TableVoltagecheckOutaddr[i].HistoryTwoTable,ID0-1,0);
            if (EvenAddr==GAL_GETTWOTABLE_ADDRERR) return SWITCH_TABLE_ERR;
            ReadDataDirect(EvenAddr,uiLenth,Dest);
    }
    return (uiLenth);
}

/////��������
u16 CommEvenMDLoad(ulong ID,uchar *Dest)
{
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
    
    uchar i,k;
    u16  TabNum;
    u16  uilenth=0;
    ulong  Addr;
    
    
    TabNum=GetEvenMDOverLoadTim();
    if((ID1==0x00)&&(ID0==0x00))  ////�����ܴ���
    {
        for(i=0;i<TabNum;i++)
        {
            //uilenth+=ucEvenMDOverLoad[i];
            ReadDataDirect((EPL_DEMAND_OVER_KW_F_COUNT+4*i),COMM_EVENT_COUNT_SIZE,(Dest+i*COMM_EVENT_COUNT_SIZE));
        }
        uilenth = TabNum*COMM_EVENT_COUNT_SIZE;
    }
    else
    {
         if((ID0==0x00)||(ID1==0x00))
            return SWITCH_TABLE_ERR;
         TabNum=GetEvenMDOverLoadRecord();
         for(i=0;i<TabNum;i++)
         {
            if(TableMDOverLoadAddr[i].IDType==ID1) break;
         }
         if(i>=TabNum) 
            return SWITCH_TABLE_ERR;
            
         if (TableMDOverLoadAddr[i].UsedState==COMM_NOUSE) 
            return SWITCH_TABLE_ERR;
         
         Addr=GetTwoTableAddrFromBlock(TableMDOverLoadAddr[i].TwoTableAddr,ID0-1,0);
         if (Addr==GAL_GETTWOTABLE_ADDRERR) return SWITCH_TABLE_ERR;
            
         TabNum=GetEvenMDOverLoadRecordLenth();
         for(k=0;k<TabNum;k++)
         {
            uilenth+=ucEvenMDOverLoadRecord[k];
         }
         ReadDataDirect(Addr,uilenth,Dest);
         // ����1���������ޣ������������¼����ڷ���
         // ��RAMֱ�Ӷ�ȡ�¼�����
         // add by ybf 20100826
         if((ID0==0x01) && (FLG_DEMAND_OVER_ALL_STATUS&TB_DEMANDOVER_ADDBIT[ID1-1]))
         {
            memcpy(Dest+12,(uchar*)&DemandOverData[ID1-1],sizeof(ST_DEMAND_OVER_DATA));
         }
    }
    
    return (uilenth);
}

////������
u16 CommEvenMeterHandle(ulong ID,uchar *Dest)
{
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
    
    u16 i,k;
    u16 TabNum=0;
    u16 TableSize=0,TableLenth=SWITCH_TABLE_ERR;
    ulong EvenAddr;
    uchar TmpBuffer[COMM_READMAXSIZE];
    /////�����ֽ�
    STR_LASTFRAME_IN_PARA  TmpPara;
    TmpPara.ucUsed=COMM_PARAMETER_USED;
    TmpPara.ucCommNo=GetExplainCommNo();
    TmpPara.ulID=ID;
    
    /************ɽ����Ƚ��������������30�μ�¼*�����޸�,������԰�TableEvenMeterHandle��
       ���Ľṹ����һ����¼���������ͨ���жϼ�¼��������֤ID����Ч��***************************************/
    if((ID1==0x01)||(ID1==0x0F))
    {
      if(ID0>30) return SWITCH_TABLE_ERR;
    }
    else
    {
      if(ID0>COMM_EVEN_RECORD_NUM) return SWITCH_TABLE_ERR;
    }
        
        
    TabNum=GetEvenMeterHandileNum();

    for(i=0;i<TabNum;i++)
    {
        if(TableEvenMeterHandle[i].IDType==ID1) break;
    }
    if(i>=TabNum)   return SWITCH_TABLE_ERR;
        
    if (TableEvenMeterHandle[i].UsedState==COMM_NOUSE)  return SWITCH_TABLE_ERR;
        
    if(ID0==0x00) ///��¼���ܴ���
    {
        ReadDataDirect(TableEvenMeterHandle[i].TotalAddr,COMM_EVEN_METER_HANDLE_TOTAL,Dest);
        return (COMM_EVEN_METER_HANDLE_TOTAL);
    }
    else    ////��¼������
    {
        ////��ø��������¼���ͷ��ַ
        EvenAddr=GetTwoTableAddrFromBlock(TableEvenMeterHandle[i].TwoTableAddr,ID0-1,0);
        if (EvenAddr==GAL_GETTWOTABLE_ADDRERR) 
            return SWITCH_TABLE_ERR;
        ////��ȡ�洢оƬ,�������,(����,��������,��������,��Щ�����,��Ҫ���չ�Լ�����½���)
        TableSize=TableEvenMeterHandle[i].UseTableSize;
        TableLenth=0;
        for(k=0;k<TableSize;k++)
        {
            TableLenth+=(*(TableEvenMeterHandle[i].RecordTableLenth+k));
        }
        
#if (COMM_METER_TYPE ==METER_TYPE_THERRPHASE)   ////������
        ReadDataDirect(EvenAddr,TableLenth,Dest);
#elif(COMM_METER_TYPE ==METER_TYPE_THERRPHASE_MORE)  /////�๦��
        /////////////////////�������๦�ܱ�洢���������ĵ���,�๦�ܴ洢�����ݱȹ�Լ��Ҫ��ܶ�
        switch (ID1)
        {
            case 0x01:   ////�������
                ////��������ʱ��,�����ߴ���
                i=0;
                ReadDataDirect(EvenAddr,10,Dest);
                EvenAddr+=10;
                ///�����й��ܵ���
                i+=10;
				ReadDataDirect(EvenAddr+5*15,5,Dest+i);
                ////�����й�
                i+=5;
				ReadDataDirect(EvenAddr+5*30,5,Dest+i);
                ///1�����޹�
                i+=5;
				ReadDataDirect(EvenAddr+5*75,5,Dest+i);
                ///2�����޹�
                i+=5;
				ReadDataDirect(EvenAddr+5*90,5,Dest+i);
                ///3�����޹�
                i+=5;
				ReadDataDirect(EvenAddr+5*105,5,Dest+i);
                ///4�����޹�
                i+=5;
				ReadDataDirect(EvenAddr+5*120,5,Dest+i);
                ///A��
                i+=5;
				ReadDataDirect(EvenAddr+5*167,10,Dest+i);
                i+=10;
				ReadDataDirect(EvenAddr+5*171,20,Dest+i);
                ///B��
                i+=20;
				ReadDataDirect(EvenAddr+5*179,10,Dest+i);
                i+=10;
				ReadDataDirect(EvenAddr+5*183,20,Dest+i);
                ///C��
                i+=20;
				ReadDataDirect(EvenAddr+5*191,10,Dest+i);
                i+=10;
				ReadDataDirect(EvenAddr+5*195,20,Dest+i);
                TableLenth=10+24*5;
                break;
            case 0x02:   ////��������
                ////��������ʱ��,�����ߴ���
                i=0;
                ReadDataDirect(EvenAddr,10,Dest);
                EvenAddr+=10;
                ////�����й���
                i+=10;
                ReadDataDirect(EvenAddr,9,Dest+i);
                ///�����й�
                i+=9;
				ReadDataDirect(EvenAddr+9*15,9,Dest+i);
                ///1�����޹�
                i+=9;
				ReadDataDirect(EvenAddr+9*60,9,Dest+i);
                ///2�����޹�
                i+=9;
				ReadDataDirect(EvenAddr+9*75,9,Dest+i);
                ///3�����޹�
                i+=9;
				ReadDataDirect(EvenAddr+9*90,9,Dest+i);
                ///4�����޹�
                i+=9;
				ReadDataDirect(EvenAddr+9*105,9,Dest+i);
                ///A��
                i+=9;
				ReadDataDirect(EvenAddr+9*150,18,Dest+i);
				i+=18;
				ReadDataDirect(EvenAddr+9*154,36,Dest+i);
				///B��
				i+=36;
				ReadDataDirect(EvenAddr+9*160,18,Dest+i);
				i+=18;
				ReadDataDirect(EvenAddr+9*164,36,Dest+i);
				///C��
				i+=36;
				ReadDataDirect(EvenAddr+9*170,18,Dest+i);
				i+=18;
				ReadDataDirect(EvenAddr+9*174,36,Dest+i);
                
                TableLenth=10+12*9;
                
                ////////�����µ�12*9���ֽ�����д�����֡BUbuffer��
                //ReadDataDirect(Dest+TableLenth,108,TmpBuffer);
                memcpy(TmpBuffer,Dest+TableLenth,108);
                TmpPara.ucFrameNo=1;
                TmpPara.ucFormatLen=108;
                if (SaveLastFrameInBuffer(TmpPara,TmpBuffer)==COMM_FAIL) 
                    return SWITCH_TABLE_ERR;
                           
                TableLenth=TableLenth|COMM_READ_RETURN_FRAME_FLAG;
                break;
            case 0x05: /////��ʱ�α���
                ReadDataDirect(EvenAddr,10,Dest);
                TableSize=TableLenth-10;
                
                EvenAddr+=10;
                ReadDataDirect(EvenAddr,TableSize,Dest+10);
                //////�����µ�����д�����֡BUbuffer��
                for(i=1;i<4;i++)
                {
                    ReadDataDirect(EvenAddr+i*TableSize,TableSize,TmpBuffer);
                    TmpPara.ucFrameNo=i;
                    TmpPara.ucFormatLen=TableSize;
                    if (SaveLastFrameInBuffer(TmpPara,TmpBuffer)==COMM_FAIL) return SWITCH_TABLE_ERR;
                }
                ///�������з���֡��.
                TableLenth=TableLenth|COMM_READ_RETURN_FRAME_FLAG;
                break;
            case 0x08:  /////�ڼ��ձ�̼�¼
                ReadDataDirect(EvenAddr,10,Dest);
                //////
                TableSize=TableLenth-10;
                EvenAddr+=10;
                ReadDataDirect(EvenAddr,TableSize,Dest+10);
                EvenAddr+=TableSize;
                //////�����µ�����д�����֡BUbuffer��
                TableSize=42*4;
                for(i=1;i<6;i++)
                {
                    ReadDataDirect(EvenAddr+(i-1)*TableSize,TableSize,TmpBuffer);
                    TmpPara.ucFrameNo=i;
                    TmpPara.ucFormatLen=TableSize;
                    if (SaveLastFrameInBuffer(TmpPara,TmpBuffer)==COMM_FAIL) 
                        return SWITCH_TABLE_ERR;
                }
                ///�������з���֡��.
              TableLenth=TableLenth|COMM_READ_RETURN_FRAME_FLAG;
                break;
            default:
                ReadDataDirect(EvenAddr,TableLenth,Dest);
                break;
        }
#endif
            return (TableLenth);
    }
}

////�������
u16 CommEvenMeterCard(ulong ID,uchar *Dest);
u16 CommEvenMeterCard(ulong ID,uchar *Dest)
{
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
    uchar ID2=(uchar)(ID>>16);
    u16  Lenth=SWITCH_TABLE_ERR;
    ulong Addr;
    
    switch(ID2)
    {
      case 0x33:
        if(ID1!=0x00) return (SWITCH_TABLE_ERR);
        if((ID0==0)||(ID0>COMM_EVEN_RECORD_NUM))return (SWITCH_TABLE_ERR); 
        Addr=GetTwoTableAddrFromBlock(TYPE_BUY_MONEY_RECORD,ID0-1,0);
        if (Addr==GAL_GETTWOTABLE_ADDRERR) return SWITCH_TABLE_ERR;
        Lenth=26;
        ReadDataDirect(Addr,Lenth,Dest);
        break;
      default:    
       return (SWITCH_TABLE_ERR);
    }
    
     return (Lenth);
}


/////����բ�¼���¼
u16 CommEvenCutGate(ulong ID,uchar *Dest);
u16 CommEvenCutGate(ulong ID,uchar *Dest)
{
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
  //  uchar ID2=(uchar)(ID>>16);
    ulong Addr;
    u16  uiLenth;
    u16 EvenPtr; 
    u16 i;

    ////ɽ����Ƚ������բû���ܴ���
    if((ID1!=0x00)&&(ID0==0X00)) 
        return (SWITCH_TABLE_ERR);
    //////�ܴ���
    if(ID0==0x00)
    {
      Addr=EPL_TOTAL_RELAY_OPEN_COUNT;
      uiLenth=3;
    }
    else
    {
       EvenPtr=GetCTSTGateNum();
    
      for(i=0;i<EvenPtr;i++)
      {
          if (TableCommCSGate[i].EvenType==ID1) break;
      }
      if(i>=EvenPtr) return (SWITCH_TABLE_ERR);
      if(TableCommCSGate[i].UsedState==COMM_NOUSE)  return (SWITCH_TABLE_ERR);
      
      if(ID0>TableCommCSGate[i].RecordTim)  return (SWITCH_TABLE_ERR);
      Addr=GetTwoTableAddrFromBlock(TableCommCSGate[i].RecordAddr,(ID0-1),0);
      if (Addr==GAL_GETTWOTABLE_ADDRERR) return SWITCH_TABLE_ERR;
      uiLenth=LENGTH_RELAY_EVENT;
    }
    ReadDataDirect(Addr,uiLenth,Dest);
    
    return (uiLenth);

}

/*********************************************************************************************************
**��������: void GetEventRecordData1(STR_READ_RETURN_PARA *Dest,ulong ID)
**����: Dest���������Ϣ��ŵĽṹ��ָ��,IDͨ������ID
**���: 
**˵��: �ⲿ�������ǲ����Լ����û�иĶ����¼���¼,Ϊ�˳�������,���ⲿ�����ݴ�ԭ����CommEvenRecordData
**      ��������,���޸Ĳ������ݲ���
** ȫ�ֱ���:
** ����ģ��:
**
**------------------------------------------------------------------------------------------------------
** ������: zlq
** �ա���: 2009��09��23��
********************************************************************************************************/
void GetEventRecordData1(STR_READ_RETURN_PARA *Dest,ulong ID);
void GetEventRecordData1(STR_READ_RETURN_PARA *Dest,ulong ID)
{
    
    uchar ID2=(uchar)(ID>>16);
        
    u16  uiLenth;
    u16 EvenPtr;
    EvenPtr=GetEvenBlockPtr(ID2);
    if (EvenPtr==SWITCH_TABLE_ERR)
    {
        Dest->strReturnData.ReturnFail=1;
    }
    else
    {
        if (TableCommEvenType[EvenPtr].UsedState!=COMM_USE)
        { 
            Dest->strReturnData.ReturnFail=1;
        }
        else
        {
            switch (TableCommEvenType[EvenPtr].IDType)
            {
            case COMM_EVEN_BLOCK_FAILURE:   ///�������¼��Ĵ���
                uiLenth=CommEvenTypeFailue(ID,CommExpDataBuff->Buffer);
                break;
            case COMM_EVEN_BLOCK_VOLTAGE_CHECKOUT:////��ѹ�ϸ���
                    uiLenth=CommEvenCheckOutVoltage(ID,CommExpDataBuff->Buffer);
                break;
            case COMM_EVEN_BLOCK_MD_OVER:   /// ��������
                    uiLenth=CommEvenMDLoad(ID,CommExpDataBuff->Buffer);
                    break;
            case COMM_EVEN_BLOCK_METER_HANDLE:  /// ��������
                    uiLenth=CommEvenMeterHandle(ID,CommExpDataBuff->Buffer);
                break;
            case COMM_EVEN_BLOCK_METER_CUTGATE:
                    uiLenth=CommEvenCutGate(ID,CommExpDataBuff->Buffer); 
                    break;
            default:
                Dest->strReturnData.ReturnFail=1;
                return;
            }
            if (uiLenth!=SWITCH_TABLE_ERR)
            {
                if (uiLenth&COMM_READ_RETURN_FRAME_FLAG)
                {
                    Dest->strReturnData.LastFrame=1;
                    uiLenth&=~COMM_READ_RETURN_FRAME_FLAG;
                }
                Dest->strReturnData.Lenth=uiLenth;
                Dest->strReturnData.ReturnFail=0;
            }
            else
            {
                Dest->strReturnData.ReturnFail=1;
            }
        }
    }
}

/*********************************************************************************************************
**��������: uchar IsEventIDValid(uchar ucID1, uchar ucID0, S_IDCONV1* psIDConv)
**����: ucID1,ucID0��ǰͨ��ID�еĵ����ֽڲ�����Ϣ,psIDConvָ��ǰID��Ӧ���¼���¼IDת�����ָ��
**���: 0-ID���� / 1-ID��ȷ
**˵��: 
** ȫ�ֱ���:
** ����ģ��:
**------------------------------------------------------------------------------------------------------
** ������: zlq
** �ա���: 2009��09��23��
********************************************************************************************************/
uchar IsEventIDValid(uchar ucID1, uchar ucID0, S_IDCONV1* psIDConv);
uchar IsEventIDValid(uchar ucID1, uchar ucID0, S_IDCONV1* psIDConv)
{
    //С���ж�,�����ڵ����ķַ�������
    if(ucID1 == 0)
    {
        return 0;
    }
    
    if((ucID1 > psIDConv->ucSim1) && (ucID1 != 0xFF))
    {
        return 0;
    }
    
    //����,�����ڵ������·�
    if(((ucID0 > (psIDConv->ucSim0+1)) && (ucID0 != 0xFF))||(ucID0 == 0x00))
    {
        return 0;
    }
    
    //����
    if((ucID0 == 0xFF) && (ucID1 == 0xFF))
    {
        return 0;
    }
    
    return 1;
}

/*********************************************************************************************************
**��������: void GetEventData(STR_READ_RETURN_PARA *Dest, uchar ucID0, uchar ucID1, S_IDCONV1* psIDConv)
**����: Destָ��ͨ�ŷ�����Ϣ��ָ��,ucID1,ucID0��ǰͨ��ID�еĵ����ֽڲ�����Ϣ,
**      psIDConvָ��ǰID��Ӧ���¼���¼IDת�����ָ��
**���: none
**˵��: ���ʱ���ID�϶�����ȷ��,��˲���Ҫ��������Ϸ����б�
** ȫ�ֱ���:
** ����ģ��:
**------------------------------------------------------------------------------------------------------
** ������: zlq
** �ա���: 2009��09��23��
**------------------------------------------------------------------------------------------------------
** �޸���  : pylon_zlq
** �޸�����: 1.��������������ʾ��Ҫ����5�ֽ����ݲ���,��ͨѶȴֻҪ4�ֽ�����,���ǰ�α���δ���Ǵ�����,���
**             ������ʾ�ϵ�bug,Ϊ����������,�����¼������޸�
**           2.������ʾ�����ܴ�FF����������,����ⲿ�ִ������ɱ��ֲ���,ͬʱ���Ҳ����,��������������
**           3.ֻ�е�������������ſ�������ʾԴ����ȡ����,��˶Դ����������������ͼ����б�,0ʱ�ǵ���������
**             ����Ҫ�ı�,1ʱΪ����������,��Ҫ5�ֽڸ���;��ԭ�����¼��������ݷ������,�Ե��������Ѿ�ƫ��©
**             ȥ��5���ֽ�,�����Ҫƫ�ƻ���,���Ҷ�Ӧ����Ҫ����һ���ֽ�
**           4.��ͨѶ���ڸ�ʽ����ĵط��Ե���ĵ��������ݻ�5�ֽ�Ϊ4�ֽ�
** �޸�����: 2010��07��01��
********************************************************************************************************/
void GetEventData(STR_READ_RETURN_PARA *Dest, S_IDCONV1* psIDConv, uchar ucID0, uchar ucID1);
void GetEventData(STR_READ_RETURN_PARA *Dest, S_IDCONV1* psIDConv, uchar ucID0, uchar ucID1)  
{
    uchar i;
    uchar ucLen = 0;
    uchar* p = CommExpDataBuff->Buffer;
    S_EVFMT* psEF = (S_EVFMT*)psIDConv->pvFmt;
    ulong ulAddr;
    
    if(ucID0 != 0xFF)                               //�������ݶ�ȡ,��ȻҲ�п����Ǽ���,�Ǿ�Ҫ��ucID1��ֵ��
    {
        ulAddr =GetTwoTableAddrFromBlock(psIDConv->ucType, ucID0 - 1, 0);
        if(ucID1 == 0xFF)                           //���ݼ���,�к���֡�������
        {
            for(i=1; i<=psIDConv->ucSim1; i++)      //ע����������ж�Ҫ����==,���ǽ����ʱ����ɵ�
            {
                ReadDataDirect(ulAddr+psEF->ucOffset, psEF->ucLen, p);
                ucLen += psEF->ucLen;
                p += psEF->ucLen;
                psEF++;
            }
        }
        else                                        //ĳһ�ε��������ݼ�¼��ȡ
        {
            psEF += ucID1 - 1;
            if(NOACT==psEF->ucType)   //if (ucType == 2), then it is not active any more
            {
                return;
            }
            ucLen = psEF->ucLen;
            if(1==psEF->ucType)
            {
                ucLen++;
                ulAddr--;
            }
            ReadDataDirect(ulAddr + psEF->ucOffset, ucLen, p);
        }
    }
    else                                            //psIDConv->ucID0+1���������ݶ�ȡ
    {
        psEF += ucID1 - 1;
        for(i=0; i<=psIDConv->ucSim0; i++)          //ע����������ж�Ҫ����==,���ǽ����ʱ����ɵ�
        {
            ulAddr =GetTwoTableAddrFromBlock(psIDConv->ucType, i, 0) + psEF->ucOffset;
            ReadDataDirect(ulAddr, psEF->ucLen, p);
            ucLen += psEF->ucLen;
            p += psEF->ucLen;
            //psEF++;
        }
    }
    
    Dest->strReturnData.Lenth = ucLen;
    Dest->strReturnData.ReturnFail = 0;
}


/*********************************************************************************************************
**��������: void GetEventRecordData2(STR_READ_RETURN_PARA *Dest, ulong ulID, ulong ulVirtualID)
**����: Destָ��ͨ�ŷ�����Ϣ��ָ��,ulID��ǰͨ��ID,ulVirtualID����ת��������ID
**���: none
**˵��: ���ǲ����Լ�޸Ĳ��ֵ��¼���¼����,���ڽ����ʶ���д�С�����Ե��,�ʶԳ�Աid�ļ����������һ����ʼ
** ȫ�ֱ���:
** ����ģ��:
**------------------------------------------------------------------------------------------------------
** ������: zlq
** �ա���: 2009��09��23��
********************************************************************************************************/
void GetEventRecordData2(STR_READ_RETURN_PARA *Dest, ulong ulID, ulong ulVirtualID);
void GetEventRecordData2(STR_READ_RETURN_PARA *Dest, ulong ulID, ulong ulVirtualID)
{
    uchar i;
    uchar ucID0 = (uchar)ulID;
    uchar ucID1 = (uchar)(ulID>>8);
    S_IDCONV1* psIDConv = (S_IDCONV1*)gCs_IDConv1 + (gCuc_IDConv1TabNum - 1);//�����¼������һ����Աָ��
    
    for(i=0; i<gCuc_IDConv1TabNum; i++)
    {
        if((ulID >= psIDConv->ulVID) && (ulVirtualID == psIDConv->ulVID))   //���ҵ���Ӧ�ĳ�Ա��Ϣ
        {
            if(IsEventIDValid(ucID1, ucID0, psIDConv) == 1)
            {
                GetEventData(Dest, psIDConv, ucID0, ucID1);                 //ID�Ϸ�,���Զ�ȡ����,
                return;
            }
            
            break;
        }
        psIDConv--;
    }
    
    Dest->strReturnData.ReturnFail = 1;                                     //û�в��ҵ���ӦID
}

/*********************************************************************************************************
**��������: void GetEventTotalCntAndTime(STR_READ_RETURN_PARA *Dest, ulong ID)
**����: Destָ��ͨ�ŷ�����Ϣ��ָ��,ulID��ǰͨ��ID
**���: none
**˵��: ���ǲ����Լ�޸Ĳ��ֵ��¼���¼����,�����¼�����ۼƴ������ۼ�ʱ��,���ڹ�Լ���嶼��3�ֽڵ�BCD��,
**      ���ֱ�Ӳ�ѯID�õ���Ӧ�����ݵ�ַ,ֱ�ӻ�ȡ
** ȫ�ֱ���:
** ����ģ��:
**------------------------------------------------------------------------------------------------------
** ������: zlq
** �ա���: 2009��09��23��
********************************************************************************************************/
uchar GetEventTotalCntAndTime(STR_READ_RETURN_PARA *Dest, ulong ID);
uchar GetEventTotalCntAndTime(STR_READ_RETURN_PARA *Dest, ulong ID)
{
    uchar i;
    S_CNTTIME* psCntTm = (S_CNTTIME*)gCS_CntAndTimeTab;
    for(i=0; i<gCuc_CntAndTimeTabNum; i++)
    {
        if(psCntTm->ulID == ID)
        {
            Dest->strReturnData.Lenth=3;
            Dest->strReturnData.ReturnFail=0;
            ReadDataDirect(psCntTm->ulAddr, 3, CommExpDataBuff->Buffer);
            return 1;
        }
        psCntTm++;
    }
    
    Dest->strReturnData.ReturnFail = 1;
    return 0;
}

/*********************************************************************************************************
**��������: void CommEvenRecordData(STR_READ_RETURN_PARA *Dest,ulong ID)
**����: Destָ��ͨ�ŷ�����Ϣ��ָ��,ulID��ǰͨ��ID
**���: none
**˵��: �¼����ݼ�¼�Ķ���,���ڲ����Լ���޸�,�����ⲿ��������Ҫ���ϴ�Ķ�,��˽�ԭ����һ�������ֳɼ�������
**      ����,���°��ոĶ���δ�Ķ������ʵ��,
** ȫ�ֱ���:
** ����ģ��:
**------------------------------------------------------------------------------------------------------
** ������: zlq
** �ա���: 2009��09��23��
********************************************************************************************************/
void CommEvenRecordData(STR_READ_RETURN_PARA *Dest,ulong ID)
{
    /*del by zlq090922,�������ⲿ�����ݶ����������һ������,��Ȼ��Ҫ�ĵ��ĵط��������ֲʱȥ��
    
    uchar ID2=(uchar)(ID>>16);
        
    u16  uiLenth;
    u16 EvenPtr;
    EvenPtr=GetEvenBlockPtr(ID2);
    if (EvenPtr==SWITCH_TABLE_ERR)
    {
            Dest->strReturnData.ReturnFail=1;
    }
    else
    {
            if (TableCommEvenType[EvenPtr].UsedState!=COMM_USE)
            { 
                Dest->strReturnData.ReturnFail=1;
            }
            else
            {
                switch (TableCommEvenType[EvenPtr].IDType)
                {
                    case COMM_EVEN_BLOCK_FAILURE:   ///�������¼��Ĵ���
                        uiLenth=CommEvenTypeFailue(ID,CommExpDataBuff->Buffer);
                        break;
                    case COMM_EVEN_BLOCK_VOLTAGE_CHECKOUT:////��ѹ�ϸ���
                            uiLenth=CommEvenCheckOutVoltage(ID,CommExpDataBuff->Buffer);
                        break;
                    case COMM_EVEN_BLOCK_MD_OVER:
                            uiLenth=CommEvenMDLoad(ID,CommExpDataBuff->Buffer);
                            break;
                    case COMM_EVEN_BLOCK_METER_HANDLE:
                            uiLenth=CommEvenMeterHandle(ID,CommExpDataBuff->Buffer);
                        break;
                                case COMM_EVEN_BLOCK_CARD:
                                                  uiLenth=CommEvenMeterCard(ID,CommExpDataBuff->Buffer);  
                                           break;
                                case COMM_EVEN_BLOCK_METER_CUTGATE:
                                        uiLenth=CommEvenCutGate(ID,CommExpDataBuff->Buffer); 
                                        break;
                    default:
                        Dest->strReturnData.ReturnFail=1;
                        return;
                }
                if (uiLenth!=SWITCH_TABLE_ERR)
                {
                        if (uiLenth&COMM_READ_RETURN_FRAME_FLAG)
                            {
                                Dest->strReturnData.LastFrame=1;
                                uiLenth&=~COMM_READ_RETURN_FRAME_FLAG;
                            }
                        Dest->strReturnData.Lenth=uiLenth;
                        Dest->strReturnData.ReturnFail=0;
                }
                else
                {
                        Dest->strReturnData.ReturnFail=1;
                }
            }
    }
    */
    
    //added by zlq090922, �����¼��Ǻ͹����¼���ݱ�ʶ���ӻ�ı�,����ʽ�ı�,�Ƚ��ⲿ�����ݶ�������,�������ݱ�ʶ��Ӧ���ݴ�����̲���
    //�ı���ⲿ������,ͨ����ָ���ʶӳ��Ϊһ�������ָ���ʶ,�ٲ��õ���������
    //uchar ID0 = (uchar)ID;
    //uchar ID1 = (uchar)(ID>>8);
    uchar ID2 = (uchar)(ID>>16);
    uchar ID3 = (uchar)(ID>>24);
    ulong ulVirtualID = ID;
    uchar ucFlg = 0;
    if((ID3 == 3) && ((ID2 == 0x32) || (ID2 == 0x33)))      // ��ʷ���������߹������¼
    {
        ulVirtualID &= 0xFFFF0000L;                         //�ض��¼���¼,��DI1DI0����
        ucFlg = 2;
    }
#if(CONFIG_METER_TYPE==CONFIG_METER_TYPE_SD39C)
    else if((ID3 >= 0x10) && (ID3 <= 0x20))
#else
    else if((ID3 >= 0x10) && (ID3 <= 0x1F))
#endif
    {
        ucFlg = 1;
        if(0==GetEventTotalCntAndTime(Dest, ID))
        {
            if(ID == 0x10000101)                           //ֱ�Ӵ���,�������Լ����
            {
                ReadDataDirect(EPL_TOTAL_LOSS_V_LAST_START, 6, CommExpDataBuff->Buffer);
                Dest->strReturnData.Lenth = 6;
                Dest->strReturnData.ReturnFail = 0;
            }
            else if(ID == 0x10000201)
            {
                ReadDataDirect(EPL_TOTAL_LOSS_V_LAST_END, 6, CommExpDataBuff->Buffer);
                Dest->strReturnData.Lenth = 6;
                Dest->strReturnData.ReturnFail = 0;
            }
            else                                                //���������ж����ų��Ǿ������¼���¼,��Ҫ�ο������Լ����
            {
                ulVirtualID &= 0xFFFF0000L;                     //�ض��¼���¼,��DI1DI0����
                ucFlg = 2;
            }
        }
    }
    
    if(ucFlg == 0)                                          //δ�Ķ����ֵĴ���
    {
        GetEventRecordData1(Dest, ID);
    }
    else if(ucFlg == 2)                                     //�Ķ����ִ���
    {
        GetEventRecordData2(Dest, ID, ulVirtualID);
    }
    
}

///�α������ݵĶ���
void CommReadParaData(STR_READ_RETURN_PARA *Dest,ulong ID)
{
    uchar ID0=(uchar)(ID);
        uchar ID1=(uchar)(ID>>8);
        uchar ID2=(uchar)(ID>>16);
        u16 uiHolidayNum;
        u16 uiLenth,i;
        switch (ID2)
        {
            case 0x03:    ////��������
              //uiHolidayNum=GetSetHolidayNum();  /////�ܶ������Ĺ���������Ŀ�����õĹ���������Ŀ���
              uiHolidayNum = 254;                   //edited by zlq091030
              if ((ID0<0x01)||(ID0>uiHolidayNum))  ////����
              {
                  Dest->strReturnData.ReturnFail=1;
              }
              else
              {
                uiLenth=COMM_HOLIDAY_WORD_SIZE;
                ReadDataDirect(EPL_PUBLIC_HOLIDAY_START+(ID0-1)*COMM_HOLIDAY_WORD_SIZE,COMM_HOLIDAY_WORD_SIZE,CommExpDataBuff->Buffer);
                Dest->strReturnData.Lenth=uiLenth;
                                Dest->strReturnData.ReturnFail=0;
              }
              break;
            case 0x04:  ////ѭ��
              switch (ID1)  ////
              {
                case 0x01:
#if(CONFIG_METER_AREA_MODE_SHANDONG!=CONFIG_METER_AREA_MODE)
                  //uiHolidayNum=GetSetCycleLcdNum();
                  uiHolidayNum = 99;//edited by zlq091030
                  if (ID0>uiHolidayNum)
                  {
                        Dest->strReturnData.ReturnFail=1;
                  }
                  else
#endif
                  {
                        uiLenth=COMM_CYCLE_DSP_SIZE;
                        ReadDataDirect(EPL_DISPLAY_AUTOSET_START+(ID0-1)*COMM_CYCLE_DSP_SIZE,COMM_CYCLE_DSP_SIZE,CommExpDataBuff->Buffer);
                                Dest->strReturnData.Lenth=uiLenth;
                                                Dest->strReturnData.ReturnFail=0;
                  }
                  break;
                case 0x02:   ////������ʾ
                 /*uiHolidayNum = 99;//edited by zlq091030
                                        if (ID0>uiHolidayNum)
                  {
                        Dest->strReturnData.ReturnFail=1;
                  }
                  else
                  {
                    uiLenth=COMM_CYCLE_DSP_SIZE;
                    ReadDataDirect(EPL_DISPLAY_KEYSET_START+(ID0-1)*COMM_CYCLE_DSP_SIZE,COMM_CYCLE_DSP_SIZE,CommExpDataBuff->Buffer);
                            Dest->strReturnData.Lenth=uiLenth;
                                            Dest->strReturnData.ReturnFail=0;
                  }*/
                  
         //  ljc  20100624  start
        #if(CONFIG_METER_AREA_MODE_SICHUAN==CONFIG_METER_AREA_MODE)
        uiHolidayNum = 0xC7;
        #else
        uiHolidayNum = 0x63;
        #endif
#if(CONFIG_METER_AREA_MODE_SHANDONG!=CONFIG_METER_AREA_MODE)
        if ((ID0>uiHolidayNum)||(ID0==0))
        {
                Dest->strReturnData.ReturnFail=1;
        }
        else
#endif
        {
            uiLenth=COMM_CYCLE_DSP_SIZE;
#if(CONFIG_METER_AREA_MODE_SHANDONG!=CONFIG_METER_AREA_MODE)
            if(ID0<0x64)
#endif
            {
                ReadDataDirect(EPL_DISPLAY_KEYSET_START+(ID0-1)*COMM_CYCLE_DSP_SIZE,COMM_CYCLE_DSP_SIZE,CommExpDataBuff->Buffer);
            }
            #if(CONFIG_METER_AREA_MODE_SICHUAN==CONFIG_METER_AREA_MODE)
            else
            {
                ReadDataDirect(KEY_TURN_DISPLAY_B_LIST_START_ADDR+(ID0-0x64)*COMM_CYCLE_DSP_SIZE,COMM_CYCLE_DSP_SIZE,CommExpDataBuff->Buffer);
            }
            #endif
            Dest->strReturnData.Lenth=uiLenth;
            Dest->strReturnData.ReturnFail=0;
                  }
         //  ljc  20100624  end
                  break;
                default:     ////����
                    Dest->strReturnData.ReturnFail=1;
                 break;
              }
              break;
            default:
                uiHolidayNum=GetParameterTableNum();
                for(i=0;i<uiHolidayNum;i++)
                {
                    if(ID==TableParaMeter[i].id) break;
                }
                if(i>=uiHolidayNum)
                {
                    Dest->strReturnData.ReturnFail=1;
                }
                else
                {
                    switch (ID2)
                    {
                        case 0x01:
                        case 0x02:
                          #if(CONFIG_METER_AREA_MODE_JIANGSU!=CONFIG_METER_AREA_MODE)
                            uiHolidayNum=GetFeeDayTableMaxNum();
                            if(ID0<=uiHolidayNum)
                          #else
                            if(ID0<=8)
                          #endif
                            {
                                    if(ID0==0X00)     /////ʱ����
                                    {
                                        uiHolidayNum=GetFeeSeasonMaxNum();
                                        uiLenth=uiHolidayNum*COMM_SEASON_SIZE;
                                    }
                                    else    ////ʱ�α�
                                    {
                                        uiHolidayNum=GetFeeTouTableMaxNum();
                                        uiLenth=uiHolidayNum*COMM_SEASON_SIZE;
                                    }
                                    
                                    if (uiLenth==0) 
                                    {
                                        Dest->strReturnData.ReturnFail=1;
                                    }
                                    else
                                    {
                                        ReadDataDirect(TableParaMeter[i].memoryAddress,uiLenth,CommExpDataBuff->Buffer);
                                        Dest->strReturnData.Lenth=uiLenth;
                                                    Dest->strReturnData.ReturnFail=0;
                                                }
                                        }
                                        else
                                        {
                                                Dest->strReturnData.ReturnFail=1;
                                        }
                            break;
                        default:
		// fprintf(stderr, "11111111111111111111111111111111");				
                            if(TableParaMeter[i].ReadAndWrite&COMM_READ) ////�ж���Ȩ��
                            {
                                uiLenth=TableParaMeter[i].dataLens;
                                                                /////////////////////////////////////�����2��,������������ر��ṩ�ı�����ַλ��
                                if((ID==0x04000409)||(ID==0x0400040A))
                                {
                                    memcpy(CommExpDataBuff->Buffer,&PROGFUNCTION_TYPE_PLUS_CONSTANT,3);
                                }
                                else if(ID==0x04000101)
                                {
                                    uchar uctemp = 0;
                                    ReadDataDirect(TableParaMeter[i].memoryAddress,uiLenth,CommExpDataBuff->Buffer);
                                    uctemp = CommExpDataBuff->Buffer[3];
                                    CommExpDataBuff->Buffer[3] = CommExpDataBuff->Buffer[2];
                                    CommExpDataBuff->Buffer[2] = CommExpDataBuff->Buffer[1];
                                    CommExpDataBuff->Buffer[1] = CommExpDataBuff->Buffer[0];
                                    CommExpDataBuff->Buffer[0] = uctemp;
                                }
                                else
                                {
                                    ReadDataDirect(TableParaMeter[i].memoryAddress,uiLenth,CommExpDataBuff->Buffer);
                                    //ReadCoefDataWithCheck(TableParaMeter[i].memoryAddress,uiLenth,CommExpDataBuff->Buffer,0);
                                }
                                //////////
                                Dest->strReturnData.Lenth=uiLenth;
                                Dest->strReturnData.ReturnFail=0;
								if((ID>=0x04000c01)&&(ID<=0x04000c0A))
								{
									CommExpDataBuff->Buffer[0] = *((uchar*)&ID) - 1;
								}
                            }
                            else
                            {
                                Dest->strReturnData.More=1;  ////û�ж�Ȩ��
                            }
                            break;
                    }
                }
                break;
        }
}

////////////////////////////////////////////////////////////////////////////////

////��ö�������ģʽ��,edited by zlq090925 ÿ���������Ͷ�����һ������ģʽ��,������Ӵ��������������
uchar GetCommFreezeWord(uchar ucType)
{
    uchar TmpData;
    ulong ulAddr;
  
    switch(ucType)
    {
        case COMM_FREEZE_TIME:              //��ʱ����
            ulAddr = RAM_CHARACTER_FREEZE_EVERYTIME_MODE;
            break;
            
        case COMM_FREEZE_INSTANTANEOUS:     //˲ʱ����
            ulAddr = RAM_CHARACTER_FREEZE_INSTANT_MODE;
            break;
            
        case COMM_FREEZE_SEANSONTABLE_CHANGE://����ʱ�����л�����
        case COMM_FREEZE_DAYTABLE_CHANGE:   //������ʱ�α��л�����
        case COMM_FREEZE_DIVTIMFEE_CHANE:   //��ʱ�����л�����
        case COMM_FREEZE_STEP_CHANE:        //�����л�����
            ulAddr = RAM_CHARACTER_FREEZE_RESTORE_MODE;
            break;
    
        case COMM_FREEZE_HOURORHALF:        //���㶳��
            ReadDataDirect(RAM_CHARACTER_FREEZE_EVERYHOUR_MODE, 1, &TmpData);
            return (TmpData & 0x03);        //����

        case COMM_FREEZE_DAY:               //�ն���
            ulAddr = RAM_CHARACTER_FREEZE_EVERYDAY_MODE;
            break;
            
        default:
            return 0;
    }
    ReadDataDirect(ulAddr, 1, &TmpData);
    return (TmpData);
}

//////�������ݵĶ���
u16 CommReadFeeze(uchar ucTwoTableaddr,ulong ID,uchar *Dest)
{
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
        uchar TmpBuf[LAST_FRAME_BLOCKSIZE];
    uchar TmpBuf1[LAST_FRAME_BLOCKSIZE];
    u16 i,k;
    u16 TabNum;
    ulong Addr=0;
    ulong EvenAddr;
    u16 Lenth=0,uiLen=0,TmpLen=0,TmpLenth=0,TmpSize,TmpLastLen=0;
        uchar ucTmpUseNum,ucFeeNum,TmpUseNum,TmpFlg=0;
        /////�����ֽ�
    STR_LASTFRAME_IN_PARA  TmpPara;
    TmpPara.ucUsed=COMM_PARAMETER_USED;
    TmpPara.ucCommNo=GetExplainCommNo();
    TmpPara.ulID=ID;
    TmpPara.ucFrameNo=0;
         
    TabNum=GetFreezedataNum();
    ucTmpUseNum=GetCommFreezeWord((uchar)(ID>>16));  ////����ģʽ��
    ucFeeNum=GetSetFeeNumber();
///////�������ݱȽ�����,�����ID1��0XFF��ʱ��,��ֱ���ڸú����������Щ���ݽ����ɹ�Լ�ĸ�ʽ
    if(ID1==0xFF)
    {
                    
        if(ID0==0x00) 
            return SWITCH_TABLE_ERR;
        Addr=GetTwoTableAddrFromBlock(ucTwoTableaddr,ID0-1,0);
        if(Addr==COMM_READ_EC_GETTWOTABLE_ADDRERR) //|| (Addr==GAL_GETTWOTABLE_POINTRERR)) 
            return SWITCH_TABLE_ERR;
        ////��������ʱ�䲢����0XAA
        ReadDataDirect(Addr,5,Dest);    
        memset(Dest+5,0xAA,1);
        Lenth+=6;
        uiLen=Lenth;
        TmpFlg=0;  /////�Ƿ���Ҫ��������ģ�0���ǣ�1����
        Addr+=5;
        TmpLastLen=0; ////����֡BUFFER�г���
        for(i=1;i<TabNum;i++)
        {
           if((uchar)(ID>>16) == 0x04)  //ID2=4,���㶳������⴦��,û�зַ��ʵ���,edited by zlq090930
           {
                TmpUseNum = 1;
                if(i >= 3)                  //edited by zlq091021
                    break;
           }
           else if(i!=(TabNum-1)) 
           {
                TmpUseNum=ucFeeNum+1;
           }        //////////����������
            else 
            {
                TmpUseNum=COMM_READ_FREEZE_VARIABLE_MAXSIZE;
            }   ////����
            
            TmpLenth=0;
            TmpSize=0;   //////1��С��ĳ���
           
            if (TableFreezeType[i].UsedState==COMM_USE)
            {
                 
                 if(ucTmpUseNum&CommFeezeArrWord[i-1])
                 {
                     for(k=0;k<TmpUseNum;k++)
                     {
                       TmpLen=TableFreezeType[i].UseLenth-TableFreezeType[i].FormatLenth;
                       ReadDataDirect(Addr+TmpLen+TmpLenth,TableFreezeType[i].FormatLenth,TmpBuf+TmpSize);  
                       TmpLenth+=TableFreezeType[i].UseLenth;
                       TmpSize+=TableFreezeType[i].FormatLenth;
                     }
                    // Addr+=(TableFreezeType[i].UseLenth*TableFreezeType[i].UseNum);  
                    // memset(TmpBuf+TmpSize,0xAA,1);
                    // TmpSize+=1;
                 }
                 if((uchar)(ID>>16) == 0x04)        //edited by zlq091009
                 {
                    Addr+=(5*1);  
                 }
                 else
                 {
                    Addr+=(TableFreezeType[i].UseLenth*TableFreezeType[i].UseNum);  
                 }
                    memset(TmpBuf+TmpSize,0xAA,1);
                    TmpSize+=1;
            }
            else
            {
                  memset(TmpBuf,0xAA,1);
                  TmpSize=1;
            }
            
            uiLen+=TmpSize;
              
            if(uiLen>LAST_FRAME_BLOCKSIZE)  ///����
            {
                    ///////��һ������֡�Ĵ���
                    if(0==TmpFlg)
                    {
                      TmpFlg=1;
                      Lenth|=COMM_READ_RETURN_FRAME_FLAG;
                      
                    }
                    else
                    {
                        TmpPara.ucFrameNo++;
                        TmpPara.ucFormatLen=uiLen-TmpSize;
                        if (SaveLastFrameInBuffer(TmpPara,TmpBuf1)==COMM_FAIL) 
                        {
                          return SWITCH_TABLE_ERR;
                        }
                    }
                    
                     TmpLastLen=TmpSize;
                     memcpy(TmpBuf1,TmpBuf,TmpSize);
                     uiLen=TmpSize;
              }
              else
              { 
                  if(0==TmpFlg)
                  {
                    memcpy(Dest+Lenth,TmpBuf,TmpSize);
                    Lenth+=TmpSize;
                  }
                  else
                  {
                     memcpy(TmpBuf1+TmpLastLen,TmpBuf,TmpSize);
                     TmpLastLen+=TmpSize;
                  }
              }
        } 
        
       if(TmpLastLen!=0) 
       {
           TmpPara.ucFrameNo++;
           TmpPara.ucFormatLen=TmpLastLen;
            if (SaveLastFrameInBuffer(TmpPara,TmpBuf1)==COMM_FAIL) 
            {
              return SWITCH_TABLE_ERR;
            }
       }
               
                       
    }
    else
    {              
            switch (ID1)
            {
                case 0x00:
                  break;
                case 0x01:
                  if (ucTmpUseNum&BIT0);
                  else return SWITCH_TABLE_ERR;
                  break;
                case 0x02:
                  if (ucTmpUseNum&BIT1);
                  else return SWITCH_TABLE_ERR;
                  break;
                case 0x03:
                  if (ucTmpUseNum&BIT2);
                  else return SWITCH_TABLE_ERR;
                    break;
                case 0x04:
                  if (ucTmpUseNum&BIT3);
                  else return SWITCH_TABLE_ERR;
                    break;
                case 0x05:
                case 0x06: 
                case 0x07:
                case 0x08:
                   if (ucTmpUseNum&BIT4);
                   else return SWITCH_TABLE_ERR;
                    break;
                case 0x09:
                   if (ucTmpUseNum&BIT5);
                   else return SWITCH_TABLE_ERR;
                    break;
                case 0x0A:
                   if (ucTmpUseNum&BIT6);
                   else return SWITCH_TABLE_ERR;
                    break;
                case 0x10:
                  if (ucTmpUseNum&BIT7);
                   else return SWITCH_TABLE_ERR;
                    break;
                default:
                     return SWITCH_TABLE_ERR;
            }
          
            for(i=0;i<TabNum;i++)
            {
                if(ID1==TableFreezeType[i].FeezeType)
                {
                    break;
                }
            }
            if (i>=TabNum) return SWITCH_TABLE_ERR;
            if (TableFreezeType[i].UsedState!=COMM_USE) return SWITCH_TABLE_ERR;
            
            if(((uchar)(ID>>16) == 0x04) && (i != 0))     //��������,�޷ַ���,���⴦��,edited by zlq090930
            {
                Lenth = 5;
                Addr = i*5+0;
            }
            else
            {
                Lenth=TableFreezeType[i].UseLenth*TableFreezeType[i].UseNum;
                //////�ӵ�ǰ�ĵ�ַ���ƻ�ȥ,�������ַ
                for(k=0;k<i;k++)
                {
                    if(TableFreezeType[k].UsedState==COMM_USE)
                    {
                            Addr+=(TableFreezeType[k].UseLenth*TableFreezeType[k].UseNum);
                    }
                }
            }
            if(ID0==0)  return SWITCH_TABLE_ERR;
            EvenAddr=GetTwoTableAddrFromBlock(ucTwoTableaddr,(ID0-1),0);
            if (EvenAddr==GAL_GETTWOTABLE_ADDRERR) return SWITCH_TABLE_ERR;
            Addr+=EvenAddr;
            ReadDataDirect(Addr,Lenth,Dest);
    } 
  return (Lenth);
}

//����Ͱ�㶳��
void CommReadFeezeZeroData(STR_READ_RETURN_PARA *Dest,ulong ID)
{
  uchar ID2=(uchar)(ID>>16);
  uchar ID0=(uchar)(ID);
  uchar ID1=(uchar)(ID>>8);
  u16  i,k,uiTmp=0;
  uchar TmpBuffer[LAST_FRAME_BLOCKSIZE];
  ulong EvenAddr=GAL_GETTWOTABLE_ADDRERR;
  uchar StateFlag=0;
  //u16  uiLenth=8*240;   ///Ĭ��ֵ
  /////�����ֽ�
  STR_LASTFRAME_IN_PARA  TmpPara;
  TmpPara.ucUsed=COMM_PARAMETER_USED;
  TmpPara.ucCommNo=GetExplainCommNo();
  TmpPara.ulID=ID;
  TmpPara.ucFrameNo=0;
  
  
  if(ID2==0x01)  
  {
     if((ID1==0x01)||(ID1==0x02))
     {
       if(ID0==0xFF) /////���
       {
          if(ID1==0x02) {uiTmp=241;}
          else {uiTmp=1;}
          //////��240*8�ֽڷֳ�8*24���ֽ���һ������BUFFER������10��BUFFER
          ////�ȷ���24*8������ֻ��Ҫ9������BUFFER
          for(i=0;i<10;i++)
          {
             for(k=0;k<24;k++)
             {
                EvenAddr=GetTwoTableAddrFromBlock(TYPE_FREEZE_HOURTIME_RECORD,(uiTmp-1+i*24+k),0);
            if (EvenAddr==GAL_GETTWOTABLE_ADDRERR) {StateFlag=1;break;}
                ReadDataDirect(EvenAddr,8,&TmpBuffer[k*8]);
             }
             if(StateFlag==1) {StateFlag=1;break;}
             if(i==0) {memcpy(CommExpDataBuff->Buffer,TmpBuffer,192);}
             else
             {
                TmpPara.ucFrameNo=i;
                TmpPara.ucFormatLen=192;
        if (SaveLastFrameInBuffer(TmpPara,TmpBuffer)==COMM_FAIL) {StateFlag=1;break;}
             }
          }
          Dest->strReturnData.LastFrame=1; 
          Dest->strReturnData.Lenth=192;
           Dest->strReturnData.ReturnFail=0;
          return;
          
       }
       else
       {
          if((ID0>0xF0)||(ID0==0x00)) {StateFlag=1;}  ///����
          else
          {
            uiTmp=0;
            if(ID1==0x02) {uiTmp=ID0+240;}
            else {uiTmp=ID0;}
          
            EvenAddr=GetTwoTableAddrFromBlock(TYPE_FREEZE_HOURTIME_RECORD,(uiTmp-1),0);
            if (EvenAddr==GAL_GETTWOTABLE_ADDRERR) {StateFlag=1;}
            else
            {
                ReadDataDirect(EvenAddr,8,CommExpDataBuff->Buffer);
            }
          }
       }
     }
     else {StateFlag=1;}
  }
  else {StateFlag=1;}
  
  //////״̬
  if(StateFlag==0) //��ȷ
  {

      Dest->strReturnData.LastFrame=0;
      Dest->strReturnData.Lenth=8;
       Dest->strReturnData.ReturnFail=0;
  }
  else     //����
  {
      Dest->strReturnData.ReturnFail=1;
  }
}

////�������ݵĶ������ƺ���
const uchar gCuc_FreezeType[] = 
{
    TYPE_FREEZE_EVERYTIME_RECORD,       //0x00,��ʱ����
    TYPE_FREEZE_INSTANT_RECORD,         //0x01,˲ʱ����
    TYPE_FREEZE_SEASONCHANGE_RECORD,    //0x02,����ʱ���л�����
    TYPE_FREEZE_DAYTABLECHANGE_RECORD,  //0x03,������ʱ�α��л�����
    TYPE_FREEZE_HOURTIME_RECORD,        //0x04,���㶳���л�
    TYPE_FREEZE_STEPPRICE_TABLECHANGE_RECORD,   //0x05,���׷����л�����
    TYPE_FREEZE_EVERYZERO_RECORD,       //0x06,����㶳�� 
    //0x07,���׽����л�����
};
void CommReadFeezeData(STR_READ_RETURN_PARA *Dest,ulong ID)
{
    uchar ID2=(uchar)(ID>>16);
    uchar ID0=(uchar)(ID);
       // uchar ID1=(uchar)(ID>>8);
        
    uchar ucTableType;
    uchar StateFlag=0;
    ulong ulLenth=SWITCH_TABLE_ERR;
    Dest->strReturnData.ReturnFail=0;
    
    switch (ID2)
    {
        case COMM_FREEZE_TIME:     ///��ʱ����
             ucTableType=TYPE_FREEZE_EVERYTIME_RECORD;
             if (ID0>COMM_FREEZE_RECORD_TIM) StateFlag=1;
            break;
        case COMM_FREEZE_INSTANTANEOUS:  ///˲ʱ����
             ucTableType=TYPE_FREEZE_INSTANT_RECORD;
             if (ID0>COMM_FREEZE_IMMEDIATE_TIM) StateFlag=1;
            break;
        case COMM_FREEZE_SEANSONTABLE_CHANGE:////����ʱ�����л�����
                ucTableType=TYPE_FREEZE_SEASONCHANGE_RECORD;
                 if (ID0>COMM_FREEZE_FEETABLE_TIM) StateFlag=1;
            break;
        case COMM_FREEZE_DAYTABLE_CHANGE: /////������ʱ�α��л�����
                ucTableType=TYPE_FREEZE_DAYTABLECHANGE_RECORD;
                 if (ID0>COMM_FREEZE_FEETABLE_TIM) StateFlag=1;
            break;
        case COMM_FREEZE_HOURORHALF:        //���㶳��
            ucTableType=TYPE_FREEZE_HOURTIME_RECORD;
            if(ID0>COMM_FREEZE_HOUR_TIM) StateFlag=1;
            //else
            //{
            //    CommReadFeezeZeroData(Dest,ID);
            //    return;
            //}
            break;
#if(CONFIG_METER_STEP_PERIODPRICE_MODE==CONFIG_METER_STEP_PERIODPRICE_MODE_ENABLE)
        case COMM_FREEZE_DIVTIMFEE_CHANE:///��ʱ�����л�����
            ucTableType=TYPE_FREEZE_PERIODPRICE_TABLECHANGE_RECORD;
            if(ID0>COMM_FREEZE_DIVFEECHANGE_TIM) StateFlag=1;
          break;
#endif
        case COMM_FREEZE_DAY:   ///�ն���
            ucTableType=TYPE_FREEZE_EVERYZERO_RECORD;
            if(ID0>COMM_FREEZE_DAY_TIM) StateFlag=1;
            break;
#if(CONFIG_METER_STEP_MODE==CONFIG_METER_STEP_MODE_ENABLE)
        case COMM_FREEZE_STEP_CHANE:    //�����л�����
            ucTableType=TYPE_FREEZE_STEPPRICE_TABLECHANGE_RECORD;
            if(ID0>COMM_FREEZE_DIVFEECHANGE_TIM) StateFlag=1;
            break;
#endif
        default:
                StateFlag=1;
            break;
    }
    
    if(StateFlag==0)
    {     
          ulLenth=CommReadFeeze(ucTableType,ID,CommExpDataBuff->Buffer);
          if(ulLenth==SWITCH_TABLE_ERR)
          {
              Dest->strReturnData.ReturnFail=1;
          }
          else
          {
              Dest->strReturnData.LastFrame=0;
              if(ulLenth&COMM_READ_RETURN_FRAME_FLAG)
              {
                ulLenth&=~COMM_READ_RETURN_FRAME_FLAG;
                Dest->strReturnData.LastFrame=1;
              }
              Dest->strReturnData.ReturnFail=0;
              Dest->strReturnData.Lenth=ulLenth;
          }
    }
    else 
    {
        Dest->strReturnData.ReturnFail=1;
    }
}

//////ͨ��ID ����ö�������
//���ص�ֵ�����λΪ0:�ɹ���1:ʧ�ܡ�
/// �ڶ���λΪ1��Ϊ�к���֡��0: �޺���
///������λ����4��λ�ա�������ֽ�λ��ʾ�������ݳ���
//���Ϊ��ȫ�ֱ�����
u16  GetDataByID(STR_READDATA_INPUT* Src)
{
    uchar ID3=(uchar)((Src->ulID)>>24);
    
    u16 uiTabPtr;
    WReturnFUNCTION  ReadTypeFunction;
    STR_READ_RETURN_PARA  ReadReturnPara;

    ReadReturnPara.uiReturnData=COMM_RETURN_STATE_FAIL;
    
    //added by zlq090923
#if(CONFIG_METER_TYPE==CONFIG_METER_TYPE_SD39C)
    if((ID3 >= 0x10) && (ID3<= 0x20))
#else
    if((ID3 >= 0x10) && (ID3<= 0x1F))
#endif
    {                       //ID3��0x10��0x1fΪ�¼���¼
        CommEvenRecordData((STR_READ_RETURN_PARA*)&ReadReturnPara, Src->ulID);
                            //��ȡ��Ӧ���¼���¼
        return (ReadReturnPara.uiReturnData);
    }
    //added by zlq090923
    
    uiTabPtr=GetCommReadTypePtr(ID3);
    
    if (uiTabPtr==SWITCH_TABLE_ERR)     //������
    {
        return COMM_RETURN_STATE_FAIL;   //�������Ϊʧ�ܵ�ֵ
    }
    else
    {
        ReadTypeFunction=TableCommReadBlock[uiTabPtr].TypeFunction;
        ReadTypeFunction((STR_READ_RETURN_PARA*)&ReadReturnPara,Src->ulID);////������Ӧ�Ĵ�����
    }
    
    return (ReadReturnPara.uiReturnData);
}



/////ͨ�ŵ���ת��Ϊ��Լ��ʽ������
///�������ݳ���
uchar  ECDataToFormat(ulong ID,uchar Lenth,uchar *Dest)
{
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
    uchar ID2=(uchar)(ID>>16);
    uchar ucFeenum=1;
    uchar Tmpbuffer[4];
    u16 i;

    if(ID2==0x90) return Lenth;

    if(ID2 == 0x0B)   ///edited by yxx091130
    {
        memcpy(Tmpbuffer,Dest+1,4);
        memcpy(Dest,Tmpbuffer,4);
        Lenth=4;    
        return   Lenth;
    }
    ///////////////////////////////////
    if (ID1==0xFF)   ////�ܣ���������
    {
        ucFeenum=GetSetFeeNumber();
        ucFeenum+=1; 
    }
    else
    {
        if(ID0==0xFF)   ////��ʷ
        {
            ucFeenum=COMM_READ_EC_HISTORY+1;
        }
        else
        {
            ucFeenum=1;
        }
    }

    for(i=0;i<ucFeenum;i++)
    {
        memcpy(Tmpbuffer,Dest+i*COMM_READ_EC_LENTH+1,4);
        memcpy(Dest+i*4,Tmpbuffer,4);
    }
    return (4*ucFeenum);  
}

/////ͨ��������ת��Ϊ��Լ��ʽ������
///�������ݳ���
uchar  MDDataToFormat(ulong ID,uchar Lenth,uchar *Dest)
{
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
    uchar ucFeenum=1;
    uchar Tmpbuffer[10];
    u16 i;
    
    if (ID1==0xFF)   ////�ܣ���������
    {
        ucFeenum=GetSetFeeNumber();
        ucFeenum+=1; 
    }
    else
    {
        if(ID0==0xFF)   ////��ʷ
        {
            ucFeenum=COMM_READ_MD_HISTORY+1;
        }
        else
        {
            ucFeenum=1;
        }
    }

    for(i=0;i<ucFeenum;i++)
    {
        memcpy(Tmpbuffer,Dest+i*(COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH)+1,3);
        memcpy(Tmpbuffer+3,Dest+i*(COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH)+4,5);
        memcpy(Dest+i*8,Tmpbuffer,8);
    }
    return (8*ucFeenum);

}
#if 0
///////����ת��Ϊ��Լ��ʽ��(ע��,�洢�ĸ�ʽ����Ҫ�ȹ�Լ���ֽ�����,���Ҷ���Ҫȥ���洢�ĵ�λ)
uchar VariableParaToFormat(ulong ID,uchar Lenth,uchar *Dest)
{
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
    uchar ID2=(uchar)(ID>>16);
    uchar Tmpbuffer[10];
    u16  DataTypePtr;
    u16  TmpLenth=0;
    uchar ucFeenum=1;
    uchar i;
    ulong ulTmpVA;
    
    if (ID2==0x80)
    {
        DataTypePtr=GetEscepecialVariablePtr(ID0);
        TmpLenth=TableVariableEscipe[DataTypePtr].UsedLenth-TableVariableEscipe[DataTypePtr].FormatLenth;
        memcpy(Tmpbuffer,Dest+TmpLenth,TableVariableEscipe[DataTypePtr].FormatLenth);
        memcpy(Dest,Tmpbuffer,TableVariableEscipe[DataTypePtr].FormatLenth);
        TmpLenth=TableVariableEscipe[DataTypePtr].FormatLenth;
    }
    else
    {
        DataTypePtr=GetVariableTypeNum(ID2);    
        if (ID1==0xFF)
        {
            ucFeenum=TableVariable[DataTypePtr].UsedID1Num;
        }
        else
        {
            if (ID0==0xFF)
            {
                    ucFeenum=TableVariable[DataTypePtr].RecordTim;
            }
        }
        ///////////////////////���ڴ洢�ĸ�ʽ���Լ���صĶԲ��Σ���ʹ�����ת��
        switch (ID2)
        {
          
            case 0x01:
                for(i=0;i<ucFeenum;i++)
                {
                    memcpy(&ulTmpVA,Dest+i*TableVariable[DataTypePtr].UseFormat,4);
                    ulTmpVA=ulTmpVA>>12;
                    ulTmpVA&=0x0000FFFF;
                    memcpy(Tmpbuffer,&ulTmpVA,TableVariable[DataTypePtr].FormatLenth);
                    memcpy(Dest+i*TableVariable[DataTypePtr].FormatLenth,Tmpbuffer,TableVariable[DataTypePtr].FormatLenth);
                    TmpLenth=TableVariable[DataTypePtr].FormatLenth;
                }
                break;
          
            case 0x02:
                for(i=0;i<ucFeenum;i++)
                {
                    memcpy(&ulTmpVA,Dest+i*TableVariable[DataTypePtr].UseFormat,4);
                    ulTmpVA=ulTmpVA>>4;
                    ulTmpVA&=0x00FFFFFF;
                    memcpy(Tmpbuffer,&ulTmpVA,TableVariable[DataTypePtr].FormatLenth);
                    memcpy(Dest+i*TableVariable[DataTypePtr].FormatLenth,Tmpbuffer,TableVariable[DataTypePtr].FormatLenth);
                    TmpLenth=TableVariable[DataTypePtr].FormatLenth;
                }
                break;

            default:
                for(i=0;i<ucFeenum;i++)
                {
                    TmpLenth=TableVariable[DataTypePtr].UseFormat-TableVariable[DataTypePtr].FormatLenth;
                    memcpy(Tmpbuffer,Dest+TmpLenth+i*TableVariable[DataTypePtr].UseFormat,TableVariable[DataTypePtr].FormatLenth);
                    memcpy(Dest+i*TableVariable[DataTypePtr].FormatLenth,Tmpbuffer,TableVariable[DataTypePtr].FormatLenth);
                    TmpLenth=TableVariable[DataTypePtr].FormatLenth;
                }
                break;
        }
    }
    return (ucFeenum*TmpLenth);
}
#endif
/////�¼�����ת���ɹ�Լ��ʽ����
uchar EvenDataToFormat(ulong ID,uchar Lenth,uchar *Dest)
{
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
    uchar ID2=(uchar)(ID>>16);
    uchar TmpBuffer[COMM_BUFFERSIZE],BufferLenth=Lenth,ucLenth,TmpLenth;
    u16 i,k,TabNum;
    u16 TableLenth,uiRecordLenth,uiFormatLenth;
    u16 EvenPtr;
    //////////////////////////
    memset(TmpBuffer,0x00,COMM_BUFFERSIZE);
    /////////////////
    EvenPtr=GetEvenBlockPtr(ID2);
    TableLenth=GetEvenDataFormatNum();
    /////�ۼƴ������ۼ�ʱ������ݸ�ʽ����
    if(ID0==0x00) return Lenth;

    switch (TableCommEvenType[EvenPtr].IDType)
    {
        case COMM_EVEN_BLOCK_FAILURE:   ///�������¼��Ĵ���
        case COMM_EVEN_BLOCK_VOLTAGE_CHECKOUT: ///��ѹ�ϸ���
        case COMM_EVEN_BLOCK_MD_OVER: /////��������
            for(i=0;i<TableLenth;i++)
            {
                    if (TableEvenDataToFormat[i].IDType==ID2)
                    {
                        break;
                    }
            }
            
            TableLenth=TableEvenDataToFormat[i].FormatLenth;
            BufferLenth=0;
            TmpLenth=0;
            ucLenth=0;
            for(k=0;k<TableLenth;k++)
            {
                uiRecordLenth=(*(TableEvenDataToFormat[i].RecordTableLenth+k));
                uiFormatLenth=(*(TableEvenDataToFormat[i].FormatTableLenth+k));
                ucLenth=uiRecordLenth-uiFormatLenth;
                memcpy(TmpBuffer,Dest+TmpLenth,uiRecordLenth);
                                memcpy(Dest+BufferLenth,TmpBuffer+ucLenth,uiFormatLenth);
                                TmpLenth+=uiRecordLenth;
                BufferLenth+=uiFormatLenth;
            }
            break;
        case COMM_EVEN_BLOCK_METER_HANDLE:  /////������
            TabNum=GetEvenMeterHandileNum();
            for(i=0;i<TabNum;i++)
            {
                    if (TableEvenMeterHandle[i].IDType==ID1)
                    {
                        break;
                    }
            }
            TableLenth=TableEvenMeterHandle[i].UseTableSize;
            BufferLenth=0;
            TmpLenth=0;
            ucLenth=0;
            for(k=0;k<TableLenth;k++)
            {
                uiRecordLenth=(*(TableEvenMeterHandle[i].RecordTableLenth+k));
                uiFormatLenth=(*(TableEvenMeterHandle[i].FormatTable+k));
                ucLenth=uiRecordLenth-uiFormatLenth;
                memcpy(TmpBuffer,Dest+TmpLenth,uiRecordLenth);
                                memcpy(Dest+BufferLenth,TmpBuffer+ucLenth,uiFormatLenth);   
                TmpLenth+=uiRecordLenth;
                                BufferLenth+=uiFormatLenth;
            }
            break;
        default:
            return Lenth;
    }
    return (BufferLenth);
    
}

/////��������ת���ɹ�ԼҪ���ʽ
uchar FreezeDataToFormat(ulong ID,uchar Lenth,uchar *Dest)
{
    uchar ID1=(uchar)(ID>>8);
    uchar ucFeeNum,ucLenth;
    uchar ucTableNum,i,k;
    u16 uiRecordLenth,uiFormatLenth=0;
    uchar TmpBuffer[20];
    ucFeeNum=GetSetFeeNumber();
    ucTableNum=GetFreezedataNum();
    
    if (ID1==0xFF) return Lenth;
    else
    {
        if(ID1==0x00)  
            return Lenth;
        else
        {
            if(ID1==0x10)
            {
                ucFeeNum=7;
            }
                            
            for(i=0;i<ucTableNum;i++)
            {
                if(TableFreezeType[i].FeezeType==ID1) break;
            }
                            ucFeeNum++;
            if((uchar)(ID>>16) == 0x04) //added by zlq091010
                ucFeeNum = 1;
            
            for(k=0;k<ucFeeNum;k++)
            {
                uiRecordLenth=TableFreezeType[i].UseLenth;
                uiFormatLenth=TableFreezeType[i].FormatLenth;
                ucLenth=uiRecordLenth-uiFormatLenth;
                memcpy(TmpBuffer,Dest+k*uiRecordLenth,uiRecordLenth);
                memcpy(Dest+k*uiFormatLenth,TmpBuffer+ucLenth,uiFormatLenth);
            }
            return (ucFeeNum*uiFormatLenth);
        }
    }
}

uchar EventDataFormat2(ulong ulID, uchar ucLen, uchar *pucBuf)
{
    uchar i;
    uchar ucID0 = (uchar)(ulID>> 0);
    uchar ucID1 = (uchar)(ulID>> 8);
    //uchar ucID2 = (uchar)(ulID>>16);
    //uchar ucID3 = (uchar)(ulID>>24);
    ulong ulVirtualID = ulID;
    S_IDCONV1* psIDConv = (S_IDCONV1*)gCs_IDConv1 + (gCuc_IDConv1TabNum - 1);//�����¼������һ����Աָ��
    S_EVFMT* psEF;
    S_CNTTIME* psCntTm = (S_CNTTIME*)gCS_CntAndTimeTab;
    
    if((ucID1 == 0xFF) || (ucID0 == 0xFF))
    {
        return ucLen;
    }
    
    for(i=0; i<gCuc_CntAndTimeTabNum; i++)
    {
        if(psCntTm->ulID == ulID)
        {
            return ucLen;
        }
        psCntTm++;
    }
    
    if(ulID == 0x10000101 || ulID == 0x10000201)        //ֱ�Ӵ���,�������Լ����
    {
        return ucLen;
    }
    
    //���������ж����ų��Ǿ������¼���¼,��Ҫ�ο������Լ����
    ulVirtualID &= 0xFFFF0000L;                     //�ض��¼���¼,��DI1DI0����
    for(i=0; i<gCuc_IDConv1TabNum; i++)
    {
        if((ulID >= psIDConv->ulVID) && (ulVirtualID == psIDConv->ulVID))   //���ҵ���Ӧ�ĳ�Ա��Ϣ
        {
            psEF = (S_EVFMT*)psIDConv->pvFmt;
            psEF += ucID1 - 1;
            if(psEF->ucType == 1)
            {
                memcpy((void*)pucBuf, (void*)(pucBuf+1), 4);
                return 4;
            }
            break;
        }
        psIDConv--;
    }
    
    return ucLen;
}

//////
////���ڴ洢�ĸ�ʽ�п������Լ�Ĳ���Ӧ,�ʶ����ݽ�����������(����,����,),���ڴ����������ݣ���Ҫ����ͷID�ģ�����Ҫ�ƶ��ֽڰ�ID��������֡��
//����ID,���ݳ���,���ݵĵ�ַ
uchar  SettleDataToFormat(ulong ID,uchar Lenth,  uchar *Dest)
{
    uchar ID3=(uchar)(ID>>24);
        uchar ucLenth=Lenth;
        uchar ucCommTmpbuffer[COMM_BUFFERSIZE+4];
    
    switch (ID3)
    {
        case COMM_READ_TYPE_EC:
            ucLenth=ECDataToFormat(ID,Lenth,Dest);
            break;
        case COMM_READ_TYPE_MD:
            ucLenth=MDDataToFormat(ID,Lenth,Dest);
            break;
        case COMM_READ_TYPE_VARIANLE:
            ucLenth=VariableParaToFormat(ID,Lenth,Dest);
            break;
        case COMM_READ_TYPE_EVEN:
            ucLenth=EvenDataToFormat(ID,Lenth,Dest);
            break;
        case COMM_READ_TYPE_FREEZE:
            ucLenth=FreezeDataToFormat(ID,Lenth,Dest);
            break;
        case COMM_READ_TYPE_LOSS_VOLTAGE:
        case COMM_READ_TYPE_DOWN_VOLTAGE:
        case COMM_READ_TYPE_OVER_VOLTAGE:
        case COMM_READ_TYPE_CUT_VOLTAGE:
        case COMM_READ_TYPE_ORDER_VOLTAGE:
        case COMM_READ_TYPE_ORDER_CURRENT:
        case COMM_READ_TYPE_UNBALANCE_VOLTAGE:
        case COMM_READ_TYPE_UNBALANCE_CURRENT:
        case COMM_READ_TYPE_LOSS_CURRENT :
        case COMM_READ_TYPE_OVER_CURRENT:
        case COMM_READ_TYPE_CUT_CURRENT :
        case COMM_READ_TYPE_REVERSEPOWER:
        case COMM_READ_TYPE_POWEROVER :
        case COMM_READ_TYPE_RELAY_OPEN :
        case COMM_READ_TYPE_RELAY_CLOSE :
        case COMM_READ_TYPE_OVERTOTALCOS :
            ucLenth=EventDataFormat2(ID,Lenth,Dest);
            break;
        default:
            ucLenth=Lenth;
            break;
    }
    memcpy(ucCommTmpbuffer,&ID,4);
    memcpy(ucCommTmpbuffer+4,Dest,ucLenth);
    ucLenth+=4;
    memcpy(Dest,ucCommTmpbuffer,ucLenth);
        return (ucLenth);
}


////���ID�Ƿ�ʹ��
uchar CheckTheIDUsed(ulong ID)
{
  /*
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
    uchar ID2=(uchar)(ID>>16);
    uchar ID3=(uchar)(ID>>24);
    
    switch (ID3)
    {
        case COMM_READ_TYPE_EC:
            break;
        case COMM_READ_TYPE_MD:
            break;
        case COMM_READ_TYPE_VARIANLE:
            break;
    }
    */
  return (COMM_TURE);
}





/////����ͨ����
void CommControlReadData(void)
{
    uchar ucLenth;
    u16   ucReturnFramePara;
    STR_READDATA_INPUT  strReadDataIn;
    memset(&strReadDataIn,0x00,sizeof(STR_READDATA_INPUT));
    ////���ͨ��ID(ucCommFormatTypeΪȫ�ֱ���)
    strReadDataIn.ulID=GetCommReadData645ID(ucCommFormatType);  //��Э�黺�����ж������ݱ�ʶ
    ucLenth=GetCommDataLen();       //��ȡ��������ĳ���
    switch (ucLenth)
    {
        case COMM_READ_LENTH_NORMAL:      //һ��Ķ�
            break;
        case COMM_READ_LENTH_LOADTIM:  ///���ɼ�¼����ʼʱ��
            GetCommReadLoadDataTim(strReadDataIn.BCDLoadTim);
        case  COMM_READ_LENTH_LOADNUM: ///���ɼ�¼����
            strReadDataIn.ucLoadBlockNum=GetCommReadLoadDataNum();
            break;
        default:
            CommExpDataBuff->Buffer[0]=BIT0; //������������0x01�����س����ʶ
            SetReturnDataFrame(0x01,(COMMTYPE_READ|BIT6)|BIT7);//���������򳤶�Ϊ1��������Ȼ����з������ݵĴ��
            return;
            //break;
    }
   /////���ͨ�ſ�
    strReadDataIn.CommNum=GetExplainCommNo();           //���ͨ�Ŷ˿ںš�
    InitialLastFrameBuffer(strReadDataIn.CommNum);  ///�����֡BUFFER����Ӧ�˿��е�����
    ///////У������Ƿ���ڸ���ID
    
    //////��������ID��ö���������
    ucReturnFramePara=GetDataByID(&strReadDataIn);
    
    ucLenth=(uchar)(ucReturnFramePara&0x00FF); /////������ݳ���
    if ((ucReturnFramePara&COMM_RETURN_STATE_FAIL)!=0)    ////����Ӧ��
    {
        if(ucReturnFramePara&COMM_RETURN_FAIL_NO_ACCREDIT)
        {
            CommExpDataBuff->Buffer[0]=BIT2;
        }
        else
        {
            CommExpDataBuff->Buffer[0]=BIT1;
        }
        SetReturnDataFrame(0x01,(COMMTYPE_READ|BIT6)|BIT7);
    }
    else
    {
        ////���ݰ��չ�Լ��ʽ����
        ucLenth=SettleDataToFormat(strReadDataIn.ulID,ucLenth,CommExpDataBuff->Buffer);
        if((ucReturnFramePara&COMM_RETURN_STATE_WITHLAST)!=0)   ///�к���֡
        {
             SetReturnDataFrame(ucLenth,(COMMTYPE_READ|BIT5)|BIT7);
        }
        else   ////�޺���֡
        {
             SetReturnDataFrame(ucLenth,COMMTYPE_READ|BIT7);
        }
    }
}

//======================================================================
//������s16 GetDataByDLT07ID
//���ܣ�����DLT645 ID��ȡ����
//������
//        uchar *pData:       ����buf��������Ŷ��ص�����
//        u16 *ucLen:        �������ݳ���
//        ulong ID:           DLT645 ID( (((ID3*256+ID2)*256)+ID1)*256+ID0 )
//        u16 ulBufLen:      �����Ǹ���buf�ĳ���(�ú�����ʱ���жϴ�ֵ��������Ҫ����ʱ�����㹻��buf�ռ�)
//Input:
//Output:
//���أ�  -1:��ʧ�ܻ��������(ID��֧�ֻ򲻴��ڡ�����buf���Ȳ���)  
//        ����:���ص����ݳ���
//��Χ��ר���ڶ�
//ע�ͣ��ޡ�
//=======================================================================

s16 GetDataByDLT07ID(uchar *pData, u16 *ucLen, ulong ID, u16 ulBufLen)
{
    uchar ucLenth;
    s16 ret=-1;
    u16   ucReturnFramePara;
    STR_READDATA_INPUT  strReadDataIn;
    STR_RETURN_EXPLAINBUFFER *pBuffSave, *pTemp;
        
    memset(&strReadDataIn,0x00,sizeof(STR_READDATA_INPUT));
    ////���ͨ��ID(ucCommFormatTypeΪȫ�ֱ���)
    strReadDataIn.ulID=ID;
    //��ʱ���⴮��1��������֡��
    strReadDataIn.CommNum=SOURCE_VIRTUAL;
    //��ʱ��������֡�Ķ�
    //InitialLastFrameBuffer(strReadDataIn.CommNum);  ///�����֡BUFFER����Ӧ�˿��е�����
    
    //�����ڴ沢��ʼ�����㣬˳����������

    
    pBuffSave = malloc(sizeof(STR_RETURN_EXPLAINBUFFER)+10);
    if(pBuffSave == NULL)
    {
        ErrPrint("GetDataByDLT07ID malloc fail\n");
        return -1;
    }
    else
    {
        memset((uchar*)&pBuffSave[0], 0, sizeof(STR_RETURN_EXPLAINBUFFER));
        pTemp = CommExpDataBuff;
        CommExpDataBuff = (STR_RETURN_EXPLAINBUFFER *)pBuffSave;
        pBuffSave = pTemp;
    }

    ///////У������Ƿ���ڸ���ID
    isSpcecial_uart = SOURCE_VIRTUAL;
    //////��������ID��ö���������
    ucReturnFramePara=GetDataByID(&strReadDataIn);
    isSpcecial_uart = 0xff;
    
    if ((ucReturnFramePara&COMM_RETURN_STATE_FAIL)!=0)    ////����Ӧ��
    {
        ret = -1;
    }
    else
    {
        ////���ݰ��չ�Լ��ʽ����
        ucLenth=(uchar)(ucReturnFramePara&0x0FFF); /////������ݳ���
        ucLenth=SettleDataToFormat(strReadDataIn.ulID,ucLenth,CommExpDataBuff->Buffer);
        {
            ucLenth = ucLenth & 0xfff;
            if(ucLenth > 4)
            {
                ucLenth = ucLenth - 4; //��ȥID CHAR
                if(ucLenth < ulBufLen)
                {
                    memcpy(pData, &(CommExpDataBuff->Buffer[4]), ucLenth);
                    *ucLen = ucLenth;
                    ret = ucLenth;
                }
            }
            else
            {
                ret = -1;
            }
        }
        if((ucReturnFramePara&COMM_RETURN_STATE_WITHLAST)!=0)   ///�к���֡
        {
            //��ʱ����֧��,�����е�һ֡
            //MTRACE("warning! it don't support continue frame !!!\n");
            CommClearLtVirtual485();
        }

    }
    free(CommExpDataBuff);
    CommExpDataBuff = (STR_RETURN_EXPLAINBUFFER *)pBuffSave;
    return ret;
        
}

#if(CONFIG_METER_SW_DEBUG_MODE == GAL_YES)
/*********************************************************************
������CommDebugSpecial
���ܣ�for special debug
������
Input:
Output:
��Χ��
ע�ͣ��ޡ�
********************************************************************/
void CommDebugSpecial(ulong ulID, uchar ucData)
{
    if(ucData == 0xFF)
    {
        if(ulID == 0xffffffff)
        {
#if(POWER_SW_DEBUG_ENABLE == GAL_YES)
            extern u16 DebugPowerOn;
            if(DebugPowerOn == GAL_YES)
                DebugPowerOn = GAL_NO;
            else
                DebugPowerOn = GAL_YES;
#endif        
            return;
        }

    }
    else if(ucData == 0x01)
    {
        DISPLATRACE("uiClacMeterVoltageCoef = 0x%x\n", uiClacMeterVoltageCoef);
        DISPLATRACE("uiCoefCurrentGAIN[0] = 0x%x\n", uiCoefCurrentGAIN[0]);
        DISPLATRACE("uiCoefCurrentGAIN[1] = 0x%x\n", uiCoefCurrentGAIN[1]);
        DISPLATRACE("uiCoefCurrentGAIN[2] = 0x%x\n", uiCoefCurrentGAIN[2]);
        DISPLATRACE("uiClacMeterKwCoef = 0x%x\n", uiClacMeterKwCoef);
        DISPLATRACE("ucClacMeterKwCoefMul = 0x%x\n", ucClacMeterKwCoefMul);
        DISPLATRACE("ucClacMeterKwCoefDiv = 0x%x\n", ucClacMeterKwCoefDiv);
        DISPLATRACE("ulTypeUn = %d\n", ulTypeUn);
        DISPLATRACE("ulTypeIb = %d\n", ulTypeIb);
        DISPLATRACE("ulTypeImax = %d\n", ulTypeImax);
        DISPLATRACE("KwhPluseNum = %d\n", KwhPluseNum);
        DISPLATRACE("The sys runed %d:%d\n", ulRunSecTime/60, ulRunSecTime%60);
#if(FILE_BUFF_ENABLE == GAL_YES)
        DISPLATRACE("FileBuf records=%d, size=%d\n", FileBufRecordNum, FileBufSize);
#endif
        DISPLATRACE("Cur set season=%d, daytable=%d\n", STATUS_SEASONTABLEPOINT, STATUS_DAYTABLEPOINT);
        DISPLATRACE("Cur season=%d, daytable=%d, price=%d\n", STATUS_SEASONNUM, STATUS_DAYTABLE, STATUS_PRICE);
    }
       
}
#endif


/*********************************************************************
������s16 CommReadDLT07Data
���ܣ�����DLT645 ID��ȡ����,����ӡ
������
Input:
Output:
��Χ����Ҫ��������GetDataByDLT07ID
ע�ͣ��ޡ�
********************************************************************/
void CommReadDLT07Data(void)
{
    u16 DataLen, idx;
    uchar *pData;
    UN_U32_PARAM ulId;

    memcpy(&(ulId.ucbData[0]), &COMM_BCAST_DATA_START, 4);
#if(CONFIG_METER_SW_DEBUG_MODE == GAL_YES)
    {
        if(ulId.ulData == 0xFFFFFFFF)
        {
            CommDebugSpecial(ulId.ulData, *((&COMM_BCAST_DATA_START)+4));
            return;
        }
    }   
#endif
    pData = malloc(512);
    if(pData == NULL)
    {
        ErrPrint("CommReadDLT07Data malloc fail\n");
        return;
    }
    if(GetDataByDLT07ID(pData, &DataLen, ulId.ulData, 512) != -1)
    {
        DISPLATRACE("CommReadDLT07Data ID=0x%08X, Len = %d Data:\n", ulId.ulData, DataLen);
        for(idx=0; idx<DataLen; idx=idx+8)
        {
            if(idx>160)
                break;
            if( (idx+8) < DataLen )
            {
                DISPLATRACE("%02X %02X %02X %02X %02X %02X %02X %02X\n",      \
                    pData[idx+0], pData[idx+1], pData[idx+2], pData[idx+3], \
                    pData[idx+4], pData[idx+5], pData[idx+6], pData[idx+7]);
            }
            else
            {
                for(; idx<DataLen; idx++)
                {
                    DISPLATRACE("%02X ", pData[idx]);
                }
                DISPLATRACE("\n");
            }
        }
    }
    else
    {
        ErrPrint("CommReadDLT07Data get data fail\n");
    }

    free(pData);
}

