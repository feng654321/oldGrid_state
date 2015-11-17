//============================================================================
//  File Name: Dlt645_07.C
//
//  Copyright PAX Hangzhou 2011.  All rights reserved.
//
//  Description:
//      DLT-645 07规约解析
//      规约解析要求不依赖于具体系统的设计，比如字长、大小ENDIAN
//  Author:
//      陶治国
//
//  Modification History:
//      $Id:  Exp $
//      $Log: $
//      Revision 1.0 Create by Taozhiguo in 2011.04.28
//============================================================================
#ifndef __DLT645_07_C__
#define __DLT645_07_C__

#include "common.h"
#define  DLTTRACE(fmt, args...)    //ErrPrint(fmt, args...)

//周休日位信息
const u8 ConWeekDayWordTable[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x00};

/*********************************************************************
函数：isIDNew
功能：根据ID判断是否属于本文件解析的范围
参数：
        u32 ID:           DLT645 ID( (((ID3*256+ID2)*256)+ID1)*256+ID0 )
        目前只支持电量、需量、变量的解析
Input:
Output:
返回：  0:非本文件解析       
        1:本文件解析
范围：
注释：无。
********************************************************************/
u8 isIDNew(u32 ID)
{
    if(DLT_ID3(ID) > 2)
    {
        return 0;
    }
    return 1;
}

////所有读出数据的大类数据表
/*COMM_CONST     func  TableCommReadBlock[][2]=
{
    GetSymbol_EC,          CommReadECData,
    GetSymbol_MD,          CommReadMDData,
    GetSymbol_VARIANLE,    CommVariableData,	
    GetSymbol_EVEN,        CommEvenRecordData,
    GetSymbol_PARA,        CommReadParaData,
    GetSymbol_FREEZE,      CommReadFeezeData,
    GetSymbol_LOAD,        CommReadLoadData,
    NULL,                  NULL,
    GetSymbol_ZEROFEEZE,   CommReadFeezeZeroData
    NULL,                  NULL,
                
};*/
    
/******************************************************************************************
            DLT645-07 电量数据开始
******************************************************************************************/
//电量类型  
//enum
//{
#define    EC_TYPE_YG   0//,     //有功
#define    EC_TYPE_WG   1//,     //无功
#define    EC_TYPE_SZ   2//,     //视在
#define    EC_TYPE_GL   3//,     //关联
#define    EC_TYPE_JB   4//,     //基波有功
#define    EC_TYPE_XB   5//,     //谐波有功
#define    EC_TYPE_YD   6//,     //用电
#define    EC_TYPE_SY   7//,     //剩余
#define    EC_TYPE_CN   8//,     //铜损有功
#define    EC_TYPE_TE   9//,     //铁损有功
//};
//分合相
enum
{
    EC_PH_ALL,      //合相
    EC_PH_PHA,      //A相
    EC_PH_PHB,      //B相
    EC_PH_PHC,      //C相
};
//有功、视在等组合类型，不一定全有
enum
{
    EC_YG_ZH_ZH,    //组合
    EC_YG_ZH_ZX,    //正向
    EC_YG_ZH_FX,    //反向
};
//无功组合类型
enum
{
    EC_WG_ZH_Z1,    //组合1
    EC_WG_ZH_Z2,    //组合1
    EC_WG_ZH_GX,    //感性
    EC_WG_ZH_RX,    //容性
    EC_WG_ZH_X1,    //1象限
    EC_WG_ZH_X2,    //2象限
    EC_WG_ZH_X3,    //3象限
    EC_WG_ZH_X4,    //4象限
};
#define PT_OTHER        (-2)
#define PT_UNSUPPORT    (-1)    //注意:这里假设所有的地址都不会是0xff
#define PT_LEFT_ALL     0x53
//根据参数算出电量组合类型
// type:电量类型 ph:分合相 zh:组合方式  //注意ph，zh不能超过3位
#define ECZT(type,ph,zh)    ( ((type)<<5) | ((ph)<<3) | (zh) )
//根据电量组合类型算出电量类型
#define ECZT_TYPE(v)        (((v)&0xE0)>>5)
//根据电量组合类型算出分合相类型
#define ECZT_PH(v)          (((v)&0x18)>>3)
//根据电量组合类型算出组合类型
#define ECZT_ZH(v)          ((v)&0x07)

typedef u8 ECTYPE_CHAR;  //电量组合类型
typedef struct
{
    ECTYPE_CHAR ectype;  //抽象的类型，将电量按不同种类抽象分类，有助于理解和显示
    u8 id2;              //ID2 的值
    u8 ecindex;          //类型索引(电量是直接定义的索引值，需量是根据RAM地址换算出来的索引)
}EC_ID2_DEF;
#define isTheECIdxUnSupport(idx)        (EC_Id2[idx].ecindex == (u8)PT_UNSUPPORT)
#define isTheMDIdxUnSupport(idx)        (MD_Id2[idx].ecindex == (u8)PT_UNSUPPORT)
#define isTheVRIdxUnSupport(idx)        (VR_Id2[idx].Addr== (u16)PT_UNSUPPORT)
#define isTheVROTHIdxUnSupport(idx)     (VR_OTH_Id0[idx].Addr== (u16)PT_UNSUPPORT)
//#pragma diag_remark=Pa089
//所有电量相关规约信息列表
#define EC_ZT(type,ph,zh,id,pti)        (ECZT(type,ph,zh)), (id), (pti)
const EC_ID2_DEF EC_Id2[]=
{
//从左到右依次是:
    //电量简单类型
    //分合相
    //组合类型
    //ID2
    //电量索引
   {EC_ZT(EC_TYPE_YG, EC_PH_ALL, EC_YG_ZH_ZH, 0x00, PT_KWH_C_ALL)},     /*00: 组合有功*/
   {EC_ZT(EC_TYPE_YG, EC_PH_ALL, EC_YG_ZH_ZX, 0x01, PT_KWH_F_ALL)},     /*01: 正向有功*/
   {EC_ZT(EC_TYPE_YG, EC_PH_ALL, EC_YG_ZH_FX, 0x02, PT_KWH_R_ALL)},     /*02: 反向有功*/
   {EC_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_Z1, 0x03, PT_KVARH_C1_ALL)},  /*03: 组合无功1*/
   {EC_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_Z2, 0x04, PT_KVARH_C2_ALL)},  /*04: 组合无功2*/
   {EC_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_X1, 0x05, PT_KVARH_Q1_ALL)},  /*05: 1象限无功*/
   {EC_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_X2, 0x06, PT_KVARH_Q2_ALL)},  /*06: 2象限无功*/
   {EC_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_X3, 0x07, PT_KVARH_Q3_ALL)},  /*07: 3象限无功*/
   {EC_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_X4, 0x08, PT_KVARH_Q4_ALL)},  /*08: 4象限无功*/
#if 1     
    {EC_ZT(EC_TYPE_SZ, EC_PH_ALL, EC_YG_ZH_ZX, 0x09, PT_KVAH_F_ALL)},     /*09: 正向视在*/
    {EC_ZT(EC_TYPE_SZ, EC_PH_ALL, EC_YG_ZH_FX, 0x0A, PT_KVAH_R_ALL)},     /*0A: 反向视在*/
#endif    
    {EC_ZT(EC_TYPE_YD, EC_PH_ALL, EC_YG_ZH_ZH, 0x0B, PT_KWH_USE_ALL)},   /*0B: 用电量*/
    
    {EC_ZT(EC_TYPE_YG, EC_PH_PHA, EC_YG_ZH_ZX, 0x15, PT_KWH_A_F_ALL)},   /*15: A正向有功*/
    {EC_ZT(EC_TYPE_YG, EC_PH_PHA, EC_YG_ZH_FX, 0x16, PT_KWH_A_R_ALL)},   /*16: A反向有功*/
#if 1     
    {EC_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_Z1, 0x17, PT_KVARH_A_C1_ALL)},     /*17: A组合无功1*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_Z2, 0x18, PT_KVARH_A_C2_ALL)},     /*18: A组合无功2*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_X1, 0x19, PT_KVARH_A_Q1_ALL)},     /*19: A1象限无功*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_X2, 0x1A, PT_KVARH_A_Q2_ALL)},     /*1A: A2象限无功*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_X3, 0x1B, PT_KVARH_A_Q3_ALL)},     /*1B: A3象限无功*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_X4, 0x1C, PT_KVARH_A_Q4_ALL)},     /*1C: A4象限无功*/
    {EC_ZT(EC_TYPE_SZ, EC_PH_PHA, EC_YG_ZH_ZX, 0x1D, PT_KVAH_A_F_ALL)},     /*1D: A正向视在*/
    {EC_ZT(EC_TYPE_SZ, EC_PH_PHA, EC_YG_ZH_FX, 0x1E, PT_KVAH_A_R_ALL)},     /*1E: A反向视在*/
#endif    
    {EC_ZT(EC_TYPE_YG, EC_PH_PHB, EC_YG_ZH_ZX, 0x29, PT_KWH_B_F_ALL)},   /*29: B正向有功*/
    {EC_ZT(EC_TYPE_YG, EC_PH_PHB, EC_YG_ZH_FX, 0x2A, PT_KWH_B_R_ALL)},   /*2A: B反向有功*/
#if 1    
    {EC_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_Z1, 0x2B, PT_KVARH_B_C1_ALL)},     /*2B: B组合无功1*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_Z2, 0x2C, PT_KVARH_B_C2_ALL)},     /*2C: B组合无功2*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_X1, 0x2D, PT_KVARH_B_Q1_ALL)},     /*2D: B1象限无功*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_X2, 0x2E, PT_KVARH_B_Q2_ALL)},     /*2E: B2象限无功*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_X3, 0x2F, PT_KVARH_B_Q3_ALL)},     /*2F: B3象限无功*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_X4, 0x30, PT_KVARH_B_Q4_ALL)},     /*30: B4象限无功*/
    {EC_ZT(EC_TYPE_SZ, EC_PH_PHB, EC_YG_ZH_ZX, 0x31, PT_KVAH_B_F_ALL)},       /*31: B正向视在*/
    {EC_ZT(EC_TYPE_SZ, EC_PH_PHB, EC_YG_ZH_FX, 0x32, PT_KVAH_B_R_ALL)},       /*32: B反向视在*/
