
#ifdef  PROT_GLOBALS
    #define PROT_EXT
#else
    #define PROT_EXT extern
#endif

#define CONST_CLR_KWH_ALL 0xA5 // CURRENT_AND_HISTORY
#define CONST_CLR_KWH_CURRENT 0x11 // ONLY CURRENT

#define CONST_CLR_EVENT_ALL 0x5A // ALL EVENT DATA 
#define CONST_CLR_EVENT_EXCEPT_PROGRAMRECORD 0x22

typedef struct
{
    unsigned int DI;
            unsigned int MemoryBlock;
            unsigned int MemoryExcursion;
    unsigned char Length;
    unsigned char Parameter;
    unsigned char *Rampt;
}COMM_Format_TAB_DL64597;
    
typedef struct
{
    unsigned long ulID;
    unsigned int MemoryBlock;
    unsigned int MemoryExcursion;
    unsigned char Length;
    unsigned char Parameter;
    unsigned char *Rampt;
}COMM_Format_TAB_DL64507;


#define CONST_COMM645_07_LENGTH 61
typedef struct
{
    unsigned char DI0;
    unsigned char DI1;
    unsigned char DI2;
    unsigned char DI3;
    
            unsigned int MemoryBlock;
            unsigned int MemoryExcursion;
    
    unsigned char Length;
    unsigned char Parameter;
    
    unsigned char *Rampt;
}COMM_645_07Format;




typedef struct
{
    unsigned char DataTotal;
    unsigned int DataAddress;
    unsigned int PtAddress;
    unsigned char DataLength;
}HIS_Format;

typedef union
{
    struct
    {
        // -->  其他错误-->
        unsigned char b_other_error : 1;
        // -->  无请求数据-->
        unsigned char b_nodata_error : 1;
        // -->  密码错误或者未授权-->
        unsigned char b_pwd_error : 1;
        // -->  通讯速率不能更改-->
        unsigned char b_boud_error : 1;
        // -->  年时区数超-->
        unsigned char b_season_error : 1;
        // -->  日时段数超-->
        unsigned char b_dayperiod_error : 1;
        // -->  费率数超-->
        unsigned char b_rate_error : 1;
        // -->  保留-->
        unsigned char b_relay_error : 1;    // 湖南要求
    }bit;
    unsigned char ucErrorFlag;
}ERR_FLAG;


#define CONST_COMM_DATA_MAX_LEN (132+4)
#define CONST_COMM_OTHERDATA_LEN  12
#define CONST_COMM_BUFFER_MAX_LEN (CONST_COMM_DATA_MAX_LEN+CONST_COMM_OTHERDATA_LEN+1)

typedef union
{
    struct
        {
        unsigned char ucD0;
        unsigned char ucD1;
        unsigned char ucD2;
        unsigned char ucD3;
        }uCharMode;
    struct
        {
        unsigned int uiLow;
        unsigned int uiHigh;
        }uIntMode;
    unsigned long uLongMode;
}TYPE_LONG_INT_CHAR_UNION;





typedef union
{
    unsigned char ucArray_Comm[CONST_COMM_BUFFER_MAX_LEN];
    struct
    {
        unsigned char ucFirstHead;
        unsigned char ucAddress[6];
        unsigned char ucSecondHead;
        unsigned char ucControl;
        unsigned char ucLength;
        union
        {
            unsigned char ucArray_Data[CONST_COMM_DATA_MAX_LEN];
            struct
                {
                unsigned char ucDI0;
                unsigned char ucDI1;
                }bytes;
            unsigned int uICode97;
            struct
                {
                unsigned char uc07DI0;
                unsigned char uc07DI1;
                unsigned char uc07DI2;
                unsigned char uc07DI3;
                }DL645_07;
            struct
                {
                unsigned int uiCodeLow;
                unsigned int uiCodeHigh;
                }DL645_07INT;
            unsigned long uLCode07;
            
            struct
                {
                unsigned long ulCode07;
                unsigned long ulPassWord;
                unsigned long ulUser;
                }Type_Control14;
            struct
                {
                unsigned long ulPassWord;
                unsigned long ulUser;
                }Type_Control19;
            struct
                {
                unsigned long ulPassWord;
                unsigned long ulUser;
                }Type_Control1A;
            struct
                {
                unsigned long ulPassWord;
                unsigned long ulUser;
                }Type_Control1B;
            struct
                {
                unsigned long ulPassWord;
                unsigned long ulUser;
                }Type_Control1C;
            struct 
                {
                unsigned int uicode97;
                unsigned long ulPasswd;
                unsigned int ulConRandomData;
                unsigned int ulConRelayId;
                }Type_JILIN_RELAY;
            
            }ucDataPart;
        unsigned char ucChksum;
        unsigned char ucEnding;
//      unsigned int ucDI;
    }DL645Data; 
}COMM_BUF;

