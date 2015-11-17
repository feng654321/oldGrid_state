/*********************************************************************************
    �汾��     :version 0.1
    ģ����       : Զ�̿���ģ��
    �ļ���       : CommExplain.c
    ����ļ�     : 
    �ļ�ʵ�ֹ��� : ͨ��������ģ��
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
#ifndef __COMMEXPLAIN_C__
#define __COMMEXPLAIN_C__
#include "common.h"
#include "commexplain.h"
#include "ap_profunction.h"

/////ͨ��֡�б��
///������ַ
void GetCommFrameAddr(uchar * CommAddr);
///���ͨ�ŵ�ַ�Ƿ���ȷ,���� 00ʧ�ܣ�01:��ȷ��ַ,08:�㲥���03ͳ�����ʽ��ַ��04:ȫAA��ַ
uchar CheckCommAddr(void);
////ѡ��ͨ�ŵĹ�Լ���� 00 :07 , 01:97, 02........
////ͨ��������������ͨ�Ź�Լ������
////��Լ���͵Ļ��
///���:�������
uchar GetCommExplainType(uchar ControlNo);
uchar GetCommType(void);  ////���ͨ�Ź�Լ����

///ͨ����ÿ�������Ϣ���õ�ͨ�Ź�Լ�Ŀ���ģʽ
//�������ݵĵ�ַ�� ͨ�ŵ�ַ������
//����1  û�з������ݣ�����0  : �з�������
uchar  Chose07CommControlType(uchar  AddrType);
///���ݼ�33����
//void DecData33(uchar * Ptr,uchar Lenth);
///���ݼ�33����
void AddData33(uchar * Ptr,uchar Lenth);
void SubData33(uchar * Ptr,uchar Lenth);
////��ʼ��ͨ�Ÿ�֡����
void InitialCommExplainFrame(void);

////���ɼ�¼�Ķ���
//void CommReadLoadData (STR_READ_RETURN_PARA *Dest,ulong ID);
//////ͨ��ID ����ö�������
//���ص�ֵ�����λΪ0:�ɹ���1:ʧ�ܡ�
/// �ڶ���λΪ1��Ϊ�к���֡��0: �޺���
///������λ����4��λ�ա�������ֽ�λ��ʾ�������ݳ���
//���Ϊ��ȫ�ֱ�����
u16  GetDataByID(STR_READDATA_INPUT* Src);
////��ñ�ͨ�ŵ�ַ
void GetReadReturnDataAddr(uchar *Dest);
////���÷��͵�ͷΪ0xFE
void GetCommReturnDataFE(uchar *Dest);
////���ض����ݵ�ͷ(FE+68+��ַ+68+������+����)
void GetReadReturnDataHead(uchar *Dest,uchar ControlData,uchar DataLenth);

////��ÿ������
uchar GetComm645ControlNO(void);

////��ʼ���������ݵ��ܳ���
void InitialOutPutCommDataLenth(void);
///��÷������ݵ��ܳ���
uchar GetOutPutCommDataLenth(void);
///645ͨ�ſ���������
void Rcomm645Control(void);
/////����������
///��Ҫ��ú���֡�ĺ���ID,֡���,�Ƿ��к���,ͨ����
void CommControlReadLastData(void);
////�Ƚ�����Ȩ������
uchar ClearCmpPassword(uchar PasswordLevel,uchar *Dest);
////д����
//�Ƚ�����
//��¼�����ߴ���
//�����ñ��,
//���ÿ��ƺ���:(�ú�������������ҳ��ṩ)
void CommControlWriteData(void);
////��ͨ�ŵ�ַ
void CommReadAddr(void);
///дͨ�ŵ�ַ
void CommWriteAddr(void);

//����ͨ������
void CommChangeBaudRate(void);
//�޸�����
void CommChangePassword(void);
//�����������
void CommClearMD(void);
///�������
void CommClearEC(void);
///�¼�����
void CommClearEven(void);
////��������
void CommControlFeezeData(void);
////�պ���
void NULLFunction(void);
/////���ز����������ID
void NULLFunctionWithReturn(uchar *Dest,ulong ID);

void GetCommPassword(uchar* Dest,uchar Lenth);

void  CommTypeAllControl(uchar AddrType);

/////���ܺ���
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
    #define EPL_COEF_DATA_END 0x0500102C // 4 byte YYMMDDNN BCD ��һ�������������ڼ���ʱ�α��
    #define EPL_COEF_DATA_START 0x05000AA8 // 0 byte   ����������ʼ
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
                                                         
////�Ƚ�2�������ֵ�Ƿ����
uchar CommStrCmp(uchar *Dest,uchar *Src,u16 uiLthen)
{
    u16  i;
    for(i=0;i<uiLthen;i++)
    {
        if((*(Dest+i))!=(*(Src+i)))  return 1;
    }
    
    return 0;
}


////ͨ��֡�б��
////������ַ
void GetCommFrameAddr(uchar * CommAddr)
{
  memcpy(CommAddr,&COMM_RECEIVE_FRAME_ADDRSTART,COMM_METRER_ADDR_LENTH);
}
////��ñ�ͨ�ŵ�ַ
void GetReadReturnDataAddr(uchar *Dest)
{ 
  ReadDataDirect(RAM_USER_COMM_ADDR,COMM_METRER_ADDR_LENTH,Dest);
}
////���÷��͵�ͷΪ0xFE
void GetCommReturnDataFE(uchar *Dest)
{
    uchar i;
    for (i=0;i<COMM_HEAD_FE_NO;i++)
    {
        *(Dest+i)=0xFE;
    }
}


////���ض����ݵ�ͷ(FE+68+��ַ+68+������+����)
void GetReadReturnDataHead(uchar *Dest,uchar ControlData,uchar DataLenth)
{
     GetCommReturnDataFE(Dest);                         //����ǰ����0xfe
    *(Dest+COMM_HEAD_FE_NO)=FORMAT_FRAME_HEAD;          //�����һ��68
     GetReadReturnDataAddr(Dest+COMM_HEAD_FE_NO+1);     //����ͨѶ��ַ
    *(Dest+COMM_HEAD_FE_NO+7)=FORMAT_FRAME_HEAD;        //����ڶ���68
    *(Dest+COMM_HEAD_FE_NO+8)=ControlData;              //���������
    *(Dest+COMM_HEAD_FE_NO+9)=DataLenth;                //���������򳤶�
     ucOutPutLenth=COMM_HEAD_ADDR_LEN+2+COMM_HEAD_FE_NO;    //
}

///���ͨ�ŵ�ַ�Ƿ���ȷ,���� 00ʧ�ܣ�01:��ȷ��ַ,08:�㲥���03ͳ�����ʽ��ַ��04:ȫAA��ַ
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
    if( 1 == ucRet)  ///ȫAA��ַ
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
                
                if( 1 == ucRet)  ///ȫ99��ַ,�㲥��ַ
                {
                    return COMMTYPE_STAEPARA_BROADCAST_ADDR;
                }
                else
                {
                        ucRet = 1;
                        
                        ReadDataDirect(COMM_METERADDR,COMM_METRER_ADDR_LENTH,ucArrayReadAddress);
                                          
                        for(i=0;i<COMM_METRER_ADDR_LENTH;i++)
                        {
                            if (ucArrayReadAddress[i]!=ucArrayFrameAddress[i]) ///�����ַ
                            {
                                ucRet=0;
                                break;
                            }
                        }

                                           
                        if( 1 == ucRet)   ///��ȷ�ĵ�ַ
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

////���ͨ�ſ������͵�ָ��
u16 GetCommTypePtr(uchar ControlData)
{
    u16 i;
    u16 TableNum;
    TableNum=GetControlTableNum();//��ȡ��������ĳ���
    for (i=0;i<TableNum;i++)
    {
        if (ControlData==TableCommControl[i].ucControlDataID)
        {                       //�������ı��
                return i;
        }
    }
    return SWITCH_TABLE_ERR;
}

///ͨ����ÿ�������Ϣ���õ�ͨ�Ź�Լ�Ŀ���ģʽ
//�������ݵĵ�ַ�� ͨ�ŵ�ַ������
//����1  û�з������ݣ�����0  : �з�������
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

    ///��ÿ��ƺ���
    ucControlNO = GetComm645ControlNO();        //�õ�������
    uiTabPtr = GetCommTypePtr(ucControlNO);     //��ȡ�������ڿ��������е�λ��
    if(IfPowerStateOff() && (uiTabPtr!=SWITCH_TABLE_ERR))
    {                                           //���Ǵ����ϵ��Ҳ鵽���������ڵı���λ��
        uctemp = TableCommControl[uiTabPtr].ucControlDataID;//ȡ��ʱ�����룬��ʱ�����룬ֱ����ucControlNO��ʱ����������
        if(!((uctemp == COMMTYPE_READ)          //����ͨѶ������
            ||(uctemp == COMMTYPE_READWITHLAST) //
            ||(uctemp == COMMTYPE_READADDR)
            ||(uctemp == COMMTYPE_DISPLAY)))
        {                                           //���˶��Ŀ������⣬ͣ���£�����Ӧ����������
            //ͣ��ʱ��ֹ���ã�tzg
            return COMM_HAVE_NO_RETURN;
        }
    }
    if(uiTabPtr!=SWITCH_TABLE_ERR)      ////���в��ҵ���ͨ����
    {
        CommFunction=TableCommControl[uiTabPtr].CommFunction;   ///���ͨ�ŵĺ���
        ucCommStatePara=(TableCommControl[uiTabPtr].strCommControlPara.CommAddrType)&0x7F;////ͨ�ŵĿ��Ʋ���
        if ((ucCommStatePara & AddrType)!=0)      ///�����ֵĹ�����ͨ�ŵ�ַ��������ƥ���
        {
            /////ִ�к���(����д����������)
            CommFunction();             //ִ�б���еĺ���
            /////Զ�̿��������ҪӦ��
            if(gucFarCtlFlg==COMM_USE)   
                return COMM_HAVE_NO_RETURN;
            
            if (TableCommControl[uiTabPtr].strCommControlPara.CommReturnValue==COMMTYPE_STAEPARA_RETURN)
            {
                if((AddrType==COMMTYPE_STAEPARA_BROADCAST_ADDR) && (ucControlNO != COMMTYPE_ZB))  
                {
                    return COMM_HAVE_NO_RETURN; ////�㲥��ַ
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

///���ݼ�33����
void AddData33(uchar * Ptr,uchar Lenth)
{
    uchar i;
    for(i=0;i<Lenth;i++)
    {
        (* (Ptr+i))+=0x33;
    }
}
///���ݼ�33����
void SubData33(uchar * Ptr,uchar Lenth)
{
    uchar i;
    for(i=0;i<Lenth;i++)
    {
        (* (Ptr+i))-=0x33;
    }
}
///������õķ�����()
uchar GetSetFeeNumber(void)
{
  uchar TmpFeeNum;
  ReadDataDirect(RAM_COEF_PRICE_MAX_NUM,1,&TmpFeeNum);  //�����õķ�����
  TmpFeeNum = BCD_Byte(TmpFeeNum);                        //BCD��תHEX��
  if(TmpFeeNum>COMM_FEE_FEE_NUM)                        //���õķ�����������������
    TmpFeeNum = COMM_FEE_FEE_NUM;                       //���õķ�����������������
  
  return (TmpFeeNum);
}

// aa ��ȡ���������� aa
uchar GetSetLadderNumber(void)
{
  uchar TmpLadderNum;
  ReadDataDirect(RAM_COEF_STEP_NUM,1,&TmpLadderNum);    //�����õĽ�����
  TmpLadderNum=BCD_Byte(TmpLadderNum);                  //BCDתHEX
  
  return (TmpLadderNum);
}

////���645��Լ��ID(ע��,�ֽڸߵ�λ��˳��,��ͬ��Ƭ���п��ܲ�ͬ��Ҫ�޸�)
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
  return (ulID);            //��������ͨѶ��ʶ��
}


uchar GetCommDataLen(void)
{
    return (COMM_RECEIVE_FRAME_LENTH);          //����ͨѶ��������ĳ���
}

///////��ȡ
uchar GetCommReadLoadDataNum(void)
{
///////start  yaoxuxu      2009.08.20    
    return (COMM_LOADRECORD_READOUT_NO);        //���ض�����֡�����
///////end  yaoxuxu      2009.08.20    
}


void GetCommReadLoadDataTim(uchar * TimAddr)
{
    ;
}

/////���ͨ�Ŷ˿ںš�
uchar GetExplainCommNo(void)
{
    if(isSpcecial_uart >= 0xf)
        return (CommExpReceiveDataBuffer.communicateFlag.source);
    else
        return isSpcecial_uart;
}

////��ʼ��ͨ�Ÿ�֡����
void InitialCommExplainFrame(void)
{
    memset((uchar*)&LastFrameData, 0, sizeof(LastFrameData));
}

//////���㴮��1  UART1_CHANNEL�����к���֡����
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
//////���㴮��2  UART1_CHANNEL�����к���֡����
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

//////��ڶ�·�����к���֡����
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

//////�����⴮�ڵ����к���֡����
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

//////��ͨ�ſڵ����к���֡����
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

/////��ʼ������֡�����ж�Ӧͨ�Ŷ˿ں��е�����
///(Ҳ������չΪֻ�����ĳ��ͨ����ĳ��ID��������������е�����)
////�˷�����һ������,�����������ͨ����ͬʱ�������Ļ�,�����ͻᷢ��ӵ��,���ݻ��������.
//���������Ƭ.��һ�����:Aͨ��������,�����к�����ռ�������еĻ���.A��������.Bͨ��Ҳ��������,
///���Bһֱ�������ź���.
void InitialLastFrameBuffer(uchar CommNo)
{
  uchar Ptr;
  
  for(Ptr=0;Ptr<LAST_FRAME_NUM;Ptr++)
  {
      if (LastFrameData[Ptr].HeadPara.ucCommNo==CommNo)
      {                                     //û�б��˿�ռ�õĺ���֡������
          LastFrameData[Ptr].HeadPara.ucUsed=COMM_PARAMETER_NO_USED;
      }
  }
}


/////����ú���֡�е�����
////3���Ӻ��Զ����BUFFER������
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

////�Ѻ��������ݱ��������֡BUffer��.
///����֡�ǰ��տ�����������ÿ�鳤��Ϊ180�ֽ�,172��Buffer,8���ֽ��Ǹÿ����Ϣ,�ܹ���6��.
///////����֡�����Ķ���
///����֡����ռ亯��(����Ĳ���,���������,)
///����COMM_FAIL,��COMM_TURE
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
    
        
    memcpy(&LastFrameData[Ptr].HeadPara,&InPara,sizeof(STR_LASTFRAME_IN_PARA));///ͷ��Ϣ
        LastFrameData[Ptr].HeadPara.ucCommNo=ucCommNo;
    memcpy(&LastFrameData[Ptr].Buffer,Dest,LastFrameData[Ptr].HeadPara.ucFormatLen); ///��������
    ////3���Ӻ��Զ����BUFFER������
        CearLastFrameBuffer(ucCommNo);
        
    return COMM_TURE;
}

/////��ù���������Ŀ
u16 GetSetHolidayNum(void)
{
   u16 TmpFeeNum;
   uchar TmpBCD[2];
   ReadDataDirect(RAM_COEF_HOLIDAY_MAX_MUN,2,TmpBCD);   
   TmpFeeNum=BCD2_Word(TmpBCD);
   
   return (TmpFeeNum);
}


////���ѭ�Ը���
u16 GetSetCycleLcdNum(void)
{
  uchar TmpBCD;
  ReadDataDirect(RAM_COEF_AUTO_TURNPAGE_NUM,1,&TmpBCD); 
    TmpBCD=BCD_Byte(TmpBCD);
    
    return (TmpBCD);
}

////��ü��Ը���
u16 GetkeyCycleNum(void)
{
     uchar TmpBCD;
     ReadDataDirect(RAM_COEF_KEY_TURNPAGE_NUM,1,&TmpBCD);   
     TmpBCD=BCD_Byte(TmpBCD);
     
     return (TmpBCD);
}

////�����ʱ����
u16  GetFeeSeasonMaxNum(void)
{
    uchar TmpBCD;
    ReadDataDirect(RAM_COEF_SEASONTABLE_MAX_NUM,1,&TmpBCD); 
    TmpBCD=BCD_Byte(TmpBCD);
     
     return (TmpBCD);
}

////���ʱ�α����
u16  GetFeeDayTableMaxNum(void)
{
    uchar TmpBCD;
    ReadDataDirect(RAM_COEF_DAYTABLE_MAX_NUM,1,&TmpBCD);    
    TmpBCD=BCD_Byte(TmpBCD);
     
    return (TmpBCD);
    
}
////���ʱ�θ���
u16  GetFeeTouTableMaxNum(void)
{
    uchar TmpBCD;
    ReadDataDirect(RAM_COEF_PERIOD_MAX_NUM,1,&TmpBCD);  
    TmpBCD=BCD_Byte(TmpBCD);
    
    return (TmpBCD);
}


///������ȷ�ķ���֡��������ȫ�ֱ�����Լ���ͣ�
void SetReturnDataFrame(uchar DataLenth,uchar ControlData)
{
    uchar ucCommCS=0;
    
    GetReadReturnDataHead(CommExpDataBuff->Head, ControlData,DataLenth);//���ݿ����롢������ĳ��ȵ���������֡��֡ͷ
    AddData33(&CommExpDataBuff->Buffer[0],DataLenth);        //���������33����
    ucOutPutLenth += DataLenth;                             //������ȼ�����������ĳ���
    ucCommCS=CommCalChksum(&CommExpDataBuff->Head[COMM_HEAD_FE_NO],ucOutPutLenth-COMM_HEAD_FE_NO);//����У���У��
    CommExpDataBuff->Buffer[DataLenth]=ucCommCS;             //д��У���
    CommExpDataBuff->Buffer[DataLenth+1]=FORMAT_FRAME_END;   //д�������
    ucOutPutLenth+=2;             //���ͳ����ټ�2
}

////��ÿ������
uchar GetComm645ControlNO(void)
{
    return (COMM_RECEIVE_FRAME_CONTROLNO);
}
////��Լ���͵Ļ��(��ʼ����Լ���Ͳ���)
///���:�������
uchar GetCommExplainType(uchar ControlNo)
{
    ///�ֱ����07,97�Ŀ������,���2����û�еĻ��ͷ��ش���
    ///�ڴ˴���ʱʹ��07���Լ
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

////��ù�Լ����
uchar GetCommType(void)
{
  return (ucCommFormatType);
}

////��ʼ���������ݵ��ܳ���
void InitialOutPutCommDataLenth(void)
{
    ucOutPutLenth=0;
}

///��÷������ݵ��ܳ���
uchar GetOutPutCommDataLenth(void)
{
    return (ucOutPutLenth);
}

////������������֡���
uchar GetLastFrameNum(void);
uchar GetLastFrameNum(void)
{
    return (COMM_LAST_FRAME_NUM);
}
/////����������
///��Ҫ��ú���֡�ĺ���ID,֡���,�Ƿ��к���,ͨ����
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
        if(ucLenth!=0x05)   ///����
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
                if (Ptr>=LAST_FRAME_NUM)   ///����
                {
                    ucState=0;
                }
                else   ////��ȷ
                {
                        memcpy(&CommExpDataBuff->Buffer[0],&ulID,4);
                                                ulLenth+=4;
                                                if(ID3==0x06)    //////���ɼ�¼�ĺ���֡
                                                {
                                                   //////////////////////////
                                                    TmpLen=CommLoadLastFrameRead(Ptr,ulID,&CommExpDataBuff->Buffer[4]);
                                                    if(TmpLen&COMM_READ_RETURN_FRAME_FLAG)   ///���к���
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
                                                        
                                                        switch (ulID&0xFFFFFF00)    ////��������һЩ�洢��ʽ�������Ҫ�����
                                                        {
                                                                case 0x03300200:    ////���������¼�Ƚ��������Ҫת���ɹ�Լ�ĸ�ʽ
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
                                                        ////////����صĺ��������ͷŵ�
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
                                                        if (Ptr>=LAST_FRAME_NUM) ///�޺���֡
                                                        {
                                                                ucState=1;
                                                        }
                                                        else  ///�к���֡
                                                        {
                                                                ucState=2;
                                                        }
                                                }
                }
        }
        switch(ucState)
        {
            case 1:   ///�޺���֡
                SetReturnDataFrame(ulLenth,COMMTYPE_READWITHLAST|BIT7);
                break;
            case 2:   ///�к���
                SetReturnDataFrame(ulLenth,(COMMTYPE_READWITHLAST|BIT7)|BIT5);
                break;
            default:
                          CommExpDataBuff->Buffer[0]=BIT1;
                          SetReturnDataFrame(0x01,(COMMTYPE_READWITHLAST|BIT6)|BIT7);
                break;
        }
}


/////////////��ò����ߴ���/////////////////////////
void GetUseNumber(uchar *Dest,uchar Lenth)
{
    memcpy(Dest,&COMM_RECEIVE_WRITE_USEDID,Lenth);
}

/////�������
void GetCommPassword(uchar* Dest,uchar Lenth)
{
    memcpy(Dest,&COMM_RECEIVE_WRITE_PASSWORD,Lenth);
}


///��ð�ȫ��֤�� ��ʱ������ֵ
u16 GetSecurityTimData(uchar PasswordLevel);
u16 GetSecurityTimData(uchar PasswordLevel)
{
        u16  uiTmpBuffer;
        ReadDataDirect(RAM_PASSWORD_LOCK_TIME_START+PasswordLevel*2,2,(uchar*)&uiTmpBuffer);
        return (uiTmpBuffer);
}

///��ð�ȫ��֤�Ĵ�������Ĳ���ֵ
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

//���ð�ȫ��֤��������������ʱ��
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

///��ID��д�Ƚ�����Ȩ��
///����0����Ȩ�޲���,��������Ȩ�޲���
uchar CommCmpPassword(uchar PasswordLevel)
{
    uchar TmpBuffer[4];
        
    GetCommPassword(TmpBuffer,4);
    PasswordLevel=ClearCmpPassword(PasswordLevel,TmpBuffer);
    return PasswordLevel;
}

////���㲿�ֱȽ�����
///��Ҫ����Ȩ��,���������
///����0����Ȩ�޲���,��������Ȩ�޲���
uchar ClearCmpPassword(uchar PasswordLevel,uchar *Dest)
// ----PasswordLevel--��͵�����Ȩ��Ҫ��------
// ----Dest[0]==����֡�е�����Ȩ��-----
// ----Dest[1]Dest[2]Dest[3]==����֡�е���������-----
{
    uchar TmpBuffer[4];
    uchar UseBuffer[4];
    u16  uiTmp;
        
        
    memcpy(TmpBuffer,Dest,4);
// AA --�ж�Ȩ���Ƿ���ȷ-->Start--AA    
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
// AA --�ж�Ȩ���Ƿ���ȷ-->End--AA  
// AA --�ж�Ŀǰ�Ƿ񻹴�������ʱ��-->Start--AA
    uiTmp=GetSecurityTimData(TmpBuffer[0]);
    if(uiTmp>0)  return COMM_FAIL;
// AA --�ж�Ŀǰ�Ƿ񻹴�������ʱ��-->End--AA
        
    ReadDataDirect(EPL_PASSWORD_0+TmpBuffer[0]*4,4,UseBuffer);

// AA --�ж������Ƿ���ȷ--AA
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

////��ñ�̼���״̬
///1Ϊ���״̬,0Ϊ�Ǳ��״̬
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

////��ͨ�ŵ�ַ
void CommReadAddr(void)
{
  uchar ReturnBit=0x13;
  
  GetReadReturnDataAddr(CommExpDataBuff->Buffer);
  SetReturnDataFrame(6,(ReturnBit|BIT7));

}

///дͨ�ŵ�ַ
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
    /////��������Ļ�������Ϊ0
    ucOutPutLenth=0;
}


/////��ù㲥Уʱ����
uchar GetBroadCastType(void);
uchar GetBroadCastType(void)
{
    uchar ucBroadCast=0;
    
    ReadDataDirect(CFGDIR_MODE_BROADCAST_TIME,1,&ucBroadCast);
    
    return ucBroadCast;
}


///�㲥Уʱ
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
        /////5�����ڲ���Уʱ(300��)
        ///  ϵͳʱ����У׼��ʱ��
        SysTim=CalendarToSec(&TmpData);
        memcpy(&SetData.second,&COMM_BCAST_DATA_START,3);
        SetData.week=TmpData.week;
        memcpy(&SetData.day,&COMM_BCAST_DATA_START+3,3);
        PcTim=CalendarToSec(&SetData);
        sIntevTim=SysTim-PcTim;
        if((sIntevTim>300)||(sIntevTim<-300)) return;
        ///////������ҹУʱ,������23:55��00:05��Уʱ
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
            //////1��ֻ��Уʱ1��
            ucBroadCast=GetBroadCastType();
            ReadDataDirect(EPL_LAST_CHANNELS01_BROADCASTTIME,6,&LastData.minute);
            if(ucBroadCast==0x02)  ////������Ȼ��
            {
                /////ϵͳʱ��=�ϴ�Уʱʱ��Ļ����ͷ���,�����
                SysTim=CalendarToDay(&TmpData);
                PcTim=CalendarToDay(&LastData);
                if(PcTim==SysTim)  return;
            }
            else    ////����24Сʱ
            {
                /////ϵͳʱ��-�ϴ�Уʱʱ��>24,�ͷ���,����
                SysTim=CalendarToMin(&TmpData);
                PcTim=CalendarToMin(&LastData);

                sIntevTim=SysTim-PcTim;
                if(sIntevTim<1440)  return;         
            }
        }
        //////Уʱ
        SetRealTime(&SetData);
        ////�ϴ�У׼ʱ��д��洢��
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
        /////5�����ڲ���Уʱ(300��)
        ///  ϵͳʱ����У׼��ʱ��
        SysTim=CalendarToSec(&TmpData);
        memcpy(&SetData.second,&COMM_BCAST_DATA_START+4,3);
        SetData.week=TmpData.week;
        memcpy(&SetData.day,&COMM_BCAST_DATA_START+3+4,3);
        PcTim=CalendarToSec(&SetData);
        sIntevTim=SysTim-PcTim;
        if((sIntevTim>600)||(sIntevTim<-600)) return;
        ///////������ҹУʱ,������23:50��00:10��Уʱ
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
            //////1��ֻ��Уʱ1��
            ucBroadCast=GetBroadCastType();
            ReadDataDirect(EPL_LAST_CHANNELS02_BROADCASTTIME,6,&LastData.minute);
            if(ucBroadCast==0x02)  ////������Ȼ��
            {
                /////ϵͳʱ��=�ϴ�Уʱʱ��Ļ����ͷ���,�����
                SysTim=GetGmDay(&TmpData);
                PcTim=GetGmDay(&LastData);
                if(PcTim==SysTim)  return;
            }
            else    ////����24Сʱ
            {
                /////ϵͳʱ��-�ϴ�Уʱʱ��>24,�ͷ���,����
                SysTim=GetGmMin(&TmpData);
                PcTim=GetGmMin(&LastData);

                sIntevTim=SysTim-PcTim;
                if(sIntevTim<1440)  return;         
            }
        }
        //////Уʱ
        SetRealTime(&SetData);
        ////�ϴ�У׼ʱ��д��洢��
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


/////��������״̬����Ҫ���õ�����
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


/////��ô���״̬
////���ڲ���,״̬��
uchar GetCommBautType(UARTMODE * Mode,uchar WordType,uchar CommNormberType)
{
    uchar returnFlag=0;
    switch(WordType&0xFF)
  {
            case BIT1:
                            //------------------------yaoxuxu  2009.11.08   start------
                                if(CommNormberType==0x01) return 0;   //����
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

//����ͨ������
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
        TmpID0=0x01;    ///����
    //------------------------yaoxuxu  2009.11.08   end------
    if (ucFlag==COMM_TURE)
    {
        if (GetCommBautType(&UartPotr.uartPara,ucBautWord,TmpID0)!=0)
        {
            ucFlag=COMM_TURE;
            switch (ucCommNo)
            {
                case SOURCE_IR:   ///����
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

//�޸�����
void CommChangePassword(void)
{
    uchar ReturnBit=0x18;
    ulong ulID;
    uchar ID0,ucPasLevel,ReturnLenth;
    uchar UseState=COMM_FAIL;
    
    /////��̼��Ƿ�ʹ��
  if (GetTheProgramKeyState()==COMM_TURE) 
  {
        ////�Ƚ�ID�Ƿ���Ч
        ulID=GetCommReadData645ID(ucCommFormatType);
        if ((ulID>=0x04000C01)&&(ulID<=0x04000C0A))
        {
             UseState=CommWriteBcdFormat(&COMM_RECEIVE_WRITE_PASSWORD,8,&ReturnLenth);
             if (UseState==COMM_TURE)
             {
                     ////�Ƚϲ��������Ƿ���ȷ
                     ID0=(uchar)ulID;
                     if(ID0==(COMM_RECEIVE_WRITE_FARME_PASSWORD+1))
                     {
                                ////�Ƚ�Ҫ�޸ĵ������Ƿ���Ȩ�ޱ��޸�
                                ucPasLevel=CommCmpPassword(COMM_RECEIVE_WRITE_FARME_PASSWORD);
                                if(ucPasLevel==COMM_TURE)
                                {
                                        if (COMM_RECEIVE_WRITE_PASSWORD<=COMM_RECEIVE_WRITE_FARME_PASSWORD)
                                        {
                                            ///�޸�����
                                             WriteCoefDataWithSync(&COMM_RECEIVE_WRITE_FARME_PASSWORD,EPL_PASSWORD_0+COMM_RECEIVE_WRITE_FARME_PASSWORD*4,4);
                                             ClrSecurityCount_timeData(COMM_RECEIVE_WRITE_FARME_PASSWORD);
                                             UseState=COMM_TURE;
                                        }
                                        else  ///��Ȩ����
                                        {
                                            UseState=COMM_FAIL;
                                        }   
                                }
                                else   ////��Ȩ����
                                {
                                    UseState=COMM_FAIL;
                                }
                     }
                     else  ////����
                     {
                            UseState=COMM_FAIL;
                     }
                }
                else  {UseState=2;}
                    
        }
        else ////����
        {
                UseState=COMM_FAIL;
        }
  }
  else   ///��Ȩ��
  {
      UseState=COMM_FAIL;
  }
  
  if(UseState==COMM_TURE)  ////�޸���ȷ����֡
  {
        memcpy(CommExpDataBuff->Buffer,&COMM_RECEIVE_WRITE_FARME_PASSWORD,4);
        SetReturnDataFrame(4,ReturnBit|BIT7);
  }
  else    /////�޸Ĵ��󷵻�֡
  {
      if (UseState==2)   ////BCD����
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

//�����������
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
          
   /////��̼��Ƿ�ʹ��
  if (GetTheProgramKeyState()==COMM_TURE) 
  {
        UseState=ClearCmpPassword(COMM_PASSWORD_POPEDOM_4,&COMM_RECEIVE_CLEAR_PASSWORD);
        if (UseState==COMM_TURE)
        {
                UseState=CWBFMaxDemandClr();
                if (UseState==1)
                {
                                  UseState=COMM_TURE;
                      ////���ü�¼������������¼��ĺ���
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
        // --aa 01��ʽ��645-07��ʽaa--
//      if(0x01==COMM_BCAST_DATA_START)
        {
            SetCommDisplayDI (&COMM_BCAST_DATA_START);
        }
    }
}

///�������
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
        /////��̼��Ƿ�ʹ��
        if (GetTheProgramKeyState()==COMM_TURE) 
        {
            if (COMM_TURE == ClearCmpPassword(COMM_PASSWORD_POPEDOM_2,&COMM_RECEIVE_CLEAR_PASSWORD))
            {
                UseState=CWBFMeterAllClr();
                if (UseState==1)
                {
                    UseState=COMM_TURE;
                    ////���ü�¼������������¼��ĺ���
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
             ////���ü�¼������������¼��ĺ���
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
**��������: void CommMultiPort(void)
**����: none
**���: none
**˵��: �๦�ܿ�������������,�����̼�,֧�ֹ㲥��ַ����
** ȫ�ֱ���:
** ����ģ��:
**------------------------------------------------------------------------------------------------------
** ������: zlq
** �ա���: 2009��10��12��
********************************************************************************************************/
void CommMultiPort(void)
{
    uchar ReturnBit=0x1D;

    if(COMM_MULTIPORT_DATA <= 2)
    {
        WriteCoefDataWithSync(&COMM_MULTIPORT_DATA,EPL_COEF_PULSEMODE,1);  //�ϵ�����������Ҫ����
        CommExpDataBuff->Buffer[0] = COMM_MULTIPORT_DATA;
        SetReturnDataFrame(1,(ReturnBit|BIT7));
        return;
    }

    /////��������Ļ�������Ϊ0
    ucOutPutLenth=0;
}