#endif    
    {EC_ZT(EC_TYPE_YG, EC_PH_PHC, EC_YG_ZH_ZX, 0x3D, PT_KWH_C_F_ALL)},   /*3D: C正向有功*/
    {EC_ZT(EC_TYPE_YG, EC_PH_PHC, EC_YG_ZH_FX, 0x3E, PT_KWH_C_R_ALL)},   /*3E: C反向有功*/
#if 1    
    {EC_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_Z1, 0x3F, PT_KVARH_C_C1_ALL)},     /*3F: C组合无功1*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_Z2, 0x40, PT_KVARH_C_C2_ALL)},     /*40: C组合无功2*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_X1, 0x41, PT_KVARH_C_Q1_ALL)},     /*41: C1象限无功*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_X2, 0x42, PT_KVARH_C_Q2_ALL)},     /*42: C2象限无功*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_X3, 0x43, PT_KVARH_C_Q3_ALL)},     /*43: C3象限无功*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_X4, 0x44, PT_KVARH_C_Q4_ALL)},     /*44: C4象限无功*/
    {EC_ZT(EC_TYPE_SZ, EC_PH_PHC, EC_YG_ZH_ZX, 0x45, PT_KVAH_C_F_ALL)},       /*45: C正向视在*/
    {EC_ZT(EC_TYPE_SZ, EC_PH_PHC, EC_YG_ZH_FX, 0x46, PT_KVAH_C_R_ALL)},       /*46: C反向视在*/
#endif    
#if 0    
    {EC_ZT(EC_TYPE_GL, EC_PH_ALL, EC_YG_ZH_ZH, 0x80, PT_UNSUPPORT)},     /*80: 总关联电能*/
    {EC_ZT(EC_TYPE_JB, EC_PH_ALL, EC_YG_ZH_ZX, 0x81, PT_UNSUPPORT)},     /*81: 总基波正向有功*/
    {EC_ZT(EC_TYPE_JB, EC_PH_ALL, EC_YG_ZH_FX, 0x82, PT_UNSUPPORT)},     /*82: 总基波反向有功*/
    {EC_ZT(EC_TYPE_XB, EC_PH_ALL, EC_YG_ZH_ZX, 0x83, PT_UNSUPPORT)},     /*83: 总谐波正向有功*/
    {EC_ZT(EC_TYPE_XB, EC_PH_ALL, EC_YG_ZH_FX, 0x84, PT_UNSUPPORT)},     /*84: 总谐波反向有功*/
    {EC_ZT(EC_TYPE_CN, EC_PH_ALL, EC_YG_ZH_ZH, 0x85, PT_UNSUPPORT)},     /*85: 总铜损有功*/
    {EC_ZT(EC_TYPE_TE, EC_PH_ALL, EC_YG_ZH_ZH, 0x86, PT_UNSUPPORT)},     /*86: 总铁损有功*/
#endif    
    {EC_ZT(EC_TYPE_SY, EC_PH_ALL, EC_YG_ZH_ZH, 0x90, PT_LEFT_ALL)},      /*90: 剩余*/
#if 0    
    {EC_ZT(EC_TYPE_GL, EC_PH_PHA, EC_YG_ZH_ZH, 0x94, PT_UNSUPPORT)},     /*94: A关联电能*/
    {EC_ZT(EC_TYPE_JB, EC_PH_PHA, EC_YG_ZH_ZX, 0x95, PT_UNSUPPORT)},     /*95: A基波正向有功*/
    {EC_ZT(EC_TYPE_JB, EC_PH_PHA, EC_YG_ZH_FX, 0x96, PT_UNSUPPORT)},     /*96: A基波反向有功*/
    {EC_ZT(EC_TYPE_XB, EC_PH_PHA, EC_YG_ZH_ZX, 0x97, PT_UNSUPPORT)},     /*97: A谐波正向有功*/
    {EC_ZT(EC_TYPE_XB, EC_PH_PHA, EC_YG_ZH_FX, 0x98, PT_UNSUPPORT)},     /*98: A谐波反向有功*/
    {EC_ZT(EC_TYPE_CN, EC_PH_PHA, EC_YG_ZH_ZH, 0x99, PT_UNSUPPORT)},     /*99: A铜损有功*/
    {EC_ZT(EC_TYPE_TE, EC_PH_PHA, EC_YG_ZH_ZH, 0x9A, PT_UNSUPPORT)},     /*9A: A铁损有功*/
    {EC_ZT(EC_TYPE_GL, EC_PH_PHB, EC_YG_ZH_ZH, 0xA8, PT_UNSUPPORT)},     /*A8: B关联电能*/
    {EC_ZT(EC_TYPE_JB, EC_PH_PHB, EC_YG_ZH_ZX, 0xA9, PT_UNSUPPORT)},     /*A9: B基波正向有功*/
    {EC_ZT(EC_TYPE_JB, EC_PH_PHB, EC_YG_ZH_FX, 0xAA, PT_UNSUPPORT)},     /*AA: B基波反向有功*/
    {EC_ZT(EC_TYPE_XB, EC_PH_PHB, EC_YG_ZH_ZX, 0xAB, PT_UNSUPPORT)},     /*AB: B谐波正向有功*/
    {EC_ZT(EC_TYPE_XB, EC_PH_PHB, EC_YG_ZH_FX, 0xAC, PT_UNSUPPORT)},     /*AC: B谐波反向有功*/
    {EC_ZT(EC_TYPE_CN, EC_PH_PHB, EC_YG_ZH_ZH, 0xAD, PT_UNSUPPORT)},     /*AD: B铜损有功*/
    {EC_ZT(EC_TYPE_TE, EC_PH_PHB, EC_YG_ZH_ZH, 0xAE, PT_UNSUPPORT)},     /*AE: B铁损有功*/
    {EC_ZT(EC_TYPE_GL, EC_PH_PHC, EC_YG_ZH_ZH, 0xBC, PT_UNSUPPORT)},     /*BC: C关联电能*/
    {EC_ZT(EC_TYPE_JB, EC_PH_PHC, EC_YG_ZH_ZX, 0xBD, PT_UNSUPPORT)},     /*BD: C基波正向有功*/
    {EC_ZT(EC_TYPE_JB, EC_PH_PHC, EC_YG_ZH_FX, 0xBE, PT_UNSUPPORT)},     /*BE: C基波反向有功*/
    {EC_ZT(EC_TYPE_XB, EC_PH_PHC, EC_YG_ZH_ZX, 0xBF, PT_UNSUPPORT)},     /*BF: C谐波正向有功*/
    {EC_ZT(EC_TYPE_XB, EC_PH_PHC, EC_YG_ZH_FX, 0xC0, PT_UNSUPPORT)},     /*C0: C谐波反向有功*/
    {EC_ZT(EC_TYPE_CN, EC_PH_PHC, EC_YG_ZH_ZH, 0xC1, PT_UNSUPPORT)},     /*C1: C铜损有功*/
    {EC_ZT(EC_TYPE_TE, EC_PH_PHC, EC_YG_ZH_ZH, 0xC2, PT_UNSUPPORT)},     /*C2: C铁损有功*/
#endif    
};
//#pragma diag_default=Pa089
#define EC_Id2_TABLE_LEN    (sizeof(EC_Id2)/sizeof(EC_ID2_DEF))

