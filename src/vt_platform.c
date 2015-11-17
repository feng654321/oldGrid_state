//============================================================================
//  File Name: vt_platform.c
//
//  Copyright PAX Hangzhou 2011.  All rights reserved.
//
//  Description:
//      主要是表型里一些驱动平台相关的接口模拟
//
//  Modification History:
//      $Id:  Exp $
//      $Log: $
//      Revision 1.0 Create by Taozhiguo in 2011.04.28
//============================================================================
#ifndef __VT_PLATFORM_C__
#define __VT_PLATFORM_C__
#include "common.h"

/*==================================================================
//函数名：  mc_soft_watch_dog_feed
//作者：    陶治国 拷贝自 "third_task.c"
//日期：    2011-5-3
//功能：    喂软件看门狗
//输入参数：count，软狗计数值
//输出参数：无
//返回值：  无
//=================================================================*/
void mc_soft_watch_dog_feed(int count);
void mc_soft_watch_dog_feed(int count)
{
	int fd;
	int ret=-1;
    int g_meter_pid;

	fd=open("/var/meter_watch_dog.log",O_WRONLY|O_CREAT|O_TRUNC, 0666);
	if (fd < 0)
		return;

	ret = flock(fd, LOCK_EX);
	if (ret < 0)
	{
		close(fd);
		return;
	}
    g_meter_pid = getpid();
	write(fd, &g_meter_pid, sizeof(g_meter_pid));
	write(fd, &count, sizeof(count));
	flock(fd, LOCK_UN);
	close(fd);
}

void ClearWatchDog(void)
{
    static u16 uiWDogCount=0;
    mc_soft_watch_dog_feed(uiWDogCount++);
}

/*void MeterTrace(uchar TraceId, uchar* fmt, args...)
{
    //printf(fmt, )
}*/
#if 0
/*通过信号初始化定时器,此后其注册的定时服务需注意函数的重入性*/
bool MeterInittimer(uint32 step)
{
    //if(step == 0)
    //{
    //    step = 100000;
    //}

    //sg_timer_b_use_alarm = 1;

    //timer_sec_count = 1;
    //memset(sg_st_timer_handle,0,sizeof(sg_st_timer_handle));/*fork后,若不需要继承父进程设置,可重新初始化*/
    
    signal(SIGALRM, TimerManage10ms);   
    
    struct itimerval tick;
    // Initialize struct     
    memset((void *)&tick, 0, sizeof(struct itimerval));
    //Timeout to run function first time           
    tick.it_value.tv_usec   =  1000*10; // micro sec.             
    //Interval time to run function   
    tick.it_interval.tv_usec = 100000;//step;         
    /* Set timer, ITIMER_REAL : real-time to decrease timer,     
    send SIGALRM when timeout  */  
    setitimer(ITIMER_REAL, &tick, NULL);   
	return true;
}
#endif
//表计文件初始化，本函数只适合于生产初始化
void MeterFileInit(const string *FileName, ulong FileLen)
{
    FILE *pFile=NULL;
    ulong ulFileLen=0, uiWrLen, ret;
    uchar *pData;
	
    mkdir("/mnt/dbf", 0777);
    pFile = fopen(FileName, "ab+");
    if(pFile != NULL)
    {
        fseek(pFile, 0, SEEK_END); 
        ulFileLen = ftell(pFile);
        MTRACE("FLASH file len = %d !\n", ulFileLen);
        if(ulFileLen < FileLen)
        {
            pData = (uchar*)malloc(512);
            if(pData == NULL)
                return;
            memset(pData, 0, 512);
            while(ulFileLen < FileLen)
            {
                if(ulFileLen+512 > FileLen)
                    uiWrLen = FileLen - ulFileLen;
                else
                    uiWrLen = 512;
                ret = fwrite((void*)pData, 1, uiWrLen, pFile);
                if (ret != uiWrLen) {
                    //MTRACE(stderr, "fwrite fail: %s\n", strerror(errno));
                    ErrPrint("fwrite fail: %s\n", strerror(errno));
                    break;                }
                ulFileLen += uiWrLen;
                MTRACE("flen %d\n", ulFileLen);
            }
            free(pData);
        }
        fclose(pFile);
    }
    else
    {
        ErrPrint("Open or Create file %s err !\n", FileName);
    }

}

