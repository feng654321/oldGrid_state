#ifndef __AP_ADE7758_H__
#define __AP_ADE7758_H__
    
#ifdef  AP_ADE7758_GLOBALS
    #define AP_ADE7758_EXT
#else
    #define AP_ADE7758_EXT extern
#endif  

#define CON_STR_FILE_ADE7878_DATA		"/usr1/etc/ade7878.dat"
#define CON_STR_FILE_ADE7878_DATA2		"/mnt/dbf/ade7878.da2"


#define CON_STR_FILE_ADE7878_PAR		"/usr1/etc/ade7878.par"
#define CON_STR_FILE_ADE7878_PA2		"/mnt/dbf/ade7878.pa2"

#define AD_AIGAIN   0x4380  // 0x000000  Phase A current gain adjust  
#define AD_AVGAIN   0x4381  // 0x000000  Phase A voltage gain adjust  
#define AD_BIGAIN   0x4382  // 0x000000  Phase B current gain adjust  
#define AD_BVGAIN   0x4383  // 0x000000  Phase B voltage gain adjust  
#define AD_CIGAIN   0x4384  // 0x000000  Phase C current gain adjust  
#define AD_CVGAIN   0x4385  // 0x000000  Phase C voltage gain adjust  
#define AD_NIGAIN   0x4386  // 0x000000  Neutral current gain adjust  
#define AD_AIRMSOS  0x4387  // 0x000000  Phase A current rms offset  
#define AD_AVRMSOS  0x4388  // 0x000000  Phase A voltage rms offset  
#define AD_BIRMSOS  0x4389  // 0x000000  Phase B current rms offset  
#define AD_BVRMSOS  0x438A  // 0x000000  Phase B voltage rms offset  
#define AD_CIRMSOS  0x438B  // 0x000000  Phase C current rms offset  
#define AD_CVRMSOS  0x438C  // 0x000000  Phase C voltage rms offset  
#define AD_NIRMSOS  0x438D  // 0x000000  Neutral current rms offset  
#define AD_AVAGAIN  0x438E  // 0x000000  Phase A apparent power gain adjust  
#define AD_BVAGAIN  0x438F  // 0x000000  Phase B apparent power gain adjust  
#define AD_CVAGAIN  0x4390  // 0x000000  Phase C apparent power gain adjust  
#define AD_AWGAIN   0x4391  // 0x000000  Phase A total active power gain adjust  
#define AD_AWATTOS  0x4392  // 0x000000  Phase A total active power offset adjust  
#define AD_BWGAIN   0x4393  // 0x000000  Phase B total active power gain adjust  
#define AD_BWATTOS  0x4394  // 0x000000  Phase B total active power offset adjust  
#define AD_CWGAIN   0x4395  // 0x000000  Phase C total active power gain adjust  
#define AD_CWATTOS  0x4396  // 0x000000  Phase C total active power offset adjust  
#define AD_AVARGAIN 0x4397  // 0x000000  Phase A total reactive power gain adjust  
#define AD_AVAROS   0x4398  // 0x000000  Phase A total reactive power offset adjust  
#define AD_BVARGAIN 0x4399  // 0x000000  Phase B total reactive power gain adjust  
#define AD_BVAROS   0x439A  // 0x000000  Phase B total reactive power offset adjust  
#define AD_CVARGAIN 0x439B  // 0x000000  Phase C total reactive power gain adjust  
#define AD_CVAROS   0x439C  // 0x000000  Phase C total reactive power offset adjust  
#define AD_AFWGAIN  0x439D  // 0x000000  Phase A fundamental active power gain adjust  
#define AD_AFWATTOS 0x439E  // 0x000000  Phase A fundamental active power offset adjust  
#define AD_BFWGAIN  0x439F  // 0x000000  Phase B fundamental active power gain adjust  
#define AD_BFWATTOS 0x43A0  // 0x000000  Phase B fundamental active power offset adjust  
#define AD_CFWGAIN  0x43A1  // 0x000000  Phase C fundamental active power gain adjust  
#define AD_CFWATTOS 0x43A2  // 0x000000  Phase C fundamental active power offset adjust  
#define AD_AFVARGAIN 0x43A3  // 0x000000  Phase A fundamental reactive power gain adjust  
#define AD_AFVAROS  0x43A4  // 0x000000  Phase A fundamental reactive power offset adjust  
#define AD_BFVARGAIN 0x43A5  // 0x000000  Phase B fundamental reactive power gain adjust  
#define AD_BFVAROS  0x43A6  // 0x000000  Phase B fundamental reactive power offset adjust  
#define AD_CFVARGAIN 0x43A7  // 0x000000  Phase C fundamental reactive power gain adjust  
#define AD_CFVAROS  0x43A8  // 0x000000  Phase C fundamental reactive power offset adjust  
#define AD_VATHR1   0x43A9  // 0x000000  Most significant 24 bits of VATHR[47:0] threshold used in phase apparent power data path.  
#define AD_VATHR0   0x43AA  // 0x000000  Less significant 24 bits of VATHR[47:0] threshold used in phase apparent power data path.  
#define AD_WTHR1    0x43AB  // 0x000000  Most significant 24 bits of WTHR[47:0] threshold used in phase total/fundamental active power data path.  
#define AD_WTHR0    0x43AC  // 0x000000  Less significant 24 bits of WTHR[47:0] threshold  used in phase total/fundamental active power data path. 
#define AD_VARTHR1  0x43AD  // 0x000000  Most significant 24 bits of VARTHR[47:0] threshold used in phase total/fundamental reactive power data path.  
#define AD_VARTHR0  0x43AE  // 0x000000  Less significant 24 bits of VARTHR[47:0] threshold used in phase total/fundamental reactive power data path.  
// #define reserved 0x43AF  // 0x000000  This memory location should be kept at 0x000000 for proper operation  
#define AD_VANOLOAD 0x43B0  // 0x0000000  No-load threshold in the apparent power data path  
#define AD_APNOLOAD 0x43B1 // 0x0000000  No-load threshold in the total/fundamental active power data path  
#define AD_VARNOLOAD 0x43B2 // 0x0000000  No-load threshold in the total/fundamental reactive power data path  
#define AD_VLEVEL   0x43B3 // 0x0000000  Register used in the algorithm that computes the fundamental active and reactive powers  
// #define reserved 0x43B4  // 0x000000  This memory location should not be written for proper operation  
#define AD_DICOEFF  0x43B5 // 0x0000000  Register used in the digital integrator algorithm. If the integrator is turned on, it must be set at 0xFF8000  
#define AD_HPFDIS   0x43B6 // 0x000000  Disables/enables the HPF in the current data path (see Table 28)  
// #define reserved 0x43B7 // 0x000000  This memory location should be kept at 0x000000 for proper operation  
#define AD_ISUMLVL  0x43B8 // 0x0000000  Threshold used in the comparison between the sum of phase currents and the neutral current  
// #define reserved 0x43B9-0x43BE  // 0x000000  These memory locations should be kept at 0x000000 for proper operation 
#define AD_ISUM     0x43BF  // NA  Sum of IAVW, IBVW and ICVW registers  
#define AD_AIRMS    0x43C0  // NA  Phase A current rms value  
#define AD_AVRMS    0x43C1  // NA  Phase A voltage rms value  
#define AD_BIRMS    0x43C2  // NA  Phase B current rms value  
#define AD_BVRMS    0x43C3  // NA  Phase B voltage rms value  
#define AD_CIRMS    0x43C4  // NA  Phase C current rms value  
#define AD_CVRMS    0x43C5  // NA  Phase C voltage rms value  
#define AD_NIRMS    0x43C6  // NA  Neutral current rms value  
// #define reserved 0x43C7-0x43FF  // 0x000000  These memory locations should not be written for proper operation  
// #define reserved 0xE203  // 0x0000  This memory location should not be written for proper operation.  
#define AD_RUN      0xE228  // 0x0000  RUN register starts and stops the DSP. See Digital Signal Processor chapter for more details.  
#define AD_AWATTHR  0xE400  // 0x00000000  Phase A total active energy accumulation  
#define AD_BWATTHR  0xE401  // 0x00000000  Phase B total active energy accumulation  
#define AD_CWATTHR  0xE402  // 0x00000000  Phase C total active energy accumulation  
#define AD_AFWATTHR 0xE403  // 0x00000000  Phase A fundamental active energy accumulation  
#define AD_BFWATTHR 0xE404  // 0x00000000  Phase B fundamental active energy accumulation  
#define AD_CFWATTHR 0xE405  // 0x00000000  Phase C fundamental active energy accumulation  
#define AD_AVARHR   0xE406  // 0x00000000  Phase A total reactive energy accumulation  
#define AD_BVARHR   0xE407  // 0x00000000  Phase B total reactive energy accumulation  
#define AD_CVARHR   0xE408  // 0x00000000  Phase C total reactive energy accumulation  
#define AD_AFVARHR  0xE409  // 0x00000000  Phase A fundamental reactive energy accumulation  
#define AD_BFVARHR  0xE40A  // 0x00000000  Phase B fundamental reactive energy accumulation  
#define AD_CFVARHR  0xE40B  // 0x00000000  Phase C fundamental reactive energy accumulation  
#define AD_AVAHR    0xE40C  // 0x00000000  Phase A apparent energy accumulation  
#define AD_BVAHR    0xE40D  // 0x00000000  Phase B apparent energy accumulation  
#define AD_CVAHR    0xE40E  // 0x00000000  Phase C apparent energy accumulation  
#define AD_IPEAK    0xE500  // NA  Current peak register. See Figure 36 and Table 29 for details about its composition.  
#define AD_VPEAK    0xE501  // NA  Voltage peak register. See Figure 36 and Table 30 for details about its composition.  
#define AD_STATUS0  0xE502  // NA  Interrupt status register 0. (See Table 31)  
#define AD_STATUS1  0xE503  // NA  Interrupt status register 1. (See Table 32)  
#define AD_AIMAV    0xE504  // NA  Phase A current rms computed during PSM1 mode  
#define AD_BIMAV    0xE505  // NA  Phase B current rms computed during PSM1 mode  
#define AD_CIMAV    0xE506  // NA  Phase C current rms computed during PSM1 mode  
#define AD_OILVL    0xE507  // 0xFFFFFF  Overcurrent threshold  
#define AD_OVLVL    0xE508  // 0xFFFFFF  Overvoltage threshold  
#define AD_SAGLVL   0xE509  // 0x000000  Voltage sag level threshold  
#define AD_MASK0    0xE50A  // 0x00000000  Interrupt enable register 0. (See Table 33)  
#define AD_MASK1    0xE50B  // 0x00000000  Interrupt enable register 1. (See Table 34)  
#define AD_IAWV     0xE50C  // NA  Instantaneous value of phase A current  
#define AD_IBWV     0xE50D  // NA  Instantaneous value of phase B current  
#define AD_ICWV     0xE50E  // NA  Instantaneous value of phase C current  
#define AD_INWV     0xE50F  // NA  Instantaneous value of neutral current  
#define AD_VAWV     0xE510  // NA  Instantaneous value of phase A voltage  
#define AD_VBWV     0xE511  // NA  Instantaneous value of phase B voltage  
#define AD_VCWV     0xE512  // NA  Instantaneous value of phase C voltage  
#define AD_AWATT    0xE513  // NA  Instantaneous value of phase A total active power  
#define AD_BWATT    0xE514  // NA  Instantaneous value of phase B total active power  
#define AD_CWATT    0xE515  // NA  Instantaneous value of phase B total active power  
#define AD_AVAR     0xE516  // NA  Instantaneous value of phase A total reactive power  
#define AD_BVAR     0xE517  // NA  Instantaneous value of phase B total reactive power  
#define AD_CVAR     0xE518  // NA  Instantaneous value of phase B total reactive power  
#define AD_AVA      0xE519  // NA  Instantaneous value of phase A apparent power  
#define AD_BVA      0xE51A  // NA  Instantaneous value of phase Bapparent power  
#define AD_CVA      0xE51B  // NA  Instantaneous value of phase B apparent power  
#define AD_CHECKSUM 0xE51F  // 0x9AE5E8B1  Checksum verification. See Checksum Register section for details  
#define AD_VNOM     0xE520  // 0x000000  Nominal phase voltage rms used in the alternative computation of the apparent power  
// #define reserved 0xE521-0xE52E  //  These addresses should not be written for proper operation  
#define AD_PHSTATUS 0xE600  // NA  Phase peak register. (See Table 35)  
#define AD_ANGLE0   0xE601  // NA  Time delay 0. See Time Interval Between Phases section for details  
#define AD_ANGLE1   0xE602  // NA  Time delay 1. See Time Interval Between Phases section for details  
#define AD_ANGLE2   0xE603  // NA  Time delay 2. See Time Interval Between Phases section for details  
// #define reserved 0xE604-0xE606  //  These addresses should not be written for proper operation  
#define AD_PERIOD   0xE607  // NA  Network line period  
#define AD_PHNOLOAD 0xE608  // NA  Phase no-load register. (See Table 36)  
// #define reserved 0xE609-0xE60B  //  These addresses should not be written for proper operation  
#define AD_LINECYC  0xE60C  // 0xFFFF  Line cycle accumulation mode count  
#define AD_ZXTOUT   0xE60D  // 0xFFFF  Zero crossing timeout count  
#define AD_COMPMODE 0xE60E  // 0x01FF  Computation mode register. (See Table 37)  
#define AD_GAIN     0xE60F  // 0x0000  PGA gains at ADC inputs. (See Table 38)  
#define AD_CFMODE   0xE610  // 0x0E88  CFx, x=1,2,3 configuration register. (See Table 39)  
#define AD_CF1DEN   0xE611  // 0x0000  CF1 denominator  
#define AD_CF2DEN   0xE612  // 0x0000  CF2 denominator  
#define AD_CF3DEN   0xE613  // 0x0000  CF3 denominator  
#define AD_APHCAL   0xE614  // 0x0000  Phase calibration of phase A. (See Table 40)  
#define AD_BPHCAL   0xE615  // 0x0000  Phase calibration of phase B. (See Table 40)  
#define AD_CPHCAL   0xE616  // 0x0000  Phase calibration of phase C. (See Table 40)  
#define AD_PHSIGN   0xE617  // NA  Power sign register. (See Table 41)  
#define AD_CONFIG   0xE618  // 0x0000  ADE7878 configuration register. (See Table 42)  
#define AD_MMODE    0xE700  // 0x16  Measurement mode register. (See Table 43)  
#define AD_ACCMODE  0xE701  // 0x00  Accumulation mode register. (SeeTable 44)  
#define AD_LCYCMODE 0xE702  // 0x78  Line accumulation mode behavior. (See Table 45)  
#define AD_PEAKCYC  0xE703  // 0x00  Peak detection half line cycles  
#define AD_SAGCYC   0xE704  // 0x00  Sag detection half line cycles  
#define AD_CFCYC    0xE705  // 0x01  Number of CF pulses between two consecutive energy latches. See Synchronizing energy registers with CFx outputs section  
#define AD_HSDC_CFG 0xE706  // 0x00  HSDC configuration register. (See Table 46)  
#define AD_VERSION  0xE707  // - Version of die  
// #define reserved 0xEBFF //  This address may be used in manipulating the SS pin when SPI is chosen as the active port. (See Serial Interfaces chapter for details)  
#define AD_LPOILVL  0xEC00  // 0x07  Overcurrent threshold used during PSM2 mode. (See Table 47)  
#define AD_CONFIG2  0xEC01  // 0x00  Configuration register used during PSM1 mode. (See Table 48)  

