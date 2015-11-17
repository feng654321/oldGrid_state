
#ifndef AP_ORDERCURRENT_H
    #define AP_ORDERCURRENT_H
#ifdef  AP_ORDERCURRENT_GLOBALS
    #define AP_ORDERCURRENT_EXT
#else
    #define AP_ORDERCURRENT_EXT extern
#endif  




AP_ORDERCURRENT_EXT void OrderCurrentSecTimeAdd(void);
AP_ORDERCURRENT_EXT void OrderCurrentMinTimeAdd(void);


AP_ORDERCURRENT_EXT void OrderCurrentInit(void);

AP_ORDERCURRENT_EXT void OrderCurrentStopIfStart(void);

AP_ORDERCURRENT_EXT uchar OrderCurrentMode(void);

























#endif  