uchar MeterFileClr(const string *FileName, ulong FileLen)
{
    FILE *pFile=NULL;
    ulong ulFileLen=0, uiWrLen, ret = DLT_RET_SUCC;
    uchar *pData;
    
    LOGTRACE("MeterFileClr %s, %d\n", FileName, FileLen);
    pFile = fopen(FileName, "wb");
    if(pFile != NULL)
    {
        //frewind(pFile);
        ulFileLen = 0;
        if(ulFileLen < FileLen)
        {
            pData = (uchar*)malloc(512);
            if(pData == NULL)
                return DLT_RET_ERR;
            memset(pData, 0, 512);
            while(ulFileLen < FileLen)
            {
                if(ulFileLen+512 > FileLen)
                    uiWrLen = FileLen - ulFileLen;
                else
                    uiWrLen = 512;
                ret = fwrite((void*)pData, 1, uiWrLen, pFile);
                if (ret != uiWrLen) {
                    //MTRACE(stderr, "fwrite fail: %s\n", strerror(errno));
                    ErrPrint("fwrite fail: %s\n", strerror(errno));
                    ret = DLT_RET_ERR;
                    break;                }
                ulFileLen += uiWrLen;
                //MTRACE("flen %d\n", ulFileLen);
            }
            free(pData);
        }
        fclose(pFile);
    }
    else
    {
        ErrPrint("Open file %s err !\n", FileName);
        return DLT_RET_ERR;
    }
    LOGTRACE("MeterFileClr End !\n");
    return ret;
}

u8 ReadFileData(u8 *pData, u32 pAddr, u16 Len, const string* FileName)
{
    FILE *pFile=NULL;
    ulong ret;
    pFile = fopen(FileName, "rb");
    if(pFile == NULL)
    {
        ErrPrint("Open r file %s 0x%08X fail !\n", FileName, pAddr);
#if(CONFIG_METER_FACTORY_MODE_ENABLE == CONFIG_METER_FACTORY_MODE)
		if (strcmp(FileName, FILE_FLASH) == 0)
			MeterFileInit(FILE_FLASH, FILE_LEN_FLASH);
#endif

        return DLT_RET_ERR;
    }
    ret = fseek(pFile, pAddr, SEEK_SET);
    if(ret != 0)
    {
        ErrPrint("Seek r file %s pos 0x%08X,%d fail !\n", FileName, pAddr, ret);
        fclose(pFile);
        return DLT_RET_ERR;
    }
    ret = ftell(pFile);
    if(ret != pAddr)
    {
        ErrPrint("Seek r file %s pos 0x%08X,%d fail !\n", FileName, pAddr, ret);
        fclose(pFile);
        return DLT_RET_ERR;
    }

    ret = fread(pData, 1, Len, pFile);
    if(ret != Len)
    {
        //ErrPrint("Read fail: %s\n", strerror(errno));
        //ErrPrint("Read file %s Len %d,%d fail !\n", FileName, ret, Len);
        ErrPrint("Read file %s off=0x%08X, Len=%d, ret=%d fail !\n", FileName, pAddr, Len, ret);
        fclose(pFile);
        return DLT_RET_ERR;
    }
    fclose(pFile);
    //MTRACE("Read file %s off=%d, Len=%d, ret=%d succ !\n", FileName, pAddr, Len, ret);
    return DLT_RET_SUCC;
}
u8 WriteFileData(const u8 *pData, u32 pAddr, u16 Len, const string* FileName)
{
    FILE *pFile=NULL;
    ulong ret;

    pFile = fopen(FileName, "rb+");
    if(pFile == NULL)
    {
        ErrPrint("Open w file %s 0x%08X fail !\n", FileName, pAddr);
#if(CONFIG_METER_FACTORY_MODE_ENABLE == CONFIG_METER_FACTORY_MODE)
		if (strcmp(FileName, FILE_FLASH) == 0)
			MeterFileInit(FILE_FLASH, FILE_LEN_FLASH);
#endif
        return DLT_RET_ERR;
    }
    ret = fseek(pFile, pAddr, SEEK_SET);
    if(ret != 0)
    {
        ErrPrint("Seek w file %s pos 0x%08X,%d fail !\n", FileName, pAddr, ret);
        fclose(pFile);
        return DLT_RET_ERR;
    }
    ret = ftell(pFile);
    if(ret != pAddr)
    {
        ErrPrint("Seek w file %s pos 0x%08X,%d fail !\n", FileName, pAddr, ret);
        fclose(pFile);
        return DLT_RET_ERR;
    }
    ret = fwrite(pData, 1, Len, pFile);
    if(ret != Len)
    {
        ErrPrint("write fail: %s\n", strerror(errno));
        ErrPrint("write file %s off=0x%08X, Len=%d, ret=%d fail !\n", FileName, pAddr, Len, ret);
        fclose(pFile);
        return DLT_RET_ERR;
    }
    //fflush();
    fclose(pFile);
    //MTRACE("write file %s off=%d, Len=%d, ret=%d succ !\n", FileName, pAddr, Len, ret);
    return DLT_RET_SUCC;
}

