/*********************************************************************************
    �汾��     :version 0.1
    ģ����       : Զ�̿���ģ��
    �ļ���       : CommExpWrite.c
    ����ļ�     : 
    �ļ�ʵ�ֹ��� : ͨ��д����ģ��
    ����         : Ҧ����
    �汾         : 0.1
----------------------------------------------------------------------------------------------------------------------
    ��ע         : <����˵��>
---------------------------------------------------------------------------------------------------------------------
    �޸ļ�¼ : 
    �� ��        �汾     �޸���              �޸�����
    YYYY/MM/DD   X.Ymai      <���߻��޸�����>    <�޸�����>
    YYYY/MM/DD   X.Y      <���߻��޸�����>    <�޸�����>
==================================================================== 
����˵���� 
*******************************************************************************/
#include "common.h"

uchar CheckBcd(uchar *pucBuf, uchar ucLength);



/////////////////////////�α������ݵ���Ч�Լ��////////////////////////////
/******************************************************************************
Function:uchar CheckBcd(uchar *pucBuf, uchar ucLength)
Description:���BCD�����Ƿ�Ϸ�
Input:mode:�����׵�ַ������
Output:
Return:1�Ϸ�0�Ƿ�
Application area:
Modification register:���ޡ�
*******************************************************************************/
uchar CheckBcd(uchar *pucBuf, uchar ucLength)
{
    uchar i;
    uchar ucRet = COMM_TURE;
    for ( i = 0 ; i < ucLength; i ++)
    {
        if ((*(pucBuf + i) & 0x0f) > 0x09 || (*(pucBuf + i) & 0xf0) > 0x90)
        {
            ucRet = COMM_FAIL;
            break;
        }
    }
    return ucRet;
}

////���ڸ�ʽ���
///��У�����������,���ݳ���,�������ݳ���
///���ص���1��ʾ����,0��ʾ�ɹ����ҳ���û�б仯,2:����ɹ����ǳ����б仯,
//3:��ʱ������,4:��ʱ������.5:��������,6,Ȩ�޲���,7,����
uchar CommDayFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    uchar ucFlag=COMM_FAIL;
    uchar ucWeek;
    STR_CALENDAR  TmpDay;
// AA    changed by zhanglong -2009-09-01--->start  
    TmpDay.day=*(Dest+ucLenth-3);
    TmpDay.month=*(Dest+ucLenth-2);
    TmpDay.year=*(Dest+ucLenth-1);
    
    ucFlag=TestDayMonthYear(&TmpDay.day);
    if(ucFlag==0) 
    {
        return (COMM_FAIL);
    }
    
        if(0x07==(*Dest))
        {
        (*Dest)=0x00;
        }
    ucWeek=CalendarToWeek(&TmpDay);
    if(ucWeek!=(*Dest))
    {
        return (COMM_FAIL);
    }
// AA    changed by zhanglong ---->End
    
    return (COMM_TURE);
    
        
}
///ʱ���ʽ���
///��У�����������,���ݳ���,�������ݳ���
///���ص���1��ʾ����,0��ʾ�ɹ����ҳ���û�б仯,2:����ɹ����ǳ����б仯,
//3:��ʱ������,4:��ʱ������.5:��������,6,Ȩ�޲���,7,����
uchar CommTimeFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    uchar ucFlag=COMM_FAIL;
    ucFlag=TestHour(*(Dest+ucLenth-1));
    if(ucFlag==0) return (COMM_FAIL);
    ucFlag=TestMinute(*(Dest+ucLenth-2));
    if(ucFlag==0) return (COMM_FAIL);
    ucFlag=TestSecond(*(Dest+ucLenth-3));
    if(ucFlag==0) return (COMM_FAIL);   

    return (COMM_TURE);
}

////����������ڼ��
/*
uchar CommMDFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
        if(((*Dest)!=0x05)&&((*Dest)!=0x10)&&((*Dest)!=0x15)&&((*Dest)!=0x30)&&((*Dest)!=0x60)) {return COMM_FAIL;}
        else {return COMM_TURE;}   
}

////����ʱ����Ч�Լ��
uchar CommTackleFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    if(((*Dest)!=0x01)&&((*Dest)!=0x02)&&((*Dest)!=0x03)&&((*Dest)!=0x05)){return COMM_FAIL;}
    else {return COMM_TURE;}   
}
*/
////��ʱ�α�/ʱ�����л�ʱ��,
uchar CommFeeTableSwitchFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    uchar ucFlag=0;
#if(CONFIG_METER_AREA_MODE_SHANDONG==CONFIG_METER_AREA_MODE)
    uchar ucBuffer[7];
#endif
//  ucFlag=TestYear(*(Dest+ucLenth-1));
//  if(ucFlag==0) return (COMM_FAIL);
//  ucFlag=TestMonth(*(Dest+ucLenth-2));
//  if(ucFlag==0) return (COMM_FAIL);
    if(5==TestZeroNum(Dest, 5))
    {
        return (COMM_TURE);
    }

    //  ljc  20100624  start
    #if(CONFIG_METER_AREA_MODE_SICHUAN==CONFIG_METER_AREA_MODE)
    if(5==Test99Num(Dest, 5))
    {
        return (COMM_TURE);
    }
        #endif
    //  ljc  20100624  end
    
    ucFlag=TestDayMonthYear((Dest+ucLenth-3));
    if(ucFlag==0) return (COMM_FAIL);   
        
    ucFlag=TestHour(*(Dest+ucLenth-4));
    if(ucFlag==0) return (COMM_FAIL);
    ucFlag=TestMinute(*(Dest+ucLenth-5));
    if(ucFlag==0) return (COMM_FAIL);   

