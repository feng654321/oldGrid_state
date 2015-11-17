
#ifndef AP_KEYEVENT_H
    #define AP_KEYEVENT_H
#ifdef  AP_KEYEVENT_GLOBALS
    #define AP_KEYEVENT_EXT
#else
    #define AP_KEYEVENT_EXT extern
#endif  



AP_KEYEVENT_EXT void KeyEventInit(void);


AP_KEYEVENT_EXT void KeyEventMode(void);




AP_KEYEVENT_EXT UN_U8_PARAM ucKeyDisplayStatus;
#define DISPLAY_CHANGE_AB_STATUS ucKeyDisplayStatus.Bits.b0
#define DISPLAY_CHANGE_TO_B_STATUS ucKeyDisplayStatus.Bits.b1
#define DISPLAY_CHANGE_TO_A_STATUS ucKeyDisplayStatus.Bits.b2

#define DISPLAY_FLG_ASK ucKeyDisplayStatus.Bits.b3
#define DISPLAY_FLG_CLR ucKeyDisplayStatus.Bits.b4

#define DISPLAY_CHANGE_AtoB_STATUS ucKeyDisplayStatus.Bits.b5





























#endif  



