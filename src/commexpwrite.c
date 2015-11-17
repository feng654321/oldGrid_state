/*********************************************************************************
    版本号     :version 0.1
    模块名       : 远程控制模块
    文件名       : CommExpWrite.c
    相关文件     : 
    文件实现功能 : 通信写参数模块
    作者         : 姚徐旭
    版本         : 0.1
----------------------------------------------------------------------------------------------------------------------
    备注         : <其它说明>
---------------------------------------------------------------------------------------------------------------------
    修改记录 : 
    日 期        版本     修改人              修改内容
    YYYY/MM/DD   X.Ymai      <作者或修改者名>    <修改内容>
    YYYY/MM/DD   X.Y      <作者或修改者名>    <修改内容>
==================================================================== 
其他说明： 
*******************************************************************************/
#include "common.h"

uchar CheckBcd(uchar *pucBuf, uchar ucLength);



/////////////////////////参变量数据的有效性检查////////////////////////////
/******************************************************************************
Function:uchar CheckBcd(uchar *pucBuf, uchar ucLength)
Description:检查BCD数据是否合法
Input:mode:数据首地址、长度
Output:
Return:1合法0非法
Application area:
Modification register:暂无。
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

////日期格式检查
///被校验的数据类型,数据长度,返回数据长度
///返回的是1表示错误,0表示成功并且长度没有变化,2:代表成功但是长度有变化,
//3:年时区数超,4:日时段数超.5:费率数超,6,权限不够,7,其他
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
///时间格式检查
///被校验的数据类型,数据长度,返回数据长度
///返回的是1表示错误,0表示成功并且长度没有变化,2:代表成功但是长度有变化,
//3:年时区数超,4:日时段数超.5:费率数超,6,权限不够,7,其他
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

////最大需量周期检查
/*
uchar CommMDFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
        if(((*Dest)!=0x05)&&((*Dest)!=0x10)&&((*Dest)!=0x15)&&((*Dest)!=0x30)&&((*Dest)!=0x60)) {return COMM_FAIL;}
        else {return COMM_TURE;}   
}

////滑差时间有效性检查
uchar CommTackleFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    if(((*Dest)!=0x01)&&((*Dest)!=0x02)&&((*Dest)!=0x03)&&((*Dest)!=0x05)){return COMM_FAIL;}
    else {return COMM_TURE;}   
}
*/
////日时段表/时区表切换时间,
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


////年时区数/有效性判断
///返回的是1表示错误,0表示成功并且长度没有变化,2:代表成功但是长度有变化,
//3:年时区数超,4:日时段数超.5:费率数超,6,权限不够,7,其他,8,没有该项
uchar CommSeasonNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    
        if(CheckBcd(Dest,ucLenth)==COMM_FAIL)  return COMM_FAIL;
         
        if ((*Dest)<=COMM_FEE_SEASON_NUM)  {return COMM_TURE;}
        else {return COMM_SEASON_NUM_OVER;}
        
}
////日时段表数有效性判断
uchar CommDayTableNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    if(CheckBcd(Dest,ucLenth)==COMM_FAIL)  return COMM_FAIL;
            
        if ((*Dest)<=COMM_FEE_DAYTABLE_NUM)  {return COMM_TURE;} 
        else  {return COMM_FAIL;} 
}

////日时段数有效性判断
uchar CommFeeTableNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    if(CheckBcd(Dest,ucLenth)==COMM_FAIL)  return COMM_FAIL;
            
        if ((*Dest)<=COMM_FEE_DAYTOU_NUM)  {return COMM_TURE;} 
        else  {return COMM_DAYTABLE_NUM_OVER;} 
}

