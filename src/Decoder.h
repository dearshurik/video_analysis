
#ifndef DECODER_H
#define DECODER_H

extern "C"{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
}

#include "Frame.h"
#include "Packet.h"

class Decoder {
public:
    Decoder(const char* filename, AVMediaType type);
    Decoder(const Decoder& orig) = delete;
    virtual ~Decoder();
    
    virtual bool decode(Packet& packet, Frame& frame) = 0;
    
    operator AVCodecContext*() { return codecContext; }
    AVCodecContext* operator ->() { return codecContext; } 
    bool readPacket(Packet& packet);
    bool seek(double timestamp);
	double getCodecTimeBase() const { return av_q2d(formatContext->streams[streamIdx]->codec->time_base); }
	double getStreamTimeBase() const { return av_q2d(formatContext->streams[streamIdx]->time_base); }

protected:
    AVFormatContext*    formatContext;
    AVCodecContext*     codecContext;
    int                 streamIdx;
	int64_t				timeBase;
};

#endif /* DECODER_H */

