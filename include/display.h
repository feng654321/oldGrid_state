/***************************************************************************
 *
 *
 *
 * COPYRIGHT (C) 2009 PaxHZ, ALL RIGHTS RESERVED
 * $Abstract: 显示设备头文件(for debug)
 *
 * $Source:src\include\display.h$
 * $Author: wudengben$
 * $Date:2009-6-29 15:17$ 
 * $Revision:1.0 显示设备头文件(for debug)$
 *
 * $Log:display.h$
 * Revision 1.0  2009-6-29 15:15  wudengben
 * 显示设备头文件(for debug).
 *
 ***************************************************************************/

#ifndef DISPLAY_H

#define DISPLAY_H
    
#include <stdio.h>
#include "basetype.h"

//#define _UNSUPPORT_CMD     

//#define DISPLAY_WRITE_FILE

#ifndef DISPLAY_WRITE_FILE

#define fprintf(...)    
#define ffulsh()     
#endif

#define SCREEN_DISPLAY_WIDTH        80
#define SCREEN_DISPLAY_HEIGHT       38
#define SCREEN_DISPLAY_CMD_NUM      5   

#define TERCTRL_SEM_KEY             0x2234

extern FILE *s_terctrl_hfile;
//extern FILE 

typedef struct tag_point
{
    uint8 x;
    uint8 y;
}point,*p_point;


typedef struct tag_display_param
{
    point cur_point;
    point cur_point_bak;
    uint8 y;
    uint8 busy;
    uint32 pid;
    uint8 sn;
}display_param_t;



void dis_correct_cursor();

void dis_return_zero();

void dis_move_to(point pt);

void dis_move_direct(uint8 x,uint8 y);

void dis_clear_row();

void dis_clear_screen(bool bfullscreen);

void dis_move_next();

void dis_pos_bakup();

void dis_move_to_bak();

void dis_pro_reset();

void dis_fill_row(uint8 cha);

void dis_openfile();
void dis_closefile();
bool dis_cancle_ctrl();
bool dis_wait_busy();


void dis_set_bupdate(bool bupdate);
bool dis_get_bupdate();

#define  printf_show_value(value,type)       show_value(value,type,printf)
#define  dis_show_value(value,type)          show_value(value,type,dis_cmd_output)
#define  show_value(value,type,func)         func(#value"="#type"\n",value)

#if ((DEBUG_LEVEL & DEBUG_LEVEL_DISPLAY) != 0)

 void testout();

/*在当前位置输出*/
#define dis_textout_c(...)          do{\
                                        dis_wait_busy();\
                                        dis_clear_row();\
                                        dis_pos_out();\
                                        /*sleep(1);*/\
                                        printf(__VA_ARGS__);\
                                        dis_move_next();\
                                        dis_cancle_ctrl();\
                                    }while(0)

/*在控制号位置输出,设定最后几行为控制台输出，输出时应带\n*/
//#define dis_cmd_output(...)      printf(__VA_ARGS__)


#define dis_cmd_output(...)       do{\
                                        dis_wait_busy();\
                                        dis_pos_bakup();\
                                        dis_cmd_setpos();\
                                        printf(__VA_ARGS__);\
                                        fprintf(s_terctrl_hfile,__VA_ARGS__);\
                                        fflush(s_terctrl_hfile);\
                                        dis_clear_cmd();\
                                        printf("\r...");\
                                        dis_move_to_bak();\
                                        dis_set_bupdate(1);\
                                        dis_cancle_ctrl();\
                                    }while(0)


/*dis_move_direct(0,SCREEN_DISPLAY_HEIGHT);*/
/*
//#define dis_cmd_output(param,...)   do{\
//                                        dis_pos_bakup();\
//                                        dis_cmd_setpos();\
//                                        printf(param,##__VA_ARGS__);\
//                                        dis_move_to_bak();\                                        
//                                    }while(0)
*/
                        
                        
#define dis_system(param)         do{\
                                        dis_wait_busy();\
                                        dis_clear_row();\
                                        system(param);\
                                        dis_move_next();\
                                        dis_cancle_ctrl();\
                                    }while(0)

/**< 指定位置格式化字符串输出 */
#define dis_textout_ex(x,y,...)     do{\
                                        dis_wait_busy();\
                                        dis_move_direct(x,y);\
                                        printf(__VA_ARGS__);\
                                        dis_move_next();\
                                        dis_correct_cursor();\
                                        dis_cancle_ctrl();\
                                    }while(0)


/*在当前位置输出,并将光标移动到下一移(字符串须带\n,)*/                                  
#define dis_textout(...)            do{\
                                        dis_wait_busy();\
                                        printf(__VA_ARGS__);\
                                        dis_move_next();\
                                        dis_correct_cursor();\
                                        dis_cancle_ctrl();\
                                    }while(0)
                                                              
                                                 
#else 

#define dis_printf(...) 
#define dis_textout_c(...)
#define dis_cmd_output(...)      printf(__VA_ARGS__)
#define dis_system(param)
#define dis_textout_ex(x,y,...)                                    
#define dis_textout(...) 

#endif       
#endif
                

