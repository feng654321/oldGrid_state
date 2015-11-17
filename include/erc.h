#ifndef ERC_H
#define ERC_H


#include <basetype.h>


struct record_event_st
{
    uint8 erc_no; /*事件代码ERC*/
    uint8 len;    /*事件记录长度Le*/
    uint8 data[]; /*事件记录内容*/
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
    uint8  pctrl_id;        /*功控类别*/
    uint8 trip_power[2];    /*跳闸前功率（总加功率）*/    
    uint8 after_power[2];   /*跳闸后2分钟的功率（总加功率）*/
    uint8 set_power[2];     /*跳闸时功率定值*/
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
    uint8 setvalue[4];     /*设置电量控定值,单位为千瓦时*/              
    uint8 alarmhold[4];    /*报警门限,单位为千瓦*/
    uint8 triphold[4];     /*跳闸门限,单位为千瓦*/
    uint8 leftvalue_old[4];/*本次购电前剩余电能量(费)*/
    uint8 leftvalue_new[4];/*本次购电后剩余电能量(费)*/
}__attribute__((packed));





#define RECORD_ERC(index)       (index)

#define RECORD_ERC_5_LEN        sizeof(struct record_erc5_st)
#define RECORD_ERC_6_LEN        sizeof(struct record_erc6_st)
#define RECORD_ERC_7_LEN        sizeof(struct record_erc7_st)
#define RECORD_ERC_19_LEN       sizeof(struct record_erc19_st)


void rec_wr_date(struct rec_date_st* des_date);

#endif // ERC_H
