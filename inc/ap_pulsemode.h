


#ifndef AP_PULSEMODE_H
    #define AP_PULSEMODE_H
#ifdef  AP_PULSEMODE_GLOBALS
    #define AP_PULSEMODE_EXT
#else
    #define AP_PULSEMODE_EXT extern
#endif  

AP_PULSEMODE_EXT u16 uiPluseTime1;
AP_PULSEMODE_EXT u16 uiPluseTime2;
AP_PULSEMODE_EXT u16 uiPluseTime3;
AP_PULSEMODE_EXT u16 uiPluseTime4;
AP_PULSEMODE_EXT u16 uiPluseTime5;
AP_PULSEMODE_EXT u16 uiPluseCFKwh;
AP_PULSEMODE_EXT u16 uiPluseCFkvarh;

AP_PULSEMODE_EXT void PluseOutInit(void);

AP_PULSEMODE_EXT void SetPluseValue(uchar uPluseType, u16 uOutTime);

AP_PULSEMODE_EXT void PluseMode(void);

#define PULSE_MODE_SECOND           0x00    // AA ��������� AA
#define PULSE_MODE_DEMANDCYCLE  0x01    // AA �������� AA
#define PULSE_MODE_DAYTABLECHANGE   0x02    // AA ʱ���л� AA
//#define PULSE_MODE_PRICECHANGE    0x02    // AA �����л� AA
#define PULSE_MODE_KWH_F            0x03    // AA �����й� AA
#define PULSE_MODE_KWH_R            0x04    // AA �����й� AA
#define PULSE_MODE_KVARH_C1         0x05    // AA ����޹�1 AA
#define PULSE_MODE_KVARH_C2         0x06    // AA ����޹�2 AA 
#define PULSE_MODE_KW_F_OVER        0x07    // AA �����й����ʳ��� AA
#define PULSE_MODE_KW_R_OVER        0x08    // AA �����й����ʳ��� AA
#define PULSE_MODE_KVARH_Q1         0x09    // AA ��1 �����޹�AA
#define PULSE_MODE_KVARH_Q2         0x10    // AA ��1 �����޹�AA
#define PULSE_MODE_KVARH_Q3         0x11    // AA ��1 �����޹�AA
#define PULSE_MODE_KVARH_Q4         0x12    // AA ��1 �����޹�AA
#define PULSE_MODE_CUOFENG      0x13    // AA ��1 �����޹�AA






















#endif


