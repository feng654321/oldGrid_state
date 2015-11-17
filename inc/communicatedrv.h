#ifndef COMMUNICATEDRV_H
    #define COMMUNICATEDRV_H

#ifdef  __COMMUNICATEDRV_C__
    #define COMMUNICATEDRV_EXT
#else
    #define COMMUNICATEDRV_EXT extern
#endif


#include "datatype.h"

//物理通道号抽象
#define UART_MAX_CHANNEL        3
#define UART0_CHANNEL           0       //UART5
#define UART1_CHANNEL           1       //USART3
#define UART2_CHANNEL           2       //UART4

//
#define SOURCE_IR               UART2_CHANNEL
#define SOURCE_485              UART0_CHANNEL 
#define SOURCE_485_2            UART1_CHANNEL 
#define WIRELESS_MODULE_COMMNO  UART1_CHANNEL
#define CARRIER_MODULE_COMMNO   UART1_CHANNEL
#if(CONFIG_METER_NO2COMM_MODE_RS485==CONFIG_METER_NO2COMM_MODE)
#define SOURCE_COMM_SECOND      SOURCE_485_2   
#elif(CONFIG_METER_NO2COMM_MODE_PLC==CONFIG_METER_NO2COMM_MODE)
#define SOURCE_COMM_SECOND      CARRIER_MODULE_COMMNO   
#elif(CONFIG_METER_NO2COMM_MODE_WIRELESS==CONFIG_METER_NO2COMM_MODE)
#define SOURCE_COMM_SECOND      WIRELESS_MODULE_COMMNO   
#endif

#define SOURCE_VIRTUAL          4       //软件虚拟串口，用于集中器显示 

#define UART_MAX_BUFF           (200+10)


#define BAUDRATE_300    0
#define BAUDRATE_600    1
#define BAUDRATE_1200   2
#define BAUDRATE_2400   3
#define BAUDRATE_4800   4
#define BAUDRATE_9600   5
#define BAUDRATE_19200  6
#define BAUDRATE_38400  7
#define BAUDRATE_56000  8
#define BAUDRATE_57600  9

#define DATALENS_6BIT   0
#define DATALENS_7BIT   1
#define DATALENS_8BIT   2
#define DATALENS_9BIT   3

#define STOPBIT_1   0
#define STOPBIT_2   1

#define NO_CHECK    0
#define CHECK_ODD   1
#define CHECK_EVEN  2

#define UART_RT_SUCC        0
#define UART_RT_ERR         1   //The NO of the UART is wrong.
#define UART_RT_NO_REC      2   

typedef  struct
{  
    uchar baudRate:5;
    uchar datab:2;         // 字长度，6/7/8/9
    uchar stopb:1;         // 停止位，1/2
    uchar parity:2;     // 奇偶校验位，0为无校验，1奇数校验，2为偶数校验
    uchar hold:6;
}UARTMODE;  

#define UART_LENS_TYPE  uchar
#define UART_LENS_BYTES 1
typedef  struct
{
    UART_LENS_TYPE phead;
    UART_LENS_TYPE ptail;
    UART_LENS_TYPE pActHead;
    UART_LENS_TYPE pcur;
    uchar buff[UART_MAX_BUFF];
}STR_UART_BUFF;

#if(UART_MAX_BUFF == UART_LENS_BYTES*256)   
//It will roll back automaticlly
#define UART_BUFF_PTR_ROLLBACK_CHK(ptr)    
#else
#define UART_BUFF_PTR_ROLLBACK_CHK(ptr)    {if((ptr) >= UART_MAX_BUFF) (ptr) = 0;}
#endif

#define WORKING_STATUS_NO_WORKING       0
#define WORKING_STATUS_SIMPLEX_REC      1
#define WORKING_STATUS_SIMPLEX_SEND     2
#define WORKING_STATUS_DOUBLE           3
typedef  struct
{
    uchar uartWorkingStatus:3;
    uchar uartsendStatus:1;
    uchar hold:4;
}STR_UART_SEND_STATUS;

typedef  struct
{
    uchar baudRate:4;
    uchar errStatus:1; 
    uchar idleTime:3;
}STR_UART_STATUS;
#define MAX_IDLE_TIME   5

COMMUNICATEDRV_EXT STR_UART_STATUS UARTStatus[UART_MAX_CHANNEL];//add by sun 10.10.21
COMMUNICATEDRV_EXT STR_UART_BUFF UARTBuf[UART_MAX_CHANNEL];
COMMUNICATEDRV_EXT STR_UART_SEND_STATUS sendStatus[UART_MAX_CHANNEL];

COMMUNICATEDRV_EXT const UARTMODE UARTDefaultPara[UART_MAX_CHANNEL] ;

COMMUNICATEDRV_EXT uchar InitUART(uchar Channel);
COMMUNICATEDRV_EXT uchar SetUART(uchar Channel,UARTMODE* Para);
COMMUNICATEDRV_EXT uchar UARTReceiveSwitch(uchar Channel,uchar switchEn);
COMMUNICATEDRV_EXT uchar UARTSendSwitch(uchar Channel,uchar switchEn);
COMMUNICATEDRV_EXT void UARTSendOver(uchar Channel);

COMMUNICATEDRV_EXT uchar UARTSend(uchar Channel,uchar* buf,uchar lens,uchar sendDelay);
COMMUNICATEDRV_EXT uchar GetSendStatus(uchar Channel);
COMMUNICATEDRV_EXT uchar GetRecStatus(uchar Channel);
COMMUNICATEDRV_EXT uchar GetCurChkWord(uchar Channel,uchar* word);
COMMUNICATEDRV_EXT uchar RollbackCurChkWord(uchar Channel, UART_LENS_TYPE backnum);
COMMUNICATEDRV_EXT uchar MoveActiveFrameToFirst(uchar Channel);
COMMUNICATEDRV_EXT uchar* GetUardActiveBuff(uchar Channel);
COMMUNICATEDRV_EXT void ActiceHeadWordChecked(uchar Channel);
COMMUNICATEDRV_EXT UART_LENS_TYPE ActiceRecLen(uchar Channel);
    
    
#endif




