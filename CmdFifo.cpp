#include "CmdFifo.h"

CmdFifo::CmdFifo()
{
	  if((mkfifo(CMD_FIFO,FILE_MODE)<0)&&(errno!=EEXIST))
	{
        #ifdef DEBUG
             fprintf(stderr,"create CMD_FIFO failed,errno=%d.\n",errno);
        #endif
		throw errno;
	}
	this->fd_write=open(CMD_FIFO,O_WRONLY,0);
}
CmdFifo::~CmdFifo() {
	close(fd_write);
	unlink(CMD_FIFO);
}




/* int CmdFifo::writeCmd(CmdFifo::cmdToMpp cmd)
{
    return write(this->fd_cmd,&cmd,sizeof(CmdFifo::cmdToMpp));
} */