//AA 寄存器里面不使用 AA
#define AD_VIRTUALREG_NO_USE        0x0000 



#define AD_VIRTUALREG_ACURRENTSAVE  0x0080
#define AD_VIRTUALREG_BCURRENTSAVE  0x0081
#define AD_VIRTUALREG_CCURRENTSAVE  0x0082


//AA  4zijie 虚拟的校验保存寄存器    AAAA
#define AD_VIRTUALREG_CHECKSUMSAVE0 0x0010  
#define AD_VIRTUALREG_CHECKSUMSAVE1 0x0011  
#define AD_VIRTUALREG_CHECKSUMSAVE2 0x0012  
#define AD_VIRTUALREG_CHECKSUMSAVE3 0x0013  
#define AD_VIRTUALREG_CHECKSUMSAVE4 0x0014  
#define AD_VIRTUALREG_CHECKSUMSAVE5 0x0015  
#define AD_VIRTUALREG_CHECKSUMSAVE6 0x0016  
#define AD_VIRTUALREG_CHECKSUMSAVE7 0x0017  
#define AD_VIRTUALREG_CHECKSUMSAVE8 0x0018  




// AA 保留使用，必须设置为0   AA
#define AD_RESERVED43AF 0x43AF  // AA 保留使用，必须设置为0   AA
#define AD_RESERVED43B7 0x43B7  // AA 保留使用，必须设置为0   AA
#define AD_RESERVED43B9 0x43B9  // AA 保留使用，必须设置为0   AA
#define AD_RESERVED43BA 0x43BA  // AA 保留使用，必须设置为0   AA
#define AD_RESERVED43BB 0x43BB  // AA 保留使用，必须设置为0   AA
#define AD_RESERVED43BC 0x43BC  // AA 保留使用，必须设置为0   AA
#define AD_RESERVED43BD 0x43BD  // AA 保留使用，必须设置为0   AA
#define AD_RESERVED43BE 0x43BE  // AA 保留使用，必须设置为0   AA


