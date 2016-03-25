#ifndef     __BASIC_UNIX_H__
#define     __BASIC_UNIX_H__
//��exit����ԭ��
#include <stdio.h>
#include <stdlib.h>
//ÿ�γ������ʧ�ܵ�ʱ��ϵͳ���Զ����ô���������errno���ȫ�ֱ���
#include <errno.h>
//�������б�׼UNIX����ԭ�� read\write\unlink
#include <unistd.h>
#endif

#ifndef     __FIFO_H__
#define     __FIFO_H__


//�ļ����� open close
#include <fcntl.h>
//fifo����ͷ�ļ�
#include <sys/stat.h>
//default file access permissions for new files
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define VIDEO_FIFO "/opt/live/armServer/video_fifo.264"
//#define CMD_FIFO "/opt/live/armServer/cmd_fifo" //arm 
#define CMD_FIFO "/root/live/armServer/cmd_fifo" //linux workstation

class CmdFifo
{
    public:
            enum cmdToMpp
        {
            PLAY,
            STOP
        };
    public:
        CmdFifo();
        virtual ~CmdFifo();
        
     protected:
            int fd_write,fd_dummy_read;
			cmdToMpp cmd;

};


#endif

