#ifndef __COMMEXPLAIN_H__
#define __COMMEXPLAIN_H__

#define COMMEXPLAIN_EXT             extern
#undef COMMON_EXT
#ifdef __COMMEXPLAIN_C__
#define COMMON_EXT
#else
#define COMMON_EXT  extern
#endif

#define METER_TYPE_THERRPHASE       0     ///������
#define METER_TYPE_THERRPHASE_MORE       1   ///�๦��

#define COMM_METER_TYPE     METER_TYPE_THERRPHASE_MORE 
#define NOACT   (2)

////�������븴�������������
#if (COMM_METER_TYPE ==METER_TYPE_THERRPHASE)        //������

#elif(COMM_METER_TYPE ==METER_TYPE_THERRPHASE_MORE)  ///��������(�๦��)

                #define COMM_CONST                              const
        
        #define COMM_READ_EC_LENTH                  5    ///��ҳ�4�ֽ�,����5�ֽ�
        #define COMM_READ_EC_FEE_MAXSIZE    ((DLT_PRICE_NUM_MAX)+(1))    ///�������ݿ��е������Ŀ��(������)    // ����4���ʷ���
        #define COMM_READ_EC_BLOCK_CHECK        0           ///�������ݿ��е�У���ֽ���
        
        #define COMM_READ_MD_LENTH              4      ///��ҳ�4�ֽ�,����5�ֽ�
        #define COMM_READ_MD_TIME_LENTH         5      ///��ҳ�4�ֽ�,����5�ֽ�
        #define COMM_READ_MD_ID_LENTH           (COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH)
        
        #define COMM_READ_MD_FEE_MAXSIZE    ((DLT_PRICE_NUM_MAX)+(1))       ///�������ݿ��е������Ŀ��(������)
        #define COMM_READ_FREEZE_FEE_MAXSIZE            COMM_READ_EC_FEE_MAXSIZE    ///����������ʸ���
        #define COMM_READ_FREEZE_VARIABLE_LENTH         3    ///����ı��������ֽڵĳ���
        #define COMM_READ_FREEZE_VARIABLE_MAXSIZE       8       ////����ı��������ֽڵĸ���
        #define COMM_READ_FREEZE_RECORDTIM                  12   ///�����¼�Ĵ���
        
        //#define COMM_READ_EC_GETTWOTABLE_ADDRERR           GAL_GETTWOTABLE_ADDRERR   ///����
        #define COMM_READ_EC_GETTWOTABLE_ADDRERR           0xFFFFFFFF
        
        #define COMM_METERADDR                      RAM_USER_COMM_ADDR
        #define COMM_EC_HISTORYDATA_START_ADDR                          TYPE_HISTROY_POWER_RECORD ////������ʼ������ʼ
        #define COMM_MD_HISTORYDATA_START_ADDR                          TYPE_HISTROY_DEMAND_RECORD ////������ʼ������ʼ
        
        #define COMM_FEE_SEASON_NUM                                         OCT_TO_HEX(DLT_SEASON_TABLE_MAX)     ////��ʱ����
        #define COMM_FEE_DAYTABLE_NUM                                       OCT_TO_HEX(DLT_DAY_TABLE_MAX)     ////��ʱ�α���
        #define COMM_FEE_DAYTOU_NUM                                         OCT_TO_HEX(DLT_DAY_PIECE_MAX)    ////��ʱ����
        #define COMM_FEE_FEE_NUM                                            OCT_TO_HEX(DLT_PRICE_NUM_MAX)   ////������
        #define COMM_FEE_HOLIDAY_NUM                                        (DLT_HOLIDAY_NUM_MAX)  ////����������Ŀ
        
        #define COMM_DSP_EC_DOT_MAX                                         0x04   ////����С�������λ��
    //  #define COMM_DSP_EC_INTER_MAX                                       0x08   ////�������������λ��
        #define COMM_DSP_MD_DOT_MAX                                         0x04   ////������С������Сλ��
    
        #define COMM_COMMTYPE_NUM                                               4    ////ͨ���ŵ�����
          
                #define COMM_EVEN_RECORD_NUM                                                                              10
              
#endif


#define BIT0        0x01
#define BIT1        0x02
#define BIT2        0x04
#define BIT3        0x08
#define BIT4        0x10
#define BIT5        0x20
#define BIT6        0x40
#define BIT7        0x80

/////����ģʽ
#define HISTORY_TEST            1      ///��ʷ�Ƿ�ʹ��   
#define COMM_TEST                       0     ////����ģʽ   
////���ش�����Ϣ
#define COMM_RETURN_ERR_STATE     BIT1     ///����������
#define COMM_READ_EC_FORMAT_LENTH   4   ///��Լ�еĵ����ֽڸ���

#define COMM_READ_MD_FORMAT_LENTH                       3      ///��Լ�е������������
#define COMM_READ_MD_TIME_FORMAT_LENTH          5      ///��Լ�е������ʱ��

#define COMM_READ_FREEZE_VARIABLE_FORMATLENTH           3    ///��Լ�ж���ı��������ֽڵĳ���
#define COMM_READ_FREEZE_VARIABLE_FORMATMAXSIZE     8       ////��Լ�еı��������ֽڵĸ���


#define COMM_READ_EC_PHASE_WITHCOMBINACTIVE     0   ////��������й����Ƿ���� 0:��,1,��
#define COMM_READ_EC_HISTORY                    12       ///��ʷ����Ϊ12��
#define COMM_READ_MD_HISTORY                    12      ///��ʷ����Ϊ12��

#define COMM_READ_EC_FORMAT_MAXID     0x0C     ///����DI2������ID

#define COMM_READ_RETURN_FRAME_FLAG         0x4000   ////����֡�ı��

/////645��׼��ͷ,β,����
#define FORMAT_FRAME_HEAD               0x68
#define FORMAT_FRAME_END                0x16


#define COMM_BUFFERSIZE      300         /////����Ǹ��ɼ�¼�Ļ��ͱ���Ҫ300���ֽ����ϣ�����250���ֽھ��㹻��
#define COMM_READMAXSIZE         192    ///���Ķ�������


#define COMM_TURE        0
#define COMM_FAIL        1


#define COMM_SEASON_NUM_OVER     3     ////��ʱ����
#define COMM_DAYTABLE_NUM_OVER     4   ////ʱ������
//#define COMM_DAYTOU_NUM_OVER      5
#define COMM_FEE_NUM_OVER         5    ////��������
#define COMM_HAVE_NO                    8      ///û�и���

#define COMM_CHANGE_BAD_ERR         9     ///ͨ�Ų����ʲ��ܸ���

#define COMM_USE                    1
#define COMM_NOUSE              0

