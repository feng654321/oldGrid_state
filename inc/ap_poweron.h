

#ifndef AP_POWERON_H
    #define AP_POWERON_H
#ifdef  AP_POWERON_GLOBALS
    #define AP_POWERON_EXT
#else
    #define AP_POWERON_EXT extern
#endif  


AP_POWERON_EXT volatile uchar g_OpenFlashPower; 



AP_POWERON_EXT void CloseFlashPowerMode(void);

AP_POWERON_EXT void PowerOnDataResume(void);

AP_POWERON_EXT void PowerOnDataInit(void);

AP_POWERON_EXT void PowerWakeupDataInit(void);




AP_POWERON_EXT void PowerDownRecordStart(void);

AP_POWERON_EXT void PowerDownRecordEnd(void);



AP_POWERON_EXT void PowerDownWhenPowerOnRecord(uchar *ucPoint);

AP_POWERON_EXT uchar PowerdDownMode(void);

AP_POWERON_EXT uchar EventRecordPowerOn(void);

AP_POWERON_EXT void EraseFlashPowerOn(void);














#endif  



