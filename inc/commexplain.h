#ifndef __COMMEXPLAIN_H__
#define __COMMEXPLAIN_H__

#define COMMEXPLAIN_EXT             extern
#undef COMMON_EXT
#ifdef __COMMEXPLAIN_C__
#define COMMON_EXT
#else
#define COMMON_EXT  extern
#endif

#define METER_TYPE_THERRPHASE       0     ///简单三相
#define METER_TYPE_THERRPHASE_MORE       1   ///多功能

#define COMM_METER_TYPE     METER_TYPE_THERRPHASE_MORE 
#define NOACT   (2)

////简单三相与复杂三相的区别定义
#if (COMM_METER_TYPE ==METER_TYPE_THERRPHASE)        //简单三相

#elif(COMM_METER_TYPE ==METER_TYPE_THERRPHASE_MORE)  ///复杂三相(多功能)

                #define COMM_CONST                              const
        
        #define COMM_READ_EC_LENTH                  5    ///李家成4字节,张龙5字节
        #define COMM_READ_EC_FEE_MAXSIZE    ((DLT_PRICE_NUM_MAX)+(1))    ///电量数据块中的最大项目数(费率数)    // 采用4费率方案
        #define COMM_READ_EC_BLOCK_CHECK        0           ///电量数据块中的校验字节数
        
        #define COMM_READ_MD_LENTH              4      ///李家成4字节,张龙5字节
        #define COMM_READ_MD_TIME_LENTH         5      ///李家成4字节,张龙5字节
        #define COMM_READ_MD_ID_LENTH           (COMM_READ_MD_LENTH+COMM_READ_MD_TIME_LENTH)
        
        #define COMM_READ_MD_FEE_MAXSIZE    ((DLT_PRICE_NUM_MAX)+(1))       ///需量数据块中的最大项目数(费率数)
        #define COMM_READ_FREEZE_FEE_MAXSIZE            COMM_READ_EC_FEE_MAXSIZE    ///冻结的最大费率个数
        #define COMM_READ_FREEZE_VARIABLE_LENTH         3    ///冻结的变量数据字节的长度
        #define COMM_READ_FREEZE_VARIABLE_MAXSIZE       8       ////冻结的变量数据字节的个数
        #define COMM_READ_FREEZE_RECORDTIM                  12   ///冻结记录的次数
        
        //#define COMM_READ_EC_GETTWOTABLE_ADDRERR           GAL_GETTWOTABLE_ADDRERR   ///错误
        #define COMM_READ_EC_GETTWOTABLE_ADDRERR           0xFFFFFFFF
        
        #define COMM_METERADDR                      RAM_USER_COMM_ADDR
        #define COMM_EC_HISTORYDATA_START_ADDR                          TYPE_HISTROY_POWER_RECORD ////电量起始数据起始
        #define COMM_MD_HISTORYDATA_START_ADDR                          TYPE_HISTROY_DEMAND_RECORD ////需量起始数据起始
        
        #define COMM_FEE_SEASON_NUM                                         OCT_TO_HEX(DLT_SEASON_TABLE_MAX)     ////年时区数
        #define COMM_FEE_DAYTABLE_NUM                                       OCT_TO_HEX(DLT_DAY_TABLE_MAX)     ////日时段表数
        #define COMM_FEE_DAYTOU_NUM                                         OCT_TO_HEX(DLT_DAY_PIECE_MAX)    ////日时段数
        #define COMM_FEE_FEE_NUM                                            OCT_TO_HEX(DLT_PRICE_NUM_MAX)   ////费率数
        #define COMM_FEE_HOLIDAY_NUM                                        (DLT_HOLIDAY_NUM_MAX)  ////公共假日数目
        
        #define COMM_DSP_EC_DOT_MAX                                         0x04   ////电量小数的最大位数
    //  #define COMM_DSP_EC_INTER_MAX                                       0x08   ////电量整数的最大位数
        #define COMM_DSP_MD_DOT_MAX                                         0x04   ////需量量小数的最小位数
    
        #define COMM_COMMTYPE_NUM                                               4    ////通信信道个数
          
                #define COMM_EVEN_RECORD_NUM                                                                              10
              
#endif


#define BIT0        0x01
#define BIT1        0x02
#define BIT2        0x04
#define BIT3        0x08
#define BIT4        0x10
#define BIT5        0x20
#define BIT6        0x40
#define BIT7        0x80

/////测试模式
#define HISTORY_TEST            1      ///历史是否使用   
#define COMM_TEST                       0     ////测试模式   
////返回错误信息
#define COMM_RETURN_ERR_STATE     BIT1     ///无请求数据
#define COMM_READ_EC_FORMAT_LENTH   4   ///规约中的电量字节个数

#define COMM_READ_MD_FORMAT_LENTH                       3      ///规约中的最大需量个数
#define COMM_READ_MD_TIME_FORMAT_LENTH          5      ///规约中的最大发生时间

#define COMM_READ_FREEZE_VARIABLE_FORMATLENTH           3    ///规约中冻结的变量数据字节的长度
#define COMM_READ_FREEZE_VARIABLE_FORMATMAXSIZE     8       ////规约中的变量数据字节的个数


#define COMM_READ_EC_PHASE_WITHCOMBINACTIVE     0   ////分相组合有功项是否存在 0:无,1,有
#define COMM_READ_EC_HISTORY                    12       ///历史电量为12次
#define COMM_READ_MD_HISTORY                    12      ///历史需量为12次

#define COMM_READ_EC_FORMAT_MAXID     0x0C     ///电量DI2中最大的ID

#define COMM_READ_RETURN_FRAME_FLAG         0x4000   ////返回帧的标记

/////645标准的头,尾,定义
#define FORMAT_FRAME_HEAD               0x68
#define FORMAT_FRAME_END                0x16


#define COMM_BUFFERSIZE      300         /////如果是负荷记录的话就必须要300个字节以上，否则250个字节就足够了
#define COMM_READMAXSIZE         192    ///最大的读出数据


#define COMM_TURE        0
#define COMM_FAIL        1


#define COMM_SEASON_NUM_OVER     3     ////年时区超
#define COMM_DAYTABLE_NUM_OVER     4   ////时段数超
//#define COMM_DAYTOU_NUM_OVER      5
#define COMM_FEE_NUM_OVER         5    ////费率数超
#define COMM_HAVE_NO                    8      ///没有该项

