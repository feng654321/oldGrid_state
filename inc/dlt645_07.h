//============================================================================
//  File Name: Dlt645_07.h
//
//  Copyright PAX Hangzhou 2011.  All rights reserved.
//
//  Description:
//      The define information of DLT645-07
//
//  Modification History:
//      $Id:  Exp $
//      $Log: $
//      Revision 1.0 Create by Taozhiguo in 2011.04.28
//============================================================================
#ifndef __DLT645_07_H__
#define __DLT645_07_H__

#undef COMMON_EXT
#ifdef __AP_METER_C__
#define COMMON_EXT
#else
#define COMMON_EXT  extern
#endif

#define DLT_RET_SUCC            0x00        //������� �ɹ�����
#define DLT_RET_ERR             0xFF        //��������
#define DLT_RET_UNSUPPORT       0xFE        //�˲�����֧�ֻ����ݲ�����
#define DLT_RET_UNFINISHED      0xFA        //���鱾��δ���
#define DLT_RET_UNFINISHED2     0xFB        //��������汾���Ѿ���ɣ����ǿ��ܶ�Ӧ�ĵײ��������ȴ�
#define DLT_RET_NO_HAPPEN       0xF0        //δ���� �� ���账��

#define DLT_METER_ADDR_LEN      (6)         //��Ƶ�ַ����

#define DLT_METER_HORMANIC_MAX  (21)        //г������

#define DLT_SEASON_TABLE_MAX    (14)        //����ʱ�����ʱ����
#define DLT_DAY_TABLE_MAX       (8)         //����ʱ�α��ʱ�α���
#define DLT_DAY_PIECE_MAX       (14)        //����ʱ�α��е�ʱ����
#if (CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE_ENABLE == CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE)
#define DLT_PRICE_NUM_MAX       (4)        //���׷��ʱ�ķ����� ���֧�ַ�����      //(14)    //64
#else
#define DLT_PRICE_NUM_MAX       (14)        //���׷��ʱ�ķ����� ���֧�ַ�����      //(14)    //64
#endif
#define DLT_STEP_NUM_MAX        (14)        //���׽�����
#define DLT_HOLIDAY_NUM_MAX     (254)       //����������Ŀ

#define DLT_DAY_PIECE_DATA_LEN          (3)         //ʱ�����ݵĳ���(hhmm+price_index)
#define DLT_DAY_TABLE_DATA_LEN          (DLT_DAY_PIECE_DATA_LEN * DLT_DAY_PIECE_MAX)    //������ʱ�α�ĳ���
#define DLT_DAY_TABLE_SHEET_DATA_LEN    (DLT_DAY_TABLE_DATA_LEN * DLT_DAY_TABLE_MAX)    //������ʱ�α�ĳ���

//�����������������������(�����й��������й�������޹�1������޹�2���޹�1~4����)
#define DLT_FREEZE_KWH_TYPE_NUM         (8)
//������������������������(�����й����������������ʱ�䡢�����й����������������ʱ��)
#define DLT_FREEZE_DEMAND_TYPE_NUM      (2)

extern const u8 ConWeekDayWordTable[8];
//��ǰʱ�α���������ǹ�Լ״̬��
#define DLT_PRICE_SWITCH_MODE_SEASON    0x00
#define DLT_PRICE_SWITCH_MODE_RESET     0x01
#define DLT_PRICE_SWITCH_MODE_HOLIDAY   0x02

typedef union
{
    u32 ID;
    u8  id[4];
    union
    {
        u8 id0;
        u8 id1;
        u8 id2;
        u8 id3;
    }idu __attribute__((__aligned__(1)));
}DLT_07_ID;
#if 1
//__LITTLE_ENDIAN__
#define DLT_IDX0        0
#define DLT_IDX1        1
#define DLT_IDX2        2
#define DLT_IDX3        3
#define DLT_ID0(ID)     ((u8)(ID))
#define DLT_ID1(ID)     ((u8)((ID)>>8))
#define DLT_ID2(ID)     ((u8)((ID)>>16))
#define DLT_ID3(ID)     ((u8)((ID)>>24))
#else
//__BIG_ENDIAN__
#define DLT_IDX3        0
#define DLT_IDX2        1
#define DLT_IDX1        2
#define DLT_IDX0        3
#define DLT_ID3(ID)     ((u8)(ID))
#define DLT_ID2(ID)     ((u8)((ID)>>8))
#define DLT_ID1(ID)     ((u8)((ID)>>16))
#define DLT_ID0(ID)     ((u8)((ID)>>24))
#endif

//�¼������ۻ�ʱ���ʼ��
//#define EVENT_CONTINUE_TIME_START_INIT(continue_time, check_time)     continue_time+=check_time
#define EVENT_CONTINUE_TIME_START_INIT(continue_time, check_time)     continue_time=0

COMMON_EXT u8 isIDNew(u32 ID);
#ifdef  _DISPLAY_
COMMON_EXT u8 SymbolGetECData(STR_DISPLAYSYMBOL *sym, u32 ID, u8 idSerialNumber, u8 *ucDLen, u8 *dataType);
COMMON_EXT u8 SymbolGetMDData(STR_DISPLAYSYMBOL *sym, u32 ID, u8 idSerialNumber, u8 *ucDLen, u8 *dataType);
COMMON_EXT u8 SymbolGetVRData(STR_DISPLAYSYMBOL *sym, u32 ID, u8 idSerialNumber, u8 *ucDLen, u8 *dataType);
#endif
COMMON_EXT u8 GetECDataByID(u8 *pData, u16 *ucLen, u32 ID, u16 ulBufLen);
COMMON_EXT u8 GetMDDataByID(u8 *pData, u16 *ucLen, u32 ID, u16 ulBufLen);
COMMON_EXT u8 GetVRDataByID(u8 *pData, u16 *ucLen, u32 ID, u16 ulBufLen);
COMMON_EXT u8 VariableParaToFormat(u32 ID,u8 Lenth,u8 *Dest);

COMMON_EXT void EventMinTimeAdd(void);

#endif