typedef union
{
    struct
    {
        unsigned char ucTransDataPoint;
        unsigned char ucTransDataLength;
    }Tbytes;
    struct
    {
        unsigned char ucReceiveDataPoint;
        unsigned char ucReceiveDataLength;
    }Rbytes;
}COMM_DATA_UNION;


typedef struct
{
    // --> 对应通道中的波特率参数  -->
    unsigned char boud;
    // --> 如果需要临时更改波特率的时候使用  -->
    unsigned char time_boud_500;
    // --> 当前这个通道的状态  -->
    unsigned char status;
    // --> 当前接受到的数据判断地址的状态  -->
    unsigned char status_Addr_info;
    // --> 当前接受状态的持续时间  -->
    unsigned char comm_rec_time;
    // -->  当前发送状态的持续时间 -->
    unsigned char comm_send_time;
    // --> 当前通道发送延时的时间 -->
    unsigned char comm_send_delay;
    // -->  当前数据接收或者发送的的长度和对应指针 -->
    COMM_DATA_UNION DataPoint;
    // -->  当前通道中接收或者发送中的数据内容 -->
    COMM_BUF DataBuffer;
}Comm_Status_Type;

// Channels Define
#define ConstCommChannels_Total 0x02
#define Comm_Rs485 0x00
#define Comm_IR 0x01

PROT_EXT Comm_Status_Type CommSys[ConstCommChannels_Total];
PROT_EXT Comm_Status_Type *CommDataPoint;
PROT_EXT unsigned char  ucCommChannelsId;





#define CONST_GAP 100
#define CONST_TR_GAP 200


#define CONST_GUIYU_JILIN 0xAC
#define CONST_GUIYU_TYPE  CONST_GUIYU_JILIN


// #define CONST_CONTROL_LENGTH 0x07
#define CONST_CONTROL_LENGTH 0x0e

//#define CONST_PRICE_NUM_0         0
//#define CONST_PRICE_NUM_1         1
//#define CONST_PRICE_NUM_2         2
//#define CONST_PRICE_NUM_3         3
//#define CONST_PRICE_NUM_4         4

//#define CONST_PRICE_NUM       CONST_PRICE_NUM_0
//#define CONST_PRICE_DATALEN   (4*(CONST_PRICE_NUM+1))
//#define CONST_KWH_HAVE 1
//#define CONST_KWH_NOHAVE 0
//#define CONST_KWH_F CONST_KWH_HAVE
//#define CONST_KWH_R CONST_KWH_HAVE


#define CONST_COMM64597_LENGTH_COUNT (96+6+4+CONST_PRICE_NUM*14)


#if (REGION_TYPE==JI_LIN)
    #define CONST_COMM64597_LENGTH (CONST_COMM64597_LENGTH_COUNT+28)
#else
    #define CONST_COMM64597_LENGTH (78+CONST_PRICE_NUM*8)
#endif



#define CONST_HISTORY_LENGTH 9
#define CONST_COMM64507_LENGTH (25)

#define CONST_COMM_ERR_MAX_TIMES 0x05

