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
    //DP14,��,��,��,4bit(��λ)(0:����ʾ��1��KW;2:KWH;3:KVAR;4:KVARH;5:V;6:A;7:KVA;8:KVAH;9:��Ԫ)
    uchar data2;
    //�ܣ���,��,ƽ,��,�裬�磬��
    uchar data3;
    //��ţ�ʣ�࣬���ʣ���ǰ��A,B,C,N
    uchar data4;
    //�����������򣩣���ѹ������ʧ��ʧѹ������(����)����
    uchar data5;
    //��ϣ����ݣ���Ƿ���ۣ�ʱ���䣬�Σ����
    uchar data6;
    //�����������ۼƣ�cosQ��������,I,I,I,V,
    uchar data7;
    //�û��ţ��࣬��ʼ������������ݣ��ԣ�����
    uchar data8;
    //�ϣ����ڣ�ʱ�䣬�У���
    uchar data9;
}ST_PRIVATE_SYMBOL;


#define ID_STOP_FLAG        0x3f

#define DATA_TYPE_BCD_AMBIT 180
#define DATA_TYPE_DL        0   //������������
#define DATA_TYPE_DL_signed 1
#define DATA_TYPE_XL        2   //������������
#define DATA_TYPE_XL_signed 3
#define DATA_TYPE_SQSD      4   //ʱ��ʱ����������
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
    ulong id;                   //ͨ����ʾID
    uchar idSerialNumber;       //ͨ����ʾID����ʾ��� ��2Ϊ��ʾ����֡�ţ���6λ��ʾ֡�ںţ�֡�ں�ȫΪ1ʱ�򣬱�ʾ��ID����
    uchar startAddress;         //���ݵ�ַ
    uchar dataLens;             //���ݳ���
    u16 privateSymbolListItem; //��ʾ����
    uchar dataType;             //��������          
}ST_DISPLIST_LIST;


//���ͨ�ź���ʾ����һ��һ����� ��Ȼ������
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
    ulong id;                   //ͨ����ʾID
    //uchar idSerialNumber;     //ͨ����ʾID����ʾ���
    UN_ULONG_UCHAR obis;        //��ʾ�ڲ�ID
    uchar* memoryAddress;       //���ݵ�ַ
    u16 dataLens;              //���ݳ���
    PEFUNCTION callBack;        //add call back for write id
    u16 privateSymbolListItem; //��ʾ����
    uchar addressType:2;        //��ַ����  
    uchar access:6;             //Ȩ��
    uchar dataType;             //��������  
    uchar enabled;              //����
}STR_COMM_DISP_LIST;

/*
typedef  struct
{  
    ulong id;                   //ͨ����ʾID
    //uchar idSerialNumber;     //ͨ����ʾID����ʾ���
    uchar* memoryAddress;       //���ݵ�ַ
    u16 dataLens;              //���ݳ���
    PEFUNCTION callBack;        //add call back for write id
    uchar addressType:3;        //��������  
    uchar enabled:5;            //����
    uchar access;               //Ȩ��
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

