#ifndef  COMMEXPWRITE_H
                #define COMMEXPWRITE_H
                #define COMMEXPWRITE_EXT                extern

////////////////////////////////////////////////////////////////////////////////////////
//typedef  uchar (*EvenFUNCTION)(void);

///////参变量数据
typedef  struct
{  
    ulong id;                   //通信显示ID
    ulong memoryAddress;        //数据地址
    uchar dataLens;             //数据长度
    WithReturnFUNCTION callBack;        //add call back for write id,(编程完毕后的一系列刷新参数的操作)
    CheckFunction CheckFunction;    ////校验参数有效性的函数
    uchar access;                               //权限
    uchar WithPKey:1;               ///是否配合编程键
    uchar WithSpecKey:2;        ///是否需要配合特殊功能(比如安全认证)
    uchar addressType:2;                //地址类型  
    uchar dataType:2;                       //数据类型  
    uchar enabled:1;                    //开关
    uchar ReadAndWrite;       ///读写权限控制
    uchar ProgramType;        ///编程记录类型
}ST_COMM_DISP_LIST;

typedef  struct
{  
    ulong id;                   //通信显示ID
    ulong memoryAddress;        //数据地址
    u16 dataLens;              //数据长度
    uchar byte_order;               //字节是否逆序
}ST_COMM_ADD_PARA;
///////需要事件记录的参变量
/*
typedef  struct
{
    ulong ID;      ////通信ID
    uchar 
//  EvenFUNCTION  EvenRecordFun;     ////事件记录调用函数
     
}ST_COMM_PROGRAM_LIST;           
*/

COMMEXPWRITE_EXT COMM_CONST  ST_COMM_DISP_LIST  TableParaMeter[];
COMMEXPWRITE_EXT COMM_CONST  ST_COMM_ADD_PARA AddPara[];
                /////////////////////////参变量数据的有效性检查////////////////////////////
COMMEXPWRITE_EXT uchar CommDayFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
///时间格式检查
COMMEXPWRITE_EXT uchar CommTimeFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////最大需量周期检查
COMMEXPWRITE_EXT uchar CommMDFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////滑差时间有效性检查
COMMEXPWRITE_EXT uchar CommTackleFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////日时段表/时区表切换时间,
COMMEXPWRITE_EXT uchar CommFeeTableSwitchFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);

COMMEXPWRITE_EXT uchar CommmmhhDDMMYYFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);

////年时区数/有效性判断
COMMEXPWRITE_EXT uchar CommSeasonNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////日时段表数有效性判断
COMMEXPWRITE_EXT uchar CommDayTableNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////日时段数有效性判断
COMMEXPWRITE_EXT uchar CommFeeTableNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
///费率数有效性判断
COMMEXPWRITE_EXT uchar CommFeeNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
///公共假日数
COMMEXPWRITE_EXT uchar CommHolidayNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////周休日编程有效性判断
COMMEXPWRITE_EXT uchar CommWeekTableNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);

//谐波分析
COMMEXPWRITE_EXT uchar CommHarmoniousFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////显示屏数(键显,按显)
//COMMEXPWRITE_EXT uchar CommDspNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
///显示时间
COMMEXPWRITE_EXT uchar CommDspTimeFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
///显示需量小数
COMMEXPWRITE_EXT uchar CommDspMDFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
///显示电量小数
COMMEXPWRITE_EXT uchar CommDspECFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
///负荷记录时间
COMMEXPWRITE_EXT uchar CommLoadRecordFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////结算日有效性判断
COMMEXPWRITE_EXT uchar CommBillDayFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////时区表有效性判断
COMMEXPWRITE_EXT uchar CommSeasonTableFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////时段表有效性判断
COMMEXPWRITE_EXT uchar CommFeeDayTableFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////公共假日有效性判断
COMMEXPWRITE_EXT uchar CommCheckHolidayFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////校验空函数
COMMEXPWRITE_EXT uchar NULLCheckFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////校验厂内状态函数
COMMEXPWRITE_EXT uchar FactoryCheckFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
///波特率校验函数
COMMEXPWRITE_EXT uchar CommBautWordFm(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
///BCD校验
COMMEXPWRITE_EXT uchar CommWriteBcdFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
#if(CONFIG_METER_PREPAY_MODE==CONFIG_METER_PREPAY_MODE_FAR)
COMMEXPWRITE_EXT uchar CommWriteFormatKey(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
#endif
COMMEXPWRITE_EXT uchar CommDemandNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);

COMMEXPWRITE_EXT uchar CommWeekDayUseTouFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
COMMEXPWRITE_EXT uchar CommCheckhhmm(uchar *Dest,uchar ucLenth,uchar *ReturnFlag);
////返回值
COMMEXPWRITE_EXT uchar NULLReturnValue(void);

COMMEXPWRITE_EXT void CommControlWriteData(void);
COMMEXPWRITE_EXT uchar GetCommTypeName(uchar ucID0);

#endif
