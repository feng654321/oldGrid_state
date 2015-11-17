#define AP_RELAY_GLOBALS
#include "common.h"


#define CON_RELAY_STATUS_CHANGE_DELAY_TIME_10MS 20
uchar ucRelayAlarmPluseStatus;
uchar ucRelayModeSecond;
uchar ucRelayModeMinute;
// void RelayStatusOpen(void);
// void RelayStatusClose(void);
uchar RelayEventRecord(uchar ucType, ulong ulCodeId);
uchar RelayEventRecord(uchar ucType, ulong ulCodeId)
{
    ulong ulDataAddr;
    ulDataAddr=SetTwoTableNextPoint(ucType);
    if(GAL_GETTWOTABLE_ADDRERR == ulDataAddr)
    {
        return 0;
    }
    else
    {
        SetTimeDataToPoint(&Wr_data[0]);
        memcpy(&Wr_data[6], (uchar *)&(ulCodeId), 4);
        memcpy(&Wr_data[10], &RAM[RAM_KWH_F_ALL], 5);
        memcpy(&Wr_data[15], &RAM[RAM_KWH_R_ALL], 5);
        memcpy(&Wr_data[20], &RAM[RAM_KVARH_Q1_ALL], 5);
        memcpy(&Wr_data[25], &RAM[RAM_KVARH_Q2_ALL], 5);
        memcpy(&Wr_data[30], &RAM[RAM_KVARH_Q3_ALL], 5);
        memcpy(&Wr_data[35], &RAM[RAM_KVARH_Q4_ALL], 5);
        memcpy(&Wr_data[40], &RAM[RAM_KVARH_C1_ALL], 5);
        memcpy(&Wr_data[45], &RAM[RAM_KVARH_C2_ALL], 5);
        
        // VOLTAGE
        Wr_data[50]=(RAM[RAM_CURRENT_V_A+2]<<4)+ (RAM[RAM_CURRENT_V_A+1]>>4);
        Wr_data[51]=(RAM[RAM_CURRENT_V_A+3]<<4)+ (RAM[RAM_CURRENT_V_A+2]>>4);
        // CURRENT
        Wr_data[52]=(RAM[RAM_CURRENT_I_A+1]<<4)+ (RAM[RAM_CURRENT_I_A+0]>>4);
        Wr_data[53]=(RAM[RAM_CURRENT_I_A+2]<<4)+ (RAM[RAM_CURRENT_I_A+1]>>4);
        Wr_data[54]=(RAM[RAM_CURRENT_I_A+3]<<4)+ (RAM[RAM_CURRENT_I_A+2]>>4);
        // KW
        Wr_data[55]=RAM[RAM_CURRENT_KW_A+1]; 
        Wr_data[56]=RAM[RAM_CURRENT_KW_A+2]; 
        Wr_data[57]=RAM[RAM_CURRENT_KW_A+3]; 
        // KVAR
        Wr_data[58]=RAM[RAM_CURRENT_KVAR_A+1]; 
        Wr_data[59]=RAM[RAM_CURRENT_KVAR_A+2]; 
        Wr_data[60]=RAM[RAM_CURRENT_KVAR_A+3]; 
        // FACTOR
        Wr_data[61]=RAM[RAM_CURRENT_FACTOR_A+2];
        Wr_data[62]=RAM[RAM_CURRENT_FACTOR_A+3];
        
        memcpy(&Wr_data[63], &RAM[RAM_KWH_B_F_ALL+1], 4);
        memcpy(&Wr_data[67], &RAM[RAM_KWH_B_R_ALL+1], 4);
		memcpy(&Wr_data[71], &RAM[RAM_KVARH_B_C1_ALL+1], 4);
		memcpy(&Wr_data[75], &RAM[RAM_KVARH_B_C2_ALL+1], 4);
        // VOLTAGE
        Wr_data[79]=(RAM[RAM_CURRENT_V_B+2]<<4)+ (RAM[RAM_CURRENT_V_B+1]>>4);
        Wr_data[80]=(RAM[RAM_CURRENT_V_B+3]<<4)+ (RAM[RAM_CURRENT_V_B+2]>>4);
        // CURRENT
        Wr_data[81]=(RAM[RAM_CURRENT_I_B+1]<<4)+ (RAM[RAM_CURRENT_I_B+0]>>4);
        Wr_data[82]=(RAM[RAM_CURRENT_I_B+2]<<4)+ (RAM[RAM_CURRENT_I_B+1]>>4);
        Wr_data[83]=(RAM[RAM_CURRENT_I_B+3]<<4)+ (RAM[RAM_CURRENT_I_B+2]>>4);
        // KW
        Wr_data[84]=RAM[RAM_CURRENT_KW_B+1]; 
        Wr_data[85]=RAM[RAM_CURRENT_KW_B+2]; 
        Wr_data[86]=RAM[RAM_CURRENT_KW_B+3]; 
        // KVAR
        Wr_data[87]=RAM[RAM_CURRENT_KVAR_B+1]; 
        Wr_data[88]=RAM[RAM_CURRENT_KVAR_B+2]; 
        Wr_data[89]=RAM[RAM_CURRENT_KVAR_B+3]; 
        // FACTOR
        Wr_data[90]=RAM[RAM_CURRENT_FACTOR_B+2];
        Wr_data[91]=RAM[RAM_CURRENT_FACTOR_B+3];
        
        
        memcpy(&Wr_data[92], &RAM[RAM_KWH_C_F_ALL+1], 4);
        memcpy(&Wr_data[96], &RAM[RAM_KWH_C_R_ALL+1], 4);
		memcpy(&Wr_data[100], &RAM[RAM_KVARH_C_C1_ALL+1], 4);
		memcpy(&Wr_data[104], &RAM[RAM_KVARH_C_C2_ALL+1], 4);
        // VOLTAGE
        Wr_data[108]=(RAM[RAM_CURRENT_V_C+2]<<4)+ (RAM[RAM_CURRENT_V_C+1]>>4);
        Wr_data[109]=(RAM[RAM_CURRENT_V_C+3]<<4)+ (RAM[RAM_CURRENT_V_C+2]>>4);
        // CURRENT
        Wr_data[110]=(RAM[RAM_CURRENT_I_C+1]<<4)+ (RAM[RAM_CURRENT_I_C+0]>>4);
        Wr_data[111]=(RAM[RAM_CURRENT_I_C+2]<<4)+ (RAM[RAM_CURRENT_I_C+1]>>4);
        Wr_data[112]=(RAM[RAM_CURRENT_I_C+3]<<4)+ (RAM[RAM_CURRENT_I_C+2]>>4);
        // KW
        Wr_data[113]=RAM[RAM_CURRENT_KW_C+1]; 
        Wr_data[114]=RAM[RAM_CURRENT_KW_C+2]; 
        Wr_data[115]=RAM[RAM_CURRENT_KW_C+3]; 
        // KVAR
        Wr_data[116]=RAM[RAM_CURRENT_KVAR_C+1]; 
        Wr_data[117]=RAM[RAM_CURRENT_KVAR_C+2]; 
        Wr_data[118]=RAM[RAM_CURRENT_KVAR_C+3]; 
        // FACTOR
        Wr_data[119]=RAM[RAM_CURRENT_FACTOR_C+2];
        Wr_data[120]=RAM[RAM_CURRENT_FACTOR_C+3];
        WriteDataDirect(&Wr_data[0], ulDataAddr, 121);
    }
    ClrFlashMode();
    return 1;
}

