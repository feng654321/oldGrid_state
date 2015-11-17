/*******************************************************************************
ģ����       : г��harmonic
�ļ���       : harmonic.c
����ļ�     : 
�ļ�ʵ�ֹ��� : �Ը����Ĳ������ݽ���г������,�õ�31��г���ĺ���,�Լ����ߵ����Ĳ���.
����         : 
�汾         : Ver 1.0��
-------------------------------------------------------------------------------
��ע         : �ó���������Ҫ����Դ�϶�,����ֻ���ڼ����������ݲɼ�,
-------------------------------------------------------------------------------
�޸ļ�¼ : 
�� ��        �汾     �޸���              �޸�����
YYYY/MM/DD   X.Y      <���߻��޸�����>    <�޸�����>
===============================================================================
����˵��:   �ޡ�
*******************************************************************************/

#define AP_HARMONIC_GLOBALS

#include "common.h"
#include "ap_harmonic.h"


#if(CONFIG_METER_HARMONIC_ENABLE == GAL_YES)    

#define MAXHARMONICTIME 21


void harmonictest(void);

long gl_harmonic_datatemp[80*2];//г��������ʱ�洢����

ulong gl_harmonic_Nsum;

//����һ��ת��
void calc_harmonic_x1(void)
{
	long* pldata = gl_harmonic_datatemp;
	long ldata;
	uchar i;
	
	for(i = 0;i < 40;i ++)
	{
		ldata = *pldata;
		*pldata = *(pldata + 2) + ldata;
		pldata += 2;
		*pldata = ldata - *pldata;
		pldata += 2;
	}
}
//���ж���ת��
void calc_harmonic_x2(void)
{
	long* pldata = gl_harmonic_datatemp;
	long ldata,ldata1;
	uchar i;
	
	for(i = 0;i < 20;i ++)
	{
		ldata = *pldata;
		*pldata = *(pldata + 4) + ldata;	//��0������ʵ��
		pldata ++;
		*pldata = 0;						//��0�������貿
		pldata ++;
		ldata1 = *pldata;				//ȡ��1������ʵ��
		pldata ++;
		*pldata = *(pldata + 3);			//��1�������貿
		pldata ++;
		*pldata = ldata - *pldata;		//��2������ʵ��
		pldata ++;
		*pldata = 0;						//��2�������貿
		pldata ++;
		*pldata = ldata1;				//��3������ʵ��,���3������ʵ����ͬ
		pldata ++;
		*pldata = (long)0 - *(pldata - 4);//��3�������貿
		pldata ++;	
	}
}

