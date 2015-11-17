#define AP_POWERCOUNT_GLOBALS
#include "common.h"


#define EVENTKWH_ADD_FM GAL_NO
#define EVENTKWH_LOSSVOLTAGE_ADD_FM GAL_NO

// a--6  b--6 c--6
uchar ucSafeCheckUse[18];
#if 0
uchar ucEnergyPulseOutEnable;
void EnergyPulseOutEnable(uchar ucEnableFlg)
{
    ucEnergyPulseOutEnable=ucEnableFlg;
}
//有功能量脉冲输出
void PluseAddKwhInt(void)
{
    if(GAL_YES==IfPowerOn())
    {
        {
            if(GAL_YES==ucEnergyPulseOutEnable)
            {
                uiPluseCFKwh=800;
                SetPulseCFKwh();        //输出有功脉冲
                if((QUADRANT_ONE==QUADRANT_Z)||(QUADRANT_FOUR==QUADRANT_Z))
                {
                    SetPluseValue(PULSE_MODE_KWH_F,800);    //输出正向有功脉冲
                }
                else
                {
                    SetPluseValue(PULSE_MODE_KWH_R,800);    //输出反向有功脉冲
                }
            }
        }
    }
}

//无功能量脉冲输出
void PluseAddKvarhInt(void)
{
    // RFLAG_KVARH_C1_ADD=1;
    if(GAL_YES==IfPowerOn())
    {                           //有电下的处理
//      if((GAL_NO==GetReactivePulseStatus()))
        {
            if(GAL_YES==ucEnergyPulseOutEnable)
            {
                uiPluseCFkvarh=800;
                SetPulseCFKvarh();                                  //输出无功脉冲
                switch(QUADRANT_Z)
                {
                    case QUADRANT_TWO:
                        if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ2)
                        {
                            SetPluseValue(PULSE_MODE_KVARH_C1,800);//输出无功组合1脉冲
                        }
                        if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ2)
                        {
                            SetPluseValue(PULSE_MODE_KVARH_C2,800);//输出无功组合2脉冲
                        }
                        SetPluseValue(PULSE_MODE_KVARH_Q2,800);     //输出二象限无功脉冲
                        break;
                    case QUADRANT_THREE:
                        if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ3)
                        {
                            SetPluseValue(PULSE_MODE_KVARH_C1,800);//输出无功组合1脉冲
                        }
                        if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ3)
                        {
                            SetPluseValue(PULSE_MODE_KVARH_C2,800);//输出无功组合2脉冲
                        }
                        SetPluseValue(PULSE_MODE_KVARH_Q3,800);     //输出三象限无功脉冲
                        break;
                    case QUADRANT_FOUR:
                        if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ4)
                        {
                            SetPluseValue(PULSE_MODE_KVARH_C1,800);//输出无功组合1脉冲
                        }
                        if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ4)
                        {
                            SetPluseValue(PULSE_MODE_KVARH_C2,800);//输出无功组合2脉冲
                        }
                        SetPluseValue(PULSE_MODE_KVARH_Q4,800);     //输出四象限无功脉冲
                        break;
                    default:
                        if(uuReactiveMode01.Bit2DemandAdd.b2KvarQ1)
                        {
                            SetPluseValue(PULSE_MODE_KVARH_C1,800);//输出无功组合1脉冲
                        }
                        if(uuReactiveMode02.Bit2DemandAdd.b2KvarQ1)
                        {
                            SetPluseValue(PULSE_MODE_KVARH_C2,800);//输出无功组合2脉冲
                        }
                        SetPluseValue(PULSE_MODE_KVARH_Q1,800);     //输出一象限无功脉冲
                        break;
                }
            }
        }
    }
}

#endif


// if data ok, return 1;
// if data err , return 0;
//扫描所给的能量数据是否都为BCD码
uchar TestKwhBCD(uchar *ucPoint,uchar ucFlagSub)
{
    uchar ucTemp;
    if(4 != TestBcdNum(ucPoint, 4)) //所给的能量数据是否为4各字节的BCD码
        return 0;
    ucTemp=*(ucPoint+4);
    if(0!=ucFlagSub)
    {                               //能量为有符号数据
        ucTemp = 0x7f & ucTemp;     //将最高字节去掉符号位
    }
    if(1 != TestBcd(ucTemp))        //能量数据的最高字节为BCD码
        return 0;
    return 1;
}

// 对应电量重新校验一遍,每个能量数据5个字节后都有一个字节的校验的
// 同时进行BCD码校验
// return 0--ok,,1----/c err   2----/b err  3----/a err 4---all err
uchar Kwh3CopySafeCheck(uchar ucFlagSub)
{
    uchar a;//,b,c,ab,ac,bc;
    uchar l,l1,l2;
    //uchar lll;
    // a   bcd jiao
    l1=0;
    for(l=0;l<5;l++)
    {
        l1=l1+ucSafeCheckUse[l];
    }
    l1=l1+0x33;
    l2=TestKwhBCD(&ucSafeCheckUse[0],ucFlagSub);
    if(l1!=ucSafeCheckUse[5]) 
        l2 = 0;                         //能量数据校验不成功
    a=l2;
    return (a!=1);
#if 0    
    // b bcd jiao
    l1=0;
    for(l=6;l<11;l++)
    {
        l1=l1+ucSafeCheckUse[l];
    }
    l1=l1+0x33;
    l2=TestKwhBCD(&ucSafeCheckUse[6],ucFlagSub);
    if(l1!=ucSafeCheckUse[11]) 
        l2=0; 
    b=l2;
    // c bcd jiao
    l1=0;
    for(l=12;l<17;l++)
    {
        l1=l1+ucSafeCheckUse[l];
    }
    l1=l1+0x33;
    l2=1; 
    if(l1!=ucSafeCheckUse[17])
        l2=0; 
    c=l2;
    // ab
    l2=1;
    for(l=0;l<5;l++)
        if(ucSafeCheckUse[l]!=ucSafeCheckUse[l+6]) l2=0;
    ab=l2;
    // a=c
    l2=1;
    for(l=0;l<5;l++)
    {
        lll=(~ucSafeCheckUse[l+12]);
        if(ucSafeCheckUse[l]!=lll) 
            l2=0;
    }
    ac=l2;
    // b=c
    l2=1;
    for(l=0;l<5;l++)
    {
        lll=(~ucSafeCheckUse[l+12]);
        if(ucSafeCheckUse[l+6]!=lll) l2=0;
    }
    bc=l2;
    if(6==a+b+c+ab+bc+ac) 
    {
        return KWH_CHECK_ALL_OK;  //ok
    }
    else
    {
        if(3==a+b+ab) 
            return KWH_CHECK_C_ERR;   // c err
        else 
        {
            if(3==a+c+ac) 
                return KWH_CHECK_B_ERR;  // b err
            else
            {
                if(3==b+c+bc) 
                    return KWH_CHECK_A_ERR; // a err
                else 
                    return KWH_CHECK_ALL_ERR;   // all err
            }
        }
    }
#endif    
}

#if 0
void  KwhErrEventRecord(void )
{
    ulong ulAddr;
    //if(CON_KWH_ERR_EVENT_RECORD_START==ucKwhErrEventRecordMode)
    {
        //ucKwhErrEventRecordMode=CON_KWH_ERR_EVENT_RECORD_END;
        
        ulAddr=SetTwoTableNextPoint(TYPE_ERR_POWER_RECORD);
        if(GAL_GETTWOTABLE_ADDRERR != ulAddr)
        {
            SetTimeDataToPoint(&Wr_data[0]);
            memcpy(&Wr_data[6], &RAM[RAM_KWH_ALL_START], 512-6);
            WriteDataDirect(&Wr_data[0], ulAddr, 512);
            memcpy(&Wr_data[0], &RAM[RAM_KWH_ALL_START+512-6], 509);
            WriteDataDirect(&Wr_data[0], ulAddr+512, 509);          
        }
        ClrFlashMode();
    }
}
#endif

