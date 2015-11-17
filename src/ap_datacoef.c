//============================================================================
//  File Name: ap_datacoef.h
//
//  Copyright PAX Hangzhou 2011.  All rights reserved.
//
//  Description:
//      �����йصĴ���������
//
//  Modification History:
//      $Id:  Exp $
//      $Log: $
//      Revision 1.0 Create by Taozhiguo in 2011.04.28
//============================================================================
#ifndef __AP_DATACOEF_C__
#define __AP_DATACOEF_C__
#include "common.h"

#define CONFIG_METER_COEF_RESUME_3COPY  GAL_YES
#define CON_COEFCHECK_ADD_COEF      0   //(0x33)
#define FIRST_COPY_COEF_START       (EPL_COEF_DATA_START)
#define FIRST_COPY_COEF_END         (EPL_COEF_DATA_END)
#define COEF_LEN                    (EPL_COEF_DATA_END - EPL_COEF_DATA_START)
#if(CONFIG_METER_COEF_RESUME_3COPY == GAL_YES)
#define SECOND_COPY_COEF_START      (BAK_COEF_DATA_START)
#define SECOND_COPY_COEF_END        (SECOND_COPY_COEF_START + COEF_LEN)
#define SECOND_COPY_ADDR_GET(x)     (SECOND_COPY_COEF_START+(x-FIRST_COPY_COEF_START))
#define THIRD_COPY_COEF_START       (FIRST_COPY_COEF_START)
#define THIRD_COPY_COEF_END         (FIRST_COPY_COEF_END)
#define SECOND_COPY_COEF_ADD_COEF   0x00
#define THIRD_COPY_COEF_ADD_COEF    0x33
#endif

typedef struct
{
    u16    CoefLogicAddr;
    u16    UseAddrType:1;
    u16    CoefType:1;
    u16    CoefLen:14;
    ulong   CoefUseAddr;
}ST_COEF_PARRM;

#define COEF_BCD            1
#define COEF_HEX            0
#define COEF_RAMV           0
#define COEF_FUNC           1