//��������ת��
void calc_harmonic_x3(void)
{
	long* pldata = gl_harmonic_datatemp;
	long ldata1,ldata2,ldata3;
	uchar i;
	
	for(i = 0;i < 10;i ++)
	{
		ldata1 = *pldata;		//�����0������ʵ��
		ldata2 = *(pldata + 8);	//�����4������ʵ��
		*pldata = ldata2 + ldata1;			//��0������ʵ�����ڵ�0�����͵�4������ʵ����
		*(pldata + 8) = ldata1 - ldata2;	//��4������ʵ�����ڵ�0��������4������ʵ��
		
		pldata += 2;				//ָ���1������ʵ��,��1�������貿ά��ԭ����0����
		ldata3 = (*(pldata + 8) * 181) / 256;//��5������ʵ����������ֵ������ֵ
		ldata2 = (*(pldata + 9) * 181) / 256;//��5�������貿��������ֵ������ֵ
		ldata1 = ldata3 - ldata2;	//����������ֵ����ȵ�,���Կ��Ժϲ�����;
		ldata2 = ldata3 + ldata2;
		*pldata = *pldata + ldata1;//��1������ʵ��=��1������ʵ��+��5������ʵ����������ֵ-��5�������貿��������ֵ
		pldata ++;					//ָ���1�������貿
		*pldata = *pldata + ldata2;//��1�������貿=��1�������貿+��5������ʵ����������ֵ+��5�������貿��������ֵ
		
		pldata += 2;				//ָ���2�������貿,ʵ������
		*pldata = *(pldata + 7);	//��2�������貿���ڵ�6������ʵ��
		
		pldata ++;					//ָ���3������ʵ��
		*pldata = *pldata - ldata1;//��3������ʵ��=��3������ʵ��+��7������ʵ����������ֵ-��7�������貿��������ֵ,��7�������5�����պö�Ӧ
		pldata ++;					//ָ���3�������貿
		*pldata = ldata2 + *pldata;//��3�������貿=��3�������貿+��7������ʵ����������ֵ+��7�������貿��������ֵ,��7�������5�����պö�Ӧ
		
		pldata += 3;				//ָ���5������ʵ��,��4�������貿����Ϊ0,ʵ����ǰ���Ѿ�������;
		*pldata = *(pldata - 4);	//��5������ʵ�����ڵ�3������ʵ��
		pldata ++;					//ָ���5�������貿
		*pldata = (long)0 - *(pldata - 4);//��5�������貿����0 - ��3�����貿
		
		pldata ++;					//ָ���6������ʵ��
		ldata1 = *pldata;
		*pldata = *(pldata - 8);	//��6������ʵ�����ڵ�2������ʵ��
		pldata ++;					//ָ���6�������貿
		*pldata = (long)0 - ldata1;//��6�������貿����0 - ��6�����貿
		
		pldata ++;					//ָ���7������ʵ��
		*pldata = *(pldata - 12);	//��7������ʵ�����ڵ�1������ʵ��
		pldata ++;					//ָ���7�������貿
		*pldata = (long)0 - *(pldata - 12);//��7�������貿����0 - ��1�����貿
		pldata ++;					//ָ���8������ʵ��
	}
}
//����4��ת��
void calc_harmonic_x4(void)
{
	long* pldata = gl_harmonic_datatemp;
	long ldata1,ldata2,ldata3,ldata4,ldata5;
	uchar i;
	
	for(i = 0;i < 5;i ++)
	{
		ldata1 = *pldata;		//�����0������ʵ��
		ldata2 = *(pldata + 16);	//�����8������ʵ��
		*pldata = ldata2 + ldata1;			//��0������ʵ�����ڵ�0�����͵�8������ʵ����
		*(pldata + 16) = ldata1 - ldata2;	//��8������ʵ�����ڵ�0��������8������ʵ��
		
		pldata += 2;				//ָ���1������ʵ��,��0�������貿����ԭ�������ݲ���
		ldata5 = *(pldata + 16);		//�����9������ʵ��
		ldata2 = *(pldata + 17);		//�����9�������貿
		ldata1 = (ldata5 * 237) / 256;//��9������ʵ����������ֵ
		ldata4 = (ldata5 * 98) / 256;//��9������ʵ����������ֵ
		ldata3 = (ldata2 * 237) / 256;//��9�������貿��������ֵ
		ldata2 = (ldata2 * 98) / 256;//��9�������貿��������ֵ
		ldata1 = ldata1 - ldata2;	//ldata1 = ��9����ʵ��*����ֵ-��9�����貿*����ֵ,
		ldata2 = ldata3 + ldata4;	//ldata2 = ��9����ʵ��*����ֵ-��9�����貿*����ֵ,
		ldata3 = *pldata;			//�����1������ʵ��
		*pldata = ldata3 + ldata1;	//��1����ʵ��=��1����ʵ��+��9����ʵ��*����ֵ-��9�����貿*����ֵ
		*(pldata + 16) = ldata3 - ldata1;	//��9����ʵ��=��1����ʵ��-��9����ʵ��*����ֵ+��9�����貿*����ֵ
		pldata ++;					//ָ���1�������貿
		ldata3 = *pldata;			//�����1�������貿
		*pldata = ldata3 + ldata2;	//��1�����貿=��1�����貿+��9����ʵ��*����ֵ+��9�����貿*����ֵ
		*(pldata + 16) = ldata3 - ldata2;	//��9�����貿=��1�����貿-��9����ʵ��*����ֵ+��9�����貿*����ֵ
		
		pldata ++;				//ָ���2������ʵ��,��2�������貿ά��ԭ����0����
		ldata3 = (*(pldata + 16) * 181) / 256;//��10������ʵ����������ֵ������ֵ
		ldata2 = (*(pldata + 17) * 181) / 256;//��10�������貿��������ֵ������ֵ
		ldata1 = ldata3 - ldata2;	//����������ֵ����ȵ�,���Կ��Ժϲ�����;
		ldata2 = ldata3 + ldata2;
		ldata3 = *pldata;
		*pldata = ldata3 + ldata1;//��2������ʵ��=��2������ʵ��+��10������ʵ����������ֵ-��10�������貿��������ֵ
		*(pldata + 16) = ldata3 - ldata1;//��10������ʵ��=��2������ʵ��-��10������ʵ����������ֵ+��10�������貿��������ֵ
		pldata ++;					//ָ���1�������貿
		ldata3 = *pldata;
		*pldata = ldata3 + ldata2;//��2�������貿=��2�������貿+��10������ʵ����������ֵ+��10�������貿��������ֵ
		*(pldata + 16) = ldata3 - ldata2;//��10�������貿=��2�������貿-��10������ʵ����������ֵ-��10�������貿��������ֵ
		
		pldata ++;				//ָ���3������ʵ��
		ldata5 = *(pldata + 16);		//�����11������ʵ��
		ldata2 = *(pldata + 17);		//�����11�������貿
		ldata1 = (ldata5 * 98) / 256;//��11������ʵ����������ֵ
		ldata4 = (ldata5 * 237) / 256;//��11������ʵ����������ֵ
		ldata3 = (ldata2 * 98) / 256;//��11�������貿��������ֵ
		ldata2 = (ldata2 * 237) / 256;//��11�������貿��������ֵ
		ldata1 = ldata1 - ldata2;	//ldata1 = ��11����ʵ��*����ֵ-��11�����貿*����ֵ,
		ldata2 = ldata3 + ldata4;	//ldata2 = ��11����ʵ��*����ֵ-��11�����貿*����ֵ,
		ldata3 = *pldata;			//�����3������ʵ��
		*pldata = ldata3 + ldata1;	//��3����ʵ��=��3����ʵ��+��11����ʵ��*����ֵ-��11�����貿*����ֵ
		*(pldata + 16) = ldata3 - ldata1;	//��11����ʵ��=��3����ʵ��-��11����ʵ��*����ֵ+��11�����貿*����ֵ
		pldata ++;					//ָ���3�������貿
		ldata3 = *pldata;			//�����3�������貿
		*pldata = ldata3 + ldata2;	//��3�����貿=��3�����貿+��11����ʵ��*����ֵ+��11�����貿*����ֵ
		*(pldata + 16) = ldata3 - ldata2;	//��11�����貿=��3�����貿-��11����ʵ��*����ֵ+��11�����貿*����ֵ
		
		pldata += 2;				//ָ���4�������貿,ʵ������
		*pldata = *(pldata + 15);	//��4�������貿���ڵ�12������ʵ��
		
		pldata ++;					//ָ���5������ʵ��
		*pldata = *(pldata + 12);	//��5������ʵ��=�����ĵ�11������ʵ��
		pldata ++;					//ָ���5�������貿
		*pldata = (long)0 - *(pldata + 12);	//��5�������貿=0-�����ĵ�11�������貿
		
		pldata ++;					//ָ���6������ʵ��
		*pldata = *(pldata + 8);	//��6������ʵ��=�����ĵ�10������ʵ��
		pldata ++;					//ָ���6�������貿
		*pldata = (long)0 - *(pldata + 8);	//��6�������貿=0-�����ĵ�10�������貿
		
		pldata ++;					//ָ���7������ʵ��
		*pldata = *(pldata + 4);	//��7������ʵ��=�����ĵ�9������ʵ��
		pldata ++;					//ָ���7�������貿
		*pldata = (long)0 - *(pldata + 4);	//��7�������貿=0-�����ĵ�9�������貿
		
		pldata += 9;					//ָ���12������ʵ��
		*pldata = *(pldata - 16);	//��12������ʵ��=�����ĵ�4������ʵ��
		pldata ++;					//ָ���12�������貿
		*pldata = (long)0 - *(pldata - 16);	//��12�������貿=0-�����ĵ�4�������貿
		
		pldata ++;					//ָ���13������ʵ��
		*pldata = *(pldata - 20);	//��13������ʵ��=�����ĵ�3������ʵ��
		pldata ++;					//ָ���12�������貿
		*pldata = (long)0 - *(pldata - 20);	//��12�������貿=0-�����ĵ�4�������貿
		
		pldata ++;					//ָ���14������ʵ��
		*pldata = *(pldata - 24);	//��14������ʵ��=�����ĵ�2������ʵ��
		pldata ++;					//ָ���14�������貿
		*pldata = (long)0 - *(pldata - 24);	//��14�������貿=0-�����ĵ�2�������貿
		
		pldata ++;					//ָ���15������ʵ��
		*pldata = *(pldata - 28);	//��15������ʵ��=�����ĵ�1������ʵ��
		pldata ++;					//ָ���15�������貿
		*pldata = (long)0 - *(pldata - 28);	//��15�������貿=0-�����ĵ�1�������貿
		
		pldata ++;					//ָ���16������ʵ��
	}
}

						//  cos,sin,cos,sin,cos,sin,cos,sin
