/***************************************************************************
 *      
 *
 *
 * COPYRIGHT (C) 2009 PaxHZ, ALL RIGHTS RESERVED
 * $Abstract: IPC相关函数
 *
 * $Source:..src\public\ipcs.c$
 * $Author: wudengben$
 * $Date:2009-9-30 8:50$ 
 * $Revision:1.0 IPC相关函数$
 *
 * $Log:display.c$
 * Revision 1.0  2009-9-30 8:50  wudengben
 * IPC相关函数)
 *
 *
 ***************************************************************************/

#include <basetype.h>
#include "app_ipcs.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdint.h>
#include <errno.h>

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 1
#endif




/*信号量相关函数接口*/
void app_sem_set_idle(int sem_id)
{
    int ret=-1;
    struct sembuf sem_b;

    sem_b.sem_num = 0;
    sem_b.sem_op  = 1;
    sem_b.sem_flg = SEM_UNDO;    
    while(ret == -1)
    {
        ret =semop(sem_id,&sem_b,1);
        if(errno !=EINTR)
        {
            break;
        }
    }
}

void app_sem_wait_busy(int sem_id)
{
    int ret=-1;
    struct sembuf sem_b;
    uint32 busy_num=0;

    sem_b.sem_num =  0;
    sem_b.sem_op  = -1;
    sem_b.sem_flg =  SEM_UNDO;  
    while(ret == -1)
    {
        ret =semop(sem_id,&sem_b,1);
        if(errno !=EINTR)
        {
            break;
        }
        busy_num ++;
        if(busy_num >30)
        {
            printf("pid_%d busy num >30\n",getpid());
            busy_num  =0;
        }
    }
}

int app_sem_open(int key,bool bset)
{
    int sem_id;
    union semun sem_union; 
    
    sem_id = semget(key,1,0666|IPC_CREAT);
    if (bset == true)
    {
        sem_union.val = 1;
	    semctl(sem_id,0,SETVAL,sem_union);   
    } 
    return sem_id;
}


int app_sem_close(int sem_id)
{
    union semun sem_union;
	int ret = -1;
     ret = semctl(sem_id, 0, IPC_RMID, sem_union);    
	if(ret == -1)	
		perror("semctl");
	return ret;
}

/*共享内存设置接口*/

void *app_shm_open(int key,int size,uint8 retry_num)
{
    int shm_id;
    uint8 i = 0;
    void * paddr;
    while(1)
    {        
        shm_id = shmget(key,size, 0666|IPC_CREAT);

        if(shm_id != -1)
        {
            break;
        }
        if(i == retry_num)
        {
            printf("shmget error,retry %d fail\n",retry_num);
            return NULL;
        }
        
        char ipcrm[]="ipcrm -M 0x000000000000";        
        sprintf(ipcrm,"ipcrm -M %d\n",key);            
        system(ipcrm);
        printf("shmget error,retry..\n");
        i++;
    }

    paddr = (struct update_param_shm_st *)shmat(shm_id,NULL, 0);

    if(paddr == ((void *)(-1)))
    {
        printf("shmat error\n");
        return NULL;
    }    
    return paddr;
}