// AA == 以下寄存器为ADE7878隐含的寄存器 ==  AA
// AA == 必须按照要求设置  ==  AA
// AA == 在RUN寄存器写入之前 ==  AA
// AA == 1、E7FE写入0XAD ==  AA
// AA == 2、E7E2写入0X01 ==  AA
// AA == 3、E7FE写入0X00 ==  AA
#define AD_HIDE_KEY         0xE7FE
#define AD_MODE_CONTROL     0xE7E2


#define AD_VIRTUALREG_A     0x00
#define AD_VIRTUALREG_B     0x01
#define AD_VIRTUALREG_C     0x02
#define AD_VIRTUALREG_ALL   0x03


#define AD_VIRTUALREG_AKW       0x00
#define AD_VIRTUALREG_BKW       0x01
#define AD_VIRTUALREG_CKW       0x02

#define AD_VIRTUALREG_AKVAR     0x03
#define AD_VIRTUALREG_BKVAR     0x04
#define AD_VIRTUALREG_CKVAR     0x05

#define AD_VIRTUALREG_AKVA      0x06
#define AD_VIRTUALREG_BKVA      0x07
#define AD_VIRTUALREG_CKVA      0x08

#define AD_VIRTUALREG_ALLKW     0x09
#define AD_VIRTUALREG_ALLKVAR   0x0A
#define AD_VIRTUALREG_ALLKVA    0x0B

