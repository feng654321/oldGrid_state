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
#define DISPLAY_AP_GLOBALS
#include "common.h"

uchar GetIdSerialNumber(ST_DISPLAY_CONTROL* controlData);
uchar GetDisplayID(ST_DISPLAY_CONTROL* controlData);
void TurnOnePage(ST_DISPLAY_CONTROL* controlData);
uchar DisplayTurnPage(ST_DISPLAY_CONTROL* controlData);
void GetDisplayInformation(ST_DISPLAY_CONTROL* controlData);
void Display(void);
uchar DisplayPrivateSegment(STR_DISPLAYMEMORY* displayMemoryData);
void TurnPageCallBack(void);
void MamageExtInput(void);
u16 SearchInDispListByObisH(uchar ObisH);
u16 SearchInComDispList(ulong id);
u16 SearchInComDispListByObisH(uchar ObisH);
void DisplayPrivateSymbol(ST_PRIVATE_SYMBOL* symbol,STR_DISPLAYMEMORY* displayMemoryData);
void DisplayPublicSegment(STR_DISPLAYMEMORY* displayMemoryData);

void DisplayPrivateSymbolChange(STR_DISPLAYMEMORY* displayMemoryData,uchar dataType);
void SpringDifferentDisplayMode(ST_DISPLAY_MODE_CHANGE* typeData);
uchar DataFormatTransform(uchar* buf,uchar lens,uchar dataType);
uchar manageCurrentData(uchar* buf,uchar dataType,uchar* sign);
uchar managePowercosData(uchar* buf,uchar dataType,uchar* sign);
uchar managePhasieData(uchar* buf,uchar dataType,uchar* sign);
uchar manageVoltageData(uchar* buf,uchar dataType,uchar* sign);
uchar manageXLData(uchar* buf,uchar dataType,uchar* sign);
uchar manageDLData(uchar* buf,uchar dataType,uchar* sign);
void DisplayFullScreen(void);
void DisplayEmptyScreen(void);
void RefalshEnCallBack(void);
void DisplayTimeManage(void);
void DisplayBufChang(uchar* buf,uchar dataType);
uchar GetIdSerialNumber1(ST_DISPLAY_CONTROL* controlData);
void DataFormatTransformBaudrate(uchar * buf, uchar *lens, uchar dataType);
void JustActiveDisplayWord(uchar* buf,uchar startAddr,uchar endAddr);



/*************************************************************
Function: 显示应用初始化
Input:
Output: 
Application area:  
Explain: 
Modification register:
**************************************************************/
void InitDisplayControl(uchar type)
{
    CheckDisplayControl();
    displayControl.displayModeTurnFlag = 0;
    displayControl.lcdFigureNum = 0;
    displayControl.currentItem[TAKE_TURN_DISPLAY_MODE][displayControl.lcdFigureNum] = 0;
    displayControl.displayMode = 0;
    displayControl.displayModeChangeFlag = 0;
    GetDisplayInformation(&displayControl);
    displayControl.displayTurnPageFlag = 0;
    //displayControl.displayRefalshFlag = 1;
    displayControl.displayRefalshFlag = 0;
    //displayControl.displayRefalshEn = 0;
    //displayControl.dispalyObis = 0;
    //displayFlag = 0;
    
    LCDSwitchFlag = 1;
    
    especiallyDisplayControl.especiallyDispalyMode = 0;
    especiallyDisplayControl.especiallyDispalyFlag = 0;
    especiallyDisplayControl.currentItem = 0xff;
    especiallyDisplayControl.maxItem = 0;
    
    AlarmDisplayLcdDataInit();
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
    cardErrorType=0;
    cardErrorTypeBak = cardErrorType;
#endif  
    if(type)
    {
        displayControl.displayRefalshEn = 0;
        displayFlag = 0;
        DisplayFullScreen();
        StartTime1s(T1SID_REFALSH_DISPLAY_TIMER_NUM, START_FULL_SCREEN_DISPLAY_TIME, TIMER_MODE_CONTINUE, RefalshEnCallBack);
    }
    else
    {
        displayControl.displayRefalshEn = 1;
        displayFlag = 1;
        StartTime1s(T1SID_TURN_PAGE_TIMER_NUM, displayControl.turnTime[displayControl.displayMode], TIMER_MODE_CONTINUE, TurnPageCallBack);
//      displayControl.displayTurnPageFlag = 1;
//      RefalshEnCallBack();
// DisplayEmptyScreen();
    }
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
    ucTempDisplayReadCardStatus=readCardStatus;
    uiAlarmDisplayCardReadTimes=0;
#endif

}


#if (CONFIG_METER_AREA_MODE_SOUTHGRID==CONFIG_METER_AREA_MODE)
// 南网特殊显示
// 如果发生失压或者失流，液晶闪烁显示'失压'或者'失流'字样
// 发生全失压，只在唤醒时闪烁显示'失压'字样
void EspDisplayOfSouthGrid(STR_DISPLAYMEMORY *displayMemoryData);
void EspDisplayOfSouthGrid(STR_DISPLAYMEMORY *displayMemoryData)
{
    displayMemoryData->symbol.Shi = 0;
    displayMemoryData->symbol.Ya= 0;
    displayMemoryData->symbol.Liu= 0;

    if((RSOFT_RTC_SECOND % 2) == 0)
    {
        if((FLG_A_LOSS_VOLTAGE_STATUS == GAL_YES)||(FLG_B_LOSS_VOLTAGE_STATUS == GAL_YES)||(FLG_C_LOSS_VOLTAGE_STATUS == GAL_YES))
        {
            displayMemoryData->symbol.Shi = 1;
            displayMemoryData->symbol.Ya= 1;
        }
        if((FLG_A_LOSS_CURRENT_STATUS == GAL_YES)||(FLG_B_LOSS_CURRENT_STATUS == GAL_YES)||(FLG_C_LOSS_CURRENT_STATUS == GAL_YES))
        {
            displayMemoryData->symbol.Shi = 1;
            displayMemoryData->symbol.Liu= 1;
        }
        if((fGetAllLostVoltageStatus)&&(IfPowerStateOff()))
        {
            displayMemoryData->symbol.Shi = 1;
            displayMemoryData->symbol.Ya= 1;
        }
    }
}
#endif


u16 GetShowAutoDisplay1Cycle(void)
{
    u16 uiData;
    uiData=displayControl.itemNum[TAKE_TURN_DISPLAY_MODE] ;
    uiData=uiData*displayControl.turnTime[TAKE_TURN_DISPLAY_MODE] ;
    if(uiData<10)
        uiData=10;
    if(uiData>3000)
        uiData=150;
    return uiData;
}

#if(CONFIG_METER_AREA_MODE_SHANDONG==CONFIG_METER_AREA_MODE)
    #define CON_DISPLA_KEY_AUTO_NUM_MAX 255
#else
    #define CON_DISPLA_KEY_AUTO_NUM_MAX 100
