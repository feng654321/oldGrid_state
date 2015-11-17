/*********************************************************************************
    版本号     :version 0.1
    模块名       : 远程控制模块
    文件名       : CommExplainTable.c
    相关文件     : 
    文件实现功能 : 通信使用表格模块
    作者         : 姚徐旭
    版本         : 0.1
----------------------------------------------------------------------------------------------------------------------
    备注         : <其它说明>
---------------------------------------------------------------------------------------------------------------------
    修改记录 : 
    日 期        版本     修改人              修改内容
    YYYY/MM/DD   X.Ymai      <作者或修改者名>    <修改内容>
    YYYY/MM/DD   X.Y      <作者或修改者名>    <修改内容>
====================================================================
其他说明： 
*******************************************************************************/
#include "common.h"

/*
u16 CommGetGmDay( uchar * Addr );
ulong GetGmHour( uchar * Addr );
ulong GetGmMin(uchar * Addr );
*/



#if (COMM_METER_TYPE ==METER_TYPE_THERRPHASE)
        /////失压,欠压,过压,断相使用长度
COMM_CONST  uchar ucEvenLosevoltageLenth[]=
        {
            6,6,
            5,5,5,5,5,5,5,5,
            2,
            3,3,3,
            2,
            5,5,5,5,
            2,
            3,3,3,
            2,
            5,5,5,5,
            2,
            3,3,3,
            2,
            5,5,5,5
        };
    
    
    /////全失压
COMM_CONST  uchar ucEvenLoseVoltageAllLenth[]=
    {
        6,3,6,
    };
    
    ////辅助电源失电
COMM_CONST  uchar ucEvenAPVolatgeLenth[]=
    {
        6,6,
    };
    ////电压,电流逆相序,潮流反向,过载
COMM_CONST  uchar ucEvenConverseLenth[]=
    {
        6,6,
        5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5
    }
    
    /////电流,电压不平衡
COMM_CONST  uchar ucEvenUblanceLenth[]=
    {
        6,6,
        2,
        5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5
    }; 

        ////失流,过流,断流
COMM_CONST  uchar ucEvenLoseCurrentLenth[]=
    {
        6,6,
        5,5,5,5,5,5,5,5,
        2,
        3,3,3,
        2,
        5,5,5,5,
        2,
        3,3,3,
        2,
        5,5,5,5,
        2,
        3,3,3,
        2
    };
    
    ////电压合格率数据
COMM_CONST  uchar ucEvenVoltagecheckOut[]=
    {
        3,3,3,3,3,2,4,2,4
    };
    
    //////掉电数据
COMM_CONST uchar ucEvenPowerOff[]=
    {
        6,6,
    };
    
    ////需量超限总次数
COMM_CONST  uchar ucEvenMDOverLoad[]=
    {
        3,3,3,3,3,3
    };
    ////需量超限记录内容
COMM_CONST  uchar ucEvenMDOverLoadRecord[]=
    {
        6,6,3,5
    };

        ////电表操作---编程
COMM_CONST  uchar ucEvenMeterProgram[]=
    {
        6,4,
        4,4,4,4,4,4,4,4,4,4
    };
    ////电表操作---电表清零
COMM_CONST  uchar ucEvenMeterClear[]=
    {
        6,4,
        5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5
    };
    
    ////电表操作---需量清零(还有(4+5)*12放在后续BUFFER中)
COMM_CONST  uchar ucEvenMDClear[]=
    {
        6,4,
        3,5,3,5,3,5,3,5,3,5,3,5,3,5,3,5,3,5,3,5,3,5,3,5,
    };
    
    ////电表操作---事件清零
COMM_CONST  uchar ucEvenEvenClear[]=
    {
        6,4,4
    };
    
    ///电表操作---校时记录
COMM_CONST  uchar ucEvenCheckTime[]=
    {
        4,6,6
    };
    
    ///电表操作---时段表编程字节数为672>200个故分成4份(还有6*(3*14*4)放在后续BUFFER中)
COMM_CONST    uchar ucEvenFeeTableProgram[]=
    {
        6,4,
        3*4*14
    };
    ///电表操作---时区表编程
COMM_CONST  uchar ucEvenFeeSeasonTableProgram[]=
    {
        6,4,
        3*28,
    };
    
    ////电表操作---周休日编程记录
COMM_CONST  uchar ucEvenFeeWeekTableProgram[]=
    {
        6,4,1
    };
    
    ////电表操作---节假日编程记录字节数为1026>200个(还有5*(42*4)分成9份放在后续BUFFER中)
COMM_CONST  uchar ucEvenFeeHolidayProgram[]=
    {
        6,
        4*45,
    };
    
    /////电表操作----有功,无功组合方式,编程记录
COMM_CONST  uchar ucEvenCalucateCombineProgram[]=
    {
        6,4,1
    };
    
    ////电表操作----结算记录
COMM_CONST  uchar ucEvenBillData[]=
    {
        6,4,2,2,2
    };
    
    ////////电表操作----开表盖.开端钮盖
COMM_CONST  uchar ucEvenOpencover[]=
    {
        6,6,
        4,4,4,4,4,4,4,4,4,4,4,4
    };
    

#elif(COMM_METER_TYPE ==METER_TYPE_THERRPHASE_MORE)  ///复杂三相(多功能)
        /////失压,过压,断相使用长度(多出的电量增量屏蔽掉)
COMM_CONST      uchar ucEvenLosevoltageLenth[]=
        {
            6,6,
            5,5,5,5,5,5,5,5,
            2,
            3,3,3,
            2,5,5,5,5,
            2,
            3,3,3,
            2,
            5,5,5,5,
            2,3,3,3,
            2,5,5,5,5
        };
    
/////南网全失压规约
#if (CONFIG_METER_AREA_MODE_SOUTHGRID==CONFIG_METER_AREA_MODE)  
COMM_CONST  uchar ucEvenLoseVoltageAllLenth[]=
{
            6,
            5,5,5,5,5,5,5,5,
            2,
            3,3,3,
            2,5,5,5,5,
            2,
            3,3,3,
            2,
            5,5,5,5,
            2,3,3,3,
            2,6,
};
#else
COMM_CONST  uchar ucEvenLoseVoltageAllLenth[]=
    {
        6,3,6,
    };
#endif

        ////辅助电源失电
COMM_CONST  uchar ucEvenAPVolatgeLenth[]=
    {
        6,6,
    };  
        ////电压,电流逆相序，潮流反向，过载
COMM_CONST      uchar ucEvenConverseLenth[]=
        {
            6,6,
            5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5
        };
    
        /////电流,电压不平衡
COMM_CONST      uchar ucEvenUblanceLenth[]=
        {
            6,6,
            2,
            5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5
        }; 
        
        ////失流,过流,断流
COMM_CONST      uchar ucEvenLoseCurrentLenth[]=
        {
            6,6,
            5,5,5,5,5,5,5,5,
            2,
            3,3,3,
            2,
            5,5,5,5,
            2,
            3,3,3,
            2,
            5,5,5,5,
            2,
            3,3,3,
            2
        };
        
        ////电压合格率数据
COMM_CONST  uchar ucEvenVoltagecheckOut[]=
    {
        3,3,3,3,3,2,4,2,4
    };
    //////掉电数据
COMM_CONST uchar ucEvenPowerOff[]=
    {
        6,6,
    };
        ////需量超限总次数
COMM_CONST  uchar ucEvenMDOverLoad[]=
    {
        4,4,4,4,4,4
    };
    ////需量超限记录内容
COMM_CONST  uchar ucEvenMDOverLoadRecord[]=
    {
        6,6,4,5
    };
    
    ////电表操作---编程
COMM_CONST  uchar ucEvenMeterProgram[]=
    {
        6,4,
        4,4,4,4,4,4,4,4,4,4,
    };
    
    ////电表操作---电表清零
COMM_CONST  uchar ucEvenMeterClear[]=
    {
        6,4,
        5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5
    };
    
    ////电表操作---需量清零由于读出的字节数为202>200个故分成2份(还有(4+5)*12放在后续BUFFER中)
COMM_CONST  uchar ucEvenMDClear[]=
    {
        6,4,
        4,5,4,5,4,5,4,5,4,5,4,5,4,5,4,5,4,5,4,5,4,5,4,5,
    };
    
    ////电表操作---事件清零
COMM_CONST  uchar ucEvenEvenClear[]=
    {
        6,4,4
    };
    
    ///电表操作---校时记录
COMM_CONST  uchar ucEvenCheckTime[]=
    {
        4,6,6
    };
    
    ///电表操作---时段表编程读出的字节数为682>200个故分成4份,第1次为178个,(还有3*(3*14*4)放在后续BUFFER中)
COMM_CONST    uchar ucEvenFeeTableProgram[]=
    {
        6,4,
        ///////以下数据比较特殊
        3*4*14,
    };
    ///电表操作---时段表编程
    /*
COMM_CONST  uchar ucEvenFeeProgram[]=
    {
        6,4,
        42,42,42,42,42,42,42,42,
        42,42,42,42,42,42,42,42
    };
    */
    ///电表操作---时区表编程
COMM_CONST  uchar ucEvenFeeSeasonTableProgram[]=
    {
        6,4,
        3*28,
    };
    
    ////电表操作---周休日编程记录
COMM_CONST  uchar ucEvenFeeWeekTableProgram[]=
    {
        6,4,1
    };
    
    ////电表操作---节假日编程记录字节数为1026>200个,先发送186个,后面的(还有5*(42*4)分成5份放在后续BUFFER中)
COMM_CONST  uchar ucEvenFeeHolidayProgram[]=
    {
        6,
        4*45,
    };
    
    
        /////电表操作----有功,无功组合方式,编程记录
COMM_CONST  uchar ucEvenCalucateCombineProgram[]=
    {
        6,4,1
    };
    
    
        ////电表操作----结算记录
COMM_CONST  uchar ucEvenBillData[]=
    {
        6,4,2,2,2,
    };
    ////////电表操作----开表盖,开端盖
COMM_CONST  uchar ucEvenOpencover[]=
    {
        6,6,
        5,5,5,5,5,5,5,5,5,5,5,5
    };
//////电表操作---远程设置时段事件记录
COMM_CONST  uchar  ucEvenSetTable[]=    
        {
                6,4,
                4*10,
        };


#endif




extern void CommReadDLT07Data(void);
///////通信帧不同执行模块的函数列表
COMM_CONST    STR_TAB_CMMCONTROL    TableCommControl[]=
{
    {COMMTYPE_READ,              CommControlReadData ,		{COMM_HAVE_RETURN,COMMTYPE_STAEPARA_RIGHTADDR+COMMTYPE_STAEPARA_AA_ADDR + COMMTYPE_STAEPARA_ALLAA_ADDR}},
    {COMMTYPE_READWITHLAST,      CommControlReadLastData,	{COMM_HAVE_RETURN,   COMMTYPE_STAEPARA_RIGHTADDR+COMMTYPE_STAEPARA_AA_ADDR + COMMTYPE_STAEPARA_ALLAA_ADDR}},
    {COMMTYPE_WRITEDATA,         CommControlWriteData,   	{COMM_HAVE_RETURN,   COMMTYPE_STAEPARA_RIGHTADDR}},
    {COMMTYPE_READADDR,          CommReadAddr,  			{COMM_HAVE_RETURN,       COMMTYPE_STAEPARA_ALLAA_ADDR}},
    {COMMTYPE_WRITEADDR,         CommWriteAddr,      		{COMM_HAVE_RETURN,           COMMTYPE_STAEPARA_ALLAA_ADDR}},
    {COMMTYPE_BROADCAST,         CommBroadCastTime,  		{COMM_HAVE_NO_RETURN,        COMMTYPE_STAEPARA_BROADCAST_ADDR}},
    {COMMTYPE_FEEZEDATA,         CommControlFeezeData,   	{COMM_HAVE_RETURN,       COMMTYPE_STAEPARA_BROADCAST_ADDR+COMMTYPE_STAEPARA_RIGHTADDR}},
    {COMMTYPE_CHANGEBAUDRATE,    CommChangeBaudRate, 		{COMM_HAVE_RETURN,           COMMTYPE_STAEPARA_RIGHTADDR}},
    {COMMTYPE_CHANGEPASSWORD,    CommChangePassword, 		{COMM_HAVE_RETURN,           COMMTYPE_STAEPARA_RIGHTADDR}},
    {COMMTYPE_CLEARMD,           CommClearMD,            	{COMM_HAVE_RETURN,       COMMTYPE_STAEPARA_RIGHTADDR}},
    {COMMTYPE_CLEAREC,           CommClearEC,            	{COMM_HAVE_RETURN,       COMMTYPE_STAEPARA_RIGHTADDR}},
    {COMMTYPE_CLEAREVEN,         CommClearEven,  			{COMM_HAVE_RETURN,               COMMTYPE_STAEPARA_RIGHTADDR}},
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
    {COMMTYPE_RELAYSET,    		 CommRelaySet,				{COMM_HAVE_RETURN,	COMMTYPE_STAEPARA_RIGHTADDR}},
#endif  
    {COMMTYPE_MULTIPORT, 		CommMultiPort,  			{COMM_HAVE_RETURN,COMMTYPE_STAEPARA_BROADCAST_ADDR+COMMTYPE_STAEPARA_RIGHTADDR}},
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
    ////安全认证
    {COMMTYPE_FARCTL,  		CommFarCtl, 					{COMM_HAVE_NO_RETURN,    COMMTYPE_STAEPARA_RIGHTADDR}},                
#endif   
    // 液晶查询
    {COMMTYPE_DISPLAY    , 		CommDisplayNO,				{COMM_HAVE_NO_RETURN,  COMMTYPE_STAEPARA_BROADCAST_ADDR+COMMTYPE_STAEPARA_RIGHTADDR+COMMTYPE_STAEPARA_ALLAA_ADDR+COMMTYPE_STAEPARA_AA_ADDR}},                
    // 数据查询
    {COMMTYPE_DLTDATA,    		CommReadDLT07Data,			{COMM_HAVE_NO_RETURN,  COMMTYPE_STAEPARA_BROADCAST_ADDR+COMMTYPE_STAEPARA_RIGHTADDR+COMMTYPE_STAEPARA_ALLAA_ADDR+COMMTYPE_STAEPARA_AA_ADDR}},                
    // 载波
    {COMMTYPE_ZB,    			CommControlZB,				{COMM_HAVE_RETURN,               COMMTYPE_STAEPARA_BROADCAST_ADDR+COMMTYPE_STAEPARA_RIGHTADDR}},
};

////所有读出数据的大类数据表
COMM_CONST     STR_TABLE_BLOCK_TYPE  TableCommReadBlock[]=
{
        {COMM_READ_TYPE_EC,CommReadECData},
        {COMM_READ_TYPE_MD,CommReadMDData},
        {COMM_READ_TYPE_VARIANLE,CommVariableData},   
        {COMM_READ_TYPE_EVEN,CommEvenRecordData},
        {COMM_READ_TYPE_PARA,CommReadParaData},
        {COMM_READ_TYPE_FREEZE,CommReadFeezeData},
        {COMM_READ_TYPE_LOAD,CommReadLoadData},
        {COMM_READ_TYPE_ZEROFEEZE,CommReadFeezeZeroData},
                
};

/////电量数据的大块分类(合相,A,B,C) 主要是区别这些项是否有费率项数
COMM_CONST    STR_EC_BLOCK_PHASE_ID   TableCommPhaseBlock[]=
{
    {0x00,0x0A},      ///合相     
    {0x15,0x1E},       ///A
    {0x29,0x32},       ///B
    {0x3D,0x46},       ///C
    /////特殊电量数据(谐波电能,基波电能...)的大块分类(合相,A,B,C) 主要是区别这些项是否有费率项数
    {0x80,0x86},    ///合相
    {0x94,0x9A},    ///A
    {0xA8,0xAE},    ///B
    {0xBC,0xC2},    //C
        
    ////卡表数据
    {0x90,0x90},
    {0x0B,0x0B},
};

