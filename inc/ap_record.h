
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
#define CON_RECORD_DATA_HAVE_CHANNEL GAL_YES                // ��¼���ݰ���ͨ����
#define CON_RECORD_FLASH_BLOCK_STARTTIME_ADDR   0       // Block ��Ϣ�ڣ���¼ʱ���ƫ�Ƶ�ַ
#define CON_RECORD_FLASH_BLOCK_BLOCKSTATUS_ADDR 3       // ״̬�ֽڵ�ƫ�Ƶ�ַ
#define CON_RECORD_FLASH_BLOCK_RECORDSTATUS_ADDR    4   // ��Block������ͨ�����ֽڵ�ƫ�Ƶ�ַ


#if(CONFIG_METER_FLASH_MODE==CONFIG_METER_FLASH_MODE_2_AT25FLASH)
#define CON_RECORD_FLASH_1FLASH_SECTOR  (96+128)// 64//4                // Sector  ����
#else
#define CON_RECORD_FLASH_1FLASH_SECTOR  (96)// 64//4                // Sector  ����
#endif


#define CON_RECORD_FLASH_1SECTOR_BLOCK  16// 2              // Sector  ������Block����
#define CON_RECORD_FLASH_1PAGE_BYTE     256             //  page�������ֽ�  ����
#define CON_RECORD_FLASH_1RECORD_BYTE   (27+CON_RECORD_DATA_HAVE_CHANNEL)   // ÿ����¼����
#define CON_RECORD_FLASH_1PAGE_RECORD   9// 1               // ÿҳ��¼������
#define CON_RECORD_FLASH_1BLOCK_PAGE        16              //  Block������page  ����
#define CON_RECORD_FLASH_1BLOCK_RECORDPAGE      15// 1      //  Block���ڼ�¼��page  ����
#define CON_RECORD_FLASH_1BLOCK_BYTE        (CON_RECORD_FLASH_1PAGE_BYTE*CON_RECORD_FLASH_1BLOCK_PAGE)          // block����
#define CON_RECORD_FLASH_1FLASH_BLOCK   (CON_RECORD_FLASH_1FLASH_SECTOR*CON_RECORD_FLASH_1SECTOR_BLOCK)     // block����
#define CON_RECORD_FLASH_1BLOCK_RECORD  (CON_RECORD_FLASH_1PAGE_RECORD*CON_RECORD_FLASH_1BLOCK_RECORDPAGE)  // block��¼������
#define CON_RECORD_FLASH_1SECTOR_RECORD (CON_RECORD_FLASH_1SECTOR_BLOCK*CON_RECORD_FLASH_1BLOCK_RECORD)     // Sector��¼������
#define CON_RECORD_FLASH_1FLASH_BLK_NUM (CON_RECORD_FLASH_1FLASH_SECTOR*CON_RECORD_FLASH_1SECTOR_BLOCK)     // Flash ������Block��
// 147456
#define CON_RECORD_DATA_RECORD_MAX (CON_RECORD_FLASH_1FLASH_SECTOR*CON_RECORD_FLASH_1SECTOR_BLOCK*CON_RECORD_FLASH_1BLOCK_RECORDPAGE*CON_RECORD_FLASH_1PAGE_RECORD) // �ܵļ�¼����

AP_RECORD_EXT const uchar TB_RECORD_CHANNEL_STATUS[6];

// ��������
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



