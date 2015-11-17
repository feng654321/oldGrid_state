
#define  AP_COMMPROGRAM_H 
#include "common.h"

void ProgramPointSet(uchar isSet)
{
    if(isSet > 0)
        ucProgramPoint=1;
    else
    ucProgramPoint=0;
    WriteDataDirect(&ucProgramPoint, EPL_PROGRAM_RECORD_STATUS, 1);
}

void EventProgramRecordReset(void)
{
    ProgramPointSet(0);
}

u16 EvenProgramRecord(STR_PROGRAM_RECORD_INDATA CommProgramdata,uchar*Src,u16 Lenth)
{

    ulong ulDataAddrTemp,ulTempId;
    uchar ucNeedComRecord;


#if(CONFIG_METER_PREPAY_MODE == CONFIG_METER_PREPAY_MODE_LOCATION)
    if((CommProgramdata.ID&0xffff0000) == 0x99990000)
    {
        if(cardType  == TYPE_PRESET_CARD)
        {
            CommProgramdata.EvenType = PROGRAM_RECORD_METER_CLR;
        }
    }
#endif


    
    ucNeedComRecord=GAL_NO;
    utlCommUserCode=CommProgramdata.HanderNum;
#if(CONFIG_METER_NO2COMM_MODE_WIRELESS==CONFIG_METER_NO2COMM_MODE)
    if(WIRELESS_MODULE_COMMNO!=GetExplainCommNo())
    {
        ucProgramTime=CON_PROGRAM_TIME_MAX;
    }   
#else
    ucProgramTime=CON_PROGRAM_TIME_MAX;
#endif
    switch(CommProgramdata.EvenType)
    {
        
        case PROGRAM_RECORD_COMMOM:
            ucNeedComRecord=GAL_YES;
            break;
        case PROGRAM_RECORD_METER_CLR:
            ProgramEventPowerClr();
            // RecordClr();
            break;
        case PROGRAM_RECORD_ENERGY_CLR:
            
            break;
        case PROGRAM_RECORD_DEMAND_CLR:
            ProgramEventDemandClr();
            break;
        case PROGRAM_RECORD_EVENT_CLR:
            ProgramEventMeterClrAll(CommProgramdata.ID);
            break;
        case PROGRAM_RECORD_ADJUST_TIME:
            ProgramEventTimeChange(Src);    
            ucNeedComRecord=GAL_YES;
            break;
        case PROGRAM_RECORD_TIMING_SEG:
            ProgramEventDayTableChange();
            ucNeedComRecord=GAL_YES;
            break;
        case PROGRAM_RECORD_TIMING_ZONE:
            ProgramEventSeasonTableChange();
            ucNeedComRecord=GAL_YES;
            break;
        case PROGRAM_RECORD_WEEK_REST:
            ProgramEventResetDayChange();
            ucNeedComRecord=GAL_YES;
            break;
        case PROGRAM_RECORD_HOLIDAY:
            ProgramEventHolidayChange();
            ucNeedComRecord=GAL_YES;
            break;
        case PROGRAM_RECORD_ACTIVE_COM:
            ProgramEventCharacterActiveChange();
            ucNeedComRecord=GAL_YES;
            break;
        case PROGRAM_RECORD_REACTIVE_COM1:
            ProgramEventCharacterActive01Change();
            ucNeedComRecord=GAL_YES;
            break;
        case PROGRAM_RECORD_REACTIVE_COM2:
            ProgramEventCharacterActive02Change();
            ucNeedComRecord=GAL_YES;
            break;
        case PROGRAM_RECORD_BALANCE_DAY:
            ProgramEventBalanceDayChange();
            ucNeedComRecord=GAL_YES;
            break;
        case PROGRAM_RECORD_RELAY_ON:
            ucNeedComRecord=GAL_NO;
            break;
        case PROGRAM_RECORD_RELAY_OFF:
            ucNeedComRecord=GAL_NO;
            break;
        default:
            ucNeedComRecord=GAL_NO;
            break;
    }

    
#if 1

    if(GAL_YES==ucNeedComRecord)
    {
        ulTempId=CommProgramdata.ID;
        if(0==ucProgramPoint)
        {
            ulDataAddrTemp=SetTwoTableNextPoint(TYPE_PROGRAM_RECORD);
            if(GAL_GETTWOTABLE_ADDRERR != ulDataAddrTemp)
            {
                SetTimeDataToPoint(&Wr_data[0]);
                memcpy(&Wr_data[6], (uchar *) &utlCommUserCode, 4);
                memcpy(&Wr_data[10], (uchar *) &ulTempId, 4);
                memset(&Wr_data[14], 0xFF, 36);
                WriteDataDirect(&Wr_data[0], ulDataAddrTemp, 50);
                Data3ByteBCDAdd1(EPL_PROGRAM_COUNT);
                ProgramPointSet(1);
            }
            ClrFlashMode();
        }
        else
        { 
            ulDataAddrTemp=GetTwoTableAddrFromBlock(TYPE_PROGRAM_RECORD,0,10);
            if(GAL_GETTWOTABLE_ADDRERR != ulDataAddrTemp)
            {
/*              
                ReadDataDirect(ulDataAddrTemp+10, 36, &Wr_data[14]);
                SetTimeDataToPoint(&Wr_data[0]);
                memcpy(&Wr_data[6], (uchar *) &utlCommUserCode, 4);
                memcpy(&Wr_data[10], (uchar *) &ulTempId, 4);
                WriteDataDirect(&Wr_data[0], ulDataAddrTemp, 50);
*/
                ReadDataDirect(ulDataAddrTemp, 36, &Wr_data[4]);
                memcpy(&Wr_data[0], (uchar *) &ulTempId, 4);
                WriteDataDirect(&Wr_data[0], ulDataAddrTemp, 40);

            }
        }
        ProgramPointSet(1);
    }
#endif

    return 0;
    
    
    
}

