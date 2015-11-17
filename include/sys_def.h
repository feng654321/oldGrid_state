/************************
 *file name:sys_def.h
 *
 *writer:lihaisong
 *
 *
 *
 * ********************************/

#ifndef _SYS_DEF_H_
#define _SYS_DEF_H_


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

#include <signal.h>
#include <errno.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>
#include <sys/time.h>
#include <sys/ioctl.h>

#include <pax_driver.h>
#include <pax_db.h>
#include <pax_base.h>
#include <pax_util.h>

#include "pax_ver.h"

#ifdef CON_TER_TYPE_FK_ALL		//专变
#define CON_TER_WITH_PULSE_SAMPLE		1		//带脉冲采集
#endif

//调试信息
#define	DBGFMT			"%s[%d]"
#define	DBGARG			__FILE__,__LINE__

#define	DBGFMT_A		"%s[%d]%d:"
#define	DBGARG_A		__FILE__,__LINE__,getpid()

#define	DBGFMT_B		"%s|%s[%d]%d:"
#define	DBGARG_B		__FILE__,__FUNCTION__,__LINE__,getpid()

#define	DBGFMT_C		"[%d]%d:"
#define	DBGARG_C		__LINE__,getpid()
//


//软件版本分为CCXX-AIT-FFF-NNNNN 格式，CC 表示厂商代码（BCD 码），XX 表示不同类型
//    的软件，A 主版本，I 次版本，T 小版本，FFF 附加信息，NNNNNN 用行政区码表示地方定制信息。
#define CON_SOFT_VER_CC		0x11	//11 华隆
#define CON_SOFT_VER_XX		0x00
#define CON_SOFT_VER_AI		0x11	//AIT-FFF  1.18 - 000
#define CON_SOFT_VER_TF		0x80
#define CON_SOFT_VER_FF		0x00
#define CON_SOFT_VER_NN1	0x00
#define CON_SOFT_VER_NN2	0x80	//80 省公司
#define CON_SOFT_VER_NN3	0x01

#define CON_HARD_VER_LL		0x05
#define CON_HARD_VER_HH		0x00


#define EQLINK_CHAN_NO      0x06/*从终端使用通道号*/

#define MSG_TYPE_COMMDATA	1//业务处理中心进程----〉端口上行通讯处理进程 数据收发
#define MSG_TYPE_CHANINFO	2//业务处理中心进程----〉端口上行通讯处理进程 通道信息参数
#define MSG_TYPE_MD_RS232   3//业务处理中心进程----〉端口上行通讯处理进程 串口设置参数 

#define MSG_TYPE_TRANSMIT_COMMDATA 	8
#define MSG_TYPE_COMMDATA_RET		9

#define MSG_TYPE_CM_TRANSMIT			19//业务处理中心进程----〉设备采集管理进程，请求信息
#define MSG_TYPE_CM_TRANSMIT_RET		20//设备采集管理进程----〉业务处理中心进程，返回结果信息
#define MSG_TYPE_RS485_CM_TRANSMIT		21//RS485抄表接口----〉RS485中继抄表通讯处理进程，请求信息
#define MSG_TYPE_RS485_CM_TRANSMIT_RET 	22//RS485中继抄表通讯处理进程----〉设备采集管理进程，返回结果信息
#define MSG_TYPE_RS485_CM 				23//RS485抄表接口----〉RS485抄表各规约通讯处理进程，请求信息
										  //RS485抄表各规约通讯处理进程----〉设备采集管理进程，返回数据信息
#define MSG_TYPE_RS485_CM_FAILURE 		24//RS485抄表各规约通讯处理进程----〉设备采集管理进程，抄表失败

#define MSG_TYPE_EQP_LINKED_COMMDATA	27//业务处理中心程序<-->设备级联管理程序，数据收发
#define MSG_TYPE_RS485_L_TRANSMIT		28//RS485级联接口---〉RS485级联转发处理进程，请求信息
#define MSG_TYPE_RS485_L_TRANSMIT_RET	29//RS485级联转发处理进程---〉设备级联管理进程，返回结果信息
#define MSG_TYPE_RS485_L_WAITRECV_BEGIN 30//RS485级联接口---〉RS485级联接收处理进程，开始端口等待接收
#define MSG_TYPE_RS485_L_WAITRECV_END	31//RS485级联接口---〉RS485级联接收处理进程，结束端口等待接收
#define MSG_TYPE_RS485_L_RECV_DATA		32//RS485级联接收处理进程---〉设备级联管理进程，接收数据

#define MSG_TYPE_SIG_COLL_COMMDATA		33//状态采集进程---〉设备级联管理进程，接收数据
#define MSG_TYPE_PLC_CM 				40//PLC抄表接口
#define MSG_TYPE_WIRELESS_CM			41//无线抄表接口，近似PLC抄表，有路由等管理
#define MSG_TYPE_SAMPLE_CM 				42//交流采集

#define MSG_TYPE_CHILD	 				50//子进程发送信息
#define MSG_TYPE_CM_REALTIME			51//业务处理中心进程----〉设备采集管理进程，实时召测，即时操作（实时召测、拉合闸、校时等）
#define MSG_TYPE_ERC                    52//事件信息
#define MSG_TYPE_CALL_SITE              53//呼叫主站

#define MSG_TYPE_REBOOT_APP				54	//应用程序重启
#define MSG_TYPE_REBOOT_SYS				55	//操作系统重启
#define MSG_TYPE_DATA_INIT				56	//数据区初始化
#define MSG_TYPE_PARA_INIT				57	//参数（除与系统主站通信有关的）及全体数据区初始化
#define MSG_TYPE_FACTORY_SETTING		58	//参数及全体数据区初始化（即恢复至出厂配置）
#define MSG_TYPE_CQ_ON_DUTY				59	//重庆，投入退出运行的消息

#define MSG_TYPE_HMI_SET                60 // 显示进程 设置成功 发送的消息
#define MSG_TYPE_HMI_DB_OK              61 // 数据库文件准备好
#define MSG_TYPE_CHN_MSG                63 // 中文信息
#define MSG_TYPE_ALARM_MSG              64 // 告警在显示屏上提示
#define MSG_TYPE_SCAN_FLASH_OK          65 // scan flash 完成
#define MSG_TYPE_HMI_NORM_MSG			66	//显示进程发出的一般事件消息

#define MSG_TYPE_ALARM_CM 				70// 报警处理的抄表
#define MSG_TYPE_FLUX_LIMIT 			71// 通信流量
#define MSG_TYPE_UPDATE					72// 程序更新相关
#define MSG_TYPE_PLC_COLL_NODE_NORET	73// 启动载波搜索新表,不需要返回信息
#define MSG_TYPE_CM_TRANSMIT_RET_F9		74// 载波抄表，数据转发F9
#define MSG_TYPE_CONNECT_MNG 			75// 终端上行通信连接管理
#define MSG_TYPE_PLC_CTRL				76// 载波抄表控制

#define MSG_TYPE_READ_METER 			77// 现场调试指定测量点抄表
#define MSG_TYPE_FIND_METER				78// 现场调试搜索表号
#define MSG_TYPE_READ_ALL_METER 		79// 现场调试所有测量点抄表
#define MSG_TYPE_READ_NEW_METER 		80// 现场调试新增电能表抄读正向有功总
#define MSG_TYPE_RTCM_TRANSMIT_RET		81//实时抄表

#define MSG_TYPE_CM_TRANSMIT_RET_F10	82// 载波抄表，数据转发F10
#define MSG_TYPE_CM_TRANSMIT_RET_F11	83// 载波抄表，数据转发F11

#define MSG_TYPE_THREAD_HEALTH			84	//线程健康监测

#define MSG_TYPE_LCD_CLEAR_CURVE		86	//界面上执行删除曲线数据

#define MSG_TYPE_TERCTRL_REMOTE_ON		0x80  //128遥控跳闸命令
#define MSG_TYPE_TERCTRL_REMOTE_OFF		0x81  //129遥控取消跳闸命令
#define MSG_TYPE_TERCTRL_CG_AMMETER		0x82  //130换表或表字翻转

#define MSG_TYPE_MISCDATA_SET			0x90  //144业务处理中心进程----〉设备采集管理进程，底度设置

#define CON_TASK_TYPE_PLC_CM			40//PLC抄表任务
#define CON_TASK_TYPE_SAMPLE_CM 		42//交流采集任务
#define CON_TASK_TYPE_RS485_CM 			23//RS485抄表任务

struct sys_msg_hdr{
	long type;
	unsigned long send_pid;
	unsigned char msg_type;
};
/*通道类型*/
#define CHAN_TYPE_RS232		1
#define CHAN_TYPE_IRDA		2
#define CHAN_TYPE_RS485		3
#define CHAN_TYPE_ETHER		4
#define CHAN_TYPE_SMS		5
#define CHAN_TYPE_GPRSCDMA	6

//子进程发送事件发生信息
#define MSG_CHILD_GPRS_CONNECT			1//gprs登录事件
#define MSG_CHILD_ETHNET_CONNECT		2//以太网登录事件

//------------------- 可执行程序路径定义 ----------------------------
#define CON_STR_FILE_RS485_CM_TRANSMIT		"rs485_cm_transmit"
#define CON_STR_PATH_RS485_CM_TRANSMIT		"/usr1/bin/rs485_cm_transmit"

#define CON_STR_FILE_RS485_CM_DLT645_1997	"rs485_cm_dlt645_1997"
#define CON_STR_PATH_RS485_CM_DLT645_1997	"/usr1/bin/rs485_cm_dlt645_1997"

#define CON_STR_FILE_RS485_CM_DLT645_2007	"rs485_cm_dlt645_2007"
#define CON_STR_PATH_RS485_CM_DLT645_2007	"/usr1/bin/rs485_cm_dlt645_2007"

#define CON_STR_FILE_RS485_CM_WEISHENG    	"rs485_cm_weisheng"
#define CON_STR_PATH_RS485_CM_WEISHENG    	"/usr1/bin/rs485_cm_weisheng"

#define CON_STR_FILE_EQP_LINKED_MNG			"eqp_linked_mng"
#define CON_STR_PATH_EQP_LINKED_MNG			"/usr1/bin/eqp_linked_mng"

#define CON_STR_FILE_EQP_COLL_MNG			"eqp_coll_mng"
#define CON_STR_PATH_EQP_COLL_MNG			"/usr1/bin/eqp_coll_mng"

#define CON_STR_FILE_SERIAL_UP_COMM			"serial_up_comm"
#define CON_STR_PATH_SERIAL_UP_COMM			"/usr1/bin/serial_up_comm"

#define CON_STR_FILE_ETHER_UP_COMM			"ether_up_comm"
#define CON_STR_PATH_ETHER_UP_COMM			"/usr1/bin/ether_up_comm"

#define CON_STR_FILE_REMOTE_WIRELESS_UP_COMM "remote_wireless_up_comm"
#define CON_STR_PATH_REMOTE_WIRELESS_UP_COMM "/usr1/bin/remote_wireless_up_comm"

#define CON_STR_FILE_MC_RUN					"mc_run"
#define CON_STR_PATH_MC_RUN					"/usr1/bin/mc_run"

#define CON_STR_FILE_MDB_INIT				"mdb_init"
#define CON_STR_PATH_MDB_INIT				"/usr1/bin/mdb_init"

#define CON_STR_FILE_SIG_COLL				"sig_coll"
#define CON_STR_PATH_SIG_COLL				"/usr1/bin/sig_coll"

#define CON_STR_FILE_MMI					"hmi_main"
#define CON_STR_PATH_MMI					"/usr1/bin/hmi_main"

#define CON_STR_FILE_DATABASE_MANAGE		"database_manage"
#define CON_STR_PATH_DATABASE_MANAGE		"/usr1/bin/database_manage"

#define CON_STR_FILE_SERIAL_COMM_RECV		"serial_comm_recv"
#define CON_STR_PATH_SERIAL_COMM_RECV		"/usr1/bin/serial_comm_recv"

#define CON_STR_FILE_RS485_L_TRANSMIT		"rs485_l_transmit"
#define CON_STR_PATH_RS485_L_TRANSMIT		"/usr1/bin/rs485_l_transmit"

#define CON_STR_FILE_PAX_TMS_CLIENT			"pax_tms_client"
#define CON_STR_PATH_PAX_TMS_CLIENT			"/usr1/bin/pax_tms_client"

#define CON_STR_FILE_MPARA_REV				"mpara_rev"
#define CON_STR_PATH_MPARA_REV				"/usr1/bin/mpara_rev"

#define CON_STR_FILE_LOAD_CTRL_MANAGE "load_ctrl_manage"
#define CON_STR_PATH_LOAD_CTRL_MANAGE "/usr1/bin/load_ctrl_manage"

#define CON_STR_FILE_EQP_BEEN_COLLECT_MNG	"eqp_been_collected_mng"
#define CON_STR_PATH_EQP_BEEN_COLLECT_MNG	"/usr1/bin/eqp_been_collected_mng"

#define CON_STR_FILE_METER	"meter"
#define CON_STR_PATH_METER	"/usr1/bin/meter"

//---------------------------- 数据项标识 -----------------------------------
#define CON_DI_TYPE_NONE								0x0000//无效数据标识
#define CON_DI_TYPE_INVALID								0xBBBB//无效数据标识
#define CON_DI_TYPE_MPRELAY								0x1111//测量点中继命令
#define CON_DI_TYPE_EXT									0xCDCD//扩展命令数据标识
#define	CON_DI_TYPE_MPALLDI								0xFFFF//所有

//#define	CON_DI_TYPE_DATA_PULSE						0x9xxx + 0x6000//脉冲电量标识一次数据
///////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPDIRPOWTOTAL						0x9010//正向有功总电能
#define CON_DI_TYPE_MPDIRPOWPLUS						0x9011//正向有功尖电能
#define CON_DI_TYPE_MPDIRPOWAPEX						0x9012//正向有功峰电能
#define CON_DI_TYPE_MPDIRPOWFLAT						0x9013//正向有功平电能
#define CON_DI_TYPE_MPDIRPOWVALE						0x9014//正向有功谷电能
#define CON_DI_TYPE_MPDIRPOW_BLOCK						0x901F//正向有功电能数据块

