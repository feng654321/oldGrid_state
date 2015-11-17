#define AP_ADE7758_GLOBALS
#include "common.h"

//电压有效值地址结构体定义
const u16 TB_ADE7878_VOLTAGE_RMS[3]=
{
    AD_AVRMS,
    AD_BVRMS,
    AD_CVRMS,   
};
//电流有效值地址结构体定义
const u16 TB_ADE7878_CURRENT_RMS[3]=
{
    AD_AIRMS,
    AD_BIRMS,
    AD_CIRMS,   
};
const u16 TB_ADE7878_ENERGY[]=
{
    AD_AWATT,
    AD_BWATT,
    AD_CWATT,
    
//  AD_AWATTHR,
//  AD_BWATTHR,
//  AD_CWATTHR,
    
    AD_AVAR,
    AD_BVAR,
    AD_CVAR,
    
    AD_AVA,
    AD_BVA,
    AD_CVA,
};
//能量地址结构体定义
const u16 TB_ADE7878_READ_NOUSE[]=
{
    AD_AWATTHR,
    AD_BWATTHR,
    AD_CWATTHR,
//  AD_AVAR,
//  AD_BVAR,
//  AD_CVAR,
    
    AD_AVARHR,
    AD_BVARHR,
    AD_CVARHR,
    
    AD_AVAHR,
    AD_BVAHR,
    AD_CVAHR,
};
const char TB_ADE7878_PERIOD_SEL[9]=
{
//  00,01,02,03,04,05,06,07,08  -->DATA
//  no, A, B,AB,C,AC,BC,ABC,    -->CUT
//     A, B, A, C, A, B, A, A, A,
    00,01,00,02,00,01,00,00,00
};