#if 1
// 正常运行过程中，电量出错，使用上1分钟保存的电量恢复
// 如果上1分钟保存的电量也出错，使用E2P上一次保存的电量
uchar KwhPowerOnSafeCheck(uchar ucKwhType,uchar ucFlagSub)
{
    uchar ucRamCheckValue/*,ucEplCheckValue,v2*/;
    u16 l0;
    uchar temp;         // 1，使用flash电量失败标识；0，成功
    //ulong ulAddr;

    temp = 1;
    for(l0=0;l0<5;l0++)
        ucSafeCheckUse[l0]=RAM[RAM_KWH_ALL_START+l0+ucKwhType*5];
    ucSafeCheckUse[5]=uKwhACopyCheck[ucKwhType];
    ucRamCheckValue=Kwh3CopySafeCheck(ucFlagSub);
    // 电量数据有误
    if(ucRamCheckValue!=0)
    {
        KwhResume();
    }
    
/*  if(uValueCheck==0) 
    {
        // RAM[inside_chech]=0x99;
        ;
    }
    else
    {
        //  AA  之前所有的恢复，仍然失败，则自能自检数据  AA
        if(1!=TestKwhBCD(&RAM[RAM_KWH_ALL_START+5*ucKwhType],ucFlagSub))
        {
            for(l=0;l<4;l++)
            {
                m=ValueHexFromBcd(RAM[RAM_KWH_ALL_START+5*ucKwhType+l])%100;
                RAM[RAM_KWH_ALL_START+5*ucKwhType+l]=ValueBcdFromHex(m);
            }
            m=RAM[RAM_KWH_ALL_START+5*ucKwhType+4];
            if(0x80==(0x80&m))
            {
                m=0x7f&m;
                m=ValueHexFromBcd(m)%100;
                m=ValueBcdFromHex(m);
                if(1==ucFlagSub)
                {
                    m=m|0x80;
                }
            }
            else
            {
                m=ValueHexFromBcd(m)%100;
                m=ValueBcdFromHex(m);
            }
            RAM[RAM_KWH_ALL_START+5*ucKwhType+4]=m;
        }
    }
*/
    return 0;
}
#else
uchar KwhPowerOnSafeCheck(uchar ucKwhType,uchar ucFlagSub)
{
        return 0;
#if 0
        uchar l0, ucRamCheckValue,ucFmCheckValue,uValueCheck,l,v2,m;
        uchar ucNeedResume;
        ucNeedResume=KWH_CHECK_ALL_OK;
        for(l0=0;l0<5;l0++)
            ucSafeCheckUse[l0]=RAM[RAM_KWH_ALL_START+l0+ucKwhType*5];
        ucSafeCheckUse[5]=uKwhACopyCheck[ucKwhType];
        for(l0=0;l0<6;l0++)
            ucSafeCheckUse[l0+6]=uKwhBCopyData[ucKwhType][l0];
        for(l0=0;l0<6;l0++)
            ucSafeCheckUse[l0+12]=uKwhCCopyData[ucKwhType][l0];
        ucRamCheckValue=Kwh3CopySafeCheck(ucFlagSub);
        uValueCheck=ucRamCheckValue;
        if(ucRamCheckValue!=0)
        {
            KwhErrEventRecord();
            // RAM[inside_chech]=0x1;
            v2=ReadDataDirect(EPL_KWH_ALL_START+ucKwhType*5,5,&ucSafeCheckUse[0]);
            v2=v2+ReadDataDirect(EPL_KWH_ALL_CHECK_START+ucKwhType,1,&ucSafeCheckUse[5]);
            v2=v2+ReadDataDirect(EPL_KWH_ALL_BCOPY_START+ucKwhType*6,6,&ucSafeCheckUse[6]);
            v2=v2+ReadDataDirect(EPL_KWH_ALL_CCOPY_START+ucKwhType*6,6,&ucSafeCheckUse[12]);
            ucFmCheckValue=Kwh3CopySafeCheck(ucFlagSub);
            if(v2!=4) 
                ucFmCheckValue=KWH_CHECK_ALL_ERR;
            if(ucFmCheckValue==0) 
            {
                for(l0=0;l0<5;l0++)
                    RAM[RAM_KWH_ALL_START+l0+ucKwhType*5]=ucSafeCheckUse[l0];
                uKwhACopyCheck[ucKwhType]=ucSafeCheckUse[5];
            }
            else
            {
                // RAM[inside_chech]=0x2;
                if(ucRamCheckValue==KWH_CHECK_ALL_ERR)
                {// err   fm---->
                    switch(ucFmCheckValue)
                    {
                        case KWH_CHECK_C_ERR:  //ab ok  
                        case KWH_CHECK_B_ERR:  //ac ok
                            for(l0=0;l0<5;l0++)
                                RAM[RAM_KWH_ALL_START+l0+ucKwhType*5]=ucSafeCheckUse[l0];
                            uKwhACopyCheck[ucKwhType]=ucSafeCheckUse[5];
                            break;
                        case KWH_CHECK_A_ERR:  // bc ok
                            for(l0=0;l0<5;l0++)
                                RAM[RAM_KWH_ALL_START+l0+ucKwhType*5]=ucSafeCheckUse[l0+6];
                            uKwhACopyCheck[ucKwhType]=ucSafeCheckUse[11];
                            break;
                        default:
                            ucNeedResume=KWH_CHECK_ALL_ERR;
                            break;
                    }
                }
                else
                {
                    switch(ucRamCheckValue)
                    {
                        case KWH_CHECK_C_ERR:
                            // ab ok
                        case KWH_CHECK_B_ERR: 
                            // ac ok
                            break;
                        case KWH_CHECK_A_ERR:  
                            // bc ok
                            for(l0=0;l0<5;l0++)
                                RAM[RAM_KWH_ALL_START+l0+ucKwhType*5]=uKwhBCopyData[ucKwhType][l0];
                            uKwhACopyCheck[ucKwhType]=uKwhBCopyData[ucKwhType][5];
                            break;
                        default: 
                            ucNeedResume=KWH_CHECK_ALL_ERR;
                            break;
                    }
                }
            }
        }
        if(uValueCheck==0) 
        {
            // RAM[inside_chech]=0x99;
            ;
        }
        else
        {
        #if 0
            //  AA  因为RAM 中和 FM中都不存在可以信赖的数据  AA
            //   AA    所以，数据从新从flash 中恢复  AA
            //   AA   从每小时的数据和每日的数据中恢复    AA
            if(KWH_CHECK_ALL_ERR==ucNeedResume)
            {
                // find  kwh data from last  1hour data
                ReadDataDirect(FL1_LAST_PER_HOUR_POWER+ucKwhType*6,6,&ucSafeCheckUse[0]);
                l0==TestKwhBCD(&ucSafeCheckUse[0],ucFlagSub);
                m=0;
                for(l=0;l<5;l++)
                {
                    m=m+ucSafeCheckUse[l];
                }
                if(m!=ucSafeCheckUse[5]) 
                    l0=0;
                if(1==l0)
                {
                    for(l0=0;l0<5;l0++)
                        RAM[RAM_KWH_ALL_START+l0+ucKwhType*5]=ucSafeCheckUse[l0];
                    uKwhACopyCheck[ucKwhType]=ucSafeCheckUse[5];
                }
                else
                {
                    // find  kwh data from last  day data
                    ReadDataDirect(FL1_LAST_PER_DAY_POWER+ucKwhType*6,6,&ucSafeCheckUse[0]);
                    l0==TestKwhBCD(&ucSafeCheckUse[0],ucFlagSub);
                    m=0;
                    for(l=0;l<5;l++)
                    {
                        m=m+ucSafeCheckUse[l];
                    }
                    if(m!=ucSafeCheckUse[5]) 
                        l0=0;
                    if(1==l0)
                    {
                        for(l0=0;l0<5;l0++)
                            RAM[RAM_KWH_ALL_START+l0+ucKwhType*5]=ucSafeCheckUse[l0];
                        uKwhACopyCheck[ucKwhType]=ucSafeCheckUse[5];
                    }
                }
            }
        #endif
            //  AA  之前所有的恢复，仍然失败，则自能自检数据  AA
            if(1!=TestKwhBCD(&RAM[RAM_KWH_ALL_START+5*ucKwhType],ucFlagSub))
            {
                for(l=0;l<4;l++)
                {
                    m=ValueHexFromBcd(RAM[RAM_KWH_ALL_START+5*ucKwhType+l])%100;
                    RAM[RAM_KWH_ALL_START+5*ucKwhType+l]=ValueBcdFromHex(m);
                }
                m=RAM[RAM_KWH_ALL_START+5*ucKwhType+4];
                if(0x80==(0x80&m))
                {
                    m=0x7f&m;
                    m=ValueHexFromBcd(m)%100;
                    m=ValueBcdFromHex(m);
                    if(1==ucFlagSub)
                    {
                        m=m|0x80;
                    }
                }
                else
                {
                    m=ValueHexFromBcd(m)%100;
                    m=ValueBcdFromHex(m);
                }
                RAM[RAM_KWH_ALL_START+5*ucKwhType+4]=m;
            }
        }
        return uValueCheck;
#endif
}
#endif


//从E2P中恢复
// 正常恢复，返回0；异常，返回1
uchar KwhPowerOnResume(uchar ucKwhType,uchar ucFlagSub)
{
    uchar l0, v2;

    v2=ReadDataDirect(EPL_KWH_ALL_START+ucKwhType*5,5,&ucSafeCheckUse[0]);
    v2=v2+ReadDataDirect(EPL_KWH_ALL_CHECK_START+ucKwhType,1,&ucSafeCheckUse[5]);
    if(v2==2)
    { 
        v2=0x33;
        for(l0=0;l0<5;l0++)
        {
            v2+=ucSafeCheckUse[l0];
        }
        if(v2==ucSafeCheckUse[5])
        {
            #if 0
            for(l0=0;l0<5;l0++)
                RAM[RAM_KWH_ALL_START+l0+ucKwhType*5]=ucSafeCheckUse[l0];
            #endif
            memcpy(&RAM[RAM_KWH_ALL_START+ucKwhType*5], &ucSafeCheckUse[0], 5);
            uKwhACopyCheck[ucKwhType]=ucSafeCheckUse[5];
            return 0;
        }
    }
    return 1;
}

void KwhUsePowerOnResume(void)
{
    ReadDataDirect(EPL_KWH_ALL_USE_START, 5*5*2, &RAM[RAM_KWH_ALL_USE_START]);
}

/* dev/mtdblock6已经mount上，返回1, 否则返回0 */
static int check_mount(void)
{	
	FILE *fp;	
	char buf[1024];		
	
	fp = fopen("/proc/mounts", "r");	
	if (fp == NULL) {		
		perror("open /proc/mounts");	
		return 0;	
	}		
	while(fgets(buf, sizeof(buf), fp)) {		
		if (strstr(buf, "/dev/mtdblock6")) {	
			fclose(fp);	
			return 1;				
		}
	}			
	fclose(fp);	
	return 0;
}

// 从外部存储器中恢复电量到内存
//调用条件: 正常上电或者激活
void KwhResume(void)
{
    u32 ulSec1, ulSec2, ulAddr;
    u8 ret, TryTimes, LastTimes;
    u16 i, idx;
    

	
    //KwhUsePowerOnResume();
    ulSec2 = 0;
    TryTimes = 0;
    LastTimes = 0;
    ReadDataDirect(EPL_KWH_ALL_END+1,4,(u8*)&ulSec1);

	if (ulSec1 != 0xffffffff) { //E2停电时没有保存
		//需要等待/mnt就绪，否则无法读取/mnt/dbf/flash.dat, 这样会造成不带电池下电时，电量丢失
		while(1) {
			if (check_mount()) break;
			usleep(100000);
		}

	    ulAddr=GetTwoTableAddrFromBlock(TYPE_MIN_POWER_RECORD, LastTimes++, 0);
    	if(GAL_GETTWOTABLE_ADDRERR != ulAddr)
    	{
        	ReadDataDirect(ulAddr+BYTES_KWH_TOTAL+1,4,(u8*)&ulSec2);

    	}
	}
    LOGTRACE("KwhResume ulSec1 = %lx, ulSec2 = %lx !\n", ulSec1, ulSec2);
    while(TryTimes <= 20)
    {
        if(ulSec1 >= ulSec2)
        {
			LOGTRACE("restore kwh from E2PROM!!\n");
            ret=ReadDataDirect(EPL_KWH_ALL_START, BYTES_KWH_TOTAL, &RAM[RAM_KWH_ALL_START]);
            ret=ret+ReadDataDirect(EPL_KWH_ALL_CHECK_START, PT_KWH_TOTAL, &uKwhACopyCheck[0]);
            if(ret==2)
            { 
                for(idx=0; idx<PT_KWH_TOTAL; idx++)
                {
                    ret=0x33;
                    for(i=0; i<5; i++)
                    {
                        ret += RAM[RAM_KWH_ALL_START+idx*5+i];
                    }
                    if(ret != uKwhACopyCheck[idx])
                    {
                    	ERRTRACE("EPL checksum is error!, index = %d\n", idx);
						if (ulSec1 == 0xffffffff) { 
							//需要等待/mnt就绪，否则无法读取/mnt/dbf/flash.dat, 这样会造成不带电池下电时，电量丢失
							while(1) {
								if (check_mount()) break;
								usleep(100000);
							}

						    ulAddr=GetTwoTableAddrFromBlock(TYPE_MIN_POWER_RECORD, LastTimes++, 0);
					    	if(GAL_GETTWOTABLE_ADDRERR != ulAddr)
					    	{
					        	ReadDataDirect(ulAddr+BYTES_KWH_TOTAL+1,4,(u8*)&ulSec2);

					    	}
						}						
                        ulSec1 = 0;
                        break;
                    }
                }
                if(idx >= PT_KWH_TOTAL)
                {
                    //finished to resume successfully
                    LOGTRACE("Resume Kwh from EPL successfully !\n");
                    return;
                }
            }
            else
            {
				if (ulSec1 == 0xffffffff) { 
					//需要等待/mnt就绪，否则无法读取/mnt/dbf/flash.dat, 这样会造成不带电池下电时，电量丢失
					while(1) {
						if (check_mount()) break;
						usleep(100000);
					}
				
					ulAddr=GetTwoTableAddrFromBlock(TYPE_MIN_POWER_RECORD, LastTimes++, 0);
					if(GAL_GETTWOTABLE_ADDRERR != ulAddr)
					{
						ReadDataDirect(ulAddr+BYTES_KWH_TOTAL+1,4,(u8*)&ulSec2);
				
					}
				}						
                ulSec1 = 0;
            }
        }
        else
        {
			LOGTRACE("restore kwh from FLASH!!\n");
            ReadDataDirect(ulAddr,BYTES_KWH_TOTAL+1,&Wr_data[0]);
            for(ret=0x33,i=0;i<BYTES_KWH_TOTAL;i++)
            {
                ret += Wr_data[i];
            }
            if((ret == Wr_data[BYTES_KWH_TOTAL])&&(TestBcdNum2(&Wr_data[0], BYTES_KWH_TOTAL) == BYTES_KWH_TOTAL))
            {
                memcpy(&RAM[RAM_KWH_ALL_START],&Wr_data[0],BYTES_KWH_TOTAL);
                for(idx=0;idx<PT_KWH_TOTAL;idx++)
                {
                    WritePower3Copy(idx);
                }
                //finished to resume successfully
                LOGTRACE("Resume Kwh from MIN rec [%d] successfully !\n", LastTimes-1);
                return;
            }
            else
            {
                ulAddr=GetTwoTableAddrFromBlock(TYPE_MIN_POWER_RECORD, LastTimes++, 0);
                if(GAL_GETTWOTABLE_ADDRERR != ulAddr)
                {
                    ReadDataDirect(ulAddr+BYTES_KWH_TOTAL+1,4,(u8*)&ulSec2);

                }
                else
                {
                    break;
                }
            }
        }
        TryTimes++;
    }

    //恢复失败
    ErrPrint("God!, Resume Kwh %d failed\n");
    memset(&RAM[RAM_KWH_ALL_START],0,BYTES_KWH_TOTAL);
    memset(&uKwhACopyCheck[0],0,PT_KWH_TOTAL);
    FLG_SAVE_EC = 1;
}
void KwhResume1(void)
{
    uchar ucKwhTpye,ucK;
    uchar ucEplCheckValue;
    u16 l0;
    ulong ulAddr;

    memset(&RAM[RAM_DLT_UNSUPPORT_DATA], 0xFF, BYTES_PER_PT_KWH);
    KwhUsePowerOnResume();
    //ucKwhErrEventRecordMode=CON_KWH_ERR_EVENT_RECORD_START;
    for(ucKwhTpye=0;ucKwhTpye<PT_KWH_TOTAL;ucKwhTpye++)
    {
        for(ucK=0;ucK<PT_KWH_TOTAL;ucK++)
        {
            if(ucKwhTpye==TB_KWH_RESUME_CAN_SUB[ucK].stKwhTpye)
            {
                if(KWH_CHECK_ALL_OK!=KwhPowerOnResume(ucKwhTpye,TB_KWH_RESUME_CAN_SUB[ucK].stCanSub))
                {
                    ErrPrint("God!, Resume Kwh %d fail by EPL ! %s-%d\n", ucKwhTpye,  __FUNCTION__, __LINE__);
                    /*Start of ybf on 2011-2-14 15:49 pax */
                    // E2P电量出错，用上一分钟保存的电量恢复内存中和e2p中的电量
                    // 如果外部存储器的电量也出错，电量清零
                    ulAddr=GetTwoTableAddrFromBlock(TYPE_MIN_POWER_RECORD,0,0);
                    if(GAL_GETTWOTABLE_ADDRERR != ulAddr)
                    {
                        ReadDataDirect(ulAddr,BYTES_KWH_TOTAL+1,&Wr_data[0]);
                        for(ucEplCheckValue=0x33,l0=0;l0<BYTES_KWH_TOTAL;l0++)
                        {
                            ucEplCheckValue += Wr_data[l0];
                        }
                        if((ucEplCheckValue == Wr_data[BYTES_KWH_TOTAL])&&(TestBcdNum2(&Wr_data[0], BYTES_KWH_TOTAL) == BYTES_KWH_TOTAL))
                        {
                            memcpy(&RAM[RAM_KWH_ALL_START],&Wr_data[0],BYTES_KWH_TOTAL);
                            for(l0=0;l0<PT_KWH_TOTAL;l0++)
                            {
                                WritePower3Copy(l0);
                            }
                        }
                        else
                        {
                            memset(&RAM[RAM_KWH_ALL_START],0,BYTES_KWH_TOTAL);
                            memset(&uKwhACopyCheck[0],0x33,PT_KWH_TOTAL);
                        }

                    }
                    else
                    {
                        memset(&RAM[RAM_KWH_ALL_START],0,BYTES_KWH_TOTAL);
                        memset(&uKwhACopyCheck[0],0x33,PT_KWH_TOTAL);
                    }
                    WriteDataDirect(&RAM[RAM_KWH_ALL_START], EPL_KWH_ALL_START,  BYTES_KWH_TOTAL);
                    WriteDataDirect(&uKwhACopyCheck[0], EPL_KWH_ALL_CHECK_START, PT_KWH_TOTAL);
                    /*End of ybf on 2011-2-14 15:49 pax */
                    FLG_SAVE_EC = 0;
                    ClearWatchDog();
                    return;
                }
                ucK=PT_KWH_TOTAL;
            }
        }
    }
    g_KwhSavedMode = KWH_SAVED_MODE_INIT;
    //ucKwhErrEventRecordMode=CON_KWH_ERR_EVENT_RECORD_END;

}