/*********************************************************************
原型：u8 ReadAt24c256b(u8 *Dst, u16 Src, u16 Len);
功能：模拟从At24c256b读取一块数据，对于容量小的器件可以多片串联。
参数：
Input:s。Dst指向存放结果的地址，Src是器件内存的地址，Len是数据块的长度。
返回：返回一个u8型的结果。
范围：应用层直接调用。
注释：无。
********************************************************************/
u8 ReadAt24c256b(u8 *Dst, u16 Src, u16 Len)
{
    ulong ret;

    ret =  ReadFileData(Dst, Src&0x00ffffff, Len, FILE_EPL);
    if(ret == DLT_RET_SUCC)
        return 0;
    return 1;
}
/*********************************************************************
原型：uchar WriteAt24c256b(u16 Dst, uchar *Src, u16 Len);
功能：模拟向At24c256b写入一块数据。
参数：
Input:s。Dst是器件内存的地址，Src指向存放结果的地址，Len是数据块的长度。
返回：返回一个uchar型的结果。
范围：应用层直接调用。
注释：无。
********************************************************************/
u8 WriteAt24c256b(u16 Dst, const u8 *Src, u16 Len)
{
    ulong ret;

    ret =  WriteFileData(Src, Dst&0x00ffffff, Len, FILE_EPL);
    if(ret == DLT_RET_SUCC)
        return 0;
    return 1;
}
/*********************************************************************
原型：u8 ReadBakData(u8 *Dst, u16 Src, u16 Len);
功能：模拟从At24c256b读取一块数据，对于容量小的器件可以多片串联。
参数：
Input:s。Dst指向存放结果的地址，Src是器件内存的地址，Len是数据块的长度。
返回：返回一个u8型的结果。
范围：应用层直接调用。
注释：无。
********************************************************************/
u8 ReadBakData(u8 *Dst, u16 Src, u16 Len)
{
    ulong ret;

    ret =  ReadFileData(Dst, Src&0x00ffffff, Len, FILE_BAK);
    if(ret == DLT_RET_SUCC)
        return 0;
    return 1;
}
/*********************************************************************
原型：uchar WriteBakData(u16 Dst, uchar *Src, u16 Len);
功能：模拟向At24c256b写入一块数据。
参数：
Input:s。Dst是器件内存的地址，Src指向存放结果的地址，Len是数据块的长度。
返回：返回一个uchar型的结果。
范围：应用层直接调用。
注释：无。
********************************************************************/
u8 WriteBakData(u16 Dst, const u8 *Src, u16 Len)
{
    ulong ret;

    ret =  WriteFileData(Src, Dst&0x00ffffff, Len, FILE_BAK);
    if(ret == DLT_RET_SUCC)
        return 0;
    return 1;
}

