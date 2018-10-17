#ifndef VIDEODECIMPL_H
#define VIDEODECIMPL_H

#include <memory>
#include "Callback.h"

using namespace VideoAnalysis;

class VideoDecoder;
class Converter;

class VideoDecImpl {
public:
    VideoDecImpl(const char* filename, int picW, int picH, ImageCallback& sc);
    VideoDecImpl(const VideoDecImpl& orig) = delete;
    virtual ~VideoDecImpl();
    
    bool setInterval(double tsStart, double tsEnd);
    bool run();
private:
    std::shared_ptr<VideoDecoder>   videoDec;
    std::unique_ptr<Converter>      converter;
    ImageCallback&                  scene;
    int                             picW; 
    int                             picH;
    double							endTimestamp;
};

#endif /* VIDEODECIMPL_H */