// 电量分类型校验
uchar WritePower3Copy(uchar ucKwhType)
{
    uchar l,l1;

    // ram a jiao
    l1=0;
    for(l=0;l<5;l++)
        l1=l1+RAM[RAM_KWH_ALL_START+5*ucKwhType+l];
    uKwhACopyCheck[ucKwhType]=l1+0x33;

    FLG_SAVE_EC = 1;
    return 1;
}
//--AA 将电量数据保存到非易失存储器 AA--
uchar WritePower2rom(uchar ucKwhType)
{
    /*uchar l,checksum;

    // ram a jiao
    checksum=0;
    for(l=0;l<5;l++)
        checksum += RAM[RAM_KWH_ALL_START+5*ucKwhType+l];
    uKwhACopyCheck[ucKwhType]=checksum+0x33;
    */
    
    // write fm fm1
    if(0xff == ucKwhType)
    {
        memset(&RAM[RAM_KWH_ALL_END+1], 0xFF, 4);
        WriteDataDirect(&RAM[RAM_KWH_ALL_START], EPL_KWH_ALL_START,  BYTES_KWH_TOTAL+5);
        WriteDataDirect(&uKwhACopyCheck[0], EPL_KWH_ALL_CHECK_START, PT_KWH_TOTAL);
        LOGTRACE("Kwh Poweroff saved\n");
    }
    else
    {
        WriteDataDirect(&RAM[RAM_KWH_ALL_START+5*ucKwhType],EPL_KWH_ALL_START+BYTES_PER_PT_KWH*ucKwhType,  BYTES_PER_PT_KWH);
        WriteDataDirect(&uKwhACopyCheck[ucKwhType],EPL_KWH_ALL_CHECK_START+ucKwhType,  1);
    }
    return 1;
}

//--AA 将结算日电量数据保存到非易失存储器 AA--
uchar WriteAlluse2rom(void)
{
    //WriteDataDirect(&RAM[RAM_KWH_ALL_USE_START],EPL_KWH_ALL_USE_START,5*5);
    //WriteDataDirect(&RAM[RAM_KWH_F_AND_R_ALL],EPL_KWH_F_AND_R_ALL,5*5);
    WriteDataDirect(&RAM[RAM_KWH_ALL_USE_START], EPL_KWH_ALL_USE_START,5*5*2);
    return 1;
}


void KwhRamAdd10Data(ulong ulRamAddr,u16 uiData)
{
    ulong ulTemp;
    ulTemp=Bcd5DataToLong(&RAM[ulRamAddr])+uiData*1;
    LongToData5BCD(ulTemp,&RAM[ulRamAddr]);
}

void KwhAddIntDataFromType(uchar ucKwhType,u16 uiData)
{
    KwhPowerOnSafeCheck(ucKwhType,0);
    KwhRamAdd10Data(RAM_KWH_ALL_START+5*ucKwhType,uiData);
    WritePower3Copy(ucKwhType);
    
}


// 电量总清
void KwhAllDataClr(void)
{
    u16 uiTemp;
    uchar *ucPoint;
    uiTemp=PT_KWH_TOTAL;
    uiTemp=5*uiTemp;
    ucPoint=&RAM[RAM_KWH_ALL_START];
    // 内存和E2P中的电量清零
    memset(ucPoint, 0x00, uiTemp);
    WriteDataDirect(ucPoint,EPL_KWH_ALL_START, uiTemp);
 
    //  内存和E2P中的电量校验和清零
    memset(&uKwhACopyCheck[0],0x33,PT_KWH_TOTAL);
    WriteDataDirect(&uKwhACopyCheck[0],EPL_KWH_ALL_CHECK_START,PT_KWH_TOTAL);

    // 尾数清零
    PowerClacResidueClr();
    

    // clr All use kwh
    memset(&RAM[RAM_KWH_ALL_USE_START], 0x00, BYTES_KWH_USE_TOTAL);
    WriteDataDirect(&RAM[RAM_KWH_ALL_USE_START],  EPL_KWH_ALL_USE_START, BYTES_KWH_USE_TOTAL);
    memset(&RAM[RAM_KWH_F_AND_R_START], 0x00, BYTES_KWH_F_AND_R_TOTAL);
    WriteDataDirect(&RAM[RAM_KWH_F_AND_R_START],  EPL_KWH_F_AND_R_START, BYTES_KWH_F_AND_R_TOTAL);
}






typedef struct
{
    uchar ucKwhType;
    uchar ucAddType;
    uchar  ucOffset;
    uchar ucPriceHave;
}ST_POWER_ADD_DATA_PARAM;
typedef  void  (*FunctioNoRe)(ST_POWER_ADD_DATA_PARAM *stAdd);  
typedef struct
{
    FunctioNoRe callBack;
    ST_POWER_ADD_DATA_PARAM stAddData;
}ST_POWER_ADD_PARAM;


ulLong Bcd5DataToLLong(uchar *Ptr);
void LLongToData5BCD(ulLong value,uchar *point);
void KwhRamAddTypeAddOnly(u16 uiRamAddr,uchar ucKwhAddrData);
void KwhRamAddTypeAddSub(u16 uiRamAddr,uchar ucKwhAddrData);
void KwhRamSubTypeAddSub(u16 uiRamAddr,uchar ucKwhAddrData);
void KwhAddDataAddOnly(uchar ucKwhType,uchar ucKwhAddData);
void KwhAddDataAddSub(uchar ucKwhType,uchar ucKwhAddData);
void KwhSubDataAddSub(uchar ucKwhType,uchar ucKwhAddData);
void KwhFmAddTypeAddOnly(ulong ulFmAddr,uchar ucKwhAddrData);
void KwhFmAddTypeAddSub(ulong ulFmAddr,uchar ucKwhAddrData);
void KwhFmSubTypeAddSub(ulong ulFmAddr,uchar ucKwhAddrData);
void KwhEventKwhAddTypeAddOnly(uchar  ucOffset,uchar ucKwhAddrData);
void KwhEventKwhAddTypeAddSub(uchar  ucOffset,uchar ucKwhAddrData);
void KwhEventKwhSubTypeAddSub(uchar  ucOffset,uchar ucKwhAddrData);
void KwhAddTypeAddOnly(ST_POWER_ADD_DATA_PARAM *stAddData);
void KwhAddTypeAddSub(ST_POWER_ADD_DATA_PARAM *stAddData);
void KwhSubTypeAddSub(ST_POWER_ADD_DATA_PARAM *stAddData);
void KwhNoAddType(ST_POWER_ADD_DATA_PARAM *stAddData);
void KwhAdd0D01Event(ulong ulLastKwh);



#define CON_KWH_ADD_EVENT_KWH_ALL_F_SOS     (0*5)
#define CON_KWH_ADD_EVENT_KWH_ALL_R_SOS     (1*5)
#define CON_KWH_ADD_EVENT_KVARH_ALL_C1_SOS  (2*5)
#define CON_KWH_ADD_EVENT_KVARH_ALL_C2_SOS  (3*5)
#define CON_KWH_ADD_EVENT_KVARH_ALL_Q1_SOS  (4*5)
#define CON_KWH_ADD_EVENT_KVARH_ALL_Q2_SOS  (5*5)
#define CON_KWH_ADD_EVENT_KVARH_ALL_Q3_SOS  (6*5)
#define CON_KWH_ADD_EVENT_KVARH_ALL_Q4_SOS  (7*5)
#define CON_KWH_ADD_EVENT_KWH_A_F_SOS       (8*5)
#define CON_KWH_ADD_EVENT_KWH_A_R_SOS       (9*5)
#define CON_KWH_ADD_EVENT_KVARH_A_C1_SOS    (10*5)
#define CON_KWH_ADD_EVENT_KVARH_A_C2_SOS    (11*5)
#define CON_KWH_ADD_EVENT_KWH_B_F_SOS       (12*5)
#define CON_KWH_ADD_EVENT_KWH_B_R_SOS       (13*5)
#define CON_KWH_ADD_EVENT_KVARH_B_C1_SOS    (14*5)
#define CON_KWH_ADD_EVENT_KVARH_B_C2_SOS    (15*5)
#define CON_KWH_ADD_EVENT_KWH_C_F_SOS       (16*5)
#define CON_KWH_ADD_EVENT_KWH_C_R_SOS       (17*5)
#define CON_KWH_ADD_EVENT_KVARH_C_C1_SOS    (18*5)
#define CON_KWH_ADD_EVENT_KVARH_C_C2_SOS    (19*5)

