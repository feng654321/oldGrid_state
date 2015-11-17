#define AP_TWOTABLE_GLOBALS
#include "common.h"


ulong SetTwoTableNextPoint2Byte(uchar ucBlockName);
ulong GetTwoTableAddrFromBlock2Byte(uchar ucBlockName,u16 uiBloakStart,ulong ulAddrChange);
// 因为之前把整半点冻结放在二次表最后外置，没有问题。现在将整半点冻结上移到编程盖
// 开启事件之后，目前的查二次表方式会导致地址冲突， 故编程盖开启事件记录暂不能使用。
const ST_TWOTAB_PARAM stTwoTable[GAL_TWOTABLE_LEN]=
{
    {TYPE_HISTROY_POWER_RECORD, 36 ,FL1_LAST_POWER_RECORD_START , 1024 }, // 0 历史电量数据记录
    {TYPE_HISTROY_DEMAND_RECORD, 36 ,FL1_LAST_DEMAND_RECORD_START , 2048 }, // 1 历史需量数据记录
    {TYPE_HISTROY_USEPOWER_RECORD, 36 , FL1_LAST_USEPOWER_RECORD_START , 1024 }, // 2 历史用电量数据记录
    {TYPE_MONITOR_VOLTAGE_ALL_RECORD, 32 , FL1_LAST_MONITOR_VOLTAGE_ALL_RECORD_START , 256 }, // 3 电压合格率统计数据记录
    {TYPE_MONITOR_VOLTAGE_A_RECORD, 32 , FL1_LAST_MONITOR_VOLTAGE_A_RECORD_START , 256 }, // 4 A相电压合格率统计数据记录
    {TYPE_MONITOR_VOLTAGE_B_RECORD, 32 , FL1_LAST_MONITOR_VOLTAGE_B_RECORD_START , 256 }, // 5 B相电压合格率统计数据记录
    {TYPE_MONITOR_VOLTAGE_C_RECORD, 32 , FL1_LAST_MONITOR_VOLTAGE_C_RECORD_START , 256 }, // 6 C相电压合格率统计数据记录
    {TYPE_LOSS_A_VOLTAGE_RECORD, 32 ,  FL1_LAST_LOSS_A_VOLTAGE_RECORD_START , 256 }, // 7 A相失压事件记录
    {TYPE_LOSS_B_VOLTAGE_RECORD, 32 , FL1_LAST_LOSS_B_VOLTAGE_RECORD_START , 256 }, // 8 B相失压事件记录
    {TYPE_LOSS_C_VOLTAGE_RECORD, 32 , FL1_LAST_LOSS_C_VOLTAGE_RECORD_START , 256 }, // 9 C相失压事件记录
    {TYPE_LOSS_AB_VOLTAGE_RECORD, 32 , FL1_LAST_LOSS_AB_VOLTAGE_RECORD_START , 256 }, // 10 AB相失压事件记录
    {TYPE_LOSS_AC_VOLTAGE_RECORD, 32 , FL1_LAST_LOSS_AC_VOLTAGE_RECORD_START , 256 }, // 11 AC相失压事件记录
    {TYPE_LOSS_BC_VOLTAGE_RECORD, 32 , FL1_LAST_LOSS_BC_VOLTAGE_RECORD_START , 256 }, // 12 BC相失压事件记录
    {TYPE_LOSS_ABC_VOLTAGE_RECORD, 32 , FL1_LAST_LOSS_ABC_VOLTAGE_RECORD_START , 256 }, // 13 ABC相失压事件记录
    {TYPE_DOWN_A_VOLTAGE_RECORD, 32 ,  FL1_LAST_DOWN_A_VOLTAGE_RECORD_START , 256 }, // 14 A相欠压事件记录
    {TYPE_DOWN_B_VOLTAGE_RECORD, 32 , FL1_LAST_DOWN_B_VOLTAGE_RECORD_START , 256 }, // 15 B相欠压事件记录
    {TYPE_DOWN_C_VOLTAGE_RECORD, 32 , FL1_LAST_DOWN_C_VOLTAGE_RECORD_START , 256 }, // 16 C相欠压事件记录
    {TYPE_OVER_A_VOLTAGE_RECORD, 32 , FL1_LAST_OVER_A_VOLTAGE_RECORD_START , 256 }, // 17 A相过压事件记录
    {TYPE_OVER_B_VOLTAGE_RECORD, 32 ,  FL1_LAST_OVER_B_VOLTAGE_RECORD_START , 256 }, // 18 B相过压事件记录
    {TYPE_OVER_C_VOLTAGE_RECORD, 32 ,  FL1_LAST_OVER_C_VOLTAGE_RECORD_START , 256 }, // 19C相过压事件记录
    {TYPE_CUT_A_VOLTAGE_RECORD, 32 , FL1_LAST_CUT_A_VOLTAGE_RECORD_START , 256 }, // 20 A相断相事件记录
    {TYPE_CUT_B_VOLTAGE_RECORD, 32 , FL1_LAST_CUT_B_VOLTAGE_RECORD_START , 256 }, // 21 B相断相事件记录
    {TYPE_CUT_C_VOLTAGE_RECORD, 32 , FL1_LAST_CUT_C_VOLTAGE_RECORD_START , 256 }, // 22 C相断相事件记录
    {TYPE_LOSS_A_CURRENT_RECORD, 32 , FL1_LAST_LOSS_A_CURRENT_RECORD_START , 256 }, // 23 A相失流事件记录
    {TYPE_LOSS_B_CURRENT_RECORD, 32 , FL1_LAST_LOSS_B_CURRENT_RECORD_START , 256 }, // 24 B相失流事件记录
    {TYPE_LOSS_C_CURRENT_RECORD, 32 , FL1_LAST_LOSS_C_CURRENT_RECORD_START , 256 }, // 25 C相失流事件记录
    {TYPE_LOSS_AB_CURRENT_RECORD, 32 , FL1_LAST_LOSS_AB_CURRENT_RECORD_START , 256 }, // 26 AB相失流事件记录
    {TYPE_LOSS_AC_CURRENT_RECORD, 32 , FL1_LAST_LOSS_AC_CURRENT_RECORD_START , 256 }, // 27 AC相失流事件记录
    {TYPE_LOSS_BC_CURRENT_RECORD, 32 , FL1_LAST_LOSS_BC_CURRENT_RECORD_START , 256 }, // 28 BC相失流事件记录
    {TYPE_LOSS_ABC_CURRENT_RECORD, 32 , FL1_LAST_LOSS_ABC_CURRENT_RECORD_START , 256 }, // 29 ABC相失流事件记录
    {TYPE_OVER_A_CURRENT_RECORD, 32 ,  FL1_LAST_OVER_A_CURRENT_RECORD_START , 256 }, // 30 A相过流事件记录
    {TYPE_OVER_B_CURRENT_RECORD, 32 , FL1_LAST_OVER_B_CURRENT_RECORD_START , 256 }, // 31 B相过流事件记录
    {TYPE_OVER_C_CURRENT_RECORD, 32 , FL1_LAST_OVER_C_CURRENT_RECORD_START , 256 }, // 32 C相过流事件记录
    {TYPE_CUT_A_CURRENT_RECORD, 32, FL1_LAST_CUT_A_CURRENT_RECORD_START , 256 }, // 33 A相断流事件记录
    {TYPE_CUT_B_CURRENT_RECORD, 32 , FL1_LAST_CUT_B_CURRENT_RECORD_START , 256 }, // 34 B相断流事件记录
    {TYPE_CUT_C_CURRENT_RECORD, 32 , FL1_LAST_CUT_C_CURRENT_RECORD_START , 256 }, // 35 C相断流事件记录
    {TYPE_REVERSEPOWER_ALL_RECORD, 32 , FL1_LAST_REVERSEPOWER_ALL_RECORD_START , 256 }, // 36总功率反向事件记录
    {TYPE_REVERSEPOWER_A_RECORD, 32 , FL1_LAST_REVERSEPOWER_A_RECORD_START , 256 }, // 37 A相功率反向事件记录
    {TYPE_REVERSEPOWER_B_RECORD, 32 , FL1_LAST_REVERSEPOWER_B_RECORD_START , 256 }, // 38 B相功率反向事件记录
    {TYPE_REVERSEPOWER_C_RECORD, 32 , FL1_LAST_REVERSEPOWER_C_RECORD_START , 256 }, // 39 C相功率反向事件记录
    {TYPE_POWEROVER_ALL_RECORD, 32 , FL1_LAST_POWEROVER_ALL_RECORD_START , 256 }, // 40 总功率过载事件记录
    {TYPE_POWEROVER_A_RECORD, 32 , FL1_LAST_POWEROVER_A_RECORD_START , 256 }, // 41 A相功率过载事件记录
    {TYPE_POWEROVER_B_RECORD, 32 , FL1_LAST_POWEROVER_B_RECORD_START , 256 }, // 42 B相功率过载事件记录
    {TYPE_POWEROVER_C_RECORD, 32, FL1_LAST_POWEROVER_C_RECORD_START , 256 }, // 43 C相功率过载事件记录
    {TYPE_DEMAND_OVER_KW_F_RECORD, 32 , FL1_LAST_DEMAND_OVER_KW_F_RECORD_START , 256 }, // 44 正向有功需量超限事件记录
    {TYPE_DEMAND_OVER_KW_R_RECORD, 32 , FL1_LAST_DEMAND_OVER_KW_R_RECORD_START , 256 }, // 45 反向有功需量超限事件记录
    {TYPE_DEMAND_OVER_KVAR_Q1_RECORD, 32 , FL1_LAST_DEMAND_OVER_KVAR_Q1_RECORD_START , 256 }, // 46 第1象限无功需量超限事件记录
    {TYPE_DEMAND_OVER_KVAR_Q2_RECORD, 32 , FL1_LAST_DEMAND_OVER_KVAR_Q2_RECORD_START , 256 }, // 47 第2象限无功需量超限事件记录
    {TYPE_DEMAND_OVER_KVAR_Q3_RECORD, 32 , FL1_LAST_DEMAND_OVER_KVAR_Q3_RECORD_START , 256 }, // 48 第3象限无功需量超限事件记录
    {TYPE_DEMAND_OVER_KVAR_Q4_RECORD, 32 , FL1_LAST_DEMAND_OVER_KVAR_Q4_RECORD_START , 256 }, // 49 第4象限无功需量超限事件记录
    {TYPE_DEMAND_OVER_KVAR_C1_RECORD, 32 , FL1_LAST_DEMAND_OVER_KVAR_C1_RECORD_START , 256 }, // 50 无功组合1需量超限事件记录
    {TYPE_DEMAND_OVER_KVAR_C2_RECORD, 32 , FL1_LAST_DEMAND_OVER_KVAR_C2_RECORD_START , 256 }, // 51 无功组合2需量超限事件记录
    {TYPE_ORDER_VOLTAGE_RECORD, 32 , FL1_LAST_ORDER_VOLTAGE_RECORD_START , 256 }, // 52 电压逆向序事件记录
    {TYPE_ORDER_CURRENT_RECORD, 32 , FL1_LAST_ORDER_CURRENT_RECORD_START , 256 }, // 53 电流逆向序事件记录
    {TYPE_UNBALANCE_VOLTAGE_RECORD, 32 , FL1_LAST_UNBALANCE_VOLTAGE_RECORD_START , 256 }, // 54 电压不平衡事件记录
    {TYPE_UNBALANCE_CURRENT_RECORD, 32 , FL1_LAST_UNBALANCE_CURRENT_RECORD_START , 256 }, // 55 电流不平衡事件记录
    {TYPE_PROGRAM_METERCLR_RECORD, 64 , FL1_LAST_PROGRAM_POWERCLR_RECORD_START , 1024 }, // 56 电表清零编程事件记录
    {TYPE_PROGRAM_DEMANDCLR_RECORD, 40 , FL1_LAST_PROGRAM_DEMANDCLR_RECORD_START , 2048 }, // 57 需量清零编程事件记录
    {TYPE_PROGRAM_EVENTCLR_RECORD, 128 , FL1_LAST_PROGRAM_EVENTCLR_RECORD_START , 64 }, // 58 事件清零编程事件记录
    {TYPE_PROGRAM_TIME_RECORD, 128 , FL1_LAST_PROGRAM_TIME_RECORD_START , 64 }, // 59 校时编程事件记录
    {TYPE_PROGRAM_DAYTABLE_RECORD, 32 , FL1_LAST_PROGRAM_DAYTABLE_RECORD_START , 1024 }, // 60 时段表编程记录
    {TYPE_PROGRAM_SEASON_RECORD, 64 , FL1_LAST_PROGRAM_SEASON_RECORD_START , 128 }, // 61 时区表编程记录
    {TYPE_PROGRAM_RESTDAY_RECORD, 64 , FL1_LAST_PROGRAM_RESTDAY_RECORD_START , 128 }, // 62 周休日编程事件记录
    {TYPE_PROGRAM_HOLIDAY_RECORD, 16 , FL1_LAST_PROGRAM_HOLIDAY_RECORD_START , 2048 }, // 63 节假日编程事件记录
    {TYPE_PROGRAM_CHARACTER_ACTIVE_RECORD, 64 , FL1_LAST_PROGRAM_CHARACTER_ACTIVE_RECORD_START , 128 }, // 64 有功组合方式特征字编程事件记录
    {TYPE_PROGRAM_CHARACTER_REACTIVE01_RECORD, 64 , FL1_LAST_PROGRAM_CHARACTER_REACTIVE01_RECORD_START , 128 }, // 65无功组合方式1编程事件记录
    {TYPE_PROGRAM_CHARACTER_REACTIVE02_RECORD, 64 , FL1_LAST_PROGRAM_CHARACTER_REACTIVE02_RECORD_START , 128 }, // 66 无功组合方式2编程事件记录
    {TYPE_PROGRAM_CHARACTER_REACTIVE03_RECORD, 64 , FL1_LAST_PROGRAM_CHARACTER_REACTIVE03_RECORD_START , 128 }, // 67 无功组合方式3编程事件记录
    {TYPE_PROGRAM_CHARACTER_REACTIVE04_RECORD, 64 , FL1_LAST_PROGRAM_CHARACTER_REACTIVE04_RECORD_START , 128 }, // 68 无功组合方式4编程事件记录
    {TYPE_PROGRAM_BALANCE_DAY_RECORD, 128 , FL1_LAST_PROGRAM_BALANCE_DAY_RECORD_START , 128 }, // 69 结算日编程事件记录
    {TYPE_DAYTABLE_MODULE_RECORD, 64 , FL1_LAST_PROGRAM_DAYTABLE_MODULE_RECORD_START , 128 }, // 70 远程设置时段事件数据记录
    {TYPE_FREEZE_EVERYTIME_RECORD, 128 , FL1_LAST_FREEZE_EVERYTIME_RECORD_START , 1024 }, // 71 定时冻结数据
    {TYPE_FREEZE_INSTANT_RECORD, 64 , FL1_LAST_FREEZE_INSTANT_RECORD_START , 1024 }, // 72 瞬时冻结数据
    {TYPE_FREEZE_EVERYZERO_RECORD, 64 , FL1_LAST_FREEZE_EVERYZERO_RECORD_START , 1024 }, // 73 日零点冻结事件数据
    {TYPE_FREEZE_SEASONCHANGE_RECORD, 16 , FL1_LAST_FREEZE_SEASONCHANGE_RECORD_START , 1024 }, // 74 2套时区表切换冻结数据
    {TYPE_FREEZE_DAYTABLECHANGE_RECORD, 16 , FL1_LAST_FREEZE_DAYTABLECHANGE_RECORD_START , 1024 }, // 75 2套日时段表切换冻结数据
    {TYPE_FREEZE_STEPPRICE_TABLECHANGE_RECORD, 16 , FL1_LAST_FREEZE_STEPPRICE_TABLECHANGE_RECORD_START , 1024 }, // 76 2套阶梯切换冻结数据
    {TYPE_FREEZE_PERIODPRICE_TABLECHANGE_RECORD, 16 , FL1_LAST_FREEZE_PERIODPRICE_TABLECHANGE_RECORD_START , 1024 }, // 77 2套费率电价切换冻结数据
    {TYPE_RELAY_OPEN_RECORD, 64 , FL1_LAST_RELAY_OPEN_RECORD_START , 128 }, // 78 拉闸事件记录
    {TYPE_RELAY_CLOSE_RECORD, 64 , FL1_LAST_RELAY_CLOSE_RECORD_START , 128 }, // 79 合闸事件记录
    {TYPE_ERR_TIME_RECORD, 128 , FL1_LAST_ERR_TIME_RECORD_START , 64 }, // 80 时钟错误事件记录
    {TYPE_ERR_POWER_RECORD, 100 , FL1_LAST_ERR_POWER_RECORD_START , 1024 }, // 81 电量错误事件记录
    {TYPE_OVERTOTALCOS_RECORD, 32 , FL1_LAST_OVERTOTALCOS_RECORD_START , 256 }, // 82 总功率因数超限事件记录
    {TYPE_BUY_MONEY_RECORD, 64 , FL1_LAST_BUY_MONEY_RECORD_START , 128 }, // 83购电金额记录
    {TYPE_BUY_KWH_RECORD, 64 , FL1_LAST_BUY_KWH_RECORD_START , 128 }, // 84 购电电量记录
    {TYPE_BROADCASTTIME_RECORD,128,FL1_LAST_BROADCASTTIME_RECORD_START,64}, // 85 广播校时
    {TYPE_FREEZE_HOURTIME_RECORD, 512 , FL1_LAST_FREEZE_HOURTIME_RECORD_START , 16 },// 86 整点半点电量冻结数据记录   
    {TYPE_PROGRAM_OPEN_RECORD, 32 , FL1_LAST_PROGRAM_OPEN_RECORD_START , 256 }, // 87 编程盖开启事件记录
    
    {TYPE_COVER_OPEN_RECORD, 10 , EPL_LAST_COVER_OPEN_RECORD_START , 72 }, // 88 表盖开启事件记录
    {TYPE_TERMINAL_OPEN_RECORD, 10 , EPL_LAST_TERMINAL_OPEN_RECORD_START , 72 }, // 89 端钮盖开启事件记录
#if (CONFIG_METER_AREA_MODE_SOUTHGRID==CONFIG_METER_AREA_MODE)
    {TYPE_LOSS_ALL_VOLTAGE_RECORD, 10 , EPL_LAST_LOSS_ALL_VOLTAGE_RECORD_START , 131 }, // 90 全失压事件记录
#else
    {TYPE_LOSS_ALL_VOLTAGE_RECORD, 10 , EPL_LAST_LOSS_ALL_VOLTAGE_RECORD_START , 16 }, // 90 全失压事件记录
#endif
    {TYPE_ACPOWER_LOSS_RECORD, 10 , EPL_LAST_ACPOWER_LOSS_RECORD_START , 16 }, // 91辅助电源掉电事件记录
    {TYPE_POWER_DOWN_RECORD, 10 , EPL_LAST_POWER_DOWN_RECORD_START , 16 }, // 92 系统电源掉电事件记录
    {TYPE_PROGRAM_RECORD, 10 , EPL_LAST_PROGRAM_RECORD_START , 64 }, // 93 编程事件记录

    {TYPE_MIN_POWER_RECORD,  56, FL1_LAST_PER_MIN_POWER_START,   1024},    // 94 每分钟电量保存

};


