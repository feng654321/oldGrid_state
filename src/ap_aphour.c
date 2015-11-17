#define AP_APHOUR_GLOBALS
#include "common.h"

 


#define TYPE_APHOUR_LOSS_AVOLTAGE 0 // A相失压期间的安培小时数计算类型
#define TYPE_APHOUR_LOSS_BVOLTAGE 1 // B相失压期间的安培小时数计算类型
#define TYPE_APHOUR_LOSS_CVOLTAGE 2 // C相失压期间的安培小时数计算类型
//#define TYPE_APHOUR_LOSS_ABVOLTAGE 3 // AB相失压期间的安培小时数计算类型
//#define TYPE_APHOUR_LOSS_ACVOLTAGE 4 // AC相失压期间的安培小时数计算类型
//#define TYPE_APHOUR_LOSS_BCVOLTAGE 5 // BC相失压期间的安培小时数计算类型
//#define TYPE_APHOUR_LOSS_ABCVOLTAGE 6 // ABC相失压期间的安培小时数计算类型
#define TYPE_APHOUR_DOWN_AVOLTAGE 3//7 // A相欠压期间的安培小时数计算类型
#define TYPE_APHOUR_DOWN_BVOLTAGE 4//8 // B相欠压期间的安培小时数计算类型
#define TYPE_APHOUR_DOWN_CVOLTAGE 5//9 // C相欠压期间的安培小时数计算类型
#define TYPE_APHOUR_OVER_AVOLTAGE 6//10 // A相过压期间的安培小时数计算类型
#define TYPE_APHOUR_OVER_BVOLTAGE 7//11 // B相过压期间的安培小时数计算类型
#define TYPE_APHOUR_OVER_CVOLTAGE 8//12 // C相过压期间的安培小时数计算类型
#define TYPE_APHOUR_CUT_AVOLTAGE 9//13 // A相断相期间的安培小时数计算类型
#define TYPE_APHOUR_CUT_BVOLTAGE 10//14 // B相断相期间的安培小时数计算类型
#define TYPE_APHOUR_CUT_CVOLTAGE 11//15 // C相断相期间的安培小时数计算类型
#define TYPE_APHOUR_TYPE_MAX    12
#define TOTAL_SAVE_EPL  GAL_NO
#if 1
#if(GAL_NO == TOTAL_SAVE_EPL)
#define EPL_TOTAL_LOSS_AV_AH_ALL    NULLDATAADDR
#define EPL_TOTAL_LOSS_BV_AH_ALL    NULLDATAADDR
#define EPL_TOTAL_LOSS_CV_AH_ALL    NULLDATAADDR
#define EPL_TOTAL_DOWN_AV_AH_ALL    NULLDATAADDR
#define EPL_TOTAL_DOWN_BV_AH_ALL    NULLDATAADDR
#define EPL_TOTAL_DOWN_CV_AH_ALL    NULLDATAADDR
#define EPL_TOTAL_OVER_AV_AH_ALL    NULLDATAADDR
#define EPL_TOTAL_OVER_BV_AH_ALL    NULLDATAADDR
#define EPL_TOTAL_OVER_CV_AH_ALL    NULLDATAADDR
#define EPL_TOTAL_CUT_AV_AH_ALL    NULLDATAADDR
#define EPL_TOTAL_CUT_BV_AH_ALL    NULLDATAADDR
#define EPL_TOTAL_CUT_CV_AH_ALL    NULLDATAADDR
#endif
const ST_TB_APHOURCLAC_PARAM TB_APHOURCLAC[TYPE_APHOUR_TYPE_MAX]=
{
    // LOSS VOLTAGE
    {RAM_CURRENT_LOSS_AV_AH_ALL,EPL_TOTAL_LOSS_AV_AH_ALL,TYPE_APHOUR_LOSS_AVOLTAGE},
    {RAM_CURRENT_LOSS_BV_AH_ALL,EPL_TOTAL_LOSS_BV_AH_ALL,TYPE_APHOUR_LOSS_BVOLTAGE},
    {RAM_CURRENT_LOSS_CV_AH_ALL,EPL_TOTAL_LOSS_CV_AH_ALL,TYPE_APHOUR_LOSS_CVOLTAGE},
    //{RAM_CURRENT_LOSS_ABV_AH_ALL,EPL_TOTAL_LOSS_ABV_AH_ALL,TYPE_APHOUR_LOSS_ABVOLTAGE},
    //{RAM_CURRENT_LOSS_ACV_AH_ALL,EPL_TOTAL_LOSS_ACV_AH_ALL,TYPE_APHOUR_LOSS_ACVOLTAGE},
    //{RAM_CURRENT_LOSS_BCV_AH_ALL,EPL_TOTAL_LOSS_BCV_AH_ALL,TYPE_APHOUR_LOSS_BCVOLTAGE},
    //{RAM_CURRENT_LOSS_ABCV_AH_ALL,EPL_TOTAL_LOSS_ABCV_AH_ALL,TYPE_APHOUR_LOSS_ABCVOLTAGE},
    // DOWN VOLTAGE
    {RAM_CURRENT_DOWN_AV_AH_ALL,EPL_TOTAL_DOWN_AV_AH_ALL,TYPE_APHOUR_DOWN_AVOLTAGE},
    {RAM_CURRENT_DOWN_BV_AH_ALL,EPL_TOTAL_DOWN_BV_AH_ALL,TYPE_APHOUR_DOWN_BVOLTAGE},
    {RAM_CURRENT_DOWN_CV_AH_ALL,EPL_TOTAL_DOWN_CV_AH_ALL,TYPE_APHOUR_DOWN_CVOLTAGE},
    // OVER VOLTAGE
    {RAM_CURRENT_OVER_AV_AH_ALL,EPL_TOTAL_OVER_AV_AH_ALL,TYPE_APHOUR_OVER_AVOLTAGE},
    {RAM_CURRENT_OVER_BV_AH_ALL,EPL_TOTAL_OVER_BV_AH_ALL,TYPE_APHOUR_OVER_BVOLTAGE},
    {RAM_CURRENT_OVER_CV_AH_ALL,EPL_TOTAL_OVER_CV_AH_ALL,TYPE_APHOUR_OVER_CVOLTAGE},
    // CUT VOLTAGE
    {RAM_CURRENT_CUT_AV_AH_ALL,EPL_TOTAL_CUT_AV_AH_ALL,TYPE_APHOUR_CUT_AVOLTAGE},
    {RAM_CURRENT_CUT_BV_AH_ALL,EPL_TOTAL_CUT_BV_AH_ALL,TYPE_APHOUR_CUT_BVOLTAGE},
    {RAM_CURRENT_CUT_CV_AH_ALL,EPL_TOTAL_CUT_CV_AH_ALL,TYPE_APHOUR_CUT_CVOLTAGE}
};
u16 uiAPHourResidue[TYPE_APHOUR_TYPE_MAX][3];
#endif 

