
#ifndef AP_AUXPOWER_H
    #define AP_AUXPOWER_H
#ifdef  AP_AUXPOWER_GLOBALS
    #define AP_AUXPOWER_EXT
#else
    #define AP_AUXPOWER_EXT extern
#endif  

#define CON_AUXPOWER_CONTINUETIME 2

AP_AUXPOWER_EXT void AuxPowerSecTimeAdd(void);
AP_AUXPOWER_EXT void AuxPowerMinTimeAdd(void);



AP_AUXPOWER_EXT void AuxPowerInit(void);
AP_AUXPOWER_EXT void AuxPowerPowerOnInit(void);

AP_AUXPOWER_EXT void AuxPowerStopIfStart(void);

AP_AUXPOWER_EXT void AuxPowerMode(void);

AP_AUXPOWER_EXT void AuxPowerPowerOn(uchar *ucStartTime,ulong ulTime);








































#endif

