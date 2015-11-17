//============================================================================
//  File Name: Dlt645_07.C
//
//  Copyright PAX Hangzhou 2011.  All rights reserved.
//
//  Description:
//      DLT-645 07��Լ����
//      ��Լ����Ҫ�������ھ���ϵͳ����ƣ������ֳ�����СENDIAN
//  Author:
//      ���ι�
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

//������λ��Ϣ
const u8 ConWeekDayWordTable[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x00};

/*********************************************************************
������isIDNew
���ܣ�����ID�ж��Ƿ����ڱ��ļ������ķ�Χ
������
        u32 ID:           DLT645 ID( (((ID3*256+ID2)*256)+ID1)*256+ID0 )
        Ŀǰֻ֧�ֵ����������������Ľ���
Input:
Output:
���أ�  0:�Ǳ��ļ�����       
        1:���ļ�����
��Χ��
ע�ͣ��ޡ�
********************************************************************/
u8 isIDNew(u32 ID)
{
    if(DLT_ID3(ID) > 2)
    {
        return 0;
    }
    return 1;
}

////���ж������ݵĴ������ݱ�
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
            DLT645-07 �������ݿ�ʼ
******************************************************************************************/
//��������  
//enum
//{
#define    EC_TYPE_YG   0//,     //�й�
#define    EC_TYPE_WG   1//,     //�޹�
#define    EC_TYPE_SZ   2//,     //����
#define    EC_TYPE_GL   3//,     //����
#define    EC_TYPE_JB   4//,     //�����й�
#define    EC_TYPE_XB   5//,     //г���й�
#define    EC_TYPE_YD   6//,     //�õ�
#define    EC_TYPE_SY   7//,     //ʣ��
#define    EC_TYPE_CN   8//,     //ͭ���й�
#define    EC_TYPE_TE   9//,     //�����й�
//};
//�ֺ���
enum
{
    EC_PH_ALL,      //����
    EC_PH_PHA,      //A��
    EC_PH_PHB,      //B��
    EC_PH_PHC,      //C��
};
//�й������ڵ�������ͣ���һ��ȫ��
enum
{
    EC_YG_ZH_ZH,    //���
    EC_YG_ZH_ZX,    //����
    EC_YG_ZH_FX,    //����
};
//�޹��������
enum
{
    EC_WG_ZH_Z1,    //���1
    EC_WG_ZH_Z2,    //���1
    EC_WG_ZH_GX,    //����
    EC_WG_ZH_RX,    //����
    EC_WG_ZH_X1,    //1����
    EC_WG_ZH_X2,    //2����
    EC_WG_ZH_X3,    //3����
    EC_WG_ZH_X4,    //4����
};
#define PT_OTHER        (-2)
#define PT_UNSUPPORT    (-1)    //ע��:����������еĵ�ַ��������0xff
#define PT_LEFT_ALL     0x53
//���ݲ�����������������
// type:�������� ph:�ֺ��� zh:��Ϸ�ʽ  //ע��ph��zh���ܳ���3λ
#define ECZT(type,ph,zh)    ( ((type)<<5) | ((ph)<<3) | (zh) )
//���ݵ���������������������
#define ECZT_TYPE(v)        (((v)&0xE0)>>5)
//���ݵ��������������ֺ�������
#define ECZT_PH(v)          (((v)&0x18)>>3)
//���ݵ��������������������
#define ECZT_ZH(v)          ((v)&0x07)

typedef u8 ECTYPE_CHAR;  //�����������
typedef struct
{
    ECTYPE_CHAR ectype;  //��������ͣ�����������ͬ���������࣬������������ʾ
    u8 id2;              //ID2 ��ֵ
    u8 ecindex;          //��������(������ֱ�Ӷ��������ֵ�������Ǹ���RAM��ַ�������������)
}EC_ID2_DEF;
#define isTheECIdxUnSupport(idx)        (EC_Id2[idx].ecindex == (u8)PT_UNSUPPORT)
#define isTheMDIdxUnSupport(idx)        (MD_Id2[idx].ecindex == (u8)PT_UNSUPPORT)
#define isTheVRIdxUnSupport(idx)        (VR_Id2[idx].Addr== (u16)PT_UNSUPPORT)
#define isTheVROTHIdxUnSupport(idx)     (VR_OTH_Id0[idx].Addr== (u16)PT_UNSUPPORT)
//#pragma diag_remark=Pa089
//���е�����ع�Լ��Ϣ�б�
#define EC_ZT(type,ph,zh,id,pti)        (ECZT(type,ph,zh)), (id), (pti)
const EC_ID2_DEF EC_Id2[]=
{
//������������:
    //����������
    //�ֺ���
    //�������
    //ID2
    //��������
   {EC_ZT(EC_TYPE_YG, EC_PH_ALL, EC_YG_ZH_ZH, 0x00, PT_KWH_C_ALL)},     /*00: ����й�*/
   {EC_ZT(EC_TYPE_YG, EC_PH_ALL, EC_YG_ZH_ZX, 0x01, PT_KWH_F_ALL)},     /*01: �����й�*/
   {EC_ZT(EC_TYPE_YG, EC_PH_ALL, EC_YG_ZH_FX, 0x02, PT_KWH_R_ALL)},     /*02: �����й�*/
   {EC_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_Z1, 0x03, PT_KVARH_C1_ALL)},  /*03: ����޹�1*/
   {EC_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_Z2, 0x04, PT_KVARH_C2_ALL)},  /*04: ����޹�2*/
   {EC_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_X1, 0x05, PT_KVARH_Q1_ALL)},  /*05: 1�����޹�*/
   {EC_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_X2, 0x06, PT_KVARH_Q2_ALL)},  /*06: 2�����޹�*/
   {EC_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_X3, 0x07, PT_KVARH_Q3_ALL)},  /*07: 3�����޹�*/
   {EC_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_X4, 0x08, PT_KVARH_Q4_ALL)},  /*08: 4�����޹�*/