void APHourInit(void)
{
    //实际未保存
    //if(1==ReadDataDirect(EPL_APHOUR_CLACL_START, sizeof(uiAPHourResidue), &Wr_data[0]))
    //{
    //  memcpy((uchar *)&uiAPHourResidue[0][0], &Wr_data[0], sizeof(uiAPHourResidue));
    //}
    memset((uchar *)&uiAPHourResidue[0][0], 0, sizeof(uiAPHourResidue));
}


void APHourClr(void)
{
    memset((uchar *)&uiAPHourResidue[0][0], 0, sizeof(uiAPHourResidue));
    WriteDataDirect((uchar *)&uiAPHourResidue[0][0], EPL_APHOUR_CLACL_START, sizeof(uiAPHourResidue));
}

#define CON_APCLAC_CEOF 36000
void APHourClac(uchar ucClalType)
{
    ulong uctCurrentClac;
    uchar ucTemp;
    uchar ucAddOne;
    uchar ucAddTotal;
#if(GAL_YES== TOTAL_SAVE_EPL)
    uchar ucTotolCanAdd;
#endif
    
    
#if(GAL_YES== TOTAL_SAVE_EPL)
    ucTotolCanAdd=GAL_NO;
    if(1==ReadDataDirect(TB_APHOURCLAC[ucClalType].ulTotalAddr, 20, &Wr_data[0]))
    {
        if(20==TestBcdNum(&Wr_data[0], 20))
        {
            ucTotolCanAdd=GAL_YES;
        }
    }
#endif
    
    ucAddTotal=0;
    
    for(ucTemp=0;ucTemp<3;ucTemp++)
    {
        uctCurrentClac=ulNowCurrent[ucTemp]/10+uiAPHourResidue[ucClalType][ucTemp];
        if((1==ucTemp)&&((METERTYPE_3_3==PROGFUNCTION_TYPE_METER_TYPE)))
        {
            uctCurrentClac=0;
        }
        if(uctCurrentClac>CON_APCLAC_CEOF)
        {
            ucAddOne=uctCurrentClac/CON_APCLAC_CEOF;
            uctCurrentClac=uctCurrentClac%CON_APCLAC_CEOF;
            Byte5BcdPointAdd10(&RAM[TB_APHOURCLAC[ucClalType].ulCurrentAddr+5+5*ucTemp],ucAddOne);
            ucAddTotal=ucAddTotal+ucAddOne;
#if(GAL_YES== TOTAL_SAVE_EPL)
            if(GAL_YES==ucTotolCanAdd)
            {
                Byte5BcdPointAdd10(&Wr_data[5+5*ucTemp],ucAddOne);
            }
#endif      
        }
        uiAPHourResidue[ucClalType][ucTemp]=uctCurrentClac;
    }
    if(ucAddTotal>0)
    {
        Byte5BcdPointAdd10(&RAM[TB_APHOURCLAC[ucClalType].ulCurrentAddr],ucAddTotal);
#if(GAL_YES== TOTAL_SAVE_EPL)
        if(GAL_YES==ucTotolCanAdd)
        {
            Byte5BcdPointAdd10(&Wr_data[0],ucAddTotal);
            WriteDataDirect(&Wr_data[0], TB_APHOURCLAC[ucClalType].ulTotalAddr, 20);
        }
#endif      
    }
}

