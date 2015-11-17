//============================================================================
//  File Name: ap_meter.h
//
//  Copyright PAX Hangzhou 2011.  All rights reserved.
//
//  Description:
//      
//
//  Modification History:
//      $Id:  Exp $
//      $Log: $
//      Revision 1.0 Create by Taozhiguo in 2011.04.28
//============================================================================
#ifndef __AP_METER_H__
#define __AP_METER_H__

#undef COMMON_EXT
#ifdef __AP_METER_C__
#define COMMON_EXT
#else
#define COMMON_EXT  extern
#endif



//1 ������¼����Ͷ���
/*----------------------------------------------------------------------
        ���ι�:
    ������(������)�¼�����ԭ��:
    1����Ҫ�Ľ�����ʵʱ����ǰ;
    2�����ٵ���ǰ�����ٵ��ں�(������ܶ�25FLASH��ɾ��������);
    3��������ٲ�����Ե���Դ��ͬ�������Ż��ֿ����в�����
    4�����������������еĿ��Բ�ʵʱ�������ܶ��ģ�����������ü�һ���������ӱ���
    5���ۺϿ��ǡ��Ż�()��
    �������:
    1���������������¼��Ĵ���ֳ����ߺ͸���;
    2�����ߵ�������Ҫ���Ⱥ�����ִ�У����µ�����ʱ����������û��ִ����ϣ������¿�ʼ��
       ���������߱�������ִ����ɺ󣬱���ȴ�����������ɣ�
       ��������������(�����ȴ������������)ִ����󣬴˵�ǰ���������������ɣ��ͷŴ�������Դ���ȴ��µ�һ�����٣�
    3��������Ҫ���ɲ�̫��Ҫ�������������豸��������ɡ���ÿ��ʱ���У����������������ɵ�һ���̶Ⱥ���ܻ��ִ�У�
       �������������벻���¿�ʼ���������Ա���������ӵ������£����������л��ᱻִ�е���������ʱ�仹�Ǳ���ø�λ
       ��������ţ�����Ҫ����������ܹ�ִ�У�
       ������������������ʱ�����µ�ǰ��������ţ��Ա�ͳ�Ƶ��ڵ�ǰ������������ִ������һ��ʱ�������߽����ȴ���
----------------------------------------------------------------------*/
enum
{
    //MAIN_STEP_SECOND_TIMER,         //����붨ʱ������
    MAIN_STEP_POWER_GET,            //�����������ԭʼ���ݻ�ȡ
    MAIN_STEP_PRICE_SWITCH,         //�����л�
    MAIN_STEP_POWER_ADD,            //�����ۼ�
    MAIN_STEP_DEMAND,               //�������㡢һ���ж����������¼�(�漰FLASH����)
    MAIN_STEP_ALARM,                //�澯����
    MAIN_STEP_KEY,                  //��������
    MAIN_STEP_DISPLAY,              //��ʾ����ֻ�ǲ��������л��ȡ�������ʾ����ͨ��������أ������¼���ʵʱ������ʾ
    MAIN_STEP_PROGRAM_EVENT,        //����¼�
    MAIN_STEP_CLR_EVENT,            //���������¼�
    MAIN_STEP_TIME_ONE_SECOND,      //�������¼�(��ֲ��ԭ������)
    MAIN_STEP_EVENT_SECTIME_ADD,    //���¼�������ʱ���1
    MAIN_STEP_SLOW_START,           //�ø��߿�ʼ����һ���
    MAIN_STEP_IDLE1,                //�ø�������һ���
    MAIN_STEP_VAR1_UPDATE,          //˲ʱ��1����()
    MAIN_STEP_VAR2_UPDATE,          //˲ʱ��2����()
    //MAIN_STEP_COVER_OPEN,           //���\��ť�ǿ������
    MAIN_STEP_ALLLOSS_VOLTAGE,      //ȫʧѹ�¼����
    MAIN_STEP_POWER_DOWN,           //����ʱ����
    MAIN_STEP_AUX_POWER,            //������Դ������
    MAIN_STEP_AHHOUR,               //����Сʱͳ��
    MAIN_STEP_IDLE2,                //�ø�������һ���
    MAIN_STEP_IDLE3,                //�ø�������һ���
    MAIN_STEP_ANGEL,                //�Ƕȱ�������
    //MAIN_STEP_AD,                   //AD���
    MAIN_STEP_MONITOR,              //��ѹ�ϸ���ͳ��
    MAIN_STEP_IDLE4,                //�ø�������һ���
    MAIN_STEP_IDLE5,                //�ø�������һ���
    MAIN_STEP_IDLE6,                //�ø�������һ���
#if(CONFIG_METER_HARMONIC_ENABLE == GAL_YES)    
    MAIN_STEP_HARMONIC,             //г�����ݴ����ͳ��
#endif    
    MAIN_STEP_SAVE_DATA,            //���ݶ�ʱ����
    MAIN_STEP_WAIT_SLOW,            //���е���Ҫ���鶼���ֻ꣬Ϊ�ȴ����ٵ���Ҫ���¼�����
    MAIN_STEP_COEF_CHECK,           //������У��
    MAIN_STEP_MAX,                  //��ǰ���������������
};
enum
{
    SLOW_STEP_RESTORE,              //�����¼�(���з���ֲ��ȴ�������)
    SLOW_STEP_FREEZE,               //�����¼�(���з���ֲ��ȴ�������)
    SLOW_STEP_RECORD,               //���ɼ�¼
    SLOW_STEP_CUT_CURRENT,          //�����¼�����(�漰FLASH����)
    SLOW_STEP_CUT_VOLTAGE,          //�����¼�����(�漰FLASH����)
    SLOW_STEP_DOWN_VOLTAGE,         //Ƿѹ�¼�����(�漰FLASH����)
    SLOW_STEP_LOSS_VOLTAGE,         //ʧѹ�¼�����(�漰FLASH����)
    SLOW_STEP_LOSS_CURRENT,         //ʧ���¼�����(�漰FLASH����)
    SLOW_STEP_ORDER_CURRENT,        //�����������¼�����(�漰FLASH����)
    SLOW_STEP_ORDER_VOLTAGE,        //��ѹ�������¼�����(�漰FLASH����)
    SLOW_STEP_OVER_CURRENT,         //�����¼�����(�漰FLASH����)
    SLOW_STEP_OVER_POWER,           //�����¼�����(�漰FLASH����)
    SLOW_STEP_OVER_VOLTAGE,         //��ѹ�¼�����(�漰FLASH����)
    SLOW_STEP_REVERSE_POWER,        //���ʷ����¼�����(�漰FLASH����)
    SLOW_STEP_UNBALANCE_CURRENT,    //������ƽ���¼�����(�漰FLASH����)
    SLOW_STEP_UNBALANCE_VOLTAGE,    //��ѹ��ƽ���¼�����(�漰FLASH����)
    SLOW_STEP_OVER_TOTALCOS,        //�������������¼�����(�漰FLASH����)
    SLOW_STEP_MAX,                  //��ǰ����������ٵ���Ҫ��������
};