//currently, it has about 157 items.
const ST_ADE7878_REG_PARAM TB_ADE7878_REG_RESUME[]=
{
    {AD_CONFIG2, CON_ADE7878_DATA_TYPE_8_U8_R_W, GAL_YES, 0x00000000}, // 0x00  Configuration register used during PSM1 mode. (See Table 48) 
    
    {AD_AIGAIN,  CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase A current gain adjust 
    {AD_AVGAIN,  CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase A voltage gain adjust 
    {AD_BIGAIN,  CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase B current gain adjust 
    {AD_BVGAIN,  CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase B voltage gain adjust 
    {AD_CIGAIN,  CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase C current gain adjust 
    {AD_CVGAIN,  CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase C voltage gain adjust 
    {AD_NIGAIN,  CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Neutral current gain adjust 
    {AD_AIRMSOS, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_NO,  0x00000000}, // 0x000000  Phase A current rms offset 
    {AD_AVRMSOS, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase A voltage rms offset 
    {AD_BIRMSOS, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_NO,  0x00000000}, // 0x000000  Phase B current rms offset 
    {AD_BVRMSOS, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase B voltage rms offset 
    {AD_CIRMSOS, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_NO,  0x00000000}, // 0x000000  Phase C current rms offset 
    {AD_CVRMSOS, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase C voltage rms offset 
    {AD_NIRMSOS, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Neutral current rms offset 
    {AD_AVAGAIN, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase A apparent power gain adjust 
    {AD_BVAGAIN, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase B apparent power gain adjust 
    {AD_CVAGAIN, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase C apparent power gain adjust 
    {AD_AWGAIN,  CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase A total active power gain adjust 
    {AD_AWATTOS, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase A total active power offset adjust 
    {AD_BWGAIN,  CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase B total active power gain adjust 
    {AD_BWATTOS, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase B total active power offset adjust 
    {AD_CWGAIN,  CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase C total active power gain adjust 
    {AD_CWATTOS, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase C total active power offset adjust 
    {AD_AVARGAIN,CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase A total reactive power gain adjust 
    {AD_AVAROS,  CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase A total reactive power offset adjust 
    {AD_BVARGAIN,CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase B total reactive power gain adjust 
    {AD_BVAROS,  CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase B total reactive power offset adjust 
    {AD_CVARGAIN,CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase C total reactive power gain adjust 
    {AD_CVAROS,  CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase C total reactive power offset adjust 
    {AD_AFWGAIN, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase A fundamental active power gain adjust 
    {AD_AFWATTOS,CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase A fundamental active power offset adjust 
    {AD_BFWGAIN, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase B fundamental active power gain adjust 
    {AD_BFWATTOS,CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase B fundamental active power offset adjust 
    {AD_CFWGAIN, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase C fundamental active power gain adjust 
    {AD_CFWATTOS,CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase C fundamental active power offset adjust 
    {AD_AFVARGAIN,CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W,GAL_YES, 0x00000000}, // 0x000000  Phase A fundamental reactive power gain adjust 
    {AD_AFVAROS, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase A fundamental reactive power offset adjust 
    {AD_BFVARGAIN,CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W,GAL_YES, 0x00000000}, // 0x000000  Phase B fundamental reactive power gain adjust 
    {AD_BFVAROS, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase B fundamental reactive power offset adjust 
    {AD_CFVARGAIN,CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W,GAL_YES, 0x00000000}, // 0x000000  Phase C fundamental reactive power gain adjust 
    {AD_CFVAROS, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Phase C fundamental reactive power offset adjust 
    {AD_VATHR1,  CON_ADE7878_DATA_TYPE_32ZP_U24_R_W, GAL_YES, 0x00000000}, // 0x000000  Most significant 24 bits of VATHR[47:0] threshold used in phase apparent power data path. 
    {AD_VATHR0,  CON_ADE7878_DATA_TYPE_32ZP_U24_R_W, GAL_YES, 0x00C35000}, // 0x000000  Less significant 24 bits of VATHR[47:0] threshold used in phase apparent power data path. 
    {AD_WTHR1,   CON_ADE7878_DATA_TYPE_32ZP_U24_R_W, GAL_YES, 0x00000000}, // 0x000000  Most significant 24 bits of WTHR[47:0] threshold used in phase total/fundamental active power data path. 
    {AD_WTHR0,   CON_ADE7878_DATA_TYPE_32ZP_U24_R_W, GAL_YES, 0x00C35000}, // 0x000000  Less significant 24 bits of WTHR[47:0] threshold  used in phase total/fundamental active power data path.
    {AD_VARTHR1, CON_ADE7878_DATA_TYPE_32ZP_U24_R_W, GAL_YES, 0x00000000}, // 0x000000  Most significant 24 bits of VARTHR[47:0] threshold used in phase total/fundamental reactive power data path. 
    {AD_VARTHR0, CON_ADE7878_DATA_TYPE_32ZP_U24_R_W, GAL_YES, 0x00C35000}, // 0x000000  Less significant 24 bits of VARTHR[47:0] threshold used in phase total/fundamental reactive power data path. 
    // {AD_reserved, , GAL_YES, 0x00000000}, // 0x000000  This memory location should be kept at 0x000000 for proper operation 
    {AD_VANOLOAD,CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x0000000  No-load threshold in the apparent power data path 
    {AD_APNOLOAD,CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x0000000  No-load threshold in the total/fundamental active power data path 
    {AD_VARNOLOAD, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x0000000  No-load threshold in the total/fundamental reactive power data path 
    {AD_VLEVEL,  CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x0000000  Register used in the algorithm that computes the fundamental active and reactive powers 
    // AD_reserved, , GAL_YES, 0x00000000, // 0x000000  This memory location should not be written for proper operation 
    {AD_DICOEFF, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x0000000  Register used in the digital integrator algorithm. If the integrator is turned on, it must be set at 0xFF8000 
    {AD_HPFDIS,  CON_ADE7878_DATA_TYPE_32ZP_U24_R_W, GAL_YES, 0x00000000}, // 0x000000  Disables/enables the HPF in the current data path (see Table 28) 
    // AD_reserved, , GAL_YES, 0x00000000}, // 0x000000  This memory location should be kept at 0x000000 for proper operation 
    {AD_ISUMLVL, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // 0x0000000  Threshold used in the comparison between the sum of phase currents and the neutral current 
    // AD_reserved, , GAL_YES, 0x00000000}, // 0x000000  These memory locations should be kept at 0x000000 for proper operation
    {AD_ISUM,    CON_ADE7878_DATA_TYPE_32ZP_S28_R , GAL_YES, 0x00000000}, // NA  Sum of IAVW, IBVW and ICVW registers 
    {AD_AIRMS,   CON_ADE7878_DATA_TYPE_32ZP_S24_R , GAL_YES, 0x00000000}, // NA  Phase A current rms value 
    {AD_AVRMS,   CON_ADE7878_DATA_TYPE_32ZP_S24_R , GAL_YES, 0x00000000}, // NA  Phase A voltage rms value 
    {AD_BIRMS,   CON_ADE7878_DATA_TYPE_32ZP_S24_R , GAL_YES, 0x00000000}, // NA  Phase B current rms value 
    {AD_BVRMS,   CON_ADE7878_DATA_TYPE_32ZP_S24_R , GAL_YES, 0x00000000}, // NA  Phase B voltage rms value 
    {AD_CIRMS,   CON_ADE7878_DATA_TYPE_32ZP_S24_R , GAL_YES, 0x00000000}, // NA  Phase C current rms value 
    {AD_CVRMS,   CON_ADE7878_DATA_TYPE_32ZP_S24_R , GAL_YES, 0x00000000}, // NA  Phase C voltage rms value 
    {AD_NIRMS,   CON_ADE7878_DATA_TYPE_32ZP_S24_R , GAL_YES, 0x00000000}, // NA  Neutral current rms value 
    // {AD_reserved, , GAL_YES, 0x00000000}, // 0x000000  These memory locations should not be written for proper operation 
    // {AD_reserved, CON_ADE7878_DATA_TYPE_16_U16_R_W, GAL_YES, 0x00000000}, // 0x0000  This memory location should not be written for proper operation. 
    {AD_AWATTHR, CON_ADE7878_DATA_TYPE_32_S32_R , GAL_YES, 0x00000000}, // 0x00000000  Phase A total active energy accumulation 
    {AD_BWATTHR, CON_ADE7878_DATA_TYPE_32_S32_R , GAL_YES, 0x00000000}, // 0x00000000  Phase B total active energy accumulation 
    {AD_CWATTHR, CON_ADE7878_DATA_TYPE_32_S32_R , GAL_YES, 0x00000000}, // 0x00000000  Phase C total active energy accumulation 
    {AD_AFWATTHR,CON_ADE7878_DATA_TYPE_32_S32_R , GAL_YES, 0x00000000}, // 0x00000000  Phase A fundamental active energy accumulation 
    {AD_BFWATTHR,CON_ADE7878_DATA_TYPE_32_S32_R , GAL_YES, 0x00000000}, // 0x00000000  Phase B fundamental active energy accumulation 
    {AD_CFWATTHR,CON_ADE7878_DATA_TYPE_32_S32_R , GAL_YES, 0x00000000}, // 0x00000000  Phase C fundamental active energy accumulation 
    {AD_AVARHR,  CON_ADE7878_DATA_TYPE_32_S32_R , GAL_YES, 0x00000000}, // 0x00000000  Phase A total reactive energy accumulation 
    {AD_BVARHR,  CON_ADE7878_DATA_TYPE_32_S32_R , GAL_YES, 0x00000000}, // 0x00000000  Phase B total reactive energy accumulation 
    {AD_CVARHR,  CON_ADE7878_DATA_TYPE_32_S32_R , GAL_YES, 0x00000000}, // 0x00000000  Phase C total reactive energy accumulation 
    {AD_AFVARHR, CON_ADE7878_DATA_TYPE_32_S32_R , GAL_YES, 0x00000000}, // 0x00000000  Phase A fundamental reactive energy accumulation 
    {AD_BFVARHR, CON_ADE7878_DATA_TYPE_32_S32_R , GAL_YES, 0x00000000}, // 0x00000000  Phase B fundamental reactive energy accumulation 
    {AD_CFVARHR, CON_ADE7878_DATA_TYPE_32_S32_R , GAL_YES, 0x00000000}, // 0x00000000  Phase C fundamental reactive energy accumulation 
    {AD_AVAHR,   CON_ADE7878_DATA_TYPE_32_S32_R , GAL_YES, 0x00000000}, // 0x00000000  Phase A apparent energy accumulation 
    {AD_BVAHR,   CON_ADE7878_DATA_TYPE_32_S32_R , GAL_YES, 0x00000000}, // 0x00000000  Phase B apparent energy accumulation 
    {AD_CVAHR,   CON_ADE7878_DATA_TYPE_32_S32_R , GAL_YES, 0x00000000}, // 0x00000000  Phase C apparent energy accumulation 
    {AD_IPEAK,   CON_ADE7878_DATA_TYPE_32_U32_R , GAL_YES, 0x00000000}, // NA  Current peak register. See Figure 36 and Table 29 for details about its composition. 
    {AD_VPEAK,   CON_ADE7878_DATA_TYPE_32_U32_R , GAL_YES, 0x00000000}, // NA  Voltage peak register. See Figure 36 and Table 30 for details about its composition. 
    {AD_STATUS0, CON_ADE7878_DATA_TYPE_32_U32_R , GAL_YES, 0x00000000}, // NA  Interrupt status register 0. (See Table 31) 
    {AD_STATUS1, CON_ADE7878_DATA_TYPE_32_U32_R , GAL_YES, 0x00000000}, // NA  Interrupt status register 1. (See Table 32) 
    {AD_AIMAV,   CON_ADE7878_DATA_TYPE_32ZP_U20_R , GAL_YES, 0x00000000}, // NA  Phase A current rms computed during PSM1 mode 
    {AD_BIMAV,   CON_ADE7878_DATA_TYPE_32ZP_U20_R , GAL_YES, 0x00000000}, // NA  Phase B current rms computed during PSM1 mode 
    {AD_CIMAV,   CON_ADE7878_DATA_TYPE_32ZP_U20_R , GAL_YES, 0x00000000}, // NA  Phase C current rms computed during PSM1 mode 
    {AD_OILVL,   CON_ADE7878_DATA_TYPE_32ZP_U24_R_W, GAL_YES, 0xFFFFFFFF}, // 0xFFFFFF  Overcurrent threshold 
    {AD_OVLVL,   CON_ADE7878_DATA_TYPE_32ZP_U24_R_W, GAL_YES, 0xFFFFFFFF}, // 0xFFFFFF  Overvoltage threshold 
    {AD_SAGLVL,  CON_ADE7878_DATA_TYPE_32ZP_U24_R_W, GAL_YES, 0x00000000}, // 0x000000  Voltage sag level threshold 
    {AD_MASK0,   CON_ADE7878_DATA_TYPE_32_U32_R_W, GAL_YES, 0x00000000}, // 0x00000000  Interrupt enable register 0. (See Table 33) 
    {AD_MASK1,   CON_ADE7878_DATA_TYPE_32_U32_R_W, GAL_YES, 0x00000000}, // 0x00000000  Interrupt enable register 1. (See Table 34) 
    {AD_IAWV,    CON_ADE7878_DATA_TYPE_32SE_S24_R , GAL_YES, 0x00000000}, // NA  Instantaneous value of phase A current 
    {AD_IBWV,    CON_ADE7878_DATA_TYPE_32SE_S24_R , GAL_YES, 0x00000000}, // NA  Instantaneous value of phase B current 
    {AD_ICWV,    CON_ADE7878_DATA_TYPE_32SE_S24_R , GAL_YES, 0x00000000}, // NA  Instantaneous value of phase C current 
    {AD_INWV,    CON_ADE7878_DATA_TYPE_32SE_S24_R , GAL_YES, 0x00000000}, // NA  Instantaneous value of neutral current 
    {AD_VAWV,    CON_ADE7878_DATA_TYPE_32SE_S24_R , GAL_YES, 0x00000000}, // NA  Instantaneous value of phase A voltage 
    {AD_VBWV,    CON_ADE7878_DATA_TYPE_32SE_S24_R , GAL_YES, 0x00000000}, // NA  Instantaneous value of phase B voltage 
    {AD_VCWV,    CON_ADE7878_DATA_TYPE_32SE_S24_R , GAL_YES, 0x00000000}, // NA  Instantaneous value of phase C voltage 
    {AD_AWATT,   CON_ADE7878_DATA_TYPE_32SE_S24_R , GAL_YES, 0x00000000}, // NA  Instantaneous value of phase A total active power 
    {AD_BWATT,   CON_ADE7878_DATA_TYPE_32SE_S24_R , GAL_YES, 0x00000000}, // NA  Instantaneous value of phase B total active power 
    {AD_CWATT,   CON_ADE7878_DATA_TYPE_32SE_S24_R , GAL_YES, 0x00000000}, // NA  Instantaneous value of phase B total active power 
    {AD_AVAR,    CON_ADE7878_DATA_TYPE_32SE_S24_R , GAL_YES, 0x00000000}, // NA  Instantaneous value of phase A total reactive power 
    {AD_BVAR,    CON_ADE7878_DATA_TYPE_32SE_S24_R , GAL_YES, 0x00000000}, // NA  Instantaneous value of phase B total reactive power 
    {AD_CVAR,    CON_ADE7878_DATA_TYPE_32SE_S24_R , GAL_YES, 0x00000000}, // NA  Instantaneous value of phase B total reactive power 
    {AD_AVA,     CON_ADE7878_DATA_TYPE_32SE_S24_R , GAL_YES, 0x00000000}, // NA  Instantaneous value of phase A apparent power 
    {AD_BVA,     CON_ADE7878_DATA_TYPE_32SE_S24_R , GAL_YES, 0x00000000}, // NA  Instantaneous value of phase Bapparent power 
    {AD_CVA,     CON_ADE7878_DATA_TYPE_32SE_S24_R , GAL_YES, 0x00000000}, // NA  Instantaneous value of phase B apparent power 
    {AD_CHECKSUM,CON_ADE7878_DATA_TYPE_32_U32_R , GAL_YES, 0x00000000}, // 0x9AE5E8B1  Checksum verification. See Checksum Register section for details 
    {AD_VNOM,    CON_ADE7878_DATA_TYPE_32ZP_S24_R_W, GAL_YES, 0x00000000}, // 0x000000  Nominal phase voltage rms used in the alternative computation of the apparent power 
    // {AD_reserved, , GAL_YES, 0x00000000}, //  These addresses should not be written for proper operation 
    {AD_PHSTATUS,CON_ADE7878_DATA_TYPE_16_U16_R , GAL_YES, 0x00000000}, // NA  Phase peak register. (See Table 35) 
    {AD_ANGLE0,  CON_ADE7878_DATA_TYPE_16_U16_R , GAL_YES, 0x00000000}, // NA  Time delay 0. See Time Interval Between Phases section for details 
    {AD_ANGLE1,  CON_ADE7878_DATA_TYPE_16_U16_R , GAL_YES, 0x00000000}, // NA  Time delay 1. See Time Interval Between Phases section for details 
    {AD_ANGLE2,  CON_ADE7878_DATA_TYPE_16_U16_R , GAL_YES, 0x00000000}, // NA  Time delay 2. See Time Interval Between Phases section for details 
    // {AD_reserved, , GAL_YES, 0x00000000}, //  These addresses should not be written for proper operation 
    {AD_PERIOD,  CON_ADE7878_DATA_TYPE_16_U16_R , GAL_YES, 0x00000000}, // NA  Network line period 
    {AD_PHNOLOAD,CON_ADE7878_DATA_TYPE_16_U16_R , GAL_YES, 0x00000000}, // NA  Phase no-load register. (See Table 36) 
    // {AD_reserved, , GAL_YES, 0x00000000}, //  These addresses should not be written for proper operation 
    {AD_LINECYC, CON_ADE7878_DATA_TYPE_16_U16_R_W, GAL_YES, 0xFFFFFFFF}, // 0xFFFF  Line cycle accumulation mode count 
    {AD_ZXTOUT,  CON_ADE7878_DATA_TYPE_16_U16_R_W, GAL_YES, 0xFFFFFFFF}, // 0xFFFF  Zero crossing timeout count 
    {AD_COMPMODE,CON_ADE7878_DATA_TYPE_16_U16_R_W, GAL_NO, 0x0000003F}, // 0x01FF  Computation mode register. (See Table 37) 
    {AD_GAIN,    CON_ADE7878_DATA_TYPE_16_U16_R_W, GAL_YES, 0x00000000}, // 0x0000  PGA gains at ADC inputs. (See Table 38) 
    {AD_CFMODE,  CON_ADE7878_DATA_TYPE_16_U16_R_W, GAL_YES, 0x00000088}, // 0x0E88  CFx, x=1,2,3 configuration register. (See Table 39) 
    {AD_CF1DEN,  CON_ADE7878_DATA_TYPE_16_U16_R_W, GAL_YES, 0x00000FB6}, // 0x0000  CF1 denominator 
    {AD_CF2DEN,  CON_ADE7878_DATA_TYPE_16_U16_R_W, GAL_YES, 0x00000FB6}, // 0x0000  CF2 denominator 
    {AD_CF3DEN,  CON_ADE7878_DATA_TYPE_16_U16_R_W, GAL_YES, 0x00000FB6}, // 0x0000  CF3 denominator 
    {AD_APHCAL,  CON_ADE7878_DATA_TYPE_16ZP_U10_R_W, GAL_YES, 0x00000000}, // 0x0000  Phase calibration of phase A. (See Table 40) 
    {AD_BPHCAL,  CON_ADE7878_DATA_TYPE_16ZP_U10_R_W, GAL_YES, 0x00000000}, // 0x0000  Phase calibration of phase B. (See Table 40) 
    {AD_CPHCAL,  CON_ADE7878_DATA_TYPE_16ZP_U10_R_W, GAL_YES, 0x00000000}, // 0x0000  Phase calibration of phase C. (See Table 40) 
    {AD_PHSIGN,  CON_ADE7878_DATA_TYPE_16_U16_R , GAL_YES, 0x00000000}, // NA  Power sign register. (See Table 41) 
    {AD_CONFIG,  CON_ADE7878_DATA_TYPE_16_U16_R_W, GAL_NO, 0x00000000}, // 0x0000  ADE7878 configuration register. (See Table 42) 
    {AD_MMODE,   CON_ADE7878_DATA_TYPE_8_U8_R_W, GAL_NO, 0x00000000}, // 0x16  Measurement mode register. (See Table 43) 
    {AD_ACCMODE, CON_ADE7878_DATA_TYPE_8_U8_R_W, GAL_YES, 0x00000000}, // 0x00  Accumulation mode register. (SeeTable 44) 
    {AD_LCYCMODE,CON_ADE7878_DATA_TYPE_8_U8_R_W, GAL_YES, 0x00000040}, // 0x78  Line accumulation mode behavior. (See Table 45) 
    {AD_PEAKCYC, CON_ADE7878_DATA_TYPE_8_U8_R_W, GAL_YES, 0x00000000}, // 0x00  Peak detection half line cycles 
    {AD_SAGCYC,  CON_ADE7878_DATA_TYPE_8_U8_R_W, GAL_YES, 0x00000000}, // 0x00  Sag detection half line cycles 
    {AD_CFCYC,   CON_ADE7878_DATA_TYPE_8_U8_R_W, GAL_YES, 0x00000001}, // 0x01  Number of CF pulses between two consecutive energy latches. See Synchronizing energy registers with CFx outputs section 
    {AD_HSDC_CFG,CON_ADE7878_DATA_TYPE_8_U8_R_W, GAL_NO, 0x00000000}, // 0x00  HSDC configuration register. (See Table 46) 
    {AD_VERSION, CON_ADE7878_DATA_TYPE_8_U8_R_W, GAL_NO, 0x00000000}, // - Version of die 
    // {AD_reserved, CON_ADE7878_DATA_TYPE_8_8_, GAL_YES, 0x00000000}, //  This address may be used in manipulating the SS pin when SPI is chosen as the active port. (See Serial Interfaces chapter for details) 
    {AD_LPOILVL, CON_ADE7878_DATA_TYPE_8_U8_R_W, GAL_YES, 0x00000007}, // 0x07  Overcurrent threshold used during PSM2 mode. (See Table 47) 

    {AD_RESERVED43AF, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // AA 保留使用，必须设置为0   AA  
    {AD_RESERVED43B7, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // AA 保留使用，必须设置为0   AA  
    {AD_RESERVED43B9, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // AA 保留使用，必须设置为0   AA  
    {AD_RESERVED43BA, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // AA 保留使用，必须设置为0   AA  
    {AD_RESERVED43BB, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // AA 保留使用，必须设置为0   AA  
    {AD_RESERVED43BC, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // AA 保留使用，必须设置为0   AA  
    {AD_RESERVED43BD, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // AA 保留使用，必须设置为0   AA  
    {AD_RESERVED43BE, CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W, GAL_YES, 0x00000000}, // AA 保留使用，必须设置为0   AA  

    {AD_RUN, CON_ADE7878_DATA_TYPE_16_U16_R_W, GAL_YES, 0x00000001}, // 0x0000  RUN register starts and stops the DSP. See Digital Signal Processor chapter for more details. 
    // 0x0000  AA  虚拟的电流校准寄存器  AA
    {AD_VIRTUALREG_ACURRENTSAVE,CON_ADE7878_DATA_TYPE_16_U16_R_W,GAL_NO, 0x00000800}, // 0x0000  AA  虚拟的电流校准寄存器  AA
    {AD_VIRTUALREG_BCURRENTSAVE,CON_ADE7878_DATA_TYPE_16_U16_R_W,GAL_NO, 0x00000800}, // 0x0000  AA  虚拟的电流校准寄存器  AA
    {AD_VIRTUALREG_CCURRENTSAVE,CON_ADE7878_DATA_TYPE_16_U16_R_W,GAL_NO, 0x00000800}, // 0x0000  AA  虚拟的电流校准寄存器  AA

    {AD_VIRTUALREG_CHECKSUMSAVE0,CON_ADE7878_DATA_TYPE_32_U32_R,GAL_NO, 0x00000000}, 
    {AD_VIRTUALREG_CHECKSUMSAVE1,CON_ADE7878_DATA_TYPE_32_U32_R,GAL_NO, 0x00000000}, 
    {AD_VIRTUALREG_CHECKSUMSAVE2,CON_ADE7878_DATA_TYPE_32_U32_R,GAL_NO, 0x00000000}, 
    {AD_VIRTUALREG_CHECKSUMSAVE3,CON_ADE7878_DATA_TYPE_32_U32_R,GAL_NO, 0x00000000}, 
    {AD_VIRTUALREG_CHECKSUMSAVE4,CON_ADE7878_DATA_TYPE_32_U32_R,GAL_NO, 0x00000000}, 
    {AD_VIRTUALREG_CHECKSUMSAVE5,CON_ADE7878_DATA_TYPE_32_U32_R,GAL_NO, 0x00000000}, 
    {AD_VIRTUALREG_CHECKSUMSAVE6,CON_ADE7878_DATA_TYPE_32_U32_R,GAL_NO, 0x00000000}, 
    {AD_VIRTUALREG_CHECKSUMSAVE7,CON_ADE7878_DATA_TYPE_32_U32_R,GAL_NO, 0x00000000}, 
    {AD_VIRTUALREG_CHECKSUMSAVE8,CON_ADE7878_DATA_TYPE_32_U32_R,GAL_NO, 0x00000000}, 
};

//local function
u16 GetAde7878RegSOS(u16 uiRegName);
uchar Ade7878RegCanWrite(uchar ucRegType);
ulong SqrtFromX2Y2(ulong x,ulong y);
void CosDataFromKwKva(ulong ukw, ulong ukva, uchar *point);
void InitAD7878PinReset(void);
void WriteADRegResetDefault(void);
void SetAde7878CheckSum(u16 uiAddrOffSet);

static uchar ucStatusPowerQuadrantUseZ;
static uchar ucStatusPowerQuadrantUseA;
static uchar ucStatusPowerQuadrantUseB;
static uchar ucStatusPowerQuadrantUseC;

static uchar ucStatusPowerQuadrantTimeZ;
static uchar ucStatusPowerQuadrantTimeA;
static uchar ucStatusPowerQuadrantTimeB;
static uchar ucStatusPowerQuadrantTimeC;

static ulong ulCoefCurrentRMSOS[3];

//static uchar ucModeAde7758Second;
//static uchar ucModeAde7758RmsSecond;
//static uchar ucModeAde7758KwClalSecond;
//static uchar ucModeAde7878AngleSecond;

//校表数据存储位置 GAL_YES:*.PAR文件   GAL_NO:按原来表计存储在E2(文件)每个位置
#define ADE_7758_USE_PAR_ADJ    GAL_YES
//驱动库版本定义 GAL_YES:新库   GAL_NO:老库
#define ADE_7758_USE_NEW_LIB    GAL_YES

/*==================================================================
//函数名：  GetAde7878RegSOS
//作者：    
//日期：    
//功能：    根据寄存器算出存储位置的偏移量
//输入参数：uiRegName
//输出参数：无
//返回值：  
//=================================================================*/
u16 GetAde7878RegSOS(u16 uiRegName)
{
    u16 uiTemp,uiCount;
    uiCount=(sizeof(TB_ADE7878_REG_RESUME)/sizeof(ST_ADE7878_REG_PARAM));
    for(uiTemp=0;uiTemp<uiCount;uiTemp++)
    {
        if(TB_ADE7878_REG_RESUME[uiTemp].RegName==uiRegName)
        {
            return (4*uiTemp);
        }
    }
    return 0xffff;
}
/*==================================================================
//函数名：  GetAde7878RegName
//作者：    
//日期：    
//功能：    根据存储位置的偏移量算出寄存器
//输入参数：uiDataAddrSos
//输出参数：无
//返回值：  
//=================================================================*/
u16 GetAde7878RegName(u16 uiDataAddrSos)
{
    u16 uiTemp;

    uiTemp = uiDataAddrSos/4;
    if( (uiDataAddrSos != uiTemp*4) || (uiTemp > sizeof(TB_ADE7878_REG_RESUME)/sizeof(ST_ADE7878_REG_PARAM)) )
        return 0xffff;
    return TB_ADE7878_REG_RESUME[uiTemp].RegName;
}
/*==================================================================
//函数名：  WriteAD7878Command
//作者：    
//日期：    
//功能：    重新调整，低字节在前，高字节在后
//输入参数：usAddr
			ucLen
//输出参数：pData
//返回值：  无
//=================================================================*/
void WriteAD7878Command(unsigned short usAddr,unsigned char *pData,unsigned char ucLen)
{
#ifdef  VRAM_ENABLE    
    if(isVRAMON())
    {
        vWriteAD7878Command(usAddr, pData, ucLen);
        return;
    }
#endif
#if(ADE_7758_USE_NEW_LIB == GAL_YES)
    acs_write_reg(usAddr, pData, ucLen);
#else
	struct acs_reg tmp_reg;
	tmp_reg.reg_add = usAddr;
	tmp_reg.data_len = ucLen;
	memcpy(tmp_reg.data, pData, ucLen);
	asc_sendcmd(ACS_WR_REG, &tmp_reg);
#endif
}

/*==================================================================
//函数名：  ReadAD7878Command
//作者：    
//日期：    
//功能：    重新调整，低字节在前，高字节在后
//输入参数：usAddr
			ucLen
//输出参数：pData
//返回值：  无
//=================================================================*/
void ReadAD7878Command(unsigned short usAddr,unsigned char *pData,unsigned char ucLen)
{
#ifdef  VRAM_ENABLE    
    if(isVRAMON())
    {
        vReadAD7878Command(usAddr, pData, ucLen);
        return;
    }
#endif    
#if(ADE_7758_USE_NEW_LIB == GAL_YES)
    acs_read_reg(usAddr, ucLen, pData);
#else    
	struct acs_reg tmp_reg;
	tmp_reg.reg_add = usAddr;
	tmp_reg.data_len = ucLen;
	asc_sendcmd(ACS_RD_REG, &tmp_reg);
	memcpy(pData, tmp_reg.data, ucLen);
#endif
    //MTRACE("7878->%02x%02x%02x%02x\n", pData[0], pData[1], pData[2], pData[3]);
}

/*==================================================================
//函数名：  bakzone_main_para_read
//作者：    
//日期：    
//功能：    从校表参数区读取
//输入参数：usAddr
			ucLen
//输出参数：pData
//返回值：  成功返回0, 失败返回 < 0
//=================================================================*/
int bakzone_main_para_read(unsigned short usAddr, unsigned char *pData,unsigned char ucLen)
{
	int ret;
	char slabel[8];
	char sval[128];
	unsigned char value_type;
	unsigned char val[4];
	
	ret = 1;
	if(ucLen > 4)
		ucLen = 4;
	sprintf(slabel, "%04X", usAddr);
	ret = cfo_get_value_in_file(CON_STR_FILE_ADE7878_PAR, slabel, sval, &value_type);
	if(ret == 0)
	{
		unsigned char c1, c2;
		int i,j;
		j = 0;
		for(i=0; i<8; i+=2)
		{
			c1 = sval[i]-'0';
			if( c1 > 9 )
				c1=c1-7;
			c2 = sval[i+1]-'0';
			if( c2 > 9 )
				c2=c2-7;
			
			val[3-j] = ( c1<<4 ) | ( c2&0xF );
			j++;
		}
		
		for(i=0;i<ucLen;i++)
			pData[i] = val[ucLen-1-i];
	}
	else
	{
		memset(pData, 0x00, ucLen);
	}
	return ret;
}

/*==================================================================
//函数名：  bakzone_main_para_write
//作者：    
//日期：    
//功能：    写入校表参数区
//输入参数：usAddr
			pData
			ucLen
//输出参数：无
//返回值：  无
//=================================================================*/
void bakzone_main_para_write(unsigned short usAddr, unsigned char *pData,unsigned char ucLen)
{
	unsigned char tmp_data[4];
	char slabel[8];
	char sval[32];
	int i;
	
	if(ucLen > 4)
		ucLen = 4;
	memset(tmp_data, 0x00, 4);
	for(i=0;i<ucLen;i++)
		tmp_data[i] = pData[ucLen-1-i];
	
	sprintf(slabel, "%04X", usAddr);
	sprintf(sval, "%02X%02X%02X%02X", tmp_data[3], tmp_data[2], tmp_data[1], tmp_data[0]);
	cfo_set_value_in_file(CON_STR_FILE_ADE7878_PAR, slabel, sval, 1);
}

/*==================================================================
//函数名：  bakzone_back_para_read
//作者：    
//日期：    
//功能：    从校表参数区读取
//输入参数：usAddr
			ucLen
//输出参数：pData
//返回值：  成功返回0, 失败返回 < 0
//=================================================================*/
int bakzone_back_para_read(unsigned short usAddr, unsigned char *pData,unsigned char ucLen)
{
	int ret;
	char slabel[8];
	char sval[128];
	unsigned char value_type;
	unsigned char val[4];
	
	if(ucLen > 4)
		ucLen = 4;
	sprintf(slabel, "%04X", usAddr);
	ret = cfo_get_value_in_file(CON_STR_FILE_ADE7878_PA2, slabel, sval, &value_type);
	if(ret == 0)
	{
		unsigned char c1, c2;
		int i,j;
		j = 0;
		for(i=0; i<8; i+=2)
		{
			c1 = sval[i]-'0';
			if( c1 > 9 )
				c1=c1-7;
			c2 = sval[i+1]-'0';
			if( c2 > 9 )
				c2=c2-7;
			
			val[3-j] = ( c1<<4 ) | ( c2&0xF );
			j++;
		}
		
		for(i=0;i<ucLen;i++)
			pData[i] = val[ucLen-1-i];
	}
	else
	{
		memset(pData, 0x00, ucLen);
	}
	
	return ret;
}

/*==================================================================
//函数名：  bakzone_back_para_write
//作者：    
//日期：    
//功能：    写入校表参数区
//输入参数：usAddr
			pData
			ucLen
//输出参数：无
//返回值：  无
//=================================================================*/
void bakzone_back_para_write(unsigned short usAddr, unsigned char *pData,unsigned char ucLen)
{
	unsigned char tmp_data[4];
	char slabel[8];
	char sval[32];
	int i;
	
	if(ucLen > 4)
		ucLen = 4;
	memset(tmp_data, 0x00, 4);
	for(i=0;i<ucLen;i++)
		tmp_data[i] = pData[ucLen-1-i];
	
	sprintf(slabel, "%04X", usAddr);
	sprintf(sval, "%02X%02X%02X%02X", tmp_data[3], tmp_data[2], tmp_data[1], tmp_data[0]);
    	//LOGTRACE("Par %s = %s\n", slabel, sval);
	cfo_set_value_in_file(CON_STR_FILE_ADE7878_PA2, slabel, sval, 1);
}

/*==================================================================
//函数名：  ReadADRegResumeDataFromPar
//作者：    
//日期：    
//功能：    
//输入参数：uiRegName
			ucDatalen
			Dst
//输出参数：无
//返回值：  成功返回0, 失败返回1
//=================================================================*/
unsigned char ReadADRegResumeDataFromPar(unsigned short uiRegName,unsigned char ucDatalen, unsigned char *Dst)
{
	unsigned short uiDataAddrSos;
	//uiDataAddrSos = GetAde7878RegSOS(uiRegName);
	uiDataAddrSos = uiRegName;
	if(0xffff != uiDataAddrSos)
	{
		if(bakzone_main_para_read(0+uiDataAddrSos, Dst, ucDatalen) != 0)
		{
			bakzone_back_para_read(0+uiDataAddrSos, Dst, ucDatalen);
		}
		return 1;
	}
	return 0;
}

/*==================================================================
//函数名：  WriteADRegResumeDataToPar
//作者：    
//日期：    
//功能：    
//输入参数：uiRegName
			ucDatalen
			Dst
//输出参数：无
//返回值：  成功返回0, 失败返回1
//=================================================================*/
unsigned char WriteADRegResumeDataToPar(unsigned short uiRegName,unsigned char ucDatalen, unsigned char *Dst)
{
	unsigned short uiDataAddrSos;
	//uiDataAddrSos = GetAde7878RegSOS(uiRegName);
	uiDataAddrSos = (uiRegName);
	//MTRACE("WritePar 0x%x, %d\n", uiRegName, ucDatalen);
	if(0xffff != uiDataAddrSos)
	{
		bakzone_main_para_write(0+uiDataAddrSos, Dst, ucDatalen);
		bakzone_back_para_write(0+uiDataAddrSos, Dst, ucDatalen);
		return 1;
	}
	return 0;
}

/*******************************************************************************
函数名      : Ade7878RegCanWrite
函数实现功能:
输入        : 
返回        :
应用范围   :
说明       : 
运行时间   :
堆栈大小   :
-------------------------------------------------------------------------------
修改记录 : 
  日 期          版本      修改人              修改内容           

-------------------------------------------------------------------------------
*******************************************************************************/
uchar Ade7878RegCanWrite(uchar ucRegType)
{
    uchar ucDataLen;
    ucDataLen=0;
    switch(ucRegType)
    {
        case CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W:
        case CON_ADE7878_DATA_TYPE_32ZP_U24_R_W:
        case CON_ADE7878_DATA_TYPE_32ZP_S24_R_W:
        case CON_ADE7878_DATA_TYPE_32_U32_R_W:
            ucDataLen=4;
            break;
        case CON_ADE7878_DATA_TYPE_16ZP_U10_R_W:
        case CON_ADE7878_DATA_TYPE_16_U16_R_W:
            ucDataLen=2;
            break;
        case CON_ADE7878_DATA_TYPE_8_U8_R_W:
            ucDataLen=1;
            break;
        case CON_ADE7878_DATA_TYPE_32ZP_S24_R:
        case CON_ADE7878_DATA_TYPE_32ZP_U20_R:
        case CON_ADE7878_DATA_TYPE_32_S32_R:
        case CON_ADE7878_DATA_TYPE_32_U32_R:
        case CON_ADE7878_DATA_TYPE_32SE_S24_R:
        case CON_ADE7878_DATA_TYPE_32ZP_S28_R:
        case CON_ADE7878_DATA_TYPE_16_U16_R:
        case CON_ADE7878_DATA_TYPE_VIRTUALREG:
        default:
            ucDataLen=0;
    }   
    return ucDataLen;
}

void InitAD7878(void)     
{
#if(ADE_7758_USE_NEW_LIB == GAL_YES)
  //  acs_();
  //  acs_close();
    acs_start_run();
#endif    
}

void CloseAD7878(void)     
{
#if(ADE_7758_USE_NEW_LIB == GAL_YES)
    acs_stop_run();
	ERRTRACE("->...AD7878 Close\n");
#endif    
}

uchar ReadADReg (u16 Src, uchar Len ,uchar *Dst)
/*********************************************************************
原型：uchar ReadADReg (u16 Src, uchar Len ,uchar *Dst)
功能：读ADE7758的内部的数据, 其中包含虚拟的寄存器
参数：
    Src 寄存器地址
    Len 要读取的数据长度
    *Dst 数据返回的地址
输入：无
返回：数据是否能正确读出
范围：应用层直接调用
注释：无
作者：张龙
版本：V1.0
最后修改时间：2009-05-04
修改说明：创建
********************************************************************/
{
    memset(Dst, 0x00, 4);
    ReadAD7878Command(Src,Dst,Len);
    return 1;
}
uchar WriteADReg (uchar *Src, u16 Dst, uchar Len)
/*********************************************************************
原型：uchar WriteADReg (uchar *Src, u16 Dst, uchar Len)
功能：往ADE7758的寄存器里面写数据
参数：
    Dst 寄存器地址
    Len 要读取的数据长度
    *Src 要写入的数据的起始地址
输入：无
返回：写入是否成功
范围：应用层直接调用
注释：无
作者：张龙
版本：V1.0
最后修改时间：2009-05-04
修改说明：创建
********************************************************************/
{
    WriteAD7878Command(Dst, Src, Len);
    return 1;
}

uchar WriteADRegCheck (uchar *Src, u16 Dst, uchar Len)
{
    uchar ucTemp[4],ucNum;
    WriteAD7878Command((uchar)Dst, Src, Len);
    if(1==ReadADReg((uchar)Dst,Len,&ucTemp[0]))
    {
        for(ucNum=0;ucNum<Len;ucNum++)
        {
            if(ucTemp[ucNum]!=*(Src+ucNum))
            {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

uchar ReadADRegComm (u16 Src, uchar Len ,uchar *Dst)
{
    memset(Dst, 0x00, 4);
    if((Src<0x1000)||(AD_AIRMSOS==Src)||(AD_BIRMSOS==Src)||(AD_CIRMSOS==Src))
    {
        ReadADRegResumeData(Src,Len,Dst);
    }
    else
    {
        ReadAD7878Command(Src,Dst,Len);
    }
    return 1;
}
// 成功 返回1；失败返回0
uchar ReadADRegResumeData(u16 uiRegName,uchar ucDatalen, uchar *Dst)
{
#if(ADE_7758_USE_PAR_ADJ == GAL_YES)    
    if(ReadADRegResumeDataFromPar(uiRegName, ucDatalen, Dst) == 1)
    {
        //成功直接返回
        return 1;
    }
#else    
    u16 uiDataAddrSos;
    uiDataAddrSos=GetAde7878RegSOS(uiRegName);

    if(0xffff!=uiDataAddrSos)
    {
        if(0==ReadDataDirect(EPL_DATA_ADREG_START+uiDataAddrSos,  ucDatalen,Dst))
        {
            ReadDataDirect(EPL_DATA_ADREG_START+uiDataAddrSos,  ucDatalen,Dst);
        }
        return 1;
    }
#endif    
    ERRTRACE("->");
    return 0;
}

/*==================================================================
//函数名：  WriteADRegResumeDataByRegname
//作者：    
//日期：    
//功能：    根据寄存器名字写入，只支持单个寄存器数据写入
//输入参数：uiRegName
			ucDatalen
			Dst
//输出参数：无
//返回值：  成功 返回1；失败返回0
//=================================================================*/
uchar WriteADRegResumeDataByRegname(u16 uiRegName,uchar ucDatalen, uchar *Dst)
{
#if(ADE_7758_USE_PAR_ADJ == GAL_YES)    
    //MTRACE("WriteName 0x%x, %d\n", uiRegName, ucDatalen);
    if(WriteADRegResumeDataToPar(uiRegName, ucDatalen, Dst) == 1)
    {
        //成功直接返回
        return 1;
    }
#else    
    u16 uiDataAddrSos;
    uiDataAddrSos=GetAde7878RegSOS(uiRegName);
    
    if(0xffff!=uiDataAddrSos)
    {
        if(0==WriteDataDirect(Dst,EPL_DATA_ADREG_START+uiDataAddrSos, ucDatalen))
        {
            WriteDataDirect(Dst,EPL_DATA_ADREG_START+uiDataAddrSos, ucDatalen);
        }
        return 1;
    }
#endif    
    ERRTRACE("->");
    return 0;
}
/*==================================================================
//函数名：  WriteADRegResumeDataByAddrSos
//作者：    
//日期：    
//功能：    根据存储地址写入，可写一片数据
//输入参数：uiRegName
			ucDatalen
			Dst
//输出参数：无
//返回值：  成功 返回1；失败返回0
//=================================================================*/
uchar WriteADRegResumeDataByAddrSos(u16 uiDataAddrSos,uchar ucDatalen, uchar *Dst)
{
#if(ADE_7758_USE_PAR_ADJ == GAL_YES)    
    u16  uiRegName;
    uchar ucLen = 0;
    u16 ret = 1;
    
    //MTRACE("WriteSos %d, %d\n", uiDataAddrSos, ucDatalen);
    if(uiDataAddrSos >= (sizeof(TB_ADE7878_REG_RESUME)/sizeof(ST_ADE7878_REG_PARAM))*4)
    {
        ERRTRACE("->");
        return 0;
    }
    while(ucDatalen)
    {
        uiRegName = GetAde7878RegName(uiDataAddrSos);
        if(uiRegName != 0xffff)
        {
            //uiTemp = uiDataAddrSos / 4;
            //ucLen=Ade7878RegCanWrite(TB_ADE7878_REG_RESUME[uiTemp].ResumeType);
            if(ucDatalen < 4)
                ucLen = ucDatalen;
            else
                ucLen = 4;
            // TODO: 这里断言 寄存器写都按4字节操作
            if(WriteADRegResumeDataToPar(uiRegName, ucLen, Dst) == 1)
            {
                //成功直接返回
                return 1;
            }
            else
            {
                ErrPrint("WriteADRegResumeDataToPar 0x%x", uiRegName);
                ret = 0;
            }
        }
        ucDatalen -= ucLen;
        uiDataAddrSos += ucLen;
        Dst += ucLen;
    }
    if(ret == 0)
        ERRTRACE("->");
    return ret;
#else        
    if(0xffff!=uiDataAddrSos)
    {
        if(0==WriteDataDirect(Dst,EPL_DATA_ADREG_START+uiDataAddrSos, ucDatalen))
        {
            WriteDataDirect(Dst,EPL_DATA_ADREG_START+uiDataAddrSos, ucDatalen);
        }
        return 1;
    }
    return 0;
#endif    
}

void SetAde7878CheckSum(u16 uiAddrOffSet)
{
    uchar ucTemp;

    for(ucTemp=0;ucTemp<9;ucTemp++)
    {
        Wr_data[0]=TB_ADE7878_PERIOD_SEL[ucTemp];
        WriteADReg(&Wr_data[0], AD_MMODE, 1);
        Delay1mS();
        Delay1mS();
        ReadADReg(AD_CHECKSUM,4,&Wr_data[10+ucTemp*4]);
    }

    WriteADRegResumeDataByAddrSos(uiAddrOffSet, CON_ADE7878CHECKSUM_DATA_MAX_LEN, &Wr_data[10]);

}

// 校表参数初始化
void WriteADRegResetDefault(void)
{
    u16 uiTemp,uiCount;
    UN_U32_PARAM unTemp;
    for(uiTemp=0;uiTemp<80;uiTemp++)
    {
        unTemp.ulData=TB_ADE7878_REG_RESUME[uiTemp].ulDefaultData;      //取寄存器的默认参数
        switch(TB_ADE7878_REG_RESUME[uiTemp].ResumeType)
        {
            case CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W:
            case CON_ADE7878_DATA_TYPE_32ZP_U24_R_W:
            case CON_ADE7878_DATA_TYPE_32ZP_S24_R_W:
            case CON_ADE7878_DATA_TYPE_32_U32_R_W:
                Wr_data[4*uiTemp+0]=unTemp.ucbData[3];
                Wr_data[4*uiTemp+1]=unTemp.ucbData[2];
                Wr_data[4*uiTemp+2]=unTemp.ucbData[1];
                Wr_data[4*uiTemp+3]=unTemp.ucbData[0];
                break;
            case CON_ADE7878_DATA_TYPE_16ZP_U10_R_W:
            case CON_ADE7878_DATA_TYPE_16_U16_R_W:
                Wr_data[4*uiTemp+0]=unTemp.ucbData[1];
                Wr_data[4*uiTemp+1]=unTemp.ucbData[0];
                Wr_data[4*uiTemp+2]=00;
                Wr_data[4*uiTemp+3]=00;
                break;
            case CON_ADE7878_DATA_TYPE_8_U8_R_W:
                Wr_data[4*uiTemp+0]=unTemp.ucbData[0];
                Wr_data[4*uiTemp+1]=0x00;
                Wr_data[4*uiTemp+2]=0x00;
                Wr_data[4*uiTemp+3]=0x00;
                break;
            case CON_ADE7878_DATA_TYPE_32ZP_S24_R:
            case CON_ADE7878_DATA_TYPE_32ZP_U20_R:
            case CON_ADE7878_DATA_TYPE_32_S32_R:
            case CON_ADE7878_DATA_TYPE_32_U32_R:
            case CON_ADE7878_DATA_TYPE_32SE_S24_R:
            case CON_ADE7878_DATA_TYPE_32ZP_S28_R:
            case CON_ADE7878_DATA_TYPE_16_U16_R:
            case CON_ADE7878_DATA_TYPE_VIRTUALREG:
            default:
                Wr_data[4*uiTemp+0]=0x00;
                Wr_data[4*uiTemp+1]=0x00;
                Wr_data[4*uiTemp+2]=0x00;
                Wr_data[4*uiTemp+3]=0x00;
                break;
        }
    }
    #if 0
    if(0==WriteDataDirect(&Wr_data[0],EPL_DATA_ADREG_START+0,  320))
    {
        WriteDataDirect(&Wr_data[0],EPL_DATA_ADREG_START+0,  320);
    }
    #endif
    for(uiTemp=0;uiTemp<5;uiTemp++)
    {
        WriteADRegResumeDataByAddrSos(uiTemp*64, 64, &Wr_data[uiTemp*64]);
    }
        
    uiCount=(sizeof(TB_ADE7878_REG_RESUME)/sizeof(ST_ADE7878_REG_PARAM));
    uiCount=uiCount-80;
    for(uiTemp=0;uiTemp<uiCount;uiTemp++)
    {
        unTemp.ulData=TB_ADE7878_REG_RESUME[80+uiTemp].ulDefaultData;
        switch(TB_ADE7878_REG_RESUME[80+uiTemp].ResumeType)
        {
            case CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W:
            case CON_ADE7878_DATA_TYPE_32ZP_U24_R_W:
            case CON_ADE7878_DATA_TYPE_32ZP_S24_R_W:
            case CON_ADE7878_DATA_TYPE_32_U32_R_W:
                Wr_data[4*uiTemp+0]=unTemp.ucbData[3];
                Wr_data[4*uiTemp+1]=unTemp.ucbData[2];
                Wr_data[4*uiTemp+2]=unTemp.ucbData[1];
                Wr_data[4*uiTemp+3]=unTemp.ucbData[0];
                break;
            case CON_ADE7878_DATA_TYPE_16ZP_U10_R_W:
            case CON_ADE7878_DATA_TYPE_16_U16_R_W:
                Wr_data[4*uiTemp+0]=unTemp.ucbData[1];
                Wr_data[4*uiTemp+1]=unTemp.ucbData[0];
                Wr_data[4*uiTemp+2]=00;
                Wr_data[4*uiTemp+3]=00;
                break;
            case CON_ADE7878_DATA_TYPE_8_U8_R_W:
                Wr_data[4*uiTemp+0]=unTemp.ucbData[0];
                Wr_data[4*uiTemp+1]=0x00;
                Wr_data[4*uiTemp+2]=0x00;
                Wr_data[4*uiTemp+3]=0x00;
                break;
            case CON_ADE7878_DATA_TYPE_32ZP_S24_R:
            case CON_ADE7878_DATA_TYPE_32ZP_U20_R:
            case CON_ADE7878_DATA_TYPE_32_S32_R:
            case CON_ADE7878_DATA_TYPE_32_U32_R:
            case CON_ADE7878_DATA_TYPE_32SE_S24_R:
            case CON_ADE7878_DATA_TYPE_32ZP_S28_R:
            case CON_ADE7878_DATA_TYPE_16_U16_R:
            case CON_ADE7878_DATA_TYPE_VIRTUALREG:
            default:
                Wr_data[4*uiTemp+0]=0x00;
                Wr_data[4*uiTemp+1]=0x00;
                Wr_data[4*uiTemp+2]=0x00;
                Wr_data[4*uiTemp+3]=0x00;
                break;
        }
    }
    #if 0
    if(0==WriteDataDirect(&Wr_data[0],EPL_DATA_ADREG_START+320,  4*uiCount))
    {
        WriteDataDirect(&Wr_data[0],EPL_DATA_ADREG_START+320,  4*uiCount);
    }
    #endif
    for(uiTemp=0;uiTemp<uiCount;uiTemp++)
    {
        WriteADRegResumeDataByAddrSos(320+uiTemp*4, 4, &Wr_data[uiTemp*4]);
    }
    InitADMode(GAL_YES, GAL_NO);
}
uchar WriteADRegResumeData(u16 uiRegName,uchar ucDatalen,uchar *Dst)
{
    u16 uiDataAddrSos;
    UN_U32_PARAM unTemp;
    if(0xffff==uiRegName)
    {
        if(4==TestZeroNum(Dst, 4))
        {
            WriteADRegResetDefault();
            return 1;
        }
        else
        {
            return 0;
        }
    }
    
    uiDataAddrSos=GetAde7878RegSOS(uiRegName);
    if(0xffff!=uiDataAddrSos)
    {
        // AA     AA
        if((AD_VIRTUALREG_CHECKSUMSAVE0<=uiRegName)&&(uiRegName<AD_VIRTUALREG_ACURRENTSAVE))
        {
            if(AD_VIRTUALREG_CHECKSUMSAVE0==uiRegName)
            {
                if(4==TestZeroNum(Dst, 4))
                {
                    memset(&Wr_data[0], 0x00, 36);
                    WriteADRegResumeDataByAddrSos(uiDataAddrSos, CON_ADE7878CHECKSUM_DATA_MAX_LEN, &Wr_data[0]);
                    
                }
                else
                {
                    SetAde7878CheckSum(uiDataAddrSos);
                }
                return 1;
            }
            return 0;
        }
        WriteADRegResumeDataByAddrSos(uiDataAddrSos, ucDatalen, Dst);

        if((AD_VIRTUALREG_ACURRENTSAVE<=uiRegName)&&(uiRegName<=AD_VIRTUALREG_CCURRENTSAVE))
        {
            unTemp.ulData=0;
            unTemp.ucbData[0]=Dst[1];
            unTemp.ucbData[1]=Dst[0];
            if(unTemp.ulData == 0) unTemp.ulData = 1;
            uiCoefCurrentGAIN[uiRegName-AD_VIRTUALREG_ACURRENTSAVE]=unTemp.ulData;
        }
        if(uiRegName>0x1000)
        {
            uiDataAddrSos=uiDataAddrSos/4;
            if(0!=Ade7878RegCanWrite(TB_ADE7878_REG_RESUME[uiDataAddrSos].ResumeType))
            {
                if((AD_AIRMSOS!=uiRegName)&&(AD_BIRMSOS!=uiRegName)&&(AD_CIRMSOS!=uiRegName))
                {
                    WriteADReg(Dst, uiRegName, ucDatalen);
                }
                else
                {
                    if(AD_AIRMSOS==uiRegName) 
                    {
                        unTemp.ucbData[0]=Dst[3];
                        unTemp.ucbData[1]=Dst[2];
                        unTemp.ucbData[2]=Dst[1];
                        unTemp.ucbData[3]=Dst[0];
                        ulCoefCurrentRMSOS[0]=(0xFFFF&(~(unTemp.ulData)+1))<<7;
                    }
                    if(AD_BIRMSOS==uiRegName)
                    {
                        unTemp.ucbData[0]=Dst[3];
                        unTemp.ucbData[1]=Dst[2];
                        unTemp.ucbData[2]=Dst[1];
                        unTemp.ucbData[3]=Dst[0];
                        ulCoefCurrentRMSOS[1]=(0xFFFF&(~(unTemp.ulData)+1))<<7;
                    }
                    if(AD_CIRMSOS==uiRegName)
                    {
                        unTemp.ucbData[0]=Dst[3];
                        unTemp.ucbData[1]=Dst[2];
                        unTemp.ucbData[2]=Dst[1];
                        unTemp.ucbData[3]=Dst[0];
                        ulCoefCurrentRMSOS[2]=(0xFFFF&(~(unTemp.ulData)+1))<<7;
                    }
                }
            }
        }
        return 1;
    }
    return 0;
}

void InitAD7878PinReset(void)
{
#if 0    
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = (AD7878A_CS | AD7878A_DIN | AD7878A_CLK);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(AD7878PORTA, &GPIO_InitStructure);
    GPIO_ResetBits(AD7878PORTA,AD7878A_CS);
    GPIO_ResetBits(AD7878PORTA,AD7878A_DIN);
    GPIO_ResetBits(AD7878PORTA,AD7878A_CLK);

    GPIO_InitStructure.GPIO_Pin = (AD7878A_DO);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(AD7878PORTA, &GPIO_InitStructure);    
    
#if(BOARD_LOWCOST != HARD_WARE)
    GPIO_InitStructure.GPIO_Pin = ( OUT_PM1_PIN );
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(OUT_PM1_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(OUT_PM1_PORT,OUT_PM1_PIN);
#endif  
#endif
}



// isOninit:1   上电时；0  掉电时
uchar InitADMode(uchar ucType, uchar isOninit)
{
    uchar ucAde7758Data[4];
    uchar ucTemp,ucTotal,ucDataLen;
    UN_U32_PARAM unTemp;

//    MTRACE("InitADMode\n");
	ERRTRACE("->...Init\n");
    memset((uchar *)&ulCoefCurrentRMSOS[0], 0, sizeof(ulCoefCurrentRMSOS));
    if(isOninit != GAL_YES)
    {
        isOninit = GAL_NO;
    }
    
    if(GAL_YES==ucType)
    {
        ClosePowerUpADE7758();
        SysDelayMs(6);
        if((isOninit == GAL_YES) && (IfPowerDown()))    return ADE_INIT_POWERDOWN;
        OpenPowerUpADE7758();

        if(isOninit)
        {
            SysDelayMs(16);
            if((isOninit == GAL_YES) && (IfPowerDown()))    return ADE_INIT_POWERDOWN;
            SysDelayMs(16);
            if((isOninit == GAL_YES) && (IfPowerDown()))    return ADE_INIT_POWERDOWN;
        }
        ClearWatchDog();
    }
    InitAD7878();
/*---------------------计量芯片bug Start--------------------------*/
    SysDelayMs(6);
    if((isOninit == GAL_YES) && (IfPowerDown()))    return ADE_INIT_POWERDOWN;
    ucAde7758Data[0]=0x00;
    ucAde7758Data[1]=0x00;
//	acs_write_reg(AD_CONFIG, ucAde7758Data, 2);
//	sleep(20);
    WriteADReg(&ucAde7758Data[0],AD_CONFIG,2);
    ucAde7758Data[0]=0x02;
    WriteADReg(&ucAde7758Data[0],AD_CONFIG2,1);
//	exit(0);
    SysDelayMs(16);
    if((isOninit == GAL_YES) && (IfPowerDown()))    return ADE_INIT_POWERDOWN;
    SysDelayMs(16);
    if((isOninit == GAL_YES) && (IfPowerDown()))    return ADE_INIT_POWERDOWN;
    ClearWatchDog();
    
    ucVoltageLowStatusABC=0;
    r7758mode_ok=0;
    status_5460_0=0;
    status_5460_1=0;
    spi_status=0;
    ucAde7758Data[0]=0;
    uiPluseRestTimes=0;
    ucAde7878CfModeTime=0;
    ucAde7758Data[0]=0X00;
    ucAde7758Data[1]=0X00;
//    WriteADReg(&ucAde7758Data[0],AD_RUN,2);

    ucAde7758Data[0]=0XAD;
    WriteADReg(&ucAde7758Data[0],AD_HIDE_KEY,1);

    ucAde7758Data[0]=0X01;
    WriteADReg(&ucAde7758Data[0],AD_MODE_CONTROL,1);

    ucAde7758Data[0]=0X00;
    WriteADReg(&ucAde7758Data[0],AD_HIDE_KEY,1);
/*---------------------计量芯片bug  End--------------------------*/

//  ucAde7758Data[0]=0X00;
//  ucAde7758Data[1]=0X00;
//  WriteADReg(&ucAde7758Data[0],AD_RUN,2);
/*--------------------- 计量参数恢复Start--------------------------*/
    ucTotal=(sizeof(TB_ADE7878_REG_RESUME)/sizeof(ST_ADE7878_REG_PARAM));
	ERRTRACE("->...readADReg before\n");
    for(ucTemp=0;ucTemp<ucTotal;ucTemp++)
    {
        ucDataLen=Ade7878RegCanWrite(TB_ADE7878_REG_RESUME[ucTemp].ResumeType);
        if(AD_CFMODE==TB_ADE7878_REG_RESUME[ucTemp].RegName)
        {
            ucDataLen=0;
        }
        if(AD_RUN==TB_ADE7878_REG_RESUME[ucTemp].RegName)
        {
            ucDataLen=0;
        }
        if(GAL_NO==TB_ADE7878_REG_RESUME[ucTemp].CheckType)
        {
            ucDataLen=0;
        }
        if(0!=ucDataLen)
        {
            ReadADRegResumeData(TB_ADE7878_REG_RESUME[ucTemp].RegName,ucDataLen,&ucAde7758Data[0]);
            WriteADReg(&ucAde7758Data[0],TB_ADE7878_REG_RESUME[ucTemp].RegName,ucDataLen);
        }
        if((isOninit == GAL_YES) && (IfPowerDown()))    return ADE_INIT_POWERDOWN;
    }

	ERRTRACE("->...readADReg after\n");
/*---------------------计量芯片bug  Start--------------------------*/
// 须连续写8次才能保证把出错概率降到最低
    for(ucTemp=0;ucTemp<8;ucTemp++)
    {
        ReadADRegResumeData(AD_CF1DEN,2,&ucAde7758Data[0]);
        WriteADReg(&ucAde7758Data[0],AD_CF1DEN,2);
        usleep(1000);// 1ms
        ReadADRegResumeData(AD_CF2DEN,2,&ucAde7758Data[0]);
        WriteADReg(&ucAde7758Data[0],AD_CF2DEN,2);
        usleep(1000);// 1ms
        ReadADRegResumeData(AD_CF3DEN,2,&ucAde7758Data[0]);
        WriteADReg(&ucAde7758Data[0],AD_CF3DEN,2);
        if((isOninit == GAL_YES) && (IfPowerDown()))    return ADE_INIT_POWERDOWN;
    }
/*---------------------计量芯片bug  End--------------------------*/
    
    // AA 启动AD 计量芯片 AA
    ReadADRegResumeData(AD_RUN,2,&ucAde7758Data[0]);
	ERRTRACE("->...AD_RUN:%02x %02x\n",ucAde7758Data[0],ucAde7758Data[1]);
//
  //  WriteADReg(&ucAde7758Data[0],AD_RUN,2);
/*---------------------计量芯片bug--------------------------*/
// 此时写一下参数到7858会有问题，故写放到内存
    for(ucTemp=0;ucTemp<3;ucTemp++)
    {
        if(0==ucTemp)
        {
            ReadADRegResumeData(AD_AIRMSOS,4,&ucAde7758Data[0]);
        }
        else
        {
            if(1==ucTemp)
            {
                ReadADRegResumeData(AD_BIRMSOS,4,&ucAde7758Data[0]);
            }
            else
            {
                ReadADRegResumeData(AD_CIRMSOS,4,&ucAde7758Data[0]);
            }
        }
        unTemp.ucbData[0]=ucAde7758Data[3];
        unTemp.ucbData[1]=ucAde7758Data[2];
        unTemp.ucbData[2]=ucAde7758Data[1];
        unTemp.ucbData[3]=ucAde7758Data[0];
        ulCoefCurrentRMSOS[ucTemp]=(0xFFFF&(~(unTemp.ulData)+1))<<7;
        if((isOninit == GAL_YES) && (IfPowerDown()))    return ADE_INIT_POWERDOWN;
    }

    for(ucTemp=0;ucTemp<3;ucTemp++)
    {
        ReadADRegResumeData(AD_VIRTUALREG_ACURRENTSAVE+ucTemp,2,&ucAde7758Data[0]);
        unTemp.ulData=0;
        unTemp.ucbData[0]=ucAde7758Data[1];
        unTemp.ucbData[1]=ucAde7758Data[0];
        if(unTemp.ulData == 0) unTemp.ulData = 1;
        uiCoefCurrentGAIN[ucTemp]=unTemp.ulData;
        if((isOninit == GAL_YES) && (IfPowerDown()))    return ADE_INIT_POWERDOWN;
    }

//
    return ADE_INIT_SUCC;
}

uchar CheckADE7758(void)
{
#define CON_ADE7878_CHECK_MAX_LEN 3
    uchar ucAde7758Data[4];
    uchar ucAde7878Read[4];
    uchar ucTemp,ucTotal,ucDataLen;
    UN_U32_PARAM unTemp;
    uchar ucCheckPoint;
    static uchar uCheckStatus;  //分时间片校验计量参数的关键，
    if(ucAde7878CfModeTime<CON_ADE7878_CFMODE_TIME_MAX)
    {
        return 0;
    }
    ucCheckPoint=uCheckStatus*CON_ADE7878_CHECK_MAX_LEN;
    ucTotal=(sizeof(TB_ADE7878_REG_RESUME)/sizeof(ST_ADE7878_REG_PARAM));
    if(ucCheckPoint>=ucTotal)
    {
        ucCheckPoint=0;
        uCheckStatus=0;
    }
    ucTemp=0;
    for(;ucCheckPoint<ucTotal;ucCheckPoint++)
    {
        ucDataLen=Ade7878RegCanWrite(TB_ADE7878_REG_RESUME[ucCheckPoint].ResumeType);

        if(GAL_NO==TB_ADE7878_REG_RESUME[ucCheckPoint].CheckType)
        {
            ucDataLen=0;
        }
        if(0!=ucDataLen)
        {
           ReadADRegResumeData(TB_ADE7878_REG_RESUME[ucCheckPoint].RegName,ucDataLen,&ucAde7758Data[0]);
           ReadADReg(TB_ADE7878_REG_RESUME[ucCheckPoint].RegName,ucDataLen,&ucAde7878Read[0]);
            if(1==ucDataLen)
            {
                if((ucAde7878Read[0]!=ucAde7758Data[0]))
                {
                    return 1;
                }
            }
            else if (2==ucDataLen)
            {
                if((ucAde7878Read[0]!=ucAde7758Data[0])||(ucAde7878Read[1]!=ucAde7758Data[1]))
                {
                    return 1;
                }
            }
            else
            {
                if((ucAde7878Read[3]!=ucAde7758Data[3])||(ucAde7878Read[1]!=ucAde7758Data[1])
                    ||(ucAde7878Read[2]!=ucAde7758Data[2]))
                {
                    return 1;
                }
            }
        }
        ucTemp++;
        if(ucTemp>CON_ADE7878_CHECK_MAX_LEN)
        {
            break;
        }
    }

    
    for(ucTemp=0;ucTemp<3;ucTemp++)
    {
        if(0==ucTemp)
        {
            ReadADRegResumeData(AD_AIRMSOS,4,&ucAde7758Data[0]);
        }
        else
        {
            if(1==ucTemp)
            {
                ReadADRegResumeData(AD_BIRMSOS,4,&ucAde7758Data[0]);
            }
            else
            {
                ReadADRegResumeData(AD_CIRMSOS,4,&ucAde7758Data[0]);
            }
        }
        unTemp.ucbData[0]=ucAde7758Data[3];
        unTemp.ucbData[1]=ucAde7758Data[2];
        unTemp.ucbData[2]=ucAde7758Data[1];
        unTemp.ucbData[3]=ucAde7758Data[0];
        ulCoefCurrentRMSOS[ucTemp]=(0xFFFF&(~(unTemp.ulData)+1))<<7;
    }

    for(ucTemp=0;ucTemp<3;ucTemp++)
    {
        ReadADRegResumeData(AD_VIRTUALREG_ACURRENTSAVE+ucTemp,2,&ucAde7758Data[0]);
        unTemp.ulData=0;
        unTemp.ucbData[0]=ucAde7758Data[1];
        unTemp.ucbData[1]=ucAde7758Data[0];
        if(unTemp.ulData == 0) unTemp.ulData = 1;
        uiCoefCurrentGAIN[ucTemp]=unTemp.ulData;
    }
    
    uCheckStatus++;

    return 0;
}

uchar GetClacPlusePowerCoef(void)

{
    uchar ucAde7758Data[4];
    u16 uiAdeData1,uiAdeData2;
    if(1==ReadADRegResumeData(AD_CF1DEN, 2, &ucAde7758Data[0]))
    {
        uiAdeData1=ucAde7758Data[0]*256+ucAde7758Data[1];
    }else
    {
    	return 1;
    }
    if(1==ReadADRegResumeData(AD_CF1DEN, 2, &ucAde7758Data[0]))
    {
        uiAdeData2=ucAde7758Data[0]*256+ucAde7758Data[1];
    }else
    {
    	return 1;
    }
    if(uiAdeData1==uiAdeData2)
        ulClacPlusePowerCoef=uiAdeData1*CON_CLAC_PLUSE_POWER_COEF;
    return 1;
}

void CosDataFromKwKva(ukw,ukva,point)
ulong ukw,ukva;
uchar *point;
{
    ulong l,lkw,lkva;
    ulong a[2];
    lkw=ukw;
    lkva=ukva;
    if(lkva<700)
    {
        lkva=1;
        lkw=1;
    }
    else
    {
        if(lkw>=lkva)
        {
            lkw=lkva;
        }
    }
    if(lkw<=lkva)
    {
        a[0]=(100*lkw)/lkva;
        l=(100*lkw)%lkva;
        a[1]=(10000*l)/lkva;
        a[0]=10000*a[0]+a[1];
        a[0]=a[0]*10;
        LongToData4BCD(a[0],point);
    }   
}
void CosDataFromKwKvar(ukw,ukvar,point)
ulong ukw,ukvar;
uchar *point;
{
    if((ukw>0x7fff)||(ukvar>0x7fff))
    {
        ukw=ukw/8;
        ukvar=ukvar/8;
        if((ukw>0x7fff)||(ukvar>0x7fff))
        {
            ukw=ukw/8;
            ukvar=ukvar/8;
            if((ukw>0x7fff)||(ukvar>0x7fff))
            {
                ukw=ukw/8;
                ukvar=ukvar/8;
            }
        }
    }
    CosDataFromKwKva(ukw, SqrtFromX2Y2(ukw, ukvar), point);
}

void CosDataFromKwKva_pre(ulong ukw,ulong ukva,uchar *point)
{
    if(ukw>0x7fff)
    {
        ukw=ukw/8;
        ukva=ukva/8;
        if(ukw>0x7fff)
        {
            ukw=ukw/8;
            ukva=ukva/8;
            if(ukw>0x7fff)
            {
                ukw=ukw/8;
                ukva=ukva/8;
            }
        }
    }
    CosDataFromKwKva(ukw, ukva, point);
}

ulong SqrtFromX2Y2(x,y)
ulong x,y;
{
    u16 z_max,z_min,z;
    uchar l;
    ulong value1,value2;
    z_max=0xffff;
    z_min=0;
    z=0x8000;
    value1=x;
    value1=value1*value1;
    value2=(uiClacMeterKwCoef*y)/uiClacMeterKvarCoef; 
    value2=value2*value2;
    value1=value1+value2;  
    for(l=0;l<18;l++)
    {
        value2=z;
        value2=value2*value2;
        if(value2>value1)
        {
            z_max=z;
            z=(z/2)+(z_min/2); 
        }
        else
        {
            if(value2<value1)
            {
                z_min=z;
                z=(z/2)+(z_max/2);
            }
            else
            {
                break;
            }
        }
    }
    value1=z;
    return value1;
 }

// 将计量芯片得到的电量值转换成16进制值
void ChangeCoefToKw(ulong *point)
{
    ulLong ullTemp;
    
    ullTemp=(*point);
    ullTemp=ullTemp*1000*ucClacMeterKwCoefMul/ucClacMeterKwCoefDiv;
    ullTemp=ullTemp/uiClacMeterKwCoef;
    *point=(ulong)ullTemp;
    /*    
        ulong b_kw,b_div,b_div_add,ulTemp;
        b_kw=uiClacMeterKwCoef;
        
        b_div=ucClacMeterKwCoefDiv;
        b_div_add=ucClacMeterKwCoefMul;
        ulTemp=(*point)%b_div;
        (*point)=(*point)/b_div;
        *point=(*point)*((1000*b_div_add)/(b_kw))+(((*point)*((1000*b_div_add)%(b_kw)))/(b_kw)); 
        ulTemp=ulTemp*1000*b_div_add/b_kw;
        *point=(*point)+(ulTemp/b_div);
    */
    
    //*point=(*point)*((100000*b_div_add)/(b_div*b_kw))+(((*point)*((100000*b_div_add)%(b_div*b_kw)))/(b_div*b_kw)); 
    //*point=(((*point)*b_div_add)/(b_div*b_kw))*1000

}

void ClrCurrentADE7758Data(uchar ucMeterClr)
{
    u16 l;
    if(ucMeterClr == GAL_YES)
    {
        //停抄电池15分钟检测一次,所以停抄电池电压暂不清0
        for(l=RAM_CURRENT_DATA_START;l<(RAM_CURRENT_DATA_END-2);l++)
            RAM[l]=0;
    }
    else
    {
        for(l=RAM_CURRENT_DATA_START;l<(RAM_CURRENT_DATA_END);l++)
            RAM[l]=0;
    }
    for(l=0;l<(AD_VIRTUALREG_TEMPR+1);l++)
        ulPowerBuffer[l]=0;
    RAM[RAM_CURRENT_METER_STATUS01+0]=0x0E&RAM[RAM_CURRENT_METER_STATUS01+0];
    RAM[RAM_CURRENT_METER_STATUS01+1]=0x00;
    
    RAM[RAM_CURRENT_METER_STATUS02+0]=0x00;
    RAM[RAM_CURRENT_METER_STATUS02+1]=0x00;
    
//  RAM[RAM_CURRENT_METER_STATUS03+0]=0x00;
//  RAM[RAM_CURRENT_METER_STATUS03+1]=0x00;
    
    RAM[RAM_CURRENT_METER_STATUS04+0]=0x00;
    RAM[RAM_CURRENT_METER_STATUS04+1]=0x00;
    RAM[RAM_CURRENT_METER_STATUS05+0]=0x00;
    RAM[RAM_CURRENT_METER_STATUS05+1]=0x00;
    RAM[RAM_CURRENT_METER_STATUS06+0]=0x00;
    RAM[RAM_CURRENT_METER_STATUS06+1]=0x00;
    //l=FLG_SYSTEMPOWER_STATUS;
    RAM[RAM_CURRENT_METER_STATUS07+0]=0x00;
    RAM[RAM_CURRENT_METER_STATUS07+1]=0x00;
    //FLG_SYSTEMPOWER_STATUS=l;
    //l=FLG_ALL_LOSSVOLTAGE_STATUS;
#if(CONFIG_METER_EVENT_COVEROPEN_SPECIAL_MODE != CONFIG_METER_EVENT_COVEROPEN_SPECIAL_MODE_DISABLE) 
    RAM[RAM_CURRENT_METER_STATUS_OTHER+0]=0xf0&RAM[RAM_CURRENT_METER_STATUS_OTHER+0];
#else
    RAM[RAM_CURRENT_METER_STATUS_OTHER+0]=0x00;
#endif
    
    RAM[RAM_CURRENT_METER_STATUS_OTHER+1]=0x00;
    
    RAM[RAM_CURRENT_METER_STATUS_DEMANDOVER+0]=0x00;
    RAM[RAM_CURRENT_METER_STATUS_DEMANDOVER+1]=0x00;
    //FLG_ALL_LOSSVOLTAGE_STATUS=l;
    if(ucMeterClr == GAL_YES)
    {
        //总清时，正好清掉，事件可以重新计
        fCoverOpenStatusClr;
        fTerminalOpenStatusClr;
        fAllLostVoltageStatusClr;
#if(CONFIG_METER_AUX_MODE_ENABLE == CONFIG_METER_AUX_MODE)
        fPowerDownStatusClr;
        fAuxPowerDownStatusClr;
#endif     
        //fProgramRecordStatusClr;
    }
    else
    {
        //DISABLE:就算停电结束了，BAKRAM照样清了，所以跟从没关系
        //NOSTOP:状态跟从停电前数据BAKRAM
        //RECORD:状态跟从掉电前或期间数据BAKRAM
        FLG_TERMINAL_OPEN_STATUS=fGetTerminalOpenStatus;
        FLG_COVER_OPEN_STATUS=fGetCoverOpenStatus;
        FLG_ALL_LOSSVOLTAGE_STATUS=fGetAllLostVoltageStatus;
#if(CONFIG_METER_AUX_MODE_ENABLE == CONFIG_METER_AUX_MODE)
        FLG_SYSTEMPOWER_STATUS = fGetPowerDownStatus;
        FLG_ACPOWER_STATUS = fGetAuxPowerDownStatus;
#endif        
        //FLG_PROGRAM_OPEN_STATUS = fGetProgramRecordStatus;
    }
}

void ModeAde7878PowerOn(void)
// AA  本函数用来上电瞬间判断各个象限使用  AA
{
    uchar ucAde7758Data[4];
    uchar m,n,ucReadADRegOkNum;
    UN_LONG l7758;
    uchar ucTempAde7878Q;
    
    ucReadADRegOkNum = 0;
    m=sizeof(ulPowerBuffer);
    memset((uchar *)&ulPowerBuffer[0],0x00, m);
    for(n=AD_VIRTUALREG_AKW;n<AD_VIRTUALREG_ALLKW;n++)
    {
        // 3P3W --> all B phase clr
        if(PROGFUNCTION_TYPE_METER_TYPE==METERTYPE_3_3)
        {
            if( (n==AD_VIRTUALREG_BKW) || (n==AD_VIRTUALREG_BKVAR) || (n==AD_VIRTUALREG_BKVA))
            {
                ulPowerBuffer[n] = 0;
                ucReadADRegOkNum++; //skip to read ADE7758
                continue;
            }
        }
        if(1==ReadADReg(TB_ADE7878_ENERGY[n],4, &ucAde7758Data[0]))
        {
            ucReadADRegOkNum++;
            //l7758.l=0;
            REV_7858_4BYTES(l7758.c, ucAde7758Data);
            if((l7758.l<CON_REVERSE_POWER_MIN_CONDITION_F)||(l7758.l>CON_REVERSE_POWER_MIN_CONDITION_R))
            {
                l7758.l=0;
            }
            if(l7758.c[2]>0x7f)
            {
                l7758.c[3]=0xff;
            }
            ulPowerBuffer[n]=l7758.l;
        }
    }

// AA------------------------电流有效值计算 ---->Start ----AA           
    for(n=0;n<3;n++)
    {
        // 3P3W --> all B phase clr
        if((PROGFUNCTION_TYPE_METER_TYPE==METERTYPE_3_3) && (n==AD_VIRTUALREG_B) )
        {
            ulNowCurrent[n]=0;
            memset(&RAM[RAM_CURRENT_I_B], 0x00, 4);
            
            ucReadADRegOkNum++; //skip to read ADE7758
            continue;
        }
        if(1==ReadADReg(TB_ADE7878_CURRENT_RMS[n],4, &ucAde7758Data[0]))
        {
            ucReadADRegOkNum++;
            //l7758.l=0;
            REV_7858_4BYTES(l7758.c, ucAde7758Data);

            if(l7758.l>=0x7f0000)
            {
                l7758.l=0;
            }
            if(l7758.l<0x07fff)
            {
                l7758.l=l7758.l*l7758.l-ulCoefCurrentRMSOS[n];
                if(0xff==l7758.c[3])
                {
                    l7758.l=0;
                }
                else
                {
                    l7758.l=Sqrt32to16(l7758.l);
                }
            }

            if(CURRENT_TYPE_BIG == CURRENT_TYPE)
            {
                l7758.l=(500*(l7758.l/uiCoefCurrentGAIN[n]))+((500*(l7758.l%uiCoefCurrentGAIN[n]))/uiCoefCurrentGAIN[n]);
            }
            else
            {
                l7758.l=(50*(l7758.l/uiCoefCurrentGAIN[n]))+((50*(l7758.l%uiCoefCurrentGAIN[n]))/uiCoefCurrentGAIN[n]);
            }
            // 潜动措施
            if(l7758.l<uiMeter0d001PerCurrent)
            {
                l7758.l=0;
                ulPowerBuffer[AD_VIRTUALREG_AKVA+n]=0;
                ulPowerBuffer[AD_VIRTUALREG_AKVAR+n]=0;
                ulPowerBuffer[AD_VIRTUALREG_AKW+n]=0;
            }
        }
    }

    // 3P3W --> all B phase clr
    if(PROGFUNCTION_TYPE_METER_TYPE==METERTYPE_3_3)
    {
        ulPowerBuffer[AD_VIRTUALREG_BKW]=0; 
        ulPowerBuffer[AD_VIRTUALREG_BKVAR]=0;
        ulPowerBuffer[AD_VIRTUALREG_BKVA]=0;
    }


    // kw add
    ucTempAde7878Q=0;
    l7758.l=0;  
    for(n=0;n<3;n++)
    { 
        l7758.l=l7758.l+ulPowerBuffer[n+AD_VIRTUALREG_AKW];
    } 
    if(l7758.c[3]>0x7f)
    {
        l7758.l=~l7758.l +1;
        {
            ucTempAde7878Q=ucTempAde7878Q|0x80;
        }
    }
    l7758.l=0;  
    for(n=0;n<3;n++)
    { 
        l7758.l=l7758.l+ulPowerBuffer[n+AD_VIRTUALREG_AKVAR];
    } 
    if(l7758.c[3]>0x7f)
    {
        l7758.l=~l7758.l +1;
        {
            ucTempAde7878Q=ucTempAde7878Q|0x8;
        }
    }
    for(n=0;n<3;n++)
    {   
        l7758.l=ulPowerBuffer[n+AD_VIRTUALREG_AKW];
        if(l7758.c[3]>0x7f)
        {
            l7758.l=~l7758.l +1;
            {
                ucTempAde7878Q=ucTempAde7878Q|BitValue(n+4);
            }
        }
        
    }
    for(n=0;n<3;n++)
    {   
        l7758.l=ulPowerBuffer[n+AD_VIRTUALREG_AKVAR];
        if(l7758.c[3]>0x7f)
        {
            l7758.l=~l7758.l +1;
            {
                ucTempAde7878Q=ucTempAde7878Q|BitValue(n+0);
            }
        }
        
    }

    // AA   总 的象限判断  AA 
    n=ucTempAde7878Q&0x88;
    ucStatusPowerQuadrantUseZ=n;
    status_5460_0=(status_5460_0&0x77)|n;   
    switch(ucStatusPowerQuadrantUseZ)
    {
        case 0x08:
            QUADRANT_Z=QUADRANT_FOUR;
            break;
        case 0x80:
            QUADRANT_Z=QUADRANT_TWO;
            break;
        case 0x88:
            QUADRANT_Z=QUADRANT_THREE;
            break;
        default:
            QUADRANT_Z=QUADRANT_ONE;
            break;
    }
    // AA   A相 的象限判断  AA 
    n=ucTempAde7878Q&0x11;
    ucStatusPowerQuadrantUseA=n;
    status_5460_0=(status_5460_0&0xEE)|n;   
    switch(ucStatusPowerQuadrantUseA)
    {
        case 0x01:
            QUADRANT_A=QUADRANT_FOUR;
            break;
        case 0x10:
            QUADRANT_A=QUADRANT_TWO;
            break;
        case 0x11:
            QUADRANT_A=QUADRANT_THREE;
            break;
        default:
            QUADRANT_A=QUADRANT_ONE;
            break;
    }
    // AA   B相 的象限判断  AA 
    n=ucTempAde7878Q&0x22;
    ucStatusPowerQuadrantUseB=n;
    status_5460_0=(status_5460_0&0xDD)|n;   
    switch(ucStatusPowerQuadrantUseB)
    {
        case 0x02:
            QUADRANT_B=QUADRANT_FOUR;
            break;
        case 0x20:
            QUADRANT_B=QUADRANT_TWO;
            break;
        case 0x22:
            QUADRANT_B=QUADRANT_THREE;
            break;
        default:
            QUADRANT_B=QUADRANT_ONE;
            break;
    }
    // AA   C相 的象限判断  AA 
    n=ucTempAde7878Q&0x44;
    ucStatusPowerQuadrantUseC=n;
    status_5460_0=(status_5460_0&0xBB)|n;   
    switch(ucStatusPowerQuadrantUseC)
    {
        case 0x04:
            QUADRANT_C=QUADRANT_FOUR;
            break;
        case 0x40:
            QUADRANT_C=QUADRANT_TWO;
            break;
        case 0x44:
            QUADRANT_C=QUADRANT_THREE;
            break;
        default:
            QUADRANT_C=QUADRANT_ONE;
            break;
    }
    if(12!=ucReadADRegOkNum)
    {
        status_5460_0=0;
        ucStatusPowerQuadrantUseA=0x00;
        ucStatusPowerQuadrantUseB=0x00;
        ucStatusPowerQuadrantUseC=0x00;
        ucStatusPowerQuadrantUseZ=0x00;
        ucStatusPowerQuadrantUseZ=QUADRANT_ONE;
        ucStatusPowerQuadrantUseA=QUADRANT_ONE;
        ucStatusPowerQuadrantUseB=QUADRANT_ONE;
        ucStatusPowerQuadrantUseC=QUADRANT_ONE;
    }
    memset(&ulPowerBuffer[0], 0x00, sizeof(ulPowerBuffer));
}

void ModeADE7758(uchar ucStep)
{
    UN_LONG l7758;
    uchar ucAde7758Data[4];
    uchar m,n,ucReadADRegOkNum;
    ulong lTemp,ulMinVoltage;
    static uchar ucTempAde7878Q;

    ucReadADRegOkNum=0;
    //if(ucModeAde7758Second!=RSOFT_RTC_SECOND)
    if(ucStep == 0)
    {
        //ucModeAde7758Second=RSOFT_RTC_SECOND;
        if(ucAde7878CfModeTime <= 100)
        {
            ucAde7878CfModeTime++;
        }
        
        if(CON_ADE7878_CFMODE_TIME_DEAL==ucAde7878CfModeTime)  /* 计量芯片bug  Start  须上电2秒后打开脉冲 */
        {
            // AA 启动脉冲输出 AA
            ReadADRegResumeData(AD_CFMODE,2,&ucAde7758Data[0]);
            WriteADReg(&ucAde7758Data[0],AD_CFMODE,2);
        }

        // AA   功率能量数据处理    AA
        for(n=AD_VIRTUALREG_AKW;n<AD_VIRTUALREG_ALLKW;n++)
        {
            // 3P3W --> all B phase clr
            if(PROGFUNCTION_TYPE_METER_TYPE==METERTYPE_3_3)
            {
                if( (n==AD_VIRTUALREG_BKW) || (n==AD_VIRTUALREG_BKVAR) || (n==AD_VIRTUALREG_BKVA))
                {
                    ulPowerBuffer[n] = 0;
                    ucReadADRegOkNum++; //skip to read ADE7758
                    continue;
                }
            }
            if(1==ReadADReg(TB_ADE7878_ENERGY[n],4, &ucAde7758Data[0]))
            {
                ucReadADRegOkNum++;

                //l7758.l=0;
                REV_7858_4BYTES(l7758.c, ucAde7758Data);
                
                if((l7758.l<CON_REVERSE_POWER_MIN_CONDITION_F)||(l7758.l>CON_REVERSE_POWER_MIN_CONDITION_R))
                {
                    l7758.l=0;
                }
                ulPowerBuffer[n]=l7758.l;
            }
        }

// AA------------------------电流有效值计算 ---->Start ----AA           
        for(n=AD_VIRTUALREG_A; n<=AD_VIRTUALREG_C; n++)
        {
            // 3P3W --> all B phase clr
            if((PROGFUNCTION_TYPE_METER_TYPE==METERTYPE_3_3) && (n==AD_VIRTUALREG_B) )
            {
                ulNowCurrent[n]=0;
                memset(&RAM[RAM_CURRENT_I_B], 0x00, 4);
                
                ucReadADRegOkNum++; //skip to read ADE7758
                continue;
            }
            if(1==ReadADReg(TB_ADE7878_CURRENT_RMS[n],4, &ucAde7758Data[0]))
            {
                ucReadADRegOkNum++;
                //l7758.l=0;
                REV_7858_4BYTES(l7758.c, ucAde7758Data);

                if(l7758.l>=0x7f0000)
                {
                    l7758.l=0;
                }
                
                /*---------------------计量芯片bug  Start--------------------------*/
                if(l7758.l < 0x07fff) //值小于0x7fff时值不准，需要调整
                {
                    l7758.l = l7758.l*l7758.l - ulCoefCurrentRMSOS[n];
                    if(0xff==l7758.c[3])
                    {
                        l7758.l=0;
                    }
                    else
                    {
                        l7758.l=Sqrt32to16(l7758.l);
                    }
                }
                /*---------------------计量芯片bug  End--------------------------*/
                //MTRACE("0x%x, 0x%x\n", l7758.l, uiCoefCurrentGAIN[n]);
                if(CURRENT_TYPE_BIG == CURRENT_TYPE)
                {
                    l7758.l=(500*(l7758.l/uiCoefCurrentGAIN[n]))+((500*(l7758.l%uiCoefCurrentGAIN[n]))/uiCoefCurrentGAIN[n]);
                }
                else
                {
                    l7758.l=(50*(l7758.l/uiCoefCurrentGAIN[n]))+((50*(l7758.l%uiCoefCurrentGAIN[n]))/uiCoefCurrentGAIN[n]);
                }
                // 潜动措施
                if(l7758.l<uiMeter0d001PerCurrent)
                {
                    l7758.l=0;
                    ulPowerBuffer[AD_VIRTUALREG_AKVA+n]=0;
                    ulPowerBuffer[AD_VIRTUALREG_AKVAR+n]=0;
                    ulPowerBuffer[AD_VIRTUALREG_AKW+n]=0;
                }
                if(l7758.l>3000000)
                {
                    l7758.l=0;
                }
                ulNowCurrent[n]=l7758.l;
                if(ucAde7878CfModeTime >= CON_ADE7878_CFMODE_TIME_DEAL)
                {
                    LongToData4BCD(l7758.l,&RAM[RAM_CURRENT_I_A+4*n]);
                }
            }
        }
        if((QUADRANT_THREE==QUADRANT_A)||(QUADRANT_TWO==QUADRANT_A))
        {
            RAM[RAM_CURRENT_I_A+3] |=0x8;
        }

        if((QUADRANT_THREE==QUADRANT_B)||(QUADRANT_TWO==QUADRANT_B))
        {
            RAM[RAM_CURRENT_I_B+3] |=0x8;
        }
        if((QUADRANT_THREE==QUADRANT_C)||(QUADRANT_TWO==QUADRANT_C))
        {
            RAM[RAM_CURRENT_I_C+3] |=0x8;
        }
        
        if(PROGFUNCTION_TYPE_METER_TYPE==METERTYPE_3_3)
        {
            memset(&RAM[RAM_CURRENT_I_B], 0x00, 4);
        }
// AA------------------------电流有效值计算 ---->End ----AA         


        // kw add
        ucTempAde7878Q=0;
        ulPowerBuffer[AD_VIRTUALREG_TEMPF]=0;
        ulPowerBuffer[AD_VIRTUALREG_TEMPR]=0;
        for(n=0;n<3;n++)
        { 
            if(ulPowerBuffer[n+AD_VIRTUALREG_AKW]>0x7fffff) 
                ulPowerBuffer[AD_VIRTUALREG_TEMPR]=ulPowerBuffer[AD_VIRTUALREG_TEMPR]+0x1000000-ulPowerBuffer[n+AD_VIRTUALREG_AKW];
            else 
                ulPowerBuffer[AD_VIRTUALREG_TEMPF]=ulPowerBuffer[AD_VIRTUALREG_TEMPF]+ulPowerBuffer[n+AD_VIRTUALREG_AKW]; 
        } 
        if(ulPowerBuffer[AD_VIRTUALREG_TEMPR]>ulPowerBuffer[AD_VIRTUALREG_TEMPF]) 
        {
            ulPowerBuffer[AD_VIRTUALREG_ALLKW]=ulPowerBuffer[AD_VIRTUALREG_TEMPR]-ulPowerBuffer[AD_VIRTUALREG_TEMPF];
            ucTempAde7878Q=ucTempAde7878Q|0x80;
        }
        else
        {
            ulPowerBuffer[AD_VIRTUALREG_ALLKW]=ulPowerBuffer[AD_VIRTUALREG_TEMPF]-ulPowerBuffer[AD_VIRTUALREG_TEMPR]; 
        }
        // kvar add
        ulPowerBuffer[AD_VIRTUALREG_TEMPF]=0;
        ulPowerBuffer[AD_VIRTUALREG_TEMPR]=0;
        for(n=0;n<3;n++)
        { 
            if(ulPowerBuffer[n+AD_VIRTUALREG_AKVAR]>0x7fffff) 
                ulPowerBuffer[AD_VIRTUALREG_TEMPR]=ulPowerBuffer[AD_VIRTUALREG_TEMPR]+0x1000000-ulPowerBuffer[AD_VIRTUALREG_AKVAR+n];
            else
                ulPowerBuffer[AD_VIRTUALREG_TEMPF]=ulPowerBuffer[AD_VIRTUALREG_TEMPF]+ulPowerBuffer[AD_VIRTUALREG_AKVAR+n]; 
        } 
        if(ulPowerBuffer[AD_VIRTUALREG_TEMPR]>ulPowerBuffer[AD_VIRTUALREG_TEMPF]) 
        {
            ulPowerBuffer[AD_VIRTUALREG_ALLKVAR]=ulPowerBuffer[AD_VIRTUALREG_TEMPR]-ulPowerBuffer[AD_VIRTUALREG_TEMPF];
            ucTempAde7878Q=ucTempAde7878Q|0x8;
        }
        else
        {
            ulPowerBuffer[AD_VIRTUALREG_ALLKVAR]=ulPowerBuffer[AD_VIRTUALREG_TEMPF]-ulPowerBuffer[AD_VIRTUALREG_TEMPR];  
        }
        
        // kva add
        ulPowerBuffer[AD_VIRTUALREG_ALLKVA]=0;
        for(n=0;n<3;n++)
        { 
            ulPowerBuffer[AD_VIRTUALREG_ALLKVA]=ulPowerBuffer[AD_VIRTUALREG_ALLKVA]+ulPowerBuffer[AD_VIRTUALREG_AKVA+n]; 
        } 
        
        for(n=0;n<3;n++)
        {   
            // kwh
            if(ulPowerBuffer[n+AD_VIRTUALREG_AKW]>0x7fffff) 
            {
                ulPowerBuffer[n+AD_VIRTUALREG_AKW]=0x1000000-ulPowerBuffer[n+AD_VIRTUALREG_AKW];
                ucTempAde7878Q=ucTempAde7878Q|BitValue(n+4);
            }
            // kvar
            if(ulPowerBuffer[n+AD_VIRTUALREG_AKVAR]>0x7fffff) 
            {
                ulPowerBuffer[n+AD_VIRTUALREG_AKVAR]=0x1000000-ulPowerBuffer[n+AD_VIRTUALREG_AKVAR];
                ucTempAde7878Q=ucTempAde7878Q|BitValue(n+0);
            }
            // AA 如果视在的能量小于有功或者无功的能量，则调整 AA
            if(ulPowerBuffer[n+AD_VIRTUALREG_AKW]>ulPowerBuffer[n+AD_VIRTUALREG_AKVA])
            {
                ulPowerBuffer[n+AD_VIRTUALREG_AKVA]=ulPowerBuffer[n+AD_VIRTUALREG_AKW];
            }
            if(ulPowerBuffer[n+AD_VIRTUALREG_AKVAR]>ulPowerBuffer[n+AD_VIRTUALREG_AKVA])
            {
                ulPowerBuffer[n+AD_VIRTUALREG_AKVA]=ulPowerBuffer[n+AD_VIRTUALREG_AKVAR];
            }
        }
        // AA 如果视在的能量小于有功或者无功的能量，则调整 AA
        if(ulPowerBuffer[AD_VIRTUALREG_ALLKW]>ulPowerBuffer[AD_VIRTUALREG_ALLKVA])
        {
            ulPowerBuffer[AD_VIRTUALREG_ALLKVA]=ulPowerBuffer[AD_VIRTUALREG_ALLKW];
        }
        if(ulPowerBuffer[AD_VIRTUALREG_ALLKVAR]>ulPowerBuffer[AD_VIRTUALREG_ALLKVA])
        {
            ulPowerBuffer[AD_VIRTUALREG_ALLKVA]=ulPowerBuffer[AD_VIRTUALREG_ALLKVAR];
        }
        if(ucReadADRegOkNum==12) 
        {
            spi_status=GAL_YES;
            r7758mode_ok=GAL_YES;
        }
        else 
        {
            spi_status=GAL_NO; 
            r7758mode_ok=GAL_NO;
        }
    }
    //if((GAL_NO==ucSystemBusy)&&(ucModeAde7758KwClalSecond!=RSOFT_RTC_SECOND))
    if(ucStep == 1)
    {
        //ucModeAde7758KwClalSecond=RSOFT_RTC_SECOND;
        if(ucAde7878CfModeTime<CON_ADE7878_CFMODE_TIME_DEAL)
            return;
// AA------------------------功率计算部分 ---->Start ----AA     
        //  AA  有功功率  AA
        for(n=0;n<3;n++)
        {
            lTemp=ulPowerBuffer[AD_VIRTUALREG_AKW+n];
            ChangeCoefToKw(&lTemp); 
            LongToData4BCD(lTemp,&RAM[RAM_CURRENT_KW_A+4*n]);
        }
        lTemp=ulPowerBuffer[AD_VIRTUALREG_ALLKW];
        ChangeCoefToKw(&lTemp); 
        LongToData4BCD(lTemp,&RAM[RAM_CURRENT_KW_ALL]);
        //  AA  无功功率  AA
        for(n=0;n<3;n++)
        {
            lTemp=ulPowerBuffer[AD_VIRTUALREG_AKVAR+n];
            ChangeCoefToKw(&lTemp);
            LongToData4BCD(lTemp,&RAM[RAM_CURRENT_KVAR_A+4*n]); 
        }
        lTemp=ulPowerBuffer[AD_VIRTUALREG_ALLKVAR];
        ChangeCoefToKw(&lTemp);  
        LongToData4BCD(lTemp,&RAM[RAM_CURRENT_KVAR_ALL]);
        //  AA  视在功率  AA
        for(n=0;n<3;n++)
        {
            lTemp=ulPowerBuffer[AD_VIRTUALREG_AKVA+n];
            ChangeCoefToKw(&lTemp);
            LongToData4BCD(lTemp,&RAM[RAM_CURRENT_KVA_A+4*n]); 
        }
        lTemp=ulPowerBuffer[AD_VIRTUALREG_ALLKVA];
        ChangeCoefToKw(&lTemp);  
        LongToData4BCD(lTemp,&RAM[RAM_CURRENT_KVA_ALL]);
// AA------------------------功率计算部分 ---->End ----AA       

// AA------------------------功率因数计算部分 ---->Start ----AA
        // AA  A相功率因数计算  AA
        CosDataFromKwKvar(ulPowerBuffer[AD_VIRTUALREG_AKW], ulPowerBuffer[AD_VIRTUALREG_AKVAR], &RAM[RAM_CURRENT_FACTOR_A]);
        // AA  B相功率因数计算  AA
        CosDataFromKwKvar(ulPowerBuffer[AD_VIRTUALREG_BKW], ulPowerBuffer[AD_VIRTUALREG_BKVAR], &RAM[RAM_CURRENT_FACTOR_B]);
        // AA  C相功率因数计算  AA
        CosDataFromKwKvar(ulPowerBuffer[AD_VIRTUALREG_CKW], ulPowerBuffer[AD_VIRTUALREG_CKVAR], &RAM[RAM_CURRENT_FACTOR_C]);
        // AA  总功率因数计算  AA
        //CosDataFromKwKvar(ulPowerBuffer[AD_VIRTUALREG_ALLKW], ulPowerBuffer[AD_VIRTUALREG_ALLKVAR], &RAM[RAM_CURRENT_FACTOR_ALL]);
		CosDataFromKwKva_pre(ulPowerBuffer[AD_VIRTUALREG_ALLKW], ulPowerBuffer[AD_VIRTUALREG_ALLKVA], &RAM[RAM_CURRENT_FACTOR_ALL]);
// AA------------------------功率因数计算部分 ---->End ----AA

// AA------------------------总和各个分相的象限判断部分 ---->Start ----AA           
        // AA   总 的象限判断  AA 
        n=ucTempAde7878Q&0x88;
        if(n==ucStatusPowerQuadrantUseZ)
        {
            if(ucStatusPowerQuadrantTimeZ<10)
                ucStatusPowerQuadrantTimeZ++;
            if(ucStatusPowerQuadrantTimeZ>=CON_QUADRANT_CHANGETIME)
            {
                status_5460_0=(status_5460_0&0x77)|n;   
                switch(ucStatusPowerQuadrantUseZ)
                {
                    case 0x08:
                        QUADRANT_Z=QUADRANT_FOUR;
                        break;
                    case 0x80:
                        QUADRANT_Z=QUADRANT_TWO;
                        break;
                    case 0x88:
                        QUADRANT_Z=QUADRANT_THREE;
                        break;
                    default:
                        QUADRANT_Z=QUADRANT_ONE;
                        break;
                }
            }
        }
        else
        {
            ucStatusPowerQuadrantUseZ=n;
            ucStatusPowerQuadrantTimeZ=0;               
        }
        // AA   A相 的象限判断  AA 
        n=ucTempAde7878Q&0x11;
        if(n==ucStatusPowerQuadrantUseA)
        {
            if(ucStatusPowerQuadrantTimeA<10)
                ucStatusPowerQuadrantTimeA++;
            if(ucStatusPowerQuadrantTimeA>=CON_QUADRANT_CHANGETIME)
            {
                status_5460_0=(status_5460_0&0xEE)|n;   
                switch(ucStatusPowerQuadrantUseA)
                {
                    case 0x01:
                        QUADRANT_A=QUADRANT_FOUR;
                        break;
                    case 0x10:
                        QUADRANT_A=QUADRANT_TWO;
                        break;
                    case 0x11:
                        QUADRANT_A=QUADRANT_THREE;
                        break;
                    default:
                        QUADRANT_A=QUADRANT_ONE;
                        break;
                }
            }
        }
        else
        {
            ucStatusPowerQuadrantUseA=n;
            ucStatusPowerQuadrantTimeA=0;               
        }           
        // AA   B相 的象限判断  AA 
        n=ucTempAde7878Q&0x22;
        if(n==ucStatusPowerQuadrantUseB)
        {
            if(ucStatusPowerQuadrantTimeB<10)
                ucStatusPowerQuadrantTimeB++;
            if(ucStatusPowerQuadrantTimeB>=CON_QUADRANT_CHANGETIME)
            {
                status_5460_0=(status_5460_0&0xDD)|n;   
                switch(ucStatusPowerQuadrantUseB)
                {
                    case 0x02:
                        QUADRANT_B=QUADRANT_FOUR;
                        break;
                    case 0x20:
                        QUADRANT_B=QUADRANT_TWO;
                        break;
                    case 0x22:
                        QUADRANT_B=QUADRANT_THREE;
                        break;
                    default:
                        QUADRANT_B=QUADRANT_ONE;
                        break;
                }
            }
        }
        else
        {
            ucStatusPowerQuadrantUseB=n;
            ucStatusPowerQuadrantTimeB=0;               
        }           
        // AA   C相 的象限判断  AA 
        n=ucTempAde7878Q&0x44;
        if(n==ucStatusPowerQuadrantUseC)
        {
            if(ucStatusPowerQuadrantTimeC<10)
                ucStatusPowerQuadrantTimeC++;
            if(ucStatusPowerQuadrantTimeC>=CON_QUADRANT_CHANGETIME)
            {
                status_5460_0=(status_5460_0&0xBB)|n;   
                switch(ucStatusPowerQuadrantUseC)
                {
                    case 0x04:
                        QUADRANT_C=QUADRANT_FOUR;
                        break;
                    case 0x40:
                        QUADRANT_C=QUADRANT_TWO;
                        break;
                    case 0x44:
                        QUADRANT_C=QUADRANT_THREE;
                        break;
                    default:
                        QUADRANT_C=QUADRANT_ONE;
                        break;
                }
            }
        }
        else
        {
            ucStatusPowerQuadrantUseC=n;
            ucStatusPowerQuadrantTimeC=0;               
        }           
// AA------------------------总和各个分相的象限判断部分 ---->End ----AA         

        switch(QUADRANT_Z)
        {
            case QUADRANT_FOUR:
                RAM[RAM_CURRENT_KVAR_ALL+3] |=0x80;
                break;
            case QUADRANT_THREE:
                RAM[RAM_CURRENT_KVAR_ALL+3] |=0x80;
                RAM[RAM_CURRENT_KW_ALL+3] |=0x80;
                RAM[RAM_CURRENT_KVA_ALL+3] |=0x80;
                RAM[RAM_CURRENT_FACTOR_ALL+3] |=0x80;
                break;
            case QUADRANT_TWO:
                RAM[RAM_CURRENT_KW_ALL+3] |=0x80;
                RAM[RAM_CURRENT_KVA_ALL+3] |=0x80;
                RAM[RAM_CURRENT_FACTOR_ALL+3] |=0x80;
                break;
            default:
                break;
        }
        
        switch(QUADRANT_A)
        {
            case QUADRANT_FOUR:
                RAM[RAM_CURRENT_KVAR_A+3] |=0x80;
                break;
            case QUADRANT_THREE:
                RAM[RAM_CURRENT_KVAR_A+3] |=0x80;
                RAM[RAM_CURRENT_KW_A+3] |=0x80;
                RAM[RAM_CURRENT_KVA_A+3] |=0x80;
                RAM[RAM_CURRENT_I_A+3] |=0x8;
                RAM[RAM_CURRENT_FACTOR_A+3] |=0x80;
                break;
            case QUADRANT_TWO:
                RAM[RAM_CURRENT_KW_A+3] |=0x80;
                RAM[RAM_CURRENT_KVA_A+3] |=0x80;
                RAM[RAM_CURRENT_I_A+3] |=0x8;
                RAM[RAM_CURRENT_FACTOR_A+3] |=0x80;
                break;
            default:
                break;
        }
        
        switch(QUADRANT_B)
        {
            case QUADRANT_FOUR:
                RAM[RAM_CURRENT_KVAR_B+3] |=0x80;
                break;
            case QUADRANT_THREE:
                RAM[RAM_CURRENT_KVAR_B+3] |=0x80;
                RAM[RAM_CURRENT_KW_B+3] |=0x80;
                RAM[RAM_CURRENT_KVA_B+3] |=0x80;
                RAM[RAM_CURRENT_I_B+3] |=0x8;
                RAM[RAM_CURRENT_FACTOR_B+3] |=0x80;
                break;
            case QUADRANT_TWO:
                RAM[RAM_CURRENT_KW_B+3] |=0x80;
                RAM[RAM_CURRENT_KVA_B+3] |=0x80;
                RAM[RAM_CURRENT_I_B+3] |=0x8;
                RAM[RAM_CURRENT_FACTOR_B+3] |=0x80;
                break;
            default:
                break;
        }
        
        switch(QUADRANT_C)
        {
            case QUADRANT_FOUR:
                RAM[RAM_CURRENT_KVAR_C+3] |=0x80;
                break;
            case QUADRANT_THREE:
                RAM[RAM_CURRENT_KVAR_C+3] |=0x80;
                RAM[RAM_CURRENT_KW_C+3] |=0x80;
                RAM[RAM_CURRENT_KVA_C+3] |=0x80;
                RAM[RAM_CURRENT_I_C+3] |=0x8;
                RAM[RAM_CURRENT_FACTOR_C+3] |=0x80;
                break;
            case QUADRANT_TWO:
                RAM[RAM_CURRENT_KW_C+3] |=0x80;
                RAM[RAM_CURRENT_KVA_C+3] |=0x80;
                RAM[RAM_CURRENT_I_C+3] |=0x8;
                RAM[RAM_CURRENT_FACTOR_C+3] |=0x80;
                break;
            default:
                break;
        }

        if(PROGFUNCTION_TYPE_METER_TYPE==METERTYPE_3_3)
        {
            memset(&RAM[RAM_CURRENT_KW_B], 0x00, 4);
            memset(&RAM[RAM_CURRENT_KVAR_B], 0x00, 4);
            memset(&RAM[RAM_CURRENT_KVA_B], 0x00, 4);
            memset(&RAM[RAM_CURRENT_FACTOR_B], 0x00, 4);
        }
    }

    //if((GAL_NO==ucSystemBusy)&&(ucModeAde7758RmsSecond!=RSOFT_RTC_SECOND))
    if(ucStep == 2)
    {
        //ucModeAde7758RmsSecond=RSOFT_RTC_SECOND;
        if(ucAde7878CfModeTime<CON_ADE7878_CFMODE_TIME_DEAL)
            return;
        
// AA------------------------电压有效值计算 ---->Start ----AA           
        ucVoltageLowStatusABC=0;
        ulMinVoltage = ulTypeUn*10; // (ulTypeUn*1000)/100; // 最小显示电压，额定电压的1%
//        if(ulMinVoltage > 20000)    //保证最小电压不大于2V
//            ulMinVoltage = 20000;
        if(ulMinVoltage < 20000)    //保证最小电压不小于2V, --LXC 2014.5.29
            ulMinVoltage = 20000;
        for(n=0;n<3;n++)
        { 
            if(1==ReadADReg(TB_ADE7878_VOLTAGE_RMS[n],4, &ucAde7758Data[0]))
            { 
                ucReadADRegOkNum++;
                //l7758.l=0;
                REV_7858_4BYTES(l7758.c, ucAde7758Data);
                
                lTemp=l7758.l/uiClacMeterVoltageCoef;
                l7758.l=(500*(l7758.l%uiClacMeterVoltageCoef))/uiClacMeterVoltageCoef+500*lTemp;//l5349 2729
                if((ucAde7758Data[1]<2)||(ucAde7758Data[1]>0x50))
                {
                    ucVoltageLowStatusABC=ucVoltageLowStatusABC+BitValue(n);
                }
                if((l7758.l>5000000)||(l7758.l<ulMinVoltage))  //大于500v或小于1%无效
                {
                    l7758.l=0;
                }
                LongToData4BCD(l7758.l, &RAM[RAM_CURRENT_V_A+4*n]);// xxxx dot xxxx
                uiNowVoltage[n]=l7758.l/1000;// xxx dot x
            }
        }       
// AA------------------------电压有效值计算 ---->End ----AA       

// AA------------------------频率计算 ---->Start ----AA         
        if(1==ReadADReg(AD_PERIOD,2, &ucAde7758Data[0]))
        {
            ucReadADRegOkNum++;
            l7758.l=0;      
            l7758.c[0]=ucAde7758Data[1];
            l7758.c[1]=ucAde7758Data[0];
            if(l7758.l == 0) 
            {
                ErrPrint("freq calc l7758.l = 0\n");
                l7758.l=1;
            }
            l7758.l = 25600000 / l7758.l;
            if((l7758.l<4500)||(6500<l7758.l))
            {
                l7758.l=5000;
            }
            if(7==ucVoltageLowStatusABC)
            {
                l7758.l=5000;           
            }
            LongToData2BCD((l7758.l),&ucAde7758Data[0]);
            RAM[RAM_CURRENT_FREQ_A+0]=ucAde7758Data[0]; 
            RAM[RAM_CURRENT_FREQ_A+1]=ucAde7758Data[1]; 
            RAM[RAM_CURRENT_FREQ_B+0]=ucAde7758Data[0]; 
            RAM[RAM_CURRENT_FREQ_B+1]=ucAde7758Data[1]; 
            RAM[RAM_CURRENT_FREQ_C+0]=ucAde7758Data[0]; 
            RAM[RAM_CURRENT_FREQ_C+1]=ucAde7758Data[1]; 
        }
// AA------------------------频率计算 ---->End ----AA      

        // AA 如果出现断相现象，则自动切换频率计算点   AA
        if(1==ReadADReg(AD_MMODE,1,&ucAde7758Data[0]))
        {
            ucReadADRegOkNum++;
            // 根据ABC断相情况，切换频率测量相
            if(TB_ADE7878_PERIOD_SEL[ucVoltageLowStatusABC]!=ucAde7758Data[0])
            {
                ucAde7758Data[0]=TB_ADE7878_PERIOD_SEL[ucVoltageLowStatusABC];
                WriteADReg(&ucAde7758Data[0],AD_MMODE,1);
            }
        }
        //  AA  以下寄存器只做读的操作，结果不使用   AA     
        m=(sizeof(TB_ADE7878_READ_NOUSE)/sizeof(u16));
        for(n=0;n<m;n++)
        {
            ReadADReg(TB_ADE7878_READ_NOUSE[n],4, &ucAde7758Data[0]);
        }

        if(PROGFUNCTION_TYPE_METER_TYPE==METERTYPE_3_3)
        {
            memset(&RAM[RAM_CURRENT_I_B], 0x00, 4);
            memset(&RAM[RAM_CURRENT_V_B], 0x00, 4);
            memset(&RAM[RAM_CURRENT_FREQ_B], 0x00, 2);
        }

    }

}