////���͵�ͷΪFE���ֽڸ���
#define COMM_HEAD_FE_NO      4
#define COMM_HEAD_ADDR_LEN  8  ///��ַ����֡ͷβ�ĳ���

typedef struct
{
    uchar Head[COMM_HEAD_ADDR_LEN+2+COMM_HEAD_FE_NO];  ///FE+ͷ+��ַ+ͷ+������+����
    uchar Buffer[COMM_BUFFERSIZE];      ////��������
}STR_RETURN_EXPLAINBUFFER;

typedef struct
{
    u16 Lenth:12;
    u16 More:2;    ////���ʧ��,00:��ʾ�޸���,01:��ʾ����Ȩ
    u16 LastFrame:1;       ////0�޺���,1�к���
    u16 ReturnFail:1;     ////0,�ɹ�,1ʧ�� 
}STR_RETURN_PARA;
/////�������ز���
typedef union
{
        u16 uiReturnData;
        STR_RETURN_PARA  strReturnData; 
}STR_READ_RETURN_PARA;


typedef  void  (*WReturnFUNCTION)(STR_READ_RETURN_PARA * Dest,ulong ID);
typedef  uchar (*WithReturnFUNCTION)(void);
//////����Ĳ���:���ݵ�ַ,���ݵĳ���,�������ݵĳ���
///��������
typedef  uchar (*CheckFunction)(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);



extern void NULLFunction(void);
extern void NULLFunctionWithReturn(uchar *Dest,ulong ID);
///////////////////////////////////////////////////////////////
typedef struct
{
    
    uchar CommReturnValue:1;
    uchar CommAddrType:7;  
    
}STR_COMMTYPE_STAEPARA;

////ͨ�ſ��ƺ�����
typedef struct
{
    uchar ucControlDataID;  ///������
    PEFUNCTION   CommFunction;       ///�ÿ������Ӧ�ĺ���
    STR_COMMTYPE_STAEPARA   strCommControlPara;    ////�����ÿ��ƺ�����һϵ�в���
}STR_TAB_CMMCONTROL;


/////��������Ҫ����Ĳ���
typedef struct
{
    ulong ulID;                 ////����ID
    uchar ucFrameNum;           ///֡���
    uchar ucLoadBlockNum;       ////���ɼ�¼����
    uchar BCDLoadTim[6];       ///���ɼ�¼��ʼʱ��
    uchar CommNum;      ////ͨ�Ŷ˿ں�
}STR_READDATA_INPUT;


/////����֡Buffer���ݵĶ���
#define LAST_FRAME_MAXSIZE              10
#define LAST_FRAME_BLOCKSIZE            192   ////����̶���С
#define LAST_FRAME_NUM                      18   ////�������


////�������֡����ĺ����еĲ����ṹ
typedef struct
{
    uchar   ucCommNo;    ////ͨ��ͨ����
    uchar   ucFrameNo;   ////����֡��
    uchar   ucFormatLen;  ///����ʹ�õĳ���
    uchar   ucUsed;     ///�Ƿ�ʹ��,00,û��,01ռ��.
    ulong   ulID;               ////ID
}STR_LASTFRAME_IN_PARA;

typedef struct
{
    STR_LASTFRAME_IN_PARA  HeadPara;   ////�����ͷ�ļ�����
    uchar   Buffer[LAST_FRAME_BLOCKSIZE];   ///����
}STR_READ_LASTFRAME;


////����֡����Ҫ��������ݽṹ:������֡���ж�,�ж������Ҫ�޸ĵ�
typedef struct
{
    uchar   ucCommNo;    ////ͨ��ͨ����
    uchar   ucHaveLast;    ///0 û�к���,1 �к���
    ulong   ulLastID;          ////����ID
    uchar   LastFrameNo;    ///֡���
}STR_LASTFRAME_Control_PARA;


#define  COMM_HAVE_RETURN        1
#define  COMM_HAVE_NO_RETURN        0

#define  SWITCH_TABLE_ERR          0xFFFF
#define TAB_CMMCONTROL_NUM       2        /////��Ԫ���ĸ���(��ʱʹ��2��������չ)

////07 
#define COMMTYPE_07                     0x00             ///                    
#define COMMTYPE_ALLCOMM                0x03 

#define COMMTYPE_READ                   0x11        //������
#define COMMTYPE_READWITHLAST           0x12        //������֡
#define COMMTYPE_WRITEDATA              0x14        //д����
#define COMMTYPE_READADDR               0x13        //��ͨѶ��ַ
#define COMMTYPE_WRITEADDR              0x15        //дͨѶ��ַ
#define COMMTYPE_BROADCAST              0x08        //�㲥Уʱ
#define COMMTYPE_FEEZEDATA              0x16        //��������ָ��
#define COMMTYPE_CHANGEBAUDRATE         0x17        //����ͨѶ����
#define COMMTYPE_CHANGEPASSWORD         0x18        //��������
#define COMMTYPE_CLEARMD                0x19        //������
#define COMMTYPE_CLEAREC                0X1A        //�����0
#define COMMTYPE_CLEAREVEN              0X1B        //�¼���0
#define COMMTYPE_RELAYSET               0X1C        //�̵�������
#define COMMTYPE_MULTIPORT              0x1D        //�๦�ܿ�����

#define COMMTYPE_FARCTL                 0x03
#define COMMTYPE_DISPLAY                0x07        //��ʾ��ѯ
#define COMMTYPE_DLTDATA                0x09        //���ݲ�ѯ
#define COMMTYPE_ZB                     0x1F

///97
#define COMMTYPE_97                     0x01

//
#define COMMTYPE_ERR                        0xFF

//#define COMMTYPE_STAEPARA_RETURN      1
////STR_COMMTYPE_STAEPARA  �����еĶ������λ�����Ƿ��з���ֵ��
////��1 λ��ʾʹ����ȷ�ı��ַ��
///��2 λ��ʾ����ʹ����ȷ��ͳ���ַ(AA)��
///��3 λ��ʾ����ʹ����ȷ��ȫ��ͳ���ַ(AA)��
///��4 λ��ʾ����ʹ����ȷ�Ĺ㲥��ַ(99)��
///��8λ��ʾ�Ƿ��з���֡
#define COMMTYPE_STAEPARA_RIGHTADDR   0x01
#define COMMTYPE_STAEPARA_AA_ADDR      0x02
#define COMMTYPE_STAEPARA_ALLAA_ADDR     0x04
#define COMMTYPE_STAEPARA_BROADCAST_ADDR  0x08

#define COMMTYPE_STAEPARA_RETURN      0x01
#define COMMTYPE_STAEPARA_ADDR_ERR      0X00