void RelayOpenEventRecord(ulong uttttlCommUserCode)
{
    Data3ByteBCDAdd1(EPL_TOTAL_RELAY_OPEN_COUNT);
    RelayEventRecord(TYPE_RELAY_OPEN_RECORD,uttttlCommUserCode);
}



void RelayCloseEventRecord(ulong uttttlCommUserCode)
{
    Data3ByteBCDAdd1(EPL_TOTAL_RELAY_CLOSE_COUNT);
    RelayEventRecord(TYPE_RELAY_CLOSE_RECORD,uttttlCommUserCode);
}

void RelayStatusOpen(void)
{
#if(CONFIG_METER_RELAY_MODE_INSIDE == CONFIG_METER_RELAY_MODE)
    ClrRelayControlOn();
    SetRelayControlOff();
    uiRelayStatusChangeDelayTime=CON_RELAY_STATUS_CHANGE_DELAY_TIME_10MS;
#endif
#if(CONFIG_METER_RELAY_MODE_OUTSIDE== CONFIG_METER_RELAY_MODE)
    ucRelayOutsideOpen=GAL_NO;
    uiRelayStatusChangeDelayTime=CON_RELAY_STATUS_CHANGE_START_TIME_10MS;
//  ucRelayModeSecond=0xff;
#endif
}
void RelayStatusClose(void)
{
#if(CONFIG_METER_RELAY_MODE_INSIDE == CONFIG_METER_RELAY_MODE)
    SetRelayControlOn();
    ClrRelayControlOff();
    uiRelayStatusChangeDelayTime=CON_RELAY_STATUS_CHANGE_DELAY_TIME_10MS;
#endif
#if(CONFIG_METER_RELAY_MODE_OUTSIDE== CONFIG_METER_RELAY_MODE)
    ucRelayOutsideOpen=GAL_YES;
    uiRelayStatusChangeDelayTime=0;
//  ucRelayModeSecond=0xff;
#endif
}
#if(CONFIG_METER_RELAY_MODE_INSIDE == CONFIG_METER_RELAY_MODE)
void RelayStatusHolding(void)
{
    ClrRelayControlOn();
    ClrRelayControlOff();   
}
#endif

