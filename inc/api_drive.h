
#ifndef API_DRIVE_H
    #define API_DRIVE_H
    
#ifdef  API_DRIVE_GLOBALS
    #define API_DRIVE_EXT
#else
    #define API_DRIVE_EXT extern
#endif  


API_DRIVE_EXT uchar GetAde7758IntStatus(void);

API_DRIVE_EXT uchar GetDownKeyStatus(void);

API_DRIVE_EXT uchar GetUpKeyStatus(void);

API_DRIVE_EXT uchar GetInfoKeyStatus(void);

API_DRIVE_EXT uchar GetProgramKeyStatus(void);

API_DRIVE_EXT uchar GetCoverOpenStatus(void);

API_DRIVE_EXT uchar GetTerminalOpenStatus(void);

API_DRIVE_EXT uchar GetProgramOpenStatus(void);

API_DRIVE_EXT uchar GetSecondPulseStatus(void);

// API_DRIVE_EXT uchar GetPowerSupplyStatus(void);
#define GetPowerSupplyStatus() (GPIO_ReadInputDataBit(IN_PECHK_PORT,IN_PECHK_PIN))

API_DRIVE_EXT uchar GetBatWakeupStatus(void);

API_DRIVE_EXT uchar GetRemotePinStatus(void);
#if 0
API_DRIVE_EXT uchar GetActivePulseStatus(void);
API_DRIVE_EXT uchar GetReactivePulseStatus(void);
#endif


API_DRIVE_EXT void OpenPowerUpADE7758(void);

API_DRIVE_EXT void ClosePowerUpADE7758(void);

API_DRIVE_EXT void OpenPowerDownADE7758(void);

API_DRIVE_EXT void ClosePowerDownADE7758(void);

API_DRIVE_EXT void OpenFlashPowerFromBat(void);

API_DRIVE_EXT void CloseFlashPowerFromBat(void);

API_DRIVE_EXT void OpenIRPower(void);

API_DRIVE_EXT void CloseIRPower(void);

API_DRIVE_EXT void SetPulseOut1(void);

API_DRIVE_EXT void SetPulseOut2(void);

API_DRIVE_EXT void SetPulseOut3(void);

API_DRIVE_EXT void SetPulseOut4(void);

API_DRIVE_EXT void SetPulseOut5(void);

API_DRIVE_EXT void ClrPulseOut1(void);

API_DRIVE_EXT void ClrPulseOut2(void);

API_DRIVE_EXT void ClrPulseOut3(void);

API_DRIVE_EXT void ClrPulseOut4(void);

API_DRIVE_EXT void ClrPulseOut5(void);

API_DRIVE_EXT void SetSpeekAlarm(void);

API_DRIVE_EXT void ClrSpeekAlarm(void);


API_DRIVE_EXT void SetPulseCFKwh(void);

API_DRIVE_EXT void SetPulseCFKvarh(void);

API_DRIVE_EXT void ClrPulseCFKwh(void);

API_DRIVE_EXT void ClrPulseCFKvarh(void);

API_DRIVE_EXT void SetLedAlarmRed(void);

API_DRIVE_EXT void ClrLedAlarmGreen(void);

API_DRIVE_EXT void SetLedAlarmGreen(void);

API_DRIVE_EXT void ClrLedAlarmRed(void);

API_DRIVE_EXT uchar IfPowerOn(void);

API_DRIVE_EXT uchar IfPowerDown(void);

API_DRIVE_EXT void InitWatchDog(void);
API_DRIVE_EXT void ClearWatchDog(void);

API_DRIVE_EXT void SetRelayControlOn(void);

API_DRIVE_EXT void ClrRelayControlOn(void);

API_DRIVE_EXT void SetRelayControlOff(void);

API_DRIVE_EXT void ClrRelayControlOff(void);

API_DRIVE_EXT void SetLedAlarm(void);

API_DRIVE_EXT void ClrLedAlarm(void);


API_DRIVE_EXT void SetHandModule(void);


API_DRIVE_EXT void ClrHandModule(void);



API_DRIVE_EXT void ClrRelayAlarmLed(void);


API_DRIVE_EXT void SetRelayAlarmLed(void);

API_DRIVE_EXT void SetRelayAlarmPluse(void);

API_DRIVE_EXT void ClrRelayAlarmPluse(void);


API_DRIVE_EXT void ClrPluseOutMode(void);

API_DRIVE_EXT void SetPluseOutMode(void);



API_DRIVE_EXT void OpenLcdPower(void);

API_DRIVE_EXT void CloseLcdPower(void);

API_DRIVE_EXT uchar GetAuxPowerStatus(void);

#if(CONFIG_METER_NO2COMM_MODE_PLC==CONFIG_METER_NO2COMM_MODE)

API_DRIVE_EXT void SetPlcRunStatus(void);

API_DRIVE_EXT void ResetPlcRunStatus(void);
#if(CONFIG_METER_TYPE_SD39C==CONFIG_METER_TYPE)
API_DRIVE_EXT void SetPlcMacAddrEnable(uchar ucEnable);
#endif
#endif

API_DRIVE_EXT void WaitClrFlash(ulong ulFlashAddr);

API_DRIVE_EXT uchar  GetFlashStatus(void);
API_DRIVE_EXT void GetFlash_control_wait(void);

API_DRIVE_EXT void ClrFlashMode(void);

API_DRIVE_EXT void ClrFlashInit(void);

#define isFlashBusy         (GAL_NO)    //(GAL_YES == GetFlashStatus())
#define isFlashFree         (GAL_YES)   //(GAL_NO  == GetFlashStatus())
#define OPERATE_FLASH_WAIT  (0)
#endif








