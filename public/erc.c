#include <erc.h>
#include <time.h>

void rec_wr_date(struct rec_date_st* des_date)
{
    time_t timep;
    struct tm *ptime;   

    time(&timep);
    ptime=localtime(&timep); /*取得当前本地时间*/    
    des_date->date_min  = (uint8)(hex_to_bcd(ptime->tm_min)); 
    des_date->date_hour = (uint8)(hex_to_bcd(ptime->tm_hour));
    des_date->date_day  = (uint8)(hex_to_bcd(ptime->tm_mday));
    des_date->date_month= (uint8)(hex_to_bcd(ptime->tm_mon+1));
    des_date->date_yera = (uint8)(hex_to_bcd(ptime->tm_year-100));
}