#define CON_DI_TYPE_MPUNDIRPOWTOTAL						0x9020//反向有功总电能
#define CON_DI_TYPE_MPUNDIRPOWPLUS						0x9021//反向有功尖电能
#define CON_DI_TYPE_MPUNDIRPOWAPEX						0x9022//反向有功峰电能
#define CON_DI_TYPE_MPUNDIRPOWFLAT						0x9023//反向有功平电能
#define CON_DI_TYPE_MPUNDIRPOWVALE						0x9024//反向有功谷电能
#define CON_DI_TYPE_MPUNDIRPOW_BLOCK 					0x902F//反向有功电能数据块
///////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPDIRPOWTOTAL_LM					0x9410//正向有功总电能（上月）
#define CON_DI_TYPE_MPDIRPOWPLUS_LM						0x9411//正向有功尖电能（上月）
#define CON_DI_TYPE_MPDIRPOWAPEX_LM						0x9412//正向有功峰电能（上月）
#define CON_DI_TYPE_MPDIRPOWFLAT_LM						0x9413//正向有功平电能（上月）
#define CON_DI_TYPE_MPDIRPOWVALE_LM						0x9414//正向有功谷电能（上月）
#define CON_DI_TYPE_MPDIRPOW_LM_BLOCK					0x941F//正向有功电能数据块（上月）

#define CON_DI_TYPE_MPUNDIRPOWTOTAL_LM					0x9420//反向有功总电能（上月）
#define CON_DI_TYPE_MPUNDIRPOWPLUS_LM					0x9421//反向有功尖电能（上月）
#define CON_DI_TYPE_MPUNDIRPOWAPEX_LM					0x9422//反向有功峰电能（上月）
#define CON_DI_TYPE_MPUNDIRPOWFLAT_LM					0x9423//反向有功平电能（上月）
#define CON_DI_TYPE_MPUNDIRPOWVALE_LM					0x9424//反向有功谷电能（上月）
#define CON_DI_TYPE_MPUNDIRPOW_LM_BLOCK 				0x942F//反向有功电能数据块（上月）
///////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPDIRVARTOTAL						0x9110//正向无功总电能
#define CON_DI_TYPE_MPDIRVARPLUS						0x9111//正向无功尖电能
#define CON_DI_TYPE_MPDIRVARAPEX						0x9112//正向无功峰电能
#define CON_DI_TYPE_MPDIRVARFLAT						0x9113//正向无功平电能
#define CON_DI_TYPE_MPDIRVARVALE						0x9114//正向无功谷电能
#define CON_DI_TYPE_MPDIRVAR_BLOCK						0x911F//正向无功电能数据块

#define CON_DI_TYPE_MPUNDIRVARTOTAL						0x9120//反向无功总电能
#define CON_DI_TYPE_MPUNDIRVARPLUS						0x9121//反向无功尖电能
#define CON_DI_TYPE_MPUNDIRVARAPEX						0x9122//反向无功峰电能
#define CON_DI_TYPE_MPUNDIRVARFLAT						0x9123//反向无功平电能
#define CON_DI_TYPE_MPUNDIRVARVALE						0x9124//反向无功谷电能
#define CON_DI_TYPE_MPUNDIRVAR_BLOCK					0x912F//反向无功电能数据块
///////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPDIRVARTOTAL_LM					0x9510//正向无功总电能（上月）
#define CON_DI_TYPE_MPDIRVARPLUS_LM						0x9511//正向无功尖电能（上月）
#define CON_DI_TYPE_MPDIRVARAPEX_LM						0x9512//正向无功峰电能（上月）
#define CON_DI_TYPE_MPDIRVARFLAT_LM						0x9513//正向无功平电能（上月）
#define CON_DI_TYPE_MPDIRVARVALE_LM						0x9514//正向无功谷电能（上月）
#define CON_DI_TYPE_MPDIRVAR_LM_BLOCK					0x951F//正向无功电能数据块（上月）

#define CON_DI_TYPE_MPUNDIRVARTOTAL_LM					0x9520//反向无功总电能（上月）
#define CON_DI_TYPE_MPUNDIRVARPLUS_LM					0x9521//反向无功尖电能（上月）
#define CON_DI_TYPE_MPUNDIRVARAPEX_LM					0x9522//反向无功峰电能（上月）
#define CON_DI_TYPE_MPUNDIRVARFLAT_LM					0x9523//反向无功平电能（上月）
#define CON_DI_TYPE_MPUNDIRVARVALE_LM					0x9524//反向无功谷电能（上月）
#define CON_DI_TYPE_MPUNDIRVAR_LM_BLOCK					0x952F//反向无功电能数据块（上月）
/////////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPVAR1								0x9130//一象限无功总电能
#define CON_DI_TYPE_MPVAR1_FEE1							0x9131//费率1
#define CON_DI_TYPE_MPVAR1_FEE2							0x9132//费率2
#define CON_DI_TYPE_MPVAR1_FEE3							0x9133//费率3
#define CON_DI_TYPE_MPVAR1_FEE4							0x9134//费率4
#define CON_DI_TYPE_MPVAR1_BLOCK						0x913F//一象限无功电能数据块

#define CON_DI_TYPE_MPVAR4								0x9140//四象限无功总电能
#define CON_DI_TYPE_MPVAR4_FEE1							0x9141//费率1
#define CON_DI_TYPE_MPVAR4_FEE2							0x9142//费率2
#define CON_DI_TYPE_MPVAR4_FEE3							0x9143//费率3
#define CON_DI_TYPE_MPVAR4_FEE4							0x9144//费率4
#define CON_DI_TYPE_MPVAR4_BLOCK						0x914F//一象限无功电能数据块

#define CON_DI_TYPE_MPVAR2								0x9150//二象限无功总电能
#define CON_DI_TYPE_MPVAR2_FEE1							0x9151//费率1
#define CON_DI_TYPE_MPVAR2_FEE2							0x9152//费率2
#define CON_DI_TYPE_MPVAR2_FEE3							0x9153//费率3
#define CON_DI_TYPE_MPVAR2_FEE4							0x9154//费率4
#define CON_DI_TYPE_MPVAR2_BLOCK						0x915F//二象限无功电能数据块

#define CON_DI_TYPE_MPVAR3								0x9160//三象限无功总电能
#define CON_DI_TYPE_MPVAR3_FEE1							0x9161//费率1
#define CON_DI_TYPE_MPVAR3_FEE2							0x9162//费率2
#define CON_DI_TYPE_MPVAR3_FEE3							0x9163//费率3
#define CON_DI_TYPE_MPVAR3_FEE4							0x9164//费率4
#define CON_DI_TYPE_MPVAR3_BLOCK						0x916F//三象限无功电能数据块
///////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPVAR1_LM							0x9530//一象限无功总电能（上月）
#define CON_DI_TYPE_MPVAR1_LM_FEE1						0x9531//费率1
#define CON_DI_TYPE_MPVAR1_LM_FEE2						0x9532//费率2
#define CON_DI_TYPE_MPVAR1_LM_FEE3						0x9533//费率3
#define CON_DI_TYPE_MPVAR1_LM_FEE4						0x9534//费率4
#define CON_DI_TYPE_MPVAR1_LM_BLOCK						0x953F

#define CON_DI_TYPE_MPVAR4_LM							0x9540//四象限无功总电能（上月）
#define CON_DI_TYPE_MPVAR4_LM_FEE1						0x9541//费率1
#define CON_DI_TYPE_MPVAR4_LM_FEE2						0x9542//费率2
#define CON_DI_TYPE_MPVAR4_LM_FEE3						0x9543//费率3
#define CON_DI_TYPE_MPVAR4_LM_FEE4						0x9544//费率4
#define CON_DI_TYPE_MPVAR4_LM_BLOCK						0x954F

#define CON_DI_TYPE_MPVAR2_LM							0x9550//二象限无功总电能（上月）
#define CON_DI_TYPE_MPVAR2_LM_FEE1						0x9551//费率1
#define CON_DI_TYPE_MPVAR2_LM_FEE2						0x9552//费率2
#define CON_DI_TYPE_MPVAR2_LM_FEE3						0x9553//费率3
#define CON_DI_TYPE_MPVAR2_LM_FEE4						0x9554//费率4
#define CON_DI_TYPE_MPVAR2_LM_BLOCK						0x955F

#define CON_DI_TYPE_MPVAR3_LM							0x9560//三象限无功总电能（上月）
#define CON_DI_TYPE_MPVAR3_LM_FEE1						0x9561//费率1
#define CON_DI_TYPE_MPVAR3_LM_FEE2						0x9562//费率2
#define CON_DI_TYPE_MPVAR3_LM_FEE3						0x9563//费率3
#define CON_DI_TYPE_MPVAR3_LM_FEE4						0x9564//费率4
#define CON_DI_TYPE_MPVAR3_LM_BLOCK						0x956F
///////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND					0xA010//正向有功总最大需量
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_FEE1				0xA011//费率1
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_FEE2				0xA012//费率2
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_FEE3				0xA013//费率3
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_FEE4				0xA014//费率4
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_BLOCK				0xA01F

#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND					0xA020//反向有功总最大需量
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_FEE1			0xA021//费率1
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_FEE2			0xA022//费率2
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_FEE3			0xA023//费率3
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_FEE4			0xA024//费率4
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_BLOCK			0xA02F

#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME				0xB010//正向有功总最大需量发生时间
#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_FEE1			0xB011//费率1
#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_FEE2			0xB012//费率2
#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_FEE3			0xB013//费率3
#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_FEE4			0xB014//费率4
#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_BLOCK			0xB01F

#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME				0xB020//反向有功总最大需量发生时间
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_FEE1		0xB021//费率1
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_FEE2		0xB022//费率2
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_FEE3		0xB023//费率3
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_FEE4		0xB024//费率4
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_BLOCK		0xB02F

#define CON_DI_TYPE_MPDIRVARMAXDEMAND					0xA110//正向无功总最大需量
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_FEE1				0xA111//费率1
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_FEE2				0xA112//费率2
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_FEE3				0xA113//费率3
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_FEE4				0xA114//费率4
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_BLOCK				0xA11F

#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND					0xA120//反向无功总最大需量
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_FEE1			0xA121//费率1
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_FEE2			0xA122//费率2
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_FEE3			0xA123//费率3
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_FEE4			0xA124//费率4
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_BLOCK			0xA12F

#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME				0xB110//正向无功总最大需量发生时间
#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_FEE1			0xB111//费率1
#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_FEE2			0xB112//费率2
#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_FEE3			0xB113//费率3
#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_FEE4			0xB114//费率4
#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_BLOCK			0xB11F

#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME				0xB120//反向无功总最大需量发生时间
#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_FEE1		0xB121//费率1
#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_FEE2		0xB122//费率2
#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_FEE3		0xB123//费率3
#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_FEE4		0xB124//费率4
#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_BLOCK		0xB12F

///////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_LM				0xA410//正向有功总最大需量（上月）
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_LM_FEE1			0xA411//费率1
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_LM_FEE2			0xA412//费率2
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_LM_FEE3			0xA413//费率3
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_LM_FEE4			0xA414//费率4
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_LM_BLOCK			0xA41F
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_LM				0xA420//反向有功总最大需量（上月）
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_LM_FEE1			0xA421//费率1
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_LM_FEE2			0xA422//费率2
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_LM_FEE3			0xA423//费率3
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_LM_FEE4			0xA424//费率4
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_LM_BLOCK		0xA42F

#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_LM			0xB410//正向有功总最大需量发生时间（上月）
#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_LM_FEE1		0xB411//费率1
#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_LM_FEE2		0xB412//费率2
#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_LM_FEE3		0xB413//费率3
#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_LM_FEE4		0xB414//费率4
#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_LM_BLOCK		0xB41F
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_LM			0xB420//反向有功总最大需量发生时间（上月）
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_LM_FEE1		0xB421//费率1
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_LM_FEE2		0xB422//费率2
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_LM_FEE3		0xB423//费率3
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_LM_FEE4		0xB424//费率4
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_LM_BLOCK	0xB42F

#define CON_DI_TYPE_MPDIRVARMAXDEMAND_LM				0xA510//正向无功总最大需量（上月）
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_LM_FEE1			0xA511//费率1
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_LM_FEE2			0xA512//费率2
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_LM_FEE3			0xA513//费率3
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_LM_FEE4			0xA514//费率4
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_LM_BLOCK			0xA51F
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_LM				0xA520//反向无功总最大需量（上月）
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_LM_FEE1			0xA521//费率1
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_LM_FEE2			0xA522//费率2
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_LM_FEE3			0xA523//费率3
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_LM_FEE4			0xA524//费率4
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_LM_BLOCK		0xA52F

#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_LM			0xB510//正向无功总最大需量发生时间（上月）
#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_LM_FEE1		0xB511//费率1
#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_LM_FEE2		0xB512//费率2
#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_LM_FEE3		0xB513//费率3
#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_LM_FEE4		0xB514//费率4
#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_LM_BLOCK		0xB51F
#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_LM			0xB520//反向无功总最大需量发生时间（上月）
#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_LM_FEE1		0xB521//费率1
#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_LM_FEE2		0xB522//费率2
#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_LM_FEE3		0xB523//费率3
#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_LM_FEE4		0xB524//费率4
#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_LM_BLOCK	0xB52F

