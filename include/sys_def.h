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

#ifdef CON_TER_TYPE_FK_ALL		//ר��
#define CON_TER_WITH_PULSE_SAMPLE		1		//������ɼ�
#endif

//������Ϣ
#define	DBGFMT			"%s[%d]"
#define	DBGARG			__FILE__,__LINE__

#define	DBGFMT_A		"%s[%d]%d:"
#define	DBGARG_A		__FILE__,__LINE__,getpid()

#define	DBGFMT_B		"%s|%s[%d]%d:"
#define	DBGARG_B		__FILE__,__FUNCTION__,__LINE__,getpid()

#define	DBGFMT_C		"[%d]%d:"
#define	DBGARG_C		__LINE__,getpid()
//


//����汾��ΪCCXX-AIT-FFF-NNNNN ��ʽ��CC ��ʾ���̴��루BCD �룩��XX ��ʾ��ͬ����
//    �������A ���汾��I �ΰ汾��T С�汾��FFF ������Ϣ��NNNNNN �����������ʾ�ط�������Ϣ��
#define CON_SOFT_VER_CC		0x11	//11 ��¡
#define CON_SOFT_VER_XX		0x00
#define CON_SOFT_VER_AI		0x11	//AIT-FFF  1.18 - 000
#define CON_SOFT_VER_TF		0x80
#define CON_SOFT_VER_FF		0x00
#define CON_SOFT_VER_NN1	0x00
#define CON_SOFT_VER_NN2	0x80	//80 ʡ��˾
#define CON_SOFT_VER_NN3	0x01

#define CON_HARD_VER_LL		0x05
#define CON_HARD_VER_HH		0x00


#define EQLINK_CHAN_NO      0x06/*���ն�ʹ��ͨ����*/

#define MSG_TYPE_COMMDATA	1//ҵ�������Ľ���----���˿�����ͨѶ������� �����շ�
#define MSG_TYPE_CHANINFO	2//ҵ�������Ľ���----���˿�����ͨѶ������� ͨ����Ϣ����
#define MSG_TYPE_MD_RS232   3//ҵ�������Ľ���----���˿�����ͨѶ������� �������ò��� 

#define MSG_TYPE_TRANSMIT_COMMDATA 	8
#define MSG_TYPE_COMMDATA_RET		9

#define MSG_TYPE_CM_TRANSMIT			19//ҵ�������Ľ���----���豸�ɼ�������̣�������Ϣ
#define MSG_TYPE_CM_TRANSMIT_RET		20//�豸�ɼ��������----��ҵ�������Ľ��̣����ؽ����Ϣ
#define MSG_TYPE_RS485_CM_TRANSMIT		21//RS485����ӿ�----��RS485�м̳���ͨѶ������̣�������Ϣ
#define MSG_TYPE_RS485_CM_TRANSMIT_RET 	22//RS485�м̳���ͨѶ�������----���豸�ɼ�������̣����ؽ����Ϣ
#define MSG_TYPE_RS485_CM 				23//RS485����ӿ�----��RS485�������ԼͨѶ������̣�������Ϣ
										  //RS485�������ԼͨѶ�������----���豸�ɼ�������̣�����������Ϣ
#define MSG_TYPE_RS485_CM_FAILURE 		24//RS485�������ԼͨѶ�������----���豸�ɼ�������̣�����ʧ��

#define MSG_TYPE_EQP_LINKED_COMMDATA	27//ҵ�������ĳ���<-->�豸����������������շ�
#define MSG_TYPE_RS485_L_TRANSMIT		28//RS485�����ӿ�---��RS485����ת��������̣�������Ϣ
#define MSG_TYPE_RS485_L_TRANSMIT_RET	29//RS485����ת���������---���豸����������̣����ؽ����Ϣ
#define MSG_TYPE_RS485_L_WAITRECV_BEGIN 30//RS485�����ӿ�---��RS485�������մ�����̣���ʼ�˿ڵȴ�����
#define MSG_TYPE_RS485_L_WAITRECV_END	31//RS485�����ӿ�---��RS485�������մ�����̣������˿ڵȴ�����
#define MSG_TYPE_RS485_L_RECV_DATA		32//RS485�������մ������---���豸����������̣���������

#define MSG_TYPE_SIG_COLL_COMMDATA		33//״̬�ɼ�����---���豸����������̣���������
#define MSG_TYPE_PLC_CM 				40//PLC����ӿ�
#define MSG_TYPE_WIRELESS_CM			41//���߳���ӿڣ�����PLC������·�ɵȹ���
#define MSG_TYPE_SAMPLE_CM 				42//�����ɼ�

#define MSG_TYPE_CHILD	 				50//�ӽ��̷�����Ϣ
#define MSG_TYPE_CM_REALTIME			51//ҵ�������Ľ���----���豸�ɼ�������̣�ʵʱ�ٲ⣬��ʱ������ʵʱ�ٲ⡢����բ��Уʱ�ȣ�
#define MSG_TYPE_ERC                    52//�¼���Ϣ
#define MSG_TYPE_CALL_SITE              53//������վ

#define MSG_TYPE_REBOOT_APP				54	//Ӧ�ó�������
#define MSG_TYPE_REBOOT_SYS				55	//����ϵͳ����
#define MSG_TYPE_DATA_INIT				56	//��������ʼ��
#define MSG_TYPE_PARA_INIT				57	//����������ϵͳ��վͨ���йصģ���ȫ����������ʼ��
#define MSG_TYPE_FACTORY_SETTING		58	//������ȫ����������ʼ�������ָ����������ã�
#define MSG_TYPE_CQ_ON_DUTY				59	//���죬Ͷ���˳����е���Ϣ

#define MSG_TYPE_HMI_SET                60 // ��ʾ���� ���óɹ� ���͵���Ϣ
#define MSG_TYPE_HMI_DB_OK              61 // ���ݿ��ļ�׼����
#define MSG_TYPE_CHN_MSG                63 // ������Ϣ
#define MSG_TYPE_ALARM_MSG              64 // �澯����ʾ������ʾ
#define MSG_TYPE_SCAN_FLASH_OK          65 // scan flash ���
#define MSG_TYPE_HMI_NORM_MSG			66	//��ʾ���̷�����һ���¼���Ϣ

#define MSG_TYPE_ALARM_CM 				70// ��������ĳ���
#define MSG_TYPE_FLUX_LIMIT 			71// ͨ������
#define MSG_TYPE_UPDATE					72// ����������
#define MSG_TYPE_PLC_COLL_NODE_NORET	73// �����ز������±�,����Ҫ������Ϣ
#define MSG_TYPE_CM_TRANSMIT_RET_F9		74// �ز���������ת��F9
#define MSG_TYPE_CONNECT_MNG 			75// �ն�����ͨ�����ӹ���
#define MSG_TYPE_PLC_CTRL				76// �ز��������

#define MSG_TYPE_READ_METER 			77// �ֳ�����ָ�������㳭��
#define MSG_TYPE_FIND_METER				78// �ֳ������������
#define MSG_TYPE_READ_ALL_METER 		79// �ֳ��������в����㳭��
#define MSG_TYPE_READ_NEW_METER 		80// �ֳ������������ܱ��������й���
#define MSG_TYPE_RTCM_TRANSMIT_RET		81//ʵʱ����

#define MSG_TYPE_CM_TRANSMIT_RET_F10	82// �ز���������ת��F10
#define MSG_TYPE_CM_TRANSMIT_RET_F11	83// �ز���������ת��F11

#define MSG_TYPE_THREAD_HEALTH			84	//�߳̽������

#define MSG_TYPE_LCD_CLEAR_CURVE		86	//������ִ��ɾ����������

#define MSG_TYPE_TERCTRL_REMOTE_ON		0x80  //128ң����բ����
#define MSG_TYPE_TERCTRL_REMOTE_OFF		0x81  //129ң��ȡ����բ����
#define MSG_TYPE_TERCTRL_CG_AMMETER		0x82  //130�������ַ�ת

#define MSG_TYPE_MISCDATA_SET			0x90  //144ҵ�������Ľ���----���豸�ɼ�������̣��׶�����

#define CON_TASK_TYPE_PLC_CM			40//PLC��������
#define CON_TASK_TYPE_SAMPLE_CM 		42//�����ɼ�����
#define CON_TASK_TYPE_RS485_CM 			23//RS485��������

struct sys_msg_hdr{
	long type;
	unsigned long send_pid;
	unsigned char msg_type;
};
/*ͨ������*/
#define CHAN_TYPE_RS232		1
#define CHAN_TYPE_IRDA		2
#define CHAN_TYPE_RS485		3
#define CHAN_TYPE_ETHER		4
#define CHAN_TYPE_SMS		5
#define CHAN_TYPE_GPRSCDMA	6

//�ӽ��̷����¼�������Ϣ
#define MSG_CHILD_GPRS_CONNECT			1//gprs��¼�¼�
#define MSG_CHILD_ETHNET_CONNECT		2//��̫����¼�¼�

//------------------- ��ִ�г���·������ ----------------------------
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

//---------------------------- �������ʶ -----------------------------------
#define CON_DI_TYPE_NONE								0x0000//��Ч���ݱ�ʶ
#define CON_DI_TYPE_INVALID								0xBBBB//��Ч���ݱ�ʶ
#define CON_DI_TYPE_MPRELAY								0x1111//�������м�����
#define CON_DI_TYPE_EXT									0xCDCD//��չ�������ݱ�ʶ
#define	CON_DI_TYPE_MPALLDI								0xFFFF//����

//#define	CON_DI_TYPE_DATA_PULSE						0x9xxx + 0x6000//���������ʶһ������
///////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPDIRPOWTOTAL						0x9010//�����й��ܵ���
#define CON_DI_TYPE_MPDIRPOWPLUS						0x9011//�����й������
#define CON_DI_TYPE_MPDIRPOWAPEX						0x9012//�����й������
#define CON_DI_TYPE_MPDIRPOWFLAT						0x9013//�����й�ƽ����
#define CON_DI_TYPE_MPDIRPOWVALE						0x9014//�����й��ȵ���
#define CON_DI_TYPE_MPDIRPOW_BLOCK						0x901F//�����й��������ݿ�

#define CON_DI_TYPE_MPUNDIRPOWTOTAL						0x9020//�����й��ܵ���
#define CON_DI_TYPE_MPUNDIRPOWPLUS						0x9021//�����й������
#define CON_DI_TYPE_MPUNDIRPOWAPEX						0x9022//�����й������
#define CON_DI_TYPE_MPUNDIRPOWFLAT						0x9023//�����й�ƽ����
#define CON_DI_TYPE_MPUNDIRPOWVALE						0x9024//�����й��ȵ���
#define CON_DI_TYPE_MPUNDIRPOW_BLOCK 					0x902F//�����й��������ݿ�
///////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPDIRPOWTOTAL_LM					0x9410//�����й��ܵ��ܣ����£�
#define CON_DI_TYPE_MPDIRPOWPLUS_LM						0x9411//�����й�����ܣ����£�
#define CON_DI_TYPE_MPDIRPOWAPEX_LM						0x9412//�����й�����ܣ����£�
#define CON_DI_TYPE_MPDIRPOWFLAT_LM						0x9413//�����й�ƽ���ܣ����£�
#define CON_DI_TYPE_MPDIRPOWVALE_LM						0x9414//�����й��ȵ��ܣ����£�
#define CON_DI_TYPE_MPDIRPOW_LM_BLOCK					0x941F//�����й��������ݿ飨���£�

#define CON_DI_TYPE_MPUNDIRPOWTOTAL_LM					0x9420//�����й��ܵ��ܣ����£�
#define CON_DI_TYPE_MPUNDIRPOWPLUS_LM					0x9421//�����й�����ܣ����£�
#define CON_DI_TYPE_MPUNDIRPOWAPEX_LM					0x9422//�����й�����ܣ����£�
#define CON_DI_TYPE_MPUNDIRPOWFLAT_LM					0x9423//�����й�ƽ���ܣ����£�
#define CON_DI_TYPE_MPUNDIRPOWVALE_LM					0x9424//�����й��ȵ��ܣ����£�
#define CON_DI_TYPE_MPUNDIRPOW_LM_BLOCK 				0x942F//�����й��������ݿ飨���£�
///////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPDIRVARTOTAL						0x9110//�����޹��ܵ���
#define CON_DI_TYPE_MPDIRVARPLUS						0x9111//�����޹������
#define CON_DI_TYPE_MPDIRVARAPEX						0x9112//�����޹������
#define CON_DI_TYPE_MPDIRVARFLAT						0x9113//�����޹�ƽ����
#define CON_DI_TYPE_MPDIRVARVALE						0x9114//�����޹��ȵ���
#define CON_DI_TYPE_MPDIRVAR_BLOCK						0x911F//�����޹��������ݿ�

