#ifndef AP_PROFUNCTION_H
    #define AP_PROFUNCTION_H
    
#ifdef  AP_PROFUNCTION_GLOBALS
    #define PROFUNCTION_EXT
#else
    #define PROFUNCTION_EXT extern
#endif  

#define VOLTAGE_RATE_220    2200  // 220V��
#define VOLTAGE_RATE_100    1000  // 100V��
#define VOLTAGE_RATE_577    577   // 57.7V��

#define METER_STANDARD      0x0100
#define PULSE_CONSTANT      0x0101
#define VOLTAGE_RATE        0x0102
#define CURRENT_IB          0x0103
#define CURRENT_IMAX        0x0104
#define METER_COUNTERSHUNT  0x0122	//Ǳ������


#define CFGDIR_METER_FACTORY_ENABLE 0x08000000 // 1 byte NN BCD ����״̬
#define CFGDIR_METER_ADJUST_ENABLE 0x08000001 // 1 byte NN BCD У��״̬
#define CFGDIR_METER_ADJUST_TCLOCK 0x08000002 // 1 byte NN HEX �²�����״̬
// #define  0x08000002 // 13 byte   ����
#define CFGDIR_PRO_METER_ENABLE 0x08000010 // 0 byte   ���ڲ�����ʹ����ʼ
#define CFGDIR_PRO_KWH_C_ENABLE 0x08000010 // 1 byte NN BCD ����й�����ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KWH_C_PRICE_ENABLE 0x08000011 // 1 byte NN BCD ����й����ʵ���ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KWH_F_ENABLE 0x08000012 // 1 byte NN BCD �����й�����ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KWH_F_PRICE_ENABLE 0x08000013 // 1 byte NN BCD �����й����ʵ���ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KWH_R_ENABLE 0x08000014 // 1 byte NN BCD �����й�����ʹ��(0=�� 0=����ʹ��)
#define CFGDIR_PRO_KWH_R_PRICE_ENABLE 0x08000015 // 1 byte NN BCD �����й����ʵ���ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVARH_C12_ENABLE 0x08000016 // 1 byte NN BCD ����޹�12����ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVARH_C12_PRICE_ENABLE 0x08000017 // 1 byte NN BCD ����޹�12���ʵ���ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVARH_Q1234_ENABLE 0x08000018 // 1 byte NN BCD �������޹�����ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVARH_Q1234_PRICE_ENABLE 0x08000019 // 1 byte NN BCD �������޹����ʵ���ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVAH_F_ENABLE 0x0800001A // 1 byte NN BCD �������ڵ���ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVAH_F_PRICE_ENABLE 0x0800001B // 1 byte NN BCD �������ڷ��ʵ���ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVAH_R_ENABLE 0x0800001C // 1 byte NN BCD �������ڵ���ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVAH_R_PRICE_ENABLE 0x0800001D // 1 byte NN BCD �������ڷ��ʵ���ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KWH_RELATED_ENABLE 0x0800001E // 1 byte NN BCD �����ܵ���ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KWH_FUNDAMENTAL_F_ENABLE 0x0800001F // 1 byte NN BCD �����й���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KWH_FUNDAMENTAL_R_ENABLE 0x08000020 // 1 byte NN BCD �����й���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KWH_HARMONIC_F_ENABLE 0x08000021 // 1 byte NN BCD �����й�г������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KWH_HARMONIC_R_ENABLE 0x08000022 // 1 byte NN BCD �����й�г������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KWH_LOST_COPPER 0x08000023 // 1 byte NN BCD ͭ�����ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KWH_LOST_IRON 0x08000024 // 1 byte NN BCD �������ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KWH_C_ABC_ENABLE 0x08000025 // 1 byte NN BCD ����������й�����ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KWH_C_ABC_PRICE_ENABLE 0x08000026 // 1 byte NN BCD ����������й����ʵ���ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KWH_F_ABC_ENABLE 0x08000027 // 1 byte NN BCD �����������й�����ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KWH_F_ABC_PRICE_ENABLE 0x08000028 // 1 byte NN BCD �����������й����ʵ���ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KWH_R_ABC_ENABLE 0x08000029 // 1 byte NN BCD �����෴���й�����ʹ��(0=�� 0=����ʹ��)
#define CFGDIR_PRO_KWH_R_ABC_PRICE_ENABLE 0x0800002A // 1 byte NN BCD �����෴���й����ʵ���ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KVARH_C12_ABC_ENABLE 0x0800002B // 1 byte NN BCD ����������޹�12����ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVARH_C12_ABC_PRICE_ENABLE 0x0800002C // 1 byte NN BCD ����������޹�12���ʵ���ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KVARH_Q1234_ABC_ENABLE 0x0800002D // 1 byte NN BCD �������������޹�����ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVARH_Q1234_ABC_PRICE_ENABLE 0x0800002E // 1 byte NN BCD �������������޹����ʵ���ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KVAH_F_ABC_ENABLE 0x0800002F // 1 byte NN BCD �������������ڵ���ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVAH_F_ABC_PRICE_ENABLE 0x08000030 // 1 byte NN BCD �������������ڷ��ʵ���ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KVAH_R_ABC_ENABLE 0x08000031 // 1 byte NN BCD �����෴�����ڵ���ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVAH_R_ABC_PRICE_ENABLE 0x08000032 // 1 byte NN BCD �����෴�����ڷ��ʵ���ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KWH_RELATED_ABC_ENABLE 0x08000033 // 1 byte NN BCD ����������ܵ���ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KWH_FUNDAMENTAL_F_ABC_ENABLE 0x08000034 // 1 byte NN BCD �����������й���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KWH_FUNDAMENTAL_R_ABC_ENABLE 0x08000035 // 1 byte NN BCD �����෴���й���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KWH_HARMONIC_F_ABC_ENABLE 0x08000036 // 1 byte NN BCD �����������й�г������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KWH_HARMONIC_R_ABC_ENABLE 0x08000037 // 1 byte NN BCD �����෴���й�г������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KWH_LOST_ABC_COPPER 0x08000038 // 1 byte NN BCD ������ͭ�����ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KWH_LOST_ABC_IRON 0x08000039 // 1 byte NN BCD �������������ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KW_C_ENABLE 0x0800003A // 1 byte NN BCD ����й�����ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KW_C_PRICE_ENABLE 0x0800003B // 1 byte NN BCD ����й���������ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KW_F_ENABLE 0x0800003C // 1 byte NN BCD �����й�����ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KW_F_PRICE_ENABLE 0x0800003D // 1 byte NN BCD �����й���������ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KW_R_ENABLE 0x0800003E // 1 byte NN BCD �����й�����ʹ��(0=�� 0=����ʹ��)
#define CFGDIR_PRO_KW_R_PRICE_ENABLE 0x0800003F // 1 byte NN BCD �����й���������ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVAR_C12_ENABLE 0x08000040 // 1 byte NN BCD ����޹�12����ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVAR_C12_PRICE_ENABLE 0x08000041 // 1 byte NN BCD ����޹�12��������ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVAR_Q1234_ENABLE 0x08000042 // 1 byte NN BCD �������޹�����ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVAR_Q1234_PRICE_ENABLE 0x08000043 // 1 byte NN BCD �������޹���������ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVA_F_ENABLE 0x08000044 // 1 byte NN BCD ������������ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVA_F_PRICE_ENABLE 0x08000045 // 1 byte NN BCD �������ڷ�������ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVA_R_ENABLE 0x08000046 // 1 byte NN BCD ������������ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVA_R_PRICE_ENABLE 0x08000047 // 1 byte NN BCD �������ڷ�������ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KW_RELATED_ENABLE 0x08000048 // 1 byte NN BCD ����������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KW_FUNDAMENTAL_F_ENABLE 0x08000049 // 1 byte NN BCD �����й���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KW_FUNDAMENTAL_R_ENABLE 0x0800004A // 1 byte NN BCD �����й���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KW_HARMONIC_F_ENABLE 0x0800004B // 1 byte NN BCD �����й�г������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KW_HARMONIC_R_ENABLE 0x0800004C // 1 byte NN BCD �����й�г������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KW_LOST_COPPER 0x0800004D // 1 byte NN BCD ͭ������ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KW_LOST_IRON 0x0800004E // 1 byte NN BCD ��������ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KW_C_ABC_ENABLE 0x0800004F // 1 byte NN BCD ����������й�����ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KW_C_ABC_PRICE_ENABLE 0x08000050 // 1 byte NN BCD ����������й���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KW_F_ABC_ENABLE 0x08000051 // 1 byte NN BCD �����������й�����ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KW_F_ABC_PRICE_ENABLE 0x08000052 // 1 byte NN BCD �����������й���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KW_R_ABC_ENABLE 0x08000053 // 1 byte NN BCD �����෴���й�����ʹ��(0=�� 0=����ʹ��)
#define CFGDIR_PRO_KW_R_ABC_PRICE_ENABLE 0x08000054 // 1 byte NN BCD �����෴���й���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KVAR_C12_ABC_ENABLE 0x08000055 // 1 byte NN BCD ����������޹�12����ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVAR_C12_ABC_PRICE_ENABLE 0x08000056 // 1 byte NN BCD ����������޹�12��������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KVAR_Q1234_ABC_ENABLE 0x08000057 // 1 byte NN BCD �������������޹�����ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVAR_Q1234_ABC_PRICE_ENABLE 0x08000058 // 1 byte NN BCD �������������޹���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KVA_F_ABC_ENABLE 0x08000059 // 1 byte NN BCD ������������������ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVA_F_ABC_PRICE_ENABLE 0x0800005A // 1 byte NN BCD �������������ڷ�������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KVA_R_ABC_ENABLE 0x0800005B // 1 byte NN BCD �����෴����������ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KVA_R_ABC_PRICE_ENABLE 0x0800005C // 1 byte NN BCD �����෴�����ڷ�������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KW_RELATED_ABC_ENABLE 0x0800005D // 1 byte NN BCD ���������������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KW_FUNDAMENTAL_F_ABC_ENABLE 0x0800005E // 1 byte NN BCD �����������й���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KW_FUNDAMENTAL_R_ABC_ENABLE 0x0800005F // 1 byte NN BCD �����෴���й���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KW_HARMONIC_F_ABC_ENABLE 0x08000060 // 1 byte NN BCD �����������й�г������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KW_HARMONIC_R_ABC_ENABLE 0x08000061 // 1 byte NN BCD �����෴���й�г������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)
#define CFGDIR_PRO_KW_LOST_ABC_COPPER 0x08000062 // 1 byte NN BCD ������ͭ������ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_KW_LOST_ABC_IRON 0x08000063 // 1 byte NN BCD ��������������ʹ��(0=�� 1=ʹ��)
// #define  0x08000064 //  byte   
#define CFGDIR_PRO_AH_CLAC_ALL_ENABLE 0x08000064 // 1 byte NN BCD �ܰ���Сʱ���ݼ���ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_AH_CLAC_ABC_ENABLE 0x08000065 // 1 byte NN BCD �����ల��Сʱ������ʹ��(0=�� 1=ʹ��)
// #define  0x08000066 //  byte   
#define CFGDIR_PRO_KWH_ABC_ENABLE 0x08000066 // 1 byte NN BCD �����������ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_DEMAND_ENABLE 0x08000067 // 1 byte NN BCD ��������ʹ��(0=�� 1=ʹ��)
#define CFGDIR_PRO_DEMAND_ABC_ENABLE 0x08000068 // 1 byte NN BCD ������������ʹ��(0=�� 1=ʹ��)
// #define  0x08000069 //  byte   
#define CFGDIR_PRO_LOSS_VOLTAGE_ENABLE 0x08000069 // 1 byte NN BCD ʧѹ���ܷ�ʽ(0=�޸ù��ܣ�����Ϊ�ض��Ĺ��ܷ�ʽ)
#define CFGDIR_PRO_OVER_VOLTAGE_ENABLE 0x0800006A // 1 byte NN BCD ��ѹ���ܷ�ʽ(0=�޸ù��ܣ�����Ϊ�ض��Ĺ��ܷ�ʽ)
#define CFGDIR_PRO_DOWN_VOLTAGE_ENABLE 0x0800006B // 1 byte NN BCD Ƿѹ���ܷ�ʽ(0=�޸ù��ܣ�����Ϊ�ض��Ĺ��ܷ�ʽ)
#define CFGDIR_PRO_CUT_VOLTAGE_ENABLE 0x0800006C // 1 byte NN BCD ���๦�ܷ�ʽ(0=�޸ù��ܣ�����Ϊ�ض��Ĺ��ܷ�ʽ)
#define CFGDIR_PRO_LOSS_CURRENT_ENABLE 0x0800006D // 1 byte NN BCD ʧ�����ܷ�ʽ(0=�޸ù��ܣ�����Ϊ�ض��Ĺ��ܷ�ʽ)
#define CFGDIR_PRO_CUT_CURRENT_ENABLE 0x0800006E // 1 byte NN BCD �������ܷ�ʽ(0=�޸ù��ܣ�����Ϊ�ض��Ĺ��ܷ�ʽ)
#define CFGDIR_PRO_OVER_CURRENT_ENABLE 0x0800006F // 1 byte NN BCD �������ܷ�ʽ(0=�޸ù��ܣ�����Ϊ�ض��Ĺ��ܷ�ʽ)
#define CFGDIR_PRO_ALLLOSTV_ENABLE 0x08000070 // 1 byte NN BCD ȫʧѹʹ��(0=�޸ù��ܣ�����Ϊ���ܷ�ʽ)(ͣ��ȫʧѹ)
// #define  0x08000071 //  byte   
#define CFGDIR_PRO_ACPOWER_LOSS_ENABLE 0x08000071 // 1 byte NN BCD ������Դ���繦��ʹ��(0=�޸ù��� 1=�ù���ʹ��)
#define CFGDIR_PRO_POWER_DOWN_ENABLE 0x08000072 // 1 byte NN BCD ϵͳͣ�繦��ʹ��(0=�޸ù��� 1=�ù���ʹ��)
#define CFGDIR_PRO_ORDER_VOLTAGE_ENABLE 0x08000073 // 1 byte NN BCD ��ѹ��������ʹ��(0=�޸ù��� 1=�ù���ʹ��)
#define CFGDIR_PRO_ORDER_CURRENT_ENABLE 0x08000074 // 1 byte NN BCD ������������ʹ��(0=�޸ù��� 1=�ù���ʹ��)
#define CFGDIR_PRO_REVERSEPOWER_ALL_ENABLE 0x08000075 // 1 byte NN BCD �ܹ��ʷ�����ʹ��(0=�޸ù��� 1=�ù���ʹ��)
#define CFGDIR_PRO_REVERSEPOWER_ABC_ENABLE 0x08000076 // 1 byte NN BCD ���๦�ʷ�����ʹ��(0=�޸ù��� 1=�ù���ʹ��)
#define CFGDIR_PRO_POWEROVER_ALL_ENABLE 0x08000077 // 1 byte NN BCD �ܹ��ʹ��ع���ʹ��(0=�޸ù��� 1=�ù���ʹ��)
#define CFGDIR_PRO_POWEROVER_ABC_ENABLE 0x08000078 // 1 byte NN BCD ���๦�ʹ��ع���ʹ��(0=�޸ù��� 1=�ù���ʹ��)
#define CFGDIR_PRO_UNBALANCE_VOLTAGE_ENABLE 0x08000079 // 1 byte NN BCD ��ѹ��ƽ�⹦��ʹ��(0=�޸ù��� 1=�ù���ʹ��)
#define CFGDIR_PRO_UNBALANCE_CURRENT_ENABLE 0x0800007A // 1 byte NN BCD ������ƽ�⹦��ʹ��(0=�޸ù��� 1=�ù���ʹ��)
#define CFGDIR_PRO_VOLTAGE_ALL_MONITOR_ENABLE 0x0800007B // 1 byte NN BCD ��ѹ���ϸ�ͳ��(��ѹ���)����ʹ��(0=�޸ù��� 1=�ù���ʹ��)
#define CFGDIR_PRO_DEMAND_OVER_ENABLE 0x0800007C // 1 byte NN BCD �������޹���ʹ��(0=�޸ù��� 1=�ù���ʹ��)
#define CFGDIR_PRO_COVER_OPEN_ENABLE 0x0800007D // 1 byte NN BCD ��ǿ�������ʹ��(0=�޸ù��� 1=�ù���ʹ��)
#define CFGDIR_PRO_TERMINAL_OPEN_ENABLE 0x0800007E // 1 byte NN BCD ��ť�ǿ�������ʹ��(0=�޸ù��� 1=�ù���ʹ��)
#define CFGDIR_PRO_PROGRAM_OPEN_ENABLE 0x0800007F // 1 byte NN BCD ��̸ǿ�������ʹ��(0=�޸ù��� 1=�ù���ʹ��)
// #define  0x08000080 // 16 byte NN BCD ���� 
// #define  0x08000090 // 0 byte   ����ͺ����ò���
#define CFGDIR_TYPE_METER_TYPE 0x08000090 // 1 byte NN BCD ����
#define CFGDIR_TYPE_PLUS_CONSTANT 0x08000091 // 3 byte NNNNNN BCD ���峣��
#define CFGDIR_TYPE_VOLTAGE_UN 0x08000094 // 5 byte 00XXXX.XXXX BCD ��ѹ���
#define CFGDIR_TYPE_CURRENT_IB 0x08000099 // 5 byte 00XXXX.XXXX BCD �������
#define CFGDIR_TYPE_CURRENT_IMAX 0x0800009E // 5 byte 00XXXX.XXXX BCD ������
#define CFGDIR_COEF_KW_MUL 0x080000A3 // 1 byte  HEX ���ʱ���220V1.5(6)A =2;100V,57.7V1.5(6)A=1
#define CFGDIR_COEF_KW_DIV 0x080000A4 // 1 byte  HEX ���ʳ���220V1.5(6)A =1;100V,57.7V1.5(6)A=2
#define CFGDIR_COEF_CALC_KW 0x080000A5 // 2 byte  HEX �й�����ϵ�������ֽ���ǰ��1456(0X05B0)
#define CFGDIR_COEF_CALC_KVAR 0x080000A7 // 2 byte  HEX �޹�����ϵ�������ֽ���ǰ��1465(0X05B9)
#define CFGDIR_COEF_CALC_KVA 0x080000A9 // 2 byte  HEX ���ڹ���ϵ�������ֽ���ǰ��1456(0X05B0)
#define CFGDIR_COEF_CURRENT_A 0x080000AB // 2 byte  HEX A�����ϵ�������ֽ���ǰ,��ʱ��ʹ�ã�
#define CFGDIR_COEF_CURRENT_B 0x080000AD // 2 byte  HEX B�����ϵ�������ֽ���ǰ,��ʱ��ʹ�ã�
#define CFGDIR_COEF_CURRENT_C 0x080000AF // 2 byte  HEX C�����ϵ�������ֽ���ǰ,��ʱ��ʹ�ã�
#define CFGDIR_COEF_VOLTAGE_A 0x080000B1 // 2 byte  HEX A���ѹϵ�������ֽ���ǰ��
#define CFGDIR_COEF_VOLTAGE_B 0x080000B3 // 2 byte  HEX B���ѹϵ�������ֽ���ǰ��
#define CFGDIR_COEF_VOLTAGE_C 0x080000B5 // 2 byte  HEX C���ѹϵ�������ֽ���ǰ��
#define CFGDIR_COEF_POWER_OUTTIME 0x080000B7 // 2 byte  HEX �����Ǳ��ʱ��
#define CFGDIR_COEF_DEMAND_STARTCOUNT 0x080000B9 // 2 byte  HEX ������Ǳ��ϵ��
#define CFGDIR_COEF_METER_PULSE_STARTUP 0x080000BB // 1 byte  HEX �������������ֵ(���֮Ib)
#define CFGDIR_COEF_METER_DATA_STARTUP 0x080000BC // 1 byte  HEX �����ʾ������ֵ(���֮Ib)
// #define  0x080000BD // 3 byte   ����
#define CFGDIR_METER_COEF_START 0x080000C0 // 0 byte   ������в�����ʼ
#define CFGDIR_COEF_BALANCE_DAY_NUM 0x080000C0 // 1 byte NN BCD ÿ�½���������(1--31)
#define CFGDIR_MODE_POWER_CALC_POINT 0x080000C1 // 1 byte NN BCD ��������С����λ��(0,1,2,3)
#define CFGDIR_MODE_BROADCAST_TIME 0x080000C2 // 1 byte NN BCD �㲥Уʱ��ʽ(00����;01�ϸ�24Сʱ;02������Ȼ��;)
#define CFGDIR_COEF_BROADCAST_TIME_EVERYDAY 0x080000C3 // 1 byte NN BCD �㲥Уʱÿ���У׼ʱ��
#define CFGDIR_COEF_BROADCAST_TIME_FIXED 0x080000C4 // 1 byte NN BCD �㲥Уʱ�̶���У׼ʱ��
#define CFGDIR_MODE_DEMAND_HANDCLR_ENABLE 0x080000C5 // 1 byte NN BCD �Ƿ������ֶ���������
#define CFGDIR_COEF_DEMAND_HANDCLR_LOCKTIME 0x080000C6 // 2 byte NN HEX ������������ʱ��
#define CFGDIR_MODE_DEMAND_CALC_POINT_FIXED 0x080000C8 // 1 byte NN BCD ��������С�����Ƿ�̶�
// #define  0x080000C9 //  byte   
// #define  0x080000C9 //  byte   
// #define  0x080000C9 // 0 byte   ������ʽ(00������;01����;02��˸)
#define CFGDIR_MODE_DISPLAYALARM_ORDER_VOLTAGE 0x080000C9 // 1 byte NN BCD ��ѹ�����򱨾�(��Ӧ��ѹ����00������;01����;02��˸)
#define CFGDIR_MODE_DISPLAYALARM_LOSS_VOLTAGE 0x080000CA // 1 byte NN BCD ʧѹ����(��Ӧ��ѹ����00������;01����;02��˸)
#define CFGDIR_MODE_DISPLAYALARM_CUT_VOLTAGE 0x080000CB // 1 byte NN BCD ���౨��(��Ӧ��ѹ����00������;01����;02��˸)
#define CFGDIR_MODE_DISPLAYALARM_OVER_VOLTAGE 0x080000CC // 1 byte NN BCD ��ѹ����(��Ӧ��ѹ����00������;01����;02��˸)
#define CFGDIR_MODE_DISPLAYALARM_DOWN_VOLTAGE 0x080000CD // 1 byte NN BCD Ƿѹ����(��Ӧ��ѹ����00������;01����;02��˸)
#define CFGDIR_MODE_DISPLAYALARM_ORDER_CURRENT 0x080000CE // 1 byte NN BCD ���������򱨾�(��Ӧ��������00������;01����;02��˸)
#define CFGDIR_MODE_DISPLAYALARM_LOSS_CURRENT 0x080000CF // 1 byte NN BCD ʧ������(��Ӧ��������00������;01����;02��˸)
#define CFGDIR_MODE_DISPLAYALARM_CUT_CURRENT 0x080000D0 // 1 byte NN BCD ��������(��Ӧ��������00������;01����;02��˸)
#define CFGDIR_MODE_DISPLAYALARM_OVER_CURRENT 0x080000D1 // 1 byte NN BCD ��������(��Ӧ��������00������;01����;02��˸)
// #define  0x080000D2 //  byte   
// #define  0x080000D2 //  byte   
#define CFGDIR_COEF_ALARM_BATVOLTAGE_CLOCK 0x080000D2 // 1 byte X.X BCD ʱ�ӵ�ر�����ѹ
#define CFGDIR_COEF_ALARM_BATVOLTAGE_POWEROFF 0x080000D3 // 1 byte X.X BCD ͣ����ر�����ѹ
// #define  0x080000D4 // 5 byte  BCD ��ر�����������
#define CFGDIR_MODE_DISPLAYALARM_BAT_CLOCK 0x080000D9 // 1 byte NN BCD ʱ�ӵ����ʾ������ʽ(00 ������ 01���� 02 ���� 03 ��˸)
#define CFGDIR_MODE_DISPLAYALARM_BAT_POWEROFF 0x080000DA // 1 byte NN BCD ͣ�������ʾ������ʽ(00 ������ 01���� 02 ���� 03 ��˸)
// #define  0x080000DB // 5 byte  BCD ��ر�����������
// #define  0x080000E0 //  byte   
// #define  0x080000E0 //  byte   
// #define  0x080000E0 //  byte   
// #define  0x080000E0 //  byte   
// #define  0x080000E0 //  byte   
// #define  0x080000E0 //  byte   
// #define  0x080000E0 //  byte   
#define CFGDIR_MODE_DISPLAYCOMM_SHOW 0x080000E0 // 1 byte NN BCD ͨѶ������ʾ��ʽ�ܿ���(00����ʾ��01���ԣ�02��˸)
#define CFGDIR_MODE_DISPLAYCOMM_CHANNELS01 0x080000E1 // 1 byte NN BCD ͨѶ������ʾͨ��01(00����ʾ;01����;02��˸)
#define CFGDIR_MODE_DISPLAYCOMM_CHANNELS02 0x080000E2 // 1 byte NN BCD ͨѶ������ʾͨ��02(00��������ʾ;01������ʾ)
#define CFGDIR_MODE_DISPLAYCOMM_CHANNELS03 0x080000E3 // 1 byte NN BCD ͨѶ������ʾͨ��03(00��������ʾ;01������ʾ)
#define CFGDIR_MODE_DISPLAYCOMM_CHANNELS04 0x080000E4 // 1 byte NN BCD ͨѶ������ʾͨ��04(00��������ʾ;01������ʾ)
#define CFGDIR_MODE_DISPLAYCOMM_CHANNELS05 0x080000E5 // 1 byte NN BCD ͨѶ������ʾͨ��05(00��������ʾ;01������ʾ)
// #define  0x080000E6 //  byte   
#define CFGDIR_COEF_COMM485_CHANNELS01_SEND_LEADER_LEN 0x080000E6 // 1 byte NN BCD ͨѶ����01����ǰ����FE�ĸ���(0-5֮�����)
#define CFGDIR_COEF_COMM485_CHANNELS02_SEND_LEADER_LEN 0x080000E7 // 1 byte NN BCD ͨѶ����02����ǰ����FE�ĸ���(0-5֮�����)
#define CFGDIR_COEF_COMM485_CHANNELS03_SEND_LEADER_LEN 0x080000E8 // 1 byte NN BCD ͨѶ����03����ǰ����FE�ĸ���(0-5֮�����)
#define CFGDIR_COEF_COMM485_CHANNELS04_SEND_LEADER_LEN 0x080000E9 // 1 byte NN BCD ͨѶ����04����ǰ����FE�ĸ���(0-5֮�����)
#define CFGDIR_COEF_COMM485_CHANNELS05_SEND_LEADER_LEN 0x080000EA // 1 byte NN BCD ͨѶ����05����ǰ����FE�ĸ���(0-5֮�����)
// #define  0x080000EB //  byte   
// #define  0x080000EB //  byte   
// #define  0x080000EB //  byte   
#define CFGDIR_MODE_COMM485_CHANNELS01_RATE 0x080000EB // 1 byte NN BCD ͨѶ������ģʽ01(00�����ʿ���;01�����ʹ̶�;02����������Ӧ)
#define CFGDIR_MODE_COMM485_CHANNELS02_RATE 0x080000EC // 1 byte NN BCD ͨѶ������ģʽ02(00�����ʿ���;01�����ʹ̶�;02����������Ӧ)
#define CFGDIR_MODE_COMM485_CHANNELS03_RATE 0x080000ED // 1 byte NN BCD ͨѶ������ģʽ03(00�����ʿ���;01�����ʹ̶�;02����������Ӧ)
#define CFGDIR_MODE_COMM485_CHANNELS04_RATE 0x080000EE // 1 byte NN BCD ͨѶ������ģʽ04(00�����ʿ���;01�����ʹ̶�;02����������Ӧ)
#define CFGDIR_MODE_COMM485_CHANNELS05_RATE 0x080000EF // 1 byte NN BCD ͨѶ������ģʽ05(00�����ʿ���;01�����ʹ̶�;02����������Ӧ)
// #define  0x080000F0 // 1 byte  BCD 
// #define  0x080000F1 // 1 byte  BCD 
// #define  0x080000F2 // 1 byte  BCD 
// #define  0x080000F3 //  byte   
// #define  0x080000F3 //  byte   
// #define  0x080000F3 //  byte   
// #define  0x080000F3 //  byte   
// #define  0x080000F3 //  byte   
// #define  0x080000F3 //  byte   
// #define  0x080000F3 //  byte   
// #define  0x080000F3 //  byte   
// #define  0x080000F3 //  byte   
// #define  0x080000F3 //  byte   
// #define  0x080000F3 //  byte   
// #define  0x080000F3 //  byte   
// #define  0x080000F3 //  byte   
// #define  0x080000F3 //  byte   
// #define  0x080000F3 //  byte   
// #define  0x080000F3 //  byte   