/*********************************************************************
函数：ECId2IdxFind
功能：根据DLT645 ID找出在信息数组中索引、并判断其正确性澹(包括是否支持)
参数：
        u32 ID:           DLT645 ID( (((ID3*256+ID2)*256)+ID1)*256+ID0 )
Input:
Output:
返回：  DLT_RET_ERR:    ID错误或不支持    
        其他:           正确的索引
范围：
注释：无。
********************************************************************/
u8 ECId2IdxFind(u32 ID);
u8 ECId2IdxFind(u32 ID)
{
    u8 ID3=DLT_ID3(ID);
    u8 ID2=DLT_ID2(ID);
    u8 ID0=DLT_ID0(ID);
    u8 ID1=DLT_ID1(ID);
    u16  idx=0;
    u8  TFeeNum=GetSetFeeNumber();

    if(ID3 != 0x00) return DLT_RET_ERR;
    if(ID2 == 0xFF) return DLT_RET_ERR;
    if((ID1 == 0xFF) && (ID0 == 0xFF)) return DLT_RET_ERR;
    if((ID0 > COMM_READ_EC_HISTORY) && (ID0 != 0xFF)) return DLT_RET_ERR;
#if(CONFIG_METER_PREPAY_MODE == CONFIG_METER_PREPAY_MODE_DISABLE)
    if(ID2==0x90)    ///卡表数据
        return DLT_RET_ERR;
#endif
    for(idx=0; idx<EC_Id2_TABLE_LEN; idx++)
    {
        if(EC_Id2[idx].id2 == ID2)
            break;
    }
    if(idx >= EC_Id2_TABLE_LEN)
        return DLT_RET_ERR;
    if(isTheECIdxUnSupport(idx)) return DLT_RET_ERR;
    if(ECZT_TYPE(EC_Id2[idx].ectype) == EC_TYPE_SY)
    {
        //剩余电量的ID1只能是1和2
        if( (ID1 < 1) || (ID1 > 2) )
            return DLT_RET_ERR;
    }
    else
    {
        if((ID1 > TFeeNum) && (ID1 != 0xFF))
            return DLT_RET_ERR;
        //如果该大类没有费率项,而ID1却有该项则错误
        if(ID1 > 0) //无费率情况下，0xFF也不允许
            if(ECZT_PH(EC_Id2[idx].ectype) != EC_PH_ALL) 
                return DLT_RET_ERR;     //分相电量无费率
    }
    
    return idx;
}
/*********************************************************************
函数：SymbolGetECData
功能：根据DLT645 ID算出需要显示的图标
参数：
Input:
Output:
返回：  DLT_RET_SUCC:   读成功        
        DLT_RET_ERR:    失败
范围：
注释：无。
********************************************************************/
u8 SymbolGetECData(STR_DISPLAYSYMBOL *sym, u32 ID, u8 idSerialNumber, u8 *ucDLen, u8 *dataType)
{
    u8 ID0=DLT_ID0(ID);
    u8 ID1=DLT_ID1(ID);
    u8 ID2=DLT_ID2(ID);
    ECTYPE_CHAR ECtype, type;
    u16  idx;

    if(idSerialNumber > 0) return DLT_RET_ERR;
    if((ID2 == 0xFF) || (ID1 == 0xFF) || (ID0 == 0xFF))
        return DLT_RET_ERR;
    
    idx = ECId2IdxFind(ID);
    if(idx == DLT_RET_ERR)
        return DLT_RET_ERR;

    *ucDLen = COMM_READ_EC_LENTH;
    ECtype = EC_Id2[idx].ectype; 
    type = ECZT_TYPE(ECtype);

    switch(type)
    {
        case EC_TYPE_YG:
        case EC_TYPE_WG:
            sym->Gong = 1;
            sym->Dian = 1;
            sym->Liang = 1;
            if(type == EC_TYPE_YG)
            {
                sym->You = 1;
                sym->KW = 1;
                sym->h1 = 1;
            }
            else
            {
                sym->Wu = 1;
                sym->kvar = 1;
                sym->h2 = 1;
            }
            if(ID1 == 0)
            {
                sym->Zong = 1;
            }
            else if(ID1 == 1)
            {
                sym->Jian= 1;
            }
            else if(ID1 == 2)
            {
                sym->Feng= 1;
            }
            else if(ID1 == 3)
            {
                sym->Ping= 1;
            }
            else if(ID1 == 4)
            {
                sym->Gu= 1;
            }
            if(ID0 == 0)
            {
                sym->DangQian = 1;
            }
            else if(ID0 <= 12)
            {
                sym->Shang1 = 1;
                sym->month = 1;
            }
            //else
            //    return DLT_RET_ERR;
            break;
        case EC_TYPE_YD:
            sym->You = 1;
            sym->Gong = 1;
            sym->KW = 1;
            sym->h1 = 1;
            sym->Dian = 1;
            sym->Liang = 1;
            if(ID1 == 0)
            {
                sym->zuhe = 1;
            }
            else
                return DLT_RET_ERR;
            if(ID0 == 0)
            {
                sym->DangQian = 1;
            }
            else if(ID0 == 1)
            {
                sym->Shang1 = 1;
                sym->month = 1;
            }
            else
                return DLT_RET_ERR;
            break;
        case EC_TYPE_SY:
            sym->You = 1;
            sym->Gong = 1;
            sym->Dian = 1;
            sym->Liang = 1;
            if(ID1 == 1)
            {
                sym->KW = 1;
                sym->h1 = 1;
            }
            else if(ID1 == 2)
            {
                sym->yuan = 1;
            }
            else
                return DLT_RET_ERR;
            if(ID0 == 0)
            {
                sym->shengyu = 1;
            }
            else if(ID1 == 1)
            {
                //sym->touzhi = 1;
            }
            else
                return DLT_RET_ERR;
            break;
        
        case EC_TYPE_SZ:
        case EC_TYPE_GL:
        case EC_TYPE_JB:
        case EC_TYPE_XB:
        case EC_TYPE_CN:
        case EC_TYPE_TE:
        default:
            return DLT_RET_ERR;
            //break;
    }
    switch(ECZT_PH(ECtype))
    {
        case EC_PH_ALL:
            //sym->Zong = 1;
            break;
        case EC_PH_PHA:
            sym->phaseA = 1;
            break;
        case EC_PH_PHB:
            sym->phaseB = 1;
            break;
        case EC_PH_PHC:
            sym->phaseC = 1;
            break;
    }
    if(type == EC_TYPE_WG)
    {
        switch(ECZT_ZH(ECtype))
        {
            case EC_WG_ZH_Z1:
                sym->zuhe = 1;
                sym->issigned = 1;
                sym->wugongxiangxian1 = 1;
                break;
            case EC_WG_ZH_Z2:
                sym->zuhe = 1;
                sym->issigned = 1;
                sym->wugongxiangxian1 = 1;
                sym->wugongxiangxian2 = 1;
                break;
            case EC_WG_ZH_GX:
                sym->zuhe = 1;
                sym->issigned = 1;
                sym->wugongxiangxian1 = 1;
                sym->wugongxiangxian2 = 1;
                sym->wugongxiangxian3 = 1;
                break;
            case EC_WG_ZH_RX:
                sym->zuhe = 1;
                sym->issigned = 1;
                sym->wugongxiangxian3 = 1;
                sym->wugongxiangxian4 = 1;
                break;
            case EC_WG_ZH_X1:
                sym->wugongxiangxian1 = 1;
                break;
            case EC_WG_ZH_X2:
                sym->wugongxiangxian1 = 1;
                sym->wugongxiangxian2 = 1;
                break;
            case EC_WG_ZH_X3:
                sym->wugongxiangxian1 = 1;
                sym->wugongxiangxian2 = 1;
                sym->wugongxiangxian3 = 1;
                break;
        case EC_WG_ZH_X4:
                sym->wugongxiangxian3 = 1;
                sym->wugongxiangxian4 = 1;
                break;
        }
    }
    else
    {
        switch(ECZT_ZH(ECtype))
        {
            case EC_YG_ZH_ZH:
                sym->zuhe = 1;
                sym->issigned = 1;
                break;
            case EC_YG_ZH_ZX:
                sym->Zheng = 1;
                sym->fangXiang = 1;
                break;
            case EC_YG_ZH_FX:
                sym->Fan = 1;
                sym->fangXiang = 1;
                break;
        }
    }
    if(sym->issigned == 0)
        *dataType = DATA_TYPE_DL;
    else
        *dataType = DATA_TYPE_DL_signed;
    return DLT_RET_SUCC;
}

/*********************************************************************
函数：GetECDataByID
功能：根据DLT645 ID读取电量数据
参数：
        u8 *pData:       数据buf，用来存放读回的数据
        u16 *ucLen:        读回数据长度
        u32 ID:           DLT645 ID( (((ID3*256+ID2)*256)+ID1)*256+ID0 )
        u16 ulBufLen:      调用是给的buf的长度
Input:
Output:
返回：  0:读成功        
        1:读失败
范围：
注释：无。
********************************************************************/
u8 GetECDataByID(u8 *pData, u16 *ucLen, u32 ID, u16 ulBufLen)
{
    u8 ID0=DLT_ID0(ID);
    u8 ID1=DLT_ID1(ID);
    u8 ID2=DLT_ID2(ID);
    //ECTYPE_CHAR ECtype, type;
    u8 ecindex;
    u16  idx;
    u32 ECAddr;
    
    DLTTRACE("GetECDataByID 0x%08X\n",ID);
    idx = ECId2IdxFind(ID);
    if(idx == DLT_RET_ERR) return DLT_RET_ERR;

    ecindex = EC_Id2[idx].ecindex;
    *ucLen = 0;
    DLTTRACE("idx=%d, ecindex %d\n",idx, ecindex);
     
    if(ID2==0x90)    ///卡表数据
    {
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
#if(CONFIG_METER_STEP_PERIODPRICE_MODE==CONFIG_METER_STEP_PERIODPRICE_MODE_ENABLE)
        if(ulBufLen < 4) return DLT_RET_ERR;
        if(ID==0x00900200)
        {
            if(0!=JudgeRemainSign(0, pData))
            // aa 如果不是剩余电量 aa
            {
                memset(pData, 0x00, 4);
            }
            *ucLen = 4;
        }
        else if(ID==0x00900201)
        {
            
            if(0==JudgeRemainSign(0, pData))
            // aa 如果不是剩余电量 aa
            {
                memset(pData, 0x00, 4);
            }
            *ucLen = 4;
        }
        if(*ucLen == 4) return DLT_RET_ERR;
#else
        return DLT_RET_ERR;
#endif
#endif
    }
    else if(ID2 == 0x0B)   //结算周期组合有功累计用电量
    {
        if(ID == 0x000B0000)
        {
            ReadDataDirect(RAM_KWH_ALL_USE_START, COMM_READ_EC_LENTH, pData);
            *ucLen = COMM_READ_EC_LENTH;
        }
        else if(ID == 0x000B0001)
        {
            ECAddr=GetTwoTableAddrFromBlock(TYPE_HISTROY_USEPOWER_RECORD,(ID0-1),0);
            ReadDataDirect(ECAddr, COMM_READ_EC_LENTH, pData);
            *ucLen = COMM_READ_EC_LENTH;
        }
        else
        {
            return DLT_RET_ERR;
        }
    }
    else
    {
        if(ID0==0xFF)
        {
            if(COMM_READ_EC_LENTH*(COMM_READ_EC_HISTORY+1) > ulBufLen) 
                return DLT_RET_ERR;
            for(ID0=0; ID0<=COMM_READ_EC_HISTORY; ID0++)
            {
                if(ID0==0)///当前
                {
                    ECAddr = RAM_KWH_ALL_START;
                }
                else //历史
                {
                    ECAddr = GetTwoTableAddrFromBlock(TYPE_HISTROY_POWER_RECORD,(ID0-1),0);
                    if(IS_TWOTABLE_ADDR_ERR(ECAddr)) return DLT_RET_ERR;   
                }
                ECAddr += (ecindex+ID1)*COMM_READ_EC_LENTH;
                //if(*ucLen > ulBufLen) return DLT_RET_ERR;
                ReadDataDirect(ECAddr, COMM_READ_EC_LENTH, pData);
                *ucLen += COMM_READ_EC_LENTH;
            }
        }
        else
        {
            if(ID0==0)///当前
            {
                ECAddr = RAM_KWH_ALL_START;
            }
            else //历史
            {
                ECAddr = GetTwoTableAddrFromBlock(TYPE_HISTROY_POWER_RECORD,(ID0-1),0);
                DLTTRACE("HISTROY_addr=0x%08X\n", ECAddr);
                if (IS_TWOTABLE_ADDR_ERR(ECAddr)) return DLT_RET_ERR;   
            }

            if (ID1==0xFF)
            {
                u8  TFeeNum=GetSetFeeNumber();
                
                ECAddr += (ecindex+0)*COMM_READ_EC_LENTH;
                *ucLen = COMM_READ_EC_LENTH*(TFeeNum+1);
                if((*ucLen>COMM_READMAXSIZE) || (*ucLen>ulBufLen))
                {
                    ///保存后续帧到后续BUFFER中
                    return DLT_RET_ERR;
                }
                ReadDataDirect(ECAddr, *ucLen, pData);
            }
            else
            {
                ECAddr += (ecindex+ID1)*COMM_READ_EC_LENTH;
                *ucLen = COMM_READ_EC_LENTH;
                if(*ucLen > ulBufLen) return DLT_RET_ERR;
                ReadDataDirect(ECAddr, *ucLen, pData);
            }
        }
    }
    return DLT_RET_SUCC;
}

