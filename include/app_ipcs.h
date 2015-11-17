/***************************************************************************
 *
 *
 *
 * COPYRIGHT (C) 2009 PaxHZ, ALL RIGHTS RESERVED
 * $Abstract: ���̼�ͨѶ���ͷ�ļ�
 *
 * $Source: src\include\basetype.h$
 * $Author: wudengben$
 * $Date:2009-6-29$ 
 * $Revision:1.1 ���semun����$
 *
 *
 * $Date:2009-6-30 9:33$ 
 * Revision 1.1  2009-6-29 15:15  wudengben
 * ���semun����
 *
 * $Date:2009-6-29 15:17$ 
 * Revision 1.0  2009-6-29 15:15  wudengben
 * ���̼�ͨѶ���ͷ�ļ�
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

/*key���壬��ֵ����Ϊ0��IPC_PRIVATE��,���������½�*/

/**< �ź�������*/
#define SEM_KEY_DB_TASK     0x0f000000         /*����������ݿ�ԭ�Ӳ���*/     
#define SEM_KEY_TERCTRL     0x0f000001         /*�������ԭ�Ӳ���*/
#define SEM_KEY_ACS_SPI     0x0f000002         /*ADE7878ԭ�Ӳ���*/
#define SEM_KEY_UP_FRAME    0x0f000003         /*Լ��֡����ԭ�Ӳ���*/
#define SEM_KEY_MAIN_LOG    0x0f000004         /*��������־ԭ�Ӳ���*/
#define SEM_KEY_COLL_LOG    0x0f000005         /*�ɼ�������־ԭ�Ӳ���*/
#define SEM_KEY_GPRS_LOG    0x0f000006         /*gprs������־ԭ�Ӳ���*/
#define SEM_KEY_ALARM_AFFIRM    0x0f000007         /*�澯֡����ȷ��ԭ�Ӳ���*/
#define SEM_KEY_LOGIN_AFFIRM    0x0f000008         /*��¼֡����ȷ��ԭ�Ӳ���*/
#define SEM_KEY_JOB_UP_AFFIRM    0x0f000009         /*��������ȷ��ԭ�Ӳ���*/
#define SEM_KEY_METER_SECOND    0x0f00000A          /*�ڱ���ʱ���ź���*/

/**< �����ڴ涨��*/
#define SHM_KEY_PROTO       0x0e000000         /*Э�����ģ��������ģ�齻��ͨ��*/
#define SHM_KEY_TERCTRL     0x0e000001         /*����ģ���ӽ��̼佻��ͨ��*/ 
#define SHM_KEY_RT_DATA     0x0e000002		   //ʵʱ����

/**< ��Ϣ����*/



/*�ź�����������ӳ���*/
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

/**< �ṹ�嶨��*/

//�������
struct task_param_update_st
{
    int update_times;   /*�ò������´���*/    
};

//����ͨѶ����
struct ether_net_param_update_st
{
    int update_times;   /*�ò������´���*/    
};

struct wireless_net_param_update_st
{
    int update_times;   /*�ò������´���*/    
};

//״̬������
struct switch_param_update_st
{
    int update_times;   /*�ò������´���*/    
};

//�澯��ز���
struct alarm_param_update_st
{
    int update_times;   /*�ò������´���*/    
};

//��������
struct link_param_update_st
{
    int update_times;   /*�ò������´���*/    
};

//�������
struct meter_param_update_st
{
    int update_times;   /*�ò������´���*/    
};

//���������
struct mpno_param_update_st
{
	int update_times;   /*�ò������´���*/    
};

//ʱ��仯
struct time_param_update_st
{
	int update_times;   /*�ò������´���*/    
};

//���Ʋ���
struct terctrl_param_update_st
{
    int update_times;    /*�ò������´���*/
    int enable_bitmap;   /*bit[0-7]��ʾ�Ƿ�ʹ�ܿ���,��λΪ1��ʾʹ��,0��ʾ������*/
};
//����ʱ�β���
struct ratetime_update_st
{
    int update_times;   /*�ò������´���*/    
};

struct ade7878_clear_update_st
{
    int update_times;   /*�ò������´���*/    
};

struct power_update_st  //�׶�����
{
    int update_times;   /*�ò������´���*/    
};

struct demand_reset_update_st  //�׶�����
{
    int update_times;   /*�ò������´���*/    
};

struct demandtime_update_st  //�׶�����
{
    int update_times;   /*�ò������´���*/    
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

//�ն��������ò��� 
struct pulse_update_st
{
    int update_times;   /**/
};

//�����ڴ�������
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
	unsigned long meter_clr_event_flag;      //ָʾ��������ı�־;0x55AA0022
};

#define CON_RT_DATA_MULTI_METER_NUM		500										//�̶�������ǰ500Ϊ�๦�ܱ�
//#define CON_RT_DATA_MULTI_METER_NUM		600										//�̶�������ǰ600Ϊ�๦�ܱ�
#define CON_RT_DATA_MULTI_MP_NUM		(CON_RT_DATA_MULTI_METER_NUM)			//�๦�ܱ�
#define CON_RT_DATA_SIMP_MP_NUM			(CON_698_MAX_MP_NUM - CON_RT_DATA_MULTI_METER_NUM)	//ʣ��Ϊ���ױ�һ��Ϊ1440

#define CON_RT_DATA_TER_DI_COUNT		640										//�ն˱���������ݱ�ʶ640��
#define CON_RT_DATA_MULTI_DI_COUNT		270										//�๦�ܱ�������ݱ�ʶ270��
#define CON_RT_DATA_SIMP_DI_COUNT		70										//���ױ�������ݱ�ʶ70��

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

/*------------��������-----------------------------------------------*/   
/**<  �ź������  **/

/*��ʼ���ź���
@param key : �ؼ���,��ͬ�Ĺؼ��ֶ�Ӧͬһ�ź���(��Դ��־)
@bset      : �Ƿ����Դ��־����ֵ,1��ʾ����ֵ*/
int app_sem_open(int key,bool bset);

/*���ÿ���״̬,ȡ����Դ��־
@ sem_id : �ź���ID,��sem_open()���ػ��
*/
void app_sem_set_idle(int sem_id);

/*����æ״̬,��ȡ��Դ��־,����ʱ��Դ��־������,������ȴ�
@ sem_id : �ź���ID,��sem_open()���ػ��*/
void app_sem_wait_busy(int sem_id);

//�ر��ź���
int app_sem_close(int sem_id);


/**<  �����ڴ���� **/

/*�����ڴ��ʼ������
@ key       :�ؼ���,��ͬ�Ĺؼ��ֶ�Ӧͬһ�ź���(��Դ��־)
@ size      :���빲���ڴ�����
@ retry_num :���Դ���,��һ��ʹ�ã�һ��Ϊ�����̣�����Ϊ1,����ʱ������Ϊ0
@ return    :���빲���ڴ�����ַ,ΪNULLʱ��ʾ����ʧ��;
@ about     :��retry_num��Ϊ0ʱ,������ʧ�ܣ���ͨ��ipcrmɾ��ԭ������;
*/
void *app_shm_open(int key,int size,uint8 retry_num);


//extern struct update_param_shm_st *g_p_update_param_shm;
#if 0

/*��Ϣ���пռ�����
@data_len : �ռ䳤��,��Ҫ���͵���Ϣ����*/
struct msg_buf_st *app_msg_malloc(uint16 data_len);

void *app_msg_get_date_addr(struct msg_buf_st *msg_date);

#endif
/**/


#endif // APP_IPCS_H