#if(CONFIG_METER_AREA_MODE_SHANDONG==CONFIG_METER_AREA_MODE)
    if(ulNowMinTime>=mmHHDDMMYYToLong((Dest+ucLenth-5)))
    {
        return (COMM_FAIL);
    }
#endif
        
    return (COMM_TURE);
    
}


uchar CommmmhhDDMMYYFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    uchar ucFlag=0;
    if(5==TestZeroNum(Dest, 5))
    {
        return (COMM_TURE);
    }
    ucFlag=TestDayMonthYear((Dest+ucLenth-3));
    if(ucFlag==0) return (COMM_FAIL);   
        
    ucFlag=TestHour(*(Dest+ucLenth-4));
    if(ucFlag==0) return (COMM_FAIL);
    ucFlag=TestMinute(*(Dest+ucLenth-5));
    if(ucFlag==0) return (COMM_FAIL);   

    return (COMM_TURE);
    
}


////��ʱ����/��Ч���ж�
///���ص���1��ʾ����,0��ʾ�ɹ����ҳ���û�б仯,2:����ɹ����ǳ����б仯,
//3:��ʱ������,4:��ʱ������.5:��������,6,Ȩ�޲���,7,����,8,û�и���
uchar CommSeasonNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    
        if(CheckBcd(Dest,ucLenth)==COMM_FAIL)  return COMM_FAIL;
         
        if ((*Dest)<=COMM_FEE_SEASON_NUM)  {return COMM_TURE;}
        else {return COMM_SEASON_NUM_OVER;}
        
}
////��ʱ�α�����Ч���ж�
uchar CommDayTableNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    if(CheckBcd(Dest,ucLenth)==COMM_FAIL)  return COMM_FAIL;
            
        if ((*Dest)<=COMM_FEE_DAYTABLE_NUM)  {return COMM_TURE;} 
        else  {return COMM_FAIL;} 
}

////��ʱ������Ч���ж�
uchar CommFeeTableNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    if(CheckBcd(Dest,ucLenth)==COMM_FAIL)  return COMM_FAIL;
            
        if ((*Dest)<=COMM_FEE_DAYTOU_NUM)  {return COMM_TURE;} 
        else  {return COMM_DAYTABLE_NUM_OVER;} 
}

///��������Ч���ж�
uchar CommFeeNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    if(CheckBcd(Dest,ucLenth)==COMM_FAIL)  return COMM_FAIL;
            
        if ((*Dest)<=COMM_FEE_FEE_NUM)  {return COMM_TURE;} 
        else  {return COMM_FEE_NUM_OVER;} 
}
///����������
uchar CommHolidayNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    u16  uiHoliadynum;
    
    if (CheckBcd(Dest,2)==COMM_FAIL)  return  COMM_FAIL;
    uiHoliadynum=BCD2_Word(Dest);
    if (uiHoliadynum<=COMM_FEE_HOLIDAY_NUM) return  COMM_TURE;
    else return COMM_FAIL;
}

////�����ձ����Ч���ж�
uchar CommWeekTableNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{ 
      if(((*Dest)>0)&&((*Dest)<=GetFeeDayTableMaxNum())) return  COMM_TURE;
      else return COMM_FAIL;
}
////ͨ�Ų�����ģʽ��
uchar CommBautWordFm(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    uchar ucWord,i,k=0;
    ucWord=*Dest;
    for(i=0;i<8;i++)
    {
        if(ucWord&UseFeezeBit[i]) k++;
    }
    
    if (k>1) return COMM_FAIL;
    if(ucWord&BIT7)     return  COMM_FAIL;
    if(ucWord&BIT0)     return  COMM_FAIL;
    return  COMM_TURE;
}
/// --������ã�Զ�̱�����ڹ�Կ״̬��--
#if(CONFIG_METER_PREPAY_MODE==CONFIG_METER_PREPAY_MODE_FAR)
uchar CommWriteFormatKey(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
       if(CheckBcd(Dest,ucLenth)==COMM_FAIL) return COMM_FAIL;
       if(0!=getFarKeyStatus()) return COMM_FAIL;
       else return COMM_TURE;
}
#endif

///BCD�ļ���
uchar CommWriteBcdFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
       if(CheckBcd(Dest,ucLenth)==COMM_FAIL) return COMM_FAIL;
       else return COMM_TURE;
}
uchar CommDemandNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    if(CheckBcd(Dest,ucLenth)==COMM_FAIL)
    {
        return COMM_FAIL;
    }
    if(1!=ucLenth)
    {
        return COMM_FAIL;
    }
    if(   (*Dest)>0x60)
    {
        return COMM_FAIL;
    }
       return COMM_TURE;
}

// AA  ----Changed by zhanglong 20090903---->start
///��ʾ����С��
uchar CommDspMDFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    uchar ucDot=(*Dest);
    if((ucDot>0x06))
        return COMM_FAIL;
    return COMM_TURE;
#if 0   
    uchar ucDot=(*Dest)>>0x0F;
    if (CheckBcd(Dest,ucLenth)==COMM_TURE)
    {
        if (ucDot>=COMM_DSP_EC_DOT_MAX) return COMM_FAIL;
        else return COMM_TURE;
    }
    else return COMM_FAIL;
#endif
}
///��ʾ����С��
uchar CommDspECFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    uchar ucDot=(*Dest);
    if((ucDot>0x04))
        return COMM_FAIL;
    return COMM_TURE;
#if 0
    uchar ucDot=(*Dest)>>0x0F;
    if (CheckBcd(Dest,ucLenth)==COMM_TURE)
    {
        if (ucDot>=COMM_DSP_EC_DOT_MAX) return COMM_FAIL;
        else return COMM_TURE;
    }
    else return COMM_FAIL;
