//============================================================================
//  File Name: ap_datacoef.h
//
//  Copyright PAX Hangzhou 2011.  All rights reserved.
//
//  Description:
//      参数有关的处理函数数据
//
//  Modification History:
//      $Id:  Exp $
//      $Log: $
//      Revision 1.0 Create by Taozhiguo in 2011.04.28
//============================================================================
#ifndef __AP_DATACOEF_C__
#define __AP_DATACOEF_C__
#include "common.h"

#define CONFIG_METER_COEF_RESUME_3COPY  GAL_YES
#define CON_COEFCHECK_ADD_COEF      0   //(0x33)
#define FIRST_COPY_COEF_START       (EPL_COEF_DATA_START)
#define FIRST_COPY_COEF_END         (EPL_COEF_DATA_END)
#define COEF_LEN                    (EPL_COEF_DATA_END - EPL_COEF_DATA_START)
#if(CONFIG_METER_COEF_RESUME_3COPY == GAL_YES)
#define SECOND_COPY_COEF_START      (BAK_COEF_DATA_START)
#define SECOND_COPY_COEF_END        (SECOND_COPY_COEF_START + COEF_LEN)
#define SECOND_COPY_ADDR_GET(x)     (SECOND_COPY_COEF_START+(x-FIRST_COPY_COEF_START))
#define THIRD_COPY_COEF_START       (FIRST_COPY_COEF_START)
#define THIRD_COPY_COEF_END         (FIRST_COPY_COEF_END)
#define SECOND_COPY_COEF_ADD_COEF   0x00
#define THIRD_COPY_COEF_ADD_COEF    0x33
#endif

typedef struct
{
    u16    CoefLogicAddr;
    u16    UseAddrType:1;
    u16    CoefType:1;
    u16    CoefLen:14;
    ulong   CoefUseAddr;
}ST_COEF_PARRM;

#define COEF_BCD            1
#define COEF_HEX            0
#define COEF_RAMV           0
#define COEF_FUNC           1

