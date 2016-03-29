#include "CmdFifo.h"

CmdFifo::CmdFifo()
{
	  if((mkfifo(FIFO_CMD,FILE_MODE)<0)&&(errno!=EEXIST))
	{
        #ifdef DEBUG
             printf("create CMD_FIFO failed,errno=%d.\n",errno);
        #endif

	}
	this->fd_write=open(FIFO_CMD,O_WRONLY,0);
}
CmdFifo::~CmdFifo() {
	close(fd_write);
	unlink(FIFO_CMD);
}

int CmdFifo::writeSetupCmd()
{
    FIFO_CMD_PARA p;
    p.cmd=SETUP;
    p.chn=0;
    return writeCmd(&p);

}
int CmdFifo::writePlayCmd(int chn)
{
    FIFO_CMD_PARA p;
    p.cmd=PLAY;
    p.chn=chn;
    return writeCmd(&p);
}
int CmdFifo::writeStopCmd(int chn)
{
    FIFO_CMD_PARA p;
    p.cmd=STOP;
    p.chn=chn;
    return writeCmd(&p);
}
int CmdFifo::writeCmd(FIFO_CMD_PARA* p)
{
    char cmd[CMDCharCount];
    memset(cmd,0,CMDCharCount);
    sprintf(cmd,"%u,%u",p->cmd,p->chn);
    if(write(this->fd_write,cmd,CMDCharCount)<0)
    {
        #ifdef DEBUG
             printf("writeCmd failed:%s \n",cmd);
        #endif
        return 0;
    }
    return 1;
}





