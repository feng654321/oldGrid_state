#ifndef  COMMLOADREC_H
                    #define  COMMLOADREC_H
                    #define  COMMLOADREC_EXT      extern
                    

typedef uchar BCD1[1];
typedef uchar BCD2[2];
typedef uchar BCD3[3];
typedef uchar BCD4[4];
typedef uchar BCD5[5];
typedef uchar BCD7[7];


typedef uchar BCD6[6];
typedef uchar BCD8[8];
typedef uchar BCD16[16];
typedef uchar BCD17[17];

typedef uchar BCD24[24];

#define  RECORDTIM                          BCD3      

#define  COMM_LOADRECORD_PAGESIZE       (512)

#define  COMM_LOADRECORD_TIME_SIZE                                  (sizeof(RECORDTIM))       ////记录中记录时间的长度

//#define  COMM_LOADRECORD0_LENTH     (17+COMM_LOADRECORD_TIME_SIZE)
//#define  COMM_LOADRECORD1_LENTH     (24+COMM_LOADRECORD_TIME_SIZE)
//#define  COMM_LOADRECORD2_LENTH     (8+COMM_LOADRECORD_TIME_SIZE)
//#define  COMM_LOADRECORD3_LENTH     (16+COMM_LOADRECORD_TIME_SIZE)
//#define  COMM_LOADRECORD4_LENTH     (16+COMM_LOADRECORD_TIME_SIZE)
//#define  COMM_LOADRECORD5_LENTH     (6+COMM_LOADRECORD_TIME_SIZE)

//#define  COMM_LOADRECORD0_ONEPAGE_NUM     (COMM_LOADRECORD_PAGESIZE/COMM_LOADRECORD0_LENTH)
//#define  COMM_LOADRECORD1_ONEPAGE_NUM     (COMM_LOADRECORD_PAGESIZE/COMM_LOADRECORD1_LENTH)
//#define  COMM_LOADRECORD2_ONEPAGE_NUM     (COMM_LOADRECORD_PAGESIZE/COMM_LOADRECORD2_LENTH)
//#define  COMM_LOADRECORD3_ONEPAGE_NUM     (COMM_LOADRECORD_PAGESIZE/COMM_LOADRECORD3_LENTH)
//#define  COMM_LOADRECORD4_ONEPAGE_NUM     (COMM_LOADRECORD_PAGESIZE/COMM_LOADRECORD4_LENTH)
//#define  COMM_LOADRECORD5_ONEPAGE_NUM     (COMM_LOADRECORD_PAGESIZE/COMM_LOADRECORD5_LENTH)



                    typedef struct
                    {
                        RECORDTIM       RecordTime;
                        BCD17           RecordData;
                    }STR_LOADRECORD0;
                    
                    //////2类负荷记录
                    typedef struct
                    {
                        RECORDTIM  RecordTime;
                        BCD24         RecordData;
                    }STR_LOADRECORD1;
                    
                    ///////3类负荷记录
                    typedef struct
                    {
                        RECORDTIM  RecordTime;
                        BCD8          RecordData;
                    }STR_POWERRECORD2;
                    
                    ///////4类负荷记录
                    typedef struct
                    {
                        RECORDTIM  RecordTime;
                        BCD16         RecordData;
                    }STR_POWERRECORD3;
                    
                    ////////5类负荷记录
                    typedef struct
                    {
                        RECORDTIM  RecordTime;
                        BCD16         RecordData;
                    }STR_POWERRECORD4;
                    
                        ////////6类负荷记录
                    typedef struct
                    {
                        RECORDTIM  RecordTime;
                        BCD6          RecordData;
                    }STR_POWERRECORD5;
 
                    
                    
                    typedef struct
                    {
                        uchar    Cycle;   ////空间有没有记满0没有，1 记满。
                        u16     Ptr;    ////记录指针。
                    }STR_RECORD_PTR_INFO;
                    
                    typedef struct s_recordstt
                    {
                        ulong ulPt;     //指针
                        ulong ulCnt;    //当前记录总数
                    }S_RECORDSTT;
                    
                    ////////记录的索引信息。
                    typedef struct
                    {
                        ulong      HeadAddr; ///该记录空间的首地址
                        uchar    DataLen;  ///每条记录的长度。
                        uchar    PageNum;  ///每页记录的条数
                        u16        uiBlockMax; // --aa对应通道诗句的最大值aa--
                        //STR_RECORD_PTR_INFO  PtrInfo;   ////记录指针信息。
                        S_RECORDSTT sRStt;      //负荷记录状态信息
                    } STR_RECORD_INDEX;

                
                    
                    
                    