//////������֡�ĳ���
#define COMM_READ_LENTH_NORMAL     0X04     //һ��Ķ�д
#define COMM_READ_LENTH_LOADNUM    0X05     //�����ɼ�¼�ĺ���֡
#define COMM_READ_LENTH_LOADTIM    0X0A     //�����ɼ�¼������֡�а�����¼��ʼʱ��

//////���������ͷ���
#define COMM_READ_TYPE_EC     0X00
#define COMM_READ_TYPE_MD     0X01
#define COMM_READ_TYPE_VARIANLE     0X02
#define COMM_READ_TYPE_EVEN     0X03
#define COMM_READ_TYPE_PARA     0X04
#define COMM_READ_TYPE_FREEZE     0X05
#define COMM_READ_TYPE_LOAD     0X06

#define COMM_READ_TYPE_ZEROFEEZE  0X08

#define COMM_READ_TYPE_LOSS_VOLTAGE         0X10
#define COMM_READ_TYPE_DOWN_VOLTAGE     0X11
#define COMM_READ_TYPE_OVER_VOLTAGE         0X12
#define COMM_READ_TYPE_CUT_VOLTAGE      0X13
#define COMM_READ_TYPE_ORDER_VOLTAGE    0X14
#define COMM_READ_TYPE_ORDER_CURRENT    0X15
#define COMM_READ_TYPE_UNBALANCE_VOLTAGE    0X16
#define COMM_READ_TYPE_UNBALANCE_CURRENT    0X17
#define COMM_READ_TYPE_LOSS_CURRENT     0X18
#define COMM_READ_TYPE_OVER_CURRENT     0X19
#define COMM_READ_TYPE_CUT_CURRENT      0X1A
#define COMM_READ_TYPE_REVERSEPOWER     0X1B
#define COMM_READ_TYPE_POWEROVER        0X1C
#define COMM_READ_TYPE_RELAY_OPEN       0X1D
#define COMM_READ_TYPE_RELAY_CLOSE      0X1E
#define COMM_READ_TYPE_OVERTOTALCOS     0X1F




////////////////////////////////////////////////////////////////////////////////
#define COMM_RETURN_STATE_FAIL    0x8000
#define COMM_RETURN_STATE_WITHLAST    0x4000
#define COMM_RETURN_FAIL_NO_ACCREDIT        0x1000  ///���ص�������Ȩ��
#define COMM_RETURN_STATE_DATA_LENTH  0X0FFF


///////////////////////�¼�//////////////////////////////////////////
///�¼��Ĵ���
#define COMM_EVEN_BLOCK_FAILURE                 0x00         ///�������¼�
#define COMM_EVEN_BLOCK_VOLTAGE_CHECKOUT  0X01     ///��ѹ�ϸ����¼�
#define COMM_EVEN_BLOCK_MD_OVER                     0x02     ///����������
#define COMM_EVEN_BLOCK_METER_HANDLE      0x03     ////��������   
#define COMM_EVEN_BLOCK_METER_CUTGATE   0x04    ///����բ�¼���
#define COMM_EVEN_BLOCK_CARD           0x05     ////���������


////�������¼�
#define COMM_EVEN_FAILURE_RECORD_TIM                    10              ////��¼����    

#define COMM_EVEN_TYPE_VOLTAGE              0x00       ///ʧѹ
#define COMM_EVEN_TYPE_ALLLOSEVOLTAGE   0x01      ////ȫʧѹ
#define COMM_EVEN_TYPE_ASSISTANT_POWERLOSE      0x02    ///������Դʧ��
#define COMM_EVEN_TYPE_CONVERSE             0x03                ////��ѹ/����������
#define COMM_EVEN_TYPE_UNBLANCE         0x04                    ////��ѹ/������ƽ��
#define COMM_EVEN_TYPE_SWIM_OVERLOAD    0X05                /////�������������
#define COMM_EVEN_TYPE_CURRENT_FAILUE   0X06      ////���������
#define COMM_EVEN_TYPE_POWEROFF             0x07                ///����

#define COMM_EVEN_FAILURE_LOSEVOLTAGE_TOTAL         18        /////ʧѹ��¼���������ۼ�ʱ������ݳ���
#define COMM_EVEN_FAILURE_ALL_LOSEVOLTAGE_TOTAL 6        ////ȫʧѹ�ļ�¼���������ۼ�ʱ������ݳ���
#define COMM_EVEN_FAILURE_LOSE_ACPPOWER_TOTAL       6        ////������Դʧ���ܴ���,�ۼ�ʱ��
#define COMM_EVEN_FAILURE_CONVERSE_VOL_CUR_TOTAL 6      ////��ѹ,����������
#define COMM_EVEN_FAILURE_UNBLANCE_VOL_CUR_TOTAL 6                  ////��ѹ,����,��ƽ��,���ۼ�ʱ��,�ۼƴ���
#define COMM_EVEN_FAILURE_REVER_CURRENT_TOTAL        18        ////��������,����
#define COMM_EVEN_FAILURE_LOSE_CURRENT_TOTAL            18        ////ʧ��,����,����
#define COMM_EVEN_FAILURE_POWEROFF_TOTAL                    3                   ////����

#define COMM_EVEN_METER_HANDLE_TOTAL                            3        ///��������¼�ܴ��������ݳ���
#if (CONFIG_METER_AREA_MODE_SOUTHGRID==CONFIG_METER_AREA_MODE)
#define COMM_EVEN_FAILURE_ALL_LOSEVOLTAGE_LENTH     131      ///ȫʧѹ��¼���ݳ���
#else
#define COMM_EVEN_FAILURE_ALL_LOSEVOLTAGE_LENTH     15      ///ȫʧѹ��¼���ݳ���
#endif
#define COMM_EVEN_FAILURE_LOSE_ACPPOWER_LENTH           12      ////������Դʧ�緢��ʱ��,����ʱ��
#define COMM_EVEN_FAILURE_POWER_OFF_LENTH                   12      //�����¼

#define COMM_EVEN_FAILURE_VOLTAGECHECKOUT_RECORD    12     ///��ѹ�ϸ��ʼ�¼12����

////��Ҫ����DI3
typedef struct
{
    uchar ucIDBlockType;   ///�������ݵ�����
    WReturnFUNCTION  TypeFunction; ////����������Ӧ�ĺ���
    
}STR_TABLE_BLOCK_TYPE;


////��Ҫ�����������DI2
typedef struct
{
    uchar Block1Start;    ///��������1���п�ʼ��ID��
    uchar Block1END;      ///��������1���н�����ID��
}STR_EC_BLOCK_PHASE_ID;


