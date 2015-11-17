#ifndef DISPLAY_API_H
    #define DISPLAY_API_H

#ifdef  DISPLAY_API_GLOBALS
    #define DISPLAY_API_EXT
#else
    #define DISPLAY_API_EXT extern
#endif  

    
#define BLINKING_0HZ    0
#define BLINKING_05HZ   1
#define BLINKING_1HZ    2
#define BLINKING_2HZ    3
typedef  struct
{  
    uchar blinking:3;       //0：不闪，1：05HZ，2：1HZ，3：2HZ。
    uchar LCDBackLed:1;     //back led
    uchar hold:4;
}STR_LCD_PARA;

typedef enum
{
    LS_DP2,
    LS_DP3,
    LS_DP4,
    LS_DP5,
    LS_DP6,
    LS_DP7,
    LS_DP8,
    LS_DP11,
    LS_DP13,
    LS_DP15,
    LS_col1,
    LS_col2,
    //LS_SDP4,            // ?
    LS_feeRate_7b,      //费率   7bits   0:no display 1:尖 2:峰 3:平 4:谷   127:all display
    LS_ShiTao,          //时套
    LS_ShiTaoNum_5b,    //时套号   5bits 0:no display 1:1 2:2 3:3 4:4   31:all display
    LS_season_2b,       //时区表     2bits
    LS_quadrant_3b,     //象限  3bits    0:no display 1:1 2:2 3:3 4:4   7:all display
    LS_DangQian,   //当前
    LS_Shang1,     //上
    LS_Shang2,     //上
    LS_month,      // 月
    LS_Fan,        //反
    LS_Zheng,      //正
    LS_zuhe,       //  组合
    LS_fangXiang,  // 向
    LS_Xiang,      // 相
    LS_You,        //有
    LS_Wu,         //无
    LS_Gong,       // 公 
    LS_xx1,        // 1 象限无功标记
    LS_xx2,        // 2 象限无功标记
    LS_xx3,        // 3 象限无功标记
    LS_xx4,        // 4 象限无功标记
    LS_Zong,       //总
    LS_Jian,       //尖
    LS_Feng,       //峰
    LS_Ping,       //平
    LS_Gu,         //谷
    LS_shengyu,    //  剩余
    LS_phaseA,     // A 相
    LS_phaseB,     // B 相
    LS_phaseC,     // C 相
    LS_phaseN,     // N 相
    LS_cos,        // cos
    LS_jiaodu,     // jiaodu
    LS_jieti,      // 阶梯
    LS_sheqian,   // 赊欠
    LS_Xu,         // 需
    LS_Liang,      //量
    LS_Dian,       //电
    LS_fei,        //费
    LS_jiage,      //价格  
    LS_Shi,        //失
    LS_Ya,         //压
    LS_Liu,        //流
    LS_Power,      //功率
    LS_timeshi,    // 时间的时 
    LS_timejian,   // 时间的间
    LS_duan,       // 段
    LS_KW,         //KW
    LS_h1,         //h1
    LS_h2,         //h2
    LS_A,          //A
    LS_V,          //V
    LS_kvar,       //kvar
    LS_kva,        // kva
    LS_kvah,       // kvah
    LS_wan,        //万
    LS_yuan,       // 元
    LS_meterNum,   //表号
    LS_changshu,   //常数
}EN_LCD_SYMBOL;

