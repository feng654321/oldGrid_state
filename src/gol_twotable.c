#define AP_TWOTABLE_GLOBALS
#include "common.h"


ulong SetTwoTableNextPoint2Byte(uchar ucBlockName);
ulong GetTwoTableAddrFromBlock2Byte(uchar ucBlockName,u16 uiBloakStart,ulong ulAddrChange);
// ��Ϊ֮ǰ������㶳����ڶ��α�������ã�û�����⡣���ڽ�����㶳�����Ƶ���̸�
// �����¼�֮��Ŀǰ�Ĳ���α�ʽ�ᵼ�µ�ַ��ͻ�� �ʱ�̸ǿ����¼���¼�ݲ���ʹ�á�
const ST_TWOTAB_PARAM stTwoTable[GAL_TWOTABLE_LEN]=
{
    {TYPE_HISTROY_POWER_RECORD, 36 ,FL1_LAST_POWER_RECORD_START , 1024 }, // 0 ��ʷ�������ݼ�¼
    {TYPE_HISTROY_DEMAND_RECORD, 36 ,FL1_LAST_DEMAND_RECORD_START , 2048 }, // 1 ��ʷ�������ݼ�¼
    {TYPE_HISTROY_USEPOWER_RECORD, 36 , FL1_LAST_USEPOWER_RECORD_START , 1024 }, // 2 ��ʷ�õ������ݼ�¼
    {TYPE_MONITOR_VOLTAGE_ALL_RECORD, 32 , FL1_LAST_MONITOR_VOLTAGE_ALL_RECORD_START , 256 }, // 3 ��ѹ�ϸ���ͳ�����ݼ�¼
    {TYPE_MONITOR_VOLTAGE_A_RECORD, 32 , FL1_LAST_MONITOR_VOLTAGE_A_RECORD_START , 256 }, // 4 A���ѹ�ϸ���ͳ�����ݼ�¼
    {TYPE_MONITOR_VOLTAGE_B_RECORD, 32 , FL1_LAST_MONITOR_VOLTAGE_B_RECORD_START , 256 }, // 5 B���ѹ�ϸ���ͳ�����ݼ�¼
    {TYPE_MONITOR_VOLTAGE_C_RECORD, 32 , FL1_LAST_MONITOR_VOLTAGE_C_RECORD_START , 256 }, // 6 C���ѹ�ϸ���ͳ�����ݼ�¼
    {TYPE_LOSS_A_VOLTAGE_RECORD, 32 ,  FL1_LAST_LOSS_A_VOLTAGE_RECORD_START , 256 }, // 7 A��ʧѹ�¼���¼
    {TYPE_LOSS_B_VOLTAGE_RECORD, 32 , FL1_LAST_LOSS_B_VOLTAGE_RECORD_START , 256 }, // 8 B��ʧѹ�¼���¼
    {TYPE_LOSS_C_VOLTAGE_RECORD, 32 , FL1_LAST_LOSS_C_VOLTAGE_RECORD_START , 256 }, // 9 C��ʧѹ�¼���¼
    {TYPE_LOSS_AB_VOLTAGE_RECORD, 32 , FL1_LAST_LOSS_AB_VOLTAGE_RECORD_START , 256 }, // 10 AB��ʧѹ�¼���¼
    {TYPE_LOSS_AC_VOLTAGE_RECORD, 32 , FL1_LAST_LOSS_AC_VOLTAGE_RECORD_START , 256 }, // 11 AC��ʧѹ�¼���¼
    {TYPE_LOSS_BC_VOLTAGE_RECORD, 32 , FL1_LAST_LOSS_BC_VOLTAGE_RECORD_START , 256 }, // 12 BC��ʧѹ�¼���¼
    {TYPE_LOSS_ABC_VOLTAGE_RECORD, 32 , FL1_LAST_LOSS_ABC_VOLTAGE_RECORD_START , 256 }, // 13 ABC��ʧѹ�¼���¼
    {TYPE_DOWN_A_VOLTAGE_RECORD, 32 ,  FL1_LAST_DOWN_A_VOLTAGE_RECORD_START , 256 }, // 14 A��Ƿѹ�¼���¼
    {TYPE_DOWN_B_VOLTAGE_RECORD, 32 , FL1_LAST_DOWN_B_VOLTAGE_RECORD_START , 256 }, // 15 B��Ƿѹ�¼���¼
    {TYPE_DOWN_C_VOLTAGE_RECORD, 32 , FL1_LAST_DOWN_C_VOLTAGE_RECORD_START , 256 }, // 16 C��Ƿѹ�¼���¼
    {TYPE_OVER_A_VOLTAGE_RECORD, 32 , FL1_LAST_OVER_A_VOLTAGE_RECORD_START , 256 }, // 17 A���ѹ�¼���¼
    {TYPE_OVER_B_VOLTAGE_RECORD, 32 ,  FL1_LAST_OVER_B_VOLTAGE_RECORD_START , 256 }, // 18 B���ѹ�¼���¼
    {TYPE_OVER_C_VOLTAGE_RECORD, 32 ,  FL1_LAST_OVER_C_VOLTAGE_RECORD_START , 256 }, // 19C���ѹ�¼���¼
    {TYPE_CUT_A_VOLTAGE_RECORD, 32 , FL1_LAST_CUT_A_VOLTAGE_RECORD_START , 256 }, // 20 A������¼���¼
    {TYPE_CUT_B_VOLTAGE_RECORD, 32 , FL1_LAST_CUT_B_VOLTAGE_RECORD_START , 256 }, // 21 B������¼���¼
    {TYPE_CUT_C_VOLTAGE_RECORD, 32 , FL1_LAST_CUT_C_VOLTAGE_RECORD_START , 256 }, // 22 C������¼���¼
    {TYPE_LOSS_A_CURRENT_RECORD, 32 , FL1_LAST_LOSS_A_CURRENT_RECORD_START , 256 }, // 23 A��ʧ���¼���¼
    {TYPE_LOSS_B_CURRENT_RECORD, 32 , FL1_LAST_LOSS_B_CURRENT_RECORD_START , 256 }, // 24 B��ʧ���¼���¼
    {TYPE_LOSS_C_CURRENT_RECORD, 32 , FL1_LAST_LOSS_C_CURRENT_RECORD_START , 256 }, // 25 C��ʧ���¼���¼
    {TYPE_LOSS_AB_CURRENT_RECORD, 32 , FL1_LAST_LOSS_AB_CURRENT_RECORD_START , 256 }, // 26 AB��ʧ���¼���¼
    {TYPE_LOSS_AC_CURRENT_RECORD, 32 , FL1_LAST_LOSS_AC_CURRENT_RECORD_START , 256 }, // 27 AC��ʧ���¼���¼
    {TYPE_LOSS_BC_CURRENT_RECORD, 32 , FL1_LAST_LOSS_BC_CURRENT_RECORD_START , 256 }, // 28 BC��ʧ���¼���¼
    {TYPE_LOSS_ABC_CURRENT_RECORD, 32 , FL1_LAST_LOSS_ABC_CURRENT_RECORD_START , 256 }, // 29 ABC��ʧ���¼���¼
    {TYPE_OVER_A_CURRENT_RECORD, 32 ,  FL1_LAST_OVER_A_CURRENT_RECORD_START , 256 }, // 30 A������¼���¼
    {TYPE_OVER_B_CURRENT_RECORD, 32 , FL1_LAST_OVER_B_CURRENT_RECORD_START , 256 }, // 31 B������¼���¼
    {TYPE_OVER_C_CURRENT_RECORD, 32 , FL1_LAST_OVER_C_CURRENT_RECORD_START , 256 }, // 32 C������¼���¼
    {TYPE_CUT_A_CURRENT_RECORD, 32, FL1_LAST_CUT_A_CURRENT_RECORD_START , 256 }, // 33 A������¼���¼
    {TYPE_CUT_B_CURRENT_RECORD, 32 , FL1_LAST_CUT_B_CURRENT_RECORD_START , 256 }, // 34 B������¼���¼
    {TYPE_CUT_C_CURRENT_RECORD, 32 , FL1_LAST_CUT_C_CURRENT_RECORD_START , 256 }, // 35 C������¼���¼
    {TYPE_REVERSEPOWER_ALL_RECORD, 32 , FL1_LAST_REVERSEPOWER_ALL_RECORD_START , 256 }, // 36�ܹ��ʷ����¼���¼
    {TYPE_REVERSEPOWER_A_RECORD, 32 , FL1_LAST_REVERSEPOWER_A_RECORD_START , 256 }, // 37 A�๦�ʷ����¼���¼
    {TYPE_REVERSEPOWER_B_RECORD, 32 , FL1_LAST_REVERSEPOWER_B_RECORD_START , 256 }, // 38 B�๦�ʷ����¼���¼
    {TYPE_REVERSEPOWER_C_RECORD, 32 , FL1_LAST_REVERSEPOWER_C_RECORD_START , 256 }, // 39 C�๦�ʷ����¼���¼
    {TYPE_POWEROVER_ALL_RECORD, 32 , FL1_LAST_POWEROVER_ALL_RECORD_START , 256 }, // 40 �ܹ��ʹ����¼���¼
    {TYPE_POWEROVER_A_RECORD, 32 , FL1_LAST_POWEROVER_A_RECORD_START , 256 }, // 41 A�๦�ʹ����¼���¼
    {TYPE_POWEROVER_B_RECORD, 32 , FL1_LAST_POWEROVER_B_RECORD_START , 256 }, // 42 B�๦�ʹ����¼���¼
    {TYPE_POWEROVER_C_RECORD, 32, FL1_LAST_POWEROVER_C_RECORD_START , 256 }, // 43 C�๦�ʹ����¼���¼
    {TYPE_DEMAND_OVER_KW_F_RECORD, 32 , FL1_LAST_DEMAND_OVER_KW_F_RECORD_START , 256 }, // 44 �����й����������¼���¼
    {TYPE_DEMAND_OVER_KW_R_RECORD, 32 , FL1_LAST_DEMAND_OVER_KW_R_RECORD_START , 256 }, // 45 �����й����������¼���¼
    {TYPE_DEMAND_OVER_KVAR_Q1_RECORD, 32 , FL1_LAST_DEMAND_OVER_KVAR_Q1_RECORD_START , 256 }, // 46 ��1�����޹����������¼���¼
    {TYPE_DEMAND_OVER_KVAR_Q2_RECORD, 32 , FL1_LAST_DEMAND_OVER_KVAR_Q2_RECORD_START , 256 }, // 47 ��2�����޹����������¼���¼
    {TYPE_DEMAND_OVER_KVAR_Q3_RECORD, 32 , FL1_LAST_DEMAND_OVER_KVAR_Q3_RECORD_START , 256 }, // 48 ��3�����޹����������¼���¼
    {TYPE_DEMAND_OVER_KVAR_Q4_RECORD, 32 , FL1_LAST_DEMAND_OVER_KVAR_Q4_RECORD_START , 256 }, // 49 ��4�����޹����������¼���¼
    {TYPE_DEMAND_OVER_KVAR_C1_RECORD, 32 , FL1_LAST_DEMAND_OVER_KVAR_C1_RECORD_START , 256 }, // 50 �޹����1���������¼���¼
    {TYPE_DEMAND_OVER_KVAR_C2_RECORD, 32 , FL1_LAST_DEMAND_OVER_KVAR_C2_RECORD_START , 256 }, // 51 �޹����2���������¼���¼
    {TYPE_ORDER_VOLTAGE_RECORD, 32 , FL1_LAST_ORDER_VOLTAGE_RECORD_START , 256 }, // 52 ��ѹ�������¼���¼
    {TYPE_ORDER_CURRENT_RECORD, 32 , FL1_LAST_ORDER_CURRENT_RECORD_START , 256 }, // 53 �����������¼���¼
    {TYPE_UNBALANCE_VOLTAGE_RECORD, 32 , FL1_LAST_UNBALANCE_VOLTAGE_RECORD_START , 256 }, // 54 ��ѹ��ƽ���¼���¼
    {TYPE_UNBALANCE_CURRENT_RECORD, 32 , FL1_LAST_UNBALANCE_CURRENT_RECORD_START , 256 }, // 55 ������ƽ���¼���¼
    {TYPE_PROGRAM_METERCLR_RECORD, 64 , FL1_LAST_PROGRAM_POWERCLR_RECORD_START , 1024 }, // 56 ����������¼���¼
    {TYPE_PROGRAM_DEMANDCLR_RECORD, 40 , FL1_LAST_PROGRAM_DEMANDCLR_RECORD_START , 2048 }, // 57 �����������¼���¼
    {TYPE_PROGRAM_EVENTCLR_RECORD, 128 , FL1_LAST_PROGRAM_EVENTCLR_RECORD_START , 64 }, // 58 �¼��������¼���¼
    {TYPE_PROGRAM_TIME_RECORD, 128 , FL1_LAST_PROGRAM_TIME_RECORD_START , 64 }, // 59 Уʱ����¼���¼
    {TYPE_PROGRAM_DAYTABLE_RECORD, 32 , FL1_LAST_PROGRAM_DAYTABLE_RECORD_START , 1024 }, // 60 ʱ�α��̼�¼
    {TYPE_PROGRAM_SEASON_RECORD, 64 , FL1_LAST_PROGRAM_SEASON_RECORD_START , 128 }, // 61 ʱ�����̼�¼
    {TYPE_PROGRAM_RESTDAY_RECORD, 64 , FL1_LAST_PROGRAM_RESTDAY_RECORD_START , 128 }, // 62 �����ձ���¼���¼
    {TYPE_PROGRAM_HOLIDAY_RECORD, 16 , FL1_LAST_PROGRAM_HOLIDAY_RECORD_START , 2048 }, // 63 �ڼ��ձ���¼���¼
    {TYPE_PROGRAM_CHARACTER_ACTIVE_RECORD, 64 , FL1_LAST_PROGRAM_CHARACTER_ACTIVE_RECORD_START , 128 }, // 64 �й���Ϸ�ʽ�����ֱ���¼���¼
    {TYPE_PROGRAM_CHARACTER_REACTIVE01_RECORD, 64 , FL1_LAST_PROGRAM_CHARACTER_REACTIVE01_RECORD_START , 128 }, // 65�޹���Ϸ�ʽ1����¼���¼
    {TYPE_PROGRAM_CHARACTER_REACTIVE02_RECORD, 64 , FL1_LAST_PROGRAM_CHARACTER_REACTIVE02_RECORD_START , 128 }, // 66 �޹���Ϸ�ʽ2����¼���¼
    {TYPE_PROGRAM_CHARACTER_REACTIVE03_RECORD, 64 , FL1_LAST_PROGRAM_CHARACTER_REACTIVE03_RECORD_START , 128 }, // 67 �޹���Ϸ�ʽ3����¼���¼
    {TYPE_PROGRAM_CHARACTER_REACTIVE04_RECORD, 64 , FL1_LAST_PROGRAM_CHARACTER_REACTIVE04_RECORD_START , 128 }, // 68 �޹���Ϸ�ʽ4����¼���¼
    {TYPE_PROGRAM_BALANCE_DAY_RECORD, 128 , FL1_LAST_PROGRAM_BALANCE_DAY_RECORD_START , 128 }, // 69 �����ձ���¼���¼
    {TYPE_DAYTABLE_MODULE_RECORD, 64 , FL1_LAST_PROGRAM_DAYTABLE_MODULE_RECORD_START , 128 }, // 70 Զ������ʱ���¼����ݼ�¼
    {TYPE_FREEZE_EVERYTIME_RECORD, 128 , FL1_LAST_FREEZE_EVERYTIME_RECORD_START , 1024 }, // 71 ��ʱ��������
    {TYPE_FREEZE_INSTANT_RECORD, 64 , FL1_LAST_FREEZE_INSTANT_RECORD_START , 1024 }, // 72 ˲ʱ��������
    {TYPE_FREEZE_EVERYZERO_RECORD, 64 , FL1_LAST_FREEZE_EVERYZERO_RECORD_START , 1024 }, // 73 ����㶳���¼�����
    {TYPE_FREEZE_SEASONCHANGE_RECORD, 16 , FL1_LAST_FREEZE_SEASONCHANGE_RECORD_START , 1024 }, // 74 2��ʱ�����л���������
    {TYPE_FREEZE_DAYTABLECHANGE_RECORD, 16 , FL1_LAST_FREEZE_DAYTABLECHANGE_RECORD_START , 1024 }, // 75 2����ʱ�α��л���������
    {TYPE_FREEZE_STEPPRICE_TABLECHANGE_RECORD, 16 , FL1_LAST_FREEZE_STEPPRICE_TABLECHANGE_RECORD_START , 1024 }, // 76 2�׽����л���������
    {TYPE_FREEZE_PERIODPRICE_TABLECHANGE_RECORD, 16 , FL1_LAST_FREEZE_PERIODPRICE_TABLECHANGE_RECORD_START , 1024 }, // 77 2�׷��ʵ���л���������
    {TYPE_RELAY_OPEN_RECORD, 64 , FL1_LAST_RELAY_OPEN_RECORD_START , 128 }, // 78 ��բ�¼���¼
    {TYPE_RELAY_CLOSE_RECORD, 64 , FL1_LAST_RELAY_CLOSE_RECORD_START , 128 }, // 79 ��բ�¼���¼
    {TYPE_ERR_TIME_RECORD, 128 , FL1_LAST_ERR_TIME_RECORD_START , 64 }, // 80 ʱ�Ӵ����¼���¼
    {TYPE_ERR_POWER_RECORD, 100 , FL1_LAST_ERR_POWER_RECORD_START , 1024 }, // 81 ���������¼���¼
    {TYPE_OVERTOTALCOS_RECORD, 32 , FL1_LAST_OVERTOTALCOS_RECORD_START , 256 }, // 82 �ܹ������������¼���¼
    {TYPE_BUY_MONEY_RECORD, 64 , FL1_LAST_BUY_MONEY_RECORD_START , 128 }, // 83�������¼
    {TYPE_BUY_KWH_RECORD, 64 , FL1_LAST_BUY_KWH_RECORD_START , 128 }, // 84 ���������¼
    {TYPE_BROADCASTTIME_RECORD,128,FL1_LAST_BROADCASTTIME_RECORD_START,64}, // 85 �㲥Уʱ
    {TYPE_FREEZE_HOURTIME_RECORD, 512 , FL1_LAST_FREEZE_HOURTIME_RECORD_START , 16 },// 86 ����������������ݼ�¼   
    {TYPE_PROGRAM_OPEN_RECORD, 32 , FL1_LAST_PROGRAM_OPEN_RECORD_START , 256 }, // 87 ��̸ǿ����¼���¼
    
    {TYPE_COVER_OPEN_RECORD, 10 , EPL_LAST_COVER_OPEN_RECORD_START , 72 }, // 88 ��ǿ����¼���¼
    {TYPE_TERMINAL_OPEN_RECORD, 10 , EPL_LAST_TERMINAL_OPEN_RECORD_START , 72 }, // 89 ��ť�ǿ����¼���¼
#if (CONFIG_METER_AREA_MODE_SOUTHGRID==CONFIG_METER_AREA_MODE)
    {TYPE_LOSS_ALL_VOLTAGE_RECORD, 10 , EPL_LAST_LOSS_ALL_VOLTAGE_RECORD_START , 131 }, // 90 ȫʧѹ�¼���¼
#else
    {TYPE_LOSS_ALL_VOLTAGE_RECORD, 10 , EPL_LAST_LOSS_ALL_VOLTAGE_RECORD_START , 16 }, // 90 ȫʧѹ�¼���¼
#endif
    {TYPE_ACPOWER_LOSS_RECORD, 10 , EPL_LAST_ACPOWER_LOSS_RECORD_START , 16 }, // 91������Դ�����¼���¼
    {TYPE_POWER_DOWN_RECORD, 10 , EPL_LAST_POWER_DOWN_RECORD_START , 16 }, // 92 ϵͳ��Դ�����¼���¼
    {TYPE_PROGRAM_RECORD, 10 , EPL_LAST_PROGRAM_RECORD_START , 64 }, // 93 ����¼���¼

    {TYPE_MIN_POWER_RECORD,  56, FL1_LAST_PER_MIN_POWER_START,   1024},    // 94 ÿ���ӵ�������

};


