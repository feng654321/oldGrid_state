/*********************************************************************************
    版本号     :version 0.1
    模块名       : 远程控制模块
    文件名       : CommExplain.c
    相关文件     : 
    文件实现功能 : 通信主控制模块
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
#ifndef __COMMEXPLAIN_C__
#define __COMMEXPLAIN_C__
#include "common.h"
#include "commexplain.h"
#include "ap_profunction.h"

/////通信帧中表号
///传出地址
void GetCommFrameAddr(uchar * CommAddr);
///检查通信地址是否正确,返回 00失败，01:正确地址,08:广播命令，03统配符方式地址，04:全AA地址
uchar CheckCommAddr(void);
////选择通信的规约类型 00 :07 , 01:97, 02........
////通过控制码来区分通信规约，对于
////规约类型的获得
///入口:控制码号
uchar GetCommExplainType(uchar ControlNo);
uchar GetCommType(void);  ////获得通信规约类型

///通过获得控制码信息，得到通信规约的控制模式
//传入数据的地址， 通信地址的类型
//返回1  没有返回数据，返回0  : 有返回数据
uchar  Chose07CommControlType(uchar  AddrType);
///数据减33处理
//void DecData33(uchar * Ptr,uchar Lenth);
///数据加33处理
void AddData33(uchar * Ptr,uchar Lenth);
void SubData33(uchar * Ptr,uchar Lenth);
////初始化通信该帧数据
void InitialCommExplainFrame(void);

////负荷记录的读出
//void CommReadLoadData (STR_READ_RETURN_PARA *Dest,ulong ID);
//////通过ID 来获得读出数据
//返回的值，最高位为0:成功，1:失败。
/// 第二高位为1，为有后续帧，0: 无后续
///第三高位，第4高位空。后面的字节位表示返回数据长度
//输出为，全局变量中
u16  GetDataByID(STR_READDATA_INPUT* Src);
////获得表通信地址
void GetReadReturnDataAddr(uchar *Dest);
////设置发送的头为0xFE
void GetCommReturnDataFE(uchar *Dest);
////返回读数据的头(FE+68+地址+68+控制码+长度)
void GetReadReturnDataHead(uchar *Dest,uchar ControlData,uchar DataLenth);

////获得控制码号
uchar GetComm645ControlNO(void);

////初始化发送数据的总长度
void InitialOutPutCommDataLenth(void);
///获得发送数据的总长度
uchar GetOutPutCommDataLenth(void);
///645通信控制主函数
void Rcomm645Control(void);
/////读后续数据
///需要获得后续帧的后续ID,帧序号,是否有后续,通道号
void CommControlReadLastData(void);
////比较清零权限密码
uchar ClearCmpPassword(uchar PasswordLevel,uchar *Dest);
////写数据
//比较密码
//记录操作者代码
//读设置表格,
//调用控制函数:(该函数由张龙和李家成提供)
void CommControlWriteData(void);
////读通信地址
void CommReadAddr(void);
///写通信地址
void CommWriteAddr(void);

//更改通信速率
void CommChangeBaudRate(void);
//修改密码
void CommChangePassword(void);
//最大需量清零
void CommClearMD(void);
///电表清零
void CommClearEC(void);
///事件清零
void CommClearEven(void);
////冻结命令
void CommControlFeezeData(void);
////空函数
void NULLFunction(void);
/////返回参数，输入的ID
void NULLFunctionWithReturn(uchar *Dest,ulong ID);

void GetCommPassword(uchar* Dest,uchar Lenth);

void  CommTypeAllControl(uchar AddrType);

/////万能函数
uchar ReadHL645KZ_FE00_Data(void);
uchar WriteHL645KZ_FE00_Data(void);
uchar WriteHL645ADE7758_BE02_Data(void);
uchar ReadHL645ADE7758_BE02_Data(void);

extern unsigned char WriteADRegResumeDataToPar(unsigned short uiRegName,unsigned char ucDatalen, unsigned char *Dst);

//------------------;yaoxuxu 2009.09.29 start 
/////////////////////////////////////////////

uchar DefaultParaInit(void)
{
    u16 len;
    u16 i;
    /*
    #define EPL_COEF_DATA_END 0x0500102C // 4 byte YYMMDDNN BCD 下一个公共假日日期及日时段表号
    #define EPL_COEF_DATA_START 0x05000AA8 // 0 byte   参数数据起始
    len=EPL_COEF_DATA_END-EPL_COEF_DATA_START=1412=512+512+388
    */

    //len=(sizeof(DEFAULT_VALUE_GROUP)/sizeof(uchar));
    len = 1412;
    for(i=0; i<len/64; i++)
    {
        WriteCoefDataWithSync((uchar*)&(DEFAULT_VALUE_GROUP[i*64]),(EPL_COEF_DATA_START+i*64),64);
        Delay(100000);
        ClearWatchDog();
    }
    WriteCoefDataWithSync((uchar*)&(DEFAULT_VALUE_GROUP[i*64]),(EPL_COEF_DATA_START+i*64),len-i*64);
    Delay(100000);
    ClearWatchDog();

#if 0
    memset(&Wr_data[0],0x00,(512-64));
    WriteCoefData3Copy(&Wr_data[0],(RAM_COEF_DATA_START+1536+64),(512-64));
#endif

    CoefPowerUpResume(0);
    return 1;
}
                                                         
////比较2个数组的值是否相等
uchar CommStrCmp(uchar *Dest,uchar *Src,u16 uiLthen)
{
    u16  i;
    for(i=0;i<uiLthen;i++)
    {
        if((*(Dest+i))!=(*(Src+i)))  return 1;
    }
    
    return 0;
}


////通信帧中表号
////传出地址
void GetCommFrameAddr(uchar * CommAddr)
{
  memcpy(CommAddr,&COMM_RECEIVE_FRAME_ADDRSTART,COMM_METRER_ADDR_LENTH);
}
////获得表通信地址
void GetReadReturnDataAddr(uchar *Dest)
{ 
  ReadDataDirect(RAM_USER_COMM_ADDR,COMM_METRER_ADDR_LENTH,Dest);
}
////设置发送的头为0xFE
void GetCommReturnDataFE(uchar *Dest)
{
    uchar i;
    for (i=0;i<COMM_HEAD_FE_NO;i++)
    {
        *(Dest+i)=0xFE;
    }
}


////返回读数据的头(FE+68+地址+68+控制码+长度)
void GetReadReturnDataHead(uchar *Dest,uchar ControlData,uchar DataLenth)
{
     GetCommReturnDataFE(Dest);                         //载入前导符0xfe
    *(Dest+COMM_HEAD_FE_NO)=FORMAT_FRAME_HEAD;          //载入第一个68
     GetReadReturnDataAddr(Dest+COMM_HEAD_FE_NO+1);     //载入通讯地址
    *(Dest+COMM_HEAD_FE_NO+7)=FORMAT_FRAME_HEAD;        //载入第二个68
    *(Dest+COMM_HEAD_FE_NO+8)=ControlData;              //载入控制码
    *(Dest+COMM_HEAD_FE_NO+9)=DataLenth;                //载入数据域长度
     ucOutPutLenth=COMM_HEAD_ADDR_LEN+2+COMM_HEAD_FE_NO;    //
}

///检查通信地址是否正确,返回 00失败，01:正确地址,08:广播命令，03统配符方式地址，04:全AA地址
uchar CheckCommAddr(void)
{
    uchar i;
    uchar ucRet=1;
    uchar ucArrayFrameAddress[COMM_METRER_ADDR_LENTH];
    uchar ucArrayReadAddress[COMM_METRER_ADDR_LENTH];
    
    GetCommFrameAddr(ucArrayFrameAddress);
    
    for ( i = 0; i < COMM_METRER_ADDR_LENTH; i++)
    {
            if (0xAA != ucArrayFrameAddress[i])
            {
                    ucRet = 0;
                    break;
            }
    }
    if( 1 == ucRet)  ///全AA地址
    {
            return COMMTYPE_STAEPARA_ALLAA_ADDR;
    }
    else
    {
                ucRet = 1;
                for ( i = 0; i <COMM_METRER_ADDR_LENTH; i++)
                {
                    if (0x99 != ucArrayFrameAddress[i])
                    {
                        ucRet = 0;
                        break;
                    }
                }
                
                if( 1 == ucRet)  ///全99地址,广播地址
                {
                    return COMMTYPE_STAEPARA_BROADCAST_ADDR;
                }
                else
                {
                        ucRet = 1;
                        
                        ReadDataDirect(COMM_METERADDR,COMM_METRER_ADDR_LENTH,ucArrayReadAddress);
                                          
                        for(i=0;i<COMM_METRER_ADDR_LENTH;i++)
                        {
                            if (ucArrayReadAddress[i]!=ucArrayFrameAddress[i]) ///错误地址
                            {
                                ucRet=0;
                                break;
                            }
                        }

                                           
                        if( 1 == ucRet)   ///正确的地址
                        {
                                return COMMTYPE_STAEPARA_RIGHTADDR;
                        }
                        else
                        {
                                ucRet = 1;
                                for (;i<COMM_METRER_ADDR_LENTH;i++)
                                {
                                    if(ucArrayFrameAddress[i]!=0xAA)
                                    {
                                        ucRet = 0;
                                        break;
                                    }
                                }

                                if( 1 == ucRet) 
                                {
                                    return COMMTYPE_STAEPARA_AA_ADDR;
                                }
                                else
                                {
                                    return COMMTYPE_STAEPARA_ADDR_ERR;
                                }
                            }
                }
        }
}

////获得通信控制类型的指针
u16 GetCommTypePtr(uchar ControlData)
{
    u16 i;
    u16 TableNum;
    TableNum=GetControlTableNum();//获取控制码表格的长度
    for (i=0;i<TableNum;i++)
    {
        if (ControlData==TableCommControl[i].ucControlDataID)
        {                       //查控制码的表格
                return i;
        }
    }
    return SWITCH_TABLE_ERR;
}

///通过获得控制码信息，得到通信规约的控制模式
//传入数据的地址， 通信地址的类型
//返回1  没有返回数据，返回0  : 有返回数据
uchar  Chose07CommControlType(uchar  AddrType)
{
  u16 uiTabPtr;
    PEFUNCTION CommFunction=NULLFunction;
    uchar ucCommStatePara;
    uchar ucControlNO;
    uchar uctemp;
    //------------------;yaoxuxu 2009.09.29 start 
    gucFarCtlFlg=COMM_NOUSE;
//------------------;yaoxuxu 2009.09.29 end 

    ///获得控制号码
    ucControlNO = GetComm645ControlNO();        //得到控制码
    uiTabPtr = GetCommTypePtr(ucControlNO);     //获取控制码在控制码表格中的位置
    if(IfPowerStateOff() && (uiTabPtr!=SWITCH_TABLE_ERR))
    {                                           //不是处于上电且查到控制码所在的表格的位置
        uctemp = TableCommControl[uiTabPtr].ucControlDataID;//取临时控制码，临时控制码，直接用ucControlNO临时变量就行了
        if(!((uctemp == COMMTYPE_READ)          //不是通讯读数据
            ||(uctemp == COMMTYPE_READWITHLAST) //
            ||(uctemp == COMMTYPE_READADDR)
            ||(uctemp == COMMTYPE_DISPLAY)))
        {                                           //除了读的控制码外，停电下，不相应其它控制码
            //停电时禁止设置，tzg
            return COMM_HAVE_NO_RETURN;
        }
    }
    if(uiTabPtr!=SWITCH_TABLE_ERR)      ////表中查找到该通信项
    {
        CommFunction=TableCommControl[uiTabPtr].CommFunction;   ///获得通信的函数
        ucCommStatePara=(TableCommControl[uiTabPtr].strCommControlPara.CommAddrType)&0x7F;////通信的控制参数
        if ((ucCommStatePara & AddrType)!=0)      ///控制字的功能与通信地址的类型是匹配的
        {
            /////执行函数(读，写，。。。。)
            CommFunction();             //执行表格中的函数
            /////远程控制命令不需要应答
            if(gucFarCtlFlg==COMM_USE)   
                return COMM_HAVE_NO_RETURN;
            
            if (TableCommControl[uiTabPtr].strCommControlPara.CommReturnValue==COMMTYPE_STAEPARA_RETURN)
            {
                if((AddrType==COMMTYPE_STAEPARA_BROADCAST_ADDR) && (ucControlNO != COMMTYPE_ZB))  
                {
                    return COMM_HAVE_NO_RETURN; ////广播地址
                }
                else
                {
                    return COMM_HAVE_RETURN;
                }
            }
            else
            {
                    return COMM_HAVE_NO_RETURN;
            }
        }
        else
        {
            return COMM_HAVE_NO_RETURN;
        }
    }
    else
    {
        return COMM_HAVE_NO_RETURN;
    }
}

