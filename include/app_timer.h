/***************************************************************************
 *
 *
 *
 * COPYRIGHT (C) 2009 PaxHZ, ALL RIGHTS RESERVED
 * $Abstract: ʱ��ģ��ͷ�ļ�
 *
  * $Source: src\include\timer.h$
 * $Author: wudengben$
 * $Date:2009-6-29 15:17$ 
 * $Revision:1.0 ʱ��ģ��ͷ�ļ�$
 *
 * $Log:timer.h$
 * Revision 1.0  2009-6-29 15:15  wudengben
 * ʱ��ģ��ͷ�ļ�
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




/**��ʼ����ʱ��*****************************************
@step:      ���ö�ʱƵ��,ԽС���ȶ�Խ��,��λΪus;
@return:    �Ƿ�ɹ�

*******************************************************/
bool inittimer(uint32 step);

void init_timer_var(void);
    

/**���̷߳�ʽ��ʼ����ʱ��
@about:     ��ʱע��Ķ�ʱ�������������Բ�ͬ�̵߳ķ�ʽ����*/
void timer_pthread_init();


/**         �������̿���ʱ���ö�ʱ�߼��ķ�ʽ��ʼ����ʱ��,�Ա�֤�źŴ��������ʱ���ڴ����ɱ�
            ��ϵĲ���ʱ�����쳣*/
bool timer_idle_init();



/**���д�����,�������ڿ���ʱ���øú���,���������õĶ�ʱ����,��timer_idle_init���ʹ��
@about:     �ú��������������,����ʱ��������ʱ�������Ҳ���ᱻ����,ֻ�ǲ������иú����Ż�
            ����*/
void timer_idel_deal();

    
/**���ö�ʱƵ�ʣ������ö�ʱ�����Ĵ���********************
@nElapse:   ָ���������ڣ�������ʱ�䴥��һ��,Ҳ��ʾ��һ�δ���ʱ��
@lpfnTimer: ����ָ�룬�������Ķ���,�ݿ����޲�,����Ҫ�����ɶ�����εĲ���;
@times:     ָ��������ִ�иò���������0��ʾ���޴�
@return:    ���ز������,�þ�������ڹر�;
@ps.:       �ݲ����ǽ��̼��ͨ����,������ͨ�����븴����ʵ�ֹ���

********************************************************/
uint8 settimer(uint32 nElapse,void (*lpfnTimer)(void),uint32 times);

uint8 settimer_ex(uint32 nElapse,void (*lpfnTimer) (void *),void * param,uint32 times);

uint8 settimer_100ms(uint32 nElapse,void (*lpfnTimer) (void *),void * param,uint32 times);

/**ȡ��֮ǰ���õ������Բ���*****************************
@handle:    �������,����SetTimer�ɹ�ʱ����;
@return:     ��Ч���;

********************************************************/
uint8 cancle_timer(uint8 handle);


/*�Ƚ�pData0��pData1������

@return:    ��pData0 <pData1,����0
            ��pData0==pData1,����1
            ��pData0 >pData1,����2
*/

uint8  datacompare(struct day_data_st * pdata0,struct day_data_st * pdata1,uint8 byear);

/* ���ô���ʱ�䣬������Ӧ�Ķ���***************************
@SetTime   ���ô���ʱ��,Ϊhh*60+mm,��ʾhh:mm(24С`ʱ��ʱ��),��ʱ����ϵͳ��ǰʱ����ͬ;
@lpfnTimer ����ָ�룬�������Ķ���
@times:    ָ��������ִ�иò���������0��ʾ���޴�
@return    �����Ƿ��Ѿ��ɹ�����;
@ps.:      �������ǽ��̼��ͨ����,������ͨ�����븴����ʵ�ֹ���;
@�ݲ�����ʵ�֣����ǵ�����ͨ�����趨ʱ���ϵͳʱ�䶼ת�����뼴��ͨ��SetTimer()ʵ��

*********************************************************/
uint8 settrigtimer(void (*lpfnTimer)(void),uint32 *idcode,uint32 SetTime,uint32 times);


/*ȡ��֮ǰָ������ʱ����*/
uint8 cancel_delay_secend(uint8 delay_handle);


/*����������ʱ����
@ delays:   ָ����ʱʱ��,��*handleΪ��Чʱʹ��,���ڳ�ʼ��,�������*handle�������ʱ��Ϣ������ʱ
@ handle:   ��ʱ��ʱ�����,�þ������ʱʱ�䵽��ᱻ����Ч,���ٵ��ûῪʼ�µ�һ�ּ�ʱ
*/
bool delay_in_secend(uint32 delays,uint8 *handle);


uint64 show_time();
void push_time();
void pop_time();

#endif//APP_TIMER_H