#endif
void CheckDisplayControl(void)
{
    uchar ucTemp,ucTempTime,ucCountAuto,ucCountKey;
    ulong ulDataAddr,ulData;
    ucCountAuto=0;
#if(CONFIG_METER_AREA_MODE_SICHUAN==CONFIG_METER_AREA_MODE)
    uchar ucCountKeyB;
#endif
    for(ucTemp=0;ucTemp<5;ucTemp++)
    {
        ulDataAddr=((ulong)ucTemp)*CON_DISPLA_KEY_AUTO_NUM_MAX+TAKE_TURN_DISPLAY_LIST_START_ADDR;
        ReadDataDirect(ulDataAddr,CON_DISPLA_KEY_AUTO_NUM_MAX, &Wr_data[0]);
        for(ucTempTime=0;ucTempTime<(CON_DISPLA_KEY_AUTO_NUM_MAX/5);ucTempTime++)
        {
            memcpy((uchar *) &ulData, &Wr_data[ucTempTime*5], 4);
            if(0xffff!=SearchInDispList(ulData,Wr_data[ucTempTime*5+4]))
            {
                ucCountAuto++;
            }
            else
            {
                ucTemp=200;
                ucTempTime=200;
            }
        }
    }
    ucCountKey=0;
    for(ucTemp=0;ucTemp<5;ucTemp++)
    {
        ulDataAddr=((ulong)ucTemp)*CON_DISPLA_KEY_AUTO_NUM_MAX+KEY_TURN_DISPLAY_LIST_START_ADDR;
        ReadDataDirect(ulDataAddr,CON_DISPLA_KEY_AUTO_NUM_MAX, &Wr_data[0]);
        for(ucTempTime=0;ucTempTime<(CON_DISPLA_KEY_AUTO_NUM_MAX/5);ucTempTime++)
        {
            memcpy((uchar *) &ulData, &Wr_data[ucTempTime*5], 4);
            if(0xffff!=SearchInDispList(ulData,Wr_data[ucTempTime*5+4]))
            {
                ucCountKey++;
            }
            else
            {
                ucTemp=200;
                ucTempTime=200;
            }
        }
    }

    //  ljc  20100620  start  
#if(CONFIG_METER_AREA_MODE_SICHUAN==CONFIG_METER_AREA_MODE)
     ucCountKeyB=0;
     for(ucTemp=0;ucTemp<5;ucTemp++)
     {
         ulDataAddr=((ulong)ucTemp)*100+KEY_TURN_DISPLAY_B_LIST_START_ADDR;
         ReadDataDirect(ulDataAddr,100, &Wr_data[0]);
         for(ucTempTime=0;ucTempTime<20;ucTempTime++)
         {
            memcpy((uchar *) &ulData, &Wr_data[ucTempTime*5], 4);
            if(0xffff!=SearchInDispList(ulData,Wr_data[ucTempTime*5+4]))
            {
                ucCountKeyB++;
            }
            else
            {
                ucTemp=200;
                ucTempTime=200;
            }
        }
     }
     displayBTableItemNum=ucCountKeyB;
#endif
    //  ljc  20100620  end
    
    ReadDataDirect(DISPLAY_PARA_START_ADDR,5,&Wr_data[0]);
#if(CONFIG_METER_AREA_MODE_SHANDONG==CONFIG_METER_AREA_MODE)
    
    displayControl.itemNum[TAKE_TURN_DISPLAY_MODE] = (Wr_data[0]);
    if(displayControl.itemNum[TAKE_TURN_DISPLAY_MODE] >ucCountAuto)
    {
        displayControl.itemNum[TAKE_TURN_DISPLAY_MODE] =ucCountAuto;
    }
    displayControl.turnTime[TAKE_TURN_DISPLAY_MODE] = BCD_Byte(Wr_data[1]);
    if(displayControl.turnTime[TAKE_TURN_DISPLAY_MODE] <5)
    {
        displayControl.turnTime[TAKE_TURN_DISPLAY_MODE] =5;
    }
    if(displayControl.turnTime[TAKE_TURN_DISPLAY_MODE] >100)
    {
        displayControl.turnTime[TAKE_TURN_DISPLAY_MODE] =10;
    }

    displayControl.energyDec = BCD_Byte(Wr_data[2]);
    if(displayControl.energyDec > 4)
    {
        displayControl.energyDec = 2;
    }
    displayControl.powerDec = BCD_Byte(Wr_data[3]);
    if(displayControl.powerDec > 6)
    {
        displayControl.powerDec = 4;
    }
    displayControl.itemNum[KEY_TURN_DISPLAY_MODE] = (Wr_data[4]);
    if(displayControl.itemNum[KEY_TURN_DISPLAY_MODE] >ucCountKey)
    {
        displayControl.itemNum[KEY_TURN_DISPLAY_MODE] =ucCountKey;
    }
#else
    displayControl.itemNum[TAKE_TURN_DISPLAY_MODE] = BCD_Byte(Wr_data[0]);
    if(displayControl.itemNum[TAKE_TURN_DISPLAY_MODE] >ucCountAuto)
    {
        displayControl.itemNum[TAKE_TURN_DISPLAY_MODE] =ucCountAuto;
    }
    if(displayControl.itemNum[TAKE_TURN_DISPLAY_MODE] > 99)
    {
        displayControl.itemNum[TAKE_TURN_DISPLAY_MODE] = 99;
    }
    displayControl.turnTime[TAKE_TURN_DISPLAY_MODE] = BCD_Byte(Wr_data[1]);
    if(displayControl.turnTime[TAKE_TURN_DISPLAY_MODE] <5)
    {
        displayControl.turnTime[TAKE_TURN_DISPLAY_MODE] =5;
    }
    if(displayControl.turnTime[TAKE_TURN_DISPLAY_MODE] >100)
    {
        displayControl.turnTime[TAKE_TURN_DISPLAY_MODE] =10;
    }

    displayControl.energyDec = BCD_Byte(Wr_data[2]);
    if(displayControl.energyDec > 4)
    {
        displayControl.energyDec = 2;
    }
    displayControl.powerDec = BCD_Byte(Wr_data[3]);
    if(displayControl.powerDec > 6)
    {
        displayControl.powerDec = 4;
    }
    displayControl.itemNum[KEY_TURN_DISPLAY_MODE] = BCD_Byte(Wr_data[4]);
    if(displayControl.itemNum[KEY_TURN_DISPLAY_MODE] >ucCountKey)
    {
        displayControl.itemNum[KEY_TURN_DISPLAY_MODE] =ucCountKey;
    }
    if(displayControl.itemNum[KEY_TURN_DISPLAY_MODE] > 99)
    {
        displayControl.itemNum[KEY_TURN_DISPLAY_MODE] = 99;
    }
#endif

    //  ljc  20100706  start
    #if(CONFIG_METER_AREA_MODE_SICHUAN==CONFIG_METER_AREA_MODE)
    if(DISPLAY_CHANGE_AtoB_STATUS==GAL_YES)
    {
        displayATableItemNumTemp=displayControl.itemNum[KEY_TURN_DISPLAY_MODE];
        displayControl.itemNum[KEY_TURN_DISPLAY_MODE]=displayBTableItemNum;
    }
    #endif
    //  ljc  20100706  end
    
    
#if 1   
    ucCountKey=ValueHexFromRam2Bcd(RAM_COEF_DISPLAY_MODE_CHANGE_TIME);
    if(ucCountKey<10)
    {
        ucCountKey=60;
    }
    if(ucCountKey>250)
    {
        ucCountKey=250;
    }
    displayControl.turnTime[KEY_TURN_DISPLAY_MODE] =ucCountKey;
    displayControl.turnTime[APPOINT_DISPLAY_MODE] =ucCountKey;
    
#else   
    
    displayControl.turnTime[KEY_TURN_DISPLAY_MODE] =2* displayControl.turnTime[TAKE_TURN_DISPLAY_MODE];
    displayControl.turnTime[APPOINT_DISPLAY_MODE] = 2*displayControl.turnTime[TAKE_TURN_DISPLAY_MODE];
    
#endif
    displayControl.turnTime[CARD_DISPLAY_MODE]  = 5;




    uiWakeUpAllTimes=1*GetShowAutoDisplay1Cycle();
}
void RefalshEnCallBack(void)
{
    displayControl.displayRefalshEn = 1;
    displayControl.displayRefalshFlag = 1;
    displayControl.displayTurnPageFlag = 0;
    CloseTime1s(T1SID_REFALSH_DISPLAY_TIMER_NUM);
    StartTime1s(T1SID_TURN_PAGE_TIMER_NUM, displayControl.turnTime[displayControl.displayMode], TIMER_MODE_CONTINUE, TurnPageCallBack);
}

void GetDisplayInformation(ST_DISPLAY_CONTROL* controlData)
{
    displayControl.lcdFigureNum = 0;
    GetDisplayID(controlData);
    GetIdSerialNumber(controlData);
    for(displayControl.lcdFigureNum=1;displayControl.lcdFigureNum<LCD_FIGURE_NUM;displayControl.lcdFigureNum++)
    {
        displayControl.currentItem[displayControl.displayMode][displayControl.lcdFigureNum] = displayControl.currentItem[displayControl.displayMode][displayControl.lcdFigureNum-1];
        displayControl.id[displayControl.lcdFigureNum] = displayControl.id[displayControl.lcdFigureNum-1];
        displayControl.idSerialNumber[displayControl.lcdFigureNum] = displayControl.idSerialNumber[displayControl.lcdFigureNum-1];
        TurnOnePage(controlData);
    }
    displayControl.lcdFigureNum = 0;
}

void SpringDifferentDisplayMode(ST_DISPLAY_MODE_CHANGE* typeData)
{
    //uchar flag;
    
    /*if(typeData->displayMode == TAKE_TURN_DISPLAY_MODE)
    {
        displayControl.currentItem[displayControl.displayMode][0] = 0;
        displayControl.displayMode = typeData->displayMode;
        displayControl.currentItem[displayControl.displayMode][0] = 0;
        GetDisplayInformation(&displayControl);
    }
    else if(typeData->displayMode == KEY_TURN_DISPLAY_MODE)
    {
        flag = 0;
        if(displayControl.displayMode == KEY_TURN_DISPLAY_MODE)
        {
            if(typeData->turnType == UP_TURN)
            {
                displayControl.currentItem[displayControl.displayMode][0]++;
                if(displayControl.currentItem[displayControl.displayMode][0] >= displayControl.itemNum[displayControl.displayMode])
                {
                    if(0xff != SearchAlarmDisplayInformation(&(displayControl.id[0]), &(displayControl.idSerialNumber[0])))
                    {
                        flag = 1;
                    }
                    else
                    {
                        alarmDisplaycurrentItem = 0;
                        displayControl.currentItem[displayControl.displayMode][0] = 0;
                    }
                }
            }
            else if(typeData->turnType == DOWN_TURN)
            {
                if(displayControl.currentItem[displayControl.displayMode][0] > 0)
                {
                    displayControl.currentItem[displayControl.displayMode][0]--;
                }
                else
                {
                    if(0xff != SearchAlarmDisplayInformation(&(displayControl.id[0]), &(displayControl.idSerialNumber[0])))
                    {
                        flag = 1;
                    }
                    else
                    {
                        alarmDisplaycurrentItem = 0;
                        displayControl.currentItem[displayControl.displayMode][0] = displayControl.itemNum[displayControl.displayMode]-1;
                    }
                    //displayControl.currentItem[displayControl.displayMode][0] = displayControl.itemNum[displayControl.displayMode]-1;
                }
            }
        }
        else
        {
            
            if(0xff != SearchAlarmDisplayInformation(&(displayControl.id[0]), &(displayControl.idSerialNumber[0])))
            {
                flag = 1;
            }
            else
            {
                alarmDisplaycurrentItem = 0;
                displayControl.currentItem[displayControl.displayMode][0] = 0;
                displayControl.displayMode = typeData->displayMode;
                displayControl.currentItem[displayControl.displayMode][0] = 0;
            }
        }
        if(flag==0)
        {
            GetDisplayInformation(&displayControl);
        }
    }
    else if(typeData->displayMode == APPOINT_DISPLAY_MODE)
    {
        displayControl.displayMode = typeData->displayMode;
        displayControl.lcdFigureNum = 0;
        displayControl.id[displayControl.lcdFigureNum] = typeData->id;
        displayControl.idSerialNumber[displayControl.lcdFigureNum] = typeData->idSerialNumber;
    }
    else if(typeData->displayMode == CARD_DISPLAY_MODE)
    {
        displayControl.displayMode = typeData->displayMode;
        displayControl.lcdFigureNum = 0;
        displayControl.id[displayControl.lcdFigureNum] = 0xffffffd1;
        displayControl.idSerialNumber[displayControl.lcdFigureNum] = 0x00;
    }
    else if(typeData->displayMode == COMM_DISPLAY_MODE)*/
    {
        ulong ultemp;
        displayControl.displayMode = KEY_TURN_DISPLAY_MODE;
        displayControl.lcdFigureNum = 0;
        displayControl.id[displayControl.lcdFigureNum] = typeData->id;
        displayControl.idSerialNumber[displayControl.lcdFigureNum] = typeData->idSerialNumber;

        ultemp = typeData->id;
        memcpy(&displayControl.screenNoData[displayControl.lcdFigureNum][0], (uchar *)&(ultemp), 4);
        
        displayControl.currentItem[displayControl.displayMode][0] = 0;
        displayControl.currentItem[displayControl.displayMode][0] = 0;
        
    }

    
    displayControl.displayModeChangeFlag = 1;
    //displayControl.displayRefalshFlag = 1;
    displayFlag = 1;
    StartTime1s(T1SID_TURN_PAGE_TIMER_NUM, displayControl.turnTime[displayControl.displayMode], TIMER_MODE_CONTINUE, TurnPageCallBack);
    displayControl.displayTurnPageFlag = 0;
}


void DisplayTimeManage(void)
{
    //if(displayControl.displayRefalshEn)//是否要刷屏标志
    if(LCDSwitchFlag)
    {
        if(displayFlag)
        {
            displayControl.displayRefalshFlag = 1;
            displayFlag = 0;
        }
    }
}


