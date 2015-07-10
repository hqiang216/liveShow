/*!
* Filename : H264FrameLiveSource.hh
* brief :  build liveSource for H264 
* author: 6000
*/

#ifndef _H264FRAMEDLIVESOURCE_HH
#define _H264FRAMEDLIVESOURCE_HH
#include "liveMedia/FramedSource.hh"
#include <stdio.h>

class H264FramedLiveSource : public FramedSource
{
	
	public : 
	// ����ӿ� ,���ڴ���H264FramedLivedSource
	static H264FramedLiveSource* createNew(UsageEnvironment& env ,
											char const * fileName,
											unsigned preferredFrameSize = 0  , 
											unsigned playTimePerFrame = 0 );



	protected :

		// protected ���캯��������ʹ��createNew  ����
		H264FramedLiveSource(UsageEnvironment& env);
		
		H264FramedLiveSource(UsageEnvironment& env ,
									char const *fileName , 
									unsigned preferredRTCPPacketSize , 
									unsigned playTimePerFrame);


		~H264FramedLiveSource();

	private :
		
		virtual void doGetNextFrame() ; 

		int getFileSize(FILE *stream);		


		int getFrameSize();

	 

	protected :

		// temp use FILE 
		FILE *inputFile ; 

		//TODO : how to set real H264 frame to the liveSource
		
	
	
} ; 



#endif 