#define CON_KWH_ADD_EVENT_KWH_NOHAVE 0xFF


const ST_POWER_ADD_PARAM TB_POWER_ADD_BUFFER[]=
{
#if (CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE_ENABLE == CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE)
    {&KwhAddTypeAddOnly, POWER_KW_F_ALL_DATA,    PT_KWH_F_ALL,   CON_KWH_ADD_EVENT_KWH_ALL_F_SOS ,   GAL_NO}}, // AA 当前正向有功总电量计算累加 AA 
    {&KwhAddTypeAddOnly, POWER_KW_R_ALL_DATA,    PT_KWH_R_ALL,   CON_KWH_ADD_EVENT_KWH_ALL_R_SOS ,   GAL_NO}}, // AA 当前反向有功总电量计算累加 AA 
#else
    {&KwhAddTypeAddOnly, {POWER_KW_F_ALL_DATA,    PT_KWH_F_ALL,   CON_KWH_ADD_EVENT_KWH_ALL_F_SOS ,   GAL_YES}}, // AA 当前正向有功总电量计算累加 AA 
    {&KwhAddTypeAddOnly, {POWER_KW_R_ALL_DATA,    PT_KWH_R_ALL,   CON_KWH_ADD_EVENT_KWH_ALL_R_SOS ,   GAL_YES}}, // AA 当前反向有功总电量计算累加 AA 
#endif
    {&KwhAddTypeAddOnly, {POWER_KVAR_Q1_ALL_DATA, PT_KVARH_Q1_ALL,    CON_KWH_ADD_EVENT_KVARH_ALL_Q1_SOS, GAL_YES}}, // AA 当前1象限无功总电量计算累加 AA 
    {&KwhAddTypeAddOnly, {POWER_KVAR_Q2_ALL_DATA, PT_KVARH_Q2_ALL,    CON_KWH_ADD_EVENT_KVARH_ALL_Q2_SOS, GAL_YES}}, // AA 当前2象限无功总电量计算累加 AA 
    {&KwhAddTypeAddOnly, {POWER_KVAR_Q3_ALL_DATA, PT_KVARH_Q3_ALL,    CON_KWH_ADD_EVENT_KVARH_ALL_Q3_SOS, GAL_YES}}, // AA 当前3象限无功总电量计算累加 AA 
    {&KwhAddTypeAddOnly, {POWER_KVAR_Q4_ALL_DATA, PT_KVARH_Q4_ALL,    CON_KWH_ADD_EVENT_KVARH_ALL_Q4_SOS, GAL_YES}}, // AA 当前4象限无功总电量计算累加 AA 
	{&KwhAddTypeAddOnly, {POWER_KVA_F_ALL_DATA,	PT_KVAH_F_ALL,	CON_KWH_ADD_EVENT_KWH_NOHAVE,	GAL_YES}}, // AA 当前正向视在总电量计算累加 AA 
	{&KwhAddTypeAddOnly, {POWER_KVA_R_ALL_DATA,	PT_KVAH_R_ALL,	CON_KWH_ADD_EVENT_KWH_NOHAVE,	GAL_YES}}, // AA 当前反向视在总电量计算累加 AA 
    {&KwhAddTypeAddOnly, {POWER_KW_A_F_ALL_DATA,  PT_KWH_A_F_ALL, CON_KWH_ADD_EVENT_KWH_A_F_SOS,  GAL_NO}}, // AA 当前A相正相有功电量计算累加 AA 
    {&KwhAddTypeAddOnly, {POWER_KW_A_R_ALL_DATA,  PT_KWH_A_R_ALL, CON_KWH_ADD_EVENT_KWH_A_R_SOS,  GAL_NO}}, // AA 当前A相反相有功电量计算累加 AA 
	{&KwhAddTypeAddOnly, {POWER_KVAR_A_Q1_ALL_DATA,	PT_KVARH_A_Q1_ALL,	CON_KWH_ADD_EVENT_KWH_NOHAVE,	GAL_NO}}, // AA 当前A相1象限无功电量计算累加 AA 
	{&KwhAddTypeAddOnly, {POWER_KVAR_A_Q2_ALL_DATA,	PT_KVARH_A_Q2_ALL,	CON_KWH_ADD_EVENT_KWH_NOHAVE,	GAL_NO}}, // AA 当前A相2象限无功电量计算累加 AA 
	{&KwhAddTypeAddOnly, {POWER_KVAR_A_Q3_ALL_DATA,	PT_KVARH_A_Q3_ALL,	CON_KWH_ADD_EVENT_KWH_NOHAVE,	GAL_NO}}, // AA 当前A相3象限无功电量计算累加 AA 
	{&KwhAddTypeAddOnly, {POWER_KVAR_A_Q4_ALL_DATA,	PT_KVARH_A_Q4_ALL,	CON_KWH_ADD_EVENT_KWH_NOHAVE,	GAL_NO}}, // AA 当前A相4象限无功电量计算累加 AA 
	{&KwhAddTypeAddOnly, {POWER_KVA_A_F_ALL_DATA,	PT_KVAH_A_F_ALL,	CON_KWH_ADD_EVENT_KWH_NOHAVE,	GAL_NO}}, // AA 当前A相正相视在电量计算累加 AA 
	{&KwhAddTypeAddOnly, {POWER_KVA_A_R_ALL_DATA,	PT_KVAH_A_R_ALL,	CON_KWH_ADD_EVENT_KWH_NOHAVE,	GAL_NO}}, // AA 当前A相反相视在电量计算累加 AA 
    {&KwhAddTypeAddOnly, {POWER_KW_B_F_ALL_DATA,  PT_KWH_B_F_ALL, CON_KWH_ADD_EVENT_KWH_B_F_SOS,  GAL_NO}}, // AA 当前B相正相有功电量计算累加 AA 
    {&KwhAddTypeAddOnly, {POWER_KW_B_R_ALL_DATA,  PT_KWH_B_R_ALL, CON_KWH_ADD_EVENT_KWH_B_R_SOS,  GAL_NO}}, // AA 当前B相反相有功电量计算累加 AA 
	{&KwhAddTypeAddOnly, {POWER_KVAR_B_Q1_ALL_DATA,	PT_KVARH_B_Q1_ALL,	CON_KWH_ADD_EVENT_KWH_NOHAVE,	GAL_NO}}, // AA 当前B相1象限无功电量计算累加 AA 
	{&KwhAddTypeAddOnly, {POWER_KVAR_B_Q2_ALL_DATA,	PT_KVARH_B_Q2_ALL,	CON_KWH_ADD_EVENT_KWH_NOHAVE,	GAL_NO}}, // AA 当前B相2象限无功电量计算累加 AA 
	{&KwhAddTypeAddOnly, {POWER_KVAR_B_Q3_ALL_DATA,	PT_KVARH_B_Q3_ALL,	CON_KWH_ADD_EVENT_KWH_NOHAVE,	GAL_NO}}, // AA 当前B相3象限无功电量计算累加 AA 
	{&KwhAddTypeAddOnly, {POWER_KVAR_B_Q4_ALL_DATA,	PT_KVARH_B_Q4_ALL,	CON_KWH_ADD_EVENT_KWH_NOHAVE,	GAL_NO}}, // AA 当前B相4象限无功电量计算累加 AA 
	{&KwhAddTypeAddOnly, {POWER_KVA_B_F_ALL_DATA,	PT_KVAH_B_F_ALL,	CON_KWH_ADD_EVENT_KWH_NOHAVE,	GAL_NO}}, // AA 当前B相正相视在电量计算累加 AA 
	{&KwhAddTypeAddOnly, {POWER_KVA_B_R_ALL_DATA,	PT_KVAH_B_R_ALL,	CON_KWH_ADD_EVENT_KWH_NOHAVE,	GAL_NO}}, // AA 当前B相反相视在电量计算累加 AA 
    {&KwhAddTypeAddOnly, {POWER_KW_C_F_ALL_DATA,  PT_KWH_C_F_ALL, CON_KWH_ADD_EVENT_KWH_C_F_SOS,  GAL_NO}}, // AA 当前C相正相有功电量计算累加 AA 
    {&KwhAddTypeAddOnly, {POWER_KW_C_R_ALL_DATA,  PT_KWH_C_R_ALL, CON_KWH_ADD_EVENT_KWH_C_R_SOS,  GAL_NO}}, // AA 当前C相反相有功电量计算累加 AA 
	{&KwhAddTypeAddOnly, {POWER_KVAR_C_Q1_ALL_DATA,	PT_KVARH_C_Q1_ALL,	CON_KWH_ADD_EVENT_KWH_NOHAVE,	GAL_NO}}, // AA 当前C相1象限无功电量计算累加 AA 
	{&KwhAddTypeAddOnly, {POWER_KVAR_C_Q2_ALL_DATA,	PT_KVARH_C_Q2_ALL,	CON_KWH_ADD_EVENT_KWH_NOHAVE,	GAL_NO}}, // AA 当前C相2象限无功电量计算累加 AA 
	{&KwhAddTypeAddOnly, {POWER_KVAR_C_Q3_ALL_DATA,	PT_KVARH_C_Q3_ALL,	CON_KWH_ADD_EVENT_KWH_NOHAVE,	GAL_NO}}, // AA 当前C相3象限无功电量计算累加 AA 
	{&KwhAddTypeAddOnly, {POWER_KVAR_C_Q4_ALL_DATA,	PT_KVARH_C_Q4_ALL,	CON_KWH_ADD_EVENT_KWH_NOHAVE,	GAL_NO}}, // AA 当前C相4象限无功电量计算累加 AA 
	{&KwhAddTypeAddOnly, {POWER_KVA_C_F_ALL_DATA,	PT_KVAH_C_F_ALL,	CON_KWH_ADD_EVENT_KWH_NOHAVE,	GAL_NO}}, // AA 当前C相正相视在电量计算累加 AA 
	{&KwhAddTypeAddOnly, {POWER_KVA_C_R_ALL_DATA,	PT_KVAH_C_R_ALL,	CON_KWH_ADD_EVENT_KWH_NOHAVE,	GAL_NO}}, // AA 当前C相反相视在电量计算累加 AA 
    {&KwhNoAddType,      {POWER_KW_FR_ALL_DATA,   PT_KWH_F_ALL,   CON_KWH_ADD_EVENT_KWH_NOHAVE,   GAL_NO}}, // AA 当前有功正加反电量计算累加 AA 
#if (CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE_ENABLE == CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE)
    {&KwhAddTypeAddSub,  {POWER_KW_C_ALL_ADD_DATA,    PT_KWH_C_ALL,   CON_KWH_ADD_EVENT_KWH_NOHAVE,   GAL_NO}}, // AA 当前组合有功增加电量计算累加 AA 
    {&KwhSubTypeAddSub,  {POWER_KW_C_ALL_SUB_DATA,    PT_KWH_C_ALL,   CON_KWH_ADD_EVENT_KWH_NOHAVE,   GAL_NO}}, // AA 当前组合有功减少电量计算累加 AA 
#else
    {&KwhAddTypeAddSub,  {POWER_KW_C_ALL_ADD_DATA,    PT_KWH_C_ALL,   CON_KWH_ADD_EVENT_KWH_NOHAVE,   GAL_YES}}, // AA 当前组合有功增加电量计算累加 AA 
    {&KwhSubTypeAddSub,  {POWER_KW_C_ALL_SUB_DATA,    PT_KWH_C_ALL,   CON_KWH_ADD_EVENT_KWH_NOHAVE,   GAL_YES}}, // AA 当前组合有功减少电量计算累加 AA 
