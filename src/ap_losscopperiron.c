#define AP_LOSSCOPPERIRON_GLOBALS
#include "common.h"
uchar ucLossCopperIronModeSecond;
#define TYPE_LOSS_COPPERIRON_TOTAL  8
#define TYPE_LOSS_COPPE_ALL         0
#define TYPE_LOSS_RIRON_ALL         1
#define TYPE_LOSS_COPPER_A              2
#define TYPE_LOSS_COPPER_B              3
#define TYPE_LOSS_COPPER_C              4
#define TYPE_LOSS_IRON_A                5
#define TYPE_LOSS_IRON_B                6
#define TYPE_LOSS_IRON_C                7
//ulong ulLossCopperIronBuffer[TYPE_LOSS_COPPERIRON_TOTAL];
//ulong ulLossCopperTempBuffer[3]; 



void LossCopperIronInit(void)
{
    
}

void LossCopperIronMode(void)
{

    if(isSystemResetUnfinisded)
        return ;
    
#if 0
    ulong ulTemp;
    ulong ulCurrentTemp;
    ulong ulTotal;
    uchar ucTimes;
    if(ucLossCopperIronModeSecond!=RSOFT_RTC_SECOND)
    {
        ucLossCopperIronModeSecond=RSOFT_RTC_SECOND;
        //  AA   ÌúËð²¹³¥µçÁ¿¼ÆËã ---->Start      AA 
        ulTotal=0;
        for(ucTimes=0;ucTimes<3;ucTimes++)
        {
            ulTemp=uiNowVoltage[ucTimes];
            ulTemp=ulTemp*ulTemp/100;
            ulTemp=ulTemp*ValueHexFromRam2Bcd(RAM_COEF_A_G+4*2*ucTimes);
            if((METERTYPE_3_3==PROGFUNCTION_TYPE_METER_TYPE  )&&(1==ucTimes))
            {
                ulTemp=0;
            }
            ulLossCopperIronBuffer[TYPE_LOSS_IRON_A+ucTimes] += ulTemp;
            if(ulLossCopperIronBuffer[TYPE_LOSS_IRON_A+ucTimes]>3600000)
            {
                ulTemp=ulLossCopperIronBuffer[TYPE_LOSS_IRON_A+ucTimes]/3600000;
                ulLossCopperIronBuffer[TYPE_LOSS_IRON_A+ucTimes] %=3600000;
                ulTotal += ulTemp;
                KwhAddIntDataFromType(PT_KWH_A_LOST_IRON_ALL+12*ucTimes,ulTemp);
            }
        }
        if(ulTotal>0)
        {
            KwhAddIntDataFromType(PT_KWH_LOST_IRON_ALL,ulTotal);
        }
        //  AA   ÌúËð²¹³¥µçÁ¿¼ÆËã ---->End      AA 
        //  AA   Í­Ëð²¹³¥µçÁ¿¼ÆËã ---->Start      AA 
        ulTotal=0;
        for(ucTimes=0;ucTimes<3;ucTimes++)
        {
            ulCurrentTemp=0;
            ulTemp=ulNowCurrent[ucTimes]/10;
            ulLossCopperTempBuffer[ucTimes] +=ulTemp*ulTemp;
            if(ulLossCopperTempBuffer[ucTimes] >3600000)
            {
                ulCurrentTemp=ulLossCopperTempBuffer[ucTimes]/3600000;
                ulLossCopperTempBuffer[ucTimes] %= 3600000;
                ulTemp=ulCurrentTemp*ValueHexFromRam2Bcd(RAM_COEF_A_R+4*2*ucTimes);
                if((METERTYPE_3_3==PROGFUNCTION_TYPE_METER_TYPE  )&&(1==ucTimes))
                {
                    ulTemp=0;
                }
                ulLossCopperIronBuffer[TYPE_LOSS_COPPER_A+ucTimes] +=ulTemp;
                if(ulLossCopperIronBuffer[TYPE_LOSS_COPPER_A+ucTimes] >1000000)
                {
                    ulTemp=ulLossCopperIronBuffer[TYPE_LOSS_COPPER_A+ucTimes] / 1000000;
                    ulLossCopperIronBuffer[TYPE_LOSS_COPPER_A+ucTimes] %= 1000000;
                    ulTotal += ulTemp;
                    KwhAddIntDataFromType(PT_KWH_A_LOST_COPPER_ALL+12*ucTimes,ulTemp);
                }
            }
            
        }
        if(ulTotal>0)
        {
            KwhAddIntDataFromType(PT_KWH_LOST_COPPER_ALL,ulTotal);
        }
        
        //  AA   Í­Ëð²¹³¥µçÁ¿¼ÆËã ---->End     AA 
        
        WriteDataDirect((uchar *)&ulLossCopperIronBuffer[0], EPL_KWH_RESIDUE_LOST_COPPER_IRON_START, 4*TYPE_LOSS_COPPERIRON_TOTAL);
        
        
        
    }
#endif  
}

void LossCopperIronResume(void)
{
//  ReadDataDirect(EPL_KWH_RESIDUE_LOST_COPPER_IRON_START, 4*TYPE_LOSS_COPPERIRON_TOTAL, (uchar *)&ulLossCopperIronBuffer[0]);
}






























































