/***************************************************************************
 *
 * COPYRIGHT (C) 2009 PaxHZ, ALL RIGHTS RESERVED
 * #Abstract: 软硬件版本定义
 * 
 ***************************************************************************/
#ifndef PAX_VER_H
#define PAX_VER_H

//=============================   终端类型选择  ================================
//请选择集中器或专变和对应的地区宏开放，注销其他所有
//集中器添加地方版本信息时注意是否带交采，带则开放相应宏CON_TER_TYPE_WITH_AC_SAMPLING

//集中器，集抄终端
#define CON_TER_TYPE_JC_ALL		//集中器----集中器请开放此宏和下面的一个
//#define CON_TER_TYPE_JC_GW		//集中器国网
//#define CON_TER_TYPE_JC_CQ		//集中器重庆---不带交采
//#define CON_TER_TYPE_JC_JX		//集中器江西
//#define CON_TER_TYPE_JC_SX		//集中器绍兴---带交采
//#define CON_TER_TYPE_JC_QH		//集中器青海
//#define CON_TER_TYPE_JC_YN		//集中器云南---不带交采
//#define CON_TER_TYPE_JC_YNML		//集中器云南弥勒---带交采
//#define CON_TER_TYPE_JC_WUXIAN	//集中器小无线
//#define CON_TER_TYPE_JC_HZJH		//集中器杭州家和---带交采
//#define CON_TER_TYPE_JC_SHANXI	//集中器山西---带交采
//#define CON_TER_TYPE_JC_HUABEI		//集中器华北---带交采
#define CON_TER_TYPE_JC_TJ		//集中器天津---带交采

//专变，大用户，负控终端
//#define CON_TER_TYPE_FK_ALL		//专变----专变请开放此宏和下面的一个
//#define CON_TER_TYPE_FK_GW		//专变Ⅲ国网
//#define CON_TER_TYPE_FK_HN		//专变河南
//#define CON_TER_TYPE_FK_JX		//专变江西
//#define CON_TER_TYPE_FK_QH		//专变青海

//=============================   终端类型选择  ================================


//-----------------------------   终端类型：集中器国网  -------------------------
#ifdef CON_TER_TYPE_JC_GW
#define CON_TER_TYPE_WITH_AC_SAMPLING	//带交流采样
//#define CON_TER_TYPE_WITH_BEEN_COLL	//带交流采样,485允许被抄
#define SOFT_VER		"GW01"		//软件版本
#define SOFT_VER_DATE	0x100903	//YYMMDD，16进制
#define HARD_VER		"GW01"		//硬件版本
#define HARD_VER_DATE	0x100330	//YYMMDD，16进制
#define PROTO_VER		"GW04"		//规约版本
#define CON_FACTORY_ID   "HZBF"		//厂商编码
#define OUTPUT_VERSTR_FMT	("CJ64B-C230-V"SOFT_VER"-%06X_bdb\n")		//输入版本号的字串格式
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//输入版本号的字串参数
#endif
//-----------------------------------------------------------------------------

//-----------------------------   终端类型：重庆集中器  -------------------------
#ifdef CON_TER_TYPE_JC_CQ
//#define CON_TER_TYPE_WITH_AC_SAMPLING	//带交流采样
#define CON_TER_TYPE_PROTOCOL_JC_CQ		//规约类型重庆、绍兴、云南相同
#define SOFT_VER		"CQ01"		//软件版本
#define SOFT_VER_DATE	0x110505	//YYMMDD，16进制
#define HARD_VER		"CQ01"		//硬件版本
#define HARD_VER_DATE	0x100528	//YYMMDD，16进制
#define PROTO_VER		"CQ04"		//规约版本
#define CON_FACTORY_ID   "HZBF"		//厂商编码
#define OUTPUT_VERSTR_FMT	("CJ64B-C230-V"SOFT_VER"-%06X_bdb\n")		//输入版本号的字串格式
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//输入版本号的字串参数
#endif
//-----------------------------------------------------------------------------

//-----------------------------   终端类型：集中器江西  -------------------------
#ifdef CON_TER_TYPE_JC_JX
#define CON_TER_TYPE_WITH_AC_SAMPLING	//带交流采样
//#define CON_TER_TYPE_WITH_BEEN_COLL	//带交流采样,485允许被抄
#define SOFT_VER		"JX15"		//软件版本
#define SOFT_VER_DATE	0x110905	//YYMMDD，16进制
#define HARD_VER		"JX01"		//硬件版本
#define HARD_VER_DATE	0x100528	//YYMMDD，16进制
#define PROTO_VER		"JX04"		//规约版本
#define CON_FACTORY_ID   "HZBF"		//厂商编码
#define OUTPUT_VERSTR_FMT	("CJ64B-C791-V"SOFT_VER"-%06X_bdb\n")		//输入版本号的字串格式
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//输入版本号的字串参数
#endif
//-----------------------------------------------------------------------------

//-----------------------------   终端类型：集中器绍兴  -------------------------
#ifdef CON_TER_TYPE_JC_SX
#define CON_TER_TYPE_WITH_AC_SAMPLING	//带交流采样
#define CON_TER_TYPE_PROTOCOL_JC_CQ		//规约类型重庆、绍兴、云南相同
#define SOFT_VER		"SX13"		//软件版本
#define SOFT_VER_DATE	0x100716	//YYMMDD，16进制
#define HARD_VER		"SX01"		//硬件版本
#define HARD_VER_DATE	0x100330	//YYMMDD，16进制
#define PROTO_VER		"SX04"		//规约版本
#define CON_FACTORY_ID   "HZBF"		//厂商编码
#define OUTPUT_VERSTR_FMT	("CJ64B-C575-V"SOFT_VER"-%06X_bdb\n")		//输入版本号的字串格式
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//输入版本号的字串参数
#endif
//-----------------------------------------------------------------------------

//-----------------------------   终端类型：集中器青海  -------------------------
#ifdef CON_TER_TYPE_JC_QH
//#define CON_TER_TYPE_WITH_AC_SAMPLING	//带交流采样
//#define CON_TER_TYPE_WITH_BEEN_COLL	//带交流采样,485允许被抄
#define SOFT_VER		"QH05"		//软件版本
#define SOFT_VER_DATE	0x111208	//YYMMDD，16进制
#define HARD_VER		"QH01"		//硬件版本
#define HARD_VER_DATE	0x100528	//YYMMDD，16进制
#define PROTO_VER		"QH04"		//规约版本
#define CON_FACTORY_ID   "HZBF"		//厂商编码
#define OUTPUT_VERSTR_FMT	("CJ64B-C971-V"SOFT_VER"-%06X_bdb\n")		//输入版本号的字串格式
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//输入版本号的字串参数
#endif
//-----------------------------------------------------------------------------

//-----------------------------   终端类型：集中器云南  -------------------------
#ifdef CON_TER_TYPE_JC_YN
//#define CON_TER_TYPE_WITH_AC_SAMPLING	//带交流采样
#define CON_TER_TYPE_PROTOCOL_JC_CQ		//规约类型重庆、绍兴、云南相同
#define CON_TER_TYPE_JC_YN_DATA			//云南数据
#define SOFT_VER		"YN08"
#define SOFT_VER_DATE   0x100921
#define HARD_VER		"YN01"
#define HARD_VER_DATE   0x100528
#define PROTO_VER		"YN04"		//规约版本
#define CON_FACTORY_ID   "HZBF"		//厂商编码
#define OUTPUT_VERSTR_FMT	("CJ64B-C871-V"SOFT_VER"-%06X_bdb\n")		//输入版本号的字串格式
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//输入版本号的字串参数
#endif
//-----------------------------------------------------------------------------