#endif
}
// AA  ----Changed by zhanglong 20090903---->start

///���ԣ�����
//uchar CommDspNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)

/////�����ղ��õ���ʱ�α��
uchar CommWeekDayUseTouFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    uchar TableNum;
    uchar ucHex;
    TableNum=GetFeeDayTableMaxNum();
    ucHex=BCD_Byte(*Dest);
        
    if ((0==ucHex)||(ucHex>TableNum)) return COMM_DAYTABLE_NUM_OVER;
    else return COMM_TURE;
}


///���ɼ�¼ʱ��
uchar CommLoadRecordFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    uchar ucFlag=COMM_FAIL;
    
    ucFlag=TestMonth(*(Dest+ucLenth-1));
    if(ucFlag==0) return (COMM_FAIL);
    ucFlag=TestDay(*(Dest+ucLenth-2));
    if(ucFlag==0) return (COMM_FAIL);   
        
    ucFlag=TestHour(*(Dest+ucLenth-3));
    if(ucFlag==0) return (COMM_FAIL);
    ucFlag=TestMinute(*(Dest+ucLenth-4));
    if(ucFlag==0) return (COMM_FAIL);   
        
    return COMM_TURE;
}

////��������Ч���ж�
uchar CommBillDayFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
  // uchar ucFlag=COMM_FAIL;
  if((1==TestDay(*(Dest+ucLenth-1)))&&(1==TestHour(*(Dest+ucLenth-2))))
  {
    return COMM_TURE;
  }
  else
  {
    if((0x99==(*(Dest+ucLenth-1)))&&(0x99==(*(Dest+ucLenth-2))))
    {
        return COMM_TURE;
    }
  }
  return (COMM_FAIL);   
/*  
  ucFlag=TestDay(*(Dest+ucLenth-1));
    if((ucFlag==0)&&(*(Dest+ucLenth-1)!=0x99)) return (COMM_FAIL);  
        
    ucFlag=TestHour(*(Dest+ucLenth-2));
    if((ucFlag==0)&&(*(Dest+ucLenth-2)!=0x99))return (COMM_FAIL);
        
    if (((*(Dest+ucLenth-1))>0x28)&&(*(Dest+ucLenth-1)!=0x99)) return COMM_FAIL;
    else return COMM_TURE;
*/
}

////ʱ������Ч���ж�
//edited by zlq091027 ����ʱ������С���ж�,����14�������һ�����㵽14��
uchar CommSeasonTableFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    /////���ж�д���ʱ�α������Ƿ�Ϸ�
    // uchar ucFlag=COMM_FAIL;
    uchar ucTou=1;
    uchar ucPtr=1;
    //uchar ucSeasonNum=1,ucTmpLenth;
    uchar i;
    ///uchar TmpBuffer[3];
    uchar ucSQCnt;                                  //ʱ����
    uchar* p;
    ulong  ulTmp;
    
// AAA  ====================== Changed by zhanglong ---->Start
    ucTou=GetFeeDayTableMaxNum();  
    //if (0 != (ucLenth%3)) 
    //{
    //  return COMM_FAIL;
    //}
    //if (0== (ucLenth)) 
    //{
    //  return COMM_FAIL;
    //}
    //if ((3*CON_SEASONTABLELEN_MAX)!= (ucLenth)) 
    //{
    //  return COMM_FAIL;
    //}
//--AA changed by zhanglong --Jiangsu  20100324-->Start   AA----
#if 0
    ucSQCnt = GetFeeSeasonMaxNum();                     //ʱ����
    if(ucSQCnt*3 != ucLenth)
    {
        if(ucLenth > ucSQCnt*3)
        {
            return COMM_SEASON_NUM_OVER;
        }
        return COMM_FAIL;
    }
#else
    ucSQCnt = CON_SEASONTABLELEN_MAX;                     //ʱ����
    if(ucLenth > ucSQCnt*3)
    {
        return COMM_SEASON_NUM_OVER;
    }
    if((ucLenth%3))
    {
        return COMM_FAIL;
    }
    ucSQCnt=ucLenth/3;
#endif
//--AA changed by zhanglong --Jiangsu  20100324-->End   AA----
    
    p = Dest + (ucSQCnt*3);
    if(ucSQCnt < CON_SEASONTABLELEN_MAX)
    {
        memcpy((void*)&ulTmp, (void*)(p-3), 3);         //ȡ���һ��ֵ,������������14�����Ĳ���
        for(i=ucSQCnt; i<CON_SEASONTABLELEN_MAX; i++)
        {
            memcpy((void*)p, (void*)&ulTmp, 3);
            p += 3;
        }
    }
    
    for(i=0;i<CON_SEASONTABLELEN_MAX;i++)
    {
        if(BCD_Byte(*(Dest+i*3))>ucTou)
        {
            return (COMM_DAYTABLE_NUM_OVER);    
        }
    }
    ucPtr=NumofEverySeasonDayTableChangeComm(Dest);
    if(ucPtr != (ucLenth/3));
    {
        for(i=ucPtr;i<CON_SEASONTABLELEN_MAX;i++)
        {
            if((*(Dest+i*3-3+1)!=*(Dest+i*3+1))
                ||(*(Dest+i*3-3+2)!=*(Dest+i*3+2)))
            {
                return COMM_FAIL;
            }
        }
    }

    *ReturnFlag = CON_SEASONTABLELEN_MAX*3;

    return COMM_TURE;
