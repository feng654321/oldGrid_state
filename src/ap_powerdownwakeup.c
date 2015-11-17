#define AP_POWERDOWNWAKEUP_GLOBALS
#include "common.h"
// extern void GPIO_Configuration(void);

#if(CONFIG_METER_EVENT_COVEROPEN_SPECIAL_MODE_POWERDOWN_RECORD==CONFIG_METER_EVENT_COVEROPEN_SPECIAL_MODE)

void PowerDownOPenEEpromPower(void)
{

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB  | RCC_APB2Periph_GPIOC  \
    | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);
    InitGui(1);
//  GPIO_Configuration();
    InitI2c(I2CA);
    InitI2c(I2CB);
    InitI2c(I2CC);
    InitI2c(I2CD);
    InitI2c(I2CE);
    InitFlash25(FIRST_FLASH);   
    OpenFlashPowerFromBat();

}


void PowerDownGetTime(void)
{

    if(ReadRealTimeFormCMOSChip(&realTime)) //read real time to buf HardTime form real time CMOS chip 
    {
        TimeDeal(GAL_NO);
    }
    
}


void PowerDownRecordEvent(void)
{
    PowerDownOPenEEpromPower();
    PowerDownGetTime();
}



#endif



