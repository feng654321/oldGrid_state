
#ifndef AP_ALLLOSSVOLTAGE_H
    #define AP_ALLLOSSVOLTAGE_H
#ifdef  AP_ALLLOSSVOLTAGE_GLOBALS
    #define AP_ALLLOSSVOLTAGE_EXT
#else
    #define AP_ALLLOSSVOLTAGE_EXT extern
#endif  

AP_ALLLOSSVOLTAGE_EXT void AllLossVoltageSecTimeAdd(void);
AP_ALLLOSSVOLTAGE_EXT void AllLossVoltageMinTimeAdd(void);


AP_ALLLOSSVOLTAGE_EXT void AllLossVoltageInit(void);
AP_ALLLOSSVOLTAGE_EXT void AllLossVoltagePowerOnInit(void);

AP_ALLLOSSVOLTAGE_EXT void AllLossVoltageStart(ulong ulMaxCurrent);

AP_ALLLOSSVOLTAGE_EXT void AllLossVoltageEnd(void);

AP_ALLLOSSVOLTAGE_EXT void AllLossVoltageTimeAdd(void);

AP_ALLLOSSVOLTAGE_EXT void AllLossVoltageMode_33(void);

AP_ALLLOSSVOLTAGE_EXT void AllLossVoltageMode_34(void);

AP_ALLLOSSVOLTAGE_EXT uchar AllLossVoltageMode(void);



AP_ALLLOSSVOLTAGE_EXT void AllLossVoltageStopIfStart(void);


#define POWERDOWN_ALLLOSSVOLTAGE_STATUS_YES 0x55
#define POWERDOWN_ALLLOSSVOLTAGE_STATUS_NO  0x33


AP_ALLLOSSVOLTAGE_EXT uchar ucPowerDownAllLossVoltageStatus;
AP_ALLLOSSVOLTAGE_EXT uchar ucPowerDownAllLossVoltageWakeupTimes;


AP_ALLLOSSVOLTAGE_EXT void PowerDownAllLossVoltageStart(ulong ulMaxCurrent);

AP_ALLLOSSVOLTAGE_EXT void PowerDownAllLossVoltageStopIfStart(void);

AP_ALLLOSSVOLTAGE_EXT void PowerDownAllLossVoltageEnd(void);

AP_ALLLOSSVOLTAGE_EXT void PowerDownAllLossVoltageMode(void);







AP_ALLLOSSVOLTAGE_EXT uchar  GetLastSaveTimeToAddr(uchar * upData);

AP_ALLLOSSVOLTAGE_EXT uchar AllLossVoltageStatuscheck(void);

//AP_ALLLOSSVOLTAGE_EXT uchar AllLossVoltagePowerOnCheck(void);
/*

AP_ALLLOSSVOLTAGE_EXT ulong  AllLossVoltagePowerDownCheck(void);


AP_ALLLOSSVOLTAGE_EXT void PowerOnRecordStart(void);

AP_ALLLOSSVOLTAGE_EXT void PowerOnRecordEnd(void);


AP_ALLLOSSVOLTAGE_EXT void PowerOnRecord(uchar *ucPoint);
*/


AP_ALLLOSSVOLTAGE_EXT void AllLossVoltagePoweronChange(ulong ulTime);












































#endif

