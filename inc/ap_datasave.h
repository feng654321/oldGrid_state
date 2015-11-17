#ifndef __AP_DATASAVE_H__
#define __AP_DATASAVE_H__

#undef COMMON_EXT
#ifdef __AP_DATASAVE_C__
#define COMMON_EXT
#else
#define COMMON_EXT  extern
#endif

// 定时保存数据全局变量
COMMON_EXT UN_U8_PARAM g_SaveDataFlag;
// 每分钟保存标识
COMMON_EXT uchar SavePowerPerMin;

#define FLG_SAVE_EC g_SaveDataFlag.Bits.b0
#define FLG_SAVE_MD g_SaveDataFlag.Bits.b1
#define FLG_SAVE_EVENT g_SaveDataFlag.Bits.b2
#define FLG_SAVE_LOAD g_SaveDataFlag.Bits.b3

#define KWH_SAVED_MODE_INIT         0xa5    //上电初始化,此时上电后电量未做分钟保存
#define KWH_SAVED_MODE_MIN_SAVED    0x5a    //上电后电量已做做分钟保存
COMMON_EXT uchar g_KwhSavedMode;     


COMMON_EXT void GetLastSaveTime(STR_CALENDAR* usTime);

COMMON_EXT void SaveDataInit(void);

COMMON_EXT void LoadEventAccTime(void);

COMMON_EXT void SaveEventAccTime(void);

COMMON_EXT uchar SaveDataMode(void);

#if(GAL_YES == BKP_VIRTUAL_FEATURE)
AP_DATASTORAGE_EXT void VirtualBPKRegSave(ulong ulStartAddr);
AP_DATASTORAGE_EXT void VirtualBPKRegResume(void);
#endif

#endif

