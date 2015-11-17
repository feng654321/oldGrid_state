/***************************************************************************
 * <��������˵��,��ͷ�ļ���������>
*
*
* COPYRIGHT (C) 2009 PaxHZ, ALL RIGHTS RESERVED
* $Abstract: ��ʱ����ؽӿں���
*
* $Source:..src\public\timer.c$
* $Author: wudengben$
* $Date:2009-6-30 8:49$ 
* $Revision:1.0$
*
* $Log:timer.c$
* Revision 1.0  2009-6-30 8:49  wudengben
* ��ʱ����ؽӿں���
*
*
***************************************************************************/



#include "app_timer.h"
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


typedef struct tag_time_handle
{
    void (*lp_timer)(void *);   /*��������*/
    void *param;             /*����,ָ���ĺ�������*/
    int32 timervalue;         /*������Ϊ0Ϊ��������*/
    uint32 timerinterval;     /*����������*/
    uint32 times;             /*ִ�д���*/
}time_handle,*p_time_handle;

typedef struct tag_trig_timer_handle
{
    void (*lp_trigtimer)(void);   /*��������*/
    uint32 starttime;             /*����ʱ��*/
    uint32 times;                 /*ִ�д���*/
    uint8  is_started_today;	  /*�����Ƿ��Ѿ�ִ��*/
    uint32 idcode;                /*ʶ����,��ʱ���޸ĺ�,����ȡ����������Ĵ�������*/
}trig_timer_handle,*p_trig_timer_handle;

static time_handle       sg_st_timer_handle[TIMER_NUM_MAX]={0};
static trig_timer_handle sg_st_trig_timer_handle[TIMER_NUM_MAX]={0}; 
static bool sg_timer_atom=0;
static uint32 sg_timer_delaytime[TIMER_DELAY_NUM]={0};
static bool sg_timer_b_use_alarm = 0;
static bool sg_timer_b_use_idle  = 0; /*�Ƿ�ͨ�����д������ʽ���ö�ʱ��*/
static uint32 sg_timer_sec_delay = 0;  /*ʱ���ۼ���ʱ*/
static uint32 timer_sec_count=0;


//
//#include <execinfo.h> 
//#include <stdio.h> 
//#include <stdlib.h> 
// 
// /* Obtain a backtrace and print it to stdout. */ 
// void print_trace (void) 
// { 
//    void *array[10]; 
//    size_t size; 
//    char **strings; 
//    size_t i; 
//    
//    size = backtrace (array, 10); 
//    strings = backtrace_symbols (array, size); 
//    
//    log_printf ("********Obtained %zd stack frames.********\n", size); 
//    
//    for (i = 0; i < size; i++) 
//    log_printf ("./bt:%s\n", strings[i]); 
//    
//    free (strings); 
//} 



void timer_set_atom()
{
    sg_timer_atom = 1;
}


void timer_clear_atom()
{
    sg_timer_atom = 0;
}


void timer_idel_deal()
{
    uint32 sec_delay;
    uint8 i;
    sec_delay = sg_timer_sec_delay;
    sg_timer_sec_delay = 0;
    
     for(i=0; i<TIMER_NUM_MAX; i++)
    {
        if(sg_st_timer_handle[i].lp_timer != NULL)
        {
        	
            if(sg_st_timer_handle[i].timervalue > sec_delay)/*0��������²������*/
            {
                sg_st_timer_handle[i].timervalue -= sec_delay;
            }
            else/*��ʱʱ�䵽*/
            {
#if 0
                uint8 delay_times = 1;
                delay_times = (sec_delay-sg_st_timer_handle[i].timervalue)/sg_st_timer_handle[i].timerinterval +1;
                while(delay_times--)/*�ж�����ʱ���Ƿ�ﵽ��һ�β���ʱ��*/
#endif                

                {
                    (sg_st_timer_handle[i].lp_timer)(sg_st_timer_handle[i].param);
                    if(sg_st_timer_handle[i].times !=0)
                    { 
                        sg_st_timer_handle[i].times--;
                        if(sg_st_timer_handle[i].times == 0){/*ָ�������������,�������*/
                            sg_st_timer_handle[i].lp_timer = NULL;
                            goto breakloop;
                        }
                    }    
                }
                /*��������ʱ��,����һ������,��ɺ���ȫ������*/
                sg_st_timer_handle[i].timervalue = sg_st_timer_handle[i].timerinterval - 
                                                    (sec_delay-sg_st_timer_handle[i].timervalue)%
                                                        sg_st_timer_handle[i].timerinterval;

breakloop:
                continue;
            }//else
        }//if
    }//for
}