////��Ҫ�����������е�DI2,��������׵�ַ
typedef struct
{
    uchar  ECTypeID;   ///���������ϸ��ID
    uchar  ECUseState:1;     ///��ǰ�����Ƿ���ڸ���(0��,1��),
    uchar  ECFeeState:1;     ///��ǰ�������Ƿ��������Ԫ��(0��,1��),
    uchar  ECHistoryState:1;     //��ʷ�����Ƿ���ڸ���(0��,1��),
    uchar  ECHistoryFeeState:1;     ///��ʷ���������Ƿ��з���   
    uchar  MDUseState:1;     ///��ǰ�����Ƿ���ڸ���(0��,1��),
    uchar  MDFeeState:1;     ///��ǰ�������Ƿ��������Ԫ��(0��,1��),
    uchar  MDHistoryState:1;     //��ʷ�����Ƿ���ڸ���(0��,1��),
    uchar  MDHistoryFeeState:1;     ///��ʷ���������Ƿ��з���   
    ulong  ECAddr;      ///������ַ
    ulong  MDAddr;     ///������ַ
        
}STR_EC_BLOCK_ID;


////�������ǿ���������ݣ����DI2=0x90�ĵ�������
typedef struct
{
  uchar TypeID1;   //DI1
  uchar TypeID0;   //ID0
  uchar UsedAble;  //�Ƿ�ʹ��
  uchar FormatLen;  //��Լ����
  uchar AcceLen;   //�洢�ĳ���
  ulong DataAddr;  //��������
  
}STR_EC_CARD_ID;


///////��������բ�����ݣ����DI2=0X31���¼���¼
typedef struct
{
  uchar  EvenType;     ////����(ID1)
  ulong  TotalCountAddr;   ///������¼��ַ
  ulong  RecordAddr;      ////��¼���ݶ��α��ַ
  u16  RecordTim;      ///��¼����
  uchar  UsedState;     ///�Ƿ�ʹ��0û�У�1 ʹ��
  
}STR_EVEN_CT_ST_GATE;




#define NULLDATAADDR   0xFFFFFFFF     ////,û�ж���ĵ�ַΪ0xFFFFFFFF

typedef struct
{
    uchar IDType;   ////DI1
    uchar Used:1;     ///�Ƿ�ʹ��
    uchar StartID:3;     ///ID1�Ƿ��Ǵ��ĸ���ʼ��,
  uchar UsedID1Num:3;  ///ID1ʹ���˼���
    uchar WithFF:1;       ///ID1ΪFFҲ���Գ���.0:������,1:����
    uchar RecordTim;      ///��¼�Ĵ���(ID0)00:��������FF����.>0�Ļ�,�Ϳ�����FF����
    uchar UseFormat:4;  ///�洢ʹ�õ��ֽڳ���(���Ȳ��ᳬ��15)
    uchar FormatLenth:4;   ////��Լ��ʽʹ�õ��ֽڳ���(���Ȳ��ᳬ��15)
    ulong Addr;         ////��ַ

}STR_VARIABLE_ID;     ////�������ݱ�ʶ

////�������е�������0x80,���ڳ��Ȳ��ᳬ��15���Գ����ð��ֽ�����ʾ
typedef struct
{
    uchar IDType;   ////DI0
    uchar Used:1;     ///�Ƿ�ʹ��0:û��,1,ʹ��
    uchar FormatLenth:3;     ///��Լʹ�õĳ���
    uchar UsedLenth:4;         ///�洢ʹ�õĳ���
    ulong Addr;         ////��ַ
}STR_VARIABLE_ESPECEIVE;


///////////////////////////////�¼�///////////////////////////////////////////////////////////////
////�¼��Ĺ���
typedef struct
{
    uchar IDTypeStart;     ///��ʼID
    uchar IDTypeEnd;      ///����ID
    uchar IDType;        ///�¼������
    uchar UsedState;  ////�Ƿ�ʹ��
    
}STR_COMM_EVENTYPE;

///�������¼�(ʧѹ,Ƿѹ,��ѹ,������.)
typedef struct
{
    uchar EvenRecordID;    ///�¼���ID
    uchar EvenType;             ///�¼�����
    ulong TotalAddr;      ////�¼���¼�ܵ�ַ(DI1=0,DI0=0)
    uchar RecordTim;            ////��¼�Ĵ���0:����û��ʹ�ø���,
    uchar TotalLenth;    ////�ۼƴ���,ʱ��ļ�¼����
}STR_COMM_EVEN_BLOCK_FAILURE;

typedef struct s_cnttime
{
    ulong ulID;                 //���ݱ�ʶ
    ulong ulAddr;               //���ݵ�ַ
}S_CNTTIME;

typedef struct s_evfmt
{
    uchar ucOffset;             //�ڼ�¼�е�ƫ��
    uchar ucLen;                //�������ݵĳ���
    uchar ucType;    
}S_EVFMT;

typedef struct s_idconv1
{
    ulong   ulVID;              //����id
    uchar   ucSim1;             //ID1����������
    uchar   ucSim0;             //ID0����������
    uchar   ucType;             //��¼���,���ڲ���α�
    uchar   reserved;           //����
    void*   pvFmt;              //ָ���ʽ���ָ��
}S_IDCONV1;

////�������¼����α������Ķ��α��ַ
typedef struct
{
    uchar IDType;
    uchar APhaseAddr;
    uchar BPhaseAddr;
    uchar CPhaseAddr;
}STR_COMM_EVEN_FAILURE_TWOTABLE_ADDR;


////��ѹ�ϸ������¼�
typedef struct
{
    uchar IDType;      ////ID1
    ulong Currently;   ////��ǰ��ַ
    u16  HistoryTwoTable;   ////���α��ַ
}STR_COMM_EVEN_VOLTAGE_CHECKOUT_ADDR;


///�������޼�¼
typedef struct
{
    uchar IDType;     ///ID1
    u16  TwoTableAddr;  ///���α�λ��
    uchar UsedState;     ///�Ƿ�ʹ��
}STR_COMM_EVEN_MD_OVER_LOAD;

////�¼��ļ�¼����
typedef struct
{
    uchar EvenID;       ///�¼�ID,ID2,
    uchar Type;        ///�¼��ķ���
    uchar RecordNum;   ///��¼����
    
}STR_EVEN_RECORD_TYPE_LOSEVOLTAGE;


/////������
typedef struct
{
    uchar IDType;           ////ID1,�¼�����
    uchar *RecordTableLenth;    ////��¼����
    ulong TotalAddr;          ///��¼�����ĵ�ַ
    u16  TwoTableAddr;       ////���α�ĵ�ַ
    uchar UsedState;                    ///�Ƿ�ʹ��
    u16  UseTableSize;             /////��Լ��ʽ���ĳ���
    uchar *FormatTable;      ////��Լ��ʽ��λ��
}STR_EVEN_RECORD_METER_HANDLE;

