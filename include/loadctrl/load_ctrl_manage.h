#ifndef _LOAD_CTRL_MANAGE_H_

#define _LOAD_CTRL_MANAGE_H_

#include <pax_driver.h>
#include <pax_db.h>

#include "load_remote.h"
#include "load_energy.h"
#include "load_power.h"
#include "beep_sound.h"

#include "../pax_ver.h"

/*************************************控制相关******************************************/
#ifdef CON_TER_TYPE_FK_JX
#define 	CON_SWITCHOUT_MODE		0x55			//继电器输出模式:0x55持续输出,0xaa每隔60秒输出
#else
#define 	CON_SWITCHOUT_MODE		0xAA			//跳闸间隔1分钟输出
#endif

#define 	CON_AVALIBLE_FLAG			0x55
#define 	CON_INVALIBLE_FLAG		0xAA


#define	CON_CTRLFEE_NUM			14
#define	CON_CTRLFEETIME_NUM		48		//30分钟一段，48段

#define	CONSWITCHOPEN			0x55		//开
#define	CONSWITCHREADY			0x5A		//预备开
#define 	CONSWITCHCLOSE			0xAA		//合
#define 	CONSWITCHINVALID			0xBB		//

#define	CONSWITCH_SOUR_REMOTE		0x11	//远方遥控，直接操作开关
#define	CONSWITCH_SOUR_POWER		0x33	//功率
#define	CONSWITCH_SOUR_ENERGY		0x44	//电控
#define 	CONSWITCH_SOUR_INVALID		0xBB	//无效

#define	CONSWITCHVOLLOW			0x55
#define	CONSWITCHVOLHIGH			0xAA

#ifdef CON_TER_TYPE_FK_JX
#define	CONPOWERON_CTRLLOCK		560			//上电闭锁持续时间，单位0.5s，5分钟
#else
#define	CONPOWERON_CTRLLOCK		1200			//上电闭锁持续时间，单位0.5s，10分钟
#endif

#define	CON_SWITCHIN_NUM				8		//开关量数量，包括1路门节点，4路遥信量
#define	CON_SWITCHOUT_NUM			4		//开关数量
#define	CON_PARA_SWITCHOUT_NUM		4		//开关数量（参数用）

#define	CON_SUMGROUP_NUM			8

#define CON_TIMEUNIT_SEC			0x01	//秒
#define CON_TIMEUNIT_MIN			0x02	//分
#define CON_TIMEUNIT_HOUR			0x03	//时
#define CON_TIMEUNIT_DAY			0x04	//日
#define CON_TIMEUNIT_MON			0x05	//月

#define	CONCTRLALRDELAY			240				//2分钟，控制动作后抄表的时间间隔

/*****************************消息类型*****************************/
#define MSG_TYPE_CTRL_DATA_INIT			200//数据初始化
#define MSG_TYPE_CTRL_PARA_INIT			201//参数及数据区初始化

#define MSG_TYPE_CTRL_RECV_COMM_FRAME			202//收到主站有效报文，跟新自动保电时间

#define MSG_TYPE_CTRL_PARA_F17			117//终端保安定值
#define MSG_TYPE_CTRL_PARA_F18			118//终端功控时段
#define MSG_TYPE_CTRL_PARA_F19			119//终端时段功控定值浮动系数
#define MSG_TYPE_CTRL_PARA_F20			120//终端月电能量控定值浮动系数
#define MSG_TYPE_CTRL_PARA_F22			122//终端电能量费率
#define MSG_TYPE_CTRL_PARA_F23			123//终端催费告警参数
#define MSG_TYPE_CTRL_PARA_F41			141//时段功控定值
#define MSG_TYPE_CTRL_PARA_F42			142//厂休功控参数
#define MSG_TYPE_CTRL_PARA_F43			143//功率控制的功率计算滑差时间
#define MSG_TYPE_CTRL_PARA_F44			144//营业报停控参数
#define MSG_TYPE_CTRL_PARA_F45			145//功控轮次设定
#define MSG_TYPE_CTRL_PARA_F46			146//月电量控定值
#define MSG_TYPE_CTRL_PARA_F47			147//购电量（费）控参数
#define MSG_TYPE_CTRL_PARA_F48			148//电控轮次设定
#define MSG_TYPE_CTRL_PARA_F49			149//功控告警时间
#define MSG_TYPE_CTRL_PARA_F57			157//终端声音告警允许∕禁止设置
#define MSG_TYPE_CTRL_PARA_F58			158//终端自动保电参数

