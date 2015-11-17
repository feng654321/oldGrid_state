/*******************************************************************************
模块名       : 谐波harmonic
文件名       : harmonic.c
相关文件     : 
文件实现功能 : 对给出的波形数据进行谐波分析,得到31次谐波的含量,以及零线电流的采样.
作者         : 
版本         : Ver 1.0。
-------------------------------------------------------------------------------
备注         : 该程序由于需要的资源较多,所以只用于集中器的数据采集,
-------------------------------------------------------------------------------
修改记录 : 
日 期        版本     修改人              修改内容
YYYY/MM/DD   X.Y      <作者或修改者名>    <修改内容>
===============================================================================
其他说明:   无。
*******************************************************************************/

#define AP_HARMONIC_GLOBALS

#include "common.h"
#include "ap_harmonic.h"


#if(CONFIG_METER_HARMONIC_ENABLE == GAL_YES)    

#define MAXHARMONICTIME 21


void harmonictest(void);

long gl_harmonic_datatemp[80*2];//谐波分析临时存储变量

ulong gl_harmonic_Nsum;

//序列一的转换
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
//序列二的转换
void calc_harmonic_x2(void)
{
	long* pldata = gl_harmonic_datatemp;
	long ldata,ldata1;
	uchar i;
	
	for(i = 0;i < 20;i ++)
	{
		ldata = *pldata;
		*pldata = *(pldata + 4) + ldata;	//第0个数的实部
		pldata ++;
		*pldata = 0;						//第0个数的需部
		pldata ++;
		ldata1 = *pldata;				//取第1个数的实部
		pldata ++;
		*pldata = *(pldata + 3);			//第1个数的需部
		pldata ++;
		*pldata = ldata - *pldata;		//第2个数的实部
		pldata ++;
		*pldata = 0;						//第2个数的需部
		pldata ++;
		*pldata = ldata1;				//第3个数的实部,与第3个数的实部相同
		pldata ++;
		*pldata = (long)0 - *(pldata - 4);//第3个数的需部
		pldata ++;	
	}
}