/*
    ucPtr=ucLenth%3;
    if (ucPtr!=0)  return COMM_FAIL;

    ucPtr=ucLenth/3;
    ucTou=GetFeeDayTableMaxNum();   ///�����ʱ�α����
    //ucSeasonNum=GetFeeSeasonMaxNum();
    for(i=0;i<ucPtr;i++)
    {
        ucFlag=TestMonth(*(Dest+i*3+2));
        if(ucFlag==0) return (COMM_FAIL);
        ucFlag=TestDay(*(Dest+i*3+1));
        if(ucFlag==0) return (COMM_FAIL);
        ucFlag=BCD_Byte(*(Dest+i*3));
                if(ucFlag==0) return COMM_FAIL;
        if(ucFlag>ucTou) return (COMM_DAYTABLE_NUM_OVER);       
    }
        
        return COMM_TURE;
*/  
// AAA  ====================== Changed by zhanglong ---->End

    
        
    /////��û������������ݲ������
    /*
    if (ucPtr<ucSeasonNum)
    {
            ucTmpLenth=ucSeasonNum-ucPtr;
            memcpy(TmpBuffer,Dest+ucLenth-3,3);
            for(i=0;i<ucTmpLenth;i++)
            {
                memcpy(Dest+ucLenth+i*3,TmpBuffer,3);
            }
            *ReturnFlag=ucLenth+3*ucTmpLenth;
            return 2;   
    }
    else
    {
        if (ucPtr==ucSeasonNum)  return COMM_TURE;
    else  return COMM_SEASON_NUM_OVER;
    }
    */
}

//////�Ƚ���ʱ�α����
/*
uchar  CommFeeDayTableNUMCheck(ulong ulTmp)
{
     ulong ulTmp;
     if((ulTmp >= 0x04010001) && (ulTmp <= 0x04010008))
    {
        ulTmp -= 0x04010001;
    }
    else if((ulTmp >= 0x04020001) && (ulTmp <= 0x04020008))
    {
        ulTmp -= 0x04020001;
    }
    else
    {
        return COMM_FAIL;
    }
    ucTou = GetFeeDayTableMaxNum();                     //�����ʱ�α����
    if(ulTmp >= ucTou)                                   //ע������Ҫ��һ����������,�������������ƫ�����
    {
        return COMM_FAIL;
    }
     
}
*/
////ʱ�α���Ч���ж�
uchar CommFeeDayTableFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    /////���ж�д���ʱ�α������Ƿ�Ϸ�
//  uchar ucFlag=0;
    uchar ucTou=1;
    uchar ucPtr=1;
    uchar i;
    //uchar TmpBuffer[3],FeeTou=1,ucTmpLenth;
    
    uchar ucSDCnt;                                      //ʱ�α��л���
    uchar* p;

// AA =======Changed by zhanglong ---->Start----

    ulong ulTmp;
   ///;------------------------yaoxuxu 2009.11.07.21.21 -----start--�������Զ��Ҫ���ã����Ա�����ڸú�������---------
     // if((*ReturnFlag)!=0xFF)   ////Զ�����õ�Ϊ0Xff,
     // {
    //    memcpy((void*)&ulTmp, (void*)(Dest+10-22), 4);      //���id,����ǲ������õ�idƫ�����
    // }
    // else
    // {
    //    memcpy()
    // }
    /*
    if((ulTmp >= 0x04010001) && (ulTmp <= 0x04010008))
    {
        ulTmp -= 0x04010001;
    }
    else if((ulTmp >= 0x04020001) && (ulTmp <= 0x04020008))
    {
        ulTmp -= 0x04020001;
    }
    else
    {
        return COMM_FAIL;
    }
    ucTou = GetFeeDayTableMaxNum();                     //�����ʱ�α����
    if(ulTmp >= ucTou)                                   //ע������Ҫ��һ����������,�������������ƫ�����
    {
        return COMM_FAIL;
    }
    */
    ///;------------------------yaoxuxu 2009.11.07.21.21 -----end-----------

 //--AA changed by zhanglong --Jiangsu  20100324-->Start   AA----   
#if 0
    ucSDCnt = GetFeeTouTableMaxNum();             //ʱ�α��л���
    if(ucSDCnt*3 != ucLenth)
    {
        return COMM_FAIL;
    }
#else
    if((DLT_SEASON_TABLE_MAX*3)<ucLenth)
    {
        return COMM_FAIL;
    }
    if((ucLenth%3))
    {
        return COMM_FAIL;
    }
    ucSDCnt=ucLenth/3;
#endif
//--AA changed by zhanglong --Jiangsu  20100324-->End   AA----

   
    
    p = Dest + (ucSDCnt*3);
    if(ucSDCnt < DLT_SEASON_TABLE_MAX)
    {
        memcpy((void*)&ulTmp, (void*)(p-3), 3);         //ȡ���һ��ֵ,������������14�����Ĳ���
        for(i=ucSDCnt; i<DLT_SEASON_TABLE_MAX; i++)
        {
            memcpy((void*)p, (void*)&ulTmp, 3);
            p += 3;
        }
    }
    
    ucTou=GetSetFeeNumber();            //������
    //if (0 != (ucLenth%3)) 
    //{
    //  return COMM_FAIL;
    //}
    //if (0== (ucLenth)) 
    //{
    //  return COMM_FAIL;
    //}
    //if ((3*DLT_SEASON_TABLE_MAX)!= (ucLenth)) 
    //{
    //  return COMM_FAIL;
    //}
    for(i=0;i<DLT_SEASON_TABLE_MAX;i++)
    {
        if(BCD_Byte(*(Dest+i*3))>ucTou)
        {
            return (COMM_FEE_NUM_OVER); 
        }
    }
    ucPtr=NumofEveryDayPriceChangeComm(Dest);
    if(ucPtr != (ucLenth/3));
    {
        for(i=ucPtr;i<DLT_SEASON_TABLE_MAX;i++)
        {
            if((*(Dest+i*3-3+1)!=*(Dest+i*3+1))
                ||(*(Dest+i*3-3+2)!=*(Dest+i*3+2)))
            {
                return COMM_FAIL;
            }
        }
    }

    *ReturnFlag = DLT_SEASON_TABLE_MAX*3;

    return COMM_TURE;


