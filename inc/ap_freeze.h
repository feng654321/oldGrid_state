
#ifndef AP_FREEZE_H
    #define AP_FREEZE_H
#ifdef  AP_FREEZE_GLOBALS
    #define AP_FREEZE_EXT
#else
    #define AP_FREEZE_EXT extern
#endif  

//����������ʱ�����ݳ���
#define BYTES_FREEZE_TIME_TOTAL    (5) 
//���������е������ݳ���
#define BYTES_FREEZE_KWH_TOTAL     ((DLT_DAY_PIECE_MAX+1)*DLT_FREEZE_KWH_TYPE_NUM*BYTES_PER_PT_KWH)
//�����������������ݳ���
#define BYTES_FREEZE_DEMAND_TOTAL  ((DLT_DAY_PIECE_MAX+1)*DLT_FREEZE_DEMAND_TYPE_NUM*BYTES_PER_DEMAND)


AP_FREEZE_EXT void FreezeInit(void);

AP_FREEZE_EXT void FreezeDataWrite(ulong ulDataAddr);

AP_FREEZE_EXT uchar  FreezeRecord(uchar ucTypeName);

AP_FREEZE_EXT uchar FreezeMode(void);



























#endif  



