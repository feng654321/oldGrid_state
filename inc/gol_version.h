#ifndef __GOL_VERSION_H__
#define __GOL_VERSION_H__

#define METER_CON_INF_STR_LENGTH    (32)
typedef  enum
{
    METER_SW_VER_INF_ID     =0,         // AA 软件版本      AA
    METER_BUILT_TIME_ID     =1,         // AA 固件编译时间  AA
    METER_SW_CON_INF1_ID    =2,         // AA 配置信息1     AA
    METER_PROTOCOL_VER_ID   =3,         // AA 协议版本号    AA
    METER_FACTORY_INF_ID    =4,         // AA 厂家信息      AA
    METER_INF_CHECKINF_ID   =5,         // AA 校验信息      AA
    METER_TYPE_INF_ID       =6,         // AA 电表型号      AA
    METER_MAX_NUM
}EN_WARE_INF;

extern const uchar TB_CON_METER_WARE_INF[][METER_CON_INF_STR_LENGTH];

#endif