/*************************************************************
Function: 显示应用进程
Input:
Output: 
Application area:  
Explain: 
Modification register:
**************************************************************/
void Display(void)
{
    uchar flag;
    STR_DISPLAYMEMORY displayMemoryData;
    
    //if(displayControl.displayRefalshEn)
    {
        MamageExtInput();
        //DisplayTimeManage();
    }
        CommExpDataBuff = (STR_RETURN_EXPLAINBUFFER*)&(CommExpReceiveDataBuffer.buff[0]);
    
    //if(displayControl.displayRefalshFlag)
    {
        //displayControl.displayRefalshFlag = 0;
        //flag = DisplayTurnPage(&displayControl);            //turn page
        flag = 1;
        if(flag)
        {
            memset(&displayMemoryData,0,sizeof(STR_DISPLAYMEMORY));
            //if(!especiallyDisplayControl.especiallyDispalyFlag)
            {
                if(!DisplayPrivateSegment(&displayMemoryData))  //display private segment; include data and symbol
                {
                    DisplayPublicSegment(&displayMemoryData);//display publuc segment symbol

                    
                    if(displayControl.id[0]==0xFFFFFFD2) 
                    {
                        if(displayControl.idSerialNumber[0] == 0)
                            DisplayFullScreen();
                        else
                            DisplayEmptyScreen();
                    }
                    else
                    {
                        ReflashDisplayMemory(&displayMemoryData);  
                    }
                }
            }
            
            /*else
            {
                //特殊显示  It is no use now
                if(especiallyDisplayControl.especiallyDispalyMode == 1)
                {
                    ;
                }
                else if(especiallyDisplayControl.especiallyDispalyMode == 2)
                {
                    ;
                }
                else if(especiallyDisplayControl.especiallyDispalyMode == 3)
                {
                    //CoefCheckFromRamAddr(DISPLAY_PARA_START_ADDR,5,1);
                    ReadDataDirect(DISPLAY_PARA_START_ADDR,5,&Wr_data[0]);
                    displayControl.energyDec = BCD_Byte(Wr_data[2]);
                    //if(displayControl.energyDec > 4)
                        displayControl.energyDec = 2;                   
                    displayControl.id[0]=0x00000000;
                    displayControl.idSerialNumber[0]=0x00;
                    displayControl.dispalyObis=1;
                    //memcpy(&displayControl.screenNoData[0], (uchar*)&(displayControl.id[0]), 4);
                    memset(&displayControl.screenNoData[0], 0, 4);
                    //TurnOnePage(&displayControl); //hhl 1003
                    if(!DisplayPrivateSegment(&displayMemoryData))  //display private segment; include data and symbol
                    {
                    }           
                }
                ReflashDisplayMemory(&displayMemoryData);
            }*/
        }
    }
}

extern u8 SymbolGetECData(STR_DISPLAYSYMBOL *sym, u32 ID, u8 idSerialNumber, u8 *ucDLen, u8 *dataType);
extern u8 SymbolGetMDData(STR_DISPLAYSYMBOL *sym, u32 ID, u8 idSerialNumber, u8 *ucDLen, u8 *dataType);
extern u8 SymbolGetVRData(STR_DISPLAYSYMBOL *sym, u32 ID, u8 idSerialNumber, u8 *ucDLen, u8 *dataType);

/*************************************************************
Function: 显示每屏的私有部分
Input:
Output: 
Application area:  
Explain: 
Modification register:
**************************************************************/
uchar DisplayPrivateSegment(STR_DISPLAYMEMORY* displayMemoryData)
{
    uchar buf[8],i,k,dataType,dataLens;//,buf1[8]enabled,
    u16 num=0,startAddress;
    ST_PRIVATE_SYMBOL symbol;
    STR_READDATA_INPUT getDataPara;
    //UN_ULONG_UCHAR obis;
    uchar ID3;
    
    for(displayControl.lcdFigureNum=0;displayControl.lcdFigureNum<LCD_FIGURE_NUM;displayControl.lcdFigureNum++)
    {
        //获取显示符号和信息
        ID3 = displayControl.id[0]>>24;
        if(ID3 == 0x00)
        {
            if(SymbolGetECData(&(displayMemoryData->symbol), displayControl.id[displayControl.lcdFigureNum], displayControl.idSerialNumber[displayControl.lcdFigureNum], &dataLens, &dataType) != DLT_RET_SUCC)
                return 1;
            startAddress = 0;
        }
        else if(ID3 == 0x01)
        {
            if(SymbolGetMDData(&(displayMemoryData->symbol), displayControl.id[displayControl.lcdFigureNum],displayControl.idSerialNumber[displayControl.lcdFigureNum], &dataLens, &dataType) != DLT_RET_SUCC)
                return 1;
            startAddress = 0;
        }
        else if(ID3 == 0x02)
        {
            if(SymbolGetVRData(&(displayMemoryData->symbol), displayControl.id[displayControl.lcdFigureNum], displayControl.idSerialNumber[displayControl.lcdFigureNum], &dataLens, &dataType) != DLT_RET_SUCC)
                return 1;
            startAddress = 0;
        }
        else
        {
        num = SearchInComDispList(displayControl.id[displayControl.lcdFigureNum]);  //get display sybmol
        if(num != 0xffff)
        {
            displayControl.idSerialNumber[displayControl.lcdFigureNum] = ID_STOP_FLAG;
            symbol = privateSymbolList[commDispList[num].privateSymbolListItem];
            dataType = commDispList[num].dataType;
            //enabled = commDispList[num].enabled;
            startAddress = 0;
            dataLens = commDispList[num].dataLens;
            //obis = commDispList[num].obis;
        }
        else
        {
            num = SearchInDispList(displayControl.id[displayControl.lcdFigureNum],displayControl.idSerialNumber[displayControl.lcdFigureNum]);
            if(num != 0xffff)
            {
                displayControl.idSerialNumber[displayControl.lcdFigureNum] = dispList[num].idSerialNumber;
                symbol = privateSymbolList[dispList[num].privateSymbolListItem];
                dataType = dispList[num].dataType;
                startAddress = dispList[num].startAddress;
                dataLens = dispList[num].dataLens;
            }
            else
                return 1;
        }
        }
        
        //获取显示数据
    if(PROGFUNCTION_METER_FACTORY == METER_IN_FACTORY)
        displayMemoryData->symbol.tunji = 1;

    if(PROGFUNCTION_METER_ADJUST == METER_IN_FACTORY)   
        displayMemoryData->symbol.touzhi = 1;
    
        getDataPara.ulID = displayControl.id[displayControl.lcdFigureNum];
        getDataPara.ucFrameNum = displayControl.idSerialNumber[displayControl.lcdFigureNum]>>6;
        if(getDataPara.ulID == 0xffffffd1)
        {
            CommExpDataBuff->Buffer[0]  = 'E';
            CommExpDataBuff->Buffer[1]  = 'R';
            CommExpDataBuff->Buffer[2]  = 'R';
            CommExpDataBuff->Buffer[3]  = '-';
            CommExpDataBuff->Buffer[4]  = ((cardErrorTypeBak%100)/10)+'0';
            CommExpDataBuff->Buffer[5]  = (cardErrorTypeBak%10)+'0';
            CommExpDataBuff->Buffer[6]  = ' ';
            CommExpDataBuff->Buffer[7]  = ' ';
            if(14==cardErrorTypeBak)
            {
                displayMemoryData->symbol.tunji=1;
            }
            
        }
        else if(0xffffff10==(0xffffff10&getDataPara.ulID))
        {
            i=(0xff&getDataPara.ulID);
            GetAlarmDisplayLcdData(&CommExpDataBuff->Buffer[0],i,
            CON_DISPLAY_ALARM_DATATYPE_ALRAM);
            
        }
        else if(0xffffff00==(0xffffff00&getDataPara.ulID))
        {
            i=(0xff&getDataPara.ulID);
            GetAlarmDisplayLcdData(&CommExpDataBuff->Buffer[0],i,
            CON_DISPLAY_ALARM_DATATYPE_ERR);
        }
        else
        {
            if(0x80000000&getDataPara.ulID)
            {
                num =ReadDataDirect(0x7fffffff&getDataPara.ulID, 5,&CommExpDataBuff->Buffer[0]);
            }
            else
            {
                //MTRACE("getDataPara.ulID = 0x%08X\n", getDataPara.ulID);
          //      num = GetDataByID(&getDataPara);//由于与通讯缓冲区使用了同一个缓冲区，导致对通讯有影响，关闭掉
                //MTRACE("getDataPara.ulID = 0x%x, 0x%02X%02X%02X%02X%02X\n", num, CommExpDataBuff->Buffer[0], 
                //    CommExpDataBuff->Buffer[1], CommExpDataBuff->Buffer[2],                     
                //    CommExpDataBuff->Buffer[3], CommExpDataBuff->Buffer[4]);
                if(0x8000<=num)
                {
                    //memset(&CommExpDataBuff->Buffer[0], 0x00, 8);由于与通讯缓冲区使用了同一个缓冲区，导致对通讯有影响，关闭掉
                    startAddress=0;
                }
                else
                {
                    if((startAddress+dataLens)>num)
                    {
                        startAddress=0;
                        memset(&CommExpDataBuff->Buffer[0], 0x00, 8);
                    }
                }
            }
        }
        //if((num&0xe000) != 0)
        //  return 3;
        if(dataLens>8)
            dataLens = 8;
        memset(buf, 0x00, sizeof(buf));
        for(i=startAddress;i<(dataLens+startAddress);i++)
        {
            buf[i-startAddress] = CommExpDataBuff->Buffer[i];
        }
        DataFormatTransformBaudrate(buf,&dataLens,dataType);
        dataLens = DataFormatTransform(buf,dataLens,dataType);
        if(1==dataLens)
        {
            displayMemoryData->symbol.fu=1;
        }
        //以下代码基于BUF为AsK数据，dataLens为AsK数据的长度
        DisplayBufChang(buf,dataType);  //do this function for lCD especial dispaly format
        if(displayControl.lcdFigureNum == 0)
        {
            memcpy(displayMemoryData->value1,buf,sizeof(displayMemoryData->value1));
        }
        else if(displayControl.lcdFigureNum == 1)
        {
            memcpy(displayMemoryData->value2,buf,sizeof(displayMemoryData->value2));
        }
        //memcpy(displayMemoryData->value2,(uchar *)&getDataPara.ulID,sizeof(displayMemoryData->value2));
        displayMemoryData->value2[0] = (uchar)(getDataPara.ulID & 0xff);
        if(displayControl.dispalyObis)
        {
            for(i=0;i<sizeof(displayMemoryData->screenNO)/2;i++)    //显示小8里的数字
            {
                k = (displayControl.screenNoData[displayControl.lcdFigureNum][sizeof(displayMemoryData->screenNO)/2-i-1]>>4)&0x0f;
                displayMemoryData->screenNO[2*i] = k+0x30;
                k = displayControl.screenNoData[displayControl.lcdFigureNum][sizeof(displayMemoryData->screenNO)/2-i-1]&0x0f;
                displayMemoryData->screenNO[2*i+1] = k+0x30;
            }
        }
        else
        {
        }
        if(displayControl.displayMode<2)
        {
            k =(displayControl.idSerialNumber[displayControl.lcdFigureNum] )%100;
            displayMemoryData->ShowIndex[0]=0x30+(k/10);
            displayMemoryData->ShowIndex[1]=0x30+(k%10);
            if(0xFFFFFF00!=(0xFFFFFF00&getDataPara.ulID))
            {
                displayMemoryData->symbol.DP11=1;
                displayMemoryData->symbol.DP13=1;
                displayMemoryData->symbol.DP15=1;
            }
        }
        else
        {
            displayMemoryData->ShowIndex[0]=' ';
            displayMemoryData->ShowIndex[1]=' ';
            
            displayMemoryData->screenNO[0]=' ';
            displayMemoryData->screenNO[1]=' ';
            displayMemoryData->screenNO[2]=' ';
            displayMemoryData->screenNO[3]=' ';
            
        }
        if(isIDNew(displayControl.id[displayControl.lcdFigureNum]) == 0)
            DisplayPrivateSymbol(&symbol,displayMemoryData);
        DisplayPrivateSymbolChange(displayMemoryData,dataType);
    }
    displayControl.lcdFigureNum = 0;
    
    return 0;
}

