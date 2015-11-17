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

#define  COMM_LOADRECORD_TIME_SIZE                                  (sizeof(RECORDTIM))       ////��¼�м�¼ʱ��ĳ���

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
                    
                    //////2�ฺ�ɼ�¼
                    typedef struct
                    {
                        RECORDTIM  RecordTime;
                        BCD24         RecordData;
                    }STR_LOADRECORD1;
                    
                    ///////3�ฺ�ɼ�¼
                    typedef struct
                    {
                        RECORDTIM  RecordTime;
                        BCD8          RecordData;
                    }STR_POWERRECORD2;
                    
                    ///////4�ฺ�ɼ�¼
                    typedef struct
                    {
                        RECORDTIM  RecordTime;
                        BCD16         RecordData;
                    }STR_POWERRECORD3;
                    
                    ////////5�ฺ�ɼ�¼
                    typedef struct
                    {
                        RECORDTIM  RecordTime;
                        BCD16         RecordData;
                    }STR_POWERRECORD4;
                    
                        ////////6�ฺ�ɼ�¼
                    typedef struct
                    {
                        RECORDTIM  RecordTime;
                        BCD6          RecordData;
                    }STR_POWERRECORD5;
 
                    
                    
                    typedef struct
                    {
                        uchar    Cycle;   ////�ռ���û�м���0û�У�1 ������
                        u16     Ptr;    ////��¼ָ�롣
                    }STR_RECORD_PTR_INFO;
                    
                    typedef struct s_recordstt
                    {
                        ulong ulPt;     //ָ��
                        ulong ulCnt;    //��ǰ��¼����
                    }S_RECORDSTT;
                    
                    ////////��¼��������Ϣ��
                    typedef struct
                    {
                        ulong      HeadAddr; ///�ü�¼�ռ���׵�ַ
                        uchar    DataLen;  ///ÿ����¼�ĳ��ȡ�
                        uchar    PageNum;  ///ÿҳ��¼������
                        u16        uiBlockMax; // --aa��Ӧͨ��ʫ������ֵaa--
                        //STR_RECORD_PTR_INFO  PtrInfo;   ////��¼ָ����Ϣ��
                        S_RECORDSTT sRStt;      //���ɼ�¼״̬��Ϣ
                    } STR_RECORD_INDEX;

                
                    
                    
                    
#define   COMM_LOADRECORD_CHENNL_NUM                            (6)     /////����ͨ������           
//#define   COMM_LOADRECORD_TIMCHG_NUM                          (1500)  ////������¼����
#define   COMM_LOADRECORD_RECORD_NUM                            (CON_RECORD_BLOCK_MAX)      ////���ɼ�¼����

    ////////���ɼ�¼�����Ϣ
                    typedef struct  
                    {
                         RECORDTIM  time;    /// --- ���ɼ�¼��ʱ��
                         ulong      Ptr[COMM_LOADRECORD_CHENNL_NUM];    ///--- ���ҵ��ĸ�����¼��λ�ã������޼�¼� FFFF
                         //u16         Ptr[COMM_LOADRECORD_CHENNL_NUM];    ///--- ���ҵ��ĸ�����¼��λ�ã������޼�¼� FFFF
                    } TIMEMULITIINDEX;
                    
                    /////////��ϲ��Ҹ��ɼ�¼ָ�������
                    typedef struct  
                    {
                         u16       Ptr[COMM_LOADRECORD_CHENNL_NUM];    ///--- ���ҵ��ĸ�����¼��λ�ã������޼�¼� FFFF
                    } SEARCHPTRARR;

/////////////����ͨ���������ݽṹ
                    typedef struct  
                    {
                        ulong  Ptr;      ////ָ��λ��
                        uchar OddNum;   ////ʣ��ĸ���
                        uchar LoadNum;  ////����ͨ����
                    }STR_LAST_LOADREC_ONE;

//////////////����ͨ���������ݽṹ
                    typedef struct  
                    {
                        ulong  Ptr;      ////ָ��λ�ã�ͨ���Ŵ�0---5��
                        uchar OddNum;   ////ʣ��ĸ���
                    }STR_LAST_LOADREC_MULT;
/*typedef struct    
{
    u16  Ptr[COMM_LOADRECORD_CHENNL_NUM];      ////ָ��λ�ã�ͨ���Ŵ�0---5��
    uchar OddNum;   ////ʣ��ĸ���
}STR_LAST_LOADREC_MULT;*/


#define   COMM_LOADRECORD_READOUT_NO                                    (CommExpReceiveDataBuffer.buff[14])
#define   COMM_LOADRECORD_READOUT_TIME                                  (CommExpReceiveDataBuffer.buff[15])


#define   COMM_LOADRECORD_CHANNEL0_MAXSIZE             (154)    ///���ɼ�¼��������󳤶�
#define   COMM_LOADRECORD_CHANNEL1_MAXSIZE             (147)    ///���ɼ�¼��������󳤶�
#define   COMM_LOADRECORD_CHANNEL2_MAXSIZE             (163)    ///���ɼ�¼��������󳤶�
#define   COMM_LOADRECORD_CHANNEL3_MAXSIZE             (155)    ///���ɼ�¼��������󳤶�
#define   COMM_LOADRECORD_CHANNEL4_MAXSIZE             (155)    ///���ɼ�¼��������󳤶�
#define   COMM_LOADRECORD_CHANNEL5_MAXSIZE             (165)    ///���ɼ�¼��������󳤶�

                                        

#define   COMM_LOADRECORD_EQU                                               0      ////���
#define   COMM_LOADRECORD_HT                                                1      ////����
#define   COMM_LOADRECORD_LT                                                2      ////С��


#if(CONFIG_METER_FLASH_MODE==CONFIG_METER_FLASH_MODE_2_AT25FLASH)
#define   COMM_LOADRECORD_SEARCH_NUM                        (19)    //(16)      ///���α���ҵĴ���    
#else
#define   COMM_LOADRECORD_SEARCH_NUM                        (18)    //(16)      ///���α���ҵĴ���    
#endif
#define   COMM_RECORD_MAXSIZE                                               (30)      ///������¼������ֽ�����3���ֽڵ�������

#define   COMM_RECORDPTR_NULL                                               (0xFFFFFFFF)   ////ָ��Ϊ��

//#define   COMM_RECORDPTR_NULL                                             (0xFFFF)   ////ָ��Ϊ��

#define   COMM_LOAD_CHANNEL_NULL                                                                  (COMM_LOADRECORD_CHENNL_NUM)    ////û���ҵ����ݵ�ͨ��
////���ɼ�¼��������
COMMLOADREC_EXT void CommReadLoadData (STR_READ_RETURN_PARA *Dest,ulong ID);
COMMLOADREC_EXT u16  ReadNRecFmMultToBuf(ulong ulPTR,ulong ulPtr,uchar ucFameNo,uchar ucNomber,uchar *Dest);
COMMLOADREC_EXT u16   CommLoadLastFrameRead(uchar ucPtr,ulong ID,uchar* Dest);
COMMLOADREC_EXT ulong ReadLoadTimeByPtr(ulong RecPtr);
COMMLOADREC_EXT ulong ReadGetPtr(uchar Num,u16 Block);
COMMLOADREC_EXT ulong ReadGetBlockAddr(u16 Block);
COMMLOADREC_EXT ulong SearchSameTimeBefore(ulong ulPtr);
COMMLOADREC_EXT uchar ReadChannelNumByPtr(ulong RecPtr);
#endif
