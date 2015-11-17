#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h> 
#include <common.h>

unsigned char g_mnt_flag;
unsigned char g_day_freeze_flag, g_hour_freeze_flag;
pthread_t 	g_db_env_init;
int g_thread_exit_flag;
int g_inner_meter_port=2;
/*==================================================================
//函数名：  thrd_db_env_init
//作者：    liuchiqi
//日期：    2011-5-18
//功能：    数据库环境初始化线程,创建完毕线程自动退出
//输入参数：无
//输出参数：无
//返回值：  无
//=================================================================*/
void thrd_db_env_init(void)
{
	log_error("meter enter %s ,%d\n", __FUNCTION__,__LINE__);
	int ret =-1;
	sigset_t set;
	sigfillset(&set);
	pthread_sigmask(SIG_SETMASK, &set, NULL);
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

	ret = db_env_init("/mnt/dblog.txt","meter", 0);

	if(ret != 0)
	{
		log_error("meter db_env_init error %s ,%d\n", __FUNCTION__,__LINE__);
		return ;
	}
	while(1)
	{
		if(g_thread_exit_flag == CON_STATUS_YES)
			break;
		sleep(3);
	}
	log_error("meter enter %s ,%d\n", __FUNCTION__,__LINE__);
	//return;
}


/*
 * 初始化100ms定时器
 */
void init_timer(void)
{
	struct itimerval value;
	
	value.it_interval.tv_sec = 0;
	value.it_interval.tv_usec = 100 * 1000;

	value.it_value.tv_sec = 0;
	value.it_value.tv_usec = 100 * 1000;
	
	setitimer(ITIMER_REAL, &value, NULL);
			
}

static int do_exit_task(void)
{
	log_error("meter enter %s ,%d\n", __FUNCTION__,__LINE__);
	g_thread_exit_flag=CON_STATUS_YES;
	if(g_db_env_init!= -1)
		pthread_join(g_db_env_init,NULL);
	
	log_error("meter enter %s ,%d\n", __FUNCTION__,__LINE__);
       MeterTaskExit();
	log_error("meter enter %s ,%d\n", __FUNCTION__,__LINE__);
	db_env_close();
	log_error("meter enter %s ,%d\n", __FUNCTION__,__LINE__);

	exit(0);
	log_error("meter enter %s ,%d\n", __FUNCTION__,__LINE__);
	return 0;
}

/*static int do_100ms_task(void)
{
	return 0;
}*/

static int do_first_init(void)
{
    MeterTaskInit();
	return 0;
}

int main(int argc, char *argv[])
{
	struct sigaction sigact;
	int ret;
	int sig;
	sigset_t  sigset;	
	//int i;
	if(argc >=2)
		g_inner_meter_port = atoi(argv[1]);
    if( g_inner_meter_port != 4 )
	   	g_inner_meter_port = 2;
	
    //初始化log文件
       log_init("meter", 1024);
    	log_error("meter enter %s ,%d\n", __FUNCTION__,__LINE__);

	// 初始化信号
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGALRM);
	sigaddset(&sigset, SIGTERM);
	sigprocmask(SIG_BLOCK, &sigset, NULL);

	memset(&sigact, 0, sizeof(sigact));
	sigact.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sigact, NULL);
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	sigaction(SIGHUP, &sigact, NULL);	
#if(CONFIG_METER_SW_DEBUG_MODE == GAL_NO)
    //调试时允许CTRL+C退出
	sigaction(SIGINT, &sigact, NULL);	
#endif
	sigaction(SIGCHLD, &sigact, NULL);	

	g_mnt_flag = 0;//初始化mnt分区标识
	g_day_freeze_flag = 0xff ;
	g_hour_freeze_flag = 0xff;
	g_thread_exit_flag = CON_STATUS_NO;
	//初始化500ms定时器
	ret = pthread_create(&g_db_env_init, NULL, (void*)thrd_db_env_init, NULL);
	if(ret){
		log_printf_level(LOG_LEVEL_ERR, DBGFMT_A" ERR pthread_create \n",DBGARG_A);
		return 1;
	}

	init_timer();
	//其它初始化, 第一次上电初始化
	do_first_init();
	
       ret = acs_open();
	   if (0 != ret)
	   {
			log_printf_level(LOG_LEVEL_ERR, DBGFMT_A" ERR ac sample open \n",DBGARG_A);
	   }
	   
 	param_shm_init();  //共享内存初始化
// 	boad_main_version_get(); //获取主板版本号

	while(1) {
		sig = sigwaitinfo(&sigset, NULL);

		if (sig == SIGTERM) {
   			ret = acs_close();
			if (0 != ret)
			{
				log_printf_level(LOG_LEVEL_ERR, DBGFMT_A" ERR ac sample close \n",DBGARG_A);
			}
			do_exit_task();
		}
		if (sig == SIGALRM) {
			Meter100msTask();
		}
		if (sig < 0) {
			log_error("sigwaitinfo return error %s\n", strerror(errno));
		}
	}
	log_error("meter enter %s ,%d\n", __FUNCTION__,__LINE__);
	return 0;
}

uchar get_cur_uart_port_no(void)
{
    uchar port_no = 2;
    if( (g_inner_meter_port > 0) && (g_inner_meter_port < 8) )
        port_no = g_inner_meter_port;
    return port_no;
}

//获取主板版本号
/*
void boad_main_version_get(void)
{
	ver = version_get(BOARD_MAIN);

       if(ver < 0)
       {
            ver = version_get(BOARD_MAIN);       
       }

	if(ver < 0) ver = 3;
}
*/