#define MSG_TYPE_CTRL_CMD_F1			1//遥控跳闸
#define MSG_TYPE_CTRL_CMD_F2			2//允许合闸
#define MSG_TYPE_CTRL_CMD_F9			9//时段功控投入
#define MSG_TYPE_CTRL_CMD_F10			10//厂休功控投入
#define MSG_TYPE_CTRL_CMD_F11			11//营业报停功控投入
#define MSG_TYPE_CTRL_CMD_F12			12//当前功率下浮控投入
#define MSG_TYPE_CTRL_CMD_F15			15//月电控投入
#define MSG_TYPE_CTRL_CMD_F16			16//购电控投入
#define MSG_TYPE_CTRL_CMD_F17			17//时段功控解除
#define MSG_TYPE_CTRL_CMD_F18			18//厂休功控解除
#define MSG_TYPE_CTRL_CMD_F19			19//营业报停功控解除
#define MSG_TYPE_CTRL_CMD_F20			20//当前功率下浮控解除
#define MSG_TYPE_CTRL_CMD_F23			23//月电控解除
#define MSG_TYPE_CTRL_CMD_F24			24//购电控解除
#define MSG_TYPE_CTRL_CMD_F25			25//终端保电投入
#define MSG_TYPE_CTRL_CMD_F26			26//催费告警投入
#define MSG_TYPE_CTRL_CMD_F33 		33//终端保电解除
#define MSG_TYPE_CTRL_CMD_F34			34//催费告警解除

#define MSG_TYPE_CTRL_SELFDEF_F92			203//上电闭锁解除

/*******************************标志*********************************/
#define CON_STATUS_YES_2BYTE			0x55AA	//两个字节标记：是
#define CON_STATUS_NO_2BYTE			0xAA55	//两个字节标记：否
#define CON_STATUS_YES					0x55	//字节标记：是
#define CON_STATUS_NO					0xAA	//字节标记：否
#define CONINVALIDVAL					0xBB


/*************************硬件操作相关*******************************************/
/*led id设置*/
#define TERCTRL_LED_TRIP_STATE_R(index)   	(2*(index))
#define TERCTRL_LED_TRIP_STATE_G(index) 	(2*(index)+1)
#define TERCTRL_LED_PWCTRL_STATE        		(8)
#define TERCTRL_LED_ERYCTRL_STATE       		(10)
#define TERCTRL_LED_ALARM_STATE         		(13)

/*继电器控制状态*/
#define TERCTRL_SWITCH_BOARD_ID          	  	2,2,1,1
#define TERCTRL_SWITCH_PORT_ID         	       1,2,1,2

/************跳闸*************/
#define		CONJUMPINTER_INVALID	0xFFFF
#define		CONJUMPDELAY_INVALID	0xFF

#define		CONJUMPINTER			120				//单位0.5s，1分钟
#define		CONJUMPDELAY			1

