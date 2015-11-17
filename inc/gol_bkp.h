#ifndef __GOL_BKP_H__
#define __GOL_BKP_H__

//ST BKP 模拟
#define BKP_VIRTUAL_FEATURE GAL_YES
#if(GAL_YES == BKP_VIRTUAL_FEATURE)
#undef BKP_BASE
#undef BKP_DR1 
#undef BKP_DR2 
#undef BKP_DR3 
#undef BKP_DR4 
#undef BKP_DR5 
#undef BKP_DR6 
#undef BKP_DR7 
#undef BKP_DR8 
#undef BKP_DR9 
#undef BKP_DR10
#undef BKP_DR11
#undef BKP_DR12
#undef BKP_DR13
#undef BKP_DR14
#undef BKP_DR15
#undef BKP_DR16
#undef BKP_DR17
#undef BKP_DR18
#undef BKP_DR19
#undef BKP_DR20
#undef BKP_DR21
#undef BKP_DR22
#undef BKP_DR23
#undef BKP_DR24
#undef BKP_DR25
#undef BKP_DR26
#undef BKP_DR27
#undef BKP_DR28
#undef BKP_DR29
#undef BKP_DR30
#undef BKP_DR31
#undef BKP_DR32
#undef BKP_DR33
#undef BKP_DR34
#undef BKP_DR35
#undef BKP_DR36
#undef BKP_DR37
#undef BKP_DR38
#undef BKP_DR39
#undef BKP_DR40
#undef BKP_DR41
#undef BKP_DR42
#undef IS_BKP_DR

#define BKP_VIRTUAL_REG_NUM 42
#ifndef __AP_DATASTORGE_C__
    extern u16 BKP_VIRTUAL_REG[];
#else
    u16 BKP_VIRTUAL_REG[BKP_VIRTUAL_REG_NUM+2];  
#endif
#define BKP_VIRTUAL_DATA_LEN    (sizeof(u16) * (BKP_VIRTUAL_REG_NUM+2))
#define IS_BKP_DR(DR)   ( (DR >= (ulong)(&(BKP_VIRTUAL_REG[1]))) && (DR <= (ulong)(&(BKP_VIRTUAL_REG[BKP_VIRTUAL_REG_NUM]))) )
#define BKP_BASE    (u16*)(&(BKP_VIRTUAL_REG[1]))
#define BKP_DR1     00
#define BKP_DR2     01
#define BKP_DR3     02
#define BKP_DR4     03
#define BKP_DR5     04
#define BKP_DR6     05
#define BKP_DR7     06
#define BKP_DR8     07
#define BKP_DR9     08
#define BKP_DR10    09
#define BKP_DR11    10
#define BKP_DR12    11
#define BKP_DR13    12
#define BKP_DR14    13
#define BKP_DR15    14
#define BKP_DR16    15
#define BKP_DR17    16
#define BKP_DR18    17
#define BKP_DR19    18
#define BKP_DR20    19
#define BKP_DR21    20
#define BKP_DR22    21
#define BKP_DR23    22
#define BKP_DR24    23
#define BKP_DR25    24
#define BKP_DR26    25
#define BKP_DR27    26
#define BKP_DR28    27
#define BKP_DR29    28
#define BKP_DR30    29
#define BKP_DR31    30
#define BKP_DR32    31
#define BKP_DR33    32
#define BKP_DR34    33
#define BKP_DR35    34
#define BKP_DR36    35
#define BKP_DR37    36
#define BKP_DR38    37
#define BKP_DR39    38
#define BKP_DR40    39
#define BKP_DR41    40
#define BKP_DR42    41
#define BKP_REG_SKIP     (1)
#else
#define BKP_REG_SKIP     (4)
#endif
//--AA   上次停电时间  AA--------------
#define uiLastSaveTimeLow  ((*(vu16 *) (BKP_BASE + BKP_DR1) ))
#define uiLastSaveTimeHigh  ((*(vu16 *) (BKP_BASE + BKP_DR2) ))
#define ulGetLastSaveTime   (((ulong)(uiLastSaveTimeHigh))*0x10000+uiLastSaveTimeLow)
#define SetLastSaveTime(ulTimer)        uiLastSaveTimeHigh=ulTimer>>16;uiLastSaveTimeLow=(ulTimer&0xffff)