COMM_CONST  char PhaseIDOffset[3]={0x00,0x14,0x28};
#if 0
/////电量小类列表(DI2)
COMM_CONST    STR_EC_BLOCK_ID    TableReadECBlock[]=
{
  //总, 
  //当前电量是否存在该项(0无,1有),
  //当前电量项是否包含费率元素(0无,1有),
  //历史电量是否存在该项(0无,1有),
  //历史电量该项是否有费率
  //当前需量是否存在该项(0无,1有),
  //当前需量项是否包含费率元素(0无,1有),
  //历史需量是否存在该项(0无,1有),
  //历史需量该项是否有费率
{0x00,1,1,1,1,0,0,0,0,RAM_KWH_C_ALL,NULLDATAADDR},     //当前组合有功总电量,
{0x01,1,1,1,1,1,1,1,1,RAM_KWH_F_ALL,RAM_KW_F_ALL_DATA},     //当前正向有功总电量,当前正向有功总最大需量
{0x02,1,1,1,1,1,1,1,1,RAM_KWH_R_ALL,RAM_KW_R_ALL_DATA},     //当前反向有功总电量,当前反向有功总最大需量
{0x03,1,1,1,1,1,1,1,1,RAM_KVARH_C1_ALL,RAM_KVAR_C1_ALL_DATA},     //当前组合无功1总电量,当前组合1无功总最大需量
{0x04,1,1,1,1,1,1,1,1,RAM_KVARH_C2_ALL,RAM_KVAR_C2_ALL_DATA},     //当前组合无功2总电量,当前组合2无功总最大需量
{0x05,1,1,1,1,1,1,1,1,RAM_KVARH_Q1_ALL,RAM_KVAR_Q1_ALL_DATA},     //当前1象限无功总电量,当前1象限无功总最大需量
{0x06,1,1,1,1,1,1,1,1,RAM_KVARH_Q2_ALL,RAM_KVAR_Q2_ALL_DATA},     //当前2象限无功总电量,当前2象限无功总最大需量
{0x07,1,1,1,1,1,1,1,1,RAM_KVARH_Q3_ALL,RAM_KVAR_Q3_ALL_DATA},     //当前3象限无功总电量,当前3象限无功总最大需量
{0x08,1,1,1,1,1,1,1,1,RAM_KVARH_Q4_ALL,RAM_KVAR_Q4_ALL_DATA},     //当前4象限无功总电量,当前4象限无功总最大需量
//{0x09,1,1,1,1,1,1,1,1,RAM_KVAH_F_ALL,RAM_KVA_F_ALL_DATA},     //当前正向视在总电量,当前正向视在总最大需量
//{0x0A,1,1,1,1,1,1,1,1,RAM_KVAH_R_ALL,RAM_KVA_R_ALL_DATA},     //当前反向视在总电量,当前反向视在总最大需量
//{0x0B,1,0,1,0,0,0,0,0,RAM_KWH_C_USE_ALL,NULLDATAADDR},    
{0x80,0,0,0,0,0,0,0,0,NULLDATAADDR,NULLDATAADDR},     //当前关联总电能,
{0x81,0,0,0,0,0,0,0,0,NULLDATAADDR,NULLDATAADDR},     //当前正向有功基波总电能,
{0x82,0,0,0,0,0,0,0,0,NULLDATAADDR,NULLDATAADDR},     //当前反向有功基波总电能,
{0x83,0,0,0,0,0,0,0,0,NULLDATAADDR,NULLDATAADDR},     //当前正向有功谐波总电能,
{0x84,0,0,0,0,0,0,0,0,NULLDATAADDR,NULLDATAADDR},     //当前反向有功谐波总电能,
//{0x85,1,0,1,0,0,0,0,0,RAM_KWH_LOST_COPPER_ALL,NULLDATAADDR},     //铜损有功总电能补偿量,
//{0x86,1,0,1,0,0,0,0,0,RAM_KWH_LOST_IRON_ALL,NULLDATAADDR},     //铁损有功总电能补偿量,
{0x15,1,0,1,0,1,0,1,0,RAM_KWH_A_F_ALL,NULLDATAADDR},     //当前A相正相有功电量,当前A相正相有功最大需量
{0x16,1,0,1,0,1,0,1,0,RAM_KWH_A_R_ALL,NULLDATAADDR},     //当前A相反相有功电量,当前A相反相有功最大需量
//{0x17,1,0,1,0,1,0,1,0,RAM_KVARH_A_C1_ALL,RAM_KVAR_A_C1_ALL_DATA},     //当前A相组合无功1电量,当前A相组合1无功最大需量
//{0x18,1,0,1,0,1,0,1,0,RAM_KVARH_A_C2_ALL,RAM_KVAR_A_C2_ALL_DATA},     //当前A相组合无功2电量,当前A相组合2无功最大需量
//{0x19,1,0,1,0,1,0,1,0,RAM_KVARH_A_Q1_ALL,RAM_KVAR_A_Q1_ALL_DATA},     //当前A相1象限无功电量,当前A相1象限无功最大需量
//{0x1A,1,0,1,0,1,0,1,0,RAM_KVARH_A_Q2_ALL,RAM_KVAR_A_Q2_ALL_DATA},     //当前A相2象限无功电量,当前A相2象限无功最大需量
//{0x1B,1,0,1,0,1,0,1,0,RAM_KVARH_A_Q3_ALL,RAM_KVAR_A_Q3_ALL_DATA},     //当前A相3象限无功电量,当前A相3象限无功最大需量
//{0x1C,1,0,1,0,1,0,1,0,RAM_KVARH_A_Q4_ALL,RAM_KVAR_A_Q4_ALL_DATA},     //当前A相4象限无功电量,当前A相4象限无功最大需量
//{0x1D,1,0,1,0,1,0,1,0,RAM_KVAH_A_F_ALL,RAM_KVA_A_F_ALL_DATA},     //当前A相正相视在电量,当前A相正相视在最大需量
//{0x1E,1,0,1,0,1,0,1,0,RAM_KVAH_A_R_ALL,RAM_KVA_A_R_ALL_DATA},     //当前A相反相视在电量,当前A相反相视在最大需量
{0x94,0,0,0,0,0,0,0,0,NULLDATAADDR,NULLDATAADDR},     //当前A相关联电能,
{0x95,0,0,0,0,0,0,0,0,NULLDATAADDR,NULLDATAADDR},     //当前A相正向有功基波电能,
{0x96,0,0,0,0,0,0,0,0,NULLDATAADDR,NULLDATAADDR},     //当前A相反向有功基波电能,
{0x97,0,0,0,0,0,0,0,0,NULLDATAADDR,NULLDATAADDR},     //当前A相正向有功谐波电能,
{0x98,0,0,0,0,0,0,0,0,NULLDATAADDR,NULLDATAADDR},     //当前A相反向有功谐波电能,
//{0x99,1,0,1,0,0,0,0,0,RAM_KWH_A_LOST_COPPER_ALL,NULLDATAADDR},     //当前A相铜损有功电能补偿量,
//{0x9A,1,0,1,0,0,0,0,0,RAM_KWH_A_LOST_IRON_ALL,NULLDATAADDR},     //当前A相铁损有功电能补偿量,
{0x29,1,0,1,0,1,0,1,0,RAM_KWH_B_F_ALL,NULLDATAADDR},     //当前B相正相有功电量,当前B相正相有功最大需量
{0x2A,1,0,1,0,1,0,1,0,RAM_KWH_B_R_ALL,NULLDATAADDR},     //当前B相反相有功电量,当前B相反相有功最大需量
//0x2B,1,0,1,0,1,0,1,0,RAM_KVARH_B_C1_ALL,RAM_KVAR_B_C1_ALL_DATA,     //当前B相组合无功1电量,当前B相组合1无功最大需量
//0x2C,1,0,1,0,1,0,1,0,RAM_KVARH_B_C2_ALL,RAM_KVAR_B_C2_ALL_DATA,     //当前B相组合无功2电量,当前B相组合2无功最大需量
//0x2D,1,0,1,0,1,0,1,0,RAM_KVARH_B_Q1_ALL,RAM_KVAR_B_Q1_ALL_DATA,     //当前B相1象限无功电量,当前B相1象限无功最大需量
//0x2E,1,0,1,0,1,0,1,0,RAM_KVARH_B_Q2_ALL,RAM_KVAR_B_Q2_ALL_DATA,     //当前B相2象限无功电量,当前B相2象限无功最大需量
//0x2F,1,0,1,0,1,0,1,0,RAM_KVARH_B_Q3_ALL,RAM_KVAR_B_Q3_ALL_DATA,     //当前B相3象限无功电量,当前B相3象限无功最大需量
//0x30,1,0,1,0,1,0,1,0,RAM_KVARH_B_Q4_ALL,RAM_KVAR_B_Q4_ALL_DATA,     //当前B相4象限无功电量,当前B相4象限无功最大需量
//0x31,1,0,1,0,1,0,1,0,RAM_KVAH_B_F_ALL,RAM_KVA_B_F_ALL_DATA,     //当前B相正相视在电量,当前B相正相视在最大需量
//0x32,1,0,1,0,1,0,1,0,RAM_KVAH_B_R_ALL,RAM_KVA_B_R_ALL_DATA,     //当前B相反相视在电量,当前B相反相视在最大需量
0xA8,0,0,0,0,0,0,0,0,NULLDATAADDR,NULLDATAADDR,     //当前B相关联电能,
0xA9,0,0,0,0,0,0,0,0,NULLDATAADDR,NULLDATAADDR,     //当前B相正向有功基波电能,
0xAA,0,0,0,0,0,0,0,0,NULLDATAADDR,NULLDATAADDR,     //当前B相反向有功基波电能,
0xAB,0,0,0,0,0,0,0,0,NULLDATAADDR,NULLDATAADDR,     //当前B相正向有功谐波电能,
0xAC,0,0,0,0,0,0,0,0,NULLDATAADDR,NULLDATAADDR,     //当前B相反向有功谐波电能,
//0xAD,1,0,1,0,0,0,0,0,RAM_KWH_B_LOST_COPPER_ALL,NULLDATAADDR,     //当前B相铜损有功电能补偿量,
//0xAE,1,0,1,0,0,0,0,0,RAM_KWH_B_LOST_IRON_ALL,NULLDATAADDR,     //当前B相铁损有功电能补偿量,
0x3D,1,0,1,0,1,0,1,0,RAM_KWH_C_F_ALL,NULLDATAADDR,     //当前C相正相有功电量,当前C相正相有功最大需量
0x3E,1,0,1,0,1,0,1,0,RAM_KWH_C_R_ALL,NULLDATAADDR,     //当前C相反相有功电量,当前C相反相有功最大需量
//0x3F,1,0,1,0,1,0,1,0,RAM_KVARH_C_C1_ALL,RAM_KVAR_C_C1_ALL_DATA,     //当前C相组合无功1电量,当前C相组合1无功最大需量
//0x40,1,0,1,0,1,0,1,0,RAM_KVARH_C_C2_ALL,RAM_KVAR_C_C2_ALL_DATA,     //当前C相组合无功2电量,当前C相组合2无功最大需量
//0x41,1,0,1,0,1,0,1,0,RAM_KVARH_C_Q1_ALL,RAM_KVAR_C_Q1_ALL_DATA,     //当前C相1象限无功电量,当前C相1象限无功最大需量
//0x42,1,0,1,0,1,0,1,0,RAM_KVARH_C_Q2_ALL,RAM_KVAR_C_Q2_ALL_DATA,     //当前C相2象限无功电量,当前C相2象限无功最大需量
//0x43,1,0,1,0,1,0,1,0,RAM_KVARH_C_Q3_ALL,RAM_KVAR_C_Q3_ALL_DATA,     //当前C相3象限无功电量,当前C相3象限无功最大需量
//0x44,1,0,1,0,1,0,1,0,RAM_KVARH_C_Q4_ALL,RAM_KVAR_C_Q4_ALL_DATA,     //当前C相4象限无功电量,当前C相4象限无功最大需量
//0x45,1,0,1,0,1,0,1,0,RAM_KVAH_C_F_ALL,RAM_KVA_C_F_ALL_DATA,     //当前C相正相视在电量,当前C相正相视在最大需量
//0x46,1,0,1,0,1,0,1,0,RAM_KVAH_C_R_ALL,RAM_KVA_C_R_ALL_DATA,     //当前C相反相视在电量,当前C相反相视在最大需量
0xBC,0,0,0,0,0,0,0,0,NULLDATAADDR,NULLDATAADDR,     //当前C相关联电能,
0xBD,0,0,0,0,0,0,0,0,NULLDATAADDR,NULLDATAADDR,     //当前C相正向有功基波电能,
0xBE,0,0,0,0,0,0,0,0,NULLDATAADDR,NULLDATAADDR,     //当前C相反向有功基波电能,
0xBF,0,0,0,0,0,0,0,0,NULLDATAADDR,NULLDATAADDR,     //当前C相正向有功谐波电能,
0xC0,0,0,0,0,0,0,0,0,NULLDATAADDR,NULLDATAADDR,     //当前C相反向有功谐波电能,
//0xC1,1,0,1,0,0,0,0,0,RAM_KWH_C_LOST_COPPER_ALL,NULLDATAADDR,     //当前C相铜损有功电能补偿量,
//0xC2,1,0,1,0,0,0,0,0,RAM_KWH_C_LOST_IRON_ALL,NULLDATAADDR,     //当前C相铁损有功电能补偿量,

};
#endif
/*
// aa changed by zhanglong ----2009-10-17----beijing---->start 
COMM_CONST  STR_EC_CARD_ID  TableCardEner[]=
{      
    //0x01, 0x00, COMM_USE, 4, 
    // aa 当前剩余金额aa
    0x02,0x00,COMM_USE,4,4,EPL_PREPAY_REMAIN_ENERGY,
    // AA  当前透支金额  AA
    0x02,0x01,COMM_USE,4,4,EPL_PREPAY_TICK_ENERGY,
    
    0x03,0x00,COMM_USE,4,5,EPL_TOTAL_MONEY_BUY_ALL,
    0x03,0x01,COMM_USE,2,2,EPL_TOTAL_MONEY_BUY_COUNT
};
// aa changed by zhanglong ----2009-10-17----beijing---->End
u16  GetCardEnergyTableNum(void)
{
  return (sizeof(TableCardEner)/sizeof(STR_EC_CARD_ID));
}
*/


////变量的列表
#if 0
COMM_CONST   STR_VARIABLE_ID  TableVariable[]=
{
    {0x01,1,1,3,1,1,4,2,RAM_CURRENT_V_A},
	{0x02,1,1,3,1,1,4,3,RAM_CURRENT_I_A},
	{0x03,1,0,4,1,1,4,3,RAM_CURRENT_KW_ALL},
	{0x04,1,0,4,1,1,4,3,RAM_CURRENT_KVAR_ALL},
	{0x05,1,0,4,1,1,4,3,RAM_CURRENT_KVA_ALL},
	{0x06,1,0,4,1,1,4,2,RAM_CURRENT_FACTOR_ALL},
	{0x07,1,1,3,1,1,2,2,RAM_CURRENT_ANGLE_AV_AI},
#if(CONFIG_METER_HARMONIC_ENABLE == GAL_YES)    
    {x08,1,1,3,1,1,4,2,RAM_CURRENT_HARMONIC_PER_V_A_ALL},
    {x09,1,1,3,1,1,4,2,RAM_CURRENT_HARMONIC_PER_I_A_ALL},
    {x0A,1,1,3,0,21,2,2,RAM_CURRENT_HARMONIC_PER_V_A_01CI},
    {x0B,1,1,3,0,21,2,2,RAM_CURRENT_HARMONIC_PER_I_A_01CI},
    {x0C,1,0,3,1,22,2,2,RAM_CURRENT_HARMONIC_PER_V_A_01CI},
    {x0D,1,0,3,1,22,2,2,RAM_CURRENT_HARMONIC_PER_I_A_01CI},
#else    
	{0x08,0,1,3,1,1,4,2,NULLDATAADDR},
	{0x09,0,1,3,1,1,4,2,NULLDATAADDR},
	{0x0A,0,1,3,0,21,2,2,NULLDATAADDR},
	{0x0B,0,1,3,0,21,2,2,NULLDATAADDR},
    {0x0C,0,0,3,1,21,2,2,NULLDATAADDR},
    {0x0D,0,0,3,1,21,2,2,NULLDATAADDR},
#endif    
}; 

///变量中0x80这些比较特殊的
COMM_CONST   STR_VARIABLE_ESPECEIVE  TableVariableEscipe[]=
{
    0x01,1,3,4,RAM_CURRENT_I_NULLLINE,
0x02,1,2,6,RAM_CURRENT_FREQ_A,
0x03,1,3,4,RAM_AVERAGE_KW_ALL,
0x04,1,3,4,RAM_CURRENT_DEMAND_KW_TOTAL,
0x05,1,3,4,RAM_CURRENT_DEMAND_KVAR_TOTAL,
//0x06,1,3,4,RAM_CURRENT_DEMAND_KVA_TOTAL,
0x07,1,2,2,RAM_CURRENT_METER_TEMP,
0x08,1,2,2,RAM_CURRENT_CLOCK_VOLTAGE,
0x09,1,2,2,RAM_CURRENT_WAKEUP_VOLTAGE,
0x0A,1,4,4,EPL_CURRENT_BAT_USETIME,
#if(CONFIG_METER_STEP_PERIODPRICE_MODE==CONFIG_METER_STEP_PERIODPRICE_MODE_ENABLE)
0x0B,1,4,4,RAM_CURRENT_STEPPRICE_PRICE,
#endif      
};
#endif

//////////////////////////////////////////////////////////
////事件分类(ID2的大类区分)
COMM_CONST STR_COMM_EVENTYPE TableCommEvenType[]=
{
    {0x01,0x0F,COMM_EVEN_BLOCK_FAILURE,COMM_USE},     ////故障事件类
    {0x11,0x11,COMM_EVEN_BLOCK_FAILURE,COMM_USE},      ////故障事件类
    {0x10,0x10,COMM_EVEN_BLOCK_VOLTAGE_CHECKOUT,COMM_USE}, ///电压合格率事件
    {0x12,0x12,COMM_EVEN_BLOCK_MD_OVER,COMM_USE},        //////需量超限类
    {0x30,0x30,COMM_EVEN_BLOCK_METER_HANDLE,COMM_USE},        /////电表操作类
        
    //0x31,0x31,COMM_EVEN_BLOCK_METER_CUTGATE,COMM_USE,    ////////拉合闸事件类
        
        //0x32,0x33,COMM_EVEN_BLOCK_CARD,COMM_USE,/////卡表操作类 ,del by zlq090922
};