///费率数有效性判断
uchar CommFeeNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    if(CheckBcd(Dest,ucLenth)==COMM_FAIL)  return COMM_FAIL;
            
        if ((*Dest)<=COMM_FEE_FEE_NUM)  {return COMM_TURE;} 
        else  {return COMM_FEE_NUM_OVER;} 
}
///公共假日数
uchar CommHolidayNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    u16  uiHoliadynum;
    
    if (CheckBcd(Dest,2)==COMM_FAIL)  return  COMM_FAIL;
    uiHoliadynum=BCD2_Word(Dest);
    if (uiHoliadynum<=COMM_FEE_HOLIDAY_NUM) return  COMM_TURE;
    else return COMM_FAIL;
}

////周休日编程有效性判断
uchar CommWeekTableNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{ 
      if(((*Dest)>0)&&((*Dest)<=GetFeeDayTableMaxNum())) return  COMM_TURE;
      else return COMM_FAIL;
}
////通信波特率模式字
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
/// --表号设置，远程表必须在公钥状态下--
#if(CONFIG_METER_PREPAY_MODE==CONFIG_METER_PREPAY_MODE_FAR)
uchar CommWriteFormatKey(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
       if(CheckBcd(Dest,ucLenth)==COMM_FAIL) return COMM_FAIL;
       if(0!=getFarKeyStatus()) return COMM_FAIL;
       else return COMM_TURE;
}
#endif

///BCD的检验
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
///显示需量小数
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
///显示电量小数
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

///按显，键显
//uchar CommDspNumFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)

/////周休日采用的日时段表号
uchar CommWeekDayUseTouFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    uchar TableNum;
    uchar ucHex;
    TableNum=GetFeeDayTableMaxNum();
    ucHex=BCD_Byte(*Dest);
        
    if ((0==ucHex)||(ucHex>TableNum)) return COMM_DAYTABLE_NUM_OVER;
    else return COMM_TURE;
}


///负荷记录时间
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

////结算日有效性判断
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

////时区表有效性判断
//edited by zlq091027 按照时区数大小来判断,不到14个用最后一个补足到14个
uchar CommSeasonTableFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    /////先判断写入的时段表数据是否合法
    // uchar ucFlag=COMM_FAIL;
    uchar ucTou=1;
    uchar ucPtr=1;
    //uchar ucSeasonNum=1,ucTmpLenth;
    uchar i;
    ///uchar TmpBuffer[3];
    uchar ucSQCnt;                                  //时区数
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
    ucSQCnt = GetFeeSeasonMaxNum();                     //时区数
    if(ucSQCnt*3 != ucLenth)
    {
        if(ucLenth > ucSQCnt*3)
        {
            return COMM_SEASON_NUM_OVER;
        }
        return COMM_FAIL;
    }
#else
    ucSQCnt = CON_SEASONTABLELEN_MAX;                     //时区数
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
        memcpy((void*)&ulTmp, (void*)(p-3), 3);         //取最后一个值,用于填满不足14个数的部分
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
    ucTou=GetFeeDayTableMaxNum();   ///获得日时段表个数
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

    
        
    /////把没有设置完的数据补充完毕
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

//////比较日时段表个数
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
    ucTou = GetFeeDayTableMaxNum();                     //获得日时段表个数
    if(ulTmp >= ucTou)                                   //注意这里要加一个等于条件,这是由上面减的偏移造成
    {
        return COMM_FAIL;
    }
     
}
*/
////时段表有效性判断
uchar CommFeeDayTableFormat(uchar *Dest,uchar ucLenth,uchar *ReturnFlag)
{
    /////先判断写入的时段表数据是否合法
//  uchar ucFlag=0;
    uchar ucTou=1;
    uchar ucPtr=1;
    uchar i;
    //uchar TmpBuffer[3],FeeTou=1,ucTmpLenth;
    
    uchar ucSDCnt;                                      //时段表切换数
    uchar* p;

// AA =======Changed by zhanglong ---->Start----

    ulong ulTmp;
   ///;------------------------yaoxuxu 2009.11.07.21.21 -----start--这个由于远程要调用，所以必须放在该函数外面---------
     // if((*ReturnFlag)!=0xFF)   ////远程设置的为0Xff,
     // {
    //    memcpy((void*)&ulTmp, (void*)(Dest+10-22), 4);      //获得id,这个是参数设置的id偏移情况
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
    ucTou = GetFeeDayTableMaxNum();                     //获得日时段表个数
    if(ulTmp >= ucTou)                                   //注意这里要加一个等于条件,这是由上面减的偏移造成
    {
        return COMM_FAIL;
    }
    */
    ///;------------------------yaoxuxu 2009.11.07.21.21 -----end-----------

 //--AA changed by zhanglong --Jiangsu  20100324-->Start   AA----   
#if 0
    ucSDCnt = GetFeeTouTableMaxNum();             //时段表切换数
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
        memcpy((void*)&ulTmp, (void*)(p-3), 3);         //取最后一个值,用于填满不足14个数的部分
        for(i=ucSDCnt; i<DLT_SEASON_TABLE_MAX; i++)
        {
            memcpy((void*)p, (void*)&ulTmp, 3);
            p += 3;
        }
    }
    
    ucTou=GetSetFeeNumber();            //费率数
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
    ucTou=GetSetFeeNumber();   ///获得费率个数
    //FeeTou=GetFeeTouTableMaxNum();  ////获得日时段表个数
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

