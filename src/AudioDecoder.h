#ifndef AUDIODECODER_H
#define AUDIODECODER_H

extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/opt.h>
#include <libavresample/avresample.h>
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
	
	uint64_t channelLayout() const { return codecContext->channel_layout; }
	uint64_t sampleRate() const { return codecContext->sample_rate; }	
	uint8_t  getAudioCh() const { return codecContext->channels; }	
private:
	static void resamplerFree(AVAudioResampleContext* ptr);
	std::shared_ptr<AVAudioResampleContext> conv;
	bool isConfig;
};

#endif /* AUDIODECODER_H */