const uint8 con_CosSin[]={255,  0,255, 20,253, 40,249, 60,243, 79,237, 98,228,116,218,134,
						  207,150,195,166,181,181,166,195,150,207,134,218,116,228, 98,237,
						   79,243, 60,249, 40,253, 20,255,  0,255};
//����5��ת��
	long ltempdata[MAXHARMONICTIME*2];
void calc_harmonic_x5(void)
{
	long* pldata = gl_harmonic_datatemp + 4;//��0�β��ü���
	long ldatas,ldatax,ldata1;
	short icos,isin;
	uchar i,j,k,uccossin;
	for(k = 0;k < 5;k ++)
	{
		pldata = gl_harmonic_datatemp;//ָ���0����
		for(i = 0;i < 16;i ++)
		{								//����39��г������,���39��,���Ե���
			ldatas = *pldata;			//��ʱʵ����ֵ
			ldatax = *(pldata + 1);		//��ʱ�貿��ֵ
			for(j = 1;j < 5;j ++)
			{
				uccossin = (j * (k * 16 + i)) % 80;//������ֵת����360���ڶ�Ӧ��ֵ
				if(uccossin >= 60)
				{						//�Ƕȴ���270��
					uccossin = (80 - uccossin) * 2;
					icos = con_CosSin[uccossin];	//ȡ����ֵ
					isin = -con_CosSin[uccossin + 1];//ȡ����ֵ
				}else if(uccossin >= 40)
				{						//�Ƕ���180�ȵ�270��
					uccossin = (uccossin - 40) * 2;
					icos = -con_CosSin[uccossin];
					isin = -con_CosSin[uccossin + 1];//
				}else if(uccossin >= 20)
				{						//�Ƕ���90�ȵ�180��
					uccossin = (40 - uccossin) * 2;
					icos = -con_CosSin[uccossin];
					isin = con_CosSin[uccossin + 1];//
				}else
				{						//�Ƕ�С��90��
					uccossin = uccossin * 2;
					icos = con_CosSin[uccossin];
					isin = con_CosSin[uccossin + 1];//
				}
				ldata1 = *(pldata + 32 * j);//ȡʵ��
				ldatas += ldata1 * icos/256;		//ʵ��������ֵ + ��һ�ε�ʵ���õ��µ�ʵ��
				ldatax += ldata1 * isin/256;		//ʵ��������ֵ + ��һ�ε�ʵ���õ��µ��貿
				ldata1 = *(pldata + 32 * j + 1);//ȡ�貿
				ldatas -= ldata1 * isin/256;//�µ�ʵ�� - �貿������ֵ
				ldatax += ldata1 * icos/256;//ʵ��������ֵ + �貿������ֵ
			}
			ltempdata[(k * 16 + i) * 2] = ldatas;
			ltempdata[(k * 16 + i) * 2 + 1] = ldatax;
			if((k*16 + i) > (MAXHARMONICTIME - 1))
			{
				k = 100;
				i = 100;//�˳�ѭ��
			}
			pldata += 2;
		}
	}
}

