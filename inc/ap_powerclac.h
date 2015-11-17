
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
#define POWER_KW_F_ALL_DATA 0   //  AA  当前正向有功总电量计算累加  AA
#define POWER_KW_R_ALL_DATA 1   //  AA  当前反向有功总电量计算累加  AA
#define POWER_KVAR_Q1_ALL_DATA  2   //  AA  当前1象限无功总电量计算累加 AA
#define POWER_KVAR_Q2_ALL_DATA  3   //  AA  当前2象限无功总电量计算累加 AA
#define POWER_KVAR_Q3_ALL_DATA  4   //  AA  当前3象限无功总电量计算累加 AA
#define POWER_KVAR_Q4_ALL_DATA  5   //  AA  当前4象限无功总电量计算累加 AA
#define	POWER_KVA_F_ALL_DATA	6	//	AA	当前正向视在总电量计算累加	AA
#define	POWER_KVA_R_ALL_DATA	7	//	AA	当前反向视在总电量计算累加	AA
#define	POWER_KW_A_F_ALL_DATA	8	//	AA	当前A相正相有功电量计算累加	AA
#define	POWER_KW_A_R_ALL_DATA	9	//	AA	当前A相反相有功电量计算累加	AA
#define	POWER_KVAR_A_Q1_ALL_DATA	10	//	AA	当前A相1象限无功电量计算累加	AA
#define	POWER_KVAR_A_Q2_ALL_DATA	11	//	AA	当前A相2象限无功电量计算累加	AA
#define	POWER_KVAR_A_Q3_ALL_DATA	12	//	AA	当前A相3象限无功电量计算累加	AA
#define	POWER_KVAR_A_Q4_ALL_DATA	13	//	AA	当前A相4象限无功电量计算累加	AA
#define	POWER_KVA_A_F_ALL_DATA	14	//	AA	当前A相正相视在电量计算累加	AA
#define	POWER_KVA_A_R_ALL_DATA	15	//	AA	当前A相反相视在电量计算累加	AA
#define	POWER_KW_B_F_ALL_DATA	16	//	AA	当前B相正相有功电量计算累加	AA
#define	POWER_KW_B_R_ALL_DATA	17	//	AA	当前B相反相有功电量计算累加	AA
#define	POWER_KVAR_B_Q1_ALL_DATA	18	//	AA	当前B相1象限无功电量计算累加	AA
#define	POWER_KVAR_B_Q2_ALL_DATA	19	//	AA	当前B相2象限无功电量计算累加	AA
#define	POWER_KVAR_B_Q3_ALL_DATA	20	//	AA	当前B相3象限无功电量计算累加	AA
#define	POWER_KVAR_B_Q4_ALL_DATA	21	//	AA	当前B相4象限无功电量计算累加	AA
#define	POWER_KVA_B_F_ALL_DATA	22	//	AA	当前B相正相视在电量计算累加	AA
#define	POWER_KVA_B_R_ALL_DATA	23	//	AA	当前B相反相视在电量计算累加	AA
#define	POWER_KW_C_F_ALL_DATA	24	//	AA	当前C相正相有功电量计算累加	AA
#define	POWER_KW_C_R_ALL_DATA	25	//	AA	当前C相反相有功电量计算累加	AA
#define	POWER_KVAR_C_Q1_ALL_DATA	26	//	AA	当前C相1象限无功电量计算累加	AA
#define	POWER_KVAR_C_Q2_ALL_DATA	27	//	AA	当前C相2象限无功电量计算累加	AA
#define	POWER_KVAR_C_Q3_ALL_DATA	28	//	AA	当前C相3象限无功电量计算累加	AA
#define	POWER_KVAR_C_Q4_ALL_DATA	29	//	AA	当前C相4象限无功电量计算累加	AA
#define	POWER_KVA_C_F_ALL_DATA	30	//	AA	当前C相正相视在电量计算累加	AA
#define	POWER_KVA_C_R_ALL_DATA	31	//	AA	当前C相反相视在电量计算累加	AA
#define	POWER_KW_ALL_DATA_END	32	//	AA	当前正向有功总电量计算累加结束	AA
#define	POWER_KW_FR_ALL_DATA	32	//	AA	当前有功正加反电量计算累加	AA
#define	POWER_KW_C_ALL_ADD_DATA	33	//	AA	当前组合有功增加电量计算累加	AA
#define	POWER_KW_C_ALL_SUB_DATA	34	//	AA	当前组合有功减少电量计算累加	AA
#define	POWER_KVAR_C1_ALL_ADD_DATA	35	//	AA	当前组合无功1电量增加计算累加	AA
#define	POWER_KVAR_C1_ALL_SUB_DATA	36	//	AA	当前组合无功1电量减少计算累加	AA
#define	POWER_KVAR_C2_ALL_ADD_DATA	37	//	AA	当前组合无功2电量增加计算累加	AA
#define	POWER_KVAR_C2_ALL_SUB_DATA	38	//	AA	当前组合无功2电量减少计算累加	AA
#define	POWER_KVAR_A_C1_ALL_ADD_DATA	39	//	AA	当前A相组合无功1电量增加计算累加	AA
#define	POWER_KVAR_A_C1_ALL_SUB_DATA	40	//	AA	当前A相组合无功1电量减少计算累加	AA
#define	POWER_KVAR_A_C2_ALL_ADD_DATA	41	//	AA	当前A相组合无功2电量增加计算累加	AA
#define	POWER_KVAR_A_C2_ALL_SUB_DATA	42	//	AA	当前A相组合无功2电量减少计算累加	AA
#define	POWER_KVAR_B_C1_ALL_ADD_DATA	43	//	AA	当前B相组合无功1电量增加计算累加	AA
#define	POWER_KVAR_B_C1_ALL_SUB_DATA	44	//	AA	当前B相组合无功1电量减少计算累加	AA
#define	POWER_KVAR_B_C2_ALL_ADD_DATA	45	//	AA	当前B相组合无功2电量增加计算累加	AA
#define	POWER_KVAR_B_C2_ALL_SUB_DATA	46	//	AA	当前B相组合无功2电量减少计算累加	AA
#define	POWER_KVAR_C_C1_ALL_ADD_DATA	47	//	AA	当前C相组合无功1电量增加计算累加	AA
#define	POWER_KVAR_C_C1_ALL_SUB_DATA	48	//	AA	当前C相组合无功1电量减少计算累加	AA
#define	POWER_KVAR_C_C2_ALL_ADD_DATA	49	//	AA	当前C相组合无功2电量增加计算累加	AA
#define	POWER_KVAR_C_C2_ALL_SUB_DATA	50	//	AA	当前C相组合无功2电量减少计算累加	AA
#if (CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE_ENABLE == CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE)
#define	POWER_KW_C_ALL_ADD_DATA_PRICE1	51	//	AA	当前组合有功费率1电量增加计算累加	AA
#define	POWER_KW_C_ALL_ADD_DATA_PRICE2	52	//	AA	当前组合有功费率2电量增加计算累加	AA
#define	POWER_KW_C_ALL_ADD_DATA_PRICE3	53	//	AA	当前组合有功费率3电量增加计算累加	AA
#define	POWER_KW_C_ALL_ADD_DATA_PRICE4	54	//	AA	当前组合有功费率4电量增加计算累加	AA
#define	POWER_KW_C_ALL_SUB_DATA_PRICE1	55	//	AA	当前组合有功费率1电量减少计算累加	AA
#define	POWER_KW_C_ALL_SUB_DATA_PRICE2	56	//	AA	当前组合有功费率2电量减少计算累加	AA
#define	POWER_KW_C_ALL_SUB_DATA_PRICE3	57	//	AA	当前组合有功费率3电量减少计算累加	AA
#define	POWER_KW_C_ALL_SUB_DATA_PRICE4	58	//	AA	当前组合有功费率4电量减少计算累加	AA
#define	POWER_KW_ALL_PRICE_DATA_START	59	//	AA	当前正反向有功各费率电量计算累加起始	AA
#define	POWER_KW_F_ALL_DATA_PRICE1	59	//	AA	当前正向有功费率1电量计算累加	AA
#define	POWER_KW_F_ALL_DATA_PRICE2	60	//	AA	当前正向有功费率2电量计算累加	AA
#define	POWER_KW_F_ALL_DATA_PRICE3	61	//	AA	当前正向有功费率3电量计算累加	AA
#define	POWER_KW_F_ALL_DATA_PRICE4	62	//	AA	当前正向有功费率4电量计算累加	AA
#define	POWER_KW_R_ALL_DATA_PRICE1	63	//	AA	当前反向有功费率1电量计算累加	AA
#define	POWER_KW_R_ALL_DATA_PRICE2	64	//	AA	当前反向有功费率2电量计算累加	AA
#define	POWER_KW_R_ALL_DATA_PRICE3	65	//	AA	当前反向有功费率3电量计算累加	AA
#define	POWER_KW_R_ALL_DATA_PRICE4	66	//	AA	当前反向有功费率4电量计算累加	AA
#endif      
      

AP_POWERCLAC_EXT uchar ucPowerClacAddFlg[CON_POWER_PLUSE_RESIDUE_MAX];










AP_POWERCLAC_EXT  void GetPowerClacResidue(void);

AP_POWERCLAC_EXT  void SetPowerClacResidue(void);

AP_POWERCLAC_EXT void PowerClacInit(void);

AP_POWERCLAC_EXT void PowerClacMode(void);

AP_POWERCLAC_EXT void PowerClacOneSecondAdd(void);

AP_POWERCLAC_EXT void PowerClacResidueClr(void);









































#endif

