#ifdef __AP_COMMDATA_C__

#define AP_COMMDATA_GLOBALS
#include "common.h"


#define CONST_COMM64597_LENGTH 78












STR_COMMUNICATA_FLAG unTempFlg;
uchar GetCommDataFromComm(void)
{
    STR_COMMUNICATE_BUFF communicateData;

    if(!GetCommunicateRecData(&communicateData))
    {
        //memcpy(&CommSys.DataBuffer.ucArray_Comm[0],&communicateData.buff[0],communicateData.lens);
        memcpy(&CommSys[0].DataBuffer.ucArray_Comm[0],&communicateData.buff[0],sizeof(communicateData.buff));
        unTempFlg=communicateData.communicateFlag;
        CommSys[0].status_Addr_info=Comm_Addr_START;
        CommSys[0].status=Comm_Status_REC;
        CommSys[0].DataPoint.Rbytes.ucReceiveDataLength=communicateData.lens;
        return 1;
    }
    return 0;
}

void  SendDataToComm(uchar ucLen)
{
    
    SendCommunicateData(&CommSys[0].DataBuffer.ucArray_Comm[0],ucLen,&unTempFlg);
}


void Comm_SendData( void )
{
//  (*CommDataPoint).DataPoint.Tbytes.ucTransDataLength=len;
    (*CommDataPoint).DataPoint.Tbytes.ucTransDataPoint=0;
    (*CommDataPoint).status=Comm_Status_SEND;
    (*CommDataPoint).comm_send_delay=CONST_TIMER_SEND_DELAY;
    (*CommDataPoint).status_Addr_info=Comm_Addr_START;
    SendDataToComm((*CommDataPoint).DataPoint.Tbytes.ucTransDataLength);
    
}