//��Чֵ����
//=====================================================================================
//г��г���������㣺void XbContentClct(void)��
//���ܣ�����õ�2��31��г���ĺ���
//���������gs_XbData[]��
//���������gui_XbContent[30]
//�����Ĵ�����guc_XbTempData1,guc_XbTempData2,guc_XbTempData3,guc_XbTempData4
//ִ��ʱ�䣺��Լ??
//======================================================================================
const uint8 con_genhao[64]={105,102, 99, 96, 94 ,91, 88, 86, 83, 80, 78 ,75, 73, 70, 68, 65,
							 63, 61, 58, 56, 54, 51, 49, 47, 45, 43, 41, 39, 37, 35, 33, 31,
							 29, 28, 26, 24, 23, 21, 19, 18, 17, 15, 14, 13, 11, 10,  9,  8,
							  7,  6,  5,  5,  4,  3,  2,  2,  1,  1,  1,  0,  0,  0,  0,  0};
void calc_harmonic_rms(uchar ucmaxtime,struct harmonic_data_st *ps_data,uchar phase)
{
	uchar i,ucdata;
	long *pldata;
	ulong uldata1,uldata2,uldata3;
	ulong ulsum;
	
	if(ucmaxtime > MAXHARMONICTIME)
	{
		ucmaxtime = MAXHARMONICTIME;
	}
	
	pldata = ltempdata + 2;
	for(i = 1;i <= ucmaxtime;i ++)
	{
		if(*pldata < 0)
		{
			uldata1 = 0 - *pldata;
		}else
		{
			uldata1 = *pldata;
		}
		pldata ++;
		if(*pldata < 0)
		{
			uldata2 = 0 - *pldata;
		}else
		{
			uldata2 = *pldata;
		}
		pldata ++;
		if(uldata2 >= uldata1)
		{
			uldata3 = uldata2;
		}else
		{
			uldata3 = uldata1;
			uldata1 = uldata2;
		}
		if(uldata1 != 0)
		{
			ucdata = ((uldata3 - uldata1)*64)/uldata3;//ʵ�����貿�ľ���ֵ�ò�ֵ
			uldata3 = (uldata3 * (256 + con_genhao[ucdata]))/256;
		}
		*(((ulong*)(ps_data + i)) + phase) = uldata3;
	}
	uldata1 = *((ulong*)(ps_data + 1) + phase);				//ȡ��������
	ulsum = 0;
	if(uldata1 > 500000)
	{														//��������500000
		uldata1 /= 10000;
		for(i = 2;i <= ucmaxtime;i ++)
		{
			uldata2 = *((ulong*)(ps_data + i) + phase) / uldata1;//ȡг������Чֵ
			if(uldata2 < 70)
			{											//��г������С��0.3%ʱ,
				*((ulong*)(ps_data + i) + phase) = 0;	//��Ӧ��г����Чֵ�ͺ�����0
				*((ushort*)(ps_data + i) + 12 + phase) = 0;//г���ĺ�������0
			}else
			{
				*((ushort*)(ps_data + i) + 12 + phase) = uldata2;//��г���������浽�洢����
				if(uldata2 > ulsum)
				{
					uldata3 = uldata2;					//uldata3��Ŵ�ֵ
					uldata2 = ulsum;
				}else
				{
					uldata3 = ulsum;
				}
				if(uldata2 == 0)
				{
					ulsum = uldata3;
				}else
				{
					ucdata = ((uldata3 - uldata2)*256)/uldata3;//ʵ�����貿�ľ���ֵ�ò�ֵ
					ulsum = (uldata3 * (257 + con_genhao[ucdata/4] - (ucdata & 0x03)))/256;
				}
			}
		}
		*((ulong*)(ps_data) + phase) = uldata1 * ulsum;	//г������Чֵ
	}else if(uldata1 < 500)
	{												//����С��100
		for(i = 0;i <= ucmaxtime;i ++)
		{
			*((ulong*)(ps_data + i) + phase) = 0;	//��Ӧ��г����Чֵ��0
			*((ushort*)(ps_data + i) + 12 + phase) = 0;	//��Ӧ��г����������0
		}
		return ;
	}else
	{												//����С��500000�Ĵ���
		for(i = 2;i <= ucmaxtime;i ++)
		{
			uldata2 = (*((ulong*)(ps_data + i) + phase) * 10000) / uldata1;//ȡг������Чֵ
			if(uldata2 < 70)
			{											//��г������С��0.3%ʱ,
				*((ulong*)(ps_data + i) + phase) = 0;	//��Ӧ��г����Чֵ�ͺ�����0
				*((ushort*)(ps_data + i) + 12 + phase) = 0;//г���ĺ�������0
			}else
			{
				*((ushort*)(ps_data + i) + 12 + phase) = uldata2;//��г���������浽�洢����
				if(uldata2 > ulsum)
				{
					uldata3 = uldata2;					//uldata3��Ŵ�ֵ
					uldata2 = ulsum;
				}else
				{
					uldata3 = ulsum;
				}
				if(uldata2 == 0)
				{
					ulsum = uldata3;
				}else
				{
					ucdata = ((uldata3 - uldata2)*256)/uldata3;//ʵ�����貿�ľ���ֵ�ò�ֵ
					ulsum = (uldata3 * (257 + con_genhao[ucdata/4] - (ucdata & 0x03)))/256;
				}
			}
		}
		*((ulong*)(ps_data) + phase) = uldata1 * ulsum/1000;	//г������Чֵ
	}
	*((ushort*)(ps_data) + 12 + phase) = ulsum;//�����ʷ�ֵ
	*((ushort*)(ps_data + 1) + 12 + phase) = 9999;//�����ʷ�ֵ
}

