
#define AP_REMOTE_GLOBALS
#include "common.h"
#if 0
extern u32 remoteKey;

/*
; ----华隆的遥控器的按键码对照表
;   按键    键值
;   关闭    0x00FF18E7
;   1       0x00FF00FF
;   2       0x00FF807F
;   3       0x00FF40BF
;   4       0x00FFC03F
;   5       0x00FF20DF
;   6       0x00FFA05F
;   7       0x00FF609F
;   8       0x00FFE01F
;   9       0x00FF10EF
;   0       0x00FF906F
;   轮显    0x00FF08F7
;   时间    0x00FFF00F
;   -1      0x00FF50AF
;   -2      0x00FFD02F
;   -3      0x00FF30CF
;   -4      0x00FFD827
;   -5      0x00FFF807
;   -6      0x00FF6897
;   -7      0x00FF7887
;   -8      0x00FFA857
;   上翻    0x00FF9867
;   下翻    0x00FF58A7
*/

#define REMOTE_HARDWARE_KEY_VALUE_OPEN  0x18E7  // AA   关闭    AA
#define REMOTE_HARDWARE_KEY_VALUE_01    0x00FF  // AA   1   AA
#define REMOTE_HARDWARE_KEY_VALUE_02    0x807F  // AA   2   AA
#define REMOTE_HARDWARE_KEY_VALUE_03    0x40BF  // AA   3   AA
#define REMOTE_HARDWARE_KEY_VALUE_04    0xC03F  // AA   4   AA
#define REMOTE_HARDWARE_KEY_VALUE_05    0x20DF  // AA   5   AA
#define REMOTE_HARDWARE_KEY_VALUE_06    0xA05F  // AA   6   AA
#define REMOTE_HARDWARE_KEY_VALUE_07    0x609F  // AA   7   AA
#define REMOTE_HARDWARE_KEY_VALUE_08    0xE01F  // AA   8   AA
#define REMOTE_HARDWARE_KEY_VALUE_09    0x10EF  // AA   9   AA
#define REMOTE_HARDWARE_KEY_VALUE_00    0x906F  // AA   0   AA
#define REMOTE_HARDWARE_KEY_VALUE_TURN  0x08F7  // AA   轮显    AA
#define REMOTE_HARDWARE_KEY_VALUE_TIME  0xF00F  // AA   时间    AA
#define REMOTE_HARDWARE_KEY_VALUE_10    0x50AF  // AA   1-  AA
#define REMOTE_HARDWARE_KEY_VALUE_20    0xD02F  // AA   2-  AA
#define REMOTE_HARDWARE_KEY_VALUE_30    0x30CF  // AA   3-  AA
#define REMOTE_HARDWARE_KEY_VALUE_40    0xD827  // AA   4-  AA
#define REMOTE_HARDWARE_KEY_VALUE_50    0xF807  // AA   5-  AA
#define REMOTE_HARDWARE_KEY_VALUE_60    0x6897  // AA   6-  AA
#define REMOTE_HARDWARE_KEY_VALUE_70    0x7887  // AA   7-  AA
#define REMOTE_HARDWARE_KEY_VALUE_80    0xA857  // AA   8-  AA
#define REMOTE_HARDWARE_KEY_VALUE_UP    0x9867  // AA   上翻    AA
#define REMOTE_HARDWARE_KEY_VALUE_DOWN  0x58A7  // AA   下翻    AA

void RemoteSetEvent(uchar ucEventNo);
void RemoteTwoKeyAdd(uchar ucKey);
void RemoteOneKeyAdd(uchar ucKey);
void RemoteSetPoint(uchar ucKey);


uchar ucRemoteKeyValue;
uchar ucRemoteTwoKeyTime;
#define CON_REMOTEKEY_TIME_MAX 10

void RemoteInit(void)
{
    ucRemoteKeyValue=0;
    remoteKey=0;
    ucRemoteTwoKeyTime=0;
}
void RemoteTwoKeyAdd(uchar ucKey)
{
    ucRemoteKeyValue=ucKey*10;
    ucRemoteTwoKeyTime=CON_REMOTEKEY_TIME_MAX;
}
void RemoteOneKeyAdd(uchar ucKey)
{
    ucRemoteKeyValue=ucRemoteKeyValue/10;
    ucRemoteKeyValue=ucRemoteKeyValue*10+ucKey;
    SetKeyEvent(DISPLAY_EVENT_REMOTEPOINT);
    ucRemoteTwoKeyTime=0;
}
uchar  RemoteGetPoint(void)
{
    return ucRemoteKeyValue;
}
void RemoteSetPoint(uchar ucKey)
{
    ucRemoteKeyValue=ucKey;
}

