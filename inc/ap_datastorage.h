




#ifndef AP_DATASTORAGE_H
    #define AP_DATASTORAGE_H
    
#ifdef  AP_DATASTORAGE_GLOBALS
    #define AP_DATASTORAGE_EXT
#else
    #define AP_DATASTORAGE_EXT extern
#endif  

//#define MEM_TYPE_FM1        0x01
//#define MEM_TYPE_FM2        0x02
#define MEM_TYPE_EPL        0x01
#define MEM_TYPE_BAK        0x02
#define MEM_TYPE_FLASH      0x03
//#define MEM_TYPE_FLASH2     0x06
#define MEM_TYPE_MAX        0x03

// extern uchar Write(uchar *upData,uchar ucStoryType,uchar uiDatalen,ulong ucStoryAddr);
 // extern uchar Read(uchar ucStoryType,uchar uiDatalen,,ulong ucStoryAddr,uchar *upData);
AP_DATASTORAGE_EXT void MemoryStatusInit(void);

AP_DATASTORAGE_EXT uchar ReadDataDirect(ulong ulDataName,  u16 nLen, uchar* pDest);

AP_DATASTORAGE_EXT uchar WriteDataDirect(const uchar* pSrc, ulong DataName,   u16 nLen);

//AP_DATASTORAGE_EXT uchar ReadDataDirectByComm(ulong DataName,   u16 nLen, uchar* pSrc);

// AP_DATASTORAGE_EXT uchar WriteDataDirectByComm(uchar* pSrc, ulong DataName,   u16 nLen);


AP_DATASTORAGE_EXT uchar WriteDataDirectEX (uchar *Src,ulong Address,ulong offset,u16 Lens);
AP_DATASTORAGE_EXT uchar ReadDataDirectEX(uchar *Dst,ulong Address,ulong offset,u16 Lens);
AP_DATASTORAGE_EXT void MemErrCountSave(void);

AP_DATASTORAGE_EXT void EraseAllFlash(void);

#define DATA_STORAGE_BLOCK_SIZE     512
#if(DATA_STORAGE_BLOCK_SIZE > CON_WR_DATA_LEN_MAX)
exit(1);
#endif
uchar SetDataDirrect(u32 DataName, u8 ucValue, u16 nLen);
uchar CpyDataDirrect(u32 DstDataName, u32 SrcDataName, u16 nLen);


#define ReadDataDirectByComm ReadDataDirect
#define WriteDataDirectByComm WriteDataDirect

#if(CONFIG_METER_FACTORY_MODE==CONFIG_METER_FACTORY_MODE_ENABLE)
AP_DATASTORAGE_EXT void InitParameterChipInfactory(uchar value);
AP_DATASTORAGE_EXT void InitParameterChipInfactory_withMeterAbout(uchar value);
AP_DATASTORAGE_EXT void InitParameterInfactory(void);
#endif

#endif








