//============================================================================
//  File Name: vt_platform.h
//
//  Copyright PAX Hangzhou 2011.  All rights reserved.
//
//  Description:
//      主要是表型里一些驱动平台相关的接口模拟的定义引用
//
//  Modification History:
//      $Id:  Exp $
//      $Log: $
//      Revision 1.0 Create by Taozhiguo in 2011.04.28
//============================================================================
#ifndef __VT_PLATFORM_H__
#define __VT_PLATFORM_H__

#undef COMMON_EXT
#ifdef __VT_PLATFORM_C__
#define COMMON_EXT
#else
#define COMMON_EXT  extern
#endif
#define STR_LINK2(A,B)              (A B)

//#define MTRACE(fmt, args...)        { MeterTrace(0, fmt, ## args); }
//#ifdef DEBUG#define my_printf(...) fprintf(stderr, __VA_ARGS__)#else#define my_printf(...) printf(__VA_ARGS__)#endif
#if(CONFIG_METER_SW_DEBUG_MODE == GAL_YES)
#define MTRACE(fmt, args...)        printf(fmt, ## args)
#define LOGTRACE(fmt, args...)      {MTRACE(fmt, ## args); log_printf_level(LOG_LEVEL_INFO, fmt, ## args);}
#define ErrPrint(fmt, args...)      { fprintf(stderr, fmt, ## args); log_printf_level(LOG_LEVEL_ERR, fmt, ## args);}
#define ERRTRACE(fmt, args...)      { fprintf(stderr, STR_LINK2("%s-%d ", fmt), __FUNCTION__, __LINE__, ## args); log_printf_level(LOG_LEVEL_ERR, STR_LINK2("%s-%d ", fmt), __FUNCTION__, __LINE__, ## args);}
#define FUNCTRACE()                 { fprintf(stderr, "%d %s-%d\n", ulRunSecTime, __FUNCTION__, __LINE__); log_printf_level(LOG_LEVEL_DEBUG, "%s-%d\n", __FUNCTION__, __LINE__);}
#define DISPLATRACE(fmt, args...)   printf(fmt, ## args)
#else
#define MTRACE(fmt, args...)        //printf(fmt, ## args)
#define LOGTRACE(fmt, args...)      {log_printf_level(LOG_LEVEL_WARN, fmt, ## args);}
#define ErrPrint(fmt, args...)      {log_printf_level(LOG_LEVEL_ERR, fmt, ## args);}
#define ERRTRACE(fmt, args...)      { log_printf_level(LOG_LEVEL_ERR, STR_LINK2("%s-%d ", fmt), __FUNCTION__, __LINE__, ## args);}
#define FUNCTRACE()                 { log_printf_level(LOG_LEVEL_DEBUG, "%s-%d\n", __FUNCTION__, __LINE__); }
#define DISPLATRACE(fmt, args...)   //printf(fmt, ## args)
#endif
//上电判断电压
#define POWER_ON_VOLTAGE_MV          (5500)  //mv
//掉电判断电压
#define POWER_OFF_VOLTAGE_MV        (5500)  //mv 6300

#define FIRST_FLASH                 1
#define SECOND_FLASH                2
#define THIRD_FLASH                 3
#if(CONFIG_METER_FLASH_MODE_2_AT25FLASH==CONFIG_METER_FLASH_MODE)
    #define MAX_ADDR                0x00ffffff
#else
    #define MAX_ADDR                0x007fffff
#endif

#if(FILE_BUFF_ENABLE == GAL_YES)
#define FILE_BUFF_BYTES_MAX         (1024*1024*2)       //用于文件缓存的最大buff大小
#define FILE_BUFF_RECORD_MAX        (128)               //用于文件缓存的最大记录数
#define FLASH_FILE_BUFF_SECOND      (60*03)             //FLASH文件在起来后最多buf的时间秒数
typedef struct VT_RAM_FILE_BUFF
{
    u32 pOffset;
    u32 ulLen;
    u32 ulFileType;
    u8* pData;
    struct VT_RAM_FILE_BUFF* pNext;
}VT_RAM_FILE_BUFF;

COMMON_EXT VT_RAM_FILE_BUFF* pFileBufHead;
COMMON_EXT u32 FileBufSize;
COMMON_EXT u32 FileBufRecordNum;
COMMON_EXT uchar FileBufPush(u32 ulFlieType, const u8 *pData, u32 ulAddr, u32 ulLen);
COMMON_EXT uchar FileBufPop(u32 ulFlieType, u8 *pData, u32 ulAddr, u32 ulLen);
COMMON_EXT uchar FileBufSet(u32 ulFlieType, const u8 *pData, u32 ulAddr, u32 ulLen);
COMMON_EXT uchar FileBufGet(u32 ulFlieType, u8 *pData, u32 ulAddr, u32 ulLen);
COMMON_EXT uchar FileBufWriteCommit(u32 ulFlieType);

#endif

COMMON_EXT uchar IfPowerOn(void);
COMMON_EXT uchar IfPowerDown(void);
COMMON_EXT void ClearWatchDog(void);
COMMON_EXT void VtPlatformInit(void);
COMMON_EXT void VtPlatformSave(void);
COMMON_EXT u8 ReadAt24c256b(u8 *Dst, u16 Src, u16 Len);
COMMON_EXT u8 ReadBakData(u8 *Dst, u16 Src, u16 Len);
COMMON_EXT u8 ReadDataFromFlash(u8 devId,u8 *up,u32 ulAddr,u16 uiLen);
COMMON_EXT u8 WriteAt24c256b(u16 Dst, const u8 *Src, u16 Len);
COMMON_EXT u8 WriteBakData(u16 Dst, const u8 *Src, u16 Len);
COMMON_EXT u8 WriteDataToFlash(u8 devId,const u8 *up,u32 ulAddr,u16 uiLen);
COMMON_EXT u8 EraseFullFlash(u8 devId);
COMMON_EXT void MeterFileInit(const string *FileName, ulong FileLen);



#define isFlashBusy         (GAL_NO)    //(GAL_YES == GetFlashStatus())
#define isFlashFree         (GAL_YES)   //(GAL_NO  == GetFlashStatus())

#endif

