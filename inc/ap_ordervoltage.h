
#ifndef AP_ORDERVOLTAGE_H
    #define AP_ORDERVOLTAGE_H
#ifdef  AP_ORDERVOLTAGE_GLOBALS
    #define AP_ORDERVOLTAGE_EXT
#else
    #define AP_ORDERVOLTAGE_EXT extern
#endif  

AP_ORDERVOLTAGE_EXT void OrderVoltageSecTimeAdd(void);
AP_ORDERVOLTAGE_EXT void OrderVoltageMinTimeAdd(void);


AP_ORDERVOLTAGE_EXT void OrderVoltageInit(void);

AP_ORDERVOLTAGE_EXT void OrderVoltageStart(void);

AP_ORDERVOLTAGE_EXT void OrderVoltageStopIfStart(void);

AP_ORDERVOLTAGE_EXT void OrderVoltageEnd(void);

AP_ORDERVOLTAGE_EXT uchar OrderVoltageMode_34(void);

AP_ORDERVOLTAGE_EXT uchar OrderVoltageMode(void);














#endif  



