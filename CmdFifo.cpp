#include "CmdFifo.h"

CmdFifo::CmdFifo()
{
	  if((mkfifo(FIFO_CMD,FILE_MODE)<0)&&(errno!=EEXIST))
	{
        #ifdef DEBUG
             printf("create CMD_FIFO failed,errno=%d.\n",errno);
        #endif

	}
        else
      {
        #ifdef DEBUG
             printf("create CMD_FIFO success.\n");
        #endif
      }
	this->fd_write=open(FIFO_CMD,O_WRONLY,0);
}
CmdFifo::~CmdFifo() {
	close(fd_write);
	unlink(FIFO_CMD);
}






