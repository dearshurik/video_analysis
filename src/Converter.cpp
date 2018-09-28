#include "Converter.h"

Converter::Converter(AVCodecContext* ctx, int w, int h, AVPixelFormat fmt)
    : imgConvertCtx(nullptr)
    , numBytes(0)
{
    imgConvertCtx = sws_getCachedContext(imgConvertCtx, ctx->width, ctx->height,
        ctx->pix_fmt, w, h, fmt, SWS_BICUBIC, NULL, NULL, NULL);
    
    numBytes = avpicture_get_size(fmt, w, h);    
}


Converter::~Converter() {
}

bool Converter::convert(Frame& frame, Frame& frame_out) {
    sws_scale(imgConvertCtx, (const uint8_t* const*)frame->data, frame->linesize, 
            0, frame->height, frame_out->data, frame_out->linesize);
    
    return true;
}
