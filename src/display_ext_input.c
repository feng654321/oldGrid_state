/*******************************************************************************
模块名       : 显示AP模块
文件名       : Display_Ap.c。
相关文件     : 
文件实现功能 :  
作者         : sun yang
版本         : Ver 1.0。
-------------------------------------------------------------------------------
备注         : 
-------------------------------------------------------------------------------
修改记录 : 
日 期        版本     修改人              修改内容
YYYY/MM/DD   X.Y      <作者或修改者名>    <修改内容>
===============================================================================
其他说明:   无。6
*******************************************************************************/
#define DISPLAY_EXT_INPUT_GLOBALS 
#include "common.h"

uchar BatterAlarm(void);
uchar VoltageAlarm(void);
uchar CurrentAlarm(void);

uchar BatterAlarm(void)
{
    uchar returnData;
    
    returnData = 0;
    if(FLG_BATTIMELOW_STATUS)
    {
        if(1==PROGFUNCTION_MODE_DISPLAYALARM_BAT_CLOCK)
        {
            returnData = 1;
        }
        else if(3==PROGFUNCTION_MODE_DISPLAYALARM_BAT_CLOCK)
        {
            if(RSOFT_RTC_SECOND&0x1)
            {
                returnData = 1;
            }
        }
    }
    
    if(FLG_BATWAKEUP_STATUS)
    {
        if(1==PROGFUNCTION_MODE_DISPLAYALARM_BAT_POWEROFF)
        {
            returnData |= 2;
        }
        else if(3==PROGFUNCTION_MODE_DISPLAYALARM_BAT_POWEROFF)
        {
            if(RSOFT_RTC_SECOND&0x1)
            {
                returnData |= 2;
            }
        }
    }
    return(returnData);
}

