#ifndef __GOL_FUNCTION_H__
#define __GOL_FUNCTION_H__
    
#undef COMMON_EXT
#ifdef __GOL_FUNCTION_C__
#define COMMON_EXT
#else
#define COMMON_EXT  extern
#endif

extern const uchar ucZeroArray[16];

//数组长度计算宏定义
#define ArrayLen(a) (sizeof(a)/sizeof(a[0]))

#define TEST_OK     1
#define TEST_FAIL   0

#define OCT_TO_HEX(ch)      ( (((ch)/10)<<4) + ((ch)%10) )

ulong HexFromRam3Bcd(uchar *pSrc);
u16  HexFromRam2Bcd(uchar *pSrc);
uchar HexFromRam1Bcd(uchar *pSrc);

COMMON_EXT uchar ByteToBCD( uchar Data );
COMMON_EXT uchar BCDToByte(uchar Data);

COMMON_EXT uchar OneByteHexToBcd(uchar a);

COMMON_EXT uchar OneByteBcdToHex(uchar a);

COMMON_EXT uchar TestBcd(uchar a);

COMMON_EXT uchar TestAddr(uchar a);

COMMON_EXT uchar TestBcdNum(uchar *point, uchar num);

COMMON_EXT uchar TestZeroNum(uchar *point, uchar num);

COMMON_EXT uchar Test99Num(uchar *point, uchar num);

COMMON_EXT uchar TestYear(uchar a);

COMMON_EXT uchar TestMonth(uchar a);

COMMON_EXT uchar TestDay(uchar a);

COMMON_EXT uchar TestWeek(uchar a);

COMMON_EXT uchar TestHour(uchar a);

COMMON_EXT uchar TestMinute(uchar a);

COMMON_EXT uchar TestSecond(uchar a);

COMMON_EXT uchar ValueBcdFromHex(uchar a);

COMMON_EXT uchar ValueHexFromBcd(uchar a);

COMMON_EXT uchar  Byte1BcdAdd(uchar ucValue);

COMMON_EXT ulong ValueHexFromRam3Bcd(ulong ulRamaddr);

COMMON_EXT u16 ValueHexFromRam2Bcd(ulong ulRamaddr);
    
COMMON_EXT uchar Byte1BcdRamAdd10(ulong ulRamaddr);

COMMON_EXT uchar Byte1BcdRamAdd(ulong ulRamaddr);

COMMON_EXT void Byte2BcdRamAdd(ulong ulRamaddr);

COMMON_EXT void Byte3BcdRamAdd(ulong ulRamaddr);

COMMON_EXT void Byte4BcdRamAdd(ulong ulRamaddr);

COMMON_EXT void Byte5BcdRamAdd(ulong ulRamaddr);

COMMON_EXT void Byte1HexTo8Bit(uchar ucData,uchar * ucDataOut);

COMMON_EXT uchar WeekDay20( uchar *upDay);
COMMON_EXT uchar WeekFromDayMonthYear(uchar *day);


COMMON_EXT uchar TestDayMonthYear(uchar *day);

COMMON_EXT uchar TestSecondMinuteHourDayMonthYear(uchar *second,uchar *day);

COMMON_EXT uchar TestMinuteHour(uchar *point);

COMMON_EXT uchar TestDayMonth(uchar *point);

COMMON_EXT u16 NumDayFromDate(uchar *ucpDay);

COMMON_EXT void LongToData2BCD(ulong value, uchar *point);
COMMON_EXT void LongToData4BCD(ulong value, uchar *point);
COMMON_EXT void LongToData5BCD(ulong value, uchar *point);

COMMON_EXT ulong Bcd5DataToLong(uchar *Ptr);

COMMON_EXT ulong Bcd4DataToLong(uchar *Ptr);

COMMON_EXT uchar testcuofengshiduan(uchar *point);

COMMON_EXT uchar CompareDateTime(u16 l1,uchar *second,uchar *day);

COMMON_EXT void Byte5BcdPointAdd10(uchar *point,uchar ucAddData);


COMMON_EXT uchar CommCalChksum(uchar *ucStartPoint,uchar ucDataLen);

COMMON_EXT ulong Bcd3DataToLong(uchar *Ptr);

COMMON_EXT u16 Bcd2DataToInt(uchar *Ptr);

COMMON_EXT void IntToData2BCD(u16 value,uchar *point);

COMMON_EXT void LongToData3BCD(ulong value,uchar *point);

COMMON_EXT uchar Data3ByteBCDAdd1(ulong ulAddr);

COMMON_EXT void SetTimeDataToPoint(uchar *ucPoint);
COMMON_EXT void SetmmhhDDMMYYToPoint(uchar *ucPoint);

COMMON_EXT void SetEventStartDataLossVoltagetoAddr(uchar *ucPoint);
COMMON_EXT void SetEventEndDataLossVoltagetoAddr(uchar *ucPoint);

COMMON_EXT void SetAPhaseCurrentDataToAddr(uchar *ucPoint);
COMMON_EXT void SetBPhaseCurrentDataToAddr(uchar *ucPoint);
COMMON_EXT void SetCPhaseCurrentDataToAddr(uchar *ucPoint);

COMMON_EXT void SetAPhaseDataToRamAddr(u16 uiRamAddr);

COMMON_EXT void SetBPhaseDataToRamAddr(u16 uiRamAddr);

COMMON_EXT void SetCPhaseDataToRamAddr(u16 uiRamAddr);

COMMON_EXT uchar TranslateStatus0or1(uchar *status,uchar *status_use,uchar *continue_time,uchar value,uchar input_status);

COMMON_EXT void NextDayFromPoint(uchar *ucPDay);