#define CON_DI_TYPE_MPUNDIRVARTOTAL						0x9120//�����޹��ܵ���
#define CON_DI_TYPE_MPUNDIRVARPLUS						0x9121//�����޹������
#define CON_DI_TYPE_MPUNDIRVARAPEX						0x9122//�����޹������
#define CON_DI_TYPE_MPUNDIRVARFLAT						0x9123//�����޹�ƽ����
#define CON_DI_TYPE_MPUNDIRVARVALE						0x9124//�����޹��ȵ���
#define CON_DI_TYPE_MPUNDIRVAR_BLOCK					0x912F//�����޹��������ݿ�
///////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPDIRVARTOTAL_LM					0x9510//�����޹��ܵ��ܣ����£�
#define CON_DI_TYPE_MPDIRVARPLUS_LM						0x9511//�����޹�����ܣ����£�
#define CON_DI_TYPE_MPDIRVARAPEX_LM						0x9512//�����޹�����ܣ����£�
#define CON_DI_TYPE_MPDIRVARFLAT_LM						0x9513//�����޹�ƽ���ܣ����£�
#define CON_DI_TYPE_MPDIRVARVALE_LM						0x9514//�����޹��ȵ��ܣ����£�
#define CON_DI_TYPE_MPDIRVAR_LM_BLOCK					0x951F//�����޹��������ݿ飨���£�

#define CON_DI_TYPE_MPUNDIRVARTOTAL_LM					0x9520//�����޹��ܵ��ܣ����£�
#define CON_DI_TYPE_MPUNDIRVARPLUS_LM					0x9521//�����޹�����ܣ����£�
#define CON_DI_TYPE_MPUNDIRVARAPEX_LM					0x9522//�����޹�����ܣ����£�
#define CON_DI_TYPE_MPUNDIRVARFLAT_LM					0x9523//�����޹�ƽ���ܣ����£�
#define CON_DI_TYPE_MPUNDIRVARVALE_LM					0x9524//�����޹��ȵ��ܣ����£�
#define CON_DI_TYPE_MPUNDIRVAR_LM_BLOCK					0x952F//�����޹��������ݿ飨���£�
/////////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPVAR1								0x9130//һ�����޹��ܵ���
#define CON_DI_TYPE_MPVAR1_FEE1							0x9131//����1
#define CON_DI_TYPE_MPVAR1_FEE2							0x9132//����2
#define CON_DI_TYPE_MPVAR1_FEE3							0x9133//����3
#define CON_DI_TYPE_MPVAR1_FEE4							0x9134//����4
#define CON_DI_TYPE_MPVAR1_BLOCK						0x913F//һ�����޹��������ݿ�

#define CON_DI_TYPE_MPVAR4								0x9140//�������޹��ܵ���
#define CON_DI_TYPE_MPVAR4_FEE1							0x9141//����1
#define CON_DI_TYPE_MPVAR4_FEE2							0x9142//����2
#define CON_DI_TYPE_MPVAR4_FEE3							0x9143//����3
#define CON_DI_TYPE_MPVAR4_FEE4							0x9144//����4
#define CON_DI_TYPE_MPVAR4_BLOCK						0x914F//һ�����޹��������ݿ�

#define CON_DI_TYPE_MPVAR2								0x9150//�������޹��ܵ���
#define CON_DI_TYPE_MPVAR2_FEE1							0x9151//����1
#define CON_DI_TYPE_MPVAR2_FEE2							0x9152//����2
#define CON_DI_TYPE_MPVAR2_FEE3							0x9153//����3
#define CON_DI_TYPE_MPVAR2_FEE4							0x9154//����4
#define CON_DI_TYPE_MPVAR2_BLOCK						0x915F//�������޹��������ݿ�

#define CON_DI_TYPE_MPVAR3								0x9160//�������޹��ܵ���
#define CON_DI_TYPE_MPVAR3_FEE1							0x9161//����1
#define CON_DI_TYPE_MPVAR3_FEE2							0x9162//����2
#define CON_DI_TYPE_MPVAR3_FEE3							0x9163//����3
#define CON_DI_TYPE_MPVAR3_FEE4							0x9164//����4
#define CON_DI_TYPE_MPVAR3_BLOCK						0x916F//�������޹��������ݿ�
///////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPVAR1_LM							0x9530//һ�����޹��ܵ��ܣ����£�
#define CON_DI_TYPE_MPVAR1_LM_FEE1						0x9531//����1
#define CON_DI_TYPE_MPVAR1_LM_FEE2						0x9532//����2
#define CON_DI_TYPE_MPVAR1_LM_FEE3						0x9533//����3
#define CON_DI_TYPE_MPVAR1_LM_FEE4						0x9534//����4
#define CON_DI_TYPE_MPVAR1_LM_BLOCK						0x953F

#define CON_DI_TYPE_MPVAR4_LM							0x9540//�������޹��ܵ��ܣ����£�
#define CON_DI_TYPE_MPVAR4_LM_FEE1						0x9541//����1
#define CON_DI_TYPE_MPVAR4_LM_FEE2						0x9542//����2
#define CON_DI_TYPE_MPVAR4_LM_FEE3						0x9543//����3
#define CON_DI_TYPE_MPVAR4_LM_FEE4						0x9544//����4
#define CON_DI_TYPE_MPVAR4_LM_BLOCK						0x954F

#define CON_DI_TYPE_MPVAR2_LM							0x9550//�������޹��ܵ��ܣ����£�
#define CON_DI_TYPE_MPVAR2_LM_FEE1						0x9551//����1
#define CON_DI_TYPE_MPVAR2_LM_FEE2						0x9552//����2
#define CON_DI_TYPE_MPVAR2_LM_FEE3						0x9553//����3
#define CON_DI_TYPE_MPVAR2_LM_FEE4						0x9554//����4
#define CON_DI_TYPE_MPVAR2_LM_BLOCK						0x955F

#define CON_DI_TYPE_MPVAR3_LM							0x9560//�������޹��ܵ��ܣ����£�
#define CON_DI_TYPE_MPVAR3_LM_FEE1						0x9561//����1
#define CON_DI_TYPE_MPVAR3_LM_FEE2						0x9562//����2
#define CON_DI_TYPE_MPVAR3_LM_FEE3						0x9563//����3
#define CON_DI_TYPE_MPVAR3_LM_FEE4						0x9564//����4
#define CON_DI_TYPE_MPVAR3_LM_BLOCK						0x956F
///////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND					0xA010//�����й����������
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_FEE1				0xA011//����1
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_FEE2				0xA012//����2
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_FEE3				0xA013//����3
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_FEE4				0xA014//����4
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_BLOCK				0xA01F

#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND					0xA020//�����й����������
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_FEE1			0xA021//����1
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_FEE2			0xA022//����2
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_FEE3			0xA023//����3
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_FEE4			0xA024//����4
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_BLOCK			0xA02F

#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME				0xB010//�����й��������������ʱ��
#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_FEE1			0xB011//����1
#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_FEE2			0xB012//����2
#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_FEE3			0xB013//����3
#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_FEE4			0xB014//����4
#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_BLOCK			0xB01F

#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME				0xB020//�����й��������������ʱ��
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_FEE1		0xB021//����1
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_FEE2		0xB022//����2
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_FEE3		0xB023//����3
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_FEE4		0xB024//����4
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_BLOCK		0xB02F

#define CON_DI_TYPE_MPDIRVARMAXDEMAND					0xA110//�����޹����������
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_FEE1				0xA111//����1
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_FEE2				0xA112//����2
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_FEE3				0xA113//����3
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_FEE4				0xA114//����4
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_BLOCK				0xA11F

#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND					0xA120//�����޹����������
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_FEE1			0xA121//����1
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_FEE2			0xA122//����2
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_FEE3			0xA123//����3
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_FEE4			0xA124//����4
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_BLOCK			0xA12F

#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME				0xB110//�����޹��������������ʱ��
#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_FEE1			0xB111//����1
#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_FEE2			0xB112//����2
#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_FEE3			0xB113//����3
#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_FEE4			0xB114//����4
#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_BLOCK			0xB11F

#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME				0xB120//�����޹��������������ʱ��
#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_FEE1		0xB121//����1
#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_FEE2		0xB122//����2
#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_FEE3		0xB123//����3
#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_FEE4		0xB124//����4
#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_BLOCK		0xB12F

///////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_LM				0xA410//�����й���������������£�
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_LM_FEE1			0xA411//����1
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_LM_FEE2			0xA412//����2
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_LM_FEE3			0xA413//����3
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_LM_FEE4			0xA414//����4
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_LM_BLOCK			0xA41F
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_LM				0xA420//�����й���������������£�
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_LM_FEE1			0xA421//����1
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_LM_FEE2			0xA422//����2
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_LM_FEE3			0xA423//����3
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_LM_FEE4			0xA424//����4
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_LM_BLOCK		0xA42F

#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_LM			0xB410//�����й��������������ʱ�䣨���£�
#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_LM_FEE1		0xB411//����1
#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_LM_FEE2		0xB412//����2
#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_LM_FEE3		0xB413//����3
#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_LM_FEE4		0xB414//����4
#define CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_LM_BLOCK		0xB41F
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_LM			0xB420//�����й��������������ʱ�䣨���£�
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_LM_FEE1		0xB421//����1
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_LM_FEE2		0xB422//����2
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_LM_FEE3		0xB423//����3
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_LM_FEE4		0xB424//����4
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_LM_BLOCK	0xB42F

#define CON_DI_TYPE_MPDIRVARMAXDEMAND_LM				0xA510//�����޹���������������£�
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_LM_FEE1			0xA511//����1
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_LM_FEE2			0xA512//����2
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_LM_FEE3			0xA513//����3
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_LM_FEE4			0xA514//����4
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_LM_BLOCK			0xA51F
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_LM				0xA520//�����޹���������������£�
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_LM_FEE1			0xA521//����1
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_LM_FEE2			0xA522//����2
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_LM_FEE3			0xA523//����3
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_LM_FEE4			0xA524//����4
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_LM_BLOCK		0xA52F

#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_LM			0xB510//�����޹��������������ʱ�䣨���£�
#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_LM_FEE1		0xB511//����1
#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_LM_FEE2		0xB512//����2
#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_LM_FEE3		0xB513//����3
#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_LM_FEE4		0xB514//����4
#define CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_LM_BLOCK		0xB51F
#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_LM			0xB520//�����޹��������������ʱ�䣨���£�
#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_LM_FEE1		0xB521//����1
#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_LM_FEE2		0xB522//����2
#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_LM_FEE3		0xB523//����3
#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_LM_FEE4		0xB524//����4
#define CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_LM_BLOCK	0xB52F

//////////////////////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPLATELYPROGTIME					0xB210//���һ�α��ʱ��
#define CON_DI_TYPE_MPLATELYMAXDEMANDCLEARTIME			0xB211//���һ�������������ʱ��
#define CON_DI_TYPE_MPPROGTIMETIMES						0xB212//��̴���
#define CON_DI_TYPE_MPMAXDEMANDCLEARTIMES				0xB213//��������������
#define CON_DI_TYPE_MPBATWORKTIME						0xB214//��ع���ʱ��
#define CON_DI_TYPE_MPMETERCLEARTIMES					0xB215//��������ܴ���
#define CON_DI_TYPE_MPLATELYMETERCLEARTIME				0xB216//���һ�ε�����㷢��ʱ��
#define CON_DI_TYPE_MPEVENTCLEARTIMES					0xB217//�¼������ܴ���
#define CON_DI_TYPE_MPLATELYEVENTCLEARTIME				0xB218//���һ���¼����㷢��ʱ��
#define CON_DI_TYPE_MPTIMINGTIMES							0xB219//Уʱ�ܴ���
#define CON_DI_TYPE_MPLATELYTIMINGTIME					0xB21A//���һ��Уʱ����ʱ��
#define CON_DI_TYPE_MPB21F_BLOCK						0xB21F

#define CON_DI_TYPE_MPVOLBREAKNUM						0xB310
#define CON_DI_TYPE_MPVOLBREAKNUMA						0xB311
#define CON_DI_TYPE_MPVOLBREAKNUMB						0xB312
#define CON_DI_TYPE_MPVOLBREAKNUMC						0xB313
#define CON_DI_TYPE_MPB31F_BLOCK						0xB31F		//�������

#define CON_DI_TYPE_MPVOLBREAKTIME						0xB320
#define CON_DI_TYPE_MPVOLBREAKTIMEA						0xB321
#define CON_DI_TYPE_MPVOLBREAKTIMEB						0xB322
#define CON_DI_TYPE_MPVOLBREAKTIMEC						0xB323
#define CON_DI_TYPE_MPB32F_BLOCK						0xB32F		//�ۼƶ���ʱ��

#define CON_DI_TYPE_MPLASTVOLBREAKBEGTIME				0xB330
#define CON_DI_TYPE_MPLASTVOLBREAKBEGTIMEA				0xB331
#define CON_DI_TYPE_MPLASTVOLBREAKBEGTIMEB				0xB332
#define CON_DI_TYPE_MPLASTVOLBREAKBEGTIMEC				0xB333
#define CON_DI_TYPE_MPB33F_BLOCK						0xB33F		//���һ�ζ�����ʼʱ��

#define CON_DI_TYPE_MPLASTVOLBREAKENDTIME				0xB340
#define CON_DI_TYPE_MPLASTVOLBREAKENDTIMEA				0xB341
#define CON_DI_TYPE_MPLASTVOLBREAKENDTIMEB				0xB342
#define CON_DI_TYPE_MPLASTVOLBREAKENDTIMEC				0xB343
#define CON_DI_TYPE_MPB34F_BLOCK						0xB34F		//���һ�ζ������ʱ��

///////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPVOLA								0xB611//A���ѹ
#define CON_DI_TYPE_MPVOLB								0xB612//B���ѹ
#define CON_DI_TYPE_MPVOLC								0xB613//C���ѹ
#define CON_DI_TYPE_MPVOL_BLOCK							0xB61F//��ѹ���ݿ�

#define CON_DI_TYPE_MPCURA								0xB621//A�����
#define CON_DI_TYPE_MPCURB								0xB622//B�����
#define CON_DI_TYPE_MPCURC								0xB623//C����� 
#define CON_DI_TYPE_MPCUR_BLOCK							0xB62F//�������ݿ�

#define CON_DI_TYPE_MPINSTANTPOW						0xB630//˲ʱ�й�����
#define CON_DI_TYPE_MPINSTANTPOWA						0xB631//A���й�����
#define CON_DI_TYPE_MPINSTANTPOWB						0xB632//B���й�����
#define CON_DI_TYPE_MPINSTANTPOWC						0xB633//C���й�����
#define CON_DI_TYPE_MPINSTANTPOW_BLOCK					0xB63F//

#define CON_DI_TYPE_MPINSTANTVAR						0xB640//˲ʱ�޹�����
#define CON_DI_TYPE_MPINSTANTVARA						0xB641//A���޹�����
#define CON_DI_TYPE_MPINSTANTVARB						0xB642//B���޹�����
#define CON_DI_TYPE_MPINSTANTVARC						0xB643//C���޹�����
#define CON_DI_TYPE_MPINSTANTVAR_BLOCK					0xB64F//

#define	CON_DI_TYPE_MPPOWRATE							0xB650//�ܹ�������
#define	CON_DI_TYPE_MPPOWRATEA							0xB651//A�๦������
#define	CON_DI_TYPE_MPPOWRATEB							0xB652//B�๦������
#define	CON_DI_TYPE_MPPOWRATEC							0xB653//C�๦������
#define	CON_DI_TYPE_MPPOWRATE_BLOCK						0xB65F//

#define CON_DI_TYPE_MPINSTANTSTOTAL						0xB660//˲ʱ���ڹ���
#define CON_DI_TYPE_MPINSTANTSA						    0xB661//A�����ڹ���
#define CON_DI_TYPE_MPINSTANTSB						    0xB662//B�����ڹ���
#define CON_DI_TYPE_MPINSTANTSC						    0xB663//C�����ڹ���
#define CON_DI_TYPE_MPINSTANTS_BLOCK					0xB66F//

///////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPPOWCONST							0xC030//�й�����
#define CON_DI_TYPE_MPVARCONST							0xC031//�޹�����
#define CON_DI_TYPE_MPCONST_BLOCK						0xC03F//

#define CON_DI_TYPE_MPFEERATE1							0xC331//����1
#define CON_DI_TYPE_MPFEERATE2							0xC332//����2
#define CON_DI_TYPE_MPFEERATE3							0xC333//����3
#define CON_DI_TYPE_MPFEERATE4							0xC334//����4
#define CON_DI_TYPE_MPFEERATE5							0xC335//����5
#define CON_DI_TYPE_MPFEERATE6							0xC336//����6
#define CON_DI_TYPE_MPFEERATE7							0xC337//����7
#define CON_DI_TYPE_MPFEERATE8							0xC338//����8
#define CON_DI_TYPE_MPFEERATE_BLOCK						0xC33F	
///////////////////////////////////////////////////////////////////////////////
#define CON_DI_TYPE_MPDATEANDWEEK						0xC010//���ڼ��ܴ�
#define CON_DI_TYPE_MPTIME								0xC011//ʱ��
#define CON_DI_TYPE_MPDATETIME_BLOCK					0xC01F//
#define CON_DI_TYPE_MPMETERSTATFLAG						0xC020//�������״̬��
#define CON_DI_TYPE_MPNETSTATFLAG						0xC021//��������״̬��
#define CON_DI_TYPE_MPCO2F_BLOCK						0xC02F
#define CON_DI_TYPE_MPCOPYDAYTIME						0xC117//������
#define CON_DI_TYPE_MPC11F_BLOCK						0xC11F

//---------- dlt645-2007 ��Լ��Ӧ���� 0x5000 0x6FFF ֧��8192�� start ------------
#define CON_DI_TYPE_CU_LOST								0x5000//(��ǰ)ͭ���й��ܵ��ܲ�����
#define CON_DI_TYPE_FE_LOST								0x5001//(��ǰ)�����й��ܵ��ܲ�����
#define CON_DI_TYPE_DIRPOW_A							0x5011//(��ǰ)A�������й�����
#define CON_DI_TYPE_DIRPOW_B							0x5012//(��ǰ)B�������й�����
#define CON_DI_TYPE_DIRPOW_C							0x5013//(��ǰ)C�������й�����
#define CON_DI_TYPE_UNDIRPOW_A							0x5021//(��ǰ)A�෴���й�����
#define CON_DI_TYPE_UNDIRPOW_B							0x5022//(��ǰ)B�෴���й�����
#define CON_DI_TYPE_UNDIRPOW_C							0x5023//(��ǰ)C�෴���й�����
#define CON_DI_TYPE_SUMVAR1_A							0x5031//(��ǰ)A������޹�1����
#define CON_DI_TYPE_SUMVAR1_B							0x5032//(��ǰ)B������޹�1����
#define CON_DI_TYPE_SUMVAR1_C							0x5033//(��ǰ)C������޹�1����
#define CON_DI_TYPE_SUMVAR2_A							0x5041//(��ǰ)A������޹�2����
#define CON_DI_TYPE_SUMVAR2_B							0x5042//(��ǰ)B������޹�2����
#define CON_DI_TYPE_SUMVAR2_C							0x5043//(��ǰ)C������޹�2����
#define CON_DI_TYPE_MP500F_BLOCK						0x500F
#define CON_DI_TYPE_MP501F_BLOCK						0x501F
#define CON_DI_TYPE_MP502F_BLOCK						0x502F
#define CON_DI_TYPE_MP503F_BLOCK						0x503F
#define CON_DI_TYPE_MP504F_BLOCK						0x504F

#define CON_DI_TYPE_METER_STAT_FLAG_1					0x5051//�������״̬��
#define CON_DI_TYPE_METER_STAT_FLAG_2					0x5052//�������״̬��
#define CON_DI_TYPE_METER_STAT_FLAG_3					0x5053//�������״̬��
#define CON_DI_TYPE_METER_STAT_FLAG_4					0x5054//�������״̬��
#define CON_DI_TYPE_METER_STAT_FLAG_5					0x5055//�������״̬��
#define CON_DI_TYPE_METER_STAT_FLAG_6					0x5056//�������״̬��
#define CON_DI_TYPE_METER_STAT_FLAG_7					0x5057//�������״̬��

#define CON_DI_TYPE_METER_CHANGE_FLAG_1					0x5058//�������״̬�ֱ�λ��־
#define CON_DI_TYPE_METER_CHANGE_FLAG_2					0x5059//�������״̬�ֱ�λ��־
#define CON_DI_TYPE_METER_CHANGE_FLAG_3					0x505A//�������״̬�ֱ�λ��־
#define CON_DI_TYPE_METER_CHANGE_FLAG_4					0x505B//�������״̬�ֱ�λ��־
#define CON_DI_TYPE_METER_CHANGE_FLAG_5					0x505C//�������״̬�ֱ�λ��־
#define CON_DI_TYPE_METER_CHANGE_FLAG_6					0x505D//�������״̬�ֱ�λ��־
#define CON_DI_TYPE_METER_CHANGE_FLAG_7					0x505E//�������״̬�ֱ�λ��־

#define CON_DI_TYPE_METER_STAT_FLAG_BLOCK				0x505F
#define CON_DI_TYPE_METER_OPEN_SWITCH                   0x5060//����1�Σ���բ����ʱ��
#define CON_DI_TYPE_METER_CLOSE_SWITCH                  0x5061//����1�Σ���բ����ʱ��

#define CON_DI_TYPE_METER_REMAIN_MONEY                  0x5062//����ǰ��ʣ����
#define CON_DI_TYPE_METER_OVERDRAFT                     0x5063//����ǰ��͸֧���
#define CON_DI_TYPE_METER_BUYPOW_TIMES_TOTAL            0x5064//��1�ι�����ܹ������
#define CON_DI_TYPE_METER_BUYPOW_MENEY_TOTAL            0x5065//��1�ι�����ۼƹ�����

#define CON_DI_TYPE_METER_HOUR_FREEZE_TIME              0x5066  //����1�Σ����㶳��ʱ��
#define CON_DI_TYPE_METER_HOUR_FREEZE_DIRPOWTOL         0x5067  //����1�Σ����㶳�������й��ܵ���
#define CON_DI_TYPE_METER_HOUR_FREEZE_REVPOWTOL         0x5068  //����1�Σ����㶳�ᷴ���й��ܵ���
#define CON_DI_TYPE_METER_HOUR_FREEZE_BLOCK             0x5069  //����1�Σ����㶳�����ݿ�

#define CON_DI_TYPE_METER_DAY_FREEZE_DI_START		0x506A  //����1�Σ��ն�����ʼ�������ʶ
#define CON_DI_TYPE_METER_DAY_FREEZE_TIME               0x506a  //����1�Σ��ն���ʱ��
#define CON_DI_TYPE_METER_DAY_FREEZE_DIRPOW               0x506b  //����1�Σ��ն��������й���������
#define CON_DI_TYPE_METER_DAY_FREEZE_REVPOW               0x506c  //����1�Σ��ն��ᷴ���й���������
#define CON_DI_TYPE_METER_DAY_FREEZE_DIRVAR               0x506d  //����1�Σ��ն�������޹�1��������
#define CON_DI_TYPE_METER_DAY_FREEZE_REVVAR               0x506e  //����1�Σ��ն�������޹�2��������
#define CON_DI_TYPE_METER_DAY_FREEZE_VAR1               0x506f    //����1�Σ��ն����һ�����޹���������
#define CON_DI_TYPE_METER_DAY_FREEZE_VAR2               0x5071  //����1�Σ��ն���ڶ������޹���������
#define CON_DI_TYPE_METER_DAY_FREEZE_VAR3               0x5072  //����1�Σ��ն�����������޹���������
#define CON_DI_TYPE_METER_DAY_FREEZE_VAR4               0x5073  //����1�Σ��ն�����������޹���������
#define CON_DI_TYPE_METER_DAY_FREEZE_DIRPOWDEMAND               0x5074  //����1�Σ��ն��������й��������������ʱ�����ݣ�
#define CON_DI_TYPE_METER_DAY_FREEZE_REVPOWDEMAND               0x5075  //����1�Σ��ն��ᷴ���й��������������ʱ�����ݣ�
#define CON_DI_TYPE_METER_DAY_FREEZE_POWER               0x5076  //����1�Σ��ն���������ݣ�����
#define CON_DI_TYPE_METER_DAY_FREEZE_DI_END		0x5076  //����1�Σ��ն������������ʶ


