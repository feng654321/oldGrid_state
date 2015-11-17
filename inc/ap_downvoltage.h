
#ifndef __AP_DOWNVOLTAGE_H__
#define __AP_DOWNVOLTAGE_H__
    
#undef COMMON_EXT
#ifdef __AP_DOWNVOLTAGE_C__
#define COMMON_EXT
#else
#define COMMON_EXT  extern
#endif


COMMON_EXT void DownVoltageParaInit(void);
COMMON_EXT void DownVoltageSecTimeAdd(void);
COMMON_EXT void DownVoltageMinTimeAdd(void);

COMMON_EXT void DownVoltageInit(void);

COMMON_EXT void DownVoltageStart(uchar ucType);

COMMON_EXT void DownVoltageStopIfStart(void);

COMMON_EXT void DownVoltageEnd(uchar ucType);

COMMON_EXT void DownVoltageTimeAdd(void);

COMMON_EXT uchar DownVoltageMode_34(void);

COMMON_EXT uchar DownVoltageMode(void);


#endif

