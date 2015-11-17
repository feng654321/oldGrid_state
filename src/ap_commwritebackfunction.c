#define AP_COMMWRITEBACKFUNCTION_GLOBALS
#include "common.h"
#define CON_NEEDCLR_YES     0x5A69
#define CON_NEEDCLR_NO  0x3355
#define CON_NEEDCLR_PASSWORD        0x3A5C6953
#define CON_NEEDCLR_PASSWORDCLR 0x00000000
ulong ulNeedClrPassWord;
u16 ucNeedClrDemandAll;
u16 ucNeedClrPowerAll;
u16 ucNeedClrInFactory;
u16 ucNeedClrEventAll;
ulong ulNeedClrEventCode;
uchar ucTimeChanged;

extern struct update_param_shm_st *g_p_update_param_shm;

//生产用函数

uchar AddDataInit(void)
//生产增加功能，初始化功能类数据    
{
    u16 l;
    PROGFUNCTION_METER_FACTORY = METER_IN_FACTORY;
    PROGFUNCTION_METER_ADJUST = METER_IN_FACTORY;
    PROGFUNCTION_METER_TCLOCK = METER_TCLOCK_IDLE;
    for(l=( 0x0000FFFF &CFGDIR_PRO_METER_ENABLE);l<=( 0x0000FFFF &CFGDIR_PRO_PROGRAM_OPEN_ENABLE);l++)
    {
        SYSTEMPROGFUNCTION[l] =GAL_YES;
    }
    SYSTEMPROGFUNCTION[ 0x0000FFFF & CFGDIR_TYPE_METER_TYPE ]=METERTYPE_3_4;
    // AA  脉冲常数  AA
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_TYPE_PLUS_CONSTANT + 0) ]= 0x00; // low
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_TYPE_PLUS_CONSTANT + 1) ]= 0x64; // middle
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_TYPE_PLUS_CONSTANT + 2) ]= 0x00; // high
    // AA  额定电压  AA
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_TYPE_VOLTAGE_UN + 0) ] = 0x00;   // 220 dot 0 V
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_TYPE_VOLTAGE_UN + 1) ] = 0x00;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_TYPE_VOLTAGE_UN + 2) ] = 0x20;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_TYPE_VOLTAGE_UN + 3) ] = 0x02;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_TYPE_VOLTAGE_UN + 4) ] = 0x00;
    // AA  额定电流  AA
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_TYPE_CURRENT_IB + 0) ] = 0x00;   // 1 dot 5 A
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_TYPE_CURRENT_IB + 1) ] = 0x50;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_TYPE_CURRENT_IB + 2) ] = 0x01;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_TYPE_CURRENT_IB + 3) ] = 0x00;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_TYPE_CURRENT_IB + 4) ] = 0x00;
    // AA  最大电流  AA
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_TYPE_CURRENT_IMAX + 0) ] = 0x00; // 6 dot 0 A
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_TYPE_CURRENT_IMAX + 1) ] = 0x00;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_TYPE_CURRENT_IMAX + 2) ] = 0x06;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_TYPE_CURRENT_IMAX + 3) ] = 0x00;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_TYPE_CURRENT_IMAX + 4) ] = 0x00;

    // AA  功率倍数   功率除数  AA
    PROGFUNCTION_COEF_KW_MUL = 0x2;// 32
    PROGFUNCTION_COEF_KW_DIV = 0x1;

    // AA  有功功率系数  AA
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_CALC_KW + 0) ] = 0x05;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_CALC_KW + 1) ] = 0x96;
    // AA  无功功率系数  AA
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_CALC_KVAR + 0) ] = 0x05;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_CALC_KVAR + 1) ] = 0x96;
    // AA  视在功率系数  AA
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_CALC_KVA + 0) ] = 0x05;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_CALC_KVA + 1) ] = 0x96;

    // AA  电流系数  AA
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_CURRENT_A + 0) ] = 0xb0;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_CURRENT_A + 1) ] = 0xb0;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_CURRENT_B + 0) ] = 0xb0;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_CURRENT_B + 1) ] = 0xb0;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_CURRENT_C + 0) ] = 0xb0;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_CURRENT_C + 1) ] = 0xb0;

    // AA  电压系数  AA
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_VOLTAGE_A + 0) ] = 0x14;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_VOLTAGE_A + 1) ] = 0xE5;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_VOLTAGE_B + 0) ] = 0x14;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_VOLTAGE_B + 1) ] = 0xE5;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_VOLTAGE_C + 0) ] = 0x14;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_VOLTAGE_C + 1) ] = 0xE5;

    // AA  脉冲防潜动系数  AA
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_POWER_OUTTIME + 0) ] = 0x03;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_POWER_OUTTIME + 1) ] = 0x54;

    // AA  脉冲防潜动系数  AA
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_DEMAND_STARTCOUNT + 0) ] = 0x00;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_DEMAND_STARTCOUNT + 1) ] = 0x06;
    PROGFUNCTION_COEF_METER_PULSE_STARTUP=8;
    PROGFUNCTION_COEF_METER_DATA_STARTUP=5;

    PROGFUNCTION_COEF_BALANCE_DAY_NUM = 0x03;
    PROGFUNCTION_MODE_POWER_CALC_POINT = 0x02;
    PROGFUNCTION_MODE_BROADCAST_TIME = 0x02;
    PROGFUNCTION_COEF_BROADCAST_TIME_EVERYDAY=0x05;
    PROGFUNCTION_COEF_BROADCAST_TIME_FIXED=60;
    PROGFUNCTION_MODE_DEMAND_HANDCLR_ENABLE = GAL_YES;
    
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_DEMAND_HANDCLR_LOCKTIME + 0) ] = 0x27;
    SYSTEMPROGFUNCTION[ 0x0000FFFF & (CFGDIR_COEF_DEMAND_HANDCLR_LOCKTIME + 1) ] = 0x60;
    PROGFUNCTION_MODE_DEMAND_CALC_POINT_FIXED = GAL_NO;

    // AA  事件显示报警方式  AA
    PROGFUNCTION_MODE_DISPLAYALARM_ORDER_VOLTAGE = 0x00;
    PROGFUNCTION_MODE_DISPLAYALARM_LOSS_VOLTAGE = 0x02;
    PROGFUNCTION_MODE_DISPLAYALARM_CUT_VOLTAGE = 0x01;
    PROGFUNCTION_MODE_DISPLAYALARM_OVER_VOLTAGE = 0x00;
    PROGFUNCTION_MODE_DISPLAYALARM_DOWN_VOLTAGE = 0x00;
    PROGFUNCTION_MODE_DISPLAYALARM_ORDER_CURRENT = 0x00;
    PROGFUNCTION_MODE_DISPLAYALARM_LOSS_CURRENT = 0x02;
    PROGFUNCTION_MODE_DISPLAYALARM_CUT_CURRENT = 0x00;
    PROGFUNCTION_MODE_DISPLAYALARM_OVER_CURRENT = 0x00;

    // AA  电池报警电压  AA
    PROGFUNCTION_COEF_ALARM_BATVOLTAGE_CLOCK = 0x24;
    PROGFUNCTION_COEF_ALARM_BATVOLTAGE_POWEROFF=0x31;
    // AA  电池报警方式  AA
    PROGFUNCTION_MODE_DISPLAYALARM_BAT_CLOCK=0x01;
    PROGFUNCTION_MODE_DISPLAYALARM_BAT_POWEROFF= 0x01;

    memcpy(&Wr_data[0], &SYSTEMPROGFUNCTION[0], CON_SYSTEMPROFUNCTION_LEN);
    for(l=0;l<8;l++)
    {
        WriteProgramData(&Wr_data[l*32],EPL_DATA_PROGRAM_START+l*32, 32);
        ClearWatchDog();
    }

    ProgFunctionLoad();
    //ClockFreqOffsetDefaultSet(0x0770);
    return 1;
}
uchar AddDataOperate(void)
{
return 1;
}
//生产用函数
uchar CWBFTimeChange(void)
// AA 时间更改所涉及到的数据   AA
// AA  日期及星期  AA
// AA  时间  AA
// AA    AA
// AA    AA
{
    ucTimeChanged=GAL_YES;
    CWBFPriceChange();
//  ucDemandPriceDemandTimeChange=GAL_YES;
    DemandDataInit();
    RecordPointReset();
    return 1;
}