//-----------------------------   终端类型：集中器云南弥勒  -------------------------
#ifdef CON_TER_TYPE_JC_YNML
#define CON_TER_TYPE_WITH_AC_SAMPLING	//带交流采样
//#define CON_TER_TYPE_WITH_BEEN_COLL	//带交流采样,485允许被抄
#define CON_TER_TYPE_PROTOCOL_JC_CQ		//规约类型重庆、绍兴、云南相同
#define CON_TER_TYPE_JC_YN_DATA			//云南数据
#define SOFT_VER		"YM11"
#define SOFT_VER_DATE   0x101130
#define HARD_VER		"YM01"
#define HARD_VER_DATE   0x100528
#define PROTO_VER		"YM04"		//规约版本
#define CON_FACTORY_ID   "HZBF"		//厂商编码
#define OUTPUT_VERSTR_FMT	("CJ64B-C871-V"SOFT_VER"-%06X_bdb\n")		//输入版本号的字串格式
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//输入版本号的字串参数
#endif
//-----------------------------------------------------------------------------

//-----------------------------   终端类型：集中器小无线  -------------------------
#ifdef CON_TER_TYPE_JC_WUXIAN
#define CON_TER_TYPE_WITH_AC_SAMPLING	//带交流采样
#define SOFT_VER		"WX01"		//软件版本
#define SOFT_VER_DATE	0x100716	//YYMMDD，16进制
#define HARD_VER		"WX01"		//硬件版本
#define HARD_VER_DATE	0x100330	//YYMMDD，16进制
#define PROTO_VER		"WX04"		//规约版本
#define CON_FACTORY_ID   "HZBF"		//厂商编码
#define OUTPUT_VERSTR_FMT	("CJ64B-C230-V"SOFT_VER"-%06X_bdb\n")		//输入版本号的字串格式
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//输入版本号的字串参数
#endif
//-----------------------------------------------------------------------------

//-----------------------------   终端类型：集中器杭州家和  -------------------------
#ifdef CON_TER_TYPE_JC_HZJH
#define CON_TER_TYPE_WITH_AC_SAMPLING	//带交流采样
#define SOFT_VER		"JH01"		//软件版本
#define SOFT_VER_DATE	0x100916	//YYMMDD，16进制
#define HARD_VER		"JH01"		//硬件版本
#define HARD_VER_DATE	0x100528	//YYMMDD，16进制
#define PROTO_VER		"JH04"		//规约版本
#define CON_FACTORY_ID   "HZJH"		//厂商编码
#define OUTPUT_VERSTR_FMT	("CJ64B-C571-V"SOFT_VER"-%06X_bdb\n")		//输入版本号的字串格式
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//输入版本号的字串参数
#endif
//-----------------------------------------------------------------------------

//-----------------------------   终端类型：集中器山西  -------------------------
#ifdef CON_TER_TYPE_JC_SHANXI
#define CON_TER_TYPE_WITH_AC_SAMPLING	//带交流采样
#define SOFT_VER		"SX01"		//软件版本
#define SOFT_VER_DATE	0x101021	//YYMMDD，16进制
#define HARD_VER		"SX01"		//硬件版本
#define HARD_VER_DATE	0x100528	//YYMMDD，16进制
#define PROTO_VER		"SX04"		//规约版本
#define CON_FACTORY_ID   "HZBF"		//厂商编码
#define OUTPUT_VERSTR_FMT	("CJ64B-C351-V"SOFT_VER"-%06X_bdb\n")		//输入版本号的字串格式
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//输入版本号的字串参数
#endif
//-----------------------------------------------------------------------------

//-----------------------------   终端类型：集中器华北  -------------------------
#ifdef CON_TER_TYPE_JC_HUABEI
#define CON_TER_TYPE_WITH_AC_SAMPLING	//带交流采样
#define SOFT_VER		"HB01"		//软件版本
#define SOFT_VER_DATE	0x101027	//YYMMDD，16进制
#define HARD_VER		"HB01"		//硬件版本
#define HARD_VER_DATE	0x100528	//YYMMDD，16进制
#define PROTO_VER		"HB04"		//规约版本
#define CON_FACTORY_ID   "HZBF"		//厂商编码
#define OUTPUT_VERSTR_FMT	("CJ64B-C311-V"SOFT_VER"-%06X_bdb\n")		//输入版本号的字串格式
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//输入版本号的字串参数
#endif
//-----------------------------------------------------------------------------

