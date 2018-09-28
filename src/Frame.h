#ifndef FRAME_H
#define FRAME_H

extern "C"{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
}

#include <memory>

class Frame {
public:
    Frame();
    Frame(size_t size, AVPixelFormat fmt, int w, int h);
    Frame(const Frame& orig);
    virtual ~Frame();

    operator AVFrame*() const { return frame.get(); }
    AVFrame* operator ->() { return frame.get(); } 
    int64_t getTimestamp() const { return av_frame_get_best_effort_timestamp(frame.get()); }

private:
    std::shared_ptr<AVFrame> frame;

};

#endif /* FRAME_H */

