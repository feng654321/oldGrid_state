#define API_DRIVE_GLOBALS
#include "common.h"

uchar GetAde7758IntStatus(void)
{
//  if(1==GPIO_ReadInputDataBit(IN_ADEIC_IRQ1_PORT,IN_ADEIC_IRQ1_PIN))
//      return GAL_NO;
    return GAL_YES;
}
uchar GetUpKeyStatus(void)
{
    return GAL_NO;
}

uchar GetDownKeyStatus(void)
{
    return GAL_NO;
}

uchar GetInfoKeyStatus(void)
{
    return GAL_NO;  
}


uchar GetProgramKeyStatus(void)
{
    return GAL_NO;
}

uchar GetCoverOpenStatus(void)
{
    return GAL_NO;
}

uchar GetTerminalOpenStatus(void)
{
    return GAL_NO;    
}

uchar GetProgramOpenStatus(void)
{
    return GAL_NO;
}

#if 0
uchar GetSecondPulseStatus(void)
// AA  ����������ܽ�����û����   AA
{
//  return (GPIO_ReadInputDataBit(GPIOE,IPE_K_XFG));
    return 1;
}
uchar GetPowerSupplyStatus(void)
// AA  ϵͳ��Դ���������ź�   AA
{
    return (GPIO_ReadInputDataBit(IN_PECHK_PORT, IN_PECHK_PIN));
}
uchar GetActivePulseStatus(void)
{
    return (GPIO_ReadInputDataBit(IN_ACTIVE_PULSE_PORT,IN_ACTIVE_PULSE_PIN));
}

uchar GetReactivePulseStatus(void)
{
    return (GPIO_ReadInputDataBit(IN_REACTIVE_PULSE_PORT,IN_REACTIVE_PULSE_PIN));
}
#endif
uchar GetBatWakeupStatus(void)
// AA  ͣ�����Ƿѹ�ź�  AA
{
    return GAL_NO;
}
uchar GetRemotePinStatus(void)
// AA  ��������ܽ� AA
{
    return GAL_NO;
}

void OpenFlashPowerFromBat(void) //open flash power
{
}
void CloseFlashPowerFromBat(void)
{
}

void OpenIRPower(void)
{
}
void CloseIRPower(void)
{
}

void OpenPowerUpADE7758(void)
// AA  �����ϵ�ʱ���AD��Դ����  AA
// AA  ͣ���ʱ����Ҫ��ע   AA
{
}
// ����оƬ��λ���ƹܽ�
void ClosePowerUpADE7758(void)
{
}

// �򿪵�ع��������Դ
void OpenPowerDownADE7758(void)
// AA  ϵͳͣ��ʱ���AD��Դ����  AA
// AA  ������ͣ�缤���ʱ����   AA
// AA  �����ϵ��ʱ����Ҫ�ر�   AA
{
}
// �رյ�ع��������Դ
void ClosePowerDownADE7758(void)
{
}
        
void SetPulseCFKvarh(void)
{
}
void SetPulseCFKwh(void)
{
}

void ClrPulseCFKvarh(void)
{
}
void ClrPulseCFKwh(void)
{
}

void SetPulseOut1(void)
{
}
void SetPulseOut2(void)
{
}
void SetPulseOut3(void)
{
}
void SetPulseOut4(void)
{
}
void SetPulseOut5(void)
{
}
void ClrPulseOut1(void)
{
}
void ClrPulseOut2(void)
{
}
void ClrPulseOut3(void)
{
}
void ClrPulseOut4(void)
{
}
void ClrPulseOut5(void)
{
}

void SetSpeekAlarm(void)
{
}
void ClrSpeekAlarm(void)
{
}
void SetLedAlarmRed(void)
{
//  ALARMB_LED_ON;
}
void ClrLedAlarmGreen(void)
{
//  ALARMA_LED_OFF;
}
void SetLedAlarmGreen(void)
{
//  ALARMA_LED_ON;
}
void ClrLedAlarmRed(void)
{
//  ALARMB_LED_OFF;
}

void SetRelayAlarmPluse(void)
{
}

void ClrRelayAlarmPluse(void)
{
}

void SetRelayControlOn(void)
{
}

void ClrRelayControlOn(void)
{
}
void SetRelayControlOff(void)
{
}

void ClrRelayControlOff(void)
{
}

void ClrRelayAlarmLed(void)
{
}
void SetRelayAlarmLed(void)
{
}
void SetLedAlarm(void)
{
}
void ClrLedAlarm(void)
{
}

void SetHandModule(void)
{
}

void ClrHandModule(void)
{
}


void ClrPluseOutMode(void)
{
    //GPIO_ResetBits(OUT_PC_PORT,OUT_PC_PIN);   
}
void SetPluseOutMode(void)
{
    //GPIO_SetBits(OUT_PC_PORT,OUT_PC_PIN); 
}

