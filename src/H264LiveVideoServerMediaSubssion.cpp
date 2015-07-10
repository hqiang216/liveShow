/*!
* Name: H264LiveVideoServerMediaSubssion.cpp
*brief   :create H264LiveVideoServerMediaSubssion
*author : 6000  
*/

#include "H264LiveVideoServerMediaSubssion.hh"
#include "H264FramedLiveSource.hh"
#include "liveMedia/H264VideoStreamFramer.hh"


/*!
\brief  public API for createNew MediaSubssion for H264LiveVideo
\return H264LiveVideoServerMediaSubssion itself 
*/
H264LiveVideoServerMediaSubssion * H264LiveVideoServerMediaSubssion::createNew(UsageEnvironment & env,
																		char const * fileName,
																		Boolean reuseFirstSource)
{
	  return new H264LiveVideoServerMediaSubssion( env, fileName, reuseFirstSource );
}


/*!
\brief  
\return FramedSource 
*/
FramedSource* H264LiveVideoServerMediaSubssion::createNewStreamSource(unsigned clientSessionId,
																	unsigned & estBitrate)
{
	// TODO
	 /* Remain to do : assign estBitrate */
    estBitrate = 1000; // kbps, estimate

    // Create the video source:
    H264FramedLiveSource* liveSource = H264FramedLiveSource::createNew(envir(), fFileName);
    if (liveSource == NULL)
    {
        return NULL;
    }

    // Create a framer for the Video Elementary Stream:
    return H264VideoStreamFramer::createNew(envir(), liveSource);
}


H264LiveVideoServerMediaSubssion::H264LiveVideoServerMediaSubssion(UsageEnvironment & env,
																char const * fileName,
																Boolean reuseFirstSource)
																:H264VideoFileServerMediaSubsession( env, fileName, reuseFirstSource )
{
	strcpy(fFileName,fileName);
}


H264LiveVideoServerMediaSubssion::~H264LiveVideoServerMediaSubssion()
{
	
}