uchar CWBFDemandCycleChange(void)
// AA  最大需量周期  AA
// AA  滑差时间  AA
{
    
    return 1;
}
uchar CWBFCommAddrChange(void)
{
#if(CONFIG_METER_NO2COMM_MODE_PLC==CONFIG_METER_NO2COMM_MODE)
    ModulePlcStatusReset();
#endif
    return 1;
}



uchar CWBFPriceChange(void)
// AA 两套时区表切换时间   AA
// AA 两套时段表切换时间   AA
// AA 年时区数   AA
// AA 时间段表数   AA
// AA 日时段表数   AA
// AA 费率数   AA
// AA 公共假日数   AA
// AA 周休日特征字   AA
// AA 周休日采用的日时段表号  AA
// AA 时区表数据   AA
// AA 时段表数据   AA
// AA    AA

{
    InitPriceSwitch();
    // ucDemandPriceDemandTimeChange=GAL_YES;
    return 1;
}

uchar CWBFDisplayChange(void)
{
    ucCoefCheckDisplayReNewRequest=GAL_YES;
    return 1;
}
uchar CWBFPowerCharacterChange(void)
{
    return 1;
}
uchar CWBFChargeRecordChange(void)
// AA   负荷记录起始时间   AA
// AA   负荷记录时间间隔   AA
// AA    AA
{
    return 1;
}
uchar CWBFBalanceDayChange(void)
// AA 每月结算日   AA
// AA    AA
// AA    AA
{
    return 1;
}
uchar CWBFFreezeInstantRecord(ulong uId)
{
    if(0x99999999==uId)
    {
        FlgFreezeInstant=GAL_YES;
    }
    else
    {
        WriteCoefDataWithSync((uchar*)&uId,EPL_COEF_FREEZE_TIME,4);
    }
    return 1;
}
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
uchar CWBFCardDataIsSet(void)
{
    GetPrepayRunPara();
    DealPrepayAlarm();
    return 1;
}
#endif
uchar CWBFMeterAllClr_InFactory(void)
{
    ulNeedClrPassWord=CON_NEEDCLR_PASSWORD;
    ucNeedClrPowerAll=CON_NEEDCLR_YES;
    ucNeedClrInFactory = CON_NEEDCLR_YES;
    return 1;
}
uchar CWBFMaxDemandClr(void)
{
    ulNeedClrPassWord=CON_NEEDCLR_PASSWORD;
    ucNeedClrDemandAll=CON_NEEDCLR_YES;
    return 1;
}
uchar CWBFMeterAllClr(void)
{
    ulNeedClrPassWord=CON_NEEDCLR_PASSWORD;
    ucNeedClrPowerAll=CON_NEEDCLR_YES;
    return 1;
}
uchar CWBFEventDataClr( ulong ulCode)
{
    if(1==EventClrFromCodeCan(ulCode))
    {
        ulNeedClrPassWord=CON_NEEDCLR_PASSWORD;
        ucNeedClrEventAll=CON_NEEDCLR_YES;
        ulNeedClrEventCode=ulCode;
        return 1;
    }
    return 0;
}
uchar CWBFRelayCommand(uchar *ucPoint)
{
    u16 uiCode;
    uchar ucReturn;
    uiCode=*(ucPoint+5);
    uiCode=uiCode*256+*(ucPoint+4);
    memcpy((uchar *) &utlCommUserCode, ucPoint, 4);
    ucReturn=0;
    switch(uiCode)
    {
        case 0xaa11:
            // ucRelayReQuestCloseByNet = GAL_YES;
            ucReturn=1;
            break;
        case 0xee11:

            // ucRelayReQuestOpenByNet = GAL_YES;
            ucReturn=1;
            break;
        default:
            ucReturn=0;
            break;
    }
    return ucReturn;
}

