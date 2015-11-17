
#ifndef AP_LOSSCURRENT_H
    #define AP_LOSSCURRENT_H
#ifdef  AP_LOSSCURRENT_GLOBALS
    #define AP_LOSSCURRENT_EXT
#else
    #define AP_LOSSCURRENT_EXT extern
#endif  





AP_LOSSCURRENT_EXT void LossCurrentParaInit(void);

AP_LOSSCURRENT_EXT void LossCurrentInit(void);

AP_LOSSCURRENT_EXT void LossCurrentStart(uchar ucType);

AP_LOSSCURRENT_EXT void LossCurrentEnd(uchar ucType);

AP_LOSSCURRENT_EXT void LossCurrentStopIfStart(void);

AP_LOSSCURRENT_EXT void LossCurrentSecTimeAdd(void);

AP_LOSSCURRENT_EXT void LossCurrentMinTimeAdd(void);

AP_LOSSCURRENT_EXT uchar LossCurrentMode_34(void);

AP_LOSSCURRENT_EXT uchar LossCurrentMode(void);




























#endif  