#define CON_DI_TYPE_CU_LOST_LM							0x6000//(��1������)ͭ���й��ܵ��ܲ�����
#define CON_DI_TYPE_FE_LOST_LM							0x6001//(��1������)�����й��ܵ��ܲ�����
#define CON_DI_TYPE_DIRPOW_A_LM							0x6011//(��1������)A�������й�����
#define CON_DI_TYPE_DIRPOW_B_LM							0x6012//(��1������)B�������й�����
#define CON_DI_TYPE_DIRPOW_C_LM							0x6013//(��1������)C�������й�����
#define CON_DI_TYPE_UNDIRPOW_A_LM						0x6021//(��1������)A�෴���й�����
#define CON_DI_TYPE_UNDIRPOW_B_LM						0x6022//(��1������)B�෴���й�����
#define CON_DI_TYPE_UNDIRPOW_C_LM						0x6023//(��1������)C�෴���й�����
#define CON_DI_TYPE_SUMVAR1_A_LM						0x6031//(��1������)A������޹�1����
#define CON_DI_TYPE_SUMVAR1_B_LM						0x6032//(��1������)B������޹�1����
#define CON_DI_TYPE_SUMVAR1_C_LM						0x6033//(��1������)C������޹�1����
#define CON_DI_TYPE_SUMVAR2_A_LM						0x6041//(��1������)A������޹�2����
#define CON_DI_TYPE_SUMVAR2_B_LM						0x6042//(��1������)B������޹�2����
#define CON_DI_TYPE_SUMVAR2_C_LM						0x6043//(��1������)C������޹�2����
#define CON_DI_TYPE_MP600F_LM_BLOCK                     0x600F
#define CON_DI_TYPE_MP601F_LM_BLOCK                     0x601F
#define CON_DI_TYPE_MP602F_LM_BLOCK                     0x602F
#define CON_DI_TYPE_MP603F_LM_BLOCK                     0x603F
#define CON_DI_TYPE_MP604F_LM_BLOCK                     0x604F

//г�����������������=0λ�÷��ʣ�
//�ڱ��������ݰ����ڱ���������
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_TOL      0x6050//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_1      0x6051//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_2      0x6052//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_3      0x6053//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_4      0x6054//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_5      0x6055//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_6      0x6056//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_7      0x6057//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_8      0x6058//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_9      0x6059//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_10      0x605a//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_11      0x605b//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_12      0x605c//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_13      0x605d//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_14      0x605e//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_15      0x605f//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_16      0x6060//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_17      0x6061//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_18      0x6062//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_19      0x6063//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_20      0x6064//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_21      0x6065//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLA_BLOCK   0x6066//��ѹг����Чֵ���ݿ�


#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_TOL  0x6070//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_1      0x6071//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_2      0x6072//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_3      0x6073//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_4      0x6074//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_5      0x6075//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_6      0x6076//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_7      0x6077//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_8      0x6078//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_9      0x6079//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_10      0x607a//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_11      0x607b//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_12      0x607c//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_13      0x607d//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_14      0x607e//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_15      0x607f//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_16      0x6080//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_17      0x6081//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_18      0x6082//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_19      0x6083//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_20      0x6084//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_21      0x6085//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLB_BLOCK   0x6086//��ѹг����Чֵ���ݿ�

#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_TOL  0x6090//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_1      0x6091//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_2      0x6092//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_3      0x6093//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_4      0x6094//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_5      0x6095//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_6      0x6096//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_7      0x6097//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_8      0x6098//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_9      0x6099//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_10      0x609a//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_11      0x609b//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_12      0x609c//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_13      0x609d//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_14      0x609e//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_15      0x609f//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_16      0x60a0//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_17      0x60a1//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_18      0x60a2//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_19      0x60a3//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_20      0x60a4//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_21      0x60a5//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_VOLC_BLOCK   0x60a6//��ѹг����Чֵ���ݿ�

#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_TOL  0x60b0//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_1      0x60b1//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_2      0x60b2//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_3      0x60b3//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_4      0x60b4//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_5      0x60b5//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_6      0x60b6//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_7      0x60b7//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_8      0x60b8//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_9      0x60b9//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_10      0x60ba//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_11      0x60bb//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_12      0x60bc//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_13      0x60bd//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_14      0x60be//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_15      0x60bf//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_16      0x60c0//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_17      0x60c1//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_18      0x60c2//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_19      0x60c3//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_20      0x60c4//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_21     0x60c5//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_BLOCK   0x60c6//��ѹг����Чֵ���ݿ�

#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_TOL  0x60d0//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_1      0x60d1//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_2      0x60d2//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_3      0x60d3//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_4      0x60d4//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_5      0x60d5//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_6      0x60d6//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_7      0x60d7//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_8      0x60d8//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_9      0x60d9//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_10      0x60da//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_11      0x60db//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_12      0x60dc//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_13      0x60dd//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_14      0x60de//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_15      0x60df//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_16      0x60e0//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_17      0x60e1//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_18      0x60e2//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_19      0x60e3//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_20      0x60e4//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_21     0x60e5//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURB_BLOCK   0x60e6//��ѹг����Чֵ���ݿ�

#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_TOL  0x60f0//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_1      0x60f1//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_2      0x60f2//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_3      0x60f3//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_4      0x60f4//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_5      0x60f5//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_6      0x60f6//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_7      0x60f7//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_8      0x60f8//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_9      0x60f9//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_10      0x60fa//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_11      0x60fb//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_12      0x60fc//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_13      0x60fd//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_14      0x60fe//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_15      0x60ff//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_16      0x6100//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_17      0x6101//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_18      0x6102//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_19      0x6103//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_20      0x6104//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_21     0x6105//��ѹг����Чֵ���ݿ�
#define CON_DI_TYPE_MPHARMONIC_VAL_CURC_BLOCK   0x6106//��ѹг����Чֵ���ݿ�

////////////////////////////////////////

#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_TOL  0x6110//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_1      0x6111//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_2      0x6112//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_3      0x6113//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_4      0x6114//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_5      0x6115//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_6      0x6116//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_7      0x6117//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_8      0x6118//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_9      0x6119//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_10      0x611a//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_11      0x611b//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_12      0x611c//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_13      0x611d//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_14      0x611e//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_15      0x611f//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_16      0x6120//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_17      0x6121//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_18      0x6122//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_19      0x6123//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_20      0x6124//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_21      0x6125//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_BLOCK  0x6126 //��ѹг�����������ݿ�

#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_TOL  0x6130//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_1      0x6131//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_2      0x6132//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_3      0x6133//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_4      0x6134//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_5      0x6135//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_6      0x6136//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_7      0x6137//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_8      0x6138//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_9      0x6139//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_10      0x613a//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_11      0x613b//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_12      0x613c//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_13      0x613d//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_14      0x613e//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_15      0x613f//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_16      0x6140//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_17      0x6141//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_18      0x6142//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_19      0x6143//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_20      0x6144//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_21      0x6145//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLB_BLOCK  0x6146 //��ѹг�����������ݿ�

#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_TOL  0x6150//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_1      0x6151//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_2      0x6152//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_3      0x6153//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_4      0x6154//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_5      0x6155//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_6      0x6156//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_7      0x6157//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_8      0x6158//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_9      0x6159//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_10      0x615a//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_11      0x615b//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_12      0x615c//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_13      0x615d//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_14      0x615e//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_15      0x615f//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_16      0x6160//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_17      0x6161//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_18      0x6162//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_19      0x6163//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_20      0x6164//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_21      0x6165//��ѹг�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_VOLC_BLOCK  0x6166 //��ѹг�����������ݿ�

#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_TOL      0x6170//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_1      0x6171//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_2      0x6172//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_3      0x6173//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_4      0x6174//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_5      0x6175//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_6      0x6176//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_7      0x6177//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_8      0x6178//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_9      0x6179//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_10      0x617a//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_11      0x617b//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_12      0x617c//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_13      0x617d//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_14      0x617e//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_15      0x617f//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_16      0x6180//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_17      0x6181//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_18      0x6182//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_19      0x6183//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_20      0x6184//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_21      0x6185//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURA_BLOCK   0x6186//����г�����������ݿ�

#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_TOL      0x6190//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_1      0x6191//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_2      0x6192//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_3      0x6193//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_4      0x6194//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_5      0x6195//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_6      0x6196//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_7      0x6197//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_8      0x6198//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_9      0x6199//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_10      0x619a//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_11      0x619b//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_12      0x619c//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_13      0x619d//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_14      0x619e//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_15      0x619f//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_16      0x61a0//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_17      0x61a1//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_18      0x61a2//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_19      0x61a3//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_20      0x61a4//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_21      0x61a5//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURB_BLOCK   0x61a6//����г�����������ݿ�

#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_TOL      0x61b0//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_1      0x61b1//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_2      0x61b2//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_3      0x61b3//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_4      0x61b4//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_5      0x61b5//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_6      0x61b6//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_7      0x61b7//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_8      0x61b8//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_9      0x61b9//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_10      0x61ba//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_11      0x61bb//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_12      0x61bc//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_13      0x61bd//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_14      0x61be//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_15      0x61bf//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_16      0x61c0//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_17      0x61c1//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_18      0x61c2//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_19      0x61c3//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_20      0x61c4//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_21      0x61c5//����г�����������ݿ�
#define CON_DI_TYPE_MPHARMONIC_RATE_CURC_BLOCK   0x61c6//����г�����������ݿ�

#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_TOL_MAX_TIME    0x6200//��ѹг�����������ֵ�ͷ���ʱ��
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

#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_TOL_MAX_TIME    0x6260//����г�����ֵ�ͷ���ʱ��
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

#define CON_DI_TYPE_MPHARMONIC_RATE_VOLA_TOL_OVER_TIME    0x6300//��ѹг��������Խ���ۼ�ʱ��
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

#define CON_DI_TYPE_MPHARMONIC_VAL_CURA_TOL_OVER_TIME    0x6360//����г��Խ���ۼ�ʱ��
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

//��λ�Ƕ���(���Ƕ�ӦUa)
//#define CON_DI_TYPE_MPPHS_ANGLE_VAL_A                                     0x6400   
//#define CON_DI_TYPE_MPPHS_ANGLE_VAL_B                                     0x6401
//#define CON_DI_TYPE_MPPHS_ANGLE_VAL_C                                     0x6402
#define CON_DI_TYPE_MPPHS_ANGLE_VAL_ALL                                 0x640F

//#define CON_DI_TYPE_MPPHS_ANGLE_I_A                                         0x6410
//#define CON_DI_TYPE_MPPHS_ANGLE_I_B                                         0x6411
//#define CON_DI_TYPE_MPPHS_ANGLE_I_C                                         0x6412
#define CON_DI_TYPE_MPPHS_ANGLE_I_ALL                                     0x641F

//---------- dlt645-2007 ��Լ��Ӧ���� 0x5000 0x6FFF ֧��8192�� end   ------------

//---------- �Զ��� 0x7600 0x7FFF ֧��2560�� -----------------------
#define CON_DI_TYPE_MPINSTANTPOW_ZEROTIME				0x7620//˲ʱ���й����ʷ���ʱ��
#define CON_DI_TYPE_MPINSTANTPOWA_ZEROTIME				0x7621//A�����й����ʷ���ʱ��
#define CON_DI_TYPE_MPINSTANTPOWB_ZEROTIME				0x7622//B�����й����ʷ���ʱ��
#define CON_DI_TYPE_MPINSTANTPOWC_ZEROTIME				0x7623//C�����й����ʷ���ʱ��

#define CON_DI_TYPE_MPINSTANTPOW_MAX					0x7630//˲ʱ����й�����
#define CON_DI_TYPE_MPINSTANTPOWA_MAX					0x7631//A������й�����
#define CON_DI_TYPE_MPINSTANTPOWB_MAX					0x7632//B������й�����
#define CON_DI_TYPE_MPINSTANTPOWC_MAX					0x7633//C������й�����

#define CON_DI_TYPE_MPINSTANTPOW_MAXTIME				0x7640//˲ʱ����й����ʷ���ʱ��
#define CON_DI_TYPE_MPINSTANTPOWA_MAXTIME				0x7641//A������й����ʷ���ʱ��
#define CON_DI_TYPE_MPINSTANTPOWB_MAXTIME				0x7642//B������й����ʷ���ʱ��
#define CON_DI_TYPE_MPINSTANTPOWC_MAXTIME				0x7643//C������й����ʷ���ʱ��

#define CON_DI_TYPE_MPPOWMAXDEMAND						0x7650//�����й����������
#define CON_DI_TYPE_MPPOWMAXDEMANDA						0x7651
#define CON_DI_TYPE_MPPOWMAXDEMANDB						0x7652
#define CON_DI_TYPE_MPPOWMAXDEMANDC						0x7653

