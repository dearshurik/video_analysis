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
    Frame(int format, uint64_t channel_layout, int sample_rate, int channels);
    Frame(const Frame& orig);
    virtual ~Frame();

    operator AVFrame*() const { return frame.get(); }
	Frame& operator=(Frame& other) {
		av_frame_copy_props(frame.get(), other.frame.get());
		frame->channel_layout = other.frame->channel_layout;
		frame->sample_rate = other.frame->sample_rate;
		frame->format =  other.frame->format;
	}
	
    Frame& operator=(Frame&& other) {
		frame = std::move(other.frame);
	}
	
    AVFrame* operator ->() { return frame.get(); } 
    int64_t timestamp() const { return av_frame_get_best_effort_timestamp(frame.get()); }
    uint8_t* video_data() const { return frame.get()->data[0]; }
    short* audio_data(uint8_t ch) const { return (short*)frame.get()->data[ch]; }

    size_t size() const { return frame.get()->nb_samples; }

    uint8_t channels() const { return frame->channels; }

    void setFormat(enum AVSampleFormat fmt) {
            frame->format = fmt; 
    }
			
private:
    std::shared_ptr<AVFrame> frame;

};

#endif /* FRAME_H */