/*************************************************************
Function:在要求只显示，有效位的时候，调用此函数可以去掉高位
Input:
Output: 
Application area:  
Explain: 
Modification register:
**************************************************************/
void JustActiveDisplayWord(uchar* buf,uchar startAddr,uchar endAddr)
{
    uchar i;
    
    for(i=startAddr;i<=endAddr;i++)
    {
        if((buf[i] == '0') || (buf[i] == ' ')) //空格也是需要的，为了break
        {
            buf[i] = ' ';
        }
        else
        {
            break;
        }
    }
}
void DataFormatTransformBaudrate(uchar * buf, uchar *lens, uchar dataType)
{
    ulong ulData;
    if (DATA_TYPE_BAUDRATE==dataType)
    {
        ulData=300*(0x7e&buf[0]);
        LongToData4BCD(ulData,&buf[0]);
        if(ulData>9600)
        {
            *lens=3;
        }
        else
        {
            *lens=2;
        }
    }
    
}

uchar DataFormatTransform(uchar* buf,uchar lens,uchar dataType)
{
    uchar i,j,k,buf1[8],endAddr;
    uchar sign;
    UN_ULONG_UCHAR data;
    sign = 0;
    data.l = 0;
    if(dataType > DATA_TYPE_HEX_AMBIT)  //hex to bcd
    {
        for(i=0;i<lens;i++)
            data.b[i]=buf[i];
        i = data.l%10;
        buf[0] = i+0x30;
        j = (data.l/10)%10;
        buf[1] = j+0x30;
        i = (data.l/100)%10;
        buf[2] = i+0x30;
        j = (data.l/1000)%10;
        buf[3] = j+0x30;
        i = (data.l/10000)%10;
        buf[4] = i+0x30;
        j = (data.l/100000)%10;
        buf[5] = j+0x30;
        i = (data.l/1000000)%10;
        buf[6] = i+0x30;
        j = (data.l/10000000)%10;
        buf[7] = j+0x30;
    }
    else if(dataType > DATA_TYPE_BCD_AMBIT)
    {
        ;
    }
    else if(dataType < DATA_TYPE_BCD_AMBIT)
    {
        switch(dataType)
        {
            case DATA_TYPE_DL:
            case DATA_TYPE_DL_signed:
                lens = manageDLData(buf,dataType,&sign);
            break;
            case DATA_TYPE_XL:
            case DATA_TYPE_XL_signed:
                lens = manageXLData(buf,dataType,&sign);
            break;
            case DATA_TYPE_VOLTAGE:
                lens = manageVoltageData(buf,dataType,&sign);
            break;
            case DATA_TYPE_CURRENT:
                lens = manageCurrentData(buf,dataType,&sign);
            break;
            case DATA_TYPE_POWER_COSE:
                lens = managePowercosData(buf,dataType,&sign);
            break;
            //case DATA_TYPE_PHASIE:
            //  lens = managePhasieData(buf,dataType,&sign);
            //break;
            case DATA_TYPE_WENDU:
                if((buf[1]&0x80) == 0x80)
                {
                    sign = 1;
                    buf[1] &=~0x80;
                }
            break;
            default:
            break;
        }
        if(lens > 4)
            lens = 4;
        for(i=0;i<lens;i++)
        {
            k = (buf[lens-1-i]>>4)&0x0f;
            buf1[2*i+(4-lens)*2] = k+0x30;
            k = (buf[lens-1-i])&0x0f;
            buf1[2*i+1+(4-lens)*2] = k+0x30;
        }
        for(i=0;i<(4-lens)*2;i++)
            buf1[i] = ' ';
        
        switch(dataType)
        {
            /*case DATA_TYPE_BCD3_8_L:
                buf1[0] = 'L';
                buf1[1] = '-';
            break;
            case DATA_TYPE_BCD3_8_H:
                buf1[0] = 'H';
                buf1[1] = '-';
            break;
            case DATA_TYPE_BCD5_8_H:
                buf1[2] = 'H';
                buf1[3] = '-';
            break;
            case DATA_TYPE_BCD3_6_H:
                buf1[0] = 'H';
                buf1[1] = '-';
                memcpy(&buf1[2],&buf1[4],4);
                buf1[6] = ' ';
                buf1[7] = ' ';              
            break;*/
            case DATA_TYPE_DL:
            case DATA_TYPE_DL_signed:
        /*#if(REPAY_FUNCTION_STYLE == METER_STYLE_PRICE)
            case DATA_TYPE_JE:
        #endif*/
// #if(CONFIG_METER_AREA_MODE_HENAN!=CONFIG_METER_AREA_MODE)
#if(CONFIG_METER_DISPLAY_POWER_HIGHZERO_MODE != CONFIG_METER_DISPLAY_POWER_HIGHZERO_MODE_ENABLE)
                endAddr = 4;
                if(displayControl.energyDec == 1)
                {
                    endAddr = 5;
                }
                else if(displayControl.energyDec == 0)
                {
                    endAddr = 6;
                }
                 else if(displayControl.energyDec == 3)
                {
                    endAddr = 3;
                }
                    else if(displayControl.energyDec == 4)
                {
                    endAddr = 2;
                }
                JustActiveDisplayWord(buf1,0,endAddr);
#endif
            break;
            case DATA_TYPE_VOLTAGE:
                JustActiveDisplayWord(buf1,4,5);
            break;
            case DATA_TYPE_CURRENT:
                JustActiveDisplayWord(buf1,2,3);
            break;
            case DATA_TYPE_XL:
            case DATA_TYPE_XL_signed:               
#if(CONFIG_METER_DISPLAY_POWER_HIGHZERO_MODE != CONFIG_METER_DISPLAY_POWER_HIGHZERO_MODE_ENABLE)
                endAddr = 2;
                if(displayControl.powerDec == 3)
                {
                    endAddr = 3;
                }
                else if(displayControl.powerDec == 2)
                {
                    endAddr = 4;
                }
                else if(displayControl.powerDec == 1)
                {
                    endAddr = 5;
                }
                else if(displayControl.powerDec == 0)
                {
                    endAddr = 6;
                }
                    else if(displayControl.powerDec == 5)
                {
                    endAddr = 1;
                }
                    else if(displayControl.powerDec == 6)
                {
                    endAddr = 0;
                }
                JustActiveDisplayWord(buf1,0,endAddr);
#else
                if(displayControl.powerDec == 5)
                {
                    buf1[0]=' ';
                }
                else if(displayControl.powerDec == 3)
                {
                    buf1[2]=' ';
                }
                else if(displayControl.powerDec == 1)
                {
                    buf1[4]=' ';
                }
//              JustActiveDisplayWord(buf1,2,endAddr);
#endif
            break;
            /*case DATA_TYPE_DATA:
                buf1[6] = ' ';

            break;*/
        /*#if(REPAY_FUNCTION_STYLE == METER_STYLE_PRICE)
            case DATA_TYPE_PRICE:
                JustActiveDisplayWord(buf1,0,2);
            break;
        #endif*/
            default:
            break;
        }
        
        memcpy(buf,buf1,sizeof(buf1));
    }   
    
    return(sign);
}

uchar managePowercosData(uchar* buf,uchar dataType,uchar* sign)
{
    uchar buf1[4],i,returnData;
    
    if((buf[3]&0x80) == 0x80)
        *sign = 1;
    buf[3] &=~0x80;
        
    for(i=0;i<2;i++)
    {
        //buf1[i] = ((buf[i]&0xf0)>>4)+(buf[i+1]<<4);
        buf1[i] = buf[i+2];
    }
    returnData = 2;
    memcpy(buf,buf1,returnData);
        
    return(returnData);
}

uchar managePhasieData(uchar* buf,uchar dataType,uchar* sign)
{
    uchar buf1[4],i,returnData;
        
    for(i=0;i<2;i++)
    {
        buf1[i] =( (buf[i+1]&0xf0)>>4)+(buf[i+2]<<4);
    }
    returnData = 2;
    memcpy(buf,buf1,returnData);
        
    return(returnData);
}


uchar manageCurrentData(uchar* buf,uchar dataType,uchar* sign)
{
    uchar buf1[4],i,returnData;
    
    if((buf[3]&0x08) == 0x08)
        *sign = 1;
    buf[3] &=~0x08;
        
    for(i=0;i<3;i++)
    {
        buf1[i] = (buf[i]&0xf0)>>4;
                buf1[i] = buf1[i]+(buf[i+1]<<4);
    }
    returnData = 3;
    memcpy(buf,buf1,returnData);
        
    return(returnData);
}


uchar manageVoltageData(uchar* buf,uchar dataType,uchar* sign)
{
    uchar buf1[4],i,returnData;
    
    for(i=0;i<2;i++)
    {
        buf1[i] =( (buf[i+1]&0xf0)>>4);
        buf1[i] = buf1[i]+(buf[i+2]<<4);
    }
    returnData = 2;
    memcpy(buf,buf1,returnData);
        
    return(returnData);
}