#define COMM_CHANGE_BAD_ERR         9     ///通信波特率不能更改

#define COMM_USE                    1
#define COMM_NOUSE              0

////发送的头为FE的字节个数
#define COMM_HEAD_FE_NO      4
#define COMM_HEAD_ADDR_LEN  8  ///地址加上帧头尾的长度

typedef struct
{
    uchar Head[COMM_HEAD_ADDR_LEN+2+COMM_HEAD_FE_NO];  ///FE+头+地址+头+控制码+长度
    uchar Buffer[COMM_BUFFERSIZE];      ////返回数据
}STR_RETURN_EXPLAINBUFFER;

typedef struct
{
    u16 Lenth:12;
    u16 More:2;    ////如果失败,00:表示无该项,01:表示无授权
    u16 LastFrame:1;       ////0无后续,1有后续
    u16 ReturnFail:1;     ////0,成功,1失败 
}STR_RETURN_PARA;
/////函数返回参数
typedef union
{
        u16 uiReturnData;
        STR_RETURN_PARA  strReturnData; 
}STR_READ_RETURN_PARA;


typedef  void  (*WReturnFUNCTION)(STR_READ_RETURN_PARA * Dest,ulong ID);
typedef  uchar (*WithReturnFUNCTION)(void);
//////输入的参数:数据地址,数据的长度,返回数据的长度
///返回数据
typedef  uchar (*CheckFunction)(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);



extern void NULLFunction(void);
extern void NULLFunctionWithReturn(uchar *Dest,ulong ID);
///////////////////////////////////////////////////////////////
typedef struct
{
    
    uchar CommReturnValue:1;
    uchar CommAddrType:7;  
    
}STR_COMMTYPE_STAEPARA;

////通信控制函数表
typedef struct
{
    uchar ucControlDataID;  ///控制码
    PEFUNCTION   CommFunction;       ///该控制码对应的函数
    STR_COMMTYPE_STAEPARA   strCommControlPara;    ////操作该控制函数的一系列参数
}STR_TAB_CMMCONTROL;


/////读数据需要传入的参数
typedef struct
{
    ulong ulID;                 ////数据ID
    uchar ucFrameNum;           ///帧序号
    uchar ucLoadBlockNum;       ////负荷记录块数
    uchar BCDLoadTim[6];       ///负荷记录起始时间
    uchar CommNum;      ////通信端口号
}STR_READDATA_INPUT;


/////后续帧Buffer内容的定义
#define LAST_FRAME_MAXSIZE              10
#define LAST_FRAME_BLOCKSIZE            192   ////缓存固定大小
#define LAST_FRAME_NUM                      18   ////缓存个数


////传入后续帧管理的函数中的参数结构
typedef struct
{
    uchar   ucCommNo;    ////通信通道号
    uchar   ucFrameNo;   ////后续帧号
    uchar   ucFormatLen;  ///缓存使用的长度
    uchar   ucUsed;     ///是否被使用,00,没有,01占用.
    ulong   ulID;               ////ID
}STR_LASTFRAME_IN_PARA;

typedef struct
{
    STR_LASTFRAME_IN_PARA  HeadPara;   ////缓存的头文件参数
    uchar   Buffer[LAST_FRAME_BLOCKSIZE];   ///缓存
}STR_READ_LASTFRAME;


////后续帧中需要管理的数据结构:读后续帧需判断,判断完后需要修改的
typedef struct
{
    uchar   ucCommNo;    ////通信通道号
    uchar   ucHaveLast;    ///0 没有后续,1 有后续
    ulong   ulLastID;          ////后续ID
    uchar   LastFrameNo;    ///帧序号
}STR_LASTFRAME_Control_PARA;


#define  COMM_HAVE_RETURN        1
#define  COMM_HAVE_NO_RETURN        0

#define  SWITCH_TABLE_ERR          0xFFFF
#define TAB_CMMCONTROL_NUM       2        /////表元数的个数(暂时使用2个后面扩展)

////07 
#define COMMTYPE_07                     0x00             ///                    
#define COMMTYPE_ALLCOMM                0x03 

#define COMMTYPE_READ                   0x11        //读数据
#define COMMTYPE_READWITHLAST           0x12        //读后续帧
#define COMMTYPE_WRITEDATA              0x14        //写数据
#define COMMTYPE_READADDR               0x13        //读通讯地址
#define COMMTYPE_WRITEADDR              0x15        //写通讯地址
#define COMMTYPE_BROADCAST              0x08        //广播校时
#define COMMTYPE_FEEZEDATA              0x16        //电量冻结指令
#define COMMTYPE_CHANGEBAUDRATE         0x17        //更改通讯速率
#define COMMTYPE_CHANGEPASSWORD         0x18        //更改密码
#define COMMTYPE_CLEARMD                0x19        //清需量
#define COMMTYPE_CLEAREC                0X1A        //电表清0
#define COMMTYPE_CLEAREVEN              0X1B        //事件清0
#define COMMTYPE_RELAYSET               0X1C        //继电器设置
#define COMMTYPE_MULTIPORT              0x1D        //多功能口设置

#define COMMTYPE_FARCTL                 0x03
#define COMMTYPE_DISPLAY                0x07        //显示查询
#define COMMTYPE_DLTDATA                0x09        //数据查询
#define COMMTYPE_ZB                     0x1F

///97
#define COMMTYPE_97                     0x01

//
#define COMMTYPE_ERR                        0xFF

//#define COMMTYPE_STAEPARA_RETURN      1
////STR_COMMTYPE_STAEPARA  数据中的定义最高位定义是否有返回值，
////第1 位表示使用正确的表地址。
///第2 位表示可以使用正确的统配地址(AA)。
///第3 位表示可以使用正确的全部统配地址(AA)。
///第4 位表示可以使用正确的广播地址(99)。
///第8位表示是否有返回帧
#define COMMTYPE_STAEPARA_RIGHTADDR   0x01
#define COMMTYPE_STAEPARA_AA_ADDR      0x02
#define COMMTYPE_STAEPARA_ALLAA_ADDR     0x04
#define COMMTYPE_STAEPARA_BROADCAST_ADDR  0x08

#define COMMTYPE_STAEPARA_RETURN      0x01
#define COMMTYPE_STAEPARA_ADDR_ERR      0X00

