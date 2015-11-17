
#define AP_DEMAND_GLOBALS
#include "common.h"


//uchar ucAddoneSecondKwmode_second;
// AA 需量週期 AA
uchar ucDemandClcye;    
// AA 滑差時間   AA
uchar ucDemandPat;



uchar rCurrentDemandPat;
uchar rCurrentPriceDemandPat;
uchar ucDemandTempBuffer[9];
uchar ucDemandOneClcyeFlg;
uchar ucDemandPulseMinute;

uchar ucDemandModeMinute;
//uchar ucDemandModeSecond;
// AA  当前需量数据缓冲区的数据指针  AA
uchar ucDemandClcyeStart;   
// AA  当前需量缓冲区内有效的数据数   AA
uchar ucDemandClcyeAllHave;
// AA  当前费率需量缓冲区内有效的数据数   AA
uchar ucDemandClcyePriceHave;

typedef struct
{
    uchar ucStartAddr;
    uchar ucHaveAllNum;
    uchar ucHavePriceNum;
}ST_DEMAND_POINT_PARAM;
typedef struct
{
    uchar ucDemandTpye; //  AA 需量类型  AA
    uchar ucCanSub;         //  AA 是否有减法  AA
    ulong ucAllStartAddr;       //  AA RAM 地址----总的指针  AA
    ulong ucPriceStartAddr; //  AA RAM 地址---- 费率的指针  AA
}ST_DEMAND_CLAC_PARAM;