//--AA  上次负荷记录记录时间 AA--------------
#define uiRecordStatusLastTimeLow    ((*(vu16 *) (BKP_BASE + BKP_DR3) ))
#define uiRecordStatusLastTimeHigh   ((*(vu16 *) (BKP_BASE + BKP_DR4) ))
#define ulGetRecordStatusLastTime   (((ulong)(uiRecordStatusLastTimeHigh))*0x10000+uiRecordStatusLastTimeLow)
#define SetRecordStatusLastTime(ulTimer2)       uiRecordStatusLastTimeHigh=ulTimer2>>16;uiRecordStatusLastTimeLow=(ulTimer2&0xffff)

//--AA  负荷记录起始指针 AA--------------
#define uiRecordStatusPointStartLow     ((*(vu16 *) (BKP_BASE + BKP_DR5) ))
#define uiRecordStatusPointStartHigh    ((*(vu16 *) (BKP_BASE + BKP_DR6) ))
#define ulGetRecordStatusPointStart (((ulong)(uiRecordStatusPointStartHigh))*0x10000+uiRecordStatusPointStartLow)
#define SetRecordStatusPointStart(ulTimer2)     uiRecordStatusPointStartHigh=ulTimer2>>16;uiRecordStatusPointStartLow=(ulTimer2&0xffff)



//--AA  负荷记录结束指针 AA--------------
#define uiRecordStatusPointEndLow   ((*(vu16 *) (BKP_BASE + BKP_DR7) ))
#define uiRecordStatusPointEndHigh  ((*(vu16 *) (BKP_BASE + BKP_DR8) ))
#define ulGetRecordStatusPointEnd   (((ulong)(uiRecordStatusPointEndHigh))*0x10000+uiRecordStatusPointEndLow)
#define SetRecordStatusPointEnd(ulTimer2)       uiRecordStatusPointEndHigh=ulTimer2>>16;uiRecordStatusPointEndLow=(ulTimer2&0xffff)



//--AA  bit0  表盖开启状态  AA--------------
#define ucTimerCoverOpenCount       ((*(vu16 *) (BKP_BASE + BKP_DR9) ))
#define ucTimerCoverOpenCountADD    ucTimerCoverOpenCount=((ucTimerCoverOpenCount&0xff00)+((ucTimerCoverOpenCount+1)&0xff))
#define ucTimerCoverOpenCountClr    ucTimerCoverOpenCount=(ucTimerCoverOpenCount&0xff00)
#define GetTimerCoverOpenCount      (ucTimerCoverOpenCount&0xff)

//--AA  bit1  端钮盖开启状态  AA--------------
#define ucTimerTerminalOpenCount        ((*(vu16 *) (BKP_BASE + BKP_DR9) ))
#define ucTimerTerminalOpenCountADD ucTimerTerminalOpenCount=(ucTimerTerminalOpenCount+0x100)
#define ucTimerTerminalOpenCountClr     ucTimerTerminalOpenCount=(ucTimerTerminalOpenCount&0x00ff)

//--AA  bit2  全失压开启状态  AA--------------
#define ucTimerAllLostVoltageCount      ((*(vu16 *) (BKP_BASE + BKP_DR10) ))
#define ucTimerAllLostVoltageCountAdd   ucTimerAllLostVoltageCount=((ucTimerAllLostVoltageCount&0xff00)+((ucTimerAllLostVoltageCount+1)&0xff))
#define ucTimerAllLostVoltageCountClr       ucTimerAllLostVoltageCount=(ucTimerAllLostVoltageCount&0xff00)

