#ifndef ENCODER_H
#define ENCODER_H

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
#include <future>

#include "Frame.h"
#include "Packet.h"

class VideoEncoder {
public:
    VideoEncoder(AVCodecID codec, AVPixelFormat fmt, int w, int h);
    VideoEncoder(const VideoEncoder& orig) = delete;
    virtual ~VideoEncoder();
    
    bool encode(Frame &frame, Packet& packet) noexcept;
    
private:
    static void freeContext(AVCodecContext* ctx);
    std::shared_ptr<AVCodecContext> context;
};

#endif /* ENCODER_H */

