/***************************************************************************
 *
 *
 *
 * COPYRIGHT (C) 2009 PaxHZ, ALL RIGHTS RESERVED
 * $Abstract: 进程间通讯相关头文件
 *
 * $Source: src\include\basetype.h$
 * $Author: wudengben$
 * $Date:2009-6-29$ 
 * $Revision:1.1 添加semun定义$
 *
 *
 * $Date:2009-6-30 9:33$ 
 * Revision 1.1  2009-6-29 15:15  wudengben
 * 添加semun定义
 *
 * $Date:2009-6-29 15:17$ 
 * Revision 1.0  2009-6-29 15:15  wudengben
 * 进程间通讯相关头文件
 *
 *
 ***************************************************************************/
#ifndef APP_IPCS_H
#define APP_IPCS_H

#include <basetype.h>
#include <time.h>
#include <sys_def.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 1
#endif

/*key定义，该值不能为0（IPC_PRIVATE）,否则总是新建*/

/**< 信号量定义*/
#define SEM_KEY_DB_TASK     0x0f000000         /*任务相关数据库原子操作*/     
#define SEM_KEY_TERCTRL     0x0f000001         /*控制相关原子操作*/
#define SEM_KEY_ACS_SPI     0x0f000002         /*ADE7878原子操作*/
#define SEM_KEY_UP_FRAME    0x0f000003         /*约规帧处理原子操作*/
#define SEM_KEY_MAIN_LOG    0x0f000004         /*主进程日志原子操作*/
#define SEM_KEY_COLL_LOG    0x0f000005         /*采集进程日志原子操作*/
#define SEM_KEY_GPRS_LOG    0x0f000006         /*gprs进程日志原子操作*/
#define SEM_KEY_ALARM_AFFIRM    0x0f000007         /*告警帧上送确认原子操作*/
#define SEM_KEY_LOGIN_AFFIRM    0x0f000008         /*登录帧上送确认原子操作*/
#define SEM_KEY_JOB_UP_AFFIRM    0x0f000009         /*任务上送确认原子操作*/
#define SEM_KEY_METER_SECOND    0x0f00000A          /*内表秒时钟信号量*/

/**< 共享内存定义*/
#define SHM_KEY_PROTO       0x0e000000         /*协议解析模块与其他模块交互通道*/
#define SHM_KEY_TERCTRL     0x0e000001         /*控制模块子进程间交互通道*/ 
#define SHM_KEY_RT_DATA     0x0e000002		   //实时数据

/**< 消息定义*/



/*信号量依赖相关子程序*/
union semun {
      int val;                  /* value for SETVAL */
      struct semid_ds *buf;     /* buffer for IPC_STAT, IPC_SET */
      unsigned short *array;    /* array for GETALL, SETALL */
                                /* Linux specific part: */
      struct seminfo *__buf;    /* buffer for IPC_INFO */
};


struct msg_buf_st
{
    struct sys_msg_hdr msg_hdr;
    uint8_t msg_data[];
};

/**< 结构体定义*/

//任务参数
struct task_param_update_st
{
    int update_times;   /*该参数更新次数*/    
};

//网络通讯参数
struct ether_net_param_update_st
{
    int update_times;   /*该参数更新次数*/    
};

struct wireless_net_param_update_st
{
    int update_times;   /*该参数更新次数*/    
};

//状态量参数
struct switch_param_update_st
{
    int update_times;   /*该参数更新次数*/    
};

//告警相关参数
struct alarm_param_update_st
{
    int update_times;   /*该参数更新次数*/    
};

//级联参数
struct link_param_update_st
{
    int update_times;   /*该参数更新次数*/    
};

//抄表参数
struct meter_param_update_st
{
    int update_times;   /*该参数更新次数*/    
};

//测量点参数
struct mpno_param_update_st
{
	int update_times;   /*该参数更新次数*/    
};

//时间变化
struct time_param_update_st
{
	int update_times;   /*该参数更新次数*/    
};

//控制参数
struct terctrl_param_update_st
{
    int update_times;    /*该参数更新次数*/
    int enable_bitmap;   /*bit[0-7]表示是否使能控制,该位为1表示使能,0表示不控制*/
};
//费率时段参数
struct ratetime_update_st
{
    int update_times;   /*该参数更新次数*/    
};

struct ade7878_clear_update_st
{
    int update_times;   /*该参数更新次数*/    
};

struct power_update_st  //底度设置
{
    int update_times;   /*该参数更新次数*/    
};

struct demand_reset_update_st  //底度设置
{
    int update_times;   /*该参数更新次数*/    
};

struct demandtime_update_st  //底度设置
{
    int update_times;   /*该参数更新次数*/    
};

struct coll_manage_portparam_update_st
{
    int update_times;   /**/
};
struct coll_manage_miscparam_update_st
{
    int update_times;   /**/
};
struct biglittle_class_meter_di_conf_st
{
	int update_times;   /**/
};
struct plc_coll_overtime_st
{
	int update_times;   /**/
};