#if 1     
    {EC_ZT(EC_TYPE_SZ, EC_PH_ALL, EC_YG_ZH_ZX, 0x09, PT_KVAH_F_ALL)},     /*09: ��������*/
    {EC_ZT(EC_TYPE_SZ, EC_PH_ALL, EC_YG_ZH_FX, 0x0A, PT_KVAH_R_ALL)},     /*0A: ��������*/
#endif    
    {EC_ZT(EC_TYPE_YD, EC_PH_ALL, EC_YG_ZH_ZH, 0x0B, PT_KWH_USE_ALL)},   /*0B: �õ���*/
    
    {EC_ZT(EC_TYPE_YG, EC_PH_PHA, EC_YG_ZH_ZX, 0x15, PT_KWH_A_F_ALL)},   /*15: A�����й�*/
    {EC_ZT(EC_TYPE_YG, EC_PH_PHA, EC_YG_ZH_FX, 0x16, PT_KWH_A_R_ALL)},   /*16: A�����й�*/
#if 1     
    {EC_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_Z1, 0x17, PT_KVARH_A_C1_ALL)},     /*17: A����޹�1*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_Z2, 0x18, PT_KVARH_A_C2_ALL)},     /*18: A����޹�2*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_X1, 0x19, PT_KVARH_A_Q1_ALL)},     /*19: A1�����޹�*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_X2, 0x1A, PT_KVARH_A_Q2_ALL)},     /*1A: A2�����޹�*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_X3, 0x1B, PT_KVARH_A_Q3_ALL)},     /*1B: A3�����޹�*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_X4, 0x1C, PT_KVARH_A_Q4_ALL)},     /*1C: A4�����޹�*/
    {EC_ZT(EC_TYPE_SZ, EC_PH_PHA, EC_YG_ZH_ZX, 0x1D, PT_KVAH_A_F_ALL)},     /*1D: A��������*/
    {EC_ZT(EC_TYPE_SZ, EC_PH_PHA, EC_YG_ZH_FX, 0x1E, PT_KVAH_A_R_ALL)},     /*1E: A��������*/
#endif    
    {EC_ZT(EC_TYPE_YG, EC_PH_PHB, EC_YG_ZH_ZX, 0x29, PT_KWH_B_F_ALL)},   /*29: B�����й�*/
    {EC_ZT(EC_TYPE_YG, EC_PH_PHB, EC_YG_ZH_FX, 0x2A, PT_KWH_B_R_ALL)},   /*2A: B�����й�*/
#if 1    
    {EC_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_Z1, 0x2B, PT_KVARH_B_C1_ALL)},     /*2B: B����޹�1*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_Z2, 0x2C, PT_KVARH_B_C2_ALL)},     /*2C: B����޹�2*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_X1, 0x2D, PT_KVARH_B_Q1_ALL)},     /*2D: B1�����޹�*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_X2, 0x2E, PT_KVARH_B_Q2_ALL)},     /*2E: B2�����޹�*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_X3, 0x2F, PT_KVARH_B_Q3_ALL)},     /*2F: B3�����޹�*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_X4, 0x30, PT_KVARH_B_Q4_ALL)},     /*30: B4�����޹�*/
    {EC_ZT(EC_TYPE_SZ, EC_PH_PHB, EC_YG_ZH_ZX, 0x31, PT_KVAH_B_F_ALL)},       /*31: B��������*/
    {EC_ZT(EC_TYPE_SZ, EC_PH_PHB, EC_YG_ZH_FX, 0x32, PT_KVAH_B_R_ALL)},       /*32: B��������*/
#endif    
    {EC_ZT(EC_TYPE_YG, EC_PH_PHC, EC_YG_ZH_ZX, 0x3D, PT_KWH_C_F_ALL)},   /*3D: C�����й�*/
    {EC_ZT(EC_TYPE_YG, EC_PH_PHC, EC_YG_ZH_FX, 0x3E, PT_KWH_C_R_ALL)},   /*3E: C�����й�*/
#if 1    
    {EC_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_Z1, 0x3F, PT_KVARH_C_C1_ALL)},     /*3F: C����޹�1*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_Z2, 0x40, PT_KVARH_C_C2_ALL)},     /*40: C����޹�2*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_X1, 0x41, PT_KVARH_C_Q1_ALL)},     /*41: C1�����޹�*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_X2, 0x42, PT_KVARH_C_Q2_ALL)},     /*42: C2�����޹�*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_X3, 0x43, PT_KVARH_C_Q3_ALL)},     /*43: C3�����޹�*/
    {EC_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_X4, 0x44, PT_KVARH_C_Q4_ALL)},     /*44: C4�����޹�*/
    {EC_ZT(EC_TYPE_SZ, EC_PH_PHC, EC_YG_ZH_ZX, 0x45, PT_KVAH_C_F_ALL)},       /*45: C��������*/
    {EC_ZT(EC_TYPE_SZ, EC_PH_PHC, EC_YG_ZH_FX, 0x46, PT_KVAH_C_R_ALL)},       /*46: C��������*/
