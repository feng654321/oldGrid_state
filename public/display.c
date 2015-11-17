/***************************************************************************
 *      
 *
 *
 * COPYRIGHT (C) 2009 PaxHZ, ALL RIGHTS RESERVED
 * $Abstract: 显示相关接口函数(调试用)
 *
 * $Source:..src\public\display.c$
 * $Author: wudengben$
 * $Date:2009-6-30 8:50$ 
 * $Revision:1.0 显示相关接口函数(调试用)$
 *
 * $Log:display.c$
 * Revision 1.0  2009-6-30 8:50  wudengben
 * 显示相关接口函数(调试用)
 *
 *
 ***************************************************************************/

#include "basetype.h"
#include "display.h"
#include <stdio.h>
#include <time.h>
#include "app_ipcs.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>


FILE *s_terctrl_hfile = NULL;

display_param_t  display_param_default={{0,0},
                                        {0,0},
                                        SCREEN_DISPLAY_HEIGHT - SCREEN_DISPLAY_CMD_NUM,
                                        0                                        
                                       };

display_param_t *p_display_param = &display_param_default;
static int32 s_dis_sem_id;


#define sg_st_point     p_display_param->cur_point
#define sg_st_point_bak p_display_param->cur_point_bak
#define sg_st_cmd_y     p_display_param->y

static uint8 sg_b_update;


void dis_set_bupdate(bool bupdate)
{
    sg_b_update = bupdate;    
}

bool dis_get_bupdate()
{
    return 1;
//    return sg_b_update;
}


bool dis_cancle_ctrl()
{
//    p_display_param->busy = 0;
    struct sembuf sem_b;
    
    sem_b.sem_num = 0;
    sem_b.sem_op  = 1;
    sem_b.sem_flg = SEM_UNDO;    
    semop(s_dis_sem_id,&sem_b,1);  
}

bool dis_wait_busy()
{
    static uint8 t; 
    struct sembuf sem_b;
    
    sem_b.sem_num =  0;
    sem_b.sem_op  = -1;
    sem_b.sem_flg =  SEM_UNDO;
    
    semop(s_dis_sem_id,&sem_b,1);
      
    
//    while(p_display_param->busy)
//    {
//        ;
////        printf("wait...");     
//    }    
//    p_display_param->busy =1;
}


uint8 dis_get_buf_size()
{
    return sizeof(display_param_t);    
}


/*设置参数地址,若不调置,取默认地址,一般在多进程情况下使用*/
void dis_set_buf_add(display_param_t *display_param)
{
    p_display_param = display_param;
    sg_st_point.x = 0;
    sg_st_point.y = 0;
    sg_st_point_bak.x =0;
    sg_st_point_bak.y =0;
    sg_st_cmd_y = SCREEN_DISPLAY_HEIGHT - SCREEN_DISPLAY_CMD_NUM;    
    p_display_param->busy = 0;
    p_display_param->sn   = 0;
}

void dis_return_zero()
{
    dis_wait_busy();
    printf("\r");
//    printf("\n")
    while(sg_st_point.y != 0)
    {
        printf("\b\r");
        sg_st_point.y--;
    }        
    sg_st_point.x=0;
    
    printf("\b\r\n");     
    dis_cancle_ctrl(); 

}

void testout()
{
    printf("sg_st_point=(%d,%d)\n", sg_st_point.x, sg_st_point.y);
}

void dis_pos_out()
{
    printf("\r");
    printf("%02d|",sg_st_point.y);
}
      
        
       
void dis_show_time()
{
    struct tm *ptime;
    time_t timep;    
            
    time(&timep);   
    ptime=localtime(&timep); /*取得当地时间*/  
        
//    printf("\r");    
    printf("<%d:%d:%d>",ptime->tm_hour, ptime->tm_min,ptime->tm_sec);

    
}


void dis_move_direct(uint8 x,uint8 y)
{
//     dis_wait_busy();
    printf("\r");
    
    while(y < sg_st_point.y)
    {
        printf("\b\r");
        sg_st_point.y--;        
    } 

    printf("\b\r\n"); /**< 避免在不同进程中切换时退格无效*/ 
    
    while(y > sg_st_point.y )
    {
        printf("\n");
        sg_st_point.y++;        
    }
//    printf("x=%d",x);
    
    
    for(sg_st_point.x=0;sg_st_point.x < (x&~0x07);sg_st_point.x+=8)
    {
        printf("\t");
    }
    
  
    //dis_cancle_ctrl();
}


void dis_move_to(point pt)
{
    dis_move_direct(pt.x,pt.y);
}

