#ifndef __GOL_STRUCT_H__
#define __GOL_STRUCT_H__
typedef struct
{
    uchar ucSecond;
    uchar ucMinute;
    uchar ucHour;
    //uchar ucWeek;
    uchar ucDay;
    uchar ucMonth;
    uchar ucYear;
    uchar ucWeek;
}ST_DATE_TIME_PARAM;

typedef struct
{
    uchar bBit0Reserve:1;
    uchar bDemandCalcMode:1;
    uchar bBatTimeStatus:1;
    uchar bBatWakeupStatus:1;
    uchar bReverseKw:1;
    uchar bReverseKvar:1;
    uchar bBit6Reserve:1;
    uchar bBit7Reserve:1;
    uchar c1Reserve;
//}ST_METERSTATUS_CHAR1_PARAM;

//typedef struct
//{
    uchar bAKwReverse:1;
    uchar bBKwReverse:1;
    uchar bCKwReverse:1;
    uchar bBit3Reserve:1;
    uchar bAKvarReverse:1;
    uchar bBKvarReverse:1;
    uchar bCKvarReverse:1;
    uchar bBit27Reserve:1;
    uchar c2Reserve;
}ST_METERSTATUS_CHAR_1_2_PARAM;

typedef struct
{
    uchar bDayTableStatus:1;        //b0
    uchar bPowerMode:2;             //b1-b2
    uchar bProgramStatus:1;         //b3
    uchar bRelayStatus:1;           //b4
    uchar bSeasonStatus:1;          //b5
    uchar bRelayCommandStatus:1;    //b6
    uchar bRelayPreAlarmStatus:1;   //b7
    uchar bMeterPrePayType:2;       //b8 b9
    uchar bPeriodPriceTableStatus:1;//b10
    uchar bStepPriceTableStatus:1;  //b11
    uchar bBit12Reserve:1;          // b12
    uchar bBit13Reserve:1;          // b13
    uchar bBit14Reserve:1;          // b14
    uchar bBit15Reserve:1;          // b15
//}ST_METERSTATUS_CHAR3_PARAM;

//typedef struct
//{
    uchar bLossVoltage:1;
    uchar bDownVoltage:1;
    uchar bOverVoltage:1;
    uchar bLossCurrent:1;
    uchar bOverCurrent:1;
    uchar bOverKw:1;
    uchar bReverseKw:1;
    uchar bCutVoltage:1;
    uchar bCutCurrent:1;
    uchar bBit2Reserve:7;
}ST_METERSTATUS_CHAR_3_4_PARAM;

typedef struct
{
    uchar bBLossVoltage:1;
    uchar bBDownVoltage:1;
    uchar bBOverVoltage:1;
    uchar bBLossCurrent:1;
    uchar bBOverCurrent:1;
    uchar bBOverKw:1;
    uchar bBReverseKw:1;
    uchar bBCutVoltage:1;
    uchar bBCutCurrent:1;
    uchar bBBit9Reserve:1;
    uchar bBBit10Reserve:1;
    uchar bBBit11Reserve:1;
    uchar bBBit12Reserve:1;
    uchar bBBit13Reserve:1;
    uchar bBBit14Reserve:1;
    uchar bBBit15Reserve:1;

    uchar bLossVoltage:1;
    uchar bDownVoltage:1;
    uchar bOverVoltage:1;
    uchar bLossCurrent:1;
    uchar bOverCurrent:1;
    uchar bOverKw:1;
    uchar bReverseKw:1;
    uchar bCutVoltage:1;
    uchar bCutCurrent:1;
    uchar bBit2Reserve:7;
}ST_METERSTATUS_CHAR_5_6_PARAM;

typedef struct
{
    uchar bOrderVoltage:1;
    uchar bOrderCurrent:1; 
    uchar bUnbalanceVoltage:1;
    uchar bUnbalanceCurrent:1;
    uchar bLossACPower:1;
    uchar bLossPower:1;
    uchar bDemandOver:1;
    uchar bOverTotalCos:1;
    uchar bUnbalanceSeverityCurrent:1;
    uchar bBit9to15Reserve:7;
}ST_METERSTATUS_CHAR7_PARAM;