//编程事件指针的特殊处理
ulong SetTwoTableNextPointProgEvent(uchar ucBlockName);
ulong SetTwoTableNextPointProgEvent(uchar ucBlockName)
{
    uchar ucPoint[2];   
    u16 uiPoint;
    
        if((ucBlockName == TYPE_COVER_OPEN_RECORD)||(ucBlockName == TYPE_TERMINAL_OPEN_RECORD)||(ucBlockName == TYPE_LOSS_ALL_VOLTAGE_RECORD)
            ||(ucBlockName == TYPE_ACPOWER_LOSS_RECORD)||(ucBlockName == TYPE_POWER_DOWN_RECORD)||(ucBlockName == TYPE_PROGRAM_RECORD)
           )    //编程事件特殊处理，存铁电
    {
        if(1==ReadDataDirect(EPL_TWOTABLE_ADDR_START+ucBlockName*2,2,&ucPoint[0]))
        {
            uiPoint=ucPoint[0];                                                             // 获取新指针
            uiPoint=uiPoint+stTwoTable[ucBlockName].ucMaxBlockNum-1;
            uiPoint=(uiPoint)% stTwoTable[ucBlockName].ucMaxBlockNum;
            if(ucPoint[1]<stTwoTable[ucBlockName].ucMaxBlockNum)                            // 更新次数
            {
                ucPoint[1]++;
            }
            else
            {
                ucPoint[1]=stTwoTable[ucBlockName].ucMaxBlockNum;
            }
            ucPoint[0]=uiPoint;
                        
            
            /*----------保存指针和次数--------------*/
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
            
            /*----------判断擦除下一block--------------*/
            uiTemp = CON_RECORD_FLASH_1BLOCK_BYTE/stTwoTable[ucBlockName].ulBlockLen;
            
            if((uiPoint[0]%uiTemp) == 1)                                                   
            {
                uiTempPoint = (uiTempPoint+stTwoTable[ucBlockName].ucMaxBlockNum - 2)%stTwoTable[ucBlockName].ucMaxBlockNum;
                ulTempAddr = uiTempPoint* stTwoTable[ucBlockName].ulBlockLen +stTwoTable[ucBlockName].ulBlockStartAddr;
                //WaitClrFlash(ulTempAddr);
            }
            else if((uiPoint[0]%uiTemp) == 0)                                              // 历史数据记满一个block的flash空间
            {
                uiTempPoint = (uiTempPoint+stTwoTable[ucBlockName].ucMaxBlockNum - 1)%stTwoTable[ucBlockName].ucMaxBlockNum;
                ulTempAddr = uiTempPoint* stTwoTable[ucBlockName].ulBlockLen +stTwoTable[ucBlockName].ulBlockStartAddr;
                //WaitClrFlash(ulTempAddr);
                if(uiPoint[1] >= (stTwoTable[ucBlockName].ucMaxBlockNum/2)) // 记满整个存储空间，删除一个block后，减去相应的条数
                {
                    uiPoint[1] = stTwoTable[ucBlockName].ucMaxBlockNum/2;
                }
            }
            
            /*----------保存指针和次数--------------*/  
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



// 获取历史数据记录的地址
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
//dqren 可以进一步优化，既然都改成int
    if(ucBlockName<GAL_TWOTABLE_LEN)
    {
        if(ucBlockName == TYPE_FREEZE_HOURTIME_RECORD)
        {
          
            return SetTwoTableNextPoint2Byte(ucBlockName);
        }
        if((ucBlockName == TYPE_COVER_OPEN_RECORD)||(ucBlockName == TYPE_TERMINAL_OPEN_RECORD)||(ucBlockName == TYPE_LOSS_ALL_VOLTAGE_RECORD)
            ||(ucBlockName == TYPE_ACPOWER_LOSS_RECORD)||(ucBlockName == TYPE_POWER_DOWN_RECORD)||(ucBlockName == TYPE_PROGRAM_RECORD)
           )    //此类事件存E2，特殊处理
        {
            return SetTwoTableNextPointProgEvent(ucBlockName);
        }
        else if(1==ReadDataDirect(EPL_TWOTABLE_ADDR_START+ucBlockName*2,2,&ucPoint[0]))     // 读指针和次数
        {
            uiPoint=ucPoint[0];                                                             // 获取新指针
            uiPoint=uiPoint+stTwoTable[ucBlockName].ucMaxBlockNum-1;
            uiPoint=(uiPoint)% stTwoTable[ucBlockName].ucMaxBlockNum;
            if(ucPoint[1]<stTwoTable[ucBlockName].ucMaxBlockNum)                            // 更新次数
            {
                ucPoint[1]++;
            }
            else
            {
                    ucPoint[1]=stTwoTable[ucBlockName].ucMaxBlockNum;
            }
            ucPoint[0]=uiPoint;

            /*----------判断擦除下一block--------------*/
            uiTemp = CON_RECORD_FLASH_1BLOCK_BYTE/stTwoTable[ucBlockName].ulBlockLen;//一个block可以记几条
            ucBlockNum = stTwoTable[ucBlockName].ucMaxBlockNum-uiTemp;
            // 当前block记满，擦除下一block，为下一次记录做准备             
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
                

                /*----------保存指针和次数--------------*/
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








// 由于整点冻结条数过大，此处专门开辟一个函数为整点冻结记录擦除下一block
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
            if(uiTemp == 0)                                                // 历史数据记满一个block的flash空间,擦除下一block空间
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
                WriteDataDirect((uchar*)&uiPoint[1],EPL_TWOTABLE_ADDR_START+ucBlockName*2+2, 2); // 保存历史记录条数
            }
        }
    }
}*/



// 判断擦除下一block
// 历史数据在记满一个block的内容时，擦除下一block。
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
            if(1==ReadDataDirect(EPL_TWOTABLE_ADDR_START+ucBlockName*2,2,&ucPoint[0]))      // 读指针和次数
            {
                uiTemp = CON_RECORD_FLASH_1BLOCK_BYTE/stTwoTable[ucBlockName].ulBlockLen;
                uiTemp = ucPoint[0]%uiTemp;
                if(uiTemp == 0)                                                // 历史数据记满一个block的flash空间
                {
                    ucPoint[0] = (ucPoint[0]+stTwoTable[ucBlockName].ucMaxBlockNum - 1)%stTwoTable[ucBlockName].ucMaxBlockNum;
                    ulTempAddr = ucPoint[0]* stTwoTable[ucBlockName].ulBlockLen +stTwoTable[ucBlockName].ulBlockStartAddr;
                    ulTempAddr &= MAX_ADDR;
                    EraseFlash(FIRST_FLASH,ulTempAddr);
                    Delayms(ERASE_BLOCK_DELAY); 
                    if(ucPoint[1] == stTwoTable[ucBlockName].ucMaxBlockNum) // 记满整个存储空间，删除一个block后，减去相应的条数
                    {
                        ucPoint[1] = stTwoTable[ucBlockName].ucBlockNum;
                    }
                    WriteDataDirect(&ucPoint[1],EPL_TWOTABLE_ADDR_START+ucBlockName*2+1, 1); // 保存历史记录条数
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