/*********************************************************************
原型：u8 ReadDataFromFlash(u8 *Dst, u16 Src, u16 Len);
功能：模拟从FLASH读取一块数据，对于容量小的器件可以多片串联。
参数：
Input:s。Dst指向存放结果的地址，Src是器件内存的地址，Len是数据块的长度。
返回：返回一个u8型的结果。
范围：应用层直接调用。
注释：无。
********************************************************************/
u8 ReadDataFromFlash(u8 devId,u8 *up,u32 ulAddr,u16 uiLen)
{
    u8 ret=DLT_RET_ERR;
    
    if(devId != FIRST_FLASH)
    {
        return 1;
    }

#if(FILE_BUFF_ENABLE == GAL_YES)
    if((FileBufRecordNum>0) )
    {
        if((ulRunSecTime > FLASH_FILE_BUFF_SECOND))
        {
            //文件缓存的时间到，不管文件是否准备好，强行全部存入硬件存储器
            FileBufWriteCommit(GAL_FLASH1);
        }
        else
        {
            ret = FileBufGet(GAL_FLASH1, up, ulAddr, uiLen);
            if(ret != DLT_RET_SUCC)
            {
                u8 temp[2];
                if(ReadFileData(&temp[0], 0, 1, FILE_FLASH) == DLT_RET_SUCC)
                {
                    //文件已经READY,则先写入，以防半命中情况发生
                    FileBufWriteCommit(GAL_FLASH1);
                }
            }
        }
    }
    if(ret != DLT_RET_SUCC)
#endif        
    ret =  ReadFileData(up, ulAddr&0x00ffffff, uiLen, FILE_FLASH);
    if(ret == DLT_RET_SUCC)
        return 0;
    return 1;
}
/*********************************************************************
原型：uchar WriteDataToFlash(u8 devId,const u8 *up,u32 ulAddr,u16 uiLen);
功能：模拟向flash写入一块数据。
参数：
Input:s。Dst是器件内存的地址，Src指向存放结果的地址，Len是数据块的长度。
返回：返回一个uchar型的结果。
范围：应用层直接调用。
注释：无。
********************************************************************/
u8 WriteDataToFlash(u8 devId,const u8 *up,u32 ulAddr,u16 uiLen)
{
    static u8 isFlashBuf=1;
    u8 ret=DLT_RET_ERR;

    if(devId != FIRST_FLASH)
    {
        return 1;
    }
    
#if(FILE_BUFF_ENABLE == GAL_YES)
    if(isFlashBuf>0)
    {
        u8 temp[2];
        if(ulRunSecTime <= FLASH_FILE_BUFF_SECOND)
        {
            //文件缓存的时间未到
            if(ReadFileData(&temp[0], 0, 1, FILE_FLASH) != DLT_RET_SUCC)
            {
                //flash操作失败，可能MNT分区未准备好
                //还是在缓存时间，则缓存
                ret = FileBufSet(GAL_FLASH1, up, ulAddr, uiLen);
            }
            else
            {
                //既然改文件已经能够操作，则不再需要缓存了
                isFlashBuf = 0;
                if(FileBufRecordNum>0)
                    FileBufWriteCommit(GAL_FLASH1);
            }
        }
        else
        {
            //文件缓存的时间到，则全部存入硬件存储器
            isFlashBuf = 0;
            if(FileBufRecordNum>0)
                FileBufWriteCommit(GAL_FLASH1);
        }
    }
    
    if(ret != DLT_RET_SUCC)
#endif        
    ret =  WriteFileData(up, ulAddr&0x00ffffff, uiLen, FILE_FLASH);
    
    if(ret == DLT_RET_SUCC)
        return 0;
    return 1;
}
//模拟FLASH删除
u8 EraseFullFlash(u8 devId)
{
    if(devId != FIRST_FLASH)
    {
        return DLT_RET_ERR;
    }
    
#if(FILE_BUFF_ENABLE == GAL_YES)
    if(FileBufRecordNum>0)
    {
        FileBufWriteCommit(GAL_FLASH1);
    }
#endif    
    
    return  MeterFileClr(FILE_FLASH, FILE_LEN_FLASH);
}
//模拟特殊显示
void EspDisplayOfOp(const string *StrShow, uchar persent)
{
    MTRACE("EspDisplay > %s, %d\n", StrShow, persent);
}
void DisplayFullScreen(void)
{
    MTRACE("<<<DisplayFullScreen >>>\n>");
}

void VtPlatformInit(void)
{
#if(FILE_BUFF_ENABLE == GAL_YES)
    pFileBufHead = NULL;
    FileBufSize = 0;
    FileBufRecordNum = 0;
#endif    
}