/******************************************************************************
Function:void WriteIRBuffer(uchar p)
Description:填写发送缓冲区
Input:mode:通道
Output:
Return:无
Application area:通讯
Modification register:暂无。
*******************************************************************************/
void WriteIRBuffer(uchar p)
{
    uchar i;
    uchar cuLen;
    // RecordWriteProgram();
    cuLen= (*CommDataPoint).DataPoint.Tbytes.ucTransDataLength - 2;
    (*CommDataPoint).DataBuffer.ucArray_Comm[0] = 0x68;
    // ReadMemory(&(*CommDataPoint).DataBuffer.ucArray_Comm[1],  METER_PARA_HEAD, METER_ADDRESS, 0x06);
    for(i=0;i<6;i++)
    {
        (*CommDataPoint).DataBuffer.ucArray_Comm[1+i]=RAM[RAM_USER_COMM_ADDR+i];
    }
    for ( i = 10; i <cuLen; i++)
    {
        (*CommDataPoint).DataBuffer.ucArray_Comm[i] += 0x33;
    }
    (*CommDataPoint).DataPoint.Tbytes.ucTransDataPoint = 00;
    (*CommDataPoint).DataBuffer.ucArray_Comm[cuLen] = CommCalChksum(&(*CommDataPoint).DataBuffer.ucArray_Comm[0], cuLen);
    (*CommDataPoint).DataBuffer.ucArray_Comm[cuLen + 1] = 0x16;
#if(CONST_COMM_SEND_LEADER_FE_NUM != CONST_COMM_SEND_LEADER_FE_NUM_0)
    cuLen=cuLen+2;
    #if(CONST_COMM_SEND_LEADER_FE_NUM == CONST_COMM_SEND_LEADER_FE_NUM_4)
        {
        for(i=cuLen;i>0;i--)
            {
            (*CommDataPoint).DataBuffer.ucArray_Comm[i+3]=(*CommDataPoint).DataBuffer.ucArray_Comm[i-1];
            }
        (*CommDataPoint).DataBuffer.ucArray_Comm[0]=0xfe;
        (*CommDataPoint).DataBuffer.ucArray_Comm[1]=0xfe;
        (*CommDataPoint).DataBuffer.ucArray_Comm[2]=0xfe;
        (*CommDataPoint).DataBuffer.ucArray_Comm[3]=0xfe;
        (*CommDataPoint).DataPoint.Tbytes.ucTransDataLength +=CONST_COMM_SEND_LEADER_FE_NUM;
        }
    #endif
    #if(CONST_COMM_SEND_LEADER_FE_NUM == CONST_COMM_SEND_LEADER_FE_NUM_3)
        {
        for(i=cuLen;i>0;i--)
            {
            (*CommDataPoint).DataBuffer.ucArray_Comm[i+2]=(*CommDataPoint).DataBuffer.ucArray_Comm[i-1];
            }
        (*CommDataPoint).DataBuffer.ucArray_Comm[0]=0xfe;
        (*CommDataPoint).DataBuffer.ucArray_Comm[1]=0xfe;
        (*CommDataPoint).DataBuffer.ucArray_Comm[2]=0xfe;
        (*CommDataPoint).DataPoint.Tbytes.ucTransDataLength +=CONST_COMM_SEND_LEADER_FE_NUM;
        }
    #endif
    #if(CONST_COMM_SEND_LEADER_FE_NUM == CONST_COMM_SEND_LEADER_FE_NUM_2)
        {
        for(i=cuLen;i>0;i--)
            {
            (*CommDataPoint).DataBuffer.ucArray_Comm[i+1]=(*CommDataPoint).DataBuffer.ucArray_Comm[i-1];
            }
        (*CommDataPoint).DataBuffer.ucArray_Comm[0]=0xfe;
        (*CommDataPoint).DataBuffer.ucArray_Comm[1]=0xfe;
        (*CommDataPoint).DataPoint.Tbytes.ucTransDataLength +=CONST_COMM_SEND_LEADER_FE_NUM;
        }
    #endif
    #if(CONST_COMM_SEND_LEADER_FE_NUM == CONST_COMM_SEND_LEADER_FE_NUM_1)
        {
        for(i=cuLen;i>0;i--)
            {
            (*CommDataPoint).DataBuffer.ucArray_Comm[i+0]=(*CommDataPoint).DataBuffer.ucArray_Comm[i-1];
            }
        (*CommDataPoint).DataBuffer.ucArray_Comm[0]=0xfe;
        (*CommDataPoint).DataPoint.Tbytes.ucTransDataLength +=CONST_COMM_SEND_LEADER_FE_NUM;
        }
    #endif
#endif
    Comm_SendData();
}




































































/******************************************************************************
Function:void CheckPassword(uchar *PT_point)
Description密码校验
Input:mode:通道
Output:
Return:无
Application area:除总清零外的其它设置命令
Modification register:暂无。
*******************************************************************************/
void CheckPassword(uchar *PT_point)
{
    // uchar i;
    // uchar ucArray_Tmp[3];
    // uchar ucPassL;
    PROTOCOL_ERR_FLAG.bit.b_pwd_error =0;
}




/******************************************************************************
Function:void CommCheckAddress(void)
Description表地址校验
Input:mode:通道
Output:
Return:无
Application area:
Modification register:暂无。
*******************************************************************************/
void CommCheckAddress( void )
{
    uchar i;
    uchar ucRet;
//  uchar ucArray_Address[6];
    ucRet = 1;
    for ( i = 0; i < 6; i++)
        {
        if (0xaa != (*CommDataPoint).DataBuffer.DL645Data.ucAddress[i])
            {
            ucRet = 0;
            break;
            }
        }
    if( 1 == ucRet)
        {
        (*CommDataPoint).status_Addr_info=Comm_Addr_Supper;
        return;
        }
    else
        {
        ucRet = 1;
        for ( i = 0; i <6; i++)
            {
            if (0x99 != (*CommDataPoint).DataBuffer.DL645Data.ucAddress[i])
                {
                ucRet = 0;
                break;
                }
            }
        if( 1 == ucRet)
            {
            (*CommDataPoint).status_Addr_info=Comm_Addr_BroadCast;
            return;
            }
        else
            {
            ucRet = 1;
            // ReadMemory(ucArray_Address,  METER_PARA_HEAD, METER_ADDRESS, 0x06);
            for ( i = 0; i < 6 ; i++)
                {
                if (RAM[RAM_USER_COMM_ADDR+i]  != (*CommDataPoint).DataBuffer.DL645Data.ucAddress[i])
                    {
                    ucRet = 0;
                    break;
                    }
                }
            if( 1 == ucRet)
                {
                (*CommDataPoint).status_Addr_info=Comm_Addr_ME;
                return;
                }
            else
                {
                ucRet = 1;
                for ( ; i < 6; i ++)
                    {
                    if (0xaa !=  (*CommDataPoint).DataBuffer.DL645Data.ucAddress[i])
                        {
                        ucRet = 0;
                        break;
                        }
                    }
                if( 1 == ucRet)
                    {
                    (*CommDataPoint).status_Addr_info=Comm_Addr_AutoAddr;
                    return;
                    }
                }
            }
        }
}

