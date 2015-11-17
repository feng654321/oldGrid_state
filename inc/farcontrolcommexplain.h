#ifndef FAR_CONTROL_COMM_EXPLAIN_H
    #define FAR_CONTROL_COMM_EXPLAIN_H
#ifdef  FAR_CONTROL_COMM_EXPLAIN_GLOBALS
    #define FAR_CONTROL_COMM_EXPLAIN_EXT
#else
    #define FAR_CONTROL_COMM_EXPLAIN_EXT extern
#endif

#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
#define PASS_WORD_98                0x98
#define PASS_WORD_99                0x99

#define COMM_NO_ERROR               0x00
#define COMM_OTHER_ERROR            0x01    //∆‰À˚¥ÌŒÛ
#define COMM_PASSWORD_ERROR         0x04    //√‹¬Î¥Ì

FAR_CONTROL_COMM_EXPLAIN_EXT void ForControl07(STR_COMMUNICATE_BUFF* commReceiveData);
FAR_CONTROL_COMM_EXPLAIN_EXT u16 SetCommFarControlSendData(STR_FARCONTROL_OUTPUTDATA* outData);
FAR_CONTROL_COMM_EXPLAIN_EXT void FarCtlMange(STR_COMMUNICATE_BUFF* commReceiveData,uchar MangeType);



FAR_CONTROL_COMM_EXPLAIN_EXT  void CommFarCtl(void);
FAR_CONTROL_COMM_EXPLAIN_EXT  void RelayControl(STR_COMMUNICATE_BUFF* commReceiveData);

FAR_CONTROL_COMM_EXPLAIN_EXT  uchar DrawDataByID(UN_LONG ID,ulong handlerID,uchar* src,uchar lens,STR_COMMUNICATA_FLAG* commFlag);
#endif

#endif
