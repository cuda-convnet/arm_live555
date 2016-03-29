#ifndef _INPUT_FIFO_HH
#define _INPUT_FIFO_HH

#include <UsageEnvironment.hh>
#include <stdio.h>

#if (defined(__WIN32__) || defined(_WIN32) || defined(_WIN32_WCE))
#ifndef _WIN32_WCE
// Include header files that might be needed by Windows (in code that uses this header file):
#include <io.h>
#include <fcntl.h>
#endif

#ifndef _WIN32_WCE
#include <sys/stat.h>
#endif
#endif

int OpenInputFifo(UsageEnvironment& env, char const* fileName);

void CloseInputFifo(int fid);

#endif
