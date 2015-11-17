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
    uchar blinking:3;       //0��������1��05HZ��2��1HZ��3��2HZ��
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
    LS_feeRate_7b,      //����   7bits   0:no display 1:�� 2:�� 3:ƽ 4:��   127:all display
    LS_ShiTao,          //ʱ��
    LS_ShiTaoNum_5b,    //ʱ�׺�   5bits 0:no display 1:1 2:2 3:3 4:4   31:all display
    LS_season_2b,       //ʱ����     2bits
    LS_quadrant_3b,     //����  3bits    0:no display 1:1 2:2 3:3 4:4   7:all display
    LS_DangQian,   //��ǰ
    LS_Shang1,     //��
    LS_Shang2,     //��
    LS_month,      // ��
    LS_Fan,        //��
    LS_Zheng,      //��
    LS_zuhe,       //  ���
    LS_fangXiang,  // ��
    LS_Xiang,      // ��
    LS_You,        //��
    LS_Wu,         //��
    LS_Gong,       // �� 
    LS_xx1,        // 1 �����޹����
    LS_xx2,        // 2 �����޹����
    LS_xx3,        // 3 �����޹����
    LS_xx4,        // 4 �����޹����
    LS_Zong,       //��
    LS_Jian,       //��
    LS_Feng,       //��
    LS_Ping,       //ƽ
    LS_Gu,         //��
    LS_shengyu,    //  ʣ��
    LS_phaseA,     // A ��
    LS_phaseB,     // B ��
    LS_phaseC,     // C ��
    LS_phaseN,     // N ��
    LS_cos,        // cos
    LS_jiaodu,     // jiaodu
    LS_jieti,      // ����
    LS_sheqian,   // ��Ƿ
    LS_Xu,         // ��
    LS_Liang,      //��
    LS_Dian,       //��
    LS_fei,        //��
    LS_jiage,      //�۸�  
    LS_Shi,        //ʧ
    LS_Ya,         //ѹ
    LS_Liu,        //��
    LS_Power,      //����
    LS_timeshi,    // ʱ���ʱ 
    LS_timejian,   // ʱ��ļ�
    LS_duan,       // ��
    LS_KW,         //KW
    LS_h1,         //h1
    LS_h2,         //h2
    LS_A,          //A
    LS_V,          //V
    LS_kvar,       //kvar
    LS_kva,        // kva
    LS_kvah,       // kvah
    LS_wan,        //��
    LS_yuan,       // Ԫ
    LS_meterNum,   //���
    LS_changshu,   //����
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
    
    uchar feeRate:7;    //����      0:no display 1:�� 2:�� 3:ƽ 4:��   127:all display
    
    uchar ShiTao:1;     //ʱ��
    uchar ShiTaoNum:5;  //ʱ�׺�    0:no display 1:1 2:2 3:3 4:4   31:all display
    uchar season:2;     //ʱ����
    
    uchar quadrant:3;   //����      0:no display 1:1 2:2 3:3 4:4   7:all display

    uchar DangQian:1;   //��ǰ
    uchar Shang1:1;     //��
    uchar Shang2:1;     //��   //IT IS NO USE NOW
    uchar month:1;      // ��
//  uchar ZuiDa:1;      //���
    uchar Fan:1;        //��
    uchar Zheng:1;      //��
    uchar zuhe:1;       //  ���
    uchar fangXiang:1;  // ��

    uchar Xiang:1;      // ��
    
    uchar You:1;        //��
    uchar Wu:1;         //��
    uchar Gong:1;       // �� 
    uchar wugongxiangxian1:1;       // 1 �����޹����
    uchar wugongxiangxian2:1;       // 2 �����޹����
    uchar wugongxiangxian3:1;       // 3 �����޹����
    uchar wugongxiangxian4:1;       // 4 �����޹����
    uchar Zong:1;       //��
    uchar Jian:1;       //��
    uchar Feng:1;       //��
    uchar Ping:1;       //ƽ
    uchar Gu:1;         //��
    uchar shengyu:1;    //  ʣ��



    uchar phaseA:1;     // A ��
    uchar phaseB:1;     // B ��
    uchar phaseC:1;     // C ��
    uchar phaseN:1;     // N ��

    uchar cos:1;        // cos
    uchar jiaodu:1;     // jiaodu
    uchar jieti:1;      // ����
    uchar sheqian :1;   // ��Ƿ
    uchar Xu:1;         // ��
    uchar Liang:1;      //��
    uchar Dian:1;       //��
    uchar fei:1;        //��
    uchar jiage:1;      //�۸�  
    uchar Shi:1;        //ʧ
    uchar Ya:1;         //ѹ
    uchar Liu:1;        //��
    uchar Power:1;      //����
    uchar timeshi:1;    // ʱ���ʱ 
    uchar timejian:1;   // ʱ��ļ�
    uchar duan:1;       // ��


    uchar KW:1;         //KW
    uchar h1:1;         //h1
    uchar h2:1;         //h2
    uchar A:1;          //A
    uchar V:1;          //V
    uchar kvar:1;       //kvar
    uchar kva:1;        // kva
    uchar kvah:1;       // kvah
    uchar wan:1;        //��
    uchar yuan:1;       // Ԫ
    
    uchar meterNum:1;   //���
    uchar changshu:1;   //����

    uchar jietiPrice:3; // ��ǰ��������״̬
    uchar jietitao1:1;  //  ����1
    uchar jietitao2:1;  //  ����2

    uchar fu:1;         //  ����
    
    uchar Ua:1;         //Ua
    uchar Ub:1;         //Ub
    uchar Uc:1;         //Uc
    uchar nixiangxu:1;  //  ������
    
    uchar symbol_1:1;   //-1
    uchar symbol_2:1;   //-2
    uchar symbol_3:1;   //-3
    uchar Ia:1;         //Ia
    uchar Ib:1;         //Ib
    uchar Ic:1;         //Ic
    uchar shiduan1:1;   //  ��1 ��ʱ��
    uchar shiduan2:1;   //  ��2 ��ʱ��
    uchar batter1:1;    //���1
    uchar batter2:1;    //���2

    uchar tongxunIr:1;  //�绰1
    uchar tongxun4851:1; //�绰1
    uchar tongxun4852:1; //�绰2
    uchar GprsZaixian:1; //GPRS ���߱�־
    uchar GprsXinhao:3;  //GPRS �ź�0

    uchar tongdian:1;   //  ͨ�� 
    uchar biancheng:1;  //  ������
    uchar suoding:1;    //  ��������
    uchar shiyanshi:1;  //  ʵ����״̬
    uchar baojing:1;    //  baojing
    
    uchar dukazhong:1;  // ������
    uchar chenggong:1;  //  �ɹ�
    uchar shibai:1;     //  ʧ��
    uchar qinggoudian:1;    //  �빺��
    uchar touzhi:1;     //  ͸֧
    uchar lazha:1;      //  ��բ
    uchar tunji:1;      //  �ڻ�

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
