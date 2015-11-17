/***************************************************************************
 *
 * COPYRIGHT (C) 2009 PaxHZ, ALL RIGHTS RESERVED
 * #Abstract: ��Ӳ���汾����
 * 
 ***************************************************************************/
#ifndef PAX_VER_H
#define PAX_VER_H

//=============================   �ն�����ѡ��  ================================
//��ѡ��������ר��Ͷ�Ӧ�ĵ����꿪�ţ�ע����������
//��������ӵط��汾��Ϣʱע���Ƿ�����ɣ����򿪷���Ӧ��CON_TER_TYPE_WITH_AC_SAMPLING

//�������������ն�
#define CON_TER_TYPE_JC_ALL		//������----�������뿪�Ŵ˺�������һ��
//#define CON_TER_TYPE_JC_GW		//����������
//#define CON_TER_TYPE_JC_CQ		//����������---��������
//#define CON_TER_TYPE_JC_JX		//����������
//#define CON_TER_TYPE_JC_SX		//����������---������
//#define CON_TER_TYPE_JC_QH		//�������ຣ
//#define CON_TER_TYPE_JC_YN		//����������---��������
//#define CON_TER_TYPE_JC_YNML		//��������������---������
//#define CON_TER_TYPE_JC_WUXIAN	//������С����
//#define CON_TER_TYPE_JC_HZJH		//���������ݼҺ�---������
//#define CON_TER_TYPE_JC_SHANXI	//������ɽ��---������
//#define CON_TER_TYPE_JC_HUABEI		//����������---������
#define CON_TER_TYPE_JC_TJ		//���������---������

//ר�䣬���û��������ն�
//#define CON_TER_TYPE_FK_ALL		//ר��----ר���뿪�Ŵ˺�������һ��
//#define CON_TER_TYPE_FK_GW		//ר������
//#define CON_TER_TYPE_FK_HN		//ר�����
//#define CON_TER_TYPE_FK_JX		//ר�佭��
//#define CON_TER_TYPE_FK_QH		//ר���ຣ

//=============================   �ն�����ѡ��  ================================


//-----------------------------   �ն����ͣ�����������  -------------------------
#ifdef CON_TER_TYPE_JC_GW
#define CON_TER_TYPE_WITH_AC_SAMPLING	//����������
//#define CON_TER_TYPE_WITH_BEEN_COLL	//����������,485������
#define SOFT_VER		"GW01"		//����汾
#define SOFT_VER_DATE	0x100903	//YYMMDD��16����
#define HARD_VER		"GW01"		//Ӳ���汾
#define HARD_VER_DATE	0x100330	//YYMMDD��16����
#define PROTO_VER		"GW04"		//��Լ�汾
#define CON_FACTORY_ID   "HZBF"		//���̱���
#define OUTPUT_VERSTR_FMT	("CJ64B-C230-V"SOFT_VER"-%06X_bdb\n")		//����汾�ŵ��ִ���ʽ
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//����汾�ŵ��ִ�����
#endif
//-----------------------------------------------------------------------------

//-----------------------------   �ն����ͣ����켯����  -------------------------
#ifdef CON_TER_TYPE_JC_CQ
//#define CON_TER_TYPE_WITH_AC_SAMPLING	//����������
#define CON_TER_TYPE_PROTOCOL_JC_CQ		//��Լ�������졢���ˡ�������ͬ
#define SOFT_VER		"CQ01"		//����汾
#define SOFT_VER_DATE	0x110505	//YYMMDD��16����
#define HARD_VER		"CQ01"		//Ӳ���汾
#define HARD_VER_DATE	0x100528	//YYMMDD��16����
#define PROTO_VER		"CQ04"		//��Լ�汾
#define CON_FACTORY_ID   "HZBF"		//���̱���
#define OUTPUT_VERSTR_FMT	("CJ64B-C230-V"SOFT_VER"-%06X_bdb\n")		//����汾�ŵ��ִ���ʽ
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//����汾�ŵ��ִ�����
#endif
//-----------------------------------------------------------------------------