#define COEF_ADDR_PHY_TO_LOGIC(PhyAddr)             (PhyAddr-FIRST_COPY_COEF_START)
#define COEF_ADDR_LOGIC_TO_PHY(LogicAddr)           (LogicAddr+FIRST_COPY_COEF_START)
#define COEFPARA(saveaddr,useaddr,utype,dt,len)     ((u16)COEF_ADDR_PHY_TO_LOGIC(saveaddr)), utype,dt,len, (ulong)useaddr  
//���еĲ����б�
const ST_COEF_PARRM TB_DATACOEF_TABLE[] = 
{
    {COEFPARA(EPL_USER_NUMBER,                       RAM_USER_NUMBER,                    COEF_RAMV, COEF_BCD, 6)}, // �û���
    {COEFPARA(EPL_USER_COMM_ADDR,                    RAM_USER_COMM_ADDR,                 COEF_RAMV, COEF_BCD, 6)}, // �û���ַ(ͨѶ��ַ)
    {COEFPARA(EPL_USER_ID,                           RAM_USER_ID,                        COEF_RAMV, COEF_BCD, 6)}, // �û��ֺ�(���)
    {COEFPARA(EPL_USER_ASSET,                        RAM_USER_ASSET,                     COEF_RAMV, COEF_HEX, 32)}, // �ʲ�������(ASCII��)
    {COEFPARA(EPL_USER_CLIENT,                       RAM_USER_CLIENT,                    COEF_RAMV, COEF_BCD, 6)}, // NNNNNNNNNNNN �ͻ����
    {COEFPARA(EPL_CHARACTER_METER_RUN,               RAM_CHARACTER_METER_RUN,            COEF_RAMV, COEF_HEX, 1)}, // �������������
    {COEFPARA(EPL_CHARACTER_ACTIVE,                  RAM_CHARACTER_ACTIVE,               COEF_RAMV, COEF_HEX, 1)}, // �й���Ϸ�ʽ������
    {COEFPARA(EPL_CHARACTER_REACTIVE01,              RAM_CHARACTER_REACTIVE01,           COEF_RAMV, COEF_HEX, 1)}, // �޹���Ϸ�ʽ1������
    {COEFPARA(EPL_CHARACTER_REACTIVE02,              RAM_CHARACTER_REACTIVE02,           COEF_RAMV, COEF_HEX, 1)}, // �޹���Ϸ�ʽ2������
    {COEFPARA(EPL_IR_MODULATOR_BAUDRATE,             RAM_IR_MODULATOR_BAUDRATE,          COEF_RAMV, COEF_HEX, 1)}, // �����ͺ�����ͨ������������
    {COEFPARA(EPL_IR_CONTACT_BAUDRATE,               RAM_IR_CONTACT_BAUDRATE,            COEF_RAMV, COEF_HEX, 1)}, // �Ӵ�ʽ������ͨ������������
    {COEFPARA(EPL_COMM485_01_BAUDRATE,               RAM_COMM485_01_BAUDRATE,            COEF_RAMV, COEF_HEX, 1)}, // ͨѶ��1ͨ������������
#if(CONFIG_METER_NO2COMM_MODE_RS485==CONFIG_METER_NO2COMM_MODE)
    {COEFPARA(EPL_COMM485_02_BAUDRATE,               RAM_COMM485_02_BAUDRATE,            COEF_RAMV, COEF_HEX, 1)}, // ͨѶ��2ͨ������������
#endif
    {COEFPARA(EPL_CHARACTER_REST_DAY,                RAM_CHARACTER_REST_DAY,             COEF_RAMV, COEF_HEX, 1)}, // ������������
    {COEFPARA(EPL_CHARACTER_REST_DAYNO,              RAM_CHARACTER_REST_DAYNO,           COEF_RAMV, COEF_BCD, 1)}, // �����ղ��õ���ʱ�α��
    {COEFPARA(EPL_CHARACTER_CHARGE_MODE,             RAM_CHARACTER_CHARGE_MODE,          COEF_RAMV, COEF_HEX, 1)}, // ���ɼ�¼ģʽ��
    {COEFPARA(EPL_CHARACTER_FREEZE_EVERYTIME_MODE,   RAM_CHARACTER_FREEZE_EVERYTIME_MODE,COEF_RAMV, COEF_HEX, 1)}, // ��ʱ��������ģʽ��
    {COEFPARA(EPL_CHARACTER_FREEZE_INSTANT_MODE,     RAM_CHARACTER_FREEZE_INSTANT_MODE,  COEF_RAMV, COEF_HEX, 1)}, // ˲ʱ��������ģʽ��
    {COEFPARA(EPL_CHARACTER_FREEZE_RESTORE_MODE,     RAM_CHARACTER_FREEZE_RESTORE_MODE,  COEF_RAMV, COEF_HEX, 1)}, // Լ����������ģʽ��
    {COEFPARA(EPL_CHARACTER_FREEZE_EVERYHOUR_MODE,   RAM_CHARACTER_FREEZE_EVERYHOUR_MODE,COEF_RAMV, COEF_HEX, 1)}, // ���㶳������ģʽ��
    {COEFPARA(EPL_CHARACTER_FREEZE_EVERYDAY_MODE,    RAM_CHARACTER_FREEZE_EVERYDAY_MODE, COEF_RAMV, COEF_HEX, 1)}, // �ն�������ģʽ��
    {COEFPARA(EPL_CHARACTER_FREEZE_EVERYHOUR_STARTTIME, RAM_CHARACTER_FREEZE_EVERYHOUR_STARTTIME,    COEF_RAMV, COEF_BCD, 5)}, // YYMMDDhhmm ���㶳����ʼʱ��
    {COEFPARA(EPL_CHARACTER_FREEZE_EVERYHOUR_INTERVAL, RAM_CHARACTER_FREEZE_EVERYHOUR_INTERVAL,      COEF_RAMV, COEF_BCD, 1)}, // NN ���㶳��ʱ����
    {COEFPARA(EPL_CHARACTER_FREEZE_EVERYDAY_TIME,    RAM_CHARACTER_FREEZE_EVERYDAY_TIME, COEF_RAMV, COEF_BCD, 2)}, // hhmm �ն���ʱ��
    {COEFPARA(EPL_CHARGE_RECORD_START_TIME,          RAM_CHARGE_RECORD_START_TIME,       COEF_RAMV, COEF_BCD, 4)}, // MMDDHHMM ���ɼ�¼��ʼʱ��
    {COEFPARA(EPL_CHARGE_RECORD_1_TIME,              RAM_CHARGE_RECORD_1_TIME,           COEF_RAMV, COEF_BCD, 2)}, // MM ��1�ฺ�ɼ�¼���ʱ��
    {COEFPARA(EPL_CHARGE_RECORD_2_TIME,              RAM_CHARGE_RECORD_2_TIME,           COEF_RAMV, COEF_BCD, 2)}, // MM ��2�ฺ�ɼ�¼���ʱ��
    {COEFPARA(EPL_CHARGE_RECORD_3_TIME,              RAM_CHARGE_RECORD_3_TIME,           COEF_RAMV, COEF_BCD, 2)}, // MM ��3�ฺ�ɼ�¼���ʱ��
    {COEFPARA(EPL_CHARGE_RECORD_4_TIME,              RAM_CHARGE_RECORD_4_TIME,           COEF_RAMV, COEF_BCD, 2)}, // MM ��4�ฺ�ɼ�¼���ʱ��
    {COEFPARA(EPL_CHARGE_RECORD_5_TIME,              RAM_CHARGE_RECORD_5_TIME,           COEF_RAMV, COEF_BCD, 2)}, // MM ��5�ฺ�ɼ�¼���ʱ��
    {COEFPARA(EPL_CHARGE_RECORD_6_TIME,              RAM_CHARGE_RECORD_6_TIME,           COEF_RAMV, COEF_BCD, 2)}, // MM ��6�ฺ�ɼ�¼���ʱ��
    {COEFPARA(EPL_BALANCE_DAY_NUM,                   RAM_BALANCE_DAY_NUM,                COEF_RAMV, COEF_BCD, 1)}, // NN ÿ�½���������
    {COEFPARA(EPL_BALANCE_DAY_01,                    RAM_BALANCE_DAY_01,                 COEF_RAMV, COEF_BCD, 2)}, // DDHH ÿ�µ�1������(9999����δ���ô˽�����)
    {COEFPARA(EPL_BALANCE_DAY_02,                    RAM_BALANCE_DAY_02,                 COEF_RAMV, COEF_BCD, 2)}, // DDHH ÿ�µ�2������(9999����δ���ô˽�����)
    {COEFPARA(EPL_BALANCE_DAY_03,                    RAM_BALANCE_DAY_03,                 COEF_RAMV, COEF_BCD, 2)}, // DDHH ÿ�µ�3������(9999����δ���ô˽�����)
    {COEFPARA(EPL_COEF_MAX_KWH_F,                    RAM_COEF_MAX_KWH_F,                 COEF_RAMV, COEF_BCD, 3)}, // XX.XXXX �����й���������ֵ
    {COEFPARA(EPL_COEF_MAX_KWH_R,                    RAM_COEF_MAX_KWH_R,                 COEF_RAMV, COEF_BCD, 3)}, // XX.XXXX �����й���������ֵ
    {COEFPARA(EPL_COEF_VOLTAGE_LIMIT_UPPER,          MoniterParaInit,                    COEF_FUNC, COEF_BCD, 2)}, // XXX.X ��ѹ����ֵ
    {COEFPARA(EPL_COEF_VOLTAGE_LIMIT_LOWER,          MoniterParaInit,                    COEF_FUNC, COEF_BCD, 2)}, // XXX.X ��ѹ����ֵ
    {COEFPARA(EPL_COEF_FREEZE_TIME,                  RAM_COEF_FREEZE_TIME,               COEF_RAMV, COEF_BCD, 4)}, // mmhhDDMM ԤԼ����ʱ��

    {COEFPARA(EPL_COEF_LOSS_VOLTAGE_CONDITION,       LossVoltageParaInit,                COEF_FUNC, COEF_BCD, (8))},// ʧѹ�ж�����
    {COEFPARA(EPL_COEF_DOWN_VOLTAGE_CONDITION,       DownVoltageParaInit,                COEF_FUNC, COEF_BCD, (3))},// Ƿѹ�ж�����
    {COEFPARA(EPL_COEF_OVER_VOLTAGE_CONDITION,       OverVoltageParaInit,                COEF_FUNC, COEF_BCD, (3))},// ��ѹ�ж�����
    {COEFPARA(EPL_COEF_CUT_VOLTAGE_CONDITION,        CutVoltageParaInit,                 COEF_FUNC, COEF_BCD, (6))},// �����ж�����
    {COEFPARA(EPL_COEF_UNBALANCE_VOLTAGE_CONDITION,  UnbalanceVoltageParaInit,           COEF_FUNC, COEF_BCD, (3))},// ��ѹ��ƽ���ж�����
    {COEFPARA(EPL_COEF_UNBALANCE_CURRENT_CONDITION,  UnbalanceCurrentParaInit,           COEF_FUNC, COEF_BCD, (3))},// ������ƽ���ж�����
    {COEFPARA(EPL_COEF_LOSS_CURRENT_CONDITION,       LossCurrentParaInit,                COEF_FUNC, COEF_BCD, (9))},// ʧ���ж�����
    {COEFPARA(EPL_COEF_OVER_CURRENT_CONDITION,       OverCurrentParaInit,                COEF_FUNC, COEF_BCD, (3))},// �����ж�����
    {COEFPARA(EPL_COEF_CUT_CURRENT_CONDITION,        CutCurrentParaInit,                 COEF_FUNC, COEF_BCD, (6))},// �����ж�����
    {COEFPARA(EPL_COEF_REVERSEPOWER_CONDITION,       ReversePowerParaInit,               COEF_FUNC, COEF_BCD, (4))},// ���������ж�����
    {COEFPARA(EPL_COEF_OVER_KW_CONDITION,            OverPowerParaInit,                  COEF_FUNC, COEF_BCD, (4))},// �����ж�����

    {COEFPARA(EPL_COEF_MONITOR_VOLTAGE_CONDITION,    MoniterParaInit,                    COEF_FUNC, COEF_BCD, (4))},// ��ѹ�����ж�����
    {COEFPARA(EPL_COEF_DEMAND_OVER_CONDITION,        DemandOverParaInit,                 COEF_FUNC, COEF_BCD, (7))},// ���������ж�����
    {COEFPARA(EPL_COEF_OVERTOTALCOS_CONDITION,       OverTotalCosParaInit,               COEF_FUNC, COEF_BCD, (3))},// �ܹ��������ж�����
    {COEFPARA(EPL_COEF_UNBALANCE_SEVERITY_CURRENT_CONDITION,   UnbalanceCurrentParaInit, COEF_FUNC, COEF_BCD, (3))},// �������ز�ƽ���ж�����
	{COEFPARA(EPL_COEF_ALARM_SPEEK,                  RAM_COEF_ALARM_SPEEK,               COEF_RAMV, COEF_HEX, (20))},// ������ʾ����������
    
    {COEFPARA(EPL_COEF_PROGRAM_TIME,                 RAM_COEF_PROGRAM_TIME,              COEF_RAMV, COEF_BCD, 2)}, // NN �� ���ά��ʱ��
    {COEFPARA(EPL_COEF_DISPLAY_MODE_CHANGE_TIME,     RAM_COEF_DISPLAY_MODE_CHANGE_TIME,  COEF_RAMV, COEF_BCD, 2)}, // NNNN�� �����л�ʱ��
    {COEFPARA(EPL_COEF_REMOTE_WAKEUP_ENABLE,         RAM_COEF_REMOTE_WAKEUP_ENABLE,      COEF_RAMV, COEF_BCD, 1)}, // NN ���⻽��ģʽ
    {COEFPARA(EPL_COEF_POWERDOWN_ALLLOSSVOLTAGE_CONDITION,  RAM_COEF_POWERDOWN_ALLLOSSVOLTAGE_CONDITION,    COEF_RAMV, COEF_BCD, 5)}, // XXX.XV+XXX.XXXA ȫʧѹ�ж�����(ͣ��)
#if((CONFIG_METER_TYPE_SD39C==CONFIG_METER_TYPE) || (CONFIG_METER_AREA_MODE == CONFIG_METER_AREA_MODE_SOUTHGRID))
    {COEFPARA(EPL_COEF_CLR_METER_ENABLE_TIMES,       RAM_COEF_CLR_METER_ENABLE_TIMES,    COEF_RAMV, COEF_HEX, 1)},// 1 byte  BCD ���������������(��������)
#endif
    {COEFPARA(EPL_DEMAND_CYCLE_TIME,                 DemandParaInit,                     COEF_FUNC, COEF_BCD, (2))},
    {COEFPARA(EPL_COEF_2SEASONCHANGE_TIME,           RAM_COEF_2SEASONCHANGE_TIME,        COEF_RAMV, COEF_BCD, 5)}, // YYMMDDHHMM ����ʱ�����л�ʱ��
    {COEFPARA(EPL_COEF_2DAYTABLECHANGE_TIME,         RAM_COEF_2DAYTABLECHANGE_TIME,      COEF_RAMV, COEF_BCD, 5)}, // YYMMDDHHMM ����ʱ�α��л�ʱ��
    {COEFPARA(EPL_COEF_STEPPRICE_CHANGETIME,         RAM_COEF_STEPPRICE_CHANGETIME,      COEF_RAMV, COEF_BCD, 5)}, // YYMMDDHHMM ���׽��ݱ��л�ʱ��(�л���,�Զ�����)
    {COEFPARA(EPL_COEF_PERIODPRICE_CHANGETIME,       RAM_COEF_PERIODPRICE_CHANGETIME,    COEF_RAMV, COEF_BCD, 5)}, // YYMMDDHHMM ���׷��ʵ���л�ʱ��(�л���,�Զ�����)
    {COEFPARA(EPL_COEF_SEASONTABLE_MAX_NUM,          RAM_COEF_SEASONTABLE_MAX_NUM,       COEF_RAMV, COEF_BCD, 1)}, // XX ��ʱ����PС��14
    {COEFPARA(EPL_COEF_DAYTABLE_MAX_NUM,             RAM_COEF_DAYTABLE_MAX_NUM,          COEF_RAMV, COEF_BCD, 1)}, // XX ��ʱ�α���QС��8
    {COEFPARA(EPL_COEF_PERIOD_MAX_NUM,               RAM_COEF_PERIOD_MAX_NUM,            COEF_RAMV, COEF_BCD, 1)}, // XX ��ʱ����(ÿ���л���)mС��14
    {COEFPARA(EPL_COEF_PRICE_MAX_NUM,                RAM_COEF_PRICE_MAX_NUM,             COEF_RAMV, COEF_BCD, 1)}, // XX ������kС��63
    {COEFPARA(EPL_COEF_HOLIDAY_MAX_MUN,              RAM_COEF_HOLIDAY_MAX_MUN,           COEF_RAMV, COEF_BCD, 2)}, // XXXX ����������nС��254

    {COEFPARA(EPL_COEF_HUMOROUS_MAX_NUM,             RAM_COEF_HUMOROUS_MAX_NUM,          COEF_RAMV, COEF_BCD, 1)}, // XX г����������
    {COEFPARA(EPL_COEF_STEP_NUM,                     RAM_COEF_STEP_NUM,                  COEF_RAMV, COEF_BCD, 1)}, // XX ���ݸ���
    {COEFPARA(EPL_COEF_AUTO_TURNPAGE_NUM,            RAM_COEF_AUTO_TURNPAGE_NUM,         COEF_RAMV, COEF_BCD, 1)}, // XX �Զ�ѭ����ʾ����
    {COEFPARA(EPL_COEF_TURNPAGE_TIME,                RAM_COEF_TURNPAGE_TIME,             COEF_RAMV, COEF_BCD, 1)}, // XX ÿ����ʾʱ��
    {COEFPARA(EPL_COEF_POWER_POINT_NUM,              RAM_COEF_POWER_POINT_NUM,           COEF_RAMV, COEF_BCD, 1)}, // XX ��ʾ����С��λ��

    {COEFPARA(EPL_COEF_DEMAND_POINT_NUM,             RAM_COEF_DEMAND_POINT_NUM,          COEF_RAMV, COEF_BCD, 1)},// XX ��ʾ����(�������)С��λ��
    {COEFPARA(EPL_COEF_KEY_TURNPAGE_NUM,             RAM_COEF_KEY_TURNPAGE_NUM,          COEF_RAMV, COEF_BCD, 1)},// XX ����ѭ����ʾ����
    {COEFPARA(EPL_COEF_PT_NUM,                       RAM_COEF_PT_NUM,                    COEF_RAMV, COEF_BCD, 3)},// XXXXXX �������������
    {COEFPARA(EPL_COEF_CT_NUM,                       RAM_COEF_CT_NUM,                    COEF_RAMV, COEF_BCD, 3)},// XXXXXX ��ѹ���������
    {COEFPARA(EPL_SEASON1_DAYTABLE_CHANGE01,         RAM_SEASON1_DAYTABLE_CHANGE01,      COEF_RAMV, COEF_BCD, 42)},// MMDDNN ��һ�׵�1ʱ����ʼ���ڼ���ʱ�α��
    {COEFPARA(EPL_SEASON1_DAYTABLE1_PERIOD01,        RAM_SEASON1_DAYTABLE1_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN ��һ�׵�1��ʱ�α��1ʱ����ʼʱ�估���ʺ�
    {COEFPARA(EPL_SEASON1_DAYTABLE2_PERIOD01,        RAM_SEASON1_DAYTABLE2_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN ��һ�׵�2��ʱ�α��1ʱ����ʼʱ�估���ʺ�
    {COEFPARA(EPL_SEASON1_DAYTABLE3_PERIOD01,        RAM_SEASON1_DAYTABLE3_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN ��һ�׵�3��ʱ�α��1ʱ����ʼʱ�估���ʺ�
    {COEFPARA(EPL_SEASON1_DAYTABLE4_PERIOD01,        RAM_SEASON1_DAYTABLE4_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN ��һ�׵�4��ʱ�α��1ʱ����ʼʱ�估���ʺ�
    {COEFPARA(EPL_SEASON1_DAYTABLE5_PERIOD01,        RAM_SEASON1_DAYTABLE5_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN ��һ�׵�5��ʱ�α��1ʱ����ʼʱ�估���ʺ�
    {COEFPARA(EPL_SEASON1_DAYTABLE6_PERIOD01,        RAM_SEASON1_DAYTABLE6_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN ��һ�׵�6��ʱ�α��1ʱ����ʼʱ�估���ʺ�
    {COEFPARA(EPL_SEASON1_DAYTABLE7_PERIOD01,        RAM_SEASON1_DAYTABLE7_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN ��һ�׵�7��ʱ�α��1ʱ����ʼʱ�估���ʺ�
    {COEFPARA(EPL_SEASON1_DAYTABLE8_PERIOD01,        RAM_SEASON1_DAYTABLE8_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN ��һ�׵�8��ʱ�α��1ʱ����ʼʱ�估���ʺ�
    {COEFPARA(EPL_SEASON2_DAYTABLE_CHANGE01,         RAM_SEASON2_DAYTABLE_CHANGE01,      COEF_RAMV, COEF_BCD, 42)},// MMDDNN �ڶ��׵�1ʱ����ʼ���ڼ���ʱ�α��
    {COEFPARA(EPL_SEASON2_DAYTABLE1_PERIOD01,        RAM_SEASON2_DAYTABLE1_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN �ڶ��׵�1��ʱ�α��1ʱ����ʼʱ�估���ʺ�
    {COEFPARA(EPL_SEASON2_DAYTABLE2_PERIOD01,        RAM_SEASON2_DAYTABLE2_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN �ڶ��׵�2��ʱ�α��1ʱ����ʼʱ�估���ʺ�
    {COEFPARA(EPL_SEASON2_DAYTABLE3_PERIOD01,        RAM_SEASON2_DAYTABLE3_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN �ڶ��׵�3��ʱ�α��1ʱ����ʼʱ�估���ʺ�
    {COEFPARA(EPL_SEASON2_DAYTABLE4_PERIOD01,        RAM_SEASON2_DAYTABLE4_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN �ڶ��׵�4��ʱ�α��1ʱ����ʼʱ�估���ʺ�
    {COEFPARA(EPL_SEASON2_DAYTABLE5_PERIOD01,        RAM_SEASON2_DAYTABLE5_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN �ڶ��׵�5��ʱ�α��1ʱ����ʼʱ�估���ʺ�
    {COEFPARA(EPL_SEASON2_DAYTABLE6_PERIOD01,        RAM_SEASON2_DAYTABLE6_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN �ڶ��׵�6��ʱ�α��1ʱ����ʼʱ�估���ʺ�
    {COEFPARA(EPL_SEASON2_DAYTABLE7_PERIOD01,        RAM_SEASON2_DAYTABLE7_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN �ڶ��׵�7��ʱ�α��1ʱ����ʼʱ�估���ʺ�
    {COEFPARA(EPL_SEASON2_DAYTABLE8_PERIOD01,        RAM_SEASON2_DAYTABLE8_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN �ڶ��׵�8��ʱ�α��1ʱ����ʼʱ�估���ʺ�
    {COEFPARA(EPL_PERIODPRICE01_PRICE01,             RAM_PERIODPRICE01_PRICE01,          COEF_RAMV, COEF_BCD, 56)},// NNNN.NNNN ��һ�׷��ʵ��1
    {COEFPARA(EPL_PERIODPRICE02_PRICE01,             RAM_PERIODPRICE02_PRICE01,          COEF_RAMV, COEF_BCD, 56)},// NNNN.NNNN �ڶ��׷��ʵ��1
    {COEFPARA(EPL_STEP01_DATA01,                     RAM_STEP01_DATA01,                  COEF_RAMV, COEF_BCD, 56)},// NNNNNN.NN ��һ�׵�01����ֵ
    {COEFPARA(EPL_STEPPRICE01_PRICE01,               RAM_STEPPRICE01_PRICE01,            COEF_RAMV, COEF_BCD, 56)},// NNNN.NNNN ��һ�׽��ݵ��01
    {COEFPARA(EPL_STEP02_DATA01,                     RAM_STEP02_DATA01,                  COEF_RAMV, COEF_BCD, 56)},// NNNNNN.NN �ڶ��׵�01����ֵ
    {COEFPARA(EPL_STEPPRICE02_PRICE01,               RAM_STEPPRICE02_PRICE01,            COEF_RAMV, COEF_BCD, 56)},// NNNN.NNNN �ڶ��׽��ݵ��01
};

//��ǰ���Ĳ���������
u16 ucCoefTypeCheckPoint;          
//��ǰ���Ĳ���С���ͻ�������
uchar ucCoefPowerCheckTablePoint;   //���ڲ����� TB_DATACOEF_TABLE
uchar ucCoefPowerCheckAde7758;      //ר����7758���
uchar ucKwhDataCheckPoint;          //ר���ڵ������

/*==================================================================
//��������  CoefCheckMode
//���ߣ�    ���ι�
//���ڣ�    
//���ܣ�    ���� ����У��
//          �ڿ���ʱ���Ը��������ݽ����ض�У��
//�����������
//�����������
//����ֵ��  ��
//=================================================================*/
uchar CoefCheckMode(void)
{
    //static uchar ucCoefCheckMinute=0;
#define CON_COEFPOWERCHECK_ADEREG       0
#define CON_COEFPOWERCHECK_POWER        1
#define CON_COEFPOWERCHECK_COEF         2
#define CON_COEFPOWERCHECK_MAX          2

    u16 uiLen;
    const ST_COEF_PARRM* ptr;
    
    // AA    ǰ�����Ӳ�����  AA 
    if((RSOFT_RTC_SECOND<5)||(RSOFT_RTC_SECOND>0x55)||(0==RSOFT_RTC_MINUTE))
    {
        return DLT_RET_SUCC;
    }
    
    //if(ucCoefCheckMinute != RSOFT_RTC_MINUTE)
    {
        //ÿ���Ӳ�һ����������ɢ����У���Ƶ�ʣ�����ϵͳ����
        //ucCoefCheckMinute = RSOFT_RTC_MINUTE;
        //���ȼ��
        /*if(GAL_YES==ucCoefCheckDisplayReNewRequest)
        {
            ucCoefCheckDisplayReNewRequest=GAL_NO;
            CheckDisplayControl();
            return DLT_RET_SUCC;
        }*/
        //MTRACE("CoefCheck %d, %d, %d, %d\n", ucCoefTypeCheckPoint, ucCoefPowerCheckAde7758, ucKwhDataCheckPoint, ucCoefPowerCheckTablePoint);
        if(ucCoefTypeCheckPoint<CON_COEFPOWERCHECK_MAX)
        {
            ucCoefTypeCheckPoint++;
        }
        else
        {
            ucCoefTypeCheckPoint=0;
        }
        
        if((CON_COEFPOWERCHECK_COEF==ucCoefTypeCheckPoint))
        // AA   ���ϵͳ����  AA 
        {
            uiLen=sizeof(TB_DATACOEF_TABLE)/sizeof(ST_COEF_PARRM);
			//while(ucCoefPowerCheckTablePoint<uiLen)
			if(ucCoefPowerCheckTablePoint<uiLen)
			{
                ptr = &(TB_DATACOEF_TABLE[ucCoefPowerCheckTablePoint]);
                if(ptr->UseAddrType == COEF_FUNC)
                {
                    ((func)(ptr->CoefUseAddr))();
                }
                else
                {
                    if((ptr->CoefUseAddr+ptr->CoefLen) < CONST_RAM_LEN)
                    {
                        ReadCoefDataWithCheck(COEF_ADDR_LOGIC_TO_PHY(ptr->CoefLogicAddr), ptr->CoefLen, &RAM[ptr->CoefUseAddr], ptr->UseAddrType);
                    }
                }
				ucCoefPowerCheckTablePoint++;
			}
            else if((uiLen+1)==ucCoefPowerCheckTablePoint)
            {
                ProgFunctionLoad();
                ucCoefPowerCheckTablePoint++;
            }
            else if((uiLen+2)==ucCoefPowerCheckTablePoint)
            {
                //��øĳɷ�ƬУ��
                PriceSwitchModeParaInit();
                ucCoefPowerCheckTablePoint++;
            }     
            /*else if((uiLen+3)==ucCoefPowerCheckTablePoint)
            {
                CheckDisplayControl();
                ucCoefPowerCheckTablePoint++;
            } */    
            else
            {
                ucCoefPowerCheckTablePoint = 0;
            }
        }
#if 1           
        else if(CON_COEFPOWERCHECK_ADEREG==ucCoefTypeCheckPoint)
        // AA   ���ADE7758  AA 
        {
                if(1==CheckADE7758())
                {
                    ucCoefPowerCheckAde7758++;
                }
                else
                {
                    ucCoefPowerCheckAde7758=0;
                }
                if(ucCoefPowerCheckAde7758>30) 
                {
                    InitADMode(GAL_YES, GAL_NO);
                    ucCoefPowerCheckAde7758=0;
                }
        }
#endif
        else if((CON_COEFPOWERCHECK_POWER==ucCoefTypeCheckPoint))
        // AA   ���ϵͳ��������  AA 
        {
            //ucKwhErrEventRecordMode=CON_KWH_ERR_EVENT_RECORD_START;
            ucKwhDataCheckPoint++;
            if(ucKwhDataCheckPoint>=PT_KWH_TOTAL)
                ucKwhDataCheckPoint=0;
            if(KWH_CHECK_ALL_OK!=KwhPowerOnSafeCheck(ucKwhDataCheckPoint,TB_KWH_RESUME_CAN_SUB[ucKwhDataCheckPoint].stCanSub))
            {
                WritePower3Copy(ucKwhDataCheckPoint);
            }
            //ucKwhErrEventRecordMode=CON_KWH_ERR_EVENT_RECORD_END;
        }
		//ZD Ԥ����ģʽ���ڼ�������ר���У�����
/*
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
        else if((CON_COEFCARDCHECK_COEF==ucCoefTypeCheckPoint))
        {
            GetPrepayRunPara();
        }
#endif
*/
    }
    return DLT_RET_SUCC;

}

/*==================================================================
//��������  CoefPowerUpResume
//���ߣ�    ���ι�
//���ڣ�    
//���ܣ�    ���� ����У��Ͷ�ȡ
//���������isPowerUpInit:      1: Init when Power up
                                0: Others
//�����������
//����ֵ��  ��
//=================================================================*/
void CoefPowerUpResume(uchar isPowerUpInit)
{
    u16 uiIdx, uiLen;
    const ST_COEF_PARRM* ptr;

    uiLen=sizeof(TB_DATACOEF_TABLE)/sizeof(ST_COEF_PARRM);
    for(uiIdx=0; uiIdx<uiLen; uiIdx++)
    {
        ptr = &(TB_DATACOEF_TABLE[uiIdx]);
        if(ptr->UseAddrType == COEF_FUNC)
        {
            if(isPowerUpInit == 0)
            {
                //�����ָ���ʼ��ʱ�����������ɸ�ģ����Գ�ʼ��
                //�ǿ�����ʼ��ʱ����Ҫ������һ����ʼ��
                ((func)(ptr->CoefUseAddr))();
            }
        }
        else
        {
            if((ptr->CoefUseAddr+ptr->CoefLen) < CONST_RAM_LEN)
            {
                ReadCoefDataWithCheck(COEF_ADDR_LOGIC_TO_PHY(ptr->CoefLogicAddr), ptr->CoefLen, &RAM[ptr->CoefUseAddr], ptr->UseAddrType);
            }
        }
    }

#if(CONFIG_METER_STEP_MODE!=CONFIG_METER_STEP_MODE_ENABLE)
    RAM[RAM_COEF_STEP_NUM]=0;
#endif
}

/*==================================================================
//��������  WriteCoefDataWithSync
//���ߣ�    ���ι�
//���ڣ�    
//���ܣ�    �������ݱ���
//          �������ݱ��ݣ�ͬʱͬ��������������
//          ����ͬʱ������ʹ�õ���Ӧ����
//          Ŀǰ���� DataName ������EPL��ͷ(�л���ĳ��߼���ַ)��������ͨ��ַ����д��
//�����������
//�����������
//����ֵ��  ��
//=================================================================*/
uchar WriteCoefDataWithSync(const uchar *ucData, ulong DataName, u16 uiLen)
{
    uchar ret=DLT_RET_SUCC;
    
    if((DataName < FIRST_COPY_COEF_START) || ((DataName+uiLen) >= FIRST_COPY_COEF_END))
    {
        ret = WriteDataDirect(ucData, DataName, uiLen);
    }
    else
    {
        u16 uiIdx, uiDataUnitMax;
        ulong ulLogicAddr, ulLogicAddrMax;
        const ST_COEF_PARRM* ptr;
        
        //if(uiLen > 200)
        //    return DLT_RET_ERR;
        ret = WriteDataDirect(ucData, DataName, uiLen);
#if(GAL_YES==CONFIG_METER_COEF_RESUME_3COPY)
        ret = WriteDataDirect(ucData, SECOND_COPY_ADDR_GET(DataName), uiLen);
#endif   
        //MTRACE("COEF %d, 0x%08x, %d, %d\n", ret, SECOND_COPY_ADDR_GET(DataName), ucData[0], ucData[1]);
        //ʹ���еĲ�������
        uiDataUnitMax=sizeof(TB_DATACOEF_TABLE)/sizeof(ST_COEF_PARRM);
        ulLogicAddr = COEF_ADDR_PHY_TO_LOGIC(DataName);
        ulLogicAddrMax = COEF_ADDR_PHY_TO_LOGIC(DataName+uiLen);
        for(uiIdx=0; uiIdx<uiDataUnitMax; uiIdx++)
        {
            ptr = &(TB_DATACOEF_TABLE[uiIdx]);
            //��ַ����������
            if((ulLogicAddr >= ptr->CoefLogicAddr ) && (ulLogicAddr < (ptr->CoefLogicAddr+ptr->CoefLen)))
            {
                if(ptr->UseAddrType == COEF_FUNC)
                {
                    ((func)(ptr->CoefUseAddr))();
                }
                else
                {
                    if((ptr->CoefUseAddr+ptr->CoefLen) < CONST_RAM_LEN)
                    {
                        //ptr->CoefLen  or others ? Now, use ptr->CoefLen temply
                        ret = ReadCoefDataWithCheck(COEF_ADDR_LOGIC_TO_PHY(ptr->CoefLogicAddr), ptr->CoefLen, &RAM[ptr->CoefUseAddr], ptr->UseAddrType);
                    }
                }
                //����������һ��������
                ulLogicAddr += ptr->CoefLen;
                if(ulLogicAddr >= ulLogicAddrMax)
                {
                    return ret;
                }
            }
        }
    }
    return ret;
}

/*==================================================================
//��������  ReadCoefDataWithCheck
//���ߣ�    ���ι�
//���ڣ�    
//���ܣ�    �������ݶ�ȡ
//          �������ݶ�ȡ��ͬʱ�ο��Ƚ�����������
//          Ŀǰ���� DataName ������EPL��ͷ(�л���ĳ��߼���ַ)��������ͨ��ַ����д��
//�����������
//�����������
//����ֵ��  ��
//=================================================================*/
uchar ReadCoefDataWithCheck(ulong DataName, u16 uiLen, uchar* pSrc, uchar ucTestBcd)
{
    uchar ucTemp,ucValue;

    if((DataName < FIRST_COPY_COEF_START) || ((DataName+uiLen) >= FIRST_COPY_COEF_END))
    {
        //return DLT_RET_ERR;
        return ReadDataDirect(DataName, uiLen, pSrc);
    }
    
    if(uiLen > CON_WR_DATA_LEN_MAX)
        return DLT_RET_ERR;

    uchar ret,ret1;
    ret = ReadDataDirect(DataName, uiLen, pSrc);
#if(GAL_YES==CONFIG_METER_COEF_RESUME_3COPY)    
    if(uiLen > CON_WR_DATA_LEN_MAX)
    {
        ret1 = 0;
    }
    else
    {
        ret1 = ReadDataDirect(SECOND_COPY_ADDR_GET(DataName),  uiLen, &Wr_data[0]);
    }
    //MTRACE("%d, 0x%02X, %d, 0x%02X\n", ret, pSrc[0], ret1, Wr_data[0]);
    if((ret == 1) && (ret1 == 0))
    {
        return DLT_RET_SUCC;
    }
    else if((ret == 0) && (ret1 == 1)) 
    {
        memcpy(pSrc, &Wr_data[0], uiLen);
        return DLT_RET_SUCC;
    }
    else if((ret == 1) && (ret1 == 1))
    {
        ucValue = 1;
        for(ucTemp=0;ucTemp<uiLen;ucTemp++)
        {
            if(pSrc[ucTemp] != Wr_data[ucTemp])
            {
                ucValue=0;
                ucTemp=uiLen;
            }
        }
        // ���ݳ�����
        if(0==ucValue)
        {
            // �������e2p�����ݶ����ִ���ʱ�����ȿ�������
            if((0==ucTestBcd)||(uiLen==TestBcdNum(&pSrc[0], uiLen)))
            {
            }
            else
            {
                if((0==ucTestBcd)||(uiLen==TestBcdNum(&Wr_data[0], uiLen)))
                {
                    for(ucTemp=0;ucTemp<uiLen;ucTemp++)
                    {
                        pSrc[ucTemp]=Wr_data[ucTemp];
                    }
                }
                else
                {
                    return DLT_RET_ERR;
                }
            }
        }    
        return DLT_RET_SUCC;
    }
    else
    {
        return DLT_RET_ERR;
    }
#else    
    if(ret == 1)
        return DLT_RET_SUCC;
    else
        return DLT_RET_ERR;
#endif
}

/*==================================================================
//��������  GetSetHarmonicNumber
//���ߣ�    ���ι�
//���ڣ�    
//���ܣ�    ������õ�г���������
//�����������
//�����������
//����ֵ��  ��
//=================================================================*/
uchar GetSetHarmonicNumber(void)
{
#if(CONFIG_METER_HARMONIC_ENABLE == GAL_YES)    
    uchar TmpNum;
    ReadDataDirect(RAM_COEF_HUMOROUS_MAX_NUM,1,&TmpNum);  //�����õķ�����
    TmpNum=BCD_Byte(TmpNum);                              //BCD��תHEX��
    if(TmpNum>DLT_METER_HORMANIC_MAX)                     //���õķ�����������������
        TmpNum = DLT_METER_HORMANIC_MAX;                  //���õķ�����������������

    return (TmpNum);
#else
    return 0;
#endif
}
#endif