typedef union
{
    struct
    {
        uchar bVAStatus:2;
        uchar bVBStatus:2;
        uchar bVCStatus:2;
        uchar bVAllStatus:2;
    }Bits;
    uchar Ch;
}ST_MONITOR_VOLTAGE_STATUS_PARAM;


typedef struct
{
    uchar b0:1;
    uchar b1:1;
    uchar b2:1;
    uchar b3:1;
    uchar b4:1;
    uchar b5:1;
    uchar b6:1;
    uchar b7:1;
}ST_U8_PARAM;




typedef struct
{
    uchar b0:1;
    uchar b1:1;
    uchar b2:1;
    uchar b3:1;
    uchar b4:1;
    uchar b5:1;
    uchar b6:1;
    uchar b7:1;
    uchar b8:1;
    uchar b9:1;
    uchar b10:1;
    uchar b11:1;
    uchar b12:1;
    uchar b13:1;
    uchar b14:1;
    uchar b15:1;
}ST_U16_PARAM_ALLBIT;


typedef struct
{
    uchar ucLow;
    uchar ucHigh;
}ST_U16_PARAM_UCHAR;




typedef struct
{
    uchar ucData0;
    uchar ucData1;
    uchar ucData2;
    uchar ucData3;
}ST_U32_PARAM_ALLBYTE;



#if 0
typedef union
{
    struct
    {
        uchar bBit0Reserve:1;
        uchar bDemandCalcMode:1;
        uchar bBatTimeStatus:1;
        uchar bBatWakeupStatus:1;
        uchar bReverseKw:1;
        uchar bReverseKvar:1;
        uchar bBit6Reserve:1;
        uchar bBit7Reserve:1;
        uchar cReserve;
    }Bits;
    u16 uiData;
    u16 ucData[2];
}UN_METERSTATUS_CHAR1_PARAM;


typedef union
{
    struct
    {
        uchar bAKwReverse:1;
        uchar bBKwReverse:1;
        uchar bCKwReverse:1;
        uchar bBit3Reserve:1;
        uchar bAKvarReverse:1;
        uchar bBKvarReverse:1;
        uchar bCKvarReverse:1;
        uchar bBit7Reserve:1;
        uchar cReserve;
    }Bits;
    u16 uiData;
    uchar ucData[2];
}UN_METERSTATUS_CHAR2_PARAM;

typedef union
{
    struct
    {
        uchar bPeriodStatus:1;
        uchar bPowerMode:2;
        uchar bProgramStatus:1;
        uchar bRelayStatus:1;
        uchar bSeasonStatus:1;
        uchar bBit6Reserve:1;
        uchar bBit7Reserve:1;
        uchar cReserve;
    }Bits;
    u16 uiData;
    u16 ucData[2];
}UN_METERSTATUS_CHAR3_PARAM;

typedef union
{
    struct
    {
        uchar bLossVoltage:1;
        uchar bDownVoltage:1;
        uchar bOverVoltage:1;
        uchar bLossCurrent:1;
        uchar bOverCurrent:1;
        uchar bOverKw:1;
        uchar bReverseKw:1;
        uchar bCutVoltage:1;
        uchar bCutCurrent:1;
        uchar bBit9Reserve:1;
        uchar bBit10Reserve:1;
        uchar bBit11Reserve:1;
        uchar bBit12Reserve:1;
        uchar bBit13Reserve:1;
        uchar bBit14Reserve:1;
        uchar bBit15Reserve:1;
    }Bits;
    u16 uiData;
    u16 ucData[2];
}UN_METERSTATUS_CHAR4_5_6_PARAM;