///数据加33处理
void AddData33(uchar * Ptr,uchar Lenth)
{
    uchar i;
    for(i=0;i<Lenth;i++)
    {
        (* (Ptr+i))+=0x33;
    }
}
///数据减33处理
void SubData33(uchar * Ptr,uchar Lenth)
{
    uchar i;
    for(i=0;i<Lenth;i++)
    {
        (* (Ptr+i))-=0x33;
    }
}
///获得设置的费率数()
uchar GetSetFeeNumber(void)
{
  uchar TmpFeeNum;
  ReadDataDirect(RAM_COEF_PRICE_MAX_NUM,1,&TmpFeeNum);  //读设置的费率数
  TmpFeeNum = BCD_Byte(TmpFeeNum);                        //BCD码转HEX码
  if(TmpFeeNum>COMM_FEE_FEE_NUM)                        //设置的费率数大于最大费率数
    TmpFeeNum = COMM_FEE_FEE_NUM;                       //设置的费率数等于最大费率数
  
  return (TmpFeeNum);
}

// aa 获取最大阶梯数量 aa
uchar GetSetLadderNumber(void)
{
  uchar TmpLadderNum;
  ReadDataDirect(RAM_COEF_STEP_NUM,1,&TmpLadderNum);    //读设置的阶梯数
  TmpLadderNum=BCD_Byte(TmpLadderNum);                  //BCD转HEX
  
  return (TmpLadderNum);
}

////获得645规约的ID(注意,字节高低位的顺序,不同单片机有可能不同需要修改)
ulong GetCommReadData645ID(uchar FormatNO)
{
    ulong ulID=0xFFFFFFFF;
    if (FormatNO==COMMTYPE_07)
    {
        memcpy(&ulID,&COMM_RECEIVE_FRAME_DATA,4);
    }
    else 
    {
        memset(&ulID,0x00,4);
        memcpy(&ulID,&COMM_RECEIVE_FRAME_DATA,2);
    }   
  return (ulID);            //返回数据通讯标识符
}


uchar GetCommDataLen(void)
{
    return (COMM_RECEIVE_FRAME_LENTH);          //返回通讯数据区域的长度
}

///////读取
uchar GetCommReadLoadDataNum(void)
{
///////start  yaoxuxu      2009.08.20    
    return (COMM_LOADRECORD_READOUT_NO);        //返回读后续帧的序号
///////end  yaoxuxu      2009.08.20    
}


void GetCommReadLoadDataTim(uchar * TimAddr)
{
    ;
}

/////获得通信端口号。
uchar GetExplainCommNo(void)
{
    if(isSpcecial_uart >= 0xf)
        return (CommExpReceiveDataBuffer.communicateFlag.source);
    else
        return isSpcecial_uart;
}

////初始化通信该帧数据
void InitialCommExplainFrame(void)
{
    memset((uchar*)&LastFrameData, 0, sizeof(LastFrameData));
}

//////清零串口1  UART1_CHANNEL的所有后续帧数据
void  CommClearLtBfIR(void);
void  CommClearLtBfIR(void)
{
  uchar Ptr;
  for(Ptr=0;Ptr<LAST_FRAME_NUM;Ptr++)
  {
      if (LastFrameData[Ptr].HeadPara.ucCommNo==SOURCE_IR)
      {                                                 
          LastFrameData[Ptr].HeadPara.ucUsed=COMM_PARAMETER_NO_USED;
      }
  } 
}
//////清零串口2  UART1_CHANNEL的所有后续帧数据
void  CommClearLtBf485(void);
void  CommClearLtBf485(void)
{ 
  uchar Ptr;
  for(Ptr=0;Ptr<LAST_FRAME_NUM;Ptr++)
  {
      if (LastFrameData[Ptr].HeadPara.ucCommNo==SOURCE_485)
      {
          LastFrameData[Ptr].HeadPara.ucUsed=COMM_PARAMETER_NO_USED;
      }
  } 
}

//////清第二路的所有后续帧数据
void  CommClearLtSecond(void);
void  CommClearLtSecond(void)
{
  uchar Ptr;
  for(Ptr=0;Ptr<LAST_FRAME_NUM;Ptr++)
  {
      if (LastFrameData[Ptr].HeadPara.ucCommNo==SOURCE_COMM_SECOND)
      {
          LastFrameData[Ptr].HeadPara.ucUsed=COMM_PARAMETER_NO_USED;
      }
  } 
}

//////清虚拟串口的所有后续帧数据
void  CommClearLtVirtual485(void)
{
  uchar Ptr;
  FUNCTRACE();
  for(Ptr=0;Ptr<LAST_FRAME_NUM;Ptr++)
  {
      if (LastFrameData[Ptr].HeadPara.ucCommNo==SOURCE_VIRTUAL)
      {
          LastFrameData[Ptr].HeadPara.ucUsed=COMM_PARAMETER_NO_USED;
      }
  } 
}

//////清通信口的所有后续帧数据
/*void  CommClearLastFrame(uchar ucCommNO);
void  CommClearLastFrame(uchar ucCommNO)
{
  uchar Ptr;
  for(Ptr=0;Ptr<LAST_FRAME_NUM;Ptr++)
  {
      if (LastFrameData[Ptr].HeadPara.ucCommNo==ucCommNO)
      {
          LastFrameData[Ptr].HeadPara.ucUsed=COMM_PARAMETER_NO_USED;
      }
  } 
}*/

/////初始化后续帧缓存中对应通信端口号中的数据
///(也可以扩展为只是针对某个通道的某个ID来清除后续缓存中的数据)
////此方法有一个问题,就是如果几个通道都同时读后续的话,后续就会发生拥挤,数据会读不出来.
//并会产生碎片.有一种情况:A通道读数据,数据有后续并占用了所有的缓存.A不读后续.B通道也来读后续,
///结果B一直都读不着后续.
void InitialLastFrameBuffer(uchar CommNo)
{
  uchar Ptr;
  
  for(Ptr=0;Ptr<LAST_FRAME_NUM;Ptr++)
  {
      if (LastFrameData[Ptr].HeadPara.ucCommNo==CommNo)
      {                                     //没有被端口占用的后续帧缓冲区
          LastFrameData[Ptr].HeadPara.ucUsed=COMM_PARAMETER_NO_USED;
      }
  }
}


/////清除该后续帧中的数据
////3分钟后自动清掉BUFFER中内容
void CearLastFrameBuffer(uchar ucCommNo);
void CearLastFrameBuffer(uchar ucCommNo)
{
    switch (ucCommNo)
    {
        case SOURCE_IR:
            StartTime1s(T1SID_SOURCE_IR_LFCLR,          180,  TIMER_MODE_CONTINUE, CommClearLtBfIR);
            break;
        case SOURCE_485:
            StartTime1s(T1SID_SOURCE_485_LFCLR,         180,  TIMER_MODE_CONTINUE, CommClearLtBf485);
            break;
        case SOURCE_COMM_SECOND:
            StartTime1s(T1SID_SOURCE_COMM_SECOND_LFCLR, 180,  TIMER_MODE_CONTINUE, CommClearLtSecond);
            break;
        case SOURCE_VIRTUAL:
            StartTime1s(T1SID_SOURCE_VIRTUAL_LFCLR,     180,  TIMER_MODE_CONTINUE, CommClearLtVirtual485);
            break;
        default:
            break;
    }
}

////把后续的数据保存入后续帧BUffer中.
///后续帧是按照块来安排数据每块长度为180字节,172个Buffer,8个字节是该块的信息,总共有6块.
///////后续帧函数的定义
///后续帧分配空间函数(传入的参数,传入的数据,)
///返回COMM_FAIL,或COMM_TURE
uchar SaveLastFrameInBuffer(STR_LASTFRAME_IN_PARA InPara,uchar *Dest)
{
    uchar Ptr;
        uchar ucCommNo;
        
        ucCommNo=GetExplainCommNo();
    for(Ptr=0;Ptr<LAST_FRAME_NUM;Ptr++)
    {
         if (LastFrameData[Ptr].HeadPara.ucUsed==COMM_PARAMETER_NO_USED) break;
    }
    if (Ptr>=LAST_FRAME_NUM) return COMM_FAIL;
    
    if (InPara.ucFormatLen>LAST_FRAME_BLOCKSIZE)    return COMM_FAIL;
    
        
    memcpy(&LastFrameData[Ptr].HeadPara,&InPara,sizeof(STR_LASTFRAME_IN_PARA));///头信息
        LastFrameData[Ptr].HeadPara.ucCommNo=ucCommNo;
    memcpy(&LastFrameData[Ptr].Buffer,Dest,LastFrameData[Ptr].HeadPara.ucFormatLen); ///数据内容
    ////3分钟后自动清掉BUFFER中内容
        CearLastFrameBuffer(ucCommNo);
        
    return COMM_TURE;
}

/////获得公共假日数目
u16 GetSetHolidayNum(void)
{
   u16 TmpFeeNum;
   uchar TmpBCD[2];
   ReadDataDirect(RAM_COEF_HOLIDAY_MAX_MUN,2,TmpBCD);   
   TmpFeeNum=BCD2_Word(TmpBCD);
   
   return (TmpFeeNum);
}


////获得循显个数
u16 GetSetCycleLcdNum(void)
{
  uchar TmpBCD;
  ReadDataDirect(RAM_COEF_AUTO_TURNPAGE_NUM,1,&TmpBCD); 
    TmpBCD=BCD_Byte(TmpBCD);
    
    return (TmpBCD);
}

////获得键显个数
u16 GetkeyCycleNum(void)
{
     uchar TmpBCD;
     ReadDataDirect(RAM_COEF_KEY_TURNPAGE_NUM,1,&TmpBCD);   
     TmpBCD=BCD_Byte(TmpBCD);
     
     return (TmpBCD);
}

////获得年时区数
u16  GetFeeSeasonMaxNum(void)
{
    uchar TmpBCD;
    ReadDataDirect(RAM_COEF_SEASONTABLE_MAX_NUM,1,&TmpBCD); 
    TmpBCD=BCD_Byte(TmpBCD);
     
     return (TmpBCD);
}

////获得时段表个数
u16  GetFeeDayTableMaxNum(void)
{
    uchar TmpBCD;
    ReadDataDirect(RAM_COEF_DAYTABLE_MAX_NUM,1,&TmpBCD);    
    TmpBCD=BCD_Byte(TmpBCD);
     
    return (TmpBCD);
    
}
////获得时段个数
u16  GetFeeTouTableMaxNum(void)
{
    uchar TmpBCD;
    ReadDataDirect(RAM_COEF_PERIOD_MAX_NUM,1,&TmpBCD);  
    TmpBCD=BCD_Byte(TmpBCD);
    
    return (TmpBCD);
}


///设置正确的返回帧（调用了全局变量规约类型）
void SetReturnDataFrame(uchar DataLenth,uchar ControlData)
{
    uchar ucCommCS=0;
    
    GetReadReturnDataHead(CommExpDataBuff->Head, ControlData,DataLenth);//根据控制码、数据域的长度等载入数据帧的帧头
    AddData33(&CommExpDataBuff->Buffer[0],DataLenth);        //数据区域加33操作
    ucOutPutLenth += DataLenth;                             //输出长度加上数据区域的长度
    ucCommCS=CommCalChksum(&CommExpDataBuff->Head[COMM_HEAD_FE_NO],ucOutPutLenth-COMM_HEAD_FE_NO);//计算校验和校验
    CommExpDataBuff->Buffer[DataLenth]=ucCommCS;             //写入校验和
    CommExpDataBuff->Buffer[DataLenth+1]=FORMAT_FRAME_END;   //写入结束符
    ucOutPutLenth+=2;             //发送长度再加2
}

////获得控制码号
uchar GetComm645ControlNO(void)
{
    return (COMM_RECEIVE_FRAME_CONTROLNO);
}
////规约类型的获得(初始化规约类型参数)
///入口:控制码号
uchar GetCommExplainType(uchar ControlNo)
{
    ///分别查找07,97的控制码表,如果2个表都没有的话就返回错误
    ///在此处暂时使用07版规约
  switch (ControlNo)
  {
      case 0x06:
      case 0x05:
          return (COMMTYPE_ALLCOMM);
      case 0x1C:
      default:
          return (COMMTYPE_07);
  }
}

////获得规约类型
uchar GetCommType(void)
{
  return (ucCommFormatType);
}

