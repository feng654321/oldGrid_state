#ifndef __COMMON_H__
#define __COMMON_H__

#include "config.h"

//common file
//#include "app_timer.h"
#include "app_ipcs.h"
//#pragma pack(1)
//__attribute__((__aligned__(1))) 
#include "datatype.h"
#pragma pack(1)
__attribute__((packed))
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <signal.h>
//#include <sys/param.h>
//#include <sys/types.h>
//#include <sys/stat.h>
#include <sys/file.h>   //for flock()
//#include <string.h>
#include "time.h"
#include "ap_meter.h"
#include "meter_main.h"
#include "string.h"
#include "math.h"
#include "gol_define.h"
#include "dlt645_07.h"
#include "gol_struct.h"
#include "gol_function.h"
#include "gol_version.h"
#include "gol_ram.h"
#include "gol_bkp.h"
#include "gol_eplock.h"
#include "gol_bak.h"
#include "gol_flash1.h"
#include "ap_profunction.h"
#include "gol_data.h"
#include "gol_version.h"
#include "gol_constflash.h"
#include "vt_platform.h"
#include "timerapi.h"
#include "ap_datastorage.h"
#include "gol_twotable.h"
#include "ap_time.h"
#include "ap_commdata.h"
#include "rtc.h"
#include "communicatedrv.h"
#include "communicateapi.h"
#include "api_drive.h"
#include "display_api.h"
#include "display_ap.h"


//special block file
#include "ap_ade7758.h"
#include "ap_powerclac.h"
#include "ap_powercount.h"
#include "ap_pulsemode.h"

#include "ap_demand.h"

#include "ap_datacoef.h"
#include "ap_priceswitch.h"

//#include "ap_ad.h"
#include "ap_alarm.h"
#include "ap_angle.h"
#include "ap_aphour.h"

#include "ap_commprogram.h"
#include "ap_commwritebackfunction.h"

//#include "ap_coveropen.h"
#include "ap_cutcurrent.h"
#include "ap_cutvoltage.h"
#include "ap_downvoltage.h"
#include "ap_freeze.h"
#include "ap_harmonic.h"
#include "ap_losscurrent.h"
#include "ap_lossvoltage.h"
#include "ap_alllossvoltage.h"
#include "ap_auxpower.h"
#include "ap_module.h"
#include "ap_moniter.h"
#include "ap_key.h"
#include "ap_ordercurrent.h"
#include "ap_ordervoltage.h"
#include "ap_overtotalcos.h"
#include "ap_overcurrent.h"
#include "ap_overpower.h"
#include "ap_overvoltage.h"
#include "ap_poweroff.h"
#include "ap_poweron.h"
#include "ap_powerdownwakeup.h"
#include "ap_priceuse.h"
#include "ap_record.h"
#include "ap_relay.h"
#include "ap_restore.h"
#include "ap_reversepower.h"
#include "ap_unbalancecurrent.h"
#include "ap_unbalancevoltage.h"
#include "ap_losscopperiron.h"

#include "commexplain.h"
#include "commloadrec.h"
#include "commexpwrite.h"
//#include "farcontrolcommexplain.h"

#include "commdisplist.h"
#include "display_ext_input.h"
#include "display_ap.h"
#include "ap_datasave.h"

#include "general.h"
#include "savemeter_to_dbf.h"


#ifdef TZG_DEBUG_MODE
#include "test_tzg.h"
#endif

#endif