void timer_handler()
{
	uint8 i;		

	/*��ʱ����ʱ�Ƿ���*/
    for(i=0; i<TIMER_DELAY_NUM; i++)
    {
        if(sg_timer_delaytime[i]!=0)
        {            
            sg_timer_delaytime[i]--;
        }
    }    
    sg_timer_sec_delay++;
    
    if(sg_timer_b_use_idle == 0)/*��δ���ÿ��д������ʱ*/
    {
        timer_idel_deal();
    }        
    if(sg_timer_b_use_alarm != 0)/*��δʹ���ź�ʱ������ʼ��alarm*/
    {
        alarm(1);
    }
}


/**< ���ö�ʱ��*/
uint8 settimer(uint32 nElapse,void (*lpfnTimer) (void),uint32 times)
{
    return settimer_100ms(10*nElapse,(void (*)(void *))lpfnTimer,(void *)NULL,times);
}


/**< ���ö�ʱ��*/
uint8 settimer_ex(uint32 nElapse,void (*lpfnTimer) (void *),void * param,uint32 times)
{
    return settimer_100ms(10*nElapse,lpfnTimer,param,times);
}

uint8 settimer_100ms(uint32 nElapse,void (*lpfnTimer) (void *),void * param,uint32 times)
{
    uint8 i;   

    for(i=0; i<0x10; i++)
    {
        if(sg_st_timer_handle[i].lp_timer==NULL)
        {               
            sg_st_timer_handle[i].lp_timer      = lpfnTimer;//(void (*)(void *)) lp
            sg_st_timer_handle[i].times         = times;
            sg_st_timer_handle[i].timervalue    = nElapse;
            sg_st_timer_handle[i].timerinterval = nElapse;
            sg_st_timer_handle[i].param         = param;
            return i;
        }
        continue;
    }
    return 0xff;

}

uint8 cancle_timer(uint8 handle)
{
    if(handle != INVAILD_TIMER_HANDLE)
    {   
        sg_st_timer_handle[handle].lp_timer = NULL;
    }
    return INVAILD_TIMER_HANDLE;
    
}

uint8 updatetimer(uint8 handler,uint32 nElapse,uint32 times)
{
    if(sg_st_timer_handle[handler].lp_timer != NULL)
    {
        sg_st_timer_handle[handler].times         = times;
        sg_st_timer_handle[handler].timervalue    = nElapse;
        sg_st_timer_handle[handler].timerinterval = nElapse;        
    }
}



