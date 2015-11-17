
#ifndef AP_COVEROPEN_H
    #define AP_COVEROPEN_H
#ifdef  AP_COVEROPEN_GLOBALS
    #define AP_COVEROPEN_EXT
#else
    #define AP_COVEROPEN_EXT extern
#endif  


#define COVEROPEN_TYPE          0
#define TERMINALOPEN_TYPE       1
#define PROGRAMOPEN_TYPE        2

#define CON_COVEROPEN_CONTINUETIME 3
#define CON_COVEROPEN_POWERDOWNCONTINUETIME 2





AP_COVEROPEN_EXT void CoverOpenInit(void);

AP_COVEROPEN_EXT void CoverOpenKwhtoPoint(uchar *uPoint,uchar ucPower);

AP_COVEROPEN_EXT void CoverOpenStart(uchar ucType,uchar ucPower);

AP_COVEROPEN_EXT void CoverOpenEnd(uchar ucType,uchar ucPower);

// AP_COVEROPEN_EXT void CoverOpenTimeAdd(void);

AP_COVEROPEN_EXT uchar CoverOpenMode(void);

//#if(CONFIG_METER_EVENT_COVEROPEN_SPECIAL_MODE_POWERDOWN_RECORD==CONFIG_METER_EVENT_COVEROPEN_SPECIAL_MODE)
//AP_COVEROPEN_EXT void CoverOpenPowerDownMode(void);
//#endif

//AP_COVEROPEN_EXT void CoverOpenStopIfStart(void);


AP_COVEROPEN_EXT uchar ucTempCoverOpenStatusUse,ucTempCoverOpenContinueTime;
AP_COVEROPEN_EXT uchar ucTempTerminalOpenStatusUse,ucTempTerminalOpenContinueTime;
AP_COVEROPEN_EXT uchar ucTempProgramOpenStatusUse,ucTempProgramOpenContinueTime;





















































#endif  