uchar manageXLData(uchar* buf,uchar dataType,uchar* sign)
{
    uchar returnData;
    ulong ulTemp;
    if(dataType == DATA_TYPE_XL_signed)
    {
        if((buf[3]&0x80) == 0x80)
            *sign = 1;
        buf[3] &=~0x80;
    }

    memcpy((uchar *) &ulTemp, buf, 4);
    
    switch (displayControl.powerDec)
    {
        case 0:
            ulTemp=ulTemp>>24;
            returnData = 1;
            break;
        case 1:
            ulTemp=ulTemp>>20;
            returnData = 2;
            break;
        case 2:
            ulTemp=ulTemp>>16;
            returnData = 2;
            break;
        case 3:
            ulTemp=ulTemp>>12;
            returnData = 3;
            break;
        case 4:
            ulTemp=ulTemp>>8;
            returnData = 3;
            break;
        case 5:
            ulTemp =ulTemp>>4;
            returnData = 4;
            break;
        case 6:
            returnData = 4;
            break;
        default:
            ulTemp=ulTemp>>8;
            returnData = 3;
            break;
    }
    memcpy(buf,(uchar *) &ulTemp,  4);
    
    return(returnData);
}


uchar manageDLData(uchar* buf,uchar dataType,uchar* sign)
{
    uchar buf1[4];
    ulong ulTemp;
    memset(&buf1[0], 0x00, 4);
    if(dataType == DATA_TYPE_DL_signed)
    {
        if((buf[4]&0x80) == 0x80)
            *sign = 1;
        buf[4] &=~0x80;
    }
    //memcpy((uchar *) &ulTemp, &buf[1], 4);
    switch (displayControl.energyDec)
    {
        case 0:
            memcpy((uchar *) &ulTemp, &buf[1], 4);
            ulTemp=ulTemp>>8;
            break;
        case 1:
            memcpy((uchar *) &ulTemp, &buf[1], 4);
            ulTemp=ulTemp>>4;
            break;
        case 2:
            memcpy((uchar *) &ulTemp, &buf[1], 4);
            break;
        case 3:
            memcpy((uchar *) &ulTemp, &buf[1], 4);
            ulTemp =(ulTemp<<4)+(buf[0]>>4);
            break;
        case 4:
            memcpy((uchar *) &ulTemp, &buf[0], 4);
            break;
        default:
            memcpy((uchar *) &ulTemp, &buf[1], 4);
            break;
    }
    memcpy(buf,(uchar *) &ulTemp,  4);
    
    return(4);
}


void DisplayBufChang(uchar* buf,uchar dataType)
{
    uchar i,j,transfer,fillMatter;
    
    transfer = 0;
    fillMatter = ' ';
    switch(dataType)
    {
        case DATA_TYPE_DL:
        case DATA_TYPE_DL_signed:
        break;
        case DATA_TYPE_BCD_XINGQI:
            buf[6]=' ';
#if(CONFIG_METER_AREA_MODE_HUABEI==CONFIG_METER_AREA_MODE)
            if('7'==buf[7])
            {
                buf[7]='0';
            }
#else
            if('0'==buf[7])
            {
                buf[7]='7';
            }
#endif            
        break;
        case DATA_TYPE_XL:
        case DATA_TYPE_XL_signed:
        break;
        case DATA_TYPE_SQSD:
        break;
        case DATA_TYPE_BCD1_8:
        case DATA_TYPE_BCD1_8_signed:
            //transfer = 1;
        break;
        case DATA_TYPE_BCD2_8:
            //transfer = 1;
        break;
        case DATA_TYPE_BCD3_8:
        break;
        case DATA_TYPE_BCD4_8:
        break;
        case DATA_TYPE_ASC1_8:
        break;
        case DATA_TYPE_ASC2:
        break;
        case DATA_TYPE_ASC3:
        break;
        case DATA_TYPE_ASC4:
        break;
        case DATA_TYPE_BAUDRATE:
        break;
        default:
        break;
    }
    
    if((transfer&0x80) == 0x00) //左移
    {
        for(i=0;i<transfer;i++)
        {
            for(j=0;j<7;j++)
            {
                buf[j] = buf[j+1];
            }
            buf[7] = fillMatter;
        }
    }
    else    //右移
    {
        ;
    }
}


void DisplayPrivateSymbolChange(STR_DISPLAYMEMORY* displayMemoryData,uchar dataType)
{
    uchar i;
    
    if((dataType == DATA_TYPE_DL)||(dataType == DATA_TYPE_DL_signed))
    {
        if(displayControl.energyDec == 0)   // 1 为小数
        {
            displayMemoryData->symbol.DP7 = 0;
        }
        else if(displayControl.energyDec == 1)  // 1 为小数
        {
            displayMemoryData->symbol.DP7 = 0;
            displayMemoryData->symbol.DP8 = 1;
        }
        else if(displayControl.energyDec == 2)    // 2 为小数
        {
            displayMemoryData->symbol.DP5 = 0;
            displayMemoryData->symbol.DP7 = 1;
        }
        else if(displayControl.energyDec == 3)  // 3 为小数
        {
            displayMemoryData->symbol.DP7 = 0;
            displayMemoryData->symbol.DP6 = 1;
        }
        else if(displayControl.energyDec == 4)  // 4 为小数
        {
            displayMemoryData->symbol.DP7 = 0;
            displayMemoryData->symbol.DP5 = 1;
        }
    }
    else if((dataType == DATA_TYPE_XL)||(dataType == DATA_TYPE_XL_signed))
    {
        if(displayControl.powerDec == 0)    // 0 为小数
        {
            displayMemoryData->symbol.DP5 = 0;
        }
        else if(displayControl.powerDec == 1)   // 1 为小数
        {
            displayMemoryData->symbol.DP5 = 0;
            displayMemoryData->symbol.DP8 = 1;
        }
        else if(displayControl.powerDec == 2)   // 2 为小数
        {
            displayMemoryData->symbol.DP5 = 0;
            displayMemoryData->symbol.DP7 = 1;
        }
        else if(displayControl.powerDec == 3)   // 3 为小数
        {
            displayMemoryData->symbol.DP5 = 0;
            displayMemoryData->symbol.DP6 = 1;
        }
        else if(displayControl.powerDec == 4)   // 4 为小数
        {
            displayMemoryData->symbol.DP6 = 0;
            displayMemoryData->symbol.DP5 = 1;
        }
        else if(displayControl.powerDec == 5)   // 5 为小数
        {
            displayMemoryData->symbol.DP5 = 0;
            displayMemoryData->symbol.DP4 = 1;
        }
        else if(displayControl.powerDec == 6)   // 6 为小数
        {
            displayMemoryData->symbol.DP5 = 0;
            displayMemoryData->symbol.DP3 = 1;
        }
    }
    else if(dataType == DATA_TYPE_VOLTAGE)    // 1 位小数
    {
        displayMemoryData->symbol.DP8 = 1;
    }
    else if(dataType == DATA_TYPE_CURRENT)    // 3 位小数
    {
        displayMemoryData->symbol.DP6 = 1;
    }
    else if(dataType == DATA_TYPE_WENDU)    // 1 位小数
    {
        displayMemoryData->symbol.DP5 = 0;
        displayMemoryData->symbol.DP8 = 1;
    }
    else if(dataType == DATA_TYPE_ERROR)
    {
        for(i=0;i<8;i++)
        {
            displayMemoryData->screenNO[i] = ' ';
        }
        displayMemoryData->ShowIndex[0]=' ';
        displayMemoryData->ShowIndex[1]=' ';
    }
}

