
#ifndef AP_PRICEUSE_H
    #define AP_PRICEUSE_H
#ifdef  AP_PRICEUSE_GLOBALS
    #define AP_PRICEUSE_EXT
#else
    #define AP_PRICEUSE_EXT extern
#endif  

AP_PRICEUSE_EXT ulong ulCTPTNum;

 


AP_PRICEUSE_EXT void InitPriceUse(void);

AP_PRICEUSE_EXT uchar PriceUseAddKwh(ulong ulRamAddr,uchar ucCurrentPrice);















#endif  



