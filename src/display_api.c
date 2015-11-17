/*******************************************************************************
模块名       : 显示API模块
文件名       : Display_api.c。
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
其他说明:   无。
*******************************************************************************/
#define DISPLAY_API_GLOBALS
#include "common.h"

const STR_LCD_PARA LCDDefaultPara = 
{
    BLINKING_0HZ,1,0
};


/*  mapping buf
             ---a
            |f  |b
             --g
            |e  |c
             ---d.h 
            
 a       b       c       d       e       f       g       h
0x10    0x01    0x04    0x80    0x40    0x20    0x02    0x08
*/
const uchar LCDMappingTableSmile[] = 
{
 //第一区
 0x14,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
 //第二区
 0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
 //第三区
 //' ',0x20                                                 //'-',0x2d,
 0x00,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x02,0x2e,0x2f,
 //第四区
 //'0  ','   1'  '  2'  ' 3'   '4'  '  5'  '  6'  '  7'  '  8'  '     9' 
 //以下为了十六进制显示的需要而直接用A-F的段码。
 0xAF,0xA0,0xCB,0xE9,0xE4,0x6D,0x6F,0xA8,0xEF,0xED,0xEE,0x67,0x0F,0xE3,0x4F,0x4E,
 //第五区
 //     A    B   'C'  D    E    F    G    H    I    J    K    L     M   N    O
 0x00,0xEE,0x67,0x0F,0xE3,0x4F,0x4E,0x6F,0xE6,0x06,0xA1,0x46,0x07,0x80,0xAE,0x63,
 //第六区
 //P    Q   R    S    T    U    V    W    X    Y    Z    [          ]        _
 0x73,0x37,0x77,0x80,0xe2,0xe5,0xe5,0x80,0x80,0xa7,0x80,0xd8,0x5c,0xF0,0x5e,0x80,
 //第七区
 //         A    B   'C'      D     E       F    G      H       I        J      K        L     M       N        O   
 0x60,0xEE,0x67,0x0F,0xE3,0x4F,0x4E,0x6F,0xE6,0x06,0xA1,0x46,0x07,0x80,0xAE,0x63,
 //第八区   
 //P    Q   R    S    T    U    V    W    X    Y    Z          |
 0x73,0x37,0x77,0x80,0xe2,0xe5,0xe5,0x80,0x80,0xa7,0x80,0x7b,0x05,0x7d,0x7e,0xff
};
// 0xaf
const uchar LCDMappingTableBig[] = 
{
 //第一区
 // '0','  1'  '  2'    '3'   ' 4'  '  5'  '  6'  '    7'  '    8'  '   9'     A     B   '   C'     D     E       F  
 0xAF,0xA0,0xCB,0xE9,0xE4,0x6D,0x6F,0xA8,0xEF,0xED,0xEE,0x67,0x0F,0xE3,0x4F,0x4E,
 //第二区
 0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
 //第三区
 //' ',0x20                                                 //'-',0x2d,
 0x00,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x40,0x2e,0x2f,
 //第四区
 // '0','  1'  '  2'    '3'   ' 4'  '  5'  '  6'  '    7'  '    8'  '   9' 
 //以下为了十六进制显示的需要而直接用A-F的段码。
 0xAF,0xA0,0xCB,0xE9,0xE4,0x6D,0x6F,0xA8,0xEF,0xED,0xEE,0x67,0x0F,0xE3,0x4F,0x4E,
 //第五区
 //      A     B   '   C'     D     E       F      G     H       I       J       K     L       M     N     O
 0x00,0xEE,0x67,0x0F,0xE3,0x4F,0x4E,0x2F,0xE6,0x20,0xA1,0xE6,0x07,0x08,0x64,0x63,
 //第六区
 //P    Q         R    S       T      U      V     W      X      Y     Z      [       ]      _
 0xCE,0xEC,0x42,0x6D,0x88,0x23,0xA7,0x80,0x80,0xa7,0x80,0x7b,0x05,0x1,0x7e,0xff,
 //第七区
 //    A    B   'C'  D    E    F    G    H    I    J    K    L     M   N    O   
 0x00,0xEE,0x67,0x0F,0xE3,0x4F,0x4E,0x2F,0xE6,0x20,0xA1,0xE6,0x07,0x08,0x64,0x63,
 //第八区   
 //P    Q         R    S       T      U      V     W      X      Y     Z      [       ]      _
 0xCE,0xEC,0x42,0x6D,0x88,0x23,0xA7,0x80,0x80,0xa7,0x80,0x7b,0x05,0x1,0x7e,0xff
};


