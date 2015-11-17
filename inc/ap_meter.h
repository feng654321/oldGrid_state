//============================================================================
//  File Name: ap_meter.h
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
#ifndef __AP_METER_H__
#define __AP_METER_H__

#undef COMMON_EXT
#ifdef __AP_METER_C__
#define COMMON_EXT
#else
#define COMMON_EXT  extern
#endif



//1 表计秒事件类型定义
/*----------------------------------------------------------------------
        陶治国:
    秒驱动(包括分)事件排序原则:
    1、重要的紧急的实时的在前;
    2、快速的在前、慢速的在后(比如可能对25FLASH做删除操作的);
    3、如果慢速操作针对的资源不同，可以优化分开并行操作；
    4、分钟驱动的任务有的可以不实时，但不能丢的，有条件的最好加一个独立分钟变量
    5、综合考虑、优化()；
    程序设计:
    1、将所有秒驱动事件的处理分成主线和副线;
    2、主线的任务按重要性先后排序执行，在新的秒来时，不管其有没有执行完毕，都重新开始；
       在所有主线本身任务执行完成后，必须等待副线任务完成；
       待所有主线任务(包括等待副线完成任务)执行完后，此当前秒的所有任务处理完成，释放处理器资源，等待新的一秒来临；
    3、副线主要是由不太重要，依赖于慢速设备的事情组成。在每秒时间中，必须等主线任务完成的一定程度后才能获得执行；
       副线任务在新秒不重新开始，这样可以避免在最恶劣的条件下，所有任务都有机会被执行到；但过分时间还是必须得复位
       副线任务号，让重要结算等任务能够执行；
       副线任务在新秒来临时，记下当前副线任务号，以便统计当在当前秒内所有任务执行完以一遍时，让主线结束等待；
----------------------------------------------------------------------*/
enum
{
    //MAIN_STEP_SECOND_TIMER,         //软件秒定时器处理
    MAIN_STEP_POWER_GET,            //电量计量相关原始数据获取
    MAIN_STEP_PRICE_SWITCH,         //费率切换
    MAIN_STEP_POWER_ADD,            //能量累加
    MAIN_STEP_DEMAND,               //需量计算、一并判断需量超限事件(涉及FLASH操作)
    MAIN_STEP_ALARM,                //告警处理
    MAIN_STEP_KEY,                  //按键处理
    MAIN_STEP_DISPLAY,              //显示管理，只是操作轮显切换等。具体显示还和通信命令相关，在秒事件外实时更新显示
    MAIN_STEP_PROGRAM_EVENT,        //编程事件
    MAIN_STEP_CLR_EVENT,            //各种清零事件
    MAIN_STEP_TIME_ONE_SECOND,      //其他秒事件(移植自原来程序)
    MAIN_STEP_EVENT_SECTIME_ADD,    //各事件持续秒时间加1
    MAIN_STEP_SLOW_START,           //让副线开始先跑一会儿
    MAIN_STEP_IDLE1,                //让副线先跑一会儿
    MAIN_STEP_VAR1_UPDATE,          //瞬时量1更新()
    MAIN_STEP_VAR2_UPDATE,          //瞬时量2更新()
    //MAIN_STEP_COVER_OPEN,           //表盖\端钮盖开启检测
    MAIN_STEP_ALLLOSS_VOLTAGE,      //全失压事件检测
    MAIN_STEP_POWER_DOWN,           //掉电时间检测
    MAIN_STEP_AUX_POWER,            //辅助电源掉电检测
    MAIN_STEP_AHHOUR,               //安培小时统计
    MAIN_STEP_IDLE2,                //让副线先跑一会儿
    MAIN_STEP_IDLE3,                //让副线先跑一会儿
    MAIN_STEP_ANGEL,                //角度变量换算
    //MAIN_STEP_AD,                   //AD检测
    MAIN_STEP_MONITOR,              //电压合格率统计
    MAIN_STEP_IDLE4,                //让副线再跑一会儿
    MAIN_STEP_IDLE5,                //让副线再跑一会儿
    MAIN_STEP_IDLE6,                //让副线再跑一会儿
#if(CONFIG_METER_HARMONIC_ENABLE == GAL_YES)    
    MAIN_STEP_HARMONIC,             //谐波数据处理和统计
#endif    
    MAIN_STEP_SAVE_DATA,            //数据定时备份
    MAIN_STEP_WAIT_SLOW,            //所有的主要事情都做完，只为等待慢速低重要性事件做完
    MAIN_STEP_COEF_CHECK,           //做参数校验
    MAIN_STEP_MAX,                  //当前秒的所有事情做完
};
enum
{
    SLOW_STEP_RESTORE,              //结算事件(所有分相分布等待处理完)
    SLOW_STEP_FREEZE,               //冻结事件(所有分相分布等待处理完)
    SLOW_STEP_RECORD,               //负荷记录
    SLOW_STEP_CUT_CURRENT,          //断流事件处理(涉及FLASH操作)
    SLOW_STEP_CUT_VOLTAGE,          //断相事件处理(涉及FLASH操作)
    SLOW_STEP_DOWN_VOLTAGE,         //欠压事件处理(涉及FLASH操作)
    SLOW_STEP_LOSS_VOLTAGE,         //失压事件处理(涉及FLASH操作)
    SLOW_STEP_LOSS_CURRENT,         //失流事件处理(涉及FLASH操作)
    SLOW_STEP_ORDER_CURRENT,        //电流逆相序事件处理(涉及FLASH操作)
    SLOW_STEP_ORDER_VOLTAGE,        //电压逆相序事件处理(涉及FLASH操作)
    SLOW_STEP_OVER_CURRENT,         //过流事件处理(涉及FLASH操作)
    SLOW_STEP_OVER_POWER,           //过载事件处理(涉及FLASH操作)
    SLOW_STEP_OVER_VOLTAGE,         //过压事件处理(涉及FLASH操作)
    SLOW_STEP_REVERSE_POWER,        //功率反向事件处理(涉及FLASH操作)
    SLOW_STEP_UNBALANCE_CURRENT,    //电流不平衡事件处理(涉及FLASH操作)
    SLOW_STEP_UNBALANCE_VOLTAGE,    //电压不平衡事件处理(涉及FLASH操作)
    SLOW_STEP_OVER_TOTALCOS,        //功率因数超限事件处理(涉及FLASH操作)
    SLOW_STEP_MAX,                  //当前秒的所有慢速低重要事情做完
};