//uchar ucAPHourModeSecond;

void APHourMode(void)
{

    if(isSystemResetUnfinisded)
        return ;
    
    //if(ucAPHourModeSecond != RSOFT_RTC_SECOND)
    {
        //ucAPHourModeSecond = RSOFT_RTC_SECOND;
        // LOSS VOLTAGE
        if(FLG_A_LOSS_VOLTAGE_STATUS)
        {
            APHourClac(TYPE_APHOUR_LOSS_AVOLTAGE);
        }
        if(FLG_B_LOSS_VOLTAGE_STATUS)
        {
            APHourClac(TYPE_APHOUR_LOSS_BVOLTAGE);
        }
        if(FLG_C_LOSS_VOLTAGE_STATUS)
        {
            APHourClac(TYPE_APHOUR_LOSS_CVOLTAGE);
        }
        
        // DOWN VOLTAGE
        if(FLG_A_DOWN_VOLTAGE_STATUS)
        {
            APHourClac(TYPE_APHOUR_DOWN_AVOLTAGE);
        }
        if(FLG_B_DOWN_VOLTAGE_STATUS)
        {
            APHourClac(TYPE_APHOUR_DOWN_BVOLTAGE);
        }
        if(FLG_C_DOWN_VOLTAGE_STATUS)
        {
            APHourClac(TYPE_APHOUR_DOWN_CVOLTAGE);
        }
        
        // OVER VOLTAGE
        if(FLG_A_OVER_VOLTAGE_STATUS)
        {
            APHourClac(TYPE_APHOUR_OVER_AVOLTAGE);
        }
        if(FLG_B_OVER_VOLTAGE_STATUS)
        {
            APHourClac(TYPE_APHOUR_OVER_BVOLTAGE);
        }
        if(FLG_C_OVER_VOLTAGE_STATUS)
        {
            APHourClac(TYPE_APHOUR_OVER_CVOLTAGE);
        }
        
        // CUT VOLTAGE
        if(FLG_A_CUT_VOLTAGE_STATUS)
        {
            APHourClac(TYPE_APHOUR_CUT_AVOLTAGE);
        }
        if(FLG_B_CUT_VOLTAGE_STATUS)
        {
            APHourClac(TYPE_APHOUR_CUT_BVOLTAGE);
        }
        if(FLG_C_CUT_VOLTAGE_STATUS)
        {
            APHourClac(TYPE_APHOUR_CUT_CVOLTAGE);
        }
    }
}






