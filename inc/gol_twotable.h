


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

#define TYPE_HISTROY_POWER_RECORD 0 // 0    ��ʷ�������ݼ�¼
#define TYPE_HISTROY_DEMAND_RECORD 1    // 1    ��ʷ�������ݼ�¼
#define TYPE_HISTROY_USEPOWER_RECORD 2  // 2    ��ʷ�õ������ݼ�¼
#define TYPE_MONITOR_VOLTAGE_ALL_RECORD 3   // 3    ��ѹ�ϸ���ͳ�����ݼ�¼
#define TYPE_MONITOR_VOLTAGE_A_RECORD 4 // 4    A���ѹ�ϸ���ͳ�����ݼ�¼
#define TYPE_MONITOR_VOLTAGE_B_RECORD 5 // 5    B���ѹ�ϸ���ͳ�����ݼ�¼
#define TYPE_MONITOR_VOLTAGE_C_RECORD 6 // 6    C���ѹ�ϸ���ͳ�����ݼ�¼
#define TYPE_LOSS_A_VOLTAGE_RECORD  7   //  7   A��ʧѹ�¼���¼
#define TYPE_LOSS_B_VOLTAGE_RECORD  8   //  8   B��ʧѹ�¼���¼
#define TYPE_LOSS_C_VOLTAGE_RECORD  9   //  9   C��ʧѹ�¼���¼
#define TYPE_LOSS_AB_VOLTAGE_RECORD 10  //  10  AB��ʧѹ�¼���¼
#define TYPE_LOSS_AC_VOLTAGE_RECORD 11  //  11  AC��ʧѹ�¼���¼
#define TYPE_LOSS_BC_VOLTAGE_RECORD 12  //  12  BC��ʧѹ�¼���¼
#define TYPE_LOSS_ABC_VOLTAGE_RECORD    13  //  13  ABC��ʧѹ�¼���¼
#define TYPE_DOWN_A_VOLTAGE_RECORD  14  //  14  A��Ƿѹ�¼���¼
#define TYPE_DOWN_B_VOLTAGE_RECORD  15  //  15  B��Ƿѹ�¼���¼
#define TYPE_DOWN_C_VOLTAGE_RECORD  16  //  16  C��Ƿѹ�¼���¼
#define TYPE_OVER_A_VOLTAGE_RECORD  17  //  17  A���ѹ�¼���¼
#define TYPE_OVER_B_VOLTAGE_RECORD  18  //  18  B���ѹ�¼���¼
#define TYPE_OVER_C_VOLTAGE_RECORD  19  //  19  C���ѹ�¼���¼
#define TYPE_CUT_A_VOLTAGE_RECORD   20  //  20  A������¼���¼
#define TYPE_CUT_B_VOLTAGE_RECORD   21  //  21  B������¼���¼
#define TYPE_CUT_C_VOLTAGE_RECORD   22  //  22  C������¼���¼
#define TYPE_LOSS_A_CURRENT_RECORD  23  //  23  A��ʧ���¼���¼
#define TYPE_LOSS_B_CURRENT_RECORD  24  //  24  B��ʧ���¼���¼
#define TYPE_LOSS_C_CURRENT_RECORD  25  //  25  C��ʧ���¼���¼
#define TYPE_LOSS_AB_CURRENT_RECORD 26  //  26  AB��ʧ���¼���¼
#define TYPE_LOSS_AC_CURRENT_RECORD 27  //  27  AC��ʧ���¼���¼
#define TYPE_LOSS_BC_CURRENT_RECORD 28  //  28  BC��ʧ���¼���¼
#define TYPE_LOSS_ABC_CURRENT_RECORD    29  //  29  ABC��ʧ���¼���¼
#define TYPE_OVER_A_CURRENT_RECORD  30  //  30  A������¼���¼
#define TYPE_OVER_B_CURRENT_RECORD  31  //  31  B������¼���¼
#define TYPE_OVER_C_CURRENT_RECORD  32  //  32  C������¼���¼
#define TYPE_CUT_A_CURRENT_RECORD   33  //  33  A������¼���¼
#define TYPE_CUT_B_CURRENT_RECORD   34  //  34  B������¼���¼
#define TYPE_CUT_C_CURRENT_RECORD   35  //  35  C������¼���¼
#define TYPE_REVERSEPOWER_ALL_RECORD    36  //  36  �ܹ��ʷ����¼���¼
#define TYPE_REVERSEPOWER_A_RECORD  37  //  37  A�๦�ʷ����¼���¼
#define TYPE_REVERSEPOWER_B_RECORD  38  //  38  B�๦�ʷ����¼���¼
#define TYPE_REVERSEPOWER_C_RECORD  39  //  39  C�๦�ʷ����¼���¼
#define TYPE_POWEROVER_ALL_RECORD   40  //  40  �ܹ��ʹ����¼���¼
#define TYPE_POWEROVER_A_RECORD 41  //  41  A�๦�ʹ����¼���¼
#define TYPE_POWEROVER_B_RECORD 42  //  42  B�๦�ʹ����¼���¼
#define TYPE_POWEROVER_C_RECORD 43  //  43  C�๦�ʹ����¼���¼
#define TYPE_DEMAND_OVER_KW_F_RECORD    44  //  44  �����й����������¼���¼
#define TYPE_DEMAND_OVER_KW_R_RECORD    45  //  45  �����й����������¼���¼
#define TYPE_DEMAND_OVER_KVAR_Q1_RECORD 46  //  46  ��1�����޹����������¼���¼
#define TYPE_DEMAND_OVER_KVAR_Q2_RECORD 47  //  47  ��2�����޹����������¼���¼
#define TYPE_DEMAND_OVER_KVAR_Q3_RECORD 48  //  48  ��3�����޹����������¼���¼
#define TYPE_DEMAND_OVER_KVAR_Q4_RECORD 49  //  49  ��4�����޹����������¼���¼
#define TYPE_DEMAND_OVER_KVAR_C1_RECORD 50  //  50  �޹����1���������¼���¼
#define TYPE_DEMAND_OVER_KVAR_C2_RECORD 51  //  51  �޹����2���������¼���¼
#define TYPE_ORDER_VOLTAGE_RECORD   52  //  52  ��ѹ�������¼���¼
#define TYPE_ORDER_CURRENT_RECORD   53  //  53  �����������¼���¼
#define TYPE_UNBALANCE_VOLTAGE_RECORD   54  //  54  ��ѹ��ƽ���¼���¼
#define TYPE_UNBALANCE_CURRENT_RECORD   55  //  55  ������ƽ���¼���¼
#define TYPE_PROGRAM_METERCLR_RECORD    56  //  56  ����������¼���¼
#define TYPE_PROGRAM_DEMANDCLR_RECORD   57  //  57  �����������¼���¼
#define TYPE_PROGRAM_EVENTCLR_RECORD    58  //  58  �¼��������¼���¼
#define TYPE_PROGRAM_TIME_RECORD    59  //  59  Уʱ����¼���¼
#define TYPE_PROGRAM_DAYTABLE_RECORD    60  //  60  ʱ�α��̼�¼
#define TYPE_PROGRAM_SEASON_RECORD  61  //  61  ʱ�����̼�¼
#define TYPE_PROGRAM_RESTDAY_RECORD 62  //  62  �����ձ���¼���¼
#define TYPE_PROGRAM_HOLIDAY_RECORD 63  //  63  �ڼ��ձ���¼���¼
#define TYPE_PROGRAM_CHARACTER_ACTIVE_RECORD    64  //  64  �й���Ϸ�ʽ�����ֱ���¼���¼
#define TYPE_PROGRAM_CHARACTER_REACTIVE01_RECORD    65  //  65  �޹���Ϸ�ʽ1����¼���¼
#define TYPE_PROGRAM_CHARACTER_REACTIVE02_RECORD    66  //  66  �޹���Ϸ�ʽ2����¼���¼
#define TYPE_PROGRAM_CHARACTER_REACTIVE03_RECORD    67  //  67  �޹���Ϸ�ʽ3����¼���¼
#define TYPE_PROGRAM_CHARACTER_REACTIVE04_RECORD    68  //  68  �޹���Ϸ�ʽ4����¼���¼
#define TYPE_PROGRAM_BALANCE_DAY_RECORD 69  //  69  �����ձ���¼���¼
#define TYPE_DAYTABLE_MODULE_RECORD 70  //  70  Զ������ʱ���¼����ݼ�¼
#define TYPE_FREEZE_EVERYTIME_RECORD    71  //  71  ��ʱ��������
#define TYPE_FREEZE_INSTANT_RECORD  72  //  72  ˲ʱ��������
#define TYPE_FREEZE_EVERYZERO_RECORD    73  //  73  ����㶳���¼�����
#define TYPE_FREEZE_SEASONCHANGE_RECORD 74  //  74  2��ʱ�����л���������
#define TYPE_FREEZE_DAYTABLECHANGE_RECORD   75  //  75  2����ʱ�α��л���������
#define TYPE_FREEZE_STEPPRICE_TABLECHANGE_RECORD    76  //  76  2�׽����л���������
#define TYPE_FREEZE_PERIODPRICE_TABLECHANGE_RECORD  77  //  77  2�׷��ʵ���л���������
#define TYPE_RELAY_OPEN_RECORD  78  //  78  ��բ�¼���¼
#define TYPE_RELAY_CLOSE_RECORD 79  //  79  ��բ�¼���¼
#define TYPE_ERR_TIME_RECORD    80  //  80  ʱ�Ӵ����¼���¼
#define TYPE_ERR_POWER_RECORD   81  //  81  ���������¼���¼
#define TYPE_OVERTOTALCOS_RECORD    82  //  82  �ܹ������������¼���¼
#define TYPE_BUY_MONEY_RECORD   83  //  83  �������¼
#define TYPE_BUY_KWH_RECORD 84  //  84  ���������¼
#define TYPE_BROADCASTTIME_RECORD   85  //  85  �㲥Уʱ�¼���¼
#define TYPE_FREEZE_HOURTIME_RECORD 86  //  86  ����������������ݼ�¼
#define TYPE_PROGRAM_OPEN_RECORD    87  //  87  ��̸ǿ����¼���¼
#define TYPE_COVER_OPEN_RECORD  88  //  88  ��ǿ����¼���¼
#define TYPE_TERMINAL_OPEN_RECORD   89  //  89  ��ť�ǿ����¼���¼
#define TYPE_LOSS_ALL_VOLTAGE_RECORD    90  //  90  ȫʧѹ�¼���¼
#define TYPE_ACPOWER_LOSS_RECORD    91  //  91  ������Դ�����¼���¼
#define TYPE_POWER_DOWN_RECORD  92  //  92  ϵͳ��Դ�����¼���¼
#define TYPE_PROGRAM_RECORD 93  //  93  ����¼���¼
#define TYPE_MIN_POWER_RECORD   94  //  94  ÿ���ӵ�����¼

AP_TWOTABLE_EXT ulong SetTwoTableNextPoint(uchar ucBlockName);

AP_TWOTABLE_EXT ulong GetTwoTableAddrFromBlock(uchar ucBlockName,u16 uiBloakStart,ulong ulAddrChange);

//AP_TWOTABLE_EXT void JudgeToEraseHistoryData(uchar ucBlockName);
//AP_TWOTABLE_EXT ulong GetTwoTableAddrFromAddr(ulong ulFromAddr);













#endif
































