//����¼�ָ������⴦��
ulong SetTwoTableNextPointProgEvent(uchar ucBlockName);
ulong SetTwoTableNextPointProgEvent(uchar ucBlockName)
{
    uchar ucPoint[2];   
    u16 uiPoint;
    
        if((ucBlockName == TYPE_COVER_OPEN_RECORD)||(ucBlockName == TYPE_TERMINAL_OPEN_RECORD)||(ucBlockName == TYPE_LOSS_ALL_VOLTAGE_RECORD)
            ||(ucBlockName == TYPE_ACPOWER_LOSS_RECORD)||(ucBlockName == TYPE_POWER_DOWN_RECORD)||(ucBlockName == TYPE_PROGRAM_RECORD)
           )    //����¼����⴦��������
    {
        if(1==ReadDataDirect(EPL_TWOTABLE_ADDR_START+ucBlockName*2,2,&ucPoint[0]))
        {
            uiPoint=ucPoint[0];                                                             // ��ȡ��ָ��
            uiPoint=uiPoint+stTwoTable[ucBlockName].ucMaxBlockNum-1;
            uiPoint=(uiPoint)% stTwoTable[ucBlockName].ucMaxBlockNum;
            if(ucPoint[1]<stTwoTable[ucBlockName].ucMaxBlockNum)                            // ���´���
            {
                ucPoint[1]++;
            }
            else
            {
                ucPoint[1]=stTwoTable[ucBlockName].ucMaxBlockNum;
            }
            ucPoint[0]=uiPoint;
                        
            
            /*----------����ָ��ʹ���--------------*/
            if(1==WriteDataDirect(&ucPoint[0],EPL_TWOTABLE_ADDR_START+ucBlockName*2, 2))
            {
                return(ucPoint[0] * stTwoTable[ucBlockName].ulBlockLen +stTwoTable[ucBlockName].ulBlockStartAddr);
            }

        }
    }
    return GAL_GETTWOTABLE_ADDRERR;
}


