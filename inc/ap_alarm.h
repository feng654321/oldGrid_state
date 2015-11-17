#ifndef __AP_ALARM_H__
#define __AP_ALARM_H__

#ifdef  AP_ALARM_GLOBALS
    #define AP_ALARM_EXT
#else
    #define AP_ALARM_EXT extern
#endif  
//#include "gol_struct.h"
#define TYPE_ALARM_TOTAL                    (32)

#define TYPE_ALARM_HARD_ERR                 0   //  AA  Ӳ������    AA
#define TYPE_ALARM_TIME_ERR                 1   //  AA  ʱ��оƬ��  AA
#define TYPE_ALARM_TMP_ERR                  2   //  AA  �¶�оƬ��  AA
#if(CONFIG_METER_AREA_MODE_ZHEJIANG_HANGZHOU == CONFIG_METER_AREA_MODE)
#define TYPE_ALARM_PREPAY_RELAY_ORDER_STATE 2   // AA �̵���Զ��������բ���� AA
#endif
#define TYPE_ALARM_PREPAY_RELAY_CTRL        3   //  AA  �̵������Ʊ���  AA
#define TYPE_ALARM_PREPAY_MOMEY_CTRL        4   //  AA  Ƿ�ѱ���(�������1���������2��)    AA
#define TYPE_ALARM_BATWAKEUP        5   //  AA  ͣ�����Ƿѹ    AA
#define TYPE_ALARM_BATTIMELOW       6   //  AA  ʱ�ӵ��Ƿѹ    AA
#define TYPE_ALARM_CONTROL_ERR      7   //  AA  �̵������Ƴ���  AA
#define TYPE_ALARM_LOSSVOLTAGE      8   //  AA  ʧѹ    AA
#define TYPE_ALARM_DOWNVOLTAGE      9   //  AA  Ƿѹ    AA
#define TYPE_ALARM_OVERVOLTAGE      10  //  AA  ��ѹ    AA
#define TYPE_ALARM_CUTVOLTAGE       11  //  AA  ����    AA
#define TYPE_ALARM_ALLLOSSVOLTAGE   12  //  AA  ȫʧѹ  AA
#define TYPE_ALARM_LOSSACPOWER      13  //  AA  ������Դ����    AA
#define TYPE_ALARM_ORDERVOLTAGE     14  //  AA  ��ѹ������  AA
#define TYPE_ALARM_ORDERCURRENT     15  //  AA  ����������  AA
#define TYPE_ALARM_UNBALANCEVOLTAGE 16  //  AA  ��ѹ��ƽ��  AA
#define TYPE_ALARM_UNBALANCECURRENT 17  //  AA  ������ƽ��  AA
#define TYPE_ALARM_LOSSCURRENT      18  //  AA  ʧ��    AA
#define TYPE_ALARM_OVERCURRENT      19  //  AA  ����    AA
#define TYPE_ALARM_CUTCURRENT       20  //  AA  ����    AA
#define TYPE_ALARM_REVERSEKW_ABC    21  //  AA  ���๦�ʷ���    AA
#define TYPE_ALARM_OVERKW_ABC       22  //  AA  ���๦�ʹ���    AA
#define TYPE_ALARM_REVERSEKW_ALL    23  //  AA  �ܹ��ʷ���  AA
#define TYPE_ALARM_OVERKW_ALL       24  //  AA  �ܹ��ʹ���  AA
#define TYPE_ALARM_OVERDEMAND       25  //  AA  �������ޱ���    AA
#define TYPE_ALARM_COVEROPEN        26  //  AA  ��ǿ���    AA
#define TYPE_ALARM_TERMINALOPEN     27  //  AA  ��ť�ǿ���  AA
// #define  TYPE_ALARM_PROGRAMOPEN  28  //  AA  ��̸ǿ���  AA
#define TYPE_ALARM_UNBALANCESEVERITYCURRENT 28  //  AA  �������ز�ƽ�ⱨ��  AA
#define TYPE_ALARM_OVERTOTALCOS     29  //  AA  ������������    AA
#define TYPE_ALARM_CARD_ERR         30  //  AA  ���ڳ�ʼ������  AA
#define TYPE_ALARM_ESAM_ERR         31  //  AA  ESAM ����   AA