#define COEF_ADDR_PHY_TO_LOGIC(PhyAddr)             (PhyAddr-FIRST_COPY_COEF_START)
#define COEF_ADDR_LOGIC_TO_PHY(LogicAddr)           (LogicAddr+FIRST_COPY_COEF_START)
#define COEFPARA(saveaddr,useaddr,utype,dt,len)     ((u16)COEF_ADDR_PHY_TO_LOGIC(saveaddr)), utype,dt,len, (ulong)useaddr  
//所有的参数列表
const ST_COEF_PARRM TB_DATACOEF_TABLE[] = 
{
    {COEFPARA(EPL_USER_NUMBER,                       RAM_USER_NUMBER,                    COEF_RAMV, COEF_BCD, 6)}, // 用户号
    {COEFPARA(EPL_USER_COMM_ADDR,                    RAM_USER_COMM_ADDR,                 COEF_RAMV, COEF_BCD, 6)}, // 用户地址(通讯地址)
    {COEFPARA(EPL_USER_ID,                           RAM_USER_ID,                        COEF_RAMV, COEF_BCD, 6)}, // 用户局号(表号)
    {COEFPARA(EPL_USER_ASSET,                        RAM_USER_ASSET,                     COEF_RAMV, COEF_HEX, 32)}, // 资产管理编号(ASCII码)
    {COEFPARA(EPL_USER_CLIENT,                       RAM_USER_CLIENT,                    COEF_RAMV, COEF_BCD, 6)}, // NNNNNNNNNNNN 客户编号
    {COEFPARA(EPL_CHARACTER_METER_RUN,               RAM_CHARACTER_METER_RUN,            COEF_RAMV, COEF_HEX, 1)}, // 电表运行特征字
    {COEFPARA(EPL_CHARACTER_ACTIVE,                  RAM_CHARACTER_ACTIVE,               COEF_RAMV, COEF_HEX, 1)}, // 有功组合方式特征字
    {COEFPARA(EPL_CHARACTER_REACTIVE01,              RAM_CHARACTER_REACTIVE01,           COEF_RAMV, COEF_HEX, 1)}, // 无功组合方式1特征字
    {COEFPARA(EPL_CHARACTER_REACTIVE02,              RAM_CHARACTER_REACTIVE02,           COEF_RAMV, COEF_HEX, 1)}, // 无功组合方式2特征字
    {COEFPARA(EPL_IR_MODULATOR_BAUDRATE,             RAM_IR_MODULATOR_BAUDRATE,          COEF_RAMV, COEF_HEX, 1)}, // 调制型红外光口通信速率特征字
    {COEFPARA(EPL_IR_CONTACT_BAUDRATE,               RAM_IR_CONTACT_BAUDRATE,            COEF_RAMV, COEF_HEX, 1)}, // 接触式红外光口通信速率特征字
    {COEFPARA(EPL_COMM485_01_BAUDRATE,               RAM_COMM485_01_BAUDRATE,            COEF_RAMV, COEF_HEX, 1)}, // 通讯口1通信速率特征字
#if(CONFIG_METER_NO2COMM_MODE_RS485==CONFIG_METER_NO2COMM_MODE)
    {COEFPARA(EPL_COMM485_02_BAUDRATE,               RAM_COMM485_02_BAUDRATE,            COEF_RAMV, COEF_HEX, 1)}, // 通讯口2通信速率特征字
#endif
    {COEFPARA(EPL_CHARACTER_REST_DAY,                RAM_CHARACTER_REST_DAY,             COEF_RAMV, COEF_HEX, 1)}, // 周休日特征字
    {COEFPARA(EPL_CHARACTER_REST_DAYNO,              RAM_CHARACTER_REST_DAYNO,           COEF_RAMV, COEF_BCD, 1)}, // 周休日采用的日时段表号
    {COEFPARA(EPL_CHARACTER_CHARGE_MODE,             RAM_CHARACTER_CHARGE_MODE,          COEF_RAMV, COEF_HEX, 1)}, // 负荷记录模式字
    {COEFPARA(EPL_CHARACTER_FREEZE_EVERYTIME_MODE,   RAM_CHARACTER_FREEZE_EVERYTIME_MODE,COEF_RAMV, COEF_HEX, 1)}, // 定时冻结数据模式字
    {COEFPARA(EPL_CHARACTER_FREEZE_INSTANT_MODE,     RAM_CHARACTER_FREEZE_INSTANT_MODE,  COEF_RAMV, COEF_HEX, 1)}, // 瞬时冻结数据模式字
    {COEFPARA(EPL_CHARACTER_FREEZE_RESTORE_MODE,     RAM_CHARACTER_FREEZE_RESTORE_MODE,  COEF_RAMV, COEF_HEX, 1)}, // 约定冻结数据模式字
    {COEFPARA(EPL_CHARACTER_FREEZE_EVERYHOUR_MODE,   RAM_CHARACTER_FREEZE_EVERYHOUR_MODE,COEF_RAMV, COEF_HEX, 1)}, // 整点冻结数据模式字
    {COEFPARA(EPL_CHARACTER_FREEZE_EVERYDAY_MODE,    RAM_CHARACTER_FREEZE_EVERYDAY_MODE, COEF_RAMV, COEF_HEX, 1)}, // 日冻结数据模式字
    {COEFPARA(EPL_CHARACTER_FREEZE_EVERYHOUR_STARTTIME, RAM_CHARACTER_FREEZE_EVERYHOUR_STARTTIME,    COEF_RAMV, COEF_BCD, 5)}, // YYMMDDhhmm 整点冻结起始时间
    {COEFPARA(EPL_CHARACTER_FREEZE_EVERYHOUR_INTERVAL, RAM_CHARACTER_FREEZE_EVERYHOUR_INTERVAL,      COEF_RAMV, COEF_BCD, 1)}, // NN 整点冻结时间间隔
    {COEFPARA(EPL_CHARACTER_FREEZE_EVERYDAY_TIME,    RAM_CHARACTER_FREEZE_EVERYDAY_TIME, COEF_RAMV, COEF_BCD, 2)}, // hhmm 日冻结时间
    {COEFPARA(EPL_CHARGE_RECORD_START_TIME,          RAM_CHARGE_RECORD_START_TIME,       COEF_RAMV, COEF_BCD, 4)}, // MMDDHHMM 负荷记录起始时间
    {COEFPARA(EPL_CHARGE_RECORD_1_TIME,              RAM_CHARGE_RECORD_1_TIME,           COEF_RAMV, COEF_BCD, 2)}, // MM 第1类负荷记录间隔时间
    {COEFPARA(EPL_CHARGE_RECORD_2_TIME,              RAM_CHARGE_RECORD_2_TIME,           COEF_RAMV, COEF_BCD, 2)}, // MM 第2类负荷记录间隔时间
    {COEFPARA(EPL_CHARGE_RECORD_3_TIME,              RAM_CHARGE_RECORD_3_TIME,           COEF_RAMV, COEF_BCD, 2)}, // MM 第3类负荷记录间隔时间
    {COEFPARA(EPL_CHARGE_RECORD_4_TIME,              RAM_CHARGE_RECORD_4_TIME,           COEF_RAMV, COEF_BCD, 2)}, // MM 第4类负荷记录间隔时间
    {COEFPARA(EPL_CHARGE_RECORD_5_TIME,              RAM_CHARGE_RECORD_5_TIME,           COEF_RAMV, COEF_BCD, 2)}, // MM 第5类负荷记录间隔时间
    {COEFPARA(EPL_CHARGE_RECORD_6_TIME,              RAM_CHARGE_RECORD_6_TIME,           COEF_RAMV, COEF_BCD, 2)}, // MM 第6类负荷记录间隔时间
    {COEFPARA(EPL_BALANCE_DAY_NUM,                   RAM_BALANCE_DAY_NUM,                COEF_RAMV, COEF_BCD, 1)}, // NN 每月结算日数量
    {COEFPARA(EPL_BALANCE_DAY_01,                    RAM_BALANCE_DAY_01,                 COEF_RAMV, COEF_BCD, 2)}, // DDHH 每月第1结算日(9999代表未设置此结算日)
    {COEFPARA(EPL_BALANCE_DAY_02,                    RAM_BALANCE_DAY_02,                 COEF_RAMV, COEF_BCD, 2)}, // DDHH 每月第2结算日(9999代表未设置此结算日)
    {COEFPARA(EPL_BALANCE_DAY_03,                    RAM_BALANCE_DAY_03,                 COEF_RAMV, COEF_BCD, 2)}, // DDHH 每月第3结算日(9999代表未设置此结算日)
    {COEFPARA(EPL_COEF_MAX_KWH_F,                    RAM_COEF_MAX_KWH_F,                 COEF_RAMV, COEF_BCD, 3)}, // XX.XXXX 正向有功功率上限值
    {COEFPARA(EPL_COEF_MAX_KWH_R,                    RAM_COEF_MAX_KWH_R,                 COEF_RAMV, COEF_BCD, 3)}, // XX.XXXX 反向有功功率上限值
    {COEFPARA(EPL_COEF_VOLTAGE_LIMIT_UPPER,          MoniterParaInit,                    COEF_FUNC, COEF_BCD, 2)}, // XXX.X 电压上限值
    {COEFPARA(EPL_COEF_VOLTAGE_LIMIT_LOWER,          MoniterParaInit,                    COEF_FUNC, COEF_BCD, 2)}, // XXX.X 电压下限值
    {COEFPARA(EPL_COEF_FREEZE_TIME,                  RAM_COEF_FREEZE_TIME,               COEF_RAMV, COEF_BCD, 4)}, // mmhhDDMM 预约冻结时间

    {COEFPARA(EPL_COEF_LOSS_VOLTAGE_CONDITION,       LossVoltageParaInit,                COEF_FUNC, COEF_BCD, (8))},// 失压判断条件
    {COEFPARA(EPL_COEF_DOWN_VOLTAGE_CONDITION,       DownVoltageParaInit,                COEF_FUNC, COEF_BCD, (3))},// 欠压判断条件
    {COEFPARA(EPL_COEF_OVER_VOLTAGE_CONDITION,       OverVoltageParaInit,                COEF_FUNC, COEF_BCD, (3))},// 过压判断条件
    {COEFPARA(EPL_COEF_CUT_VOLTAGE_CONDITION,        CutVoltageParaInit,                 COEF_FUNC, COEF_BCD, (6))},// 断相判断条件
    {COEFPARA(EPL_COEF_UNBALANCE_VOLTAGE_CONDITION,  UnbalanceVoltageParaInit,           COEF_FUNC, COEF_BCD, (3))},// 电压不平衡判断条件
    {COEFPARA(EPL_COEF_UNBALANCE_CURRENT_CONDITION,  UnbalanceCurrentParaInit,           COEF_FUNC, COEF_BCD, (3))},// 电流不平衡判断条件
    {COEFPARA(EPL_COEF_LOSS_CURRENT_CONDITION,       LossCurrentParaInit,                COEF_FUNC, COEF_BCD, (9))},// 失流判断条件
    {COEFPARA(EPL_COEF_OVER_CURRENT_CONDITION,       OverCurrentParaInit,                COEF_FUNC, COEF_BCD, (3))},// 过流判断条件
    {COEFPARA(EPL_COEF_CUT_CURRENT_CONDITION,        CutCurrentParaInit,                 COEF_FUNC, COEF_BCD, (6))},// 断流判断条件
    {COEFPARA(EPL_COEF_REVERSEPOWER_CONDITION,       ReversePowerParaInit,               COEF_FUNC, COEF_BCD, (4))},// 潮流反向判断条件
    {COEFPARA(EPL_COEF_OVER_KW_CONDITION,            OverPowerParaInit,                  COEF_FUNC, COEF_BCD, (4))},// 过载判定条件

    {COEFPARA(EPL_COEF_MONITOR_VOLTAGE_CONDITION,    MoniterParaInit,                    COEF_FUNC, COEF_BCD, (4))},// 电压考核判断条件
    {COEFPARA(EPL_COEF_DEMAND_OVER_CONDITION,        DemandOverParaInit,                 COEF_FUNC, COEF_BCD, (7))},// 需量超限判定条件
    {COEFPARA(EPL_COEF_OVERTOTALCOS_CONDITION,       OverTotalCosParaInit,               COEF_FUNC, COEF_BCD, (3))},// 总功率因数判断条件
    {COEFPARA(EPL_COEF_UNBALANCE_SEVERITY_CURRENT_CONDITION,   UnbalanceCurrentParaInit, COEF_FUNC, COEF_BCD, (3))},// 电流严重不平衡判断条件
	{COEFPARA(EPL_COEF_ALARM_SPEEK,                  RAM_COEF_ALARM_SPEEK,               COEF_RAMV, COEF_HEX, (20))},// 声光显示报警控制字
    
    {COEFPARA(EPL_COEF_PROGRAM_TIME,                 RAM_COEF_PROGRAM_TIME,              COEF_RAMV, COEF_BCD, 2)}, // NN 分 编程维持时间
    {COEFPARA(EPL_COEF_DISPLAY_MODE_CHANGE_TIME,     RAM_COEF_DISPLAY_MODE_CHANGE_TIME,  COEF_RAMV, COEF_BCD, 2)}, // NNNN秒 轮显切换时间
    {COEFPARA(EPL_COEF_REMOTE_WAKEUP_ENABLE,         RAM_COEF_REMOTE_WAKEUP_ENABLE,      COEF_RAMV, COEF_BCD, 1)}, // NN 红外唤醒模式
    {COEFPARA(EPL_COEF_POWERDOWN_ALLLOSSVOLTAGE_CONDITION,  RAM_COEF_POWERDOWN_ALLLOSSVOLTAGE_CONDITION,    COEF_RAMV, COEF_BCD, 5)}, // XXX.XV+XXX.XXXA 全失压判断条件(停电)
#if((CONFIG_METER_TYPE_SD39C==CONFIG_METER_TYPE) || (CONFIG_METER_AREA_MODE == CONFIG_METER_AREA_MODE_SOUTHGRID))
    {COEFPARA(EPL_COEF_CLR_METER_ENABLE_TIMES,       RAM_COEF_CLR_METER_ENABLE_TIMES,    COEF_RAMV, COEF_HEX, 1)},// 1 byte  BCD 电量清零允许次数(南网适用)
#endif
    {COEFPARA(EPL_DEMAND_CYCLE_TIME,                 DemandParaInit,                     COEF_FUNC, COEF_BCD, (2))},
    {COEFPARA(EPL_COEF_2SEASONCHANGE_TIME,           RAM_COEF_2SEASONCHANGE_TIME,        COEF_RAMV, COEF_BCD, 5)}, // YYMMDDHHMM 两套时区表切换时间
    {COEFPARA(EPL_COEF_2DAYTABLECHANGE_TIME,         RAM_COEF_2DAYTABLECHANGE_TIME,      COEF_RAMV, COEF_BCD, 5)}, // YYMMDDHHMM 两套时段表切换时间
    {COEFPARA(EPL_COEF_STEPPRICE_CHANGETIME,         RAM_COEF_STEPPRICE_CHANGETIME,      COEF_RAMV, COEF_BCD, 5)}, // YYMMDDHHMM 两套阶梯表切换时间(切换完,自动清零)
    {COEFPARA(EPL_COEF_PERIODPRICE_CHANGETIME,       RAM_COEF_PERIODPRICE_CHANGETIME,    COEF_RAMV, COEF_BCD, 5)}, // YYMMDDHHMM 两套费率电价切换时间(切换完,自动清零)
    {COEFPARA(EPL_COEF_SEASONTABLE_MAX_NUM,          RAM_COEF_SEASONTABLE_MAX_NUM,       COEF_RAMV, COEF_BCD, 1)}, // XX 年时区数P小于14
    {COEFPARA(EPL_COEF_DAYTABLE_MAX_NUM,             RAM_COEF_DAYTABLE_MAX_NUM,          COEF_RAMV, COEF_BCD, 1)}, // XX 日时段表数Q小于8
    {COEFPARA(EPL_COEF_PERIOD_MAX_NUM,               RAM_COEF_PERIOD_MAX_NUM,            COEF_RAMV, COEF_BCD, 1)}, // XX 日时段数(每日切换数)m小于14
    {COEFPARA(EPL_COEF_PRICE_MAX_NUM,                RAM_COEF_PRICE_MAX_NUM,             COEF_RAMV, COEF_BCD, 1)}, // XX 费率数k小于63
    {COEFPARA(EPL_COEF_HOLIDAY_MAX_MUN,              RAM_COEF_HOLIDAY_MAX_MUN,           COEF_RAMV, COEF_BCD, 2)}, // XXXX 公共假日数n小于254

    {COEFPARA(EPL_COEF_HUMOROUS_MAX_NUM,             RAM_COEF_HUMOROUS_MAX_NUM,          COEF_RAMV, COEF_BCD, 1)}, // XX 谐波分析次数
    {COEFPARA(EPL_COEF_STEP_NUM,                     RAM_COEF_STEP_NUM,                  COEF_RAMV, COEF_BCD, 1)}, // XX 阶梯个数
    {COEFPARA(EPL_COEF_AUTO_TURNPAGE_NUM,            RAM_COEF_AUTO_TURNPAGE_NUM,         COEF_RAMV, COEF_BCD, 1)}, // XX 自动循环显示屏数
    {COEFPARA(EPL_COEF_TURNPAGE_TIME,                RAM_COEF_TURNPAGE_TIME,             COEF_RAMV, COEF_BCD, 1)}, // XX 每屏显示时间
    {COEFPARA(EPL_COEF_POWER_POINT_NUM,              RAM_COEF_POWER_POINT_NUM,           COEF_RAMV, COEF_BCD, 1)}, // XX 显示电能小数位数

    {COEFPARA(EPL_COEF_DEMAND_POINT_NUM,             RAM_COEF_DEMAND_POINT_NUM,          COEF_RAMV, COEF_BCD, 1)},// XX 显示功率(最大需量)小数位数
    {COEFPARA(EPL_COEF_KEY_TURNPAGE_NUM,             RAM_COEF_KEY_TURNPAGE_NUM,          COEF_RAMV, COEF_BCD, 1)},// XX 按键循环显示屏数
    {COEFPARA(EPL_COEF_PT_NUM,                       RAM_COEF_PT_NUM,                    COEF_RAMV, COEF_BCD, 3)},// XXXXXX 电流互感器变比
    {COEFPARA(EPL_COEF_CT_NUM,                       RAM_COEF_CT_NUM,                    COEF_RAMV, COEF_BCD, 3)},// XXXXXX 电压互感器变比
    {COEFPARA(EPL_SEASON1_DAYTABLE_CHANGE01,         RAM_SEASON1_DAYTABLE_CHANGE01,      COEF_RAMV, COEF_BCD, 42)},// MMDDNN 第一套第1时区起始日期及日时段表号
    {COEFPARA(EPL_SEASON1_DAYTABLE1_PERIOD01,        RAM_SEASON1_DAYTABLE1_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN 第一套第1日时段表第1时段起始时间及费率号
    {COEFPARA(EPL_SEASON1_DAYTABLE2_PERIOD01,        RAM_SEASON1_DAYTABLE2_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN 第一套第2日时段表第1时段起始时间及费率号
    {COEFPARA(EPL_SEASON1_DAYTABLE3_PERIOD01,        RAM_SEASON1_DAYTABLE3_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN 第一套第3日时段表第1时段起始时间及费率号
    {COEFPARA(EPL_SEASON1_DAYTABLE4_PERIOD01,        RAM_SEASON1_DAYTABLE4_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN 第一套第4日时段表第1时段起始时间及费率号
    {COEFPARA(EPL_SEASON1_DAYTABLE5_PERIOD01,        RAM_SEASON1_DAYTABLE5_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN 第一套第5日时段表第1时段起始时间及费率号
    {COEFPARA(EPL_SEASON1_DAYTABLE6_PERIOD01,        RAM_SEASON1_DAYTABLE6_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN 第一套第6日时段表第1时段起始时间及费率号
    {COEFPARA(EPL_SEASON1_DAYTABLE7_PERIOD01,        RAM_SEASON1_DAYTABLE7_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN 第一套第7日时段表第1时段起始时间及费率号
    {COEFPARA(EPL_SEASON1_DAYTABLE8_PERIOD01,        RAM_SEASON1_DAYTABLE8_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN 第一套第8日时段表第1时段起始时间及费率号
    {COEFPARA(EPL_SEASON2_DAYTABLE_CHANGE01,         RAM_SEASON2_DAYTABLE_CHANGE01,      COEF_RAMV, COEF_BCD, 42)},// MMDDNN 第二套第1时区起始日期及日时段表号
    {COEFPARA(EPL_SEASON2_DAYTABLE1_PERIOD01,        RAM_SEASON2_DAYTABLE1_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN 第二套第1日时段表第1时段起始时间及费率号
    {COEFPARA(EPL_SEASON2_DAYTABLE2_PERIOD01,        RAM_SEASON2_DAYTABLE2_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN 第二套第2日时段表第1时段起始时间及费率号
    {COEFPARA(EPL_SEASON2_DAYTABLE3_PERIOD01,        RAM_SEASON2_DAYTABLE3_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN 第二套第3日时段表第1时段起始时间及费率号
    {COEFPARA(EPL_SEASON2_DAYTABLE4_PERIOD01,        RAM_SEASON2_DAYTABLE4_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN 第二套第4日时段表第1时段起始时间及费率号
    {COEFPARA(EPL_SEASON2_DAYTABLE5_PERIOD01,        RAM_SEASON2_DAYTABLE5_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN 第二套第5日时段表第1时段起始时间及费率号
    {COEFPARA(EPL_SEASON2_DAYTABLE6_PERIOD01,        RAM_SEASON2_DAYTABLE6_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN 第二套第6日时段表第1时段起始时间及费率号
    {COEFPARA(EPL_SEASON2_DAYTABLE7_PERIOD01,        RAM_SEASON2_DAYTABLE7_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN 第二套第7日时段表第1时段起始时间及费率号
    {COEFPARA(EPL_SEASON2_DAYTABLE8_PERIOD01,        RAM_SEASON2_DAYTABLE8_PERIOD01,     COEF_RAMV, COEF_BCD, 42)},// hhmmNN 第二套第8日时段表第1时段起始时间及费率号
    {COEFPARA(EPL_PERIODPRICE01_PRICE01,             RAM_PERIODPRICE01_PRICE01,          COEF_RAMV, COEF_BCD, 56)},// NNNN.NNNN 第一套费率电价1
    {COEFPARA(EPL_PERIODPRICE02_PRICE01,             RAM_PERIODPRICE02_PRICE01,          COEF_RAMV, COEF_BCD, 56)},// NNNN.NNNN 第二套费率电价1
    {COEFPARA(EPL_STEP01_DATA01,                     RAM_STEP01_DATA01,                  COEF_RAMV, COEF_BCD, 56)},// NNNNNN.NN 第一套第01阶梯值
    {COEFPARA(EPL_STEPPRICE01_PRICE01,               RAM_STEPPRICE01_PRICE01,            COEF_RAMV, COEF_BCD, 56)},// NNNN.NNNN 第一套阶梯电价01
    {COEFPARA(EPL_STEP02_DATA01,                     RAM_STEP02_DATA01,                  COEF_RAMV, COEF_BCD, 56)},// NNNNNN.NN 第二套第01阶梯值
    {COEFPARA(EPL_STEPPRICE02_PRICE01,               RAM_STEPPRICE02_PRICE01,            COEF_RAMV, COEF_BCD, 56)},// NNNN.NNNN 第二套阶梯电价01
};

//当前检察的参数大类型
u16 ucCoefTypeCheckPoint;          
//当前检察的参数小类型或数据项
uchar ucCoefPowerCheckTablePoint;   //用于参数表 TB_DATACOEF_TABLE
uchar ucCoefPowerCheckAde7758;      //专用于7758检察
uchar ucKwhDataCheckPoint;          //专用于电量检察

/*==================================================================
//函数名：  CoefCheckMode
//作者：    陶治国
//日期：    
//功能：    参数 数据校验
//          在空闲时，对各参数数据进行重读校验
//输入参数：无
//输出参数：无
//返回值：  无
//=================================================================*/
uchar CoefCheckMode(void)
{
    //static uchar ucCoefCheckMinute=0;
#define CON_COEFPOWERCHECK_ADEREG       0
#define CON_COEFPOWERCHECK_POWER        1
#define CON_COEFPOWERCHECK_COEF         2
#define CON_COEFPOWERCHECK_MAX          2

    u16 uiLen;
    const ST_COEF_PARRM* ptr;
    
    // AA    前几秒钟不处理  AA 
    if((RSOFT_RTC_SECOND<5)||(RSOFT_RTC_SECOND>0x55)||(0==RSOFT_RTC_MINUTE))
    {
        return DLT_RET_SUCC;
    }
    
    //if(ucCoefCheckMinute != RSOFT_RTC_MINUTE)
    {
        //每分钟查一个参数，分散参数校验的频率，降低系统负担
        //ucCoefCheckMinute = RSOFT_RTC_MINUTE;
        //优先检察
        /*if(GAL_YES==ucCoefCheckDisplayReNewRequest)
        {
            ucCoefCheckDisplayReNewRequest=GAL_NO;
            CheckDisplayControl();
            return DLT_RET_SUCC;
        }*/
        //MTRACE("CoefCheck %d, %d, %d, %d\n", ucCoefTypeCheckPoint, ucCoefPowerCheckAde7758, ucKwhDataCheckPoint, ucCoefPowerCheckTablePoint);
        if(ucCoefTypeCheckPoint<CON_COEFPOWERCHECK_MAX)
        {
            ucCoefTypeCheckPoint++;
        }
        else
        {
            ucCoefTypeCheckPoint=0;
        }
        
        if((CON_COEFPOWERCHECK_COEF==ucCoefTypeCheckPoint))
        // AA   检测系统参数  AA 
        {
            uiLen=sizeof(TB_DATACOEF_TABLE)/sizeof(ST_COEF_PARRM);
			//while(ucCoefPowerCheckTablePoint<uiLen)
			if(ucCoefPowerCheckTablePoint<uiLen)
			{
                ptr = &(TB_DATACOEF_TABLE[ucCoefPowerCheckTablePoint]);
                if(ptr->UseAddrType == COEF_FUNC)
                {
                    ((func)(ptr->CoefUseAddr))();
                }
                else
                {
                    if((ptr->CoefUseAddr+ptr->CoefLen) < CONST_RAM_LEN)
                    {
                        ReadCoefDataWithCheck(COEF_ADDR_LOGIC_TO_PHY(ptr->CoefLogicAddr), ptr->CoefLen, &RAM[ptr->CoefUseAddr], ptr->UseAddrType);
                    }
                }
				ucCoefPowerCheckTablePoint++;
			}
            else if((uiLen+1)==ucCoefPowerCheckTablePoint)
            {
                ProgFunctionLoad();
                ucCoefPowerCheckTablePoint++;
            }
            else if((uiLen+2)==ucCoefPowerCheckTablePoint)
            {
                //最好改成分片校验
                PriceSwitchModeParaInit();
                ucCoefPowerCheckTablePoint++;
            }     
            /*else if((uiLen+3)==ucCoefPowerCheckTablePoint)
            {
                CheckDisplayControl();
                ucCoefPowerCheckTablePoint++;
            } */    
            else
            {
                ucCoefPowerCheckTablePoint = 0;
            }
        }
#if 1           
        else if(CON_COEFPOWERCHECK_ADEREG==ucCoefTypeCheckPoint)
        // AA   检测ADE7758  AA 
        {
                if(1==CheckADE7758())
                {
                    ucCoefPowerCheckAde7758++;
                }
                else
                {
                    ucCoefPowerCheckAde7758=0;
                }
                if(ucCoefPowerCheckAde7758>30) 
                {
                    InitADMode(GAL_YES, GAL_NO);
                    ucCoefPowerCheckAde7758=0;
                }
        }
#endif
        else if((CON_COEFPOWERCHECK_POWER==ucCoefTypeCheckPoint))
        // AA   检测系统电量数据  AA 
        {
            //ucKwhErrEventRecordMode=CON_KWH_ERR_EVENT_RECORD_START;
            ucKwhDataCheckPoint++;
            if(ucKwhDataCheckPoint>=PT_KWH_TOTAL)
                ucKwhDataCheckPoint=0;
            if(KWH_CHECK_ALL_OK!=KwhPowerOnSafeCheck(ucKwhDataCheckPoint,TB_KWH_RESUME_CAN_SUB[ucKwhDataCheckPoint].stCanSub))
            {
                WritePower3Copy(ucKwhDataCheckPoint);
            }
            //ucKwhErrEventRecordMode=CON_KWH_ERR_EVENT_RECORD_END;
        }
		//ZD 预付费模式，在集中器或专变中，不用
/*
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
        else if((CON_COEFCARDCHECK_COEF==ucCoefTypeCheckPoint))
        {
            GetPrepayRunPara();
        }
#endif
*/
    }
    return DLT_RET_SUCC;

}

/*==================================================================
//函数名：  CoefPowerUpResume
//作者：    陶治国
//日期：    
//功能：    参数 数据校验和读取
//输入参数：isPowerUpInit:      1: Init when Power up
                                0: Others
//输出参数：无
//返回值：  无
//=================================================================*/
void CoefPowerUpResume(uchar isPowerUpInit)
{
    u16 uiIdx, uiLen;
    const ST_COEF_PARRM* ptr;

    uiLen=sizeof(TB_DATACOEF_TABLE)/sizeof(ST_COEF_PARRM);
    for(uiIdx=0; uiIdx<uiLen; uiIdx++)
    {
        ptr = &(TB_DATACOEF_TABLE[uiIdx]);
        if(ptr->UseAddrType == COEF_FUNC)
        {
            if(isPowerUpInit == 0)
            {
                //开机恢复初始化时，带函数的由各模块独自初始化
                //非开机初始化时，需要在这里一并初始化
                ((func)(ptr->CoefUseAddr))();
            }
        }
        else
        {
            if((ptr->CoefUseAddr+ptr->CoefLen) < CONST_RAM_LEN)
            {
                ReadCoefDataWithCheck(COEF_ADDR_LOGIC_TO_PHY(ptr->CoefLogicAddr), ptr->CoefLen, &RAM[ptr->CoefUseAddr], ptr->UseAddrType);
            }
        }
    }

#if(CONFIG_METER_STEP_MODE!=CONFIG_METER_STEP_MODE_ENABLE)
    RAM[RAM_COEF_STEP_NUM]=0;
#endif
}

/*==================================================================
//函数名：  WriteCoefDataWithSync
//作者：    陶治国
//日期：    
//功能：    参数数据备份
//          参数数据备份，同时同步到其他备份区
//          备份同时，更新使用的相应参数
//          目前参数 DataName 必须是EPL开头(有机会改成逻辑地址)，否则当普通地址数据写入
//输入参数：无
//输出参数：无
//返回值：  无
//=================================================================*/
uchar WriteCoefDataWithSync(const uchar *ucData, ulong DataName, u16 uiLen)
{
    uchar ret=DLT_RET_SUCC;
    
    if((DataName < FIRST_COPY_COEF_START) || ((DataName+uiLen) >= FIRST_COPY_COEF_END))
    {
        ret = WriteDataDirect(ucData, DataName, uiLen);
    }
    else
    {
        u16 uiIdx, uiDataUnitMax;
        ulong ulLogicAddr, ulLogicAddrMax;
        const ST_COEF_PARRM* ptr;
        
        //if(uiLen > 200)
        //    return DLT_RET_ERR;
        ret = WriteDataDirect(ucData, DataName, uiLen);
#if(GAL_YES==CONFIG_METER_COEF_RESUME_3COPY)
        ret = WriteDataDirect(ucData, SECOND_COPY_ADDR_GET(DataName), uiLen);
#endif   
        //MTRACE("COEF %d, 0x%08x, %d, %d\n", ret, SECOND_COPY_ADDR_GET(DataName), ucData[0], ucData[1]);
        //使用中的参数更新
        uiDataUnitMax=sizeof(TB_DATACOEF_TABLE)/sizeof(ST_COEF_PARRM);
        ulLogicAddr = COEF_ADDR_PHY_TO_LOGIC(DataName);
        ulLogicAddrMax = COEF_ADDR_PHY_TO_LOGIC(DataName+uiLen);
        for(uiIdx=0; uiIdx<uiDataUnitMax; uiIdx++)
        {
            ptr = &(TB_DATACOEF_TABLE[uiIdx]);
            //地址在数据项里
            if((ulLogicAddr >= ptr->CoefLogicAddr ) && (ulLogicAddr < (ptr->CoefLogicAddr+ptr->CoefLen)))
            {
                if(ptr->UseAddrType == COEF_FUNC)
                {
                    ((func)(ptr->CoefUseAddr))();
                }
                else
                {
                    if((ptr->CoefUseAddr+ptr->CoefLen) < CONST_RAM_LEN)
                    {
                        //ptr->CoefLen  or others ? Now, use ptr->CoefLen temply
                        ret = ReadCoefDataWithCheck(COEF_ADDR_LOGIC_TO_PHY(ptr->CoefLogicAddr), ptr->CoefLen, &RAM[ptr->CoefUseAddr], ptr->UseAddrType);
                    }
                }
                //继续查找下一个数据项
                ulLogicAddr += ptr->CoefLen;
                if(ulLogicAddr >= ulLogicAddrMax)
                {
                    return ret;
                }
            }
        }
    }
    return ret;
}

/*==================================================================
//函数名：  ReadCoefDataWithCheck
//作者：    陶治国
//日期：    
//功能：    参数数据读取
//          参数数据读取，同时参考比较其他备份区
//          目前参数 DataName 必须是EPL开头(有机会改成逻辑地址)，否则当普通地址数据写入
//输入参数：无
//输出参数：无
//返回值：  无
//=================================================================*/
uchar ReadCoefDataWithCheck(ulong DataName, u16 uiLen, uchar* pSrc, uchar ucTestBcd)
{
    uchar ucTemp,ucValue;

    if((DataName < FIRST_COPY_COEF_START) || ((DataName+uiLen) >= FIRST_COPY_COEF_END))
    {
        //return DLT_RET_ERR;
        return ReadDataDirect(DataName, uiLen, pSrc);
    }
    
    if(uiLen > CON_WR_DATA_LEN_MAX)
        return DLT_RET_ERR;

    uchar ret,ret1;
    ret = ReadDataDirect(DataName, uiLen, pSrc);
#if(GAL_YES==CONFIG_METER_COEF_RESUME_3COPY)    
    if(uiLen > CON_WR_DATA_LEN_MAX)
    {
        ret1 = 0;
    }
    else
    {
        ret1 = ReadDataDirect(SECOND_COPY_ADDR_GET(DataName),  uiLen, &Wr_data[0]);
    }
    //MTRACE("%d, 0x%02X, %d, 0x%02X\n", ret, pSrc[0], ret1, Wr_data[0]);
    if((ret == 1) && (ret1 == 0))
    {
        return DLT_RET_SUCC;
    }
    else if((ret == 0) && (ret1 == 1)) 
    {
        memcpy(pSrc, &Wr_data[0], uiLen);
        return DLT_RET_SUCC;
    }
    else if((ret == 1) && (ret1 == 1))
    {
        ucValue = 1;
        for(ucTemp=0;ucTemp<uiLen;ucTemp++)
        {
            if(pSrc[ucTemp] != Wr_data[ucTemp])
            {
                ucValue=0;
                ucTemp=uiLen;
            }
        }
        // 数据出错处理
        if(0==ucValue)
        {
            // 当铁电和e2p的数据都出现错误时，优先考虑铁电
            if((0==ucTestBcd)||(uiLen==TestBcdNum(&pSrc[0], uiLen)))
            {
            }
            else
            {
                if((0==ucTestBcd)||(uiLen==TestBcdNum(&Wr_data[0], uiLen)))
                {
                    for(ucTemp=0;ucTemp<uiLen;ucTemp++)
                    {
                        pSrc[ucTemp]=Wr_data[ucTemp];
                    }
                }
                else
                {
                    return DLT_RET_ERR;
                }
            }
        }    
        return DLT_RET_SUCC;
    }
    else
    {
        return DLT_RET_ERR;
    }
#else    
    if(ret == 1)
        return DLT_RET_SUCC;
    else
        return DLT_RET_ERR;
#endif
}

/*==================================================================
//函数名：  GetSetHarmonicNumber
//作者：    陶治国
//日期：    
//功能：    获得设置的谐波计算次数
//输入参数：无
//输出参数：无
//返回值：  无
//=================================================================*/
uchar GetSetHarmonicNumber(void)
{
#if(CONFIG_METER_HARMONIC_ENABLE == GAL_YES)    
    uchar TmpNum;
    ReadDataDirect(RAM_COEF_HUMOROUS_MAX_NUM,1,&TmpNum);  //读设置的费率数
    TmpNum=BCD_Byte(TmpNum);                              //BCD码转HEX码
    if(TmpNum>DLT_METER_HORMANIC_MAX)                     //设置的费率数大于最大费率数
        TmpNum = DLT_METER_HORMANIC_MAX;                  //设置的费率数等于最大费率数

    return (TmpNum);
#else
    return 0;
#endif
}
#endif

