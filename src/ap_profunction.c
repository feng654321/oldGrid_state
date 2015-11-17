#define AP_PROFUNCTION_GLOBALS
#include "common.h"

const u16 TB_VOLTAGE_TYPE_TO_COEF[3]=
{
    CK_V_577,
    CK_V_100, 
    CK_V_220
};
#define GetProgramBakAddr(addr)     (BAK_DATA_PROGRAM_START+(addr-EPL_DATA_PROGRAM_START))

unsigned long bcd_to_hex_3(unsigned char *bcd)
{
	unsigned char tmp;
	unsigned long ret_hex = 0;
	
	tmp = bcd[2];
	tmp &= 0xF0;
	tmp >>= 4;
	ret_hex += tmp*100000;
	
	tmp = bcd[2];
	tmp &= 0x0F;
	ret_hex += tmp*10000;
	
	tmp = bcd[1];
	tmp &= 0xF0;
	tmp >>= 4;
	ret_hex += tmp*1000;
	
	tmp = bcd[1];
	tmp &= 0x0F;
	ret_hex += tmp*100;
	
	tmp = bcd[0];
	tmp &= 0xF0;
	tmp >>= 4;
	ret_hex += tmp*10;
	
	tmp = bcd[0];
	tmp &= 0x0F;
	ret_hex += tmp;
	
	return ret_hex;
}

unsigned long bcd_to_hex_4(unsigned char *bcd)
{
	unsigned char tmp;
	unsigned long ret_hex = 0;

	tmp = bcd[3];
	tmp &= 0xF0;
	tmp >>= 4;
	ret_hex += tmp*10000000;
	
	tmp = bcd[3];
	tmp &= 0x0F;
	ret_hex += tmp*1000000;
	
	tmp = bcd[2];
	tmp &= 0xF0;
	tmp >>= 4;
	ret_hex += tmp*100000;
	
	tmp = bcd[2];
	tmp &= 0x0F;
	ret_hex += tmp*10000;
	
	tmp = bcd[1];
	tmp &= 0xF0;
	tmp >>= 4;
	ret_hex += tmp*1000;
	
	tmp = bcd[1];
	tmp &= 0x0F;
	ret_hex += tmp*100;
	
	tmp = bcd[0];
	tmp &= 0xF0;
	tmp >>= 4;
	ret_hex += tmp*10;
	
	tmp = bcd[0];
	tmp &= 0x0F;
	ret_hex += tmp;
	
	return ret_hex;
}

unsigned long hex_to_bcd_4(unsigned long hex_val)
{
	unsigned long ret = 0;
	if(hex_val > 99999999)
		hex_val = 99999999;
	ret = hex_val % 10 + (hex_val % 100) / 10 * 0x10;
	hex_val = hex_val / 100;
	ret = (hex_val % 10 + (hex_val % 100) / 10 * 0x10) * 0x100 + ret;
	hex_val = hex_val / 100;
	ret = (hex_val % 10 + (hex_val % 100) / 10 * 0x10) * 0x10000 + ret;
	hex_val = hex_val / 100;
	ret = (hex_val % 10 + (hex_val % 100) / 10 * 0x10) * 0x1000000 + ret;
	return ret;
}

unsigned long hex_to_bcd_3(unsigned long hex_val)
{
	unsigned long ret = 0;
	if(hex_val > 999999)
		hex_val = 999999;
	ret = hex_val % 10 + (hex_val % 100) / 10 * 0x10;
	hex_val = hex_val / 100;
	ret = (hex_val % 10 + (hex_val % 100) / 10 * 0x10) * 0x100 + ret;
	hex_val = hex_val / 100;
	ret = (hex_val % 10 + (hex_val % 100) / 10 * 0x10) * 0x10000 + ret;
	return ret;
}

unsigned long bcd_to_hex_2(unsigned char *bcd)
{
	unsigned char tmp;
	unsigned long ret_hex = 0;
	
	tmp = bcd[1];
	tmp &= 0xF0;
	tmp >>= 4;
	ret_hex += tmp*1000;
	
	tmp = bcd[1];
	tmp &= 0x0F;
	ret_hex += tmp*100;
	
	tmp = bcd[0];
	tmp &= 0xF0;
	tmp >>= 4;
	ret_hex += tmp*10;
	
	tmp = bcd[0];
	tmp &= 0x0F;
	ret_hex += tmp;
	
	return ret_hex;
}

uchar ReadProgramData(ulong DataName, u16 nLen, uchar* pSrc)
{
    if(1 !=ReadDataDirect(DataName, nLen, pSrc))
    {
        if(1 !=ReadDataDirect(GetProgramBakAddr(DataName), nLen, pSrc))
        {
            ErrPrint("GOD!, read SYSTEMPROFUNCTION failed ! DataName=0x%08X, Len=%d\n", DataName, nLen);
            return DLT_RET_ERR;
        }
    }
    return DLT_RET_SUCC;
}