/******************************************************************************************
            DLT645-07 需量数据开始
******************************************************************************************/
//根据需量存储地址转换成需量索引
#define MD_RAM_TO_IDX(ram)          ((u8)(((ram)-RAM_DEMAND_DATA_START)/BYTES_PER_DEMAND))
//根据需量索引转换成需量存储的地址的偏移量
#define MD_IDX_TO_OFFSET(idx)       ((u32)((idx)*BYTES_PER_DEMAND))
//根据需量索引转换成需量存储的地址
#define MD_IDX_TO_RAM(idx)          ((u32)(RAM_DEMAND_DATA_START+MD_IDX_TO_OFFSET(idx)))
#define MD_ZT(type,ph,zh,id2,addr)  (ECZT(type,ph,zh)), (id2), MD_RAM_TO_IDX(addr)

//#pragma diag_remark=Pa089
const EC_ID2_DEF MD_Id2[]=
{
//从左到右依次是:
    //需量简单类型
    //分合相
    //组合类型
    //ID2
    //需量地址(为了减少数组空间，地址将会转换为索引)
    {MD_ZT(EC_TYPE_YG, EC_PH_ALL, EC_YG_ZH_ZX, 0x01, RAM_KW_F_ALL_DATA)},     /*01: 正向有功*/
    {MD_ZT(EC_TYPE_YG, EC_PH_ALL, EC_YG_ZH_FX, 0x02, RAM_KW_R_ALL_DATA)},     /*02: 反向有功*/
#if 1     
    {MD_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_Z1, 0x03, RAM_KVAR_C1_ALL_DATA)},  /*03: 组合无功1*/
    {MD_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_Z2, 0x04, RAM_KVAR_C2_ALL_DATA)},  /*04: 组合无功2*/
#endif    
    {MD_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_X1, 0x05, RAM_KVAR_Q1_ALL_DATA)},  /*05: 1象限无功*/
    {MD_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_X2, 0x06, RAM_KVAR_Q2_ALL_DATA)},  /*06: 2象限无功*/
    {MD_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_X3, 0x07, RAM_KVAR_Q3_ALL_DATA)},  /*07: 3象限无功*/
    {MD_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_X4, 0x08, RAM_KVAR_Q4_ALL_DATA)},  /*08: 4象限无功*/
#if 1     
    {MD_ZT(EC_TYPE_SZ, EC_PH_ALL, EC_YG_ZH_ZX, 0x09, RAM_KVA_F_ALL_DATA)},     /*09: 正向视在*/
    {MD_ZT(EC_TYPE_SZ, EC_PH_ALL, EC_YG_ZH_FX, 0x0A, RAM_KVA_R_ALL_DATA)},     /*0A: 反向视在*/
    {MD_ZT(EC_TYPE_YG, EC_PH_PHA, EC_YG_ZH_ZX, 0x15, RAM_KW_A_F_ALL_DATA)},    /*15: A正向有功*/
    {MD_ZT(EC_TYPE_YG, EC_PH_PHA, EC_YG_ZH_FX, 0x16, RAM_KW_A_R_ALL_DATA)},    /*16: A反向有功*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_Z1, 0x17, RAM_KVAR_A_C1_ALL_DATA)},     /*17: A组合无功1*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_Z2, 0x18, RAM_KVAR_A_C2_ALL_DATA)},     /*18: A组合无功2*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_X1, 0x19, RAM_KVAR_A_Q1_ALL_DATA)},     /*19: A1象限无功*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_X2, 0x1A, RAM_KVAR_A_Q2_ALL_DATA)},     /*1A: A2象限无功*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_X3, 0x1B, RAM_KVAR_A_Q3_ALL_DATA)},     /*1B: A3象限无功*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_X4, 0x1C, RAM_KVAR_A_Q4_ALL_DATA)},     /*1C: A4象限无功*/
    {MD_ZT(EC_TYPE_SZ, EC_PH_PHA, EC_YG_ZH_ZX, 0x1D, RAM_KVA_A_F_ALL_DATA)},     /*1D: A正向视在*/
    {MD_ZT(EC_TYPE_SZ, EC_PH_PHA, EC_YG_ZH_FX, 0x1E, RAM_KVA_A_R_ALL_DATA)},     /*1E: A反向视在*/
    {MD_ZT(EC_TYPE_YG, EC_PH_PHB, EC_YG_ZH_ZX, 0x29, RAM_KW_B_F_ALL_DATA)},      /*29: B正向有功*/
    {MD_ZT(EC_TYPE_YG, EC_PH_PHB, EC_YG_ZH_FX, 0x2A, RAM_KW_B_R_ALL_DATA)},      /*2A: B反向有功*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_Z1, 0x2B, RAM_KVAR_B_C1_ALL_DATA)},     /*2B: B组合无功1*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_Z2, 0x2C, RAM_KVAR_B_C2_ALL_DATA)},     /*2C: B组合无功2*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_X1, 0x2D, RAM_KVAR_B_Q1_ALL_DATA)},     /*2D: B1象限无功*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_X2, 0x2E, RAM_KVAR_B_Q2_ALL_DATA)},     /*2E: B2象限无功*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_X3, 0x2F, RAM_KVAR_B_Q3_ALL_DATA)},     /*2F: B3象限无功*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_X4, 0x30, RAM_KVAR_B_Q4_ALL_DATA)},     /*30: B4象限无功*/
    {MD_ZT(EC_TYPE_SZ, EC_PH_PHB, EC_YG_ZH_ZX, 0x31, RAM_KVA_B_F_ALL_DATA)},       /*31: B正向视在*/
    {MD_ZT(EC_TYPE_SZ, EC_PH_PHB, EC_YG_ZH_FX, 0x32, RAM_KVA_B_R_ALL_DATA)},       /*32: B反向视在*/
    {MD_ZT(EC_TYPE_YG, EC_PH_PHC, EC_YG_ZH_ZX, 0x3D, RAM_KW_C_F_ALL_DATA)},      /*3D: C正向有功*/
    {MD_ZT(EC_TYPE_YG, EC_PH_PHC, EC_YG_ZH_FX, 0x3E, RAM_KW_C_R_ALL_DATA)},      /*3E: C反向有功*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_Z1, 0x3F, RAM_KVAR_C_C1_ALL_DATA)},     /*3F: C组合无功1*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_Z2, 0x40, RAM_KVAR_C_C2_ALL_DATA)},     /*40: C组合无功2*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_X1, 0x41, RAM_KVAR_C_Q1_ALL_DATA)},     /*41: C1象限无功*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_X2, 0x42, RAM_KVAR_C_Q2_ALL_DATA)},     /*42: C2象限无功*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_X3, 0x43, RAM_KVAR_C_Q3_ALL_DATA)},     /*43: C3象限无功*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_X4, 0x44, RAM_KVAR_C_Q4_ALL_DATA)},     /*44: C4象限无功*/
    {MD_ZT(EC_TYPE_SZ, EC_PH_PHC, EC_YG_ZH_ZX, 0x45, RAM_KVA_C_F_ALL_DATA)},       /*45: C正向视在*/
    {MD_ZT(EC_TYPE_SZ, EC_PH_PHC, EC_YG_ZH_FX, 0x46, RAM_KVA_C_R_ALL_DATA)},       /*46: C反向视在*/
#endif    
};
//#pragma diag_default=Pa089
#define MD_Id2_TABLE_LEN    (sizeof(MD_Id2)/sizeof(EC_ID2_DEF))

