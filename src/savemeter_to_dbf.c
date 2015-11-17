//============================================================================
//  File Name: savemeter_to_dbf.c
//
//  Copyright PAX Hangzhou 2011.  All rights reserved.
//
//  Description:
//      表内数据到共享内存转存
//
//  Modification History:
//      $Id:  Exp $
//      $Log: $
//      Revision 1.0 Create by liuchiqi in 2011.04.28
//============================================================================
#ifndef __METER_MAIN_C__
#define __METER_MAIN_C__
#include <sys/file.h>   //for flock()
#include "common.h"
#include "savemeter_to_dbf.h"
#include "app_ipcs.h"

struct mp_rt_data_st *g_p_mp_rt_data_shm;			//实时数据共享内存数据
struct update_param_shm_st *g_p_update_param_shm;
//需要的数据项标识
#define CON_EECT_TEST_FILE             "/mnt/eect_meter_test.flg"           // 测试文件
extern unsigned char g_mnt_flag;

const short in_meter_rt_di_01[]=
{
	CON_DI_TYPE_MPVOL_BLOCK,
	CON_DI_TYPE_MPCUR_BLOCK,
	0
};

const short in_meter_rt_di_02[]=
{
	CON_DI_TYPE_MPINSTANTPOW_BLOCK,
	CON_DI_TYPE_MPINSTANTVAR_BLOCK,
	CON_DI_TYPE_MPPOWRATE_BLOCK,
	0
};


const short in_meter_rt_di_11[]=
{
	CON_DI_TYPE_MPDIRPOW_BLOCK,
	CON_DI_TYPE_MPUNDIRPOW_BLOCK,
	CON_DI_TYPE_MPDIRVAR_BLOCK,
	CON_DI_TYPE_MPUNDIRVAR_BLOCK,
	CON_DI_TYPE_MPDATEANDWEEK,
	CON_DI_TYPE_MPTIME,	
	0

};

const short in_meter_rt_di_12[]=
{
	CON_DI_TYPE_MPVAR1_BLOCK,
	CON_DI_TYPE_MPVAR2_BLOCK,
	CON_DI_TYPE_MPVAR3_BLOCK,
	CON_DI_TYPE_MPVAR4_BLOCK,
	0
};

const short in_meter_rt_di_13[]=
{
	CON_DI_TYPE_MPDIRPOWMAXDEMAND_BIG_BLOCK,
	CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_BIG_BLOCK,
	CON_DI_TYPE_MPDIRVARMAXDEMAND_BIG_BLOCK,
	CON_DI_TYPE_MPUNDIRVARMAXDEMAND_BIG_BLOCK,
	0
};

const short in_meter_rt_di_14[]=
{
	CON_DI_TYPE_DIRPOW_A,
	CON_DI_TYPE_UNDIRPOW_A,
	CON_DI_TYPE_SUMVAR1_A,
	CON_DI_TYPE_SUMVAR2_A,
	CON_DI_TYPE_DIRPOW_B,
	CON_DI_TYPE_UNDIRPOW_B,
	CON_DI_TYPE_SUMVAR1_B,
	CON_DI_TYPE_SUMVAR2_B,
	CON_DI_TYPE_DIRPOW_C,
	CON_DI_TYPE_UNDIRPOW_C,
	CON_DI_TYPE_SUMVAR1_C,
	CON_DI_TYPE_SUMVAR2_C,
	0
};

const short in_meter_rt_di_15[]=
{
	CON_DI_TYPE_MPHARMONIC_VAL_VOLA_BLOCK,     //电压谐波有效值数据块
	CON_DI_TYPE_MPHARMONIC_VAL_VOLB_BLOCK,      //电压谐波有效值数据块
	CON_DI_TYPE_MPHARMONIC_VAL_VOLC_BLOCK,      //电压谐波有效值数据块
	0
};

const short in_meter_rt_di_16[]=
{
	CON_DI_TYPE_MPHARMONIC_VAL_CURA_BLOCK,	    //电流谐波有效值数据块
	CON_DI_TYPE_MPHARMONIC_VAL_CURB_BLOCK,	    //电流谐波有效值数据块
	CON_DI_TYPE_MPHARMONIC_VAL_CURC_BLOCK,	    //电流谐波有效值数据块
	0
};

const short in_meter_rt_di_17[]=
{
	CON_DI_TYPE_MPHARMONIC_RATE_VOLA_BLOCK,    //电压谐波含有率数据块
	CON_DI_TYPE_MPHARMONIC_RATE_VOLB_BLOCK,    //电压谐波含有率数据块
	CON_DI_TYPE_MPHARMONIC_RATE_VOLC_BLOCK,    //电压谐波含有率数据块
	0
};

const short in_meter_rt_di_18[]=
{
	CON_DI_TYPE_MPHARMONIC_RATE_CURA_BLOCK,   //电流谐波含有率数据块
	CON_DI_TYPE_MPHARMONIC_RATE_CURB_BLOCK,   //电流谐波含有率数据块
	CON_DI_TYPE_MPHARMONIC_RATE_CURC_BLOCK,   //电流谐波含有率数据块
	0
};

const short in_meter_rt_di_19[]=
{
	CON_DI_TYPE_MPHARMONIC_RATE_VOLA_TOL,      //电压谐波含有率数据块
	CON_DI_TYPE_MPHARMONIC_RATE_VOLB_TOL,      //电压谐波含有率数据块
	CON_DI_TYPE_MPHARMONIC_RATE_VOLC_TOL,      //电压谐波含有率数据块
	0
};
const short in_meter_rt_di_20[]=
{
	CON_DI_TYPE_CU_LOST,
	CON_DI_TYPE_FE_LOST,
	CON_DI_TYPE_METER_STAT_FLAG_BLOCK,
	CON_DI_TYPE_MPPHS_ANGLE_VAL_ALL,
       CON_DI_TYPE_MPPHS_ANGLE_I_ALL,
	0
};

const short in_meter_rt_di_21[]=
{

	CON_DI_TYPE_MPVOLBREAKNUMA,
	CON_DI_TYPE_MPVOLBREAKNUMB,
	CON_DI_TYPE_MPVOLBREAKNUMC,
	CON_DI_TYPE_MPVOLBREAKTIMEA,
	CON_DI_TYPE_MPVOLBREAKTIMEB,
	CON_DI_TYPE_MPVOLBREAKTIMEC,
	0
};

const short in_meter_rt_di_22[]=
{
	CON_DI_TYPE_MPLASTVOLBREAKBEGTIMEA,
	CON_DI_TYPE_MPLASTVOLBREAKBEGTIMEB,
	CON_DI_TYPE_MPLASTVOLBREAKBEGTIMEC,
	CON_DI_TYPE_MPLASTVOLBREAKENDTIMEA,
	CON_DI_TYPE_MPLASTVOLBREAKENDTIMEB,
	CON_DI_TYPE_MPLASTVOLBREAKENDTIMEC,
	0
};

const short in_meter_rt_di_23[]=
{
	CON_DI_TYPE_METER_OPEN_SWITCH,
	CON_DI_TYPE_METER_CLOSE_SWITCH,
	CON_DI_TYPE_METER_REMAIN_MONEY,
	CON_DI_TYPE_METER_OVERDRAFT,
	CON_DI_TYPE_METER_BUYPOW_TIMES_TOTAL,
	CON_DI_TYPE_METER_BUYPOW_MENEY_TOTAL,
	CON_DI_TYPE_MPMETERCLEARTIMES,		//电表清零总次数
	CON_DI_TYPE_MPEVENTCLEARTIMES,		//事件清零总次数
	CON_DI_TYPE_MPTIMINGTIMES,		//校时总次数
	CON_DI_TYPE_MPLATELYMETERCLEARTIME,	//最近一次电表清零发生时刻
	CON_DI_TYPE_MPLATELYEVENTCLEARTIME,	//最近一次事件清零发生时刻
	CON_DI_TYPE_MPLATELYTIMINGTIME,		//最近一次校时发生时刻
	CON_DI_TYPE_MPBATWORKTIME,
	CON_DI_TYPE_MPPROGTIMETIMES,
	CON_DI_TYPE_MPMAXDEMANDCLEARTIMES,
	CON_DI_TYPE_MPLATELYMAXDEMANDCLEARTIME,
	CON_DI_TYPE_MPLATELYPROGTIME,
	0
};


const short in_meter_hourfreeze_di[]=
{
	CON_DI_TYPE_METER_HOUR_FREEZE_BLOCK,
	0
};

const short in_meter_dayfreeze_di[]=
{
/*
	CON_DI_TYPE_METER_DAY_FREEZE_TIME,
	CON_DI_TYPE_METER_DAY_FREEZE_DIRPOW,
	CON_DI_TYPE_METER_DAY_FREEZE_REVPOW,
	CON_DI_TYPE_METER_DAY_FREEZE_DIRVAR,
	CON_DI_TYPE_METER_DAY_FREEZE_REVVAR,
	CON_DI_TYPE_METER_DAY_FREEZE_VAR1,
	CON_DI_TYPE_METER_DAY_FREEZE_VAR2,
	CON_DI_TYPE_METER_DAY_FREEZE_VAR3,
	CON_DI_TYPE_METER_DAY_FREEZE_VAR4,
	CON_DI_TYPE_METER_DAY_FREEZE_DIRPOWDEMAND,
	CON_DI_TYPE_METER_DAY_FREEZE_REVPOWDEMAND,
	CON_DI_TYPE_METER_DAY_FREEZE_POWER,
*/	
	CON_DI_TYPE_CU_LOST_LM,
	CON_DI_TYPE_FE_LOST_LM,

	CON_DI_TYPE_DIRPOW_A_LM,
	CON_DI_TYPE_UNDIRPOW_A_LM,
	CON_DI_TYPE_SUMVAR1_A_LM,
	CON_DI_TYPE_SUMVAR2_A_LM,

	CON_DI_TYPE_DIRPOW_B_LM,
	CON_DI_TYPE_UNDIRPOW_B_LM,
	CON_DI_TYPE_SUMVAR1_B_LM,
	CON_DI_TYPE_SUMVAR2_B_LM,

	CON_DI_TYPE_DIRPOW_C_LM,
	CON_DI_TYPE_UNDIRPOW_C_LM,
	CON_DI_TYPE_SUMVAR1_C_LM,
	CON_DI_TYPE_SUMVAR2_C_LM,
	CON_DI_TYPE_MPPOWCONST,
	CON_DI_TYPE_MPVARCONST,

	CON_DI_TYPE_MPDIRPOW_LM_BLOCK,
	CON_DI_TYPE_MPDIRPOW_LM_BLOCK,
	CON_DI_TYPE_MPUNDIRPOW_LM_BLOCK,
	CON_DI_TYPE_MPDIRVAR_LM_BLOCK,
	CON_DI_TYPE_MPUNDIRVAR_LM_BLOCK,

	CON_DI_TYPE_MPVAR1_LM_BLOCK,
	CON_DI_TYPE_MPVAR4_LM_BLOCK,
	CON_DI_TYPE_MPVAR2_LM_BLOCK,
	CON_DI_TYPE_MPVAR3_LM_BLOCK,

	 CON_DI_TYPE_MPDIRPOWMAXDEMAND_LM_BLOCK,
	 CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_LM_BLOCK,
	 CON_DI_TYPE_MPDIRVARMAXDEMAND_LM_BLOCK,
	 CON_DI_TYPE_MPUNDIRVARMAXDEMAND_LM_BLOCK,
	 CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_LM_BLOCK,
	 CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_LM_BLOCK,
	 CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_LM_BLOCK,
	 CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_LM_BLOCK,
	0
};

unsigned long di97_to_di07(unsigned short data_id);
int inter_data_mng(unsigned short mpno, unsigned short data_id, unsigned char *recv_data, unsigned short recv_len, unsigned char proto_flag, unsigned char data_flag,unsigned char poweroff_flag);
struct date_time_rec get_current_time(void);
void get_part_id_from_big_block(unsigned short data_id , unsigned short * pbase_id,unsigned short *pbase_id0);
void get_baseid_from_daydataid(unsigned short *base_id,unsigned short *data_id);
int save_mp_his_curve_data_by_mpno(int mpno, unsigned short data_id, unsigned long *puldata_val, struct date_time_rec *rec_time);
int db_sd_drt_write_data_shm(struct data_rt *sd);
int db_sd_drt_check_di_is_db(unsigned short di);
int bdb_check(void);
extern unsigned char g_day_freeze_flag, g_hour_freeze_flag;
unsigned char data_save_count;

extern s16 GetDataByDLT07ID(uchar *pData, u16 *ucLen, ulong ID, u16 ulBufLen);

//==================================================================
//函数名：  param_shm_init
//作者：    
//日期：    2011-05-07
//功能：    内表初始化的时候调用
//输入参数：无
//输出参数：无
//返回值：  成功返回0，失败返回-1
//=================================================================
int param_shm_init(void)
{
	g_p_update_param_shm = app_shm_open(SHM_KEY_PROTO,sizeof(struct update_param_shm_st),0);

	if(g_p_update_param_shm == NULL)
	{
		log_printf_level(LOG_LEVEL_ERR, DBGFMT_A" ERR shmat \n",DBGARG_A);
		return -1;
	}


	g_p_mp_rt_data_shm = app_shm_open(SHM_KEY_RT_DATA,sizeof(struct mp_rt_data_st),1);
	if(g_p_mp_rt_data_shm == NULL)
	{
		log_printf_level(LOG_LEVEL_ERR, DBGFMT_A" ERR shmat g_p_mp_rt_data_shm \n",DBGARG_A);
		return -1;
	}

	return 0;
}
//