void CWBFCommIrSetData(void)
{
    FLG_COMM_IR_DATASET_STATUS=GAL_YES;
    ClrHandModule();
}
/*************************************************************
Function: 卡操作之后，引起的变化
Input:无
Output: 无
Application area:  
Explain: 
Modification register:
**************************************************************/
void MeterParaChangeBringEvent(void)
{
    CWBFPriceChange();
}



/*
uchar CWBFWriteFromIr(void)
{

    
}
uchar CWBFReadFromModule(void)
{
    
}

*/

void ProgramEventInit(void)
{
    ulNeedClrPassWord=CON_NEEDCLR_PASSWORDCLR;
    ucNeedClrDemandAll=CON_NEEDCLR_NO;
    ucNeedClrPowerAll=CON_NEEDCLR_NO;
    ucNeedClrEventAll=CON_NEEDCLR_NO;
    ucNeedClrInFactory=CON_NEEDCLR_NO;
    ulNeedClrEventCode=0x00;
    ucCoefCheckDisplayReNewRequest=GAL_NO;
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
    PURCHASE_ENERGY_RECORD_FLAG=GAL_NO;
#endif
}


uchar ProgramEventDemandClr(void)
{
    ulong ulTempAddr;
    ulTempAddr=SetTwoTableNextPoint(TYPE_PROGRAM_DEMANDCLR_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR == ulTempAddr)
    {
        return 0;   
    }
    else
    {
        SetTimeDataToPoint(&Wr_data[0]);
        memcpy(&Wr_data[6], (uchar * )&utlCommUserCode, 4);
        WriteDataDirect(&Wr_data[0], ulTempAddr, 10);
        WriteDataDirect(&RAM[RAM_DEMAND_DATA_START], ulTempAddr+10, BYTES_DEMAND_TOTAL);
        // AA  对应编程次数  + 1 AA 
        Data3ByteBCDAdd1(EPL_CLR_DEMAND_COUNT);
    }
    ClrFlashMode();
    return 1;
    
}

