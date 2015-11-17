#ifndef AP_DEMAND_H
    #define AP_DEMAND_H
    
#ifdef  AP_DEMAND_GLOBALS
    #define AP_DEMAND_EXT
#else
    #define AP_DEMAND_EXT extern
#endif  

#define DEMAND_OVER_NUM             8

#define PTD_DEMAND_COUNT            32
#define DEMAND_BUFFER_TIME_COUNT    60

#define BYTES_PER_DEMAND             9
#define DEMAND_COUNT_WITH_FEE       (DLT_PRICE_NUM_MAX)
#define BYTES_DEMAND_TOTAL          (RAM_DEMAND_DATA_END - RAM_DEMAND_DATA_START)

#define PTD_KW_F_ALL_DATA 0 // AA 当前正向有功总最大需量指针 AA
#define PTD_KW_R_ALL_DATA 1 // AA 当前反向有功总最大需量指针 AA
#define PTD_KVAR_Q1_ALL_DATA 2 // AA 当前1象限无功总最大需量指针 AA
#define PTD_KVAR_Q2_ALL_DATA 3 // AA 当前2象限无功总最大需量指针 AA
#define PTD_KVAR_Q3_ALL_DATA 4 // AA 当前3象限无功总最大需量指针 AA
#define PTD_KVAR_Q4_ALL_DATA 5 // AA 当前4象限无功总最大需量指针 AA
#define PTD_KVA_F_ALL_DATA 6 // AA 当前正向视在总最大需量指针 AA
#define PTD_KVA_R_ALL_DATA 7 // AA 当前反向视在总最大需量指针 AA
#define PTD_KW_A_F_ALL_DATA 8 // AA 当前A相正相有功最大需量指针 AA
#define PTD_KW_A_R_ALL_DATA 9 // AA 当前A相反相有功最大需量指针 AA
#define PTD_KVAR_A_Q1_ALL_DATA 10 // AA 当前A相1象限无功最大需量指针 AA
#define PTD_KVAR_A_Q2_ALL_DATA 11 // AA 当前A相2象限无功最大需量指针 AA
#define PTD_KVAR_A_Q3_ALL_DATA 12 // AA 当前A相3象限无功最大需量指针 AA
#define PTD_KVAR_A_Q4_ALL_DATA 13 // AA 当前A相4象限无功最大需量指针 AA
#define PTD_KVA_A_F_ALL_DATA 14 // AA 当前A相正相视在最大需量指针 AA
#define PTD_KVA_A_R_ALL_DATA 15 // AA 当前A相反相视在最大需量指针 AA
#define PTD_KW_B_F_ALL_DATA 16 // AA 当前B相正相有功最大需量指针 AA
#define PTD_KW_B_R_ALL_DATA 17 // AA 当前B相反相有功最大需量指针 AA
#define PTD_KVAR_B_Q1_ALL_DATA 18 // AA 当前B相1象限无功最大需量指针 AA
#define PTD_KVAR_B_Q2_ALL_DATA 19 // AA 当前B相2象限无功最大需量指针 AA
#define PTD_KVAR_B_Q3_ALL_DATA 20 // AA 当前B相3象限无功最大需量指针 AA
#define PTD_KVAR_B_Q4_ALL_DATA 21 // AA 当前B相4象限无功最大需量指针 AA
#define PTD_KVA_B_F_ALL_DATA 22 // AA 当前B相正相视在最大需量指针 AA
#define PTD_KVA_B_R_ALL_DATA 23 // AA 当前B相反相视在最大需量指针 AA
#define PTD_KW_C_F_ALL_DATA 24 // AA 当前C相正相有功最大需量指针 AA
#define PTD_KW_C_R_ALL_DATA 25 // AA 当前C相反相有功最大需量指针 AA
#define PTD_KVAR_C_Q1_ALL_DATA 26 // AA 当前C相1象限无功最大需量指针 AA
#define PTD_KVAR_C_Q2_ALL_DATA 27 // AA 当前C相2象限无功最大需量指针 AA
#define PTD_KVAR_C_Q3_ALL_DATA 28 // AA 当前C相3象限无功最大需量指针 AA
#define PTD_KVAR_C_Q4_ALL_DATA 29 // AA 当前C相4象限无功最大需量指针 AA
#define PTD_KVA_C_F_ALL_DATA 30 // AA 当前C相正相视在最大需量指针 AA
#define PTD_KVA_C_R_ALL_DATA 31 // AA 当前C相反相视在最大需量指针 AA