// AA   没有费率需量   AA
#define DEMAND_PRICE_NO_HAVE        0xFFFFFFFF
// AA  需量计算时，只有加的功能，没有减的功能    AA
#define DEMAND_CLAC_ONLYADD         0x00
// AA  需量计算中，有加也有减    AA
#define DEMAND_CLAC_CANSUB      0x01
const ST_DEMAND_CLAC_PARAM TB_DEMAND_CLAC[PTD_DEMAND_COUNT]=
{
    // AA 需量计算类型,累加方式,         总的RAM数据指针,   费率的RAM数据 指针
    {PTD_KW_F_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KW_F_ALL_DATA , RAM_KW_F_F1_DATA }, // 0 AA 当前正向有功总最大需量指针 AA
    {PTD_KW_R_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KW_R_ALL_DATA , RAM_KW_R_F1_DATA }, // 1 AA 当前反向有功总最大需量指针 AA
	{PTD_KVAR_Q1_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_Q1_ALL_DATA , RAM_KVAR_Q1_F1_DATA }, // 4 AA 当前1象限无功总最大需量指针 AA
	{PTD_KVAR_Q2_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_Q2_ALL_DATA , RAM_KVAR_Q2_F1_DATA }, // 5 AA 当前2象限无功总最大需量指针 AA
	{PTD_KVAR_Q3_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_Q3_ALL_DATA , RAM_KVAR_Q3_F1_DATA} , // 6 AA 当前3象限无功总最大需量指针 AA
	{PTD_KVAR_Q4_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_Q4_ALL_DATA , RAM_KVAR_Q4_F1_DATA} , // 7 AA 当前4象限无功总最大需量指针 AA
	{PTD_KVA_F_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVA_F_ALL_DATA , RAM_KVA_F_F1_DATA} , // 8 AA 当前正向视在总最大需量指针 AA
	{PTD_KVA_R_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVA_R_ALL_DATA , RAM_KVA_R_F1_DATA} , // 9 AA 当前反向视在总最大需量指针 AA
	{PTD_KW_A_F_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KW_A_F_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 10 AA 当前A相正相有功最大需量指针 AA
	{PTD_KW_A_R_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KW_A_R_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 11 AA 当前A相反相有功最大需量指针 AA
	{PTD_KVAR_A_Q1_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_A_Q1_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 14 AA 当前A相1象限无功最大需量指针 AA
	{PTD_KVAR_A_Q2_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_A_Q2_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 15 AA 当前A相2象限无功最大需量指针 AA
	{PTD_KVAR_A_Q3_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_A_Q3_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 16 AA 当前A相3象限无功最大需量指针 AA
	{PTD_KVAR_A_Q4_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_A_Q4_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 17 AA 当前A相4象限无功最大需量指针 AA
	{PTD_KVA_A_F_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVA_A_F_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 18 AA 当前A相正相视在最大需量指针 AA
	{PTD_KVA_A_R_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVA_A_R_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 19 AA 当前A相反相视在最大需量指针 AA
	{PTD_KW_B_F_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KW_B_F_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 20 AA 当前B相正相有功最大需量指针 AA
	{PTD_KW_B_R_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KW_B_R_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 21 AA 当前B相反相有功最大需量指针 AA
	{PTD_KVAR_B_Q1_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_B_Q1_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 24 AA 当前B相1象限无功最大需量指针 AA
	{PTD_KVAR_B_Q2_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_B_Q2_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 25 AA 当前B相2象限无功最大需量指针 AA
	{PTD_KVAR_B_Q3_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_B_Q3_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 26 AA 当前B相3象限无功最大需量指针 AA
	{PTD_KVAR_B_Q4_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_B_Q4_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 27 AA 当前B相4象限无功最大需量指针 AA
	{PTD_KVA_B_F_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVA_B_F_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 28 AA 当前B相正相视在最大需量指针 AA
	{PTD_KVA_B_R_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVA_B_R_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 29 AA 当前B相反相视在最大需量指针 AA
	{PTD_KW_C_F_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KW_C_F_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 30 AA 当前C相正相有功最大需量指针 AA
	{PTD_KW_C_R_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KW_C_R_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 31 AA 当前C相反相有功最大需量指针 AA
	{PTD_KVAR_C_Q1_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_C_Q1_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 34 AA 当前C相1象限无功最大需量指针 AA
	{PTD_KVAR_C_Q2_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_C_Q2_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 35 AA 当前C相2象限无功最大需量指针 AA
	{PTD_KVAR_C_Q3_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_C_Q3_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 36 AA 当前C相3象限无功最大需量指针 AA
	{PTD_KVAR_C_Q4_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_C_Q4_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 37 AA 当前C相4象限无功最大需量指针 AA
	{PTD_KVA_C_F_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVA_C_F_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 38 AA 当前C相正相视在最大需量指针 AA
	{PTD_KVA_C_R_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVA_C_R_ALL_DATA , DEMAND_PRICE_NO_HAVE} // 39 AA 当前C相反相视在最大需量指针 AA
};

void DemandParaInit(void)
{
    ReadCoefDataWithCheck(EPL_DEMAND_CYCLE_TIME, 2, Ap_temp, 1);

    if((Ap_temp[0] >= 1) && (Ap_temp[0] <= 0x60) && ((Ap_temp[0] & 0x0f) <= 0x09))
    {								//需量周期大于0，小于0x60（BCD码），个位数不大于9，数据有效
        ucDemandClcye=HexFromRam1Bcd(Ap_temp);
    }
    else 
    {								//参数出错，恢复默认参数
        ucDemandClcye=15;
    }
    if((Ap_temp[1] >= 1) && (Ap_temp[1] <= ucDemandClcye) && ((Ap_temp[0] & 0x0f) <= 0x09)) //<=60
    {								//滑差时间大于0，小于0x60（BCD码），个位数不大于9，数据有效
        ucDemandPat=HexFromRam1Bcd(Ap_temp+1);
    }
    else
    {								//参数出错，恢复默认参数
        ucDemandPat=1;
    }
	if((ucDemandClcye % ucDemandPat) != 0)
	{							//不能整除恢复默认值
		//ucDemandClcye=15;
		//ucDemandPat=1;
	}
    //MTRACE("DemandParaInit %d, %d\n", ucDemandClcye, ucDemandPat);
    //uuReactiveMode01.ucData = RAM[RAM_CHARACTER_REACTIVE01];
    //uuReactiveMode02.ucData = RAM[RAM_CHARACTER_REACTIVE02];
}

// ST_DEMAND_POINT_PARAM rCurrentDemandPoint[PTD_DEMAND_COUNT];
/*********************************************************************
原型：void DemandDataInit(void);
功能：初始化需量数据
参数：无
输入：无
返回：无
范围：应用层直接调用
注释：无
作者：张龙
版本：V1.0
最后修改时间：2009-01-19
修改说明：创建
********************************************************************/
void DemandDataInit(void)
{
    uchar ucPoint;
    for(ucPoint=0;ucPoint<PTD_DEMAND_COUNT;ucPoint++)
    {
        ulKwPerMinute[ucPoint]=0;
        //ucKwPerSecondCount=0;
        //ucAddoneSecondKwmode_second=0xff;
        memset(&uiDemandClacBuffer[ucPoint][0], 0x00, 2*DEMAND_BUFFER_TIME_COUNT);
    }
    ucKwPerSecondCount=0;
    rCurrentDemandPat=0;
    rCurrentPriceDemandPat=0;
    ucDemandOneClcyeFlg=GAL_NO;
    ucDemandPulseMinute=0;
    ucDemandModeMinute=RSOFT_RTC_MINUTE;
    ucTempCurrentDemandPrice=ucCurrentPriceHEX;
    ucDemandClcyeStart=0;
    ucDemandClcyeAllHave=0;
    ucDemandClcyePriceHave=0;
    ucDemandPriceDemandTimeChange=GAL_NO;   
    DemandParaInit();
    DemandPriceChange();
    memset(&RAM[RAM_CURRENT_DEMAND_KW_F], 0x00, 4*(PTD_DEMAND_COUNT+2));
    memset(&ulDemandClacKvarC1C2SumBuffer[0], 0x00, sizeof(ulDemandClacKvarC1C2SumBuffer));
    
}


/*********************************************************************
原型：ulong ClacDemandFromPower(ulong value)
功能：把计算得到ADE7758能量数据转化为功率数据
参数：
输入：value 输入的能量数据
返回：计算之后的功率数据。
范围：应用层直接调用
注释：无
作者：张龙
版本：V1.0
最后修改时间：2009-01-19
修改说明：创建
********************************************************************/
#define CON_KW_CALC_COEF  100000
ulong ClacDemandFromPower(ulong value)
{
#if 1
    ulong sum;
    ulong t;
       sum=value;
    sum=sum*((CON_KW_CALC_COEF*ucClacMeterKwCoefMul)/(ucClacMeterKwCoefDiv*uiClacMeterKwCoef))+((sum*((CON_KW_CALC_COEF*ucClacMeterKwCoefMul)%(ucClacMeterKwCoefDiv*uiClacMeterKwCoef)))/(ucClacMeterKwCoefDiv*uiClacMeterKwCoef)); 
    t=(value*((CON_KW_CALC_COEF*ucClacMeterKwCoefMul)%(ucClacMeterKwCoefDiv*uiClacMeterKwCoef)))%(ucClacMeterKwCoefDiv*uiClacMeterKwCoef);
    if(t>(ucClacMeterKwCoefDiv*uiClacMeterKwCoef)/2)
        sum=sum+1;
       if(sum<uiMeterDemandResetValue)
        sum=0;
    return sum;
#else
    ulong b_kw,b_div,b_div_add,ulTemp;
    b_kw=uiClacMeterKwCoef;
    
    b_div=ucClacMeterKwCoefDiv;
    b_div_add=ucClacMeterKwCoefMul;
    ulTemp=value%b_div;
    value=value/b_div;
    value=value*((CON_KW_CALC_COEF*b_div_add)/(b_kw))+((value*((CON_KW_CALC_COEF*b_div_add)%(b_kw)))/(b_kw)); 
    ulTemp=ulTemp*CON_KW_CALC_COEF*b_div_add/b_kw;
    value=value+ulTemp;

    return value;
#endif
    
}
/*********************************************************************
原型：uchar CompareDemand(u16 uiAddr)
功能：比较当前需量和uiAddr所对应的RAM 地址对应的需量的大小
参数：ucDemandTempBuffer[] 当前的需量信息数据
输入：uiAddr 指定的RAM 地址
返回：如果ucDemandTempBuffer的数据大，则为1， 否则为0
范围：应用层直接调用
注释：无
作者：张龙
版本：V1.0
最后修改时间：2009-01-19
修改说明：创建
********************************************************************/
uchar CompareDemand(ulong ulAddr)
{
    UN_U32_PARAM m1,m2;
    uchar k;
    m1.ulData=0;
    m2.ulData=0;
    for(k=0;k<4;k++)
    {
        m1.ucbData[k]=RAM[ulAddr+k];
        m2.ucbData[k]=ucDemandTempBuffer[k];
    }
    if(m1.ulData<m2.ulData)
    {
        return 1;
    }
    return 0;

}
uchar CompareRamDataAndMoveToMax(u16 uiMaxAddr,u16 uiFromAddr)
{
    ulong ulMax,ulFrom;
    memcpy((uchar *)&ulMax, &RAM[uiMaxAddr], 4);
    memcpy((uchar *)&ulFrom, &RAM[uiFromAddr], 4);
    if(ulFrom>ulMax)
    {
        memcpy( &RAM[uiMaxAddr],(uchar *)&ulFrom, 4);
        return 1;
    }
    return 0;
}

#if 0
void CopyDemandRamtoFm2(ulong ulRamAddr)
{
    WriteDataDirect(&ucDemandTempBuffer[0], EPL_DEMAND_DATA_START+ulRamAddr-RAM_DEMAND_DATA_START,  9);
    
}
#endif
/*********************************************************************
原型：void  DemandStorNowTime(void)
功能：把当前的时间信息写到ucDemandTempBuffer 中
参数：无
输入：无 
返回：无
范围：应用层直接调用
注释：无
作者：张龙
版本：V1.0
最后修改时间：2009-01-19
修改说明：创建
********************************************************************/
void  DemandStorNowTime(void)
{
    ucDemandTempBuffer[4]=RSOFT_RTC_MINUTE;
    ucDemandTempBuffer[5]=RSOFT_RTC_HOUR;
    ucDemandTempBuffer[6]=RSOFT_RTC_DAY;
    ucDemandTempBuffer[7]=RSOFT_RTC_MONTH;
    ucDemandTempBuffer[8]=RSOFT_RTC_YEAR;
}
/*********************************************************************
原型：  uchar  ComPareMaxDemandFromAddr(ulong ulData,ulong ulAddr)
功能：  给出当前需量值和要比较的RAM 地址，
            如果当前的需量值大，则更新数据
            同时记录对应的时间
参数：  MODE_DEMAND_CALC_POINT 需量计算的小数点位数
输入：  ulData  当前的需量值
            uiAddr 对应的RAM地址
返回：  1 表示有更新
            0 表示没有更新
范围：  应用层直接调用
注释：  无
作者：  张龙
版本：  V1.0
最后修改时间：2009-01-19
修改说明：创建
********************************************************************/
uchar  ComPareMaxDemandFromAddr(ulong ulData,ulong ulAddr)
{
#if 0
    // uchar ucValue;
    LongToData4BCD(ulData, &ucDemandTempBuffer[0]);
    switch(MODE_DEMAND_CALC_POINT)
    {
        case MODE_DEMAND_CALC_POINT_2DOT: 
            ucDemandTempBuffer[1]=0;
            ucDemandTempBuffer[0]=0;
            break;
        case MODE_DEMAND_CALC_POINT_3DOT:
            ucDemandTempBuffer[1]=ucDemandTempBuffer[2]&0xf0;
            ucDemandTempBuffer[0]=0;
            break;
        case MODE_DEMAND_CALC_POINT_5DOT:
            ucDemandTempBuffer[0]=ucDemandTempBuffer[3]&0xf0;
            break;
        case MODE_DEMAND_CALC_POINT_6DOT:
            break;
        default: // MODE_DEMAND_CALC_POINT_4DOT 
            ucDemandTempBuffer[0]=0;
            break;
    }
#else
    switch(RAM[RAM_COEF_DEMAND_POINT_NUM])
    {
        case MODE_DEMAND_CALC_POINT_5DOT:
            ulData=((ulData+5)/10)*10;
            break;
        case MODE_DEMAND_CALC_POINT_6DOT:
//  ----6位小数点时，不需要任何操作-----
            break;
//      case MODE_DEMAND_CALC_POINT_1DOT: 
//      case MODE_DEMAND_CALC_POINT_2DOT: 
//      case MODE_DEMAND_CALC_POINT_3DOT:
//      case MODE_DEMAND_CALC_POINT_4DOT:
        default: 
            ulData=((ulData+50)/100)*100;
            break;
    }
    LongToData4BCD(ulData, &ucDemandTempBuffer[0]);
#endif
    if(1==CompareDemand(ulAddr))
    {
        SetmmhhDDMMYYToPoint(&ucDemandTempBuffer[4]);
        memcpy(&RAM[ulAddr], &ucDemandTempBuffer[0], 9);
        FLG_SAVE_MD = 1;
        //CopyDemandRamtoFm2(ulAddr);
        return 1;
    }
    return 0;
}
/*********************************************************************
原型：  void AddOneSecondKwMode(void)
功能：  把每秒钟ADE7758中得到的能量数据累加到需量计算的分钟能量中
参数：  ulPowerBuffer ADE7758中的能量
输入：  无
返回：  无
范围：  应用层直接调用
注释：  无
作者：  张龙
版本：  V1.0
最后修改时间：2009-01-19
修改说明：创建
********************************************************************/
void AddOneSecondKwMode(void)
{
    //if(ucAddoneSecondKwmode_second!=RSOFT_RTC_SECOND)
    {
        //ucAddoneSecondKwmode_second=RSOFT_RTC_SECOND;
        if(ucKwPerSecondCount<60)
        {
            ucKwPerSecondCount++;
            switch(QUADRANT_Z)
            {
                case QUADRANT_TWO:
                        ulKwPerMinute[PTD_KW_R_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_ALLKW];
						ulKwPerMinute[PTD_KVA_R_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_ALLKVA];
                        ulKwPerMinute[PTD_KVAR_Q2_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_ALLKVAR];
                    break;
                case QUADRANT_THREE:
                        ulKwPerMinute[PTD_KW_R_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_ALLKW];
						ulKwPerMinute[PTD_KVA_R_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_ALLKVA];
                        ulKwPerMinute[PTD_KVAR_Q3_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_ALLKVAR];
                    break;
                case QUADRANT_FOUR:
                        ulKwPerMinute[PTD_KW_F_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_ALLKW];
						ulKwPerMinute[PTD_KVA_F_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_ALLKVA];
                        ulKwPerMinute[PTD_KVAR_Q4_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_ALLKVAR];
                    break;
                case QUADRANT_ONE:
                        ulKwPerMinute[PTD_KW_F_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_ALLKW];
						ulKwPerMinute[PTD_KVA_F_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_ALLKVA];
                        ulKwPerMinute[PTD_KVAR_Q1_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_ALLKVAR];
                default:// one
                    break;
            }

            switch(QUADRANT_A)
            {
                case QUADRANT_TWO:
                        ulKwPerMinute[PTD_KW_A_R_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_AKW];
                        ulKwPerMinute[PTD_KVA_A_R_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_AKVA];
                        ulKwPerMinute[PTD_KVAR_A_Q2_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_AKVAR];
                    break;
                case QUADRANT_THREE:
                        ulKwPerMinute[PTD_KW_A_R_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_AKW];
                        ulKwPerMinute[PTD_KVA_A_R_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_AKVA];
                        ulKwPerMinute[PTD_KVAR_A_Q3_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_AKVAR];
                    break;
                case QUADRANT_FOUR:
                        ulKwPerMinute[PTD_KW_A_F_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_AKW];
                        ulKwPerMinute[PTD_KVA_A_F_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_AKVA];
                        ulKwPerMinute[PTD_KVAR_A_Q4_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_AKVAR];
                    break;
                case QUADRANT_ONE:
                        ulKwPerMinute[PTD_KW_A_F_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_AKW];
                        ulKwPerMinute[PTD_KVA_A_F_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_AKVA];
                        ulKwPerMinute[PTD_KVAR_A_Q1_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_AKVAR];
                default:// one
                    break;
            }

            switch(QUADRANT_B)
            {
                case QUADRANT_TWO:
                        ulKwPerMinute[PTD_KW_B_R_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_BKW];
                        ulKwPerMinute[PTD_KVA_B_R_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_BKVA];
                        ulKwPerMinute[PTD_KVAR_B_Q2_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_BKVAR];
                    break;
                case QUADRANT_THREE:
                        ulKwPerMinute[PTD_KW_B_R_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_BKW];
                        ulKwPerMinute[PTD_KVA_B_R_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_BKVA];
                        ulKwPerMinute[PTD_KVAR_B_Q3_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_BKVAR];
                    break;
                case QUADRANT_FOUR:
                        ulKwPerMinute[PTD_KW_B_F_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_BKW];
                        ulKwPerMinute[PTD_KVA_B_F_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_BKVA];
                        ulKwPerMinute[PTD_KVAR_B_Q4_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_BKVAR];
                    break;
                case QUADRANT_ONE:
                        ulKwPerMinute[PTD_KW_B_F_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_BKW];
                        ulKwPerMinute[PTD_KVA_B_F_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_BKVA];
                        ulKwPerMinute[PTD_KVAR_B_Q1_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_BKVAR];
                default:// one
                    break;
            }

            switch(QUADRANT_C)
            {
                case QUADRANT_TWO:
                        ulKwPerMinute[PTD_KW_C_R_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_CKW];
                        ulKwPerMinute[PTD_KVA_C_R_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_CKVA];
                        ulKwPerMinute[PTD_KVAR_C_Q2_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_CKVAR];
                    break;
                case QUADRANT_THREE:
                        ulKwPerMinute[PTD_KW_C_R_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_CKW];
                        ulKwPerMinute[PTD_KVA_C_R_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_CKVA];
                        ulKwPerMinute[PTD_KVAR_C_Q3_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_CKVAR];
                    break;
                case QUADRANT_FOUR:
                        ulKwPerMinute[PTD_KW_C_F_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_CKW];
                        ulKwPerMinute[PTD_KVA_C_F_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_CKVA];
                        ulKwPerMinute[PTD_KVAR_C_Q4_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_CKVAR];
                    break;
                case QUADRANT_ONE:
                        ulKwPerMinute[PTD_KW_C_F_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_CKW];
                        ulKwPerMinute[PTD_KVA_C_F_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_CKVA];
                        ulKwPerMinute[PTD_KVAR_C_Q1_ALL_DATA] += ulPowerBuffer[AD_VIRTUALREG_CKVAR];
                default:// one
                    break;
            }
			
        }

    }
}

/*********************************************************************
原型：  void DemandPulseOut(void)
功能：  需量的脉冲输出
参数：  无
输入：  无
返回：  无
范围：  应用层直接调用
注释：  无
作者：  张龙
版本：  V1.0
最后修改时间：2009-01-19
修改说明：创建
********************************************************************/

void DemandPulseOut(void)
{
    SetPluseValue(PULSE_MODE_DEMANDCYCLE,800);
}


/*********************************************************************
原型：  void DemandPriceChange(void)
功能：  费率切换时，自动清除费率需量的数据
参数：  ucCurrentPriceHEX 当前运行的费率
输入：  无
返回：  无
范围：  应用层直接调用
注释：  无
作者：  张龙
版本：  V1.0
最后修改时间：2009-01-19
修改说明：创建
********************************************************************/
void DemandPriceChange(void)
{
    
    if(ucTempCurrentDemandPrice!=ucCurrentPriceHEX)
    {
        ucTempCurrentDemandPrice=ucCurrentPriceHEX;
        rCurrentPriceDemandPat=0;
        ucDemandClcyePriceHave=0;

    }
}


/*********************************************************************
原型：  void DemandMode(void)
功能：  计算需量的主体函数
参数：  无
输入：  无
返回：  无
范围：  应用层直接调用
注释：  无
作者：  张龙
版本：  V1.0
最后修改时间：2009-01-19
修改说明：创建
********************************************************************/
void DemandMode(void)
{
    ulong ulSum;
    ulong uiData;
    uchar ucTemp;
    uchar ucLen,ucPoint;
    ulong ulTemp;
    
    AddOneSecondKwMode();
    
    if(ucDemandModeMinute!=RSOFT_RTC_MINUTE)
    {
        ucDemandModeMinute=RSOFT_RTC_MINUTE;
        if(ucDemandPulseMinute<ucDemandClcye)
        {
            ucDemandPulseMinute++;
        }
        // 满足一个需量周期
        if(ucDemandPulseMinute>=ucDemandClcye)
        {
            ucDemandPulseMinute=0;
            ucDemandOneClcyeFlg=GAL_YES;
            if(DEMAND_PULSE_MODE0==DEMAND_PULSE_MODE) // xuliang zhou qi mochong
            {
                DemandPulseOut();
            }
        }
        if(ucDemandClcyeStart>=(ucDemandClcye-1))
        {
            ucDemandClcyeStart=0;
        }
        else
        {
            ucDemandClcyeStart++;
        }
        // AA   计算当前1分钟的数据      AA
        for(ucPoint=0;ucPoint<PTD_DEMAND_COUNT;ucPoint++)
        {
            if(0==ucKwPerSecondCount)
            {
                uiData=0;
            }
            else
            {
                uiData=(ulKwPerMinute[ucPoint]+30)/ucKwPerSecondCount;
                uiData=(uiData+50)/100;
            }
            ulKwPerMinute[ucPoint]=0;
            uiDemandClacBuffer[ucPoint][ucDemandClcyeStart]=uiData;
        }
        // AA   总的当前的需量周期中的数据     AA
        ucDemandClcyeAllHave++;
        if(ucDemandClcyeAllHave>=ucDemandClcye)
        {
            ucDemandClcyeAllHave=ucDemandClcye;
        }
        // AA   费率的当前的需量周期中的数据     AA
        ucDemandClcyePriceHave++;
        if(ucDemandClcyePriceHave>=ucDemandClcye)
        {
            ucDemandClcyePriceHave=ucDemandClcye;
        }
            
        ucKwPerSecondCount=0;
        
        rCurrentDemandPat++;
        // 满足一个滑差时间
        if(rCurrentDemandPat>=ucDemandPat)
        {
            rCurrentDemandPat=0;
             // AA  组合无功的数据清零  AA
            memset(&ulDemandClacKvarC1C2SumBuffer[0],0x00, 4*(PTD_KVAR_C1C2_COUNT-2));
            if((GAL_YES==ucDemandOneClcyeFlg)&&(0!=ucDemandClcyeAllHave))
            {
                if(DEMAND_PULSE_MODE1==DEMAND_PULSE_MODE) // xuliang zhou qi mochong
                {
                    DemandPulseOut();
                }
                
                for(ucPoint=0;ucPoint<PTD_DEMAND_COUNT;ucPoint++)
                {
                    ulSum=0;
                    memset(&ucDemandTempBuffer[0],0x00, 4);
                    ucLen=ucDemandClcyeStart;
                    for(ucTemp=0;ucTemp<ucDemandClcyeAllHave;ucTemp++)
                    {
                        ulSum +=uiDemandClacBuffer[ucPoint][ucLen];
                        if(0==ucLen)
                        {
                            ucLen=ucDemandClcye-1;
                        }
                        else
                        {
                            ucLen--;
                        }
                    }
                    ulSum=(ulSum+ucDemandClcye/2)/ucDemandClcye;
                    ulSum=ClacDemandFromPower(ulSum);
                    ComPareMaxDemandFromAddr(ulSum,TB_DEMAND_CLAC[ucPoint].ucAllStartAddr);
                    // 更新内存中的需量实时量
                    if(ucPoint<=PTD_KVAR_Q4_ALL_DATA)   
                    {
                        memcpy(&RAM[RAM_CURRENT_DEMAND_KW_F+4*ucPoint], &ucDemandTempBuffer[0],4);
                    }
					if(PTD_KVA_F_ALL_DATA==ucPoint)
					{
						memcpy(&RAM[RAM_CURRENT_DEMAND_KVA_F], &ucDemandTempBuffer[0],4);
					}
					if(PTD_KVA_R_ALL_DATA==ucPoint)
					{
						memcpy(&RAM[RAM_CURRENT_DEMAND_KVA_R], &ucDemandTempBuffer[0],4);
					}
                    // 分象限无功最大需量作为组合无功最大需量
                    if((ucPoint>=PTD_KVAR_Q1_ALL_DATA)&&(ucPoint<=PTD_KVAR_Q4_ALL_DATA))
                    {
                        switch(ucPoint)
                        {
                            case PTD_KVAR_Q1_ALL_DATA:
                                if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ1)
                                {
                                    if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C1_ALL_DATA]<ulSum)
                                        ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C1_ALL_DATA]=ulSum;
                                }
                                if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ1)
                                {
                                    if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C2_ALL_DATA]<ulSum)
                                        ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C2_ALL_DATA]=ulSum;
                                }
                                break;
                            case PTD_KVAR_Q2_ALL_DATA:
                                if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ2)
                                {
                                    if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C1_ALL_DATA]<ulSum)
                                        ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C1_ALL_DATA]=ulSum;
                                }
                                if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ2)
                                {
                                    if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C2_ALL_DATA]<ulSum)
                                        ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C2_ALL_DATA]=ulSum;
                                }
                                break;
                            case PTD_KVAR_Q3_ALL_DATA:
                                if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ3)
                                {
                                    if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C1_ALL_DATA]<ulSum)
                                        ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C1_ALL_DATA]=ulSum;
                                }
                                if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ3)
                                {
                                    if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C2_ALL_DATA]<ulSum)
                                        ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C2_ALL_DATA]=ulSum;
                                }
                                break;
                            case PTD_KVAR_Q4_ALL_DATA:
                                if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ4)
                                {
                                    if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C1_ALL_DATA]<ulSum)
                                        ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C1_ALL_DATA]=ulSum;
                                }
                                if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ4)
                                {
                                    if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C2_ALL_DATA]<ulSum)
                                        ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C2_ALL_DATA]=ulSum;
                                }
                                break;
                        }
                    }   
					if((ucPoint>=PTD_KVAR_A_Q1_ALL_DATA)&&(ucPoint<=PTD_KVAR_A_Q4_ALL_DATA))
					{
						switch(ucPoint)
						{
							case PTD_KVAR_A_Q1_ALL_DATA:
								if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ1)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_A_C1_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_A_C1_ALL_DATA]=ulSum;
								}
								if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ1)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_A_C2_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_A_C2_ALL_DATA]=ulSum;
								}
								break;
							case PTD_KVAR_A_Q2_ALL_DATA:
								if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ2)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_A_C1_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_A_C1_ALL_DATA]=ulSum;
								}
								if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ2)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_A_C2_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_A_C2_ALL_DATA]=ulSum;
								}
								break;
							case PTD_KVAR_A_Q3_ALL_DATA:
								if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ3)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_A_C1_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_A_C1_ALL_DATA]=ulSum;
								}
								if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ3)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_A_C2_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_A_C2_ALL_DATA]=ulSum;
								}
								break;
							case PTD_KVAR_A_Q4_ALL_DATA:
								if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ4)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_A_C1_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_A_C1_ALL_DATA]=ulSum;
								}
								if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ4)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_A_C2_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_A_C2_ALL_DATA]=ulSum;
								}
								break;
						}
					}
					if((ucPoint>=PTD_KVAR_B_Q1_ALL_DATA)&&(ucPoint<=PTD_KVAR_B_Q4_ALL_DATA))
					{
						switch(ucPoint)
						{
							case PTD_KVAR_B_Q1_ALL_DATA:
								if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ1)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_B_C1_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_B_C1_ALL_DATA]=ulSum;
								}
								if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ1)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_B_C2_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_B_C2_ALL_DATA]=ulSum;
								}
								break;
							case PTD_KVAR_B_Q2_ALL_DATA:
								if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ2)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_B_C1_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_B_C1_ALL_DATA]=ulSum;
								}
								if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ2)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_B_C2_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_B_C2_ALL_DATA]=ulSum;
								}
								break;
							case PTD_KVAR_B_Q3_ALL_DATA:
								if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ3)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_B_C1_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_B_C1_ALL_DATA]=ulSum;
								}
								if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ3)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_B_C2_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_B_C2_ALL_DATA]=ulSum;
								}
								break;
							case PTD_KVAR_B_Q4_ALL_DATA:
								if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ4)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_B_C1_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_B_C1_ALL_DATA]=ulSum;
								}
								if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ4)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_B_C2_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_B_C2_ALL_DATA]=ulSum;
								}
								break;
						}
					}
					if((ucPoint>=PTD_KVAR_C_Q1_ALL_DATA)&&(ucPoint<=PTD_KVAR_C_Q4_ALL_DATA))
					{
						switch(ucPoint)
						{
							case PTD_KVAR_C_Q1_ALL_DATA:
								if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ1)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C_C1_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C_C1_ALL_DATA]=ulSum;
								}
								if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ1)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C_C2_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C_C2_ALL_DATA]=ulSum;
								}
								break;
							case PTD_KVAR_C_Q2_ALL_DATA:
								if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ2)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C_C1_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C_C1_ALL_DATA]=ulSum;
								}
								if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ2)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C_C2_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C_C2_ALL_DATA]=ulSum;
								}
								break;
							case PTD_KVAR_C_Q3_ALL_DATA:
								if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ3)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C_C1_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C_C1_ALL_DATA]=ulSum;
								}
								if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ3)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C_C2_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C_C2_ALL_DATA]=ulSum;
								}
								break;
							case PTD_KVAR_C_Q4_ALL_DATA:
								if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ4)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C_C1_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C_C1_ALL_DATA]=ulSum;
								}
								if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ4)
								{
									if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C_C2_ALL_DATA]<ulSum)
										ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C_C2_ALL_DATA]=ulSum;
								}
								break;
						}
					}
				}

                // 判断需量超限事件
                //for(ucPoint=0;ucPoint<=PTD_KVAR_Q4_ALL_DATA;ucPoint++)
				for(ucPoint=0;ucPoint<DEMAND_OVER_NUM;ucPoint++)
                {
                    DemandOverMode(ucPoint);
                }
             } 
            // 判断组合无功1、2最大需量
            ComPareMaxDemandFromAddr(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C1_ALL_DATA],RAM_KVAR_C1_ALL_DATA);
			memcpy(&RAM[RAM_CURRENT_DEMAND_KVAR_C1], &ucDemandTempBuffer[0],4);
            ComPareMaxDemandFromAddr(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C2_ALL_DATA],RAM_KVAR_C2_ALL_DATA);
			memcpy(&RAM[RAM_CURRENT_DEMAND_KVAR_C2], &ucDemandTempBuffer[0],4);
			ComPareMaxDemandFromAddr(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_A_C1_ALL_DATA],RAM_KVAR_A_C1_ALL_DATA);
			ComPareMaxDemandFromAddr(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_A_C2_ALL_DATA],RAM_KVAR_A_C2_ALL_DATA);
			ComPareMaxDemandFromAddr(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_B_C1_ALL_DATA],RAM_KVAR_B_C1_ALL_DATA);
			ComPareMaxDemandFromAddr(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_B_C2_ALL_DATA],RAM_KVAR_B_C2_ALL_DATA);
			ComPareMaxDemandFromAddr(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C_C1_ALL_DATA],RAM_KVAR_C_C1_ALL_DATA);
			ComPareMaxDemandFromAddr(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C_C2_ALL_DATA],RAM_KVAR_C_C2_ALL_DATA);
            // AA  有功需量(含方向)  AA 
            ulTemp=Bcd4DataToLong(&RAM[RAM_CURRENT_DEMAND_KW_F]);
            ulSum=Bcd4DataToLong(&RAM[RAM_CURRENT_DEMAND_KW_R]);
            if(ulTemp>=ulSum)
            {
                ulTemp=ulTemp-ulSum;
                LongToData4BCD(ulTemp, &RAM[RAM_CURRENT_DEMAND_KW_TOTAL]);
            }
            else
            {
                ulTemp=ulSum-ulTemp;
                LongToData4BCD(ulTemp, &RAM[RAM_CURRENT_DEMAND_KW_TOTAL]);
                RAM[RAM_CURRENT_DEMAND_KW_TOTAL+3] |=0x80;
            }
            
            // AA  无功需量(含方向)  AA         
            ulTemp=Bcd4DataToLong(&RAM[RAM_CURRENT_DEMAND_KVAR_Q1])+Bcd4DataToLong(&RAM[RAM_CURRENT_DEMAND_KVAR_Q2]);
            ulSum=Bcd4DataToLong(&RAM[RAM_CURRENT_DEMAND_KVAR_Q3])+Bcd4DataToLong(&RAM[RAM_CURRENT_DEMAND_KVAR_Q4]);
            if(ulTemp>=ulSum)
            {
                ulTemp=ulTemp-ulSum;
                LongToData4BCD(ulTemp, &RAM[RAM_CURRENT_DEMAND_KVAR_TOTAL]);
            }
            else
            {
                ulTemp=ulSum-ulTemp;
                LongToData4BCD(ulTemp, &RAM[RAM_CURRENT_DEMAND_KVAR_TOTAL]);
                RAM[RAM_CURRENT_DEMAND_KVAR_TOTAL+3] |=0x80;
            }
			
			// AA  视在需量(含方向)  AA			
			ulTemp=Bcd4DataToLong(&RAM[RAM_CURRENT_DEMAND_KVA_F]);
			ulSum=Bcd4DataToLong(&RAM[RAM_CURRENT_DEMAND_KVA_R]);
			if(ulTemp>=ulSum)
			{
				ulTemp=ulTemp-ulSum;
				LongToData4BCD(ulTemp, &RAM[RAM_CURRENT_DEMAND_KVA_TOTAL]);
			}
			else
			{
				ulTemp=ulSum-ulTemp;
				LongToData4BCD(ulTemp, &RAM[RAM_CURRENT_DEMAND_KVA_TOTAL]);
				RAM[RAM_CURRENT_DEMAND_KVA_TOTAL+3] |=0x80;
        }
        
		}
        // AA  当前1分钟有功平均功率(含方向)  AA            
        ulTemp=uiDemandClacBuffer[PTD_KW_F_ALL_DATA][ucDemandClcyeStart];
        ulSum=uiDemandClacBuffer[PTD_KW_R_ALL_DATA][ucDemandClcyeStart];
        if(ulTemp>=ulSum)
        {
            ulTemp=ulTemp-ulSum;
            ulTemp=ClacDemandFromPower(ulTemp);
            LongToData4BCD(ulTemp, &RAM[RAM_AVERAGE_KW_ALL]);
        }
        else
        {
            ulTemp=ulSum-ulTemp;
            ulTemp=ClacDemandFromPower(ulTemp);
            LongToData4BCD(ulTemp, &RAM[RAM_AVERAGE_KW_ALL]);
            RAM[RAM_AVERAGE_KW_ALL+3] |=0x80;
        }
        if(GAL_YES==ucDemandPriceDemandTimeChange)
        {
            ucDemandPriceDemandTimeChange=GAL_NO;
            rCurrentPriceDemandPat=0;
            ucDemandClcyePriceHave=0;
        }
        rCurrentPriceDemandPat++;
        if(rCurrentPriceDemandPat>=ucDemandPat)
        {
            // aa 滑差时间到了 aa 
            rCurrentPriceDemandPat=0;
            memset(&ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C1_PRICE_DATA],0x00, 4*2);

            if((GAL_YES==ucDemandOneClcyeFlg)&&(ucDemandClcyePriceHave==ucDemandClcye))
            {
                // AA  只做有费率的那几个数据    AA
				 for(ucPoint=0;ucPoint<PTD_KW_A_F_ALL_DATA;ucPoint++)
                {
                    ulSum=0;
                    ucLen=ucDemandClcyeStart;
                    for(ucTemp=0;ucTemp<ucDemandClcyePriceHave;ucTemp++)
                    {
                        ulSum +=uiDemandClacBuffer[ucPoint][ucLen];
                        if(0==ucLen)
                        {
                            ucLen=ucDemandClcye-1;
                        }
                        else
                        {
                            ucLen--;
                        }
                    }
                    ulSum=(ulSum+ucDemandClcye/2)/ucDemandClcye;
                    ulSum=ClacDemandFromPower(ulSum);
                    ComPareMaxDemandFromAddr(ulSum,(TB_DEMAND_CLAC[ucPoint].ucAllStartAddr+9*ucTempCurrentDemandPrice));
                    if((ucPoint>=PTD_KVAR_Q1_ALL_DATA)&&(ucPoint<=PTD_KVAR_Q4_ALL_DATA))
                    {
                        switch(ucPoint)
                        {
                            case PTD_KVAR_Q1_ALL_DATA:
                                if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ1)
                                {
                                    if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C1_PRICE_DATA]<ulSum)
                                        ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C1_PRICE_DATA]=ulSum;
                                }
                                if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ1)
                                {
                                    if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C2_PRICE_DATA]<ulSum)
                                        ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C2_PRICE_DATA]=ulSum;
                                }
                                break;
                            case PTD_KVAR_Q2_ALL_DATA:
                                if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ2)
                                {
                                    if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C1_PRICE_DATA]<ulSum)
                                        ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C1_PRICE_DATA]=ulSum;
                                }
                                if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ2)
                                {
                                    if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C2_PRICE_DATA]<ulSum)
                                        ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C2_PRICE_DATA]=ulSum;
                                }
                                break;
                            case PTD_KVAR_Q3_ALL_DATA:
                                if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ3)
                                {
                                    if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C1_PRICE_DATA]<ulSum)
                                        ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C1_PRICE_DATA]=ulSum;
                                }
                                if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ3)
                                {
                                    if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C2_PRICE_DATA]<ulSum)
                                        ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C2_PRICE_DATA]=ulSum;
                                }
                                break;
                            case PTD_KVAR_Q4_ALL_DATA:
                                if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ4)
                                {
                                    if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C1_PRICE_DATA]<ulSum)
                                        ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C1_PRICE_DATA]=ulSum;
                                }
                                if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ4)
                                {
                                    if(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C2_PRICE_DATA]<ulSum)
                                        ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C2_PRICE_DATA]=ulSum;
                                }
                                break;
                        }
                    }               
                }
                ComPareMaxDemandFromAddr(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C1_PRICE_DATA],RAM_KVAR_C1_ALL_DATA+BYTES_PER_DEMAND*ucTempCurrentDemandPrice);
                ComPareMaxDemandFromAddr(ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C2_PRICE_DATA],RAM_KVAR_C2_ALL_DATA+BYTES_PER_DEMAND*ucTempCurrentDemandPrice);
            }

        }
        DemandPriceChange();
        if(FLG_DEMAND_OVER_ALL_STATUS>0)
        {
            FLG_DEMANDOVER_STATUS=GAL_YES;
        }
        else
        {
            FLG_DEMANDOVER_STATUS=GAL_NO;
        }
    }


}