/*************************************************************
Function: 显示表里储存的符号
Input:
Output: 
Application area:  
Explain: 
Modification register:
**************************************************************/
void DisplayPrivateSymbol(ST_PRIVATE_SYMBOL* symbol,STR_DISPLAYMEMORY* displayMemoryData)
{
//  AA   重新映射标点符号  AA


    if(symbol->data1&0x80)
        displayMemoryData->symbol.DP8 = 1;
    if(symbol->data1&0x40)
        displayMemoryData->symbol.col2= 1;
    if(symbol->data1&0x20)
        displayMemoryData->symbol.DP7 = 1;
    if(symbol->data1&0x10)
        displayMemoryData->symbol.DP6 = 1;
    if(symbol->data1&0x08)
        displayMemoryData->symbol.col1= 1;
    if(symbol->data1&0x04)
        displayMemoryData->symbol.DP5 = 1;
    if(symbol->data1&0x02)
        displayMemoryData->symbol.DP4 = 1;
    if(symbol->data1&0x01)
        displayMemoryData->symbol.DP3 = 1;
    
    if(symbol->data2&0x40)
        displayMemoryData->symbol.You = 1;
    if(symbol->data2&0x20)
        displayMemoryData->symbol.Wu = 1;
    if(symbol->data2&0x10)
        displayMemoryData->symbol.Gong = 1;
    if((symbol->data2&0x0f) == 1)
    {
        displayMemoryData->symbol.KW = 1;
    }
    else if((symbol->data2&0x0f) == 2)
    {
        displayMemoryData->symbol.KW = 1;
        displayMemoryData->symbol.h1 = 1;
    }
    else if((symbol->data2&0x0f) == 3)
    {
        displayMemoryData->symbol.kvar = 1;
    }
    else if((symbol->data2&0x0f) == 4)
    {
        displayMemoryData->symbol.kvar = 1;
        displayMemoryData->symbol.h2 = 1;
    }
    else if((symbol->data2&0x0f) == 5)
    {
        displayMemoryData->symbol.V = 1;
    }
    else if((symbol->data2&0x0f) == 6)
    {
        displayMemoryData->symbol.A = 1;
    }
    else if((symbol->data2&0x0f) == 7)
    {
        displayMemoryData->symbol.kva= 1;
    }
    else if((symbol->data2&0x0f) == 8)
    {
        displayMemoryData->symbol.kvah= 1;
    }
    else if((symbol->data2&0x0f) ==10)
    {
        displayMemoryData->symbol.yuan= 1;
    }
    
    if(symbol->data3&0x80)
        displayMemoryData->symbol.Zong = 1;

#if(CONFIG_METER_AREA_MODE_SHANGHAI==CONFIG_METER_AREA_MODE)
    if(symbol->data3&0x40)
        displayMemoryData->symbol.Ping= 1;
    if(symbol->data3&0x20)
        displayMemoryData->symbol.Gu= 1;
    if(symbol->data3&0x10)
        displayMemoryData->symbol.Jian= 1;
    if(symbol->data3&0x08)
        displayMemoryData->symbol.Feng= 1;
#else
    if(symbol->data3&0x40)
        displayMemoryData->symbol.Jian = 1;
    if(symbol->data3&0x20)
        displayMemoryData->symbol.Feng = 1;
    if(symbol->data3&0x10)
        displayMemoryData->symbol.Ping = 1;
    if(symbol->data3&0x08)
        displayMemoryData->symbol.Gu = 1;
#endif  
    if(symbol->data3&0x04)
        displayMemoryData->symbol.Xu = 1;
    if(symbol->data3&0x02)
        displayMemoryData->symbol.Dian = 1;
    if(symbol->data3&0x01)
        displayMemoryData->symbol.Liang = 1;
    
    if(symbol->data4&0x80)
        displayMemoryData->symbol.meterNum = 1;
    if(symbol->data4&0x40)
        displayMemoryData->symbol.shengyu= 1;
    if(symbol->data4&0x20)
        displayMemoryData->symbol.Power = 1;
    if(symbol->data4&0x10)
        displayMemoryData->symbol.DangQian = 1;
    if(symbol->data4&0x08)
        displayMemoryData->symbol.phaseA= 1;
    if(symbol->data4&0x04)
        displayMemoryData->symbol.phaseB= 1;
    if(symbol->data4&0x02)
        displayMemoryData->symbol.phaseC= 1;
    if(symbol->data4&0x01)
        displayMemoryData->symbol.phaseN= 1;
    
    if(symbol->data5&0x80)
        displayMemoryData->symbol.Zheng = 1;
    if(symbol->data5&0x40)
        displayMemoryData->symbol.Fan = 1;
    if(symbol->data5&0x20)
        displayMemoryData->symbol.fangXiang= 1;
    if(symbol->data5&0x10)
        displayMemoryData->symbol.Ya = 1;
    if(symbol->data5&0x08)
        displayMemoryData->symbol.Liu = 1;
    if(symbol->data5&0x04)
        displayMemoryData->symbol.Shi = 1;
    if(symbol->data5&0x02)
        displayMemoryData->symbol.Shang1 = 1;
    if(symbol->data5&0x01)
        displayMemoryData->symbol.month = 1;
    
    if(symbol->data6&0x80)
        displayMemoryData->symbol.zuhe= 1;
    if(symbol->data6&0x40)
        displayMemoryData->symbol.jieti= 1;
    if(symbol->data6&0x20)
        displayMemoryData->symbol.sheqian= 1;
    if(symbol->data6&0x10)
        displayMemoryData->symbol.jiage= 1;
    if(symbol->data6&0x08)
        displayMemoryData->symbol.timeshi= 1;
    if(symbol->data6&0x04)
        displayMemoryData->symbol.timejian= 1;
    if(symbol->data6&0x02)
        displayMemoryData->symbol.duan= 1;
    //if(symbol->data6&0x01)
    //  displayMemoryData->symbol.jine= 1;
    
    if(symbol->data7&0x80)
        displayMemoryData->symbol.changshu= 1;
//  if(symbol->data7&0x40)
//      displayMemoryData->symbol.jieti= 1;
//  if(symbol->data7&0x20)
//      displayMemoryData->symbol.sheqian= 1;
    if(symbol->data7&0x10)
    {
        displayMemoryData->symbol.cos= 1;
        displayMemoryData->symbol.jiaodu= 1;
    }
    if(symbol->data7&0x08)
    {
        displayMemoryData->symbol.wugongxiangxian1= 1;
    }
    if(symbol->data7&0x04)
    {
        displayMemoryData->symbol.wugongxiangxian1= 1;
        displayMemoryData->symbol.wugongxiangxian2= 1;
    }
    if(symbol->data7&0x02)
    {
        displayMemoryData->symbol.wugongxiangxian1= 1;
        displayMemoryData->symbol.wugongxiangxian2= 1;
        displayMemoryData->symbol.wugongxiangxian3= 1;
    }
    if(symbol->data7&0x01)
    {
        displayMemoryData->symbol.wugongxiangxian3= 1;
        displayMemoryData->symbol.wugongxiangxian4= 1;
    }
    
//  if(symbol->data8&0x80)
//      displayMemoryData->symbol.zuhe= 1;
//  if(symbol->data8&0x40)
//      displayMemoryData->symbol.jieti= 1;
//  if(symbol->data8&0x20)
//      displayMemoryData->symbol.sheqian= 1;
//  if(symbol->data8&0x10)
//      displayMemoryData->symbol.jiage= 1;
//  if(symbol->data8&0x08)
//      displayMemoryData->symbol.timeshi= 1;
//  if(symbol->data8&0x04)
//      displayMemoryData->symbol.timejian= 1;
//  if(symbol->data8&0x02)
//      displayMemoryData->symbol.duan= 1;
//  if(symbol->data8&0x01)
//      displayMemoryData->symbol.jine= 1;
    
    
    if(symbol->data9&0x80)
    {
        if(symbol->data8&0x40)
            displayMemoryData->symbol.Xiang = 1;
    }
//  if(symbol->data8&0x08)
//      displayMemoryData->symbol.ZuiDa = 1;
//  if(symbol->data8&0x04)
//      displayMemoryData->symbol.Rong = 1;
//  if(symbol->data8&0x02)
//      displayMemoryData->symbol.Xing = 1;
//  if(symbol->data8&0x01)
//      displayMemoryData->symbol.ChiShu = 1;
        
//  if(symbol->data9&0x80)
//      displayMemoryData->symbol.Duan = 1;
//  if(symbol->data9&0x40)
//      displayMemoryData->symbol.data = 1;
//  if(symbol->data9&0x20)
//      displayMemoryData->symbol.time = 1;
//  if(symbol->data9&0x10)
//      displayMemoryData->symbol.Gan = 1;
    if(symbol->data9&0x08)
        displayMemoryData->symbol.Shang2 = 1;
    if(symbol->data9&0x20)
    {
        displayMemoryData->symbol.timeshi= 1;
        displayMemoryData->symbol.timejian= 1;
    }
    //if(symbol->data2&0x80)
    //  displayMemoryData->symbol.SDP4 = 1;
}


/*************************************************************
Function: 显示每屏公共符号
Input:
Output: 
Application area:  
Explain: 
Modification register:
**************************************************************/
void DisplayPublicSegment(STR_DISPLAYMEMORY* displayMemoryData)
{
    uchar Flag;
    //uchar ucTemp[8];
    if(CON_POWER_STATUS_USE_WAKEUPBAT!=FLG_POWER_STATUS)
    {
        displayMemoryData->symbol.quadrant = QUADRANT_Z;
        if(STATUS_PRICE <= 4)
            displayMemoryData->symbol.feeRate = STATUS_PRICE;
        
        Flag = VoltageAlarm();
        if(Flag&0x01)
            displayMemoryData->symbol.Ua = 1;
        if(Flag&0x02)
            displayMemoryData->symbol.Ub = 1;
        if(Flag&0x04)
            displayMemoryData->symbol.Uc = 1;
        if(FLG_ORDER_VOLTAGE_STATUS)
            displayMemoryData->symbol.nixiangxu =1;
#if (CONFIG_METER_AREA_MODE!=CONFIG_METER_AREA_MODE_SHANDONG)
        if(FLG_ORDER_CURRENT_STATUS)
            displayMemoryData->symbol.nixiangxu =1;
#endif      
#if (CONFIG_METER_AREA_MODE==CONFIG_METER_AREA_MODE_ZHEJIANG_HANGZHOU)
        if((RSOFT_RTC_SECOND&0x1) == 0)
            displayMemoryData->symbol.nixiangxu =0;
#endif

        Flag = CurrentAlarm();
        if(Flag&0x01)
            displayMemoryData->symbol.Ia = 1;
        if(Flag&0x02)
            displayMemoryData->symbol.Ib = 1;
        if(Flag&0x04)
            displayMemoryData->symbol.Ic = 1;
        if(FLG_A_REVERSEKW_STATUS)
            displayMemoryData->symbol.symbol_1 = 1;
        if(FLG_B_REVERSEKW_STATUS)
            displayMemoryData->symbol.symbol_2 = 1;
        if(FLG_C_REVERSEKW_STATUS)
            displayMemoryData->symbol.symbol_3 = 1;
        
        Flag = BatterAlarm();
        if(Flag&0x01)
            displayMemoryData->symbol.batter1 = 1;
        if(Flag&0x02)
            displayMemoryData->symbol.batter2 = 1;
        if(1==STATUS_DAYTABLEPOINT)
        {
            displayMemoryData->symbol.shiduan1=1;
        }
        else
        {
            displayMemoryData->symbol.shiduan2=1;
        }

#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
#if(CONFIG_METER_STEP_MODE==CONFIG_METER_STEP_MODE_ENABLE)
        
        if(RAM[RAM_COEF_STEP_NUM])
        {
            if(STATUS_STEPPRICE_NUM<=4)
            {
                displayMemoryData->symbol.jietiPrice=STATUS_STEPPRICE_NUM;
            }
            else
            {
                displayMemoryData->symbol.jietiPrice=0;  //not display
            }
            if(FLG_STEPPRICETABLE_STATUS)
            {
                displayMemoryData->symbol.jietitao1=0;
                displayMemoryData->symbol.jietitao2=1;
            }
            else
            {
                displayMemoryData->symbol.jietitao1=1;
                displayMemoryData->symbol.jietitao2=0;
            }
        }
#endif
        if(FLG_RELAY_ON_ALARM_STATUS == 0)
        {
            if(RELAY_ORDER_STATE_FLAG == 1)
            {
                displayMemoryData->symbol.lazha= 1;
                
            }
            else
            {
                if((RSOFT_RTC_SECOND&0x1))
                {
                    displayMemoryData->symbol.lazha = FLG_RELAY_OFF_ALARM_STATUS;

                }
            }
        }
        if((RSOFT_RTC_SECOND&0x1))
        {
            //只要小于报警金额1就显示 请购电
            displayMemoryData->symbol.qinggoudian= RELAY_ORDER_ALARM_FLAG|PREPAY_ALARM1_FLAG|PREPAY_ALARM2_FLAG|PREPAY_ALARM3_FLAG;
#if(CONFIG_METER_AREA_MODE_SHANDONG==CONFIG_METER_AREA_MODE)
            if(displayMemoryData->symbol.qinggoudian==0)
            {
                displayMemoryData->symbol.qinggoudian= RELAY_COMMAND_STATE_FLAG; // FLG_RELAY_ON_ALARM_STATUS;
            }
            if(displayMemoryData->symbol.qinggoudian==0)
            {
                displayMemoryData->symbol.qinggoudian= RELAY_STATE_FLAG;
            }
#endif                  
        }

#if(CONFIG_METER_PREPAY_MODE == CONFIG_METER_PREPAY_MODE_LOCATION)

        if(uiAlarmDisplayCardReadTimes>0)
        {
            switch(readCardStatus)
            {
                case 1:
                    displayMemoryData->symbol.dukazhong=1;
                    break;
                case 2:
                    displayMemoryData->symbol.chenggong=1;
                    break;
                case 3:
                    displayMemoryData->symbol.shibai=1;
                    break;
                default:
                    break;
            }
        }
        if(0==FACTORY_FLAG_KEY )
        {
            displayMemoryData->symbol.shiyanshi=1;
        }
        if(0x40==(errDisplayID&0x40))
        {
            displayMemoryData->symbol.touzhi=1;
        }
#endif
#endif      
        if(STATUS_DAYTABLE <= 4)
            displayMemoryData->symbol.ShiTaoNum = STATUS_DAYTABLE;
        if(20!=TestZeroNum(&RAM[RAM_PASSWORD_LOCK_TIME_START], 20))
        {
            displayMemoryData->symbol.suoding= 1;
        }
        if(FLG_PROGRAM_STATUS)
        {
            displayMemoryData->symbol.biancheng= 1;
        }
#if(CONFIG_METER_AREA_MODE_SHANGHAI!=CONFIG_METER_AREA_MODE)
        if(ucAlarmLedStatus)
        {
            displayMemoryData->symbol.baojing=1;
        }
#endif
    }
//  if(DISPLAY_FLG_CLR)
//      displayMemoryData->symbol.QingLing = 1;
//  if(DISPLAY_FLG_ASK)
//      displayMemoryData->symbol.interrogation = 1;
    
//  displayMemoryData->symbol.ShiTao = 1;
    
    Flag = 0;
    if(ucCommFlgStatusChannel01 != 0)
    {
        displayMemoryData->symbol.tongxunIr= 1;
    }
    if(ucCommFlgStatusChannel03 != 0)
    {
        displayMemoryData->symbol.tongxun4851= 1;
    }
    if(ucCommFlgStatusChannel04 != 0)
    {
#if(CONFIG_METER_NO2COMM_MODE_RS485==CONFIG_METER_NO2COMM_MODE)
        displayMemoryData->symbol.tongxun4852= 1;
#endif
#if(CONFIG_METER_NO2COMM_MODE_PLC==CONFIG_METER_NO2COMM_MODE)
        displayMemoryData->symbol.tongdian= 1;
#endif
#if(CONFIG_METER_NO2COMM_MODE_WIRELESS==CONFIG_METER_NO2COMM_MODE)
//      displayMemoryData->symbol.tongxun4852= 1;
#endif
    }
    
#if(CONFIG_METER_NO2COMM_MODE_WIRELESS==CONFIG_METER_NO2COMM_MODE)
    Flag=0x07&RAM[RAM_CURRENT_MODULE_DATA];
    if(Flag>7)
    {
        Flag=7;
    }
    displayMemoryData->symbol.GprsXinhao=Flag;
    if(0x80&RAM[RAM_CURRENT_MODULE_DATA])
    {
        Flag=1;
    }
    else
    {
        Flag=0;
    }
    if(ucCommFlgStatusChannel04 !=0)
    {
        if(realTime.second%2 == 1)
        {
            if(0x80&RAM[RAM_CURRENT_MODULE_DATA])
            {
                Flag=0;
            }
            else
            {
                Flag=1;
            }
        }
    }
    if(Flag)
    {
        displayMemoryData->symbol.GprsZaixian=1;
    }
    else
    {
        displayMemoryData->symbol.GprsZaixian=0;
    }
#endif
}