////初始化发送数据的总长度
void InitialOutPutCommDataLenth(void)
{
    ucOutPutLenth=0;
}

///获得发送数据的总长度
uchar GetOutPutCommDataLenth(void)
{
    return (ucOutPutLenth);
}

////获得主机请求的帧序号
uchar GetLastFrameNum(void);
uchar GetLastFrameNum(void)
{
    return (COMM_LAST_FRAME_NUM);
}
/////读后续数据
///需要获得后续帧的后续ID,帧序号,是否有后续,通道号
void CommControlReadLastData(void)
{
        ulong ulID;
        uchar ucLenth=0,Ptr,i,ucState=0;
        uchar ucFrameNum;
        uchar ucCommNum;
        u16  ulLenth=0,TmpLen;
               
                uchar ID3;
                
        uchar TmpBuffer[LAST_FRAME_BLOCKSIZE];
        ulID=GetCommReadData645ID(ucCommFormatType);
            
        ucLenth=GetCommDataLen();
        ucFrameNum=GetLastFrameNum();
        ucCommNum=GetExplainCommNo();
        ID3=(uchar)(ulID>>24);
        if(ucLenth!=0x05)   ///错误
        {
            ucState=0;
            CommExpDataBuff->Buffer[0]=BIT0;
        } 
        else
        {
                for(Ptr=0;Ptr<LAST_FRAME_NUM;Ptr++)
                {
                     if ((LastFrameData[Ptr].HeadPara.ucUsed==COMM_PARAMETER_USED)&&(
                                    LastFrameData[Ptr].HeadPara.ucCommNo==ucCommNum)&&(
                                    LastFrameData[Ptr].HeadPara.ucFrameNo==ucFrameNum)&&(
                                    LastFrameData[Ptr].HeadPara.ulID==ulID)&&(LastFrameData[Ptr].HeadPara.ucFormatLen>0)) 
                        {
                            break;
                        }
                }
                if (Ptr>=LAST_FRAME_NUM)   ///错误
                {
                    ucState=0;
                }
                else   ////正确
                {
                        memcpy(&CommExpDataBuff->Buffer[0],&ulID,4);
                                                ulLenth+=4;
                                                if(ID3==0x06)    //////负荷记录的后续帧
                                                {
                                                   //////////////////////////
                                                    TmpLen=CommLoadLastFrameRead(Ptr,ulID,&CommExpDataBuff->Buffer[4]);
                                                    if(TmpLen&COMM_READ_RETURN_FRAME_FLAG)   ///还有后续
                                                    {
                                                        ucState=2;
                                                    }
                                                    else
                                                    {
                                                        ucState=1;
                                                    }
                                                    ucLenth=((uchar)TmpLen);
                                                    ulLenth+=ucLenth;
                                                    memcpy(&CommExpDataBuff->Buffer[4+ucLenth],&ucFrameNum,1);
                                                    ulLenth+=1;
                                                }
                                                else
                                                {
                                                        
                                                        switch (ulID&0xFFFFFF00)    ////后续桢中一些存储格式特殊的需要处理的
                                                        {
                                                                case 0x03300200:    ////需量清零记录比较特殊故需要转换成规约的格式
                                                                        ucLenth=LastFrameData[Ptr].HeadPara.ucFormatLen/(COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH);
                                                                        for(i=0;i<ucLenth;i++)
                                                                        {
                                                                                memcpy(TmpBuffer,&LastFrameData[Ptr].Buffer[i*(COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH)+1],COMM_READ_MD_FORMAT_LENTH+COMM_READ_MD_TIME_FORMAT_LENTH);
                                                                                memcpy(&LastFrameData[Ptr].Buffer[i*(COMM_READ_MD_FORMAT_LENTH+COMM_READ_MD_TIME_FORMAT_LENTH)],TmpBuffer,COMM_READ_MD_FORMAT_LENTH+COMM_READ_MD_TIME_FORMAT_LENTH);
                                                                        }
                                                                        ucLenth*=(COMM_READ_MD_FORMAT_LENTH+COMM_READ_MD_TIME_FORMAT_LENTH);
                                                                        break;
                                                                default:
                                                                        memcpy(&CommExpDataBuff->Buffer[4],LastFrameData[Ptr].Buffer,LastFrameData[Ptr].HeadPara.ucFormatLen);
                                                                        ucLenth=LastFrameData[Ptr].HeadPara.ucFormatLen;
                                                                        break;
                                                        }
                                                        memcpy(&CommExpDataBuff->Buffer[4],LastFrameData[Ptr].Buffer,ucLenth);
                                                        ulLenth+=ucLenth;
                                                       // memcpy(&CommExpDataBuff->Buffer[4+ucLenth],&ucFrameNum,ucLenth);
                                                        memcpy(&CommExpDataBuff->Buffer[4+ucLenth],&ucFrameNum,1);
                                                        ulLenth+=1;
                                                        ////////把相关的后续缓存释放掉
                                                        LastFrameData[Ptr].HeadPara.ucUsed=COMM_PARAMETER_NO_USED;
                                                        
                                                        for(Ptr=0;Ptr<LAST_FRAME_NUM;Ptr++)
                                                        {
                                                                 if ((LastFrameData[Ptr].HeadPara.ucUsed==COMM_PARAMETER_USED)&&(
                                                                                                LastFrameData[Ptr].HeadPara.ucCommNo==ucCommNum)&&(
                                                                                                //LastFrameData[Ptr].HeadPara.ucFrameNo==ucFrameNum+1)&&(
                                                                                                LastFrameData[Ptr].HeadPara.ulID==ulID)&&(LastFrameData[Ptr].HeadPara.ucFormatLen>0)) 
                                                                        {
                                                                                break;
                                                                        }
                                                        }
                                                        if (Ptr>=LAST_FRAME_NUM) ///无后续帧
                                                        {
                                                                ucState=1;
                                                        }
                                                        else  ///有后续帧
                                                        {
                                                                ucState=2;
                                                        }
                                                }
                }
        }
        switch(ucState)
        {
            case 1:   ///无后续帧
                SetReturnDataFrame(ulLenth,COMMTYPE_READWITHLAST|BIT7);
                break;
            case 2:   ///有后续
                SetReturnDataFrame(ulLenth,(COMMTYPE_READWITHLAST|BIT7)|BIT5);
                break;
            default:
                          CommExpDataBuff->Buffer[0]=BIT1;
                          SetReturnDataFrame(0x01,(COMMTYPE_READWITHLAST|BIT6)|BIT7);
                break;
        }
}


/////////////获得操作者代码/////////////////////////
void GetUseNumber(uchar *Dest,uchar Lenth)
{
    memcpy(Dest,&COMM_RECEIVE_WRITE_USEDID,Lenth);
}

/////获得密码
void GetCommPassword(uchar* Dest,uchar Lenth)
{
    memcpy(Dest,&COMM_RECEIVE_WRITE_PASSWORD,Lenth);
}


///获得安全认证得 计时器参数值
u16 GetSecurityTimData(uchar PasswordLevel);
u16 GetSecurityTimData(uchar PasswordLevel)
{
        u16  uiTmpBuffer;
        ReadDataDirect(RAM_PASSWORD_LOCK_TIME_START+PasswordLevel*2,2,(uchar*)&uiTmpBuffer);
        return (uiTmpBuffer);
}

///获得安全认证的错误次数的参数值
uchar GetSecurityCountData(uchar PasswordLevel);
uchar GetSecurityCountData(uchar PasswordLevel)
{
        uchar  uiTmpBuffer;
        ReadDataDirect(RAM_PASSWORD_ERR_COUNT_START+PasswordLevel,1,&uiTmpBuffer);
        return (uiTmpBuffer);
}

void ClrSecurityCount_timeData(uchar PasswordLevel);
void ClrSecurityCount_timeData(uchar PasswordLevel)
{
    uchar ucTemp;
    if(PasswordLevel>COMM_PASSWORD_POPEDOM_9)
    {
        return;
    }
    ucTemp=1;//10-PasswordLevel;
    memset(&RAM[RAM_PASSWORD_ERR_COUNT_START+PasswordLevel], 00, ucTemp);
    
    memset(&RAM[RAM_PASSWORD_LOCK_TIME_START+PasswordLevel*2], 00, ucTemp*2);
    //WriteDataDirect(&RAM[RAM_PASSWORD_LOCK_TIME_START],EPL_PASSWORD_LOCK_TIME_START,20);
    
}

//设置安全认证次数和密码锁定时间
void SetSecurityCount_timeData(uchar PasswordLevel);
void SetSecurityCount_timeData(uchar PasswordLevel)
{
    u16  uiTmp;
    uchar ucCount;

    ucCount=GetSecurityCountData(PasswordLevel);
        
    if(ucCount>=COMM_PASSWORD_ERR_MAXTIME)
    {
        uiTmp=1440;
        WriteDataDirect((uchar*)&uiTmp,RAM_PASSWORD_LOCK_TIME_START+2*PasswordLevel,2);
        WriteDataDirect((uchar*)&uiTmp,EPL_PASSWORD_LOCK_TIME_START+2*PasswordLevel,2);
        ucCount=0;
        WriteDataDirect(&ucCount,RAM_PASSWORD_ERR_COUNT_START+PasswordLevel,1);
        WriteDataDirect(&ucCount,EPL_PASSWORD_ERR_COUNT_START+PasswordLevel,1);
    }
    else
    {
        ucCount+=1;
        WriteDataDirect(&ucCount,RAM_PASSWORD_ERR_COUNT_START+PasswordLevel,1);
        WriteDataDirect(&ucCount,EPL_PASSWORD_ERR_COUNT_START+PasswordLevel,1);
    }
}

///有ID的写比较密码权限
///返回0是有权限操作,否则是无权限操作
uchar CommCmpPassword(uchar PasswordLevel)
{
    uchar TmpBuffer[4];
        
    GetCommPassword(TmpBuffer,4);
    PasswordLevel=ClearCmpPassword(PasswordLevel,TmpBuffer);
    return PasswordLevel;
}

////清零部分比较密码
///需要密码权限,传入的密码
///返回0是有权限操作,否则是无权限操作
uchar ClearCmpPassword(uchar PasswordLevel,uchar *Dest)
// ----PasswordLevel--最低的密码权限要求------
// ----Dest[0]==命令帧中的密码权限-----
// ----Dest[1]Dest[2]Dest[3]==命令帧中的密码内容-----
{
    uchar TmpBuffer[4];
    uchar UseBuffer[4];
    u16  uiTmp;
        
        
    memcpy(TmpBuffer,Dest,4);
// AA --判断权限是否正确-->Start--AA    
    if(TmpBuffer[0]>COMM_PASSWORD_POPEDOM_9) 
    {
         // SetSecurityCount_timeData(TmpBuffer[0]);
        return COMM_FAIL;
    }
    if(TmpBuffer[0]>PasswordLevel)
    {
        // SetSecurityCount_timeData(TmpBuffer[0]);
        return COMM_FAIL;
    }
    
#if(CONFIG_METER_TYPE==CONFIG_METER_TYPE_SD39C)
    if((TmpBuffer[0] != COMM_PASSWORD_POPEDOM_2)&&(TmpBuffer[0] != COMM_PASSWORD_POPEDOM_4)
        &&(TmpBuffer[0] != COMM_PASSWORD_POPEDOM_6))
#else
    if((TmpBuffer[0] != COMM_PASSWORD_POPEDOM_2)&&(TmpBuffer[0] != COMM_PASSWORD_POPEDOM_4))
#endif
    {
        return COMM_FAIL;
    }
// AA --判断权限是否正确-->End--AA  
// AA --判断目前是否还处于锁定时间-->Start--AA
    uiTmp=GetSecurityTimData(TmpBuffer[0]);
    if(uiTmp>0)  return COMM_FAIL;
// AA --判断目前是否还处于锁定时间-->End--AA
        
    ReadDataDirect(EPL_PASSWORD_0+TmpBuffer[0]*4,4,UseBuffer);

// AA --判断密码是否正确--AA
    if(CommStrCmp(&TmpBuffer[1],&UseBuffer[1],3)==1)
    {
        SetSecurityCount_timeData(TmpBuffer[0]);
        return COMM_FAIL;
    }
#if 1   
    else
    {
        ClrSecurityCount_timeData(TmpBuffer[0]);
    }
#endif
    return (COMM_TURE);
}

void ClearAllPasswordErrCount(void)
{
    memset(&RAM[RAM_PASSWORD_ERR_COUNT_START], 0x00, 10);
    WriteDataDirect(&RAM[RAM_PASSWORD_ERR_COUNT_START], EPL_PASSWORD_ERR_COUNT_START, 10);
}