uchar ProgramEventPowerClr(void)
{
    ulong ulTempAddr;
    ulTempAddr=SetTwoTableNextPoint(TYPE_PROGRAM_METERCLR_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR == ulTempAddr)
    {
        return 0;   
    }
    else
    {
        SetTimeDataToPoint(&Wr_data[0]);
        memcpy(&Wr_data[6], (uchar * )&utlCommUserCode, 4);
        WriteDataDirect(&Wr_data[0], ulTempAddr, 10);
        //-10是因为总空间需要1025，而实际分配只有1024(所以干脆去掉无用的铜损铁损电量空间)
        WriteDataDirect(&RAM[RAM_KWH_ALL_START], ulTempAddr+10, BYTES_KWH_TOTAL-10); 
        // AA  对应编程次数  + 1 AA 
        Data3ByteBCDAdd1(EPL_CLR_METER_COUNT);
    }
    ClrFlashMode();
    return 1;
}

uchar ProgramEventMeterClrAll(ulong  ultEventCode)
{
    ulong ulTempAddr;
    ulTempAddr=SetTwoTableNextPoint(TYPE_PROGRAM_EVENTCLR_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR == ulTempAddr)
    {
        return 0;   
    }
    else
    {
        SetTimeDataToPoint(&Wr_data[0]);
        memcpy(&Wr_data[6], (uchar * )&utlCommUserCode, 4);
        memcpy(&Wr_data[10], (uchar * )&ultEventCode, 4);
        WriteDataDirect(&Wr_data[0], ulTempAddr, 14);
        // AA  对应编程次数  + 1 AA 
        Data3ByteBCDAdd1(EPL_CLR_EVENT_COUNT);
    }
    ClrFlashMode();
    return 1;
}
uchar ProgramEventTimeChange(uchar * ucScr)
{
    ulong ulTempAddr;
//  ulong ulTempData;
    // AA  计算时间差，如果时间差大于30分钟  AA
    // AA   则对负荷记录进行处理，否则不处理  AA
    // AA  -->Start  AA
    SetTimeDataToPoint(&Wr_data[0]);
    
    // AA  -->End  AA
    ulTempAddr=SetTwoTableNextPoint(TYPE_PROGRAM_TIME_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR == ulTempAddr)
    {
        return 0;   
    }
    else
    {
        memcpy(&Wr_data[0], (uchar * )&utlCommUserCode, 4);
        SetTimeDataToPoint(&Wr_data[4]);
        memcpy(&Wr_data[10], ucScr, 6);
        WriteDataDirect(&Wr_data[0], ulTempAddr, 16);
        // AA  对应编程次数  + 1 AA 
        Data3ByteBCDAdd1(EPL_PROGRAM_TIME_COUNT);
    }
    ClrFlashMode();
    return 1;
}

uchar ProgramEventDayTableChange(void)
{
    ulong ulTempAddr;
    ulTempAddr=SetTwoTableNextPoint(TYPE_PROGRAM_DAYTABLE_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR == ulTempAddr)
    {
        return 0;   
    }
    else
    {
        SetTimeDataToPoint(&Wr_data[0]);
        memcpy(&Wr_data[6], (uchar * )&utlCommUserCode, 4);
        
        memcpy(&Wr_data[10], &RAM[RAM_SEASON1_DAYTABLE1_PERIOD01+0], 336);
        memcpy(&Wr_data[10+336], &RAM[RAM_SEASON2_DAYTABLE1_PERIOD01+0], 512-336-10);
        WriteDataDirect(&Wr_data[0], ulTempAddr+512*0, 512);
        
        memcpy(&Wr_data[0], &RAM[RAM_SEASON2_DAYTABLE1_PERIOD01+512-336-10], 336*2+10-512);
        WriteDataDirect(&Wr_data[0], ulTempAddr+512*1, 336*2+10-512);
        // AA  对应编程次数  + 1 AA 
        Data3ByteBCDAdd1(EPL_PROGRAM_PERIOD_COUNT);
    }
    ClrFlashMode();
    return 1;
}

uchar ProgramEventSeasonTableChange(void)
{
    ulong ulTempAddr;
    ulTempAddr=SetTwoTableNextPoint(TYPE_PROGRAM_SEASON_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR == ulTempAddr)
    {
        return 0;   
    }
    else
    {
        SetTimeDataToPoint(&Wr_data[0]);
        memcpy(&Wr_data[6], (uchar * )&utlCommUserCode, 4);
        
        memcpy(&Wr_data[10], &RAM[RAM_SEASON1_DAYTABLE_CHANGE01], 42);
        memcpy(&Wr_data[10+42], &RAM[RAM_SEASON2_DAYTABLE_CHANGE01], 42);
        WriteDataDirect(&Wr_data[0], ulTempAddr, 10+42+42);
        // AA  对应编程次数  + 1 AA 
        Data3ByteBCDAdd1(EPL_PROGRAM_SEASON_COUNT);
    }
    ClrFlashMode();
    return 1;
}
uchar ProgramEventResetDayChange(void)
{
    ulong ulTempAddr;
    ulTempAddr=SetTwoTableNextPoint(TYPE_PROGRAM_RESTDAY_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR == ulTempAddr)
    {
        return 0;   
    }
    else
    {
        SetTimeDataToPoint(&Wr_data[0]);
        memcpy(&Wr_data[6], (uchar * )&utlCommUserCode, 4);
        memcpy(&Wr_data[10], &RAM[RAM_CHARACTER_REST_DAYNO], 1);
        WriteDataDirect(&Wr_data[0], ulTempAddr, 11);
        // AA  对应编程次数  + 1 AA 
        Data3ByteBCDAdd1(EPL_PROGRAM_CHARACTER_REST_COUNT);
    }
    ClrFlashMode();
    return 1;
}


