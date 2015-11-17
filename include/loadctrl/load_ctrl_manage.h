#ifndef _LOAD_CTRL_MANAGE_H_

#define _LOAD_CTRL_MANAGE_H_

#include <pax_driver.h>
#include <pax_db.h>

#include "load_remote.h"
#include "load_energy.h"
#include "load_power.h"
#include "beep_sound.h"

#include "../pax_ver.h"

/*************************************�������******************************************/
#ifdef CON_TER_TYPE_FK_JX
#define 	CON_SWITCHOUT_MODE		0x55			//�̵������ģʽ:0x55�������,0xaaÿ��60�����
#else
#define 	CON_SWITCHOUT_MODE		0xAA			//��բ���1�������
#endif

#define 	CON_AVALIBLE_FLAG			0x55
#define 	CON_INVALIBLE_FLAG		0xAA


#define	CON_CTRLFEE_NUM			14
#define	CON_CTRLFEETIME_NUM		48		//30����һ�Σ�48��

#define	CONSWITCHOPEN			0x55		//��
#define	CONSWITCHREADY			0x5A		//Ԥ����
#define 	CONSWITCHCLOSE			0xAA		//��
#define 	CONSWITCHINVALID			0xBB		//

#define	CONSWITCH_SOUR_REMOTE		0x11	//Զ��ң�أ�ֱ�Ӳ�������
#define	CONSWITCH_SOUR_POWER		0x33	//����
#define	CONSWITCH_SOUR_ENERGY		0x44	//���
#define 	CONSWITCH_SOUR_INVALID		0xBB	//��Ч

#define	CONSWITCHVOLLOW			0x55
#define	CONSWITCHVOLHIGH			0xAA

#ifdef CON_TER_TYPE_FK_JX
#define	CONPOWERON_CTRLLOCK		560			//�ϵ��������ʱ�䣬��λ0.5s��5����
#else
#define	CONPOWERON_CTRLLOCK		1200			//�ϵ��������ʱ�䣬��λ0.5s��10����
#endif

#define	CON_SWITCHIN_NUM				8		//����������������1·�Žڵ㣬4·ң����
#define	CON_SWITCHOUT_NUM			4		//��������
#define	CON_PARA_SWITCHOUT_NUM		4		//���������������ã�

#define	CON_SUMGROUP_NUM			8

#define CON_TIMEUNIT_SEC			0x01	//��
#define CON_TIMEUNIT_MIN			0x02	//��
#define CON_TIMEUNIT_HOUR			0x03	//ʱ
#define CON_TIMEUNIT_DAY			0x04	//��
#define CON_TIMEUNIT_MON			0x05	//��

#define	CONCTRLALRDELAY			240				//2���ӣ����ƶ����󳭱��ʱ����

/*****************************��Ϣ����*****************************/
#define MSG_TYPE_CTRL_DATA_INIT			200//���ݳ�ʼ��
#define MSG_TYPE_CTRL_PARA_INIT			201//��������������ʼ��

#define MSG_TYPE_CTRL_RECV_COMM_FRAME			202//�յ���վ��Ч���ģ������Զ�����ʱ��

#define MSG_TYPE_CTRL_PARA_F17			117//�ն˱�����ֵ
#define MSG_TYPE_CTRL_PARA_F18			118//�ն˹���ʱ��
#define MSG_TYPE_CTRL_PARA_F19			119//�ն�ʱ�ι��ض�ֵ����ϵ��
#define MSG_TYPE_CTRL_PARA_F20			120//�ն��µ������ض�ֵ����ϵ��
#define MSG_TYPE_CTRL_PARA_F22			122//�ն˵���������
#define MSG_TYPE_CTRL_PARA_F23			123//�ն˴߷Ѹ澯����
#define MSG_TYPE_CTRL_PARA_F41			141//ʱ�ι��ض�ֵ
#define MSG_TYPE_CTRL_PARA_F42			142//���ݹ��ز���
#define MSG_TYPE_CTRL_PARA_F43			143//���ʿ��ƵĹ��ʼ��㻬��ʱ��
#define MSG_TYPE_CTRL_PARA_F44			144//Ӫҵ��ͣ�ز���
#define MSG_TYPE_CTRL_PARA_F45			145//�����ִ��趨
#define MSG_TYPE_CTRL_PARA_F46			146//�µ����ض�ֵ
#define MSG_TYPE_CTRL_PARA_F47			147//���������ѣ��ز���
#define MSG_TYPE_CTRL_PARA_F48			148//����ִ��趨
#define MSG_TYPE_CTRL_PARA_F49			149//���ظ澯ʱ��
#define MSG_TYPE_CTRL_PARA_F57			157//�ն������澯����M��ֹ����
#define MSG_TYPE_CTRL_PARA_F58			158//�ն��Զ��������

#define MSG_TYPE_CTRL_CMD_F1			1//ң����բ
#define MSG_TYPE_CTRL_CMD_F2			2//�����բ
#define MSG_TYPE_CTRL_CMD_F9			9//ʱ�ι���Ͷ��
#define MSG_TYPE_CTRL_CMD_F10			10//���ݹ���Ͷ��
#define MSG_TYPE_CTRL_CMD_F11			11//Ӫҵ��ͣ����Ͷ��
#define MSG_TYPE_CTRL_CMD_F12			12//��ǰ�����¸���Ͷ��
#define MSG_TYPE_CTRL_CMD_F15			15//�µ��Ͷ��
#define MSG_TYPE_CTRL_CMD_F16			16//�����Ͷ��
#define MSG_TYPE_CTRL_CMD_F17			17//ʱ�ι��ؽ��
#define MSG_TYPE_CTRL_CMD_F18			18//���ݹ��ؽ��
#define MSG_TYPE_CTRL_CMD_F19			19//Ӫҵ��ͣ���ؽ��
#define MSG_TYPE_CTRL_CMD_F20			20//��ǰ�����¸��ؽ��
#define MSG_TYPE_CTRL_CMD_F23			23//�µ�ؽ��
#define MSG_TYPE_CTRL_CMD_F24			24//����ؽ��
#define MSG_TYPE_CTRL_CMD_F25			25//�ն˱���Ͷ��
#define MSG_TYPE_CTRL_CMD_F26			26//�߷Ѹ澯Ͷ��
#define MSG_TYPE_CTRL_CMD_F33 		33//�ն˱�����
#define MSG_TYPE_CTRL_CMD_F34			34//�߷Ѹ澯���

#define MSG_TYPE_CTRL_SELFDEF_F92			203//�ϵ�������

/*******************************��־*********************************/
#define CON_STATUS_YES_2BYTE			0x55AA	//�����ֽڱ�ǣ���
#define CON_STATUS_NO_2BYTE			0xAA55	//�����ֽڱ�ǣ���
#define CON_STATUS_YES					0x55	//�ֽڱ�ǣ���
#define CON_STATUS_NO					0xAA	//�ֽڱ�ǣ���
#define CONINVALIDVAL					0xBB


/*************************Ӳ���������*******************************************/
/*led id����*/
#define TERCTRL_LED_TRIP_STATE_R(index)   	(2*(index))
#define TERCTRL_LED_TRIP_STATE_G(index) 	(2*(index)+1)
#define TERCTRL_LED_PWCTRL_STATE        		(8)
#define TERCTRL_LED_ERYCTRL_STATE       		(10)
#define TERCTRL_LED_ALARM_STATE         		(13)

/*�̵�������״̬*/
#define TERCTRL_SWITCH_BOARD_ID          	  	2,2,1,1
#define TERCTRL_SWITCH_PORT_ID         	       1,2,1,2

/************��բ*************/
#define		CONJUMPINTER_INVALID	0xFFFF
#define		CONJUMPDELAY_INVALID	0xFF

#define		CONJUMPINTER			120				//��λ0.5s��1����
#define		CONJUMPDELAY			1