/////�¼��Ĵ洢��ʽ���Լ��ʽ�Ķ��ձ�
typedef struct
{
    uchar IDType;    ////ID1,�¼�����
    ///uchar TotalLenth;  ////���ۼƳ���
    uchar *RecordTableLenth;   ////�洢���ݵĸ�ʽ
    uchar *FormatTableLenth;     ////��Լ�ĸ�ʽ
    uchar  FormatLenth;             ////��Լ���ĳ���
    
}STR_EVEN_RECORD_CHANGETOFORMAT;

#define COMM_EVEN_WEITH_NULL     0x00      ////�¼���¼��û��ʹ�õ��������ø�ֵ��д

/////����Ȩ��
#define COMM_PASSWORD_POPEDOM_0                 0x00    ///0��Ȩ��
#define COMM_PASSWORD_POPEDOM_1                 0x01    ///1��Ȩ��
#define COMM_PASSWORD_POPEDOM_2                 0x02    ///2��Ȩ��
#define COMM_PASSWORD_POPEDOM_3                 0x03    ///3��Ȩ��
#define COMM_PASSWORD_POPEDOM_4                 0x04    ///4��Ȩ��
#define COMM_PASSWORD_POPEDOM_5                 0x05    ///5��Ȩ��
#define COMM_PASSWORD_POPEDOM_6                 0x06    ///6��Ȩ��
#define COMM_PASSWORD_POPEDOM_7                 0x07    ///7��Ȩ��
#define COMM_PASSWORD_POPEDOM_8                 0x08    ///8��Ȩ��
#define COMM_PASSWORD_POPEDOM_9                 0x09    ///9��Ȩ��

#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
#define COMM_PASSWORD_FIRST_PARA                (COMM_PASSWORD_POPEDOM_2)
#define COMM_PASSWORD_SECOND_PARA               (COMM_PASSWORD_POPEDOM_2)
#else
#define COMM_PASSWORD_FIRST_PARA                (COMM_PASSWORD_POPEDOM_4)
#define COMM_PASSWORD_SECOND_PARA               (COMM_PASSWORD_POPEDOM_4)
#endif

#define COMM_PASSWORD_LOCKTIME_SIZE             2       // ��������ʱ�䳤��
#if (CONFIG_METER_AREA_MODE == CONFIG_METER_AREA_MODE_SOUTHGRID) // ����Ҫ����������5�γ���������
#define COMM_PASSWORD_ERR_MAXTIME   4
#else
#if(CONFIG_METER_TYPE==CONFIG_METER_TYPE_SD39C)
#define COMM_PASSWORD_ERR_MAXTIME   4
#else
#define COMM_PASSWORD_ERR_MAXTIME   2
#endif
#endif

////����������
#define COMM_PARAMETER_USED            1   /////ʹ��
#define COMM_PARAMETER_NO_USED         0   ////û��ʹ��
////���⹦��ʹ��
#define COMM_PARAMETER_SAVE_NO_ATTESTATION   0    ///û�����⹦��
////��ַ����
#define COMM_DIRECT_ADDRESSING                      0 //////
//#define COMM_
///��������
#define COMM_PARAMETER_BCD_TYPE         0     ///BCD����
#define COMM_PARAMETER_ASC_TYPE         1     ///ASCII����
////��д����
#define COMM_WRITE                      0x01    ///д
#define COMM_READ                       0x02    ///��
#define COMM_PASSWORD                   0x04   /////����,���ɶ�����д
#define COMM_IDEL                       0x00    ///��д����ֹ

/////�����ֽڳ���
#define COMM_HOLIDAY_WORD_SIZE          4     ///���������ֽڳ���
#define COMM_CYCLE_DSP_SIZE             5     ///ѭ����ʾ,������ʾ�ֽڳ���
#define COMM_SEASON_SIZE                3    ////��ʱ������
#define COMM_EVENT_COUNT_SIZE           3    // �¼���������

////////////////����//////////////////////////////////////
///���������
#define  COMM_FREEZE_TIME                       0x00     ///��ʱ����
#define  COMM_FREEZE_INSTANTANEOUS  0X01       ///˲ʱ����
#define  COMM_FREEZE_SEANSONTABLE_CHANGE   0X02   ////����ʱ�����л�����
#define  COMM_FREEZE_DAYTABLE_CHANGE            0X03    /////������ʱ�α��л�����
#define  COMM_FREEZE_HOURORHALF                     0x04//���㶳��
#define  COMM_FREEZE_DIVTIMFEE_CHANE                     0x05   ////��ʱ�����л�����
#define  COMM_FREEZE_DAY                                0x06   /////�ն���
#define  COMM_FREEZE_STEP_CHANE                          0x07    ////���׽����л�����



#define  COMM_FREEZE_RECORD_TIM                         60     ////��ʱ�����¼�Ĵ���
#define  COMM_FREEZE_IMMEDIATE_TIM                  3      ////˲ʱ�����¼�Ĵ���
#define  COMM_FREEZE_FEETABLE_TIM                       2      ////����ʱ��,ʱ�α��¼�Ĵ���
#define  COMM_FREEZE_HOUR_TIM                       254  //���㶳�����
#define  COMM_FREEZE_DIVFEECHANGE_TIM                                     2 ////�����л��������
#define  COMM_FREEZE_DAY_TIM                                  62   /////�ն���


#define  COMM_FREEZE_ZERO_TIME                                      10///���㶳�����

#define  COMM_FREEZE_ZEROTIME_NUM                                  48  ///���㶳��ĵ������ݸ���

#define  COMM_FREEZE_MAXLENTH                               20      ////�������ݵķ��������¼Ԫ�صĸ���������ڴ�ֵ�Ļ���Ҫ����֡�����û�з���֡
////��������ݽṹ
typedef struct
{
    uchar FeezeType;  ////�������������,
    uchar UsedState;   ////�Ƿ�ʹ�õ�
    uchar UseLenth;     ///ʹ�õĳ���(����Ԫ�صĳ���)
    uchar UseNum;              ////Ԫ�ظ���
    uchar FormatLenth;  ////��Լ�еĸ�ʽ(����Ԫ�صĳ���).
    //uchar RecordTim;    /////����Ĵ���
}STR_FREEZE_DATA_TYPE;


//////�ն�ͨ�ŵ����ݽṹ
typedef struct
{
  u16  uiID;    ////ʹ��ID
  ulong ulIRAWAddr;   ////����д��ַ
  ulong ulIRARAddr;   ////�������ַ
  ulong ulDataFlagAddr;    ////��־
  u16  uiLenth;           ///���ݳ���
  uchar WRAccess;          ///��дȨ�� 1ֻ��,2ֻд,3���ɶ�д
}STR_ZHONGDUAN_COMMDATA;


