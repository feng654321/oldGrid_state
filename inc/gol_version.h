#ifndef __GOL_VERSION_H__
#define __GOL_VERSION_H__

#define METER_CON_INF_STR_LENGTH    (32)
typedef  enum
{
    METER_SW_VER_INF_ID     =0,         // AA ����汾      AA
    METER_BUILT_TIME_ID     =1,         // AA �̼�����ʱ��  AA
    METER_SW_CON_INF1_ID    =2,         // AA ������Ϣ1     AA
    METER_PROTOCOL_VER_ID   =3,         // AA Э��汾��    AA
    METER_FACTORY_INF_ID    =4,         // AA ������Ϣ      AA
    METER_INF_CHECKINF_ID   =5,         // AA У����Ϣ      AA
    METER_TYPE_INF_ID       =6,         // AA ����ͺ�      AA
    METER_MAX_NUM
}EN_WARE_INF;

extern const uchar TB_CON_METER_WARE_INF[][METER_CON_INF_STR_LENGTH];

#endif