//序列三的转换
void calc_harmonic_x3(void)
{
	long* pldata = gl_harmonic_datatemp;
	long ldata1,ldata2,ldata3;
	uchar i;
	
	for(i = 0;i < 10;i ++)
	{
		ldata1 = *pldata;		//保存第0个数的实部
		ldata2 = *(pldata + 8);	//保存第4个数的实部
		*pldata = ldata2 + ldata1;			//第0个数的实部等于第0个数和第4个数的实部和
		*(pldata + 8) = ldata1 - ldata2;	//第4个数的实部等于第0个数减第4个数的实部
		
		pldata += 2;				//指向第1个数的实部,第1个数的需部维持原来的0不变
		ldata3 = (*(pldata + 8) * 181) / 256;//第5个数的实部乘以余弦值或正弦值
		ldata2 = (*(pldata + 9) * 181) / 256;//第5个数的需部乘以余弦值或正弦值
		ldata1 = ldata3 - ldata2;	//由于正余弦值是相等的,所以可以合并计算;
		ldata2 = ldata3 + ldata2;
		*pldata = *pldata + ldata1;//第1个数的实部=第1个数的实部+第5个数的实部乘以余弦值-第5个数的需部乘以正弦值
		pldata ++;					//指向第1个数的需部
		*pldata = *pldata + ldata2;//第1个数的需部=第1个数的需部+第5个数的实部乘以正弦值+第5个数的需部乘以余弦值
		
		pldata += 2;				//指向第2个数的需部,实部不变
		*pldata = *(pldata + 7);	//第2个数的需部等于第6个数的实部
		
		pldata ++;					//指向第3个数的实部
		*pldata = *pldata - ldata1;//第3个数的实部=第3个数的实部+第7个数的实部乘以余弦值-第7个数的需部乘以正弦值,第7个数与第5个数刚好对应
		pldata ++;					//指向第3个数的需部
		*pldata = ldata2 + *pldata;//第3个数的需部=第3个数的需部+第7个数的实部乘以正弦值+第7个数的需部乘以余弦值,第7个数与第5个数刚好对应
		
		pldata += 3;				//指向第5个数的实部,第4个数的需部保持为0,实部在前面已经计算了;
		*pldata = *(pldata - 4);	//第5个数的实部等于第3个数的实部
		pldata ++;					//指向第5个数的需部
		*pldata = (long)0 - *(pldata - 4);//第5个数的需部等于0 - 第3个数需部
		
		pldata ++;					//指向第6个数的实部
		ldata1 = *pldata;
		*pldata = *(pldata - 8);	//第6个数的实部等于第2个数的实部
		pldata ++;					//指向第6个数的需部
		*pldata = (long)0 - ldata1;//第6个数的需部等于0 - 第6个数需部
		
		pldata ++;					//指向第7个数的实部
		*pldata = *(pldata - 12);	//第7个数的实部等于第1个数的实部
		pldata ++;					//指向第7个数的需部
		*pldata = (long)0 - *(pldata - 12);//第7个数的需部等于0 - 第1个数需部
		pldata ++;					//指向第8个数的实部
	}
}
//序列4的转换
void calc_harmonic_x4(void)
{
	long* pldata = gl_harmonic_datatemp;
	long ldata1,ldata2,ldata3,ldata4,ldata5;
	uchar i;
	
	for(i = 0;i < 5;i ++)
	{
		ldata1 = *pldata;		//保存第0个数的实部
		ldata2 = *(pldata + 16);	//保存第8个数的实部
		*pldata = ldata2 + ldata1;			//第0个数的实部等于第0个数和第8个数的实部和
		*(pldata + 16) = ldata1 - ldata2;	//第8个数的实部等于第0个数减第8个数的实部
		
		pldata += 2;				//指向第1个数的实部,第0个数的需部保持原来的数据不变
		ldata5 = *(pldata + 16);		//保存第9个数的实部
		ldata2 = *(pldata + 17);		//保存第9个数的需部
		ldata1 = (ldata5 * 237) / 256;//第9个数的实部乘以余弦值
		ldata4 = (ldata5 * 98) / 256;//第9个数的实部乘以正弦值
		ldata3 = (ldata2 * 237) / 256;//第9个数的需部乘以余弦值
		ldata2 = (ldata2 * 98) / 256;//第9个数的需部乘以正弦值
		ldata1 = ldata1 - ldata2;	//ldata1 = 第9个数实部*余弦值-第9个数需部*正弦值,
		ldata2 = ldata3 + ldata4;	//ldata2 = 第9个数实部*正弦值-第9个数需部*余弦值,
		ldata3 = *pldata;			//保存第1个数的实部
		*pldata = ldata3 + ldata1;	//第1个数实部=第1个数实部+第9个数实部*余弦值-第9个数需部*正弦值
		*(pldata + 16) = ldata3 - ldata1;	//第9个数实部=第1个数实部-第9个数实部*余弦值+第9个数需部*正弦值
		pldata ++;					//指向第1个数的需部
		ldata3 = *pldata;			//保存第1个数的需部
		*pldata = ldata3 + ldata2;	//第1个数需部=第1个数需部+第9个数实部*正弦值+第9个数需部*余弦值
		*(pldata + 16) = ldata3 - ldata2;	//第9个数需部=第1个数需部-第9个数实部*正弦值+第9个数需部*余弦值
		
		pldata ++;				//指向第2个数的实部,第2个数的需部维持原来的0不变
		ldata3 = (*(pldata + 16) * 181) / 256;//第10个数的实部乘以余弦值或正弦值
		ldata2 = (*(pldata + 17) * 181) / 256;//第10个数的需部乘以余弦值或正弦值
		ldata1 = ldata3 - ldata2;	//由于正余弦值是相等的,所以可以合并计算;
		ldata2 = ldata3 + ldata2;
		ldata3 = *pldata;
		*pldata = ldata3 + ldata1;//第2个数的实部=第2个数的实部+第10个数的实部乘以余弦值-第10个数的需部乘以正弦值
		*(pldata + 16) = ldata3 - ldata1;//第10个数的实部=第2个数的实部-第10个数的实部乘以余弦值+第10个数的需部乘以正弦值
		pldata ++;					//指向第1个数的需部
		ldata3 = *pldata;
		*pldata = ldata3 + ldata2;//第2个数的需部=第2个数的需部+第10个数的实部乘以正弦值+第10个数的需部乘以余弦值
		*(pldata + 16) = ldata3 - ldata2;//第10个数的需部=第2个数的需部-第10个数的实部乘以正弦值-第10个数的需部乘以余弦值
		
		pldata ++;				//指向第3个数的实部
		ldata5 = *(pldata + 16);		//保存第11个数的实部
		ldata2 = *(pldata + 17);		//保存第11个数的需部
		ldata1 = (ldata5 * 98) / 256;//第11个数的实部乘以余弦值
		ldata4 = (ldata5 * 237) / 256;//第11个数的实部乘以正弦值
		ldata3 = (ldata2 * 98) / 256;//第11个数的需部乘以余弦值
		ldata2 = (ldata2 * 237) / 256;//第11个数的需部乘以正弦值
		ldata1 = ldata1 - ldata2;	//ldata1 = 第11个数实部*余弦值-第11个数需部*正弦值,
		ldata2 = ldata3 + ldata4;	//ldata2 = 第11个数实部*正弦值-第11个数需部*余弦值,
		ldata3 = *pldata;			//保存第3个数的实部
		*pldata = ldata3 + ldata1;	//第3个数实部=第3个数实部+第11个数实部*余弦值-第11个数需部*正弦值
		*(pldata + 16) = ldata3 - ldata1;	//第11个数实部=第3个数实部-第11个数实部*余弦值+第11个数需部*正弦值
		pldata ++;					//指向第3个数的需部
		ldata3 = *pldata;			//保存第3个数的需部
		*pldata = ldata3 + ldata2;	//第3个数需部=第3个数需部+第11个数实部*正弦值+第11个数需部*余弦值
		*(pldata + 16) = ldata3 - ldata2;	//第11个数需部=第3个数需部-第11个数实部*正弦值+第11个数需部*余弦值
		
		pldata += 2;				//指向第4个数的需部,实部不变
		*pldata = *(pldata + 15);	//第4个数的需部等于第12个数的实部
		
		pldata ++;					//指向第5个数的实部
		*pldata = *(pldata + 12);	//第5个数的实部=计算后的第11个数的实部
		pldata ++;					//指向第5个数的需部
		*pldata = (long)0 - *(pldata + 12);	//第5个数的需部=0-计算后的第11个数的需部
		
		pldata ++;					//指向第6个数的实部
		*pldata = *(pldata + 8);	//第6个数的实部=计算后的第10个数的实部
		pldata ++;					//指向第6个数的需部
		*pldata = (long)0 - *(pldata + 8);	//第6个数的需部=0-计算后的第10个数的需部
		
		pldata ++;					//指向第7个数的实部
		*pldata = *(pldata + 4);	//第7个数的实部=计算后的第9个数的实部
		pldata ++;					//指向第7个数的需部
		*pldata = (long)0 - *(pldata + 4);	//第7个数的需部=0-计算后的第9个数的需部
		
		pldata += 9;					//指向第12个数的实部
		*pldata = *(pldata - 16);	//第12个数的实部=计算后的第4个数的实部
		pldata ++;					//指向第12个数的需部
		*pldata = (long)0 - *(pldata - 16);	//第12个数的需部=0-计算后的第4个数的需部
		
		pldata ++;					//指向第13个数的实部
		*pldata = *(pldata - 20);	//第13个数的实部=计算后的第3个数的实部
		pldata ++;					//指向第12个数的需部
		*pldata = (long)0 - *(pldata - 20);	//第12个数的需部=0-计算后的第4个数的需部
		
		pldata ++;					//指向第14个数的实部
		*pldata = *(pldata - 24);	//第14个数的实部=计算后的第2个数的实部
		pldata ++;					//指向第14个数的需部
		*pldata = (long)0 - *(pldata - 24);	//第14个数的需部=0-计算后的第2个数的需部
		
		pldata ++;					//指向第15个数的实部
		*pldata = *(pldata - 28);	//第15个数的实部=计算后的第1个数的实部
		pldata ++;					//指向第15个数的需部
		*pldata = (long)0 - *(pldata - 28);	//第15个数的需部=0-计算后的第1个数的需部
		
		pldata ++;					//指向第16个数的实部
	}
}

						//  cos,sin,cos,sin,cos,sin,cos,sin