//////////////////////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPLATELYPROGTIME					0xB210//最近一次编程时间
#define CON_DI_TYPE_MPLATELYMAXDEMANDCLEARTIME			0xB211//最近一次最大需量清零时间
#define CON_DI_TYPE_MPPROGTIMETIMES						0xB212//编程次数
#define CON_DI_TYPE_MPMAXDEMANDCLEARTIMES				0xB213//最大需量清零次数
#define CON_DI_TYPE_MPBATWORKTIME						0xB214//电池工作时间
#define CON_DI_TYPE_MPMETERCLEARTIMES					0xB215//电表清零总次数
#define CON_DI_TYPE_MPLATELYMETERCLEARTIME				0xB216//最近一次电表清零发生时刻
#define CON_DI_TYPE_MPEVENTCLEARTIMES					0xB217//事件清零总次数
#define CON_DI_TYPE_MPLATELYEVENTCLEARTIME				0xB218//最近一次事件清零发生时刻
#define CON_DI_TYPE_MPTIMINGTIMES							0xB219//校时总次数
#define CON_DI_TYPE_MPLATELYTIMINGTIME					0xB21A//最近一次校时发生时刻
#define CON_DI_TYPE_MPB21F_BLOCK						0xB21F

#define CON_DI_TYPE_MPVOLBREAKNUM						0xB310
#define CON_DI_TYPE_MPVOLBREAKNUMA						0xB311
#define CON_DI_TYPE_MPVOLBREAKNUMB						0xB312
#define CON_DI_TYPE_MPVOLBREAKNUMC						0xB313
#define CON_DI_TYPE_MPB31F_BLOCK						0xB31F		//断相次数

#define CON_DI_TYPE_MPVOLBREAKTIME						0xB320
#define CON_DI_TYPE_MPVOLBREAKTIMEA						0xB321
#define CON_DI_TYPE_MPVOLBREAKTIMEB						0xB322
#define CON_DI_TYPE_MPVOLBREAKTIMEC						0xB323
#define CON_DI_TYPE_MPB32F_BLOCK						0xB32F		//累计断相时间

#define CON_DI_TYPE_MPLASTVOLBREAKBEGTIME				0xB330
#define CON_DI_TYPE_MPLASTVOLBREAKBEGTIMEA				0xB331
#define CON_DI_TYPE_MPLASTVOLBREAKBEGTIMEB				0xB332
#define CON_DI_TYPE_MPLASTVOLBREAKBEGTIMEC				0xB333
#define CON_DI_TYPE_MPB33F_BLOCK						0xB33F		//最近一次断相起始时刻

#define CON_DI_TYPE_MPLASTVOLBREAKENDTIME				0xB340
#define CON_DI_TYPE_MPLASTVOLBREAKENDTIMEA				0xB341
#define CON_DI_TYPE_MPLASTVOLBREAKENDTIMEB				0xB342
#define CON_DI_TYPE_MPLASTVOLBREAKENDTIMEC				0xB343
#define CON_DI_TYPE_MPB34F_BLOCK						0xB34F		//最近一次断相结束时刻

///////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPVOLA								0xB611//A相电压
#define CON_DI_TYPE_MPVOLB								0xB612//B相电压
#define CON_DI_TYPE_MPVOLC								0xB613//C相电压
#define CON_DI_TYPE_MPVOL_BLOCK							0xB61F//电压数据块

#define CON_DI_TYPE_MPCURA								0xB621//A相电流
#define CON_DI_TYPE_MPCURB								0xB622//B相电流
#define CON_DI_TYPE_MPCURC								0xB623//C相电流 
#define CON_DI_TYPE_MPCUR_BLOCK							0xB62F//电流数据块

#define CON_DI_TYPE_MPINSTANTPOW						0xB630//瞬时有功功率
#define CON_DI_TYPE_MPINSTANTPOWA						0xB631//A相有功功率
#define CON_DI_TYPE_MPINSTANTPOWB						0xB632//B相有功功率
#define CON_DI_TYPE_MPINSTANTPOWC						0xB633//C相有功功率
#define CON_DI_TYPE_MPINSTANTPOW_BLOCK					0xB63F//

#define CON_DI_TYPE_MPINSTANTVAR						0xB640//瞬时无功功率
#define CON_DI_TYPE_MPINSTANTVARA						0xB641//A相无功功率
#define CON_DI_TYPE_MPINSTANTVARB						0xB642//B相无功功率
#define CON_DI_TYPE_MPINSTANTVARC						0xB643//C相无功功率
#define CON_DI_TYPE_MPINSTANTVAR_BLOCK					0xB64F//

#define	CON_DI_TYPE_MPPOWRATE							0xB650//总功率因素
#define	CON_DI_TYPE_MPPOWRATEA							0xB651//A相功率因素
#define	CON_DI_TYPE_MPPOWRATEB							0xB652//B相功率因素
#define	CON_DI_TYPE_MPPOWRATEC							0xB653//C相功率因素
#define	CON_DI_TYPE_MPPOWRATE_BLOCK						0xB65F//

#define CON_DI_TYPE_MPINSTANTSTOTAL						0xB660//瞬时视在功率
#define CON_DI_TYPE_MPINSTANTSA						    0xB661//A相视在功率
#define CON_DI_TYPE_MPINSTANTSB						    0xB662//B相视在功率
#define CON_DI_TYPE_MPINSTANTSC						    0xB663//C相视在功率
#define CON_DI_TYPE_MPINSTANTS_BLOCK					0xB66F//

///////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPPOWCONST							0xC030//有功常数
#define CON_DI_TYPE_MPVARCONST							0xC031//无功常数
#define CON_DI_TYPE_MPCONST_BLOCK						0xC03F//

#define CON_DI_TYPE_MPFEERATE1							0xC331//费率1
#define CON_DI_TYPE_MPFEERATE2							0xC332//费率2
#define CON_DI_TYPE_MPFEERATE3							0xC333//费率3
#define CON_DI_TYPE_MPFEERATE4							0xC334//费率4
#define CON_DI_TYPE_MPFEERATE5							0xC335//费率5
#define CON_DI_TYPE_MPFEERATE6							0xC336//费率6
#define CON_DI_TYPE_MPFEERATE7							0xC337//费率7
#define CON_DI_TYPE_MPFEERATE8							0xC338//费率8
#define CON_DI_TYPE_MPFEERATE_BLOCK						0xC33F	
///////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPDATEANDWEEK						0xC010//日期及周次
#define CON_DI_TYPE_MPTIME								0xC011//时间
#define CON_DI_TYPE_MPDATETIME_BLOCK					0xC01F//
#define CON_DI_TYPE_MPMETERSTATFLAG						0xC020//电表运行状态字
#define CON_DI_TYPE_MPNETSTATFLAG						0xC021//电网运行状态字
#define CON_DI_TYPE_MPCO2F_BLOCK						0xC02F
#define CON_DI_TYPE_MPCOPYDAYTIME						0xC117//抄表日
#define CON_DI_TYPE_MPC11F_BLOCK						0xC11F

//---------- dlt645-2007 规约对应数据 0x5000 0x6FFF 支持8192个 start ------------
#define CON_DI_TYPE_CU_LOST								0x5000//(当前)铜损有功总电能补偿量
#define CON_DI_TYPE_FE_LOST								0x5001//(当前)铁损有功总电能补偿量
#define CON_DI_TYPE_DIRPOW_A							0x5011//(当前)A相正向有功电能
#define CON_DI_TYPE_DIRPOW_B							0x5012//(当前)B相正向有功电能
#define CON_DI_TYPE_DIRPOW_C							0x5013//(当前)C相正向有功电能
#define CON_DI_TYPE_UNDIRPOW_A							0x5021//(当前)A相反向有功电能
#define CON_DI_TYPE_UNDIRPOW_B							0x5022//(当前)B相反向有功电能
#define CON_DI_TYPE_UNDIRPOW_C							0x5023//(当前)C相反向有功电能
#define CON_DI_TYPE_SUMVAR1_A							0x5031//(当前)A相组合无功1电能
#define CON_DI_TYPE_SUMVAR1_B							0x5032//(当前)B相组合无功1电能
#define CON_DI_TYPE_SUMVAR1_C							0x5033//(当前)C相组合无功1电能
#define CON_DI_TYPE_SUMVAR2_A							0x5041//(当前)A相组合无功2电能
#define CON_DI_TYPE_SUMVAR2_B							0x5042//(当前)B相组合无功2电能
#define CON_DI_TYPE_SUMVAR2_C							0x5043//(当前)C相组合无功2电能
#define CON_DI_TYPE_MP500F_BLOCK						0x500F
#define CON_DI_TYPE_MP501F_BLOCK						0x501F
#define CON_DI_TYPE_MP502F_BLOCK						0x502F
#define CON_DI_TYPE_MP503F_BLOCK						0x503F
#define CON_DI_TYPE_MP504F_BLOCK						0x504F

#define CON_DI_TYPE_METER_STAT_FLAG_1					0x5051//电表运行状态字
#define CON_DI_TYPE_METER_STAT_FLAG_2					0x5052//电表运行状态字
#define CON_DI_TYPE_METER_STAT_FLAG_3					0x5053//电表运行状态字
#define CON_DI_TYPE_METER_STAT_FLAG_4					0x5054//电表运行状态字
#define CON_DI_TYPE_METER_STAT_FLAG_5					0x5055//电表运行状态字
#define CON_DI_TYPE_METER_STAT_FLAG_6					0x5056//电表运行状态字
#define CON_DI_TYPE_METER_STAT_FLAG_7					0x5057//电表运行状态字

#define CON_DI_TYPE_METER_CHANGE_FLAG_1					0x5058//电表运行状态字变位标志
#define CON_DI_TYPE_METER_CHANGE_FLAG_2					0x5059//电表运行状态字变位标志
#define CON_DI_TYPE_METER_CHANGE_FLAG_3					0x505A//电表运行状态字变位标志
#define CON_DI_TYPE_METER_CHANGE_FLAG_4					0x505B//电表运行状态字变位标志
#define CON_DI_TYPE_METER_CHANGE_FLAG_5					0x505C//电表运行状态字变位标志
#define CON_DI_TYPE_METER_CHANGE_FLAG_6					0x505D//电表运行状态字变位标志
#define CON_DI_TYPE_METER_CHANGE_FLAG_7					0x505E//电表运行状态字变位标志

#define CON_DI_TYPE_METER_STAT_FLAG_BLOCK				0x505F
#define CON_DI_TYPE_METER_OPEN_SWITCH                   0x5060//（上1次）跳闸发生时刻
#define CON_DI_TYPE_METER_CLOSE_SWITCH                  0x5061//（上1次）合闸发生时刻

#define CON_DI_TYPE_METER_REMAIN_MONEY                  0x5062//（当前）剩余金额
#define CON_DI_TYPE_METER_OVERDRAFT                     0x5063//（当前）透支金额
#define CON_DI_TYPE_METER_BUYPOW_TIMES_TOTAL            0x5064//上1次购电后总购电次数
#define CON_DI_TYPE_METER_BUYPOW_MENEY_TOTAL            0x5065//上1次购电后累计购电金额

#define CON_DI_TYPE_METER_HOUR_FREEZE_TIME              0x5066  //（上1次）整点冻结时间
#define CON_DI_TYPE_METER_HOUR_FREEZE_DIRPOWTOL         0x5067  //（上1次）整点冻结正向有功总电能
#define CON_DI_TYPE_METER_HOUR_FREEZE_REVPOWTOL         0x5068  //（上1次）整点冻结反向有功总电能
#define CON_DI_TYPE_METER_HOUR_FREEZE_BLOCK             0x5069  //（上1次）整点冻结数据块

#define CON_DI_TYPE_METER_DAY_FREEZE_DI_START		0x506A  //（上1次）日冻结起始数据项标识
#define CON_DI_TYPE_METER_DAY_FREEZE_TIME               0x506a  //（上1次）日冻结时间
#define CON_DI_TYPE_METER_DAY_FREEZE_DIRPOW               0x506b  //（上1次）日冻结正向有功电能数据
#define CON_DI_TYPE_METER_DAY_FREEZE_REVPOW               0x506c  //（上1次）日冻结反向有功电能数据
#define CON_DI_TYPE_METER_DAY_FREEZE_DIRVAR               0x506d  //（上1次）日冻结组合无功1电能数据
#define CON_DI_TYPE_METER_DAY_FREEZE_REVVAR               0x506e  //（上1次）日冻结组合无功2电能数据
#define CON_DI_TYPE_METER_DAY_FREEZE_VAR1               0x506f    //（上1次）日冻结第一象限无功电能数据
#define CON_DI_TYPE_METER_DAY_FREEZE_VAR2               0x5071  //（上1次）日冻结第二象限无功电能数据
#define CON_DI_TYPE_METER_DAY_FREEZE_VAR3               0x5072  //（上1次）日冻结第三象限无功电能数据
#define CON_DI_TYPE_METER_DAY_FREEZE_VAR4               0x5073  //（上1次）日冻结第四象限无功电能数据
#define CON_DI_TYPE_METER_DAY_FREEZE_DIRPOWDEMAND               0x5074  //（上1次）日冻结正向有功最大需量及发生时间数据：
#define CON_DI_TYPE_METER_DAY_FREEZE_REVPOWDEMAND               0x5075  //（上1次）日冻结反向有功最大需量及发生时间数据：
#define CON_DI_TYPE_METER_DAY_FREEZE_POWER               0x5076  //（上1次）日冻结变量数据：功率
#define CON_DI_TYPE_METER_DAY_FREEZE_DI_END		0x5076  //（上1次）日冻结束数据项标识