////故障事件归类,事件COMM_EVEN_BLOCK_FAILURE,
COMM_CONST STR_COMM_EVEN_BLOCK_FAILURE      TableCommEvenFAILURE[]=
{
    //0x01,COMM_EVEN_TYPE_VOLTAGE,EPL_TOTAL_LOSS_AV_COUNT_TOTAL,COMM_EVEN_FAILURE_RECORD_TIM,COMM_EVEN_FAILURE_LOSEVOLTAGE_TOTAL,
    //0x02,COMM_EVEN_TYPE_VOLTAGE,EPL_TOTAL_DOWN_AV_COUNT_TOTAL,COMM_EVEN_FAILURE_RECORD_TIM,COMM_EVEN_FAILURE_LOSEVOLTAGE_TOTAL,
    //0x03,COMM_EVEN_TYPE_VOLTAGE,EPL_TOTAL_OVER_AV_COUNT_TOTAL,COMM_EVEN_FAILURE_RECORD_TIM,COMM_EVEN_FAILURE_LOSEVOLTAGE_TOTAL,
    //0x04,COMM_EVEN_TYPE_VOLTAGE,EPL_TOTAL_CUT_AV_COUNT_TOTAL,COMM_EVEN_FAILURE_RECORD_TIM,COMM_EVEN_FAILURE_LOSEVOLTAGE_TOTAL,
    {0x05,COMM_EVEN_TYPE_ALLLOSEVOLTAGE,RAM_ALLLOSS_VOLTAGE_COUNT,COMM_EVEN_FAILURE_RECORD_TIM,COMM_EVEN_FAILURE_ALL_LOSEVOLTAGE_TOTAL},
#if(CONFIG_METER_AUX_MODE==CONFIG_METER_AUX_MODE_ENABLE)
    {0x06,COMM_EVEN_TYPE_ASSISTANT_POWERLOSE,RAM_ACPOWER_LOSS_COUNT,COMM_EVEN_FAILURE_RECORD_TIM,COMM_EVEN_FAILURE_LOSE_ACPPOWER_TOTAL},
#endif
    //0x07,COMM_EVEN_TYPE_CONVERSE,EPL_TOTAL_ORDER_VOLTAGE_COUNT_TOTAL,COMM_EVEN_FAILURE_RECORD_TIM,COMM_EVEN_FAILURE_ALL_LOSEVOLTAGE_TOTAL,
    //0x08,COMM_EVEN_TYPE_CONVERSE,EPL_TOTAL_ORDER_CURRENT_COUNT_TOTAL,COMM_EVEN_FAILURE_RECORD_TIM,COMM_EVEN_FAILURE_ALL_LOSEVOLTAGE_TOTAL,
    //0x09,COMM_EVEN_TYPE_UNBLANCE,EPL_TOTAL_UNBALANCE_VOLTAGE_BLOCK_START,COMM_EVEN_FAILURE_RECORD_TIM,COMM_EVEN_FAILURE_ALL_LOSEVOLTAGE_TOTAL,
    //0x0A,COMM_EVEN_TYPE_UNBLANCE,EPL_TOTAL_UNBALANCE_CURRENT_BLOCK_START,COMM_EVEN_FAILURE_RECORD_TIM,COMM_EVEN_FAILURE_ALL_LOSEVOLTAGE_TOTAL,
    //0x0B,COMM_EVEN_TYPE_CURRENT_FAILUE,EPL_TOTAL_LOSS_AI_COUNT_TOTAL,COMM_EVEN_FAILURE_RECORD_TIM,COMM_EVEN_FAILURE_REVER_CURRENT_TOTAL,
    //0x0C,COMM_EVEN_TYPE_CURRENT_FAILUE,EPL_TOTAL_OVER_AI_COUNT_TOTAL,COMM_EVEN_FAILURE_RECORD_TIM,COMM_EVEN_FAILURE_REVER_CURRENT_TOTAL,
    //0x0D,COMM_EVEN_TYPE_CURRENT_FAILUE,EPL_TOTAL_CUT_AI_COUNT_TOTAL,COMM_EVEN_FAILURE_RECORD_TIM,COMM_EVEN_FAILURE_REVER_CURRENT_TOTAL,
    //0x0E,COMM_EVEN_TYPE_SWIM_OVERLOAD,EPL_TOTAL_REVERSE_A_COUNT_TOTAL,COMM_EVEN_FAILURE_RECORD_TIM,COMM_EVEN_FAILURE_LOSE_CURRENT_TOTAL,
    //0x0F,COMM_EVEN_TYPE_SWIM_OVERLOAD,EPL_TOTAL_POWEROVER_A_COUNT_TOTAL,COMM_EVEN_FAILURE_RECORD_TIM,COMM_EVEN_FAILURE_LOSE_CURRENT_TOTAL,
    {0x11,COMM_EVEN_TYPE_POWEROFF,EPL_POWER_DOWN_COUNT,COMM_EVEN_FAILURE_RECORD_TIM,COMM_EVEN_FAILURE_POWEROFF_TOTAL}
    
};


const S_CNTTIME gCS_CntAndTimeTab[] = 
{
    {0x10000001, EPL_TOTAL_LOSS_V_COUNT_TOTAL}, //失压总次数
    {0x10000002, RAM_TOTAL_LOSS_V_TIME_TOTAL},  //失压总累计时间
    {0x10010001, EPL_TOTAL_LOSS_AV_COUNT_TOTAL},    //A相失压总次数
    {0x10010002, RAM_TOTAL_LOSS_AV_TIME_TOTAL}, //A相失压总累计时间
    {0x10020001, EPL_TOTAL_LOSS_BV_COUNT_TOTAL},    //B相失压总次数
    {0x10020002, RAM_TOTAL_LOSS_BV_TIME_TOTAL}, //B相失压总累计时间
    {0x10030001, EPL_TOTAL_LOSS_CV_COUNT_TOTAL},    //C相失压总次数
    {0x10030002, RAM_TOTAL_LOSS_CV_TIME_TOTAL}, //C相失压总累计时间
    
    {0x11010001, EPL_TOTAL_DOWN_AV_COUNT_TOTAL},    //A相欠压总次数
    {0x11010002, RAM_TOTAL_DOWN_AV_TIME_TOTAL}, //A相欠压总累计时间
    {0x11020001, EPL_TOTAL_DOWN_BV_COUNT_TOTAL},    //B相欠压总次数
    {0x11020002, RAM_TOTAL_DOWN_BV_TIME_TOTAL}, //B相欠压总累计时间
    {0x11030001, EPL_TOTAL_DOWN_CV_COUNT_TOTAL},    //C相欠压总次数
    {0x11030002, RAM_TOTAL_DOWN_CV_TIME_TOTAL}, //C相欠压总累计时间
    
    {0x12010001, EPL_TOTAL_OVER_AV_COUNT_TOTAL},    //A相过压总次数
    {0x12010002, RAM_TOTAL_OVER_AV_TIME_TOTAL}, //A相过压总累计时间
    {0x12020001, EPL_TOTAL_OVER_BV_COUNT_TOTAL},    //B相过压总次数
    {0x12020002, RAM_TOTAL_OVER_BV_TIME_TOTAL}, //B相过压总累计时间
    {0x12030001, EPL_TOTAL_OVER_CV_COUNT_TOTAL},    //C相过压总次数
    {0x12030002, RAM_TOTAL_OVER_CV_TIME_TOTAL}, //C相过压总累计时间
    
    {0x13010001, EPL_TOTAL_CUT_AV_COUNT_TOTAL}, //A相断相总次数
    {0x13010002, RAM_TOTAL_CUT_AV_TIME_TOTAL},  //A相断相总累计时间
    {0x13020001, EPL_TOTAL_CUT_BV_COUNT_TOTAL}, //B相断相总次数
    {0x13020002, RAM_TOTAL_CUT_BV_TIME_TOTAL},  //B相断相总累计时间
    {0x13030001, EPL_TOTAL_CUT_CV_COUNT_TOTAL}, //C相断相总次数
    {0x13030002, RAM_TOTAL_CUT_CV_TIME_TOTAL},  //C相断相总累计时间
    
    {0x14000001, EPL_TOTAL_ORDER_VOLTAGE_COUNT_TOTAL},  //电压逆相序总次数
    {0x14000002, RAM_TOTAL_ORDER_VOLTAGE_TIME_TOTAL},   //电压逆相序总累计时间
    
    {0x15000001, EPL_TOTAL_ORDER_CURRENT_COUNT_TOTAL},  //电流逆相序总次数
    {0x15000002, RAM_TOTAL_ORDER_CURRENT_TIME_TOTAL},   //电流逆相序总累计时间
    
    {0x16000001, EPL_TOTAL_UNBALANCE_VOLTAGE_COUNT_TOTAL},  //电压不平衡总次数
    {0x16000002, RAM_TOTAL_UNBALANCE_VOLTAGE_TIME_TOTAL},   //电压不平衡总累计时间
    
    {0x17000001, EPL_TOTAL_UNBALANCE_CURRENT_COUNT_TOTAL},  //电流不平衡总次数
    {0x17000002, RAM_TOTAL_UNBALANCE_CURRENT_TIME_TOTAL},   //电流不平衡总累计时间
    
    {0x18010001, EPL_TOTAL_LOSS_AI_COUNT_TOTAL},    //A相失流总次数
    {0x18010002, RAM_TOTAL_LOSS_AI_TIME_TOTAL}, //A相失流总累计时间
    {0x18020001, EPL_TOTAL_LOSS_BI_COUNT_TOTAL},    //B相失流总次数
    {0x18020002, RAM_TOTAL_LOSS_BI_TIME_TOTAL}, //B相失流总累计时间
    {0x18030001, EPL_TOTAL_LOSS_CI_COUNT_TOTAL},    //C相失流总次数
    {0x18030002, RAM_TOTAL_LOSS_CI_TIME_TOTAL}, //C相失流总累计时间
    
    {0x19010001, EPL_TOTAL_OVER_AI_COUNT_TOTAL},    //A相过流总次数
    {0x19010002, RAM_TOTAL_OVER_AI_TIME_TOTAL}, //A相过流总累计时间
    {0x19020001, EPL_TOTAL_OVER_BI_COUNT_TOTAL},    //B相过流总次数
    {0x19020002, RAM_TOTAL_OVER_BI_TIME_TOTAL}, //B相过流总累计时间
    {0x19030001, EPL_TOTAL_OVER_CI_COUNT_TOTAL},    //C相过流总次数
    {0x19030002, RAM_TOTAL_OVER_CI_TIME_TOTAL}, //C相过流总累计时间
    
    {0x1A010001, EPL_TOTAL_CUT_AI_COUNT_TOTAL}, //A相断流总次数
    {0x1A010002, RAM_TOTAL_CUT_AI_TIME_TOTAL},  //A相断流总累计时间
    {0x1A020001, EPL_TOTAL_CUT_BI_COUNT_TOTAL}, //B相断流总次数
    {0x1A020002, RAM_TOTAL_CUT_BI_TIME_TOTAL},  //B相断流总累计时间
    {0x1A030001, EPL_TOTAL_CUT_CI_COUNT_TOTAL}, //C相断流总次数
    {0x1A030002, RAM_TOTAL_CUT_CI_TIME_TOTAL},  //C相断流总累计时间
    
    {0x1B010001, EPL_TOTAL_REVERSE_A_COUNT_TOTAL},  //A相潮流总次数
    {0x1B010002, RAM_TOTAL_REVERSE_A_TIME_TOTAL},   //A相潮流总累计时间
    {0x1B020001, EPL_TOTAL_REVERSE_B_COUNT_TOTAL},  //B相潮流总次数
    {0x1B020002, RAM_TOTAL_REVERSE_B_TIME_TOTAL},   //B相潮流总累计时间
    {0x1B030001, EPL_TOTAL_REVERSE_C_COUNT_TOTAL},  //C相潮流总次数
    {0x1B030002, RAM_TOTAL_REVERSE_C_TIME_TOTAL},   //C相潮流总累计时间
    
    {0x1C010001, EPL_TOTAL_POWEROVER_A_COUNT_TOTAL},    //A相过载总次数
    {0x1C010002, RAM_TOTAL_POWEROVER_A_TIME_TOTAL}, //A相过载总累计时间
    {0x1C020001, EPL_TOTAL_POWEROVER_B_COUNT_TOTAL},    //B相过载总次数
    {0x1C020002, RAM_TOTAL_POWEROVER_B_TIME_TOTAL}, //B相过载总累计时间
    {0x1C030001, EPL_TOTAL_POWEROVER_C_COUNT_TOTAL},    //C相过载总次数
    {0x1C030002, RAM_TOTAL_POWEROVER_C_TIME_TOTAL}, //C相过载总累计时间
    
#if(CONFIG_METER_RELAY_MODE_DISABLE!=CONFIG_METER_RELAY_MODE)
    {0x1D000001, EPL_TOTAL_RELAY_OPEN_COUNT},           //跳闸次数
    {0x1E000001, EPL_TOTAL_RELAY_CLOSE_COUNT},          //合闸次数
#endif  

    {0x1F000001, EPL_TOTAL_OVERTOTALCOS_COUNT_TOTAL},   //总功率因数超下限总次数
    {0x1F000002, RAM_TOTAL_OVERTOTALCOS_TIME_TOTAL},    //总功率因数超下限总累计时间
#if(CONFIG_METER_TYPE==CONFIG_METER_TYPE_SD39C)
    {0x20000001, EPL_TOTAL_BROADCASTTIME_COUNT},    //
    {0x20000002, EPL_TOTAL_BROADCASTTIME_TIME}, //
#endif
};

const uchar gCuc_CntAndTimeTabNum = sizeof(gCS_CntAndTimeTab) / sizeof(S_CNTTIME);