//--AA  bit3  编程记录记录状态  AA--------------
#define ucProgramTimerAddr              ((*(vu16 *) (BKP_BASE + BKP_DR10) ))
#define ucProgramTimerSet(ucProgramTimeData)            ucProgramTimerAddr=(ucProgramTimerAddr&0x00ff)+ucProgramTimeData*0x100          
#define ucGetProgramTime()              (ucProgramTimerAddr>>8)
#define ucProgramTimerClr               ucProgramTimerAddr=(ucProgramTimerAddr&0x00ff)
#define ucProgramTimerSub               ucProgramTimerAddr=(ucProgramTimerAddr-0x100)


#define  uiStatusPowerDownRun           ((*(vu16 *) (BKP_BASE + BKP_DR11) ))



//--AA  bit0  表盖开启状态  AA--------------
#define fCoverOpenStatusSet             uiStatusPowerDownRun=(uiStatusPowerDownRun|0x01)            
#define fCoverOpenStatusClr             uiStatusPowerDownRun=(uiStatusPowerDownRun&(~0x01))
#define fGetCoverOpenStatus             (uiStatusPowerDownRun&0x01)

//--AA  bit1  端钮盖开启状态  AA--------------
#define fTerminalOpenStatusSet          uiStatusPowerDownRun=(uiStatusPowerDownRun|0x02)            
#define fTerminalOpenStatusClr          uiStatusPowerDownRun=(uiStatusPowerDownRun&(~0x02))
#define fGetTerminalOpenStatus          ((uiStatusPowerDownRun&0x02)>>1)

//--AA  bit2  全失压开启状态  AA--------------
#define fAllLostVoltageStatusSet            uiStatusPowerDownRun=(uiStatusPowerDownRun|0x04)            
#define fAllLostVoltageStatusClr            uiStatusPowerDownRun=(uiStatusPowerDownRun&(~0x04))
#define fGetAllLostVoltageStatus            ((uiStatusPowerDownRun&0x04)>>2)

//--AA  bit3  掉电开启状态  AA--------------

#define fPowerDownStatusSet             uiStatusPowerDownRun=(uiStatusPowerDownRun|0x08)            
#define fPowerDownStatusClr             uiStatusPowerDownRun=(uiStatusPowerDownRun&(~0x08))
#define fGetPowerDownStatus             ((uiStatusPowerDownRun&0x08)>>3)

//--AA  bit4  辅助电源掉电开启状态  AA--------------

#define fAuxPowerDownStatusSet              uiStatusPowerDownRun=(uiStatusPowerDownRun|0x10)            
#define fAuxPowerDownStatusClr              uiStatusPowerDownRun=(uiStatusPowerDownRun&(~0x10))
#define fGetAuxPowerDownStatus              ((uiStatusPowerDownRun&0x10)>>4)


//--AA  bit5  掉电时刻上一秒开表盖检测状态  AA--------------

#define fCoverOpenLastSecondStatusSet(ucTemp)               uiStatusPowerDownRun=(ucTemp == 1?(uiStatusPowerDownRun|0x20):(uiStatusPowerDownRun&(~0x20)))           
//#define fCoverOpenLastSecondStatusClr             uiStatusPowerDownRun=(uiStatusPowerDownRun&(~0x20))
#define fGetCoverOpenLastSecondStatus               ((uiStatusPowerDownRun&0x20)>>5)

//--AA  bit6   掉电时刻上一秒开端钮盖检测状态  AA--------------

#define fTerminalOpenLastSecondStatusSet(ucTemp)                uiStatusPowerDownRun=(ucTemp == 1?(uiStatusPowerDownRun|0x40):(uiStatusPowerDownRun&(~0x40)))           
//#define fTerminalOpenLastSecondStatusClr              uiStatusPowerDownRun=(uiStatusPowerDownRun&(~0x40))
#define fGetTerminalOpenLastSecondStatus                ((uiStatusPowerDownRun&0x40)>>6)