//#define CON_SYSTEMPROFUNCTION_LEN ((CFGDIR_MODE_COMM485_CHANNELS05_RATE&0xffff)+1)    //256
#define CON_SYSTEMPROFUNCTION_LEN 256

PROFUNCTION_EXT uchar SYSTEMPROGFUNCTION[CON_SYSTEMPROFUNCTION_LEN];

#define PROGFUNCTION_METER_FACTORY SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_METER_FACTORY_ENABLE ] // ����״̬   
#define PROGFUNCTION_METER_ADJUST SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_METER_ADJUST_ENABLE ] // У��״̬   
#define PROGFUNCTION_METER_TCLOCK    SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_METER_ADJUST_TCLOCK ] // У��״̬   
       
#define PROGFUNCTION_METER SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_METER_ENABLE ] // ���ڲ�����ʹ����ʼ   
#define PROGFUNCTION_KWH_C SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_C_ENABLE ] // ����й�����ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KWH_C_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_C_PRICE_ENABLE ] // ����й����ʵ���ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KWH_F SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_F_ENABLE ] // �����й�����ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KWH_F_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_F_PRICE_ENABLE ] // �����й����ʵ���ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KWH_R SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_R_ENABLE ] // �����й�����ʹ��(0=�� 0=����ʹ��)   
#define PROGFUNCTION_KWH_R_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_R_PRICE_ENABLE ] // �����й����ʵ���ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVARH_C12 SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVARH_C12_ENABLE ] // ����޹�12����ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVARH_C12_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVARH_C12_PRICE_ENABLE ] // ����޹�12���ʵ���ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVARH_Q1234 SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVARH_Q1234_ENABLE ] // �������޹�����ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVARH_Q1234_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVARH_Q1234_PRICE_ENABLE ] // �������޹����ʵ���ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVAH_F SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVAH_F_ENABLE ] // �������ڵ���ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVAH_F_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVAH_F_PRICE_ENABLE ] // �������ڷ��ʵ���ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVAH_R SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVAH_R_ENABLE ] // �������ڵ���ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVAH_R_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVAH_R_PRICE_ENABLE ] // �������ڷ��ʵ���ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KWH_RELATED SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_RELATED_ENABLE ] // �����ܵ���ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KWH_FUNDAMENTAL_F SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_FUNDAMENTAL_F_ENABLE ] // �����й���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KWH_FUNDAMENTAL_R SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_FUNDAMENTAL_R_ENABLE ] // �����й���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KWH_HARMONIC_F SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_HARMONIC_F_ENABLE ] // �����й�г������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KWH_HARMONIC_R SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_HARMONIC_R_ENABLE ] // �����й�г������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KWH_LOST_COPPER  SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_LOST_COPPER  ] // ͭ�����ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KWH_LOST_IRON SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_LOST_IRON ] // �������ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KWH_C_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_C_ABC_ENABLE ] // ����������й�����ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KWH_C_ABC_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_C_ABC_PRICE_ENABLE ] // ����������й����ʵ���ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KWH_F_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_F_ABC_ENABLE ] // �����������й�����ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KWH_F_ABC_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_F_ABC_PRICE_ENABLE ] // �����������й����ʵ���ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KWH_R_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_R_ABC_ENABLE ] // �����෴���й�����ʹ��(0=�� 0=����ʹ��)   
#define PROGFUNCTION_KWH_R_ABC_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_R_ABC_PRICE_ENABLE ] // �����෴���й����ʵ���ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KVARH_C12_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVARH_C12_ABC_ENABLE ] // ����������޹�12����ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVARH_C12_ABC_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVARH_C12_ABC_PRICE_ENABLE ] // ����������޹�12���ʵ���ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KVARH_Q1234_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVARH_Q1234_ABC_ENABLE ] // �������������޹�����ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVARH_Q1234_ABC_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVARH_Q1234_ABC_PRICE_ENABLE ] // �������������޹����ʵ���ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KVAH_F_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVAH_F_ABC_ENABLE ] // �������������ڵ���ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVAH_F_ABC_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVAH_F_ABC_PRICE_ENABLE ] // �������������ڷ��ʵ���ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KVAH_R_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVAH_R_ABC_ENABLE ] // �����෴�����ڵ���ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVAH_R_ABC_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVAH_R_ABC_PRICE_ENABLE ] // �����෴�����ڷ��ʵ���ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KWH_RELATED_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_RELATED_ABC_ENABLE ] // ����������ܵ���ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KWH_FUNDAMENTAL_F_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_FUNDAMENTAL_F_ABC_ENABLE ] // �����������й���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KWH_FUNDAMENTAL_R_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_FUNDAMENTAL_R_ABC_ENABLE ] // �����෴���й���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KWH_HARMONIC_F_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_HARMONIC_F_ABC_ENABLE ] // �����������й�г������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KWH_HARMONIC_R_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_HARMONIC_R_ABC_ENABLE ] // �����෴���й�г������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KWH_LOST_ABC_COPPER  SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_LOST_ABC_COPPER  ] // ������ͭ�����ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KWH_LOST_ABC_IRON SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_LOST_ABC_IRON ] // �������������ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KW_C SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_C_ENABLE ] // ����й�����ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KW_C_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_C_PRICE_ENABLE ] // ����й���������ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KW_F SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_F_ENABLE ] // �����й�����ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KW_F_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_F_PRICE_ENABLE ] // �����й���������ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KW_R SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_R_ENABLE ] // �����й�����ʹ��(0=�� 0=����ʹ��)   
#define PROGFUNCTION_KW_R_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_R_PRICE_ENABLE ] // �����й���������ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVAR_C12 SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVAR_C12_ENABLE ] // ����޹�12����ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVAR_C12_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVAR_C12_PRICE_ENABLE ] // ����޹�12��������ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVAR_Q1234 SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVAR_Q1234_ENABLE ] // �������޹�����ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVAR_Q1234_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVAR_Q1234_PRICE_ENABLE ] // �������޹���������ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVA_F SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVA_F_ENABLE ] // ������������ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVA_F_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVA_F_PRICE_ENABLE ] // �������ڷ�������ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVA_R SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVA_R_ENABLE ] // ������������ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVA_R_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVA_R_PRICE_ENABLE ] // �������ڷ�������ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KW_RELATED SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_RELATED_ENABLE ] // ����������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KW_FUNDAMENTAL_F SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_FUNDAMENTAL_F_ENABLE ] // �����й���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KW_FUNDAMENTAL_R SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_FUNDAMENTAL_R_ENABLE ] // �����й���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KW_HARMONIC_F SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_HARMONIC_F_ENABLE ] // �����й�г������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KW_HARMONIC_R SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_HARMONIC_R_ENABLE ] // �����й�г������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KW_LOST_COPPER  SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_LOST_COPPER  ] // ͭ������ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KW_LOST_IRON SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_LOST_IRON ] // ��������ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KW_C_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_C_ABC_ENABLE ] // ����������й�����ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KW_C_ABC_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_C_ABC_PRICE_ENABLE ] // ����������й���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KW_F_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_F_ABC_ENABLE ] // �����������й�����ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KW_F_ABC_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_F_ABC_PRICE_ENABLE ] // �����������й���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KW_R_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_R_ABC_ENABLE ] // �����෴���й�����ʹ��(0=�� 0=����ʹ��)   
#define PROGFUNCTION_KW_R_ABC_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_R_ABC_PRICE_ENABLE ] // �����෴���й���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KVAR_C12_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVAR_C12_ABC_ENABLE ] // ����������޹�12����ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVAR_C12_ABC_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVAR_C12_ABC_PRICE_ENABLE ] // ����������޹�12��������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KVAR_Q1234_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVAR_Q1234_ABC_ENABLE ] // �������������޹�����ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVAR_Q1234_ABC_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVAR_Q1234_ABC_PRICE_ENABLE ] // �������������޹���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KVA_F_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVA_F_ABC_ENABLE ] // ������������������ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVA_F_ABC_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVA_F_ABC_PRICE_ENABLE ] // �������������ڷ�������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KVA_R_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVA_R_ABC_ENABLE ] // �����෴����������ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KVA_R_ABC_PRICE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KVA_R_ABC_PRICE_ENABLE ] // �����෴�����ڷ�������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KW_RELATED_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_RELATED_ABC_ENABLE ] // ���������������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KW_FUNDAMENTAL_F_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_FUNDAMENTAL_F_ABC_ENABLE ] // �����������й���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KW_FUNDAMENTAL_R_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_FUNDAMENTAL_R_ABC_ENABLE ] // �����෴���й���������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KW_HARMONIC_F_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_HARMONIC_F_ABC_ENABLE ] // �����������й�г������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KW_HARMONIC_R_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_HARMONIC_R_ABC_ENABLE ] // �����෴���й�г������ʹ��(0=�� 1=ʹ��)(Ŀǰû�иù���)   
#define PROGFUNCTION_KW_LOST_ABC_COPPER  SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_LOST_ABC_COPPER  ] // ������ͭ������ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_KW_LOST_ABC_IRON SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KW_LOST_ABC_IRON ] // ��������������ʹ��(0=�� 1=ʹ��)   
       
