CFLAGS = -c -fPIC -Wall
SRC_DIR = src
LIB555_DIR = lib/live555
LIBS = $(LIB555_DIR)/libliveMedia.a $(LIB555_DIR)/libgroupsock.a $(LIB555_DIR)/libBasicUsageEnvironment.a $(LIB555_DIR)/libUsageEnvironment.a
INCS = -Iinclude -Iinclude/UsageEnvironment/include -Iinclude/groupsock/include
SRCS = $(SRC_DIR)/live555Demo.cpp $(SRC_DIR)/H264FramedLiveSource.cpp $(SRC_DIR)/H264LiveVideoServerMediaSubssion.cpp
live555Demo:
	g++ -static-libstdc++ -o live555demo $(SRCS) $(INCS) -L/lib  $(LIBS) 