//--AA  bit8  编程记录记录状态  AA--------------
#define fProgramRecordStatusSet         uiStatusPowerDownRun=(uiStatusPowerDownRun|0x0100)          
#define fProgramRecordStatusClr         uiStatusPowerDownRun=(uiStatusPowerDownRun&(~0x0100))
#define fGetProgramRecordStatus         ((uiStatusPowerDownRun&0x0100)>>8)

// bit 9  擦除flash记录状态
#define fEraseFlashStatusSet                uiStatusPowerDownRun=(uiStatusPowerDownRun|0x0200)
#define fEraseFlashStatusClr                uiStatusPowerDownRun=(uiStatusPowerDownRun&(~0x0200))
#define fGetEraseFlashStatus                ((uiStatusPowerDownRun&0x0200)>>9)


//--AA  bit10/11/12 掉电开表盖延时状态  AA--------------
#define fCoverOpenTimeDelayAdd          uiStatusPowerDownRun=(uiStatusPowerDownRun+0x0400)
#define fCoverOpenTimeDelaySet(ucTime)          uiStatusPowerDownRun=((uiStatusPowerDownRun&0xE3FF)+ucTime*0x0400)
#define fCoverOpenTimeDelayClr          uiStatusPowerDownRun=(uiStatusPowerDownRun&0xE3FF)
#define fCoverOpenTimeDelayGet          ((uiStatusPowerDownRun&0x1C00)>>10)

//--AA  bit13/14/15  掉电开端钮盖延时状态  AA--------------
#define fTerminalOpenTimeDelayAdd           uiStatusPowerDownRun=(uiStatusPowerDownRun+0x2000)
#define fTerminalOpenTimeDelaySet(ucTime)           uiStatusPowerDownRun=((uiStatusPowerDownRun&0x1FFF)+ucTime*0x2000)
#define fTerminalOpenTimeDelayClr           uiStatusPowerDownRun=(uiStatusPowerDownRun&0x1FFF)
#define fTerminalOpenTimeDelayGet           ((uiStatusPowerDownRun&0xE000)>>13)


#define uiWakeupData                    ((*(vu16 *) (BKP_BASE + BKP_DR12) ))

#define fWakeUpEnableSet                uiWakeupData=(uiWakeupData|0x100)
#define fWakeUpEnableClr                uiWakeupData=(uiWakeupData&(~0x100))
#define fGetWakeUpEnable                ((uiWakeupData&0x100)>>8)

// #define ucIRWakeUpOneDayCountSet( AA1111)    uiWakeupData=((0xff00&uiWakeupData)+AA1111)
#define ucIRWakeUpOneDayCountSet( AA1111)   uiWakeupData=((0xff00&uiWakeupData)+AA1111)
#define ucIRWakeUpOneDayCountSub        uiWakeupData=((0xff&uiWakeupData)-1)+(0xff00&uiWakeupData)
#define ucIRWakeUpOneDayCountClr            uiWakeupData=(0xff00&uiWakeupData)
#define GetIRWakeUpOneDayCount          (uiWakeupData&0xff)

#define uiIRWakeUpTimer                 ((*(vu16 *) (BKP_BASE + BKP_DR13) ))
// 掉电后用于全失压检测的计时
#define uiAllLossVoltageSecond          ((*(vu16 *) (BKP_BASE + BKP_DR14) ))
#if (CONFIG_METER_AREA_MODE_SOUTHGRID==CONFIG_METER_AREA_MODE)
// 掉电后第15分钟的全失压检测结果
#define fGetAllLossVoltage15Min         (uiAllLossVoltageSecond&0x8000)
#define fSetAllLossVoltage15Min         uiAllLossVoltageSecond = (uiAllLossVoltageSecond|0x8000)
#define fClrAllLossVoltage15Min         uiAllLossVoltageSecond = (uiAllLossVoltageSecond&0x7FFF)
#endif

//基准 频偏，每次上电设置一下，单位ppm
#define siClockOffSetFreqAddr               ((*(vu16 *) (BKP_BASE + BKP_DR19) ))
#define siClockOffSetFreqSet(AB123)     siClockOffSetFreqAddr=  AB123
#define GetsiClockOffSetFreq                (siClockOffSetFreqAddr)