#define CON_ALARM_STATUS_START      0
#define CON_ALARM_STATUS_STOP       1

#define CON_ALARM_SPEEK_ALRAM_TIME_MAX      (300)

#define TYPE_LCD_DISPLAY_ERR_CONTROL        (TYPE_ALARM_CONTROL_ERR)    //0x01
#define TYPE_LCD_DISPLAY_ERR_ESAM           (TYPE_ALARM_ESAM_ERR)       //0x02
#define TYPE_LCD_DISPLAY_ERR_CARD           (TYPE_ALARM_CARD_ERR)       //0x04
#define TYPE_LCD_DISPLAY_ERR_BATTIMELOW     (TYPE_ALARM_BATTIMELOW)     //0x08
#define TYPE_LCD_DISPLAY_ERR_PROGRAMDATA    (0xff)                      //0x10    //no meaning
#define TYPE_LCD_DISPLAY_ERR_HARD_ERR       (TYPE_ALARM_HARD_ERR)       //0x20
#define TYPE_LCD_DISPLAY_ERR_TIME_ERR       (TYPE_ALARM_TIME_ERR)       //0x40
#define TYPE_LCD_DISPLAY_ERR_ADC_ERR        (32)       
#define TYPE_LCD_DISPLAY_ERR_EPL_ERR        (33)       
#define TYPE_LCD_DISPLAY_ERR_FLASH_ERR      (34)       
#define TYPE_LCD_DISPLAY_ERR_RTC_ERR        (35)       


#define TYPE_LCD_DISPLAY_ALARM_OVERPOWER    (TYPE_ALARM_OVERKW_ABC)     //0x01
#define TYPE_LCD_DISPLAY_ALARM_UNBALANCESEVERITYCURRENT     (TYPE_ALARM_UNBALANCESEVERITYCURRENT)   //0x02
#define TYPE_LCD_DISPLAY_ALARM_OVERVOLTAGE  (TYPE_ALARM_OVERVOLTAGE)    //0x04
#define TYPE_LCD_DISPLAY_ALARM_OVERTOTALCOS (TYPE_ALARM_OVERTOTALCOS)   //0x08
#define TYPE_LCD_DISPLAY_ALARM_OVERDEMADNKW (TYPE_ALARM_OVERDEMAND)     //0x10
#if ((CONFIG_METER_AREA_MODE_QINGHAI == CONFIG_METER_AREA_MODE) && (GAL_YES == CONFIG_METER_MULTI_FUNCTION))
#define TYPE_LCD_DISPLAY_ALARM_UNBALANCECURRENT     (TYPE_ALARM_UNBALANCECURRENT)   //0x20
#else
#define TYPE_LCD_DISPLAY_ALARM_REVERSEKW_ALL        (TYPE_ALARM_REVERSEKW_ALL)      //0x20
#endif

#define CHECK_ALARM_TYPE_LCDALARM_ALLOWEDLY(ucCharName, ucCharBit)    (ucCharBit == (RAM[RAM_COEF_ALARM_LCD_DISPLLAY +ucCharName]&ucCharBit))
#define CHECK_ALARM_TYPE_LCDERR_ALLOWEDLY(ucCharName, ucCharBit)    (ucCharBit == (RAM[RAM_COEF_ALARM_LCD_ERROR +ucCharName]&ucCharBit))


AP_ALARM_EXT u16 uiAlarmSpeekAlarmTime;
AP_ALARM_EXT uchar ucAlarmSpeekTempTimer;
AP_ALARM_EXT uchar ucAlarmSpeekCardReadSpeek;

#define CON_ALARM_TYPE_BYTE_MAX   (TYPE_ALARM_TOTAL/8)
#define CON_ALARM_LEDGREEN_ENABLE   (GAL_YES)