void trig_time_handler()
{
    time_t timep;
    struct tm *pTime;
    uint32 current_time;
	uint8  i;
    
    time(&timep);   
    pTime=localtime(&timep); /*ȡ�õ���ʱ��*/
	
    current_time = pTime->tm_hour*60 + pTime->tm_min;  
    
	//    xprintf("current_time: %d\n",current_time);     
	
    for(i=0; i<0x10; i++)
    {
        if(sg_st_trig_timer_handle[i].lp_trigtimer != NULL)
        {
			//    		xprintf("current_time: %d ",current_time);         	
			//        	xprintf("starttime[%d]:%d\n",i,sg_st_trig_timer_handle[i].starttime);
            
            if(current_time == sg_st_trig_timer_handle[i].starttime)
            {
				if(sg_st_trig_timer_handle[i].is_started_today == true)/*������ִ��,����ִ��*/
				{
					continue;
				}
                (sg_st_trig_timer_handle[i].lp_trigtimer)();
                sg_st_trig_timer_handle[i].is_started_today = true;
                if(sg_st_trig_timer_handle[i].times !=0)
                { 
                    sg_st_trig_timer_handle[i].times--;
                    if(sg_st_trig_timer_handle[i].times == 0){/*ָ�������������,�������*/
                        xprintf("timeout");
                        sg_st_trig_timer_handle[i].lp_trigtimer = NULL;
                        continue;
                    }
                }//if
            }//if
            else{
				sg_st_trig_timer_handle[i].is_started_today = false;
            }
        }//if
    }//for
}


uint32 get_trig_timer_id_code(uint8 handle)
{
	return  sg_st_trig_timer_handle[handle].idcode;
}

bool cancle_trig_timer(uint8 handle,uint32 id_code)
{
    if(handle == INVAILD_TIMER_HANDLE)
    {
        return true;
    }
    if(sg_st_trig_timer_handle[handle].idcode != id_code)
    {        
        return false;
    }
    sg_st_trig_timer_handle[handle].lp_trigtimer = NULL;
    return true;
}



uint8 settrigtimer(void (*lpfnTimer)(void),uint32 *idcode,uint32 SetTime,uint32 times)  /*���ô���ʱ�䣬������Ӧ�Ķ���*/
{
    static uint8 bInit=0;	
	static uint32 s_timer_id_code;
	uint8 i;
    
    if(bInit == 0)
    {
        bInit = 1;/*�����ж�ʱ�����������ʱ,��ʱ���û���,��ȡ��TrigTimeHandler�Ĳ���*/
        settimer(1,trig_time_handler,0);/*1s���һ��*/
    }
    
    for(i=0; i<0x10; i++)
    {
        if(sg_st_trig_timer_handle[i].lp_trigtimer == NULL)
        {
            s_timer_id_code|=0x80000000;             
            if(idcode != NULL)
            {
                *idcode = s_timer_id_code;
            }
            sg_st_trig_timer_handle[i].idcode       = s_timer_id_code;
            sg_st_trig_timer_handle[i].lp_trigtimer = lpfnTimer;
            sg_st_trig_timer_handle[i].starttime    = SetTime;
            sg_st_trig_timer_handle[i].times        = times;
            s_timer_id_code++;
			
			//            xprintf("sg_st_trig_timer_handle[%d].lp_trigtimer = %x\n",i,sg_st_trig_timer_handle[i].lp_trigtimer);
            return i;
        }
    }
    return  INVAILD_TIMER_HANDLE;     
}

/*�Ƚ�pData0��pData1������

@return:    ��pData0 <pData1,����0
��pData0==pData1,����1
��pData0 >pData1,����2
*/

uint8  datacompare(struct day_data_st * pdata0,struct day_data_st * pdata1,uint8 byear)
{

    if(byear !=0){
        if(pdata0->year > pdata1->year)
        {
            return 2;
        }
        if(pdata0->year < pdata1->year)
        {
            return 0;
        }
    }
    if(pdata0->month > pdata1->month)
    {
        return 2;
    }
    if(pdata0->month < pdata1->month)
    {
        return 0;
    }
    if(pdata0->day > pdata1->day)
    {
        return 2;
        xprintf("return 2");
    }
    if(pdata0->day < pdata1->day)
    {
        return 0;
        xprintf("return 0");
    }
    return 1;
}

void delay_sleep(uint32 delay)
{
    while(delay--){
        sleep(1);
    }
}

uint8 delay_set_secend(uint32 delay)
{
    uint8 i;
    for(i=0; i<TIMER_DELAY_NUM; i++)
    {
        if(sg_timer_delaytime[i] == 0)
        {
            sg_timer_delaytime[i] = delay;
            return i;
        }
    }
    return INVAILD_TIMER_HANDLE;    
}

