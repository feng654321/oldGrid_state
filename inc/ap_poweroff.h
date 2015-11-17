
#ifndef AP_POWEROFF_H
    #define AP_POWEROFF_H
#ifdef  AP_POWEROFF_GLOBALS
    #define AP_POWEROFF_EXT
#else
    #define AP_POWEROFF_EXT extern
#endif  

AP_POWEROFF_EXT u16 PowerOffWaitTimeStep10mS;
AP_POWEROFF_EXT void PowerOffDataSaveInit(void);

AP_POWEROFF_EXT uchar PowerOffDataSave(void);


AP_POWEROFF_EXT void PowerOffDataMustSave(void);

AP_POWEROFF_EXT void PowerOffStart(void);
AP_POWEROFF_EXT void PowerOffSaveAllData(void);

#if(CONFIG_METER_STOPEVENT_POWERON == GAL_NO)    
AP_POWEROFF_EXT void PowerOffStopIfStart(void);
#endif

#endif  