uchar ProgramEventHolidayChange(void)
{
    uchar HolidayNum;
    ulong ulTempAddr;
    
    ulTempAddr=SetTwoTableNextPoint(TYPE_PROGRAM_HOLIDAY_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR == ulTempAddr)
    {
        return 0;   
    }
    else
    {
        HolidayNum=ucPriceSwitchHolidayMax;
        if(HolidayNum>254)
        {
            HolidayNum=254;
        }
        SetTimeDataToPoint(&Wr_data[0]);
        memcpy(&Wr_data[6], (uchar * )&utlCommUserCode, 4);
        #if 0
        ReadDataDirect(EPL_PUBLIC_HOLIDAY_START, 512-10, &Wr_data[10]);
        WriteDataDirect(&Wr_data[0], ulTempAddr, 512);
        ReadDataDirect(EPL_PUBLIC_HOLIDAY_START+512-10, 512+2, &Wr_data[0]);
        WriteDataDirect(&Wr_data[0], ulTempAddr+512, 512+2);
        #else
        if(HolidayNum > 126)
        {
            ReadDataDirect(EPL_PUBLIC_HOLIDAY_START, 504, &Wr_data[10]);
            WriteDataDirect(&Wr_data[0], ulTempAddr, 514);
            ReadDataDirect(EPL_PUBLIC_HOLIDAY_START+514-10, (HolidayNum-126)*4, &Wr_data[0]);
            memset(&Wr_data[0+(HolidayNum-126)*4],0x00,512-(HolidayNum-126)*4);
            WriteDataDirect(&Wr_data[0], ulTempAddr+514, 512);
        }
        else
        {
            ReadDataDirect(EPL_PUBLIC_HOLIDAY_START,HolidayNum*4, &Wr_data[10]);
            memset(&Wr_data[10+HolidayNum*4],0x00,504-HolidayNum*4);
            WriteDataDirect(&Wr_data[0], ulTempAddr, 514);
            memset(&Wr_data[0],0x00,512);
            WriteDataDirect(&Wr_data[0], ulTempAddr+514, 512);
        }
        
        #endif
        // AA  对应编程次数  + 1 AA 
        Data3ByteBCDAdd1(EPL_PROGRAM_PUBLIC_HOLIDAY_COUNT);
    }
    ClrFlashMode();
    return 1;
}

uchar ProgramEventCharacterActiveChange(void)
{
    ulong ulTempAddr;
    ulTempAddr=SetTwoTableNextPoint(TYPE_PROGRAM_CHARACTER_ACTIVE_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR == ulTempAddr)
    {
        return 0;   
    }
    else
    {
        SetTimeDataToPoint(&Wr_data[0]);
        memcpy(&Wr_data[6], (uchar * )&utlCommUserCode, 4);
        memcpy(&Wr_data[10], &RAM[RAM_CHARACTER_ACTIVE], 1);
        WriteDataDirect(&Wr_data[0], ulTempAddr, 11);
        // AA  对应编程次数  + 1 AA 
        Data3ByteBCDAdd1(EPL_PROGRAM_ACTIVE_COM_COUNT);
    }
    ClrFlashMode();
    return 1;
}



uchar ProgramEventCharacterActive01Change(void)
{
    ulong ulTempAddr;
    ulTempAddr=SetTwoTableNextPoint(TYPE_PROGRAM_CHARACTER_REACTIVE01_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR == ulTempAddr)
    {
        return 0;   
    }
    else
    {
        SetTimeDataToPoint(&Wr_data[0]);
        memcpy(&Wr_data[6], (uchar * )&utlCommUserCode, 4);
        memcpy(&Wr_data[10], &RAM[RAM_CHARACTER_REACTIVE01], 1);
        WriteDataDirect(&Wr_data[0], ulTempAddr, 11);
        // AA  对应编程次数  + 1 AA 
        Data3ByteBCDAdd1(EPL_PROGRAM_REACTIVE1_COM_COUNT);
    }
    ClrFlashMode();
    return 1;
}


