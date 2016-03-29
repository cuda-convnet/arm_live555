#ifndef     __FIFO_H__
#define     __FIFO_H__
#include "share.h"


class CmdFifo
{

    public:
        CmdFifo();
        virtual ~CmdFifo();
        int writeSetupCmd();
        int writePlayCmd(int chn);
        int writeStopCmd(int chn);
     protected:
            int fd_write;
			FIFO_CMD_PARA cmd;
            int writeCmd(FIFO_CMD_PARA*);

};


#endif

