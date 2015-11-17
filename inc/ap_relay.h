#ifndef AP_RELAY_H
    #define AP_RELAY_H
#ifdef  AP_RELAY_GLOBALS
    #define AP_RELAY_EXT
#else
    #define AP_RELAY_EXT extern
#endif  

AP_RELAY_EXT void RelayInit(void);

AP_RELAY_EXT void RelayOpenEventRecord(ulong uttttlCommUserCode);

AP_RELAY_EXT void RelayCloseEventRecord(ulong uttttlCommUserCode);

AP_RELAY_EXT u16 uiRelayStatusChangeDelayTime;

#if(CONFIG_METER_RELAY_MODE_INSIDE == CONFIG_METER_RELAY_MODE)
AP_RELAY_EXT void RelayStatusHolding(void);
#endif
#if(CONFIG_METER_RELAY_MODE_OUTSIDE== CONFIG_METER_RELAY_MODE)
#define CON_RELAY_STATUS_MAX_TIME_10MS  2000
#define CON_RELAY_STATUS_CHANGE_START_TIME_10MS 300
#define CON_RELAY_STATUS_CHANGE_END_TIME_10MS 600
AP_RELAY_EXT uchar ucRelayOutsideOpen;
AP_RELAY_EXT void RelayStatusCheckOnKwhAdd(void);
#endif
AP_RELAY_EXT void RelayStatusOpen(void);

AP_RELAY_EXT void RelayStatusClose(void);

AP_RELAY_EXT void RelayMode(void);
AP_RELAY_EXT void SetRelayAlarmPluseStatus(uchar ucStatus);


































#endif