// AA =======Changed by zhanglong ---->End----
/*
    ucPtr=ucLenth%3;
    if (ucPtr!=0)  return COMM_FAIL;
    ucPtr=ucLenth/3;
    ucTou=GetSetFeeNumber();   ///��÷��ʸ���
    //FeeTou=GetFeeTouTableMaxNum();  ////�����ʱ�α����
    for(i=0;i<ucPtr;i++)
    {
        ucFlag=TestHour(*(Dest+i*3+2));
        if(ucFlag==0) return (COMM_FAIL);
        ucFlag=TestMinute(*(Dest+i*3+1));
        if(ucFlag==0) return (COMM_FAIL);
        ucFlag=BCD_Byte(*(Dest+i*3));
                if(ucFlag==0) return (COMM_FAIL);
        if(ucFlag>ucTou) return (COMM_FEE_NUM_OVER);        
    }
    
    return COMM_TURE;
*/
    /*
    if (ucPtr<FeeTou) 
    {
        ucTmpLenth=FeeTou-ucPtr;
        memcpy(TmpBuffer,Dest+ucLenth-3,3);
        for(i=0;i<ucTmpLenth;i++)
        {
            memcpy(Dest+ucLenth+i*3,TmpBuffer,3);
        }
        *ReturnFlag=ucLenth+3*ucTmpLenth;
        
        return 2;
    }
    else
    {
        if (ucPtr==FeeTou) return COMM_TURE;
            else return COMM_FEE_NUM_OVER; 
    }
    */
}

////����������Ч���ж�
uchar CommCheckHolidayFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    uchar ucFlag=COMM_FAIL;
    uchar ucTou=1;
	
//  ucFlag=TestYear(*(Dest+ucLenth-1));
//  if(ucFlag==0) return (COMM_FAIL);
//  ucFlag=TestMonth(*(Dest+ucLenth-2));
//  if(ucFlag==0) return (COMM_FAIL);
    ucFlag=TestDayMonthYear((Dest+ucLenth-3));
	if(4 == TestZeroNum((Dest+ucLenth-4), 4))
	{
		ucFlag=COMM_FAIL;
	}
    if(ucFlag==0) return (COMM_FAIL);   
        
    ucTou=GetFeeDayTableMaxNum();
    
    if ((*Dest)>ucTou) return COMM_FAIL;
    else return COMM_TURE;
    
}

uchar CommCheckhhmm(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    uchar ucFlag=COMM_FAIL;
    ucFlag=TestHour(*(Dest+ucLenth-1));
    if(ucFlag==0) return (COMM_FAIL);
    ucFlag=TestMinute(*(Dest+ucLenth-2));
    if(ucFlag==0) return (COMM_FAIL);

    return (COMM_TURE);
}

////У��պ���
uchar NULLCheckFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    return COMM_TURE;
}
uchar FactoryCheckFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    if(((COMM_RECEIVE_FRAME_CONTROLNO&0x14)==0x14)
        ||(COMM_97TYPE_CONTROLWORD==0x05))
        {
            if(PROGFUNCTION_METER_FACTORY != METER_IN_FACTORY)      
                return COMM_FAIL;
            else
                return COMM_TURE;
        }
    else
        return COMM_FAIL;
}

////��ö˿ں�����
////ID0
uchar GetCommTypeName(uchar ucID0);
uchar GetCommTypeName(uchar ucID0)
{
    switch (ucID0)
    {
        case 0x01:
            return SOURCE_IR;
        case 0x03:
            return SOURCE_485;
        case 0x04:
            return SOURCE_485_2;
        case 0x05:
            return CARRIER_MODULE_COMMNO;
        default:
            return  0xFF;
    }
}

