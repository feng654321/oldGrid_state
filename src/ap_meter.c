//============================================================================
//  File Name: ap_meter.c
//
//  Copyright PAX Hangzhou 2011.  All rights reserved.
//
//  Description:
//      
//
//  Modification History:
//      $Id:  Exp $
//      $Log: $
//      Revision 1.0 Create by Taozhiguo in 2011.04.28
//============================================================================
#ifndef __AP_METER_C__
#define __AP_METER_C__
#include "common.h"

//将表计的所有任务分散在每秒的时间片(比如100ms)
//此变量标示当前秒内的时间片索引
static uchar ucCurTimePieceIdx=0;
//此数组定义个时间片执行到的任务数
const uchar ucMainStepInTimePiece[MAX_TIME_PIECE_EACH_SECOND] = 
{
    MAIN_STEP_DISPLAY,
    MAIN_STEP_EVENT_SECTIME_ADD,
    MAIN_STEP_VAR1_UPDATE,
    MAIN_STEP_AHHOUR,
    MAIN_STEP_MONITOR,
    MAIN_STEP_IDLE6,
    MAIN_STEP_SAVE_DATA,
    MAIN_STEP_MAX,
    0,
};

//此变量用于标示当前特殊需要长时间处理的命令处理状态，如厂内总清
static ulong ulMeterCmdOpBusyValue=0;
//static uchar ucFlgCurSecond=0xFF;
static uchar ucMainStep=0, ucSlowStep=0, ucSlowStepSave=0;

void MeterSecondEventSecTimeAdd(void)
{
    CutCurrentSecTimeAdd();
    CutVoltageSecTimeAdd();
    LossVoltageSecTimeAdd();
    LossCurrentSecTimeAdd();
    DownVoltageSecTimeAdd();
    OverVoltageSecTimeAdd();
    OverCurrentSecTimeAdd();
    UnbalanceVoltageSecTimeAdd();
    UnbalanceCurrentSecTimeAdd();
    OverTotalCosSecTimeAdd();
    ReversePowerSecTimeAdd();
    OverPowerSecTimeAdd();
    OrderCurrentSecTimeAdd();
    OrderVoltageSecTimeAdd();
    AllLossVoltageSecTimeAdd();
    AuxPowerSecTimeAdd();
}

void MeterEventMinTimeAdd(void)
{
    CutCurrentMinTimeAdd();
    CutVoltageMinTimeAdd();
    LossVoltageMinTimeAdd();
    LossCurrentMinTimeAdd();
    DownVoltageMinTimeAdd();
    OverVoltageMinTimeAdd();
    OverCurrentMinTimeAdd();
    UnbalanceVoltageMinTimeAdd();
    UnbalanceCurrentMinTimeAdd();
    OverTotalCosMinTimeAdd();
    ReversePowerMinTimeAdd();
    OverPowerMinTimeAdd();
    OrderCurrentMinTimeAdd();
    OrderVoltageMinTimeAdd();
    AllLossVoltageMinTimeAdd();
    AuxPowerMinTimeAdd();
}

