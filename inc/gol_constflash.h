
#define GET_TRUE_ADDR_BY_INDEX(index)   (0xA1000000+index)
#define CFL_METER_ASCII_INF_NO_BEGIN    GET_TRUE_ADDR_BY_INDEX(0)    // 32 byte ASCII  ��������汾��(ASCII��)
#define CFL_METER_ASCII_SOFT_NO         GET_TRUE_ADDR_BY_INDEX(METER_SW_VER_INF_ID)    // 32 byte ASCII  ��������汾��(ASCII��)
#define CFL_METER_ASCII_BTTIME_NO       GET_TRUE_ADDR_BY_INDEX(METER_BUILT_TIME_ID)    // 32 byte ASCII  ��������汾��(ASCII��)
#define CFL_METER_ASCII_METER_NO        GET_TRUE_ADDR_BY_INDEX(METER_TYPE_INF_ID)      // 10 byte ASCII  ����ͺ�(ASCII��)
#define CFL_METER_ASCII_COMM_NO         GET_TRUE_ADDR_BY_INDEX(METER_PROTOCOL_VER_ID)  // 16 byte ASCII  Э��汾��(ASCII��)
#define CFL_METER_ASCII_FRACTORY_NO     GET_TRUE_ADDR_BY_INDEX(METER_FACTORY_INF_ID)   // 32 byte ASCII  ���ұ��(ASCII��)
//#define CFL_METER_ASCII_HARD_NO         (GET_TRUE_ADDR_BY_INDEX(0) // 32 byte ASCII  ����Ӳ���汾��(ASCII��)






































