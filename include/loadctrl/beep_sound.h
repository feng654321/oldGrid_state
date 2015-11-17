#ifndef _BEEP_SOUND_H_

#define _BEEP_SOUND_H_

#define		CON_BEEP_TOTAL_URGEFEE			120				//催费告警，单位0.5秒
#define		CON_BEEP_DELAY_URGEFEE			0
#define		CON_BEEP_LAST_URGEFEE			8
#define		CON_BEEP_INTER_URGEFEE			15

#define		CON_BEEP_TOTAL_MONENER			124				//月电控告警，单位0.5秒
#define		CON_BEEP_DELAY_MONENER			4
#define		CON_BEEP_LAST_MONENER			8
#define		CON_BEEP_INTER_MONENER			15

#define		CON_BEEP_TOTAL_BUYENER			280				//购电控告警，单位0.5秒
#define		CON_BEEP_DELAY_BUYENER			4
#define		CON_BEEP_LAST_BUYENER			8
#define		CON_BEEP_INTER_BUYENER			112

#define		CON_BEEP_TOTAL_EXECTRL			30				//执行控制，单位0.5秒
#define		CON_BEEP_DELAY_EXECTRL			6
#define		CON_BEEP_LAST_EXECTRL			3
#define		CON_BEEP_INTER_EXECTRL			9

#define		CON_BEEP_TOTAL_PARACHG			30				//参数修改，单位0.5秒
#define		CON_BEEP_DELAY_PARACHG			6
#define		CON_BEEP_LAST_PARACHG			1
#define		CON_BEEP_INTER_PARACHG			5

#define		CON_BEEP_TOTAL_TRIPALR			60				//跳闸告警，单位0.5秒
#define		CON_BEEP_DELAY_TRIPALR			0
#define		CON_BEEP_LAST_TRIPALR			1
#define		CON_BEEP_INTER_TRIPALR			0

#define		CON_BEEP_SOUND					0x55
#define		CON_BEEP_ALL					0xAA

void Beep_Init(void);
void Beep_Timer(void);
void Beep_Start(unsigned short usTotal,unsigned short usDelay,unsigned short usLast,unsigned short usInter);
void Beep_Stop(void);
void Beep_ExternPara_Change(void);

#endif