ulong SetTwoTableNextPoint2Byte(uchar ucBlockName)
{   
    u16 uiPoint[2];
    u16 uiTempPoint;
    u16 uiTemp;
    ulong ulTempAddr;
    
    if(TYPE_FREEZE_HOURTIME_RECORD==ucBlockName)
    {
        if(1==ReadDataDirect(EPL_TWOTABLE_ADDR_START+ucBlockName*2,4,(uchar *)&uiPoint[0]))
        {
            uiTempPoint=uiPoint[0]+stTwoTable[ucBlockName].ucMaxBlockNum-1;
            uiTempPoint=(uiTempPoint)% stTwoTable[ucBlockName].ucMaxBlockNum;
            uiPoint[1]++;
            if(uiPoint[1]>stTwoTable[ucBlockName].ucMaxBlockNum)
            {
                uiPoint[1]=stTwoTable[ucBlockName].ucMaxBlockNum;
            }
            uiPoint[0] = uiTempPoint;
            
            /*----------�жϲ�����һblock--------------*/
            uiTemp = CON_RECORD_FLASH_1BLOCK_BYTE/stTwoTable[ucBlockName].ulBlockLen;
            
            if((uiPoint[0]%uiTemp) == 1)                                                   
            {
                uiTempPoint = (uiTempPoint+stTwoTable[ucBlockName].ucMaxBlockNum - 2)%stTwoTable[ucBlockName].ucMaxBlockNum;
                ulTempAddr = uiTempPoint* stTwoTable[ucBlockName].ulBlockLen +stTwoTable[ucBlockName].ulBlockStartAddr;
                //WaitClrFlash(ulTempAddr);
            }
            else if((uiPoint[0]%uiTemp) == 0)                                              // ��ʷ���ݼ���һ��block��flash�ռ�
            {
                uiTempPoint = (uiTempPoint+stTwoTable[ucBlockName].ucMaxBlockNum - 1)%stTwoTable[ucBlockName].ucMaxBlockNum;
                ulTempAddr = uiTempPoint* stTwoTable[ucBlockName].ulBlockLen +stTwoTable[ucBlockName].ulBlockStartAddr;
                //WaitClrFlash(ulTempAddr);
                if(uiPoint[1] >= (stTwoTable[ucBlockName].ucMaxBlockNum/2)) // ���������洢�ռ䣬ɾ��һ��block�󣬼�ȥ��Ӧ������
                {
                    uiPoint[1] = stTwoTable[ucBlockName].ucMaxBlockNum/2;
                }
            }
            
            /*----------����ָ��ʹ���--------------*/  
            if(1==WriteDataDirect((uchar *)&uiPoint[0],EPL_TWOTABLE_ADDR_START+ucBlockName*2, 4))
            {
                return(uiPoint[0] * stTwoTable[ucBlockName].ulBlockLen +stTwoTable[ucBlockName].ulBlockStartAddr);
            }
        }
    }
    return GAL_GETTWOTABLE_ADDRERR;
    
}
ulong GetTwoTableAddrFromBlock2Byte(uchar ucBlockName,u16 uiBloakStart,ulong ulAddrChange)
{
    
    ulong ulTemp;
    u16 uiPoint[2];
    if(TYPE_FREEZE_HOURTIME_RECORD==ucBlockName)
    {
        if(1==ReadDataDirect(EPL_TWOTABLE_ADDR_START+ucBlockName*2,4,(uchar *)&uiPoint[0]))
        {
            if(uiBloakStart>=uiPoint[1])
            {
                return GAL_GETTWOTABLE_POINTRERR;
            }
            ulTemp=(uiPoint[0]+uiBloakStart)% stTwoTable[ucBlockName].ucMaxBlockNum;
            return(ulAddrChange+ulTemp* stTwoTable[ucBlockName].ulBlockLen +stTwoTable[ucBlockName].ulBlockStartAddr);
        }
    }
    return GAL_GETTWOTABLE_ADDRERR;
}