const uchar con_HmncZhengxu[80]=
	{ 0,40,20,60,10,50,30,70, 5,45,25,65,15,55,35,75,
	  1,41,21,61,11,51,31,71, 6,46,26,66,16,56,36,76,
	  2,42,22,62,12,52,32,72, 7,47,27,67,17,57,37,77,
	  3,43,23,63,13,53,33,73, 8,48,28,68,18,58,38,78,
	  4,44,24,64,14,54,34,74, 9,49,29,69,19,59,39,79};

	
int calc_harmonic(struct acs_harmonic_waveform *p_waveform,struct harmonic_data_list_st *p_harmonic_data_list)
{
	uchar i,j;//ѭ������ʱ����
	long ldata;
	ulong ulsum;
	long lsum;
	
//fprintf(stderr, "%s-%d\n", __FUNCTION__, __LINE__);
	
	
	//�����������
	ulsum = 0;
	lsum= 0;
	for(i = 0;i < 40;i ++)
	{
		ldata = ((long)(p_waveform + i*4 )->iawv * 256) / uiCoefCurrentGAIN[0] + ((long)(p_waveform + i*4)->ibwv * 256) / uiCoefCurrentGAIN[1]
					 + ((long)(p_waveform + i*4)->icwv * 256) / uiCoefCurrentGAIN[2];//����ABC��˲ʱֵ�ۼ�
		lsum += ldata;
		ldata -= gl_harmonic_Nsum;
		if(ldata < 0)
		{
			ulsum -= ldata;
		}else
		{
			ulsum += ldata;
		}
	}
	gl_harmonic_Nsum = lsum/40;
	LongToData4BCD(ulsum/(186),&RAM[RAM_CURRENT_I_NULLSEQU]);
	//�����ã���ӡг����Чֵ
	//		memcpy(&ulsum,&RAM[RAM_CURRENT_I_NULLSEQU],4);
	//		fprintf(stderr, "lingxudianliu rms =  %08x    ", ulsum);
	//		fprintf(stderr, "lingxudianliu =  %08x   ", gl_harmonic_Nsum);
	//		fprintf(stderr, "jiaodu1 = %04x   ", *(ushort*)&RAM[RAM_CURRENT_ANGLE_AI_AV]);
	//		fprintf(stderr, "jiaodu1 = %04x  ", *(ushort*)&RAM[RAM_CURRENT_ANGLE_BI_AV]);
	//		fprintf(stderr, "jiaodu2 = %04x  ", *(ushort*)&RAM[RAM_CURRENT_ANGLE_CI_AV]);
			
	//	fprintf(stderr, " \n");
    
    //fprintf(stderr, "Address of RAM[0] = %x\n", &RAM[0]);
	
	//������������ȡ80��������ݲ�����ƫ��,ȫ��ת����������,��г�������Ĵ���洢���洢����
	for(i = 0;i < 7;i ++)
	{							//�����ĵ�ѹ������ѭ��
		if(i == 3)
			continue;				//���ߵ���������
		for(j = 0;j < 80;j ++)
		{
			//gl_harmonic_datatemp[k*2+j*32] = *((ulong *)p_waveform + 14 * (j*16+k) + i);
			gl_harmonic_datatemp[j*2] = (*((long *)p_waveform + i + 14 * con_HmncZhengxu[j]))/20;
			//gl_harmonic_datatemp[k*2+j*32+1] = 0;
		}
		calc_harmonic_x1();			//����1��ת��,2�ĵ���
		calc_harmonic_x2();			//����2��ת��,4�ĵ���
		calc_harmonic_x3();			//����3��ת��,8�ĵ���
		calc_harmonic_x4();			//����4��ת��,16�ĵ���
		calc_harmonic_x5();			//����5��ת��,5��ĵ���

//fprintf(stderr, "%s-%d,    addr = %08x\n", __FUNCTION__, __LINE__,p_harmonic_data_list);

		if(i < 3)
		{
			calc_harmonic_rms(sizeof(p_harmonic_data_list->harmonic_data_order)/sizeof(p_harmonic_data_list->harmonic_data_order[0]),
						&p_harmonic_data_list->harmonic_data_all,i);		//������Чֵ�������������ʵ�
		}else
		{
			calc_harmonic_rms(sizeof(p_harmonic_data_list->harmonic_data_order)/sizeof(p_harmonic_data_list->harmonic_data_order[0]),
						&p_harmonic_data_list->harmonic_data_all,i - 1);		//������Чֵ�������������ʵ�
		}
		//��ЧֵУ��
	}
	return 0;
}