void RemoteSetEvent(uchar ucEventNo)
{
    SetKeyEvent(ucEventNo);
    ucRemoteTwoKeyTime=0;
}
#if(CONFIG_METER_AREA_MODE_JIANGXI==CONFIG_METER_AREA_MODE)     
void RemoteHaveAFlg(void)
{
        RELAY_OPERATE_FLAG=1;
}
#endif
uchar ucRemoteKeyLeaderCodeTimes;
uchar RemoteModeSecond;
void RemoteMode(void)
{
//  uchar ucTemp;
    u16  uiRemoteKey;
    ulong ulRemoteKeyUse;

    if(RemoteModeSecond != RSOFT_RTC_SECOND)
    {
        RemoteModeSecond=RSOFT_RTC_SECOND;
        if(ucRemoteTwoKeyTime>0)
        {
            ucRemoteTwoKeyTime--;
        }
        if(0==ucRemoteTwoKeyTime)
        {
            ucRemoteKeyValue=0;
        }
    }
    
    if((0!=remoteKey))
    {
        ulRemoteKeyUse=remoteKey;
        ulRemoteKeyShow=remoteKey;
        remoteKey=0;
#if(CONFIG_METER_AREA_MODE_JIANGXI==CONFIG_METER_AREA_MODE)     
        if(0x90000000&ulRemoteKeyUse)
        {
            ucRemoteKeyLeaderCodeTimes++;
            if(ucRemoteKeyLeaderCodeTimes>10)
            {
                ucRemoteKeyLeaderCodeTimes=0;
                RELAY_OPERATE_FLAG=1;
            }
        }
        else
        {
            ucRemoteKeyLeaderCodeTimes=0;
        }
#else
        if(0x00ff ==(ulRemoteKeyUse>>16))
        {
            uiRemoteKey=ulRemoteKeyUse;
            switch(uiRemoteKey)
            {
                case REMOTE_HARDWARE_KEY_VALUE_00:
                    RemoteOneKeyAdd(0x00);
                    break;
                case REMOTE_HARDWARE_KEY_VALUE_01:
                    RemoteOneKeyAdd(0x01);
                    break;
                case REMOTE_HARDWARE_KEY_VALUE_02:
                    RemoteOneKeyAdd(0x02);
                    break;
                case REMOTE_HARDWARE_KEY_VALUE_03:
                    RemoteOneKeyAdd(0x03);
                    break;
                case REMOTE_HARDWARE_KEY_VALUE_04:
                    RemoteOneKeyAdd(0x04);
                    break;
                case REMOTE_HARDWARE_KEY_VALUE_05:
                    RemoteOneKeyAdd(0x05);
                    break;
                case REMOTE_HARDWARE_KEY_VALUE_06:
                    RemoteOneKeyAdd(0x06);
                    break;
                case REMOTE_HARDWARE_KEY_VALUE_07:
                    RemoteOneKeyAdd(0x07);
                    break;
                case REMOTE_HARDWARE_KEY_VALUE_08:
                    RemoteOneKeyAdd(0x08);
                    break;
                case REMOTE_HARDWARE_KEY_VALUE_09:
                    RemoteOneKeyAdd(0x09);
                    break;
                case REMOTE_HARDWARE_KEY_VALUE_10:
                    RemoteTwoKeyAdd(0x01);
                    break;
                case REMOTE_HARDWARE_KEY_VALUE_20:
                    RemoteTwoKeyAdd(0x02);
                    break;
                case REMOTE_HARDWARE_KEY_VALUE_30:
                    RemoteTwoKeyAdd(0x03);
                    break;
                case REMOTE_HARDWARE_KEY_VALUE_40:
                    RemoteTwoKeyAdd(0x04);
                    break;
                case REMOTE_HARDWARE_KEY_VALUE_50:
                    RemoteTwoKeyAdd(0x05);
                    break;
                case REMOTE_HARDWARE_KEY_VALUE_60:
                    RemoteTwoKeyAdd(0x06);
                    break;
                case REMOTE_HARDWARE_KEY_VALUE_70:
                    RemoteTwoKeyAdd(0x07);
                    break;
                case REMOTE_HARDWARE_KEY_VALUE_80:
                    RemoteTwoKeyAdd(0x08);
                    break;
                case REMOTE_HARDWARE_KEY_VALUE_OPEN:
                    RemoteSetEvent(DISPLAY_EVENT_REMOTEOPEN);
                    break;
                case REMOTE_HARDWARE_KEY_VALUE_TURN:
                    RemoteSetEvent(DISPLAY_EVENT_REMOTETURN);
                    break;
                case REMOTE_HARDWARE_KEY_VALUE_TIME:
                    RemoteSetEvent(DISPLAY_EVENT_REMOTETIME);
                    break;
                case REMOTE_HARDWARE_KEY_VALUE_UP:
                    RemoteSetEvent(DISPLAY_EVENT_REMOTEUP);
                    break;
                case REMOTE_HARDWARE_KEY_VALUE_DOWN:
                    RemoteSetEvent(DISPLAY_EVENT_REMOTEDOWN);
                    break;
                default:
                    ucRemoteTwoKeyTime=0;
                    break;
            }
        }
#endif
    }
}

#endif


