////获得编程键的状态
///1为编程状态,0为非编程状态
uchar GetTheProgramKeyState(void)
{
#if(CONFIG_METER_FACTORY_MODE_ENABLE == CONFIG_METER_FACTORY_MODE)
	return (COMM_TURE);
#endif

#if(0)
    u16 TmpBuffer=0;
#if(CONFIG_METER_NO2COMM_MODE_WIRELESS==CONFIG_METER_NO2COMM_MODE)
    if(WIRELESS_MODULE_COMMNO==GetExplainCommNo())
    {
        return COMM_TURE;
    }
#endif
    ReadDataDirect(RAM_CURRENT_METER_STATUS03,2,(uchar*)&TmpBuffer);
    if (TmpBuffer&BIT3)
    {
        return COMM_TURE;
    }
    else
    {
        return (COMM_FAIL);
    }
#else
    if(FLG_PROGRAM_STATUS == GAL_YES)
        return (COMM_TURE);
    else
        return (COMM_FAIL);
#endif 
}

////读通信地址
void CommReadAddr(void)
{
  uchar ReturnBit=0x13;
  
  GetReadReturnDataAddr(CommExpDataBuff->Buffer);
  SetReturnDataFrame(6,(ReturnBit|BIT7));

}

///写通信地址
void CommWriteAddr(void)
{

    ulong ulAddr=EPL_USER_COMM_ADDR;
    uchar ucState,ReturnLenth;
    uchar ReturnBit=0x15;

    if (GetTheProgramKeyState()==COMM_TURE) 
    {
        ucState=CommWriteBcdFormat(&COMM_RECEIVE_WRITE_ADDR_DATA,DLT_METER_ADDR_LEN,&ReturnLenth);
        if(ucState==COMM_TURE)
        {
            CWBFCommAddrChange();
            WriteCoefDataWithSync(&COMM_RECEIVE_WRITE_ADDR_DATA,ulAddr,DLT_METER_ADDR_LEN);
            memcpy(&RAM[RAM_USER_COMM_ADDR], &COMM_RECEIVE_WRITE_ADDR_DATA, DLT_METER_ADDR_LEN);
            SetReturnDataFrame(0,(ReturnBit|BIT7));
            return;
        }
    }
    /////发生错误的话长度置为0
    ucOutPutLenth=0;
}


/////获得广播校时类型
uchar GetBroadCastType(void);
uchar GetBroadCastType(void)
{
    uchar ucBroadCast=0;
    
    ReadDataDirect(CFGDIR_MODE_BROADCAST_TIME,1,&ucBroadCast);
    
    return ucBroadCast;
}


///广播校时
void CommBroadCastTime(void);
void CommBroadCastTime(void)
{
    uchar ucDataLen,ucFlag=0;
    uchar ucBroadCast=0;
    //uchar ErrFlag=0;
    STR_CALENDAR TmpData,SetData,LastData;
    ulong SysTim=0,PcTim=0;
    signed long sIntevTim;
    
    ucDataLen=GetCommDataLen();
    if (ucDataLen==6)
    {
//      ucFlag=TestYear(*(&COMM_BCAST_DATA_START+5));
//      if(ucFlag==0)  return;
//      ucFlag=TestMonth(*(&COMM_BCAST_DATA_START+4));
//      if(ucFlag==0)  return; 
        ucFlag=TestDayMonthYear((&COMM_BCAST_DATA_START+3));
        if(ucFlag==0)  return;
        ucFlag=TestHour(*(&COMM_BCAST_DATA_START+2));
        if(ucFlag==0)  return;
        ucFlag=TestMinute(*(&COMM_BCAST_DATA_START+1));
        if(ucFlag==0)  return;
        ucFlag=TestSecond(*(&COMM_BCAST_DATA_START));
        if(ucFlag==0)  return;

        GetRealTime(&TmpData);
        /////5分钟内不能校时(300秒)
        ///  系统时钟与校准的时钟
        SysTim=CalendarToSec(&TmpData);
        memcpy(&SetData.second,&COMM_BCAST_DATA_START,3);
        SetData.week=TmpData.week;
        memcpy(&SetData.day,&COMM_BCAST_DATA_START+3,3);
        PcTim=CalendarToSec(&SetData);
        sIntevTim=SysTim-PcTim;
        if((sIntevTim>300)||(sIntevTim<-300)) return;
        ///////不在午夜校时,不能在23:55至00:05间校时
        if(TmpData.hour==0x23)  
        {
            if(TmpData.minute>=0x55) return;
        } 

        if(TmpData.hour==0x00)
        {
            if(TmpData.minute<0x05) return;
        }   
        // --AA changed by zhanglong --20091117-->start AA--
        ucFlag=GetTheProgramKeyState();
        if(COMM_FAIL==ucFlag)
        {
            //////1天只能校时1次
            ucBroadCast=GetBroadCastType();
            ReadDataDirect(EPL_LAST_CHANNELS01_BROADCASTTIME,6,&LastData.minute);
            if(ucBroadCast==0x02)  ////按照自然天
            {
                /////系统时钟=上次校时时间的话，就返回,否则就
                SysTim=CalendarToDay(&TmpData);
                PcTim=CalendarToDay(&LastData);
                if(PcTim==SysTim)  return;
            }
            else    ////按照24小时
            {
                /////系统时钟-上次校时时间>24,就返回,否则
                SysTim=CalendarToMin(&TmpData);
                PcTim=CalendarToMin(&LastData);

                sIntevTim=SysTim-PcTim;
                if(sIntevTim<1440)  return;         
            }
        }
        //////校时
        SetRealTime(&SetData);
        ////上次校准时间写入存储器
        if(COMM_TURE==ucFlag)
        {
            memset((uchar * )&SetData, 0x00, sizeof(STR_CALENDAR));
        }
        CWBFTimeChange();
        WriteDataDirect(&SetData.minute,EPL_LAST_CHANNELS01_BROADCASTTIME,6);
         
    }
#if(CONFIG_METER_TYPE==CONFIG_METER_TYPE_SD39C)
    else
    {
        if(10==ucDataLen)
        {
        ucFlag=ClearCmpPassword(COMM_PASSWORD_POPEDOM_6,&COMM_BCAST_DATA_START);
        
        if (ucFlag!=COMM_TURE)
        {
            return;
        }           
//      ucFlag=TestYear(*(&COMM_BCAST_DATA_START+5));
//      if(ucFlag==0)  return;
//      ucFlag=TestMonth(*(&COMM_BCAST_DATA_START+4));
//      if(ucFlag==0)  return; 
        ucFlag=TestDayMonthYear((&COMM_BCAST_DATA_START+3+4));
        if(ucFlag==0)  return;
        ucFlag=TestHour(*(&COMM_BCAST_DATA_START+2+4));
        if(ucFlag==0)  return;
        ucFlag=TestMinute(*(&COMM_BCAST_DATA_START+1+4));
        if(ucFlag==0)  return;
        ucFlag=TestSecond(*(&COMM_BCAST_DATA_START+4));
        if(ucFlag==0)  return;

        GetRealTime(&TmpData);
        /////5分钟内不能校时(300秒)
        ///  系统时钟与校准的时钟
        SysTim=CalendarToSec(&TmpData);
        memcpy(&SetData.second,&COMM_BCAST_DATA_START+4,3);
        SetData.week=TmpData.week;
        memcpy(&SetData.day,&COMM_BCAST_DATA_START+3+4,3);
        PcTim=CalendarToSec(&SetData);
        sIntevTim=SysTim-PcTim;
        if((sIntevTim>600)||(sIntevTim<-600)) return;
        ///////不在午夜校时,不能在23:50至00:10间校时
        if(TmpData.hour==0x23)  
        {
            if(TmpData.minute>=0x50) return;
        } 

        if(TmpData.hour==0x00)
        {
            if(TmpData.minute<0x10) return;
        }   
        // --AA changed by zhanglong --20091117-->start AA--
        ucFlag=GetTheProgramKeyState();
        if(COMM_FAIL==ucFlag)
        {
            //////1天只能校时1次
            ucBroadCast=GetBroadCastType();
            ReadDataDirect(EPL_LAST_CHANNELS02_BROADCASTTIME,6,&LastData.minute);
            if(ucBroadCast==0x02)  ////按照自然天
            {
                /////系统时钟=上次校时时间的话，就返回,否则就
                SysTim=GetGmDay(&TmpData);
                PcTim=GetGmDay(&LastData);
                if(PcTim==SysTim)  return;
            }
            else    ////按照24小时
            {
                /////系统时钟-上次校时时间>24,就返回,否则
                SysTim=GetGmMin(&TmpData);
                PcTim=GetGmMin(&LastData);

                sIntevTim=SysTim-PcTim;
                if(sIntevTim<1440)  return;         
            }
        }
        //////校时
        SetRealTime(&SetData);
        ////上次校准时间写入存储器
        if(COMM_TURE==ucFlag)
        {
            memset((uchar * )&SetData, 0x00, sizeof(STR_CALENDAR));
        }
        CWBFTimeChange();
        WriteDataDirect(&SetData.minute,EPL_LAST_CHANNELS02_BROADCASTTIME,6);
         }
    }
    if(sIntevTim<0)
    {
        PcTim=0-sIntevTim;
        LongToData4BCD(PcTim,(uchar*)& SysTim);
        SysTim=0x8000|SysTim;
    }
    else
    {
        PcTim=sIntevTim;
        LongToData4BCD(PcTim,(uchar*)& SysTim);
    }
    RSOFT_RTC_SECOND    = realTime.second;
    RSOFT_RTC_MINUTE    = realTime.minute;
    RSOFT_RTC_HOUR      = realTime.hour;
    RSOFT_RTC_WEEK      = realTime.week;
    RSOFT_RTC_DAY       = realTime.day;
    RSOFT_RTC_MONTH     = realTime.month;
    RSOFT_RTC_YEAR      = realTime.year;
    ProgramBroadCastTimeChange((uchar *)&TmpData,(u16 )SysTim);
#endif
}


/////串口依据状态字需要设置的类型
COMM_CONST  UARTMODE    CommUartPortType[]=
{
    {BAUDRATE_9600,  DATALENS_8BIT,  STOPBIT_1,  CHECK_EVEN,0},
    {BAUDRATE_600,   DATALENS_8BIT,  STOPBIT_1,  CHECK_EVEN,0},
    {BAUDRATE_1200,  DATALENS_8BIT,  STOPBIT_1,  CHECK_EVEN,0},
    {BAUDRATE_2400,  DATALENS_8BIT,  STOPBIT_1,  CHECK_EVEN,0},
    {BAUDRATE_4800,  DATALENS_8BIT,  STOPBIT_1,  CHECK_EVEN,0},
    {BAUDRATE_9600,  DATALENS_8BIT,  STOPBIT_1,  CHECK_EVEN,0},
    {BAUDRATE_19200, DATALENS_8BIT,  STOPBIT_1,  CHECK_EVEN,0},
    {BAUDRATE_9600,  DATALENS_8BIT,  STOPBIT_1,  CHECK_EVEN,0},
};


/////获得串口状态
////串口参数,状态字
uchar GetCommBautType(UARTMODE * Mode,uchar WordType,uchar CommNormberType)
{
    uchar returnFlag=0;
    switch(WordType&0xFF)
  {
            case BIT1:
                            //------------------------yaoxuxu  2009.11.08   start------
                                if(CommNormberType==0x01) return 0;   //红外
                                   //------------------------yaoxuxu  2009.11.08   end------
                                
                returnFlag=1;
                break;
            case BIT2:
                returnFlag=2;
                break;
            case BIT3:
                returnFlag=3;
                break;
            case BIT4:
                            //------------------------yaoxuxu  2009.11.08   start------
                                if(CommNormberType==0x01) return 0;
                                   //------------------------yaoxuxu  2009.11.08   end------
                returnFlag=4;
                break;
            case BIT5:
                            //------------------------yaoxuxu  2009.11.08   start------
                                if(CommNormberType==0x01) return 0;
                                   //------------------------yaoxuxu  2009.11.08   end------
                returnFlag=5;
                break;
            case BIT6:
                                 //------------------------yaoxuxu  2009.11.08   start------
                //returnFlag=6;
                //break;
                              //------------------------yaoxuxu  2009.11.08   end------
            default:
                    returnFlag=0;
                return (returnFlag);
  }
  memcpy(Mode,&CommUartPortType[returnFlag],sizeof(UARTMODE));
  return returnFlag;
}