//////读数据帧的长度
#define COMM_READ_LENTH_NORMAL     0X04     //一般的读写
#define COMM_READ_LENTH_LOADNUM    0X05     //读负荷记录的后续帧
#define COMM_READ_LENTH_LOADTIM    0X0A     //读负荷记录，数据帧中包含记录起始时间

//////读数据类型分类
#define COMM_READ_TYPE_EC     0X00
#define COMM_READ_TYPE_MD     0X01
#define COMM_READ_TYPE_VARIANLE     0X02
#define COMM_READ_TYPE_EVEN     0X03
#define COMM_READ_TYPE_PARA     0X04
#define COMM_READ_TYPE_FREEZE     0X05
#define COMM_READ_TYPE_LOAD     0X06

#define COMM_READ_TYPE_ZEROFEEZE  0X08

#define COMM_READ_TYPE_LOSS_VOLTAGE         0X10
#define COMM_READ_TYPE_DOWN_VOLTAGE     0X11
#define COMM_READ_TYPE_OVER_VOLTAGE         0X12
#define COMM_READ_TYPE_CUT_VOLTAGE      0X13
#define COMM_READ_TYPE_ORDER_VOLTAGE    0X14
#define COMM_READ_TYPE_ORDER_CURRENT    0X15
#define COMM_READ_TYPE_UNBALANCE_VOLTAGE    0X16
#define COMM_READ_TYPE_UNBALANCE_CURRENT    0X17
#define COMM_READ_TYPE_LOSS_CURRENT     0X18
#define COMM_READ_TYPE_OVER_CURRENT     0X19
#define COMM_READ_TYPE_CUT_CURRENT      0X1A
#define COMM_READ_TYPE_REVERSEPOWER     0X1B
#define COMM_READ_TYPE_POWEROVER        0X1C
#define COMM_READ_TYPE_RELAY_OPEN       0X1D
#define COMM_READ_TYPE_RELAY_CLOSE      0X1E
#define COMM_READ_TYPE_OVERTOTALCOS     0X1F




////////////////////////////////////////////////////////////////////////////////
#define COMM_RETURN_STATE_FAIL    0x8000
#define COMM_RETURN_STATE_WITHLAST    0x4000
#define COMM_RETURN_FAIL_NO_ACCREDIT        0x1000  ///返回的是无授权的
#define COMM_RETURN_STATE_DATA_LENTH  0X0FFF


///////////////////////事件//////////////////////////////////////////
///事件的大类
#define COMM_EVEN_BLOCK_FAILURE                 0x00         ///故障类事件
#define COMM_EVEN_BLOCK_VOLTAGE_CHECKOUT  0X01     ///电压合格率事件
#define COMM_EVEN_BLOCK_MD_OVER                     0x02     ///需量超限类
#define COMM_EVEN_BLOCK_METER_HANDLE      0x03     ////电表操作类   
#define COMM_EVEN_BLOCK_METER_CUTGATE   0x04    ///拉合闸事件类
#define COMM_EVEN_BLOCK_CARD           0x05     ////卡表操作类


////故障类事件
#define COMM_EVEN_FAILURE_RECORD_TIM                    10              ////记录次数    

#define COMM_EVEN_TYPE_VOLTAGE              0x00       ///失压
#define COMM_EVEN_TYPE_ALLLOSEVOLTAGE   0x01      ////全失压
#define COMM_EVEN_TYPE_ASSISTANT_POWERLOSE      0x02    ///辅助电源失电
#define COMM_EVEN_TYPE_CONVERSE             0x03                ////电压/电流逆相序
#define COMM_EVEN_TYPE_UNBLANCE         0x04                    ////电压/电流不平衡
#define COMM_EVEN_TYPE_SWIM_OVERLOAD    0X05                /////潮流反向与过载
#define COMM_EVEN_TYPE_CURRENT_FAILUE   0X06      ////电流类故障
#define COMM_EVEN_TYPE_POWEROFF             0x07                ///掉电

#define COMM_EVEN_FAILURE_LOSEVOLTAGE_TOTAL         18        /////失压记录次数与总累计时间的数据长度
#define COMM_EVEN_FAILURE_ALL_LOSEVOLTAGE_TOTAL 6        ////全失压的记录次数与总累计时间的数据长度
#define COMM_EVEN_FAILURE_LOSE_ACPPOWER_TOTAL       6        ////辅助电源失电总次数,累计时间
#define COMM_EVEN_FAILURE_CONVERSE_VOL_CUR_TOTAL 6      ////电压,电流逆相序
#define COMM_EVEN_FAILURE_UNBLANCE_VOL_CUR_TOTAL 6                  ////电压,电流,不平衡,总累计时间,累计次数
#define COMM_EVEN_FAILURE_REVER_CURRENT_TOTAL        18        ////电流反向,过载
#define COMM_EVEN_FAILURE_LOSE_CURRENT_TOTAL            18        ////失流,过流,断流
#define COMM_EVEN_FAILURE_POWEROFF_TOTAL                    3                   ////掉电

#define COMM_EVEN_METER_HANDLE_TOTAL                            3        ///电表操作记录总次数的数据长度
#if (CONFIG_METER_AREA_MODE_SOUTHGRID==CONFIG_METER_AREA_MODE)
#define COMM_EVEN_FAILURE_ALL_LOSEVOLTAGE_LENTH     131      ///全失压记录数据长度
#else
#define COMM_EVEN_FAILURE_ALL_LOSEVOLTAGE_LENTH     15      ///全失压记录数据长度
#endif
#define COMM_EVEN_FAILURE_LOSE_ACPPOWER_LENTH           12      ////辅助电源失电发生时刻,结束时刻
#define COMM_EVEN_FAILURE_POWER_OFF_LENTH                   12      //掉电记录

#define COMM_EVEN_FAILURE_VOLTAGECHECKOUT_RECORD    12     ///电压合格率记录12个月

////主要解析DI3
typedef struct
{
    uchar ucIDBlockType;   ///读出数据的类型
    WReturnFUNCTION  TypeFunction; ////读出数据相应的函数
    
}STR_TABLE_BLOCK_TYPE;


////主要解析电量类的DI2
typedef struct
{
    uchar Block1Start;    ///电量数据1块中开始的ID号
    uchar Block1END;      ///电量数据1块中结束的ID号
}STR_EC_BLOCK_PHASE_ID;


