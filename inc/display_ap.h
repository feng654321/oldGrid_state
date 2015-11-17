#ifndef DISPLAY_AP_H
    #define DISPLAY_AP_H
    
#ifdef  DISPLAY_AP_GLOBALS
    #define DISPLAY_AP_EXT
#else
    #define DISPLAY_AP_EXT extern
#endif


#define LCD_FIGURE_NUM                      1       //数字显示行数

#define TAKE_TURN_DISPLAY_LIST_START_ADDR   EPL_DISPLAY_AUTOSET_START
#define KEY_TURN_DISPLAY_LIST_START_ADDR    EPL_DISPLAY_KEYSET_START
#define DISPLAY_PARA_START_ADDR             RAM_COEF_AUTO_TURNPAGE_NUM
#define KEY_TURN_DISPLAY_B_LIST_START_ADDR  (KEY_TURN_DISPLAY_LIST_START_ADDR+100*5)
#if(CONFIG_METER_FACTORY_MODE==CONFIG_METER_FACTORY_MODE_ENABLE)
#define START_FULL_SCREEN_DISPLAY_TIME      2   //S
#else
#define START_FULL_SCREEN_DISPLAY_TIME      2   //S
#endif

#define MAX_DISPLAY_ITEM        200     //max display item
#define MAX_DISPLAY_MODE        4       //max display type(mode)

#define MEMORY_ONE_LOG_LEN      10

#define TAKE_TURN_DISPLAY_MODE  0
#define KEY_TURN_DISPLAY_MODE   1
#define APPOINT_DISPLAY_MODE    2
#define CARD_DISPLAY_MODE       3
#define COMM_DISPLAY_MODE       4

////#pragma pack(push, 4)
typedef  struct
{  
    ulong id[LCD_FIGURE_NUM];   //当前显示的ID
    uchar itemNum[MAX_DISPLAY_MODE];                        //轮显的总项数
    uchar currentItem[MAX_DISPLAY_MODE][LCD_FIGURE_NUM];    //指向当前要显示的序号
    uchar turnTime[MAX_DISPLAY_MODE];                   //自动轮显的时间。由用户设定
    uchar idSerialNumber[LCD_FIGURE_NUM];
    uchar screenNoData[LCD_FIGURE_NUM][4];  //当前显示小8
    uchar holdData[LCD_FIGURE_NUM][2];
    uchar energyDec;
    uchar powerDec;
    uchar lcdFigureNum:3;   //当前显示LCD行
    uchar displayMode:4;
    uchar displayModeChangeFlag:1;
    uchar displayRefalshFlag:1;
    uchar displayTurnPageFlag:1;
    uchar displayModeTurnFlag:1;
    uchar displayRefalshEn:1; 
    uchar dispalyObis:1; 
    uchar displayShowAlarm:1;
}ST_DISPLAY_CONTROL;
////#pragma pack(pop)

typedef  struct
{  
    uchar especiallyDispalyMode:2;
    uchar especiallyDispalyFlag:1;
    uchar currentItem;
    uchar maxItem;
}ST_ESPECIALLY_DISPLAY_CONTROL;


#define DOWN_TURN   2
#define UP_TURN     1
typedef  struct
{  
    uchar displayMode;
    ulong id;
    uchar idSerialNumber;
    uchar turnType;
}ST_DISPLAY_MODE_CHANGE;


DISPLAY_AP_EXT ST_DISPLAY_CONTROL displayControl;
DISPLAY_AP_EXT uchar displayFlag,LCDSwitchFlag;
//DISPLAY_AP_EXT STR_CALENDAR rtcClock;
DISPLAY_AP_EXT ST_ESPECIALLY_DISPLAY_CONTROL especiallyDisplayControl;

DISPLAY_AP_EXT uchar cardErrorTypeBak;

#if(CONFIG_METER_AREA_MODE_SICHUAN==CONFIG_METER_AREA_MODE)
DISPLAY_AP_EXT uchar displayBTableItemNum;
DISPLAY_AP_EXT uchar displayATableItemNumTemp;
#endif

DISPLAY_AP_EXT void InitDisplayControl(uchar type);
DISPLAY_AP_EXT void Display(void);

DISPLAY_AP_EXT void SpringDifferentDisplayMode(ST_DISPLAY_MODE_CHANGE* typeData);

DISPLAY_AP_EXT void CheckDisplayControl(void);
DISPLAY_AP_EXT u16 GetShowAutoDisplay1Cycle(void);
DISPLAY_AP_EXT u16 SearchInDispList(ulong id,uchar idSerialNumber);
DISPLAY_AP_EXT u16 SearchInDispListCom(ulong id,uchar idSerialNumber);
DISPLAY_AP_EXT void SetCommDisplayDI(uchar * pData);
DISPLAY_AP_EXT void GetCommDisplayDI(ST_DISPLAY_MODE_CHANGE *stTemp);

DISPLAY_AP_EXT void GetDisplayInformation(ST_DISPLAY_CONTROL* controlData);
#if(CONFIG_METER_AREA_MODE_SICHUAN==CONFIG_METER_AREA_MODE)
DISPLAY_AP_EXT void KeyDisplayAtoBChange(void);
#endif

#endif

