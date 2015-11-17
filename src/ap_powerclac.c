#define AP_POWERCLAC_GLOBALS
#include "common.h"
      
      
      
      
      
      
      
      

#define POWER_CLAC_SUB_ENABLE_YES 0x01
#define POWER_CLAC_SUB_ENABLE_NO 0x00

uchar ucPowerClacSecond;
uchar ucPowerClacNeedAdd;
ulong ulKwhPluseResidue[CON_POWER_PLUSE_RESIDUE_MAX];
ulong ulKwhPowerResidue[CON_POWER_PLUSE_RESIDUE_MAX];

void PowerClacResidueClr(void)
{
    memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
    WriteDataDirect(&Wr_data[0], EPL_KWH_RESIDUE_CLAC_START,4*CON_POWER_PLUSE_RESIDUE_MAX);
    memset((uchar * )&ulKwhPluseResidue[0], 0x00, 4*CON_POWER_PLUSE_RESIDUE_MAX);
    memset((uchar * )&ulKwhPowerResidue[0], 0x00, 4*CON_POWER_PLUSE_RESIDUE_MAX);
    //memset((uchar *)&PowerAddFlg[0].ucData, 0x00, sizeof(PowerAddFlg));
}

void GetPowerClacResidue(void)
{
    uchar ucTemp;
    if(1==ReadDataDirect(EPL_KWH_RESIDUE_CLAC_START, 4*CON_POWER_PLUSE_RESIDUE_MAX, &Wr_data[0]))
    {
        memcpy((uchar * )&ulKwhPluseResidue[0], &Wr_data[0], 4*CON_POWER_PLUSE_RESIDUE_MAX);
    }
    for(ucTemp=0;ucTemp<CON_POWER_PLUSE_RESIDUE_MAX;ucTemp++)
    {
        ulKwhPluseResidue[ucTemp]=ulKwhPluseResidue[ucTemp]&0x1ffff;
    }
}
void SetPowerClacResidue(void)
{
    WriteDataDirect((uchar * )&ulKwhPluseResidue[0], EPL_KWH_RESIDUE_CLAC_START, 4*CON_POWER_PLUSE_RESIDUE_MAX);
}
void PowerClacInit(void)
{
    uchar ucTemp;
    for(ucTemp=0;ucTemp<CON_POWER_PLUSE_RESIDUE_MAX;ucTemp++)
    {
        ulKwhPowerResidue[ucTemp]=0;
    }
    ulClacPlusePowerCoef=0x0FB6;
    ulClacPlusePowerCoef=ulClacPlusePowerCoef*CON_CLAC_PLUSE_POWER_COEF;
    GetClacPlusePowerCoef();
    if(ulClacPlusePowerCoef ==0)
        ulClacPlusePowerCoef=0x0FB6;
    memset( &ucPowerClacAddFlg[0], 0x00, sizeof(ucPowerClacAddFlg));
}
void PowerClacOneSecondAdd(void)
{

    switch (QUADRANT_Z)
    {
        case QUADRANT_TWO:
            ulKwhPowerResidue[POWER_KW_R_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_ALLKW];
            ulKwhPowerResidue[POWER_KVAR_Q2_ALL_DATA]+=ulPowerBuffer[AD_VIRTUALREG_ALLKVAR];
            // KVAH
			ulKwhPowerResidue[POWER_KVA_R_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_ALLKVA];
            break;
        case QUADRANT_THREE:
            ulKwhPowerResidue[POWER_KW_R_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_ALLKW];
            ulKwhPowerResidue[POWER_KVAR_Q3_ALL_DATA]+=ulPowerBuffer[AD_VIRTUALREG_ALLKVAR];
            // KVAH
			ulKwhPowerResidue[POWER_KVA_R_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_ALLKVA];
            break;
        case QUADRANT_FOUR:
            ulKwhPowerResidue[POWER_KW_F_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_ALLKW];
            ulKwhPowerResidue[POWER_KVAR_Q4_ALL_DATA]+=ulPowerBuffer[AD_VIRTUALREG_ALLKVAR];
            // KVAH
			ulKwhPowerResidue[POWER_KVA_F_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_ALLKVA];
            break;
        default : // QUADRANT_ONE
            ulKwhPowerResidue[POWER_KW_F_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_ALLKW];
            ulKwhPowerResidue[POWER_KVAR_Q1_ALL_DATA]+=ulPowerBuffer[AD_VIRTUALREG_ALLKVAR];
            // KVAH
			ulKwhPowerResidue[POWER_KVA_F_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_ALLKVA];
            break;
    }


    switch (QUADRANT_A)
    {
        case QUADRANT_TWO:
            //KWH
            ulKwhPowerResidue[POWER_KW_A_R_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_AKW];
            // KVARH
			ulKwhPowerResidue[POWER_KVAR_A_Q2_ALL_DATA]+=ulPowerBuffer[AD_VIRTUALREG_AKVAR];
            // KVAH
			ulKwhPowerResidue[POWER_KVA_A_R_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_AKVA];
            break;
        case QUADRANT_THREE:
            ulKwhPowerResidue[POWER_KW_A_R_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_AKW];
			ulKwhPowerResidue[POWER_KVAR_A_Q3_ALL_DATA]+=ulPowerBuffer[AD_VIRTUALREG_AKVAR];
            // KVAH
			ulKwhPowerResidue[POWER_KVA_A_R_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_AKVA];
            break;
        case QUADRANT_FOUR:
            ulKwhPowerResidue[POWER_KW_A_F_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_AKW];
			ulKwhPowerResidue[POWER_KVAR_A_Q4_ALL_DATA]+=ulPowerBuffer[AD_VIRTUALREG_AKVAR];
            // KVAH
			ulKwhPowerResidue[POWER_KVA_A_F_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_AKVA];
            break;
        default : // QUADRANT_ONE
            ulKwhPowerResidue[POWER_KW_A_F_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_AKW];
			ulKwhPowerResidue[POWER_KVAR_A_Q1_ALL_DATA]+=ulPowerBuffer[AD_VIRTUALREG_AKVAR];
            // KVAH
			ulKwhPowerResidue[POWER_KVA_A_F_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_AKVA];
            break;
    }

    switch (QUADRANT_B)
    {
        case QUADRANT_TWO:
            //KWH
            ulKwhPowerResidue[POWER_KW_B_R_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_BKW];
			ulKwhPowerResidue[POWER_KVAR_B_Q2_ALL_DATA]+=ulPowerBuffer[AD_VIRTUALREG_BKVAR];
			// KVAH
			ulKwhPowerResidue[POWER_KVA_B_R_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_BKVA];
			break;
		case QUADRANT_THREE:
			ulKwhPowerResidue[POWER_KW_B_R_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_BKW];
			ulKwhPowerResidue[POWER_KVAR_B_Q3_ALL_DATA]+=ulPowerBuffer[AD_VIRTUALREG_BKVAR];
			// KVAH
			ulKwhPowerResidue[POWER_KVA_B_R_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_BKVA];
			break;
		case QUADRANT_FOUR:
			ulKwhPowerResidue[POWER_KW_B_F_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_BKW];
			ulKwhPowerResidue[POWER_KVAR_B_Q4_ALL_DATA]+=ulPowerBuffer[AD_VIRTUALREG_BKVAR];
			// KVAH
			ulKwhPowerResidue[POWER_KVA_B_F_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_BKVA];
			break;
		default : // QUADRANT_ONE
			ulKwhPowerResidue[POWER_KW_B_F_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_BKW];
			ulKwhPowerResidue[POWER_KVAR_B_Q1_ALL_DATA]+=ulPowerBuffer[AD_VIRTUALREG_BKVAR];
			// KVAH
			ulKwhPowerResidue[POWER_KVA_B_F_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_BKVA];
			break;
	}

	switch (QUADRANT_C)
	{
		case QUADRANT_TWO:
			//KWH
			ulKwhPowerResidue[POWER_KW_C_R_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_CKW];
			// KVARH
			ulKwhPowerResidue[POWER_KVAR_C_Q2_ALL_DATA]+=ulPowerBuffer[AD_VIRTUALREG_CKVAR];
			// KVAH
			ulKwhPowerResidue[POWER_KVA_C_R_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_CKVA];
			break;
		case QUADRANT_THREE:
			ulKwhPowerResidue[POWER_KW_C_R_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_CKW];
			ulKwhPowerResidue[POWER_KVAR_C_Q3_ALL_DATA]+=ulPowerBuffer[AD_VIRTUALREG_CKVAR];
			// KVAH
			ulKwhPowerResidue[POWER_KVA_C_R_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_CKVA];
			break;
		case QUADRANT_FOUR:
			ulKwhPowerResidue[POWER_KW_C_F_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_CKW];
			ulKwhPowerResidue[POWER_KVAR_C_Q4_ALL_DATA]+=ulPowerBuffer[AD_VIRTUALREG_CKVAR];
			// KVAH
			ulKwhPowerResidue[POWER_KVA_C_F_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_CKVA];
			break;
		default : // QUADRANT_ONE
			ulKwhPowerResidue[POWER_KW_C_F_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_CKW];
			ulKwhPowerResidue[POWER_KVAR_C_Q1_ALL_DATA]+=ulPowerBuffer[AD_VIRTUALREG_CKVAR];
			// KVAH
			ulKwhPowerResidue[POWER_KVA_C_F_ALL_DATA] +=ulPowerBuffer[AD_VIRTUALREG_CKVA];
            break;
    }

}








