
#ifndef AP_COMMWRITEBACKFUNCTION_H
    #define AP_COMMWRITEBACKFUNCTION_H
#ifdef  AP_COMMWRITEBACKFUNCTION_GLOBALS
    #define AP_COMMWRITEBACKFUNCTION_EXT
#else
    #define AP_COMMWRITEBACKFUNCTION_EXT extern
#endif  



AP_COMMWRITEBACKFUNCTION_EXT ulong utlCommUserCode;

AP_COMMWRITEBACKFUNCTION_EXT uchar AddDataInit(void);

//AP_COMMWRITEBACKFUNCTION_EXT uchar DefaultParaInit(void);
AP_COMMWRITEBACKFUNCTION_EXT uchar AddDataInit(void);
AP_COMMWRITEBACKFUNCTION_EXT uchar AddDataOperate(void);

AP_COMMWRITEBACKFUNCTION_EXT uchar CWBFTimeChange(void);

AP_COMMWRITEBACKFUNCTION_EXT uchar CWBFDemandCycleChange(void);

AP_COMMWRITEBACKFUNCTION_EXT uchar CWBFPriceChange(void);

AP_COMMWRITEBACKFUNCTION_EXT uchar CWBFDisplayChange(void);

AP_COMMWRITEBACKFUNCTION_EXT uchar CWBFPowerCharacterChange(void);

AP_COMMWRITEBACKFUNCTION_EXT uchar CWBFChargeRecordChange(void);

AP_COMMWRITEBACKFUNCTION_EXT uchar CWBFBalanceDayChange(void);

AP_COMMWRITEBACKFUNCTION_EXT uchar CWBFFreezeInstantRecord(ulong uId);

AP_COMMWRITEBACKFUNCTION_EXT uchar CWBFMaxDemandClr(void);

AP_COMMWRITEBACKFUNCTION_EXT uchar CWBFMeterAllClr(void);

AP_COMMWRITEBACKFUNCTION_EXT uchar CWBFMeterAllClr_InFactory(void);

AP_COMMWRITEBACKFUNCTION_EXT uchar CWBFEventDataClr( ulong ulCode);

AP_COMMWRITEBACKFUNCTION_EXT uchar CWBFRelayCommand(uchar *ucPoint);

AP_COMMWRITEBACKFUNCTION_EXT void CWBFCommIrSetData(void);

AP_COMMWRITEBACKFUNCTION_EXT uchar CWBFCommAddrChange(void);


AP_COMMWRITEBACKFUNCTION_EXT void MeterParaChangeBringEvent(void);


AP_COMMWRITEBACKFUNCTION_EXT void ProgramEventInit(void);



AP_COMMWRITEBACKFUNCTION_EXT uchar ProgramEventDemandClr(void);




AP_COMMWRITEBACKFUNCTION_EXT uchar ProgramEventPowerClr(void);


AP_COMMWRITEBACKFUNCTION_EXT uchar ProgramEventMeterClrAll(ulong  ultEventCode);


AP_COMMWRITEBACKFUNCTION_EXT uchar ProgramEventDayTableChange(void);

AP_COMMWRITEBACKFUNCTION_EXT void ProgramEventMode(void);

AP_COMMWRITEBACKFUNCTION_EXT void CLR_Down_EventMode(void);

AP_COMMWRITEBACKFUNCTION_EXT void shm_clean_pro(void);

AP_COMMWRITEBACKFUNCTION_EXT struct date_time_rec get_current_time(void);

AP_COMMWRITEBACKFUNCTION_EXT int db_sd_drt_write_data_shm(struct data_rt *sd);

AP_COMMWRITEBACKFUNCTION_EXT void MeterAllDataClr_pro(void);

AP_COMMWRITEBACKFUNCTION_EXT uchar ProgramEventTimeChange(uchar * ucScr);

AP_COMMWRITEBACKFUNCTION_EXT uchar ProgramEventDayTableChange(void);

AP_COMMWRITEBACKFUNCTION_EXT uchar ProgramEventSeasonTableChange(void);

AP_COMMWRITEBACKFUNCTION_EXT uchar ProgramEventResetDayChange(void);

AP_COMMWRITEBACKFUNCTION_EXT uchar ProgramEventHolidayChange(void);

AP_COMMWRITEBACKFUNCTION_EXT uchar ProgramEventCharacterActiveChange(void);

AP_COMMWRITEBACKFUNCTION_EXT uchar ProgramEventCharacterActive01Change(void);

AP_COMMWRITEBACKFUNCTION_EXT uchar ProgramEventCharacterActive02Change(void);

AP_COMMWRITEBACKFUNCTION_EXT uchar ProgramEventBalanceDayChange(void);

AP_COMMWRITEBACKFUNCTION_EXT uchar ProgramBroadCastTimeChange(uchar *ucOldTime,u16 uiTime);

#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
AP_COMMWRITEBACKFUNCTION_EXT void PurchaseEnergyRecord(void);
AP_COMMWRITEBACKFUNCTION_EXT uchar PURCHASE_ENERGY_RECORD_FLAG;

AP_COMMWRITEBACKFUNCTION_EXT uchar CWBFCardDataIsSet(void);

#endif


















#endif



