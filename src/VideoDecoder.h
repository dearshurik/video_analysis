#ifndef VIDEODECODER_H
#define VIDEODECODER_H

extern "C"{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
    #include <libavfilter/avfiltergraph.h>
    //#include <libavfilter/avcodec.h>
    #include <libavfilter/buffersink.h>
    #include <libavfilter/buffersrc.h>
}

#include <memory>

#include "Frame.h"
#include "Decoder.h"
#include "Packet.h"

class VideoDecoder
    : public Decoder
{
public:
    VideoDecoder(const char * filename);
    VideoDecoder(const VideoDecoder& orig) = delete;
    virtual ~VideoDecoder();

    virtual bool decode(Packet& packet, Frame& frame) override;
};

#endif /* VIDEODECODER_H */