// ��ȡ��ʷ���ݼ�¼�ĵ�ַ
ulong SetTwoTableNextPoint(uchar ucBlockName)
{
    uchar ucTemp,ucBlockNum;
    uchar ucPoint[2];
    u16 uiPoint;
    u16 uiTemp;
    ulong ulTempAddr;
    
    for(ucTemp=0;ucTemp<GAL_TWOTABLE_LEN;ucTemp++)
    {
        if(stTwoTable[ucTemp].ucBlockType == ucBlockName)
        {
            ucBlockName=ucTemp;
            break;
        }
    }
    if(ucTemp>=GAL_TWOTABLE_LEN)
    {
        ucBlockName=0xff;
    }
//dqren ���Խ�һ���Ż�����Ȼ���ĳ�int
    if(ucBlockName<GAL_TWOTABLE_LEN)
    {
        if(ucBlockName == TYPE_FREEZE_HOURTIME_RECORD)
        {
          
            return SetTwoTableNextPoint2Byte(ucBlockName);
        }
        if((ucBlockName == TYPE_COVER_OPEN_RECORD)||(ucBlockName == TYPE_TERMINAL_OPEN_RECORD)||(ucBlockName == TYPE_LOSS_ALL_VOLTAGE_RECORD)
            ||(ucBlockName == TYPE_ACPOWER_LOSS_RECORD)||(ucBlockName == TYPE_POWER_DOWN_RECORD)||(ucBlockName == TYPE_PROGRAM_RECORD)
           )    //�����¼���E2�����⴦��
        {
            return SetTwoTableNextPointProgEvent(ucBlockName);
        }
        else if(1==ReadDataDirect(EPL_TWOTABLE_ADDR_START+ucBlockName*2,2,&ucPoint[0]))     // ��ָ��ʹ���
        {
            uiPoint=ucPoint[0];                                                             // ��ȡ��ָ��
            uiPoint=uiPoint+stTwoTable[ucBlockName].ucMaxBlockNum-1;
            uiPoint=(uiPoint)% stTwoTable[ucBlockName].ucMaxBlockNum;
            if(ucPoint[1]<stTwoTable[ucBlockName].ucMaxBlockNum)                            // ���´���
            {
                ucPoint[1]++;
            }
            else
            {
                    ucPoint[1]=stTwoTable[ucBlockName].ucMaxBlockNum;
            }
            ucPoint[0]=uiPoint;

            /*----------�жϲ�����һblock--------------*/
            uiTemp = CON_RECORD_FLASH_1BLOCK_BYTE/stTwoTable[ucBlockName].ulBlockLen;//һ��block���ԼǼ���
            ucBlockNum = stTwoTable[ucBlockName].ucMaxBlockNum-uiTemp;
            // ��ǰblock������������һblock��Ϊ��һ�μ�¼��׼��             
            if((ucPoint[0]%uiTemp) == 1)                                                   
            {
                uiPoint = (uiPoint+stTwoTable[ucBlockName].ucMaxBlockNum - 2)%stTwoTable[ucBlockName].ucMaxBlockNum;
                ulTempAddr = uiPoint* stTwoTable[ucBlockName].ulBlockLen +stTwoTable[ucBlockName].ulBlockStartAddr;
                //WaitClrFlash(ulTempAddr);
            }
            else if((ucPoint[0]%uiTemp) == 0)                                                  
            {
                uiPoint = (uiPoint+stTwoTable[ucBlockName].ucMaxBlockNum - 1)%stTwoTable[ucBlockName].ucMaxBlockNum;
                ulTempAddr = uiPoint* stTwoTable[ucBlockName].ulBlockLen +stTwoTable[ucBlockName].ulBlockStartAddr;
                //WaitClrFlash(ulTempAddr);
                if(ucPoint[1] == stTwoTable[ucBlockName].ucMaxBlockNum) 
                {
                    ucPoint[1] = ucBlockNum;
                }
            }
                

                /*----------����ָ��ʹ���--------------*/
            if(1==WriteDataDirect(&ucPoint[0],EPL_TWOTABLE_ADDR_START+ucBlockName*2, 2))
            {
                    return(ucPoint[0] * stTwoTable[ucBlockName].ulBlockLen +stTwoTable[ucBlockName].ulBlockStartAddr);
            }
        }
    }
    return GAL_GETTWOTABLE_ADDRERR;
}

