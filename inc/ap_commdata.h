
#ifndef AP_COMMDATA_H
    #define AP_COMMDATA_H
    
#ifdef  AP_COMMDATA_GLOBALS
    #define AP_COMMDATA_EXT
#else
    #define AP_COMMDATA_EXT extern
#endif  





#define CONST_COMM_DATA_MAX_LEN (132+4)
#define CONST_COMM_OTHERDATA_LEN  12
#define CONST_COMM_BUFFER_MAX_LEN (CONST_COMM_DATA_MAX_LEN+CONST_COMM_OTHERDATA_LEN+1)

typedef union
{
    uchar ucArray_Comm[CONST_COMM_BUFFER_MAX_LEN];
    struct
    {
        uchar ucFirstHead;
        uchar ucAddress[6];
        uchar ucSecondHead;
        uchar ucControl;
        uchar ucLength;
        union
        {
            uchar ucArray_Data[CONST_COMM_DATA_MAX_LEN];
            struct
                {
                uchar ucDI0;
                uchar ucDI1;
                }bytes;
            u16  uICode97;
            struct
                {
                uchar uc07DI0;
                uchar uc07DI1;
                uchar uc07DI2;
                uchar uc07DI3;
                }DL645_07;
            struct
                {
                u16 uiCodeLow;
                u16 uiCodeHigh;
                }DL645_07INT;
            ulong uLCode07;
            
            struct
                {
                ulong ulCode07;
                ulong ulPassWord;
                ulong ulUser;
                }Type_Control14;
            struct
                {
                ulong ulPassWord;
                ulong ulUser;
                }Type_Control19;
            struct
                {
                ulong ulPassWord;
                ulong ulUser;
                }Type_Control1A;
            struct
                {
                ulong ulPassWord;
                ulong ulUser;
                }Type_Control1B;
            struct
                {
                ulong ulPassWord;
                ulong ulUser;
                }Type_Control1C;
            struct 
                {
                u16 uicode97;
                ulong ulPasswd;
                u16 ulConRandomData;
                u16 ulConRelayId;
                }Type_JILIN_RELAY;
            struct
            {
                u16 uicode97;// 0xFE00;
                ulong ulPasswd;
                uchar ucStoryType;
                uchar ucAddrLow;
                uchar ucAddrM;
                uchar ucAddrHigh;
                uchar ucDatalen;
                uchar ucWriteData[10];
            }Type_OC_Write;
            struct
            {
                u16 uicode97;// 0xFE00;
                // ulong ulPasswd;
                uchar ucStoryType;
                uchar ucAddrLow;
                uchar ucAddrM;
                uchar ucAddrHigh;
                uchar ucDatalen;
                uchar ucWriteData[10];
            }Type_OC_Read;// 0xFE00;
            struct
            {
                u16 uicode97;// BE02;
                ulong ulPasswd;
                uchar ucAddr;
                uchar ucDatalen;
                uchar ucWriteData[10];
            }Type_ADE7758_Write; // BE02;
            struct
            {
                u16 uicode97;// BE02;
                // ulong ulPasswd;
                uchar ucAddr;
                uchar ucDatalen;
                uchar ucReadData[10];
            }Type_ADE7758_READ; // BE02;
            
            }ucDataPart;
        uchar ucChksum;
        uchar ucEnding;
    }DL645Data; 
}COMM_BUF;

typedef union
{
    struct
    {
        uchar ucTransDataPoint;
        uchar ucTransDataLength;
    }Tbytes;
    struct
    {
        uchar ucReceiveDataPoint;
        uchar ucReceiveDataLength;
    }Rbytes;
}COMM_DATA_UNION;


typedef struct
{
    // --> ��Ӧͨ���еĲ����ʲ���  -->
    uchar boud;
    // --> �����Ҫ��ʱ���Ĳ����ʵ�ʱ��ʹ��  -->
    uchar time_boud_500;
    // --> ��ǰ���ͨ����״̬  -->
    uchar status;
    // --> ��ǰ���ܵ��������жϵ�ַ��״̬  -->
    uchar status_Addr_info;
    // --> ��ǰ����״̬�ĳ���ʱ��  -->
    uchar comm_rec_time;
    // -->  ��ǰ����״̬�ĳ���ʱ�� -->
    uchar comm_send_time;
    // --> ��ǰͨ��������ʱ��ʱ�� -->
    uchar comm_send_delay;
    // -->  ��ǰ���ݽ��ջ��߷��͵ĵĳ��ȺͶ�Ӧָ�� -->
    COMM_DATA_UNION DataPoint;
    // -->  ��ǰͨ���н��ջ��߷����е��������� -->
    COMM_BUF DataBuffer;
}UN_COMM_BUF_PARAM;