#define PROGFUNCTION_AH_CLAC_ALL SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_AH_CLAC_ALL_ENABLE ] // �ܰ���Сʱ���ݼ���ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_AH_CLAC_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_AH_CLAC_ABC_ENABLE ] // �����ల��Сʱ������ʹ��(0=�� 1=ʹ��)   
       
#define PROGFUNCTION_KWH_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_KWH_ABC_ENABLE ] // �����������ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_DEMAND SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_DEMAND_ENABLE ] // ��������ʹ��(0=�� 1=ʹ��)   
#define PROGFUNCTION_DEMAND_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_DEMAND_ABC_ENABLE ] // ������������ʹ��(0=�� 1=ʹ��)   
       
#define PROGFUNCTION_LOSS_VOLTAGE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_LOSS_VOLTAGE_ENABLE ] // ʧѹ���ܷ�ʽ(0=�޸ù��ܣ�����Ϊ�ض��Ĺ��ܷ�ʽ)   
#define PROGFUNCTION_OVER_VOLTAGE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_OVER_VOLTAGE_ENABLE ] // ��ѹ���ܷ�ʽ(0=�޸ù��ܣ�����Ϊ�ض��Ĺ��ܷ�ʽ)   
#define PROGFUNCTION_DOWN_VOLTAGE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_DOWN_VOLTAGE_ENABLE ] // Ƿѹ���ܷ�ʽ(0=�޸ù��ܣ�����Ϊ�ض��Ĺ��ܷ�ʽ)   
#define PROGFUNCTION_CUT_VOLTAGE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_CUT_VOLTAGE_ENABLE ] // ���๦�ܷ�ʽ(0=�޸ù��ܣ�����Ϊ�ض��Ĺ��ܷ�ʽ)   
#define PROGFUNCTION_LOSS_CURRENT SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_LOSS_CURRENT_ENABLE ] // ʧ�����ܷ�ʽ(0=�޸ù��ܣ�����Ϊ�ض��Ĺ��ܷ�ʽ)   
#define PROGFUNCTION_CUT_CURRENT SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_CUT_CURRENT_ENABLE ] // �������ܷ�ʽ(0=�޸ù��ܣ�����Ϊ�ض��Ĺ��ܷ�ʽ)   
#define PROGFUNCTION_OVER_CURRENT SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_OVER_CURRENT_ENABLE ] // �������ܷ�ʽ(0=�޸ù��ܣ�����Ϊ�ض��Ĺ��ܷ�ʽ)   
#define PROGFUNCTION_ALLLOSTV SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_ALLLOSTV_ENABLE ] // ȫʧѹʹ��(0=�޸ù��ܣ�����Ϊ���ܷ�ʽ)(ͣ��ȫʧѹ)   
       