// 
ulong GetTwoTableAddrFromBlock(uchar ucBlockName,u16 uiBloakStart,ulong ulAddrChange)
{
    uchar ucTemp;
    ulong ulTemp;
    uchar ucPoint[2];
    for(ucTemp=0;ucTemp<GAL_TWOTABLE_LEN;ucTemp++)
    {
        if(stTwoTable[ucTemp].ucBlockType == ucBlockName)
        {
            //assert(ucBlockName==ucTemp)
            break;
        }
    }
    if(ucTemp>=GAL_TWOTABLE_LEN)
    {
        ucBlockName=0xff;
    }
    if(ucBlockName<GAL_TWOTABLE_LEN)
    {
    
        if(ucBlockName == TYPE_FREEZE_HOURTIME_RECORD)
        {
            return GetTwoTableAddrFromBlock2Byte(ucBlockName,uiBloakStart,ulAddrChange);
        }
        else if(1==ReadDataDirect(EPL_TWOTABLE_ADDR_START+ucBlockName*2,2,&ucPoint[0]))
        {
            if(uiBloakStart>=ucPoint[1])
            {
                return GAL_GETTWOTABLE_POINTRERR;
            }
            ulTemp=(ucPoint[0]+uiBloakStart)% stTwoTable[ucBlockName].ucMaxBlockNum;
            return(ulAddrChange+ulTemp* stTwoTable[ucBlockName].ulBlockLen +stTwoTable[ucBlockName].ulBlockStartAddr);
        }
    }
    return GAL_GETTWOTABLE_ADDRERR;
}