//终端脉冲配置参数 
struct pulse_update_st
{
    int update_times;   /**/
};

//共享内存参数变更
struct update_param_shm_st
{
	struct task_param_update_st		    job_task_update; 
	struct ether_net_param_update_st	ether_net_param_update; 
	struct wireless_net_param_update_st	wireless_net_param_update; 
	struct switch_param_update_st		switch_param_update; 
	struct alarm_param_update_st		alarm_param_update; 
	struct link_param_update_st			link_param_update; 
	struct meter_param_update_st		meter_param_update; 
	struct mpno_param_update_st			mpno_param_update;
	struct time_param_update_st			time_param_update;
	struct terctrl_param_update_st      terctrl_param_update;
	struct ratetime_update_st           ratetime_update;
	struct ade7878_clear_update_st		ade7878_clear_update;
	struct power_update_st              power_update;
	struct demand_reset_update_st       demand_reset_update;
	struct demandtime_update_st         demandtime_update;
	struct coll_manage_portparam_update_st  coll_manage_portparam_update;
	struct coll_manage_miscparam_update_st  coll_manage_miscparam_update;
	struct biglittle_class_meter_di_conf_st biglittle_class_meter_di_conf;
	struct pulse_update_st				pulse_update;
	struct plc_coll_overtime_st			plc_coll_overtime;
	int meter_para_is_setting;
	unsigned char app_cfg_info_print;
	int shm_ter_sample_mp_no;
	int app_cfg_open_close_ethernet;
	unsigned long meter_clr_event_flag;      //指示清零操作的标志;0x55AA0022
};

#define CON_RT_DATA_MULTI_METER_NUM		500										//固定测量点前500为多功能表
//#define CON_RT_DATA_MULTI_METER_NUM		600										//固定测量点前600为多功能表
#define CON_RT_DATA_MULTI_MP_NUM		(CON_RT_DATA_MULTI_METER_NUM)			//多功能表
#define CON_RT_DATA_SIMP_MP_NUM			(CON_698_MAX_MP_NUM - CON_RT_DATA_MULTI_METER_NUM)	//剩余为简易表，一般为1440

#define CON_RT_DATA_TER_DI_COUNT		640										//终端本身最多数据标识640个
#define CON_RT_DATA_MULTI_DI_COUNT		270										//多功能表最多数据标识270个
#define CON_RT_DATA_SIMP_DI_COUNT		70										//简易表最多数据标识70个

struct rt_data_per
{
	long rec_time;
	unsigned short data_id;
	unsigned char reserve[2];
	unsigned char data[8];
};
struct mp_rt_data_ter_per
{
	struct rt_data_per rt_data[CON_RT_DATA_TER_DI_COUNT];
};
struct mp_rt_data_multi_per
{
	struct rt_data_per rt_data[CON_RT_DATA_MULTI_DI_COUNT];
};
struct mp_rt_data_simple_per
{
	struct rt_data_per rt_data[CON_RT_DATA_SIMP_DI_COUNT];
};
struct mp_rt_data_st
{
	struct mp_rt_data_ter_per mp_rt_data_t[1];
	struct mp_rt_data_multi_per mp_rt_data_m[CON_RT_DATA_MULTI_MP_NUM];
	struct mp_rt_data_simple_per mp_rt_data_s[CON_RT_DATA_SIMP_MP_NUM];
};

/*------------函数申明-----------------------------------------------*/   
/**<  信号量相关  **/

/*初始化信号量
@param key : 关键字,相同的关键字对应同一信号量(资源标志)
@bset      : 是否给资源标志赋初值,1表示赋初值*/
int app_sem_open(int key,bool bset);

/*设置空闲状态,取消资源标志
@ sem_id : 信号量ID,由sem_open()返回获得
*/
void app_sem_set_idle(int sem_id);

/*设置忙状态,获取资源标志,若此时资源标志不可用,则持续等待
@ sem_id : 信号量ID,由sem_open()返回获得*/
void app_sem_wait_busy(int sem_id);

//关闭信号量
int app_sem_close(int sem_id);


/**<  共享内存相关 **/

/*共享内存初始化设置
@ key       :关键字,相同的关键字对应同一信号量(资源标志)
@ size      :申请共享内存容量
@ retry_num :重试次数,第一次使用（一般为主进程）设置为1,其他时候设置为0
@ return    :申请共享内存分配地址,为NULL时表示申请失败;
@ about     :当retry_num不为0时,若申请失败，会通过ipcrm删除原有设置;
*/
void *app_shm_open(int key,int size,uint8 retry_num);


//extern struct update_param_shm_st *g_p_update_param_shm;
#if 0

/*消息队列空间申请
@data_len : 空间长度,需要发送的消息长度*/
struct msg_buf_st *app_msg_malloc(uint16 data_len);

void *app_msg_get_date_addr(struct msg_buf_st *msg_date);

#endif
/**/


#endif // APP_IPCS_H

