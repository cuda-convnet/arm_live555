#ifndef __SHARE_H__
#define __SHARE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include <signal.h>


#define FIFO_CMD "/tmp/cmd.fifo"
#define FIFO_STREAM "/tmp/%d%s"
#define CMDCharCount 20
#define MaxChnCount 8

typedef enum fifo_cmd_name
{
	SETUP = 0,
	PLAY,
	STOP,
}FIFO_CMD_NAME;

typedef struct fifo_cmd_para
{
     FIFO_CMD_NAME cmd;
     unsigned int  chn;
}FIFO_CMD_PARA;





#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif