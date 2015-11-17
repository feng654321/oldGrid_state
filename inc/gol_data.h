#ifndef AP_DATA_H
    #define AP_DATA_H
    
#ifdef  AP_DATA_GLOBALS
    #define AP_DATA_EXT
#else
    #define AP_DATA_EXT extern
#endif  

#define FILE_EPL            "/usr1/etc/epl.dat"
#define FILE_BAK            "/usr1/etc/bak.dat"
#define FILE_FLASH          "/mnt/dbf/flash.dat"
#define FILE_LEN_EPL        (1024*32)
#define FILE_LEN_BAK        (1024*4)    //(EPL_COEF_DATA_END - EPL_COEF_DATA_START)
#define FILE_LEN_FLASH      (1024*1024*8)

#if (CONFIG_METER_POWERDOWN_DISPLAY_MODE_ENABLE == CONFIG_METER_POWERDOWN_DISPLAY_MODE)  //tzg
#define TINGXIAN_SHIJIAN   (3600*24*7+3628) //(3600*24*1+432)以秒为单位
AP_DATA_EXT ulong tingdian_miao_count;
#endif
#define HIGH_BYTE_FRONT 0x45
#define LOW_BYTE_FRONT 0x67
#define CON_POWER_STATUS_USE_MAINPOWER 0x00
#define CON_POWER_STATUS_USE_WAKEUPBAT 0x02
#define CON_POWER_STATUS_USE_AUXPOWER 0x01



#define CON_TIME_COUNT_MINUTE       60
#define CON_TIME_COUNT_HOUR     3600        // -- 60*60
#define CON_TIME_COUNT_DAY      86400       // -- 60*60*24

#if(CONFIG_METER_SW_DEBUG_MODE == GAL_YES)
AP_DATA_EXT uchar ucSystemResetMode;
#endif

#define CONST_RAM_LEN (RAM_MEMORY_ADDR_END&0x00ffffff)
    //主要是为了确保RAM数组的自然对齐
//AP_DATA_EXT uchar RAM[CONST_RAM_LEN];
AP_DATA_EXT ulong ulRAM[(CONST_RAM_LEN+3)/4];
AP_DATA_EXT uchar* RAM;

AP_DATA_EXT uchar ucProgramFlashWait;       // 操作Flash等待时间,单位为10mS
AP_DATA_EXT uchar ucSystemResetOk;          //系统启动检测正常指标变量
#define CON_SYSTEM_REST_OK                  (10)
#define isSystemResetOK                     (ucSystemResetOk >= CON_SYSTEM_REST_OK)
#define isSystemResetUnfinisded             (ucSystemResetOk < CON_SYSTEM_REST_OK)


AP_DATA_EXT uchar ucSystemBusy;// write eeprom 5,or read 5460a
// AP_DATA_EXT uchar system_control_time1;//lost v,lost i,over ,moniter,nixiangxu
// AP_DATA_EXT uchar system_control_time2;//dongjie,fuhe zhuancun


#define CON_WR_DATA_LEN_MAX (1024+50)    //530  主要用在电量类型加大后临时处理,用在电量上电检测和恢复
AP_DATA_EXT uchar Wr_data[CON_WR_DATA_LEN_MAX];
AP_DATA_EXT uchar Ap_temp[16];
//uchar *Ap_temp = &(RAM[RAM_TEMP_ADDR]);

#if((RAM_CURRENT_METER_STATUS01%4) != 0)
#error "RAM_CURRENT_METER_STATUS01地址需要按4对齐"
#endif
#define stMeterStatusChar01 ((ST_METERSTATUS_CHAR_1_2_PARAM*)(&RAM[RAM_CURRENT_METER_STATUS01]))
#define stMeterStatusChar02 ((ST_METERSTATUS_CHAR_1_2_PARAM*)(&RAM[RAM_CURRENT_METER_STATUS01]))
#define stMeterStatusChar03 ((ST_METERSTATUS_CHAR_3_4_PARAM*)(&RAM[RAM_CURRENT_METER_STATUS03]))
#define stMeterStatusPhaseA ((ST_METERSTATUS_CHAR_3_4_PARAM*)(&RAM[RAM_CURRENT_METER_STATUS03]))
#define stMeterStatusPhaseB ((ST_METERSTATUS_CHAR_5_6_PARAM*)(&RAM[RAM_CURRENT_METER_STATUS05]))
#define stMeterStatusPhaseC ((ST_METERSTATUS_CHAR_5_6_PARAM*)(&RAM[RAM_CURRENT_METER_STATUS05]))
#define stMeterStatusPhaseAll ((ST_METERSTATUS_CHAR7_PARAM*)(&RAM[RAM_CURRENT_METER_STATUS07]))