#define PROGFUNCTION_ACPOWER_LOSS SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_ACPOWER_LOSS_ENABLE ] // ������Դ���繦��ʹ��(0=�޸ù��� 1=�ù���ʹ��)   
#define PROGFUNCTION_POWER_DOWN SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_POWER_DOWN_ENABLE ] // ϵͳͣ�繦��ʹ��(0=�޸ù��� 1=�ù���ʹ��)   
#define PROGFUNCTION_ORDER_VOLTAGE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_ORDER_VOLTAGE_ENABLE ] // ��ѹ��������ʹ��(0=�޸ù��� 1=�ù���ʹ��)   
#define PROGFUNCTION_ORDER_CURRENT SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_ORDER_CURRENT_ENABLE ] // ������������ʹ��(0=�޸ù��� 1=�ù���ʹ��)   
#define PROGFUNCTION_REVERSEPOWER_ALL SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_REVERSEPOWER_ALL_ENABLE ] // �ܹ��ʷ�����ʹ��(0=�޸ù��� 1=�ù���ʹ��)   
#define PROGFUNCTION_REVERSEPOWER_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_REVERSEPOWER_ABC_ENABLE ] // ���๦�ʷ�����ʹ��(0=�޸ù��� 1=�ù���ʹ��)   
#define PROGFUNCTION_POWEROVER_ALL SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_POWEROVER_ALL_ENABLE ] // �ܹ��ʹ��ع���ʹ��(0=�޸ù��� 1=�ù���ʹ��)   
#define PROGFUNCTION_POWEROVER_ABC SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_POWEROVER_ABC_ENABLE ] // ���๦�ʹ��ع���ʹ��(0=�޸ù��� 1=�ù���ʹ��)   
#define PROGFUNCTION_UNBALANCE_VOLTAGE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_UNBALANCE_VOLTAGE_ENABLE ] // ��ѹ��ƽ�⹦��ʹ��(0=�޸ù��� 1=�ù���ʹ��)   
#define PROGFUNCTION_UNBALANCE_CURRENT SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_UNBALANCE_CURRENT_ENABLE ] // ������ƽ�⹦��ʹ��(0=�޸ù��� 1=�ù���ʹ��)   
#define PROGFUNCTION_VOLTAGE_ALL_MONITOR SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_VOLTAGE_ALL_MONITOR_ENABLE ] // ��ѹ���ϸ�ͳ��(��ѹ���)����ʹ��(0=�޸ù��� 1=�ù���ʹ��)   
#define PROGFUNCTION_DEMAND_OVER SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_DEMAND_OVER_ENABLE ] // �������޹���ʹ��(0=�޸ù��� 1=�ù���ʹ��)   
#define PROGFUNCTION_COVER_OPEN SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_COVER_OPEN_ENABLE ] // ��ǿ�������ʹ��(0=�޸ù��� 1=�ù���ʹ��)   
#define PROGFUNCTION_TERMINAL_OPEN SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_TERMINAL_OPEN_ENABLE ] // ��ť�ǿ�������ʹ��(0=�޸ù��� 1=�ù���ʹ��)   
#define PROGFUNCTION_PROGRAM_OPEN SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_PRO_PROGRAM_OPEN_ENABLE ] // ��̸ǿ�������ʹ��(0=�޸ù��� 1=�ù���ʹ��)   
       