const S_EVFMT gCs_EvFmt1[] =    //失压,欠压,过压,断相等数据格式表
{
    {0,     6, 0},                 //发生时刻
    {7,     4, 1},                 //失压发生时刻正向有功总电能,取两位小数点,故偏移取7
    {12,    4, 1},                 //失压发生时刻反向有功总电能
    {17,    4, 1},                 //发生时刻组合无功1
    {22,    4, 1},                 //发生时刻组合无功2
    
    {27,    4, 1},                 //发生时刻A相正有功
    {32,    4, 1},                 //发生时刻A相反有功
    {37,    4, 1},                 //发生时刻A相组合无功1
    {42,    4, 1},                 //发生时刻A相组合无功2
    {46,    2, 0},                 //A相电压
    {48,    3, 0},                 //A相电流
    {51,    3, 0},                 //A相有功功率
    {54,    3, 0},                 //A相无功功率
    {57,    2, 0},                 //A相功率因数
    
    {60,    4, 1},                 //发生时刻B相正有功
    {65,    4, 1},                 //发生时刻B相反有功
    {70,    4, 1},                 //发生时刻B相组合无功1
    {75,    4, 1},                 //发生时刻B相组合无功2
    {79,    2, 0},                 //B相电压
    {81,    3, 0},                 //B相电流
    {84,    3, 0},                 //B相有功功率
    {87,    3, 0},                 //B相无功功率
    {90,    2, 0},                 //B相功率因数
    
    {93,    4, 1},                 //发生时刻C相正有功
    {98,    4, 1},                 //发生时刻C相反有功
    {103,   4, 1},                 //发生时刻C相组合无功1
    {108,   4, 1},                 //发生时刻C相组合无功2
    {112,   2, 0},                 //C相电压
    {114,   3, 0},                 //C相电流
    {117,   3, 0},                 //C相有功功率
    {120,   3, 0},                 //C相无功功率
    {123,   2, 0},                 //C相功率因数
    
    {126,   4, 1},                 //失压期间总安时数
    {131,   4, 1},                 //失压期间A相安时数
    {136,   4, 1},                 //失压期间B相安时数
    {141,   4, 1},                 //失压期间C相安时数
    
    {145,   6, 0},                 //结束时刻
    {152,   4, 1},                 //失压结束时刻正向有功总电能
    {157,   4, 1},                 //失压结束时刻反向有功总电能
    {162,   4, 1},                 //结束时刻组合无功1
    {167,   4, 1},                 //结束时刻组合无功2
    
    {172,   4, 1},                 //结束时刻A相正有功
    {177,   4, 1},                 //结束时刻A相反有功
    {182,   4, 1},                 //结束时刻A相组合无功1
    {187,   4, 1},                 //结束时刻A相组合无功2
    
    {192,   4, 1},                 //结束时刻B相正有功
    {197,   4, 1},                 //结束时刻B相反有功
    {202,   4, 1},                 //结束时刻B相组合无功1
    {207,   4, 1},                 //结束时刻B相组合无功2
    
    {212,   4, 1},                 //结束时刻C相正有功
    {217,   4, 1},                 //结束时刻C相反有功
    {222,   4, 1},                 //结束时刻C相组合无功1
    {227,   4, 1},                 //结束时刻C相组合无功2
};
const S_EVFMT gCs_EvFmt2[] =    //失流,过流,断流等数据格式表
{
    {0,     6, 0},                 //发生时刻
    {7,     4, 1},                 //失压发生时刻正向有功总电能,取两位小数点,故偏移取7
    {12,    4, 1},                 //失压发生时刻反向有功总电能
    {17,    4, 1},                 //发生时刻组合无功1
    {22,    4, 1},                 //发生时刻组合无功2
    
    {27,    4, 1},                 //发生时刻A相正有功
    {32,    4, 1},                 //发生时刻A相反有功
    {37,    4, 1},                 //发生时刻A相组合无功1
    {42,    4, 1},                 //发生时刻A相组合无功2
    {46,    2, 0},                 //A相电压
    {48,    3, 0},                 //A相电流
    {51,    3, 0},                 //A相有功功率
    {54,    3, 0},                 //A相无功功率
    {57,    2, 0},                 //A相功率因数
    
    {60,    4, 1},                 //发生时刻B相正有功
    {65,    4, 1},                 //发生时刻B相反有功
    {70,    4, 1},                 //发生时刻B相组合无功1
    {75,    4, 1},                 //发生时刻B相组合无功2
    {79,    2, 0},                 //B相电压
    {81,    3, 0},                 //B相电流
    {84,    3, 0},                 //B相有功功率
    {87,    3, 0},                 //B相无功功率
    {90,    2, 0},                 //B相功率因数
    
    {93,    4, 1},                 //发生时刻C相正有功
    {98,    4, 1},                 //发生时刻C相反有功
    {103,   4, 1},                 //发生时刻C相组合无功1
    {108,   4, 1},                 //发生时刻C相组合无功2
    {112,   2, 0},                 //C相电压
    {114,   3, 0},                 //C相电流
    {117,   3, 0},                 //C相有功功率
    {120,   3, 0},                 //C相无功功率
    {123,   2, 0},                 //C相功率因数
    
    {125,   6, 0},                 //结束时刻
    {132,   4, 1},                 //失压结束时刻正向有功总电能
    {137,   4, 1},                 //失压结束时刻反向有功总电能
    {142,   4, 1},                 //结束时刻组合无功1
    {147,   4, 1},                 //结束时刻组合无功2
    
    {152,   4, 1},                 //结束时刻A相正有功
    {157,   4, 1},                 //结束时刻A相反有功
    {162,   4, 1},                 //结束时刻A相组合无功1
    {167,   4, 1},                 //结束时刻A相组合无功2
    
    {172,   4, 1},                 //结束时刻B相正有功
    {177,   4, 1},                 //结束时刻B相反有功
    {182,   4, 1},                 //结束时刻B相组合无功1
    {187,   4, 1},                 //结束时刻B相组合无功2
    
    {192,   4, 1},                 //结束时刻C相正有功
    {197,   4, 1},                 //结束时刻C相反有功
    {202,   4, 1},                 //结束时刻C相组合无功1
    {207,   4, 1},                 //结束时刻C相组合无功2
};
const S_EVFMT gCs_EvFmt3[] =    //电压逆相序,电流逆相序,潮流,过载等数据格式表
{
    {0,     6, 0},                 //发生时刻
    {7,     4, 1},                 //发生时刻正向有功总电能,取两位小数点,故偏移取7
    {12,    4, 1},                 //发生时刻反向有功总电能
    {17,    4, 1},                 //发生时刻组合无功1
    {22,    4, 1},                 //发生时刻组合无功2
    
    {27,    4, 1},                 //发生时刻A相正有功
    {32,    4, 1},                 //发生时刻A相反有功
    {37,    4, 1},                 //发生时刻A相组合无功1
    {42,    4, 1},                 //发生时刻A相组合无功2

    {60,    4, 1},                 //发生时刻B相正有功
    {65,    4, 1},                 //发生时刻B相反有功
    {70,    4, 1},                 //发生时刻B相组合无功1
    {75,    4, 1},                 //发生时刻B相组合无功2

    {93,    4, 1},                 //发生时刻C相正有功
    {98,    4, 1},                 //发生时刻C相反有功
    {103,   4, 1},                 //发生时刻C相组合无功1
    {108,   4, 1},                 //发生时刻C相组合无功2
    
    {125,   6, 0},                 //结束时刻
    {132,   4, 1},                 //结束时刻正向有功总电能
    {137,   4, 1},                 //结束时刻反向有功总电能
    {142,   4, 1},                 //结束时刻组合无功1
    {147,   4, 1},                 //结束时刻组合无功2
    
    {152,   4, 1},                 //结束时刻A相正有功
    {157,   4, 1},                 //结束时刻A相反有功
    {162,   4, 1},                 //结束时刻A相组合无功1
    {167,   4, 1},                 //结束时刻A相组合无功2
    
    {172,   4, 1},                 //结束时刻B相正有功
    {177,   4, 1},                 //结束时刻B相反有功
    {182,   4, 1},                 //结束时刻B相组合无功1
    {187,   4, 1},                 //结束时刻B相组合无功2
    
    {192,   4, 1},                 //结束时刻C相正有功
    {197,   4, 1},                 //结束时刻C相反有功
    {202,   4, 1},                 //结束时刻C相组合无功1
    {207,   4, 1},                 //结束时刻C相组合无功2
};
const S_EVFMT gCs_EvFmt4[] =    //电压不平衡,电流不平衡等数据格式表
{
    {0,     6, 0},                 //发生时刻
    {7,     4, 1},                 //发生时刻正向有功总电能,取两位小数点,故偏移取7
    {12,    4, 1},                 //发生时刻反向有功总电能
    {17,    4, 1},                 //发生时刻组合无功1
    {22,    4, 1},                 //发生时刻组合无功2
    
    {27,    4, 1},                 //发生时刻A相正有功
    {32,    4, 1},                 //发生时刻A相反有功
    {37,    4, 1},                 //发生时刻A相组合无功1
    {42,    4, 1},                 //发生时刻A相组合无功2

    {60,    4, 1},                 //发生时刻B相正有功
    {65,    4, 1},                 //发生时刻B相反有功
    {70,    4, 1},                 //发生时刻B相组合无功1
    {75,    4, 1},                 //发生时刻B相组合无功2

    {93,    4, 1},                 //发生时刻C相正有功
    {98,    4, 1},                 //发生时刻C相反有功
    {103,   4, 1},                 //发生时刻C相组合无功1
    {108,   4, 1},                 //发生时刻C相组合无功2
    
    {125,   3, 0},                 //期间最大不平衡率
    
    {128,   6, 0},                 //结束时刻
    {135,   4, 1},                 //结束时刻正向有功总电能
    {140,   4, 1},                 //结束时刻反向有功总电能
    {145,   4, 1},                 //结束时刻组合无功1
    {150,   4, 1},                 //结束时刻组合无功2
    
    {155,   4, 1},                 //结束时刻A相正有功
    {160,   4, 1},                 //结束时刻A相反有功
    {165,   4, 1},                 //结束时刻A相组合无功1
    {170,   4, 1},                 //结束时刻A相组合无功2
    
    {175,   4, 1},                 //结束时刻B相正有功
    {180,   4, 1},                 //结束时刻B相反有功
    {185,   4, 1},                 //结束时刻B相组合无功1
    {190,   4, 1},                 //结束时刻B相组合无功2
    
    {195,   4, 1},                 //结束时刻C相正有功
    {200,   4, 1},                 //结束时刻C相反有功
    {205,   4, 1},                 //结束时刻C相组合无功1
    {210,   4, 1},                 //结束时刻C相组合无功2
};
const S_EVFMT gCs_EvFmt5[] =    //拉闸,合闸等数据格式表
{
    {0,     6, 0},                 //发生时刻
    {6,     4, 0},                 //操作者代码
    {11,    4, 1},                 //正有功总
    {16,    4, 1},                 //反有功总
    {21,    4, 1},                 //一象限无功总
    {26,    4, 1},                 //二象限无功总
    {31,    4, 1},                 //三象限无功总
    {36,    4, 1},                 //四象限无功总
};

const S_EVFMT gCs_EvFmt6[] =    //功率因数超下限等数据格式表
{
    {0,     6, 0},                 //发生时刻
    {7,     4, 1},                 //正有功总
    {12,    4, 1},                 //反有功总
    {17,    4, 1},                 //组合无功1总
    {22,    4, 1},                 //组合无功2总
    
    {125,   6, 0},                 //结束时间
    {132,   4, 1},                 //正有功总
    {137,   4, 1},                 //反有功总
    {142,   4, 1},                 //组合无功1总
    {147,   4, 1},                 //组合无功2总
};

const S_EVFMT gCs_EvFmt7[] =    //购电电量,购电金额等数据格式表
{
    {1,     5, 0},                 // aa  购电日期 aa
    {6,     2, 0},                 // aa  购电后总购电次数  aa
    {10,    4, 0},                 // aa  本次购电金额  aa
    {14,    4, 0},                 // aa  购电前剩余金额  aa
    {18,    4, 0},                 // aa  购电后剩余金额  aa
    {22,    4, 0},                 // aa  累计购电金额  aa
};
const S_EVFMT gCs_EvFmt20[] =   
{
    {0,     6,0},                
    {6,     6,0},              
    {12,    2,0},            
};

//这个表的id必须从小到大排列
const S_IDCONV1 gCs_IDConv1[] = 
{
//    {0x03320000, 0x06, 0x09, TYPE_BUY_KWH_RECORD,               0x00, (void*)gCs_EvFmt7}, //上1-10次购电电量信息
#if(CONFIG_METER_STEP_PERIODPRICE_MODE==CONFIG_METER_STEP_PERIODPRICE_MODE_ENABLE)
    {0x03330000, 0x06, 0x09, TYPE_BUY_MONEY_RECORD,             0x00, (void*)gCs_EvFmt7},   //上1-10次购电金额信息
#endif

    {0x10010000, 0x35, 0x09, TYPE_LOSS_A_VOLTAGE_RECORD,        0x00, (void*)gCs_EvFmt1},   //上1-10次A相失压记录
    {0x10020000, 0x35, 0x09, TYPE_LOSS_B_VOLTAGE_RECORD,        0x00, (void*)gCs_EvFmt1},   //上1-10次B相失压记录
    {0x10030000, 0x35, 0x09, TYPE_LOSS_C_VOLTAGE_RECORD,        0x00, (void*)gCs_EvFmt1},   //上1-10次C相失压记录

    {0x11010000, 0x35, 0x09, TYPE_DOWN_A_VOLTAGE_RECORD,        0x00, (void*)gCs_EvFmt1},   //上1-10次A相欠压记录
    {0x11020000, 0x35, 0x09, TYPE_DOWN_B_VOLTAGE_RECORD,        0x00, (void*)gCs_EvFmt1},   //上1-10次B相欠压记录
    {0x11030000, 0x35, 0x09, TYPE_DOWN_C_VOLTAGE_RECORD,        0x00, (void*)gCs_EvFmt1},   //上1-10次C相欠压记录
    
    {0x12010000, 0x35, 0x09, TYPE_OVER_A_VOLTAGE_RECORD,        0x00, (void*)gCs_EvFmt1},   //上1-10次A相过压记录
    {0x12020000, 0x35, 0x09, TYPE_OVER_B_VOLTAGE_RECORD,        0x00, (void*)gCs_EvFmt1},   //上1-10次B相过压记录
    {0x12030000, 0x35, 0x09, TYPE_OVER_C_VOLTAGE_RECORD,        0x00, (void*)gCs_EvFmt1},   //上1-10次C相过压记录
    
    {0x13010000, 0x35, 0x09, TYPE_CUT_A_VOLTAGE_RECORD,         0x00, (void*)gCs_EvFmt1},   //上1-10次A相断相记录
    {0x13020000, 0x35, 0x09, TYPE_CUT_B_VOLTAGE_RECORD,         0x00, (void*)gCs_EvFmt1},   //上1-10次B相断相记录
    {0x13030000, 0x35, 0x09, TYPE_CUT_C_VOLTAGE_RECORD,         0x00, (void*)gCs_EvFmt1},   //上1-10次C相断相记录
    
    {0x14000000, 0x22, 0x09, TYPE_ORDER_VOLTAGE_RECORD,         0x00, (void*)gCs_EvFmt3},   //上1-10次电压逆相序记录
    {0x15000000, 0x22, 0x09, TYPE_ORDER_CURRENT_RECORD,         0x00, (void*)gCs_EvFmt3},   //上1-10次电流逆相序记录
    {0x16000000, 0x23, 0x09, TYPE_UNBALANCE_VOLTAGE_RECORD,     0x00, (void*)gCs_EvFmt4},   //上1-10次电压不平衡记录
    {0x17000000, 0x23, 0x09, TYPE_UNBALANCE_CURRENT_RECORD,     0x00, (void*)gCs_EvFmt4},   //上1-10次电流不平衡记录
    
    {0x18010000, 0x31, 0x09, TYPE_LOSS_A_CURRENT_RECORD,        0x00, (void*)gCs_EvFmt2},   //上1-10次A相失流记录
    {0x18020000, 0x31, 0x09, TYPE_LOSS_B_CURRENT_RECORD,        0x00, (void*)gCs_EvFmt2},   //上1-10次B相失流记录
    {0x18030000, 0x31, 0x09, TYPE_LOSS_C_CURRENT_RECORD,        0x00, (void*)gCs_EvFmt2},   //上1-10次C相失流记录
    
    {0x19010000, 0x31, 0x09, TYPE_OVER_A_CURRENT_RECORD,        0x00, (void*)gCs_EvFmt2},   //上1-10次A相过流记录
    {0x19020000, 0x31, 0x09, TYPE_OVER_B_CURRENT_RECORD,        0x00, (void*)gCs_EvFmt2},   //上1-10次B相过流记录
    {0x19030000, 0x31, 0x09, TYPE_OVER_C_CURRENT_RECORD,        0x00, (void*)gCs_EvFmt2},   //上1-10次C相过流记录
    
    {0x1A010000, 0x31, 0x09, TYPE_CUT_A_CURRENT_RECORD,         0x00, (void*)gCs_EvFmt2},   //上1-10次A相断流记录
    {0x1A020000, 0x31, 0x09, TYPE_CUT_B_CURRENT_RECORD,         0x00, (void*)gCs_EvFmt2},   //上1-10次B相断流记录
    {0x1A030000, 0x31, 0x09, TYPE_CUT_C_CURRENT_RECORD,         0x00, (void*)gCs_EvFmt2},   //上1-10次C相断流记录
    
    {0x1B010000, 0x22, 0x09, TYPE_REVERSEPOWER_A_RECORD,        0x00, (void*)gCs_EvFmt3},   //上1-10次A相潮流记录
    {0x1B020000, 0x22, 0x09, TYPE_REVERSEPOWER_B_RECORD,        0x00, (void*)gCs_EvFmt3},   //上1-10次B相潮流记录
    {0x1B030000, 0x22, 0x09, TYPE_REVERSEPOWER_C_RECORD,        0x00, (void*)gCs_EvFmt3},   //上1-10次C相潮流记录
    
    {0x1C010000, 0x22, 0x09, TYPE_POWEROVER_A_RECORD,           0x00, (void*)gCs_EvFmt3},   //上1-10次A相过载记录
    {0x1C020000, 0x22, 0x09, TYPE_POWEROVER_B_RECORD,           0x00, (void*)gCs_EvFmt3},   //上1-10次B相过载记录
    {0x1C030000, 0x22, 0x09, TYPE_POWEROVER_C_RECORD,           0x00, (void*)gCs_EvFmt3},   //上1-10次C相过载记录
#if(CONFIG_METER_RELAY_MODE!=CONFIG_METER_RELAY_MODE_DISABLE)
    {0x1D000000, 0x08, 0x09, TYPE_RELAY_OPEN_RECORD,            0x00, (void*)gCs_EvFmt5},   //上1-10次跳闸记录
    {0x1E000000, 0x08, 0x09, TYPE_RELAY_CLOSE_RECORD,           0x00, (void*)gCs_EvFmt5},   //上1-10次合闸记录
#endif
    {0x1F000000, 0x0A, 0x09, TYPE_OVERTOTALCOS_RECORD,          0x00, (void*)gCs_EvFmt6},   //上1-10次总功率因数超下限记录

#if(CONFIG_METER_TYPE==CONFIG_METER_TYPE_SD39C)
    {0x20000000, 0x03, 0x09, TYPE_BROADCASTTIME_RECORD,          0x00, (void*)gCs_EvFmt20}, //上1-10次广播校时记录
#endif

};
const uchar gCuc_IDConv1TabNum = sizeof(gCs_IDConv1) / sizeof(S_IDCONV1);

/////失压类事件的记录内容的规约格式(如果没有使用的话就置成0)
///规约中长度
COMM_CONST uchar ucEvenLosevoltageFoematLenth[]=
{
    6,6,
    4,4,4,4,4,4,4,4,
    2,
    3,3,3,
    2,4,4,4,4,
    2,
    3,3,3,
    2,
    4,4,4,4,
    2,3,3,3,
    2,4,4,4,4
};

#if (CONFIG_METER_AREA_MODE_SOUTHGRID==CONFIG_METER_AREA_MODE)
//////南网全失压事件的规约格式
COMM_CONST uchar ucEvenLoseVoltageAllFormatLenth[]=
{
    6,
    4,4,4,4,4,4,4,4,
    2,
    3,3,3,
    2,4,4,4,4,
    2,
    3,3,3,
    2,
    4,4,4,4,
    2,3,3,3,
    2,6,
};
#else
//////全失压事件的规约格式
COMM_CONST uchar ucEvenLoseVoltageAllFormatLenth[]=
{
    6,3,6,
};
#endif

////辅助电源失电的规约格式
COMM_CONST uchar ucEvenAPVoltageLoseFormatLenth[]=
{
    6,6,
};

/////电压逆相序的规约格式
COMM_CONST uchar ucEvenConversFormatLenth[]=
{
    6,6,
    4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
};

//////电压,电流不平衡的规约格式
COMM_CONST uchar ucEvenUnblanceFormatLenth[]=
{
    6,6,
    2,
    4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
};

/////失流类时间的规约格式
COMM_CONST uchar ucEvenLoseCurentFormatLenth[]=
{
    6,6,
    4,4,4,4,4,4,4,4,
    2,3,3,3,
    2,4,4,4,4,
    2,3,3,3,
    2,4,4,4,4,
    2,3,3,3,2,
};
    ////电压合格率数据的规约格式
COMM_CONST  uchar ucEvenVoltagecheckOutFormatLenth[]=
    {
        3,3,3,3,3,2,4,2,4
    };


//////掉电数据
COMM_CONST uchar ucEvenPowerOffFormatLenth[]=
    {
        6,6,
    };

//////需量超限
COMM_CONST uchar ucEvenMDOverFormatLenth[]=
    {
        6,6,3,5,
    };

////电表操作-编程
COMM_CONST uchar ucEvenMeterProgramFormatLenth[]=
{
    6,4,
    4,4,4,4,4,4,4,4,4,4,
};

////电表操作-电表清零
COMM_CONST uchar ucEvenMeterClearFormatLenth[]=
{
    6,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
};

////电表操作-需量清零(后续帧需要(3+5)*12)
COMM_CONST uchar ucEvenMeterMDClearFormatLenth[]=
{
    6,4,
    3,5,3,5,3,5,3,5,3,5,3,5,3,5,3,5,3,5,3,5,3,5,3,5,
};

////电表操作-事件清零
COMM_CONST uchar ucEvenMeterEvenClearFormatLenth[]=
{
    6,4,4
};

/////电表操作-校时
COMM_CONST uchar ucEvenCheckTimeFormatLenth[]=
{
    4,6,6
};

