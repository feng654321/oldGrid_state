#define AP_ANGLE_GLOBALS
#include "common.h"

#define ORDERCURRENTSTATUS_NO   (status_5460_1 &=0xf7)
#define ORDERCURRENTSTATUS_YES  (status_5460_1 |=0x08)
#define CON_ANGLE_DATA_LEN      2

const u16 TB_AD7878_ANGLE[3]=
{
    AD_ANGLE0,
    AD_ANGLE1,
    AD_ANGLE2,
};

/*
void AngleCurrentAndVoltage(uchar xiang);
void AngleCosToAngle(uchar abcz);

const uchar jiaodu_0[]={0x10,0x20,0x40,0x80};
const uchar jiaodu_1[]={0x1,0x2,0x4,0x8};


u16 xiangjiao_count[3];



//2006-0 add---------------------------------------------start
const uchar TB_ARC_COS_USE[][3]=
{            
    {99,99,99},// 0
    {99,98,48},// 1
    {99,93,91},// 2
    {99,86,29},// 3
    {99,75,64},// 4
    {99,61,95},// 5
    {99,45,22}, // 6
    {99,25,46},// 7
    {99,02,68},// 8
    {98,76,88},// 9
    {98,48,0x8},// 10
    {98,16,27},// 11
    {97,81,48},// 12
    {97,43,70},// 13
    {97,02,96},// 14
    {96,59,26},// 15
    {96,12,62},// 16
    {95,63,05},// 17
    {95,10,57},// 18
    {94,55,19},// 19
    {93,96,93},// 20
    {93,35,80},// 21
    {92,71,84},// 22
    {92,05,05},// 23
    {91,35,45},// 24
    {90,63,0x8},// 25
    {89,87,94},// 26
    {89,10,0x7},// 27
    {88,29,48},// 28
    {87,46,20},// 29
    {86,60,25},// 30
    {85,71,67},// 31
    {84,80,48},// 32
    {83,86,71},// 33
    {82,90,38},// 34
    {81,91,52},// 35
    {80,90,17},// 36
    {79,86,36},// 37
    {78,80,11},// 38
    {77,71,46},// 39
    {76,60,44},// 40
    {75,47,10},// 41
    {74,31,45},// 42
    {73,13,54},// 43
    {71,93,40},// 44
    {70,71,07},// 45
    {69,46,58},// 46
    {68,19,98},// 47
    {66,91,31},// 48
    {65,60,59},// 49
    {64,27,88},// 50
    {62,93,20},// 51
    {61,56,61},// 52
    {60,18,15},// 53
    {58,77,85},// 54
    {57,35,76},// 55
    {55,91,93},// 56
    {54,46,39},// 57
    {52,99,19},// 58
    {51,50,38},// 59
    {50,00,00},// 60
    {48,48,10},// 61
    {46,94,72},// 62
    {45,39,90},// 63
    {43,83,71},// 64
    {42,26,18},// 65
    {40,67,37},// 66
    {39,07,31},// 67
    {37,46,07},// 68
    {35,83,68},// 69
    {34,20,20},// 70
    {32,55,68},// 71
    {30,90,17},// 72
    {29,23,72},// 73
    {27,56,37},// 74
    {25,88,19},// 75
    {24,19,22},// 76
    {22,49,51},// 77
    {20,79,12},// 78
    {19,0x8,0x9},// 79
    {17,36,48},// 80
    {15,64,34},// 81
    {13,91,73},// 82
    {12,18,69},// 83
    {10,45,28},// 84
    {0x8,71,56},// 85
    {0x6,97,56},// 86
    {0x5,23,36},// 87
    {0x3,48,99},// 88
    {0x1,74,52},// 89
    {00,00,00}// 90
};


void AngleCosToAngle(uchar abcz)
//abcz 0 a 1 b 2 c 3 z
{
    uchar l1,m1,m2;
    u16 l;
    union k1 {
        uchar s[4];
        ulong v;
        }d0,d1,d2;
    ulong m;
    ulong h1,h2,h3,h4;
    uchar *point,*to;
    
    abcz=abcz%4;
    point=&RAM[RAM_CURRENT_FACTOR_A];
    to=&RAM[RAM_CURRENT_ANGLE_AV_AI];
    if(abcz==1)
    {
        point=&RAM[RAM_CURRENT_FACTOR_B];
        to=&RAM[RAM_CURRENT_ANGLE_BV_BI];
    }
    if(abcz==2)
    {
        point=&RAM[RAM_CURRENT_FACTOR_C];
        to=&RAM[RAM_CURRENT_ANGLE_CV_CI];
    }
    if(abcz==3)
    {
        point=&RAM[RAM_CURRENT_FACTOR_ALL];
        to=&RAM[RAM_CURRENT_ANGLE_ZV_ZI];
    }
    m=Bcd4DataToLong(point)/10;
    LongToData4BCD(m, &d1.s[0]);
    for(l=0;l<4;l++)
    {
        d0.s[l]=ValueHexFromBcd(d1.s[l]);
    }
    m=0;
    m1=0;
    d1.v=0;
    d2.v=0;
    m2=0;
    for(l=1;l<91;l++)
        {
        for(l1=0;l1<3;l1++)
            {
            d1.s[l1]=TB_ARC_COS_USE[l][2-l1];
            d2.s[l1]=TB_ARC_COS_USE[l-1][2-l1];
            }
        if(d0.v>d1.v)
            {
            m=l;
            l=91;
            h3=d1.s[2];
            h3=h3*10000;
            h3=h3+100*d1.s[1];
            h3=h3+d1.s[0];
            h4=d2.s[2];
            h4=10000*h4;
            h4=h4+100*d2.s[1];
            h4=h4+d2.s[0];
            h1=h4-h3;
            h2=d0.s[3];
            h2=100*100*100*h2;
            h4=d0.s[2];
            h2=h2+100*100*h4;
            h2=h2+100*d0.s[1];
            h2=h2+d0.s[0];
            h2=h2-h3;       
            if(0!=h1)
                {
                m1=((10*h2)/h1)%10;
                h3=10*((10*h2)%h1);//
                m2=(h3/h1)%10;//
                }
            }
        }
    if(d0.v>=0x00999999) 
        {
        m=0;
        m1=0;
        m2=0;//
        }
    if(d0.v==0) 
        {
        m=90;
        m1=0;
        m2=0;//
        }
    if(m>0) 
        m=10*(m*10-m1)-m2;//
    if((status_5460_0&jiaodu_0[abcz])==0) 
        {
        if((status_5460_0&jiaodu_1[abcz])!=0)
            {
            m=36000-m;//
            }
        }
    else
        {
        if((status_5460_0&jiaodu_1[abcz])==0)
            m=18000-m;//
        else
            m=18000+m;//
        }
    m=m%36000;
    if(abcz<3)
        xiangjiao_count[abcz]=m;  
    l=m/10000; 
    *(to+2)=ValueBcdFromHex(l);
    l=m%10000;
    l=l/100;
    *(to+1)=ValueBcdFromHex(l);
    l=m%100;
    *to=ValueBcdFromHex(l);
}




void AngleCurrentAndVoltage(uchar xiang)
{
    u16 temp_int,l;
    uchar i;
    switch(xiang)
    { 
        case 0://a
            for(i=0;i<3;i++) 
            {
                RAM[RAM_CURRENT_ANGLE_AI_AV+i]=RAM[RAM_CURRENT_ANGLE_AV_AI+i];
            }
            if(0== JudjeFunction05Ib(0))
            {
                for(i=0;i<3;i++)          
                {
                    RAM[RAM_CURRENT_ANGLE_AI_AV+i]=0;   
                }
            }
            break;
        case 1://b
            if(0== JudjeFunction05Ib(1))
            { 
                for(i=0;i<3;i++)
                {
                    RAM[RAM_CURRENT_ANGLE_BI_AV+i]=0;   
                }
            }
            else
            {
                temp_int= ValueHexFrom3BcdRam(RAM_CURRENT_ANGLE_BV_AV)+xiangjiao_count[xiang];
                temp_int=temp_int%36000;
                l=temp_int/10000; 
                RAM[RAM_CURRENT_ANGLE_BI_AV+2]=ValueBcdFromHex(l);
                l=temp_int%10000;
                l=l/100;
                RAM[RAM_CURRENT_ANGLE_BI_AV+1]=ValueBcdFromHex(l);
                l=temp_int%100;
                RAM[RAM_CURRENT_ANGLE_BI_AV]=ValueBcdFromHex(l);
            }
            break;
        case 2://c
            if(0== JudjeFunction05Ib(2))
            { 
                for(i=0;i<3;i++) 
                {
                    RAM[RAM_CURRENT_ANGLE_CI_AV+i]=0;   
                }
            }
            else    
            {  
                temp_int= ValueHexFrom3BcdRam(RAM_CURRENT_ANGLE_CV_AV)+xiangjiao_count[xiang];
                temp_int=temp_int%36000;
                l=temp_int/10000; 
                RAM[RAM_CURRENT_ANGLE_CI_AV+2]=ValueBcdFromHex(l);
                l=temp_int%10000;
                l=l/100;
                RAM[RAM_CURRENT_ANGLE_CI_AV+1]=ValueBcdFromHex(l);
                l=temp_int%100;
                RAM[RAM_CURRENT_ANGLE_CI_AV]=ValueBcdFromHex(l);
            }
            break;
        default:
            break;      
    }
}

*/