#define CON_DI_TYPE_CU_LOST_LM							0x6000//(上1结算日)铜损有功总电能补偿量
#define CON_DI_TYPE_FE_LOST_LM							0x6001//(上1结算日)铁损有功总电能补偿量
#define CON_DI_TYPE_DIRPOW_A_LM							0x6011//(上1结算日)A相正向有功电能
#define CON_DI_TYPE_DIRPOW_B_LM							0x6012//(上1结算日)B相正向有功电能
#define CON_DI_TYPE_DIRPOW_C_LM							0x6013//(上1结算日)C相正向有功电能
#define CON_DI_TYPE_UNDIRPOW_A_LM						0x6021//(上1结算日)A相反向有功电能
#define CON_DI_TYPE_UNDIRPOW_B_LM						0x6022//(上1结算日)B相反向有功电能
#define CON_DI_TYPE_UNDIRPOW_C_LM						0x6023//(上1结算日)C相反向有功电能
#define CON_DI_TYPE_SUMVAR1_A_LM						0x6031//(上1结算日)A相组合无功1电能
#define CON_DI_TYPE_SUMVAR1_B_LM						0x6032//(上1结算日)B相组合无功1电能
#define CON_DI_TYPE_SUMVAR1_C_LM						0x6033//(上1结算日)C相组合无功1电能
#define CON_DI_TYPE_SUMVAR2_A_LM						0x6041//(上1结算日)A相组合无功2电能
#define CON_DI_TYPE_SUMVAR2_B_LM						0x6042//(上1结算日)B相组合无功2电能
#define CON_DI_TYPE_SUMVAR2_C_LM						0x6043//(上1结算日)C相组合无功2电能
#define CON_DI_TYPE_MP600F_LM_BLOCK                     0x600F
#define CON_DI_TYPE_MP601F_LM_BLOCK                     0x601F
#define CON_DI_TYPE_MP602F_LM_BLOCK                     0x602F
#define CON_DI_TYPE_MP603F_LM_BLOCK                     0x603F
#define CON_DI_TYPE_MP604F_LM_BLOCK                     0x604F

//谐波数据在特殊测量点=0位置访问，
//内表其他数据按照内表测量点访问
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_TOL      0x6050//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_1      0x6051//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_2      0x6052//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_3      0x6053//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_4      0x6054//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_5      0x6055//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_6      0x6056//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_7      0x6057//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_8      0x6058//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_9      0x6059//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_10      0x605a//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_11      0x605b//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_12      0x605c//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_13      0x605d//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_14      0x605e//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_15      0x605f//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_16      0x6060//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_17      0x6061//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_18      0x6062//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_19      0x6063//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_20      0x6064//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_21      0x6065//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_BLOCK   0x6066//电压谐波有效值数据块


#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_TOL  0x6070//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_1      0x6071//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_2      0x6072//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_3      0x6073//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_4      0x6074//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_5      0x6075//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_6      0x6076//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_7      0x6077//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_8      0x6078//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_9      0x6079//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_10      0x607a//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_11      0x607b//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_12      0x607c//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_13      0x607d//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_14      0x607e//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_15      0x607f//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_16      0x6080//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_17      0x6081//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_18      0x6082//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_19      0x6083//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_20      0x6084//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_21      0x6085//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_BLOCK   0x6086//电压谐波有效值数据块

#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_TOL  0x6090//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_1      0x6091//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_2      0x6092//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_3      0x6093//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_4      0x6094//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_5      0x6095//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_6      0x6096//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_7      0x6097//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_8      0x6098//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_9      0x6099//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_10      0x609a//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_11      0x609b//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_12      0x609c//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_13      0x609d//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_14      0x609e//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_15      0x609f//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_16      0x60a0//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_17      0x60a1//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_18      0x60a2//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_19      0x60a3//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_20      0x60a4//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_21      0x60a5//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_BLOCK   0x60a6//电压谐波有效值数据块

#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_TOL  0x60b0//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_1      0x60b1//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_2      0x60b2//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_3      0x60b3//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_4      0x60b4//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_5      0x60b5//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_6      0x60b6//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_7      0x60b7//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_8      0x60b8//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_9      0x60b9//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_10      0x60ba//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_11      0x60bb//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_12      0x60bc//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_13      0x60bd//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_14      0x60be//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_15      0x60bf//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_16      0x60c0//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_17      0x60c1//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_18      0x60c2//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_19      0x60c3//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_20      0x60c4//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_21     0x60c5//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_BLOCK   0x60c6//电压谐波有效值数据块

#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_TOL  0x60d0//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_1      0x60d1//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_2      0x60d2//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_3      0x60d3//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_4      0x60d4//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_5      0x60d5//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_6      0x60d6//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_7      0x60d7//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_8      0x60d8//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_9      0x60d9//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_10      0x60da//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_11      0x60db//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_12      0x60dc//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_13      0x60dd//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_14      0x60de//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_15      0x60df//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_16      0x60e0//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_17      0x60e1//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_18      0x60e2//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_19      0x60e3//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_20      0x60e4//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_21     0x60e5//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_BLOCK   0x60e6//电压谐波有效值数据块

#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_TOL  0x60f0//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_1      0x60f1//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_2      0x60f2//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_3      0x60f3//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_4      0x60f4//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_5      0x60f5//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_6      0x60f6//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_7      0x60f7//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_8      0x60f8//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_9      0x60f9//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_10      0x60fa//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_11      0x60fb//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_12      0x60fc//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_13      0x60fd//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_14      0x60fe//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_15      0x60ff//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_16      0x6100//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_17      0x6101//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_18      0x6102//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_19      0x6103//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_20      0x6104//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_21     0x6105//电压谐波有效值数据块
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_BLOCK   0x6106//电压谐波有效值数据块

////////////////////////////////////////

#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_TOL  0x6110//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_1      0x6111//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_2      0x6112//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_3      0x6113//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_4      0x6114//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_5      0x6115//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_6      0x6116//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_7      0x6117//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_8      0x6118//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_9      0x6119//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_10      0x611a//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_11      0x611b//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_12      0x611c//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_13      0x611d//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_14      0x611e//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_15      0x611f//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_16      0x6120//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_17      0x6121//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_18      0x6122//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_19      0x6123//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_20      0x6124//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_21      0x6125//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_BLOCK  0x6126 //电压谐波含有率数据块

#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_TOL  0x6130//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_1      0x6131//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_2      0x6132//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_3      0x6133//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_4      0x6134//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_5      0x6135//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_6      0x6136//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_7      0x6137//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_8      0x6138//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_9      0x6139//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_10      0x613a//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_11      0x613b//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_12      0x613c//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_13      0x613d//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_14      0x613e//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_15      0x613f//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_16      0x6140//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_17      0x6141//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_18      0x6142//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_19      0x6143//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_20      0x6144//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_21      0x6145//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_BLOCK  0x6146 //电压谐波含有率数据块

#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_TOL  0x6150//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_1      0x6151//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_2      0x6152//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_3      0x6153//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_4      0x6154//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_5      0x6155//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_6      0x6156//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_7      0x6157//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_8      0x6158//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_9      0x6159//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_10      0x615a//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_11      0x615b//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_12      0x615c//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_13      0x615d//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_14      0x615e//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_15      0x615f//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_16      0x6160//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_17      0x6161//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_18      0x6162//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_19      0x6163//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_20      0x6164//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_21      0x6165//电压谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_BLOCK  0x6166 //电压谐波含有率数据块

#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_TOL      0x6170//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_1      0x6171//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_2      0x6172//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_3      0x6173//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_4      0x6174//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_5      0x6175//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_6      0x6176//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_7      0x6177//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_8      0x6178//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_9      0x6179//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_10      0x617a//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_11      0x617b//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_12      0x617c//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_13      0x617d//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_14      0x617e//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_15      0x617f//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_16      0x6180//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_17      0x6181//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_18      0x6182//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_19      0x6183//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_20      0x6184//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_21      0x6185//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_BLOCK   0x6186//电流谐波含有率数据块

#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_TOL      0x6190//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_1      0x6191//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_2      0x6192//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_3      0x6193//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_4      0x6194//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_5      0x6195//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_6      0x6196//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_7      0x6197//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_8      0x6198//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_9      0x6199//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_10      0x619a//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_11      0x619b//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_12      0x619c//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_13      0x619d//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_14      0x619e//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_15      0x619f//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_16      0x61a0//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_17      0x61a1//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_18      0x61a2//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_19      0x61a3//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_20      0x61a4//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_21      0x61a5//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_BLOCK   0x61a6//电流谐波含有率数据块

#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_TOL      0x61b0//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_1      0x61b1//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_2      0x61b2//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_3      0x61b3//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_4      0x61b4//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_5      0x61b5//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_6      0x61b6//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_7      0x61b7//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_8      0x61b8//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_9      0x61b9//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_10      0x61ba//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_11      0x61bb//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_12      0x61bc//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_13      0x61bd//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_14      0x61be//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_15      0x61bf//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_16      0x61c0//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_17      0x61c1//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_18      0x61c2//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_19      0x61c3//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_20      0x61c4//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_21      0x61c5//电流谐波含有率数据块
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_BLOCK   0x61c6//电流谐波含有率数据块

#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_TOL_MAX_TIME    0x6200//电压谐波含有率最大值和发生时间
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_1_MAX_TIME      0x6201
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_2_MAX_TIME      0x6202
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_3_MAX_TIME      0x6203
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_4_MAX_TIME      0x6204
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_5_MAX_TIME      0x6205
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_6_MAX_TIME      0x6206
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_7_MAX_TIME      0x6207
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_8_MAX_TIME      0x6208
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_9_MAX_TIME      0x6209
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_10_MAX_TIME      0x620A
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_11_MAX_TIME      0x620B
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_12_MAX_TIME      0x620C
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_13_MAX_TIME      0x620D
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_14_MAX_TIME      0x620E
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_15_MAX_TIME      0x620F
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_16_MAX_TIME      0x6210
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_17_MAX_TIME      0x6211
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_18_MAX_TIME      0x6212
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_19_MAX_TIME      0x6213
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_20_MAX_TIME      0x6214

#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_TOL_MAX_TIME    0x6220
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_1_MAX_TIME      0x6221
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_2_MAX_TIME      0x6222
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_3_MAX_TIME      0x6223
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_4_MAX_TIME      0x6224
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_5_MAX_TIME      0x6225
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_6_MAX_TIME      0x6226
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_7_MAX_TIME      0x6227
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_8_MAX_TIME      0x6228
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_9_MAX_TIME      0x6229
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_10_MAX_TIME      0x622A
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_11_MAX_TIME      0x622B
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_12_MAX_TIME      0x622C
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_13_MAX_TIME      0x622D
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_14_MAX_TIME      0x622E
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_15_MAX_TIME      0x622F
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_16_MAX_TIME      0x6230
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_17_MAX_TIME      0x6231
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_18_MAX_TIME      0x6232
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_19_MAX_TIME      0x6233
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_20_MAX_TIME      0x6234

#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_TOL_MAX_TIME    0x6240
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_1_MAX_TIME      0x6241
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_2_MAX_TIME      0x6242
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_3_MAX_TIME      0x6243
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_4_MAX_TIME      0x6244
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_5_MAX_TIME      0x6245
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_6_MAX_TIME      0x6246
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_7_MAX_TIME      0x6247
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_8_MAX_TIME      0x6248
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_9_MAX_TIME      0x6249
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_10_MAX_TIME      0x624A
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_11_MAX_TIME      0x624B
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_12_MAX_TIME      0x624C
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_13_MAX_TIME      0x624D
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_14_MAX_TIME      0x624E
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_15_MAX_TIME      0x624F
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_16_MAX_TIME      0x6250
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_17_MAX_TIME      0x6251
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_18_MAX_TIME      0x6252
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_19_MAX_TIME      0x6253
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_20_MAX_TIME      0x6254

#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_TOL_MAX_TIME    0x6260//电流谐波最大值和发生时间
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_1_MAX_TIME      0x6261
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_2_MAX_TIME      0x6262
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_3_MAX_TIME      0x6263
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_4_MAX_TIME      0x6264
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_5_MAX_TIME      0x6265
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_6_MAX_TIME      0x6266
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_7_MAX_TIME      0x6267
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_8_MAX_TIME      0x6268
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_9_MAX_TIME      0x6269
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_10_MAX_TIME      0x626A
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_11_MAX_TIME      0x626B
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_12_MAX_TIME      0x626C
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_13_MAX_TIME      0x626D
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_14_MAX_TIME      0x626E
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_15_MAX_TIME      0x626F
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_16_MAX_TIME      0x6270
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_17_MAX_TIME      0x6271
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_18_MAX_TIME      0x6272
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_19_MAX_TIME      0x6273
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_20_MAX_TIME      0x6274

#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_TOL_MAX_TIME    0x6280
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_1_MAX_TIME      0x6281
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_2_MAX_TIME      0x6282
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_3_MAX_TIME      0x6283
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_4_MAX_TIME      0x6284
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_5_MAX_TIME      0x6285
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_6_MAX_TIME      0x6286
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_7_MAX_TIME      0x6287
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_8_MAX_TIME      0x6288
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_9_MAX_TIME      0x6289
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_10_MAX_TIME      0x628A
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_11_MAX_TIME      0x628B
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_12_MAX_TIME      0x628C
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_13_MAX_TIME      0x628D
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_14_MAX_TIME      0x628E
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_15_MAX_TIME      0x628F
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_16_MAX_TIME      0x6290
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_17_MAX_TIME      0x6291
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_18_MAX_TIME      0x6292
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_19_MAX_TIME      0x6293
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_20_MAX_TIME      0x6294

#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_TOL_MAX_TIME    0x62A0
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_1_MAX_TIME      0x62A1
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_2_MAX_TIME      0x62A2
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_3_MAX_TIME      0x62A3
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_4_MAX_TIME      0x62A4
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_5_MAX_TIME      0x62A5
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_6_MAX_TIME      0x62A6
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_7_MAX_TIME      0x62A7
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_8_MAX_TIME      0x62A8
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_9_MAX_TIME      0x62A9
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_10_MAX_TIME      0x62AA
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_11_MAX_TIME      0x62AB
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_12_MAX_TIME      0x62AC
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_13_MAX_TIME      0x62AD
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_14_MAX_TIME      0x62AE
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_15_MAX_TIME      0x62AF
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_16_MAX_TIME      0x62B0
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_17_MAX_TIME      0x62B1
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_18_MAX_TIME      0x62B2
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_19_MAX_TIME      0x62B3
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_20_MAX_TIME      0x62B4