/////电表操作-时段表编程
COMM_CONST uchar ucEvenDayTableFormatLenth[]=
{
    6,4,
    /////这个比较特殊,依据4*14的长度来做成一帧
    4*3*14,
};

//////电表操作-时区表表编程
COMM_CONST uchar ucEvenSeasonTableFormatLenth[]=
{
    6,4,
    3*28,
};

////电表操作-周休日编程
COMM_CONST uchar ucEvenWeekTableFormatLenth[]=
{
    6,4,1,
};

/////电表操作---节假日编程记录字节数为1026>200个(还有5*(42*4)分成9份放在后续BUFFER中)
COMM_CONST uchar ucEvenHolidayFormatLenth[]=
{
    6,
    4*45,
};

/////电表操作---有无功组合方式
COMM_CONST uchar ucEvenCalucateCombineFormatLenth[]=
{
    6,4,1,
};
/////电表操作---结算日编程记录
COMM_CONST uchar ucEvenBillDataFormatLenth[]=
{
    6,4,2,2,2,
};

/////电表操作---开表盖,开端盖记录
COMM_CONST uchar ucEvenOpenCoverFormatLenth[]=
{
    6,6,
    4,4,4,4,4,4,4,4,4,4,4,4,
};

/////电表操作---远程设置时段表
COMM_CONST uchar ucEvenFarSetTableFormatLenth[]=
{
      6,4,
      4*10
};


//////解析DI2
COMM_CONST  STR_COMM_EVEN_FAILURE_TWOTABLE_ADDR  TableTwotableAddr[]=
{
    ////失压类各个分相的二次表地址
    {0x01,TYPE_LOSS_A_VOLTAGE_RECORD,TYPE_LOSS_B_VOLTAGE_RECORD,TYPE_LOSS_C_VOLTAGE_RECORD},
    {0x02,TYPE_DOWN_A_VOLTAGE_RECORD,TYPE_DOWN_B_VOLTAGE_RECORD,TYPE_DOWN_C_VOLTAGE_RECORD},
    {0x03,TYPE_OVER_A_VOLTAGE_RECORD,TYPE_OVER_B_VOLTAGE_RECORD,TYPE_OVER_C_VOLTAGE_RECORD},
    {0x04,TYPE_CUT_A_VOLTAGE_RECORD,TYPE_CUT_B_VOLTAGE_RECORD,TYPE_CUT_C_VOLTAGE_RECORD},
    ////失流,过流
    {0x0B,TYPE_LOSS_A_CURRENT_RECORD,TYPE_LOSS_B_CURRENT_RECORD,TYPE_LOSS_C_CURRENT_RECORD},
    {0x0C,TYPE_OVER_A_CURRENT_RECORD,TYPE_OVER_B_CURRENT_RECORD,TYPE_OVER_C_CURRENT_RECORD},
    {0x0D,TYPE_CUT_A_CURRENT_RECORD,TYPE_CUT_B_CURRENT_RECORD,TYPE_CUT_C_CURRENT_RECORD},

    ////反向,过载类各个分相的二次表地址
    {0x0E,TYPE_REVERSEPOWER_A_RECORD,TYPE_REVERSEPOWER_B_RECORD,TYPE_REVERSEPOWER_C_RECORD},
    {0x0F,TYPE_POWEROVER_A_RECORD,TYPE_POWEROVER_B_RECORD,TYPE_POWEROVER_C_RECORD},
    ///
};


////解析DI1类数据(电压合格率数据)
COMM_CONST  STR_COMM_EVEN_VOLTAGE_CHECKOUT_ADDR   TableVoltagecheckOutaddr[]=
{
    {0x00,RAM_VOLTAGE_ALL_MONITOR_TIME,TYPE_MONITOR_VOLTAGE_ALL_RECORD},
    {0x01,RAM_VOLTAGE_A_MONITOR_TIME,TYPE_MONITOR_VOLTAGE_A_RECORD},
    {0x02,RAM_VOLTAGE_B_MONITOR_TIME,TYPE_MONITOR_VOLTAGE_B_RECORD},
    {0x03,RAM_VOLTAGE_C_MONITOR_TIME,TYPE_MONITOR_VOLTAGE_C_RECORD},
};


/////需量超限记录
COMM_CONST  STR_COMM_EVEN_MD_OVER_LOAD  TableMDOverLoadAddr[]=
{
    {0x01,TYPE_DEMAND_OVER_KW_F_RECORD,COMM_USE},
    {0x02,TYPE_DEMAND_OVER_KW_R_RECORD,COMM_USE},
    {0x03,TYPE_DEMAND_OVER_KVAR_Q1_RECORD,COMM_USE},
    {0x04,TYPE_DEMAND_OVER_KVAR_Q2_RECORD,COMM_USE},
    {0x05,TYPE_DEMAND_OVER_KVAR_Q3_RECORD,COMM_USE},
    {0x06,TYPE_DEMAND_OVER_KVAR_Q4_RECORD,COMM_USE}
};



////事件类----电表操作处理结构表
COMM_CONST STR_EVEN_RECORD_METER_HANDLE TableEvenMeterHandle[]=
{
	{0x00,(uchar*)ucEvenMeterProgram,EPL_PROGRAM_COUNT,TYPE_PROGRAM_RECORD,COMM_USE,sizeof(ucEvenMeterProgram),(uchar*)ucEvenMeterProgramFormatLenth},
    {0x01,(uchar*)ucEvenMeterClear,EPL_CLR_METER_COUNT,TYPE_PROGRAM_METERCLR_RECORD,COMM_USE,sizeof(ucEvenMeterClear),(uchar*)ucEvenMeterClearFormatLenth},
    {0x02,(uchar*)ucEvenMDClear,EPL_CLR_DEMAND_COUNT,TYPE_PROGRAM_DEMANDCLR_RECORD,COMM_USE,sizeof(ucEvenMDClear),(uchar*)ucEvenMeterMDClearFormatLenth},
    {0x03,(uchar*)ucEvenEvenClear,EPL_CLR_EVENT_COUNT,TYPE_PROGRAM_EVENTCLR_RECORD,COMM_USE,sizeof(ucEvenEvenClear),(uchar*)ucEvenMeterEvenClearFormatLenth},
    {0x04,(uchar*)ucEvenCheckTime,EPL_PROGRAM_TIME_COUNT,TYPE_PROGRAM_TIME_RECORD,COMM_USE,sizeof(ucEvenCheckTime),(uchar*)ucEvenCheckTimeFormatLenth},
    {0x05,(uchar*)ucEvenFeeTableProgram,EPL_PROGRAM_PERIOD_COUNT,TYPE_PROGRAM_DAYTABLE_RECORD,COMM_USE,sizeof(ucEvenFeeTableProgram),(uchar*)ucEvenDayTableFormatLenth},
    {0x06,(uchar*)ucEvenFeeSeasonTableProgram,EPL_PROGRAM_SEASON_COUNT,TYPE_PROGRAM_SEASON_RECORD,COMM_USE,sizeof(ucEvenFeeSeasonTableProgram),(uchar*)ucEvenSeasonTableFormatLenth},
    {0x07,(uchar*)ucEvenFeeWeekTableProgram,EPL_PROGRAM_CHARACTER_REST_COUNT,TYPE_PROGRAM_RESTDAY_RECORD,COMM_USE,sizeof(ucEvenFeeWeekTableProgram),(uchar*)ucEvenWeekTableFormatLenth},
    {0x08,(uchar*)ucEvenFeeHolidayProgram,EPL_PROGRAM_PUBLIC_HOLIDAY_COUNT,TYPE_PROGRAM_HOLIDAY_RECORD,COMM_USE,sizeof(ucEvenFeeHolidayProgram),(uchar*)ucEvenHolidayFormatLenth},
    {0x09,(uchar*)ucEvenCalucateCombineProgram,EPL_PROGRAM_ACTIVE_COM_COUNT,TYPE_PROGRAM_CHARACTER_ACTIVE_RECORD,COMM_USE,sizeof(ucEvenCalucateCombineProgram),(uchar*)ucEvenCalucateCombineFormatLenth},
    {0x0A,(uchar*)ucEvenCalucateCombineProgram,EPL_PROGRAM_REACTIVE1_COM_COUNT,TYPE_PROGRAM_CHARACTER_REACTIVE01_RECORD,COMM_USE,sizeof(ucEvenCalucateCombineProgram),(uchar*)ucEvenCalucateCombineFormatLenth},
    {0x0B,(uchar*)ucEvenCalucateCombineProgram,EPL_PROGRAM_REACTIVE2_COM_COUNT,TYPE_PROGRAM_CHARACTER_REACTIVE02_RECORD,COMM_USE,sizeof(ucEvenCalucateCombineProgram),(uchar*)ucEvenCalucateCombineFormatLenth},
    {0x0C,(uchar*)ucEvenBillData,EPL_PROGRAM_BALANCE_DAY_COUNT,TYPE_PROGRAM_BALANCE_DAY_RECORD,COMM_USE,sizeof(ucEvenBillData),(uchar*)ucEvenBillDataFormatLenth},
    {0x0D,(uchar*)ucEvenOpencover,EPL_TOTAL_COVER_COUNT,TYPE_COVER_OPEN_RECORD,COMM_USE,sizeof(ucEvenOpencover),(uchar*)ucEvenOpenCoverFormatLenth},
    {0x0E,(uchar*)ucEvenOpencover,EPL_TOTAL_TERMINAL_BLOCK_START,TYPE_TERMINAL_OPEN_RECORD,COMM_USE,sizeof(ucEvenOpencover),(uchar*)ucEvenOpenCoverFormatLenth},
    {0x0F,(uchar*)ucEvenSetTable,EPL_TOTAL_PROGRAM_DAYTABLE_MODULE_COUNT,TYPE_DAYTABLE_MODULE_RECORD,COMM_USE,sizeof(ucEvenSetTable),(uchar*)ucEvenFarSetTableFormatLenth},
        
};

//////事件中规约格式与存储格式对照表(编程事件类除外)
COMM_CONST STR_EVEN_RECORD_CHANGETOFORMAT TableEvenDataToFormat[]=
{
    {0x01,(uchar*)ucEvenLosevoltageLenth,(uchar*)ucEvenLosevoltageFoematLenth,sizeof(ucEvenLosevoltageFoematLenth)},
    {0x02,(uchar*)ucEvenLosevoltageLenth,(uchar*)ucEvenLosevoltageFoematLenth,sizeof(ucEvenLosevoltageFoematLenth)},
    {0x03,(uchar*)ucEvenLosevoltageLenth,(uchar*)ucEvenLosevoltageFoematLenth,sizeof(ucEvenLosevoltageFoematLenth)},
    {0x04,(uchar*)ucEvenLosevoltageLenth,(uchar*)ucEvenLosevoltageFoematLenth,sizeof(ucEvenLosevoltageFoematLenth)},
    {0x05,(uchar*)ucEvenLoseVoltageAllLenth,(uchar*)ucEvenLoseVoltageAllFormatLenth,sizeof(ucEvenLoseVoltageAllFormatLenth)},
    {0x06,(uchar*)ucEvenAPVolatgeLenth,(uchar*)ucEvenAPVoltageLoseFormatLenth,sizeof(ucEvenAPVoltageLoseFormatLenth)},
    {0x07,(uchar*)ucEvenConverseLenth,(uchar*)ucEvenConversFormatLenth,sizeof(ucEvenConversFormatLenth)},
    {0x08,(uchar*)ucEvenConverseLenth,(uchar*)ucEvenConversFormatLenth,sizeof(ucEvenConversFormatLenth)},
    {0x09,(uchar*)ucEvenUblanceLenth,(uchar*)ucEvenUnblanceFormatLenth,sizeof(ucEvenUnblanceFormatLenth)},
    {0x0A,(uchar*)ucEvenUblanceLenth,(uchar*)ucEvenUnblanceFormatLenth,sizeof(ucEvenUnblanceFormatLenth)},
    {0x0B,(uchar*)ucEvenLoseCurrentLenth,(uchar*)ucEvenLoseCurentFormatLenth,sizeof(ucEvenLoseCurentFormatLenth)},
    {0x0C,(uchar*)ucEvenLoseCurrentLenth,(uchar*)ucEvenLoseCurentFormatLenth,sizeof(ucEvenLoseCurentFormatLenth)},
    {0x0D,(uchar*)ucEvenLoseCurrentLenth,(uchar*)ucEvenLoseCurentFormatLenth,sizeof(ucEvenLoseCurentFormatLenth)},
    {0x0E,(uchar*)ucEvenConverseLenth,(uchar*)ucEvenConversFormatLenth,sizeof(ucEvenConversFormatLenth)},
    {0x0F,(uchar*)ucEvenConverseLenth,(uchar*)ucEvenConversFormatLenth,sizeof(ucEvenConversFormatLenth)},
    {0x10,(uchar*)ucEvenVoltagecheckOut,(uchar*)ucEvenVoltagecheckOutFormatLenth,sizeof(ucEvenVoltagecheckOutFormatLenth)},
    {0x11,(uchar*)ucEvenPowerOff,(uchar*)ucEvenPowerOffFormatLenth,sizeof(ucEvenPowerOffFormatLenth)},
    {0x12,(uchar*)ucEvenMDOverLoadRecord,(uchar*)ucEvenMDOverFormatLenth,sizeof(ucEvenMDOverFormatLenth)},
};

/////////////////冻结,DI1//////////////////////////////////
COMM_CONST  STR_FREEZE_DATA_TYPE        TableFreezeType[]=
{
    {0x00,COMM_USE,			5,				1,						5},
    {0x01,COMM_USE,COMM_READ_EC_LENTH,COMM_READ_EC_FEE_MAXSIZE,COMM_READ_EC_FORMAT_LENTH},
    {0x02,COMM_USE,COMM_READ_EC_LENTH,COMM_READ_EC_FEE_MAXSIZE,COMM_READ_EC_FORMAT_LENTH},
    {0x03,COMM_USE,COMM_READ_EC_LENTH,COMM_READ_FREEZE_FEE_MAXSIZE,COMM_READ_EC_FORMAT_LENTH},
    {0x04,COMM_USE,COMM_READ_EC_LENTH,COMM_READ_FREEZE_FEE_MAXSIZE,COMM_READ_EC_FORMAT_LENTH},
    {0x05,COMM_USE,COMM_READ_EC_LENTH,COMM_READ_FREEZE_FEE_MAXSIZE,COMM_READ_EC_FORMAT_LENTH},
    {0x06,COMM_USE,COMM_READ_EC_LENTH,COMM_READ_FREEZE_FEE_MAXSIZE,COMM_READ_EC_FORMAT_LENTH},
    {0x07,COMM_USE,COMM_READ_EC_LENTH,COMM_READ_FREEZE_FEE_MAXSIZE,COMM_READ_EC_FORMAT_LENTH},
    {0x08,COMM_USE,COMM_READ_EC_LENTH,COMM_READ_FREEZE_FEE_MAXSIZE,COMM_READ_EC_FORMAT_LENTH},
    {0x09,COMM_USE,(COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH),COMM_READ_FREEZE_FEE_MAXSIZE,COMM_READ_MD_FORMAT_LENTH+COMM_READ_MD_TIME_FORMAT_LENTH},
    {0x0A,COMM_USE,(COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH),COMM_READ_FREEZE_FEE_MAXSIZE,COMM_READ_MD_FORMAT_LENTH+COMM_READ_MD_TIME_FORMAT_LENTH},
    {0x10,COMM_USE,COMM_READ_FREEZE_VARIABLE_LENTH,COMM_READ_FREEZE_VARIABLE_MAXSIZE,COMM_READ_FREEZE_VARIABLE_FORMATLENTH}
    
};