//==================================================================
//函数名：  savemeterdata_to_dbf_per
//作者：    
//日期：    2011-05-07
//功能：    把表数据保存集中器对应位置
//输入参数：unsigned short mpno    测量点
//				   unsigned short * di      数据项列表地址
//输出参数：无
//返回值：  成功返回0，失败返回-1
//=================================================================*/
void savemeterdata_to_dbf_per(unsigned short mpno,unsigned short * di,unsigned char poweroff_flag)
{
	int ret=-1, i=0;
	unsigned short *di_tmp=di;
	unsigned long ulid_07 ;
	unsigned short usid_97;
	unsigned char pdata[300];
	unsigned short recv_len;

	for(i=0;*(di_tmp+i)!=0;i++)  //实时数据转换
	{
		memset(pdata,0x00,300);
		usid_97=*(di_tmp+i);
		ulid_07 = di97_to_di07(usid_97);
		ret = GetDataByDLT07ID(pdata, &recv_len, ulid_07, 300);
		if(ret >=0)
		{
			inter_data_mng(mpno, usid_97, pdata, recv_len, 0x91,1,poweroff_flag);
		}
	}
}
/*==================================================================
//函数名：  savemeterdata_to_dbf
//作者：    
//日期：    2011-05-07
//功能：    把表数据保存到实时数据库( 另小时冻结 日冻结保存?
			表主程序每隔1s调用一次
//输入参数：无
//输出参数：无
//返回值：  成功返回0，失败返回-1
//=================================================================*/
void savemeterdata_to_dbf(unsigned char poweroff_flag)
{
	//int ret=-1, i=0,k=0;
	//unsigned long ulid_07 ;
	//unsigned short usid_97;
	//unsigned char pdata[300];
	//unsigned long ulval=0;
	//unsigned short recv_len;
	FILE *fp;
	unsigned short mpno=g_p_update_param_shm->shm_ter_sample_mp_no;
	struct date_time_rec cur_time= get_current_time();

	struct collstate tmp_collstate, *ptr_cs;					//交流采集作为表的状态
	int cs_num;

#if(CONFIG_METER_FACTORY_MODE_ENABLE == CONFIG_METER_FACTORY_MODE)
	g_mnt_flag =0x01;
#else	
	if(g_mnt_flag !=0x01)   //mnt 分区判断
	{
		if((fp=fopen(CON_EECT_TEST_FILE,"w")) != NULL)
		{
			fclose(fp);
			if (bdb_check() == 1)
				g_mnt_flag =0x01;
		}
	}
#endif	
	switch(data_save_count)
	{
	case 0:
	case 10:
	case 30:		
	case 40:		
	case 50:		
		savemeterdata_to_dbf_per( mpno,(unsigned short *)in_meter_rt_di_01,poweroff_flag);
		break;
	case 6:
	case 16:
	case 26:		
	case 36:		
	case 46:		
	case 56:		
		savemeterdata_to_dbf_per( mpno,(unsigned short *)in_meter_rt_di_02,poweroff_flag);
		savemeterdata_to_dbf_per( mpno,(unsigned short *)in_meter_rt_di_11,poweroff_flag);		
		break;
	case 2:
	case 12:
	case 22:
	case 32:
	case 42:
	case 52:
		savemeterdata_to_dbf_per( mpno,(unsigned short *)in_meter_rt_di_11,poweroff_flag);
		break;		
	case 4:
		savemeterdata_to_dbf_per( mpno,(unsigned short *)in_meter_rt_di_12,poweroff_flag);
		break;
	case 8:
		savemeterdata_to_dbf_per( mpno,(unsigned short *)in_meter_rt_di_13,poweroff_flag);
		break;
	case 14:
		savemeterdata_to_dbf_per( mpno,(unsigned short *)in_meter_rt_di_14,poweroff_flag);
		break;	
	case 18:
		savemeterdata_to_dbf_per( mpno,(unsigned short *)in_meter_rt_di_15,poweroff_flag);
		break;
	case 24:
		savemeterdata_to_dbf_per( mpno,(unsigned short *)in_meter_rt_di_16,poweroff_flag);
		break;
	case 28:
		savemeterdata_to_dbf_per( mpno,(unsigned short *)in_meter_rt_di_17,poweroff_flag);
		break;	
	case 34:
		savemeterdata_to_dbf_per( mpno,(unsigned short *)in_meter_rt_di_18,poweroff_flag);
		break;
	case 38:
		savemeterdata_to_dbf_per( mpno,(unsigned short *)in_meter_rt_di_19,poweroff_flag);
		break;
	case 48:		
		savemeterdata_to_dbf_per( mpno,(unsigned short *)in_meter_rt_di_20,poweroff_flag);
		break;
	case 54:
		savemeterdata_to_dbf_per( mpno,(unsigned short *)in_meter_rt_di_21,poweroff_flag);
		break;		
	case 58:		
		savemeterdata_to_dbf_per( mpno,(unsigned short *)in_meter_rt_di_22,poweroff_flag);
		break;
#if(CONFIG_METER_FACTORY_MODE_ENABLE != CONFIG_METER_FACTORY_MODE)		
	case 59:
		if(mpno > 0 && mpno < CON_698_TER_SAMPLE_DEFAULT_MPNO)
		{
			ptr_cs = NULL;
			cs_num = 0;
			if(db_rd_cs_get(mpno, mpno, (&ptr_cs), &cs_num) == 0)
			{
				if(cs_num == 1)
				{
					if(ptr_cs[0].status != CON_PLC_MNG_METER_SUCCESS)		//读取发现状态非成功则需要修改
						cs_num = 0;
				}
			}
			if(ptr_cs != NULL)
				free(ptr_cs);

			if(cs_num != 1)
			{
				tmp_collstate.mpno = mpno;
				tmp_collstate.status = CON_PLC_MNG_METER_SUCCESS;
				memset(tmp_collstate.addr, 0x00, 6);
				tmp_collstate.replay_depth = 0;
				tmp_collstate.rep_pareant_mpno = 0;
				db_rd_cs_add_one(&tmp_collstate);
			}
		}
		break;
#endif		
	case 60:
		savemeterdata_to_dbf_per( mpno,(unsigned short *)in_meter_rt_di_23,poweroff_flag);
		break;
		
	default:
	       break;
	}
	if(data_save_count>60)
		data_save_count=0;
	else 
		data_save_count++;

/*	if( (cur_time.minute >5) && 	(cur_time.hour !=  g_hour_freeze_flag)&&(g_mnt_flag ==0x01))
	{
		g_hour_freeze_flag = cur_time.hour ;
		savemeterdata_to_dbf_per( mpno,(unsigned short *)in_meter_hourfreeze_di,poweroff_flag);
	}
*/
	if( (cur_time.minute >10 ) && (cur_time.day !=  g_day_freeze_flag)&&(g_mnt_flag ==0x01))
	{
		g_day_freeze_flag = cur_time.day;
		savemeterdata_to_dbf_per( mpno,(unsigned short *)in_meter_dayfreeze_di,poweroff_flag);
	}
	return;
}

