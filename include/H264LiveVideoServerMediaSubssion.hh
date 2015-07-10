/*!
* FileName : H264LiveVideoServerMediaSubssion.hh 
* brief       : For h264 VideoServer 
* author    : 
*/
#ifndef _H264_LIVE_VIDEO_SERVER_MEDIA_SUBSSION_HH
#define _H264_LIVE_VIDEO_SERVER_MEDIA_SUBSSION_HH

#include "liveMedia/H264VideoFileServerMediaSubsession.hh"

class H264LiveVideoServerMediaSubssion : public H264VideoFileServerMediaSubsession
{
	public:
	static H264LiveVideoServerMediaSubssion *
		createNew(UsageEnvironment& env,
               		char const* fileName, 
                	Boolean reuseFirstSource);


    protected : 
      
		H264LiveVideoServerMediaSubssion(UsageEnvironment& env, 
													char const* fileName, 
													Boolean reuseFirstSource);

		~H264LiveVideoServerMediaSubssion();


		FramedSource* createNewStreamSource(unsigned clientSessionId,
                          unsigned& estBitrate);

	
	public :
		char fFileName[100];     
    
};


#endif