/*****************数据结构*******************/
typedef enum
{
	RET_SUCCESS=0,
	RET_ERROR,
	RET_FILL_SAME,				//内容相同，不再填写
	RET_MEM_OVER,				//内存溢出

	RET_TOO_LITTLE,				//未到最小长度
	RET_HEAD_ERROR,				//帧头错误
	RET_MID_END,				//中途结束
	RET_NOENOUGH_LONG,			//长度未到

	RET_GRTASK_NEEDPROC,		//GR任务队列中有任务要执行
	RET_GRTASK_NONEEDPROC,		//GR任务队列中无任务要执行

	RET_OVERTIME,
	RET_RS485_TASKSOURCE_FULL,
	RET_RS485_TASKSOURCE_NULL,

	RET_TASK_EMPTY,				//任务为空
	RET_TASK_NOEMPTY,			//任务为非空
	RET_SPEC,
	RET_NEEDPROC,				//需要处理
	RET_DATA_AVAILABLE,			//数据有效
	RET_NEED_JUDGE,				//需要预判
	RET_NONEED_JUDGE,			//不需要预判

	RET_PASS_ERR,				//密码错误
	RET_SEQ_ERR,				//SEQ错误
	RET_ADDR_ERR,				//地址错误
	RET_CTRLB_ERR,				//控制字错误
	RET_LEN_ERR,				//长度错误
	RET_REP_ERR,				//报文类型错误

	RET_ENSURE_FINISH,			//确诊结束
	RET_LCD_BUSY,				//LCD_Busy
	
	RET_ALR_HAPPEN,				//告警发生
	RET_ALR_RECOVER,			//告警恢复

	RET_MCM_NONEEDSEND,			//无须上送了
	RET_NEEDCLRGROUP,			//需清除相同任务来源以及表号的任务
	RET_COMM_TIMEOVER,			//通信超时次数到
	RET_CHANGEPORTPARA,			//需要改变端口参数

	RET_CONNECT_OK				//收到完成CONNECT
}ENURETVALUE;


/////////////////常用/////////////////////////
typedef struct _STSWITCHDELAY
{
	unsigned char	ucJumpDelay;
	unsigned short  usJumpInter;
}STSWITCHDELAY;


/////////////////////功控///////////////////////////////
typedef struct _STREMOTECTRLCOUNT
{
	unsigned short	usJumpTimeCount;			//动作延迟时间
	unsigned short	usRevTimeCount;	
	unsigned short	usJumpTimeAlrCount;			//告警持续时间
	unsigned short	usRevTimeAlrCount;
}STREMOTECTRLCOUNT;

//功控跳闸计数器
typedef struct _STPOWERCTRLCOUNT
{
	unsigned short	usJumpTimeCount;
	unsigned short	usRevTimeCount;
	unsigned short	usJumpTimeAlrCount;
	unsigned short	usRevTimeAlrCount;
}STPOWERCTRLCOUNT;


/********************************时间公用函数封装*********************************/

STDATETIME	 GetCurrentTime(void);
unsigned char ClearDateTime(STDATETIME *pstDateTime);
void AddTime(STDATETIME *pstDateTime,unsigned long ulTimeInter,unsigned char ucTimeUnit);
unsigned char TimeIsOver(STDATETIME *pstWorkDateTime,STDATETIME *pstBaseDateTime);

/*开关操作相关*/
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

/*4路轮次灯控制*/
void Switch_Set_Trun_Light(unsigned char ucSwitchNo,unsigned char ucSwitchStat);
/*4路继电器控制*/
void Switch_Set_Vol(unsigned char ucSwitchNo,unsigned char ucSwitchStat);

void Load_Switch_Output();
unsigned char Switch_GetSwitch_PowerReadyOpen(unsigned char ucSwitchSour,unsigned char ucSumGroupNo);
unsigned char Load_SetSwitch_PowerReadyOpen(unsigned char ucSwitchSour,unsigned char ucSumGroupNo);
unsigned char Switch_GetSwitch_Open(unsigned char ucSwitchSour);
void Load_Inital_SwitchStat(STSWITCHSTAT *pstSwitchStat);

/*LED点灯*/
void Led_Timer(void);


/***************控制全局变量读取*****************/
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

/***************控制全局变量设置*****************/
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

/*数据初始化*/
void load_ctrl_data_init(unsigned char *data);
/*参数及数据初始化*/
void load_ctrl_para_init(unsigned char *data);
/*控制命令消息解析*/
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


/*控制参数消息解析*/
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