unsigned long di97_to_di07(unsigned short data_id)
{
	int pos = 0;
	unsigned char frame[4];
	unsigned long ret_di_07 = 0;
	switch(data_id)
	{
	case CON_DI_TYPE_MPDIRPOWTOTAL:		//正向有功电量
	case CON_DI_TYPE_MPDIRPOWPLUS:
	case CON_DI_TYPE_MPDIRPOWAPEX:
	case CON_DI_TYPE_MPDIRPOWFLAT:
	case CON_DI_TYPE_MPDIRPOWVALE:
		frame[pos ++] = 0x00;
		frame[pos ++] = (unsigned char)(data_id & 0x000F);
		frame[pos ++] = 0x01;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPDIRPOW_BLOCK:
		frame[pos ++] = 0x00;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x01;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPUNDIRPOWTOTAL:		//反向有功电量
	case CON_DI_TYPE_MPUNDIRPOWPLUS:
	case CON_DI_TYPE_MPUNDIRPOWAPEX:
	case CON_DI_TYPE_MPUNDIRPOWFLAT:
	case CON_DI_TYPE_MPUNDIRPOWVALE:
		frame[pos ++] = 0x00;
		frame[pos ++] = (unsigned char)(data_id & 0x000F);
		frame[pos ++] = 0x02;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPUNDIRPOW_BLOCK:
		frame[pos ++] = 0x00;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x02;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPDIRVARTOTAL:		//正向无功电量
	case CON_DI_TYPE_MPDIRVARPLUS:
	case CON_DI_TYPE_MPDIRVARAPEX:
	case CON_DI_TYPE_MPDIRVARFLAT:
	case CON_DI_TYPE_MPDIRVARVALE:
		frame[pos ++] = 0x00;
		frame[pos ++] = (unsigned char)(data_id & 0x000F);
		frame[pos ++] = 0x03;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPDIRVAR_BLOCK:
		frame[pos ++] = 0x00;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x03;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPUNDIRVARTOTAL:		//反向无功电量
	case CON_DI_TYPE_MPUNDIRVARPLUS:
	case CON_DI_TYPE_MPUNDIRVARAPEX:
	case CON_DI_TYPE_MPUNDIRVARFLAT:
	case CON_DI_TYPE_MPUNDIRVARVALE:
		frame[pos ++] = 0x00;
		frame[pos ++] = (unsigned char)(data_id & 0x000F);
		frame[pos ++] = 0x04;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPUNDIRVAR_BLOCK:
		frame[pos ++] = 0x00;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x04;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPVAR1:
	case CON_DI_TYPE_MPVAR1_FEE1:
	case CON_DI_TYPE_MPVAR1_FEE2:
	case CON_DI_TYPE_MPVAR1_FEE3:
	case CON_DI_TYPE_MPVAR1_FEE4:
		frame[pos ++] = 0x00;
		frame[pos ++] = (unsigned char)(data_id & 0x000F);
		frame[pos ++] = 0x05;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPVAR1_BLOCK:		//一象限无功电能数据块
		frame[pos ++] = 0x00;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x05;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPVAR2:
	case CON_DI_TYPE_MPVAR2_FEE1:
	case CON_DI_TYPE_MPVAR2_FEE2:
	case CON_DI_TYPE_MPVAR2_FEE3:
	case CON_DI_TYPE_MPVAR2_FEE4:
		frame[pos ++] = 0x00;
		frame[pos ++] = (unsigned char)(data_id & 0x000F);
		frame[pos ++] = 0x06;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPVAR2_BLOCK:		//二象限无功电能数据块
		frame[pos ++] = 0x00;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x06;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPVAR3:
	case CON_DI_TYPE_MPVAR3_FEE1:
	case CON_DI_TYPE_MPVAR3_FEE2:
	case CON_DI_TYPE_MPVAR3_FEE3:
	case CON_DI_TYPE_MPVAR3_FEE4:
		frame[pos ++] = 0x00;
		frame[pos ++] = (unsigned char)(data_id & 0x000F);
		frame[pos ++] = 0x07;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPVAR3_BLOCK:		//三象限无功电能数据块
		frame[pos ++] = 0x00;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x07;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPVAR4:
	case CON_DI_TYPE_MPVAR4_FEE1:
	case CON_DI_TYPE_MPVAR4_FEE2:
	case CON_DI_TYPE_MPVAR4_FEE3:
	case CON_DI_TYPE_MPVAR4_FEE4:
		frame[pos ++] = 0x00;
		frame[pos ++] = (unsigned char)(data_id & 0x000F);
		frame[pos ++] = 0x08;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPVAR4_BLOCK:		//四象限无功电能数据块
		frame[pos ++] = 0x00;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x08;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPDIRPOWMAXDEMAND:			//正向有功最大需量
	case CON_DI_TYPE_MPDIRPOWMAXDEMAND_FEE1:
	case CON_DI_TYPE_MPDIRPOWMAXDEMAND_FEE2:
	case CON_DI_TYPE_MPDIRPOWMAXDEMAND_FEE3:
	case CON_DI_TYPE_MPDIRPOWMAXDEMAND_FEE4:
	case CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME:			//正向有功最大需量发生时间
	case CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_FEE1:
	case CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_FEE2:
	case CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_FEE3:
	case CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_FEE4:
		frame[pos ++] = 0x00;
		frame[pos ++] = (unsigned char)(data_id & 0x000F);
		frame[pos ++] = 0x01;
		frame[pos ++] = 0x01;	
		break;
	case CON_DI_TYPE_MPDIRPOWMAXDEMAND_BLOCK:
	case CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_BLOCK:
	case CON_DI_TYPE_MPDIRPOWMAXDEMAND_BIG_BLOCK:
		frame[pos ++] = 0x00;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x01;
		frame[pos ++] = 0x01;	
		break;
	case CON_DI_TYPE_MPUNDIRPOWMAXDEMAND:			//反向有功最大需量
	case CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_FEE1:
	case CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_FEE2:
	case CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_FEE3:
	case CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_FEE4:
	case CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME:			//反向有功最大需量发生时间
	case CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_FEE1:
	case CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_FEE2:
	case CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_FEE3:
	case CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_FEE4:
		frame[pos ++] = 0x00;
		frame[pos ++] = (unsigned char)(data_id & 0x000F);
		frame[pos ++] = 0x02;
		frame[pos ++] = 0x01;	
		break;
	case CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_BLOCK:
	case CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_BLOCK:
	case CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_BIG_BLOCK:
		frame[pos ++] = 0x00;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x02;
		frame[pos ++] = 0x01;	
		break;
	case CON_DI_TYPE_MPDIRVARMAXDEMAND:			//正向无功最大需量
	case CON_DI_TYPE_MPDIRVARMAXDEMAND_FEE1:
	case CON_DI_TYPE_MPDIRVARMAXDEMAND_FEE2:
	case CON_DI_TYPE_MPDIRVARMAXDEMAND_FEE3:
	case CON_DI_TYPE_MPDIRVARMAXDEMAND_FEE4:
	case CON_DI_TYPE_MPDIRVARMAXDEMANDTIME:			//正向无功最大需量发生时间
	case CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_FEE1:
	case CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_FEE2:
	case CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_FEE3:
	case CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_FEE4:
		frame[pos ++] = 0x00;
		frame[pos ++] = (unsigned char)(data_id & 0x000F);
		frame[pos ++] = 0x03;
		frame[pos ++] = 0x01;	
		break;
	case CON_DI_TYPE_MPDIRVARMAXDEMAND_BLOCK:
	case CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_BLOCK:
	case CON_DI_TYPE_MPDIRVARMAXDEMAND_BIG_BLOCK:
		frame[pos ++] = 0x00;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x03;
		frame[pos ++] = 0x01;	
		break;
	case CON_DI_TYPE_MPUNDIRVARMAXDEMAND:			//反向无功最大需量
	case CON_DI_TYPE_MPUNDIRVARMAXDEMAND_FEE1:
	case CON_DI_TYPE_MPUNDIRVARMAXDEMAND_FEE2:
	case CON_DI_TYPE_MPUNDIRVARMAXDEMAND_FEE3:
	case CON_DI_TYPE_MPUNDIRVARMAXDEMAND_FEE4:
	case CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME:			//反向无功最大需量发生时间
	case CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_FEE1:
	case CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_FEE2:
	case CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_FEE3:
	case CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_FEE4:
		frame[pos ++] = 0x00;
		frame[pos ++] = (unsigned char)(data_id & 0x000F);
		frame[pos ++] = 0x04;
		frame[pos ++] = 0x01;	
		break;
	case CON_DI_TYPE_MPUNDIRVARMAXDEMAND_BLOCK:
	case CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_BLOCK:
	case CON_DI_TYPE_MPUNDIRVARMAXDEMAND_BIG_BLOCK:
		frame[pos ++] = 0x00;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x04;
		frame[pos ++] = 0x01;	
		break;
	case CON_DI_TYPE_MPVOLA:
	case CON_DI_TYPE_MPVOLB:
	case CON_DI_TYPE_MPVOLC:
		frame[pos ++] = 0x00;
		frame[pos ++] = (unsigned char)(data_id & 0x000F);
		frame[pos ++] = 0x01;
		frame[pos ++] = 0x02;	
		break;
	case CON_DI_TYPE_MPVOL_BLOCK:					//电压数据块
		frame[pos ++] = 0x00;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x01;
		frame[pos ++] = 0x02;	
		break;
	case CON_DI_TYPE_MPCURA:
	case CON_DI_TYPE_MPCURB:
	case CON_DI_TYPE_MPCURC:
		frame[pos ++] = 0x00;
		frame[pos ++] = (unsigned char)(data_id & 0x000F);
		frame[pos ++] = 0x02;
		frame[pos ++] = 0x02;	
		break;
	case CON_DI_TYPE_MPCUR_BLOCK:					//电流数据块
		frame[pos ++] = 0x00;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x02;
		frame[pos ++] = 0x02;	
		break;
	case CON_DI_TYPE_MPINSTANTPOW:
	case CON_DI_TYPE_MPINSTANTPOWA:
	case CON_DI_TYPE_MPINSTANTPOWB:
	case CON_DI_TYPE_MPINSTANTPOWC:
		frame[pos ++] = 0x00;
		frame[pos ++] = (unsigned char)(data_id & 0x000F);
		frame[pos ++] = 0x03;
		frame[pos ++] = 0x02;	
		break;
	case CON_DI_TYPE_MPINSTANTPOW_BLOCK:			//有功功率数据块
		frame[pos ++] = 0x00;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x03;
		frame[pos ++] = 0x02;	
		break;
	case CON_DI_TYPE_MPINSTANTVAR:
	case CON_DI_TYPE_MPINSTANTVARA:
	case CON_DI_TYPE_MPINSTANTVARB:
	case CON_DI_TYPE_MPINSTANTVARC:
		frame[pos ++] = 0x00;
		frame[pos ++] = (unsigned char)(data_id & 0x000F);
		frame[pos ++] = 0x04;
		frame[pos ++] = 0x02;	
		break;
	case CON_DI_TYPE_MPINSTANTVAR_BLOCK:			//无功功率数据块
		frame[pos ++] = 0x00;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x04;
		frame[pos ++] = 0x02;	
		break;
    case CON_DI_TYPE_MPPOWRATE_BLOCK:
        frame[pos ++] = 0x00;
        frame[pos ++] = 0xFF;
        frame[pos ++] = 0x06;
        frame[pos ++] = 0x02;	
		break;

	case CON_DI_TYPE_MPLATELYPROGTIME:				//最近一次编程时间
		frame[pos ++] = 0x01;
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x30;
		frame[pos ++] = 0x03;	
		break;
	case CON_DI_TYPE_MPLATELYMAXDEMANDCLEARTIME:				//最近一次最大需量清零时间
		frame[pos ++] = 0x01;
		frame[pos ++] = 0x02;
		frame[pos ++] = 0x30;
		frame[pos ++] = 0x03;	
		break;
	case CON_DI_TYPE_MPPROGTIMETIMES:				//编程次数
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x30;
		frame[pos ++] = 0x03;	
		break;
	case CON_DI_TYPE_MPMAXDEMANDCLEARTIMES:				//最大需量清零次数
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x02;
		frame[pos ++] = 0x30;
		frame[pos ++] = 0x03;	
		break;

	case CON_DI_TYPE_MPMETERCLEARTIMES:	//电表清零总次数
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x01;
		frame[pos ++] = 0x30;
		frame[pos ++] = 0x03;	
		break;
	case CON_DI_TYPE_MPEVENTCLEARTIMES:	//事件清零总次数
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x03;
		frame[pos ++] = 0x30;
		frame[pos ++] = 0x03;	
		break;
	case CON_DI_TYPE_MPTIMINGTIMES:			//校时总次数
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x04;
		frame[pos ++] = 0x30;
		frame[pos ++] = 0x03;	
		break;
	case CON_DI_TYPE_MPLATELYMETERCLEARTIME:	//最近一次电表清零发生时刻
		frame[pos ++] = 0x01;
		frame[pos ++] = 0x01;
		frame[pos ++] = 0x30;
		frame[pos ++] = 0x03;	
		break;	
	case CON_DI_TYPE_MPLATELYEVENTCLEARTIME:	//最近一次事件清零发生时刻
		frame[pos ++] = 0x01;
		frame[pos ++] = 0x03;
		frame[pos ++] = 0x30;
		frame[pos ++] = 0x03;	
		break;		
	case CON_DI_TYPE_MPLATELYTIMINGTIME:		//最近一次校时发生时刻
		frame[pos ++] = 0x01;
		frame[pos ++] = 0x04;
		frame[pos ++] = 0x30;
		frame[pos ++] = 0x03;	
		break;

	case CON_DI_TYPE_MPBATWORKTIME:				//电池工作时间
		frame[pos ++] = 0x0A;
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x80;
		frame[pos ++] = 0x02;	
		break;

/************************************************************************/

    case CON_DI_TYPE_MPVOLBREAKNUMA:	
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x13;	
		break;
	case CON_DI_TYPE_MPVOLBREAKNUMB:
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x02;
        frame[pos ++] = 0x13;	
		break;
	case CON_DI_TYPE_MPVOLBREAKNUMC:
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x03;
        frame[pos ++] = 0x13;	
		break;

	case CON_DI_TYPE_MPVOLBREAKTIMEA: 
        frame[pos ++] = 0x02;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x13;	
		break;
	case CON_DI_TYPE_MPVOLBREAKTIMEB:
        frame[pos ++] = 0x02;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x02;
        frame[pos ++] = 0x13;	
		break;
	case CON_DI_TYPE_MPVOLBREAKTIMEC:
        frame[pos ++] = 0x02;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x03;
        frame[pos ++] = 0x13;	
		break;
    case CON_DI_TYPE_MPLASTVOLBREAKBEGTIMEA:	
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x13;	
		break;
	case CON_DI_TYPE_MPLASTVOLBREAKBEGTIMEB:
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x02;
        frame[pos ++] = 0x13;	
		break;
	case CON_DI_TYPE_MPLASTVOLBREAKBEGTIMEC:
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x03;
        frame[pos ++] = 0x13;	
		break;
 	
	case CON_DI_TYPE_MPLASTVOLBREAKENDTIMEA:	
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x25;
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x13;	
		break;
	case CON_DI_TYPE_MPLASTVOLBREAKENDTIMEB:
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x25;
        frame[pos ++] = 0x02;
        frame[pos ++] = 0x13;	
		break;
	case CON_DI_TYPE_MPLASTVOLBREAKENDTIMEC:
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x25;
        frame[pos ++] = 0x03;
        frame[pos ++] = 0x13;	
		break;
	case CON_DI_TYPE_MPPOWCONST:					//有功常数
		frame[pos ++] = 0x09;
		frame[pos ++] = 0x04;
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x04;	
		break;
	case CON_DI_TYPE_MPVARCONST:					//无功常数
		frame[pos ++] = 0x0A;
		frame[pos ++] = 0x04;
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x04;	
		break;
	case CON_DI_TYPE_MPDATEANDWEEK:						//日期及周次
		frame[pos ++] = 0x01;
		frame[pos ++] = 0x01;
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x04;
		break;
	case CON_DI_TYPE_MPTIME:							//时间
		frame[pos ++] = 0x02;
		frame[pos ++] = 0x01;
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x04;
		break;
	case CON_DI_TYPE_MPMETERSTATFLAG:					//电表运行状态字(大块)
		frame[pos ++] = 0x01;
		frame[pos ++] = 0x05;
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x04;
		break;
	case CON_DI_TYPE_MPCOPYDAYTIME:						//抄表日
		frame[pos ++] = 0x01;
		frame[pos ++] = 0x0B;
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x04;
		break;
	case CON_DI_TYPE_MPFEERATE_BLOCK:					//费率
		break;

	case CON_DI_TYPE_CU_LOST:
	case CON_DI_TYPE_FE_LOST:
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x85 + (data_id - CON_DI_TYPE_CU_LOST);
		frame[pos ++] = 0x00;
		break;

	case CON_DI_TYPE_DIRPOW_A:
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x15;
		frame[pos ++] = 0x00;
		break;

	case CON_DI_TYPE_UNDIRPOW_A:
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x16;
		frame[pos ++] = 0x00;
		break;

	case CON_DI_TYPE_SUMVAR1_A:
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x17;
		frame[pos ++] = 0x00;
		break;

	case CON_DI_TYPE_SUMVAR2_A:
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x18;
		frame[pos ++] = 0x00;
		break;

	case CON_DI_TYPE_DIRPOW_B:
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x29;
		frame[pos ++] = 0x00;
		break;

	case CON_DI_TYPE_UNDIRPOW_B:
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x2A;
		frame[pos ++] = 0x00;
		break;

	case CON_DI_TYPE_SUMVAR1_B:
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x2B;
		frame[pos ++] = 0x00;
		break;

	case CON_DI_TYPE_SUMVAR2_B:
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x2C;
		frame[pos ++] = 0x00;
		break;
		
	case CON_DI_TYPE_DIRPOW_C:
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x3D;
		frame[pos ++] = 0x00;
		break;

	case CON_DI_TYPE_UNDIRPOW_C:
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x3E;
		frame[pos ++] = 0x00;
		break;

	case CON_DI_TYPE_SUMVAR1_C:
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x3F;
		frame[pos ++] = 0x00;
		break;

	case CON_DI_TYPE_SUMVAR2_C:
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x40;
		frame[pos ++] = 0x00;
		break;
		
/************************************************************************/
    case CON_DI_TYPE_CU_LOST_LM:
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x85;
		frame[pos ++] = 0x00;
        break;
    case CON_DI_TYPE_FE_LOST_LM:
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x86;
        frame[pos ++] = 0x00;
        break;
    case CON_DI_TYPE_DIRPOW_A_LM:
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x15;
        frame[pos ++] = 0x00;
        break;

    case CON_DI_TYPE_UNDIRPOW_A_LM:
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x16;
        frame[pos ++] = 0x00;
        break;
    case CON_DI_TYPE_SUMVAR1_A_LM:
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x19;
        frame[pos ++] = 0x00;
        break;
    case CON_DI_TYPE_SUMVAR2_A_LM:
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x1A;
        frame[pos ++] = 0x00;
        break;        
    case CON_DI_TYPE_DIRPOW_B_LM:
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x29;
        frame[pos ++] = 0x00;
        break;
    case CON_DI_TYPE_UNDIRPOW_B_LM:
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x2A;
        frame[pos ++] = 0x00;
        break;
    case CON_DI_TYPE_SUMVAR1_B_LM:
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x2D;
        frame[pos ++] = 0x00;
        break;
    case CON_DI_TYPE_SUMVAR2_B_LM:
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x2E;
        frame[pos ++] = 0x00;
        break;
    case CON_DI_TYPE_DIRPOW_C_LM:
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x3D;
        frame[pos ++] = 0x00;
        break;
    case CON_DI_TYPE_UNDIRPOW_C_LM:
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x3E;
        frame[pos ++] = 0x00;
        break;
    case CON_DI_TYPE_SUMVAR1_C_LM:
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x41;
        frame[pos ++] = 0x00;
        break;
    case CON_DI_TYPE_SUMVAR2_C_LM:
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x42;
        frame[pos ++] = 0x00;
        break;

	case CON_DI_TYPE_MPDIRPOW_LM_BLOCK:
		frame[pos ++] = 0x01;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x01;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPUNDIRPOW_LM_BLOCK:
		frame[pos ++] = 0x01;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x02;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPDIRVAR_LM_BLOCK:
		frame[pos ++] = 0x01;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x03;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPUNDIRVAR_LM_BLOCK:
		frame[pos ++] = 0x01;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x04;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPVAR1_LM_BLOCK:		//一象限无功电能数据块(上月)
		frame[pos ++] = 0x01;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x05;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPVAR2_LM_BLOCK:		//二象限无功电能数据块(上月)
		frame[pos ++] = 0x01;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x06;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPVAR3_LM_BLOCK:		//三象限无功电能数据块(上月)
		frame[pos ++] = 0x01;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x07;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPVAR4_LM_BLOCK:		//四象限无功电能数据块(上月)
		frame[pos ++] = 0x01;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x08;
		frame[pos ++] = 0x00;	
		break;
	case CON_DI_TYPE_MPDIRPOWMAXDEMAND_LM_BLOCK:
	case CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_LM_BLOCK:
		frame[pos ++] = 0x01;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x01;
		frame[pos ++] = 0x01;	
		break;
	case CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_LM_BLOCK:
	case CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_LM_BLOCK:
		frame[pos ++] = 0x01;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x02;
		frame[pos ++] = 0x01;	
		break;
	case CON_DI_TYPE_MPDIRVARMAXDEMAND_LM_BLOCK:
	case CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_LM_BLOCK:
		frame[pos ++] = 0x01;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x03;
		frame[pos ++] = 0x01;	
		break;
	case CON_DI_TYPE_MPUNDIRVARMAXDEMAND_LM_BLOCK:
	case CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_LM_BLOCK:
		frame[pos ++] = 0x01;
		frame[pos ++] = 0xFF;
		frame[pos ++] = 0x04;
		frame[pos ++] = 0x01;	
		break;

	case CON_DI_TYPE_METER_STAT_FLAG_1:
	case CON_DI_TYPE_METER_STAT_FLAG_2:
	case CON_DI_TYPE_METER_STAT_FLAG_3:
	case CON_DI_TYPE_METER_STAT_FLAG_4:
	case CON_DI_TYPE_METER_STAT_FLAG_5:
	case CON_DI_TYPE_METER_STAT_FLAG_6:
	case CON_DI_TYPE_METER_STAT_FLAG_7:
		frame[pos ++] = 0x01 + (data_id - CON_DI_TYPE_METER_STAT_FLAG_1);
		frame[pos ++] = 0x05;
		frame[pos ++] = 0x00;
		frame[pos ++] = 0x04;
		break;
    case CON_DI_TYPE_METER_STAT_FLAG_BLOCK:
        frame[pos ++] = 0xff;
        frame[pos ++] = 0x05;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x04;
		break;
/************************************************************************/
        
    case CON_DI_TYPE_METER_OPEN_SWITCH:                   //（上1次）跳闸发生时刻
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x1d;
		break;
    case CON_DI_TYPE_METER_CLOSE_SWITCH:                  //（上1次）合闸发生时刻
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x1e;
		break;
    case CON_DI_TYPE_METER_REMAIN_MONEY:                 //（当前）剩余金额
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x02;
        frame[pos ++] = 0x90;
        frame[pos ++] = 0x00;
		break;
    case CON_DI_TYPE_METER_OVERDRAFT:                     //（当前）透支金额
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x02;
        frame[pos ++] = 0x90;
        frame[pos ++] = 0x00;
		break;
    case CON_DI_TYPE_METER_BUYPOW_TIMES_TOTAL:            //上1次购电后总购电次数
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x02;
        frame[pos ++] = 0x33;
        frame[pos ++] = 0x03;
		break;
    case CON_DI_TYPE_METER_BUYPOW_MENEY_TOTAL:            //上1次购电后累计购电金额
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x06;
        frame[pos ++] = 0x33;
        frame[pos ++] = 0x03;
		break;
    case CON_DI_TYPE_METER_HOUR_FREEZE_TIME:                //（上1次）整点冻结时间
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x04;
        frame[pos ++] = 0x05;
		break;
    case CON_DI_TYPE_METER_HOUR_FREEZE_DIRPOWTOL:           //（上1次）整点冻结正向有功总电能
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x04;
        frame[pos ++] = 0x05;
		break;
    case CON_DI_TYPE_METER_HOUR_FREEZE_REVPOWTOL:           //（上1次）整点冻结反向有功总电能
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x02;
        frame[pos ++] = 0x04;
        frame[pos ++] = 0x05;
		break;
    case CON_DI_TYPE_METER_HOUR_FREEZE_BLOCK:               //（上1次）整点冻结数据块
        frame[pos ++] = 0x01;
        frame[pos ++] = 0xff;
        frame[pos ++] = 0x04;
        frame[pos ++] = 0x05;
		break;
    case CON_DI_TYPE_METER_DAY_FREEZE_TIME:                 //（上1次）日冻结时间
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x06;
        frame[pos ++] = 0x05;
		break;
    case CON_DI_TYPE_METER_DAY_FREEZE_DIRPOW:                 //（上1次）日冻结正向有功电能数据
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x06;
        frame[pos ++] = 0x05;
		break;
    case CON_DI_TYPE_METER_DAY_FREEZE_REVPOW:                 //（上1次）日冻结反向有功电能数据
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x02;
        frame[pos ++] = 0x06;
        frame[pos ++] = 0x05;
		break;
    case CON_DI_TYPE_METER_DAY_FREEZE_DIRVAR:                 //（上1次）日冻结组合无功1电能数据
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x03;
        frame[pos ++] = 0x06;
        frame[pos ++] = 0x05;
		break;
    case CON_DI_TYPE_METER_DAY_FREEZE_REVVAR:                 //（上1次）日冻结组合无功2电能数据
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x04;
        frame[pos ++] = 0x06;
        frame[pos ++] = 0x05;
		break;
    case CON_DI_TYPE_METER_DAY_FREEZE_VAR1:                   //（上1次）日冻结第一象限无功电能数据
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x05;
        frame[pos ++] = 0x06;
        frame[pos ++] = 0x05;
		break;
    case CON_DI_TYPE_METER_DAY_FREEZE_VAR2:                 //（上1次）日冻结第二象限无功电能数据
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x06;
        frame[pos ++] = 0x06;
        frame[pos ++] = 0x05;
		break;
    case CON_DI_TYPE_METER_DAY_FREEZE_VAR3:                 //（上1次）日冻结第三象限无功电能数据
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x07;
        frame[pos ++] = 0x06;
        frame[pos ++] = 0x05;
		break;
    case CON_DI_TYPE_METER_DAY_FREEZE_VAR4:                 //（上1次）日冻结第四象限无功电能数据
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x08;
        frame[pos ++] = 0x06;
        frame[pos ++] = 0x05;
		break;
    case CON_DI_TYPE_METER_DAY_FREEZE_DIRPOWDEMAND:                 //（上1次）日冻结正向有功最大需量及发生时间数据：
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x09;
        frame[pos ++] = 0x06;
        frame[pos ++] = 0x05;
		break;
    case CON_DI_TYPE_METER_DAY_FREEZE_REVPOWDEMAND:                 //（上1次）日冻结反向有功最大需量及发生时间数据：
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x0a;
        frame[pos ++] = 0x06;
        frame[pos ++] = 0x05;
		break;
    case CON_DI_TYPE_METER_DAY_FREEZE_POWER:                 //（上1次）日冻结变量数据：功率
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x10;
        frame[pos ++] = 0x06;
        frame[pos ++] = 0x05;
		break;

    case CON_DI_TYPE_MPHARMONIC_VAL_VOLA_BLOCK:      //电压谐波有效值数据块
        frame[pos ++] = 0xff;
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x0c;
        frame[pos ++] = 0x02;
		break;
    case CON_DI_TYPE_MPHARMONIC_VAL_VOLB_BLOCK:      //电压谐波有效值数据块
        frame[pos ++] = 0xff;
        frame[pos ++] = 0x02;
        frame[pos ++] = 0x0c;
        frame[pos ++] = 0x02;
		break;
    case CON_DI_TYPE_MPHARMONIC_VAL_VOLC_BLOCK:      //电压谐波有效值数据块
        frame[pos ++] = 0xff;
        frame[pos ++] = 0x03;
        frame[pos ++] = 0x0c;
        frame[pos ++] = 0x02;
		break;
    case CON_DI_TYPE_MPHARMONIC_VAL_CURA_BLOCK:	//电流谐波有效值数据块
        frame[pos ++] = 0xff;
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x0d;
        frame[pos ++] = 0x02;
		break;
    case CON_DI_TYPE_MPHARMONIC_VAL_CURB_BLOCK	:      //电流谐波有效值数据块
        frame[pos ++] = 0xff;
        frame[pos ++] = 0x02;
        frame[pos ++] = 0x0d;
        frame[pos ++] = 0x02;
		break;
    case CON_DI_TYPE_MPHARMONIC_VAL_CURC_BLOCK:	//电流谐波有效值数据块
        frame[pos ++] = 0xff;
        frame[pos ++] = 0x03;
        frame[pos ++] = 0x0d;
        frame[pos ++] = 0x02;
		break;
    case CON_DI_TYPE_MPHARMONIC_RATE_VOLA_BLOCK:    //电压谐波含有率数据块
        frame[pos ++] = 0xff;
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x0a;
        frame[pos ++] = 0x02;
		break;
    case CON_DI_TYPE_MPHARMONIC_RATE_VOLB_BLOCK:    //电压谐波含有率数据块
        frame[pos ++] = 0xff;
        frame[pos ++] = 0x02;
        frame[pos ++] = 0x0a;
        frame[pos ++] = 0x02;
		break;
    case CON_DI_TYPE_MPHARMONIC_RATE_VOLC_BLOCK:    //电压谐波含有率数据块
        frame[pos ++] = 0xff;
        frame[pos ++] = 0x03;
        frame[pos ++] = 0x0a;
        frame[pos ++] = 0x02;
		break;
    case CON_DI_TYPE_MPHARMONIC_RATE_CURA_BLOCK:   //电流谐波含有率数据块
        frame[pos ++] = 0xff;
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x0b;
        frame[pos ++] = 0x02;
		break;
    case CON_DI_TYPE_MPHARMONIC_RATE_CURB_BLOCK:   //电流谐波含有率数据块
        frame[pos ++] = 0xff;
        frame[pos ++] = 0x02;
        frame[pos ++] = 0x0b;
        frame[pos ++] = 0x02;
		break;
    case CON_DI_TYPE_MPHARMONIC_RATE_CURC_BLOCK:   //电流谐波含有率数据块	
        frame[pos ++] = 0xff;
        frame[pos ++] = 0x03;
        frame[pos ++] = 0x0b;
        frame[pos ++] = 0x02;
		break;
		
	case CON_DI_TYPE_MPHARMONIC_VAL_CURA_TOL:      //电流谐波有效值数据块
	 frame[pos ++] = 0x00;
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x0d;
        frame[pos ++] = 0x02;
		break;
	case CON_DI_TYPE_MPHARMONIC_VAL_CURB_TOL:      //电流谐波有效值数据块
	 frame[pos ++] = 0x00;
        frame[pos ++] = 0x02;
        frame[pos ++] = 0x0d;
        frame[pos ++] = 0x02;
		break;
	case CON_DI_TYPE_MPHARMONIC_VAL_CURC_TOL:      //电流谐波有效值数据块
	 frame[pos ++] = 0x00;
        frame[pos ++] = 0x03;
        frame[pos ++] = 0x0d;
        frame[pos ++] = 0x02;
		break;
	case CON_DI_TYPE_MPHARMONIC_RATE_VOLA_TOL:      //电压谐波含有率数据块
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x08;
        frame[pos ++] = 0x02;
		break;	
	case CON_DI_TYPE_MPHARMONIC_RATE_VOLB_TOL:      //电压谐波含有率数据块
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x02;
        frame[pos ++] = 0x08;
        frame[pos ++] = 0x02;
		break;
	case CON_DI_TYPE_MPHARMONIC_RATE_VOLC_TOL:      //电压谐波含有率数据块
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x03;
        frame[pos ++] = 0x08;
        frame[pos ++] = 0x02;
		break;	
	case CON_DI_TYPE_MPHARMONIC_RATE_CURA_TOL:      //电压谐波含有率数据块
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x01;
        frame[pos ++] = 0x09;
        frame[pos ++] = 0x02;
		break;	
	case CON_DI_TYPE_MPHARMONIC_RATE_CURB_TOL:      //电压谐波含有率数据块
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x02;
        frame[pos ++] = 0x09;
        frame[pos ++] = 0x02;
		break;
	case CON_DI_TYPE_MPHARMONIC_RATE_CURC_TOL:      //电压谐波含有率数据块
        frame[pos ++] = 0x00;
        frame[pos ++] = 0x03;
        frame[pos ++] = 0x09;
        frame[pos ++] = 0x02;
		break;	
	case CON_DI_TYPE_MPPHS_ANGLE_VAL_ALL:
	 frame[pos ++] = 0x00;
        frame[pos ++] = 0xff;
        frame[pos ++] = 0xf1;
        frame[pos ++] = 0x02;
		break;
	case CON_DI_TYPE_MPPHS_ANGLE_I_ALL:
	 frame[pos ++] = 0x00;
        frame[pos ++] = 0xff;
        frame[pos ++] = 0xf2;
        frame[pos ++] = 0x02;
		break;
	default:
		break;
	}
	if(pos >= 4)
	{
		ret_di_07=frame[0]+0x100*frame[1]+0x10000*frame[2]+0x1000000*frame[3];
	}

	return ret_di_07;
}
//proto_flag = 91标识07