//-----------------------------   �ն����ͣ�����������  -------------------------
#ifdef CON_TER_TYPE_JC_JX
#define CON_TER_TYPE_WITH_AC_SAMPLING	//����������
//#define CON_TER_TYPE_WITH_BEEN_COLL	//����������,485������
#define SOFT_VER		"JX15"		//����汾
#define SOFT_VER_DATE	0x110905	//YYMMDD��16����
#define HARD_VER		"JX01"		//Ӳ���汾
#define HARD_VER_DATE	0x100528	//YYMMDD��16����
#define PROTO_VER		"JX04"		//��Լ�汾
#define CON_FACTORY_ID   "HZBF"		//���̱���
#define OUTPUT_VERSTR_FMT	("CJ64B-C791-V"SOFT_VER"-%06X_bdb\n")		//����汾�ŵ��ִ���ʽ
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//����汾�ŵ��ִ�����
#endif
//-----------------------------------------------------------------------------

//-----------------------------   �ն����ͣ�����������  -------------------------
#ifdef CON_TER_TYPE_JC_SX
#define CON_TER_TYPE_WITH_AC_SAMPLING	//����������
#define CON_TER_TYPE_PROTOCOL_JC_CQ		//��Լ�������졢���ˡ�������ͬ
#define SOFT_VER		"SX13"		//����汾
#define SOFT_VER_DATE	0x100716	//YYMMDD��16����
#define HARD_VER		"SX01"		//Ӳ���汾
#define HARD_VER_DATE	0x100330	//YYMMDD��16����
#define PROTO_VER		"SX04"		//��Լ�汾
#define CON_FACTORY_ID   "HZBF"		//���̱���
#define OUTPUT_VERSTR_FMT	("CJ64B-C575-V"SOFT_VER"-%06X_bdb\n")		//����汾�ŵ��ִ���ʽ
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//����汾�ŵ��ִ�����
#endif
//-----------------------------------------------------------------------------

//-----------------------------   �ն����ͣ��������ຣ  -------------------------
#ifdef CON_TER_TYPE_JC_QH
//#define CON_TER_TYPE_WITH_AC_SAMPLING	//����������
//#define CON_TER_TYPE_WITH_BEEN_COLL	//����������,485������
#define SOFT_VER		"QH05"		//����汾
#define SOFT_VER_DATE	0x111208	//YYMMDD��16����
#define HARD_VER		"QH01"		//Ӳ���汾
#define HARD_VER_DATE	0x100528	//YYMMDD��16����
#define PROTO_VER		"QH04"		//��Լ�汾
#define CON_FACTORY_ID   "HZBF"		//���̱���
#define OUTPUT_VERSTR_FMT	("CJ64B-C971-V"SOFT_VER"-%06X_bdb\n")		//����汾�ŵ��ִ���ʽ
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//����汾�ŵ��ִ�����
#endif
//-----------------------------------------------------------------------------

//-----------------------------   �ն����ͣ�����������  -------------------------
#ifdef CON_TER_TYPE_JC_YN
//#define CON_TER_TYPE_WITH_AC_SAMPLING	//����������
#define CON_TER_TYPE_PROTOCOL_JC_CQ		//��Լ�������졢���ˡ�������ͬ
#define CON_TER_TYPE_JC_YN_DATA			//��������
#define SOFT_VER		"YN08"
#define SOFT_VER_DATE   0x100921
#define HARD_VER		"YN01"
#define HARD_VER_DATE   0x100528
#define PROTO_VER		"YN04"		//��Լ�汾
#define CON_FACTORY_ID   "HZBF"		//���̱���
#define OUTPUT_VERSTR_FMT	("CJ64B-C871-V"SOFT_VER"-%06X_bdb\n")		//����汾�ŵ��ִ���ʽ
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//����汾�ŵ��ִ�����
#endif
//-----------------------------------------------------------------------------

//-----------------------------   �ն����ͣ���������������  -------------------------
#ifdef CON_TER_TYPE_JC_YNML
#define CON_TER_TYPE_WITH_AC_SAMPLING	//����������
//#define CON_TER_TYPE_WITH_BEEN_COLL	//����������,485������
#define CON_TER_TYPE_PROTOCOL_JC_CQ		//��Լ�������졢���ˡ�������ͬ
#define CON_TER_TYPE_JC_YN_DATA			//��������
#define SOFT_VER		"YM11"
#define SOFT_VER_DATE   0x101130
#define HARD_VER		"YM01"
#define HARD_VER_DATE   0x100528
#define PROTO_VER		"YM04"		//��Լ�汾
#define CON_FACTORY_ID   "HZBF"		//���̱���
#define OUTPUT_VERSTR_FMT	("CJ64B-C871-V"SOFT_VER"-%06X_bdb\n")		//����汾�ŵ��ִ���ʽ
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//����汾�ŵ��ִ�����
#endif
//-----------------------------------------------------------------------------

