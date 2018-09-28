#include "Frame.h"
#include "Except.h"

Frame::Frame()
    : frame(av_frame_alloc(), av_free)
{
    if(!frame)
        throw Except("Can't alloc frame");
}

Frame::Frame(size_t size, AVPixelFormat fmt, int w, int h) 
    : frame(av_frame_alloc(), av_free)
{
    uint8_t* buffer = (uint8_t*)av_malloc(size); // Can use a shared_ptr?
    
    frame->width = w;
    frame->height = h;
    frame->format = fmt;
    avpicture_fill((AVPicture *)frame.get(), buffer, fmt, w, h);
   
}

Frame::Frame(const Frame& orig) {
    frame = orig.frame;
}

Frame::~Frame() {
}