const uint8 con_CosSin[]={255,  0,255, 20,253, 40,249, 60,243, 79,237, 98,228,116,218,134,
						  207,150,195,166,181,181,166,195,150,207,134,218,116,228, 98,237,
						   79,243, 60,249, 40,253, 20,255,  0,255};
//序列5的转换
	long ltempdata[MAXHARMONICTIME*2];
void calc_harmonic_x5(void)
{
	long* pldata = gl_harmonic_datatemp + 4;//第0次不用计算
	long ldatas,ldatax,ldata1;
	short icos,isin;
	uchar i,j,k,uccossin;
	for(k = 0;k < 5;k ++)
	{
		pldata = gl_harmonic_datatemp;//指向第0个数
		for(i = 0;i < 16;i ++)
		{								//计算39次谐波含量,最多39次,可以调整
			ldatas = *pldata;			//临时实部赋值
			ldatax = *(pldata + 1);		//临时需部赋值
			for(j = 1;j < 5;j ++)
			{
				uccossin = (j * (k * 16 + i)) % 80;//正余弦值转换成360度内对应的值
				if(uccossin >= 60)
				{						//角度大于270度
					uccossin = (80 - uccossin) * 2;
					icos = con_CosSin[uccossin];	//取余弦值
					isin = -con_CosSin[uccossin + 1];//取正弦值
				}else if(uccossin >= 40)
				{						//角度在180度到270度
					uccossin = (uccossin - 40) * 2;
					icos = -con_CosSin[uccossin];
					isin = -con_CosSin[uccossin + 1];//
				}else if(uccossin >= 20)
				{						//角度在90度到180度
					uccossin = (40 - uccossin) * 2;
					icos = -con_CosSin[uccossin];
					isin = con_CosSin[uccossin + 1];//
				}else
				{						//角度小于90度
					uccossin = uccossin * 2;
					icos = con_CosSin[uccossin];
					isin = con_CosSin[uccossin + 1];//
				}
				ldata1 = *(pldata + 32 * j);//取实部
				ldatas += ldata1 * icos/256;		//实部乘余弦值 + 上一次的实部得到新的实部
				ldatax += ldata1 * isin/256;		//实部乘正弦值 + 上一次的实部得到新的需部
				ldata1 = *(pldata + 32 * j + 1);//取需部
				ldatas -= ldata1 * isin/256;//新的实部 - 需部乘正弦值
				ldatax += ldata1 * icos/256;//实部乘正弦值 + 需部乘余弦值
			}
			ltempdata[(k * 16 + i) * 2] = ldatas;
			ltempdata[(k * 16 + i) * 2 + 1] = ldatax;
			if((k*16 + i) > (MAXHARMONICTIME - 1))
			{
				k = 100;
				i = 100;//退出循环
			}
			pldata += 2;
		}
	}
}