uchar WriteTimeStand(uchar *ucTime)
{
    STR_DATE_TIME TempTime;
    TempTime.week=*(ucTime+0);
    TempTime.day=*(ucTime+1);
    TempTime.month=*(ucTime+2);
    TempTime.year=*(ucTime+3);
    TempTime.second=*(ucTime+4);
    TempTime.minute=*(ucTime+5);
    TempTime.hour=*(ucTime+6);
    if(1==SetRealTime(&TempTime))
        return 0;
    return 1;
}
        
uchar ReadDL64507_11_00_kWhData(ulong ulCode_in,uchar *ucpDataout)
{
    TYPE_LONG_INT_CHAR_UNION ulCode07;
    uchar ucReturnLen;
    uchar ucTemp,ucPoint;
    uchar *PT_Point;
    u16 ciAddrM,ciAddrL,ciPointAddr,Ptr=0;
    ulCode07.uLongMode=ulCode_in;
    ucTemp=0;
    ucReturnLen=0;
    if(ulCode07.uCharMode.ucD2<0x0a)
        {
        if((0x00==ulCode07.uCharMode.ucD1)) //||(0xff==ulCode07.uCharMode.ucD1))
            {
            if((ulCode07.uCharMode.ucD0<0x0d))
                {
                ucTemp=1;
                }
            }
        }
    ucReturnLen=0;
    if(1==ucTemp)
        {

        if(0==ulCode07.uCharMode.ucD0)
            {
            
            ciAddrM=ulCode07.uCharMode.ucD2;
            ciAddrM=ciAddrM*15*5+1;
            ciAddrM=ciAddrM+ulCode07.uCharMode.ucD1*5;
            ReadDataDirect(ciAddrM,  4, ucpDataout);
            return 4;
            }
            
        }
    return ucReturnLen;
}