/*纠正光标位置,*/
void dis_correct_cursor()
{
    dis_move_to(sg_st_point);
}


void delay(uint32 tdealy)
{
    while(tdealy--);
    
}

void dis_clear_row()
{
    uint8 i;
    printf("\r");
    
    for(i=0; i<SCREEN_DISPLAY_WIDTH; i++)
    {
        printf(" ");
    }
    printf("\r");    
}

void dis_fill_row(uint8 cha)
{
    uint8 i;
    
    dis_wait_busy();
    printf("\r");
    
    for(i=0; i<SCREEN_DISPLAY_WIDTH; i++)
    {
        printf("%c",cha);
    }
    printf("\r\n");
    
     dis_move_next();
    
    dis_cancle_ctrl();
}

void dis_pos_bakup()
{
    sg_st_point_bak.x = sg_st_point.x;
    sg_st_point_bak.y = sg_st_point.y;
}

void dis_move_to_bak()
{
//    dis_move_direct(sg_st_point_bak.x,sg_st_point_bak.y+2);
    dis_move_to(sg_st_point_bak);
}

void dis_clear_screen(bool bfullscreen)
{
    uint8 i,j;
    uint8  y = SCREEN_DISPLAY_HEIGHT;
    
    dis_pos_bakup();
    dis_return_zero();
    
    if(bfullscreen == 0)
    {
        y -= SCREEN_DISPLAY_CMD_NUM;
    }
    
    for(j=0; j< y; j++)
    {
        for(i=0; i< SCREEN_DISPLAY_WIDTH; i++)
        {
            printf(" ");
        }
        printf("\n");
    }
    sg_st_point.x = SCREEN_DISPLAY_WIDTH;
    sg_st_point.y = y;        
    dis_move_to_bak();
}


void dis_clear_cmd()
{
    dis_move_direct(0,sg_st_cmd_y);   
    dis_clear_row();    
}

/*将光标移动到当前命令行输出处(指定屏幕最后n行循环输出)*/
void dis_cmd_setpos()
{
    struct tm *ptime;
    time_t timep;    
            
    time(&timep);   
    ptime=localtime(&timep); /*取得当地时间*/          
    
    dis_move_direct(0,sg_st_cmd_y);   
    dis_clear_row();
        
    printf("[cmd %03d time(%d:%d:%d)]",p_display_param->sn,
                ptime->tm_hour, ptime->tm_min,ptime->tm_sec);
                                            
    fprintf(s_terctrl_hfile,"[cmd %03d time(%d:%d:%d)]",p_display_param->sn,
                ptime->tm_hour, ptime->tm_min,ptime->tm_sec);
    fflush(s_terctrl_hfile);                
    
//    printf("[cmd %03d]",p_display_param->sn,sg_st_cmd_y);
    
//    dis_show_time();                                             
    
    p_display_param->sn++;
    sg_st_cmd_y++;
        
    if(sg_st_cmd_y >= SCREEN_DISPLAY_HEIGHT)
    {
        sg_st_cmd_y = SCREEN_DISPLAY_HEIGHT - SCREEN_DISPLAY_CMD_NUM;
    }
    sg_st_point.y++;//纠正当前控制台光标位置,即每次输入后都跳到下一行
    
    
//    sg_st_point.y =y;        
    
}

void dis_move_next()
{
    sg_st_point.y++;
}


void dis_pro_reset()
{
    uint8 i;
    union semun sem_union;   

#if 0     /*多进程显示需有该延时*/
    for(i=0;i<0x2;i++)
    {         
        sleep(0x10);
    }
#endif    
    s_dis_sem_id = semget(TERCTRL_SEM_KEY,1,0666|IPC_CREAT);
    
    
    sem_union.val = 1;
    semctl(s_dis_sem_id,0,SETVAL,sem_union);
}

#ifdef DISPLAY_WRITE_FILE

void dis_openfile()
{
    s_terctrl_hfile = fopen("output.txt","w");
    
    if(s_terctrl_hfile == NULL)
    {
        dis_cmd_output("open file error\n");
    }    
//    fprintf(s_terctrl_hfile,"...\n");    
}

void dis_closefile()
{
    dis_cmd_output("close file \n");
    fclose(s_terctrl_hfile);
}

#else

void dis_openfile()
{
    ;   
}

void dis_closefile()
{
    ;  
}

#endif
//
//void dis_exit_ouput()
//{
//    dis_move_direct(0,SCREEN_DISPLAY_HEIGHT);
//}
//