//有效值计算
//=====================================================================================
//谐波谐波含量计算：void XbContentClct(void)：
//功能：计算得到2到31次谐波的含量
//输入参数：gs_XbData[]；
//输出参数：gui_XbContent[30]
//操作寄存器：guc_XbTempData1,guc_XbTempData2,guc_XbTempData3,guc_XbTempData4
//执行时间：大约??
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
			ucdata = ((uldata3 - uldata1)*64)/uldata3;//实部与需部的绝对值得差值
			uldata3 = (uldata3 * (256 + con_genhao[ucdata]))/256;
		}
		*(((ulong*)(ps_data + i)) + phase) = uldata3;
	}
	uldata1 = *((ulong*)(ps_data + 1) + phase);				//取基波除以
	ulsum = 0;
	if(uldata1 > 500000)
	{														//基波大于500000
		uldata1 /= 10000;
		for(i = 2;i <= ucmaxtime;i ++)
		{
			uldata2 = *((ulong*)(ps_data + i) + phase) / uldata1;//取谐波的有效值
			if(uldata2 < 70)
			{											//当谐波含量小于0.3%时,
				*((ulong*)(ps_data + i) + phase) = 0;	//相应的谐波有效值和含量清0
				*((ushort*)(ps_data + i) + 12 + phase) = 0;//谐波的含有率清0
			}else
			{
				*((ushort*)(ps_data + i) + 12 + phase) = uldata2;//将谐波含量保存到存储器中
				if(uldata2 > ulsum)
				{
					uldata3 = uldata2;					//uldata3存放大值
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
					ucdata = ((uldata3 - uldata2)*256)/uldata3;//实部与需部的绝对值得差值
					ulsum = (uldata3 * (257 + con_genhao[ucdata/4] - (ucdata & 0x03)))/256;
				}
			}
		}
		*((ulong*)(ps_data) + phase) = uldata1 * ulsum;	//谐波总有效值
	}else if(uldata1 < 500)
	{												//基波小于100
		for(i = 0;i <= ucmaxtime;i ++)
		{
			*((ulong*)(ps_data + i) + phase) = 0;	//相应的谐波有效值清0
			*((ushort*)(ps_data + i) + 12 + phase) = 0;	//相应的谐波含有率清0
		}
		return ;
	}else
	{												//基波小于500000的处理
		for(i = 2;i <= ucmaxtime;i ++)
		{
			uldata2 = (*((ulong*)(ps_data + i) + phase) * 10000) / uldata1;//取谐波的有效值
			if(uldata2 < 70)
			{											//当谐波含量小于0.3%时,
				*((ulong*)(ps_data + i) + phase) = 0;	//相应的谐波有效值和含量清0
				*((ushort*)(ps_data + i) + 12 + phase) = 0;//谐波的含有率清0
			}else
			{
				*((ushort*)(ps_data + i) + 12 + phase) = uldata2;//将谐波含量保存到存储器中
				if(uldata2 > ulsum)
				{
					uldata3 = uldata2;					//uldata3存放大值
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
					ucdata = ((uldata3 - uldata2)*256)/uldata3;//实部与需部的绝对值得差值
					ulsum = (uldata3 * (257 + con_genhao[ucdata/4] - (ucdata & 0x03)))/256;
				}
			}
		}
		*((ulong*)(ps_data) + phase) = uldata1 * ulsum/1000;	//谐波总有效值
	}
	*((ushort*)(ps_data) + 12 + phase) = ulsum;//畸变率幅值
	*((ushort*)(ps_data + 1) + 12 + phase) = 9999;//畸变率幅值
}