#if 0
//AP_ALARM_EXT uchar ucAlarmStatusSpeek[CON_ALARM_TYPE_BYTE_MAX];
//AP_ALARM_EXT uchar ucAlarmStatusLedYellow[CON_ALARM_TYPE_BYTE_MAX];
#if(CON_ALARM_LEDGREEN_ENABLE == GAL_YES)
//AP_ALARM_EXT uchar ucAlarmStatusLedGreen[CON_ALARM_TYPE_BYTE_MAX];
#endif
//AP_ALARM_EXT uchar ucAlarmStatusLcdDisplay[CON_ALARM_TYPE_BYTE_MAX];
//AP_ALARM_EXT uchar ucAlarmStatusLcdError[CON_ALARM_TYPE_BYTE_MAX];
#else
#define ucAlarmStatusSpeek          ( (uchar*)(&RAM[RAM_ALARM_SPEEK_STATUS]) )          // 4 byte  HEX ������״̬��
#define RAM_ALARM_SPEEK_STATUS_LEN              4
#define ucAlarmStatusLedYellow      ( (uchar*)(&RAM[RAM_ALARM_LEDYELLOW_STATUS]) )      // 4 byte  HEX �ƹⱨ��״̬��
#define RAM_ALARM_LEDYELLOW_STATUS_LEN          4
#if(CON_ALARM_LEDGREEN_ENABLE == GAL_YES)
#define ucAlarmStatusLedGreen       ( (uchar*)(&RAM[RAM_ALARM_LEDGREEN_STATUS]) )       // 4 byte  HEX �̹ⱨ��״̬��
#define RAM_ALARM_LEDGREEN_STATUS_LEN           4
#endif
#define ucAlarmStatusLcdDisplay     ( (uchar*)(&RAM[RAM_ALARM_LCD_DISPLLAY_STATUS]) )   // 4 byte  HEX Һ�����Ա���״̬��
#define RAM_ALARM_LCD_DISPLLAY_STATUS_LEN       4
#define ucAlarmStatusLcdError       ( (uchar*)(&RAM[RAM_ALARM_LCD_ERROR_STATUS]) )      // 4 byte  HEX Һ�����󱨾�״̬��
#define RAM_ALARM_LCD_ERROR_STATUS_LEN          4
#endif

AP_ALARM_EXT uchar errorDisplaycurrentItem,alarmDisplaycurrentItem;