typedef union
{
    struct
    {
        uchar bOrderVoltage:1;
        uchar bOrderCurrent:1; 
        uchar bUnbalanceVoltage:1;
        uchar bUnbalanceCurrent:1;
        uchar bLossACPower:1;
        uchar bLossPower:1;
        uchar bDemandOver:1;
        uchar bBit7Reserve:1;
        uchar cReserve;
    }Bits;
    u16 uiData;
    u16 ucData[2];
}UN_METERSTATUS_CHAR7_PARAM;
#endif



typedef union
{
    struct
    {
        uchar bKwFAdd:1;
        uchar bKwFSub:1; 
        uchar bKwRAdd:1;
        uchar bKwRSub:1;
        uchar bBit4Reserve:1;
        uchar bBit5Reserve:1;
        uchar bBit6Reserve:1;
        uchar bBit7Reserve:1;
    }Bits;
    struct
    {
        uchar b2KwF:2;
        uchar b2KwR:2;
        uchar b4Reserve:4;
    }Bit2DemandAdd;
    uchar ucData;
}UN_METERSTATUS_CHARACTER_ACTIVE_PARAM;

typedef union
{
    struct
    {
        uchar bKvarQ1Add:1;
        uchar bKvarQ1Sub:1;
        uchar bKvarQ2Add:1;
        uchar bKvarQ2Sub:1;
        uchar bKvarQ3Add:1;
        uchar bKvarQ3Sub:1;
        uchar bKvarQ4Add:1;
        uchar bKvarQ4Sub:1;
    }Bits;
    struct
    {
        uchar b2KvarQ1:2;
        uchar b2KvarQ2:2;
        uchar b2KvarQ3:2;
        uchar b2KvarQ4:2;
    }Bit2DemandAdd;
    uchar ucData;
}UN_METERSTATUS_CHARACTER_REACTIVE_PARAM;

typedef union
{
    struct
    {
        uchar bWeek0:1;
        uchar bWeek1:1;
        uchar bWeek2:1;
        uchar bWeek3:1;
        uchar bWeek4:1;
        uchar bWeek5:1;
        uchar bWeek6:1;
        uchar bBit7Reserve:1;
    }Bits;
    uchar ucData;
}UN_METERSTATUS_REST_DAY_PARAM;




typedef union
{
    struct
    {
        uchar bVoltageCurrent:1;
        uchar bKwKvar:1;
        uchar bFactor:1;
        uchar bKwhKvarh:1;
        uchar bKvarQ1234:1;
        uchar bDemand:1;
        uchar bBit6Reserve:1;
        uchar bBit7Reserve:1;
    }Bits;
    uchar ucData;
}UN_METERSTATUS_CHARGE_MODE_PARAM;




typedef union
{
    struct
    {
        uchar bKwhF:1;
        uchar bKwhR:1;
        uchar bKvarC1:1;
        uchar bKvarC2:1;
        uchar bKvarQ1234:1;
        uchar bDemandKwF:1;
        uchar bDemandKwR:1;
        uchar bBit7Reserve:1;
    }Bits;
    uchar ucData;
}UN_METERSTATUS_FREEZE_MODE_PARAM;




typedef union
{
    struct
    {
        uchar b0:1;
        uchar b1:1;
        uchar b2:1;
        uchar b3:1;
        uchar b4:1;
        uchar b5:1;
        uchar b6:1;
        uchar b7:1;
    }Bits;
    struct
    {
        uchar bLow4:4;
        uchar bHigh4:4;
    }bit4;
    uchar ucData;
}UN_U8_PARAM;




typedef union
{
     struct
    {
        uchar b0:1;
        uchar b1:1;
        uchar b2:1;
        uchar b3:1;
        uchar b4:1;
        uchar b5:1;
        uchar b6:1;
        uchar b7:1;
        uchar b8:1;
        uchar b9:1;
        uchar b10:1;
        uchar b11:1;
        uchar b12:1;
        uchar b13:1;
        uchar b14:1;
        uchar b15:1;
    }Bits;
    struct
    {
        uchar cLow;
        uchar cHigh;
    }uChars;
    u16 uiData;
    u16 ucData[2];
}UN_U16_PARAM;