const uchar con_HmncZhengxu[80]=
	{ 0,40,20,60,10,50,30,70, 5,45,25,65,15,55,35,75,
	  1,41,21,61,11,51,31,71, 6,46,26,66,16,56,36,76,
	  2,42,22,62,12,52,32,72, 7,47,27,67,17,57,37,77,
	  3,43,23,63,13,53,33,73, 8,48,28,68,18,58,38,78,
	  4,44,24,64,14,54,34,74, 9,49,29,69,19,59,39,79};

	
int calc_harmonic(struct acs_harmonic_waveform *p_waveform,struct harmonic_data_list_st *p_harmonic_data_list)
{
	uchar i,j;//循环的临时变量
	long ldata;
	ulong ulsum;
	long lsum;
	
//fprintf(stderr, "%s-%d\n", __FUNCTION__, __LINE__);
	
	
	//零序电流计算
	ulsum = 0;
	lsum= 0;
	for(i = 0;i < 40;i ++)
	{
		ldata = ((long)(p_waveform + i*4 )->iawv * 256) / uiCoefCurrentGAIN[0] + ((long)(p_waveform + i*4)->ibwv * 256) / uiCoefCurrentGAIN[1]
					 + ((long)(p_waveform + i*4)->icwv * 256) / uiCoefCurrentGAIN[2];//电流ABC的瞬时值累加
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
	//调试用，打印谐波有效值
	//		memcpy(&ulsum,&RAM[RAM_CURRENT_I_NULLSEQU],4);
	//		fprintf(stderr, "lingxudianliu rms =  %08x    ", ulsum);
	//		fprintf(stderr, "lingxudianliu =  %08x   ", gl_harmonic_Nsum);
	//		fprintf(stderr, "jiaodu1 = %04x   ", *(ushort*)&RAM[RAM_CURRENT_ANGLE_AI_AV]);
	//		fprintf(stderr, "jiaodu1 = %04x  ", *(ushort*)&RAM[RAM_CURRENT_ANGLE_BI_AV]);
	//		fprintf(stderr, "jiaodu2 = %04x  ", *(ushort*)&RAM[RAM_CURRENT_ANGLE_CI_AV]);
			
	//	fprintf(stderr, " \n");
    
    //fprintf(stderr, "Address of RAM[0] = %x\n", &RAM[0]);
	
	//从输入数据中取80个点的数据并加上偏移,全部转换成正数后,按谐波分析的次序存储到存储器中
	for(i = 0;i < 7;i ++)
	{							//分析的电压电流相循环
		if(i == 3)
			continue;				//零线电流不分析
		for(j = 0;j < 80;j ++)
		{
			//gl_harmonic_datatemp[k*2+j*32] = *((ulong *)p_waveform + 14 * (j*16+k) + i);
			gl_harmonic_datatemp[j*2] = (*((long *)p_waveform + i + 14 * con_HmncZhengxu[j]))/20;
			//gl_harmonic_datatemp[k*2+j*32+1] = 0;
		}
		calc_harmonic_x1();			//序列1的转换,2的碟形
		calc_harmonic_x2();			//序列2的转换,4的碟形
		calc_harmonic_x3();			//序列3的转换,8的碟形
		calc_harmonic_x4();			//序列4的转换,16的碟形
		calc_harmonic_x5();			//序列5的转换,5点的碟形

//fprintf(stderr, "%s-%d,    addr = %08x\n", __FUNCTION__, __LINE__,p_harmonic_data_list);

		if(i < 3)
		{
			calc_harmonic_rms(sizeof(p_harmonic_data_list->harmonic_data_order)/sizeof(p_harmonic_data_list->harmonic_data_order[0]),
						&p_harmonic_data_list->harmonic_data_all,i);		//计算有效值、含量、畸变率等
		}else
		{
			calc_harmonic_rms(sizeof(p_harmonic_data_list->harmonic_data_order)/sizeof(p_harmonic_data_list->harmonic_data_order[0]),
						&p_harmonic_data_list->harmonic_data_all,i - 1);		//计算有效值、含量、畸变率等
		}
		//有效值校正
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
	//acs_start_harmonic(&gs_harmonic_para);	//开启谐波采集模块
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
	//acs_stop_harmonic();					//关闭谐波采集模块
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
	{										//取数据不成功
		acs_start_harmonic(&gs_harmonic_para);	//开启谐波采集模块
    	return ;								//直接返回
    }
	    
	//谐波数据取成功，将数据覆盖到RAM中
	uiaddr1 = 0;
	uiaddr2 = 0;
	for(i = 0;i < 3;i ++)
	{										//电压转换
		pldata32 = &s_harmonic_data.harmonic_data_all.voltage_rms[i];
		pldata16 = &s_harmonic_data.harmonic_data_all.voltage_per[i];
		for(j = 0;j <= 21;j ++)
		{
			LongToData4BCD(*pldata32/360,&RAM[RAM_CURRENT_HARMONIC_V_A_ALL + uiaddr1] );//电压有效值转换成BCD码，并将数据写入到RAM中
			uiaddr1 += 4;					//向后移动4个字节
			pldata32 += sizeof(struct harmonic_data_st)/4;//指向下一个谐波的电压有效值
			if(j == 0)
			{								//总失真度
				IntToData2BCD(*pldata16,&RAM[RAM_CURRENT_HARMONIC_PER_V_A_ALL + i * 2] );//电压含量转换成BCD码，并将数据写入到RAM中
				
			}else
			{
				IntToData2BCD(*pldata16,&RAM[RAM_CURRENT_HARMONIC_PER_V_A_01CI + uiaddr2] );//电压含量转换成BCD码，并将数据写入到RAM中
				uiaddr2 += 2;					//向后移动2个字节
			}
			pldata16 += sizeof(struct harmonic_data_st)/2;
		}
	}
	uiaddr1 = 0;
	uiaddr2 = 0;
	for(i = 0;i < 3;i ++)
	{										//电流转换
		pldata32 = &s_harmonic_data.harmonic_data_all.current_rms[i];
		pldata16 = &s_harmonic_data.harmonic_data_all.current_per[i];
		
		for(j = 0;j <= 21;j ++)
		{
			LongToData4BCD(*pldata32/101,&RAM[RAM_CURRENT_HARMONIC_I_A_ALL + uiaddr1] );//电流有效值转换成BCD码，并将数据写入到RAM中
			uiaddr1 += 4;					//向后移动4个字节
			pldata32 += sizeof(struct harmonic_data_st)/4;//指向下一个谐波的电压有效值
			if(j == 0)
			{								//总失真度
				IntToData2BCD(*pldata16,&RAM[RAM_CURRENT_HARMONIC_PER_I_A_ALL + i * 2] );//电压含量转换成BCD码，并将数据写入到RAM中
			}else
			{
				IntToData2BCD(*pldata16,&RAM[RAM_CURRENT_HARMONIC_PER_I_A_01CI + uiaddr2] );//电压含量转换成BCD码，并将数据写入到RAM中
				uiaddr2 += 2;					//向后移动2个字节
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










