////冻结状态字
COMM_CONST   uchar   CommFeezeArrWord[]={BIT0,BIT1,BIT2,BIT3,BIT4,BIT4,BIT4,BIT4,BIT5,BIT6,BIT7};
/////////////////////////////参变量/////////////////////
COMM_CONST  ST_COMM_ADD_PARA AddPara[]=
{
	{0x0000,0xffffffff,4,LOW_BYTE_FRONT},																																					
	{0xffff,0xffffffff,4,LOW_BYTE_FRONT},																																					
	{0x0100,CFGDIR_TYPE_METER_TYPE,1,LOW_BYTE_FRONT},																																					
	{0x0101,CFGDIR_TYPE_PLUS_CONSTANT,3,LOW_BYTE_FRONT},																																					
	{0x0102,CFGDIR_TYPE_VOLTAGE_UN,5,LOW_BYTE_FRONT},																																					
	{0x0103,CFGDIR_TYPE_CURRENT_IB,5,LOW_BYTE_FRONT},																																					
	{0x0104,CFGDIR_TYPE_CURRENT_IMAX,5,LOW_BYTE_FRONT},																																					
	{0x0110,CFGDIR_COEF_KW_MUL,1,LOW_BYTE_FRONT},																																					
	{0x0111,CFGDIR_COEF_KW_DIV,1,LOW_BYTE_FRONT},																																					
	{0x0112,CFGDIR_COEF_CALC_KW,2,HIGH_BYTE_FRONT},																																					
	{0x0113,CFGDIR_COEF_CALC_KVAR,2,HIGH_BYTE_FRONT},																																					
	{0x0114,CFGDIR_COEF_CALC_KVA,2,HIGH_BYTE_FRONT},																																					
	{0x0115,CFGDIR_COEF_CURRENT_A,2,HIGH_BYTE_FRONT},																																					
	{0x0116,CFGDIR_COEF_CURRENT_B,2,HIGH_BYTE_FRONT},																																					
	{0x0117,CFGDIR_COEF_CURRENT_C,2,HIGH_BYTE_FRONT},																																					
	{0x0118,CFGDIR_COEF_VOLTAGE_A,2,HIGH_BYTE_FRONT},																																					
	{0x0119,CFGDIR_COEF_VOLTAGE_B,2,HIGH_BYTE_FRONT},																																					
	{0x011a,CFGDIR_COEF_VOLTAGE_C,2,HIGH_BYTE_FRONT},																																					
	{0x0120,CFGDIR_COEF_POWER_OUTTIME,2,LOW_BYTE_FRONT},																																					
	{0x0121,CFGDIR_COEF_DEMAND_STARTCOUNT,2,LOW_BYTE_FRONT},
	{0x0122,CFGDIR_COEF_METER_PULSE_STARTUP,1,LOW_BYTE_FRONT},
	{0x0123,CFGDIR_COEF_METER_DATA_STARTUP,1,LOW_BYTE_FRONT},
	{0x1101,CFGDIR_COEF_BALANCE_DAY_NUM,1,LOW_BYTE_FRONT},
	{0x1102,CFGDIR_MODE_POWER_CALC_POINT,1,LOW_BYTE_FRONT},
	{0x1103,CFGDIR_MODE_BROADCAST_TIME,1,LOW_BYTE_FRONT},
	{0x1104,CFGDIR_COEF_BROADCAST_TIME_EVERYDAY,1,LOW_BYTE_FRONT},
	{0x1105,CFGDIR_COEF_BROADCAST_TIME_FIXED,1,LOW_BYTE_FRONT},
	{0x1106,CFGDIR_MODE_DEMAND_HANDCLR_ENABLE,1,LOW_BYTE_FRONT},
	{0x1107,CFGDIR_COEF_DEMAND_HANDCLR_LOCKTIME,2,LOW_BYTE_FRONT},
	{0x1108,CFGDIR_MODE_DEMAND_CALC_POINT_FIXED,1,LOW_BYTE_FRONT},
	{0x1201,CFGDIR_MODE_DISPLAYALARM_ORDER_VOLTAGE,1,LOW_BYTE_FRONT},
	{0x1202,CFGDIR_MODE_DISPLAYALARM_LOSS_VOLTAGE,1,LOW_BYTE_FRONT},
	{0x1203,CFGDIR_MODE_DISPLAYALARM_CUT_VOLTAGE,1,LOW_BYTE_FRONT},
	{0x1204,CFGDIR_MODE_DISPLAYALARM_OVER_VOLTAGE,1,LOW_BYTE_FRONT},
	{0x1205,CFGDIR_MODE_DISPLAYALARM_DOWN_VOLTAGE,1,LOW_BYTE_FRONT},
	{0x1206,CFGDIR_MODE_DISPLAYALARM_ORDER_CURRENT,1,LOW_BYTE_FRONT},
	{0x1207,CFGDIR_MODE_DISPLAYALARM_LOSS_CURRENT,1,LOW_BYTE_FRONT},
	{0x1208,CFGDIR_MODE_DISPLAYALARM_CUT_CURRENT,1,LOW_BYTE_FRONT},
	{0x1209,CFGDIR_MODE_DISPLAYALARM_OVER_CURRENT,1,LOW_BYTE_FRONT},
	{0x1211,CFGDIR_COEF_ALARM_BATVOLTAGE_CLOCK,1,LOW_BYTE_FRONT},
	{0x1212,CFGDIR_COEF_ALARM_BATVOLTAGE_POWEROFF,1,LOW_BYTE_FRONT},
	{0x1213,CFGDIR_MODE_DISPLAYALARM_BAT_CLOCK,1,LOW_BYTE_FRONT},
	{0x1214,CFGDIR_MODE_DISPLAYALARM_BAT_POWEROFF,1,LOW_BYTE_FRONT},
														
	{0x8000,0,CON_ALARM_TYPE_BYTE_MAX,LOW_BYTE_FRONT},                                          //各种报警状态
	// add by ybf 2010.09.15    						
	{0x8001,EPL_COEF_ALARM_SPEEK,CON_ALARM_TYPE_BYTE_MAX,LOW_BYTE_FRONT},                       //声报警控制字
	{0x8002,EPL_COEF_ALARM_LEDYELLOW,CON_ALARM_TYPE_BYTE_MAX,LOW_BYTE_FRONT},                   //黄光报警控制字(报警灯)
	{0x8003,EPL_COEF_ALARM_LEDGREEN,CON_ALARM_TYPE_BYTE_MAX,LOW_BYTE_FRONT},                        //绿光报警控制字
	{0x8004,EPL_COEF_ALARM_LCD_DISPLLAY,CON_ALARM_TYPE_BYTE_MAX,LOW_BYTE_FRONT},                    //液晶轮显报警控制字
	{0x8005,EPL_COEF_ALARM_LCD_ERROR,CON_ALARM_TYPE_BYTE_MAX,LOW_BYTE_FRONT},                   //液晶错误报警控制字
														
	{0x8010,EPL_COEF_REMOTE_WAKEUP_ENABLE,1,LOW_BYTE_FRONT},              //红外唤醒模式
	{0x8020,EPL_COEF_PROGRAM_TIME,2,LOW_BYTE_FRONT},                      //编程维持时间
	{0x8030,EPL_COEF_DISPLAY_MODE_CHANGE_TIME,2,LOW_BYTE_FRONT},          //轮显切换时间
	{0x8040,EPL_COEF_POWERDOWN_ALLLOSSVOLTAGE_CONDITION,5,LOW_BYTE_FRONT},    //全失压判断条件
	{0x8050,EPL_COEF_CLR_METER_ENABLE_TIMES,1,LOW_BYTE_FRONT},                //电量清零允许次数(南网适用)
	{0x9000,EPL_PUBLIC_HOLIDAY001,0,LOW_BYTE_FRONT},
};