//-----------------------------   �ն����ͣ�������С����  -------------------------
#ifdef CON_TER_TYPE_JC_WUXIAN
#define CON_TER_TYPE_WITH_AC_SAMPLING	//����������
#define SOFT_VER		"WX01"		//����汾
#define SOFT_VER_DATE	0x100716	//YYMMDD��16����
#define HARD_VER		"WX01"		//Ӳ���汾
#define HARD_VER_DATE	0x100330	//YYMMDD��16����
#define PROTO_VER		"WX04"		//��Լ�汾
#define CON_FACTORY_ID   "HZBF"		//���̱���
#define OUTPUT_VERSTR_FMT	("CJ64B-C230-V"SOFT_VER"-%06X_bdb\n")		//����汾�ŵ��ִ���ʽ
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//����汾�ŵ��ִ�����
#endif
//-----------------------------------------------------------------------------

//-----------------------------   �ն����ͣ����������ݼҺ�  -------------------------
#ifdef CON_TER_TYPE_JC_HZJH
#define CON_TER_TYPE_WITH_AC_SAMPLING	//����������
#define SOFT_VER		"JH01"		//����汾
#define SOFT_VER_DATE	0x100916	//YYMMDD��16����
#define HARD_VER		"JH01"		//Ӳ���汾
#define HARD_VER_DATE	0x100528	//YYMMDD��16����
#define PROTO_VER		"JH04"		//��Լ�汾
#define CON_FACTORY_ID   "HZJH"		//���̱���
#define OUTPUT_VERSTR_FMT	("CJ64B-C571-V"SOFT_VER"-%06X_bdb\n")		//����汾�ŵ��ִ���ʽ
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//����汾�ŵ��ִ�����
#endif
//-----------------------------------------------------------------------------

//-----------------------------   �ն����ͣ�������ɽ��  -------------------------
#ifdef CON_TER_TYPE_JC_SHANXI
#define CON_TER_TYPE_WITH_AC_SAMPLING	//����������
#define SOFT_VER		"SX01"		//����汾
#define SOFT_VER_DATE	0x101021	//YYMMDD��16����
#define HARD_VER		"SX01"		//Ӳ���汾
#define HARD_VER_DATE	0x100528	//YYMMDD��16����
#define PROTO_VER		"SX04"		//��Լ�汾
#define CON_FACTORY_ID   "HZBF"		//���̱���
#define OUTPUT_VERSTR_FMT	("CJ64B-C351-V"SOFT_VER"-%06X_bdb\n")		//����汾�ŵ��ִ���ʽ
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//����汾�ŵ��ִ�����
#endif
//-----------------------------------------------------------------------------

//-----------------------------   �ն����ͣ�����������  -------------------------
#ifdef CON_TER_TYPE_JC_HUABEI
#define CON_TER_TYPE_WITH_AC_SAMPLING	//����������
#define SOFT_VER		"HB01"		//����汾
#define SOFT_VER_DATE	0x101027	//YYMMDD��16����
#define HARD_VER		"HB01"		//Ӳ���汾
#define HARD_VER_DATE	0x100528	//YYMMDD��16����
#define PROTO_VER		"HB04"		//��Լ�汾
#define CON_FACTORY_ID   "HZBF"		//���̱���
#define OUTPUT_VERSTR_FMT	("CJ64B-C311-V"SOFT_VER"-%06X_bdb\n")		//����汾�ŵ��ִ���ʽ
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//����汾�ŵ��ִ�����
#endif
//-----------------------------------------------------------------------------