//////////////////////////////////////////////////////////////
#define ECDI2WITHNO      0xFF   
////////////////////////////////////////////////////////////////////////////////
#define COMM_METRER_ADDR_LENTH          6    ////ͨ�ŵ�ַ�ĳ���

COMMON_EXT  STR_RETURN_EXPLAINBUFFER *CommExpDataBuff;
COMMON_EXT  STR_READ_LASTFRAME  LastFrameData[LAST_FRAME_NUM];

COMMON_EXT  uchar ucOutPutLenth;
COMMON_EXT  uchar ucCommFormatType;   ////��Լ����
COMMON_EXT  STR_UART_PARA_CHANGE_CONTROL  UartPotr;     /////ͨ�Ŷ˿ڲ���
COMMON_EXT  uchar gucFarCtlFlg;
COMMON_EXT uchar isSpcecial_uart;      //���ڵײ㴮����ͨ��ȫ�ֱ�����ã�Ϊ�˼��ڼ䣬Ϊ�����⴮�ڶ���
///////���ܶ�д
///��
#define COMM_RECEIVE_ALL_STORYTYPE                    (CommExpReceiveDataBuffer.buff[12])
#define COMM_RECEIVE_ALL_DATALOW                      (CommExpReceiveDataBuffer.buff[13])
#define COMM_RECEIVE_ALL_DATAMID                      (CommExpReceiveDataBuffer.buff[14])
#define COMM_RECEIVE_ALL_DATAHI                       (CommExpReceiveDataBuffer.buff[15])
#define COMM_RECEIVE_ALL_DATALEN                      (CommExpReceiveDataBuffer.buff[16])
#define COMM_RECEIVE_ALL_INDEX                        (CommExpReceiveDataBuffer.buff[12])

////д
#define COMM_WRITE_ALL_STORYTYPE                    (CommExpReceiveDataBuffer.buff[16])
#define COMM_WRITE_ALL_DATALOW                     (CommExpReceiveDataBuffer.buff[17])
#define COMM_WRITE_ALL_DATAMID                     (CommExpReceiveDataBuffer.buff[18])
#define COMM_WRITE_ALL_DATAHI                      (CommExpReceiveDataBuffer.buff[19])
#define COMM_WRITE_ALL_DATALEN                     (CommExpReceiveDataBuffer.buff[20])
#define COMM_WRITE_ALL_DATA                        (CommExpReceiveDataBuffer.buff[21])

////Զ������բ
#define COMM_RECEIVE_STCTGATE_PASSWORD                (CommExpReceiveDataBuffer.buff[10])
#define COMM_RECEIVE_STCTGATE_USERID                  (CommExpReceiveDataBuffer.buff[14])
#define COMM_RECEIVE_STCTGATE_CONTROLID               (CommExpReceiveDataBuffer.buff[18])

///ADE7758��д
///��
#define COMM_ADE7758_READ_LENTH                                 (CommExpReceiveDataBuffer.buff[14]) 
#define COMM_ADE7758_READ_ADDRH                                 (CommExpReceiveDataBuffer.buff[12])                                                         
#define COMM_ADE7758_READ_ADDRL                                 (CommExpReceiveDataBuffer.buff[13])                                                         
///д
#define COMM_ADE7758_WRITE_LENTH                                    (CommExpReceiveDataBuffer.buff[18]) 
#define COMM_ADE7758_WRITE_ADDRH                                    (CommExpReceiveDataBuffer.buff[16]) 
#define COMM_ADE7758_WRITE_ADDRL                                    (CommExpReceiveDataBuffer.buff[17]) 
#define COMM_ADE7758_WRITE_DATA                                 (CommExpReceiveDataBuffer.buff[19])                 

/////////////////////////////////////////////////////////////////////////////////
#define COMM_RECEIVE_FRAME_ADDRSTART             (CommExpReceiveDataBuffer.buff[1])
#define COMM_RECEIVE_FRAME_CONTROLNO             (CommExpReceiveDataBuffer.buff[8])
#define COMM_RECEIVE_FRAME_LENTH                     (CommExpReceiveDataBuffer.buff[9])
#define COMM_RECEIVE_FRAME_DATA                      (CommExpReceiveDataBuffer.buff[10])

///////д����֡
#define COMM_RECEIVE_WRITE_PASSWORD             (CommExpReceiveDataBuffer.buff[14]) 
#define COMM_RECEIVE_WRITE_USEDID               (CommExpReceiveDataBuffer.buff[18]) 
#define COMM_RECEIVE_WRITE_DATA                   (CommExpReceiveDataBuffer.buff[22])   


/////����֡
#define COMM_LAST_FRAME_NUM                             (CommExpReceiveDataBuffer.buff[14]) 


/////д����
#define COMM_RECEIVE_WRITE_FARME_PASSWORD                 (CommExpReceiveDataBuffer.buff[18])   

/////����,���,�¼������������ʼλ
#define COMM_RECEIVE_CLEAR_PASSWORD                   (CommExpReceiveDataBuffer.buff[10])   

#define COMM_RECEIVE_CLEAR_USERNUM                (CommExpReceiveDataBuffer.buff[14])   
////�¼��������ݱ�ʾ
#define COMM_EVEN_CLEAR_DATA                                (CommExpReceiveDataBuffer.buff[18]) 

/////д���ַ����֡
#define COMM_RECEIVE_WRITE_ADDR_DATA                         (CommExpReceiveDataBuffer.buff[10])

////��������
#define COMM_RECEIVE_FEEZE_DATA_MIN                         (CommExpReceiveDataBuffer.buff[10])
#define COMM_RECEIVE_FEEZE_DATA_HOUR                         (CommExpReceiveDataBuffer.buff[11])
#define COMM_RECEIVE_FEEZE_DATA_DAY                         (CommExpReceiveDataBuffer.buff[12])
#define COMM_RECEIVE_FEEZE_DATA_MON                         (CommExpReceiveDataBuffer.buff[13])
/////////////���ݿ��ַ�Ķ���

//////�ն˶�д�ĸ�ʽ(97��645��Լ)
#define COMM_ZHONGDUAN_ID                           (CommExpReceiveDataBuffer.buff[10])
#define COMM_ZHONGDUAN_WRITE                        (CommExpReceiveDataBuffer.buff[10])

#define COMM_97TYPE_CONTROLWORD                         (CommExpReceiveDataBuffer.buff[8])
#define COMM_97TYPE_LENGTH                         (CommExpReceiveDataBuffer.buff[9])
#define COMM_97TYPE_PASSWORD                         (CommExpReceiveDataBuffer.buff[12])
#define COMM_97TYPE_WRITEDATA                        (CommExpReceiveDataBuffer.buff[16])