#define AD_VIRTUALREG_TEMPF     0x0C        //AA 正向计算临时使用  AA
#define AD_VIRTUALREG_TEMPR     0x0D        //AA 反向计算临时使用  AA

//#define ADREG_TEMP_CLAC_ALLWATTHR   0x0D    //AA 总有功--计算临时使用  AA
//#define ADREG_TEMP_CLAC_ALLVARHR    0x0E    //AA 总无功--计算临时使用  AA




#define ADREG_AIRMS         0x0a    
#define ADREG_BIRMS         0x0b
#define ADREG_CIRMS         0x0c
#define ADREG_AVRMS         0x0d
#define ADREG_BVRMS         0x0e
#define ADREG_CVRMS         0x0f
#define ADREG_FREQ          0x10
#define ADREG_TEMP          0x11
#define ADREG_WFORM         0x12
#define ADREG_OPMODE        0x13
#define ADREG_MODE          0x14
#define ADREG_WAVMODE       0x15
#define ADREG_COMPMODE      0x16
#define ADREG_LCYCMODE      0x17
#define ADREG_MASK          0x18
#define ADREG_STATUS        0x19
#define ADREG_RSTATUS       0x1a
#define ADREG_ZXTOUT        0x1b
#define ADREG_LINECYC       0x1c
#define ADREG_SAGCYC        0x1d
#define ADREG_SAGLVL        0x1e
#define ADREG_VPINTLVL      0x1f
#define ADREG_IPINTLVL      0x20
#define ADREG_VPEAK         0x21
#define ADREG_IPEAK         0x22
#define ADREG_GAIN          0x23
#define ADREG_AVRMSGA       0x24
#define ADREG_BVRMSGA       0x25
#define ADREG_CVRMSGA       0x26
#define ADREG_AIGAIN        0x27
#define ADREG_BIGAIN        0x28
#define ADREG_CIGAIN        0x29
#define ADREG_AWG           0x2a
#define ADREG_BWG           0x2b
#define ADREG_CWG           0x2c
#define ADREG_AVARG         0x2d
#define ADREG_BVARG         0x2e
#define ADREG_CVARG         0x2f
#define ADREG_AVAG          0x30
#define ADREG_BVAG          0x31
#define ADREG_CVAG          0x32
#define ADREG_AVRMSOS       0x33
#define ADREG_BVRMSOS       0x34
#define ADREG_CVRMSOS       0x35
#define ADREG_AIRMSOS       0x36
#define ADREG_BIRMSOS       0x37
#define ADREG_CIRMSOS       0x38
#define ADREG_AWATTOS       0x39
#define ADREG_BWATTOS       0x3a
#define ADREG_CWATTOS       0x3b
#define ADREG_AVAROS        0x3c
#define ADREG_BVAROS        0x3d
#define ADREG_CVAROS        0x3e
#define ADREG_APHCAL        0x3f
#define ADREG_BPHCAL        0x40
#define ADREG_CPHCAL        0x41
#define ADREG_WDIV          0x42
#define ADREG_VARDIV        0x43
#define ADREG_VADIV         0x44
#define ADREG_APCFNUM       0x45
#define ADREG_APCFDEN       0x46
#define ADREG_VARCFNU       0x47
#define ADREG_VARCFDE       0x48
#define ADREG_CHKSUM        0x7e
#define ADREG_VERSION       0x7f