//-----------------------------   �ն����ͣ��������  -------------------------
#ifdef CON_TER_TYPE_JC_TJ
#define CON_TER_TYPE_WITH_AC_SAMPLING	//����������
#define SOFT_VER		"TJ01"		//����汾
#define SOFT_VER_DATE	0x120911	//YYMMDD��16����
#define HARD_VER		"TJ01"		//Ӳ���汾
#define HARD_VER_DATE	0x100528	//YYMMDD��16����
#define PROTO_VER		"TJ04"		//��Լ�汾
#define CON_FACTORY_ID   "3001"		//���̱���
#define OUTPUT_VERSTR_FMT	("CJ64B-C220-V"SOFT_VER"-%06X_bdb\n")		//����汾�ŵ��ִ���ʽ
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//����汾�ŵ��ִ�����
#endif
//-----------------------------------------------------------------------------


//-----------------------------   �ն����ͣ�ר������  ----------------------
#ifdef CON_TER_TYPE_FK_GW
#define CON_TER_TYPE_WITH_AC_SAMPLING	//����������
#define SOFT_VER		"GW01"		//����汾
#define SOFT_VER_DATE	0x100830	//YYMMDD��16����
#define HARD_VER		"GW01"		//Ӳ���汾
#define HARD_VER_DATE	0x100402	//YYMMDD��16����
#define PROTO_VER		"GW04"		//��Լ�汾
#define CON_FACTORY_ID   "HZBF"		//���̱���
#define OUTPUT_VERSTR_FMT	("ZF64A-C230-V"SOFT_VER"-%06X_bdb\n")		//����汾�ŵ��ִ���ʽ
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//����汾�ŵ��ִ�����
#endif
//-----------------------------------------------------------------------------

//-----------------------------   �ն����ͣ�ר�����  -------------------------
#ifdef CON_TER_TYPE_FK_HN
#define CON_TER_TYPE_WITH_AC_SAMPLING	//����������
#define SOFT_VER		"HN01"		//����汾
#define SOFT_VER_DATE	0x100830	//YYMMDD��16����
#define HARD_VER		"HN01"		//Ӳ���汾
#define HARD_VER_DATE	0x100402	//YYMMDD��16����
#define PROTO_VER		"HN04"		//��Լ�汾
#define CON_FACTORY_ID   "HZBF"		//���̱���
#define OUTPUT_VERSTR_FMT	("ZF64A-C371-V"SOFT_VER"-%06X_bdb\n")		//����汾�ŵ��ִ���ʽ
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//����汾�ŵ��ִ�����
#endif
//-----------------------------------------------------------------------------

//-----------------------------   �ն����ͣ�ר�佭��  -------------------------
#ifdef CON_TER_TYPE_FK_JX
#define CON_TER_TYPE_WITH_AC_SAMPLING	//����������
#define SOFT_VER		"JX03"		//����汾
#define SOFT_VER_DATE	0x101009	//YYMMDD��16����
#define HARD_VER		"JX01"		//Ӳ���汾
#define HARD_VER_DATE	0x100402	//YYMMDD��16����
#define PROTO_VER		"JX04"		//��Լ�汾
#define CON_FACTORY_ID   "HZBF"		//���̱���
#define OUTPUT_VERSTR_FMT	("ZF64A-C791-V"SOFT_VER"-%06X_bdb\n")		//����汾�ŵ��ִ���ʽ
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//����汾�ŵ��ִ�����
#endif
//-----------------------------------------------------------------------------

//-----------------------------   �ն����ͣ�ר���ຣ  -------------------------
#ifdef CON_TER_TYPE_FK_QH
#define CON_TER_TYPE_WITH_AC_SAMPLING	//����������
#define SOFT_VER		"QH01"		//����汾
#define SOFT_VER_DATE	0x100826	//YYMMDD��16����
#define HARD_VER		"QH01"		//Ӳ���汾
#define HARD_VER_DATE	0x100402	//YYMMDD��16����
#define PROTO_VER		"QH04"		//��Լ�汾
#define CON_FACTORY_ID   "HZBF"		//���̱���
#define OUTPUT_VERSTR_FMT	("ZF64B-C971-V"SOFT_VER"-%06X_bdb\n")		//����汾�ŵ��ִ���ʽ
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//����汾�ŵ��ִ�����
#endif
//-----------------------------------------------------------------------------

#endif // PAX_VER_H