// �������㶳���������󣬴˴�ר�ſ���һ������Ϊ���㶳���¼������һblock
/*void EraseTwoTableNextBlock2Byte(uchar ucBlockName);
void EraseTwoTableNextBlock2Byte(uchar ucBlockName)
{
    u16 uiTemp;
    u16 uiPoint[2];
    ulong ulTempAddr;
    
    if(TYPE_FREEZE_HOURTIME_RECORD==ucBlockName)
    {
        if(1==ReadDataDirect(EPL_TWOTABLE_ADDR_START+ucBlockName*2,4,(uchar *)&uiPoint[0]))
        {
            uiTemp = CON_RECORD_FLASH_1BLOCK_BYTE/stTwoTable[ucBlockName].ulBlockLen;
            uiTemp = uiPoint[0]%uiTemp;
            if(uiTemp == 0)                                                // ��ʷ���ݼ���һ��block��flash�ռ�,������һblock�ռ�
            {           
                uiPoint[0] = (uiPoint[0]+CON_FREEZE_HOURTIME_RECORD_MAX_COUNT - 1)%CON_FREEZE_HOURTIME_RECORD_MAX_COUNT;
                ulTempAddr = uiPoint[0]* stTwoTable[ucBlockName].ulBlockLen +stTwoTable[ucBlockName].ulBlockStartAddr;
                ulTempAddr &= MAX_ADDR;
                EraseFlash(FIRST_FLASH,ulTempAddr);
                Delayms(ERASE_BLOCK_DELAY);

                if(uiPoint[1] == CON_FREEZE_HOURTIME_RECORD_MAX_COUNT)
                {
                    uiPoint[1] = CON_FREEZE_HOURTIME_RECORD_MAX_COUNT/2;
                }
                WriteDataDirect((uchar*)&uiPoint[1],EPL_TWOTABLE_ADDR_START+ucBlockName*2+2, 2); // ������ʷ��¼����
            }
        }
    }
}*/



