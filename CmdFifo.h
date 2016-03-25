#ifndef     __BASIC_UNIX_H__
#define     __BASIC_UNIX_H__
//有exit函数原型
#include <stdio.h>
#include <stdlib.h>
//每次程序调用失败的时候，系统会自动用用错误代码填充errno这个全局变量
#include <errno.h>
//包含所有标准UNIX函数原型 read\write\unlink
#include <unistd.h>
#endif

#ifndef     __FIFO_H__
#define     __FIFO_H__


//文件操作 open close
#include <fcntl.h>
//fifo所需头文件
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