#endif
    {&KwhAddTypeAddSub,  {POWER_KVAR_C1_ALL_ADD_DATA, PT_KVARH_C1_ALL,    CON_KWH_ADD_EVENT_KVARH_ALL_C1_SOS, GAL_YES}}, // AA 当前组合无功1电量增加计算累加 AA 
    {&KwhSubTypeAddSub,  {POWER_KVAR_C1_ALL_SUB_DATA, PT_KVARH_C1_ALL,    CON_KWH_ADD_EVENT_KVARH_ALL_C1_SOS, GAL_YES}}, // AA 当前组合无功1电量减少计算累加 AA 
    {&KwhAddTypeAddSub,  {POWER_KVAR_C2_ALL_ADD_DATA, PT_KVARH_C2_ALL,    CON_KWH_ADD_EVENT_KVARH_ALL_C2_SOS, GAL_YES}}, // AA 当前组合无功2电量增加计算累加 AA 
    {&KwhSubTypeAddSub,  {POWER_KVAR_C2_ALL_SUB_DATA, PT_KVARH_C2_ALL,    CON_KWH_ADD_EVENT_KVARH_ALL_C2_SOS, GAL_YES}}, // AA 当前组合无功2电量减少计算累加 AA 
	{&KwhAddTypeAddSub,	 {POWER_KVAR_A_C1_ALL_ADD_DATA,	PT_KVARH_A_C1_ALL,	CON_KWH_ADD_EVENT_KVARH_A_C1_SOS,	GAL_NO}}, // AA 当前A相组合无功1电量增加计算累加 AA 
	{&KwhSubTypeAddSub,	 {POWER_KVAR_A_C1_ALL_SUB_DATA,	PT_KVARH_A_C1_ALL,	CON_KWH_ADD_EVENT_KVARH_A_C1_SOS,	GAL_NO}}, // AA 当前A相组合无功1电量减少计算累加 AA 
	{&KwhAddTypeAddSub,	 {POWER_KVAR_A_C2_ALL_ADD_DATA,	PT_KVARH_A_C2_ALL,	CON_KWH_ADD_EVENT_KVARH_A_C2_SOS,	GAL_NO}}, // AA 当前A相组合无功2电量增加计算累加 AA 
	{&KwhSubTypeAddSub,	 {POWER_KVAR_A_C2_ALL_SUB_DATA,	PT_KVARH_A_C2_ALL,	CON_KWH_ADD_EVENT_KVARH_A_C2_SOS,	GAL_NO}}, // AA 当前A相组合无功2电量减少计算累加 AA 
	{&KwhAddTypeAddSub,	 {POWER_KVAR_B_C1_ALL_ADD_DATA,	PT_KVARH_B_C1_ALL,	CON_KWH_ADD_EVENT_KVARH_B_C1_SOS,	GAL_NO}}, // AA 当前B相组合无功1电量增加计算累加 AA 
	{&KwhSubTypeAddSub,	 {POWER_KVAR_B_C1_ALL_SUB_DATA,	PT_KVARH_B_C1_ALL,	CON_KWH_ADD_EVENT_KVARH_B_C1_SOS,	GAL_NO}}, // AA 当前B相组合无功1电量减少计算累加 AA 
	{&KwhAddTypeAddSub,	 {POWER_KVAR_B_C2_ALL_ADD_DATA,	PT_KVARH_B_C2_ALL,	CON_KWH_ADD_EVENT_KVARH_B_C2_SOS,	GAL_NO}}, // AA 当前B相组合无功2电量增加计算累加 AA 
	{&KwhSubTypeAddSub,	 {POWER_KVAR_B_C2_ALL_SUB_DATA,	PT_KVARH_B_C2_ALL,	CON_KWH_ADD_EVENT_KVARH_B_C2_SOS,	GAL_NO}}, // AA 当前B相组合无功2电量减少计算累加 AA 
	{&KwhAddTypeAddSub,	 {POWER_KVAR_C_C1_ALL_ADD_DATA,	PT_KVARH_C_C1_ALL,	CON_KWH_ADD_EVENT_KVARH_C_C1_SOS,	GAL_NO}}, // AA 当前C相组合无功1电量增加计算累加 AA 
	{&KwhSubTypeAddSub,	 {POWER_KVAR_C_C1_ALL_SUB_DATA,	PT_KVARH_C_C1_ALL,	CON_KWH_ADD_EVENT_KVARH_C_C1_SOS,	GAL_NO}}, // AA 当前C相组合无功1电量减少计算累加 AA 
	{&KwhAddTypeAddSub,	 {POWER_KVAR_C_C2_ALL_ADD_DATA,	PT_KVARH_C_C2_ALL,	CON_KWH_ADD_EVENT_KVARH_C_C2_SOS,	GAL_NO}}, // AA 当前C相组合无功2电量增加计算累加 AA 
	{&KwhSubTypeAddSub,	 {POWER_KVAR_C_C2_ALL_SUB_DATA,	PT_KVARH_C_C2_ALL,	CON_KWH_ADD_EVENT_KVARH_C_C2_SOS,	GAL_NO}}, // AA 当前C相组合无功2电量减少计算累加 AA 
#if (CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE_ENABLE == CONFIG_METER_POWERRESIDUE_PRICE_RECORD_MODE)
    {&KwhAddTypeAddOnly, {POWER_KW_F_ALL_DATA_PRICE1, PT_KWH_F_ALL+1, CON_KWH_ADD_EVENT_KWH_NOHAVE,   GAL_NO}}, // AA 当前正向有功费率1电量计算累加 AA 
    {&KwhAddTypeAddOnly, {POWER_KW_F_ALL_DATA_PRICE2, PT_KWH_F_ALL+2, CON_KWH_ADD_EVENT_KWH_NOHAVE,   GAL_NO}}, // AA 当前正向有功费率2电量计算累加 AA 
    {&KwhAddTypeAddOnly, {POWER_KW_F_ALL_DATA_PRICE3, PT_KWH_F_ALL+3, CON_KWH_ADD_EVENT_KWH_NOHAVE,   GAL_NO}}, // AA 当前正向有功费率3电量计算累加 AA 
    {&KwhAddTypeAddOnly, {POWER_KW_F_ALL_DATA_PRICE4, PT_KWH_F_ALL+4, CON_KWH_ADD_EVENT_KWH_NOHAVE,   GAL_NO}}, // AA 当前正向有功费率4电量计算累加 AA 
    {&KwhAddTypeAddOnly, {POWER_KW_R_ALL_DATA_PRICE1, PT_KWH_R_ALL+1, CON_KWH_ADD_EVENT_KWH_NOHAVE,   GAL_NO}}, // AA 当前反向有功费率1电量计算累加 AA 
    {&KwhAddTypeAddOnly, {POWER_KW_R_ALL_DATA_PRICE2, PT_KWH_R_ALL+2, CON_KWH_ADD_EVENT_KWH_NOHAVE,   GAL_NO}}, // AA 当前反向有功费率2电量计算累加 AA 
    {&KwhAddTypeAddOnly, {POWER_KW_R_ALL_DATA_PRICE3, PT_KWH_R_ALL+3, CON_KWH_ADD_EVENT_KWH_NOHAVE,   GAL_NO}}, // AA 当前反向有功费率3电量计算累加 AA 
    {&KwhAddTypeAddOnly, {POWER_KW_R_ALL_DATA_PRICE4, PT_KWH_R_ALL+4, CON_KWH_ADD_EVENT_KWH_NOHAVE,   GAL_NO}}, // AA 当前反向有功费率4电量计算累加 AA 
    {&KwhAddTypeAddSub,  {POWER_KW_C_ALL_ADD_DATA_PRICE1, PT_KWH_C_ALL+1, CON_KWH_ADD_EVENT_KWH_NOHAVE,   GAL_NO}}, // AA 当前组合有功费率1电量增加计算累加 AA 
    {&KwhAddTypeAddSub,  {POWER_KW_C_ALL_ADD_DATA_PRICE2, PT_KWH_C_ALL+2, CON_KWH_ADD_EVENT_KWH_NOHAVE,   GAL_NO}}, // AA 当前组合有功费率2电量增加计算累加 AA 
    {&KwhAddTypeAddSub,  {POWER_KW_C_ALL_ADD_DATA_PRICE3, PT_KWH_C_ALL+3, CON_KWH_ADD_EVENT_KWH_NOHAVE,   GAL_NO}}, // AA 当前组合有功费率3电量增加计算累加 AA 
    {&KwhAddTypeAddSub,  {POWER_KW_C_ALL_ADD_DATA_PRICE4, PT_KWH_C_ALL+4, CON_KWH_ADD_EVENT_KWH_NOHAVE,   GAL_NO}}, // AA 当前组合有功费率4电量增加计算累加 AA 
    {&KwhSubTypeAddSub,  {POWER_KW_C_ALL_SUB_DATA_PRICE1, PT_KWH_C_ALL+1, CON_KWH_ADD_EVENT_KWH_NOHAVE,   GAL_NO}}, // AA 当前组合有功费率1电量减少计算累加 AA 
    {&KwhSubTypeAddSub,  {POWER_KW_C_ALL_SUB_DATA_PRICE2, PT_KWH_C_ALL+2, CON_KWH_ADD_EVENT_KWH_NOHAVE,   GAL_NO}}, // AA 当前组合有功费率2电量减少计算累加 AA 
    {&KwhSubTypeAddSub,  {POWER_KW_C_ALL_SUB_DATA_PRICE3, PT_KWH_C_ALL+3, CON_KWH_ADD_EVENT_KWH_NOHAVE,   GAL_NO}}, // AA 当前组合有功费率3电量减少计算累加 AA 
    {&KwhSubTypeAddSub,  {POWER_KW_C_ALL_SUB_DATA_PRICE4, PT_KWH_C_ALL+4, CON_KWH_ADD_EVENT_KWH_NOHAVE,   GAL_NO}}, // AA 当前组合有功费率4电量减少计算累加 AA 
#endif
};





ulLong Bcd5DataToLLong(uchar *Ptr)
{
   return( (ulong)OneByteBcdToHex(*Ptr)+
            100*((ulLong)(OneByteBcdToHex(*(Ptr+1))+
            (ulong)OneByteBcdToHex(*(Ptr+2))*100+
            (ulong)OneByteBcdToHex(*(Ptr+3))*10000+
            (ulong)OneByteBcdToHex(*(Ptr+4))*1000000)));
}
void LLongToData5BCD(ulLong value,uchar *point)
{
    point[0]=OneByteHexToBcd(value%100);
    LongToData4BCD(value/100,point+1);
}

