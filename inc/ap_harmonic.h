
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
	long iawv;		//A�����˲ʱֵ
	long ibwv;		//B�����˲ʱֵ
	long icwv;		//C�����˲ʱֵ
	long inwv;		//���ߵ���˲ʱֵ
	long vawv;		//A����ѹ˲ʱֵ
	long vbwv;		//B����ѹ˲ʱֵ
	long vcwv;		//C����ѹ˲ʱֵ
}acs_harmonic_waveform;

typedef struct 
{
	unsigned long current_rms[3];	//г��������Чֵ,��Ա0��1��2�ֱ����A��B��C��
	unsigned long voltage_rms[3];	//г����ѹ��Чֵ,��Ա0��1��2�ֱ����A��B��C��
	unsigned short int current_per[3];	//г������������(�ٷֱ�). ��Ա0��1��2�ֱ����A��B��C��
	unsigned short int voltage_per[3];	//г����ѹ������(�ٷֱ�). ��Ա0��1��2�ֱ����A��B��C��
}harmonic_data_st;
typedef struct 
{
	unsigned char max_order;			// ���г������
	harmonic_data_st harmonic_data_all;			// ��������ĸ���г����
	harmonic_data_st harmonic_data_order[MAXHARMONICTIME];	// ��Ա0��30�� ���δ��1�ε�31��г��������
}harmonic_data_list_st;

typedef int (*PFUNCHARMONIC_FN)(acs_harmonic_waveform *, harmonic_data_list_st *);
typedef struct{
	unsigned char max_order;	
	//����г�����ݻص�����
	//p_waveform: �ɼ����Ĳ�������
	//p_harmonic_data_list�� �������ɵ�г������
	PFUNCHARMONIC_FN   calc_harmonic_callback;
}harmonic_para_st;
*/
AP_HARMONIC_EXT void HarmonicInit(void);
AP_HARMONIC_EXT void HarmonicIdle(void);
AP_HARMONIC_EXT void HarmonicMode(void);


#endif