////主要解析电量类中的DI2,并归类块首地址
typedef struct
{
    uchar  ECTypeID;   ///合相电量类细分ID
    uchar  ECUseState:1;     ///当前电量是否存在该项(0无,1有),
    uchar  ECFeeState:1;     ///当前电量项是否包含费率元素(0无,1有),
    uchar  ECHistoryState:1;     //历史电量是否存在该项(0无,1有),
    uchar  ECHistoryFeeState:1;     ///历史电量该项是否有费率   
    uchar  MDUseState:1;     ///当前需量是否存在该项(0无,1有),
    uchar  MDFeeState:1;     ///当前需量项是否包含费率元素(0无,1有),
    uchar  MDHistoryState:1;     //历史需量是否存在该项(0无,1有),
    uchar  MDHistoryFeeState:1;     ///历史需量该项是否有费率   
    ulong  ECAddr;      ///电量地址
    ulong  MDAddr;     ///需量地址
        
}STR_EC_BLOCK_ID;


////解析的是卡表类的数据，针对DI2=0x90的电量数据
typedef struct
{
  uchar TypeID1;   //DI1
  uchar TypeID0;   //ID0
  uchar UsedAble;  //是否被使用
  uchar FormatLen;  //规约长度
  uchar AcceLen;   //存储的长度
  ulong DataAddr;  //数据类型
  
}STR_EC_CARD_ID;


///////解析拉合闸类数据，针对DI2=0X31的事件记录
typedef struct
{
  uchar  EvenType;     ////类型(ID1)
  ulong  TotalCountAddr;   ///次数记录地址
  ulong  RecordAddr;      ////记录内容二次表地址
  u16  RecordTim;      ///记录次数
  uchar  UsedState;     ///是否使用0没有，1 使用
  
}STR_EVEN_CT_ST_GATE;




#define NULLDATAADDR   0xFFFFFFFF     ////,没有定义的地址为0xFFFFFFFF

typedef struct
{
    uchar IDType;   ////DI1
    uchar Used:1;     ///是否使用
    uchar StartID:3;     ///ID1是否是从哪个开始的,
  uchar UsedID1Num:3;  ///ID1使用了几个
    uchar WithFF:1;       ///ID1为FF也可以抄收.0:不可以,1:可以
    uchar RecordTim;      ///记录的次数(ID0)00:代表不能用FF抄收.>0的话,就可以用FF抄收
    uchar UseFormat:4;  ///存储使用的字节长度(长度不会超过15)
    uchar FormatLenth:4;   ////规约格式使用的字节长度(长度不会超过15)
    ulong Addr;         ////地址

}STR_VARIABLE_ID;     ////变量数据标识

////变量表中的特殊项0x80,由于长度不会超过15所以长度用半字节来表示
typedef struct
{
    uchar IDType;   ////DI0
    uchar Used:1;     ///是否使用0:没有,1,使用
    uchar FormatLenth:3;     ///规约使用的长度
    uchar UsedLenth:4;         ///存储使用的长度
    ulong Addr;         ////地址
}STR_VARIABLE_ESPECEIVE;


///////////////////////////////事件///////////////////////////////////////////////////////////////
////事件的归类
typedef struct
{
    uchar IDTypeStart;     ///起始ID
    uchar IDTypeEnd;      ///结束ID
    uchar IDType;        ///事件的类别
    uchar UsedState;  ////是否被使用
    
}STR_COMM_EVENTYPE;

///故障类事件(失压,欠压,过压,断相类.)
typedef struct
{
    uchar EvenRecordID;    ///事件的ID
    uchar EvenType;             ///事件类型
    ulong TotalAddr;      ////事件记录总地址(DI1=0,DI0=0)
    uchar RecordTim;            ////记录的次数0:代表没有使用该项,
    uchar TotalLenth;    ////累计次数,时间的记录长度
}STR_COMM_EVEN_BLOCK_FAILURE;

typedef struct s_cnttime
{
    ulong ulID;                 //数据标识
    ulong ulAddr;               //数据地址
}S_CNTTIME;

typedef struct s_evfmt
{
    uchar ucOffset;             //在记录中的偏移
    uchar ucLen;                //子项数据的长度
    uchar ucType;    
}S_EVFMT;

typedef struct s_idconv1
{
    ulong   ulVID;              //虚拟id
    uchar   ucSim1;             //ID1允许的最大项
    uchar   ucSim0;             //ID0允许的最大项
    uchar   ucType;             //记录类别,用于查二次表
    uchar   reserved;           //保留
    void*   pvFmt;              //指向格式表的指针
}S_IDCONV1;

////故障类事件二次表各分相的二次表地址
typedef struct
{
    uchar IDType;
    uchar APhaseAddr;
    uchar BPhaseAddr;
    uchar CPhaseAddr;
}STR_COMM_EVEN_FAILURE_TWOTABLE_ADDR;


////电压合格率类事件
typedef struct
{
    uchar IDType;      ////ID1
    ulong Currently;   ////当前地址
    u16  HistoryTwoTable;   ////二次表地址
}STR_COMM_EVEN_VOLTAGE_CHECKOUT_ADDR;


///需量超限记录
typedef struct
{
    uchar IDType;     ///ID1
    u16  TwoTableAddr;  ///二次表位置
    uchar UsedState;     ///是否被使用
}STR_COMM_EVEN_MD_OVER_LOAD;

////事件的记录内容
typedef struct
{
    uchar EvenID;       ///事件ID,ID2,
    uchar Type;        ///事件的分类
    uchar RecordNum;   ///记录次数
    
}STR_EVEN_RECORD_TYPE_LOSEVOLTAGE;


/////电表操作
typedef struct
{
    uchar IDType;           ////ID1,事件类型
    uchar *RecordTableLenth;    ////记录内容
    ulong TotalAddr;          ///记录次数的地址
    u16  TwoTableAddr;       ////二次表的地址
    uchar UsedState;                    ///是否被使用
    u16  UseTableSize;             /////规约格式表格的长度
    uchar *FormatTable;      ////规约格式表位置
}STR_EVEN_RECORD_METER_HANDLE;

/////事件的存储格式与规约格式的对照表
typedef struct
{
    uchar IDType;    ////ID1,事件类型
    ///uchar TotalLenth;  ////总累计长度
    uchar *RecordTableLenth;   ////存储内容的格式
    uchar *FormatTableLenth;     ////规约的格式
    uchar  FormatLenth;             ////规约表格的长度
    
}STR_EVEN_RECORD_CHANGETOFORMAT;

