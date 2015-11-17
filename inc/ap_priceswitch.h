#ifndef __AP_PRICESWITCH_H__
#define __AP_PRICESWITCH_H__
    
#ifdef  AP_PRICESWITCH_GLOBALS
    #define AP_PRICESWITCH_EXT
#else
    #define AP_PRICESWITCH_EXT extern
#endif  
extern uchar ucPriceSwitchHolidayMax;      // max =254

AP_PRICESWITCH_EXT uchar ucCurrentPriceHEX;

AP_PRICESWITCH_EXT void InitPriceSwitch(void);
AP_PRICESWITCH_EXT uchar NumofEveryDayPriceChangeComm(uchar*point);
AP_PRICESWITCH_EXT uchar NumofEveryDayPriceChange(uchar*point);
AP_PRICESWITCH_EXT uchar NumofEverySeasonDayTableChangeComm(uchar*point);
AP_PRICESWITCH_EXT uchar NumofEverySeasonDayTableChange(uchar*point);
AP_PRICESWITCH_EXT void GetEveryDayTableMax(void);
AP_PRICESWITCH_EXT void GetNextHoliday(void);
AP_PRICESWITCH_EXT void TwoSeasonTableChange(void);
AP_PRICESWITCH_EXT void GetDayTableNumFromSeasonNum(void);
AP_PRICESWITCH_EXT void GetDayTableNumFromHoliday(void);
AP_PRICESWITCH_EXT void GetDayTableNumFromWeekDay(void);
AP_PRICESWITCH_EXT void PriceSwitchMode(void);

AP_PRICESWITCH_EXT uchar TestDayTableLen(uchar ucPoint);
AP_PRICESWITCH_EXT uchar TestDayTableNum(uchar ucPoint);
AP_PRICESWITCH_EXT uchar TestOnePrice(uchar ucPrice);

AP_PRICESWITCH_EXT ulong GetStepPrice(void);

AP_PRICESWITCH_EXT void PriceSwitchModeParaInit(void);
AP_PRICESWITCH_EXT uchar Do2SheetSwitch(void);
AP_PRICESWITCH_EXT void GetCurSheetNum(void);
AP_PRICESWITCH_EXT void GetNext2SheetSwitchTime(void);
AP_PRICESWITCH_EXT void GetCurDayTableNum(void);
AP_PRICESWITCH_EXT void GetNextDayPieceSwitchTime(void);

#endif