/*********************************************************************************************************
**��������: void CommControlZB(void)
**����: none
**���: none
**˵��: �ز�ͨ��,��ַ����
** ȫ�ֱ���:
** ����ģ��:
**------------------------------------------------------------------------------------------------------
** ������: zlq
** �ա���: 2009��11��20��
********************************************************************************************************/
void CommControlZB(void)
{
    uchar ReturnBit=0x1F;


    CommExpDataBuff->Buffer[0] = 0xAF;//-0x33;
    CommExpDataBuff->Buffer[1] = 0x02;//0x100 + 0x02 - 0x33;
    ReadDataDirect(COMM_METERADDR,COMM_METRER_ADDR_LENTH,(CommExpDataBuff->Buffer+2));
    SetReturnDataFrame(8,(ReturnBit|BIT7));

    /////��������Ļ�������Ϊ0
    //ucOutPutLenth=0;
}

///�¼�����
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
        
   /////��̼��Ƿ�ʹ��
  if (GetTheProgramKeyState()==COMM_TURE) 
  {
        
                UseState=ClearCmpPassword(COMM_PASSWORD_POPEDOM_2,&COMM_RECEIVE_CLEAR_PASSWORD);
        if (UseState==COMM_TURE)
        {
                  /////////////////////��ID��Ч�Ե��ж�
            memcpy(&ulID,&COMM_EVEN_CLEAR_DATA,4);
            {
                UseState=CWBFEventDataClr(ulID);
                if (UseState==1)
                {
                    UseState=COMM_TURE;
                    ////���ü�¼�¼����������¼��ĺ���
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
                                            /////���ͨ�ſ�
                                            strReadDataIn.CommNum=GetExplainCommNo();
                                            // strReadDataIn.ulID=TmpID;
                                            // InitialLastFrameBuffer(strReadDataIn.CommNum);  ///�����֡BUFFER����Ӧ�˿��е�����
                                            //////��ö���������
                                            // ucReturnFramePara=GetDataByID(&strReadDataIn);
                                            // InitialLastFrameBuffer(strReadDataIn.CommNum);  ///�����֡BUFFER����Ӧ�˿��е�����
                                         }
                                       
                                          if ((ucReturnFramePara&COMM_RETURN_STATE_FAIL)!=0)  {UseState=COMM_FAIL;}  ////����Ӧ��
                                          else
                                          {
                                              UseState=CWBFEventDataClr(ulID);
                                              if (UseState==1)
                                              {
                                                  UseState=COMM_TURE;
                                           ////���ü�¼�¼����������¼��ĺ���
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

////��������
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
             //////���ö��ắ��
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

////�պ���
void NULLFunction(void)
{
    ;
}

/////���ز����������ID
void NULLFunctionWithReturn(uchar *Dest,ulong ID)
{
    ;
}
////������ֵ�Ŀպ���
uchar NULLReturnValue(void)
{
    return 1;
}


//////ADE7758�ĵ���(��)
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
////ADE7758�ĵ���(д)
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

/////���ܶ�����
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
/////����д����
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

///////Զ������բ����
///���ص�0Ϊ��ȷ�������Ϊ����״̬��
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
    ////Ҫ�޶�Ψһ��ͨ��
  strRecordData.CommNo=GetExplainCommNo();
     
  strRecordData.CommType=GetCommType();
  
  if(uiTmp==0xAA11)  //��բ
  {
    strRecordData.EvenType=PROGRAM_RECORD_RELAY_OFF;
  }
  else
  {
      if (uiTmp==0xEE11)  //��բ
      {
        strRecordData.EvenType= PROGRAM_RECORD_RELAY_ON;
      }
      else
      {
          ucState=BIT1;
          return ucState;
      }
  }
  ///��¼�±���¼�
  EvenProgramRecord(strRecordData,&COMM_RECEIVE_STCTGATE_CONTROLID,ReturnLenth);
  ////ִ������բ����
  ucState=CWBFRelayCommand(&COMM_RECEIVE_STCTGATE_USERID);
  if(ucState==1)  {return 0;}
  else  ///û����բ�ɹ�
  {
    ucState=BIT0;
  }
  return ucState;
}


///////���ܶ�д���ƺ���
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
        case 0x05:    ///����д
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
                    // ��������
                    // �˴����������¼������������¼�����ʶ,��ProgramEventMode()��ִ������
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
                            //���������ڲ���������������ϵ��ʼ��ʱĬ�Ͻ���У��״̬��
                            //�������������ڿ�����ʱ�ı�У��״̬
                            //�ڹ���ģʽ�£���������˳�У��ģʽ
                            if(PROGFUNCTION_METER_FACTORY == METER_IN_FACTORY)
                            {
                                PROGFUNCTION_METER_ADJUST=ucData;
                                ucData=ucData+0x33;
                                WriteProgramData(&PROGFUNCTION_METER_ADJUST, (EPL_DATA_PROGRAM_START+(0x0000FFFF & CFGDIR_METER_ADJUST_ENABLE)), 1);
                                ErrState=COMM_TURE; 
                            }
                            else 
#endif                            
                            //���������ڲ�����������������ֹ����У��״̬��
                            {
                                ErrState=COMM_FAIL; 
                            }
                        }
                        else if(0xBE00==uiID)
                        {
                            // --aa ��������˳�����ģʽaa--
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
                                // �˳�����ģʽ�󣬱���Զ��˳�У��ģʽ
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
                            // ��������ֻ�����ڳ���ģʽ�¿ɶ���д
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
                            {   // ʹ��Ĭ�ϲ���
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
                //if(ErrState==1)   ///Ȩ��
                CommExpDataBuff->Buffer[0]=ErrState;
                ReturnBit=0xC5;
                SetReturnDataFrame(1,ReturnBit);
            }
            break;

        case 0x06:   ////���ܶ�
            if(0xFE00==uiID)
            {
                ucDataLen=ReadHL645KZ_FE00_Data();
                ErrState=COMM_TURE;
            }
            else if(0xEE14==uiID)//����汾��
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
                    ||(((uiID&0xFF00)==0x7400)&&(((uiID&0x00FF)>=0x00E0)&&((uiID&0x00FF)<=0x00EA))))   ////�ն�ͨ��
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
                    CommExpDataBuff->Buffer[0]=0x02;  //����������
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
            
        ///////Զ������բ
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
/////����ͨ�ŷ�����ʾ�ı��
void SetCommDspFlag(uchar CommNo);
void SetCommDspFlag(uchar CommNo)
{ 
    switch(CommNo)
    {
        case SOURCE_IR:   ///Զ���⣬1��
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
///645ͨ�ſ���������
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
        ////��ʼ���������ݳ���
        InitialOutPutCommDataLenth();
        ////////�Ƚ�ͨ��֡�б��
        AddrType=CheckCommAddr();
        if (AddrType!=COMMTYPE_STAEPARA_ADDR_ERR)  ///���ַû�д���,������Ӧ��
        {
            ////���տ�������Ϣ�����ֹ�Լ����(07,97)
            ucControlNO=GetComm645ControlNO(); 
            ulLenth=GetCommDataLen();
            /////ͨ����ʾ������λ
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
                case COMMTYPE_97:  ///����97��ĺ���
                    ucCommFormatType=COMMTYPE_97;
                    break;
                case COMMTYPE_ALLCOMM:///����
                    CommTypeAllControl(AddrType);  
                    ucWithReturn=COMM_HAVE_RETURN;                           
                    break;

                case COMMTYPE_ERR:     //�����������Ӧ��
                default:
                    break;
            }
        }                
        if (ucWithReturn==COMM_HAVE_RETURN)
        {
            ulLenth=GetOutPutCommDataLenth();
            //if(ucOutPutLenth!=0)//ͨ��Ǳ�������޸� YXX
            {
                ////��������
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

