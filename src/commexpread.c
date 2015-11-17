/*********************************************************************************
    版本号     :version 0.1
    模块名       : 远程控制模块
    文件名       : CommExpRead.c
    相关文件     : 
    文件实现功能 : 通信读数据模块
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
/////冻结数据转化成规约要求格式
uchar FreezeDataToFormat(ulong ID,uchar Lenth,uchar *Dest);
////由于存储的格式有可能与规约的不相应,故对数据进行重新整理(电量,需量,)
//传入ID,数据长度,数据的地址
uchar  SettleDataToFormat(ulong ID,uchar Lenth,uchar *Dest);
uchar EventDataFormat2(ulong ulID, uchar ucLen, uchar *pucBuf);

/////读普通数据
void CommControlReadData(void);
////校验ID是否有效
uchar CheckTheIDUsed(ulong ID);

/////获得读数据中大类数据项的指针
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

/***********************电量数据*********************************************/
////查找数据在电量大类中是属于哪一类
///传出的数据MODE 4后就是相别
u16 GetCommReadECTypeNum(uchar ControlData)
{
    u16 i;
    u16 TableNum;
    
    TableNum=GetECBlockPhaseTableNum();     //获取大块数据的表格长度
    
    for (i=0;i<TableNum;i++)
    {
        if ((ControlData>=TableCommPhaseBlock[i].Block1Start)&&(ControlData<=TableCommPhaseBlock[i].Block1END))
        {
            return i;                       //返回大块数据对应的位置
        }
    }
    return SWITCH_TABLE_ERR;
}

#if 0
////查找电量小类表
///传入ID号
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

////计算电量地址偏移
///TableReadECBlock表中位置
///返回的是历史电量的地址
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