void LCDSwitch(uchar switchEn);
uchar SetLCD(STR_LCD_PARA* para);
void ReflashDisplayMemory(STR_DISPLAYMEMORY* src);
void DisplayMemoryMappingLCD(STR_DISPLAYMEMORY* src);
void ReflashLCDDisplay(STR_DISPLAYMEMORY* src);
void InitLCD(void);
void ReflashLEDDisplay(STR_LED_DISPLAY* LEDDisplay);
void InitLED(void);
void ClrLedBackLight(void)
{
    //GPIO_ResetBits(OUT_BLIGHT_PORT,OUT_BLIGHT_PIN);
}

void SetLedBackLight(void)
{
    //GPIO_SetBits(OUT_BLIGHT_PORT,OUT_BLIGHT_PIN);
}



/*************************************************************
Function: 开关LCD
Input:switchEn ON：开 OFF：关 
Output: 无
Application area:  
Explain: 
Modification register:
**************************************************************/
void LCDSwitch(uchar switchEn)
{
}


/*************************************************************
Function: 设置LCD显示
Input: 
Output: 无
Application area:  
Explain: 
Modification register:
**************************************************************/
uchar SetLCD(STR_LCD_PARA* para)
{
    return(1);
}


/*************************************************************
Function: 更新显存
Input: Src：内容
Output: 无
Application area:  
Explain: 
Modification register:
**************************************************************/
void ReflashDisplayMemory(STR_DISPLAYMEMORY* src)
{
    memcpy(&displayMemory,src,sizeof(STR_DISPLAYMEMORY));
    LCDRefalshEn = 1;
}


