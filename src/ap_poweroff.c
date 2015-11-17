#define AP_POWEROFF_GLOBALS
#include "common.h"



/*********************************************************************
功能：  上电操作过程
范围：  应用层直接调用
注释：  无
作者：  张龙
版本：  V1.0
最后修改时间：2009-01-19
修改说明：创建
********************************************************************/

/*uchar ucPowerOffDataSavePoint;

void PowerOffDataSaveInit(void)
{
    ucPowerOffDataSavePoint=0;
    PowerOffWaitTimeStep10mS=350;// step = 10ms ,total =3 dot 5 S
}*/


uchar PowerOffDataSave(void)
{
    //ucPowerOffDataSavePoint++;
    //switch(ucPowerOffDataSavePoint)
    {
    //    case 0:
    //        return (0);
    //    case 1:
            SaveEventAccTime(); // 掉电保存所有事件累加时间
    //        return (0);
    //    case 2:
#if(CONFIG_METER_STOPEVENT_POWERON == GAL_YES)    
            if(FLG_A_LOSS_VOLTAGE_STATUS)
            {
                WriteDataDirect(&RAM[RAM_CURRENT_LOSS_AV_AH_ALL], EPL_POWEROFF_SAVEDATA_ADDR+20*0, 20);
            }
            if(FLG_B_LOSS_VOLTAGE_STATUS)
            {
                WriteDataDirect(&RAM[RAM_CURRENT_LOSS_BV_AH_ALL], EPL_POWEROFF_SAVEDATA_ADDR+20*1, 20);
            }
            if(FLG_C_LOSS_VOLTAGE_STATUS)
            {
                WriteDataDirect(&RAM[RAM_CURRENT_LOSS_CV_AH_ALL], EPL_POWEROFF_SAVEDATA_ADDR+20*2, 20);
            }
            if(FLG_A_DOWN_VOLTAGE_STATUS)
            {
                WriteDataDirect(&RAM[RAM_CURRENT_DOWN_AV_AH_ALL], EPL_POWEROFF_SAVEDATA_ADDR+20*3, 20);
            }
            if(FLG_B_DOWN_VOLTAGE_STATUS)
            {
                WriteDataDirect(&RAM[RAM_CURRENT_DOWN_BV_AH_ALL], EPL_POWEROFF_SAVEDATA_ADDR+20*4, 20);
            }
            if(FLG_C_DOWN_VOLTAGE_STATUS)
            {
                WriteDataDirect(&RAM[RAM_CURRENT_DOWN_CV_AH_ALL], EPL_POWEROFF_SAVEDATA_ADDR+20*5, 20);
            }
            if(FLG_A_OVER_VOLTAGE_STATUS)
            {
                WriteDataDirect(&RAM[RAM_CURRENT_OVER_AV_AH_ALL], EPL_POWEROFF_SAVEDATA_ADDR+20*6, 20);
            }
            if(FLG_B_OVER_VOLTAGE_STATUS)
            {
                WriteDataDirect(&RAM[RAM_CURRENT_OVER_BV_AH_ALL], EPL_POWEROFF_SAVEDATA_ADDR+20*7, 20);
            }
            if(FLG_C_OVER_VOLTAGE_STATUS)
            {
                WriteDataDirect(&RAM[RAM_CURRENT_OVER_CV_AH_ALL], EPL_POWEROFF_SAVEDATA_ADDR+20*8, 20);
            }
            if(FLG_A_CUT_VOLTAGE_STATUS)
            {
                WriteDataDirect(&RAM[RAM_CURRENT_CUT_AV_AH_ALL], EPL_POWEROFF_SAVEDATA_ADDR+20*9, 20);
            }
            if(FLG_B_CUT_VOLTAGE_STATUS)
            {
                WriteDataDirect(&RAM[RAM_CURRENT_CUT_BV_AH_ALL], EPL_POWEROFF_SAVEDATA_ADDR+20*10, 20);
            }
            if(FLG_C_CUT_VOLTAGE_STATUS)
            {
                WriteDataDirect(&RAM[RAM_CURRENT_CUT_CV_AH_ALL], EPL_POWEROFF_SAVEDATA_ADDR+20*11, 20);
            }
            if(FLG_UNBALANCE_VOLTAGE_STATUS)
            {
                WriteDataDirect(&RAM[RAM_CURRENT_UNBALANCE_VOLTAGE_MAXDATA], EPL_POWEROFF_SAVEDATA_ADDR+20*12, 3);
            }
            if(FLG_UNBALANCE_CURRENT_STATUS)
            {
                WriteDataDirect(&RAM[RAM_CURRENT_UNBALANCE_CURRENT_MAXDATA], EPL_POWEROFF_SAVEDATA_ADDR+20*12+3, 3);
            }
            
            WriteDataDirect(&RAM[RAM_CURRENT_METER_STATUS01], EPL_POWEROFF_SAVEDATA_ADDR+246, 19);
#endif            
            if(FLG_DEMANDOVER_STATUS)
            {
                WriteDataDirect((uchar*)&DemandOverData[0], EPL_POWEROFF_SAVEDATA_ADDR+246+19, DEMAND_OVER_NUM*BYTES_PER_DEMAND);
            }
        //    return (0);
        //default:
        //    ucPowerOffDataSavePoint=200;
            return (1);

    }

}


void PowerOffDataMustSave(void)
{
#if(GAL_YES == BKP_VIRTUAL_FEATURE)
    VirtualBPKRegSave(EPL_BKP_VIRTURL_BAK_ADDR);
#endif
    
    //if(FLG_SAVE_EC)
    if(g_KwhSavedMode == KWH_SAVED_MODE_MIN_SAVED)
    {
        WritePower2rom(0xff);
        WriteAlluse2rom();
        //FLG_SAVE_EC = 0;
    }
    SetPowerClacResidue();

    if(FLG_SAVE_MD)
    {
        SaveMDByTimeStamp();
        FLG_SAVE_MD = 0;
    }

    if(FLG_SAVE_LOAD)
    {
        SaveLoadPtrToEE();
        FLG_SAVE_LOAD = 0;
}
    WriteDataDirect(&RAM[RAM_PASSWORD_ERR_COUNT_START], EPL_PASSWORD_ERR_COUNT_START, 33);

    ModuleInit();
    //SaveProgramTime();
    SavePasswordInf();
#ifdef TIME_FASTER_TEST
    TimeFasterTestPoweroff();
#endif
#if(MEM_ERR_RECORD_ENABLE == GAL_YES)
    MemErrCountSave();
#endif 

}

#if(CONFIG_METER_STOPEVENT_POWERON == GAL_NO)    
void PowerOffStopIfStart(void)
{
	//CoverOpenStopIfStart();
	CutCurrentStopIfStart();
	CutVoltageStopIfStart();
	DownVoltageStopIfStart();
	DemandOverStopIfStart();
	LossCurrentStopIfStart();
	LossVoltageStopIfStart();
	OrderCurrentStopIfStart();
	OrderVoltageStopIfStart();
	OverCurrentStopIfStart();
	OverPowerStopIfStart();
	OverVoltageStopIfStart();
	ReversePowerStopIfStart();
	UnbalanceCurrentStopIfStart();
	UnbalanceVoltageStopIfStart();
	OverTotalCosStopIfStart();
	//AuxPowerStopIfStart();
}
#endif

void PowerOffSaveAllData(void)
{
    PowerOffDataMustSave();
    PowerOffDataSave();
#if(CONFIG_METER_STOPEVENT_POWERON == GAL_NO)    
    PowerOffStopIfStart();
#endif
}





