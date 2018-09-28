#ifndef CONVERTER_H
#define CONVERTER_H

extern "C"{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
    #include <libavfilter/avfiltergraph.h>
    //#include <libavfilter/avcodec.h>
    #include <libavfilter/buffersink.h>
    #include <libavfilter/buffersrc.h>
}

#include "Frame.h"

class Converter {
public:
    Converter(AVCodecContext* ctx, int w, int h, AVPixelFormat fmt);
    Converter(const Converter& orig) = delete;
    virtual ~Converter();
    
    size_t getFrameSize() const noexcept { return numBytes; }
    bool operator()(Frame& frame, Frame& frame_out);
private:
    SwsContext* imgConvertCtx;
    ulong       numBytes;
};

#endif /* CONVERTER_H */

