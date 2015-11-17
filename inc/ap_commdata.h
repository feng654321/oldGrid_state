
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
    // --> 对应通道中的波特率参数  -->
    uchar boud;
    // --> 如果需要临时更改波特率的时候使用  -->
    uchar time_boud_500;
    // --> 当前这个通道的状态  -->
    uchar status;
    // --> 当前接受到的数据判断地址的状态  -->
    uchar status_Addr_info;
    // --> 当前接受状态的持续时间  -->
    uchar comm_rec_time;
    // -->  当前发送状态的持续时间 -->
    uchar comm_send_time;
    // --> 当前通道发送延时的时间 -->
    uchar comm_send_delay;
    // -->  当前数据接收或者发送的的长度和对应指针 -->
    COMM_DATA_UNION DataPoint;
    // -->  当前通道中接收或者发送中的数据内容 -->
    COMM_BUF DataBuffer;
}UN_COMM_BUF_PARAM;


typedef union
{
    struct
    {
        // -->  其他错误-->
        uchar bOtherError : 1;
        // -->  无请求数据-->
        uchar bNodataError : 1;
        // -->  密码错误或者未授权-->
        uchar bPwdError : 1;
        // -->  通讯速率不能更改-->
        uchar bBoudError : 1;
        // -->  年时区数超-->
        uchar bSeasonError : 1;
        // -->  日时段数超-->
        uchar bDayperiodError : 1;
        // -->  费率数超-->
        uchar bRateError : 1;
        // -->  保留-->
        // -->// 湖南要求
        uchar bRelayError : 1;  
    }Bits;
    uchar ucData;
}UN_COMMSTATUS_ERRFLAG_PARAM;
typedef union
{
    struct
    {
        // -->  其他错误-->
        uchar b_other_error : 1;
        // -->  无请求数据-->
        uchar b_nodata_error : 1;
        // -->  密码错误或者未授权-->
        uchar b_pwd_error : 1;
        // -->  通讯速率不能更改-->
        uchar b_boud_error : 1;
        // -->  年时区数超-->
        uchar b_season_error : 1;
        // -->  日时段数超-->
        uchar b_dayperiod_error : 1;
        // -->  费率数超-->
        uchar b_rate_error : 1;
        // -->  保留-->
        uchar b_relay_error : 1;    // 湖南要求
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

