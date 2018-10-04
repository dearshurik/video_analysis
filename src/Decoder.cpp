#include "Decoder.h"
#include "Except.h"

Decoder::Decoder(const char* filename, AVMediaType type) 
    : formatContext(nullptr)
    , codecContext(nullptr)
    , streamIdx(-1)
{
    avcodec_register_all();
    av_register_all();

    if (avformat_open_input(&formatContext, filename, NULL, NULL) < 0)
        throw Except("Unable to open input file");

    if (avformat_find_stream_info(formatContext, NULL) < 0)
        throw Except("Unable to find stream info");
  
    
    for (auto i = 0; i < formatContext->nb_streams; ++i) {
        if (formatContext->streams[i]->codec->codec_type == type) {
                streamIdx = i;
                break;
        }
    }
    
    if(streamIdx >= 0) {
        codecContext = formatContext->streams[streamIdx]->codec;
        AVCodec* codec = avcodec_find_decoder(codecContext->codec_id);
        if (avcodec_open2(codecContext, codec, NULL) < 0)
            throw Except("Unable to open codec");
    }
}

Decoder::~Decoder() {
    avcodec_close(codecContext);    
    avformat_close_input(&formatContext);    
}

bool Decoder::readPacket(Packet& packet) {
    return (av_read_frame(formatContext, packet) >= 0);
}

bool Decoder::seek(double timestamp) {
    return (av_seek_frame(formatContext, -1, timestamp/getCodecTimeBase()/getStreamTimeBase(), AVSEEK_FLAG_ANY) >=0);
}