/*****************���ݽṹ*******************/
typedef enum
{
	RET_SUCCESS=0,
	RET_ERROR,
	RET_FILL_SAME,				//������ͬ��������д
	RET_MEM_OVER,				//�ڴ����

	RET_TOO_LITTLE,				//δ����С����
	RET_HEAD_ERROR,				//֡ͷ����
	RET_MID_END,				//��;����
	RET_NOENOUGH_LONG,			//����δ��

	RET_GRTASK_NEEDPROC,		//GR���������������Ҫִ��
	RET_GRTASK_NONEEDPROC,		//GR���������������Ҫִ��

	RET_OVERTIME,
	RET_RS485_TASKSOURCE_FULL,
	RET_RS485_TASKSOURCE_NULL,

	RET_TASK_EMPTY,				//����Ϊ��
	RET_TASK_NOEMPTY,			//����Ϊ�ǿ�
	RET_SPEC,
	RET_NEEDPROC,				//��Ҫ����
	RET_DATA_AVAILABLE,			//������Ч
	RET_NEED_JUDGE,				//��ҪԤ��
	RET_NONEED_JUDGE,			//����ҪԤ��

	RET_PASS_ERR,				//�������
	RET_SEQ_ERR,				//SEQ����
	RET_ADDR_ERR,				//��ַ����
	RET_CTRLB_ERR,				//�����ִ���
	RET_LEN_ERR,				//���ȴ���
	RET_REP_ERR,				//�������ʹ���

	RET_ENSURE_FINISH,			//ȷ�����
	RET_LCD_BUSY,				//LCD_Busy
	
	RET_ALR_HAPPEN,				//�澯����
	RET_ALR_RECOVER,			//�澯�ָ�

	RET_MCM_NONEEDSEND,			//����������
	RET_NEEDCLRGROUP,			//�������ͬ������Դ�Լ���ŵ�����
	RET_COMM_TIMEOVER,			//ͨ�ų�ʱ������
	RET_CHANGEPORTPARA,			//��Ҫ�ı�˿ڲ���

	RET_CONNECT_OK				//�յ����CONNECT
}ENURETVALUE;


/////////////////����/////////////////////////
typedef struct _STSWITCHDELAY
{
	unsigned char	ucJumpDelay;
	unsigned short  usJumpInter;
}STSWITCHDELAY;


/////////////////////����///////////////////////////////
typedef struct _STREMOTECTRLCOUNT
{
	unsigned short	usJumpTimeCount;			//�����ӳ�ʱ��
	unsigned short	usRevTimeCount;	
	unsigned short	usJumpTimeAlrCount;			//�澯����ʱ��
	unsigned short	usRevTimeAlrCount;
}STREMOTECTRLCOUNT;

//������բ������
typedef struct _STPOWERCTRLCOUNT
{
	unsigned short	usJumpTimeCount;
	unsigned short	usRevTimeCount;
	unsigned short	usJumpTimeAlrCount;
	unsigned short	usRevTimeAlrCount;
}STPOWERCTRLCOUNT;


/********************************ʱ�乫�ú�����װ*********************************/

STDATETIME	 GetCurrentTime(void);
unsigned char ClearDateTime(STDATETIME *pstDateTime);
void AddTime(STDATETIME *pstDateTime,unsigned long ulTimeInter,unsigned char ucTimeUnit);
unsigned char TimeIsOver(STDATETIME *pstWorkDateTime,STDATETIME *pstBaseDateTime);

/*���ز������*/
void Switch_Cancel(unsigned char ucSwitchNo);
void  Switch_Start(unsigned char ucSwitchNo);
void  Switch_Ready(unsigned char ucSwitchNo,unsigned char ucSwitchSour);
void  Switch_Open(unsigned char ucSwitchNo,unsigned char ucSwitchSour);
unsigned char Load_All_Reset(unsigned char ucSwitchSour);
unsigned char Load_Ctrl_Reset(unsigned char ucSwitchSour);

unsigned char Load_GetSwitch_EnergyReadyOpen(unsigned char ucSwitchSour,unsigned char ucSumGroupNo);
unsigned char Load_SetSwitch_EnergyReadyOpen(unsigned char ucSwitchSour,unsigned char ucSumGroupNo);
unsigned char Load_SetSwitch_Open(unsigned char ucSwitchSour);
unsigned char Load_SetSwitch_Cancel_LastOne(unsigned char ucSwitchSour);
unsigned char Load_SetSwitch_Cancel_Open(unsigned char ucSwitchSour);

/*4·�ִεƿ���*/
void Switch_Set_Trun_Light(unsigned char ucSwitchNo,unsigned char ucSwitchStat);
/*4·�̵�������*/
void Switch_Set_Vol(unsigned char ucSwitchNo,unsigned char ucSwitchStat);