/*********************************************************************
原型：  void DemandResume(void)
功能：  上电时，需量数据恢复
参数：  无
输入：  无
返回：  无
范围：  应用层直接调用
注释：  无
作者：  张龙
版本：  V1.0
最后修改时间：2009-01-19
修改说明：创建
********************************************************************/
void DemandResume(void)
{
    uchar ucTemp;
    u16 uiDataStart;
	for(ucTemp=0;ucTemp<18;ucTemp++)
    {
        uiDataStart=ucTemp;
        uiDataStart=uiDataStart*90;
        if(0==ReadDataDirect(EPL_DEMAND_DATA_START+uiDataStart, 90, &RAM[RAM_DEMAND_DATA_START+ uiDataStart]))
        {
            ReadDataDirect(EPL_DEMAND_DATA_START+uiDataStart, 90, &RAM[RAM_DEMAND_DATA_START+ uiDataStart]);
        }
    }
}


void SaveMDByTimeStamp(void)
{
    WriteDataDirect(&RAM[RAM_DEMAND_DATA_START],EPL_DEMAND_DATA_START , BYTES_DEMAND_TOTAL);
}
    


/*********************************************************************
原型：  uchar DemandDataClrAllCurrent(void)
功能：  所有当前需量数据清零
参数：  无
输入：  无
返回：  无
范围：  应用层直接调用
注释：  无
作者：  张龙
版本：  V1.0
最后修改时间：2009-01-19
修改说明：创建
********************************************************************/
uchar DemandDataClrAllCurrent(void)
{
    
    //uchar ucTemp;
    //u16 uiDataStart;
    // 清当前需量，RAM和铁电中的
    memset(&RAM[RAM_DEMAND_DATA_START], 0x00, BYTES_DEMAND_TOTAL);
    WriteDataDirect(&RAM[RAM_DEMAND_DATA_START], EPL_DEMAND_DATA_START, BYTES_DEMAND_TOTAL );
    DemandDataInit();
    

    return 1;
}