void MeterSecondEvent(void)
{
    uchar ret=0;
    ret = DLT_RET_SUCC;
#if 0
    ucMainStep++;
    ucSlowStep++;
#else
    /*static uchar ucFlgCurSecond=0xFF;
    static uchar ucMainStep=0, ucSlowStep=0, ucSlowStepSave=0;


    if(ucFlgCurSecond != RSOFT_RTC_SECOND)
    {
        ucFlgCurSecond = RSOFT_RTC_SECOND;
        ucMainStep = 0;
    }
    */

    if(ucMainStep < MAIN_STEP_MAX)
    {
        // main step operate
        ret = DLT_RET_SUCC;
        switch(ucMainStep)
        {
            //case MAIN_STEP_SECOND_TIMER:
            //    TimerManage1s();
            //    break;
            case MAIN_STEP_POWER_GET:
                ModeADE7758(0);
                break;
            case MAIN_STEP_PRICE_SWITCH:
                PriceSwitchMode();
                break;
            case MAIN_STEP_POWER_ADD:
                // TODO: 发现跨秒，需要优化判断，重复累加
                PowerClacMode();
                KwhAddMode();
                PowerClacMode();
                KwhAddMode();
                break;
            case MAIN_STEP_DEMAND:
                DemandMode();
                break;
            case MAIN_STEP_ALARM:
                AlarmMode();
//                PluseMode();  //ZD 集中器与专变无多功能脉冲输出
//                ModuleMode(); //ZD 集中器内表部分没有模块的概念
                TimerManage1s();
                break;
            case MAIN_STEP_KEY:
                KeyEventMode();
                break;
            case MAIN_STEP_DISPLAY:
#if (DISPLAY_PRINT_ENABLE == GAL_YES)   
                {
                    extern uchar ucDisplayPrintEnable;
                    if(ucDisplayPrintEnable == GAL_YES)
                    {
                        Display();
                        ReflashLCDDisplay(&displayMemory);
                        //PrintAllAdjCoef();
                    }
                }
#endif                
                break;
            case MAIN_STEP_PROGRAM_EVENT:
                ProgramEventMode();
                break;
            case MAIN_STEP_CLR_EVENT:
		        CLR_Down_EventMode();//各种清零事件
		   		break;
            case MAIN_STEP_TIME_ONE_SECOND:
                TimeOneSecondChange();
                break;
            case MAIN_STEP_EVENT_SECTIME_ADD:
                MeterSecondEventSecTimeAdd();
                MeterEventMinTimeAdd();
                break;
            case MAIN_STEP_VAR1_UPDATE:
                ModeADE7758(1);
                break;
            case MAIN_STEP_VAR2_UPDATE:
                ModeADE7758(2);
                break;
            //case MAIN_STEP_COVER_OPEN:
            //    CoverOpenMode();
            //    break;
            case MAIN_STEP_ALLLOSS_VOLTAGE:
                AllLossVoltageMode();
                break;
            case MAIN_STEP_POWER_DOWN:
                PowerdDownMode();
                break;
            case MAIN_STEP_AUX_POWER:
//                AuxPowerMode();     //ZD 辅助电源模式  集中器与专变内表无此项功能，
                break;
            case MAIN_STEP_AHHOUR:
                APHourMode();
                break;
            case MAIN_STEP_SAVE_DATA:
                SaveDataMode();
                break;
#if(CONFIG_METER_HARMONIC_ENABLE == GAL_YES)    
            case MAIN_STEP_HARMONIC:
                HarmonicMode();
                break;
#endif                
            case MAIN_STEP_ANGEL:
                AngleMode();
                break;
            //case MAIN_STEP_AD:
            //    ADMode();
            //    break;
            case MAIN_STEP_MONITOR:
                savemeterdata_to_dbf(0);	
                MoniterMode();
                break;
            case MAIN_STEP_SLOW_START:
                if(RSOFT_RTC_SECOND == 0)
                {
                    //过分时间还是必须得复位副线任务号，让重要结算等任务能够执行；
                    ucSlowStep= 0;
                }
                ucSlowStepSave = ucSlowStep;
                ret = DLT_RET_NO_HAPPEN;
                break;
            case MAIN_STEP_WAIT_SLOW:
                if(ucSlowStepSave == (ucSlowStep+0x80))
                {
                    //慢速任务已经轮流执行一遍，可以放心的结束了
                    ret = DLT_RET_SUCC;
                    //只是为了保险期间
                    //ucMainStep = MAIN_STEP_MAX + 2;
                }
                else
                {
                    //UNFINISHED,当然就是等在这里不前进了
                    ret = DLT_RET_UNFINISHED;
                }
                break;
            case MAIN_STEP_COEF_CHECK:
                CoefCheckMode();
                break;
            default:
                ret = DLT_RET_NO_HAPPEN;
                break;
        }
        if((ret == DLT_RET_SUCC) || (ret == DLT_RET_NO_HAPPEN))
        {
            ucMainStep++;
        }
        if((ucMainStep >= MAIN_STEP_SLOW_START)   //在主线的此操作之后才成运行副线任务
            && (ret != DLT_RET_SUCC))           //在主线任务已执行过的情况下不执行副线任务，保证一次只有一个任务执行
        {
            // slow step operate
            //MTRACE("ucSlowStep = %d, %d, %d\n", ucMainStep, ucSlowStep, ucSlowStepSave);
            ret = DLT_RET_SUCC;
            switch(ucSlowStep)
            {
                case SLOW_STEP_RESTORE:
                    ret = RestoreMode();
                    break;
                case SLOW_STEP_FREEZE:
                    ret = FreezeMode();
                    break;
                case SLOW_STEP_RECORD:
                    ret = RecordMode();
                    break;
                case SLOW_STEP_CUT_CURRENT:
                    ret = CutCurrentMode();
                    break;
                case SLOW_STEP_CUT_VOLTAGE:
                    ret = CutVoltageMode();
                    break;
                case SLOW_STEP_DOWN_VOLTAGE:
                    ret = DownVoltageMode();
                    break;
                case SLOW_STEP_LOSS_VOLTAGE:
                    ret = LossVoltageMode();
                    break;
                case SLOW_STEP_LOSS_CURRENT:
                    ret = LossCurrentMode();
                    break;
                case SLOW_STEP_ORDER_CURRENT:
                    ret = OrderCurrentMode();
                    break;
                case SLOW_STEP_ORDER_VOLTAGE:
                    ret = OrderVoltageMode();
                    break;
                case SLOW_STEP_OVER_CURRENT:
                    ret = OverCurrentMode();
                    break;
                case SLOW_STEP_OVER_POWER:
                    ret = OverPowerMode();
                    break;
                case SLOW_STEP_OVER_VOLTAGE:
                    ret = OverVoltageMode();
                    break;
                case SLOW_STEP_REVERSE_POWER:
                    ret = ReversePowerMode();
                    break;
                case SLOW_STEP_UNBALANCE_CURRENT:
                    ret = UnbalanceCurrentMode();
                    break;
                case SLOW_STEP_UNBALANCE_VOLTAGE:
                    ret = UnbalanceVoltageMode();
                    break;
                case SLOW_STEP_OVER_TOTALCOS:
                    ret = OverTotalCosMode();
                    break;
                default:
                    ucSlowStep = 0;
                    break;
            }
            if((ret != DLT_RET_UNFINISHED))
            {
                ucSlowStep++;
                ucSlowStepSave |= 0x80;
                if(ucSlowStep >= SLOW_STEP_MAX)
                    ucSlowStep = 0;
            }
        }
    }
#endif    
}
/*==================================================================
//函数名：  MeterTimeUpdateSimply
//作者：    陶治国
//日期：    
//功能：    此函数专门用来简单的时间更新，用于初始化，时间更改等情况
//输入参数：
//输出参数：
            通过全局变量的方式输出表系统时间如:
            RSOFT_RTC_SECOND。。。
            
//返回值：  
            返回当前时间片索引值，为了提高局部效率，同时赋值给全局变量ucCurTimePieceIdx
//=================================================================*/
void MeterTimeUpdateSimply(void)
{
	time_t tmp_time;
	struct tm *ptr_time;
    ulong ulTempSecTime;
	long  ltemptime;

    time(&tmp_time);
	ptr_time = localtime(&tmp_time); /*取得当地时间*/  
		
    {
        RSOFT_RTC_SECOND    = ByteToBCD(ptr_time->tm_sec);
        RSOFT_RTC_MINUTE    = ByteToBCD(ptr_time->tm_min);
        RSOFT_RTC_HOUR      = ByteToBCD(ptr_time->tm_hour);
        RSOFT_RTC_WEEK      = ByteToBCD(ptr_time->tm_wday);
        RSOFT_RTC_DAY       = ByteToBCD(ptr_time->tm_mday);
        RSOFT_RTC_MONTH     = ByteToBCD(ptr_time->tm_mon+1);
        RSOFT_RTC_YEAR      = ByteToBCD(ptr_time->tm_year-100);
        //if(last_min != RSOFT_RTC_MINUTE)
        {
            ulNowMinTime = mmHHDDMMYYToLong(&(RSOFT_RTC_MINUTE));
            //last_min = RSOFT_RTC_MINUTE;
        }
        //以下代码用来判断系统时间是否被修改，为了节省系统资源，放在这里可能有秒级延时
		//ulTempSecTime = CalendarToSec((STR_CALENDAR*)(&RSOFT_RTC_SECOND);
		ulTempSecTime = ulNowMinTime*60 + ptr_time->tm_sec;
    	ltemptime = ulTempSecTime - ulNowSecTime;
    	if((ltemptime > 5) || (ltemptime < 0))
    	{
    	}
        ulNowSecTime = ulTempSecTime;
    }
}

