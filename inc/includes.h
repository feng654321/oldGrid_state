#ifndef INCLUDES_H
    #define INCLUDES_H
    
#ifdef  INCLUDES_GLOBALS
    #define INCLUDES_EXT
#else
    #define INCLUDES_EXT extern
#endif

#include "stm32f10x_lib.h"
#include "string.h"
#include "math.h"
#pragma pack(1)
#include "common.h"
#include "..\..\exdrv\inc\drv_config.h"
#include "..\..\exdrv\inc\drv_i2cBus.h"
#include "..\..\exdrv\inc\drv_at24c256a.h"
#include "..\..\exdrv\inc\drv_at24c256b.h"
#include "..\..\exdrv\inc\drv_at24c256c.h"
#include "..\..\exdrv\inc\drv_at24c256d.h"
#include "..\..\exdrv\inc\drv_fm24c64a.h"
#include "..\..\exdrv\inc\drv_fm24c64b.h"
//#include "..\..\exdrv\inc\drv_lcd.h"
#include "..\..\exdrv\inc\drv_ade7878.h"
#include "..\..\exdrv\inc\drv_calendar.h"
#include "..\..\exdrv\inc\drv_flash.h"
#include "..\..\exdrv\inc\drv_45DB321Da.h"
#include "..\..\exdrv\inc\drv_45DB321Db.h"
#include "..\..\exdrv\inc\drv_temp75.h"
#include "..\..\exdrv\inc\drv_interface.h"
#include "..\..\exdrv\inc\drv_remote.h"

//#include "..\..\exdrv\inc\drv_hc595.h"

//#include "..\..\cpudrv\inc\TimerDrv.h"


#include "..\..\api\inc\Api.h"
#include "..\..\prepay\inc\PrepayAPManger.h"

#include "..\..\cpudrv\inc\CpuDrv.h"

#include "gol_ram.h"
#include "gol_EPLOCK.h"

#include "gol_flash1.h"
#include "gol_CONSTFLASH.h"
#include "gol_BKP.h"


#include "gol_TwoTable.h"
#include "ap_profunction.h"

#include "api_drive.h"

#include "gol_data.h"
#include "ap_Datastorage.h"
#include "ap_pulsemode.h"

#include "ap_ade7758.h"
#include "ap_demand.h"
#include "ap_powercount.h"
#include "ap_time.h"

// #include "ap_commdata.h"
#include "ap_datacoef.h"
#include "ap_priceswitch.h"

#include "..\..\protocol\dlt645_07.h"

#include "Ap_AD.h"
#include "Ap_Alarm.h"
#include "Ap_Angle.h"
#include "Ap_aphour.h"

#include "ap_CommProgram.h"
#include "ap_CommWriteBackFunction.h"

#include "Ap_CoverOpen.h"
#include "ap_CutCurrent.h"
#include "ap_CutVoltage.h"
#include "ap_DownVoltage.h "
#include "Ap_Freeze.h"
#include "ap_Harmonic.h"
#include "ap_LossCurrent.h"
#include "ap_LossVoltage.h"
#include "ap_AllLossVoltage.h"
#include "ap_AuxPower.h"
#include "Ap_Module.h"
#include "Ap_Moniter.h"
#include "ap_Key.h"
#include "Ap_OrderCurrent.h"
#include "Ap_OrderVoltage.h"
#include "ap_OverTotalCos.h"
#include "ap_OverCurrent.h"
#include "ap_OverPower.h"
#include "ap_OverVoltage.h"
#include "ap_PowerOff.h"
#include "ap_PowerOn.h"
#include "Ap_PowerDownWakeUp.h"
#include "ap_PriceUse.h"
#include "Ap_Record.h"
#include "Ap_Relay.h"
#include "Ap_Restore.h"
#include "Ap_Remote.h"
#include "Ap_ReversePower.h"
#include "Ap_UnbalanceCurrent.h"
#include "Ap_UnbalanceVoltage.h"
#include "Ap_LossCopperIron.h"

#include "ap_PowerClac.h"


#include "CommExplain.h"
#include "CommLoadRec.h"
#include "CommExpWrite.h"
#include "FarControlCommExplain.h"

#include "CommDisplist.h"
#include "display_ext_input.h"
#include "Display_Ap.h"
#include "ap_datasave.h"

#ifdef TZG_DEBUG_MODE
#include "..\project\test_tzg.h"
#endif

#endif