uchar VoltageAlarm(void)
{
    uchar VoltageFlag,returnData;
    uchar ucTimeFlg;
    ucTimeFlg = (RSOFT_RTC_SECOND&0x1);
    
    VoltageFlag = 0;
    returnData = 0xff;
    if(FLG_ORDER_VOLTAGE_STATUS)    //电压逆向序
    {
        if(PROGFUNCTION_MODE_DISPLAYALARM_ORDER_VOLTAGE == 1)   //常灭
        {
            returnData = 0;
            VoltageFlag = 1;
        }
        else if(PROGFUNCTION_MODE_DISPLAYALARM_ORDER_VOLTAGE == 2)  //闪烁
        {
            if(ucTimeFlg == 1)
                returnData = 0x05;
            else
                returnData = 0x02;
            VoltageFlag = 1;
        }
    }
    
    if(!VoltageFlag)
    {
        if(FLG_A_DOWN_VOLTAGE_STATUS||FLG_B_DOWN_VOLTAGE_STATUS||FLG_C_DOWN_VOLTAGE_STATUS)
        {
            if(PROGFUNCTION_MODE_DISPLAYALARM_DOWN_VOLTAGE == 1)
            {
                if(FLG_A_DOWN_VOLTAGE_STATUS)
                    returnData &=~0x01;
                if(FLG_B_DOWN_VOLTAGE_STATUS)
                    returnData &=~0x02;
                if(FLG_C_DOWN_VOLTAGE_STATUS)
                    returnData &=~0x04;
                VoltageFlag = 1;
            }
            else if(PROGFUNCTION_MODE_DISPLAYALARM_DOWN_VOLTAGE == 2)
            {
                if(FLG_A_DOWN_VOLTAGE_STATUS)
                {
                    if(1==ucTimeFlg)
                    {
                        returnData &= ~0x01;
                    }
                    else
                    {
                        returnData |=  0x01;
                    }
                }
                if(FLG_B_DOWN_VOLTAGE_STATUS)
                {
                    if(1==ucTimeFlg)
                    {
                        returnData &= ~0x02;
                    }
                    else
                    {
                        returnData |=  0x02;
                    }
                }
                if(FLG_C_DOWN_VOLTAGE_STATUS)
                {
                    if(1==ucTimeFlg)
                    {
                        returnData &= ~0x04;
                    }
                    else
                    {
                        returnData |=  0x04;
                    }
                }
                VoltageFlag = 1;
            }
        }
        
        if(FLG_A_OVER_VOLTAGE_STATUS||FLG_B_OVER_VOLTAGE_STATUS||FLG_C_OVER_VOLTAGE_STATUS)
        {
            if(PROGFUNCTION_MODE_DISPLAYALARM_OVER_VOLTAGE == 1)
            {
                if(FLG_A_OVER_VOLTAGE_STATUS)
                    returnData &=~0x01;
                if(FLG_B_OVER_VOLTAGE_STATUS)
                    returnData &=~0x02;
                if(FLG_C_OVER_VOLTAGE_STATUS)
                    returnData &=~0x04;
                VoltageFlag = 1;
            }
            else if(PROGFUNCTION_MODE_DISPLAYALARM_OVER_VOLTAGE == 2)
            {
                if(FLG_A_OVER_VOLTAGE_STATUS)
                {
                    if(1==ucTimeFlg)
                    {
                        returnData &= ~0x01;
                    }
                    else
                    {
                        returnData |=  0x01;
                    }
                }
                if(FLG_B_OVER_VOLTAGE_STATUS)
                {
                    if(1==ucTimeFlg)
                    {
                        returnData &= ~0x02;
                    }
                    else
                    {
                        returnData |=  0x02;
                    }
                }
                if(FLG_C_OVER_VOLTAGE_STATUS)
                {
                    if(1==ucTimeFlg)
                    {
                        returnData &= ~0x04;
                    }
                    else
                    {
                        returnData |=  0x04;
                    }
                }
                VoltageFlag = 1;
            }
        }       
        
        if(FLG_A_CUT_VOLTAGE_STATUS||FLG_B_CUT_VOLTAGE_STATUS||FLG_C_CUT_VOLTAGE_STATUS)
        {
            if(PROGFUNCTION_MODE_DISPLAYALARM_CUT_VOLTAGE == 1)
            {
                if(FLG_A_CUT_VOLTAGE_STATUS)
                    returnData &=~0x01;
                if(FLG_B_CUT_VOLTAGE_STATUS)
                    returnData &=~0x02;
                if(FLG_C_CUT_VOLTAGE_STATUS)
                    returnData &=~0x04;
                VoltageFlag = 1;
            }
            else if(PROGFUNCTION_MODE_DISPLAYALARM_CUT_VOLTAGE == 2)
            {
                if(FLG_A_CUT_VOLTAGE_STATUS)
                {
                    if(1==ucTimeFlg)
                    {
                        returnData &= ~0x01;
                    }
                    else
                    {
                        returnData |=  0x01;
                    }
                }
                if(FLG_B_CUT_VOLTAGE_STATUS)
                {
                    if(1==ucTimeFlg)
                    {
                        returnData &= ~0x02;
                    }
                    else
                    {
                        returnData |=  0x02;
                    }
                }
                if(FLG_C_CUT_VOLTAGE_STATUS)
                {
                    if(1==ucTimeFlg)
                    {
                        returnData &= ~0x04;
                    }
                    else
                    {
                        returnData |=  0x04;
                    }
                }
                VoltageFlag = 1;
            }
        }
        if(FLG_A_LOSS_VOLTAGE_STATUS||FLG_B_LOSS_VOLTAGE_STATUS||FLG_C_LOSS_VOLTAGE_STATUS)
        {
            if(PROGFUNCTION_MODE_DISPLAYALARM_LOSS_VOLTAGE == 1)
            {
                if(FLG_A_LOSS_VOLTAGE_STATUS)
                    returnData &=~0x01;
                if(FLG_B_LOSS_VOLTAGE_STATUS)
                    returnData &=~0x02;
                if(FLG_C_LOSS_VOLTAGE_STATUS)
                    returnData &=~0x04;
                VoltageFlag = 1;
            }
            else if(PROGFUNCTION_MODE_DISPLAYALARM_LOSS_VOLTAGE == 2)
            {
                if(FLG_A_LOSS_VOLTAGE_STATUS)
                {
                    if(1==ucTimeFlg)
                    {
                        returnData &= ~0x01;
                    }
                    else
                    {
                        returnData |=  0x01;
                    }
                }
                if(FLG_B_LOSS_VOLTAGE_STATUS)
                {
                    if(1==ucTimeFlg)
                    {
                        returnData &= ~0x02;
                    }
                    else
                    {
                        returnData |=  0x02;
                    }
                }
                if(FLG_C_LOSS_VOLTAGE_STATUS)
                {
                    if(1==ucTimeFlg)
                    {
                        returnData &= ~0x04;
                    }
                    else
                    {
                        returnData |=  0x04;
                    }
                }
                VoltageFlag = 1;
            }
        }
    }
    
    return(returnData);
}