#endif    
#if 0    
    {EC_ZT(EC_TYPE_GL, EC_PH_ALL, EC_YG_ZH_ZH, 0x80, PT_UNSUPPORT)},     /*80: �ܹ�������*/
    {EC_ZT(EC_TYPE_JB, EC_PH_ALL, EC_YG_ZH_ZX, 0x81, PT_UNSUPPORT)},     /*81: �ܻ��������й�*/
    {EC_ZT(EC_TYPE_JB, EC_PH_ALL, EC_YG_ZH_FX, 0x82, PT_UNSUPPORT)},     /*82: �ܻ��������й�*/
    {EC_ZT(EC_TYPE_XB, EC_PH_ALL, EC_YG_ZH_ZX, 0x83, PT_UNSUPPORT)},     /*83: ��г�������й�*/
    {EC_ZT(EC_TYPE_XB, EC_PH_ALL, EC_YG_ZH_FX, 0x84, PT_UNSUPPORT)},     /*84: ��г�������й�*/
    {EC_ZT(EC_TYPE_CN, EC_PH_ALL, EC_YG_ZH_ZH, 0x85, PT_UNSUPPORT)},     /*85: ��ͭ���й�*/
    {EC_ZT(EC_TYPE_TE, EC_PH_ALL, EC_YG_ZH_ZH, 0x86, PT_UNSUPPORT)},     /*86: �������й�*/
#endif    
    {EC_ZT(EC_TYPE_SY, EC_PH_ALL, EC_YG_ZH_ZH, 0x90, PT_LEFT_ALL)},      /*90: ʣ��*/
#if 0    
    {EC_ZT(EC_TYPE_GL, EC_PH_PHA, EC_YG_ZH_ZH, 0x94, PT_UNSUPPORT)},     /*94: A��������*/
    {EC_ZT(EC_TYPE_JB, EC_PH_PHA, EC_YG_ZH_ZX, 0x95, PT_UNSUPPORT)},     /*95: A���������й�*/
    {EC_ZT(EC_TYPE_JB, EC_PH_PHA, EC_YG_ZH_FX, 0x96, PT_UNSUPPORT)},     /*96: A���������й�*/
    {EC_ZT(EC_TYPE_XB, EC_PH_PHA, EC_YG_ZH_ZX, 0x97, PT_UNSUPPORT)},     /*97: Aг�������й�*/
    {EC_ZT(EC_TYPE_XB, EC_PH_PHA, EC_YG_ZH_FX, 0x98, PT_UNSUPPORT)},     /*98: Aг�������й�*/
    {EC_ZT(EC_TYPE_CN, EC_PH_PHA, EC_YG_ZH_ZH, 0x99, PT_UNSUPPORT)},     /*99: Aͭ���й�*/
    {EC_ZT(EC_TYPE_TE, EC_PH_PHA, EC_YG_ZH_ZH, 0x9A, PT_UNSUPPORT)},     /*9A: A�����й�*/
    {EC_ZT(EC_TYPE_GL, EC_PH_PHB, EC_YG_ZH_ZH, 0xA8, PT_UNSUPPORT)},     /*A8: B��������*/
    {EC_ZT(EC_TYPE_JB, EC_PH_PHB, EC_YG_ZH_ZX, 0xA9, PT_UNSUPPORT)},     /*A9: B���������й�*/
    {EC_ZT(EC_TYPE_JB, EC_PH_PHB, EC_YG_ZH_FX, 0xAA, PT_UNSUPPORT)},     /*AA: B���������й�*/
    {EC_ZT(EC_TYPE_XB, EC_PH_PHB, EC_YG_ZH_ZX, 0xAB, PT_UNSUPPORT)},     /*AB: Bг�������й�*/
    {EC_ZT(EC_TYPE_XB, EC_PH_PHB, EC_YG_ZH_FX, 0xAC, PT_UNSUPPORT)},     /*AC: Bг�������й�*/
    {EC_ZT(EC_TYPE_CN, EC_PH_PHB, EC_YG_ZH_ZH, 0xAD, PT_UNSUPPORT)},     /*AD: Bͭ���й�*/
    {EC_ZT(EC_TYPE_TE, EC_PH_PHB, EC_YG_ZH_ZH, 0xAE, PT_UNSUPPORT)},     /*AE: B�����й�*/
    {EC_ZT(EC_TYPE_GL, EC_PH_PHC, EC_YG_ZH_ZH, 0xBC, PT_UNSUPPORT)},     /*BC: C��������*/
    {EC_ZT(EC_TYPE_JB, EC_PH_PHC, EC_YG_ZH_ZX, 0xBD, PT_UNSUPPORT)},     /*BD: C���������й�*/
    {EC_ZT(EC_TYPE_JB, EC_PH_PHC, EC_YG_ZH_FX, 0xBE, PT_UNSUPPORT)},     /*BE: C���������й�*/
    {EC_ZT(EC_TYPE_XB, EC_PH_PHC, EC_YG_ZH_ZX, 0xBF, PT_UNSUPPORT)},     /*BF: Cг�������й�*/
    {EC_ZT(EC_TYPE_XB, EC_PH_PHC, EC_YG_ZH_FX, 0xC0, PT_UNSUPPORT)},     /*C0: Cг�������й�*/
    {EC_ZT(EC_TYPE_CN, EC_PH_PHC, EC_YG_ZH_ZH, 0xC1, PT_UNSUPPORT)},     /*C1: Cͭ���й�*/
    {EC_ZT(EC_TYPE_TE, EC_PH_PHC, EC_YG_ZH_ZH, 0xC2, PT_UNSUPPORT)},     /*C2: C�����й�*/
