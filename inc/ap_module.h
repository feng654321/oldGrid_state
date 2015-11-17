#ifndef AP_MODULE_H
    #define AP_MODULE_H
#ifdef  AP_MODULE_GLOBALS
    #define AP_MODULE_EXT
#else
    #define AP_MODULE_EXT extern
#endif  

#define CON_MODULE_POWER_OFF_DELAY 30



AP_MODULE_EXT void ModuleMode(void);

AP_MODULE_EXT void ModulePlcStatusReset(void);

AP_MODULE_EXT void ModuleInit(void);
AP_MODULE_EXT void ModuleEventAlarm(uchar ucType);

#if(CONFIG_METER_NO2COMM_MODE_WIRELESS==CONFIG_METER_NO2COMM_MODE)
AP_MODULE_EXT void ModuleWirelessFlagInit(void);
AP_MODULE_EXT void ModuleWirelessEventReset(void);
AP_MODULE_EXT void ModuleWirelessEventSet(uchar ucType);

AP_MODULE_EXT uchar WirelessStatusDelay;

#endif






























#endif