unsigned char PROGFUNCTION_TYPE_METER_TYPE;       
//#define PROGFUNCTION_TYPE_METER_TYPE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_TYPE_METER_TYPE ] // ����   
#define PROGFUNCTION_TYPE_PLUS_CONSTANT SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_TYPE_PLUS_CONSTANT ] // ���峣��   
#define PROGFUNCTION_TYPE_VOLTAGE_UN SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_TYPE_VOLTAGE_UN ] // ��ѹ���   
#define PROGFUNCTION_TYPE_CURRENT_IB SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_TYPE_CURRENT_IB ] // �������   
#define PROGFUNCTION_TYPE_CURRENT_IMAX SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_TYPE_CURRENT_IMAX ] // ������   
#define PROGFUNCTION_COEF_KW_MUL SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_KW_MUL ] // ���ʱ���220V1.5(6)A =2;100V,57.7V1.5(6)A=1   
#define PROGFUNCTION_COEF_KW_DIV SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_KW_DIV ] // ���ʳ���220V1.5(6)A =1;100V,57.7V1.5(6)A=2   
#define PROGFUNCTION_COEF_CALC_KW SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_CALC_KW ] // �й�����ϵ�������ֽ���ǰ��1456(0X05B0)   
#define PROGFUNCTION_COEF_CALC_KVAR SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_CALC_KVAR ] // �޹�����ϵ�������ֽ���ǰ��1465(0X05B9)   
#define PROGFUNCTION_COEF_CALC_KVA SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_CALC_KVA ] // ���ڹ���ϵ�������ֽ���ǰ��1456(0X05B0)   
#define PROGFUNCTION_COEF_CURRENT_A SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_CURRENT_A ] // A�����ϵ�������ֽ���ǰ��   
#define PROGFUNCTION_COEF_CURRENT_B SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_CURRENT_B ] // B�����ϵ�������ֽ���ǰ��   
#define PROGFUNCTION_COEF_CURRENT_C SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_CURRENT_C ] // C�����ϵ�������ֽ���ǰ��   
#define PROGFUNCTION_COEF_VOLTAGE_A SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_VOLTAGE_A ] // A���ѹϵ�������ֽ���ǰ��   
#define PROGFUNCTION_COEF_VOLTAGE_B SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_VOLTAGE_B ] // B���ѹϵ�������ֽ���ǰ��   
#define PROGFUNCTION_COEF_VOLTAGE_C SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_VOLTAGE_C ] // C���ѹϵ�������ֽ���ǰ��   
#define PROGFUNCTION_COEF_POWER_OUTTIME SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_POWER_OUTTIME ] // �����Ǳ��ʱ��   
#define PROGFUNCTION_COEF_DEMAND_STARTCOUNT SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_DEMAND_STARTCOUNT ] // ������Ǳ��ϵ��   
#define PROGFUNCTION_COEF_METER_PULSE_STARTUP SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_METER_PULSE_STARTUP ] // �������������ֵ(���֮Ib)
#define PROGFUNCTION_COEF_METER_DATA_STARTUP SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_METER_DATA_STARTUP ] // �����ʾ������ֵ(���֮Ib)