#if(CONFIG_METER_RELAY_MODE_OUTSIDE== CONFIG_METER_RELAY_MODE)
void RelayStatusCheckOnKwhAdd(void)
{
    if(uiRelayStatusChangeDelayTime>CON_RELAY_STATUS_CHANGE_END_TIME_10MS)
    {
        uiRelayStatusChangeDelayTime=0;
    }
    ucRelayModeSecond=0xff;
}
#endif



void RelayInit(void)
{
//  ucRelayReQuestCloseByMoney=GAL_NO;
//  ucRelayReQuestCloseByNet=GAL_NO;
//  ucRelayReQuestOpenByNet=GAL_NO;
    uiRelayStatusChangeDelayTime=0;
#if(CONFIG_METER_RELAY_MODE_INSIDE == CONFIG_METER_RELAY_MODE)
    RelayStatusHolding();
#endif
#if(CONFIG_METER_RELAY_MODE_OUTSIDE== CONFIG_METER_RELAY_MODE)
    ucRelayOutsideOpen=GAL_NO;
    ClrRelayControlOff();
#endif
    ucRelayAlarmPluseStatus=GAL_NO;
    ucRelayModeSecond=0xff;
}

void SetRelayAlarmPluseStatus(uchar ucStatus)
{
    if(GAL_YES!=ucStatus)
    {
        ucStatus=GAL_NO;
    }
    ucRelayAlarmPluseStatus=ucStatus;
}

void RelayMode(void)
{
    if(ucRelayModeSecond!=RSOFT_RTC_SECOND)
    {
        ucRelayModeSecond=RSOFT_RTC_SECOND;
        if(ucRelayAlarmPluseStatus)
        {
#if(CONFIG_METER_RELAY_MODE_DISABLE!=CONFIG_METER_RELAY_MODE)
            SetRelayAlarmPluse();
//          ClrRelayControlOn();
//          SetRelayControlOff();
#else
            SetRelayAlarmPluse();
            ClrRelayControlOn();
//          SetRelayControlOff();
#endif
        }
        else
        {
#if(CONFIG_METER_RELAY_MODE_DISABLE!=CONFIG_METER_RELAY_MODE)
            ClrRelayAlarmPluse();
//          ClrRelayControlOn();
//          ClrRelayControlOff();
#else
            ClrRelayAlarmPluse();
            ClrRelayControlOn();
//          ClrRelayControlOff();
#endif
        }

#if(CONFIG_METER_RELAY_MODE_OUTSIDE== CONFIG_METER_RELAY_MODE)
//      if(ucRelayModeMinute!=RSOFT_RTC_MINUTE)
//      {
//          ucRelayModeMinute=RSOFT_RTC_MINUTE;
//          if(uiRelayStatusChangeDelayTime>CON_RELAY_STATUS_CHANGE_END_TIME_10MS)
//          {
//              RelayStatusCheckOnKwhAdd();
//          }
//      }
#endif
    }
}













