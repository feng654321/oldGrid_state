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

//����Ƶ����������ɢ��ÿ���ʱ��Ƭ(����100ms)
//�˱�����ʾ��ǰ���ڵ�ʱ��Ƭ����
static uchar ucCurTimePieceIdx=0;
//�����鶨���ʱ��Ƭִ�е���������
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

//�˱������ڱ�ʾ��ǰ������Ҫ��ʱ�䴦��������״̬���糧������
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
                // TODO: ���ֿ��룬��Ҫ�Ż��жϣ��ظ��ۼ�
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
//                PluseMode();  //ZD ��������ר���޶๦���������
//                ModuleMode(); //ZD �������ڱ���û��ģ��ĸ���
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
		        CLR_Down_EventMode();//���������¼�
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
//                AuxPowerMode();     //ZD ������Դģʽ  ��������ר���ڱ��޴���ܣ�
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
                    //����ʱ�仹�Ǳ���ø�λ��������ţ�����Ҫ����������ܹ�ִ�У�
                    ucSlowStep= 0;
                }
                ucSlowStepSave = ucSlowStep;
                ret = DLT_RET_NO_HAPPEN;
                break;
            case MAIN_STEP_WAIT_SLOW:
                if(ucSlowStepSave == (ucSlowStep+0x80))
                {
                    //���������Ѿ�����ִ��һ�飬���Է��ĵĽ�����
                    ret = DLT_RET_SUCC;
                    //ֻ��Ϊ�˱����ڼ�
                    //ucMainStep = MAIN_STEP_MAX + 2;
                }
                else
                {
                    //UNFINISHED,��Ȼ���ǵ������ﲻǰ����
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
        if((ucMainStep >= MAIN_STEP_SLOW_START)   //�����ߵĴ˲���֮��ų����и�������
            && (ret != DLT_RET_SUCC))           //������������ִ�й�������²�ִ�и������񣬱�֤һ��ֻ��һ������ִ��
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
//��������  MeterTimeUpdateSimply
//���ߣ�    ���ι�
//���ڣ�    
//���ܣ�    �˺���ר�������򵥵�ʱ����£����ڳ�ʼ����ʱ����ĵ����
//���������
//���������
            ͨ��ȫ�ֱ����ķ�ʽ�����ϵͳʱ����:
            RSOFT_RTC_SECOND������
            
//����ֵ��  
            ���ص�ǰʱ��Ƭ����ֵ��Ϊ����߾ֲ�Ч�ʣ�ͬʱ��ֵ��ȫ�ֱ���ucCurTimePieceIdx
//=================================================================*/
void MeterTimeUpdateSimply(void)
{
	time_t tmp_time;
	struct tm *ptr_time;
    ulong ulTempSecTime;
	long  ltemptime;

    time(&tmp_time);
	ptr_time = localtime(&tmp_time); /*ȡ�õ���ʱ��*/  
		
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
        //���´��������ж�ϵͳʱ���Ƿ��޸ģ�Ϊ�˽�ʡϵͳ��Դ����������������뼶��ʱ
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
//��������  MeterTimeGet
//���ߣ�    ���ι�
//���ڣ�    
//���ܣ�    �˺��������ǰ���ʱ���Լ���ǰ����ʱ��Ƭ
//���������
            isTimePieceAdd: 1:ʱ��Ƭ����  0:ʱ��Ƭ����
//���������
            ͨ��ȫ�ֱ����ķ�ʽ�����ϵͳʱ����:
            RSOFT_RTC_SECOND������
            
//����ֵ��  
            ���ص�ǰʱ��Ƭ����ֵ��Ϊ����߾ֲ�Ч�ʣ�ͬʱ��ֵ��ȫ�ֱ���ucCurTimePieceIdx
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
	ptr_time = localtime(&tmp_time); /*ȡ�õ���ʱ��*/ 
	
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
        //���´��������ж�ϵͳʱ���Ƿ��޸ģ�Ϊ�˽�ʡϵͳ��Դ����������������뼶��ʱ
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
//��������  MeterTaskInit
//���ߣ�    ���ι�
//���ڣ�    
//���ܣ�    ����̿�����ʼ��
//�����������
//�����������
//����ֵ��  ��
//=================================================================*/
void MeterTaskInit(void)
{
    //��Ҫ��Ϊ��ȷ��RAM�������Ȼ����
    RAM = (uchar*)(&(ulRAM[0]));
	//�ļ���ʼ��
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
//��������  MeterTaskExit
//���ߣ�    ���ι�
//���ڣ�    
//���ܣ�    ������˳�����
//�����������
//�����������
//����ֵ��  ��
//=================================================================*/
void MeterTaskExit(void)
{
    LOGTRACE("MeterTaskExit\n");
    MeterPowerOff();
}
/*==================================================================
//��������  MeterPowerOnInit
//���ߣ�    ���ι�
//���ڣ�    
//���ܣ�    ���ϵ��ʼ��
//�����������
//�����������
//����ֵ��  ��
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
        //�������ͬһ�죬��������������
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
//��������  MeterPowerOff
//���ߣ�    ���ι�
//���ڣ�    
//���ܣ�    ����紦��
//�����������
//�����������
//����ֵ��  ��
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
    //  �����������3�룬���ܽ�����Ҫ���ݵ��籣��
    if(ucSystemResetOk >= 3)
    {
        PowerOffSaveAllData();
		PowerDownRecordStart();
    }
    SetCurrentTime();
    VtPlatformSave();
}

/*==================================================================
//��������  Meter100msTask
//���ߣ�    ���ι�
//���ڣ�    
//���ܣ�    ��100msʱ��Ƭ����
//�����������
//�����������
//����ֵ��  ��
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
            //Ϊ�˷�ֹ״̬����(�����ͷ�)������æ��״̬������255��
            return 1;
        }
    }
    return 0;
}

#endif

