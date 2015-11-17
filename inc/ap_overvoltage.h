
#ifndef AP_OVERVOLTAGE_H
    #define AP_OVERVOLTAGE_H
#ifdef  AP_OVERVOLTAGE_GLOBALS
    #define AP_OVERVOLTAGE_EXT
#else
    #define AP_OVERVOLTAGE_EXT extern
#endif  










AP_OVERVOLTAGE_EXT void OverVoltageParaInit(void);
AP_OVERVOLTAGE_EXT void OverVoltageSecTimeAdd(void);
AP_OVERVOLTAGE_EXT void OverVoltageMinTimeAdd(void);

AP_OVERVOLTAGE_EXT void OverVoltageInit(void);

AP_OVERVOLTAGE_EXT void OverVoltageStart(uchar ucType);

AP_OVERVOLTAGE_EXT void OverVoltageStopIfStart(void);

AP_OVERVOLTAGE_EXT void OverVoltageEnd(uchar ucType);

AP_OVERVOLTAGE_EXT void OverVoltageTimeAdd(void);

AP_OVERVOLTAGE_EXT uchar OverVoltageMode_34(void);

AP_OVERVOLTAGE_EXT uchar OverVoltageMode(void);









































#endif  