uchar ReadHL645KZ_FE00_Data(void)
{
    uchar utstory,uDatalen;
    ulong uAddr;
    utstory=(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.Type_OC_Read.ucStoryType;
    uDatalen=(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.Type_OC_Read.ucDatalen;
    uAddr=utstory;
    uAddr=uAddr*256+(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.Type_OC_Read.ucAddrHigh;
    uAddr=uAddr*256+(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.Type_OC_Read.ucAddrM;
    uAddr=uAddr*256+(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.Type_OC_Read.ucAddrLow;
    if(1==ReadDataDirect(uAddr,  uDatalen, &((*CommDataPoint).DataBuffer.DL645Data.ucDataPart.Type_OC_Read.ucStoryType)))
    {
        return (uDatalen);
    }
    return 0;
}
uchar WriteHL645KZ_FE00_Data(void)
{
    uchar utstory,uDatalen;
    ulong uAddr;
    utstory=(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.Type_OC_Write.ucStoryType;
    uDatalen=(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.Type_OC_Write.ucDatalen;
    uAddr=utstory;
    uAddr=uAddr*256+(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.Type_OC_Write.ucAddrHigh;
    uAddr=uAddr*256+(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.Type_OC_Write.ucAddrM;
    uAddr=uAddr*256+(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.Type_OC_Write.ucAddrLow;
    if(1==WriteDataDirect(&((*CommDataPoint).DataBuffer.DL645Data.ucDataPart.Type_OC_Write.ucWriteData[0]),uAddr,  uDatalen))
    {
        return 1;
    }
    return 0;
}
uchar ReadHL645ADE7758_BE02_Data(void)
{
    uchar uDatalen;
    u16 uAddr;
    uDatalen=(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.Type_ADE7758_READ.ucDatalen;
    uAddr=(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.Type_ADE7758_READ.ucAddr;
    if(1==ReadADE7758(uAddr,uDatalen, &((*CommDataPoint).DataBuffer.DL645Data.ucDataPart.Type_ADE7758_READ.ucReadData[0])))
    {
        return (uDatalen+4);
    }
    return 0;
}
uchar WriteHL645ADE7758_BE02_Data(void)
{
    uchar uDatalen;
    ulong uAddr;
    uDatalen=(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.Type_ADE7758_Write.ucDatalen;
    uAddr=(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.Type_ADE7758_Write.ucAddr;
    if(1==WriteADE7758ResumeData(uAddr,uDatalen,&((*CommDataPoint).DataBuffer.DL645Data.ucDataPart.Type_ADE7758_Write.ucWriteData[0])))
    {
        return 1;
    }
    return 0;
}


uchar ReadDL64507_11_Data(ulong ulCode_in,uchar *ucpDataout)
{
    TYPE_LONG_INT_CHAR_UNION ulCode07;
    uchar ucTemp;
    ulong ulId;
    uchar ucPoint;
    
    ulCode07.uLongMode=ulCode_in;
    // kwh data
    if(0x00==ulCode07.uCharMode.ucD3)
        {
//      ucPoint=Read64507_kwh();
        ucPoint=ReadDL64507_11_00_kWhData(ulCode07.uLongMode,ucpDataout);
        if(0!=ucPoint)
            {
            return ucPoint;
            }
        }

    return 0;
}



/*
void RecordWriteProgram(void)
{
    uchar ucTemp;
    uchar Temp[32];
    u16 Ptr=0;
    
    ucTemp=(*CommDataPoint).DataBuffer.DL645Data.ucControl;
    if(0x40!=(0x40&ucTemp))
    //--正确应答时记录数据 -->
        {
        ucTemp=ucTemp&0x1f;
        if((0x04==ucTemp)||(0x14==ucTemp)||(0x18==ucTemp)
            ||(0x19==ucTemp)||(0x1a==ucTemp)||(0x1b==ucTemp)
            ||(0x1c==ucTemp))
            {
            //RecordWriteProgram_count();
            if(ucRecordWriteProgram_point<10)
                {
                if(0==ucRecordWriteProgram_point)
                    {
                    ReadMemory((uchar*)&Ptr,SYSTEM_PARA_HEAD,HISTORY_PROGAM_EVENT_PTR,1);
                    Ptr++;
                    if ( Ptr >= PROGRAM_EVENT_NUMBER )Ptr = 0;
                    WriteMemoryDouble( SYSTEM_PARA_HEAD ,HISTORY_PROGAM_EVENT_PTR ,(uchar*)&Ptr,1);
                    for(ucTemp=0;ucTemp<32;ucTemp++)
                        Temp[ucTemp]=0xff;
                    memcpy( (uchar*)&Temp[0],(uchar*)&eventClock.second, 6 );
                    memcpy( (uchar*)&Temp[6],(uchar*)&uuRecordWriteProgram_user.uLongMode, 4 );
                    memcpy( (uchar*)&Temp[10],(uchar*)&uuRecordWriteProgram_code.uLongMode, 4 );
                    
                    Ptr=Ptr*50+PROGRAM_EVENT_CLOCK_1;
                    WriteMemory( PROGRAM_EVENT_HEAD, Ptr,(uchar*)&Temp[0],30);
                    for(ucTemp=0;ucTemp<32;ucTemp++)
                        Temp[ucTemp]=0xff;
                    Ptr=Ptr+30;
                    WriteMemory( PROGRAM_EVENT_HEAD, Ptr,(uchar*)&Temp[0],20);
                    }
                else
                    {
                    ReadMemory((uchar*)&Ptr,SYSTEM_PARA_HEAD,HISTORY_PROGAM_EVENT_PTR,1);
                    Ptr=Ptr*50+PROGRAM_EVENT_CLOCK_1+10+ucRecordWriteProgram_point*4;
                    memcpy( (uchar*)&Temp[0],(uchar*)&uuRecordWriteProgram_code.uLongMode, 4 );
                    WriteMemory( PROGRAM_EVENT_HEAD, Ptr,(uchar*)&Temp[0],4);
                    }
                ucRecordWriteProgram_point++;
                }
            }
        
        }
    
}


void RecordWriteProgram_setcodeuser()
{
    uchar ucTemp;
    switch((*CommDataPoint).DataBuffer.DL645Data.ucControl)
        {
        case 0x04:
            uuRecordWriteProgram_code.uLongMode=0xffff0000+(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.uICode97;;
            uuRecordWriteProgram_user.uLongMode=0xffffffff;
            break;
        case 0x14:
            uuRecordWriteProgram_code.uLongMode=(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.uLCode07;
            uuRecordWriteProgram_user.uLongMode=(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.Type_Control14.ulUser;
            break;
        case 0x18:
            uuRecordWriteProgram_code.uLongMode=(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.uLCode07;
            uuRecordWriteProgram_user.uLongMode=0xffffffff;
            break;
        case 0x19:
        case 0x1a:
        case 0x1b:
        case 0x1c:
            uuRecordWriteProgram_code.uLongMode=0xffffff00+(*CommDataPoint).DataBuffer.DL645Data.ucControl;
            uuRecordWriteProgram_user.uLongMode=(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.Type_Control1A.ulUser;
        default:
            break;
        }
}


*/


/******************************************************************************
void ExplainProtocol(uchar p)
Description:解析通讯帧
Input:mode:通道
Output:
Return:
Application area:
Modification register:暂无。
*******************************************************************************/
void ExplainProtocol(uchar  p)
{
    uchar ucIndex;
    uchar ucFreeze,ucTemp;
    u16 ciDelayControl;
    uchar ucDataLen;
    // RecordWriteProgram_setcodeuser();
    switch ((*CommDataPoint).DataBuffer.DL645Data.ucControl)
    {
        //读操作
        case 0x01:
            
                PROTOCOL_ERR_FLAG.bit.b_other_error = 1;
            ucDataLen=0;
            if (PROTOCOL_ERR_FLAG.ucErrorFlag)
                {
                (*CommDataPoint).DataBuffer.DL645Data.ucControl = 0xc1;
                (*CommDataPoint).DataBuffer.DL645Data.ucLength= 0x01;
                (*CommDataPoint).DataBuffer.ucArray_Comm[10] = PROTOCOL_ERR_FLAG.ucErrorFlag;
                (*CommDataPoint).DataPoint.Tbytes.ucTransDataLength = 13;
                }
            else
                {
                (*CommDataPoint).DataBuffer.DL645Data.ucControl = 0x81;
                (*CommDataPoint).DataBuffer.DL645Data.ucLength = ucDataLen + 2;
                (*CommDataPoint).DataPoint.Tbytes.ucTransDataLength = ucDataLen + 2 + 12;
                }
            WriteIRBuffer(p);
            break;
        //写操作
        case 0x04:
            if(0xc01f==(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.uICode97)
            {
                WriteTimeStand(&(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.ucArray_Data[6]);
            }
            else
            {
                PROTOCOL_ERR_FLAG.bit.b_other_error = 1;
            }
                
            if (PROTOCOL_ERR_FLAG.ucErrorFlag)
                {
                (*CommDataPoint).DataBuffer.DL645Data.ucControl = 0xc4;
                (*CommDataPoint).DataBuffer.DL645Data.ucLength= 0x01;
                (*CommDataPoint).DataBuffer.ucArray_Comm[10] = PROTOCOL_ERR_FLAG.ucErrorFlag;
                (*CommDataPoint).DataPoint.Tbytes.ucTransDataLength = 13;
                }
            else
                {   
                (*CommDataPoint).DataBuffer.DL645Data.ucControl = 0x84;
                (*CommDataPoint).DataBuffer.DL645Data.ucLength= 0x00;
                (*CommDataPoint).DataPoint.Tbytes.ucTransDataLength = 12;

                }
            WriteIRBuffer(p);
            break;
        case 0x05:
            if(0xfe00==(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.uICode97)
            {
                if(1!=WriteHL645KZ_FE00_Data())
                {
                    PROTOCOL_ERR_FLAG.bit.b_other_error = 1;
                }
                else
                {
                (*CommDataPoint).DataBuffer.DL645Data.ucControl = 0x85;
                (*CommDataPoint).DataBuffer.DL645Data.ucLength= 0x00;
                (*CommDataPoint).DataPoint.Tbytes.ucTransDataLength = 12;

                }
            }
            else 
            {
                if(0xBE02==(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.uICode97)
                {
                    if(1!=WriteHL645ADE7758_BE02_Data())
                    {
                        PROTOCOL_ERR_FLAG.bit.b_other_error = 1;
                    }
                    else
                    {
                    (*CommDataPoint).DataBuffer.DL645Data.ucControl = 0x85;
                    (*CommDataPoint).DataBuffer.DL645Data.ucLength= 0x03;
                    (*CommDataPoint).DataPoint.Tbytes.ucTransDataLength = 12+3;
                    (*CommDataPoint).DataBuffer.DL645Data.ucDataPart.Type_ADE7758_READ.ucAddr=(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.Type_ADE7758_Write.ucAddr;
                        
                    }
                }
                else 
                {
                    if((0xBD00==(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.uICode97)
                        ||(0xBD01==(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.uICode97)
                        ||(0xBD03==(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.uICode97))
                    {
                        KwhAllDataClr();
                    }
                    else
                    {
                        PROTOCOL_ERR_FLAG.bit.b_other_error = 1;
                    }
                }
            }
                
            if (PROTOCOL_ERR_FLAG.ucErrorFlag)
                {
                (*CommDataPoint).DataBuffer.DL645Data.ucControl = 0xc5;
                (*CommDataPoint).DataBuffer.DL645Data.ucLength= 0x01;
                (*CommDataPoint).DataBuffer.ucArray_Comm[10] = PROTOCOL_ERR_FLAG.ucErrorFlag;
                (*CommDataPoint).DataPoint.Tbytes.ucTransDataLength = 13;
                }
            WriteIRBuffer(p);
            break;
            

        case 0x06:
            if(0xfe00==(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.uICode97)
            {
                ucDataLen=ReadHL645KZ_FE00_Data();
            }
            else 
            {
                if(0xbe02==(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.uICode97)
                {
                    ucDataLen=ReadHL645ADE7758_BE02_Data();
                }
                else
                {
                    PROTOCOL_ERR_FLAG.bit.b_other_error = 1;
                }
            }
            if (PROTOCOL_ERR_FLAG.ucErrorFlag)
                {
                (*CommDataPoint).DataBuffer.DL645Data.ucControl = 0xc6;
                (*CommDataPoint).DataBuffer.DL645Data.ucLength= 0x01;
                (*CommDataPoint).DataBuffer.ucArray_Comm[10] = PROTOCOL_ERR_FLAG.ucErrorFlag;
                (*CommDataPoint).DataPoint.Tbytes.ucTransDataLength = 13;
                }
            else
                {
                (*CommDataPoint).DataBuffer.DL645Data.ucControl = 0x86;
                (*CommDataPoint).DataBuffer.DL645Data.ucLength = ucDataLen + 2;
                (*CommDataPoint).DataPoint.Tbytes.ucTransDataLength = ucDataLen + 2 + 12;
                }
            WriteIRBuffer(p);
            break;
        case 0x08:
            // 645-07 广播校时
            // BroadCastTime();
            ///InitialSerialPort(p);
            break;
        case 0x11:
            // 645-07 READ command
            if( 0x04 == (*CommDataPoint).DataBuffer.DL645Data.ucLength )
                {
                ucDataLen = ReadDL64507_11_Data((*CommDataPoint).DataBuffer.DL645Data.ucDataPart.uLCode07,
            (uchar*)&(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.ucArray_Data[4]);
                if(0 == ucDataLen)
                    {
                    PROTOCOL_ERR_FLAG.bit.b_nodata_error = 1;
                    }
                }
            else
                {
                PROTOCOL_ERR_FLAG.bit.b_other_error = 1;
                }
            
            if (PROTOCOL_ERR_FLAG.ucErrorFlag)
                {
                (*CommDataPoint).DataBuffer.DL645Data.ucControl = 0xd1;
                (*CommDataPoint).DataBuffer.DL645Data.ucLength= 0x01;
                (*CommDataPoint).DataBuffer.ucArray_Comm[10] = PROTOCOL_ERR_FLAG.ucErrorFlag;
                (*CommDataPoint).DataPoint.Tbytes.ucTransDataLength = 13;
                }
            else
                {
                (*CommDataPoint).DataBuffer.DL645Data.ucControl = 0x91;
                (*CommDataPoint).DataBuffer.DL645Data.ucLength= ucDataLen+4;
                (*CommDataPoint).DataPoint.Tbytes.ucTransDataLength = ucDataLen + 4 + 12;
                }
            
            WriteIRBuffer(p);
            break;
        case 0x14:
            // 645-07 WRITE command
            if( 0x04 == (*CommDataPoint).DataBuffer.DL645Data.ucLength )
                {
                ucDataLen = ReadDL64507_11_Data((*CommDataPoint).DataBuffer.DL645Data.ucDataPart.uLCode07,
            (uchar*)&(*CommDataPoint).DataBuffer.DL645Data.ucDataPart.ucArray_Data[4]);
                if(0 == ucDataLen)
                    {
                    PROTOCOL_ERR_FLAG.bit.b_nodata_error = 1;
                    }
                }
            else
                {
                PROTOCOL_ERR_FLAG.bit.b_other_error = 1;
                }
            
            if (PROTOCOL_ERR_FLAG.ucErrorFlag)
                {
                (*CommDataPoint).DataBuffer.DL645Data.ucControl = 0xd1;
                (*CommDataPoint).DataBuffer.DL645Data.ucLength= 0x01;
                (*CommDataPoint).DataBuffer.ucArray_Comm[10] = PROTOCOL_ERR_FLAG.ucErrorFlag;
                (*CommDataPoint).DataPoint.Tbytes.ucTransDataLength = 13;
                }
            else
                {
                (*CommDataPoint).DataBuffer.DL645Data.ucControl = 0x91;
                (*CommDataPoint).DataBuffer.DL645Data.ucLength= ucDataLen+4;
                (*CommDataPoint).DataPoint.Tbytes.ucTransDataLength = ucDataLen + 4 + 12;
                }
            
            WriteIRBuffer(p);
            
            break;
        case 0x19:
            // 645-07 最大需量清零
            if( 0x08 == (*CommDataPoint).DataBuffer.DL645Data.ucLength )
            {
                DemandDataClrAllCurrent();
            }           
            else
            {
                PROTOCOL_ERR_FLAG.bit.b_other_error = 1;
            }
            if (PROTOCOL_ERR_FLAG.ucErrorFlag)
            {
                (*CommDataPoint).DataBuffer.DL645Data.ucControl = 0xd9;
                (*CommDataPoint).DataBuffer.DL645Data.ucLength= 0x01;
                (*CommDataPoint).DataBuffer.ucArray_Comm[10] = PROTOCOL_ERR_FLAG.ucErrorFlag;
                (*CommDataPoint).DataPoint.Tbytes.ucTransDataLength = 13;
            }
            else
            {
                (*CommDataPoint).DataBuffer.DL645Data.ucControl = 0x99;
                (*CommDataPoint).DataBuffer.DL645Data.ucLength= 0+4;
                (*CommDataPoint).DataPoint.Tbytes.ucTransDataLength = 0 + 4 + 12;
            }
            
            WriteIRBuffer(p);
            break;
        default:
            break;
    }
}























void DecodeProtocol(uchar uctChannelsId)
{
    uchar ucTemp,ucTData,uctReclen,uctDatalen;

    ucCommChannelsId=uctChannelsId;
    CommDataPoint=&(CommSys[ucCommChannelsId]);

    PROTOCOL_ERR_FLAG.ucErrorFlag=0;


    uctReclen=(*CommDataPoint).DataPoint.Rbytes.ucReceiveDataLength;
    uctReclen=(*CommDataPoint).DataPoint.Rbytes.ucReceiveDataLength;
    //  uctReclen=CommDataPoint->DataPoint->Rbytes->ucReceiveDataLenth;
    // Check Addr 
    if(uctReclen>8)
    {
        // 如果还没有判断过通讯地址
        if(Comm_Addr_START==(*CommDataPoint).status_Addr_info)
        {
            if((0x68==(*CommDataPoint).DataBuffer.DL645Data.ucFirstHead)
            &&(0x68==(*CommDataPoint).DataBuffer.DL645Data.ucSecondHead))
            {
                CommCheckAddress();
            }
        }
        // -->如果不是针对本表操作，则自动复位串口-->
        if(Comm_Addr_START==(*CommDataPoint).status_Addr_info)
        {
            (*CommDataPoint).status=Comm_Status_ERR;
        //ResetCommConfig(uctChannelsId);
        }
    }
    // -->针对本表操作---->
    if(Comm_Addr_START != (*CommDataPoint).status_Addr_info)
    {
        CommTimeShow=CON_COMMTIMESHOW_MAX;
        
        if(uctReclen >= CONST_COMM_OTHERDATA_LEN)
        {
            uctDatalen=(*CommDataPoint).DataBuffer.DL645Data.ucLength;
            // --> 数据超限判断 -->
            if(uctDatalen>=CONST_COMM_DATA_MAX_LEN)
            {
            // -->数据错误，请求重新初始化通讯  -->
                (*CommDataPoint).status=Comm_Status_ERR;
            }
            // ---->数据接收足够 -->
            if(uctReclen>=uctDatalen+CONST_COMM_OTHERDATA_LEN)
            {
                ucTemp=1;
//              if((*CommDataPoint).DataBuffer.DL645Data.ucDataPart.ucArray_Data[uctDatalen] != CommCalChksum(&(*CommDataPoint).DataBuffer.ucArray_Comm[0],uctDatalen+10))
//              {
//                  ucTemp=0;
//              }
//              if(0x16 != (*CommDataPoint).DataBuffer.ucArray_Comm[uctDatalen+10+1])
//              {
//                  ucTemp=0;
//              }
//              // -->数据错误，请求重新初始化通讯  -->
//              (*CommDataPoint).status=Comm_Status_ERR;
//              if(0x80&((*CommDataPoint).DataBuffer.DL645Data.ucControl))
//              {
//                  ucTemp=0;
//              }
                if(1==ucTemp)
                {
                    // --> 命令帧格式正确 -->
                    // -->液晶屏通讯符号闪烁-->
//                  BlinkLcd(ICON_LCD_K2,2);
//                  comLedTurnOnTime = 10;
//                  for(ucTemp=0;ucTemp<uctDatalen;ucTemp++)
//                  {
//                      (*CommDataPoint).DataBuffer.DL645Data.ucDataPart.ucArray_Data[ucTemp] -= 0x33;
//                  }
                    ExplainProtocol(uctChannelsId);
                }

            }

        }
    }
}


void CommMode(void)
{
    if(1==GetCommDataFromComm())
    {
        DecodeProtocol(0);
    }
}



#endif