#define CON_DI_TYPE_MPPOWMAXDEMAND_TIME					0x7660//�����й��������������ʱ��
#define CON_DI_TYPE_MPPOWMAXDEMANDA_TIME				0x7661
#define CON_DI_TYPE_MPPOWMAXDEMANDB_TIME				0x7662
#define CON_DI_TYPE_MPPOWMAXDEMANDC_TIME				0x7663

#define CON_DI_TYPE_MPMAXVOLA							0x7671//A������ѹ
#define CON_DI_TYPE_MPMAXVOLB							0x7672//B������ѹ
#define CON_DI_TYPE_MPMAXVOLC							0x7673//C������ѹ

#define CON_DI_TYPE_MPMAXVOLA_TIME						0x7681//A������ѹ����ʱ��
#define CON_DI_TYPE_MPMAXVOLB_TIME						0x7682//B������ѹ����ʱ��
#define CON_DI_TYPE_MPMAXVOLC_TIME						0x7683//C������ѹ����ʱ��

#define CON_DI_TYPE_MPMINVOLA							0x7691//A����С��ѹ
#define CON_DI_TYPE_MPMINVOLB							0x7692//B����С��ѹ
#define CON_DI_TYPE_MPMINVOLC							0x7693//C����С��ѹ

#define CON_DI_TYPE_MPMINVOLA_TIME						0x76A1//A����С��ѹ����ʱ��
#define CON_DI_TYPE_MPMINVOLB_TIME						0x76A2//B����С��ѹ����ʱ��
#define CON_DI_TYPE_MPMINVOLC_TIME						0x76A3//C����С��ѹ����ʱ��

#define CON_DI_TYPE_MP_NORMAL_TIME_VOLA					0x76B1//A���ѹ�ϸ�ʱ��
#define CON_DI_TYPE_MP_NORMAL_TIME_VOLB					0x76B2//B���ѹ�ϸ�ʱ��
#define CON_DI_TYPE_MP_NORMAL_TIME_VOLC					0x76B3//C���ѹ�ϸ�ʱ��

#define CON_DI_TYPE_MP_ERRUP_TIME_VOLA					0x76C1//A���ѹԽ������ʱ��
#define CON_DI_TYPE_MP_ERRUP_TIME_VOLB					0x76C2//B���ѹԽ������ʱ��
#define CON_DI_TYPE_MP_ERRUP_TIME_VOLC					0x76C3//C���ѹԽ������ʱ��

#define CON_DI_TYPE_MP_NORUP_TIME_VOLA					0x76D1//A���ѹԽ����ʱ��
#define CON_DI_TYPE_MP_NORUP_TIME_VOLB					0x76D2//B���ѹԽ����ʱ��
#define CON_DI_TYPE_MP_NORUP_TIME_VOLC					0x76D3//C���ѹԽ����ʱ��

#define CON_DI_TYPE_MP_ERRDOWN_TIME_VOLA				0x76E1//A���ѹԽ������ʱ��
#define CON_DI_TYPE_MP_ERRDOWN_TIME_VOLB				0x76E2//B���ѹԽ������ʱ��
#define CON_DI_TYPE_MP_ERRDOWN_TIME_VOLC				0x76E3//C���ѹԽ������ʱ��

#define CON_DI_TYPE_MP_NORDOWN_TIME_VOLA				0x76F1//A���ѹԽ����ʱ��
#define CON_DI_TYPE_MP_NORDOWN_TIME_VOLB				0x76F2//B���ѹԽ����ʱ��
#define CON_DI_TYPE_MP_NORDOWN_TIME_VOLC				0x76F3//C���ѹԽ����ʱ��

#define CON_DI_TYPE_MP_STAT_TIME_VOLA					0x77A1//A���ѹͳ��ʱ��
#define CON_DI_TYPE_MP_STAT_TIME_VOLB					0x77A2//B���ѹͳ��ʱ��
#define CON_DI_TYPE_MP_STAT_TIME_VOLC					0x77A3//C���ѹͳ��ʱ��

#define CON_DI_TYPE_MP_SUM_VOLA							0x7701//A���ѹ�ۼ�
#define CON_DI_TYPE_MP_SUM_VOLB							0x7702//B���ѹ�ۼ�
#define CON_DI_TYPE_MP_SUM_VOLC							0x7703//C���ѹ�ۼ�

#define CON_DI_TYPE_MP_MAX_CURRA						0x7711//A��������
#define CON_DI_TYPE_MP_MAX_CURRB						0x7712//B��������
#define CON_DI_TYPE_MP_MAX_CURRC						0x7713//C��������
#define CON_DI_TYPE_MP_MAX_CURRN						0x7714//N��������

#define CON_DI_TYPE_MP_MAX_CURRA_TIME					0x7721//A������������ʱ��
#define CON_DI_TYPE_MP_MAX_CURRB_TIME					0x7722//B������������ʱ��
#define CON_DI_TYPE_MP_MAX_CURRC_TIME					0x7723//C������������ʱ��
#define CON_DI_TYPE_MP_MAX_CURRN_TIME					0x7724//N������������ʱ��

#define CON_DI_TYPE_MP_ERRUP_TIME_CURRA					0x7731//A�����Խ������ʱ��
#define CON_DI_TYPE_MP_ERRUP_TIME_CURRB					0x7732//B�����Խ������ʱ��
#define CON_DI_TYPE_MP_ERRUP_TIME_CURRC					0x7733//C�����Խ������ʱ��
#define CON_DI_TYPE_MP_ERRUP_TIME_CURRN					0x7734//N�����Խ������ʱ��

#define CON_DI_TYPE_MP_NORUP_TIME_CURRA					0x7741//A�����Խ����ʱ��
#define CON_DI_TYPE_MP_NORUP_TIME_CURRB					0x7742//B�����Խ����ʱ��
#define CON_DI_TYPE_MP_NORUP_TIME_CURRC					0x7743//C�����Խ����ʱ��
#define CON_DI_TYPE_MP_NORUP_TIME_CURRN					0x7744//N�����Խ����ʱ��

#define CON_DI_TYPE_MP_UNBALANCE_TIME_VOLT				0x7750//��ѹ��ƽ��ʱ��
#define CON_DI_TYPE_MP_UNBALANCE_TIME_CURR				0x7751//������ƽ��ʱ��
#define CON_DI_TYPE_MP_UNBALANCE_MAX_VOLT				0x7752//��ѹ��ƽ�����ֵ
#define CON_DI_TYPE_MP_UNBALANCE_MAX_CURR				0x7753//������ƽ�����ֵ
#define CON_DI_TYPE_MP_UNBALANCE_MAX_VOLT_TIME			0x7754//��ѹ��ƽ�����ֵ����ʱ��
#define CON_DI_TYPE_MP_UNBALANCE_MAX_CURR_TIME			0x7755//������ƽ�����ֵ����ʱ��

#define CON_DI_TYPE_MP_ERRUP_TIME_SPOWER				0x7756//���ڹ���Խ������ʱ��
#define CON_DI_TYPE_MP_NORUP_TIME_SPOWER				0x7757//���ڹ���Խ����ʱ��

#define CON_DI_TYPE_MP_POWRATESECT1_TIME				0x7758//���������ֲ�����1�ۼ�ʱ�䣨�������� < ��ֵ1��
#define CON_DI_TYPE_MP_POWRATESECT2_TIME				0x7759//���������ֲ�����2�ۼ�ʱ�䣨��ֵ1�ܹ�������<��ֵ2��
#define CON_DI_TYPE_MP_POWRATESECT3_TIME				0x775A//���������ֲ�����3�ۼ�ʱ�䣨���������ݶ�ֵ2��

#define CON_DI_TYPE_MP_TERPOWERON_TIME					0x7760//�ն˹���ʱ��
#define CON_DI_TYPE_MP_TERRESET_NUM						0x7761//�ն˸�λ�ۼƴ���
#define CON_DI_TYPE_MP_MONTHENERGYCTRL_TRIPNUM			0x7762//�µ����բ����
#define CON_DI_TYPE_MP_BUYENERGYCTRL_TRIPNUM			0x7763//�������բ����
#define CON_DI_TYPE_MP_POWERCTRL_TRIPNUM				0x7764//������բ����
#define CON_DI_TYPE_MP_REMOTECTRL_TRIPNUM				0x7765//ң����բ����
#define CON_DI_TYPE_MP_FLUXBYTES						0x7766//�����ֽ���
#define CON_DI_TYPE_MP_FLUX_OVER_FLAG				0x7767//����Խ�ޱ�־
#define CON_DI_TYPE_MP_FLUX_OVER_COUNT				0x7768//����Խ�޼�����
#define CON_DI_TYPE_MP_DISCONNECT_FLAG				0x7769//����ͨ�����ӿ���

#define CON_DI_TYPE_MP_SIG_0							0x7770//�ź�״̬��0
#define CON_DI_TYPE_MP_SIG_1							0x7771//�ź�״̬��1
#define CON_DI_TYPE_MP_SIG_2							0x7772//�ź�״̬��2
#define CON_DI_TYPE_MP_SIG_3							0x7773//�ź�״̬��3
#define CON_DI_TYPE_MP_SIG_4							0x7774//�ź�״̬��4
#define CON_DI_TYPE_MP_SIG_5							0x7775//�ź�״̬��5
#define CON_DI_TYPE_MP_SIG_6							0x7776//�ź�״̬��6
#define CON_DI_TYPE_MP_SIG_7							0x7777//�ź�״̬��7

#define CON_DI_TYPE_MP_ANALOG_DC_1						0x7781//ֱ��ģ����1
#define CON_DI_TYPE_MP_ANALOG_DC_2						0x7782//ֱ��ģ����2

#define CON_DI_TYPE_MP_SUMG_INST_POW					0x7791//�ܼ�˲ʱ�й�����
#define CON_DI_TYPE_MP_SUMG_INST_VAR					0x7792//�ܼ�˲ʱ�޹�����
#define CON_DI_TYPE_MP_SUMG_LEFT_POW					0x7793//�ն��ܼӵ�ǰʣ�����
#define CON_DI_TYPE_MP_SUMG_POW_FIX_VALUE					0x7794//�ն��ܼӵ�ǰ���ض�ֵ

#define CON_DI_TYPE_MP_SUMG_POW_TOTAL					0x7800//�ܼ��й�����ʾֵ��
#define CON_DI_TYPE_MP_SUMG_POW_FEE1					0x7801//�ܼ��й�����ʾֵ1
#define CON_DI_TYPE_MP_SUMG_POW_FEE2					0x7802//�ܼ��й�����ʾֵ2
#define CON_DI_TYPE_MP_SUMG_POW_FEE3					0x7803//�ܼ��й�����ʾֵ3
#define CON_DI_TYPE_MP_SUMG_POW_FEE4					0x7804//�ܼ��й�����ʾֵ4

#define CON_DI_TYPE_MP_SUMG_VAR_TOTAL					0x7810//�ܼ��޹�����ʾֵ��
#define CON_DI_TYPE_MP_SUMG_VAR_FEE1					0x7811//�ܼ��޹�����ʾֵ1
#define CON_DI_TYPE_MP_SUMG_VAR_FEE2					0x7812//�ܼ��޹�����ʾֵ2
#define CON_DI_TYPE_MP_SUMG_VAR_FEE3					0x7813//�ܼ��޹�����ʾֵ3
#define CON_DI_TYPE_MP_SUMG_VAR_FEE4					0x7814//�ܼ��޹�����ʾֵ4

#define CON_DI_TYPE_MP_SUMG_LAST_POW_TOTAL				0x7820//�ܼ���һ�й�����ʾֵ��
#define CON_DI_TYPE_MP_SUMG_LAST_POW_FEE1				0x7821//�ܼ���һ�й�����ʾֵ1
#define CON_DI_TYPE_MP_SUMG_LAST_POW_FEE2				0x7822//�ܼ���һ�й�����ʾֵ2
#define CON_DI_TYPE_MP_SUMG_LAST_POW_FEE3				0x7823//�ܼ���һ�й�����ʾֵ3
#define CON_DI_TYPE_MP_SUMG_LAST_POW_FEE4				0x7824//�ܼ���һ�й�����ʾֵ4

#define CON_DI_TYPE_MP_SUMG_LAST_VAR_TOTAL				0x7830//�ܼ���һ�޹�����ʾֵ��
#define CON_DI_TYPE_MP_SUMG_LAST_VAR_FEE1				0x7831//�ܼ���һ�޹�����ʾֵ1
#define CON_DI_TYPE_MP_SUMG_LAST_VAR_FEE2				0x7832//�ܼ���һ�޹�����ʾֵ2
#define CON_DI_TYPE_MP_SUMG_LAST_VAR_FEE3				0x7833//�ܼ���һ�޹�����ʾֵ3
#define CON_DI_TYPE_MP_SUMG_LAST_VAR_FEE4				0x7834//�ܼ���һ�޹�����ʾֵ4

