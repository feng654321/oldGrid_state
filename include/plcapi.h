#ifndef __PLC_H
#define __PLC_H


#define CMD_QUERY_NODE_NUM		0x01
#define CMD_DOWNLOAD_NODE_INFO		0x02
#define CMD_DOWNLOAD_ROUTE_INFO		0x03
#define CMD_QUERY_STUDY_LEVEL		0x04
#define CMD_QUERY_WORK_BREAK		0x05
#define CMD_QUERY_PROBE_WORD		0x06
#define CMD_QUERY_UNREACH_NODE_NUM	0x07
#define CMD_DOWNLOAD_UNREACH_NODE_INFO	0x08
#define CMD_QUERY_ROUTE_ID		0x09
#define CMD_QUERY_ROUTE_RUN_WAY		0x0a

#define CMD_CLEAR_ALL_NODE		0x10
#define CMD_ADD_NODE			0x11
#define CMD_DEL_NODE			0x12
#define CMD_MODIFY_NODE			0x13
#define CMD_ADD_ROUTE			0x14
#define CMD_SET_STUDY_LEVEL		0x15
#define CMD_RESET_WORK_BREAK		0x16
#define CMD_SET_WORK_MODE		0x17
#define CMD_SET_PROBE_WORD		0x18
#define CMD_SET_ROUTE_ID		0x19
#define CMD_SET_ROUTE_RUN_WAY		0x1a

#define CMD_DATA_COMM			0x20

#define CMD_CHANGE_PHASE		0x30
#define CMD_START_COPY_METER		0x31
#define CMD_STOP_COPY_METER		0x32
#define CMD_RESTART_SYS			0x33
#define CMD_START_BROADCAST		0x34
#define CMD_START_PHASE_INDENTIFY	0x35

#define CMD_QUERY_ROUTE_STAT		0x40
#define CMD_SET_DEFAULT_COPY_DATA	0x41
#define CMD_SET_NODE_COPY_DATA		0x42
#define CMD_READ_NODE_COPY_DATA		0x43
#define CMD_READ_ALL_COPY_DATA		0x44
#define CMD_SET_BROADCAST_DATA		0x45
#define CMD_SET_PHASE_INDENTIFY_DATA	0x46
#define CMD_SET_COPY_CIRCLE		0x47


// �����ֶ���
#define ERR_LEN					0x01		// ���ȴ���
#define ERR_INS_NOTEXIST		0x02		// ָ�����
#define ERR_INS_FORMAT			0x03		// ָ�����ݸ�ʽ����
#define ERR_PLC_NO_RESPONSE		0x04		// PLC�豸û����Ӧ
#define ERR_COPYING				0x05		// ���ڳ�����ִ�д�ָ��
#define ERR_NODE_EXIST			0x06		// �˽ڵ��Ѵ���
#define ERR_NODE_NOTEXIST		0x07		// �˽ڵ㲻����
#define ERR_NODE_OVERFLOW		0x08		// �ڵ��������
#define ERR_OUT_NODE_MEM		0x09		// ��Žڵ�ID�洢�����
#define ERR_ZERO_NODE			0x0a		// �ڵ�ID���� Ϊ0
#define ERR_ACCESS_NODE_FAIL	0x0b		// ����ָ���ڵ�IDʧ��
#define ERR_NO_DIRECT_NODE		0x0c		// û���ҵ��Ϸ���ֱ���ڵ�
#define ERR_NO_SUCH_NODE		0x0d		// û��ָ��ѡ���ڵ�
#define ERR_NO_COPIED_DATA		0x0e		// û���ѳ�������
#define ERR_NO_BC_DATA			0x0f		// û�����ù㲥����
#define ERR_NO_BC_PHASE_DATA	0x10		// û��������λʶ��㲥����
#define ERR_NO_COPY_DATA		0x11		// û�����ó�������
#define ERR_OUT_OF_MEMORY		0x12		// ��ϵͳ�����ڴ����		
#define	ERR_SYSTEM_ERR			0x13		// ϵͳ���ݴ���
#define ERR_TERMINAL_TIMEOUT	0x14		// �û��ն˳�ʱ
	

struct  cmd_req_struct {
	unsigned char cmd;				// ָ�����3.1b
	unsigned char cmd_len;			// ָ�������򳤶�
	unsigned char cmd_data[256];	// ָ��������
};

struct cmd_rsp_struct {
	unsigned char  rerr;		// ����ִ�н����0x00����ɹ��� ����������ֶ����
	int  rlen;					// ��Ӧ���ݳ���
	unsigned char  *rdata;		// ��Ӧ����
};

extern int plc_start(void);
extern int plc_stop(void);
extern int plc_send_cmd(struct cmd_req_struct *p_cmd,  struct cmd_rsp_struct *p_rsp,  int  timeout);


#define		ERR_INIT_MSG		-100
#define		ERR_FORK			-101
#define		ERR_SYS				-102
#define		ERR_START_FAIL		-103
#define		ERR_STOP_FAIL		-104
#define		ERR_MSG_SND			-105
#define		ERR_TIMEOUT			-106
#define		ERR_NO_MEM			-107


#endif