void Load_Switch_Output();
unsigned char Switch_GetSwitch_PowerReadyOpen(unsigned char ucSwitchSour,unsigned char ucSumGroupNo);
unsigned char Load_SetSwitch_PowerReadyOpen(unsigned char ucSwitchSour,unsigned char ucSumGroupNo);
unsigned char Switch_GetSwitch_Open(unsigned char ucSwitchSour);
void Load_Inital_SwitchStat(STSWITCHSTAT *pstSwitchStat);

/*LED���*/
void Led_Timer(void);


/***************����ȫ�ֱ�����ȡ*****************/
STSWITCHSTAT GetSwitchShouldStat(void);
unsigned char	RunPara_GetKeepPower();
STENERGYCTRL	RunPara_GetEnergyCtrl(unsigned char ucSumGroupNo);
STCTRLFEERATE	RunPara_GetCtrlFeeRate();
unsigned char   RunPara_GetTerAdjPara_EnerBuyIsNotFee();
STHISSUMVALGROUP Get_History_PowValSumVal(unsigned char ucPos,unsigned char ucFeeNo);
STCTRLTURN	RunPara_GetEnergyCtrlTurn(unsigned char ucSumGroupNo);
unsigned char Load_GetPowerCtrl_SumGNo(void);
unsigned char Load_GetEnergyCtrl_SumGNo(void);
STMONENERGYREC	RunPara_GetMonEnergyRec(unsigned char ucSumGroupNo);
STBUYENERGYREC	RunPara_GetBuyEnergyRec(unsigned char ucSumGroupNo);
STPOWERCTRLPROJ RunPara_GetPowCtrlProj(unsigned char ucCurveNo,unsigned char ucSumGroupNo);
STPOWERCTRLTIME RunPara_GetPowCtrlTimePer(unsigned char ucCurveNo,unsigned char ucSumGroupNo);
STLOADFIXVAL	RunPara_GetCtrlSafeFixVal();
STLOADFIXVAL	RunPara_GetPowFixVal(unsigned char *pucPowCurveNo,unsigned char *pucEndHour,unsigned char *pucEndMinute,unsigned char ucSumGroupNo);
STPOWERCTRLHOLDTIME RunPara_GetPowCtrlHoldTime(unsigned char ucSumGroupNo);
STCTRLTURN	RunPara_GetPowerCtrlTurn(unsigned char ucSumGroupNo);
unsigned char Get_AutoKeepPower_Hours(void);

/***************����ȫ�ֱ�������*****************/
unsigned char RunPara_SetKeepPower(unsigned char ucFlag);
unsigned char Set_KeepPowEnd_Time(STDATETIME *pstDateTime);
unsigned char RunPara_SetEnergyCtrl(STENERGYCTRL *pstEnergyCtrl,unsigned char ucSumGroupNo);
void Load_SetPowerCtrl_SumGNo(unsigned char ucSumGNo);
void Load_SetEnergyCtrl_SumGNo(unsigned char ucSumGNo);
unsigned char RunPara_SetCtrlFeeRate(STCTRLFEERATE *pstCtrlFeeRate);
unsigned char RunPara_SetMonEnergyRec(STMONENERGYREC *pstMonEnergyRec,unsigned char ucSumGroupNo);
unsigned char RunPara_SetBuyEnergyRec(STBUYENERGYREC *pstBuyEnergyRec,unsigned char ucSumGroupNo);
unsigned char RunPara_SetEnergyCtrlTurn(STCTRLTURN *pstEnergyCtrlTurn,unsigned char ucSumGroupNo);
unsigned char RunPara_SetPowerCtrlAvailble(unsigned char ucCurveNo,unsigned char ucFlag,unsigned char ucSumGroupNo);
unsigned char RunPara_SetPowCtrlProj(unsigned char ucCurveNo,STPOWERCTRLPROJ *pstPowerCtrlProj,unsigned char ucSumGroupNo);
unsigned char RunPara_SetPowCtrlTimePer_Availble(unsigned char ucFlag,unsigned char ucCurveNo,unsigned char ucSumGroupNo);
unsigned char RunPara_SetPowCtrlProj_Availble(unsigned char ucFlag,unsigned char ucCurveNo,unsigned char ucSumGroupNo);
unsigned char RunPara_SetCtrlSafeFixVal(STLOADFIXVAL *pstSaveFixVal);
unsigned char RunPara_SetPowCtrlTimePer(unsigned char ucCurveNo,STPOWERCTRLTIME *pstPowerCtrlTime,unsigned char ucSumGroupNo);
unsigned char RunPara_SetPowCtrlHoldTime(STPOWERCTRLHOLDTIME *pstPowerHoldTime,unsigned char ucSumGroupNo);
unsigned char RunPara_SetPowerCtrlTurn(STCTRLTURN *pstPowerCtrlTurn,unsigned char ucSumGroupNo);
unsigned char Set_PowLower_FreeseTime(STDATETIME *pstDateTime,unsigned char ucFrosenT,unsigned char ucDiff);
unsigned char Set_AutoKeepPower_Time(STDATETIME *pstDateTime);
void  Load_PowLowerCtrlPara_Set(unsigned char ucCtrlTime,unsigned char ucAlrTime1,unsigned char ucAlrTime2,unsigned char ucAlrTime3,unsigned char ucAlrTime4);