#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_TOL_OVER_TIME    0x6300//电压谐波含有率越限累计时间
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_1_OVER_TIME      0x6301
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_2_OVER_TIME      0x6302
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_3_OVER_TIME      0x6303
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_4_OVER_TIME      0x6304
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_5_OVER_TIME      0x6305
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_6_OVER_TIME      0x6306
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_7_OVER_TIME      0x6307
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_8_OVER_TIME      0x6308
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_9_OVER_TIME      0x6309
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_10_OVER_TIME      0x630A
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_11_OVER_TIME      0x630B
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_12_OVER_TIME      0x630C
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_13_OVER_TIME      0x630D
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_14_OVER_TIME      0x630E
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_15_OVER_TIME      0x630F
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_16_OVER_TIME      0x6310
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_17_OVER_TIME      0x6311
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_18_OVER_TIME      0x6312
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_19_OVER_TIME      0x6313
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_20_OVER_TIME      0x6314

#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_TOL_OVER_TIME    0x6320
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_1_OVER_TIME      0x6321
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_2_OVER_TIME      0x6322
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_3_OVER_TIME      0x6323
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_4_OVER_TIME      0x6324
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_5_OVER_TIME      0x6325
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_6_OVER_TIME      0x6326
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_7_OVER_TIME      0x6327
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_8_OVER_TIME      0x6328
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_9_OVER_TIME      0x6329
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_10_OVER_TIME      0x632A
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_11_OVER_TIME      0x632B
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_12_OVER_TIME      0x632C
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_13_OVER_TIME      0x632D
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_14_OVER_TIME      0x632E
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_15_OVER_TIME      0x632F
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_16_OVER_TIME      0x6330
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_17_OVER_TIME      0x6331
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_18_OVER_TIME      0x6332
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_19_OVER_TIME      0x6333
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_20_OVER_TIME      0x6334

#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_TOL_OVER_TIME    0x6340
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_1_OVER_TIME      0x6341
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_2_OVER_TIME      0x6342
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_3_OVER_TIME      0x6343
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_4_OVER_TIME      0x6344
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_5_OVER_TIME      0x6345
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_6_OVER_TIME      0x6346
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_7_OVER_TIME      0x6347
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_8_OVER_TIME      0x6348
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_9_OVER_TIME      0x6349
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_10_OVER_TIME      0x634A
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_11_OVER_TIME      0x634B
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_12_OVER_TIME      0x634C
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_13_OVER_TIME      0x634D
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_14_OVER_TIME      0x634E
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_15_OVER_TIME      0x634F
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_16_OVER_TIME      0x6350
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_17_OVER_TIME      0x6351
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_18_OVER_TIME      0x6352
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_19_OVER_TIME      0x6353
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_20_OVER_TIME      0x6354

#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_TOL_OVER_TIME    0x6360//电流谐波越限累计时间
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_1_OVER_TIME      0x6361
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_2_OVER_TIME      0x6362
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_3_OVER_TIME      0x6363
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_4_OVER_TIME      0x6364
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_5_OVER_TIME      0x6365
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_6_OVER_TIME      0x6366
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_7_OVER_TIME      0x6367
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_8_OVER_TIME      0x6368
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_9_OVER_TIME      0x6369
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_10_OVER_TIME      0x636A
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_11_OVER_TIME      0x636B
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_12_OVER_TIME      0x636C
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_13_OVER_TIME      0x636D
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_14_OVER_TIME      0x636E
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_15_OVER_TIME      0x636F
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_16_OVER_TIME      0x6370
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_17_OVER_TIME      0x6371
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_18_OVER_TIME      0x6372
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_19_OVER_TIME      0x6373
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_20_OVER_TIME      0x6374

#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_TOL_OVER_TIME    0x6380
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_1_OVER_TIME      0x6381
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_2_OVER_TIME      0x6382
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_3_OVER_TIME      0x6383
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_4_OVER_TIME      0x6384
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_5_OVER_TIME      0x6385
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_6_OVER_TIME      0x6386
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_7_OVER_TIME      0x6387
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_8_OVER_TIME      0x6388
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_9_OVER_TIME      0x6389
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_10_OVER_TIME      0x638A
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_11_OVER_TIME      0x638B
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_12_OVER_TIME      0x638C
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_13_OVER_TIME      0x638D
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_14_OVER_TIME      0x638E
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_15_OVER_TIME      0x638F
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_16_OVER_TIME      0x6390
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_17_OVER_TIME      0x6391
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_18_OVER_TIME      0x6392
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_19_OVER_TIME      0x6393
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_20_OVER_TIME      0x6394

#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_TOL_OVER_TIME    0x63A0
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_1_OVER_TIME      0x63A1
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_2_OVER_TIME      0x63A2
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_3_OVER_TIME      0x63A3
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_4_OVER_TIME      0x63A4
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_5_OVER_TIME      0x63A5
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_6_OVER_TIME      0x63A6
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_7_OVER_TIME      0x63A7
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_8_OVER_TIME      0x63A8
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_9_OVER_TIME      0x63A9
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_10_OVER_TIME      0x63AA
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_11_OVER_TIME      0x63AB
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_12_OVER_TIME      0x63AC
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_13_OVER_TIME      0x63AD
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_14_OVER_TIME      0x63AE
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_15_OVER_TIME      0x63AF
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_16_OVER_TIME      0x63B0
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_17_OVER_TIME      0x63B1
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_18_OVER_TIME      0x63B2
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_19_OVER_TIME      0x63B3
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_20_OVER_TIME      0x63B4

//相位角定义(都是对应Ua)
//#define CON_DI_TYPE_MPPHS_ANGLE_VAL_A                                     0x6400   
//#define CON_DI_TYPE_MPPHS_ANGLE_VAL_B                                     0x6401
//#define CON_DI_TYPE_MPPHS_ANGLE_VAL_C                                     0x6402
#define CON_DI_TYPE_MPPHS_ANGLE_VAL_ALL                                 0x640F

//#define CON_DI_TYPE_MPPHS_ANGLE_I_A                                         0x6410
//#define CON_DI_TYPE_MPPHS_ANGLE_I_B                                         0x6411
//#define CON_DI_TYPE_MPPHS_ANGLE_I_C                                         0x6412
#define CON_DI_TYPE_MPPHS_ANGLE_I_ALL                                     0x641F

//---------- dlt645-2007 规约对应数据 0x5000 0x6FFF 支持8192个 end   ------------

//---------- 自定义 0x7600 0x7FFF 支持2560个 -----------------------
#define CON_DI_TYPE_MPINSTANTPOW_ZEROTIME				0x7620//瞬时零有功功率发生时间
#define CON_DI_TYPE_MPINSTANTPOWA_ZEROTIME				0x7621//A相零有功功率发生时间
#define CON_DI_TYPE_MPINSTANTPOWB_ZEROTIME				0x7622//B相零有功功率发生时间
#define CON_DI_TYPE_MPINSTANTPOWC_ZEROTIME				0x7623//C相零有功功率发生时间

#define CON_DI_TYPE_MPINSTANTPOW_MAX					0x7630//瞬时最大有功功率
#define CON_DI_TYPE_MPINSTANTPOWA_MAX					0x7631//A相最大有功功率
#define CON_DI_TYPE_MPINSTANTPOWB_MAX					0x7632//B相最大有功功率
#define CON_DI_TYPE_MPINSTANTPOWC_MAX					0x7633//C相最大有功功率

#define CON_DI_TYPE_MPINSTANTPOW_MAXTIME				0x7640//瞬时最大有功功率发生时间
#define CON_DI_TYPE_MPINSTANTPOWA_MAXTIME				0x7641//A相最大有功功率发生时间
#define CON_DI_TYPE_MPINSTANTPOWB_MAXTIME				0x7642//B相最大有功功率发生时间
#define CON_DI_TYPE_MPINSTANTPOWC_MAXTIME				0x7643//C相最大有功功率发生时间

#define CON_DI_TYPE_MPPOWMAXDEMAND						0x7650//正向有功总最大需量
#define CON_DI_TYPE_MPPOWMAXDEMANDA						0x7651
#define CON_DI_TYPE_MPPOWMAXDEMANDB						0x7652
#define CON_DI_TYPE_MPPOWMAXDEMANDC						0x7653

#define CON_DI_TYPE_MPPOWMAXDEMAND_TIME					0x7660//正向有功总最大需量发生时间
#define CON_DI_TYPE_MPPOWMAXDEMANDA_TIME				0x7661
#define CON_DI_TYPE_MPPOWMAXDEMANDB_TIME				0x7662
#define CON_DI_TYPE_MPPOWMAXDEMANDC_TIME				0x7663

#define CON_DI_TYPE_MPMAXVOLA							0x7671//A相最大电压
#define CON_DI_TYPE_MPMAXVOLB							0x7672//B相最大电压
#define CON_DI_TYPE_MPMAXVOLC							0x7673//C相最大电压

#define CON_DI_TYPE_MPMAXVOLA_TIME						0x7681//A相最大电压发生时间
#define CON_DI_TYPE_MPMAXVOLB_TIME						0x7682//B相最大电压发生时间
#define CON_DI_TYPE_MPMAXVOLC_TIME						0x7683//C相最大电压发生时间

#define CON_DI_TYPE_MPMINVOLA							0x7691//A相最小电压
#define CON_DI_TYPE_MPMINVOLB							0x7692//B相最小电压
#define CON_DI_TYPE_MPMINVOLC							0x7693//C相最小电压

#define CON_DI_TYPE_MPMINVOLA_TIME						0x76A1//A相最小电压发生时间
#define CON_DI_TYPE_MPMINVOLB_TIME						0x76A2//B相最小电压发生时间
#define CON_DI_TYPE_MPMINVOLC_TIME						0x76A3//C相最小电压发生时间

#define CON_DI_TYPE_MP_NORMAL_TIME_VOLA					0x76B1//A相电压合格时长
#define CON_DI_TYPE_MP_NORMAL_TIME_VOLB					0x76B2//B相电压合格时长
#define CON_DI_TYPE_MP_NORMAL_TIME_VOLC					0x76B3//C相电压合格时长

#define CON_DI_TYPE_MP_ERRUP_TIME_VOLA					0x76C1//A相电压越上上限时长
#define CON_DI_TYPE_MP_ERRUP_TIME_VOLB					0x76C2//B相电压越上上限时长
#define CON_DI_TYPE_MP_ERRUP_TIME_VOLC					0x76C3//C相电压越上上限时长

#define CON_DI_TYPE_MP_NORUP_TIME_VOLA					0x76D1//A相电压越上限时长
#define CON_DI_TYPE_MP_NORUP_TIME_VOLB					0x76D2//B相电压越上限时长
#define CON_DI_TYPE_MP_NORUP_TIME_VOLC					0x76D3//C相电压越上限时长

#define CON_DI_TYPE_MP_ERRDOWN_TIME_VOLA				0x76E1//A相电压越下下限时长
#define CON_DI_TYPE_MP_ERRDOWN_TIME_VOLB				0x76E2//B相电压越下下限时长
#define CON_DI_TYPE_MP_ERRDOWN_TIME_VOLC				0x76E3//C相电压越下下限时长

#define CON_DI_TYPE_MP_NORDOWN_TIME_VOLA				0x76F1//A相电压越下限时长
#define CON_DI_TYPE_MP_NORDOWN_TIME_VOLB				0x76F2//B相电压越下限时长
#define CON_DI_TYPE_MP_NORDOWN_TIME_VOLC				0x76F3//C相电压越下限时长

#define CON_DI_TYPE_MP_STAT_TIME_VOLA					0x77A1//A相电压统计时长
#define CON_DI_TYPE_MP_STAT_TIME_VOLB					0x77A2//B相电压统计时长
#define CON_DI_TYPE_MP_STAT_TIME_VOLC					0x77A3//C相电压统计时长

#define CON_DI_TYPE_MP_SUM_VOLA							0x7701//A相电压累加
#define CON_DI_TYPE_MP_SUM_VOLB							0x7702//B相电压累加
#define CON_DI_TYPE_MP_SUM_VOLC							0x7703//C相电压累加

#define CON_DI_TYPE_MP_MAX_CURRA						0x7711//A相最大电流
#define CON_DI_TYPE_MP_MAX_CURRB						0x7712//B相最大电流
#define CON_DI_TYPE_MP_MAX_CURRC						0x7713//C相最大电流
#define CON_DI_TYPE_MP_MAX_CURRN						0x7714//N相最大电流

#define CON_DI_TYPE_MP_MAX_CURRA_TIME					0x7721//A相最大电流发生时间
#define CON_DI_TYPE_MP_MAX_CURRB_TIME					0x7722//B相最大电流发生时间
#define CON_DI_TYPE_MP_MAX_CURRC_TIME					0x7723//C相最大电流发生时间
#define CON_DI_TYPE_MP_MAX_CURRN_TIME					0x7724//N相最大电流发生时间

#define CON_DI_TYPE_MP_ERRUP_TIME_CURRA					0x7731//A相电流越上上限时长
#define CON_DI_TYPE_MP_ERRUP_TIME_CURRB					0x7732//B相电流越上上限时长
#define CON_DI_TYPE_MP_ERRUP_TIME_CURRC					0x7733//C相电流越上上限时长
#define CON_DI_TYPE_MP_ERRUP_TIME_CURRN					0x7734//N相电流越上上限时长

#define CON_DI_TYPE_MP_NORUP_TIME_CURRA					0x7741//A相电流越上限时长
#define CON_DI_TYPE_MP_NORUP_TIME_CURRB					0x7742//B相电流越上限时长
#define CON_DI_TYPE_MP_NORUP_TIME_CURRC					0x7743//C相电流越上限时长
#define CON_DI_TYPE_MP_NORUP_TIME_CURRN					0x7744//N相电流越上限时长

