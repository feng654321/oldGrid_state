#define AP_PULSEMODE_GLOBALS
#include "common.h"

void PluseOutInit(void)
{
    uiPluseTime1=0;
    uiPluseTime2=0;
    uiPluseTime3=0;
    uiPluseTime4=0;
    uiPluseTime5=0;
    uiPluseCFKwh=0;
    uiPluseCFkvarh=0;
// AA   ------固定的秒脉冲输出-----------------------
    RAM[RAM_COEF_PULSEMODE]=PULSE_MODE_SECOND;
}

//多功能输出端口根据uPluseType输出相应的类型,uOutTime为脉冲宽度时间,单位ms
void SetPluseValue(uchar uPluseType, u16 uOutTime)
{
    if(PULSE_MODE_SECOND==RAM[RAM_COEF_PULSEMODE])
        return;
    if(RAM[RAM_COEF_PULSEMODE]==uPluseType) // if set the value
    {
        if(uOutTime!=0)
        {
            uiPluseTime1=uOutTime/100;                        
            SetPulseOut1();
        }
        else
        {
            uiPluseTime1=0;                           
        }
    }
}
uchar ucPluseModeSecond;

void PluseMode(void)
{
    static uchar ucLastPulseMode = 0;
    
    if(ucLastPulseMode != RAM[RAM_COEF_PULSEMODE])
    {
        ucLastPulseMode = RAM[RAM_COEF_PULSEMODE];
        ClrPulseOut1();
    }
    
    if(ucPluseModeSecond != RSOFT_RTC_SECOND)
    {
        ucPluseModeSecond=RSOFT_RTC_SECOND;
        if(PULSE_MODE_SECOND==RAM[RAM_COEF_PULSEMODE])
        {
            //ClrPluseOutMode();
            //ClrPulseOut1();
        }
        else
        {
            SetPluseOutMode();
        }
        
    }
}









