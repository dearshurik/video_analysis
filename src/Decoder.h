
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
    Decoder(char* filename, AVMediaType type);
    Decoder(const Decoder& orig) = delete;
    virtual ~Decoder();
    
    virtual bool decode(Packet& packet, Frame& frame) = 0;
    
    operator AVCodecContext*() { return codecContext; }
    AVCodecContext* operator ->() { return codecContext; } 
    bool readPacket(Packet& packet);
protected:
    AVFormatContext*    formatContext;
    AVCodecContext*     codecContext;
    int                 streamIdx;
};

#endif /* DECODER_H */

