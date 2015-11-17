#ifndef __METER_MAIN_H__
#define __METER_MAIN_H__

#undef COMMON_EXT
#ifdef __METER_MAIN_C__
#define COMMON_EXT
#else
#define COMMON_EXT  extern
#endif

COMMON_EXT int g_meter_second_sem_id;
COMMON_EXT int g_meter_pid;
#endif