int inter_data_mng(unsigned short mpno, unsigned short data_id, unsigned char *recv_data, unsigned short recv_len, unsigned char proto_flag, unsigned char data_flag,unsigned char poweroff_flag)
{
	int ret = 0;
	int i = 0;
	unsigned long ulval = 0;
	//unsigned char data_val[200];
	//unsigned short group_id;
	unsigned short base_id,base_id0,base_id2;
	unsigned char tmp_val[18];
	struct data_his_day tmp_data_day;
	struct date_time_rec curr_time,rec_time;
	long ldata_time=0,lrec_time;
	struct  plc_rec_data_decompose tmp_data_decompose;
	unsigned char tmp_data_num;
	/*	group_id = (data_id & 0xFFF0) + 0x000F;*/
	unsigned short mpno_back=mpno;
	memset(&tmp_data_decompose,0x00,sizeof(tmp_data_decompose));
	switch(data_id)
	{
	case CON_DI_TYPE_MPDIRPOWTOTAL:
	case CON_DI_TYPE_MPUNDIRPOWTOTAL:
		ulval = bcd_to_u32(recv_data);
		memcpy(tmp_data_decompose.data_decompose_per[0].data,&ulval,4);
		tmp_data_decompose.data_decompose_per[0].data_id=data_id;
		tmp_data_decompose.data_id_num = 1;
		break;
	case CON_DI_TYPE_MPDIRPOW_BLOCK:
	case CON_DI_TYPE_MPUNDIRPOW_BLOCK:
	case CON_DI_TYPE_MPDIRPOW_LM_BLOCK:
	case CON_DI_TYPE_MPUNDIRPOW_LM_BLOCK:
	case CON_DI_TYPE_MPVAR1_BLOCK:
	case CON_DI_TYPE_MPVAR4_BLOCK:
	case CON_DI_TYPE_MPVAR2_BLOCK:
	case CON_DI_TYPE_MPVAR3_BLOCK:
	case CON_DI_TYPE_MPVAR1_LM_BLOCK:
	case CON_DI_TYPE_MPVAR4_LM_BLOCK:
	case CON_DI_TYPE_MPVAR2_LM_BLOCK:
	case CON_DI_TYPE_MPVAR3_LM_BLOCK:
		base_id = (data_id & 0xFFF0);
		tmp_data_num = recv_len / 4;
		if(tmp_data_num > 5)
			tmp_data_num = 5;
		for(i=0;i<tmp_data_num;i++)//目前先按固定4费率来算
		{
			ulval = bcd_to_u32(recv_data+4*i);
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		for(i=tmp_data_num;i<5;i++)
		{
			ulval = CON_INVALID_LONG_VAL;
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		tmp_data_decompose.data_id_num = 5;
		break;
	case CON_DI_TYPE_MPDIRVAR_BLOCK:
	case CON_DI_TYPE_MPUNDIRVAR_BLOCK:
	case CON_DI_TYPE_MPDIRVAR_LM_BLOCK:
	case CON_DI_TYPE_MPUNDIRVAR_LM_BLOCK:
		base_id = (data_id & 0xFFF0);
		tmp_data_num = recv_len / 4;
		if(tmp_data_num > 5)
			tmp_data_num = 5;
		for(i=0;i<tmp_data_num;i++)//目前先按固定4费率来算
		{
			*(recv_data+4*i+3)&=0x7f;         //去掉符号位
			ulval = bcd_to_u32(recv_data+4*i);
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		for(i=tmp_data_num;i<5;i++)
		{
			ulval = CON_INVALID_LONG_VAL;
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		tmp_data_decompose.data_id_num = 5;
		break;

	case CON_DI_TYPE_MPDIRPOWMAXDEMAND_BLOCK:
	case CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_BLOCK:
	case CON_DI_TYPE_MPDIRVARMAXDEMAND_BLOCK:
	case CON_DI_TYPE_MPUNDIRVARMAXDEMAND_BLOCK:
	case CON_DI_TYPE_MPDIRPOWMAXDEMAND_LM_BLOCK:
	case CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_LM_BLOCK:
	case CON_DI_TYPE_MPDIRVARMAXDEMAND_LM_BLOCK:
	case CON_DI_TYPE_MPUNDIRVARMAXDEMAND_LM_BLOCK:
		base_id = (data_id & 0xFFF0);
		tmp_data_num = recv_len / 8;
		if(tmp_data_num > 5)
			tmp_data_num = 5;
		for(i=0;i<tmp_data_num;i++)//目前先按固定4费率来算
		{
			ulval = bcd_to_u24(recv_data+8*i);
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		for(i=tmp_data_num;i<5;i++)
		{
			ulval = CON_INVALID_LONG_VAL;
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		tmp_data_decompose.data_id_num = 5;
		break;

	case CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_BLOCK:
	case CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_BLOCK:
	case CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_BLOCK:
	case CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_BLOCK:
	case CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_LM_BLOCK:
	case CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_LM_BLOCK:
	case CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_LM_BLOCK:
	case CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_LM_BLOCK:
		base_id = (data_id & 0xFFF0);
		tmp_data_num = recv_len / 8;
		if(tmp_data_num > 5)
			tmp_data_num = 5;	
		for(i=0;i<tmp_data_num;i++)//目前先按固定4费率来算
		{
			tmp_data_decompose.data_decompose_per[i].data[0] = bcd_to_u8(recv_data+8*i+3);	    //分
			tmp_data_decompose.data_decompose_per[i].data[1] = bcd_to_u8(recv_data+8*i+4);	//时
			tmp_data_decompose.data_decompose_per[i].data[2] = bcd_to_u8(recv_data+8*i+5);	//日
			tmp_data_decompose.data_decompose_per[i].data[3] = bcd_to_u8(recv_data+8*i+6);	//月
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		for(i=tmp_data_num;i<5;i++)
		{
			tmp_data_decompose.data_decompose_per[i].data[0] = 0xff;	    //分
			tmp_data_decompose.data_decompose_per[i].data[1] = 0xff;	//时
			tmp_data_decompose.data_decompose_per[i].data[2] = 0xff;	//日
			tmp_data_decompose.data_decompose_per[i].data[3] = 0xff;	//月
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		tmp_data_decompose.data_id_num = 5;
		break;

	case CON_DI_TYPE_MPDIRPOWMAXDEMAND_BIG_BLOCK:
	case CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_BIG_BLOCK:
	case CON_DI_TYPE_MPDIRVARMAXDEMAND_BIG_BLOCK:
	case CON_DI_TYPE_MPUNDIRVARMAXDEMAND_BIG_BLOCK:
		get_part_id_from_big_block(data_id, &base_id, &base_id0);
		tmp_data_num = recv_len / 8;
		if(tmp_data_num > 5)
			tmp_data_num = 5;	
		for(i=0;i<tmp_data_num;i++)//目前先按固定4费率来算
		{
			ulval = bcd_to_u24(recv_data+8*i);
			memcpy(tmp_data_decompose.data_decompose_per[2*i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[2*i].data_id=base_id +i;

			tmp_data_decompose.data_decompose_per[2*i+1].data[0] = bcd_to_u8(recv_data+8*i+3);	//分
			tmp_data_decompose.data_decompose_per[2*i+1].data[1] = bcd_to_u8(recv_data+8*i+4);	//时
			tmp_data_decompose.data_decompose_per[2*i+1].data[2] = bcd_to_u8(recv_data+8*i+5);	//日
			tmp_data_decompose.data_decompose_per[2*i+1].data[3] = bcd_to_u8(recv_data+8*i+6);	//月
			tmp_data_decompose.data_decompose_per[2*i+1].data_id=base_id0 +i;
		}
		for(i=tmp_data_num; i<5; i++)        //目前先按固定4费率来算
		{
			ulval = CON_INVALID_LONG_VAL;
			memcpy(tmp_data_decompose.data_decompose_per[2*i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[2*i].data_id=base_id +i;

			tmp_data_decompose.data_decompose_per[2*i+1].data[0] = 0xFF;	//分
			tmp_data_decompose.data_decompose_per[2*i+1].data[1] = 0xFF;	//时
			tmp_data_decompose.data_decompose_per[2*i+1].data[2] = 0xFF;	//日
			tmp_data_decompose.data_decompose_per[2*i+1].data[3] = 0xFF;	//月
			tmp_data_decompose.data_decompose_per[2*i+1].data_id=base_id0 +i;
		}
		tmp_data_decompose.data_id_num = 10;
		break;


	case CON_DI_TYPE_MPLATELYPROGTIME:	
	case CON_DI_TYPE_MPLATELYMAXDEMANDCLEARTIME:
	case CON_DI_TYPE_MPLATELYMETERCLEARTIME:	//最近一次电表清零发生时刻
	case CON_DI_TYPE_MPLATELYEVENTCLEARTIME:	//最近一次事件清零发生时刻
		tmp_data_decompose.data_decompose_per[0].data[0] = bcd_to_u8(recv_data);	       //秒
		tmp_data_decompose.data_decompose_per[0].data[1] = bcd_to_u8(recv_data+1);	//分
		tmp_data_decompose.data_decompose_per[0].data[2] = bcd_to_u8(recv_data+2);	//时
		tmp_data_decompose.data_decompose_per[0].data[3] = bcd_to_u8(recv_data+3);	//日
		tmp_data_decompose.data_decompose_per[0].data[4] = bcd_to_u8(recv_data+4);	//月
		tmp_data_decompose.data_decompose_per[0].data[5] = bcd_to_u8(recv_data+5);	//年
		tmp_data_decompose.data_decompose_per[0].data_id=data_id;
		tmp_data_decompose.data_id_num = 1;
		break;
	case CON_DI_TYPE_MPLATELYTIMINGTIME:		//最近一次校时发生时刻	
		tmp_data_decompose.data_decompose_per[0].data[0] = bcd_to_u8(recv_data+4);	       //秒
		tmp_data_decompose.data_decompose_per[0].data[1] = bcd_to_u8(recv_data+1+4);	//分
		tmp_data_decompose.data_decompose_per[0].data[2] = bcd_to_u8(recv_data+2+4);	//时
		tmp_data_decompose.data_decompose_per[0].data[3] = bcd_to_u8(recv_data+3+4);	//日
		tmp_data_decompose.data_decompose_per[0].data[4] = bcd_to_u8(recv_data+4+4);	//月
		tmp_data_decompose.data_decompose_per[0].data[5] = bcd_to_u8(recv_data+5+4);	//年
		tmp_data_decompose.data_decompose_per[0].data_id=data_id;
		tmp_data_decompose.data_id_num = 1;
		break;
	case CON_DI_TYPE_MPLASTVOLBREAKBEGTIME:
	case CON_DI_TYPE_MPLASTVOLBREAKBEGTIMEA:
	case CON_DI_TYPE_MPLASTVOLBREAKBEGTIMEB:
	case CON_DI_TYPE_MPLASTVOLBREAKBEGTIMEC:
	case CON_DI_TYPE_MPLASTVOLBREAKENDTIME:
	case CON_DI_TYPE_MPLASTVOLBREAKENDTIMEA:
	case CON_DI_TYPE_MPLASTVOLBREAKENDTIMEB:
	case CON_DI_TYPE_MPLASTVOLBREAKENDTIMEC:
//		tmp_data_decompose.data_decompose_per[0].data[0] = bcd_to_u8(recv_data);	       //秒
		tmp_data_decompose.data_decompose_per[0].data[0] = bcd_to_u8(recv_data+1);	//分
		tmp_data_decompose.data_decompose_per[0].data[1] = bcd_to_u8(recv_data+2);	//时
		tmp_data_decompose.data_decompose_per[0].data[2] = bcd_to_u8(recv_data+3);	//日
		tmp_data_decompose.data_decompose_per[0].data[3] = bcd_to_u8(recv_data+4);	//月
//		tmp_data_decompose.data_decompose_per[0].data[5] = bcd_to_u8(recv_data+5);	//年
		tmp_data_decompose.data_decompose_per[0].data_id=data_id;
		tmp_data_decompose.data_id_num = 1;
		break;

	case CON_DI_TYPE_MPPROGTIMETIMES:	
	case CON_DI_TYPE_MPMAXDEMANDCLEARTIMES:
	case CON_DI_TYPE_MPMETERCLEARTIMES:		//电表清零总次数
	case CON_DI_TYPE_MPEVENTCLEARTIMES	:	//事件清零总次数
	case CON_DI_TYPE_MPTIMINGTIMES:		//校时总次数
		ulval = bcd_to_u24(recv_data);
		memcpy(tmp_data_decompose.data_decompose_per[0].data,&ulval,4);
		tmp_data_decompose.data_decompose_per[0].data_id=data_id;
		tmp_data_decompose.data_id_num = 1;
		break;
	case CON_DI_TYPE_MPVOLBREAKNUMA:
	case CON_DI_TYPE_MPVOLBREAKNUMB:
	case CON_DI_TYPE_MPVOLBREAKNUMC:
	case CON_DI_TYPE_MPVOLBREAKTIMEA:
	case CON_DI_TYPE_MPVOLBREAKTIMEB:
	case CON_DI_TYPE_MPVOLBREAKTIMEC:
		ulval = bcd_to_u24(recv_data);
		memcpy(tmp_data_decompose.data_decompose_per[0].data,&ulval,4);
		tmp_data_decompose.data_decompose_per[0].data_id=data_id;
		tmp_data_decompose.data_id_num = 1;
		break;
	case CON_DI_TYPE_MPBATWORKTIME:
		ulval = bcd_to_u32(recv_data);
		memcpy(tmp_data_decompose.data_decompose_per[0].data,&ulval,4);
		tmp_data_decompose.data_decompose_per[0].data_id=data_id;
		tmp_data_decompose.data_id_num = 1;
		break;
	case CON_DI_TYPE_MPVOL_BLOCK:				//单位V 转换为 0.01V
		base_id = (data_id & 0xFFF1);

		tmp_data_num = recv_len / 2;
		if (tmp_data_num >3)
			tmp_data_num=3;

		for(i=0;i<tmp_data_num;i++)//
		{
			memcpy(tmp_val, recv_data+i+i, 2);
			if(tmp_val[0] == 0xFF && tmp_val[1] == 0xFF)
			{
				ulval = CON_INVALID_LONG_VAL;
			}
			else
			{
				ulval = bcd_to_u16(recv_data+2*i);
				if(proto_flag == 0x91)				//07规约
					ulval = ulval * 10;				
				else
					ulval = ulval * 100;
			}
			if(poweroff_flag == 1)
				ulval = 0;
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		for(i=tmp_data_num;i<3;i++)
		{
			ulval = CON_INVALID_LONG_VAL;
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		tmp_data_decompose.data_id_num=3;
		break;
	case CON_DI_TYPE_MPCUR_BLOCK:				//单位0.01A 转换为 0.0001A
		base_id = (data_id & 0xFFF1);

		if(proto_flag == 0x91)				//07规约
			tmp_data_num = recv_len / 3;
		else
			tmp_data_num = recv_len / 2;
		if (tmp_data_num >3)
			tmp_data_num=3;

		for(i=0;i<tmp_data_num;i++)//
		{
			if(proto_flag == 0x91)				//07规约
			{
				memcpy(tmp_val, recv_data+i+i+i, 3);
				if(tmp_val[0] == 0xFF && tmp_val[1] == 0xFF && tmp_val[2] == 0xFF)
				{
					ulval = CON_INVALID_LONG_VAL;
				}
				else
				{
					if((tmp_val[2] & 0x80) == 0x80)
					{
						tmp_val[2] -= 0x80;
						ulval = bcd_to_u24(tmp_val);
						ulval = ulval * 10;
						ulval = 0 - ulval;
					}
					else
					{
						ulval = bcd_to_u24(tmp_val);
						ulval = ulval * 10;
					}
				}
			}
			else
			{
				ulval = bcd_to_u16(recv_data+2*i);
				ulval = ulval * 100;
			}
			if(poweroff_flag == 1)
				ulval = 0;
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		for(i=tmp_data_num;i<3;i++)
		{
			ulval = CON_INVALID_LONG_VAL;
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		tmp_data_decompose.data_id_num=3;
		break;


	case CON_DI_TYPE_MPINSTANTPOW_BLOCK:
		base_id = (data_id & 0xFFF0);

		tmp_data_num = recv_len / 3;
		if (tmp_data_num >4)
			tmp_data_num=4;

		for(i=0;i<tmp_data_num;i++)//
		{
			memcpy(tmp_val, recv_data+i+i+i, 3);
			if(tmp_val[0] == 0xFF && tmp_val[1] == 0xFF && tmp_val[2] == 0xFF)
			{
				ulval = CON_INVALID_LONG_VAL;
			}
			else
			{
				if((tmp_val[2] & 0x80) == 0x80)
				{
					tmp_val[2] -= 0x80;
					ulval = bcd_to_u24(tmp_val);
					ulval = 0 - ulval;
				}
				else
				{
					ulval = bcd_to_u24(tmp_val);
				}
			}
			if(poweroff_flag == 1)
				ulval = 0;			
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		for(i=tmp_data_num;i<4;i++)
		{
			ulval = CON_INVALID_LONG_VAL;
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		tmp_data_decompose.data_id_num=4;
		break;

	case CON_DI_TYPE_MPINSTANTVAR_BLOCK:		//0.01kvar 转换为 0.0001kvar
		base_id = (data_id & 0xFFF0);

		if(proto_flag == 0x91)				//07规约
			tmp_data_num = recv_len / 3;
		else
			tmp_data_num = recv_len / 2;
		if (tmp_data_num >4)
			tmp_data_num=4;

		for(i=0;i<tmp_data_num;i++)//
		{
			if(proto_flag == 0x91)				//07规约
			{
				memcpy(tmp_val, recv_data+i+i+i, 3);
				if(tmp_val[0] == 0xFF && tmp_val[1] == 0xFF && tmp_val[2] == 0xFF)
				{
					ulval = CON_INVALID_LONG_VAL;
				}
				else
				{
					if((tmp_val[2] & 0x80) == 0x80)
					{
						tmp_val[2] -= 0x80;
						ulval = bcd_to_u24(tmp_val);
						ulval = 0 - ulval;
					}
					else
					{
						ulval = bcd_to_u24(tmp_val);
					}
				}
			}
			else
			{
				ulval = bcd_to_u16(recv_data+2*i);
				ulval = ulval * 100;
			}
			if(poweroff_flag == 1)
				ulval = 0;			
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		for(i=tmp_data_num;i<4;i++)
		{
			ulval = CON_INVALID_LONG_VAL;
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		tmp_data_decompose.data_id_num=4;
		break;

    case CON_DI_TYPE_MPPOWRATE_BLOCK:
        base_id = (data_id & 0xFFF0);
        tmp_data_num = recv_len / 2;
        if (tmp_data_num >4)
            tmp_data_num=4;
        for(i=0;i<tmp_data_num;i++)
        {
            tmp_data_decompose.data_decompose_per[i].data_id = base_id + i;
            memcpy(tmp_val, recv_data+2*i, 2);
			if(tmp_val[0] == 0xFF && tmp_val[1] == 0xFF)
			{
				ulval = CON_INVALID_LONG_VAL;
			}
			else
			{
				if((tmp_val[1] & 0x80) == 0x80)		//07规约功率因数增加负的处理
				{
					tmp_val[1] -= 0x80;
					ulval = bcd_to_u16(tmp_val);
					ulval = 0 - ulval;
				}
				else
				{
					ulval = bcd_to_u16(tmp_val);
				}
			}
            memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
        }

        for(i=tmp_data_num; i <4; i++)
        {
            tmp_data_decompose.data_decompose_per[i].data_id = base_id + i;
            ulval = CON_INVALID_LONG_VAL;
            memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
        }
        tmp_data_decompose.data_id_num=4;
        break;

	case CON_DI_TYPE_MPVOL_BLOCK_07 :       //单位V 转换为 0.01V
		base_id = (CON_DI_TYPE_MPVOL_BLOCK & 0xFFF1);
		tmp_data_num = recv_len / 2;
		if (tmp_data_num >3)
			tmp_data_num=3;
		for(i=0;i<tmp_data_num;i++)//
		{
			memcpy(tmp_val, recv_data+2*i, 2);
			if(tmp_val[0] == 0xFF && tmp_val[1] == 0xFF)
			{
				ulval = CON_INVALID_LONG_VAL;
			}
			else
			{
				ulval = bcd_to_u16(recv_data+2*i);
				ulval = ulval * 10;
			}
			if(poweroff_flag == 1)
				ulval = 0;			
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		for(i=tmp_data_num;i<3;i++)
		{
			ulval = CON_INVALID_LONG_VAL;
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		tmp_data_decompose.data_id_num=3;
		break;


	case CON_DI_TYPE_MPCUR_BLOCK_07 ://单位0.01A 转换为 0.0001A
		base_id = (CON_DI_TYPE_MPCUR_BLOCK & 0xFFF1);
		tmp_data_num = recv_len / 3;
		if (tmp_data_num >3)
			tmp_data_num=3;
		for(i=0;i<tmp_data_num;i++)//
		{
			memcpy(tmp_val, recv_data+3*i, 3);
			if(tmp_val[0] == 0xFF && tmp_val[1] == 0xFF && tmp_val[2] == 0xFF)
			{
				ulval = CON_INVALID_LONG_VAL;
			}
			else
			{
			ulval = bcd_to_u24(recv_data+3*i);
			ulval = ulval * 10;
			}
			if(poweroff_flag == 1)
			ulval = 0;		
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		for(i=tmp_data_num;i<3;i++)
		{
			ulval = CON_INVALID_LONG_VAL;
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		tmp_data_decompose.data_id_num=3;
		break;


	case CON_DI_TYPE_MPINSTANTPOW_BLOCK_07://0.0001KW
		base_id = (CON_DI_TYPE_MPINSTANTPOW_BLOCK & 0xFFF0);
		tmp_data_num = recv_len / 3;
		if (tmp_data_num >4)
			tmp_data_num=4;
		for(i=0;i<tmp_data_num;i++)//
		{
			memcpy(tmp_val, recv_data+3*i, 3);
			if(tmp_val[0] == 0xFF && tmp_val[1] == 0xFF && tmp_val[2] == 0xFF)
			{
				ulval = CON_INVALID_LONG_VAL;
			}
			else
			{
			ulval = bcd_to_u24(recv_data+3*i);
			}
			if(poweroff_flag == 1)
				ulval = 0;			
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		for(i=tmp_data_num;i<4;i++)//
		{
			ulval = CON_INVALID_LONG_VAL;
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		tmp_data_decompose.data_id_num=4;
		break;


	case CON_DI_TYPE_MPINSTANTVAR_BLOCK_07:
		base_id = (CON_DI_TYPE_MPINSTANTVAR_BLOCK & 0xFFF0);
		tmp_data_num = recv_len / 3;
		if (tmp_data_num >4)
			tmp_data_num=4;
		for(i=0;i<tmp_data_num;i++)//
		{
			memcpy(tmp_val, recv_data+3*i, 3);
			if(tmp_val[0] == 0xFF && tmp_val[1] == 0xFF && tmp_val[2] == 0xFF)
			{
				ulval = CON_INVALID_LONG_VAL;
			}
			else
			{
				ulval = bcd_to_u24(recv_data+3*i);
			}
			if(poweroff_flag == 1)
				ulval = 0;			
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		for(i=tmp_data_num;i<4;i++)
		{
			ulval = CON_INVALID_LONG_VAL;
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		tmp_data_decompose.data_id_num=4;
		break;

	case CON_DI_TYPE_MPPOWCONST:	
	case CON_DI_TYPE_MPVARCONST:
		ulval = bcd_to_u24(recv_data);
		memcpy(tmp_data_decompose.data_decompose_per[0].data,&ulval,4);
		tmp_data_decompose.data_decompose_per[0].data_id=data_id;
		tmp_data_decompose.data_id_num = 1;
		break;

	case CON_DI_TYPE_MPDATEANDWEEK:	
		tmp_data_decompose.data_decompose_per[0].data[0] = bcd_to_u8(recv_data+1);
		tmp_data_decompose.data_decompose_per[0].data[1] = bcd_to_u8(recv_data+2);
		tmp_data_decompose.data_decompose_per[0].data[2] = bcd_to_u8(recv_data+3);
		tmp_data_decompose.data_decompose_per[0].data[3] = 0x00;
		tmp_data_decompose.data_decompose_per[0].data_id=data_id;
		tmp_data_decompose.data_id_num = 1;
		break;

	case CON_DI_TYPE_MPTIME:
		tmp_data_decompose.data_decompose_per[0].data[0] = bcd_to_u8(recv_data+0);
		tmp_data_decompose.data_decompose_per[0].data[1] = bcd_to_u8(recv_data+1);
		tmp_data_decompose.data_decompose_per[0].data[2] = bcd_to_u8(recv_data+2);
		tmp_data_decompose.data_decompose_per[0].data[3] = 0x00;
		tmp_data_decompose.data_decompose_per[0].data_id=data_id;
		tmp_data_decompose.data_id_num = 1;
		break;

	case CON_DI_TYPE_MPMETERSTATFLAG: 	
	case CON_DI_TYPE_MPNETSTATFLAG:
		memcpy(tmp_data_decompose.data_decompose_per[0].data,recv_data,1);
		tmp_data_decompose.data_decompose_per[0].data_id=data_id;
		tmp_data_decompose.data_id_num = 1;
		break;

	case CON_DI_TYPE_MPCO2F_BLOCK:				//运行状态字
		memcpy(tmp_data_decompose.data_decompose_per[0].data,recv_data,2);
		tmp_data_decompose.data_decompose_per[0].data_id=data_id;
		tmp_data_decompose.data_id_num = 1;
		break;

	case CON_DI_TYPE_METER_STAT_FLAG_BLOCK:
		base_id = CON_DI_TYPE_METER_STAT_FLAG_1;
		for(i=0;i<7;i++)
		{
			memcpy(tmp_data_decompose.data_decompose_per[i].data,recv_data+2*i,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		tmp_data_decompose.data_id_num = 7;
		break;

	case CON_DI_TYPE_CU_LOST: 
	case CON_DI_TYPE_FE_LOST:
	case CON_DI_TYPE_CU_LOST_LM: 
	case CON_DI_TYPE_FE_LOST_LM:
	case CON_DI_TYPE_DIRPOW_A: 
	case CON_DI_TYPE_DIRPOW_B: 
	case CON_DI_TYPE_DIRPOW_C:
	case CON_DI_TYPE_UNDIRPOW_A:
	case CON_DI_TYPE_UNDIRPOW_B: 
	case CON_DI_TYPE_UNDIRPOW_C:
	case CON_DI_TYPE_SUMVAR1_A:
	case CON_DI_TYPE_SUMVAR1_B: 
	case CON_DI_TYPE_SUMVAR1_C:
	case CON_DI_TYPE_SUMVAR2_A:
	case CON_DI_TYPE_SUMVAR2_B: 
	case CON_DI_TYPE_SUMVAR2_C:
	case CON_DI_TYPE_DIRPOW_A_LM:
	case CON_DI_TYPE_DIRPOW_B_LM: 
	case CON_DI_TYPE_DIRPOW_C_LM:
	case CON_DI_TYPE_UNDIRPOW_A_LM:
	case CON_DI_TYPE_UNDIRPOW_B_LM:
	case CON_DI_TYPE_UNDIRPOW_C_LM:
	case CON_DI_TYPE_SUMVAR1_A_LM: 
	case CON_DI_TYPE_SUMVAR1_B_LM: 
	case CON_DI_TYPE_SUMVAR1_C_LM:
	case CON_DI_TYPE_SUMVAR2_A_LM: 
	case CON_DI_TYPE_SUMVAR2_B_LM: 
	case CON_DI_TYPE_SUMVAR2_C_LM:
		ulval = bcd_to_u32(recv_data);
		memcpy(tmp_data_decompose.data_decompose_per[0].data, &ulval, 4);
		tmp_data_decompose.data_decompose_per[0].data_id = data_id;
		tmp_data_decompose.data_id_num = 1;
		break;

	case CON_DI_TYPE_MPCOPYDAYTIME:				//抄表日等信息
		tmp_data_decompose.data_decompose_per[0].data[0] = bcd_to_u8(recv_data);	//时
		tmp_data_decompose.data_decompose_per[0].data[1] = bcd_to_u8(recv_data+1);//日
		tmp_data_decompose.data_decompose_per[0].data_id = data_id;
		tmp_data_decompose.data_id_num = 1;
		break;
/************************************************************************/
//用实时数据存        
    case CON_DI_TYPE_METER_OPEN_SWITCH:                   //（上1次）跳闸发生时刻
    case CON_DI_TYPE_METER_CLOSE_SWITCH:                  //（上1次）合闸发生时刻
        tmp_data_decompose.data_decompose_per[0].data[0] = bcd_to_u8(recv_data+5);	//时
        tmp_data_decompose.data_decompose_per[0].data[1] = bcd_to_u8(recv_data+4);//日
        tmp_data_decompose.data_decompose_per[0].data[2] = bcd_to_u8(recv_data+3);//日
        tmp_data_decompose.data_decompose_per[0].data[3] = bcd_to_u8(recv_data+2);//日
        tmp_data_decompose.data_decompose_per[0].data[4] = bcd_to_u8(recv_data+1);//日
        tmp_data_decompose.data_decompose_per[0].data[5] = bcd_to_u8(recv_data);//日
        tmp_data_decompose.data_decompose_per[0].data_id = data_id;
		tmp_data_decompose.data_id_num = 1;
		break;

    case CON_DI_TYPE_METER_REMAIN_MONEY:                 //（当前）剩余金额
    case CON_DI_TYPE_METER_OVERDRAFT:                     //（当前）透支金额
    case CON_DI_TYPE_METER_BUYPOW_MENEY_TOTAL:            //上1次购电后累计购电金额
        ulval = bcd_to_u32(recv_data);
        memcpy(tmp_data_decompose.data_decompose_per[0].data,&ulval,4);
        tmp_data_decompose.data_decompose_per[0].data_id=data_id;
        tmp_data_decompose.data_id_num = 1;
		break;
    case CON_DI_TYPE_METER_BUYPOW_TIMES_TOTAL:            //上1次购电后总购电次数
        ulval = bcd_to_u16(recv_data);
        memcpy(tmp_data_decompose.data_decompose_per[0].data,&ulval,4);
        tmp_data_decompose.data_decompose_per[0].data_id=data_id;
        tmp_data_decompose.data_id_num = 1;
		break;
    case CON_DI_TYPE_MPHARMONIC_VAL_VOLA_BLOCK:     //电压谐波有效值数据块
    case CON_DI_TYPE_MPHARMONIC_VAL_VOLB_BLOCK:      //电压谐波有效值数据块
    case CON_DI_TYPE_MPHARMONIC_VAL_VOLC_BLOCK:      //电压谐波有效值数据块
		mpno_back=0;//谐波测量点强制为零
		base_id = (data_id -0x16);
		for(i=0;i<20;i++)//目前先按固定4费率来算
		{
			ulval = bcd_to_u16(recv_data+2*i);	//xxx.x -> xxx.x
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		tmp_data_decompose.data_id_num = 20;
		break;
    case CON_DI_TYPE_MPHARMONIC_VAL_CURA_BLOCK:	    //电流谐波有效值数据块
    case CON_DI_TYPE_MPHARMONIC_VAL_CURB_BLOCK:	    //电流谐波有效值数据块
    case CON_DI_TYPE_MPHARMONIC_VAL_CURC_BLOCK:	    //电流谐波有效值数据块
       mpno_back=0;//谐波测量点强制为零
	base_id = (data_id -0x16);
	for(i=0;i<20;i++)//目前先按固定4费率来算
	{
			ulval = bcd_to_u24(recv_data+3*i);
			ulval = ulval/10;						//xxx.xxx -> xx.xx
		memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
		tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
	}
	tmp_data_decompose.data_id_num = 20;
		break;
    case CON_DI_TYPE_MPHARMONIC_RATE_VOLA_BLOCK:    //电压谐波含有率数据块
    case CON_DI_TYPE_MPHARMONIC_RATE_VOLB_BLOCK:    //电压谐波含有率数据块
    case CON_DI_TYPE_MPHARMONIC_RATE_VOLC_BLOCK:    //电压谐波含有率数据块
    case CON_DI_TYPE_MPHARMONIC_RATE_CURA_BLOCK:   //电流谐波含有率数据块
    case CON_DI_TYPE_MPHARMONIC_RATE_CURB_BLOCK:   //电流谐波含有率数据块
    case CON_DI_TYPE_MPHARMONIC_RATE_CURC_BLOCK:   //电流谐波含有率数据块
       mpno_back=0;//谐波测量点强制为零
	base_id = (data_id -0x16);
	for(i=1;i<20;i++)//目前先按固定4费率来算
	{
	       ulval = bcd_to_u16(recv_data+2*(i-1));
		   ulval = ulval/10;						//xx.xx%  ->  xxx.x%
		memcpy(tmp_data_decompose.data_decompose_per[i-1].data,&ulval,4);
		tmp_data_decompose.data_decompose_per[i-1].data_id=base_id +i;
	}
	tmp_data_decompose.data_id_num = 19;
		break;

    case CON_DI_TYPE_MPHARMONIC_RATE_VOLA_TOL:      //电压谐波含有率数据块
    case CON_DI_TYPE_MPHARMONIC_RATE_VOLB_TOL:      //电压谐波含有率数据块
    case CON_DI_TYPE_MPHARMONIC_RATE_VOLC_TOL:      //电压谐波含有率数据块
    case CON_DI_TYPE_MPHARMONIC_RATE_CURA_TOL:      //电压谐波含有率数据块
    case CON_DI_TYPE_MPHARMONIC_RATE_CURB_TOL:      //电压谐波含有率数据块
    case CON_DI_TYPE_MPHARMONIC_RATE_CURC_TOL:      //电压谐波含有率数据块
       mpno_back=0;//谐波测量点强制为零
       ulval = bcd_to_u16(recv_data);
	   ulval = ulval/10;							//xx.xx%  ->  xxx.x%
	memcpy(tmp_data_decompose.data_decompose_per[0].data,&ulval,4);
	tmp_data_decompose.data_decompose_per[0].data_id=data_id ;
	tmp_data_decompose.data_id_num = 1;
		break;

	case CON_DI_TYPE_MPPHS_ANGLE_VAL_ALL:
	case CON_DI_TYPE_MPPHS_ANGLE_I_ALL:		
		if(data_id == CON_DI_TYPE_MPPHS_ANGLE_VAL_ALL)
			base_id=CON_DI_TYPE_TER_PHASE_UA;
		else 
			base_id=CON_DI_TYPE_TER_PHASE_IA;
			
		tmp_data_num = recv_len / 2;
		if(tmp_data_num > 3)
			tmp_data_num = 3;
		for(i=0;i<tmp_data_num;i++)//目前先按固定4费率来算
		{
			ulval=0;
			memcpy(&ulval,recv_data+2*i,2);
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		for(i=tmp_data_num;i<3;i++)
		{
			ulval = CON_INVALID_LONG_VAL;
			memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
			tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
		}
		tmp_data_decompose.data_id_num = 3;
		break;
		
/************************************************************************/

/************************************************************************/
//用曲线数据存，整点冻结采用块抄考虑到时间问题
//     case CON_DI_TYPE_METER_HOUR_FREEZE_TIME:                //（上1次）整点冻结时间
// 
// 		break;
//     case CON_DI_TYPE_METER_HOUR_FREEZE_DIRPOWTOL:           //（上1次）整点冻结正向有功总电能
// 
// 		break;
//     case CON_DI_TYPE_METER_HOUR_FREEZE_REVPOWTOL:           //（上1次）整点冻结反向有功总电能
// 
// 		break;
    case CON_DI_TYPE_METER_HOUR_FREEZE_BLOCK:               //（上1次）整点冻结数据块按曲线存
        //获取时间
        rec_time.year = bcd_to_u8(recv_data+4)+2000;	//时
        rec_time.month = bcd_to_u8(recv_data+3);   //日
        rec_time.day = bcd_to_u8(recv_data+2);   //日
        rec_time.hour = bcd_to_u8(recv_data+1);   //日
        rec_time.minute = 0;     //归整，主要是考虑采集器抄97的表的问题
        rec_time.second = 0;

#ifdef PLC_MNG_DEBUG
		log_printf_level(LOG_LEVEL_DEBUG, DBGFMT_A"save hour freeze mp%d %04d-%02d-%02d %02d:%02d:%02d %04X\n",DBGARG_A, mpno, 
            rec_time.year,rec_time.month,rec_time.day,rec_time.hour,rec_time.minute,rec_time.second, CON_DI_TYPE_METER_HOUR_FREEZE_BLOCK);
#endif
        
        ulval = bcd_to_u32(recv_data+6); //中间有分割符
#ifdef PLC_MNG_DEBUG
        log_printf_level(LOG_LEVEL_DEBUG, DBGFMT_A"save hour freeze mp %d %x %04X \n",DBGARG_A, mpno, 
            ulval, CON_DI_TYPE_MPDIRPOWTOTAL);
#endif
        ret = save_mp_his_curve_data_by_mpno(mpno, CON_DI_TYPE_MPDIRPOWTOTAL, &ulval, &rec_time);
        if (!ret)
        {
            ulval = bcd_to_u32(recv_data+11); //中间有分割符
#ifdef PLC_MNG_DEBUG
            log_printf_level(LOG_LEVEL_DEBUG, DBGFMT_A"save hour freeze mp %d %x %04X \n",DBGARG_A, mpno, 
                ulval, CON_DI_TYPE_MPUNDIRPOWTOTAL);
#endif
            ret = save_mp_his_curve_data_by_mpno(mpno, CON_DI_TYPE_MPUNDIRPOWTOTAL, &ulval, &rec_time);
            if (!ret)
                return ret;
        }
		break;
/************************************************************************/
    case CON_DI_TYPE_METER_DAY_FREEZE_TIME:                 //（上1次）日冻结时间
 //       int save_mp_his_day_data_by_mpno(int mpno, unsigned short data_id, struct date_time_rec *std_time, unsigned long *puldata_val, struct date_time_rec *rec_time)

		break;
    case CON_DI_TYPE_METER_DAY_FREEZE_DIRPOW:               //（上1次）日冻结正向有功电能数据
    case CON_DI_TYPE_METER_DAY_FREEZE_REVPOW:               //（上1次）日冻结反向有功电能数据
    case CON_DI_TYPE_METER_DAY_FREEZE_DIRVAR:               //（上1次）日冻结组合无功1电能数据
    case CON_DI_TYPE_METER_DAY_FREEZE_REVVAR:               //（上1次）日冻结组合无功2电能数据
    case CON_DI_TYPE_METER_DAY_FREEZE_VAR1:                 //（上1次）日冻结第一象限无功电能数据
    case CON_DI_TYPE_METER_DAY_FREEZE_VAR2:                 //（上1次）日冻结第二象限无功电能数据
    case CON_DI_TYPE_METER_DAY_FREEZE_VAR3:                 //（上1次）日冻结第三象限无功电能数据
    case CON_DI_TYPE_METER_DAY_FREEZE_VAR4:                 //（上1次）日冻结第四象限无功电能数据
#if(CONFIG_METER_FACTORY_MODE_ENABLE == CONFIG_METER_FACTORY_MODE)
	return 0;
#else	
        curr_time = get_current_time();
        if (((curr_time.hour >0) || (curr_time.minute >5)) &&
            ((curr_time.hour < 23) || (curr_time.minute <45)))
        {
//            set_day_di_flag(mpno,data_id);
			log_printf_level(LOG_LEVEL_INFO, "\ntime %04d-%02d-%02d %02d:%02d:%02d\n" ,curr_time.year,
                curr_time.month,curr_time.day,curr_time.hour,curr_time.minute,curr_time.second);
            get_baseid_from_daydataid(&base_id,&data_id);
            base_id = (base_id & 0xFFF0);

			tmp_data_num = recv_len / 4;
			if (tmp_data_num >5)
				tmp_data_num=5;
			for(i=0;i<tmp_data_num;i++)//
            {
                ulval = bcd_to_u32(recv_data+4*i);
                memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
                tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
            }
			for(i=tmp_data_num;i<5;i++)
			{
				ulval = CON_INVALID_LONG_VAL;
				memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
				tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
			}

            lrec_time = timerec_to_long(&curr_time);
            curr_time.hour =0;
            curr_time.minute=0;
            curr_time.second=0;
#ifdef CON_TER_TYPE_JC_TJ		//
            lrec_time = timerec_to_long(&curr_time);
#endif
            ldata_time = timerec_to_long(&curr_time);
#ifdef CON_TER_TYPE_JC_CQ		//集中器重庆	重庆要求日冻结数据为上上日的数据，21011123后理解为不减一天，改为日冻结抄读作为日初数据
           if(g_app_etc_cfg_cq_job_up_last_last == CON_STATUS_YES)
	            ldata_time -= 86400;
#else
			ldata_time -= 86400;
#endif
#ifdef PLC_MNG_DEBUG
			struct date_time_rec time_tmp=time_long_to_timerec(ldata_time);
			struct date_time_rec rec_time_test;
			long data_val_tmp;
			//log_printf_level(LOG_LEVEL_DEBUG, "\nday %04d-%02d-%02d %02d:%02d:%02d\n" ,time_tmp.year,
			//			time_tmp.month,time_tmp.day,time_tmp.hour,time_tmp.minute,time_tmp.second);
#endif
            for (i=0;i<5;i++)
            {
                tmp_data_day.reg_time = ldata_time;
                tmp_data_day.mp_no = mpno;
                tmp_data_day.di = tmp_data_decompose.data_decompose_per[i].data_id;
                memset(tmp_data_day.data,0x00,8);

/************************************************************************/
                if(data_flag == 1)						//数据有效
                {
                    memcpy(tmp_data_day.data,tmp_data_decompose.data_decompose_per[i].data,8);
                    tmp_data_day.rec_time = lrec_time;
                    ret = db_sd_dhd_write_one_data(&tmp_data_day);
   
#ifdef PLC_MNG_DEBUG
                    log_printf_level(LOG_LEVEL_DEBUG, DBGFMT_A"mp%d %02X%02X%02X%02X %04X\n",DBGARG_A, mpno, 
                        tmp_data_decompose.data_decompose_per[i].data[3], tmp_data_decompose.data_decompose_per[i].data[2], 
                        tmp_data_decompose.data_decompose_per[i].data[1], tmp_data_decompose.data_decompose_per[i].data[0], tmp_data_day.di);
#endif
                }
                else
                {
                    unsigned long err_data;
                    err_data = CON_INVALID_LONG_VAL;
                    memcpy(tmp_data_day.data, &err_data, 4);
                    tmp_data_day.rec_time = lrec_time;
				    ret = db_sd_dhd_write_one_data(&tmp_data_day);
#ifdef PLC_MNG_DEBUG
                    log_printf_level(LOG_LEVEL_DEBUG, DBGFMT_A"err mp %d %04X\n",DBGARG_A, mpno, tmp_data_day.di);
#endif
		        }
                
/************************************************************************/

#ifdef PLC_MNG_DEBUG
                //log_printf_level(LOG_LEVEL_DEBUG, DBGFMT_A"day mp%d %02X%02X%02X%02X %04X\n",DBGARG_A, mpno, 
                //    tmp_data_decompose.data_decompose_per[i].data[3], tmp_data_decompose.data_decompose_per[i].data[2], 
                //    tmp_data_decompose.data_decompose_per[i].data[1], tmp_data_decompose.data_decompose_per[i].data[0], tmp_data_day.di);
                
                //get_mp_his_day_data_by_mpno(mpno, tmp_data_day.di, &time_tmp, &data_val_tmp, &rec_time_test);

                    //log_printf_level(LOG_LEVEL_DEBUG, "\n get data save time= %d-%d-%d-%d-%d-%d ; val = %d ---------!!!!!!!\n" ,rec_time_test.year,
                    //rec_time_test.month,rec_time_test.day,rec_time_test.hour,rec_time_test.minute,rec_time_test.second
                    //,data_val_tmp);
#endif
            }
        }
        	return ret;
        log_printf_level(LOG_LEVEL_INFO, "\n ------------- program not return -----------------------!!!!!!!!!!!!!!\n");
#endif	//#if(CONFIG_METER_FACTORY_MODE_ENABLE == CONFIG_METER_FACTORY_MODE)	
		break;

    case CON_DI_TYPE_METER_DAY_FREEZE_DIRPOWDEMAND:         //（上1次）日冻结正向有功最大需量及发生时间数据：
    case CON_DI_TYPE_METER_DAY_FREEZE_REVPOWDEMAND:         //（上1次）日冻结反向有功最大需量及发生时间数据：
#if(CONFIG_METER_FACTORY_MODE_ENABLE == CONFIG_METER_FACTORY_MODE)    
return 0;
#else
        curr_time = get_current_time();
        if (((curr_time.hour >0) || (curr_time.minute >5)) &&
            ((curr_time.hour < 23) || (curr_time.minute <45)))
        {
            get_baseid_from_daydataid(&base_id2,&data_id);
            get_part_id_from_big_block(base_id2,&base_id, &base_id0);
            for(i=0; i<5; i++)        //目前先按固定4费率来算
            {
                ulval = bcd_to_u24(recv_data+8*i);
                memcpy(tmp_data_decompose.data_decompose_per[2*i].data,&ulval,4);
                tmp_data_decompose.data_decompose_per[2*i].data_id=base_id +i;
                
                tmp_data_decompose.data_decompose_per[2*i+1].data[0] = bcd_to_u8(recv_data+8*i+3);	//秒
                tmp_data_decompose.data_decompose_per[2*i+1].data[1] = bcd_to_u8(recv_data+8*i+4);	//分
                tmp_data_decompose.data_decompose_per[2*i+1].data[2] = bcd_to_u8(recv_data+8*i+5);	//时
                tmp_data_decompose.data_decompose_per[2*i+1].data[3] = bcd_to_u8(recv_data+8*i+6);	//日
                tmp_data_decompose.data_decompose_per[2*i+1].data[4] = bcd_to_u8(recv_data+8*i+7);	//月
                tmp_data_decompose.data_decompose_per[2*i+1].data_id=base_id0 +i;
            }
            lrec_time = timerec_to_long(&curr_time);
            curr_time.hour =0;
            curr_time.minute=0;
            curr_time.second=0;
            ldata_time = timerec_to_long(&curr_time);
#ifdef CON_TER_TYPE_JC_CQ		//集中器重庆	重庆要求日冻结数据为上上日的数据，21011123后理解为不减一天，改为日冻结抄读作为日初数据
			if(g_app_etc_cfg_cq_job_up_last_last == CON_STATUS_YES)
	            ldata_time -= 86400;
#else
			ldata_time -= 86400;
#endif
            for (i=0;i<10;i++)
            {
                tmp_data_day.reg_time = ldata_time;
                tmp_data_day.mp_no = mpno;
                tmp_data_day.di = tmp_data_decompose.data_decompose_per[i].data_id;
                memset(tmp_data_day.data,0x00,8);

/************************************************************************/
                if(data_flag == 1)						//数据有效
                {
                    memcpy(tmp_data_day.data,tmp_data_decompose.data_decompose_per[i].data,8);
                    tmp_data_day.rec_time = lrec_time;
                    ret = db_sd_dhd_write_one_data(&tmp_data_day);
       
#ifdef PLC_MNG_DEBUG
                    //log_printf_level(LOG_LEVEL_DEBUG, DBGFMT_A"mp%d %02X%02X%02X%02X %04X\n",DBGARG_A, mpno, 
                    //    tmp_data_decompose.data_decompose_per[i].data[3], tmp_data_decompose.data_decompose_per[i].data[2], 
                    //    tmp_data_decompose.data_decompose_per[i].data[1], tmp_data_decompose.data_decompose_per[i].data[0], tmp_data_day.di);
#endif
                }
                else
                {
                    unsigned long err_data;
                    err_data = CON_INVALID_LONG_VAL;
                    memcpy(tmp_data_day.data, &err_data, 4);
                    tmp_data_day.rec_time = lrec_time;
                   ret = db_sd_dhd_write_one_data(&tmp_data_day);
#ifdef PLC_MNG_DEBUG
                    log_printf_level(LOG_LEVEL_DEBUG, DBGFMT_A"err mp %d %04X\n",DBGARG_A, mpno, tmp_data_day.di);
#endif
                }
                
/************************************************************************/

#ifdef PLC_MNG_DEBUG
                //log_printf_level(LOG_LEVEL_DEBUG, DBGFMT_A"day mp%d %02X%02X%02X%02X %04X\n",DBGARG_A, mpno, 
                //    tmp_data_decompose.data_decompose_per[i].data[3], tmp_data_decompose.data_decompose_per[i].data[2], 
                //    tmp_data_decompose.data_decompose_per[i].data[1], tmp_data_decompose.data_decompose_per[i].data[0], tmp_data_day.di);
#endif
            }
        }
            return ret;
            log_printf_level(LOG_LEVEL_INFO, "\n ------------- program not return -----------------------!!!!!!!!!!!!!!\n");
#endif //#if(CONFIG_METER_FACTORY_MODE_ENABLE == CONFIG_METER_FACTORY_MODE)
        break;

    case CON_DI_TYPE_METER_DAY_FREEZE_POWER:                //（上1次）日冻结变量数据：功率
#if(CONFIG_METER_FACTORY_MODE_ENABLE == CONFIG_METER_FACTORY_MODE)
return 0;
#else
//         struct data_his_day tmp_data_day;
//         struct date_time_rec curr_time;
        curr_time = get_current_time();
/*        long ldata_time=0,lrec_time;*/
        if ((curr_time.hour >0) || (curr_time.minute >15))
        {
            base_id = (CON_DI_TYPE_MPINSTANTPOW_BLOCK & 0xFFF0);
            for(i=0; i<4; i++)//
            {
                ulval = bcd_to_u24(recv_data+3*i);
                memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
                tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
            }
            base_id = (CON_DI_TYPE_MPINSTANTVAR_BLOCK & 0xFFF0);
            for(i=4;i<8; i++)
            {
                ulval = bcd_to_u24(recv_data+3*i);
                memcpy(tmp_data_decompose.data_decompose_per[i].data,&ulval,4);
                tmp_data_decompose.data_decompose_per[i].data_id=base_id +i;
            }
		    tmp_data_decompose.data_id_num=i;

            lrec_time = timerec_to_long(&curr_time);
            curr_time.hour =0;
            curr_time.minute=0;
            curr_time.second=0;
            ldata_time = timerec_to_long(&curr_time);
#ifdef CON_TER_TYPE_JC_CQ		//集中器重庆	重庆要求日冻结数据为上上日的数据，21011123后理解为不减一天，改为日冻结抄读作为日初数据
			if(g_app_etc_cfg_cq_job_up_last_last == CON_STATUS_YES)
	            ldata_time -= 86400;
#else
			ldata_time -= 86400;
#endif
            for (i=0;i<8;i++)
            {
                tmp_data_day.reg_time = ldata_time;
                tmp_data_day.mp_no = mpno;
                tmp_data_day.di = tmp_data_decompose.data_decompose_per[i].data_id;
                memset(tmp_data_day.data,0x00,8);

/************************************************************************/
                if(data_flag == 1)						//数据有效
                {
                    memcpy(tmp_data_day.data,tmp_data_decompose.data_decompose_per[i].data,8);
                    tmp_data_day.rec_time = lrec_time;
                    ret = db_sd_dhd_write_one_data(&tmp_data_day);
 
#ifdef PLC_MNG_DEBUG
                    //log_printf_level(LOG_LEVEL_DEBUG, DBGFMT_A"mp%d %02X%02X%02X%02X %04X\n",DBGARG_A, mpno, 
                    //    tmp_data_decompose.data_decompose_per[i].data[3], tmp_data_decompose.data_decompose_per[i].data[2], 
                    //    tmp_data_decompose.data_decompose_per[i].data[1], tmp_data_decompose.data_decompose_per[i].data[0], tmp_data_day.di);
#endif
                }
                else
                {
                    unsigned long err_data;
                    err_data = CON_INVALID_LONG_VAL;
                    memcpy(tmp_data_day.data, &err_data, 4);
                    tmp_data_day.rec_time = lrec_time;
                    ret = db_sd_dhd_write_one_data(&tmp_data_day);
#ifdef PLC_MNG_DEBUG
                    log_printf_level(LOG_LEVEL_DEBUG, DBGFMT_A"err mp %d %04X\n",DBGARG_A, mpno, tmp_data_day.di);
#endif
                }
                
/************************************************************************/
            }
        }
        return ret;
#endif //#if(CONFIG_METER_FACTORY_MODE_ENABLE == CONFIG_METER_FACTORY_MODE)
		break;

	default:
		if (recv_len >8)
			recv_len=8;
		memcpy(tmp_data_decompose.data_decompose_per[0].data, recv_data, recv_len);
		tmp_data_decompose.data_decompose_per[0].data_id = data_id;
		tmp_data_decompose.data_id_num = 1;
		break;
	}
	for(i=0;i<tmp_data_decompose.data_id_num;i++)
	{
		struct data_rt tmp_data_rt;
/*		struct date_time_rec curr_time;*/
		curr_time = get_current_time();
		tmp_data_rt.mp_no = mpno_back;
		tmp_data_rt.rec_time = timerec_to_long(&curr_time);

		tmp_data_rt.di = tmp_data_decompose.data_decompose_per[i].data_id;
		memset(tmp_data_rt.data, 0x00, 8);
		if(data_flag == 1)						//数据有效
		{
			memcpy(tmp_data_rt.data, tmp_data_decompose.data_decompose_per[i].data, 8);
			db_sd_drt_write_data_shm(&tmp_data_rt);
#ifdef PLC_MNG_DEBUG
			log_printf_level(LOG_LEVEL_DEBUG, DBGFMT_A"mp%d %02X%02X%02X%02X %04X\n",DBGARG_A, mpno, 
				tmp_data_decompose.data_decompose_per[i].data[3], tmp_data_decompose.data_decompose_per[i].data[2], 
				tmp_data_decompose.data_decompose_per[i].data[1], tmp_data_decompose.data_decompose_per[i].data[0], tmp_data_rt.di);
#endif
		}
		else
		{
			unsigned long err_data;
			err_data = CON_INVALID_LONG_VAL;
			memcpy(tmp_data_rt.data, &err_data, 4);
			db_sd_drt_write_data_shm(&tmp_data_rt);
#ifdef PLC_MNG_DEBUG
			log_printf_level(LOG_LEVEL_DEBUG, DBGFMT_A"err mp %d %04X\n",DBGARG_A, mpno, tmp_data_rt.di);
#endif
		}
	}

	return ret;
}
/*==================================================================
//函数名：  rtc_get_time
//作者：    
//日期：    
//功能：    获取rtc时间
//输入参数：无
//输出参数：无
//返回值：  date_time_rec类型结构体
//=================================================================*/
struct date_time_rec rtc_get_time(void)
{
	struct date_time_rec ret_time;
	int ret = -1;

	ret = rtc_get(&ret_time);
	if(ret != 0)
	{
		ret_time.year = 2000;
		ret_time.month = 1;
		ret_time.day = 1;
		ret_time.hour = 0;
		ret_time.minute = 0;
		ret_time.second = 0;
	}
	return ret_time;
}

/*==================================================================
//函数名：  get_current_time
//作者：    
//日期：    
//功能：    获取当前时间
//输入参数：无
//输出参数：无
//返回值：  date_time_rec类型结构体
//=================================================================*/
struct date_time_rec get_current_time(void)
{
	time_t tmp_time;
	struct tm *ptr_time;
	struct date_time_rec ret_time;

	tmp_time = time(0);
	if(tmp_time < 0)
	{
		ret_time = rtc_get_time();
	}
	else
	{
		ptr_time = localtime(&tmp_time);
		ret_time.year = ptr_time->tm_year + 1900;
		ret_time.month = ptr_time->tm_mon + 1;
		ret_time.day = ptr_time->tm_mday;
		ret_time.hour = ptr_time->tm_hour;
		ret_time.minute = ptr_time->tm_min;
		ret_time.second = ptr_time->tm_sec;
	}
	return ret_time;
}

/*==================================================================
//函数名：  get_part_id_from_big_block
//作者：    liuchiqi
//日期：    2011-1-23
//功能：    针对07需量
//输入参数：从大项数据中读取部分项
//输出参数：无
//返回值：  无
//=================================================================*/
void get_part_id_from_big_block(unsigned short data_id , unsigned short * pbase_id,unsigned short *pbase_id0)
{
    switch(data_id)
    {
    case CON_DI_TYPE_MPDIRPOWMAXDEMAND_BIG_BLOCK:
        * pbase_id = CON_DI_TYPE_MPDIRPOWMAXDEMAND;
        * pbase_id0 = CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME;
        break;
        
    case CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_BIG_BLOCK:
        * pbase_id = CON_DI_TYPE_MPUNDIRPOWMAXDEMAND;
        * pbase_id0 = CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME;
        break;
        
    case CON_DI_TYPE_MPDIRVARMAXDEMAND_BIG_BLOCK:
        * pbase_id = CON_DI_TYPE_MPDIRVARMAXDEMAND;
        * pbase_id0 = CON_DI_TYPE_MPDIRVARMAXDEMANDTIME;
        break;
        
 	case CON_DI_TYPE_MPUNDIRVARMAXDEMAND_BIG_BLOCK:
        * pbase_id = CON_DI_TYPE_MPUNDIRVARMAXDEMAND;
        * pbase_id0 = CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME;
        break;
    default:
        break;
    }
    return;
}
/*==================================================================
//函数名：  save_mp_his_curve_data_by_mpno
//作者：    xuwanhua
//日期：    2011-1-23
//功能：    数据库写曲线数据一条记录
//输入参数：测量点，数据标识，数据指针，数据时间
//输出参数：
//返回值：  
//说明：	
//=================================================================*/
//
int save_mp_his_curve_data_by_mpno(int mpno, unsigned short data_id, unsigned long *puldata_val, struct date_time_rec *rec_time)
{
#if(CONFIG_METER_FACTORY_MODE_ENABLE == CONFIG_METER_FACTORY_MODE)
	return 0;
#else
    int ret = 0;
    struct data_his_cur tmp_data_his_cur;
	tmp_data_his_cur.mp_no = (unsigned short)mpno;
    tmp_data_his_cur.regtime = timerec_to_long(rec_time);
	tmp_data_his_cur.di = data_id;
    memset(tmp_data_his_cur.data, 0x00, 8);
    memcpy(tmp_data_his_cur.data,puldata_val,4);
    
    db_sd_dhc_write_one_data(&tmp_data_his_cur);
    
    return ret;
#endif	
}


/*==================================================================
//函数名：  get_baseid_from_daydataid
//作者：    liuchiqi
//日期：    2011-1-23
//功能：    初始化
//输入参数：07日冻结数据标识
//输出参数：终端自定义日冻结数据标识
//返回值：  无
//=================================================================*/
void get_baseid_from_daydataid(unsigned short *base_id,unsigned short *data_id)
{
    switch (*data_id)
    {
    case CON_DI_TYPE_METER_DAY_FREEZE_DIRPOW:               //（上1次）日冻结正向有功电能数据
        *base_id = CON_DI_TYPE_MPDIRPOW_BLOCK;
        break;
    case CON_DI_TYPE_METER_DAY_FREEZE_REVPOW:               //（上1次）日冻结反向有功电能数据
        *base_id = CON_DI_TYPE_MPUNDIRPOW_BLOCK;
        break;
    case CON_DI_TYPE_METER_DAY_FREEZE_DIRVAR:               //（上1次）日冻结组合无功1电能数据
        *base_id = CON_DI_TYPE_MPDIRVAR_BLOCK;
        break;
    case CON_DI_TYPE_METER_DAY_FREEZE_REVVAR:               //（上1次）日冻结组合无功2电能数据
        *base_id = CON_DI_TYPE_MPUNDIRVAR_BLOCK;
        break;
    case CON_DI_TYPE_METER_DAY_FREEZE_VAR1:                 //（上1次）日冻结第一象限无功电能数据
        *base_id = CON_DI_TYPE_MPVAR1_BLOCK;
        break;
    case CON_DI_TYPE_METER_DAY_FREEZE_VAR2:                 //（上1次）日冻结第二象限无功电能数据
        *base_id = CON_DI_TYPE_MPVAR2_BLOCK;
        break;
    case CON_DI_TYPE_METER_DAY_FREEZE_VAR3:                 //（上1次）日冻结第三象限无功电能数据
        *base_id = CON_DI_TYPE_MPVAR3_BLOCK;
        break;
    case CON_DI_TYPE_METER_DAY_FREEZE_VAR4:                 //（上1次）日冻结第四象限无功电能数据
        *base_id = CON_DI_TYPE_MPVAR4_BLOCK;
        break;
    case CON_DI_TYPE_METER_DAY_FREEZE_DIRPOWDEMAND:         //（上1次）日冻结正向有功最大需量及发生时间数据：
        *base_id = CON_DI_TYPE_MPDIRPOWMAXDEMAND_BIG_BLOCK;
        break;
    case CON_DI_TYPE_METER_DAY_FREEZE_REVPOWDEMAND:         //（上1次）日冻结反向有功最大需量及发生时间数据：
        *base_id = CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_BIG_BLOCK;
        break;
    default:
        break;
    }
    return;
}


/*==================================================================
//函数名：  db_sd_drt_write_data_shm
//作者：    
//日期：    2011-2-16
//功能：    实时数据写入接口(测量点，数据标识，数据项数据值)，从共享内存写入
//输入参数：实时数据结构
//输出参数：无
//返回值：  ret 成功失败
//=================================================================*/
int db_sd_drt_write_data_shm(struct data_rt *sd)
{
	int ret = -1;
	int i,j;

	int mp_no;
	unsigned short di;

	mp_no = sd->mp_no;
	di = sd->di;

	if(db_sd_drt_check_di_is_db(di) == 1)					//部分需要存储到数据库
	{
		ret = db_sd_drt_write_data(sd);
		return ret;
	}

	if(mp_no < 0)
	{
		;
	}
	else if(mp_no == 0)
	{
		struct mp_rt_data_ter_per *rt_data_t;
		rt_data_t = g_p_mp_rt_data_shm->mp_rt_data_t;
		for(i=0;i<CON_RT_DATA_TER_DI_COUNT;i++)
		{
			if(rt_data_t->rt_data[i].data_id == di)
			{
				rt_data_t->rt_data[i].rec_time = sd->rec_time;
				memcpy(rt_data_t->rt_data[i].data, sd->data, 8);
				ret = 0;
				break;
			}
		}
		if(i == CON_RT_DATA_TER_DI_COUNT)
		{//找不到，新增加
			for(j=0;j<CON_RT_DATA_TER_DI_COUNT;j++)
			{
				if(rt_data_t->rt_data[j].data_id == 0)
				{
					rt_data_t->rt_data[j].data_id = di;
					rt_data_t->rt_data[j].rec_time = sd->rec_time;
					memcpy(rt_data_t->rt_data[j].data, sd->data, 8);
					ret = 0;
					break;
				}
			}
			if(j == CON_RT_DATA_TER_DI_COUNT)
			{//满了，考虑删除某些数据
				;
			}
		}
	}
	else if(mp_no <= CON_RT_DATA_MULTI_MP_NUM)
	{
		struct mp_rt_data_multi_per *rt_data_m;
		rt_data_m = g_p_mp_rt_data_shm->mp_rt_data_m + mp_no - 1;
		for(i=0;i<CON_RT_DATA_MULTI_DI_COUNT;i++)
		{
			if(rt_data_m->rt_data[i].data_id == di)
			{
				rt_data_m->rt_data[i].rec_time = sd->rec_time;
				memcpy(rt_data_m->rt_data[i].data, sd->data, 8);
				ret = 0;
				break;
			}
		}
		if(i == CON_RT_DATA_MULTI_DI_COUNT)
		{//找不到，新增加
			for(j=0;j<CON_RT_DATA_MULTI_DI_COUNT;j++)
			{
				if(rt_data_m->rt_data[j].data_id == 0)
				{
					rt_data_m->rt_data[j].data_id = di;
					rt_data_m->rt_data[j].rec_time = sd->rec_time;
					memcpy(rt_data_m->rt_data[j].data, sd->data, 8);
					ret = 0;
					break;
				}
			}
			if(j == CON_RT_DATA_MULTI_DI_COUNT)
			{//满了，考虑删除某些数据
				;
			}
		}
	}
	else if(mp_no <= CON_698_MAX_MP_NUM)
	{
		struct mp_rt_data_simple_per *rt_data_s;
		rt_data_s = g_p_mp_rt_data_shm->mp_rt_data_s + mp_no - CON_RT_DATA_MULTI_MP_NUM - 1;
		for(i=0;i<CON_RT_DATA_SIMP_DI_COUNT;i++)
		{
			if(rt_data_s->rt_data[i].data_id == di)
			{
				rt_data_s->rt_data[i].rec_time = sd->rec_time;
				memcpy(rt_data_s->rt_data[i].data, sd->data, 8);
				ret = 0;
				break;
			}
		}
		if(i == CON_RT_DATA_SIMP_DI_COUNT)
		{//找不到，新增加
			for(j=0;j<CON_RT_DATA_SIMP_DI_COUNT;j++)
			{
				if(rt_data_s->rt_data[j].data_id == 0)
				{
					rt_data_s->rt_data[j].data_id = di;
					rt_data_s->rt_data[j].rec_time = sd->rec_time;
					memcpy(rt_data_s->rt_data[j].data, sd->data, 8);
					ret = 0;
					break;
				}
			}
			if(j == CON_RT_DATA_SIMP_DI_COUNT)
			{//满了，考虑删除某些数据
				;
			}
		}
	}
	else
	{
		;
	}

	return ret;
}

/*==================================================================
//函数名：  db_sd_drt_check_di_is_db
//作者：    xuwanhua
//日期：    2011-2-16
//功能：    检查数据标识，是否需要存储到数据库
//输入参数：数据标识
//输出参数：无
//返回值：  1或者其他 - 需要存储到数据库， 0 - 不需要存储到数据库
//=================================================================*/
int db_sd_drt_check_di_is_db(unsigned short di)
{
#if(CONFIG_METER_FACTORY_MODE_ENABLE == CONFIG_METER_FACTORY_MODE)
	return 0;
#else
	int ret = 0;
	switch(di)
	{
	case CON_DI_TYPE_TER_POWEROFF_LAST_TIME:
	case CON_DI_TYPE_TER_POWERON_LAST_TIME:
	case CON_DI_TYPE_TER_POWEROFF_FLAG:

	case CON_DI_TYPE_POWCTRL_SUMGNO:
	case CON_DI_TYPE_ENERGYCTRL_SUMGNO:
	case CON_DI_TYPE_MONTH_CHANGE_FLAG:

	case CON_DI_TYPE_ALARM_ACD_STATUS:
	case CON_DI_TYPE_IMP_EVENT_POINTER:
	case CON_DI_TYPE_NOR_EVENT_POINTER:
	case CON_DI_TYPE_EVENT_STATUS_L:
	case CON_DI_TYPE_EVENT_STATUS_H:

	case CON_DI_TYPE_MP_TER_LAST_TIME:
	case CON_DI_TYPE_MP_TER_LAST_UP_COMM_TIME:

	case CON_DI_TYPE_CURR_SOFTWARE_EDITION:
	case CON_DI_TYPE_LAST_SOFTWARE_EDITION:
	case CON_DI_TYPE_METER_TIME_ERR_TIME:
	case CON_DI_TYPE_METER_STOP_TIME:

	case CON_DI_TYPE_MP_FLUX_OVER_FLAG:
	case CON_DI_TYPE_MP_FLUX_OVER_COUNT:
	case CON_DI_TYPE_MP_DISCONNECT_FLAG:

	case CON_DI_TYPE_MP_SUMG_POW_TOTAL:					//总加实时数据需要存储到数据库
	case CON_DI_TYPE_MP_SUMG_POW_FEE1:
	case CON_DI_TYPE_MP_SUMG_POW_FEE2:
	case CON_DI_TYPE_MP_SUMG_POW_FEE3:
	case CON_DI_TYPE_MP_SUMG_POW_FEE4:
	case CON_DI_TYPE_MP_SUMG_VAR_TOTAL:
	case CON_DI_TYPE_MP_SUMG_VAR_FEE1:
	case CON_DI_TYPE_MP_SUMG_VAR_FEE2:
	case CON_DI_TYPE_MP_SUMG_VAR_FEE3:
	case CON_DI_TYPE_MP_SUMG_VAR_FEE4:

	case CON_DI_TYPE_MP_SUMG_INST_POW:
	case CON_DI_TYPE_MP_SUMG_INST_VAR:
	case CON_DI_TYPE_MP_SUMG_LEFT_POW:
	case CON_DI_TYPE_MP_SUMG_POW_FIX_VALUE:

	case CON_DI_TYPE_MP_SUMG_LAST_POW_TOTAL:
	case CON_DI_TYPE_MP_SUMG_LAST_POW_FEE1:
	case CON_DI_TYPE_MP_SUMG_LAST_POW_FEE2:
	case CON_DI_TYPE_MP_SUMG_LAST_POW_FEE3:
	case CON_DI_TYPE_MP_SUMG_LAST_POW_FEE4:
	case CON_DI_TYPE_MP_SUMG_LAST_VAR_TOTAL:
	case CON_DI_TYPE_MP_SUMG_LAST_VAR_FEE1:
	case CON_DI_TYPE_MP_SUMG_LAST_VAR_FEE2:
	case CON_DI_TYPE_MP_SUMG_LAST_VAR_FEE3:
	case CON_DI_TYPE_MP_SUMG_LAST_VAR_FEE4:

	case CON_DI_TYPE_MP_SUMG_MAX_INSTANT_POW:
	case CON_DI_TYPE_MP_SUMG_MAX_INSTANT_POW_TIME:
	case CON_DI_TYPE_MP_SUMG_MIN_INSTANT_POW:
	case CON_DI_TYPE_MP_SUMG_MIN_INSTANT_POW_TIME:
	case CON_DI_TYPE_MP_SUMG_ZEROTIME_INSTANT_POW:
	case CON_DI_TYPE_MP_SUMG_OVERTIME_POWER:
	case CON_DI_TYPE_MP_SUMG_OVERTIME_ENERGY:
	case CON_DI_TYPE_MP_SUMG_POWEROVERACCVALTOTAL:
	case CON_DI_TYPE_MP_SUMG_ENERGYOVERACCVALTOTAL:
	case CON_DI_TYPE_MP_SUMG_POWEROVERSTARTVAL:
	case CON_DI_TYPE_MP_SUMG_ENERGYOVERSTARTVAL:

		ret = 1;
		break;

	default:
		break;
	}
	return ret;
#endif	
}

/*==================================================================
//函数名：  db_sd_drt_get_by_md_shm
//作者：    
//日期：    2011-2-16
//功能：    实时数据读取，从共享内存读取
//输入参数：测量点号，数据标识
//输出参数：结构(数据值, 记录时间)
//返回值：  ret 成功失败
//=================================================================*/
int db_sd_drt_get_by_md_shm(unsigned short mp_no, unsigned short di, struct simp_data *sd)
{
	int ret = -1;
	int i;

	if(db_sd_drt_check_di_is_db(di) == 1)					//部分需要从数据库读取
	{
		ret = db_sd_drt_get_by_md(mp_no, di, sd);
		return ret;
	}

	if(mp_no == 0)
	{
		struct mp_rt_data_ter_per *rt_data_t;
		rt_data_t = g_p_mp_rt_data_shm->mp_rt_data_t;
		for(i=0;i<CON_RT_DATA_TER_DI_COUNT;i++)
		{
			if(rt_data_t->rt_data[i].data_id == di)
			{
				sd->time = rt_data_t->rt_data[i].rec_time;
				memcpy(sd->data, rt_data_t->rt_data[i].data, 8);
				ret = 0;
				break;
			}
		}
	}
	else if(mp_no <= CON_RT_DATA_MULTI_MP_NUM)
	{
		struct mp_rt_data_multi_per *rt_data_m;
		rt_data_m = g_p_mp_rt_data_shm->mp_rt_data_m + mp_no - 1;
		for(i=0;i<CON_RT_DATA_MULTI_DI_COUNT;i++)
		{
			if(rt_data_m->rt_data[i].data_id == di)
			{
				sd->time = rt_data_m->rt_data[i].rec_time;
				memcpy(sd->data, rt_data_m->rt_data[i].data, 8);
				ret = 0;
				break;
			}
		}
	}
	else if(mp_no <= CON_698_MAX_MP_NUM)
	{
		struct mp_rt_data_simple_per *rt_data_s;
		rt_data_s = g_p_mp_rt_data_shm->mp_rt_data_s + mp_no - CON_RT_DATA_MULTI_MP_NUM - 1;
		for(i=0;i<CON_RT_DATA_SIMP_DI_COUNT;i++)
		{
			if(rt_data_s->rt_data[i].data_id == di)
			{
				sd->time = rt_data_s->rt_data[i].rec_time;
				memcpy(sd->data, rt_data_s->rt_data[i].data, 8);
				ret = 0;
				break;
			}
		}
	}
	else
	{
		sd->time = 0;
		memset(sd->data, 0xFF, 8);
		sd->data[3] = 0x7F;
	}

	return ret;
}

/*
	long向时间结构转换
*/
struct date_time_rec time_long_to_timerec(long ltime)
{
	time_t tmp_time;
	struct tm *ptr_time;
	struct date_time_rec mytime;

	tmp_time = (time_t)ltime;
	ptr_time = localtime(&tmp_time);

	mytime.year = ptr_time->tm_year + 1900;
	mytime.month = ptr_time->tm_mon + 1;
	mytime.day = ptr_time->tm_mday;
	mytime.hour = ptr_time->tm_hour;
	mytime.minute = ptr_time->tm_min;
	mytime.second = ptr_time->tm_sec;

	return mytime;
}
/*==================================================================
//函数名：  get_mp_curr_data_by_mpno
//作者：    
//日期：    
//功能：    从数据库读取实时数据
//输入参数：mpno 测量点
            data_id
//输出参数：pddata_val
						rec_time
//返回值：  成功返回0, 失败返回 < 0
//=================================================================*/
int get_mp_curr_data_by_mpno(int mpno, unsigned short data_id, unsigned long *puldata_val, struct date_time_rec *rec_time)
{
	int ret = 0;
	unsigned long ulval = CON_INVALID_LONG_VAL;
	struct simp_data st_data;

	st_data.time = 0;
	db_sd_drt_get_by_md_shm((unsigned short)mpno, data_id, &st_data);
	if(st_data.time == 0)
	{
		rec_time->second = 255;
		memcpy(puldata_val, &ulval, 4);
	}
	else
	{
		(*rec_time) = time_long_to_timerec(st_data.time);
		memcpy(puldata_val, st_data.data, 4);
	}

	return ret;
}


/*******************************************************************
//函数名：  get_program_key_status()
//作者：    lcq
//日期：    2011-05-09
//功能：    获取编程键状态
//输入参数：
//返回值：  
                      1 表示有编程键按下
                      0和其他值 表示没有键按下
//注意事项：无
*******************************************************************/
int get_program_key_status(void)
{
	int ret=0;
	struct date_time_rec data_time;//存放数据时间
	unsigned long uldata_val = CON_INVALID_LONG_VAL;
	get_mp_curr_data_by_mpno(CON_TER_MPNO, CON_DI_TYPE_TER_PROGRAMKEY_FLAG, &uldata_val, &data_time);
	if(uldata_val == 0x01)
		ret = uldata_val;
	else 
		ret = 0;
	return ret;
}

#define  FLAG_FILE "/tmp/dbserver.flag"
static int get_dbserver_flag(unsigned char *flag)
{
    int fd, ret;
    
    fd = open(FLAG_FILE, O_RDONLY);
    if (fd < 0) return -1;
    
    ret = flock(fd, LOCK_SH);
    if (ret < 0) {
        close(fd);
        return -1;
    }
    
    ret = read(fd, flag, 1);
    
    flock(fd, LOCK_UN);
    close(fd);	
    
    if (ret != 1) {
        return -1;
    }
    return 0;
}
/*==================================================================
//函数名：  del_comm_frame
//作者：    
//日期：    
//功能：    bdb数据库异常检查
//输入参数：无
//输出参数：无
//返回值：  成功返回0，失败返回 < 0
//=================================================================*/
int bdb_check()
{
    int ret=-1;
    unsigned char val;
    ret = get_dbserver_flag(&val);

    if( ret == 0 )
    {
        switch (val)
        {
		case 0x30:
		case 0x31:
		case 0x32:
		case 0x33:
		case 0x34:
			ret=val-0x30;
			break;
        default:
            ret = -1;
            break;
        }
    }
    else
    {
		log_printf_level(LOG_LEVEL_ERR, DBGFMT_A" open dbserver.flag failed--------\n", DBGARG_A);
        ret = -1;
    }
    return ret;
}

#endif