// �жϲ�����һblock
// ��ʷ�����ڼ���һ��block������ʱ��������һblock��
/*void JudgeToEraseHistoryData(uchar ucBlockName)
{
    uchar ucTemp;
    uchar ucPoint[2];
    //u16 uiPoint; 
    u16 uiTemp;
    ulong ulTempAddr;
    
    for(ucTemp=0;ucTemp<GAL_TWOTABLE_LEN;ucTemp++)
    {
        if(stTwoTable[ucTemp].ucBlockType == ucBlockName)
        {
            ucBlockName=ucTemp;
            break;
        }
    }
    if(ucTemp>=GAL_TWOTABLE_LEN)
    {
        ucBlockName=0xff;
    }
    if(ucBlockName<GAL_TWOTABLE_LEN)
    {
    
        if(ucBlockName == TYPE_FREEZE_HOURTIME_RECORD)
        {
            EraseTwoTableNextBlock2Byte(ucBlockName);
        }
        else
        {
            if(1==ReadDataDirect(EPL_TWOTABLE_ADDR_START+ucBlockName*2,2,&ucPoint[0]))      // ��ָ��ʹ���
            {
                uiTemp = CON_RECORD_FLASH_1BLOCK_BYTE/stTwoTable[ucBlockName].ulBlockLen;
                uiTemp = ucPoint[0]%uiTemp;
                if(uiTemp == 0)                                                // ��ʷ���ݼ���һ��block��flash�ռ�
                {
                    ucPoint[0] = (ucPoint[0]+stTwoTable[ucBlockName].ucMaxBlockNum - 1)%stTwoTable[ucBlockName].ucMaxBlockNum;
                    ulTempAddr = ucPoint[0]* stTwoTable[ucBlockName].ulBlockLen +stTwoTable[ucBlockName].ulBlockStartAddr;
                    ulTempAddr &= MAX_ADDR;
                    EraseFlash(FIRST_FLASH,ulTempAddr);
                    Delayms(ERASE_BLOCK_DELAY); 
                    if(ucPoint[1] == stTwoTable[ucBlockName].ucMaxBlockNum) // ���������洢�ռ䣬ɾ��һ��block�󣬼�ȥ��Ӧ������
                    {
                        ucPoint[1] = stTwoTable[ucBlockName].ucBlockNum;
                    }
                    WriteDataDirect(&ucPoint[1],EPL_TWOTABLE_ADDR_START+ucBlockName*2+1, 1); // ������ʷ��¼����
                    //ucProgramFlashWait=ERASE_BLOCK_DELAY/10;
                }
            }
        }
    }
}*/










