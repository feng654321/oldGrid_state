
#ifndef AP_OVERCURRENT_H
    #define AP_OVERCURRENT_H
#ifdef  AP_OVERCURRENT_GLOBALS
    #define AP_OVERCURRENT_EXT
#else
    #define AP_OVERCURRENT_EXT extern
#endif  


AP_OVERCURRENT_EXT void OverCurrentParaInit(void);
AP_OVERCURRENT_EXT void OverCurrentSecTimeAdd(void);
AP_OVERCURRENT_EXT void OverCurrentMinTimeAdd(void);


AP_OVERCURRENT_EXT void OverCurrentInit(void);

AP_OVERCURRENT_EXT void OverCurrentStart(uchar ucType);

AP_OVERCURRENT_EXT void OverCurrentStopIfStart(void);

AP_OVERCURRENT_EXT void OverCurrentEnd(uchar ucType);

AP_OVERCURRENT_EXT void OverCurrentTimeAdd(void);

AP_OVERCURRENT_EXT uchar OverCurrentMode_34(void);

AP_OVERCURRENT_EXT uchar OverCurrentMode(void);


























#endif  