/*********************************************************************
函数：MDId2IdxFind
功能：根据DLT645 ID找出在信息数组中索引、并判断其正确性澹(包括是否支持)
参数：
        u32 ID:           DLT645 ID( (((ID3*256+ID2)*256)+ID1)*256+ID0 )
Input:
Output:
返回：  DLT_RET_ERR:    ID错误或不支持    
        其他:           正确的索引
范围：
注释：无。
********************************************************************/
u8 MDId2IdxFind(u32 ID);
u8 MDId2IdxFind(u32 ID)
{
    u8 ID3=DLT_ID3(ID);
    u8 ID2=DLT_ID2(ID);
    u8 ID0=DLT_ID0(ID);
    u8 ID1=DLT_ID1(ID);
    u16  idx=0;

    DLTTRACE("ID=0x%08X, ID3=%02X, ID2=%02X, ID1=%02X, ID0=%02X\n", ID, ID3, ID2, ID1, ID0);
    if(ID3 != 0x01) return DLT_RET_ERR;
    if(ID2 == 0xFF) return DLT_RET_ERR;
    if((ID1 == 0xFF) && (ID0 == 0xFF)) return DLT_RET_ERR;
    if((ID0 > COMM_READ_MD_HISTORY) && (ID0 != 0xFF)) return DLT_RET_ERR;
    if((ID1 > GetSetFeeNumber()) && (ID1 != 0xFF)) return DLT_RET_ERR;

    for(idx=0; idx<MD_Id2_TABLE_LEN; idx++)
    {
        if(MD_Id2[idx].id2 == ID2)
            break;
    }
    if(idx >= MD_Id2_TABLE_LEN)
        return DLT_RET_ERR;
    if(isTheMDIdxUnSupport(idx)) return DLT_RET_ERR;
    //如果该大类没有费率项,而ID1却有该项则错误
    if(ID1 > 0) //无费率情况下，0xFF也不允许
        if(ECZT_PH(MD_Id2[idx].ectype) != EC_PH_ALL) 
                return DLT_RET_ERR;
    
    return idx;
}
/*********************************************************************
函数：SymbolGetMDData
功能：根据DLT645 ID算出需要显示的图标
参数：
Input:
Output:
返回：  DLT_RET_SUCC:   读成功        
        DLT_RET_ERR:    失败
范围：
注释：无。
********************************************************************/
u8 SymbolGetMDData(STR_DISPLAYSYMBOL *sym, u32 ID, u8 idSerialNumber, u8 *ucDLen, u8 *dataType)
{
    u8 ID0=DLT_ID0(ID);
    u8 ID1=DLT_ID1(ID);
    u8 ID2=DLT_ID2(ID);
    ECTYPE_CHAR ECtype, type;
    u16  idx;

    if(idSerialNumber > 2) return DLT_RET_ERR;
    if((ID2 == 0xFF) || (ID1 == 0xFF) || (ID0 == 0xFF))
        return DLT_RET_ERR;
    
    idx = MDId2IdxFind(ID);
    if(idx == DLT_RET_ERR)
        return DLT_RET_ERR;
    
    sym->Xu= 1;
    sym->Liang = 1;
    
    if(idSerialNumber == 0)
    {
        *ucDLen = 4;
        *dataType = DATA_TYPE_XL;
    }
    else if(idSerialNumber == 1)
    {
        *ucDLen = 3;
        *dataType = DATA_TYPE_BCD3_8;
        return DLT_RET_SUCC;
    }
    else if(idSerialNumber == 2)
    {
        sym->timeshi = 1;
        sym->timejian = 1;
        *ucDLen = 2;
        *dataType = DATA_TYPE_BCD5_8;
        return DLT_RET_SUCC;
    }

    ECtype = EC_Id2[idx].ectype; 
    type = ECZT_TYPE(ECtype);

    switch(type)
    {
        case EC_TYPE_YG:
        case EC_TYPE_WG:
            sym->Gong = 1;
            //sym->Xu= 1;
            //sym->Liang = 1;
            if(type == EC_TYPE_YG)
            {
                sym->You = 1;
                sym->KW = 1;
                sym->h1 = 1;
            }
            else
            {
                sym->Wu = 1;
                sym->kvar = 1;
                sym->h2 = 1;
            }
            if(ID1 == 0)
            {
                sym->Zong = 1;
            }
            else if(ID1 == 1)
            {
                sym->Jian= 1;
            }
            else if(ID1 == 2)
            {
                sym->Feng= 1;
            }
            else if(ID1 == 3)
            {
                sym->Ping= 1;
            }
            else if(ID1 == 4)
            {
                sym->Gu= 1;
            }
            if(ID0 == 0)
            {
                sym->DangQian = 1;
            }
            else if(ID0 <= 12)
            {
                sym->Shang1 = 1;
                sym->month = 1;
            }
            //else
            //    return DLT_RET_ERR;
            break;
        
        case EC_TYPE_SZ:
        default:
            return DLT_RET_ERR;
            //break;
    }
    switch(ECZT_PH(ECtype))
    {
        case EC_PH_ALL:
            //sym->Zong = 1;
            break;
        case EC_PH_PHA:
            sym->phaseA = 1;
            break;
        case EC_PH_PHB:
            sym->phaseB = 1;
            break;
        case EC_PH_PHC:
            sym->phaseC = 1;
            break;
    }
    if(type == EC_TYPE_WG)
    {
        switch(ECZT_ZH(ECtype))
        {
            case EC_WG_ZH_Z1:
                sym->zuhe = 1;
                sym->issigned = 1;
                sym->wugongxiangxian1 = 1;
                break;
            case EC_WG_ZH_Z2:
                sym->zuhe = 1;
                sym->issigned = 1;
                sym->wugongxiangxian1 = 1;
                sym->wugongxiangxian2 = 1;
                break;
            case EC_WG_ZH_GX:
                sym->zuhe = 1;
                sym->issigned = 1;
                sym->wugongxiangxian1 = 1;
                sym->wugongxiangxian2 = 1;
                sym->wugongxiangxian3 = 1;
                break;
            case EC_WG_ZH_RX:
                sym->zuhe = 1;
                sym->issigned = 1;
                sym->wugongxiangxian3 = 1;
                sym->wugongxiangxian4 = 1;
                break;
            case EC_WG_ZH_X1:
                sym->wugongxiangxian1 = 1;
                break;
            case EC_WG_ZH_X2:
                sym->wugongxiangxian1 = 1;
                sym->wugongxiangxian2 = 1;
                break;
            case EC_WG_ZH_X3:
                sym->wugongxiangxian1 = 1;
                sym->wugongxiangxian2 = 1;
                sym->wugongxiangxian3 = 1;
                break;
        case EC_WG_ZH_X4:
                sym->wugongxiangxian3 = 1;
                sym->wugongxiangxian4 = 1;
                break;
        }
    }
    else
    {
        switch(ECZT_ZH(ECtype))
        {
            case EC_YG_ZH_ZH:
                sym->zuhe = 1;
                sym->issigned = 1;
                break;
            case EC_YG_ZH_ZX:
                sym->Zheng = 1;
                sym->fangXiang = 1;
                break;
            case EC_YG_ZH_FX:
                sym->Fan = 1;
                sym->fangXiang = 1;
                break;
        }
    }
    if(sym->issigned == 0)
        *dataType = DATA_TYPE_XL;
    else
        *dataType = DATA_TYPE_XL_signed;
    return DLT_RET_SUCC;
}

/*********************************************************************
函数：GetMDDataByID
功能：根据DLT645 ID读取需量数据
参数：
        u8 *pData:       数据buf，用来存放读回的数据
        u16 *ucLen:        读回数据长度
        u32 ID:           DLT645 ID( (((ID3*256+ID2)*256)+ID1)*256+ID0 )
        u16 ulBufLen:      调用是给的buf的长度
Input:
Output:
返回：  0:读成功        
        1:读失败
范围：
注释：无。
********************************************************************/
u8 GetMDDataByID(u8 *pData, u16 *ucLen, u32 ID, u16 ulBufLen)
{
    u8 ID0=DLT_ID0(ID);
    u8 ID1=DLT_ID1(ID);
    //u8 ID2=DLT_ID2(ID);
    //ECTYPE_CHAR ECtype, type;
    u8 ecindex;
    u16  idx;
    u32 ECAddr;
    u8  TFeeNum=GetSetFeeNumber();
    
    idx = MDId2IdxFind(ID);
    if(idx == DLT_RET_ERR) return DLT_RET_ERR;

    ecindex = MD_Id2[idx].ecindex;
    *ucLen = 0;
    DLTTRACE("GetMDDataByID idx=%d,ecindex=%d\n",idx, ecindex);
     
    {
        if(ID0==0xFF)
        {
            if(COMM_READ_MD_ID_LENTH*(COMM_READ_MD_HISTORY+1) > ulBufLen) 
                return DLT_RET_ERR;
            for(ID0=0; ID0<=COMM_READ_MD_HISTORY; ID0++)
            {
                if(ID0==0)///当前
                {
                    ECAddr = RAM_DEMAND_DATA_START;
                }
                else //历史
                {
                    ECAddr = GetTwoTableAddrFromBlock(TYPE_HISTROY_DEMAND_RECORD,(ID0-1),0);
                    if (IS_TWOTABLE_ADDR_ERR(ECAddr)) return DLT_RET_ERR; 
                }
                ECAddr += (MD_IDX_TO_OFFSET(ecindex+ID1));
                //if(*ucLen > ulBufLen) return DLT_RET_ERR;
                ReadDataDirect(ECAddr, COMM_READ_MD_ID_LENTH, pData);
                *ucLen += COMM_READ_MD_ID_LENTH;
            }
        }
        else
        {
            if(ID0==0)///当前
            {
                ECAddr = RAM_DEMAND_DATA_START;
            }
            else //历史
            {
                ECAddr = GetTwoTableAddrFromBlock(TYPE_HISTROY_DEMAND_RECORD,(ID0-1),0);
                    if (IS_TWOTABLE_ADDR_ERR(ECAddr)) return DLT_RET_ERR;  
            }

            if (ID1==0xFF)
            {
                DLTTRACE("GetMDDataByID addr=0x%08X, len=%d, %d\n",ECAddr, ecindex, MD_IDX_TO_OFFSET(ecindex+0));
                ECAddr += (MD_IDX_TO_OFFSET(ecindex+0));
                *ucLen = COMM_READ_MD_ID_LENTH*(TFeeNum+1);
                if((*ucLen>COMM_READMAXSIZE) || (*ucLen>ulBufLen))
                {
                    ///保存后续帧到后续BUFFER中
                    return DLT_RET_ERR;
                }
                DLTTRACE("GetMDDataByID addr=0x%08X, len=%d\n",ECAddr, *ucLen);
                ReadDataDirect(ECAddr, *ucLen, pData);
            }
            else
            {
                ECAddr += (MD_IDX_TO_OFFSET(ecindex+ID1));
                *ucLen = COMM_READ_MD_ID_LENTH;
                if(*ucLen > ulBufLen) return DLT_RET_ERR;
                ReadDataDirect(ECAddr, *ucLen, pData);
            }
        }
    }
    return DLT_RET_SUCC;
}