void KwhRamAddTypeAddOnly(u16 uiRamAddr,uchar ucKwhAddrData)
{
    ulLong ullDAta;
    ullDAta=Bcd5DataToLLong(&RAM[uiRamAddr])+ucKwhAddrData;
    LLongToData5BCD(ullDAta,&RAM[uiRamAddr]);
}
void KwhRamAddTypeAddSub(u16 uiRamAddr,uchar ucKwhAddrData)
{
    ulLong ullDAta;

    if(0x80==(0x80&RAM[uiRamAddr+4]))
    {
        RAM[uiRamAddr+4]=0x7F&RAM[uiRamAddr+4];
        ullDAta=Bcd5DataToLLong(&RAM[uiRamAddr]);
        // --aa 注意，这里是>号，不是>=号aa--
        if(ullDAta>ucKwhAddrData)
        {
            ullDAta-=ucKwhAddrData;
            LLongToData5BCD(ullDAta,&RAM[uiRamAddr]);
            RAM[uiRamAddr+4]=RAM[uiRamAddr+4]|0x80;
        }
        else
        {
            ullDAta=ucKwhAddrData-ullDAta;
            LLongToData5BCD(ullDAta,&RAM[uiRamAddr]);
        }
    }
    else
    {
        ullDAta=Bcd5DataToLLong(&RAM[uiRamAddr])+ucKwhAddrData;
        LLongToData5BCD(ullDAta,&RAM[uiRamAddr]);
        RAM[uiRamAddr+4]=0x7F&RAM[uiRamAddr+4];
    }
}
void KwhRamSubTypeAddSub(u16 uiRamAddr,uchar ucKwhAddrData)
{
    ulLong ullDAta;

    if(0x00==(0x80&RAM[uiRamAddr+4]))
    {
        ullDAta=Bcd5DataToLLong(&RAM[uiRamAddr]);
        if(ullDAta>=ucKwhAddrData)
        {
            ullDAta-=ucKwhAddrData;
            LLongToData5BCD(ullDAta,&RAM[uiRamAddr]);
        }
        else
        {
            ullDAta=ucKwhAddrData-ullDAta;
            LLongToData5BCD(ullDAta,&RAM[uiRamAddr]);
            RAM[uiRamAddr+4]=RAM[uiRamAddr+4]|0x80;
        }
    }
    else
    {
        RAM[uiRamAddr+4]=0x7F&RAM[uiRamAddr+4];
        ullDAta=Bcd5DataToLLong(&RAM[uiRamAddr])+ucKwhAddrData;
        LLongToData5BCD(ullDAta,&RAM[uiRamAddr]);
        RAM[uiRamAddr+4]=RAM[uiRamAddr+4]|0x80;
    }


}
void KwhFmAddTypeAddOnly(ulong ulFmAddr,uchar ucKwhAddrData)
{
    uchar ucTemp,ucReadOk;
    ucReadOk=0;
    for(ucTemp=0;ucTemp<3;ucTemp++)
    {
        if(1==ReadDataDirect(ulFmAddr,5,&RAM[RAM_COEF_TEMP_CLACUSE]))
        {
            if(5==TestBcdNum(&RAM[RAM_COEF_TEMP_CLACUSE],5))
            {
                ucReadOk=1;
                ucTemp=4;
            }
        }
    }
    if(1==ucReadOk)
    {
        KwhRamAddTypeAddOnly(RAM_COEF_TEMP_CLACUSE,ucKwhAddrData);
        WriteDataDirect(&RAM[RAM_COEF_TEMP_CLACUSE],ulFmAddr,5);
    }
}

void KwhFmAddTypeAddSub(ulong ulFmAddr,uchar ucKwhAddrData)
{
    uchar ucTemp,ucReadOk;
    ucReadOk=0;
    for(ucTemp=0;ucTemp<3;ucTemp++)
    {
        if(1==ReadDataDirect(ulFmAddr,5,&RAM[RAM_COEF_TEMP_CLACUSE]))
        {
            if(1==TestKwhBCD(&RAM[RAM_COEF_TEMP_CLACUSE],1))
            {
                ucReadOk=1;
                ucTemp=4;
            }
            
        }
    }
    if(1==ucReadOk)
    {
        KwhRamAddTypeAddSub(RAM_COEF_TEMP_CLACUSE,ucKwhAddrData);
        WriteDataDirect(&RAM[RAM_COEF_TEMP_CLACUSE],ulFmAddr,5);
    }
}

void KwhFmSubTypeAddSub(ulong ulFmAddr,uchar ucKwhAddrData)
{
    uchar ucTemp,ucReadOk;
    ucReadOk=0;
    for(ucTemp=0;ucTemp<3;ucTemp++)
    {
        if(1==ReadDataDirect(ulFmAddr,5,&RAM[RAM_COEF_TEMP_CLACUSE]))
        {
            if(1==TestKwhBCD(&RAM[RAM_COEF_TEMP_CLACUSE],1))
            {
                ucReadOk=1;
                ucTemp=4;
            }
            
        }
    }
    if(1==ucReadOk)
    {
        KwhRamSubTypeAddSub(RAM_COEF_TEMP_CLACUSE,ucKwhAddrData);
        WriteDataDirect(&RAM[RAM_COEF_TEMP_CLACUSE],ulFmAddr,5);
    }
}