typedef  struct
{  
    uchar DP2:1;
    uchar DP3:1;
    uchar DP4:1;
    uchar DP5:1;
    uchar DP6:1;
    uchar DP7:1;
    uchar DP8:1;
    uchar DP11:1;
    uchar DP13:1;
    uchar DP15:1;

    uchar col1:1;
    uchar col2:1;
    
    uchar SDP4:1;       // ?
    
    uchar feeRate:7;    //费率      0:no display 1:尖 2:峰 3:平 4:谷   127:all display
    
    uchar ShiTao:1;     //时套
    uchar ShiTaoNum:5;  //时套号    0:no display 1:1 2:2 3:3 4:4   31:all display
    uchar season:2;     //时区表
    
    uchar quadrant:3;   //象限      0:no display 1:1 2:2 3:3 4:4   7:all display

    uchar DangQian:1;   //当前
    uchar Shang1:1;     //上
    uchar Shang2:1;     //上   //IT IS NO USE NOW
    uchar month:1;      // 月
//  uchar ZuiDa:1;      //最大
    uchar Fan:1;        //反
    uchar Zheng:1;      //正
    uchar zuhe:1;       //  组合
    uchar fangXiang:1;  // 向

    uchar Xiang:1;      // 相
    
    uchar You:1;        //有
    uchar Wu:1;         //无
    uchar Gong:1;       // 公 
    uchar wugongxiangxian1:1;       // 1 象限无功标记
    uchar wugongxiangxian2:1;       // 2 象限无功标记
    uchar wugongxiangxian3:1;       // 3 象限无功标记
    uchar wugongxiangxian4:1;       // 4 象限无功标记
    uchar Zong:1;       //总
    uchar Jian:1;       //尖
    uchar Feng:1;       //峰
    uchar Ping:1;       //平
    uchar Gu:1;         //谷
    uchar shengyu:1;    //  剩余



    uchar phaseA:1;     // A 相
    uchar phaseB:1;     // B 相
    uchar phaseC:1;     // C 相
    uchar phaseN:1;     // N 相

    uchar cos:1;        // cos
    uchar jiaodu:1;     // jiaodu
    uchar jieti:1;      // 阶梯
    uchar sheqian :1;   // 赊欠
    uchar Xu:1;         // 需
    uchar Liang:1;      //量
    uchar Dian:1;       //电
    uchar fei:1;        //费
    uchar jiage:1;      //价格  
    uchar Shi:1;        //失
    uchar Ya:1;         //压
    uchar Liu:1;        //流
    uchar Power:1;      //功率
    uchar timeshi:1;    // 时间的时 
    uchar timejian:1;   // 时间的间
    uchar duan:1;       // 段


    uchar KW:1;         //KW
    uchar h1:1;         //h1
    uchar h2:1;         //h2
    uchar A:1;          //A
    uchar V:1;          //V
    uchar kvar:1;       //kvar
    uchar kva:1;        // kva
    uchar kvah:1;       // kvah
    uchar wan:1;        //万
    uchar yuan:1;       // 元
    
    uchar meterNum:1;   //表号
    uchar changshu:1;   //常数

    uchar jietiPrice:3; // 当前阶梯运行状态
    uchar jietitao1:1;  //  阶梯1
    uchar jietitao2:1;  //  阶梯2

    uchar fu:1;         //  负号
    
    uchar Ua:1;         //Ua
    uchar Ub:1;         //Ub
    uchar Uc:1;         //Uc
    uchar nixiangxu:1;  //  逆向序
    
    uchar symbol_1:1;   //-1
    uchar symbol_2:1;   //-2
    uchar symbol_3:1;   //-3
    uchar Ia:1;         //Ia
    uchar Ib:1;         //Ib
    uchar Ic:1;         //Ic
    uchar shiduan1:1;   //  第1 套时段
    uchar shiduan2:1;   //  第2 套时段
    uchar batter1:1;    //电池1
    uchar batter2:1;    //电池2

    uchar tongxunIr:1;  //电话1
    uchar tongxun4851:1; //电话1
    uchar tongxun4852:1; //电话2
    uchar GprsZaixian:1; //GPRS 在线标志
    uchar GprsXinhao:3;  //GPRS 信号0

    uchar tongdian:1;   //  通电 
    uchar biancheng:1;  //  编程许可
    uchar suoding:1;    //  密码锁定
    uchar shiyanshi:1;  //  实验室状态
    uchar baojing:1;    //  baojing
    
    uchar dukazhong:1;  // 读卡中
    uchar chenggong:1;  //  成功
    uchar shibai:1;     //  失败
    uchar qinggoudian:1;    //  请购电
    uchar touzhi:1;     //  透支
    uchar lazha:1;      //  拉闸
    uchar tunji:1;      //  囤积

    uchar HOLD:4;
    uchar issigned:1;
    uchar LCDRefalsh:1; //this bit is Refalsh LCD flag,if this bit set ,you must Refalsh LCD display
}STR_DISPLAYSYMBOL;

typedef  struct
{  
    uchar value1[8];
    uchar value2[8];
    uchar screenNO[8];
    uchar ShowIndex[2];
    //uchar last[2];
    STR_DISPLAYSYMBOL symbol;
}STR_DISPLAYMEMORY;

typedef  struct
{
    uchar alarmLED1:1;
    uchar alarmLED2:1;
    uchar alarmLED3:1;
    uchar alarmLED4:1;
    uchar alarmLED5:1;
    uchar alarmLED6:1;
    uchar hold:2;    
}STR_LED_DISPLAY;



DISPLAY_API_EXT STR_DISPLAYMEMORY displayMemory;    //LCD display data store here
DISPLAY_API_EXT STR_LCD_PARA lcdPara;
#define LCDRefalshEn displayMemory.symbol.LCDRefalsh    //this bit is Refalsh LCD flag,if this bit set ,you must Refalsh LCD display


DISPLAY_API_EXT void LCDSwitch(uchar switchEn);
DISPLAY_API_EXT uchar SetLCD(STR_LCD_PARA* para );
DISPLAY_API_EXT void ReflashDisplayMemory(STR_DISPLAYMEMORY* src);
DISPLAY_API_EXT void ReflashLEDDisplay(STR_LED_DISPLAY* LEDDisplay);


DISPLAY_API_EXT void InitLED(void);
DISPLAY_API_EXT void InitLCD(void);
DISPLAY_API_EXT void ReflashLCDDisplay(STR_DISPLAYMEMORY* src);
DISPLAY_API_EXT void ClrLedBackLight(void);
DISPLAY_API_EXT void SetLedBackLight(void);
DISPLAY_API_EXT void ReflashLcdAllByte(uchar ucData);
DISPLAY_API_EXT void DisplayFullScreen(void);
DISPLAY_API_EXT void DisplayEmptyScreen(void);
DISPLAY_API_EXT void EspDisplayOfOp(const string *StrShow, uchar persent);

#endif
