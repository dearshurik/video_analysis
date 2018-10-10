/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AudioDecoder.cpp
 * Author: kuznetsov
 * 
 * Created on October 4, 2018, 3:30 PM
 */

#include "AudioDecoder.h"
#include <iostream>

AudioDecoder::AudioDecoder(const char * filename)
    : Decoder(filename, AVMEDIA_TYPE_AUDIO)
    , conv(swr_alloc(), resamplerFree)
    , isConfig(false)
{
    swr_init(conv.get());
}

AudioDecoder::~AudioDecoder() {
    swr_close(conv.get());
}

bool AudioDecoder::decode(Packet& packet, Frame& frame) {
    int frame_finished;
    if(packet.getStreamIdx() == streamIdx) {
        Frame decodedFrame;
        avcodec_decode_audio4(codecContext, decodedFrame, &frame_finished, packet);
        if(frame_finished) {
            frame = decodedFrame;
            frame.setFormat(AV_SAMPLE_FMT_S16P);
            if(!isConfig) {
                swr_config_frame(conv.get(), frame, decodedFrame);
                isConfig = true;
            }
            int ret = swr_convert_frame(conv.get(), frame, decodedFrame);
            std::cout << std::to_string(ret) << std::endl;
        }
        
        packet.free();
        return (frame_finished > 0);  
    }
    return false;
}

void AudioDecoder::resamplerFree(SwrContext* ptr) {
    swr_free (&ptr);
}
