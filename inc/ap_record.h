
#ifndef AP_RECORD_H
    #define AP_RECORD_H
#ifdef  AP_RECORD_GLOBALS
    #define AP_RECORD_EXT
#else
    #define AP_RECORD_EXT extern
#endif  
#define CON_RECORD_BLOCK_MAX 60000
#define CON_RECORD_CHANNELS_MAX 6

#ifdef  AP_RECORD_GLOBALS
const ST_RECORD_TYPE_BUFFER_PARAM stRecordBuffer[CON_RECORD_CHANNELS_MAX]=
{
    //FL1_CHANNELS01_RECORD_STARTADDR,
    {21},
        //25,
    //FL1_METER_RECORD_STARTADDR,
    {28},
    //18,
    //FL2_CHANNELS03_RECORD_STARTADDR,
    {12},
    //46,
    //FL1_CHANNELS04_RECORD_STARTADDR,
    {20},
    //26,
    //FL2_CHANNELS05_RECORD_STARTADDR,
    {20},
    //26,
    //FL2_CHANNELS06_RECORD_STARTADDR,
    {10}
    //,56
};
#else
extern const ST_RECORD_TYPE_BUFFER_PARAM stRecordBuffer[];
#endif  

/*Start of ybf on 2010-7-24 15:21 V1.0*/
#define CON_RECORD_DATA_HAVE_CHANNEL GAL_YES                // 记录数据包含通道号
#define CON_RECORD_FLASH_BLOCK_STARTTIME_ADDR   0       // Block 信息内，记录时间的偏移地址
#define CON_RECORD_FLASH_BLOCK_BLOCKSTATUS_ADDR 3       // 状态字节的偏移地址
#define CON_RECORD_FLASH_BLOCK_RECORDSTATUS_ADDR    4   // 该Block内所有通道号字节的偏移地址


#if(CONFIG_METER_FLASH_MODE==CONFIG_METER_FLASH_MODE_2_AT25FLASH)
#define CON_RECORD_FLASH_1FLASH_SECTOR  (96+128)// 64//4                // Sector  数量
#else
#define CON_RECORD_FLASH_1FLASH_SECTOR  (96)// 64//4                // Sector  数量
#endif


#define CON_RECORD_FLASH_1SECTOR_BLOCK  16// 2              // Sector  包含的Block数量
#define CON_RECORD_FLASH_1PAGE_BYTE     256             //  page包含的字节  数量
#define CON_RECORD_FLASH_1RECORD_BYTE   (27+CON_RECORD_DATA_HAVE_CHANNEL)   // 每条记录长度
#define CON_RECORD_FLASH_1PAGE_RECORD   9// 1               // 每页记录的条数
#define CON_RECORD_FLASH_1BLOCK_PAGE        16              //  Block包含的page  数量
#define CON_RECORD_FLASH_1BLOCK_RECORDPAGE      15// 1      //  Block用于记录的page  数量
#define CON_RECORD_FLASH_1BLOCK_BYTE        (CON_RECORD_FLASH_1PAGE_BYTE*CON_RECORD_FLASH_1BLOCK_PAGE)          // block长度
#define CON_RECORD_FLASH_1FLASH_BLOCK   (CON_RECORD_FLASH_1FLASH_SECTOR*CON_RECORD_FLASH_1SECTOR_BLOCK)     // block数量
#define CON_RECORD_FLASH_1BLOCK_RECORD  (CON_RECORD_FLASH_1PAGE_RECORD*CON_RECORD_FLASH_1BLOCK_RECORDPAGE)  // block记录的条数
#define CON_RECORD_FLASH_1SECTOR_RECORD (CON_RECORD_FLASH_1SECTOR_BLOCK*CON_RECORD_FLASH_1BLOCK_RECORD)     // Sector记录的条数
#define CON_RECORD_FLASH_1FLASH_BLK_NUM (CON_RECORD_FLASH_1FLASH_SECTOR*CON_RECORD_FLASH_1SECTOR_BLOCK)     // Flash 包含的Block数
// 147456
#define CON_RECORD_DATA_RECORD_MAX (CON_RECORD_FLASH_1FLASH_SECTOR*CON_RECORD_FLASH_1SECTOR_BLOCK*CON_RECORD_FLASH_1BLOCK_RECORDPAGE*CON_RECORD_FLASH_1PAGE_RECORD) // 总的记录条数

AP_RECORD_EXT const uchar TB_RECORD_CHANNEL_STATUS[6];

// 函数声明
AP_RECORD_EXT void RecordInit(void );
AP_RECORD_EXT void SaveLoadPtrToEE(void);

AP_RECORD_EXT void RecordPointReset(void);

AP_RECORD_EXT void RecordClr(void);

AP_RECORD_EXT ulong RecordSetNext(uchar ucType);

AP_RECORD_EXT void  RecordTimetoPoint(uchar *ucPoint);

//AP_RECORD_EXT void RecordLastRecordTime(uchar ucType);
AP_RECORD_EXT void RecordLastRecordTime(void);

AP_RECORD_EXT uchar RecordIsNeedRecord(uchar ucType);

AP_RECORD_EXT uchar RecordMode(void);

//AP_RECORD_EXT void RecordClrByType( uchar ucType);
AP_RECORD_EXT void RecordClrByType( void);
AP_RECORD_EXT void RecordModeFlashCheck(void);
AP_RECORD_EXT ulong RecordChangePointtoAddr(ulong ulNowPoint);

AP_RECORD_EXT void Delayms(u16 n);

AP_RECORD_EXT ulong RecordGetNowPoint(void);

AP_RECORD_EXT ulong RecordGetLastPoint(void);

AP_RECORD_EXT void WaitFlashFree(uchar RemainTime);







#endif  



