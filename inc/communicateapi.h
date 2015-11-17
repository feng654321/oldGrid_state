#ifndef COMMUNICATEAPI_H
    #define COMMUNICATEAPI_H
    
#ifdef  COMMUNICATEAPI_GLOBALS
    #define COMMUNICATEAPI_EXT
#else
    #define COMMUNICATEAPI_EXT extern
#endif  





#define REC_MAX_LINk_MUN    4
#define SEND_MAX_LINk_MUN   1


#define FRAME_HEAD_WORD     0x68
#define FRAME_END_WORD      0x16
#define FRAME_ADD_WORD      0x33
#define REC_WATE_TIME       500 //ms
#define SEND_WAIT_TIME      20  //ms

//#define UART_REC_FRAME_LEN_MAX	 200

#define UART_REC_DATA_LEN_MAX   (220)
#define UART_REC_FRAME_LEN_MAX  (UART_REC_DATA_LEN_MAX+10)
#define UART_SEND_DATA_LEN_MAX  (200)
typedef struct 
{
    uchar source:3; 
    uchar deformityFrame:1;
    uchar recStatus:4;
    uchar sendDelay;    //ms
}STR_COMMUNICATA_FLAG;

typedef  struct
{
    uchar buff[UART_REC_FRAME_LEN_MAX+100];//缓冲区加长，给发送填入数据时用的
    UART_LENS_TYPE lens;			//接收数据的长度
    UART_LENS_TYPE prtcllens;		//协议长度
    STR_COMMUNICATA_FLAG communicateFlag;
}STR_COMMUNICATE_BUFF;

typedef  struct
{
    uchar phead;
    uchar ptail;
    STR_COMMUNICATE_BUFF recBuf[REC_MAX_LINk_MUN];
}STR_REC_LINK;


typedef  struct
{
    //uchar phead;
    //uchar ptail;
    uchar sendbufhave;
    STR_COMMUNICATE_BUFF sendBuf[SEND_MAX_LINk_MUN];
}STR_SEND_LINK;

#define NO_SEND         0
#define SENDING         1
#define SEND_OVER       2 

enum
{
    UART_API_NO_REC,
    UART_API_HEAD1,
    UART_API_ADDR,
    UART_API_HEAD2,
    UART_API_CMD,
    UART_API_LEN,
    UART_API_DATA,
    UART_API_CS,
    UART_API_FULL_FRAME,
    UART_API_TIMEOVER,
    UART_API_IDLE,
};

typedef struct 
{   UART_LENS_TYPE fdatalen;
    uchar recStatus:4; 
    uchar sendStatus:3; //0:no send 1:sending 2:end send
    uchar hold:1;
}STR_UART_CONTROL;

typedef struct 
{   
    UARTMODE uartPara;  
    uchar controlData;  ////0,不更改，1，发送前更改，2，发送后更改
}STR_UART_PARA_CHANGE_CONTROL;

COMMUNICATEAPI_EXT STR_COMMUNICATE_BUFF  CommExpReceiveDataBuffer;

COMMUNICATEAPI_EXT void judgeFrameStructure(uchar chunnel) ;

COMMUNICATEAPI_EXT void InitCommunicate(uchar port_no);
COMMUNICATEAPI_EXT void IdleCommunicate(void);
COMMUNICATEAPI_EXT uchar SendCommunicateData(uchar* src,u16 lens,STR_COMMUNICATA_FLAG* sendFlag,STR_UART_PARA_CHANGE_CONTROL* data);
#endif



