#ifndef     __FIFO_H__
#define     __FIFO_H__
#include "share.h"


class CmdFifo
{

    public:
        CmdFifo();
        virtual ~CmdFifo();
        
     protected:
            int fd_write;
			FIFO_CMD_PARA cmd;

};


#endif