#define COMM_EVEN_WEITH_NULL     0x00      ////事件记录中没有使用的数据项用该值填写

/////密码权限
#define COMM_PASSWORD_POPEDOM_0                 0x00    ///0级权限
#define COMM_PASSWORD_POPEDOM_1                 0x01    ///1级权限
#define COMM_PASSWORD_POPEDOM_2                 0x02    ///2级权限
#define COMM_PASSWORD_POPEDOM_3                 0x03    ///3级权限
#define COMM_PASSWORD_POPEDOM_4                 0x04    ///4级权限
#define COMM_PASSWORD_POPEDOM_5                 0x05    ///5级权限
#define COMM_PASSWORD_POPEDOM_6                 0x06    ///6级权限
#define COMM_PASSWORD_POPEDOM_7                 0x07    ///7级权限
#define COMM_PASSWORD_POPEDOM_8                 0x08    ///8级权限
#define COMM_PASSWORD_POPEDOM_9                 0x09    ///9级权限

#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
#define COMM_PASSWORD_FIRST_PARA                (COMM_PASSWORD_POPEDOM_2)
#define COMM_PASSWORD_SECOND_PARA               (COMM_PASSWORD_POPEDOM_2)
#else
#define COMM_PASSWORD_FIRST_PARA                (COMM_PASSWORD_POPEDOM_4)
#define COMM_PASSWORD_SECOND_PARA               (COMM_PASSWORD_POPEDOM_4)
#endif

#define COMM_PASSWORD_LOCKTIME_SIZE             2       // 密码锁定时间长度
#if (CONFIG_METER_AREA_MODE == CONFIG_METER_AREA_MODE_SOUTHGRID) // 南网要求密码连续5次出错，锁密码
#define COMM_PASSWORD_ERR_MAXTIME   4
#else
#if(CONFIG_METER_TYPE==CONFIG_METER_TYPE_SD39C)
#define COMM_PASSWORD_ERR_MAXTIME   4
#else
#define COMM_PASSWORD_ERR_MAXTIME   2
#endif
#endif

////开关量定义
#define COMM_PARAMETER_USED            1   /////使用
#define COMM_PARAMETER_NO_USED         0   ////没有使用
////特殊功能使用
#define COMM_PARAMETER_SAVE_NO_ATTESTATION   0    ///没有特殊功能
////地址类型
#define COMM_DIRECT_ADDRESSING                      0 //////
//#define COMM_
///数据类型
#define COMM_PARAMETER_BCD_TYPE         0     ///BCD类型
#define COMM_PARAMETER_ASC_TYPE         1     ///ASCII类型
////读写控制
#define COMM_WRITE                      0x01    ///写
#define COMM_READ                       0x02    ///读
#define COMM_PASSWORD                   0x04   /////密码,不可读不可写
#define COMM_IDEL                       0x00    ///读写都禁止

/////读出字节长度
#define COMM_HOLIDAY_WORD_SIZE          4     ///公共假日字节长度
#define COMM_CYCLE_DSP_SIZE             5     ///循环显示,按键显示字节长度
#define COMM_SEASON_SIZE                3    ////年时区表长度
#define COMM_EVENT_COUNT_SIZE           3    // 事件次数长度

////////////////冻结//////////////////////////////////////
///冻结的类型
#define  COMM_FREEZE_TIME                       0x00     ///定时冻结
#define  COMM_FREEZE_INSTANTANEOUS  0X01       ///瞬时冻结
#define  COMM_FREEZE_SEANSONTABLE_CHANGE   0X02   ////两套时区表切换冻结
#define  COMM_FREEZE_DAYTABLE_CHANGE            0X03    /////两套日时段表切换冻结
#define  COMM_FREEZE_HOURORHALF                     0x04//整点冻结
#define  COMM_FREEZE_DIVTIMFEE_CHANE                     0x05   ////分时费率切换冻结
#define  COMM_FREEZE_DAY                                0x06   /////日冻结
#define  COMM_FREEZE_STEP_CHANE                          0x07    ////两套阶梯切换冻结



#define  COMM_FREEZE_RECORD_TIM                         60     ////定时冻结记录的次数
#define  COMM_FREEZE_IMMEDIATE_TIM                  3      ////瞬时冻结记录的次数
#define  COMM_FREEZE_FEETABLE_TIM                       2      ////费率时区,时段表记录的次数
#define  COMM_FREEZE_HOUR_TIM                       254  //整点冻结次数
#define  COMM_FREEZE_DIVFEECHANGE_TIM                                     2 ////费率切换冻结次数
#define  COMM_FREEZE_DAY_TIM                                  62   /////日冻结


#define  COMM_FREEZE_ZERO_TIME                                      10///整点冻结次数

#define  COMM_FREEZE_ZEROTIME_NUM                                  48  ///整点冻结的电量数据个数

#define  COMM_FREEZE_MAXLENTH                               20      ////冻结数据的费率数与记录元素的个数如果大于此值的话就要返回帧否则就没有返回帧
////冻结的数据结构
typedef struct
{
    uchar FeezeType;  ////冻结的数据类型,
    uchar UsedState;   ////是否被使用到
    uchar UseLenth;     ///使用的长度(单个元素的长度)
    uchar UseNum;              ////元素个数
    uchar FormatLenth;  ////规约中的格式(单个元素的长度).
    //uchar RecordTim;    /////冻结的次数
}STR_FREEZE_DATA_TYPE;


//////终端通信的数据结构
typedef struct
{
  u16  uiID;    ////使用ID
  ulong ulIRAWAddr;   ////红外写地址
  ulong ulIRARAddr;   ////红外读地址
  ulong ulDataFlagAddr;    ////标志
  u16  uiLenth;           ///数据长度
  uchar WRAccess;          ///读写权限 1只读,2只写,3，可读写
}STR_ZHONGDUAN_COMMDATA;


//////////////////////////////////////////////////////////////
#define ECDI2WITHNO      0xFF   
////////////////////////////////////////////////////////////////////////////////
#define COMM_METRER_ADDR_LENTH          6    ////通信地址的长度

COMMON_EXT  STR_RETURN_EXPLAINBUFFER *CommExpDataBuff;
COMMON_EXT  STR_READ_LASTFRAME  LastFrameData[LAST_FRAME_NUM];

