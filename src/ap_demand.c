
#define AP_DEMAND_GLOBALS
#include "common.h"


//uchar ucAddoneSecondKwmode_second;
// AA �����L�� AA
uchar ucDemandClcye;    
// AA ����r�g   AA
uchar ucDemandPat;



uchar rCurrentDemandPat;
uchar rCurrentPriceDemandPat;
uchar ucDemandTempBuffer[9];
uchar ucDemandOneClcyeFlg;
uchar ucDemandPulseMinute;

uchar ucDemandModeMinute;
//uchar ucDemandModeSecond;
// AA  ��ǰ�������ݻ�����������ָ��  AA
uchar ucDemandClcyeStart;   
// AA  ��ǰ��������������Ч��������   AA
uchar ucDemandClcyeAllHave;
// AA  ��ǰ������������������Ч��������   AA
uchar ucDemandClcyePriceHave;

typedef struct
{
    uchar ucStartAddr;
    uchar ucHaveAllNum;
    uchar ucHavePriceNum;
}ST_DEMAND_POINT_PARAM;
typedef struct
{
    uchar ucDemandTpye; //  AA ��������  AA
    uchar ucCanSub;         //  AA �Ƿ��м���  AA
    ulong ucAllStartAddr;       //  AA RAM ��ַ----�ܵ�ָ��  AA
    ulong ucPriceStartAddr; //  AA RAM ��ַ---- ���ʵ�ָ��  AA
}ST_DEMAND_CLAC_PARAM;

