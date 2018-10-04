#include "VideoDecoder.h"

VideoDecoder::VideoDecoder(const char * filename) 
    : Decoder(filename, AVMEDIA_TYPE_VIDEO)
{
}

VideoDecoder::~VideoDecoder() {
}

bool VideoDecoder::decode(Packet& packet, Frame& frame) {
    int frame_finished;
    if(packet.getStreamIdx() == streamIdx) {
        avcodec_decode_video2(codecContext, frame, &frame_finished, packet);
        packet.free();
        return (frame_finished > 0);  
    }
    return false;
}
