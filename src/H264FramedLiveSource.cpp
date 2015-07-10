/*!
* FileName : H264FramedLivedSource.cpp 
* brief :  build H264Frame source 
* author: 6000
*/
#include "H264FramedLiveSource.hh"


/*! 
\brief   createNew ,public api for H264FramedlivedSource 
\return point to H264FramedLivedSource
*/
H264FramedLiveSource* H264FramedLiveSource::createNew(UsageEnvironment & env,
								char const * fileName,
								unsigned preferredFrameSize ,
								unsigned playTimePerFrame )
{
	H264FramedLiveSource* frameSource = new H264FramedLiveSource(env , 
																	fileName,
																	preferredFrameSize,
																	playTimePerFrame);
	return frameSource; 
}

/*!
\brief destructor for H264FramedLivedSource
*/
H264FramedLiveSource::~H264FramedLiveSource()
{
	if(inputFile != NULL )
	{
		fclose(inputFile);
	}	
}


/*!
\brief constructor for H264FramedLivedSource  called by createNew API
*/
H264FramedLiveSource :: H264FramedLiveSource(UsageEnvironment & env,
											char const * fileName,
											unsigned preferredRTCPPacketSize,
											unsigned playTimePerFrame)
											:FramedSource(env)
{
	if(fileName != NULL)
	{
		inputFile  =  fopen( fileName, "rb" );
	}	
}

/*!
\brief get next H264Frames, called by getNextFrame()
*/

void H264FramedLiveSource::doGetNextFrame()
{
	if(getFileSize(inputFile) > fMaxSize)
	{
		fFrameSize = fread(fTo,1,fMaxSize,inputFile);
	}
	else 
	{
		fFrameSize = fread(fTo,1,getFileSize(inputFile),inputFile);
        fseek(inputFile, 0, SEEK_SET);	
	}

	nextTask() = envir().taskScheduler().scheduleDelayedTask( 0,
        													(TaskFunc*)FramedSource::afterGetting, 
        													this);//表示延迟0秒后再执行 afterGetting 函数
    return;
}


/*!
\brief   : get file size use ftell func 
\return : Size of the FILE
*/
int H264FramedLiveSource::getFileSize(FILE *stream)
{
	long curpos, length;
    curpos = ftell(stream);
    fseek(stream, 0L, SEEK_END);
    length = ftell(stream);
    fseek(stream, curpos, SEEK_SET);
    return length;
}



								

