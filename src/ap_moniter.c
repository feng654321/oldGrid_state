#define AP_MONITER_GLOBALS
#include "common.h"

/**********************************************************************
// 
// 
**********************************************************************/
uchar MoniterMinute;
//uchar MoniterSecond;

#define CON_MONITER_STATUS_NO   0x00
#define CON_MONITER_STATUS_DOWN 0x01
#define CON_MONITER_STATUS_OVER 0x02
#define CON_MONITER_STATUS_ALL  0x03

u16 uiMonitorVoltageUpperMin,uiMonitorVoltageUpperMax;
u16 uiMonitorVoltageDownMin,uiMonitorVoltageDownMax;
void MoniterParaInit(void)
{
    ReadCoefDataWithCheck(EPL_COEF_VOLTAGE_LIMIT_UPPER, 2, Ap_temp, 1);
    uiMonitorVoltageUpperMin = HexFromRam2Bcd(Ap_temp);
    ReadCoefDataWithCheck(EPL_COEF_VOLTAGE_LIMIT_LOWER, 2, Ap_temp, 1);
    uiMonitorVoltageDownMax = HexFromRam2Bcd(Ap_temp);
    ReadCoefDataWithCheck(EPL_COEF_MONITOR_VOLTAGE_CONDITION, 4, Ap_temp, 1);
    uiMonitorVoltageUpperMax = HexFromRam2Bcd(Ap_temp);
    uiMonitorVoltageDownMin = HexFromRam2Bcd(Ap_temp+2);
}

void MoniterInit(void)
{
    //MoniterSecond=RSOFT_RTC_SECOND;
    MoniterMinute=RSOFT_RTC_MINUTE;
    MoniterParaInit();
}