typedef union{
    struct{
        char    ReadMeter:1;
        char    b1:1;
        char    BATVoltage:1;
        char    b3:1;   
        char    EnergyWay:1;
        char    b5:1;
        char    RelayState:1;
        char    BreakPowerAlarm:1;
    } bit;
    char    byte;
} R_State;

PROT_EXT R_State Run_State;
PROT_EXT unsigned long relayOpenSumTime;
//PROT_EXT unsigned int openRelayAlarmTime;


PROT_EXT unsigned char baudStateIR;
PROT_EXT unsigned char baudStateRS485;

PROT_EXT unsigned char Factory_Flag;

// PROT_EXT unsigned char ucGap[2];
// PROT_EXT unsigned char ucSbuf[2];
// PROT_EXT COMM_DATA_UNION IR_COMM_DATA_UNION[2];
// PROT_EXT COM_STRUCT COM_STRUCT1;
// PROT_EXT COM_FLAG Protocol[2];
PROT_EXT unsigned int ProgramTime;
PROT_EXT unsigned int ProgramTimeLength;
PROT_EXT unsigned char cuPassWordErrTime[2];
PROT_EXT unsigned char comLedTurnOnTime;

PROT_EXT void DecodeProtocol(uchar p);
PROT_EXT void TransLateData0(void);
PROT_EXT void TransLateData1(void);
PROT_EXT void InitializeUART(void);
PROT_EXT void CheckByteGap(void);
PROT_EXT void ResetCommConfig(unsigned char ucCh);
PROT_EXT void SaveRelayCloseBill(void);
PROT_EXT void SaveRelayOpenBill(void);
PROT_EXT void ExitBreakPowerAlarm(void);

PROT_EXT unsigned char ucRecordWriteProgram_point;
PROT_EXT TYPE_LONG_INT_CHAR_UNION uuRecordWriteProgram_code;
PROT_EXT TYPE_LONG_INT_CHAR_UNION uuRecordWriteProgram_user;





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



#define CONST_BaudState_300 0
#define CONST_BaudState_600 1
#define CONST_BaudState_1200 2
#define CONST_BaudState_2400 3
#define CONST_BaudState_4800 4
#define CONST_BaudState_9600 5
#define CONST_BaudState_19200 6
#define CONST_BaudState_Rs485_Default CONST_BaudState_1200
#define CONST_BaudState_IR0_Default CONST_BaudState_1200

typedef struct
{
    unsigned char   clockSource;
    unsigned char   baudNumber;
} BAUT_STRUCT;
#ifdef  PROT_GLOBALS
    const near BAUT_STRUCT UartBautTab[7] = 
    {
        0x01,0xCC,      //300 //0
        0x01,0x66,      //600 //1
        0x01,0x33,      //1200 //2
        0x01,0x19,      //2400 //3
        0x01,0x0C,      //4800 //4
        0x00,0x33,      //9600 //5
        0x00,0x19       //19200 //6
    };
#else
    extern const near BAUT_STRUCT UartBautTab[] ;
#endif



 


typedef union  
{
    struct 
    {
    unsigned char b0 : 1 ;
    unsigned char b1 : 1 ;
    unsigned char b2 : 1 ;
    unsigned char b3 : 1 ;
    unsigned char b4 : 1 ;
    unsigned char b5 : 1 ;
    unsigned char b6 : 1 ;
    unsigned char b7 : 1 ;
    }bit_dis;
    unsigned char byte ;
}byte_dis;

PROT_EXT byte_dis COMM_USE0 ;
PROT_EXT byte_dis METER_STATUS_64507 [16];



#define RFLAG_SEND_START_IR0 COMM_USE0.bit_dis.b0
#define RFLAG_SEND_START_4850 COMM_USE0.bit_dis.b2 

//PROT_EXT void ClearAllEnergy(void);
PROT_EXT void ClearEventRecord(unsigned char clearType );
PROT_EXT void ClearEnergy(unsigned char clearType);
PROT_EXT void SaveRelayOpenBill(void);
PROT_EXT void SaveRelayCloseBill(void);