struct harmonic_para_st gs_harmonic_para = 
{
	MAXHARMONICTIME,
	calc_harmonic,
};
void HarmonicInit(void)
{
	//acs_start_harmonic(&gs_harmonic_para);	//����г���ɼ�ģ��
	harmonic_module_run_flg = acs_start_harmonic(&gs_harmonic_para);
	gl_harmonic_Nsum = 0;
	if(0 != harmonic_module_run_flg)
		{
			acs_stop_harmonic();
			return;		
		}
}

void HarmonicIdle(void)
{
	//acs_stop_harmonic();					//�ر�г���ɼ�ģ��
	if(0 != harmonic_module_run_flg)
		return;
	acs_stop_harmonic();



}

void HarmonicMode(void)
{
	uchar i,j;
	ulong *pldata32;
	ushort *pldata16;
	ushort uiaddr1,uiaddr2;
	struct harmonic_data_list_st s_harmonic_data;

	if(0 != harmonic_module_run_flg)
		return;
	
    if(isSystemResetUnfinisded)
        return ;
    if((acs_get_harmonic_data(&s_harmonic_data,21)) != 0)
	{										//ȡ���ݲ��ɹ�
		acs_start_harmonic(&gs_harmonic_para);	//����г���ɼ�ģ��
    	return ;								//ֱ�ӷ���
    }
	    
	//г������ȡ�ɹ��������ݸ��ǵ�RAM��
	uiaddr1 = 0;
	uiaddr2 = 0;
	for(i = 0;i < 3;i ++)
	{										//��ѹת��
		pldata32 = &s_harmonic_data.harmonic_data_all.voltage_rms[i];
		pldata16 = &s_harmonic_data.harmonic_data_all.voltage_per[i];
		for(j = 0;j <= 21;j ++)
		{
			LongToData4BCD(*pldata32/360,&RAM[RAM_CURRENT_HARMONIC_V_A_ALL + uiaddr1] );//��ѹ��Чֵת����BCD�룬��������д�뵽RAM��
			uiaddr1 += 4;					//����ƶ�4���ֽ�
			pldata32 += sizeof(struct harmonic_data_st)/4;//ָ����һ��г���ĵ�ѹ��Чֵ
			if(j == 0)
			{								//��ʧ���
				IntToData2BCD(*pldata16,&RAM[RAM_CURRENT_HARMONIC_PER_V_A_ALL + i * 2] );//��ѹ����ת����BCD�룬��������д�뵽RAM��
				
			}else
			{
				IntToData2BCD(*pldata16,&RAM[RAM_CURRENT_HARMONIC_PER_V_A_01CI + uiaddr2] );//��ѹ����ת����BCD�룬��������д�뵽RAM��
				uiaddr2 += 2;					//����ƶ�2���ֽ�
			}
			pldata16 += sizeof(struct harmonic_data_st)/2;
		}
	}
	uiaddr1 = 0;
	uiaddr2 = 0;
	for(i = 0;i < 3;i ++)
	{										//����ת��
		pldata32 = &s_harmonic_data.harmonic_data_all.current_rms[i];
		pldata16 = &s_harmonic_data.harmonic_data_all.current_per[i];
		
		for(j = 0;j <= 21;j ++)
		{
			LongToData4BCD(*pldata32/101,&RAM[RAM_CURRENT_HARMONIC_I_A_ALL + uiaddr1] );//������Чֵת����BCD�룬��������д�뵽RAM��
			uiaddr1 += 4;					//����ƶ�4���ֽ�
			pldata32 += sizeof(struct harmonic_data_st)/4;//ָ����һ��г���ĵ�ѹ��Чֵ
			if(j == 0)
			{								//��ʧ���
				IntToData2BCD(*pldata16,&RAM[RAM_CURRENT_HARMONIC_PER_I_A_ALL + i * 2] );//��ѹ����ת����BCD�룬��������д�뵽RAM��
			}else
			{
				IntToData2BCD(*pldata16,&RAM[RAM_CURRENT_HARMONIC_PER_I_A_01CI + uiaddr2] );//��ѹ����ת����BCD�룬��������д�뵽RAM��
				uiaddr2 += 2;					//����ƶ�2���ֽ�
			}
			pldata16 += sizeof(struct harmonic_data_st)/2;
		}
	}
    
	return ;
}