/*���ݳ�ʼ��*/
void load_ctrl_data_init(unsigned char *data);
/*���������ݳ�ʼ��*/
void load_ctrl_para_init(unsigned char *data);
/*����������Ϣ����*/
void load_ctrl_cmd_f1(unsigned char *data);
void load_ctrl_cmd_f2(unsigned char *data);
void load_ctrl_cmd_f9(unsigned char *data);
void load_ctrl_cmd_f10(unsigned char *data);
void load_ctrl_cmd_f11(unsigned char *data);
void load_ctrl_cmd_f12(unsigned char *data);
void load_ctrl_cmd_f15(unsigned char *data);
void load_ctrl_cmd_f16(unsigned char *data);
void load_ctrl_cmd_f17(unsigned char *data);
void load_ctrl_cmd_f18(unsigned char *data);
void load_ctrl_cmd_f19(unsigned char *data);
void load_ctrl_cmd_f20(unsigned char *data);
void load_ctrl_cmd_f23(unsigned char *data);
void load_ctrl_cmd_f24(unsigned char *data);
void load_ctrl_cmd_f25(unsigned char *data);
void load_ctrl_cmd_f26(unsigned char *data);
void load_ctrl_cmd_f33(unsigned char *data);
void load_ctrl_cmd_f34(unsigned char *data);


/*���Ʋ�����Ϣ����*/
void load_ctrl_para_f17(unsigned char *data);
void load_ctrl_para_f18(unsigned char *data);
void load_ctrl_para_f19(unsigned char *data);
void load_ctrl_para_f20(unsigned char *data);
void load_ctrl_para_f22(unsigned char *data);
void load_ctrl_para_f23(unsigned char *data);
void load_ctrl_para_f41(unsigned char *data);
void load_ctrl_para_f42(unsigned char *data);
void load_ctrl_para_f43(unsigned char *data);
void load_ctrl_para_f44(unsigned char *data);
void load_ctrl_para_f45(unsigned char *data);
void load_ctrl_para_f46(unsigned char *data);
void load_ctrl_para_f47(unsigned char *data);
void load_ctrl_para_f48(unsigned char *data);
void load_ctrl_para_f49(unsigned char *data);
void load_ctrl_para_f58(unsigned char *data);
void load_ctrl_self_def_f92(unsigned char *data);
void load_ctrl_recv_comm_frame();


/*��ʷ���ݡ�ʵʱ���ݽӿ�����*/
int save_sumg_curr_data_by_sumgno(int sumgno, unsigned short data_id, double *pddata_val, struct date_time_rec *rec_time);
int get_sumg_curr_data_by_sumgno(int sumgno, unsigned short data_id, double *pddata_val, struct date_time_rec *rec_time);
int get_sumg_his_month_data_by_sumgno(int sumgno, unsigned short data_id, struct date_time_rec *std_time, double *pddata_val, struct date_time_rec *rec_time);
int save_mp_curr_data_by_mpno(int mpno, unsigned short data_id, unsigned long *puldata_val, struct date_time_rec *rec_time);
int get_mp_curr_data_by_mpno(int mpno, unsigned short data_id, unsigned long *puldata_val, struct date_time_rec *rec_time);
int get_mp_his_day_data_by_mpno(int mpno, unsigned short data_id, struct date_time_rec *std_time, unsigned long *puldata_val, struct date_time_rec *rec_time);
int get_mp_his_month_data_by_mpno(int mpno, unsigned short data_id, struct date_time_rec *std_time, unsigned long *puldata_val, struct date_time_rec *rec_time);
int save_mp_his_day_data_by_mpno(int mpno, unsigned short data_id, struct date_time_rec *std_time, unsigned long *puldata_val, struct date_time_rec *rec_time);
int save_mp_his_month_data_by_mpno(int mpno, unsigned short data_id, struct date_time_rec *std_time, unsigned long *puldata_val, struct date_time_rec *rec_time);

