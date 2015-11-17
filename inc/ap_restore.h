
#ifndef AP_RESTORE_H
    #define AP_RESTORE_H
#ifdef  AP_RESTORE_GLOBALS
    #define AP_RESTORE_EXT
#else
    #define AP_RESTORE_EXT extern
#endif  




AP_RESTORE_EXT uchar ucTimeLastSave[8];
// AP_RESTORE_EXT STR_CALENDAR usTimeLastSave;


AP_RESTORE_EXT void RestoreInit(void);

AP_RESTORE_EXT void RestoreMoniterClr(void);

AP_RESTORE_EXT void RestoreMoniter(uchar * ucPTime);

AP_RESTORE_EXT void RestorePower(uchar * ucPTime);

AP_RESTORE_EXT void RestorePowerUse(uchar * ucPTime);

//AP_RESTORE_EXT void RestoreDemandClr(void);

AP_RESTORE_EXT void RestoreDemand(uchar * ucPTime);
AP_RESTORE_EXT void RestoreDemand0xFF(uchar * ucPTime);

AP_RESTORE_EXT uchar RestoreMode(void);

AP_RESTORE_EXT void RestoreModePowerOn(void);
























#endif  



