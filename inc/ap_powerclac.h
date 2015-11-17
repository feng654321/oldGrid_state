
#ifndef AP_POWERCLAC_H
    #define AP_POWERCLAC_H
#ifdef  AP_POWERCLAC_GLOBALS
    #define AP_POWERCLAC_EXT
#else
    #define AP_POWERCLAC_EXT extern
#endif  



#define CON_CLAC_PLUSE_POWER_COEF   100
AP_POWERCLAC_EXT ulong ulClacPlusePowerCoef ;

AP_POWERCLAC_EXT UN_METERSTATUS_CHARACTER_ACTIVE_PARAM unPowerKwhC1Mode;
AP_POWERCLAC_EXT UN_METERSTATUS_CHARACTER_REACTIVE_PARAM  unPowerKvahC1mode;
AP_POWERCLAC_EXT UN_METERSTATUS_CHARACTER_REACTIVE_PARAM  unPowerKvahC2mode;



#if (CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE_ENABLE == CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE)
#define CON_POWER_PLUSE_RESIDUE_MAX (51+16)
#else
#define CON_POWER_PLUSE_RESIDUE_MAX (51)
#endif
#define POWER_KW_F_ALL_DATA 0   //  AA  ��ǰ�����й��ܵ��������ۼ�  AA
#define POWER_KW_R_ALL_DATA 1   //  AA  ��ǰ�����й��ܵ��������ۼ�  AA
#define POWER_KVAR_Q1_ALL_DATA  2   //  AA  ��ǰ1�����޹��ܵ��������ۼ� AA
#define POWER_KVAR_Q2_ALL_DATA  3   //  AA  ��ǰ2�����޹��ܵ��������ۼ� AA
#define POWER_KVAR_Q3_ALL_DATA  4   //  AA  ��ǰ3�����޹��ܵ��������ۼ� AA
#define POWER_KVAR_Q4_ALL_DATA  5   //  AA  ��ǰ4�����޹��ܵ��������ۼ� AA
#define	POWER_KVA_F_ALL_DATA	6	//	AA	��ǰ���������ܵ��������ۼ�	AA
#define	POWER_KVA_R_ALL_DATA	7	//	AA	��ǰ���������ܵ��������ۼ�	AA
#define	POWER_KW_A_F_ALL_DATA	8	//	AA	��ǰA�������й����������ۼ�	AA
#define	POWER_KW_A_R_ALL_DATA	9	//	AA	��ǰA�෴���й����������ۼ�	AA
#define	POWER_KVAR_A_Q1_ALL_DATA	10	//	AA	��ǰA��1�����޹����������ۼ�	AA
#define	POWER_KVAR_A_Q2_ALL_DATA	11	//	AA	��ǰA��2�����޹����������ۼ�	AA
#define	POWER_KVAR_A_Q3_ALL_DATA	12	//	AA	��ǰA��3�����޹����������ۼ�	AA
#define	POWER_KVAR_A_Q4_ALL_DATA	13	//	AA	��ǰA��4�����޹����������ۼ�	AA
#define	POWER_KVA_A_F_ALL_DATA	14	//	AA	��ǰA���������ڵ��������ۼ�	AA
#define	POWER_KVA_A_R_ALL_DATA	15	//	AA	��ǰA�෴�����ڵ��������ۼ�	AA
#define	POWER_KW_B_F_ALL_DATA	16	//	AA	��ǰB�������й����������ۼ�	AA
#define	POWER_KW_B_R_ALL_DATA	17	//	AA	��ǰB�෴���й����������ۼ�	AA
#define	POWER_KVAR_B_Q1_ALL_DATA	18	//	AA	��ǰB��1�����޹����������ۼ�	AA
#define	POWER_KVAR_B_Q2_ALL_DATA	19	//	AA	��ǰB��2�����޹����������ۼ�	AA
#define	POWER_KVAR_B_Q3_ALL_DATA	20	//	AA	��ǰB��3�����޹����������ۼ�	AA
#define	POWER_KVAR_B_Q4_ALL_DATA	21	//	AA	��ǰB��4�����޹����������ۼ�	AA
#define	POWER_KVA_B_F_ALL_DATA	22	//	AA	��ǰB���������ڵ��������ۼ�	AA
#define	POWER_KVA_B_R_ALL_DATA	23	//	AA	��ǰB�෴�����ڵ��������ۼ�	AA
#define	POWER_KW_C_F_ALL_DATA	24	//	AA	��ǰC�������й����������ۼ�	AA
#define	POWER_KW_C_R_ALL_DATA	25	//	AA	��ǰC�෴���й����������ۼ�	AA
#define	POWER_KVAR_C_Q1_ALL_DATA	26	//	AA	��ǰC��1�����޹����������ۼ�	AA
#define	POWER_KVAR_C_Q2_ALL_DATA	27	//	AA	��ǰC��2�����޹����������ۼ�	AA
#define	POWER_KVAR_C_Q3_ALL_DATA	28	//	AA	��ǰC��3�����޹����������ۼ�	AA
#define	POWER_KVAR_C_Q4_ALL_DATA	29	//	AA	��ǰC��4�����޹����������ۼ�	AA
#define	POWER_KVA_C_F_ALL_DATA	30	//	AA	��ǰC���������ڵ��������ۼ�	AA
#define	POWER_KVA_C_R_ALL_DATA	31	//	AA	��ǰC�෴�����ڵ��������ۼ�	AA
#define	POWER_KW_ALL_DATA_END	32	//	AA	��ǰ�����й��ܵ��������ۼӽ���	AA
#define	POWER_KW_FR_ALL_DATA	32	//	AA	��ǰ�й����ӷ����������ۼ�	AA
#define	POWER_KW_C_ALL_ADD_DATA	33	//	AA	��ǰ����й����ӵ��������ۼ�	AA
#define	POWER_KW_C_ALL_SUB_DATA	34	//	AA	��ǰ����й����ٵ��������ۼ�	AA
#define	POWER_KVAR_C1_ALL_ADD_DATA	35	//	AA	��ǰ����޹�1�������Ӽ����ۼ�	AA
#define	POWER_KVAR_C1_ALL_SUB_DATA	36	//	AA	��ǰ����޹�1�������ټ����ۼ�	AA
#define	POWER_KVAR_C2_ALL_ADD_DATA	37	//	AA	��ǰ����޹�2�������Ӽ����ۼ�	AA
#define	POWER_KVAR_C2_ALL_SUB_DATA	38	//	AA	��ǰ����޹�2�������ټ����ۼ�	AA
#define	POWER_KVAR_A_C1_ALL_ADD_DATA	39	//	AA	��ǰA������޹�1�������Ӽ����ۼ�	AA
#define	POWER_KVAR_A_C1_ALL_SUB_DATA	40	//	AA	��ǰA������޹�1�������ټ����ۼ�	AA
#define	POWER_KVAR_A_C2_ALL_ADD_DATA	41	//	AA	��ǰA������޹�2�������Ӽ����ۼ�	AA
#define	POWER_KVAR_A_C2_ALL_SUB_DATA	42	//	AA	��ǰA������޹�2�������ټ����ۼ�	AA
#define	POWER_KVAR_B_C1_ALL_ADD_DATA	43	//	AA	��ǰB������޹�1�������Ӽ����ۼ�	AA
#define	POWER_KVAR_B_C1_ALL_SUB_DATA	44	//	AA	��ǰB������޹�1�������ټ����ۼ�	AA
#define	POWER_KVAR_B_C2_ALL_ADD_DATA	45	//	AA	��ǰB������޹�2�������Ӽ����ۼ�	AA
#define	POWER_KVAR_B_C2_ALL_SUB_DATA	46	//	AA	��ǰB������޹�2�������ټ����ۼ�	AA
#define	POWER_KVAR_C_C1_ALL_ADD_DATA	47	//	AA	��ǰC������޹�1�������Ӽ����ۼ�	AA
#define	POWER_KVAR_C_C1_ALL_SUB_DATA	48	//	AA	��ǰC������޹�1�������ټ����ۼ�	AA
#define	POWER_KVAR_C_C2_ALL_ADD_DATA	49	//	AA	��ǰC������޹�2�������Ӽ����ۼ�	AA
#define	POWER_KVAR_C_C2_ALL_SUB_DATA	50	//	AA	��ǰC������޹�2�������ټ����ۼ�	AA
#if (CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE_ENABLE == CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE)
#define	POWER_KW_C_ALL_ADD_DATA_PRICE1	51	//	AA	��ǰ����й�����1�������Ӽ����ۼ�	AA
#define	POWER_KW_C_ALL_ADD_DATA_PRICE2	52	//	AA	��ǰ����й�����2�������Ӽ����ۼ�	AA
#define	POWER_KW_C_ALL_ADD_DATA_PRICE3	53	//	AA	��ǰ����й�����3�������Ӽ����ۼ�	AA
#define	POWER_KW_C_ALL_ADD_DATA_PRICE4	54	//	AA	��ǰ����й�����4�������Ӽ����ۼ�	AA
#define	POWER_KW_C_ALL_SUB_DATA_PRICE1	55	//	AA	��ǰ����й�����1�������ټ����ۼ�	AA
#define	POWER_KW_C_ALL_SUB_DATA_PRICE2	56	//	AA	��ǰ����й�����2�������ټ����ۼ�	AA
#define	POWER_KW_C_ALL_SUB_DATA_PRICE3	57	//	AA	��ǰ����й�����3�������ټ����ۼ�	AA
#define	POWER_KW_C_ALL_SUB_DATA_PRICE4	58	//	AA	��ǰ����й�����4�������ټ����ۼ�	AA
#define	POWER_KW_ALL_PRICE_DATA_START	59	//	AA	��ǰ�������й������ʵ��������ۼ���ʼ	AA
#define	POWER_KW_F_ALL_DATA_PRICE1	59	//	AA	��ǰ�����й�����1���������ۼ�	AA
#define	POWER_KW_F_ALL_DATA_PRICE2	60	//	AA	��ǰ�����й�����2���������ۼ�	AA
#define	POWER_KW_F_ALL_DATA_PRICE3	61	//	AA	��ǰ�����й�����3���������ۼ�	AA
#define	POWER_KW_F_ALL_DATA_PRICE4	62	//	AA	��ǰ�����й�����4���������ۼ�	AA
#define	POWER_KW_R_ALL_DATA_PRICE1	63	//	AA	��ǰ�����й�����1���������ۼ�	AA
#define	POWER_KW_R_ALL_DATA_PRICE2	64	//	AA	��ǰ�����й�����2���������ۼ�	AA
#define	POWER_KW_R_ALL_DATA_PRICE3	65	//	AA	��ǰ�����й�����3���������ۼ�	AA
#define	POWER_KW_R_ALL_DATA_PRICE4	66	//	AA	��ǰ�����й�����4���������ۼ�	AA
#endif      
      

AP_POWERCLAC_EXT uchar ucPowerClacAddFlg[CON_POWER_PLUSE_RESIDUE_MAX];










AP_POWERCLAC_EXT  void GetPowerClacResidue(void);

AP_POWERCLAC_EXT  void SetPowerClacResidue(void);

AP_POWERCLAC_EXT void PowerClacInit(void);

AP_POWERCLAC_EXT void PowerClacMode(void);

AP_POWERCLAC_EXT void PowerClacOneSecondAdd(void);

AP_POWERCLAC_EXT void PowerClacResidueClr(void);









































#endif