#define CON_DI_TYPE_MP_SUMG_MAX_INSTANT_POW				0x7840//����ܼ��й�ͳ��
#define CON_DI_TYPE_MP_SUMG_MAX_INSTANT_POW_TIME		0x7841//����ܼ��й�ͳ�Ʒ���ʱ��
#define CON_DI_TYPE_MP_SUMG_MIN_INSTANT_POW				0x7842//��С�ܼ��й�ͳ��
#define CON_DI_TYPE_MP_SUMG_MIN_INSTANT_POW_TIME		0x7843//��С�ܼ��й�ͳ�Ʒ���ʱ��
#define CON_DI_TYPE_MP_SUMG_ZEROTIME_INSTANT_POW		0x7844//�ܼ��й�Ϊ0����ʱ��

#define CON_DI_TYPE_MP_SUMG_OVERTIME_POWER				0x7845//�ܼӹ��ʳ���ֵʱ��
#define CON_DI_TYPE_MP_SUMG_OVERTIME_ENERGY				0x7846//�ܼ��µ�������ֵʱ��

#define CON_DI_TYPE_MP_SUMG_POWEROVERACCVALTOTAL		0x7847//���ʳ���ֵ�µ����ۼ�
#define CON_DI_TYPE_MP_SUMG_ENERGYOVERACCVALTOTAL		0x7848//�µ�������ֵ�µ����ۼ�
#define CON_DI_TYPE_MP_SUMG_POWEROVERSTARTVAL			0x7849//���ʳ���ֵ��ʼʾֵ
#define CON_DI_TYPE_MP_SUMG_ENERGYOVERSTARTVAL			0x784A//�µ�������ֵ��ʼʾֵ	//����Խ���򱣳ָ�ֵ��Խ�޻ָ����޸ĸ�ֵ�޸ĵ����ۼƣ��ɻָ���Խ�����޸ĸ�ֵ

#define CON_DI_TYPE_MP_LAST_DIRPOWTOTAL					0x7A10//��һ�������й��ܵ���
#define CON_DI_TYPE_MP_LAST_DIRPOWPLUS					0x7A11//��һ�������й������
#define CON_DI_TYPE_MP_LAST_DIRPOWAPEX					0x7A12//��һ�������й������
#define CON_DI_TYPE_MP_LAST_DIRPOWFLAT					0x7A13//��һ�������й�ƽ����
#define CON_DI_TYPE_MP_LAST_DIRPOWVALE					0x7A14//��һ�������й��ȵ���

#define CON_DI_TYPE_MP_LAST_UNDIRPOWTOTAL				0x7A20//��һ�������й��ܵ���
#define CON_DI_TYPE_MP_LAST_UNDIRPOWPLUS				0x7A21//��һ�������й������
#define CON_DI_TYPE_MP_LAST_UNDIRPOWAPEX				0x7A22//��һ�������й������
#define CON_DI_TYPE_MP_LAST_UNDIRPOWFLAT				0x7A23//��һ�������й�ƽ����
#define CON_DI_TYPE_MP_LAST_UNDIRPOWVALE				0x7A24//��һ�������й��ȵ���

#define CON_DI_TYPE_MP_LAST_DIRVARTOTAL					0x7B10//��һ�������޹��ܵ���
#define CON_DI_TYPE_MP_LAST_DIRVARPLUS					0x7B11//��һ�������޹������
#define CON_DI_TYPE_MP_LAST_DIRVARAPEX					0x7B12//��һ�������޹������
#define CON_DI_TYPE_MP_LAST_DIRVARFLAT					0x7B13//��һ�������޹�ƽ����
#define CON_DI_TYPE_MP_LAST_DIRVARVALE					0x7B14//��һ�������޹��ȵ���

#define CON_DI_TYPE_MP_LAST_UNDIRVARTOTAL				0x7B20//��һ�������޹��ܵ���
#define CON_DI_TYPE_MP_LAST_UNDIRVARPLUS				0x7B21//��һ�������޹������
#define CON_DI_TYPE_MP_LAST_UNDIRVARAPEX				0x7B22//��һ�������޹������
#define CON_DI_TYPE_MP_LAST_UNDIRVARFLAT				0x7B23//��һ�������޹�ƽ����
#define CON_DI_TYPE_MP_LAST_UNDIRVARVALE				0x7B24//��һ�������޹��ȵ���

#define CON_DI_TYPE_IMP_EVENT_POINTER					0x7D01//��Ҫ�¼�ָ��
#define CON_DI_TYPE_NOR_EVENT_POINTER					0x7D02//һ���¼�ָ��
#define CON_DI_TYPE_EVENT_STATUS_L						0x7D03//�¼�״̬��4�ֽ�
#define CON_DI_TYPE_EVENT_STATUS_H						0x7D04//�¼�״̬��4�ֽ�
#define CON_DI_TYPE_MP_TER_LAST_TIME					0x7D05//�ն��������ʱ��
#define CON_DI_TYPE_MP_TER_LAST_UP_COMM_TIME			0x7D06 //�ն��������ͨѶʱ��

#define CON_DI_TYPE_WIRELESS_GSM_CSQ_MIN_VAL			0x7D0C //�ź�ǿ����Сֵ
#define CON_DI_TYPE_WIRELESS_GSM_CSQ_MIN_TIME			0x7D0D //�ź�ǿ����Сֵ����ʱ��
#define CON_DI_TYPE_WIRELESS_GSM_CSQ_MAX_VAL			0x7D0E //�ź�ǿ�����ֵ
#define CON_DI_TYPE_WIRELESS_GSM_CSQ_MAX_TIME			0x7D0F //�ź�ǿ�����ֵ����ʱ�� 
#define CON_DI_TYPE_WIRELESS_GSM_CSQ					0x7D10 //�ź�ǿ��0-31
#define CON_DI_TYPE_WIRELESS_LOGIN_TYPE					0x7D11 //��¼״̬0:δ��¼��1:�ѵ�¼
#define CON_DI_TYPE_MODULE_TYPE					        0x7D12 //GPRSģ�����ͣ�0:GPRS_MODULE_Q2686 1:GPRS_MODULE_MC52I 15:GPRS_MODULE_NULL

#define CON_DI_TYPE_WIRELESS_COMM_STATE					0x7D13 //��վͨ��״̬��1:ͨѶ  2:����  ����:����
#define CON_DI_TYPE_TASK_RUN_STATE 						0x7D14 //����ִ��״̬��1:����  2:�ѱ�  ����:���

#define CON_DI_TYPE_TER_PASSWORD_STORE					0x7D15 //��������
#define CON_DI_TYPE_WIRELESS_STAT                                   		0x7D16 //����ģ��״̬:1:ע�����磬2:���ڵ�¼3:GPRS�Ѿ�����4:GPRS�Ѿ�����
#define CON_DI_TYPE_PLC_STAT								0x7D17 //plcģ��״̬:1����2:�ѱ�3:����

#define CON_DI_TYPE_TER_POWEROFF_LAST_TIME				0x7D20 //���ͣ��ʱ��
#define CON_DI_TYPE_TER_POWERON_LAST_TIME				0x7D21 //����ϵ�ʱ��
#define CON_DI_TYPE_TER_IP_WIRELESS						0x7D22 //�����ֻ�ģ����ն�ip
#define CON_DI_TYPE_TER_POWEROFF_FLAG					0x7D23 //�ն�ͣ���־
#define CON_DI_TYPE_TER_PROGRAMKEY_FLAG					0x7D24 //��̰�����Ч��1��Ч��0����������Ч

#define CON_DI_TYPE_ALARM_ACD_STATUS					0x7D30 //�¼�������ʶ


#define CON_DI_TYPE_ZERO_METER_EXEC_STATUS_LINELOST		0x7E01	//��㶳�᳭��״̬�������������
#define CON_DI_TYPE_ZERO_METER_EXEC_STATUS_METER_FAIL	0x7E02	//��㶳�᳭��״̬�����ڳ���ʧ�ܸ澯
#define CON_DI_TYPE_ZERO_METER_FAIL_COUNT				0x7E03	//��㶳�᳭��ʧ�ܴ���

#define CON_DI_TYPE_LINE_LOST_FINISHED					0x7E04	//����������

#define CON_DI_TYPE_MPDIRPOWTOTAL_ZERO					0x7E10	//������������й�������CT����

#define CON_DI_TYPE_CURR_SOFTWARE_EDITION				0x7E20	//��ǰ����汾��4λASCII	����V1.0����Ϊ100,V1.1����Ϊ101
#define CON_DI_TYPE_LAST_SOFTWARE_EDITION				0x7E21	//��һ����汾��4λASCII	����V1.0����Ϊ100,V1.1����Ϊ101

#define CON_DI_TYPE_TER_PHASE_ORDER_NORM				0x7E22	//��������������Ϊ0�����쳣������������

#define CON_DI_TYPE_TER_PHASE_UA                        0x7E23  //��λ�ǣ�Ua->Ua
#define CON_DI_TYPE_TER_PHASE_UB						0x7E24	//��λ�ǣ�Ub->Ua
#define CON_DI_TYPE_TER_PHASE_UC						0x7E25	//��λ�ǣ�Uc->Ua
#define CON_DI_TYPE_TER_PHASE_IA                        0x7E26  //��λ�ǣ�Ia->Ua
#define CON_DI_TYPE_TER_PHASE_IB						0x7E27	//��λ�ǣ�Ib->Ua
#define CON_DI_TYPE_TER_PHASE_IC						0x7E28	//��λ�ǣ�Ic->Ua

#define CON_DI_TYPE_APP_START_TIME						0x7E29	//Ӧ�ó���ʼʱ��
#define CON_DI_TYPE_METER_STOP_TIME						0x7E30	//���ܱ�ͣ��ʱ�䱣��
#define CON_DI_TYPE_METER_TIME_ERR_TIME					0x7E31	//���ܱ�ʱ�䳬���ʱ�䱣��

//����������Զ���
#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_BIG_BLOCK         0x7E32
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_BIG_BLOCK       0x7E33
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_BIG_BLOCK         0x7E34
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_BIG_BLOCK       0x7E35

#define CON_DI_TYPE_MPDIRPOWMAXDEMAND_LM_BIG_BLOCK      0x7E36
#define CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_LM_BIG_BLOCK    0x7E37
#define CON_DI_TYPE_MPDIRVARMAXDEMAND_LM_BIG_BLOCK      0x7E38
#define CON_DI_TYPE_MPUNDIRVARMAXDEMAND_LM_BIG_BLOCK    0x7E39

//��ѹ�������������ݸ�ʽ��һ������Ҫר�Ŷ���
#define CON_DI_TYPE_MPVOL_BLOCK_07                      0x7E40
#define CON_DI_TYPE_MPCUR_BLOCK_07                      0x7E41
#define CON_DI_TYPE_MPINSTANTPOW_BLOCK_07				0x7E42//
#define CON_DI_TYPE_MPINSTANTVAR_BLOCK_07				0x7E43//
#define CON_DI_TYPE_TER_ZERO_LINE_I00					0x7E44// ��ʱ����Ҫ�ŵ�����

//�м̼����Ӧ��ĸ���
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

//����ͳ��
#define CON_DI_TYPE_TOTAL_METER_NUM						0x7F0A//	��������
#define CON_DI_TYPE_VIP_METER_NUM						0x7F0B//	�ص㻧��
#define CON_DI_TYPE_SUCC_METER_NUM						0x7F0C//	�ɹ�����
#define CON_DI_TYPE_FAIL_METER_NUM						0x7F0D//	ʧ������

#define CON_DI_TYPE_FAIL_MP_FLAG1                       0x7F0E//   ʧ�ܱ�Ĳ����ŵ�1-��4��	��ΪҪ����ʷ����ʷһ�����ݱ�ʾ��4��������
#define CON_DI_TYPE_FAIL_MP_FLAG2                       0x7F0F//   ʧ�ܱ�Ĳ����ŵ�5-��8��
#define CON_DI_TYPE_FAIL_MP_FLAG3                       0x7F10//   ʧ�ܱ�Ĳ����ŵ�9-��12��
#define CON_DI_TYPE_FAIL_MP_FLAG4                       0x7F11//   ʧ�ܱ�Ĳ����ŵ�13-��16��
#define CON_DI_TYPE_FAIL_MP_FLAG5                       0x7F12//   ʧ�ܱ�Ĳ����ŵ�17-��20��
#define CON_DI_TYPE_FAIL_MP_FLAG6                       0x7F13//   ʧ�ܱ�Ĳ����ŵ�21-��24��
#define CON_DI_TYPE_FAIL_MP_FLAG7                       0x7F14//   ʧ�ܱ�Ĳ����ŵ�25-��28��
#define CON_DI_TYPE_FAIL_MP_FLAG8                       0x7F15//   ʧ�ܱ�Ĳ����ŵ�29-��32��
//...
#define CON_DI_TYPE_FAIL_MP_FLAG_LAST					0x7F8E//   
//0x7F0E - 7F8E   128����֧��512��������

#define CON_DI_TYPE_NODE_COLL_START_TIME				0x7F96	//�ն���������ѱ�ʼʱ��
#define CON_DI_TYPE_NODE_COLL_END_TIME					0x7F97	//�ն���������ѱ����ʱ��

#define CON_DI_TYPE_PLC_METER_START_TIME				0x7F98	//�ն������������ʼʱ��
#define CON_DI_TYPE_PLC_METER_END_TIME					0x7F99	//�ն���������������ʱ��

#define CON_DI_TYPE_NEXT_HW_REBOOT_TIME					0x7F9A	//�ն��Զ���������һ��ʱ��

#define CON_DI_TYPE_METER_485_1_RUN_NUM					0x7F9B	//485һ���������ͳɹ���
#define CON_DI_TYPE_METER_485_2_RUN_NUM					0x7F9C	//485�����������ͳɹ���
//--------------------------����ģ�����---------------------------------------------
#define CON_DI_TYPE_POWCTRL_SUMGNO                      		0x2010			//�����ܼ����			
#define CON_DI_TYPE_ENERGYCTRL_SUMGNO                    	0x2011			//����ܼ����
#define CON_DI_TYPE_MONTH_CHANGE_FLAG                    	0x2012			//�·ݱ仯��־


#define CON_DI_TYPE_MULTI_HRT_INT					0x2014			//�����ݽ�������ʱ�䱶��
#define CON_DI_TYPE_MODULE_RESET_COUNT			0x2015			

//---------- �Զ��� 0x7600 0x7FFF ֧��2560�� -----------------------



#define CON_DI_TYPE_MPDIRPOWTOTAL_LST2M			0x9810	//�����������й�����
#define CON_DI_TYPE_MPDIRPOWPLUS_LST2M			0x9811	//�����������й�����
#define CON_DI_TYPE_MPDIRPOWAPEX_LST2M			0x9812	//�����������й�����
#define CON_DI_TYPE_MPDIRPOWFLAT_LST2M			0x9813	//�����������й�����
#define CON_DI_TYPE_MPDIRPOWVALE_LST2M			0x9814	//�����������й�����
#define CON_DI_TYPE_MPDIRPOW_LST2M_BLOCK		0x981F

#define CON_DI_TYPE_MPDIRPOWTOTAL_LST3M			0x9A10	//�������������й�����
#define CON_DI_TYPE_MPDIRPOWPLUS_LST3M			0x9A11	//�������������й�����
#define CON_DI_TYPE_MPDIRPOWAPEX_LST3M			0x9A12	//�������������й�����
#define CON_DI_TYPE_MPDIRPOWFLAT_LST3M			0x9A13	//�������������й�����
#define CON_DI_TYPE_MPDIRPOWVALE_LST3M			0x9A14	//�������������й�����
#define CON_DI_TYPE_MPDIRPOW_LST3M_BLOCK		0x9A1F

#define CON_DI_TYPE_MPDIRPOWTOTAL_LST0DAY			0x9090//��ǰ�����ڵ���
#define CON_DI_TYPE_MPDIRPOWTOTAL_LST1DAY			0x9091//��1�մ����ڵ���
#define CON_DI_TYPE_MPDIRPOWTOTAL_LST2DAY			0x9092//��2�մ����ڵ���
#define CON_DI_TYPE_MPDIRPOWTOTAL_LST3DAY			0x9093//��3�մ����ڵ���
#define CON_DI_TYPE_MPDIRPOWTOTAL_LST4DAY			0x9094//��4�մ����ڵ���
#define CON_DI_TYPE_MPDIRPOWTOTAL_LST5DAY			0x9095//��5�մ����ڵ���
#define CON_DI_TYPE_MPDIRPOWTOTAL_LST6DAY			0x9096//��6�մ����ڵ���
#define CON_DI_TYPE_MPDIRPOWTOTAL_LST7DAY			0x9097//��7�մ����ڵ���

#define CON_DI_TYPE_MPLOSTVOL_NUM						0xE130//ʧѹ����
#define CON_DI_TYPE_MPLOSTVOLA_NUM						0xE133//ʧѹ����
#define CON_DI_TYPE_MPLOSTVOLB_NUM						0xE136
#define CON_DI_TYPE_MPLOSTVOLC_NUM						0xE139
#define CON_DI_TYPE_MPLOSTVOL_BLOCK					0xE13F

#define CON_DI_TYPE_MPLOSTCURA_NUM						0xE122//ʧ������
#define CON_DI_TYPE_MPLOSTCURB_NUM						0xE124
#define CON_DI_TYPE_MPLOSTCURC_NUM						0xE126

#define CON_DI_TYPE_MPINDIR_CURA_NUM						0xE142
#define CON_DI_TYPE_MPINDIR_CURB_NUM						0xE146
#define CON_DI_TYPE_MPINDIR_CURC_NUM						0xE14A

#define CON_DI_TYPE_MPPROG_DATEANDNUM					0xE211
#define CON_DI_TYPE_MPMETERSTAT_GD2_FLAG				0xC029	//�㶫�������״̬��2
//---------- �������ݱ�ʶ -------------------------------------------
#define CON_DI_TYPE_STATIONADDR0				0x8010//��վͨ�ŵ�ַ0	����д���߼�Ȩ�ޣ�
#define CON_DI_TYPE_STATIONADDR1				0x8011//��վͨ�ŵ�ַ1	����д���߼�Ȩ�ޣ�
#define CON_DI_TYPE_STATIONADDR2				0x8012//��վͨ�ŵ�ַ2	����д���߼�Ȩ�ޣ�
#define	CON_DI_TYPE_SMSCENTERNUM				0x8013//�������ĺ���	����д���߼�Ȩ�ޣ�
#define CON_DI_TYPE_NETGATEADDR					0x8014//���ص�ַ		����д���߼�Ȩ�ޣ�
#define CON_DI_TYPE_NETAPN						0x8015//APN����			����д���߼�Ȩ�ޣ�
#define	CON_DI_TYPE_TERAERA						0x8016//�ն˵�����		����д���߼�Ȩ�ޣ�
#define CON_DI_TYPE_TERADDR						0x8017//�ն˵�ַ		����д���߼�Ȩ�ޣ�
#define CON_DI_TYPE_NETUSERNAME					0x8019//GPRS(CDMA)��¼�û�������д���߼�Ȩ�ޣ�
#define CON_DI_TYPE_NETPASSWORD					0x801A//GPRS(CDMA)��¼����	����д���߼�Ȩ�ޣ�
#define CON_DI_TYPE_801F_BLOCK					0x801F//				����д���߼�Ȩ�ޣ�

#define CON_DI_TYPE_READPASSWORD				0x8020//��ͨ����		��д���ͼ�&�߼�Ȩ�ޣ�
#define CON_DI_TYPE_SETPASSWORD					0x8021//��������		��д���ͼ�&�߼�Ȩ�ޣ�
#define	CON_DI_TYPE_ADMINPASSWORD				0x8022//����Ա����		��д���߼�Ȩ�ޣ�
#define CON_DI_TYPE_802F_BLOCK					0x802F//				��д���߼�Ȩ�ޣ�	

#define CON_DI_TYPE_TERTIME						0x8030//�ն�ʱ��		����д���ͼ�&�߼�Ȩ�ޣ�
#define CON_DI_TYPE_CHECKTIME						0x803E//��ʱ
#define CON_DI_TYPE_TERSOFTWAREINFO				0x8809//���ֽ��ն˳��̴��룻���Ϊ�ն�����汾�ţ�����
#define CON_DI_TYPE_TARHARDWAREVERNO			0x880A//�ն�Ӳ���汾�ţ�����

#define CON_DI_TYPE_RINGNUM						0x8810//�������
#define CON_DI_TYPE_METERNUM						0x8811//���ܱ�����
#define CON_DI_TYPE_COMMETER						0x8812//��ͨ���
#define CON_DI_TYPE_MULFUNMETER					0x8813//�๦�ܵ���� 
#define CON_DI_TYPE_IMUSRMETER					0x8814//�ص��û�
#define CON_DI_TYPE_TASKSTART						0x8815//������ʼʱ��
#define CON_DI_TYPE_TASKINTER						0x8816//����ִ�м�� 
#define CON_DI_TYPE_RELAYMODE						0x8817//�м̷�ʽ
#define CON_DI_TYPE_LOSTLIMIT						0x8818//������ֵ
#define CON_DI_TYPE_IMUPTIME						0x8819//�ص��û��ϴ�ʱ��
#define CON_DI_TYPE_DAYUPTIME						0x881A//�ն��������ϴ�ʱ��
#define CON_DI_TYPE_ALARMEABLE					0x881B//�澯ʹ�ܿ�����
#define CON_DI_TYPE_LOSTTODAY						0x881C//����������
#define CON_DI_TYPE_SLAVEADD						0x881D//�������ն˵�ַ
#define CON_DI_TYPE_LINKED_PROPERTY				0x881E//��������

#define CON_DI_TYPE_MONCOPYTIME					0x8820//��ĩ���ݳ��տ�ʼʱ��
#define CON_DI_TYPE_MONUPTIME						0x8821//��ĩ�����ϴ�ʱ��
#define CON_DI_TYPE_DISTERADD						0x8822//̨����Ӧ����ն˵�ַ

#define CON_DI_TYPE_TERMMAG						0x8830//̨����Ӧ����ն˱���
#define CON_DI_TYPE_HEARTINTER					0x8831//��������

#define CON_DI_TYPE_MPPROP						0x8901//����������		����д���ͼ�&�߼�Ȩ�ޣ�
#define CON_DI_TYPE_MPADDR						0x8902//�������ַ		����д���ͼ�&�߼�Ȩ�ޣ�

#define CON_DI_TYPE_MP_TERADDR					0x8939//�������Ӧ���ն˵�ַ
#define CON_DI_TYPE_METERTYPE						0x8940//������

#define CON_DI_TYPE_AUTORELAY						0x8943//�Զ��м�Լ������

#define CON_DI_TYPE_MODYMETER_BATCH				0x894D//�����޸�
#define CON_DI_TYPE_MODYMETER						0x894E//�޸ı��

#define CON_DI_TYPE_MPMETERSTAT_GD_FLAG					0x8EA0	//�㶫�������״̬��

#define CON_STATUS_YES				0x55	//�ֽڱ�ǣ���
#define CON_STATUS_NO				0xAA	//�ֽڱ�ǣ���
#define	CON_INVALID_VAL				0xFF
#define	CON_INVALID_LONG_VAL		0x7FFFFFFF

#define CON_READ_METER_OK			0x55	//����ɹ�
#define CON_READ_METER_ERR			0xAA	//����ʧ��
#define	CON_READ_METER_INVALID		0xFF	//��Ч״̬

#define CON_STATUS_NONE				0x00	//��ǣ���
#define CON_STATUS_START			0x33	//��ǣ�������
#define CON_STATUS_FINISHED			0xCC	//��ǣ����

#define CON_MAIN_DEV				0	//���ն�
#define CON_SLAVE_DEV				1	//���ն�

#define CON_PRI_UP_ACTIVE			0	//��������
#define CON_PRI_UP_NORMAL			1	//��ͨ

#define	CON_METERTYPE_3P3L		0x01
#define	CON_METERTYPE_3P4L		0x02
#define	CON_METERTYPE_1P		0x03

#define CON_SMS_LIST_NUM		7	//���ű���֡��������Ŀ
#define CON_MAX_CURVE_DATA_NUM	96	//��վ����������������������

#define		CON_SUMGFLAG_ENERGYCTRL	0x55	//��������
#define		CON_SUMGFLAG_POWERCTRL	0xAA	//���ʿ���
#define		CON_SUMGFLAG_CTRL_COMB	0xFF	//�������ƺ͹��ʿ���

