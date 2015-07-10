#include <stdio.h>
#include "liveMedia/liveMedia.hh"
#include "liveMedia/H264or5VideoStreamFramer.hh"
#include "BasicUsageEnvironment/BasicUsageEnvironment.hh"
#include "groupsock/GroupsockHelper.hh"
#include "H264LiveVideoServerMediaSubssion.hh"
#include "H264FramedLiveSource.hh"


#if 1

UsageEnvironment *env ;  

Boolean reuseFirstSource = True; 
static void announceStream(RTSPServer* rtspServer, 
							ServerMediaSession* sms,
							char const *streamName, 
							char const *inputFileName);

// what is ?
static char newMatroskaDemuxWatchVariable ; 
static MatroskaFileServerDemux* demux ;


static void onMatroskaDemuxCreation(MatroskaFileServerDemux* newDemux, void* ) {
 	demux = newDemux;
 	newMatroskaDemuxWatchVariable = 1;
}


int main(int argc , char** argv )
{
	// create Task scheduler and set to Basic Environment
	TaskScheduler *scheduler = BasicTaskScheduler::createNew();
	env = BasicUsageEnvironment::createNew(*scheduler);


	//create authDB for access control 
	UserAuthenticationDatabase * authDB = NULL  ;
#ifdef ACCESS_CONTROL
	authDB = new UserAuthenticationDatabase ; 
	authDB->addUserRecord("username","password");
#endif 

	// create the RTSP server 
	RTSPServer* rtspServer = RTSPServer::createNew(*env,8554,authDB);
	if( rtspServer == NULL )
	{
		*env << "Failed to create RTSP Server :" << env->getResultMsg() << "\n";
		return -1 ;
	}

	// should use descString  
	char const * descString = "Session Streamed by \"live555DemoRTSPServer\"";

	//create H264 video stream 
	
	char const *streamName = "H264ESVideoTest";
	char const *inputFileName = "test.h264";
	
	//create MediaSession   set streamName eg.
	ServerMediaSession* sms = ServerMediaSession::createNew( *env,
															streamName,
															streamName,
															descString);

	// add Subsession  for mediaSession  now add H264LiveVideoServerMediaSubssion 
	sms->addSubsession(H264LiveVideoServerMediaSubssion::createNew(*env,
																	inputFileName,
																	reuseFirstSource));

	// add server mediaSession to rtsp Server 
	rtspServer->addServerMediaSession(sms);  

	
	//at last announce the stream 
	announceStream( rtspServer,
					sms,
					streamName,
					inputFileName);

	*env << "开始发送流媒体...\n";

	// run task
	env->taskScheduler().doEventLoop();

	return 0 ;
	
}


static void announceStream(RTSPServer * rtspServer,ServerMediaSession * sms,char const * streamName,char const * inputFileName)
{
	char * url = rtspServer->rtspURL(sms);

	UsageEnvironment & env = rtspServer->envir();

	env << "\n\"" << streamName << "\"stream. from the file \"" << inputFileName << "\"\n" ; 
	env << "Play this stream using the URL\"" << url << "\"\n";
	delete[] url ;
}
#endif 


