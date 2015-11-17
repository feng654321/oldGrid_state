#ifndef  COMMEXPWRITE_H
                #define COMMEXPWRITE_H
                #define COMMEXPWRITE_EXT                extern

////////////////////////////////////////////////////////////////////////////////////////
//typedef  uchar (*EvenFUNCTION)(void);

///////�α�������
typedef  struct
{  
    ulong id;                   //ͨ����ʾID
    ulong memoryAddress;        //���ݵ�ַ
    uchar dataLens;             //���ݳ���
    WithReturnFUNCTION callBack;        //add call back for write id,(�����Ϻ��һϵ��ˢ�²����Ĳ���)
    CheckFunction CheckFunction;    ////У�������Ч�Եĺ���
    uchar access;                               //Ȩ��
    uchar WithPKey:1;               ///�Ƿ���ϱ�̼�
    uchar WithSpecKey:2;        ///�Ƿ���Ҫ������⹦��(���簲ȫ��֤)
    uchar addressType:2;                //��ַ����  
    uchar dataType:2;                       //��������  
    uchar enabled:1;                    //����
    uchar ReadAndWrite;       ///��дȨ�޿���
    uchar ProgramType;        ///��̼�¼����
}ST_COMM_DISP_LIST;

typedef  struct
{  
    ulong id;                   //ͨ����ʾID
    ulong memoryAddress;        //���ݵ�ַ
    u16 dataLens;              //���ݳ���
    uchar byte_order;               //�ֽ��Ƿ�����
}ST_COMM_ADD_PARA;
///////��Ҫ�¼���¼�Ĳα���
/*
typedef  struct
{
    ulong ID;      ////ͨ��ID
    uchar 
//  EvenFUNCTION  EvenRecordFun;     ////�¼���¼���ú���
     
}ST_COMM_PROGRAM_LIST;           
*/

COMMEXPWRITE_EXT COMM_CONST  ST_COMM_DISP_LIST  TableParaMeter[];
COMMEXPWRITE_EXT COMM_CONST  ST_COMM_ADD_PARA AddPara[];
                /////////////////////////�α������ݵ���Ч�Լ��////////////////////////////
COMMEXPWRITE_EXT uchar CommDayFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
///ʱ���ʽ���
COMMEXPWRITE_EXT uchar CommTimeFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////����������ڼ��
COMMEXPWRITE_EXT uchar CommMDFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////����ʱ����Ч�Լ��
COMMEXPWRITE_EXT uchar CommTackleFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////��ʱ�α�/ʱ�����л�ʱ��,
COMMEXPWRITE_EXT uchar CommFeeTableSwitchFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);

COMMEXPWRITE_EXT uchar CommmmhhDDMMYYFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);

////��ʱ����/��Ч���ж�
COMMEXPWRITE_EXT uchar CommSeasonNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////��ʱ�α�����Ч���ж�
COMMEXPWRITE_EXT uchar CommDayTableNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////��ʱ������Ч���ж�
COMMEXPWRITE_EXT uchar CommFeeTableNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
///��������Ч���ж�
COMMEXPWRITE_EXT uchar CommFeeNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
///����������
COMMEXPWRITE_EXT uchar CommHolidayNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////�����ձ����Ч���ж�
COMMEXPWRITE_EXT uchar CommWeekTableNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);

//г������
COMMEXPWRITE_EXT uchar CommHarmoniousFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////��ʾ����(����,����)
//COMMEXPWRITE_EXT uchar CommDspNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
///��ʾʱ��
COMMEXPWRITE_EXT uchar CommDspTimeFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
///��ʾ����С��
COMMEXPWRITE_EXT uchar CommDspMDFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
///��ʾ����С��
COMMEXPWRITE_EXT uchar CommDspECFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
///���ɼ�¼ʱ��
COMMEXPWRITE_EXT uchar CommLoadRecordFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////��������Ч���ж�
COMMEXPWRITE_EXT uchar CommBillDayFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////ʱ������Ч���ж�
COMMEXPWRITE_EXT uchar CommSeasonTableFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////ʱ�α���Ч���ж�
COMMEXPWRITE_EXT uchar CommFeeDayTableFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////����������Ч���ж�
COMMEXPWRITE_EXT uchar CommCheckHolidayFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////У��պ���
COMMEXPWRITE_EXT uchar NULLCheckFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////У�鳧��״̬����
COMMEXPWRITE_EXT uchar FactoryCheckFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
///������У�麯��
COMMEXPWRITE_EXT uchar CommBautWordFm(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
///BCDУ��
COMMEXPWRITE_EXT uchar CommWriteBcdFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
#if(CONFIG_METER_PREPAY_MODE==CONFIG_METER_PREPAY_MODE_FAR)
COMMEXPWRITE_EXT uchar CommWriteFormatKey(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
#endif
COMMEXPWRITE_EXT uchar CommDemandNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);

COMMEXPWRITE_EXT uchar CommWeekDayUseTouFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
COMMEXPWRITE_EXT uchar CommCheckhhmm(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////����ֵ
COMMEXPWRITE_EXT uchar NULLReturnValue(void);

COMMEXPWRITE_EXT void CommControlWriteData(void);
COMMEXPWRITE_EXT uchar GetCommTypeName(uchar ucID0);

#endif