uchar ProgramEventCharacterActive02Change(void)
{
    ulong ulTempAddr;
    ulTempAddr=SetTwoTableNextPoint(TYPE_PROGRAM_CHARACTER_REACTIVE02_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR == ulTempAddr)
    {
        return 0;   
    }
    else
    {
        SetTimeDataToPoint(&Wr_data[0]);
        memcpy(&Wr_data[6], (uchar * )&utlCommUserCode, 4);
        memcpy(&Wr_data[10], &RAM[RAM_CHARACTER_REACTIVE02], 1);
        WriteDataDirect(&Wr_data[0], ulTempAddr, 11);
        // AA  对应编程次数  + 1 AA 
        Data3ByteBCDAdd1(EPL_PROGRAM_REACTIVE2_COM_COUNT);
    }
    ClrFlashMode();
    return 1;
}

uchar ProgramEventBalanceDayChange(void)
{
    ulong ulTempAddr;
    ulTempAddr=SetTwoTableNextPoint(TYPE_PROGRAM_BALANCE_DAY_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR == ulTempAddr)
    {
        return 0;   
    }
    else
    {
        SetTimeDataToPoint(&Wr_data[0]);
        memcpy(&Wr_data[6], (uchar * )&utlCommUserCode, 4);
        memcpy(&Wr_data[10], &RAM[RAM_BALANCE_DAY_01], 6);
        WriteDataDirect(&Wr_data[0], ulTempAddr, 16);
        // AA  对应编程次数  + 1 AA 
        Data3ByteBCDAdd1(EPL_PROGRAM_BALANCE_DAY_COUNT);
    }
    ClrFlashMode();
    return 1;
}



#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)


/*************************************************************
Function: 购电记录
Input:
Output:无
Application area:
Explain:
Modification register:
**************************************************************/
void PurchaseEnergyRecord(void)
{
    ulong ulTempAddr,ulTempData;
    ulTempAddr=SetTwoTableNextPoint(TYPE_BUY_MONEY_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR!=ulTempAddr)
    {
    //=====================
        SetTimeDataToPoint(&Wr_data[0]);
        
        ReadDataDirectEX((uchar*)&ulTempData,EPL_PREPAY_SUM_BUY_NUMBER,0,4);    //购电次数
        LongToData4BCD(ulTempData,&Wr_data[6]);
        
        ReadDataDirectEX((uchar*)&ulTempData,EPL_PREPAY_ENERGY_PRESENT_BUY,0,4);    //购电量
        LongToData4BCD(ulTempData,&Wr_data[10]);
        
        memcpy(&Wr_data[14],(uchar*)&remainEnergy_last.l,4);    //购电前电量
        
        if(JudgeRemainSign(0,&Wr_data[18])) 
        //A--A 购电后剩余电量（金额）A--A
        {
            memset(&Wr_data[18],0x00,4);
        }
        
        ReadDataDirectEX((uchar*)&ulTempData,EPL_PREPAY_ENERGY_SUM_BUY,0,4);    //累计购电量
        LongToData4BCD(ulTempData,&Wr_data[22]);
        WriteDataDirect(&Wr_data[0], ulTempAddr, 26);
    //======================
    }
    ClrFlashMode();
}
#endif
#if(CONFIG_METER_TYPE==CONFIG_METER_TYPE_SD39C)
uchar ProgramBroadCastTimeChange(uchar *ucOldTime,u16 uiTime)
{
    ulong ulTempAddr,ulData;
    ulTempAddr=SetTwoTableNextPoint(TYPE_BROADCASTTIME_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR == ulTempAddr)
    {   
        return 0;
    }
    else
    {
        SetTimeDataToPoint(&Wr_data[6]);
        memcpy(&Wr_data[0],&ucOldTime[0], 3);
        memcpy(&Wr_data[3], &ucOldTime[4], 3);
        memcpy(&Wr_data[12], (uchar *)&uiTime, 2);
        WriteDataDirect(&Wr_data[0], ulTempAddr, 14);
            //ClrFlashMode();
        // AA  对应编程次数  + 1 AA 
        Data3ByteBCDAdd1(EPL_TOTAL_BROADCASTTIME_COUNT);
        ulData=0;
        ReadDataDirect(EPL_TOTAL_BROADCASTTIME_TIME, 3, (uchar *)&ulData);
        if(ulData>0x800000)
        {
            ulData=0x7fffff&ulData;
            ulData=Bcd4DataToLong((uchar*)&ulData);
            ulData=(~ulData)+1;
        }
        else
        {
            ulData=Bcd4DataToLong((uchar*)&ulData);
        }
        if(uiTime>0x8000)
        {
            ulTempAddr=0x7fff&uiTime;
            ulTempAddr=Bcd2DataToInt((uchar*)&ulTempAddr);
            ulTempAddr=(~ulTempAddr)+1;
        }
        else
        {
            ulTempAddr=Bcd2DataToInt((uchar*)&uiTime);

        }
        ulData=ulData+ulTempAddr;
        if(ulData>0x80000000)
        {
            ulData=(~ulData)+1;
            LongToData4BCD(ulData, (uchar *)&ulData);
            ulData=0x800000|ulData;
        }
        else
        {
            LongToData4BCD(ulData, (uchar *)&ulData);
        }
        WriteDataDirect((uchar *)&ulData, EPL_TOTAL_BROADCASTTIME_TIME, 3);
    }
    ClrFlashMode();
    return 1;
}
#endif