/*==================================================================
//函数名：  MeterTimeGet
//作者：    陶治国
//日期：    
//功能：    此函数算出当前表的时间以及当前秒内时间片
//输入参数：
            isTimePieceAdd: 1:时间片增加  0:时间片不变
//输出参数：
            通过全局变量的方式输出表系统时间如:
            RSOFT_RTC_SECOND。。。
            
//返回值：  
            返回当前时间片索引值，为了提高局部效率，同时赋值给全局变量ucCurTimePieceIdx
//=================================================================*/
uchar MeterTimeGet(uchar isTimePieceAdd)
{
    static uchar last_sec=0xff;
    //static uchar last_min=0xff;
    //static uchar ucCurTimePieceIdx=0;
	time_t tmp_time;
	struct tm *ptr_time;
    ulong ulTempSecTime;
	long  ltemptime;

    if(isTimePieceAdd)
    {
        ucCurTimePieceIdx++;
    }
    time(&tmp_time);
	ptr_time = localtime(&tmp_time); /*取得当地时间*/ 
	
    if(last_sec != ptr_time->tm_sec)
    {
        ulRunSecTime++;
		
        last_sec = ptr_time->tm_sec;
        RSOFT_RTC_SECOND    = ByteToBCD(ptr_time->tm_sec);
        RSOFT_RTC_MINUTE    = ByteToBCD(ptr_time->tm_min);
        RSOFT_RTC_HOUR      = ByteToBCD(ptr_time->tm_hour);
        RSOFT_RTC_WEEK      = ByteToBCD(ptr_time->tm_wday);
        RSOFT_RTC_DAY       = ByteToBCD(ptr_time->tm_mday);
        RSOFT_RTC_MONTH     = ByteToBCD(ptr_time->tm_mon+1);
        RSOFT_RTC_YEAR      = ByteToBCD(ptr_time->tm_year-100);
        ucCurTimePieceIdx = 0;         //rewind when a new second
        //if(last_min != RSOFT_RTC_MINUTE)
        {
            ulNowMinTime = mmHHDDMMYYToLong(&(RSOFT_RTC_MINUTE));
            //last_min = RSOFT_RTC_MINUTE;
        }
        //以下代码用来判断系统时间是否被修改，为了节省系统资源，放在这里可能有秒级延时
		//ulTempSecTime = CalendarToSec((STR_CALENDAR*)(&RSOFT_RTC_SECOND);
		ulTempSecTime = ulNowMinTime*60 + ptr_time->tm_sec;
    	ltemptime = ulTempSecTime - ulNowSecTime;
    	if((ltemptime > 5) || (ltemptime < 0))
    	{
            if(isTimePieceAdd)
            {
    		    CWBFTimeChange();
                LOGTRACE("time changed = %02x-%02x-%02x %02x:%02x:%02x\n",RSOFT_RTC_YEAR,RSOFT_RTC_MONTH,
                        RSOFT_RTC_DAY,RSOFT_RTC_HOUR,RSOFT_RTC_MINUTE, RSOFT_RTC_SECOND);
                LOGTRACE("ulNowSecTime = %d, ulTempSecTime = %d\n", ulNowSecTime, ulTempSecTime);
            }
    	}
        ulNowSecTime = ulTempSecTime;
    }
    if(ucCurTimePieceIdx >= MAX_TIME_PIECE_EACH_SECOND)
    {
        ucCurTimePieceIdx = 0;
    }
    return ucCurTimePieceIdx;
}
            
