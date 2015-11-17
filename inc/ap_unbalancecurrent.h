
#ifndef AP_UNBALANCECURRENT_H
    #define AP_UNBALANCECURRENT_H
#ifdef  AP_UNBALANCECURRENT_GLOBALS
    #define AP_UNBALANCECURRENT_EXT
#else
    #define AP_UNBALANCECURRENT_EXT extern
#endif  





AP_UNBALANCECURRENT_EXT void UnbalanceCurrentParaInit(void);
AP_UNBALANCECURRENT_EXT void UnbalanceCurrentSecTimeAdd(void);
AP_UNBALANCECURRENT_EXT void UnbalanceCurrentMinTimeAdd(void);


AP_UNBALANCECURRENT_EXT void UnbalanceCurrentInit(void);

AP_UNBALANCECURRENT_EXT void UnbalanceCurrentStart(void);

AP_UNBALANCECURRENT_EXT void UnbalanceCurrentStopIfStart(void);

AP_UNBALANCECURRENT_EXT void UnbalanceCurrentEnd(void);

AP_UNBALANCECURRENT_EXT uchar UnbalanceCurrentMode_34(void);

AP_UNBALANCECURRENT_EXT uchar UnbalanceCurrentMode(void);


























#endif  