/*************************************************************
Function: 显存到实际LCD的映射函数
Input: src：显存内容
Output: 无
Application area:  
Explain: 
Modification register:更换LCD屏时，主要更改函数
**************************************************************/
#if(MLCD_TYPE == MLCD_TYPE1)
#if(CONFIG_METER_SW_DEBUG_MODE == GAL_YES)
extern uchar ucSystemResetMode;
#endif
void DisplayMemoryMappingLCD(STR_DISPLAYMEMORY* src)
{
#if 0    
    static uchar ucTempDisplayTimesUse=0;

    uchar buf[32],i,j;//,k;
    
    memset(buf,0,sizeof(buf));

    for(i=0;i<8;i++)
    {
        buf[31-i] =LCDMappingTableBig[src->value1[i]];
    }
    
    for(i=0;i<8;i++)
    {
        buf[11-i] =LCDMappingTableBig[src->screenNO[i]];
    }

    buf[13]=LCDMappingTableBig[src->ShowIndex[0]];
    buf[12]=LCDMappingTableBig[src->ShowIndex[1]];
    
    if(src->symbol.DangQian)
    {
        buf[16] |= 0x10;    //  dangqian 
    }
    if(src->symbol.month)
    {
        buf[18] |= 0x20;    // yue
        if((src->symbol.Shang1)||(src->symbol.Shang2))
        {
            j=src->value2[0];
            if((j/10))
            {
                ;
                // AA 显示1 AA
                buf[16] |= 0x40;    // 1p
                ;
                j=j%10;
            }
            j=LCDMappingTableBig[j];
            buf[17] =(j>>4)+(j<<4);
            buf[16] |= 0x20;    //  shang   
        }
        
    }
    else
    {
        if(src->symbol.Shang1)
        {
            j=src->value2[0];
            if(j<20)
            {
                if((j/10))
                {
                    ;
                    // AA 显示1 AA
                    buf[16] |= 0x40;    // 1p
                    ;
                    j=j%10;
                }
                j=LCDMappingTableBig[j];
                buf[17] =(j>>4)+(j<<4);
                buf[16] |= 0x20;    //  shang
            }
        }
    }
#if(CONFIG_METER_SW_DEBUG_MODE == GAL_YES)
    if(ucSystemResetMode)
    {
        j=LCDMappingTableBig[ucSystemResetMode];
        buf[17] =(j>>4)+(j<<4);
    }
#endif
#if (CONFIG_METER_SIGNED_DIGIT_SHOW_MODE == CONFIG_METER_SIGNED_DIGIT_SHOW_MODE_CLOSED)
    //对有符号数，符号显示在数字前面
    if(src->symbol.fu)      //tzg
    {
        j = 0;
        for(i=7;i>=0;i--)
        {
            if(src->value1[i] == ' ')
            //if(buf[31-i] == LCDMappingTableBig[' '])
            {
                buf[31-i] |= LCDMappingTableBig['-']; //'-'
                j = 0xff;
                break;
            }
        }
        if(j != 0xff) //数字全显，没地方插入负号，就只能还是用原来的负号
            buf[23] |= 0x02;
    }
#elif (CONFIG_METER_SIGNED_DIGIT_SHOW_MODE == CONFIG_METER_SIGNED_DIGIT_SHOW_MODE_FIXED)
    //对有符号数，符号显示在最前
    if(src->symbol.fu)
        buf[23] |= 0x02;
#endif
    if(src->symbol.DP2)
        buf[31] |= 0x10;
    if(src->symbol.DP3)
        buf[30] |= 0x10;
    if(src->symbol.DP4)
        buf[29] |= 0x10;    
    if(src->symbol.DP5)
        buf[28] |= 0x10;    
    if(src->symbol.DP6)
        buf[27] |= 0x10;    
    if(src->symbol.DP7)
        buf[26] |= 0x10;    
    if(src->symbol.DP8)
        buf[25] |= 0x10;    
    if(src->symbol.DP11)
        buf[10] |= 0x10;
    if(src->symbol.DP13)
        buf[8] |= 0x10; 
    if(src->symbol.DP15)
        buf[6] |= 0x10; 
    if(src->symbol.col1)
        buf[19] |= 0x08;
    if(src->symbol.col2)
        buf[20] |= 0x80;
        
#if(CONFIG_METER_AREA_MODE_SHANGHAI==CONFIG_METER_AREA_MODE)
    if(src->symbol.feeRate == 3)
        buf[14] |= 0x10;
    else if(src->symbol.feeRate == 4)
        buf[14] |= 0x20;    
    else if(src->symbol.feeRate == 1)
        buf[14] |= 0x40;    
    else if(src->symbol.feeRate == 2)
        buf[14] |= 0x80;    
    else if(src->symbol.feeRate == 127)
        buf[14] |= 0xf0;    
#else
    if(src->symbol.feeRate == 1)
        buf[14] |= 0x10;
    else if(src->symbol.feeRate == 2)
        buf[14] |= 0x20;    
    else if(src->symbol.feeRate == 3)
        buf[14] |= 0x40;    
    else if(src->symbol.feeRate == 4)
        buf[14] |= 0x80;    
    else if(src->symbol.feeRate == 127)
        buf[14] |= 0xf0;    
#endif
//  if(src->symbol.ShiTao)
//      buf[0] |= 0x02;
#if 0
    if(src->symbol.ShiTaoNum == 1)
        buf[14] |= 0x01;
    else if(src->symbol.ShiTaoNum == 2)
        buf[14] |= 0x02;
    else if(src->symbol.ShiTaoNum == 3)
        buf[14] |= 0x04;
    else if(src->symbol.ShiTaoNum == 4)
        buf[14] |= 0x08;
    else if(src->symbol.ShiTaoNum == 31)
    {
        buf[14] |= 0x0f;
    }
#endif
#if(CONFIG_METER_FACTORY_MODE!=CONFIG_METER_FACTORY_MODE_ENABLE)
    if(src->symbol.quadrant == 1)
    {
        buf[15] |= 0x84;
    }
    else if(src->symbol.quadrant == 2)
    {
        buf[15] |= 0x14;
    }
    else if(src->symbol.quadrant == 3)
    {
        buf[15] |= 0x24;
    }
    else if(src->symbol.quadrant == 4)
    {
        buf[15] |= 0x44;
    }
    else if(src->symbol.quadrant == 7)
    {
        buf[15] |= 0xf4;    
    }
#else
    if(src->symbol.quadrant == 1)
    {
        buf[15] |= 0x74;
    }
    else if(src->symbol.quadrant == 2)
    {
        buf[15] |= 0xe4;
    }
    else if(src->symbol.quadrant == 3)
    {
        buf[15] |= 0xd4;
    }
    else if(src->symbol.quadrant == 4)
    {
        buf[15] |= 0xb4;
    }
    else if(src->symbol.quadrant == 7)
    {
        buf[15] |= 0xf4;    
    }
    
#endif  


#if(CONFIG_METER_AREA_MODE_SHANGHAI!=CONFIG_METER_AREA_MODE)
    if(src->symbol.zuhe)
    {
        buf[18] |=0x10;
    }
#endif
    if(src->symbol.Fan)
    {
        buf[18] |=0x01;
    }
    if(src->symbol.Zheng)
    {
        buf[18] |=0x02;
    }
    
    if(src->symbol.fangXiang)
    {
        buf[19] |=0x20;
    }
    if(src->symbol.Wu)
    {
        buf[19] |=0x10;
    }
    if(src->symbol.You)
    {
        buf[19] |=0x01;
    }
    if(src->symbol.Gong)
    {
        buf[19] |=0x02;
    }
    
    if(src->symbol.wugongxiangxian1)
    {
        buf[20] |=0x20;
    }
    if(src->symbol.wugongxiangxian2)
    {
        buf[20] |=0x10;
    }
    if(src->symbol.wugongxiangxian3)
    {
        buf[20] |=0x01;
    }
    if(src->symbol.wugongxiangxian4)
    {
        buf[20] |=0x02;
    }
    if(src->symbol.Zong)
    {
        buf[21] |=0x20;
    }
    if(src->symbol.Jian)
    {
        buf[21] |=0x10;
    }
    if(src->symbol.Feng)
    {
        buf[21] |=0x01;
    }
    if(src->symbol.Ping)
    {
        buf[21] |=0x02;
    }
    if(src->symbol.Gu)
    {
        buf[22] |=0x10;
    }
    
    if(src->symbol.shengyu)
    {
        buf[18] |=0x08;
    }
    if(src->symbol.phaseA)
    {
        buf[16] |=0x01;
    }
    if(src->symbol.phaseB)
    {
        buf[16] |=0x02;
    }
    if(src->symbol.phaseC)
    {
        buf[16] |=0x04;
    }
    if(src->symbol.phaseN)
    {
        buf[16] |=0x08;
    }
    if(src->symbol.cos)
    {
        buf[17] |=0x01;
    }
    if(src->symbol.jiaodu)
    {
        buf[18] |=0x40;
    }
    if(src->symbol.jieti)
    {
        buf[18] |=0x04;
    }
    if(src->symbol.jietitao1)
    {
        buf[18] |=0x80;
    }
    if(src->symbol.jietitao2)
    {
        buf[23] |=0x01;
    }
    if(1==src->symbol.jietiPrice)
    {
        buf[14] |=0x1;
    }
    else if(2==src->symbol.jietiPrice)
    {
        buf[14] |=0x2;
    }
    else if(3==src->symbol.jietiPrice)
    {
        buf[14] |=0x4;
    }
    else if(4==src->symbol.jietiPrice)
    {
        buf[14] |=0x8;
    }
//  if(src->symbol.sheqian)
//  {
//      buf[18] |=0x01;
//  }
    if(src->symbol.shengyu)
    {
        buf[18] |=0x08;
    }
    if(src->symbol.Xu)
    {
        buf[19] |=0x80;
    }
    if(src->symbol.Dian)
    {
        buf[19] |=0x40;
    }
    if(src->symbol.Liang)
    {
        buf[19] |=0x04;
    }
    if(src->symbol.fei)
    {
        buf[20] |=0x40;
    }
    if(src->symbol.jiage)
    {
        buf[20] |=0x08;
    }
    if(src->symbol.Shi)
    {
        buf[20] |=0x04;
    }
    if(src->symbol.Ya)
    {
        buf[21] |=0x80;
    }
    if(src->symbol.Liu)
    {
        buf[21] |=0x40;
    }
    if(src->symbol.Power)
    {
        buf[21] |=0x08;
    }
    if(src->symbol.timeshi)
    {
        buf[21] |=0x04;
    }
    if(src->symbol.timejian)
    {
        buf[22] |=0x20;
    }
    if(src->symbol.duan)
    {
        buf[22] |=0x40;
    }
    
    if(src->symbol.wan)
    {
        buf[23] |=0x20;
    }
    if(src->symbol.yuan)
    {
        buf[23] |=0x10;
    }

    if(src->symbol.KW)
    {
        buf[22] |=0x80;
        buf[23] |=0xC0; // 0x80 + 0x40
    }
    if(src->symbol.h1)
    {
        buf[22] |=0x02;
    }
    if(src->symbol.kvar)
    {
        buf[24] |=0x10;
        buf[22] |=0x08;
    }
    if(src->symbol.kva)
    {
        buf[22] |=0x84;
        buf[23] |=0x80;
    }
    if(src->symbol.kvah)
    {
        buf[22] |=0x86;
        buf[23] |=0x80;
    }
    
    if(src->symbol.h2)
    {
        buf[22] |=0x01;
    }
    if(src->symbol.V)
    {
        buf[23] |=0x80;
    }
    if(src->symbol.A)
    {
        buf[22] |=0x04;
    }


    if(src->symbol.Ua)
    {
        buf[3] |=0x40;
    }
    if(src->symbol.Ub)
    {
        buf[3] |=0x80;
    }
    if(src->symbol.Uc)
    {
        buf[2] |=0x08;
    }
    if(src->symbol.nixiangxu)
    {
        buf[2] |=0x04;
    }
    if(src->symbol.symbol_1)
    {
        buf[2] |=0x40;
    }
    if(src->symbol.Ia)
    {
        buf[2] |=0x80;
    }
    if(src->symbol.symbol_2)
    {
        buf[1] |=0x08;
    }
    if(src->symbol.Ib)
    {
        buf[1] |=0x04;
    }
    if(src->symbol.symbol_3)
    {
        buf[1] |=0x40;
    }
    if(src->symbol.Ic)
    {
        buf[1] |=0x80;
    }
    if(src->symbol.shiduan1)
    {
        buf[0] |=0x08;
    }
    if(src->symbol.shiduan2)
    {
        buf[0] |=0x04;
    }
    if(src->symbol.batter1)
    {
        buf[0] |=0x02;
    }
    if(src->symbol.batter2)
    {
        buf[0] |=0x10;
    }
    if(src->symbol.GprsZaixian)
    {
        buf[3] |=0x08;
    }
    i=src->symbol.GprsXinhao;
    switch(i)
    {
        case 7:
        case 6:
        case 5:
        case 4:
            buf[11] |=0x10;
            buf[3] |=0x07;
            break;
        case 3:
            buf[3] |=0x07;
            break;
        case 2:
            buf[3] |=0x06;          
            break;
//      case 1:
//          buf[3] |=0x06;          
//          break;
        case 1:
            buf[3] |=0x04;
            break;
        default:
            
            break;
    }

    if(src->symbol.tongxunIr)
    {
        buf[7] |=0x10;
    }
    
    if(src->symbol.tongxun4851)
    {
        buf[7] |=0x10;
        buf[5] |=0x10;
    }
    if(src->symbol.tongxun4852)
    {
        buf[7] |=0x10;
        buf[4] |=0x10;
    }
    if(src->symbol.tongdian)
    {
        buf[9] |=0x10;
    }

    if(src->symbol.biancheng)
    {
        buf[3] |=0x10;
    }

    if(src->symbol.suoding)
    {
        buf[3] |=0x20;
    }

    if(src->symbol.shiyanshi)
    {
        buf[2] |=0x02;
    }
    if(src->symbol.baojing)
    {
        buf[2] |=0x01;
    }
    if(src->symbol.dukazhong)
    {
        buf[13] |=0x10;
        buf[2] |=0x10;
    }
    if(src->symbol.chenggong)
    {
        buf[13] |=0x10;
        buf[2] |=0x20;
    }
    if(src->symbol.shibai)
    {
        buf[13] |=0x10;
        buf[1] |=0x02;
    }
    if(src->symbol.qinggoudian)
    {
        buf[1] |=0x01;
    }
    if(src->symbol.touzhi)
    {
        buf[1] |=0x10;
    }
    if(src->symbol.lazha)
    {
        buf[1] |=0x20;
    }
    if(src->symbol.tunji)
    {
        buf[23] |=0x08;
    }
    ucTempDisplayTimesUse++;
    if(ucTempDisplayTimesUse>250)
    {
        ucTempDisplayTimesUse=0;
        InitializeBu9792();
    }
    RefreshBu9792(buf, lcdPara.blinking);
#endif    
}
#endif
uchar ucDisplayPrintEnable=GAL_YES;
/*************************************************************
Function: 更新LCD显示内容
Input: Src：内容
Output: 无
Application area:  
Explain: 
Modification register:
**************************************************************/
void ReflashLCDDisplay(STR_DISPLAYMEMORY* src)
{
    //if(LCDRefalshEn == 1)
    if(ucDisplayPrintEnable == GAL_YES)
    {
        //DisplayMemoryMappingLCD(src);
        /*DISPLATRACE("Display-> %02x %02x %02x %02x %02x %02x %02x %02x\n", \
                        src->value1[0],src->value1[1],src->value1[2],src->value1[3],    \
                        src->value1[4],src->value1[5],src->value1[6],src->value1[7]);
                        */
        uchar ucDisplay[10];
        static uchar ucDisplayLast[10], ucAlarmLast[5]={0xff, 0xff, 0xff, 0xff, 0};
        uchar idx, ucNumPoint=0;
        for(idx=0; idx<8; idx++)
        {
            ucDisplay[idx] = src->value1[idx];
        }
        ucDisplay[8] = 0;
        ucDisplay[9] = 0;

        if(src->symbol.DP8 == 1)// 1 为小数
        {
            ucNumPoint = 1;
        }
        else if(src->symbol.DP7 == 1)// 2 为小数
        {
            ucNumPoint = 2;
        }
        else if(src->symbol.DP6 == 1)// 3 为小数
        {
            ucNumPoint = 3;
        }
        else if(src->symbol.DP5 == 1)// 4 为小数
        {
            ucNumPoint = 4;
        }
        else if(src->symbol.DP4 == 1)// 5 为小数
        {
            ucNumPoint = 5;
        }
        else if(src->symbol.DP3 == 1)// 6 为小数
        {
            ucNumPoint = 6;
        }
        if(ucNumPoint>0)
        {
            for(idx=7; idx>=(8-ucNumPoint); idx--)
            {
                ucDisplay[idx+1]=ucDisplay[idx];
            }
            ucDisplay[idx+1]='.';
        }
        if((memcmp(ucDisplay, ucDisplayLast, 10) != 0) || (RSOFT_RTC_SECOND == 0))
        //if((memcmp(ucDisplay, ucDisplayLast, 9) != 0))
        {
            DISPLATRACE("Display->%02x:%02x:%02x  %s\n", RSOFT_RTC_HOUR, RSOFT_RTC_MINUTE, RSOFT_RTC_SECOND, ucDisplay);
            memcpy(ucDisplayLast, ucDisplay, 9);
        }
        //if((*((ulong*)ucAlarmStatusLedGreen) != *((ulong*)ucAlarmLast)) || (RSOFT_RTC_SECOND == 0))
        if(((memcmp(ucAlarmLast, ucAlarmStatusLedGreen, 4) != 0)) || (RSOFT_RTC_SECOND == 0))
        {
            DISPLATRACE("LedAlarm->%02x %02x %02x %02x\n", ucAlarmStatusLedGreen[0], ucAlarmStatusLedGreen[1], ucAlarmStatusLedGreen[2], ucAlarmStatusLedGreen[3]);
            //*((ulong*)ucAlarmLast) = *((ulong*)ucAlarmStatusLedGreen);
            memcpy(ucAlarmLast, ucAlarmStatusLedGreen, 4);
        }
#if 0        
        DISPLATRACE("Kw-> %02x %02x %02x %02x\n", RAM[RAM_CURRENT_KW_ALL+0],RAM[RAM_CURRENT_KW_ALL+1],  \
                                             RAM[RAM_CURRENT_KW_ALL+2],RAM[RAM_CURRENT_KW_ALL+3]);
        DISPLATRACE("Kwh-> %02x %02x %02x %02x %02x\n",   RAM[RAM_KWH_F_ALL+0],RAM[RAM_KWH_F_ALL+1],  \
                                                    RAM[RAM_KWH_F_ALL+2],RAM[RAM_KWH_F_ALL+3],RAM[RAM_KWH_F_ALL+4]);
        DISPLATRACE("Vol-> %02x %02x %02x %02x\n", RAM[RAM_CURRENT_V_A+0],RAM[RAM_CURRENT_V_A+1],  \
                                             RAM[RAM_CURRENT_V_A+2],RAM[RAM_CURRENT_V_A+3]);
#endif        
        //LCDRefalshEn = 0;
    }
}


