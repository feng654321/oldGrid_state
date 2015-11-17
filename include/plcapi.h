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


// 错误字定义
#define ERR_LEN					0x01		// 长度错误
#define ERR_INS_NOTEXIST		0x02		// 指令不存在
#define ERR_INS_FORMAT			0x03		// 指令内容格式错误
#define ERR_PLC_NO_RESPONSE		0x04		// PLC设备没有响应
#define ERR_COPYING				0x05		// 正在抄表不能执行此指令
#define ERR_NODE_EXIST			0x06		// 此节点已存在
#define ERR_NODE_NOTEXIST		0x07		// 此节点不存在
#define ERR_NODE_OVERFLOW		0x08		// 节点数量溢出
#define ERR_OUT_NODE_MEM		0x09		// 存放节点ID存储区溢出
#define ERR_ZERO_NODE			0x0a		// 节点ID数量 为0
#define ERR_ACCESS_NODE_FAIL	0x0b		// 访问指定节点ID失败
#define ERR_NO_DIRECT_NODE		0x0c		// 没有找到合法的直抄节点
#define ERR_NO_SUCH_NODE		0x0d		// 没用指定选抄节点
#define ERR_NO_COPIED_DATA		0x0e		// 没有已抄读数据
#define ERR_NO_BC_DATA			0x0f		// 没有设置广播内容
#define ERR_NO_BC_PHASE_DATA	0x10		// 没有设置相位识别广播内容
#define ERR_NO_COPY_DATA		0x11		// 没有设置抄读内容
#define ERR_OUT_OF_MEMORY		0x12		// 子系统分配内存出错		
#define	ERR_SYSTEM_ERR			0x13		// 系统内容错误
#define ERR_TERMINAL_TIMEOUT	0x14		// 用户终端超时
	

struct  cmd_req_struct {
	unsigned char cmd;				// 指令见表3.1b
	unsigned char cmd_len;			// 指令数据域长度
	unsigned char cmd_data[256];	// 指令数据域
};

struct cmd_rsp_struct {
	unsigned char  rerr;		// 命令执行结果，0x00代表成功， 否则见错误字定义表
	int  rlen;					// 响应数据长度
	unsigned char  *rdata;		// 响应数据
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