#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
#if 1
void CardProgramRecord(CARD_PROGRAM_RECORD_STRUCT* dataDI)
{
    uchar buf[10],i;
    ulong ultemp=0;
    STR_PROGRAM_RECORD_INDATA CommProgramdata;
    
    memset((uchar*)&CommProgramdata,0,sizeof(STR_PROGRAM_RECORD_INDATA));
    if(dataDI->keyheadcode == 0x0000)
    {
        dataDI->keyheadcode = 0x9998;
    }
    memcpy((uchar*)&ultemp,dataDI,4);
    CommProgramdata.ID = ultemp;
    //memcpy((uchar*)&CommProgramdata.handlerID,(dataDI+4),4);
    for(i=0;i<4;i++)
    {
        buf[i] = dataDI->cardNum4[3-i];
    }
    memcpy((uchar*)&ultemp,buf,4);
    CommProgramdata.HanderNum = ultemp;
    CommProgramdata.EvenType= PROGRAM_RECORD_COMMOM;
    EventProgramRecordReset();
    EvenProgramRecord(CommProgramdata,buf,0);
    EventProgramRecordReset();
}

#else

void CardProgramRecord(CARD_PROGRAM_RECORD_STRUCT* dataDI)
{
    uchar i;
    ulong ulTempAddr;

    if(0x0000==dataDI->keyheadcode)
    {
        dataDI->keyheadcode=0x9998;
    }
    ulTempAddr=SetTwoTableNextPoint(TYPE_PROGRAM_RECORD);
    if(GAL_GETTWOTABLE_ADDRERR != ulTempAddr)
    {
        SetTimeDataToPoint(&Wr_data[0]);
        Wr_data[6]=dataDI->paraUpdateSign;
        Wr_data[7]=dataDI->cardordercode;
        Wr_data[8]=dataDI->keyheadcode%256;
        Wr_data[9]=dataDI->keyheadcode/256;
        Wr_data[10]=dataDI->cardNum4[3];
        Wr_data[11]=dataDI->cardNum4[2];
        Wr_data[12]=dataDI->cardNum4[1];
        Wr_data[13]=dataDI->cardNum4[0];
        for(i=4;i<40;i++)
        {
            Wr_data[10+i]=0xff;
        }
        WriteDataDirect(&Wr_data[0], ulTempAddr, 50);
        Data3ByteBCDAdd1(EPL_PROGRAM_COUNT);
        EventProgramRecordReset();
    }
    ClrFlashMode();
}
#endif

void SpringStartTotalCommRecord(uchar type)
{
    if(!type)
    {
        if(0==Certification)
        {
            EventProgramRecordReset();
        }
    }
    else
    {
        if(0==ucProgramTime)
        {
            if(0==Certification)
            {
                EventProgramRecordReset();
            }
        }
    }
    
}


#endif



