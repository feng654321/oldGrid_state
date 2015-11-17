/*******************************************************************************
ģ����       : ͨ��API
�ļ���       : 
����ļ�     : 
�ļ�ʵ�ֹ��� : ����ӵײ�ȡ����,�����г�ʱ�ж�,�����յ�һ�����ݲ���ʱ����30msʱ,����Э���������,����Э�����
����         : 
�汾         : Ver 1.0��
-------------------------------------------------------------------------------
��ע         : 
-------------------------------------------------------------------------------
�޸ļ�¼ : 
�� ��        �汾     �޸���              �޸�����
YYYY/MM/DD   X.Y      <���߻��޸�����>    <�޸�����>
===============================================================================
����˵��:   �ޡ�
*******************************************************************************/
#define COMMUNICATEAPI_GLOBALS

#include "string.h"
#include "math.h"
#include "common.h"

uchar guc_comuartstt;
int gi_485fp;//����485�˿ڷ��ص��ļ�������,�ڵ��ú���rs485_openʱ����ֵ
//
//=====================================
//������Ӳ��
//5   /dev/ttyS2          485�˿�1
//6   /dev/ttyS4          485�˿�2
//������Ĭ��Ϊ /dev/ttyS2  485�˿�1
//=================================
void InitCommunicate(uchar port_no)
{
	memset(&CommExpReceiveDataBuffer,0,sizeof(CommExpReceiveDataBuffer));
	if(port_no ==2)
		gi_485fp = rs485_open("/dev/ttyS2", 9600, 8,1, PARITY_EVEN);//����485ͨѶ
	else if(port_no == 4)	
		gi_485fp = rs485_open("/dev/ttyS4", 9600, 8,1, PARITY_EVEN);//����485ͨѶ
	else	
		gi_485fp = rs485_open("/dev/ttyS2", 9600, 8,1, PARITY_EVEN);//����485ͨѶ
    CommExpDataBuff = (STR_RETURN_EXPLAINBUFFER*)&(CommExpReceiveDataBuffer.buff[0]);
}

void IdleCommunicate(void)
{
	 rs485_close (gi_485fp);//�ر�485ͨѶ
}

//======================================================
//���ܣ��򻺳���д������
//���룺
//�����
//ʹ��˵����
//======================================================
void ComWrBuff(uchar Chunnel,uchar data)
{
	if(CommExpReceiveDataBuffer.lens < UART_REC_FRAME_LEN_MAX)
	{
		CommExpReceiveDataBuffer.communicateFlag.source = Chunnel;//����ͨѶ��������ͨ����
		CommExpReceiveDataBuffer.communicateFlag.sendDelay = 0;//����ͨѶ����������ʱ
		CommExpReceiveDataBuffer.buff[CommExpReceiveDataBuffer.lens] = data;//��������
	//	fprintf(stderr,"%02x  ", CommExpReceiveDataBuffer.buff[CommExpReceiveDataBuffer.lens]);  
		CommExpReceiveDataBuffer.lens ++;	//���ճ����ۼ�
	}else
	{
		CommExpReceiveDataBuffer.lens = 0;
	}
}

/*************************************************************
Function: ��������
Input: 
Output: �Ƿ�ɹ�
Application area: 
Explain: 
Modification register:
**************************************************************/
uchar SendCommunicateData(uchar* src,u16 lens,STR_COMMUNICATA_FLAG* sendFlag,STR_UART_PARA_CHANGE_CONTROL* data)
{
    rs485_write(gi_485fp,src,lens,0);//��������
    return(0);
}


void PrtclParse(void)
{
	uchar ucpdata,*pdata8,templen ,tempchk;
	uchar flag = 0;
	
    
	for(ucpdata = 0;CommExpReceiveDataBuffer.lens >= 12;ucpdata ++,CommExpReceiveDataBuffer.lens--)
																//ɨ�����ݳ���С�ڹ�Լ��С�������˳�ѭ��
	{
		pdata8 = CommExpReceiveDataBuffer.buff + ucpdata;
		if(*pdata8 != 0x68)										//�жϵ�һ��68��
			continue;
		if((*(pdata8 + 7)) != 0x68)								//�жϵڶ���68��
			continue;
		templen = *(pdata8 + 9);								//ȡ�������򳤶�
		if((*(pdata8 + 11+templen)) != 0x16)
			continue;
		tempchk = CheckSun(pdata8,templen + 10);
		if((*(pdata8 + 10+templen)) == tempchk)
		{														//Ϊ645��Լ
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
	memcpy(CommExpReceiveDataBuffer.buff,CommExpReceiveDataBuffer.buff + ucpdata,CommExpReceiveDataBuffer.lens);	//ȥ��ǰ����,���ݰ��Ƶ����������׵�ַ��ʼ
	pdata8 = CommExpReceiveDataBuffer.buff + 10;				//ָ��ָ����������
	for( ;templen > 0;templen --)//�������33
	{
		*pdata8 -= 0x33;
		pdata8 ++;
	}
	Rcomm645Control();
	memset(&CommExpReceiveDataBuffer,0,sizeof(CommExpReceiveDataBuffer));
}
//*************************************************************
//Function: �жϽ������ݵ�֡�ṹ,�Ǳ�ƽ�����,10ms���߳�,��Լ10ms����һ��
//Input: 
//Output: 
//Application area: 
//Explain: 
//Modification register:
//**************************************************************/
void judgeFrameStructure(uchar chunnel) 
{						//�Ǳ�ƽ�����,100ms���߳�uchar i,data;
	uchar i,data;
	
	i = 0;
	while(rs485_read(gi_485fp, &data, 1, 0) != 0)
	{
		ComWrBuff(chunnel,data);//������д��ͨѶ������
		i = 1;
	}
	if(i != 0)
	{										//��100ms�ڽ��յ�����
		// MTRACE("\n%s-%d\n", __FUNCTION__, __LINE__); 
		i = rs485_read(gi_485fp, &data, 1, 30);//30ms�ڵȴ�����,���û���ܵ�����,��Ϊ����֡�������
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
		ComWrBuff(chunnel,data);//������д��ͨѶ������
	}else if(CommExpReceiveDataBuffer.lens >= 12)
	{												//��100msû���ܵ�����,�������ݽ���
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



