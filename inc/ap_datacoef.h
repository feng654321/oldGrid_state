//============================================================================
//  File Name: ap_datacoef.h
//
//  Copyright PAX Hangzhou 2011.  All rights reserved.
//
//  Description:
//      参数有关的处理信息
//
//  Modification History:
//      $Id:  Exp $
//      $Log: $
//      Revision 1.0 Create by Taozhiguo in 2011.04.28
//============================================================================
#ifndef __AP_DATACOEF_H__
#define __AP_DATACOEF_H__
    
#ifdef  __AP_DATACOEF_C__
    #define AP_DATACOEF_EXT
#else
    #define AP_DATACOEF_EXT extern
#endif  
AP_DATACOEF_EXT uchar ucCoefCheckDisplayReNewRequest;// 显示参数更新标识

AP_DATACOEF_EXT uchar CoefCheckMode(void);

AP_DATACOEF_EXT void CoefPowerUpResume(uchar isPowerUpInit);

AP_DATACOEF_EXT uchar WriteCoefDataWithSync(const uchar *usData, ulong DataName, u16 uiLen);
AP_DATACOEF_EXT uchar ReadCoefDataWithCheck(ulong DataName, u16 uiLen, uchar* pSrc, uchar ucTestBcd);
AP_DATACOEF_EXT void MeterParaInit(void);

AP_DATACOEF_EXT uchar GetSetHarmonicNumber(void);
#endif

























