#define PROGFUNCTION_METER_COEF_START SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_METER_COEF_START ] // ������в�����ʼ   
#define PROGFUNCTION_COEF_BALANCE_DAY_NUM SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_BALANCE_DAY_NUM ] // ÿ�½���������(1--31)   
#define PROGFUNCTION_MODE_POWER_CALC_POINT SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_POWER_CALC_POINT ] // ��������С����λ��(0,1,2,3)   
#define PROGFUNCTION_MODE_BROADCAST_TIME SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_BROADCAST_TIME ] // �㲥Уʱ��ʽ(00����;01�ϸ�24Сʱ;02������Ȼ��;)   
#define PROGFUNCTION_COEF_BROADCAST_TIME_EVERYDAY SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_BROADCAST_TIME_EVERYDAY ] // �㲥Уʱÿ���У׼ʱ��   
#define PROGFUNCTION_COEF_BROADCAST_TIME_FIXED SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_BROADCAST_TIME_FIXED ] // �㲥Уʱ�̶���У׼ʱ��   
#define PROGFUNCTION_MODE_DEMAND_HANDCLR_ENABLE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DEMAND_HANDCLR_ENABLE ] // �Ƿ������ֶ���������   
#define PROGFUNCTION_COEF_DEMAND_HANDCLR_LOCKTIME SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_DEMAND_HANDCLR_LOCKTIME ] // ������������ʱ��   
#define PROGFUNCTION_MODE_DEMAND_CALC_POINT_FIXED SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DEMAND_CALC_POINT_FIXED ] // ��������С�����Ƿ�̶�   
       
       
       
#define PROGFUNCTION_MODE_DISPLAYALARM_ORDER_VOLTAGE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DISPLAYALARM_ORDER_VOLTAGE ] // ��ѹ�����򱨾�(��Ӧ��ѹ����00������;01����;02��˸)   
#define PROGFUNCTION_MODE_DISPLAYALARM_LOSS_VOLTAGE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DISPLAYALARM_LOSS_VOLTAGE ] // ʧѹ����(��Ӧ��ѹ����00������;01����;02��˸)   
#define PROGFUNCTION_MODE_DISPLAYALARM_CUT_VOLTAGE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DISPLAYALARM_CUT_VOLTAGE ] // ���౨��(��Ӧ��ѹ����00������;01����;02��˸)   
#define PROGFUNCTION_MODE_DISPLAYALARM_OVER_VOLTAGE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DISPLAYALARM_OVER_VOLTAGE ] // ��ѹ����(��Ӧ��ѹ����00������;01����;02��˸)   
#define PROGFUNCTION_MODE_DISPLAYALARM_DOWN_VOLTAGE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DISPLAYALARM_DOWN_VOLTAGE ] // Ƿѹ����(��Ӧ��ѹ����00������;01����;02��˸)   
#define PROGFUNCTION_MODE_DISPLAYALARM_ORDER_CURRENT SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DISPLAYALARM_ORDER_CURRENT ] // ���������򱨾�(��Ӧ��������00������;01����;02��˸)   
#define PROGFUNCTION_MODE_DISPLAYALARM_LOSS_CURRENT SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DISPLAYALARM_LOSS_CURRENT ] // ʧ������(��Ӧ��������00������;01����;02��˸)   
#define PROGFUNCTION_MODE_DISPLAYALARM_CUT_CURRENT SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DISPLAYALARM_CUT_CURRENT ] // ��������(��Ӧ��������00������;01����;02��˸)   
#define PROGFUNCTION_MODE_DISPLAYALARM_OVER_CURRENT SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DISPLAYALARM_OVER_CURRENT ] // ��������(��Ӧ��������00������;01����;02��˸)   
       
       
#define PROGFUNCTION_COEF_ALARM_BATVOLTAGE_CLOCK SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_ALARM_BATVOLTAGE_CLOCK ] // ʱ�ӵ�ر�����ѹ   
#define PROGFUNCTION_COEF_ALARM_BATVOLTAGE_POWEROFF SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_ALARM_BATVOLTAGE_POWEROFF ] // ͣ����ر�����ѹ   
       
#define PROGFUNCTION_MODE_DISPLAYALARM_BAT_CLOCK SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DISPLAYALARM_BAT_CLOCK ] // ʱ�ӵ����ʾ������ʽ(00 ������ 01���� 02 ���� 03 ��˸)   
#define PROGFUNCTION_MODE_DISPLAYALARM_BAT_POWEROFF SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DISPLAYALARM_BAT_POWEROFF ] // ͣ�������ʾ������ʽ(00 ������ 01���� 02 ���� 03 ��˸)   
       
       
       
       
       
       
       
       
#define PROGFUNCTION_MODE_DISPLAYCOMM_SHOW SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DISPLAYCOMM_SHOW ] // ͨѶ������ʾ��ʽ�ܿ���(00����ʾ��01���ԣ�02��˸)   
#define PROGFUNCTION_MODE_DISPLAYCOMM_CHANNELS01 SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DISPLAYCOMM_CHANNELS01 ] // ͨѶ������ʾͨ��01(00����ʾ;01����;02��˸)   
#define PROGFUNCTION_MODE_DISPLAYCOMM_CHANNELS02 SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DISPLAYCOMM_CHANNELS02 ] // ͨѶ������ʾͨ��02(00��������ʾ;01������ʾ)   
#define PROGFUNCTION_MODE_DISPLAYCOMM_CHANNELS03 SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DISPLAYCOMM_CHANNELS03 ] // ͨѶ������ʾͨ��03(00��������ʾ;01������ʾ)   
#define PROGFUNCTION_MODE_DISPLAYCOMM_CHANNELS04 SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DISPLAYCOMM_CHANNELS04 ] // ͨѶ������ʾͨ��04(00��������ʾ;01������ʾ)   
#define PROGFUNCTION_MODE_DISPLAYCOMM_CHANNELS05 SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DISPLAYCOMM_CHANNELS05 ] // ͨѶ������ʾͨ��05(00��������ʾ;01������ʾ)   
#define PROGFUNCTION_MODE_DISPLAYCOMM_CHANNELS06 SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DISPLAYCOMM_CHANNELS06 ] // ͨѶ������ʾͨ��06(00��������ʾ;01������ʾ)   
#define PROGFUNCTION_MODE_DISPLAYCOMM_CHANNELS07 SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DISPLAYCOMM_CHANNELS07 ] // ͨѶ������ʾͨ��07(00��������ʾ;01������ʾ)   
#define PROGFUNCTION_MODE_DISPLAYCOMM_CHANNELS08 SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DISPLAYCOMM_CHANNELS08 ] // ͨѶ������ʾͨ��08(00��������ʾ;01������ʾ)   
#define PROGFUNCTION_MODE_DISPLAYCOMM_CHANNELS09 SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DISPLAYCOMM_CHANNELS09 ] // ͨѶ������ʾͨ��09(00��������ʾ;01������ʾ)   
#define PROGFUNCTION_MODE_DISPLAYCOMM_CHANNELS10 SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_DISPLAYCOMM_CHANNELS10 ] // ͨѶ������ʾͨ��10(00��������ʾ;01������ʾ)   
       