//#define HARMONICTEST
#ifdef HARMONICTEST

struct acs_harmonic_waveform gs_harmonicpp[160];
struct harmonic_data_list_st gs_harmonictest;


const uint16 con_Sin1125[]={  0,  503, 1005, 1508, 2010, 2512, 3014, 3516, 4017, 4518, 
						   5018, 5518, 6018, 6517, 7015, 7513, 8009, 8506, 9001, 9495,
						   9989,10481,10973,11463,11952,12441,12928,13413,13898,14381,
						  14863,15343,15822,16299,16775,17249,17721,18192,18661,19128,
						  19593,20057,20518,20978,21435,21891,22344,22795,23244,23691,
						  24136,24578,25017,25455,25890,26322,26752,27179,27604,28026,
						  28445,28862,29276,29687,30095,30500,30902,31301,31698,32091,
						  32481,32868,33252,33632,34010,34384,34755,35122,35486,35847,
						  36204,36558,36908,37254,37597,37937,38272,38604,38933,39257,
						  39578,39895,40208,40517,40823,41124,41422,41715,42005,42290,
						  42571,42848,43122,43390,43655,43916,44172,44424,44672,44915,
						  45154,45389,45620,45846,46067,46284,46497,46705,46909,47108,
						  47303,47493,47678,47859,48035,48207,48374,48536,48694,48847,
						  48995,49139,49278,49412,49541,49666,49785,49900,50010,50116,
						  50216,50312,50403,50489,50570,50646,50717,50784,50845,50902,
						  50953,51000,51042,51079,51111,51138,51161,51178,51190,51198,
						  51200};
						  