#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
AP_ALARM_EXT u16 uiAlarmDisplayCardReadTimes;
#endif
AP_ALARM_EXT uchar ucAlarmErrBlackLightHave;
AP_ALARM_EXT uchar ucAlarmStatusSpeekLast[CON_ALARM_TYPE_BYTE_MAX];
// �¼������жϱ�־,��Ҫ����з�����¼�
//#define RAM_COEF_ALARM_NEWEVENT (RAM_COEF_ALARM_LEDGREEN)
#if(BIT_VAR_ENABLE == GAL_YES)
#define FLG_ALARM_STATUE_SPEEK_LAST(type)   BIT_ADDR( (u32)(&ucAlarmStatusSpeekLast[type>>3]),type&0x7)
#define FLG_LOSS_VOLTAGE_ALARM  FLG_ALARM_STATUE_SPEEK_LAST(TYPE_ALARM_LOSSVOLTAGE)
#define FLG_DOWN_VOLTAGE_ALARM  FLG_ALARM_STATUE_SPEEK_LAST(TYPE_ALARM_DOWNVOLTAGE)
#define FLG_OVER_VOLTAGE_ALARM  FLG_ALARM_STATUE_SPEEK_LAST(TYPE_ALARM_OVERVOLTAGE)
#define FLG_CUT_VOLTAGE_ALARM   FLG_ALARM_STATUE_SPEEK_LAST(TYPE_ALARM_CUTVOLTAGE)
#define FLG_LOSS_CURRENT_ALARM  FLG_ALARM_STATUE_SPEEK_LAST(TYPE_ALARM_LOSSCURRENT)
#define FLG_OVER_CURRENT_ALARM  FLG_ALARM_STATUE_SPEEK_LAST(TYPE_ALARM_OVERCURRENT)
#define FLG_CUT_CURRENT_ALARM   FLG_ALARM_STATUE_SPEEK_LAST(TYPE_ALARM_CUTCURRENT)
#define FLG_REVERSEKW_ABC_ALARM FLG_ALARM_STATUE_SPEEK_LAST(TYPE_ALARM_REVERSEKW_ABC)
#define FLG_OVERKW_ABC_ALARM    FLG_ALARM_STATUE_SPEEK_LAST(TYPE_ALARM_OVERKW_ABC)
#else
#define FLG_LOSS_VOLTAGE_ALARM  ((UN_U32_PARAM*)(&ucAlarmStatusSpeekLast[0]))->Bit2s.b10
#define FLG_DOWN_VOLTAGE_ALARM  ((UN_U32_PARAM*)(&ucAlarmStatusSpeekLast[0]))->Bit2s.b11
#define FLG_OVER_VOLTAGE_ALARM  ((UN_U32_PARAM*)(&ucAlarmStatusSpeekLast[0]))->Bit2s.b12
#define FLG_CUT_VOLTAGE_ALARM   ((UN_U32_PARAM*)(&ucAlarmStatusSpeekLast[0]))->Bit2s.b13
#define FLG_LOSS_CURRENT_ALARM  ((UN_U32_PARAM*)(&ucAlarmStatusSpeekLast[0]))->Bit2s.b22
#define FLG_OVER_CURRENT_ALARM  ((UN_U32_PARAM*)(&ucAlarmStatusSpeekLast[0]))->Bit2s.b23
#define FLG_CUT_CURRENT_ALARM   ((UN_U32_PARAM*)(&ucAlarmStatusSpeekLast[0]))->Bit2s.b24
#define FLG_REVERSEKW_ABC_ALARM ((UN_U32_PARAM*)(&ucAlarmStatusSpeekLast[0]))->Bit2s.b25
#define FLG_OVERKW_ABC_ALARM    ((UN_U32_PARAM*)(&ucAlarmStatusSpeekLast[0]))->Bit2s.b26
#endif

typedef  struct
{  
	ulong id;
	uchar errorType;
	uchar idSerialNumber;
    uchar ucErrShow;
}ERROR_DISPLAY_INFORMATION;

#if(CONFIG_METER_FACTORY_MODE_ENABLE == CONFIG_METER_FACTORY_MODE)
#define ALARM_ERR_DISPLAY_NUM           (11)
#else
#define ALARM_ERR_DISPLAY_NUM           (7)
#endif
#define ALARM_ALARM_DISPLAY_NUM         (6)
extern const ERROR_DISPLAY_INFORMATION errorDisplayInformation[ALARM_ERR_DISPLAY_NUM];
extern const ERROR_DISPLAY_INFORMATION alarmDisplayInformation[ALARM_ALARM_DISPLAY_NUM];

AP_ALARM_EXT void AlarmParaInit(void);

AP_ALARM_EXT void AlarmDoLedSpeek(uchar value,uchar type);
AP_ALARM_EXT void AlarmSpeekAlarmClr(void);
AP_ALARM_EXT uchar ucAlarmLedStatus;
AP_ALARM_EXT void AlarmMode(void);
AP_ALARM_EXT void AlarmInit(void);
AP_ALARM_EXT void AlarmSpeekAlarmCardReadTime(u16 uiTimes,uchar ucTimeStart);
AP_ALARM_EXT void AlarmClrAll(void);

#define CON_DISPLAY_ALARM_DATATYPE_ALRAM    0x00
#define CON_DISPLAY_ALARM_DATATYPE_ERR      0x01
AP_ALARM_EXT void AlarmDisplayLcdDataInit(void);
AP_ALARM_EXT void GetAlarmDisplayLcdData(uchar *ucReturnBuffer,uchar ucDataId,uchar ucType);
AP_ALARM_EXT uchar SearchErrorDisplayInformation(ulong *id, uchar *idSerialNumber);
AP_ALARM_EXT uchar SearchAlarmDisplayInformation(ulong *id, uchar *idSerialNumber);


#endif  

