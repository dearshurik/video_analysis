CC=g++
CFLAGS=-std=gnu++14 -I./include -I./src -g -Wall 
LDFLAGS=-lpthread

FFMPEG_LIBS=    libavdevice                        \
                libavformat                        \
                libavfilter                        \
                libavcodec                         \
                libswresample                      \
                libswscale                         \
                libavutil                          \

CFLAGS := $(shell pkg-config --cflags $(FFMPEG_LIBS)) $(CFLAGS)
LDFLAGS := $(shell pkg-config --libs $(FFMPEG_LIBS)) $(LDFLAGS)

SOURCES= \
	src/AudioDec.cpp \
	src/Converter.cpp  \
	src/FilterChain.cpp  \
	src/SceneIndex.cpp \
	src/VideoDecImpl.cpp \
	src/AudioDecImpl.cpp \
	src/Decoder.cpp \
	src/Frame.cpp \
	src/SceneIndexImpl.cpp \
	src/VideoDecoder.cpp \
	src/AudioDecoder.cpp \
	src/Except.cpp \
	src/Packet.cpp \
	src/VideoDec.cpp \
	src/VideoEncoder.cpp \
	testenv/main.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

%.o : %.cpp
	echo $<
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm $(OBJECTS)