//1 表的电源状态管理
typedef enum
{
    METER_SYS_IDLE,                 //表计空状态        ----过度态
    METER_SYS_POWERON_INIT,         //表计上电初始化    ----过度态
    METER_SYS_POWEROFF_SAVE,        //表计掉电处理      ----过度态
    METER_SYS_POWEROFF,             //表计掉电状态      ----稳态
    METER_SYS_POWERON,              //表计上电运行      ----稳态
}eMeterSysState;


#define MAX_TIME_PIECE_EACH_SECOND  (10)

//COMMON_EXT int ver;

COMMON_EXT ulong ulNowMinTime;
COMMON_EXT ulong ulNowSecTime;
COMMON_EXT ulong ulRunSecTime;

COMMON_EXT void MeterTaskInit(void);
COMMON_EXT void MeterTaskExit(void);
COMMON_EXT void Meter100msTask(void);
COMMON_EXT void MeterSecondEventSecTimeAdd(void);
COMMON_EXT void MeterEventMinTimeAdd(void);
COMMON_EXT void MeterTimeUpdateSimply(void);
COMMON_EXT uchar MeterTimeGet(uchar isTimePieceAdd);
COMMON_EXT void MeterSecondEvent(void);
COMMON_EXT void MeterPowerOff(void);
COMMON_EXT void MeterCmdOpStateSet(uchar isBusy);
COMMON_EXT uchar MeterCmdOpStateGet(void);

//COMMON_EXT void boad_main_version_get(void);

//表计的系统状态变量
COMMON_EXT eMeterSysState eMeterState;
#define IfPowerStateOn()    (eMeterState == METER_SYS_POWERON)
#define IfPowerStateOff()    (eMeterState != METER_SYS_POWERON)

extern uchar get_cur_uart_port_no(void);
#endif

