#define AP_PRICEUSE_GLOBALS
#include "common.h"

ulong ulCurrentKwh0Dot01Use;
ulong ulCurrentPrice0Dot01UseH,ulCurrentPrice0Dot01UseL;
#define CON_PRICE_COEF_H 100000
#define CON_PRICE_COEF_L 1000

#define CON_PRICE_NUM_MAX (4)

ulong PriceGetCurrent(void);
void PriceChangePriceUse(void);


void InitPriceUse(void)
{
    
}

#if 0
uchar PriceUseAddKwh(ulong ulRamAddr,uchar ucCPrice)
{
    ulong ulData;
    uchar ulTemp;
    if(MODE_POWER_CALC_POINT==MODE_POWER_CALC_POINT_3DOT)
    {
        ulTemp=1;
    }
    else
    {
        ulTemp=10;
    }
    if((ucCPrice<=4)&&(0!=ucCPrice))
    {
        ulData=Bcd5DataToLong(&RAM[ulRamAddr+ucCPrice*5])+ulTemp;   
        LongToBcd5Data(ulData,&RAM[ulRamAddr+ucCPrice*5]);
    }
    ulData=Bcd5DataToLong(&RAM[ulRamAddr])+ulTemp;  
    LongToBcd5Data(ulData,&RAM[ulRamAddr]);
    WriteDataDirect(&RAM[ulRamAddr], EPL_KWH_ALL_USE_START, BYTES_KWH_USE_TOTAL);
    return 1;
}

#endif
































