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
// AA   ------�̶������������-----------------------
    RAM[RAM_COEF_PULSEMODE]=PULSE_MODE_SECOND;
}

//�๦������˿ڸ���uPluseType�����Ӧ������,uOutTimeΪ������ʱ��,��λms
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