uchar WriteProgramData(const uchar* pSrc, ulong DataName, u16 nLen)
{
    WriteDataDirect(pSrc, DataName, nLen);
    WriteDataDirect(pSrc, GetProgramBakAddr(DataName), nLen);
    return DLT_RET_SUCC;
}

void ProgFunctionLoad(void)
{

    u16 l;
    uchar ucTemp;
    // uchar *ucpData;
    ucTemp=1;
    
#if (PROFUNCTION_METER_TYPE==PROFUNCTION_METER_TYPE_ALL)
    if(DLT_RET_SUCC == ReadProgramData(EPL_DATA_PROGRAM_START, CON_SYSTEMPROFUNCTION_LEN,&Wr_data[0]))
    {
        memcpy(&SYSTEMPROGFUNCTION[0], &Wr_data[0], CON_SYSTEMPROFUNCTION_LEN);
    }
    else
    {
        //AddDataInit();
    }
    
    
#if(CONFIG_METER_FACTORY_MODE_ENABLE == CONFIG_METER_FACTORY_MODE)
    //生产模式程序，固定厂内状态和校表状态
    if((PROGFUNCTION_METER_FACTORY != METER_IN_FACTORY)||
        (PROGFUNCTION_METER_ADJUST != METER_IN_FACTORY))
    {
        PROGFUNCTION_METER_FACTORY = METER_IN_FACTORY;
        PROGFUNCTION_METER_ADJUST = METER_IN_FACTORY;
        WriteProgramData(&PROGFUNCTION_METER_FACTORY, (EPL_DATA_PROGRAM_START+(0x0000FFFF & CFGDIR_METER_FACTORY_ENABLE)), 2);
    }
#else
    //非生产模式程序，禁止校表状态
    if((PROGFUNCTION_METER_ADJUST == METER_IN_FACTORY))
    {
        PROGFUNCTION_METER_ADJUST = METER_OUT_FACTORY;
        WriteProgramData(&PROGFUNCTION_METER_ADJUST, (EPL_DATA_PROGRAM_START+(0x0000FFFF & CFGDIR_METER_ADJUST_ENABLE)), 1);
    }
#endif    
    // 打开表内功能
    for(l=( 0x0000FFFF &CFGDIR_PRO_METER_ENABLE);l<=( 0x0000FFFF &CFGDIR_PRO_PROGRAM_OPEN_ENABLE);l++)
    {
        SYSTEMPROGFUNCTION[l] =GAL_YES;
    }
#else
#endif

// #endif

    
    // AA  表型  AA 
    ulTypeIb=15;    // 1 dot 5 A
    ulTypeImax=60;  // 6 dot 0 A
    ulTypeUn=2200;  // 220 dot 0 V

	unsigned long ultmp;
	unsigned char ucAde7758Data[4];
	ReadADRegResumeData(CURRENT_IB,4,&ucAde7758Data[0]);//电流规格
	ultmp=ucAde7758Data[0];
	ultmp=ultmp*256+ucAde7758Data[1];
	ultmp=ultmp*256+ucAde7758Data[2];
	ultmp=ultmp*256+ucAde7758Data[3];
	ultmp = bcd_to_hex_4((unsigned char*) &ultmp);
	if (ultmp > 100000 || ultmp < 3000)
	{
		ultmp = 15000;
	}
	ulTypeIb = ultmp/1000;
	MTRACE("ulTypeIb:%d\n",ulTypeIb);

	ReadADRegResumeData(CURRENT_IMAX,4,&ucAde7758Data[0]);//最大电流
	ultmp=ucAde7758Data[0];
	ultmp=ultmp*256+ucAde7758Data[1];
	ultmp=ultmp*256+ucAde7758Data[2];
	ultmp=ultmp*256+ucAde7758Data[3];
	ultmp = bcd_to_hex_4((unsigned char*) &ultmp);
	if (ultmp > 600000 || ultmp < 12000)
	{
		ultmp = 60000;
	}
	ulTypeImax = ultmp/1000;
	MTRACE("ulTypeImax:%d\n",ulTypeImax);

	ReadADRegResumeData(VOLTAGE_RATE,4,&ucAde7758Data[0]);//电压规格
	ultmp=ucAde7758Data[0];
	ultmp=ultmp*256+ucAde7758Data[1];
	ultmp=ultmp*256+ucAde7758Data[2];
	ultmp=ultmp*256+ucAde7758Data[3];
	ultmp = bcd_to_hex_4((unsigned char*) &ultmp)/1000;
	if(ultmp != VOLTAGE_RATE_220 && ultmp != VOLTAGE_RATE_100 && ultmp != VOLTAGE_RATE_577)
	{
		ultmp = VOLTAGE_RATE_220;
	}
	ulTypeUn = ultmp;
	MTRACE("ulTypeUn:%d\n",ulTypeUn);

    if((ulTypeIb>=50)&&(ulTypeImax>=100))
    {
        CURRENT_TYPE=CURRENT_TYPE_BIG;
    }
    else
    {
        CURRENT_TYPE=CURRENT_TYPE_SMALL;
    }
        
	ReadADRegResumeData(PULSE_CONSTANT,4,&ucAde7758Data[0]);//脉冲常数
	ultmp=ucAde7758Data[0];
	ultmp=ultmp*256+ucAde7758Data[1];
	ultmp=ultmp*256+ucAde7758Data[2];
	ultmp=ultmp*256+ucAde7758Data[3];
	ultmp = bcd_to_hex_4((unsigned char*) &ultmp);
	if (ultmp > 100000 || ultmp < 400)
	{
		ultmp = 6400;
	}
	KwhPluseNum = ultmp/100;
	MTRACE("KwhPluseNum:%d\n",KwhPluseNum);

	ReadADRegResumeData(METER_STANDARD,4,&ucAde7758Data[0]);//电表规格
	ultmp=ucAde7758Data[0];
	ultmp=ultmp*256+ucAde7758Data[1];
	ultmp=ultmp*256+ucAde7758Data[2];
	ultmp=ultmp*256+ucAde7758Data[3];
//	ultmp = bcd_to_hex_4((unsigned char*) &ultmp);
	if (ultmp != 0x42 && ultmp != 0x43)
	{
		ultmp = METERTYPE_3_4;//43;
	}

	PROGFUNCTION_TYPE_METER_TYPE = ultmp;//meter_type;
	MTRACE("PROGFUNCTION_TYPE_METER_TYPE:%d\n",PROGFUNCTION_TYPE_METER_TYPE);

    // AA    电压计算系数    AA 
    ucTemp=SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_TYPE_VOLTAGE_UN + 3 )];
    if(ucTemp>2)
        ucTemp=2;
    uiClacMeterVoltageCoef=TB_VOLTAGE_TYPE_TO_COEF[ucTemp];

    // AA    有功- 无功- 视在-功率计算倍数和除数   AA   
    ucClacMeterKwCoefMul=PROGFUNCTION_COEF_KW_MUL;
    ucClacMeterKwCoefDiv=PROGFUNCTION_COEF_KW_DIV;
    if(0==ucClacMeterKwCoefDiv) 
        ucClacMeterKwCoefDiv=1;
    if(0==ucClacMeterKwCoefMul)
        ucClacMeterKwCoefMul=2;
    
    // AA    有功计算系数   AA  
    uiClacMeterKwCoef=SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_CALC_KW + 0)] ;
    uiClacMeterKwCoef=uiClacMeterKwCoef*256+SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_CALC_KW + 1 )];
    if(0==uiClacMeterKwCoef) 
        uiClacMeterKwCoef=1430;
    
    // AA    无功计算系数   AA  
    uiClacMeterKvarCoef=SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_CALC_KVAR+ 0)] ;
    uiClacMeterKvarCoef=uiClacMeterKvarCoef*256+SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_CALC_KVAR + 1 )];
    if(0==uiClacMeterKvarCoef) 
        uiClacMeterKvarCoef=1430;
    
    // AA    视在计算系数   AA  
    uiClacMeterKvaCoef=SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_CALC_KVA+ 0)] ;
    uiClacMeterKvaCoef=uiClacMeterKvaCoef*256+SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_CALC_KVA + 1 )];
    if(0==uiClacMeterKvaCoef) 
        uiClacMeterKvaCoef=1430;
    
    // AA    脉冲防潜动系数    AA   
    uiMeterPluseResetDelaySet=SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_POWER_OUTTIME + 0 )] ;
    uiMeterPluseResetDelaySet=uiMeterPluseResetDelaySet*256+SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_POWER_OUTTIME + 1 )] ;
    if(0==uiMeterPluseResetDelaySet)
        uiMeterPluseResetDelaySet=852;
    
    // AA    需量防潜动系数    AA   
    uiMeterDemandResetValue=SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_DEMAND_STARTCOUNT + 0 )] ;
    uiMeterDemandResetValue=uiMeterDemandResetValue*256+SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_DEMAND_STARTCOUNT + 1 )] ;
    if(0==uiMeterDemandResetValue)
        uiMeterDemandResetValue=7;


    //RAM[RAM_COEF_HUMOROUS_MAX_NUM]=0x00;
    RAM[RAM_POWER_PULSE_TIME+0]=0x80;
    RAM[RAM_POWER_PULSE_TIME+1]=0x00;

//    PROGFUNCTION_ACPOWER_LOSS=CONFIG_METER_AUX_MODE;   //ZD 无辅助电源功能

    uiMeter0d001PerCurrent=ulTypeIb*PROGFUNCTION_COEF_METER_DATA_STARTUP/10;
}