#endif    
};
//#pragma diag_default=Pa089
#define EC_Id2_TABLE_LEN    (sizeof(EC_Id2)/sizeof(EC_ID2_DEF))

/*********************************************************************
������ECId2IdxFind
���ܣ�����DLT645 ID�ҳ�����Ϣ���������������ж�����ȷ���(�����Ƿ�֧��)
������
        u32 ID:           DLT645 ID( (((ID3*256+ID2)*256)+ID1)*256+ID0 )
Input:
Output:
���أ�  DLT_RET_ERR:    ID�����֧��    
        ����:           ��ȷ������
��Χ��
ע�ͣ��ޡ�
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
    if(ID2==0x90)    ///��������
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
        //ʣ�������ID1ֻ����1��2
        if( (ID1 < 1) || (ID1 > 2) )
            return DLT_RET_ERR;
    }
    else
    {
        if((ID1 > TFeeNum) && (ID1 != 0xFF))
            return DLT_RET_ERR;
        //����ô���û�з�����,��ID1ȴ�и��������
        if(ID1 > 0) //�޷�������£�0xFFҲ������
            if(ECZT_PH(EC_Id2[idx].ectype) != EC_PH_ALL) 
                return DLT_RET_ERR;     //��������޷���
    }
    
    return idx;
}
/*********************************************************************
������SymbolGetECData
���ܣ�����DLT645 ID�����Ҫ��ʾ��ͼ��
������
Input:
Output:
���أ�  DLT_RET_SUCC:   ���ɹ�        
        DLT_RET_ERR:    ʧ��
��Χ��
ע�ͣ��ޡ�
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
������GetECDataByID
���ܣ�����DLT645 ID��ȡ��������
������
        u8 *pData:       ����buf��������Ŷ��ص�����
        u16 *ucLen:        �������ݳ���
        u32 ID:           DLT645 ID( (((ID3*256+ID2)*256)+ID1)*256+ID0 )
        u16 ulBufLen:      �����Ǹ���buf�ĳ���
Input:
Output:
���أ�  0:���ɹ�        
        1:��ʧ��
��Χ��
ע�ͣ��ޡ�
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
     
    if(ID2==0x90)    ///��������
    {
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
#if(CONFIG_METER_STEP_PERIODPRICE_MODE==CONFIG_METER_STEP_PERIODPRICE_MODE_ENABLE)
        if(ulBufLen < 4) return DLT_RET_ERR;
        if(ID==0x00900200)
        {
            if(0!=JudgeRemainSign(0, pData))
            // aa �������ʣ����� aa
            {
                memset(pData, 0x00, 4);
            }
            *ucLen = 4;
        }
        else if(ID==0x00900201)
        {
            
            if(0==JudgeRemainSign(0, pData))
            // aa �������ʣ����� aa
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
    else if(ID2 == 0x0B)   //������������й��ۼ��õ���
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
                if(ID0==0)///��ǰ
                {
                    ECAddr = RAM_KWH_ALL_START;
                }
                else //��ʷ
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
            if(ID0==0)///��ǰ
            {
                ECAddr = RAM_KWH_ALL_START;
            }
            else //��ʷ
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
                    ///�������֡������BUFFER��
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
            DLT645-07 �������ݿ�ʼ
******************************************************************************************/
//���������洢��ַת������������
#define MD_RAM_TO_IDX(ram)          ((u8)(((ram)-RAM_DEMAND_DATA_START)/BYTES_PER_DEMAND))
//������������ת���������洢�ĵ�ַ��ƫ����
#define MD_IDX_TO_OFFSET(idx)       ((u32)((idx)*BYTES_PER_DEMAND))
//������������ת���������洢�ĵ�ַ
#define MD_IDX_TO_RAM(idx)          ((u32)(RAM_DEMAND_DATA_START+MD_IDX_TO_OFFSET(idx)))
#define MD_ZT(type,ph,zh,id2,addr)  (ECZT(type,ph,zh)), (id2), MD_RAM_TO_IDX(addr)

//#pragma diag_remark=Pa089
const EC_ID2_DEF MD_Id2[]=
{
//������������:
    //����������
    //�ֺ���
    //�������
    //ID2
    //������ַ(Ϊ�˼�������ռ䣬��ַ����ת��Ϊ����)
    {MD_ZT(EC_TYPE_YG, EC_PH_ALL, EC_YG_ZH_ZX, 0x01, RAM_KW_F_ALL_DATA)},     /*01: �����й�*/
    {MD_ZT(EC_TYPE_YG, EC_PH_ALL, EC_YG_ZH_FX, 0x02, RAM_KW_R_ALL_DATA)},     /*02: �����й�*/
#if 1     
    {MD_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_Z1, 0x03, RAM_KVAR_C1_ALL_DATA)},  /*03: ����޹�1*/
    {MD_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_Z2, 0x04, RAM_KVAR_C2_ALL_DATA)},  /*04: ����޹�2*/
#endif    
    {MD_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_X1, 0x05, RAM_KVAR_Q1_ALL_DATA)},  /*05: 1�����޹�*/
    {MD_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_X2, 0x06, RAM_KVAR_Q2_ALL_DATA)},  /*06: 2�����޹�*/
    {MD_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_X3, 0x07, RAM_KVAR_Q3_ALL_DATA)},  /*07: 3�����޹�*/
    {MD_ZT(EC_TYPE_WG, EC_PH_ALL, EC_WG_ZH_X4, 0x08, RAM_KVAR_Q4_ALL_DATA)},  /*08: 4�����޹�*/