////д����
//�Ƚ�����
//��¼�����ߴ���
//�����ñ��,
//���ÿ��ƺ���:(�ú�������������ҳ��ṩ)
void CommControlWriteData(void)
{
    uchar ucLenth=0,ProgramState,TmpComm;  ///����
    ulong ulID,ulAddr=0xffffffff; 
    uchar TmpClockBuffer[6];
    ulong ulTmp;
    uchar ID0;
    uchar Popedome,ReturnState=8,ReturnLenth,ReturnBit;
    WithReturnFUNCTION  BackFunction=NULLReturnValue;  ///�ص�����
    CheckFunction  TmpCheckFunction=NULLCheckFormat;    ///У��������Ч�Ժ���
    u16   Ptr,TableNum;     ///����ָ��
    STR_CALENDAR  CommTim;   //ʱ��      
    STR_PROGRAM_RECORD_INDATA  strRecordData;
  
    ulID=GetCommReadData645ID(ucCommFormatType);
    ID0=(uchar)(ulID);
        
    ProgramState=GetTheProgramKeyState();   ///�Ƿ��ڱ��״̬
#if(CONFIG_METER_PREPAY_MODE !=CONFIG_METER_PREPAY_MODE_DISABLE)
    if((COMM_RECEIVE_WRITE_PASSWORD== PASS_WORD_98)||(COMM_RECEIVE_WRITE_PASSWORD== PASS_WORD_99))  //����
    {
        FarCtlMange(&CommExpReceiveDataBuffer,COMM_RECEIVE_WRITE_PASSWORD);
        gucFarCtlFlg=COMM_USE;  //Զ�̿��Ʋ��ڴ˴�Ӧ��
        return;
    }
    else
#endif

    {
        if((ProgramState==COMM_FAIL) && (ulID != 0x04001301))   //�ź�ǿ�ȵ����⴦��
        {
          ReturnState=6;
        }
        else
        {
#if(CONFIG_METER_PREPAY_MODE !=CONFIG_METER_PREPAY_MODE_DISABLE)

            ///////�ѿص��1�����������02�����������
            if((ulID==0x04000108)||(ulID==0x04000306)||(ulID==0x04000307)||(ulID==0x04001001)
                ||(ulID==0x04001002)||(ulID==0x0400040E)
                ||(0x04050100==(ulID&0xffffff00))||(0x04050200==(ulID&0xffffff00)))
            {

                 ReturnState=6;
            }
            else
#endif
            {
                if ((ulID>=0x04030001)&&(ulID<=0x040300FE)) ////��������
                {
                    Popedome=CommCmpPassword(COMM_PASSWORD_SECOND_PARA);  ///Ĭ��Ȩ������߼�
                    if (Popedome==COMM_TURE)
                    {
                        ReturnLenth=4;
                        ReturnState=CommCheckHolidayFormat(&COMM_RECEIVE_WRITE_DATA,ReturnLenth,&ReturnLenth);
                        if (ReturnState==COMM_TURE)
                        {
                            {
                                ulAddr=EPL_PUBLIC_HOLIDAY_START+ReturnLenth*(ID0-1);
                                BackFunction=CWBFPriceChange;
                                ReturnState=COMM_TURE;
                                ///////////////
                                strRecordData.EvenType=PROGRAM_RECORD_HOLIDAY;
                                      
                            }
                        }
                    }
                    else  {ReturnState=6;}
                }
                else
                {
#if(CONFIG_METER_AREA_MODE_SHANDONG!=CONFIG_METER_AREA_MODE)
                    if ((ulID>=0x04040101)&&(ulID<=0x04040163))  ////�Զ���ʾ,FE->63,zlq090922
#else                                       
                    if ((ulID>=0x04040101)&&(ulID<=0x040401ff))  ////�Զ���ʾ,FE->63,zlq090922
#endif
                    {
                        Popedome=CommCmpPassword(COMM_PASSWORD_POPEDOM_4);  ///Ĭ��Ȩ������߼�
                                
                        if(Popedome==0)
                        {
                            //TableNum=GetSetCycleLcdNum();
                            memcpy((uchar *)&ulTmp, (uchar *) &COMM_RECEIVE_WRITE_DATA, 4);
                            memcpy((uchar *)&ReturnLenth, (uchar *)(4+(&COMM_RECEIVE_WRITE_DATA)), 1);
                                
                            //if (ID0>TableNum)/////ID
                            //{
                            //        ReturnState=COMM_HAVE_NO;
                            //}
                            if(0xffff==SearchInDispList(ulTmp,ReturnLenth))
                            {
                                ReturnState=7;
                            }
                            else
                            {
                                ReturnLenth=5;
                                ulAddr=EPL_DISPLAY_AUTOSET_START+(ID0-1)*ReturnLenth;
                                ReturnState=COMM_TURE;
                                BackFunction=CWBFDisplayChange;
                                ////
                                strRecordData.EvenType=PROGRAM_RECORD_COMMOM;
                            }
                        }
                        else  {ReturnState=6;}
                    }
                    else
                    {
#if(CONFIG_METER_AREA_MODE_SHANDONG!=CONFIG_METER_AREA_MODE)
                        if ((ulID>=0x04040201)&&(ulID<=0x04040263))  ////������ʾ,FE->63,zlq090922
#else
                        if ((ulID>=0x04040201)&&(ulID<=0x040402ff))  ////������ʾ,FE->63,zlq090922
#endif
                        {
                            Popedome=CommCmpPassword(COMM_PASSWORD_POPEDOM_4);  ///Ĭ��Ȩ������߼�
                            if (Popedome==0)
                            {
                                ReturnLenth=5;
                                //TableNum=GetkeyCycleNum();
                                //if (ID0>TableNum)/////ID
                                //{
                                //        ReturnState=COMM_HAVE_NO;
                                //}
                                //else
                                memcpy((uchar *)&ulTmp, (uchar *) &COMM_RECEIVE_WRITE_DATA, 4);
                                memcpy((uchar *)&ReturnLenth, (uchar *)(4+(&COMM_RECEIVE_WRITE_DATA)), 1);
        
                                //if (ID0>TableNum)/////ID
                                //{
                                //        ReturnState=COMM_HAVE_NO;
                                //}
                                if(0xffff==SearchInDispList(ulTmp,ReturnLenth))
                                {
                                    ReturnState=7;
                                }
                                else
                                {
                                    ReturnLenth=5;
                                    ulAddr=EPL_DISPLAY_KEYSET_START+(ID0-1)*ReturnLenth;
                                    ReturnState=COMM_TURE;
                                    BackFunction=CWBFDisplayChange;
                                    //////
                                    strRecordData.EvenType=PROGRAM_RECORD_COMMOM;
                                }
                            }
                            else {ReturnState=6;}   
                        }
                        //  ljc  20100620  start
#if(CONFIG_METER_AREA_MODE_SICHUAN==CONFIG_METER_AREA_MODE)
                        else if ((ulID>=0x04040264)&&(ulID<=0x040402C7))  ////
                        {
                            Popedome=CommCmpPassword(COMM_PASSWORD_POPEDOM_4);  ///Ĭ��Ȩ������߼�
                            if (Popedome==0)
                            {
                                ReturnLenth=5;
                                memcpy((uchar *)&ulTmp, (uchar *) &COMM_RECEIVE_WRITE_DATA, 4);
                                memcpy((uchar *)&ReturnLenth, (uchar *)(4+(&COMM_RECEIVE_WRITE_DATA)), 1);
            
                                if(0xffff==SearchInDispListCom(ulTmp,ReturnLenth))
                                {
                                    ReturnState=7;
                                }
                                else
                                {
                                    ReturnLenth=5;
                                    ulAddr=KEY_TURN_DISPLAY_B_LIST_START_ADDR+(ID0-0x64)*ReturnLenth;
                                    ReturnState=COMM_TURE;
                                    BackFunction=CWBFDisplayChange;

                                    strRecordData.EvenType=PROGRAM_RECORD_COMMOM;
                                 }
                            }
                            else {ReturnState=6;}   
                        }
#endif
//  ljc  20100620  end
                        else
                        {
                            TableNum=GetParameterTableNum();
                            for (Ptr=0;Ptr<TableNum;Ptr++)
                            {
                                    if(TableParaMeter[Ptr].id==ulID) break;
                            }
                            
                            if(Ptr>=TableNum)///û�и�ID
                            {
                                //ReturnState=COMM_HAVE_NO;
                                ReturnState = 6;                //edited by zlq091029 id����������ʱ��Ȩ�������
                            }
                            else
                            {
                                if (TableParaMeter[Ptr].enabled==COMM_PARAMETER_USED)
                                {
									//ProgramState=GetTheProgramKeyState();   ///�Ƿ��ڱ��״̬
									//if((TableParaMeter[Ptr].WithPKey==COMM_PARAMETER_USED)&&(ProgramState==COMM_FAIL))   ////��Ҫ��̼����
									//{
										//ReturnState=6;
									//}
									//else   ///��ʹ��Ȩ��
									//{
										if(TableParaMeter[Ptr].id == 0x04001301)
										{
											Popedome = COMM_FAIL;
										#if(CONFIG_METER_NO2COMM_MODE_WIRELESS==CONFIG_METER_NO2COMM_MODE)
											if(GetExplainCommNo() == WIRELESS_MODULE_COMMNO)
											{
												//����ģ����ź�ǿ��֡��������У��
												Popedome= COMM_TURE;
											}
											//else if((ProgramState == COMM_TURE) && (PROGFUNCTION_METER_FACTORY == METER_IN_FACTORY))
											//{
											//    Popedome=CommCmpPassword(TableParaMeter[Ptr].access);
											//}
										#endif 
										}
										else
										{
											Popedome=CommCmpPassword(TableParaMeter[Ptr].access);
										}
           
										ucLenth=GetCommDataLen();
										ucLenth-=12;
										if((ucLenth==TableParaMeter[Ptr].dataLens) || (TableParaMeter[Ptr].WithSpecKey != 0))
										{
											//if ((Popedome==0) || (ulID == 0x04001301))
											if(((Popedome==0)&&((TableParaMeter[Ptr].ReadAndWrite&COMM_WRITE)||(TableParaMeter[Ptr].ReadAndWrite&COMM_PASSWORD)))/* || (ulID == 0x04001301)*/) 
											{
                                                TmpCheckFunction=TableParaMeter[Ptr].CheckFunction;
                                                ReturnLenth=ucLenth;
                                                ReturnState=TmpCheckFunction(&COMM_RECEIVE_WRITE_DATA,ucLenth,&ReturnLenth);
                                                ulAddr=TableParaMeter[Ptr].memoryAddress;
                                                
                                                BackFunction=TableParaMeter[Ptr].callBack;
                                                strRecordData.EvenType=TableParaMeter[Ptr].ProgramType;
											}
											else
											{
												ReturnState=6;
											}     ////����Ȩ�޲���
	                                    }
	                                    else    ////���Ȳ���
	                                    {
											ReturnState=7;
	                                    }
									//} 
                                }
                                else   ////û��ʹ�ø���
                                {
                                        ReturnState=COMM_FAIL;
                                }
                            }
                        }
                    }
                }
            }
        }
        switch (ReturnState)
        {
            case COMM_FAIL:    ///û�и�ID
                CommExpDataBuff->Buffer[0]=BIT0;
                ucLenth=1;
                ReturnBit=(COMMTYPE_WRITEDATA|BIT6)|BIT7;
                break;
            case COMM_TURE:
            case 2:
                ///////��̼�¼һ��                                                                                                   
               ///////��¼�±���¼�
               strRecordData.ID=ulID;
               GetUseNumber((uchar*)&ulTmp,4);
               strRecordData.HanderNum=ulTmp;
               strRecordData.CommNo=GetExplainCommNo();
               strRecordData.CommType=GetCommType();
                       
                //  EvenProgramRecord(strRecordData,&COMM_RECEIVE_WRITE_DATA,ReturnLenth);
               /////д�²���
                switch (ulID)
                {
                    case    0x04000101:    ///����
                        GetRealTime(&CommTim); 
                        memcpy(&CommTim.day,(&COMM_RECEIVE_WRITE_DATA)+1,3);
                                      
                        memcpy(&TmpClockBuffer,&CommTim.second,3);
                        memcpy(&TmpClockBuffer[3],&CommTim.day,3);
                        EvenProgramRecord(strRecordData,&TmpClockBuffer[0],6);
                      
                        SetRealTime(&CommTim);
                        // �㲥Уʱ��¼����
                        WriteCoefDataWithSync(&ucZeroArray[0],EPL_LAST_CHANNELS01_BROADCASTTIME,6);
                        break;

                    case  0x04000102:    ///ʱ��
                        GetRealTime(&CommTim);
                        memcpy(&CommTim.second,&COMM_RECEIVE_WRITE_DATA,ReturnLenth);
                        memcpy(&TmpClockBuffer,&CommTim.second,3);
                        memcpy(&TmpClockBuffer[3],&CommTim.day,3);
                        EvenProgramRecord(strRecordData,&TmpClockBuffer[0],6);
                                    
                        SetRealTime(&CommTim);  
                        // �㲥Уʱ��¼����
                        WriteCoefDataWithSync(&ucZeroArray[0],EPL_LAST_CHANNELS01_BROADCASTTIME,6);
                                            
                        break;
                    case  0x04000701:    //����ͨ������������
                    //case  0x04000702:    //ͨ������������
                    case  0x04000703:    //ͨ������������1  
#if(CONFIG_METER_NO2COMM_MODE_RS485==CONFIG_METER_NO2COMM_MODE)
                    case  0x04000704:    //ͨ������������2
#endif
#if(CONFIG_METER_NO2COMM_MODE_PLC==CONFIG_METER_NO2COMM_MODE)
                // --AA ����������AA--
                    // case  0x04000704:    //ͨ������������2
#endif
#if(CONFIG_METER_NO2COMM_MODE_WIRELESS==CONFIG_METER_NO2COMM_MODE)
                // --AA ����������AA--
                //   case  0x04000704:    //ͨ������������2
#endif
                //  case  0x04000705:    //ͨ������������3
                        EvenProgramRecord(strRecordData,&COMM_RECEIVE_WRITE_DATA,ReturnLenth);
                        TmpComm=GetCommTypeName(ID0);
                        if (TmpComm!=0xFF)
                        {
                                              //------------------------------yaoxuxu  2009.11.08 ----start
                            if(GetCommBautType(&UartPotr.uartPara,COMM_RECEIVE_WRITE_DATA,ID0)==0x00)
                            {
                                CommExpDataBuff->Buffer[0]=BIT3;
                                ReturnBit=(COMMTYPE_WRITEDATA|BIT6)|BIT7;
                                ucLenth=1;
                                SetReturnDataFrame(ucLenth,ReturnBit);
                                UartPotr.controlData=0;   ///��������Ҫ����(����������)
                                return;
                            }
                            else
                            //------------------------------yaoxuxu  2009.11.08 ----end
                            {
                                if(TmpComm==GetExplainCommNo())
                                {
                                    UartPotr.controlData=2;   ///��������Ҫ����(����������)
                                }
                                else
                                {
                              //      SetUART(TmpComm,&UartPotr.uartPara);
                              //      UartPotr.controlData=0;   ///��������Ҫ����(����������)
                                }
                            }
                        }
                        else
                        {
                            CommExpDataBuff->Buffer[0]=BIT3;
                            ReturnBit=(COMMTYPE_WRITEDATA|BIT6)|BIT7;
                            ucLenth=1;
                            SetReturnDataFrame(ucLenth,ReturnBit);
                            UartPotr.controlData=0;   ///��������Ҫ����(����������)
                            return;
                        }
                        //////�޸ĵڼ�ͨ���Ĳ�����
                        break;
#if(CONFIG_METER_NO2COMM_MODE_WIRELESS==CONFIG_METER_NO2COMM_MODE)
                // --AA ����ͨ�����߼��ź�ǿ��ָʾ�����ü�¼ AA--
                    case  0x04001301:
                                   WirelessStatusDelay = 200;
                        break;
#endif
                    default:
                        EvenProgramRecord(strRecordData,&COMM_RECEIVE_WRITE_DATA,ReturnLenth);
                        break;
                    }
                    CommExpDataBuff->Buffer[0]= 0;       
                    if(0x04000101 == ulID)
                    {
                        WriteCoefDataWithSync(&COMM_RECEIVE_WRITE_DATA,EPL_SOFT_DAY+3,1);
                        WriteCoefDataWithSync((&COMM_RECEIVE_WRITE_DATA)+1,EPL_SOFT_DAY,3);
                    }
                    else if(0x04000101 == ulID)
                    {
                        WriteCoefDataWithSync((&COMM_RECEIVE_WRITE_DATA),EPL_SOFT_SECOND,3);
                    }
                    else
                    {
                        WriteCoefDataWithSync(&COMM_RECEIVE_WRITE_DATA,ulAddr,ReturnLenth);
                    }
                    //////���ûص�����(ˢ������)
                    BackFunction();
                    ucLenth=0;
                    ReturnBit=COMMTYPE_WRITEDATA|BIT7;
                    break;
                case 3:////��ʱ������
                    CommExpDataBuff->Buffer[0]=BIT4;
                    ucLenth=1;
                    ReturnBit=(COMMTYPE_WRITEDATA|BIT6)|BIT7;
                    break;
                case 4://///��ʱ������
                    CommExpDataBuff->Buffer[0]=BIT5;
                    ucLenth=1;
                    ReturnBit=(COMMTYPE_WRITEDATA|BIT6)|BIT7;
                    break;
                case 5:////��������
                    CommExpDataBuff->Buffer[0]=BIT6;
                    ucLenth=1;
                    ReturnBit=(COMMTYPE_WRITEDATA|BIT6)|BIT7;
                    break;
                case 6:////������δ��Ȩ
                    CommExpDataBuff->Buffer[0]=BIT2;
                    ucLenth=1;
                    ReturnBit=(COMMTYPE_WRITEDATA|BIT6)|BIT7;
                    break;
             case 8:  //////����������
                    CommExpDataBuff->Buffer[0]=BIT1;
                    ucLenth=1;
                    ReturnBit=(COMMTYPE_WRITEDATA|BIT6)|BIT7;
                break;
                case 7:  ////��������
                default:
                    CommExpDataBuff->Buffer[0]=BIT0;
                    ReturnBit=(COMMTYPE_WRITEDATA|BIT6)|BIT7;
                    ucLenth=1;
                    break;
            }
            
            SetReturnDataFrame(ucLenth,ReturnBit);
        }
}