uchar CurrentAlarm(void)
{
    uchar CurrenteFlag,returnData;
    uchar ucTimeFlg;
    CurrenteFlag = 0;
    returnData = 0xff;
    ucTimeFlg=(RSOFT_RTC_SECOND&0x1);
    if(FLG_ORDER_CURRENT_STATUS)
    {
        if(PROGFUNCTION_MODE_DISPLAYALARM_ORDER_CURRENT == 1)
        {
            returnData = 0;
            CurrenteFlag = 1;
        }
        else if(PROGFUNCTION_MODE_DISPLAYALARM_ORDER_CURRENT == 2)
        {
            if(ucTimeFlg == 1)
                returnData = 0x05;
            else
                returnData = 0x02;
            CurrenteFlag = 1;
        }
    }
    
    if(!CurrenteFlag)
    {
        if(FLG_A_CURRENT_NOHAVE_STATUS||FLG_B_CURRENT_NOHAVE_STATUS||FLG_C_CURRENT_NOHAVE_STATUS)
        {
            if(FLG_A_CURRENT_NOHAVE_STATUS)
                returnData &=~0x01;
            if(FLG_B_CURRENT_NOHAVE_STATUS)
                returnData &=~0x02;
            if(FLG_C_CURRENT_NOHAVE_STATUS)
                returnData &=~0x04;
        }
        if(FLG_A_OVER_CURRENT_STATUS||FLG_B_OVER_CURRENT_STATUS||FLG_C_OVER_CURRENT_STATUS)
        {
            if(PROGFUNCTION_MODE_DISPLAYALARM_OVER_CURRENT == 1)
            {
                if(FLG_A_OVER_CURRENT_STATUS)
                    returnData &=~0x01;
                if(FLG_B_OVER_CURRENT_STATUS)
                    returnData &=~0x02;
                if(FLG_C_OVER_CURRENT_STATUS)
                    returnData &=~0x04;
                CurrenteFlag = 1;
            }
            else if(PROGFUNCTION_MODE_DISPLAYALARM_OVER_CURRENT == 2)
            {
                if(FLG_A_OVER_CURRENT_STATUS)
                {
                    if(1==ucTimeFlg)
                    {
                        returnData &= ~0x01;
                    }
                    else
                    {
                        returnData |=  0x01;
                    }
                }
                if(FLG_B_OVER_CURRENT_STATUS)
                {
                    if(1==ucTimeFlg)
                    {
                        returnData &= ~0x02;
                    }
                    else
                    {
                        returnData |=  0x02;
                    }
                }
                if(FLG_C_OVER_CURRENT_STATUS)
                {
                    if(1==ucTimeFlg)
                    {
                        returnData &= ~0x04;
                    }
                    else
                    {
                        returnData |=  0x04;
                    }
                }
                    
                CurrenteFlag = 1;
            }
        }

        if(FLG_A_CUT_CURRENT_STATUS||FLG_B_CUT_CURRENT_STATUS||FLG_C_CUT_CURRENT_STATUS)
        {
            if(PROGFUNCTION_MODE_DISPLAYALARM_CUT_CURRENT == 1)
            {
                if(FLG_A_CUT_CURRENT_STATUS)
                    returnData &=~0x01;
                if(FLG_B_CUT_CURRENT_STATUS)
                    returnData &=~0x02;
                if(FLG_C_CUT_CURRENT_STATUS)
                    returnData &=~0x04;
                CurrenteFlag = 1;
            }
            else if(PROGFUNCTION_MODE_DISPLAYALARM_CUT_CURRENT == 2)
            {
                if(FLG_A_CUT_CURRENT_STATUS)
                {
                    if(1==ucTimeFlg)
                    {
                        returnData &= ~0x01;
                    }
                    else
                    {
                        returnData |=  0x01;
                    }
                }
                if(FLG_B_CUT_CURRENT_STATUS)
                {
                    if(1==ucTimeFlg)
                    {
                        returnData &= ~0x02;
                    }
                    else
                    {
                        returnData |=  0x02;
                    }
                }
                if(FLG_C_CUT_CURRENT_STATUS)
                {
                    if(1==ucTimeFlg)
                    {
                        returnData &= ~0x04;
                    }
                    else
                    {
                        returnData |=  0x04;
                    }
                }
                CurrenteFlag = 1;
            }
        }

        if(FLG_A_LOSS_CURRENT_STATUS||FLG_B_LOSS_CURRENT_STATUS||FLG_C_LOSS_CURRENT_STATUS)
        {
            if(PROGFUNCTION_MODE_DISPLAYALARM_LOSS_CURRENT == 1)
            {
                if(FLG_A_LOSS_CURRENT_STATUS)
                    returnData &=~0x01;
                if(FLG_B_LOSS_CURRENT_STATUS)
                    returnData &=~0x02;
                if(FLG_C_LOSS_CURRENT_STATUS)
                    returnData &=~0x04;
                CurrenteFlag = 1;
            }
            else if(PROGFUNCTION_MODE_DISPLAYALARM_LOSS_CURRENT == 2)
            {
                if(FLG_A_LOSS_CURRENT_STATUS)
                {
                    if(1==ucTimeFlg)
                    {
                        returnData &= ~0x01;
                    }
                    else
                    {
                        returnData |=  0x01;
                    }
                }
                if(FLG_B_LOSS_CURRENT_STATUS)
                {
                    if(1==ucTimeFlg)
                    {
                        returnData &= ~0x02;
                    }
                    else
                    {
                        returnData |=  0x02;
                    }
                }
                if(FLG_C_LOSS_CURRENT_STATUS)
                {
                    if(1==ucTimeFlg)
                    {
                        returnData &= ~0x04;
                    }
                    else
                    {
                        returnData |=  0x04;
                    }
                }
                CurrenteFlag = 1;
            }
        }
    }
    if(METERTYPE_3_3 == PROGFUNCTION_TYPE_METER_TYPE  )
    {
        returnData &= ~0x04;
    }
    return(returnData);
}