COMMON_EXT void PerDayFromPoint(uchar *ucPDay);

COMMON_EXT void DateFromNumDay(u16 uiDataNum,uchar *ucpDay);

COMMON_EXT ulong  mmHHDDMMYYToLong(uchar *ucPoint);

COMMON_EXT void LongTommHHDDMMYY(ulong ulData,uchar *ucPoint);

COMMON_EXT void EventDataTotalClr(uchar ucType);
    
COMMON_EXT uchar EventAllDataClr(uchar ucType);

COMMON_EXT uchar MeterAllDataClr(uchar ucType);


COMMON_EXT uchar EventLossVoltageClr(uchar ucType);

COMMON_EXT uchar EventDownVoltageClr(uchar ucType);


COMMON_EXT uchar EventOverVoltageClr(uchar ucType);


COMMON_EXT uchar EventCutVoltageClr(uchar ucType);



COMMON_EXT uchar EventAllLossVoltageClr(uchar ucType);

COMMON_EXT uchar EventAuxPowerClr(uchar ucType);


COMMON_EXT uchar EventOrderVoltageClr(uchar ucType);

COMMON_EXT uchar EventOrderCurrentClr(uchar ucType);

COMMON_EXT uchar EventUnbalanceVoltageClr(uchar ucType);

COMMON_EXT uchar EventUnbalanceCurrentClr(uchar ucType);


COMMON_EXT uchar EventLossCurrentClr(uchar ucType);


COMMON_EXT uchar EventOverCurrentClr(uchar ucType);

COMMON_EXT uchar EventCutCurrentClr(uchar ucType);

COMMON_EXT uchar EventReversePowerClr(uchar ucType);


COMMON_EXT uchar EventOverPowerClr(uchar ucType);
COMMON_EXT uchar EventRelayOpenClr(uchar ucType);
COMMON_EXT uchar EventRelayCloseClr(uchar ucType);
COMMON_EXT uchar EventOverTotalCosClr(uchar ucType);
COMMON_EXT uchar EventBroadCastTimeClr(uchar ucType);
COMMON_EXT uchar EventMoniterClr(uchar ucType);

COMMON_EXT uchar EventPowerOffClr(uchar ucType);

COMMON_EXT uchar EventDemandOverClr(uchar ucType);

COMMON_EXT uchar EventProgramRecordClr(uchar ucType);

COMMON_EXT uchar EventProgramPowerClrRecordClr(uchar ucType);

COMMON_EXT uchar EventProgramDemandClrRecordClr(uchar ucType);


COMMON_EXT uchar EventProgramEventClrRecordClr(uchar ucType);


COMMON_EXT uchar EventProgramTimeRecordClr(uchar ucType);


COMMON_EXT uchar EventProgramDayTableRecordClr(uchar ucType);

COMMON_EXT uchar EventProgramSeasonTableRecordClr(uchar ucType);

COMMON_EXT uchar EventProgramCharacterRestRecordClr(uchar ucType);


COMMON_EXT uchar EventProgramHolidayRecordClr(uchar ucType);

COMMON_EXT uchar EventProgramCharacterActiveRecordClr(uchar ucType);


COMMON_EXT uchar EventProgramCharacterReActive01RecordClr(uchar ucType);


COMMON_EXT uchar EventProgramCharacterReActive02RecordClr(uchar ucType);


COMMON_EXT uchar EventProgramBalanceDayRecordClr(uchar ucType);

COMMON_EXT uchar EventBuyMoneyRecordClr(uchar ucType);

COMMON_EXT uchar EventBuyKwhRecordClr(uchar ucType);

COMMON_EXT uchar EventCoverOpenClr(uchar ucType);

COMMON_EXT uchar EventTerminalOpenOpenClr(uchar ucType);


COMMON_EXT uchar EventProgramOpenOpenClr(uchar ucType);

COMMON_EXT uchar EventClrFromCodeCan(ulong ulTCode);

COMMON_EXT uchar EventClrFromCode(ulong ulCode);


COMMON_EXT u16 ValueHexFrom3BcdRam(u16 uiRamAddr);



COMMON_EXT uchar  TimeChangedmmhhDDMMYYFromAddr(ulong ulTimeAddr);
COMMON_EXT uchar  TimeChangedhhDDMMYYFromAddr(ulong ulTimeAddr);


COMMON_EXT void SavemmhhDDMMYYtoAddr(ulong ulTimeAddr);


COMMON_EXT uchar Byte1PointBCDAdd1(uchar *Point);

COMMON_EXT uchar ByteNPointBCDAdd1(uchar * Point,uchar ucNum);

COMMON_EXT void SaveProgramTime(void);
COMMON_EXT void SavePasswordInf(void);

COMMON_EXT uchar JudgeUartParaWord(uchar word,uchar* uartPara);
COMMON_EXT u16 TestBcdNum2(uchar *point, u16 num);

COMMON_EXT u16 Sqrt32to16(ulong m) ;

COMMON_EXT void SetCurrentTime(void);

COMMON_EXT uchar JudjeFunction05Ib(uchar ucType);
COMMON_EXT uchar JudjeFunction01Ib(void);

COMMON_EXT void SysDelayMs(vu32 nMs);
COMMON_EXT void Delay(vu32 nCount);
//COMMON_EXT void  Delay1mS(void);
#define Delay1mS()  SysDelayMs(1)

#define BitValue(BitOffset) (1<<(BitOffset))
#if(BIT_VAR_ENABLE == GAL_YES)
// 把“位带地址＋位序号”转换别名地址宏 
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
//把该地址转换成一个指针 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)  (MEM_ADDR(BITBAND(addr, bitnum)))
#endif

#endif






