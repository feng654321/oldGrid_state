/***************************************************************************
 *
 *
 *
 * COPYRIGHT (C) 2009 PaxHZ, ALL RIGHTS RESERVED
 * $Abstract: 时间模块头文件
 *
  * $Source: src\include\timer.h$
 * $Author: wudengben$
 * $Date:2009-6-29 15:17$ 
 * $Revision:1.0 时间模块头文件$
 *
 * $Log:timer.h$
 * Revision 1.0  2009-6-29 15:15  wudengben
 * 时间模块头文件
 *
 *
 ***************************************************************************/

#ifndef  APP_TIMER_H
#define  APP_TIMER_H


//#include <time.h>
#include <basetype.h>

#define DATA_M(month)       (month-1)
#define TIME_M(hour,minute)	((hour)*60 + (minute))


#define TIMER_DELAY_NUM       0x20
#define TIMER_NUM_MAX         0x10

#define INVAILD_TIMER_HANDLE  0xff
#define INVAILD_DELAY_TIMER   0xff
#define INVAILD_TIMER_ID_CODE 0xffffffff

#define DELAY_TIME_OUT      1
#define DELAY_CONTINUE      0

uint32 get_trig_timer_id_code(uint8 handle);




/**初始化定时器*****************************************
@step:      设置定时频率,越小精度度越高,单位为us;
@return:    是否成功

*******************************************************/
bool inittimer(uint32 step);

void init_timer_var(void);
    

/**以线程方式初始化定时器
@about:     此时注册的定时服务与主进程以不同线程的方式进行*/
void timer_pthread_init();


/**         以主进程空闲时调用定时逻辑的方式初始化定时器,以保证信号打断主进程时正在处理不可被
            打断的操作时引起异常*/
bool timer_idle_init();



/**空闲处理函数,主程序在空闲时调用该函数,以启动设置的定时程序,与timer_idle_init配合使用
@about:     该函数由主程序调用,否则定时处理函数在时间满足后也不会被触发,只是不断运行该函数才会
            触发*/
void timer_idel_deal();

    
/**设置定时频率，并设置定时操作的次数********************
@nElapse:   指定触发周期，即多少时间触发一次,也表示第一次触发时间
@lpfnTimer: 函数指针，即触发的动作,暂考虑无参,若需要参数可定义带参的操作;
@times:     指定触发后执行该操作次数，0表示无限次
@return:    返回操作句柄,该句柄可用于关闭;
@ps.:       暂不考虑进程间的通用性,但可以通过代码复制来实现共用

********************************************************/
uint8 settimer(uint32 nElapse,void (*lpfnTimer)(void),uint32 times);

uint8 settimer_ex(uint32 nElapse,void (*lpfnTimer) (void *),void * param,uint32 times);

uint8 settimer_100ms(uint32 nElapse,void (*lpfnTimer) (void *),void * param,uint32 times);

/**取消之前设置的周期性操作*****************************
@handle:    操作句柄,调用SetTimer成功时返回;
@return:     无效句柄;

********************************************************/
uint8 cancle_timer(uint8 handle);


/*比较pData0与pData1的日期

@return:    若pData0 <pData1,返回0
            若pData0==pData1,返回1
            若pData0 >pData1,返回2
*/

uint8  datacompare(struct day_data_st * pdata0,struct day_data_st * pdata1,uint8 byear);

/* 设置触发时间，启动相应的动作***************************
@SetTime   设置触发时间,为hh*60+mm,表示hh:mm(24小`时计时制),其时区与系统当前时区相同;
@lpfnTimer 函数指针，即触发的动作
@times:    指定触发后执行该操作次数，0表示无限次
@return    返回是否已经成功设置;
@ps.:      仅不考虑进程间的通用性,但可以通过代码复制来实现共用;
@暂不考虑实现，考虑到可以通过将设定时间和系统时间都转换成秒即可通过SetTimer()实现

*********************************************************/
uint8 settrigtimer(void (*lpfnTimer)(void),uint32 *idcode,uint32 SetTime,uint32 times);


/*取消之前指定的延时操作*/
uint8 cancel_delay_secend(uint8 delay_handle);


/*非阻塞型延时操作
@ delays:   指定延时时间,在*handle为无效时使用,用于初始化,否则根据*handle保存的延时信息进行延时
@ handle:   延时定时器句柄,该句柄在延时时间到后会被置无效,若再调用会开始新的一轮计时
*/
bool delay_in_secend(uint32 delays,uint8 *handle);


uint64 show_time();
void push_time();
void pop_time();

#endif//APP_TIMER_H