#if 1     
    {MD_ZT(EC_TYPE_SZ, EC_PH_ALL, EC_YG_ZH_ZX, 0x09, RAM_KVA_F_ALL_DATA)},     /*09: ��������*/
    {MD_ZT(EC_TYPE_SZ, EC_PH_ALL, EC_YG_ZH_FX, 0x0A, RAM_KVA_R_ALL_DATA)},     /*0A: ��������*/
    {MD_ZT(EC_TYPE_YG, EC_PH_PHA, EC_YG_ZH_ZX, 0x15, RAM_KW_A_F_ALL_DATA)},    /*15: A�����й�*/
    {MD_ZT(EC_TYPE_YG, EC_PH_PHA, EC_YG_ZH_FX, 0x16, RAM_KW_A_R_ALL_DATA)},    /*16: A�����й�*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_Z1, 0x17, RAM_KVAR_A_C1_ALL_DATA)},     /*17: A����޹�1*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_Z2, 0x18, RAM_KVAR_A_C2_ALL_DATA)},     /*18: A����޹�2*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_X1, 0x19, RAM_KVAR_A_Q1_ALL_DATA)},     /*19: A1�����޹�*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_X2, 0x1A, RAM_KVAR_A_Q2_ALL_DATA)},     /*1A: A2�����޹�*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_X3, 0x1B, RAM_KVAR_A_Q3_ALL_DATA)},     /*1B: A3�����޹�*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHA, EC_WG_ZH_X4, 0x1C, RAM_KVAR_A_Q4_ALL_DATA)},     /*1C: A4�����޹�*/
    {MD_ZT(EC_TYPE_SZ, EC_PH_PHA, EC_YG_ZH_ZX, 0x1D, RAM_KVA_A_F_ALL_DATA)},     /*1D: A��������*/
    {MD_ZT(EC_TYPE_SZ, EC_PH_PHA, EC_YG_ZH_FX, 0x1E, RAM_KVA_A_R_ALL_DATA)},     /*1E: A��������*/
    {MD_ZT(EC_TYPE_YG, EC_PH_PHB, EC_YG_ZH_ZX, 0x29, RAM_KW_B_F_ALL_DATA)},      /*29: B�����й�*/
    {MD_ZT(EC_TYPE_YG, EC_PH_PHB, EC_YG_ZH_FX, 0x2A, RAM_KW_B_R_ALL_DATA)},      /*2A: B�����й�*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_Z1, 0x2B, RAM_KVAR_B_C1_ALL_DATA)},     /*2B: B����޹�1*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_Z2, 0x2C, RAM_KVAR_B_C2_ALL_DATA)},     /*2C: B����޹�2*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_X1, 0x2D, RAM_KVAR_B_Q1_ALL_DATA)},     /*2D: B1�����޹�*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_X2, 0x2E, RAM_KVAR_B_Q2_ALL_DATA)},     /*2E: B2�����޹�*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_X3, 0x2F, RAM_KVAR_B_Q3_ALL_DATA)},     /*2F: B3�����޹�*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHB, EC_WG_ZH_X4, 0x30, RAM_KVAR_B_Q4_ALL_DATA)},     /*30: B4�����޹�*/
    {MD_ZT(EC_TYPE_SZ, EC_PH_PHB, EC_YG_ZH_ZX, 0x31, RAM_KVA_B_F_ALL_DATA)},       /*31: B��������*/
    {MD_ZT(EC_TYPE_SZ, EC_PH_PHB, EC_YG_ZH_FX, 0x32, RAM_KVA_B_R_ALL_DATA)},       /*32: B��������*/
    {MD_ZT(EC_TYPE_YG, EC_PH_PHC, EC_YG_ZH_ZX, 0x3D, RAM_KW_C_F_ALL_DATA)},      /*3D: C�����й�*/
    {MD_ZT(EC_TYPE_YG, EC_PH_PHC, EC_YG_ZH_FX, 0x3E, RAM_KW_C_R_ALL_DATA)},      /*3E: C�����й�*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_Z1, 0x3F, RAM_KVAR_C_C1_ALL_DATA)},     /*3F: C����޹�1*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_Z2, 0x40, RAM_KVAR_C_C2_ALL_DATA)},     /*40: C����޹�2*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_X1, 0x41, RAM_KVAR_C_Q1_ALL_DATA)},     /*41: C1�����޹�*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_X2, 0x42, RAM_KVAR_C_Q2_ALL_DATA)},     /*42: C2�����޹�*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_X3, 0x43, RAM_KVAR_C_Q3_ALL_DATA)},     /*43: C3�����޹�*/
    {MD_ZT(EC_TYPE_WG, EC_PH_PHC, EC_WG_ZH_X4, 0x44, RAM_KVAR_C_Q4_ALL_DATA)},     /*44: C4�����޹�*/
    {MD_ZT(EC_TYPE_SZ, EC_PH_PHC, EC_YG_ZH_ZX, 0x45, RAM_KVA_C_F_ALL_DATA)},       /*45: C��������*/
    {MD_ZT(EC_TYPE_SZ, EC_PH_PHC, EC_YG_ZH_FX, 0x46, RAM_KVA_C_R_ALL_DATA)},       /*46: C��������*/