#define COMM_97TYPE_ADDDATAID                         (CommExpReceiveDataBuffer.buff[16]+(CommExpReceiveDataBuffer.buff[17]<<8)) 
#define COMM_97TYPE_ADDDATAIDREAD                         (CommExpReceiveDataBuffer.buff[12]+(CommExpReceiveDataBuffer.buff[13]<<8)) 
#define COMM_97TYPE_ADDDATABEGIN                         (CommExpReceiveDataBuffer.buff[18]) 
#define COMM_97TYPE_ADDDATAREADBEGIN                         (CommExpReceiveDataBuffer.buff[14]) 
#define COMM_97TYPE_READDATA                         (CommExpReceiveDataBuffer.buff[12]) 

#define COMM_MULTIPORT_DATA                         (CommExpReceiveDataBuffer.buff[10])

////�㲥Уʱ
#define COMM_BCAST_DATA_START                              (CommExpReceiveDataBuffer.buff[10])     
///////�޸�ͨ�Ų�����������
#define COMM_CHANGE_COMM_BAUT_WORD                            (CommExpReceiveDataBuffer.buff[10])       


// �¼���¼���ȶ���
#define LENGTH_RELAY_EVENT 105


COMMEXPLAIN_EXT COMM_CONST      STR_TAB_CMMCONTROL    TableCommControl[];
COMMEXPLAIN_EXT COMM_CONST    STR_TABLE_BLOCK_TYPE  TableCommReadBlock[];
COMMEXPLAIN_EXT COMM_CONST    STR_EC_BLOCK_ID           TableReadECPhaseBlock[];

//COMMEXPLAIN_EXT COMM_CONST  STR_EC_CARD_ID  TableCardEner[];


COMMEXPLAIN_EXT COMM_CONST    STR_EC_BLOCK_PHASE_ID   TableCommPhaseBlock[];
//COMMEXPLAIN_EXT COMM_CONST    STR_EC_BLOCK_ID    TableReadECBlock[];
//COMMEXPLAIN_EXT COMM_CONST    STR_VARIABLE_ID  TableVariable[];
//COMMEXPLAIN_EXT COMM_CONST    STR_VARIABLE_ESPECEIVE  TableVariableEscipe[];
COMMEXPLAIN_EXT COMM_CONST      STR_COMM_EVENTYPE TableCommEvenType[];
COMMEXPLAIN_EXT COMM_CONST      uchar ucEvenLosevoltageLenth[];
COMMEXPLAIN_EXT COMM_CONST      STR_COMM_EVEN_BLOCK_FAILURE     TableCommEvenFAILURE[];
COMMEXPLAIN_EXT COMM_CONST  STR_COMM_EVEN_FAILURE_TWOTABLE_ADDR  TableTwotableAddr[];
COMMEXPLAIN_EXT COMM_CONST    uchar ucEvenConverseLenth[];
COMMEXPLAIN_EXT COMM_CONST  uchar ucEvenUblanceLenth[];
COMMEXPLAIN_EXT COMM_CONST  STR_COMM_EVEN_VOLTAGE_CHECKOUT_ADDR   TableVoltagecheckOutaddr[];
COMMEXPLAIN_EXT COMM_CONST  uchar ucEvenVoltagecheckOut[];
COMMEXPLAIN_EXT COMM_CONST  uchar ucEvenMDOverLoad[];
COMMEXPLAIN_EXT COMM_CONST  STR_COMM_EVEN_MD_OVER_LOAD  TableMDOverLoadAddr[];
COMMEXPLAIN_EXT COMM_CONST  uchar ucEvenMDOverLoadRecord[];
COMMEXPLAIN_EXT COMM_CONST STR_EVEN_RECORD_METER_HANDLE TableEvenMeterHandle[];
COMMEXPLAIN_EXT COMM_CONST  uchar ucEvenLoseCurrentLenth[];
COMMEXPLAIN_EXT COMM_CONST  uchar ucEvenLoseCurrentLenth[];
COMMEXPLAIN_EXT COMM_CONST  STR_FREEZE_DATA_TYPE        TableFreezeType[];
COMMEXPLAIN_EXT COMM_CONST   uchar   CommFeezeArrWord[];
COMMEXPLAIN_EXT COMM_CONST  uchar ucEvenFeeTableProgram[];

COMMEXPLAIN_EXT COMM_CONST STR_EVEN_RECORD_CHANGETOFORMAT TableEvenDataToFormat[];

COMMEXPLAIN_EXT COMM_CONST STR_EVEN_CT_ST_GATE TableCommCSGate[];
COMMEXPLAIN_EXT  const uchar DEFAULT_VALUE_GROUP[];
COMMEXPLAIN_EXT const S_IDCONV1 gCs_IDConv1[];
COMMEXPLAIN_EXT const S_CNTTIME gCS_CntAndTimeTab[];

COMMEXPLAIN_EXT const uchar gCuc_IDConv1TabNum;
COMMEXPLAIN_EXT const uchar gCuc_CntAndTimeTabNum;

// COMMEXPLAIN_EXT COMM_CONST  STR_ZHONGDUAN_COMMDATA  TableZhongDuanComm[];

//////λ����
COMMEXPLAIN_EXT COMM_CONST uchar UseFeezeBit[];

COMMEXPLAIN_EXT  uchar GetComm645ControlNO(void);
COMMEXPLAIN_EXT  u16 GetControlTableNum(void);
COMMEXPLAIN_EXT  u16 GetCommReadTypeNum(void);
COMMEXPLAIN_EXT u16  GetDataByID(STR_READDATA_INPUT* Src);
COMMEXPLAIN_EXT u16  GetVariableTableNum(void);
COMMEXPLAIN_EXT u16 GetEvenBlockTypeNum(void);
COMMEXPLAIN_EXT u16 GetEvenTypeFailureNum(void);

//COMMEXPLAIN_EXT u16 GetCardEnergyTableNum(void);

COMMEXPLAIN_EXT u16 GetZhongDuanTableNum(void);