/*历史数据、实时数据接口声明*/
int save_sumg_curr_data_by_sumgno(int sumgno, unsigned short data_id, double *pddata_val, struct date_time_rec *rec_time);
int get_sumg_curr_data_by_sumgno(int sumgno, unsigned short data_id, double *pddata_val, struct date_time_rec *rec_time);
int get_sumg_his_month_data_by_sumgno(int sumgno, unsigned short data_id, struct date_time_rec *std_time, double *pddata_val, struct date_time_rec *rec_time);
int save_mp_curr_data_by_mpno(int mpno, unsigned short data_id, unsigned long *puldata_val, struct date_time_rec *rec_time);
int get_mp_curr_data_by_mpno(int mpno, unsigned short data_id, unsigned long *puldata_val, struct date_time_rec *rec_time);
int get_mp_his_day_data_by_mpno(int mpno, unsigned short data_id, struct date_time_rec *std_time, unsigned long *puldata_val, struct date_time_rec *rec_time);
int get_mp_his_month_data_by_mpno(int mpno, unsigned short data_id, struct date_time_rec *std_time, unsigned long *puldata_val, struct date_time_rec *rec_time);
int save_mp_his_day_data_by_mpno(int mpno, unsigned short data_id, struct date_time_rec *std_time, unsigned long *puldata_val, struct date_time_rec *rec_time);
int save_mp_his_month_data_by_mpno(int mpno, unsigned short data_id, struct date_time_rec *std_time, unsigned long *puldata_val, struct date_time_rec *rec_time);

//电控
unsigned char Load_EnergyCtrl();
unsigned char Load_EnergyCtrl_Export(STENERGYCTRL *pstEnergyCtrl);
double Load_Energy_LeftPowVal(STENERGYCTRL *pstEnergyCtrl,unsigned char ucSumGNo);
unsigned char Load_EnergyCtrl_MonFlash(STENERGYCTRL *pstEnergyCtrl);
unsigned char Load_SetEnergy_StaPowVal_LM(void);
unsigned char Load_SetEnergy_StaPowVal(void);
STHISSUMVALGROUP Get_History_PowValSumVal_LM(unsigned char ucPos,unsigned char ucFeeNo);
double Load_Energy_LeftPowVal_CalcBuy(STENERGYCTRL *pstEnergyCtrl,unsigned char ucSumGNo);

//功控
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

//遥控
void Load_RemoteCtrl();
unsigned char Load_RemoteResetRevCount(unsigned char ucSwitchNo);
unsigned char Load_RemoteResetJumpCount(unsigned char ucSwitchNo);
unsigned char Load_RemoteResetRevPara(unsigned char ucSwitchNo);
unsigned char Load_RemoteResetJumpPara(unsigned char ucSwitchNo);
unsigned char Load_RemoteSetJumpPara(unsigned char ucSwitchNo,unsigned short usJumpTimeCount,unsigned short usJumpTimeAlrCount,unsigned long ulSecondTimeLast);
unsigned char Load_RemoteSetRevPara(unsigned char ucSwitchNo,unsigned short usRevTimeCount,unsigned short usRevTimeAlrCount);

//告警
void Alarm_EnsureJudge_BuyPowEnerRec(STBUYENERGYREC pstBuyEnergyRecPtr,double dLeftVal_befor,double dLeftVal_after, unsigned char ucSumGroupNo);
void Alarm_EnsureJudge_EnergyAlr(unsigned char ucEnerType,unsigned char ucCtrlTurn,double dEnerVal,double dFixVal, unsigned char ucSumGroupNo);
void Alarm_EnsureJudge_RemoteCtrl(STSWITCHALARMINFO *pstSwitchAlarmInfo);
void Alarm_EnsureJudge_EnergyCtrl(STSWITCHALARMINFO *pstSwitchAlarmInfo);
void Alarm_EnsureJudge_PowerCtrl(STSWITCHALARMINFO *pstSwitchAlarmInfo);
void Load_Alarm_Manage(void);
unsigned char Load_Alarm_Start(unsigned char ucCtrlTrun,STSWITCHALARMINFO *pstSwitchAlarmInfo);

//统计
void DataProc_Stat_RemoteCtrlNum_Inc(void);
void DataProc_Stat_PowCtrlNum_Inc(void);
void DataProc_Stat_MonthEnerCtrlNum_Inc(void);
void DataProc_Stat_BuyEnerCtrlNum_Inc(void);

unsigned char Load_PowerCtrl_Time_IsOver(unsigned char ucCurvNo);


#endif
