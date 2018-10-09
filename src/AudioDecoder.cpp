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
    , conv(avresample_alloc_context(), resamplerFree)
    , isConfig(false)
{
    avresample_open(conv.get());
}

AudioDecoder::~AudioDecoder() {
    avresample_close(conv.get());
}

bool AudioDecoder::decode(Packet& packet, Frame& frame) {
    int frame_finished;
    if(packet.getStreamIdx() == streamIdx) {
        Frame decodedFrame;
        avcodec_decode_audio4(codecContext, frame, &frame_finished, packet);
        /*if(frame_finished) {
            if(!isConfig) {
                avresample_config(conv.get(), frame, decodedFrame);
                isConfig = true;
            }
            int ret = avresample_convert_frame(conv.get(), frame, decodedFrame);
            std::cout << std::to_string(ret) << std::endl;
        }*/
        
        packet.free();
        return (frame_finished > 0);  
    }
    return false;
}

void AudioDecoder::resamplerFree(AVAudioResampleContext* ptr) {
    avresample_free(&ptr);
}