void PowerClacMode(void)
{
    uchar ucTemp;
    uchar ucPowerChange;
    u16 uiTemp;
    if(ucPowerClacSecond !=RSOFT_RTC_SECOND)
    {
        ucPowerClacSecond=RSOFT_RTC_SECOND;
        PowerClacOneSecondAdd();
        for(ucTemp=0;ucTemp<POWER_KW_ALL_DATA_END;ucTemp++)
        {
            if(ulKwhPowerResidue[ucTemp]>ulClacPlusePowerCoef)
            {
                uiTemp=ulKwhPowerResidue[ucTemp]/ulClacPlusePowerCoef;
                uiTemp*=100;
                ulKwhPluseResidue[ucTemp] +=uiTemp;
#if (CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE_ENABLE == CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE)
                if(((POWER_KW_F_ALL_DATA==ucTemp)||(POWER_KW_R_ALL_DATA==ucTemp)) )
                {
                    if (ucCurrentPriceHEX<=CON_PRICENUM_MAX)
                    {
                        ulKwhPluseResidue[POWER_KW_ALL_PRICE_DATA_START+ucTemp*CON_PRICENUM_MAX+ucCurrentPriceHEX-1]+=uiTemp;
                    }
                    else
                    {
                        ulKwhPluseResidue[POWER_KW_ALL_PRICE_DATA_START+ucTemp*CON_PRICENUM_MAX+1-1]+=uiTemp;
                    }
                }
#endif
                ulKwhPowerResidue[ucTemp] %=ulClacPlusePowerCoef;
                ucPowerClacNeedAdd=GAL_YES;
//              if(ucTemp<POWER_KVA_F_ALL_DATA)
                if(ucTemp<=POWER_KVAR_Q4_ALL_DATA)
                {
                    uiPluseRestTimes=0;
                }
            }
        }
        #if 0
        if(GAL_YES==ucPowerClacNeedAdd)
        {
            SetPowerClacResidue();
        }
        #endif
        unPowerKwhC1Mode.ucData=RAM[RAM_CHARACTER_ACTIVE];
        unPowerKvahC1mode.ucData=RAM[RAM_CHARACTER_REACTIVE01];
        unPowerKvahC2mode.ucData=RAM[RAM_CHARACTER_REACTIVE02];

        // 组合特征字设置一增一减，无效
        if(0x03==unPowerKwhC1Mode.Bit2DemandAdd.b2KwF)
        {
            unPowerKwhC1Mode.Bit2DemandAdd.b2KwF=0;
        }
        if(0x03==unPowerKwhC1Mode.Bit2DemandAdd.b2KwR)
        {
            unPowerKwhC1Mode.Bit2DemandAdd.b2KwR=0;
        }
        
        if(0x03==unPowerKvahC1mode.Bit2DemandAdd.b2KvarQ1)
        {
            unPowerKvahC1mode.Bit2DemandAdd.b2KvarQ1=0;
        }
        if(0x03==unPowerKvahC1mode.Bit2DemandAdd.b2KvarQ2)
        {
            unPowerKvahC1mode.Bit2DemandAdd.b2KvarQ2=0;
        }
        if(0x03==unPowerKvahC1mode.Bit2DemandAdd.b2KvarQ3)
        {
            unPowerKvahC1mode.Bit2DemandAdd.b2KvarQ3=0;
        }
        if(0x03==unPowerKvahC1mode.Bit2DemandAdd.b2KvarQ4)
        {
            unPowerKvahC1mode.Bit2DemandAdd.b2KvarQ4=0;
        }
        
        if(0x03==unPowerKvahC2mode.Bit2DemandAdd.b2KvarQ1)
        {
            unPowerKvahC2mode.Bit2DemandAdd.b2KvarQ1=0;
        }
        if(0x03==unPowerKvahC2mode.Bit2DemandAdd.b2KvarQ2)
        {
            unPowerKvahC2mode.Bit2DemandAdd.b2KvarQ2=0;
        }
        if(0x03==unPowerKvahC2mode.Bit2DemandAdd.b2KvarQ3)
        {
            unPowerKvahC2mode.Bit2DemandAdd.b2KvarQ3=0;
        }
        if(0x03==unPowerKvahC2mode.Bit2DemandAdd.b2KvarQ4)
        {
            unPowerKvahC2mode.Bit2DemandAdd.b2KvarQ4=0;
        }
        
    }
    ucPowerChange=GAL_NO;
    if((GAL_YES==ucPowerClacNeedAdd)&&(GAL_NO==KwhAddModeAddEnd))
    {
#if 1
        uiTemp=100;
        if(MODE_POWER_CALC_POINT==MODE_POWER_CALC_POINT_3DOT)
        {
            uiTemp=10;
        }
        if(MODE_POWER_CALC_POINT==MODE_POWER_CALC_POINT_4DOT)
        {
            uiTemp=1;
        }
        
        for(ucTemp=0;ucTemp<POWER_KW_ALL_DATA_END;ucTemp++)
        {
            if((ulKwhPluseResidue[ucTemp]/uiTemp)>=KwhPluseNum)
            {
                ucPowerClacAddFlg[ucTemp]=(ulKwhPluseResidue[ucTemp]/uiTemp)/KwhPluseNum;
                if(ucPowerClacAddFlg[ucTemp]>(200/uiTemp))
                {
                    ucPowerClacAddFlg[ucTemp]=(200/uiTemp);
                }
                ucPowerClacAddFlg[ucTemp] =ucPowerClacAddFlg[ucTemp] * uiTemp;
                ulKwhPluseResidue[ucTemp]-=ucPowerClacAddFlg[ucTemp]*KwhPluseNum;
                ucPowerChange=GAL_YES;
            }
        }
        
#if (CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE_ENABLE == CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE)
        for(ucTemp=POWER_KW_ALL_PRICE_DATA_START;ucTemp<(POWER_KW_ALL_PRICE_DATA_START+8);ucTemp++)
        {
            if((ulKwhPluseResidue[ucTemp]/uiTemp)>=KwhPluseNum)
            {
                ucPowerClacAddFlg[ucTemp]=(ulKwhPluseResidue[ucTemp]/uiTemp)/KwhPluseNum;
                if(ucPowerClacAddFlg[ucTemp]>(200/uiTemp))
                {
                    ucPowerClacAddFlg[ucTemp]=(200/uiTemp);
                }
                ucPowerClacAddFlg[ucTemp] =ucPowerClacAddFlg[ucTemp] * uiTemp;
                ulKwhPluseResidue[ucTemp]-=ucPowerClacAddFlg[ucTemp]*KwhPluseNum;
                ucPowerChange=GAL_YES;
            }
        }
#endif
#else       
        for(ucTemp=0;ucTemp<POWER_KW_ALL_DATA_END;ucTemp++)
        {
            if((ulKwhPluseResidue[ucTemp])>=KwhPluseNum)
            {
                ucPowerClacAddFlg[ucTemp]=(ulKwhPluseResidue[ucTemp])/KwhPluseNum;
                if(ucPowerClacAddFlg[ucTemp]>(200))
                {
                    ucPowerClacAddFlg[ucTemp]=(200);
                }
                //ucPowerClacAddFlg[ucTemp] =ucPowerClacAddFlg[ucTemp] ;
                ulKwhPluseResidue[ucTemp]-=ucPowerClacAddFlg[ucTemp]*KwhPluseNum;
                ucPowerChange=GAL_YES;
            }
        }
        
#if (CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE_ENABLE == CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE)
        for(ucTemp=POWER_KW_ALL_PRICE_DATA_START;ucTemp<(POWER_KW_ALL_PRICE_DATA_START+8);ucTemp++)
        {
            if((ulKwhPluseResidue[ucTemp])>=KwhPluseNum)
            {
                ucPowerClacAddFlg[ucTemp]=(ulKwhPluseResidue[ucTemp])/KwhPluseNum;
                if(ucPowerClacAddFlg[ucTemp]>(200))
                {
                    ucPowerClacAddFlg[ucTemp]=(200);
                }
                ucPowerClacAddFlg[ucTemp] =ucPowerClacAddFlg[ucTemp] ;
                ulKwhPluseResidue[ucTemp]-=ucPowerClacAddFlg[ucTemp]*KwhPluseNum;
                ucPowerChange=GAL_YES;
            }
        }
#endif
#endif

// --AA   重新保存目前的脉冲尾数AA--
        //SetPowerClacResidue();
#if (CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE_ENABLE == CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE)

        // ZHENGXIANG YOUGONG PRICE1 
        if(ucPowerClacAddFlg[POWER_KW_F_ALL_DATA_PRICE1])
        {
            if(unPowerKwhC1Mode.Bits.bKwFAdd)
            {
                ucPowerClacAddFlg[POWER_KW_C_ALL_ADD_DATA_PRICE1]=ucPowerClacAddFlg[POWER_KW_F_ALL_DATA_PRICE1];
            }
            if(unPowerKwhC1Mode.Bits.bKwFSub)
            {
                ucPowerClacAddFlg[POWER_KW_C_ALL_SUB_DATA_PRICE1]=ucPowerClacAddFlg[POWER_KW_F_ALL_DATA_PRICE1];
            }
        }
        // ZHENGXIANG YOUGONG PRICE2
        if(ucPowerClacAddFlg[POWER_KW_F_ALL_DATA_PRICE2])
        {
            if(unPowerKwhC1Mode.Bits.bKwFAdd)
            {
                ucPowerClacAddFlg[POWER_KW_C_ALL_ADD_DATA_PRICE2]=ucPowerClacAddFlg[POWER_KW_F_ALL_DATA_PRICE2];
            }
            if(unPowerKwhC1Mode.Bits.bKwFSub)
            {
                ucPowerClacAddFlg[POWER_KW_C_ALL_SUB_DATA_PRICE2]=ucPowerClacAddFlg[POWER_KW_F_ALL_DATA_PRICE2];
            }
        }
        // ZHENGXIANG YOUGONG PRICE3
        if(ucPowerClacAddFlg[POWER_KW_F_ALL_DATA_PRICE3])
        {
            if(unPowerKwhC1Mode.Bits.bKwFAdd)
            {
                ucPowerClacAddFlg[POWER_KW_C_ALL_ADD_DATA_PRICE3]=ucPowerClacAddFlg[POWER_KW_F_ALL_DATA_PRICE3];
            }
            if(unPowerKwhC1Mode.Bits.bKwFSub)
            {
                ucPowerClacAddFlg[POWER_KW_C_ALL_SUB_DATA_PRICE3]=ucPowerClacAddFlg[POWER_KW_F_ALL_DATA_PRICE3];
            }
        }
        // ZHENGXIANG YOUGONG PRICE4
        if(ucPowerClacAddFlg[POWER_KW_F_ALL_DATA_PRICE4])
        {
            if(unPowerKwhC1Mode.Bits.bKwFAdd)
            {
                ucPowerClacAddFlg[POWER_KW_C_ALL_ADD_DATA_PRICE4]=ucPowerClacAddFlg[POWER_KW_F_ALL_DATA_PRICE4];
            }
            if(unPowerKwhC1Mode.Bits.bKwFSub)
            {
                ucPowerClacAddFlg[POWER_KW_C_ALL_SUB_DATA_PRICE4]=ucPowerClacAddFlg[POWER_KW_F_ALL_DATA_PRICE4];
            }
        }

        // FANXIANG YOUGONG PRICE1 
        if(ucPowerClacAddFlg[POWER_KW_R_ALL_DATA_PRICE1])
        {
            if(unPowerKwhC1Mode.Bits.bKwRAdd)
            {
                ucPowerClacAddFlg[POWER_KW_C_ALL_ADD_DATA_PRICE1]=ucPowerClacAddFlg[POWER_KW_R_ALL_DATA_PRICE1];
            }
            if(unPowerKwhC1Mode.Bits.bKwRSub)
            {
                ucPowerClacAddFlg[POWER_KW_C_ALL_SUB_DATA_PRICE1]=ucPowerClacAddFlg[POWER_KW_R_ALL_DATA_PRICE1];
            }
        }
        // FANXIANG YOUGONG PRICE2
        if(ucPowerClacAddFlg[POWER_KW_R_ALL_DATA_PRICE2])
        {
            if(unPowerKwhC1Mode.Bits.bKwRAdd)
            {
                ucPowerClacAddFlg[POWER_KW_C_ALL_ADD_DATA_PRICE2]=ucPowerClacAddFlg[POWER_KW_R_ALL_DATA_PRICE2];
            }
            if(unPowerKwhC1Mode.Bits.bKwRSub)
            {
                ucPowerClacAddFlg[POWER_KW_C_ALL_SUB_DATA_PRICE2]=ucPowerClacAddFlg[POWER_KW_R_ALL_DATA_PRICE2];
            }
        }
        // FANXIANG YOUGONG PRICE3
        if(ucPowerClacAddFlg[POWER_KW_R_ALL_DATA_PRICE3])
        {
            if(unPowerKwhC1Mode.Bits.bKwRAdd)
            {
                ucPowerClacAddFlg[POWER_KW_C_ALL_ADD_DATA_PRICE3]=ucPowerClacAddFlg[POWER_KW_R_ALL_DATA_PRICE3];
            }
            if(unPowerKwhC1Mode.Bits.bKwRSub)
            {
                ucPowerClacAddFlg[POWER_KW_C_ALL_SUB_DATA_PRICE3]=ucPowerClacAddFlg[POWER_KW_R_ALL_DATA_PRICE3];
            }
        }
        // FANXIANG YOUGONG PRICE4
        if(ucPowerClacAddFlg[POWER_KW_R_ALL_DATA_PRICE4])
        {
            if(unPowerKwhC1Mode.Bits.bKwRAdd)
            {
                ucPowerClacAddFlg[POWER_KW_C_ALL_ADD_DATA_PRICE4]=ucPowerClacAddFlg[POWER_KW_R_ALL_DATA_PRICE4];
            }
            if(unPowerKwhC1Mode.Bits.bKwRSub)
            {
                ucPowerClacAddFlg[POWER_KW_C_ALL_SUB_DATA_PRICE4]=ucPowerClacAddFlg[POWER_KW_R_ALL_DATA_PRICE4];
            }
        }

#endif

//   AA   所有组合类的数据  AA  
//   AA  组合有功  AA
        if(ucPowerClacAddFlg[POWER_KW_F_ALL_DATA])
        {
            if(unPowerKwhC1Mode.Bits.bKwFAdd)
            {
                ucPowerClacAddFlg[POWER_KW_C_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KW_F_ALL_DATA];
            }
            if(unPowerKwhC1Mode.Bits.bKwFSub)
            {
                ucPowerClacAddFlg[POWER_KW_C_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KW_F_ALL_DATA];
            }
            // --AA 新增加的正反向有功电量,该数据不判断组合方式,直接累加AA--
            ucPowerClacAddFlg[POWER_KW_FR_ALL_DATA]=ucPowerClacAddFlg[POWER_KW_F_ALL_DATA];
        }
        
        if(ucPowerClacAddFlg[POWER_KW_R_ALL_DATA])
        {
            if(unPowerKwhC1Mode.Bits.bKwRAdd)
            {
                ucPowerClacAddFlg[POWER_KW_C_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KW_R_ALL_DATA];
            }
            if(unPowerKwhC1Mode.Bits.bKwRSub)
            {
                ucPowerClacAddFlg[POWER_KW_C_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KW_R_ALL_DATA];
            }
            // --AA 新增加的正反向有功电量,该数据不判断组合方式,直接累加AA--
            ucPowerClacAddFlg[POWER_KW_FR_ALL_DATA]=ucPowerClacAddFlg[POWER_KW_R_ALL_DATA];
        }


        //   AA  组合C1 无功AA
        // Q1
        if(unPowerKvahC1mode.Bits.bKvarQ1Add)
        {
            if(ucPowerClacAddFlg[POWER_KVAR_Q1_ALL_DATA])
            {
                ucPowerClacAddFlg[POWER_KVAR_C1_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_Q1_ALL_DATA];
            }
			if(ucPowerClacAddFlg[POWER_KVAR_A_Q1_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_A_C1_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_A_Q1_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_B_Q1_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_B_C1_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_B_Q1_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_C_Q1_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C_C1_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_C_Q1_ALL_DATA];
			}
		}
		if(unPowerKvahC1mode.Bits.bKvarQ1Sub)
		{
			if(ucPowerClacAddFlg[POWER_KVAR_Q1_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C1_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_Q1_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_A_Q1_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_A_C1_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_A_Q1_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_B_Q1_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_B_C1_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_B_Q1_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_C_Q1_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C_C1_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_C_Q1_ALL_DATA];
			}
		}
		// Q2
		if(unPowerKvahC1mode.Bits.bKvarQ2Add)
		{
			if(ucPowerClacAddFlg[POWER_KVAR_Q2_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C1_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_Q2_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_A_Q2_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_A_C1_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_A_Q2_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_B_Q2_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_B_C1_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_B_Q2_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_C_Q2_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C_C1_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_C_Q2_ALL_DATA];
			}
		}
		if(unPowerKvahC1mode.Bits.bKvarQ2Sub)
		{
			if(ucPowerClacAddFlg[POWER_KVAR_Q2_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C1_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_Q2_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_A_Q2_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_A_C1_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_A_Q2_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_B_Q2_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_B_C1_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_B_Q2_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_C_Q2_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C_C1_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_C_Q2_ALL_DATA];
			}
		}
		// Q3
		if(unPowerKvahC1mode.Bits.bKvarQ3Add)
		{
			if(ucPowerClacAddFlg[POWER_KVAR_Q3_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C1_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_Q3_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_A_Q3_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_A_C1_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_A_Q3_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_B_Q3_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_B_C1_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_B_Q3_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_C_Q3_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C_C1_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_C_Q3_ALL_DATA];
			}
		}
		if(unPowerKvahC1mode.Bits.bKvarQ3Sub)
		{
			if(ucPowerClacAddFlg[POWER_KVAR_Q3_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C1_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_Q3_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_A_Q3_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_A_C1_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_A_Q3_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_B_Q3_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_B_C1_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_B_Q3_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_C_Q3_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C_C1_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_C_Q3_ALL_DATA];
			}
		}
		// Q4
		if(unPowerKvahC1mode.Bits.bKvarQ4Add)
		{
			if(ucPowerClacAddFlg[POWER_KVAR_Q4_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C1_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_Q4_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_A_Q4_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_A_C1_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_A_Q4_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_B_Q4_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_B_C1_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_B_Q4_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_C_Q4_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C_C1_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_C_Q4_ALL_DATA];
			}
		}
		if(unPowerKvahC1mode.Bits.bKvarQ4Sub)
		{
			if(ucPowerClacAddFlg[POWER_KVAR_Q4_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C1_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_Q4_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_A_Q4_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_A_C1_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_A_Q4_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_B_Q4_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_B_C1_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_B_Q4_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_C_Q4_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C_C1_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_C_Q4_ALL_DATA];
			}
		}
		
		//   AA  组合C2 无功AA
		// Q1
		if(unPowerKvahC2mode.Bits.bKvarQ1Add)
		{
			if(ucPowerClacAddFlg[POWER_KVAR_Q1_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C2_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_Q1_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_A_Q1_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_A_C2_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_A_Q1_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_B_Q1_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_B_C2_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_B_Q1_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_C_Q1_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C_C2_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_C_Q1_ALL_DATA];
			}
		}
		if(unPowerKvahC2mode.Bits.bKvarQ1Sub)
		{
			if(ucPowerClacAddFlg[POWER_KVAR_Q1_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C2_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_Q1_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_A_Q1_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_A_C2_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_A_Q1_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_B_Q1_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_B_C2_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_B_Q1_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_C_Q1_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C_C2_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_C_Q1_ALL_DATA];
			}
		}
		// Q2
		if(unPowerKvahC2mode.Bits.bKvarQ2Add)
		{
			if(ucPowerClacAddFlg[POWER_KVAR_Q2_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C2_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_Q2_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_A_Q2_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_A_C2_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_A_Q2_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_B_Q2_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_B_C2_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_B_Q2_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_C_Q2_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C_C2_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_C_Q2_ALL_DATA];
			}
		}
		if(unPowerKvahC2mode.Bits.bKvarQ2Sub)
		{
			if(ucPowerClacAddFlg[POWER_KVAR_Q2_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C2_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_Q2_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_A_Q2_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_A_C2_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_A_Q2_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_B_Q2_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_B_C2_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_B_Q2_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_C_Q2_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C_C2_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_C_Q2_ALL_DATA];
			}
		}
		// Q3
		if(unPowerKvahC2mode.Bits.bKvarQ3Add)
		{
			if(ucPowerClacAddFlg[POWER_KVAR_Q3_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C2_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_Q3_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_A_Q3_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_A_C2_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_A_Q3_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_B_Q3_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_B_C2_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_B_Q3_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_C_Q3_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C_C2_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_C_Q3_ALL_DATA];
			}
		}
		if(unPowerKvahC2mode.Bits.bKvarQ3Sub)
		{
			if(ucPowerClacAddFlg[POWER_KVAR_Q3_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C2_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_Q3_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_A_Q3_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_A_C2_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_A_Q3_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_B_Q3_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_B_C2_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_B_Q3_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_C_Q3_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C_C2_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_C_Q3_ALL_DATA];
			}
		}
		// Q4
		if(unPowerKvahC2mode.Bits.bKvarQ4Add)
		{
			if(ucPowerClacAddFlg[POWER_KVAR_Q4_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C2_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_Q4_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_A_Q4_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_A_C2_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_A_Q4_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_B_Q4_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_B_C2_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_B_Q4_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_C_Q4_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C_C2_ALL_ADD_DATA]=ucPowerClacAddFlg[POWER_KVAR_C_Q4_ALL_DATA];
			}
		}
		if(unPowerKvahC2mode.Bits.bKvarQ4Sub)
		{
			if(ucPowerClacAddFlg[POWER_KVAR_Q4_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C2_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_Q4_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_A_Q4_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_A_C2_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_A_Q4_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_B_Q4_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_B_C2_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_B_Q4_ALL_DATA];
			}
			if(ucPowerClacAddFlg[POWER_KVAR_C_Q4_ALL_DATA])
			{
				ucPowerClacAddFlg[POWER_KVAR_C_C2_ALL_SUB_DATA]=ucPowerClacAddFlg[POWER_KVAR_C_Q4_ALL_DATA];
			}
		}
        

        if(GAL_YES ==ucPowerChange)
        {
            ucPowerClacNeedAdd=GAL_YES;
            KwhAddModeAddEnd=GAL_YES;
        }
        else
        {
            ucPowerClacNeedAdd=GAL_NO;
        }
        
    }
}