#define ADREG_INSIDECONFIGURE       0x7d

#define ADREG_VIRTUAL_ADDRSTART     0x4f
#define ADREG_VIRTUAL_ACURRENT      0x80
#define ADREG_VIRTUAL_BCURRENT      0x81
#define ADREG_VIRTUAL_CCURRENT      0x82


#define CON_REVERSE_POWER_MIN_CONDITION_F   0x10
#define CON_REVERSE_POWER_MIN_CONDITION_R   0xFFFFE0

#define CON_QUADRANT_CHANGETIME             1   //象限有效切换最小延时

#define CON_ADE7758_1S_TIME_MAX             10100
#define CON_ADE7758_1S_TIME_MIN             9900
#define CON_ADE7758_1S_TIME_CURRENT         8000

#define CON_ADE7878CHECKSUM_DATA_MAX_LEN    36

#define CON_REVERSE_POWER_ALL_CONDITION     0x000100
#define CON_REVERSE_POWER_ABC_CONDITION     0x000064


#define CON_ADE7878_DATA_TYPE_32ZPSE_S24_R_W    0x01
#define CON_ADE7878_DATA_TYPE_32ZP_U24_R_W      0x02
#define CON_ADE7878_DATA_TYPE_32ZP_S24_R        0x03
#define CON_ADE7878_DATA_TYPE_32ZP_U20_R        0x04
#define CON_ADE7878_DATA_TYPE_32_S32_R          0x05
#define CON_ADE7878_DATA_TYPE_32_U32_R          0x06
#define CON_ADE7878_DATA_TYPE_32_U32_R_W        0x07
#define CON_ADE7878_DATA_TYPE_32SE_S24_R        0x08
#define CON_ADE7878_DATA_TYPE_32ZP_S24_R_W      0x09
#define CON_ADE7878_DATA_TYPE_32ZP_S28_R        0x0a