#if((RAM_CURRENT_METER_STATUS_OTHER%4) != 0)
#error "RAM_CURRENT_METER_STATUS_OTHER地址需要按4对齐"
#endif
#define stMeterStatusOther01 ((UN_U32_PARAM*)(&RAM[RAM_CURRENT_METER_STATUS_OTHER]))
#define stMeterStatusOther02 ((UN_U32_PARAM*)(&RAM[RAM_CURRENT_METER_STATUS_OTHER]))
#define stMeterStatusDemandOver ((UN_U32_PARAM*)(&RAM[RAM_CURRENT_METER_STATUS_OTHER]))

//#define stMonitorVoltageStatus ((ST_MONITOR_VOLTAGE_STATUS_PARAM*)(&RAM[RAM_CURRENT_MONITOR_VOLTAGE_STATUS]))
ST_MONITOR_VOLTAGE_STATUS_PARAM stMonitorVoltageStatus;

#if(CONFIG_METER_TYPE_SD39C==CONFIG_METER_TYPE)
#define CON_PROGRAM_TIME_MAX 120
#else
#define CON_PROGRAM_TIME_MAX 240
#endif
//#define stRelayStatus ((ST_U8_PARAM*)(&RAM[RAM_CURRENT_RELAY_STATUS]))

#if((RAM_SOFT_TIME%4) != 0)
#error "RAM_SOFT_TIME地址需要按4对齐"
#endif
#define stTime ((ST_DATE_TIME_PARAM*)(&RAM[RAM_SOFT_TIME]))


/*
AP_DATA_EXT UN_METERSTATUS_CHAR1_PARAM unMeterStatusChar1;
AP_DATA_EXT UN_METERSTATUS_CHAR2_PARAM unMeterStatusChar2;
AP_DATA_EXT UN_METERSTATUS_CHAR3_PARAM unMeterStatusChar3;
AP_DATA_EXT UN_METERSTATUS_CHAR4_5_6_PARAM unMeterStatusPhaseA;
AP_DATA_EXT UN_METERSTATUS_CHAR4_5_6_PARAM unMeterStatusPhaseB;
AP_DATA_EXT UN_METERSTATUS_CHAR4_5_6_PARAM unMeterStatusPhaseC;
AP_DATA_EXT UN_METERSTATUS_CHAR7_PARAM unMeterStatusAll;

AP_DATA_EXT UN_U8_PARAM unMeterStatusOther;
AP_DATA_EXT UN_U8_PARAM unDemandOverStatus;
*/

// CHAR 1
#define FLG_DEMANDCLACMODE          stMeterStatusChar01->bDemandCalcMode
#define FLG_BATTIMELOW_STATUS       stMeterStatusChar01->bBatTimeStatus
#define FLG_BATWAKEUP_STATUS        stMeterStatusChar01->bBatWakeupStatus
#define FLG_REVERSEKW_ALL_STATUS    stMeterStatusChar01->bReverseKw
#define FLG_REVERSEKVAR_ALL_STATUS  stMeterStatusChar01->bReverseKvar

// CHAR 2
#define FLG_REVERSEKW_A_STATUS      stMeterStatusChar02->bAKwReverse
#define FLG_REVERSEKW_B_STATUS      stMeterStatusChar02->bBKwReverse
#define FLG_REVERSEKW_C_STATUS      stMeterStatusChar02->bCKwReverse
#define FLG_REVERSEKVAR_A_STATUS    stMeterStatusChar02->bAKvarReverse
#define FLG_REVERSEKVAR_B_STATUS    stMeterStatusChar02->bBKvarReverse
#define FLG_REVERSEKVAR_C_STATUS    stMeterStatusChar02->bCKvarReverse



