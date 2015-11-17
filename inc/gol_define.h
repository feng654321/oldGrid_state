#ifndef __GOL_DEFINE_H__
#define __GOL_DEFINE_H__

//存储器类型
#define GAL_RAM             0
#define GAL_FM1             1
#define GAL_FM2             2
#define GAL_PWD             (GAL_FM2)       //为了跟老表兼容
#define GAL_COEFDATA        4
#define GAL_EPLOCK          5
#define GAL_DATABAK         6
#define GAL_EEPROM2         7
#define GAL_CFG             8
#define GAL_IN
#define GAL_FLASH1          0x10
#define GAL_FLASH2          0x12
#define GAL_FLASH1ADD       0x11
#define GAL_FLASH2ADD       0x13
#define GAL_ADE7758         0x20
#define GAL_TWOTABLE        0x21
#define GAL_POWERBUFFER     0x22
#define GAL_DEMANDBUFFER    0x23
#define GAL_DEMANDMINUTEBUFFER  0x24
#define GAL_RECORD          0x30
#define GAL_RAWRAM          0x88
#define GAL_BKP             0x09
#define GAL_CRAM            0xA0
#define GAL_CFLASH          0xA1
#define GAL_MEDIA_ERR       0xFF
#define GAL_KWH             0xF1

//系统电源状态
#define SYS_STATE_POWERON   0
#define SYS_STATE_POWEROFF  1
#define SYS_STATE_WAKEUP    2
#define SYS_STATE_GETIR     3
#define SYS_STATE_ALLLOSSV  4


#if(CONFIG_METER_FACTORY_MODE==CONFIG_METER_FACTORY_MODE_ENABLE)
//--AA如果是生产程序，则软件版本号自动为0000 AA--
#define CON_PRO_METER_SET_VER_STR       "0000"  
#else
// ----25系列FLASH更新之后的程序,程序版本号从1000开始-->
#define CON_PRO_METER_SET_VER_STR       "3001"  
#endif

#define CON_PRO_METER_SET_DATE_STR      "110726"          // YYMMDD
#endif