#define CON_DI_TYPE_MP_UNBALANCE_TIME_VOLT				0x7750//电压不平衡时长
#define CON_DI_TYPE_MP_UNBALANCE_TIME_CURR				0x7751//电流不平衡时长
#define CON_DI_TYPE_MP_UNBALANCE_MAX_VOLT				0x7752//电压不平衡最大值
#define CON_DI_TYPE_MP_UNBALANCE_MAX_CURR				0x7753//电流不平衡最大值
#define CON_DI_TYPE_MP_UNBALANCE_MAX_VOLT_TIME			0x7754//电压不平衡最大值发生时间
#define CON_DI_TYPE_MP_UNBALANCE_MAX_CURR_TIME			0x7755//电流不平衡最大值发生时间

#define CON_DI_TYPE_MP_ERRUP_TIME_SPOWER				0x7756//视在功率越上上限时间
#define CON_DI_TYPE_MP_NORUP_TIME_SPOWER				0x7757//视在功率越上限时间

#define CON_DI_TYPE_MP_POWRATESECT1_TIME				0x7758//功率因数分布区域1累计时间（功率因数 < 定值1）
#define CON_DI_TYPE_MP_POWRATESECT2_TIME				0x7759//功率因数分布区域2累计时间（定值1≤功率因数<定值2）
#define CON_DI_TYPE_MP_POWRATESECT3_TIME				0x775A//功率因数分布区域3累计时间（功率因数≥定值2）

#define CON_DI_TYPE_MP_TERPOWERON_TIME					0x7760//终端供电时间
#define CON_DI_TYPE_MP_TERRESET_NUM						0x7761//终端复位累计次数
#define CON_DI_TYPE_MP_MONTHENERGYCTRL_TRIPNUM			0x7762//月电控跳闸次数
#define CON_DI_TYPE_MP_BUYENERGYCTRL_TRIPNUM			0x7763//购电控跳闸次数
#define CON_DI_TYPE_MP_POWERCTRL_TRIPNUM				0x7764//功控跳闸次数
#define CON_DI_TYPE_MP_REMOTECTRL_TRIPNUM				0x7765//遥控跳闸次数
#define CON_DI_TYPE_MP_FLUXBYTES						0x7766//流量字节数
#define CON_DI_TYPE_MP_FLUX_OVER_FLAG				0x7767//流量越限标志
#define CON_DI_TYPE_MP_FLUX_OVER_COUNT				0x7768//流量越限计数器
#define CON_DI_TYPE_MP_DISCONNECT_FLAG				0x7769//上行通信连接控制

#define CON_DI_TYPE_MP_SIG_0							0x7770//信号状态量0
#define CON_DI_TYPE_MP_SIG_1							0x7771//信号状态量1
#define CON_DI_TYPE_MP_SIG_2							0x7772//信号状态量2
#define CON_DI_TYPE_MP_SIG_3							0x7773//信号状态量3
#define CON_DI_TYPE_MP_SIG_4							0x7774//信号状态量4
#define CON_DI_TYPE_MP_SIG_5							0x7775//信号状态量5
#define CON_DI_TYPE_MP_SIG_6							0x7776//信号状态量6
#define CON_DI_TYPE_MP_SIG_7							0x7777//信号状态量7

#define CON_DI_TYPE_MP_ANALOG_DC_1						0x7781//直流模拟量1
#define CON_DI_TYPE_MP_ANALOG_DC_2						0x7782//直流模拟量2

#define CON_DI_TYPE_MP_SUMG_INST_POW					0x7791//总加瞬时有功功率
#define CON_DI_TYPE_MP_SUMG_INST_VAR					0x7792//总加瞬时无功功率
#define CON_DI_TYPE_MP_SUMG_LEFT_POW					0x7793//终端总加当前剩余电量
#define CON_DI_TYPE_MP_SUMG_POW_FIX_VALUE					0x7794//终端总加当前功控定值

#define CON_DI_TYPE_MP_SUMG_POW_TOTAL					0x7800//总加有功电量示值总
#define CON_DI_TYPE_MP_SUMG_POW_FEE1					0x7801//总加有功电量示值1
#define CON_DI_TYPE_MP_SUMG_POW_FEE2					0x7802//总加有功电量示值2
#define CON_DI_TYPE_MP_SUMG_POW_FEE3					0x7803//总加有功电量示值3
#define CON_DI_TYPE_MP_SUMG_POW_FEE4					0x7804//总加有功电量示值4

#define CON_DI_TYPE_MP_SUMG_VAR_TOTAL					0x7810//总加无功电量示值总
#define CON_DI_TYPE_MP_SUMG_VAR_FEE1					0x7811//总加无功电量示值1
#define CON_DI_TYPE_MP_SUMG_VAR_FEE2					0x7812//总加无功电量示值2
#define CON_DI_TYPE_MP_SUMG_VAR_FEE3					0x7813//总加无功电量示值3
#define CON_DI_TYPE_MP_SUMG_VAR_FEE4					0x7814//总加无功电量示值4

#define CON_DI_TYPE_MP_SUMG_LAST_POW_TOTAL				0x7820//总加上一有功电量示值总
#define CON_DI_TYPE_MP_SUMG_LAST_POW_FEE1				0x7821//总加上一有功电量示值1
#define CON_DI_TYPE_MP_SUMG_LAST_POW_FEE2				0x7822//总加上一有功电量示值2
#define CON_DI_TYPE_MP_SUMG_LAST_POW_FEE3				0x7823//总加上一有功电量示值3
#define CON_DI_TYPE_MP_SUMG_LAST_POW_FEE4				0x7824//总加上一有功电量示值4

#define CON_DI_TYPE_MP_SUMG_LAST_VAR_TOTAL				0x7830//总加上一无功电量示值总
#define CON_DI_TYPE_MP_SUMG_LAST_VAR_FEE1				0x7831//总加上一无功电量示值1
#define CON_DI_TYPE_MP_SUMG_LAST_VAR_FEE2				0x7832//总加上一无功电量示值2
#define CON_DI_TYPE_MP_SUMG_LAST_VAR_FEE3				0x7833//总加上一无功电量示值3
#define CON_DI_TYPE_MP_SUMG_LAST_VAR_FEE4				0x7834//总加上一无功电量示值4

#define CON_DI_TYPE_MP_SUMG_MAX_INSTANT_POW				0x7840//最大总加有功统计
#define CON_DI_TYPE_MP_SUMG_MAX_INSTANT_POW_TIME		0x7841//最大总加有功统计发生时间
#define CON_DI_TYPE_MP_SUMG_MIN_INSTANT_POW				0x7842//最小总加有功统计
#define CON_DI_TYPE_MP_SUMG_MIN_INSTANT_POW_TIME		0x7843//最小总加有功统计发生时间
#define CON_DI_TYPE_MP_SUMG_ZEROTIME_INSTANT_POW		0x7844//总加有功为0持续时间

#define CON_DI_TYPE_MP_SUMG_OVERTIME_POWER				0x7845//总加功率超定值时间
#define CON_DI_TYPE_MP_SUMG_OVERTIME_ENERGY				0x7846//总加月电量超定值时间

#define CON_DI_TYPE_MP_SUMG_POWEROVERACCVALTOTAL		0x7847//功率超定值月电量累计
#define CON_DI_TYPE_MP_SUMG_ENERGYOVERACCVALTOTAL		0x7848//月电量超定值月电量累计
#define CON_DI_TYPE_MP_SUMG_POWEROVERSTARTVAL			0x7849//功率超定值开始示值
#define CON_DI_TYPE_MP_SUMG_ENERGYOVERSTARTVAL			0x784A//月电量超定值开始示值	//持续越限则保持改值，越限恢复则修改该值修改电量累计，由恢复到越限则修改改值

#define CON_DI_TYPE_MP_LAST_DIRPOWTOTAL					0x7A10//上一个正向有功总电能
#define CON_DI_TYPE_MP_LAST_DIRPOWPLUS					0x7A11//上一个正向有功尖电能
#define CON_DI_TYPE_MP_LAST_DIRPOWAPEX					0x7A12//上一个正向有功峰电能
#define CON_DI_TYPE_MP_LAST_DIRPOWFLAT					0x7A13//上一个正向有功平电能
#define CON_DI_TYPE_MP_LAST_DIRPOWVALE					0x7A14//上一个正向有功谷电能

#define CON_DI_TYPE_MP_LAST_UNDIRPOWTOTAL				0x7A20//上一个反向有功总电能
#define CON_DI_TYPE_MP_LAST_UNDIRPOWPLUS				0x7A21//上一个反向有功尖电能
#define CON_DI_TYPE_MP_LAST_UNDIRPOWAPEX				0x7A22//上一个反向有功峰电能
#define CON_DI_TYPE_MP_LAST_UNDIRPOWFLAT				0x7A23//上一个反向有功平电能
#define CON_DI_TYPE_MP_LAST_UNDIRPOWVALE				0x7A24//上一个反向有功谷电能

#define CON_DI_TYPE_MP_LAST_DIRVARTOTAL					0x7B10//上一个正向无功总电能
#define CON_DI_TYPE_MP_LAST_DIRVARPLUS					0x7B11//上一个正向无功尖电能
#define CON_DI_TYPE_MP_LAST_DIRVARAPEX					0x7B12//上一个正向无功峰电能
#define CON_DI_TYPE_MP_LAST_DIRVARFLAT					0x7B13//上一个正向无功平电能
#define CON_DI_TYPE_MP_LAST_DIRVARVALE					0x7B14//上一个正向无功谷电能

#define CON_DI_TYPE_MP_LAST_UNDIRVARTOTAL				0x7B20//上一个反向无功总电能
#define CON_DI_TYPE_MP_LAST_UNDIRVARPLUS				0x7B21//上一个反向无功尖电能
#define CON_DI_TYPE_MP_LAST_UNDIRVARAPEX				0x7B22//上一个反向无功峰电能
#define CON_DI_TYPE_MP_LAST_UNDIRVARFLAT				0x7B23//上一个反向无功平电能
#define CON_DI_TYPE_MP_LAST_UNDIRVARVALE				0x7B24//上一个反向无功谷电能

#define CON_DI_TYPE_IMP_EVENT_POINTER					0x7D01//重要事件指针
#define CON_DI_TYPE_NOR_EVENT_POINTER					0x7D02//一般事件指针
#define CON_DI_TYPE_EVENT_STATUS_L						0x7D03//事件状态低4字节
#define CON_DI_TYPE_EVENT_STATUS_H						0x7D04//事件状态高4字节
#define CON_DI_TYPE_MP_TER_LAST_TIME					0x7D05//终端最近工作时间
#define CON_DI_TYPE_MP_TER_LAST_UP_COMM_TIME			0x7D06 //终端最近对上通讯时间

#define CON_DI_TYPE_WIRELESS_GSM_CSQ_MIN_VAL			0x7D0C //信号强度最小值
#define CON_DI_TYPE_WIRELESS_GSM_CSQ_MIN_TIME			0x7D0D //信号强度最小值发生时间
#define CON_DI_TYPE_WIRELESS_GSM_CSQ_MAX_VAL			0x7D0E //信号强度最大值
#define CON_DI_TYPE_WIRELESS_GSM_CSQ_MAX_TIME			0x7D0F //信号强度最大值发生时间 
#define CON_DI_TYPE_WIRELESS_GSM_CSQ					0x7D10 //信号强度0-31
#define CON_DI_TYPE_WIRELESS_LOGIN_TYPE					0x7D11 //登录状态0:未登录，1:已登录
#define CON_DI_TYPE_MODULE_TYPE					        0x7D12 //GPRS模块类型：0:GPRS_MODULE_Q2686 1:GPRS_MODULE_MC52I 15:GPRS_MODULE_NULL

#define CON_DI_TYPE_WIRELESS_COMM_STATE					0x7D13 //主站通信状态：1:通讯  2:掉线  其他:空闲
#define CON_DI_TYPE_TASK_RUN_STATE 						0x7D14 //任务执行状态：1:抄表  2:搜表  其他:完毕

#define CON_DI_TYPE_TER_PASSWORD_STORE					0x7D15 //界面密码
#define CON_DI_TYPE_WIRELESS_STAT                                   		0x7D16 //无线模块状态:1:注册网络，2:正在登录3:GPRS已经连接4:GPRS已经断线
#define CON_DI_TYPE_PLC_STAT								0x7D17 //plc模块状态:1组网2:搜表3:抄表

#define CON_DI_TYPE_TER_POWEROFF_LAST_TIME				0x7D20 //最近停电时间
#define CON_DI_TYPE_TER_POWERON_LAST_TIME				0x7D21 //最近上电时间
#define CON_DI_TYPE_TER_IP_WIRELESS						0x7D22 //无线手机模块的终端ip
#define CON_DI_TYPE_TER_POWEROFF_FLAG					0x7D23 //终端停电标志
#define CON_DI_TYPE_TER_PROGRAMKEY_FLAG					0x7D24 //编程按键有效：1有效，0或者其他无效

#define CON_DI_TYPE_ALARM_ACD_STATUS					0x7D30 //事件发生标识


#define CON_DI_TYPE_ZERO_METER_EXEC_STATUS_LINELOST		0x7E01	//零点冻结抄表状态，用于线损计算
#define CON_DI_TYPE_ZERO_METER_EXEC_STATUS_METER_FAIL	0x7E02	//零点冻结抄表状态，用于抄表失败告警
#define CON_DI_TYPE_ZERO_METER_FAIL_COUNT				0x7E03	//零点冻结抄表失败次数

#define CON_DI_TYPE_LINE_LOST_FINISHED					0x7E04	//线损计算完成

#define CON_DI_TYPE_MPDIRPOWTOTAL_ZERO					0x7E10	//当日零点正向有功电量含CT倍率

#define CON_DI_TYPE_CURR_SOFTWARE_EDITION				0x7E20	//当前软件版本号4位ASCII	例：V1.0保存为100,V1.1保存为101
#define CON_DI_TYPE_LAST_SOFTWARE_EDITION				0x7E21	//上一软件版本号4位ASCII	例：V1.0保存为100,V1.1保存为101

