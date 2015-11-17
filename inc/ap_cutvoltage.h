
#ifndef AP_CUTVOLTAGE_H
    #define AP_CUTVOLTAGE_H
#ifdef  AP_CUTVOLTAGE_GLOBALS
    #define AP_CUTVOLTAGE_EXT
#else
    #define AP_CUTVOLTAGE_EXT extern
#endif  





AP_CUTVOLTAGE_EXT void CutVoltageInit(void);

AP_CUTVOLTAGE_EXT void CutVoltageStart(uchar ucType);

AP_CUTVOLTAGE_EXT void CutVoltageStopIfStart(void);

AP_CUTVOLTAGE_EXT void CutVoltageEnd(uchar ucType);

AP_CUTVOLTAGE_EXT void CutVoltageSecTimeAdd(void);

AP_CUTVOLTAGE_EXT void CutVoltageMinTimeAdd(void);

AP_CUTVOLTAGE_EXT uchar CutVoltageMode_33(void);

AP_CUTVOLTAGE_EXT uchar CutVoltageMode_34(void);

AP_CUTVOLTAGE_EXT uchar CutVoltageMode(void);

AP_CUTVOLTAGE_EXT void CutVoltageParaInit(void);



















#endif  



