#ifndef __AP_ANGLE_H__
#define __AP_ANGLE_H__

#ifdef  AP_ANGLE_GLOBALS
    #define AP_ANGLE_EXT
#else
    #define AP_ANGLE_EXT extern
#endif  


AP_ANGLE_EXT void AngleInit(void);

AP_ANGLE_EXT uchar AngleMode(void);

#endif

