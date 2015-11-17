/***************************************************************************
 *
 *
 *
 * COPYRIGHT (C) 2009 PaxHZ, ALL RIGHTS RESERVED
 * $Abstract: 按键输入程序(调试用)
 *
 * $Source:..src\puclic\scanf_ex.c$
 * $Author: wudengben$
 * $2009-6-30 8:54$ 
 * $Revision:1.0  按键输入程序$
 *
 * $Log:scanf_ex.c$
 * Revision 1.0  2009-6-30 8:54  wudengben
 * 按键输入程序
 *
 *
 ***************************************************************************/

#include <pthread.h>
#include <basetype.h>
#include <stdio.h>
#include "display.h"


#define BUF_SIZE_MAX    1024

uint8 StringBuf[BUF_SIZE_MAX]="test";
uint8 *p;
static bool sg_scanf_b_full=0;

void * KeyScanf(void *arg)
{
	while(1){
	    		
		if(sg_scanf_b_full == true){
			continue;
		}  
        
		if(fgets(StringBuf,BUF_SIZE_MAX,stdin) == NULL)
		{
			dis_cmd_output("gets error\n");	
		}
		else{
		    dis_wait_busy();
		    printf("\r\b\r\b\r\n");
		    dis_clear_row();
		    dis_cancle_ctrl();
            sg_scanf_b_full=true;

            uint16 i;
            for(i=0;i<BUF_SIZE_MAX;i++)
            {
                if(StringBuf[i]==0x0a)
                {
                   StringBuf[i]=0;
                   break; 
                }    
            }    
            if(*StringBuf >=32)/*控制字符不显示*/
            {
                dis_cmd_output("%s input\n",StringBuf);                
            }
		}	
	}
	printf("error \n");
}

uint8 *get_buf_addr()
{
	if(sg_scanf_b_full == true){
		sg_scanf_b_full = false;
		return StringBuf;
	}
	return (void *)NULL;
	
}


void scanfex_init()
{
	pthread_t a_thread;
	uint32 res;	
	
	res = pthread_create(&a_thread,NULL,KeyScanf,(void *)NULL);
	if(res!= 0)
	{	
		dis_cmd_output("create error...\n");
	}	
	dis_cmd_output("KeyScanf is added ...\n");	
}
