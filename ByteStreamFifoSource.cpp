/**********
This library is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the
Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version. (See <http://www.gnu.org/copyleft/lesser.html>.)

This library is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
**********/
// "liveMedia"
// Copyright (c) 1996-2016 Live Networks, Inc.  All rights reserved.
// A file source that is a plain byte stream (rather than frames)
// Implementation

#include "ByteStreamFifoSource.hh"
#include "InputFifo.hh"
#include "GroupsockHelper.hh"

////////// ByteStreamFifoSource //////////

ByteStreamFifoSource*
ByteStreamFifoSource::createNew(UsageEnvironment& env, char const* fileName,
				unsigned preferredFrameSize,
				unsigned playTimePerFrame)
{
  int fid = OpenInputFifo(env, fileName);
  if (fid < 1) return NULL;

  ByteStreamFifoSource* newSource
    = new ByteStreamFifoSource(env, fid, preferredFrameSize, playTimePerFrame);

  return newSource;
}

ByteStreamFifoSource*
ByteStreamFifoSource::createNew(UsageEnvironment& env, int fid,
				unsigned preferredFrameSize,
				unsigned playTimePerFrame) {
  if (fid < 1) return NULL;

  ByteStreamFifoSource* newSource = new ByteStreamFifoSource(env, fid, preferredFrameSize, playTimePerFrame);

  return newSource;
}


ByteStreamFifoSource::ByteStreamFifoSource(UsageEnvironment& env, int fid,
					   unsigned preferredFrameSize,
					   unsigned playTimePerFrame)
  : FramedFifoSource(env, fid), fPreferredFrameSize(preferredFrameSize),
    fPlayTimePerFrame(playTimePerFrame), fLastPlayTime(0),
    fHaveStartedReading(False){

}

ByteStreamFifoSource::~ByteStreamFifoSource() {
  if (fFid < 1) return;

#ifndef READ_FROM_FILES_SYNCHRONOUSLY
  envir().taskScheduler().turnOffBackgroundReadHandling(fFid);
#endif

  CloseInputFifo(fFid);
}

void ByteStreamFifoSource::doGetNextFrame() {

#ifdef READ_FROM_FILES_SYNCHRONOUSLY
  doReadFromFile();
#else
  if (!fHaveStartedReading) {
    // Await readable data from the file:
    envir().taskScheduler().turnOnBackgroundReadHandling(fFid,
	       (TaskScheduler::BackgroundHandlerProc*)&fileReadableHandler, this);
    fHaveStartedReading = True;
  }
#endif
}

void ByteStreamFifoSource::doStopGettingFrames() {
  envir().taskScheduler().unscheduleDelayedTask(nextTask());
#ifndef READ_FROM_FILES_SYNCHRONOUSLY
  envir().taskScheduler().turnOffBackgroundReadHandling(fFid);
  fHaveStartedReading = False;
#endif
}

void ByteStreamFifoSource::fileReadableHandler(ByteStreamFifoSource* source, int /*mask*/) {
  if (!source->isCurrentlyAwaitingData()) {
    source->doStopGettingFrames(); // we're not ready for the data yet
    return;
  }
  source->doReadFromFile();
}

void ByteStreamFifoSource::doReadFromFile() {
  // Try to read as many bytes as will fit in the buffer provided (or "fPreferredFrameSize" if less)

  if (fPreferredFrameSize > 0 && fPreferredFrameSize < fMaxSize) {
    fMaxSize = fPreferredFrameSize;
  }

  fFrameSize = read(fFid, fTo, fMaxSize);
  if (fFrameSize == 0) {
    handleClosure();
    return;
  }

  // Set the 'presentation time':
  if (fPlayTimePerFrame > 0 && fPreferredFrameSize > 0) {
    if (fPresentationTime.tv_sec == 0 && fPresentationTime.tv_usec == 0) {
      // This is the first frame, so use the current time:
      gettimeofday(&fPresentationTime, NULL);
    } else {
      // Increment by the play time of the previous data:
      unsigned uSeconds	= fPresentationTime.tv_usec + fLastPlayTime;
      fPresentationTime.tv_sec += uSeconds/1000000;
      fPresentationTime.tv_usec = uSeconds%1000000;
    }

    // Remember the play time of this data:
    fLastPlayTime = (fPlayTimePerFrame*fFrameSize)/fPreferredFrameSize;
    fDurationInMicroseconds = fLastPlayTime;
  } else {
    // We don't know a specific play time duration for this data,
    // so just record the current time as being the 'presentation time':
    gettimeofday(&fPresentationTime, NULL);
  }

  // Inform the reader that he has data:
#ifdef READ_FROM_FILES_SYNCHRONOUSLY
  // To avoid possible infinite recursion, we need to return to the event loop to do this:
  nextTask() = envir().taskScheduler().scheduleDelayedTask(0,
				(TaskFunc*)FramedSource::afterGetting, this);
#else
  // Because the file read was done from the event loop, we can call the
  // 'after getting' function directly, without risk of infinite recursion:
  FramedSource::afterGetting(this);
#endif
}