void VtPlatformSave(void)
{
#if(FILE_BUFF_ENABLE == GAL_YES)
    if(FileBufRecordNum>0)
    {
        FileBufWriteCommit(0xFFFFFFFF);
    }
#endif    
}

#if(FILE_BUFF_ENABLE == GAL_YES)
#define FileBufTrace    FUNCTRACE
uchar FileBufPush(u32 ulFlieType, const u8 *pData, u32 ulAddr, u32 ulLen)
{
    u8 *pTemp=NULL;
    VT_RAM_FILE_BUFF* pFbuf;
    u32 TempLen;

    FileBufTrace();
    TempLen = ulLen+sizeof(VT_RAM_FILE_BUFF);
    if((FileBufSize+TempLen > FILE_BUFF_BYTES_MAX) || (FileBufRecordNum >= FILE_BUFF_RECORD_MAX))
        return DLT_RET_ERR;
    
    pTemp = (u8*)malloc(TempLen);
    if(pTemp == NULL)
        return DLT_RET_ERR;
    
    pFbuf = (VT_RAM_FILE_BUFF*)pTemp;
    pFbuf->ulFileType = ulFlieType;
    pFbuf->pOffset = ulAddr;
    pFbuf->ulLen = ulLen;
    pFbuf->pData = pTemp+sizeof(VT_RAM_FILE_BUFF);
    memcpy(pFbuf->pData, pData, ulLen);
    pFbuf->pNext = pFileBufHead;
    pFileBufHead = pFbuf;
    FileBufSize = FileBufSize+TempLen;
    FileBufRecordNum++;
    return DLT_RET_SUCC;
}

uchar FileBufPop(u32 ulFlieType, u8 *pData, u32 ulAddr, u32 ulLen)
{
    FileBufTrace();
    return DLT_RET_SUCC;
}

uchar FileBufSet(u32 ulFlieType, const u8 *pData, u32 ulAddr, u32 ulLen)
{
    VT_RAM_FILE_BUFF* pFbuf = pFileBufHead;
    u32 idx=0;
    u8 isNeedFree=0;
    FileBufTrace();
    while(pFbuf != NULL)
    {
        if((idx >= FileBufRecordNum) || (idx >= FILE_BUFF_RECORD_MAX))
        {
            //死循环保护
            return DLT_RET_ERR;
        }
        if(pFbuf->ulFileType == ulFlieType)
        {
            //目前只用来存放FLASH的记录数据，而记录都是对齐的按块存储，不存在交错的情况
            //所以暂时不考虑数据在跨度缓存的情况----还是考虑了
            if((ulAddr >= pFbuf->pOffset) && ((ulAddr+ulLen) <= (pFbuf->pOffset+pFbuf->ulLen)) )
            {
                //命中，就是申请缓存的数据块被包括在本块预存的数据块内
                memcpy((pFbuf->pData + (ulAddr - pFbuf->pOffset)), pData, ulLen);
                return DLT_RET_SUCC;
            }
            else if((ulAddr <= pFbuf->pOffset) && ((ulAddr+ulLen) >= (pFbuf->pOffset+pFbuf->ulLen)) )
            {
                //反命中，就是本块预存的数据块被包括在当前申请缓存的数据块内
                //则删除本预存块，重新开启一块
                pFbuf->ulLen = 0;
            }
            else if((ulAddr < pFbuf->pOffset) 
                    && ( (ulAddr+ulLen) >= pFbuf->pOffset )
                    && ((ulAddr+ulLen) <= (pFbuf->pOffset+pFbuf->ulLen)) )
            {
                //后半命中(尾在中间，头在前), 则删除合并
                u8 *pTemp;
                u16 uiUnMatchBefore = (pFbuf->pOffset - ulAddr); //前面未命中长出部分数据长度,头-头
                pTemp = (u8*)malloc(pFbuf->ulLen + uiUnMatchBefore);
                if(pTemp == NULL) return DLT_RET_ERR;
                memcpy(pTemp, pData, ulLen);
                memcpy(pTemp+ulLen, pFbuf->pData + ulLen - uiUnMatchBefore, pFbuf->ulLen - (ulLen - uiUnMatchBefore));
                if(isNeedFree == 1) 
                    free((uchar*)pData);    //表示pData已经是新申请的了
                pData = pTemp;
                pFbuf->ulLen = 0;   //delete
                isNeedFree = 1;
            }
            else if((ulAddr >= pFbuf->pOffset) 
                    && ( ulAddr <= pFbuf->pOffset )
                    && ((ulAddr+ulLen) > (pFbuf->pOffset+pFbuf->ulLen)) )
            {
                //前半命中(头在中间，尾在后), 则删除合并
                u8 *pTemp;
                u16 uiUnMatchBefore = (ulAddr+ulLen-(pFbuf->pOffset+pFbuf->ulLen)); //后面未命中长出部分数据长度，尾-尾
                pTemp = (u8*)malloc(pFbuf->ulLen + uiUnMatchBefore);
                if(pTemp == NULL) return DLT_RET_ERR;
                memcpy(pTemp, pFbuf->pData, pFbuf->ulLen + uiUnMatchBefore - ulLen);
                memcpy(pTemp+pFbuf->ulLen + uiUnMatchBefore - ulLen, pData, ulLen);
                if(isNeedFree == 1) 
                    free((uchar*)pData);    //表示pData已经是新申请的了
                pData = pTemp;
                pFbuf->ulLen = 0;   //delete
                isNeedFree = 1;
            }
        }
        pFbuf = pFbuf->pNext;
        idx++;
    }
    return FileBufPush(ulFlieType, pData, ulAddr, ulLen); //新增
}