COMM_CONST  ST_COMM_DISP_LIST  TableParaMeter[]=
{
	{0x04000101,RAM_SOFT_DAY,4,CWBFTimeChange,CommDayFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x06},
	{0x04000102,RAM_SOFT_TIME,3,CWBFTimeChange,CommTimeFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x06},
	{0x04000103,EPL_DEMAND_CYCLE_TIME,1,CWBFDemandCycleChange,CommDemandNumFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000104,EPL_DEMAND_PAT_TIME,1,CWBFDemandCycleChange,CommDemandNumFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000105,EPL_POWER_PULSE_TIME,2,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ,0x01},
	{0x04000106,EPL_COEF_2SEASONCHANGE_TIME,5,CWBFPriceChange,CommFeeTableSwitchFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000107,EPL_COEF_2DAYTABLECHANGE_TIME,5,CWBFPriceChange,CommFeeTableSwitchFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	//块2
	{0x04000201,EPL_COEF_SEASONTABLE_MAX_NUM,1,CWBFPriceChange,CommSeasonNumFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000202,EPL_COEF_DAYTABLE_MAX_NUM,1,CWBFPriceChange,CommDayTableNumFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000203,EPL_COEF_PERIOD_MAX_NUM,1,CWBFPriceChange,CommFeeTableNumFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000204,EPL_COEF_PRICE_MAX_NUM,1,CWBFPriceChange,CommFeeNumFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000205,EPL_COEF_HOLIDAY_MAX_MUN,2,CWBFPriceChange,CommHolidayNumFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000206,EPL_COEF_HUMOROUS_MAX_NUM,1,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	//块3
	#if(CONFIG_METER_AREA_MODE_SHANDONG==CONFIG_METER_AREA_MODE)
	{0x04000301,EPL_COEF_AUTO_TURNPAGE_NUM,1,CWBFDisplayChange,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_IDEL,0x01},
	#else
	{0x04000301,EPL_COEF_AUTO_TURNPAGE_NUM,1,CWBFDisplayChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_IDEL,0x01},
	#endif
	{0x04000302,EPL_COEF_TURNPAGE_TIME,1,CWBFDisplayChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_IDEL,0x01},
	{0x04000303,EPL_COEF_POWER_POINT_NUM,1,CWBFDisplayChange,CommDspECFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000304,EPL_COEF_DEMAND_POINT_NUM,1,CWBFDisplayChange,CommDspMDFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	#if(CONFIG_METER_AREA_MODE_SHANDONG==CONFIG_METER_AREA_MODE)
	{0x04000305,EPL_COEF_KEY_TURNPAGE_NUM,1,CWBFDisplayChange,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_IDEL,0x01},
	#else
	{0x04000305,EPL_COEF_KEY_TURNPAGE_NUM,1,CWBFDisplayChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_IDEL,0x01},
	#endif
	//块4
	{0x04000401,EPL_USER_COMM_ADDR,6,CWBFCommAddrChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	#if(CONFIG_METER_PREPAY_MODE==CONFIG_METER_PREPAY_MODE_FAR)
	{0x04000402,EPL_USER_ID,6,NULLReturnValue,CommWriteFormatKey,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	#elif(CONFIG_METER_PREPAY_MODE==CONFIG_METER_PREPAY_MODE_LOCATION)
	{0x04000402,EPL_USER_ID,6,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ,0x01},
	#else
	{0x04000402,EPL_USER_ID,6,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	#endif
	{0x04000403,EPL_USER_ASSET,32,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,1,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000404,EPL_METER_ASCII_TYPE_UN,6,NULLReturnValue,FactoryCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,1,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000405,EPL_METER_ASCII_TYPE_IB,6,NULLReturnValue,FactoryCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,1,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000406,EPL_METER_ASCII_TYPE_IMAX,6,NULLReturnValue,FactoryCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,1,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000407,EPL_METER_ASCII_ACTIVE_PRECISION,4,NULLReturnValue,FactoryCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,1,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000408,EPL_METER_ASCII_REACTIVE_PRECISION,4,NULLReturnValue,FactoryCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,1,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000409,CFGDIR_TYPE_PLUS_CONSTANT,3,NULLReturnValue,FactoryCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ,0x01},
	{0x0400040A,CFGDIR_TYPE_PLUS_CONSTANT,3,NULLReturnValue,FactoryCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ,0x01},
	{0x0400040B,EPL_METER_ASCII_METER_TYPE,10,NULLReturnValue,FactoryCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,1,1,COMM_READ+COMM_WRITE,0x01},
	{0x0400040C,EPL_METER_ASCII_PRODUCE_TIME,10,NULLReturnValue,FactoryCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,1,1,COMM_READ+COMM_WRITE,0x01},
	{0x0400040D,EPL_METER_ASCII_COMM_VER,16,NULLReturnValue,FactoryCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,1,1,COMM_READ+COMM_WRITE,0x01},
	//{0x0400040D,NULLDATAADDR,16,,,COMM_PASSWORD_POPEDOM_4,1,0,0,1,1,COMM_READ,
	//电表运行状态字数据块
	{0x04000501,RAM_CURRENT_METER_STATUS01,2,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ,0x01},
	{0x04000502,RAM_CURRENT_METER_STATUS02,2,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ,0x01},
	{0x04000503,RAM_CURRENT_METER_STATUS03,2,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ,0x01},
	{0x04000504,RAM_CURRENT_METER_STATUS04,2,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ,0x01},
	{0x04000505,RAM_CURRENT_METER_STATUS05,2,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ,0x01},
	{0x04000506,RAM_CURRENT_METER_STATUS06,2,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ,0x01},
	{0x04000507,RAM_CURRENT_METER_STATUS07,2,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ,0x01},
	{0x040005FF,RAM_CURRENT_METER_STATUS01,14,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ,0x01},
	//块6
	{0x04000601,EPL_CHARACTER_ACTIVE,1,CWBFPowerCharacterChange,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x11},
	{0x04000602,EPL_CHARACTER_REACTIVE01,1,CWBFPowerCharacterChange,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x12},
	{0x04000603,EPL_CHARACTER_REACTIVE02,1,CWBFPowerCharacterChange,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x13},
	//块7
	{0x04000701,EPL_IR_MODULATOR_BAUDRATE,1,NULLReturnValue,CommBautWordFm,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	//{0x04000702,EPL_IR_CONTACT_BAUDRATE,1,NULLReturnValue,CommBautWordFm,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000703,EPL_COMM485_01_BAUDRATE,1,NULLReturnValue,CommBautWordFm,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	#if(CONFIG_METER_NO2COMM_MODE_RS485==CONFIG_METER_NO2COMM_MODE)
	    {0x04000704,EPL_COMM485_02_BAUDRATE,1,NULLReturnValue,CommBautWordFm,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	#endif
	//{0x04000705,EPL_COMM485_03_BAUDRATE,1,NULLReturnValue,CommBautWordFm,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	//块8
	{0x04000801,EPL_CHARACTER_REST_DAY,1,CWBFPriceChange,NULLCheckFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000802,EPL_CHARACTER_REST_DAYNO,1,CWBFPriceChange,CommWeekDayUseTouFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x09},
	//块9
	{0x04000901,EPL_CHARACTER_CHARGE_MODE,1,CWBFChargeRecordChange,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000902,EPL_CHARACTER_FREEZE_EVERYTIME_MODE,1,CWBFChargeRecordChange,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	//块10
	{0x04000A01,EPL_CHARGE_RECORD_START_TIME,4,CWBFChargeRecordChange,CommLoadRecordFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000A02,EPL_CHARGE_RECORD_1_TIME,2,CWBFChargeRecordChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000A03,EPL_CHARGE_RECORD_2_TIME,2,CWBFChargeRecordChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000A04,EPL_CHARGE_RECORD_3_TIME,2,CWBFChargeRecordChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000A05,EPL_CHARGE_RECORD_4_TIME,2,CWBFChargeRecordChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000A06,EPL_CHARGE_RECORD_5_TIME,2,CWBFChargeRecordChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000A07,EPL_CHARGE_RECORD_6_TIME,2,CWBFChargeRecordChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	//块11
	{0x04000B01,EPL_BALANCE_DAY_01,2,CWBFBalanceDayChange,CommBillDayFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x14},
	{0x04000B02,EPL_BALANCE_DAY_02,2,CWBFBalanceDayChange,CommBillDayFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x14},
	{0x04000B03,EPL_BALANCE_DAY_03,2,CWBFBalanceDayChange,CommBillDayFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x14},
	//块12
	{0x04000C01,EPL_PASSWORD_0,4,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_0,1,0,0,0,1,COMM_PASSWORD+COMM_READ,0x00},
	{0x04000C02,EPL_PASSWORD_1,4,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_1,1,0,0,0,1,COMM_PASSWORD+COMM_READ,0x00},
	{0x04000C03,EPL_PASSWORD_2,4,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_2,1,0,0,0,1,COMM_PASSWORD+COMM_READ,0x00},
	{0x04000C04,EPL_PASSWORD_3,4,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_3,1,0,0,0,1,COMM_PASSWORD+COMM_READ,0x00},
	{0x04000C05,EPL_PASSWORD_4,4,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_PASSWORD+COMM_READ,0x00},
	{0x04000C06,EPL_PASSWORD_5,4,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_5,1,0,0,0,1,COMM_PASSWORD+COMM_READ,0x00},
	{0x04000C07,EPL_PASSWORD_6,4,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_6,1,0,0,0,1,COMM_PASSWORD+COMM_READ,0x00},
	{0x04000C08,EPL_PASSWORD_7,4,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_7,1,0,0,0,1,COMM_PASSWORD+COMM_READ,0x00},
	{0x04000C09,EPL_PASSWORD_8,4,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_8,1,0,0,0,1,COMM_PASSWORD+COMM_READ,0x00},
	{0x04000C0A,EPL_PASSWORD_9,4,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_9,1,0,0,0,1,COMM_PASSWORD+COMM_READ,0x00},
	//块13
	#if 0
	{0x04000D01,RAM_COEF_A_G,2,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000D02,RAM_COEF_A_B,2,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000D03,RAM_COEF_A_R,2,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000D04,RAM_COEF_A_X,2,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000D05,RAM_COEF_B_G,2,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000D06,RAM_COEF_B_B,2,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000D07,RAM_COEF_B_R,2,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000D08,RAM_COEF_B_X,2,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000D09,RAM_COEF_C_G,2,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000D0A,RAM_COEF_C_B,2,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000D0B,RAM_COEF_C_R,2,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000D0C,RAM_COEF_C_X,2,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	#endif
	//块14
	{0x04000E01,EPL_COEF_MAX_KWH_F,3,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000E02,EPL_COEF_MAX_KWH_R,3,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000E03,EPL_COEF_VOLTAGE_LIMIT_UPPER,2,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000E04,EPL_COEF_VOLTAGE_LIMIT_LOWER,2,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	//时区时段数据
	#if(CONFIG_METER_STEP_PERIODPRICE_MODE==CONFIG_METER_STEP_PERIODPRICE_MODE_ENABLE)
	{0x04001001,EPL_PREPAY_ENERGY_ALARM1,4,CWBFCardDataIsSet,CommWriteBcdFormat,COMM_PASSWORD_FIRST_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04001002,EPL_PREPAY_ENERGY_ALARM2,4,CWBFCardDataIsSet,CommWriteBcdFormat,COMM_PASSWORD_FIRST_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04001003,EPL_PREPAY_ENERGY_OVEDRAFT,4,CWBFCardDataIsSet,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04001004,EPL_PREPAY_ENERGY_REGRATE,4,CWBFCardDataIsSet,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04001005,EPL_RELAY_CLOSE_MEMORY_LIMIT,4,CWBFCardDataIsSet,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	#endif
	//
	#if(CONFIG_METER_RELAY_MODE_DISABLE!=CONFIG_METER_RELAY_MODE)
	{0x04001401,EPL_RELAY_OPEN_DELAY_TIME,2,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04001402,EPL_RELAY_CLOSE_DELAY_TIME,2,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	#endif
	
	//第一套
	{0x04010000,EPL_SEASON1_DAYTABLE_CHANGE01, 42,CWBFPriceChange,CommSeasonTableFormat,COMM_PASSWORD_SECOND_PARA,1,1,0,0,1,COMM_READ+COMM_WRITE,0x08},
	{0x04010001,EPL_SEASON1_DAYTABLE1_PERIOD01,42,CWBFPriceChange,CommFeeDayTableFormat,COMM_PASSWORD_SECOND_PARA,1,1,0,0,1,COMM_READ+COMM_WRITE,0x07},
	{0x04010002,EPL_SEASON1_DAYTABLE2_PERIOD01,42,CWBFPriceChange,CommFeeDayTableFormat,COMM_PASSWORD_SECOND_PARA,1,1,0,0,1,COMM_READ+COMM_WRITE,0x07},
	{0x04010003,EPL_SEASON1_DAYTABLE3_PERIOD01,42,CWBFPriceChange,CommFeeDayTableFormat,COMM_PASSWORD_SECOND_PARA,1,1,0,0,1,COMM_READ+COMM_WRITE,0x07},
	{0x04010004,EPL_SEASON1_DAYTABLE4_PERIOD01,42,CWBFPriceChange,CommFeeDayTableFormat,COMM_PASSWORD_SECOND_PARA,1,1,0,0,1,COMM_READ+COMM_WRITE,0x07},
	{0x04010005,EPL_SEASON1_DAYTABLE5_PERIOD01,42,CWBFPriceChange,CommFeeDayTableFormat,COMM_PASSWORD_SECOND_PARA,1,1,0,0,1,COMM_READ+COMM_WRITE,0x07},
	{0x04010006,EPL_SEASON1_DAYTABLE6_PERIOD01,42,CWBFPriceChange,CommFeeDayTableFormat,COMM_PASSWORD_SECOND_PARA,1,1,0,0,1,COMM_READ+COMM_WRITE,0x07},
	{0x04010007,EPL_SEASON1_DAYTABLE7_PERIOD01,42,CWBFPriceChange,CommFeeDayTableFormat,COMM_PASSWORD_SECOND_PARA,1,1,0,0,1,COMM_READ+COMM_WRITE,0x07},
	{0x04010008,EPL_SEASON1_DAYTABLE8_PERIOD01,42,CWBFPriceChange,CommFeeDayTableFormat,COMM_PASSWORD_SECOND_PARA,1,1,0,0,1,COMM_READ+COMM_WRITE,0x07},
	//第二套
	{0x04020000,EPL_SEASON2_DAYTABLE_CHANGE01, 42,CWBFPriceChange,CommSeasonTableFormat,COMM_PASSWORD_SECOND_PARA,1,1,0,0,1,COMM_READ+COMM_WRITE,0x08},
	{0x04020001,EPL_SEASON2_DAYTABLE1_PERIOD01,42,CWBFPriceChange,CommFeeDayTableFormat,COMM_PASSWORD_SECOND_PARA,1,1,0,0,1,COMM_READ+COMM_WRITE,0x07},
	{0x04020002,EPL_SEASON2_DAYTABLE2_PERIOD01,42,CWBFPriceChange,CommFeeDayTableFormat,COMM_PASSWORD_SECOND_PARA,1,1,0,0,1,COMM_READ+COMM_WRITE,0x07},
	{0x04020003,EPL_SEASON2_DAYTABLE3_PERIOD01,42,CWBFPriceChange,CommFeeDayTableFormat,COMM_PASSWORD_SECOND_PARA,1,1,0,0,1,COMM_READ+COMM_WRITE,0x07},
	{0x04020004,EPL_SEASON2_DAYTABLE4_PERIOD01,42,CWBFPriceChange,CommFeeDayTableFormat,COMM_PASSWORD_SECOND_PARA,1,1,0,0,1,COMM_READ+COMM_WRITE,0x07},
	{0x04020005,EPL_SEASON2_DAYTABLE5_PERIOD01,42,CWBFPriceChange,CommFeeDayTableFormat,COMM_PASSWORD_SECOND_PARA,1,1,0,0,1,COMM_READ+COMM_WRITE,0x07},
	{0x04020006,EPL_SEASON2_DAYTABLE6_PERIOD01,42,CWBFPriceChange,CommFeeDayTableFormat,COMM_PASSWORD_SECOND_PARA,1,1,0,0,1,COMM_READ+COMM_WRITE,0x07},
	{0x04020007,EPL_SEASON2_DAYTABLE7_PERIOD01,42,CWBFPriceChange,CommFeeDayTableFormat,COMM_PASSWORD_SECOND_PARA,1,1,0,0,1,COMM_READ+COMM_WRITE,0x07},
	{0x04020008,EPL_SEASON2_DAYTABLE8_PERIOD01,42,CWBFPriceChange,CommFeeDayTableFormat,COMM_PASSWORD_SECOND_PARA,1,1,0,0,1,COMM_READ+COMM_WRITE,0x07},
	//最后一项
	{0x04800001,EPL_METER_ASCII_SOFT_VER,32,NULLReturnValue,FactoryCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,1,1,COMM_READ+COMM_WRITE,0x00},
	{0x04800002,EPL_METER_ASCII_HARD_VER,32,NULLReturnValue,FactoryCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,1,1,COMM_READ+COMM_WRITE,0x00},
	{0x04800003,EPL_METER_ASCII_FACTORY_NUM,32,NULLReturnValue,FactoryCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,1,1,COMM_READ+COMM_WRITE,0x00},
	//参变量
	#if(CONFIG_METER_STEP_PERIODPRICE_MODE==CONFIG_METER_STEP_PERIODPRICE_MODE_ENABLE)
	{0x04000108,EPL_COEF_PERIODPRICE_CHANGETIME,5,CWBFPriceChange,CommFeeTableSwitchFormat,COMM_PASSWORD_FIRST_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	#endif
	{0x04000306,EPL_COEF_PT_NUM,3,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_FIRST_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000307,EPL_COEF_CT_NUM,3,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_FIRST_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	// {0x04001001,RAM_COEF_MONEY_ALARM1,4,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	// {0x04001002,RAM_COEF_MONEY_ALARM2,4,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	// {0x04001003,RAM_COEF_MONEY_OVERDRAFT,4,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	
	/*del by zlq090922
	{0x04050101,RAM_STEPPRICE01_PRICE01,4,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04050102,RAM_STEPPRICE01_PRICE01+4,4,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04050103,RAM_STEPPRICE01_PRICE01+8,4,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04050104,RAM_STEPPRICE01_PRICE01+12,4,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04050201,RAM_STEPPRICE02_PRICE01,4,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04050202,RAM_STEPPRICE02_PRICE01+4,4,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04050203,RAM_STEPPRICE02_PRICE01+8,4,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04050204,RAM_STEPPRICE02_PRICE01+12,4,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	*/
	// {0x04060101,RAM_COEF_STEPPRICE_01_KWH_START,12,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	// {0x04060102,RAM_COEF_STEPPRICE_02_KWH_START,12,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	// {0x04060201,RAM_COEF_STEPPRICE_01_PRICE_START,9,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	// {0x04060202,RAM_COEF_STEPPRICE_02_PRICE_START,9,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	//{0x04060300,RAM_COEF_STEPPRICE_CHANGETIME,5,NULLReturnValue,CommFeeTableSwitchFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	//{0x04060400,RAM_CURRENT_STEPPRICE_STATUS,1,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ,0x00},
	//{0x04060401,RAM_KWH_ALL_USE_START,4,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ,0x00},
	
	
	//new added, zlq090922
	#if(CONFIG_METER_STEP_MODE==CONFIG_METER_STEP_MODE_ENABLE)
	{0x04000109,EPL_COEF_STEPPRICE_CHANGETIME,5,CWBFPriceChange,CommFeeTableSwitchFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04000207,EPL_COEF_STEP_NUM,1,CWBFPriceChange,CommSeasonNumFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},//阶梯数
	#endif
	{0x0400040E,EPL_METER_USER_ID,6,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_FIRST_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},//客户编号
	{0x04000903,EPL_CHARACTER_FREEZE_INSTANT_MODE,1,CWBFChargeRecordChange,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},//瞬时冻结数据模式字
	{0x04000904,EPL_CHARACTER_FREEZE_RESTORE_MODE,1,CWBFChargeRecordChange,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},//约定冻结数据模式字
	{0x04000905,EPL_CHARACTER_FREEZE_EVERYHOUR_MODE,1,CWBFChargeRecordChange,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},//整点冻结数据模式字
	{0x04000906,EPL_CHARACTER_FREEZE_EVERYDAY_MODE,1,CWBFChargeRecordChange,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},//日冻结数据模式字
	// {0x04000F01,RAM_COEF_KWH_ALARM1,4,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},//报警电量1限值
	// {0x04000F02,RAM_COEF_KWH_ALARM2,4,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},//报警电量2限值
	// {0x04000F03,RAM_COEF_KWH_HOARDING,4,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},//囤积电量限值
	// {0x04000F04,RAM_COEF_KWH_OVERDRAFT,4,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},//透支电量限值
	// {0x04001004,RAM_COEF_MONEY_HOARDING,4,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},//透支电量限值
	// {0x04001005,RAM_COEF_MONEY_CLOSE_RELAY,4,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},//合闸允许金额限值
	{0x04001101,EPL_CHARACTER_METER_RUN,1,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},//电表运行特征字
	{0x04001201,EPL_CHARACTER_FREEZE_EVERYHOUR_STARTTIME,5,NULLReturnValue,CommmmhhDDMMYYFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},//整点冻结起始时间
	{0x04001202,EPL_CHARACTER_FREEZE_EVERYHOUR_INTERVAL,1,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},//整点冻结时间间隔
	{0x04001203,EPL_CHARACTER_FREEZE_EVERYDAY_TIME,2,NULLReturnValue,CommCheckhhmm,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},//日冻结时间
	
	#if(CONFIG_METER_NO2COMM_MODE_WIRELESS==CONFIG_METER_NO2COMM_MODE)
	{0x04001301,RAM_CURRENT_MODULE_DATA,1,NULLReturnValue,NULLCheckFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},//无线通讯在线及信号强弱指示
	#endif
	
	#if(CONFIG_METER_STEP_PERIODPRICE_MODE==CONFIG_METER_STEP_PERIODPRICE_MODE_ENABLE)
	//第一套费率电价1-14
	{0x04050101,EPL_PERIODPRICE01_PRICE01,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04050102,EPL_PERIODPRICE01_PRICE01+4,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04050103,EPL_PERIODPRICE01_PRICE01+8,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04050104,EPL_PERIODPRICE01_PRICE01+12,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04050105,EPL_PERIODPRICE01_PRICE01+16,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04050106,EPL_PERIODPRICE01_PRICE01+20,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04050107,EPL_PERIODPRICE01_PRICE01+24,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04050108,EPL_PERIODPRICE01_PRICE01+28,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04050109,EPL_PERIODPRICE01_PRICE01+32,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0405010A,EPL_PERIODPRICE01_PRICE01+36,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0405010B,EPL_PERIODPRICE01_PRICE01+40,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0405010C,EPL_PERIODPRICE01_PRICE01+44,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0405010D,EPL_PERIODPRICE01_PRICE01+48,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0405010E,EPL_PERIODPRICE01_PRICE01+52,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	//第二套费率电价1-14
	{0x04050201,EPL_PERIODPRICE02_PRICE01,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04050202,EPL_PERIODPRICE02_PRICE01+4,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04050203,EPL_PERIODPRICE02_PRICE01+8,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04050204,EPL_PERIODPRICE02_PRICE01+12,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04050205,EPL_PERIODPRICE02_PRICE01+16,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04050206,EPL_PERIODPRICE02_PRICE01+20,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04050207,EPL_PERIODPRICE02_PRICE01+24,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04050208,EPL_PERIODPRICE02_PRICE01+28,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04050209,EPL_PERIODPRICE02_PRICE01+32,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0405020A,EPL_PERIODPRICE02_PRICE01+36,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0405020B,EPL_PERIODPRICE02_PRICE01+40,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0405020C,EPL_PERIODPRICE02_PRICE01+44,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0405020D,EPL_PERIODPRICE02_PRICE01+48,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0405020E,EPL_PERIODPRICE02_PRICE01+52,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	#endif
	
	#if(CONFIG_METER_STEP_MODE==CONFIG_METER_STEP_MODE_ENABLE)
	//第一套阶梯值1~14
	{0x04060001,EPL_STEP01_DATA01,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060002,EPL_STEP01_DATA01+4,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060003,EPL_STEP01_DATA01+8,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060004,EPL_STEP01_DATA01+12,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060005,EPL_STEP01_DATA01+16,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060006,EPL_STEP01_DATA01+20,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060007,EPL_STEP01_DATA01+24,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060008,EPL_STEP01_DATA01+28,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060009,EPL_STEP01_DATA01+32,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0406000A,EPL_STEP01_DATA01+36,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0406000B,EPL_STEP01_DATA01+40,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0406000C,EPL_STEP01_DATA01+44,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0406000D,EPL_STEP01_DATA01+48,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0406000E,EPL_STEP01_DATA01+52,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	
	//第一套阶梯电价1~(14+1)
	{0x04060101,EPL_STEPPRICE01_PRICE01,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060102,EPL_STEPPRICE01_PRICE01+4,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060103,EPL_STEPPRICE01_PRICE01+8,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060104,EPL_STEPPRICE01_PRICE01+12,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060105,EPL_STEPPRICE01_PRICE01+16,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060106,EPL_STEPPRICE01_PRICE01+20,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060107,EPL_STEPPRICE01_PRICE01+24,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060108,EPL_STEPPRICE01_PRICE01+28,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060109,EPL_STEPPRICE01_PRICE01+32,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0406010A,EPL_STEPPRICE01_PRICE01+36,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0406010B,EPL_STEPPRICE01_PRICE01+40,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0406010C,EPL_STEPPRICE01_PRICE01+44,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0406010D,EPL_STEPPRICE01_PRICE01+48,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0406010E,EPL_STEPPRICE01_PRICE01+52,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0406010F,EPL_STEPPRICE01_PRICE01+56,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	
	//第二套阶梯值1~14
	{0x04060201,EPL_STEP02_DATA01,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060202,EPL_STEP02_DATA01+4,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060203,EPL_STEP02_DATA01+8,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060204,EPL_STEP02_DATA01+12,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060205,EPL_STEP02_DATA01+16,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060206,EPL_STEP02_DATA01+20,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060207,EPL_STEP02_DATA01+24,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060208,EPL_STEP02_DATA01+28,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060209,EPL_STEP02_DATA01+32,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0406020A,EPL_STEP02_DATA01+36,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0406020B,EPL_STEP02_DATA01+40,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0406020C,EPL_STEP02_DATA01+44,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0406020D,EPL_STEP02_DATA01+48,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0406020E,EPL_STEP02_DATA01+52,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	
	//第二套阶梯电价1~(14+1)
	{0x04060301,EPL_STEPPRICE02_PRICE01,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060302,EPL_STEPPRICE02_PRICE01+4,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060303,EPL_STEPPRICE02_PRICE01+8,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060304,EPL_STEPPRICE02_PRICE01+12,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060305,EPL_STEPPRICE02_PRICE01+16,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060306,EPL_STEPPRICE02_PRICE01+20,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060307,EPL_STEPPRICE02_PRICE01+24,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060308,EPL_STEPPRICE02_PRICE01+28,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04060309,EPL_STEPPRICE02_PRICE01+32,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0406030A,EPL_STEPPRICE02_PRICE01+36,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0406030B,EPL_STEPPRICE02_PRICE01+40,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0406030C,EPL_STEPPRICE02_PRICE01+44,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0406030D,EPL_STEPPRICE02_PRICE01+48,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0406030E,EPL_STEPPRICE02_PRICE01+52,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x0406030F,EPL_STEPPRICE02_PRICE01+56,4,CWBFPriceChange,CommWriteBcdFormat,COMM_PASSWORD_SECOND_PARA,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	#endif
	//失压事件判断条件
	{0x04090101,EPL_COEF_LOSS_VOLTAGE_V_START,2,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04090102,EPL_COEF_LOSS_VOLTAGE_V_END,2,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04090103,EPL_COEF_LOSS_VOLTAGE_I_START,3,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04090104,EPL_COEF_LOSS_VOLTAGE_TIME,1,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	
	//欠压事件判断条件
	{0x04090201,EPL_COEF_DOWN_VOLTAGE_V_START,2,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04090202,EPL_COEF_DOWN_VOLTAGE_TIME,1,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	
	//过压事件判断条件
	{0x04090301,EPL_COEF_OVER_VOLTAGE_V_START,2,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04090302,EPL_COEF_OVER_VOLTAGE_TIME,1,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	
	//断相事件判断条件
	{0x04090401,EPL_COEF_CUT_VOLTAGE_V_START,2,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04090402,EPL_COEF_CUT_VOLTAGE_I_START,3,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04090403,EPL_COEF_CUT_VOLTAGE_TIME,1,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	
	//电压不平衡事件判断条件
	{0x04090501,EPL_COEF_UNBALANCE_VOLTAGE_DATA,2,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04090502,EPL_COEF_UNBALANCE_VOLTAGE_TIME,1,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	
	//电流不平衡事件判断条件
	{0x04090601,EPL_COEF_UNBALANCE_CURRENT_DATA,2,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04090602,EPL_COEF_UNBALANCE_CURRENT_TIME,1,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	
	//失流事件判断条件
	{0x04090701,EPL_COEF_LOSS_CURRENT_V_START,2,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04090702,EPL_COEF_LOSS_CURRENT_I_START,3,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04090703,EPL_COEF_LOSS_CURRENT_I_END ,3,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04090704,EPL_COEF_LOSS_CURRENT_TIME,1,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	
	//过流事件判断条件
	{0x04090801,EPL_COEF_OVER_CURRENT_I_START,2,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04090802,EPL_COEF_OVER_CURRENT_TIME,1,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	
	//断流事件判断条件
	{0x04090901,EPL_COEF_CUT_CURRENT_V_START,2,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04090902,EPL_COEF_CUT_CURRENT_I_START,3,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04090903,EPL_COEF_CUT_CURRENT_TIME,1,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	
	//潮流事件判断条件
	{0x04090A01,EPL_COEF_REVERSEPOWER_KW_START,3,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04090A02,EPL_COEF_REVERSEPOWER_KW_TIME,1,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	
	//过载事件判断条件
	{0x04090B01,EPL_COEF_OVER_KW_KW_START,3,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04090B02,EPL_COEF_OVER_KW_TIME,1,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	
	//电压考核上下限
	{0x04090C01,EPL_COEF_MONITOR_VOLTAGE_MAX,2,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04090C02,EPL_COEF_MONITOR_VOLTAGE_MIN,2,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	
	//需量超限判断条件
	{0x04090D01,EPL_COEF_DEMAND_OVER_KW_START,3,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04090D02,EPL_COEF_DEMAND_OVER_KVAR_START,3,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04090D03,EPL_COEF_DEMAND_OVER_TIME,1,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	
	//总功率因数超下限判断条件
	{0x04090E01,EPL_COEF_OVERTOTALCOS_START,2,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04090E02,EPL_COEF_OVERTOTALCOS_TIME,1,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	
	//电流严重不平衡判断条件
	{0x04090F01,EPL_COEF_UNBALANCE_SEVERITY_CURRENT_DATA,2,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	{0x04090F02,EPL_COEF_UNBALANCE_SEVERITY_CURRENT_TIME,1,NULLReturnValue,CommWriteBcdFormat,COMM_PASSWORD_POPEDOM_4,1,0,0,0,1,COMM_READ+COMM_WRITE,0x01},
	// 时钟补偿基准频偏
	//{0x0400F14F,EPL_DATA_FREQ_OFFSET,2,SetClockCompensateFlash,FactoryCheckFormat,COMM_PASSWORD_POPEDOM_2,1,0,0,1,1,COMM_READ+COMM_WRITE,0x01},
};


//////拉合闸事件记录格式
COMM_CONST STR_EVEN_CT_ST_GATE TableCommCSGate[]=
{
  {0x01,EPL_TOTAL_RELAY_OPEN_COUNT,TYPE_RELAY_OPEN_RECORD,30,COMM_USE},
  {0x02,EPL_TOTAL_RELAY_OPEN_COUNT,TYPE_RELAY_CLOSE_RECORD,30,COMM_USE}

};
#if 0
//////终端通信表格
COMM_CONST  STR_ZHONGDUAN_COMMDATA  TableZhongDuanComm[]=
{
    {0x74E0,RAM_RENEW_MODULE_HARD_ADDR,RAM_CURRENT_MODULE_HARD_ADDR,RAM_RENEW_MODULE_HARD_ADDR_CHANGE,4,3},
    {0x74E1,RAM_RENEW_MODULE_MESSAGE_NO,RAM_CURRENT_MODULE_MESSAGE_NO,RAM_RENEW_MODULE_MESSAGE_NO_CHANGE,8,3},
    {0x74E2,RAM_RENEW_MODULE_COMM_MAIN_ADDR,RAM_CURRENT_MODULE_COMM_MAIN_ADDR,RAM_RENEW_MODULE_COMM_MAIN_ADDR_CHANGE,9,3},
    {0x74E3,RAM_RENEW_MODULE_COMM_BAK1_ADDR,RAM_CURRENT_MODULE_COMM_BAK1_ADDR,RAM_RENEW_MODULE_COMM_BAK1_ADDR_CHANGE,9,3},
    {0x74E4,RAM_RENEW_MODULE_COMM_BAK2_ADDR,RAM_CURRENT_MODULE_COMM_BAK2_ADDR,RAM_RENEW_MODULE_COMM_BAK2_ADDR_CHANGE,9,3},
    {0x74E5,RAM_RENEW_MODULE_COMM_NETGATE,RAM_CURRENT_MODULE_COMM_NETGATE,RAM_RENEW_MODULE_COMM_NETGATE_CHANGE,8,3},
    {0x74E6,RAM_RENEW_MODULE_COMM_APN,RAM_CURRENT_MODULE_COMM_APN,RAM_RENEW_MODULE_COMM_APN_CHANGE,16,3},
    {0x74E7,RAM_RENEW_MODULE_NETCOMM_SET,RAM_CURRENT_MODULE_NETCOMM_SET,RAM_RENEW_MODULE_NETCOMM_SET_CHANGE,9,3},
    {0x74E8,RAM_RENEW_MODULE_COMM_USER,RAM_CURRENT_MODULE_COMM_USER,RAM_RENEW_MODULE_COMM_USER_CHANGE,16,2},
    {0x74E9,RAM_RENEW_MODULE_COMM_PWD,RAM_CURRENT_MODULE_COMM_PWD,RAM_RENEW_MODULE_COMM_PWD_CHANGE,16,2},
    {0x74EA,RAM_RENEW_MODULE_COMM_TYPE,RAM_CURRENT_MODULE_COMM_TYPE,RAM_RENEW_MODULE_COMM_TYPE_CHANGE,1,3},
};

/////终端通信的元素个数
u16 GetZhongDuanTableNum(void)
{
    return (sizeof(TableZhongDuanComm)/sizeof(STR_ZHONGDUAN_COMMDATA));
}
#endif
const uchar DEFAULT_VALUE_GROUP[]=
{
    0x01, 0x01, 0x03, 0x02, 0x01, 0x09, 0x02, 0x01, 0x09, 0x02, 0x01, 0x09, 0x02, 0x01, 0x09, 0x02,
    0x01, 0x09, 0x02, 0x01, 0x09, 0x02, 0x01, 0x09, 0x02, 0x01, 0x09, 0x02, 0x01, 0x09, 0x02, 0x01,
    0x09, 0x02, 0x01, 0x09, 0x02, 0x01, 0x09, 0x02, 0x01, 0x09, 0x01, 0x00, 0x00, 0x02, 0x00, 0x03,
    0x03, 0x00, 0x06, 0x04, 0x00, 0x09, 0x01, 0x00, 0x12, 0x02, 0x00, 0x15, 0x03, 0x00, 0x18, 0x04,
    0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00,
    0x21, 0x04, 0x00, 0x21, 0x01, 0x00, 0x00, 0x02, 0x00, 0x03, 0x03, 0x00, 0x06, 0x04, 0x00, 0x09,
    0x01, 0x00, 0x12, 0x02, 0x00, 0x15, 0x03, 0x00, 0x18, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04,
    0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x01, 0x00,
    0x00, 0x02, 0x00, 0x03, 0x03, 0x00, 0x06, 0x04, 0x00, 0x09, 0x01, 0x00, 0x12, 0x02, 0x00, 0x15,
    0x03, 0x00, 0x18, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04,
    0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x01, 0x00, 0x00, 0x02, 0x00, 0x03, 0x03, 0x00,
    0x06, 0x04, 0x00, 0x09, 0x01, 0x00, 0x12, 0x02, 0x00, 0x15, 0x03, 0x00, 0x18, 0x04, 0x00, 0x21,
    0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04,
    0x00, 0x21, 0x01, 0x00, 0x00, 0x02, 0x00, 0x03, 0x03, 0x00, 0x06, 0x04, 0x00, 0x09, 0x01, 0x00,
    0x12, 0x02, 0x00, 0x15, 0x03, 0x00, 0x18, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21,
    0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x01, 0x00, 0x00, 0x02,
    0x00, 0x03, 0x03, 0x00, 0x06, 0x04, 0x00, 0x09, 0x01, 0x00, 0x12, 0x02, 0x00, 0x15, 0x03, 0x00,
    0x18, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21,
    0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x01, 0x00, 0x00, 0x02, 0x00, 0x03, 0x03, 0x00, 0x06, 0x04,
    0x00, 0x09, 0x01, 0x00, 0x12, 0x02, 0x00, 0x15, 0x03, 0x00, 0x18, 0x04, 0x00, 0x21, 0x04, 0x00,
    0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21,
    0x01, 0x00, 0x00, 0x02, 0x00, 0x03, 0x03, 0x00, 0x06, 0x04, 0x00, 0x09, 0x01, 0x00, 0x12, 0x02,
    0x00, 0x15, 0x03, 0x00, 0x18, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00,
    0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x01, 0x01, 0x03, 0x02, 0x01, 0x09,
    0x02, 0x01, 0x09, 0x02, 0x01, 0x09, 0x02, 0x01, 0x09, 0x02, 0x01, 0x09, 0x02, 0x01, 0x09, 0x02,
    0x01, 0x09, 0x02, 0x01, 0x09, 0x02, 0x01, 0x09, 0x02, 0x01, 0x09, 0x02, 0x01, 0x09, 0x02, 0x01,
    0x09, 0x02, 0x01, 0x09, 0x01, 0x00, 0x00, 0x02, 0x00, 0x03, 0x03, 0x00, 0x06, 0x04, 0x00, 0x09,
    0x01, 0x00, 0x12, 0x02, 0x00, 0x15, 0x03, 0x00, 0x18, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04,
    0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x01, 0x00,
    0x00, 0x02, 0x00, 0x03, 0x03, 0x00, 0x06, 0x04, 0x00, 0x09, 0x01, 0x00, 0x12, 0x02, 0x00, 0x15,
    0x03, 0x00, 0x18, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04,
    0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x01, 0x00, 0x00, 0x02, 0x00, 0x03, 0x03, 0x00,
    0x06, 0x04, 0x00, 0x09, 0x01, 0x00, 0x12, 0x02, 0x00, 0x15, 0x03, 0x00, 0x18, 0x04, 0x00, 0x21,
    0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04,
    0x00, 0x21, 0x01, 0x00, 0x00, 0x02, 0x00, 0x03, 0x03, 0x00, 0x06, 0x04, 0x00, 0x09, 0x01, 0x00,
    0x12, 0x02, 0x00, 0x15, 0x03, 0x00, 0x18, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21,
    0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x01, 0x00, 0x00, 0x02,
    0x00, 0x03, 0x03, 0x00, 0x06, 0x04, 0x00, 0x09, 0x01, 0x00, 0x12, 0x02, 0x00, 0x15, 0x03, 0x00,
    0x18, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21,
    0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x01, 0x00, 0x00, 0x02, 0x00, 0x03, 0x03, 0x00, 0x06, 0x04,
    0x00, 0x09, 0x01, 0x00, 0x12, 0x02, 0x00, 0x15, 0x03, 0x00, 0x18, 0x04, 0x00, 0x21, 0x04, 0x00,
    0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21,
    0x01, 0x00, 0x00, 0x02, 0x00, 0x03, 0x03, 0x00, 0x06, 0x04, 0x00, 0x09, 0x01, 0x00, 0x12, 0x02,
    0x00, 0x15, 0x03, 0x00, 0x18, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00,
    0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x01, 0x00, 0x00, 0x02, 0x00, 0x03,
    0x03, 0x00, 0x06, 0x04, 0x00, 0x09, 0x01, 0x00, 0x12, 0x02, 0x00, 0x15, 0x03, 0x00, 0x18, 0x04,
    0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00, 0x21, 0x04, 0x00,
    0x21, 0x04, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x55, 0x55, 0x04, 0x00, 0x08, 0x08,
    0x00, 0x7F, 0x01, 0x3F, 0xFF, 0xFF, 0xFF, 0x03, 0xFF, 0x00, 0x00, 0x01, 0x01, 0x10, 0x60, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x01, 0x15, 0x00, 0x15, 0x00, 0x15, 0x00, 0x15, 0x00, 0x15, 0x00, 0x15,
    0x00, 0x00, 0x00, 0x01, 0x99, 0x99, 0x99, 0x99, 0x40, 0x58, 0x01, 0x40, 0x58, 0x01, 0x54, 0x23,
    0x46, 0x20, 0x00, 0x00, 0x00, 0x00, 0x16, 0x17, 0x70, 0x18, 0x75, 0x00, 0x00, 0x60, 0x60, 0x17,
    0x60, 0x30, 0x25, 0x60, 0x20, 0x13, 0x75, 0x00, 0x00, 0x60, 0x00, 0x30, 0x60, 0x00, 0x30, 0x60,
    0x20, 0x13, 0x75, 0x00, 0x00, 0x50, 0x07, 0x00, 0x60, 0x72, 0x00, 0x60, 0x20, 0x13, 0x75, 0x00,
    0x00, 0x60, 0x01, 0x00, 0x00, 0x60, 0x40, 0x58, 0x01, 0x60, 0x40, 0x26, 0x40, 0x15, 0x40, 0x58,
    0x01, 0x40, 0x58, 0x01, 0x60, 0x00, 0x03, 0x60, 0x00, 0x60, 0x60, 0x63, 0xCD, 0x40, 0x32, 0x63,
    0xCD, 0x40, 0x32, 0x63, 0xCD, 0x40, 0x32, 0x00, 0x04, 0x40, 0x32, 0x43, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x40, 0x02, 0x60, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
    0x02, 0x08, 0x04, 0x54, 0x02, 0x21, 0x00, 0x00, 0x05, 0x02, 0x04, 0x00, 0x01, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00,
};

u16  GetCTSTGateNum(void)
{
   return (sizeof(TableCommCSGate)/sizeof(STR_EVEN_CT_ST_GATE));
}

//////获得通信执行模块表的元素个数
u16 GetControlTableNum(void)
{
    return (sizeof(TableCommControl)/sizeof(STR_TAB_CMMCONTROL));
}

////获得读数据大类的元数个数
u16 GetCommReadTypeNum(void)
{
    return (sizeof(TableCommReadBlock)/sizeof(STR_TABLE_BLOCK_TYPE));
}

/////电量数据的大块分类表的元数个数
u16 GetECBlockPhaseTableNum(void)
{
    return (sizeof(TableCommPhaseBlock)/sizeof(STR_EC_BLOCK_PHASE_ID));
    
}
#if 0
/////电量小类列表
u16 GetECTypeBlockTableNum(void)
{
    return (sizeof(TableReadECBlock)/sizeof(STR_EC_BLOCK_ID));
}
#endif

#if 0
////变量列表
u16 GetVariableTableNum(void)
{
    return (sizeof(TableVariable)/sizeof(STR_VARIABLE_ID));
}
////ID特殊的变量列表
u16 GetEscepecialVariableNum(void)
{
    return (sizeof(TableVariableEscipe)/sizeof(STR_VARIABLE_ESPECEIVE));
}
#endif
////事件大类列表
u16 GetEvenBlockTypeNum(void)
{
    return (sizeof(TableCommEvenType)/sizeof(STR_COMM_EVENTYPE));
}


/////字节定义
COMM_CONST  uchar UseFeezeBit[]=
{
    BIT0,BIT1,BIT2,BIT3,BIT4,BIT5,BIT6,BIT7
};

///事件列表
/*
u16 GetEvenRecod(void)
{
    return (sizeof(TableEvenRecord)/sizeof(STR_EVEN_RECORD));
}
*/
////事件中的故障类
u16 GetEvenTypeFailureNum(void)
{
    return (sizeof(TableCommEvenFAILURE)/sizeof(STR_COMM_EVEN_BLOCK_FAILURE));
}

////失压事件的的长度
u16 GetEvenLoseVoltageNum(void)
{
    return (sizeof(ucEvenLosevoltageLenth));
}
////失压类事件的个分相头的表的长度(失流与失压共用)
u16 GetEvenLoseVoltagePhaseNum(void)
{
    return (sizeof(TableTwotableAddr)/sizeof(STR_COMM_EVEN_FAILURE_TWOTABLE_ADDR));
}

////电压/电流不平衡记录表的长度
u16 GetEvenVolCurUnblanceNum(void)
{
    return (sizeof(ucEvenUblanceLenth));
}
////电压/电流逆相序表的长度
u16 GetEvenConverseNum(void)
{
    return (sizeof(ucEvenConverseLenth));
}

////失流,过流,断相,数据长度表
u16 GetEvenLoseCurrentNum(void)
{
    return (sizeof(ucEvenLoseCurrentLenth));
}


////电压合格率事件记录长度
u16 GetCheckOutVoltageNum(void)
{
    return (sizeof(ucEvenVoltagecheckOut)); 
}
///电压合格率事件记录类型在表中的位置
u16 GetCheckOutVoltageType(void)
{
    return (sizeof(TableVoltagecheckOutaddr)/sizeof(STR_COMM_EVEN_VOLTAGE_CHECKOUT_ADDR));
}

////需量超限总次数表的长度
u16 GetEvenMDOverLoadTim(void)
{
    return (sizeof(ucEvenMDOverLoad));
}

////需量超限记录数据表的长度
///
u16 GetEvenMDOverLoadRecordLenth(void)
{
    return (sizeof(ucEvenMDOverLoadRecord));
}

////需量超限记录数据表的长度
u16 GetEvenMDOverLoadRecord(void)
{
    return (sizeof(TableMDOverLoadAddr)/sizeof(STR_COMM_EVEN_MD_OVER_LOAD));
}

///操作类事件表的长度
u16 GetEvenMeterHandileNum(void)
{
    return (sizeof(TableEvenMeterHandle)/sizeof(STR_EVEN_RECORD_METER_HANDLE));
}

////事件类
u16 GetEvenDataFormatNum(void)
{
    return (sizeof(TableEvenDataToFormat)/sizeof(STR_EVEN_RECORD_CHANGETOFORMAT));
}
////参变量类表个数
u16 GetParameterTableNum(void)
{
  return(sizeof(TableParaMeter)/sizeof(ST_COMM_DISP_LIST));
}
////增加的参变量类表个数
u16 GetAddParameterTableNum(void)
{
  return(sizeof(AddPara)/sizeof(ST_COMM_ADD_PARA));
}
////冻结数据
u16 GetFreezedataNum(void)
{
    return (sizeof(TableFreezeType)/sizeof(STR_FREEZE_DATA_TYPE));
}














