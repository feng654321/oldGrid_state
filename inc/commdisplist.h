#ifndef COMMDISPLIST_H
    #define COMMDISPLIST_H

#ifdef  COMMDISPLIST_GLOBALS
    #define COMMDISPLIST_EXT
#else
    #define COMMDISPLIST_EXT extern
#endif  


typedef  struct
{
    //DP2,DP3,DP4,DP6,DP7,DP8,DP10,DP12
    uchar data1;
    //DP14,有,无,功,4bit(单位)(0:不显示；1：KW;2:KWH;3:KVAR;4:KVARH;5:V;6:A;7:KVA;8:KVAH;9:万元)
    uchar data2;
    //总，尖,峰,平,谷,需，电，量
    uchar data3;
    //表号，剩余，功率，当前，A,B,C,N
    uchar data4;
    //正，反（反向），向，压，流，失（失压），上(上月)，月
    uchar data5;
    //组合，阶梯，赊欠，价，时，间，段，金额
    uchar data6;
    //常数，购买，累计，cosQ（因数）,I,I,I,V,
    uchar data7;
    //用户号，相，开始，结束，最大，容，性，次数
    uchar data8;
    //断，日期，时间，感，上
    uchar data9;
}ST_PRIVATE_SYMBOL;


#define ID_STOP_FLAG        0x3f

#define DATA_TYPE_BCD_AMBIT 180
#define DATA_TYPE_DL        0   //电量特有类型
#define DATA_TYPE_DL_signed 1
#define DATA_TYPE_XL        2   //需量特有类型
#define DATA_TYPE_XL_signed 3
#define DATA_TYPE_SQSD      4   //时区时段特有类型
#define DATA_TYPE_VOLTAGE   5
#define DATA_TYPE_CURRENT   6
#define DATA_TYPE_POWER_COSE 7
#define DATA_TYPE_PHASIE    8
#define DATA_TYPE_BCD1_8    20
#define DATA_TYPE_BCD2_8    21
#define DATA_TYPE_BCD3_8    22
#define DATA_TYPE_BCD3_8_signed 23
#define DATA_TYPE_BCD4_8    24
#define DATA_TYPE_BCD5_8    25
#define DATA_TYPE_BCD5_8_signed 26
#define DATA_TYPE_BCD7_8    27
#define DATA_TYPE_BCD1_8_signed 28
#define DATA_TYPE_BCD_XINGQI    29
#define DATA_TYPE_WENDU     30

#define DATA_TYPE_ASC1_8    181
#define DATA_TYPE_ASC2      182
#define DATA_TYPE_ASC3      183
#define DATA_TYPE_ASC4      184
#define DATA_TYPE_ASC7_8    187
#define DATA_TYPE_ASC3_8    188
#define DATA_TYPE_ASC5_8    189
#define DATA_TYPE_ERROR 190
#define DATA_TYPE_BAUDRATE  170
#define DATA_TYPE_HEX_AMBIT 220

typedef  union
{  
    ulong l;
    uchar b[4];
}UN_ULONG_UCHAR;

typedef  struct
{  
    ulong id;                   //通信显示ID
    uchar idSerialNumber;       //通信显示ID里显示序号 高2为表示后续帧号，低6位表示帧内号，帧内号全为1时候，表示该ID结束
    uchar startAddress;         //数据地址
    uchar dataLens;             //数据长度
    u16 privateSymbolListItem; //显示符号
    uchar dataType;             //数据类型          
}ST_DISPLIST_LIST;


//针对通信和显示内容一对一的情况 不然不可用
#define DIRECT_ADDRESSING   0
#define INDIRECT_ADDRESSING 1
#define SPECIAL_ADDRESSING  2
#define POPEDOM0            0
#define POPEDOM1            1
#define POPEDOM2            2
#define POPEDOM3            3
#define POPEDOM4            4
#define POPEDOM5            5
typedef  struct
{  
    ulong id;                   //通信显示ID
    //uchar idSerialNumber;     //通信显示ID里显示序号
    UN_ULONG_UCHAR obis;        //显示内部ID
    uchar* memoryAddress;       //数据地址
    u16 dataLens;              //数据长度
    PEFUNCTION callBack;        //add call back for write id
    u16 privateSymbolListItem; //显示符号
    uchar addressType:2;        //地址类型  
    uchar access:6;             //权限
    uchar dataType;             //数据类型  
    uchar enabled;              //开关
}STR_COMM_DISP_LIST;

/*
typedef  struct
{  
    ulong id;                   //通信显示ID
    //uchar idSerialNumber;     //通信显示ID里显示序号
    uchar* memoryAddress;       //数据地址
    u16 dataLens;              //数据长度
    PEFUNCTION callBack;        //add call back for write id
    uchar addressType:3;        //数据类型  
    uchar enabled:5;            //开关
    uchar access;               //权限
}ST_COMM_LIST;
*/




/*
COMMDISPLIST_EXT const near STR_COMM_DISP_LIST commDispList[];
COMMDISPLIST_EXT const near STR_COMM_DISP_LIST commList[];
COMMDISPLIST_EXT const near ST_PRIVATE_SYMBOL privateSymbolList[];
COMMDISPLIST_EXT const near ST_DISPLIST_LIST dispList[];
*/

COMMDISPLIST_EXT const STR_COMM_DISP_LIST commDispList[];
COMMDISPLIST_EXT const STR_COMM_DISP_LIST commList[];
COMMDISPLIST_EXT const ST_PRIVATE_SYMBOL privateSymbolList[];
COMMDISPLIST_EXT const ST_DISPLIST_LIST dispList[];


COMMDISPLIST_EXT u16 GetDispListLens(void);
COMMDISPLIST_EXT u16 GetCommListLens(void);
COMMDISPLIST_EXT u16 GetCommDispListLens(void);
COMMDISPLIST_EXT u16 GetPrivateSymbolListLens(void);
#define CON_DISPLIST_ERR_NUM 17
//COMMDISPLIST_EXT uchar ReadDataDirect(ulong ulDataName,  u16 nLen, uchar* pDest);
//COMMDISPLIST_EXT uchar WriteDataDirect(uchar* pSrc, ulong DataName,  int nLen);


#endif

