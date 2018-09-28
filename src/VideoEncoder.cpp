#include "VideoEncoder.h"
#include "Except.h"

VideoEncoder::VideoEncoder(AVCodecID codec, AVPixelFormat fmt, int w, int h)
    : context(avcodec_alloc_context3( avcodec_find_encoder(codec) ), freeContext)
{
    if(!context)
        throw Except("Can't alloc encoder context");
    
    context->pix_fmt = fmt; 
    context->height = h;
    context->width = w;
    context->time_base = {1, 1};
    
    if(avcodec_open2(context.get(), avcodec_find_encoder(codec), NULL) < 0)
        throw Except("Can't open encoder");
}

VideoEncoder::~VideoEncoder() {
}

bool VideoEncoder::encode(Frame &frame, Packet& packet) noexcept
{
    int gotFrame;

    if (avcodec_encode_video2(context.get(), packet, frame, &gotFrame) < 0) 
        return false;
    
    if(gotFrame)
        return false;
    
    return true;
}

void VideoEncoder::freeContext(AVCodecContext* ctx) {
    avcodec_free_context(&ctx);
}