void TurnPageCallBack(void)
{
    displayControl.displayTurnPageFlag = 1;
}


/*************************************************************
Function: 显示翻页函数（包括同ID的不同页面）
Input:
Output: 
Application area:  
Explain: 
Modification register:
**************************************************************/
uchar DisplayTurnPage(ST_DISPLAY_CONTROL* controlData)
{   
    uchar i,returnData;
    ST_DISPLAY_MODE_CHANGE displayType;
    
    returnData = 0;
    if(controlData->displayTurnPageFlag)
    {
        controlData->displayTurnPageFlag = 0;
        StartTime1s(T1SID_TURN_PAGE_TIMER_NUM, controlData->turnTime[controlData->displayMode], TIMER_MODE_CONTINUE, TurnPageCallBack);
        returnData = 1;
        for(controlData->lcdFigureNum=0;controlData->lcdFigureNum<LCD_FIGURE_NUM;controlData->lcdFigureNum++)
        {
            for(i=0;i<LCD_FIGURE_NUM;i++)
            {
                TurnOnePage(controlData);
                if(controlData->displayModeTurnFlag)
                    break;
            }
            if(controlData->displayModeTurnFlag == 1)
            {
                controlData->displayModeTurnFlag = 0;
                
                if(controlData->lcdFigureNum == 0)
                {
                    displayType.displayMode = TAKE_TURN_DISPLAY_MODE;
                    SpringDifferentDisplayMode(&displayType);
                }
                //在显示的时候是否要记录有一个显示的实际行数
                break;
            }
        }
    }
    
    return(returnData);
}

void TurnOnePage(ST_DISPLAY_CONTROL* controlData)
{
    u16 errorFlag;//,flag
    
    //flag = 0;
    if(controlData->displayMode == TAKE_TURN_DISPLAY_MODE)
    {
        errorFlag = 0;
        if(controlData->currentItem[controlData->displayMode][controlData->lcdFigureNum]<(controlData->itemNum[controlData->displayMode]-1))
            controlData->currentItem[controlData->displayMode][controlData->lcdFigureNum]++; 
        else
        {
            if(0xff != SearchErrorDisplayInformation(&(displayControl.id[0]), &(displayControl.idSerialNumber[0])))
            {
                errorFlag = 1;
            }
            else
            {
                controlData->currentItem[controlData->displayMode][controlData->lcdFigureNum] = 0;
                if(0xff != SearchAlarmDisplayInformation(&(displayControl.id[0]), &(displayControl.idSerialNumber[0])))
                {
                    errorFlag = 1;
                }
                else
                {
                    alarmDisplaycurrentItem = 0;
                    controlData->currentItem[controlData->displayMode][controlData->lcdFigureNum] = 0;
                    displayControl.currentItem[displayControl.displayMode][0] = 0;
                }
            }
        }
        if(errorFlag==0)
        {
            GetDisplayID(controlData);
            GetIdSerialNumber(controlData);
        }
    }
    else if(controlData->displayMode == KEY_TURN_DISPLAY_MODE)
    {
        /*if((controlData->idSerialNumber[controlData->lcdFigureNum]&0x3f) != ID_STOP_FLAG)
        {
            num = SearchInDispList(controlData->id[controlData->lcdFigureNum],controlData->idSerialNumber[controlData->lcdFigureNum]);
            if(num < GetDispListLens())
            {
                if(controlData->id[controlData->lcdFigureNum] == dispList[num+1].id)
                {
                    controlData->idSerialNumber[controlData->lcdFigureNum] = dispList[num+1].idSerialNumber;
                    flag = 1;
                }
                else
                {
                    controlData->idSerialNumber[controlData->lcdFigureNum] = ID_STOP_FLAG;
                }
            }
            else
            {
                controlData->idSerialNumber[controlData->lcdFigureNum] = ID_STOP_FLAG;
            }
        }*/
        //if(((controlData->idSerialNumber[controlData->lcdFigureNum]&0x3f) == ID_STOP_FLAG)&&(flag == 0))
        //{
            controlData->displayModeTurnFlag = 1;//标志一个键盘ID已经显示完成
        //}
    }
    else if(controlData->displayMode == APPOINT_DISPLAY_MODE)
    {
        controlData->displayModeTurnFlag = 1;
    }
    else if(controlData->displayMode == CARD_DISPLAY_MODE)
    {
        controlData->displayModeTurnFlag = 1;
    }
    
}


void MamageExtInput(void)
{
    uchar flag;
    ST_DISPLAY_MODE_CHANGE displayType;
    
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)

#if(CONFIG_METER_AREA_MODE_SHANGHAI!=CONFIG_METER_AREA_MODE)
    flag = 0;
    if(cardErrorType>0)
    {
        cardErrorTypeBak = cardErrorType;
        if(cardErrorTypeBak>0)
        {
            displayType.displayMode = CARD_DISPLAY_MODE;
            SpringDifferentDisplayMode(&displayType);
            flag = 1;
        }
        else
        {
            if(displayControl.displayMode == CARD_DISPLAY_MODE)
            {
                displayType.displayMode = TAKE_TURN_DISPLAY_MODE;
                SpringDifferentDisplayMode(&displayType);
                flag = 1;
            }
        }
        cardErrorType=0;
    }
    if(flag>0)
        return;
#endif
    
#endif

    flag = 0;
    switch(PopKeyEvent())
    {
        case DISPLAY_EVENT_KEYUP:
            LCDSwitchFlag = 1;
            displayType.displayMode = KEY_TURN_DISPLAY_MODE;
            displayType.turnType = 1;
            flag = 1;
            break;
        case DISPLAY_EVENT_KEYDOWN:
            LCDSwitchFlag = 1;
            displayType.displayMode = KEY_TURN_DISPLAY_MODE;
            displayType.turnType = 2;
            flag = 1;
            break;

        case DISPLAY_EVENT_REMOTEOPEN:
            if(LCDSwitchFlag)
            {
                LCDSwitch(0);
                LCDSwitchFlag = 0;
            }
            else
            {
                LCDSwitch(1);
                LCDSwitchFlag = 1;
                InitDisplayControl(1);
            }
            break;
        case DISPLAY_EVENT_KEYPRO:
            displayFlag=1;
            LCDSwitchFlag = 1;
            break;

        case DISPLAY_EVENT_COMMDISPLAY:
            displayType.id =0x02010100;
            displayType.idSerialNumber =0x00;
            GetCommDisplayDI(&displayType);
            displayControl.dispalyObis = 1;
            LCDSwitchFlag = 1;
            flag = 1;
            break;
            
#ifdef CONFIG_METER_REMOTE_INPUT_ENABLE
        case DISPLAY_EVENT_REMOTEPOINT:
            break;
        case DISPLAY_EVENT_REMOTEUP:
            break;
        case DISPLAY_EVENT_REMOTEDOWN:
            break;
        case DISPLAY_EVENT_REMOTETURN:
            break;
        case DISPLAY_EVENT_REMOTETIME:
            break;
#endif            
        case DISPLAY_EVENT_NO:
        default:
            break;
    }
    
    if(flag)
        SpringDifferentDisplayMode(&displayType);
    
}



