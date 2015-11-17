//============================================================================
//  File Name: vt_platform.c
//
//  Copyright PAX Hangzhou 2011.  All rights reserved.
//
//  Description:
//      ��Ҫ�Ǳ�����һЩ����ƽ̨��صĽӿ�ģ��
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
//��������  mc_soft_watch_dog_feed
//���ߣ�    ���ι� ������ "third_task.c"
//���ڣ�    2011-5-3
//���ܣ�    ι������Ź�
//���������count��������ֵ
//�����������
//����ֵ��  ��
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
/*ͨ���źų�ʼ����ʱ��,�˺���ע��Ķ�ʱ������ע�⺯����������*/
bool MeterInittimer(uint32 step)
{
    //if(step == 0)
    //{
    //    step = 100000;
    //}

    //sg_timer_b_use_alarm = 1;

    //timer_sec_count = 1;
    //memset(sg_st_timer_handle,0,sizeof(sg_st_timer_handle));/*fork��,������Ҫ�̳и���������,�����³�ʼ��*/
    
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
//����ļ���ʼ����������ֻ�ʺ���������ʼ��
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
ԭ�ͣ�u8 ReadAt24c256b(u8 *Dst, u16 Src, u16 Len);
���ܣ�ģ���At24c256b��ȡһ�����ݣ���������С���������Զ�Ƭ������
������
Input:s��Dstָ���Ž���ĵ�ַ��Src�������ڴ�ĵ�ַ��Len�����ݿ�ĳ��ȡ�
���أ�����һ��u8�͵Ľ����
��Χ��Ӧ�ò�ֱ�ӵ��á�
ע�ͣ��ޡ�
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
ԭ�ͣ�uchar WriteAt24c256b(u16 Dst, uchar *Src, u16 Len);
���ܣ�ģ����At24c256bд��һ�����ݡ�
������
Input:s��Dst�������ڴ�ĵ�ַ��Srcָ���Ž���ĵ�ַ��Len�����ݿ�ĳ��ȡ�
���أ�����һ��uchar�͵Ľ����
��Χ��Ӧ�ò�ֱ�ӵ��á�
ע�ͣ��ޡ�
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
ԭ�ͣ�u8 ReadBakData(u8 *Dst, u16 Src, u16 Len);
���ܣ�ģ���At24c256b��ȡһ�����ݣ���������С���������Զ�Ƭ������
������
Input:s��Dstָ���Ž���ĵ�ַ��Src�������ڴ�ĵ�ַ��Len�����ݿ�ĳ��ȡ�
���أ�����һ��u8�͵Ľ����
��Χ��Ӧ�ò�ֱ�ӵ��á�
ע�ͣ��ޡ�
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
ԭ�ͣ�uchar WriteBakData(u16 Dst, uchar *Src, u16 Len);
���ܣ�ģ����At24c256bд��һ�����ݡ�
������
Input:s��Dst�������ڴ�ĵ�ַ��Srcָ���Ž���ĵ�ַ��Len�����ݿ�ĳ��ȡ�
���أ�����һ��uchar�͵Ľ����
��Χ��Ӧ�ò�ֱ�ӵ��á�
ע�ͣ��ޡ�
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
ԭ�ͣ�u8 ReadDataFromFlash(u8 *Dst, u16 Src, u16 Len);
���ܣ�ģ���FLASH��ȡһ�����ݣ���������С���������Զ�Ƭ������
������
Input:s��Dstָ���Ž���ĵ�ַ��Src�������ڴ�ĵ�ַ��Len�����ݿ�ĳ��ȡ�
���أ�����һ��u8�͵Ľ����
��Χ��Ӧ�ò�ֱ�ӵ��á�
ע�ͣ��ޡ�
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
            //�ļ������ʱ�䵽�������ļ��Ƿ�׼���ã�ǿ��ȫ������Ӳ���洢��
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
                    //�ļ��Ѿ�READY,����д�룬�Է��������������
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
ԭ�ͣ�uchar WriteDataToFlash(u8 devId,const u8 *up,u32 ulAddr,u16 uiLen);
���ܣ�ģ����flashд��һ�����ݡ�
������
Input:s��Dst�������ڴ�ĵ�ַ��Srcָ���Ž���ĵ�ַ��Len�����ݿ�ĳ��ȡ�
���أ�����һ��uchar�͵Ľ����
��Χ��Ӧ�ò�ֱ�ӵ��á�
ע�ͣ��ޡ�
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
            //�ļ������ʱ��δ��
            if(ReadFileData(&temp[0], 0, 1, FILE_FLASH) != DLT_RET_SUCC)
            {
                //flash����ʧ�ܣ�����MNT����δ׼����
                //�����ڻ���ʱ�䣬�򻺴�
                ret = FileBufSet(GAL_FLASH1, up, ulAddr, uiLen);
            }
            else
            {
                //��Ȼ���ļ��Ѿ��ܹ�������������Ҫ������
                isFlashBuf = 0;
                if(FileBufRecordNum>0)
                    FileBufWriteCommit(GAL_FLASH1);
            }
        }
        else
        {
            //�ļ������ʱ�䵽����ȫ������Ӳ���洢��
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
//ģ��FLASHɾ��
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
//ģ��������ʾ
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
            //��ѭ������
            return DLT_RET_ERR;
        }
        if(pFbuf->ulFileType == ulFlieType)
        {
            //Ŀǰֻ�������FLASH�ļ�¼���ݣ�����¼���Ƕ���İ���洢�������ڽ�������
            //������ʱ�����������ڿ�Ȼ�������----���ǿ�����
            if((ulAddr >= pFbuf->pOffset) && ((ulAddr+ulLen) <= (pFbuf->pOffset+pFbuf->ulLen)) )
            {
                //���У��������뻺������ݿ鱻�����ڱ���Ԥ������ݿ���
                memcpy((pFbuf->pData + (ulAddr - pFbuf->pOffset)), pData, ulLen);
                return DLT_RET_SUCC;
            }
            else if((ulAddr <= pFbuf->pOffset) && ((ulAddr+ulLen) >= (pFbuf->pOffset+pFbuf->ulLen)) )
            {
                //�����У����Ǳ���Ԥ������ݿ鱻�����ڵ�ǰ���뻺������ݿ���
                //��ɾ����Ԥ��飬���¿���һ��
                pFbuf->ulLen = 0;
            }
            else if((ulAddr < pFbuf->pOffset) 
                    && ( (ulAddr+ulLen) >= pFbuf->pOffset )
                    && ((ulAddr+ulLen) <= (pFbuf->pOffset+pFbuf->ulLen)) )
            {
                //�������(β���м䣬ͷ��ǰ), ��ɾ���ϲ�
                u8 *pTemp;
                u16 uiUnMatchBefore = (pFbuf->pOffset - ulAddr); //ǰ��δ���г����������ݳ���,ͷ-ͷ
                pTemp = (u8*)malloc(pFbuf->ulLen + uiUnMatchBefore);
                if(pTemp == NULL) return DLT_RET_ERR;
                memcpy(pTemp, pData, ulLen);
                memcpy(pTemp+ulLen, pFbuf->pData + ulLen - uiUnMatchBefore, pFbuf->ulLen - (ulLen - uiUnMatchBefore));
                if(isNeedFree == 1) 
                    free((uchar*)pData);    //��ʾpData�Ѿ������������
                pData = pTemp;
                pFbuf->ulLen = 0;   //delete
                isNeedFree = 1;
            }
            else if((ulAddr >= pFbuf->pOffset) 
                    && ( ulAddr <= pFbuf->pOffset )
                    && ((ulAddr+ulLen) > (pFbuf->pOffset+pFbuf->ulLen)) )
            {
                //ǰ������(ͷ���м䣬β�ں�), ��ɾ���ϲ�
                u8 *pTemp;
                u16 uiUnMatchBefore = (ulAddr+ulLen-(pFbuf->pOffset+pFbuf->ulLen)); //����δ���г����������ݳ��ȣ�β-β
                pTemp = (u8*)malloc(pFbuf->ulLen + uiUnMatchBefore);
                if(pTemp == NULL) return DLT_RET_ERR;
                memcpy(pTemp, pFbuf->pData, pFbuf->ulLen + uiUnMatchBefore - ulLen);
                memcpy(pTemp+pFbuf->ulLen + uiUnMatchBefore - ulLen, pData, ulLen);
                if(isNeedFree == 1) 
                    free((uchar*)pData);    //��ʾpData�Ѿ������������
                pData = pTemp;
                pFbuf->ulLen = 0;   //delete
                isNeedFree = 1;
            }
        }
        pFbuf = pFbuf->pNext;
        idx++;
    }
    return FileBufPush(ulFlieType, pData, ulAddr, ulLen); //����
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
            //��ѭ������
            return DLT_RET_ERR;
        }
        if(pFbuf->ulFileType == ulFlieType)
        {
            //Ŀǰֻ�������FLASH�ļ�¼���ݣ�����¼���Ƕ���İ���洢�������ڽ�������
            //������ʱ�����������ڿ�Ȼ�������
            if((ulAddr >= pFbuf->pOffset) && ((ulAddr+ulLen) <= (pFbuf->pOffset+pFbuf->ulLen)) )
            {
                //����
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
    //Ŀǰֻ�������FLASH�ļ�¼���ݣ�����¼���Ƕ���İ���洢�������ڽ�������
    //������ʱ�����������ڿ�Ȼ�������
    //ͬʱ��������������������͵Ļ���
    FileBufTrace();
    while(pFbuf != NULL)
    {
        if((idx >= FileBufRecordNum) || (idx >= FILE_BUFF_RECORD_MAX))
        {
            //��ѭ������
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