/******************************************************************************************
            DLT645-07 变量数据开始
******************************************************************************************/
//enum
//{
#define    VR_TYPE_VOL   0x00     //电压
#define    VR_TYPE_CUL   0x01     //电流
#define    VR_TYPE_YGL   0x02     //有功功率
#define    VR_TYPE_WGL   0x03     //无功功率
#define    VR_TYPE_SZL   0x04     //视在功率
#define    VR_TYPE_GLY   0x05     //功率因数
#define    VR_TYPE_XJX   0x06     //相角-同相电压和电流
#define    VR_TYPE_VSZ   0x07     //电压失真度
#define    VR_TYPE_ISZ   0x08     //电流失真度
#define    VR_TYPE_VXH   0x09     //电压谐波含有率
#define    VR_TYPE_IXH   0x0A     //电流谐波含有率
#define    VR_TYPE_OTH   0x0B     //其他
#define    VR_TYPE_VXX   0x0C     //电压谐波有效值
#define    VR_TYPE_IXX   0x0D     //电流谐波有效值
#define    VR_TYPE_XJ1   0x0E     //相角-各相电压对A相电压
#define    VR_TYPE_XJ2   0x0F     //相角-各相电流对A相电压
#define    VR_TYPE_ILX   0x11     // 3 零线电流
#define    VR_TYPE_WFL   0x12     // 2 电网频率
#define    VR_TYPE_PER   0x13     // 3 一分钟有功总平均功率
#define    VR_TYPE_XYG   0x14     // 3 当前有功需量
#define    VR_TYPE_XWG   0x15     // 3 当前无功需量
#define    VR_TYPE_XSZ   0x16     // 2 当前视在需量
#define    VR_TYPE_CBN   0x17     // 2 表内温度
#define    VR_TYPE_SZV   0x18     // 2 时钟电池电压（内部）
#define    VR_TYPE_DCV   0x19     // 2 停电抄表电池电压（外部）
#define    VR_TYPE_TTD   0x1A     // 4 内部电池工作时间
#define    VR_TYPE_JTP   0x1B     // 4 当前阶梯电价
//};
//分合相
enum
{
    VR_PH_ALL,      //合相  //只有三种功率和功率因数有
    VR_PH_PHA,      //A相
    VR_PH_PHB,      //B相
    VR_PH_PHC,      //C相
};
// type:电量类型 ph:分合相 zh:组合方式  //注意x，z不能超过3位
#define VRZT(type)          ( ((type)) )
#define VRZT_TYPE(v)        ( ((v) )

#define VR_ZT(type,id2,ul,fl,id1s,id1w,id1n,addr)    ((addr)&0xFFFF), (VRZT(type)), (id2), (ul), (fl), (id1s),(id1w), (id1n), 0
typedef struct
{
    u16 Addr;               //存储地址
    u8 vrtype;           //数据类型
    u8 id2;              //Acturally, it is no use buf for aligned
    u8 UsedLenth:4;      //存储使用的字节长度(长度不会超过15)
    u8 FormatLenth:4;    //规约格式使用的字节长度(长度不会超过15)
    u8 id1Start:1;       //规约中ID1开始的数字
    u8 id1WithFF:1;      //ID1为FF也可以抄收.0:不可以,1:可以
    u8 id1Num:4;         //存储的项数(3:ABC三相 4:总+ABC)
    u8 others:2;         //保留
    //u8 id0Start:1;       //规约中ID0开始的数字
    //u8 id0WithFF:1;      //ID0为FF也可以抄收.0:不可以,1:可以
    //u8 RecordTim;      //记录的次数(ID0)00:代表不能用FF抄收.>0的话,就可以用FF抄收
}VR_ID2_DEF;
//#pragma diag_remark=Pa089

const VR_ID2_DEF VR_Id2[]=
{
//从左到右依次是:
    //变量类型
//Acturally, it is no use buf for aligned
//存储使用的字节长度(长度不会超过15)
//规约格式使用的字节长度(长度不会超过15)
//规约中ID1开始的数字
//ID1为FF也可以抄收.0:不可以,1:可以
//存储的项数(3:ABC三相 4:总+ABC)
//存储地址
    {VR_ZT(VR_TYPE_VOL, 0x01, 4, 2, 1, 1, 3, RAM_CURRENT_V_A        )},  /*01: 电压*/
    {VR_ZT(VR_TYPE_CUL, 0x02, 4, 3, 1, 1, 3, RAM_CURRENT_I_A        )},  /*02: 电流*/
    {VR_ZT(VR_TYPE_YGL, 0x03, 4, 3, 0, 1, 4, RAM_CURRENT_KW_ALL     )},  /*03: 有功功率*/
    {VR_ZT(VR_TYPE_WGL, 0x04, 4, 3, 0, 1, 4, RAM_CURRENT_KVAR_ALL   )},  /*04: 无功功率*/
    {VR_ZT(VR_TYPE_SZL, 0x05, 4, 3, 0, 1, 4, RAM_CURRENT_KVA_ALL    )},  /*05: 视在功率*/
    {VR_ZT(VR_TYPE_GLY, 0x06, 4, 2, 0, 1, 4, RAM_CURRENT_FACTOR_ALL )},  /*06: 功率因数*/
    {VR_ZT(VR_TYPE_XJX, 0x07, 2, 2, 1, 1, 3, RAM_CURRENT_ANGLE_AV_AI)},  /*07: 相角-同相电压和电流*/
#if(CONFIG_METER_HARMONIC_ENABLE == GAL_YES)    
    {VR_ZT(VR_TYPE_VSZ, 0x08, 2, 2, 1, 1, 3, RAM_CURRENT_HARMONIC_PER_V_A_ALL      )},  /*08: 电压失真度*/
    {VR_ZT(VR_TYPE_ISZ, 0x09, 2, 2, 1, 1, 3, RAM_CURRENT_HARMONIC_PER_I_A_ALL      )},  /*09: 电流失真度*/
    {VR_ZT(VR_TYPE_VXH, 0x0A, 2, 2, 1, 0, 0, RAM_CURRENT_HARMONIC_PER_V_A_01CI     )},  /*0A: 电压谐波含有率*/
    {VR_ZT(VR_TYPE_IXH, 0x0B, 2, 2, 1, 0, 0, RAM_CURRENT_HARMONIC_PER_I_A_01CI     )},  /*0B: 电流谐波含有率*/
    {VR_ZT(VR_TYPE_VXX, 0x0C, 4, 2, 1, 1, 0, RAM_CURRENT_HARMONIC_V_A_ALL          )},  /*0B: 电压谐波有效值*/
    {VR_ZT(VR_TYPE_IXX, 0x0D, 4, 3, 1, 1, 0, RAM_CURRENT_HARMONIC_I_A_ALL          )},  /*0B: 电流谐波有效值*/
#endif    
    {VR_ZT(VR_TYPE_XJ1, 0xF1, 2, 2, 1, 1, 3, RAM_CURRENT_ANGLE_AV_AV)},  /*07: 相角-各相电压对A相电压*/
    {VR_ZT(VR_TYPE_XJ2, 0xF2, 2, 2, 1, 1, 3, RAM_CURRENT_ANGLE_AI_AV)},  /*07: 相角-各相电流对A相电压*/
    {VR_ZT(VR_TYPE_OTH, 0x80, 0, 0, 0, 0, 0, PT_OTHER               )},  /*80: 其他*/
};
#define VR_ID2_TABLE_LEN    (sizeof(VR_Id2)/sizeof(VR_ID2_DEF))
////变量表中的特殊项0x80,由于长度不会超过15所以长度用半字节来表示
typedef struct
{
    u32 Addr;            //变量存储地址
    u8 vrtype;           //变量类型
    u8 datatype;         //变量数据类型
    u8 id0;              //DI0
    //u8 Used:1;         //是否使用0:没有,1,使用
    u8 FormatLenth:4;    //规约使用的长度
    u8 UsedLenth:4;      //存储使用的长度
}STR_VAR_ESPECEIVE;
#define VR_ESP(type, id0, ud, fl, ul, dtype, addr)     (addr), (type), (dtype), (id0), (fl), (ul)
///变量中0x80这些比较特殊的
const STR_VAR_ESPECEIVE VR_OTH_Id0[]=
{
//从左到右依次是:
    //变量类型
    //ID0
    //该变量是否使用(目前此数据未采用，依旧根据地址判断)
    //规约格式使用的字节长度(长度不会超过15)
    //存储使用的长度
    //变量数据类型
    //存储地址
    {VR_ESP(VR_TYPE_ILX, 0x01, 1, 3, 4, DATA_TYPE_CURRENT,   RAM_CURRENT_I_NULLSEQU       )},  /*01: 零线电流*/
    {VR_ESP(VR_TYPE_WFL, 0x02, 1, 2, 6, DATA_TYPE_BCD5_8,    RAM_CURRENT_FREQ_A           )},  /*02: 电网频率*/
    {VR_ESP(VR_TYPE_PER, 0x03, 1, 3, 4, DATA_TYPE_XL_signed, RAM_AVERAGE_KW_ALL           )},  /*03: 一分钟有功总平均功率*/
    {VR_ESP(VR_TYPE_XYG, 0x04, 1, 3, 4, DATA_TYPE_XL_signed, RAM_CURRENT_DEMAND_KW_TOTAL  )},  /*04: 当前有功需量*/
    {VR_ESP(VR_TYPE_XWG, 0x05, 1, 3, 4, DATA_TYPE_XL_signed, RAM_CURRENT_DEMAND_KVAR_TOTAL)},  /*05: 当前无功需量*/
    {VR_ESP(VR_TYPE_XSZ, 0x06, 1, 3, 4, DATA_TYPE_XL_signed, RAM_CURRENT_DEMAND_KVA_TOTAL )},  /*06: 当前视在需量*/
    {VR_ESP(VR_TYPE_CBN, 0x07, 1, 2, 2, DATA_TYPE_WENDU,     RAM_CURRENT_METER_TEMP       )},  /*07: 表内温度*/
    {VR_ESP(VR_TYPE_SZV, 0x08, 1, 2, 2, DATA_TYPE_BCD5_8,    RAM_CURRENT_CLOCK_VOLTAGE    )},  /*08: 时钟电池电压（内部）*/
    {VR_ESP(VR_TYPE_DCV, 0x09, 1, 2, 2, DATA_TYPE_BCD5_8,    RAM_CURRENT_WAKEUP_VOLTAGE   )},  /*09: 停电抄表电池电压（外部）*/
    {VR_ESP(VR_TYPE_TTD, 0x0A, 1, 4, 4, DATA_TYPE_BCD1_8,    EPL_CURRENT_BAT_USETIME      )},  /*0A: 内部电池工作时间*/
#if(CONFIG_METER_STEP_PERIODPRICE_MODE==CONFIG_METER_STEP_PERIODPRICE_MODE_ENABLE)
    {VR_ESP(VR_TYPE_JTP, 0x0B, 1, 4, 4, DATA_TYPE_BCD1_8,    RAM_CURRENT_STEPPRICE_PRICE  )},  /*0B: 当前阶梯电价*/
#else
    {VR_ESP(VR_TYPE_JTP, 0x0B, 1, 4, 4, DATA_TYPE_BCD1_8,    PT_UNSUPPORT                 )},  /*0B: 当前阶梯电价*/
#endif
};
#define VR_OTH_Id0_TABLE_LEN    (sizeof(VR_OTH_Id0)/sizeof(STR_VAR_ESPECEIVE))

