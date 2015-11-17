#ifndef DISPLAY_EXT_INPUT_H
    #define DISPLAY_EXT_INPUT_H

#ifdef  DISPLAY_EXT_INPUT_GLOBALS
    #define DISPLAY_EXT_INPUT_EXT
#else
    #define DISPLAY_EXT_INPUT_EXT extern
#endif  



DISPLAY_EXT_INPUT_EXT uchar BatterAlarm(void);
DISPLAY_EXT_INPUT_EXT uchar VoltageAlarm(void);
DISPLAY_EXT_INPUT_EXT uchar CurrentAlarm(void);
DISPLAY_EXT_INPUT_EXT uchar ucTempDisplayReadCardStatus;

#endif