#define CON_ADE7878_DATA_TYPE_16ZP_U10_R_W      0x21
#define CON_ADE7878_DATA_TYPE_16_U16_R_W        0x22
#define CON_ADE7878_DATA_TYPE_16_U16_R          0x23

#define CON_ADE7878_DATA_TYPE_8_U8_R_W          0x30
#define CON_ADE7878_DATA_TYPE_VIRTUALREG        0x80

typedef struct
{
    u16 RegName;               //寄存器地址
    uchar ResumeType;           //数据类型
    uchar CheckType;            //
    ulong ulDefaultData;        //默认值
}ST_ADE7878_REG_PARAM;

#define REV_7858_4BYTES(d, s) {d[0]=s[3]; d[1]=s[2]; d[2]=s[1]; d[3]=0; }

AP_ADE7758_EXT const u16 TB_ADE7878_VOLTAGE_RMS[];
AP_ADE7758_EXT const u16 TB_ADE7878_CURRENT_RMS[];
AP_ADE7758_EXT const u16 TB_ADE7878_ENERGY[];


AP_ADE7758_EXT uchar status_5460_0;// zhuang tai zi
AP_ADE7758_EXT uchar status_5460_1;// zhuang tai zi

AP_ADE7758_EXT uchar r7758mode_ok;
AP_ADE7758_EXT uchar spi_status;