/*ulong GetTwoTableAddrFromAddr(ulong ulFromAddr)
{
    ulong ulAllLen,ulAddrMax,ulTemp;
    uchar ucTemp;
    for ( ucTemp = 0; ucTemp < GAL_TWOTABLE_LEN; ucTemp ++)
    {
        if(stTwoTable[ucTemp].ulBlockStartAddr <= ulFromAddr)
        {
            ulAllLen = stTwoTable[ucTemp].ulBlockLen ;
            ulAllLen=ulAllLen* stTwoTable[ucTemp].ucBlockNum;
            ulAddrMax=ulAllLen+stTwoTable[ucTemp].ulBlockStartAddr;
            if(ulAddrMax<ulFromAddr)
            // Data if  find
            {
                if(1==ReadDataDirect(EPL_TWOTABLE_ADDR_START+ucTemp*2,1,&ucTemp))
                {
                    ulTemp=ucTemp%stTwoTable[ucTemp].ucBlockNum;
                    ulTemp=ulFromAddr + ulTemp * stTwoTable[ucTemp].ulBlockLen ;
                    if(ulTemp>=ulAddrMax)
                        {
                        ulTemp=ulTemp-ulAllLen;
                        }
                    return ulTemp;
                }
            }
        }
    }
    return GAL_GETTWOTABLE_ADDRERR;
}*/


/*

ulong GetTwoTableAddrFromAddr(uchar ucStoryTypeIn,ulong ulFromAddr)
{
    ulong ulAllLen,ulAddrMax,ulTemp;
    uchar ucTemp;
    for ( ucTemp = 0; ucTemp < GAL_TWOTABLE_LEN; ucTemp ++)
    {
        if( stTwoTable[ucTemp].ucStorType == ucStoryTypeIn )
        // The Same storyType
        {
            if(stTwoTable[ucTemp].ulBlockStartAddr <= ulFromAddr)
            {
                ulAllLen = stTwoTable[ucTemp].ulBlockLen ;
                ulAllLen=ulAllLen* stTwoTable[ucTemp].ucBlockNum;
                ulAddrMax=ulAllLen+stTwoTable[ucTemp].ulBlockStartAddr;
                if(ulAddrMax<ulFromAddr)
                // Data if  find
                {
                    if(1==ReadDataDirect(EPL_TWOTABLE_ADDR_START+ucTemp,1,&ucTemp))
                    {
                        ulTemp=ucTemp%stTwoTable[ucTemp].ucBlockNum;
                        ulTemp=ulFromAddr + ulTemp * stTwoTable[ucTemp].ulBlockLen ;
                        if(ulTemp>=ulAddrMax)
                            {
                            ulTemp=ulTemp-ulAllLen;
                            }
                        return ulTemp;
                    }
                }
            }
        }
    }
    return GAL_GETTWOTABLE_ADDRERR;
}
*/