uchar CompareMaxVoltage(ulong ulAddr,u16 uiCurrentVoltage)
{
    u16 ulVoltage;
    if(1==ReadDataDirect(ulAddr, 2, &Wr_data[0]))
    {
        ulVoltage=Bcd2DataToInt(&Wr_data[0]);
        if(ulVoltage<uiCurrentVoltage)
        {
            IntToData2BCD(uiCurrentVoltage, &Wr_data[0]);
            SetmmhhDDMMYYToPoint(&Wr_data[2]);
            WriteDataDirect(&Wr_data[0], ulAddr, 6);
            return 1;
        }
    }
    return 0;
}
uchar CompareMinVoltage(ulong ulAddr,u16 uiCurrentVoltage)
{
    u16 ulVoltage;
    if(1==ReadDataDirect(ulAddr, 6, &Wr_data[0]))
    {
        ulVoltage=Bcd2DataToInt(&Wr_data[0]);
        if(ulVoltage>uiCurrentVoltage)
        {
            IntToData2BCD(uiCurrentVoltage, &Wr_data[0]);
            SetmmhhDDMMYYToPoint(&Wr_data[2]);
            WriteDataDirect(&Wr_data[0], ulAddr, 6);
            return 1;
        }
        else
        {
            if(4 ==TestZeroNum(&Wr_data[2], 4))
            {
                IntToData2BCD(uiCurrentVoltage, &Wr_data[0]);
                SetmmhhDDMMYYToPoint(&Wr_data[2]);
                WriteDataDirect(&Wr_data[0], ulAddr, 6);
                return 1;
            }
        }
    }
    return 0;
}
void MoniterMode(void)
{
    ulong ulData,ulDataMax;
    uchar ucValueOver,ucValueDown;
    ulong ulDataAll,ulDataErr;

    if(isSystemResetUnfinisded)
        return ;
    
    if(GAL_YES==PROGFUNCTION_VOLTAGE_ALL_MONITOR)
    {
        //if(MoniterSecond!=RSOFT_RTC_SECOND)
        {
            //MoniterSecond=RSOFT_RTC_SECOND;
            FLG_MONITOR_V_STATUS=0;
// AA ----判断状态---->Start----   AA           
            ulData=uiMonitorVoltageUpperMin;
            ulDataMax=uiMonitorVoltageUpperMax;
            if(ulDataMax<ulData)
            {
                ulDataMax=ulData;
            }
            if((ulData<=uiNowVoltage[0])&&(uiNowVoltage[0]<=ulDataMax))
            {
                FLG_MONITOR_V_A_STATUS=CON_MONITER_STATUS_OVER;
            }
            if(METERTYPE_3_3!=PROGFUNCTION_TYPE_METER_TYPE  )
            {
                if((ulData<=uiNowVoltage[1])&&(uiNowVoltage[1]<=ulDataMax))
                {
                    FLG_MONITOR_V_B_STATUS=CON_MONITER_STATUS_OVER;
                }
            }
            if((ulData<=uiNowVoltage[2])&&(uiNowVoltage[2]<=ulDataMax))
            {
                FLG_MONITOR_V_C_STATUS=CON_MONITER_STATUS_OVER;
            }
            ulDataMax=uiMonitorVoltageDownMax;
            ulData=uiMonitorVoltageDownMin;
            if(ulDataMax<ulData)
            {
                ulDataMax=ulData;
            }
            if((ulData<=uiNowVoltage[0])&&(uiNowVoltage[0]<=ulDataMax))
            {
                FLG_MONITOR_V_A_STATUS=CON_MONITER_STATUS_DOWN;
            }
            if(METERTYPE_3_3!=PROGFUNCTION_TYPE_METER_TYPE  )
            {
                if((ulData<=uiNowVoltage[1])&&(uiNowVoltage[1]<=ulDataMax))
                {
                    FLG_MONITOR_V_B_STATUS=CON_MONITER_STATUS_DOWN;
                }
            }
            if((ulData<=uiNowVoltage[2])&&(uiNowVoltage[2]<=ulDataMax))
            {
                FLG_MONITOR_V_C_STATUS=CON_MONITER_STATUS_DOWN;
            }
// AA ----判断状态---->End----   AA         
// AA ----比较大小---->Start----   AA           
            if(CON_MONITER_STATUS_OVER==FLG_MONITOR_V_A_STATUS)
            {
                if(1==CompareMaxVoltage(RAM_VOLTAGE_A_MONITOR_MAX_VOLTAGE,uiNowVoltage[0]))
                {
                    CompareMaxVoltage(RAM_VOLTAGE_ALL_MONITOR_MAX_VOLTAGE,uiNowVoltage[0]);
                }
            }
            if(METERTYPE_3_3!=PROGFUNCTION_TYPE_METER_TYPE  )
            {
                if(CON_MONITER_STATUS_OVER==FLG_MONITOR_V_B_STATUS)
                {
                    if(1==CompareMaxVoltage(RAM_VOLTAGE_B_MONITOR_MAX_VOLTAGE,uiNowVoltage[1]))
                    {
                        CompareMaxVoltage(RAM_VOLTAGE_ALL_MONITOR_MAX_VOLTAGE,uiNowVoltage[1]);
                    }
                }
            }
            if(CON_MONITER_STATUS_OVER==FLG_MONITOR_V_C_STATUS)
            {
                if(1==CompareMaxVoltage(RAM_VOLTAGE_C_MONITOR_MAX_VOLTAGE,uiNowVoltage[2]))
                {
                    CompareMaxVoltage(RAM_VOLTAGE_ALL_MONITOR_MAX_VOLTAGE,uiNowVoltage[2]);
                }
            }
            
            if(CON_MONITER_STATUS_DOWN==FLG_MONITOR_V_A_STATUS)
            {
                if(1==CompareMinVoltage(RAM_VOLTAGE_A_MONITOR_MIN_VOLTAGE,uiNowVoltage[0]))
                {
                    CompareMinVoltage(RAM_VOLTAGE_ALL_MONITOR_MIN_VOLTAGE,uiNowVoltage[0]);
                }
            }
            if(METERTYPE_3_3!=PROGFUNCTION_TYPE_METER_TYPE  )
            {
                if(CON_MONITER_STATUS_DOWN==FLG_MONITOR_V_B_STATUS)
                {
                    if(1==CompareMinVoltage(RAM_VOLTAGE_B_MONITOR_MIN_VOLTAGE,uiNowVoltage[1]))
                    {
                        CompareMinVoltage(RAM_VOLTAGE_ALL_MONITOR_MIN_VOLTAGE,uiNowVoltage[1]);
                    }
                }
            }
            if(CON_MONITER_STATUS_DOWN==FLG_MONITOR_V_C_STATUS)
            {
                if(1==CompareMinVoltage(RAM_VOLTAGE_C_MONITOR_MIN_VOLTAGE,uiNowVoltage[2]))
                {
                    CompareMinVoltage(RAM_VOLTAGE_ALL_MONITOR_MIN_VOLTAGE,uiNowVoltage[2]);
                }
            }
// AA ----比较大小---->End----   AA     
        }
            
        if(MoniterMinute!=RSOFT_RTC_MINUTE)
        {
            MoniterMinute=RSOFT_RTC_MINUTE;
            ucValueDown=GAL_NO;
            ucValueOver=GAL_NO;
            // A phase
            Data3ByteBCDAdd1(RAM_VOLTAGE_A_MONITOR_TIME);
            if(CON_MONITER_STATUS_DOWN==FLG_MONITOR_V_A_STATUS)
            {
                Data3ByteBCDAdd1(RAM_VOLTAGE_A_MONITOR_DOWN_TIME);
                ucValueDown=GAL_YES;
            }
            else
            {
                if(CON_MONITER_STATUS_OVER==FLG_MONITOR_V_A_STATUS)
                {
                    Data3ByteBCDAdd1(RAM_VOLTAGE_A_MONITOR_OVER_TIME);
                    ucValueOver=GAL_YES;
                }
            }
            if(1==ReadDataDirect(RAM_VOLTAGE_A_MONITOR_TIME, 15, &Wr_data[0]))
            {
                ulDataErr=Bcd3DataToLong(&Wr_data[9])+Bcd3DataToLong(&Wr_data[12]);
                ulDataAll=Bcd3DataToLong(&Wr_data[0]);
                if(ulDataAll<=ulDataErr)
                {
                    ulDataErr=ulDataAll;
                }
                if(0 != ulDataAll)
                {
                    ulDataErr=((ulDataAll-ulDataErr)*10000)/ulDataAll;
                    LongToData3BCD(ulDataErr,&Wr_data[3]);
                    LongToData3BCD((10000-ulDataErr),&Wr_data[6]);
                    WriteDataDirect(&Wr_data[0],RAM_VOLTAGE_A_MONITOR_TIME, 15 );
                }
                
            }       
            // B phase
            if(METERTYPE_3_3!=PROGFUNCTION_TYPE_METER_TYPE  )
            {
                Data3ByteBCDAdd1(RAM_VOLTAGE_B_MONITOR_TIME);
                if(CON_MONITER_STATUS_DOWN==FLG_MONITOR_V_B_STATUS)
                {
                    Data3ByteBCDAdd1(RAM_VOLTAGE_B_MONITOR_DOWN_TIME);
                    ucValueDown=GAL_YES;
                }
                else
                {
                    if(CON_MONITER_STATUS_OVER==FLG_MONITOR_V_B_STATUS)
                    {
                        Data3ByteBCDAdd1(RAM_VOLTAGE_B_MONITOR_OVER_TIME);
                        ucValueOver=GAL_YES;
                    }
                }
                if(1==ReadDataDirect(RAM_VOLTAGE_B_MONITOR_TIME, 15, &Wr_data[0]))
                {
                    ulDataErr=Bcd3DataToLong(&Wr_data[9])+Bcd3DataToLong(&Wr_data[12]);
                    ulDataAll=Bcd3DataToLong(&Wr_data[0]);
                    if(ulDataAll<=ulDataErr)
                    {
                        ulDataErr=ulDataAll;
                    }
                    if(0 != ulDataAll)
                    {
                        ulDataErr=((ulDataAll-ulDataErr)*10000)/ulDataAll;
                        LongToData3BCD(ulDataErr,&Wr_data[3]);
                        LongToData3BCD((10000-ulDataErr),&Wr_data[6]);
                        WriteDataDirect(&Wr_data[0],RAM_VOLTAGE_B_MONITOR_TIME, 15 );
                    }
                    
                }
            }
            // C phase
            Data3ByteBCDAdd1(RAM_VOLTAGE_C_MONITOR_TIME);
            if(CON_MONITER_STATUS_DOWN==FLG_MONITOR_V_C_STATUS)
            {
                Data3ByteBCDAdd1(RAM_VOLTAGE_C_MONITOR_DOWN_TIME);
                ucValueDown=GAL_YES;
            }
            else
            {
                if(CON_MONITER_STATUS_OVER==FLG_MONITOR_V_C_STATUS)
                {
                    Data3ByteBCDAdd1(RAM_VOLTAGE_C_MONITOR_OVER_TIME);
                    ucValueOver=GAL_YES;
                }
            }
            if(1==ReadDataDirect(RAM_VOLTAGE_C_MONITOR_TIME, 15, &Wr_data[0]))
            {
                ulDataErr=Bcd3DataToLong(&Wr_data[9])+Bcd3DataToLong(&Wr_data[12]);
                ulDataAll=Bcd3DataToLong(&Wr_data[0]);
                if(ulDataAll<=ulDataErr)
                {
                    ulDataErr=ulDataAll;
                }
                if(0 != ulDataAll)
                {
                    ulDataErr=((ulDataAll-ulDataErr)*10000)/ulDataAll;
                    LongToData3BCD(ulDataErr,&Wr_data[3]);
                    LongToData3BCD((10000-ulDataErr),&Wr_data[6]);
                    WriteDataDirect(&Wr_data[0],RAM_VOLTAGE_C_MONITOR_TIME, 15 );
                }
                
            }
            
            
            // ALL phase
            Data3ByteBCDAdd1(RAM_VOLTAGE_ALL_MONITOR_TIME);
            if((GAL_YES==ucValueDown)||(GAL_YES==ucValueOver))
            {
                Data3ByteBCDAdd1(RAM_VOLTAGE_ALL_MONITOR_ERR_TIME);
            }
            if(GAL_YES==ucValueDown)
            {
                Data3ByteBCDAdd1(RAM_VOLTAGE_ALL_MONITOR_DOWN_TIME);
            }
            if(GAL_YES==ucValueOver)
            {
                Data3ByteBCDAdd1(RAM_VOLTAGE_ALL_MONITOR_OVER_TIME);

            }
            if(1==ReadDataDirect(RAM_VOLTAGE_ALL_MONITOR_ERR_TIME, 12, &Wr_data[0]))
            {
                ulDataErr=Bcd3DataToLong(&Wr_data[0]);
                ulDataAll=Bcd3DataToLong(&Wr_data[3]);
                if(ulDataAll<=ulDataErr)
                {
                    ulDataErr=ulDataAll;
                }
                if(0 != ulDataAll)
                {
                    ulDataErr=((ulDataAll-ulDataErr)*10000)/ulDataAll;
                    LongToData3BCD(ulDataErr,&Wr_data[6]);
                    LongToData3BCD((10000-ulDataErr),&Wr_data[9]);
                    WriteDataDirect(&Wr_data[0],RAM_VOLTAGE_ALL_MONITOR_ERR_TIME, 12 );
                }
            }
        }
    }
}