ulong ulDemandOverKwStart;
ulong ulDemandOverKvarStart;
//uchar ucDemandOverStartTime;
//uchar ucDemandOverContineTime[DEMAND_OVER_NUM]; //it is not needed, since there is no total time

void DemandOverParaInit(void)
{
    ReadCoefDataWithCheck(EPL_COEF_DEMAND_OVER_CONDITION, 7, Ap_temp, 1);
    ulDemandOverKwStart=HexFromRam3Bcd(Ap_temp);
    ulDemandOverKvarStart=HexFromRam3Bcd(Ap_temp+3);// xx dot xx
    /*
    ucDemandOverStartTime=HexFromRam1Bcd((Ap_temp+6));
    if(ucDemandOverStartTime<CONFIG_METER_EVENT_DELAY_MIN_TIME)
        ucDemandOverStartTime=CONFIG_METER_EVENT_DELAY_MIN_TIME;
    ucDemandOverContineTime[]=0;
    */
    
}

void DemandOverInit(void)
{
    FLG_DEMANDOVER_STATUS=GAL_NO;
    FLG_DEMAND_OVER_ALL_STATUS=GAL_NO;
    DemandOverParaInit();
    // add by ybf 2010.08.26
    memset((uchar*)&DemandOverData[0],0x00,sizeof(DemandOverData[DEMAND_OVER_NUM]));
}