// CHAR 3
#define FLG_PROGRAM_STATUS          stMeterStatusChar03->bProgramStatus
#define FLG_RELAY_STATUS            stMeterStatusChar03->bRelayStatus
#define FLG_SEASON_STATUS           stMeterStatusChar03->bSeasonStatus
#define FLG_POWER_STATUS            stMeterStatusChar03->bPowerMode
#define FLG_DAYTABLE_STATUS         stMeterStatusChar03->bDayTableStatus


#define FLG_RELAYCOMMAND_STATUS         stMeterStatusChar03->bRelayCommandStatus
#define FLG_RELAYPREALARM_STATUS        stMeterStatusChar03->bRelayPreAlarmStatus
#define FLG_METERPREPAY_TYPE            stMeterStatusChar03->bMeterPrePayType
#define FLG_PERIODPRICETABLE_STATUS     stMeterStatusChar03->bPeriodPriceTableStatus    // ok
#define FLG_STEPPRICETABLE_STATUS       stMeterStatusChar03->bStepPriceTableStatus  // ok





// CHAR 4 PHASE A
#define FLG_A_LOSS_VOLTAGE_STATUS   stMeterStatusPhaseA->bLossVoltage
#define FLG_A_DOWN_VOLTAGE_STATUS   stMeterStatusPhaseA->bDownVoltage
#define FLG_A_OVER_VOLTAGE_STATUS   stMeterStatusPhaseA->bOverVoltage
#define FLG_A_LOSS_CURRENT_STATUS   stMeterStatusPhaseA->bLossCurrent
#define FLG_A_OVER_CURRENT_STATUS   stMeterStatusPhaseA->bOverCurrent
#define FLG_A_OVER_KW_STATUS        stMeterStatusPhaseA->bOverKw
#define FLG_A_REVERSEKW_STATUS      stMeterStatusPhaseA->bReverseKw
#define FLG_A_CUT_VOLTAGE_STATUS    stMeterStatusPhaseA->bCutVoltage
#define FLG_A_CUT_CURRENT_STATUS    stMeterStatusPhaseA->bCutCurrent


// CHAR 5 PHASE B
#define FLG_B_LOSS_VOLTAGE_STATUS   stMeterStatusPhaseB->bBLossVoltage
#define FLG_B_DOWN_VOLTAGE_STATUS   stMeterStatusPhaseB->bBDownVoltage
#define FLG_B_OVER_VOLTAGE_STATUS   stMeterStatusPhaseB->bBOverVoltage
#define FLG_B_LOSS_CURRENT_STATUS   stMeterStatusPhaseB->bBLossCurrent
#define FLG_B_OVER_CURRENT_STATUS   stMeterStatusPhaseB->bBOverCurrent
#define FLG_B_OVER_KW_STATUS        stMeterStatusPhaseB->bBOverKw
#define FLG_B_REVERSEKW_STATUS      stMeterStatusPhaseB->bBReverseKw
#define FLG_B_CUT_VOLTAGE_STATUS    stMeterStatusPhaseB->bBCutVoltage
#define FLG_B_CUT_CURRENT_STATUS    stMeterStatusPhaseB->bBCutCurrent

// CHAR 6 PHASE C
#define FLG_C_LOSS_VOLTAGE_STATUS   stMeterStatusPhaseC->bLossVoltage
#define FLG_C_DOWN_VOLTAGE_STATUS   stMeterStatusPhaseC->bDownVoltage
#define FLG_C_OVER_VOLTAGE_STATUS   stMeterStatusPhaseC->bOverVoltage
#define FLG_C_LOSS_CURRENT_STATUS   stMeterStatusPhaseC->bLossCurrent
#define FLG_C_OVER_CURRENT_STATUS   stMeterStatusPhaseC->bOverCurrent
#define FLG_C_OVER_KW_STATUS            stMeterStatusPhaseC->bOverKw
#define FLG_C_REVERSEKW_STATUS      stMeterStatusPhaseC->bReverseKw
#define FLG_C_CUT_VOLTAGE_STATUS        stMeterStatusPhaseC->bCutVoltage
#define FLG_C_CUT_CURRENT_STATUS        stMeterStatusPhaseC->bCutCurrent