void KwhEventKwhAddTypeAddOnly(uchar  ucOffset,uchar ucKwhAddrData)
{
#if(GAL_YES==EVENTKWH_LOSSVOLTAGE_ADD_FM)
    if( FLG_A_LOSS_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddOnly(EPL_TOTAL_LOSS_AV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_B_LOSS_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddOnly(EPL_TOTAL_LOSS_BV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_C_LOSS_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddOnly(EPL_TOTAL_LOSS_CV_KWH_F + ucOffset,ucKwhAddrData);
    }
#endif
    // OVER VOLTAGE
#if(GAL_YES==EVENTKWH_ADD_FM)
    if( FLG_A_OVER_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddOnly(EPL_TOTAL_OVER_AV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_B_OVER_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddOnly(EPL_TOTAL_OVER_BV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_C_OVER_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddOnly(EPL_TOTAL_OVER_CV_KWH_F + ucOffset,ucKwhAddrData);
    }
#endif
    
    // DOWN VOLTAGE
#if(GAL_YES==EVENTKWH_ADD_FM)
    if( FLG_A_DOWN_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddOnly(EPL_TOTAL_DOWN_AV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_B_DOWN_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddOnly(EPL_TOTAL_DOWN_BV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_C_DOWN_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddOnly(EPL_TOTAL_DOWN_CV_KWH_F + ucOffset,ucKwhAddrData);
    }
#endif
    // CUT VOLTAGE
#if(GAL_YES==EVENTKWH_ADD_FM)
    if( FLG_A_CUT_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddOnly(EPL_TOTAL_CUT_AV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_B_CUT_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddOnly(EPL_TOTAL_CUT_BV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_C_CUT_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddOnly(EPL_TOTAL_CUT_CV_KWH_F + ucOffset,ucKwhAddrData);
    }
#endif

    // LOSS CURRENT
#if(GAL_YES==EVENTKWH_ADD_FM)
    if( FLG_A_LOSS_CURRENT_STATUS )
    {
        KwhFmAddTypeAddOnly(EPL_TOTAL_LOSS_AI_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_B_LOSS_CURRENT_STATUS )
    {
        KwhFmAddTypeAddOnly(EPL_TOTAL_LOSS_BI_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_C_LOSS_CURRENT_STATUS )
    {
        KwhFmAddTypeAddOnly(EPL_TOTAL_LOSS_CI_KWH_F + ucOffset,ucKwhAddrData);
    }
#endif
    // OVER CURRENT
#if(GAL_YES==EVENTKWH_ADD_FM)
    if( FLG_A_OVER_CURRENT_STATUS )
    {
        KwhFmAddTypeAddOnly(EPL_TOTAL_OVER_AI_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_B_OVER_CURRENT_STATUS )
    {
        KwhFmAddTypeAddOnly(EPL_TOTAL_OVER_BI_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_C_OVER_CURRENT_STATUS )
    {
        KwhFmAddTypeAddOnly(EPL_TOTAL_OVER_CI_KWH_F + ucOffset,ucKwhAddrData);
    }
#endif
    // CUT CURRENT
#if(GAL_YES==EVENTKWH_ADD_FM)
    if( FLG_A_CUT_CURRENT_STATUS )
    {
        KwhFmAddTypeAddOnly(EPL_TOTAL_CUT_AI_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_B_CUT_CURRENT_STATUS )
    {
        KwhFmAddTypeAddOnly(EPL_TOTAL_CUT_BI_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_C_CUT_CURRENT_STATUS )
    {
        KwhFmAddTypeAddOnly(EPL_TOTAL_CUT_CI_KWH_F + ucOffset,ucKwhAddrData);
    }
#endif
    // REVERSE 
#if(GAL_YES==EVENTKWH_ADD_FM)
    if(PROGFUNCTION_REVERSEPOWER_ALL)
    {
        if( FLG_REVERSEKW_ALL_STATUS)
        {
            KwhFmAddTypeAddOnly(EPL_TOTAL_REVERSE_ALL_KWH_F + ucOffset,ucKwhAddrData);
        }
        if( FLG_REVERSEKW_A_STATUS)
        {
            KwhFmAddTypeAddOnly(EPL_TOTAL_REVERSE_A_KWH_F + ucOffset,ucKwhAddrData);
        }
        if( FLG_REVERSEKW_B_STATUS)
        {
            KwhFmAddTypeAddOnly(EPL_TOTAL_REVERSE_B_KWH_F + ucOffset,ucKwhAddrData);
        }
        if( FLG_REVERSEKW_C_STATUS)
        {
            KwhFmAddTypeAddOnly(EPL_TOTAL_REVERSE_C_KWH_F + ucOffset,ucKwhAddrData);
        }
    }
#endif
    // KW OVER
#if(GAL_YES==EVENTKWH_ADD_FM)
    if(PROGFUNCTION_POWEROVER_ALL)
    {
        if( FLG_ALL_OVER_KW_STATUS)
        {
            KwhFmAddTypeAddOnly(EPL_TOTAL_POWEROVER_ALL_KWH_F + ucOffset,ucKwhAddrData);
        }
        if( FLG_A_OVER_KW_STATUS)
        {
            KwhFmAddTypeAddOnly(EPL_TOTAL_POWEROVER_A_KWH_F + ucOffset,ucKwhAddrData);
        }
        if( FLG_B_OVER_KW_STATUS)
        {
            KwhFmAddTypeAddOnly(EPL_TOTAL_POWEROVER_B_KWH_F + ucOffset,ucKwhAddrData);
        }
        if( FLG_C_OVER_KW_STATUS)
        {
            KwhFmAddTypeAddOnly(EPL_TOTAL_POWEROVER_C_KWH_F + ucOffset,ucKwhAddrData);
        }
    }
#endif
    
    // ORDER VOLTAGE
#if(GAL_YES==EVENTKWH_ADD_FM)
    if(PROGFUNCTION_ORDER_VOLTAGE)
    {
        if( FLG_ORDER_VOLTAGE_STATUS)
        {
            KwhFmAddTypeAddOnly(EPL_TOTAL_ORDER_VOLTAGE_KWH_F + ucOffset,ucKwhAddrData);
        }
    }
#endif
    // ORDER CURRENT
#if(GAL_YES==EVENTKWH_ADD_FM)
    if(PROGFUNCTION_ORDER_CURRENT)
    {
        if( FLG_ORDER_CURRENT_STATUS)
        {
            KwhFmAddTypeAddOnly(EPL_TOTAL_ORDER_CURRENT_KWH_F + ucOffset,ucKwhAddrData);
        }
    }
#endif
    
    // UNBALANCE VOLTAGE
#if(GAL_YES==EVENTKWH_ADD_FM)
    if(PROGFUNCTION_UNBALANCE_VOLTAGE)
    {
        if( FLG_UNBALANCE_VOLTAGE_STATUS)
        {
            KwhFmAddTypeAddOnly(EPL_TOTAL_UNBALANCE_VOLTAGE_KWH_F + ucOffset,ucKwhAddrData);
        }
    }
#endif
    
    // UNBALANCE CURRENT
#if(GAL_YES==EVENTKWH_ADD_FM)
    if(PROGFUNCTION_UNBALANCE_CURRENT)
    {
        if( FLG_UNBALANCE_CURRENT_STATUS)
        {
            KwhFmAddTypeAddOnly(EPL_TOTAL_UNBALANCE_CURRENT_KWH_F + ucOffset,ucKwhAddrData);
        }
    }       
#endif
}


void KwhEventKwhAddTypeAddSub(uchar  ucOffset,uchar ucKwhAddrData)
{
#if(GAL_YES==EVENTKWH_LOSSVOLTAGE_ADD_FM)
    if( FLG_A_LOSS_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddSub(EPL_TOTAL_LOSS_AV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_B_LOSS_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddSub(EPL_TOTAL_LOSS_BV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_C_LOSS_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddSub(EPL_TOTAL_LOSS_CV_KWH_F + ucOffset,ucKwhAddrData);
    }
#endif
    // OVER VOLTAGE
#if(GAL_YES==EVENTKWH_ADD_FM)
    if( FLG_A_OVER_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddSub(EPL_TOTAL_OVER_AV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_B_OVER_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddSub(EPL_TOTAL_OVER_BV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_C_OVER_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddSub(EPL_TOTAL_OVER_CV_KWH_F + ucOffset,ucKwhAddrData);
    }
#endif
    
    // DOWN VOLTAGE
#if(GAL_YES==EVENTKWH_ADD_FM)
    if( FLG_A_DOWN_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddSub(EPL_TOTAL_DOWN_AV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_B_DOWN_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddSub(EPL_TOTAL_DOWN_BV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_C_DOWN_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddSub(EPL_TOTAL_DOWN_CV_KWH_F + ucOffset,ucKwhAddrData);
    }
#endif
    // CUT VOLTAGE
#if(GAL_YES==EVENTKWH_ADD_FM)
    if( FLG_A_CUT_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddSub(EPL_TOTAL_CUT_AV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_B_CUT_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddSub(EPL_TOTAL_CUT_BV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_C_CUT_VOLTAGE_STATUS )
    {
        KwhFmAddTypeAddSub(EPL_TOTAL_CUT_CV_KWH_F + ucOffset,ucKwhAddrData);
    }
#endif

    // LOSS CURRENT
#if(GAL_YES==EVENTKWH_ADD_FM)
    if( FLG_A_LOSS_CURRENT_STATUS )
    {
        KwhFmAddTypeAddSub(EPL_TOTAL_LOSS_AI_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_B_LOSS_CURRENT_STATUS )
    {
        KwhFmAddTypeAddSub(EPL_TOTAL_LOSS_BI_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_C_LOSS_CURRENT_STATUS )
    {
        KwhFmAddTypeAddSub(EPL_TOTAL_LOSS_CI_KWH_F + ucOffset,ucKwhAddrData);
    }
#endif
    // OVER CURRENT
#if(GAL_YES==EVENTKWH_ADD_FM)
    if( FLG_A_OVER_CURRENT_STATUS )
    {
        KwhFmAddTypeAddSub(EPL_TOTAL_OVER_AI_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_B_OVER_CURRENT_STATUS )
    {
        KwhFmAddTypeAddSub(EPL_TOTAL_OVER_BI_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_C_OVER_CURRENT_STATUS )
    {
        KwhFmAddTypeAddSub(EPL_TOTAL_OVER_CI_KWH_F + ucOffset,ucKwhAddrData);
    }
#endif
    // CUT CURRENT
#if(GAL_YES==EVENTKWH_ADD_FM)
    if( FLG_A_CUT_CURRENT_STATUS )
    {
        KwhFmAddTypeAddSub(EPL_TOTAL_CUT_AI_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_B_CUT_CURRENT_STATUS )
    {
        KwhFmAddTypeAddSub(EPL_TOTAL_CUT_BI_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_C_CUT_CURRENT_STATUS )
    {
        KwhFmAddTypeAddSub(EPL_TOTAL_CUT_CI_KWH_F + ucOffset,ucKwhAddrData);
    }
#endif
    // REVERSE 
#if(GAL_YES==EVENTKWH_ADD_FM)
    if(PROGFUNCTION_REVERSEPOWER_ALL)
    {
        if( FLG_REVERSEKW_ALL_STATUS)
        {
            KwhFmAddTypeAddSub(EPL_TOTAL_REVERSE_ALL_KWH_F + ucOffset,ucKwhAddrData);
        }
        if( FLG_REVERSEKW_A_STATUS)
        {
            KwhFmAddTypeAddSub(EPL_TOTAL_REVERSE_A_KWH_F + ucOffset,ucKwhAddrData);
        }
        if( FLG_REVERSEKW_B_STATUS)
        {
            KwhFmAddTypeAddSub(EPL_TOTAL_REVERSE_B_KWH_F + ucOffset,ucKwhAddrData);
        }
        if( FLG_REVERSEKW_C_STATUS)
        {
            KwhFmAddTypeAddSub(EPL_TOTAL_REVERSE_C_KWH_F + ucOffset,ucKwhAddrData);
        }
    }
#endif
    // KW OVER
#if(GAL_YES==EVENTKWH_ADD_FM)
    if(PROGFUNCTION_POWEROVER_ALL)
    {
        if( FLG_ALL_OVER_KW_STATUS)
        {
            KwhFmAddTypeAddSub(EPL_TOTAL_POWEROVER_ALL_KWH_F + ucOffset,ucKwhAddrData);
        }
        if( FLG_A_OVER_KW_STATUS)
        {
            KwhFmAddTypeAddSub(EPL_TOTAL_POWEROVER_A_KWH_F + ucOffset,ucKwhAddrData);
        }
        if( FLG_B_OVER_KW_STATUS)
        {
            KwhFmAddTypeAddSub(EPL_TOTAL_POWEROVER_B_KWH_F + ucOffset,ucKwhAddrData);
        }
        if( FLG_C_OVER_KW_STATUS)
        {
            KwhFmAddTypeAddSub(EPL_TOTAL_POWEROVER_C_KWH_F + ucOffset,ucKwhAddrData);
        }
    }
#endif
    
    // ORDER VOLTAGE
#if(GAL_YES==EVENTKWH_ADD_FM)
    if(PROGFUNCTION_ORDER_VOLTAGE)
    {
        if( FLG_ORDER_VOLTAGE_STATUS)
        {
            KwhFmAddTypeAddSub(EPL_TOTAL_ORDER_VOLTAGE_KWH_F + ucOffset,ucKwhAddrData);
        }
    }
#endif
    // ORDER CURRENT
#if(GAL_YES==EVENTKWH_ADD_FM)
    if(PROGFUNCTION_ORDER_CURRENT)
    {
        if( FLG_ORDER_CURRENT_STATUS)
        {
            KwhFmAddTypeAddSub(EPL_TOTAL_ORDER_CURRENT_KWH_F + ucOffset,ucKwhAddrData);
        }
    }
#endif
    
    // UNBALANCE VOLTAGE
#if(GAL_YES==EVENTKWH_ADD_FM)
    if(PROGFUNCTION_UNBALANCE_VOLTAGE)
    {
        if( FLG_UNBALANCE_VOLTAGE_STATUS)
        {
            KwhFmAddTypeAddSub(EPL_TOTAL_UNBALANCE_VOLTAGE_KWH_F + ucOffset,ucKwhAddrData);
        }
    }
#endif
    
    // UNBALANCE CURRENT
#if(GAL_YES==EVENTKWH_ADD_FM)
    if(PROGFUNCTION_UNBALANCE_CURRENT)
    {
        if( FLG_UNBALANCE_CURRENT_STATUS)
        {
            KwhFmAddTypeAddSub(EPL_TOTAL_UNBALANCE_CURRENT_KWH_F + ucOffset,ucKwhAddrData);
        }
    }       
#endif
}


void KwhEventKwhSubTypeAddSub(uchar  ucOffset,uchar ucKwhAddrData)
{
#if(GAL_YES==EVENTKWH_LOSSVOLTAGE_ADD_FM)
    if( FLG_A_LOSS_VOLTAGE_STATUS )
    {
        KwhFmSubTypeAddSub(EPL_TOTAL_LOSS_AV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_B_LOSS_VOLTAGE_STATUS )
    {
        KwhFmSubTypeAddSub(EPL_TOTAL_LOSS_BV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_C_LOSS_VOLTAGE_STATUS )
    {
        KwhFmSubTypeAddSub(EPL_TOTAL_LOSS_CV_KWH_F + ucOffset,ucKwhAddrData);
    }
#endif
    // OVER VOLTAGE
#if(GAL_YES==EVENTKWH_ADD_FM)
    if( FLG_A_OVER_VOLTAGE_STATUS )
    {
        KwhFmSubTypeAddSub(EPL_TOTAL_OVER_AV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_B_OVER_VOLTAGE_STATUS )
    {
        KwhFmSubTypeAddSub(EPL_TOTAL_OVER_BV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_C_OVER_VOLTAGE_STATUS )
    {
        KwhFmSubTypeAddSub(EPL_TOTAL_OVER_CV_KWH_F + ucOffset,ucKwhAddrData);
    }
#endif
    
    // DOWN VOLTAGE
#if(GAL_YES==EVENTKWH_ADD_FM)
    if( FLG_A_DOWN_VOLTAGE_STATUS )
    {
        KwhFmSubTypeAddSub(EPL_TOTAL_DOWN_AV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_B_DOWN_VOLTAGE_STATUS )
    {
        KwhFmSubTypeAddSub(EPL_TOTAL_DOWN_BV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_C_DOWN_VOLTAGE_STATUS )
    {
        KwhFmSubTypeAddSub(EPL_TOTAL_DOWN_CV_KWH_F + ucOffset,ucKwhAddrData);
    }
#endif
    // CUT VOLTAGE
#if(GAL_YES==EVENTKWH_ADD_FM)
    if( FLG_A_CUT_VOLTAGE_STATUS )
    {
        KwhFmSubTypeAddSub(EPL_TOTAL_CUT_AV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_B_CUT_VOLTAGE_STATUS )
    {
        KwhFmSubTypeAddSub(EPL_TOTAL_CUT_BV_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_C_CUT_VOLTAGE_STATUS )
    {
        KwhFmSubTypeAddSub(EPL_TOTAL_CUT_CV_KWH_F + ucOffset,ucKwhAddrData);
    }
#endif

    // LOSS CURRENT
#if(GAL_YES==EVENTKWH_ADD_FM)
    if( FLG_A_LOSS_CURRENT_STATUS )
    {
        KwhFmSubTypeAddSub(EPL_TOTAL_LOSS_AI_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_B_LOSS_CURRENT_STATUS )
    {
        KwhFmSubTypeAddSub(EPL_TOTAL_LOSS_BI_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_C_LOSS_CURRENT_STATUS )
    {
        KwhFmSubTypeAddSub(EPL_TOTAL_LOSS_CI_KWH_F + ucOffset,ucKwhAddrData);
    }
#endif
    // OVER CURRENT
#if(GAL_YES==EVENTKWH_ADD_FM)
    if( FLG_A_OVER_CURRENT_STATUS )
    {
        KwhFmSubTypeAddSub(EPL_TOTAL_OVER_AI_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_B_OVER_CURRENT_STATUS )
    {
        KwhFmSubTypeAddSub(EPL_TOTAL_OVER_BI_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_C_OVER_CURRENT_STATUS )
    {
        KwhFmSubTypeAddSub(EPL_TOTAL_OVER_CI_KWH_F + ucOffset,ucKwhAddrData);
    }
#endif
    // CUT CURRENT
#if(GAL_YES==EVENTKWH_ADD_FM)
    if( FLG_A_CUT_CURRENT_STATUS )
    {
        KwhFmSubTypeAddSub(EPL_TOTAL_CUT_AI_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_B_CUT_CURRENT_STATUS )
    {
        KwhFmSubTypeAddSub(EPL_TOTAL_CUT_BI_KWH_F + ucOffset,ucKwhAddrData);
    }
    if( FLG_C_CUT_CURRENT_STATUS )
    {
        KwhFmSubTypeAddSub(EPL_TOTAL_CUT_CI_KWH_F + ucOffset,ucKwhAddrData);
    }
#endif
    // REVERSE 
#if(GAL_YES==EVENTKWH_ADD_FM)
    if(PROGFUNCTION_REVERSEPOWER_ALL)
    {
        if( FLG_REVERSEKW_ALL_STATUS)
        {
            KwhFmSubTypeAddSub(EPL_TOTAL_REVERSE_ALL_KWH_F + ucOffset,ucKwhAddrData);
        }
        if( FLG_REVERSEKW_A_STATUS)
        {
            KwhFmSubTypeAddSub(EPL_TOTAL_REVERSE_A_KWH_F + ucOffset,ucKwhAddrData);
        }
        if( FLG_REVERSEKW_B_STATUS)
        {
            KwhFmSubTypeAddSub(EPL_TOTAL_REVERSE_B_KWH_F + ucOffset,ucKwhAddrData);
        }
        if( FLG_REVERSEKW_C_STATUS)
        {
            KwhFmSubTypeAddSub(EPL_TOTAL_REVERSE_C_KWH_F + ucOffset,ucKwhAddrData);
        }
    }
#endif
    // KW OVER
#if(GAL_YES==EVENTKWH_ADD_FM)
    if(PROGFUNCTION_POWEROVER_ALL)
    {
        if( FLG_ALL_OVER_KW_STATUS)
        {
            KwhFmSubTypeAddSub(EPL_TOTAL_POWEROVER_ALL_KWH_F + ucOffset,ucKwhAddrData);
        }
        if( FLG_A_OVER_KW_STATUS)
        {
            KwhFmSubTypeAddSub(EPL_TOTAL_POWEROVER_A_KWH_F + ucOffset,ucKwhAddrData);
        }
        if( FLG_B_OVER_KW_STATUS)
        {
            KwhFmSubTypeAddSub(EPL_TOTAL_POWEROVER_B_KWH_F + ucOffset,ucKwhAddrData);
        }
        if( FLG_C_OVER_KW_STATUS)
        {
            KwhFmSubTypeAddSub(EPL_TOTAL_POWEROVER_C_KWH_F + ucOffset,ucKwhAddrData);
        }
    }
#endif
    
    // ORDER VOLTAGE
#if(GAL_YES==EVENTKWH_ADD_FM)
    if(PROGFUNCTION_ORDER_VOLTAGE)
    {
        if( FLG_ORDER_VOLTAGE_STATUS)
        {
            KwhFmSubTypeAddSub(EPL_TOTAL_ORDER_VOLTAGE_KWH_F + ucOffset,ucKwhAddrData);
        }
    }
#endif
    // ORDER CURRENT
#if(GAL_YES==EVENTKWH_ADD_FM)
    if(PROGFUNCTION_ORDER_CURRENT)
    {
        if( FLG_ORDER_CURRENT_STATUS)
        {
            KwhFmSubTypeAddSub(EPL_TOTAL_ORDER_CURRENT_KWH_F + ucOffset,ucKwhAddrData);
        }
    }
#endif
    
    // UNBALANCE VOLTAGE
#if(GAL_YES==EVENTKWH_ADD_FM)
    if(PROGFUNCTION_UNBALANCE_VOLTAGE)
    {
        if( FLG_UNBALANCE_VOLTAGE_STATUS)
        {
            KwhFmSubTypeAddSub(EPL_TOTAL_UNBALANCE_VOLTAGE_KWH_F + ucOffset,ucKwhAddrData);
        }
    }
#endif
    
    // UNBALANCE CURRENT
#if(GAL_YES==EVENTKWH_ADD_FM)
    if(PROGFUNCTION_UNBALANCE_CURRENT)
    {
        if( FLG_UNBALANCE_CURRENT_STATUS)
        {
            KwhFmSubTypeAddSub(EPL_TOTAL_UNBALANCE_CURRENT_KWH_F + ucOffset,ucKwhAddrData);
        }
    }       
#endif
}


void KwhAddDataAddOnly(uchar ucKwhType,uchar ucKwhAddData)
{
    KwhPowerOnSafeCheck(ucKwhType,0);
    KwhRamAddTypeAddOnly(RAM_KWH_ALL_START+5*ucKwhType,ucKwhAddData);
    WritePower3Copy(ucKwhType);
}

void KwhAddDataAddSub(uchar ucKwhType,uchar ucKwhAddData)
{
    KwhPowerOnSafeCheck(ucKwhType,1);
    KwhRamAddTypeAddSub(RAM_KWH_ALL_START+5*ucKwhType,ucKwhAddData);
    WritePower3Copy(ucKwhType);
}
void KwhSubDataAddSub(uchar ucKwhType,uchar ucKwhAddData)
{
    KwhPowerOnSafeCheck(ucKwhType,1);
    KwhRamSubTypeAddSub(RAM_KWH_ALL_START+5*ucKwhType,ucKwhAddData);
    WritePower3Copy(ucKwhType);
}



void KwhAddTypeAddOnly(ST_POWER_ADD_DATA_PARAM *stAddData)
{
    uchar ucKwhAdd;
    ucKwhAdd=ucPowerClacAddFlg[stAddData->ucKwhType];
    KwhAddDataAddOnly(stAddData->ucAddType,ucKwhAdd);
    if(GAL_YES==(stAddData->ucPriceHave))
    {
        KwhAddDataAddOnly(ucCurrentPriceHEX+(stAddData->ucAddType),ucKwhAdd);
    }
#if(GAL_YES==EVENTKWH_ADD_FM)
    if(CON_KWH_ADD_EVENT_KWH_NOHAVE!=(stAddData->ucOffset  ))
    {
        KwhEventKwhAddTypeAddOnly((stAddData->ucOffset  ), ucKwhAdd);
    }
#endif
}
void KwhAddTypeAddSub(ST_POWER_ADD_DATA_PARAM *stAddData)
{
    uchar ucKwhAdd;
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
    ulong ulTemp;
    memcpy((uchar *)&ulTemp, &RAM[RAM_KWH_C_ALL+1] ,4);
#endif  
    ucKwhAdd=ucPowerClacAddFlg[stAddData->ucKwhType];
    KwhAddDataAddSub(stAddData->ucAddType,ucKwhAdd);
    if(GAL_YES==(stAddData->ucPriceHave))
    {
        KwhAddDataAddSub(ucCurrentPriceHEX+(stAddData->ucAddType),ucKwhAdd);
    }
    if(CON_KWH_ADD_EVENT_KWH_NOHAVE!=(stAddData->ucOffset  ))
    {
        KwhEventKwhAddTypeAddSub((stAddData->ucOffset  ), ucKwhAdd);
    }
// --AA 如果是组合有功电量的话，需要考虑增加用电量数据 AA--
    if(PT_KWH_C_ALL==(stAddData->ucAddType))
    {
// --AA 增加用电量数据 AA--
        KwhRamAddTypeAddOnly(RAM_KWH_C_USE_ALL,ucKwhAdd);
        if(GAL_YES==(stAddData->ucPriceHave))
        {
            #if(CON_PRICENUM_MAX<=CON_PRICENUM_USE_KWH)
                KwhRamAddTypeAddOnly(ucCurrentPriceHEX*5+RAM_KWH_C_USE_ALL,ucKwhAdd);
            #else
                if(ucCurrentPriceHEX>CON_PRICENUM_USE_KWH)
                {
                    KwhRamAddTypeAddOnly(1*5+RAM_KWH_C_USE_ALL,ucKwhAdd);
                }
                else
                {
                    KwhRamAddTypeAddOnly(ucCurrentPriceHEX*5+RAM_KWH_C_USE_ALL,ucKwhAdd);
                }
            #endif
        }
        //WriteDataDirect(&RAM[RAM_KWH_C_USE_ALL],EPL_KWH_C_USE_ALL,5*5);
    }
    
#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)
// --AA 如果是预付费表,在组合有功计算时，需要考虑事件 AA--
    if(PT_KWH_C_ALL==(stAddData->ucAddType))
    {
        KwhAdd0D01Event(ulTemp);
    }
#endif

    
}

#if(CONFIG_METER_PREPAY_MODE != CONFIG_METER_PREPAY_MODE_DISABLE)

void KwhAdd0D01Event(ulong ulLastKwh)
// --AA  程序限定只有在加的程序里面才被调用,   AA--
// --AA  且每次增加不能超过2个刻度   AA--
// --AA  程序的输入为在增加前的电量,数据精确到小数点后2位.   AA--
// --AA     AA--
// --AA     AA--
{
    ulong ulNowKwh, ulTemp;
    slong slNowKwh, slLastKwh;
    uchar ucTemp;
    memcpy((uchar *)&ulNowKwh, &RAM[RAM_KWH_C_ALL+1] ,4);
    if(ulNowKwh != ulLastKwh)
    {
        if(ulLastKwh>=0x80000000)
        {
            ulLastKwh=~(0x7fffffff&ulLastKwh)+1;
            ulTemp = Bcd4DataToLong((uchar *)&ulLastKwh);
            slLastKwh = - (slong)ulTemp;
        }
        else
        {
            ulTemp = Bcd4DataToLong((uchar *)&ulLastKwh);
            slLastKwh = (slong)ulTemp;
        }
        if(ulNowKwh>=0x80000000)
        {
            ulNowKwh=~(0x7fffffff&ulNowKwh)+1;
            ulTemp = Bcd4DataToLong((uchar *)&ulNowKwh);
            slNowKwh = - (slong)ulTemp;
        }
        else
        {
            ulTemp = Bcd4DataToLong((uchar *)&ulNowKwh);
            slNowKwh = (slong)ulTemp;
        }
// --AA  且每次增加不能超过2个刻度   AA--
        if((slNowKwh - slLastKwh > 2) || (slNowKwh - slLastKwh < 1))
        {
            return;
        }
        ulNowKwh=slNowKwh-slLastKwh;
        for(ucTemp=0;ucTemp<ulNowKwh;ucTemp++)
        {
            GetReadySubMoney();
        }
#if(CONFIG_METER_RELAY_MODE_OUTSIDE== CONFIG_METER_RELAY_MODE)
        RelayStatusCheckOnKwhAdd();
#endif          
    }
}
#endif

void KwhSubTypeAddSub(ST_POWER_ADD_DATA_PARAM *stAddData)
{
    uchar ucKwhAdd;
    ucKwhAdd=ucPowerClacAddFlg[stAddData->ucKwhType];
    KwhSubDataAddSub(stAddData->ucAddType,ucKwhAdd);
    if(GAL_YES==(stAddData->ucPriceHave))
    {
        KwhSubDataAddSub(ucCurrentPriceHEX+(stAddData->ucAddType),ucKwhAdd);
    }
    if(CON_KWH_ADD_EVENT_KWH_NOHAVE!=(stAddData->ucOffset  ))
    {
        KwhEventKwhSubTypeAddSub((stAddData->ucOffset  ), ucKwhAdd);
    }
}
void KwhNoAddType(ST_POWER_ADD_DATA_PARAM *stAddData)
{

    uchar ucKwhAdd;
    ucKwhAdd=ucPowerClacAddFlg[stAddData->ucKwhType];
    KwhRamAddTypeAddOnly(RAM_KWH_F_AND_R_ALL,ucKwhAdd);
    if(GAL_YES==(stAddData->ucPriceHave))
    {
        #if(CON_PRICENUM_MAX<=CON_PRICENUM_USE_KWH)
        KwhRamAddTypeAddOnly(ucCurrentPriceHEX*5+RAM_KWH_F_AND_R_ALL,ucKwhAdd);
        #else
        if(ucCurrentPriceHEX>CON_PRICENUM_USE_KWH)
        {
            KwhRamAddTypeAddOnly(1*5+RAM_KWH_F_AND_R_ALL,ucKwhAdd);
        }
        else
        {
            KwhRamAddTypeAddOnly(ucCurrentPriceHEX*5+RAM_KWH_F_AND_R_ALL,ucKwhAdd);
        }
        #endif
    }
    //WriteDataDirect(&RAM[RAM_KWH_F_AND_R_ALL],EPL_KWH_F_AND_R_ALL,5*5);
    
}



void KwhAddMode()
{
    uchar ucTemp,ucCount;
    ST_POWER_ADD_DATA_PARAM stAddTemp;
    KwhAddModeAddEnd=GAL_NO;
    //ucKwhErrEventRecordMode=CON_KWH_ERR_EVENT_RECORD_START;
    ucCount=sizeof(TB_POWER_ADD_BUFFER)/sizeof(ST_POWER_ADD_PARAM);
    for(ucTemp=0;ucTemp<ucCount;ucTemp++)
    {
        stAddTemp=TB_POWER_ADD_BUFFER[ucTemp].stAddData;
        if(ucPowerClacAddFlg[stAddTemp.ucKwhType])
        {
            if(0xff!=stAddTemp.ucAddType)
            {
                TB_POWER_ADD_BUFFER[ucTemp].callBack(&stAddTemp);
            }
        }
        ucPowerClacAddFlg[stAddTemp.ucKwhType]=0;
    }
    //ucKwhErrEventRecordMode=CON_KWH_ERR_EVENT_RECORD_END; 
}