//1 ��ĵ�Դ״̬����
typedef enum
{
    METER_SYS_IDLE,                 //��ƿ�״̬        ----����̬
    METER_SYS_POWERON_INIT,         //����ϵ��ʼ��    ----����̬
    METER_SYS_POWEROFF_SAVE,        //��Ƶ��紦��      ----����̬
    METER_SYS_POWEROFF,             //��Ƶ���״̬      ----��̬
    METER_SYS_POWERON,              //����ϵ�����      ----��̬
}eMeterSysState;


#define MAX_TIME_PIECE_EACH_SECOND  (10)

//COMMON_EXT int ver;

COMMON_EXT ulong ulNowMinTime;
COMMON_EXT ulong ulNowSecTime;
COMMON_EXT ulong ulRunSecTime;

COMMON_EXT void MeterTaskInit(void);
COMMON_EXT void MeterTaskExit(void);
COMMON_EXT void Meter100msTask(void);
COMMON_EXT void MeterSecondEventSecTimeAdd(void);
COMMON_EXT void MeterEventMinTimeAdd(void);
COMMON_EXT void MeterTimeUpdateSimply(void);
COMMON_EXT uchar MeterTimeGet(uchar isTimePieceAdd);
COMMON_EXT void MeterSecondEvent(void);
COMMON_EXT void MeterPowerOff(void);
COMMON_EXT void MeterCmdOpStateSet(uchar isBusy);
COMMON_EXT uchar MeterCmdOpStateGet(void);

//COMMON_EXT void boad_main_version_get(void);

//��Ƶ�ϵͳ״̬����
COMMON_EXT eMeterSysState eMeterState;
#define IfPowerStateOn()    (eMeterState == METER_SYS_POWERON)
#define IfPowerStateOff()    (eMeterState != METER_SYS_POWERON)

extern uchar get_cur_uart_port_no(void);
#endif

