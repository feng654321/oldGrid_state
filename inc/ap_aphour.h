
#ifndef AP_APHOUR_H
    #define AP_APHOUR_H
#ifdef  AP_APHOUR_GLOBALS
    #define AP_APHOUR_EXT
#else
    #define AP_APHOUR_EXT extern
#endif  



AP_APHOUR_EXT void APHourInit(void);

AP_APHOUR_EXT void APHourClr(void);

AP_APHOUR_EXT void APHourClac(uchar ucClalType);

AP_APHOUR_EXT void APHourMode(void);



































#endif