//#pragma diag_default=Pa089

/*********************************************************************
函数：VRId2IdxFind
功能：根据DLT645 ID找出在信息数组中索引、并判断其正确性澹(包括是否支持)
参数：
        u32 ID:           DLT645 ID( (((ID3*256+ID2)*256)+ID1)*256+ID0 )
Input:
Output:
返回：  DLT_RET_ERR:    ID错误或不支持    
        其他:           正确的索引
范围：
注释：无。
********************************************************************/
u8 VRId2IdxFind(u32 ID);
u8 VRId2IdxFind(u32 ID)
{
    u8 ID3=DLT_ID3(ID);
    u8 ID2=DLT_ID2(ID);
    u8 ID0=DLT_ID0(ID);
    u8 ID1=DLT_ID1(ID);
    u16  idx=0;
    VR_ID2_DEF *pVR_Id2;

    if(ID3 != 0x02) return DLT_RET_ERR;
    if(ID2 == 0xFF) return DLT_RET_ERR;
    if((ID1 == 0xFF) && (ID0 == 0xFF)) return DLT_RET_ERR;

    for(idx=0; idx<VR_ID2_TABLE_LEN; idx++)
    {
        if(VR_Id2[idx].id2 == ID2)
            break;
    }
    if(idx >= VR_ID2_TABLE_LEN)
    {
        return DLT_RET_ERR;
    }
    if(ID2 == 0x80)
    {
        if(ID1 != 0) return DLT_RET_ERR;
        if((ID0 < 1) || (ID0 > 0x0B)) return DLT_RET_ERR;
        if((ID0) > VR_OTH_Id0_TABLE_LEN)
            return DLT_RET_ERR;
        if(isTheVROTHIdxUnSupport(ID0-1))  return DLT_RET_ERR;
        
        return idx;
    }
    
    if(isTheVRIdxUnSupport(idx)) return DLT_RET_ERR;

    pVR_Id2 = (VR_ID2_DEF*)(&(VR_Id2[idx]));
    if(ID1 == 0xFF)
    {
        if(pVR_Id2->id1WithFF != 1)
            return DLT_RET_ERR;
    }
    else if( (ID1 < pVR_Id2->id1Start) && (ID1 > (pVR_Id2->id1Start + pVR_Id2->id1Num)) )
    {
        return DLT_RET_ERR;
    }

    if(pVR_Id2->vrtype < VR_TYPE_VXH)  
    {
        if(ID0 != 0) return DLT_RET_ERR;
    }
    else if((pVR_Id2->vrtype == VR_TYPE_VXH) || (pVR_Id2->vrtype == VR_TYPE_IXH))
    {
        if((ID0 != 0xFF) && ((ID0 == 0) || (ID0 > GetSetHarmonicNumber()))) return DLT_RET_ERR;
    }
    else if((pVR_Id2->vrtype == VR_TYPE_VXX) || (pVR_Id2->vrtype == VR_TYPE_IXX))
    {
        if((ID0 != 0xFF) && ((ID0 > GetSetHarmonicNumber()))) return DLT_RET_ERR;
    }
    return idx;
}
/*********************************************************************
函数：SymbolGetMDData
功能：根据DLT645 ID算出需要显示的图标
参数：
Input:
Output:
返回：  DLT_RET_SUCC:   读成功        
        DLT_RET_ERR:    失败
范围：
注释：无。
********************************************************************/
u8 SymbolGetVRData(STR_DISPLAYSYMBOL *sym, u32 ID, u8 idSerialNumber, u8 *ucDLen, u8 *dataType)
{
    u8 ID0=DLT_ID0(ID);
    u8 ID1=DLT_ID1(ID);
    u8 ID2=DLT_ID2(ID);
    u8 vrtype;
    u16  idx;

    if(idSerialNumber > 2) return DLT_RET_ERR;
    if((ID2 == 0xFF) || (ID1 == 0xFF) || (ID0 == 0xFF))
        return DLT_RET_ERR;
    
    idx = VRId2IdxFind(ID);
    if(idx == DLT_RET_ERR)
        return DLT_RET_ERR;
    
    vrtype = VR_Id2[idx].vrtype;
    if(vrtype == VR_TYPE_OTH)
    {
        switch(VR_OTH_Id0[ID0-1].vrtype)
        {
            case VR_TYPE_ILX:
                sym->Dian = 1;
                sym->Liu = 1;
                sym->phaseN = 1;
                break;
            case VR_TYPE_WFL:
                break;
            case VR_TYPE_PER:
                sym->Power = 1;
                break;
            case VR_TYPE_XYG:
                sym->DangQian = 1;
                sym->You = 1;
                sym->Gong = 1;
                sym->Xu = 1;
                sym->Liang = 1;
                break;
            case VR_TYPE_XWG:
                sym->DangQian = 1;
                sym->Wu= 1;
                sym->Gong = 1;
                sym->Xu = 1;
                sym->Liang = 1;
                break;
            case VR_TYPE_XSZ:
                sym->DangQian = 1;
                sym->Xu = 1;
                sym->Liang = 1;
                break;
            case VR_TYPE_CBN:
                break;
            case VR_TYPE_SZV:
            case VR_TYPE_DCV:
                sym->V = 1;
                break;
            case VR_TYPE_TTD:
                sym->timeshi = 1;
                sym->timejian = 1;
                break;
            case VR_TYPE_JTP:
                sym->yuan = 1;
                break;
        }
        *dataType = VR_OTH_Id0[ID0-1].datatype;
        *ucDLen = VR_OTH_Id0[ID0-1].UsedLenth;
        return DLT_RET_SUCC;
    }
    *ucDLen = VR_Id2[idx].UsedLenth;
    switch(vrtype)
    {
        case VR_TYPE_VOL:
            sym->Dian = 1;
            sym->Ya = 1;
            *dataType = DATA_TYPE_VOLTAGE;
            break;
        case VR_TYPE_CUL:
            sym->Dian = 1;
            sym->Liu = 1;
            *dataType = DATA_TYPE_CURRENT;
            break;
        case VR_TYPE_YGL:
            sym->You = 1;
            sym->Gong = 1;
            sym->Power = 1;
            *dataType = DATA_TYPE_XL_signed;
            break;
        case VR_TYPE_WGL:
            sym->Wu = 1;
            sym->Gong = 1;
            sym->Power = 1;
            *dataType = DATA_TYPE_XL_signed;
            break;
        case VR_TYPE_SZL:
            sym->Power = 1;
            *dataType = DATA_TYPE_XL_signed;
            break;
        case VR_TYPE_GLY:
            sym->Power = 1;
            *dataType = DATA_TYPE_POWER_COSE;
            break;
        case VR_TYPE_XJX:
        case VR_TYPE_XJ1:
        case VR_TYPE_XJ2:
            sym->cos = 1;
            *dataType = DATA_TYPE_PHASIE;
            break;
        case VR_TYPE_VSZ:
            sym->Dian = 1;
            sym->Ya = 1;
            sym->Shi = 1;
            *dataType = DATA_TYPE_BCD1_8;
            break;
        case VR_TYPE_ISZ:
            sym->Dian = 1;
            sym->Liu = 1;
            sym->Shi = 1;
            *dataType = DATA_TYPE_BCD1_8;
            break;
        case VR_TYPE_VXH:
            sym->Dian = 1;
            sym->Ya = 1;
            sym->Power = 1;
            *dataType = DATA_TYPE_BCD1_8;
            break;
        case VR_TYPE_IXH:
            sym->Dian = 1;
            sym->Liu = 1;
            sym->Power = 1;
            *dataType = DATA_TYPE_BCD1_8;
            break;
        case VR_TYPE_VXX:
            sym->Dian = 1;
            sym->Ya = 1;
            sym->Power = 1;
            *dataType = DATA_TYPE_VOLTAGE;
            break;
        case VR_TYPE_IXX:
            sym->Dian = 1;
            sym->Liu = 1;
            sym->Power = 1;
            *dataType = DATA_TYPE_CURRENT;
            break;
    }
    
    switch(ID1)
    {
        case 0:
            sym->Zong = 1;
            break;
        case 1:
            sym->phaseA = 1;
            break;
        case 2:
            sym->phaseB = 1;
            break;
        case 3:
            sym->phaseC = 1;
            break;
    }
        
    return DLT_RET_SUCC;
}

