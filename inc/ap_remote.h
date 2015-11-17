
#ifndef AP_REMOTE_H
    #define AP_REMOTE_H
#ifdef  AP_REMOTE_GLOBALS
    #define AP_REMOTE_EXT
#else
    #define AP_REMOTE_EXT extern
#endif  



AP_REMOTE_EXT void RemoteInit(void);


AP_REMOTE_EXT uchar  RemoteGetPoint(void);


AP_REMOTE_EXT void RemoteMode(void);



AP_REMOTE_EXT ulong ulRemoteKeyShow;

#if(CONFIG_METER_AREA_MODE_JIANGXI==CONFIG_METER_AREA_MODE)     
void RemoteHaveAFlg(void);
#endif




#endif  



