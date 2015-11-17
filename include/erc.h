#ifndef ERC_H
#define ERC_H


#include <basetype.h>


struct record_event_st
{
    uint8 erc_no; /*�¼�����ERC*/
    uint8 len;    /*�¼���¼����Le*/
    uint8 data[]; /*�¼���¼����*/
}__attribute__((packed));

struct rec_date_st
{
    uint8  date_min;
    uint8  date_hour;
    uint8  date_day;
    uint8  date_month;
    uint8  date_yera;
}__attribute__((packed));

struct record_erc5_st
{
    struct rec_date_st rec_date;
    uint8  trun;
    uint8 trip_value[2];
    uint8 after_power[2];
}__attribute__((packed));

struct record_erc6_st
{
    struct rec_date_st rec_date;
    uint8  gp_no;
    uint8  trun;
    uint8  pctrl_id;        /*�������*/
    uint8 trip_power[2];    /*��բǰ���ʣ��ܼӹ��ʣ�*/    
    uint8 after_power[2];   /*��բ��2���ӵĹ��ʣ��ܼӹ��ʣ�*/
    uint8 set_power[2];     /*��բʱ���ʶ�ֵ*/
}__attribute__((packed));

struct record_erc7_st
{
    struct rec_date_st rec_date;
    uint8 gp_no;
    uint8 trun;
    uint8 eryctrl_id;
    uint8 ery_value[4];
    uint8 set_value[4];
}__attribute__((packed));

struct record_erc19_st
{
    struct rec_date_st rec_date;
    uint8 gp_no;
    uint8 order[4];
    uint8 refresh;
    uint8 setvalue[4];     /*���õ����ض�ֵ,��λΪǧ��ʱ*/              
    uint8 alarmhold[4];    /*��������,��λΪǧ��*/
    uint8 triphold[4];     /*��բ����,��λΪǧ��*/
    uint8 leftvalue_old[4];/*���ι���ǰʣ�������(��)*/
    uint8 leftvalue_new[4];/*���ι����ʣ�������(��)*/
}__attribute__((packed));





#define RECORD_ERC(index)       (index)

#define RECORD_ERC_5_LEN        sizeof(struct record_erc5_st)
#define RECORD_ERC_6_LEN        sizeof(struct record_erc6_st)
#define RECORD_ERC_7_LEN        sizeof(struct record_erc7_st)
#define RECORD_ERC_19_LEN       sizeof(struct record_erc19_st)


void rec_wr_date(struct rec_date_st* des_date);

#endif // ERC_H