void DemandOverStart(uchar ucType)
{
    ulong ulDataAddr;
    FLG_DEMAND_OVER_ALL_STATUS |= (1<<ucType);
    Data3ByteBCDAdd1(EPL_DEMAND_OVER_KW_F_COUNT+4*ucType);
    
    ulDataAddr=SetTwoTableNextPoint(TYPE_DEMAND_OVER_KW_F_RECORD+ucType);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetTimeDataToPoint(&Wr_data[0]);
        memset(&Wr_data[6],0,15);
        WriteDataDirect(&Wr_data[0], ulDataAddr,  21);
        DemandStorNowTime();
        memcpy((uchar*)&DemandOverData[ucType],&ucDemandTempBuffer[0] ,sizeof(ST_DEMAND_OVER_DATA));
    }
    ClrFlashMode();
}
void DemandOverStopIfStart(void)
{
    uchar ucTemp;
    for(ucTemp=0;ucTemp<8;ucTemp++)
    {
        if(0!=((1<<ucTemp)&FLG_DEMAND_OVER_ALL_STATUS))
        {
            DemandOverEnd(ucTemp);
        }
    }
    
}
void DemandOverEnd(uchar ucType)
{
    ulong ulDataAddr;
    FLG_DEMAND_OVER_ALL_STATUS &= ~(1<<ucType);
    ulDataAddr=GetTwoTableAddrFromBlock(TYPE_DEMAND_OVER_KW_F_RECORD+ucType,0,6);
    if(GAL_GETTWOTABLE_ADDRERR != ulDataAddr)
    {
        SetTimeDataToPoint(&Wr_data[0]);
        // modified by ybf 100826
        memcpy(&Wr_data[6],(uchar*)&DemandOverData[ucType],sizeof(ST_DEMAND_OVER_DATA));
        WriteDataDirect(&Wr_data[0], ulDataAddr,  15);
        memset((uchar*)&DemandOverData[ucType],0x00,sizeof(ST_DEMAND_OVER_DATA));
    }
}