//更改通信速率
void CommChangeBaudRate(void)
{
    uchar ucCommNo,ucFlag,ReturnBit=0x17,TmpID0=0x03;
    uchar ucBautWord,ucLenth=1;
    ulong ulAddr;
    
    ucCommNo=GetExplainCommNo();
    ucBautWord=COMM_CHANGE_COMM_BAUT_WORD;
    ucFlag=CommBautWordFm(&ucBautWord,ucLenth,&ucLenth);
    //------------------------yaoxuxu  2009.11.08   start------
    if(ucCommNo==SOURCE_IR)  
        TmpID0=0x01;    ///红外
    //------------------------yaoxuxu  2009.11.08   end------
    if (ucFlag==COMM_TURE)
    {
        if (GetCommBautType(&UartPotr.uartPara,ucBautWord,TmpID0)!=0)
        {
            ucFlag=COMM_TURE;
            switch (ucCommNo)
            {
                case SOURCE_IR:   ///红外
                    ulAddr=EPL_IR_MODULATOR_BAUDRATE;
                    break;
                case SOURCE_485:
                    ulAddr=EPL_COMM485_01_BAUDRATE;
                    break;
                case SOURCE_COMM_SECOND: 
                    ulAddr=EPL_COMM485_02_BAUDRATE;
                    break;
                default:
                    ucFlag=COMM_FAIL;
                    break;
            }
        }
        else
        {
            ucFlag=COMM_FAIL;
        }
    }
    else 
    {
        ucFlag=COMM_FAIL;
    }

    if(ucFlag==COMM_TURE)
    {
        UartPotr.controlData=2;
        WriteCoefDataWithSync(&COMM_CHANGE_COMM_BAUT_WORD,ulAddr,1);
        CommExpDataBuff->Buffer[0]=COMM_CHANGE_COMM_BAUT_WORD;
        ReturnBit|=BIT7;
    }
    else
    {
        UartPotr.controlData=0;
        CommExpDataBuff->Buffer[0]=BIT3;
        ReturnBit|=BIT7;
        ReturnBit|=BIT6;
    }

    SetReturnDataFrame(0x01,ReturnBit);
}

//修改密码
void CommChangePassword(void)
{
    uchar ReturnBit=0x18;
    ulong ulID;
    uchar ID0,ucPasLevel,ReturnLenth;
    uchar UseState=COMM_FAIL;
    
    /////编程键是否被使用
  if (GetTheProgramKeyState()==COMM_TURE) 
  {
        ////比较ID是否有效
        ulID=GetCommReadData645ID(ucCommFormatType);
        if ((ulID>=0x04000C01)&&(ulID<=0x04000C0A))
        {
             UseState=CommWriteBcdFormat(&COMM_RECEIVE_WRITE_PASSWORD,8,&ReturnLenth);
             if (UseState==COMM_TURE)
             {
                     ////比较操作密码是否正确
                     ID0=(uchar)ulID;
                     if(ID0==(COMM_RECEIVE_WRITE_FARME_PASSWORD+1))
                     {
                                ////比较要修改的密码是否有权限被修改
                                ucPasLevel=CommCmpPassword(COMM_RECEIVE_WRITE_FARME_PASSWORD);
                                if(ucPasLevel==COMM_TURE)
                                {
                                        if (COMM_RECEIVE_WRITE_PASSWORD<=COMM_RECEIVE_WRITE_FARME_PASSWORD)
                                        {
                                            ///修改密码
                                             WriteCoefDataWithSync(&COMM_RECEIVE_WRITE_FARME_PASSWORD,EPL_PASSWORD_0+COMM_RECEIVE_WRITE_FARME_PASSWORD*4,4);
                                             ClrSecurityCount_timeData(COMM_RECEIVE_WRITE_FARME_PASSWORD);
                                             UseState=COMM_TURE;
                                        }
                                        else  ///无权操作
                                        {
                                            UseState=COMM_FAIL;
                                        }   
                                }
                                else   ////无权操作
                                {
                                    UseState=COMM_FAIL;
                                }
                     }
                     else  ////错误
                     {
                            UseState=COMM_FAIL;
                     }
                }
                else  {UseState=2;}
                    
        }
        else ////错误
        {
                UseState=COMM_FAIL;
        }
  }
  else   ///无权限
  {
      UseState=COMM_FAIL;
  }
  
  if(UseState==COMM_TURE)  ////修改正确返回帧
  {
        memcpy(CommExpDataBuff->Buffer,&COMM_RECEIVE_WRITE_FARME_PASSWORD,4);
        SetReturnDataFrame(4,ReturnBit|BIT7);
  }
  else    /////修改错误返回帧
  {
      if (UseState==2)   ////BCD错误
      {
        CommExpDataBuff->Buffer[0]=BIT0;
      }
      else 
      {
        CommExpDataBuff->Buffer[0]=BIT2;
      }
      SetReturnDataFrame(1,(ReturnBit|BIT7)|BIT6);
  }
}

//最大需量清零
void CommClearMD(void)
{
    uchar UseState=COMM_FAIL;
    uchar ReturnBit=0x19;
        ulong ulTmp;
        
        STR_PROGRAM_RECORD_INDATA EvenData;
        EvenData.EvenType=PROGRAM_RECORD_DEMAND_CLR;
        EvenData.ID=0xFFFFFFFF;
        
        memcpy(&ulTmp,&COMM_RECEIVE_CLEAR_USERNUM,4);
        EvenData.HanderNum=ulTmp;
        
        EvenData.CommNo=GetExplainCommNo();
        EvenData.CommType=GetCommType();
          
   /////编程键是否被使用
  if (GetTheProgramKeyState()==COMM_TURE) 
  {
        UseState=ClearCmpPassword(COMM_PASSWORD_POPEDOM_4,&COMM_RECEIVE_CLEAR_PASSWORD);
        if (UseState==COMM_TURE)
        {
                UseState=CWBFMaxDemandClr();
                if (UseState==1)
                {
                                  UseState=COMM_TURE;
                      ////调用记录最大需量清零事件的函数
                   EvenProgramRecord(EvenData,&COMM_RECEIVE_CLEAR_USERNUM,0);
                }
                                else {UseState=COMM_FAIL;}
                                  
        }
    }
    
    if (UseState==COMM_TURE)
    {
            SetReturnDataFrame(0,ReturnBit|BIT7);
    }
    else
    {
            CommExpDataBuff->Buffer[0]=BIT2;
            SetReturnDataFrame(1,(ReturnBit|BIT7)|BIT6);
    }
    
}
void CommDisplayNO(void);
void CommDisplayNO(void)
{
    uchar ucDataLen;
    
    ucDataLen=GetCommDataLen();
    if (ucDataLen==5)
    {
        // --aa 01方式是645-07方式aa--
//      if(0x01==COMM_BCAST_DATA_START)
        {
            SetCommDisplayDI (&COMM_BCAST_DATA_START);
        }
    }
}

///电表清零
void CommClearEC(void)
{
    uchar UseState=COMM_FAIL;
    uchar ReturnBit=0x1A;
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_LOCATION)
    ulong ulTmp;
#endif

#if((CONFIG_METER_TYPE_SD39C==CONFIG_METER_TYPE) || (CONFIG_METER_AREA_MODE == CONFIG_METER_AREA_MODE_SOUTHGRID))
    uchar dl_count;
    ulong dianliang_current;
#endif        

#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_LOCATION)
    STR_PROGRAM_RECORD_INDATA EvenData;
    EvenData.EvenType=PROGRAM_RECORD_METER_CLR;
    EvenData.ID=0xFFFFFFFF;
    memcpy(&ulTmp,&COMM_RECEIVE_CLEAR_USERNUM,4);
    EvenData.HanderNum=ulTmp;

    EvenData.CommNo=GetExplainCommNo();
    EvenData.CommType=GetCommType();
        
#if(CONFIG_METER_TYPE_SD39C==CONFIG_METER_TYPE)
    dl_count=RAM[RAM_COEF_CLR_METER_ENABLE_TIMES];
    dianliang_current=ValueHexFromRam3Bcd(RAM_KWH_C_ALL+2);
    if ((dl_count != 0)&&(dianliang_current<10))
#elif (CONFIG_METER_AREA_MODE == CONFIG_METER_AREA_MODE_SOUTHGRID)
    dl_count=RAM[RAM_COEF_CLR_METER_ENABLE_TIMES];
    dianliang_current=ValueHexFromRam3Bcd(RAM_KWH_C_ALL+2);
    if ((dl_count != 0)&&(dianliang_current<20))
#endif
    {
        /////编程键是否被使用
        if (GetTheProgramKeyState()==COMM_TURE) 
        {
            if (COMM_TURE == ClearCmpPassword(COMM_PASSWORD_POPEDOM_2,&COMM_RECEIVE_CLEAR_PASSWORD))
            {
                UseState=CWBFMeterAllClr();
                if (UseState==1)
                {
                    UseState=COMM_TURE;
                    ////调用记录最大需量清零事件的函数
                    EvenProgramRecord(EvenData,&COMM_RECEIVE_CLEAR_USERNUM,0);   
                }
                else 
                {
                    UseState=COMM_FAIL;
                }
            }
        }
    }
#endif
    
    if (UseState==COMM_TURE)
    {
        SetReturnDataFrame(0,ReturnBit|BIT7);
#if((CONFIG_METER_TYPE_SD39C==CONFIG_METER_TYPE) || (CONFIG_METER_AREA_MODE == CONFIG_METER_AREA_MODE_SOUTHGRID))
        dl_count --;
        WriteCoefDataWithSync(&dl_count,EPL_COEF_CLR_METER_ENABLE_TIMES,1);
#endif

    }
    else
    {
        CommExpDataBuff->Buffer[0]=BIT2;
        SetReturnDataFrame(1,(ReturnBit|BIT7)|BIT6);
    }

}
void CommRelaySet(void)
{
//------------------;yaoxuxu 2009.09.29 start 
/*
    uchar UseState=COMM_FAIL;
    uchar ReturnBit=0x1C;
        ulong ulTmp;
        
        STR_PROGRAM_RECORD_INDATA EvenData;
        EvenData.EvenType=PROGRAM_RECORD_METER_CLR;
        EvenData.ID=0xFFFFFFFF;
        memcpy(&ulTmp,&COMM_RECEIVE_CLEAR_USERNUM,4);
        EvenData.HanderNum=ulTmp;
        
        EvenData.CommNo=GetExplainCommNo();
        EvenData.CommType=GetCommType();
        
    UseState=ClearCmpPassword(COMM_PASSWORD_POPEDOM_2,&COMM_RECEIVE_CLEAR_PASSWORD);
    if (UseState==COMM_TURE)
    {
            UseState=CWBFRelayCommand(&COMM_RECEIVE_CLEAR_USERNUM);
            if (UseState==1)
            {
                               UseState=COMM_TURE;
             ////调用记录最大需量清零事件的函数
               EvenProgramRecord(EvenData,&COMM_RECEIVE_CLEAR_USERNUM,0);   
            }
                            else {UseState=COMM_FAIL;}
    }
    */
    
    /*
    if (UseState==COMM_TURE)
    {
            SetReturnDataFrame(0,ReturnBit|BIT7);
    }
    else
    {
            CommExpDataBuff->Buffer[0]=BIT2;
            SetReturnDataFrame(1,(ReturnBit|BIT7)|BIT6);
    }
    */
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
    RelayControl(&CommExpReceiveDataBuffer);
#endif

//------------------;yaoxuxu 2009.09.29 end

    
}

/*********************************************************************************************************
**函数名称: void CommMultiPort(void)
**输入: none
**输出: none
**说明: 多功能口脉冲类型设置,不需编程键,支持广播地址设置
** 全局变量:
** 调用模块:
**------------------------------------------------------------------------------------------------------
** 作　者: zlq
** 日　期: 2009年10月12日
********************************************************************************************************/
void CommMultiPort(void)
{
    uchar ReturnBit=0x1D;

    if(COMM_MULTIPORT_DATA <= 2)
    {
        WriteCoefDataWithSync(&COMM_MULTIPORT_DATA,EPL_COEF_PULSEMODE,1);  //上电重来，不需要备份
        CommExpDataBuff->Buffer[0] = COMM_MULTIPORT_DATA;
        SetReturnDataFrame(1,(ReturnBit|BIT7));
        return;
    }

    /////发生错误的话长度置为0
    ucOutPutLenth=0;
}

