
#ifndef EVENT_PROGRAM_H
    #define EVENT_PROGRAM_H

#ifdef  AP_COMMPROGRAM_H
    #define EVENT_PROGRAM_EXT
#else
    #define EVENT_PROGRAM_EXT extern
#endif

#define     PROGRAM_CLEAR_ENABLE_SWITCH1        0xA55A
#define     PROGRAM_CLEAR_ENABLE_SWITCH2        0x5AA5


EVENT_PROGRAM_EXT   u16 programEnableCount;



/*
///////���07���
//////���ֱ���¼������ݶ���            
#define COMM_EVEN_MeterClear    0x01
#define COMM_EVEN_MDClear               0x02
#define COMM_EVEN_EvenClear         0x03
#define COMM_EVEN_CHECKTIME         0x04
#define COMM_EVEN_FEETABLEP_ROGRAM  0x05
#define COMM_EVEN_SEASONTABLE_PROGRAM 0x06
#define COMM_EVEN_WEEKTABLE_PROGRAM 0x07
#define COMM_EVEN_HOLIDAY_PROGRAM       0x08
#define COMM_EVEN_ACTIVECOMBINE_1_PROGRAM           0x09
#define COMM_EVEN_NACTIVECOMBINE_2_PROGRAM      0x0A
#define COMM_EVEN_NACTIVECOMBINE_3_PROGRAM                  0X0B

*/



// ��¼�¼�����
#define PROGRAM_RECORD_COMMOM           0x01        ////����¼����ݼ�¼
#define PROGRAM_RECORD_METER_CLR            0x02        ////����������¼����ݼ�¼
#define PROGRAM_RECORD_ENERGY_CLR       0x03        ////�����������¼����ݼ�¼
#define PROGRAM_RECORD_DEMAND_CLR       0x04        ////�����������¼����ݼ�¼
#define PROGRAM_RECORD_EVENT_CLR            0x05        ////�¼��������¼����ݼ�¼
#define PROGRAM_RECORD_ADJUST_TIME      0x06        ////Уʱ����¼����ݼ�¼
#define PROGRAM_RECORD_TIMING_SEG       0x07        ////ʱ�α����¼����ݼ�¼
#define PROGRAM_RECORD_TIMING_ZONE      0x08        ////ʱ�������¼����ݼ�¼
#define PROGRAM_RECORD_WEEK_REST            0x09        ////�����ձ���¼����ݼ�¼
#define PROGRAM_RECORD_HOLIDAY          0x10        ////�ڼ��ձ���¼����ݼ�¼
#define PROGRAM_RECORD_ACTIVE_COM       0x11        ////�й���Ϸ�ʽ�����ֱ���¼�
#define PROGRAM_RECORD_REACTIVE_COM1    0x12        ////�޹����1��ʽ�����ֱ���¼����ݼ�¼
#define PROGRAM_RECORD_REACTIVE_COM2    0x13        ////�޹����2��ʽ�����ֱ���¼����ݼ�¼
#define PROGRAM_RECORD_BALANCE_DAY      0x14        ////�����ձ���¼����ݼ�¼
#define PROGRAM_RECORD_RELAY_ON         0x15        ////�̵�����ͨ�¼����ݼ�¼
#define PROGRAM_RECORD_RELAY_OFF            0x16        ////�̵����Ͽ��¼����ݼ�¼





typedef struct
{
    uchar EvenType;    /////�¼�����,
    ulong ID;  /////ͨ��ID,(û��ID�ı�̸�λ��FFFFFF����,��λΪ������)
    ulong HanderNum;  ////�����ߴ���,
    uchar CommNo;  ///ͨ��ͨ������
    uchar CommType;  ///��Լ����.
}STR_PROGRAM_RECORD_INDATA; 

//////��������,��������,���ݳ���,
EVENT_PROGRAM_EXT u16 EvenProgramRecord(STR_PROGRAM_RECORD_INDATA CommProgramdata,uchar*Src,u16 Lenth);


EVENT_PROGRAM_EXT void EventProgramRecordReset(void);

EVENT_PROGRAM_EXT uchar ucProgramPoint; //����¼���¼״̬(0δ��¼��1�Ѿ���¼��
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
EVENT_PROGRAM_EXT void CardProgramRecord(CARD_PROGRAM_RECORD_STRUCT* dataDI);
#endif
EVENT_PROGRAM_EXT void SpringStartTotalCommRecord(uchar type);

EVENT_PROGRAM_EXT void ProgramPointSet(uchar isSet);

#endif