// 时钟补偿时间点
#define uiClockAdjustCountLow           ((*(vu16 *) (BKP_BASE + BKP_DR20) ))
#define uiClockAdjustCountHigh          ((*(vu16 *) (BKP_BASE + BKP_DR21) ))
#define ClockAdjustCountSet(AA122)      uiClockAdjustCountLow= (AA122&0xffff);uiClockAdjustCountHigh=(AA122>>16)
#define ClockAdjustCountGet             ((((ulong)uiClockAdjustCountHigh)<<16)+uiClockAdjustCountLow)

#define uiPowerDownTimePassedAddr       (BKP_BASE + BKP_DR17)
#define uiPowerDownTimePassed           ((*(vu16 *) uiPowerDownTimePassedAddr ))
//#define uiPowerDownTimePassedSet(x)     uiPowerDownTimePassed=(x)
//#define uiPowerDownTimePassedClr        uiPowerDownTimePassed=0
// 预分频值
#define uiRtcPrlTempAddr                    ((*(vu16 *) (BKP_BASE + BKP_DR22) ))
#define uiRtcPrlTempSet(AA123)          uiRtcPrlTempAddr=(AA123)
#define GetuiRtcPrlTemp                 (uiRtcPrlTempAddr)
// RTC时钟校准值
#define uiRtcCalTempAddr                    ((*(vu16 *) (BKP_BASE + BKP_DR23) ))
#define uiRtcCalTempSet(AA124)          uiRtcCalTempAddr=(AA124)
#define GetuiRtcCalTemp                 (uiRtcCalTempAddr)
// 当前温度下的频偏，ppm值
#define siRTCCalPPMSaveAddr             ((*(vu16 *) (BKP_BASE + BKP_DR24 )))
#define siRtcCalPPMDataSet(AA125)       siRTCCalPPMSaveAddr=(AA125)
#define GetsiRtcCalPPMData              (siRTCCalPPMSaveAddr)

//--AA  掉电时刻保存的擦除flash的地址 AA--------------
#define uiEraseFlashAddrLow     ((*(vu16 *) (BKP_BASE + BKP_DR25) ))
#define uiEraseFlashAddrHigh    ((*(vu16 *) (BKP_BASE + BKP_DR26) ))
#define ulGetEraseFlashAddr (((ulong)(uiEraseFlashAddrHigh))*0x10000+uiEraseFlashAddrLow)
#define SetEraseFlashAddr(ulAddr1)      uiEraseFlashAddrHigh=ulAddr1>>16;uiEraseFlashAddrLow=(ulAddr1&0xffff)

// 以下代码统计各种复位次数
#if 1
#define uiTaskStartCounterAddr             ((*(vu16 *) (BKP_BASE + BKP_DR27) ))
#define uiTaskStartCounterAdd_1                uiTaskStartCounterAddr = uiTaskStartCounterAddr+1
#define uiTaskStartCounterClr              uiTaskStartCounterAddr = 0

#define uiPowerOnCounterAddr             ((*(vu16 *) (BKP_BASE + BKP_DR28) ))
#define uiPowerOnCounterAdd_1                uiPowerOnCounterAddr = uiPowerOnCounterAddr+1
#define uiPowerOnCounterClr              uiPowerOnCounterAddr = 0

#define uiPowerOffCounterAddr             ((*(vu16 *) (BKP_BASE + BKP_DR29) ))
#define uiPowerOffCounterAdd_1                uiPowerOffCounterAddr = uiPowerOffCounterAddr+1
#define uiPowerOffCounterClr              uiPowerOffCounterAddr = 0

#else
#define uiPINRSTCounterAddr             ((*(vu16 *) (BKP_BASE + BKP_DR27) ))
#define uiPINRSTCounterAdd_1                uiPINRSTCounterAddr = uiPINRSTCounterAddr+1
#define uiPINRSTCounterClr              uiPINRSTCounterAddr = 0