#define PROGFUNCTION_COEF_COMM485_CHANNELS01_SEND_LEADER_LEN SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_COMM485_CHANNELS01_SEND_LEADER_LEN ] // ͨѶ����01����ǰ����FE�ĸ���(0-5֮�����)   
#define PROGFUNCTION_COEF_COMM485_CHANNELS02_SEND_LEADER_LEN SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_COMM485_CHANNELS02_SEND_LEADER_LEN ] // ͨѶ����02����ǰ����FE�ĸ���(0-5֮�����)   
#define PROGFUNCTION_COEF_COMM485_CHANNELS03_SEND_LEADER_LEN SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_COMM485_CHANNELS03_SEND_LEADER_LEN ] // ͨѶ����03����ǰ����FE�ĸ���(0-5֮�����)   
#define PROGFUNCTION_COEF_COMM485_CHANNELS04_SEND_LEADER_LEN SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_COMM485_CHANNELS04_SEND_LEADER_LEN ] // ͨѶ����04����ǰ����FE�ĸ���(0-5֮�����)   
#define PROGFUNCTION_COEF_COMM485_CHANNELS05_SEND_LEADER_LEN SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_COMM485_CHANNELS05_SEND_LEADER_LEN ] // ͨѶ����05����ǰ����FE�ĸ���(0-5֮�����)   
#define PROGFUNCTION_COEF_COMM485_CHANNELS06_SEND_LEADER_LEN SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_COMM485_CHANNELS06_SEND_LEADER_LEN ] // ͨѶ����06����ǰ����FE�ĸ���(0-5֮�����)   
#define PROGFUNCTION_COEF_COMM485_CHANNELS07_SEND_LEADER_LEN SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_COMM485_CHANNELS07_SEND_LEADER_LEN ] // ͨѶ����07����ǰ����FE�ĸ���(0-5֮�����)   
#define PROGFUNCTION_COEF_COMM485_CHANNELS08_SEND_LEADER_LEN SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_COMM485_CHANNELS08_SEND_LEADER_LEN ] // ͨѶ����08����ǰ����FE�ĸ���(0-5֮�����)   
#define PROGFUNCTION_COEF_COMM485_CHANNELS09_SEND_LEADER_LEN SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_COMM485_CHANNELS09_SEND_LEADER_LEN ] // ͨѶ����09����ǰ����FE�ĸ���(0-5֮�����)   
#define PROGFUNCTION_COEF_COMM485_CHANNELS10_SEND_LEADER_LEN SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_COEF_COMM485_CHANNELS10_SEND_LEADER_LEN ] // ͨѶ����10����ǰ����FE�ĸ���(0-5֮�����)   
       
       
       
#define PROGFUNCTION_MODE_COMM485_CHANNELS01_RATE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_COMM485_CHANNELS01_RATE ] // ͨѶ������ģʽ01(00�����ʿ���;01�����ʹ̶�;02����������Ӧ)   
#define PROGFUNCTION_MODE_COMM485_CHANNELS02_RATE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_COMM485_CHANNELS02_RATE ] // ͨѶ������ģʽ02(00�����ʿ���;01�����ʹ̶�;02����������Ӧ)   
#define PROGFUNCTION_MODE_COMM485_CHANNELS03_RATE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_COMM485_CHANNELS03_RATE ] // ͨѶ������ģʽ03(00�����ʿ���;01�����ʹ̶�;02����������Ӧ)   
#define PROGFUNCTION_MODE_COMM485_CHANNELS04_RATE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_COMM485_CHANNELS04_RATE ] // ͨѶ������ģʽ04(00�����ʿ���;01�����ʹ̶�;02����������Ӧ)   
#define PROGFUNCTION_MODE_COMM485_CHANNELS05_RATE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_COMM485_CHANNELS05_RATE ] // ͨѶ������ģʽ05(00�����ʿ���;01�����ʹ̶�;02����������Ӧ)   
#define PROGFUNCTION_MODE_COMM485_CHANNELS06_RATE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_COMM485_CHANNELS06_RATE ] // ͨѶ������ģʽ06(00�����ʿ���;01�����ʹ̶�;02����������Ӧ)   
#define PROGFUNCTION_MODE_COMM485_CHANNELS07_RATE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_COMM485_CHANNELS07_RATE ] // ͨѶ������ģʽ07(00�����ʿ���;01�����ʹ̶�;02����������Ӧ)   
#define PROGFUNCTION_MODE_COMM485_CHANNELS08_RATE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_COMM485_CHANNELS08_RATE ] // ͨѶ������ģʽ08(00�����ʿ���;01�����ʹ̶�;02����������Ӧ)   
#define PROGFUNCTION_MODE_COMM485_CHANNELS09_RATE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_COMM485_CHANNELS09_RATE ] // ͨѶ������ģʽ09(00�����ʿ���;01�����ʹ̶�;02����������Ӧ)   
#define PROGFUNCTION_MODE_COMM485_CHANNELS10_RATE SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_MODE_COMM485_CHANNELS10_RATE ] // ͨѶ������ģʽ10(00�����ʿ���;01�����ʹ̶�;02����������Ӧ)   
       
       
       
       
       























#define DEMAND_PULSE_MODE0  0    // aaa ��������AAAA
#define DEMAND_PULSE_MODE1   1    // AAA ����AAAAAAAA

#define DEMAND_PULSE_MODE DEMAND_PULSE_MODE1

#define METERTYPE_3_3 0x42     // aaa ��������AAAA
#define METERTYPE_3_4 0x43     // aaaa��������AAAAA

#define PROFUNCTION_3P3W_SUB_VOLTAGE 150
#define PROFUNCTION_3P3W_ADD_VOLTAGE 1150


#define LOSS_CURRENT_MODE0  0           // aaʧ��ģʽ0    AAAAAAAA
#define LOSS_CURRENT_MODE1  1           // aaʧ��ģʽ1    AAAAAAAA
#define LOSS_CURRENT_MODE2  2           // aaʧ��ģʽ2    AAAAAAAA
#define LOSS_CURRENT_MODE3  3           // aaʧ��ģʽ3    AAAAAAAA
#define LOSS_CURRENT_MODE4  4           // aaʧ��ģʽ4    AAAAAAAA
#define LOSS_CURRENT_MODE5  5           // aaʧ��ģʽ5    AAAAAAAA
#define LOSS_CURRENT_MODE6  6           // aaʧ��ģʽ6    AAAAAAAA

#define LOSS_VOLTAGE_MODE_0  0          // aaʧѹģʽ0    AAAAAAAA
#define LOSS_VOLTAGE_MODE_1  1          // aaʧѹģʽ1    AAAAAAAA
#define LOSS_VOLTAGE_MODE_2  2          // aaʧѹģʽ2    AAAAAAAA
#define LOSS_VOLTAGE_MODE_3  3          // aaʧѹģʽ3    AAAAAAAA
#define LOSS_VOLTAGE_MODE_4  4          // aaʧѹģʽ4    AAAAAAAA
#define LOSS_VOLTAGE_MODE_5  5          // aaʧѹģʽ5    AAAAAAAA
#define LOSS_VOLTAGE_MODE_6  6          // aaʧѹģʽ6    AAAAAAAA

// cos
#define COSSUB10 0x00996100
#define COSADD10 0x01000700
// cos55 cos 65
#define COSADD5L 0x00573600
#define COSSUB05L 0x00422600


#define CONST_VALUE_BATTER 0x22
#define TIMEVALUE_SPEEK 0x05
#define TIMEVALUE_DEMANDCLR_LOCK 7*24*60



//#define type_33_b_v_add 1150   // AAA����������AAAA
#define type_33_b_v_sub  150    // AAA����������AAAA
//ppp3//pppp3-3--------------------------------->
//#define cos3_3_90 0x00087155
//#define cos3_3_30sub 0x00819152
//#define cos3_3_30add 0x00906308

#define METER_IN_FACTORY 0xA5
#define METER_OUT_FACTORY 0x33

#define METER_TCLOCK_IDLE       0x33    //����״̬
#define METER_TCLOCK_PP_ADJUST  0xA5    //����ƵƫУ��
#define METER_TCLOCK_WK_TEST    0x5A    //�²�����״̬


#define CURRENT_TYPE_SMALL              0
#define CURRENT_TYPE_BIG                1
#define CURRENT_TYPE_VERYBIG            2


#define KWHCLACMODE     1


#define CK_V_220 (636)
#define CK_V_100 (1399)
#define CK_V_577 (2425)

#define PROGFUNCTION_CLALKW_Z       GAL_YES
#define PROGFUNCTION_CLALKW_A   GAL_YES
#define PROGFUNCTION_CLALKW_B       GAL_YES
#define PROGFUNCTION_CLALKW_C       GAL_YES



#define MODE_POWER_CALC_POINT_0DOT  0
#define MODE_POWER_CALC_POINT_1DOT  1
#define MODE_POWER_CALC_POINT_2DOT  2
#define MODE_POWER_CALC_POINT_3DOT  3
#define MODE_POWER_CALC_POINT_4DOT  4

//#define MODE_POWER_CALC_POINT MODE_POWER_CALC_POINT_4DOT
#define MODE_POWER_CALC_POINT RAM[RAM_COEF_POWER_POINT_NUM]

                          
#define MODE_DEMAND_CALC_POINT_2DOT 2
#define MODE_DEMAND_CALC_POINT_3DOT 3
#define MODE_DEMAND_CALC_POINT_4DOT 4
#define MODE_DEMAND_CALC_POINT_5DOT 5
#define MODE_DEMAND_CALC_POINT_6DOT 6
#define MODE_DEMAND_CALC_POINT MODE_DEMAND_CALC_POINT_6DOT








PROFUNCTION_EXT u16 KwhPluseNum;//���峣��/100

PROFUNCTION_EXT int ulTypeIb;       // xxx dot x A
PROFUNCTION_EXT int ulTypeImax;     // xxx dot x A
PROFUNCTION_EXT int ulTypeUn;       // xxx dot x V