uchar FileBufGet(u32 ulFlieType, u8 *pData, u32 ulAddr, u32 ulLen)
{
    VT_RAM_FILE_BUFF* pFbuf = pFileBufHead;
    u32 idx=0;
    FileBufTrace();
    while(pFbuf != NULL)
    {
        if((idx >= FileBufRecordNum) || (idx >= FILE_BUFF_RECORD_MAX))
        {
            //死循环保护
            return DLT_RET_ERR;
        }
        if(pFbuf->ulFileType == ulFlieType)
        {
            //目前只用来存放FLASH的记录数据，而记录都是对齐的按块存储，不存在交错的情况
            //所以暂时不考虑数据在跨度缓存的情况
            if((ulAddr >= pFbuf->pOffset) && ((ulAddr+ulLen) <= (pFbuf->pOffset+pFbuf->ulLen)) )
            {
                //命中
                memcpy(pData, (pFbuf->pData + (ulAddr - pFbuf->pOffset)), ulLen);
                return DLT_RET_SUCC;
            }
        }
        pFbuf = pFbuf->pNext;
        idx++;
    }
    return DLT_RET_ERR;
}

uchar FileBufWriteCommit(u32 ulFlieType)
{
    VT_RAM_FILE_BUFF *pFbuf = pFileBufHead;
    u32 idx=0;
    //目前只用来存放FLASH的记录数据，而记录都是对齐的按块存储，不存在交错的情况
    //所以暂时不考虑数据在跨度缓存的情况
    //同时简单起见，不考虑其他类型的缓存
    FileBufTrace();
    while(pFbuf != NULL)
    {
        if((idx >= FileBufRecordNum) || (idx >= FILE_BUFF_RECORD_MAX))
        {
            //死循环保护
            return DLT_RET_ERR;
        }
        //if((pFbuf->ulFileType == ulFlieType) || (ulFlieType == 0xFFFFFFFF))
        {
            if(ulFlieType == GAL_FLASH1)
                WriteFileData(pFbuf->pData, pFbuf->pOffset, pFbuf->ulLen, FILE_FLASH);
            else
            {
                ErrPrint("FileBufWriteCommit ERR! for wrong file type\n")
            }
        }
        pFileBufHead = pFbuf->pNext;
        free((void*)pFbuf);
        pFbuf = pFileBufHead;
        FileBufRecordNum--;
        idx++;
    }
    pFileBufHead = NULL;
    if(FileBufRecordNum > 0)
    {
        ErrPrint("FileBufWriteCommit ERR! for wrong left record num=%d\n", FileBufRecordNum);
        FileBufRecordNum = 0;
    }
    FileBufSize = 0;
    return DLT_RET_SUCC;
}
#endif
#endif