//-------------------------- ���Ϲ�Լ���� -----------------------------------
#define MAIN_CHAN_ID 1			//��ͨ�����
#define BACK_CHAN_ID 2			//��ͨ�����
#define BACK_CHAN_ID1 3			//��ͨ��2���
#define WLS_CHAN_ID     MAIN_CHAN_ID//����ģ��ͨ��
#define CON_698_MAX_MP_NUM				2040		//��������
#define CON_698_MAX_METER_NUM			2040		//�����ܱ���߽���װ����
#define CON_698_MAX_CALC_NUM			8			//����ܼ�����
#define CON_698_MAX_CALC_MP_NUM			64			//����ܼ����������

#define CON_698_ERR_MPNO				2019		//�쳣������
#define CON_698_TER_SAMPLE_DEFAULT_MPNO	2010		//Ĭ�Ͻ����ɼ������� DA0 DA1 = 02 FB
#define CON_698_ERR_DSOBJNO				1019		//�쳣�����

#define	CON_698_EXT_PROTOCOL_INVALID	0		//��Ч
#define	CON_698_EXT_PROTOCOL_DL645_1997	1		//645 1997��Լ
#define	CON_698_EXT_PROTOCOL_SAMPLE		2		//�����ɼ�

#define	CON_698_EXT_PROTOCOL_WS			3		//��ʤv4.x
#define	CON_698_EXT_PROTOCOL_LANDD		4		//������D��
#define	CON_698_EXT_PROTOCOL_ABB_R		5		//ABB����
#define	CON_698_EXT_PROTOCOL_GENIUS		6		//����
#define	CON_698_EXT_PROTOCOL_HND		7		//������
#define	CON_698_EXT_PROTOCOL_LANDB		8		//������B��
#define	CON_698_EXT_PROTOCOL_DL645_2007	30		//645 2007��Լ

#define	CON_698_METERTYPE_3P3L		0x01		//��������
#define	CON_698_METERTYPE_3P4L		0x02		//��������
#define	CON_698_METERTYPE_1P		0x03		//�����

#define	CON_698_METERTYPE_1P_NOT_CFM	0x00	//���������಻ȷ��
#define	CON_698_METERTYPE_1P_PA			0x04	//����������A��
#define	CON_698_METERTYPE_1P_PB			0x08	//����������B��
#define	CON_698_METERTYPE_1P_PC			0x0C	//����������C��


//�㶫������
#define CON_MAX_MP_NUM				1280	//1024+254+1+1	/0102���࣬03���׶๦��08�ܱ�
			//������� 0 Ϊ�������������豸������Ŵ� 1 ��ʼ
#define CON_MAX_VIP_MP_NUM			6		//�ص��û�
#define CON_MAX_SMETER_MP_NUM		1024	//������߻�е
#define CON_MAX_MMETER_MP_NUM		254		//���׶๦��
#define CON_MAX_NEED_FROZ_MP_NUM	1024	//��Ҫ����������������

#define CON_TER_MPNO				0		//�ն����������

#define CON_HIS_DATA_DAY_NUM		63		//�ն�������
#define CON_HIS_DATA_MON_NUM		25		//�¶�������
//#define CON_CURVE_DATA_DAY_NUM		32		//��������
#define CON_CURVE_DATA_DAY_NUM		63		//��������  ��Ҫд�����ݿ���������ã�ĿǰĬ��63��
#define CON_CURVE_DATA_POINT_NUM	(CON_CURVE_DATA_DAY_NUM  * 96)		//���ߵ���������15�����ܶ�
#define CON_CURVE_DATA_INTER_SEC	900		//����15�����ܶȣ�900��

#define CON_INDEX_RESET				0xFFEE	//�ϵ������
#define CON_INDEX_INVALID			0xFFFF	//��Ч����

#define CON_METER_PROP1_485			0x01	//485
#define CON_METER_PROP1_PLC			0x02	//�ز�
#define CON_METER_PROP1_OTHER		0x03	//����
#define CON_METER_PROP1_MASK		0x07

#define CON_METER_PROP2_SMETER		0x08	//����
#define CON_METER_PROP2_JMETER		0x10	//��е
#define CON_METER_PROP2_MMETER		0x18	//���׶๦��
#define CON_METER_PROP2_ZMETER		0x40	//��
#define CON_METER_PROP2_MASK		0x78

#define CON_METER_PROP3_GATE_1		0x80	//��
#define CON_METER_PROP3_GATE_0		0x00	//��
#define CON_METER_PROP3_MASK		0x80

#define CON_METER_DATATYPE_MONTH	0x80		//��ĩ����
#define CON_METER_DATATYPE_DAY		0x40		//��ĩ����
#define CON_METER_DATATYPE_MASK		0xC0
//-------------------------- �豸���� -----------------------------------
#define	CON_UP_BOARD_PORT		1
#define	CON_DOWN_BOARD_PORT		2
#define	CON_SPEC_BOARD_PORT		3

#define	CON_BOARD_PORT_DINPUT	CON_DOWN_BOARD_PORT
#define	CON_BOARD_PORT_SPEC		CON_SPEC_BOARD_PORT

#define CON_BOARD_ID			0xFF00		//�����������ȡ�ð���ID
#define CON_PORT_ID				0x00FF		//�����������ȡ��ʵ�ʵĶ˿�ID
//�˿�ID�ĸ���λΪ���ӵ�ID������λ����ʵ�ʵĶ˿�ID��ʹ��ʱ����0x00FF(CON_PORT_ID)������õ�ʵ�ʵĶ˿�ID
#define CON_DOWN_BOARD_X	0xFFFF		//��Ч
//---------------���¶˿ڶ�����\etc\port.cfg�ļ��У�ר��ͼ������в��---------------
#ifdef CON_TER_TYPE_FK_ALL		//ר��
#define CON_UP_BOARD_3			0x0103		//up_board_3 = "pb6"  #������5
#define CON_UP_BOARD_4			0x0104		//up_board_4 = "pb7"  #������6
#define CON_DOWN_BOARD_4		0x0204		//down_board_4 = "pa9"  #������1 (21,22)
#define CON_DOWN_BOARD_5		0x0205		//down_board_5 = "pa8"  #������2 (23,24)
#define CON_DOWN_BOARD_6		0x0206		//down_board_6 = "pa7"  #������3 (25,26)
#define CON_DOWN_BOARD_7		0x0207		//down_board_7 = "pa6"  #������4 (27,28)
#define CON_DOWN_BOARD_12		0x020C		//down_board_12 = "pb20" #�Ž��
#define CON_COVER_MONITOR_1 	0x0301		//cover_monitor_1 = "pc28" #������8(0,0)���Ǽ��

#define CON_SIG_COLL_ID1		CON_DOWN_BOARD_4
#define CON_SIG_COLL_ID2		CON_DOWN_BOARD_5
#define CON_SIG_COLL_ID3		CON_UP_BOARD_3
#define CON_SIG_COLL_ID4		CON_UP_BOARD_4
#define CON_SIG_COLL_ID5		CON_DOWN_BOARD_X
#define CON_SIG_COLL_ID6		CON_DOWN_BOARD_X
#define CON_SIG_COLL_ID7		CON_DOWN_BOARD_X
#define CON_SIG_COLL_ID8		CON_DOWN_BOARD_12
#else							//������
#define CON_DOWN_BOARD_1	0x0201			//down_board_1  = "pa9"  #������1(13,14)
#define CON_DOWN_BOARD_2	0x0202			//down_board_2  = "pa8"  #������2(15,16)
#define CON_COVER_MONITOR_1 	0x0301			//cover_monitor_1 = "pc28" #������8(0,0)���Ǽ��

#define CON_SIG_COLL_ID1		CON_DOWN_BOARD_1
#define CON_SIG_COLL_ID2		CON_DOWN_BOARD_2
#define CON_SIG_COLL_ID3		CON_DOWN_BOARD_X
#define CON_SIG_COLL_ID4		CON_DOWN_BOARD_X
#define CON_SIG_COLL_ID5		CON_DOWN_BOARD_X
#define CON_SIG_COLL_ID6		CON_DOWN_BOARD_X
#define CON_SIG_COLL_ID7		CON_DOWN_BOARD_X
#define CON_SIG_COLL_ID8		CON_COVER_MONITOR_1
#endif
//---------------���϶˿ڶ�����\etc\port.cfg�ļ��У�ר��ͼ������в��---------------

#define	CON_SIG_COLL_NUM		8			//�źŲɼ�·��

#define CON_SIG_TYPEA			1	//��A�ഥ�� һ��
#define CON_SIG_TYPEB			0	//��B�ഥ�� �෴

/*����״̬����*/
#define CON_SIG_STAT_CLOSE		1	//���غ�
#define CON_SIG_STAT_OPEN		0	//���ط�

#define CON_SIG_DOOR1		8	//�������Žڵ�
#define CON_SIG_DOOR2		7	//�ն˸�
#define CON_SIG_DOOR3		6	//���ܱ��

#define CON_SIG_SWITCH1		1	//ң��1
#define CON_SIG_SWITCH2		2	//ң��2
#define CON_SIG_SWITCH3		3	//ң��3
#define CON_SIG_SWITCH4		4	//ң��4

#define CON_SIG_COVER_TAIL	1	//���1��β��
#define CON_SIG_COVER_SMALL	2	//���2��С��
#define CON_SIG_COVER_BIG	3	//���3�����

//#define CON_LED_RUN			5	//DA2	D5			//�㶫������
//#define CON_LED_ALARM		6	//DA3	D6				//�㶫������
#define CON_LED_RUN			12
#define CON_LED_ALARM		13

#define CON_LED_GPRS_NET	8	//gprs ����
#define CON_LED_GPRS_TXD	9	//gprs ���緢��
#define CON_LED_GPRS_RXD	10	//gprs �������

#define CON_POWER_LOW_INPUT_VOLT	5500	//3000mv

#ifdef CON_TER_TYPE_JC_CQ

//�˿ڱ�ţ����������Լ��								//���ݿ⣬ͨ��������Ҫ��Ӧ�޸�
#define CON_PORT_SAMPLE		26	//�ն˽��������ӿ�ͨ��
#define CON_PORT_485_1		1	//RS485 1 �ӿ�ͨ��
#define CON_PORT_485_2		2	//RS485 2 �ӿ�ͨ��
#define CON_PORT_LINK		30	//�ն˼���ͨ��
#define CON_PORT_PLC		31	//����ͨ��ģ��ӿ�ͨ��
#define CON_PORT_BEEN_COLL	CON_PORT_LINK	//�ն˽�����

#else

//�˿ڱ�ţ����������Լ��
#define CON_PORT_SAMPLE		1	//�ն˽��������ӿ�ͨ��
#define CON_PORT_485_1		2	//RS485 1 �ӿ�ͨ��
#define CON_PORT_485_2		3	//RS485 2 �ӿ�ͨ��
#define CON_PORT_LINK		30	//�ն˼���ͨ��
#define CON_PORT_PLC		31	//����ͨ��ģ��ӿ�ͨ��
#define CON_PORT_BEEN_COLL	CON_PORT_LINK	//�ն˽�����

#endif

#define CON_485_PORT_AREA   CON_PORT_485_1,CON_PORT_485_2,CON_PORT_LINK

//plc������
#define CON_PLC_MNG_METER_NOT_ACK	0			//����״̬δ֪��δ����
#define CON_PLC_MNG_METER_SUCCESS	1			//����ɹ�
#define CON_PLC_MNG_METER_FAIL		2			//����ʧ��
#define CON_PLC_MNG_METER_NEW_ADD	3			//��������

#define CON_PLC_MNG_METER_NOT_FIND	4			//·��δ�ѵ���

#define CON_PLC_CTRL_NONE			0			// �ز�������ƣ��޲���
#define CON_PLC_CTRL_PAUSE			1			// F49������ָ��ͨ�Ŷ˿���ͣ����
#define CON_PLC_CTRL_RESUME			2			// F50������ָ��ͨ�Ŷ˿ڻָ�����
#define CON_PLC_CTRL_RESET			3			// F51������ָ��ͨ�Ŷ˿����³���
#define CON_PLC_CTRL_INIT_ROUTE		4			// F52����ʼ��ָ��ͨ�Ŷ˿��µ�ȫ���м�·����Ϣ
#define CON_PLC_CTRL_START_WITH_RET	5			// ���³��������֪ͨ

#define CON_UP_CHAN_NUM				3			//�ڶ�������GPRSͨ����������������̫��ͨ������һ������

//��������
#define CON_MODULE_TYPE_GPRS		0			//ģ�����ͣ�GPRS
#define CON_MODULE_TYPE_CDMA		1			//ģ�����ͣ�CDMA
#define CON_MODULE_TYPE_NONE		15			//ģ�����ͣ�û�в�ģ��
#define CON_MODULE_TYPE_ERR			-1			//ģ�����ͣ�δ֪


#endif
