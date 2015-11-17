
#ifndef AP_REVERSEPOWER_H
    #define AP_REVERSEPOWER_H
#ifdef  AP_REVERSEPOWER_GLOBALS
    #define AP_REVERSEPOWER_EXT
#else
    #define AP_REVERSEPOWER_EXT extern
#endif  



AP_REVERSEPOWER_EXT void ReversePowerParaInit(void);
AP_REVERSEPOWER_EXT void ReversePowerSecTimeAdd(void);
AP_REVERSEPOWER_EXT void ReversePowerMinTimeAdd(void);


AP_REVERSEPOWER_EXT void ReversePowerInit(void);

AP_REVERSEPOWER_EXT void ReversePowerStart(uchar ucType);

AP_REVERSEPOWER_EXT void ReversePowerStopIfStart(void);

AP_REVERSEPOWER_EXT void ReversePowerEnd(uchar ucType);

AP_REVERSEPOWER_EXT void ReversePowerTimeAdd(void);

AP_REVERSEPOWER_EXT uchar ReversePowerMode_34(void);

AP_REVERSEPOWER_EXT uchar ReversePowerMode(void);


























































#endif  