#define   COMM_LOADRECORD_CHENNL_NUM                            (6)     /////负荷通道个数           
//#define   COMM_LOADRECORD_TIMCHG_NUM                          (1500)  ////辅助记录个数
#define   COMM_LOADRECORD_RECORD_NUM                            (CON_RECORD_BLOCK_MAX)      ////负荷记录个数

    ////////负荷记录组合信息
                    typedef struct  
                    {
                         RECORDTIM  time;    /// --- 负荷记录的时间
                         ulong      Ptr[COMM_LOADRECORD_CHENNL_NUM];    ///--- 查找到的各个记录的位置，对于无记录填： FFFF
                         //u16         Ptr[COMM_LOADRECORD_CHENNL_NUM];    ///--- 查找到的各个记录的位置，对于无记录填： FFFF
                    } TIMEMULITIINDEX;
                    
                    /////////组合查找负荷记录指针的数组
                    typedef struct  
                    {
                         u16       Ptr[COMM_LOADRECORD_CHENNL_NUM];    ///--- 查找到的各个记录的位置，对于无记录填： FFFF
                    } SEARCHPTRARR;

/////////////单个通道后续数据结构
                    typedef struct  
                    {
                        ulong  Ptr;      ////指针位置
                        uchar OddNum;   ////剩余的个数
                        uchar LoadNum;  ////负荷通道号
                    }STR_LAST_LOADREC_ONE;

//////////////负荷通道后续数据结构
                    typedef struct  
                    {
                        ulong  Ptr;      ////指针位置（通道号从0---5）
                        uchar OddNum;   ////剩余的个数
                    }STR_LAST_LOADREC_MULT;
/*typedef struct    
{
    u16  Ptr[COMM_LOADRECORD_CHENNL_NUM];      ////指针位置（通道号从0---5）
    uchar OddNum;   ////剩余的个数
}STR_LAST_LOADREC_MULT;*/


#define   COMM_LOADRECORD_READOUT_NO                                    (CommExpReceiveDataBuffer.buff[14])
#define   COMM_LOADRECORD_READOUT_TIME                                  (CommExpReceiveDataBuffer.buff[15])


#define   COMM_LOADRECORD_CHANNEL0_MAXSIZE             (154)    ///负荷记录读出的最大长度
#define   COMM_LOADRECORD_CHANNEL1_MAXSIZE             (147)    ///负荷记录读出的最大长度
#define   COMM_LOADRECORD_CHANNEL2_MAXSIZE             (163)    ///负荷记录读出的最大长度
#define   COMM_LOADRECORD_CHANNEL3_MAXSIZE             (155)    ///负荷记录读出的最大长度
#define   COMM_LOADRECORD_CHANNEL4_MAXSIZE             (155)    ///负荷记录读出的最大长度
#define   COMM_LOADRECORD_CHANNEL5_MAXSIZE             (165)    ///负荷记录读出的最大长度

                                        

#define   COMM_LOADRECORD_EQU                                               0      ////相等
#define   COMM_LOADRECORD_HT                                                1      ////大于
#define   COMM_LOADRECORD_LT                                                2      ////小于


#if(CONFIG_METER_FLASH_MODE==CONFIG_METER_FLASH_MODE_2_AT25FLASH)
#define   COMM_LOADRECORD_SEARCH_NUM                        (19)    //(16)      ///二次表查找的次数    
#else
#define   COMM_LOADRECORD_SEARCH_NUM                        (18)    //(16)      ///二次表查找的次数    
#endif
#define   COMM_RECORD_MAXSIZE                                               (30)      ///各个记录的最大字节数（3个字节的余量）

#define   COMM_RECORDPTR_NULL                                               (0xFFFFFFFF)   ////指针为空

//#define   COMM_RECORDPTR_NULL                                             (0xFFFF)   ////指针为空

#define   COMM_LOAD_CHANNEL_NULL                                                                  (COMM_LOADRECORD_CHENNL_NUM)    ////没有找到数据的通道
////负荷记录读出函数
COMMLOADREC_EXT void CommReadLoadData (STR_READ_RETURN_PARA *Dest,ulong ID);
COMMLOADREC_EXT u16  ReadNRecFmMultToBuf(ulong ulPTR,ulong ulPtr,uchar ucFameNo,uchar ucNomber,uchar *Dest);
COMMLOADREC_EXT u16   CommLoadLastFrameRead(uchar ucPtr,ulong ID,uchar* Dest);
COMMLOADREC_EXT ulong ReadLoadTimeByPtr(ulong RecPtr);
COMMLOADREC_EXT ulong ReadGetPtr(uchar Num,u16 Block);
COMMLOADREC_EXT ulong ReadGetBlockAddr(u16 Block);
COMMLOADREC_EXT ulong SearchSameTimeBefore(ulong ulPtr);
COMMLOADREC_EXT uchar ReadChannelNumByPtr(ulong RecPtr);
#endif