////公共假日有效性判断
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

////校验空函数
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

////获得端口号名称
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

////写数据
//比较密码
//记录操作者代码
//读设置表格,
//调用控制函数:(该函数由张龙和李家成提供)
void CommControlWriteData(void)
{
    uchar ucLenth=0,ProgramState,TmpComm;  ///长度
    ulong ulID,ulAddr=0xffffffff; 
    uchar TmpClockBuffer[6];
    ulong ulTmp;
    uchar ID0;
    uchar Popedome,ReturnState=8,ReturnLenth,ReturnBit;
    WithReturnFUNCTION  BackFunction=NULLReturnValue;  ///回调函数
    CheckFunction  TmpCheckFunction=NULLCheckFormat;    ///校验数据有效性函数
    u16   Ptr,TableNum;     ///表内指针
    STR_CALENDAR  CommTim;   //时钟      
    STR_PROGRAM_RECORD_INDATA  strRecordData;
  
    ulID=GetCommReadData645ID(ucCommFormatType);
    ID0=(uchar)(ulID);
        
    ProgramState=GetTheProgramKeyState();   ///是否处于编程状态
#if(CONFIG_METER_PREPAY_MODE !=CONFIG_METER_PREPAY_MODE_DISABLE)
    if((COMM_RECEIVE_WRITE_PASSWORD== PASS_WORD_98)||(COMM_RECEIVE_WRITE_PASSWORD== PASS_WORD_99))  //加密
    {
        FarCtlMange(&CommExpReceiveDataBuffer,COMM_RECEIVE_WRITE_PASSWORD);
        gucFarCtlFlg=COMM_USE;  //远程控制不在此处应答
        return;
    }
    else
#endif

    {
        if((ProgramState==COMM_FAIL) && (ulID != 0x04001301))   //信号强度的特殊处理
        {
          ReturnState=6;
        }
        else
        {
#if(CONFIG_METER_PREPAY_MODE !=CONFIG_METER_PREPAY_MODE_DISABLE)

            ///////费控电表1类参数不允许02级密码的设置
            if((ulID==0x04000108)||(ulID==0x04000306)||(ulID==0x04000307)||(ulID==0x04001001)
                ||(ulID==0x04001002)||(ulID==0x0400040E)
                ||(0x04050100==(ulID&0xffffff00))||(0x04050200==(ulID&0xffffff00)))
            {

                 ReturnState=6;
            }
            else
#endif
            {
                if ((ulID>=0x04030001)&&(ulID<=0x040300FE)) ////公共假日
                {
                    Popedome=CommCmpPassword(COMM_PASSWORD_SECOND_PARA);  ///默认权限是最高级
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
                    if ((ulID>=0x04040101)&&(ulID<=0x04040163))  ////自动显示,FE->63,zlq090922
#else                                       
                    if ((ulID>=0x04040101)&&(ulID<=0x040401ff))  ////自动显示,FE->63,zlq090922
#endif
                    {
                        Popedome=CommCmpPassword(COMM_PASSWORD_POPEDOM_4);  ///默认权限是最高级
                                
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
                        if ((ulID>=0x04040201)&&(ulID<=0x04040263))  ////按键显示,FE->63,zlq090922
#else
                        if ((ulID>=0x04040201)&&(ulID<=0x040402ff))  ////按键显示,FE->63,zlq090922
#endif
                        {
                            Popedome=CommCmpPassword(COMM_PASSWORD_POPEDOM_4);  ///默认权限是最高级
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
                            Popedome=CommCmpPassword(COMM_PASSWORD_POPEDOM_4);  ///默认权限是最高级
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
                            
                            if(Ptr>=TableNum)///没有该ID
                            {
                                //ReturnState=COMM_HAVE_NO;
                                ReturnState = 6;                //edited by zlq091029 id不对在设置时会权限密码错
                            }
                            else
                            {
                                if (TableParaMeter[Ptr].enabled==COMM_PARAMETER_USED)
                                {
									//ProgramState=GetTheProgramKeyState();   ///是否处于编程状态
									//if((TableParaMeter[Ptr].WithPKey==COMM_PARAMETER_USED)&&(ProgramState==COMM_FAIL))   ////需要编程键配合
									//{
										//ReturnState=6;
									//}
									//else   ///有使用权限
									//{
										if(TableParaMeter[Ptr].id == 0x04001301)
										{
											Popedome = COMM_FAIL;
										#if(CONFIG_METER_NO2COMM_MODE_WIRELESS==CONFIG_METER_NO2COMM_MODE)
											if(GetExplainCommNo() == WIRELESS_MODULE_COMMNO)
											{
												//无线模块的信号强度帧忽略密码校验
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
											}     ////密码权限不对
	                                    }
	                                    else    ////长度不对
	                                    {
											ReturnState=7;
	                                    }
									//} 
                                }
                                else   ////没有使用该项
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
            case COMM_FAIL:    ///没有该ID
                CommExpDataBuff->Buffer[0]=BIT0;
                ucLenth=1;
                ReturnBit=(COMMTYPE_WRITEDATA|BIT6)|BIT7;
                break;
            case COMM_TURE:
            case 2:
                ///////编程记录一下                                                                                                   
               ///////记录下编程事件
               strRecordData.ID=ulID;
               GetUseNumber((uchar*)&ulTmp,4);
               strRecordData.HanderNum=ulTmp;
               strRecordData.CommNo=GetExplainCommNo();
               strRecordData.CommType=GetCommType();
                       
                //  EvenProgramRecord(strRecordData,&COMM_RECEIVE_WRITE_DATA,ReturnLenth);
               /////写下参数
                switch (ulID)
                {
                    case    0x04000101:    ///日期
                        GetRealTime(&CommTim); 
                        memcpy(&CommTim.day,(&COMM_RECEIVE_WRITE_DATA)+1,3);
                                      
                        memcpy(&TmpClockBuffer,&CommTim.second,3);
                        memcpy(&TmpClockBuffer[3],&CommTim.day,3);
                        EvenProgramRecord(strRecordData,&TmpClockBuffer[0],6);
                      
                        SetRealTime(&CommTim);
                        // 广播校时记录清零
                        WriteCoefDataWithSync(&ucZeroArray[0],EPL_LAST_CHANNELS01_BROADCASTTIME,6);
                        break;

                    case  0x04000102:    ///时间
                        GetRealTime(&CommTim);
                        memcpy(&CommTim.second,&COMM_RECEIVE_WRITE_DATA,ReturnLenth);
                        memcpy(&TmpClockBuffer,&CommTim.second,3);
                        memcpy(&TmpClockBuffer[3],&CommTim.day,3);
                        EvenProgramRecord(strRecordData,&TmpClockBuffer[0],6);
                                    
                        SetRealTime(&CommTim);  
                        // 广播校时记录清零
                        WriteCoefDataWithSync(&ucZeroArray[0],EPL_LAST_CHANNELS01_BROADCASTTIME,6);
                                            
                        break;
                    case  0x04000701:    //调制通信速率特征字
                    //case  0x04000702:    //通信速率特征字
                    case  0x04000703:    //通信速率特征字1  
#if(CONFIG_METER_NO2COMM_MODE_RS485==CONFIG_METER_NO2COMM_MODE)
                    case  0x04000704:    //通信速率特征字2
#endif
#if(CONFIG_METER_NO2COMM_MODE_PLC==CONFIG_METER_NO2COMM_MODE)
                // --AA 不可以设置AA--
                    // case  0x04000704:    //通信速率特征字2
#endif
#if(CONFIG_METER_NO2COMM_MODE_WIRELESS==CONFIG_METER_NO2COMM_MODE)
                // --AA 不可以设置AA--
                //   case  0x04000704:    //通信速率特征字2
#endif
                //  case  0x04000705:    //通信速率特征字3
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
                                UartPotr.controlData=0;   ///波特率需要更改(发送完后更改)
                                return;
                            }
                            else
                            //------------------------------yaoxuxu  2009.11.08 ----end
                            {
                                if(TmpComm==GetExplainCommNo())
                                {
                                    UartPotr.controlData=2;   ///波特率需要更改(发送完后更改)
                                }
                                else
                                {
                              //      SetUART(TmpComm,&UartPotr.uartPara);
                              //      UartPotr.controlData=0;   ///波特率需要更改(发送完后更改)
                                }
                            }
                        }
                        else
                        {
                            CommExpDataBuff->Buffer[0]=BIT3;
                            ReturnBit=(COMMTYPE_WRITEDATA|BIT6)|BIT7;
                            ucLenth=1;
                            SetReturnDataFrame(ucLenth,ReturnBit);
                            UartPotr.controlData=0;   ///波特率需要更改(发送完后更改)
                            return;
                        }
                        //////修改第几通道的波特率
                        break;
#if(CONFIG_METER_NO2COMM_MODE_WIRELESS==CONFIG_METER_NO2COMM_MODE)
                // --AA 无线通信在线及信号强弱指示，不用记录 AA--
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
                    //////调用回调函数(刷新内容)
                    BackFunction();
                    ucLenth=0;
                    ReturnBit=COMMTYPE_WRITEDATA|BIT7;
                    break;
                case 3:////年时区数超
                    CommExpDataBuff->Buffer[0]=BIT4;
                    ucLenth=1;
                    ReturnBit=(COMMTYPE_WRITEDATA|BIT6)|BIT7;
                    break;
                case 4://///日时段数超
                    CommExpDataBuff->Buffer[0]=BIT5;
                    ucLenth=1;
                    ReturnBit=(COMMTYPE_WRITEDATA|BIT6)|BIT7;
                    break;
                case 5:////费率数超
                    CommExpDataBuff->Buffer[0]=BIT6;
                    ucLenth=1;
                    ReturnBit=(COMMTYPE_WRITEDATA|BIT6)|BIT7;
                    break;
                case 6:////密码错或未授权
                    CommExpDataBuff->Buffer[0]=BIT2;
                    ucLenth=1;
                    ReturnBit=(COMMTYPE_WRITEDATA|BIT6)|BIT7;
                    break;
             case 8:  //////无请求数据
                    CommExpDataBuff->Buffer[0]=BIT1;
                    ucLenth=1;
                    ReturnBit=(COMMTYPE_WRITEDATA|BIT6)|BIT7;
                break;
                case 7:  ////其他错误
                default:
                    CommExpDataBuff->Buffer[0]=BIT0;
                    ReturnBit=(COMMTYPE_WRITEDATA|BIT6)|BIT7;
                    ucLenth=1;
                    break;
            }
            
            SetReturnDataFrame(ucLenth,ReturnBit);
        }
}