/*********************************************************************
函数：GetVRDataByID
功能：根据DLT645 ID读取变量数据
参数：
        u8 *pData:       数据buf，用来存放读回的数据
        u16 *ucLen:        读回数据长度
        u32 ID:           DLT645 ID( (((ID3*256+ID2)*256)+ID1)*256+ID0 )
        u16 ulBufLen:      调用是给的buf的长度
Input:
Output:
返回：  0:读成功        
        1:读失败
范围：
注释：无。
********************************************************************/
u8 GetVRDataByID(u8 *pData, u16 *ucLen, u32 ID, u16 ulBufLen)
{
    u8 ID0=DLT_ID0(ID);
    u8 ID1=DLT_ID1(ID);
    //u8 ID2=DLT_ID2(ID);
    u16  idx;
    u8 vrtype;
    u16 tmplen;
    u32 DataAddr;
    
    idx = VRId2IdxFind(ID);
    if(idx == DLT_RET_ERR) return DLT_RET_ERR;
    if(isTheVRIdxUnSupport(idx))
        return DLT_RET_ERR;

    vrtype = VR_Id2[idx].vrtype;
    *ucLen = 0;
    DLTTRACE("GetVRDataByID idx=%d,vrtype=0x%X\n",idx, vrtype);
	
    //if(ID2 == 0x80)
    if(VR_TYPE_OTH == vrtype)
    {
        DataAddr = VR_OTH_Id0[ID0-1].Addr;
        if(DataAddr == PT_UNSUPPORT)
            return DLT_RET_ERR;
        tmplen = VR_OTH_Id0[ID0-1].UsedLenth;
        if(ulBufLen < tmplen)
            return DLT_RET_ERR;
        ReadDataDirect(DataAddr, tmplen, pData);
        *ucLen = tmplen;
        DLTTRACE("VR_TYPE_OTH idx=%d, addr=0x%X, len=%d, %02x%02x\n",(ID0-1), DataAddr, tmplen, pData[0], pData[1]);
        return DLT_RET_SUCC;
    }
    else if( (vrtype <= VR_TYPE_ISZ)
        || ((vrtype >= VR_TYPE_XJ1) && (vrtype <= VR_TYPE_XJ2)) )
    {
        DataAddr = VR_Id2[idx].Addr;
        if(ID1 == 0xFF)
            tmplen = VR_Id2[idx].UsedLenth * VR_Id2[idx].id1Num;
        else
        {
            DataAddr += VR_Id2[idx].UsedLenth * (ID1-VR_Id2[idx].id1Start);
            tmplen = VR_Id2[idx].UsedLenth;
        }

        if(tmplen > ulBufLen) 
            return DLT_RET_ERR;
        ReadDataDirect(DataAddr, tmplen, pData);
        DLTTRACE("GetVRDataByID %d, 0x%X\n",tmplen, DataAddr);
        *ucLen = tmplen;
        return DLT_RET_SUCC;
    }
    else if(vrtype <= VR_TYPE_IXH)
    {
        DataAddr = VR_Id2[idx].Addr;
        DataAddr += VR_Id2[idx].UsedLenth * (DLT_METER_HORMANIC_MAX*(ID1-VR_Id2[idx].id1Start));
        if(ID0 == 0xFF)
            tmplen = VR_Id2[idx].UsedLenth * GetSetHarmonicNumber();
        else if(ID0 > 0)
        {
            DataAddr += ( (ID0-1)*VR_Id2[idx].UsedLenth );
            tmplen = VR_Id2[idx].UsedLenth;
        }else
        	return DLT_RET_ERR;//ID0 == 0不支持
        if(tmplen > ulBufLen) 
            return DLT_RET_ERR;
        ReadDataDirect(DataAddr, tmplen, pData);
        *ucLen = tmplen;
        return DLT_RET_SUCC;
    }
    else if(vrtype <= VR_TYPE_IXX)
    {
        DataAddr = VR_Id2[idx].Addr;
        if((ID1 == 0xFF) && (ID0 == 0))
        {
            //允许块读各相总谐波有效值
            u8 ucItemLen=0;
            ucItemLen = VR_Id2[idx].UsedLenth;
            tmplen = ucItemLen*3;
            if(tmplen > ulBufLen) 
                return DLT_RET_ERR;
            ReadDataDirect(DataAddr, ucItemLen, pData);
            DataAddr += VR_Id2[idx].UsedLenth * ((DLT_METER_HORMANIC_MAX+1));
            ReadDataDirect(DataAddr, ucItemLen, pData+ucItemLen);
            DataAddr += VR_Id2[idx].UsedLenth * ((DLT_METER_HORMANIC_MAX+1));
            ReadDataDirect(DataAddr, ucItemLen, pData+ucItemLen*2);
        }
        else
        {
            DataAddr += VR_Id2[idx].UsedLenth * ((DLT_METER_HORMANIC_MAX+1)*(ID1-VR_Id2[idx].id1Start));
            if(ID0 == 0xFF)
                tmplen = VR_Id2[idx].UsedLenth * (GetSetHarmonicNumber()+1);  //各次谐波加总
            else// if(ID0 > 0)
            {
                DataAddr += ( (ID0)*VR_Id2[idx].UsedLenth );
                tmplen = VR_Id2[idx].UsedLenth;
            }/*else
            	return DLT_RET_ERR;*/
            if(tmplen > ulBufLen) 
                return DLT_RET_ERR;
            ReadDataDirect(DataAddr, tmplen, pData);
        }
        *ucLen = tmplen;
        return DLT_RET_SUCC;
    }
    else
    {
        return DLT_RET_ERR;
    }
    //return DLT_RET_SUCC;
}

/*********************************************************************
函数：VariableParaToFormat
功能：变量转换为规约格式性(注意,存储的格式都是要比规约的字节数多,并且都是要去掉存储的低位)
参数：

Input:
Output:
返回：  字节数       
范围：
注释：无。
********************************************************************/
u8 VariableParaToFormat(u32 ID,u8 Lenth,u8 *Dest)
{
    u8 ID0=DLT_ID0(ID);
    u8 ID1=DLT_ID1(ID);
    u8 ID2=DLT_ID2(ID);
    u8 Tmpbuffer[10];
    u8 idx;
    u16  TmpLenth=0;
    u8 ucNum=1;
    u8 i;
    u32 ulTmpVA;
    VR_ID2_DEF *pVR_Id2;
    
    if (ID2==0x80)
    {
        if(ID0 == 0)
            return 0;
        idx=ID0-1;
        if(idx > VR_OTH_Id0_TABLE_LEN)
            return 0;
        else if(VR_OTH_Id0[idx].datatype == DATA_TYPE_CURRENT)
        {
            memcpy(&ulTmpVA,Dest,4);
            ulTmpVA=ulTmpVA>>4;
            ulTmpVA&=0x00FFFFFF;
            memcpy(Dest,&ulTmpVA,VR_OTH_Id0[idx].FormatLenth);
            TmpLenth=VR_OTH_Id0[idx].FormatLenth;
        }
        else
        {
            TmpLenth=VR_OTH_Id0[idx].UsedLenth-VR_OTH_Id0[idx].FormatLenth;
            memcpy(Tmpbuffer,Dest+TmpLenth,VR_OTH_Id0[idx].FormatLenth);
            memcpy(Dest,Tmpbuffer,VR_OTH_Id0[idx].FormatLenth);
            TmpLenth=VR_OTH_Id0[idx].FormatLenth;
        }
    }
    else
    {
        idx=VRId2IdxFind(ID);   
        if(idx == DLT_RET_ERR)
            return 0;
        pVR_Id2 = (VR_ID2_DEF*)(&(VR_Id2[idx]));
        if (ID1==0xFF)
        {
            ucNum=pVR_Id2->id1Num;
        }
        else
        {
            if(ID0==0xFF)
            {
                //ucNum=VR_Id2[idx].RecordTim;
                if((pVR_Id2->vrtype == VR_TYPE_IXH) || (pVR_Id2->vrtype == VR_TYPE_VXH))
                    ucNum = GetSetHarmonicNumber();
                else if((pVR_Id2->vrtype == VR_TYPE_VXX) || (pVR_Id2->vrtype == VR_TYPE_IXX))
                    ucNum = GetSetHarmonicNumber()+1;
                else
                    ucNum = 1;
            }
        }
        //存储的格式与规约转换
        switch (pVR_Id2->vrtype)
        {
          
            case VR_TYPE_VOL:
                for(i=0;i<ucNum;i++)
                {
                    memcpy(&ulTmpVA, Dest+i*pVR_Id2->UsedLenth, 4);
                    ulTmpVA=ulTmpVA>>12;
                    ulTmpVA&=0x0000FFFF;
                    memcpy(Tmpbuffer,&ulTmpVA,pVR_Id2->FormatLenth);
                    memcpy(Dest+i*pVR_Id2->FormatLenth,Tmpbuffer,pVR_Id2->FormatLenth);
                    TmpLenth=pVR_Id2->FormatLenth;
                }
                break;
            case VR_TYPE_VXX:
                for(i=0;i<ucNum;i++)
                {
                    memcpy(&ulTmpVA, Dest+i*pVR_Id2->UsedLenth, 4);
                    ulTmpVA=ulTmpVA>>4;
                    ulTmpVA&=0x0000FFFF;
                    memcpy(Tmpbuffer,&ulTmpVA,pVR_Id2->FormatLenth);
                    memcpy(Dest+i*pVR_Id2->FormatLenth,Tmpbuffer,pVR_Id2->FormatLenth);
                    TmpLenth=pVR_Id2->FormatLenth;
                }
                break;
          
            case VR_TYPE_CUL:
            case VR_TYPE_IXX:
                for(i=0;i<ucNum;i++)
                {
                    memcpy(&ulTmpVA,Dest+i*pVR_Id2->UsedLenth,4);
                    ulTmpVA=ulTmpVA>>4;
                    ulTmpVA&=0x00FFFFFF;
                    memcpy(Tmpbuffer,&ulTmpVA,pVR_Id2->FormatLenth);
                    memcpy(Dest+i*pVR_Id2->FormatLenth,Tmpbuffer,pVR_Id2->FormatLenth);
                    TmpLenth=pVR_Id2->FormatLenth;
                }
                break;

            default:
                for(i=0;i<ucNum;i++)
                {
                    TmpLenth=pVR_Id2->UsedLenth-pVR_Id2->FormatLenth;
                    memcpy(Tmpbuffer,Dest+TmpLenth+i*pVR_Id2->UsedLenth,pVR_Id2->FormatLenth);
                    memcpy(Dest+i*pVR_Id2->FormatLenth,Tmpbuffer,pVR_Id2->FormatLenth);
                }
                TmpLenth=pVR_Id2->FormatLenth;
                break;
        }
    }
    return (ucNum*TmpLenth);
}

#endif