typedef union
{
    struct
    {
        // -->  ��������-->
        uchar bOtherError : 1;
        // -->  ����������-->
        uchar bNodataError : 1;
        // -->  ����������δ��Ȩ-->
        uchar bPwdError : 1;
        // -->  ͨѶ���ʲ��ܸ���-->
        uchar bBoudError : 1;
        // -->  ��ʱ������-->
        uchar bSeasonError : 1;
        // -->  ��ʱ������-->
        uchar bDayperiodError : 1;
        // -->  ��������-->
        uchar bRateError : 1;
        // -->  ����-->
        // -->// ����Ҫ��
        uchar bRelayError : 1;  
    }Bits;
    uchar ucData;
}UN_COMMSTATUS_ERRFLAG_PARAM;
typedef union
{
    struct
    {
        // -->  ��������-->
        uchar b_other_error : 1;
        // -->  ����������-->
        uchar b_nodata_error : 1;
        // -->  ����������δ��Ȩ-->
        uchar b_pwd_error : 1;
        // -->  ͨѶ���ʲ��ܸ���-->
        uchar b_boud_error : 1;
        // -->  ��ʱ������-->
        uchar b_season_error : 1;
        // -->  ��ʱ������-->
        uchar b_dayperiod_error : 1;
        // -->  ��������-->
        uchar b_rate_error : 1;
        // -->  ����-->
        uchar b_relay_error : 1;    // ����Ҫ��
    }bit;
    uchar ucErrorFlag;
}UN_COMMSTATUS_ERRFLAG_OLD_PARAM;
AP_COMMDATA_EXT UN_COMM_BUF_PARAM CommSys[1];
AP_COMMDATA_EXT UN_COMM_BUF_PARAM *CommDataPoint;
AP_COMMDATA_EXT uchar  ucCommChannelsId;

AP_COMMDATA_EXT UN_COMMSTATUS_ERRFLAG_OLD_PARAM PROTOCOL_ERR_FLAG;

AP_COMMDATA_EXT uchar ucRecordWriteProgram_point;
AP_COMMDATA_EXT TYPE_LONG_INT_CHAR_UNION uuRecordWriteProgram_code;
AP_COMMDATA_EXT TYPE_LONG_INT_CHAR_UNION uuRecordWriteProgram_user;





#define Comm_Status_START 0         // wait to rec
#define Comm_Status_REC 1           // in rec status
#define Comm_Status_SEND 2          // in send status
#define Comm_Status_ERR 3           // is in err 
#define Comm_Status_STARTSEND 4


#define Comm_Addr_START 0
#define Comm_Addr_ME 1
#define Comm_Addr_BroadCast 2 
#define Comm_Addr_Supper 3
#define Comm_Addr_AutoAddr 4

#define CONST_TIMER_CHANGE_BOUD_MS 50
#define TIME_MAX_COMM_R_IR0 30 
#define TIME_MAX_COMM_R_4850 30 

#define CONST_TIMER_SEND_DELAY 3


#define CONST_COMM_ERR_MAX_TIMES 0x05

AP_COMMDATA_EXT uchar cuPassWordErrTime[10];














AP_COMMDATA_EXT uchar WriteTimeStand(uchar *ucTime);





AP_COMMDATA_EXT uchar GetCommDataFromComm(void);

AP_COMMDATA_EXT void  SendDataToComm(uchar ucLen);

AP_COMMDATA_EXT void Comm_SendData( void );

AP_COMMDATA_EXT void WriteIRBuffer(uchar p);

AP_COMMDATA_EXT void CheckPassword(uchar *PT_point);

AP_COMMDATA_EXT void CommCheckAddress( void );

AP_COMMDATA_EXT uchar ReadDL64507_11_00_kWhData(ulong ulCode_in,uchar *ucpDataout);

AP_COMMDATA_EXT uchar ReadHL645KZ_FE00_Data(void);

AP_COMMDATA_EXT uchar WriteHL645KZ_FE00_Data(void);

AP_COMMDATA_EXT uchar ReadDL64507_11_Data(ulong ulCode_in,uchar *ucpDataout);

AP_COMMDATA_EXT void ExplainProtocol(uchar  p);

AP_COMMDATA_EXT void DecodeProtocol(uchar uctChannelsId);

AP_COMMDATA_EXT void CommMode(void);

AP_COMMDATA_EXT uchar ReadHL645ADE7758_BE02_Data(void);
AP_COMMDATA_EXT uchar WriteHL645ADE7758_BE02_Data(void);




#endif