//-----------------------------   终端类型：天津集中器  -------------------------
#ifdef CON_TER_TYPE_JC_TJ
#define CON_TER_TYPE_WITH_AC_SAMPLING	//带交流采样
#define SOFT_VER		"TJ01"		//软件版本
#define SOFT_VER_DATE	0x120911	//YYMMDD，16进制
#define HARD_VER		"TJ01"		//硬件版本
#define HARD_VER_DATE	0x100528	//YYMMDD，16进制
#define PROTO_VER		"TJ04"		//规约版本
#define CON_FACTORY_ID   "3001"		//厂商编码
#define OUTPUT_VERSTR_FMT	("CJ64B-C220-V"SOFT_VER"-%06X_bdb\n")		//输入版本号的字串格式
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//输入版本号的字串参数
#endif
//-----------------------------------------------------------------------------


//-----------------------------   终端类型：专变Ⅲ国网  ----------------------
#ifdef CON_TER_TYPE_FK_GW
#define CON_TER_TYPE_WITH_AC_SAMPLING	//带交流采样
#define SOFT_VER		"GW01"		//软件版本
#define SOFT_VER_DATE	0x100830	//YYMMDD，16进制
#define HARD_VER		"GW01"		//硬件版本
#define HARD_VER_DATE	0x100402	//YYMMDD，16进制
#define PROTO_VER		"GW04"		//规约版本
#define CON_FACTORY_ID   "HZBF"		//厂商编码
#define OUTPUT_VERSTR_FMT	("ZF64A-C230-V"SOFT_VER"-%06X_bdb\n")		//输入版本号的字串格式
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//输入版本号的字串参数
#endif
//-----------------------------------------------------------------------------

//-----------------------------   终端类型：专变河南  -------------------------
#ifdef CON_TER_TYPE_FK_HN
#define CON_TER_TYPE_WITH_AC_SAMPLING	//带交流采样
#define SOFT_VER		"HN01"		//软件版本
#define SOFT_VER_DATE	0x100830	//YYMMDD，16进制
#define HARD_VER		"HN01"		//硬件版本
#define HARD_VER_DATE	0x100402	//YYMMDD，16进制
#define PROTO_VER		"HN04"		//规约版本
#define CON_FACTORY_ID   "HZBF"		//厂商编码
#define OUTPUT_VERSTR_FMT	("ZF64A-C371-V"SOFT_VER"-%06X_bdb\n")		//输入版本号的字串格式
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//输入版本号的字串参数
#endif
//-----------------------------------------------------------------------------

//-----------------------------   终端类型：专变江西  -------------------------
#ifdef CON_TER_TYPE_FK_JX
#define CON_TER_TYPE_WITH_AC_SAMPLING	//带交流采样
#define SOFT_VER		"JX03"		//软件版本
#define SOFT_VER_DATE	0x101009	//YYMMDD，16进制
#define HARD_VER		"JX01"		//硬件版本
#define HARD_VER_DATE	0x100402	//YYMMDD，16进制
#define PROTO_VER		"JX04"		//规约版本
#define CON_FACTORY_ID   "HZBF"		//厂商编码
#define OUTPUT_VERSTR_FMT	("ZF64A-C791-V"SOFT_VER"-%06X_bdb\n")		//输入版本号的字串格式
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//输入版本号的字串参数
#endif
//-----------------------------------------------------------------------------

//-----------------------------   终端类型：专变青海  -------------------------
#ifdef CON_TER_TYPE_FK_QH
#define CON_TER_TYPE_WITH_AC_SAMPLING	//带交流采样
#define SOFT_VER		"QH01"		//软件版本
#define SOFT_VER_DATE	0x100826	//YYMMDD，16进制
#define HARD_VER		"QH01"		//硬件版本
#define HARD_VER_DATE	0x100402	//YYMMDD，16进制
#define PROTO_VER		"QH04"		//规约版本
#define CON_FACTORY_ID   "HZBF"		//厂商编码
#define OUTPUT_VERSTR_FMT	("ZF64B-C971-V"SOFT_VER"-%06X_bdb\n")		//输入版本号的字串格式
#define OUTPUT_VERSTR_ARG	SOFT_VER_DATE							//输入版本号的字串参数
#endif
//-----------------------------------------------------------------------------

#endif // PAX_VER_H