#define uiPORRSTCounterAddr             ((*(vu16 *) (BKP_BASE + BKP_DR28) ))
#define uiPORRSTCounterAdd_1                uiPORRSTCounterAddr = uiPORRSTCounterAddr+1
#define uiPORRSTCounterClr              uiPORRSTCounterAddr = 0

#define uiSFTRSTCounterAddr             ((*(vu16 *) (BKP_BASE + BKP_DR29) ))
#define uiSFTRSTCounterAdd_1                uiSFTRSTCounterAddr = uiSFTRSTCounterAddr+1
#define uiSFTRSTCounterClr              uiSFTRSTCounterAddr = 0


#define uiIWDGRSTCounterAddr                ((*(vu16 *) (BKP_BASE + BKP_DR30) ))
#define uiIWDGRSTCounterAdd_1               uiIWDGRSTCounterAddr = uiIWDGRSTCounterAddr+1
#define uiIWDGRSTCounterClr             uiIWDGRSTCounterAddr = 0


#define uiWWDGRSTCounterAddr                ((*(vu16 *) (BKP_BASE + BKP_DR31) ))
#define uiWWDGRSTCounterAdd_1               uiWWDGRSTCounterAddr = uiWWDGRSTCounterAddr+1
#define uiWWDGRSTCounterClr             uiWWDGRSTCounterAddr = 0


#define uiLPWRRSTCounterAddr                ((*(vu16 *) (BKP_BASE + BKP_DR32) ))
#define uiLPWRRSTCounterAdd_1               uiLPWRRSTCounterAddr = uiLPWRRSTCounterAddr+1
#define uiLPWRRSTCounterClr             uiLPWRRSTCounterAddr = 0
#endif

#if(MEM_ERR_RECORD_ENABLE == GAL_YES)
// E2出错统计
#define uiE2promErrTimes                    ((*(vu16 *) (BKP_BASE + BKP_DR34) ))
#define GetE2promErrTimes                   (uiE2promErrTimes)
#define SetE2promErrTimes(AAA)              uiE2promErrTimes=(AAA)  

// flash出错统计
#define uiFlashErrTimes                     ((*(vu16 *) (BKP_BASE + BKP_DR35) ))
#define GetFlashErrTimes                    (uiFlashErrTimes)
#define SetFlashErrTimes(AAA)               GetFlashErrTimes=(AAA)  

#endif
#define BKP_RTC_INIT_FLAG           (((ulong)GAL_BKP)*256*256*256 + 0x36)   // 2 byte   剩余电量的小数   BKP_DR36

#define BKP_REMAIN_ENERGY_DECIMAL   (((ulong)GAL_BKP)*256*256*256 + 0x40)   // 5 byte   剩余电量的小数   BKP_DR40 ~ BKP_DR42

#if 0
#define uiKWH_High          ((*(vu16 *) (BKP_BASE + BKP_DR33) ))
#define uiKWH_Mid           ((*(vu16 *) (BKP_BASE + BKP_DR34) ))
#define uiKWH_Low           ((*(vu16 *) (BKP_BASE + BKP_DR35) ))

#define uiKWH_ALLh           ((*(vu16 *) (BKP_BASE + BKP_DR36) ))
#define uiKWH_ALLl           ((*(vu16 *) (BKP_BASE + BKP_DR37) ))

#define uiKWH_Curh           ((*(vu16 *) (BKP_BASE + BKP_DR38) ))
#define uiKWH_Curl           ((*(vu16 *) (BKP_BASE + BKP_DR39) ))

#define uiRdErrTime          ((*(vu16 *) (BKP_BASE + BKP_DR40) ))
#define uiWrErrTime          ((*(vu16 *) (BKP_BASE + BKP_DR41) ))
#define uiCkErrTime          ((*(vu16 *) (BKP_BASE + BKP_DR42) ))
#define uiRWTime             ((*(vu16 *) (BKP_BASE + BKP_DR32) ))
#endif
#endif

