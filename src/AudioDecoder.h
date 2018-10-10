#ifndef AUDIODECODER_H
#define AUDIODECODER_H

extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/opt.h>
#include <libswresample/swresample.h>
}

#include <memory>

#include "Frame.h"
#include "Decoder.h"
#include "Packet.h"

class AudioDecoder 
	: public Decoder
{
public:
	AudioDecoder(const char * filename);
	AudioDecoder(const AudioDecoder& orig) = delete;
	virtual ~AudioDecoder();
	
    virtual bool decode(Packet& packet, Frame& frame) override;
	
private:
	static void resamplerFree(SwrContext* ptr);
	std::shared_ptr<SwrContext> conv;
	bool isConfig;
};

#endif /* AUDIODECODER_H */

