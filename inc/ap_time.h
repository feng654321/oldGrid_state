



#ifndef AP_TIME_H
    #define AP_TIME_H
    
#ifdef  AP_TIME_GLOBALS
    #define AP_TIME_EXT
#else
    #define AP_TIME_EXT extern
#endif  

#if(CONFIG_METER_AREA_MODE==CONFIG_METER_AREA_MODE_HUABEI)
#define LCD_BACKLIGHT_TIME_EVENT    (30)
#else
#define LCD_BACKLIGHT_TIME_EVENT    (60)
#endif
#define WAKEUP_TIME_EVENT           (30)

AP_TIME_EXT void second_change_dis_use(void);


// AP_TIME_EXT void rtc(void);

AP_TIME_EXT void zhongduan_8025_second_set(void);

AP_TIME_EXT void zhongduan_8025_second(void);

AP_TIME_EXT void rtc_tingdian(void);

AP_TIME_EXT void Start10msInt(void);

AP_TIME_EXT void Time10mSInterrupt(void);
AP_TIME_EXT void Time100uSInterrupt(void);

#if(BOARD_LOWCOST == HARD_WARE)
#define KEY_STATUS_DOWN   0          
#define KEY_STATUS_UP     1  
#define KEY_DOWN_MAP      0x00
#define KEY_UP_MAP      0x0f
#else
#define KEY_STATUS_DOWN   1          
#define KEY_STATUS_UP     0          
#define KEY_DOWN_MAP      0x0F
#define KEY_UP_MAP      0x00
#endif

AP_TIME_EXT UN_U8_PARAM ucKeyStatusAll;
AP_TIME_EXT UN_U8_PARAM ucKeyStatusEvent;
#define FLG_KEY_UP_STATUS  ucKeyStatusAll.Bits.b0
#define FLG_KEY_DOWN_STATUS  ucKeyStatusAll.Bits.b1
#define FLG_KEY_PROGRAM_STATUS  ucKeyStatusAll.Bits.b2
#define FLG_KEY_INFO_STATUS  ucKeyStatusAll.Bits.b3


#define FLG_KEY_UPKEY_UPEVENT       ucKeyStatusEvent.Bits.b0
#define FLG_KEY_UPKEY_DOWNEVENT ucKeyStatusEvent.Bits.b1    // �������£�״̬�仯
#define FLG_KEY_DOWNKEY_UPEVENT ucKeyStatusEvent.Bits.b2
#define FLG_KEY_DOWNKEY_DOWNEVENT   ucKeyStatusEvent.Bits.b3
#define FLG_KEY_PROGRAMKEY_UPEVENT  ucKeyStatusEvent.Bits.b4
#define FLG_KEY_PROGRAMKEY_DOWNEVENT    ucKeyStatusEvent.Bits.b5
#define FLG_KEY_INFOKEY_UPEVENT     ucKeyStatusEvent.Bits.b6
#define FLG_KEY_INFOKEY_DOWNEVENT   ucKeyStatusEvent.Bits.b7


AP_TIME_EXT uchar GetKeyStatus(void);

AP_TIME_EXT uchar  PopKeyEvent(void);

AP_TIME_EXT void SetKeyEvent(uchar ucEvent);



// ��ǰ������ң�������¼���� ��ʹ�ú궨��ö������
#define DISPLAY_EVENT_NO                0x00        // û���¼�
#define DISPLAY_EVENT_KEYDOWN           0x01        // �����·�
#define DISPLAY_EVENT_KEYUP             0x02        // �����Ϸ�
#define DISPLAY_EVENT_KEYPRO            0x03        // ������̼�
#define DISPLAY_EVENT_KEYINFO           0x04        // ������ѯ��

#define DISPLAY_EVENT_REMOTEOPEN        0x11        // ң�������ؼ�
#ifdef CONFIG_METER_REMOTE_INPUT_ENABLE
#define DISPLAY_EVENT_REMOTEUP          0x12        // ң�����Ϸ���
#define DISPLAY_EVENT_REMOTEDOWN        0x13        // ң�����·���
#define DISPLAY_EVENT_REMOTETURN        0x14        // ң�������Լ�
#define DISPLAY_EVENT_REMOTETIME        0x15        // ң����ʱ���
#define DISPLAY_EVENT_REMOTEPOINT       0x16        // ң�������
#endif 
#define DISPLAY_EVENT_REMOTECOMM        0x20        // ������ͨѶ
#define DISPLAY_EVENT_COMMDISPLAY       0x30        // Һ���鿴����


AP_TIME_EXT void TimeDeal(uchar ucRunType);

AP_TIME_EXT void TimeOneSecondChange(void);

AP_TIME_EXT void TimeOneSecondPowerOffChange(void);

AP_TIME_EXT u16 uiBackLightTime;
AP_TIME_EXT uchar ucTime500mSCount;

#endif



