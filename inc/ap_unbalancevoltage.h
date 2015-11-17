
#ifndef AP_UNBALANCEVOLTAGE_H
    #define AP_UNBALANCEVOLTAGE_H
#ifdef  AP_UNBALANCEVOLTAGE_GLOBALS
    #define AP_UNBALANCEVOLTAGE_EXT
#else
    #define AP_UNBALANCEVOLTAGE_EXT extern
#endif  








AP_UNBALANCEVOLTAGE_EXT void UnbalanceVoltageParaInit(void);
AP_UNBALANCEVOLTAGE_EXT void UnbalanceVoltageSecTimeAdd(void);
AP_UNBALANCEVOLTAGE_EXT void UnbalanceVoltageMinTimeAdd(void);

AP_UNBALANCEVOLTAGE_EXT void UnbalanceVoltageInit(void);

AP_UNBALANCEVOLTAGE_EXT void UnbalanceVoltageStart(void);

AP_UNBALANCEVOLTAGE_EXT void UnbalanceVoltageStopIfStart(void);

AP_UNBALANCEVOLTAGE_EXT void UnbalanceVoltageEnd(void);

AP_UNBALANCEVOLTAGE_EXT uchar UnbalanceVoltageMode_34(void);

AP_UNBALANCEVOLTAGE_EXT uchar UnbalanceVoltageMode(void);




























#endif  



