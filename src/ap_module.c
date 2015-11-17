#define AP_MODULE_GLOBALS
#include "common.h"
#define CON_STATUS_MODULE_POWER_ON 1
#define CON_STATUS_MODULE_POWER_OFF 0


uchar ucModulePowerStatus;

uchar ucPlcRunStatusTime;

void ModuleInit(void)
{
    ucPlcRunStatusTime=0xff;
#if(CONFIG_METER_NO2COMM_MODE_WIRELESS==CONFIG_METER_NO2COMM_MODE)
    ModuleWirelessFlagInit();
#endif
}

#if(CONFIG_METER_NO2COMM_MODE_PLC==CONFIG_METER_NO2COMM_MODE)



void ModulePlcStatusReset(void)
{
    ucPlcRunStatusTime=0;
}

#endif

void ModuleEventAlarm(uchar ucType)
{
#if(CONFIG_METER_NO2COMM_MODE_WIRELESS==CONFIG_METER_NO2COMM_MODE)
    if(GAL_YES==ucType)
    {
        ModuleWirelessEventSet(1);
    }
#endif
}

#if(CONFIG_METER_NO2COMM_MODE_WIRELESS==CONFIG_METER_NO2COMM_MODE)
uchar WirelessStatusDelay;
void ModuleWirelessFlagInit(void)
{
    //无线标志复位初始化
    WirelessStatusDelay = 0;
    RAM[RAM_CURRENT_MODULE_DATA] = 0;
}

void ModuleWirelessEventReset(void)
{
    ClrHandModule();
}

void ModuleWirelessEventSet(uchar ucType)
{
    SetHandModule();
}

#endif
void ModuleMode(void)
{
    {
        
#if(CONFIG_METER_NO2COMM_MODE_PLC==CONFIG_METER_NO2COMM_MODE)
        if(0==ucPlcRunStatusTime)
        {
            ResetPlcRunStatus();
        }
        if(ucPlcRunStatusTime<10)
        {
            ucPlcRunStatusTime++;
        }
        if(ucPlcRunStatusTime>2)
        {
            SetPlcRunStatus();
        }
#endif

#if(CONFIG_METER_NO2COMM_MODE_WIRELESS==CONFIG_METER_NO2COMM_MODE)
        if(WirelessStatusDelay)
        {
            WirelessStatusDelay--;
        }
        if(WirelessStatusDelay == 0)
        {
            RAM[RAM_CURRENT_MODULE_DATA] = 0;
        }
#endif

#if 0
        
        if(0 != ucModulePowerOffDelay)
        {
            ucModulePowerOffDelay--;
        }
        if((0==ucModulePowerOffDelay)&&(CON_STATUS_MODULE_POWER_ON !=ucModulePowerStatus))
        {
            ModuleSetPowerOn();
        }
#endif
        
    }
}








