/*==================================================================
//函数名：  MeterTaskInit
//作者：    陶治国
//日期：    
//功能：    表进程开启初始化
//输入参数：无
//输出参数：无
//返回值：  无
//=================================================================*/
void MeterTaskInit(void)
{
    //主要是为了确保RAM数组的自然对齐
    RAM = (uchar*)(&(ulRAM[0]));
	//文件初始化
#if(CONFIG_METER_FACTORY_MODE_ENABLE == CONFIG_METER_FACTORY_MODE)
	MeterFileInit(FILE_EPL, FILE_LEN_EPL);
    MeterFileInit(FILE_BAK, FILE_LEN_BAK);
	MeterFileInit(FILE_FLASH, FILE_LEN_FLASH);
#endif
    eMeterState = METER_SYS_POWEROFF;
    ucCurTimePieceIdx = 0;
    ulRunSecTime=0;
    uiTaskStartCounterAdd_1;
    VtPlatformInit();
}
/*==================================================================
//函数名：  MeterTaskExit
//作者：    陶治国
//日期：    
//功能：    表进程退出处理
//输入参数：无
//输出参数：无
//返回值：  无
//=================================================================*/
void MeterTaskExit(void)
{
    LOGTRACE("MeterTaskExit\n");
    MeterPowerOff();
}
/*==================================================================
//函数名：  MeterPowerOnInit
//作者：    陶治国
//日期：    
//功能：    表上电初始化
//输入参数：无
//输出参数：无
//返回值：  无
//=================================================================*/