void OpenLcdPower(void)
{
}
void CloseLcdPower(void)
{
}
#if(POWER_SW_DEBUG_ENABLE == GAL_YES)
    u16 DebugPowerOn=GAL_YES;
#endif
uchar IfPowerOn(void)
{
    int power_on_voltage_mv=POWER_ON_VOLTAGE_MV;

#if(POWER_SW_DEBUG_ENABLE == GAL_YES)
    if( (DebugPowerOn == GAL_YES) && (input_vot_check() == 1) )
        return 1;
    return 0;
#else
    if(input_vot_check() == 1)
        return 1;
    return 0;
#endif    
}

uchar IfPowerDown(void)
{
    int power_off_voltage_mv=POWER_OFF_VOLTAGE_MV;

#if(POWER_SW_DEBUG_ENABLE == GAL_YES)
    if( (DebugPowerOn == GAL_NO) || (input_vot_check() != 1) )
        return 1;
    return 0;
#else
    if(input_vot_check() != 1)
        return 1;
    return 0;
#endif    
}

#if 0
#if(CONFIG_METER_SW_DEBUG_MODE == GAL_YES)
#define WATCH_DOG_OPEN  GAL_NO    
#else
#if(CONFIG_METER_FACTORY_MODE==CONFIG_METER_FACTORY_MODE_DISABLE)
#define WATCH_DOG_OPEN  GAL_YES  
#else
#define WATCH_DOG_OPEN  GAL_NO    
#endif
#endif

void ClearWatchDog(void)
{
#if(WATCH_DOG_OPEN == GAL_YES)
#if 0
    static uchar ucWatchDogStatus;
    if(1==ucWatchDogStatus)
    {
        GPIO_SetBits(OUT_CLRWD_PORT,OUT_CLRWD_PIN);
        ucWatchDogStatus=0;
        SetSpeekAlarm();
    }
    else
    {
        GPIO_ResetBits(OUT_CLRWD_PORT,OUT_CLRWD_PIN);
        ucWatchDogStatus=1;
        ClrSpeekAlarm();
    }
#else
    IWDG_ReloadCounter();
#endif
#endif
}
    
void InitWatchDog(void)
{
#if(WATCH_DOG_OPEN == GAL_YES)
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    IWDG_SetPrescaler(IWDG_Prescaler_256);
    IWDG_SetReload(0xfff);
    IWDG_ReloadCounter();
    IWDG_Enable();
#endif
}
#endif

#if(CONFIG_METER_AUX_MODE==CONFIG_METER_AUX_MODE_ENABLE)
uchar GetAuxPowerStatus(void)
{
    return GAL_NO;  //
}
#endif

#if(CONFIG_METER_NO2COMM_MODE_PLC==CONFIG_METER_NO2COMM_MODE)
void SetPlcRunStatus(void)
{
}

void ResetPlcRunStatus(void)
{
}
#endif



ulong ulTempClrFlashAddr;
uchar ucTempClrFlashPassWord;
#define CON_CLR_FLASH_PASSWORD 0xA5

/*********************************************************************************
 * Function:       ����flash������ʼ��
 * Description:    
 * Input:          
 * Output:         
 * Others:         
 *******************************************************************************/ 
void ClrFlashInit(void)
{
    return;
}

/*********************************************************************************
 * Function:       ׼������flash
 * Description:    
 * Input:          
 * Output:         
 * Others:         
 *******************************************************************************/ 
void WaitClrFlash(ulong ulFlashAddr)
{
    int i;
    uchar *pData;
    
    ulFlashAddr &= (~(CON_RECORD_FLASH_1BLOCK_BYTE-1));      //4K
    MTRACE("WaitClrFlash addr = %08x\n", ulFlashAddr);
    pData = (uchar*)malloc(512);
    if(pData == NULL)
        return;
    memset(pData, 0, 512);
    
    for(i=0; i<(CON_RECORD_FLASH_1BLOCK_BYTE/512); i++)
    {
        MTRACE("WaitClrFlash addr = %08x\n", ulFlashAddr+512*i);
        WriteDataDirect(pData, ulFlashAddr+512*i, 512);
    }
    free(pData);
    return;
}
// --aa����FLASH��æ״̬�������æ������1��������У�����0   aa--
/*uchar  GetFlashStatus(void)
{
    return GAL_NO;
}*/

// �ȴ�flash����
//RemainTime:��λ10ms
void WaitFlashFree(uchar RemainTime)
{
    return;
}
//ȡ��FLASH�Ŀ���Ȩ�������æ���ȴ�
void GetFlash_control_wait(void)
{
    return;
    //if(ucProgramFlashWait)
    //    WaitFlashFree(ucProgramFlashWait);
}

/*********************************************************************************
 * Function:       ִ�в���flash����
 * Description:    
 * Input:          
 * Output:         
 * Others:         
 *******************************************************************************/ 
void ClrFlashMode(void)
{
    
}