#endif    
};
//#pragma diag_default=Pa089
#define MD_Id2_TABLE_LEN    (sizeof(MD_Id2)/sizeof(EC_ID2_DEF))

/*********************************************************************
������MDId2IdxFind
���ܣ�����DLT645 ID�ҳ�����Ϣ���������������ж�����ȷ���(�����Ƿ�֧��)
������
        u32 ID:           DLT645 ID( (((ID3*256+ID2)*256)+ID1)*256+ID0 )
Input:
Output:
���أ�  DLT_RET_ERR:    ID�����֧��    
        ����:           ��ȷ������
��Χ��
ע�ͣ��ޡ�
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
    //����ô���û�з�����,��ID1ȴ�и��������
    if(ID1 > 0) //�޷�������£�0xFFҲ������
        if(ECZT_PH(MD_Id2[idx].ectype) != EC_PH_ALL) 
                return DLT_RET_ERR;
    
    return idx;
}
/*********************************************************************
������SymbolGetMDData
���ܣ�����DLT645 ID�����Ҫ��ʾ��ͼ��
������
Input:
Output:
���أ�  DLT_RET_SUCC:   ���ɹ�        
        DLT_RET_ERR:    ʧ��
��Χ��
ע�ͣ��ޡ�
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
������GetMDDataByID
���ܣ�����DLT645 ID��ȡ��������
������
        u8 *pData:       ����buf��������Ŷ��ص�����
        u16 *ucLen:        �������ݳ���
        u32 ID:           DLT645 ID( (((ID3*256+ID2)*256)+ID1)*256+ID0 )
        u16 ulBufLen:      �����Ǹ���buf�ĳ���
Input:
Output:
���أ�  0:���ɹ�        
        1:��ʧ��
��Χ��
ע�ͣ��ޡ�
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
                if(ID0==0)///��ǰ
                {
                    ECAddr = RAM_DEMAND_DATA_START;
                }
                else //��ʷ
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
            if(ID0==0)///��ǰ
            {
                ECAddr = RAM_DEMAND_DATA_START;
            }
            else //��ʷ
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
                    ///�������֡������BUFFER��
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
            DLT645-07 �������ݿ�ʼ
******************************************************************************************/
//enum
//{
#define    VR_TYPE_VOL   0x00     //��ѹ
#define    VR_TYPE_CUL   0x01     //����
#define    VR_TYPE_YGL   0x02     //�й�����
#define    VR_TYPE_WGL   0x03     //�޹�����
#define    VR_TYPE_SZL   0x04     //���ڹ���
#define    VR_TYPE_GLY   0x05     //��������
#define    VR_TYPE_XJX   0x06     //���-ͬ���ѹ�͵���
#define    VR_TYPE_VSZ   0x07     //��ѹʧ���
#define    VR_TYPE_ISZ   0x08     //����ʧ���
#define    VR_TYPE_VXH   0x09     //��ѹг��������
#define    VR_TYPE_IXH   0x0A     //����г��������
#define    VR_TYPE_OTH   0x0B     //����
#define    VR_TYPE_VXX   0x0C     //��ѹг����Чֵ
#define    VR_TYPE_IXX   0x0D     //����г����Чֵ
#define    VR_TYPE_XJ1   0x0E     //���-�����ѹ��A���ѹ
#define    VR_TYPE_XJ2   0x0F     //���-���������A���ѹ
#define    VR_TYPE_ILX   0x11     // 3 ���ߵ���
#define    VR_TYPE_WFL   0x12     // 2 ����Ƶ��
#define    VR_TYPE_PER   0x13     // 3 һ�����й���ƽ������
#define    VR_TYPE_XYG   0x14     // 3 ��ǰ�й�����
#define    VR_TYPE_XWG   0x15     // 3 ��ǰ�޹�����
#define    VR_TYPE_XSZ   0x16     // 2 ��ǰ��������
#define    VR_TYPE_CBN   0x17     // 2 �����¶�
#define    VR_TYPE_SZV   0x18     // 2 ʱ�ӵ�ص�ѹ���ڲ���
#define    VR_TYPE_DCV   0x19     // 2 ͣ�糭���ص�ѹ���ⲿ��
#define    VR_TYPE_TTD   0x1A     // 4 �ڲ���ع���ʱ��
#define    VR_TYPE_JTP   0x1B     // 4 ��ǰ���ݵ��
//};
//�ֺ���
enum
{
    VR_PH_ALL,      //����  //ֻ�����ֹ��ʺ͹���������
    VR_PH_PHA,      //A��
    VR_PH_PHB,      //B��
    VR_PH_PHC,      //C��
};
// type:�������� ph:�ֺ��� zh:��Ϸ�ʽ  //ע��x��z���ܳ���3λ
#define VRZT(type)          ( ((type)) )
#define VRZT_TYPE(v)        ( ((v) )

#define VR_ZT(type,id2,ul,fl,id1s,id1w,id1n,addr)    ((addr)&0xFFFF), (VRZT(type)), (id2), (ul), (fl), (id1s),(id1w), (id1n), 0
typedef struct
{
    u16 Addr;               //�洢��ַ
    u8 vrtype;           //��������
    u8 id2;              //Acturally, it is no use buf for aligned
    u8 UsedLenth:4;      //�洢ʹ�õ��ֽڳ���(���Ȳ��ᳬ��15)
    u8 FormatLenth:4;    //��Լ��ʽʹ�õ��ֽڳ���(���Ȳ��ᳬ��15)
    u8 id1Start:1;       //��Լ��ID1��ʼ������
    u8 id1WithFF:1;      //ID1ΪFFҲ���Գ���.0:������,1:����
    u8 id1Num:4;         //�洢������(3:ABC���� 4:��+ABC)
    u8 others:2;         //����
    //u8 id0Start:1;       //��Լ��ID0��ʼ������
    //u8 id0WithFF:1;      //ID0ΪFFҲ���Գ���.0:������,1:����
    //u8 RecordTim;      //��¼�Ĵ���(ID0)00:��������FF����.>0�Ļ�,�Ϳ�����FF����
}VR_ID2_DEF;
//#pragma diag_remark=Pa089