// AA   û�з�������   AA
#define DEMAND_PRICE_NO_HAVE        0xFFFFFFFF
// AA  ��������ʱ��ֻ�мӵĹ��ܣ�û�м��Ĺ���    AA
#define DEMAND_CLAC_ONLYADD         0x00
// AA  ���������У��м�Ҳ�м�    AA
#define DEMAND_CLAC_CANSUB      0x01
const ST_DEMAND_CLAC_PARAM TB_DEMAND_CLAC[PTD_DEMAND_COUNT]=
{
    // AA ������������,�ۼӷ�ʽ,         �ܵ�RAM����ָ��,   ���ʵ�RAM���� ָ��
    {PTD_KW_F_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KW_F_ALL_DATA , RAM_KW_F_F1_DATA }, // 0 AA ��ǰ�����й����������ָ�� AA
    {PTD_KW_R_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KW_R_ALL_DATA , RAM_KW_R_F1_DATA }, // 1 AA ��ǰ�����й����������ָ�� AA
	{PTD_KVAR_Q1_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_Q1_ALL_DATA , RAM_KVAR_Q1_F1_DATA }, // 4 AA ��ǰ1�����޹����������ָ�� AA
	{PTD_KVAR_Q2_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_Q2_ALL_DATA , RAM_KVAR_Q2_F1_DATA }, // 5 AA ��ǰ2�����޹����������ָ�� AA
	{PTD_KVAR_Q3_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_Q3_ALL_DATA , RAM_KVAR_Q3_F1_DATA} , // 6 AA ��ǰ3�����޹����������ָ�� AA
	{PTD_KVAR_Q4_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_Q4_ALL_DATA , RAM_KVAR_Q4_F1_DATA} , // 7 AA ��ǰ4�����޹����������ָ�� AA
	{PTD_KVA_F_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVA_F_ALL_DATA , RAM_KVA_F_F1_DATA} , // 8 AA ��ǰ�����������������ָ�� AA
	{PTD_KVA_R_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVA_R_ALL_DATA , RAM_KVA_R_F1_DATA} , // 9 AA ��ǰ�����������������ָ�� AA
	{PTD_KW_A_F_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KW_A_F_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 10 AA ��ǰA�������й��������ָ�� AA
	{PTD_KW_A_R_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KW_A_R_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 11 AA ��ǰA�෴���й��������ָ�� AA
	{PTD_KVAR_A_Q1_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_A_Q1_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 14 AA ��ǰA��1�����޹��������ָ�� AA
	{PTD_KVAR_A_Q2_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_A_Q2_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 15 AA ��ǰA��2�����޹��������ָ�� AA
	{PTD_KVAR_A_Q3_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_A_Q3_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 16 AA ��ǰA��3�����޹��������ָ�� AA
	{PTD_KVAR_A_Q4_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_A_Q4_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 17 AA ��ǰA��4�����޹��������ָ�� AA
	{PTD_KVA_A_F_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVA_A_F_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 18 AA ��ǰA�����������������ָ�� AA
	{PTD_KVA_A_R_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVA_A_R_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 19 AA ��ǰA�෴�������������ָ�� AA
	{PTD_KW_B_F_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KW_B_F_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 20 AA ��ǰB�������й��������ָ�� AA
	{PTD_KW_B_R_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KW_B_R_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 21 AA ��ǰB�෴���й��������ָ�� AA
	{PTD_KVAR_B_Q1_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_B_Q1_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 24 AA ��ǰB��1�����޹��������ָ�� AA
	{PTD_KVAR_B_Q2_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_B_Q2_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 25 AA ��ǰB��2�����޹��������ָ�� AA
	{PTD_KVAR_B_Q3_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_B_Q3_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 26 AA ��ǰB��3�����޹��������ָ�� AA
	{PTD_KVAR_B_Q4_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_B_Q4_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 27 AA ��ǰB��4�����޹��������ָ�� AA
	{PTD_KVA_B_F_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVA_B_F_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 28 AA ��ǰB�����������������ָ�� AA
	{PTD_KVA_B_R_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVA_B_R_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 29 AA ��ǰB�෴�������������ָ�� AA
	{PTD_KW_C_F_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KW_C_F_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 30 AA ��ǰC�������й��������ָ�� AA
	{PTD_KW_C_R_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KW_C_R_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 31 AA ��ǰC�෴���й��������ָ�� AA
	{PTD_KVAR_C_Q1_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_C_Q1_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 34 AA ��ǰC��1�����޹��������ָ�� AA
	{PTD_KVAR_C_Q2_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_C_Q2_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 35 AA ��ǰC��2�����޹��������ָ�� AA
	{PTD_KVAR_C_Q3_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_C_Q3_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 36 AA ��ǰC��3�����޹��������ָ�� AA
	{PTD_KVAR_C_Q4_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVAR_C_Q4_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 37 AA ��ǰC��4�����޹��������ָ�� AA
	{PTD_KVA_C_F_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVA_C_F_ALL_DATA , DEMAND_PRICE_NO_HAVE} , // 38 AA ��ǰC�����������������ָ�� AA
	{PTD_KVA_C_R_ALL_DATA , DEMAND_CLAC_ONLYADD , RAM_KVA_C_R_ALL_DATA , DEMAND_PRICE_NO_HAVE} // 39 AA ��ǰC�෴�������������ָ�� AA
};

void DemandParaInit(void)
{
    ReadCoefDataWithCheck(EPL_DEMAND_CYCLE_TIME, 2, Ap_temp, 1);

    if((Ap_temp[0] >= 1) && (Ap_temp[0] <= 0x60) && ((Ap_temp[0] & 0x0f) <= 0x09))
    {								//�������ڴ���0��С��0x60��BCD�룩����λ��������9��������Ч
        ucDemandClcye=HexFromRam1Bcd(Ap_temp);
    }
    else 
    {								//���������ָ�Ĭ�ϲ���
        ucDemandClcye=15;
    }
    if((Ap_temp[1] >= 1) && (Ap_temp[1] <= ucDemandClcye) && ((Ap_temp[0] & 0x0f) <= 0x09)) //<=60
    {								//����ʱ�����0��С��0x60��BCD�룩����λ��������9��������Ч
        ucDemandPat=HexFromRam1Bcd(Ap_temp+1);
    }
    else
    {								//���������ָ�Ĭ�ϲ���
        ucDemandPat=1;
    }
	if((ucDemandClcye % ucDemandPat) != 0)
	{							//���������ָ�Ĭ��ֵ
		//ucDemandClcye=15;
		//ucDemandPat=1;
	}
    //MTRACE("DemandParaInit %d, %d\n", ucDemandClcye, ucDemandPat);
    //uuReactiveMode01.ucData = RAM[RAM_CHARACTER_REACTIVE01];
    //uuReactiveMode02.ucData = RAM[RAM_CHARACTER_REACTIVE02];
}

// ST_DEMAND_POINT_PARAM rCurrentDemandPoint[PTD_DEMAND_COUNT];
/*********************************************************************
ԭ�ͣ�void DemandDataInit(void);
���ܣ���ʼ����������
��������
���룺��
���أ���
��Χ��Ӧ�ò�ֱ�ӵ���
ע�ͣ���
���ߣ�����
�汾��V1.0
����޸�ʱ�䣺2009-01-19
�޸�˵��������
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
ԭ�ͣ�ulong ClacDemandFromPower(ulong value)
���ܣ��Ѽ���õ�ADE7758��������ת��Ϊ��������
������
���룺value �������������
���أ�����֮��Ĺ������ݡ�
��Χ��Ӧ�ò�ֱ�ӵ���
ע�ͣ���
���ߣ�����
�汾��V1.0
����޸�ʱ�䣺2009-01-19
�޸�˵��������
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
ԭ�ͣ�uchar CompareDemand(u16 uiAddr)
���ܣ��Ƚϵ�ǰ������uiAddr����Ӧ��RAM ��ַ��Ӧ�������Ĵ�С
������ucDemandTempBuffer[] ��ǰ��������Ϣ����
���룺uiAddr ָ����RAM ��ַ
���أ����ucDemandTempBuffer�����ݴ���Ϊ1�� ����Ϊ0
��Χ��Ӧ�ò�ֱ�ӵ���
ע�ͣ���
���ߣ�����
�汾��V1.0
����޸�ʱ�䣺2009-01-19
�޸�˵��������
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
ԭ�ͣ�void  DemandStorNowTime(void)
���ܣ��ѵ�ǰ��ʱ����Ϣд��ucDemandTempBuffer ��
��������
���룺�� 
���أ���
��Χ��Ӧ�ò�ֱ�ӵ���
ע�ͣ���
���ߣ�����
�汾��V1.0
����޸�ʱ�䣺2009-01-19
�޸�˵��������
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
ԭ�ͣ�  uchar  ComPareMaxDemandFromAddr(ulong ulData,ulong ulAddr)
���ܣ�  ������ǰ����ֵ��Ҫ�Ƚϵ�RAM ��ַ��
            �����ǰ������ֵ�����������
            ͬʱ��¼��Ӧ��ʱ��
������  MODE_DEMAND_CALC_POINT ���������С����λ��
���룺  ulData  ��ǰ������ֵ
            uiAddr ��Ӧ��RAM��ַ
���أ�  1 ��ʾ�и���
            0 ��ʾû�и���
��Χ��  Ӧ�ò�ֱ�ӵ���
ע�ͣ�  ��
���ߣ�  ����
�汾��  V1.0
����޸�ʱ�䣺2009-01-19
�޸�˵��������
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
//  ----6λС����ʱ������Ҫ�κβ���-----
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
ԭ�ͣ�  void AddOneSecondKwMode(void)
���ܣ�  ��ÿ����ADE7758�еõ������������ۼӵ���������ķ���������
������  ulPowerBuffer ADE7758�е�����
���룺  ��
���أ�  ��
��Χ��  Ӧ�ò�ֱ�ӵ���
ע�ͣ�  ��
���ߣ�  ����
�汾��  V1.0
����޸�ʱ�䣺2009-01-19
�޸�˵��������
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
ԭ�ͣ�  void DemandPulseOut(void)
���ܣ�  �������������
������  ��
���룺  ��
���أ�  ��
��Χ��  Ӧ�ò�ֱ�ӵ���
ע�ͣ�  ��
���ߣ�  ����
�汾��  V1.0
����޸�ʱ�䣺2009-01-19
�޸�˵��������
********************************************************************/

void DemandPulseOut(void)
{
    SetPluseValue(PULSE_MODE_DEMANDCYCLE,800);
}


/*********************************************************************
ԭ�ͣ�  void DemandPriceChange(void)
���ܣ�  �����л�ʱ���Զ������������������
������  ucCurrentPriceHEX ��ǰ���еķ���
���룺  ��
���أ�  ��
��Χ��  Ӧ�ò�ֱ�ӵ���
ע�ͣ�  ��
���ߣ�  ����
�汾��  V1.0
����޸�ʱ�䣺2009-01-19
�޸�˵��������
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
ԭ�ͣ�  void DemandMode(void)
���ܣ�  �������������庯��
������  ��
���룺  ��
���أ�  ��
��Χ��  Ӧ�ò�ֱ�ӵ���
ע�ͣ�  ��
���ߣ�  ����
�汾��  V1.0
����޸�ʱ�䣺2009-01-19
�޸�˵��������
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
        // ����һ����������
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
        // AA   ���㵱ǰ1���ӵ�����      AA
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
        // AA   �ܵĵ�ǰ�����������е�����     AA
        ucDemandClcyeAllHave++;
        if(ucDemandClcyeAllHave>=ucDemandClcye)
        {
            ucDemandClcyeAllHave=ucDemandClcye;
        }
        // AA   ���ʵĵ�ǰ�����������е�����     AA
        ucDemandClcyePriceHave++;
        if(ucDemandClcyePriceHave>=ucDemandClcye)
        {
            ucDemandClcyePriceHave=ucDemandClcye;
        }
            
        ucKwPerSecondCount=0;
        
        rCurrentDemandPat++;
        // ����һ������ʱ��
        if(rCurrentDemandPat>=ucDemandPat)
        {
            rCurrentDemandPat=0;
             // AA  ����޹�����������  AA
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
                    // �����ڴ��е�����ʵʱ��
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
                    // �������޹����������Ϊ����޹��������
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

                // �ж����������¼�
                //for(ucPoint=0;ucPoint<=PTD_KVAR_Q4_ALL_DATA;ucPoint++)
				for(ucPoint=0;ucPoint<DEMAND_OVER_NUM;ucPoint++)
                {
                    DemandOverMode(ucPoint);
                }
             } 
            // �ж�����޹�1��2�������
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
            // AA  �й�����(������)  AA 
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
            
            // AA  �޹�����(������)  AA         
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
			
			// AA  ��������(������)  AA			
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
        // AA  ��ǰ1�����й�ƽ������(������)  AA            
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
            // aa ����ʱ�䵽�� aa 
            rCurrentPriceDemandPat=0;
            memset(&ulDemandClacKvarC1C2SumBuffer[PTD_KAVR_C1_PRICE_DATA],0x00, 4*2);

            if((GAL_YES==ucDemandOneClcyeFlg)&&(ucDemandClcyePriceHave==ucDemandClcye))
            {
                // AA  ֻ���з��ʵ��Ǽ�������    AA
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
ԭ�ͣ�  void DemandResume(void)
���ܣ�  �ϵ�ʱ���������ݻָ�
������  ��
���룺  ��
���أ�  ��
��Χ��  Ӧ�ò�ֱ�ӵ���
ע�ͣ�  ��
���ߣ�  ����
�汾��  V1.0
����޸�ʱ�䣺2009-01-19
�޸�˵��������
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
ԭ�ͣ�  uchar DemandDataClrAllCurrent(void)
���ܣ�  ���е�ǰ������������
������  ��
���룺  ��
���أ�  ��
��Χ��  Ӧ�ò�ֱ�ӵ���
ע�ͣ�  ��
���ߣ�  ����
�汾��  V1.0
����޸�ʱ�䣺2009-01-19
�޸�˵��������
********************************************************************/
uchar DemandDataClrAllCurrent(void)
{
    
    //uchar ucTemp;
    //u16 uiDataStart;
    // �嵱ǰ������RAM�������е�
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

// �����ǰ��������ֵ���ڼ�¼ʱ�̵���������ֵ����������
void DemandOverChange(uchar ucType)
{
    memcpy( &RAM[RAM_COEF_TEMP_CLACUSE],(uchar*)&DemandOverData[ucType],4);
    if(1==CompareDemand(RAM_COEF_TEMP_CLACUSE))
    {
        DemandStorNowTime();
        memcpy((uchar*)&DemandOverData[ucType],&ucDemandTempBuffer[0] ,sizeof(ST_DEMAND_OVER_DATA));
    }
}

// ���������¼���¼
void DemandOverMode(uchar ucDemandType)
{
    ulong ulDataJudue;
    uchar ucCurrentStatus;
    uchar ucNeedRecord;
    ulong ulDataIn;
    if(ucDemandType>=DEMAND_OVER_NUM)
        return ;
    
    memcpy(&ucDemandTempBuffer[0], &RAM[RAM_CURRENT_DEMAND_KW_F+4*ucDemandType], 4);
    ulDataIn=Bcd3DataToLong(&ucDemandTempBuffer[1]);    // ����ֵ

    // ��������
    if(ucDemandType<2)   //ZD =2ʱ��Ϊ�޹�����
        ulDataJudue = ulDemandOverKwStart;
    else
        ulDataJudue = ulDemandOverKvarStart;
    
    ucCurrentStatus=FLG_DEMAND_OVER_ALL_STATUS&(1<<ucDemandType);
    ucNeedRecord=GAL_YES;
    // ��ǰ��������
    if(ulDataIn>ulDataJudue)
    {
        if(GAL_NO==ucCurrentStatus)
        {
            DemandOverStart(ucDemandType);
            ucNeedRecord=GAL_NO;
        }
    }
    // ��ǰ����δ����
    else
    {
        if(GAL_NO != ucCurrentStatus)
        {
            DemandOverEnd(ucDemandType);
        }
    }
    // ---�ж��Ƿ���Ҫ�����������-----
    if((GAL_NO != ucCurrentStatus)&&(GAL_YES==ucNeedRecord))
    {
        DemandOverChange(ucDemandType);
    }
}

