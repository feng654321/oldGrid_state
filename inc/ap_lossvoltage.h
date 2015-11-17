
#ifndef AP_LOSSVOLTAGE_H
    #define AP_LOSSVOLTAGE_H
#ifdef  AP_LOSSVOLTAGE_GLOBALS
    #define AP_LOSSVOLTAGE_EXT
#else
    #define AP_LOSSVOLTAGE_EXT extern
#endif  










AP_LOSSVOLTAGE_EXT void LossVoltageParaInit(void);

AP_LOSSVOLTAGE_EXT void LossVoltageInit(void);

AP_LOSSVOLTAGE_EXT void LossVoltageStart(uchar ucType);

AP_LOSSVOLTAGE_EXT void LossVoltageStopIfStart(void);

AP_LOSSVOLTAGE_EXT void LossVoltageEnd(uchar ucType);

AP_LOSSVOLTAGE_EXT void LossVoltageSecTimeAdd(void);

AP_LOSSVOLTAGE_EXT void LossVoltageMinTimeAdd(void);

AP_LOSSVOLTAGE_EXT uchar LossVoltageMode_33(void);

AP_LOSSVOLTAGE_EXT uchar LossVoltageMode_34(void);

AP_LOSSVOLTAGE_EXT uchar LossVoltageMode(void);
























































#endif