const VR_ID2_DEF VR_Id2[]=
{
//������������:
    //��������
//Acturally, it is no use buf for aligned
//�洢ʹ�õ��ֽڳ���(���Ȳ��ᳬ��15)
//��Լ��ʽʹ�õ��ֽڳ���(���Ȳ��ᳬ��15)
//��Լ��ID1��ʼ������
//ID1ΪFFҲ���Գ���.0:������,1:����
//�洢������(3:ABC���� 4:��+ABC)
//�洢��ַ
    {VR_ZT(VR_TYPE_VOL, 0x01, 4, 2, 1, 1, 3, RAM_CURRENT_V_A        )},  /*01: ��ѹ*/
    {VR_ZT(VR_TYPE_CUL, 0x02, 4, 3, 1, 1, 3, RAM_CURRENT_I_A        )},  /*02: ����*/
    {VR_ZT(VR_TYPE_YGL, 0x03, 4, 3, 0, 1, 4, RAM_CURRENT_KW_ALL     )},  /*03: �й�����*/
    {VR_ZT(VR_TYPE_WGL, 0x04, 4, 3, 0, 1, 4, RAM_CURRENT_KVAR_ALL   )},  /*04: �޹�����*/
    {VR_ZT(VR_TYPE_SZL, 0x05, 4, 3, 0, 1, 4, RAM_CURRENT_KVA_ALL    )},  /*05: ���ڹ���*/
    {VR_ZT(VR_TYPE_GLY, 0x06, 4, 2, 0, 1, 4, RAM_CURRENT_FACTOR_ALL )},  /*06: ��������*/
    {VR_ZT(VR_TYPE_XJX, 0x07, 2, 2, 1, 1, 3, RAM_CURRENT_ANGLE_AV_AI)},  /*07: ���-ͬ���ѹ�͵���*/
#if(CONFIG_METER_HARMONIC_ENABLE == GAL_YES)    
    {VR_ZT(VR_TYPE_VSZ, 0x08, 2, 2, 1, 1, 3, RAM_CURRENT_HARMONIC_PER_V_A_ALL      )},  /*08: ��ѹʧ���*/
    {VR_ZT(VR_TYPE_ISZ, 0x09, 2, 2, 1, 1, 3, RAM_CURRENT_HARMONIC_PER_I_A_ALL      )},  /*09: ����ʧ���*/
    {VR_ZT(VR_TYPE_VXH, 0x0A, 2, 2, 1, 0, 0, RAM_CURRENT_HARMONIC_PER_V_A_01CI     )},  /*0A: ��ѹг��������*/
    {VR_ZT(VR_TYPE_IXH, 0x0B, 2, 2, 1, 0, 0, RAM_CURRENT_HARMONIC_PER_I_A_01CI     )},  /*0B: ����г��������*/
    {VR_ZT(VR_TYPE_VXX, 0x0C, 4, 2, 1, 1, 0, RAM_CURRENT_HARMONIC_V_A_ALL          )},  /*0B: ��ѹг����Чֵ*/
    {VR_ZT(VR_TYPE_IXX, 0x0D, 4, 3, 1, 1, 0, RAM_CURRENT_HARMONIC_I_A_ALL          )},  /*0B: ����г����Чֵ*/
#endif    
    {VR_ZT(VR_TYPE_XJ1, 0xF1, 2, 2, 1, 1, 3, RAM_CURRENT_ANGLE_AV_AV)},  /*07: ���-�����ѹ��A���ѹ*/
    {VR_ZT(VR_TYPE_XJ2, 0xF2, 2, 2, 1, 1, 3, RAM_CURRENT_ANGLE_AI_AV)},  /*07: ���-���������A���ѹ*/
    {VR_ZT(VR_TYPE_OTH, 0x80, 0, 0, 0, 0, 0, PT_OTHER               )},  /*80: ����*/
};
#define VR_ID2_TABLE_LEN    (sizeof(VR_Id2)/sizeof(VR_ID2_DEF))
////�������е�������0x80,���ڳ��Ȳ��ᳬ��15���Գ����ð��ֽ�����ʾ
typedef struct
{
    u32 Addr;            //�����洢��ַ
    u8 vrtype;           //��������
    u8 datatype;         //������������
    u8 id0;              //DI0
    //u8 Used:1;         //�Ƿ�ʹ��0:û��,1,ʹ��
    u8 FormatLenth:4;    //��Լʹ�õĳ���
    u8 UsedLenth:4;      //�洢ʹ�õĳ���
}STR_VAR_ESPECEIVE;
#define VR_ESP(type, id0, ud, fl, ul, dtype, addr)     (addr), (type), (dtype), (id0), (fl), (ul)
///������0x80��Щ�Ƚ������
const STR_VAR_ESPECEIVE VR_OTH_Id0[]=
{
//������������:
    //��������
    //ID0
    //�ñ����Ƿ�ʹ��(Ŀǰ������δ���ã����ɸ��ݵ�ַ�ж�)
    //��Լ��ʽʹ�õ��ֽڳ���(���Ȳ��ᳬ��15)
    //�洢ʹ�õĳ���
    //������������
    //�洢��ַ
    {VR_ESP(VR_TYPE_ILX, 0x01, 1, 3, 4, DATA_TYPE_CURRENT,   RAM_CURRENT_I_NULLSEQU       )},  /*01: ���ߵ���*/
    {VR_ESP(VR_TYPE_WFL, 0x02, 1, 2, 6, DATA_TYPE_BCD5_8,    RAM_CURRENT_FREQ_A           )},  /*02: ����Ƶ��*/
    {VR_ESP(VR_TYPE_PER, 0x03, 1, 3, 4, DATA_TYPE_XL_signed, RAM_AVERAGE_KW_ALL           )},  /*03: һ�����й���ƽ������*/
    {VR_ESP(VR_TYPE_XYG, 0x04, 1, 3, 4, DATA_TYPE_XL_signed, RAM_CURRENT_DEMAND_KW_TOTAL  )},  /*04: ��ǰ�й�����*/
    {VR_ESP(VR_TYPE_XWG, 0x05, 1, 3, 4, DATA_TYPE_XL_signed, RAM_CURRENT_DEMAND_KVAR_TOTAL)},  /*05: ��ǰ�޹�����*/
    {VR_ESP(VR_TYPE_XSZ, 0x06, 1, 3, 4, DATA_TYPE_XL_signed, RAM_CURRENT_DEMAND_KVA_TOTAL )},  /*06: ��ǰ��������*/
    {VR_ESP(VR_TYPE_CBN, 0x07, 1, 2, 2, DATA_TYPE_WENDU,     RAM_CURRENT_METER_TEMP       )},  /*07: �����¶�*/
    {VR_ESP(VR_TYPE_SZV, 0x08, 1, 2, 2, DATA_TYPE_BCD5_8,    RAM_CURRENT_CLOCK_VOLTAGE    )},  /*08: ʱ�ӵ�ص�ѹ���ڲ���*/
    {VR_ESP(VR_TYPE_DCV, 0x09, 1, 2, 2, DATA_TYPE_BCD5_8,    RAM_CURRENT_WAKEUP_VOLTAGE   )},  /*09: ͣ�糭���ص�ѹ���ⲿ��*/
    {VR_ESP(VR_TYPE_TTD, 0x0A, 1, 4, 4, DATA_TYPE_BCD1_8,    EPL_CURRENT_BAT_USETIME      )},  /*0A: �ڲ���ع���ʱ��*/
#if(CONFIG_METER_STEP_PERIODPRICE_MODE==CONFIG_METER_STEP_PERIODPRICE_MODE_ENABLE)
    {VR_ESP(VR_TYPE_JTP, 0x0B, 1, 4, 4, DATA_TYPE_BCD1_8,    RAM_CURRENT_STEPPRICE_PRICE  )},  /*0B: ��ǰ���ݵ��*/
#else
    {VR_ESP(VR_TYPE_JTP, 0x0B, 1, 4, 4, DATA_TYPE_BCD1_8,    PT_UNSUPPORT                 )},  /*0B: ��ǰ���ݵ��*/
#endif
};
#define VR_OTH_Id0_TABLE_LEN    (sizeof(VR_OTH_Id0)/sizeof(STR_VAR_ESPECEIVE))