int32 sinp(uint32 jiaodu)
{
	uint8 i;
	
	while(jiaodu >= 360000)
		jiaodu -= 360000;
	if(jiaodu >= 270000)
	{
		jiaodu = 360000 - jiaodu;
		i = (jiaodu*2) / 1125;
		return (int32)0 - con_Sin1125[i];
	}else if(jiaodu >= 180000)
	{
		jiaodu = jiaodu - 180000;
		i = (jiaodu*2) / 1125;
		return (int32)0 - con_Sin1125[i];
	}else if(jiaodu >= 90000)
	{
		jiaodu = 180000 - jiaodu;
		i = (jiaodu*2) / 1125;
		return con_Sin1125[i];
	}else
	{
		i = (jiaodu*2) / 1125;
		return con_Sin1125[i];
	}
}
#define jibofuzhi  10000
#define jibojiaodu	2
#define xiebocishu1		39
#define xiebocishu2		5
#define xiebocishu3		7
#define xiebocishu4		9

#define xiebofuzhi1		400
#define xiebofuzhi2		300
#define xiebofuzhi3		200
#define xiebofuzhi4		100

#define xiebojiaodu1    0
#define xiebojiaodu2    0
#define xiebojiaodu3    0
#define xiebojiaodu4    0
long test;
void harmonictest(void)
{
	uint8 i;
	test = sinp(722000);
	for(i = 0;i < 160; i ++)
	{
		gs_harmonicpp[i].iawv = (jibofuzhi * sinp((i*2250+jibojiaodu)) + 
						xiebofuzhi1 * sinp((i*xiebocishu1*2250+xiebojiaodu1)) +
						xiebofuzhi2 * sinp((i*xiebocishu2*2250+xiebojiaodu2)) +
						xiebofuzhi3 * sinp((i*xiebocishu3*2250+xiebojiaodu3)) +
						xiebofuzhi4 * sinp((i*xiebocishu4*2250+xiebojiaodu4)))/64;
		gs_harmonicpp[i].ibwv = (jibofuzhi * sinp((i*2250+jibojiaodu)) + 
						xiebofuzhi1 * sinp((i*xiebocishu1*2250+xiebojiaodu1)) +
						xiebofuzhi2 * sinp((i*xiebocishu2*2250+xiebojiaodu2)) +
						xiebofuzhi3 * sinp((i*xiebocishu3*2250+xiebojiaodu3)) +
						xiebofuzhi4 * sinp((i*xiebocishu4*2250+xiebojiaodu4)))/64;
		gs_harmonicpp[i].icwv = (jibofuzhi * sinp((i*2250+jibojiaodu)) + 
						xiebofuzhi1 * sinp((i*xiebocishu1*2250+xiebojiaodu1)) +
						xiebofuzhi2 * sinp((i*xiebocishu2*2250+xiebojiaodu2)) +
						xiebofuzhi3 * sinp((i*xiebocishu3*2250+xiebojiaodu3)) +
						xiebofuzhi4 * sinp((i*xiebocishu4*2250+xiebojiaodu4)))/64;
		//gs_harmonicpp[i].iawv = i;
	}
	
	calc_harmonic(gs_harmonicpp, & gs_harmonictest);
		
		
}
#endif



#endif










































