#ifndef __SAVEMETER_TO_DBF_H__
#define __SAVEMETER_TO_DBF_H__
struct plc_rec_data_decompose_per
{
    unsigned short data_id;
    unsigned char data[8];
};

struct  plc_rec_data_decompose{
    unsigned char data_id_num;
    struct plc_rec_data_decompose_per data_decompose_per[20]; 
};
extern void savemeterdata_to_dbf(unsigned char poweroff_flag);
extern int param_shm_init(void);

extern int get_program_key_status(void);


#endif