//#pragma diag_default=Pa089

/*********************************************************************
������VRId2IdxFind
���ܣ�����DLT645 ID�ҳ�����Ϣ���������������ж�����ȷ���(�����Ƿ�֧��)
������
        u32 ID:           DLT645 ID( (((ID3*256+ID2)*256)+ID1)*256+ID0 )
Input:
Output:
���أ�  DLT_RET_ERR:    ID�����֧��    
        ����:           ��ȷ������
��Χ��
ע�ͣ��ޡ�
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
������SymbolGetMDData
���ܣ�����DLT645 ID�����Ҫ��ʾ��ͼ��
������
Input:
Output:
���أ�  DLT_RET_SUCC:   ���ɹ�        
        DLT_RET_ERR:    ʧ��
��Χ��
ע�ͣ��ޡ�
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
������GetVRDataByID
���ܣ�����DLT645 ID��ȡ��������
������
        u8 *pData:       ����buf��������Ŷ��ص�����
        u16 *ucLen:        �������ݳ���
        u32 ID:           DLT645 ID( (((ID3*256+ID2)*256)+ID1)*256+ID0 )
        u16 ulBufLen:      �����Ǹ���buf�ĳ���
Input:
Output:
���أ�  0:���ɹ�        
        1:��ʧ��
��Χ��
ע�ͣ��ޡ�
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
        	return DLT_RET_ERR;//ID0 == 0��֧��
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
            //������������г����Чֵ
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
                tmplen = VR_Id2[idx].UsedLenth * (GetSetHarmonicNumber()+1);  //����г������
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
������VariableParaToFormat
���ܣ�����ת��Ϊ��Լ��ʽ��(ע��,�洢�ĸ�ʽ����Ҫ�ȹ�Լ���ֽ�����,���Ҷ���Ҫȥ���洢�ĵ�λ)
������

Input:
Output:
���أ�  �ֽ���       
��Χ��
ע�ͣ��ޡ�
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
        //�洢�ĸ�ʽ���Լת��
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