/*************************************************************
Function: 初始化LCD
Input: 
Output: 无
Application area: 系统启动时调用
Explain: 
Modification register:
**************************************************************/
void InitLCD(void)
{
    memset(&displayMemory,0,sizeof(STR_DISPLAYMEMORY));
    LCDRefalshEn = 0;
    lcdPara = LCDDefaultPara;
#if 0
    if(lcdPara.LCDBackLed)
    {
        ClrLedBackLight();
    }
    else
    {
        SetLedBackLight();
    }
#endif
    //InitializeBu9792();
    //DisplayMode(lcdPara.blinking);
    LCDSwitch(1);
}


/*************************************************************
Function: 更新LED显示
Input: LEDDisplay：显示内容
Output: 无
Application area:  
Explain: 
Modification register:
**************************************************************/
void ReflashLEDDisplay(STR_LED_DISPLAY* LEDDisplay)
{
    if(LEDDisplay->alarmLED1)
    {
//          ALARMA_LED_ON;
    }
    else
    {
//          ALARMA_LED_OFF;
    }
    if(LEDDisplay->alarmLED2)
    {
//          ALARMB_LED_ON;
    }
    else
    {
//           ALARMB_LED_OFF;
    }
}


/*************************************************************
Function: 初始化LED
Input: 
Output: 无
Application area: 系统启动时调用
Explain: 
Modification register:
**************************************************************/
void InitLED(void)
{
    ;
}
void ReflashLcdAllByte(uchar ucData)
{
    uchar buf[32];
    memset(&buf[0],  ucData, 32);
    //RefreshBu9792(buf, lcdPara.blinking);
}

/*void DisplayFullScreen(void)
{
    ReflashLcdAllByte(0xff);
}*/
void DisplayEmptyScreen(void)
{
    ReflashLcdAllByte(0x00);
}

#if 0
void EspDisplayOfOp(const uchar *StrShow, uchar persent)
{
    u16 i;
    uchar buffer[2];
    STR_DISPLAYMEMORY displayMemoryData;

    memset((uchar*)&displayMemoryData,0,sizeof(STR_DISPLAYMEMORY));
    for(i=0; i<8; i++)
    {
        if(StrShow[i] == 0)
            break;
        displayMemoryData.value1[i] = StrShow[i];
    }
    for(; i<8; i++)
    {
         displayMemoryData.value1[i] = ' ';
    }

    IntToData2BCD(persent ,(uchar*)&buffer[0]);
    displayMemoryData.screenNO[4] = buffer[1]>>4;
    displayMemoryData.screenNO[5] = buffer[1]&0x0f;
    displayMemoryData.screenNO[6] = buffer[0]>>4;
    displayMemoryData.screenNO[7] = buffer[0]&0x0f;

    ReflashDisplayMemory(&displayMemoryData);  
    ReflashLCDDisplay(&displayMemory);
}
#endif

