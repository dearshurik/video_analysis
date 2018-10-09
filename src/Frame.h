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
	Frame& operator=(Frame& other) = delete;
    Frame& operator=(Frame&& other) = delete;
	
    AVFrame* operator ->() { return frame.get(); } 
    int64_t timestamp() const { return av_frame_get_best_effort_timestamp(frame.get()); }
	uint8_t* video_data() const { return frame.get()->data[0]; }
	int16_t* audio_data(uint8_t ch) const { return (int16_t*)frame.get()->extended_data[ch]; }
	
	size_t size() const { return frame.get()->nb_samples; }
	size_t audioSize() const {
		int plane_size;
		int data_size = av_samples_get_buffer_size(&plane_size, frame->channels,
											   frame->nb_samples,
											   (AVSampleFormat)frame->format, 1);
		return plane_size;
	}
			
private:
    std::shared_ptr<AVFrame> frame;

};

#endif /* FRAME_H */