AP_ADE7758_EXT ulong ulPowerBuffer[AD_VIRTUALREG_TEMPR+1];


AP_ADE7758_EXT u16  uiNowVoltage[4];        // xxx dot x V
AP_ADE7758_EXT ulong ulNowCurrent[4];   // xxx dot xxxX A
AP_ADE7758_EXT uchar ucVoltageLowStatusABC;  // 电压低的状态

AP_ADE7758_EXT u16  uiCoefCurrentGAIN[3];
AP_ADE7758_EXT ulong ucAde7878CfModeTime;

#define CON_ADE7878_CFMODE_TIME_MAX         5
#define CON_ADE7878_CFMODE_TIME_DEAL    2
AP_ADE7758_EXT uchar ByteOneNum(uchar value);

AP_ADE7758_EXT uchar ReadADReg (u16 Src, uchar Len ,uchar *Dst);

AP_ADE7758_EXT uchar WriteADReg (uchar *Src, u16 Dst, uchar Len);

AP_ADE7758_EXT uchar WriteADRegCheck (uchar *Src, u16 Dst, uchar Len);

AP_ADE7758_EXT uchar ReadADRegComm (u16 Src, uchar Len ,uchar *Dst);

AP_ADE7758_EXT uchar ReadADRegResumeData(u16 uiRegName,uchar ucDatalen, uchar *Dst);

AP_ADE7758_EXT uchar WriteADRegResumeData(u16 uiRegName,uchar ucDatalen,uchar *Dst);

#define ADE_INIT_SUCC       0
#define ADE_INIT_FAIL       2
#define ADE_INIT_POWERDOWN  3
AP_ADE7758_EXT uchar InitADMode(uchar ucType, uchar isOninit);

AP_ADE7758_EXT uchar CheckADE7758(void);

AP_ADE7758_EXT void CosDataFromKwKvar(ulong ukw,ulong ukva,uchar *point);

AP_ADE7758_EXT void ChangeCoefToKw(ulong *point);

AP_ADE7758_EXT u16 AutoChangeAde7758Gain(uchar ufas);

AP_ADE7758_EXT uchar AutoChangeAde7758Phase(uchar ufas);

AP_ADE7758_EXT uchar GreatSet16Kw(void);
AP_ADE7758_EXT void ModeAde7878PowerOn(void);
  
AP_ADE7758_EXT void ModeADE7758(uchar ucStep);

AP_ADE7758_EXT void ClrCurrentADE7758Data(uchar ucMeterClr);


AP_ADE7758_EXT u16 uiPluseRestTimes;

AP_ADE7758_EXT void CloseAD7878(void);

AP_ADE7758_EXT uchar GetClacPlusePowerCoef(void);


AP_ADE7758_EXT void CosDataFromKwKva_pre(ulong ukw,ulong ukva,uchar *point);
#endif