/*********************************************************************************************************
**函数名称: void CommControlZB(void)
**输入: none
**输出: none
**说明: 载波通信,地址抄读
** 全局变量:
** 调用模块:
**------------------------------------------------------------------------------------------------------
** 作　者: zlq
** 日　期: 2009年11月20日
********************************************************************************************************/
void CommControlZB(void)
{
    uchar ReturnBit=0x1F;


    CommExpDataBuff->Buffer[0] = 0xAF;//-0x33;
    CommExpDataBuff->Buffer[1] = 0x02;//0x100 + 0x02 - 0x33;
    ReadDataDirect(COMM_METERADDR,COMM_METRER_ADDR_LENTH,(CommExpDataBuff->Buffer+2));
    SetReturnDataFrame(8,(ReturnBit|BIT7));

    /////发生错误的话长度置为0
    //ucOutPutLenth=0;
}

///事件清零
void CommClearEven(void)
{
    uchar UseState=COMM_FAIL;
    uchar ReturnBit=0x1B;
    ulong ulID;
        ulong ulTmp;
      //  u16   ucReturnFramePara;
    //STR_READDATA_INPUT  strReadDataIn;
        
        
        STR_PROGRAM_RECORD_INDATA EvenData;
        EvenData.EvenType=PROGRAM_RECORD_EVENT_CLR;
        memcpy(&ulID,&COMM_EVEN_CLEAR_DATA,4);
        EvenData.ID=ulID;
        
        memcpy(&ulTmp,&COMM_RECEIVE_CLEAR_USERNUM,4);
        EvenData.HanderNum=ulTmp;
        
        EvenData.CommNo=GetExplainCommNo();
        EvenData.CommType=GetCommType();
        
   /////编程键是否被使用
  if (GetTheProgramKeyState()==COMM_TURE) 
  {
        
                UseState=ClearCmpPassword(COMM_PASSWORD_POPEDOM_2,&COMM_RECEIVE_CLEAR_PASSWORD);
        if (UseState==COMM_TURE)
        {
                  /////////////////////对ID有效性的判断
            memcpy(&ulID,&COMM_EVEN_CLEAR_DATA,4);
            {
                UseState=CWBFEventDataClr(ulID);
                if (UseState==1)
                {
                    UseState=COMM_TURE;
                    ////调用记录事件清零清零事件的函数
                    EvenProgramRecord(EvenData,&COMM_RECEIVE_CLEAR_USERNUM,0);    
                }
                else 
                {
                    UseState=COMM_FAIL;
                }
            }   
#if 0
                         TmpID=(ulID&0xFFFFFF00);
                         ID3=(uchar)(ulID>>24); 
                         ID1=(uchar)(ulID>>8);  
                         if((ID3==0x03)||(ID3==0xFF))
                         {
                                 if((TmpID!=0x03300100)&&(TmpID!=0x03300300))
                                 {
                                       if(ulID==0xFFFFFFFF)
                                       {
                                         ucReturnFramePara=0;
                                       }
                                       else
                                       {
                                           // if(ID1==0x00);
                                           // else TmpID+=0x01;
                                            /////获得通信口
                                            strReadDataIn.CommNum=GetExplainCommNo();
                                            // strReadDataIn.ulID=TmpID;
                                            // InitialLastFrameBuffer(strReadDataIn.CommNum);  ///清后续帧BUFFER中相应端口中的数据
                                            //////获得读出的数据
                                            // ucReturnFramePara=GetDataByID(&strReadDataIn);
                                            // InitialLastFrameBuffer(strReadDataIn.CommNum);  ///清后续帧BUFFER中相应端口中的数据
                                         }
                                       
                                          if ((ucReturnFramePara&COMM_RETURN_STATE_FAIL)!=0)  {UseState=COMM_FAIL;}  ////错误应答
                                          else
                                          {
                                              UseState=CWBFEventDataClr(ulID);
                                              if (UseState==1)
                                              {
                                                  UseState=COMM_TURE;
                                           ////调用记录事件清零清零事件的函数
                                                 EvenProgramRecord(EvenData,&COMM_RECEIVE_CLEAR_USERNUM,0);    
                                              }
                                              else {UseState=COMM_FAIL;}
                                          }
                                       
                                 
                                 }
                                 else {UseState=COMM_FAIL;}
                         }
                         else {UseState=COMM_FAIL;}    
#endif
        }
    }
    
    if (UseState==COMM_TURE)
    {
            SetReturnDataFrame(0,ReturnBit|BIT7);
    }
    else
    {
            CommExpDataBuff->Buffer[0]=BIT2;
            SetReturnDataFrame(1,(ReturnBit|BIT7)|BIT6);
    }
}

////冻结命令
void CommControlFeezeData(void)
{
    
    uchar UseState=0;
    uchar ReturnBit=0x16;
    ulong ulID;
        
    UseState=TestMinute(COMM_RECEIVE_FEEZE_DATA_MIN);
    if ((UseState==1)||((COMM_RECEIVE_FEEZE_DATA_MIN==0x99)&&(COMM_RECEIVE_FEEZE_DATA_HOUR==0x99)&&(COMM_RECEIVE_FEEZE_DATA_DAY==0x99)&&(COMM_RECEIVE_FEEZE_DATA_MON==0x99)))
    {
        UseState=1;
        UseState=TestHour(COMM_RECEIVE_FEEZE_DATA_HOUR);
        if ((UseState==1)||((COMM_RECEIVE_FEEZE_DATA_HOUR==0x99)&&(COMM_RECEIVE_FEEZE_DATA_DAY==0x99)&&(COMM_RECEIVE_FEEZE_DATA_MON==0x99)))
        {
            UseState=1;
            UseState=TestDay(COMM_RECEIVE_FEEZE_DATA_DAY);
            if ((UseState==1)||(COMM_RECEIVE_FEEZE_DATA_DAY==0x99))
            {
                    UseState=1;
                    UseState=TestMonth(COMM_RECEIVE_FEEZE_DATA_MON);
                    if ((UseState==1)||(COMM_RECEIVE_FEEZE_DATA_MON==0x99))
                    {
                        UseState=1;
                    }
            }
        }
    }
    
        if (UseState==1)
        {
             //////调用冻结函数
             memcpy(&ulID,&COMM_RECEIVE_FEEZE_DATA_MIN,4);
             UseState=CWBFFreezeInstantRecord(ulID);
        }
     
    if (UseState==1)
    {
                SetReturnDataFrame(0,ReturnBit|BIT7);
    }
    else
    {
        CommExpDataBuff->Buffer[0]=BIT0;
        SetReturnDataFrame(1,(ReturnBit|BIT7)|BIT6);
    }     
}

////空函数
void NULLFunction(void)
{
    ;
}

/////返回参数，输入的ID
void NULLFunctionWithReturn(uchar *Dest,ulong ID)
{
    ;
}
////带返回值的空函数
uchar NULLReturnValue(void)
{
    return 1;
}


//////ADE7758的调试(读)
uchar ReadHL645ADE7758_BE02_Data(void)
{
    uchar uDatalen; 
    u16 uAddr;
    uchar ucCommTmpbuffer[COMM_BUFFERSIZE+4];
    u16 uiID;
    uiID=GetCommReadData645ID(COMMTYPE_ALLCOMM);
    uDatalen=COMM_ADE7758_READ_LENTH;
    uAddr=COMM_ADE7758_READ_ADDRH;
    uAddr=uAddr*256+COMM_ADE7758_READ_ADDRL;
    if(1==ReadADRegComm(uAddr,uDatalen, CommExpDataBuff->Buffer))
    {
          memcpy(ucCommTmpbuffer,&uiID,2);
          memcpy(ucCommTmpbuffer+2,&COMM_ADE7758_READ_ADDRH,1);
          memcpy(ucCommTmpbuffer+3,&COMM_ADE7758_READ_ADDRL,1);
          memcpy(ucCommTmpbuffer+4,&uDatalen,1);
      memcpy(ucCommTmpbuffer+5, CommExpDataBuff->Buffer,uDatalen);
      uDatalen+=5;
      memcpy( CommExpDataBuff->Buffer,ucCommTmpbuffer,uDatalen);
            return (uDatalen);
    }
    return 0;
    
}
////ADE7758的调试(写)
uchar WriteHL645ADE7758_BE02_Data(void)
{
    uchar uDatalen;
    ulong uAddr;
    uDatalen=COMM_ADE7758_WRITE_LENTH;
    uAddr=COMM_ADE7758_WRITE_ADDRH;
    uAddr=uAddr*256+COMM_ADE7758_WRITE_ADDRL;
    if(1==WriteADRegResumeData(uAddr,uDatalen,&COMM_ADE7758_WRITE_DATA))
    {
        return 1;
    }
    return 0;
}

/////万能读函数
uchar ReadHL645KZ_FE00_Data(void)
{
    uchar utstory,uDatalen;
    ulong uAddr;
        uchar ucCommTmpbuffer[COMM_BUFFERSIZE+4];
    
        
        u16 uiID;
    uiID=GetCommReadData645ID(COMMTYPE_ALLCOMM);
        
    utstory=COMM_RECEIVE_ALL_STORYTYPE;
    uDatalen=COMM_RECEIVE_ALL_DATALEN;
    uAddr=utstory;
    uAddr=uAddr*256+COMM_RECEIVE_ALL_DATAHI;
    uAddr=uAddr*256+COMM_RECEIVE_ALL_DATAMID;
    uAddr=uAddr*256+COMM_RECEIVE_ALL_DATALOW;
    if(1==ReadDataDirect(uAddr,  uDatalen, CommExpDataBuff->Buffer))
    {
          memcpy(ucCommTmpbuffer,&uiID,2);
              memcpy(ucCommTmpbuffer+2, CommExpDataBuff->Buffer,uDatalen);
              uDatalen+=2;
              memcpy( CommExpDataBuff->Buffer,ucCommTmpbuffer,uDatalen);
              return (uDatalen);
    }
    return 0;

}
/////万能写函数
uchar WriteHL645KZ_FE00_Data(void)
{
//#if(CONFIG_METER_FACTORY_MODE_ENABLE == CONFIG_METER_FACTORY_MODE)    
    uchar utstory,uDatalen;
    ulong uAddr;

    if((PROGFUNCTION_METER_FACTORY == METER_IN_FACTORY))
    {
        utstory=COMM_WRITE_ALL_STORYTYPE;
        uDatalen=COMM_WRITE_ALL_DATALEN;
        uAddr=utstory;
        uAddr=uAddr*256+COMM_WRITE_ALL_DATAHI;
        uAddr=uAddr*256+COMM_WRITE_ALL_DATAMID;
        uAddr=uAddr*256+COMM_WRITE_ALL_DATALOW;
        //if(1==WriteDataDirect(&COMM_WRITE_ALL_DATA,uAddr, uDatalen))
        if(1==WriteCoefDataWithSync(&COMM_WRITE_ALL_DATA,uAddr,uDatalen))
        {
            return 1;
        }
    }
//#endif    
    return 0;
}

///////远程拉合闸控制
///返回的0为正确，否则就为错误状态字
//
uchar FarCutOrSortGateControl(void);
uchar FarCutOrSortGateControl(void)
{
  STR_PROGRAM_RECORD_INDATA  strRecordData;
  u16 uiTmp,ReturnLenth=2;
  ulong ulTmp;
  uchar ucState;
  memcpy(&uiTmp,&COMM_RECEIVE_STCTGATE_CONTROLID,2);
  strRecordData.ID=0;
  memcpy(&ulTmp,&COMM_RECEIVE_STCTGATE_USERID,4);
  strRecordData.HanderNum=ulTmp;   
    ////要限定唯一的通道
  strRecordData.CommNo=GetExplainCommNo();
     
  strRecordData.CommType=GetCommType();
  
  if(uiTmp==0xAA11)  //拉闸
  {
    strRecordData.EvenType=PROGRAM_RECORD_RELAY_OFF;
  }
  else
  {
      if (uiTmp==0xEE11)  //合闸
      {
        strRecordData.EvenType= PROGRAM_RECORD_RELAY_ON;
      }
      else
      {
          ucState=BIT1;
          return ucState;
      }
  }
  ///记录下编程事件
  EvenProgramRecord(strRecordData,&COMM_RECEIVE_STCTGATE_CONTROLID,ReturnLenth);
  ////执行拉合闸操作
  ucState=CWBFRelayCommand(&COMM_RECEIVE_STCTGATE_USERID);
  if(ucState==1)  {return 0;}
  else  ///没有拉闸成功
  {
    ucState=BIT0;
  }
  return ucState;
}