///00,成功,01,失败(电量小类块的读出为全FF的操作)
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
    
    if (ID0==0)///当前
    {
        ECAddr=TableReadECBlock[ECBlockPtr].ECAddr;
        OffsetAddr=0;
    }
    else //历史
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
    ////获得子项
        Lenth=COMM_READ_EC_FEE_MAXSIZE;
        Lenth*=COMM_READ_EC_LENTH;
        if (Lenth>COMM_READMAXSIZE)
        {
            ///保存后续帧到后续BUFFER中
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
///00,成功,否则失败
uchar  GetECHistoryFFData(ulong ID,u16 ECBlockPtr,uchar *Dest)
{
    uchar i;
    uchar ID1=(uchar)(ID>>8);
    uchar ID2=(uchar)(ID>>16);
    ulong ECAddr;
    u16  OffsetAddr;
        uchar  TFeeNum=GetSetFeeNumber()+1;
    ////超过范围的就返回错误
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
///读出卡表的电量数据
//传入为ID，传出为0的话是失败，否则就是数据长度
#if 0
u16 CommReadECCardData(ulong ID);
u16 CommReadECCardData(ulong ID)
{
    
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
#if(CONFIG_METER_STEP_PERIODPRICE_MODE==CONFIG_METER_STEP_PERIODPRICE_MODE_ENABLE)
    if(ID==0x00900200)
    {
        if(0!=JudgeRemainSign(0,CommExpDataBuff.Buffer))
        // aa 如果不是剩余电量 aa
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
            // aa 如果不是剩余电量 aa
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
//////读电量数据
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
    ////读电量中的大类
    ECTypePtr=GetCommReadECTypeNum(ID2);
    if(ECTypePtr!=SWITCH_TABLE_ERR)
    {     
             if(ID2==0x90)    ///卡表数据
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
             else if(ID2 == 0x0B)   //结算周期组合有功累计用电量
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
                if (ECBlockPtr==SWITCH_TABLE_ERR)//没找到ID
                {
                    Dest->strReturnData.ReturnFail=1;   
                }
                else
                {
                    if (TableReadECBlock[ECBlockPtr].ECUseState==0)   ///没有使用当前ID
                    {
                        Dest->strReturnData.ReturnFail=1;   
                    }
                    else
                    {
                    ///如果该大类没有费率项,而ID1却有该项则错误
                        if ((ID1>0)&&(TableReadECBlock[ECBlockPtr].ECFeeState==0)) //没有该ID
                        {
                            Dest->strReturnData.ReturnFail=1;
                        }
                        else
                        {
                            if (ID0==0xFF)   ////操作所有的电量大块数据(当前,历史,)
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
                                if (GetECTBlockFFData(ID,ECBlockPtr,CommExpDataBuff->Buffer)==COMM_TURE)  ///正确
                                {
                                    if(ID2==0xFF)
                                    {
                                        Dest->strReturnData.Lenth=COMM_READ_EC_LENTH*COMM_READ_EC_FEE_MAXSIZE;
                                        //如果后后续帧的话就直接把后续帧置位
                                        //Dest->strReturnData.LastFrame=1;
                                    }
                                    else
                                    {
                                        Dest->strReturnData.Lenth=COMM_READ_EC_LENTH;
                                    }
                                    
                                    Dest->strReturnData.ReturnFail=0;
                                }
                                else   ///失败
                                {
                                    Dest->strReturnData.ReturnFail=1;
                                }
                            }   
                        }
                    }
                }
             }
    }
    else   ////没找到ID
    {
            Dest->strReturnData.ReturnFail=1;
    }
#endif    
}
#if 0
/**********************需量数据*********************************************************/
////计算需量历史地址偏移
///TableReadECBlock表中位置
///返回的是历史电量的地址
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


///00,成功,01,失败(电量小类块的读出为全FF的操作)
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
    
    if (ID0==0)///当前
    {
        ECAddr=TableReadECBlock[ECBlockPtr].MDAddr;
        OffsetAddr=0;
    }
    else //历史
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
        //////获得设置的费率个数
        Lenth=COMM_READ_MD_FEE_MAXSIZE;
        Lenth*=(COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH);
        if (Lenth>COMM_READMAXSIZE)
        {
            ///保存后续帧到后续BUFFER中
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

///00,成功,否则失败
uchar  GetMDHistoryFFData(ulong ID,u16 ECBlockPtr,uchar *Dest)
{
    uchar i;
    uchar ID1=(uchar)(ID>>8);
    uchar ID2=(uchar)(ID>>16);
    ulong ECAddr;
    u16  OffsetAddr;
        uchar  TFeeNum=GetSetFeeNumber()+1;
    ////超过范围的就返回错误
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
////读需量数据(由于与电量是功能和数据结构相差不多故可以与电量共用一种表)
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
    
    MDTypePtr = GetCommReadECTypeNum(ID2);          //根据ID2查找要读出的数据是ABC还是总的
    
    if ((MDTypePtr>3)||(ID2==0))  ///ID错误
    {
        Dest->strReturnData.ReturnFail=1;
    } 
    else
    {   //  因为电量与需量用的是同一张电量小类列表，而需量不支持分相，故此处根据ID2直接判断需量是否合法
        if(ID2>=0x15)
        {
            MDBlockPtr = SWITCH_TABLE_ERR;
        }
        else
        {
            MDBlockPtr=GetCommReadECBlockNum(ID2);   ////查找指针
        }
        if (MDBlockPtr==SWITCH_TABLE_ERR)//没找到ID
        {
            Dest->strReturnData.ReturnFail=1;
        }
        else
        {
            if (TableReadECBlock[MDBlockPtr].MDUseState==0x00)   ///没有使用该ID
            {
                    Dest->strReturnData.ReturnFail=1;
            }
            else  ///
            {
                ///如果该大类没有费率项,而ID1却有该项则错误
                    if ((ID1>0)&&(TableReadECBlock[MDBlockPtr].MDFeeState==0)) //没有该ID
                    {
                        Dest->strReturnData.ReturnFail=1;
                    }
                    else
                    {
                        if (ID0==0xFF)   ////操作所有的电量大块数据(当前,历史,)
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
                            if (GetMDTBlockFFData(ID,MDBlockPtr,CommExpDataBuff->Buffer)==0)  ///正确
                            {
                                if(ID2==0xFF)
                                {
                                    Dest->strReturnData.Lenth=(COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH)*COMM_READ_EC_FEE_MAXSIZE;
                                    //如果后后续帧的话就直接把后续帧置位
                                    //Dest->strReturnData.LastFrame=1;
                                }
                                else
                                {
                                    Dest->strReturnData.Lenth=(COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH);
                                }
                                Dest->strReturnData.ReturnFail=0;
                            }
                            else   ///失败
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
/*****************************变量******************************************************/
////获得ID在变量类数据表中的偏移
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
/////变量数据的读出
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
    if (ID2==0x80)    ///特殊参数表
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
            if (DataTypePtr==SWITCH_TABLE_ERR)  ///表中没有
            {
                    Dest->strReturnData.ReturnFail=1;
            }
            else
            {
                    if(TableVariable[DataTypePtr].Used==0) ///没有该ID
                    {
                            Dest->strReturnData.ReturnFail=1;
                    }
                    else 
                    {
                                if (ID1==0xFF)
                                {
                                    if(TableVariable[DataTypePtr].WithFF==COMM_USE)
                                    {
                                        if(ID0!=0x00)     ////变量DI2
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
                                        if ((ID1<TableVariable[DataTypePtr].StartID)||(ID1>(TableVariable[DataTypePtr].StartID+TableVariable[DataTypePtr].UsedID1Num-1)))  ///错误
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

/*********************事件记录*********************************************/
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

/////查找在故障类事件表中位置
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

////故障1类事件的处理(失压,欠压,断相,过流)
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
#if(COMM_METER_TYPE ==METER_TYPE_THERRPHASE_MORE)  ////多功能
    ReadDataDirect(EvenAddr,32,Dest);
    ReadDataDirect(EvenAddr+32+20,Lenth-20,Dest+32);     
#elif (COMM_METER_TYPE ==METER_TYPE_THERRPHASE)
    ReadDataDirect(EvenAddr,Lenth,Dest);
#endif  
    return (Lenth); 
}


/////故障类事件中的全失压
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

/////故障类事件中的辅助电源失电
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

/////////电压/电流逆相序
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
         
    if(ID2==0x07)  ///电压逆相序
    {
            Lenth=TYPE_ORDER_VOLTAGE_RECORD;
    }
    else          
    {
            if(ID2==0x08)   ///电流逆相序
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
        ////2009。07。03 yaoxuxu
        ////zhonglong 对数据结构做了重新的定义，故凡是电压，电流逆相序事件类，功率正反向类的都需要重新做
        //ReadDataDirect(EvenAddr,Lenth,Dest);  
        ReadDataDirect(EvenAddr,32,Dest);
        ReadDataDirect(EvenAddr+32+20,Lenth-32,Dest+32);

    return (Lenth);
}


/////////电压/电流不平衡
u16 CommEvenUnblance(ulong ID,uchar *Dest)
{
    uchar ID0=(uchar)(ID);
    uchar ID2=(uchar)(ID>>16);
        uchar ID1=(uchar)(ID>>8);
    u16    TabNum=0;
    uchar k;
    u16  Lenth=0;
    ulong EvenAddr=0;
    
    if(ID2==0x09)  ///电压不平衡
    {
        Lenth=TYPE_UNBALANCE_VOLTAGE_RECORD;
    }
    else
    {
            if (ID2==0x0A)  ////电流不平衡
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
        ////////多功能表比较特殊，比规约中的数据要多几种电量
        ReadDataDirect(EvenAddr,34,Dest);
        ReadDataDirect(EvenAddr+34+20,Lenth-34,Dest+34);
    return (Lenth);
}

////潮流反向,过载
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
     ////2009。07。03 yaoxuxu
        ////zhonglong 对数据结构做了重新的定义，故凡是电压，电流逆相序事件类，功率正反向类的都需要重新做
        //ReadDataDirect(EvenAddr,Lenth,Dest);  
        ReadDataDirect(EvenAddr,32,Dest);
        ReadDataDirect(EvenAddr+32+20,Lenth-32,Dest+32);
    return (Lenth); 
        
}


///////过流,失流,断流
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

////掉电
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

///所有故障类事件，全失压、辅助电源掉电、电表掉电
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
    ////发生累计时间,累计次数
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

/////电压合格率统计数据
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
    /////记录长度
    TabNum=GetCheckOutVoltageNum();
    for(k=0;k<TabNum;k++)
    {
        uiLenth+=ucEvenVoltagecheckOut[k];
    }
    
    if(ID0==0x00) ///当前
    {
            ReadDataDirect(TableVoltagecheckOutaddr[i].Currently,uiLenth,Dest);
    }
    else   ////历史
    {
            if (ID0>COMM_EVEN_FAILURE_VOLTAGECHECKOUT_RECORD) 
                return SWITCH_TABLE_ERR;
            EvenAddr=GetTwoTableAddrFromBlock(TableVoltagecheckOutaddr[i].HistoryTwoTable,ID0-1,0);
            if (EvenAddr==GAL_GETTWOTABLE_ADDRERR) return SWITCH_TABLE_ERR;
            ReadDataDirect(EvenAddr,uiLenth,Dest);
    }
    return (uiLenth);
}

/////需量超限
u16 CommEvenMDLoad(ulong ID,uchar *Dest)
{
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
    
    uchar i,k;
    u16  TabNum;
    u16  uilenth=0;
    ulong  Addr;
    
    
    TabNum=GetEvenMDOverLoadTim();
    if((ID1==0x00)&&(ID0==0x00))  ////超限总次数
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
         // 读上1次需量超限，且需量超限事件正在发生
         // 从RAM直接读取事件数据
         // add by ybf 20100826
         if((ID0==0x01) && (FLG_DEMAND_OVER_ALL_STATUS&TB_DEMANDOVER_ADDBIT[ID1-1]))
         {
            memcpy(Dest+12,(uchar*)&DemandOverData[ID1-1],sizeof(ST_DEMAND_OVER_DATA));
         }
    }
    
    return (uilenth);
}

////电表操作
u16 CommEvenMeterHandle(ulong ID,uchar *Dest)
{
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
    
    u16 i,k;
    u16 TabNum=0;
    u16 TableSize=0,TableLenth=SWITCH_TABLE_ERR;
    ulong EvenAddr;
    uchar TmpBuffer[COMM_READMAXSIZE];
    /////后续字节
    STR_LASTFRAME_IN_PARA  TmpPara;
    TmpPara.ucUsed=COMM_PARAMETER_USED;
    TmpPara.ucCommNo=GetExplainCommNo();
    TmpPara.ulID=ID;
    
    /************山东表比较特殊电量请零是30次记录*故做修改,后面可以把TableEvenMeterHandle的
       表格的结构增加一个记录次数项，可以通过判断记录次数来验证ID的有效性***************************************/
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
        
    if(ID0==0x00) ///记录的总次数
    {
        ReadDataDirect(TableEvenMeterHandle[i].TotalAddr,COMM_EVEN_METER_HANDLE_TOTAL,Dest);
        return (COMM_EVEN_METER_HANDLE_TOTAL);
    }
    else    ////记录的内容
    {
        ////获得各个操作事件的头地址
        EvenAddr=GetTwoTableAddrFromBlock(TableEvenMeterHandle[i].TwoTableAddr,ID0-1,0);
        if (EvenAddr==GAL_GETTWOTABLE_ADDRERR) 
            return SWITCH_TABLE_ERR;
        ////读取存储芯片,获得数据,(对于,电量清零,需量清零,这些特殊的,需要按照规约来做下解析)
        TableSize=TableEvenMeterHandle[i].UseTableSize;
        TableLenth=0;
        for(k=0;k<TableSize;k++)
        {
            TableLenth+=(*(TableEvenMeterHandle[i].RecordTableLenth+k));
        }
        
#if (COMM_METER_TYPE ==METER_TYPE_THERRPHASE)   ////简单三相
        ReadDataDirect(EvenAddr,TableLenth,Dest);
#elif(COMM_METER_TYPE ==METER_TYPE_THERRPHASE_MORE)  /////多功能
        /////////////////////针对三相多功能表存储的内容做的调整,多功能存储的内容比规约中要多很多
        switch (ID1)
        {
            case 0x01:   ////电表清零
                ////读出发生时刻,操作者代码
                i=0;
                ReadDataDirect(EvenAddr,10,Dest);
                EvenAddr+=10;
                ///正向有功总电量
                i+=10;
				ReadDataDirect(EvenAddr+5*15,5,Dest+i);
                ////反向有功
                i+=5;
				ReadDataDirect(EvenAddr+5*30,5,Dest+i);
                ///1象限无功
                i+=5;
				ReadDataDirect(EvenAddr+5*75,5,Dest+i);
                ///2象限无功
                i+=5;
				ReadDataDirect(EvenAddr+5*90,5,Dest+i);
                ///3象限无功
                i+=5;
				ReadDataDirect(EvenAddr+5*105,5,Dest+i);
                ///4象限无功
                i+=5;
				ReadDataDirect(EvenAddr+5*120,5,Dest+i);
                ///A相
                i+=5;
				ReadDataDirect(EvenAddr+5*167,10,Dest+i);
                i+=10;
				ReadDataDirect(EvenAddr+5*171,20,Dest+i);
                ///B相
                i+=20;
				ReadDataDirect(EvenAddr+5*179,10,Dest+i);
                i+=10;
				ReadDataDirect(EvenAddr+5*183,20,Dest+i);
                ///C相
                i+=20;
				ReadDataDirect(EvenAddr+5*191,10,Dest+i);
                i+=10;
				ReadDataDirect(EvenAddr+5*195,20,Dest+i);
                TableLenth=10+24*5;
                break;
            case 0x02:   ////需量清零
                ////读出发生时刻,操作者代码
                i=0;
                ReadDataDirect(EvenAddr,10,Dest);
                EvenAddr+=10;
                ////正向有功总
                i+=10;
                ReadDataDirect(EvenAddr,9,Dest+i);
                ///反向有功
                i+=9;
				ReadDataDirect(EvenAddr+9*15,9,Dest+i);
                ///1象限无功
                i+=9;
				ReadDataDirect(EvenAddr+9*60,9,Dest+i);
                ///2象限无功
                i+=9;
				ReadDataDirect(EvenAddr+9*75,9,Dest+i);
                ///3象限无功
                i+=9;
				ReadDataDirect(EvenAddr+9*90,9,Dest+i);
                ///4象限无功
                i+=9;
				ReadDataDirect(EvenAddr+9*105,9,Dest+i);
                ///A相
                i+=9;
				ReadDataDirect(EvenAddr+9*150,18,Dest+i);
				i+=18;
				ReadDataDirect(EvenAddr+9*154,36,Dest+i);
				///B相
				i+=36;
				ReadDataDirect(EvenAddr+9*160,18,Dest+i);
				i+=18;
				ReadDataDirect(EvenAddr+9*164,36,Dest+i);
				///C相
				i+=36;
				ReadDataDirect(EvenAddr+9*170,18,Dest+i);
				i+=18;
				ReadDataDirect(EvenAddr+9*174,36,Dest+i);
                
                TableLenth=10+12*9;
                
                ////////把余下的12*9个字节内容写入后续帧BUbuffer中
                //ReadDataDirect(Dest+TableLenth,108,TmpBuffer);
                memcpy(TmpBuffer,Dest+TableLenth,108);
                TmpPara.ucFrameNo=1;
                TmpPara.ucFormatLen=108;
                if (SaveLastFrameInBuffer(TmpPara,TmpBuffer)==COMM_FAIL) 
                    return SWITCH_TABLE_ERR;
                           
                TableLenth=TableLenth|COMM_READ_RETURN_FRAME_FLAG;
                break;
            case 0x05: /////日时段表编程
                ReadDataDirect(EvenAddr,10,Dest);
                TableSize=TableLenth-10;
                
                EvenAddr+=10;
                ReadDataDirect(EvenAddr,TableSize,Dest+10);
                //////把余下的内容写入后续帧BUbuffer中
                for(i=1;i<4;i++)
                {
                    ReadDataDirect(EvenAddr+i*TableSize,TableSize,TmpBuffer);
                    TmpPara.ucFrameNo=i;
                    TmpPara.ucFormatLen=TableSize;
                    if (SaveLastFrameInBuffer(TmpPara,TmpBuffer)==COMM_FAIL) return SWITCH_TABLE_ERR;
                }
                ///该数据有返回帧的.
                TableLenth=TableLenth|COMM_READ_RETURN_FRAME_FLAG;
                break;
            case 0x08:  /////节假日编程记录
                ReadDataDirect(EvenAddr,10,Dest);
                //////
                TableSize=TableLenth-10;
                EvenAddr+=10;
                ReadDataDirect(EvenAddr,TableSize,Dest+10);
                EvenAddr+=TableSize;
                //////把余下的内容写入后续帧BUbuffer中
                TableSize=42*4;
                for(i=1;i<6;i++)
                {
                    ReadDataDirect(EvenAddr+(i-1)*TableSize,TableSize,TmpBuffer);
                    TmpPara.ucFrameNo=i;
                    TmpPara.ucFormatLen=TableSize;
                    if (SaveLastFrameInBuffer(TmpPara,TmpBuffer)==COMM_FAIL) 
                        return SWITCH_TABLE_ERR;
                }
                ///该数据有返回帧的.
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

////卡表操作
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


/////拉合闸事件记录
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

    ////山东表比较特殊合闸没有总次数
    if((ID1!=0x00)&&(ID0==0X00)) 
        return (SWITCH_TABLE_ERR);
    //////总次数
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
**函数名称: void GetEventRecordData1(STR_READ_RETURN_PARA *Dest,ulong ID)
**输入: Dest用于输出信息存放的结构体指针,ID通信数据ID
**输出: 
**说明: 这部分内容是补充规约里面没有改动的事件记录,为了程序处理方便,将这部分内容从原来的CommEvenRecordData
**      独立出来,与修改部分内容并列
** 全局变量:
** 调用模块:
**
**------------------------------------------------------------------------------------------------------
** 作　者: zlq
** 日　期: 2009年09月23日
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
            case COMM_EVEN_BLOCK_FAILURE:   ///故障类事件的处理
                uiLenth=CommEvenTypeFailue(ID,CommExpDataBuff->Buffer);
                break;
            case COMM_EVEN_BLOCK_VOLTAGE_CHECKOUT:////电压合格率
                    uiLenth=CommEvenCheckOutVoltage(ID,CommExpDataBuff->Buffer);
                break;
            case COMM_EVEN_BLOCK_MD_OVER:   /// 需量超限
                    uiLenth=CommEvenMDLoad(ID,CommExpDataBuff->Buffer);
                    break;
            case COMM_EVEN_BLOCK_METER_HANDLE:  /// 电表操作类
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
**函数名称: uchar IsEventIDValid(uchar ucID1, uchar ucID0, S_IDCONV1* psIDConv)
**输入: ucID1,ucID0当前通信ID中的低两字节部分信息,psIDConv指向当前ID对应的事件记录ID转换表的指针
**输出: 0-ID错误 / 1-ID正确
**说明: 
** 全局变量:
** 调用模块:
**------------------------------------------------------------------------------------------------------
** 作　者: zlq
** 日　期: 2009年09月23日
********************************************************************************************************/
uchar IsEventIDValid(uchar ucID1, uchar ucID0, S_IDCONV1* psIDConv);
uchar IsEventIDValid(uchar ucID1, uchar ucID0, S_IDCONV1* psIDConv)
{
    //小项判断,类似于电量的分费率数据
    if(ucID1 == 0)
    {
        return 0;
    }
    
    if((ucID1 > psIDConv->ucSim1) && (ucID1 != 0xFF))
    {
        return 0;
    }
    
    //次数,类似于电量的月份
    if(((ucID0 > (psIDConv->ucSim0+1)) && (ucID0 != 0xFF))||(ucID0 == 0x00))
    {
        return 0;
    }
    
    //集抄
    if((ucID0 == 0xFF) && (ucID1 == 0xFF))
    {
        return 0;
    }
    
    return 1;
}

/*********************************************************************************************************
**函数名称: void GetEventData(STR_READ_RETURN_PARA *Dest, uchar ucID0, uchar ucID1, S_IDCONV1* psIDConv)
**输入: Dest指向通信返回信息的指针,ucID1,ucID0当前通信ID中的低两字节部分信息,
**      psIDConv指向当前ID对应的事件记录ID转换表的指针
**输出: none
**说明: 这个时候的ID肯定是正确的,因此不需要再做额外合法性判别
** 全局变量:
** 调用模块:
**------------------------------------------------------------------------------------------------------
** 作　者: zlq
** 日　期: 2009年09月23日
**------------------------------------------------------------------------------------------------------
** 修改人  : pylon_zlq
** 修改内容: 1.电量数据送往显示需要保持5字节内容不变,而通讯却只要4字节内容,因此前次编码未考虑此问题,因此
**             存在显示上的bug,为修正此问题,作以下几部分修改
**           2.由于显示不可能带FF类型数据项,因此这部分代码区可保持不变,同时表格也不变,不包括增加内容
**           3.只有单独的数据子项才可能是显示源来获取数据,因此对此类数据用数据类型加以判别,0时非电量类数据
**             不需要改变,1时为电量类数据,需要5字节给出;而原来的事件数据内容分配表中,对电量数据已经偏移漏
**             去第5个字节,因此需要偏移回来,并且对应长度要增加一个字节
**           4.在通讯出口格式处理的地方对单项的电量类数据化5字节为4字节
** 修改日期: 2010年07月01日
********************************************************************************************************/
void GetEventData(STR_READ_RETURN_PARA *Dest, S_IDCONV1* psIDConv, uchar ucID0, uchar ucID1);
void GetEventData(STR_READ_RETURN_PARA *Dest, S_IDCONV1* psIDConv, uchar ucID0, uchar ucID1)  
{
    uchar i;
    uchar ucLen = 0;
    uchar* p = CommExpDataBuff->Buffer;
    S_EVFMT* psEF = (S_EVFMT*)psIDConv->pvFmt;
    ulong ulAddr;
    
    if(ucID0 != 0xFF)                               //单次数据读取,当然也有可能是集抄,那就要看ucID1的值了
    {
        ulAddr =GetTwoTableAddrFromBlock(psIDConv->ucType, ucID0 - 1, 0);
        if(ucID1 == 0xFF)                           //数据集抄,有后续帧情况出现
        {
            for(i=1; i<=psIDConv->ucSim1; i++)      //注意这里次数判断要加上==,这是建表的时候造成的
            {
                ReadDataDirect(ulAddr+psEF->ucOffset, psEF->ucLen, p);
                ucLen += psEF->ucLen;
                p += psEF->ucLen;
                psEF++;
            }
        }
        else                                        //某一次的子项数据记录读取
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
    else                                            //psIDConv->ucID0+1次子项数据读取
    {
        psEF += ucID1 - 1;
        for(i=0; i<=psIDConv->ucSim0; i++)          //注意这里次数判断要加上==,这是建表的时候造成的
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
**函数名称: void GetEventRecordData2(STR_READ_RETURN_PARA *Dest, ulong ulID, ulong ulVirtualID)
**输入: Dest指向通信返回信息的指针,ulID当前通信ID,ulVirtualID经过转换的虚拟ID
**输出: none
**说明: 这是补充规约修改部分的事件记录内容,由于建表标识排列从小到大的缘故,故对成员id的检测从数组最后一个开始
** 全局变量:
** 调用模块:
**------------------------------------------------------------------------------------------------------
** 作　者: zlq
** 日　期: 2009年09月23日
********************************************************************************************************/
void GetEventRecordData2(STR_READ_RETURN_PARA *Dest, ulong ulID, ulong ulVirtualID);
void GetEventRecordData2(STR_READ_RETURN_PARA *Dest, ulong ulID, ulong ulVirtualID)
{
    uchar i;
    uchar ucID0 = (uchar)ulID;
    uchar ucID1 = (uchar)(ulID>>8);
    S_IDCONV1* psIDConv = (S_IDCONV1*)gCs_IDConv1 + (gCuc_IDConv1TabNum - 1);//故障事件表最后一个成员指针
    
    for(i=0; i<gCuc_IDConv1TabNum; i++)
    {
        if((ulID >= psIDConv->ulVID) && (ulVirtualID == psIDConv->ulVID))   //查找到对应的成员信息
        {
            if(IsEventIDValid(ucID1, ucID0, psIDConv) == 1)
            {
                GetEventData(Dest, psIDConv, ucID0, ucID1);                 //ID合法,可以读取数据,
                return;
            }
            
            break;
        }
        psIDConv--;
    }
    
    Dest->strReturnData.ReturnFail = 1;                                     //没有查找到对应ID
}

/*********************************************************************************************************
**函数名称: void GetEventTotalCntAndTime(STR_READ_RETURN_PARA *Dest, ulong ID)
**输入: Dest指向通信返回信息的指针,ulID当前通信ID
**输出: none
**说明: 这是补充规约修改部分的事件记录内容,故障事件类的累计次数和累计时间,由于规约定义都是3字节的BCD码,
**      因此直接查询ID得到对应的数据地址,直接获取
** 全局变量:
** 调用模块:
**------------------------------------------------------------------------------------------------------
** 作　者: zlq
** 日　期: 2009年09月23日
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
**函数名称: void CommEvenRecordData(STR_READ_RETURN_PARA *Dest,ulong ID)
**输入: Dest指向通信返回信息的指针,ulID当前通信ID
**输出: none
**说明: 事件数据记录的读出,由于补充规约的修改,导致这部分内容需要作较大改动,因此将原来的一个函数分成几个并列
**      部分,大致按照改动和未改动两大块实现,
** 全局变量:
** 调用模块:
**------------------------------------------------------------------------------------------------------
** 作　者: zlq
** 日　期: 2009年09月23日
********************************************************************************************************/
void CommEvenRecordData(STR_READ_RETURN_PARA *Dest,ulong ID)
{
    /*del by zlq090922,将下面这部分内容独立出来组成一个函数,当然需要改掉的地方则会在移植时去除
    
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
                    case COMM_EVEN_BLOCK_FAILURE:   ///故障类事件的处理
                        uiLenth=CommEvenTypeFailue(ID,CommExpDataBuff->Buffer);
                        break;
                    case COMM_EVEN_BLOCK_VOLTAGE_CHECKOUT:////电压合格率
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
    
    //added by zlq090922, 故障事件记和购电记录数据标识增加或改变,处理方式改变,先将这部分内容独立出来,其他数据标识对应内容处理过程不变
    //改变的这部分内容,通过将指令标识映射为一个虚拟的指令标识,再查表得到数据内容
    //uchar ID0 = (uchar)ID;
    //uchar ID1 = (uchar)(ID>>8);
    uchar ID2 = (uchar)(ID>>16);
    uchar ID3 = (uchar)(ID>>24);
    ulong ulVirtualID = ID;
    uchar ucFlg = 0;
    if((ID3 == 3) && ((ID2 == 0x32) || (ID2 == 0x33)))      // 历史购电量或者购电金额记录
    {
        ulVirtualID &= 0xFFFF0000L;                         //特定事件记录,将DI1DI0清零
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
            if(ID == 0x10000101)                           //直接处理,见具体规约内容
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
            else                                                //上面两个判断是排除非卷绕型事件记录,需要参考具体规约内容
            {
                ulVirtualID &= 0xFFFF0000L;                     //特定事件记录,将DI1DI0清零
                ucFlg = 2;
            }
        }
    }
    
    if(ucFlg == 0)                                          //未改动部分的处理
    {
        GetEventRecordData1(Dest, ID);
    }
    else if(ucFlg == 2)                                     //改动部分处理
    {
        GetEventRecordData2(Dest, ID, ulVirtualID);
    }
    
}

///参变量数据的读出
void CommReadParaData(STR_READ_RETURN_PARA *Dest,ulong ID)
{
    uchar ID0=(uchar)(ID);
        uchar ID1=(uchar)(ID>>8);
        uchar ID2=(uchar)(ID>>16);
        u16 uiHolidayNum;
        u16 uiLenth,i;
        switch (ID2)
        {
            case 0x03:    ////公共假日
              //uiHolidayNum=GetSetHolidayNum();  /////能读出来的公共假日数目与设置的公共假日数目相关
              uiHolidayNum = 254;                   //edited by zlq091030
              if ((ID0<0x01)||(ID0>uiHolidayNum))  ////错误
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
            case 0x04:  ////循显
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
                case 0x02:   ////按键显示
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
                default:     ////错误
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
                                    if(ID0==0X00)     /////时区表
                                    {
                                        uiHolidayNum=GetFeeSeasonMaxNum();
                                        uiLenth=uiHolidayNum*COMM_SEASON_SIZE;
                                    }
                                    else    ////时段表
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
                            if(TableParaMeter[i].ReadAndWrite&COMM_READ) ////有读的权限
                            {
                                uiLenth=TableParaMeter[i].dataLens;
                                                                /////////////////////////////////////特殊的2个,这个是由张龙特别提供的变量地址位置
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
                                Dest->strReturnData.More=1;  ////没有读权限
                            }
                            break;
                    }
                }
                break;
        }
}

////////////////////////////////////////////////////////////////////////////////

////获得冻结数据模式字,edited by zlq090925 每个冻结类型都配有一个冻结模式字,因此增加传入参数冻结类型
uchar GetCommFreezeWord(uchar ucType)
{
    uchar TmpData;
    ulong ulAddr;
  
    switch(ucType)
    {
        case COMM_FREEZE_TIME:              //定时冻结
            ulAddr = RAM_CHARACTER_FREEZE_EVERYTIME_MODE;
            break;
            
        case COMM_FREEZE_INSTANTANEOUS:     //瞬时冻结
            ulAddr = RAM_CHARACTER_FREEZE_INSTANT_MODE;
            break;
            
        case COMM_FREEZE_SEANSONTABLE_CHANGE://两套时区表切换冻结
        case COMM_FREEZE_DAYTABLE_CHANGE:   //两套日时段表切换冻结
        case COMM_FREEZE_DIVTIMFEE_CHANE:   //分时费率切换冻结
        case COMM_FREEZE_STEP_CHANE:        //阶梯切换冻结
            ulAddr = RAM_CHARACTER_FREEZE_RESTORE_MODE;
            break;
    
        case COMM_FREEZE_HOURORHALF:        //整点冻结
            ReadDataDirect(RAM_CHARACTER_FREEZE_EVERYHOUR_MODE, 1, &TmpData);
            return (TmpData & 0x03);        //特例

        case COMM_FREEZE_DAY:               //日冻结
            ulAddr = RAM_CHARACTER_FREEZE_EVERYDAY_MODE;
            break;
            
        default:
            return 0;
    }
    ReadDataDirect(ulAddr, 1, &TmpData);
    return (TmpData);
}

//////冻结数据的读出
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
        /////后续字节
    STR_LASTFRAME_IN_PARA  TmpPara;
    TmpPara.ucUsed=COMM_PARAMETER_USED;
    TmpPara.ucCommNo=GetExplainCommNo();
    TmpPara.ulID=ID;
    TmpPara.ucFrameNo=0;
         
    TabNum=GetFreezedataNum();
    ucTmpUseNum=GetCommFreezeWord((uchar)(ID>>16));  ////冻结模式字
    ucFeeNum=GetSetFeeNumber();
///////冻结数据比较特殊,故如果ID1是0XFF的时候,就直接在该函数里面把这些数据解析成规约的格式
    if(ID1==0xFF)
    {
                    
        if(ID0==0x00) 
            return SWITCH_TABLE_ERR;
        Addr=GetTwoTableAddrFromBlock(ucTwoTableaddr,ID0-1,0);
        if(Addr==COMM_READ_EC_GETTWOTABLE_ADDRERR) //|| (Addr==GAL_GETTWOTABLE_POINTRERR)) 
            return SWITCH_TABLE_ERR;
        ////读出冻结时间并加上0XAA
        ReadDataDirect(Addr,5,Dest);    
        memset(Dest+5,0xAA,1);
        Lenth+=6;
        uiLen=Lenth;
        TmpFlg=0;  /////是否是要填入后续的，0不是，1：是
        Addr+=5;
        TmpLastLen=0; ////后续帧BUFFER中长度
        for(i=1;i<TabNum;i++)
        {
           if((uchar)(ID>>16) == 0x04)  //ID2=4,整点冻结的特殊处理,没有分费率电量,edited by zlq090930
           {
                TmpUseNum = 1;
                if(i >= 3)                  //edited by zlq091021
                    break;
           }
           else if(i!=(TabNum-1)) 
           {
                TmpUseNum=ucFeeNum+1;
           }        //////////电量与需量
            else 
            {
                TmpUseNum=COMM_READ_FREEZE_VARIABLE_MAXSIZE;
            }   ////变量
            
            TmpLenth=0;
            TmpSize=0;   //////1个小块的长度
           
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
              
            if(uiLen>LAST_FRAME_BLOCKSIZE)  ///后续
            {
                    ///////第一个后续帧的处理
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
            
            if(((uchar)(ID>>16) == 0x04) && (i != 0))     //整点数据,无分费率,特殊处理,edited by zlq090930
            {
                Lenth = 5;
                Addr = i*5+0;
            }
            else
            {
                Lenth=TableFreezeType[i].UseLenth*TableFreezeType[i].UseNum;
                //////从当前的地址倒推回去,计算出地址
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

//整点和半点冻结
void CommReadFeezeZeroData(STR_READ_RETURN_PARA *Dest,ulong ID)
{
  uchar ID2=(uchar)(ID>>16);
  uchar ID0=(uchar)(ID);
  uchar ID1=(uchar)(ID>>8);
  u16  i,k,uiTmp=0;
  uchar TmpBuffer[LAST_FRAME_BLOCKSIZE];
  ulong EvenAddr=GAL_GETTWOTABLE_ADDRERR;
  uchar StateFlag=0;
  //u16  uiLenth=8*240;   ///默认值
  /////后续字节
  STR_LASTFRAME_IN_PARA  TmpPara;
  TmpPara.ucUsed=COMM_PARAMETER_USED;
  TmpPara.ucCommNo=GetExplainCommNo();
  TmpPara.ulID=ID;
  TmpPara.ucFrameNo=0;
  
  
  if(ID2==0x01)  
  {
     if((ID1==0x01)||(ID1==0x02))
     {
       if(ID0==0xFF) /////块读
       {
          if(ID1==0x02) {uiTmp=241;}
          else {uiTmp=1;}
          //////把240*8字节分成8*24个字节用一个缓存BUFFER，共用10个BUFFER
          ////先返回24*8个，则只需要9个后续BUFFER
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
          if((ID0>0xF0)||(ID0==0x00)) {StateFlag=1;}  ///错误
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
  
  //////状态
  if(StateFlag==0) //正确
  {

      Dest->strReturnData.LastFrame=0;
      Dest->strReturnData.Lenth=8;
       Dest->strReturnData.ReturnFail=0;
  }
  else     //错误
  {
      Dest->strReturnData.ReturnFail=1;
  }
}

////冻结数据的读出控制函数
const uchar gCuc_FreezeType[] = 
{
    TYPE_FREEZE_EVERYTIME_RECORD,       //0x00,定时冻结
    TYPE_FREEZE_INSTANT_RECORD,         //0x01,瞬时冻结
    TYPE_FREEZE_SEASONCHANGE_RECORD,    //0x02,两套时区切换冻结
    TYPE_FREEZE_DAYTABLECHANGE_RECORD,  //0x03,两套日时段表切换冻结
    TYPE_FREEZE_HOURTIME_RECORD,        //0x04,整点冻结切换
    TYPE_FREEZE_STEPPRICE_TABLECHANGE_RECORD,   //0x05,两套费率切换冻结
    TYPE_FREEZE_EVERYZERO_RECORD,       //0x06,日零点冻结 
    //0x07,两套阶梯切换冻结
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
        case COMM_FREEZE_TIME:     ///定时冻结
             ucTableType=TYPE_FREEZE_EVERYTIME_RECORD;
             if (ID0>COMM_FREEZE_RECORD_TIM) StateFlag=1;
            break;
        case COMM_FREEZE_INSTANTANEOUS:  ///瞬时冻结
             ucTableType=TYPE_FREEZE_INSTANT_RECORD;
             if (ID0>COMM_FREEZE_IMMEDIATE_TIM) StateFlag=1;
            break;
        case COMM_FREEZE_SEANSONTABLE_CHANGE:////两套时区表切换冻结
                ucTableType=TYPE_FREEZE_SEASONCHANGE_RECORD;
                 if (ID0>COMM_FREEZE_FEETABLE_TIM) StateFlag=1;
            break;
        case COMM_FREEZE_DAYTABLE_CHANGE: /////两套日时段表切换冻结
                ucTableType=TYPE_FREEZE_DAYTABLECHANGE_RECORD;
                 if (ID0>COMM_FREEZE_FEETABLE_TIM) StateFlag=1;
            break;
        case COMM_FREEZE_HOURORHALF:        //整点冻结
            ucTableType=TYPE_FREEZE_HOURTIME_RECORD;
            if(ID0>COMM_FREEZE_HOUR_TIM) StateFlag=1;
            //else
            //{
            //    CommReadFeezeZeroData(Dest,ID);
            //    return;
            //}
            break;
#if(CONFIG_METER_STEP_PERIODPRICE_MODE==CONFIG_METER_STEP_PERIODPRICE_MODE_ENABLE)
        case COMM_FREEZE_DIVTIMFEE_CHANE:///分时费率切换冻结
            ucTableType=TYPE_FREEZE_PERIODPRICE_TABLECHANGE_RECORD;
            if(ID0>COMM_FREEZE_DIVFEECHANGE_TIM) StateFlag=1;
          break;
#endif
        case COMM_FREEZE_DAY:   ///日冻结
            ucTableType=TYPE_FREEZE_EVERYZERO_RECORD;
            if(ID0>COMM_FREEZE_DAY_TIM) StateFlag=1;
            break;
#if(CONFIG_METER_STEP_MODE==CONFIG_METER_STEP_MODE_ENABLE)
        case COMM_FREEZE_STEP_CHANE:    //阶梯切换冻结
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

//////通过ID 来获得读出数据
//返回的值，最高位为0:成功，1:失败。
/// 第二高位为1，为有后续帧，0: 无后续
///第三高位，第4高位空。后面的字节位表示返回数据长度
//输出为，全局变量中
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
    {                       //ID3从0x10到0x1f为事件记录
        CommEvenRecordData((STR_READ_RETURN_PARA*)&ReadReturnPara, Src->ulID);
                            //读取相应的事件记录
        return (ReadReturnPara.uiReturnData);
    }
    //added by zlq090923
    
    uiTabPtr=GetCommReadTypePtr(ID3);
    
    if (uiTabPtr==SWITCH_TABLE_ERR)     //查表错误
    {
        return COMM_RETURN_STATE_FAIL;   //返回最高为失败的值
    }
    else
    {
        ReadTypeFunction=TableCommReadBlock[uiTabPtr].TypeFunction;
        ReadTypeFunction((STR_READ_RETURN_PARA*)&ReadReturnPara,Src->ulID);////调用相应的处理函数
    }
    
    return (ReadReturnPara.uiReturnData);
}



/////通信电量转换为规约格式性数据
///返回数据长度
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
    if (ID1==0xFF)   ////总，各费率项
    {
        ucFeenum=GetSetFeeNumber();
        ucFeenum+=1; 
    }
    else
    {
        if(ID0==0xFF)   ////历史
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

/////通信需量量转换为规约格式性数据
///返回数据长度
uchar  MDDataToFormat(ulong ID,uchar Lenth,uchar *Dest)
{
    uchar ID0=(uchar)(ID);
    uchar ID1=(uchar)(ID>>8);
    uchar ucFeenum=1;
    uchar Tmpbuffer[10];
    u16 i;
    
    if (ID1==0xFF)   ////总，各费率项
    {
        ucFeenum=GetSetFeeNumber();
        ucFeenum+=1; 
    }
    else
    {
        if(ID0==0xFF)   ////历史
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
///////变量转换为规约格式性(注意,存储的格式都是要比规约的字节数多,并且都是要去掉存储的低位)
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
        ///////////////////////由于存储的格式与规约严重的对不牢，故使用这个转换
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
/////事件数据转换成规约格式类型
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
    /////累计次数与累计时间的数据格式不变
    if(ID0==0x00) return Lenth;

    switch (TableCommEvenType[EvenPtr].IDType)
    {
        case COMM_EVEN_BLOCK_FAILURE:   ///故障类事件的处理
        case COMM_EVEN_BLOCK_VOLTAGE_CHECKOUT: ///电压合格率
        case COMM_EVEN_BLOCK_MD_OVER: /////需量超限
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
        case COMM_EVEN_BLOCK_METER_HANDLE:  /////电表操作
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

/////冻结数据转化成规约要求格式
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
    S_IDCONV1* psIDConv = (S_IDCONV1*)gCs_IDConv1 + (gCuc_IDConv1TabNum - 1);//故障事件表最后一个成员指针
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
    
    if(ulID == 0x10000101 || ulID == 0x10000201)        //直接处理,见具体规约内容
    {
        return ucLen;
    }
    
    //上面两个判断是排除非卷绕型事件记录,需要参考具体规约内容
    ulVirtualID &= 0xFFFF0000L;                     //特定事件记录,将DI1DI0清零
    for(i=0; i<gCuc_IDConv1TabNum; i++)
    {
        if((ulID >= psIDConv->ulVID) && (ulVirtualID == psIDConv->ulVID))   //查找到对应的成员信息
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
////由于存储的格式有可能与规约的不相应,故对数据进行重新整理(电量,需量,),由于传出来的数据，需要加上头ID的，故需要移动字节把ID加入数据帧中
//传入ID,数据长度,数据的地址
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


////检查ID是否被使用
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





/////读普通数据
void CommControlReadData(void)
{
    uchar ucLenth;
    u16   ucReturnFramePara;
    STR_READDATA_INPUT  strReadDataIn;
    memset(&strReadDataIn,0x00,sizeof(STR_READDATA_INPUT));
    ////获得通信ID(ucCommFormatType为全局变量)
    strReadDataIn.ulID=GetCommReadData645ID(ucCommFormatType);  //从协议缓冲区中读出数据标识
    ucLenth=GetCommDataLen();       //获取数据区域的长度
    switch (ucLenth)
    {
        case COMM_READ_LENTH_NORMAL:      //一般的读
            break;
        case COMM_READ_LENTH_LOADTIM:  ///负荷记录的起始时间
            GetCommReadLoadDataTim(strReadDataIn.BCDLoadTim);
        case  COMM_READ_LENTH_LOADNUM: ///负荷记录块数
            strReadDataIn.ucLoadBlockNum=GetCommReadLoadDataNum();
            break;
        default:
            CommExpDataBuff->Buffer[0]=BIT0; //数据区域填入0x01，返回出错标识
            SetReturnDataFrame(0x01,(COMMTYPE_READ|BIT6)|BIT7);//给出数据域长度为1、控制码然后进行返回数据的打包
            return;
            //break;
    }
   /////获得通信口
    strReadDataIn.CommNum=GetExplainCommNo();           //获得通信端口号。
    InitialLastFrameBuffer(strReadDataIn.CommNum);  ///清后续帧BUFFER中相应端口中的数据
    ///////校验表中是否存在该项ID
    
    //////根据数据ID获得读出的数据
    ucReturnFramePara=GetDataByID(&strReadDataIn);
    
    ucLenth=(uchar)(ucReturnFramePara&0x00FF); /////获得数据长度
    if ((ucReturnFramePara&COMM_RETURN_STATE_FAIL)!=0)    ////错误应答
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
        ////数据按照规约格式整理
        ucLenth=SettleDataToFormat(strReadDataIn.ulID,ucLenth,CommExpDataBuff->Buffer);
        if((ucReturnFramePara&COMM_RETURN_STATE_WITHLAST)!=0)   ///有后续帧
        {
             SetReturnDataFrame(ucLenth,(COMMTYPE_READ|BIT5)|BIT7);
        }
        else   ////无后续帧
        {
             SetReturnDataFrame(ucLenth,COMMTYPE_READ|BIT7);
        }
    }
}

//======================================================================
//函数：s16 GetDataByDLT07ID
//功能：根据DLT645 ID读取数据
//参数：
//        uchar *pData:       数据buf，用来存放读回的数据
//        u16 *ucLen:        读回数据长度
//        ulong ID:           DLT645 ID( (((ID3*256+ID2)*256)+ID1)*256+ID0 )
//        u16 ulBufLen:      调用是给的buf的长度(该函数暂时不判断此值，所以需要调用时给够足够的buf空间)
//Input:
//Output:
//返回：  -1:读失败或参数错误(ID不支持或不存在、数据buf长度不够)  
//        其他:读回的数据长度
//范围：专供内读
//注释：无。
//=======================================================================

s16 GetDataByDLT07ID(uchar *pData, u16 *ucLen, ulong ID, u16 ulBufLen)
{
    uchar ucLenth;
    s16 ret=-1;
    u16   ucReturnFramePara;
    STR_READDATA_INPUT  strReadDataIn;
    STR_RETURN_EXPLAINBUFFER *pBuffSave, *pTemp;
        
    memset(&strReadDataIn,0x00,sizeof(STR_READDATA_INPUT));
    ////获得通信ID(ucCommFormatType为全局变量)
    strReadDataIn.ulID=ID;
    //暂时虚拟串口1，读后续帧用
    strReadDataIn.CommNum=SOURCE_VIRTUAL;
    //暂时不做后续帧的读
    //InitialLastFrameBuffer(strReadDataIn.CommNum);  ///清后续帧BUFFER中相应端口中的数据
    
    //申请内存并初始化成零，顺便留点余量

    
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

    ///////校验表中是否存在该项ID
    isSpcecial_uart = SOURCE_VIRTUAL;
    //////根据数据ID获得读出的数据
    ucReturnFramePara=GetDataByID(&strReadDataIn);
    isSpcecial_uart = 0xff;
    
    if ((ucReturnFramePara&COMM_RETURN_STATE_FAIL)!=0)    ////错误应答
    {
        ret = -1;
    }
    else
    {
        ////数据按照规约格式整理
        ucLenth=(uchar)(ucReturnFramePara&0x0FFF); /////获得数据长度
        ucLenth=SettleDataToFormat(strReadDataIn.ulID,ucLenth,CommExpDataBuff->Buffer);
        {
            ucLenth = ucLenth & 0xfff;
            if(ucLenth > 4)
            {
                ucLenth = ucLenth - 4; //减去ID CHAR
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
        if((ucReturnFramePara&COMM_RETURN_STATE_WITHLAST)!=0)   ///有后续帧
        {
            //暂时不用支持,但放行第一帧
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
函数：CommDebugSpecial
功能：for special debug
参数：
Input:
Output:
范围：
注释：无。
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
函数：s16 CommReadDLT07Data
功能：根据DLT645 ID读取数据,并打印
参数：
Input:
Output:
范围：主要用来测试GetDataByDLT07ID
注释：无。
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