COMMEXPLAIN_EXT u16 GetEvenMDOverLoadRecordLenth(void);
COMMEXPLAIN_EXT u16 GetEvenMDOverLoadRecord(void);
COMMEXPLAIN_EXT u16 GetEvenMeterHandileNum(void);
COMMEXPLAIN_EXT u16 GetECBlockPhaseTableNum(void);
COMMEXPLAIN_EXT u16 GetECTypeBlockTableNum(void);
COMMEXPLAIN_EXT u16 GetFreezedataNum(void);
COMMEXPLAIN_EXT u16 GetEscepecialVariableNum(void);
COMMEXPLAIN_EXT u16 GetEvenLoseVoltageNum(void);
COMMEXPLAIN_EXT u16 GetEvenLoseVoltagePhaseNum(void);
COMMEXPLAIN_EXT u16 GetEvenConverseNum(void);
COMMEXPLAIN_EXT u16 GetEvenVolCurUnblanceNum(void);
COMMEXPLAIN_EXT u16 GetEvenLoseCurrentNum(void);
COMMEXPLAIN_EXT u16 GetCheckOutVoltageNum(void);
COMMEXPLAIN_EXT u16 GetCheckOutVoltageType(void);
COMMEXPLAIN_EXT u16 GetEvenMDOverLoadTim(void);
//COMMEXPLAIN_EXT u16 GetEvenMDOverLoadTim(void);
COMMEXPLAIN_EXT u16 GetEvenDataFormatNum(void);
COMMEXPLAIN_EXT u16 GetParameterTableNum(void);
COMMEXPLAIN_EXT u16 GetAddParameterTableNum(void);


COMMEXPLAIN_EXT u16  GetCTSTGateNum(void);
////���645��Լ��ID(ע��,�ֽڸߵ�λ��˳��,��ͬ��Ƭ���п��ܲ�ͬ��Ҫ�޸�)
ulong GetCommReadData645ID(uchar FormatNO);
uchar GetCommDataLen(void);
uchar GetCommReadLoadDataNum(void);
void GetCommReadLoadDataTim(uchar * TimAddr);

/////////////��ò����ߴ���/////////////////////////
void GetUseNumber(uchar *Dest,uchar Lenth);
///�Ƚ�����Ȩ��
///����0����Ȩ�޲���,��������Ȩ�޲���
uchar CommCmpPassword(uchar PasswordLevel);
void ClearAllPasswordErrCount(void);

/////��ù���������Ŀ
u16 GetSetHolidayNum(void);
////���ѭ�Ը���
u16 GetSetCycleLcdNum(void);
////��ü��Ը���
u16 GetkeyCycleNum(void);
////��ñ�̼���״̬
///1Ϊ���״̬,0Ϊ�Ǳ��״̬
uchar GetTheProgramKeyState(void);

COMMEXPLAIN_EXT void  CommClearLtVirtual485(void);

COMMEXPLAIN_EXT uchar DefaultParaInit(void);
COMMEXPLAIN_EXT  uchar CommStrCmp(uchar *Dest,uchar *Src,u16 uiLthen);

////���ʱ�α����
COMMEXPLAIN_EXT u16  GetFeeDayTableMaxNum(void);
////�����ʱ����
COMMEXPLAIN_EXT u16  GetFeeSeasonMaxNum(void);
///������õķ�����
COMMEXPLAIN_EXT uchar GetSetFeeNumber(void);

COMMEXPLAIN_EXT uchar GetSetLadderNumber(void);

////���ʱ�θ���
COMMEXPLAIN_EXT u16  GetFeeTouTableMaxNum(void);

/////���ͨ�Ŷ˿ںš�
COMMEXPLAIN_EXT uchar GetExplainCommNo(void);
/////��ù�Լ���͡�
COMMEXPLAIN_EXT uchar GetCommType(void);

////���ͨ�ſ������͵�ָ��
COMMEXPLAIN_EXT u16 GetCommTypePtr(uchar ControlData);
/////��ö������д����������ָ��
COMMEXPLAIN_EXT u16 GetCommReadTypePtr(uchar ControlData);

COMMEXPLAIN_EXT uchar GetCommBautType(UARTMODE * Mode,uchar WordType,uchar CommNormberType);

/////��ʼ������֡�����ж�Ӧͨ�Ŷ˿ں��е�����
COMMEXPLAIN_EXT void InitialLastFrameBuffer(uchar CommNo);

///������ַ�İ���
COMMEXPLAIN_EXT uchar SaveLastFrameInBuffer(STR_LASTFRAME_IN_PARA InPara,uchar *Dest);
///���÷���֡
COMMEXPLAIN_EXT void SetReturnDataFrame(uchar DataLenth,uchar ControlData);

COMMEXPLAIN_EXT void CommControlReadData(void);
COMMEXPLAIN_EXT void CommControlReadLastData(void);
COMMEXPLAIN_EXT void CommReadECData(STR_READ_RETURN_PARA *Dest,ulong ID);
COMMEXPLAIN_EXT void CommReadMDData(STR_READ_RETURN_PARA *Dest,ulong ID);
COMMEXPLAIN_EXT void CommVariableData(STR_READ_RETURN_PARA *Dest,ulong ID);
COMMEXPLAIN_EXT void CommEvenRecordData(STR_READ_RETURN_PARA *Dest,ulong ID);
COMMEXPLAIN_EXT void CommReadParaData(STR_READ_RETURN_PARA *Dest,ulong ID);
COMMEXPLAIN_EXT void CommReadFeezeData(STR_READ_RETURN_PARA *Dest,ulong ID);
COMMEXPLAIN_EXT void CommReadFeezeZeroData(STR_READ_RETURN_PARA *Dest,ulong ID);



COMMEXPLAIN_EXT void CommReadAddr(void);
COMMEXPLAIN_EXT void CommWriteAddr(void);
COMMEXPLAIN_EXT void CommBroadCastTime(void);
COMMEXPLAIN_EXT void CommControlFeezeData(void);
COMMEXPLAIN_EXT void CommClearEven(void);
COMMEXPLAIN_EXT void CommRelaySet(void);
COMMEXPLAIN_EXT void CommClearEC(void);
COMMEXPLAIN_EXT void CommDisplayNO(void);
COMMEXPLAIN_EXT void CommChangeBaudRate(void);
COMMEXPLAIN_EXT void CommChangePassword(void);
COMMEXPLAIN_EXT void CommClearMD(void);
COMMEXPLAIN_EXT void CommMultiPort(void);
COMMEXPLAIN_EXT void CommControlZB(void);

COMMEXPLAIN_EXT void Rcomm645Control(void);


COMMEXPLAIN_EXT void AddData33(uchar * Ptr,uchar Lenth);
COMMEXPLAIN_EXT void SubData33(uchar * Ptr,uchar Lenth);

////���ض����ݵ�ͷ(FE+68+��ַ+68+������+����)
COMMEXPLAIN_EXT void GetReadReturnDataHead(uchar *Dest,uchar ControlData,uchar DataLenth);
////�Ƚ�����Ȩ������
COMMEXPLAIN_EXT uchar ClearCmpPassword(uchar PasswordLevel,uchar *Dest);
#endif



