///////万能读写控制函数
void  CommTypeAllControl(uchar AddrType)
{
    u16 uiID;
    uchar ucControlNO,ReturnBit;
    uchar  ucDataLen=0,ucData;
    //uchar Clear_Array[4];  
    u16 i=0,j;
    uchar status;
    uchar ProgramState;
    uchar  ErrState=COMM_FAIL;
    u16 TableLength;

    uiID=GetCommReadData645ID(COMMTYPE_ALLCOMM);
    ucControlNO=GetComm645ControlNO();

    switch (ucControlNO)
    {
        case 0x05:    ///万能写
            ProgramState=GetTheProgramKeyState(); 
            if((ProgramState==COMM_TURE))
            {
                ErrState=COMM_TURE;
            }
            if(COMM_TURE==ErrState)
            {
                if(0xFE00==uiID)
                {
                    if(1!=WriteHL645KZ_FE00_Data()) 
                        ErrState=COMM_FAIL;
                    else 
                        ErrState=COMM_TURE;
                }
                else if((0xBE02==uiID)&&(PROGFUNCTION_METER_ADJUST== METER_IN_FACTORY))
                {
                    if(1!=WriteHL645ADE7758_BE02_Data())
                    {
                        ErrState=COMM_FAIL;
                    }
                    else 
                    {
                        ErrState=COMM_TURE; 
                    }
                }
                else if((0xBD00==uiID)||(0xBD01==uiID)||(0xBD03==uiID)||(0xBE01==uiID))
                {
                    // 厂内总清
                    // 此处清电表清零记录，并置其他记录清零标识,在ProgramEventMode()中执行总清
                    if(((0xBE01==uiID)&&(PROGFUNCTION_METER_FACTORY == METER_IN_FACTORY)))
                    {
                        CWBFMeterAllClr_InFactory();
                        EventProgramPowerClrRecordClr(0);
                        ErrState=COMM_TURE; 
                    }
                    else
                    {
                        ErrState=COMM_FAIL;
                    }
                }
                //sheng chan ----------start
                else if((0xBE04==uiID)||(0xBE00==uiID))
                {
                    ucData=COMM_97TYPE_WRITEDATA;
                    if(COMM_97TYPE_LENGTH==0x07)
                    {
                        if(0xBE04==uiID)
                        {
#if(CONFIG_METER_FACTORY_MODE_ENABLE == CONFIG_METER_FACTORY_MODE)
                            //本集中器内采软件，生产程序上电初始化时默认进入校表状态。
                            //在这里留个窗口可以暂时改变校表状态
                            //在工厂模式下，进入或者退出校表模式
                            if(PROGFUNCTION_METER_FACTORY == METER_IN_FACTORY)
                            {
                                PROGFUNCTION_METER_ADJUST=ucData;
                                ucData=ucData+0x33;
                                WriteProgramData(&PROGFUNCTION_METER_ADJUST, (EPL_DATA_PROGRAM_START+(0x0000FFFF & CFGDIR_METER_ADJUST_ENABLE)), 1);
                                ErrState=COMM_TURE; 
                            }
                            else 
#endif                            
                            //本集中器内采软件，非生产程序禁止进入校表状态。
                            {
                                ErrState=COMM_FAIL; 
                            }
                        }
                        else if(0xBE00==uiID)
                        {
                            // --aa 进入或者退出工厂模式aa--
#if(CONFIG_METER_FACTORY_MODE==CONFIG_METER_FACTORY_MODE_DISABLE)
                            /*if((ucData==METER_IN_FACTORY) && (FLG_COVER_OPEN_STATUS != GAL_YES))
                            {
                                ErrState=COMM_FAIL; 
                            }
                            else*/
#endif
                            {
                                PROGFUNCTION_METER_FACTORY=ucData;
                                ucData=ucData+0x33;
                                WriteProgramData(&PROGFUNCTION_METER_FACTORY, (EPL_DATA_PROGRAM_START+(0x0000FFFF & CFGDIR_METER_FACTORY_ENABLE)), 1);
                                // 退出工厂模式后，表计自动退出校表模式
                                if((PROGFUNCTION_METER_FACTORY != METER_IN_FACTORY)&&
                                    (PROGFUNCTION_METER_ADJUST == METER_IN_FACTORY))
                                {
                                    PROGFUNCTION_METER_ADJUST = METER_OUT_FACTORY;
                                    WriteProgramData(&PROGFUNCTION_METER_ADJUST, (EPL_DATA_PROGRAM_START+(0x0000FFFF & CFGDIR_METER_ADJUST_ENABLE)), 1);
                                }
                                ErrState=COMM_TURE; 
                            }
                        }
                    }
                }
#if(CONFIG_METER_FACTORY_MODE==CONFIG_METER_FACTORY_MODE_ENABLE)
                else if(0xBE05==uiID)
                {
                    if((COMM_97TYPE_WRITEDATA == 0x00) || (COMM_97TYPE_WRITEDATA == 0xFF))
                        InitParameterChipInfactory(COMM_97TYPE_WRITEDATA);
                    ErrState=COMM_TURE;
                }
                else if(0xBE06==uiID)
                {
                    if((COMM_97TYPE_WRITEDATA == 0x00) || (COMM_97TYPE_WRITEDATA == 0xFF))
                    {
                        InitParameterChipInfactory_withMeterAbout(COMM_97TYPE_WRITEDATA);
                    }
                    ErrState=COMM_TURE;
                }
                else if(0xBE07==uiID)
                {
                    if((COMM_97TYPE_WRITEDATA == 0x00))
                    {
                        InitParameterInfactory();
                    }
                    ErrState=COMM_TURE;
                }
#endif                            
                else if(0xEE40==uiID)
                {   
                    status=COMM_TURE;
                    TableLength=GetAddParameterTableNum();
                    for(i=0;i<TableLength;i++)
                    {
                        if(AddPara[i].id==COMM_97TYPE_ADDDATAID)
                        {
                            break;
                        }
                    }
                    if(i==TableLength)  
                    {
                        status=COMM_FAIL;
                    }
                    if((status==COMM_TURE)&&
                        (COMM_97TYPE_LENGTH==(AddPara[i].dataLens+8)))
                    {
                        status=COMM_FAIL;
                        /*Start of ybf on 2010-9-15 9:48 V1.0*/
                        if(((AddPara[i].id>=0x8001) && (AddPara[i].id<=0x8005))
                            ||((AddPara[i].id>=0x8010) && (AddPara[i].id<=0x8040)))
                        {
                            WriteCoefDataWithSync(&COMM_97TYPE_ADDDATABEGIN,AddPara[i].memoryAddress,AddPara[i].dataLens);
                            status=COMM_TURE;
                        }
                        else if (0x9000==AddPara[i].id)
                        {
                            memset(&Wr_data[0], 0x00, 64);
                            for(i=0;i<16;i++)
                            {
                                WriteCoefDataWithSync(&Wr_data[0],EPL_PUBLIC_HOLIDAY001+i*64,64);
                                ClearWatchDog();
                            }
                            WriteCoefDataWithSync(&Wr_data[0],EPL_COEF_HOLIDAY_MAX_MUN,2);
                            CWBFPriceChange();
                            status=COMM_TURE;
                        }
                        /*End of ybf on 2010-9-15 9:48 V1.0*/
                        else if(PROGFUNCTION_METER_FACTORY == METER_IN_FACTORY)
                        {
                            /*Start of ybf on 2010-9-15 10:10 V1.0*/
                            // 电量清零只允许在厂内模式下可读可写
                            if(AddPara[i].id==0x8050)
                            {
                                WriteCoefDataWithSync(&COMM_97TYPE_ADDDATABEGIN,AddPara[i].memoryAddress,AddPara[i].dataLens);
                                status=COMM_TURE;
                            }
                            /*End of ybf on 2010-9-15 10:10 V1.0*/
                            else if((AddPara[i].id!=0x0000)&&(AddPara[i].id!=0xffff))
                            {                                       
                                if(AddPara[i].byte_order != HIGH_BYTE_FRONT)
                                {
									unsigned char tmp[4] = {0x0};
									unsigned char *p = NULL;
									unsigned char *p1 = NULL;
									unsigned char j = 0;

                                    memcpy(&SYSTEMPROGFUNCTION[0x0000FFFF&AddPara[i].memoryAddress],
                                    &COMM_97TYPE_ADDDATABEGIN, AddPara[i].dataLens);

                                    WriteDataDirect(&COMM_97TYPE_ADDDATABEGIN, 
                                    (EPL_DATA_PROGRAM_START+(0x0000FFFF&AddPara[i].memoryAddress)), AddPara[i].dataLens); 

									if (METER_STANDARD == AddPara[i].id)
									{
										WriteADRegResumeDataToPar(AddPara[i].id,AddPara[i].dataLens,&COMM_97TYPE_ADDDATABEGIN);
									}

									if (PULSE_CONSTANT == AddPara[i].id)
									{
										p1 = &COMM_97TYPE_ADDDATABEGIN;
										p = tmp;
										for(j=0;j<AddPara[i].dataLens;j++)
											*(p++) = *(p1+2-j);

										WriteADRegResumeDataToPar(AddPara[i].id,AddPara[i].dataLens,tmp);
									}

									if (VOLTAGE_RATE == AddPara[i].id)
									{
//										value_tmp = bcd_to_hex_4(&COMM_97TYPE_ADDDATABEGIN)/10;
//										value_tmp = hex_to_bcd_4(value_tmp);
//										p1 = (unsigned char*)&value_tmp;
//										p = tmp;
//										for(j=0;j<4;j++)
//											*(p++) = *(p1+3-j);
										p1 = &COMM_97TYPE_ADDDATABEGIN;
										p = tmp;
										for(j=0;j<AddPara[i].dataLens;j++)
											*(p++) = *(p1+3-j);
																				
										WriteADRegResumeDataToPar(AddPara[i].id,AddPara[i].dataLens-1,tmp);
									}

									if (CURRENT_IB == AddPara[i].id)
									{
										p1 = &COMM_97TYPE_ADDDATABEGIN;
										p = tmp;
										for(j=0;j<AddPara[i].dataLens;j++)
											*(p++) = *(p1+3-j);
										
										WriteADRegResumeDataToPar(AddPara[i].id,AddPara[i].dataLens-1,tmp);
									}

									if (CURRENT_IMAX == AddPara[i].id)
									{
										p1 = &COMM_97TYPE_ADDDATABEGIN;
										p = tmp;
										for(j=0;j<AddPara[i].dataLens;j++)
											*(p++) = *(p1+3-j);
																				
										WriteADRegResumeDataToPar(AddPara[i].id,AddPara[i].dataLens-1,tmp);
									}

                                }
                                else
                                {
                                    for(j=0;j<AddPara[i].dataLens;j++)
                                    {
                                        SYSTEMPROGFUNCTION[(0x0000FFFF&AddPara[i].memoryAddress)+j]
                                        =CommExpReceiveDataBuffer.buff[18+AddPara[i].dataLens-j-1];
                                    }
                                    WriteDataDirect(&SYSTEMPROGFUNCTION[0x0000FFFF&AddPara[i].memoryAddress], 
                                    (EPL_DATA_PROGRAM_START+(0x0000FFFF&AddPara[i].memoryAddress)), AddPara[i].dataLens);
                                }
                                status=COMM_TURE;
                            }
                            else if(AddPara[i].id==0x0000)
                            {
                                AddDataInit();
                                status=COMM_TURE;
                            }
                            else if(AddPara[i].id==0xFFFF)
                            {   // 使用默认参数
                                //68 AA AA AA AA AA AA 68 05 0C 73 21 33 33 33 33 32 32 33 33 33 33 6D 16
                                if(1==DefaultParaInit())
                                status=COMM_TURE;
                            }
                            else
                            {
                                status=COMM_FAIL;
                            }
                        }
                        else
                        {
                        status=COMM_FAIL;       
                        }
                        ErrState=status;
                    }
                }
                //sheng chan ----------end
                else 
                {
                    if(((uiID&0xFF00)==0x7400)&&(((uiID&0x00FF)>=0x00E0)&&((uiID&0x00FF)<=0x00EA)))
                    {
                        //ErrState=WriteZhongDuanCommControl();
                        //ErrState=COMM_TURE;
                        ErrState=COMM_FAIL;
                    }
                    else
                    {
                        ErrState=COMM_FAIL;
                    }
                }
            }
            if(ErrState==COMM_TURE)
            {
                ReturnBit=0x85;
                if(0xBE02==uiID)
                {
                    ucDataLen=4;
                    memcpy(CommExpDataBuff->Buffer,&uiID,2);
                    CommExpDataBuff->Buffer[2]=COMM_ADE7758_WRITE_ADDRH;
                    CommExpDataBuff->Buffer[3]=COMM_ADE7758_WRITE_ADDRL;
                }
                else
                {
                    ucDataLen=0;
                }
                SetReturnDataFrame(ucDataLen,ReturnBit);
            }
            else
            {    
                //if(ErrState==1)   ///权限
                CommExpDataBuff->Buffer[0]=ErrState;
                ReturnBit=0xC5;
                SetReturnDataFrame(1,ReturnBit);
            }
            break;

        case 0x06:   ////万能读
            if(0xFE00==uiID)
            {
                ucDataLen=ReadHL645KZ_FE00_Data();
                ErrState=COMM_TURE;
            }
            else if(0xEE14==uiID)//程序版本号
            {
                ReadDataDirectByComm(CFL_METER_ASCII_SOFT_NO, METER_CON_INF_STR_LENGTH,(uchar *) &CommExpDataBuff->Buffer[2]);
                SwapBuf((uchar *) &CommExpDataBuff->Buffer[2], METER_CON_INF_STR_LENGTH);
                CommExpDataBuff->Buffer[0]=0x14;
                CommExpDataBuff->Buffer[1]=0xee;                         
                ucDataLen=32+2;
                ErrState=COMM_TURE;
            }
            else if(0xEE15==uiID)
            {
                if(COMM_RECEIVE_ALL_INDEX < METER_MAX_NUM)
                {
                    ReadDataDirectByComm(GET_TRUE_ADDR_BY_INDEX(COMM_RECEIVE_ALL_INDEX), METER_CON_INF_STR_LENGTH,(uchar *) &CommExpDataBuff->Buffer[3]);
                    SwapBuf((uchar *) &CommExpDataBuff->Buffer[3], METER_CON_INF_STR_LENGTH);
                    CommExpDataBuff->Buffer[0]=0x15;
                    CommExpDataBuff->Buffer[1]=0xee; 
                    CommExpDataBuff->Buffer[2]=COMM_RECEIVE_ALL_INDEX;
                    ucDataLen=32+3;
                    ErrState=COMM_TURE;
                }
                else
                {
                    ErrState=COMM_FAIL; 
                }
            }
            else if(0xEE40==uiID)
            {
                ErrState=COMM_TURE;
                TableLength=GetAddParameterTableNum();
                for(i=0;i<TableLength;i++)
                    if(AddPara[i].id==COMM_97TYPE_ADDDATAIDREAD)
                        break;
                    
                if((i==TableLength)||(AddPara[i].id==0x0000)    )
                {
                    ErrState=COMM_FAIL;
                }

                if(ErrState==COMM_TURE)
                {
                    if(AddPara[i].byte_order == HIGH_BYTE_FRONT)
                    {
                        for(j=0;j<AddPara[i].dataLens;j++)
                        {
                            CommExpDataBuff->Buffer[4+AddPara[i].dataLens-j-1]=
                            SYSTEMPROGFUNCTION[(0x0000FFFF&AddPara[i].memoryAddress)+j];                                        
                        }
                    }
                    else
                    {
                        if(((AddPara[i].id>=0x8001) && (AddPara[i].id<=0x8005))
                        ||((AddPara[i].id>=0x8010) && (AddPara[i].id<=0x8050)))
                        {
                            //memcpy(&CommExpDataBuff->Buffer[4],(uchar*)&RAM[AddPara[i].memoryAddress],AddPara[i].dataLens);
                            ReadCoefDataWithCheck(AddPara[i].memoryAddress, AddPara[i].dataLens, &CommExpDataBuff->Buffer[4], 0);
                            if((AddPara[i].id==0x8050)&&(PROGFUNCTION_METER_FACTORY == METER_OUT_FACTORY))
                                ErrState=COMM_FAIL;
                        }
                        else if (0x8000==AddPara[i].id)
                        {
                            ErrState=COMM_TURE;
                            if(COMM_97TYPE_ADDDATAREADBEGIN == 0x01)
                                memcpy(&CommExpDataBuff->Buffer[4], &(ucAlarmStatusSpeek[0]), CON_ALARM_TYPE_BYTE_MAX);
                            else if(COMM_97TYPE_ADDDATAREADBEGIN == 0x02)
                                memcpy(&CommExpDataBuff->Buffer[4], &(ucAlarmStatusLedYellow[0]), CON_ALARM_TYPE_BYTE_MAX);
                            else if(COMM_97TYPE_ADDDATAREADBEGIN == 0x03)
#if(CON_ALARM_LEDGREEN_ENABLE == GAL_YES)
                                memcpy(&CommExpDataBuff->Buffer[4], &(ucAlarmStatusLedGreen[0]), CON_ALARM_TYPE_BYTE_MAX);
#else
                                memset(&CommExpDataBuff->Buffer[4], 0x00, CON_ALARM_TYPE_BYTE_MAX);
#endif
                            else if(COMM_97TYPE_ADDDATAREADBEGIN == 0x04)
                                memcpy(&CommExpDataBuff->Buffer[4], &(ucAlarmStatusLcdDisplay[0]), CON_ALARM_TYPE_BYTE_MAX);
                            else if(COMM_97TYPE_ADDDATAREADBEGIN == 0x05)
                                memcpy(&CommExpDataBuff->Buffer[4], &(ucAlarmStatusLcdError[0]), CON_ALARM_TYPE_BYTE_MAX);
                            else
                            {
                                ErrState=COMM_FAIL;
                            }
                        }
                        else
                        {
                            for(j=0;j<AddPara[i].dataLens;j++)
                            {
                                CommExpDataBuff->Buffer[4+j]=
                                SYSTEMPROGFUNCTION[(0x0000FFFF&AddPara[i].memoryAddress)+j];                                        
                            }               
                        }
                    }
                    CommExpDataBuff->Buffer[2]=AddPara[i].id&0xff;
                    CommExpDataBuff->Buffer[3]=(AddPara[i].id>>8)&0xff;  
                }
            }
            else if(0xBE00==uiID)
            {                   
                CommExpDataBuff->Buffer[2]=PROGFUNCTION_METER_FACTORY;                           
                ErrState=COMM_TURE;
            }
            else if(0xBE04==uiID)
            {                       
                CommExpDataBuff->Buffer[2]=PROGFUNCTION_METER_ADJUST;
                ErrState=COMM_TURE;
            }
            else 
            {
                if(0xBE02==uiID)
                {
                    ucDataLen=ReadHL645ADE7758_BE02_Data();
                    ErrState=COMM_TURE;
                }
                else 
                {
                    if((0x74D3==uiID)||(0x74C0==uiID)||(0x74C1==uiID)||(0x74C2==uiID)
                    ||(((uiID&0xFF00)==0x7400)&&(((uiID&0x00FF)>=0x00E0)&&((uiID&0x00FF)<=0x00EA))))   ////终端通信
                    {
                        //ErrState=ReadZhongDuanCommControl(&ucDataLen);
                        ErrState=COMM_FAIL;                      
                    }
                    else
                    {
                        ErrState=COMM_FAIL;
                    }
                }
            }

            if (ErrState==COMM_TURE)
            {
                ReturnBit=0x86;
                if((0xEE40==uiID)||(0xBE00==uiID)||(0xBE04==uiID)||(0xEE14==uiID))
                {
                    CommExpDataBuff->Buffer[0]=uiID&0xff;
                    CommExpDataBuff->Buffer[1]=(uiID>>8)&0xff;
                    if(0xEE40==uiID)
                        ucDataLen=AddPara[i].dataLens+4;  
                    else if((0xBE00==uiID)||(0xBE04==uiID))
                        ucDataLen=3;
                    else
                        ucDataLen=32+2;
                }
                else if((ucDataLen == 0) && (0xFE00==uiID))
                {
                    ReturnBit=0xC6;
                    CommExpDataBuff->Buffer[0]=0x02;  //无请求数据
                    ucDataLen = 1;
                }
                SetReturnDataFrame(ucDataLen,ReturnBit);
            }
            else
            {
                CommExpDataBuff->Buffer[0]=ErrState;
                ReturnBit=0xC6;
                SetReturnDataFrame(1,ReturnBit);
            }
            break;
            
        ///////远程拉合闸
        case 0x1C:
            if(AddrType!=COMMTYPE_STAEPARA_RIGHTADDR) 
                return;
            CommExpDataBuff->Buffer[0]=FarCutOrSortGateControl();
            if(CommExpDataBuff->Buffer[0]==0x00)
            {
                ReturnBit=0x9C;
                SetReturnDataFrame(0,ReturnBit);
            }
            else
            {
                ReturnBit=0xDC;
                SetReturnDataFrame(1,ReturnBit);
            }
            break;
            
        default:
            break;
    }
}
/////设置通信符号显示的标记
void SetCommDspFlag(uchar CommNo);
void SetCommDspFlag(uchar CommNo)
{ 
    switch(CommNo)
    {
        case SOURCE_IR:   ///远红外，1口
            ucCommFlgStatusChannel01=CON_COMMFLGSTATUS_SHOWTIME;
            SetKeyEvent(DISPLAY_EVENT_REMOTECOMM);
            break;
            
        case SOURCE_485:
            ucCommFlgStatusChannel03=CON_COMMFLGSTATUS_SHOWTIME;
            break;

        case SOURCE_COMM_SECOND:
#if(CONFIG_METER_NO2COMM_MODE_RS485==CONFIG_METER_NO2COMM_MODE)
            ucCommFlgStatusChannel04=CON_COMMFLGSTATUS_SHOWTIME;
#elif(CONFIG_METER_NO2COMM_MODE_PLC==CONFIG_METER_NO2COMM_MODE)
            ucCommFlgStatusChannel05=CON_COMMFLGSTATUS_SHOWTIME;
#elif(CONFIG_METER_NO2COMM_MODE_WIRELESS==CONFIG_METER_NO2COMM_MODE)
            ucCommFlgStatusChannel04=0x04;
            ModuleWirelessEventReset();
#endif
            break;

        default:
        break;
    }

}
///645通信控制主函数
void Rcomm645Control(void)
{
    uchar AddrType;
    uchar ExplainType;
    uchar ucControlNO;//,ucCommNo;
    uchar ucWithReturn=COMM_HAVE_NO_RETURN;
    u16 ulLenth=0;

    UartPotr.controlData=0;
    ucCommFormatType=COMMTYPE_ERR;
   //if(!GetCommunicateRecData(&CommExpReceiveDataBuffer))
    {
        ////初始化发送数据长度
        InitialOutPutCommDataLenth();
        ////////比较通信帧中表号
        AddrType=CheckCommAddr();
        if (AddrType!=COMMTYPE_STAEPARA_ADDR_ERR)  ///表地址没有错误,否则不做应答
        {
            ////依照控制码信息来区分规约类型(07,97)
            ucControlNO=GetComm645ControlNO(); 
            ulLenth=GetCommDataLen();
            /////通信显示符号置位
            isSpcecial_uart = 0xff;
            MTRACE("%s-%d\n", __FUNCTION__, __LINE__);  
			ExplainType=GetCommExplainType(ucControlNO);
            switch (ExplainType)
            {
                case COMMTYPE_07:
                        //MTRACE(stderr, "%s-%d\n", __FUNCTION__, __LINE__);  
                    ucCommFormatType=COMMTYPE_07;
                    ucWithReturn=Chose07CommControlType(AddrType);
                    break;
                case COMMTYPE_97:  ///调用97版的函数
                    ucCommFormatType=COMMTYPE_97;
                    break;
                case COMMTYPE_ALLCOMM:///万能
                    CommTypeAllControl(AddrType);  
                    ucWithReturn=COMM_HAVE_RETURN;                           
                    break;

                case COMMTYPE_ERR:     //控制码错误不做应答
                default:
                    break;
            }
        }                
        if (ucWithReturn==COMM_HAVE_RETURN)
        {
            ulLenth=GetOutPutCommDataLenth();
            //if(ucOutPutLenth!=0)//通信潜在问题修改 YXX
            {
                ////发送数据
                ulLenth = CommExpDataBuff->Head[COMM_HEAD_ADDR_LEN+2+COMM_HEAD_FE_NO-1]+COMM_HEAD_ADDR_LEN+2+COMM_HEAD_FE_NO+2;
                SendCommunicateData(CommExpDataBuff->Head,ulLenth,&CommExpReceiveDataBuffer.communicateFlag,&UartPotr);
				MTRACE("%s-%d\n", __FUNCTION__, __LINE__);  
            }
        }
        else
        {
            SendCommunicateData(CommExpDataBuff->Head,0,&CommExpReceiveDataBuffer.communicateFlag, &UartPotr);
        }
        CommExpDataBuff = (STR_RETURN_EXPLAINBUFFER*)&(CommExpReceiveDataBuffer.buff[0]);
    }
}
#endif