#define CON_DI_TYPE_TER_PHASE_ORDER_NORM				0x7E22	//相序正常，读到为0，则异常，其他均正常

#define CON_DI_TYPE_TER_PHASE_UA                        0x7E23  //相位角，Ua->Ua
#define CON_DI_TYPE_TER_PHASE_UB						0x7E24	//相位角，Ub->Ua
#define CON_DI_TYPE_TER_PHASE_UC						0x7E25	//相位角，Uc->Ua
#define CON_DI_TYPE_TER_PHASE_IA                        0x7E26  //相位角，Ia->Ua
#define CON_DI_TYPE_TER_PHASE_IB						0x7E27	//相位角，Ib->Ua
#define CON_DI_TYPE_TER_PHASE_IC						0x7E28	//相位角，Ic->Ua

#define CON_DI_TYPE_APP_START_TIME						0x7E29	//应用程序开始时间
#define CON_DI_TYPE_METER_STOP_TIME						0x7E30	//电能表停走时间保存
#define CON_DI_TYPE_METER_TIME_ERR_TIME					0x7E31	//电能表时间超差发生时间保存

//针对需量的自定义
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_BIG_BLOCK         0x7E32
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_BIG_BLOCK       0x7E33
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_BIG_BLOCK         0x7E34
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_BIG_BLOCK       0x7E35

#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_LM_BIG_BLOCK      0x7E36
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_LM_BIG_BLOCK    0x7E37
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_LM_BIG_BLOCK      0x7E38
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_LM_BIG_BLOCK    0x7E39

//电压电流抄表返回数据格式不一样，需要专门定义
#define CON_DI_TYPE_MPVOL_BLOCK_07                      0x7E40
#define CON_DI_TYPE_MPCUR_BLOCK_07                      0x7E41
#define CON_DI_TYPE_MPINSTANTPOW_BLOCK_07				0x7E42//
#define CON_DI_TYPE_MPINSTANTVAR_BLOCK_07				0x7E43//
#define CON_DI_TYPE_TER_ZERO_LINE_I00					0x7E44// 临时，需要张旦调整

//中继级别对应表的个数
#define CON_DI_TYPE_RELAY_0_METER_NUM					0x7F00//
#define CON_DI_TYPE_RELAY_1_METER_NUM					0x7F01//
#define CON_DI_TYPE_RELAY_2_METER_NUM					0x7F02//
#define CON_DI_TYPE_RELAY_3_METER_NUM					0x7F03//
#define CON_DI_TYPE_RELAY_4_METER_NUM					0x7F04//
#define CON_DI_TYPE_RELAY_5_METER_NUM					0x7F05//
#define CON_DI_TYPE_RELAY_6_METER_NUM					0x7F06//
#define CON_DI_TYPE_RELAY_7_METER_NUM					0x7F07//
#define CON_DI_TYPE_RELAY_8_METER_NUM					0x7F08//
#define CON_DI_TYPE_RELAY_9_METER_NUM					0x7F09//

//抄表统计
#define CON_DI_TYPE_TOTAL_METER_NUM						0x7F0A//	抄表总数
#define CON_DI_TYPE_VIP_METER_NUM						0x7F0B//	重点户数
#define CON_DI_TYPE_SUCC_METER_NUM						0x7F0C//	成功总数
#define CON_DI_TYPE_FAIL_METER_NUM						0x7F0D//	失败总数

#define CON_DI_TYPE_FAIL_MP_FLAG1                       0x7F0E//   失败表的测量号第1-第4个	因为要存历史，历史一个数据标示存4个测量点
#define CON_DI_TYPE_FAIL_MP_FLAG2                       0x7F0F//   失败表的测量号第5-第8个
#define CON_DI_TYPE_FAIL_MP_FLAG3                       0x7F10//   失败表的测量号第9-第12个
#define CON_DI_TYPE_FAIL_MP_FLAG4                       0x7F11//   失败表的测量号第13-第16个
#define CON_DI_TYPE_FAIL_MP_FLAG5                       0x7F12//   失败表的测量号第17-第20个
#define CON_DI_TYPE_FAIL_MP_FLAG6                       0x7F13//   失败表的测量号第21-第24个
#define CON_DI_TYPE_FAIL_MP_FLAG7                       0x7F14//   失败表的测量号第25-第28个
#define CON_DI_TYPE_FAIL_MP_FLAG8                       0x7F15//   失败表的测量号第29-第32个
//...
#define CON_DI_TYPE_FAIL_MP_FLAG_LAST					0x7F8E//   
//0x7F0E - 7F8E   128个，支持512个测量点

#define CON_DI_TYPE_NODE_COLL_START_TIME				0x7F96	//终端最近启动搜表开始时间
#define CON_DI_TYPE_NODE_COLL_END_TIME					0x7F97	//终端最近启动搜表结束时间

#define CON_DI_TYPE_PLC_METER_START_TIME				0x7F98	//终端最近启动抄表开始时间
#define CON_DI_TYPE_PLC_METER_END_TIME					0x7F99	//终端最近启动抄表结束时间

#define CON_DI_TYPE_NEXT_HW_REBOOT_TIME					0x7F9A	//终端自动重启的下一次时间

#define CON_DI_TYPE_METER_485_1_RUN_NUM					0x7F9B	//485一抄表总数和成功数
#define CON_DI_TYPE_METER_485_2_RUN_NUM					0x7F9C	//485二抄表总数和成功数
//--------------------------控制模块相关---------------------------------------------
#define CON_DI_TYPE_POWCTRL_SUMGNO                      		0x2010			//功控总加组号			
#define CON_DI_TYPE_ENERGYCTRL_SUMGNO                    	0x2011			//电控总加组号
#define CON_DI_TYPE_MONTH_CHANGE_FLAG                    	0x2012			//月份变化标志


#define CON_DI_TYPE_MULTI_HRT_INT					0x2014			//无数据接收心跳时间倍数
#define CON_DI_TYPE_MODULE_RESET_COUNT			0x2015			

//---------- 自定义 0x7600 0x7FFF 支持2560个 -----------------------



#define CON_DI_TYPE_MPDIRPOWTOTAL_LST2M			0x9810	//上上月正向有功电量
#define CON_DI_TYPE_MPDIRPOWPLUS_LST2M			0x9811	//上上月正向有功电量
#define CON_DI_TYPE_MPDIRPOWAPEX_LST2M			0x9812	//上上月正向有功电量
#define CON_DI_TYPE_MPDIRPOWFLAT_LST2M			0x9813	//上上月正向有功电量
#define CON_DI_TYPE_MPDIRPOWVALE_LST2M			0x9814	//上上月正向有功电量
#define CON_DI_TYPE_MPDIRPOW_LST2M_BLOCK		0x981F

#define CON_DI_TYPE_MPDIRPOWTOTAL_LST3M			0x9A10	//上上上月正向有功电量
#define CON_DI_TYPE_MPDIRPOWPLUS_LST3M			0x9A11	//上上上月正向有功电量
#define CON_DI_TYPE_MPDIRPOWAPEX_LST3M			0x9A12	//上上上月正向有功电量
#define CON_DI_TYPE_MPDIRPOWFLAT_LST3M			0x9A13	//上上上月正向有功电量
#define CON_DI_TYPE_MPDIRPOWVALE_LST3M			0x9A14	//上上上月正向有功电量
#define CON_DI_TYPE_MPDIRPOW_LST3M_BLOCK		0x9A1F

#define CON_DI_TYPE_MPDIRPOWTOTAL_LST0DAY			0x9090//当前带日期电量
#define CON_DI_TYPE_MPDIRPOWTOTAL_LST1DAY			0x9091//上1日带日期电量
#define CON_DI_TYPE_MPDIRPOWTOTAL_LST2DAY			0x9092//上2日带日期电量
#define CON_DI_TYPE_MPDIRPOWTOTAL_LST3DAY			0x9093//上3日带日期电量
#define CON_DI_TYPE_MPDIRPOWTOTAL_LST4DAY			0x9094//上4日带日期电量
#define CON_DI_TYPE_MPDIRPOWTOTAL_LST5DAY			0x9095//上5日带日期电量
#define CON_DI_TYPE_MPDIRPOWTOTAL_LST6DAY			0x9096//上6日带日期电量
#define CON_DI_TYPE_MPDIRPOWTOTAL_LST7DAY			0x9097//上7日带日期电量

#define CON_DI_TYPE_MPLOSTVOL_NUM						0xE130//失压次数
#define CON_DI_TYPE_MPLOSTVOLA_NUM						0xE133//失压次数
#define CON_DI_TYPE_MPLOSTVOLB_NUM						0xE136
#define CON_DI_TYPE_MPLOSTVOLC_NUM						0xE139
#define CON_DI_TYPE_MPLOSTVOL_BLOCK					0xE13F

#define CON_DI_TYPE_MPLOSTCURA_NUM						0xE122//失流次数
#define CON_DI_TYPE_MPLOSTCURB_NUM						0xE124
#define CON_DI_TYPE_MPLOSTCURC_NUM						0xE126

#define CON_DI_TYPE_MPINDIR_CURA_NUM						0xE142
#define CON_DI_TYPE_MPINDIR_CURB_NUM						0xE146
#define CON_DI_TYPE_MPINDIR_CURC_NUM						0xE14A

#define CON_DI_TYPE_MPPROG_DATEANDNUM					0xE211
#define CON_DI_TYPE_MPMETERSTAT_GD2_FLAG				0xC029	//广东电表运行状态字2
//---------- 参数数据标识 -------------------------------------------
#define CON_DI_TYPE_STATIONADDR0				0x8010//主站通信地址0	（读写，高级权限）
#define CON_DI_TYPE_STATIONADDR1				0x8011//主站通信地址1	（读写，高级权限）
#define CON_DI_TYPE_STATIONADDR2				0x8012//主站通信地址2	（读写，高级权限）
#define	CON_DI_TYPE_SMSCENTERNUM				0x8013//短信中心号码	（读写，高级权限）
#define CON_DI_TYPE_NETGATEADDR					0x8014//网关地址		（读写，高级权限）
#define CON_DI_TYPE_NETAPN						0x8015//APN名称			（读写，高级权限）
#define	CON_DI_TYPE_TERAERA						0x8016//终端地市码		（读写，高级权限）
#define CON_DI_TYPE_TERADDR						0x8017//终端地址		（读写，高级权限）
#define CON_DI_TYPE_NETUSERNAME					0x8019//GPRS(CDMA)登录用户名（读写，高级权限）
#define CON_DI_TYPE_NETPASSWORD					0x801A//GPRS(CDMA)登录密码	（读写，高级权限）
#define CON_DI_TYPE_801F_BLOCK					0x801F//				（读写，高级权限）

#define CON_DI_TYPE_READPASSWORD				0x8020//普通密码		（写，低级&高级权限）
#define CON_DI_TYPE_SETPASSWORD					0x8021//设置密码		（写，低级&高级权限）
#define	CON_DI_TYPE_ADMINPASSWORD				0x8022//管理员密码		（写，高级权限）
#define CON_DI_TYPE_802F_BLOCK					0x802F//				（写，高级权限）	

#define CON_DI_TYPE_TERTIME						0x8030//终端时间		（读写，低级&高级权限）
#define CON_DI_TYPE_CHECKTIME						0x803E//对时
#define CON_DI_TYPE_TERSOFTWAREINFO				0x8809//首字节终端厂商代码；其后为终端软件版本号（读）
#define CON_DI_TYPE_TARHARDWAREVERNO			0x880A//终端硬件版本号（读）

#define CON_DI_TYPE_RINGNUM						0x8810//振铃次数
#define CON_DI_TYPE_METERNUM						0x8811//电能表总数
#define CON_DI_TYPE_COMMETER						0x8812//普通电表
#define CON_DI_TYPE_MULFUNMETER					0x8813//多功能电表数 
#define CON_DI_TYPE_IMUSRMETER					0x8814//重点用户
#define CON_DI_TYPE_TASKSTART						0x8815//任务起始时间
#define CON_DI_TYPE_TASKINTER						0x8816//任务执行间隔 
#define CON_DI_TYPE_RELAYMODE						0x8817//中继方式
#define CON_DI_TYPE_LOSTLIMIT						0x8818//线损阈值
#define CON_DI_TYPE_IMUPTIME						0x8819//重点用户上传时间
#define CON_DI_TYPE_DAYUPTIME						0x881A//日冻结数据上传时间
#define CON_DI_TYPE_ALARMEABLE					0x881B//告警使能控制字
#define CON_DI_TYPE_LOSTTODAY						0x881C//本日线损率
#define CON_DI_TYPE_SLAVEADD						0x881D//级联从终端地址
#define CON_DI_TYPE_LINKED_PROPERTY				0x881E//级联参数

#define CON_DI_TYPE_MONCOPYTIME					0x8820//月末数据抄收开始时间
#define CON_DI_TYPE_MONUPTIME						0x8821//月末数据上传时间
#define CON_DI_TYPE_DISTERADD						0x8822//台区对应配变终端地址

#define CON_DI_TYPE_TERMMAG						0x8830//台区对应配变终端倍率
#define CON_DI_TYPE_HEARTINTER					0x8831//心跳周期

#define CON_DI_TYPE_MPPROP						0x8901//测量点性质		（读写，低级&高级权限）
#define CON_DI_TYPE_MPADDR						0x8902//测量点地址		（读写，低级&高级权限）

#define CON_DI_TYPE_MP_TERADDR					0x8939//测量点对应的终端地址
#define CON_DI_TYPE_METERTYPE						0x8940//表类型

#define CON_DI_TYPE_AUTORELAY						0x8943//自动中继约束条件

#define CON_DI_TYPE_MODYMETER_BATCH				0x894D//批量修改
#define CON_DI_TYPE_MODYMETER						0x894E//修改表计

