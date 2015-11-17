/*******************************************************************************
模块名       : 通信API
文件名       : 
相关文件     : 
文件实现功能 : 负责从底层取数据,并进行超时判断,当接收到一串数据并延时大于30ms时,调用协议解析函数,进行协议解析
作者         : 
版本         : Ver 1.0。
-------------------------------------------------------------------------------
备注         : 
-------------------------------------------------------------------------------
修改记录 : 
日 期        版本     修改人              修改内容
YYYY/MM/DD   X.Y      <作者或修改者名>    <修改内容>
===============================================================================
其他说明:   无。
*******************************************************************************/
#define COMMUNICATEAPI_GLOBALS

#include "string.h"
#include "math.h"
#include "common.h"

uchar guc_comuartstt;
int gi_485fp;//开启485端口返回的文件描述符,在调用函数rs485_open时返回值
//
//=====================================
//针对天津硬件
//5   /dev/ttyS2          485端口1
//6   /dev/ttyS4          485端口2
//其他则默认为 /dev/ttyS2  485端口1
//=================================
void InitCommunicate(uchar port_no)
{
	memset(&CommExpReceiveDataBuffer,0,sizeof(CommExpReceiveDataBuffer));
	if(port_no ==2)
		gi_485fp = rs485_open("/dev/ttyS2", 9600, 8,1, PARITY_EVEN);//开启485通讯
	else if(port_no == 4)	
		gi_485fp = rs485_open("/dev/ttyS4", 9600, 8,1, PARITY_EVEN);//开启485通讯
	else	
		gi_485fp = rs485_open("/dev/ttyS2", 9600, 8,1, PARITY_EVEN);//开启485通讯
    CommExpDataBuff = (STR_RETURN_EXPLAINBUFFER*)&(CommExpReceiveDataBuffer.buff[0]);
}

void IdleCommunicate(void)
{
	 rs485_close (gi_485fp);//关闭485通讯
}

//======================================================
//功能：向缓冲区写入数据
//输入：
//输出：
//使用说明：
//======================================================
void ComWrBuff(uchar Chunnel,uchar data)
{
	if(CommExpReceiveDataBuffer.lens < UART_REC_FRAME_LEN_MAX)
	{
		CommExpReceiveDataBuffer.communicateFlag.source = Chunnel;//设置通讯缓冲区的通道号
		CommExpReceiveDataBuffer.communicateFlag.sendDelay = 0;//设置通讯缓冲区的延时
		CommExpReceiveDataBuffer.buff[CommExpReceiveDataBuffer.lens] = data;//保存数据
	//	fprintf(stderr,"%02x  ", CommExpReceiveDataBuffer.buff[CommExpReceiveDataBuffer.lens]);  
		CommExpReceiveDataBuffer.lens ++;	//接收长度累加
	}else
	{
		CommExpReceiveDataBuffer.lens = 0;
	}
}

/*************************************************************
Function: 发送数据
Input: 
Output: 是否成功
Application area: 
Explain: 
Modification register:
**************************************************************/
uchar SendCommunicateData(uchar* src,u16 lens,STR_COMMUNICATA_FLAG* sendFlag,STR_UART_PARA_CHANGE_CONTROL* data)
{
    rs485_write(gi_485fp,src,lens,0);//发送数据
    return(0);
}


void PrtclParse(void)
{
	uchar ucpdata,*pdata8,templen ,tempchk;
	uchar flag = 0;
	
    
	for(ucpdata = 0;CommExpReceiveDataBuffer.lens >= 12;ucpdata ++,CommExpReceiveDataBuffer.lens--)
																//扫描数据长度小于规约最小长度则退出循环
	{
		pdata8 = CommExpReceiveDataBuffer.buff + ucpdata;
		if(*pdata8 != 0x68)										//判断第一个68；
			continue;
		if((*(pdata8 + 7)) != 0x68)								//判断第二个68；
			continue;
		templen = *(pdata8 + 9);								//取数据区域长度
		if((*(pdata8 + 11+templen)) != 0x16)
			continue;
		tempchk = CheckSun(pdata8,templen + 10);
		if((*(pdata8 + 10+templen)) == tempchk)
		{														//为645规约
			flag = 1;
			break;
		}
	}
	if(flag == 0)
	{
		if(CommExpReceiveDataBuffer.lens > (UART_REC_FRAME_LEN_MAX - 20))
		{
			memset(&CommExpReceiveDataBuffer,0,sizeof(CommExpReceiveDataBuffer));
		}
		return ;
	}
	memcpy(CommExpReceiveDataBuffer.buff,CommExpReceiveDataBuffer.buff + ucpdata,CommExpReceiveDataBuffer.lens);	//去掉前导符,数据搬移到缓冲区的首地址起始
	pdata8 = CommExpReceiveDataBuffer.buff + 10;				//指针指向数据区域
	for( ;templen > 0;templen --)//数据域减33
	{
		*pdata8 -= 0x33;
		pdata8 ++;
	}
	Rcomm645Control();
	memset(&CommExpReceiveDataBuffer,0,sizeof(CommExpReceiveDataBuffer));
}
//*************************************************************
//Function: 判断接收数据的帧结构,是表计进程中,10ms的线程,大约10ms进入一次
//Input: 
//Output: 
//Application area: 
//Explain: 
//Modification register:
//**************************************************************/
void judgeFrameStructure(uchar chunnel) 
{						//是表计进程中,100ms的线程uchar i,data;
	uchar i,data;
	
	i = 0;
	while(rs485_read(gi_485fp, &data, 1, 0) != 0)
	{
		ComWrBuff(chunnel,data);//把数据写入通讯缓冲区
		i = 1;
	}
	if(i != 0)
	{										//上100ms内接收到数据
		// MTRACE("\n%s-%d\n", __FUNCTION__, __LINE__); 
		i = rs485_read(gi_485fp, &data, 1, 30);//30ms内等待接收,如果没接受到数据,认为数据帧接收完成
		if(i == 0)
		{ 
			//MTRACE("\n%s-%d\n", __FUNCTION__, __LINE__); 
			if(rs485_read(gi_485fp, &data, 1, 1) == 0)
			{  
				/*MTRACE("\n%s-%d\n", __FUNCTION__, __LINE__);    i = CommExpReceiveDataBuffer.lens;
		           for(i = 0 ;i < CommExpReceiveDataBuffer.lens;i ++)
		           {
		           	
		          	 fprintf(stderr,"%02x  ", CommExpReceiveDataBuffer.buff[i]);  
		        	}
		           fprintf(stderr,"\n");*/
				PrtclParse();
				return;
			}
		}
		ComWrBuff(chunnel,data);//把数据写入通讯缓冲区
	}else if(CommExpReceiveDataBuffer.lens >= 12)
	{												//上100ms没接受到数据,进行数据解析
		  /*MTRACE("\n%s-%d\n", __FUNCTION__, __LINE__);    i = CommExpReceiveDataBuffer.lens;
		           for(i = 0 ;i < CommExpReceiveDataBuffer.lens;i ++)
		           {
		           	
		          	 fprintf(stderr,"%02x  ", CommExpReceiveDataBuffer.buff[i]);  
		        	}
		           fprintf(stderr,"\n");*/
		PrtclParse();
	}else
	{ //MTRACE("\n%s-%d\n", __FUNCTION__, __LINE__); 
		CommExpReceiveDataBuffer.lens = 0;
	}
}