void MeterPowerOnInit(uchar port_no)
{
    ulong ulTempTest = 0;

	ERRTRACE("->...Init\n");
    uiPowerOnCounterAdd_1;
    ucSystemResetOk=0;
    AlarmClrAll();
    MemoryStatusInit();
    CoefPowerUpResume(1);
    ProgFunctionLoad();
    KwhResume();
    DemandResume();
    MeterTimeUpdateSimply();
    
    //memset((uchar *)&ucTimeLastSave[0],0xff,sizeof(ucTimeLastSave));
    //GetLastSaveTime((STR_CALENDAR* ) &ucTimeLastSave[0]);
    EventRecordPowerOn();
    ClrCurrentADE7758Data(GAL_NO);
    
    PowerOnDataInit();
    //Start10msInt();
    InitCommunicate(port_no);
#if(DISPLAY_PRINT_ENABLE == GAL_YES)
    InitDisplayControl(1);
    uchar ucDisplayId[5] = {0x00, 0x00, 0x01, 0x00, 0x00};
    SetCommDisplayDI (&ucDisplayId[0]);
#endif    
	ERRTRACE("->...INITADMODE\n");
    if(InitADMode(GAL_NO, GAL_YES) == ADE_INIT_POWERDOWN)
    {
        ErrPrint("InitADMode ADE_INIT_POWERDOWN\n");
    }

#if(CONFIG_METER_HARMONIC_ENABLE == GAL_YES)    
    HarmonicInit();
#endif
    /*if(0==TestSecondMinuteHourDayMonthYear(&ucTimeLastSave[0], &ucTimeLastSave[3]))
    {
        memcpy(&ucTimeLastSave[0], &RSOFT_RTC_SECOND, 7);
    }*/
                
    if(1==ReadDataDirect(EPL_CURRENT_BAT_USETIME, 4, &Wr_data[0]))
    {
        //memcpy(&Wr_data[10], &ucTimeLastSave[1], 2);
        //memcpy(&Wr_data[12], &ucTimeLastSave[3], 3);
        memcpy(&Wr_data[20], &RSOFT_RTC_MINUTE, 2);
        memcpy(&Wr_data[22], &RSOFT_RTC_DAY, 3);
        ulTempTest=mmHHDDMMYYToLong(&Wr_data[20]);//now time
        //ulTempTest=ulTempTest-mmHHDDMMYYToLong(&Wr_data[10]); // last time
        ulTempTest=ulTempTest-ulGetLastSaveTime/60; // last time
        MTRACE("now time = %d, last time=%d\n", mmHHDDMMYYToLong(&Wr_data[20]), ulGetLastSaveTime/60);
#if(CONFIG_METER_AREA_MODE_SHANGHAI==CONFIG_METER_AREA_MODE)
        //如果不在同一天，密码错误次数清零
        LongTommHHDDMMYY(ulGetLastSaveTime/60, &ucTimeLastSave[0]);
        MTRACE("%02X-%02X-%02X %02X:%02X\n", ucTimeLastSave[4], ucTimeLastSave[3], ucTimeLastSave[2], \
            ucTimeLastSave[1], ucTimeLastSave[0]);
        if((Wr_data[22] != ucTimeLastSave[0]) 
            || (Wr_data[23] != ucTimeLastSave[1]) 
            || (Wr_data[24] != ucTimeLastSave[2]))
        {
            ClearAllPasswordErrCount();
        }
#endif
        if(ulTempTest<0x00ffffff)
        {
            LongToData4BCD(ulTempTest+Bcd4DataToLong(&Wr_data[0]), &Wr_data[4]);
            WriteDataDirect(&Wr_data[4],EPL_CURRENT_BAT_USETIME, 4 );
        }
        else
        {
            ulTempTest=0;
        }
    }
    //SetCurrentTime();
                   
    if(GetTheProgramKeyState()==COMM_TURE)  //(ucProgramTime > 0)
    {
        ReadDataDirect(EPL_PROGRAM_RECORD_STATUS, 1, &ucProgramPoint);
        if(1!=ucProgramPoint)
        {
            ucProgramPoint=0;
        }
    }
    else
    {
        ucProgramPoint=0;
    }
    
#if(CONFIG_METER_FACTORY_MODE_DISABLE==CONFIG_METER_FACTORY_MODE)
    if(ulTempTest>=1440)
#endif
    {
        memset(&Wr_data[0], 0x00, CON_WR_DATA_LEN_MAX);
        WriteDataDirect(&Wr_data[0],RAM_PASSWORD_ERR_COUNT_START,33);
        WriteDataDirect(&Wr_data[0],EPL_PASSWORD_ERR_COUNT_START,33);
#if(CONFIG_METER_FACTORY_MODE_ENABLE==CONFIG_METER_FACTORY_MODE)
        WriteDataDirect(&Wr_data[0],EPL_PASSWORD_START,10*4);
        memset(&Wr_data[0],1,3);
        WriteDataDirect(&Wr_data[0],EPL_PASSWORD_4+1,4);
        memset(&Wr_data[0],0,4);

#endif
    }
#if(CONFIG_METER_FACTORY_MODE_DISABLE==CONFIG_METER_FACTORY_MODE)
    else
    {
        uint uiTimesCount;
        uchar ucTempStatus;
        ReadDataDirect(EPL_PASSWORD_ERR_COUNT_START, 33, &RAM[RAM_PASSWORD_ERR_COUNT_START]);
        for(ucTempStatus=0;ucTempStatus<10;ucTempStatus++)
        {
            memcpy((uchar *)&uiTimesCount, &RAM[RAM_PASSWORD_LOCK_TIME_START+ucTempStatus*2], 2);
            if((uiTimesCount<=ulTempTest) || (uiTimesCount>1440))
            {
                uiTimesCount=0;
            }
            else
            {
                uiTimesCount=uiTimesCount-ulTempTest;
            }
            memcpy( &RAM[RAM_PASSWORD_LOCK_TIME_START+ucTempStatus*2],(uchar *)&uiTimesCount, 2);
        }
        WriteDataDirect(&RAM[RAM_PASSWORD_LOCK_TIME_START],EPL_PASSWORD_LOCK_TIME_START,20);
    }
#endif
    
    ClearWatchDog();
    {
        if(GAL_YES==AllLossVoltageStatuscheck())
        {
            AllLossVoltagePoweronChange(ulTempTest);
        }
        else
        {
            PowerDownWhenPowerOnRecord(&ucTimeLastSave[0]);
        }
        AuxPowerPowerOn(&ucTimeLastSave[0],ulTempTest);
        uiAllLossVoltageSecond = 0;
    }
    
    ModeAde7878PowerOn();
}
/*==================================================================
//函数名：  MeterPowerOff
//作者：    陶治国
//日期：    
//功能：    表掉电处理
//输入参数：无
//输出参数：无
//返回值：  无
//=================================================================*/