bool dealy_is_over(uint8 delay_handle)
{
    if(delay_handle == INVAILD_DELAY_TIMER)
    {
        log_printf("INVAILD_DELAY_TIMER\n");
        return 1;/*�޴���ʱ��������ظ���ʱ�����*/
    }    
    return (bool)(sg_timer_delaytime[delay_handle] == 0);
}


uint8 cancel_delay_secend(uint8 delay_handle)
{
    if(delay_handle < TIMER_DELAY_NUM)
    {
        sg_timer_delaytime[delay_handle] = 0;
    }
    return INVAILD_DELAY_TIMER;
}



bool delay_in_secend(uint32 delays,uint8 *handle)
{
    if(delays == 0)
    {
        *handle = INVAILD_DELAY_TIMER;
        return DELAY_TIME_OUT;
    }        
    
    if(*handle == INVAILD_DELAY_TIMER)
    {
        *handle = delay_set_secend(delays);        
    }
    
    if(dealy_is_over(*handle) == 0)/*��ʱʱ�仹δ��*/
    {
        return DELAY_CONTINUE;
    }else
    {
        *handle = INVAILD_DELAY_TIMER;
        return DELAY_TIME_OUT;
    }
}


static void * timer_pthread_deal(void *arg)
{
    inittimer(0);

    while(1){
        pause();
    }   

}


/*ͨ���߳�����ʼ������,��ʱ��ע��Ķ�ʱ�������迼�Ǻ����Ŀ�����,���迼�Ƕ��߳����õ����*/
void timer_pthread_init()
{
    pthread_t a_thread;
    uint32 res;	

    res = pthread_create(&a_thread,NULL,timer_pthread_deal,(void *)NULL);

    if(res!= 0)
    {	
		;
    }
}

/*��ʼ����غ���*/

bool timer_idle_init()
{
    sg_timer_b_use_idle = 1; 
    return inittimer(0);
    
    
}

void init_timer_var(void)
{
	memset(sg_st_timer_handle, 0, sizeof(sg_st_timer_handle));   
}

/*ͨ���źų�ʼ����ʱ��,�˺���ע��Ķ�ʱ������ע�⺯����������*/
bool inittimer(uint32 step)
{
    //if(step == 0)
    //{
    //    step = 100000;
    //}

    //sg_timer_b_use_alarm = 1;

    //timer_sec_count = 1;
    //memset(sg_st_timer_handle,0,sizeof(sg_st_timer_handle));/*fork��,������Ҫ�̳и���������,�����³�ʼ��*/
    
    signal(SIGALRM,timer_handler);   
    
    struct itimerval tick;
    // Initialize struct     
    memset((void *)&tick, 0, sizeof(struct itimerval));
    //Timeout to run function first time           
    tick.it_value.tv_usec   =  100000; // micro sec.             
    //Interval time to run function   
    tick.it_interval.tv_usec = 100000;//step;         
    /* Set timer, ITIMER_REAL : real-time to decrease timer,     
    send SIGALRM when timeout  */  
    setitimer(ITIMER_REAL, &tick, NULL);   
	return true;
}

#if 1//DEBUG_LVEL >=1

uint64 show_time()
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday (&tv , &tz);
    log_printf("show_time: %d.%d\n", tv.tv_sec,tv.tv_usec);    
    return tv.tv_sec*1000000+tv.tv_usec;
}

struct timeval start_tv;
void push_time()
{    
    struct timezone tz;
    gettimeofday (&start_tv , &tz);
}

void pop_time()
{
    struct timezone tz;
    struct timeval tv;
    gettimeofday (&tv , &tz);
    log_printf("the time pushed was %ds.%d.us",tv.tv_sec-start_tv.tv_sec,tv.tv_usec-start_tv.tv_usec);
}
#endif