PROFUNCTION_EXT u16 type_v_duanxian;//ll  (2200*3)/10        //(2200*3)/10  // AAA�����ѹ����AAAAA3-4
PROFUNCTION_EXT u16 type_60per_v;//l   (2200*6)/10  //    (2200*8)/10   //80% v
//aa �����й���С����AAAAAA
PROFUNCTION_EXT ulong type_minvalue_fanxiangyougong;//   0x00003300         //0x00009900  // KW3-4 220v


PROFUNCTION_EXT ulong  kw_set7758_16h;

//   p3--4

PROFUNCTION_EXT u16 imaxsub;
PROFUNCTION_EXT u16 imaxadd;
PROFUNCTION_EXT u16 ibsub;
PROFUNCTION_EXT u16 ibadd;
PROFUNCTION_EXT u16 imaxsub5l;
PROFUNCTION_EXT u16 imaxadd5l;
PROFUNCTION_EXT u16 ibsub5l;
PROFUNCTION_EXT u16 ibadd5l;

//l7758

PROFUNCTION_EXT uchar ucClacMeterKwCoefDiv;
PROFUNCTION_EXT uchar ucClacMeterKwCoefMul;
PROFUNCTION_EXT u16 uiClacMeterVoltageCoef;
PROFUNCTION_EXT u16 uiClacMeterKwCoef;
PROFUNCTION_EXT u16 uiClacMeterKvarCoef;
PROFUNCTION_EXT u16 uiClacMeterKvaCoef;

PROFUNCTION_EXT u16 uiMeterPluseResetDelaySet;
PROFUNCTION_EXT u16 uiMeterDemandResetValue;

PROFUNCTION_EXT uchar ucCurrentType;
#define CURRENT_TYPE    ucCurrentType
PROFUNCTION_EXT u16  uiMeter0d001PerCurrent;//0.01Ib



#define CONST_COMM_SEND_LEADER_FE_NUM_0 0
#define CONST_COMM_SEND_LEADER_FE_NUM_1 1
#define CONST_COMM_SEND_LEADER_FE_NUM_2 2
#define CONST_COMM_SEND_LEADER_FE_NUM_3 3
#define CONST_COMM_SEND_LEADER_FE_NUM_4 4
#define CONST_COMM_SEND_LEADER_FE_NUM  CONST_COMM_SEND_LEADER_FE_NUM_4




/*#define CON_PRICENUM_N0HAVE 0
#define CON_PRICENUM_01         1
#define CON_PRICENUM_02     2
#define CON_PRICENUM_03     3
#define CON_PRICENUM_04     4
#define CON_PRICENUM_05     5
#define CON_PRICENUM_06     6
#define CON_PRICENUM_07     7
#define CON_PRICENUM_08     8
#define CON_PRICENUM_09     9
#define CON_PRICENUM_10     0x0a
#define CON_PRICENUM_11     0x0b
#define CON_PRICENUM_12     0x0c
#define CON_PRICENUM_13     0x0d
#define CON_PRICENUM_14     0x0e*/
//#if (CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE_ENABLE == CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE)
//#define CON_PRICENUM_MAX        CON_PRICENUM_04
//#else
//#define CON_PRICENUM_MAX        CON_PRICENUM_14
//#endif

//#define CON_DAYTABLELEN_12  12
//#define CON_DAYTABLELEN_14  14





//#define CON_SEASONTABLELEN_12   12
//#define CON_SEASONTABLELEN_14   14

#define CON_SEASONTABLELEN_MAX  DLT_SEASON_TABLE_MAX
#define CON_DAYTABLE_MAX        DLT_DAY_TABLE_MAX
#define CON_DAYTABLELEN_MAX     DLT_DAY_PIECE_MAX
#define CON_PRICENUM_MAX        DLT_PRICE_NUM_MAX
#define CON_STEPNUM_MAX         DLT_STEP_NUM_MAX

#define CON_HOLIDAYNUM_MAX      DLT_HOLIDAY_NUM_MAX

//�õ����еķ���������Լ��ֻ���ܣ��޷ַ��ʣ�������Ĭ�϶���Ϊ4
#define CON_PRICENUM_USE_KWH    (4)

/*
0.3(1.2)A       20000       0x01
1(2)A       20000       0x02
1(6)A       20000       0x03
1.5(6)A     20000       0x04
3(6)A       20000       0x05
5(6)A       20000       0x06
1.5(9)A     20000       0x07
2.5(10)A        6400        0x08
5(10)A      AAAA        0x09
5(20)A      1200        0x0A
5(30)A      800         0x0B
5(40)A      600         0x0C
5(60)A      400         0x0D
10(40)A     600         0x0E
10(60)A     400         0x0F
15(60)A     400         0x10
20(80)A     300         0x11
10(100A     200         0x12
20(100)A        200         0x13
5(60)A      600         0x14

*/
#define PROFUNCTION_METER_TYPE_3P4W_577V_0D3_1D2_100000 0x01
#define PROFUNCTION_METER_TYPE_3P4W_577V_01_02_60000        0x02
#define PROFUNCTION_METER_TYPE_3P4W_577V_1D0_06_20000       0x03
#define PROFUNCTION_METER_TYPE_3P4W_577V_1D5_06_20000       0x04
#define PROFUNCTION_METER_TYPE_3P4W_577V_03_06_20000        0x05
#define PROFUNCTION_METER_TYPE_3P4W_577V_05_06_20000        0x06
#define PROFUNCTION_METER_TYPE_3P4W_577V_2D5_10_12800       0x08


#define PROFUNCTION_METER_TYPE_3P3W_100V_1D5_06_20000       0x30
#define PROFUNCTION_METER_TYPE_3P3W_100V_1D5_09_15000       0x31
#define PROFUNCTION_METER_TYPE_3P3W_100V_2D5_10_15000       0x32


#define PROFUNCTION_METER_TYPE_3P4W_220V_0D3_1D2_20000  0x60
#define PROFUNCTION_METER_TYPE_3P4W_220V_1D5_06_5000        0x61
#define PROFUNCTION_METER_TYPE_3P4W_220V_1D5_09_5000        0x62
#define PROFUNCTION_METER_TYPE_3P4W_220V_1D5_06_6400        0x63

#define PROFUNCTION_METER_TYPE_3P4W_220V_5_20_1200      0x68

#define PROFUNCTION_METER_TYPE_3P4W_220V_5_40_800       0x69
#define PROFUNCTION_METER_TYPE_3P4W_220V_5_30_800       0x6a
#define PROFUNCTION_METER_TYPE_3P4W_220V_5_30_1000  0x6b
#define PROFUNCTION_METER_TYPE_3P4W_220V_5_40_600       0x6c
#define PROFUNCTION_METER_TYPE_3P4W_220V_5_60_400       0x6d
#define PROFUNCTION_METER_TYPE_3P4W_220V_5_60_600       0x6e

#define PROFUNCTION_METER_TYPE_3P4W_220V_10_60_800  0x6f
#define PROFUNCTION_METER_TYPE_3P4W_220V_10_40_800  0x70
#define PROFUNCTION_METER_TYPE_3P4W_220V_10_40_600  0x71

#define PROFUNCTION_METER_TYPE_3P4W_220V_10_60_400  0x72
#define PROFUNCTION_METER_TYPE_3P4W_220V_10_60_600  0x73
#define PROFUNCTION_METER_TYPE_3P4W_220V_10_100_200 0x74
#define PROFUNCTION_METER_TYPE_3P4W_220V_10_100_300 0x75
#define PROFUNCTION_METER_TYPE_3P4W_220V_15_60_400  0x78
#define PROFUNCTION_METER_TYPE_3P4W_220V_15_60_800  0x79

#define PROFUNCTION_METER_TYPE_3P4W_220V_20_80_400  0x7b
#define PROFUNCTION_METER_TYPE_3P4W_220V_20_80_300  0x7c
#define PROFUNCTION_METER_TYPE_3P4W_220V_20_100_300 0x7d
#define PROFUNCTION_METER_TYPE_3P4W_220V_20_100_200 0x7e

#define PROFUNCTION_METER_TYPE_ALL                      0xFF



//--AA �벻Ҫ������������ã���Ϊ�������Ѿ���ȫ֧����������AA--
#define PROFUNCTION_METER_TYPE PROFUNCTION_METER_TYPE_ALL


PROFUNCTION_EXT const u16 TB_VOLTAGE_TYPE_TO_COEF[];

PROFUNCTION_EXT void ProgFunctionLoad(void);

PROFUNCTION_EXT uchar WriteProgramData(const uchar* pSrc, ulong DataName, u16 nLen);

PROFUNCTION_EXT unsigned long bcd_to_hex_2(unsigned char *bcd);

PROFUNCTION_EXT unsigned long hex_to_bcd_3(unsigned long hex_val);

PROFUNCTION_EXT unsigned long bcd_to_hex_3(unsigned char *bcd);

PROFUNCTION_EXT unsigned long bcd_to_hex_4(unsigned char *bcd);

PROFUNCTION_EXT unsigned long hex_to_bcd_4(unsigned long hex_val);
	
#endif  