uchar GetIdSerialNumber1(ST_DISPLAY_CONTROL* controlData)
{
    /*u16 num;
    
    controlData->idSerialNumber[controlData->lcdFigureNum] = ID_STOP_FLAG;
    num = SearchInComDispList(controlData->id[controlData->lcdFigureNum]);  //get display sybmol
    if(num == 0xffff)
    {
        num = SearchInDispList(displayControl.id[controlData->lcdFigureNum],0x00);
        if(num != 0xffff)
        {
            displayControl.idSerialNumber[controlData->lcdFigureNum] = dispList[num].idSerialNumber;
        }
    }*/
    
    ulong startAddr=0;

    if(controlData->displayMode == TAKE_TURN_DISPLAY_MODE)
    {
        startAddr = TAKE_TURN_DISPLAY_LIST_START_ADDR;
    }
    else if(controlData->displayMode == KEY_TURN_DISPLAY_MODE)
    {
        startAddr = KEY_TURN_DISPLAY_LIST_START_ADDR;

        
        // ljc 20100621 start
        #if(CONFIG_METER_AREA_MODE_SICHUAN==CONFIG_METER_AREA_MODE)
        if(DISPLAY_CHANGE_AtoB_STATUS== GAL_YES)
        {
            startAddr = KEY_TURN_DISPLAY_B_LIST_START_ADDR;
        }
        #endif
        // ljc 20100621 end
    }
    
    //startAddr += 4*controlData->currentItem[controlData->displayMode][controlData->lcdFigureNum];
    startAddr += ((ulong)5)*controlData->currentItem[controlData->displayMode][controlData->lcdFigureNum];
    startAddr += 4;
    ReadDataDirect(startAddr,1,&controlData->idSerialNumber[controlData->lcdFigureNum]);

    return(0);
}


uchar GetIdSerialNumber(ST_DISPLAY_CONTROL* controlData)
{
    uchar iFlag;
    ulong errorID;
    memcpy((uchar*)&errorID,ucAlarmStatusLcdError,4);
    iFlag = 0;
    if(errorID!=0)
    {
        iFlag = 1;
    }
    if(controlData->displayMode == KEY_TURN_DISPLAY_MODE)
    {
        iFlag = 0;
    }
    //if((controlData->displayMode != TAKE_TURN_DISPLAY_MODE) ||(errorID==0))
    if(!iFlag)
    {
        GetIdSerialNumber1(controlData);
        
        if(0xffff==SearchInDispList(controlData->id[controlData->lcdFigureNum],controlData->idSerialNumber[controlData->lcdFigureNum] ))
        {
            //displayControl.displayRefalshFlag = 1;
            //displayControl.displayTurnPageFlag = 1;
            //displayControl.currentItem[displayControl.displayMode][0]=0xff;
            //controlData->currentItem[controlData->displayMode][controlData->lcdFigureNum] = 0;
            controlData->currentItem[controlData->displayMode][0] = 0;
            GetDisplayID(controlData);
            GetIdSerialNumber1(controlData);
        }
    }
    
    return(0);
}




/*************************************************************
Function: 获取显示ID
Input:
Output: 
Application area:  
Explain: 
Modification register:
**************************************************************/
uchar GetDisplayID(ST_DISPLAY_CONTROL* controlData)
{
    uchar buf[MEMORY_ONE_LOG_LEN],i,num,errorFlag;
    ulong startAddr=0;
    UN_ULONG_UCHAR id;
    
    if(COMM_DISPLAY_MODE==controlData->displayMode )
    {
        displayControl.dispalyObis = 1;
        return (0);
    }
    errorFlag = 0;
    if((controlData->displayMode == TAKE_TURN_DISPLAY_MODE))
    {
        num = SearchErrorDisplayInformation(&(controlData->id[controlData->lcdFigureNum]), &(controlData->idSerialNumber[controlData->lcdFigureNum]));
        if(num!=0xff)
        {
            errorFlag = 1;
        }
    }

    if(!errorFlag)
    {
        displayControl.dispalyObis = 1;
        if(controlData->displayMode == TAKE_TURN_DISPLAY_MODE)
        {
            startAddr = TAKE_TURN_DISPLAY_LIST_START_ADDR;
        }
        else if(controlData->displayMode == KEY_TURN_DISPLAY_MODE)
        {
            startAddr = KEY_TURN_DISPLAY_LIST_START_ADDR;
            #if(CONFIG_METER_AREA_MODE_SICHUAN==CONFIG_METER_AREA_MODE)
            if(DISPLAY_CHANGE_AtoB_STATUS== GAL_YES)
            {
                startAddr = KEY_TURN_DISPLAY_B_LIST_START_ADDR;
            }
            #endif
        }
        
        startAddr +=((ulong) 5)*controlData->currentItem[controlData->displayMode][controlData->lcdFigureNum];
        ReadDataDirect(startAddr,4,buf);
        for(i=0;i<4;i++)
        {
            id.b[i] = buf[i];
            controlData->screenNoData[controlData->lcdFigureNum][i] = buf[i];
        }
        controlData->id[controlData->lcdFigureNum] = id.l;
        controlData->holdData[0][0]=controlData->currentItem[controlData->displayMode][controlData->lcdFigureNum];
    }
    return(0);
}


/*************************************************************
Function: 查DispList表
Input:
Output: 表号 ，没查到返回0xffff
Application area:  
Explain: 
Modification register:
**************************************************************/
u16 SearchInDispList(ulong id,uchar idSerialNumber)
{
    u16 i,maxNum;//,buf[];
    STR_DISPLAYSYMBOL symbol;
    uchar ucLen, datatype;
    if((id>>24) == 0x00)
    {
        if(SymbolGetECData(&(symbol), id, idSerialNumber, &ucLen, &datatype) == DLT_RET_SUCC)
            return 0;
        else
            return 0xffff;
    }
    else if((id>>24) == 0x01)
    {
        if(SymbolGetMDData(&(symbol), id, idSerialNumber, &ucLen, &datatype) == DLT_RET_SUCC)
            return 0;
        else
            return 0xffff;
    }
    else if((id>>24) == 0x02)
    {
        if(SymbolGetVRData(&(symbol), id, idSerialNumber, &ucLen, &datatype) == DLT_RET_SUCC)
            return 0;
        else
            return 0xffff;
    }
    
    maxNum = GetDispListLens();
    for(i=0;i<maxNum;i++)
    {
        if((dispList[i].id == id)&&(dispList[i].idSerialNumber == idSerialNumber))
            break;
    }
    if(i == maxNum)
        i = 0xffff;
    
    return(i);
}

u16 SearchInDispListCom(ulong id,uchar idSerialNumber)
{
    if((0xFFFFFFFF==id)&&(0xFF==idSerialNumber))return 0;
    return SearchInDispList(id,idSerialNumber);
}

u16 SearchInDispListByObisH(uchar ObisH)
{
    u16 i,maxNum;//,buf[];
    
    maxNum = GetDispListLens();
    for(i=0;i<maxNum;i++)
    {
        //if(dispList[i].obis.b[1] == ObisH)
            break;
    }
    if(i == maxNum)
        i = 0xffff;
    
    return(i);
}


/*************************************************************
Function: 查ComDispList表
Input:
Output: 表号 ，没查到返回0xffff
Application area:  
Explain: 
Modification register:
**************************************************************/
u16 SearchInComDispList(ulong id)
{
    u16 i,maxNum;
    
    maxNum = GetCommDispListLens();
    for(i=0;i<maxNum;i++)
    {
        if(commDispList[i].id == id)
            break;
    }
    if(i == maxNum)
        i = 0xffff;
    
    return(i);
}


u16 SearchInComDispListByObisH(uchar ObisH)
{
    u16 i,maxNum;
    
    maxNum = GetCommDispListLens();
    for(i=0;i<maxNum;i++)
    {
        if(commDispList[i].obis.b[1] == ObisH)
            break;
    }
    if(i == maxNum)
        i = 0xffff;
    
    return(i);
}
ST_DISPLAY_MODE_CHANGE stDisplayComm;
void GetCommDisplayDI(ST_DISPLAY_MODE_CHANGE *stTemp)
{
    memcpy((uchar *)stTemp, (uchar *) &stDisplayComm, sizeof(ST_DISPLAY_MODE_CHANGE));
}
void SetCommDisplayDI(uchar * pData)
{
    ulong ulData;
    memcpy((uchar *) &ulData, pData, 4);
    if(0xffff!=SearchInDispList(ulData,pData[4]))
    {
        stDisplayComm.id = ulData;
        stDisplayComm.idSerialNumber = pData[4];
        stDisplayComm.displayMode = COMM_DISPLAY_MODE;
        SetKeyEvent(DISPLAY_EVENT_COMMDISPLAY);
    }
    else if((0xFFFFFFFF == ulData) && (0xFF == pData[4]))
    {
        //RemoteSetEvent(DISPLAY_EVENT_REMOTEOPEN);
        //SetKeyEvent(DISPLAY_EVENT_REMOTEOPEN);
        extern uchar ucDisplayPrintEnable;
        if(ucDisplayPrintEnable == GAL_YES)
        {
            ucDisplayPrintEnable = GAL_NO;
        }
        else
        {
            ucDisplayPrintEnable = GAL_YES;
        }
    }

}

#if(CONFIG_METER_AREA_MODE_SICHUAN==CONFIG_METER_AREA_MODE)
void KeyDisplayAtoBChange(void)
{
    if(displayBTableItemNum)
    {
        if(DISPLAY_CHANGE_AtoB_STATUS==GAL_NO)
        {
            DISPLAY_CHANGE_AtoB_STATUS=GAL_YES;
            displayATableItemNumTemp=displayControl.itemNum[KEY_TURN_DISPLAY_MODE];
            displayControl.itemNum[KEY_TURN_DISPLAY_MODE]=displayBTableItemNum;
        }
        else
        {
            DISPLAY_CHANGE_AtoB_STATUS=GAL_NO;
            displayControl.itemNum[KEY_TURN_DISPLAY_MODE]=displayATableItemNumTemp;
        }
        displayControl.displayMode = KEY_TURN_DISPLAY_MODE;
        displayControl.currentItem[KEY_TURN_DISPLAY_MODE][0]=0;
        //displayControl.displayTurnPageFlag=1;
        GetDisplayInformation(&displayControl);
        StartTime1s(T1SID_TURN_PAGE_TIMER_NUM,displayControl.turnTime[displayControl.displayMode],TurnPageCallBack);
        displayControl.displayRefalshFlag=1;
    }
}
#endif