void MeterPowerOff(void)
{
//    MTRACE("MeterPowerOffInit\n");
	ERRTRACE("->...MeterPowerOffInit\n");
    //close 7878
    //close display
    uiPowerOffCounterAdd_1;
    
#if(CONFIG_METER_HARMONIC_ENABLE == GAL_YES)    
    HarmonicIdle();
#endif
    //clear All Alarm status
    AlarmClrAll();
    CloseAD7878();
    //  表计正常运行3秒，才能进行重要数据掉电保存
    if(ucSystemResetOk >= 3)
    {
        PowerOffSaveAllData();
		PowerDownRecordStart();
    }
    SetCurrentTime();
    VtPlatformSave();
}

/*==================================================================
//函数名：  Meter100msTask
//作者：    陶治国
//日期：    
//功能：    表100ms时间片处理
//输入参数：无
//输出参数：无
//返回值：  无
//=================================================================*/
void Meter100msTask(void)
{
    //MTRACE("Meter100msTask !\n");
    //eMeterState = METER_SYS_POWERON;
    //while(1)
    {
        switch(eMeterState)
        {
            case METER_SYS_POWEROFF:
                ClearWatchDog();
                if(IfPowerOn())
                {
                    eMeterState = METER_SYS_POWERON_INIT;
					ERRTRACE("->...METER_SYS_POWERON_INIT\n");
                    MeterPowerOnInit(get_cur_uart_port_no());
                    eMeterState = METER_SYS_POWERON;
                    break;
                }
		  else 
		  	savemeterdata_to_dbf(1);
                //judgeFrameStructure(0);
                break;
                
            case METER_SYS_POWERON:
                {
                    ClearWatchDog();
                    if((GAL_YES==spi_status)&&(GAL_YES==r7758mode_ok)&&(ucSystemResetOk<=CON_SYSTEM_REST_OK))
                    {
                        //MTRACE("ucSystemResetOk = %d\n", ucSystemResetOk);
                        r7758mode_ok=GAL_NO;
                        ucSystemResetOk++;
                    }
                    if(IfPowerDown())
                    {
                        eMeterState = METER_SYS_POWEROFF_SAVE;
						ERRTRACE("->...METER_SYS_POWERON_OFF\n");
                        MeterPowerOff();
                        IdleCommunicate();
                        eMeterState = METER_SYS_POWEROFF;
                        break;
                    }
                    MeterTimeGet(1);
                    if(ucCurTimePieceIdx == 0)
                    {
                        ucMainStep = 0;
                    }
                    //MTRACE("->%d, %d, %d\n", ucMainStep, ucSlowStep, ucMainStepInTimePiece[ucCurTimePieceIdx]);
                    judgeFrameStructure(0);
                    while(ucMainStep < ucMainStepInTimePiece[ucCurTimePieceIdx])
                    {
                        //MTRACE("->%d, %d, %d\n", ucMainStep, ucSlowStep, ucMainStepInTimePiece[ucCurTimePieceIdx]);
                        /*MeterTimeGet(0);
                        if(ucCurTimePieceIdx == 0)
                        {
                            ucMainStep = 0;
                        }*/
                        ClearWatchDog();
                        MeterSecondEvent();
                    }
                    //MTRACE("<-%d, %d, %d\n", ucMainStep, ucSlowStep, ucMainStepInTimePiece[ucCurTimePieceIdx]);
                }
                break;
                
            /*case METER_SYS_POWERON_INIT:
                MTRACE("METER_SYS_POWERON_INIT\n");
                //PowerOnDataInit();
                eMeterState = METER_SYS_POWERON;
                break;
                
            case METER_SYS_POWEROFF_SAVE:
                MTRACE("METER_SYS_POWEROFF_SAVE\n");
                //PowerOff();
                eMeterState = METER_SYS_POWEROFF;
                break;
            */    
             case METER_SYS_IDLE:
             default:
                eMeterState = METER_SYS_POWEROFF;
                break;
        }
    }
}
void MeterCmdOpStateSet(uchar isBusy)
{
    if(isBusy)
        ulMeterCmdOpBusyValue = ulRunSecTime;
    else
        ulMeterCmdOpBusyValue = 0;
}
uchar isMeterCmdOpStateBusy(void)
{
    if(ulMeterCmdOpBusyValue)
    {
        if( (ulRunSecTime-ulMeterCmdOpBusyValue) < 255 )
        {
            //为了防止状态死锁(忘记释放)，假设忙的状态最多持续255秒
            return 1;
        }
    }
    return 0;
}

#endif