void ProgramEventMode(void)
{
    //if((CON_NEEDCLR_PASSWORD == ulNeedClrPassWord)&&(0==ucSystemBusy))
    if((CON_NEEDCLR_PASSWORD == ulNeedClrPassWord))
    {
        if(CON_NEEDCLR_YES == ucNeedClrDemandAll)
        {
            DemandDataClrAllCurrent();
            ucNeedClrDemandAll=CON_NEEDCLR_NO;
            ulNeedClrPassWord=CON_NEEDCLR_PASSWORDCLR;
        }
        if(CON_NEEDCLR_YES == ucNeedClrPowerAll)
        {
            MeterCmdOpStateSet(1);
            if(PROGFUNCTION_METER_FACTORY == METER_IN_FACTORY)
            {
                if(ucNeedClrInFactory == CON_NEEDCLR_YES)
                {
                    EraseAllFlash();
                    ucNeedClrInFactory = CON_NEEDCLR_NO;
                }
                MeterAllDataClr(GAL_YES);
            }
            else
            {
                MeterAllDataClr(GAL_NO);
            }

            ucNeedClrPowerAll=CON_NEEDCLR_NO;
            ulNeedClrPassWord=CON_NEEDCLR_PASSWORDCLR;
            MeterCmdOpStateSet(0);
        }
        if(CON_NEEDCLR_YES==ucNeedClrEventAll)
        {
            EventClrFromCode(ulNeedClrEventCode);
            ucNeedClrEventAll=CON_NEEDCLR_NO;
            ulNeedClrPassWord=CON_NEEDCLR_PASSWORDCLR;
        }
    }
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
    //if((GAL_YES==PURCHASE_ENERGY_RECORD_FLAG)&&(0==ucSystemBusy))
    if((GAL_YES==PURCHASE_ENERGY_RECORD_FLAG))
    {
        PURCHASE_ENERGY_RECORD_FLAG=GAL_NO;
        PurchaseEnergyRecord();
    }
#endif
}
void MeterAllDataClr_pro(void)
{
        MeterCmdOpStateSet(1);
        if(PROGFUNCTION_METER_FACTORY == METER_IN_FACTORY)
        {
            if(ucNeedClrInFactory == CON_NEEDCLR_YES)
            {
                EraseAllFlash();
                ucNeedClrInFactory = CON_NEEDCLR_NO;
            }
            MeterAllDataClr(GAL_YES);
        }
        else
        {
            MeterAllDataClr(GAL_NO);
        }
	MeterCmdOpStateSet(0);
}
void CLR_Down_EventMode(void)
{
	unsigned long clr_event_flag = 0;

	clr_event_flag = g_p_update_param_shm->meter_clr_event_flag;
	switch(clr_event_flag)
	{
		case 0x55aa0011:    //电表总清
			shm_clean_pro();
			MeterAllDataClr_pro();
			g_p_update_param_shm->meter_clr_event_flag &=0xffff00ff;
			g_p_update_param_shm->meter_clr_event_flag |= ((clr_event_flag & 0xff)<<8);
		break;

		case 0x55aa0022:    //清当前需量数据
			DemandDataClrAllCurrent();
			g_p_update_param_shm->meter_clr_event_flag &=0xffff00ff;
			g_p_update_param_shm->meter_clr_event_flag |= ((clr_event_flag & 0xff)<<8);
		break;

		case 0x55aa0033:   //事件清零
			EventClrFromCode(0xffffffff);
			g_p_update_param_shm->meter_clr_event_flag &=0xffff00ff;
			g_p_update_param_shm->meter_clr_event_flag |= ((clr_event_flag & 0xff)<<8);
		break;
		
		case 0x55aa0044:  
			g_p_update_param_shm->meter_clr_event_flag &=0xffff00ff;
		break;

		case 0x55aa0055:
			g_p_update_param_shm->meter_clr_event_flag &=0xffff00ff;
		break;

		case 0x55aa0066:
			g_p_update_param_shm->meter_clr_event_flag &=0xffff00ff;
		break;
		
		default:
		break;
	}

}

long time_timerec_to_long(struct date_time_rec *mytime)
{
	time_t tmp_time;
	struct tm tmp_tm;
	struct tm *ptr_time;

	time(&tmp_time);
	ptr_time = localtime(&tmp_time);

	tmp_tm.tm_year = mytime->year - 1900;
	tmp_tm.tm_mon = mytime->month - 1;
	tmp_tm.tm_mday = mytime->day;
	tmp_tm.tm_hour = mytime->hour;
	tmp_tm.tm_min = mytime->minute;
	tmp_tm.tm_sec = mytime->second;
	tmp_tm.tm_isdst = ptr_time->tm_isdst;
	tmp_tm.tm_wday = 0;
	tmp_tm.tm_yday = 0;

	tmp_time = mktime(&tmp_tm);				//local

	return ((long)tmp_time);
}