#if 0
/*************************************************************
Function: 查ComDispList表
Input:
Output: type:0:无 1:上反 2：下反 3：指定
Application area:  
Explain: 
Modification register:
**************************************************************/
uchar GetDisplayExtInput(uchar* type,ulong* id,uchar* obisH);
uchar GetDisplayExtInput(uchar* type,ulong* id,uchar* obisH)
{
    uchar returnData,inputData;
    
    returnData = 1;
    
    *type = 0;
    inputData = PopKeyEvent();

    if(inputData == DISPLAY_EVENT_NO)
    {
        returnData = 0;
        *type = 0;
    }
    else if(inputData == DISPLAY_EVENT_KEYUP)
    {
        *type = 1;
    }
    else if(inputData == DISPLAY_EVENT_KEYDOWN)
    {
        *type = 2;
    }
    else if(inputData == DISPLAY_EVENT_REMOTEOPEN)
    {
        *type = 8;
    }
    else if(inputData == DISPLAY_EVENT_KEYPRO)
    {
        *type = 0xff;
    }
    else if (inputData == DISPLAY_EVENT_COMMDISPLAY)
    {
        *type = 21;
        *id=0x00000000;
        *obisH=0x00;
    }
#ifdef CONFIG_METER_REMOTE_INPUT_ENABLE
    else if(inputData == DISPLAY_EVENT_REMOTEUP)
    {
        *type = 4;
    }
    else if(inputData == DISPLAY_EVENT_REMOTEDOWN)
    {
        *type = 5;
    }
    else if(inputData == DISPLAY_EVENT_REMOTETURN)
    {
        *type = 6;
    }
    else if(inputData == DISPLAY_EVENT_REMOTETIME)
    {
        *type = 7;
    }
    else if(inputData == DISPLAY_EVENT_REMOTEPOINT)
    {
        *type = 3;
        //*obisH = GetKeyStatus();
        inputData = RemoteGetPoint();
        *obisH = ((inputData/10)%10)<<4;
        *obisH += inputData%10; 
        if((*obisH&0xf0) == 0x00)
        {
            //*obisH = *obisH|0xa0;
        }
        if((*obisH&0xf0) == 0x60)
        {
            //*obisH = *obisH&0x0f;
            //*obisH = *obisH|0xd0;
        }
        if((*obisH&0xf0) == 0x70)
        {
            //*obisH = *obisH&0x0f;
            //*obisH = *obisH|0xb0;
        }
        if((*obisH&0xf0) == 0x80)
        { 
            //*obisH = *obisH&0x0f;
            //*obisH = *obisH|0xc0;
        }
    }
#endif
    
#if(CONFIG_METER_PREPAY_MODE == CONFIG_METER_PREPAY_MODE_LOCATION)
    if(ucTempDisplayReadCardStatus !=readCardStatus)
    {
        ucTempDisplayReadCardStatus=readCardStatus;
        switch(ucTempDisplayReadCardStatus)
        {
            case 1: // dukazhong
                uiAlarmDisplayCardReadTimes=1000;
                break;
            case 2:  // chengong
                uiAlarmDisplayCardReadTimes=300;
                AlarmSpeekAlarmCardReadTime(1,90);
                break;
            case 3: // shibai
                uiAlarmDisplayCardReadTimes=300;
                // AlarmSpeekAlarmCardReadTime(1,00);
                break;
            default:
                break;
        }
        *type = 0xff;
        returnData=1;
    }   
#endif
    return(returnData);
}
#endif