#define PTD_KVAR_C1C2_COUNT 10
#define PTD_KAVR_C1_ALL_DATA 0      // AA all C1 
#define PTD_KAVR_C2_ALL_DATA 1      // AA all C2 
#define PTD_KAVR_A_C1_ALL_DATA 2		// AA a C1 
#define PTD_KAVR_A_C2_ALL_DATA 3		// AA a C2
#define PTD_KAVR_B_C1_ALL_DATA 4		// AA b C1 
#define PTD_KAVR_B_C2_ALL_DATA 5		// AA b C2
#define PTD_KAVR_C_C1_ALL_DATA 6		// AA c C1 
#define PTD_KAVR_C_C2_ALL_DATA 7		// AA c C2
#define PTD_KAVR_C1_PRICE_DATA 8		// AA all C1 
#define PTD_KAVR_C2_PRICE_DATA 9		// AA all C2 

// add by ybf 100826
typedef struct
{
    ulong ulDemand;
    uchar ucTime[5];
}ST_DEMAND_OVER_DATA;

AP_DEMAND_EXT uchar ucTempCurrentDemandPrice;


//AP_DEMAND_EXT UN_METERSTATUS_CHARACTER_REACTIVE_PARAM uuReactiveMode01,uuReactiveMode02;
#define uuReactiveMode01    unPowerKvahC1mode
#define uuReactiveMode02    unPowerKvahC2mode

AP_DEMAND_EXT u16 uiDemandClacBuffer[PTD_DEMAND_COUNT][DEMAND_BUFFER_TIME_COUNT];
AP_DEMAND_EXT ulong ulDemandClacKvarC1C2SumBuffer[PTD_KVAR_C1C2_COUNT]; //可以用局部临时变量，但数量比较大了
AP_DEMAND_EXT ulong ulKwPerMinute[PTD_DEMAND_COUNT];  //it can be replaced by uiDemandClacBuffer[ucPoint][ucDemandClcyeStart]
AP_DEMAND_EXT uchar ucKwPerSecondCount;

AP_DEMAND_EXT uchar ucDemandPriceDemandTimeChange;

// add by ybf 2010..8.26
AP_DEMAND_EXT ST_DEMAND_OVER_DATA DemandOverData[DEMAND_OVER_NUM];     // 需量超限缓存区
AP_DEMAND_EXT const uchar TB_DEMANDOVER_ADDBIT[8];

AP_DEMAND_EXT void DemandDataInit(void);

AP_DEMAND_EXT void DemandMode(void);

AP_DEMAND_EXT ulong ClacDemandFromPower(ulong value);
AP_DEMAND_EXT uchar CompareDemand(ulong ulAddr);

//AP_DEMAND_EXT void CopyDemandRamtoFm2(ulong ulRamAddr);
AP_DEMAND_EXT void  DemandStorNowTime(void);
AP_DEMAND_EXT uchar  ComPareMaxDemandFromAddr(ulong ulData,ulong ulAddr);

AP_DEMAND_EXT void DemandPulseOut(void);

AP_DEMAND_EXT void DemandPriceChange(void);

AP_DEMAND_EXT void DemandResume(void);

AP_DEMAND_EXT uchar DemandDataClrAllCurrent(void);

AP_DEMAND_EXT void AddOneSecondKwMode(void);
AP_DEMAND_EXT void DemandParaInit(void);

AP_DEMAND_EXT void DemandOverInit(void);
AP_DEMAND_EXT void DemandOverParaInit(void);

AP_DEMAND_EXT void DemandOverStart(uchar ucType);

AP_DEMAND_EXT void DemandOverStopIfStart(void);

AP_DEMAND_EXT void DemandOverEnd(uchar ucType);

AP_DEMAND_EXT void DemandOverChange(uchar ucType);

// AP_DEMAND_EXT void DemandOverTimeAdd(void);

AP_DEMAND_EXT void DemandOverMode(uchar ucDemandType);

AP_DEMAND_EXT  uchar CompareRamDataAndMoveToMax(u16 uiMaxAddr,u16 uiFromAddr);

AP_DEMAND_EXT void SaveMDByTimeStamp(void);

#endif