COMMON_EXT  uchar ucOutPutLenth;
COMMON_EXT  uchar ucCommFormatType;   ////规约类型
COMMON_EXT  STR_UART_PARA_CHANGE_CONTROL  UartPotr;     /////通信端口参数
COMMON_EXT  uchar gucFarCtlFlg;
COMMON_EXT uchar isSpcecial_uart;      //由于底层串口是通过全局变量获得，为了简单期间，为了虚拟串口而设
///////万能读写
///读
#define COMM_RECEIVE_ALL_STORYTYPE                    (CommExpReceiveDataBuffer.buff[12])
#define COMM_RECEIVE_ALL_DATALOW                      (CommExpReceiveDataBuffer.buff[13])
#define COMM_RECEIVE_ALL_DATAMID                      (CommExpReceiveDataBuffer.buff[14])
#define COMM_RECEIVE_ALL_DATAHI                       (CommExpReceiveDataBuffer.buff[15])
#define COMM_RECEIVE_ALL_DATALEN                      (CommExpReceiveDataBuffer.buff[16])
#define COMM_RECEIVE_ALL_INDEX                        (CommExpReceiveDataBuffer.buff[12])

////写
#define COMM_WRITE_ALL_STORYTYPE                    (CommExpReceiveDataBuffer.buff[16])
#define COMM_WRITE_ALL_DATALOW                     (CommExpReceiveDataBuffer.buff[17])
#define COMM_WRITE_ALL_DATAMID                     (CommExpReceiveDataBuffer.buff[18])
#define COMM_WRITE_ALL_DATAHI                      (CommExpReceiveDataBuffer.buff[19])
#define COMM_WRITE_ALL_DATALEN                     (CommExpReceiveDataBuffer.buff[20])
#define COMM_WRITE_ALL_DATA                        (CommExpReceiveDataBuffer.buff[21])

////远程拉合闸
#define COMM_RECEIVE_STCTGATE_PASSWORD                (CommExpReceiveDataBuffer.buff[10])
#define COMM_RECEIVE_STCTGATE_USERID                  (CommExpReceiveDataBuffer.buff[14])
#define COMM_RECEIVE_STCTGATE_CONTROLID               (CommExpReceiveDataBuffer.buff[18])

///ADE7758读写
///读
#define COMM_ADE7758_READ_LENTH                                 (CommExpReceiveDataBuffer.buff[14]) 
#define COMM_ADE7758_READ_ADDRH                                 (CommExpReceiveDataBuffer.buff[12])                                                         
#define COMM_ADE7758_READ_ADDRL                                 (CommExpReceiveDataBuffer.buff[13])                                                         
///写
#define COMM_ADE7758_WRITE_LENTH                                    (CommExpReceiveDataBuffer.buff[18]) 
#define COMM_ADE7758_WRITE_ADDRH                                    (CommExpReceiveDataBuffer.buff[16]) 
#define COMM_ADE7758_WRITE_ADDRL                                    (CommExpReceiveDataBuffer.buff[17]) 
#define COMM_ADE7758_WRITE_DATA                                 (CommExpReceiveDataBuffer.buff[19])                 

/////////////////////////////////////////////////////////////////////////////////
#define COMM_RECEIVE_FRAME_ADDRSTART             (CommExpReceiveDataBuffer.buff[1])
#define COMM_RECEIVE_FRAME_CONTROLNO             (CommExpReceiveDataBuffer.buff[8])
#define COMM_RECEIVE_FRAME_LENTH                     (CommExpReceiveDataBuffer.buff[9])
#define COMM_RECEIVE_FRAME_DATA                      (CommExpReceiveDataBuffer.buff[10])

///////写命令帧
#define COMM_RECEIVE_WRITE_PASSWORD             (CommExpReceiveDataBuffer.buff[14]) 
#define COMM_RECEIVE_WRITE_USEDID               (CommExpReceiveDataBuffer.buff[18]) 
#define COMM_RECEIVE_WRITE_DATA                   (CommExpReceiveDataBuffer.buff[22])   


/////后续帧
#define COMM_LAST_FRAME_NUM                             (CommExpReceiveDataBuffer.buff[14]) 


/////写密码
#define COMM_RECEIVE_WRITE_FARME_PASSWORD                 (CommExpReceiveDataBuffer.buff[18])   

/////需量,电表,事件清零的密码起始位
#define COMM_RECEIVE_CLEAR_PASSWORD                   (CommExpReceiveDataBuffer.buff[10])   

#define COMM_RECEIVE_CLEAR_USERNUM                (CommExpReceiveDataBuffer.buff[14])   
////事件清零数据标示
#define COMM_EVEN_CLEAR_DATA                                (CommExpReceiveDataBuffer.buff[18]) 

/////写表地址命令帧
#define COMM_RECEIVE_WRITE_ADDR_DATA                         (CommExpReceiveDataBuffer.buff[10])

////冻结命令
#define COMM_RECEIVE_FEEZE_DATA_MIN                         (CommExpReceiveDataBuffer.buff[10])
#define COMM_RECEIVE_FEEZE_DATA_HOUR                         (CommExpReceiveDataBuffer.buff[11])
#define COMM_RECEIVE_FEEZE_DATA_DAY                         (CommExpReceiveDataBuffer.buff[12])
#define COMM_RECEIVE_FEEZE_DATA_MON                         (CommExpReceiveDataBuffer.buff[13])
/////////////数据块地址的定义

//////终端读写的格式(97版645规约)
#define COMM_ZHONGDUAN_ID                           (CommExpReceiveDataBuffer.buff[10])
#define COMM_ZHONGDUAN_WRITE                        (CommExpReceiveDataBuffer.buff[10])

#define COMM_97TYPE_CONTROLWORD                         (CommExpReceiveDataBuffer.buff[8])
#define COMM_97TYPE_LENGTH                         (CommExpReceiveDataBuffer.buff[9])
#define COMM_97TYPE_PASSWORD                         (CommExpReceiveDataBuffer.buff[12])
#define COMM_97TYPE_WRITEDATA                        (CommExpReceiveDataBuffer.buff[16])

