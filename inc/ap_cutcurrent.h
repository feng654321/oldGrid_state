
#ifndef __AP_CUTCURRENT_H__
#define __AP_CUTCURRENT_H__
    
#ifdef  __AP_CUTCURRENT_C__
    #define AP_CUTCURRENT_EXT
#else
    #define AP_CUTCURRENT_EXT extern
#endif  




AP_CUTCURRENT_EXT void CutCurrentInit(void);
AP_CUTCURRENT_EXT void CutCurrentParaInit(void);
AP_CUTCURRENT_EXT void CutCurrentStopIfStart(void);
AP_CUTCURRENT_EXT uchar CutCurrentMode(void);
AP_CUTCURRENT_EXT void CutCurrentSecTimeAdd(void);
AP_CUTCURRENT_EXT void CutCurrentMinTimeAdd(void);



// AP_CUTCURRENT_EXT void CutCurrentStart(uchar ucType);
// AP_CUTCURRENT_EXT void CutCurrentEnd(uchar ucType);
// AP_CUTCURRENT_EXT void CutCurrentMode_34(void);






















#endif  