// CHAR 7 ALL ERR
#define FLG_ORDER_VOLTAGE_STATUS        stMeterStatusPhaseAll->bOrderVoltage
#define FLG_ORDER_CURRENT_STATUS        stMeterStatusPhaseAll->bOrderCurrent
#define FLG_UNBALANCE_VOLTAGE_STATUS    stMeterStatusPhaseAll->bUnbalanceVoltage
#define FLG_UNBALANCE_CURRENT_STATUS    stMeterStatusPhaseAll->bUnbalanceCurrent
#define FLG_ACPOWER_STATUS          stMeterStatusPhaseAll->bLossACPower
#define FLG_SYSTEMPOWER_STATUS      stMeterStatusPhaseAll->bLossPower
#define FLG_DEMANDOVER_STATUS       stMeterStatusPhaseAll->bDemandOver

#define FLG_OVERTOTALCOS_STATUS     stMeterStatusPhaseAll->bOverTotalCos
#define FLG_UNBALANCE_SEVERITY_CURRENT_STATUS   stMeterStatusPhaseAll->bUnbalanceSeverityCurrent


// OTHER ERR
#define FLG_ALL_OVER_KW_STATUS      stMeterStatusOther01->Bit2s.b00
#define FLG_ALL_REVERSEKW_STATUS        stMeterStatusOther01->Bit2s.b01
#define FLG_ALL_LOSSVOLTAGE_STATUS  stMeterStatusOther01->Bit2s.b02
#define FLG_LOSSACPOWER_STATUS      stMeterStatusOther01->Bit2s.b03

#define FLG_COVER_OPEN_STATUS           stMeterStatusOther01->Bit2s.b04
#define FLG_TERMINAL_OPEN_STATUS        stMeterStatusOther01->Bit2s.b05
#define FLG_PROGRAM_OPEN_STATUS     stMeterStatusOther01->Bit2s.b06
#define FLG_COMM_IR_DATASET_STATUS  stMeterStatusOther01->Bit2s.b07

#define FLG_A_CURRENT_NOHAVE_STATUS stMeterStatusOther02->Bit2s.b10
#define FLG_B_CURRENT_NOHAVE_STATUS stMeterStatusOther02->Bit2s.b11
#define FLG_C_CURRENT_NOHAVE_STATUS stMeterStatusOther02->Bit2s.b12

// DEMAND OVER
#define FLG_DEMAND_OVER_ALL_STATUS      RAM[RAM_CURRENT_METER_STATUS_DEMANDOVER]
#define FLG_DEMAND_OVER_KW_F_STATUS     stMeterStatusDemandOver->Bit2s.b20
#define FLG_DEMAND_OVER_KW_R_STATUS     stMeterStatusDemandOver->Bit2s.b21
#define FLG_DEMAND_OVER_KVAR_Q1_STATUS  stMeterStatusDemandOver->Bit2s.b22
#define FLG_DEMAND_OVER_KVAR_Q2_STATUS  stMeterStatusDemandOver->Bit2s.b23
#define FLG_DEMAND_OVER_KVAR_Q3_STATUS  stMeterStatusDemandOver->Bit2s.b24
#define FLG_DEMAND_OVER_KVAR_Q4_STATUS  stMeterStatusDemandOver->Bit2s.b25
#define FLG_DEMAND_OVER_KVAR_C1_STATUS  stMeterStatusDemandOver->Bit2s.b26
#define FLG_DEMAND_OVER_KVAR_C2_STATUS  stMeterStatusDemandOver->Bit2s.b27



#define FLG_MONITOR_V_A_STATUS      stMonitorVoltageStatus.Bits.bVAStatus
#define FLG_MONITOR_V_B_STATUS      stMonitorVoltageStatus.Bits.bVBStatus
#define FLG_MONITOR_V_C_STATUS      stMonitorVoltageStatus.Bits.bVCStatus
#define FLG_MONITOR_V_ALL_STATUS    stMonitorVoltageStatus.Bits.bVAllStatus
#define FLG_MONITOR_V_STATUS        stMonitorVoltageStatus.Ch












//#define FLG_RELAY_STATUS_ALL    RAM[RAM_CURRENT_RELAY_STATUS]
//#define FLG_RELAY_STATUS_OPENCLOSE  stRelayStatus->b1







// AA  编程时间  AA
AP_DATA_EXT u16 ucProgramTime;
// AA  通讯符号显示控制  AA
#define CON_COMMFLGSTATUS_SHOWTIME 0x03;
AP_DATA_EXT uchar ucCommFlgStatusChannel01;
AP_DATA_EXT uchar ucCommFlgStatusChannel02;
AP_DATA_EXT uchar ucCommFlgStatusChannel03;
AP_DATA_EXT uchar ucCommFlgStatusChannel04;
AP_DATA_EXT uchar ucCommFlgStatusChannel05;





