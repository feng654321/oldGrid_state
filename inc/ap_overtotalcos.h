
#ifndef AP_OVERTOTALCOS_H
    #define AP_OVERTOTALCOS_H
#ifdef  AP_OVERTOTALCOS_GLOBALS
    #define AP_OVERTOTALCOS_EXT
#else
    #define AP_OVERTOTALCOS_EXT extern
#endif  


AP_OVERTOTALCOS_EXT void OverTotalCosParaInit(void);
AP_OVERTOTALCOS_EXT void OverTotalCosSecTimeAdd(void);
AP_OVERTOTALCOS_EXT void OverTotalCosMinTimeAdd(void);


AP_OVERTOTALCOS_EXT void OverTotalCosInit(void);

AP_OVERTOTALCOS_EXT void OverTotalCosStart(void);

AP_OVERTOTALCOS_EXT void OverTotalCosStopIfStart(void);

AP_OVERTOTALCOS_EXT void OverTotalCosEnd(void);

AP_OVERTOTALCOS_EXT void OverTotalCosTimeAdd(void);

AP_OVERTOTALCOS_EXT uchar OverTotalCosMode_34(void);

AP_OVERTOTALCOS_EXT uchar OverTotalCosMode(void);









































#endif  