// 如果当前需量超限值大于记录时刻的需量超限值，更新需量
void DemandOverChange(uchar ucType)
{
    memcpy( &RAM[RAM_COEF_TEMP_CLACUSE],(uchar*)&DemandOverData[ucType],4);
    if(1==CompareDemand(RAM_COEF_TEMP_CLACUSE))
    {
        DemandStorNowTime();
        memcpy((uchar*)&DemandOverData[ucType],&ucDemandTempBuffer[0] ,sizeof(ST_DEMAND_OVER_DATA));
    }
}

// 需量超限事件记录
void DemandOverMode(uchar ucDemandType)
{
    ulong ulDataJudue;
    uchar ucCurrentStatus;
    uchar ucNeedRecord;
    ulong ulDataIn;
    if(ucDemandType>=DEMAND_OVER_NUM)
        return ;
    
    memcpy(&ucDemandTempBuffer[0], &RAM[RAM_CURRENT_DEMAND_KW_F+4*ucDemandType], 4);
    ulDataIn=Bcd3DataToLong(&ucDemandTempBuffer[1]);    // 需量值

    // 需量下限
    if(ucDemandType<2)   //ZD =2时，为无功需量
        ulDataJudue = ulDemandOverKwStart;
    else
        ulDataJudue = ulDemandOverKvarStart;
    
    ucCurrentStatus=FLG_DEMAND_OVER_ALL_STATUS&(1<<ucDemandType);
    ucNeedRecord=GAL_YES;
    // 当前需量超限
    if(ulDataIn>ulDataJudue)
    {
        if(GAL_NO==ucCurrentStatus)
        {
            DemandOverStart(ucDemandType);
            ucNeedRecord=GAL_NO;
        }
    }
    // 当前需量未超限
    else
    {
        if(GAL_NO != ucCurrentStatus)
        {
            DemandOverEnd(ucDemandType);
        }
    }
    // ---判断是否需要更新最大需量-----
    if((GAL_NO != ucCurrentStatus)&&(GAL_YES==ucNeedRecord))
    {
        DemandOverChange(ucDemandType);
    }
}