void shm_clean_pro(void)
{
	 struct data_rt tmp_data_rt;
	 struct date_time_rec curr_time;
	 curr_time = get_current_time();
	 tmp_data_rt.rec_time = time_timerec_to_long(&curr_time);
	 tmp_data_rt.mp_no = g_p_update_param_shm->shm_ter_sample_mp_no;
	 memset(tmp_data_rt.data, 0x00, 8);

	//电量清零 
	tmp_data_rt.di = CON_DI_TYPE_MPDIRPOWTOTAL;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPDIRPOWPLUS;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPDIRPOWAPEX;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPDIRPOWFLAT;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPDIRPOWVALE;
	db_sd_drt_write_data_shm(&tmp_data_rt);


	tmp_data_rt.di = CON_DI_TYPE_MPDIRVARTOTAL;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPDIRVARPLUS;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPDIRVARAPEX;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPDIRVARFLAT;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPDIRVARVALE;
	db_sd_drt_write_data_shm(&tmp_data_rt);

	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRPOWTOTAL;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRPOWPLUS;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRPOWAPEX;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRPOWFLAT;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRPOWVALE;
	db_sd_drt_write_data_shm(&tmp_data_rt);

	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRVARTOTAL;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRVARPLUS;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRVARAPEX;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRVARFLAT;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRVARVALE;
	db_sd_drt_write_data_shm(&tmp_data_rt);

	tmp_data_rt.di = CON_DI_TYPE_MPVAR1;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPVAR1_FEE1;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPVAR1_FEE2;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPVAR1_FEE3;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPVAR1_FEE4;
	db_sd_drt_write_data_shm(&tmp_data_rt);

	tmp_data_rt.di = CON_DI_TYPE_MPVAR2;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPVAR2_FEE1;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPVAR2_FEE2;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPVAR2_FEE3;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPVAR2_FEE4;
	db_sd_drt_write_data_shm(&tmp_data_rt);

	tmp_data_rt.di = CON_DI_TYPE_MPVAR3;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPVAR3_FEE1;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPVAR3_FEE2;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPVAR3_FEE3;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPVAR3_FEE4;
	db_sd_drt_write_data_shm(&tmp_data_rt);

	tmp_data_rt.di = CON_DI_TYPE_MPVAR4;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPVAR4_FEE1;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPVAR4_FEE2;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPVAR4_FEE3;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPVAR4_FEE4;
	db_sd_drt_write_data_shm(&tmp_data_rt);

       //需量清零
	tmp_data_rt.di = CON_DI_TYPE_MPDIRPOWMAXDEMAND;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	tmp_data_rt.di = CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPDIRPOWMAXDEMAND_FEE1;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	tmp_data_rt.di = CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_FEE1;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPDIRPOWMAXDEMAND_FEE2;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	tmp_data_rt.di = CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_FEE2;
	db_sd_drt_write_data_shm(&tmp_data_rt);

	tmp_data_rt.di = CON_DI_TYPE_MPDIRPOWMAXDEMAND_FEE3;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	tmp_data_rt.di = CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_FEE3;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPDIRPOWMAXDEMAND_FEE4;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	tmp_data_rt.di = CON_DI_TYPE_MPDIRPOWMAXDEMANDTIME_FEE4;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPDIRVARMAXDEMAND;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	tmp_data_rt.di = CON_DI_TYPE_MPDIRVARMAXDEMANDTIME;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPDIRVARMAXDEMAND_FEE1;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	tmp_data_rt.di = CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_FEE1;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPDIRVARMAXDEMAND_FEE2;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	tmp_data_rt.di = CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_FEE2;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPDIRVARMAXDEMAND_FEE3;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	tmp_data_rt.di = CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_FEE3;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPDIRVARMAXDEMAND_FEE4;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	tmp_data_rt.di = CON_DI_TYPE_MPDIRVARMAXDEMANDTIME_FEE4;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRPOWMAXDEMAND;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_FEE1;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_FEE1;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_FEE2;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_FEE2;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_FEE3;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_FEE3;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRPOWMAXDEMAND_FEE4;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRPOWMAXDEMANDTIME_FEE4;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRVARMAXDEMAND;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRVARMAXDEMAND_FEE1;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_FEE1;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRVARMAXDEMAND_FEE2;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_FEE2;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRVARMAXDEMAND_FEE3;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_FEE3;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRVARMAXDEMAND_FEE4;
	db_sd_drt_write_data_shm(&tmp_data_rt);
	tmp_data_rt.di = CON_DI_TYPE_MPUNDIRVARMAXDEMANDTIME_FEE4;
	db_sd_drt_write_data_shm(&tmp_data_rt);
		
}




