#define CON_DI_TYPE_MPMETERSTAT_GD_FLAG					0x8EA0	//广东电表运行状态字

#define CON_STATUS_YES				0x55	//字节标记：是
#define CON_STATUS_NO				0xAA	//字节标记：否
#define	CON_INVALID_VAL				0xFF
#define	CON_INVALID_LONG_VAL		0x7FFFFFFF

#define CON_READ_METER_OK			0x55	//抄表成功
#define CON_READ_METER_ERR			0xAA	//抄表失败
#define	CON_READ_METER_INVALID		0xFF	//无效状态

#define CON_STATUS_NONE				0x00	//标记：无
#define CON_STATUS_START			0x33	//标记：启动中
#define CON_STATUS_FINISHED			0xCC	//标记：完成

#define CON_MAIN_DEV				0	//主终端
#define CON_SLAVE_DEV				1	//从终端

#define CON_PRI_UP_ACTIVE			0	//主动上送
#define CON_PRI_UP_NORMAL			1	//普通

#define	CON_METERTYPE_3P3L		0x01
#define	CON_METERTYPE_3P4L		0x02
#define	CON_METERTYPE_1P		0x03

#define CON_SMS_LIST_NUM		7	//短信报文帧拆分最大数目
#define CON_MAX_CURVE_DATA_NUM	96	//主站请求曲线数据最大个数限制

#define		CON_SUMGFLAG_ENERGYCTRL	0x55	//电量控制
#define		CON_SUMGFLAG_POWERCTRL	0xAA	//功率控制
#define		CON_SUMGFLAG_CTRL_COMB	0xFF	//电量控制和功率控制

//-------------------------- 对上规约定义 -----------------------------------
#define MAIN_CHAN_ID 1			//主通道编号
#define BACK_CHAN_ID 2			//备通道编号
#define BACK_CHAN_ID1 3			//备通道2编号
#define WLS_CHAN_ID     MAIN_CHAN_ID//无线模块通道
#define CON_698_MAX_MP_NUM				2040		//最大测量点
#define CON_698_MAX_METER_NUM			2040		//最大电能表或者交采装置数
#define CON_698_MAX_CALC_NUM			8			//最大总加组数
#define CON_698_MAX_CALC_MP_NUM			64			//最大总加组测量点数

#define CON_698_ERR_MPNO				2019		//异常测量点
#define CON_698_TER_SAMPLE_DEFAULT_MPNO	2010		//默认交流采集测量点 DA0 DA1 = 02 FB
#define CON_698_ERR_DSOBJNO				1019		//异常对象点

#define	CON_698_EXT_PROTOCOL_INVALID	0		//无效
#define	CON_698_EXT_PROTOCOL_DL645_1997	1		//645 1997规约
#define	CON_698_EXT_PROTOCOL_SAMPLE		2		//交流采集

#define	CON_698_EXT_PROTOCOL_WS			3		//威胜v4.x
#define	CON_698_EXT_PROTOCOL_LANDD		4		//西门子D表
#define	CON_698_EXT_PROTOCOL_ABB_R		5		//ABB方表
#define	CON_698_EXT_PROTOCOL_GENIUS		6		//红相
#define	CON_698_EXT_PROTOCOL_HND		7		//浩宁达
#define	CON_698_EXT_PROTOCOL_LANDB		8		//西门子B表
#define	CON_698_EXT_PROTOCOL_DL645_2007	30		//645 2007规约

#define	CON_698_METERTYPE_3P3L		0x01		//三相三线
#define	CON_698_METERTYPE_3P4L		0x02		//三相四线
#define	CON_698_METERTYPE_1P		0x03		//单相表

#define	CON_698_METERTYPE_1P_NOT_CFM	0x00	//单相表接线相不确定
#define	CON_698_METERTYPE_1P_PA			0x04	//单相表接线相A相
#define	CON_698_METERTYPE_1P_PB			0x08	//单相表接线相B相
#define	CON_698_METERTYPE_1P_PC			0x0C	//单相表接线相C相


//广东集中器
#define CON_MAX_MP_NUM				1280	//1024+254+1+1	/0102单相，03简易多功，08总表
			//测量点号 0 为集中器自身，表设备测量点号从 1 开始
#define CON_MAX_VIP_MP_NUM			6		//重点用户
#define CON_MAX_SMETER_MP_NUM		1024	//单相或者机械
#define CON_MAX_MMETER_MP_NUM		254		//简易多功能
#define CON_MAX_NEED_FROZ_MP_NUM	1024	//需要集中器冻结零点电量

#define CON_TER_MPNO				0		//终端自身测量点

#define CON_HIS_DATA_DAY_NUM		63		//日冻结天数
#define CON_HIS_DATA_MON_NUM		25		//月冻结月数
//#define CON_CURVE_DATA_DAY_NUM		32		//曲线天数
#define CON_CURVE_DATA_DAY_NUM		63		//曲线天数  需要写入数据库才能起作用，目前默认63天
#define CON_CURVE_DATA_POINT_NUM	(CON_CURVE_DATA_DAY_NUM  * 96)		//曲线点数，按照15分钟密度
#define CON_CURVE_DATA_INTER_SEC	900		//曲线15分钟密度，900秒

#define CON_INDEX_RESET				0xFFEE	//上电后索引
#define CON_INDEX_INVALID			0xFFFF	//无效索引

#define CON_METER_PROP1_485			0x01	//485
#define CON_METER_PROP1_PLC			0x02	//载波
#define CON_METER_PROP1_OTHER		0x03	//其他
#define CON_METER_PROP1_MASK		0x07

#define CON_METER_PROP2_SMETER		0x08	//单相
#define CON_METER_PROP2_JMETER		0x10	//机械
#define CON_METER_PROP2_MMETER		0x18	//简易多功能
#define CON_METER_PROP2_ZMETER		0x40	//总
#define CON_METER_PROP2_MASK		0x78

#define CON_METER_PROP3_GATE_1		0x80	//总
#define CON_METER_PROP3_GATE_0		0x00	//分
#define CON_METER_PROP3_MASK		0x80

#define CON_METER_DATATYPE_MONTH	0x80		//月末数据
#define CON_METER_DATATYPE_DAY		0x40		//日末数据
#define CON_METER_DATATYPE_MASK		0xC0
//-------------------------- 设备定义 -----------------------------------
#define	CON_UP_BOARD_PORT		1
#define	CON_DOWN_BOARD_PORT		2
#define	CON_SPEC_BOARD_PORT		3

#define	CON_BOARD_PORT_DINPUT	CON_DOWN_BOARD_PORT
#define	CON_BOARD_PORT_SPEC		CON_SPEC_BOARD_PORT

#define CON_BOARD_ID			0xFF00		//用于与操作，取得板子ID
#define CON_PORT_ID				0x00FF		//用于与操作，取得实际的端口ID
//端口ID的高两位为板子的ID，低两位才是实际的端口ID，使用时需与0x00FF(CON_PORT_ID)与操作得到实际的端口ID
#define CON_DOWN_BOARD_X	0xFFFF		//无效
//---------------以下端口定义在\etc\port.cfg文件中，专变和集中器有差别---------------
#ifdef CON_TER_TYPE_FK_ALL		//专变
#define CON_UP_BOARD_3			0x0103		//up_board_3 = "pb6"  #开关量5
#define CON_UP_BOARD_4			0x0104		//up_board_4 = "pb7"  #开关量6
#define CON_DOWN_BOARD_4		0x0204		//down_board_4 = "pa9"  #开关量1 (21,22)
#define CON_DOWN_BOARD_5		0x0205		//down_board_5 = "pa8"  #开关量2 (23,24)
#define CON_DOWN_BOARD_6		0x0206		//down_board_6 = "pa7"  #开关量3 (25,26)
#define CON_DOWN_BOARD_7		0x0207		//down_board_7 = "pa6"  #开关量4 (27,28)
#define CON_DOWN_BOARD_12		0x020C		//down_board_12 = "pb20" #门结点
#define CON_COVER_MONITOR_1 	0x0301		//cover_monitor_1 = "pc28" #开关量8(0,0)开盖检测

#define CON_SIG_COLL_ID1		CON_DOWN_BOARD_4
#define CON_SIG_COLL_ID2		CON_DOWN_BOARD_5
#define CON_SIG_COLL_ID3		CON_UP_BOARD_3
#define CON_SIG_COLL_ID4		CON_UP_BOARD_4
#define CON_SIG_COLL_ID5		CON_DOWN_BOARD_X
#define CON_SIG_COLL_ID6		CON_DOWN_BOARD_X
#define CON_SIG_COLL_ID7		CON_DOWN_BOARD_X
#define CON_SIG_COLL_ID8		CON_DOWN_BOARD_12
#else							//集中器
#define CON_DOWN_BOARD_1	0x0201			//down_board_1  = "pa9"  #开关量1(13,14)
#define CON_DOWN_BOARD_2	0x0202			//down_board_2  = "pa8"  #开关量2(15,16)
#define CON_COVER_MONITOR_1 	0x0301			//cover_monitor_1 = "pc28" #开关量8(0,0)开盖检测

#define CON_SIG_COLL_ID1		CON_DOWN_BOARD_1
#define CON_SIG_COLL_ID2		CON_DOWN_BOARD_2
#define CON_SIG_COLL_ID3		CON_DOWN_BOARD_X
#define CON_SIG_COLL_ID4		CON_DOWN_BOARD_X
#define CON_SIG_COLL_ID5		CON_DOWN_BOARD_X
#define CON_SIG_COLL_ID6		CON_DOWN_BOARD_X
#define CON_SIG_COLL_ID7		CON_DOWN_BOARD_X
#define CON_SIG_COLL_ID8		CON_COVER_MONITOR_1
#endif
//---------------以上端口定义在\etc\port.cfg文件中，专变和集中器有差别---------------

#define	CON_SIG_COLL_NUM		8			//信号采集路数

#define CON_SIG_TYPEA			1	//－A类触点 一致
#define CON_SIG_TYPEB			0	//－B类触点 相反

/*开关状态设置*/
#define CON_SIG_STAT_CLOSE		1	//开关合
#define CON_SIG_STAT_OPEN		0	//开关分

#define CON_SIG_DOOR1		8	//计量柜门节点
#define CON_SIG_DOOR2		7	//终端盖
#define CON_SIG_DOOR3		6	//电能表盖

#define CON_SIG_SWITCH1		1	//遥信1
#define CON_SIG_SWITCH2		2	//遥信2
#define CON_SIG_SWITCH3		3	//遥信3
#define CON_SIG_SWITCH4		4	//遥信4

#define CON_SIG_COVER_TAIL	1	//编号1：尾盖
#define CON_SIG_COVER_SMALL	2	//编号2：小盖
#define CON_SIG_COVER_BIG	3	//编号3：大盖

//#define CON_LED_RUN			5	//DA2	D5			//广东集中器
//#define CON_LED_ALARM		6	//DA3	D6				//广东集中器
#define CON_LED_RUN			12
#define CON_LED_ALARM		13

#define CON_LED_GPRS_NET	8	//gprs 网络
#define CON_LED_GPRS_TXD	9	//gprs 网络发送
#define CON_LED_GPRS_RXD	10	//gprs 网络接收

#define CON_POWER_LOW_INPUT_VOLT	5500	//3000mv

#ifdef CON_TER_TYPE_JC_CQ

//端口编号，按宣贯材料约定								//数据库，通道参数需要相应修改
#define CON_PORT_SAMPLE		26	//终端交流采样接口通信
#define CON_PORT_485_1		1	//RS485 1 接口通信
#define CON_PORT_485_2		2	//RS485 2 接口通信
#define CON_PORT_LINK		30	//终端级联通信
#define CON_PORT_PLC		31	//本地通信模块接口通信
#define CON_PORT_BEEN_COLL	CON_PORT_LINK	//终端交表被抄

#else

//端口编号，按宣贯材料约定
#define CON_PORT_SAMPLE		1	//终端交流采样接口通信
#define CON_PORT_485_1		2	//RS485 1 接口通信
#define CON_PORT_485_2		3	//RS485 2 接口通信
#define CON_PORT_LINK		30	//终端级联通信
#define CON_PORT_PLC		31	//本地通信模块接口通信
#define CON_PORT_BEEN_COLL	CON_PORT_LINK	//终端交表被抄

#endif

#define CON_485_PORT_AREA   CON_PORT_485_1,CON_PORT_485_2,CON_PORT_LINK

//plc抄表结果
#define CON_PLC_MNG_METER_NOT_ACK	0			//抄表状态未知，未抄表
#define CON_PLC_MNG_METER_SUCCESS	1			//抄表成功
#define CON_PLC_MNG_METER_FAIL		2			//抄表失败
#define CON_PLC_MNG_METER_NEW_ADD	3			//表，新增加

#define CON_PLC_MNG_METER_NOT_FIND	4			//路由未搜到表

#define CON_PLC_CTRL_NONE			0			// 载波抄表控制，无操作
#define CON_PLC_CTRL_PAUSE			1			// F49：命令指定通信端口暂停抄表
#define CON_PLC_CTRL_RESUME			2			// F50：命令指定通信端口恢复抄表
#define CON_PLC_CTRL_RESET			3			// F51：命令指定通信端口重新抄表
#define CON_PLC_CTRL_INIT_ROUTE		4			// F52：初始化指定通信端口下的全部中继路由信息
#define CON_PLC_CTRL_START_WITH_RET	5			// 重新抄表，完成由通知

#define CON_UP_CHAN_NUM				3			//第二个用作GPRS通道，第三个用作以太网通道，第一个备用

//其他定义
#define CON_MODULE_TYPE_GPRS		0			//模块类型，GPRS
#define CON_MODULE_TYPE_CDMA		1			//模块类型，CDMA
#define CON_MODULE_TYPE_NONE		15			//模块类型，没有插模块
#define CON_MODULE_TYPE_ERR			-1			//模块类型，未知


#endif
