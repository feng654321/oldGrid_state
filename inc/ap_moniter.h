
#ifndef AP_MONITER_H
    #define AP_MONITER_H
#ifdef  AP_MONITER_GLOBALS
    #define AP_MONITER_EXT
#else
    #define AP_MONITER_EXT extern
#endif  

AP_MONITER_EXT void MoniterParaInit(void);

AP_MONITER_EXT void MoniterInit(void);

AP_MONITER_EXT uchar CompareMaxVoltage(ulong ulAddr,u16 uiCurrentVoltage);

AP_MONITER_EXT uchar CompareMinVoltage(ulong ulAddr,u16 uiCurrentVoltage);

AP_MONITER_EXT void MoniterMode(void);

































#endif  



