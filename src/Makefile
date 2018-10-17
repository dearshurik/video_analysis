CC=g++
LIB=../lib/libvideoanalysis.so
EXEC=main
CFLAGS=-std=gnu++14 -I../include -g -Wall -fPIC -fvisibility=hidden
LDFLAGS=-lpthread -shared

FFMPEG_LIBS=    libavdevice                        \
                libavformat                        \
                libavfilter                        \
                libavcodec                         \
                libswresample                      \
                libswscale                         \
                libavutil                          \
		libavresample			   \

CFLAGS := $(shell pkg-config --cflags $(FFMPEG_LIBS)) $(CFLAGS)
LDFLAGS := $(shell pkg-config --libs $(FFMPEG_LIBS)) $(LDFLAGS)

SOURCES= \
	AudioDec.cpp \
	Converter.cpp  \
	FilterChain.cpp  \
	SceneIndex.cpp \
	VideoDecImpl.cpp \
	AudioDecImpl.cpp \
	Decoder.cpp \
	Frame.cpp \
	SceneIndexImpl.cpp \
	VideoDecoder.cpp \
	AudioDecoder.cpp \
	Except.cpp \
	Packet.cpp \
	VideoDec.cpp \
	VideoEncoder.cpp 

OBJECTS=$(SOURCES:.cpp=.o)
	
all: $(LIB)

$(LIB): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	
%.o : %.cpp
	echo $<
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm $(OBJECTS) $(LIB)