//  AA   当前处于时区表1还是时区表2     AA
#define STATUS_SEASONTABLEPOINT RAM[RAM_CURRENT_SEASONTABLEPOINT]
//  AA   当前处于套时段表1还是套时段表2     AA
#define STATUS_DAYTABLEPOINT    RAM[RAM_CURRENT_DAYTABLEPOINT]
//  AA   当前处于时区表中的第几项     AA
#define STATUS_SEASONNUM    RAM[RAM_CURRENT_SEASONNUM]
//  AA   当前处于第几个日时段表     AA
#define STATUS_DAYTABLE RAM[RAM_CURRENT_DAYTABLE]
//  AA   当前处于什么费率     AA
#define STATUS_PRICE        RAM[RAM_CURRENT_PRICE]

// AA  当前运行阶梯套  AA
#define STATUS_STEPPRICE_POINT  RAM[RAM_CURRENT_STEPPRICE_POINT]
// AA  当前运行阶梯  AA
#define STATUS_STEPPRICE_NUM        RAM[RAM_CURRENT_STEPPRICE_STATUS]

// AA  当前运行费率电价套  AA
#define STATUS_PERIODPRICE_POINT    RAM[RAM_CURRENT_PERIODPRICE_POINT]
// AA  当前运行费率电价梯  AA
#define STATUS_PERIODPRICE_NUM  RAM[RAM_CURRENT_PERIODPRICE_STATUS]





#define RSOFT_RTC_SECOND  RAM[RAM_SOFT_SECOND]
#define RSOFT_RTC_MINUTE   RAM[RAM_SOFT_MINUTE]
#define RSOFT_RTC_HOUR      RAM[RAM_SOFT_HOUR]
#define RSOFT_RTC_WEEK      RAM[RAM_SOFT_WEEK]  
#define RSOFT_RTC_DAY        RAM[RAM_SOFT_DAY]
#define RSOFT_RTC_MONTH   RAM[RAM_SOFT_MONTH]
#define RSOFT_RTC_YEAR      RAM[RAM_SOFT_YEAR]

#define QUADRANT_NOHAVE 0
#define QUADRANT_ONE        1
#define QUADRANT_TWO        2
#define QUADRANT_THREE  3
#define QUADRANT_FOUR       4

#define QUADRANT_Z  RAM[RAM_CURRENT_QUADRANT_Z]
#define QUADRANT_A  RAM[RAM_CURRENT_QUADRANT_A]
#define QUADRANT_B  RAM[RAM_CURRENT_QUADRANT_B]
#define QUADRANT_C RAM[RAM_CURRENT_QUADRANT_C]

AP_DATA_EXT uchar second_rtc_point_timera0;    //zhong duan miao ji shu qi用于中断中秒加  ping shi
AP_DATA_EXT uchar second_rtc_point_timerb1;    //zhong duan miao ji shu qi用于中断中秒加  tingdian
// aaa硬件对时AAAAAA
AP_DATA_EXT uchar qingqiuduishi_rtc;

AP_DATA_EXT u16 remote_jiehuo_10day;//(minute) 10*24*60
AP_DATA_EXT uchar tingchao_enabled;
AP_DATA_EXT u16 quanshiya_10day; // minute



AP_DATA_EXT u16 remote_display_7day;//m 7*24*60






AP_DATA_EXT uchar FlgFreezeSeasonChange;
AP_DATA_EXT uchar FlgFreezeDayTableChange;
AP_DATA_EXT uchar FlgFreezeStepPriceTableChange;
AP_DATA_EXT uchar FlgFreezePeriodPriceTableChange;

AP_DATA_EXT uchar FlgFreezeInstant;
AP_DATA_EXT uchar FlgFreezeEveryTime;
AP_DATA_EXT uchar FlgFreezeEveryDayZeroTime;
AP_DATA_EXT uchar FlgFreezeEveryHalfHour;

AP_DATA_EXT uchar FlgFreezeFactoryEveryHour;
AP_DATA_EXT uchar FlgFreezeFactoryEveryDay;


#endif