static uchar ucAngleModePoint;

void AngleInit(void)
{
    memset(&RAM[RAM_CURRENT_ANGLE_AV_AV], 0xFF, CON_ANGLE_DATA_LEN);
    memset(&RAM[RAM_CURRENT_ANGLE_BV_AV], 0xFF, CON_ANGLE_DATA_LEN);
    memset(&RAM[RAM_CURRENT_ANGLE_CV_AV], 0xFF, CON_ANGLE_DATA_LEN);
    memset(&RAM[RAM_CURRENT_ANGLE_AV_AI], 0xFF, CON_ANGLE_DATA_LEN);
    memset(&RAM[RAM_CURRENT_ANGLE_BV_BI], 0xFF, CON_ANGLE_DATA_LEN);
    memset(&RAM[RAM_CURRENT_ANGLE_CV_CI], 0xFF, CON_ANGLE_DATA_LEN);
    memset(&RAM[RAM_CURRENT_ANGLE_ZV_ZI], 0xFF, CON_ANGLE_DATA_LEN);
    
    memset(&RAM[RAM_CURRENT_ANGLE_AI_AV], 0xFF, CON_ANGLE_DATA_LEN);
    memset(&RAM[RAM_CURRENT_ANGLE_BI_AV], 0xFF, CON_ANGLE_DATA_LEN);
    memset(&RAM[RAM_CURRENT_ANGLE_CI_AV], 0xFF, CON_ANGLE_DATA_LEN);
}
uchar AngleMode(void)
{
#define CON_ANGLEMODE_POINT_VI      0   // 80
#define CON_ANGLEMODE_POINT_DELAY1  100
#define CON_ANGLEMODE_POINT_DELAY2  120
#define CON_ANGLEMODE_POINT_DELAY3  140
#define CON_ANGLEMODE_POINT_DELAY4  160
#define CON_ANGLEMODE_POINT_VV      1   // 180
#define CON_ANGLEMODE_POINT_MAX     2   // 250
    uchar n;
    u16 uiTemp;
        // AA    第0 秒不处理    AAA
    if(0==RSOFT_RTC_SECOND)
    {
        return DLT_RET_SUCC;
    }
    else
    {
        {
            if(ucAde7878CfModeTime<CON_ADE7878_CFMODE_TIME_MAX)
            {
                return DLT_RET_SUCC;
            }
            if(CON_ANGLEMODE_POINT_VI==ucAngleModePoint)
            {
// AA----各相电压和各相电流之间的夹角--->Start----AAA
                for(n=0;n<3;n++)
                { 
                    if(1==ReadADReg(TB_AD7878_ANGLE[n],2, &Wr_data[0]))
                    { 
						uiTemp=Wr_data[0];
						uiTemp=uiTemp*256+Wr_data[1];
						uiTemp = ((ulong)uiTemp)*7042/10000;
                        // 当前相电流小于启动电流或者当前相电压欠压，不判断该相角度
                        if(0==JudjeFunction05Ib(n))
                        {
                            uiTemp=0;
                        }
                        if(BitValue(n)==(ucVoltageLowStatusABC&BitValue(n)))
                        {
                            uiTemp=0;
                        }
                        IntToData2BCD(uiTemp,&RAM[RAM_CURRENT_ANGLE_AV_AI+CON_ANGLE_DATA_LEN*n]);// xxxx dot xxxx
                    }
                }
                if(PROGFUNCTION_TYPE_METER_TYPE==METERTYPE_3_3)
                {
                    memset(&RAM[RAM_CURRENT_ANGLE_AV_AI+CON_ANGLE_DATA_LEN*1], 0x00, CON_ANGLE_DATA_LEN);
                }
// AA----各相电压和各相电流之间的夹角--->End----AAA
                /*if(1!=ReadADRegResumeData(AD_VIRTUALREG_CHECKSUMSAVE0,4,&Wr_data[0]))
                {
                    memset(&Wr_data[0], 0xff, 4);
                }
                if(4==TestZeroNum(&Wr_data[0], 4))
                {
                    ReadADReg(AD_COMPMODE,2,&Wr_data[0]);
                    Wr_data[0]=0x02;
                }
                else*/
                {
                    Wr_data[0]=0x02;
                    Wr_data[1]=0x3f;
                }
                WriteADReg(&Wr_data[0],AD_COMPMODE,2);
//              Delay(41000);//aaa 30mS=41000   aaa             
            }   
            /*if(CON_ANGLEMODE_POINT_DELAY1==ucAngleModePoint)
            {
                SysDelayMs(7);
            }
            if(CON_ANGLEMODE_POINT_DELAY2==ucAngleModePoint)
            {
                SysDelayMs(7);
            }
            if(CON_ANGLEMODE_POINT_DELAY3==ucAngleModePoint)
            {
                SysDelayMs(7);
            }
            if(CON_ANGLEMODE_POINT_DELAY4==ucAngleModePoint)
            {
                SysDelayMs(7);
            }*/
            if(CON_ANGLEMODE_POINT_VV==ucAngleModePoint)
            {
// AA----A相电压和各相电压之间的夹角--->Start----AAA
                if(PROGFUNCTION_TYPE_METER_TYPE==METERTYPE_3_3)
                {
                    // AA----ANGLE0=AC----AA
                    if(1==ReadADReg(TB_AD7878_ANGLE[0],2, &Wr_data[0]))
                    { 
						uiTemp=Wr_data[0];
						uiTemp=uiTemp*256+Wr_data[1];
						uiTemp = ((ulong)uiTemp)*7042/10000;
                        IntToData2BCD(uiTemp,&RAM[RAM_CURRENT_ANGLE_AV_AV+CON_ANGLE_DATA_LEN*2]);// xxxx dot xxxx
                    }
                    
                    memset(&RAM[RAM_CURRENT_ANGLE_AV_AV+CON_ANGLE_DATA_LEN*0], 0x00, CON_ANGLE_DATA_LEN);
                    memset(&RAM[RAM_CURRENT_ANGLE_AV_AV+CON_ANGLE_DATA_LEN*1], 0x00, CON_ANGLE_DATA_LEN);
                    if((0x05&ucVoltageLowStatusABC))
                    {
                        memset(&RAM[RAM_CURRENT_ANGLE_AV_AV+CON_ANGLE_DATA_LEN*2], 0x00, CON_ANGLE_DATA_LEN);
                    }
                    
                }
                else
                {
                    // AA----A------AA
                    memset(&RAM[RAM_CURRENT_ANGLE_AV_AV+CON_ANGLE_DATA_LEN*0], 0x00, CON_ANGLE_DATA_LEN);
                    // AA----ANGLE2=AB----AA
                    if(1==ReadADReg(TB_AD7878_ANGLE[2],2, &Wr_data[0]))
                    { 
						uiTemp=Wr_data[0];
						uiTemp=uiTemp*256+Wr_data[1];
						uiTemp = ((ulong)uiTemp)*7042/10000;
                        IntToData2BCD(uiTemp,&RAM[RAM_CURRENT_ANGLE_AV_AV+CON_ANGLE_DATA_LEN*1]);// xxxx dot xxxx
                    }
                    if(0x01&ucVoltageLowStatusABC)
                    {
                        memset(&RAM[RAM_CURRENT_ANGLE_AV_AV+CON_ANGLE_DATA_LEN*1], 0x00, CON_ANGLE_DATA_LEN);
                        // AA----ANGLE0=AC----AA
                        if(1==ReadADReg(TB_AD7878_ANGLE[1],2, &Wr_data[0]))
                        { 
							uiTemp=Wr_data[0];
							uiTemp=uiTemp*256+Wr_data[1];
							uiTemp = ((ulong)uiTemp)*7042/10000;
                            IntToData2BCD(uiTemp,&RAM[RAM_CURRENT_ANGLE_AV_AV+CON_ANGLE_DATA_LEN*2]);// xxxx dot xxxx
                        }
                    }
                    else
                    {
                        // AA----ANGLE0=AC----AA
                        if(1==ReadADReg(TB_AD7878_ANGLE[0],2, &Wr_data[0]))
                        { 
							uiTemp=Wr_data[0];
							uiTemp=uiTemp*256+Wr_data[1];
							uiTemp = ((ulong)uiTemp)*7042/10000;
                            IntToData2BCD(uiTemp,&RAM[RAM_CURRENT_ANGLE_AV_AV+CON_ANGLE_DATA_LEN*2]);// xxxx dot xxxx
                        }
                    }
                    if(0x03==(0x03&ucVoltageLowStatusABC))
                    {
                        memset(&RAM[RAM_CURRENT_ANGLE_AV_AV+CON_ANGLE_DATA_LEN*0], 0x00, CON_ANGLE_DATA_LEN);
                        memset(&RAM[RAM_CURRENT_ANGLE_AV_AV+CON_ANGLE_DATA_LEN*1], 0x00, CON_ANGLE_DATA_LEN);
                        memset(&RAM[RAM_CURRENT_ANGLE_AV_AV+CON_ANGLE_DATA_LEN*2], 0x00, CON_ANGLE_DATA_LEN);
                    }
                    if(0x02==(0x02&ucVoltageLowStatusABC))
                    {
                        memset(&RAM[RAM_CURRENT_ANGLE_AV_AV+CON_ANGLE_DATA_LEN*1], 0x00, CON_ANGLE_DATA_LEN);
                    }
                    if(0x04==(0x04&ucVoltageLowStatusABC))
                    {
                        memset(&RAM[RAM_CURRENT_ANGLE_AV_AV+CON_ANGLE_DATA_LEN*2], 0x00, CON_ANGLE_DATA_LEN);
                    }
                }
// AA----A相电压和各相电压之间的夹角--->End---AAA
// AA----A相电压和各相电流之间的夹角--->Start----AAA
                //AA           ANGLE --->AV and AI
                RAM[RAM_CURRENT_ANGLE_AI_AV+0]=RAM[RAM_CURRENT_ANGLE_AV_AI+0];
                RAM[RAM_CURRENT_ANGLE_AI_AV+1]=RAM[RAM_CURRENT_ANGLE_AV_AI+1];
                //AA           ANGLE --->AV and BI
                if(PROGFUNCTION_TYPE_METER_TYPE==METERTYPE_3_3)
                {
                    memset(&RAM[RAM_CURRENT_ANGLE_AI_AV+CON_ANGLE_DATA_LEN*1], 0x00, CON_ANGLE_DATA_LEN);
                }
                else
                {
                    uiTemp=ValueHexFromRam2Bcd(RAM_CURRENT_ANGLE_AV_AV+CON_ANGLE_DATA_LEN*1+0)+ValueHexFromRam2Bcd(RAM_CURRENT_ANGLE_AV_AI+CON_ANGLE_DATA_LEN*1+0);
                    uiTemp=uiTemp%3600;
                    IntToData2BCD(uiTemp,&RAM[RAM_CURRENT_ANGLE_AI_AV+CON_ANGLE_DATA_LEN*1]);
                }
                //AA           ANGLE --->AV and BI
                uiTemp=ValueHexFromRam2Bcd(RAM_CURRENT_ANGLE_AV_AV+CON_ANGLE_DATA_LEN*2+0)+ValueHexFromRam2Bcd(RAM_CURRENT_ANGLE_AV_AI+CON_ANGLE_DATA_LEN*2+0);
                uiTemp=uiTemp%3600;
                IntToData2BCD(uiTemp,&RAM[RAM_CURRENT_ANGLE_AI_AV+CON_ANGLE_DATA_LEN*2]);
// AA----A相电压和各相电流之间的夹角--->End----AAA

// AA----三相三线电压相序判断--->Start----AAA
/*   
// AA  关于三相三线电压逆向序判断的分析  AA
// AA  在一般的情况下，三相三线的AC相位差都是300度左右  AA
// AA  在逆相序的情况下，三相三线的AC的相位差在60度  AA
// AA  所以，个人认为，要是小于180度，则认为是逆相序了。  AA
// AA    AA
*/
                if(PROGFUNCTION_TYPE_METER_TYPE==METERTYPE_3_3)
                {
                    if(0==(0x05&ucVoltageLowStatusABC))
                    {
                        uiTemp=ValueHexFromRam2Bcd(RAM_CURRENT_ANGLE_AV_AV+CON_ANGLE_DATA_LEN*2+0);
                        if(uiTemp<1800)
                        
                        {
                            status_5460_1=0x80;
                        }
                        else
                        {
                            status_5460_1=0x00;
                        }
                    }
                }
                else
                {
                    //三相三线是错的，但四线是准的
                    if(1==ReadADReg(AD_STATUS1,4, &Wr_data[0]))
                    {
                        if((0x8&Wr_data[1])==0)
                        {
                            status_5460_1=0x00;
                        }
                        else
                        {
                            status_5460_1=0x80;
                        }
                    }
                    memset(&Wr_data[0], 0xFF, 4);
                    WriteADReg(&Wr_data[0], AD_STATUS1, 4);
                } 

// AA----三相三线电压相序判断--->End----AAA




// AA----三线四线电流相序判断--->Start----AAA
                if(PROGFUNCTION_TYPE_METER_TYPE!=METERTYPE_3_3)
                //  AA  ----三相四线的情况下-------   AAA
                {
                    if((0==ucVoltageLowStatusABC)&&(0==(0x80&status_5460_1)))
                    //  AA  ----不断相的情况下-------   AAA
                    {
                        if(3==(JudjeFunction05Ib(0)+JudjeFunction05Ib(1)+JudjeFunction05Ib(2)))
                        //  AA  ----电流比较大的情况下-------   AAA
                        {
/*   
// AA  关于电流逆向序的分析  AA
// AA  |  各种类型  -->     3者关系 | 相序   |AA

// AA  |   A>B A>C B>C  -->     A>B>C       | ERR    |  AA 
// AA  |   A>B A>C B<C  -->     A>C>B       | OK     |  AA 

// AA  |   A>B A<C B>C  -->     ERR         | ERR    |  AA 
// AA  |   A>B A<C B<C  -->     C>A>B       | ERR    |  AA 


// AA  |   A<B A>C B>C  -->     B>A>C       | OK     |  AA 
// AA  |   A<B A>C B<C  -->     ERR         | ERR    |  AA 

// AA  |   A<B A<C B>C  -->     B>C>A       | ERR    |  AA 
// AA  |   A<B A<C B<C  -->     C>B>A       | OK     |  AA 

// AA  通过分析，判定只有3 种情况下电流不逆向序  AA
// AA  其他情况下，电流都是逆向序的  AA

*/
                            ORDERCURRENTSTATUS_NO;
                            if(Bcd2DataToInt(&RAM[RAM_CURRENT_ANGLE_AI_AV+CON_ANGLE_DATA_LEN*0])>Bcd2DataToInt(&RAM[RAM_CURRENT_ANGLE_AI_AV+CON_ANGLE_DATA_LEN*1])) // a>b
                            {
                                if(Bcd2DataToInt(&RAM[RAM_CURRENT_ANGLE_AI_AV+CON_ANGLE_DATA_LEN*1])>Bcd2DataToInt(&RAM[RAM_CURRENT_ANGLE_AI_AV+CON_ANGLE_DATA_LEN*2]))     // b>c
                                {
                                    ORDERCURRENTSTATUS_YES; // A>B>C
                                }
                                if(Bcd2DataToInt(&RAM[RAM_CURRENT_ANGLE_AI_AV+CON_ANGLE_DATA_LEN*2])>Bcd2DataToInt(&RAM[RAM_CURRENT_ANGLE_AI_AV+CON_ANGLE_DATA_LEN*0]))     // b>c
                                {
                                    ORDERCURRENTSTATUS_YES; // C>A>B
                                }
                            }
                            else
                            {
                                if((Bcd2DataToInt(&RAM[RAM_CURRENT_ANGLE_AI_AV+CON_ANGLE_DATA_LEN*1])>Bcd2DataToInt(&RAM[RAM_CURRENT_ANGLE_AI_AV+CON_ANGLE_DATA_LEN*2]))
                                    &&(Bcd2DataToInt(&RAM[RAM_CURRENT_ANGLE_AI_AV+CON_ANGLE_DATA_LEN*2])>Bcd2DataToInt(&RAM[RAM_CURRENT_ANGLE_AI_AV+CON_ANGLE_DATA_LEN*0])))
                                {
                                    ORDERCURRENTSTATUS_YES; // B>C>A
                                }
                            }
                        }
                    }
                }
// AA----三线四线电流相序判断--->End----AAA
                else
// AA----三相三线电流相序判断--->Start----AAA
                {

                    if((0==(0x05&ucVoltageLowStatusABC))&&(2==(JudjeFunction05Ib(0)+JudjeFunction05Ib(2))))
                    {
                        
                        uiTemp=ValueHexFromRam2Bcd(RAM_CURRENT_ANGLE_AI_AV+CON_ANGLE_DATA_LEN*2+0);
                        if(uiTemp<ValueHexFromRam2Bcd(RAM_CURRENT_ANGLE_AI_AV+CON_ANGLE_DATA_LEN*0+0))
                        {
                            uiTemp=uiTemp+3600;
                        }
                        uiTemp=uiTemp-ValueHexFromRam2Bcd(RAM_CURRENT_ANGLE_AI_AV+CON_ANGLE_DATA_LEN*0+0);
                        
                        if(uiTemp<1800)
                        
                        {
                            ORDERCURRENTSTATUS_YES;
                        }
                        else
                        {
                            ORDERCURRENTSTATUS_NO;
                        }
                    }
                    
                }
// AA----三相三线电流相序判断--->End----AAA
                
                /*if(1!=ReadADRegResumeData(AD_VIRTUALREG_CHECKSUMSAVE0,4,&Wr_data[0]))
                {
                    memset(&Wr_data[0], 0xff, 4);
                }
                if(4==TestZeroNum(&Wr_data[0], 4))
                {
                    ReadADReg(AD_COMPMODE,2,&Wr_data[0]);
                    Wr_data[0] =0x00;
                }
                else*/
                {
                    Wr_data[0]=0x00;
                    Wr_data[1]=0x3f;
                }
                WriteADReg(&Wr_data[0],AD_COMPMODE,2);
            }
            ucAngleModePoint++;
            if(ucAngleModePoint>=CON_ANGLEMODE_POINT_MAX)
            {
                ucAngleModePoint=0;
            }
        }
    }
    return DLT_RET_SUCC;
}



/*   
// AA  关于电流逆向序的分析  AA
// AA  |  各种类型  -->     3者关系 | 相序   |AA

// AA  |   A>B A>C B>C  -->     A>B>C       | ERR    |  AA 
// AA  |   A>B A>C B<C  -->     A>C>B       | OK     |  AA 

// AA  |   A>B A<C B>C  -->     ERR         | ERR    |  AA 
// AA  |   A>B A<C B<C  -->     C>A>B       | ERR    |  AA 


// AA  |   A<B A>C B>C  -->     B>A>C       | OK     |  AA 
// AA  |   A<B A>C B<C  -->     ERR         | ERR    |  AA 

// AA  |   A<B A<C B>C  -->     B>C>A       | ERR    |  AA 
// AA  |   A<B A<C B<C  -->     C>B>A       | OK     |  AA 

// AA  通过分析，判定只有3 种情况下电流不逆向序  AA
// AA  其他情况下，电流都是逆向序的  AA

*/
