#define COMM_97TYPE_ADDDATAID                         (CommExpReceiveDataBuffer.buff[16]+(CommExpReceiveDataBuffer.buff[17]<<8)) 
#define COMM_97TYPE_ADDDATAIDREAD                         (CommExpReceiveDataBuffer.buff[12]+(CommExpReceiveDataBuffer.buff[13]<<8)) 
#define COMM_97TYPE_ADDDATABEGIN                         (CommExpReceiveDataBuffer.buff[18]) 
#define COMM_97TYPE_ADDDATAREADBEGIN                         (CommExpReceiveDataBuffer.buff[14]) 
#define COMM_97TYPE_READDATA                         (CommExpReceiveDataBuffer.buff[12]) 

#define COMM_MULTIPORT_DATA                         (CommExpReceiveDataBuffer.buff[10])

////广播校时
#define COMM_BCAST_DATA_START                              (CommExpReceiveDataBuffer.buff[10])     
///////修改通信波特率特征字
#define COMM_CHANGE_COMM_BAUT_WORD                            (CommExpReceiveDataBuffer.buff[10])       


// 事件记录长度定义
#define LENGTH_RELAY_EVENT 105


COMMEXPLAIN_EXT COMM_CONST      STR_TAB_CMMCONTROL    TableCommControl[];
COMMEXPLAIN_EXT COMM_CONST    STR_TABLE_BLOCK_TYPE  TableCommReadBlock[];
COMMEXPLAIN_EXT COMM_CONST    STR_EC_BLOCK_ID           TableReadECPhaseBlock[];

//COMMEXPLAIN_EXT COMM_CONST  STR_EC_CARD_ID  TableCardEner[];


COMMEXPLAIN_EXT COMM_CONST    STR_EC_BLOCK_PHASE_ID   TableCommPhaseBlock[];
//COMMEXPLAIN_EXT COMM_CONST    STR_EC_BLOCK_ID    TableReadECBlock[];
//COMMEXPLAIN_EXT COMM_CONST    STR_VARIABLE_ID  TableVariable[];
//COMMEXPLAIN_EXT COMM_CONST    STR_VARIABLE_ESPECEIVE  TableVariableEscipe[];
COMMEXPLAIN_EXT COMM_CONST      STR_COMM_EVENTYPE TableCommEvenType[];
COMMEXPLAIN_EXT COMM_CONST      uchar ucEvenLosevoltageLenth[];
COMMEXPLAIN_EXT COMM_CONST      STR_COMM_EVEN_BLOCK_FAILURE     TableCommEvenFAILURE[];
COMMEXPLAIN_EXT COMM_CONST  STR_COMM_EVEN_FAILURE_TWOTABLE_ADDR  TableTwotableAddr[];
COMMEXPLAIN_EXT COMM_CONST    uchar ucEvenConverseLenth[];
COMMEXPLAIN_EXT COMM_CONST  uchar ucEvenUblanceLenth[];
COMMEXPLAIN_EXT COMM_CONST  STR_COMM_EVEN_VOLTAGE_CHECKOUT_ADDR   TableVoltagecheckOutaddr[];
COMMEXPLAIN_EXT COMM_CONST  uchar ucEvenVoltagecheckOut[];
COMMEXPLAIN_EXT COMM_CONST  uchar ucEvenMDOverLoad[];
COMMEXPLAIN_EXT COMM_CONST  STR_COMM_EVEN_MD_OVER_LOAD  TableMDOverLoadAddr[];
COMMEXPLAIN_EXT COMM_CONST  uchar ucEvenMDOverLoadRecord[];
COMMEXPLAIN_EXT COMM_CONST STR_EVEN_RECORD_METER_HANDLE TableEvenMeterHandle[];
COMMEXPLAIN_EXT COMM_CONST  uchar ucEvenLoseCurrentLenth[];
COMMEXPLAIN_EXT COMM_CONST  uchar ucEvenLoseCurrentLenth[];
COMMEXPLAIN_EXT COMM_CONST  STR_FREEZE_DATA_TYPE        TableFreezeType[];
COMMEXPLAIN_EXT COMM_CONST   uchar   CommFeezeArrWord[];
COMMEXPLAIN_EXT COMM_CONST  uchar ucEvenFeeTableProgram[];

COMMEXPLAIN_EXT COMM_CONST STR_EVEN_RECORD_CHANGETOFORMAT TableEvenDataToFormat[];

COMMEXPLAIN_EXT COMM_CONST STR_EVEN_CT_ST_GATE TableCommCSGate[];
COMMEXPLAIN_EXT  const uchar DEFAULT_VALUE_GROUP[];
COMMEXPLAIN_EXT const S_IDCONV1 gCs_IDConv1[];
COMMEXPLAIN_EXT const S_CNTTIME gCS_CntAndTimeTab[];

COMMEXPLAIN_EXT const uchar gCuc_IDConv1TabNum;
COMMEXPLAIN_EXT const uchar gCuc_CntAndTimeTabNum;

// COMMEXPLAIN_EXT COMM_CONST  STR_ZHONGDUAN_COMMDATA  TableZhongDuanComm[];

//////位定义
COMMEXPLAIN_EXT COMM_CONST uchar UseFeezeBit[];

COMMEXPLAIN_EXT  uchar GetComm645ControlNO(void);
COMMEXPLAIN_EXT  u16 GetControlTableNum(void);
COMMEXPLAIN_EXT  u16 GetCommReadTypeNum(void);
COMMEXPLAIN_EXT u16  GetDataByID(STR_READDATA_INPUT* Src);
COMMEXPLAIN_EXT u16  GetVariableTableNum(void);
COMMEXPLAIN_EXT u16 GetEvenBlockTypeNum(void);
COMMEXPLAIN_EXT u16 GetEvenTypeFailureNum(void);

//COMMEXPLAIN_EXT u16 GetCardEnergyTableNum(void);

COMMEXPLAIN_EXT u16 GetZhongDuanTableNum(void);