typedef union
{
    struct
    {
        uchar b0:1;
        uchar b1:1;
        uchar b2:1;
        uchar b3:1;
        uchar b4:1;
        uchar b5:1;
        uchar b6:1;
        uchar b7:1;
        uchar b8:1;
        uchar b9:1;
        uchar b10:1;
        uchar b11:1;
        uchar b12:1;
        uchar b13:1;
        uchar b14:1;
        uchar b15:1;
        uchar b16:1;
        uchar b17:1;
        uchar b18:1;
        uchar b19:1;
        uchar b20:1;
        uchar b21:1;
        uchar b22:1;
        uchar b23:1;
        uchar b24:1;
        uchar b25:1;
        uchar b26:1;
        uchar b27:1;
        uchar b28:1;
        uchar b29:1;
        uchar b30:1;
        uchar b31:1;
    }Bits;
    struct
    {
        uchar b00:1;
        uchar b01:1;
        uchar b02:1;
        uchar b03:1;
        uchar b04:1;
        uchar b05:1;
        uchar b06:1;
        uchar b07:1;
        uchar b10:1;
        uchar b11:1;
        uchar b12:1;
        uchar b13:1;
        uchar b14:1;
        uchar b15:1;
        uchar b16:1;
        uchar b17:1;
        uchar b20:1;
        uchar b21:1;
        uchar b22:1;
        uchar b23:1;
        uchar b24:1;
        uchar b25:1;
        uchar b26:1;
        uchar b27:1;
        uchar b30:1;
        uchar b31:1;
        uchar b32:1;
        uchar b33:1;
        uchar b34:1;
        uchar b35:1;
        uchar b36:1;
        uchar b37:1;
    }Bit2s;
    struct
    {
        uchar ucData0;
        uchar ucData1;
        uchar ucData2;
        uchar ucData3;
    }cData;
    uchar ucbData[4];
    u16 uibData[2];
    struct
    {
        u16 uiData0;
        u16 uiData1;
    }iData;
    ulong ulData;
}UN_U32_PARAM;// __attribute__((__aligned__(1)));


typedef struct
    {
        uchar stKwhTpye;
        uchar stCanSub;
    }ST_KWH_RESUME_CANSUB_PARAM;





typedef union
{
    struct
        {
        uchar ucD0;
        uchar ucD1;
        uchar ucD2;
        uchar ucD3;
        }uCharMode;
    struct
        {
        u16 uiLow;
        u16 uiHigh;
        }uIntMode;
    ulong uLongMode;
}TYPE_LONG_INT_CHAR_UNION;



typedef struct
{
    uchar ucStoryType;
    uchar  uiShowLen;
    u16 ulDataAddr;
    u16 uiShowId;
    uchar ucPointShow;
}ST_TB_DISPLAY_PARAM;





typedef struct
{
    ulong ulCurrentAddr;
    ulong ulTotalAddr;
    uchar ucHourResidueId;
}ST_TB_APHOURCLAC_PARAM;


typedef union
{
    struct
        {
        uchar ucHour;

        uchar ucDay;
        }uInChar;
    uchar ucStart;
    u16 uiDataCode;
}UN_BALANCEDAY_TYPE_PARAM;


typedef struct
{
    uchar ucHour;
    uchar ucDay;
    uchar ucMonth;
    uchar ucYear;
}ST_BALANCEDAY_POWERON_BUFFER_PARAM;


typedef union
{
    double db;
    ulong ul[2];
}UN_DB_UL_TYPE_PARAM;




typedef struct
{
    uchar ucCharName;
    uchar ucCharBite;
}ST_ALARM_STATUS_BUFFER_PARAM;


typedef struct
{
    //ulong ulStartAddr;
    uchar ucBlockLen;
    //uchar ucPageBlockNum;
}ST_RECORD_TYPE_BUFFER_PARAM;

////#pragma pack(push, 4)
typedef union
{
    ulong l;
    uchar c[4];
}UN_LONG;
////#pragma pack(pop)

typedef union
{
    ulLong  ll;
    uchar c[8];
}UN_LONG_LONG;

#endif

