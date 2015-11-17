
#ifndef AP_HARMONIC_H
    #define AP_HARMONIC_H
#ifdef  AP_HARMONIC_GLOBALS
    #define AP_HARMONIC_EXT
#else
    #define AP_HARMONIC_EXT extern
#endif  

#include "pax_driver.h"

int    harmonic_module_run_flg;
/*
typedef struct
{
	long iawv;		//A相电流瞬时值
	long ibwv;		//B相电流瞬时值
	long icwv;		//C相电流瞬时值
	long inwv;		//中线电流瞬时值
	long vawv;		//A相电电压瞬时值
	long vbwv;		//B相电电压瞬时值
	long vcwv;		//C相电电压瞬时值
}acs_harmonic_waveform;

typedef struct 
{
	unsigned long current_rms[3];	//谐波电流有效值,成员0，1，2分别代表A，B，C相
	unsigned long voltage_rms[3];	//谐波电压有效值,成员0，1，2分别代表A，B，C相
	unsigned short int current_per[3];	//谐波电流含有率(百分比). 成员0，1，2分别代表A，B，C相
	unsigned short int voltage_per[3];	//谐波电压含有率(百分比). 成员0，1，2分别代表A，B，C相
}harmonic_data_st;
typedef struct 
{
	unsigned char max_order;			// 最大谐波次数
	harmonic_data_st harmonic_data_all;			// 参与测量的各相谐波总
	harmonic_data_st harmonic_data_order[MAXHARMONICTIME];	// 成员0～30， 依次存放1次到31次谐波的数据
}harmonic_data_list_st;

typedef int (*PFUNCHARMONIC_FN)(acs_harmonic_waveform *, harmonic_data_list_st *);
typedef struct{
	unsigned char max_order;	
	//计算谐波数据回调函数
	//p_waveform: 采集到的波形数据
	//p_harmonic_data_list： 计算生成的谐波数据
	PFUNCHARMONIC_FN   calc_harmonic_callback;
}harmonic_para_st;
*/
AP_HARMONIC_EXT void HarmonicInit(void);
AP_HARMONIC_EXT void HarmonicIdle(void);
AP_HARMONIC_EXT void HarmonicMode(void);


#endif