COMMEXPLAIN_EXT u16 GetEvenMDOverLoadRecordLenth(void);
COMMEXPLAIN_EXT u16 GetEvenMDOverLoadRecord(void);
COMMEXPLAIN_EXT u16 GetEvenMeterHandileNum(void);
COMMEXPLAIN_EXT u16 GetECBlockPhaseTableNum(void);
COMMEXPLAIN_EXT u16 GetECTypeBlockTableNum(void);
COMMEXPLAIN_EXT u16 GetFreezedataNum(void);
COMMEXPLAIN_EXT u16 GetEscepecialVariableNum(void);
COMMEXPLAIN_EXT u16 GetEvenLoseVoltageNum(void);
COMMEXPLAIN_EXT u16 GetEvenLoseVoltagePhaseNum(void);
COMMEXPLAIN_EXT u16 GetEvenConverseNum(void);
COMMEXPLAIN_EXT u16 GetEvenVolCurUnblanceNum(void);
COMMEXPLAIN_EXT u16 GetEvenLoseCurrentNum(void);
COMMEXPLAIN_EXT u16 GetCheckOutVoltageNum(void);
COMMEXPLAIN_EXT u16 GetCheckOutVoltageType(void);
COMMEXPLAIN_EXT u16 GetEvenMDOverLoadTim(void);
//COMMEXPLAIN_EXT u16 GetEvenMDOverLoadTim(void);
COMMEXPLAIN_EXT u16 GetEvenDataFormatNum(void);
COMMEXPLAIN_EXT u16 GetParameterTableNum(void);
COMMEXPLAIN_EXT u16 GetAddParameterTableNum(void);


COMMEXPLAIN_EXT u16  GetCTSTGateNum(void);
////获得645规约的ID(注意,字节高低位的顺序,不同单片机有可能不同需要修改)
ulong GetCommReadData645ID(uchar FormatNO);
uchar GetCommDataLen(void);
uchar GetCommReadLoadDataNum(void);
void GetCommReadLoadDataTim(uchar * TimAddr);

/////////////获得操作者代码/////////////////////////
void GetUseNumber(uchar *Dest,uchar Lenth);
///比较密码权限
///返回0是有权限操作,否则是无权限操作
uchar CommCmpPassword(uchar PasswordLevel);
void ClearAllPasswordErrCount(void);

/////获得公共假日数目
u16 GetSetHolidayNum(void);
////获得循显个数
u16 GetSetCycleLcdNum(void);
////获得键显个数
u16 GetkeyCycleNum(void);
////获得编程键的状态
///1为编程状态,0为非编程状态
uchar GetTheProgramKeyState(void);

COMMEXPLAIN_EXT void  CommClearLtVirtual485(void);

COMMEXPLAIN_EXT uchar DefaultParaInit(void);
COMMEXPLAIN_EXT  uchar CommStrCmp(uchar *Dest,uchar *Src,u16 uiLthen);

////获得时段表个数
COMMEXPLAIN_EXT u16  GetFeeDayTableMaxNum(void);
////获得年时区数
COMMEXPLAIN_EXT u16  GetFeeSeasonMaxNum(void);
///获得设置的费率数
COMMEXPLAIN_EXT uchar GetSetFeeNumber(void);

COMMEXPLAIN_EXT uchar GetSetLadderNumber(void);

////获得时段个数
COMMEXPLAIN_EXT u16  GetFeeTouTableMaxNum(void);

/////获得通信端口号。
COMMEXPLAIN_EXT uchar GetExplainCommNo(void);
/////获得规约类型。
COMMEXPLAIN_EXT uchar GetCommType(void);

////获得通信控制类型的指针
COMMEXPLAIN_EXT u16 GetCommTypePtr(uchar ControlData);
/////获得读数据中大类数据项的指针
COMMEXPLAIN_EXT u16 GetCommReadTypePtr(uchar ControlData);

COMMEXPLAIN_EXT uchar GetCommBautType(UARTMODE * Mode,uchar WordType,uchar CommNormberType);

/////初始化后续帧缓存中对应通信端口号中的数据
COMMEXPLAIN_EXT void InitialLastFrameBuffer(uchar CommNo);

///后续地址的安排
COMMEXPLAIN_EXT uchar SaveLastFrameInBuffer(STR_LASTFRAME_IN_PARA InPara,uchar *Dest);
///设置返回帧
COMMEXPLAIN_EXT void SetReturnDataFrame(uchar DataLenth,uchar ControlData);

COMMEXPLAIN_EXT void CommControlReadData(void);
COMMEXPLAIN_EXT void CommControlReadLastData(void);
COMMEXPLAIN_EXT void CommReadECData(STR_READ_RETURN_PARA *Dest,ulong ID);
COMMEXPLAIN_EXT void CommReadMDData(STR_READ_RETURN_PARA *Dest,ulong ID);
COMMEXPLAIN_EXT void CommVariableData(STR_READ_RETURN_PARA *Dest,ulong ID);
COMMEXPLAIN_EXT void CommEvenRecordData(STR_READ_RETURN_PARA *Dest,ulong ID);
COMMEXPLAIN_EXT void CommReadParaData(STR_READ_RETURN_PARA *Dest,ulong ID);
COMMEXPLAIN_EXT void CommReadFeezeData(STR_READ_RETURN_PARA *Dest,ulong ID);
COMMEXPLAIN_EXT void CommReadFeezeZeroData(STR_READ_RETURN_PARA *Dest,ulong ID);



COMMEXPLAIN_EXT void CommReadAddr(void);
COMMEXPLAIN_EXT void CommWriteAddr(void);
COMMEXPLAIN_EXT void CommBroadCastTime(void);
COMMEXPLAIN_EXT void CommControlFeezeData(void);
COMMEXPLAIN_EXT void CommClearEven(void);
COMMEXPLAIN_EXT void CommRelaySet(void);
COMMEXPLAIN_EXT void CommClearEC(void);
COMMEXPLAIN_EXT void CommDisplayNO(void);
COMMEXPLAIN_EXT void CommChangeBaudRate(void);
COMMEXPLAIN_EXT void CommChangePassword(void);
COMMEXPLAIN_EXT void CommClearMD(void);
COMMEXPLAIN_EXT void CommMultiPort(void);
COMMEXPLAIN_EXT void CommControlZB(void);

COMMEXPLAIN_EXT void Rcomm645Control(void);


COMMEXPLAIN_EXT void AddData33(uchar * Ptr,uchar Lenth);
COMMEXPLAIN_EXT void SubData33(uchar * Ptr,uchar Lenth);

////返回读数据的头(FE+68+地址+68+控制码+长度)
COMMEXPLAIN_EXT void GetReadReturnDataHead(uchar *Dest,uchar ControlData,uchar DataLenth);
////比较清零权限密码
COMMEXPLAIN_EXT uchar ClearCmpPassword(uchar PasswordLevel,uchar *Dest);
#endif



