//���
unsigned char Load_EnergyCtrl();
unsigned char Load_EnergyCtrl_Export(STENERGYCTRL *pstEnergyCtrl);
double Load_Energy_LeftPowVal(STENERGYCTRL *pstEnergyCtrl,unsigned char ucSumGNo);
unsigned char Load_EnergyCtrl_MonFlash(STENERGYCTRL *pstEnergyCtrl);
unsigned char Load_SetEnergy_StaPowVal_LM(void);
unsigned char Load_SetEnergy_StaPowVal(void);
STHISSUMVALGROUP Get_History_PowValSumVal_LM(unsigned char ucPos,unsigned char ucFeeNo);
double Load_Energy_LeftPowVal_CalcBuy(STENERGYCTRL *pstEnergyCtrl,unsigned char ucSumGNo);

//����
unsigned char	Load_PowerCtrl(void);
double Load_GetCurrentInstantPow(unsigned char ucSumGNo);
STHISSUMVALGROUP Get_History_InstantPowSumVal(unsigned char ucPos);
void  Load_ResetRevCount();
void  Load_ResetJumpCount();
unsigned char Load_PowerCtrl_Time_Set(unsigned char ucCurvNo,STDATETIME *pstDateTime);
unsigned char Load_SetSwitch_CancelReady(unsigned char ucSwitchSour);
unsigned char Switch_GetLast_Switch_Open(unsigned char ucSwitchSour);
unsigned char Load_GetLast_Switch_Open(unsigned char ucSwitchSour);
unsigned char Load_PowerCtrl_Time_IsOver_InitNo(unsigned char ucCurvNo);
void Load_PowerCtrl_Time_Init(unsigned char ucCurvNo);
void Load_PowerFrseese_Manage(void);

//ң��
void Load_RemoteCtrl();
unsigned char Load_RemoteResetRevCount(unsigned char ucSwitchNo);
unsigned char Load_RemoteResetJumpCount(unsigned char ucSwitchNo);
unsigned char Load_RemoteResetRevPara(unsigned char ucSwitchNo);
unsigned char Load_RemoteResetJumpPara(unsigned char ucSwitchNo);
unsigned char Load_RemoteSetJumpPara(unsigned char ucSwitchNo,unsigned short usJumpTimeCount,unsigned short usJumpTimeAlrCount,unsigned long ulSecondTimeLast);
unsigned char Load_RemoteSetRevPara(unsigned char ucSwitchNo,unsigned short usRevTimeCount,unsigned short usRevTimeAlrCount);

//�澯
void Alarm_EnsureJudge_BuyPowEnerRec(STBUYENERGYREC pstBuyEnergyRecPtr,double dLeftVal_befor,double dLeftVal_after, unsigned char ucSumGroupNo);
void Alarm_EnsureJudge_EnergyAlr(unsigned char ucEnerType,unsigned char ucCtrlTurn,double dEnerVal,double dFixVal, unsigned char ucSumGroupNo);
void Alarm_EnsureJudge_RemoteCtrl(STSWITCHALARMINFO *pstSwitchAlarmInfo);
void Alarm_EnsureJudge_EnergyCtrl(STSWITCHALARMINFO *pstSwitchAlarmInfo);
void Alarm_EnsureJudge_PowerCtrl(STSWITCHALARMINFO *pstSwitchAlarmInfo);
void Load_Alarm_Manage(void);
unsigned char Load_Alarm_Start(unsigned char ucCtrlTrun,STSWITCHALARMINFO *pstSwitchAlarmInfo);

//ͳ��
void DataProc_Stat_RemoteCtrlNum_Inc(void);
void DataProc_Stat_PowCtrlNum_Inc(void);
void DataProc_Stat_MonthEnerCtrlNum_Inc(void);
void DataProc_Stat_BuyEnerCtrlNum_Inc(void);

unsigned char Load_PowerCtrl_Time_IsOver(unsigned char ucCurvNo);


#endif
