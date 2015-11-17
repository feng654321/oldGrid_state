


#ifndef AP_TWOTABLE_H
    #define AP_TWOTABLE_H
    
#ifdef  AP_TWOTABLE_GLOBALS
    #define AP_TWOTABLE_EXT
#else
    #define AP_TWOTABLE_EXT extern
#endif  











typedef struct
{
    uchar ucBlockType;
    u16 ucMaxBlockNum;
    //uchar ucBlockNum;
    ulong ulBlockStartAddr;
    u16 ulBlockLen;
}ST_TWOTAB_PARAM;


#define GAL_TWOTABLE_LEN 95

#define GAL_GETTWOTABLE_ADDRERR     0xFFFFFFFF
#define GAL_GETTWOTABLE_POINTRERR   0xFF800000
//#define IS_TWOTABLE_ADDR_ERR(addr)          ( ((addr) == GAL_GETTWOTABLE_ADDRERR) || ((addr) == GAL_GETTWOTABLE_POINTRERR) )
#define IS_TWOTABLE_ADDR_ERR(addr)          ( ((addr) == GAL_GETTWOTABLE_ADDRERR) )

#define TYPE_HISTROY_POWER_RECORD 0 // 0    历史电量数据记录
#define TYPE_HISTROY_DEMAND_RECORD 1    // 1    历史需量数据记录
#define TYPE_HISTROY_USEPOWER_RECORD 2  // 2    历史用电量数据记录
#define TYPE_MONITOR_VOLTAGE_ALL_RECORD 3   // 3    电压合格率统计数据记录
#define TYPE_MONITOR_VOLTAGE_A_RECORD 4 // 4    A相电压合格率统计数据记录
#define TYPE_MONITOR_VOLTAGE_B_RECORD 5 // 5    B相电压合格率统计数据记录
#define TYPE_MONITOR_VOLTAGE_C_RECORD 6 // 6    C相电压合格率统计数据记录
#define TYPE_LOSS_A_VOLTAGE_RECORD  7   //  7   A相失压事件记录
#define TYPE_LOSS_B_VOLTAGE_RECORD  8   //  8   B相失压事件记录
#define TYPE_LOSS_C_VOLTAGE_RECORD  9   //  9   C相失压事件记录
#define TYPE_LOSS_AB_VOLTAGE_RECORD 10  //  10  AB相失压事件记录
#define TYPE_LOSS_AC_VOLTAGE_RECORD 11  //  11  AC相失压事件记录
#define TYPE_LOSS_BC_VOLTAGE_RECORD 12  //  12  BC相失压事件记录
#define TYPE_LOSS_ABC_VOLTAGE_RECORD    13  //  13  ABC相失压事件记录
#define TYPE_DOWN_A_VOLTAGE_RECORD  14  //  14  A相欠压事件记录
#define TYPE_DOWN_B_VOLTAGE_RECORD  15  //  15  B相欠压事件记录
#define TYPE_DOWN_C_VOLTAGE_RECORD  16  //  16  C相欠压事件记录
#define TYPE_OVER_A_VOLTAGE_RECORD  17  //  17  A相过压事件记录
#define TYPE_OVER_B_VOLTAGE_RECORD  18  //  18  B相过压事件记录
#define TYPE_OVER_C_VOLTAGE_RECORD  19  //  19  C相过压事件记录
#define TYPE_CUT_A_VOLTAGE_RECORD   20  //  20  A相断相事件记录
#define TYPE_CUT_B_VOLTAGE_RECORD   21  //  21  B相断相事件记录
#define TYPE_CUT_C_VOLTAGE_RECORD   22  //  22  C相断相事件记录
#define TYPE_LOSS_A_CURRENT_RECORD  23  //  23  A相失流事件记录
#define TYPE_LOSS_B_CURRENT_RECORD  24  //  24  B相失流事件记录
#define TYPE_LOSS_C_CURRENT_RECORD  25  //  25  C相失流事件记录
#define TYPE_LOSS_AB_CURRENT_RECORD 26  //  26  AB相失流事件记录
#define TYPE_LOSS_AC_CURRENT_RECORD 27  //  27  AC相失流事件记录
#define TYPE_LOSS_BC_CURRENT_RECORD 28  //  28  BC相失流事件记录
#define TYPE_LOSS_ABC_CURRENT_RECORD    29  //  29  ABC相失流事件记录
#define TYPE_OVER_A_CURRENT_RECORD  30  //  30  A相过流事件记录
#define TYPE_OVER_B_CURRENT_RECORD  31  //  31  B相过流事件记录
#define TYPE_OVER_C_CURRENT_RECORD  32  //  32  C相过流事件记录
#define TYPE_CUT_A_CURRENT_RECORD   33  //  33  A相断流事件记录
#define TYPE_CUT_B_CURRENT_RECORD   34  //  34  B相断流事件记录
#define TYPE_CUT_C_CURRENT_RECORD   35  //  35  C相断流事件记录
#define TYPE_REVERSEPOWER_ALL_RECORD    36  //  36  总功率反向事件记录
#define TYPE_REVERSEPOWER_A_RECORD  37  //  37  A相功率反向事件记录
#define TYPE_REVERSEPOWER_B_RECORD  38  //  38  B相功率反向事件记录
#define TYPE_REVERSEPOWER_C_RECORD  39  //  39  C相功率反向事件记录
#define TYPE_POWEROVER_ALL_RECORD   40  //  40  总功率过载事件记录
#define TYPE_POWEROVER_A_RECORD 41  //  41  A相功率过载事件记录
#define TYPE_POWEROVER_B_RECORD 42  //  42  B相功率过载事件记录
#define TYPE_POWEROVER_C_RECORD 43  //  43  C相功率过载事件记录
#define TYPE_DEMAND_OVER_KW_F_RECORD    44  //  44  正向有功需量超限事件记录
#define TYPE_DEMAND_OVER_KW_R_RECORD    45  //  45  反向有功需量超限事件记录
#define TYPE_DEMAND_OVER_KVAR_Q1_RECORD 46  //  46  第1象限无功需量超限事件记录
#define TYPE_DEMAND_OVER_KVAR_Q2_RECORD 47  //  47  第2象限无功需量超限事件记录
#define TYPE_DEMAND_OVER_KVAR_Q3_RECORD 48  //  48  第3象限无功需量超限事件记录
#define TYPE_DEMAND_OVER_KVAR_Q4_RECORD 49  //  49  第4象限无功需量超限事件记录
#define TYPE_DEMAND_OVER_KVAR_C1_RECORD 50  //  50  无功组合1需量超限事件记录
#define TYPE_DEMAND_OVER_KVAR_C2_RECORD 51  //  51  无功组合2需量超限事件记录
#define TYPE_ORDER_VOLTAGE_RECORD   52  //  52  电压逆向序事件记录
#define TYPE_ORDER_CURRENT_RECORD   53  //  53  电流逆向序事件记录
#define TYPE_UNBALANCE_VOLTAGE_RECORD   54  //  54  电压不平衡事件记录
#define TYPE_UNBALANCE_CURRENT_RECORD   55  //  55  电流不平衡事件记录
#define TYPE_PROGRAM_METERCLR_RECORD    56  //  56  电表清零编程事件记录
#define TYPE_PROGRAM_DEMANDCLR_RECORD   57  //  57  需量清零编程事件记录
#define TYPE_PROGRAM_EVENTCLR_RECORD    58  //  58  事件清零编程事件记录
#define TYPE_PROGRAM_TIME_RECORD    59  //  59  校时编程事件记录
#define TYPE_PROGRAM_DAYTABLE_RECORD    60  //  60  时段表编程记录
#define TYPE_PROGRAM_SEASON_RECORD  61  //  61  时区表编程记录
#define TYPE_PROGRAM_RESTDAY_RECORD 62  //  62  周休日编程事件记录
#define TYPE_PROGRAM_HOLIDAY_RECORD 63  //  63  节假日编程事件记录
#define TYPE_PROGRAM_CHARACTER_ACTIVE_RECORD    64  //  64  有功组合方式特征字编程事件记录
#define TYPE_PROGRAM_CHARACTER_REACTIVE01_RECORD    65  //  65  无功组合方式1编程事件记录
#define TYPE_PROGRAM_CHARACTER_REACTIVE02_RECORD    66  //  66  无功组合方式2编程事件记录
#define TYPE_PROGRAM_CHARACTER_REACTIVE03_RECORD    67  //  67  无功组合方式3编程事件记录
#define TYPE_PROGRAM_CHARACTER_REACTIVE04_RECORD    68  //  68  无功组合方式4编程事件记录
#define TYPE_PROGRAM_BALANCE_DAY_RECORD 69  //  69  结算日编程事件记录
#define TYPE_DAYTABLE_MODULE_RECORD 70  //  70  远程设置时段事件数据记录
#define TYPE_FREEZE_EVERYTIME_RECORD    71  //  71  定时冻结数据
#define TYPE_FREEZE_INSTANT_RECORD  72  //  72  瞬时冻结数据
#define TYPE_FREEZE_EVERYZERO_RECORD    73  //  73  日零点冻结事件数据
#define TYPE_FREEZE_SEASONCHANGE_RECORD 74  //  74  2套时区表切换冻结数据
#define TYPE_FREEZE_DAYTABLECHANGE_RECORD   75  //  75  2套日时段表切换冻结数据
#define TYPE_FREEZE_STEPPRICE_TABLECHANGE_RECORD    76  //  76  2套阶梯切换冻结数据
#define TYPE_FREEZE_PERIODPRICE_TABLECHANGE_RECORD  77  //  77  2套费率电价切换冻结数据
#define TYPE_RELAY_OPEN_RECORD  78  //  78  拉闸事件记录
#define TYPE_RELAY_CLOSE_RECORD 79  //  79  合闸事件记录
#define TYPE_ERR_TIME_RECORD    80  //  80  时钟错误事件记录
#define TYPE_ERR_POWER_RECORD   81  //  81  电量错误事件记录
#define TYPE_OVERTOTALCOS_RECORD    82  //  82  总功率因数超限事件记录
#define TYPE_BUY_MONEY_RECORD   83  //  83  购电金额记录
#define TYPE_BUY_KWH_RECORD 84  //  84  购电电量记录
#define TYPE_BROADCASTTIME_RECORD   85  //  85  广播校时事件记录
#define TYPE_FREEZE_HOURTIME_RECORD 86  //  86  整点半点电量冻结数据记录
#define TYPE_PROGRAM_OPEN_RECORD    87  //  87  编程盖开启事件记录
#define TYPE_COVER_OPEN_RECORD  88  //  88  表盖开启事件记录
#define TYPE_TERMINAL_OPEN_RECORD   89  //  89  端钮盖开启事件记录
#define TYPE_LOSS_ALL_VOLTAGE_RECORD    90  //  90  全失压事件记录
#define TYPE_ACPOWER_LOSS_RECORD    91  //  91  辅助电源掉电事件记录
#define TYPE_POWER_DOWN_RECORD  92  //  92  系统电源掉电事件记录
#define TYPE_PROGRAM_RECORD 93  //  93  编程事件记录
#define TYPE_MIN_POWER_RECORD   94  //  94  每分钟电量记录

AP_TWOTABLE_EXT ulong SetTwoTableNextPoint(uchar ucBlockName);

AP_TWOTABLE_EXT ulong GetTwoTableAddrFromBlock(uchar ucBlockName,u16 uiBloakStart,ulong ulAddrChange);

//AP_TWOTABLE_EXT void JudgeToEraseHistoryData(uchar ucBlockName);
//AP_TWOTABLE_EXT ulong GetTwoTableAddrFromAddr(ulong ulFromAddr);













#endif
































































