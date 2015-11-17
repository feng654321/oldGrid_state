
#ifndef AP_OVERPOWER_H
    #define AP_OVERPOWER_H
#ifdef  AP_OVERPOWER_GLOBALS
    #define AP_OVERPOWER_EXT
#else
    #define AP_OVERPOWER_EXT extern
#endif  

AP_OVERPOWER_EXT void OverPowerParaInit(void);
AP_OVERPOWER_EXT void OverPowerSecTimeAdd(void);
AP_OVERPOWER_EXT void OverPowerMinTimeAdd(void);

AP_OVERPOWER_EXT void OverPowerInit(void);

AP_OVERPOWER_EXT void OverPowerStart(uchar ucType);

AP_OVERPOWER_EXT void OverPowerStopIfStart(void);

AP_OVERPOWER_EXT void OverPowerEnd(uchar ucType);

AP_OVERPOWER_EXT void OverPowerTimeAdd(void);

AP_OVERPOWER_EXT uchar OverPowerMode_34(void);

AP_OVERPOWER_EXT uchar OverPowerMode(void);


























#endif  



